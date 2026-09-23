#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_operate_wind.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_kankyo_wether.h"
#include "d/d_s_play.h"
#include "d/d_meter.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_controller_pad.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/JKernel/JKRExpHeap.h"

/* 8021E58C-8021E5F8       .text __ct__9dOw_HIO_cFv */
dOw_HIO_c::dOw_HIO_c() {                           
    field_0x08 = 30;
    field_0x0a = 95;
    field_0x0c = 155;
    field_0x0e = 16;
    field_0x18 = 100;
    field_0x10 = 120;
    field_0x12 = 50;
    field_0x04 = 7.0f;
    field_0x14 = 20;
    field_0x16 = 40;
}

dOw_HIO_c g_owHIO;

/* 8021E5F8-8021E6A4       .text draw__15dDlst_Ow_main_cFv */
void dDlst_Ow_main_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();

    for (int i = 0; i < mLineMax; i++) {
        J2DDrawLine(mX1[i], mY1[i], mX2[i], mY2[i], color, 6);
    }

    scrn->draw(0.0f, 0.0f, graf);
}

/* 8021E6A4-8021E708       .text draw__15dDlst_Ow_mask_cFv */
void dDlst_Ow_mask_c::draw() {
    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    scrn->draw(0.0f, 0.0f, graf);
}

/* 8021E708-8021E7E4       .text dOw_angleRegular__15dOperate_wind_cFf */
int dOperate_wind_c::dOw_angleRegular(f32 angle) {
    if (angle < -247.5f)
        return 90;
    else if (angle < -202.5f)
        return 135;
    else if (angle < -157.5f)
        return 180;
    else if (angle < -112.5f)
        return 225;
    else if (angle < -67.5f)
        return 270;
    else if (angle < -22.5f)
        return 315;
    else if (angle < 22.5f)
        return 0;
    else if (angle < 67.5f)
        return 45;
    else if (angle < 112.5f)
        return 90;
    else if (angle < 157.5f)
        return 135;
    else if (angle < 202.5f)
        return 180;
    // !@bug missing end return
}

/* 8021E7E4-8021E974       .text dOw_stickControl__15dOperate_wind_cFis */
int dOperate_wind_c::dOw_stickControl(int ret, s16 ang) {
    int angi = abs(ang);
    if (ret == 0) {
        if (angi > 0x7000) {
            return 1;
        } else if (ang >= 0x5000) {
            return 2;
        } else if (ang <= -0x5000) {
            return 8;
        } else if (ang >= 0x3000) {
            return 3;
        } else if (ang <= -0x3000) {
            return 7;
        } else if (ang >= 0x1000) {
            return 4;
        } else if (ang <= -0x1000) {
            return 6;
        } else {
            return 5;
        }
    } else {
        s16 r0 = 0x80;
        if (angi > (s16)(0x8000 - r0)) {
            return 1;
        }
        s16 r6 = 0x800;
        if (ang >= (s16)(0x6000 - r6) && ang <= (s16)(0x6000 + r6)) {
            return 2;
        }
        if (ang <= (s16)(-0x6000 + r6) && ang >= (s16)(-0x6000 - r6)) {
            return 8;
        }
        if (ang >= (s16)(0x4000 - r0) && ang <= (s16)(0x4000 + r0)) {
            return 3;
        }
        if (ang <= (s16)(-0x4000 + r0) && ang >= (s16)(-0x4000 - r0)) {
            return 7;
        }
        if (ang >= (s16)(0x2000 - r6) && ang <= (s16)(0x2000 + r6)) {
            return 4;
        }
        if (ang <= (s16)(-0x2000 + r6) && ang >= (s16)(-0x2000 - r6)) {
            return 6;
        }
        if (angi < r0) {
            return 5;
        }
    }

    return ret;
}

