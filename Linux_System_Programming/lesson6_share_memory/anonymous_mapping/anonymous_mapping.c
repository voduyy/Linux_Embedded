#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid = 0;
    char *data = (char *)mmap(0, 1, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // meu khong su dung bat ky file nao de mo thi co the su dung -1
    *data = 20;
    if ((child_pid = fork()) == 0)
    {
        printf("Im child process\n");
        printf("Increase shared data: %d\n", ++(*data));
        munmap(data, 1);
    }
    else
    {
        wait(NULL);
        printf("Im parent process\n");
        printf("Increase shared data: %d\n", ++(*data));
    }
}