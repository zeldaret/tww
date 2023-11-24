#ifndef D_A_GHOSTSHIP_H
#define D_A_GHOSTSHIP_H

#include "f_op/f_op_actor.h"

class daGhostship_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}
    void checkInShip() {}
    void getAlpha() {}
    void setMtx() {}

    void _createHeap();
    void pathMove();
    void modeWaitInit();
    void modeWait();
    void modeRealize();
    void _pathMove(cXyz*, cXyz*, cXyz*);
    void modePathMoveInit();
    void modePathMove();
    void modeProcCall();
    void createInit();
    void getArg();

public:
    /* Place member variables here */
};

#endif /* D_A_GHOSTSHIP_H */
