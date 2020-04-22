#ifndef COUNTERS_COLLECTION_H
#define COUNTERS_COLLECTION_H
typedef struct Counters{
    int line_counter;
    int bit_counter;
    int match_counter;
    int a_block_counter;
} Counters;

void reset_counters(Counters *counters);

#endif
