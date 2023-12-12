/* Created by Marian Busoi, Dec 8th, 2023,
 * Advent Of Code 2023, Day 8: https://adventofcode.com/2023/day/8
*/
#include "bumasoft/standard.h"
#include "aoc.h"
#include "solution.h"

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 8, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    // line buffer
    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));
    char* line_head = line;

    // get first non-empty line
    while (fgets(line, BUFFER_LENGTH, fp) && !(line = str_trim(line)));

    // this will be our sequence of actions
    char *actions = str_clone(line);
    size_t actions_len = strlen(actions);

    // get nodes
    hashmap_t* nodes = _hashmap_init();
    vector_t p2_start_nodes = vector_init(); // vector for part 2 start nodes

    while (fgets(line, BUFFER_LENGTH, fp)) {
        if (!(line = str_trim(line)) || !*line) continue; // skip empty lines

        vector_t by_equals = str_split(line, "=");
        if (by_equals.length != 2) PANIC("Invalid input.");

        char *node_name = str_trim((char *) _vector_first(&by_equals)._ptr);

        char *linked_nodes_str = str_trim((char *) _vector_last(&by_equals)._ptr);
        if (linked_nodes_str == NULL) PANIC("Invalid input.");

        linked_nodes_str[strlen(linked_nodes_str) - 1] = '\0'; // remove ')' at end
        linked_nodes_str++; // remove '(' at start

        vector_t by_comma = str_split(linked_nodes_str, ",");
        if (by_comma.length != 2) PANIC("Invalid input.");

        char *node_name_prev = str_trim((char *) _vector_first(&by_comma)._ptr);
        char *node_name_next = str_trim((char *) _vector_last(&by_comma)._ptr);

        SAFE_MALLOC(Node*, node, 1, sizeof(Node));

        strncpy(node->tag, node_name, TAG_LENGTH);
        strncpy(node->prev, node_name_prev, TAG_LENGTH);
        strncpy(node->next, node_name_next, TAG_LENGTH);

        if (P2_IS_START(node->tag)) _vector_push_string(&p2_start_nodes, node_name);

        nodes->put(nodes, node_name, node);

        // Some cleanup:
        for (size_t i = 0; i < by_comma.length; i++)
            free(by_comma.get(&by_comma, i)._ptr);
        _vector_free_items(&by_comma);
        for (size_t i = 0; i < by_equals.length; i++)
            free(by_equals.get(&by_equals, i)._ptr);
        _vector_free_items(&by_equals);
    };

    solve_part_one(actions, actions_len, nodes, &solution);
    solve_part_two(p2_start_nodes, nodes, actions, actions_len, &solution);

    printf("Part 1: %llu\n", solution.part_one);
    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(actions);
    free(line_head);
    nodes->free(nodes);

    for (size_t i = 0; i < p2_start_nodes.length; i++)
        free(_vector_get(&p2_start_nodes, i)._ptr);
    _vector_free_items(&p2_start_nodes);
}