#ifndef D_A_MT_H
#define D_A_MT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_hostIO.h"

class dPath;
class mDoExt_McaMorf;
class mDoExt_btkAnm;
class mDoExt_brkAnm;
class J3DTexNoAnm;

class mt_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ request_of_phase_process_class mPhs;
    /* 0x02B4 */ u8 m2B4;
    /* 0x02B5 */ u8 m2B5;
    /* 0x02B6 */ bool m2B6;
    /* 0x02B7 */ u8 m2B7;
    /* 0x02B8 */ u8 m2B8;
    /* 0x02B9 */ u8 m2B9;
    /* 0x02BA */ u8 m2BA;
    /* 0x02BB */ u8 m2BB;
    /* 0x02BC */ s8 m2BC;
    /* 0x02BD */ s8 mPathPntIdx;
    /* 0x02BE */ s8 mPathDir;
    /* 0x02C0 */ dPath* mpPath;
    /* 0x02C4 */ mDoExt_McaMorf* mpMorf[8];
    /* 0x02E4 */ u8 m2E4;
    /* 0x02E8 */ int mBrkFrame;
    /* 0x02EC */ int mBtkFrame;
    /* 0x02F0 */ mDoExt_btkAnm* btk[8];
    /* 0x0310 */ mDoExt_brkAnm* brk[8];
    /* 0x0330 */ f32 m330;
    /* 0x0334 */ s16 m334;
    /* 0x0338 */ f32 m338;
    /* 0x033C */ J3DAnmTexPattern* mpAnmTex;
    /* 0x0340 */ J3DTexNoAnm* mpTexNoAnm;
    /* 0x0344 */ u8 mTexAnmFrame;
    /* 0x0345 */ bool mTexAnmPlaying;
    /* 0x0346 */ u8 mAnmTexMaxFrame;
    u8 m347[1];
    /* 0x0348 */ u8 m348;
    /* 0x034A */ s16 m34A;
    /* 0x034C */ bool m34C;
    /* 0x0350 */ cXyz m350[8];
    /* 0x03B0 */ dPa_followEcallBack mPtclCallback[8];
    /* 0x0450 */ JPABaseEmitter* mpEmitter;
    /* 0x0454 */ u8 mMode;
    /* 0x0455 */ u8 mFightMode;
    /* 0x0456 */ s16 mTimer[5];
    /* 0x0460 */ s16 m460;
    /* 0x0462 */ s16 m462;
    /* 0x0464 */ s16 mBlinkTimer;
    /* 0x0466 */ s16 m466;
    /* 0x0468 */ s16 m468;
    /* 0x046A */ s16 m46A;
    /* 0x046C */ s16 m46C;
    /* 0x046E */ s16 m46E;
    /* 0x0470 */ f32 m470;
    /* 0x0474 */ f32 m474;
    /* 0x0478 */ f32 m478;
    /* 0x047C */ cXyz m47C;
    /* 0x0488 */ s16 m488;
    /* 0x048A */ s16 m48A;
    /* 0x048C */ s16 m48C;
    /* 0x048E */ s16 m48E;
    /* 0x0490 */ s16 m490;
    /* 0x0492 */ s16 m492;
    /* 0x0494 */ s16 m494;
    /* 0x0496 */ s16 m496;
    /* 0x049A */ csXyz m49A;
    /* 0x04A0 */ cXyz mPos[8];
    /* 0x0500 */ cXyz mOldPos[8];
    /* 0x0560 */ csXyz mAngle[8];
    /* 0x0590 */ cXyz m590[8];
    /* 0x05F0 */ s16 m5F0[8];
    /* 0x0600 */ f32 mScale[8];
    /* 0x0620 */ f32 m620[8];
    /* 0x0640 */ csXyz m640[30];
    /* 0x06F4 */ cXyz m6F4[64];
    /* 0x09F4 */ csXyz m9F4[64];
    /* 0x0B74 */ s16 mB74[64];
    /* 0x0BF4 */ int mBF4;
    u8 mBF8[0x0C00 - 0x0BF8];
    /* 0x0C00 */ bool mC00;
    /* 0x0C01 */ bool mC01;
    /* 0x0C02 */ s16 mC02;
    /* 0x0C04 */ u8 mC04;
    /* 0x0C08 */ dBgS_AcchCir mAcchCir;
    /* 0x0C48 */ dBgS_Acch mAcch;
    /* 0x0E0C */ dCcD_Stts mStts;
    /* 0x0E48 */ dCcD_Sph mSph[8];
    /* 0x17A8 */ dCcD_Sph mEyeSph;
    /* 0x18D4 */ u8 m18D4;
    /* 0x18D8 */ J3DModel* br_modelL[3];
    /* 0x18E4 */ J3DModel* br_modelR[3];
    /* 0x18F0 */ f32 m18F0;
    /* 0x18F4 */ f32 m18F4;
    /* 0x18F8 */ s8 m18F8;
    /* 0x18F9 */ bool mBlocked;
    /* 0x18FA */ bool mInLava;
    /* 0x18FB */ s8 m18FB;
    /* 0x18FC */ s16 m18FC;
    /* 0x1900 */ enemyice mEnemyIce;
    /* 0x1CB8 */ u32 m1CB8;
    /* 0x1CBC */ s8 m1CBC;
}; // Size: 0x1CC0

STATIC_ASSERT(sizeof(mt_class) == 0x1CC0);

class daMt_HIO_c : public mDoHIO_entry_c {
public:
    daMt_HIO_c();
    virtual ~daMt_HIO_c() {}

public:
    /* 0x00 */ // vtable  
    /* 0x04 */ u8 m04;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ s16 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ s16 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x28 */ f32 m2C;
    /* 0x30 */ s16 m30;
    /* 0x32 */ s16 m32;
    /* 0x34 */ f32 m34;
    /* 0x38 */ s16 m38;
    /* 0x3A */ s16 m3A;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ s16 m50;
    /* 0x52 */ s16 m52;
    /* 0x54 */ s16 m54;
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
};

#endif /* D_A_MT_H */
