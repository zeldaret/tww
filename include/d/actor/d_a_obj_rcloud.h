#ifndef D_A_OBJ_RCLOUD_H
#define D_A_OBJ_RCLOUD_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "m_Do/m_Do_ext.h"

class daObjRcloud_c : public fopAc_ac_c {
public:
    typedef void (daObjRcloud_c::*ProcFunc)();

    enum Param_e {
        PRM_ARG_W = 1,
        PRM_ARG_S = 0,
    };
    int param_get_arg() const { return daObj::PrmAbstract(this, PRM_ARG_W, PRM_ARG_S); }


    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);

    bool create_heap();
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
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2B0 */ ProcFunc mCurrentActProc;
    /* 0x2BC */ int m2BC;
    /* 0x2C0 */ int mDemoNameIndex;
    /* 0x2C4 */ u8 mResourceLoadedFlag;
    /* 0x2C5 */ u8 m2C5[0x2C8 - 0x2C5];
    /* 0x2C8 */ f32 mCloudAnimProgress;
};
#endif /* D_A_OBJ_RCLOUD_H */
