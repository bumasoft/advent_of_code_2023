//
// Created by Victor-Marian Busoi on 11.12.2023.
//

#include "math.h"


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
uint64_t lcm_for_array(uint64_t arr[], uint64_t n) {
    uint64_t result = arr[0];

    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
    }

    return result;
}

uint64_t max(size_t count, ...) {
    uint64_t result = 0;

    va_list args;
    va_start(args, count);

    for (size_t i = 0; i < count; i++) {
        uint64_t num = va_arg(args, uint64_t);

        if (num > result) result = num;
    }

    return result;
}