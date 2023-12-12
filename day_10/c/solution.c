//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "solution.h"
#include "bumasoft/math.h"
#include <stdio.h>
#include <string.h>

uint64_t part_one_recurse(tile_t **maze, size_t row_count, size_t col_count, position_t start, uint64_t accumulator) {
    if (start.x < 0 || start.y < 0 || start.x >= col_count || start.y >= row_count)
        return 0;

    char this_pipe = maze[start.y][start.x].symbol;

    maze[start.y][start.x].dist = accumulator < maze[start.y][start.x].dist || maze[start.y][start.x].dist == 0 ? accumulator : maze[start.y][start.x].dist;
    
    uint64_t top = 0;
    uint64_t bottom = 0;
    uint64_t left = 0;
    uint64_t right = 0;
    
    if (start.y > 0 && !maze[start.y][start.x].status.top_checked) {
        maze[start.y][start.x].status.top_checked = 1;
        position_t next_pos = (position_t){start.x, start.y - 1};

        top =  (this_pipe == STARTING_POSITION ||
                this_pipe == VERTICAL_PIPE ||
                this_pipe == N_W_BEND ||
                this_pipe == N_E_BEND) ?
               part_one_recurse(maze, row_count, col_count,
                                next_pos,
                                accumulator + 1) : 0;
    }
    

    if (start.x > 0 && !maze[start.y][start.x].status.left_checked) {
        maze[start.y][start.x].status.left_checked = true;
        position_t next_pos = (position_t){start.x - 1, start.y};

        left =  (this_pipe == STARTING_POSITION ||
                 this_pipe == HORIZONTAL_PIPE ||
                 this_pipe == N_W_BEND ||
                 this_pipe == S_W_BEND) ?
                part_one_recurse(maze, row_count, col_count,
                                 next_pos,
                                 accumulator + 1) : 0;
    }

    if (start.x < col_count - 1 && !maze[start.y][start.x].status.right_checked) {
        maze[start.y][start.x].status.right_checked = 1;
        position_t next_pos = (position_t){start.x + 1, start.y};

        right = (this_pipe == STARTING_POSITION ||
                 this_pipe == HORIZONTAL_PIPE ||
                 this_pipe == N_E_BEND ||
                 this_pipe == S_E_BEND) ?
                part_one_recurse(maze, row_count, col_count,
                                 next_pos,
                                 accumulator + 1) : 0;
    }

    if (start.y < row_count - 1 && !maze[start.y][start.x].status.bottom_checked) {
        maze[start.y][start.x].status.bottom_checked = 1;
        printf("going down %zu %zu\n", start.y, start.x);
        position_t next_pos = (position_t){start.x, start.y + 1};

        bottom = (this_pipe == STARTING_POSITION ||
                  this_pipe == VERTICAL_PIPE ||
                  this_pipe == S_W_BEND ||
                  this_pipe == S_E_BEND) ?
                 part_one_recurse(maze, row_count, col_count,
                                  next_pos,
                                  accumulator + 1) : 0;
    }

    uint64_t result = max(5, accumulator, top, left, right, bottom);

   /* for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++)
            printf("%llu\t", counter[i*j + j]);
        puts("\n");
    }
    puts("****\n\n");*/

    return result;
}

void solve_part_one(tile_t **maze, size_t row_count, size_t col_count, position_t start, solution_t *solution) {
    solution->part_one = part_one_recurse(maze, row_count, col_count, start, 0);

    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++)
            printf("%u\t", maze[i][j].dist);
        puts("\n");
    }
}

void solve_part_two(tile_t **maze, size_t row_count, size_t col_count, position_t start, solution_t *solution) {

}