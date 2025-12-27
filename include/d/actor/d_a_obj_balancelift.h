#ifndef D_A_OBJ_BALANCELIFT_H
#define D_A_OBJ_BALANCELIFT_H

#include "f_op/f_op_actor.h"

class daBalancelift_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void calc_quat();
    void set_mtx();
    void calc_weight();
    void CreateHeap();
    void CreateInit();

public:
    /* Place member variables here */
};

class daBalancelift_HIO_c {
public:
    daBalancelift_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_BALANCELIFT_H */
