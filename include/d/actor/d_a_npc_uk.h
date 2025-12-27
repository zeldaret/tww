#ifndef D_A_NPC_UK_H
#define D_A_NPC_UK_H

#include "f_op/f_op_actor.h"

class daNpc_Uk_c : public fopAc_ac_c {
public:
    void ChkOrder(unsigned char) {}
    void ClrOrder(unsigned char) {}
    void SetOrder(unsigned char) {}
    void chkFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Uk_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}
    void setFlag(unsigned short) {}

    void getType();
    void getPath();
    void getShapeType();
    void getCaughtFlag();
    void getFoundFlag();
    void getFirstTalk();
    void chkGameStart();
    void chkPositioning(float, float, float, short, short);
    void nextVisitMode();
    void approachRun(fopAc_ac_c*);
    void aroundWalk(fopAc_ac_c*);
    void surrender();
    void runawayInit();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char, unsigned char);
    void chkAttentionLocal();
    void chkAttention();
    void setAnmStatus();
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void msgAnm(unsigned char);
    void talkInit();
    void talk();
    void init();
    void setAttention(bool);
    void getLookBackMode();
    void lookBack();
    void getStaffName();
    void checkDemoStart();
    void getNowEventAction();
    void visitInit(unsigned char);
    void visitProc();
    void wait01();
    void talk01();
    void talk02();
    void visitTalkInit();
    void visitSetEvent();
    void visit01();
    void warningB();
    void warningC();
    void warningD();
    void found();
    void runaway();
    void jump();
    void jitanda01();
    void jitanda02();
    void demo01();
    void demo02();
    void demoInitCom();
    void demoProc();
    void wait_action(void*);
    void seek_action(void*);
    void hind_action(void*);
    void visit_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_UK_H */
