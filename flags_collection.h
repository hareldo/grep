#ifndef FLAGS_COLLECTION_H
#define FLAGS_COLLECTION_H
typedef struct Flags{
    int a_flag_num;
    int b_flag;
    int c_flag;
    int i_flag;
    int n_flag;
    int v_flag;
    int x_flag;
    int e_flag;
} Flags;

void set_flags_to_defulat(Flags *flags);
#endif