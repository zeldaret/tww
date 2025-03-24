#ifndef D_A_OBJ_RFLW_H
#define D_A_OBJ_RFLW_H

#include "f_op/f_op_actor.h"

class daObjRflw_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_RFLW_H */
