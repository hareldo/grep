#ifndef GREP_MACH_LINE_H
#define GREP_MACH_LINE_H

#include <stdbool.h>
#include "flags_collection.h"

typedef enum regex_type {OR, RANGE} regex_type;

typedef struct basic_expression {
    char* string1;
    char* string2;
    regex_type type;
} basic_expression;

typedef struct expressions_array {
    basic_expression *array;
    int length;
} expressions_array;


int parse_expression(char *regex_p, expressions_array *expressions);
bool is_match_in_line(char *line_p, expressions_array *expressions, Flags *flags);
#endif //GREP_MACH_LINE_H
