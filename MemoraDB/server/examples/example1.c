#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 5000
#define SERVER_IP "127.0.0.1"

int execute_command(int client_socket, const char *command) {
    ssize_t bytes_sent, bytes_received;
    char request[256], response[256];

    snprintf(request, sizeof(request), "%s", command);
    bytes_sent = send(client_socket, request, strlen(request), 0);

    if (bytes_sent == -1) {
        perror("Error sending command");
        return -1;
    } else if (bytes_sent != strlen(request)) {
        fprintf(stderr, "Incomplete send: Sent %zd bytes, expected %zu bytes\n", bytes_sent, strlen(request));
        return -1;
    } else {
        bytes_received = recv(client_socket, response, sizeof(response) - 1, 0);

        if (bytes_received == -1) {
            perror("Error receiving response");
            return -1;
        } else {
            response[bytes_received] = '\0'; // Add a null terminator to the received string
            printf("%s response: %s\n", command, response);
            return 0;
        }
    }
}


int main()
{
    int client_socket;
    struct sockaddr_in server_address;
    char input[512];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Failed to create client socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0)
    {
        perror("Invalid server IP address");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Failed to connect to server");
        exit(EXIT_FAILURE);
    }

    // Enter loop until user types "EXIT"
    while (1)
    {
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        // Call execute_command with the entered command
        execute_command(client_socket, input);
    }

    close(client_socket);
    return 0;
}
