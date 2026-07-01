#ifndef D_A_NPC_YM1_H
#define D_A_NPC_YM1_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daNpc_Ym1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void setKariFlg();
    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void init_YM1_0();
    void init_YM1_1();
    void init_YM2_0();
    void init_YM2_1();
    void init_YM2_2();
    void init_YM2_3();
    void init_YMx_error();
    void createInit();
    void play_animation();
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
    void getMsg_YM1_0();
    void getMsg_YM1_1();
    void getMsg_YM2_0();
    void getMsg_YM2_1();
    void getMsg_YM2_2();
    void getMsg_YM2_3();
    void getMsg();
    void eventOrder();
    void checkOrder();
    void set_collision_sp();
    void set_cutGrass();
    void chk_BlackPig();
    void chk_nbt_attn();
    void chk_talk();
    void chk_parts_notMov();
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Ym1_c::*)(void*), void*);
    void setStt(signed char);
    void chk_areaIN(float, cXyz);
    void kari_1();
    void wait_1();
    void wait_2();
    void talk_1();
    void turn_1();
    void NBTwai();
    void SITwai();
    void wait_action1(void*);
    void wait_action2(void*);
    void wait_action3(void*);
    void wait_action4(void*);
    void demo_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void bodyCreateHeap();
    void headCreateHeap();
    void itemCreateHeap();
    void CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 mHeadJointIdx;
    /* 0x6CD */ s8 mBboneJointIdx;
    /* 0x6CE */ s8 mHandLJointIndex;
    /* 0x6CF */ s8 mHandRJointIndex;
    /* 0x6D0 */ J3DModel* m6D0;
    /* 0x6D4 */ char mArcName[4];
    /* 0x6D8 */ u8 m6D8[0x6DC - 0x6D8];
    /* 0x6DC */ J3DModel* mpHeadModel;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u8 m6F4[0x704 - 0x6F4];
    /* 0x704 */ dCcD_Cyl mCyl;
    /* 0x834 */ u8 m834[0x842 - 0x834];
    /* 0x842 */ s16 mRotYTarget;
    /* 0x844 */ u8 m844[0x846 - 0x844];
    /* 0x846 */ csXyz m846;
    /* 0x84C */ u8 m84C[0x890 - 0x84C];
    /* 0x890 */ s16 mKariTimer;
    /* 0x892 */ u8 m892[0x89B - 0x892];
    /* 0x89B */ u8 mKariFlag;
    /* 0x89C */ u8 m89C;
    /* 0x89D */ u8 m89D;
    /* 0x89E */ u8 m89E;
    /* 0x89F */ u8 m89F[0x8A0 - 0x89F];
    /* 0x8A0 */ u8 m8A0;
    /* 0x8A1 */ u8 m8A1[0x8A4 - 0x8A1];
    /* 0x8A4 */ u8 m8A4;
    /* 0x8A5 */ u8 m8A5;
    /* 0x8A6 */ u8 m8A6[0x8AB - 0x8A6];
    /* 0x8AB */ u8 m8AB;
    /* 0x8AC */ u8 m8AC[0x8AD - 0x8AC];
    /* 0x8AD */ u8 m8AD;
    /* 0x8AE */ u8 m8AE[0x8AF - 0x8AE];
    /* 0x8AF */ u8 m8AF;
    /* 0x8B0 */ s8 mSubType;
    /* 0x8B1 */ s8 mStaff;
    /* 0x8B2 */ u8 m8B2[0x8B4 - 0x8B2];
};

class daNpc_Ym1_childHIO_c {
public:
    daNpc_Ym1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Ym1_HIO_c {
public:
    daNpc_Ym1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_YM1_H */
