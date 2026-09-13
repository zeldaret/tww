#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "f_op/f_op_actor.h"

struct daFallRockTag_data {
    /* 0x00 */ f32 m00;
    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ s16 m14;
    /* 0x16 */ s16 m16;
    /* 0x18 */ s16 m18;
    /* 0x1A */ s16 m1A;
};

class daFallRockTag_c : public fopAc_ac_c {
public:
    inline ~daFallRockTag_c() {
        cDyl_Unlink(fpcNm_FallRock_e);
    }
    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    daFallRockTag_data* getData();

    void createRock(cXyz*, cXyz*, csXyz*, int, u32);

    static f32 m_div_num;
    static daFallRockTag_data m_data;

public:
    /* 0x290 */ u8 m290[0x298 - 0x290];
    /* 0x298 */ int m298;
    /* 0x29C */ s16 m29C;
    /* 0x29E */ u8 m29E;
    /* 0x29F */ u8 m29F;
};

STATIC_ASSERT(sizeof(daFallRockTag_c) == 0x2A0);

#endif /* D_A_FALLROCK_TAG_H */
