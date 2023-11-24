#ifndef D_A_NPC_CB1_H
#define D_A_NPC_CB1_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daNpc_Cb1_c : public fopAc_ac_c {
public:
    void XyCheckCB(int) {}
    void XyEventCB(int) {}
    void chkNpcAction(int (daNpc_Cb1_c::*)(void*)) {}
    void chkPlayerAction(int (daNpc_Cb1_c::*)(void*)) {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getBaseAnimeFrame() {}
    void getBaseAnimeFrameRate() {}
    void getEyePos() {}
    void getFlyingTimer() {}
    void getGroundY() {}
    void getHead_y() {}
    void getLeftHandMatrix() {}
    void getNusSpeed() {}
    void getNutPos() {}
    void getRightHandMatrix() {}
    void getWork3() {}
    void incAttnSetCount() {}
    void isFlying() {}
    void isMusic() {}
    void isNoCarryAction() {}
    void isNut() {}
    void isPlayerFind() {}
    void isPlayerRoom() {}
    void isShipRide() {}
    void isTact() {}
    void isTactCancel() {}
    void isTactCorrect() {}
    void isTypeBossDie() {}
    void isTypeEkaze() {}
    void isTypeForest() {}
    void isTypeKaze() {}
    void isTypeKazeBoss() {}
    void isTypeWaterFall() {}
    void noCarryAction() {}
    void offFlying() {}
    void offMusic() {}
    void offNoCarryAction() {}
    void offNut() {}
    void offPlayerFind() {}
    void offPlayerRoom() {}
    void offShipRide() {}
    void offTact() {}
    void offTactCancel() {}
    void offTactCorrect() {}
    void onFlying() {}
    void onMusic() {}
    void onNut() {}
    void onPlayerFind() {}
    void onPlayerRoom() {}
    void onShipRide() {}
    void onTact() {}
    void onTactCancel() {}
    void onTactCorrect() {}
    void restartPoint(short) {}
    void setFlyingTimer(short) {}

    void isTagCheckOK();
    void setMessageAnimation(unsigned char);
    void create();
    void createHeap();
    void setAction(int (daNpc_Cb1_c::**)(void*), int (daNpc_Cb1_c::*)(void*), void*);
    void setWaitAction(void*);
    void setWaitNpcAction(void*);
    void npcAction(void*);
    void setNpcAction(int (daNpc_Cb1_c::*)(void*), void*);
    void playerAction(void*);
    void setPlayerAction(int (daNpc_Cb1_c::*)(void*), void*);
    void getStickAngY();
    void calcStickPos(short, cXyz*);
    void flyCheck();
    void checkLanding();
    void breaking();
    void flyAction(int, float, short, int);
    void walkAction(float, float, short);
    void returnLinkPlayer();
    void isFlyAction();
    void sowCheck();
    void shipRideCheck();
    void eventProc();
    void evCheckDisp(int);
    void evInitWait(int);
    void evActWait(int);
    void evInitMsgSet(int);
    void evActMsgSet(int);
    void evInitMsgEnd(int);
    void evActMsgEnd(int);
    void evInitMovePos(int);
    void evActMovePos(int);
    void evInitOffsetLink(int);
    void evActOffsetLink(int);
    void evInitWalk(int);
    void evActWalk(int);
    void evInitToLink(int);
    void evActToLink(int);
    void evInitTact(int);
    void evActTact(int);
    void evInitCelloPlay(int);
    void evActCelloPlay(int);
    void evInitTurn(int);
    void evActTurn(int);
    void evInitSow(int);
    void evActSow(int);
    void evInitSetAnm(int);
    void evActSetAnm(int);
    void evInitSetGoal(int);
    void evActSetGoal(int);
    void evInitWarp(int);
    void evActWarp(int);
    void evInitEnd(int);
    void evActEnd(int);
    void getAnmType(int);
    void initTalk();
    void execTalk(int);
    void waitNpcAction(void*);
    void talkNpcAction(void*);
    void carryNpcAction(void*);
    void flyNpcAction(void*);
    void routeAngCheck(cXyz&, short*);
    void routeWallCheck(cXyz&, cXyz&, short*);
    void checkForwardGroundY(short);
    void checkWallJump(short);
    void chkWallHit();
    void routeCheck(float, short*);
    void searchNpcAction(void*);
    void hitNpcAction(void*);
    void jumpNpcAction(void*);
    void rescueNpcAction(void*);
    void musicNpcAction(void*);
    void shipNpcAction(void*);
    void waitPlayerAction(void*);
    void walkPlayerAction(void*);
    void hitPlayerAction(void*);
    void jumpPlayerAction(void*);
    void flyPlayerAction(void*);
    void carryPlayerAction(void*);
    void calcFlyingTimer();
    void initAnm(signed char, int);
    void musicPlay();
    void musicStop();
    void setAnm(unsigned char);
    void playAnm();
    void chkAttention(float, long);
    void carryCheck();
    void eventOrder();
    void checkOrder();
    void checkCommandTalk();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void lookBack(int);
    void setBaseMtx();
    void init();
    void draw();
    void execute();

public:
    /* 0x4EC */ request_of_phase_process_class m4EC;
    /* 0x4F4 */ mDoExt_McaMorf* mMcaMorf;
    /* 0x4F8 */ u8 m4F8[0x4FC - 0x4F8];
    /* 0x4FC */ J3DModel* mpStickModel;
    /* 0x500 */ J3DModel* mpCelloModel;
    /* 0x504 */ J3DModel* mpFaceModel;
    /* 0x508 */ J3DModel* mpPropellerModel;
    /* 0x50C */ J3DModel* mpNutModel;
    /* 0x510 */ mDoExt_bckAnm mPropellerBckAnim;
    /* 0x520 */ mDoExt_bckAnm mNutBckAnim;
    /* 0x530 */ dBgS_AcchCir mAcchCir1;
    /* 0x570 */ dBgS_AcchCir mAcchCir2;
    /* 0x5B0 */ u8 m5B0[0x5EC - 0x5B0];
    /* 0x5EC */ dCcD_GObjInf m5EC;
    /* 0x6E4 */ u8 m6E4[0x7DC - 0x6E4];
    /* 0x7DC */ cXyz m7DC;
    /* 0x7E8 */ cXyz m7E8;
    /* 0x7F4 */ u8 m7F4[0x8D2 - 0x7F4];
    /* 0x8D2 */ u8 mBackboneIdx;
    /* 0x8D3 */ u8 mArmRendJointIdx;
    /* 0x8D4 */ u8 mArmL2JointIdx;
    /* 0x8D5 */ u8 mNutJointIdx;
    /* 0x8D6 */ u8 mCenterJointIdx;
    /* 0x8D7 */ u8 m8D7[0x8DD - 0x8D7];
    /* 0x8DD */ u8 m8DD;
    /* 0x8DE */ u8 m8DE[0x8E0 - 0x8DE];
    /* 0x8E0 */ u8 m8E0;
    /* 0x8E1 */ u8 m8E1;
    /* 0x8E2 */ u8 m8E2;
    /* 0x8E3 */ u8 m8E3[0x8FC - 0x8E3];
    /* 0x8FC */ f32 m8FC;
    /* 0x900 */ f32 m900;
    /* 0x904 */ u8 m904[0x910 - 0x904];
    /* 0x910 */ cXyz m910;
    /* 0x91C */ cXyz m91C;
    /* 0x928 */ cBgS_PolyInfo m928;
};

#endif /* D_A_NPC_CB1_H */
