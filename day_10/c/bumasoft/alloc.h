//
// Created by Victor-Marian Busoi on 05.12.2023.
//

#ifndef BUMASOFT_ALLOC_H
#define BUMASOFT_ALLOC_H
#include <stdio.h>
#include <stdlib.h>

#define SAFE_MALLOC(type, var, count, elemsize) type var = malloc(count * elemsize); \
                                                if (var == NULL) throw_allocation_error();
#define SAFE_CALLOC(type, var, count, elemsize) type var = calloc(count, elemsize); \
                                           if (var == NULL) throw_allocation_error();
#define SAFE_REALLOC(type, new_var, old_var, count, elemsize) type new_var = realloc(old_var, count * elemsize); \
                                           if (new_var == NULL) throw_allocation_error();

inline static void throw_allocation_error() {
    fputs("Memory allocation issue.", stderr);
    exit(EXIT_FAILURE);
}
#endif //BUMASOFT_ALLOC_H
