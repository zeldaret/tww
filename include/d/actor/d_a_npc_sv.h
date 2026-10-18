#ifndef D_A_NPC_SV_H
#define D_A_NPC_SV_H

#include "d/d_cc_d.h"
#include "d/d_npc.h"

struct sSvAnmDat {};

class daNpcSv_c : public fopNpc_npc_c {
public:
    void getMsgPtn() {}
    void getNpcNo() {}
    void getPhaseP() {}
    void setResFlag(unsigned char) {}

    daNpcSv_c();
    cPhs_State _create();
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
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    void eventMesSet();
    void eventGetItemInit(int);
    void eventGetItem();
    void eventSetAngleInit();
    void eventAttentionInit(int);
    void eventAttention();
    void eventTurnOkInit();
    void talk2(int, fopAc_ac_c*);
    virtual u16 next_msgStatus(unsigned long*);
    virtual u32 getMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    void getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sSvAnmDat*);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    void getTalkNo();
    void isTalkOK();

private:
    /* 0x6C4 */ u8 padding_0x6C4[8];
    /* 0x6CC */ request_of_phase_process_class mPhase;
};

#endif /* D_A_NPC_SV_H */
