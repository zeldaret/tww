#ifndef D_S_PLAY
#define D_S_PLAY

#include "f_op/f_op_scene.h"

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

#endif /* D_S_PLAY */
