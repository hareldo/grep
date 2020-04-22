#ifndef PRINT_H
#define PRINT_H
#include "flags_collection.h"


void print_line(Flags *flags, char *line, int line_counter, int bit_counter);
void print_for_a_flag(Flags *flags, char *line, int line_counter, int bit_counter);
void print_end_of_a(int block_number);
void print_c_flag(int match_counter);

#endif