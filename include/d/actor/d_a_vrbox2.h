#ifndef D_A_VRBOX2_H
#define D_A_VRBOX2_H

#include "f_op/f_op_actor.h"

class vrbox2_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x294 - 0x290];
    /* 0x294 */ J3DModel* mpBackCloud;
    /* 0x298 */ u8 m298[0x29C - 0x298];
    /* 0x29C */ J3DModel* mpKasumiMae;
    /* 0x2A0 */ u8 m2A0[0x2A4 - 0x2A0];
    /* 0x2A4 */ J3DModel* mpUsoUmi;
    /* 0x2A8 */ u8 m2A8[0x2AC - 0x2A8];
};

#endif /* D_A_VRBOX2_H */
