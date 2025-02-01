#ifndef D_A_LEAFLIFT_H
#define D_A_LEAFLIFT_H

#include "f_op/f_op_actor.h"

class daLlift_c : public fopAc_ac_c {
public:
    bool _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void setMoveBGMtx();
    bool _execute();
    void emitterCtrl();
    void MoveDownLift();
    bool _draw();

    void checkEndDownLift();
    void MoveUpLift();

    static const f32 m_height;
    static const f32 m_max_speed;
    static const f32 m_min_speed;

public:
    /* Place member variables here */
};

#endif /* D_A_LEAFLIFT_H */
