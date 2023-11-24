#ifndef D_A_GRID_H
#define D_A_GRID_H

#include "f_op/f_op_actor.h"

class daGrid_c : public fopAc_ac_c {
public:
    void force_calc_wind_rel_angle(short) {}

    void _create();
    void _delete();
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_GRID_H */
