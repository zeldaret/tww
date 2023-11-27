#ifndef D_A_NPC_OS_H
#define D_A_NPC_OS_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"
#include "d/actor/d_a_pedestal.h"

class mDoExt_McaMorf;

class daNpc_Os_c : public fopAc_ac_c {
public:
    void chkNpcAction(int (daNpc_Os_c::*)(void*)) {}
    void chkPlayerAction(int (daNpc_Os_c::*)(void*)) {}
    void clearStatus() {}
    void getAttentionBasePos() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getBaseAnimeFrame() {}
    void getBaseAnimeFrameRate() {}
    void getCattleRoomNo() {}
    void getEyePos() {}
    void getGroundY() {}
    void getHead_x() {}
    void getHead_y() {}
    void getLeftHandMatrix() {}
    void getRightHandMatrix() {}
    void incAttnSetCount() {}
    void isFinish() {}
    void isGravity() {}
    void isPlayerRoom(int) {}
    void isPlayerRoom_Goat() {}
    void isSetHomePos() {}
    void isWaterHit() {}
    void offGravity() {}
    void offPlayerRoom(int) {}
    void onFinish() {}
    void onGravity() {}
    void onPlayerRoom(int) {}
    void onSetHomePos() {}
    void onWaterHit() {}
    void setCattleRoomNo(signed char) {}

    s32 create();
    void createHeap();
    void jointCheck(signed char);
    void wakeupCheck();
    void setWakeup();
    void finishCheck();
    void setFinish();
    void getWakeupOrderEventNum();
    void getFinishOrderEventNum();
    void getMyStaffId();
    void getRestartNumber();
    void checkGoalRoom();
    void checkPlayerRoom();
    void eventOrderCheck();
    void makeBeam(int);
    void endBeam();
    void wallHitCheck();
    void walkProc(float, short);
    void setAction(int (daNpc_Os_c::**)(void*), int (daNpc_Os_c::*)(void*), void*);
    void npcAction(void*);
    void setNpcAction(int (daNpc_Os_c::*)(void*), void*);
    void playerAction(void*);
    void setPlayerAction(int (daNpc_Os_c::*)(void*), void*);
    void getStickAngY();
    void calcStickPos(short, cXyz*);
    void returnLinkPlayer();
    void returnLinkCheck();
    void waitNpcAction(void*);
    void finish01NpcAction(void*);
    void finish02NpcAction(void*);
    void talkNpcAction(void*);
    void carryNpcAction(void*);
    void throwNpcAction(void*);
    void jumpNpcAction(void*);
    void routeAngCheck(cXyz&, short*);
    void routeWallCheck(cXyz&, cXyz&, short*);
    void checkForwardGroundY(short);
    void checkWallJump(short);
    void routeCheck(float, short*);
    void searchNpcAction(void*);
    void waitPlayerAction(void*);
    void walkPlayerAction(void*);
    void eventProc();
    void initialDefault(int);
    void actionDefault(int);
    void initialWaitEvent(int);
    void actionWaitEvent(int);
    void initialWakeupEvent(int);
    void actionWakeupEvent(int);
    void initialMoveEvent(int);
    void actionMoveEvent(int);
    void initialMoveEndEvent(int);
    void initialEndEvent(int);
    void initialTurnEvent(int);
    void actionTurnEvent(int);
    void initialFinishEvent(int);
    void actionFinishEvent(int);
    void initialMsgSetEvent(int);
    void actionMsgSetEvent(int);
    void actionMsgEndEvent(int);
    void initialSwitchOnEvent(int);
    void initialNextEvent(int);
    void initialSaveEvent(int);
    void talk_init();
    void talk();
    void setAnm(int);
    void dNpc_Os_setAnm(mDoExt_McaMorf*, int, float, float, int, const char*);
    void initBrkAnm(unsigned char, bool);
    void playBrkAnm();
    void setAnm_brkAnm(int);
    void chkAttention(cXyz, short);
    void chkArea(cXyz*);
    void carryCheck();
    void eventOrder();
    void checkOrder();
    void checkCommandTalk();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void setAttention(bool);
    void lookBack(int, int, int);
    void setBaseMtx();
    void init();
    BOOL draw();
    void animationPlay();
    void smokeSet(unsigned short);
    BOOL execute();

public:
    /* 0x4EC */ request_of_phase_process_class mPhs;
    /* 0x4F4 */ mDoExt_McaMorf* m4F4;
    /* 0x4F8 */ daPedestal::daPds_c* mpPedestal;
    /* 0x4FC */ u8 m4FC[0x518 - 0x4FC];
    /* 0x518 */ dBgS_AcchCir mAcchCir1;
    /* 0x558 */ dBgS_AcchCir mAcchCir2;
    /* 0x598 */ u8 m598[0x704 - 0x598];
    /* 0x704 */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x738 */ u8 m738[0x784 - 0x738];
    /* 0x784 */ u32 m784;
    /* 0x788 */ u8 m788[0x798 - 0x788];
    /* 0x798 */ s16 m798;
    /* 0x79A */ u8 m79A[0x79C - 0x79A];
    /* 0x79C */ u8 mTuno1JointIdx;
    /* 0x79D */ u8 mTuno2JointIdx;
    /* 0x79E */ u8 mTuno3JointIdx;
    /* 0x79F */ u8 m79F[0x7A2 - 0x79F];
    /* 0x7A2 */ u8 m7A2;
    /* 0x7A3 */ u8 m7A3;
    /* 0x7A4 */ u8 m7A4[0x7A8 - 0x7A4];
    /* 0x7A8 */ u8 m7A8;
    /* 0x7A9 */ u8 m7A9[0x7FC - 0x7A9];
    /* 0x7FC */ cBgS_PolyInfo m7FC;
};

#endif /* D_A_NPC_OS_H */
