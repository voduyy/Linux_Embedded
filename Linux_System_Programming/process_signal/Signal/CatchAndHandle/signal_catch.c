#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h> // su dung SIGCHLD phai include 
#include<signal.h> // su dung SIGINT phai include  
int counter=0;
void Signal_Handler_1(int signum)
{
    printf("\nIm SIG: %d, count: %d",signum,++counter);
}
int main()
{
    signal(SIGINT,Signal_Handler_1);
    while(1)
    {
        sleep(1);
    }
}