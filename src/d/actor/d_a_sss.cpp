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

f32 size_d[10] = {10.0f, 10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.5f};

cXyz non_pos;

/* 000000EC-000001F0       .text hand_draw__FP9sss_class */
void hand_draw(sss_class* i_this) {
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
    if (i_this->field_0x2B8 != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->eyePos, &i_this->tevStr);
        hand_draw(i_this);
    }
    return TRUE;
}

/* 00000248-000002C8       .text hand_close__FP9sss_class */
void hand_close(sss_class* i_this) {
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_TOJIRU_e);
    i_this->field_0x2B4->setAnm(anm, J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
}

/* 000002C8-00000348       .text hand_open__FP9sss_class */
void hand_open(sss_class* i_this) {
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e);
    i_this->field_0x2B4->setAnm(anm, J3DFrameCtrl::EMode_NONE, 1.0f, 1.0f, 0.0f, -1.0f, NULL);
}

/* 00000348-00000444       .text hand_mtx_set__FP9sss_class */
void hand_mtx_set(sss_class* i_this) {
    MtxTrans(i_this->field_0x2D4.x, i_this->field_0x2D4.y, i_this->field_0x2D4.z, false);
    mDoMtx_XrotM(*calc_mtx, i_this->field_0x2E0);
    mDoMtx_YrotM(*calc_mtx, i_this->field_0x2E2);
    mDoMtx_XrotM(*calc_mtx, REG12_S(1) - 0x4000);
    MtxScale(0.5f, REG0_F(0) + 0.2f, 0.5f, true);
    MtxTrans(0.0f, REG12_F(3) + -130.0f, 0.0f, true);
    J3DModel* temp = i_this->field_0x2B4->getModel();
    MTXCopy(*calc_mtx, temp->getBaseTRMtx());
}

/* 00000444-000004CC       .text control3__FP9sss_class */
void control3(sss_class* i_this) {
    sss_s* sp = i_this->field_0x33C;
    for (int i = 0; i < 10; i++) {
        f32 temp;
        temp = cM_ssin(i_this->field_0x2BC * 500 + i * 100) * 0.1f + 0.8f;
        sp++->field_0x18 = temp * size_d[i];
    }
}

/* 000004CC-00000804       .text control1__FP9sss_class */
void control1(sss_class* i_this) {
    static f32 g_d[10] = {50.0f, 50.0f, 35.0f, 25.0f, 15.0f, 9.0f, 6.0f, 6.0f, 6.0f, 6.0f};
    cXyz sp3C;
    cXyz sp30;
    cXyz sp24;
    cXyz sp18;

    int i;
    f32 f30;
    f32 f29;
    f32 f28;
    f32 f26;
    i_this->field_0x33C[0].field_0x00 = i_this->current.pos;
    sss_s* current = &i_this->field_0x33C[1];
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = i_this->field_0x2F0;
    MtxPosition(&sp3C, &sp24);
    sp3C.z = i_this->field_0x2E8;
    f32 f27 = i_this->field_0x2F4;
    for (i = 1; i < 9; i++, current++) {
        sp30.x = f27 * cM_ssin((i_this->field_0x2BC * (REG0_S(5) + 1100)) + i * (REG0_S(6) + 4000));
        sp30.y = g_d[i];
        sp30.z = f27 * cM_scos((i_this->field_0x2BC * (REG0_S(7) + 800)) + i * (REG0_S(8) + 4000));
        f30 = 1.0f;
        MtxPosition(&sp30, &sp18);
        f32 f2 = sp18.x * f30;
        f32 f1 = (current[0].field_0x00.x - current[-1].field_0x00.x);
        f29 = (sp24.x * f30) + f1 + f2;
        f2 = sp18.y * f30;
        f1 = (current[0].field_0x00.y - current[-1].field_0x00.y);
        f28 = sp24.y * f30 + f1 + f2;
        f2 = sp18.z * f30;
        f1 = (current[0].field_0x00.z - current[-1].field_0x00.z);
        f26 = sp24.z * f30 + f1 + f2;
        s16 y_atan;
        int xz_atan = cM_atan2s(f29, f26);
        y_atan = -cM_atan2s(f28, std::sqrtf(SQUARE(f29) + SQUARE(f26)));
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, xz_atan);
        mDoMtx_XrotM(*calc_mtx, y_atan);
        MtxPosition(&sp3C, &sp30);
        MtxPull();
        current[0].field_0x00 = current[-1].field_0x00 + sp30;
    }
}

