#include <string.h>
#include "ancillary.h"

/* Advent Of Code 2023, Day 1: https://adventofcode.com/2023/day/1 */

#define UNDEFINED_DIGIT 255
#define DEBUG_RESULT() printf("%s = %d\n", buffer, num)
#define UPDATE_DIGITS_P1(d) set_digits(&first_digit_p1, &last_digit_p1, d)
#define UPDATE_DIGITS_P2(d) set_digits(&first_digit_p2, &last_digit_p2, d)

static inline void set_digits(uint8_t* first_digit, uint8_t* last_digit, uint8_t value) {
    if (*first_digit == UNDEFINED_DIGIT) *first_digit = value;
    *last_digit = value;
}

typedef struct {
    uint64_t part_one;
    uint64_t part_two;
} solution_t;

void process_string(char* str, solution_t* solution) {
    uint8_t first_digit_p1 = UNDEFINED_DIGIT;
    uint8_t last_digit_p1 = UNDEFINED_DIGIT;

    uint8_t first_digit_p2 = UNDEFINED_DIGIT;
    uint8_t last_digit_p2 = UNDEFINED_DIGIT;

    for(; *str; str++) {
        if (*str < '0' || *str > '9') {
            // handle numbers spelled with letters
            switch (*str) {
                case 'o':
                    if (str_starts_with(str, "one"))
                        UPDATE_DIGITS_P2(1);
                    break;
                case 't':
                    if (str_starts_with(str, "two"))
                        UPDATE_DIGITS_P2(2);
                    else if (str_starts_with(str, "three"))
                        UPDATE_DIGITS_P2(3);
                    break;
                case 'f':
                    if (str_starts_with(str, "four"))
                        UPDATE_DIGITS_P2(4);
                    else if (str_starts_with(str, "five"))
                        UPDATE_DIGITS_P2(5);
                    break;
                case 's':
                    if (str_starts_with(str, "six"))
                        UPDATE_DIGITS_P2(6);
                    else if (str_starts_with(str, "seven"))
                        UPDATE_DIGITS_P2(7);
                    break;
                case 'e':
                    if (str_starts_with(str, "eight"))
                        UPDATE_DIGITS_P2(8);
                    break;
                case 'n':
                    if (str_starts_with(str, "nine"))
                        UPDATE_DIGITS_P2(9);
                    break;
                default: ;
            }

            continue;
        }

        UPDATE_DIGITS_P1(*str - '0');
        UPDATE_DIGITS_P2(*str - '0');
    }

    solution->part_one += (first_digit_p1 * 10 + last_digit_p1);
    solution->part_two += (first_digit_p2 * 10 + last_digit_p2);
}

int main(int argc, char** argv)    {
    puts("**** Advent of Code, Day 1, 2023 ****\n");

    if (argc < 2) {
        fputs("Error: Input file not specified.\n", stderr);
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* fp = open_file_from_args(argc, argv);

    char buffer[BUFFER_LENGTH];

    solution_t solution = {0, 0};

    while (fgets(buffer, BUFFER_LENGTH, fp)) process_string(buffer, &solution);

    printf("Part 1 answer: %llu\n", solution.part_one);
    printf("Part 2 answer: %llu\n", solution.part_two);

    fclose(fp);
}