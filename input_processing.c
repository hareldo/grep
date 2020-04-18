#include "flags_collection.h"
#include "input_processing.h"
#include "common_defines.h"
#include "print.h"
#include "match_line.h"
#include <stdlib.h>
#include <string.h>

FILE *set_search_parameters(FILE *file_pointer, Flags *input_flags, char **search_fraze,
                    char *input_args[], int number_of_args){
    if(file_pointer!=NULL){
        number_of_args--;
    }
    else {
        file_pointer = stdin;
    }
    for (int i = 1; i < number_of_args; i++) {
        if(strcmp(input_args[i],"-A")==0){
            input_flags->a_flag_num = atoi(input_args[i+1]);
            i++;
        }
        else if (strcmp(input_args[i],"-b")==0)
            input_flags->b_flag = TRUE;
        else if (strcmp(input_args[i],"-c")==0)
            input_flags->c_flag = TRUE;
        else if (strcmp(input_args[i],"-i")==0)
            input_flags->i_flag = TRUE;
        else if (strcmp(input_args[i],"-n")==0)
            input_flags->n_flag = TRUE;
        else if (strcmp(input_args[i],"-v")==0)
            input_flags->v_flag = TRUE;
        else if (strcmp(input_args[i],"-x")==0)
            input_flags->x_flag = TRUE;
        else if (strcmp(input_args[i],"-E")==0)
            input_flags->e_flag = TRUE;
        else{
            *search_fraze = malloc(strlen(input_args[i]));
            strcpy(*search_fraze,input_args[i]);
        }

    }
    return file_pointer;
}


int search_lines(FILE *file_pointer, char *search_fraze, Flags *input_flags){
    int line_read, line_counter = 1, bit_counter = 0, match_counter = 0;
    size_t line_size = 0;
    char *line = NULL;
    ExpressionsArray *expressions = (ExpressionsArray *)malloc(sizeof(ExpressionsArray));
    expressions->length = 0;
    parse_regex(search_fraze, expressions,input_flags);
    line_read = getline(&line, &line_size, file_pointer);
    while(line_read != -1){
        int is_match = is_match_in_line(line, expressions, input_flags);
        if ((is_match && !input_flags->v_flag) || (!is_match && input_flags->v_flag)){
            if(input_flags->c_flag)
                match_counter++;
            else
                print_line(file_pointer, input_flags, line, line_counter, bit_counter);
        }
        line_read = getline(&line, &line_size, file_pointer);
        line_counter++;
        bit_counter = bit_counter + line_read;
    }
    if(input_flags->c_flag)
        print_c_flag(match_counter);
    free_expression(expressions);
    return 0;
}

