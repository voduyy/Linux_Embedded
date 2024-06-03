#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//#include<bits/sigset.h>
#include<signal.h>
void sig_int_func(int signum)
{
    printf("hello\n");
}
int main()
{
    sigset_t newset,oldset;
    signal(SIGINT,sig_int_func);
    sigemptyset(&newset);
    sigemptyset(&oldset);

    sigaddset(&newset,SIGINT);
    //printf("newset is %x\n",newset);
    if(sigprocmask(SIG_SETMASK,&newset,&oldset)==0)
    {
        if(sigismember(&newset,SIGINT))
        {
            printf("SIGINT exist\n");

        }
    }
    while(1);
}