/* 00000840-00000B0C       .text control2__FP9sss_class */
void control2(sss_class* i_this) {
    cXyz sp34;
    cXyz sp28;
    
    sp34.x = 0.0f;
    sp34.y = 0.0f;
    sp34.z = i_this->field_0x2E8;
    i_this->field_0x33C[9].field_0x00 = i_this->field_0x2C8;
    int r29;
    s16 r28;
    s16 r27;
    sss_s* r26 = &i_this->field_0x33C[8];
    for (r29 = 8; r29 >= 1; r29--, r26--) {
        f32 f29 = r26->field_0x00.x - r26[1].field_0x00.x;
        f32 f30 = r26->field_0x00.y - r26[1].field_0x00.y;
        f32 f28 = r26->field_0x00.z - r26[1].field_0x00.z;
        r27 = (s16)cM_atan2s(f29, f28);
        r28 = -cM_atan2s(f30, std::sqrtf(SQUARE(f29) + SQUARE(f28)));
        mDoMtx_YrotS(*calc_mtx, r27);
        mDoMtx_XrotM(*calc_mtx, r28);
        if (r29 == 8) {
            sp34.z = i_this->field_0x2E8 - 10.0f;
            if (sp34.z < 0.0f) {
                sp34.z = 0.0f;
            }
        } else {
            sp34.z = i_this->field_0x2E8;
        }
        MtxPosition(&sp34, &sp28);
        r26->field_0x00 = r26[1].field_0x00 + sp28;
    }
    i_this->field_0x2D4 = i_this->field_0x33C[9].field_0x00;
    sp34 = i_this->field_0x33C[8].field_0x00 - i_this->field_0x33C[9].field_0x00;
    i_this->field_0x2E0 = -cM_atan2s(sp34.y, sp34.z);
    i_this->field_0x2E2 = cM_atan2s(sp34.x, std::sqrtf(SQUARE(sp34.y) + SQUARE(sp34.z)));
    hand_mtx_set(i_this);
}

/* 00000B0C-00000F78       .text cut_control1__FP9sss_class */
void cut_control1(sss_class* i_this) {
    cXyz v1;
    cXyz v2;
    cXyz v3;
    int i;

    i_this->field_0x490[0].field_0x00 = i_this->current.pos;
    sss_s* current = &i_this->field_0x490[1];
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    v1.z = i_this->field_0x2FC;
    f32 x_val;
    f32 y_val;
    f32 z_val;
    f32 reg = REG0_F(18) + 50.0f;
    for (i = 1; i < 5; i++, current++) {
        v2.x = reg * cM_ssin((i_this->field_0x2BC * (REG0_S(5) + 4100)) + i * (REG0_S(6) + 10000));
        v2.y = REG0_F(17) + 50.0f;
        v2.z = reg * cM_scos((i_this->field_0x2BC * (REG0_S(7) + 4400)) + i * (REG0_S(8) + 10000));
        MtxPosition(&v2, &v3);
        x_val = v3.x + (current->field_0x00.x - current[-1].field_0x00.x);
        y_val = v3.y + (current->field_0x00.y - current[-1].field_0x00.y);
        z_val = v3.z + (current->field_0x00.z - current[-1].field_0x00.z);
        s16 y_atan;
        int xz_atan = cM_atan2s(x_val, z_val);
        y_atan = -cM_atan2s(y_val, std::sqrtf(SQUARE(x_val) + SQUARE(z_val)));
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, xz_atan);
        mDoMtx_XrotM(*calc_mtx, y_atan);
        MtxPosition(&v1, &v2);
        MtxPull();
        current->field_0x00 = current[-1].field_0x00 + v2;
    }
    if (i_this->field_0xA10 == NULL && (s8)i_this->field_0xA18 != 0) {
        i_this->field_0xA10 = dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, &i_this->field_0x490[4].field_0x00);
        i_this->field_0x2C2[1] = 60;
    }
    if (i_this->field_0xA10) {
        v1 = i_this->field_0x490[4].field_0x00 - i_this->field_0x490[3].field_0x00;
        s16 rot_x, rot_y, rot_z;
        rot_y = (s16)cM_atan2s(v1.x, v1.z);
        rot_x = -cM_atan2s(v1.y, std::sqrtf(SQUARE(v1.x) + SQUARE(v1.z)));
        rot_z = 0;
        f32 trans_x, trans_y, trans_z;
        trans_x = i_this->field_0x490[4].field_0x00.x;
        trans_z = i_this->field_0x490[4].field_0x00.z;
        trans_y = i_this->field_0x490[4].field_0x00.y;
        i_this->field_0xA10->setGlobalTranslation(trans_x, trans_y, trans_z);
        i_this->field_0xA10->setGlobalRotation(JGeometry::TVec3<s16>(rot_x, rot_y, rot_z));
        if (i_this->field_0x2C2[1] == 1) {
            i_this->field_0xA10->becomeInvalidEmitter();
            i_this->field_0xA10 = NULL;
        }
    }
}

