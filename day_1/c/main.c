#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Advent Of Code 2023, Day 1: https://adventofcode.com/2023/day/1 */

#define BUFFER_LENGTH 255
#define DEBUG_RESULT() printf("%s = %d\n", buffer, num)
#define UPDATE_DIGITS(d) set_digits(&first_digit, &last_digit, d)

static inline void set_digits(uint8_t* first_digit, uint8_t* last_digit, uint8_t value) {
    if (*first_digit == 255) *first_digit = value;
    *last_digit = value;
}

bool starts_with(const char* str, const char* test) {
    for (; *str == *test && *test; str++, test++) ;

    return !*test && *str;
}

uint8_t num_from_string(char* str) {
    uint8_t first_digit = 255;
    uint8_t last_digit = 255;

    for(; *str; str++) {
        if (*str < '0' || *str > '9') {
            // handle numbers spelled with letters
            switch (*str) {
                case 'o':
                    if (starts_with(str, "one"))
                        UPDATE_DIGITS(1);
                    break;
                case 't':
                    if (starts_with(str, "two"))
                        UPDATE_DIGITS(2);
                    else if (starts_with(str, "three"))
                        UPDATE_DIGITS(3);
                    break;
                case 'f':
                    if (starts_with(str, "four"))
                        UPDATE_DIGITS(4);
                    else if (starts_with(str, "five"))
                        UPDATE_DIGITS(5);
                    break;
                case 's':
                    if (starts_with(str, "six"))
                        UPDATE_DIGITS(6);
                    else if (starts_with(str, "seven"))
                        UPDATE_DIGITS(7);
                    break;
                case 'e':
                    if (starts_with(str, "eight"))
                        UPDATE_DIGITS(8);
                    break;
                case 'n':
                    if (starts_with(str, "nine"))
                        UPDATE_DIGITS(9);
                    break;
                default: ;
            }

            continue;
        }

        if (first_digit == 255) first_digit = *str - '0';
        last_digit = *str - '0';
    }

    return first_digit * 10 + last_digit;
}

int main(int argc, char** argv)    {
    puts("**** Advent of Code, Day 1, 2023 ****\n");

    if (argc < 2) {
        fputs("Error: Input file not specified.\n", stderr);
        fputs("Usage: calib filename\n", stderr);
        exit(0);
    }

    FILE* fp = fopen(argv[1], "r");

    if (fp == NULL) {
        puts("Could not open file.");
        exit(0);
    }

    char buffer[BUFFER_LENGTH];

    uint64_t sum = 0;

    while (fgets(buffer, BUFFER_LENGTH, fp)) {
        uint8_t num = num_from_string(buffer);
        // DEBUG_RESULT();
        sum += num;
    }

    printf("\nSum of all the calibration values: %llu", sum);

    fclose(fp);
    return 0;
}