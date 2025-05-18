#ifndef D_A_KUI_H
#define D_A_KUI_H

#include "f_op/f_op_actor.h"

class dBgW;

class kui_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel2;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ u8 type;
    /* 0x2A1 */ u8 field_0x2A1;
    /* 0x2A2 */ u8 field_0x2A2;
    /* 0x2A3 */ u8 mSwitchNo;
    /* 0x2A4 */ u8 field_0x2A4[0x2A8 - 0x2A4];
    /* 0x2A8 */ Mtx field_0x2A8;
    /* 0x2D8 */ dBgW* field_0x2D8;
    /* 0x2DC */ s16 field_0x2DC[3];
    /* 0x2E2 */ s16 field_0x2E2;
    /* 0x2E4 */ s16 field_0x2E4;
    /* 0x2E6 */ s16 field_0x2E6;
    /* 0x2E8 */ s8 field_0x2E8;
    /* 0x2E9 */ u8 field_0x2E9[0x2EA - 0x2E9];
    /* 0x2EA */ s16 field_0x2EA;
    /* 0x2EC */ cXyz field_0x2EC;
    /* 0x2F8 */ cXyz field_0x2F8;
    /* 0x304 */ u8 field_0x304[0x308 - 0x304];
    /* 0x308 */ s16 field_0x308;
    /* 0x30A */ u8 field_0x30A[0x30C - 0x30A];
    /* 0x30C */ f32 field_0x30C;
};

#endif /* D_A_KUI_H */
