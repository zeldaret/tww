#ifndef D_A_FGANON_H
#define D_A_FGANON_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"

class mDoExt_McaMorf;
class mDoExt_brkAnm;
class mDoExt_btkAnm;

class fganon_class : public fopAc_ac_c {
public:
    /* 0x290 */ f32 m290;
    /* 0x294 */ u8 m294[0x2AC - 0x294];
    /* 0x2AC */ request_of_phase_process_class m2AC;
    /* 0x2B4 */ request_of_phase_process_class m2B4;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 m2BE;
    /* 0x2BF */ u8 m2BF;
    /* 0x2C0 */ mDoExt_McaMorf* m2C0;
    /* 0x2C4 */ mDoExt_brkAnm* m2C4;
    /* 0x2C8 */ J3DModel* m2C8;
    /* 0x2CC */ mDoExt_brkAnm* m2CC;
    /* 0x2D0 */ u8 m2D0[0x386 - 0x2D0];
    /* 0x386 */ s16 m386;
    /* 0x388 */ s16 m388;
    /* 0x38A */ u8 m38A[0x3AE - 0x38A];
    /* 0x3AE */ s16 m3AE;
    /* 0x3B0 */ u8 m3B0[0x3B6 - 0x3B0];
    /* 0x3B6 */ s16 m3B6;
    /* 0x3B8 */ u8 m3B8[0x408 - 0x3B8];
    /* 0x408 */ u8 m408;
    /* 0x409 */ u8 m409[0x40C - 0x409];
    /* 0x40C */ dCcD_Sph m40C;
    /* 0x538 */ dCcD_Sph m538;
    /* 0x664 */ u8 m664[0x674 - 0x664];
    /* 0x674 */ J3DModel* m674;
    /* 0x678 */ mDoExt_btkAnm* m678;
    /* 0x67C */ mDoExt_brkAnm* m67C;
    /* 0x680 */ u8 m680[0x68C - 0x680];
    /* 0x68C */ u8 m68C;
    /* 0x68D */ u8 m68D[0x68F - 0x68D];
    /* 0x68F */ u8 m68F;
    /* 0x690 */ u8 m690;
    /* 0x691 */ u8 m691[0x6B4 - 0x691];
    /* 0x6B4 */ uint mCapeID;
    /* 0x6B8 */ dBgS_AcchCir m6B8;
    /* 0x6F8 */ dBgS_Acch m6F8;
    /* 0x8BC */ dCcD_Stts mStts;
    /* 0x8F8 */ dCcD_GObjInf mCcDObjInf;
    /* 0x9F0 */ u8 m9F0[0xA28 - 0x9F0];
    /* 0xA28 */ dCcD_Sph mA28;
    /* 0xB54 */ u8 mB54[0xB88 - 0xB54];
    /* 0xB88 */ u8 mB88;
    /* 0xB89 */ u8 mB89[0xB8A - 0xB89];
    /* 0xB8A */ u8 mB8A;
    /* 0xB8B */ u8 mB8B[0xB8C - 0xB8B];
};

class daFganon_HIO_c {
public:
    daFganon_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_FGANON_H */
