#ifndef D_A_OBJ_YGUSH00_H
#define D_A_OBJ_YGUSH00_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/actor/d_a_obj_gryw00.h"

class daObjYgush00_c : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mLoadYgush00Phs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2B0 */ mDoExt_bckAnm mBckAnm;
    /* 0x2C0 */ u32 mType;
    /* 0x2C4 */ daObjGryw00_c* mpGryw00;
};

#endif /* D_A_OBJ_YGUSH00_H */
