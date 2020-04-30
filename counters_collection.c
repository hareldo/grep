#include "counters_collection.h"

void reset_counters(Counters *counters)
{
    counters->line_counter = 1;
    counters->bit_counter = 0;
    counters->match_counter = 0;
    counters->a_block_counter = 0;
}