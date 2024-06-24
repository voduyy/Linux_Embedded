#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio_ext.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdlib.h>
#define PWM_STATE _IOW('a', '1', int32_t *)
#define GPIO_STATE _IOW('a', '0', int32_t *)
void menu(void)
{
    printf("=============================================\n");
    printf("======================MENU===================\n");
    printf("1. PWM \n");
    printf("2. GPIO \n");
    printf("0. Exit \n");
}
int main()
{
    int select, value;
    int fd = open("/dev/my_device", O_RDWR);
    while (1)
    {
        menu();
        printf(">>>");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("PWM STATE \n");
            ioctl(fd, PWM_STATE, &value);
            break;
        case 2:
            printf("GPIO STATE \n");
            ioctl(fd, GPIO_STATE, &value);
            break;
        case 0:
            printf("exit \n");
            exit(1);
            break;
        }
    }
    close(fd);
}