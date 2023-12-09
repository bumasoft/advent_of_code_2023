/* Created by Marian Busoi, Dec 3rd, 2023,
 * Advent Of Code 2023, Day 3: https://adventofcode.com/2023/day/3
*/
#include "bumasoft/standard.h"
#include "aoc.h"

const char START_NODE[3] = "AAA";
const char END_NODE[3] = "ZZZ";

#define TAGS_EQUAL(t1, t2) (t1[0] == t2[0] && t1[1] == t2[1] && t1[2] == t2[2])
#define PART_TWO_IS_START(tag) (tag[2] == 'A')
#define PART_TWO_IS_END(tag) (tag[2] == 'Z')

struct DoublyLinkedList {
    char tag[4];
    char prev[4];
    char next[4];
};

typedef struct DoublyLinkedList Node;

// Function to calculate the greatest common divisor (GCD) using Euclidean algorithm
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the least common multiple (LCM) of two numbers
uint64_t lcm(uint64_t a, uint64_t b) {
    return (a * b) / gcd(a, b);
}

// Function to calculate the LCM of an array of integers
uint64_t calculateLCM(uint64_t arr[], uint64_t n) {
    uint64_t result = arr[0];

    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
    }

    return result;
}

int main(int argc, char **argv) {
    puts("**** Advent of Code, Day 8, 2023 ****\n");

    FILE *fp = open_file_from_args(argc, argv);

    solution_t solution = {0, 0};

    // line buffer
    SAFE_CALLOC(char*, line, BUFFER_LENGTH, sizeof(char));
    char *line_head = line;

    // get first non-empty line
    while (fgets(line, BUFFER_LENGTH, fp) && !(line = str_trim(line)));
    // this will be our sequence of actions
    char *actions = str_clone(line);
    size_t actions_len = strlen(actions);

    puts(actions);

    // get nodes
    hashmap_t* nodes = _hashmap_init();

    vector_t part_two_start_nodes = vector_init();

    char list_head_part1[3] = {'\0'};

    while (fgets(line, BUFFER_LENGTH, fp)) {
        if (!(line = str_trim(line)) || !*line) continue;

        SAFE_MALLOC(Node*, node, 1, sizeof(Node));

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

        strncpy(node->tag, node_name, 3);
        strncpy(node->prev, node_name_prev, 3);
        strncpy(node->next, node_name_next, 3);

        if (TAGS_EQUAL(node->tag, START_NODE)) strncpy(list_head_part1, node_name, 3);
        if (PART_TWO_IS_START(node->tag)) _vector_push_string(&part_two_start_nodes, node_name);

        nodes->put(nodes, node_name, node);

        puts(line);
    };

    // Part 1 traversal:
      bool reached_end = false;
      char current_node[3] = {'\0'};
      strncpy(current_node, list_head_part1, 3);

      while (!reached_end) {
          for (size_t i = 0; i < actions_len; i++) {
              solution.part_one++;

              hashmap_kv_pair_t* kv = nodes->get(nodes, current_node);
              if (kv == NULL) PANIC("Something went wrong.");

              Node* node = kv->value;

              if (actions[i] == 'L' && TAGS_EQUAL(node->prev, END_NODE)) {
                  reached_end = true;
                  break;
              }

              if (actions[i] == 'R' && TAGS_EQUAL(node->next, END_NODE)) {
                  reached_end = true;
                  break;
              }

              strncpy(current_node, actions[i] == 'L' ? node->prev : node->next, 3);
          }
      }

      printf("Part 1: %llu\n", solution.part_one);

    // Part 2 traversal


    puts("Start nodes:\n");

    for (size_t j = 0; j < part_two_start_nodes.length; j++) {
        hashmap_kv_pair_t* kv = nodes->get(nodes, _vector_get(&part_two_start_nodes, j)._ptr);
        if (kv == NULL) PANIC("Something went wrong.");

        Node* node = kv->value;

        printf("%.3s\t", node->tag);
    }

    puts("\n");

    uint64_t path_lengths[part_two_start_nodes.length];

    for (size_t i = 0; i < part_two_start_nodes.length; i++) {
        // for each node we need to find the cycle length

        hashmap_kv_pair_t* kv = nodes->get(nodes, _vector_get(&part_two_start_nodes, i)._ptr);
        if (kv == NULL)
            PANIC("Something went wrong.");

        Node* node = kv->value;

        uint64_t len = 0;

        while(true) {
            bool found_path = false;

            for (size_t j = 0; j < actions_len; j++) {
                len++;

                if ((actions[j] == 'L' && PART_TWO_IS_END(node->prev))
                    || (actions[j] == 'R' && PART_TWO_IS_END(node->next))) {
                    found_path = true;
                    break;
                }

                char* next_tag;
                if (actions[j] == 'L') next_tag = node->prev;
                else next_tag = node->next;

                hashmap_kv_pair_t* kvp = nodes->get(nodes, next_tag);
                if (kvp == NULL)
                    PANIC("Something went wrong.");
                node = kvp->value;
            }

            if (found_path || PART_TWO_IS_END(node->tag)) break;
        }

        path_lengths[i] = len;
    }

    solution.part_two = calculateLCM(path_lengths, part_two_start_nodes.length);

    printf("Part 2: %llu\n", solution.part_two);

    // Cleanup:
    fclose(fp);
    free(line_head);
    free(actions);
}