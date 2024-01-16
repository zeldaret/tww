#ifndef D_A_LWOOD_H
#define D_A_LWOOD_H

#include "f_op/f_op_actor.h"

class daLwood_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _draw();
    inline BOOL _execute();
    void getYureScale() const {}
    void getYureTimer() const {}
    void setMoveBGMtx(); // weak but not inlined?
    void set_mtx(); // weak but not inlined?

    void CreateHeap();
    void CreateInit();

public:
    /* Place member variables here */
};

#endif /* D_A_LWOOD_H */
