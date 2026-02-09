#ifndef D_A_BOOMERANG_H
#define D_A_BOOMERANG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daBoomerang_blur_c : public J3DPacket {
public:
    void initBlur(MtxP, s16);
    void copyBlur(MtxP, s16);
    virtual void draw();
};

class daBoomerang_sightPacket_c : public dDlst_base_c {
public:
    virtual void draw();
    void setSight(cXyz*, int);
    void play(int);
};

class daBoomerang_c : public fopAc_ac_c {
public:
    void onCancelFlg() { mCancelFlg = true; }

    daBoomerang_c();
    cPhs_State create();
    BOOL draw();
    BOOL execute();
    float getFlyMax();
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
    /* 0x290 */ u8 m290[0x294 - 0x290];
    /* 0x294 */ daBoomerang_sightPacket_c mSightPacket;
    /* 0x298 */ u8 field_0x298[0x3A0 - 0x298];
    /* 0x3A0 */ daBoomerang_blur_c mBlur;
    /* 0x23B0 */ u8 field_0x3B0[0xF34 - 0x3B0];
    /* 0xF34 */ bool mCancelFlg;
};

#endif /* D_A_BOOMERANG_H */
