//
// Created by Victor-Marian Busoi on 05.12.2023.
//
#include "string.h"

bool str_starts_with(const char* str, const char* test) {
    for (; *str == *test && *test; str++, test++) ;

    return !*test;
}

char* str_ltrim(char* str) {
    if (str == NULL) return str;

    while(*str && CHAR_IS_WHITESPACE(*str)) str++;
    return str;
}

char* str_rtrim(char* str) {
    if (str == NULL) return NULL;

    char* head = str;

    do str++; while (*str);
    do str--; while(CHAR_IS_WHITESPACE(*str));

    *(str+1) = '\0';
    return head;
}

inline char* str_trim(char* str) {
    return str_rtrim(str_ltrim(str));
}

vector_t str_split(char* str, char* delimiter) {
    size_t delim_len = strlen(delimiter);
    vector_t vec = vector_init(.length = 0, .capacity = 25);

    char* pivot;
    while ((pivot = strstr(str, delimiter))) {
        char chunk[pivot - str + 1];
        memcpy(chunk, str, (pivot - str) * sizeof(char));
        chunk[pivot - str] = '\0';
        vec.push_string(&vec, chunk);

        str = pivot + delim_len;
    }

    vec.push_string(&vec, str);

    return vec;
}