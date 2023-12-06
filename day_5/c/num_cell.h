//
// Created by Victor-Marian Busoi on 03.12.2023.
//

#ifndef C_ADJACENT_H
#define C_ADJACENT_H
#include "bumasoft/standard.h"

/*
 * Greedily consumes a number at the specified location in the string.
 * If it finds a digit there, it goes to the left as long as more digits are found,
 * then moves right, constructing the number until it reaches a non-digit character.
 */
uint64_t number_at(char** line);

#endif //C_ADJACENT_H
