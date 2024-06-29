#include<stdio.h>
int main(int argc, char * argv[]) //argc: argument count, argv: argument vector
{
    printf("Have a %d argument\n",argc);
    for (int i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
    printf("\n");
}