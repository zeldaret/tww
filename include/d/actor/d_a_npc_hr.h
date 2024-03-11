#ifndef D_A_NPC_HR_H
#define D_A_NPC_HR_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"

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
    void create(fopAc_ac_c*, unsigned char, float*, int);
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
    /* 0x11C */ uint mActorProcID;
    /* 0x120 */ f32 m120;
    /* 0x124 */ f32 m124;
    /* 0x128 */ f32 m128;
    /* 0x12C */ f32 m12C;
    /* 0x130 */ f32 m130;
};

class daNpc_Hr_c : public fopAc_ac_c {
public:
    void ChkOrder(unsigned char) {}
    void ClrOrder() {}
    void SetOrder(unsigned char) {}
    void chkEvFlag(unsigned short) {}
    void chkFlag(unsigned short) {}
    void clrEvFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void getBackboneJntNum() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Hr_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEvFlag(unsigned short) {}
    void setEyePos(cXyz) {}
    void setFlag(unsigned short) {}

    void getShapeType();
    void getSwbit();
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
    void demoProc();
    void node_Ht_ant(int);
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setTexPtn(signed char);
    void setAnm(signed char);
    void setAnmStatus();
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void nextAnm(signed char, int);
    void msgAnm(unsigned char);
    void talkInit();
    void talk();
    void init();
    void setAttention(bool);
    void getNowJointY();
    void getTornadoPos(int, cXyz*);
    void rideTornado();
    void getLookBackMode();
    void lookBack();
    void rt_search();
    void rt_hide();
    void rt_intro();
    void to_rt_hit();
    void to_rt_tact();
    void rt_angry();
    void rt_win();
    void rt_hit0();
    void rt_hit1();
    void ht_hide();
    void wait01();
    void wait02();
    void endTalk();
    void endTact();
    void setEmitFlash(float);
    void smokeProc();
    void talk01();
    void ht_tact01();
    void wait_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void CreateHeap();

public:
    /* 0x290 */ u8 m290[0x294 - 0x290];
    /* 0x294 */ cXyz mPos;
    /* 0x2A0 */ u8 m2A0[0x2A8 - 0x2A0];
    /* 0x2A8 */ request_of_phase_process_class mResHrPhs;
    /* 0x2B0 */ u8 m2B0[0x314 - 0x2B0];
    /* 0x314 */ cCcD_Obj mObj0;
    /* 0x364 */ u8 m364[0x42C - 0x364];
    /* 0x42C */ cM3dGCyl m42C;
    /* 0x444 */ u8 m444[0x598 - 0x444];
    /* 0x598 */ cM3dGCyl m598;
    /* 0x5B0 */ u8 m5B0[0x608 - 0x5B0];
    /* 0x608 */ u16 m608;
    /* 0x60A */ u8 m60A[0x60C - 0x60A];
    /* 0x60C */ u8 m60C;
    /* 0x60D */ u8 m60D[0x610 - 0x60D];
    /* 0x610 */ dPa_followEcallBack mSmokeCallBack;
    /* 0x624 */ u8 m624[0x638 - 0x624];
    /* 0x638 */ u8 m638;
    /* 0x639 */ u8 m639[0x63A - 0x639];
    /* 0x63A */ u8 mType;
    /* 0x63B */ u8 m63B[0x694 - 0x63B];
    /* 0x694 */ daNpc_Wind_Clothes mClothes;
    /* 0x7C8 */ u8 m7C8[0x828 - 0x7C8];
};

#endif /* D_A_NPC_HR_H */
