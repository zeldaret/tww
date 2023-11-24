#ifndef D_A_SHUTTER_H
#define D_A_SHUTTER_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daShutter_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateHeap();
    void Create();
    void _create();
    void set_mtx();
    void _execute();
    void shutter_move();
    void demo();
    void _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u8 m298[0x308 - 0x298];
    /* 0x308 */ cXyz m308[2];
    /* 0x320 */ u8 m320[0x335 - 0x320];
    /* 0x335 */ u8 mType;
    /* 0x336 */ u8 m336[0x33C - 0x336];
};

#endif /* D_A_SHUTTER_H */
