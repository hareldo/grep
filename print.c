#include "flags_collection.h"
#include <stdio.h>
#include <stdlib.h>

int print_with_a_flag(FILE *file_pointer, Flags *flags, int line_counter, int bit_counter){
    int line_read, line_size = 0;
    char *line_for_a = NULL;
    for (int i = 0; i < flags->a_flag; i++) {
        line_read = getline(&line_for_a, line_size, file_pointer);
        line_counter++;
        if(flags->c_flag){

        }
        else{
            if(flags->n_flag)
                printf("%d:", line_counter);
            else if (flags->b_flag)
                printf("%d-", bit_counter);
            printf("%s\n", line_for_a);
        }
    }
    printf("--");

    return line_counter;
}


int print_line(FILE *file_pointer, Flags *flags, char *line, int line_counter, int bit_counter){
    if(flags->c_flag){

    }
    else{
        if(flags->n_flag)
            printf("%d:", line_counter);
        else if (flags->b_flag)
            printf("%d:", bit_counter);
        printf("%s\n", line);
    }
    if(flags->a_flag)
        line_counter = (file_pointer, flags, line_counter, bit_counter);
    return line_counter;

}

