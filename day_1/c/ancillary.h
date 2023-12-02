//
// Created by Victor-Marian Busoi on 02.12.2023.
//

#ifndef C_ANCILLARY_H
#define C_ANCILLARY_H
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 255

// File IO
FILE* open_file_from_args(int argc, char** argv);

// String processing
bool str_starts_with(const char* str, const char* test);

#endif //C_ANCILLARY_H