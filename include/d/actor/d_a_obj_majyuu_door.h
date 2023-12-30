#ifndef D_A_OBJ_MAJYUU_DOOR_H
#define D_A_OBJ_MAJYUU_DOOR_H

#include "f_op/f_op_actor.h"

class daObj_MjDoor_c : public fopAc_ac_c {
public:
    void modeProcCall() {}

    void set_mtx();
    void _createHeap();
    void getArg();
    void CreateInit();
    s32 _create();
    BOOL _delete();
    void setCollision();
    void modeWaitInit();
    void modeWait();
    void smoke_set();
    void modeDeleteInit();
    void modeDelete();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

class daObj_MjDoorHIO_c {
public:
    daObj_MjDoorHIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_MAJYUU_DOOR_H */
