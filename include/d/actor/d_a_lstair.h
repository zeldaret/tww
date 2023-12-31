#ifndef D_A_LSTAIR_H
#define D_A_LSTAIR_H

#include "f_op/f_op_actor.h"

class daLStair_c : public fopAc_ac_c {
public:
    inline BOOL _draw();

    BOOL _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void setMoveBGMtx();
    BOOL _execute();
    void demoMove();
    void checkAppear();
    void moveBG();
    void appear_stair();
    void disappear_stair();
    void set_on_se();
    void set_off_se();

public:
    /* Place member variables here */
};

#endif /* D_A_LSTAIR_H */
