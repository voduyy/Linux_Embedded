#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
    int socket_sd, port_no;
    char buffer[255];
    struct hostent *server;
    struct sockaddr_in serv_addr;
    // if (argc < 3)
    // {
    //     perror("Not enough arguments, missing ports");
    //     exit(0);
    // }
    // socket_sd = socket(AF_INET, SOCK_STREAM, 0);
    // port_no = atoi(argv[2]);
    // server = gethostbyname(argv[1]);
    // if (server == NULL)
    // {
    //     perror("no host");
    //     exit(1);
    // }
    // serv_addr.sin_family = AF_INET;
    // bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    // serv_addr.sin_port = htons(port_no);
    // if (connect(socket_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    // {
    //     exit(1);
    // }
    FILE *f;

    int word = 0;
    char c;
    f = fopen("hello.txt", "r");
    bzero(buffer, 255);
    while ((c = getc(f)) != EOF)
    {
        fscanf(f, "%s", buffer);
        if (isspace(c) || c == '\t')
            word++;
    }
    // write(socket_sd, &word, sizeof(word));
    rewind(f); // set con trỏ về vị trí bắt đầu
    char ch;
    while (ch != EOF)
    {
        fscanf(f, "%s", buffer);
        // write(socket_sd, buffer, 255);
        ch = fgetc(f);
        printf("%c", ch);
    }
    printf("%d", word);
    fclose(f);
    // while (1)
    // {
    //     bzero(buffer, 255);
    //     printf("\nPlease enter the message : ");
    //     fgets(buffer, 255, stdin);
    //     /* Gửi thông điệp tới server bằng hàm write */
    //     write(socket_sd, buffer, sizeof(buffer));
    //     bzero(buffer, 255);
    //     read(socket_sd, buffer, sizeof(buffer));
    //     printf("\nMessage from Server: %s\n", buffer);
    // }
    close(socket_sd);
}
