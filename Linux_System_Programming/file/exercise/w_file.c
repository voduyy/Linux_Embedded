#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char*argv[])
{
    int fd = open("w_file.txt",O_RDWR|O_APPEND);
    if(fd<0)
    {
        printf("Open file failed\n");
    }
    else printf("Open file successfully\n");
    lseek(fd,0,SEEK_SET);
    write(fd,"\nHello Duy\n",strlen("\nHello Duy\n"));
    close(fd);
}