#include "flags_collection.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *set_search_parameters(FILE *file_pointer, Flags *input_flags, char *search_fraze,
                    char *input_args[], int number_of_args){
    if(file_pointer!=NULL){
        number_of_args--;
    }
    else
        file_pointer = stdin;
    for (int i = 1; i < number_of_args; i++) {
        if(strcmp(input_args[i],"-A")==0){
            input_flags->a_flag = input_args[i+1];
            i++;
        }
        else if (strcmp(input_args[i],"-b")==0)
            input_flags->b_flag = 1;
        else if (strcmp(input_args[i],"-c")==0)
            input_flags->c_flag = 1;
        else if (strcmp(input_args[i],"-i")==0)
            input_flags->i_flag = 1;
        else if (strcmp(input_args[i],"-n")==0)
            input_flags->n_flag = 1;
        else if (strcmp(input_args[i],"-v")==0)
            input_flags->v_flag = 1;
        else if (strcmp(input_args[i],"-x")==0)
            input_flags->x_flag = 1;
        else if (strcmp(input_args[i],"-E")==0)
            input_flags->e_flag = 1;
        else{
            search_fraze = malloc(strlen(input_args[i]));
            strcpy(search_fraze,input_args[i]);
        }

    }
    return file_pointer
}


int search_lines(FILE *file_pointer, char *search_fraze, Flags *input_flags){
    int line_read, line_size = 0, line_counter=0, bit_counter=0;
    char *line = NULL;
    line_read = getline(&line, line_size, file_pointer);
    while(line_read != -1){
        /// call the search and print functions
        line_read = getline(&line, line_size, file_pointer);
        line_counter++;
        bit_counter = bit_counter + line_read;
    }
    return 0;
}