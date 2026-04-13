#ifndef D_A_OBJ_GTAKI_H
#define D_A_OBJ_GTAKI_H

#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daObjGtaki_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void set_effect() {}

    void setDummyTexture();
    BOOL CreateHeap();
    bool CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_btkAnm mBtkAnm;
    /* 0x2B0 */ dCcD_Stts mStts;
    /* 0x2EC */ dCcD_Cyl mCyl;
    /* 0x41C */ dBgW* mpBgW;
    /* 0x420 */ Mtx mMtx;
    /* 0x450 */ dKy_tevstr_c mTevStr;
};  // Size: 0x500

#endif /* D_A_OBJ_GTAKI_H */
