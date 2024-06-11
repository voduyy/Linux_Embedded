#include "socketutil.h"
#include "queue_socket.h"

pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
void *handle_connection(void *arg);
void *handle_thread(void *client_socket);
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i], NULL, handle_thread, NULL);
        pthread_detach(thread_pool[i]);
    }
    int socket_sd, client_socket_sd;
    struct sockaddr_in client_address;

    socket_sd = create_tcp_ipv4_socket();
    if (socket_sd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in *server_address = create_ipv4_address("", atoi(argv[1]));
    if (bind(socket_sd, (struct sockaddr *)server_address, sizeof(*server_address)) < 0)
    {
        perror("Bind failed");
        close(socket_sd);
        exit(EXIT_FAILURE);
    }

    if (listen(socket_sd, SERVER_BACKLOG) < 0)
    {
        perror("Listen failed");
        close(socket_sd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %s\n", argv[1]);

    while (1)
    {
        socklen_t length_client_addr = sizeof(client_address);
        client_socket_sd = accept(socket_sd, (struct sockaddr *)&client_address, &length_client_addr);
        if (client_socket_sd < 0)
        {
            perror("Accept failed");
            continue;
        }

        int *p = malloc(sizeof(int));
        if (p == NULL)
        {
            perror("Memory allocation failed");
            close(client_socket_sd);
            continue;
        }

        int *p_client = malloc(sizeof(int));
        *p_client = client_socket_sd;
        pthread_mutex_lock(&mutex);
        enqueue(p_client);
        pthread_cond_signal(&condition_var);
        pthread_mutex_unlock(&mutex);
        // Detach thread to avoid waiting for it to finish
    }
    close(socket_sd);
    return 0;
}
void *handle_thread(void *client_socket)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&condition_var, &mutex);
        int *p_client = dequeue();
        pthread_mutex_unlock(&mutex);
        if (p_client != NULL)
        {
            handle_connection(p_client);
        }
    }
}
void *handle_connection(void *arg)
{
    char write_buffer[1024];
    size_t bytes_read;
    char actual_path[PATH_MAX] = "/home/voduy/Workspace/lesson4_socket/socket_multithread_chat";
    int client_fd = *((int *)arg);

    free(arg); // Free the allocated memory for the argument

    // Initialize buffers
    memset(write_buffer, 0, sizeof(write_buffer));

    // Read data from the client
    ssize_t num_bytes = read(client_fd, write_buffer, sizeof(write_buffer) - 1);
    if (num_bytes < 0)
    {
        perror("Error reading from client");
        close(client_fd);
        return NULL;
    }

    write_buffer[num_bytes] = '\0'; // Null-terminate the read data

    printf("Client request: %s\n", write_buffer);

    strcat(actual_path, write_buffer); // get the path

    printf("Resolved path: %s\n", actual_path);

    // Open the file
    FILE *fp = fopen(actual_path, "r");
    if (fp == NULL)
    {
        perror("Cannot open file");
        close(client_fd);
        return NULL;
    }

    // Clear the buffer
    memset(write_buffer, 0, sizeof(write_buffer));

    // Read from the file and send to the client
    while ((bytes_read = fread(write_buffer, 1, sizeof(write_buffer), fp)) > 0)
    {
        printf("Read %zu bytes from file, sending to client...\n", bytes_read); // Debug statement

        // Write to the client
        ssize_t bytes_written = write(client_fd, write_buffer, bytes_read);
        if (bytes_written < 0)
        {
            perror("Error writing to client");
            fclose(fp);
            close(client_fd);
            return NULL;
        }

        printf("Sent %zd bytes to client\n", bytes_written); // Debug statement

        // Clear the buffer for the next read
        memset(write_buffer, 0, sizeof(write_buffer));
    }

    if (ferror(fp))
    {
        perror("Error reading from file");
    }

    // Close file and client connection
    fclose(fp);
    close(client_fd);

    return NULL;
}
