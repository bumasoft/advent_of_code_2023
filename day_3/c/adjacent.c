//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "adjacent.h"

bool is_adjacent_to_symbol(size_t i, char *line, char *prev_line) {
    if (IS_SYMBOL(line[i + 1]) || (i > 0 && IS_SYMBOL(line[i - 1]))) return true;
    if (!prev_line[i]) return false;

    return (IS_SYMBOL(prev_line[i]) || (i > 0 && IS_SYMBOL(prev_line[i - 1])) || IS_SYMBOL(prev_line[i + 1]));
}

bool is_adjacent_to_digits_above(size_t i, char *prev_line) {
    if (!prev_line[i]) return false;

    return (IS_DIGIT(prev_line[i]) || (i > 0 && IS_DIGIT(prev_line[i - 1])) || IS_DIGIT(prev_line[i + 1]));
}

/*
 * Greedily consumes a number at the specified location in the string.
 * If it finds a digit there, it goes to the left as long as more digits are found,
 * then moves right, constructing the number until it reaches a non-digit character.
 */
uint64_t num_at(char *line, int i) {
    uint64_t num = 0;

    if (i < 0 || !IS_DIGIT(line[i])) return num;

    for (; i > 0 && IS_DIGIT(line[i - 1]); i--);
    for (; IS_DIGIT(line[i]); i++) num = num * 10 + TO_DIGIT(line[i]);
    return num;
}