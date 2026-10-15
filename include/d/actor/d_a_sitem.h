#ifndef D_A_SITEM_H
#define D_A_SITEM_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct sitem_s {
    /* 0x00 */ cXyz pos;
    /* 0x0C */ u8 field_0x0C[0x18 - 0x0C];
    /* 0x18 */ f32 thickness;
};  // Size: 0x1C

class sitem_class {
public:
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ J3DModel* mpModel;
    /* 0x2B8 */ u8 mPodType;
    /* 0x2B9 */ u8 mVineLengthType;
    /* 0x2BA */ s8 mItemBit;
    /* 0x2BB */ u8 mItemTableNo;
    /* 0x2BC */ s16 mFrameCounter;
    /* 0x2BE */ u8 field_0x2BE[0x2C0 - 0x2BE];
    /* 0x2C0 */ s16 mAction;
    /* 0x2C2 */ s16 mTimers[2]; // [0]: delay before deletion after the pod breaks.
    /* 0x2C6 */ s16 mHitCooldownTimer; // Also controls when cut-vine particles end.
    /* 0x2C8 */ cXyz mPodPos;
    /* 0x2D4 */ cXyz mOldPodPos;
    /* 0x2E0 */ cXyz mVineEndPos;
    /* 0x2EC */ s16 mPodAngleX;
    /* 0x2EE */ s16 mPodAngleY;
    /* 0x2F0 */ u8 field_0x2F0[0x2F4 - 0x2F0];
    /* 0x2F4 */ f32 mVineSegmentLength;
    /* 0x2F8 */ u8 field_0x2F8[0x2FC - 0x2F8];
    /* 0x2FC */ f32 mVineAxialBias;
    /* 0x300 */ f32 mVineSwayAmplitude;
    /* 0x304 */ f32 mGroundY;
    /* 0x308 */ f32 mVineStubSegmentLength;
    /* 0x30C */ mDoExt_3DlineMat0_c mVineLineMat;
    /* 0x328 */ sitem_s mVinePoints[10];
    /* 0x440 */ mDoExt_3DlineMat0_c mVineStubLineMat;
    /* 0x45C */ sitem_s mVineStubPoints[5];
    /* 0x4E8 */ dCcD_Stts mCcStts;
    /* 0x524 */ dCcD_Sph mVinePodSph[4]; // [0..2]: vine; [3]: pod.
    /* 0x9D4 */ dCcD_Sph mBoomerangSph; // Receives boomerang and wind attacks.
    /* 0xB00 */ cXyz mPodCenterPos;
    /* 0xB0C */ f32 mSwayOffset;
    /* 0xB10 */ s16 mSwayAngleY;
    /* 0xB12 */ u8 field_0xB12[0xB14 - 0xB12];
    /* 0xB14 */ dBgS_AcchCir mBgAcchCir;
    /* 0xB54 */ dBgS_ObjAcch mBgAcch;
#if VERSION == VERSION_DEMO
    /* 0xD18 */ JPABaseEmitter* mpCutParticleEmitter[2];
#endif
    /* 0xD18 */ dPa_followEcallBack mCutParticleCallback[2]; // [0]: ceiling stub; [1]: detached vine.
    /* 0xD40 */ csXyz mCutParticleAngle[2];
    /* 0xD4C */ s8 mCutParticleFlag; // enables cut particles
};  // Size: 0xD50

#endif /* D_A_SITEM_H */
