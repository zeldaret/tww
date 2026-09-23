/**
 * d_a_sss.cpp
 * Enemy - Dexivine (Forbidden Woods, Wind Temple)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_sss.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "res/Object/Sss.h"

f32 size_d[10] = {10, 10, 9.5, 9.0, 8.5, 8.0, 7.5, 7.0, 6.5, 6.5};
f32 g_d[10] = {50, 50, 35, 25, 15, 9, 6, 6, 6, 6};

cXyz non_pos;

/* 000000EC-000001F0       .text hand_draw__FP9sss_class */
void hand_draw(sss_class* i_this) {
    /* Nonmatching */
    g_env_light.setLightTevColorType(i_this->field_0x2B4->getModel(), &i_this->tevStr);
    i_this->field_0x2B4->updateDL();
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    i_this->field_0x300.update(10, color, &i_this->tevStr);
    dComIfGd_set3DlineMat(&i_this->field_0x300);
    if (i_this->field_0x2FC > 0.1f) {
        GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
        i_this->field_0x454.update(5, color, &i_this->tevStr);
        dComIfGd_set3DlineMat(&i_this->field_0x454);
    }
}

/* 000001F0-00000248       .text daSss_Draw__FP9sss_class */
static BOOL daSss_Draw(sss_class* i_this) {
    /* Nonmatching */
    if (i_this->field_0x2B8 != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->eyePos, &i_this->tevStr);
        hand_draw(i_this);
    }
    return TRUE;
}

/* 00000248-000002C8       .text hand_close__FP9sss_class */
void hand_close(sss_class* i_this) {
    /* Nonmatching */
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_TOJIRU_e);
    i_this->field_0x2B4->setAnm(anm, 0, 1, 1, 0, -1, NULL);
}

/* 000002C8-00000348       .text hand_open__FP9sss_class */
void hand_open(sss_class* i_this) {
    /* Nonmatching */
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e);
    i_this->field_0x2B4->setAnm(anm, 0, 1, 1, 0, -1, NULL);
}

/* 00000348-00000444       .text hand_mtx_set__FP9sss_class */
void hand_mtx_set(sss_class* i_this) {
    /* Nonmatching */
    MtxTrans(i_this->field_0x2D4.x, i_this->field_0x2D4.y, i_this->field_0x2D4.z, false);
    mDoMtx_XrotM(*calc_mtx, i_this->field_0x2E0);
    mDoMtx_YrotM(*calc_mtx, i_this->field_0x2E2);
    mDoMtx_XrotM(*calc_mtx, REG12_S(1) + -0x4000);
    MtxScale(0.5, REG0_F(0) + 0.2f, 0.5, true);
    MtxTrans(0, REG12_F(3) + -130, 0, true);
    J3DModel* temp = i_this->field_0x2B4->getModel();
    MTXCopy(*calc_mtx, temp->getBaseTRMtx());
}

/* 00000444-000004CC       .text control3__FP9sss_class */
void control3(sss_class* i_this) {
    /* Nonmatching */
    sss_s* sp = i_this->field_0x33C;
    for (int i = 0; i < 10; i++) {
        f32 temp;
        temp = cM_ssin(i_this->field_0x2BC * 500 + i * 100) * 0.1f + 0.8f;
        temp *= size_d[i];
        sp++->field_0x18 = temp;
    }
}

