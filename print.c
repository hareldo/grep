#include "flags_collection.h"
#include <stdio.h>
#include <stdlib.h>

int print_with_a_flag(FILE *file_pointer, Flags *flags, int line_counter, int bit_counter){
    int line_read, line_size = 0;
    char *line_for_a = NULL;
    for (int i = 0; i < flags->a_flag_num; i++) {
        line_read = getline(&line_for_a, line_size, file_pointer);
        line_counter++;
        if(flags->n_flag)
            printf("%d-", line_counter);
        if (flags->b_flag)
            printf("%d-", bit_counter);
        printf("%s\n", line_for_a);
    }
    printf("--\n");
    return line_counter;
}


int print_line(FILE *file_pointer, Flags *flags, char *line, int line_counter, int bit_counter){
        if(flags->n_flag)
            printf("%d:", line_counter);
        if (flags->b_flag)
            printf("%d:", bit_counter);
        printf("%s\n", line);
    if(flags->a_flag_num)
        line_counter = print_with_a_flag(file_pointer, flags, line_counter, bit_counter);
    return line_counter;

}


int print_c_flag(int match_counter){
    printf("%d", match_counter);
    return 0;
}

