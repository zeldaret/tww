#ifndef D_A_SWITEM_H
#define D_A_SWITEM_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor_mng.h"

class daSwItem_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateInit();
    s32 _create();
    bool _execute();
    BOOL isRupeeInAllCreateTable(int);
    bool _draw();

public:
    /* 0x290 */ u8 m290[0x29C - 0x290];
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ u8 mAtTypeTrigger;
    /* 0x409 */ bool mSpawnedItem;
    /* 0x40A */ u8 m40A[0x40C - 0x40A];
};

namespace daSwItem_prm {
    inline u32 getAtType(daSwItem_c* item) { return (fopAcM_GetParam(item) >> 0x00) & 0xFF; }
    inline u32 getItemTbl(daSwItem_c* item) { return (fopAcM_GetParam(item) >> 0x08) & 0x3F; }
    inline u32 getItemBitNo(daSwItem_c* item) { return (fopAcM_GetParam(item) >> 0x0E) & 0x7F; }
}

#endif /* D_A_SWITEM_H */
