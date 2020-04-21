#include "print.h"
#include <stdio.h>


void print_for_a_flag(Flags *flags, char *line, int line_counter, int bit_counter){
        if(flags->n_flag)
            printf("%d-", line_counter);
        if (flags->b_flag)
            printf("%d-", bit_counter);
        printf("%s", line);
}


void print_line(Flags *flags, char *line, int line_counter, int bit_counter){
        if(flags->n_flag)
            printf("%d:", line_counter);
        if (flags->b_flag)
            printf("%d:", bit_counter);
        printf("%s", line);
}


void print_c_flag(int match_counter){
    printf("%d\n", match_counter);
}

void print_end_of_block(){
    printf("%s\n", BLOCKS_DELIMITER);
}