//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#ifndef README_MD_SOLUTION_H
#define README_MD_SOLUTION_H
#include "aoc.h"
#include "bumasoft/hashmap.h"
#include "bumasoft/vector.h"
#include "bumasoft/math.h"
#include "bumasoft/io.h"
#include <string.h>

#define TAG_LENGTH 3
#define TAGS_EQUAL(t1, t2) (t1[0] == t2[0] && t1[1] == t2[1] && t1[2] == t2[2])

struct DoublyLinkedList {
    char tag[TAG_LENGTH + 1];
    char prev[TAG_LENGTH + 1];
    char next[TAG_LENGTH + 1];
};

typedef struct DoublyLinkedList Node;

// Part 1:
#define P1_START_NODE "AAA"
#define P1_END_NODE "ZZZ"

// Part 2:
#define P2_IS_START(tag) (tag[TAG_LENGTH - 1] == 'A')
#define P2_IS_END(tag) (tag[TAG_LENGTH - 1] == 'Z')

void solve_part_one(char* actions, size_t actions_len, hashmap_t* nodes, solution_t* solution);
void solve_part_two(vector_t p2_start_nodes, hashmap_t* nodes, char* actions, size_t actions_len, solution_t* solution);

#endif //README_MD_SOLUTION_H
