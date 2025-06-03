#ifndef D_A_NPC_TT_H
#define D_A_NPC_TT_H

#include "f_op/f_op_actor.h"

struct tt_ke_s {
    void ke_control(float);
    void ke_pos_set(cXyz*);
};

class daNpc_Tt_c : public fopAc_ac_c {
public:
    void ChkOrder(unsigned char) {}
    void ClrOrder() {}
    void SetOrder(unsigned char) {}
    void chkEvFlag(unsigned short) {}
    void chkFlag(unsigned short) {}
    void clrEvFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Tt_c::*)(void*), void*) {}
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
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(int);
    void danceInit(int);
    void danceProc();
    void danceNext();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_TT_H */
