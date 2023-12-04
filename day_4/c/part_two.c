//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "part_two.h"

uint64_t recurse_sum(const uint64_t array[], int pivot) {
    if (pivot < 0) return 0;

    uint64_t sum = 1; // the card itself
    for (size_t i = 0; i < array[pivot]; i++) // plus the number of copies it has won us
        sum += recurse_sum(array, pivot + i + 1);

    return sum;
}

/*
 * Computes the solution for part 2 based on the data gathered in part 1.
 */
void solve_part_two(solution_t* solution) {
    if (solution->part_two_match_count == 0) return;

    // We begin with the last card, which does not win us any other copies,
    //so we start the sum at 1.
    solution->part_two_sum = 1;

    for (int i = solution->part_two_match_count - 2; i >= 0; i--)
        solution->part_two_sum += recurse_sum(solution->part_two_matches, i);
}