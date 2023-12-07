//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "bumasoft/standard.h"
#include "solution.h"
#include "aoc.h"

static uint64_t build_num_from_scattered_digits(char* str) {
    uint64_t num = 0;

    while (*str) {
        if (CHAR_IS_DIGIT(*str))
            num = num * 10 + CHAR_TO_DIGIT(*str);

        str++;
    }

    return num;
}

static uint64_t compute_num_ways(uint64_t t, uint64_t d) {
    uint64_t ways = 0;

    for (uint64_t hold_time = 1; hold_time < t; hold_time++) {
        uint64_t time_left = t - hold_time;
        uint64_t speed = hold_time; // speed is equal to hold time

        uint64_t dist_can_travel = speed * time_left;

        if (dist_can_travel > d)
            ways++;
    }

    return ways;
}

void solve_part_one(char* time_str, char* dist_str, char* time_tag, char* dist_tag, solution_t *solution) {
    vector_t times = str_split_by_whitespace(time_str + strlen(time_tag));
    vector_t distances = str_split_by_whitespace(dist_str + strlen(dist_tag));

    times.to_u64(&times);
    distances.to_u64(&distances);

    if (times.length == 0 || (times.length != distances.length)) {
        fprintf(stderr, "Invalid input file.");
        exit(EXIT_FAILURE);
    }

    uint64_t result = 0;

    for (size_t i = 0; i < times.length; i++) {
        uint64_t t = times.get(&times, i)._uint64;
        uint64_t d = distances.get(&distances, i)._uint64;

        uint64_t ways = compute_num_ways(t, d);

        result = result == 0 ? ways : result * ways;
    }

    solution->part_one = result;

    // Cleanup
    _vector_free(&times);
    _vector_free(&distances);
}

void solve_part_two(char* time_str, char* dist_str, solution_t *solution) {
    uint64_t time = build_num_from_scattered_digits(time_str);
    uint64_t dist = build_num_from_scattered_digits(dist_str);

    solution->part_two = compute_num_ways(time, dist);
}