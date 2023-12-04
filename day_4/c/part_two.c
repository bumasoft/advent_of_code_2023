//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "part_two.h"

uint64_t recurse_sum(const uint64_t array[], int pivot) {
    if (pivot < 0) return 0;

    uint64_t sum = 1;

    for (size_t i = 0; i < array[pivot]; i++)
        sum += recurse_sum(array, pivot + i + 1);

    return sum;
}

void solve_part_two(solution_t* solution) {
    if (solution->part_two_match_count == 0) return;

    solution->part_two_sum = 1;

    for (int i = solution->part_two_match_count - 2; i >= 0; i--)
        solution->part_two_sum += recurse_sum(solution->part_two_matches, i);
}