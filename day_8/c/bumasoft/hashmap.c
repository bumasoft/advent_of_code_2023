//
// Created by Victor-Marian Busoi on 09.12.2023.
//

#include <string.h>
#include "hashmap.h"
#include "alloc.h"

/*
 * Receives a string key and returns a bucket index.
 * Uses three chars from the string and apply the modulo method.
 */
size_t _hashmap_hash(char* key) {
    size_t index = 0;

    if (key == NULL) return index;

    size_t len = strlen(key);

    char start = key[0];
    char mid = key[len/2];
    char end = key[len-1];

    index = start * CHARSET_SIZE + mid;

    return (index * CHARSET_SIZE + end) % BUCKETS_COUNT;
}

void _hashmap_free(hashmap_t* map) {
    if (map == NULL) return;

    free(map);
}

hashmap_kv_pair_t* _hashmap_get(hashmap_t* map, char* key) {
    if (map == NULL) return NULL;

    size_t index = _hashmap_hash(key);

    if (index >= BUCKETS_COUNT) return NULL;

    hashmap_kv_pair_t* node = map->buckets[index];

    if (node == NULL) return NULL;

    while (node != NULL && strcmp(node->key, key) != 0)
        node = node->next;

    return node;
}

bool _hashmap_put(hashmap_t* map, char* key, void* value) {
    hashmap_kv_pair_t* node = _hashmap_get(map, key);

    // if key is already set, then exit
    if (node != NULL) return false;

    // else set the new key
    size_t index = _hashmap_hash(key);

    if (index >= BUCKETS_COUNT) return false; // something weird if this happens

    SAFE_MALLOC(, node, 1, sizeof(hashmap_kv_pair_t));
    SAFE_CALLOC(, node->key, strlen(key) + 1, sizeof(char));
    strcpy(node->key, key);
    // note value is not copied over, since we don't know what size & type it is
    node->value = value;
    node->next = NULL;

    hashmap_kv_pair_t* head = map->buckets[index];

    if (head == NULL) {
        map->buckets[index] = node;
        return true;
    }

    while (head->next != NULL) head = head->next;

    head->next = node;

    return true;
}

/*
 * Allocates a new hashmap on the heap.
 */
hashmap_t* _hashmap_init() {
    SAFE_MALLOC(hashmap_t*, new_hashmap, 1, sizeof(hashmap_t) + BUCKETS_COUNT * sizeof(hashmap_kv_pair_t*));

    new_hashmap->free = _hashmap_free;
    new_hashmap->get = _hashmap_get;
    new_hashmap->put = _hashmap_put;

    return new_hashmap;
}