/* 00000F78-000014F4       .text cut_control2__FP9sss_class */
void cut_control2(sss_class* i_this) {
    cXyz sp60;
    cXyz sp54;
    cXyz sp48;
    sp60.x = 0.0f;
    sp60.y = 0.0f;
    sp60.z = i_this->field_0x2E8;
    i_this->field_0x33C[9].field_0x00 = i_this->field_0x2C8;
    int i;
    sss_s* current = &i_this->field_0x33C[8];
    f32 x_val;
    f32 f1;
    f32 z_val;
    f32 f28;
    f32 f27 = i_this->field_0x2F4;
    f32 f0;
    for (i = 8; i >= 0; i--, current--) {
        sp48.x = f27 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 2500) + i * (REG0_S(6) + 3000));
        sp48.y = f27 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 2950) + i * (REG0_S(6) + 4000));
        sp48.z = f27 * cM_scos(i_this->field_0x2BC * (REG0_S(7) + 2800) + i * (REG0_S(8) + 3500));
        x_val = sp48.x + (current->field_0x00.x - current[1].field_0x00.x);
        f1 = current->field_0x00.y - 10.0f + sp48.y;
        f0 = i_this->field_0x2F8 + 5.0f;
        if (f1 < f0) {
            f1 = f0;
        }
        f28 = f1 - current[1].field_0x00.y;
        z_val = sp48.z + (current->field_0x00.z - current[1].field_0x00.z);
        s16 y_atan;
        int xz_atan = cM_atan2s(x_val, z_val);
        y_atan = -cM_atan2s(f28, std::sqrtf(SQUARE(x_val) + SQUARE(z_val)));
        mDoMtx_YrotS(*calc_mtx, xz_atan);
        mDoMtx_XrotM(*calc_mtx, y_atan);
        if (i == 8) {
            sp60.z = i_this->field_0x2E8 - 10.0f;
            if (sp60.z < 0.0f) {
                sp60.z = 0.0f;
            }
        } else {
            sp60.z = i_this->field_0x2E8;
        }
        MtxPosition(&sp60, &sp54);
        current->field_0x00 = current[1].field_0x00 + sp54;
    }
    i_this->field_0x2D4 = i_this->field_0x33C[9].field_0x00;
    sp60 = i_this->field_0x33C[8].field_0x00 - i_this->field_0x33C[9].field_0x00;
    i_this->field_0x2E0 = -cM_atan2s(sp60.y, sp60.z);
    i_this->field_0x2E2 = cM_atan2s(sp60.x, std::sqrtf(SQUARE(sp60.y) + SQUARE(sp60.z)));
    hand_mtx_set(i_this);
    if (!i_this->field_0xA14 && (s8)i_this->field_0xA18 != 0) {
        i_this->field_0xA14 = dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, &i_this->field_0x33C[0].field_0x00);
    }
    if (i_this->field_0xA14) {
        sp60 = i_this->field_0x33C[0].field_0x00 - i_this->field_0x33C[1].field_0x00;
        s16 rot_x;
        s16 r21;
        s16 rot_z;
        r21 = (s16)cM_atan2s(sp60.x, sp60.z);
        rot_x = -cM_atan2s(sp60.y, std::sqrtf(SQUARE(sp60.x) + SQUARE(sp60.z)));
        rot_z = 0;
        f32 trans_x;
        f32 trans_y;
        f32 trans_z;
        trans_x = i_this->field_0x33C[0].field_0x00.x;
        trans_z = i_this->field_0x33C[0].field_0x00.z;
        trans_y = i_this->field_0x33C[0].field_0x00.y;
        i_this->field_0xA14->setGlobalTranslation(trans_x, trans_y, trans_z);
        i_this->field_0xA14->setGlobalRotation(JGeometry::TVec3<s16>(rot_x, r21, rot_z));
        if (i_this->field_0x2C2[1] == 1) {
            i_this->field_0xA14->becomeInvalidEmitter();
            i_this->field_0xA14 = NULL;
            i_this->field_0xA18 = false;
        }
    }
}

