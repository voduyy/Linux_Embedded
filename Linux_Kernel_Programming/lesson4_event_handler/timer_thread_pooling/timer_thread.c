#include <linux/module.h>
#include <linux/timer.h>
#include <linux/printk.h>
#include <linux/jiffies.h>
#define DRIVER_AUTHOR "Vo Duy"
#define DRIVER_DESCRIPTION "timer thread"
#define VERSION "1.0"
#define TIME_OUT 2000

struct timer_list exp_timer;
void timer_callback(struct timer_list *data)
{
    pr_info("This is timer\n");
    mod_timer(&exp_timer, jiffies + msecs_to_jiffies(TIME_OUT));
}
static int __init my_timer_init(void)
{

    printk(KERN_INFO "Create timer thread \n");
    timer_setup_on_stack(&exp_timer, timer_callback, 0);

    mod_timer(&exp_timer, jiffies + msecs_to_jiffies(TIME_OUT));

    return 0;
}

static void __exit my_timer_exit(void)
{
    del_timer(&exp_timer);
    pr_info("Goodbye\n");
}
module_init(my_timer_init);
module_exit(my_timer_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(VERSION);