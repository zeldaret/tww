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

class STControl {
public:
    STControl(s16, s16, s16, s16, f32, f32, s16, s16);
    void setWaitParm(s16, s16, s16, s16, f32, f32, s16, s16);
    void init();
    void Xinit();
    void Yinit();
    void getValueStick();
    void getAngleStick();
    bool checkTrigger();
    bool checkLeftTrigger();
    bool checkRightTrigger();
    bool checkUpTrigger();
    bool checkDownTrigger();

    /* 0x00 */ void* vtbl;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ u8 field_0x0c;
    /* 0x0D */ u8 field_0x0d;
    /* 0x0E */ u16 field_0x0e;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ u16 field_0x18;
    /* 0x1A */ u16 field_0x1a;
    /* 0x1C */ u16 field_0x1c;
    /* 0x1E */ u16 field_0x1e;
    /* 0x20 */ u16 field_0x20;
    /* 0x22 */ u16 field_0x22;
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ s16 field_0x26;
};

class CSTControl {
public:
    void getValueStick();
    void getAngleStick();
};

class dLib_anm_prm_c {
public:
    /* 0x00 */ s8 field_0x00;
    /* 0x01 */ s8 field_0x01;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ u32 loopMode;
};

class dLib_circle_path_c;
class dLib_wave_c;
class dLib_anm_idx_c;

void dLib_setCirclePath(dLib_circle_path_c*);
void dLib_getWaterY(cXyz&, dBgS_ObjAcch&);
void dLib_waveRot(Vec*, f32, dLib_wave_c*);
void dLib_debugDrawAxis(Mtx&, f32);
void dLib_debugDrawFan(cXyz&, s16, s16, f32, const GXColor&);
void dLib_brkInit(J3DModelData*, mDoExt_brkAnm*, const char*, int);
void dLib_btkInit(J3DModelData*, mDoExt_btkAnm*, const char*, int);
void dLib_setAnm(const char*, mDoExt_McaMorf*, s8*, s8*, s8*, const dLib_anm_idx_c*, const dLib_anm_prm_c*, bool);
void dLib_bcks_setAnm(const char*, mDoExt_McaMorf*, s8*, s8*, s8*, const int*, const dLib_anm_prm_c*, bool);
void dLib_scaleAnime(f32*, f32*, int, int*, f32, f32, f32);
void dLib_getPosFromMtx(f32(*)[4], cXyz*);
void dLib_pathInfo(dPath**, u8);
void dLib_pathMove(cXyz*, s8*, dPath*, f32, int (*)(cXyz*, cXyz*, cXyz*, void*), void*);
void dLib_setNextStageBySclsNum(u8, s8);
void dLib_setFirstMsg(u16, u32, u32);
bool dLib_checkPlayerInCircle(cXyz, f32, f32);
bool dLib_checkActorInCircle(cXyz, fopAc_ac_c*, f32, f32);
bool dLib_checkActorInFan(cXyz, fopAc_ac_c*, s16, s16, f32, f32);
void dLib_getIplDaysFromSaveTime();
void dLib_get_QuatFromTriangle(cXyz*, cXyz*, cXyz*);
void dLib_calc_QuatFromTriangle(Quaternion*, f32, cXyz*, cXyz*, cXyz*);

#endif /* D_LIB_H */
