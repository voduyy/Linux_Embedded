#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
void func(int signum)
{
    printf("Im a function");
    wait(NULL);
}

int main()
{
    pid_t child_pid = fork();
    if(child_pid == 0)
    {
        printf("Im a child process, my pid is %d",getpid());
        while(1);
    }
    else 
    {
        signal(SIGCHLD,func); // bat ky khi nao co tin hieu cua SIGCHLD thi se goi ham func
        printf("Im a parent\n");
        while(1);
    }
}