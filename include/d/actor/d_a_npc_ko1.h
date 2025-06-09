#ifndef D_A_NPC_KO1_H
#define D_A_NPC_KO1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_msg.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;

class ko_hna_class : public fopAc_ac_c{};
class ko_bou_class : public fopAc_ac_c{};
class ko_ob_class : public fopAc_ac_c{};

class daNpc_Ko1_c : public fopNpc_npc_c {

public:
    struct anm_prm_c {
        s8 field0;
        s8 field1;
        f32 field4;
        f32 field8;
        s32 fieldC;
        s32 field10;
    };

    void nodeHedControl(J3DNode*, J3DModel*);
    void nodeBlnControl(J3DNode*, J3DModel*);
    void nodeKo1Control(J3DNode*, J3DModel*);
    bool init_HNA_0();
    bool init_HNA_1();
    bool init_HNA_2();
    bool init_HNA_3();
    bool init_HNA_4();
    bool init_BOU_0();
    bool init_BOU_1();
    bool init_BOU_2();
    bool init_BOU_3();
    s8 createInit();
    void setMtx(bool);
    s32 anmNum_toResID(int);
    s32 headAnmNum_toResID(int);
    s32 balloon_anmNum_toResID(int);
    s32 btpNum_toResID(int);
    bool setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    s32 setAnm_anm(anm_prm_c*);
    s32 set_balloonAnm_anm(anm_prm_c*);
    void set_balloonAnm_NUM(int);
    void setAnm_NUM(int, int);
    bool setAnm();
    void setPlaySpd(float);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_manzai_1();
    void chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(unsigned long*);
    void getMsg_HNA_0();
    void getMsg_HNA_1();
    void getMsg_HNA_2();
    void getMsg_HNA_3();
    void getMsg_BOU_0();
    void getMsg_BOU_1();
    void bitCount(unsigned char);
    void getMsg_BOU_2();
    u32 getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(fpc_ProcID);
    void partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    void check_landOn();
    void ko_setPthPos();
    void set_tgtPos(cXyz);
    void ko_movPass();
    void ko_clcMovSpd();
    void ko_clcSwmSpd();
    void ko_nMove();
    void chk_routeAngle(cXyz&, short*);
    void routeWallCheck(cXyz&, cXyz&, short*);
    void chk_ForwardGroundY(short);
    void chk_wallJump(short);
    void routeCheck(float, short*);
    void chk_start_swim();
    void get_crsActorID();
    void chk_areaIn(float, cXyz);
    void setPrtcl_Hamon(float, float);
    void setPrtcl_HanaPachi();
    void charDecide(int);
    void event_actionInit(int);
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Ko1_c::*)(void*), void*);
    void clrSpd();
    void setStt(signed char);
    void wait_1();
    void wait_2();
    void wait_3();
    void wait_4();
    void wait_5(signed char);
    void wait_6();
    void wait_7();
    void wait_9();
    void wait_a();
    void walk_1();
    void walk_2(signed char, signed char);
    void walk_3();
    void swim_1();
    void swim_2();
    void attk_1();
    void attk_2(signed char, signed char);
    void attk_3();
    void down_1(signed char);
    void talk_1();
    void talk_2();
    void manzai();
    void neru_1();
    void neru_2();
    int hana_action1(void*);
    int hana_action2(void*);
    int hana_action3(void*);
    int hana_action4(void*);
    int hana_action5(void*);
    int wait_action1(void*);
    int wait_action2(void*);
    int wait_action3(void*);
    int wait_action4(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_hed_Anm();
    void create_bln_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    u8 pad6C4[0x8];
    s8 field_0x6CC;
    s8 field_0x6CD;
    s8 field_0x6CE;       
    s8 field_0x6CF;
    s8 field_0x6D0;
    Mtx field_0x6D4;
    mDoExt_McaMorf* field_0x704;  
    J3DModel* field_0x708;
    u32 pad70C;
    mDoExt_McaMorf* field_0x710;
    /*0x714*/ J3DAnmTexPattern* m_hed_tex_pttrn;
    mDoExt_btpAnm field_0x718;
    u8 field_0x72C;
    s16 field_0x72E;
    u8 pad730[0xC];
    /*0x73C*/ dNpc_PathRun_c mPathRun;
    /*0x744*/ u32 pad744;
    /*0x748*/ dNpc_EventCut_c mEventCut;
    u8 pad7B4[0x10];
    cXyz field_0x7C4;
    csXyz field_0x7D0;
    csXyz field_0x7D6;
    cXyz field_0x7DC;
    cXyz field_0x7E8;
    u8 pad7F4[0x805-0x7F4];
    u8 field_0x805;
    u8 pad806[0x80C-0x806];
    cXyz field_0x80C;
    u8 pad810[0x824 - 0x818];
    f32 field_0x824;
    f32 field_0x828;
    u8 pad828[0x848 - 0x82C];
    u32 field_0x848;
    u8 pad84C[0x85E - 0x84C];
    s8 field_0x85E;
    s8 field_0x85F;
    s8 field_0x860;
    s8 field_0x861;
    u8 pad862[0x865 - 0x862];
    u8 field_0x865;
    u8 pad866[0x86C - 0x866];   
    u8 field_0x86C;
    u8 pad8CD[0x876 - 0x86D];  
    u8 field_0x876; 
    u8 field_0x877;
    u8 pad878[0x89C - 0x878];
    u8 field_0x89C;
    u8 field_0x89D;
    s8 field_0x89E;
    s8 field_0x89F;
    u8 pad8A0;
    s8 field_0x8A1;
    u8 pad8A2;
    s8 field_0x8A3;
    s8 field_0x8A4;
    s8 field_0x8A5;  
    s8 field_0x8A6;
    s8 field_0x8A7;
    s32 field_0x8A8;

};