/* 000004CC-00000804       .text control1__FP9sss_class */
void control1(sss_class* i_this) {
    /* Nonmatching */
    cXyz v1;
    cXyz v2;
    cXyz v3;
    cXyz v4;

    i_this->field_0x33C[0].field_0x00 = i_this->current.pos;
    sss_s* sp = &i_this->field_0x33C[1];
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    v1.x = 0; 
    v1.y = 0;
    v1.z = i_this->field_0x2F0;
    MtxPosition(&v1, &v2);
    v1.z = i_this->field_0x2E8;
    f32 f1 = i_this->field_0x2F4;
    for (int i = 1; i < 9; i++) {
        v4.x = f1 * cM_ssin((i_this->field_0x2BC * (REG0_S(5) + 1100)) + i * (REG0_S(6) + 4000));
        v4.y = g_d[i];
        v4.z = f1 * cM_scos((i_this->field_0x2BC * (REG0_S(7) + 800)) + i * (REG0_S(8) + 4000));
        f32 one = 1.0f;
        MtxPosition(&v4, &v3);
        f32 x_val = v3.x * one;
        x_val += (sp[0].field_0x00.x - sp[-1].field_0x00.x) + v2.x * one;
        f32 y_val = v3.y * one;
        y_val += (sp[0].field_0x00.y - sp[-1].field_0x00.y) + v2.y * one;
        f32 z_val = v3.z * one;
        z_val += (sp[0].field_0x00.z - sp[-1].field_0x00.z) + v2.z * one;
        int xz_atan = cM_atan2s(x_val, z_val);
        s16 y_atan = -cM_atan2s(y_val, std::sqrtf(SQUARE(x_val) + SQUARE(z_val)));
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, xz_atan);
        mDoMtx_XrotM(*calc_mtx, y_atan);
        MtxPosition(&v1, &v4);
        MtxPull();
        sp[0].field_0x00 = sp[-1].field_0x00 + v4;
        sp++;
    }
}

/* 00000840-00000B0C       .text control2__FP9sss_class */
void control2(sss_class* i_this) {
    /* Nonmatching */
    cXyz v1;
    cXyz v2;

    v2.x = 0;
    v2.y = 0;
    v2.z = i_this->field_0x2E8;
    i_this->field_0x33C[9].field_0x00 = i_this->field_0x2C8;
    sss_s* current = &i_this->field_0x33C[8];
    for (int i = 8; i >= 1; i--) {
        f32 x_diff = current->field_0x00.x - current[1].field_0x00.x;
        f32 y_diff = current->field_0x00.y - current[1].field_0x00.y;
        f32 z_diff = current->field_0x00.z - current[1].field_0x00.z;
        int xz_atan = cM_atan2s(x_diff, z_diff);
        s16 y_atan = -cM_atan2s(y_diff, std::sqrtf(SQUARE(x_diff) + SQUARE(z_diff)));
        mDoMtx_YrotS(*calc_mtx, xz_atan);
        mDoMtx_XrotM(*calc_mtx, y_atan);
        if (i == 8) {
            v2.z = i_this->field_0x2E8 - 10;
            if (v2.z < 0) {
                v2.z = 0;
            }
        } else {
            v2.z = i_this->field_0x2E8;
        }
        MtxPosition(&v2, &v1);
        current->field_0x00 = current[1].field_0x00 + v1;
        current--;
    }
    i_this->field_0x2D4 = i_this->field_0x33C[9].field_0x00;
    cXyz v3 = i_this->field_0x33C[8].field_0x00 - i_this->field_0x33C[9].field_0x00;
    i_this->field_0x2E0 = -cM_atan2s(v3.y, v3.z);
    i_this->field_0x2E2 = cM_atan2s(v2.x, std::sqrtf(SQUARE(v2.y) + SQUARE(v2.z)));
    hand_mtx_set(i_this);
}

