//
// Created by Victor-Marian Busoi on 05.12.2023.
//

#ifndef BUMASOFT_STRING_H
#define BUMASOFT_STRING_H

#include "vector.h"
#include <stdbool.h>
#include <string.h>

#define IS_DIGIT(expr) ((expr) >= '0' && (expr) <= '9')
#define TO_DIGIT(expr) ((expr) - '0')
#define IS_CRLF(expr) ((expr) == '\n' || (expr) == '\r')
#define IS_WHITESPACE(expr) ((expr) == ' ' || (expr) == '\n' || (expr) == '\r')

bool str_starts_with(const char* str, const char* test);
char* str_ltrim(char* str);
char* str_rtrim(char* str);
char* str_trim(char* str);
vector_t str_split(char* str, char* delimiter);

#endif //BUMASOFT_STRING_H