/* 8021E974-8021ED4C       .text screenSet__15dOperate_wind_cFv */
void dOperate_wind_c::screenSet() {
    fopMsgM_setPaneData(&field_0x0c, scrn1, 'wdn');
    fopMsgM_setPaneData(&field_0x44, scrn1, 'wds');
    fopMsgM_setPaneData(&field_0x7c, scrn1, 'wdw');
    fopMsgM_setPaneData(&field_0xb4, scrn1, 'wde');
    fopMsgM_setPaneData(&field_0x54c, scrn1, 'win');
    fopMsgM_setPaneData(&field_0xec, scrn1, 'wib');

    fopMsgM_setPaneData(&field_0x124[0], scrn1, 'wi21');
    fopMsgM_setPaneData(&field_0x124[1], scrn1, 'wi22');

    fopMsgM_setPaneData(&field_0x194, scrn1, 'wi2b');

    fopMsgM_setPaneData(&field_0x1cc[0], scrn1, 'n2');
    fopMsgM_setPaneData(&field_0x1cc[1], scrn1, 's2');
    fopMsgM_setPaneData(&field_0x1cc[2], scrn1, 'w2');
    fopMsgM_setPaneData(&field_0x1cc[3], scrn1, 'e2');

    #if VERSION >= VERSION_USA
    field_0x1cc[0].pane->hide();
    field_0x1cc[1].pane->hide();
    field_0x1cc[2].pane->hide();
    field_0x1cc[3].pane->hide();
    #endif

    fopMsgM_setPaneData(&field_0x2ac[0], scrn1, 'str1');
    fopMsgM_setPaneData(&field_0x2ac[1], scrn1, 'str2');
    fopMsgM_setPaneData(&field_0x2ac[2], scrn1, 'str3');
    fopMsgM_setPaneData(&field_0x2ac[3], scrn1, 'str4');
    fopMsgM_setPaneData(&field_0x2ac[4], scrn1, 'str5');
    fopMsgM_setPaneData(&field_0x2ac[5], scrn1, 'str6');
    fopMsgM_setPaneData(&field_0x2ac[6], scrn1, 'str7');
    fopMsgM_setPaneData(&field_0x2ac[7], scrn1, 'str8');

    fopMsgM_setPaneData(&field_0x46c[0], scrn1, 'ci04');
    fopMsgM_setPaneData(&field_0x46c[1], scrn1, 'ci05');
    fopMsgM_setPaneData(&field_0x46c[2], scrn1, 'ci06');
    fopMsgM_setPaneData(&field_0x46c[3], scrn1, 'ci07');

    fopMsgM_setPaneData(&field_0x554, scrn2, 'mask');
    field_0x554.mInitAlpha = 130;

    #if VERSION == VERSION_PAL
    if (dComIfGs_getPalLanguage() == 1) {
        JKRReadTypeResource(shipfontTimg, 0xC00, 'TIMG', "shipfont_o_big.bti", dComIfGp_getWindResArchive());
        ((J2DPicture*)field_0xb4.pane)->changeTexture(shipfontTimg, 0);
    } else if (dComIfGs_getPalLanguage() == 2 || dComIfGs_getPalLanguage() == 3 || dComIfGs_getPalLanguage() == 4) {
        JKRReadTypeResource(shipfontTimg, 0xC00, 'TIMG', "shipfont_o_big.bti", dComIfGp_getWindResArchive());
        ((J2DPicture*)field_0x7c.pane)->changeTexture(shipfontTimg, 0);
    }
    #endif

    ((J2DPicture*)field_0x54c.pane)->getCornerColor(field_0x568);
    ((J2DPicture*)field_0x124[0].pane)->getCornerColor(field_0x578);
    ((J2DPicture*)field_0x554.pane)->getCornerColor(field_0x588);
}

/* 8021ED4C-8021EE9C       .text alphaSet__15dOperate_wind_cFf */
void dOperate_wind_c::alphaSet(f32 i_alpha) {
    fopMsgM_setNowAlpha(&field_0x0c, i_alpha);
    fopMsgM_setNowAlpha(&field_0x44, i_alpha);
    fopMsgM_setNowAlpha(&field_0x7c, i_alpha);
    fopMsgM_setNowAlpha(&field_0xb4, i_alpha);
    fopMsgM_setNowAlpha(&field_0x54c, i_alpha);

    for (int i = 0; i < 2; i++) {
        fopMsgM_setNowAlpha(&field_0x124[i], i_alpha);
    }

    fopMsgM_setNowAlpha(&field_0x194, i_alpha);

    for (int i = 0; i < 4; i++) {
        fopMsgM_setNowAlpha(&field_0x1cc[i], i_alpha);
    }

    for (int i = 0; i < 8; i++) {
        fopMsgM_setNowAlpha(&field_0x2ac[i], i_alpha);
    }

    fopMsgM_setNowAlpha(&field_0x46c[0], i_alpha);
    fopMsgM_setNowAlpha(&field_0x554, i_alpha);

    field_0x8d4 = g_owHIO.field_0x18 * i_alpha;
}

