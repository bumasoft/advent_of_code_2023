//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#ifndef README_MD_MATH_H
#define README_MD_MATH_H
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

// Function to calculate the greatest common divisor (GCD) using Euclidean algorithm
uint64_t gcd(uint64_t a, uint64_t b);

// Function to calculate the least common multiple (LCM) of two numbers
uint64_t lcm(uint64_t a, uint64_t b);

// Function to calculate the LCM of an array of integers
uint64_t lcm_for_array(uint64_t arr[], uint64_t n);

uint64_t max(size_t count, ...);
uint64_t min(size_t count, ...);

#endif //README_MD_MATH_H
