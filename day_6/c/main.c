/* Created by Marian Busoi, Dec 3rd, 2023,
 * Advent Of Code 2023, Day 3: https://adventofcode.com/2023/day/3
*/
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 6, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    SAFE_CALLOC(char*, line1, BUFFER_LENGTH, sizeof(char));
    SAFE_CALLOC(char*, line2, BUFFER_LENGTH, sizeof(char));

    char time_tag[] = "Time:";
    char dist_tag[] = "Distance:";

    fgets(line1, BUFFER_LENGTH, fp);
    char* time_str = str_trim(line1);

    if (!time_str || !str_starts_with(time_str, time_tag)) {
        fprintf(stderr, "Invalid input file.");
        exit(EXIT_FAILURE);
    }

    fgets(line2, BUFFER_LENGTH, fp);
    char* dist_str = str_trim(line2);

    if (!dist_str || !str_starts_with(dist_str, dist_tag)) {
        fprintf(stderr, "Invalid input file.");
        exit(EXIT_FAILURE);
    }

    solve_part_one(time_str, dist_str, time_tag, dist_tag, &solution);
    solve_part_two(time_str, dist_str, &solution);

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line1);
    free(line2);
}