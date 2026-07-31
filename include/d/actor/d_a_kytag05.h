#ifndef D_A_KYTAG05_H
#define D_A_KYTAG05_H

#include "f_op/f_op_actor.h"

struct kytag05_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ u8 mIndex;
    /* 0x294 */ int mTimer;
    /* 0x298 */ int mUnknownParam;
}; /* size = 0x29C */

#endif /* D_A_KYTAG05_H */
