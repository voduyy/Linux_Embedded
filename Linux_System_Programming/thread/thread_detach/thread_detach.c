#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
pthread_attr_t detach_thread;
void *routine(void *arg)
{
    sleep(2);
    printf("Execution from thread\n");
}
int main()
{
    pthread_t thr_id[2];
    pthread_attr_init(&detach_thread);
    pthread_attr_setdetachstate(&detach_thread, PTHREAD_CREATE_DETACHED);
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&thr_id[i], &detach_thread, routine, NULL);
    }
    pthread_attr_destroy(&detach_thread);
    pthread_exit(0);
}