#include <linux/module.h>
#include <linux/of.h>
#include <linux/i2c.h>

#define DRIVER_AUTHOR "voduy"
#define DRIVER_DESC "i2c oled"
#define DRIVER_VERS "1.0"

static const struct of_device_id i2c_of_id[] = {
    {
        .compatible = "i2c_driver",
    },
    {}};
MODULE_DEVICE_TABLE(of, i2c_of_id);
static int i2c_probe_new(struct i2c_client *client)
{
    pr_info("hello i2c\n");
    pr_info("Address of device %X\n", client->addr);
    pr_info("%s---%d\n", __func__, __LINE__);
    return 0;
}
static int i2c_remove(struct i2c_client *client)
{
    pr_info("goodbye\n");
    pr_info("%s---%d\n", __func__, __LINE__);
    return 0;
}

static struct i2c_driver my_i2c_driver = {
    .driver = {
        .name = "my_i2c_driver",
        .of_match_table = i2c_of_id,
        .owner = THIS_MODULE,
    },
    .probe_new = i2c_probe_new,
    .remove = i2c_remove,
};

module_i2c_driver(my_i2c_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);