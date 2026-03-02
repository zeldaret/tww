#ifndef D_A_BOOMERANG_H
#define D_A_BOOMERANG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

#define BOOM_TARGET_MAX 5

class daBoomerang_blur_c : public J3DPacket {
public:
    virtual ~daBoomerang_blur_c() {}
    void initBlur(MtxP, s16);
    void copyBlur(MtxP, s16);
    virtual void draw();

    static const s32 SEGMENTS_PER_STEP = 5;

public:
    /* 0x010 */ void* imageData;
    /* 0x014 */ s32 numTrailSegments;
    /* 0x018 */ cXyz pos;
    /* 0x024 */ cXyz trail0_vtxArr0[12 * SEGMENTS_PER_STEP];
    /* 0x2F4 */ cXyz trail0_vtxArr1[12 * SEGMENTS_PER_STEP];
    /* 0x5C4 */ cXyz trail1_vtxArr0[12 * SEGMENTS_PER_STEP];
    /* 0x894 */ cXyz trail1_vtxArr1[12 * SEGMENTS_PER_STEP];
};

class daBoomerang_sightPacket_c : public dDlst_base_c {
public:
    virtual ~daBoomerang_sightPacket_c() {}
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
    BOOL setLockActor(fopAc_ac_c* i_actor, BOOL doSoundEffect);
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
    /* 0x0F2C */ bool mIsReturning;
    /* 0x0F2D */ bool unused_0xF2D;
    /* 0x0F2E */ bool mJustHit;
    /* 0x0F2F */ bool mCatchAndDelete;
    /* 0x0F30 */ u8 unused_0xF30;
    /* 0x0F31 */ u8 mNumTargets;
    /* 0x0F32 */ u8 mCurTargetIdx;
    /* 0x0F33 */ bool mThirdPerson;
    /* 0x0F34 */ bool mCancelFlg;
    /* 0x0F35 */ u8 mInWater;
    /* 0x0F36 */ bool mFreeFlyOut;
    /* 0x0F38 */ s16 mModelRotZ;
    /* 0x0F3A */ s16 mModelRotY;
    /* 0x0F3C */ f32 mGroundY;
    /* 0x0F40 */ cXyz mTargetPos;
    /* 0x0F4C */ dCcD_Stts mStts;
    /* 0x0F88 */ dCcD_Cps mCps;
    /* 0x10C0 */ dBgS_BoomerangLinChk mLinChk;
    /* 0x112C */ dBgS_ObjGndChk mGndChk;
    /* 0x1180 */ daBoomerang_c_ProcFunc mCurrProcFunc;
};

STATIC_ASSERT(offsetof(daBoomerang_c, mSightPacket) == 0x294);
STATIC_ASSERT(offsetof(daBoomerang_c, mBlur) == 0x3A0);
STATIC_ASSERT(offsetof(daBoomerang_c, mCancelFlg) == 0xF34);
STATIC_ASSERT(offsetof(daBoomerang_c, mStts) == 0xF4C);
STATIC_ASSERT(offsetof(daBoomerang_c, mCps) == 0xF88);
STATIC_ASSERT(sizeof(daBoomerang_c) == 0x118C);

#endif /* D_A_BOOMERANG_H */
