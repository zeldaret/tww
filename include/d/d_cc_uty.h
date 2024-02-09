#ifndef D_CC_UTY_H
#define D_CC_UTY_H

#include "SSystem/SComponent/c_cc_d.h"
#include "f_op/f_op_actor.h"

struct CcAtInfo {
public:
    CcAtInfo() {}
    ~CcAtInfo() {}

public:
    /* 0x00 */ cCcD_Obj* mpObj; // The attack obj
    /* 0x04 */ fopAc_ac_c* mpActor; // The attacking actor
    /* 0x08 */ u8 mDamage;
    /* 0x09 */ bool mbDead;
    /* 0x0A */ u8 mResultingAttackType; // TODO: Add enum for this
    /* 0x0C */ csXyz m0C;
    /* 0x12 */ u16 mPlCutBit;
    /* 0x14 */ cXyz* pParticlePos;
    /* 0x18 */ s32 mHitSoundId; // TODO: Not sure what this is, argument passed to bgmHitSound
};

u16 cc_pl_cut_bit_get();
u32 at_se_get(cCcD_Obj*);
u32 at_se_getC(cCcD_Obj*);
void def_se_set(fopAc_ac_c*, cCcD_Obj*, unsigned long);
void def_se_set_p(fopAc_ac_c*, cXyz*, cCcD_Obj*, unsigned long);
fopAc_ac_c* at_power_check(CcAtInfo*);
fopAc_ac_c* cc_at_check(fopAc_ac_c*, CcAtInfo*);

inline void dCc_GetAc(void*) {}

#endif /* D_CC_UTY_H */
