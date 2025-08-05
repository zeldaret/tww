#ifndef D_A_OBJ_OHATCH_H
#define D_A_OBJ_OHATCH_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

class dBgW;

class daObjOhatch_c : public fopAc_ac_c {
    typedef void (daObjOhatch_c::*ActionFunc)();

    enum Param_e {
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0,
    };

public:
    s32 param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

    void set_mtx();
    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    cPhs_State _create();
    bool _delete();
    void close_wait_act_proc();
    void tremor_act_proc();
    void open_act_proc();
    void vibrate_act_proc();
    void open_wait_act_proc();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ s32 m29C;
    /* 0x2A0 */ dBgW* mBgW1;
    /* 0x2A4 */ dBgW* mBgW2;
    /* 0x2A8 */ Mtx m2A8;
    /* 0x2D8 */ s16 m2D8;
    /* 0x2DC */ ActionFunc mActionFunc;
    /* 0x2E8 */ f32 m2E8;
    /* 0x2EC */ s32 m2EC;
    /* 0x2F0 */ s16 m2F0;
    /* 0x2F2 */ s16 m2F2;
}; // size = 0x2F4

#endif /* D_A_OBJ_OHATCH_H */
