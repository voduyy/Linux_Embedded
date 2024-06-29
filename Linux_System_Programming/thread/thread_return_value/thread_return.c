#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<malloc.h>
pthread_t thread_id1;
void *handler_thread(void *args)
{
    int *iptr = (int*) malloc (sizeof(int));
    *iptr =5;
    return iptr;
}
int main(int argc, char *argv[])
{
    int *result;
    if(pthread_create(&thread_id1,NULL,&handler_thread,NULL))
    {
        perror("Error:\n");
    }
    pthread_join(thread_id1,(void*)&result);
    printf("%d",*result);

}