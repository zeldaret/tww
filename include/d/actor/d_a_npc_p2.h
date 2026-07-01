#ifndef D_A_NPC_P2_H
#define D_A_NPC_P2_H

#include "d/actor/d_a_himo3.h"
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

    enum Type_e{
        Type_ZUKO_e = 0,
        Type_NIKO_e = 1,
        Type_MAKO_e = 2,
    };

    enum States_e{
        State_WAIT01_e = 1,
        State_TALK01_e = 2,
        State_DEMO_WAIT_e = 3,
        State_DEMO_INTRO_e = 4,
        State_DEMO_LIFT_e = 5,  //Niko waits for the platforms to rise
        State_DEMO_JUMP_e = 6,  //Niko speaks to link, then jumps to the platform
        State_GOAL_TALKPOS_WAIT_e = 7,
        State_GOAL_TALKPOS_TALK_e = 8,
        State_GOAL_GOALPOS_TO_TALKPOS_e = 9,
        State_GOAL_TALKPOS_TO_GOALPOS_e = 0xA,
        State_GOAL_GOALPOS_WAIT_e = 0xB,
        State_DEMO_GOAL_e = 0xC,
        State_TREASURE_WAIT_e = 0xD,
        State_TREASURE_WAIT_TALK_e = 0xE,
        State_DEMO_ARRIVE_e = 0xF,
        State_MOCCOWAIT_e = 0x10,
        State_ZUKOTELESCOPE_e = 0x11,
        State_DEMO_WAIT_2_e = 0x12,
        State_DEMO_INTRO_2_e = 0x13,
        State_GOAL_WAIT_2_e = 0x14,
        State_DEMO_GOAL_2_e = 0x15,
        State_DEMO_BOMB_GET_e = 0x16,
    };
    enum DemoIdx_e{
        DemoIdx_NONE_e = 0,
        DemoIdx_TALK_e = 1,
        DemoIdx_TALK_2_e = 2,
        DemoIdx_P2B_INTRO_e = 3,
        DemoIdx_P2B_TO_GOAL_e = 4,
        DemoIdx_P2B_GOAL_WAIT_TALK_e = 5,
        DemoIdx_P2B_GOAL_e = 6,
        DemoIdx_P2B_ARRIVE_MAJYU_e = 7,
        DemoIdx_P2B_INTRO_2_e = 8,
        DemoIdx_P2B_GOAL_2_e = 9,
        DemoIdx_P2B_BOMB_GET_e = 0xA
    };
    enum Actions_e{
        Action_TALK_e,
        Action_RIDE_SWITCH_e,
        Action_RUN_WAIT_e,
        Action_JUMP_TO_LIFT_e,
        Action_LIFT_TO_ROPE_e,
        Action_ROPE_TALK_e,
        Action_ROPE_TO_LIFT_e,
        Action_JUMP_TO_GOAL_e,
        Action_SET_ANM_e,
        Action_JUMP_e,
        Action_SW_ON_e,
        Action_SW_OFF_e,
        Action_SURPRISE_e,
        Action_OMAMORI_INIT_e,
        Action_OMAMORI_END_e
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

    BOOL initTexPatternAnm(bool);
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
    BOOL _createHeap();
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
    static void* searchNearLift(void*, void*);
    void cutJumpToLiftStart(int);
    void cutJumpToLiftProc(int);
    static void* searchNearRope(void*, void*);
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

    /* 0x290 */ u8 mType;
                u8 m291;
                u8 m292;
                u8 m293;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ mDoExt_McaMorf* mpMorf;
    /* 0x2A0 */ mDoExt_McaMorf* mpMorf2;
    /* 0x2A4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2B8 */ J3DModel* m2B8; //head model
    /* 0x2BC */ J3DModel* m2BC;
    /* 0x2C0 */ J3DModel* m2C0;
    /* 0x2C4 */ J3DModel* m2C4;
    /* 0x2C8 */ u32 mShadowId;
    /* 0x2CC */ dNpc_JntCtrl_c m_jnt;
    /* 0x300 */ dNpc_EventCut_c mEventCut;
                u8 m36C[0x370-0x36C];
                u8 m370;
                f32 m374;
                u8 m378;
                s16 m37A;
                dBgS_ObjAcch mAcch;
                dBgS_AcchCir mAcchCir;
                dCcD_Stts mStts;
                dCcD_Cyl m5BC;
                //u8 m60C[0x6D4-0x60C];
                //cM3dGCyl m6D4;
                csXyz m6EC;
                s16 m6F2;
                u8 m6F4[0x6F8-0x6F4];
                cXyz m6F8;
                cXyz m704;
                //J3DModel* m710;
                u8 m710;
                u16 m712;
                cXyz mClosestPos;
                daNpc_P2_c* mActor;
                u8 m724;
                u8 m725;
                u32 m728;
                u8 m72C;
                cXyz m730;
                cXyz m73C;
                s16 m748;
                u8 m74A;
                int m74C;
                u8 m750;
                u8 m751;
    /* 0x754 */ dPa_smokeEcallBack mSmokeCallback;
    /* 0x774 */ cXyz mSmokePos;
    /* 0x780 */ csXyz mSmokeAngle;
    /* 0x786 */ u8 m786;
                u32 m788;
                cXyz m78C;
                f32 m798;
                f32 m79C;
                f32 m7A0;
                f32 m7A4;
                s16 m7A8;
                s16 m7AA;
                u32 m7AC;
                Vec m7B0;
                himo3_class* m7BC;
                u8 m7C0;
    /* 0x7C1 */ u8 m7C1;
    /* 0x7C2 */ u8 m7C2;
                ActionFunc mActionFunc;

    /* 0x7D0 */ s8 m7D0;
    /* 0x7D1 */ s8 m7D1;
    /* 0x7D2 */ s8 mAnmFileIdx;
    /* 0x7D3 */ s8 m7D3;
    /* 0x7D4 */ s8 m7D4;
    /* 0x7D5 */ s8 mDemoOrderIdx;
    /* 0x7D6 */ s8 mState;
    /* 0x7D7 */ u8 m7D7;
                u8 m7D8;
    /* 0x7DC */ cXyz m7DC;
    /* 0x7E8 */ cXyz m7E8;
                int m7F4;
                f32 m7F8;
                f32 m7FC;
                f32 m800;
    /* 0x804 */ u32 m804;
    /* 0x808 */ s8 m808;
    /* 0x809 */ s8 m809;
    /* 0x80A */ s8 m80A;
    //SIZE: 0x80C
};


#endif /* D_A_NPC_P2_H */
