#ifndef GREP_MACH_LINE_H
#define GREP_MACH_LINE_H


typedef enum regex_type {OR, RANGE} regex_type;

typedef struct basic_expression {
    char* string1;
    char* string2;
    int length1;
    int length2;
    char first_char;
    char last_char;
    regex_type type;
} basic_expression;

int parse_expression(char *line_p, basic_expression* full_expression);

#endif //GREP_MACH_LINE_H
