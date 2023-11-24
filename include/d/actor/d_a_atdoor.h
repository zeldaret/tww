#ifndef D_A_ATDOOR_H
#define D_A_ATDOOR_H

#include "f_op/f_op_actor.h"

class daAtdoor_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setAction(unsigned char) {}

    void getSwbit();
    void CreateHeap();
    void calcMtx();
    void CreateInit();
    s32 create();

public:
    /* Place member variables here */
};

#endif /* D_A_ATDOOR_H */
