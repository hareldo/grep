#include "flags_collection.h"
#include "common_defines.h"

void set_flags_to_default(Flags* flags)
{
  flags->a_flag_num = 0;
  flags->b_flag = FALSE;
  flags->c_flag = FALSE;
  flags->i_flag = FALSE;
  flags->n_flag = FALSE;
  flags->v_flag = FALSE;
  flags->x_flag = FALSE;
  flags->e_flag = FALSE;
}
