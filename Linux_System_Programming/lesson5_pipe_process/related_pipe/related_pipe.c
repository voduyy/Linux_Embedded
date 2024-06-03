#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define WRITE_PIPE 1
#define READ_PIPE 0
char *msg1 = "Hello world 1\n";
char *msg2 = "Hello world 2\n";
char *msg3 = "Hello world 3\n";
int fds1[2], fds2[2];
char msg[25];
int main()
{
    int size_of_msg = strlen(msg1);
    if (pipe(fds1) < 0)
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
        write(fds1[WRITE_PIPE], msg1, strlen(msg1));
        write(fds1[WRITE_PIPE], msg2, strlen(msg2));
        write(fds1[WRITE_PIPE], msg3, strlen(msg3));
        sleep(2);
        write(fds1[WRITE_PIPE], msg3, strlen(msg));
        if (close(fds1[WRITE_PIPE]) < 0)
        {
            perror("Close write unsuccessful\n");
        }
    }
    else
    {
        printf("I am a parent process\n");
        if (close(fds1[WRITE_PIPE]) < 0)
        {
            perror("Close write unsuccessful\n");
        }
        while (1)
        {
            int num_bytes = read(fds1[READ_PIPE], msg, size_of_msg);
            if (num_bytes == -1)
            {
                perror("read wrong\n");
                exit(EXIT_FAILURE);
            }
            else if (num_bytes == 0)
            {
                printf("end of pipe %s\n", msg);
                memset(msg, 0, size_of_msg);
                break;
            }
            else
            {
                printf("Data: %s\n", msg);
                memset(msg, 0, size_of_msg);
            }
            sleep(3);
        }
    }
}