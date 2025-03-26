#ifndef D_A_TAG_KK1_H
#define D_A_TAG_KK1_H

#include "f_op/f_op_actor.h"

class daTag_Kk1_c : public fopAc_ac_c {
public:
    void createInit();
    bool _draw();
    bool _execute();
    bool _delete();
    cPhs_State _create();

public:
    /* Place member variables here */
};

class daTag_Kk1_HIO_c {
public:
    daTag_Kk1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_KK1_H */
