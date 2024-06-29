#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#define BIG 10000000UL
uint64_t count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *thread_func(void *arg)
{
    for (int i = 0; i < BIG; i++)
    {
        pthread_mutex_lock(&mutex);
        count += i;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t id1, id2;
    pthread_create(&id1, NULL, thread_func, NULL);
    pthread_create(&id2, NULL, thread_func, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("Value count: %ld\n", count);
    return 0;
}