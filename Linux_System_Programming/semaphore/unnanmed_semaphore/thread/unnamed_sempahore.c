#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <malloc.h>
sem_t semaphore;
void *routine(void *arg)
{
    sem_wait(&semaphore);
    sleep(1);
    int new_arg = *(int *)arg;
    free(arg);
    printf("hello from %d \n", new_arg);
    sem_post(&semaphore);
}
int main()
{
    pthread_t thr_id[4];
    pthread_attr_t detachThread;
    sem_init(&semaphore, 0, 1);
    pthread_attr_init(&detachThread);
    pthread_attr_setdetachstate(&detachThread, PTHREAD_CREATE_DETACHED);
    for (int i = 0; i < 4; i++)
    {
        int *index = malloc(sizeof(int));
        *index = i;
        pthread_create(&thr_id[i], &detachThread, &routine, index);
    }
    sem_destroy(&semaphore);
    pthread_attr_destroy(&detachThread);
    pthread_exit(0);
}