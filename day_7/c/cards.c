//
// Created by Victor-Marian Busoi on 07.12.2023.
//
#include "cards.h"
#include "bumasoft/vector.h"
#include <string.h>
#include <stdlib.h>

size_t hash_code(char c, bool with_jokers) {
    const char* head = with_jokers ? CHAR_MAP_PART2 : CHAR_MAP_PART1;
    char* pos = strchr(head, c);

    if (pos == NULL) return 0;

    size_t hash = (pos - head);

    return (hash > FREQUENCY_MAP_SIZE - 1) ? 0 : hash;
}

// Descending order
int compare_ints(const void *a, const void *b) {
    return *((int8_t *) b) - *((int8_t *) a);
}

int compare_hands(const void *a, const void *b, bool with_jokers) {
    vector_item_t* vec_a = (vector_item_t*) a;
    vector_item_t* vec_b = (vector_item_t*) b;

    vector_t* hand_a = (vector_t*) vec_a->_ptr;
    vector_t* hand_b = (vector_t*) vec_b->_ptr;

    // compare by HandType
    int first_order_sort = (int8_t)hand_b->get(hand_b, 2)._uint8 - (int8_t)hand_a->get(hand_a, 2)._uint8;
    if (first_order_sort != 0) return first_order_sort;

    // if they are equal, then compare cards one by one
    int second_order_sort = 0;

    for (size_t i = 0; i < CARDS_PER_HAND; i++) {
        vector_t* cards_a = (vector_t*)hand_a->get(hand_a, 0)._ptr;
        vector_t* cards_b = (vector_t*)hand_b->get(hand_b, 0)._ptr;

        int comp = (int) hash_code(cards_b->get(cards_b, i)._char, with_jokers) - (int) hash_code(cards_a->get(cards_a, i)._char, with_jokers);
        if (comp != 0) return comp;
    }

    return second_order_sort;
}

int compare_hands_part_one(const void *a, const void *b) {
    return compare_hands(a, b, false);
}

int compare_hands_part_two(const void *a, const void *b) {
    return compare_hands(a, b, true);
}

hand_type_t get_hand_type(vector_t* cards, bool with_jokers) {
    uint8_t frequency_map[FREQUENCY_MAP_SIZE] = {0};

    for (size_t i = 0; i < cards->length; i++)
        frequency_map[hash_code(cards->get(cards, i)._char, with_jokers)]++;

    uint8_t non_null_freqs[CARDS_PER_HAND] = {0};

    size_t count = 0;

    for (size_t i = 0; i < FREQUENCY_MAP_SIZE; i++)
        if (frequency_map[i] > 0)
            non_null_freqs[count++] = frequency_map[i];

    qsort(non_null_freqs, CARDS_PER_HAND, sizeof(uint8_t), compare_ints);

    switch (non_null_freqs[0]) {
        case 5:
            return FIVE_OF_A_KIND;
        case 4:
            return (with_jokers && frequency_map[0] > 0 ? FIVE_OF_A_KIND : FOUR_OF_A_KIND);
        case 3:
            if (with_jokers) {
                if (frequency_map[0] == 3) return non_null_freqs[1] == 2 ? FIVE_OF_A_KIND : FOUR_OF_A_KIND;
                if (frequency_map[0] == 2) return FIVE_OF_A_KIND;
                if (frequency_map[0] == 1) return FOUR_OF_A_KIND;
                if (non_null_freqs[1] == 2) return FULL_HOUSE;
                return THREE_OF_A_KIND;
            }

            return (non_null_freqs[1] == 2) ? FULL_HOUSE : THREE_OF_A_KIND;
        case 2:
            if (with_jokers && frequency_map[0] > 0) {
                if (frequency_map[0] == 1)
                    return non_null_freqs[1] == 2 ? FULL_HOUSE : THREE_OF_A_KIND;

                return non_null_freqs[1] == 2 ? FOUR_OF_A_KIND : THREE_OF_A_KIND;
            }

            return (non_null_freqs[1] == 2) ? TWO_PAIRS : ONE_PAIR;
        default:
            return frequency_map[0] == 1 && with_jokers ? ONE_PAIR : HIGH_CARD;
    }
}