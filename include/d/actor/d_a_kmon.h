#ifndef D_A_KMON_H
#define D_A_KMON_H

#include "f_op/f_op_actor.h"

class daKmon_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void set_mtx();
    void CreateHeap();
    void CreateInit();
    void checkTalk();

public:
    /* Place member variables here */
};

#endif /* D_A_KMON_H */
