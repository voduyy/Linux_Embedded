#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char * argv[])
{
    pid_t pid_child;
    int a=0;
    printf("Gia tri khoi tao a: %d\n",a);
    pid_child = fork();
    if(pid_child==0)
    {
        printf("Toi la tien trinh con, pid la %d, pid cha la %d \n",getpid(),getppid());
        printf("Gia tri cua a:%d",++a);
    }
    else 
    {
        printf("Toi la tien trinh cha,pid la: %d\n",getpid());
        printf("Gia tri cua a:%d\n",++a);
    }
}