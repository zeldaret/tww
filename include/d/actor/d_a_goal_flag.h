#ifndef D_A_GOAL_FLAG_H
#define D_A_GOAL_FLAG_H

#include "f_op/f_op_actor.h"

class daGoal_Flag_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}
    void getRopePos(int, int) {}
    void setAction(int (daGoal_Flag_c::*)()) {}

    void getRacePath(unsigned char);
    void RopeMove();
    void CreateBuoyRaces();
    void goal_check();
    void flag_move();
    void get_cloth_anim_factor(cXyz*, cXyz*, cXyz*, int, int);
    void CreateHeap();
    void getDemoAction(int);
    void RaceStart();
    void TimerExecute();
    void RaceEnd();

public:
    /* Place member variables here */
};

#endif /* D_A_GOAL_FLAG_H */
