#ifndef D_A_OBJ_LEAVES_H
#define D_A_OBJ_LEAVES_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daObjLeaves_c : public fopAc_ac_c {
public:
    void chk_appear();
    void init_mtx();
    void birthEffect(int, cXyz*, csXyz*, _GXColor*);
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void tg_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    void _create();
    void _delete();
    void wait_proc();
    void alpha_calc_start_wait_proc();
    void item_set_wait_proc();
    void retire_wait_proc();
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_LEAVES_H */
