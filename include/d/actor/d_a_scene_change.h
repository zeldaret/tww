#ifndef D_A_SCENE_CHANGE_H
#define D_A_SCENE_CHANGE_H

#include "f_op/f_op_actor.h"

class d_a_scene_change_c : public fopAc_ac_c {
public:
    /* 0x290 */ Mtx mTransformMtx;
};

class daSceneChgHIO_c {
public:
    daSceneChgHIO_c();
    virtual ~daSceneChgHIO_c() {
        mNo = -1;
    }

    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 m0005;
    /* 0x08 */ f32 m0008;
};

#endif /* D_A_SCENE_CHANGE_H */
