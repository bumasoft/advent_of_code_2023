//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "solution.h"
#include <stdlib.h>

uint64_t extrapolate(vector_t* history, part_t part) {
    vector_t* diffs = vector_init_ptr();

    bool all_zeroes = true;

    for (size_t i = 0; i < history->length - 1; i++) {
        uint64_t diff = history->get(history, i + 1)._uint64 - history->get(history, i)._uint64;
        diffs->push(diffs, VEC_U64(diff));

        all_zeroes &= (diff == 0);
    }

    uint64_t item = history->get(history, part == PART_ONE ? history->length - 1 : 0)._uint64;

    if (all_zeroes) {
        _vector_free_items((diffs));
        free(diffs);
        return item;
    }

    uint64_t extrapolate_next = extrapolate(diffs, part);

    _vector_free_items(diffs);
    free(diffs);
    return part == PART_ONE ? extrapolate_next + item : item - extrapolate_next;
}

void solve_part_one(vector_t* histories, solution_t* solution) {
    for (size_t i = 0; i < histories->length; i++) {
        uint64_t next_value = extrapolate(_vector_get(histories, i)._ptr, PART_ONE);

        solution->part_one += next_value;
    }
}

void solve_part_two(vector_t* histories, solution_t* solution) {
    for (size_t i = 0; i < histories->length; i++) {
        uint64_t next_value = extrapolate(_vector_get(histories, i)._ptr, PART_TWO);

        solution->part_two += next_value;
    }
}