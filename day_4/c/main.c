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
    puts("**** Advent of Code, Day 4, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0, {0}, 0};

    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));

    while (fgets(line, BUFFER_LENGTH, fp) && (line = str_trim(line)))
        solve_part_one(line, &solution);

    solve_part_two(&solution);

    printf("Part 1: %llu\n", solution.part_one_sum);
    printf("Part 2: %llu\n", solution.part_two_sum);

    // Cleanup:
    free(line);

    fclose(fp);
}