#ifndef D_A_NPC_OS_H
#define D_A_NPC_OS_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"
#include "d/actor/d_a_player_npc.h"
#include "d/actor/d_a_pedestal.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_hostIO.h"

class mDoExt_McaMorf;

class daNpc_Os_infiniteEcallBack_c : public dPa_levelEcallBack {
public:
    void end();
    void makeEmitter(u16, const cXyz*, const csXyz*, const cXyz*);
    void execute(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);

    JPABaseEmitter* getEmitter() { return mpBaseEmitter; }

private:
    /* 0x04 */ JPABaseEmitter* mpBaseEmitter;
}; // Size: 0x08

class daNpc_Os_c : public daPy_npc_c {
public:
    typedef int(daNpc_Os_c::*ActionFunc_t)(void*);

    daNpc_Os_c() {}
    ~daNpc_Os_c();
    BOOL chkNpcAction(ActionFunc_t action) {
        return mNpcAction == action;
    }
    BOOL chkPlayerAction(ActionFunc_t action) {
        return mPlayerAction == action;
    }
    void clearStatus() { field_0x784 = 0; }
    cXyz& getAttentionBasePos() { return field_0x754; }
    s16 getBackbone_x() { return mJntCtrl.getBackbone_x(); }
    s16 getBackbone_y() { return mJntCtrl.getBackbone_y(); }
    f32 getBaseAnimeFrame() { return 0.0f; }
    f32 getBaseAnimeFrameRate() { return 1.0f; }
    s8 getCattleRoomNo() { return m_cattleRoomNo; }
    cXyz& getEyePos() { return field_0x748; }
    f32 getGroundY() { return mAcch.GetGroundH(); }
    s16 getHead_x() { return mJntCtrl.getHead_x(); }
    s16 getHead_y() { return mJntCtrl.getHead_y(); }
    MtxP getLeftHandMatrix() { return cullMtx; }
    MtxP getRightHandMatrix() { return cullMtx; }
    void incAttnSetCount() {
        if(field_0x7A3 != 0xFF) {
            field_0x7A3 += 1;
        }
    }
    BOOL isFinish() { return cLib_checkBit(field_0x784, 0x1UL); }
    void onFinish() { cLib_onBit(field_0x784, 0x1UL); }
    BOOL isSetHomePos() { return cLib_checkBit(field_0x784, 0x2UL); }
    void onSetHomePos() { cLib_onBit(field_0x784, 0x2UL); }
    BOOL isWaterHit() { return cLib_checkBit(field_0x784, 0x4UL); }
    void onWaterHit() { cLib_onBit(field_0x784, 0x4UL); }
    BOOL isGravity() { return cLib_checkBit(field_0x784, 0x8UL); }
    void onGravity() { cLib_onBit(field_0x784, 0x8UL); }
    void offGravity() { cLib_offBit(field_0x784, 0x8UL); }
    // Note: The 0x10 bit is used in the final release, but not in the demo debug maps, so its official name is unknown.
    void offPlayerRoom(int idx) { m_playerRoom[idx] = false; }
    void onPlayerRoom(int idx) { m_playerRoom[idx] = true; }
    void setCattleRoomNo(s8 roomNo) { m_cattleRoomNo = roomNo; }

    static bool isPlayerRoom(int idx) { return m_playerRoom[idx]; }
    static bool isPlayerRoom_Goat() { return isPlayerRoom(1); }

    s32 create();
    BOOL createHeap();
    BOOL jointCheck(s8);
    BOOL wakeupCheck();
    void setWakeup();
    BOOL finishCheck();
    void setFinish();
    s8 getWakeupOrderEventNum();
    s8 getFinishOrderEventNum();
    int getMyStaffId();
    s8 getRestartNumber();
    BOOL checkGoalRoom();
    void checkPlayerRoom();
    void eventOrderCheck();
    void makeBeam(int);
    void endBeam();
    s32 wallHitCheck();
    void walkProc(f32, s16);
    BOOL setAction(ActionFunc_t*, ActionFunc_t, void*);
    void npcAction(void*);
    void setNpcAction(ActionFunc_t, void*);
    void playerAction(void*);
    void setPlayerAction(ActionFunc_t, void*);
    s16 getStickAngY();
    int calcStickPos(s16, cXyz*);
    void returnLinkPlayer();
    BOOL returnLinkCheck();
    BOOL waitNpcAction(void*);
    BOOL finish01NpcAction(void*);
    BOOL finish02NpcAction(void*);
    BOOL talkNpcAction(void*);
    BOOL carryNpcAction(void*);
    BOOL throwNpcAction(void*);
    BOOL jumpNpcAction(void*);
    void routeAngCheck(cXyz&, s16*);
    void routeWallCheck(cXyz&, cXyz&, s16*);
    f32 checkForwardGroundY(s16);
    f32 checkWallJump(s16);
    BOOL routeCheck(f32, s16*);
    BOOL searchNpcAction(void*);
    BOOL waitPlayerAction(void*);
    BOOL walkPlayerAction(void*);
    BOOL eventProc();
    void initialDefault(int);
    BOOL actionDefault(int);
    void initialWaitEvent(int);
    BOOL actionWaitEvent(int);
    void initialWakeupEvent(int);
    BOOL actionWakeupEvent(int);
    void initialMoveEvent(int);
    BOOL actionMoveEvent(int);
    void initialMoveEndEvent(int);
    void initialEndEvent(int);
    void initialTurnEvent(int);
    BOOL actionTurnEvent(int);
    void initialFinishEvent(int);
    BOOL actionFinishEvent(int);
    void initialMsgSetEvent(int);
    BOOL actionMsgSetEvent(int);
    BOOL actionMsgEndEvent(int);
    void initialSwitchOnEvent(int);
    void initialNextEvent(int);
    void initialSaveEvent(int);
    BOOL talk_init();
    BOOL talk();
    void setAnm(int);
    BOOL dNpc_Os_setAnm(mDoExt_McaMorf*, int, f32, f32, int, const char*);
    BOOL initBrkAnm(u8, bool);
    void playBrkAnm();
    void setAnm_brkAnm(int);
    BOOL chkAttention(cXyz, s16);
    bool chkArea(cXyz*);
    void carryCheck();
    void eventOrder();
    void checkOrder();
    BOOL checkCommandTalk();
    u16 next_msgStatus(u32* pMsgNo);
    u32 getMsg();
    void setCollision();
    void setAttention(bool);
    void lookBack(int, int, int);
    void setBaseMtx();
    BOOL init();
    BOOL draw();
    void animationPlay();
    void smokeSet(u16);
    BOOL execute();

