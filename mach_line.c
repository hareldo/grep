#include "mach_line.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

bool is_match_simple_expression(char *line, basic_expression *expression){
    bool is_match;
    is_match = (strncmp(line, expression->string1, expression->length1) == 0);

    if(expression->type == OR)
        is_match = (is_match || (strncmp(line, expression->string2, expression->length2) == 0));

    return is_match;
}


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



int add_chars_range(char first_char, char last_char, basic_expression **expressions, int num_of_expressions){
    *expressions = (basic_expression *) realloc(expressions, sizeof(basic_expression) * num_of_expressions);
    (*expressions)[num_of_expressions - 1].first_char = first_char;
    (*expressions)[num_of_expressions - 1].last_char = last_char;
    (*expressions)[num_of_expressions - 1].type = RANGE;
    return 1;
}

int parse_round_bracket(char *string, basic_expression **expressions, int num_of_expressions){
    char *string_copy;
    string_copy = strdup(string);
    char *first_string = strtok(string_copy, "|");
    char *second_string = strtok(NULL, ")");
    if((NULL != first_string) || (NULL != second_string)) {
        *expressions = (basic_expression *) realloc(expressions, sizeof(basic_expression) * num_of_expressions);
        (*expressions)[num_of_expressions - 1].string1 = strdup(first_string);
        (*expressions)[num_of_expressions - 1].length1 = strlen(first_string);
        (*expressions)[num_of_expressions - 1].string2 = strdup(second_string);
        (*expressions)[num_of_expressions - 1].length2 = strlen(second_string);
        (*expressions)[num_of_expressions - 1].type = OR;
        return strlen(first_string) + strlen(second_string) + 1;
    } else
        return add_chars_range('(', '(', expressions, num_of_expressions);
}

int parse_square_bracket(char *string, basic_expression **expressions, int num_of_expressions){
    char *string_copy;
    string_copy = strdup(string);
    char *first_char = strtok(string_copy, "-");
    char *last_char = strtok(NULL, "]");
    if((NULL != first_char) || (NULL != last_char)) {
        add_chars_range(*first_char, *last_char, expressions, num_of_expressions);
        return strlen(first_char) + strlen(last_char) + 1;
    } else
        return add_chars_range('[', '[', expressions, num_of_expressions);
}


int parse_expression(char *line_p, basic_expression* expressions){
    int num_of_expressions = 1;
    expressions = (basic_expression *)malloc(sizeof(basic_expression));
    int expression_len;
    while ('\0' != *line_p) {
        switch (*line_p) {
            case '(':
                expression_len = parse_round_bracket(line_p + 1, &expressions, ++num_of_expressions);
                printf(" (%s or %s) ", expressions[num_of_expressions-1].string1, expressions[num_of_expressions-1].string2);
                break;
            case '[':
                expression_len = parse_square_bracket(line_p + 1, &expressions, ++num_of_expressions);
                printf(" (%c or %c) ", expressions[num_of_expressions-1].first_char, expressions[num_of_expressions-1].last_char);
                break;
            case '\\':
                expression_len = add_chars_range(*(line_p+1), *(line_p+1), &expressions, ++num_of_expressions);
                printf(" (%c or %c) ", expressions[num_of_expressions-1].first_char, expressions[num_of_expressions-1].last_char);
                break;
            default :
                expression_len = add_chars_range(*line_p, *line_p, &expressions, ++num_of_expressions);
                printf(" (%c or %c) ", expressions[num_of_expressions-1].first_char, expressions[num_of_expressions-1].last_char);
        }
        line_p += expression_len;
    }
    return num_of_expressions;
    // should we free each element in full_expression or just free full_expression?
}