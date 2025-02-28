#ifndef D_A_SHIP_H
#define D_A_SHIP_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_msg.h"
#include "d/actor/d_a_grid.h"

class daShip_c : public fopAc_ac_c {
public:
    enum daSHIP_SFLG {
        daSFLG_HEAD_NO_DRAW_e = 0x00200000,
    };
    
    bool checkStateFlg(daSHIP_SFLG flag) const { return m0358 & flag; }
    bool checkHeadNoDraw() const { return checkStateFlg(daSFLG_HEAD_NO_DRAW_e); }
    
    int getTactWarpPosNum() const { return mTactWarpPosNum; }
    void setTactWarpPosNum(int num) { mTactWarpPosNum = num; }
    u32 getTactWarpID() { return mTactWarpID; }
    void setTactWarpID(u32 warpID) { mTactWarpID = warpID; }
    
    bool unknown_inline_TODO() const { return mTornadoActor || m0424; }
    
    void checkCraneMode() const {}
    void checkCraneUpEnd() const {}
    void checkForceMove() {}
    void checkJumpOkFlg() const {}
    void checkRopeCntMax() const {}
    void checkRopeDownStart() const {}
    void checkSalvageDemo() const {}
    void checkShootCannon() const {}
    void checkTornadoFlg() const {}
    void checkTornadoUp() const {}
    void getBeltSpeed() const {}
    void getBodyMtx() {}
    void getCannonAngleX() const {}
    void getCannonAngleY() const {}
    void getCraneAngle() const {}
    void getCraneBaseAngle() const {}
    void getCraneHookAngleY() const {}
    void getCraneRipplePosX() const {}
    void getCraneRipplePosY() const {}
    void getCraneRipplePosZ() const {}
    void getCraneTop() {}
    void getFlyFlg() {}
    void getHeadJntMtx() {}
    void getJumpFlg() const {}
    void getJumpRate() {}
    void getLandFlg() const {}
    void getPart() const {}
    void getRopeCnt() const {}
    void getSailAngle() {}
    void getSailOn() {}
    void getTactJntMtx() {}
    void getTillerAngleRate() {}
    void getTillerTopPosP() {}
    fopAc_ac_c* getTornadoActor() { return mTornadoActor; }
    void getWhirlActor() {}
    void offCraneHookFlg() {}
    void offFantomGanonBattle() {}
    void offStateFlg(daSHIP_SFLG) {}
    void offTornadoFlg() {
        mTornadoID = fpcM_ERROR_PROCESS_ID_e;
        mTornadoActor = NULL;
    }
    void offWhirlFlg() {}
    void onCb1Ride() {}
    void onCraneHookFlg() {}
    void onCrashFlg() {}
    void onFantomGanonBattle() {}
    void onJumpRideFlg() {}
    void onLinkSit() {}
    void onSceneChange() {}
    void onShortHitFlg() {}
    void onStateFlg(daSHIP_SFLG) {}
    void onTornadoFlg(u32 tornadoID) { mTornadoID = tornadoID; }
    void onWhirlFlg(unsigned long, short) {}
    void onWhirlFlgDirect(unsigned long, short) {}
    void setAtnPos(const cXyz*) {}
    void setCannon() {}
    void setCrane() {}
    void setGetOffFirst() {}
    void setGetOffSecond() {}
    void setPaddleMove() {}
    void setReadyFirst() {}
    void setReadySecond() {}
    void setStartModeThrow() {}
    void setStartModeWarp() {}
    void setSteerMove() {}
    void setTactWarp() {}

