#ifndef D_A_SWPROPELLER_H
#define D_A_SWPROPELLER_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"

class daSwProp_c : public fopAc_ac_c {
public:
    bool _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ u8 m290[0x294 - 0x290];
    /* 0x294 */ void* m294;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ u8 m408[0x43C - 0x408];
    /* 0x43C */ dBgS_Acch mAcch;
    /* 0x600 */ dBgS_AcchCir mAcchCir;
    /* 0x640 */ s16 mRotY;
    /* 0x642 */ s16 mRotYVel;
    /* 0x644 */ u8 m644[0x648 - 0x644];
    /* 0x648 */ u32 m648;
    /* 0x64C */ u8 m64C[0x800 - 0x64C];
};

#endif /* D_A_SWPROPELLER_H */
