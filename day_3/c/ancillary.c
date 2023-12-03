//
// Created by Victor-Marian Busoi on 03.12.2023.
//

#include "ancillary.h"

FILE* open_file_from_args(int argc, char** argv) {
    if (argc < 2) {
        fputs("Error: Input file not specified.\n", stderr);
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(argv[1], "r");

    if (fp == NULL) {
        puts("Could not open file.");
        exit(EXIT_FAILURE);
    }

    return fp;
}

bool str_starts_with(const char* str, const char* test) {
    for (; *str == *test && *test; str++, test++) ;

    return !*test;
}

/*
 * Left trim a string, removing all whitespace (including CRLF).
 */
char* str_ltrim(char* str) {
    while(*str && IS_WHITESPACE(*str)) str++;
    if (!*str) return NULL;

    return str;
}

/*
 * Right trim a string, removing all whitespace (including CRLF).
 */
char* str_rtrim(char* str) {
    char* head = str;

    do str++; while (*str);
    for(; IS_WHITESPACE(*(str-1)); str--) ;
    *str = '\0';

    return head;
}

/*
 * Trim a string on both sides, removing all whitespace (including CRLF).
 */
char* str_trim(char* str) {
    if(!(str = str_ltrim(str))) return NULL;

    return str_rtrim(str);
}