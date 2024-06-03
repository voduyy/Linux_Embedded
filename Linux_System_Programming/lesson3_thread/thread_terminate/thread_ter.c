#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
pthread_t threadid1,threadid2;
typedef struct thread_arguments
{
    char name[30];
    char msg[30];
}thread_arg;
static void *thread_func(void *args)
{
    //printf("Hello, im thread 1\n");
    pthread_detach(pthread_self()); // waitpid() lien tuc
    pthread_exit(NULL);
}
static void *thread_func_2(void *args)
{
    pthread_t id=pthread_self(); // cho biet duoc thread_id;
    thread_arg *data = (thread_arg*) args;
    
       
    if(pthread_equal(id,threadid2))
    {
        printf("Im thread 2, my thread_id is %ld\n", threadid2);
        printf("My name is %s\n",data->name);
        printf("Message: %s\n",data->msg);
    }
    while(1)
    {
        printf("hi\n");
        sleep(1);
    }
    
}
int main() // dang co 3 thread bao gom (main, thread_func,thread_func_2)
{
    thread_arg thr;
    int ret;
    int count=0;
    strncpy(thr.name,"Vo Duy",sizeof(thr.name));
    strncpy(thr.msg,"Hello",sizeof(thr.msg));
    while(1)
    {
        if(pthread_create(&threadid1,NULL,&thread_func,NULL))
        {   
            printf("pthread_create got error \n");
        }
        count++;
        if(count%1000==0)
        {
            printf("Thread number %d\n",count);
        }
    }
    sleep(2);
    if(pthread_create(&threadid2,NULL,&thread_func_2,&thr))
    {   
        printf("pthread_create got error \n");
    }
    sleep(5);
    pthread_cancel(threadid2); // tuong tu nhu kill, se huy theo cach chu dong 
    pthread_join(threadid2,NULL); // tuong tu waitpid()
    printf("Thread id 2 got terminated\n");
    return 1;
}