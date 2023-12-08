//
// Created by Victor-Marian Busoi on 07.12.2023.
//

#ifndef C_CARDS_H
#define C_CARDS_H

#include "bumasoft/vector.h"
#include <stddef.h>

#define FREQUENCY_MAP_SIZE 13
#define CARDS_PER_HAND 5
#define TUPLE 2

typedef enum {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
} hand_type_t;

static const char CHAR_MAP_PART1[13] = "23456789TJQKA";
static const char CHAR_MAP_PART2[13] = "J23456789TQKA";

size_t hash_code(char c, bool with_jokers);

int compare_ints(const void *a, const void *b);
int compare_hands(const void *a, const void *b, bool with_jokers);
int compare_hands_part_one(const void *a, const void *b);
int compare_hands_part_two(const void *a, const void *b);
hand_type_t get_hand_type(vector_t* cards, bool with_jokers);

#endif //C_CARDS_H
