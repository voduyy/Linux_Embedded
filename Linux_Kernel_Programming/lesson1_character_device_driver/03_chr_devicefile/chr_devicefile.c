#include <linux/module.h>
#include <linux/fs.h>
#include <linux/printk.h>
#include <linux/device.h>
#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESC "Hello kernel character device file"
#define DRIVER_VERS "1.0"

struct my_device
{
    struct class *my_class;
    dev_t dev_num;
} my_dev;

static int __init create_chrdev_file(void)
{
    if (alloc_chrdev_region(&my_dev.dev_num, 0, 1, "my_device_number") < 0)
    {
        pr_info("failed to alloc device number \n");
        return -1;
    }
    pr_info("Hello kernel, Major= %d, Minor = %d \n", MAJOR(my_dev.dev_num), MINOR(my_dev.dev_num));
    if ((my_dev.my_class = class_create(THIS_MODULE, "my_new_class")) == NULL)
    {
        pr_info("Can't create class \n");
        goto rm_dev_num;
    }
    if ((device_create(my_dev.my_class, NULL, my_dev.dev_num, NULL, "my_device")) == NULL)
    {
        pr_info("Can't create device file\n");
        goto rm_class;
    }
    pr_info("hello");
    pr_info("Create successfully\n");
    return 0;
rm_class:
    class_destroy(my_dev.my_class);
rm_dev_num:
    unregister_chrdev_region(my_dev.dev_num, 1);
    return -1;
}

static void __exit delete_chrdev_file(void)
{
    device_destroy(my_dev.my_class, my_dev.dev_num); /* 3.0 */
    class_destroy(my_dev.my_class);
    unregister_chrdev_region(my_dev.dev_num, 1);
    pr_info("Good bye\n");
}

module_init(create_chrdev_file);
module_exit(delete_chrdev_file);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);
