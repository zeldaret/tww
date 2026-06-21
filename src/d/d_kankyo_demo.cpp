/**
 * d_kankyo_demo.cpp
 *
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_kankyo.h"
#include "d/d_kankyo_demo.h"

/* 8009BE64-8009BF6C       .text dKydm_demo_plight_entry__FP11DEMO_PLIGHTP4cXyziUc */
void dKydm_demo_plight_entry(DEMO_PLIGHT* i_plight, cXyz* i_pos, int param_2, u8 param_3) {
    if (param_2 >= 0) {
        i_plight->mLightInfluence.mPos = *i_pos;
        i_plight->field_0x04 = param_2 + param_3 * 100;

        if (i_plight->field_0x04 < 100) {
            // idk if this is fake but it's needed to match...
            switch (i_plight->field_0x04) {
            case 0:
                break;
            }

            i_plight->mLightInfluence.mColor.r = 255;
            i_plight->mLightInfluence.mColor.g = 255;
            i_plight->mLightInfluence.mColor.b = 128;
            i_plight->mLightInfluence.mPower = 500.0f;
            i_plight->mLightInfluence.mFluctuation = 255.0f;
            dKy_plight_set(&i_plight->mLightInfluence);
        } else {
            if (i_plight->field_0x04 != 103) {
                i_plight->mLightInfluence.mColor.r = 255;
                i_plight->mLightInfluence.mColor.g = 255;
                i_plight->mLightInfluence.mColor.b = 120;
                i_plight->mLightInfluence.mPower = 437.0f;
                i_plight->mLightInfluence.mFluctuation = 55.0f;
            } else {
                i_plight->mLightInfluence.mColor.r = 255;
                i_plight->mLightInfluence.mColor.g = 255;
                i_plight->mLightInfluence.mColor.b = 120;
                i_plight->mLightInfluence.mPower = 532.0f;
                i_plight->mLightInfluence.mFluctuation = 71.0f;
            }

            dKy_efplight_set(&i_plight->mLightInfluence);
        }

        i_plight->field_0x00 = 0;
        i_plight->field_0x04 = param_2;
    }
}

/* 8009BF6C-8009BFB0       .text dKydm_demo_plight_delete__FP11DEMO_PLIGHT */
void dKydm_demo_plight_delete(DEMO_PLIGHT* i_plight) {
    if (i_plight != NULL) {
        if (i_plight->field_0x04 < 100) {
            dKy_plight_cut(&i_plight->mLightInfluence);
        } else {
            dKy_efplight_cut(&i_plight->mLightInfluence);
        }
    }
}

/* 8009BFB0-8009BFD4       .text dKydm_demo_plight_execute__FP11DEMO_PLIGHTP4cXyz */
void dKydm_demo_plight_execute(DEMO_PLIGHT* i_plight, cXyz* i_pos) {
    if (i_plight != NULL) {
        i_plight->mLightInfluence.mPos = *i_pos;
    }
}
