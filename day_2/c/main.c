/* Created by Marian Busoi, Dec 2nd, 2023,
 * Advent Of Code 2023, Day 2: https://adventofcode.com/2023/day/2
*/
#include "ancillary.h"
#include "game.h"

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 2, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    char game[BUFFER_LENGTH];

    solution_t solution = {0, 0};

    while (fgets(game, BUFFER_LENGTH, fp)) solve_game(game, &solution);

    printf("Part 1. Sum of Ids: %llu\n", solution.part_one_sum);
    printf("Part 2. Sum of Powers of Minimum Set of Cubes: %llu\n", solution.part_two_sum);

    fclose(fp);
}