class daNpc_Ko1_childHIO_c: public mDoHIO_entry_c {
public:
    daNpc_Ko1_childHIO_c();

public:
    char pad04[0x5C-0x04];
    u32 field5C;
    /* Place member variables here */
};

class daNpc_Ko1_HIO_c: public mDoHIO_entry_c {
    struct hio_prm_child_c{
        u8 pad[0x58];
    };
public:
    daNpc_Ko1_HIO_c();

public:
    s8 mNo;
    u32 field8;
    daNpc_Ko1_childHIO_c children[2];
    struct hio_prm_c {
        hio_prm_child_c childtable[2];
	// .4byte 0x20001F40
	// .4byte 0xE0C0E0C0
	// .4byte 0x00001F40
	// .4byte 0x0000E0C0
	// .4byte 0x07D00640
	// .4byte 0x42B40000
	// .4byte 0x00000004
	// .4byte 0x08000000
	// .4byte 0x3F666666
	// .4byte 0x3F800000
	// .4byte 0x3F000000
	// .4byte 0x41A80000
	// .4byte 0x3DCCCCCD
	// .4byte 0x41200000
	// .4byte 0x3E99999A
	// .4byte 0x42200000
	// .4byte 0x42A00000
	// .4byte 0x43480000
	// .4byte 0x43960000
	// .4byte 0x43160000
	// .4byte 0x44898000
	// .4byte 0x44BB8000
	// .4byte 0x20001F40
	// .4byte 0xE0C0E0C0
	// .4byte 0x00001F40
	// .4byte 0x0000E0C0
	// .4byte 0x07D00640
	// .4byte 0x42B40000
	// .4byte 0x00000006
	// .4byte 0x08000000
	// .4byte 0x3E99999A
	// .4byte 0x40C00000
	// .4byte 0x3ECCCCCD
	// .4byte 0x41A80000
	// .4byte 0x3DCCCCCD
	// .4byte 0x41400000
	// .4byte 0x3FC00000
	// .4byte 0x42C80000
	// .4byte 0x00000000
	// .4byte 0x43AF0000
	// .4byte 0x43FA0000
	// .4byte 0x43160000
	// .4byte 0x00000000
	// .4byte 0x00000000
    };
    /* Place member variables here */
};

#endif /* D_A_NPC_KO1_H */
