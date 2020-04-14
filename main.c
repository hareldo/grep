#include "flags_collection.h"
#include "input_processing.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file_pointer;
    file_pointer = fopen(argv[argc],"r");
    Flags *input_flags = (Flags *)malloc(sizeof(Flags));
    set_flags_to_defulat(input_flags);
    char *search_fraze = NULL;
    file_pointer = set_search_parameters(file_pointer, input_flags, search_fraze, argv, argc);
    ///at this point search_fraze input_flags and file_pointer are all ready to be used by the search and print modules
    return 0;
}
