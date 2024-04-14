#ifndef D_A_ESA_H
#define D_A_ESA_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"

class esa_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ u8 field_0x298;
    /* 0x29C */ f32 mGroundHeight;
    /* 0x2A0 */ s8 mActionState;
    /* 0x2A1 */ s8 mState;
    /* 0x2A2 */ u8 field_0x2A2[0x2A4 - 0x2A2];
    /* 0x2A4 */ dPa_rippleEcallBack field_0x2A4;
    /* 0x2B8 */ u8 field_0x2B8;
    /* 0x2B9 */ u8 field_0x2B9;
    /* 0x2BA */ u8 field_0x2BA;
    /* 0x2BC */ J3DModel* mpModel;
    /* 0x2C0 */ s16 mTimer[2];
}; // Size: 0x2C4

#endif /* D_A_ESA_H */
