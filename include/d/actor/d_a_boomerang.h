#ifndef D_A_BOOMERANG_H
#define D_A_BOOMERANG_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daBoomerang_blur_c : public J3DPacket {
public:
    void initBlur(MtxP, s16);
    void copyBlur(MtxP, s16);
    virtual void draw();

public:
    /* 0x010 */ void* imageData;
    /* 0x014 */ s32 field_0x14;
    /* 0x018 */ cXyz pos;
    /* 0x024 */ cXyz arr_0x24[60];
    /* 0x2F4 */ cXyz arr_0x2F4[60];
    /* 0x5C4 */ cXyz arr_0x5C4[60];
    /* 0x894 */ cXyz arr_0x894[60];
};

class daBoomerang_sightPacket_c : public dDlst_base_c {
public:
    virtual void draw();
    void setSight(cXyz*, int);
    void play(int);
};

class daBoomerang_c : public fopAc_ac_c {
public:
    typedef BOOL (daBoomerang_c::*daBoomerang_c_ProcFunc)();

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
    BOOL procWait();
    BOOL procMove();
    BOOL createHeap();

public:
    /* 0x0290 */ J3DModel* mpModel;
    /* 0x0294 */ daBoomerang_sightPacket_c mSightPacket;
    /* 0x0298 */ u8 field_0x298[0x398 - 0x298];
    /* 0x0398 */ void* field_0x398;
    /* 0x039C */ ResTIMG* field_0x39C;
    /* 0x03A0 */ daBoomerang_blur_c mBlur;
    /* 0x0F04 */ s32 arr_0xF04[5];
    /* 0x0F18 */ fopAc_ac_c* arr_0xF18[5];
    /* 0x0F2C */ u8 field_0xF2C[0xF30 - 0xF2C];
    /* 0x0F30 */ u8 field_0xF30;
    /* 0x0F31 */ u8 field_0xF31;
    /* 0x0F32 */ u8 field_0xF32[0xF34 - 0xF32];
    /* 0x0F34 */ bool mCancelFlg;
    /* 0x0F35 */ u8 field_0xF35[0xF64 - 0xF35];
    /* 0x0F64 */ dCcD_Stts mStts;
    /* 0x0FA0 */ u8 field_0xFA0[0xFC4 - 0xFA0];
    /* 0x0FC4 */ dCcD_Cps mCps;
    /* 0x10FC */ u8 field_0x10FC[0x1118 - 0x10FC];
    /* 0x1118 */ dBgS_BoomerangLinChk mLinChk;
    // FIXME: mCurrProcFunc should be at 0x1180.
    /* 0x1184 */ daBoomerang_c_ProcFunc mCurrProcFunc;
};

STATIC_ASSERT(offsetof(daBoomerang_c, mSightPacket) == 0x294);
STATIC_ASSERT(offsetof(daBoomerang_c, mBlur) == 0x3A0);
STATIC_ASSERT(offsetof(daBoomerang_c, mCancelFlg) == 0xF34);
STATIC_ASSERT(offsetof(daBoomerang_c, mStts) == 0xF64);
STATIC_ASSERT(offsetof(daBoomerang_c, mCps) == 0xFC4);
// STATIC_ASSERT(sizeof(daBoomerang_c) == 0x118C);

#endif /* D_A_BOOMERANG_H */
