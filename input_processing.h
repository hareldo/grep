#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H
#include <stdio.h>
void set_search_parameters(char **file_name, Flags *input_flags, char **search_fraze,
                           char *input_args[], int number_of_args);

int search_lines(FILE *file_pointer, char *search_fraze, Flags *input_flags, Counters *counters);
#endif