#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    printf("Thuc hien lenh -lah sau 2s\n"); // -lah thuc ra bao gom 3 doi so: -l, -a, -h
    sleep(2); // sleep 2s 
    execl("/bin/ls", "ls" ,"-l","-a","-h",NULL); // boi vi -l,-a,-h la cac lenh khac nhau 
}