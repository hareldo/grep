#include "flags_collection.h"
#include "counters_collection.h"
#include "input_processing.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    Flags *input_flags = (Flags *)malloc(sizeof(Flags));
    set_flags_to_default(input_flags);
    char *search_fraze = NULL;
    char *file_name = NULL;
    FILE *file_pointer;
    set_search_parameters(&file_name, input_flags, &search_fraze, argv, argc);
    if(file_name != NULL)
        file_pointer = fopen(file_name,"r");
    else
        file_pointer = stdin;
    free(file_name);
    Counters *counters = (Counters *)malloc(sizeof(Counters));
    reset_counters(counters);
    search_lines(file_pointer, search_fraze, input_flags, counters);
    fclose(file_pointer);
    free(input_flags);
    free(counters);
    free(search_fraze);
    return 0;
}