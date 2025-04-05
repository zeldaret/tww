#ifndef D_A_HIMO2_H
#define D_A_HIMO2_H

#include "f_op/f_op_actor.h"

struct himo2_s {
    
};

class himo2_class : public fopAc_ac_c {
public:
    BOOL setTargetPos(cXyz*, float*, float*);

public:
    /* Place member variables here */
    // TODO: is this right?
    /* 0x290 */ u8 field_0x290[0x2DC - 0x290];
    /* 0x2DC */ s32 field_0x2DC;
    /* 0x2E0 */ u8 field_0x2E0[0x15F8 - 0x2E0];
    /* 0x15FC */ cXyz field_0x15F8;
};

class himo2HIO_c {
public:
    ~himo2HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_HIMO2_H */
