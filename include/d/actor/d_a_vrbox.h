#ifndef D_A_VRBOX_H
#define D_A_VRBOX_H

#include "f_op/f_op_actor_mng.h"

class vrbox_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x294 - 0x290];
    /* 0x294 */ J3DModel* mpModel;
    /* 0x298 */ u8 m298[0x29C - 0x298];
    /* 0x29C */ u8 m29C;
    /* 0x29D */ u8 m29D[0x2A0 - 0x29D];
};

#endif /* D_A_VRBOX_H */
