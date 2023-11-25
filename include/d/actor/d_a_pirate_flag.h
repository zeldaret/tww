#ifndef D_A_PIRATE_FLAG_H
#define D_A_PIRATE_FLAG_H

#include "f_op/f_op_actor.h"

class pirate_flag_class : public fopAc_ac_c {
public:
    /* Place member variables here */
};

class daPirate_Flag_packet_c {
public:
    ~daPirate_Flag_packet_c();
    void setCorrectNrmAngle(short, float);
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
    BOOL draw();
};

class daPirate_Flag_HIO_c {
    ~daPirate_Flag_HIO_c();
};
#endif /* D_A_PIRATE_FLAG_H */
