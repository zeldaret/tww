#ifndef D_A_OBJ_HCBH_H
#define D_A_OBJ_HCBH_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daObjHcbh_c : public fopAc_ac_c {
public:
    void param_get_itemNo() const {}
    void param_get_itemSaveBitNo() const {}
    void param_get_swSave() const {}
    void param_on_swSave() const {}

    void chk_appear();
    void set_mtx();
    void init_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void setup_break_condition(fopAc_ac_c*);
    void checkCollision();
    void co_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    void particle_set();
    void make_item();
    s32 _create();
    bool _delete();
    void wait_act_proc();
    void fall_act_proc();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_HCBH_H */
