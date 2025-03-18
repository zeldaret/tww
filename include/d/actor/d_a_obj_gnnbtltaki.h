#ifndef D_A_OBJ_GNNBTLTAKI_H
#define D_A_OBJ_GNNBTLTAKI_H

#include "f_op/f_op_actor.h"

class daObjGnnbtaki_c : public fopAc_ac_c {
public:
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_GNNBTLTAKI_H */
