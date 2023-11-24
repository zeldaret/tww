#ifndef D_A_SALVAGE_TBOX_H
#define D_A_SALVAGE_TBOX_H

#include "f_op/f_op_actor.h"

class daSTBox_c : public fopAc_ac_c {
public:
    inline BOOL _draw();

    BOOL _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    BOOL _execute();
    void initWait(int);
    void initWait02(int);
    void initWaitGetItem(int);
    void initWaitDummy(int);
    void initDrop(int);
    void actWait(int);
    void actDrop(int);
    void actWait02(int);
    void actWaitGetItem(int);
    void actWaitDummy(int);

public:
    /* Place member variables here */
};

#endif /* D_A_SALVAGE_TBOX_H */