/* 8021EE9C-8021F550       .text arrowColor1__15dOperate_wind_cFv */
void dOperate_wind_c::arrowColor1() {
    s16 r0 = 10;
    int r5 = (r0 * 2) + 5;
    s16 r4 = r5 + 5;

    JUtility::TColor sp24;
    JUtility::TColor sp20;

    field_0xec.mUserArea++;
    if (field_0xec.mUserArea > r4) {
        field_0xec.mUserArea = 0;
    }

    if (field_0xec.mUserArea < r0) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0xec.mUserArea, 0);
        sp20.r = field_0x568.corner1.r + (temp_f1 * (field_0x568.corner0.r - field_0x568.corner1.r));
        sp20.g = field_0x568.corner1.g + (temp_f1 * (field_0x568.corner0.g - field_0x568.corner1.g));
        sp20.b = field_0x568.corner1.b + (temp_f1 * (field_0x568.corner0.b - field_0x568.corner1.b));
        sp20.a = field_0x568.corner1.a + (temp_f1 * (field_0x568.corner0.a - field_0x568.corner1.a));
    } else if (field_0xec.mUserArea < r0 + 5) {
        sp20 = field_0x568.corner0;
    } else if (field_0xec.mUserArea < ((r0 * 2) + 5)) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, ((r0 * 2) + 5) - field_0xec.mUserArea, 0);
        sp20.r = field_0x568.corner1.r + (temp_f1 * (field_0x568.corner0.r - field_0x568.corner1.r));
        sp20.g = field_0x568.corner1.g + (temp_f1 * (field_0x568.corner0.g - field_0x568.corner1.g));
        sp20.b = field_0x568.corner1.b + (temp_f1 * (field_0x568.corner0.b - field_0x568.corner1.b));
        sp20.a = field_0x568.corner1.a + (temp_f1 * (field_0x568.corner0.a - field_0x568.corner1.a));
    } else {
        sp20 = field_0x568.corner1;
    }

    if (field_0xec.mUserArea < r0 - 5) {
        sp24 = field_0x568.corner0;
    } else if (field_0xec.mUserArea < r0 + 5) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, r0 + 5 - field_0xec.mUserArea, 0);
        sp24.r = field_0x568.corner1.r + (temp_f1 * (field_0x568.corner0.r - field_0x568.corner1.r));
        sp24.g = field_0x568.corner1.g + (temp_f1 * (field_0x568.corner0.g - field_0x568.corner1.g));
        sp24.b = field_0x568.corner1.b + (temp_f1 * (field_0x568.corner0.b - field_0x568.corner1.b));
        sp24.a = field_0x568.corner1.a + (temp_f1 * (field_0x568.corner0.a - field_0x568.corner1.a));
    } else if (field_0xec.mUserArea < r0 + 10) {
        sp24 = field_0x568.corner1;
    } else {
        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0xec.mUserArea - (r0 + 10), 0);
        sp24.r = field_0x568.corner1.r + (temp_f1 * (field_0x568.corner0.r - field_0x568.corner1.r));
        sp24.g = field_0x568.corner1.g + (temp_f1 * (field_0x568.corner0.g - field_0x568.corner1.g));
        sp24.b = field_0x568.corner1.b + (temp_f1 * (field_0x568.corner0.b - field_0x568.corner1.b));
        sp24.a = field_0x568.corner1.a + (temp_f1 * (field_0x568.corner0.a - field_0x568.corner1.a));
    }

    ((J2DPicture*)field_0x54c.pane)->setCornerColor(sp20, sp24, sp20, sp24);
}

