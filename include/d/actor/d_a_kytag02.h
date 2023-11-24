#ifndef D_A_KYTAG02_H
#define D_A_KYTAG02_H

#include "f_op/f_op_actor.h"
#include "d/d_path.h"

class kytag02_class : public fopAc_ac_c {
public:
    /* 0x290 */ dPath* mpPath;
    /* 0x294 */ cXyz mWindVec;
};

#endif /* D_A_KYTAG02_H */