/* 000014F4-00002614       .text hand_move__FP9sss_class */
void hand_move(sss_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*) i_this;
    fopAc_ac_c* a_player = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*) a_player;
    daPy_lk_c* link = (daPy_lk_c*) dComIfGp_getLinkPlayer();
    f32 speedRatio;
    f32 f6;
    f32 f28;
    f32 f27;
    f32 target;
    f32 maxSpeed;
    f32 f24;
    f32 f5;
    f32 f1;
    
    bool b1;
    bool b2;
    cXyz sp8C;
    cXyz sp80;
    cXyz sp74;
    f32 f4;

    dBgS_GndChk gnd_chk;
    gnd_chk.MaskNormalGrp();
    b1 = false;
    b2 = false;
    speedRatio = 0.1f;
    f6 = 8.0f;
    f28 = 0.1f;
    f27 = 0.0f;
    target = 30.0f;
    maxSpeed = 1.0f;
    f24 = 0.0f;
    f4 = fopAcM_searchActorDistance(a_this, dComIfGp_getPlayer(0));
    f1 = 5.0f;
    if (i_this->field_0x2B9 != 0xFF) {
        f5 = i_this->field_0x2B9 * 10.0f;
    } else {
        f5 = 1000.0f;
    }
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    s8 b = 0;
    switch (i_this->field_0x2C0) {
        case 0: {
            sp74 = i_this->current.pos;
            target = 0.0f;
            maxSpeed = 0.5f;
            f24 = -20.0f;
            if (!i_this->field_0x2C2[0]) {
                if (i_this->field_0x2BA) {
                    if (dComIfGs_isSwitch(i_this->field_0x2BA, fopAcM_GetRoomNo(a_this)) || REG0_S(0)) {
                        i_this->field_0x2C0 = 1;
                        i_this->field_0x2C2[0] = 30;
                        hand_open(i_this);
                        b = 1;
                    }
                } else {
                    if (f4 < f5) {
                        i_this->field_0x2C0 = 1;
                        i_this->field_0x2C2[0] = 30;
                        hand_open(i_this);
                        b = 1;
                    }
                }
            }
            if (std::abs(i_this->field_0x2C8.y - i_this->current.pos.y) < 5.0f && b) {
                if (i_this->field_0x2B8 == 1) {
                    fopAcM_seStart(a_this, JA_SE_OBJ_SVINE_OUT_WATER, 0);
                } else {
                    fopAcM_seStart(a_this, JA_SE_OBJ_SVINE_OUT, 0);
                }
            }
            break;
        }
        case 1:
            sp8C.x = (REG0_F(13) + 50.0f) * cM_ssin(i_this->field_0x2BC * 600);
            sp8C.y = 250.0f;
            sp8C.z = (REG0_F(13) + 50.0f) * cM_ssin(i_this->field_0x2BC * 700);
            MtxPosition(&sp8C, &sp80);
            sp74 = i_this->current.pos + sp80;
            if (i_this->field_0x2C2[0] == 0 && f4 < REG0_F(14) + 300.0f) {
                i_this->field_0x2C0 = 2;
            }
            if (f4 > (f5 + 100.0f)) {
                i_this->field_0x2C0 = 0;
            }
            break;
        case 2:
            f6 = 15.0f;
            f27 = 10.0f;
            f28 = 0.5f;

            b1 = true;
            sp74 = a_player->current.pos;
            sp74.y += 70.0f;
            if (f4 > REG0_F(14) + 450.0f) {
                i_this->field_0x2C0 = 1;
                i_this->speedF = 0.0f;
            }
            sp8C = sp74 - i_this->field_0x2C8;
            if (sp8C.abs() < 20.0f && player == link) {
                i_this->field_0x2C0 = 3;
                hand_close(i_this);
                fopAcM_seStart(a_this, JA_SE_OBJ_SVINE_GRASP, 0);
            } else {
                break;
            }
            // Fall-through
        case 3:
            player->onNoResetFlg1(daPy_lk_c::daPyFlg1_VINE_CATCH);
            player->setFace(daPy_lk_c::daPyFace_TIYAYA);
            if (dComIfGs_getMagic()) {
                g_dComIfG_gameInfo.play.field_0x4965 |= 1;
                fopAcM_seStart(a_this, JA_SE_OBJ_ATK_VINE_MP_SUCK, 0);
                if ((i_this->field_0x2BC & 0x1F) == 0) {
                    dComIfGp_setItemMagicCount(-1);
                }
            }
            {
                f32 temp = REG6_F(2) + 400.0f;
                if (f4 > temp) {
                    f32 f5 = (REG6_F(0) + 0.1f) * (f4 - temp);
                    if (f5 > REG6_F(1) + 100.0f) {
                        f5 = REG6_F(1) + 100.0f;
                    }
                    s16 temp = fopAcM_searchActorAngleY(a_this, dComIfGp_getPlayer(0));
                    player->setOutPower(f5, temp + 0x8000, 0);
                }
            }
            sp74 = player->current.pos;
            sp74.y += 70.0f;
            f6 = 200.0f;
            speedRatio = 1.0f;
            f28 = 5.0f;
            i_this->field_0x2F4 = REG0_F(11) + 10.0f;
            if (f4 > 800.0f) {
                i_this->field_0x2C0 = 1;
                i_this->speedF = 30.0f;
                hand_open(i_this);
            }
            break;
        case 5:
            f1 = 50.0f;
            i_this->field_0x2F4 = 50.0f;
            b2 = true;
            target = 25.0f;
            maxSpeed = 1.0f;
            i_this->field_0x2C8 += i_this->speed;
            i_this->speed.y -= 3.0f;
            i_this->field_0x2C2[2] = 5;
            {
                JGeometry::TVec3<f32> temp = i_this->field_0x2C8;
                temp.y += 200.0f;
                gnd_chk.m_pos = temp;
            }
            i_this->field_0x2F8 = dComIfG_Bgsp()->GroundCross(&gnd_chk);
            if (i_this->field_0x2F8 == -1e9f || i_this->field_0x2C8.y <= i_this->field_0x2F8 + 10.0f) {
                i_this->field_0x2C8.y = i_this->field_0x2F8 + 10.0f;
                i_this->field_0x2C2[0] = 100;
                i_this->field_0x2C0 = 6;
            }
            break;
        case 6:
            b2 = true;
            f1 = 0.0f;
            i_this->field_0x2C2[2] = 10;
            if (i_this->field_0x2C2[0] < 40) {
                target = f1;
                maxSpeed = 1;
                i_this->field_0x2C8.y -= 2.0f;
            }
            if (i_this->field_0x2C2[0] == 0) {
                i_this->field_0x2C8 = i_this->current.pos;
                i_this->field_0x2C0 = 0;
                i_this->field_0x2E8 = 0.0f;
                i_this->field_0x2FC = 0.0f;
            }
    }
    cLib_addCalc2(&i_this->field_0x2E8, target, 0.5f, maxSpeed);
    cLib_addCalc2(&i_this->field_0x2F0, f27, 1.0f, 0.2f);
    cLib_addCalc2(&i_this->field_0x2F4, f1, 1.0f, 1.5f);
    if (!b2) {
        cLib_addCalc2(&i_this->speedF, f6, 1.0f, f28);
        if (i_this->field_0xA08 > 1.0f && i_this->field_0x2C0 != 3) {
            mDoMtx_YrotS(*calc_mtx, i_this->field_0xA0C);
            sp8C.x = 0.0f;
            sp8C.y = REG6_F(9) + 100.0f;
            sp8C.z = i_this->field_0xA08;
            MtxPosition(&sp8C, &sp80);
            sp74 = i_this->current.pos + sp80;
            speedRatio = 0.1f;
            i_this->speedF = i_this->field_0xA08 * 0.2f;
            if (i_this->speedF > REG6_F(8) + 30.0f) {
                i_this->speedF = REG6_F(8) + 30.0f;
            }
        }
        cLib_addCalc0(&i_this->field_0xA08, 1.0f, REG6_F(7) + 5.0f);
        cLib_addCalc2(&i_this->field_0x2C8.x, sp74.x, speedRatio, i_this->speedF);
        cLib_addCalc2(&i_this->field_0x2C8.y, sp74.y, speedRatio, i_this->speedF);
        cLib_addCalc2(&i_this->field_0x2C8.z, sp74.z, speedRatio, i_this->speedF);
        cLib_addCalc2(&i_this->current.pos.y, i_this->home.pos.y + f24, 0.5f, 0.5f);
        if (b1 && i_this->current.angle.x == 0) {
            cLib_addCalcAngleS2(&i_this->current.angle.y, fopAcM_searchActorAngleY(a_this, dComIfGp_getPlayer(0)), 16, 2048);
        }
        control1(i_this);
        control2(i_this);
    } else {
        cut_control1(i_this);
        cut_control2(i_this);
        sss_s* sp = i_this->field_0x490;
        cXyz* segments = i_this->field_0x454.getPos(0);
        u8* sizes = i_this->field_0x454.getSize(0);
        for (int i = 0; i < 5; i++, sp++, segments++, sizes++) {
            *segments = sp->field_0x00;
            *sizes = sp->field_0x18;
        }
        cLib_addCalc0(&i_this->field_0x2FC, 1.0f, REG0_F(1) + 1.0f);
    }
    control3(i_this);
    i_this->field_0x2B4->play(NULL, 0, 0);
    sss_s* sp = i_this->field_0x33C;
    cXyz* segments = i_this->field_0x300.getPos(0);
    u8* sizes = i_this->field_0x300.getSize(0);
    for (int i = 0; i < 10; i++, sp++, segments++, sizes++) {
        *segments = sp->field_0x00;
        *sizes = sp->field_0x18;
    }
    cXyz* r22 = i_this->field_0x300.getPos(0);
    i_this->eyePos = r22[5];
    i_this->attention_info.position = i_this->eyePos;
    i_this->field_0x51C.Move();
    if (!b2) {
        i_this->field_0x8DC.SetC(i_this->eyePos);
    } else {
        i_this->field_0x8DC.SetC(non_pos);
    }
    u8 u1 = 0;
    dComIfG_Ccsp()->Set(&i_this->field_0x8DC);
    for (int i = 0; i < ARRAY_SSIZE(i_this->field_0x558); i++) {
        int r4 = (i_this->field_0x2BC & 3) + i * 2;
        r4 = r4 % 10;
        cXyz sp68 = r22[r4];
        if (!b2) {
            i_this->field_0x558[i].SetC(sp68);
        } else {
            i_this->field_0x558[i].SetC(non_pos);
        }
        if (i_this->field_0x2C0 == 3) {
            i_this->field_0x558[i].OffCoSPrmBit(1);
        } else {
            i_this->field_0x558[i].OnCoSPrmBit(1);
        }
        dComIfG_Ccsp()->Set(&i_this->field_0x558[i]);
    }
    for (s32 i = 0; i < 3; i++) {
        if (i_this->field_0x558[i].ChkTgHit()) {
            u1 = i + 1;
            break;
        }
    }
    if ((u1 || i_this->field_0x8DC.ChkTgHit() != 0) && i_this->field_0x2C2[2] == 0) {
        CcAtInfo at_info;
        at_info.pParticlePos = NULL;
        i_this->field_0x2C2[2] = 20;
        u8 r3 = u1;
        if (!r3) {
            at_info.mpObj = i_this->field_0x8DC.GetTgHitObj();
            at_info.pParticlePos = i_this->field_0x8DC.GetTgHitPosP();
            at_power_check(&at_info);
            if (at_info.mResultingAttackType == 8) {
                i_this->field_0xA08 = REG6_F(6) + 300.0f;
                i_this->field_0xA0C = fopAcM_searchActorAngleY(a_this, dComIfGp_getPlayer(0)) + 0x8000;
                return;
            }
        } else {
            dCcD_GObjInf* objInf = &i_this->field_0x558[r3 - 1];
            at_info.mpObj = objInf->GetTgHitObj();
            at_info.pParticlePos = objInf->GetTgHitPosP();
        }
        fopAcM_seStart(a_this, JA_SE_LK_LAST_HIT, 0);
        fopAcM_seStart(a_this, JA_SE_OBJ_SVINE_CRASH, 0);
        i_this->field_0x2C0 = 5;
        i_this->speed.x = cM_rndFX(10.0f);
        i_this->speed.y = cM_rndF(10.0f) + 30.0f;
        i_this->speed.z = cM_rndFX(10.0f);
        cXyz scale(0.3f, 0.3f, 0.3f);
        dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, &i_this->eyePos, NULL, &scale);
        i_this->field_0xA18 = true;
        sss_s* r18 = i_this->field_0x33C;
        sss_s* r19 = i_this->field_0x490;
        for (int i = 0; i < 5; i++, r18++, r19++) {
            r19[0].field_0x00 = r18[0].field_0x00;
            r19[0].field_0x18 = r18[0].field_0x18;
            if (i == 4) {
                cXyz temp = r19[0].field_0x00 - r19[-1].field_0x00;
                i_this->field_0x2FC = (REG0_F(2) + 1.5f) * temp.abs();
            }
        }
        hand_open(i_this);
    }
    return;
}

