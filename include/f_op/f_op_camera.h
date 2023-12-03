#ifndef F_F_OP_CAMERA_H_
#define F_F_OP_CAMERA_H_

#include "f_op/f_op_view.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_phase.h"
#include "SSystem/SComponent/c_angle.h"
#include "SSystem/SComponent/c_rnd.h"
#include "d/d_cam_param.h"
#include "global.h"

class fopAc_ac_c;
class dStage_Event_dt_c;
class camera_class;

struct stage_camera__entry {
    /* 0x00 */ char mpTypeStr[16];
    /* 0x10 */ u8 mArrowIdx;
    /* 0x11 */ u8 m11;
    /* 0x12 */ u8 m12;
    /* 0x13 */ u8 m13;
};

struct stage_arrow__entry {
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ csXyz mRot;
    /* 0x12 */ s16 m12;
};

struct dCamera__EventParam {
    /* 0x00 */ char mName[16];
    /* 0x10 */ int mValue;
};

class d2DBSplinePath {
    /* 0x00 */ int mKeyframeCur;
    /* 0x04 */ int mTimer;
    /* 0x08 */ int mKeyframeNum;
    /* 0x0C */ int mState;
    /* 0x10 */ int m10;
    /* 0x14 */ int mKeyframeLast;
    /* 0x18 */ u8 m18[0x1C - 0x18];
    /* 0x1C */ f32 mTime;
    /* 0x20 */ u8 m20[0x24 - 0x20];
    /* 0x24 */ f32 mFrameWeight[3];
    /* 0x30 */ int mFrameIdx[3];
    /* 0x3C */ u8 m3C[0x40 - 0x3C];
    /* 0x40 */ void* vtbl;
};

class dCamForcusLine {
    /* 0x00 */ void* vtbl;
    /* 0x04 */ cM_rnd_c mRnd;
    /* 0x10 */ u8 field_10[0x70 - 0x10];
};

class dCamera_c {
public:
    struct BG {
        u8 temp[0xB0];
    };
    
