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


char* parse_round_bracket(char *string, basic_expression **full_expression, int num_of_expressions){
    char *string_copy;
    string_copy = strdup(string);
    char *first_string = strtok(string_copy, "|");
    char *second_string = strtok(NULL, ")");
    if((NULL != first_string) || (NULL != second_string)) {
        *full_expression = (basic_expression *) malloc(sizeof(basic_expression) * num_of_expressions);
        (*full_expression)[num_of_expressions - 1].string1 = strdup(first_string);
        (*full_expression)[num_of_expressions - 1].length1 = strlen(first_string);
        (*full_expression)[num_of_expressions - 1].string2 = strdup(second_string);
        (*full_expression)[num_of_expressions - 1].length2 = strlen(second_string);
        (*full_expression)[num_of_expressions - 1].type = OR;
        printf(" ( %s | %s ) \n", (*full_expression)[num_of_expressions - 1].string1, (*full_expression)[num_of_expressions - 1].string2);
        return(string + strlen(first_string) + strlen(second_string) + 2);
    } else
        return(string + 1);
}


void parse_expression(char *line_p, basic_expression* full_expression){
    int num_of_expressions = 1;
    basic_expression *next_expression = NULL;

    full_expression = (basic_expression *)malloc(sizeof(basic_expression));

    while ('\0' != *line_p) {
        switch (*line_p) {
            case '(':
                line_p = parse_round_bracket(line_p + 1, &full_expression, ++num_of_expressions);
                printf("next expression : %s\n", line_p);
                break;
            default :
                line_p++;
        }
    }
}