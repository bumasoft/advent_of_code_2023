//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#ifndef README_MD_SOLUTION_H
#define README_MD_SOLUTION_H
#include "aoc.h"
#include <stdbool.h>
#include "bumasoft/alloc.h"

#define MAX_ROWS 500
#define IS_START_OR_DIRT(sym) ((sym) == 'S' || (sym == '.'))

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

typedef struct {
    char symbol;
    uint32_t dist;
    struct {
        unsigned int top_checked : 1;
        unsigned int bottom_checked : 1;
        unsigned int left_checked : 1;
        unsigned int right_checked : 1;
    } status;
} tile_t;

void print_maze(tile_t** maze, size_t row_count, size_t col_count);
void part_one_recurse(tile_t** maze, size_t row_count, size_t col_count, position_t start);
void solve_part_one(tile_t** maze, size_t row_count, size_t col_count, position_t start, solution_t* solution);
void solve_part_two(tile_t** maze, size_t row_count, size_t col_count, position_t start, solution_t* solution);
#endif //README_MD_SOLUTION_H
