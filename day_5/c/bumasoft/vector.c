//
// Created by Victor-Marian Busoi on 05.12.2023.
//
#include "vector.h"
#include "alloc.h"
#include <string.h>

vector_item_t _vector_get(vector_t* vec, size_t i) {
    if (vec == NULL || vec->length <= i || vec->items == NULL) 
        return (vector_item_t){.is_empty = true};

    return vec->items[i];
}

bool _vector_set(vector_t *vec, size_t i, vector_item_t item) {
    if (vec == NULL || i >= vec->length) return false;

    size_t size = sizeof(vector_item_t);

    return memcpy(&vec->items[i], &item, size);
}

vector_item_t _vector_push(vector_t* vec, vector_item_t item) {
    if (item.is_empty) return item;

    size_t size = sizeof(vector_item_t);

    if (vec->length == 0) {
        SAFE_CALLOC(, vec->items, vec->capacity, size);
    }

    if (vec->length == vec->capacity) {
        vec->capacity *= vec->growth_factor;

        SAFE_REALLOC(, vec->items, vec->items, vec->capacity, size);
    }

    void* result = memcpy(&vec->items[vec->length], &item, size);

    if (result == NULL) return (vector_item_t){.is_empty=true};

    vec->length++;

    return item;
}

vector_item_t _vector_push_string(vector_t* vec, char* str) {
    vector_item_t item = {.is_empty = true, ._ptr= NULL, .type = VECTOR_ITEM_PTR};

    if (str == NULL) return item;

    item.is_empty = false;

    size_t string_len = strlen(str);
    SAFE_CALLOC(, item._ptr, string_len, sizeof(char));
    memcpy(item._ptr, str, sizeof(char) * string_len);

    return _vector_push(vec, item);
}

vector_item_t _vector_pop(vector_t* vec) {
    if (vec->length == 0)
        return (vector_item_t){.is_empty = true};

    vector_item_t item = _vector_get(vec, vec->length - 1 );
    vec->length--;

    if (vec->length == 0) _vector_free(vec);

    return item;
}

vector_t _vector_init(vector_t vinit) {
    void* items;
    size_t item_size = sizeof(vector_item_t);

    if (vinit.items == NULL) vinit.length = 0;

    if (vinit.length > 0) {
        SAFE_CALLOC(, items, vinit.length, item_size);

        memcpy(items, vinit.items, item_size * vinit.length);
    }
    else items = NULL;

    vector_t vec = {
            .length = vinit.length,
            .growth_factor = vinit.growth_factor > 0 ? vinit.growth_factor : VECTOR_DEFAULT_GROWTH_FACTOR,
            .capacity = vinit.capacity > 0 ? vinit.capacity : VECTOR_DEFAULT_CAPACITY,
            .items = items,
            .get = (vector_item_t (*)(void* vec, size_t i)) _vector_get,
            .set = (bool (*)(void* vec, size_t i, vector_item_t item)) _vector_set,
            .push_string = (vector_item_t (*)(void* vec, char* str)) _vector_push_string,
            .push = (vector_item_t (*)(void* vec, vector_item_t item)) _vector_push,
            .pop = (vector_item_t (*)(void* vec)) _vector_pop,
            .to_u64 = (vector_t (*)(void* vec)) _vector_to_u64,
            .free = (void (*)(void* vec)) _vector_free,
    };

    return vec;
}

vector_t _vector_to_u64(vector_t *vec) {
    if (vec == NULL || vec->length == 0) return *vec;

    for (size_t i = 0; i < vec->length; i++)
        vec->set(vec, i, VEC_U64(atoll( (char*) vec->get(vec, i)._ptr )));

    return *vec;
}

/*
 * Frees all memory allocated for items and clears vector.
 */
void _vector_free(vector_t *vec) {
    if (vec == NULL) return;

    free(vec->items);

    vec->length = 0;
    vec->capacity = VECTOR_DEFAULT_CAPACITY;
    vec->growth_factor = VECTOR_DEFAULT_GROWTH_FACTOR;
}