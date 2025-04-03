#ifndef D_CAMERA_H
#define D_CAMERA_H

#include "SSystem/SComponent/c_angle.h"
#include "SSystem/SComponent/c_rnd.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "f_pc/f_pc_base.h"
#include "d/d_cam_param.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_com_inf_game.h"
#include "global.h"

class camera_class;
class camera_process_class;
class dBgS_LinChk;
class dBgS_CamGndChk;
class cBgS_PolyInfo;
class dStage_Event_dt_c;
class fopAc_ac_c;

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

struct dCamera__Type {
    /* 0x00 */ char name[24];
    /* 0x18 */ s16 mStyles[2][10];
};  // Size: 0x40

class d2DBSplinePath {
public:
    ~d2DBSplinePath() {}
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
public:
    void Init();
    void Draw();
    bool Off();

    /* 0x00 */ dDlst_effectLine_c mEffectLine;
    /* 0x38 */ cXyz m38;
    /* 0x44 */ GXColor m44;
    /* 0x48 */ u8 m48;
    /* 0x49 */ u8 m49;
    /* 0x4C */ int m4C;
    /* 0x50 */ int m50;
    /* 0x54 */ int m54;
    /* 0x58 */ u16 m58;
    /* 0x5A */ u16 m5A;
    /* 0x5C */ u16 m5C;
    /* 0x5E */ u16 m5E;
    /* 0x60 */ f32 m60;
    /* 0x64 */ f32 m64;
    /* 0x68 */ f32 m68;
    /* 0x6C */ f32 m6C;
};

class dCamera_c;
typedef bool (dCamera_c::*engine_fn)(s32);

class dCamera_c {
public:
    struct BG {
        BG() {}
        ~BG() {}
        /* 0x00 */ u8 m00[0x04 - 0x00];
        /* 0x04 */ dBgS_CamGndChk m04;
        /* 0x58 */ f32 m58;
        /* 0x5C */ u8 m5C[0x74 - 0x5C];
        /* 0x74 */ cBgS_PolyInfo m74;
        /* 0x78 */ u8 m84[0xB0 - 0x84];
        //u8 temp[0xB0];
    };

