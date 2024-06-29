#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main()
{
    char actual_path[4096] = "/home/voduy/Workspace/lesson4_socket/socket_multithread_chat/text/1.c";
    char buffer_2[1024];
    size_t byte_read;

    printf("%s", actual_path);
    FILE *fp = fopen(actual_path, "r");

    while (byte_read = fread(buffer_2, 1, 1024, fp) > 0)
    {
        printf("%s %ld", buffer_2, byte_read);
    }
    fclose(fp);
}