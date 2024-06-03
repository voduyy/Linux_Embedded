#include <linux/module.h>
#include <linux/fs.h>
#include <linux/printk.h>
#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESC "Hello kernel module_major_minor"
#define DRIVER_VERS "1.0"
struct my_dev_num
{
    dev_t dev_num;
} my_dev;

static int __init chdev_init(void)
{
    if (alloc_chrdev_region(&my_dev.dev_num, 0, 1, "my_dev_num") < 0)
    {
        pr_info("Failed to alloc new region \n");
        return -1;
    }
    pr_info("Hello kernel, major = %d, minor %d\n", MAJOR(my_dev.dev_num), MINOR(my_dev.dev_num));
    return 0;
}
static void __exit chdev_exit(void)
{
    unregister_chrdev_region(my_dev.dev_num, 1);
    pr_info("Goodbye, kernel\n");
}
module_init(chdev_init);
module_exit(chdev_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);
