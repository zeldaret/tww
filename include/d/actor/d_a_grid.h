#ifndef D_A_GRID_H
#define D_A_GRID_H

#include "f_op/f_op_actor.h"

class daHo_packet_c {
public:
    void setBackNrm();
    void setNrmMtx(cXyz&);
    void setNrmVtx(cXyz*, int, int);
    void setTopNrmVtx(cXyz*);
    void draw();
};

class daGrid_c : public fopAc_ac_c {
public:
    void force_calc_wind_rel_angle(short) {}

    s32 _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

class daHo_HIO_c {
public:
    virtual ~daHo_HIO_c() {}

    u8 field_0x4[0xa4 - 0x04];
};

#endif /* D_A_GRID_H */
