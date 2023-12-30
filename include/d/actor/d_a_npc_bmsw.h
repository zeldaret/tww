#ifndef D_A_NPC_BMSW_H
#define D_A_NPC_BMSW_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

class ShopCursor_c;

class daNpc_Bmsw_c : public fopAc_ac_c {
public:
    void getArmLMtx() {}
    void getArmRMtx() {}
    void getAttentionBasePos() {}
    void setAction(int (daNpc_Bmsw_c::*)(void*), void*) {}

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void anmAtr(unsigned short);
    void CreateInit();
    void set_mtx();
    void setAttention();
    void lookBack();
    void wait01();
    void talk01();
    void wait_action(void*);
    void checkNextMailThrowOK();
    void setGameGetRupee(short);
    void TimerCountDown();
    void shiwake_game_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x968 - 0x6C4];
    /* 0x968 */ ShopCursor_c* mpShopCursor;
    /* 0x96C */ u8 m96C[0x9E4 - 0x96C];
};

class SwMail_c {
public:
    void CheckProc(void (SwMail_c::*)()) {}
    void SetProc(void (SwMail_c::*)()) {}

    void MailCreateInit(cXyz*, cXyz*);
    void getNextNo(unsigned char);
    void init();
    void set_mtx();
    void set_mtx_throw();
    void DummyInit();
    void Dummy();
    void AppearInit();
    void Appear();
    void WaitInit();
    void Wait();
    void ThrowInit(cXyz, unsigned char);
    void Throw();
    void EndInit();
    void End();
    void SeDelete();
    void move();
    void draw(dKy_tevstr_c*);

public:
    /* Place member variables here */
};

class SwCam_c {
public:
    void ActiveOff() {}
    void ActiveOn() {}
    void getCenterP() {}
    void getEyeP() {}
    void setAimIdx(signed char, signed char) {}

    void Move();

public:
    /* Place member variables here */
};

class daNpc_Bmsw_HIO_c {
public:
    daNpc_Bmsw_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BMSW_H */
