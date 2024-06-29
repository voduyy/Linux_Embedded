#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> // su dung SIGCHLD phai include
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#define LOW (0)
#define HIGH (1)

#define INPUT (0)
#define OUTPUT (1)

#define BUFFER_MAX (25)
#define PATH_MAX (50)

#define ERROR (-1)
#define QUANTITY_OF_GPIO 50
typedef struct gpio_data
{
    int pin_num;
    char direction[BUFFER_MAX];
    int level;
} mgpio_t;

mgpio_t pin_used[QUANTITY_OF_GPIO] = {0};
char direction[BUFFER_MAX] = "in\0out";
ssize_t byte_write = 0;
char buffer[BUFFER_MAX];
int count_pin = 0;
sig_atomic_t volatile start_program = true;

int32_t gpio_export(int32_t pin);
int32_t gpio_unexport(int32_t pin);
int32_t gpio_set_direction(int32_t pin, uint8_t direction);
int32_t gpio_set_level(int32_t pin, uint8_t value);
int32_t search_gpio_array(int pin);
bool print_all_pins();
bool print_properties_pins();
int menu();
void format_array_gpio(int pos);