#ifndef D_A_OBJ_AJAVW_H
#define D_A_OBJ_AJAVW_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daObjAjavW_c : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ mDoExt_btkAnm mBtk;
    /* 0x2B0 */ dBgW* mBgW;
};

#endif /* D_A_OBJ_AJAVW_H */
