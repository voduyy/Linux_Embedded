#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/printk.h>
#include <linux/atomic.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/pwm.h>
#include <linux/of.h>
#include <linux/string.h>
#include <linux/kernel.h>
#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESCRIPTION "PWM DRIVER"
#define DRIVER_VERSION "1.0"
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset);
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset);
static int m_open(struct inode *inode, struct file *file);
static int m_release(struct inode *inode, struct file *file);
const char *pwm_specs;
struct device_node *np;
unsigned long pwm_period;
struct my_dev
{
    dev_t dev_num;
    struct class *my_class;
    struct cdev my_cdevice;
} my_dev;

enum
{
    CDEV_NO_USE = 0,
    CDEV_BEING_USED = 1
};
struct pwm_device *pwm_dev;
struct device *my_device_pwm;
static atomic_t state_of_module = ATOMIC_INIT(CDEV_NO_USE);
static struct file_operations fops = {
    .open = m_open,
    .release = m_release,
    .read = m_read,
    .write = m_write};
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset)
{
    pr_info("Function read() being called\n");
    return 0;
}
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset)
{
    pr_info("Function write() being called\n");
    char *dynamic_ptr = NULL;
    int period_value = 0;
    int ret = -1;

    dynamic_ptr = (char *)kzalloc(size, GFP_KERNEL);
    if ((ret = copy_from_user(dynamic_ptr, user_buf, size)) < 0)
    {
        pr_err("can't copy\n");
        return -1;
    }
    if ((ret = kstrtol(dynamic_ptr, 10, (long *)&period_value)) < 0)
    {
        pr_err("can't convert\n");
        return -1;
    }
    pwm_config(pwm_dev, period_value / 2, period_value);
    return 1;
}
static int m_open(struct inode *inode, struct file *file)
{
    pr_info("Function open() being called\n");

    if (atomic_cmpxchg(&state_of_module, CDEV_NO_USE, CDEV_BEING_USED))
    {
        pr_info("Being used this module by another process\n");
        return -EBUSY; // LOG: Device or resource busy
    }
    pr_info("You are using this module\n");
    try_module_get(THIS_MODULE);
    pr_info("Quantity of user: %d\n", module_refcount(THIS_MODULE));
    return 0;
}
static int m_release(struct inode *inode, struct file *file)
{
    pr_info("Function close() being called\n");
    atomic_set(&state_of_module, CDEV_NO_USE);
    module_put(THIS_MODULE);
    return 0;
}
static const struct of_device_id my_pwm_id[] = {
    {.compatible = "my_pwm_driver"},
    {},
};
MODULE_DEVICE_TABLE(of, my_pwm_id);

static int my_pwm_probe(struct platform_device *pdev)
{
    if (alloc_chrdev_region(&my_dev.dev_num, 0, 1, "my_device_num") < 0)
    {
        pr_info("Can't alloc device numbers \n");
        return 1;
    }
    pr_info("Alloc successfully device numbers, Major = %d, Minor = %d \n", MAJOR(my_dev.dev_num), MINOR(my_dev.dev_num));
    cdev_init(&my_dev.my_cdevice, &fops);
    if (cdev_add(&my_dev.my_cdevice, my_dev.dev_num, 1) < 0)
    {
        pr_info("Can't generate character device \n");
        goto rm_device_num;
    }
    if (IS_ERR(my_dev.my_class = class_create(THIS_MODULE, "my_new_led_class")))
    {
        pr_info("Can't create class \n");
        goto rm_cdev;
    }
    if (IS_ERR(device_create(my_dev.my_class, NULL, my_dev.dev_num, NULL, "my_device")))
    {
        pr_info("Can't create device \n");
        goto rm_class;
    }
    my_device_pwm = &pdev->dev;
    pwm_dev = pwm_get(my_device_pwm, "my_sec_pwm");
    if (IS_ERR(pwm_dev))
    {
        pr_info("Can't get device \n");
        goto rm_device;
    }
    if (of_property_read_string(np, "pwms", &pwm_specs))
    {
        printk("Failed to read 'pwms' property\n");
        return -1;
    }

    if (sscanf(pwm_specs, "<ehrpwm1_pins 0 %ld", &pwm_period) != 1)
    {
        printk("Failed to parse pwm_period from pwm_specs: %s\n", pwm_specs);
        return -1;
    }

    printk("pwm_period: %ld\n", pwm_period);

    if (pwm_config(pwm_dev, pwm_period / 2, pwm_period) != 0)
    {
        printk("Failed to configure PWM\n");
        return -1;
    }
    pwm_enable(pwm_dev);
    pr_info("Create successfully\n");
    return 0;
rm_device:
    device_destroy(my_dev.my_class, my_dev.dev_num);
rm_class:
    class_destroy(my_dev.my_class);
rm_cdev:
    cdev_del(&my_dev.my_cdevice);
rm_device_num:
    unregister_chrdev_region(my_dev.dev_num, 1);
    return 1;
}
static int my_pwm_remove(struct platform_device *pdev)
{

    device_destroy(my_dev.my_class, my_dev.dev_num);
    class_destroy(my_dev.my_class);
    cdev_del(&my_dev.my_cdevice);
    unregister_chrdev_region(my_dev.dev_num, 1);
    pr_info("Goodbye, kernel\n");
    return 0;
}
static struct platform_driver my_pwm_driver =
    {
        .probe = my_pwm_probe,
        .remove = my_pwm_remove,
        .driver = {
            .name = "pwm_driver",
            .of_match_table = my_pwm_id,
            .owner = THIS_MODULE,
        },
};
module_platform_driver(my_pwm_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);
