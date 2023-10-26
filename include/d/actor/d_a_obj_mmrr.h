#ifndef D_A_OBJ_MMRR_H
#define D_A_OBJ_MMRR_H

#include "f_op/f_op_actor_mng.h"

namespace daObjMmrr {
    class Act_c : public fopAc_ac_c {
    public:
        void setup(const cXyz* pos) {
            current.pos = *pos;
            mBF8 = 1;
        }
    public:
        /* 0x290 */ u8 temp[0xBF8 - 0x290];
        /* 0xBF8 */ u8 mBF8;
    };
};

#endif /* D_A_OBJ_MMRR_H */
