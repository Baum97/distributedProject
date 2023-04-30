#ifndef MEMORA_H
#define MEMORA_H

#include <stdint.h>

// Data structure representing a key-value pair in the in-memory data store
typedef struct {
    char *key;
    char *value;
} KeyValuePair;

/**
 * Establishes a connection to the MemoraDB server at the specified address and port.
 *
 * @param address The IP address or hostname of the MemoraDB server.
 * @param port The port number on which the MemoraDB server is listening.
 * @return A handle to the MemoraDB client connection, or NULL on failure.
 */
void* memora_connect(const char *address, uint16_t port);

/**
 * Closes the connection to the MemoraDB server.
 *
 * @param handle The handle to the MemoraDB client connection.
 * @return 0 on success, and non-zero on failure.
 */
int memora_close(void *handle);

/**
 * Creates a new record in the data store with the specified key and value.
 *
 * @param handle The handle to the MemoraDB client connection.
 * @param key The key for the new record.
 * @param value The value for the new record.
 * @return 0 on success, and non-zero on failure (e.g., if the key already exists).
 */
int memora_create(void *handle, const char *key, const char *value);

/**
 * Retrieves the value associated with the specified key in the data store.
 *
 * @param handle The handle to the MemoraDB client connection.
 * @param key The key for the record to be retrieved.
 * @return The value as a string, or NULL if the key is not found.
 */
char* memora_read(void *handle, const char *key);

/**
 * Updates the value associated with the specified key in the data store.
 *
 * @param handle The handle to the MemoraDB client connection.
 * @param key The key for the record to be updated.
 * @param value The new value for the record.
 * @return 0 on success, and non-zero on failure (e.g., if the key does not exist).
 */
int memora_update(void *handle, const char *key, const char *value);

/**
 * Deletes the record associated with the specified key from the data store.
 *
 * @param handle The handle to the MemoraDB client connection.
 * @param key The key for the record to be deleted.
 * @return 0 on success, and non-zero on failure (e.g., if the key does not exist).
 */
int memora_delete(void *handle, const char *key);

/**
 * Upserts the record in the data store with the specified key and value.
 * If the key does not exist, it creates a new record with the key and value.
 * If the key already exists, it updates the value for the existing record.
 *
 * @param handle The handle to the MemoraDB client connection.
 * @param key The key for the record to be upserted.
 * @param value The new value for the record.
 * @return 0 on success, and non-zero on failure.
 */
int memora_upsert(void *handle, const char *key, const char *value);

#endif // MEMORA_H