    /* 0x000 */ camera_class* mpCamera;
    /* 0x004 */ u8 m004;
    /* 0x005 */ u8 m005;
    /* 0x006 */ u8 m006[0x008 - 0x006];
    /* 0x008 */ f32 m008;
    /* 0x00C */ s16 m00C;
    /* 0x00E */ cSAngle m00E;
    /* 0x010 */ cXyz mCenter;
    /* 0x01C */ cXyz mEye;
    /* 0x028 */ cXyz mUp;
    /* 0x034 */ cSAngle mBank;
    /* 0x036 */ u8 m036[0x038 - 0x036];
    /* 0x038 */ f32 mFovY;
    /* 0x03C */ cSGlobe m03C;
    /* 0x044 */ cXyz m044;
    /* 0x050 */ cXyz m050;
    /* 0x05C */ s16 m05C;
    /* 0x05E */ u8 m05E[0x060 - 0x05E];
    /* 0x060 */ f32 m060;
    /* 0x064 */ u8 m064[0x068 - 0x064];
    /* 0x068 */ int m068;
    /* 0x06C */ cSAngle mAngleY;
    /* 0x06E */ u8 m06E[0x080 - 0x06E];
    /* 0x080 */ u32 m080;
    /* 0x084 */ cXyz m084;
    /* 0x090 */ cXyz m090;
    /* 0x09C */ f32 m09C;
    /* 0x0A0 */ f32 m0A0;
    // /* 0x0A4 */ @class$4017d_camera_cpp m0A4[2];
    /* 0x0A4 */ u8 m0A4[0x40];
    /* 0x0E4 */ int mStageMapToolCameraIdx;
    /* 0x0E8 */ int m0E8;
    /* 0x0EC */ u8 m0EC[0x108 - 0x0EC];
    /* 0x108 */ int m108;
    /* 0x10C */ u8 m10C[0x110 - 0x10C];
    /* 0x110 */ u8 m110;
    /* 0x111 */ u8 m111[0x114 - 0x111];
    /* 0x114 */ int m114;
    /* 0x118 */ int m118;
    /* 0x11C */ int m11C;
    /* 0x120 */ int mCameraInfoIdx;
    /* 0x124 */ int mPadId;
    /* 0x128 */ fopAc_ac_c* mpPlayerActor;
    /* 0x12C */ fopAc_ac_c* mpLockonTarget;
    /* 0x130 */ int m130;
    /* 0x134 */ u8 m134[0x138 - 0x134];
    /* 0x138 */ int m138;
    /* 0x13C */ int mCurMode;
    /* 0x140 */ int mNextMode;
    /* 0x144 */ int m144;
    /* 0x148 */ cSAngle m148;
    /* 0x14A */ u8 m14A[0x14C - 0x14A];
    /* 0x14C */ f32 m14C;
    /* 0x150 */ u8 m150[0x154 - 0x150];
    /* 0x154 */ f32 mStickMainPosXLast;
    /* 0x158 */ f32 mStickMainPosYLast;
    /* 0x15C */ f32 mStickMainValueLast;
    /* 0x160 */ f32 mStickMainPosXDelta;
    /* 0x164 */ f32 mStickMainPosYDelta;
    /* 0x168 */ f32 mStickMainValueDelta;
    /* 0x16C */ f32 mStickCPosXLast;
    /* 0x170 */ f32 mStickCPosYLast;
    /* 0x174 */ f32 mStickCValueLast;
    /* 0x178 */ f32 mStickCPosXDelta;
    /* 0x17C */ f32 mStickCPosYDelta;
    /* 0x180 */ f32 mStickCValueDelta;
    /* 0x184 */ u8 m184[0x190 - 0x184];
    /* 0x190 */ f32 mTriggerLeftLast;
    /* 0x194 */ f32 mTriggerLeftDelta;
    /* 0x198 */ u8 m198;
    /* 0x199 */ u8 m199;
    /* 0x19A */ u8 m19A;
    /* 0x19B */ u8 m19B;
    /* 0x19C */ f32 mTriggerRightLast;
    /* 0x1A0 */ f32 mTriggerRightDelta;
    /* 0x1A4 */ u8 m1A4;
    /* 0x1A5 */ u8 m1A5;
    /* 0x1A6 */ u8 m1A6;
    /* 0x1A7 */ u8 m1A7;
    /* 0x1A8 */ u8 m1A8;
    /* 0x1A9 */ u8 m1A9;
    /* 0x1AA */ u8 m1AA;
    /* 0x1AB */ u8 m1AB;
    /* 0x1AC */ u8 m1AC;
    /* 0x1AD */ u8 m1AD;
    /* 0x1AE */ u8 m1AE;
    /* 0x1AF */ u8 m1AF[0x1B0 - 0x1AF];
    /* 0x1B0 */ dCamForcusLine mForcusLine;
    /* 0x220 */ u8 m220[0x228 - 0x220];
    /* 0x228 */ cXyz mMonitorPos;
    /* 0x234 */ f32 m234;
    /* 0x238 */ f32 m238;
    /* 0x23C */ f32 m23C;
    /* 0x240 */ int m240;
    /* 0x244 */ f32 m244;
    /* 0x248 */ u8 m248[0x254 - 0x248];
    /* 0x254 */ int m254;
    /* 0x258 */ u8 m258[0x25C - 0x258];
    /* 0x25C */ BG mBG;
    /* 0x30C */ u8 m30C[0x31D - 0x30C];
    /* 0x31D */ u8 m31D;
    /* 0x31E */ u8 m31E[0x350 - 0x31E];
    /* 0x350 */ int m350;
    /* 0x354 */ u8 m354[0x358 - 0x354];
    /* 0x358 */ int mRoomNo;
    /* 0x35C */ int mRoomMapToolCameraIdx;
    /* 0x360 */ u8 m360[0x394 - 0x360];
    /* 0x394 */ f32 mEvFovy;
    /* 0x398 */ f32 mEvBank;
    /* 0x39C */ fopAc_ac_c* mpEvRelActor;
    /* 0x3A0 */ char mEvRelUseMask[4];
    /* 0x3A4 */ int mEvTimer;
    /* 0x3A8 */ u8 m3A8;
    /* 0x3A9 */ u8 m3A9[0x3AC - 0x3A9];
    /* 0x3AC */ cXyz mEvBasePos;
    /* 0x3B8 */ u8 m3B8[0x3FC - 0x3B8];
    /* 0x3FC */ int mStaffIdx;
    /* 0x400 */ int m400;
    /* 0x404 */ int m404;
    /* 0x408 */ u8 m408;
    /* 0x409 */ u8 m409[0x40C - 0x409];
    /* 0x40C */ int m40C;
    /* 0x410 */ int m410;
    /* 0x414 */ u8 m414[0x424 - 0x414];
    /* 0x424 */ dCamera__EventParam mEventParams[8];
    /* 0x4C4 */ dStage_Event_dt_c* m4C4;
    /* 0x4C8 */ d2DBSplinePath mSpline2DPath;
    /* 0x50C */ u32 mEventFlags;
    /* 0x510 */ int mCurStyle;
    /* 0x514 */ int m514;
    /* 0x518 */ int mCurType;
    /* 0x51C */ int mNextType;
    /* 0x520 */ int mMapToolType;
    /* 0x524 */ int m524;
    /* 0x528 */ int m528;
    /* 0x52C */ u8 m52C[0x530 - 0x52C];
    /* 0x530 */ int m530;
    /* 0x534 */ s16 m534;
    /* 0x536 */ s16 m536;
    /* 0x538 */ u8 m538[0x550 - 0x538];
    /* 0x550 */ int m550;
    /* 0x554 */ int m554;
    /* 0x558 */ u8 m558[0x568 - 0x558];
    /* 0x568 */ cXyz mCenterShake;
    /* 0x574 */ cXyz mEyeShake;
    /* 0x580 */ f32 mFovYShake;
    /* 0x584 */ u8 m584[0x590 - 0x584];
    /* 0x590 */ int mBlureTimer;
    /* 0x594 */ u8 m594[0x59C - 0x594];
    /* 0x59C */ int mBlurePositionType;
    /* 0x5A0 */ cXyz mBlurePosition;
    /* 0x5AC */ cXyz mBlureScale;
    /* 0x5B8 */ f32 mBlureAlpha;
    /* 0x5BC */ u8 m5BC[0x5C0 - 0x5BC];
    /* 0x5C0 */ stage_camera__entry mCurRoomCamEntry;
    /* 0x5D4 */ stage_arrow__entry mCurRoomArrowEntry;
    /* 0x5E8 */ int mCurArrowIdx;
    /* 0x5EC */ f32 m5EC;
    /* 0x5F0 */ f32 m5F0;
    /* 0x5F4 */ u8 m5F4[0x5F8 - 0x5F4];
    /* 0x5F8 */ f32 m5F8;
    /* 0x5FC */ int m5FC;
    /* 0x600 */ u8 m600[0x604 - 0x600];
    /* 0x604 */ f32 m604;
    /* 0x608 */ u8 m608[0x60C - 0x608];
    /* 0x60C */ dCamSetup_c mCamSetup;
    /* 0x750 */ dCamParam_c mCamParam;
    /* 0x75C */ int mCamTypeField;
    /* 0x760 */ int mCamTypeEvent;
    /* 0x764 */ int mCamTypeWater;
    /* 0x768 */ int mCamTypeSubject;
    /* 0x76C */ int mCamTypeBoat;
    /* 0x770 */ int mCamTypeBoatBattle;
    /* 0x774 */ int m774;
    /* 0x778 */ int mCamTypeKeep;
    /* 0x77C */ int mCamTypeRestrict;
    /* 0x780 */ u8 field_780[0x800 - 0x780];
    
public:
    void ForceLockOff(unsigned int pcId);
    void Reset(cXyz, cXyz, f32, s16);
    void Set(cXyz, cXyz, f32, s16);
    void Stay();
    void SetTrimSize(s32);
    void StartEventCamera(int, int, ...);
    void EndEventCamera(int);
    
