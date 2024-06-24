#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/printk.h>
#include <linux/atomic.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/pinctrl/consumer.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/types.h>
#include <linux/of.h>
#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESCRIPTION "GPIO IOCTL"
#define DRIVER_VERSION "1.0"

#define PWM_STATE _IOW('a', '1', int32_t *)
#define GPIO_STATE _IOW('a', '0', int32_t *)

#define HIGH 1
#define LOW 0
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset);
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset);
static int m_open(struct inode *inode, struct file *file);
static int m_release(struct inode *inode, struct file *file);
static long m_unlockioctl(struct file *filp, unsigned int cmd, unsigned long arg);

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
struct device *my_pinctrl_device;
static atomic_t state_of_module = ATOMIC_INIT(CDEV_NO_USE);
static struct file_operations fops = {
    .open = m_open,
    .release = m_release,
    .unlocked_ioctl = m_unlockioctl,
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
    return size;
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
static long m_unlockioctl(struct file *filp, unsigned int command, unsigned long arg)
{
    switch (command)
    {
    case PWM_STATE:
        pinctrl_get_select(my_pinctrl_device, "default");
        pr_info("Command PWM being called \n");
        break;
    case GPIO_STATE:
        pinctrl_get_select(my_pinctrl_device, "sleep");
        pr_info("Command GPIO being called \n");
        break;
    }
    return 0;
}
static int m_release(struct inode *inode, struct file *file)
{
    pr_info("Function close() being called\n");
    atomic_set(&state_of_module, CDEV_NO_USE);
    module_put(THIS_MODULE);
    return 0;
}
static const struct of_device_id pwm_gpio_id[] = {
    {.compatible = "pwm-gpio-pins"},
    {},
};
MODULE_DEVICE_TABLE(of, pwm_gpio_id);

static int gpio_probe(struct platform_device *pdev)
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
    my_pinctrl_device = &pdev->dev;

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
static int gpio_remove(struct platform_device *pdev)
{

    device_destroy(my_dev.my_class, my_dev.dev_num);
    class_destroy(my_dev.my_class);
    cdev_del(&my_dev.my_cdevice);
    unregister_chrdev_region(my_dev.dev_num, 1);
    gpiod_put(m_gpio);
    pr_info("Goodbye, kernel\n");
    return 0;
}
static struct platform_driver my_gpio_driver =
    {
        .probe = gpio_probe,
        .remove = gpio_remove,
        .driver = {
            .name = "gpio_driver",
            .of_match_table = pwm_gpio_id,
            .owner = THIS_MODULE,
        },
};
module_platform_driver(my_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);
