//
// Created by Victor-Marian Busoi on 05.12.2023.
//

#ifndef BUMASOFT_STRING_H
#define BUMASOFT_STRING_H

#include "vector.h"
#include <stdbool.h>
#include <string.h>

#define CHAR_IS_DIGIT(expr) ((expr) >= '0' && (expr) <= '9')
#define CHAR_TO_DIGIT(expr) ((expr) - '0')
#define CHAR_IS_CRLF(expr) ((expr) == '\n' || (expr) == '\r')
#define CHAR_IS_WHITESPACE(expr) ((expr) == ' ' || (expr) == '\n' || (expr) == '\r')

/* Checks if a string starts with a substring. */
bool str_starts_with(const char* str, const char* test);

/* Left trim a string, removing all whitespace (including CRLF). */
char* str_ltrim(char* str);

/* Right trim a string, removing all whitespace (including CRLF). */
char* str_rtrim(char* str);

/* Trim a string on both sides, removing all whitespace (including CRLF). */
char* str_trim(char* str);

/* Splits a string on a delimiter and returns a vector of component strings. */
vector_t str_split(char* str, char* delimiter);

#endif //BUMASOFT_STRING_H
