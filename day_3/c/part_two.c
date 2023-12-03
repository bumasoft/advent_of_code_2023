//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "part_two.h"

/* Receives the full input as a char matrix, along with the total line count,
 * and length of each row in the matrix. Computes the solution for part 2
 * by looking at numbers adjacent to * symbols in the input.
 */
void solve_part_two(char** lines, size_t line_count, size_t line_len, solution_t* solution) {
    for (size_t i = 0; i < line_count; i++) { // traverse lines
        for (size_t j = 0; j < line_len; j++) { // walk each line, char by char
            if (lines[i][j] != '*') continue;

            // Potential gear found. Detect adjacent numbers:
            uint64_t left_num = number_at(lines[i], j - 1);
            uint64_t right_num = number_at(lines[i], j + 1);
            uint64_t top_num = i > 0 ? number_at(lines[i - 1], j) : 0;
            uint64_t top_left_num = i > 0 && top_num == 0 ? number_at(lines[i - 1], j - 1) : 0;
            uint64_t top_right_num = i > 0 && top_num == 0 ? number_at(lines[i - 1], j + 1) : 0;
            uint64_t bottom_num = i < line_count - 1 ? number_at(lines[i + 1], j) : 0;
            uint64_t bottom_left_num = i < line_count - 1 && bottom_num == 0 ? number_at(lines[i + 1], j - 1) : 0;
            uint64_t bottom_right_num = i < line_count - 1 && bottom_num == 0 ? number_at(lines[i + 1], j + 1) : 0;

            uint64_t adjacent_nums[8] = {left_num, right_num, top_num, bottom_num,
                                         top_left_num, top_right_num,
                                         bottom_left_num, bottom_right_num};

            uint64_t prod = 1;
            size_t counter = 0; // how many numbers did we detect?

            for (size_t i = 0; i < 8; i++) {
                if (adjacent_nums[i] == 0) continue;
                counter++;

                if (counter > 2) break;

                prod *= adjacent_nums[i];
            }

            if (counter != 2) continue;
            // Only add to solution if gear has EXACTLY 2 adjacent numbers.
            solution->part_two_sum += prod;
        }
    }
}