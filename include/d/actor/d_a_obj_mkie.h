#ifndef D_A_OBJ_MKIE_H
#define D_A_OBJ_MKIE_H

#include "f_op/f_op_actor_mng.h"

namespace daObjMkie {
    class Act_c : public fopAc_ac_c {
    public:
        void setup(const cXyz* pos) {
            current.pos = *pos;
            mF58 = 1;
        }
        static u32 prm_make(u8 eventId, int swNo) {
            return swNo << 0x10 | (eventId | 0x3000);
        }
    public:
        /* 0x290 */ u8 temp[0xF58 - 0x290];
        /* 0xF58 */ u8 mF58;
    };
};

#endif /* D_A_OBJ_MKIE_H */
