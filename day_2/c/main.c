/* Created by Marian Busoi, Dec 2nd, 2023,
 * Advent Of Code 2023, Day 2: https://adventofcode.com/2023/day/2
*/
#include <string.h>
#include "ancillary.h"
#include "cubes.h"
#include "draw.h"

typedef struct {
    uint64_t part_one_sum;
    uint64_t part_two_sum;
} solution_t;

/*
 * Computes the product of all elements in an array.
 */
static uint64_t array_product(const uint8_t array[NUM_COLORS]) {
    uint64_t prod = 1;

    for (size_t i = 0; i < NUM_COLORS; i++) prod *= array[i];

    return prod;
}

/*
 * Adds the Game Id to the sum for part 1 if the game is possible.
 * Computes the minimum amount of cubes of each color that would have been required
 * for the game to be possible and calculates the power of this minimum set of cubes,
 * as defined by the requirements. Adds this result to the sum for part 2.
 */
static void solve_game(char game[], solution_t *solution) {
    if (!str_starts_with(game, "Game")) return;

    char *semicolon = strstr(game, ":");
    if (semicolon == NULL) return;

    char *draws = semicolon + 1;

    uint8_t game_id = 0;

    // Point to first char before semicolon, then compute game id
    semicolon--;
    for (uint16_t pow = 10; semicolon != game && IS_DIGIT(*semicolon); semicolon--, pow *= 10)
        game_id += (TO_DIGIT(*semicolon) * pow / 10);

    if (!game_id) return;

    bool possible = true;

    uint8_t max_colors[NUM_COLORS] = {0};

    while (*draws) {
        const char *draw = get_draw_and_skip_ahead(&draws);
        draw_analysis_t draw_report = {0};

        analyze_draw(draw, &draw_report);

        if (!draw_report.possible) possible = false;

        for (Color i = RED; i < NUM_COLORS; i++)
            if (draw_report.numbers[i] > max_colors[i]) max_colors[i] = draw_report.numbers[i];

        free((void*)draw);
    }

    if (possible) solution->part_one_sum += game_id;
    solution->part_two_sum += array_product(max_colors);
}

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