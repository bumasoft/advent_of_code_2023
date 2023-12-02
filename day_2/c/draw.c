//
// Created by Victor-Marian Busoi on 02.12.2023.
//
#include <string.h>
#include "ancillary.h"
#include "color_cubes.h"
#include "draw.h"

/*
 * Isolates an individual draw event (e.g.: 3 blue, 4 red, 5 green)
 */
const char *get_draw_and_skip_ahead(char **draws) {
    // skip whitespace
    while (**draws && !IS_DIGIT(**draws)) (*draws)++;

    SAFE_MALLOC(char*, draw, SMALL_BUFFER_LENGTH, sizeof(char));

    // copy draw and skip ahead in the draws buffer
    size_t i;
    for (i = 0; **draws && **draws != ';'; (*draws)++, i++) {
        if (IS_CRLF(**draws)) continue;
        if (i == SMALL_BUFFER_LENGTH) {
            PANIC("Buffer overflow. Seems the data is corrupted.");
        }
        draw[i] = **draws;
    }

    draw[i] = '\0';

    if (**draws == ';') *draws++;

    return draw;
}

/*
 * Returns a structure holding the color and number separately.
 */
color_draw_t process_color_draw(char color_draw[], size_t color_draw_len) {
    const char *token_red = strstr(color_draw, RED_TEXT);
    const char *token_green = strstr(color_draw, GREEN_TEXT);
    const char *token_blue = strstr(color_draw, BLUE_TEXT);

    color_draw_t data;

    if (token_red != NULL) data.color = RED;
    else if (token_blue != NULL) data.color = BLUE;
    else if (token_green) data.color = GREEN;
    else {
        PANIC("Faulty data! Invalid color detected.");
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
void analyze_draw(const char *draw, draw_analysis_t *report) {
    report->possible = true;

    while (*draw) {
        char color_draw[SMALL_BUFFER_LENGTH];

        size_t color_draw_len = 0;
        while (*draw && *draw != ',' && *draw != ';') {
            if (color_draw_len == SMALL_BUFFER_LENGTH) {
                PANIC("Buffer overflow. Seems the data is corrupted.");
            }
            color_draw[color_draw_len++] = *draw;
            draw++;
        }
        color_draw[color_draw_len] = '\0';

        if (color_draw_len == 0) return;

        color_draw_t data = process_color_draw(color_draw, color_draw_len);

        if (data.number > MAX_CUBES[data.color]) report->possible = false;

        report->numbers[data.color] = data.number;

        while (*draw && !IS_DIGIT(*draw)) draw++;
    }
}