    static bool m_playerRoom[];
    static s8 m_cattleRoomNo;
    static dPa_smokeEcallBack m_smoke;
    static dKy_tevstr_c m_smoke_tevstr;

private:
    /* 0x4EC */ request_of_phase_process_class mPhs;
    /* 0x4F4 */ mDoExt_McaMorf* mpMorf;
    /* 0x4F8 */ daPedestal::daPds_c* mpPedestal;
    /* 0x4FC */ mDoExt_brkAnm mBrkAnm;
    /* 0x514 */ u32 mShadowId;
    /* 0x518 */ dBgS_AcchCir mAcchCir[2];
    /* 0x598 */ dCcD_Stts mStts;
    /* 0x5D4 */ dCcD_Cyl mCyl;
    /* 0x704 */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x738 */ daNpc_Os_infiniteEcallBack_c field_0x738;
    /* 0x740 */ daNpc_Os_infiniteEcallBack_c field_0x740;
    /* 0x748 */ cXyz field_0x748;
    /* 0x754 */ cXyz field_0x754;
    /* 0x760 */ f32 mPrevMorfFrame;
    /* 0x764 */ f32 field_0x764;
    /* 0x768 */ ActionFunc_t mPlayerAction;
    /* 0x774 */ ActionFunc_t mNpcAction;
    /* 0x780 */ u32 field_0x780;
    /* 0x784 */ u32 field_0x784;
    /* 0x788 */ f32 field_0x788;
    /* 0x78C */ s32 field_0x78C;
    /* 0x790 */ u8 field_0x790[0x794 - 0x790];
    /* 0x794 */ u32 field_0x794;
    /* 0x798 */ s16 field_0x798;
    /* 0x79A */ u8 field_0x79A[0x79C - 0x79A];
    /* 0x79C */ s8 mTuno1JointIdx;
    /* 0x79D */ s8 mTuno2JointIdx;
    /* 0x79E */ s8 mTuno3JointIdx;
    /* 0x79F */ s8 mReachedAnimEnd;
    /* 0x7A0 */ s8 field_0x7A0;
    /* 0x7A0 */ s8 field_0x7A1;
    /* 0x7A2 */ s8 field_0x7A2;
    /* 0x7A3 */ u8 field_0x7A3;
    /* 0x7A4 */ u8 field_0x7A4;
    /* 0x7A5 */ s8 field_0x7A5;
    /* 0x7A6 */ s8 field_0x7A6;
    /* 0x7A7 */ u8 field_0x7A7;
    /* 0x7A8 */ u8 field_0x7A8;
    /* 0x7A9 */ s8 field_0x7A9;
    /* 0x7AA */ s8 field_0x7AA;
    /* 0x7AB */ u8 field_0x7AB;
    /* 0x7AC */ s16 field_0x7AC;
    /* 0x7AE */ s16 field_0x7AE;
    /* 0x7B0 */ s16 field_0x7B0;
    /* 0x7B2 */ s16 field_0x7B2;
    /* 0x7B4 */ s16 field_0x7B4;
    /* 0x7B6 */ s16 field_0x7B6;
    /* 0x7B8 */ f32 field_0x7B8;
    /* 0x7BC */ s16 field_0x7BC;
    /* 0x7BE */ s16 field_0x7BE;
    /* 0x7C0 */ s16 field_0x7C0;
    /* 0x7C2 */ s16 field_0x7C2;
    /* 0x7C4 */ s16 field_0x7C4[0x10];
    /* 0x7E4 */ cXyz field_0x7E4;
    /* 0x7F0 */ cXyz field_0x7F0;
    /* 0x7FC */ cBgS_PolyInfo field_0x7FC;
}; // Size: 0x80C

class daNpc_Os_HIO2_c : public JORReflexible {
public:
    daNpc_Os_HIO2_c();
    virtual ~daNpc_Os_HIO2_c() {}

public:
    /* 0x00 - vtable */

    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ s16 field_0x26;
    /* 0x28 */ s16 field_0x28;
}; // Size: 0x2A

class daNpc_Os_HIO_c : public JORReflexible {
public:
    daNpc_Os_HIO_c();
    virtual ~daNpc_Os_HIO_c() {}

public:
    /* 0x00 - vtable*/

    /* 0x04 */ s8 field_0x04;

    /* 0x08 */ daNpc_Os_HIO2_c mOs2;
    /* 0x34 */ dNpc_HIO_c mNpc;

    /* 0x5C */ daNpc_Os_c* field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ f32 field_0x98;
    /* 0x9C */ f32 field_0x9C;
    /* 0xA0 */ f32 field_0xA0;
    /* 0xA4 */ f32 field_0xA4;
    /* 0xA8 */ f32 field_0xA8;
    /* 0xAC */ f32 field_0xAC;
    /* 0xB0 */ f32 field_0xB0;
}; // Size: 0xB4

#endif /* D_A_NPC_OS_H */
