#ifndef D_A_NPC_BJ1_H
#define D_A_NPC_BJ1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Bj1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void nodeBj1Control(J3DNode*, J3DModel*);
    void nodePrpControl(J3DNode*, J3DModel*);
    void init_BJ4_0();
    void init_BJ6_0();
    void init_BJ7_0();
    void init_BJX_0();
    void init_BJX_1();
    void createInit();
    void setMtx_anmProc();
    void setMtx(bool);
    void anmNum_toResID(int);
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int);
    void setAnm();
    void setAnm_prp(signed char);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_drct(float);
    void chk_partsNotMove();
    void lookBack();
    void getMaskInf(unsigned char*);
    void chkReg(unsigned short);
    void setReg(unsigned short);
    void next_msgStatus(unsigned long*);
    void getMsg_BJ1_0();
    void getMsg_BJ2_0();
    void getMsg_BJ3_0();
    void getMsg_BJ4_0();
    void getMsg_BJ5_0();
    void getMsg_BJ6_0();
    void getMsg_BJ7_0();
    void getMsg_BJ8_0();
    void getMsg_BJ9_0();
    void getMsg_Corog();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(uint);
    void partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    void setCollision_SP_();
    void set_pthPoint(unsigned char);
    void bj_clcFlySpd();
    void bj_movPass(bool);
    void bj_flyMove();
    void bj_clcMovSpd();
    void bj_nMove();
    void setPrtcl_drugPot_1();
    void setPrtcl_drugPot_2();
    void delPrtcl_drugPot();
    void setPrtcl_danceLR();
    void flwPrtcl_danceLR();
    void delPrtcl_danceLR();
    void setPrtcl_peraProOpen();
    void createSeed();
    void deleteSeed();
    void charDecide(int);
    void eInit_setLocFlag(int*);
    void eInit_setShapeAngleY(int*, short);
    void eInit_setEvTimer(int*);
    void eInit_calcRelativPos(cXyz*, int*);
    void eInit_prmFloat(float*, float);
    void eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*);
    void eInit_PLYER_MOV_1_();
    void eInit_MOV_(float*, float*, float*, int*);
    void eInit_JMP_(float*, float*);
    void eInit_CHG_PTH_(int*, int*);
    void eInit_END_MOV_();
    void eInit_SET_TNE_();
    void eInit_DEL_TNE_();
    void eInit_SET_ANM_(int*, float*);
    void event_actionInit(int);
    void eMove_ATTENTION_();
    void eMove_MOV_();
    void eMove_JMP_();
    void eMove_SET_TNE_();
    void eMove_PTH_MOV_();
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Bj1_c::*)(void*), void*);
    void setStt(signed char);
    void wait_1();
    void wait_2();
    void wait_3();
    void wait_4();
    void flyMov();
    void fall01();
    void talk_1();
    void walk_1();
    void wait_action1(void*);
    void wait_action2(void*);
    void wait_action3(void*);
    void wait_action4(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void create_Anm();
    void create_prp_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Bj1_childHIO_c {
public:
    daNpc_Bj1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Bj1_HIO_c {
public:
    daNpc_Bj1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BJ1_H */
