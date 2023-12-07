/* Created by Marian Busoi, Dec 3rd, 2023,
 * Advent Of Code 2023, Day 3: https://adventofcode.com/2023/day/3
*/
#include <string.h>
#include "aoc.h"
#include "solution.h"

#define FREQUENCY_MAP_SIZE 15
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
} HandType;

size_t hashCode(char c) {
    if (CHAR_IS_DIGIT(c)) return c - '0';

    switch (c) {
        case 'T':
            return 10;
        case 'A':
            return 11;
        case 'J':
            return 12;
        case 'Q':
            return 13;
        case 'K':
            return 14;
        default:
            // this would be a bogus result, it would not match any card
            return 0;
    }
}

// Descending order
int compare_ints(const void *a, const void *b) {
    return *((int8_t *) b) - *((int8_t *) a);
}

int compare_hands(const void *a, const void *b) {
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

        int comp = (int)hashCode( cards_b->get(cards_b, i)._char ) - (int)hashCode( cards_a->get(cards_a, i)._char );
        if (comp != 0) return comp;
    }

    return second_order_sort;
}

HandType get_hand_type(vector_t* cards) {
    uint8_t frequency_map[FREQUENCY_MAP_SIZE] = {0};

    for (size_t i = 0; i < cards->length; i++)
        frequency_map[hashCode(cards->get(cards, i)._char)]++;

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
            return FOUR_OF_A_KIND;
        case 3:
            return (non_null_freqs[1] == 2) ? FULL_HOUSE : THREE_OF_A_KIND;
        case 2:
            return (non_null_freqs[1] == 2) ? TWO_PAIRS : ONE_PAIR;
        default:
            return HIGH_CARD;
    }
}

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 7, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));

    vector_t hands = vector_init();

    while (fgets(line, BUFFER_LENGTH, fp)) {
        vector_t by_space = str_split_by_whitespace(line);

        if (by_space.length != TUPLE) PANIC("Invalid input.");

        uint64_t bid = atoll(by_space.get(&by_space, 1)._ptr);
        vector_t* cards = str_to_vec(by_space.get(&by_space, 0)._ptr);

        if (cards->length != CARDS_PER_HAND) PANIC("Invalid input.");

        uint8_t frequency_map[FREQUENCY_MAP_SIZE] = {0};

        for (size_t i = 0; i < cards->length; i++)
            frequency_map[hashCode(cards->get(cards, i)._char)]++;

        HandType type = get_hand_type(cards);

        vector_t* hand = vector_init_ptr(.length = TUPLE + 1, .capacity = TUPLE + 1,
                                    .items = (vector_item_t[]) { VEC_ITEM_PTR(cards), VEC_U64(bid), VEC_U8(type) });

        hands.push(&hands, VEC_ITEM_PTR(hand));
    }

    // Sort hands
    qsort(hands.items, hands.length, sizeof(vector_item_t), compare_hands);

    // Compute sum
    for (size_t j = 0; j < hands.length; j++) {
        vector_t* hand = (vector_t*)hands.get(&hands, j)._ptr;

        solution.part_one += (hand->get(hand, 1)._uint64 * (hands.length - j));
    }

    puts("\n\n");

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line);
}