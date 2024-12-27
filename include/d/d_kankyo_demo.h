#ifndef D_KANKYO_DEMO_H
#define D_KANKYO_DEMO_H

#include "d/d_kankyo.h"

struct cXyz;

struct DEMO_PLIGHT {
    /* 0x00 */ int field_0x00;
    /* 0x04 */ int field_0x04;
    /* 0x08 */ LIGHT_INFLUENCE mLightInfluence;
};

void dKydm_demo_plight_entry(DEMO_PLIGHT* i_plight, cXyz* i_pos, int param_2, u8 param_3);
void dKydm_demo_plight_delete(DEMO_PLIGHT* i_plight);
void dKydm_demo_plight_execute(DEMO_PLIGHT* i_plight);

#endif /* D_KANKYO_DEMO_H */
