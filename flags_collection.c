#include "flags_collection.h"
#include <stdbool.h>

void set_flags_to_default(Flags* flags)
{
    flags->a_flag_num = 0;
    flags->b_flag = false;
    flags->c_flag = false;
    flags->i_flag = false;
    flags->n_flag = false;
    flags->v_flag = false;
    flags->x_flag = false;
    flags->e_flag = false;
}