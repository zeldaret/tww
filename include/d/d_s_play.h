#ifndef D_S_PLAY
#define D_S_PLAY

#include "f_op/f_op_scene.h"
#include "m_Do/m_Do_hostIO.h"

class dScnPly_ply_c : public scene_class {
public:
    s8 calcPauseTimer();
    bool resetGame();
    void offReset();

    static bool isPause() { return pauseTimer == 0; }
    static void setPauseTimer(s8 time) { pauseTimer = time; }

    static s8 pauseTimer;
    static s8 nextPauseTimer;
};

class dScnPly_reg_childHIO_c {
public:
    virtual ~dScnPly_reg_childHIO_c();

    f32 mFloats[30];
    s16 mShorts[30];
};

class dScnPly_reg_HIO_c : public mDoHIO_entry_c {
public:
    void* field_0x04;
    dScnPly_reg_childHIO_c mChild[22];
};

extern dScnPly_reg_HIO_c g_regHIO;

#endif /* D_S_PLAY */
