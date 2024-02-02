#ifndef D_A_SPOTBOX_H
#define D_A_SPOTBOX_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class daSpotbox_c : public fopAc_ac_c {
public:
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();
    inline u32 getType() { return fopAcM_GetParam(this) & 1; }

public:
    /* 0x290 */ Mtx mMtx;
}; // Size: 0x2C0

#endif /* D_A_SPOTBOX_H */
