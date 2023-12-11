//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "solution.h"

uint64_t part_one_extrapolate(vector_t* history) {
    vector_t* diffs = vector_init_ptr();

    bool all_zeroes = true;

    for (size_t i = 0; i < history->length - 1; i++) {
        uint64_t diff = history->get(history, i + 1)._uint64 - history->get(history, i)._uint64;
        diffs->push(diffs, VEC_U64(diff));

        all_zeroes &= (diff == 0);
    }

    uint64_t last_item = history->get(history, history->length - 1)._uint64;

    if (all_zeroes) return 0 + last_item;

    return part_one_extrapolate(diffs) + last_item;
}

void solve_part_one(vector_t* histories, solution_t* solution) {
    for (size_t i = 0; i < histories->length; i++) {
        uint64_t next_value = part_one_extrapolate(_vector_get(histories, i)._ptr);

        solution->part_one += next_value;
    }
}