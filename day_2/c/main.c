/* Created by Marian Busoi, Dec 2nd, 2023,
 * Advent Of Code 2023, Day 2: https://adventofcode.com/2023/day/2
*/

#include <string.h>
#include "ancillary.h"

#define RED_TEXT "red"
#define GREEN_TEXT "green"
#define BLUE_TEXT "blue"
#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14

typedef enum {
    RED = 0,
    GREEN,
    BLUE,
    NUM_COLORS
} Color;

const uint8_t MAX_CUBES[NUM_COLORS] = {MAX_RED_CUBES, MAX_GREEN_CUBES, MAX_BLUE_CUBES};

typedef struct {
    uint8_t number;
    Color color;
} color_draw_t;

typedef struct {
    bool possible;
    uint8_t numbers[NUM_COLORS];
} draw_analysis_t;

typedef struct {
    uint64_t part_one_sum;
    uint64_t part_two_sum;
} solution_t;

/*
 * Isolates an individual draw event (e.g.: 3 blue, 4 red, 5 green)
 */
static const char *get_draw_and_skip_ahead(char **draws) {
    // skip whitespace
    while (**draws && !IS_DIGIT(**draws)) (*draws)++;

    SAFE_MALLOC(char*, draw, 64, sizeof(char));

    // copy draw and skip ahead in the draws buffer
    size_t i;
    for (i = 0; **draws && **draws != ';'; (*draws)++, i++)
        if NOT_CRLF(**draws) draw[i] = **draws;
    draw[i] = '\0';

    if (**draws == ';') *draws++;

    return draw;
}

/*
 * Returns a structure holding the color and number separately.
 */
static color_draw_t process_color_draw(char color_draw[], size_t color_draw_len) {
    const char *token_red = strstr(color_draw, RED_TEXT);
    const char *token_green = strstr(color_draw, GREEN_TEXT);
    const char *token_blue = strstr(color_draw, BLUE_TEXT);

    color_draw_t data;

    if (token_red != NULL) data.color = RED;
    else if (token_blue != NULL) data.color = BLUE;
    else if (token_green) data.color = GREEN;
    else {
        fprintf(stderr, "Faulty data: %s", color_draw);
        exit(EXIT_FAILURE);
    }

    uint8_t num = 0;

    for (size_t i = 0; i < color_draw_len && IS_DIGIT(color_draw[i]); i++)
        num = num * 10 + TO_DIGIT(color_draw[i]);

    data.number = num;

    return data;
}

/*
 * Processes a draw event (e.g. 3 blue, 4 red, 5 green)
 * and builds a draw_analysis_t report that specifies whether the event is possible or not,
 * and also the numbers extracted for each color.
 */
static void analyze_draw(const char *draw, draw_analysis_t *report) {
    report->possible = true;

    while (*draw) {
        char color_draw[SMALL_BUFFER_LENGTH];

        size_t color_draw_len = 0;
        while (*draw && *draw != ',' && *draw != ';') {
            if (color_draw_len == SMALL_BUFFER_LENGTH) {
                puts("Buffer overflow. Seems the data is corrupted.");
                exit(EXIT_FAILURE);
            }
            color_draw[color_draw_len++] = *draw;
            draw++;
        }
        color_draw[color_draw_len] = '\0';

        if (color_draw_len == 0) return;

        color_draw_t data = process_color_draw(color_draw, color_draw_len);

        for (Color i = RED; i < NUM_COLORS; i++)
            if (data.color == i && data.number > MAX_CUBES[i]) {
                report->possible = false;
                break;
            }

        report->numbers[data.color] = data.number;

        while (*draw && !IS_DIGIT(*draw)) draw++;
    }
}

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