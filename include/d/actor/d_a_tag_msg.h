#ifndef D_A_TAG_MSG_H
#define D_A_TAG_MSG_H

#include "f_op/f_op_actor.h"

class daTag_Msg_c : public fopAc_ac_c {
public:
    void create() {}
    void draw() {}
    void execute() {}
    void setActio(unsigned char) {}

public:
    /* 0x290 */ u8 m290[0x294 - 0x290];
};

#endif /* D_A_TAG_MSG_H */
