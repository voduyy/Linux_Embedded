#include <linux/module.h>          /* Defines functions such as module_init/module_exit */
#include <linux/gpio.h>            /* Defines functions such as gpio_request/gpio_free */
#include <linux/platform_device.h> /* For platform devices */
#include <linux/gpio/consumer.h>   /* For GPIO Descriptor */
#include <linux/of.h>              /* For DT */
#define DRIVER_AUTHOR "Vo Duy"
#define DRIVER_DESC "gpio subsystem"

#define LOW 0
#define HIGH 1
struct gpio_desc *gpiod;
static const struct of_device_id gpio_id[] =
    {
        {
            .compatible = "gpio_base_subsystem",
        },
        {
            /*sentinal*/
        }};
static int my_probe(struct platform_device *pdev)
{
    struct device *my_dev = &pdev->dev;
    gpiod = gpiod_get(my_dev, "led30", GPIOD_OUT_LOW);
    gpiod_set_value(gpiod, HIGH);
    pr_info("%s - %d", __func__, __LINE__);
    return 0;
}
static int my_remove(struct platform_device *pdev)
{

    gpiod_set_value(gpiod, LOW);
    pr_info("%s - %d", __func__, __LINE__);
    gpio_put(gpiod);
    return 0;
}
static struct platform_driver my_drv = {
    .probe = my_probe,
    .remove = my_remove,
    .driver = {
        .name = "driver_gpio",
        .of_match_table = of_match_ptr(gpio_id),
        .owner = THIS_MODULE,

    },
};
module_platform_driver(my_drv);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");