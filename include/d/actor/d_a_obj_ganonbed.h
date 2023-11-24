#ifndef D_A_OBJ_GANONBED_H
#define D_A_OBJ_GANONBED_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class daObjGbed_c : public fopAc_ac_c {
public:
    void init_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
};

#endif /* D_A_OBJ_GANONBED_H */
