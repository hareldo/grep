#ifndef GREP_MACH_LINE_H
#define GREP_MACH_LINE_H

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


void parse_regex(char *regex_p, expressions_array *expressions, Flags *flags);
int is_match_in_line(char *line_p, expressions_array *expressions, Flags *flags);

#endif //GREP_MACH_LINE_H
