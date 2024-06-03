#include<stdio.h>
#include"hello.h"
void hi()
{
	printf("%s-%d,Hi\n",__func__,__LINE__);
}
