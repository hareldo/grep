#include "match_line.h"
#include "common_defines.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  FIRST_ASCII_CHAR 33
#define  LAST_ASCII_CHAR 126
#define IS_END_OF_LINE(C) (('\0' == C) || ('\n' == C))

typedef enum match_type {NOT_MATCH, MATCH, EXACT_MATCH} match_type;

int count_matching_chars(char *line, BasicExpression *expression, Flags *flags){
    int first_match, second_match;
    if(expression->type == OR) {
        if (flags->i_flag){
            first_match = (strncasecmp(line, expression->string1, strlen(expression->string1)) == 0);
            second_match = (strncasecmp(line, expression->string2, strlen(expression->string2)) == 0);
        } else {
            first_match = (strncmp(line, expression->string1, strlen(expression->string1)) == 0);
            second_match = (strncmp(line, expression->string2, strlen(expression->string2)) == 0);
        }
        if(first_match)
            return strlen(expression->string1);
        else if(second_match)
            return strlen(expression->string2);
        else
            return FALSE;
    }
    else {
        if (flags->i_flag) {
            first_match = (tolower(*line) >= tolower(*(expression->string1)));
            second_match = (tolower(*line) <= tolower(*(expression->string2)));
        } else {
            first_match = (*line >= *(expression->string1));
            second_match = (*line <= *(expression->string2));
        }
        return (first_match && second_match);
    }
}

match_type is_exact_match_in_line(char *line_p, ExpressionsArray *expressions, Flags *flags){
    int expression_index = 0;
    int num_of_matching_chars;
    while (!IS_END_OF_LINE(*line_p) && (expression_index < expressions->length)){
        num_of_matching_chars = count_matching_chars(line_p, &expressions->array[expression_index], flags);
        if(num_of_matching_chars == 0)
            return NOT_MATCH;
        expression_index++;
        line_p += num_of_matching_chars;
    }
    if (expression_index == expressions->length) {
        if (IS_END_OF_LINE(*line_p))
            return EXACT_MATCH;
        else
            return MATCH;
    }
    else
        return NOT_MATCH;
}


int move_to_first_match_in_line(char **line_p, ExpressionsArray *expressions, Flags *flags){
    int expression_index = 0;
    int num_of_matching_chars;

    while (!IS_END_OF_LINE(**line_p)){
        num_of_matching_chars = count_matching_chars(*line_p, &expressions->array[expression_index], flags);
        if(num_of_matching_chars > 0){
            return TRUE;
        }else
            *line_p += 1;
    }
    return FALSE;
}


int add_chars_range(char *first_char, char *last_char, BasicExpression *expression){
    expression->string1 = strndup(first_char, 1);
    expression->string2 = strndup(last_char, 1);
    expression->type = RANGE;
    return 1;
}

int parse_round_bracket(char *string, BasicExpression *expression){
    char *string_copy;
    string_copy = strdup(string + 1);
    char *first_string = strtok(string_copy, "|");
    char *second_string = strtok(NULL, ")");
    int expression_len;
    if((NULL != first_string) || (NULL != second_string)) {
        expression->string1 = strdup(first_string);
        expression->string2 = strdup(second_string);
        expression->type = OR;
        expression_len = strlen(first_string) + strlen(second_string) + 3;
    } else
        expression_len = add_chars_range(string, string, expression);
    free(string_copy);
    return expression_len;
}

int parse_square_bracket(char *string, BasicExpression *expression){
    char *string_copy;
    string_copy = strdup(string + 1);
    int expression_len;
    char *first_char = strtok(string_copy, "-");
    char *last_char = strtok(NULL, "]");
    if((NULL != first_char) || (NULL != last_char)) {
        add_chars_range(first_char, last_char, expression);
        expression_len = strlen(first_char) + strlen(last_char) + 3;
    } else
        expression_len = add_chars_range(string, string, expression);
    free(string_copy);
    return expression_len;
}


void parse_regex(char *regex_p, ExpressionsArray *expressions, Flags *flags){
    int num_of_expressions = 0;
    BasicExpression *new_array;
    new_array = (BasicExpression *)malloc(sizeof(BasicExpression));

    if (!flags->e_flag) {
        new_array[0].string1 = strdup(regex_p);
        new_array[0].string2 = strdup(regex_p);
        new_array[0].type = OR;
        num_of_expressions = 1;
    } else {
        BasicExpression *new_expression;
        int expression_len;
        char first_ascii_char_p = FIRST_ASCII_CHAR;
        char last_ascii_char_p = LAST_ASCII_CHAR;
        while ('\0' != *regex_p) {
            new_array = (BasicExpression *) realloc(new_array, sizeof(BasicExpression) * (num_of_expressions + 1));
            new_expression = &new_array[num_of_expressions];
            switch (*regex_p) {
                case '(':
                    expression_len = parse_round_bracket(regex_p, new_expression);
                    break;
                case '[':
                    expression_len = parse_square_bracket(regex_p, new_expression);
                    break;
                case '\\':
                    expression_len = 1 + add_chars_range(regex_p + 1, regex_p + 1, new_expression);
                    break;
                case '.':
                    expression_len = add_chars_range(&first_ascii_char_p, &last_ascii_char_p, new_expression);
                    break;
                default :
                    expression_len = add_chars_range(regex_p, regex_p, new_expression);
            }
            num_of_expressions++;
            regex_p += expression_len;
        }
    }
    expressions->length = num_of_expressions;
    expressions->array = new_array;
}


int is_match_in_line(char *line_p, ExpressionsArray *expressions, Flags *flags){
    if (flags->x_flag) {
        if (EXACT_MATCH == is_exact_match_in_line(line_p, expressions, flags))
            return TRUE;
        else
            return FALSE;
    }
    while (!IS_END_OF_LINE(*line_p)) {
        if (!move_to_first_match_in_line(&line_p, expressions, flags))
            return FALSE;
        if (is_exact_match_in_line(line_p, expressions, flags) >= MATCH)
            return TRUE;
        line_p++;
    }
    return FALSE;
}


void free_expression(ExpressionsArray *expressions) {
    int i = 0;
    for(i =0; i < expressions->length; i++){
        free(expressions->array[i].string1);
        free(expressions->array[i].string2);
    }
    free(expressions->array);
    free(expressions);
}