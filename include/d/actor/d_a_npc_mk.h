#ifndef D_A_NPC_MK_H
#define D_A_NPC_MK_H

#include "f_op/f_op_actor.h"

class daNpc_Mk_c : public fopAc_ac_c {
public:
    void ChkOrder(unsigned char) {}
    void ClrOrder(unsigned char) {}
    void SetOrder(unsigned char) {}
    void chkAngry() {}
    void chkFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void getVisitMode() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Mk_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}
    void setFlag(unsigned short) {}

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void setAnmStatus();
    void chkAttentionLocal();
    void chkAttention();
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void msgAnm(unsigned char);
    void talkInit();
    void msgPushButton();
    void talk();
    void checkDemoStart();
    void getNowEventAction();
    void init();
    void getType();
    void getPath();
    void nextVisitMode();
    void visitInit(unsigned char);
    void visitProc();
    void runawayInit();
    void walkPath(unsigned char);
    void runLink();
    void aroundLink();
    void remove_Um2();
    void demoInitCom();
    void demoProc();
    void setAttention(bool);
    void getLookBackMode();
    void lookBack();
    void wait01();
    void talk01();
    void talk02();
    void visitTalkInit();
    void visitSetEvent();
    void visit01();
    void climb01();
    void drop01();
    void runaway();
    void jump();
    void jitanda01();
    void jitanda02();
    void demo01();
    void demo02();
    void demo03();
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

#endif /* D_A_NPC_MK_H */
