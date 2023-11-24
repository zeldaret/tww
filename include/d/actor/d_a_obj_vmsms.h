#ifndef D_A_OBJ_VMSMS_H
#define D_A_OBJ_VMSMS_H

#include "f_op/f_op_actor.h"

class daObjVmsms_c : public fopAc_ac_c {
public:
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void _create();
    void _delete();
    void init_mtx();
    void check_demo() const;
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_VMSMS_H */
