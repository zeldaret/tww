#ifndef D_A_HMLIF_H
#define D_A_HMLIF_H

#include "d/d_bg_s_movebg_actor.h"

class daHmlif_c : public dBgS_MoveBgActor {
public:
    virtual BOOL Delete();
    BOOL daHmlifDelete();
    virtual BOOL CreateHeap();
    virtual BOOL Create();
    cPhs_State daHmlifCreate();
    void set_mtx();
    virtual BOOL Execute(Mtx**);
    void move();
    void set_se();
    void anim_play();
    void check_col();
    void lift_smooth_move();
    void lift_normal_move();
    void set_next_pnt();
    void setNextPath();
    void chkSwitchPathType();
    virtual BOOL Draw();

public:
    /* Place member variables here */
};

#endif /* D_A_HMLIF_H */
