#ifndef D_A_NPC_AH_H
#define D_A_NPC_AH_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

struct sAhAnmDat {
    
};

class daNpcAh_c : public fopAc_ac_c {
public:
    daNpcAh_c();

    void getPhaseP() {}
    void setResFlag(unsigned char) {}

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
    void getPrmArg0();
    void getSwBit();
    void setMtx();
    void chkAttention();
    void lookBack();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sAhAnmDat*);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    void chkEndEvent();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_AH_H */
