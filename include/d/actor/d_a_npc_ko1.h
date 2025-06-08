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
        
    };

    void nodeHedControl(J3DNode*, J3DModel*);
    void nodeBlnControl(J3DNode*, J3DModel*);
    void nodeKo1Control(J3DNode*, J3DModel*);
    BOOL init_HNA_0();
    BOOL init_HNA_1();
    BOOL init_HNA_2();
    BOOL init_HNA_3();
    BOOL init_HNA_4();
    BOOL init_BOU_0();
    BOOL init_BOU_1();
    BOOL init_BOU_2();
    BOOL init_BOU_3();
    void createInit();
    void setMtx(bool);
    void anmNum_toResID(int);
    void headAnmNum_toResID(int);
    void balloon_anmNum_toResID(int);
    void btpNum_toResID(int);
    void setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    void setAnm_anm(anm_prm_c*);
    void set_balloonAnm_anm(anm_prm_c*);
    void set_balloonAnm_NUM(int);
    void setAnm_NUM(int, int);
    void setAnm();
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
    ///* 0x6C4 */ u8 m6C4[0x8AC - 0x6C4];
    u8 pad6C4[0x8];
    s8 field_0x6CC;
    s8 field_0x6CD;
    s8 field_0x6CE;       
    s8 field_0x6CF;
    s8 field_0x6D0;
    Mtx field_0x6D4;
    u32 field_0x704;
    u32 field_0x708;
    u8 pad70C[0x7DC-0x70C];
    cXyz field_0x7DC;
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
