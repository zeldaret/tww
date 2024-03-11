#ifndef D_A_NPC_YW1_H
#define D_A_NPC_YW1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Yw1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void _nodeCB_Hair(J3DNode*, J3DModel*);
    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void init_YW1_0();
    void init_YW1_1();
    void init_YW1_2();
    void init_YW1_3();
    void createInit();
    void play_animation();
    void upLift();
    void setMtx(bool);
    void bckResID(int);
    void btpResID(int);
    void init_texPttrnAnm(signed char, bool);
    void play_texPttrnAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void next_msgStatus(unsigned long*);
    void getMsg_YW1_0();
    void getMsg_YW1_1();
    void getMsg_YW1_2();
    void getMsg_YW1_3();
    void getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_parts_notMov();
    void searchByID(uint, int*);
    void partner_search_sub(void* (*)(void*, void*));
    void partner_search();
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Yw1_c::*)(void*), void*);
    void setStt(signed char);
    void chngTsuboAnm();
    void chk_areaIN(float, float, short, cXyz);
    void set_pthPoint(unsigned char);
    void setHairAngle();
    void chk_brkTsubo();
    void chk_bm1Odoroki();
    void wait_1();
    void wait_2();
    void wait_3();
    void walk_1();
    void turn_1();
    void talk_1();
    void wait_action1(void*);
    void wait_action2(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void bodyCreateHeap();
    void headCreateHeap();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Yw1_childHIO_c {
public:
    daNpc_Yw1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Yw1_HIO_c {
public:
    daNpc_Yw1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_YW1_H */
