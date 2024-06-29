#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/of.h>
#include <linux/device.h>
#define DRIVER_AUTHOR "voduy"
#define DRIVER_DESC "i2c oled"
#define DRIVER_VERS "1.0"

static const struct of_device_id my_spi_of_id[] = {
    {.compatible = "spi_driver"},
    {},
};

static int nokia_probe(struct spi_device *spi)
{
    struct spi_message spi_msg;
    struct spi_transfer spi_xfers;
    
    pr_info("Hello\n");
    return 0;
}
static int nokia_remove(struct spi_device *spi)
{
    pr_info("Hello\n");
    return 0;
}

static struct spi_driver nokia = {
    .driver = {
        .name = "nokia",
        .of_match_table = my_spi_of_id,
    },
    .probe = nokia_probe,
    .remove = nokia_remove,
};
MODULE_DEVICE_TABLE(of, my_spi_of_id);
module_spi_driver(nokia);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);