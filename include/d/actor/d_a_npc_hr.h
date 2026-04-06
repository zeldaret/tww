#ifndef D_A_NPC_HR_H
#define D_A_NPC_HR_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_npc.h"

class daNpc_Wind_Eff {
public:
    void init();
    void remove();
    void create(cXyz*);
    void end();
    void proc();
    void setspd();
    void move();

public:
    /* 0x00 */ int m00;
    /* 0x04 */ u8 m04[0x14 - 0x04];
    /* 0x14 */ cXyz mPos;
    /* 0x20 */ cXyz mVel;
    /* 0x2C */ cXyz* m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ u8 m34;
    /* 0x35 */ u8 m35[0x38 - 0x35];
};

class daNpc_Wind_Clothes {
public:
    void setSquallPos(int);
    void create(fopAc_ac_c*, u8, f32*, int);
    void end();
    void proc();
    void init();
    void remove();

public:
    /* 0x000 */ daNpc_Wind_Eff mEff[4];
    /* 0x0E0 */ s16 mSquallCounter[4];
    /* 0x0E8 */ cXyz mSquallPos[4];
    /* 0x118 */ u8 m118;
    /* 0x119 */ u8 m119[0x11C - 0x119];
    /* 0x11C */ fpc_ProcID mActorProcID;
    /* 0x120 */ f32 m120;
    /* 0x124 */ f32 m124;
    /* 0x128 */ f32 m128;
    /* 0x12C */ f32 m12C;
    /* 0x130 */ f32 m130;
};

class daNpc_Hr_c : public fopAc_ac_c {
public:

    typedef int (daNpc_Hr_c::*ActionFunc)(void*);

    void ChkOrder(u8) {}
    void ClrOrder() {}
    void SetOrder(u8) {}
    void chkEvFlag(u16) {}
    void chkFlag(u16) {}
    void clrEvFlag(u16) {}
    void clrFlag(u16) {}
    void getBackboneJntNum() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    bool setAction(ActionFunc, void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEvFlag(u16) {}
    void setEyePos(cXyz) {}
    void setFlag(u16) {}

    daNpc_Hr_c();
    int getShapeType();
    int getSwbit();
    void XyCheckCB(int);
    void onHide(int);
    void offHide(int);
    void defaultSetPos(cXyz*);
    void getNowEventAction();
    void demoInitWind();
    void demoProcWind(int);
    void demoInitWait();
    void demoProcWait();
    void demoInitSpeak();
    void demoProcSpeak();
    void demoProcPatten();
    void demoProcTact0();
    void demoProcTact1();
    void demoProcTact2();
    void demoProcTact3();
    void calcKaijou(int);
    void demoInitMove();
    void demoInitSmall();
    void demoProcSmall();
    void demoProcMove();
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
    void next_msgStatus(u32*);
    void getMsg();
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
    /* 0x2A3 */ u8 field_0x2A3[0x2A8 - 0x2A3];
    /* 0x2A8 */ request_of_phase_process_class mPhs;
    /* 0x2B0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B4 */ J3DModel* mpModel;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf2;
    /* 0x2BC */ u8 field_0x2BC[0x2C0 - 0x2BC];
    /* 0x2C0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2D4 */ u8 field_0x2D4;
    /* 0x2D5 */ u8 field_0x2D5[0x2D8 - 0x2D5];
    /* 0x2D8 */ dCcD_Stts mStts;
    /* 0x314 */ dCcD_Cyl mCyl;
    /* 0x444 */ dCcD_Stts mStts2;
    /* 0x480 */ dCcD_Cyl mCyl2;
    /* 0x5B0 */ dNpc_JntCtrl_c m_jnt;
    /* 0x5E4 */ u8 field_0x5E4[0x5FC - 0x5E4];
    /* 0x5FC */ s16 mMaxHeadTurnVelocity;
    /* 0x5FE */ s8 field_0x5FE;
    /* 0x5FF */ u8 field_0x5FF[0x600 - 0x5FF];
    /* 0x600 */ f32 field_0x600;
    /* 0x604 */ u8 field_0x604[0x608 - 0x604];
    /* 0x608 */ u16 field_0x608;
    /* 0x60A */ u8 field_0x60A;
    /* 0x60B */ u8 mHitCount;
    /* 0x60C */ u8 mHitDelayTimer;
    /* 0x60D */ u8 field_0x60D[0x610 - 0x60D];
    /* 0x610 */ dPa_followEcallBack mSmokeCallBack;
    /* 0x624 */ fpc_ProcID mProcId;
    /* 0x628 */ ActionFunc mCurrActionFunc;
    /* 0x634 */ u8 mSomeTexPatternIdx;
    /* 0x635 */ u8 field_0x635[0x637 - 0x635];
    /* 0x637 */ u8 field_0x637;
    /* 0x638 */ s8 field_0x638;
    /* 0x639 */ s8 field_0x639;
    /* 0x63A */ s8 mType;
    /* 0x63B */ u8 field_0x63B;
    /* 0x63C */ u8 field_0x63C[0x640 - 0x63C];
    /* 0x640 */ int mStaffId;
    /* 0x644 */ int field_0x644;
    /* 0x648 */ u8 field_0x648[0x650 - 0x648];
    /* 0x650 */ s16 field_0x650;
    /* 0x652 */ u8 field_0x652[0x662 - 0x652];
    /* 0x662 */ u8 field_0x662;
    /* 0x663 */ u8 field_0x663[0x694 - 0x663];
    /* 0x694 */ daNpc_Wind_Clothes mClothes;
    /* 0x7C8 */ u8 field_0x7C8[0x828 - 0x7C8];
};  // Size: 0x828

#endif /* D_A_NPC_HR_H */
