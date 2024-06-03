#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if(child_pid==0)
    {
        printf("Child process respawn\n");
    }
    else
    {
        while(1);
    }
}