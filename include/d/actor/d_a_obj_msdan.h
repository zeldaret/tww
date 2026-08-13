#ifndef D_A_OBJ_MSDAN_H
#define D_A_OBJ_MSDAN_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

namespace daObjMsdan {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SIZE_W = 0x1,
            PRM_SIZE_S = 0x10,

            PRM_SOUND_W = 0x1,
            PRM_SOUND_S = 0x12,

            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x0,

            PRM_EVID_W = 0x8,
            PRM_EVID_S = 0x18,
        };

        s32 prm_get_evId() const { return daObj::PrmAbstract(this, PRM_EVID_W, PRM_EVID_S); }
        s32 prm_get_size() const { return daObj::PrmAbstract(this, PRM_SIZE_W, PRM_SIZE_S); }
        s32 prm_get_sound() const { return daObj::PrmAbstract(this, PRM_SOUND_W, PRM_SOUND_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    
        cPhs_State Mthd_Create();
        BOOL Mthd_Execute();
        BOOL Mthd_Delete();

        static const char M_arcname[];
        static const char M_evname[];
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ s16 mEventIdx;
        /* 0x29A */ u8 m29A[0x29C - 0x29A];
        /* 0x29C */ s32 mState;
    };
};

#endif /* D_A_OBJ_MSDAN_H */
