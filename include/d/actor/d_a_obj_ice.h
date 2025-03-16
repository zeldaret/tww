#ifndef D_A_OBJ_ICE_H
#define D_A_OBJ_ICE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daObjIce_c : public fopAc_ac_c {
public:
    void param_get_swSave() const {}
    void param_on_swSave() const {}
    inline void setEffectMtx();

    void chk_appear();
    void set_mtx();
    void init_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void tg_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    s32 _create();
    bool _delete();
    void wait_act_proc();
    void fade_out_retire_act_proc();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_ICE_H */
