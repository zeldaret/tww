#ifndef D_A_SWATTACK_H
#define D_A_SWATTACK_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"

class daSwAt_c : public fopAc_ac_c {
public:
    s32 _create();
    bool _execute();
    bool _draw();
    bool _delete();
    void CreateInit();

public:
    /* 0x290 */ u32 field_0x290[3];
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ u8 mAtType;
    /* 0x40C */ u32 mSwitchNo;
};

namespace daSwAt_prm {
    inline u8 getAtType(daSwAt_c* ac) { return (fopAcM_GetParam(ac) >> 0) & 0xFF; }
    inline u8 getSwitchNo(daSwAt_c* ac) { return (fopAcM_GetParam(ac) >> 8) & 0xFF; }
};

#endif /* D_A_SWATTACK_H */
