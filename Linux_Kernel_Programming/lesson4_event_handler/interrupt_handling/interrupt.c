#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

#define DRIVER_AUTHOR "voduy"
#define DRIVER_DESC "interrupt button"
#define DRIVER_VERS "1.0"

#define GPIO_INTERRUPT 44
static unsigned int itr_number = 0;
static irqreturn_t irq_callback(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    pr_info("This is interrupt\n");
    return (irqreturn_t)IRQ_HANDLED;
}
static int __init gpio_interrupt_init(void)
{
    pr_info("Hello kernel\n");
    gpio_request(GPIO_INTERRUPT, "gpio_interrupt_44");
    gpio_direction_input(GPIO_INTERRUPT);

    itr_number = gpio_to_irq(GPIO_INTERRUPT);
    return request_irq(itr_number, (irq_handler_t)irq_callback, IRQF_TRIGGER_FALLING, "mygpio", NULL);
}

static void __exit gpio_interrupt_exit(void)
{
    free_irq(itr_number, NULL);
    gpio_free(GPIO_INTERRUPT);
}

module_init(gpio_interrupt_init);
module_exit(gpio_interrupt_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);