    void bodyJointCallBack(int);
    void cannonJointCallBack(int);
    void craneJointCallBack();
    void headJointCallBack0();
    void headJointCallBack1(int);
    BOOL draw();
    void checkForceMessage();
    void setInitMessage();
    void setNextMessage(msg_class*);
    void seStart(u32, cXyz*);
    void setSailAngle();
    void setControllAngle(s16);
    void getMaxWaterY(cXyz*);
    void setWaveAngle(s16*, s16*);
    void getWaterY();
    void setYPos();
    void checkOutRange();
    void decrementShipSpeed(f32);
    void firstDecrementShipSpeed(f32);
    void getAimControllAngle(s16);
    void setMoveAngle(s16);
    void changeDemoEndProc();
    void setCrashData(s16);
    void checkNextMode(int);
    void setPartOnAnime(u8);
    void setPartOffAnime();
    void setPartAnimeInit(u8);
    void setSelfMove(int);
    void procWait_init();
    void procWait();
    void procReady_init();
    void procReady();
    void procGetOff_init();
    void procGetOff();
    void procPaddleMove_init();
    void procPaddleMove();
    void procSteerMove_init();
    void procSteerMove();
    void procCannonReady_init();
    void procCannonReady();
    void procCannon_init();
    void procCannon();
    void procCraneReady_init();
    void procCraneReady();
    void procCrane_init();
    void procCrane();
    void procCraneUp_init();
    void procCraneUp();
    void procToolDemo_init();
    void procToolDemo();
    void procZevDemo_init();
    void procZevDemo();
    void procTalkReady_init();
    void procTalkReady();
    void procTalk_init();
    void procTalk();
    void procTurn_init();
    void procTurn();
    void procTornadoUp_init();
    void procTornadoUp();
    void procStartModeWarp_init();
    void procStartModeWarp();
    void procTactWarp_init();
    void procTactWarp();
    void procWhirlDown_init();
    void procWhirlDown();
    void procStartModeThrow_init();
    void procStartModeThrow();
    void setEffectData(f32, s16);
    void setRoomInfo();
    void incRopeCnt(int, int);
    void setRopePos();
    void getAnglePartRate();
    void setTornadoActor();
    void setWhirlActor();
    void setHeadAnm();
    BOOL execute();
    void shipDelete();
    void createHeap();
    s32 create();
    void checkForceMove() const;
    void initStartPos(cXyz const*, s16);

public:
    /* 0x0290 */ request_of_phase_process_class mPhs;
    /* 0x0298 */ mDoExt_McaMorf* m0298;
    /* 0x029C */ mDoExt_McaMorf* m029C;
    /* 0x02A0 */ u8 m02A0[0x02A8 - 0x02A0];
    /* 0x02A8 */ Mtx m02A8;
    /* 0x02D8 */ u8 m02D8[0x02EC - 0x02D8];
    /* 0x02EC */ J3DFrameCtrl mFrameCtrl;
    /* 0x0300 */ J3DModel* mpCannonModel;
    /* 0x0304 */ J3DModel* mpSalvageArmModel;
    /* 0x0308 */ J3DModel* m0308;
    /* 0x030C */ mDoExt_3DlineMat1_c mRopeLine;
    /* 0x0348 */ u8 m0348[0x034D - 0x0348];
    /* 0x034D */ u8 m034D;
    /* 0x034E */ u8 mShipMode;
    /* 0x034F */ u8 m034F[0x0354 - 0x034F];
    /* 0x0354 */ int mEvtStaffId;
    /* 0x0358 */ u32 m0358;
    /* 0x035C */ int mNextMessageID;
    /* 0x0360 */ u32 mShadowId;
    /* 0x0364 */ u8 m0364[0x036C - 0x0364];
    /* 0x036C */ s16 m036C;
    /* 0x036E */ u8 m036E[0x0370 - 0x036E];
    /* 0x0370 */ s16 m0370;
    /* 0x0372 */ s16 m0372;
    /* 0x0374 */ u8 m0374[0x037A - 0x0374];
    /* 0x037A */ s16 m037A;
    /* 0x037C */ s16 m037C;
    /* 0x037E */ s16 m037E;
    /* 0x0380 */ u8 m0380[0x0384 - 0x0380];
    /* 0x0384 */ s16 m0384;
    /* 0x0386 */ s16 m0386;
    /* 0x0388 */ s16 m0388;
    /* 0x038A */ u8 m038A[0x0392 - 0x038A];
    /* 0x0392 */ s16 m0392;
    /* 0x0394 */ s16 m0394;
    /* 0x0396 */ s16 m0396;
    /* 0x0398 */ s16 m0398;
    /* 0x039A */ s16 m039A;
    /* 0x039C */ s16 m039C;
    /* 0x039E */ u16 m039E;
    /* 0x03A0 */ u8 m03A0[0x03A4 - 0x03A0];
    /* 0x03A4 */ s16 mStickMAng;
    /* 0x03A6 */ u8 m03A6[0x03B4 - 0x03A6];
    /* 0x03B4 */ s16 m03B4;
    /* 0x03B6 */ u8 m03B6[0x03B8 - 0x03B6];
    /* 0x03B8 */ s16 m03B8;
    /* 0x03BA */ u8 m03BA[0x03C8 - 0x03BA];
    /* 0x03C8 */ int mTactWarpPosNum;
    /* 0x03CC */ int m03CC;
    /* 0x03D0 */ u8 m03D0[0x03D8 - 0x03D0];
    /* 0x03D8 */ f32 m03D8;
    /* 0x03DC */ u8 m03DC[0x03E8 - 0x03DC];
    /* 0x03E8 */ f32 m03E8;
    /* 0x03EC */ f32 mStickMVal;
    /* 0x03F0 */ u8 m03F0[0x03F4 - 0x03F0];
    /* 0x03F4 */ f32 m03F4;
    /* 0x03F8 */ u8 m03F8[0x03FC - 0x03F8];
    /* 0x03FC */ f32 mFwdVel;
    /* 0x0400 */ f32 m0400;
    /* 0x0404 */ f32 m0404;
    /* 0x0408 */ f32 m0408;
    /* 0x040C */ f32 m040C;
    /* 0x0410 */ int mGridId;
    /* 0x0414 */ daGrid_c* mpGrid;
    /* 0x0418 */ u32 mTornadoID;
    /* 0x041C */ fopAc_ac_c* mTornadoActor;
    /* 0x0420 */ u32 m0420;
    /* 0x0424 */ fopAc_ac_c* m0424;
    /* 0x0428 */ u8 m0428[0x042C - 0x0428];
    /* 0x042C */ u32 mTactWarpID;
    /* 0x0430 */ u8 m0430[0x0434 - 0x0430];
    /* 0x0434 */ cXyz* m0434;
    /* 0x0438 */ cXyz m0438;
    /* 0x0444 */ cXyz m0444;
    /* 0x0450 */ u8 m0450[0x045C - 0x0450];
    /* 0x045C */ cXyz m045C;
    /* 0x0468 */ u8 m0468[0x1044 - 0x0468];
    /* 0x1044 */ cXyz m1044;
    /* 0x1050 */ u8 m1050[0x105C - 0x1050];
    /* 0x105C */ cXyz mEffPos;
    /* 0x1068 */ u8 m1068[0x1180 - 0x1068];
    /* 0x1180 */ dBgS_Acch mAcch;
    /* 0x1344 */ dCcD_Stts mStts;
    /* 0x1380 */ dCcD_Cyl mCyl[3];
    /* 0x1710 */ dCcD_Sph m1710;
    /* 0x183C */ dPa_waveEcallBack mWaveR;
    /* 0x18A0 */ dPa_waveEcallBack mWaveL;
    /* 0x1904 */ dPa_splashEcallBack mSplash;
    /* 0x1920 */ dPa_trackEcallBack mTrack;
    /* 0x1970 */ dPa_rippleEcallBack m1970;
    /* 0x1984 */ dPa_followEcallBack m1984;
    /* 0x1998 */ dPa_followEcallBack m1998;
    /* 0x19AC */ dPa_followEcallBack m19AC;
    /* 0x19C0 */ dPa_rippleEcallBack m19C0;
    /* 0x19D4 */ int (daShip_c::*mProc)();
};

#endif /* D_A_SHIP_H */
