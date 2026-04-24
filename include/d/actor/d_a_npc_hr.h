#ifndef D_A_NPC_HR_H
#define D_A_NPC_HR_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_npc.h"

class daNpc_Wind_Eff{
public:
    void init();
    void remove();
    BOOL create(cXyz*);
    BOOL end();
    void proc();
    void setspd();
    void move();

public:
    /* 0x00 */ dPa_followEcallBack mpFollowECallBack;
    /* 0x14 */ cXyz mPos;
    /* 0x20 */ cXyz mSpeed;
    /* 0x2C */ cXyz* field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ u8 field_0x34;
    /* 0x35 */ u8 field_0x35[0x38 - 0x35];
};  // Size: 0x38

class daNpc_Wind_Clothes {
public:
    void setSquallPos(int);
    BOOL create(fopAc_ac_c*, u8, f32*, int);
    BOOL end();
    void proc();
    void init();
    void remove();

public:
    /* 0x000 */ daNpc_Wind_Eff mWindEff[4];
    /* 0x0E0 */ s16 mSquallCounter[4];
    /* 0x0E8 */ cXyz mSquallPos[4];
    /* 0x118 */ u8 field_0x118;
    /* 0x119 */ u8 field_0x119[0x11C - 0x119];
    /* 0x11C */ fpc_ProcID mProcId;
    /* 0x120 */ f32 field_0x120[4]; // maybe [5]
    /* 0x130 */ f32 field_0x130;
};  // Size: 0x134

