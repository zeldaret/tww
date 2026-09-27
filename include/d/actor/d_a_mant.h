#ifndef D_A_MANT_H
#define D_A_MANT_H

#include "f_op/f_op_actor.h"

struct mant_j_s {
    
};

class daMant_packet_c {
public:
    void getMtx() {}
    void getMtx2() {}
    void getNrm() {}
    void getPos() {}
    void getTexNo() {}
    void setTevStr(dKy_tevstr_c*) {}
    void setTexNo(unsigned char) {}
    void setarg0(unsigned char) {}

    void draw();
};

class mant_class : public fopAc_ac_c {
public:
    enum CapeType {
        /* 0x0 */ Type_DARKNUT_e = 0x0,
        /* 0x1 */ Type_PHANTOM_GANON_e = 0x1,
    };

public:
    /* 0x0290 */ u8 m0290[0x1BE0 - 0x0290];
    /* 0x1BE0 */ cXyz m1BE0;
    /* 0x1BEC */ cXyz m1BEC;
    /* 0x1BF8 */ f32 m1BF8;
    /* 0x1BFC */ f32 m1BFC;
    /* 0x1C00 */ u8 m1C00[0x1C0E - 0x1C00];
    /* 0x1C0E */ s16 m1C0E;
    /* 0x1C10 */ u8 m1C10[0x2834 - 0x1C10];
    /* 0x2834 */ s8 m2834;
    /* 0x2835 */ s8 m2835[0x2836 - 0x2835];
    /* 0x2836 */ s16 m2836;
    /* 0x2838 */ u8 m2838[0x283C - 0x2838];
};

#endif /* D_A_MANT_H */