/* 8021F550-8021FBC0       .text arrowColor2__15dOperate_wind_cFv */
void dOperate_wind_c::arrowColor2() {
    s16 var_r31 = g_owHIO.field_0x14;
    s16 var_r30 = g_owHIO.field_0x16;
    s16 r0 = 10;
    s16 r4 = var_r30 + ((r0 * 2) + var_r31);
    JUtility::TColor sp3C;
    JUtility::TColor sp38;

    field_0x124[0].mUserArea++;
    if (field_0x124[0].mUserArea > r4) {
        field_0x124[0].mUserArea = 0;
    }

    if (field_0x124[0].mUserArea < r0) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0x124[0].mUserArea, 0);
        sp38.r = field_0x578.corner0.r + (temp_f1 * (field_0x578.corner1.r - field_0x578.corner0.r));
        sp38.g = field_0x578.corner0.g + (temp_f1 * (field_0x578.corner1.g - field_0x578.corner0.g));
        sp38.b = field_0x578.corner0.b + (temp_f1 * (field_0x578.corner1.b - field_0x578.corner0.b));
    } else if (field_0x124[0].mUserArea < var_r31 + 10) {
        sp38 = field_0x578.corner1;
    } else if (field_0x124[0].mUserArea < ((r0 * 2) + var_r31)) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, ((r0 * 2) + var_r31) - field_0x124[0].mUserArea, 0);
        sp38.r = field_0x578.corner0.r + (temp_f1 * (field_0x578.corner1.r - field_0x578.corner0.r));
        sp38.g = field_0x578.corner0.g + (temp_f1 * (field_0x578.corner1.g - field_0x578.corner0.g));
        sp38.b = field_0x578.corner0.b + (temp_f1 * (field_0x578.corner1.b - field_0x578.corner0.b));
    } else {
        sp38 = field_0x578.corner0;
    }
    
    if (field_0x124[0].mUserArea < var_r31) {
        sp3C = field_0x578.corner1;
    } else if (field_0x124[0].mUserArea < var_r31 + 10) {
        f32 temp_f1 = fopMsgM_valueIncrease(10, (var_r31 + 10) - field_0x124[0].mUserArea, 0);
        sp3C.r = field_0x578.corner0.r + (temp_f1 * (field_0x578.corner1.r - field_0x578.corner0.r));
        sp3C.g = field_0x578.corner0.g + (temp_f1 * (field_0x578.corner1.g - field_0x578.corner0.g));
        sp3C.b = field_0x578.corner0.b + (temp_f1 * (field_0x578.corner1.b - field_0x578.corner0.b));
    } else if (field_0x124[0].mUserArea < var_r30 + (var_r31 + 10)) {
        sp3C = field_0x578.corner0;
    } else {
        f32 temp_f1 = fopMsgM_valueIncrease(10, field_0x124[0].mUserArea - (var_r30 + (var_r31 + 10)), 0);
        sp3C.r = field_0x578.corner0.r + (temp_f1 * (field_0x578.corner1.r - field_0x578.corner0.r));
        sp3C.g = field_0x578.corner0.g + (temp_f1 * (field_0x578.corner1.g - field_0x578.corner0.g));
        sp3C.b = field_0x578.corner0.b + (temp_f1 * (field_0x578.corner1.b - field_0x578.corner0.b));
    }

    sp38.a = 0xFF;
    sp3C.a = 0x96;

    ((J2DPicture*)field_0x124[0].pane)->setCornerColor(sp3C, sp38, sp3C, sp38);
    ((J2DPicture*)field_0x124[1].pane)->setCornerColor(sp3C, sp38, sp3C, sp38);
}

/* 8021FBC0-80220360       .text maskColor__15dOperate_wind_cFv */
void dOperate_wind_c::maskColor() {
    s16 var_r31 = g_owHIO.field_0x10;
    s16 r4 = var_r31 * 4;
    JUtility::TColor sp48[4];

    field_0x46c[0].mUserArea++;
    if (field_0x46c[0].mUserArea >= r4) {
        field_0x46c[0].mUserArea = 0;
    }

    int r4_2 = field_0x46c[0].mUserArea % var_r31;
    f32 var_f1 = fopMsgM_valueIncrease(var_r31, r4_2, 2);

    sp48[0].r = field_0x588.corner0.r + (var_f1 * (field_0x588.corner2.r - field_0x588.corner0.r));
    sp48[0].g = field_0x588.corner0.g + (var_f1 * (field_0x588.corner2.g - field_0x588.corner0.g));
    sp48[0].b = field_0x588.corner0.b + (var_f1 * (field_0x588.corner2.b - field_0x588.corner0.b));
    sp48[0].a = field_0x588.corner0.a + (var_f1 * (field_0x588.corner2.a - field_0x588.corner0.a));

    sp48[1].r = field_0x588.corner1.r + (var_f1 * (field_0x588.corner0.r - field_0x588.corner1.r));
    sp48[1].g = field_0x588.corner1.g + (var_f1 * (field_0x588.corner0.g - field_0x588.corner1.g));
    sp48[1].b = field_0x588.corner1.b + (var_f1 * (field_0x588.corner0.b - field_0x588.corner1.b));
    sp48[1].a = field_0x588.corner1.a + (var_f1 * (field_0x588.corner0.a - field_0x588.corner1.a));

    sp48[2].r = field_0x588.corner2.r + (var_f1 * (field_0x588.corner3.r - field_0x588.corner2.r));
    sp48[2].g = field_0x588.corner2.g + (var_f1 * (field_0x588.corner3.g - field_0x588.corner2.g));
    sp48[2].b = field_0x588.corner2.b + (var_f1 * (field_0x588.corner3.b - field_0x588.corner2.b));
    sp48[2].a = field_0x588.corner2.a + (var_f1 * (field_0x588.corner3.a - field_0x588.corner2.a));

    sp48[3].r = field_0x588.corner3.r + (var_f1 * (field_0x588.corner1.r - field_0x588.corner3.r));
    sp48[3].g = field_0x588.corner3.g + (var_f1 * (field_0x588.corner1.g - field_0x588.corner3.g));
    sp48[3].b = field_0x588.corner3.b + (var_f1 * (field_0x588.corner1.b - field_0x588.corner3.b));
    sp48[3].a = field_0x588.corner3.a + (var_f1 * (field_0x588.corner1.a - field_0x588.corner3.a));

    if (field_0x46c[0].mUserArea < var_r31) {
        ((J2DPicture*)field_0x554.pane)->setCornerColor(sp48[0], sp48[1], sp48[2], sp48[3]);
    } else if (field_0x46c[0].mUserArea < var_r31 * 2) {
        ((J2DPicture*)field_0x554.pane)->setCornerColor(sp48[2], sp48[0], sp48[3], sp48[1]);
    } else if (field_0x46c[0].mUserArea < var_r31 * 3) {
        ((J2DPicture*)field_0x554.pane)->setCornerColor(sp48[3], sp48[2], sp48[1], sp48[0]);
    } else {
        ((J2DPicture*)field_0x554.pane)->setCornerColor(sp48[1], sp48[3], sp48[0], sp48[2]);
    }
}

