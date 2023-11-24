#ifndef D_A_TAG_SO_H
#define D_A_TAG_SO_H

#include "f_op/f_op_actor.h"

class daTag_So_c : public fopAc_ac_c {
public:
    void getJumpRange() {}
    void getRndNum() {}
    void isMinigame() {}
    void isTag() {}

    void _execute();
    void debugDraw();
    void _draw();
    void getArg();
    void _create();
    void _delete();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_SO_H */
