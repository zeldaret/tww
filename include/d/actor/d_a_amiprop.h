#ifndef D_A_AMIPROP_H
#define D_A_AMIPROP_H

#include "f_op/f_op_actor.h"

class daAmiProp_c : public fopAc_ac_c {
public:
    BOOL _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void setMoveBGMtx();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_AMIPROP_H */
