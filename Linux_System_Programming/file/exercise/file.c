#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<libgen.h>
#include <inttypes.h>
int main(int argc, char * argv[])
{
    char path_test[] ="/home/voduy/Workspace/Lesson1/exercise/test.txt";
    struct stat my_stat;
    int res=stat(path_test,&my_stat);
    if(res==-1)
    {
        printf("File does not exist\n");
    }
    else {

        printf("File does exist\n");
        char *dname=basename(path_test);
        printf("File name is: %s\n",dname);

    
    
        printf("File type: ");

        switch (my_stat.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           //case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           //case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
        printf("Last status change:   %s", ctime(&my_stat.st_mtime));
        printf("File size:%jd bytes\n",(intmax_t) my_stat.st_size);
    }
}