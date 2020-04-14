#include "mach_line.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


#define  FIRST_ASCII_CHAR 33
#define  LAST_ASCII_CHAR 126

bool is_match_basic_expression(char *line, basic_expression *expression){
    bool first_match, second_match;
    if(expression->type == OR) {
        first_match = (strncmp(line, expression->string1, strlen(expression->string1)) == 0);
        second_match = (strncmp(line, expression->string2, strlen(expression->string2)) == 0);
        return (first_match || second_match);
    }
    else {
        first_match = (*line < expression->first_char);
        second_match = (*line < expression->last_char);
        return (first_match && second_match);
    }
}

bool is_match_in_line(char *line_p, basic_expression *expressions, int num_of_expressions) {
    int expression_index = 0;

    char *matches_array = (char *)malloc(num_of_expressions * sizeof(bool));
    for(int i = 0; i<num_of_expressions; i++){
        matches_array[i] = false;
    }

    while ('\0' != *line_p){
        matches_array[expression_index] = is_match_basic_expression()
        expression_index++;
        line_p++;
    }
}

/*
bool is_match_in_line(char *line, basic_expression *parsed_expression, int num_of_simple_expressions){
    int expression_index = 0;
    char *line_p = line;
    char *is_match = (char *)malloc(num_of_simple_expressions * sizeof(bool));
    for(int i = 0; i<num_of_simple_expressions; i++){
        is_match[i] = false;
    }

    while ('\0' != *line_p){
        if (is_match_simple_expression(line_p, &parsed_expression[expression_index])) {
            is_match[expression_index] = true;
            if(expression_index < num_of_simple_expressions)
                expression_index++;
        }
        line_p++;
    }
    free(is_match);
}

*/

int add_chars_range(char first_char, char last_char, basic_expression *expression){
    expression->first_char = first_char;
    expression->last_char = last_char;
    expression->type = RANGE;
    return 1;
}

int parse_round_bracket(char *string, basic_expression *expression){
    char *string_copy;
    string_copy = strdup(string);
    char *first_string = strtok(string_copy, "|");
    char *second_string = strtok(NULL, ")");
    if((NULL != first_string) || (NULL != second_string)) {
        expression->string1 = strdup(first_string);
        expression->string2 = strdup(second_string);
        expression->type = OR;
        return strlen(first_string) + strlen(second_string) + 3;
    } else
        return add_chars_range('(', '(', expression);
}

int parse_square_bracket(char *string, basic_expression *expression){
    char *string_copy;
    string_copy = strdup(string);
    char *first_char = strtok(string_copy, "-");
    char *last_char = strtok(NULL, "]");
    if((NULL != first_char) || (NULL != last_char)) {
        add_chars_range(*first_char, *last_char, expression);
        return strlen(first_char) + strlen(last_char) + 3;
    } else
        return add_chars_range('[', '[', expression);
}


///// should we support "[   0-9   ]"????


int parse_expression(char *regex_p, basic_expression* expressions){
    int num_of_expressions = 0;
    expressions = (basic_expression *)malloc(sizeof(basic_expression));
    basic_expression *new_basic_expression;
    int expression_len;
    while ('\0' != *regex_p) {
        expressions = (basic_expression *) realloc(expressions, sizeof(basic_expression) * (num_of_expressions + 1));
        new_basic_expression = &expressions[num_of_expressions];
        switch (*regex_p) {
            case '(':
                expression_len = parse_round_bracket(regex_p + 1, new_basic_expression);
                printf(" (%s or %s) \n", expressions[num_of_expressions].string1, expressions[num_of_expressions].string2);
                break;
            case '[':
                expression_len = parse_square_bracket(regex_p + 1, new_basic_expression);
                printf(" [ %c - %c ]\n ", expressions[num_of_expressions].first_char, expressions[num_of_expressions].last_char);
                break;
            case '\\':
                expression_len = 1 + add_chars_range(*(regex_p+1), *(regex_p+1), new_basic_expression);
                printf(" \\ -> %c  %c \n", expressions[num_of_expressions].first_char, expressions[num_of_expressions].last_char);
                break;
            case '.':
                expression_len = add_chars_range(FIRST_ASCII_CHAR, LAST_ASCII_CHAR, new_basic_expression);
                printf(" %c to %c \n", expressions[num_of_expressions].first_char, expressions[num_of_expressions].last_char);
                break;
            default :
                expression_len = add_chars_range(*regex_p, *regex_p, new_basic_expression);
                printf(" %c is %c \n", expressions[num_of_expressions].first_char, expressions[num_of_expressions].last_char);
        }
        num_of_expressions++;
        line_p += expression_len;
    }
    return num_of_expressions;
    // should we free each element in full_expression or just free full_expression?
}