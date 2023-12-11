/* Created by Marian Busoi, Dec 8th, 2023,
 * Advent Of Code 2023, Day 8: https://adventofcode.com/2023/day/8
*/
#include "bumasoft/standard.h"
#include "aoc.h"
#include "solution.h"

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 9, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    // line buffer
    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));

    vector_t histories = vector_init();

    while (fgets(line, BUFFER_LENGTH, fp)) {
        vector_t* history = str_split_by_whitespace(line);
        history->to_u64(history);

        histories.push(&histories, VEC_ITEM_PTR(history));
    }

    solve_part_one(&histories, &solution);
    solve_part_two(&histories, &solution);

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line);
}