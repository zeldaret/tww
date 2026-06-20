#ifndef D_A_KYTAG02_H
#define D_A_KYTAG02_H

#include "f_op/f_op_actor.h"
#include "d/d_path.h"

struct kytag02_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ dPath* mpPath;
    /* 0x294 */ cXyz mWindVec;
};

#endif /* D_A_KYTAG02_H */
