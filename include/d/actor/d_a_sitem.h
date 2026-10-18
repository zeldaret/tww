#ifndef D_A_SITEM_H
#define D_A_SITEM_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct sitem_s {
    /* 0x00 */ cXyz pos;
    /* 0x0C */ cXyz field_0x0C;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class sitem_class {
public:
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ J3DModel* mpModel;
    /* 0x2B8 */ u8 mPodType;
    /* 0x2B9 */ u8 field_0x2B9;
    /* 0x2BA */ s8 mItemBit;
    /* 0x2BB */ u8 mItemTableNo;
    /* 0x2BC */ s16 field_0x2BC;
    /* 0x2BE */ u8 field_0x2BE[0x2C0 - 0x2BE];
    /* 0x2C0 */ s16 field_0x2C0;
    /* 0x2C2 */ s16 field_0x2C2[2];
    /* 0x2C6 */ s16 field_0x2C6;
    /* 0x2C8 */ cXyz field_0x2C8;
    /* 0x2D4 */ cXyz field_0x2D4;
    /* 0x2E0 */ cXyz field_0x2E0;
    /* 0x2EC */ s16 field_0x2EC;
    /* 0x2EE */ s16 field_0x2EE;
    /* 0x2F0 */ u8 field_0x2F0[0x2F4 - 0x2F0];
    /* 0x2F4 */ f32 field_0x2F4;
    /* 0x2F8 */ u8 field_0x2F8[0x2FC - 0x2F8];
    /* 0x2FC */ f32 field_0x2FC;
    /* 0x300 */ f32 field_0x300;
    /* 0x304 */ f32 field_0x304;
    /* 0x308 */ f32 field_0x308;
    /* 0x30C */ mDoExt_3DlineMat0_c mVineLineMat;
    /* 0x328 */ sitem_s mVinePoints[10];
    /* 0x440 */ mDoExt_3DlineMat0_c mVineStubLineMat;
    /* 0x45C */ sitem_s mVineStubPoints[5];
    /* 0x4E8 */ dCcD_Stts mCcStts;
    /* 0x524 */ dCcD_Sph mVinePodSph[4];
    /* 0x9D4 */ dCcD_Sph mBoomerangSph;
    /* 0xB00 */ cXyz field_0xB00;
    /* 0xB0C */ f32 field_0xB0C;
    /* 0xB10 */ s16 field_0xB10;
    /* 0xB12 */ u8 field_0xB12[0xB14 - 0xB12];
    /* 0xB14 */ dBgS_AcchCir mBgAcchCir;
    /* 0xB54 */ dBgS_ObjAcch mBgAcch;
#if VERSION == VERSION_DEMO
    /* 0xD18 */ JPABaseEmitter* mpParticleEmitter[2];
#endif
    /* 0xD18 */ dPa_followEcallBack mParticleCallback[2];
    /* 0xD40 */ csXyz field_0xD40[2];
    /* 0xD4C */ s8 field_0xD4C;
};  // Size: 0xD50

#endif /* D_A_SITEM_H */
