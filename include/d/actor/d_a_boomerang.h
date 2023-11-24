#ifndef D_A_BOOMERANG_H
#define D_A_BOOMERANG_H

#include "f_op/f_op_actor.h"

class daBoomerang_blur_c : public fopAc_ac_c {
public:
    void initBlur(float(*)[4], short);
    void copyBlur(float(*)[4], short);
    void draw();

public:
    /* Place member variables here */
};

#endif /* D_A_BOOMERANG_H */
