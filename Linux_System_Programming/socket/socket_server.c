#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int socket_sd, new_socket_sd, port_no;
    char buffer[255];
    struct sockaddr_in server_addr, client_addr;
    if (argc < 2)
    {
        perror("Not enough arguments, missing ports");
        exit(0);
    }
    socket_sd = socket(AF_INET, SOCK_STREAM, 0);
    port_no = atoi(argv[1]);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);
    if (bind(socket_sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("wrong");
    }
    listen(socket_sd, 5);
    socklen_t new_len = sizeof(client_addr);
    printf("\nWaiting...");
    new_socket_sd = accept(socket_sd, (struct sockaddr *)&client_addr, (socklen_t *)&(new_len));
    int word, ch;
    FILE *file;
    file = fopen("new_file.txt", "a");

    read(new_socket_sd, &word, sizeof(int));

    while (ch != word)
    {
        read(new_socket_sd, buffer, 255);
        fprintf(file, "%s", buffer);
        ch++;
        if (feof(file))
        {
            break;
        }
    }
    fclose(file);
    // while (1)
    // {
    //     bzero(buffer, 255);
    //     printf("\nConnect successful");
    //     read(new_socket_sd, buffer, 255); // being block
    //     system("clear");
    //     printf("\nMessage from client %s", buffer);
    //     bzero(buffer, 255);
    //     printf("\nEnter message");
    //     fgets(buffer, 255, stdin);
    //     write(new_socket_sd, buffer, 255); // being block
    // }
    close(new_socket_sd);
    close(socket_sd);
}