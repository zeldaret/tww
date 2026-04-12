#ifndef D_A_NZG_H
#define D_A_NZG_H

#include "d/d_path.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class nzg_class : public fopAc_ac_c {
public:
    /* Place member variables here */
    /* 0x290 */ u8 pad1[28];
    /* 0x2AC */ request_of_phase_process_class m2AC;
    /* 0x2B4 */ J3DModel* m2B4;
    u8 m2B8;
    u8 m2B9;
    u8 m2BA;
    u8 m2BB;
    u8 mPad2[2];
    s16 m2BE;
    s16 m2C0;
    s16 m2C2[5];
    f32 m2CC;
    f32 m2D0;
    u32 m2D4;
    dPath *m2D8;
    u8 mPad4[13];
    u8 m2E9;
    dCcD_Stts mStts;
    dCcD_Cyl m328;
};

#endif /* D_A_NZG_H */
