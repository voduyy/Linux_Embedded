#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <mqueue.h>
#define SERVER_MESSAGE_QUEUE "/message_queue2"
#define CLIENT_PERMISSION 0666
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10
int main()
{
    char in_buffer[MSG_BUFFER_SIZE];
    char client_queue_name[MSG_BUFFER_SIZE];

    char temp_buffer[10];
    mqd_t client_mq;
    mqd_t server_mq = mq_open(SERVER_MESSAGE_QUEUE, O_WRONLY);

    sprintf(client_queue_name, "/client_%d", getpid());
    mq_unlink(client_queue_name);
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    client_mq = mq_open(client_queue_name, O_CREAT | O_EXCL | O_RDONLY, CLIENT_PERMISSION, &attr);
    printf("Ask for token: <Press Enter>\n");
    while (fgets(temp_buffer, 2, stdin))
    {
        mq_send(server_mq, client_queue_name, strlen(client_queue_name) + 1, 0);
        printf("Send message for server\n");
        mq_receive(client_mq, in_buffer, MSG_BUFFER_SIZE, NULL);
        printf("Token %s\n", in_buffer);
        printf("Ask for token: <Press Enter>\n");
    }
    mq_close(client_mq);
    mq_unlink(client_queue_name);
}