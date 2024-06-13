#include "hello.h"
#include "goodbye.h"
#include "new_name.h"
int main()
{
    printf("============================\n");
    hello();
    new_name();
    goodbye();
    printf("I'm calling at new_name.c\n");
}