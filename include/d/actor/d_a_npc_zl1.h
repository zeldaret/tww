#ifndef D_A_NPC_ZL1_H
#define D_A_NPC_ZL1_H

#include "f_op/f_op_actor.h"

class J3DMaterial;
class J3DNode;

class daNpc_Zl1_matAnm_c {
public:
    void clrMoveFlag() {}
    void getNowOffsetX() {}
    void getNowOffsetY() {}
    void setMoveFlag() {}

    daNpc_Zl1_matAnm_c();
    void calc(J3DMaterial*) const;

public:
    /* Place member variables here */
};

class daNpc_Zl1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void set_startPos(int);
    void init_ZL1_0();
    void init_ZL1_1();
    void init_ZL1_2();
    void init_ZL1_3();
    void init_ZL1_4();
    void init_ZL1_5();
    void init_ZL1_6();
    void init_ZL1_7();
    void createInit();
    void play_animation();
    void swoon_OnShip();
    void setMtx(bool);
    void bckResID(int);
    void btpResID(int);
    void btkResID(int);
    void setBtp(signed char, bool);
    void setMat();
    void setBtk(signed char, bool);
    void init_texPttrnAnm(signed char, bool);
    void play_btp_anm();
    void eye_ctrl();
    void play_btk_anm();
    void setAnm_anm(daNpc_Zl1_c::anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void next_msgStatus(unsigned long*);
    void getMsg_ZL1_2();
    void getMsg_ZL1_4();
    void getMsg_ZL1_5();
    void getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_parts_notMov();
    void searchByID(uint, int*);
    void partner_search_sub(void* (*)(void*, void*));
    void partner_search();
    void setEyeCtrl();
    void clrEyeCtrl();
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void get_prmFloat(float*, float);
    void set_LightPos();
    void init_Light();
    void incEnvironment();
    void decEnvironment();
    void darkProc();
    void cut_init_LOK_PLYER(int);
    void cut_move_LOK_PLYER();
    void cut_init_LOK_PARTNER(int);
    void cut_move_LOK_PARTNER();
    void cut_init_CHG_ANM_ATR(int);
    void cut_move_CHG_ANM_ATR();
    void cut_init_PLYER_TRN_PARTNER(int);
    void cut_move_PLYER_TRN_PARTNER();
    void cut_init_PLYER_TRN_TETRA(int);
    void cut_move_PLYER_TRN_TETRA();
    void cut_init_MAJYU_START(int);
    void cut_move_MAJYU_START();
    void cut_init_OKIRU(int);
    void cut_move_OKIRU();
    void cut_init_OKIRU_2(int);
    void cut_move_OKIRU_2();
    void cut_init_DRW_ONOFF(int);
    void cut_move_DRW_ONOFF();
    void cut_init_PLYER_DRW_ONOFF(int);
    void cut_move_PLYER_DRW_ONOFF();
    void cut_init_JMP_OFF(int);
    void cut_move_JMP_OFF();
    void cut_init_OMAMORI_ONOFF(int);
    void cut_move_OMAMORI_ONOFF();
    void cut_init_SURPRISED(int);
    void cut_move_SURPRISED();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Zl1_c::*)(void*), void*);
    void setStt(signed char);
    void chk_areaIN(float, float, short, cXyz);
    void setWaterRipple();
    void setWaterSplash();
    void set_simpleLand(bool);
    void setEff();
    void setFrontWallType();
    void move_jmp();
    void kyoroPos(int);
    void kyorokyoro();
    void wait_1();
    void talk_1();
    void demo_1();
    void demo_2();
    void demo_3();
    void demo_4();
    void optn_1();
    void optn_2();
    void optn_3();
    void wait_action1(void*);
    void demo_action1(void*);
    void demo_action2(void*);
    void optn_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void bodyCreateHeap();
    void itemCreateHeap();
    void CreateHeap();
public:
    /* Place member variables here */
};

class daNpc_Zl1_HIO_c {
public:
    daNpc_Zl1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_ZL1_H */
