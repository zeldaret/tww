#ifndef D_ENVSE_H
#define D_ENVSE_H

#include "f_op/f_op_kankyo.h"

class dEnvSe_c : public kankyo_class {
public:
    BOOL execute();

    /* 0xF8 */ u32 field_0xf8;
    /* 0xFC */ u32 field_0xfc;
};

#endif /* D_ENVSE_H */
