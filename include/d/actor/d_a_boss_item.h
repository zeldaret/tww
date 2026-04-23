#ifndef D_A_BOSS_ITEM_H
#define D_A_BOSS_ITEM_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

struct bossitem_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ u8 m290[0x298 - 0x290];
};  // Size: 0x298

namespace daBossItem_prm {
    inline int getStage(bossitem_class* actor) { return fopAcM_GetParam(actor) & 0xFF; }
}

#endif /* D_A_BOSS_ITEM_H */
