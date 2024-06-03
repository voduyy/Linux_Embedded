#include<stdio.h>
int main()
{
    printf("%s - %d,Im a proccess\n", __func__,__LINE__);
    while(1);
}