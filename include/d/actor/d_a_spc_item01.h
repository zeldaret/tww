#ifndef D_A_SPC_ITEM01_H
#define D_A_SPC_ITEM01_H

#include "f_op/f_op_actor.h"

class daSpcItem01_c : public fopAc_ac_c {
public:
    void set_mtx();
    void _delete();
    void _create();
    void CreateInit();
    void _execute();
    void set_effect();
    void scale_anim();
    void anim_play();
    void move();
    void rotate_item();
    void setCol();
    void _draw();
    void setTevStr();

public:
    /* Place member variables here */
};

#endif /* D_A_SPC_ITEM01_H */
