#ifndef D_A_OBJ_QUAKE_H
#define D_A_OBJ_QUAKE_H

#include "f_op/f_op_actor.h"

class daObjQuake_c : public fopAc_ac_c {
public:
    void _create();
    void _delete();
    void _is_delete();
    void _execute();
    void getPrmType();
    void getPrmSch();
    void getPrmPower();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_QUAKE_H */
