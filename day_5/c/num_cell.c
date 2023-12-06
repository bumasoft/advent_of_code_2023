//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "num_cell.h"

/*
 * Greedily consumes a number at the specified location in the string.
 * If it finds a digit there, it goes to the left as long as more digits are found,
 * then moves right, constructing the number until it reaches a non-digit character.
 */
uint64_t number_at(char** line) {
    uint64_t num = 0;

    *line = str_ltrim(*line);

    if (!*line) return num;

    while(IS_DIGIT(**line)) {
        num = num * 10 + TO_DIGIT(**line);
        (*line)++;
    }

    return num;
}