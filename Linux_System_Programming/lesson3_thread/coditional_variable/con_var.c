#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t threadid1,threadid2;
int count=0;
static void *handler1(void *args)
{
    
    while(1)
    {
        pthread_mutex_lock(&lock1);
        while(count<5)
        {
            count++;
            printf("Count %d\n",count);
            sleep(1);
        }
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock1);
    }
  
    pthread_exit(NULL);
}
/*static void *handler2(void *args)
{
    pthread_mutex_lock(&lock1);
    printf("thread hanlder2 %d\n",++count);
    pthread_mutex_unlock(&lock1);
    pthread_exit(NULL);
} */
int main()
{
    if(pthread_create(&threadid1,NULL,&handler1,NULL))
    {
        printf("ERROR\n");
    }
 /*   if(pthread_create(&threadid2,NULL,&handler2,NULL))
    {
        printf("ERROR\n");
    } */
    pthread_mutex_lock(&lock1);
    while(1)
    {
        pthread_cond_wait(&cond,&lock1); // giong wait
        if(count==5)
        { 
            printf("Count is equal 5\n");
            count=0;
       }
       
    }
    pthread_mutex_unlock(&lock1); // tranh truong hop cpu phai lam qua nhieu, viec nay giup cpu ranh 
    
    pthread_join(threadid1,NULL);
   // pthread_join(threadid2,NULL);
}