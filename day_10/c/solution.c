//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "solution.h"
#include "bumasoft/math.h"
#include <stdio.h>
#include <string.h>

uint64_t part_one_recurse(char **maze, size_t row_count, size_t col_count, position_t start, uint64_t accumulator) {
    if (start.x < 0 || start.y < 0 || start.x >= col_count || start.y >= row_count)
        return 0;

    char this_pipe = maze[start.y][start.x];

    maze[start.y][start.x] = '.';
    
    uint64_t top = 0;
    uint64_t bottom = 0;
    uint64_t left = 0;
    uint64_t right = 0;
    
    if (start.y > 0 && maze[start.y - 1][start.x] != '.') {
        top =  (this_pipe == STARTING_POSITION ||
                this_pipe == VERTICAL_PIPE ||
                this_pipe == N_W_BEND ||
                this_pipe == N_E_BEND) ?
               part_one_recurse(maze, row_count, col_count,
                                (position_t) {start.x, start.y - 1},
                                accumulator + 1) : 0;
    }
    

    if (start.x > 0 && maze[start.y][start.x - 1] != '.') {
        left =  (this_pipe == STARTING_POSITION ||
                 this_pipe == HORIZONTAL_PIPE ||
                 this_pipe == N_W_BEND ||
                 this_pipe == S_W_BEND) ?
                part_one_recurse(maze, row_count, col_count,
                                 (position_t) {start.x - 1, start.y},
                                 accumulator + 1) : 0;
    }

    if (start.x < col_count - 1 && maze[start.y][start.x + 1] != '.') {
        right = (this_pipe == STARTING_POSITION ||
                 this_pipe == HORIZONTAL_PIPE ||
                 this_pipe == N_E_BEND ||
                 this_pipe == S_E_BEND) ?
                part_one_recurse(maze, row_count, col_count,
                                 (position_t) {start.x + 1, start.y},
                                 accumulator + 1) : 0;
    }

    if (start.y < row_count - 1 && maze[start.y + 1][start.x] != '.') {
        bottom = start.y < row_count - 1 && maze[start.y + 1][start.x] != '.' &&
                 (this_pipe == STARTING_POSITION ||
                  this_pipe == VERTICAL_PIPE ||
                  this_pipe == S_W_BEND ||
                  this_pipe == S_E_BEND) ?
                 part_one_recurse(maze, row_count, col_count,
                                  (position_t) {start.x, start.y + 1},
                                  accumulator + 1) : 0;
    }

    return max(5, accumulator, top, left, right, bottom);
}

void solve_part_one(char **maze, size_t row_count, size_t col_count, position_t start, solution_t *solution) {
    solution->part_one = part_one_recurse(maze, row_count, col_count, start, 0);
}

void solve_part_two(char **maze, size_t row_count, size_t col_count, position_t start, solution_t *solution) {

}