//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#ifndef README_MD_SOLUTION_H
#define README_MD_SOLUTION_H
#include "aoc.h"
#include "bumasoft/vector.h"

typedef enum {
    PART_ONE,
    PART_TWO
} part_t;

uint64_t extrapolate(vector_t* history, part_t part);
void solve_part_one(vector_t* histories, solution_t* solution);
void solve_part_two(vector_t* histories, solution_t* solution);
#endif //README_MD_SOLUTION_H