class daNpc_Hr_c : public fopAc_ac_c {
public:

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };

    typedef int (daNpc_Hr_c::*ActionFunc)(void*);
    // TODO
    void ChkOrder(u8) {}
    void ClrOrder() {}
    void SetOrder(u8) {}
    void chkEvFlag(u16) {}
    void chkFlag(u16) {}
    void clrEvFlag(u16) {}
    void clrFlag(u16) {}
    s8 getBackboneJntNum() { return m_jnt.getBackboneJntNum(); }
    s16 getBackbone_y() { return m_jnt.getBackbone_y(); }
    s8 getHeadJntNum() { return m_jnt.getHeadJntNum(); }
    s16 getHead_x() { return m_jnt.getHead_x(); }
    s16 getHead_y() { return m_jnt.getHead_y(); }
    void incAttnSetCount() {
        if (mAttnSetCount != 0xff) {
            mAttnSetCount++;
        }  
    }

    BOOL setAction(ActionFunc actionFunc, void* arg) {
        if (mCurrActionFunc != actionFunc) {
            if (mCurrActionFunc != NULL) {
                mActionStatus = ACTION_ENDING;
                (this->*mCurrActionFunc)(arg);
            }
            mCurrActionFunc = actionFunc;
            mActionStatus = ACTION_STARTING;
            (this->*mCurrActionFunc)(arg);
        }
        return TRUE;
    }

    void setAttentionBasePos(cXyz i_attnBasePos) { mAttnBasePos = i_attnBasePos; }
    void setEvFlag(u16) {}
    void setEyePos(cXyz i_eyePos) { mEyePos = i_eyePos; }
    void setFlag(u16) {}

    daNpc_Hr_c();
    int getShapeType();
    int getSwbit();
    s16 XyCheckCB(int);
    void onHide(int);
    void offHide(int);
    void defaultSetPos(cXyz*);
    s32 getNowEventAction();
    void demoInitWind();
    bool demoProcWind(int);
    void demoInitWait();
    BOOL demoProcWait();
    void demoInitSpeak();
    BOOL demoProcSpeak();
    BOOL demoProcPatten();
    BOOL demoProcTact0();
    BOOL demoProcTact1();
    BOOL demoProcTact2();
    BOOL demoProcTact3();
    int calcKaijou(int);
    void demoInitMove();
    void demoInitSmall();
    BOOL demoProcSmall();
    bool demoProcMove();
    void demoInitChange();
    void demoInitCom();
    void demoProcCom();
    bool demoProc();
    void node_Ht_ant(int);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setTexPtn(s8);
    void setAnm(s8);
    void setAnmStatus();
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void nextAnm(s8, int);
    void msgAnm(u8);
    void talkInit();
    u16 talk();
    BOOL init();
    void setAttention(bool);
    int getNowJointY();
    void getTornadoPos(int, cXyz*);
    bool rideTornado();
    u8 getLookBackMode();
    void lookBack();
    bool rt_search();
    bool rt_hide();
    bool rt_intro();
    bool to_rt_hit();
    bool to_rt_tact();
    bool rt_angry();
    bool rt_win();
    bool rt_hit0();
    bool rt_hit1();
    bool ht_hide();
    bool wait01();
    bool wait02();
    void endTalk();
    void endTact();
    void setEmitFlash(f32);
    void smokeProc();
    bool talk01();
    bool ht_tact01();
    BOOL wait_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x290 */ s8 m_waist_jnt_num;
    /* 0x291 */ u8 field_0x291[0x294 - 0x291];
    /* 0x294 */ cXyz mPos;
    /* 0x2A0 */ s16 mEventIdx;
    /* 0x2A2 */ s8 field_0x2A2;
    /* 0x2A3 */ u8 field_0x2A3[0x2A4 - 0x2A3];
    /* 0x2A4 */ s16 field_0x2A4;
    /* 0x2A6 */ u8 field_0x2A6[0x2A8 - 0x2A6];
    /* 0x2A8 */ request_of_phase_process_class mPhs;
    /* 0x2B0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B4 */ J3DModel* mpModel;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf2;
    /* 0x2BC */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2C0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2D4 */ u8 field_0x2D4;
    /* 0x2D5 */ u8 field_0x2D5[0x2D6 - 0x2D5];
    /* 0x2D6 */ s16 field_0x2D6;
    /* 0x2D8 */ dCcD_Stts mStts;
    /* 0x314 */ dCcD_Cyl mCyl;
    /* 0x444 */ dCcD_Stts mStts2;
    /* 0x480 */ dCcD_Cyl mCyl2;
    /* 0x5B0 */ dNpc_JntCtrl_c m_jnt;
    /* 0x5E4 */ cXyz mEyePos;
    /* 0x5F0 */ cXyz mAttnBasePos;
    /* 0x5FC */ s16 mMaxHeadTurnVelocity;
    /* 0x5FE */ s8 field_0x5FE;
    /* 0x5FF */ u8 mAttnSetCount;
    /* 0x600 */ f32 field_0x600;
    /* 0x604 */ u32 field_0x604;
    /* 0x608 */ u16 field_0x608;
    /* 0x60A */ u8 field_0x60A;
    /* 0x60B */ u8 mHitCount;
    /* 0x60C */ u8 mHitDelayTimer;
    /* 0x60D */ u8 field_0x60D[0x610 - 0x60D];
    /* 0x610 */ dPa_followEcallBack mSmokeCallBack; // not named by me
#if VERSION == VERSION_DEMO
    JPABaseEmitter* mpEmitter;
