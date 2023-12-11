//
// Created by Victor-Marian Busoi on 09.12.2023.
//

#ifndef README_MD_HASHMAP_H
#define README_MD_HASHMAP_H

#include <stdbool.h>
#include <stddef.h>

#define BUCKETS_COUNT 2500
#define CHARSET_SIZE 255

typedef struct hashmap_node_struct {
    char* key;
    void* value;
    struct hashmap_node_struct* next;
} hashmap_kv_pair_t;

typedef struct hashmap_struct hashmap_t;

typedef hashmap_kv_pair_t* (*HashmapFuncGet)(hashmap_t* map, char* key);
hashmap_kv_pair_t* _hashmap_get(hashmap_t* map, char* key);

typedef bool (*HashmapFuncPut)(hashmap_t* map, char* key, void* value);
bool _hashmap_put(hashmap_t* map, char* key, void* value);

typedef bool (*HashmapFuncUpdate)(hashmap_t* map, char* key, void* value);
bool _hashmap_update(hashmap_t* map, char* key, void* value);

typedef bool (*HashmapFuncDel)(hashmap_t* map, char* key);
bool _hashmap_del(hashmap_t* map, char* key);

typedef void (*HashmapFuncFree)(hashmap_t* map);
void _hashmap_free(hashmap_t* map);

struct hashmap_struct {
    HashmapFuncGet get;
    HashmapFuncPut put;
    HashmapFuncUpdate update;
    HashmapFuncDel del;
    HashmapFuncFree free;
    hashmap_kv_pair_t* buckets[];
};

size_t _hashmap_hash(char* key);
hashmap_t* _hashmap_init();

#endif //README_MD_HASHMAP_H
