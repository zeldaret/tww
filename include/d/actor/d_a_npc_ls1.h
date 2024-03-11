#ifndef D_A_NPC_LS1_H
#define D_A_NPC_LS1_H

#include "f_op/f_op_actor.h"

class J3DMaterial;
class J3DNode;

class daNpc_Ls1_matAnm_c {
public:
    daNpc_Ls1_matAnm_c();
    void clrMoveFlag() {}
    void getNowOffsetX() {}
    void getNowOffsetY() {}
    void setMoveFlag() {}

    void calc(J3DMaterial*) const;

public:
    /* Place member variables here */
};

class daNpc_Ls1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void _nodeCB_Hand_L(J3DNode*, J3DModel*);
    void _nodeCB_Hand_R(J3DNode*, J3DModel*);
    void _Ls_hand_nodeCB_Hand_L(J3DNode*, J3DModel*);
    void _Ls_hand_nodeCB_Hand_R(J3DNode*, J3DModel*);
    void init_LS1_0();
    void init_LS1_1();
    void init_LS1_2();
    void init_LS1_3();
    void init_LS1_4();
    void createInit();
    void play_animation();
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
    void setAnm_anm(daNpc_Ls1_c::anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void next_msgStatus(unsigned long*);
    void getMsg_LS1_0();
    void getMsg_LS1_3();
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
    void cut_init_LOK_PLYER(int);
    void cut_move_LOK_PLYER();
    void cut_init_PLYER_MOV(int);
    void cut_move_PLYER_MOV();
    void cut_init_WAI(int);
    void cut_move_WAI();
    void cut_init_ANM_CHG(int);
    void cut_move_ANM_CHG();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Ls1_c::*)(void*), void*);
    void setStt(signed char);
    void chk_areaIN(float, float, short, cXyz);
    void get_playerEvnPos(int);
    void chkTelescope_sph(cXyz, float, float);
    void chkTelescope(cXyz, float, float);
    void telescope_proc();
    void wait_1();
    void wait_2();
    void wait_3();
    void wait_4();
    void talk_1();
    void wait_action1(void*);
    void demo_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void bodyCreateHeap();
    void handCreateHeap();
    void itemCreateHeap();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Ls1_HIO_c {
public:
    daNpc_Ls1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_LS1_H */
