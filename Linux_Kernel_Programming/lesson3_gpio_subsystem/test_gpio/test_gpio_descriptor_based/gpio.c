#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>

#define DRIVER_AUTHOR "Vo Duy"
#define DRIVER_DESCRIPTION "gpio_descriptor"
#define DRIVER_VERSION "1.0"

#define LOW 1
#define HIGH 0
struct gpio_desc *my_gpio;
static const struct of_device_id gpiod_id[] = {
    {
        .compatible = "gpio_new_based",
    },
    {/*sentinal*/},
};
MODULE_DEVICE_TABLE(of, gpiod_id);

static int my_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    my_gpio = gpiod_get(dev, "myled", GPIOD_OUT_LOW);
    gpiod_set_value(my_gpio, HIGH);
    pr_info("State of LED %s\n", gpiod_get_value(my_gpio) ? "high" : "low");
    return 0;
}
static int my_remove(struct platform_device *pdev)
{
    gpiod_set_value(my_gpio, LOW);
    pr_info("State of LED %s\n", gpiod_get_value(my_gpio) ? "high" : "low");
    gpiod_put(my_gpio);
    return 0;
}
static struct platform_driver my_drv = {
    .probe = my_probe,
    .remove = my_remove,
    .driver = {
        .name = "my_driver_gpio",
        .of_match_table = gpiod_id,
        .owner = THIS_MODULE},
};
module_platform_driver(my_drv);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);
