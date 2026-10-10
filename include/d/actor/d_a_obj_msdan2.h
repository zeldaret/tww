#ifndef D_A_OBJ_MSDAN2_H
#define D_A_OBJ_MSDAN2_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

namespace daObjMsdan2 {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
        };

        int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

        cPhs_State Mthd_Create();
        BOOL Mthd_Execute();
        BOOL Mthd_Delete();

    public:
        /* 0x290 */ u8 field_0x290[0x298 - 0x290];
        /* 0x298 */ s16 mEventIdx;
        /* 0x29C */ int mMode;
    };  // Size: 0x2A0
};

#endif /* D_A_OBJ_MSDAN2_H */
