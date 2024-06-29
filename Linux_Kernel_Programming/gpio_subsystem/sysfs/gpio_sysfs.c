#include "gpio_sysfs.h"
int32_t gpio_export(int32_t pin)
{
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (ERROR == fd)
    {
        fprintf(stderr, "open failed \n");
        exit(1);
    }
    memset(buffer, 0, byte_write);
    byte_write = snprintf(buffer, BUFFER_MAX, "%d", pin);
    if (ERROR == write(fd, buffer, byte_write))
    {
        fprintf(stderr, "write failed \n");
        close(fd);
        exit(1);
    }
    pin_used[count_pin].pin_num = pin;
    count_pin++;
    byte_write = 0;
    close(fd);
    return 0;
}
int32_t gpio_set_direction(int32_t pin, uint8_t direction_value)
{
    char direction_select[BUFFER_MAX];
    int index;
    if (ERROR == (index = search_gpio_array(pin)))
    {
        fprintf(stderr, "Don't find gpio\n");
        exit(1);
    }
    if (direction_value > 2 || direction_value < 0)
    {
        perror("Not correct value\n");
        exit(1);
    }
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    printf("Open path: %s\n", path);
    int fd = open(path, O_WRONLY);
    if (ERROR == fd)
    {
        fprintf(stderr, "open failed \n");
        close(fd);
        exit(1);
    }
    memset(buffer, 0, BUFFER_MAX);

    int length = (INPUT == direction_value ? (2) : (3));
    strncpy(direction_select, &direction[INPUT == direction_value ? 0 : 3], length);
    write(fd, direction_select, length);
    strncpy(pin_used[index].direction, direction_select, length);
    close(fd);
    return 0;
}
int32_t gpio_set_level(int32_t pin, uint8_t value)
{
    int index;
    if (ERROR == (index = search_gpio_array(pin)))
    {
        fprintf(stderr, "Don't find gpio\n");
        exit(1);
    }

    if (value > 2 || value < 0)
    {
        perror("Not correct value\n");
        exit(1);
    }
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "/sys/class/gpio/gpio%d/value", pin);
    printf("Open path: %s\n", path);
    int fd = open(path, O_WRONLY);
    if (ERROR == fd)
    {
        fprintf(stderr, "open failed \n");
        close(fd);
        exit(1);
    }
    memset(buffer, 0, BUFFER_MAX);
    sprintf(buffer, "%d", value);
    write(fd, buffer, 1);
    pin_used[index].level = value;
    close(fd);
    return 0;
}
int32_t gpio_unexport(int32_t pin)
{
    int index;
    if (ERROR == (index = search_gpio_array(pin)))
    {
        fprintf(stderr, "Don't find gpio\n");
        exit(1);
    }
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (ERROR == fd)
    {
        fprintf(stderr, "open failed \n");
        exit(1);
    }
    memset(buffer, 0, byte_write);
    byte_write = snprintf(buffer, BUFFER_MAX, "%d", pin);
    if (ERROR == write(fd, buffer, byte_write))
    {
        fprintf(stderr, "write failed \n");
        close(fd);
        exit(1);
    }
    format_array_gpio(index);
    byte_write = 0;
    close(fd);
    return 0;
}
void format_array_gpio(int pos)
{
    if (pos >= count_pin)
    {
        printf("Valid postion\n");
        return;
    }
    if (count_pin == 0)
    {
        printf("There is no pin\n");
    }
    for (int index = pos; index < count_pin - 1; index++)
    {
        pin_used[index].pin_num = pin_used[index + 1].pin_num;
        pin_used[index].level = pin_used[index + 1].level;
        strcpy(pin_used[index].direction, pin_used[index + 1].direction);
    }
    count_pin--;
}
int32_t search_gpio_array(int pin)
{
    for (int i = 0; i < count_pin; i++)
    {
        if (pin == pin_used[i].pin_num)
        {
            return i;
        }
    }
    return -1;
}
void end_gpio()
{
    printf("Off program\n");
    for (int i = 0; i < count_pin; i++)
    {
        gpio_set_level(pin_used[i].pin_num, LOW);
        gpio_unexport(pin_used[i].pin_num);
    }
    start_program = false;
}
bool print_all_pins()
{
    if (!count_pin)
    {
        printf("There is no pin being used\n");
        return false;
    }
    else
    {
        printf("Pin which being used is:\n");
        printf("\t");
        for (int i = 0; i < count_pin; i++)
        {
            printf("%d ", pin_used[i]);
        }
        printf("\n");
        return true;
    }
}
bool print_properties_pins()
{
    if (!count_pin)
    {
        printf("There is no pin being used\n");
        return false;
    }
    else
    {
        printf("All properties of pin being used \n");
        for (int i = 0; i < count_pin; i++)
        {
            printf("INDEX %d:\n", i);
            printf("Pin: %d\n", pin_used[i].pin_num);
            printf("Direction of pin %d: %s\n", pin_used[i].pin_num, pin_used[i].direction);
            printf("Level of pin %d: %d\n", pin_used[i].pin_num, pin_used[i].level);
            printf("=============================================\n");
        }
        return true;
    }
}
int menu()
{
    int select;
    printf("=============================================\n");
    printf("======================MENU===================\n");
    printf("1. Export pin \n");
    printf("2. Set direction pin \n");
    printf("3. Set level pin \n");
    printf("4. Unexport pin \n");
    printf("5. Show all properties pin used \n");
    printf("6. Exit\n");
    printf("=============================================\n");
    printf(">>>");
    scanf("%d", &select);
    return select;
}

int main()
{
    signal(SIGINT, end_gpio);
    int pin, direction, value;
    while (start_program)
    {

        switch (menu())
        {
        case 1:
            printf("Export pin:");
            scanf("%d", &pin);
            if (-1 == search_gpio_array(pin))
            {
                gpio_export(pin);
            }
            else
            {
                printf("This pin being used\n");
            }

            break;
        case 2:
            print_all_pins();
            printf("Choose pin:");
            scanf("%d", &pin);
            printf("Enter direction pin (in = 0 /out = 1):");
            scanf("%d", &direction);
            gpio_set_direction(pin, direction);
            break;
        case 3:
            print_all_pins();
            printf("Choose pin:");
            scanf("%d", &pin);
            printf("Enter value pin:");
            scanf("%d", &value);
            gpio_set_level(pin, value);
            break;
        case 4:
            if (print_all_pins())
            {
                printf("Choose pin:");
                scanf("%d", &pin);
                gpio_unexport(pin);
            }
            else
            {
                printf("\nThere is no pins to unexport \n");
            }
            break;
        case 5:
            print_properties_pins();
            break;
        case 6:
            printf("Exit\n");
            exit(1);
            break;
        }
    }
    return 0;
    /*Show all pin used and select*/
}