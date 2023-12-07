/* Created by Marian Busoi, Dec 3rd, 2023,
 * Advent Of Code 2023, Day 3: https://adventofcode.com/2023/day/3
*/
#include <string.h>
#include "aoc.h"
#include "solution.h"

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 4, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));

    fgets(line, BUFFER_LENGTH, fp);
    line = str_trim(line);

    if (!line || !str_starts_with(line, "seeds: ")) {
        fprintf(stderr, "Invalid input file.");
        exit(-1);
    }

    vector_t by_semi = str_split(line, ": ");
    char* seeds_str = str_trim( (char*) _vector_get(&by_semi, 1)._ptr );
    vector_t seeds = str_split(seeds_str, " ");
    seeds.to_u64(&seeds);

    solve(fp, &seeds, &solution);

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line);
    _vector_free(&seeds);
    _vector_free(&by_semi);
}
#pragma clang diagnostic pop