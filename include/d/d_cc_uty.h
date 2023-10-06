#ifndef D_CC_UTY_H
#define D_CC_UTY_H

#include "SSystem/SComponent/c_cc_d.h"
#include "f_op/f_op_actor.h"

struct CcAtInfo {
    /* 0x00 */ cCcD_Obj* mpObj;
    /* 0x04 */ fopAc_ac_c* mpActor;
    /* 0x08 */ u8 mDamage;
    /* 0x09 */ u8 mbDead;
    /* 0x0A */ u8 mResultingAttackType;
    /* 0x0B */ u8 m0B[0x0E - 0x0B];
    /* 0x0E */ s16 m0E;
    /* 0x10 */ u8 m10[0x12 - 0x10];
    /* 0x12 */ u16 mPlCutBit;
    /* 0x14 */ cXyz* pParticlePos;
    /* 0x18 */ s32 mHitSoundId;
};

void cc_pl_cut_bit_get();
void at_se_get(cCcD_Obj*);
void at_se_getC(cCcD_Obj*);
void def_se_set(fopAc_ac_c*, cCcD_Obj*, unsigned long);
void def_se_set_p(fopAc_ac_c*, cXyz*, cCcD_Obj*, unsigned long);
void at_power_check(CcAtInfo*);
void cc_at_check(fopAc_ac_c*, CcAtInfo*);

#endif /* D_CC_UTY_H */
