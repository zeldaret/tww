#ifndef D_A_OBJ_BSCURTAIN_H
#define D_A_OBJ_BSCURTAIN_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daObj_Bscurtain_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}

    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u8 m298[0x29C - 0x298];
    /* 0x29C */ J3DModel* mpModel;
};

#endif /* D_A_OBJ_BSCURTAIN_H */
