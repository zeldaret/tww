#ifndef D_A_SPC_ITEM01_H
#define D_A_SPC_ITEM01_H

#include "f_op/f_op_actor.h"

class daSpcItem01_c : public fopAc_ac_c {
public:
    void set_mtx();
    BOOL _delete();
    s32 _create();
    void CreateInit();
    BOOL _execute();
    void set_effect();
    void scale_anim();
    void anim_play();
    void move();
    void rotate_item();
    void setCol();
    BOOL _draw();
    void setTevStr();

public:
    /* Place member variables here */
};

#endif /* D_A_SPC_ITEM01_H */