/* 00000B0C-00000F78       .text cut_control1__FP9sss_class */
void cut_control1(sss_class* i_this) {
    /* Nonmatching */
    cXyz v1;
    cXyz v2;
    
    i_this->field_0x490[0].field_0x00 = i_this->current.pos;
    sss_s* current = &i_this->field_0x490[1];
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    v2.z = i_this->field_0x2FC;
    f32 reg = REG0_F(18) + 50;
    for (int i = 1; i < 5; i++) {
        cXyz temp_2;
        temp_2.x = reg * cM_ssin((i_this->field_0x2BC * (REG0_S(5) + 4100)) + i * (REG0_S(6) + 10000));
        temp_2.y = REG0_F(17) + 50;
        temp_2.z = reg * cM_scos((i_this->field_0x2BC * (REG0_S(7) + 4400)) + i * (REG0_S(8) + 10000));
        MtxPosition(&temp_2, &v1);
        f32 x_val = v1.x + (current->field_0x00.x - current[-1].field_0x00.x);
        f32 y_val = v1.y + (current->field_0x00.y - current[-1].field_0x00.y);
        f32 z_val = v1.z + (current->field_0x00.z - current[-1].field_0x00.z);
        int xz_atan = cM_atan2s(x_val, z_val);
        s16 y_atan = -cM_atan2s(y_val, std::sqrtf(SQUARE(x_val) + SQUARE(z_val)));
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, xz_atan);
        mDoMtx_XrotM(*calc_mtx, y_atan);
        MtxPosition(&v2, &temp_2);
        MtxPull();
        current->field_0x00 = current[-1].field_0x00 + temp_2;
        current++;
    }
    if (i_this->field_0xA10 == NULL && i_this->field_0xA18 != FALSE) {
        i_this->field_0xA10 = dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, &i_this->field_0x490[4].field_0x00);
        i_this->field_0x2C2[1] = 60;
    }
    if (i_this->field_0xA10) {
        cXyz v = i_this->field_0x490[4].field_0x00 - i_this->field_0x490[3].field_0x00;
        JGeometry::TVec3<s16> rot;
        rot.y = (int)cM_atan2s(v.x, v.z);
        rot.x = -cM_atan2s(v2.y, std::sqrtf(SQUARE(v2.x) + SQUARE(v2.z)));
        i_this->field_0xA10->setGlobalTranslation(i_this->field_0x490[4].field_0x00.x, i_this->field_0x490[4].field_0x00.y, i_this->field_0x490[4].field_0x00.z);
        i_this->field_0xA10->setGlobalRotation(rot);
        if (i_this->field_0x2C2[1] == 1) {
            i_this->field_0xA10->becomeInvalidEmitter();
            i_this->field_0xA10 = NULL;
        }
    }
}

/* 00000F78-000014F4       .text cut_control2__FP9sss_class */
void cut_control2(sss_class* i_this) {
    /* Nonmatching */
    cXyz v1;
    cXyz v2;
    v1.x = 0;
    v1.y = 0;
    v1.z = i_this->field_0x2E8;
    i_this->field_0x33C[9].field_0x00 = i_this->field_0x2C8;
    sss_s* current = &i_this->field_0x33C[8];
    f32 f1 = i_this->field_0x2F4;
    for (int i = 8; i >= 0; i--) {
        v2.x = f1 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 2500) + i * (REG0_S(6) + 3000));
        v2.y = f1 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 2950) + i * (REG0_S(6) + 4000));
        v2.z = f1 * cM_scos(i_this->field_0x2BC * (REG0_S(7) + 2800) + i * (REG0_S(8) + 3500));
        f32 x_val = v2.x + (current->field_0x00.x - current[1].field_0x00.x);
        f32 y_val = current->field_0x00.y - 10 + v2.y;
        f32 f2 = i_this->field_0x2F8 + 5;
        if (y_val < f2) {
            y_val = f2;
        }
        y_val -= current[1].field_0x00.y;
        f32 z_val = v2.z + (current->field_0x00.z - current[1].field_0x00.z);
        int xz_atan = cM_atan2s(x_val, z_val);
        s16 y_atan = -cM_atan2s(y_val, std::sqrtf(SQUARE(x_val) + SQUARE(z_val)));
        mDoMtx_YrotS(*calc_mtx, xz_atan);
        mDoMtx_XrotM(*calc_mtx, y_atan);
        if (i == 8) {
            v1.z = i_this->field_0x2E8 - 10;
            if (v1.z < 0) {
                v1.z = 0;
            }
        } else {
            v1.z = i_this->field_0x2E8;
        }
        cXyz temp;
        MtxPosition(&v1, &temp);
        current->field_0x00 = current[1].field_0x00 + temp;
        current--;
    }
    i_this->field_0x2D4 = i_this->field_0x33C[9].field_0x00;
    cXyz v = i_this->field_0x33C[8].field_0x00 - i_this->field_0x33C[9].field_0x00;
    i_this->field_0x2E0 = -cM_atan2s(v.y, v.z);
    i_this->field_0x2E2 = cM_atan2s(v1.x, std::sqrtf(SQUARE(v1.y) + SQUARE(v1.z)));
    hand_mtx_set(i_this);
    if (!i_this->field_0xA14 && i_this->field_0xA18) {
        i_this->field_0xA14 = dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, &i_this->field_0x33C[0].field_0x00);
    }
    if (i_this->field_0xA14) {
        cXyz v = i_this->field_0x33C[0].field_0x00 - i_this->field_0x33C[1].field_0x00;
        JGeometry::TVec3<s16> rot;
        rot.y = (int)cM_atan2s(v.x, v.z);
        rot.x = -cM_atan2s(v1.y, std::sqrtf(SQUARE(v1.x) + SQUARE(v1.z)));
        rot.z = 0;
        i_this->field_0xA14->setGlobalTranslation(i_this->field_0x33C[0].field_0x00.x, i_this->field_0x33C[0].field_0x00.y, i_this->field_0x33C[0].field_0x00.z);
        i_this->field_0xA14->setGlobalRotation(rot);
        if (i_this->field_0x2C2[1] == 1) {
            i_this->field_0xA14->becomeInvalidEmitter();
            i_this->field_0xA14 = NULL;
            i_this->field_0xA18 = false;
        }
    }
}

