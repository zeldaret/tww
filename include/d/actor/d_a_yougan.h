#ifndef D_A_YOUGAN_H
#define D_A_YOUGAN_H

#include "f_op/f_op_actor.h"

class daYougan_c : public fopAc_ac_c {
public:
    BOOL _daYougan_draw();
    BOOL _daYougan_execute();
    BOOL _daYougan_isdelete();
    BOOL _daYougan_delete();
    BOOL useHeapInit();
    cPhs_State _daYougan_create();

public:
    /* Place member variables here */
};

class daYOUGAN_HIO_c {
public:
    daYOUGAN_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_YOUGAN_H */
