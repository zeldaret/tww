#ifndef D_A_OBJ_DOGUU_H
#define D_A_OBJ_DOGUU_H

#include "f_op/f_op_actor.h"

class daObjDoguu_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();
    void setEffectMtx(const cXyz*, float); // weak but not inlined?

    void setPointLight();
    void CreateHeap();
    void CreateInit();
    void set_mtx();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setGoal(int);
    void setPlayerAngle(int);
    void setQuake(int);
    void setJDemo(int);
    void privateCut();
    void getFinishEventCount();
    void setFinishMyEvent();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_DOGUU_H */
