#ifndef D_A_OBJ_PBCO_H
#define D_A_OBJ_PBCO_H

#include "f_op/f_op_actor.h"

class daObj_Pbco_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    void set_mtx();
    void CreateHeap();
    void CreateInit();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_PBCO_H */