    /* 0x000 */ camera_class* mpCamera;
    /* 0x004 */ u8 m004;
    /* 0x005 */ u8 m005;
    /* 0x006 */ cSAngle m006;
    /* 0x008 */ f32 mDistance;
    /* 0x00C */ cSAngle m00C;
    /* 0x00E */ cSAngle mNextCsAngle;
    /* 0x010 */ cXyz mCenter;
    /* 0x01C */ cXyz mEye;
    /* 0x028 */ cXyz mUp;
    /* 0x034 */ cSAngle mBank;
    /* 0x036 */ u8 m036[0x038 - 0x036];
    /* 0x038 */ f32 mFovY;
    /* 0x03C */ cSGlobe m03C;
    /* 0x044 */ cXyz m044;
    /* 0x050 */ cXyz m050;
    /* 0x05C */ cSAngle m05C;
    /* 0x05E */ u8 m05E[0x060 - 0x05E];
    /* 0x060 */ f32 m060;
    /* 0x064 */ f32 m064;
    /* 0x068 */ int m068;
    /* 0x06C */ cSAngle mAngleY;
    /* 0x06E */ u8 m06E[0x070 - 0x06E];
    /* 0x070 */ cXyz m070;
    /* 0x07C */ u32 m07C;
    /* 0x080 */ u32 m080;
    /* 0x084 */ cXyz m084;
    /* 0x090 */ cXyz m090;
    /* 0x09C */ f32 m09C;
    /* 0x0A0 */ f32 m0A0;
    // /* 0x0A4 */ @class$4017d_camera_cpp m0A4[2];
    /* 0x0A4 */ u8 m0A4[0x40];
    /* 0x0E4 */ int mStageMapToolCameraIdx;
    /* 0x0E8 */ int m0E8;
    /* 0x0EC */ u8 m0EC[0x100 - 0x0EC];
    /* 0x100 */ u8 m100;
    /* 0x101 */ u8 m101;
    /* 0x102 */ u8 m102;
    /* 0x103 */ u8 m103[0x108 - 0x103];
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
    /* 0x130 */ u32 mLockOnActorId;
    /* 0x134 */ fopAc_ac_c* mpLockonActor;
    /* 0x138 */ int mForceLockTimer;
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
    /* 0x184 */ u32 m184;
    /* 0x188 */ u32 m188;
    /* 0x18C */ u32 m18C;
    /* 0x190 */ f32 mTriggerLeftLast;
    /* 0x194 */ f32 mTriggerLeftDelta;
    /* 0x198 */ u8 mHoldLockL;
    /* 0x199 */ u8 mTrigLockL;
    /* 0x19A */ u8 m19A;
    /* 0x19B */ u8 m19B;
    /* 0x19C */ f32 mTriggerRightLast;
    /* 0x1A0 */ f32 mTriggerRightDelta;
    /* 0x1A4 */ u8 mHoldLockR;
    /* 0x1A5 */ u8 mTrigLockR;
    /* 0x1A6 */ u8 m1A6;
    /* 0x1A7 */ u8 m1A7;
    /* 0x1A8 */ u8 mHoldX;
    /* 0x1A9 */ u8 mTrigX;
    /* 0x1AA */ u8 mHoldY;
    /* 0x1AB */ u8 mTrigY;
    /* 0x1AC */ u8 mHoldZ;
    /* 0x1AD */ u8 mTrigZ;
    /* 0x1AE */ u8 m1AE;
    /* 0x1AF */ u8 m1AF[0x1B0 - 0x1AF];
    /* 0x1B0 */ dCamForcusLine mForcusLine;
    /* 0x220 */ u8 m220;
    /* 0x221 */ u8 m221[0x224 - 0x221];
    /* 0x224 */ cSAngle m224;
    /* 0x226 */ u8 m226[0x228 - 0x226];
    /* 0x228 */ cXyz mMonitorPos;
    /* 0x234 */ f32 m234;
    /* 0x238 */ f32 m238;
    /* 0x23C */ f32 m23C;
    /* 0x240 */ int m240;
    /* 0x244 */ f32 m244;
    /* 0x248 */ int m248[3];
    /* 0x254 */ int m254;
    /* 0x258 */ int m258;
    /* 0x25C */ BG mBG;
    /* 0x30C */ u8 m30C[0x310 - 0x30C];
    /* 0x310 */ f32 m310;
    /* 0x314 */ u8 m314[0x318 - 0x314];
    /* 0x318 */ f32 m318;
    /* 0x31C */ u8 m31C;
    /* 0x31D */ u8 m31D;
    /* 0x31E */ u8 m31E[0x320 - 0x31E];
    /* 0x320 */ cXyz m320;
    /* 0x32C */ cXyz m32C;
    /* 0x338 */ s16 m338;
    /* 0x33A */ cSAngle m33A;
    /* 0x33C */ u32 m33C;
    /* 0x340 */ u8 m340[0x350 - 0x340];
    /* 0x350 */ int m350;
    /* 0x354 */ f32 m354;
    /* 0x358 */ int mRoomNo;
    /* 0x35C */ int mRoomMapToolCameraIdx;
    /* 0x360 */ u32 m360;
    /* 0x364 */ u32 m364;
    /* 0x368 */ f32 m368;
    /* 0x36C */ u8 m36C[0x394 - 0x36C];
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
    /* 0x538 */ f32 m538;
    /* 0x53C */ f32 m53C;
    /* 0x540 */ f32 m540;
    /* 0x544 */ u8 m544[0x550 - 0x544];
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
    /* 0x5F4 */ f32 m5F4;
    /* 0x5F8 */ f32 mTrimHeight;
    /* 0x5FC */ int mTrimSize;
    /* 0x600 */ int mTrimTypeForce;
    /* 0x604 */ f32 m604;
    /* 0x608 */ f32 m608;
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
    /* 0x780 */ u8 m780;
    /* 0x781 */ u8 m781;
    /* 0x782 */ u8 m782;
    /* 0x783 */ u8 m783;
    /* 0x784 */ u8 m784;
    /* 0x785 */ u8 m785;
    /* 0x786 */ u8 m786;
    /* 0x787 */ u8 m787;
    /* 0x788 */ u8 m788;
    /* 0x789 */ u8 m789;
    /* 0x78A */ u8 m78A;
    /* 0x78B */ u8 m78B;
    /* 0x78C */ u8 m78C[0x800 - 0x78C];;

public:
    dCamera_c(camera_class*);
    ~dCamera_c();
    void initialize(camera_class*, fopAc_ac_c*, u32, u32);
    void Start();
    void Stop();
    void Stay();
    bool ChangeModeOK(s32);
    void initPad();
    void updatePad();
    void initMonitor();
    void updateMonitor();
    cSAngle calcPeepAngle();
    void Att();
    bool checkForceLockTarget();
    bool Run();
    bool NotRun();
    bool SetTrimSize(s32);
    bool SetTrimTypeForce(s32);
    void CalcTrimSize();
    bool Draw();
    int nextMode(s32);
    bool onModeChange(s32, s32);
    int nextType(s32);
    bool onTypeChange(s32, s32);
    void SetTypeForce(char*, fopAc_ac_c*);
    void SetTypeForce(s32, fopAc_ac_c*);
    bool onStyleChange(s32, s32);
    int GetCameraTypeFromMapToolID(s32, s32);
    int GetCameraTypeFromCameraName(const char*);
    void pushPos();
    cSAngle directionOf(fopAc_ac_c*);
    cXyz positionOf(fopAc_ac_c*);
    cXyz attentionPos(fopAc_ac_c*);
    cXyz relationalPos(fopAc_ac_c*, cXyz*);
    cXyz relationalPos(fopAc_ac_c*, cXyz*, cSAngle);
    cXyz relationalPos(fopAc_ac_c*, fopAc_ac_c*, cXyz*, f32);
    void setDMCAngle();
    cSAngle getDMCAngle(cSAngle);
    void pointInSight(cXyz*);
    void radiusActorInSight(fopAc_ac_c*, fopAc_ac_c*);
    void radiusActorInSight(fopAc_ac_c*, fopAc_ac_c*, cXyz*, cXyz*, f32, s16);
    void groundHeight(cXyz*);
    bool lineBGCheck(cXyz*, cXyz*, dBgS_LinChk*, u32);
    bool lineBGCheck(cXyz*, cXyz*, cXyz*, u32);
    bool lineBGCheck(cXyz*, cXyz*, u32);
    void lineBGCheckBack(cXyz*, cXyz*, u32);
    void lineBGCheckBoth(cXyz*, cXyz*, dBgS_LinChk*, u32);
    void lineCollisionCheckBush(cXyz*, cXyz*);
    void compWallMargin(cXyz*, f32);
    void defaultTriming();
    void setView(f32, f32, f32, f32);
    cSAngle forwardCheckAngle();
    void bumpCheck(u32);
    void getWaterSurfaceHeight(cXyz*);
    void checkSpecialArea();
    void checkGroundInfo();
    bool followCamera2(s32);
    bool followCamera(s32);
    void eyePos(fopAc_ac_c*);
    void heightOf(fopAc_ac_c*);
    bool lockonCamera(s32);
    void getMsgCmdSpeaker();
    void getMsgCmdCut();
    bool talktoCamera(s32);
    void CalcSubjectAngle(s16*, s16*);
    bool subjectCamera(s32);
    bool towerCamera(s32);
    bool crawlCamera(s32);
    bool hookshotCamera(s32);
    bool tornadoCamera(s32);
    bool rideCamera(s32);
    bool hungCamera(s32);
    bool vomitCamera(s32);
    bool shieldCamera(s32);
    bool manualCamera(s32);
    bool nonOwnerCamera(s32);
    bool fixedFrameCamera(s32);
    bool fixedPositionCamera(s32);
    bool eventCamera(s32);
    bool demoCamera(s32);
    bool letCamera(s32);
    void Set(cXyz, cXyz);
    void Set(cXyz, cXyz, f32, s16);
    void Set(cXyz, cXyz, s16, f32);
    void Reset(cXyz, cXyz, f32, s16);
    void Reset(cXyz, cXyz);
    void Reset();
    void ResetView();
    bool Chtyp(s32);
    void U2();
    void shakeCamera();
    void StartShake(s32, u8*, s32, cXyz);
    void StopShake();
    void ResetBlure(int);
    void SetBlureAlpha(f32);
    void SetBlureScale(f32, f32, f32);
    void SetBlureScale(f32);
    void SetBlurePosition(f32, f32, f32);
    void SetBlurePositionType(int);
    void SetBlureTimer(s32);
    void SubjectLockOn(fopAc_ac_c*);
    void SubjectLockOff();
    fopAc_ac_c* GetForceLockOnActor();
    void ForceLockOn(fpc_ProcID);
    void ForceLockOff(fpc_ProcID);
    void SetExtendedPosition(cXyz*);
    void ScopeViewMsgModeOff();

