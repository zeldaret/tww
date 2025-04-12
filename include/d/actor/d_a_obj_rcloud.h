#ifndef D_A_OBJ_RCLOUD_H
#define D_A_OBJ_RCLOUD_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daObjRcloud_c : public fopAc_ac_c {
public:
    void param_get_arg() const {}

    void init_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    cPhs_State _create();
    bool _delete();
    void wait_act_proc();
    void clouds_lift_start_wait_act_proc();
    void clouds_lift_act_proc();
    void setup_action(int);
    bool _execute();
    void setTexMtx();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhsBVkumo;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2B0 */ u8 m2B0[0x2BC - 0x2B0];
    /* 0x2BC */ int m2BC;
    /* 0x2C0 */ int m2C0;
    /* 0x2C4 */ u8 m2C4;
    /* 0x2C5 */ u8 m2C5[0x2C8 - 0x2C5];
    /* 0x2C8 */ f32 m2C8;
};

#endif /* D_A_OBJ_RCLOUD_H */
