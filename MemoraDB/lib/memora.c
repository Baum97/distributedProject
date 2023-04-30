#include "memora.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void* memora_connect(const char *address, uint16_t port) {
    // Create a socket for the client
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Failed to create client socket");
        return NULL;
    }

    // Configure the server address
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, address, &server_address.sin_addr) <= 0) {
        perror("Failed to convert address");
        close(client_socket);
        return NULL;
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to connect to the server");
        close(client_socket);
        return NULL;
    }

    // Return the client_socket as the handle
    return (void *)(intptr_t)client_socket;
}

int memora_close(void *handle) {
    // Cast the handle back to an int (client_socket)
    int client_socket = (int)(intptr_t)handle;

    // Close the client socket
    if (close(client_socket) < 0) {
        perror("Failed to close client socket");
        return -1;
    }

    return 0;
}

int memora_create(void *handle, const char *key, const char *value) {
    // Cast the handle back to an int (client_socket)
    int client_socket = (int)(intptr_t)handle;

    // Prepare the request string
    char request[512];
    snprintf(request, sizeof(request), "CREATE %s %s", key, value);

    // Send the request to the server
    if (send(client_socket, request, strlen(request), 0) < 0) {
        perror("Failed to send request");
        return -1;
    }

    // Receive the response from the server
    char response[512];
    ssize_t received = recv(client_socket, response, sizeof(response) - 1, 0);
    if (received <= 0) {
        perror("Failed to receive server response");
        return -1;
    }
    response[received] = '\0';

    // Check if the server response is "OK"
    if (strcmp(response, "OK") == 0) {
        return 0;
    } else {
        // If the response is not "OK", return an error code
        return -1;
    }
}

char* memora_read(void *handle, const char *key) {
    // Cast the handle back to an int (client_socket)
    int client_socket = (int)(intptr_t)handle;

    // Prepare the request string
    char request[512];
    snprintf(request, sizeof(request), "READ %s", key);

    // Send the request to the server
    if (send(client_socket, request, strlen(request), 0) < 0) {
        perror("Failed to send request");
        return NULL;
    }

    // Receive the response from the server
    char *response = (char *)malloc(512 * sizeof(char));
    ssize_t received = recv(client_socket, response, 511, 0);
    if (received <= 0) {
        perror("Failed to receive server response");
        free(response);
        return NULL;
    }
    response[received] = '\0';

    // Check if the server response starts with "OK"
    if (strncmp(response, "OK", 2) == 0) {
        // Extract the value from the response and return it
        char *value = (char *)malloc(256 * sizeof(char));
        sscanf(response + 3, "%255s", value);
        free(response);
        return value;
    } else {
        // If the response is not "OK", free the response buffer and return NULL
        free(response);
        return NULL;
    }
}

int memora_update(void *handle, const char *key, const char *value) {
    // Cast the handle back to an int (client_socket)
    int client_socket = (int)(intptr_t)handle;

    // Prepare the request string
    char request[512];
    snprintf(request, sizeof(request), "UPDATE %s %s", key, value);

    // Send the request to the server
    if (send(client_socket, request, strlen(request), 0) < 0) {
        perror("Failed to send request");
        return -1;
    }

    // Receive the response from the server
    char response[512];
    ssize_t received = recv(client_socket, response, sizeof(response) - 1, 0);
    if (received <= 0) {
        perror("Failed to receive server response");
        return -1;
    }
    response[received] = '\0';

    // Check if the server response is "OK"
    if (strcmp(response, "OK") == 0) {
        return 0;
    } else {
        // If the response is not "OK", return -1
        return -1;
    }
}

int memora_delete(void *handle, const char *key) {
    // Cast the handle back to an int (client_socket)
    int client_socket = (int)(intptr_t)handle;

    // Prepare the request string
    char request[512];
    snprintf(request, sizeof(request), "DELETE %s", key);

    // Send the request to the server
    if (send(client_socket, request, strlen(request), 0) < 0) {
        perror("Failed to send request");
        return -1;
    }

    // Receive the response from the server
    char response[512];
    ssize_t received = recv(client_socket, response, sizeof(response) - 1, 0);
    if (received <= 0) {
        perror("Failed to receive server response");
        return -1;
    }
    response[received] = '\0';

    // Check if the server response is "OK"
    if (strcmp(response, "OK") == 0) {
        return 0;
    } else {
        // If the response is not "OK", return -1
        return -1;
    }
}

int memora_upsert(void *handle, const char *key, const char *value) {
    // Cast the handle back to an int (client_socket)
    int client_socket = (int)(intptr_t)handle;

    // Prepare the request string
    char request[512];
    snprintf(request, sizeof(request), "UPSERT %s %s", key, value);

    // Send the request to the server
    if (send(client_socket, request, strlen(request), 0) < 0) {
        perror("Failed to send request");
        return -1;
    }

    // Receive the response from the server
    char response[512];
    ssize_t received = recv(client_socket, response, sizeof(response) - 1, 0);
    if (received <= 0) {
        perror("Failed to receive server response");
        return -1;
    }
    response[received] = '\0';

    // Check if the server response is "OK"
    if (strcmp(response, "OK") == 0) {
        return 0;
    } else {
        // If the response is not "OK", return -1
        return -1;
    }
}