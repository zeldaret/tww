#ifndef D_A_FALLROCK_H
#define D_A_FALLROCK_H

#include "f_op/f_op_actor.h"

class daFallRock_c : public fopAc_ac_c {
public:
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

    void CreateHeap();
    void set_mtx();
    void setParticle(int, cXyz*);

public:
    /* Place member variables here */
};

#endif /* D_A_FALLROCK_H */
