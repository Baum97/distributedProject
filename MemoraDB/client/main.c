#include <stdio.h>
#include "../lib/memora.h"

int main() {
    const char *server_address = "127.0.0.1";
    uint16_t port = 5000;

    // Connect to the MemoraDB server
    void *handle = NULL;
    int retries = 0;
    while (!handle && retries < 5) {
        handle = memora_connect(server_address, port);
        if (!handle) {
            retries++;
            fprintf(stderr, "Failed to connect to MemoraDB server at %s:%d (attempt %d)\n", server_address, port, retries);
            if (retries < 5) {
                // Wait for 6 seconds before retrying
                sleep(6);
            }
        }
    }

    if (!handle) {
        fprintf(stderr, "Failed to connect to MemoraDB server after 5 attempts\n");
        return 1;
    }

    // Test create operation
    if (memora_create(handle, "key1", "value1") == 0) {
        printf("Create: key1 => value1\n");
    } else {
        printf("Failed to create key1\n");
    }

    // Test read operation
    char *value = memora_read(handle, "key1");
    if (value) {
        printf("Read: key1 => %s\n", value);
    } else {
        printf("Failed to read key1\n");
    }

    // Test update operation
    if (memora_update(handle, "key1", "new_value1") == 0) {
        printf("Update: key1 => new_value1\n");
    } else {
        printf("Failed to update key1\n");
    }

    // Test upsert operation
    if (memora_upsert(handle, "key2", "value2") == 0) {
        printf("Upsert: key2 => value2\n");
    } else {
        printf("Failed to upsert key2\n");
    }

    // Test delete operation
    if (memora_delete(handle, "key1") == 0) {
        printf("Delete: key1\n");
    } else {
        printf("Failed to delete key1\n");
    }

    // Close the connection to the MemoraDB server
    if (memora_close(handle) == 0) {
        printf("Connection closed\n");
    } else {
        printf("Failed to close connection\n");
    }

    return 0;
}
