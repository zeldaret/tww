#ifndef D_A_KYTAG03_H
#define D_A_KYTAG03_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class mDoExt_McaMorf;

class kytag03_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ mDoExt_McaMorf* mpModel;
    /* 0x29C */ u32 field_0x29c;
    /* 0x2A0 */ u8 field_0x2a0;
    /* 0x2A1 */ u8 mSwitchID;
    /* 0x2A2 */ u8 mbRoomActive;
    /* 0x2A3 */ u8 mbVisible;
    /* 0x2A4 */ u8 mbIsActive;
    /* 0x2A5 */ u8 m2A5;
    /* 0x2A8 */ f32 field_0x2a8;
};

#endif /* D_A_KYTAG03_H */
