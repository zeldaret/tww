#ifndef D_A_OBJ_DRAGONHEAD_H
#define D_A_OBJ_DRAGONHEAD_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"

class daObjDragonhead_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Sph mSph;
    /* 0x404 */ u8 mAlpha;
    /* 0x405 */ bool mSwitchOn;
    /* 0x408 */ dBgW * mpBgW;
    /* 0x40C */ u8 field_0x40c;
    /* 0x410 */ cXyz mSphCenter;
    /* 0x41C */ Mtx mtx;
};

#endif /* D_A_OBJ_DRAGONHEAD_H */