    void Bank() {}
    void Up() {}
    cXyz Center() { return mCenter + mCenterShake; }

    void StartEventCamera(int, int, ...);
    void EndEventCamera(int);
    void searchEventArgData(char*);
    void getEvIntData(int*, char*);
    void getEvStringPntData(char*);
    void getEvIntData(int*, char*, int);
    void getEvFloatData(f32*, char*, f32);
    void getEvXyzData(cXyz*, char*, cXyz);
    void getEvStringData(char*, char*, char*);
    void getEvStringPntData(char*, char*);
    void getEvActor(char*);
    void getEvActor(char*, char*);
    void pauseEvCamera();
    void fixedFrameEvCamera();
    void stokerEvCamera();
    void rollingEvCamera();
    void fixedPositionEvCamera();
    void uniformTransEvCamera();
    void uniformBrakeEvCamera();
    void uniformAcceleEvCamera();
    void watchActorEvCamera();
    void restorePosEvCamera();
    void talktoEvCamera();
    void maptoolIdEvCamera();
    void styleEvCamera();
    void gameOverEvCamera();
    void tactEvCamera();
    void windDirectionEvCamera();
    void turnToActorEvCamera();
    void tornadoWarpEvCamera();
    void saveEvCamera();
    void loadEvCamera();
    void useItem0EvCamera();
    void useItem1EvCamera();
    void getItemEvCamera();
    void possessedEvCamera();
    void fixedFramesEvCamera();
    void bSplineEvCamera();
    void twoActor0EvCamera();

