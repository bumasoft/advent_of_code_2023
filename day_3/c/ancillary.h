//
// Created by Victor-Marian Busoi on 03.12.2023.
//

#ifndef C_ANCILLARY_H
#define C_ANCILLARY_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 255
#define SMALL_BUFFER_LENGTH 32

#define IS_DIGIT(expr) ((expr) >= '0' && (expr) <= '9')
#define TO_DIGIT(expr) ((expr) - '0')
#define IS_CRLF(expr) ((expr) == '\n' || (expr) == '\r')
#define IS_WHITESPACE(expr) ((expr) == ' ' || (expr) == '\n' || (expr) == '\r')

#define PANIC(msg) fprintf(stderr, msg); \
                   exit(EXIT_FAILURE);

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

// Typical structure for an Advent of Code puzzle solution
typedef struct {
    uint64_t part_one_sum;
    uint64_t part_two_sum;
} solution_t;

// File IO
FILE* open_file_from_args(int argc, char** argv);

// String processing
bool str_starts_with(const char* str, const char* test);
char* str_trim(char* str);

#endif //C_ANCILLARY_H