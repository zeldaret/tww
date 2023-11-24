#ifndef D_A_DEMO_KMM_H
#define D_A_DEMO_KMM_H

#include "f_op/f_op_actor.h"

class daDemo_Kmm_c : public fopAc_ac_c {
public:
    inline BOOL draw();
    inline BOOL execute();
    void setAction(unsigned char) {}

    void CreateHeap();
    void calcMtx();
    void setAnime(int, int, float, float);
    void CreateInit();
    s32 create();

public:
    /* Place member variables here */
};

#endif /* D_A_DEMO_KMM_H */
