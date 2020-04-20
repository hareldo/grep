#ifndef PRINT_H
#define PRINT_H
#include "flags_collection.h"
#include "match_line.h"
#include <stdio.h>

void print_line(Flags *flags, char *line, int line_counter, int bit_counter);
void print_for_a_flag(Flags *flags, char *line, int line_counter, int bit_counter);
void print_c_flag(int match_counter);

#endif