/* 00002614-00002618       .text hand_main__FP9sss_class */
void hand_main(sss_class*) {
}

/* 00002618-0000269C       .text daSss_Execute__FP9sss_class */
static BOOL daSss_Execute(sss_class* i_this) {
    i_this->field_0x2BC += 1;
    for (int i = 0; i < 2; i++) {
        if (i_this->field_0x2C2[i] != '\0') {
            i_this->field_0x2C2[i] -= 1;
        }
    }
    if (i_this->field_0x2C2[2] != '\0') {
        i_this->field_0x2C2[2] -= 1;
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
    dComIfG_resDelete(&i_this->field_0x2AC, "Sss");
    JPABaseEmitter* emitter = i_this->field_0xA10;
    if (emitter) {
        emitter->becomeInvalidEmitter();
    }
    emitter = i_this->field_0xA14;
    if (emitter) {
        emitter->becomeInvalidEmitter();
    }
    return TRUE;
}

/* 00002720-000028A0       .text useHeapInit__FP9sss_class */
BOOL useHeapInit(sss_class* i_this) {
    i_this->field_0x2B4 = new mDoExt_McaMorf(
        (J3DModelData*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BMD_SSS_HAND_e),
        NULL, NULL,
        (J3DAnmTransformKey*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e),
        J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, TRUE, NULL, 0, 0x11020203
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
    return useHeapInit((sss_class*)i_actor);
}

/* 000028C0-00002BB4       .text daSss_Create__FP10fopAc_ac_c */
static cPhs_State daSss_Create(fopAc_ac_c* i_actor) {
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
            non_pos.x = 0.0f;
            non_pos.y = 30000.0f;
            non_pos.z = -20000.0f;
            i_this->field_0x2B8 = fopAcM_GetParam(i_this);
            if (i_this->field_0x2B8 == 0xFF) {
                i_this->field_0x2B8 = 0;
            }
            if (i_this->field_0x2B8 != 1) {
                i_this->field_0x2B8 = 0x23;
            }
            i_this->field_0x2B9 = fopAcM_GetParam(i_this) >> 8;
            i_this->field_0x2BA = fopAcM_GetParam(i_this) >> 16;
            if (i_this->field_0x2BA == 0xFF) {
                i_this->field_0x2BA = false;
            }
            i_this->health = 2;
            i_this->field_0x2BC = cM_rndF(10000.0f);
            i_this->field_0x51C.Init(0xFF, 0xFF, i_this);
            for (int i = 0; i < 3; i++) {
                i_this->field_0x558[i].Set(tg_sph_src);
                i_this->field_0x558[i].SetStts(&i_this->field_0x51C);
            }
            i_this->field_0x8DC.Set(bm_sph_src);
            i_this->field_0x8DC.SetStts(&i_this->field_0x51C);
            i_this->field_0x2C8 = i_this->current.pos;
            if (!i_this->field_0x2BA) {
                i_this->field_0x2C8.y += 230.0f;
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
