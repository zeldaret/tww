#ifndef D_A_TAG_BA1_H
#define D_A_TAG_BA1_H

#include "f_op/f_op_actor.h"

class daTag_Ba1_c : public fopAc_ac_c {
public:
    s16 XyCheck_cB(int);
    s16 XyEvent_cB(int);
    bool createInit();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    /* 0x290 */ s16 eventIds[1];
    /* 0x292 */ s16 eventIdx;
};

#endif /* D_A_TAG_BA1_H */
