#ifndef D_A_NPC_P2_H
#define D_A_NPC_P2_H

#include "f_op/f_op_actor.h"

class daNpc_P2_c : public fopAc_ac_c {
public:
    void getAttentionBasePos() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getEyePos() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_P2_c::*)(void*), void*) {}
    void setEyeStopFlag() {}

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm();
    void setTexAnm();
    void setAttention();
    void chkAttention();
    void lookBack();
    void setMtx();
    void setCollision();
    void smoke_set();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void talkInit();
    void anmAtr(unsigned short);
    void talk(bool);
    void eventOrder();
    void checkOrder();
    void demo_wait_2();
    void demo_intro_2();
    void goal_wait_2();
    void demo_goal_2();
    void demo_bomb_get();
    void demo_wait();
    void demo_intro();
    void demo_lift();
    void demo_jump();
    void goal_goalpos_to_talkpos();
    void goal_talkpos_to_goalpos();
    void goal_goalpos_wait();
    void goal_talkpos_wait();
    void demo_goal();
    void goal_talkpos_talk();
    void treasure_wait();
    void treasure_wait_talk();
    void demo_arrive();
    void wait01();
    void zukotelescope();
    void moccowait();
    void talk01();
    void intro_action(void*);
    void wait_action(void*);
    BOOL _execute();
    void draw_item(J3DModel*, signed char);
    void drawDagger();
    void drawHead();
    void drawShadow();
    void drawP2a();
    void drawP2b();
    void drawP2c();
    BOOL _draw();
    void getArg();
    void _createHeap();
    void createInit();
    s32 _create();
    BOOL _delete();
    void cutProc();
    void cutTalkStart(int);
    void cutTalkProc(int);
    void cutRideSwitchStart(int);
    void cutRideSwitchProc(int);
    void cutRunWaitStart(int);
    void cutRunWaitProc(int);
    void searchNearLift(void*, void*);
    void cutJumpToLiftStart(int);
    void cutJumpToLiftProc(int);
    void searchNearRope(void*, void*);
    void cutLiftToRopeStart(int);
    void cutLiftToRopeProc(int);
    void cutRopeTalkStart(int);
    void cutRopeTalkProc(int);
    void cutRopeToLiftStart(int);
    void cutRopeToLiftProc(int);
    void cutJumpToGoalStart(int);
    void cutJumpToGoalProc(int);
    void cutJumpStart(int);
    void cutJumpProc(int);
    void cutSetAnmStart(int);
    void cutSetAnmProc(int);
    void cutSwOnStart(int);
    void cutSwOnProc(int);
    void cutSwOffStart(int);
    void cutSwOffProc(int);
    void cutSurpriseStart(int);
    void cutSurpriseProc(int);
    void cutOmamoriInitStart(int);
    void cutOmamoriInitProc(int);
    void cutOmamoriEndStart(int);
    void cutOmamoriEndProc(int);

public:
    /* Place member variables here */
};

class daNpc_P2_childHIO_c {
public:
    daNpc_P2_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_P2_HIO_c {
public:
    daNpc_P2_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_P2_H */
