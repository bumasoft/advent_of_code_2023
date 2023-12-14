/* Created by Marian Busoi, Dec 8th, 2023,
 * Advent Of Code 2023, Day 8: https://adventofcode.com/2023/day/8
*/
#include "bumasoft/standard.h"
#include "aoc.h"
#include "solution.h"

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 10, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));
    SAFE_CALLOC(tile_t**, maze, MAX_ROWS, sizeof(tile_t*));

    size_t row_count = 0;
    size_t col_count = 0;
    position_t start = {0, 0};

    size_t prev_cols = 0;

    while (fgets(line, BUFFER_LENGTH, fp)) {
        char* trimmed = str_trim(line);
        size_t len = strlen(trimmed);

        if (prev_cols > 0 && len != prev_cols) PANIC("Invalid data.");

        prev_cols = len;

        SAFE_CALLOC(, maze[row_count], len + 1, sizeof(tile_t));

        char* start_x;
        if ((start_x = strchr(trimmed, STARTING_POSITION)) != NULL)
            start = (position_t){ (start_x - trimmed), row_count };

        for (size_t i = 0; i < len; i++)
            maze[row_count][i] = (tile_t) { trimmed[i], 0, .status=0};

        row_count++;
    }

    col_count = prev_cols;

    solve_part_one(maze, row_count, col_count, start, &solution);
    solve_part_two(maze, row_count, col_count, start, &solution);

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line);

    for (size_t i = 0; i < row_count; i++) free(maze[i]);
    free(maze);
}