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
    void force_calc_wind_rel_angle(short param_1) { m2216 = param_1; m2218 = 1; }

    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

public:
    /* 0x0290 */ u8 m0290[0x2200 - 0x290];
    /* 0x2200 */ f32 m2200;
    /* 0x2204 */ u8 m2219[0x2216 - 0x2204];
    /* 0x2216 */ s16 m2216;
    /* 0x2218 */ u8 m2218;
};

class daHo_HIO_c {
public:
    virtual ~daHo_HIO_c() {}

    u8 field_0x4[0xa4 - 0x04];
};

#endif /* D_A_GRID_H */
