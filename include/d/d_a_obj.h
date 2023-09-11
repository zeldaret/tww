#ifndef D_A_OBJ
#define D_A_OBJ

#include "f_op/f_op_actor_mng.h"

namespace daObj {
    template <typename T>
    int PrmAbstract(const fopAc_ac_c* actor, T width, T shift) {
        return ((1 << width) - 1) & (fopAcM_GetParam(actor) >> shift);
    }
};

#endif /* D_A_OBJ */
