#include<stdio.h>
#include"hello.h"
void hello()
{
	printf("%s-%d, hello\n",__func__,__LINE__);
}

