#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 25
char msg1[BUFFER_SIZE] = "Hello world 1\n";
char msg2[BUFFER_SIZE] = "Hello world 2\n";
char msg3[BUFFER_SIZE] = "Hello world 3\n";
int fds[2];
char msg_read[BUFFER_SIZE];
int main()
{
    if (pipe(fds) < 0)
    {
        perror("Can't create pipe");
        exit(EXIT_FAILURE);
    }
    write(fds[1], msg1, BUFFER_SIZE);
    write(fds[1], msg2, BUFFER_SIZE);
    write(fds[1], msg3, BUFFER_SIZE);
    sleep(1);

    for (int i = 0; i < 3; i++)
    {
        read(fds[0], msg_read, sizeof(msg_read));
        printf("msg read [%d]: %s", i, msg_read);
    }
    return 0;
}