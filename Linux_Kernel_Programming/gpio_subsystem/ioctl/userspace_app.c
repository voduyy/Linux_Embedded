#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio_ext.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdlib.h>
#define LED_ON _IOW('a', '1', int32_t *)
#define LED_OFF _IOW('a', '0', int32_t *)
void menu(void)
{
    printf("=============================================\n");
    printf("======================MENU===================\n");
    printf("1. Turn on led \n");
    printf("2. Turn off led \n");
    printf("0. Exit \n");
}
int main()
{
    int select, value;
    int fd = open("/dev/my_device", O_RDWR);
    while (1)
    {
        menu();
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("Turn on led \n");
            ioctl(fd, LED_ON, &value);
            break;
        case 2:
            printf("Turn off led \n");
            ioctl(fd, LED_OFF, &value);
            break;
        case 0:
            printf("exit \n");
            exit(1);
            break;
        }
    }
    close(fd);
}