/* 000014F4-00002614       .text hand_move__FP9sss_class */
void hand_move(sss_class* i_this) {
    /* Nonmatching */
    bool b1;
    bool b2;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    cXyz v1;
    cXyz v2;
    cXyz v3;
    cXyz v4;

    daPy_py_c* player = (daPy_py_c*) dComIfGp_getPlayer(0);
    daPy_lk_c* link = (daPy_lk_c*) dComIfGp_getLinkPlayer();
    dBgS_GndChk gnd_chk;
    gnd_chk.MaskNormalGrp();
    b1 = false;
    b2 = false;
    f32 speedRatio = 0.1;
    f6 = 8;
    f32 f7 = 0;
    f32 target = 30;
    f32 maxSpeed = 1;
    f4 = fopAcM_searchActorDistance(i_this, dComIfGp_getPlayer(0));
    f1 = 5;
    if (i_this->field_0x2B9 != 0xFF) {
        f5 = i_this->field_0x2B9 * 10.0f;
    } else {
        f5 = 1000;
    }
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    switch (i_this->field_0x2C0) {
        case 0: {
            bool b = false;
            v2 = i_this->current.pos;
            target = 0;
            maxSpeed = 0.5;
            f2 = -20;
            if (!i_this->field_0x2C2[0]) {
                if (i_this->field_0x2BA) {
                    if (dComIfGs_isSwitch(i_this->field_0x2BA, fopAcM_GetRoomNo(i_this)) || REG0_S(0)) {
                        i_this->field_0x2C0 = 1;
                        i_this->field_0x2C2[0] = 30;
                        hand_open(i_this);
                        b = true;
                    }
                } else {
                    if (f4 < f5) {
                        i_this->field_0x2C0 = 1;
                        i_this->field_0x2C2[0] = 30;
                        hand_open(i_this);
                        b = true;
                    }
                }
            }
            if (std::abs(i_this->field_0x2C8.y - i_this->current.pos.y) < 5 && b) {
                if (i_this->field_0x2B8 == 1) {
                    fopAcM_seStart(i_this, JA_SE_OBJ_SVINE_OUT_WATER, 0);
                } else {
                    fopAcM_seStart(i_this, JA_SE_OBJ_SVINE_OUT, 0);
                }
            }
            break;
        }
        case 1:
            v3.x = (REG0_F(13) + 50) * cM_ssin(i_this->field_0x2BC * 600);
            v3.y = 250;
            v3.z = (REG0_F(13) + 50) * cM_ssin(i_this->field_0x2BC * 700);
            MtxPosition(&v3, &v1);
            v4 = i_this->current.pos + v1;
            if (i_this->field_0x2C2[0] == 0 && f4 < REG0_F(14) + 300) {
                i_this->field_0x2C0 = 2;
            }
            if ((f5 + 100) > f4) {
                i_this->field_0x2C0 = 0;
            }
            break;
        case 2:
            f6 = 15;
            f7 = 10;
            b1 = true;
            v2.x = i_this->current.pos.x;
            v2.z = i_this->current.pos.z;
            v2.y = i_this->current.pos.y;
            v2.y += 70;
            if (f4 > REG0_F(14) + 450) {
                i_this->field_0x2C0 = 1;
                f3 = 0.5;
                i_this->speedF = 0;
            }
            v4 = v2 - i_this->field_0x2C8;
            if (!(std::sqrtf(VECSquareMag(&v3)) < 20) || player != link) break;
            i_this->field_0x2C0 = 3;
            hand_close(i_this);
            fopAcM_seStart(i_this, JA_SE_OBJ_SVINE_GRASP, 0);
        case 3:
            player->onNoResetFlg1(daPy_lk_c::daPyFlg1_VINE_CATCH);
            player->setFace(daPy_lk_c::daPyFace_TIYAYA);
            if (dComIfGs_getMagic()) {
                g_dComIfG_gameInfo.play.field_0x4965 |= 1;
                fopAcM_seStart(i_this, JA_SE_OBJ_ATK_VINE_MP_SUCK, 0);
                if ((i_this->field_0x2BC & 0x1F) == 0) {
                    dComIfGp_setItemMagicCount(-1);
                }
            }
            if (f4 > REG6_F(2) + 400) {
                f4 = (REG6_F(0) + 0.1f) * (f4 - REG6_F(2));
                if (f4 > REG6_F(1) + 100) {
                    f4 = REG6_F(1) + 100;
                }
                s16 temp = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0));
                player->setOutPower(f4, temp - 0x8000, 0);
            }
            v2.x = player->current.pos.x;
            v2.z = player->current.pos.z;
            v2.y = player->current.pos.y;
            v2.y += 70;
            f6 = 200;
            speedRatio = 1;
            f3 = 5;
            i_this->field_0x2F4 = REG0_F(11) + 10;
            if (f4 > 800) {
                i_this->field_0x2C0 = 1;
                i_this->speedF = 30;
                hand_open(i_this);
            }
            break;
        case 5:
            f1 = 50;
            i_this->field_0x2F4 = 50;
            b2 = true;
            target = 25;
            maxSpeed = 1;
            i_this->field_0x2C8 += i_this->speed;
            i_this->speed.y -= 3;
            i_this->field_0x2C2[2] = 5;
            {
                f32 temp_z = i_this->field_0x2C8.z;
                f32 temp_y = i_this->field_0x2C8.y;
                f32 temp_x = i_this->field_0x2C8.x;
                temp_y += 200;
                gnd_chk.m_pos.z = temp_z;
                gnd_chk.m_pos.y = temp_y;
                gnd_chk.m_pos.x = temp_x;
            }
            i_this->field_0x2F8 = dComIfG_Bgsp()->GroundCross(&gnd_chk);
            if (i_this->field_0x2F8 == -1e9f || i_this->field_0x2C8.y <= i_this->field_0x2F8 + 10) {
                i_this->field_0x2C8.y = i_this->field_0x2F8 + 10;
                i_this->field_0x2C2[0] = 100;
                i_this->field_0x2C0 = 6;
            }
            break;
        case 6:
            b2 = true;
            f1 = 0;
            i_this->field_0x2C2[2] = 10;
            if (i_this->field_0x2C2[0] < 40) {
                target = f1;
                maxSpeed = 1;
                i_this->field_0x2C8.y -= 2;
            }
            if (i_this->field_0x2C2[0] == 0) {
                i_this->field_0x2C8 = i_this->current.pos;
                i_this->field_0x2C0 = 0;
                i_this->field_0x2E8 = 0;
                i_this->field_0x2FC = 0;
            }
    }
    cLib_addCalc2(&i_this->field_0x2E8, target, 0.5, maxSpeed);
    cLib_addCalc2(&i_this->field_0x2F0, f7, 1, 0.2);
    cLib_addCalc2(&i_this->field_0x2F4, f1, 1, 1.5);
    if (!b2) {
        cLib_addCalc2(&i_this->speedF, f6, 1, f3);
        if (i_this->field_0xA08 > 1 && i_this->field_0x2C0 != 3) {
            mDoMtx_YrotS(*calc_mtx, i_this->field_0xA0C);
            v3.x = 0;
            v3.y = REG6_F(9) + 100;
            v3.z = i_this->field_0xA08;
            MtxPosition(&v3, &v1);
            v4 = i_this->current.pos + v1;
            speedRatio = 0.1f;
            i_this->speedF = i_this->field_0xA08 * 0.2f;
            if (i_this->speedF > REG6_F(8) + 30) {
                i_this->speedF = REG6_F(8) + 30;
            }
        }
        cLib_addCalc0(&i_this->field_0xA08, 1, REG6_F(7) + 5);
        cLib_addCalc2(&i_this->field_0x2C8.x, v2.x, speedRatio, i_this->speedF);
        cLib_addCalc2(&i_this->field_0x2C8.y, v2.y, speedRatio, i_this->speedF);
        cLib_addCalc2(&i_this->field_0x2C8.z, v2.z, speedRatio, i_this->speedF);
        cLib_addCalc2(&i_this->current.pos.y, i_this->home.pos.y + f2, 0.5, 0.5);
        if (b1 && i_this->current.angle.x == 0) {
            cLib_addCalcAngleS2(&i_this->current.angle.y, fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0)), 16, 2048);
        }
        control1(i_this);
        control2(i_this);
    } else {
        cut_control1(i_this);
        cut_control2(i_this);
        sss_s* pointer = i_this->field_0x490;
        cXyz* segments = i_this->field_0x454.getPos(0);
        u8* sizes = i_this->field_0x454.getSize(0);
        for (int i = 0; i < 5; i++) {
            segments[i] = pointer[i].field_0x00;
            sizes[i] = pointer[i].field_0x18;
        }
        cLib_addCalc0(&i_this->field_0x2FC, 1, REG0_F(1) + 1);
    }
    control3(i_this);
    i_this->field_0x2B4->play(NULL, 0, 0);
    for (int i = 0; i < 10; i++) {
        i_this->field_0x300.getPos(0)[i] = i_this->field_0x33C[i].field_0x00;
        // local_e8 = i_this->field_0x33C[i].field_0x18;
        i_this->field_0x300.getSize(0)[i] = i_this->field_0x33C[i].field_0x18;
    }
    i_this->eyePos = i_this->field_0x300.getPos(0)[5];
    i_this->attention_info.position = i_this->eyePos;
    i_this->field_0x51C.Move();
    if (b2) {
        i_this->field_0x8DC.SetC(non_pos);
    } else {
        i_this->field_0x8DC.SetC(i_this->eyePos);
    }
    dComIfG_Ccsp()->Set(&i_this->field_0x8DC);
    for (int i = 0; i < 3; i++) {
        // TODO
        if (!b2) {
            i_this->field_0x558[i].SetC(v4);
        } else {
            i_this->field_0x558[i].SetC(non_pos);
        }
        if (i_this->field_0x2C0 == 3) {
            i_this->field_0x558[i].OffCoSPrmBit(1);
        } else {
            i_this->field_0x558[i].OnCoSPrmBit(1);
        }
        dComIfG_Ccsp()->Set(i_this->field_0x558[0].GetCoHitObj());
    }
    u32 u1 = 0;
    for (int i = 0; i < 3; i++) {
        if (i_this->field_0x558[i].ChkTgHit()) {
            u1 = i + 1 & 0xFF;
            break;
        }
    }
    if ((u1 != 0 || i_this->field_0x8DC.ChkTgHit() != 0) && i_this->field_0x2C2[2] == 0) {
        CcAtInfo at_info;
        at_info.pParticlePos = NULL;
        i_this->field_0x2C2[2] = 20;
        if (u1 == 0) {
            at_info.mpObj = i_this->field_0x8DC.GetTgHitObj();
            at_info.pParticlePos = i_this->field_0x8DC.GetTgHitPosP();
            at_power_check(&at_info);
            if (at_info.mResultingAttackType == 8) {
                i_this->field_0xA08 = REG6_F(6) + 300;
                i_this->field_0xA0C = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0)) - 0x8000;
                return;
            }
        } else {
            // TODO
            dCcD_GObjInf* objInf = NULL;
            at_info.mpObj = objInf->GetTgHitObj();
            at_info.pParticlePos = objInf->GetTgHitPosP();
        }
        fopAcM_seStart(i_this, JA_SE_LK_LAST_HIT, 0);
        fopAcM_seStart(i_this, JA_SE_OBJ_SVINE_CRASH, 0);
        i_this->field_0x2C0 = 5;
        i_this->speed.x = cM_rndFX(10);
        i_this->speed.y = cM_rndFX(10) + 30;
        i_this->speed.z = cM_rndFX(10);
        cXyz scale(0.3, 0.3, 0.3);
        dComIfGp_particle_set(0x16, &i_this->eyePos, NULL, &scale);
        i_this->field_0xA18 = true;
        cXyz* this_is_wrong = &i_this->field_0x490[0].field_0x00;
        for (int i = 0; i < 5; i++) {
            *this_is_wrong = i_this->field_0x33C[i].field_0x00;
            this_is_wrong[2].x = i_this->field_0x33C[i].field_0x18;
            if (i == 4) {
                cXyz temp = *this_is_wrong - *((cXyz*) &this_is_wrong[-3].z);
                i_this->field_0x2FC = (REG0_F(2) + 1.5f) * std::sqrtf(VECSquareMag(&temp));
            }
        }
        hand_open(i_this);
    }
    return;
}

