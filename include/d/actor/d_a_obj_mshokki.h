#ifndef D_A_OBJ_MSHOKKI_H
#define D_A_OBJ_MSHOKKI_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daObjMshokki_c : public fopAc_ac_c {
public:
    void param_get_arg() const {}

    void set_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void checkCollision();
    void co_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    void break_proc();
    void set_se();
    s32 _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_MSHOKKI_H */
