//
// Created by Victor-Marian Busoi on 07.12.2023.
//
#include "cards.h"
#include "bumasoft/vector.h"
#include <string.h>
#include <stdlib.h>

size_t card_strength(char c, bool with_jokers) {
    const char *head = with_jokers ? CHAR_MAP_PART2 : CHAR_MAP_PART1;
    char *pos = strchr(head, c);

    if (pos == NULL) return 0;

    size_t hash = (pos - head);
    return (hash > FREQUENCY_MAP_SIZE - 1) ? 0 : hash;
}

// Descending order
int compare_ints(const void *a, const void *b) {
    return *((int8_t *) b) - *((int8_t *) a);
}

// Descending order
int compare_hands(const void *a, const void *b, bool with_jokers) {
    vector_item_t *vec_a = (vector_item_t *) a;
    vector_item_t *vec_b = (vector_item_t *) b;

    vector_t *hand_a = (vector_t *) vec_a->_ptr;
    vector_t *hand_b = (vector_t *) vec_b->_ptr;

    // compare by HandType
    int first_order_sort = (int8_t) hand_b->get(hand_b, 2)._uint8 - (int8_t) hand_a->get(hand_a, 2)._uint8;
    if (first_order_sort != 0) return first_order_sort;

    // if they are equal, then compare cards one by one
    int second_order_sort = 0;

    vector_t *cards_a = (vector_t *) hand_a->get(hand_a, 0)._ptr;
    vector_t *cards_b = (vector_t *) hand_b->get(hand_b, 0)._ptr;

    for (size_t i = 0; i < CARDS_PER_HAND; i++) {
        int comp = (int) card_strength(cards_b->get(cards_b, i)._char, with_jokers)
                   - (int) card_strength(cards_a->get(cards_a, i)._char, with_jokers);

        if (comp != 0) return comp;
    }

    return second_order_sort;
}

hand_type_t get_hand_type(vector_t *cards, bool with_jokers) {
    uint8_t frequency_map[FREQUENCY_MAP_SIZE] = {0};

    for (size_t i = 0; i < cards->length; i++) {
        char card = cards->get(cards, i)._char;
        frequency_map[card_strength(card, with_jokers)]++;
    }

    uint8_t card_counts[CARDS_PER_HAND] = {0};

    size_t count = 0;
    for (size_t i = 0; i < FREQUENCY_MAP_SIZE; i++)
        if (frequency_map[i] > 0)
            card_counts[count++] = frequency_map[i];

    qsort(card_counts, CARDS_PER_HAND, sizeof(uint8_t), compare_ints);

    uint8_t joker_count = frequency_map[0]; //only used when with_jokers = true, joker being the lowest card
    uint8_t highest_card_count = card_counts[0];

    switch (highest_card_count) {
        case 5:
            return FIVE_OF_A_KIND;
        case 4:
            return (with_jokers && joker_count > 0 ? FIVE_OF_A_KIND : FOUR_OF_A_KIND);
        case 3:
            // when no jokers are used, we either have a full house or a three of a kind:
            if (!with_jokers || joker_count == 0)
                return (card_counts[1] == 2) ? FULL_HOUSE : THREE_OF_A_KIND;

            // otherwise the presence of a joker gives us either a five of a kind or a four of a kind:
            return card_counts[1] == 2 && joker_count > 1 ? FIVE_OF_A_KIND : FOUR_OF_A_KIND;
        case 2:
            // when no jokers are used, we either have two pairs or one pair
            if (!with_jokers || joker_count == 0)
                return (card_counts[1] == 2) ? TWO_PAIRS : ONE_PAIR;

            // if we have a joker, it's either a full house or three of a kind
            if (joker_count == 1)
                return card_counts[1] == 2 ? FULL_HOUSE : THREE_OF_A_KIND;

            // if we got here then we have two jokers
            return card_counts[1] == 2 ? FOUR_OF_A_KIND : THREE_OF_A_KIND;

        default:
            return with_jokers && joker_count == 1 ? ONE_PAIR : HIGH_CARD;
    }
}