
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#define SERVER_MESSAGE_QUEUE "/message_queue2"
#define SERVER_PERMISSION 0666
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10
int main()
{
    char in_buffer[MSG_BUFFER_SIZE];
    char out_buffer[MSG_BUFFER_SIZE];
    int token = 1;

    mq_unlink(SERVER_MESSAGE_QUEUE);

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t client_mq;
    mqd_t server_mq = mq_open(SERVER_MESSAGE_QUEUE, O_CREAT | O_RDONLY, SERVER_PERMISSION, &attr);
    printf("Open server \n");
    while (1)
    {
        ssize_t byte_read;
        if ((byte_read = mq_receive(server_mq, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1)
        {
            perror("Server: mq_receive");
            exit(1);
        }

        printf("Receive %ld bytes from client: %s \n", byte_read, in_buffer);

        if ((client_mq = mq_open(in_buffer, O_WRONLY)) == 1)
        {
            perror("Server: Not able to open client queue");
            continue;
        }
        printf("Connect client successful %s\n", in_buffer);
        sprintf(out_buffer, "%d", token);
        mq_send(client_mq, out_buffer, strlen(out_buffer) + 1, 0);
        printf("Send message to client\n");
        token++;
    }
    mq_close(server_mq);
    mq_unlink(SERVER_MESSAGE_QUEUE);
}