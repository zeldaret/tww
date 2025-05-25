#ifndef D_A_NPC_KM1_H
#define D_A_NPC_KM1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Km1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        
    };

    void getAttPos() {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getEyePos() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}

    void createInit();
    void setMtx();
    bool anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(signed char);
    u8 init_btp(bool, int);
    bool initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void setStt(signed char);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    bool chkAttention();
    void setAttention();
    bool decideType(int);
    void event_actionInit(int);
    bool event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    void set_action(int (daNpc_Km1_c::*)(void*), void*);
    void wait01();
    void talk01();
    void wait_action1(void*);
    void demo();
    bool _draw();
    bool _execute();
    bool _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x6CC - 0x6C4];
    /* 0x6CC */ u8 mHeadJntIdx;
    /* 0x6CD */ u8 mBackBoneJntIdx;
    /* 0x6CE */ u8 field_0x6CE[0x6F4 - 0x6CE];
    /* 0x6F4 */ int (daNpc_Km1_c::*field_0x6F4)();
    /* 0x700 */ u8 field_0x700[0x738 - 0x700];
    /* 0x700 */ cXyz field_0x738;
    /* 0x700 */ u8 field_0x744[0x76C - 0x744];
    /* 0x76C */ csXyz field_0x76C;
    /* 0x772 */ u8 field_0x772[0x774 - 0x772];
    /* 0x774 */ cXyz field_0x774;
    /* 0x780 */ cXyz field_0x780;
    /* 0x78C */ cXyz field_0x78C;
    /* 0x798 */ cXyz field_0x798;
    /* 0x7A4 */ f32 field_0x7A4;
    /* 0x7A8 */ u8 field_0x7A8[0x7AC - 0x7A8];
    /* 0x7AC */ f32 field_0x7AC;

    /* 0x7B0 */ s16 field_0x7B0;
    /* 0x7B2 */ s16 field_0x7B2;
    /* 0x7B4 */ s8 field_0x7B4; 
    /* 0x7B5 */ s8 field_0x7B5;
    /* 0x7B6 */ u8 field_0x7B6[0x7B8 - 0x7B6];
    /* 0x7B8 */ u8 field_0x7B8;
    /* 0x7B9 */ u8 field_0x7B9[0x7BC - 0x7B9];
    /* 0x7BC */ s32 field_0x7BC; 
    /* 0x7C0 */ s32 field_0x7C0; 
    /* 0x7C4 */ u16 field_0x7C5;
    /* 0x7C6 */ bool mHeadOnlyFollow;
    /* 0x7C7 */ u8 field_0x7C7;
    /* 0x7C8 */ u8 field_0x7C8[0x7CA - 0x7C8];
    /* 0x7CA */ s8 field_0x7CA;
    /* 0x7CB */ s8 field_0x7CB;
    /* 0x7CC */ s8 field_0x7CC;
    /* 0x7CD */ s8 field_0x7CD;
    /* 0x7CE */ s8 field_0x7CE;
    /* 0x7CF */ u8 field_0x7CF;
    /* 0x7D0 */ s8 field_0x7D0;
    /* 0x7D0 */ s8 field_0x7D1;
    /* 0x7D0 */ s8 field_0x7D2;
    /* 0x7D0 */ s8 field_0x7D3;
    /* 0x7D0 */ s8 field_0x7D4;
    /* 0x7D0 */ s8 field_0x7D5;
    /* 0x7D0 */ s8 field_0x7D6;
    /* 0x7D0 */ s8 field_0x7D7;
};  // Size: 0x7D8

class daNpc_Km1_HIO_c : mDoHIO_entry_c {
    struct daNpc_Km1_HIO__PrmTbl{
        s16 field_0[0x9];
        s16 field_12;
        f32 mAttentionArrowYOffset;
        f32 field_18;
    };  // Size: 0x1C
public:
    daNpc_Km1_HIO_c();
    virtual ~daNpc_Km1_HIO_c(){};
public:
    /* Place member variables here */
    /* 0x4  */ s8  field_0x4;
    /* 0x5  */ s8  field_0x5;
    /* 0x6  */ s8  field_0x6;
    /* 0x7  */ s8  field_0x7;
    /* 0x8  */ int field_0x8;
    /* 0xC  */ daNpc_Km1_HIO__PrmTbl mPrmTbl;

};

#endif /* D_A_NPC_KM1_H */
