#ifndef D_A_OBJ_BALANCELIFT_H
#define D_A_OBJ_BALANCELIFT_H

#include "f_op/f_op_actor.h"

class daBalancelift_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    void calc_quat();
    void set_mtx();
    void calc_weight();
    void CreateHeap();
    void CreateInit();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_BALANCELIFT_H */
