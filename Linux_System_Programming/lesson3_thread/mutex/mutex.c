#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_t threadid1,threadid2;
int count=2;
static void *handler1(void *args)
{
   // pthread_mutex_lock(&lock1);
    printf("thread hanlder1 %d\n",++count);
    sleep(5);
   // pthread_mutex_unlock(&lock1);
    pthread_exit(NULL);
}
static void *handler2(void *args)
{
   // pthread_mutex_lock(&lock1);
    printf("thread hanlder2 %d\n",++count);
   // pthread_mutex_unlock(&lock1);
    pthread_exit(NULL);
} 
int main()
{
    if(pthread_create(&threadid1,NULL,&handler1,NULL))
    {
        printf("ERROR\n");
    }
    if(pthread_create(&threadid2,NULL,&handler2,NULL))
    {
        printf("ERROR\n");
    }
    pthread_join(threadid1,NULL);
    pthread_join(threadid2,NULL);
}