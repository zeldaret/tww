#ifndef D_A_GND_H
#define D_A_GND_H

#include "f_op/f_op_actor.h"

struct gnd_ke_s {
    
};

class gnd_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ u8 m02AC[0x13CF - 0x02AC];
    /* 0x13CF */ u8 mNextParryOpeningType;
    /* 0x13D0 */ u8 m13D0;
    /* 0x13D1 */ u8 m13D1;
    /* 0x13D2 */ u8 m13D2[0x15E4 - 0x13D2];
};

class daGnd_HIO_c {
public:
    daGnd_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_GND_H */
