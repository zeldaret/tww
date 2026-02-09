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
    /* 0x0290 */ u8 m290[0x294 - 0x290];
    /* 0x0294 */ daBoomerang_sightPacket_c mSightPacket;
    /* 0x0298 */ u8 field_0x298[0x3A0 - 0x298];
    /* 0x03A0 */ daBoomerang_blur_c mBlur;
    /* 0x03B0 */ u8 field_0x3B0[0x3C4 - 0x3B0];
    /* 0x03C4 */ cXyz arr_0x3C4[60];
    /* 0x0694 */ cXyz arr_0x694[60];
    /* 0x0964 */ cXyz arr_0x964[60];
    /* 0x0C34 */ cXyz arr_0xC34[60];
    /* 0x0F04 */ u8 field_0xF04[0xF34 - 0xF04];
    /* 0x0F34 */ bool mCancelFlg;
    /* 0x0F35 */ u8 field_0xF35[0xF64 - 0xF35];
    /* 0x0F64 */ dCcD_Stts mStts;
    /* 0x0FA0 */ u8 field_0xFA0[0xFC4 - 0xFA0];
    /* 0x0FC4 */ dCcD_Cps mCps;
    /* 0x10FC */ u8 field_0x10FC[0x1118 - 0x10FC];
    /* 0x1118 */ dBgS_BoomerangLinChk mLinChk;
    /* 0x1184 */ u8 field_0x1184[0x118C - 0x1184];
};

STATIC_ASSERT(offsetof(daBoomerang_c, mSightPacket) == 0x294);
STATIC_ASSERT(offsetof(daBoomerang_c, mBlur) == 0x3A0);
STATIC_ASSERT(offsetof(daBoomerang_c, mCancelFlg) == 0xF34);
STATIC_ASSERT(offsetof(daBoomerang_c, mStts) == 0xF64);
STATIC_ASSERT(offsetof(daBoomerang_c, mCps) == 0xFC4);
STATIC_ASSERT(sizeof(daBoomerang_c) == 0x118C);

#endif /* D_A_BOOMERANG_H */
