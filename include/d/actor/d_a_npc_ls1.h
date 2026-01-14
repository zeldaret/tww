#ifndef D_A_NPC_LS1_H
#define D_A_NPC_LS1_H

#include "d/d_npc.h"
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

class daNpc_Ls1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        
    };

    inline daNpc_Ls1_c();

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
    bool createInit();
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
    u16 next_msgStatus(unsigned long*);
    void getMsg_LS1_0();
    void getMsg_LS1_3();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_parts_notMov();
    void searchByID(fpc_ProcID, int*);
    void partner_search_sub(void* (*)(void*, void*));
    void partner_search();
    void setEyeCtrl();
    void clrEyeCtrl();
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void cut_init_LOK_PLYER(int);
    BOOL cut_move_LOK_PLYER();
    void cut_init_PLYER_MOV(int);
    BOOL cut_move_PLYER_MOV();
    void cut_init_WAI(int);
    BOOL cut_move_WAI();
    void cut_init_ANM_CHG(int);
    BOOL cut_move_ANM_CHG();
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
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL handCreateHeap();
    BOOL itemCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class field_0x6C4;
    /* 0x6CC */ u8 field_0x6CC[0x6D0 - 0x6CC];
    /* 0x6D0 */ J3DModel* field_0x6D0;
    /* 0x6D4 */ u8 field_0x6D4[0x6E0 - 0x6D4];
    /* 0x6E0 */ char field_0x6E0[3];
    /* 0x6E3 */ u8 field_0x6E3[0x6E8 - 0x6E3];
    /* 0x6E8 */ J3DModel* field_0x6E8;
    /* 0x6EC */ s8 m_lsHnd_L_jnt_num;
    /* 0x6ED */ s8 m_lsHnd_R_jnt_num;
    /* 0x6EE */ u8 field_0x6EE[0x6F0 - 0x6EE];
    /* 0x6F0 */ mDoExt_btkAnm field_0x6F0;
    /* 0x704 */ u8 field_0x704[0x708 - 0x704];
    /* 0x708 */ mDoExt_btpAnm field_0x708;
    /* 0x71C */ u8 field_0x71C[0x7CC - 0x71C];
    /* 0x7CC */ cXyz field_0x7CC[2];
    /* 0x7E4 */ u8 field_0x7E4[0x837 - 0x7E4];
    /* 0x837 */ bool field_0x837;
    /* 0x838 */ u8 field_0x838[0x854 - 0x838];
    /* 0x854 */ s8 field_0x854;
    /* 0x855 */ s8 field_0x855;
    /* 0x856 */ u8 field_0x856[0x858 - 0x856];
};  // Size: 0x858

class daNpc_Ls1_HIO_c {
public:
    daNpc_Ls1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_LS1_H */
