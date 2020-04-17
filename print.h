#ifndef PRINT_H
#define PRINT_H
#include "flags_collection.h"
#include <stdio.h>

int print_line(FILE *file_pointer, Flags *flags, char *line, int line_counter, int bit_counter);

int print_c_flag(int match_counter);

#endif
