#ifndef D_A_MFLFT_H
#define D_A_MFLFT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

class dBgW;
class JPABaseEmitter;

struct mflft_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ s16 m298;
    /* 0x29A */ s16 m29A;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ u8 m2A0;
    /* 0x2A1 */ u8 m2A1;
    /* 0x2A2 */ u8 m2A2[0x2A4 - 0x2A2];
    /* 0x2A4 */ cXyz m2A4;
    /* 0x2B0 */ f32 m2B0;
    /* 0x2B4 */ u8 m2B4[0x2B8 - 0x2B4];
    /* 0x2B8 */ f32 m2B8;
    /* 0x2BC */ f32 m2BC;
    /* 0x2C0 */ u8 m2C0[0x2C4 - 0x2C0];
    /* 0x2C4 */ f32 m2C4;
    /* 0x2C8 */ csXyz m2C8;
    /* 0x2CE */ s16 m2CE;
    /* 0x2D0 */ f32 m2D0;
    /* 0x2D4 */ s8 m2D4[3];
    /* 0x2D7 */ u8 m2D7[0x2D8 - 0x2D7];
    /* 0x2D8 */ cXyz m2D8[3];
    /* 0x2FC */ cXyz m2FC[3];
    /* 0x320 */ dCcD_Stts mStts;
    /* 0x35C */ dCcD_Cyl mCyls[3];
    /* 0x6EC */ s16 m6EC[3];
    /* 0x6F2 */ s8 m6F2[3];
    /* 0x6F5 */ s8 m6F5;
    /* 0x6F6 */ s16 m6F6;
    /* 0x6F8 */ s16 m6F8;
    /* 0x6FA */ s16 m6FA;
    /* 0x6FC */ u8 m6FC[0x700 - 0x6FC];
    /* 0x700 */ Mtx m700;
    /* 0x730 */ dBgW* pm_bgw;
    /* 0x734 */ f32 m734;
    /* 0x738 */ mDoExt_3DlineMat1_c mLineMat;
    /* 0x774 */ JPABaseEmitter* m774;
    /* 0x778 */ s8 m778;
    /* 0x779 */ u8 m779[0x77C - 0x779];
    /* 0x77C */ // vtbl
    
    virtual void setLiftUp(cXyz);
}; // size = 0x780

#endif /* D_A_MFLFT_H */
