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
#define CAN_GO_NORTH(pipe) ((pipe) == STARTING_POSITION || (pipe) == VERTICAL_PIPE || (pipe) == N_W_BEND || (pipe) == N_E_BEND)
#define CAN_GO_WEST(pipe) ((pipe) == STARTING_POSITION || (pipe) == HORIZONTAL_PIPE || (pipe) == N_W_BEND || (pipe) == S_W_BEND)
#define CAN_GO_EAST(pipe) ((pipe) == STARTING_POSITION || (pipe) == HORIZONTAL_PIPE || (pipe) == N_E_BEND || (pipe) == S_E_BEND)
#define CAN_GO_SOUTH(pipe) ((pipe) == STARTING_POSITION || (pipe) == VERTICAL_PIPE || (pipe) == S_W_BEND || (pipe) == S_E_BEND)

typedef enum {
    NORTH = 0,
    WEST,
    EAST,
    SOUTH
} directions_t;

#define NUM_DIRECTIONS 4
static const uint8_t DIRECTIONS[NUM_DIRECTIONS] = { NORTH, WEST, EAST, SOUTH};

#define MIRROR_DIR(dir) ((dir) == NORTH ? SOUTH : ((dir) == WEST ? EAST : ((dir) == SOUTH ? NORTH : WEST)))

#define CAN_GO(pipe, dir) (((dir) == NORTH && CAN_GO_NORTH(pipe)) || ((dir) == WEST && CAN_GO_WEST(pipe)) || \
                           ((dir) == EAST && CAN_GO_EAST(pipe)) || ((dir) == SOUTH && CAN_GO_SOUTH(pipe)))

#define NEXT_Y(dir) ((dir) == NORTH ? -1 : ((dir) == SOUTH ? 1 : 0))
#define NEXT_X(dir) ((dir) == WEST ? -1 : ((dir) == EAST ? 1 : 0))

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
    uint8_t status; // We will use  4 bits to flag each direction
} tile_t;

void part_one_recurse(tile_t** maze, size_t row_count, size_t col_count, position_t start);
void solve_part_one(tile_t** maze, size_t row_count, size_t col_count, position_t start, solution_t* solution);
void solve_part_two(tile_t** maze, size_t row_count, size_t col_count, position_t start, solution_t* solution);
#endif //README_MD_SOLUTION_H
