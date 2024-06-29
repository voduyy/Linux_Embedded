#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define WRITE_PIPE 1
#define READ_PIPE 0

int fds1[2], fds2[2];
char msg1[25], msg2[25];
int main()
{
    int size_of_msg = strlen(msg1);
    if (pipe(fds1) < 0)
    {
        perror("Can't create pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(fds2) < 0)
    {
        perror("Can't create pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid_child = fork();
    if (!pid_child)
    {
        printf("I am child process\n");
        if (close(fds1[READ_PIPE]) < 0)
        {
            perror("Close read unsuccessful\n");
        }
        if (close(fds2[WRITE_PIPE]) < 0)
        {
            perror("Close write unsuccessful\n");
        }
        while (1)
        {
            printf("Child write message:\n");
            fgets(msg1, 25, stdin);
            fflush(stdin);
            write(fds1[WRITE_PIPE], msg1, 25);
            read(fds2[READ_PIPE], msg2, 25);
            printf("Message from parent: %s", msg2);
        }
    }
    else
    {
        printf("I am a parent process\n");
        if (close(fds1[WRITE_PIPE]) < 0)
        {
            perror("Close write unsuccessful\n");
        }
        if (close(fds2[READ_PIPE]) < 0)
        {
            perror("Close write unsuccessful\n");
        }
        while (1)
        {
            read(fds1[READ_PIPE], msg1, 25);
            printf("Message from parent: %s", msg1);
            printf("Parent write message:\n");
            fgets(msg2, 25, stdin);
            fflush(stdin);
            write(fds2[WRITE_PIPE], msg2, 25);
        }
    }
}