    void CStickUse() { clrFlag(0x800000); }
    void CStickUseless() { setFlag(0x800000); }
    cXyz Eye() { return mEye + mEyeShake; }
    void StickUse() { clrFlag(0x1000000); }
    void StickUseless() { setFlag(0x1000000); }
    void setFlag(u32 flag) { mEventFlags |= flag; }
    bool chkFlag(u32 flag) { return mEventFlags & flag; }
    void clrFlag(u32 flag) { mEventFlags &= ~flag; }

    static engine_fn engine_tbl[];
    static dCamera__Type types[63];
};

STATIC_ASSERT(sizeof(dCamera_c) == 0x800);

class dBgS_CamSphChk {
    ~dBgS_CamSphChk();
};

s16 dCam_getAngleY(camera_class*);
s16 dCam_getAngleX(camera_class*);
s16 dCam_getControledAngleY(camera_class*);
camera_class* dCam_getCamera();
dCamera_c* dCam_getBody();

engine_fn dCamera_c::engine_tbl[] = {
    &dCamera_c::letCamera,
    &dCamera_c::lockonCamera,
    &dCamera_c::talktoCamera,
    &dCamera_c::subjectCamera,
    &dCamera_c::fixedPositionCamera,
    &dCamera_c::fixedFrameCamera,
    &dCamera_c::towerCamera,
    &dCamera_c::rideCamera,
    &dCamera_c::manualCamera,
    &dCamera_c::eventCamera,
    &dCamera_c::hookshotCamera,
    &dCamera_c::followCamera2,
    &dCamera_c::followCamera,
    &dCamera_c::crawlCamera,
    &dCamera_c::tornadoCamera,
    &dCamera_c::hungCamera,
    &dCamera_c::vomitCamera,
    &dCamera_c::shieldCamera,
    &dCamera_c::nonOwnerCamera,
    &dCamera_c::demoCamera
};


namespace {
    static int Stage;
    
    //inline static int get_camera_id(camera_class* i_camera) {
    //    return fopCamM_GetParam(i_camera);
    //}

    inline static u32 check_owner_action(u32 param_0, u32 param_1) {
        return dComIfGp_checkPlayerStatus0(param_0, param_1);
    }
    
    inline static u32 check_owner_action1(u32 param_0, u32 param_1) {
        return dComIfGp_checkPlayerStatus1(param_0, param_1);
    }
    
    inline static void setComStat(u32 param_0) {
        dComIfGp_onCameraAttentionStatus(0, param_0);
    }
    
    inline static void clrComStat(u32 param_0) {
        dComIfGp_offCameraAttentionStatus(0, param_0);
    }

    inline static bool getComStat(u32 param_0) {
        return dComIfGp_getCameraAttentionStatus(0) & param_0;
    }
    
    inline static void setComZoomScale(f32 param_0) {
        dComIfGp_setCameraZoomScale(0, param_0);
    }
    
    inline static void setComZoomForcus(f32 param_0) {
        dComIfGp_setCameraZoomForcus(0, param_0);
    } 
}  // namespace

#endif /* D_CAMERA_H */
