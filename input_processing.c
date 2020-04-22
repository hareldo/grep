#include "flags_collection.h"
#include "counters_collection.h"
#include "input_processing.h"
#include "common_defines.h"
#include "print.h"
#include "match_line.h"
#include <stdlib.h>
#include <string.h>

void set_search_parameters(char **file_name, Flags *input_flags, char **search_fraze,
                           char *input_args[], int number_of_args){
    int i;
    for (i = 1; i < number_of_args; i++) {
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
            if(i < number_of_args - 1)
                *search_fraze = strdup(input_args[i]);
            else{
                if(*search_fraze == NULL)
                    *search_fraze = strdup(input_args[i]);
                else
                    *file_name = strdup(input_args[i]);
            }
        }
    }
}



int search_a_flag_lines(FILE *file_pointer, Flags *input_flags, ExpressionsArray *expressions, Counters *counters){
    print_end_of_a(counters->a_block_counter);
    int line_read;
    size_t line_size = 0;
    char *line_for_a = NULL;
    int i;
    for (i = 0; i < input_flags->a_flag_num; i++) {
        line_read = getline(&line_for_a, &line_size, file_pointer);
        if (line_read == -1) {
            free(line_for_a);
            return counters->line_counter;
        }
        counters->line_counter++;
        counters->bit_counter = counters->bit_counter + line_read;
        int is_match = is_match_in_line(line_for_a, expressions, input_flags);
        if ((is_match && !input_flags->v_flag) || (!is_match && input_flags->v_flag)){
            print_line(input_flags, line_for_a, counters->line_counter, counters->bit_counter);
            i = -1;
        }
        else
            print_for_a_flag(input_flags, line_for_a, counters->line_counter, counters->bit_counter);
    }
    counters->a_block_counter++;
    free(line_for_a);
    return 0;
}


int search_lines(FILE *file_pointer, char *search_fraze, Flags *input_flags, Counters *counters){
    int line_read;
    size_t line_size = 0;
    char *line = NULL;
    ExpressionsArray *expressions = (ExpressionsArray *)malloc(sizeof(ExpressionsArray));
    expressions->length = 0;
    parse_regex(search_fraze, expressions,input_flags);
    line_read = getline(&line, &line_size, file_pointer);
    while(line_read != -1){
        int bit_offset = line_read;
        int is_match = is_match_in_line(line, expressions, input_flags);
        if ((is_match && !input_flags->v_flag) || (!is_match && input_flags->v_flag)){
            if(input_flags->c_flag)
                counters->match_counter++;
            else {
                print_line(input_flags, line, counters->line_counter, counters->bit_counter);
                if(input_flags->a_flag_num)
                    search_a_flag_lines(file_pointer, input_flags, expressions, counters);
            }
        }
        line_read = getline(&line, &line_size, file_pointer);
        counters->bit_counter =counters->bit_counter + bit_offset;
        counters->line_counter++;
    }
    if(input_flags->c_flag)
        print_c_flag(counters->match_counter);
    free_expression(expressions);
    free(line);
    return 0;
}