#endif
    /* 0x624 */ fpc_ProcID mProcId;
    /* 0x628 */ ActionFunc mCurrActionFunc;
    /* 0x634 */ s8 mSomeTexPatternIdx;
    /* 0x635 */ u8 field_0x635;
    /* 0x636 */ u8 field_0x636;
    /* 0x637 */ u8 field_0x637;
    /* 0x638 */ s8 field_0x638;
    /* 0x639 */ s8 field_0x639;
    /* 0x63A */ s8 mType;
    /* 0x63B */ s8 mActionStatus;
    /* 0x63C */ s8 field_0x63C;
    /* 0x63D */ u8 field_0x63D[0x640 - 0x63D];
    /* 0x640 */ int mStaffIdx;
    /* 0x644 */ int field_0x644;
    /* 0x648 */ f32 field_0x648;
    /* 0x64C */ u8 field_0x64C[0x650 - 0x64C];
    /* 0x650 */ s16 field_0x650;
    /* 0x652 */ s16 field_0x652;
    /* 0x654 */ cXyz field_0x654;
    /* 0x660 */ s16 field_0x660;
    /* 0x662 */ u8 field_0x662;
    /* 0x663 */ u8 field_0x663[0x664 - 0x663];
    /* 0x664 */ cXyz field_0x664;
    /* 0x670 */ cXyz field_0x670;
    /* 0x67C */ cXyz field_0x67C;
    /* 0x688 */ cXyz field_0x688;
    /* 0x694 */ daNpc_Wind_Clothes mClothes;
};  // Size: 0x7C8
//     /* 0x290 */ s8 field_0x290;
//     /* 0x291 */ u8 field_0x291[0x294 - 0x291];
//     /* 0x294 */ cXyz mPos;
//     /* 0x2A0 */ s16 field_0x2A0;
//     /* 0x2A2 */ s8 field_0x2A2;
//     /* 0x2A3 */ u8 field_0x2A3[0x2A4 - 0x2A3];
//     /* 0x2A4 */ s16 field_0x2A4;
//     /* 0x2A6 */ u8 field_0x2A6[0x2A8 - 0x2A6];
//     /* 0x2A8 */ request_of_phase_process_class mPhs;
//     /* 0x2B0 */ mDoExt_McaMorf* mpMorf;
//     /* 0x2B4 */ J3DModel* mpModel;
//     /* 0x2B8 */ mDoExt_McaMorf* MpMorf2;
//     /* 0x2BC */ J3DAnmTexPattern* m_head_tex_pattern;
//     /* 0x2C0 */ mDoExt_btpAnm mBtpAnm;
//     /* 0x2D4 */ u8 field_0x2D4;
//     /* 0x2D5 */ u8 field_0x2D5[0x2D6 - 0x2D5];
//     /* 0x2D6 */ s16 field_0x2D6;
//     /* 0x2D8 */ dCcD_Stts mStts;
//     /* 0x314 */ dCcD_Cyl mCyl;
//     /* 0x444 */ dCcD_Stts mStts2;
//     /* 0x480 */ dCcD_Cyl mCyl2;
//     /* 0x5B0 */ dNpc_JntCtrl_c m_jnt;
//     /* 0x5E4 */ cXyz mEyePos;
//     /* 0x5F0 */ cXyz mAttnBasePos;
//     /* 0x5FC */ s16 mMaxHeadTurnVelocity;
//     /* 0x5FE */ s8 field_0x5FE;
//     /* 0x5FF */ u8 mAttnSetCount;
//     /* 0x600 */ f32 field_0x600;
//     /* 0x604 */ u32 field_0x604;
//     /* 0x608 */ u16 field_0x608;
//     /* 0x60A */ u8 field_0x60A[0x60B - 0x60A];
//     /* 0x60B */ u8 mHitCount;
//     /* 0x60C */ u8 mHitDelayTimer;
//     /* 0x60D */ u8 field_0x60D[0x620 - 0x60D];
//     /* 0x620 */ dPa_followEcallBack field_0x620;
//     /* 0x634 */ u8 field_0x634[0x63A - 0x634];
//     /* 0x63A */ s8 mType;
//     /* 0x63B */ s8 mActionStatus;
//     /* 0x63C */ s8 field_0x63C;
//     /* 0x63D */ u8 field_0x63D[0x640 - 0x63D];
//     /* 0x640 */ int field_0x640;
//     /* 0x644 */ u8 field_0x644[0x694 - 0x644];
//     /* 0x694 */ daNpc_Wind_Clothes mClothes;
//     /* 0x7C8 */ u8 field_0x7C8[0x7CC - 0x7C8];
// };  // Size: 0x7CC

#endif /* D_A_NPC_HR_H */
