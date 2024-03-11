#ifndef D_A_NPC_GK1_H
#define D_A_NPC_GK1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Gk1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void init_GK1_0();
    void createInit();
    void play_animation();
    void setMtx(bool);
    void bckResID(int);
    void btpResID(int);
    void setBtp(signed char, bool);
    void init_texPttrnAnm(signed char, bool);
    void play_btp_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void next_msgStatus(unsigned long*);
    void getMsg_GK1_0();
    void getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_parts_notMov();
    void searchByID(uint, int*);
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Gk1_c::*)(void*), void*);
    void setStt(signed char);
    void chk_attn();
    void wait_1();
    void talk_1();
    void wait_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void bodyCreateHeap();
    void itemCreateHeap();
    void hat_CreateHeap();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Gk1_HIO_c {
public:
    daNpc_Gk1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_GK1_H */
