#ifndef D_A_NPC_ROTEN_H
#define D_A_NPC_ROTEN_H

#include "f_op/f_op_actor.h"

struct sRotenAnmDat {
    
};

class daNpcRoten_c : public fopAc_ac_c {
public:
    void getPhaseP() {}
    void getWindVec() {}
    void setNpcNo(unsigned char) {}
    void setResFlag(unsigned char) {}

    daNpcRoten_c();
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
    void executeWalkInit();
    void executeWalk();
    void executeTurnInit();
    void executeTurn();
    void executeWindInit();
    void executeWind();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventInit();
    void eventMesSetInit(int);
    void eventMesSet();
    void eventSetItemInit();
    void eventSetItem();
    void eventClrItemInit();
    void eventGetItemInit(int);
    void eventSetAngleInit();
    void eventOnPlrInit();
    void eventOffPlrInit();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void getPrmRailID();
    void setMtx();
    void chkAttention();
    void lookBack();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sRotenAnmDat*);
    void isHaitatuItem(unsigned char);
    void isKoukanItem(unsigned char);
    void isGetMap(unsigned char);
    void XyEventCB(int);
    void setCollisionB();
    void setCollisionH();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_ROTEN_H */
