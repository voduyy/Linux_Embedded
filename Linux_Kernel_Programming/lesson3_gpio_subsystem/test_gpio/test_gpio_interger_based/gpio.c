#include <linux/module.h> /* This module defines functions such as module_init/module_exit */
#include <linux/gpio.h>   /* This module defines functions such as ioremap/iounmap */
                          /* Gpio modules */

#define DRIVER_AUTHOR "Vo Duy"
#define DRIVER_DESC "Turn on and off led"

#define GPIO1_12 44
#define LOW 0 
#define HIGH 1 
/* Constructor */
static int __init gpio_init(void)
{
    gpio_request(GPIO1_12, "GPIO1_12");
    gpio_direction_output(GPIO1_12, LOW);
    gpio_set_value(GPIO1_12, HIGH);
    pr_info("Status of led %s\n", gpio_get_value(GPIO1_12) ? "High" : "Low");
    return 0;
}

/* Destructor */
static void __exit gpio_exit(void)
{
    gpio_set_value(GPIO1_12, LOW);
    pr_info("Status of led %s\n", gpio_get_value(GPIO1_12) ? "High" : "Low");
    gpio_free(GPIO1_12);
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");