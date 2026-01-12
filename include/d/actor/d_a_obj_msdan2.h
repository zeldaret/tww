#ifndef D_A_OBJ_MSDAN2_H
#define D_A_OBJ_MSDAN2_H

#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_a_obj.h"

namespace daObjMsdan2 {
    class Act_c : public fopAc_ac_c {
    public:

        enum Prm_e {
            PRM_SWSAVE_W = 8, 
            PRM_SWSAVE_S = 0, 
        };

        enum Mode_e {
            MODE_WAIT         = 0,
            MODE_EVENT        = 1,
            MODE_EVENT_RUNNING= 2,
            MODE_DONE         = 3,
        };
        
        int prm_get_swSave() const { 
            return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); 
        }

        cPhs_State Mthd_Create();
        BOOL Mthd_Execute();
        BOOL Mthd_Delete();
        
        /* 0x1C8 */ u8 field_0x1c8[0x1E2 - sizeof(fopAc_ac_c)]; 
        /* 0x1E2 */ s8 mSwitchBit;
        /* 0x1E3 */ u8 field_0x1e3[0x204 - 0x1E3];
        /* 0x204 */ csXyz mSavedAngle;
        /* 0x20A */ s8 mType;
        /* 0x20B */ u8 field_0x20b[0x290 - 0x20B];
        /* 0x290 */ u8 field_0x290[0x8];
        /* 0x298 */ s16 mEventIdx;
        /* 0x29A */ u8 field_0x29A[0x2];
        /* 0x29C */ s32 mMode;
    };
};

#endif /* D_A_OBJ_MSDAN2_H */
