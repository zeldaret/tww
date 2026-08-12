#ifndef D_A_NZ_H
#define D_A_NZ_H

#include "c/c_damagereaction.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

struct nz_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ u8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6;
    /* 0x2B7 */ u8 m2B7[0x2B8 - 0x2B7];
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ u8 mAction;
    /* 0x2BD */ u8 mMode;
    /* 0x2BE */ u8 m2BE;
    /* 0x2BF */ u8 m2BF[0x2C0 - 0x2BF];
    /* 0x2C0 */ u8 m2C0;
    /* 0x2C1 */ u8 m2C1;
    /* 0x2C2 */ u8 m2C2;
    /* 0x2C3 */ u8 m2C3;
    /* 0x2C4 */ fpc_ProcID m2C4;
    /* 0x2C8 */ fpc_ProcID m2C8;
    /* 0x2CC */ s16 m2CC;
    /* 0x2CE */ s16 m2CE;
    /* 0x2D0 */ s16 m2D0;
    /* 0x2D2 */ s16 m2D2;
    /* 0x2D4 */ s16 mTimers[5];
    /* 0x2DE */ u8 m2DE[0x2E2 - 0x2DE];
    /* 0x2E2 */ s16 m2E2;
    /* 0x2E4 */ s32 m2E4;
#if VERSION > VERSION_DEMO
    /* 0x2E8 */ int mCurrBckIdx;
#endif
    /* 0x2EC */ f32 m2EC;
    /* 0x2F0 */ f32 m2F0;
    /* 0x2F4 */ f32 m2F4;
    /* 0x2F8 */ csXyz m2F8;
    /* 0x2FE */ u8 m2FE[0x300 - 0x2FE];
    /* 0x300 */ s16 m300;
    /* 0x302 */ u8 m302[0x304 - 0x302];
    /* 0x304 */ cXyz m304;
    /* 0x310 */ u8 m310[0x31C - 0x310];
    /* 0x31C */ cXyz m31C;
    /* 0x328 */ cXyz m328;
    /* 0x334 */ cXyz m334;
    /* 0x340 */ f32 m340;
    /* 0x344 */ u8 m344[0x35C - 0x344];
    /* 0x35C */ cXyz m35C;
    /* 0x368 */ cXyz m368[8];
    /* 0x3C8 */ cXyz m3C8[8];
    /* 0x428 */ s16 m428;
    /* 0x42A */ u8 m42A[0x42B - 0x42A];
    /* 0x42B */ u8 m42B;
    /* 0x42C */ u8 m42C;
    /* 0x42D */ u8 m42D[0x430 - 0x42D];
    /* 0x430 */ mDoExt_3DlineMat1_c mTailLineMat;
    /* 0x46C */ cXyz m46C[10];
    /* 0x4E4 */ cXyz m4E4[10];
    /* 0x55C */ cXyz m55C[2];
    /* 0x574 */ cXyz m574;
    /* 0x580 */ s16 m580;
    /* 0x582 */ u8 m582[0x584 - 0x582];
    /* 0x584 */ cXyz m584;
    /* 0x590 */ csXyz m590;
    /* 0x596 */ u8 m596[0x598 - 0x596];
    /* 0x598 */ cXyz m598;
    /* 0x5A4 */ csXyz m5A4;
    /* 0x5AA */ u8 m5AA[0x5AC - 0x5AA];
    /* 0x5AC */ dPa_rippleEcallBack mRippleCb;
    /* 0x5C0 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x5E0 */ dPa_followEcallBack mFollowCb;
    /* 0x5F4 */ J3DMaterialTable* mpMaterialTable;
    /* 0x5F8 */ dBgS_AcchCir mAcchCir;
    /* 0x638 */ dBgS_ObjAcch mAcch;
    /* 0x7FC */ dCcD_Stts mStts;
    /* 0x838 */ dCcD_Cyl mBodyCyl;
    /* 0x968 */ u8 m968[0x979 - 0x968];
    /* 0x979 */ u8 m979;
    /* 0x97A */ u8 m97A[0x97C - 0x97A];
    /* 0x97C */ enemyice mEnemyIce;
    /* 0xD34 */ enemyfire mEnemyFire;
    /* 0xF5C */ mDoExt_invisibleModel mInvisibleModel;
}; // Size: 0xF64

class daNZ_HIO_c : public mDoHIO_entry_c {
public:
    daNZ_HIO_c();
    virtual ~daNZ_HIO_c() {}
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
}; // Size: 0x18

#endif /* D_A_NZ_H */
