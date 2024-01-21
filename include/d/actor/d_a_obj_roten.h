#ifndef D_A_OBJ_ROTEN_H
#define D_A_OBJ_ROTEN_H

#include "f_op/f_op_actor.h"

class daObj_Roten_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();

    void set_mtx();
    void CreateHeap();
    void CreateInit();
    
    static void getCreateCount();

public:
    /* Place member variables here */
};

class daObj_Roten_HIO_c {
public:
    daObj_Roten_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_ROTEN_H */
