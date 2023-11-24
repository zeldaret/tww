#ifndef D_A_KYTAG00_H
#define D_A_KYTAG00_H

#include "f_op/f_op_actor.h"

class kytag00_class : public fopAc_ac_c {
public:
    /* 0x290 */ u32 field_0x290;
    /* 0x294 */ u8 mbEfSet;
    /* 0x295 */ u8 mbPselSet;
    /* 0x296 */ u8 field_0x296;
    /* 0x297 */ u8 mPselIdx;
    /* 0x298 */ u8 mEfMode;
    /* 0x29C */ s32 mThickness;
    /* 0x2A0 */ s32 mInnerFadeY;
    /* 0x2A4 */ f32 mInnerRadius;
    /* 0x2A8 */ f32 mOuterRadius;
    /* 0x2AC */ f32 mTarget;
    /* 0x2B0 */ u8 mSwitchNo;
    /* 0x2B1 */ u8 mbInvert;
    /* 0x2B2 */ u8 mMode;
};

#endif /* D_A_KYTAG00_H */
