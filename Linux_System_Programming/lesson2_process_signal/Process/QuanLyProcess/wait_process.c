#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
    pid_t pid_child;
    int a=0,ret=0;
    int status;    
    printf("Value a is %d \n", a);
    pid_child = fork();
    if(!pid_child)
    {
        printf("Im a child process, my id is %d and my parent id is %d \n",getpid(), getppid());
        while(1);
        //sleep(2);
        //exit(0); // exit successfully
    }
    else 
    {
        ret = wait(&status);
        if(ret==-1)
        {
            printf("Wait unsuccessfully\n");
        }
        else 
        {
            printf("wait successful, im the parent process, my child pid is %d\n", ret);
        }
    }
    if(WIFEXITED(status))
    {
        printf("Process is terminated normally\n,status %d\n",WEXITSTATUS(status)); // exit(n) -> return n 
    }
    else if(WIFSIGNALED(status))
    {
        printf("Process is terminated abnormally and kill by %d\n",WTERMSIG(status));
    }
}