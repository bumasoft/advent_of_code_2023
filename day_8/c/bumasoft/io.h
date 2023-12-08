//
// Created by Victor-Marian Busoi on 05.12.2023.
//

#ifndef BUMASOFT_IO_H
#define BUMASOFT_IO_H

#include "stdio.h"
#include "stdlib.h"

#define PANIC(msg) { fprintf(stderr, msg); \
                   exit(EXIT_FAILURE); }

// File IO
FILE* open_file_from_args(int argc, char** argv);

#endif //BUMASOFT_IO_H
