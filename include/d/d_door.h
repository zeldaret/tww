#ifndef D_DOOR_H
#define D_DOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

class msg_class;

class dDoor_info_c : public fopAc_ac_c {
public:
    BOOL valShipId() { return getShipId() != 0x3F; }

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
    u8 getViewRoomNo();
    s32 frontCheckOld();
    s32 frontCheck();
    s32 drawCheck_local();
    s32 drawCheck(int);
    s32 checkExecute();
    void startDemoProc();
    void makeEventId(int);
    void initProc(int);
    void initOpenDemo(int);
    BOOL checkArea(f32, f32, f32);
    void openInitCom(int);
    void openProcCom();
    void closeEndCom();
    s32 getDemoAction();
    void setGoal();
    void setPlayerAngle(int);
    void setPosAndAngle(cXyz*, s16);

public:
    /* 0x290 */ s8 mRoomNo2;
    /* 0x291 */ u8 mFromRoomNo;
    /* 0x292 */ u8 mToRoomNo;
    /* 0x293 */ u8 m293[0x294 - 0x293];
    /* 0x294 */ cXyz mAngleVec;
    /* 0x2A0 */ u8 mFrontCheck;
    /* 0x2A1 */ u8 m2A1;
    /* 0x2A2 */ s16 mEventIdx[12];
    /* 0x2BA */ u8 mToolId[12];
    /* 0x2C6 */ u8 m2C6;
    /* 0x2C7 */ u8 m2C7;
    /* 0x2C8 */ int mStaffId;
    /* 0x2CC */ s8 mRoomNo;
    /* 0x2CD */ u8 m2CD[0x2D0 - 0x2CD];
};  // Size: 0x2D0

class dDoor_smoke_c {
public:
    void smokeInit(dDoor_info_c*);
    void smokeProc(dDoor_info_c*);
    void smokeEnd();

public:
    /* 0x00 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x22 */ csXyz mRot;
    /* 0x28 */ cXyz mPos;
    /* 0x34 */ u8 m34;
    /* 0x35 */ u8 m35;
};

class dDoor_key2_c {
public:
    cPhs_State keyResLoad();
    void keyResDelete();
    void keyInit(dDoor_info_c*);
    BOOL keyProc();
    BOOL keyCreate_Nkey();
    BOOL keyCreate_Bkey();
    BOOL keyCreate(int);
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
    dDoor_stop_c() {}
    ~dDoor_stop_c() {}

    void calcMtx(dDoor_info_c*);
    void closeInit(dDoor_info_c*);
    s32 closeProc(dDoor_info_c*);
    void openInit(dDoor_info_c*);
    s32 openProc(dDoor_info_c*);
    BOOL create();

public:
    /* 0x0 */ J3DModel* mpModel;
    /* 0x4 */ f32 mOffsY;
    /* 0x8 */ u8 m8;
    /* 0x9 */ u8 mFrontCheck;
    /* 0xA */ u8 mA;
    /* 0xB */ u8 mB;
};

class dDoor_msg_c {
public:
    void init(s16);
    BOOL proc(cXyz*);

public:
    /* 0x0 */ fpc_ProcID mMsgPId;
    /* 0x4 */ msg_class* m_msg;
    /* 0x8 */ u8 mState;
    /* 0xA */ s16 mMsgId;
};

class dDoor_hkyo_c {
public:
    dDoor_hkyo_c() {}
    ~dDoor_hkyo_c() {}

    bool chkUse() { return m11 != 0; }
    void offUse() { m11 = 0; }
    void onUse(u8 arg0) { m11 = arg0; }

    cPhs_State resLoad();
    void resDelete();
    BOOL create();
    void setAnm(u8);
    void init();
    void calcMtx(dDoor_info_c*, f32);
    void draw(dDoor_info_c*);
    void proc(dDoor_info_c*);
    BOOL chkFirst();
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
