#ifndef D_A_BOOMERANG_H
#define D_A_BOOMERANG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

#define BOOM_TARGET_MAX 5

class daBoomerang_blur_c : public J3DPacket {
public:
    void initBlur(MtxP, s16);
    void copyBlur(MtxP, s16);
    virtual void draw();

public:
    /* 0x010 */ void* imageData;
    /* 0x014 */ s32 field_0x14;
    /* 0x018 */ cXyz pos;
    /* 0x024 */ cXyz arr_0x24[12][5];
    /* 0x2F4 */ cXyz arr_0x2F4[12][5];
    /* 0x5C4 */ cXyz arr_0x5C4[12][5];
    /* 0x894 */ cXyz arr_0x894[12][5];
};

class daBoomerang_sightPacket_c : public dDlst_base_c {
public:
    virtual void draw();
    void setSight(cXyz*, int);
    void play(int);

    void initFrame(int n) { mFrameArr[n] = 0; }
    void resetSightOn() { mSightOnFlg = 0; }
    void setImage(ResTIMG* i_img) { mImage = i_img; }
    void setTex(void* data) { mTex = data; }

    static const s32 ANIM_LENGTH = 26;
    static const s32 HALF_ANIM_LENGTH = ANIM_LENGTH / 2;

private:
    /* 0x004 */ Mtx mMtxArr[BOOM_TARGET_MAX];
    /* 0x0F4 */ u8 mFrameArr[BOOM_TARGET_MAX];
    /* 0x0F9 */ u8 mScaleArr[BOOM_TARGET_MAX];
    /* 0x100 */ u32 mSightOnFlg;
    /* 0x104 */ void* mTex;
    /* 0x108 */ ResTIMG* mImage;
};

class daBoomerang_c : public fopAc_ac_c {
public:
    typedef BOOL (daBoomerang_c::*daBoomerang_c_ProcFunc)();

    void onCancelFlg() { mCancelFlg = true; }

    daBoomerang_c();
    cPhs_State create();
    BOOL draw();
    BOOL execute();
    float getFlyMax();
    void rockLineCallback(fopAc_ac_c*);
    void setAimActor(fopAc_ac_c*);
    void setLockActor(fopAc_ac_c*, int);
    void resetLockActor();
    void setRoomInfo();
    void setKeepMatrix();
    void setAimPos();
    void checkBgHit(cXyz*, cXyz*);
    BOOL procWait();
    BOOL procMove();
    BOOL createHeap();

public:
    /* 0x0290 */ J3DModel* mpModel;
    /* 0x0294 */ daBoomerang_sightPacket_c mSightPacket;
    /* 0x03A0 */ daBoomerang_blur_c mBlur;
    /* 0x0F04 */ fpc_ProcID mTargetIds[BOOM_TARGET_MAX];
    /* 0x0F18 */ fopAc_ac_c* mTargetPtrs[BOOM_TARGET_MAX];
    /* 0x0F2C */ u8 field_0xF2C;
    /* 0x0F2D */ u8 field_0xF2D;
    /* 0x0F2E */ u8 field_0xF2E;
    /* 0x0F2F */ u8 field_0xF2F;
    /* 0x0F30 */ u8 field_0xF30;
    /* 0x0F31 */ u8 mNumTargets;
    /* 0x0F32 */ u8 mCurTargetIdx;
    /* 0x0F33 */ u8 field_0xF33;
    /* 0x0F34 */ bool mCancelFlg;
    /* 0x0F35 */ u8 field_0xF35;
    /* 0x0F36 */ u8 field_0xF36;
    /* 0x0F37 */ u8 field_0xF37[0xF3A - 0xF37];
    /* 0x0F3A */ s16 field_0xF3A;
    /* 0x0F35 */ u8 field_0xF3C[0xF40 - 0xF3C];
    /* 0x0F40 */ cXyz field_0xF40;
    /* 0x0F4C */ u8 field_0xF4C[0xF64 - 0xF4C];
    /* 0x0F64 */ dCcD_Stts mStts;
    /* 0x0FA0 */ u8 field_0xFA0[0xFC4 - 0xFA0];
    /* 0x0FC4 */ dCcD_Cps mCps;
    /* 0x10FC */ u8 field_0x10FC[0x1118 - 0x10FC];
    /* 0x1118 */ dBgS_BoomerangLinChk mLinChk;
    // FIXME: mCurrProcFunc should be at 0x1180.
    /* 0x1184 */ daBoomerang_c_ProcFunc mCurrProcFunc;
};

STATIC_ASSERT(offsetof(daBoomerang_c, mSightPacket) == 0x294);
STATIC_ASSERT(offsetof(daBoomerang_c, mBlur) == 0x3A0);
STATIC_ASSERT(offsetof(daBoomerang_c, mCancelFlg) == 0xF34);
STATIC_ASSERT(offsetof(daBoomerang_c, mStts) == 0xF64);
STATIC_ASSERT(offsetof(daBoomerang_c, mCps) == 0xFC4);
// STATIC_ASSERT(sizeof(daBoomerang_c) == 0x118C);

#endif /* D_A_BOOMERANG_H */
