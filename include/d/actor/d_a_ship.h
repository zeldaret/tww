#ifndef D_A_SHIP_H
#define D_A_SHIP_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_particle.h"

class msg_class;

class daShip_c : public fopAc_ac_c {
public:
    daShip_c();

    void initStartPos(cXyz const*, s16);
    void bodyJointCallBack(int);
    void cannonJointCallBack(int);
    void craneJointCallBack();
    void headJointCallBack0();
    void headJointCallBack1(int);
    void draw();
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
    void execute();
    void shipDelete();
    void createHeap();
    void create();
    void getCannonAngleX() const;
    void checkForceMove() const;

    /* 0x0290 */ u8 field_0x0290[0x02EC - 0x0290];
    /* 0x02EC */ J3DFrameCtrl mFrameCtrl;
    /* 0x0300 */ J3DModel* mpCannonModel;
    /* 0x0304 */ J3DModel* mpSalvageArmModel;
    /* 0x0308 */ J3DModel* field_0x308;
    /* 0x030C */ mDoExt_3DlineMat1_c mRopeLine;
    /* 0x0348 */ u8 field_0x0348[0x034D - 0x0348];
    /* 0x034D */ u8 field_0x034D;
    /* 0x034E */ u8 mShipMode;
    /* 0x034F */ u8 field_0x034F[0x0358 - 0x034F];
    /* 0x0358 */ u32 field_0x0358;
    /* 0x035C */ int mNextMessageID;
    /* 0x0360 */ int mShadowId;
    /* 0x0364 */ u8 field_0x0364[0x183C - 0x0364];
    /* 0x183C */ dPa_waveEcallBack mWaveL;
    /* 0x187C */ u8 field_0x187C[0x18A0 - 0x187C];
    /* 0x18A0 */ dPa_waveEcallBack mWaveR;
    /* 0x18E0 */ u8 field_0x18E0[0x1904 - 0x18E0];
    /* 0x1904 */ dPa_splashEcallBack mSplash;
    /* 0x1920 */ dPa_trackEcallBack mTrack;
    /* 0x194C */ u8 field_0x194C[0x1970 - 0x194C];
    /* 0x1970 */ dPa_rippleEcallBack field_0x1970;
    /* 0x1984 */ dPa_followEcallBack field_0x1984;
    /* 0x1984 */ dPa_followEcallBack field_0x1998;
    /* 0x1984 */ dPa_followEcallBack field_0x19ac;
    /* 0x19C0 */ dPa_rippleEcallBack field_0x19c0;

};

#endif /* D_A_SHIP_H */
