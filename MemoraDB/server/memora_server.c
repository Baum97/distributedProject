#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "memora_server.h"

KeyValuePair *data_store = NULL;
size_t data_store_size = 0;
//pthread_t thread_id;
//pthread_join(thread_id, NULL);

void init_data_store()
{
    data_store = NULL;
    data_store_size = 0;
}

void free_data_store()
{
    for (size_t i = 0; i < data_store_size; i++)
    {
        free(data_store[i].key);
        free(data_store[i].value);
    }
    free(data_store);
    data_store_size = 0;
}

int find_key(const char *key)
{
    for (size_t i = 0; i < data_store_size; i++)
    {
        if (strcmp(data_store[i].key, key) == 0)
        {
            return i;
        }
    }
    return -1;
}

int create_record(const char *key, const char *value)
{
    if (find_key(key) != -1)
    {
        return -1;
    }

    data_store = realloc(data_store, (data_store_size + 1) * sizeof(KeyValuePair));
    data_store[data_store_size].key = strdup(key);
    data_store[data_store_size].value = strdup(value);
    data_store_size++;
    return 0;
}

char *read_record(const char *key)
{
    int index = find_key(key);
    if (index == -1)
    {
        return NULL;
    }
    char *string = strdup(data_store[index].value);
    return *string;
}

int update_record(const char *key, const char *value)
{
    int index = find_key(key);

    if (index == -1)
    {
        return -1;
    }
    free(data_store[index].value);
    data_store[index].value = strdup(value);
    return 0;
}

int delete_record(const char *key)
{
    int index = find_key(key);
    if (index == -1)
    {
        return -1;
    }
    free(data_store[index].key);
    free(data_store[index].value);
    memmove(&data_store[index], &data_store[index + 1], (data_store_size - index - 1) * sizeof(KeyValuePair));
    data_store_size--;
    data_store = realloc(data_store, data_store_size * sizeof(KeyValuePair));
    return 0;
}

int handle_client(int client_socket)
{
    char request[512];
    ssize_t received = recv(client_socket, request, sizeof(request) - 1, 0);
    if (received <= 0)
    {
        perror("Failed to receive client request");
        return -1;
    }
    request[received] = '\0';

    char operation[16], key[256], value[256], response[512];

    int ret = sscanf(request, "%15s %255s %255s", operation, key, value);

    if (strcmp(operation, "EXIT") == 0)
    {
        return -1;
    }
    else if (strcmp(operation, "CREATE") == 0 && ret == 3)
    {
        if (create_record(key, value) == 0)
            snprintf(response, sizeof(response), "OK");
        else
            snprintf(response, sizeof(response), "ERROR: Key already exists");
    }
    else if (strcmp(operation, "READ") == 0 && ret == 2)
    {
        char *result = read_record(key);
        if (result != NULL)
            snprintf(response, sizeof(response), "OK %s", result);
        else
            snprintf(response, sizeof(response), "ERROR: Key not found");
    }
    else if (strcmp(operation, "UPDATE") == 0 && ret == 3)
    {
        if (update_record(key,value) == 0)
            snprintf(response, sizeof(response), "OK");
        else
            snprintf(response, sizeof(response), "ERROR: Key not found");
    }
    else if (strcmp(operation, "DELETE") == 0 && ret == 2)
    {
        if (delete_record(key) == 0)
            snprintf(response, sizeof(response), "OK");
        else
            snprintf(response, sizeof(response), "ERROR: Key not found");
    }
    else
    {
        snprintf(response, sizeof(response), "ERROR: Invalid command");
    }

    send(client_socket, response, strlen(response), 0);
    return 0;
}

void run_server(uint16_t port)
{
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;

    socklen_t client_address_length;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Failure to create server socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Failed to bind server socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0)
    {
        perror("Failed to listen on server socket");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d...\n");

    while (1)
    {
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
        if (client_socket < 0)
        {
            perror("Failed to accept client connection");
            continue;
        }

        while (1)
        {
            int result = handle_client(client_socket);

            if (result < 0)
            {
                break;
            }
        }
        close(client_socket);
    }
}

void start_server()
{
    uint16_t port = 5000;
    init_data_store();
    run_server(port);
    free_data_store();
}
