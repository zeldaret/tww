#ifndef D_A_OBJ_DOGUU_DEMO_H
#define D_A_OBJ_DOGUU_DEMO_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"

class daObjDoguuD_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mMtx;
    /* 0x2D0 */ bool mBgwRegistered;
    /* 0x2D1 */ u8 mUnusedParam;
    /* 0x2D4 */ u32 mShape;
};

#endif /* D_A_OBJ_DOGUU_DEMO_H */
