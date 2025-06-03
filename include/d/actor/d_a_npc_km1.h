#ifndef D_A_NPC_KM1_H
#define D_A_NPC_KM1_H

#include "f_op/f_op_actor.h"

class daNpc_Km1_c : public fopAc_ac_c {
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
    void anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(signed char);
    void init_btp(bool, int);
    void initTexPatternAnm(bool);
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
    void next_msgStatus(unsigned long*);
    void getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    void chkAttention();
    void setAttention();
    void decideType(int);
    void event_actionInit(int);
    void event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    void set_action(int (daNpc_Km1_c::*)(void*), void*);
    void wait01();
    void talk01();
    void wait_action1(void*);
    void demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x6CC - 0x6C4];
    /* 0x6CC */ u8 mHeadJntIdx;
    /* 0x6CD */ u8 mBackBoneJntIdx;
    /* 0x6CE */ u8 m6CE[0x6F4 - 0x6CE];
    /* 0x6F4 */ int (daNpc_Km1_c::*m6F4)();
    /* 0x700 */ u8 m700[0x76C - 0x700];
    /* 0x76C */ csXyz m76C;
    /* 0x772 */ u8 m772[0x774 - 0x772];
    /* 0x774 */ cXyz m774;
    /* 0x780 */ cXyz m780;
    /* 0x78C */ cXyz m78C;
    /* 0x798 */ cXyz m798;
    /* 0x7A4 */ u8 m7A4[0x7B0 - 0x7A4];
    /* 0x7B0 */ s16 m7B0;
    /* 0x7B2 */ u8 m7B2[0x7B8 - 0x7B2];
    /* 0x7B8 */ u8 m7B8;
    /* 0x7B9 */ u8 m7B9[0x7C7 - 0x7B9];
    /* 0x7C7 */ u8 m7C7;
    /* 0x7C8 */ u8 m7C8[0x7D8 - 0x7C8];
};

class daNpc_Km1_HIO_c {
public:
    daNpc_Km1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KM1_H */
