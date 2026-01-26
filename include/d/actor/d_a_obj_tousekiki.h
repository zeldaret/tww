#ifndef D_A_OBJ_TOUSEKIKI_H
#define D_A_OBJ_TOUSEKIKI_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class mDoExt_McaMorf;

class daObj_Tousekiki_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    inline void demo_move();
    inline void set_mtx();

    BOOL CreateHeap();

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ mDoExt_McaMorf* mMorf;
    /* 0x2A0 */ Mtx m2A0;
    /* 0x2D0 */ u16 m2D0;
    /* 0x2D4 */ dCcD_Stts mStts;
    /* 0x310 */ dCcD_Cyl mCyl;
}; // size = 0x440

#endif /* D_A_OBJ_TOUSEKIKI_H */
