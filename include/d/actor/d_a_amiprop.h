#ifndef D_A_AMIPROP_H
#define D_A_AMIPROP_H

#include "f_op/f_op_actor.h"

class daAmiProp_c : public fopAc_ac_c {
public:
    bool _delete();
    void CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    void setMoveBGMtx();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_AMIPROP_H */
