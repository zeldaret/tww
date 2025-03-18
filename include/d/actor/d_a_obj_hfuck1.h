#ifndef D_A_OBJ_HFUCK1_H
#define D_A_OBJ_HFUCK1_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"

class daObjHfuck1_c : public fopAc_ac_c {
public:
    void init_mtx();
    cPhs_State _create();
    bool _execute();
    bool _draw();
    bool _delete();
    bool create_heap();
    bool checkCollision();
    static BOOL solidHeapCB(fopAc_ac_c *i_this);

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * mpModel;
    /* 0x29C */ dBgW * mpBgW;
    /* 0x2A0 */ dCcD_Stts mStts;
    /* 0x408 */ dCcD_Sph mSph;
    /* 0x40C */ fopAc_ac_c * mpHookshotActor;
};

#endif /* D_A_OBJ_HFUCK1_H */
