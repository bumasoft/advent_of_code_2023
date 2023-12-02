//
// Created by Victor-Marian Busoi on 02.12.2023.
//

#ifndef C_DRAW_H
#define C_DRAW_H
#pragma once
#include "cubes.h"
typedef struct {
    uint8_t number;
    Color color;
} color_draw_t;

typedef struct {
    bool possible;
    uint8_t numbers[NUM_COLORS];
} draw_analysis_t;

const char *get_draw_and_skip_ahead(char **draws);
color_draw_t process_color_draw(char color_draw[], size_t color_draw_len);
void analyze_draw(const char *draw, draw_analysis_t *report);
#endif //C_DRAW_H
