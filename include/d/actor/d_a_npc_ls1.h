#ifndef D_A_NPC_LS1_H
#define D_A_NPC_LS1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class J3DMaterial;
class J3DNode;

class daNpc_Ls1_matAnm_c : public J3DMaterialAnm {
public:
    daNpc_Ls1_matAnm_c();
    void clrMoveFlag() {}
    void getNowOffsetX() {}
    void getNowOffsetY() {}
    void setMoveFlag() {}

    void calc(J3DMaterial*) const;

public:
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ u8 field_0x74[0x7C - 0x74];
    /* 0x7C */ u8 field_0x7C;
    /* 0x7D */ u8 field_0x7D[0x80 - 0x7D];
};  // Size: 0x80

class daNpc_Ls1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Ls1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 field_0x00;
        /* 0x01 */ s8 field_0x01;
        /* 0x04 */ f32 field_0x04;
        /* 0x08 */ f32 field_0x08;
        /* 0x0C */ int field_0x0C;
    };  // Size: 0x10

    inline daNpc_Ls1_c();

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void _nodeCB_Hand_L(J3DNode*, J3DModel*);
    void _nodeCB_Hand_R(J3DNode*, J3DModel*);
    void _Ls_hand_nodeCB_Hand_L(J3DNode*, J3DModel*);
    void _Ls_hand_nodeCB_Hand_R(J3DNode*, J3DModel*);
    bool init_LS1_0();
    bool init_LS1_1();
    bool init_LS1_2();
    bool init_LS1_3();
    bool init_LS1_4();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    int btkResID(int);
    bool setBtp(signed char, bool);
    void setMat();
    bool setBtk(signed char, bool);
    bool init_texPttrnAnm(s8, bool);
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
    u32 getMsg_LS1_3();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    bool chk_parts_notMov();
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
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(int (daNpc_Ls1_c::*)(void*), void*);
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
    BOOL wait_action1(void*);
    BOOL demo_action1(void*);
    bool demo();
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
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_L_jnt_num;
    /* 0x6CF */ s8 m_hnd_R_jnt_num;
    /* 0x6D0 */ J3DModel* field_0x6D0;
    /* 0x6D4 */ f32 field_0x6D4;
    /* 0x6D8 */ daNpc_Ls1_matAnm_c* field_0x6D8[2];
    /* 0x6E0 */ char field_0x6E0[3];
    /* 0x6E3 */ u8 field_0x6E3[0x6E8 - 0x6E3];
    /* 0x6E8 */ J3DModel* field_0x6E8;
    /* 0x6EC */ s8 m_lsHnd_L_jnt_num;
    /* 0x6ED */ s8 m_lsHnd_R_jnt_num;
    /* 0x6EE */ u8 field_0x6EE[0x6F0 - 0x6EE];
    /* 0x6F0 */ mDoExt_btkAnm field_0x6F0;
    /* 0x704 */ u8 field_0x704;
    /* 0x705 */ u8 field_0x705[0x708 - 0x705];
    /* 0x708 */ mDoExt_btpAnm field_0x708;
    /* 0x71C */ u8 field_0x71C;
    /* 0x71D */ u8 field_0x71D[0x71E - 0x71D];
    /* 0x71E */ s16 field_0x71E;
    /* 0x720 */ ProcFunc field_0x720;
    /* 0x72C */ u8 field_0x72C[0x794 - 0x72C];
    /* 0x794 */ cXyz field_0x794;
    /* 0x7A0 */ csXyz field_0x7A0;
    /* 0x7A6 */ csXyz field_0x7A6;
    /* 0x7AC */ u8 field_0x7AC[0x7CC - 0x7AC];
    /* 0x7CC */ cXyz field_0x7CC[2];
    /* 0x7E4 */ u8 field_0x7E4[0x800 - 0x7E4];
    /* 0x800 */ f32 field_0x800;
    /* 0x804 */ s16 field_0x804;
    /* 0x806 */ s16 field_0x806;
    /* 0x808 */ s16 field_0x808;
    /* 0x80A */ u8 field_0x80A[0x814 - 0x80A];
    /* 0x814 */ s16 field_0x814[4];
    /* 0x81C */ u8 field_0x81C[0x81E - 0x81C];
    /* 0x81E */ s16 field_0x81E;
    /* 0x820 */ u8 field_0x820[0x830 - 0x820];
    /* 0x830 */ s8 field_0x830;
    /* 0x831 */ u8 field_0x831;
    /* 0x832 */ u8 field_0x832[0x834 - 0x832];
    /* 0x834 */ u8 field_0x834;
    /* 0x835 */ u8 field_0x835[0x837 - 0x835];
    /* 0x837 */ bool field_0x837;
    /* 0x838 */ u8 field_0x838;
    /* 0x839 */ u8 field_0x839[0x83A - 0x839];
    /* 0x83A */ u8 field_0x83A;
    /* 0x83B */ u8 field_0x83B;
    /* 0x83C */ u8 field_0x83C;
    /* 0x83D */ bool field_0x83D;
    /* 0x83E */ u8 field_0x83E[0x840 - 0x83E];
    /* 0x840 */ u8 field_0x840;
    /* 0x841 */ u8 field_0x841;
    /* 0x842 */ u8 field_0x842[0x84B - 0x842];
    /* 0x84B */ u8 field_0x84B;
    /* 0x84C */ u8 field_0x84C;
    /* 0x84D */ s8 field_0x84D;
    /* 0x84E */ s8 field_0x84E;
    /* 0x84F */ s8 field_0x84F;
    /* 0x850 */ u8 field_0x850[0x851 - 0x850];
    /* 0x851 */ s8 field_0x851;
    /* 0x852 */ u8 field_0x852[0x853 - 0x852];
    /* 0x853 */ u8 field_0x853;
    /* 0x854 */ s8 field_0x854;
    /* 0x855 */ s8 field_0x855;
    /* 0x856 */ u8 field_0x856;
    /* 0x857 */ u8 field_0x857[0x858 - 0x857];
};  // Size: 0x858

class daNpc_Ls1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 field_0x00;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ s16 field_0x04;
        /* 0x06 */ s16 field_0x06;
        /* 0x08 */ s16 field_0x08;
        /* 0x0A */ s16 field_0x0A;
        /* 0x0C */ s16 field_0x0C;
        /* 0x0E */ s16 field_0x0E;
        /* 0x10 */ s16 field_0x10;
        /* 0x12 */ s16 field_0x12;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ u8 field_0x18;
        /* 0x19 */ u8 field_0x19[0x1C - 0x19];
        /* 0x1C */ f32 field_0x1C;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2C;
        /* 0x30 */ s16 field_0x30;
        /* 0x32 */ u8 field_0x32[0x34 - 0x32];
        /* 0x34 */ f32 field_0x34;
    };  // Size: 0x38
    daNpc_Ls1_HIO_c();
    inline virtual ~daNpc_Ls1_HIO_c();
public:
    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05[0x08 - 0x05]; // probably padding?
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ hio_prm_c field_0x0C;
};  // Size: 0x44

#endif /* D_A_NPC_LS1_H */
