#ifndef D_A_OBJ_MSDAN2_H
#define D_A_OBJ_MSDAN2_H

namespace daObjMsdan2 {

    class Act_c : public fopAc_ac_c {
    public:
        
        void prm_get_swSave() const {}

        enum Prm_e {
            PRM_SW_W = 8, 
            PRM_SW_S = 0, 
        };
        
        cPhs_State Mthd_Create();
        BOOL Mthd_Execute();
        BOOL Mthd_Delete();
        /* 0x1C8 */ u8 field_0x1c8[0x1E2 - sizeof(fopAc_ac_c)]; 
        /* 0x1E2 */ s8 mSwitchBit;
        /* 0x1E3 */ u8 field_0x1e3[0x20A - 0x1E3];
        /* 0x20A */ s8 mType;
        /* 0x20B */ u8 field_0x20b[0x290 - 0x20B];
        /* 0x290 */ u8 field_0x290[0x8];
        /* 0x298 */ s16 mEventIdx;
        /* 0x29A */ u8 field_0x29A[0x2];
        /* 0x29C */ s32 mMode;
    };
};

#endif /* D_A_OBJ_MSDAN2_H */
