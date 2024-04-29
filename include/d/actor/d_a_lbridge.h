#ifndef D_A_LBRIDGE_H
#define D_A_LBRIDGE_H

#include "f_op/f_op_actor.h"

class daLbridge_c : public fopAc_ac_c {
public:
    inline BOOL _delete();

    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    void setMoveBGMtx();
    BOOL _execute();
    void sw_check();
    void demo();
    void appear_bridge();
    void disappear_bridge();
    void set_on_se();
    void set_off_se();
    BOOL _draw();

    static const char m_arcname[];

public:
    /* Place member variables here */
};

#endif /* D_A_LBRIDGE_H */
