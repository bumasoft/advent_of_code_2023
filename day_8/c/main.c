/* Created by Marian Busoi, Dec 3rd, 2023,
 * Advent Of Code 2023, Day 3: https://adventofcode.com/2023/day/3
*/
#include "bumasoft/standard.h"
#include "aoc.h"

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 8, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));

    vector_t hands = vector_init();

    while (fgets(line, BUFFER_LENGTH, fp)) {

    }

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line);
}