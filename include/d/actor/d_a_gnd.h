#ifndef D_A_GND_H
#define D_A_GND_H

#include "f_op/f_op_actor.h"

class gnd_class : public fopAc_ac_c {
public:
    /* 0x02AC */ u8 m02AC[0x13CF - 0x02AC];
    /* 0x13CF */ fopEn_enemy_c__ParryOpeningType mNextParryOpeningType;
    /* 0x13D0 */ u8 m13D0;
    /* 0x13D1 */ u8 m13D1;
    /* 0x13D2 */ u8 m13D2[0x15E4 - 0x13D2];
};

#endif /* D_A_GND_H */
