#include <linux/module.h>
#include <linux/gpio.h>

#define DRIVER_AUTHOR "VODUY"
#define DRIVER_DESC "Driver led on off"
#define DRIVER_VERS "1.0"

#define GPIO2_1 65
#define HIGH 1
#define LOW 0

static int __init gpio_init(void)
{
    gpio_request(GPIO2_1, "GPIO2_1");
    gpio_direction_output(GPIO2_1, LOW); // co the set san level
    gpio_set_value(GPIO2_1, HIGH);
    pr_info("Turn on led, status: %s \n", gpio_get_value(GPIO2_1) ? "HIGH" : "LOW");

    return 0;
}
static void __exit gpio_exit(void)
{
    gpio_set_value(GPIO2_1, LOW);
    pr_info("Turn off led, status: %s \n", gpio_get_value(GPIO2_1) ? "HIGH" : "LOW");
    gpio_free(GPIO2_1);
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);