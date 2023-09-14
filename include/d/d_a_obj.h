#ifndef D_A_OBJ
#define D_A_OBJ

#include "f_op/f_op_actor_mng.h"

namespace daObj {
    template <typename T>
    int PrmAbstract(const fopAc_ac_c* actor, T width, T shift) {
        u32 param = fopAcM_GetParam(actor);
        return ((1 << width) - 1) & (param >> shift);
    }

    void HitSeStart(const cXyz*, int, const dCcD_GObjInf*, unsigned long);
    void HitEff_hibana(const fopAc_ac_c*, const dCcD_Cyl*);
};

#endif /* D_A_OBJ */
