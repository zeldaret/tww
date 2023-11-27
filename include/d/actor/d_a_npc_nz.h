#ifndef D_A_NPC_NZ_H
#define D_A_NPC_NZ_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Nz_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    void modeProcInit(int) {}

    void NodeCallBack(J3DNode*, int);
    void TailNodeCallBack(J3DNode*, int);
    void TailControl();
    void _createHeap();
    void XyEventCB(int);
    void eventOrder();
    void checkOrder();
    void setAttention();
    void LookBack();
    void setAnm(signed char, bool);
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeEventEsaInit();
    void modeEventEsa();
    void modeProc(Proc_e, int);
    void createShopItem(unsigned char, unsigned char);
    void getShopItem(int);
    void deleteShopItem();
    void next_msgStatus(unsigned long*);
    void anmAtr(unsigned short);
    BOOL _execute();
    BOOL _draw();
    void createInit();
    void setSmokeParticle();
    void getArg();
    s32 _create();
    BOOL _delete();
    void _searchEsa(fopAc_ac_c*);
    void cutProc();
    void cutEatesaStart();
    void cutEatesaProc();
    void cutEatesaFirstStart();
    void cutEatesaFirstProc();
    void cutKillAllStart();
    void cutKillAllProc();
    void cutShowStart();
    void cutShowProc();
    void cutHideStart();
    void cutHideProc();
    void cutSetAnmStart();
    void cutSetAnmProc();
    void cutGoHomeStart();
    void cutGoHomeProc();
    void cutChkGetItemStart();
    void cutChkGetItemProc();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_NZ_H */
