#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "c/c_dylink.h"
#include "f_op/f_op_actor.h"

struct daFallRockTag_Data_c {
    /* 0x00 */ f32 mRange;
    /* 0x04 */ f32 mScaleMin;
    /* 0x08 */ f32 mScaleMax;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 mTimerOffset;
    /* 0x18 */ s16 mRockNumPerSec;
};  // Size: 0x1C

class daFallRockTag_c : public fopAc_ac_c {
public:
    ~daFallRockTag_c() {
        cDyl_Unlink(fpcNm_FallRock_e);
    }

    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    inline daFallRockTag_Data_c* getData();

    void createRock(cXyz*, cXyz*, csXyz*, int, u32);

    static f32 m_div_num;
    static daFallRockTag_Data_c m_data;

public:
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ int field_0x298;
    /* 0x29C */ u8 field_0x29c[0x29E - 0x29C];
    /* 0x29E */ u8 mSchBit;
    /* 0x29F */ u8 field_0x29f[0x2A0 - 0x29F];
};  // Size: 0x2A0

#endif /* D_A_FALLROCK_TAG_H */
