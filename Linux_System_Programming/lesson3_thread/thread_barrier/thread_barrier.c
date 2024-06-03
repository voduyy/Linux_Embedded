#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#define NUMBER_OF_THREAD 3
pthread_barrier_t barrier;

void *thread_func(void *arg)
{
    printf("waiting for threads\n");
    pthread_barrier_wait(&barrier);
    printf("Have enough threads\n");
}
int main()
{
    pthread_barrier_init(&barrier, NULL, NUMBER_OF_THREAD);
    pthread_t thr_id[2];
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&thr_id[i], NULL, thread_func, NULL);
    }
    pthread_barrier_wait(&barrier);
    printf("hello\n");
    // pthread_create(&thr_id[2], NULL, thread_func, NULL);
    for (int i = 0; i < 2; i++)
    {
        pthread_join(thr_id[i], NULL);
    }
    pthread_barrier_destroy(&barrier);
}