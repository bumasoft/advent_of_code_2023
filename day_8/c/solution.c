//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "solution.h"

void solve_part_one(char* actions, size_t actions_len, hashmap_t* nodes, solution_t* solution) {
    bool reached_end = false;
    char current_node[3] = P1_START_NODE;

    while (!reached_end) {
        for (size_t i = 0; i < actions_len; i++) {
            solution->part_one++;

            hashmap_kv_pair_t* kv = nodes->get(nodes, current_node);
            if (kv == NULL) PANIC("Something went wrong.");

            Node* node = kv->value;

            if (actions[i] == 'L' && TAGS_EQUAL(node->prev, P1_END_NODE)) {
                reached_end = true;
                break;
            }

            if (actions[i] == 'R' && TAGS_EQUAL(node->next, P1_END_NODE)) {
                reached_end = true;
                break;
            }

            strncpy(current_node, actions[i] == 'L' ? node->prev : node->next, TAG_LENGTH);
        }
    }
}

void solve_part_two(vector_t p2_start_nodes, hashmap_t* nodes, char* actions, size_t actions_len, solution_t* solution) {
    uint64_t path_lengths[p2_start_nodes.length];

    // traverse each path and save the path length
    for (size_t i = 0; i < p2_start_nodes.length; i++) {

        hashmap_kv_pair_t* kv = nodes->get(nodes, _vector_get(&p2_start_nodes, i)._ptr);
        if (kv == NULL) PANIC("Something went wrong.");

        Node* node = kv->value;

        uint64_t len = 0;

        while(true) {
            bool found_path = false;

            for (size_t j = 0; j < actions_len; j++) {
                len++;

                if (actions[j] == 'L' && P2_IS_END(node->prev)) {
                    found_path = true;
                    break;
                }

                if (actions[j] == 'R' && P2_IS_END(node->next)) {
                    found_path = true;
                    break;
                }

                hashmap_kv_pair_t* kvp = nodes->get(nodes, actions[j] == 'L' ? node->prev : node->next);
                node = kvp->value;
            }

            if (found_path || P2_IS_END(node->tag)) break;
        }

        path_lengths[i] = len;
    }

    /* The lowest common multiple of the path lengths tells us where all the cycles meet.
     * That is the solution for Part 2.
     */
    solution->part_two = lcm_for_array(path_lengths, p2_start_nodes.length);
}