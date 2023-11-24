#ifndef D_A_FAN_H
#define D_A_FAN_H

#include "f_op/f_op_actor.h"

class daFan_c : public fopAc_ac_c {
public:
    void Delete();
    void CreateHeap();
    void Create();
    void _create();
    void set_mtx();
    void set_wind_length(float);
    void set_cps(float);
    void Execute(float(**)[3][4]);
    void Draw();

public:
    /* Place member variables here */
};

#endif /* D_A_FAN_H */
