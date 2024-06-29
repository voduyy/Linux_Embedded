#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <unistd.h>
struct sockaddr_in *create_ipv4_address(char *ip, int port)
{
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}
int create_tcp_ipv4_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}
int main()
{
    // printf("connect unsuccessful");
    int socket_sd = create_tcp_ipv4_socket();
    int res;
    /*
        By this way, ip is google.com, and port for http://google.com is 80
        And address will have family is AF_INET, port = 80, ip_address like below
    */
    struct sockaddr_in *address = create_ipv4_address("142.250.188.46", 80);
    /*
        Because function int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
        using const struct addr for second param, so we need to type casting for this struct type,
        And in order to can have size of address, we should use star to take value of address
    */
    if ((res = connect(socket_sd, (struct sockaddr *)address, sizeof(*address))) < 0)
    {
        printf("connect unsuccessful");
    }
    else
    {
        printf("connect successful");
    }
    char *message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n"; // message to get information of html
    /*
        important note:
            sizeof() can't note use at this function because it will return sizeof the pointer not the array,
            at this situation it return 4 or 8 value, so that server can't return value for client
    */
    if (send(socket_sd, message, strlen(message), 0) < 0)
    {
        printf("write error");
    }
    char buffer[1024];
    if (recv(socket_sd, buffer, sizeof(buffer), 0) < 0)
    {
        printf("write error");
    }
    printf("%s\n", buffer);
}
