#include "mach_line.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


#define  FIRST_ASCII_CHAR 33
#define  LAST_ASCII_CHAR 126


typedef enum match_type {MATCH, EXACT_MATCH, NOT_MATCH} match_type;


int count_matching_chars(char *line, basic_expression *expression){
    bool first_match, second_match;
    if(expression->type == OR) {
        if(strncmp(line, expression->string1, strlen(expression->string1)) == 0)
            return strlen(expression->string1);
        else if(strncmp(line, expression->string2, strlen(expression->string2)) == 0)
            return strlen(expression->string2);
        else
            return 0;
    }
    else {
        first_match = (*line >= *(expression->string1));
        second_match = (*line <= *(expression->string2));
        return (first_match && second_match);
    }
}

match_type is_exact_match_in_line(char *line_p, expressions_array *expressions){
    int expression_index = 0;
    int num_of_matching_chars;
    while (('\0' != *line_p) && (expression_index < expressions->length)){
        num_of_matching_chars = count_matching_chars(line_p, &expressions->array[expression_index]);
        if(num_of_matching_chars == 0)
            return NOT_MATCH;
        expression_index++;
        line_p += num_of_matching_chars;
    }
    if (expression_index == expressions->length) {
        if ('\0' == *line_p)
            return EXACT_MATCH;
        else
            return MATCH;
    }
    else
        return NOT_MATCH;
}


bool move_to_first_match_in_line(char **line_p, expressions_array *expressions){
    int expression_index = 0;
    bool is_find_match = false;
    int num_of_matching_chars;

    while ('\0' != **line_p){
        num_of_matching_chars = count_matching_chars(*line_p, &expressions->array[expression_index]);
        if(num_of_matching_chars > 0){
            return true;
        }else
            *line_p += 1;
    }
    return false;
}

bool is_match_in_line(char *line_p, expressions_array *expressions, Flags *flags) {
    int num_of_matches;
    if (flags->x_flag == 1) {
        if(count_matching_chars(line_p, &expressions->array[0]) == 0)
            return false;
    }

    if (!move_to_first_match_in_line(&line_p, expressions))
        return false;

    printf("first match : %c\n", *(line_p - 1));

    match_type is = is_exact_match_in_line(line_p, expressions);
    printf("is match : %d\n", is);
    ////// put in the end or outside??
//    if ((flags->v_flag == 1) && (is_find_match == true))
//        return false;


//    if
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

int add_chars_range(char *first_char, char *last_char, basic_expression *expression){
    //expression->first_char = first_char;
    //expression->last_char = last_char;
    expression->string1 = strndup(first_char, 1);
    expression->string2 = strndup(last_char, 1);
    expression->type = RANGE;
    return 1;
}

int parse_round_bracket(char *string, basic_expression *expression){
    char *string_copy;
    string_copy = strdup(string + 1);
    char *first_string = strtok(string_copy, "|");
    char *second_string = strtok(NULL, ")");
    if((NULL != first_string) || (NULL != second_string)) {
        expression->string1 = strdup(first_string);
        expression->string2 = strdup(second_string);
        expression->type = OR;
        return strlen(first_string) + strlen(second_string) + 3;
    } else
        return add_chars_range(string, string, expression);
}

int parse_square_bracket(char *string, basic_expression *expression){
    char *string_copy;
    string_copy = strdup(string + 1);
    char *first_char = strtok(string_copy, "-");
    char *last_char = strtok(NULL, "]");
    if((NULL != first_char) || (NULL != last_char)) {
        add_chars_range(first_char, last_char, expression);
        return strlen(first_char) + strlen(last_char) + 3;
    } else
        return add_chars_range(string, string, expression);
}


///// should we support "[   0-9   ]"????


int parse_expression(char *regex_p, expressions_array* expressions){
    int num_of_expressions = 0;
    char first_ascii_char_p = FIRST_ASCII_CHAR;
    char last_ascii_char_p = LAST_ASCII_CHAR;
    basic_expression *new_array;
    new_array = (basic_expression *)malloc(sizeof(basic_expression));
    basic_expression *new_basic_expression;
    int expression_len;
    while ('\0' != *regex_p) {
        new_array = (basic_expression *) realloc(new_array, sizeof(basic_expression) * (num_of_expressions + 1));
        new_basic_expression = &new_array[num_of_expressions];
        switch (*regex_p) {
            case '(':
                expression_len = parse_round_bracket(regex_p, new_basic_expression);
//                printf(" (%s or %s) \n", new_array[num_of_expressions].string1, new_array[num_of_expressions].string2);
                break;
            case '[':
                expression_len = parse_square_bracket(regex_p, new_basic_expression);
//                printf(" [ %c - %c ]\n ", *new_array[num_of_expressions].string1, *new_array[num_of_expressions].string2);
                break;
            case '\\':
                expression_len = 1 + add_chars_range(regex_p+1, regex_p+1, new_basic_expression);
//                printf(" \\ -> %s  %s \n", new_array[num_of_expressions].string1, new_array[num_of_expressions].string2);
                break;
            case '.':
                expression_len = add_chars_range(&first_ascii_char_p, &last_ascii_char_p, new_basic_expression);
//                printf(" %c to %c \n", *new_array[num_of_expressions].string1, *new_array[num_of_expressions].string2);
                break;
            default :
                expression_len = add_chars_range(regex_p, regex_p, new_basic_expression);
//                printf(" %c is %c \n", *new_array[num_of_expressions].string1, *new_array[num_of_expressions].string2);
        }
        num_of_expressions++;
        regex_p += expression_len;
    }
    expressions->length = num_of_expressions;
    expressions->array = new_array;
    return num_of_expressions;
    // should we free each element in full_expression or just free full_expression?
}