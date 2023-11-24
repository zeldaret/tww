#ifndef D_A_BGN3_H
#define D_A_BGN3_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

class bgn3_class : public fopAc_ac_c {
public:
    /* 0x00290 */ u8 m00290[0x002E4 - 0x00290];
    /* 0x002E4 */ bgn3_ke_s mHairs[40];
    /* 0x01784 */ mDoExt_3DlineMat0_c mLineMat;
    /* 0x017A0 */ u8 m017A0[0x017CC - 0x017A0];
    /* 0x017CC */ part_s3 mParts[10];
    /* 0x0FD7C */ u8 m0FD7C[0x0FDDC - 0x0FD7C];
    /* 0x0FDDC */ dCcD_GStts m0FDDC;
    /* 0x0FDFC */ dCcD_GObjInf m0FDFC;
    /* 0x0FEF4 */ u8 m0FEF4[0x0FF28 - 0x0FEF4];
    /* 0x0FF28 */ dCcD_GObjInf m0FF28;
    /* 0x10020 */ u8 m10020[0x100B4 - 0x10020];
};

#endif /* D_A_BGN3_H */
