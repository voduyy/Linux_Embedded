#ifndef __LED_MODULE_H__
#define __LED_MODULE_H__

#define GPIO_START_ADDR 0x481AC000
#define GPIO_END_ADDR 0x481ACFFF
#define GPIO_SIZE (GPIO_END_ADDR - GPIO_START_ADDR)

#define GPIO_OE_OFFSET 0x134
#define GPIO_SETDATAOUT_OFFSET 0x194
#define GPIO_CLEARDATAOUT_OFFSET 0x190

#define GPIO1_3 (1 << 1)
#endif /* __LED_MODULE_H__ */