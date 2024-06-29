#include <linux/module.h>
#include <linux/printk.h>
#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESC "Hello kernel module"
#define DRIVER_VERS "1.0"
static int __init chdev_init(void)
{
    pr_info("hello kernel Vo Duy\n");
    return 0;
}
static void __exit chdev_exit(void)
{
    pr_info("Exit, good byte\n");
}

module_init(chdev_init);
module_exit(chdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);