/* 00002614-00002618       .text hand_main__FP9sss_class */
void hand_main(sss_class*) {
    /* Nonmatching */
}

/* 00002618-0000269C       .text daSss_Execute__FP9sss_class */
static BOOL daSss_Execute(sss_class* i_this) {
    /* Nonmatching */
    int j;

    i_this->field_0x2BC = i_this->field_0x2BC + 1;
    j = 0;
    for (int i = 2; i != 0; i--) {
        if (i_this->field_0x2C2[j] != '\0') {
            i_this->field_0x2C2[j] = i_this->field_0x2C2[j] - 1;
        }
        j = j + 1;
    }
    if (i_this->field_0x2C2[2] != '\0') {
        i_this->field_0x2C2[2] = i_this->field_0x2C2[2] - 1;
    }
    if (!i_this->field_0x2B8) {
        hand_main(i_this);
    } else {
        hand_move(i_this);
    }
    return TRUE;
}

/* 0000269C-000026A4       .text daSss_IsDelete__FP9sss_class */
static BOOL daSss_IsDelete(sss_class*) {
    return TRUE;
}

/* 000026A4-00002720       .text daSss_Delete__FP9sss_class */
static BOOL daSss_Delete(sss_class* i_this) {
    /* Nonmatching */
    dComIfG_resDelete(&i_this->field_0x2AC, "Sss");
    JPABaseEmitter* emitter = i_this->field_0xA10;
    if (emitter) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(JPAEmtrStts_StopEmit);
    }
    emitter = i_this->field_0xA14;
    if (emitter) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(JPAEmtrStts_StopEmit);
    }
    return TRUE;
}

