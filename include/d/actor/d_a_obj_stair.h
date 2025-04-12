#ifndef D_A_OBJ_STAIR_H
#define D_A_OBJ_STAIR_H

#include "d/d_bg_s_movebg_actor.h"

class daObj_Stair_c : public dBgS_MoveBgActor {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void set_mtx() {}

    virtual BOOL CreateHeap();
    virtual BOOL Create();
    virtual BOOL Execute(Mtx**);
    virtual BOOL Draw();
    virtual BOOL Delete();

public:
    /* Place member variables here */
};

class daobj_stairHIO_c {
public:
    daobj_stairHIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_STAIR_H */
