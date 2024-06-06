#include <linux/module.h>
#include <linux/io.h>
#include "gpio.h"

#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESC "Hello kernel module"

uint32_t __iomem *gpio2_base_addr;

static int __init gpio_init(void)
{
    pr_info("Initializing GPIO module\n");

    gpio2_base_addr = ioremap(GPIO_START_ADDR, GPIO_SIZE);
    if (!gpio2_base_addr)
    {
        
        pr_err("Failed to map GPIO memory\n");

        return -ENOMEM;
    }
    pr_info("Mapped GPIO memory at address: %p\n", gpio2_base_addr);

    *(gpio2_base_addr + (GPIO_OE_OFFSET / 4)) &= ~GPIO2_0;
    *(gpio2_base_addr + (GPIO_SETDATAOUT_OFFSET / 4)) |= GPIO2_0;
    pr_info("On led\n");
    return 0;
}
static void __exit gpio_exit(void)
{
    *(gpio2_base_addr + (GPIO_CLEARDATAOUT_OFFSET / 4)) |= GPIO2_0;
    iounmap(gpio2_base_addr);
    pr_info("Off led \n");
}
module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");