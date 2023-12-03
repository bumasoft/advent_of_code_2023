//
// Created by Victor-Marian Busoi on 03.12.2023.
//

#ifndef C_ADJACENT_H
#define C_ADJACENT_H
#include "ancillary.h"

#define IS_SYMBOL(expr) ((expr) && (expr) != '.' && ((expr) < '0' || (expr) > '9'))

bool cell_is_adjacent_to_symbol(char *line, char *prev_line, size_t i);

bool cell_is_adjacent_to_num_above(char *prev_line, size_t i);

/*
 * Greedily consumes a number at the specified location in the string.
 * If it finds a digit there, it goes to the left as long as more digits are found,
 * then moves right, constructing the number until it reaches a non-digit character.
 */
uint64_t number_at(char *line, int i);

#endif //C_ADJACENT_H
