#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <malloc.h>
#define THREAD_NUM 8
pthread_barrier_t barrier, barrier_roll_dice;
int value_roll_dice[THREAD_NUM];
int status[THREAD_NUM] = {0};
void *roll_dice(void *arg)
{
    int index = *(int *)arg;
    value_roll_dice[index] = rand() % 6 + 1;
    pthread_barrier_wait(&barrier);
    pthread_barrier_wait(&barrier_roll_dice);
    if (status[index])
    {
        printf("(index: %d roll %d) I won\n", index, value_roll_dice[index]);
    }
    else
    {
        printf("(index: %d roll %d) I lose\n", index, value_roll_dice[index]);
    }
    free(arg);
}
int main()
{
    srand(time(NULL));
    int max = 0;
    pthread_barrier_init(&barrier, NULL, THREAD_NUM + 1);
    pthread_barrier_init(&barrier_roll_dice, NULL, THREAD_NUM + 1);
    pthread_t thr_id[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *p = malloc(sizeof(int));
        *p = i;
        pthread_create(&thr_id[i], NULL, &roll_dice, p);
    }
    pthread_barrier_wait(&barrier);
    for (int i = 0; i < THREAD_NUM; i++)
    {
        max = value_roll_dice[i] >= max ? value_roll_dice[i] : max;
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        status[i] = value_roll_dice[i] == max ? 1 : 0;
    }
    pthread_barrier_wait(&barrier_roll_dice);
    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(thr_id[i], NULL);
    }
    pthread_barrier_destroy(&barrier);
    pthread_barrier_destroy(&barrier_roll_dice);
}