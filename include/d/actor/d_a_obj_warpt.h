#ifndef D_A_OBJ_WARPT_H
#define D_A_OBJ_WARPT_H

#include "f_op/f_op_actor.h"

class daObj_Warpt_c : public fopAc_ac_c {
public:
    void modeProcInit(int) {}

    void _createHeap();
    void createHutaHeap();
    void createBodyHeap();
    void _ride(fopAc_ac_c*);
    void isHuta();
    void isSp();
    void isOtherHuta();
    void isRealHuta();
    void warp(int);
    void onWarpBit(unsigned char);
    void isWarpBit(unsigned char);
    void setMtx();
    void initCollision();
    void setCollision();
    void breakHuta(int);
    void openHuta();
    void checkHitSE();
    void modeOpenInit();
    void modeOpen();
    void modeCloseInit();
    void modeClose();
    void modeBreakFireInit();
    void modeBreakFire();
    void modeEventWarpInit();
    void modeEventWarp();
    void normalWarp();
    void spWarp();
    void modeEventOpenInit();
    void modeEventOpen();
    void modeProc(daObj_Warpt_c::Proc_e, int);
    void _execute();
    void _draw();
    void getArg();
    void createInit();
    void _create();
    void _delete();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_WARPT_H */
