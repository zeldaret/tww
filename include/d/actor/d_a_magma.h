#ifndef D_A_MAGMA_H
#define D_A_MAGMA_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "SSystem/SComponent/c_phase.h"

class daMagma_c : public fopAc_ac_c {
public:
    inline ~daMagma_c();
    inline s32 create();
    inline s32 getPathNo() { return fopAcM_GetParam(this); }

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
};

#endif /* D_A_MAGMA_H */
