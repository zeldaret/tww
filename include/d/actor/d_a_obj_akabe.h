#ifndef D_A_OBJ_AKABE_H
#define D_A_OBJ_AKABE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjAkabe {
    class Act_c : public fopAc_ac_c {
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ dBgW* mpBgW;
        /* 0x29C */ Mtx mCollMtx;
        /* 0x2CC */ int mType;
        /* 0x2D0 */ u8 mbAppear;
        /* 0x2D1 */ u8 m2D1[0x2D4 - 0x2D1];
    };
};

#endif /* D_A_OBJ_AKABE_H */
