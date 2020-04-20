#include "flags_collection.h"
#include "counters_collection.h"
#include "input_processing.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file_pointer = fopen(argv[argc-1],"r");
    Flags *input_flags = (Flags *)malloc(sizeof(Flags));
    set_flags_to_default(input_flags);
    char *search_fraze = NULL;
    file_pointer = set_search_parameters(file_pointer, input_flags, &search_fraze, argv, argc);
    Counters *counters = (Counters *)malloc(sizeof(Counters));
    reset_counters(counters);
    search_lines(file_pointer, search_fraze, input_flags, counters);
    fclose(file_pointer);
    free(input_flags);
    free(counters);
    free(search_fraze);
    return 0;
}
