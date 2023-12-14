//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "solution.h"
#include "bumasoft/math.h"

void part_one_recurse(tile_t **maze, size_t row_count, size_t col_count, position_t start) {
    if (start.x > col_count - 1 || start.x < 0 || start.y < 0 || start.y > row_count - 1) return;

    char this_pipe = maze[start.y][start.x].symbol;

    for (uint8_t i = 0; i < NUM_DIRECTIONS; i++) {
        uint8_t status_mask = (1 << i);
        if (maze[start.y][start.x].status & status_mask) continue;

        maze[start.y][start.x].status |= status_mask; // turn on the flag for current direction
        position_t next_pos = (position_t) {start.x + NEXT_X(DIRECTIONS[i]), start.y + NEXT_Y(DIRECTIONS[i])};

        if (next_pos.x > col_count - 1 || next_pos.x < 0 || next_pos.y > row_count - 1 || next_pos.y < 0) continue;

        uint8_t mirror_mask = (1 << MIRROR_DIR(DIRECTIONS[i]));
        maze[next_pos.y][next_pos.x].status |= mirror_mask; // set opposite direction status flag

        if (CAN_GO(this_pipe, DIRECTIONS[i])) {
            uint32_t next_dist = maze[next_pos.y][next_pos.x].dist == 0 ? maze[start.y][start.x].dist + 1
                                                                        : (maze[next_pos.y][next_pos.x].dist < maze[start.y][start.x].dist + 1 ? maze[next_pos.y][next_pos.x].dist : maze[start.y][start.x].dist + 1) ;
            maze[next_pos.y][next_pos.x].dist = IS_START_OR_DIRT(maze[next_pos.y][next_pos.x].symbol) ? 0 : next_dist;

            part_one_recurse(maze, row_count, col_count, next_pos);
            maze[next_pos.y][next_pos.x].status ^= mirror_mask; // clear opposite direction status flag
        }
    }

}

void solve_part_one(tile_t **maze, size_t row_count, size_t col_count, position_t start, solution_t *solution) {
    part_one_recurse(maze, row_count, col_count, start);

    uint32_t max_dist = 0;

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