//
// Created by Victor-Marian Busoi on 05.12.2023.
//
#include "io.h"

FILE* open_file_from_args(int argc, char** argv) {
    if (argc < 2) {
        fputs("Error: Input file not specified.\n", stderr);
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(argv[1], "r");

    if (fp == NULL) {
        puts("Could not open file.");
        exit(EXIT_FAILURE);
    }

    return fp;
}