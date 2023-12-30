#ifndef D_A_NPC_MN_H
#define D_A_NPC_MN_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

struct sMnAnmDat {
    
};

class daNpcMn_c : public fopAc_ac_c {
public:
    void getNpcNo() {}
    void getPhaseP() {}
    void getPosFlag() {}
    void setResFlag(unsigned char) {}

    daNpcMn_c();
    s32 _create();
    void createHeap();
    void createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeCommon();
    void executeSetMode(unsigned char);
    void executeWaitInit();
    void executeWait();
    void executeTalkInit();
    void executeTalk();
    void executeTalk3Init();
    void executeTalk3();
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
    void eventWaitInit(int);
    void eventWait(int);
    void eventSwOnInit(int);
    void eventSwOn();
    void eventHatchInit();
    void eventHatch();
    void eventBikkuriInit(int);
    void eventBikkuri();
    void eventTurnInit();
    void eventTurn(int);
    void eventWalkInit();
    void eventWalk();
    void eventLookInit();
    void eventLook();
    void eventJumpInit(int);
    void eventJump();
    void talk2(int);
    void talk3(int);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void getMsg3();
    void chkMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void getPrmRailID();
    void getPrmSwitchBit();
    void getPrmSwitchBit2();
    void setMtx();
    void chkAttention();
    void lookBack();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sMnAnmDat*);
    void XyCheckCB(int);
    void getRand(int);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    void chkEndEvent();
    void chkPosNo();
    void getPosNo();
    void isChangePos(unsigned char);

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_MN_H */
