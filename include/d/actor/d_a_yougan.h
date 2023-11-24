#ifndef D_A_YOUGAN_H
#define D_A_YOUGAN_H

#include "f_op/f_op_actor.h"

class daYougan_c : public fopAc_ac_c {
public:
    void _daYougan_draw();
    void _daYougan_execute();
    void _daYougan_isdelete();
    void _daYougan_delete();
    void useHeapInit();
    void _daYougan_create();

public:
    /* Place member variables here */
};

#endif /* D_A_YOUGAN_H */
