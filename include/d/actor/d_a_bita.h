#ifndef D_A_BITA_H
#define D_A_BITA_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"

class J3DModel;
class mDoExt_brkAnm;
class dBgW;

class bita_class : public fopAc_ac_c {
public:
    enum Mode {
        MODE_NORMAL = 0x0,
        MODE_DEAD = 0x1,
    };

    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpModelEf;
    /* 0x2A0 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2A4 */ u8 mType;
    /* 0x2A5 */ u8 mPrmScale;
    /* 0x2A6 */ u8 mTimer;
    /* 0x2A7 */ u8 field_0x2a7;
    /* 0x2A8 */ u8 mMode;
    /* 0x2A9 */ u8 mSub;
    /* 0x2AA */ u8 field_0x2aa;
    /* 0x2AB */ u8 field_0x2ab;
    /* 0x2AC */ dCcD_Stts mStts;
    /* 0x2E8 */ dCcD_Cyl mCyl;
    /* 0x418 */ Mtx mMtx;
    /* 0x448 */ dBgW* mpBgW;
};

#endif /* D_A_BITA_H */
