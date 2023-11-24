#ifndef D_A_ANDSW2_H
#define D_A_ANDSW2_H

#include "f_op/f_op_actor.h"

class daAndsw2_c : public fopAc_ac_c {
public:
    void create() {}
    void draw() {}
    void execute() {}
    void setActio(unsigned char) {}

public:
    /* 0x290 */ u8 mAction;
    /* 0x291 */ u8 m291[0x292 - 0x291];
    /* 0x292 */ s16 mTimer;
    /* 0x294 */ s16 mEventIdx;
    /* 0x296 */ u8 m296[0x298 - 0x296];
};

#endif /* D_A_ANDSW2_H */
