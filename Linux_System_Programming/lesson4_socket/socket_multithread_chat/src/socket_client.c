#include "socketutil.h"
#include "queue_socket.h"
int main(int argc, char *argv[])
{
    int socket_sd;
    char buffer[1024];

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <ip server> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    socket_sd = create_tcp_ipv4_socket();
    if (socket_sd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in *address = create_ipv4_address(argv[1], atoi(argv[2]));
    if (connect(socket_sd, (struct sockaddr *)address, sizeof(*address)) < 0)
    {
        perror("Connect unsuccessful");
        close(socket_sd);
        exit(EXIT_FAILURE);
    }
    printf("Connect successful\n");

    while (1)
    {
        printf("Send message to server\n");
        const char *request = "/text/1.c";
        ssize_t bytes_sent = write(socket_sd, request, strlen(request));
        if (bytes_sent < 0)
        {
            perror("Error sending message to server");
            close(socket_sd);
            exit(EXIT_FAILURE);
        }

        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = read(socket_sd, buffer, sizeof(buffer) - 1); // Read up to the buffer size - 1
        if (bytes_received < 0)
        {
            perror("Error reading from server");
            close(socket_sd);
            exit(EXIT_FAILURE);
        }
        else if (bytes_received == 0)
        {
            printf("Server closed the connection\n");
            close(socket_sd);
            exit(EXIT_SUCCESS);
        }

        buffer[bytes_received] = '\0'; // Null-terminate the received data
        printf("Received: %s\n", buffer);

        sleep(5); // Sleep for 5 seconds for easier testing, adjust as necessary
    }

    close(socket_sd);
    return 0;
}
