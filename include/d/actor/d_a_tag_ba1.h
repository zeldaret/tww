#ifndef D_A_TAG_BA1_H
#define D_A_TAG_BA1_H

#include "f_op/f_op_actor.h"

class daTag_Ba1_c : public fopAc_ac_c {
public:
    void XyCheck_cB(int);
    void XyEvent_cB(int);
    void createInit();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    /* Place member variables here */
};

class daTag_Ba1_HIO_c {
public:
    daTag_Ba1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_BA1_H */
