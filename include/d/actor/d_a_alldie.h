#ifndef D_A_ALLDIE_H
#define D_A_ALLDIE_H

#include "f_op/f_op_actor.h"

class daAlldie_c : public fopAc_ac_c {
public:
    inline s32 create();
    inline BOOL draw();
    void setActio(u8 action) { mAction = action; }

    u8 getSwbit();
    BOOL actionWait();
    BOOL actionCheck();
    BOOL actionTimer();
    BOOL execute();
public:
    /* 0x290 */ u8 mAction;
    /* 0x292 */ s16 mTimer;
};

#endif /* D_A_ALLDIE_H */