/* 80220360-802207C8       .text arrowDirection__15dOperate_wind_cFv */
void dOperate_wind_c::arrowDirection() {
    f32 stick_value = stick->getValueStick();
    s16 var_r31 = field_0xec.pane->getRotate();

    if (stick->getValueStick() >= 0.89999998f && fabs(stick_value) - fabs(field_0x8b8) >= 0.0) {
        int stick_control = dOw_stickControl(field_0x8d0, stick->getAngleStick());
        if (field_0x8ca == 0 && stick_control != field_0x8d0) {
            field_0x8d0 = stick_control;

            switch (stick_control) {
            case 8:
                if (mDeg != 315) {
                    field_0x8ca = 7;
                    mDeg = 315;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            case 7:
                if (mDeg != 0) {
                    field_0x8ca = 7;
                    mDeg = 0;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            case 6:
                if (mDeg != 45) {
                    field_0x8ca = 7;
                    mDeg = 45;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            case 5:
                if (mDeg != 90) {
                    field_0x8ca = 7;
                    mDeg = 90;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            case 4:
                if (mDeg != 135) {
                    field_0x8ca = 7;
                    mDeg = 135;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            case 3:
                if (mDeg != 180) {
                    field_0x8ca = 7;
                    mDeg = 180;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            case 2:
                if (mDeg != 225) {
                    field_0x8ca = 7;
                    mDeg = 225;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            case 1:
                if (mDeg != 270) {
                    field_0x8ca = 7;
                    mDeg = 270;
                    mDoAud_seStart(JA_SE_TAKT_WIND_CURSOR);
                }
                break;
            }
        }
    } else if (stick->getValueStick() < 0.89999998f && fabs(stick_value) - fabs(field_0x8b8) < 0.0f) {
        field_0x8d0 = 0;
    }

    field_0x8b8 = stick_value;
    if (field_0x8ca > 0) {
        field_0x8ca--;
    }

    s16 var_r29 = mDeg - var_r31;
    if (var_r29 > 180) {
        var_r29 -= 360;
    } else if (var_r29 < -180) {
        var_r29 += 360;
    }

    if (abs(var_r29) < 16) {
        field_0x8ca = 0;
    }

    f32 temp_f1 = var_r29 * (1.0f - fopMsgM_valueIncrease(7, field_0x8ca, 0));
    var_r31 += (s16)temp_f1;
    arrowRotate(&field_0xec, var_r31);
}

/* 802207C8-802208C4       .text windSet__15dOperate_wind_cFv */
void dOperate_wind_c::windSet() {
    switch (mDeg) {
    case 315:
        dKyw_tact_wind_set(0, -0x6000);
        break;
    case 0:
        dKyw_tact_wind_set(0, -0x8000);
        break;
    case 45:
        dKyw_tact_wind_set(0, 0x6000);
        break;
    case 90:
        dKyw_tact_wind_set(0, 0x4000);
        break;
    case 135:
        dKyw_tact_wind_set(0, 0x2000);
        break;
    case 180:
        dKyw_tact_wind_set(0, 0);
        break;
    case 225:
        dKyw_tact_wind_set(0, -0x2000);
        break;
    case 270:
        dKyw_tact_wind_set(0, -0x4000);
        break;
    }
}

/* 802208C4-8022098C       .text ringScale__15dOperate_wind_cFf */
void dOperate_wind_c::ringScale(f32 i_scale) {
    for (int i = 0; i < 4; i++) {
        if (i == 0) {
            field_0x46c[i].mPosCenter.x = mPosX + i_scale * (field_0x46c[i].mPosCenterOrig.x - mPosX);
            field_0x46c[i].mPosCenter.y = mPosY + i_scale * (field_0x46c[i].mPosCenterOrig.y - mPosY);
        } else {
            field_0x46c[i].mPosCenter.x = field_0x46c[i].mPosCenterOrig.x * i_scale;
            field_0x46c[i].mPosCenter.y = field_0x46c[i].mPosCenterOrig.y * i_scale;
        }

        fopMsgM_paneScaleXY(&field_0x46c[i], i_scale);
    }
}

/* 8022098C-80220A60       .text directionTrans__15dOperate_wind_cFf */
void dOperate_wind_c::directionTrans(f32 param_0) {
    f32 var_f30 = param_0 * 80.0f;

    fopMsgM_paneTrans(&field_0x0c, 0.0f, var_f30);
    fopMsgM_paneTrans(&field_0x44, 0.0f, -var_f30);
    fopMsgM_paneTrans(&field_0x7c, var_f30, 0.0f);
    fopMsgM_paneTrans(&field_0xb4, -var_f30, 0.0f);

    fopMsgM_paneTrans(&field_0x1cc[0], 0.0f, var_f30);
    fopMsgM_paneTrans(&field_0x1cc[1], 0.0f, -var_f30);
    fopMsgM_paneTrans(&field_0x1cc[2], var_f30, 0.0f);
    fopMsgM_paneTrans(&field_0x1cc[3], -var_f30, 0.0f);
}

/* 80220A60-80220CD8       .text lineInit__15dOperate_wind_cFf */
void dOperate_wind_c::lineInit(f32 param_0) {
    f32 temp_f29 = -((-172.0f - REG6_F(5)) * param_0);
    f32 temp = field_0x2ac[0].mPosTopLeftOrig.y - field_0x194.mPosCenterOrig.y;
    f32 temp_f28 = temp * param_0;
    f32 var_f27;
    f32 var_f26;
    f32 temp_f25 = 360.0f / field_0x8ce;
    f32 var_f24 = 11.25f;

    BOOL temp_r29;
    for (int i = 0; i < field_0x8ce; i++) {

        temp_r29 = i % 2;
        if (temp_r29) {
            var_f27 = mPosX + (temp_f28 * std::sinf(M_PI * ((101.25f + var_f24) / 180.0f)));
            var_f26 = mPosY + (temp_f28 * std::cosf(M_PI * ((101.25f + var_f24) / 180.0f)));
        } else {
            var_f27 = mPosX + (temp_f28 * std::sinf(M_PI * ((78.75f + var_f24) / 180.0f)));
            var_f26 = mPosY + (temp_f28 * std::cosf(M_PI * ((78.75f + var_f24) / 180.0f)));
        }

        field_0x598[i] = var_f27 + (temp_f29 * std::sinf(M_PI * (var_f24 / 180.0f)));
        field_0x660[i] = var_f26 + (temp_f29 * std::cosf(M_PI * (var_f24 / 180.0f)));
        field_0x728[i] = (2.0f * var_f27) - field_0x598[i];
        field_0x7f0[i] = (2.0f * var_f26) - field_0x660[i];

        if (temp_r29) {
            field_0x598[i] = var_f27;
            field_0x660[i] = var_f26;
        } else {
            field_0x728[i] = var_f27;
            field_0x7f0[i] = var_f26;
        }

        var_f24 += temp_f25;
    }
}

/* 80220CD8-80220D80       .text lineDraw__15dOperate_wind_cFv */
void dOperate_wind_c::lineDraw() {
    JUtility::TColor color(0xFF, 0xFF, 0xFF, field_0x8d4);
    mMain->setLineColor(color);
    mMain->setLineMax(field_0x8ce);

    for (int i = 0; i < field_0x8ce; i++) {
        mMain->drawLine(i, field_0x598[i], field_0x660[i], field_0x728[i], field_0x7f0[i]);
    }
}

/* 80220D80-80220E18       .text arrowRotate__15dOperate_wind_cFP18fopMsgM_pane_classs */
void dOperate_wind_c::arrowRotate(fopMsgM_pane_class* i_pane, s16 i_angle) {
    if (i_angle < 0) {
        i_angle += 360;
    }
    if (i_angle > 360) {
        i_angle -= 360;
    }

    i_pane->pane->rotate(i_pane->mSizeOrig.x / 2, i_pane->mSizeOrig.y / 2, ROTATE_Z, i_angle);
}

/* 80220E18-80221090       .text initialize__15dOperate_wind_cFv */
void dOperate_wind_c::initialize() {
    mTimer = 0;
    field_0x8ca = 0;
    field_0x8ce = g_owHIO.field_0x0e;
    field_0x8d4 = 0;
    field_0x8d0 = 0;

    field_0xec.mUserArea = 0;
    field_0x46c[0].mUserArea = 0;
    field_0x124[0].mUserArea = 30;
    field_0x124[1].mUserArea = 35;

    ((J2DPicture*)field_0x124[0].pane)->setCornerColor(
        JUtility::TColor(0xFFFFFF96),
        JUtility::TColor(0x00FFFFFF),
        JUtility::TColor(0xFFFFFF96),
        JUtility::TColor(0x00FFFFFF)
    );

    ((J2DPicture*)field_0x124[1].pane)->setCornerColor(
        JUtility::TColor(0xFFFFFF96),
        JUtility::TColor(0x00FFFFFF),
        JUtility::TColor(0xFFFFFF96),
        JUtility::TColor(0x00FFFFFF)
    );

    mPosX = field_0x46c[0].mPosTopLeftOrig.x + field_0x46c[0].mSizeOrig.x;
    mPosY = field_0x46c[0].mPosTopLeftOrig.y;

    cXyz* wind_vec = dKyw_get_wind_vec();
    s16 temp_r3 = cM_atan2s(wind_vec->x, wind_vec->z) + 0x8000;
    mDeg = dOw_angleRegular(((180.0f * temp_r3) / (f32)0x8000) - 90.0f);
    arrowRotate(&field_0xec, mDeg);
    arrowRotate(&field_0x194, mDeg + 90);

    field_0x8b8 = stick->getValueStick();
    lineInit(0.0f);
}

/* 80221090-802213B0       .text _create__15dOperate_wind_cFv */
void dOperate_wind_c::_create() {
    scrn1 = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(965, 965, 990, 990), scrn1 != NULL);
    scrn1->set("operate_wind.blo", dComIfGp_getWindResArchive());

    scrn2 = new J2DScreen();
    JUT_ASSERT(VERSION_SELECT(969, 969, 994, 994), scrn2 != NULL);
    scrn2->set("operate_wind_mask.blo", dComIfGp_getWindResArchive());

    stick = new STControl(5, 2, 3, 2, 1.0f, 1.0f, 0x1000, 0x2000);
    JUT_ASSERT(VERSION_SELECT(973, 973, 998, 998), stick != NULL);

    mMain = new dDlst_Ow_main_c();
    JUT_ASSERT(VERSION_SELECT(976, 976, 1001, 1001), mMain != NULL);
    mMain->setScreen(scrn1);

    mMask = new dDlst_Ow_mask_c();
    JUT_ASSERT(VERSION_SELECT(980, 980, 1005, 1005), mMask != NULL);
    mMask->setScreen(scrn2);

    screenSet();
    initialize();
}

/* 802213B0-8022147C       .text _delete__15dOperate_wind_cFv */
void dOperate_wind_c::_delete() {
    delete scrn1;
    delete scrn2;
    delete stick;
    delete mMain;
    delete mMask;
    dComIfGp_getWindResArchive()->removeResourceAll();
}

/* 8022147C-8022151C       .text _move__15dOperate_wind_cFv */
void dOperate_wind_c::_move() {
    if (!dMenu_flag()) {
        if (CPad_CHECK_TRIG_A(0)) {
            windSet();
            dComIfGp_setOperateWindChangeOff();
        } else if (CPad_CHECK_TRIG_B(0)) {
            dComIfGp_setOperateWindCancelOff();
        }

        arrowColor1();
        arrowColor2();
        maskColor();
        arrowDirection();
    }
}

/* 8022151C-8022163C       .text _draw__15dOperate_wind_cFv */
void dOperate_wind_c::_draw() {
    fopMsgM_setAlpha(&field_0x0c);
    fopMsgM_setAlpha(&field_0x44);
    fopMsgM_setAlpha(&field_0x7c);
    fopMsgM_setAlpha(&field_0xb4);
    fopMsgM_setAlpha(&field_0x54c);

    for (int i = 0; i < 2; i++) {
        fopMsgM_setAlpha(&field_0x124[i]);
    }

    fopMsgM_setAlpha(&field_0x194);

    for (int i = 0; i < 4; i++) {
        fopMsgM_setAlpha(&field_0x1cc[i]);
    }

    for (int i = 0; i < 8; i++) {
        fopMsgM_setAlpha(&field_0x2ac[i]);
    }

    fopMsgM_setAlpha(&field_0x46c[0]);
    fopMsgM_setAlpha(&field_0x554);

    lineDraw();
    dComIfGd_set2DOpa(mMask);
    dComIfGd_set2DOpa(mMain);
}

/* 8022163C-802216F0       .text _open__15dOperate_wind_cFv */
bool dOperate_wind_c::_open() {
    bool rt = false;
    if (mTimer < 10) {
        mTimer++;

        f32 temp_f1 = fopMsgM_valueIncrease(10, mTimer, 0);
        alphaSet(temp_f1);
        ringScale(temp_f1);

        f32 temp_f1_2 = fopMsgM_valueIncrease(10, 10 - mTimer, 0);
        directionTrans(temp_f1_2);
        lineInit(temp_f1);
    }

    if (mTimer >= 10) {
        rt = true;
    }

    return rt;
}

/* 802216F0-80221770       .text _close__15dOperate_wind_cFv */
bool dOperate_wind_c::_close() {
    s16 temp_r4 = g_owHIO.field_0x18;

    bool rt = false;
    if (mTimer > 0) {
        mTimer--;

        f32 temp_f1 = fopMsgM_valueIncrease(temp_r4, mTimer, 0);
        alphaSet(temp_f1);
    }

    if (mTimer <= 0) {
        rt = true;
    }

    return rt;
}

/* 80221770-80221830       .text _create__5dOw_cFv */
void dOw_c::_create() {
    dOw_scrn = new dOperate_wind_c();
    JUT_ASSERT(VERSION_SELECT(1119, 1119, 1144, 1144), dOw_scrn != NULL);

#if VERSION == VERSION_PAL
    void* p = heap->alloc(0xC00, 0x20);
    JUT_ASSERT(1149, p != NULL);
    dOw_scrn->shipfontTimg = (ResTIMG*)p;
#endif

    dOw_scrn->_create();
}

/* 80221830-80221880       .text _delete__5dOw_cFv */
void dOw_c::_delete() {
#if VERSION == VERSION_PAL
    if (dOw_scrn->shipfontTimg != NULL) {
        heap->free(dOw_scrn->shipfontTimg);
        dOw_scrn->shipfontTimg = NULL;
    }
#endif

    dOw_scrn->_delete();
    delete dOw_scrn;
}

/* 80221880-802218B4       .text dOw_Draw__FP5dOw_c */
static BOOL dOw_Draw(dOw_c* i_this) {
    if (i_this->getStatus() != 0) {
        i_this->_draw();
    }
    return TRUE;
}

/* 802218B4-802219A4       .text dOw_Execute__FP5dOw_c */
static BOOL dOw_Execute(dOw_c* i_this) {
    static u8 wind_flag = dComIfGp_getOperateWind();
    JKRHeap* old_heap = mDoExt_setCurrentHeap(i_this->getHeap());

    if (dComIfGp_getOperateWind() == 2) {
        if (i_this->_open()) {
            i_this->_move();
        }
    } else {
        if (wind_flag == 2) {
            i_this->setTimer(g_owHIO.field_0x08);
        }

        if (!i_this->_close()) {
            i_this->_move();
        } else {
            i_this->setStatus(0);
            fopMsgM_Delete(i_this);
        }
    }

    wind_flag = dComIfGp_getOperateWind();
    mDoExt_setCurrentHeap(old_heap);
    return TRUE;
}

/* 802219A4-802219AC       .text dOw_IsDelete__FP5dOw_c */
static BOOL dOw_IsDelete(dOw_c* i_this) {
    UNUSED(i_this);
    return TRUE;
}

/* 802219AC-80221A04       .text dOw_Delete__FP5dOw_c */
static BOOL dOw_Delete(dOw_c* i_this) {
    JKRHeap* old_heap = mDoExt_setCurrentHeap(i_this->getHeap());
    i_this->_delete();
    mDoExt_setCurrentHeap(old_heap);
    fopMsgM_destroyExpHeap(i_this->getHeap());
#if VERSION == VERSION_DEMO
    g_owHIO.removeHIO();
#endif
    return TRUE;
}

/* 80221A04-80221AA0       .text dOw_Create__FP9msg_class */
static cPhs_State dOw_Create(msg_class* i_msg) {
    dOw_c* i_this = (dOw_c*)i_msg;

#if VERSION == VERSION_DEMO
    // "Wind Direction Control Screen
    g_owHIO.entryHIO("風向操作表示画面");
#endif

    JKRExpHeap* heap = fopMsgM_createExpHeap(20000);
    JUT_ASSERT(VERSION_SELECT(1310, 1310, 1351, 1351), heap != NULL);
    i_this->setHeap(heap);

    JKRHeap* old_heap = mDoExt_setCurrentHeap(i_this->getHeap());
    i_this->setStatus(1);
    i_this->_create();
    mDoExt_setCurrentHeap(old_heap);
    return cPhs_COMPLEATE_e;
}

static msg_method_class l_dOperate_wind_Method = {
    (process_method_func)dOw_Create,
    (process_method_func)dOw_Delete,
    (process_method_func)dOw_Execute,
    (process_method_func)dOw_IsDelete,
    (process_method_func)dOw_Draw,
};

msg_process_profile_definition g_profile_OPERATE_WIND = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 12,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_OPERATE_WIND_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dOw_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopMsg_Method,
    /* Draw Prio    */ fpcDwPi_OPERATE_WIND_e,
    /* Msg SubMtd   */ &l_dOperate_wind_Method,
};
