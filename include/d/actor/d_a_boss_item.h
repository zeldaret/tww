#ifndef D_A_BOSS_ITEM_H
#define D_A_BOSS_ITEM_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

class bossitem_class : public fopAc_ac_c {
    /* 0x290 */ u8 m290[0x298 - 0x290];
};

namespace daBossItem_prm {
    inline int getStage(bossitem_class* actor) { return fopAcM_GetParam(actor) & 0xFF; }
}

#endif /* D_A_BOSS_ITEM_H */
