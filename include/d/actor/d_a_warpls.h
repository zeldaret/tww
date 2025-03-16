#ifndef D_A_WARPLS_H
#define D_A_WARPLS_H

#include "f_op/f_op_actor.h"

class daWarpls_c : public fopAc_ac_c {
public:
    inline bool _draw();
    void set_mtx(); // weak but not inlined?

    bool _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    bool _execute();
    void checkOrder();
    void eventOrder();
    void setStatus();
    void demo();
    void check_warp_link();
    void check_warp_distance();
    void warp_eff_start();

public:
    /* Place member variables here */
};

#endif /* D_A_WARPLS_H */
