#ifndef PRINT_H
#define PRINT_H
#include "flags_collection.h"

#define BLOCKS_DELIMITER "--\n"

void print_line(Flags *flags, char *line, int line_counter, int bit_counter);
void print_for_a_flag(Flags *flags, char *line, int line_counter, int bit_counter);
void print_c_flag(int match_counter);
#endif
