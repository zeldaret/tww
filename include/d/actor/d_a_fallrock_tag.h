#ifndef D_A_FALLROCK_TAG_H
#define D_A_FALLROCK_TAG_H

#include "c/c_dylink.h"
#include "f_op/f_op_actor.h"

struct daFallRockTag_data {
    /* 0x00 */ f32 mPosRange;
    /* 0x04 */ f32 mScaleMin;
    /* 0x08 */ f32 mScaleMax;
    /* 0x0C */ f32 mSpeedY;
    /* 0x10 */ f32 mGravity;
    /* 0x14 */ s16 mAngle;
    /* 0x16 */ s16 mTimerStart;
    /* 0x18 */ s16 mSpawnNum;
};

class daFallRockTag_c : public fopAc_ac_c {
public:
    ~daFallRockTag_c() { cDyl_Unlink(fpcNm_FallRock_e); }

    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    daFallRockTag_data* getData();

    void createRock(cXyz*, cXyz*, csXyz*, int, unsigned long);

    static f32 m_div_num;
    static daFallRockTag_data m_data;

public:
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ int field_0x298;
    /* 0x29C */ u8 field_0x29C[0x29E - 0x29C];
    /* 0x29E */ u8 mSchBit;
};

#endif /* D_A_FALLROCK_TAG_H */
