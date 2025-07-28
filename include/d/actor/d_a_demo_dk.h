#ifndef D_A_DEMO_DK_H
#define D_A_DEMO_DK_H

#include "f_op/f_op_actor.h"

class mDoExt_McaMorf;

class demo_dk_class {
public:
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ char unk290[0x1C];
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ char unk2B4[0x2];
    /* 0x2B6 */ u8 unk_2B6;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ s16 unk_2BC[2];
    /* 0x2C0 */ s16 unk_2C0;
    /* 0x2C4 */ cXyz unk_2C4;
}; // size = 0x2D0

#endif /* D_A_DEMO_DK_H */
