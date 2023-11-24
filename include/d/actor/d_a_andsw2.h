#ifndef D_A_ANDSW2_H
#define D_A_ANDSW2_H

#include "f_op/f_op_actor.h"

struct daAndsw2_c : public fopAc_ac_c {
public:
    void setActio(u8 action) { mAction = action; }

    u8 getEventNo();
    u8 getSwbit();
    u8 getSwbit2();
    u8 getType();
    u8 getTimer();
    u8 getNum();
    u8 getTopSw();
    BOOL chkAllSw2();
    
    inline BOOL execute();
    inline s32 create();
    inline BOOL draw();

public:
    /* 0x290 */ u8 mAction;
    /* 0x292 */ s16 mTimer;
    /* 0x294 */ s16 mEventIdx;
};

#endif /* D_A_ANDSW2_H */
