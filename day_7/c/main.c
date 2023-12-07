/* Created by Marian Busoi, Dec 3rd, 2023,
 * Advent Of Code 2023, Day 3: https://adventofcode.com/2023/day/3
*/
#include <string.h>
#include "aoc.h"
#include "solution.h"
#include "cards.h"

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

        hand_type_t type = get_hand_type(cards, false);

        vector_t* hand = vector_init_ptr(.length = TUPLE + 1, .capacity = TUPLE + 1,
                                    .items = (vector_item_t[]) { VEC_ITEM_PTR(cards), VEC_U64(bid), VEC_U8(type) });

        hands.push(&hands, VEC_ITEM_PTR(hand));
    }

    // Sort hands for part 1
    qsort(hands.items, hands.length, sizeof(vector_item_t), compare_hands);

    // Compute sum for part 1
    for (size_t j = 0; j < hands.length; j++) {
        vector_t* hand = (vector_t*)hands.get(&hands, j)._ptr;

        solution.part_one += (hand->get(hand, 1)._uint64 * (hands.length - j));
    }

    // For part 2, we must recalculate hand types
    for (size_t j = 0; j < hands.length; j++) {
        vector_t* hand = (vector_t*)hands.get(&hands, j)._ptr;
        vector_t* cards = (vector_t*)hand->get(hand, 0)._ptr;

        hand->set(hand, 2, VEC_U8(get_hand_type(cards, true)));
    }

    // Sort hands for part 2
    qsort(hands.items, hands.length, sizeof(vector_item_t), compare_hands_part_two);

    for (size_t i = 0; i < hands.length; i++) {
        vector_t* hand = (vector_t*) hands.get(&hands, i)._ptr;
        vector_t* cards = (vector_t*) hand->get(hand, 0)._ptr;
        uint64_t bid = hand->get(hand, 1)._uint64;
        hand_type_t type = hand->get(hand, 2)._uint8;

        for (size_t j = 0; j < cards->length; j++) {
            printf("%c", cards->get(cards, j)._char);
        }

        printf("\t%llu = %u\n", bid, type);
    }

    // Compute sum for part 2
    for (size_t j = 0; j < hands.length; j++) {
        vector_t* hand = (vector_t*)hands.get(&hands, j)._ptr;

        solution.part_two += (hand->get(hand, 1)._uint64 * (hands.length - j));
    }

    puts("\n\n");

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line);
    hands.free(&hands);
}