#ifndef D_A_NPC_P2_H
#define D_A_NPC_P2_H

#include "d/d_npc.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class daNpc_P2_c : public fopAc_ac_c {
public:
    typedef int (daNpc_P2_c::*ActionFunc)(void*);
    struct anm_prm_c {
        s8 m0;
        s8 m1;
        u16 m2;
        f32 m4;
        f32 m8;
        u32 mC;
    };


    cXyz& getAttentionBasePos() {return m6F8;}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getEyePos() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_P2_c::*)(void*), void*) {}
    void setEyeStopFlag() {}

    bool initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm();
    void setTexAnm();
    void setAttention();
    bool chkAttention();
    void lookBack();
    void setMtx();
    void setCollision();
    void smoke_set();
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void talkInit();
    void anmAtr(unsigned short);
    u16 talk(bool);
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
    BOOL intro_action(void*);
    BOOL wait_action(void*);
    bool _execute();
    void draw_item(J3DModel*, signed char);
    void drawDagger();
    void drawHead();
    void drawShadow();
    void drawP2a();
    void drawP2b();
    void drawP2c();
    bool _draw();
    void getArg();
    void _createHeap();
    void createInit();
    cPhs_State _create();
    bool _delete();
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
    static const u32 m_heapsize[3];
    static const char m_arc_name[3];
public:
    /* Place member variables here */

    /* 0x290 */ u8 m290;
                u8 m291;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ mDoExt_McaMorf* mpMorf;
    /* 0x2A0 */ mDoExt_McaMorf* mpMorf2;
    /* 0x2A4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2B8 */ J3DModel* m2B8;
    /* 0x2BC */ J3DModel* m2BC;
    /* 0x2C0 */ J3DModel* m2C0;
    /* 0x2C4 */ J3DModel* m2C4;
    /* 0x2CC */ dNpc_JntCtrl_c m_jnt;
    /* 0x300 */ dNpc_EventCut_c mEventCut;
                u8 filler;
                u8 filler2;
                u32 m_neck_jnt_num;
                u32 m_hed_jnt_num;
                u32 m2FC;
                u8 m300[0x378-0x300];
                u8 m378;
                u16 m37A;
                u32 m37C;
                u8 m380[0x6F8-0x380];
                cXyz m6F8;
                cXyz m704;

                J3DModel* m710;
                u8 m714;
                u8 m715[0x7D0-0x715];
                u8 m724;
                u8 m725;
                cXyz m73C;
                u8 m748;
                s32 m74C;
    /* 0x754 */ dPa_smokeEcallBack m754;

    /* 0x774 */ cXyz mSmokePos;
    /* 0x780 */ csXyz mSmokeAngle;
                
                u8 m7C1;
                s8 m7D0;
                u8 m7D1;
                u8 m7D2;
                s8 m7D3;
                u8 m7D4;
                u8 m7D5;
                s8 m7D6;
                cXyz m7DC;
                s8 m808;
                u8 m809;
                u8 m80A;
    //SIZE: 0x80C
};


#endif /* D_A_NPC_P2_H */
