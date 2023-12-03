//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "part_one.h"

void solve_part_one(char* line, size_t line_len, char* prev_line, solution_t* solution) {
    for (size_t i = 0; i < line_len; i++) {
        if (IS_DIGIT(line[i])) {
            uint64_t num = 0;
            bool is_valid_num = false;
            size_t len = 0;

            /* For each digit, check for adjacent symbols. If we find any, the number
             * will be added to our sum for part 1.
             */
            for (num = 0; IS_DIGIT(line[i]); i++, len++) {
                num = num * 10 + TO_DIGIT(line[i]);

                is_valid_num |= is_adjacent_to_symbol(i, line, prev_line);
            }

            if (is_valid_num) {
                solution->part_one_sum += num;
                // we do not want to add this number again when we process the next line of text
                for (i--; len > 0; len--, i--) line[i] = '.';
            }
        } else if (IS_SYMBOL(line[i]) && prev_line[i] && is_adjacent_to_digits_above(i, prev_line)) {
            // First check to the top left diagonal.
            uint64_t num = 0;
            size_t j = i;
            // Jump to first digit of number, if any.
            while (j > 0 && IS_DIGIT(prev_line[j - 1])) j--;
            // Then construct the number, if any.
            for (num = 0; IS_DIGIT(prev_line[j]); j++) {
                num = num * 10 + TO_DIGIT(prev_line[j]);
            }

            solution->part_one_sum += num; // will be 0 if no number was found

            // Then check top right diagonal.
            if (i + 1 > j && IS_DIGIT(prev_line[i + 1])) {
                for (num = 0, j = i + 1; IS_DIGIT(prev_line[j]); j++) {
                    num = num * 10 + TO_DIGIT(prev_line[j]);
                }

                solution->part_one_sum += num;
            }
        }
    }
}