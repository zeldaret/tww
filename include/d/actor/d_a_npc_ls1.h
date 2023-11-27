#ifndef D_A_NPC_LS1_H
#define D_A_NPC_LS1_H

#include "f_op/f_op_actor.h"

class J3DMaterial;

class daNpc_Ls1_matAnm_c : public fopAc_ac_c {
public:
    void clrMoveFlag() {}
    void getNowOffsetX() {}
    void getNowOffsetY() {}
    void setMoveFlag() {}

    void calc(J3DMaterial*) const;

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_LS1_H */
