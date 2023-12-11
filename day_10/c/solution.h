//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#ifndef README_MD_SOLUTION_H
#define README_MD_SOLUTION_H
#include "aoc.h"
#include "bumasoft/vector.h"

#define MAX_ROWS 500

typedef enum {
    VERTICAL_PIPE = '|',
    HORIZONTAL_PIPE = '-',
    N_E_BEND = 'L',
    N_W_BEND = 'J',
    S_W_BEND = '7',
    S_E_BEND = 'F',
    STARTING_POSITION = 'S'
} pipe_t;

typedef enum {
    PART_ONE,
    PART_TWO
} part_t;

typedef struct {
    size_t x;
    size_t y;
} position_t;

uint64_t part_one_recurse(char** maze, size_t row_count, size_t col_count, position_t start, uint64_t accumulator);
void solve_part_one(char** maze, size_t row_count, size_t col_count, position_t start, solution_t* solution);
void solve_part_two(char** maze, size_t row_count, size_t col_count, position_t start, solution_t* solution);
#endif //README_MD_SOLUTION_H
