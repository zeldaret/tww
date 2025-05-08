#ifndef D_A_GOAL_FLAG_H
#define D_A_GOAL_FLAG_H

#include "f_op/f_op_actor.h"

class daGoal_Flag_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
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
    void changeCurrentPos() {}
    void getDPos() {}
    void getMtx() {}
    void getNrm() {}
    void getOffsetVec() {}
    void getPos() {}
    void getTexObjP() {}
    void getToonTexObjP() {}
    void setTevStr(dKy_tevstr_c*) {}

    void setTexObj(unsigned char);
    void setToonTexObj();
    void draw();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
};

#endif /* D_A_GOAL_FLAG_H */
