#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
void func(int signum)
{
    printf("Im a func\n");
    wait(NULL);
}
int main()
{
    pid_t child_pid = fork();
    if(child_pid==0)
    {
        printf("Hello, im child, my pid is %d\n",getpid());
        while(1);
    }
    else
    {
        signal(SIGCHLD,func);
        printf("Hi\n");
        while(1);
    }
}
