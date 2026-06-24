#ifndef D_A_NPC_YM1_H
#define D_A_NPC_YM1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daNpc_Ym1_c : public fopNpc_npc_c {
public:

    typedef int (daNpc_Ym1_c::*ActionFunc)(void*);
    struct anm_prm_c {
        s8 m0;
        s8 m1;
        u16 m2;
        f32 m4;
        f32 m8;
        u32 mC;
    };

    void setKariFlg();
    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_YM1_0();
    bool init_YM1_1();
    bool init_YM2_0();
    bool init_YM2_1();
    bool init_YM2_2();
    bool init_YM2_3();
    bool init_YMx_error();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool init_texPttrnAnm(signed char, bool);
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
    u16 next_msgStatus(unsigned long*);
    unsigned long getMsg_YM1_0();
    unsigned long getMsg_YM1_1();
    unsigned long getMsg_YM2_0();
    unsigned long getMsg_YM2_1();
    unsigned long getMsg_YM2_2();
    unsigned long getMsg_YM2_3();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void set_collision_sp();
    void set_cutGrass();
    bool chk_BlackPig();
    bool chk_nbt_attn();
    bool chk_talk();
    bool chk_parts_notMov();
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    bool set_action(int (daNpc_Ym1_c::*)(void*), void*);
    void setStt(signed char);
    bool chk_areaIN(float, cXyz);
    bool kari_1();
    bool wait_1();
    bool wait_2();
    bool talk_1();
    bool turn_1();
    void NBTwai();
    void SITwai();
    int wait_action1(void*);
    int wait_action2(void*);
    void wait_action3(void*);
    void wait_action4(void*);
    void demo_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    void headCreateHeap();
    void itemCreateHeap();
    void CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_L_jnt_num;
    /* 0x6CF */ s8 m_hnd_R_jnt_num;
    /* 0x6D0 */ J3DModel* m6D0;
    /* 0x6D4 */ char mArcName[4];
    /* 0x6D8 */ //u8 m6D8[0x6DC - 0x6D8];
    /* 0x6DC */ J3DModel* mpHeadModel;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u8 m6F4;
                u8 m6F5;
                s16 m6F6;
                u32 m6F8;
                ActionFunc mCurrActionFunc;
    /* 0x704 */ dCcD_Cyl mCyl704;
    /* 0x834 */ cXyz m834;     
                csXyz mRotTarget;
    /* 0x846 */ csXyz m846;
                Vec m84C;
    /* 0x84C */ //u8 m858[0x870 - 0x858];
                cXyz m858;
                Vec m864;
                Vec m870;
                f32 m87C;
                s16 m880;
                s16 m882;
                s16 m884;
                u8 m886;
                s32 m888;
                
                s16 m88C;
                s16 m88E;
    /* 0x890 */ s16 mKariTimer;
    /* 0x892 */ u8 m892[0x896 - 0x892];
                s16 m896;
                s8 m898;
                u8 m899;
                u8 m89A;
    /* 0x89B */ u8 mKariFlag;
    /* 0x89C */ u8 m89C;
    /* 0x89D */ u8 m89D;
    /* 0x89E */ u8 m89E;
    /* 0x89F */ u8 m89F;
    /* 0x8A0 */ u8 m8A0;
    /* 0x8A1 */ u8 m8A1;
                u8 m8A2;
                u8 m8A3;
    /* 0x8A4 */ bool m8A4;
    /* 0x8A5 */ u8 m8A5;
    /* 0x8A6 */ u8 m8A6;
                s8 m8A7;
                u8 m8A8;
                u8 m8A9;
                s8 m8AA;
    /* 0x8AB */ s8 m8AB;
    /* 0x8AC */ s8 m8AC;
    /* 0x8AD */ s8 m8AD;
    /* 0x8AE */ u8 m8AE;
    /* 0x8AF */ s8 m8AF;
    /* 0x8B0 */ s8 mSubType;
    /* 0x8B1 */ s8 mStaff;
    /* 0x8B2 */ u8 m8B2;
                s8 m8B3;

};




#endif /* D_A_NPC_YM1_H */
