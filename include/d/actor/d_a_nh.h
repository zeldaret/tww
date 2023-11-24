#ifndef D_A_NH_H
#define D_A_NH_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "m_Do/m_Do_ext.h"

class daNh_c : public fopAc_ac_c {
public:
    void isTypeBottle() {}

    void setBaseMtx();
    void action(void* arg);
    void BGCheck();
    void airMove();
    void playBrkAnm();

public:
    /* 0x290 */ u8 m290[0x29C - 0x290];
    /* 0x29C */ dBgS_ObjAcch mAcch;
    /* 0x460 */ dBgS_AcchCir mAcchCir;
    /* 0x4A0 */ dCcD_Stts mStts;
    /* 0x4DC */ dCcD_Cyl mCyl;
    /* 0x60C */ mDoExt_brkAnm mBrkAnm;
    /* 0x624 */ u8 m624[0x630 - 0x624];
    /* 0x630 */ cBgS_PolyInfo mPolyInfo;
    /* 0x640 */ u8 m640[0x6A8 - 0x640];
};

#endif /* D_A_NH_H */
