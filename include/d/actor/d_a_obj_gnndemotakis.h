#ifndef D_A_OBJ_GNNDEMOTAKIS_H
#define D_A_OBJ_GNNDEMOTAKIS_H

#include "f_op/f_op_actor.h"

class daObjGnntakis_c : public fopAc_ac_c {
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

#endif /* D_A_OBJ_GNNDEMOTAKIS_H */
