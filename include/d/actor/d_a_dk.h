#ifndef D_A_DK_H
#define D_A_DK_H

#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

struct tail_s {
    /* 0x000 */ J3DModel* models[9];
    /* 0x024 */ cXyz field_0x024[10];
    /* 0x09C */ csXyz field_0x09C[10];
    /* 0x0D8 */ cXyz field_0x0D8[10];
    /* 0x150 */ cXyz field_0x150[2];
    /* 0x168 */ csXyz field_0x168;
    /* 0x170 */ cXyz field_0x170;
};  // Size: 0x17C

class dk_class : public fopAc_ac_c {
public:

    dk_class() : field_0xACC(1, 1, 0, 0) {

    }

    /* 0x290 */ u8 field_0x290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ u8 field_0x2B4;
    /* 0x2B8 */ mDoExt_McaMorf* field_0x2B8;
    /* 0x2BC */ s16 field_0x2BC;
    /* 0x2BE */ u8 field_0x2BE[0x2C0 - 0x2BE];
    /* 0x2C0 */ s16 field_0x2C0[5];
    /* 0x2CC */ tail_s tails[4];
    /* 0x8BC */ J3DModel* mpModelKamen;
    /* 0x8C0 */ dBgS_AcchCir field_0x8C0;
    /* 0x900 */ dBgS_ObjAcch field_0x900;
    /* 0xAC4 */ u8 field_0xAC4[0xAC5 - 0xAC4];
    /* 0xAC5 */ s8 field_0xAC5;
    /* 0xAC8 */ s32 field_0xAC8;
    /* 0xACC */ dPa_smokeEcallBack field_0xACC;
    /* 0xAEC */ u8 field_0xAEC[0xAEE - 0xAEC];
    /* 0xAEE */ u8 field_0xAEE;
};  // Size: 0xAF0

class daDk_HIO_c : public JORReflexible {
public:
    daDk_HIO_c();
    virtual ~daDk_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 field_0x06[0x08 - 0x06];
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ u8 field_0x14;
};  // Size: 0x15

#endif /* D_A_DK_H */
