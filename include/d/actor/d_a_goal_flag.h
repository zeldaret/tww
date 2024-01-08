#ifndef D_A_GOAL_FLAG_H
#define D_A_GOAL_FLAG_H

#include "f_op/f_op_actor.h"

class daGoal_Flag_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();
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

class daGFlag_packet_c {
public:
    void setTexObj(unsigned char);
    void setToonTexObj();
    void draw();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
};

#endif /* D_A_GOAL_FLAG_H */
