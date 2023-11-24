#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "f_op/f_op_actor.h"

class daFallRockTag_c : public fopAc_ac_c {
public:
    void create() {}
    void draw() {}
    void execute() {}
    void getData() {}

    void createRock(cXyz*, cXyz*, csXyz*, int, unsigned long);

public:
    /* Place member variables here */
};

#endif /* D_A_FALLROCK_TAG_H */
