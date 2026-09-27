#ifndef D_A_OBJ_MSDAN2_H
#define D_A_OBJ_MSDAN2_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"

namespace daObjMsdan2 {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x0,
        };

        int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    
        cPhs_State Mthd_Create();
        BOOL Mthd_Execute();
        BOOL Mthd_Delete();

        static const char M_evname[];
    
    public:
        /* 0x290 */ u8 m290[8];
        /* 0x298 */ s16 mEventIdx;
        /* 0x29A */ u8 m29A[2];
        /* 0x29C */ s32 mMode;
    };
};

#endif /* D_A_OBJ_MSDAN2_H */
