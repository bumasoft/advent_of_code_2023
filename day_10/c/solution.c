//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "solution.h"
#include "bumasoft/math.h"
#include <stdio.h>
#include <string.h>

void print_maze(tile_t** maze, size_t row_count, size_t col_count) {
    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            printf("%u\t", maze[i][j].dist);
        }
        puts("\n");
    }
    puts("---------------\n");
}

void part_one_recurse(tile_t **maze, size_t row_count, size_t col_count, position_t start) {
    char this_pipe = maze[start.y][start.x].symbol;

    if (start.y > 0 && maze[start.y][start.x].status.top_checked == 0) {
        maze[start.y][start.x].status.top_checked = 1;

        position_t next_pos = (position_t) {start.x, start.y - 1};

        maze[next_pos.y][next_pos.x].status.bottom_checked = 1;

        if (this_pipe == STARTING_POSITION ||
            this_pipe == VERTICAL_PIPE ||
            this_pipe == N_W_BEND ||
            this_pipe == N_E_BEND) {

            if (IS_START_OR_DIRT(maze[next_pos.y][next_pos.x].symbol)) {
                maze[next_pos.y][next_pos.x].dist = 0;
            } else {
                maze[next_pos.y][next_pos.x].dist = maze[next_pos.y][next_pos.x].dist == 0 ? maze[start.y][start.x].dist + 1 : min(2, maze[next_pos.y][next_pos.x].dist, maze[start.y][start.x].dist)+1;
            } /* else if (maze[next_pos.y][next_pos.x].dist == 0) {
                maze[next_pos.y][next_pos.x].dist = 1;
            } else {
                maze[next_pos.y][next_pos.x].dist = min(2, maze[start.y][start.x].dist + 1,
                                                         maze[next_pos.y][next_pos.x].dist);
            }*/

            //printf("At (%zu, %zu) and going up.\n\n", start.x, start.y);
            part_one_recurse(maze, row_count, col_count, next_pos);
            maze[next_pos.y][next_pos.x].status.bottom_checked = 0;
        }
    }

    // print_maze(maze, row_count, col_count);


    if (start.x > 0 && maze[start.y][start.x].status.left_checked == 0) {
        maze[start.y][start.x].status.left_checked = 1;

        position_t next_pos = (position_t) {start.x - 1, start.y};

        maze[next_pos.y][next_pos.x].status.right_checked = 1;

        if (this_pipe == STARTING_POSITION ||
            this_pipe == HORIZONTAL_PIPE ||
            this_pipe == N_W_BEND ||
            this_pipe == S_W_BEND) {

            if (IS_START_OR_DIRT(maze[next_pos.y][next_pos.x].symbol)) {
                maze[next_pos.y][next_pos.x].dist = 0;
            } else {
                maze[next_pos.y][next_pos.x].dist = maze[next_pos.y][next_pos.x].dist == 0 ? maze[start.y][start.x].dist + 1 : min(2, maze[next_pos.y][next_pos.x].dist, maze[start.y][start.x].dist)+1;
            }
            //printf("At (%zu, %zu) and going left.\n\n", start.x, start.y);

            part_one_recurse(maze, row_count, col_count, next_pos);
            maze[next_pos.y][next_pos.x].status.right_checked = 0;
        }
    }

    // print_maze(maze, row_count, col_count);

    if (start.x < col_count - 1 && maze[start.y][start.x].status.right_checked == 0) {
        maze[start.y][start.x].status.right_checked = 1;

        position_t next_pos = (position_t) {start.x + 1, start.y};
        maze[next_pos.y][next_pos.x].status.left_checked = 1;

        if (this_pipe == STARTING_POSITION ||
            this_pipe == HORIZONTAL_PIPE ||
            this_pipe == N_E_BEND ||
            this_pipe == S_E_BEND) {

            if (IS_START_OR_DIRT(maze[next_pos.y][next_pos.x].symbol)) {
                maze[next_pos.y][next_pos.x].dist = 0;
            } else {
                maze[next_pos.y][next_pos.x].dist = maze[next_pos.y][next_pos.x].dist == 0 ? maze[start.y][start.x].dist + 1 : min(2, maze[next_pos.y][next_pos.x].dist, maze[start.y][start.x].dist)+1;
            }
            //printf("At (%zu, %zu) and going right.\n\n", start.x, start.y);
            part_one_recurse(maze, row_count, col_count, next_pos);
            maze[next_pos.y][next_pos.x].status.left_checked = 0;
        }
    }

    // print_maze(maze, row_count, col_count);

    if (start.y < row_count - 1 && maze[start.y][start.x].status.bottom_checked == 0) {
        maze[start.y][start.x].status.bottom_checked = 1;

        position_t next_pos = (position_t) {start.x, start.y + 1};
        maze[next_pos.y][next_pos.x].status.top_checked = 1;

        if (this_pipe == STARTING_POSITION ||
            this_pipe == VERTICAL_PIPE ||
            this_pipe == S_W_BEND ||
            this_pipe == S_E_BEND) {
            /*maze[next_pos.y][next_pos.x].dist =
                    maze[next_pos.y][next_pos.x].dist == 0 && !IS_START_OR_DIRT(maze[next_pos.y][next_pos.x].symbol) ?
                    maze[start.y][start.x].dist + 1 : min(2, maze[start.y][start.x].dist + 1,
                                                          maze[next_pos.y][next_pos.x].dist);*/
            if (IS_START_OR_DIRT(maze[next_pos.y][next_pos.x].symbol)) {
                maze[next_pos.y][next_pos.x].dist = 0;
            } else {
                maze[next_pos.y][next_pos.x].dist = maze[next_pos.y][next_pos.x].dist == 0 ? maze[start.y][start.x].dist + 1 : min(2, maze[next_pos.y][next_pos.x].dist, maze[start.y][start.x].dist)+1;
            }
            //printf("At (%zu, %zu) and going down.\n\n", start.x, start.y);
            part_one_recurse(maze, row_count, col_count, next_pos);
            maze[next_pos.y][next_pos.x].status.top_checked = 0;
        }
    }

}

void solve_part_one(tile_t **maze, size_t row_count, size_t col_count, position_t start, solution_t *solution) {
    part_one_recurse(maze, row_count, col_count, start);

    uint32_t max_dist = 0;
    print_maze(maze, row_count, col_count);

    for (size_t i = 0; i < row_count; i++) {
        for (size_t j = 0; j < col_count; j++) {
            if (maze[i][j].dist > max_dist)
                max_dist = maze[i][j].dist;
        }
    }

    solution->part_one = max_dist;
}

void solve_part_two(tile_t **maze, size_t row_count, size_t col_count, position_t start, solution_t *solution) {

}