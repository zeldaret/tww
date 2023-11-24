#ifndef D_A_NPC_TT_H
#define D_A_NPC_TT_H

#include "f_op/f_op_actor.h"

class daNpc_Tt_c : public fopAc_ac_c {
public:
    void ChkOrder(unsigned char) {}
    void ClrOrder() {}
    void SetOrder(unsigned char) {}
    void chkEvFlag(unsigned short) {}
    void chkFlag(unsigned short) {}
    void clrEvFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void danceInit(int) {}
    void danceNext() {}
    void danceProc() {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void initTexPatternAnm(bool) {}
    void playTexPatternAnm() {}
    void setAction(int (daNpc_Tt_c::*)(void*), void*) {}
    void setAnm(int) {}
    void setAttentionBasePos(cXyz) {}
    void setEvFlag(unsigned short) {}
    void setEyePos(cXyz) {}
    void setFlag(unsigned short) {}

    void XyCheckCB(int);
    void setAnmStatus();
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void talkInit();
    void msgAnm();
    void msgPushButton();
    void msgContinue();
    void talk();
    void demoInitChange();
    void demoProcTact1();
    void demoInitPatten();
    void demoProcPatten();
    void demoInitSpeak();
    void demoProcSpeak();
    void demoInitWait();
    void demoProcWait();
    void demoInitCom();
    void demoProcCom();
    void getNowEventAction();
    void demoProc();
    void init();
    void setAttention(bool);
    void lookBack();
    void wait01();
    void talk01();
    void tact00();
    void wait_action(void*);
    void set_ke_root(int, int, int);
    void ke_execute();
    void _draw();
    void _execute();
    void _delete();
    void _create();
    void CreateHeap();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_TT_H */
