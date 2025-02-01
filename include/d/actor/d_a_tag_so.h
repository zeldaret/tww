#ifndef D_A_TAG_SO_H
#define D_A_TAG_SO_H

#include "f_op/f_op_actor.h"

class daTag_So_c : public fopAc_ac_c {
public:
    void getJumpRange() {}
    void getRndNum() {}
    void isMinigame() {}
    void isTag() {}

    bool _execute();
    void debugDraw();
    bool _draw();
    void getArg();
    s32 _create();
    bool _delete();

public:
    /* Place member variables here */
};

class daTag_So_HIO_c {
public:
    daTag_So_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_SO_H */
