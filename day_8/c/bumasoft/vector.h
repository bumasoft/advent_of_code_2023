//
// Created by Victor-Marian Busoi on 05.12.2023.
//

#ifndef BUMASOFT_VECTOR_H
#define BUMASOFT_VECTOR_H
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winitializer-overrides"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define VECTOR_DEFAULT_GROWTH_FACTOR 1.5
#define VECTOR_DEFAULT_CAPACITY 50

typedef enum {
    VECTOR_ITEM_CHAR = 0,
    VECTOR_ITEM_INT,
    VECTOR_ITEM_INT8,
    VECTOR_ITEM_INT16,
    VECTOR_ITEM_INT32,
    VECTOR_ITEM_INT64,
    VECTOR_ITEM_UINT8,
    VECTOR_ITEM_UINT16,
    VECTOR_ITEM_UINT32,
    VECTOR_ITEM_UINT64,
    VECTOR_ITEM_PTR
} vector_item_type_t;

typedef struct {
    bool is_empty;
    vector_item_type_t type;
    union {
        char _char;
        int _int;
        int8_t _int8;
        int16_t _int16;
        int32_t _int32;
        int64_t _int64;
        uint8_t _uint8;
        uint16_t _uint16;
        uint32_t _uint32;
        uint64_t _uint64;
        void *_ptr;
    };
} vector_item_t;

#define VEC_ITEMS (vector_item_t [])

#define VEC_CHAR(c) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_CHAR, ._char=(c)})
#define VEC_INT(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_INT, ._int=(num)})
#define VEC_I8(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_INT8, ._int8=(num)})
#define VEC_I16(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_INT16, ._int16=(num)})
#define VEC_I32(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_INT32, ._int32=(num)})
#define VEC_I64(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_INT64, ._int64=(num)})
#define VEC_U8(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_UINT8, ._uint8=(num)})
#define VEC_U16(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_UINT16, ._uint16=(num)})
#define VEC_U32(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_UINT32, ._uint32=(num)})
#define VEC_U64(num) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_UINT64, ._uint64=(num)})
#define VEC_ITEM_PTR(var) ((vector_item_t){.is_empty=false, .type=VECTOR_ITEM_PTR, ._ptr=(var)})

typedef struct vector_struct vector_t;

typedef vector_item_t (*VectorItemGet)(vector_t* vec, size_t i);
typedef vector_item_t (*VectorItemFirst)(vector_t* vec);
typedef vector_item_t (*VectorItemLast)(vector_t* vec);
typedef bool (*VectorItemSet)(vector_t* vec, size_t i, vector_item_t item);
typedef void (*VectorAppend)(vector_t* vec, vector_t extra);
typedef vector_item_t (*VectorItemPushString)(vector_t* vec, char* str);
typedef vector_item_t (*VectorItemPush)(vector_t* vec, vector_item_t item);
typedef vector_item_t (*VectorItemPop)(vector_t* vec);
typedef vector_t (*VectorToU64)(vector_t* vec);
typedef void (*VectorFree)(vector_t* vec);

struct vector_struct {
    size_t capacity;
    double growth_factor;
    size_t length;
    VectorItemFirst first;
    VectorItemLast last;
    VectorItemGet get;
    VectorItemSet set;
    VectorAppend append;
    VectorItemPushString push_string;
    VectorItemPush push;
    VectorItemPop pop;
    VectorToU64 to_u64;
    VectorFree free;
    vector_item_t* items;
};

#define vector_init(...) _vector_init((vector_t){.length=0,.capacity=VECTOR_DEFAULT_CAPACITY,.growth_factor=VECTOR_DEFAULT_GROWTH_FACTOR,.items=NULL, __VA_ARGS__})

#define vector_init_ptr(...) _vector_init_ptr((vector_t){.length=0,.capacity=VECTOR_DEFAULT_CAPACITY,.growth_factor=VECTOR_DEFAULT_GROWTH_FACTOR,.items=NULL, __VA_ARGS__})

vector_t _vector_init(vector_t vinit);
vector_t* _vector_init_ptr(vector_t vinit);
vector_item_t _vector_get(vector_t* vec, size_t i);
vector_item_t _vector_first(vector_t* vec);
vector_item_t _vector_last(vector_t* vec);
bool _vector_set(vector_t* vec, size_t i, vector_item_t);
void _vector_append(vector_t* vec, vector_t extra);
vector_item_t _vector_push_string(vector_t* vec, char* str);
vector_item_t _vector_push(vector_t* vec, vector_item_t item);
vector_item_t _vector_pop(vector_t* vec);
vector_t _vector_to_u64(vector_t* vec);

void _vector_free(vector_t *vec);

#endif //BUMASOFT_VECTOR_H
