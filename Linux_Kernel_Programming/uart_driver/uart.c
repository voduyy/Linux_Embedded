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
#include <linux/serdev.h>
#include <linux/of.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <stdbool.h>
#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESCRIPTION "PWM DRIVER"
#define DRIVER_VERSION "1.0"
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset);
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset);
static int m_open(struct inode *inode, struct file *file);
static int m_release(struct inode *inode, struct file *file);

const char *msg;
int len;
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
struct device *my_device_uart;
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
static const struct of_device_id my_uart_id[] = {
    {.compatible = "my_uart_driver"},
    {},
};
MODULE_DEVICE_TABLE(of, my_uart_id);

static int serdev_receive_buf(struct serdev_device *serdev, const unsigned char *buffer, size_t size)
{
    pr_info("Receive data: %s\n", buffer);
    return 0;
}
static void serdev_write_wakeup(struct serdev_device *serdev)
{
    pr_info("Print hello \n");
    msg = "Hello world\n";
    len = strlen(msg);
    serdev_device_write(serdev, msg, len, 1000);
}
static const struct serdev_device_ops serdev_ops = {
    .receive_buf = serdev_receive_buf,
    .write_wakeup = serdev_write_wakeup,
};
static int my_uart_probe(struct serdev_device *pdev)
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
    my_device_uart = &pdev->dev;
    serdev_device_set_client_ops(pdev, &serdev_ops);
    serdev_device_open(pdev);
    serdev_device_set_baudrate(pdev, 9600);
    serdev_device_set_flow_control(pdev, false);
    serdev_device_set_parity(pdev, SERDEV_PARITY_NONE);
    serdev_device_write_buf(pdev, "Hello\n", strlen("Hello\n"));
    pr_info("Create successfully\n");
    return 0;
rm_class:
    class_destroy(my_dev.my_class);
rm_cdev:
    cdev_del(&my_dev.my_cdevice);
rm_device_num:
    unregister_chrdev_region(my_dev.dev_num, 1);
    return 1;
}
static void my_uart_remove(struct serdev_device *pdev)
{

    device_destroy(my_dev.my_class, my_dev.dev_num);
    class_destroy(my_dev.my_class);
    cdev_del(&my_dev.my_cdevice);
    unregister_chrdev_region(my_dev.dev_num, 1);
    pr_info("Goodbye, kernel\n");
}
static struct serdev_device_driver my_uart_driver =
    {
        .probe = my_uart_probe,
        .remove = my_uart_remove,
        .driver = {
            .name = "uart_driver",
            .of_match_table = my_uart_id,
            .owner = THIS_MODULE,
        },
};

module_serdev_device_driver(my_uart_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);
