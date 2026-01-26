#ifndef D_A_NPC_AC1_H
#define D_A_NPC_AC1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

class daNpc_Ac1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void nodeWngControl(J3DNode*, J3DModel*);
    void nodeArmControl(J3DNode*, J3DModel*);
    void nodeAc1Control(J3DNode*, J3DModel*);
    void init_AC1_0();
    void createInit();
    void setMtx(bool);
    void anmNum_toResID(int);
    void wingAnmNum_toResID(int);
    void btpNum_toResID(int);
    void setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_partsNotMove();
    void lookBack();
    void next_msgStatus(unsigned long*);
    void getBitMask();
    void getMsg_AC1_0();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void charDecide(int);
    void event_actionInit(int);
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Ac1_c::*)(void*), void*);
    void setStt(signed char);
    void wait_1();
    void talk_1();
    void wait_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_wng_Anm();
    void create_arm_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x6CC - 0x6C4];
    /* 0x6CC */ u8 m6CC;
    /* 0x6CD */ u8 m6CD;
    /* 0x6CE */ u8 m6CE;
    /* 0x6CF */ u8 m6CF;
    /* 0x6D0 */ u8 m6D0[0x6D4 - 0x6D0];
    /* 0x6D4 */ J3DModel* m6D4;
    /* 0x6D8 */ u8 m6D8[0x6DC - 0x6D8];
    /* 0x6DC */ J3DAnmTexPattern* m6DC;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnim;
    /* 0x6F4 */ u8 m6F4;
    /* 0x6F5 */ u8 m6F5[0x6FC - 0x6F5];
    /* 0x6FC */ mDoExt_McaMorf* m6FC;
    /* 0x700 */ u8 m700;
    /* 0x701 */ u8 m701;
    /* 0x702 */ u8 m702[0x708 - 0x702];
    /* 0x708 */ mDoExt_McaMorf* m708;
    /* 0x70C */ u8 m70C[0x77C - 0x70C];
    /* 0x77C */ dNpc_PathRun_c mPathRun;
    /* 0x784 */ dNpc_EventCut_c mEventCut;
    /* 0x7E8 */ u8 m7E8[0x7F4 - 0x7E8];
    /* 0x7F4 */ cXyz m7F4;
    /* 0x800 */ csXyz m800;
    /* 0x806 */ u8 m806[0x814 - 0x806];
    /* 0x814 */ cXyz m814;
    /* 0x820 */ u8 m820[0x82C - 0x820];
    /* 0x82C */ f32 m82C;
    /* 0x830 */ u8 m830[0x84C - 0x830];
    /* 0x84C */ s16 m84C;
    /* 0x84E */ u8 m84E[0x852 - 0x84E];
    /* 0x852 */ s16 m852;
    /* 0x854 */ s16 m854;
    /* 0x856 */ u8 m856[0x858 - 0x856];
    /* 0x858 */ u8 m858;
    /* 0x859 */ u8 m859[0x85D - 0x859];
    /* 0x85D */ u8 m85D;
    /* 0x85E */ u8 m85E;
    /* 0x85F */ u8 m85F;
    /* 0x860 */ u8 m860;
    /* 0x861 */ u8 m861;
    /* 0x862 */ u8 m862[0x863 - 0x862];
    /* 0x863 */ u8 m863;
    /* 0x864 */ u8 m864[0x869 - 0x864];
    /* 0x869 */ u8 m869;
    /* 0x86A */ u8 m86A[0x86B - 0x86A];
    /* 0x86B */ u8 m86B;
    /* 0x86C */ u8 m86C[0x86E - 0x86C];
    /* 0x86E */ u8 m86E;
    /* 0x86F */ u8 m86F[0x870 - 0x86F];
    /* 0x870 */ u8 m870;
    /* 0x871 */ u8 m871;
    /* 0x872 */ u8 m872[0x874 - 0x872];
    /* 0x874 */ u8 m874;
    /* 0x875 */ u8 m875;
    /* 0x876 */ u8 m876;
    /* 0x877 */ u8 m877;
    /* 0x878 */ u8 m878[0x879 - 0x878];
    /* 0x879 */ u8 m879;
    /* 0x87A */ u8 m87A[0x87C - 0x87A];
};

class daNpc_Ac1_HIO_c {
public:
    daNpc_Ac1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_AC1_H */