    void CStickUse() {}
    void CStickUseless() {}
    void Center() {}
    void Eye() {}
    void StickUse() {}
    void StickUseless() {}
    void clrFlag(u32) {}
    void setFlag(u32) {}
};

STATIC_ASSERT(sizeof(dCamera_c) == 0x800);

typedef struct leafdraw_method_class leafdraw_method_class;

class camera_process_class : public view_class {
public:
    /* 0x210 */ create_tag_class mDwTg;
    /* 0x224 */ leafdraw_method_class* mpMtd;
    /* 0x228 */ u8 field_0x228[4];
    /* 0x22C */ s8 mPrm1;
    /* 0x22D */ s8 mPrm2;
    /* 0x22E */ s8 mPrm3;
    /* 0x22F */ s8 field_0x22f;
    /* 0x230 */ csXyz mAngle;
    /* 0x238 */ int field_0x238;
};

class camera_class : public camera_process_class {
public:
    /* 0x23C */ int field_0x23c;
    /* 0x240 */ int field_0x244;
     /* 0x244 */ dCamera_c mCamera;
};

struct camera_process_profile_definition {
    /* 0x00 */ view_process_profile_definition mBase;
    /* 0x3C */ leafdraw_method_class* mSubMtd; // Subclass methods
};

dCamera_c* dCam_getBody();
s16 dCam_getAngleY(camera_class*);
s16 dCam_getAngleX(camera_class*);

#endif
