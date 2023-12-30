#ifndef D_A_DEMO00_H
#define D_A_DEMO00_H

#include "f_op/f_op_actor.h"

class dDemo_actor_c;

class daDemo00_model_c {
public:
    void reset();

public:
    /* Place member variables here */
};

class daDemo00_resID_c {
public:
    void reset();

public:
    /* Place member variables here */
};

class daDemo00_c : public fopAc_ac_c {
public:
    void action(dDemo_actor_c*) {}
    void setAction(int (daDemo00_c::*)(dDemo_actor_c*)) {}

    void setBaseMtx();
    void setShadowSize();
    void createHeap();
    void actStandby(dDemo_actor_c*);
    void actPerformance(dDemo_actor_c*);
    void actLeaving(dDemo_actor_c*);
    inline BOOL create();
    BOOL draw();
    BOOL execute();

public:
    /* Place member variables here */
};

#endif /* D_A_DEMO00_H */
