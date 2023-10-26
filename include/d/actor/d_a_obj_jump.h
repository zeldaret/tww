#ifndef D_A_OBJ_JUMP_H
#define D_A_OBJ_JUMP_H

#include "f_op/f_op_actor_mng.h"

namespace daObjJump {
    class Act_c : public fopAc_ac_c {
    public:
        void setup(const cXyz* pos) {
            current.pos = *pos;
            m336 = 1;
        }
        static u32 prm_make_b() {
            return 1;
        }
    public:
        /* 0x290 */ u8 temp[0x336 - 0x290];
        /* 0x336 */ u8 m336;
    };
};

#endif /* D_A_OBJ_JUMP_H */
