//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include <string.h>
#include "part_one.h"

/* Receives one line of input, and a pointer to the solution struct.
 * Incrementally computes the solution for part 1 and gathers the data necessary for part 2.
 */
void solve_part_one(char *line, solution_t *solution) {
    uint64_t sum = 0;

    char* semicolon = strchr(line, ':');
    if (semicolon == NULL) return;

    line = semicolon + 1;

    char* pipe = strchr(line, '|');
    if (pipe == NULL) return;

    // The part between : and | is the list of winning #s
    SAFE_CALLOC(char*, winning_nums, pipe - line + 1, sizeof(char));
    char* winning_nums_head = winning_nums;

    strncpy(winning_nums, line, pipe - line);
    winning_nums[pipe - line] = '\0';
    winning_nums = str_trim(winning_nums);

    // The part after the | is the list of #s picked
    char* end_of_line;
    for (end_of_line = line; *end_of_line && !IS_CRLF(*end_of_line); end_of_line++);
    SAFE_CALLOC(char*, own_nums, end_of_line - pipe + 1, sizeof(char));
    char* own_nums_head = own_nums;

    strncpy(own_nums, pipe + 1, end_of_line - pipe);
    own_nums[end_of_line - pipe] = '\0';
    own_nums = str_trim(own_nums);

    // Now process these two sets of numbers into int arrays
    uint64_t winning[50] = {0};
    uint64_t picked[50] = {0};

    size_t winning_counter = 0;
    for(winning_counter = 0; (winning[winning_counter] = number_at(&winning_nums)); winning_counter++) ;

    size_t picked_counter = 0;
    for (picked_counter = 0; (picked[picked_counter] = number_at(&own_nums)); picked_counter++) ;

    uint64_t matches = 0; // to save the count of winning picks for this card

    // walk the picked numbers array
    for (size_t i = 0; i < picked_counter; i++) {
        // and check if any # matches another # in the winning #s array
        for(size_t j = 0; j < winning_counter; j++)
            if (winning[j] == picked[i]) {
                sum = sum == 0 ? 1 : 2 * sum;
                matches++;
                break;
            }
    }

    solution->part_one_sum += sum;
    solution->part_two_matches[solution->part_two_match_count++] = matches;

    free(winning_nums_head);
    free(own_nums_head);
}