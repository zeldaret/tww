#ifndef D_DOOR_H
#define D_DOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

class dDoor_info_c : public fopAc_ac_c {
public:
    void valShipId() {}

    u8 getSwbit();
    u8 getSwbit2();
    u8 getType();
    void setType(u8);
    u8 getEventNo();
    u8 getFRoomNo();
    u8 getBRoomNo();
    u8 getShipId();
    u8 getArg1();
    BOOL adjoinPlayer();
    void getViewRoomNo();
    void frontCheckOld();
    void frontCheck();
    void drawCheck_local();
    void drawCheck(int);
    void checkExecute();
    void startDemoProc();
    void makeEventId(int);
    void initProc(int);
    void initOpenDemo(int);
    void checkArea(f32, f32, f32);
    void openInitCom(int);
    void openProcCom();
    void closeEndCom();
    void getDemoAction();
    void setGoal();
    void setPlayerAngle(int);
    void setPosAndAngle(cXyz*, s16);

public:
    /* 0x290 */ u8 mRoomNo2;
    /* 0x291 */ u8 mFRoomNo;
    /* 0x292 */ u8 mBRoomNo;
    /* 0x293 */ u8 m293[0x294 - 0x293];
    /* 0x294 */ cXyz mAngleVec;
    /* 0x2A0 */ u8 mFrontCheck;
    /* 0x2A1 */ u8 m2A1;
    /* 0x2A2 */ u8 m2A2[0x2A4 - 0x2A2];
    /* 0x2A4 */ void* m2A4;
    /* 0x2A8 */ s16 m2A8;
    /* 0x2AA */ u8 m2AA[0x2AC - 0x2AA];
    /* 0x2AC */ void* m2AC;
    /* 0x2B0 */ void* m2B0;
    /* 0x2B4 */ void* m2B4;
    /* 0x2B8 */ void* m2B8;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 m2BE[0x2C0 - 0x2BE];
    /* 0x2C0 */ void* m2C0;
    /* 0x2C4 */ void* m2C4;
    /* 0x2C8 */ int mStaffId;
    /* 0x2CC */ u8 mRoomNo;
    /* 0x2CD */ u8 m2CD[0x2D0 - 0x2CD];
};

class dDoor_smoke_c {
public:
    void smokeInit(dDoor_info_c*);
    void smokeProc(dDoor_info_c*);
    void smokeEnd();

public:
    /* 0x00 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x04 */ u8 m04[0x22 - 0x04];
    /* 0x22 */ s16 m22;
    /* 0x24 */ u8 m24[0x28 - 0x24];
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ s8 m34;
    /* 0x35 */ u8 m35;
};

class dDoor_key2_c {
public:
    void keyResLoad();
    void keyResDelete();
    void keyInit(dDoor_info_c*);
    void keyProc();
    void keyCreate_Nkey();
    void keyCreate_Bkey();
    void keyCreate(int);
    void keyOn();
    void keyOff();
    void calcMtx(dDoor_info_c*);
    void draw(dDoor_info_c*);

public:
    /* 0x00 */ bool mbEnabled;
    /* 0x01 */ u8 m01[0x04 - 0x01];
    /* 0x04 */ J3DModel* mpModel;
    /* 0x08 */ mDoExt_bckAnm mBckAnim;
    /* 0x18 */ request_of_phase_process_class mPhs;
    /* 0x20 */ u8 m20;
    /* 0x21 */ u8 mbIsBossDoor;
    /* 0x22 */ u8 m22[0x24 - 0x22];
};

class dDoor_stop_c {
public:
    void calcMtx(dDoor_info_c*);
    void closeInit(dDoor_info_c*);
    void closeProc(dDoor_info_c*);
    void openInit(dDoor_info_c*);
    void openProc(dDoor_info_c*);
    void create();

public:
    /* 0x0 */ J3DModel* mpModel;
    /* 0x4 */ f32 m4;
    /* 0x8 */ u8 m8;
    /* 0x9 */ u8 mFrontCheck;
    /* 0xA */ u8 mA;
    /* 0xB */ u8 mB;
};

class dDoor_msg_c {
public:
    void init(s16);
    void proc(cXyz*);

public:
    /* 0x0 */ u32 m0;
    /* 0x4 */ int mMsg;
    /* 0x8 */ s8 m8;
    /* 0x9 */ u8 m9[0xA - 0x9];
    /* 0xA */ s16 mA;
};

class dDoor_hkyo_c {
public:
    void chkUse() {}
    void offUse() {}
    void onUse(u8) {}

    s32 resLoad();
    void resDelete();
    void create();
    void setAnm(u8);
    void init();
    void calcMtx(dDoor_info_c*, f32);
    void draw(dDoor_info_c*);
    void proc(dDoor_info_c*);
    void chkFirst();
    void onFirst();
    BOOL chkStart();

public:
    /* 0x00 */ request_of_phase_process_class mPhs;
    /* 0x08 */ J3DModel* mpModel;
    /* 0x0C */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x10 */ u8 mAnmIdx;
    /* 0x11 */ u8 m11;
    /* 0x12 */ u8 m12[0x14 - 0x12];
};

#endif /* D_DOOR_H */
