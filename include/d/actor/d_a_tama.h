#ifndef D_A_TAMA_H
#define D_A_TAMA_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"

class daTama_c : public fopAc_ac_c {
public:
    void setDis(f32 dis) { mDis = dis; }
    void setPartnerID(uint id) { mPartnerID = id; }
    void setSpd(f32 spd) { speedF = spd; }

    BOOL createInit();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();

public:
    /* 0x290 */ uint mPartnerID;
    /* 0x294 */ dBgS_ObjAcch mAcch;
    /* 0x458 */ dBgS_AcchCir mAcchCir;
    /* 0x498 */ dCcD_Stts mStts;
    /* 0x4D4 */ dCcD_Sph mSph;
    /* 0x600 */ f32 mDis;
};

#endif /* D_A_TAMA_H */
