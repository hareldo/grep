#ifndef GREP_MATCH_LINE_H
#define GREP_MATCH_LINE_H

#include "flags_collection.h"

typedef enum regex_type {OR, RANGE} regex_type;

typedef struct BasicExpression {
    char* string1;
    char* string2;
    regex_type type;
} BasicExpression;

typedef struct ExpressionsArray {
    BasicExpression *array;
    int length;
} ExpressionsArray;


void parse_regex(char *regex_p, ExpressionsArray *expressions, Flags *flags);
int is_match_in_line(char *line_p, ExpressionsArray *expressions, Flags *flags);
void free_expression(ExpressionsArray *expressions);
#endif