/* 00002720-000028A0       .text useHeapInit__FP9sss_class */
BOOL useHeapInit(sss_class* i_this) {
    /* Nonmatching */
    i_this->field_0x2B4 = new mDoExt_McaMorf(
        (J3DModelData*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BMD_SSS_HAND_e),
        NULL, NULL,
        (J3DAnmTransformKey*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e),
        J3DFrameCtrl::EMode_NONE, 1, 0, -1, TRUE, NULL, 0, 0x11020203
    );
    if (!i_this->field_0x2B4->getModel()) {
        return FALSE;
    }

    ResTIMG* tex = (ResTIMG*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BTI_SSS_e);
    if (!i_this->field_0x300.init(1, 10, tex, TRUE)) {
        return FALSE;
    }

    tex = (ResTIMG*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BTI_SSS_e);
    if (!i_this->field_0x454.init(1, 5, tex, TRUE)) {
        return FALSE;
    }

    return TRUE;
}

/* 000028A0-000028C0       .text daSss_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSss_solidHeapCB(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    return useHeapInit((sss_class*)i_actor);
}

/* 000028C0-00002BB4       .text daSss_Create__FP10fopAc_ac_c */
static cPhs_State daSss_Create(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    static dCcD_SrcSph tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 20.0f,
        }},
    };
    static dCcD_SrcSph bm_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_BOOMERANG | AT_TYPE_WIND,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 80.0f,
        }},
    };

    fopAcM_ct(i_actor, sss_class);

    sss_class* i_this = (sss_class*) i_actor;

    cPhs_State state = dComIfG_resLoad(&i_this->field_0x2AC, "Sss");
    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_actor, daSss_solidHeapCB, 0x3040)) {
            non_pos.x = 0;
            non_pos.y = 30000;
            non_pos.z = -20000;
            i_this->field_0x2B8 = fopAcM_GetParam(i_this);
            if (i_this->field_0x2B8 == 0xFF) {
                i_this->field_0x2B8 = 0;
            }
            if (i_this->field_0x2B8 != 1) {
                i_this->field_0x2B8 = 0x23;
            }
            i_this->field_0x2B9 = fopAcM_GetParam(i_this) >> 8;
            i_this->field_0x2BA = fopAcM_GetParam(i_this) >> 0x10;
            if (i_this->field_0x2BA == 0xFF) {
                i_this->field_0x2BA = false;
            }
            i_this->health = 2;
            i_this->field_0x2BC = cM_rndF(10000);
            i_this->field_0x51C.Init(0xFF, 0xFF, i_this);
            for (int i = 0; i < 3; i++) {
                i_this->field_0x558[i].Set(tg_sph_src);
                i_this->field_0x558[i].SetStts(&i_this->field_0x51C);
            }
            i_this->field_0x8DC.Set(bm_sph_src);
            i_this->field_0x8DC.SetStts(&i_this->field_0x51C);
            i_this->field_0x2C8 = i_this->current.pos;
            if (!i_this->field_0x2BA) {
                i_this->field_0x2C8.y += 230;
            }
            daSss_Execute(i_this);
        } else {
            state = cPhs_ERROR_e;
        }
    }
    return state;
}

static actor_method_class l_daSss_Method = {
    (process_method_func)daSss_Create,
    (process_method_func)daSss_Delete,
    (process_method_func)daSss_Execute,
    (process_method_func)daSss_IsDelete,
    (process_method_func)daSss_Draw,
};

actor_process_profile_definition g_profile_SSS = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_SSS_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sss_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_SSS_e,
    /* Actor SubMtd */ &l_daSss_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
