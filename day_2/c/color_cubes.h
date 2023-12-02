//
// Created by Victor-Marian Busoi on 02.12.2023.
//

#ifndef C_CUBES_H
#define C_CUBES_H
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

static const uint8_t MAX_CUBES[NUM_COLORS] = {MAX_RED_CUBES, MAX_GREEN_CUBES, MAX_BLUE_CUBES};
#endif //C_CUBES_H
