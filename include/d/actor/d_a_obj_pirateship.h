#ifndef D_A_OBJ_PIRATESHIP_H
#define D_A_OBJ_PIRATESHIP_H

#include "f_op/f_op_actor_mng.h"

namespace daObjPirateship {
    class Act_c : public fopAc_ac_c {
    public:
        /* 0x290 */ u8 temp[0x2CC - 0x290];
        /* 0x2CC */ u8 unk2CC;
        /* 0x2D0 */ J3DModel* mpModel;
    };
    
    static f32 getShipOffsetY(s16*, s16*, f32);
}

#endif /* D_A_OBJ_PIRATESHIP_H */
