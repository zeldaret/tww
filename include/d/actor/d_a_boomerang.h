#ifndef D_A_BOOMERANG_H
#define D_A_BOOMERANG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daBoomerang_c : public fopAc_ac_c {
public:
    void onCancelFlg() { mCancelFlg = true; }

    daBoomerang_c();
    s32 create();
    BOOL draw();
    BOOL execute();
    void getFlyMax();
    void rockLineCallback(fopAc_ac_c*);
    void setAimActor(fopAc_ac_c*);
    void setLockActor(fopAc_ac_c*, int);
    void resetLockActor();
    void setRoomInfo();
    void setKeepMatrix();
    void setAimPos();
    void checkBgHit(cXyz*, cXyz*);
    void procWait();
    void procMove();
    void createHeap();

public:
    /* Place member variables here */
    /* 0x290 */ u8 m290[0xF34 - 0x290];
    /* 0xF34 */ bool mCancelFlg;
};

class daBoomerang_blur_c {
public:
    void initBlur(MtxP, s16);
    void copyBlur(MtxP, s16);
    void draw();
};

class daBoomerang_sightPacket_c {
public:
    void draw();
    void setSight(cXyz*, int);
    void play(int);
};

#endif /* D_A_BOOMERANG_H */
