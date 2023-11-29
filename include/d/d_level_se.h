#ifndef D_LEVEL_SE_H
#define D_LEVEL_SE_H

#include "f_op/f_op_kankyo.h"
#include "SSystem/SComponent/c_lib.h"

class dLevelSe_c : public kankyo_class {
public:
    /* 0xF8 */ u32 field_0xf8;
    /* 0xFC */ s8 mReverb;
    /* 0xFD */ u8 mFlag;
    /* 0xFE */ u8 field_0xfe;
    /* 0xFF */ u8 field_0xff;

public:
    inline void setReverb(u32 value, s8 reverb) {
        field_0xf8 = value;
        mReverb = reverb;
        cLib_onBit(mFlag, (u8)4);
    }
};

#endif /* D_LEVEL_SE_H */
