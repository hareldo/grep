#include "print.h"
#include <stdio.h>

int print_with_a_flag(FILE *file_pointer, Flags *flags, int line_counter, int bit_counter){
    int line_read;
    size_t line_size = 0;
    char *line_for_a = NULL;
    for (int i = 0; i < flags->a_flag_num; i++) {
        line_read = getline(&line_for_a, &line_size, file_pointer);
        if(line_read == -1)
            return line_counter;
        line_counter++;
        bit_counter = bit_counter + line_read;
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
    printf("%d\n", match_counter);
    return 0;
}

