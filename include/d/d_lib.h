#ifndef D_LIB_H
#define D_LIB_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"
#include "d/d_bg_s_acch.h"
#include "dolphin/gx/GXStruct.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_path.h"

extern Quaternion ZeroQuat;

class STControl {
public:
    STControl() {
        setWaitParm(0xF, 0xF, 0, 0, 0.9f, 0.5f, 0, 0x2000);
        init();
    }
    STControl(s16, s16, s16, s16, f32, f32, s16, s16);
    void setWaitParm(s16, s16, s16, s16, f32, f32, s16, s16);
    void init();
    void Xinit();
    void Yinit();
    virtual f32 getValueStick();
    virtual s16 getAngleStick();
    bool checkTrigger();
    bool checkLeftTrigger();
    bool checkRightTrigger();
    bool checkUpTrigger();
    bool checkDownTrigger();

    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ u8 field_0x0c;
    /* 0x0D */ u8 field_0x0d;
    /* 0x0E */ s16 field_0x0e;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1a;
    /* 0x1C */ s16 field_0x1c;
    /* 0x1E */ s16 field_0x1e;
    /* 0x20 */ s16 field_0x20;
    /* 0x22 */ s16 field_0x22;
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ s16 field_0x26;
};

class CSTControl : public STControl {
public:
    virtual f32 getValueStick();
    virtual s16 getAngleStick();
};

class dLib_anm_prm_c {
public:
    /* 0x00 */ s8 mBckIdx;
    /* 0x01 */ s8 mNextPrmIdx;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ f32 mMorf;
    /* 0x08 */ f32 mPlaySpeed;
    /* 0x0C */ int mLoopMode;
};

class dLib_circle_path_c {
public:
    /* 0x00 */ cXyz mTranslation;
    /* 0x0C */ cXyz mPos;
    /* 0x18 */ f32 mRadius;
    /* 0x1C */ f32 mWobbleAmplitude;
    /* 0x20 */ s16 mAngle;
    /* 0x22 */ s16 mAngleSpeed;
};

class dLib_wave_c {
public:
    /* 0x00 */ s16 mAngX;
    /* 0x02 */ s16 mAngZ;
    /* 0x04 */ s16 mAnimX;
    /* 0x06 */ s16 mAnimZ;
    /* 0x08 */ s16 mRotX;
    /* 0x0A */ s16 mRotZ;
};

class dLib_anm_idx_c;

void dLib_setCirclePath(dLib_circle_path_c*);
f32 dLib_getWaterY(cXyz& pos, dBgS_ObjAcch& acch);
void dLib_waveRot(Vec*, f32, dLib_wave_c*);
void dLib_debugDrawAxis(Mtx& mtx, f32 length);
void dLib_debugDrawFan(cXyz& center, s16 angleY, s16 fanSpreadAngle, f32 radius, const GXColor& color);
bool dLib_brkInit(J3DModelData*, mDoExt_brkAnm*, const char*, int);
bool dLib_btkInit(J3DModelData*, mDoExt_btkAnm*, const char*, int);
void dLib_setAnm(const char*, mDoExt_McaMorf*, s8*, s8*, s8*, const dLib_anm_idx_c*, const dLib_anm_prm_c*, bool);
void dLib_bcks_setAnm(const char* arcName, mDoExt_McaMorf* morf, s8* pBckIdx, s8* pPrmIdx,
                      s8* param_5, const int* bcksTbl, const dLib_anm_prm_c* anmPrmTbl, bool param_8);
void dLib_scaleAnime(f32* o_value, f32* p_targets, int targetNum, int* p_targetIdx, f32 scale, f32 maxStep, f32 minStep);
void dLib_getPosFromMtx(f32(*)[4], cXyz*);
bool dLib_pathInfo(dPath**, u8);
void dLib_pathMove(cXyz*, s8*, dPath*, f32, int (*)(cXyz*, cXyz*, cXyz*, void*), void*);
void dLib_setNextStageBySclsNum(u8 i_sclsnum, s8 room_no);
u32 dLib_setFirstMsg(u16 eventBit, u32 firstMsgNo, u32 secondMsgNo);
/**
 * Checks if Link is within a circular area.
 */
bool dLib_checkPlayerInCircle(cXyz center, f32 radius, f32 halfHeight);
/**
 * Checks if an actor is within a circular area.
 */
bool dLib_checkActorInCircle(cXyz center, fopAc_ac_c* actor, f32 radius, f32 halfHeight);
/**
 * Checks if an actor is within a fan-shaped area (sector of a circle).
 */
bool dLib_checkActorInFan(cXyz center, fopAc_ac_c* actor, s16 angleY, s16 fanSpreadAngle, f32 radius, f32 halfHeight);
u32 dLib_getIplDaysFromSaveTime();
void dLib_get_QuatFromTriangle(cXyz*, cXyz*, cXyz*);
void dLib_calc_QuatFromTriangle(Quaternion*, f32, cXyz*, cXyz*, cXyz*);

#endif /* D_LIB_H */
