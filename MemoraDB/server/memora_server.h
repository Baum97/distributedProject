#ifndef MEMORA_SERVER_H
#define MEMORA_SERVER_H

#include <stdint.h>

// Data structure representing a key-value pair in the in-memory data store
typedef struct {
    char *key;
    char *value;
} KeyValuePair;

/**
 * Initializes the in-memory data store.
 */
void init_data_store();

/**
 * Frees the memory allocated for the data store.
 */
void free_data_store();

/**
 * Creates a new record in the data store with the specified key and value.
 *
 * @param key The key for the new record.
 * @param value The value for the new record.
 * @return 0 on success, and non-zero on failure (e.g., if the key already exists).
 */
int create_record(const char *key, const char *value);

/**
 * Retrieves the value associated with the specified key in the data store.
 *
 * @param key The key for the record to be retrieved.
 * @return The value as a string, or NULL if the key is not found.
 */
char *read_record(const char *key);

/**
 * Updates the value associated with the specified key in the data store.
 *
 * @param key The key for the record to be updated.
 * @param value The new value for the record.
 * @return 0 on success, and non-zero on failure (e.g., if the key does not exist).
 */
int update_record(const char *key, const char *value);

/**
 * Deletes the record associated with the specified key from the data store.
 *
 * @param key The key for the record to be deleted.
 * @return 0 on success, and non-zero on failure (e.g., if the key does not exist).
 */
int delete_record(const char *key);

/**
 * Starts the server loop, listening for client socket connections on the specified port.
 *
 * @param port The port on which the server will listen for client connections.
 */
void run_server(uint16_t port);

/**
 * Starts the MemoraDB server.
 */
void start_server();

#endif // MEMORA_SERVER_H