#ifndef D_A_HMLIF_H
#define D_A_HMLIF_H

#include "f_op/f_op_actor.h"

class daHmlif_c : public fopAc_ac_c {
public:
    BOOL Delete();
    void daHmlifDelete();
    void CreateHeap();
    s32 Create();
    cPhs_State daHmlifCreate();
    void set_mtx();
    void Execute(float(**)[3][4]);
    void move();
    void set_se();
    void anim_play();
    void check_col();
    void lift_smooth_move();
    void lift_normal_move();
    void set_next_pnt();
    void setNextPath();
    void chkSwitchPathType();
    BOOL Draw();

public:
    /* Place member variables here */
};

#endif /* D_A_HMLIF_H */
