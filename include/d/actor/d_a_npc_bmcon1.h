#ifndef D_A_NPC_BMCON1_H
#define D_A_NPC_BMCON1_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class J3DNode;

struct sBmconAnmDat {
    
};

class daNpcBmcon_c : public fopAc_ac_c {
public:
    daNpcBmcon_c();

    void getNpcNo() {}
    void getPhaseP() {}
    void get_arm_L_jnt_num() {}
    void get_arm_R_jnt_num() {}
    void get_nec_jnt_num() {}
    void setResFlag(unsigned char) {}

    void nodeArmControl(J3DNode*, J3DModel*);
    s32 _create();
    void createHeap();
    void createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    void executeCommon();
    void executeSetMode(unsigned char);
    void executeWaitInit();
    void executeWait();
    void executeTalkInit();
    void executeTalk();
    void executeWalkInit();
    void executeWalk();
    void executeTurnInit();
    void executeTurn();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    void eventMesSet();
    void eventGetItemInit();
    void talk2(int);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void chkMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void getPrmRailID();
    void setMtx();
    void chkAttention();
    void lookBack();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sBmconAnmDat*);
    void XyCheckCB(int);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    void calcFlyDist();
    void getFlyDistMax();
    void setFlyDistMax(short);
    void getFlyDistNow();
    void setFlyDistNow(short);
    void chkEndEvent();
    void isClear();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BMCON1_H */
