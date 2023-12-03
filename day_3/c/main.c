/* Created by Marian Busoi, Dec 3rd, 2023,
 * Advent Of Code 2023, Day 3: https://adventofcode.com/2023/day/3
*/
#include <string.h>
#include "ancillary.h"
#include "part_one.h"
#include "part_two.h"

#define LINES_CAPACITY 1000
#define LINES_GROWTH_FACTOR 1.5

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 3, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    // For part one, we just do one pass, but for each line processed
    // we need access to the previous line as well.
    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));
    SAFE_CALLOC(char*, prev_line, BUFFER_LENGTH, sizeof(char));

    // Also declare a dynamic matrix to hold the entire line set,
    // to be used in part 2. This is just to make it easier, otherwise we would require
    // a 2-lines lookback (we'd need to be able to peek 2 lines back) in order to calculate gear ratios.
    uint32_t lines_capacity = LINES_CAPACITY;
    SAFE_CALLOC(char**, lines, lines_capacity, sizeof(char*));

    size_t line_len = 0;   // will hold the length of one line
    size_t line_count = 0; // will hold the total # of lines

    while (fgets(line, BUFFER_LENGTH, fp) && (line = str_trim(line))) {
        if (line_len == 0) line_len = strlen(line);

        size_t current_len = strlen(line);
        if (current_len != line_len) {
            PANIC("Faulty input data. All lines must have equal length.");
        }

        // append line to dynamic array, increasing capacity if necessary
        line_count++;

        if (line_count == lines_capacity) {
            // increase capacity
            lines_capacity *= LINES_GROWTH_FACTOR;
            lines = realloc(lines, lines_capacity);

            if (lines == NULL) throw_allocation_error();
        }
        // allocate memory for one line and set contents
        lines[line_count - 1] = calloc(line_len, sizeof(char));
        if (lines[line_count - 1] == NULL) throw_allocation_error();
        memcpy(lines[line_count - 1], line, line_len * sizeof(char));

        solve_part_one(line, line_len, prev_line, &solution);

        // update prev_line before moving on to next line
        for (size_t i = 0; i < line_len; i++) prev_line[i] = line[i];
    }

    solve_part_two(lines, line_count, line_len, &solution);

    printf("Part 1: %llu\n", solution.part_one_sum);
    printf("Part 2: %llu\n", solution.part_two_sum);

    // Cleanup:
    for (size_t i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);

    free(prev_line);
    free(line);

    fclose(fp);
}