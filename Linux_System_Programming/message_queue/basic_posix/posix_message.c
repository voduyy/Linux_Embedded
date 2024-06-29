#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    struct mq_attr attr;
    attr.mq_maxmsg = 100;
    mqd_t message_queue = mq_open("/message_queue", O_RDWR | O_CREAT | O_EXCL | O_NONBLOCK, 0666, attr);
    mq_close()
}