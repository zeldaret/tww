/**
 * d_a_bdk.cpp
 * Boss - Helmaroc King / 戦闘用大怪鳥 (Giant monstrous bird for battle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/res/res_bdk.h"
#include "d/actor/d_a_bdk.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_cc_d.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_jnt_hit.h"
#include "d/d_snap.h"
#include "d/d_s_play.h"
#include "d/d_particle_name.h"
#include "d/d_priority.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "JSystem/JUtility/JUTReport.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#if VERSION > VERSION_DEMO
#include "m_Do/m_Do_graphic.h"
#endif

enum ActionStatus {
    ACTION_FLY = 0,
    ACTION_UP_FLY = 1,
    ACTION_LANDING = 2,
    ACTION_WAIT = 3,
    ACTION_JUMP = 4,
    ACTION_KUTI_ATTACK = 5,
    ACTION_JIDA_ATTACK = 6,
    ACTION_FLY_ATTACK = 7,
    ACTION_WIND_ATTACK = 8,
    ACTION_KAMEN_DEMO = 9,
    ACTION_END = 0xA,
    ACTION_START = 0xF,
    ACTION_T_FLY = 0x64,
    ACTION_T_LANDING = 0x65,
    ACTION_T_LASTATTACK = 0x66,
    ACTION_T_DOWN = 0x67,
    ACTION_AFTER_FIGHT = 0x6E,
};

static cXyz center_pos;
static cXyz center_pos2;
static cXyz wind_se_pos;
static daBdk_HIO_c l_HIO;
static cXyz foot_eff_pos[2];

/* 000000EC-0000015C       .text __ct__11daBdk_HIO_cFv */
daBdk_HIO_c::daBdk_HIO_c() {
    mNo = -1;
    m005 = 0;
    m006 = 0;
    m008 = 1.0f;
    m00C = 4.0f;
    m010 = 1.5f;
    m014 = 0;
    m018 = 20.0f;
    m01C = 2.0f;
    m020 = 60.0f;
    m024 = 100.0f;
    m028 = 0x2D0;
}

/* 0000015C-000001A8       .text kamome_delete_sub__FPvPv */
void* kamome_delete_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_KAMOME) {
        fopAcM_delete(static_cast<fopAc_ac_c*>(param_1));
    }
    return NULL;
}

/* 000001A8-000001F4       .text kui_delete_sub__FPvPv */
void* kui_delete_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_KUI) {
        fopAcM_delete(static_cast<fopAc_ac_c*>(param_1));
    }
    return NULL;
}

/* 000001F4-00000240       .text ep_delete_sub__FPvPv */
void* ep_delete_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_EP) {
        fopAcM_delete(static_cast<fopAc_ac_c*>(param_1));
    }
    return NULL;
}

/* 00000240-0000028C       .text dk_delete_sub__FPvPv */
void* dk_delete_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_DK) {
        fopAcM_delete(static_cast<fopAc_ac_c*>(param_1));
    }
    return NULL;
}

/* 0000028C-000002E8       .text obj_delete_sub__FPvPv */
void* obj_delete_sub(void* param_1, void*) {
    fopAc_ac_c* actor = static_cast<fopAc_ac_c*>(param_1);
    if (fopAc_IsActor(actor) && fopAcM_GetName(actor) == PROC_BDKOBJ
    && (fopAcM_GetParam(actor) & 0xF) >= 2) {
        fopAcM_delete(actor);
    }
    return NULL;
}

/* 000002E8-00000334       .text sea_delete_sub__FPvPv */
void* sea_delete_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_Obj_Tide) {
        fopAcM_delete(static_cast<fopAc_ac_c*>(param_1));
    }
    return NULL;
}

/* 00000334-00000380       .text bk_delete_sub__FPvPv */
void* bk_delete_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_BK) {
        fopAcM_delete(static_cast<fopAc_ac_c*>(param_1));
    }
    return NULL;
}

/* 00000380-000003CC       .text boko_delete_sub__FPvPv */
void* boko_delete_sub(void* param_1, void*) {
    if (fopAc_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_BOKO) {
        fopAcM_delete(static_cast<fopAc_ac_c*>(param_1));
    }
    return NULL;
}

/* 000003CC-00000424       .text obj2_delete_sub__FPvPv */
void* obj2_delete_sub(void* param_1, void*) {
    fopAc_ac_c* actor = static_cast<fopAc_ac_c*>(param_1);
    if (fopAc_IsActor(actor) && fopAcM_GetName(actor) == PROC_BDKOBJ
    && actor->model == NULL) {
        fopAcM_delete(actor);
    }
    return NULL;
}

/* 00000424-000004D4       .text land_area_check__FP4cXyzf */
BOOL land_area_check(cXyz* param_1, float param_2) {
    f32 val1 = param_1->x - 3600.0f;
    f32 val2 = param_1->z - (-3800.0f);
    if ((std::sqrtf(val1 * val1 + val2 * val2) < param_2)) {
        return TRUE;
    }
    return FALSE;
}

/* 000004D4-0000073C       .text eff_hane_set__FP9bdk_classP4cXyziSc */
void eff_hane_set(bdk_class* i_this, cXyz* offset, int param_3, signed char param_4) {
    fopAc_ac_c* actor = &i_this->actor;
    bdk_eff_s* eff;
    for (s32 iVar4 = 0, i = 0; i < (s32)(ARRAY_SIZE(i_this->m261C) - 1); i++) {
        if (iVar4 >= param_3) {
            break;
        }
        eff = &i_this->m261C[i_this->m261A];
        i_this->m261A++;
        if (i_this->m261A > 0x26) {
            i_this->m261A = 0;
        }

        eff->m000 = 1;
        eff->m03E = 2000;
        eff->m001 = 0;
        eff->m040 = 0;
        eff->m02C = 1.0f;

        eff->m004.x = offset->x;
        eff->m004.y = offset->y;
        eff->m004.z = offset->z;

        eff->m024 = 0.0f;
        eff->m03C = cM_rndF(65536.0f);
        eff->m036.z = cM_rndFX(1200.0f + REG8_F(10));
        eff->m036.x = cM_rndFX(800.0f + REG8_F(16));
        iVar4++;

        if (param_4 > 0) {
            eff->m030.y = actor->shape_angle.y + (s16)cM_rndFX(5000.0f);
            eff->m020 = REG8_F(8) + (cM_rndF(10.0f) + 20.0f);
            eff->m01C = REG8_F(9) + (cM_rndFX(5.0f) - 10.0f);
            eff->m040 = cM_rndF(20.0f) + 20.0f;
        } else {
            if (param_4 < 0) {
                eff->m020 = cM_rndF(10.0f);
            } else {
                eff->m020 = REG8_F(8) + (cM_rndF(5.0f) + 5.0f);
            }
            eff->m01C = REG8_F(9) + (cM_rndF(5.0f) + 5.0f);
            eff->m030.y = cM_rndF(65536.0f);
        }
    }
}

/* 0000073C-000007A4       .text pl_view_check__FP9bdk_class */
BOOL pl_view_check(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 angle = fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0));
    angle = actor->current.angle.y - angle;
    if (angle < 0) {
        angle = -angle;
    }
    if ((u16)angle < 0x6000) {
        return TRUE;
    }
    return FALSE;
}

/* 000007A4-000008F8       .text anm_init__FP9bdk_classifUcfiUc */
void anm_init(bdk_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx, unsigned char param7) {
    if (param7 == 0) {
        i_this->m2588 = bckFileIdx;
        i_this->m258C = soundFileIdx;
        i_this->m2590 = loopMode;
        i_this->m2591 = 0;
    } else {
        i_this->m2591 = 1;
    }

    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bdk", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            dComIfG_getObjectRes("Bdk", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bdk", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            NULL
        );
    }
}

/* 000008F8-00000B10       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jnt_no = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bdk_class* bdk = (bdk_class*)model->getUserArea();
        if (bdk != NULL) {
            MTXCopy(model->getAnmMtx(jnt_no), *calc_mtx);
            if (jnt_no == 0x17) { // j_dk_kubi1 joint
                cMtx_YrotM(*calc_mtx, bdk->mF14);
                cMtx_XrotM(*calc_mtx, bdk->mF12);
                model->setAnmMtx(jnt_no, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            } else if (jnt_no >= 0x1F && 0x24 >= jnt_no) { // j_dk_tosaka_A1 to j_dk_tosaka_B2 joints
                if (jnt_no >= 0x23) { // j_dk_tosaka_B1 and j_dk_tosaka_B2 joints
                    cMtx_YrotM(*calc_mtx, bdk->m112E + bdk->m1120 + bdk->m1124);
                    cMtx_ZrotM(*calc_mtx, bdk->m112C + bdk->m1122 + bdk->m1126);
                } else {
                    cMtx_YrotM(*calc_mtx, -(bdk->m112E + bdk->m1120 + bdk->m1128));
                    cMtx_ZrotM(*calc_mtx, -(bdk->m112C + bdk->m1122 + bdk->m112A));
                }
                model->setAnmMtx(jnt_no, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            } else {
                cXyz offset;
                jnt_no = (jnt_no - 0x3A) / 2;

                offset.z = 0;
                offset.y = 0;
                offset.x = 0;
                MtxPosition(&offset, &bdk->m300[jnt_no].m0150[1]);
                offset.x = -10.0f;
                MtxPosition(&offset, &bdk->m300[jnt_no].m0150[0]);
            }
        }
    }
    return TRUE;
}

/* 00000B4C-00001008       .text tail_control__FP9bdk_classP10bdk_tail_s */
void tail_control(bdk_class* i_this, bdk_tail_s* tail) {
    cXyz vec1, vec2, vec3;
    f32 fVar1, fVar2;

    vec1 = tail->m0150[1] - tail->m0150[0];
    tail->m0168.y = cM_atan2s(vec1.x, vec1.z);
    tail->m0168.x = -cM_atan2s(vec1.y, std::sqrtf(vec1.x * vec1.x + vec1.z * vec1.z));

    vec1.x = 0.0f;
    vec1.y = 0.0f;
    vec1.z = 30.0f;

    cMtx_YrotS(*calc_mtx, tail->m0168.y);
    cMtx_XrotM(*calc_mtx, tail->m0168.x);
    MtxPosition(&vec1, &tail->m0170);

    tail->m024[0] = tail->m0150[1];

    s32 i;
    s16 sVar1, sVar2;
    cXyz* array_24 = &tail->m024[1];
    csXyz* array_9c = &tail->m09C[1];
    cXyz* array_d8 = &tail->m0D8[1];

    fVar2 = i_this->mAcch.GetGroundH() + 5.0f;
    if (i_this->mAction == ACTION_START) {
        fVar2 = -30000.0f;
    }

    for(i = 1; i < (s32)ARRAY_SIZE(tail->m024); i++, array_24++, array_9c++, array_d8++) {
        fVar1 = 1.0f - (i - 1) * 0.1f;
        vec3.x =  array_d8->x + tail->m0170.x * fVar1;
        vec3.y  = array_d8->y + tail->m0170.y * fVar1;
        vec3.z  = array_d8->z + tail->m0170.z * fVar1;

        f32 fVar3 = array_24->y + vec3.y;
        if (fVar3 < fVar2) {
            fVar3 = fVar2;
        }
        fVar1 = fVar3 - array_24[-1].y;
        f32 dx = vec3.x + (array_24->x - array_24[-1].x);
        f32 dz = vec3.z + (array_24->z - array_24[-1].z);
        sVar2 = (s16)cM_atan2s(dx, dz);
        sVar1 = -cM_atan2s(fVar1, std::sqrtf(dx * dx + dz * dz));

        array_9c[-1].y = sVar2;
        array_9c[-1].x = sVar1;

        vec1.x = 0.0f;
        vec1.y = 0.0f;
        vec1.z = 2.0f * (20.0f * (0.25f + 0.03f * i)) * l_HIO.m00C * l_HIO.m010;

        cMtx_YrotS(*calc_mtx, sVar2);
        cMtx_XrotM(*calc_mtx, sVar1);
        MtxPosition(&vec1, &vec2);

        array_d8->x = array_24->x;
        array_d8->y = array_24->y;
        array_d8->z = array_24->z;

        array_24->x = array_24[-1].x + vec2.x;
        array_24->y = array_24[-1].y + vec2.y;
        array_24->z = array_24[-1].z + vec2.z;

        f32 div = 0.77000004f;
        array_d8->x = (array_24->x - array_d8->x) * div;
        array_d8->y = (array_24->y - array_d8->y) * div;
        array_d8->z = (array_24->z - array_d8->z) * div;
    }
}

static f32 tial_scale[] = {
    0.25f, 0.275f, 0.2875f, 0.3f, 0.325f, 0.375f, 0.4625f, 0.575f, 0.8f,
};
/* 00001008-00001120       .text tail_draw__FP9bdk_classP10bdk_tail_s */
void tail_draw(bdk_class* i_this, bdk_tail_s* tail) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m2F6 != 0) {
        i_this->m2F6--;
    } else {
        cXyz* pos = tail->m024;
        csXyz* angle = tail->m09C;
        for(s32 i = 0; i < 9; pos++, angle++, i++) {
            f32 scale = l_HIO.m00C * tial_scale[i];
            MtxTrans(pos->x, pos->y, pos->z, FALSE);
            MtxScale(scale, scale, scale, TRUE);
            cMtx_YrotM(*calc_mtx, angle->y);
            cMtx_XrotM(*calc_mtx, angle->x);

            J3DModel* model = tail->m000[i];
            model->setBaseTRMtx(*calc_mtx);
            g_env_light.setLightTevColorType(model, &actor->tevStr);
            mDoExt_modelUpdateDL(model);
        }
    }
}

/* 00001120-000011A0       .text kamen_break_draw__FP9bdk_class */
void kamen_break_draw(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m8FC); i++) {
        if (i_this->m90C[i] != 0) {
            model = i_this->m8FC[i];
            g_env_light.setLightTevColorType(model, &actor->tevStr);
            mDoExt_modelUpdateDL(model);
        }
    }
}

/* 000011A0-00001278       .text obj_draw__FP9bdk_class */
void obj_draw(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    g_env_light.settingTevStruct(TEV_TYPE_BG3, &actor->current.pos, &i_this->m6224);
    J3DModel* model = i_this->mp62D8;
    g_env_light.setLightTevColorType(model, &i_this->m6224);
    mDoExt_modelUpdateDL(model);

    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mp6310); i++) {
        model = i_this->mp6310[i];
        g_env_light.setLightTevColorType(model, &i_this->m6224);
        dComIfGd_setListBG();
        mDoExt_modelUpdateDL(model);
        dComIfGd_setList();
    }
}
static s32 kamen_pt[] = {0, 1, 2, 3};

/* 00001278-00001488       .text kamen_draw__FP9bdk_class */
void kamen_draw(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* kamen_model = i_this->mp8F0;
    f32 fVar1 = i_this->m2FA * (REG0_F(14) + 150.0f);
    s16 sVar1 = fVar1 * cM_ssin(i_this->m2C4 * 0x5100);
    s16 sVar2 = fVar1 * cM_scos(i_this->m2C4 * 0x4300);
    f32 fVar3 = 1.0f;
    if (i_this->m2FA & 2) {
        fVar1 = 1.20f;
        fVar3 = REG8_F(18) + 1.20f;
    }

    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x18), *calc_mtx); // j_dk_atama1 joint
    cMtx_YrotM(*calc_mtx, sVar1 + 0x4000);
    cMtx_ZrotM(*calc_mtx, sVar2 + -0x4000);
    MtxTrans(0.0f, 40.0f, 125.0f, TRUE);
    MtxScale(fVar3, fVar3, fVar3, TRUE);
    kamen_model->setBaseTRMtx(*calc_mtx);

    if (i_this->m8F8 <= 3) {
        g_env_light.setLightTevColorType(kamen_model, &actor->tevStr);
        i_this->bva->setFrame(kamen_pt[i_this->m8F8]);
        i_this->bva->entry(kamen_model);
        mDoExt_modelUpdateDL(kamen_model);
    }
}

/* 00001488-000014D0       .text eff_hane_draw__FP9bdk_classP9bdk_eff_s */
void eff_hane_draw(bdk_class* i_this, bdk_eff_s* eff) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = eff->m044;
    g_env_light.setLightTevColorType(model, &actor->tevStr);
    mDoExt_modelUpdateDL(model);
}

/* 000014D0-00001518       .text eff_Grock_draw__FP9bdk_classP9bdk_eff_s */
void eff_Grock_draw(bdk_class* i_this, bdk_eff_s* eff) {
    J3DModel* model = eff->m044;
    g_env_light.setLightTevColorType(model, &i_this->m6224);
    mDoExt_modelUpdateDL(model);
}

/* 00001518-0000159C       .text my_effect_draw__FP9bdk_class */
void my_effect_draw(bdk_class* i_this) {
    bdk_eff_s* eff = &i_this->m261C[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m261C); i++, eff++) {
        s8 cVar1 = eff->m000;
        if (cVar1 != 0) {
            if (cVar1 == 1) {
                eff_hane_draw(i_this, eff);
            } else if (cVar1 == 2) {
                eff_Grock_draw(i_this, eff);
            }
        }
    }
}

/* 0000159C-000018C4       .text daBdk_Draw__FP9bdk_class */
static BOOL daBdk_Draw(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();

    #if VERSION > VERSION_DEMO
    if (i_this->m259E > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->m259E);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->m259E == 1) {
        i_this->m259E = 0;
        mDoGph_gInf_c::mBlureFlag = FALSE;
    }
    #endif

    if (!dComIfGs_isStageBossEnemy()) {
        fopAc_ac_c* player = dComIfGp_getPlayer(1);
        actor->tevStr = player->tevStr;
        g_env_light.setLightTevColorType(model, &actor->tevStr);
        i_this->mpMorf->entryDL();

        J3DModel* model_2bc = i_this->mp2BC;
        for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
            model_2bc->setAnmMtx(i, model->getAnmMtx(i));
        }
        for (u16 i = 0; i < model->getModelData()->getWEvlpMtxNum(); i++) {
            model_2bc->setWeightAnmMtx(i, model->getWeightAnmMtx(i));
        }

        cXyz shadow_pos (
            actor->current.pos.x,
            actor->current.pos.y + (REG0_F(1) * 10.0f),
            actor->current.pos.z)
        ;
        f32 p5 = REG0_F(2) * 10.0f + 2000;
        i_this->m2C0 = dComIfGd_setRealShadow(
            i_this->m2C0, 1, i_this->mp2BC,
            &shadow_pos,
            p5, 0.0f, &actor->tevStr
        );

        kamen_draw(i_this);
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m300); i++) {
            tail_draw(i_this, &i_this->m300[i]);
        }
        dSnap_RegistFig(DSNAP_TYPE_BDK, actor, 1.0f, 1.0f, 1.0f);
    }
    kamen_break_draw(i_this);
    my_effect_draw(i_this);
    obj_draw(i_this);

    return TRUE;
}

/* 000018C4-00001BA0       .text pos_move__FP9bdk_class */
void pos_move(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz diff;
    cXyz out;
    diff = i_this->m2CC - actor->current.pos;
    s16 targetAngleXZ = cM_atan2s(diff.x, diff.z);
    s16 targetAngleY = -cM_atan2s(diff.y, std::sqrtf(diff.x * diff.x + diff.z * diff.z));

    s16 sVar1 = actor->current.angle.y;
    cLib_addCalcAngleS2(&actor->current.angle.y, targetAngleXZ,
    REG0_S(3) + 10,
    i_this->m2DC * i_this->m2E0);

    sVar1 = (sVar1 - actor->current.angle.y) * 0x20;
    s16 sVar2 = REG0_S(1) + 5500;

    if (sVar1 > sVar2) {
        sVar1 = sVar2;
    } else if (sVar1 < -sVar2) {
        sVar1 = -sVar2;
    }

    cLib_addCalcAngleS2(&actor->current.angle.z, (s16)sVar1,
    REG0_S(3) + 10,
    i_this->m2DC * i_this->m2E0 * 0.5f);

    cLib_addCalcAngleS2(&actor->current.angle.x, targetAngleY,
    REG0_S(3) + 10,
    i_this->m2DC*i_this->m2E0);

    cLib_addCalc2(&i_this->m2E0, 1.0f, 1.0f, 0.05f);
    cLib_addCalc2(&actor->speedF, i_this->m2E4, 1.0f, i_this->m2E8);

    diff.x = 0.0f;
    diff.y = 0.0f;
    diff.z = actor->speedF;

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);

    if (i_this->m2591 == 0) {
        MtxPosition(&diff, &actor->speed);
    } else {
        MtxPosition(&diff, &out);
        actor->speed.x = out.x;
        actor->speed.z = out.z;

        if (i_this->mpMorf->getFrame() < 20.0f) {
            actor->speed.y -= REG0_F(9) + 1.5f;
        } else {
            actor->speed.y += REG0_F(10) + 1.5f;
        }
    }
    actor->current.pos += actor->speed;
}

/* 00001BA0-00001CE0       .text ground_move__FP9bdk_class */
void ground_move(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz diff;
    cXyz out;
    cLib_addCalcAngleS2(&actor->current.angle.z, 0, 2 , 0x800);
    cLib_addCalcAngleS2(&actor->current.angle.x, 0, 2, 0x800);
    cLib_addCalc2(&actor->speedF, i_this->m2E4, 1.0f, i_this->m2E8);

    diff.x = 0.0f;
    diff.y = 0.0f;
    diff.z = actor->speedF;

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    MtxPosition(&diff, &out);

    actor->speed.x = out.x;
    actor->speed.z = out.z;
    actor->current.pos += actor->speed;
    actor->speed.y += actor->gravity;

    diff = i_this->m2CC - actor->current.pos;
    cLib_addCalcAngleS2(&actor->current.angle.y, cM_atan2s(diff.x, diff.z), 2, i_this->m2DC * i_this->m2E0);
    cLib_addCalc2(&i_this->m2E0, 1.0f, 1.0f, 0.1f);
}


/* 00001CE0-00001EB4       .text up_fly__FP9bdk_class */
void up_fly(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz diff;
    cXyz out;

    u8 pos_flag = 0;
    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_TOBITATU1, 5.0f, 0, 1.0f, BDK_BAS_TOBITATU1, 0);
        i_this->m2618 = 0x19;
        cMtx_YrotS(*calc_mtx,  actor->current.angle.y);
        diff.x = 0.0f;
        diff.y = 2000.0f;
        diff.z = 5000.0f;
        MtxPosition(&diff, &out);
        i_this->m2CC = actor->current.pos + out;
        i_this->mState++;
        i_this->m2E4 = 0.0f;
        i_this->m2E8 = 1.0f;
        actor->speedF = 0.0f;
        break;
    case 1: {
        s32 frame = i_this->mpMorf->getFrame();
        if (frame == REG0_S(7) + 0x17) {
            i_this->mState = 2;
            actor->speedF = REG0_F(8) + 50.0f;
            i_this->m2E4 = 40.0f;
            i_this->m2E8 = REG0_F(9) + 1.0f;
            actor->current.angle.x = -0x3000;
        } else {
            pos_flag = 1;
            break;
        }
        // Fall-through
    }
    case 2:
        i_this->m2E0 = 0.0f;
        if (i_this->mpMorf->isStop()) {
            i_this->mAction = ACTION_FLY;
            i_this->m2CA = -1;
            i_this->mState = 0;
        }
        break;
    default:
        break;
    }

    if (!pos_flag) {
        pos_move(i_this);
    }
}

/* 00001EB4-00002368       .text fly__FP9bdk_class */
void fly(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz diff;
    i_this->mF10 = 1;
    switch (i_this->m2CA) {
    case 0:
        break;
    case -1:
        anm_init(i_this, BDK_BCK_FLY1, 10.0f, 2, 1.0f, BDK_BAS_FLY1, 0);
        i_this->m2CA = 0;
        break;
    default:
        break;
    }

    i_this->m2E4 = l_HIO.m020;
    i_this->m2E8 = REG0_F(9) + 1.0f;
    i_this->m2DC = 600.0f;

    switch (i_this->mState) {
    case 0:
        if (i_this->m2FC == 0) {
            i_this->m2FC = cM_rndF(2.990f);
        } else {
            if (cM_rndF(1.0f) < 0.8f) {
                if (i_this->m2FC == 1) {
                    i_this->m2FC = 2;
                } else if (i_this->m2FC == 2) {
                    i_this->m2FC = 1;
                }
            } else {
                i_this->m2FC = 0;
            }
        }

        if (i_this->m2FC == 0) {
            actor->home.pos.x = REG0_F(0) + 6500.0f;
            actor->home.pos.y = REG0_F(1) + 11000.0f;
            actor->home.pos.z = REG0_F(2) + 2600.0f;

            i_this->m2CC.x = actor->home.pos.x + cM_rndFX(REG0_F(3) + 3000.0f);
            i_this->m2CC.y = actor->home.pos.y + 1000.0f;
            i_this->m2CC.z = actor->home.pos.z + cM_rndFX(REG0_F(3) + 3000.0f);
        } else if (i_this->m2FC == 1) {
            actor->home.pos.x = REG0_F(0) + 9800.0f;
            actor->home.pos.y = REG0_F(1) + 12000.0f;
            actor->home.pos.z = REG0_F(2) + -1500.0f;

            i_this->m2CC.x = actor->home.pos.x + cM_rndFX(REG0_F(3) + 1000.0f);
            i_this->m2CC.y = actor->home.pos.y + cM_rndF(1000.0f);
            i_this->m2CC.z = actor->home.pos.z + cM_rndFX(REG0_F(3) + 1000.0f);
        } else if (i_this->m2FC == 2) {
            actor->home.pos.x = REG0_F(0) + -1000.0f;
            actor->home.pos.y = REG0_F(1) + 12000.0f;
            actor->home.pos.z = REG0_F(2) + -2900.0f;

            i_this->m2CC.x = actor->home.pos.x + cM_rndFX(REG0_F(3) + 1000.0f);
            i_this->m2CC.y = actor->home.pos.y + 1000.0f;
            i_this->m2CC.z = actor->home.pos.z + cM_rndFX(REG0_F(3) + 1000.0f);
        }
        i_this->m2E0 = 0.0f;
        diff = i_this->m2CC - actor->current.pos;
        if (diff.abs() > 1000.0f) {
            i_this->mState++;
            i_this->m2EC[0] = 0;
        }
        break;
    case 1:
        diff = i_this->m2CC - actor->current.pos;
        if (diff.abs() < 1500.0f) {
            if (i_this->m2FC == 0 || cM_rndF(1.0f) < 0.3f || i_this->m2593 >= 4 || i_this->m8F8 < 2) {
                i_this->mAction = ACTION_LANDING;
                i_this->m2593 = 0;
                i_this->mState = 0;
            } else {
                i_this->mAction = ACTION_FLY_ATTACK;
                i_this->mState = 0;
                i_this->m2593++;
            }
        }
        break;
    default:
        break;
    }
    pos_move(i_this);
}

/* 00002368-000029F4       .text landing__FP9bdk_class */
void landing(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz diff1;
    cXyz diff2;
    cXyz out;

    u8 pos_flag = 0;
    u8 eff_hane_num = 0;
    i_this->mF10 = 1;
    switch (i_this->mState) {
    case -2:
    case 0: {
        s16 angle = fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0));
        cMtx_YrotS(*calc_mtx, angle);
        diff2.x = 0.0f;
        diff2.y = 0.0f;
        if (i_this->mState == 0) {
            diff2.z = -800.0f;
        } else {
            diff2.z = 0.0f;
        }

        MtxPosition(&diff2, &out);
        i_this->m2CC = player->current.pos + out;
        if (land_area_check(&i_this->m2CC, 1400.0f)) {
            i_this->m2CC.y += REG0_F(2) + 600.0f;
            i_this->mState = 1;
            i_this->m2DC = 1000.0f;
            i_this->m2E0 = 0.0f;
            i_this->m2EC[0] = 50.0f;
        } else {
            i_this->mAction = ACTION_FLY;
            i_this->mState = 0;
            break;
        }
        // Fall-through
    }
    case 1:
        diff1 = i_this->m2CC - actor->current.pos;
        if (diff1.abs() < 1300.0f) {
            i_this->mState = 2;
            anm_init(i_this, BDK_BCK_TYAKUTI1, 15.0f, 0, 0.001f, BDK_BAS_TYAKUTI1, 0);
            i_this->m2E0 = 1.0f;
            pos_flag = 1;
        } else {
            if (i_this->m2EC[0] == 1) {
                anm_init(i_this, BDK_BCK_KAKKU1, 30.0f, 2, 1.0f, -1, 0);
            }
        }
        break;
    case 2:
        pos_flag = 1;

        cLib_addCalc2(&actor->current.pos.x, i_this->m2CC.x, 1.0f, std::fabsf(actor->speed.x) * i_this->m2E0);
        cLib_addCalc2(&actor->current.pos.y, i_this->m2CC.y, 1.0f, std::fabsf(actor->speed.y) * i_this->m2E0);
        cLib_addCalc2(&actor->current.pos.z, i_this->m2CC.z, 1.0f, std::fabsf(actor->speed.z) * i_this->m2E0);
        cLib_addCalcAngleS2(&actor->current.angle.z, 0, 2, 0x800);
        cLib_addCalcAngleS2(&actor->current.angle.x, 0, 2, 0x800);
        diff1 = i_this->m2CC - actor->current.pos;
        if (diff1.abs() < REG0_F(3) + 300.0f) {
            i_this->mState = 3;
        }
        break;
    case 3:
    case 4:
        pos_flag = 1;
        eff_hane_num = 3;
        actor->current.pos.y += actor->speed.y;
        actor->speed.y += actor->gravity;

        cLib_addCalc2(&actor->current.pos.x, i_this->m2CC.x, 0.2f, std::fabsf(actor->speed.x) * i_this->m2E0);
        cLib_addCalc2(&actor->current.pos.z, i_this->m2CC.z, 0.2f, std::fabsf(actor->speed.z) * i_this->m2E0);
        cLib_addCalcAngleS2(&actor->current.angle.z, 0, 2, 0x800);
        cLib_addCalcAngleS2(&actor->current.angle.x, 0, 2, 0x800);

        if (i_this->m2586 != 0 || i_this->mAcch.ChkGroundHit() || actor->current.pos.y <= i_this->mAcch.GetGroundH() + 1.0f) {
            actor->speedF = 0.0f;

            actor->speed.z = 0.0f;
            actor->speed.x = 0.0f;
            actor->speed.y = -10.0f;
            if (i_this->mState == 3) {
                anm_init(i_this, BDK_BCK_TYAKUTI1, 5.0f, 0, 1.0f, BDK_BAS_TYAKUTI1, 0);
                i_this->mState = 4;
                eff_hane_num = 10;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));

                dComIfGp_particle_set(
                    dPa_name::ID_SCENE_8131, &actor->current.pos, NULL, NULL,
                    0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
                    &i_this->m6224.mColorK0, &i_this->m6224.mColorK0
                );
                if (i_this->m6078[0] == 0) {
                    i_this->m6078[0] = 100;
                    dComIfGp_particle_setToon(
                        dPa_name::ID_SCENE_A132, &actor->current.pos, NULL, NULL,
                        0xB9, &i_this->m6080[0], (s8)fopAcM_GetRoomNo(actor)
                    );
                }
            }
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mAction = ACTION_WAIT;
            i_this->mState = 0;
            i_this->m2EC[3] = cM_rndF(600.0f) + 600.0f;
        }
        i_this->m2584 = 2;
        break;
    default:
        break;
    }

    if (!pos_flag) {
        pos_move(i_this);
    }
    if (eff_hane_num != 0) {
        if (eff_hane_num <= 7) {
            if (!(i_this->m2C4 & eff_hane_num)) {
                eff_hane_set(i_this, &i_this->m1168, 1, 0);
            }
        } else {
            eff_hane_set(i_this, &i_this->m1168, eff_hane_num, 0);
        }
    }
}

/* 000029F4-00002F64       .text wait__FP9bdk_class */
void wait(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 dist = fopAcM_searchActorDistance(actor, player);
    i_this->mF10 = 1;
    i_this->m2CC = player->current.pos;

    s16 angle = actor->current.angle.y - fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0));
    i_this->m2E4 = 0.0f;
    i_this->m2E8 = 5.0f;
    i_this->m2DC = 500.0f;

    BOOL view = pl_view_check(i_this);

    switch (i_this->mState) {
    case 0:
        if (5 <= i_this->m2594 || (2 <= i_this->m2592 && i_this->m8F8 < 4) || !view || i_this->m2EC[3] == 0) {
            i_this->mAction = ACTION_UP_FLY;
            i_this->m2594 = 0;
            i_this->m2592 = 0;
            break;
        }
        anm_init(i_this, BDK_BCK_WAIT1, 10.0f, 2, 1.0f, -1, 0);
        i_this->mState = 1;
        i_this->m2EC[0] = cM_rndF(30.0f) + 40.0f;
        i_this->m2CA = 0;
        actor->speedF = 0.0f;
        // Fall-through
    case 1:
        if (angle > 0x3000 || angle < -0x3000) {
            i_this->mState = 5;
        } else {
            if (i_this->m2EC[1] == 0) {
                if (!view) {
                    i_this->mState = 0;
                    break;
                }
                if (angle > 0x800) {
                    if (i_this->m2CA != 1) {
                        i_this->m2CA = 1;
                        anm_init(i_this, BDK_BCK_SENKAI_L1, 10.0f, 2, 1.0f, BDK_BAS_SENKAI_L1, 0);
                        i_this->m2EC[1] = 0x14;
                    }
                } else {
                    if (angle < -0x800) {
                        if (i_this->m2CA != 2) {
                        i_this->m2CA = 2;
                        anm_init(i_this, BDK_BCK_SENKAI_R1, 10.0f, 2, 1.0f, BDK_BAS_SENKAI_R1, 0);
                        i_this->m2EC[1] = 0x14;
                        }
                    } else if (i_this->m2CA != 3) {
                        i_this->m2CA = 3;
                        anm_init(i_this, BDK_BCK_WAIT1, 10.0f, 2, 1.0f, -1, 0);
                        i_this->m2EC[1] = 0x14;
                    }
                }
            }
            if (i_this->m2CA != 3) {
                i_this->m2DC = REG0_F(0) + 800.0f;
            }
            if ((i_this->m2EC[0] == 0) && (i_this->m2CA == 3)) {
                if (l_HIO.m014 != 0) {
                    if (l_HIO.m014 == 1) {
                    i_this->mAction = ACTION_KUTI_ATTACK;
                    } else if (l_HIO.m014 == 2) {
                    i_this->mAction = ACTION_WIND_ATTACK;
                    }
                    i_this->mState = 0;
                } else {
                    i_this->m2592++;
                    if (dist < REG0_F(11) + 450.0f) {
                        i_this->mAction = ACTION_JIDA_ATTACK;
                        i_this->mState = 0;
                    } else if (dist < REG0_F(12) + 550.0f ) {
                        #if VERSION > VERSION_DEMO
                        if (i_this->m8F8 < 2) {
                            i_this->mAction = ACTION_KUTI_ATTACK;
                        } else
                        #endif
                        {
                            if (cM_rndF(1.0f) < 0.25f) {
                                i_this->mAction = ACTION_WIND_ATTACK;
                            } else {
                                i_this->mAction = ACTION_KUTI_ATTACK;
                            }
                        }
                        i_this->mState = 0;
                    } else if (dist < REG0_F(15) + 1300.0f) {
                        i_this->mState = 2;
                        anm_init(i_this, BDK_BCK_WALK1, 3.0f, 2, l_HIO.m01C, BDK_BAS_WALK1, 0);
                        i_this->m2E0 = 0.0f;
                        actor->speedF = 0.0f;
                    } else {
                        if (cM_rndF(1.0f) < 0.5f) {
                            i_this->mAction = ACTION_JUMP;
                            i_this->mState = 0;
                        } else {
                            i_this->mAction = ACTION_WIND_ATTACK;
                            i_this->mState = 0;
                        }
                    }
                }
            }
        }
        break;
    case 2:
        i_this->m2E4 = l_HIO.m018;
        i_this->m2E8 = 1.0f;
        if (dist < REG0_F(12) + 530.0f || dist > 1350.0f) {
            i_this->mState = 1;
        }
        break;
    case 5:
        anm_init(i_this, BDK_BCK_JUMP1, 5.0f, 0, 0.0f, BDK_BAS_JUMP1, 0);
        i_this->mState = 6;
        fopAcM_GetSpeed_p(actor)->y = REG8_F(9) + 50.0f;
        actor->speedF = 0.0f;
        // Fall-through
    case 6:
        i_this->m2DC = 700.0f;
        if (fopAcM_GetSpeed_p(actor)->y < 0.0f && fopAcM_GetPosition_p(actor)->y < i_this->mAcch.GetGroundH() + 5.0f) {
            anm_init(i_this, BDK_BCK_JUMP1, 2.0f, 0, 1.0f, BDK_BAS_JUMP1, 0);
            i_this->mState = 7;
        }
        break;
    case 7:
        i_this->m2DC = 0.0f;
        if (i_this->mpMorf->isStop()) {
            i_this->mState = 1;
        }
        break;
    default:
        break;
    }
    ground_move(i_this);
}

/* 00002F64-00003164       .text jump__FP9bdk_class */
void jump(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz diff;
    cXyz out;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    i_this->mF10 = 1;
    i_this->m2E4 = 0.0f;
    i_this->m2E8 = 5.0f;
    i_this->m2DC = 500.0f;

    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_TOBITATU1, 5.0f, 0, 1.0f, BDK_BAS_TOBITATU1, 0);
        i_this->m2618 = 0x19;
        i_this->mState = 1;
        i_this->m2CC = player->current.pos;
        break;
    case 1:
        if (REG0_S(7) + 0x17 != (s32)i_this->mpMorf->getFrame()) {
            break;
        }
        actor->speed.y = REG8_F(9) + 50.0f;
        i_this->mState = 2;
        i_this->m2586 = 0;
        diff.x = 0.0f;
        diff.y = 0.0f;
        diff.z = 10000.0f;
        cMtx_YrotS(*calc_mtx, actor->current.angle.y);
        MtxPosition(&diff, &out);

        i_this->m2CC = out + actor->current.pos;
        i_this->m2EC[0] = REG8_S(5) + 0x1E;
        // Fall-through
    case 2:
        actor->speedF = REG8_F(10) + 30.0f;
        i_this->m2E4 = 30.0f;
        i_this->m2E8 = 30.0f;
        if (actor->speed.y < 0.0f) {
            actor->speed.y = 0.0f;
        }
        if (i_this->m2EC[0] == 0) {
            anm_init(i_this, BDK_BCK_TYAKUTI1, 15.0f, 0, 0.001f, BDK_BAS_TYAKUTI1, 0);
            i_this->mAction = ACTION_LANDING;
            i_this->mState = 3;
        }
        break;
    default:
        break;
    }
    ground_move(i_this);
}

/* 00003164-0000345C       .text jida_attack__FP9bdk_class */
void jida_attack(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    cXyz vec1;
    f32 dist = fopAcM_searchActorDistance(actor, player);
    i_this->mF10 = 1;

    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_JIDANDA1, 10.0f, 2, 1.0f, BDK_BAS_JIDANDA1, 0);
        i_this->mState = 1;
        i_this->m2EC[0] = (s16)cM_rndF(5.0f) * 0x18;
        // Fall-through
    case 1: {
        if (!(i_this->m2C4 & 7)) {
            eff_hane_set(i_this, &i_this->m1168, 1, 0);
        }
        i_this->m2584 = 2;
        s32 frame = (s32)i_this->mpMorf->getFrame();
        if (frame == 1 || frame == 0xD) {
                s32 index = 0;
                if (frame == 0xD) {
                    index = 1;
                }
                dComIfGp_particle_set(
                dPa_name::ID_SCENE_8133, &i_this->m1174[index], NULL, NULL,
                0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
                &i_this->m6224.mColorK0, &i_this->m6224.mColorK0
            );
            if (i_this->m6078[1] == 0) {
                i_this->m6078[1] = 0xA;
                dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A134, &i_this->m1174[index], 0, NULL, 0xB9,
                &i_this->m6080[1], (s8)fopAcM_GetRoomNo(actor)
                );
            }
        }

        if ((frame >= 4 && frame <= 0xB) || (frame >= 0x10 && frame <= 0x17)) {
            cLib_addCalcAngleS2(&actor->current.angle.y, fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0)), 8, 0x200);
            vec1.z = REG0_F(1) + 10.0f;

            if (frame == 4 || frame == 0x10) {
                dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
        } else {
            vec1.z = 0.0f;
        }

        cMtx_YrotS(*calc_mtx, fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0)));

        vec1.x = 0.0f;
        vec1.y = -10.0f;
        MtxPosition(&vec1, &actor->speed);
        actor->current.pos += actor->speed;

        if (i_this->m2EC[0] == 0 || dist > 600.0f) {
            i_this->mAction = ACTION_WAIT;
            i_this->mState = 0;
        }
        break;
    }
    default:
        break;
    }
}

/* 0000345C-00003BC4       .text kuti_attack__FP9bdk_class */
void kuti_attack(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz vec1;

    s8 bVar1 = 0;
    s8 bVar2 = 0;
    i_this->m1134 = 2500;
    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_ATTACK1, 5.0f, 0, 1.0f, BDK_BAS_ATTACK1, 0);
        i_this->mState = 2;
        fopAcM_monsSeStart(actor, JA_SE_CV_DK_ATTACK, 0);
        break;
    case 2:
        if (i_this->mpMorf->getFrame() < 36.0f) {
            i_this->m2584 = 1;
        }

        if ((s16)(REG0_S(5) + 0x1E) == (s16)i_this->mpMorf->getFrame()) {
            i_this->m1138 = REG0_S(6) + 0x1E;
            i_this->m1136 = 0;

            fopAcM_seStart(actor, JA_SE_CM_DK_ATTACK, 0);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 6, -0x21, cXyz(0.0f, 1.0f, 0.0f));

            i_this->m261C[0x27].m000 = 2;
            i_this->m261C[0x27].m03C = 0;

            cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
            vec1.x = 0.0f;
            vec1.y = 0.0f;
            vec1.z = 500.0f;
            MtxPosition(&vec1, &i_this->m261C[0x27].m004);

            i_this->m261C[0x27].m004 += actor->current.pos;

            dComIfGp_particle_set(
                dPa_name::ID_SCENE_812D, &i_this->m261C[0x27].m004, NULL, NULL,
                0xFF, NULL, -1
            );
            eff_hane_set(i_this, &i_this->m1168, 5, 0);
            bVar2 = 1;
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BDK_BCK_NUKENAI1, 2.0f, 0, 1.0f, -1, 0);
            i_this->mState = 5;
            i_this->m2EC[0] = cM_rndF(60.0f) + 90.0f;

            mDoAud_seStart(JA_SE_CM_DK_JITABATA, &actor->eyePos, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            fopAcM_monsSeStart(actor, JA_SE_CV_DK_NUKEZU, 0);
        }
        break;
    case 3:
        if (i_this->mpMorf->isStop()) {
            i_this->mAction = ACTION_WAIT;
            i_this->mState = 0;
        }
        break;
    case 5:
        if (i_this->mpMorf->isStop()) {
            if (i_this->m2EC[0] == 0) {
                bVar1 = 1;
            } else {
                i_this->mpMorf->setPlaySpeed(-1.0f);
                i_this->mState = 6;
            }
        }
        break;
    case 6:
        if (i_this->mpMorf->isStop()) {
            i_this->mpMorf->setPlaySpeed(1.0f);
            i_this->mState = 5;
            fopAcM_seStart(actor, JA_SE_CM_DK_JITABATA, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_DK_NUKEZU, 0);
            eff_hane_set(i_this, &i_this->m1168, 2, 0);
        }
        break;
    case 10:
        if (i_this->mpMorf->isStop()) {
            if (i_this->m2EC[0] == 0) {
                bVar1 = 1;
            } else {
                anm_init(i_this, BDK_BCK_NUKENAI1, 2.0f, 0, 1.0f, -1, 0);
                i_this->mState = 5;
                fopAcM_seStart(actor, JA_SE_CM_DK_JITABATA, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_DK_NUKEZU, 0);
            }
            eff_hane_set(i_this, &i_this->m1168, 2, 0);
        }
        break;
    default:
        break;
    }
    if (i_this->m2EC[2] == 1 || bVar1 != 0) {
        anm_init(i_this, BDK_BCK_NUKU1, 1.0f, 0, 1.0f, -1, 0);
        i_this->mState = 3;
        fopAcM_seStart(actor, JA_SE_CM_DK_PULL_UP_HEAD, 0);
        fopAcM_monsSeStart(actor, JA_SE_CV_DK_NUKERU, 0);
        i_this->m261C[0x27].m000 = 0;
        bVar2 = 1;
    }
    if (bVar2) {
        if (i_this->m6078[2] == 0) {
            i_this->m6078[2] = 0x3c;

            dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A12E, &i_this->m261C[0x27].m004, 0, NULL, 0xB9,
                &i_this->m6080[2], (s8)fopAcM_GetRoomNo(actor)
            );
        }
        dComIfGp_particle_set(
            dPa_name::ID_SCENE_812C, &i_this->m261C[0x27].m004, NULL, NULL,
            0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
            &i_this->m6224.mColorK0, &i_this->m6224.mColorK0
        );
    }
    actor->current.pos.y += actor->speed.y;
}

/* 00003BC4-00003D9C       .text wind_set__FP9bdk_classP4cXyz */
void wind_set(bdk_class* i_this, cXyz* param2) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player;
    camera_class* camera;
    cXyz vec1;
    cXyz vec2;

    if ((i_this->m2C4 & 1) == 0) {
        player = dComIfGp_getPlayer(0);
        vec1.y = 0.0f;
        vec1.x = 0.0f;
        vec1.z = REG0_F(4) + 100.0f;

        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m2494); i++) {
            if (i_this->m2488[i] == 0) {
                i_this->m2488[i] = 1;

                cMtx_YrotS(*calc_mtx, actor->current.angle.y + (s16)cM_rndFX(6000.0f));
                MtxPosition(&vec1, &i_this->m250C[i]);
                i_this->m2494[i] = *param2;
                i_this->m2494[i].y = player->current.pos.y;
                break;
            }
        }
    }
    camera = static_cast<camera_class*>(dComIfGp_getCamera(0));
    vec2 = actor->eyePos - camera->mLookat.mEye;
    wind_se_pos = actor->eyePos + (camera->mLookat.mEye - actor->eyePos) * 0.8f;
    mDoAud_seStart(JA_SE_CM_DK_WIND, &wind_se_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

/* 00003D9C-000045C8       .text fly_attack__FP9bdk_class */
void fly_attack(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = daPy_getPlayerActorClass();

    cXyz offset;
    cXyz offset2;
    cXyz dest;
    u8 bVar1 = 0;
    i_this->mF10 = 1;
    switch (i_this->mState) {
    case 0:
        i_this->mState = 1;
        i_this->m2EC[0] = 0x1E;
        i_this->m2E0 = 0.0f;
        i_this->m2EC[1] = 200;
        i_this->mF18 = cM_rndFX(100.0f);
        // Fall-through
    case 1:
        bVar1 = 1;
        i_this->m2CC = player->current.pos;
        i_this->m2CC.x = i_this->m2CC.x + i_this->mF18;
        i_this->m2CC.z = i_this->m2CC.z + i_this->mF18;
        if (i_this->m2EC[0] == 0) {
            i_this->m2DC = 400.0f;
        } else {
            i_this->m2CC.x = 3273.0f;
            i_this->m2CC.z = -3108.0f;
            i_this->m2DC = 1000.0f;
        }
        i_this->m2E4 = l_HIO.m024;
        i_this->m2E8 = 1.0f;
        offset = i_this->m2CC - actor->current.pos;
        if (offset.abs() < REG8_F(11) + 1000.0f || i_this->m2EC[1] == 0) {
            i_this->mState = 2;
            cMtx_YrotS(*calc_mtx, actor->current.angle.y);

            offset2.x = 0.0f;
            offset2.y = 500.0f;
            offset2.z = 4000.0f;

            MtxPosition(&offset2, &dest);
            i_this->m2CC = actor->current.pos + dest;
            i_this->m2E0 = 0.0f;
            i_this->m2EC[0] = 0x28;
            eff_hane_set(i_this, &i_this->m1168, 10, 0);
        } else if (i_this->m2EC[0] == 1) {
            anm_init(i_this, BDK_BCK_KAKKU1, 30.0f, 2, 1.0f, -1, 0);
        }
        break;
    case 2:
        bVar1 = 1;
        offset2.x = 0.0f;
        offset2.y = 0.0f;
        offset2.z = REG0_F(11) + -1000.0f;
        cMtx_YrotS(*calc_mtx, actor->current.angle.y);
        MtxPosition(&offset2, &dest);
        dest += actor->current.pos;
        wind_set(i_this, &dest);
        if (i_this->m2EC[0] == 0) {
            i_this->mAction = ACTION_FLY;
            i_this->m2CA = -1;
            i_this->mState = 0;
        }
        break;
    case 10:
        anm_init(i_this, BDK_BCK_DAMAGE4, 2.0f, 0, 1.0f, -1, 1);
        i_this->mState = 0xB;
        actor->speed.y = 0.0f;
        i_this->m2EC[0] = REG0_S(5) + 0x28;
        i_this->m2EC[1] = REG0_S(6) + 0x50;
        dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        fopAcM_seStart(actor, JA_SE_CM_DK_CRASH_WALL, 0);
        fopAcM_monsSeStart(actor, JA_SE_CV_DK_KABE_DAMAGE, 0);

        JPABaseEmitter* emitter;
        if (i_this->m6078[3] == 0) {
            i_this->m6078[3] = 100;
            emitter = dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A135, &actor->current.pos, &actor->shape_angle, NULL,
                0xB9, &i_this->m6080[3], (s8)fopAcM_GetRoomNo(actor)
            );
            if (emitter) {
                emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x1C)); // j_dk_mabuta joint
            }
        }
        emitter = dComIfGp_particle_set(
            dPa_name::ID_SCENE_8137, &actor->current.pos, &actor->shape_angle, NULL,
            0xFF, NULL, (s8)fopAcM_GetRoomNo(actor), &actor->tevStr.mColorK0, &actor->tevStr.mColorK0
        );
        if (emitter) {
            emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x16)); // j_dk_mune2 joint
        }
        // Fall-through
    case 0xB:
        actor->current.pos.y += actor->speed.y;
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BDK_BCK_PIKUPIKU1, 5.0f, 2, 1.0f, -1, 0);
        }
        if (i_this->m2EC[0] == 0) {
            actor->speed.y -= (0.5f + REG0_F(7));
            actor->current.angle.z += (s16)(REG0_S(7) + 0x50);
            if (i_this->m2EC[1] == 0) {
                i_this->mState = 0xC;
                i_this->m2D8 = actor->current.angle.y + 0x8000;
                i_this->m2EC[0] = REG0_S(8) + 0x28;
                anm_init(i_this, BDK_BCK_FLY2, 5.0f, 2, 2.0f, BDK_BAS_FLY2, 0);
            }
        }
        break;
    case 0xC:
        actor->speed.y += REG0_F(8) + 2.0f;
        actor->current.pos.y += actor->speed.y;
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->m2D8, 8, 0x400);

        if (i_this->m2EC[0] == 0) {
            i_this->mAction = ACTION_FLY;
            i_this->m2CA = -1;
            i_this->mState = 0;
            actor->speedF = 0.0f;
        }
        break;
    default:
        break;
    }
    if (i_this->mAction == ACTION_FLY_ATTACK && (i_this->mState < 10)) {
        i_this->m2584 = 2;
        pos_move(i_this);
        i_this->mAcchCir.SetWall(REG0_F(17) + 500.0f, 500.0f);
        i_this->mAcch.SetGroundUpY(REG0_F(18));
        if (i_this->mAcch.ChkGroundHit() && (i_this->m2619 == 0)) {
            for (s32 i = 0; i <= 1; i++) {
                foot_eff_pos[i] = i_this->m1174[i];

                i_this->mp6214[0 + i] = dComIfGp_particle_set(
                dPa_name::ID_SCENE_812A, &foot_eff_pos[i], &actor->shape_angle);

                i_this->mp6214[2 + i] = dComIfGp_particle_set(
                dPa_name::ID_SCENE_812B, &foot_eff_pos[i], &actor->shape_angle);
            }
            i_this->m2619++;
        }
        if (i_this->mAcch.ChkWallHit()) {
            i_this->mState = 10;
        }
    }
    if ((u8)bVar1) {
        fopAcM_seStart(actor, JA_SE_CM_DK_GLIDING, 0);
    }
}

/* 000045C8-0000491C       .text wind_attack__FP9bdk_class */
void wind_attack(bdk_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    fopAc_ac_c* actor = &i_this->actor;
    cXyz offset;
    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_TOBITATU1, 5.0f, 0, 1.0f, BDK_BAS_TOBITATU1, 0);
        i_this->m2618 = 0x19;
        i_this->mState++;
        i_this->m2CC = actor->current.pos;
        i_this->m2E0 = 0;
        // Fall-through
    case 1:
        if (i_this->mpMorf->getFrame() == 23) {
        i_this->mState = 2;
        i_this->m2CC.y += 500.0f;
        }
        break;
    case 2:
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BDK_BCK_FLY2, 5.0f, 2, 2.0f, BDK_BAS_FLY2, 0);
            i_this->mState = 3;
            i_this->m2EC[0] = 200;
        }
        break;
    case 3:
        wind_set(i_this, &actor->current.pos);
        if (!(i_this->m2C4 & 1)) {
            offset = i_this->m1168;
            offset.x += cM_rndFX(300.0f);
            offset.y -= cM_rndF(200.0f);
            offset.z += cM_rndFX(300.0f);
            eff_hane_set(i_this, &offset, 1, 1);
        }
        cLib_addCalc2(&i_this->m2608, 1.0f, 1.0f, 0.05f);
        cLib_addCalc2(&i_this->m2E0, 1.0f, 1.0f, 0.05f);

        if (i_this->m2EC[0] == 0 || i_this->m2F8 != 0) {
            i_this->mAction = ACTION_LANDING;
            i_this->mState = 3;

            i_this->m2CC = player->current.pos;
            actor->speed.y = -20.0f;
            return;
        }
        break;
    default:
        break;
    }

    cLib_addCalcAngleS2(&actor->current.angle.y, fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0)), 4, 0x800);
    cLib_addCalc2(&actor->current.pos.y, i_this->m2CC.y + (cM_ssin(i_this->m2C4 * 1500)) * i_this->m2E0 * 100.0f, 0.1f, 60.0f);
    cLib_addCalc2(&actor->current.pos.x, i_this->m2CC.x + cM_ssin(i_this->m2C4 * 700) * i_this->m2E0 * 200.0f, 0.1f, 40.0f);
    cLib_addCalc2(&actor->current.pos.z, i_this->m2CC.z + cM_ssin(i_this->m2C4 * 500) * i_this->m2E0 * 200.0f, 0.1f, 40.0f);
}

/* 0000491C-000049C0       .text end_set__FP9bdk_class */
void end_set(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mAction = ACTION_END;
    i_this->m261C[0x27].m000 = 0;
    if (actor->current.pos.y < 9810.0f) {
        if (i_this->m1150.y < 10000.0f) {
            i_this->mState = 0;
        } else {
            i_this->mState = 1;
        }
    } else {
        i_this->mState = 2;
        i_this->m25A2 = 1;
    }
    i_this->m25A0 = 100;
    fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
    mDoAud_bgmStop(0x1E);
}

/* 000049C0-00005018       .text damage_check__FP9bdk_class */
void damage_check(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = daPy_getPlayerActorClass();

    i_this->mStts.Move();
    s8 sVar1 = 0;
    u8 hit_type = 0;
    csXyz angle;
    cXyz pos;
    CcAtInfo atInfo;

    if (i_this->m8F8 < 4) {
        if (i_this->mHeadTgSph.ChkTgHit()) {
            hit_type = 1;
            atInfo.mpObj = i_this->mHeadTgSph.GetTgHitObj();
        }
    } else {
        if (i_this->mTosakaTgSph.ChkTgHit()) {
            hit_type = 2;
            atInfo.mpObj = i_this->mTosakaTgSph.GetTgHitObj();
        }
    }
    if (hit_type != 0 && i_this->m2F8 == 0) {
        at_power_check(&atInfo);
        if (hit_type == 1) {
            i_this->m2F8 = 0xC;
            if (atInfo.mResultingAttackType == 9 && i_this->m1150.y < 10000.0f) {
                actor->health = 0x14;
                fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x32);
                if (i_this->m2B4 == 1) {
                    i_this->mAction = ACTION_T_DOWN;
                    i_this->mState = 0;
                    i_this->m2FA = REG0_S(3) + 10;
                    i_this->m2F8 = 0x1E;

                    fopAcM_monsSeStart(actor, JA_SE_CV_DK_LAST_DAMAGE, 0);
                    dScnPly_ply_c::setPauseTimer(8);
                    mDoAud_bgmStop(0x1E);
                } else {
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_3C01);
                    #if VERSION > VERSION_DEMO
                    dScnPly_ply_c::setPauseTimer(5);
                    #endif
                    i_this->m8F8++;
                    if (i_this->m8F8 == 4) {
                        i_this->m8F8 = 3;
                        i_this->mAction = ACTION_KAMEN_DEMO;
                        i_this->mState = 0;
                        fopAcM_seStart(actor, JA_SE_CM_DK_BREAK_MASK, 0);
                    } else {
                        i_this->m2FA = REG0_S(3) + 10;
                        i_this->m2EC[2] = 0xF;
                        i_this->m2F8 = 0x1E;
                    }
                }
                i_this->m1138 = 0;

                pos.z = 2.0f;
                pos.y = 2.0f;
                pos.x = 2.0f;
                angle.z = 0;
                angle.x = 0;
                angle.y = player->shape_angle.y + 0x8000;
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, i_this->mHeadTgSph.GetTgHitPosP(), &angle, &pos);
                dComIfGp_particle_set(dPa_name::ID_SCENE_8129, i_this->mHeadTgSph.GetTgHitPosP(), &actor->shape_angle, NULL);

                dKy_SordFlush_set(actor->current.pos, 1);
                dComIfGp_getVibration().StartShock(REG0_S(2) + 5,
                -0x21, cXyz(0.0f, 1.0f, 0.0f));
            } else {
                def_se_set(actor, atInfo.mpObj, 0x40);
            }
        } else {
            i_this->m2F8 = 6;

            atInfo.mpActor = cc_at_check(actor, &atInfo);
            fopAcM_monsSeStart(actor, JA_SE_CV_DK_DAMAGE, 0);

            i_this->m1138 = REG0_S(5) + 0x1E;
            i_this->m1136 = cM_atan2s(actor->eyePos.x - player->current.pos.x,
            actor->eyePos.z - player->current.pos.z);

            if (i_this->mAction == ACTION_KUTI_ATTACK && i_this->m1150.y < 10000.0f) {
                anm_init(i_this, BDK_BCK_DAMAGE1, 2.0f, 0, 1.0f, -1, 0);
                i_this->mState = 10;
                i_this->m2594++;
                if (6 <= i_this->m2594) {
                    i_this->m2EC[2] = 10;
                    i_this->m2F8 = 0x14;
                }
                sVar1 = 1;
            } else {
                if (i_this->m2586 != 0) {
                    if (i_this->mAction == ACTION_KUTI_ATTACK) {
                        i_this->mAction = ACTION_WAIT;
                        anm_init(i_this, BDK_BCK_WAIT1, 10.0f, 2, 1.0f, -1, 0);
                        i_this->mState = 1;

                        i_this->m2EC[0] = cM_rndF(30.0f) + 30.0f;
                        i_this->m2EC[1] = i_this->m2EC[0];
                        i_this->m2CA = 0;
                    }
                    anm_init(i_this, BDK_BCK_DAMAGE3, 2.0f, 0, 1.0f, -1, 1);
                    sVar1 = 1;
                } else {
                    anm_init(i_this, BDK_BCK_DAMAGE2, 2.0f, 0, 1.0f, BDK_BAS_DAMAGE2, 1);
                    sVar1 = 1;
                }
            }
            if (actor->health <= 0) {
                dScnPly_ply_c::setPauseTimer(8);
                end_set(i_this);
                fopAcM_monsSeStart(actor, JA_SE_CV_DK_LAST_DAMAGE, 0);
            } else if (sVar1) {
                JPABaseEmitter* emitter = dComIfGp_particle_set(
                dPa_name::ID_SCENE_8137, &actor->current.pos, &actor->shape_angle, NULL,
                0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
                &actor->tevStr.mColorK0, &actor->tevStr.mColorK0
                );
                if (emitter) {
                    emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x16)); // j_dk_mune2 joint
                }
            }
        }
    }
}
static f32 kamen_break_off_x[] = {
    50.0f, 30.0f, -50.0f, -30.0f,
};
static f32 kamen_break_off_y[] = {
    0.0f, -120.0f, 20.0f, 0.0f,
};
static f32 kamen_break_off_z[] = {
    50.0f, 20.0f, 50.0f, 0.0f,
};
static f32 kamen_break_sd_x[] = {
    -5.0f, 0.0f, 5.0f, 0.0f,
};
static f32 kamen_break_sd_z[] = {
    0.0f, 5.0f, 0.0f, 0.0f,
};
static u8 kamen_break_time[] = {
    0x1E, 0x2D, 0x28, 0x23,
};

/* 00005054-000053C4       .text kamen_demo__FP9bdk_class */
void kamen_demo(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz pos;
    cXyz dist;

    i_this->m1134 = 0;
    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_NUKENAI1, 0.0f, 0, 0.0f, -1, 0);
        i_this->mState = 1;
        i_this->m25A0 = 1;
        fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
        break;
    case 1:
        i_this->m25A4 = 0;
        i_this->m25A6 = 0;
        i_this->m25C8 = 45.0f;

        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m90C); i++) {
            i_this->m90C[i] = 1;
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 0.0f;

            MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x18), *calc_mtx); // j_dk_atama1 joint
            MtxPosition(&pos, &i_this->m910[i]);
            i_this->m9A0[i].y = actor->shape_angle.y;
            i_this->m9A0[i].x = REG0_S(6) + 0x3625;
            i_this->m9A0[i].z = 0;
            pos.x = -kamen_break_off_x[i];
            pos.y = 0.01f * REG0_F(15) + (55.0f - kamen_break_off_y[i]);
            pos.z = 0.01f * REG0_F(16) + (110.0f - kamen_break_off_z[i]);
            cMtx_YrotS(*calc_mtx, i_this->m9A0[i].y);
            cMtx_XrotM(*calc_mtx, i_this->m9A0[i].x);
            MtxPosition(&pos, &dist);
            i_this->m910[i] += dist;
            i_this->m940[i].x = i_this->m910[i].x;
            i_this->m940[i].y = i_this->m910[i].y;
            i_this->m940[i].z = i_this->m910[i].z;
            cMtx_YrotS(*calc_mtx, i_this->m9A0[i].y);
            pos.x = (1.0f + REG0_F(7)) * kamen_break_sd_x[i];
            pos.y = 0.0f;
            pos.z = (1.0f + REG0_F(7)) * kamen_break_sd_z[i];

            MtxPosition(&pos, &i_this->m970[i]);
            i_this->m9E8[i] = kamen_break_time[i];
        }
        i_this->mState = 2;
        break;
    case 2:
        if (i_this->m25A6 > REG0_S(8) + 0x2d) {
            i_this->m1134 = 500;
            i_this->m113A = 1;
        }
        if (i_this->m25A6 >= 0x6E && REG8_S(8) == 0) {
            i_this->m25A0 = 150;
            i_this->mAction = ACTION_KUTI_ATTACK;
            anm_init(i_this, BDK_BCK_NUKENAI1, 2.0f, 0, 1.0f, -1, 0);
            i_this->mState = 5;
            i_this->m2EC[0] = cM_rndF(120.0f) + 30.0f;
            mDoAud_bgmStart(JA_BGM_UNK_110);
        }
        break;
    default:
        break;
    }
}

/* 000053C4-000057E8       .text start__FP9bdk_class */
void start(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();

    switch (i_this->mState) {
    case 0:
        if (player->current.pos.y >= 9800.0f && !player->checkPlayerFly()) {
            if (i_this->m2EC[0] == 0) {
                i_this->mState = 1;
                i_this->m25A0 = 10;
                i_this->m25A4 = 0;
                i_this->m25A6 = 0;
                fpcM_Search(&kamome_delete_sub, i_this);
                fpcM_Search(&dk_delete_sub, i_this);
                fpcM_Search(&kui_delete_sub, i_this);
                fpcM_Search(&sea_delete_sub, i_this);
                fpcM_Search(&obj_delete_sub, i_this);
                fpcM_Search(&bk_delete_sub, i_this);
                fpcM_Search(&boko_delete_sub, i_this);
                fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
            }
        } else {
            i_this->m2EC[0] = 0x14;
        }
        break;
    case 1:
        if (i_this->m25D8 != 0) {
            i_this->m25D8 = 0;
            i_this->mState = 2;
            i_this->m2F6 = REG0_S(6) + 0x19;
            actor->current.pos.y = REG0_F(10) + 8500.0f;
            actor->speed.y = REG0_F(12) + 80.0f;
            anm_init(i_this, BDK_BCK_S_DEMO1, 5.0f, 2, 1.0f, -1, 0);
            fopAcM_seStart(actor, JA_SE_CM_DK_ROUND_UP, 0);

            dComIfGp_particle_set(dPa_name::ID_SCENE_813C, &actor->current.pos, &actor->shape_angle, NULL,
            0xFF, &i_this->m61B0, (s8)fopAcM_GetRoomNo(actor),
            &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);
        }
        break;
    case 2:
        actor->current.pos.y += actor->speed.y;
        actor->speed.y -= REG0_F(13) + 1.0f;
        actor->current.angle.y += 0x1300;
        if (i_this->m25D8 != 0) {
            i_this->m25D8 = 0;
            i_this->mState = 3;
            anm_init(i_this, BDK_BCK_S_DEMO2, 5.0f, 0, 1.0f, BDK_BAS_S_DEMO2, 0);
            i_this->m2EC[0] = 0x2D;
        }
        break;
    case 3:
        if (i_this->m2EC[0] != 0) {
            actor->current.pos.y += actor->speed.y;
            actor->speed.y -= REG0_F(13) + 1.0f;
        }
        if (i_this->m2EC[0] == (s16)(REG8_S(8) + 5)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_DK_ENTER, 0);
            i_this->m61B0.remove();
            for (s32 i = 0; i < 2; i++) {
                JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8158, &actor->current.pos, &actor->shape_angle, NULL,
                0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
                &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);

                if (emitter) {
                    emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x16)); // j_dk_mune2 joint
                }
            }
        }
        cLib_addCalcAngleS2(&actor->current.angle.y,
        fopAcM_searchActorAngleY(actor, daPy_getPlayerActorClass()),
        10, 0x1300);
    default:
        break;
    }
}

/* 000057E8-00005EA0       .text end__FP9bdk_class */
void end(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1 = 0;
    u16 particle_id = 0;
    i_this->m1134 = 4000;
    i_this->m2F8 = 10;
    cXyz offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = 0.0f;

    switch(i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_LAST_DAMAGE1, 2.0f, 0, 1.0f, BDK_BAS_LAST_DAMAGE1, 0);
        i_this->mState = 5;
        i_this->m2EC[0] = 0xB3;
        particle_id = dPa_name::ID_SCENE_8139;
        break;
    case 1:
        anm_init(i_this, BDK_BCK_LAST_DAMAGE3, 2.0f, 0, 1.0f, BDK_BAS_LAST_DAMAGE3, 0);
        i_this->mState = 5;
        i_this->m2EC[0] = 0xB3;
        particle_id = dPa_name::ID_SCENE_815A;
        break;
    case 2:
        anm_init(i_this, BDK_BCK_LAST_DAMAGE2, 2.0f, 0, 1.0f, BDK_BAS_LAST_DAMAGE2, 0);
        i_this->mState = 5;
        i_this->m2EC[0] = 0;
        particle_id = dPa_name::ID_SCENE_8159;
        break;
    case 5:
        if (i_this->mpMorf->isStop()) {
            i_this->mState = 6;
            anm_init(i_this, BDK_BCK_DEATH1, 2.0f, 2, 1.0f, BDK_BAS_DEATH1, 0);
            i_this->m2EC[0] = REG0_S(3) + 300;

            for (s32 i = 0; i <= 1; i++) {
                JPABaseEmitter* emitter = dComIfGp_particle_set(
                dPa_name::ID_SCENE_813A, &actor->current.pos, NULL, NULL,
                0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
                &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);

                i_this->m6100[i] = emitter;
            }
        } else {
            if (i_this->m2EC[0] == 0) {
                cLib_addCalc2(&actor->current.pos.y, 10800.0f, 0.1f, 50.0f);
                bVar1 = 1;
            }
            break;
        }
        // Fall-through
    case 6:
        bVar1 = 1;
        for (s32 i = 0; i <= 1; i++) {
            JPABaseEmitter* emitter = i_this->m6100[i];
            if (emitter) {
                emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x28 + i * 0xA)); // j_dk_hane_l2 joint, j_dk_hane_r2 joint
            }
        }
        if (i_this->m2EC[0] == 0xAA) {
            i_this->m25A0 = 0x6E;
        }
        cLib_addCalc2(&actor->current.pos.x, 3600.0f, 0.05f, 50.0f);
        cLib_addCalc2(&actor->current.pos.y, REG8_F(18) + 15800.0f, 0.1f,
        REG8_F(19) + 20.0f);
        cLib_addCalc2(&actor->current.pos.z, -3800.0f, 0.05f, 50.0f);
        cLib_addCalcAngleS2(&actor->current.angle.y, -8000, 0x10, 0x80);
        if (i_this->m2EC[0] == 0x3C) {
            fopAcM_seStart(actor, JA_SE_CV_DK_DIE, 0);
            anm_init(i_this, BDK_BCK_DEATH2, 5.0f, 0, 1.0f, -1, 0);
        }
        if (i_this->m2EC[0] == 0 && REG0_S(4) == 0) {
            i_this->mState = 7;
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m90C); i++) {
                i_this->m90C[i] = 0;
            }
            fpcM_Search(&obj2_delete_sub, actor);
            i_this->m2CC = actor->current.pos;
            i_this->m2CC.y += 200.0f;
            actor->current.angle.y = 0x4000;
            fopAcM_createDisappear(actor, &i_this->m2CC, 0x32, 2);
            mDoAud_seStart(JA_SE_CM_DK_DIE_EXPLODE, &i_this->m2CC, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            i_this->m2EC[0] = 0x1E;

            for (s32 i = 0; i < 2; i++) {
                if (i_this->m6100[i]) {
                    i_this->m6100[i]->becomeInvalidEmitter();
                    i_this->m6100[i] = NULL;
                }
            }
            dComIfGp_particle_set(
            dPa_name::ID_SCENE_813B, &actor->current.pos, NULL, NULL,
            0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
            &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);
        }
        break;
    case 7:
        actor->current.pos.x = 100000.0f;
        actor->current.pos.y = 100000.0f;
        if (i_this->m2EC[0] == 0) {
            i_this->m25A0++;
            i_this->mState = 8;
        }
        break;
    case 8:
        break;
    default:
        break;
    }
    if (bVar1 != 0 && i_this->m2EC[4] == 0) {
        i_this->m2EC[4] = cM_rndF(30.0) + 25.0f;
        fopAcM_monsSeStart(actor, JA_SE_CV_DK_MODAE, 0);
    }
    cLib_addCalcAngleS2(&actor->current.angle.z, 0, 2, 0x800);
    cLib_addCalcAngleS2(&actor->current.angle.x, 0, 2, 0x800);
    if ((u16)particle_id) {
        JPABaseEmitter* emitter = dComIfGp_particle_set(
        dPa_name::ID_SCENE_8138, &actor->current.pos, &actor->shape_angle, NULL,
        0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
        &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);
        if (emitter) {
            emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x16)); // j_dk_mune2 joint
        }
        for (s32 i = 0; i <= 1; i++) {
            JPABaseEmitter* emitter = dComIfGp_particle_set(
            particle_id, &actor->current.pos, &actor->shape_angle, NULL,
            0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
            &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);

            if (emitter) {
                emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x28 + i * 0xA)); // j_dk_hane_l2 joint, j_dk_hane_r2 joint
            }
        }
    }
    return;
}

/* 00005EA0-00005F08       .text obj_s_sub__FPvPv */
void* obj_s_sub(void* param_1, void*) {
    fopAc_ac_c* actor = (fopAc_ac_c*)param_1;
    if (fopAc_IsActor(actor) && fopAcM_GetName(actor) == PROC_BDKOBJ && (fpcM_GetParam(actor) & 0xF) != 0xF && actor->health != 0) {
        return param_1;
    }
    return NULL;
}
/* 00005F08-000065FC       .text t_fly__FP9bdk_class */
void t_fly(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();
    s32 frame;
    cXyz pos;
    cXyz dist;
    i_this->mF10 = 1;
    fopAc_ac_c* bdkobj = (fopAc_ac_c*)fpcM_Search(&obj_s_sub, actor);
    f32 dVar12 = 0.0f;
    f32 dVar11 = -500.0f;
    f32 dVar10 = 20.0f;
    if (i_this->m2C4 == 100) {
        dComIfGs_onSwitch(0x80, fopAcM_GetRoomNo(actor));
        fpcM_Search(&kamome_delete_sub, actor);
    }

    switch(i_this->mState) {
    case -10:
        anm_init(i_this, BDK_BCK_TOBITATU1, 5.0f, 0, 1.0f, BDK_BAS_TOBITATU1, 0);
        i_this->mState++;
        break;
    case -9:
        if (i_this->mpMorf->isStop()) {
            i_this->mState = 0;
        }
        break;
    case 0:
        fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
        anm_init(i_this, BDK_BCK_FLY2, 5.0f, 2, 1.0f, BDK_BAS_FLY2, 0);
        i_this->mState++;
        // Fall-through
    case 1:
        if (bdkobj) {
            i_this->m2CC = bdkobj->current.pos;
            anm_init(i_this, BDK_BCK_ATTACK_T1, 5.0f, 0, 1.0f, -1, 0);
            i_this->mState++;
            fopAcM_monsSeStart(actor, JA_SE_CV_DK_ATTACK, 0);
            i_this->mp2598 = bdkobj;
        } else {
            i_this->m2CC = player->current.pos;
            if (i_this->m2EC[0] == 0) {
                anm_init(i_this, BDK_BCK_ATTACK_T2, 5.0f, 0, 1.0f, -1, 0);
                i_this->mState = 10;
                fopAcM_monsSeStart(actor, JA_SE_CV_DK_ATTACK, 0);
                fopAcM_seStart(actor, JA_SE_CM_DK_FOOT_ATTACK, 0);
                i_this->m2EC[0] = l_HIO.m028;
            }
        }
        break;
    case 2:
        frame = i_this->mpMorf->getFrame();
        if (frame >= REG0_S(3) + 0x2B && (s32)i_this->mpMorf->getFrame() <= REG0_S(4) + 0x32) {
            wind_set(i_this, &actor->current.pos);
            i_this->m2584 = 1;
            dVar11 = REG8_F(8) + 150.0f;
            dVar10 = 300.0f;
            if (i_this->mp2598 && (s32)i_this->mpMorf->getFrame() == 0x30) {
                fopAcM_SetParam(i_this->mp2598, 0xF);
                i_this->mp2598 = NULL;
                fopAcM_seStart(actor, JA_SE_CM_DK_PECK, 0);
            }
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mState = 0;
            i_this->m2E0 = 0.0f;
        }
        break;
    case 10:
        frame = i_this->mpMorf->getFrame();
        if (frame >= REG0_S(3) + 0x17 &&
        (s32)i_this->mpMorf->getFrame() <= (REG0_S(4) + 0x32)) {
            wind_set(i_this, &actor->current.pos);
            dVar12 = REG8_F(9) + -50.0f;
            dVar11 = REG8_F(10) + 250.0f;
            dVar10 = 300.0f;

            if ((s32)i_this->mpMorf->getFrame() <= REG0_S(5) + 0x23) {
                i_this->m2584 = 2;
            }
        }
        if (i_this->mFootCCSph[0].ChkAtHit() ||i_this->mFootCCSph[1].ChkAtHit()) {
            fopAcM_seStart(actor, JA_SE_CM_DK_FOOT_ATK_COL, 0);
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mState = 0;
            i_this->m2E0 = 0.0;
        }
        break;
    default:
        break;
    }

    pos = i_this->m2CC - center_pos;
    s16 angle = (s16)cM_atan2s(pos.x, pos.z);
    cLib_addCalcAngleS2(&actor->current.angle.y, angle, 10, 0x800);
    pos.x = 0.0;
    pos.y = dVar12;
    pos.z = dVar11 + -450.0f;
    cMtx_YrotS(*calc_mtx, angle);
    cMtx_XrotM(*calc_mtx, REG8_S(4));
    MtxPosition(&pos, &dist);
    cLib_addCalc2(&actor->current.pos.x, i_this->m2CC.x + dist.x, 0.2f, dVar10 * i_this->m2E0);

    if (actor->speed.y > 0.0f) {
        actor->current.pos.y = actor->current.pos.y + actor->speed.y;
        actor->speed.y = actor->speed.y - 5.0f;
    }
    else {
        cLib_addCalc2(&actor->current.pos.y, i_this->m2CC.y + dist.y, 0.2f, dVar10 * i_this->m2E0);
    }

    cLib_addCalc2(&actor->current.pos.z, i_this->m2CC.z + dist.z, 0.2f, dVar10 * i_this->m2E0);
    cLib_addCalc2(&i_this->m2E0, 1.0f, 1.0f, 0.02f);

    if (player->current.pos.y > REG0_F(3) + 9300.0f - 50.0f) {
        i_this->mAction = ACTION_T_LASTATTACK;
        i_this->mState = 0;
    }
}

/* 000065FC-00006680       .text t_landing__FP9bdk_class */
void t_landing(bdk_class* i_this) {
    i_this->mF10 = 1;
    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_TOBITATU_T1, 5.0f, 2, 1.0f, -1, 0);
        i_this->mState++;
        break;
    case 1:
        break;
    default:
        break;
    }
    pos_move(i_this);
}

/* 00006680-00006C10       .text t_lastattack__FP9bdk_class */
void t_lastattack(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)daPy_getPlayerActorClass();

    f32 fVar1;
    f32 fVar2;
    f32 fVar3;

    s8 isfalling = 0;

    fVar2 = (REG0_F(9) * 0.01f) + -3872.0f;
    fVar1 = (REG0_F(8) * 0.01f) + 9579.0f;
    i_this->m2CC.x = REG0_F(7) * 0.01f + 2825.0f - 40.0f;
    i_this->m2CC.y = fVar1;
    i_this->m2CC.z = fVar2;
    cLib_addCalc2(&actor->current.pos.x, i_this->m2CC.x, 0.5f, 30.0f);
    cLib_addCalc2(&actor->current.pos.z, i_this->m2CC.z, 0.5f, 30.0f);
    actor->current.pos.y += actor->speed.y;
    actor->speed.y = actor->speed.y - 5.0f;
    if (actor->current.pos.y <= i_this->m2CC.y) {
        actor->current.pos.y = i_this->m2CC.y;
        actor->speed.y = -1.0f;
        isfalling = 1;
    }

    s16 angle = fopAcM_searchActorAngleY(actor, daPy_getPlayerActorClass()) -0x8000;
    if (angle < -0xEB8) {
        angle = -0xEB8;
    }
    else if (0xE8 < angle) {
        angle = 0xE8;
    }
    cLib_addCalcAngleS2(&actor->current.angle.y, angle + 0x8000, 2, 0x800);

    switch (i_this->mState) {
    case 0:
        actor->speed.y = REG0_F(6) + 80.0f;
        i_this->mState++;
        anm_init(i_this, BDK_BCK_TYAKUTI_T1, 10.0f, 0, 0.001f, BDK_BAS_TYAKUTI_T1, 0);
        break;
    case 1:
        if (!(s8)isfalling) {
            break;
        }

        anm_init(i_this, BDK_BCK_TYAKUTI_T1, 1.0f, 0, 1.0f, BDK_BAS_TYAKUTI_T1, 0);
        i_this->mState++;
        dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        dComIfGp_particle_set(
            dPa_name::ID_SCENE_8131, &actor->current.pos, NULL, NULL,
            0xFF, NULL, (s8)fopAcM_GetRoomNo(actor),
            &i_this->m6224.mColorK0, &i_this->m6224.mColorK0);

        if (i_this->m6078[0] == 0) {
            i_this->m6078[0] = 100;

        dComIfGp_particle_setToon(
            dPa_name::ID_SCENE_A132, &actor->current.pos, NULL, NULL, 0xB9,
            &i_this->m6080[0], (s8)fopAcM_GetRoomNo(actor));
        }
        break;
    case 2:
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BDK_BCK_WAIT_T1, 5.0, 2, 1.0f, -1, 0);
            i_this->mState++;
        }
        break;
    case 3:
        if (i_this->m2EC[0] == 0 &&
        fopAcM_searchActorDistance(actor, daPy_getPlayerActorClass()) < REG0_F(13) + 700.0f) {
            anm_init(i_this, BDK_BCK_ATTACK_T3, 5.0f, 0, 1.0f, -1, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_DK_ATTACK, 0);
            i_this->mState = 4;
        }
        break;
    case 4:
        fVar3 = i_this->mpMorf->getFrame();
        if (fVar3 > 10.0f && fVar3 < 15.0f) {
            i_this->m2584 = 1;
        }

        if ((s16)(REG0_S(5) + 0xD) == (s16)i_this->mpMorf->getFrame()) {
            fopAcM_seStart(actor, JA_SE_CM_DK_PECK, 0);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            eff_hane_set(i_this, &i_this->m1168, 5, 0);
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BDK_BCK_WAIT_T1, 5.0f, 2, 1.0f, -1, 0);
            i_this->mState = 3;
            i_this->m2EC[0] = cM_rndF(100.0f) + 100.0f;
        }
        break;
    default:
        break;
    }
    if (player->current.pos.y < REG0_F(3) + 9290.0f - 50.0f) {
        i_this->mAction = ACTION_T_FLY;
        i_this->mState = -10;
        actor->speed.y = REG0_F(7) + 70.0f;
    }
}

/* 00006C10-00007008       .text t_down__FP9bdk_class */
void t_down(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz offset;

    switch (i_this->mState) {
    case 0:
        anm_init(i_this, BDK_BCK_TO_DAMAGE_T1, 2.0f, 0, 1.0f, -1, 0);
        i_this->mState++;
        i_this->m2EC[0] = REG0_S(6) + 0x50;
        i_this->m2EC[1] = REG0_S(7) + 0x50;
        i_this->m25A0 = 0x32;
        fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
        eff_hane_set(i_this, &i_this->m1168, 5, 0);
        dComIfGs_offSwitch(0x80, fopAcM_GetRoomNo(actor));
        i_this->m259E = 0xB4;
        // Fall-through
    case 1:
    case 2:
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BDK_BCK_DAMAGE_T1, 2.0f, 2, 1.0f, -1, 0);
        }
        cLib_addCalc2(&actor->current.pos.x, center_pos.x, 0.2f, REG0_F(4) + 10.0f);
        cLib_addCalc2(&actor->current.pos.z, center_pos.z, 0.2f, REG0_F(4) + 10.0f);

        cLib_addCalcAngleS2(&i_this->m259E, 1, 1, 2);
        if (i_this->m2EC[1] == 1) {
            anm_init(i_this, BDK_BCK_RAKKA_T1, REG0_F(6) + 20.0f, 2, 1.0f, -1, 0);
            i_this->m259E = 1;
            fopAcM_seStart(actor, JA_SE_CM_DK_FALL_WATER, 0);
        }

        if (i_this->m2EC[0] != 0) {
            return;
        }
        actor->current.pos.y += actor->speed.y;
        actor->speed.y -= 5.0f;
        if (actor->current.pos.y < 6900.0f && i_this->mState == 1) {
            i_this->mState = 2;

            offset.x = 3600.f;
            offset.y = 6900.f;
            offset.z = -3800.f;

            dComIfGp_particle_set(dPa_name::ID_SCENE_8147, &offset, NULL, NULL);
            dComIfGp_particle_set(dPa_name::ID_SCENE_8148, &offset, NULL, NULL);
            dComIfGp_particle_set(dPa_name::ID_SCENE_8149, &offset, NULL, NULL);
            dComIfGp_particle_set(dPa_name::ID_SCENE_814A, &offset, NULL, NULL);
            fopAcM_seStart(actor, JA_SE_CM_DK_WATER_COLUMN, 0);
        }
        if (actor->current.pos.y < 5500.0f) {
            i_this->mAction = ACTION_START;
            i_this->mState = 0;
            actor->current.pos.y = -25000.0f;
            actor->health = 20;
            actor->max_health = 20;
        }
        break;
    default:
        break;
    }

}

/* 00007008-00007014       .text after_fight__FP9bdk_class */
void after_fight(bdk_class* i_this) {
    i_this->m2F8 = 10;
}

/* 00007014-00007218       .text move__FP9bdk_class */
void move(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    switch (i_this->mAction) {
    case ACTION_FLY:
        fly(i_this);
        break;
    case ACTION_UP_FLY:
        up_fly(i_this);
        break;
    case ACTION_LANDING:
        landing(i_this);
        break;
    case ACTION_WAIT:
        wait(i_this);
        break;
    case ACTION_JUMP:
        jump(i_this);
        break;
    case ACTION_KUTI_ATTACK:
        kuti_attack(i_this);
        break;
    case ACTION_JIDA_ATTACK:
        jida_attack(i_this);
        break;
    case ACTION_FLY_ATTACK:
        fly_attack(i_this);
        break;
    case ACTION_WIND_ATTACK:
        wind_attack(i_this);
        break;
    case ACTION_KAMEN_DEMO:
        kamen_demo(i_this);
        break;
    case ACTION_END:
        end(i_this);
        break;
    case ACTION_START:
        start(i_this);
        break;
    case ACTION_T_FLY:
        t_fly(i_this);
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
        break;
    case ACTION_T_LANDING:
        t_landing(i_this);
        break;
    case ACTION_T_LASTATTACK:
        t_lastattack(i_this);
        break;
    case ACTION_T_DOWN:
        t_down(i_this);
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
        break;
    case ACTION_AFTER_FIGHT:
        after_fight(i_this);
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
        break;
    default:
        break;
    }

    if (i_this->m2591 != 0) {
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, i_this->m2588, 20.0f, i_this->m2590, 1.0f, i_this->m258C, 0);
            i_this->m2591 = 0;
        }
    }
}

/* 00007218-00007684       .text col_set__FP9bdk_class */
void col_set(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz offset;
    cXyz dist;
    J3DModel* model;

    i_this->m1168 = actor->current.pos;
    i_this->m1168.y += 380.0f;
    model = i_this->mpMorf->getModel();
    MTXCopy(model->getAnmMtx(0x18), *calc_mtx); // j_dk_atama1 joint

    offset.x = REG8_F(0) + 40.0f;
    offset.y = REG8_F(1);
    if (i_this->m8F8 >= 4) {
        offset.z = 0.0f;
        i_this->mHeadTgSph.SetR(80.0f);
    } else {
        offset.z = REG8_F(2) + -70.0f;
        i_this->mHeadTgSph.SetR(110.0f);
    }

    i_this->m1144 = i_this->m1150;
    MtxPosition(&offset, &i_this->m1150);
    if (i_this->m2584 == 1) {
        model = i_this->mpMorf->getModel();
        MTXCopy(model->getAnmMtx(0x19), *calc_mtx); // j_dk_ago joint
        offset.x = REG8_F(3) + 120.0f;
        offset.y = REG8_F(4);
        offset.z = REG8_F(5);
        MtxPosition(&offset, &i_this->m115C);
    } else {
        i_this->m115C.y = -10000.0f;
    }
    i_this->mHeadAtSph.SetR(REG8_F(6) + 70.0f);
    i_this->mBodyCCSph.SetR(REG8_F(8) + 250.0f);
    i_this->mHeadAtSph.SetC(i_this->m115C);
    i_this->mHeadTgSph.SetC(i_this->m1150);
    i_this->mBodyCCSph.SetC(i_this->m1168);
    dComIfG_Ccsp()->Set(&i_this->mHeadAtSph);
    dComIfG_Ccsp()->Set(&i_this->mHeadTgSph);
    dComIfG_Ccsp()->Set(&i_this->mBodyCCSph);

    if (4 <= i_this->m8F8) {
        model = i_this->mpMorf->getModel();
        MTXCopy(model->getAnmMtx(REG8_S(2) + 0x21), *calc_mtx); // j_dk_tosaka_A3 joint

        offset.x = REG8_F(3);
        offset.y = REG8_F(4);
        offset.z = REG8_F(5);
        MtxPosition(&offset, &dist);
        i_this->mTosakaTgSph.SetR(REG8_F(11) + 80.0f);
        i_this->mTosakaTgSph.SetC(dist);
        dComIfG_Ccsp()->Set(&i_this->mTosakaTgSph);
    }
    for (s32 i = 0; i < 2; i++) {
        if (i == 0) {
            model = i_this->mpMorf->getModel();
            MTXCopy(model->getAnmMtx(0x5), *calc_mtx); // j_dk_ashi_l3 joint
        } else {
            model = i_this->mpMorf->getModel();
            MTXCopy(model->getAnmMtx(0xE), *calc_mtx); // j_dk_ashi_r3 joint
        }
        if (i_this->mAction == ACTION_T_LASTATTACK) {
            i_this->mFootCCSph[i].SetR(REG0_F(8) + 300.0f);
            i_this->mFootCCSph[i].OffTgSetBit();
            offset.x = REG0_F(3) + 100.0f;
            offset.y = REG0_F(4) + 200.0f;
        } else {
            i_this->mFootCCSph[i].SetR(REG0_F(9) + 60.0f);
            i_this->mFootCCSph[i].OnTgSetBit();
            offset.x = REG0_F(3) + 50.0f;
            offset.y = REG0_F(4);
        }
        offset.z = REG0_F(5);
        MtxPosition(&offset, &i_this->m1174[i]);
        i_this->mFootCCSph[i].SetC(i_this->m1174[i]);

        if (i_this->m2584 == 2) {
            i_this->mFootCCSph[i].OnAtSetBit();
            s16 action = i_this->mAction;
            if (action == ACTION_FLY_ATTACK || action == ACTION_T_FLY || action == ACTION_JIDA_ATTACK) {
                i_this->mFootCCSph[i].SetAtSpl(dCcG_At_Spl_UNK9);
            } else {
                i_this->mFootCCSph[i].SetAtSpl(dCcG_At_Spl_UNK0);
            }
            if (i_this->m2585 == 0) {
                i_this->mFootCCSph[i].StartCAt(i_this->m1174[i]);
                i_this->m2585++;
            } else {
                i_this->mFootCCSph[i].MoveCAt(i_this->m1174[i]);
            }
        } else {
            i_this->mFootCCSph[i].OffAtSetBit();
            i_this->m2585 = 0;
        }
        dComIfG_Ccsp()->Set(&i_this->mFootCCSph[i]);
    }
}

/* 00007684-000078AC       .text kankyo_cont__FP9bdk_class */
void kankyo_cont(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m25DC = actor->current.pos;
    cXyz local_38(0.0f, 0.0f, 1.0f);
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    MtxPosition(&local_38, &i_this->m25E8);

    i_this->m25F4.x = i_this->m2608 * 2000.0f;
    i_this->m25F4.z = 0.0f;
    cLib_addCalc0(&i_this->m2608, 1.0f, 0.02f);

    if (i_this->m2608 > 1.0f) {
        i_this->m25F4.y = 1.0f;
    } else {
        i_this->m25F4.y = 0.0f;
    }
    static cXyz non_pos;
    non_pos.x = 0.0f;
    non_pos.y = -10000.0f;
    non_pos.z = 10000.0f;

    for (s32 i = 0; i < 10; i++) {
        if (i_this->m2488[i] != 0) {
            i_this->m2494[i] += i_this->m250C[i];

            if (i_this->m2B4 == 1) {
                i_this->mWindAtSph[i].SetR(REG8_F(7) + 600.0f);
            } else {
                i_this->mWindAtSph[i].SetR(REG8_F(6) + 300.0f);
            }

            if (i_this->m2488[i] == 1) {
                i_this->mWindAtSph[i].StartCAt(i_this->m2494[i]);
            } else {
                i_this->mWindAtSph[i].MoveCAt(i_this->m2494[i]);
            }

            i_this->m2488[i]++;
            if (i_this->m2488[i] > 25) {
                i_this->m2488[i] = 0;
            }
        } else {
            i_this->mWindAtSph[i].SetC(non_pos);
        }
        dComIfG_Ccsp()->Set(&i_this->mWindAtSph[i]);
    }
}
static f32 g_d[] = {9820.0f, 9820.0f, 9820.0f, 9820.0f};
static s16 z_d[] = {0x2000, 0x2000, -0x2000, -0x2000};
static s16 z_d2[] = {-0x1000, -0x1000, 0x1000, 0x1000};

/* 000078AC-00008520       .text kamen_break_move__FP9bdk_class */
void kamen_break_move(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    static cXyz non_pos(-50000.0f, -50000.0f, -50000.0f);
    CcAtInfo hit_atInfo;
    dBgS_GndChk gndChk;
    dBgS_LinChk linChk;
    cXyz vec1;
    cXyz vec2;
    cXyz vec3;
    cXyz vec4;
    cXyz vec5;

    s16 rot1;
    s16 rot2;

    for (s32 i = 0; i < 4; i++) {
        if (i_this->m90C[i] != 0) {
            rot2 = 0;
            rot1 = 0;

            if (i_this->m9E8[i] == 0) {
                i_this->m940[i] = i_this->m910[i];
                i_this->m910[i] += i_this->m970[i];
                i_this->m970[i].y -= 5.0f;

                if (i_this->m910[i].y < 8000.0f) {
                    i_this->m90C[i] = 0;
                }

                vec3 = i_this->m910[i];
                vec3.y += 200.0f;

                gndChk.SetPos(&vec3);
                f32 ground_y = dComIfG_Bgsp()->GroundCross(&gndChk) + 15.0f + REG0_F(11);
                if (i_this->m910[i].y <= ground_y) {
                    i_this->m910[i].y = ground_y;
                    csXyz* m9D0 = &i_this->m9D0[i];
                    m9D0->x = 0;
                    m9D0->y = 0;

                    if (i_this->m970[i].y < REG0_F(2) + -30.0f) {
                        i_this->m970[i].y = 4.0f + (10.0f + REG0_F(3));
                        i_this->m9EC[i] = REG0_F(4) + 3000.0f;
                        i_this->m9A0[i].z = z_d2[i];
                        mDoAud_seStart(JA_SE_CM_MAGBALL_BOUND, &i_this->m910[i], 0x63, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    } else {
                        i_this->m970[i].y = 0.0f;
                        s32 target = i_this->m9EC[i] * cM_ssin(i_this->m2C4 * + 0x2000 + i * 0x3000);
                        cLib_addCalc0(&i_this->m9EC[i], 1.0f, 200.0f + REG0_F(5));
                        cLib_addCalcAngleS2(&i_this->m9A0[i].z, z_d[i] + target, 1, 0x1000);
                    }
                    vec1.x = 0.0f;
                    vec1.y = 0.0f;
                    vec1.z = i_this->m9FC[i];
                    cMtx_YrotS(*calc_mtx, i_this->mA0C[i]);
                    MtxPosition(&vec1, &vec2);

                    i_this->m970[i].x = vec2.x;
                    i_this->m970[i].z = vec2.z;
                    i_this->m9A0[i].y += (s16)(i_this->mF00[i] * i_this->m9FC[i]);

                    cLib_addCalc0(&i_this->m9FC[i], 1.0f, REG0_F(5) + 0.2f);

                    if (i_this->mA50[i].ChkTgHit() && i_this->m9FC[i] < 1.0f) {
                        hit_atInfo.mpObj = i_this->mA50[i].GetTgHitObj();
                        hit_atInfo.mpActor = at_power_check(&hit_atInfo);

                        if (hit_atInfo.mResultingAttackType == 8) {
                            i_this->m9FC[i] = REG0_F(4) + 7.0f + cM_rndF(2.0f);
                            if (hit_atInfo.mpActor) {
                                i_this->mA0C[i] = hit_atInfo.mpActor->shape_angle.y + (s16)cM_rndFX(2000.0f);
                            }
                            i_this->mF00[i] = (s16)cM_rndFX(200.0f);
                        } else {
                            cXyz* hitpos = i_this->mA50[i].GetTgHitPosP();
                            vec1 = i_this->m910[i] - *hitpos;
                            cMtx_YrotS(*calc_mtx, (s16)cM_atan2s(vec1.x, vec1.z));

                            if (hit_atInfo.mResultingAttackType == 1) {
                                vec1.set(0.0f, cM_rndF(5.0f) + 5.0f, cM_rndF(5.0f) + 5.0f);
                                i_this->m9D0[i].y = cM_rndFX(1000.0f);
                            } else {
                                vec1.set(0.0f, cM_rndF(10.0f) + 30.0f, cM_rndF(5.0f) + 10.0f);
                                i_this->m9D0[i].y = cM_rndFX(3000.0f);
                                i_this->m9D0[i].x = cM_rndFX(3000.0f);
                            }

                            MtxPosition(&vec1, &i_this->m970[i]);
                            i_this->m9FC[i] = 0.0f;
                            mDoAud_seStart(JA_SE_CM_MAGBALL_BOUND, &i_this->m910[i], 0x63, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                        }
                    }
                    cLib_addCalcAngleS2(&i_this->m9A0[i].x, 0x4000, 1, 0x2000);
                    i_this->mA50[i].SetC(i_this->m910[i]);
                    dComIfG_Ccsp()->Set(&i_this->mA50[i]);
                }
                vec1 = i_this->m910[i] - i_this->m940[i];
                if (vec1.abs() > 0.0f) {
                    cMtx_YrotS(*calc_mtx, cM_atan2s(vec1.x, vec1.z));
                    vec1.x = 0.0f;
                    vec1.y = 30.0f;
                    vec1.z = 20.0f;
                    MtxPosition(&vec1, &vec2);

                    vec4 = i_this->m910[i];
                    vec4.y += 30.0f;

                    vec5 = i_this->m910[i] + vec2;

                    linChk.Set(&vec4, &vec5, actor);
                    if (dComIfG_Bgsp()->LineCross(&linChk)) {
                        i_this->m910[i].x = i_this->m940[i].x;
                        i_this->m910[i].z = i_this->m940[i].z;
                        i_this->m9D0[i] = csXyz(0, 0, 0);
                        i_this->m9FC[i] = 0.0f;
                    }
                }
            } else {
                i_this->m9E8[i]--;
                if (i_this->m9E8[i] < 0x14) {
                    rot1 = cM_ssin(i_this->m9E8[i] * 3300) * 200.0f;
                    rot2 = cM_scos(i_this->m9E8[i] * 4800) * 200.0f;
                }
            }
            MtxTrans(i_this->m910[i].x, i_this->m910[i].y, i_this->m910[i].z, FALSE);
            cMtx_YrotM(*calc_mtx, i_this->m9A0[i].y + i_this->m9B8[i].y);
            cMtx_ZrotM(*calc_mtx, i_this->m9A0[i].z + rot2);
            cMtx_XrotM(*calc_mtx, i_this->m9B8[i].x + (i_this->m9A0[i].x + rot1));
            i_this->m9B8[i] += i_this->m9D0[i];
            MtxTrans(kamen_break_off_x[i], kamen_break_off_y[i], kamen_break_off_z[i], TRUE);
            i_this->m8FC[i]->setBaseTRMtx(*calc_mtx);
        } else {
            i_this->mA50[i].SetC(non_pos);
            dComIfG_Ccsp()->Set(&i_this->mA50[i]);
        }
    }
}

/* 00008AF0-00008CB8       .text obj_move__FP9bdk_class */
void obj_move(bdk_class* i_this) {
    if (dComIfGs_isStageBossEnemy()) {
        cLib_addCalc2(&i_this->m62D4, -500.0f, 1.0f, 20.0f);
    }
    MtxTrans(REG0_F(10) + 4600.0f + 155.0f, REG0_F(11) + 9800.0f + i_this->m62D4, REG0_F(12) - 4700.0f, 0);
    cMtx_YrotM(*calc_mtx, (REG0_S(0) + -7000));
    i_this->mp62D8->setBaseTRMtx(*calc_mtx);
    MTXCopy(*calc_mtx, i_this->m62DC);
    i_this->pm_bgw->Move();
    MtxTrans(3595.0f, i_this->m6324 + 9800.0f + REG8_F(2), -3820.0f, 0);
    for (s32 i = 0; i < 3; i++) {
        MtxRotY(M_PI * 2 / 3, 1);
        MtxPush();
        MtxRotY(i_this->m631C, 1);
        MtxTrans(0.0f, 0.0f, i_this->m6320 + REG8_F(3), 1);
        i_this->mp6310[i]->setBaseTRMtx(*calc_mtx);
        MTXCopy(*calc_mtx, i_this->m632C[i]);
        i_this->mp63BC[i]->Move();
        MtxPull();
    }
}

/* 00008CB8-0000A7C8       .text demo_camera__FP9bdk_class */
void demo_camera(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    csXyz local_14C;
    csXyz local_154;

    cXyz local_104;
    cXyz local_108;
    cXyz local_e4;
    cXyz local_f0;

    f32 dVar16  = 45.0f;
    f32 dVar15 = 1.0f;
    f32 dVar14 = 0.05f;

    u8 r28 = 1;
    u8 r27 = 0;

    switch (i_this->m25A0) {
    case 0x0:
        break;
    case 0x1:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtType_OTHER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            r28 = 0;
            break;
        }

        i_this->m25A0++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m25A4 = 0;
        i_this->m25A6 = 0;
        i_this->m25C8 = dVar16;
        i_this->m8F8 = 4;
        player->changeOriginalDemo();
    case 0x2: {
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);

        local_104.x = REG0_F(0) + -30.0f - 50.0f;
        local_104.y = REG0_F(1) + -30.0f;
        local_104.z = REG0_F(2) + 50.0f;
        MtxPosition(&local_104, &i_this->m25B4);
        i_this->m25B4 += i_this->m1150;

        local_104.x = REG0_F(5) + 400.0f;
        local_104.y = REG0_F(6) + -100.0f;
        local_104.z = REG0_F(7) + 400.0f;
        MtxPosition(&local_104, &i_this->m25A8);
        i_this->m25A8 += i_this->m1150;

        local_104.x = (REG0_F(0) + -150.0f) - 30.0f - 50.0f;
        local_104.y = 0.0f;
        local_104.z = REG0_F(2) + 100.0f + 10.0f;
        MtxPosition(&local_104, &local_108);

        local_108.x += i_this->m1150.x;
        local_108.y = player->current.pos.y;
        local_108.z += i_this->m1150.z;
        player->setPlayerPosAndAngle(&local_108, actor->shape_angle.y + 20000 + REG0_S(6));

        s16 r4 = i_this->m25A6;
        if (i_this->m25A6 > REG0_S(7) + 0x3C) {
            dVar16 = 20.0f;
            dVar15 = 1.0f;
            dVar14 = 0.5f;
        } else if ((s16)r4 > 0) {
            dVar16 = 35.0f;
            dVar15 = 0.35f;
        }
        if (r4 == 0x51) {
            player->changeDemoMode(daPy_demo_c::DEMO_SMILE_e);
        }
        cLib_addCalc2(&i_this->m25C8, dVar16, dVar14, dVar15);
        break;
    }
    case 0xA:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtType_OTHER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            r28 = 0;
            break;
        }
        i_this->m25A0++;
        i_this->m25CC = 0.0f;
        i_this->m25A4 = 0;
        i_this->m25A6 = 0;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m25C8 = 55.0f;

        i_this->m25B4.x = 2598.0f;
        i_this->m25B4.y = 9902.0f;
        i_this->m25B4.z = -3498.0f;

        i_this->m25A8.x = 2228.0f;
        i_this->m25A8.y = 9961.0f;
        i_this->m25A8.z = -3403.0f;

        mDoAud_bgmStreamPrepare(JA_STRM_DK_START);
        player->changeOriginalDemo();
        // Fall-through
    case 0xB:
        cLib_addCalc2(&i_this->m25B4.x, 164.0f, 0.05f, i_this->m25CC * 24.34f);
        cLib_addCalc2(&i_this->m25B4.y, 11617.0f, 0.05f, i_this->m25CC * 17.15f);
        cLib_addCalc2(&i_this->m25B4.z, -2802.0f, 0.05f, i_this->m25CC * 6.96f);
        cLib_addCalc2(&i_this->m25A8.x, -167.0f, 0.05f, i_this->m25CC * 23.949999f);
        cLib_addCalc2(&i_this->m25A8.y, 11791.0f, 0.05f, i_this->m25CC * 18.3f);
        cLib_addCalc2(&i_this->m25A8.z, -2706.0f, 0.05f, i_this->m25CC * 6.97f);

        if (i_this->m25A6 > (s16)(REG0_S(1) + 0x1E)) {
            cLib_addCalc2(&i_this->m25CC, REG0_F(1) + 1.0f, 1.0f, REG0_F(2) + 0.015f);
        }

        if (i_this->m25A6 >= (s16)(REG0_S(6) + 0xBE)) {
            if (i_this->m25A6 == (s16)(REG0_S(6) + 0xD2)) {
                player->changeDemoMode(daPy_demo_c::DEMO_UNK_028_e);
                mDoAud_bgmStreamPlay();
            }
            if (i_this->m25A6 == (s16)(REG0_S(6) + 0xBE)) {

                local_14C.x = 0;
                local_14C.y = 0;
                local_14C.z = 0;
                for (s32 i = 0; i <= 2; i++) {
                    local_14C.y = 10000 + i * 0x5555 + REG8_S(4);
                    dComIfGp_particle_setToon(dPa_name::ID_SCENE_A14F, &center_pos, &local_14C, NULL, 0xB9, &i_this->m6130[i], (s16)fopAcM_GetRoomNo(actor));
                }
                dComIfGp_particle_setToon(dPa_name::ID_SCENE_A150, &center_pos2, NULL, NULL, 0xB9, &i_this->m6130[3], (s16)fopAcM_GetRoomNo(actor));
                i_this->m6100[1] = dComIfGp_particle_set(dPa_name::ID_SCENE_814E, &center_pos2, NULL, NULL, 0xFF);
            }
            i_this->m25D4 = REG0_F(18) + 1.5f;
            mDoAud_seStart(JA_SE_ATM_MJT_JINARI, 0);
            cLib_addCalc0(&i_this->m6320, 1.0f, REG0_F(0) + 1.0f);
            i_this->m631C += 0.003f + REG0_F(8);
            r27 = 1;
        }
        if (i_this->m25A6 > (s16)(REG0_S(2) + 0xFA)) {
            i_this->m25A0 = 0xC;
            i_this->m25B4.x = 2195.0f;
            i_this->m25B4.y = 10007.0f;
            i_this->m25B4.z = -4079.0f;

            i_this->m25A8.x = 1816.0f;
            i_this->m25A8.y = 10051.0f;
            i_this->m25A8.z = -4137.0f;
            i_this->m25CC = 0.0f;
            i_this->m25A6 = 0;
        } else {
            local_108.x = 2580.0f;
            local_108.y = player->current.pos.y;
            local_108.z = -3670.0f;
            player->setPlayerPosAndAngle(&local_108, player->shape_angle.y);
            break;
        }
        // Fall-through
    case 0xC:
        cLib_addCalc0(&i_this->m6320, 1.0f, REG0_F(0) + 1.0f);
        r27 = 1;
        i_this->m631C += REG0_F(8) + 0.003f;

        if (i_this->m25A6 < (s16)(REG0_S(6) + 0x9B)) {
            i_this->m25D4 = REG0_F(5) + 5.0f;
            mDoAud_seStart(JA_SE_ATM_MJT_JINARI, 0);
        }
        if (i_this->m25A6 == (s16)(REG0_S(6) + 0x96)) {
            i_this->m25D8 = 1;
        }
        if (i_this->m25A6 == (s16)(REG0_S(7) + 0xA0)) {
            i_this->m25A6 = 0;
            i_this->m25A0 = 0xD;
        }
        cLib_addCalc2(&i_this->m25B4.x, 2682.0f, 0.05f, i_this->m25CC * 4.87f);
        cLib_addCalc2(&i_this->m25B4.y, 9904.0f, 0.05f, i_this->m25CC * 1.03f);
        cLib_addCalc2(&i_this->m25B4.z, -3600.0f, 0.05f, i_this->m25CC * 4.79f);
        cLib_addCalc2(&i_this->m25A8.x, 2308.0f, 0.05f, i_this->m25CC * 4.92f);
        cLib_addCalc2(&i_this->m25A8.y, 9961.0f, 0.05f, i_this->m25CC * 0.9f);

        cLib_addCalc2(&i_this->m25A8.z, -3524.0f, 0.05f, i_this->m25CC * 6.1299998f);
        cLib_addCalc2(&i_this->m25CC, REG0_F(3) + 1.5f, 1.0f, REG0_F(4) + 0.02f);

        local_108.x = 2580.0f;
        local_108.y = player->current.pos.y;
        local_108.z = -3670.0f;
        player->setPlayerPosAndAngle(&local_108, 18000);
        break;
    case 0xD:
        if (i_this->m25A6 < (s16)(REG0_S(3) + 0x64)) {
            cLib_addCalc2(&i_this->m25C8, 25.0f, 0.1f, 0.5f);
        } else {
            cLib_addCalc2(&i_this->m25C8, 55.0f, 0.2f, 3.0f);
        }
        if (i_this->m25A6 == (s16)(REG0_S(8) + 0x37)) {
            i_this->m25D8 = 1;
        }
        cLib_addCalc2(&i_this->m25B4.x, i_this->m1150.x, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m25B4.y, (i_this->m1150.y - 200.0f) + REG0_F(11), 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m25B4.z, i_this->m1150.z, 0.1f, 50.0f);


        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, BDK_BCK_FLY3, 1.0f, 2, 1.0f, BDK_BAS_FLY3, 0);
            player->changeDemoMode(daPy_demo_c::DEMO_A_WAIT_e);
            player->changeDemoParam0(2);
        }

        if (i_this->m25A6 == (s16)(REG0_S(8) + 0xF0)) {
            i_this->m25A6 = 0;
            i_this->m25A0 = 0xE;
        }
        r27 = 1;
        break;
    case 0xE:
        i_this->m25B4.x = 3304.0f;
        i_this->m25B4.y = 10983.0f;
        i_this->m25B4.z = -3644.0f;

        i_this->m25A8.x = 2841.0f;
        i_this->m25A8.y = 13058.0f;
        i_this->m25A8.z = -3272.0f;

        i_this->m25A0 = 0xF;
        i_this->m25A6 = 0;
        i_this->m25CC = 0.0f;
        i_this->m6320 = REG0_F(17) + -100.0f;
        i_this->m631C = 0.0f;
    case 0xF:
        r27 = 1;
        // Fall-through
    case 0x10:
        cLib_addCalc0(&i_this->m6320, 1.0f, REG0_F(11) + 1.5f);
        if (std::fabsf(i_this->m6320) < 1.0f) {
            cLib_addCalc0(&i_this->m6324, 1.0f, REG0_F(12) + 1.0f);
            if (i_this->m25A0 == 0xF) {
                dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0401);
                dComIfGs_onStageBossDemo();
                fpcM_Search(ep_delete_sub, actor);

                mDoAud_seStart(JA_SE_ATM_MJT_SHUTTER_END, &center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));

                r27 = 0;
                i_this->m25A0 = 0x10;

                local_154.x = 0;
                local_154.y = 0;
                local_154.z = 0;
                dPa_smokeEcallBack* a;
                s32 i = 0;

                for (i = 0; i <= 2; i++) {
                    a = &i_this->m6130[i];
                    local_154.y = i * 0x5555;
                    dComIfGp_particle_setToon(dPa_name::ID_SCENE_A151, &center_pos,
                    &local_154, NULL, 0xB9, a, (u8)fopAcM_GetRoomNo(actor));
                }
                i_this->m6130[3].remove();

                if (i_this->m6100[1]) {
                    i_this->m6100[1]->becomeInvalidEmitter();
                    i_this->m6100[1] = NULL;
                }
            }
        }
        cLib_addCalc2(&i_this->m25A8.x, 3152.0f, 0.05f, i_this->m25CC * 3.11f);
        cLib_addCalc2(&i_this->m25A8.z, -3070.0f, 0.05f, i_this->m25CC * 2.02f);
        cLib_addCalc2(&i_this->m25CC, REG0_F(3) + 1.2f, 1.0f, REG0_F(4) + 0.015f);

        if (i_this->m25A6 == 0xA0) {
            i_this->m25A0 = 0x96;
            i_this->mAction = ACTION_FLY;
            i_this->m2CA = -1;
            i_this->mState = 0;

            actor->gravity = REG0_F(4) + -5.0f;
            i_this->m2B4 = 0;
            for (s32 i = 0; i < ARRAY_SIZE(i_this->mWindAtSph); i++) {
                i_this->mWindAtSph[i].SetAtType(AT_TYPE_WIND);
            }
            actor->shape_angle.x = 0;
            mDoAud_bgmStart(JA_BGM_DK_BATTLE);
        }
        break;
    case 0x32:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtType_OTHER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            r28 = 0;
            break;
        }

        i_this->m25A0++;
        i_this->m25CC = 0.0f;
        i_this->m25A4 = 0;
        i_this->m25A6 = 0;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);

        i_this->m25A8.x = 3267.0f;
        i_this->m25A8.y = 9561.0f;
        i_this->m25A8.z = -4562.0f;

        i_this->m25B4 = actor->eyePos;
        i_this->m25B4.y -= (REG0_F(7) + 100.0f);
        i_this->m25C8 = 60.0f;
        // Fall-through
    case 0x33:
        cLib_addCalc2(&i_this->m25B4.x, actor->eyePos.x, 0.1f, i_this->m25CC * 100.0f);
        cLib_addCalc2(&i_this->m25B4.y, actor->eyePos.y -(REG0_F(7)+ 100.0f), 0.3f, i_this->m25CC * 200.0f);
        cLib_addCalc2(&i_this->m25B4.z, actor->eyePos.z, 0.1f, i_this->m25CC * 100.0f);

        if (i_this->mAction == ACTION_START) {
            i_this->m25A0++;
            i_this->m25A6 = 0;
        }
        cLib_addCalc2(&i_this->m25CC, 1.0f, 1.0f, REG0_F(4) + 0.02f);
        break;
    case 0x34:
        if (i_this->m25A6 >= 0x64) {
            i_this->m25A0 = 0x96;
        }
        break;
    case 0x64: {
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtType_OTHER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            r28 = 0;
            break;
        }
        i_this->m25A0++;
        i_this->m25CC = 0.0f;
        i_this->m25A4 = 0;
        i_this->m25A6 = 0;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);

        camera_class* pCamera = dComIfGp_getCamera(0);
        i_this->m25A8 = pCamera->mLookat.mEye;
        local_104.x = pCamera->mLookat.mEye.x - i_this->m1150.x;
        local_104.z = pCamera->mLookat.mEye.z - i_this->m1150.z;

        i_this->m25C0.y = cM_atan2s(local_104.x, local_104.z);

        i_this->m25C0.x = -cM_atan2s(local_104.y, std::sqrtf(local_104.x * local_104.x + local_104.z * local_104.z));
        actor->current.angle.y = i_this->m25C0.y + (s16)cM_rndFX(4000.0f);
        i_this->m25D0 = 1500.0f;
        i_this->m25C8 = 45.0f;
        player->changeOriginalDemo();
        mDoAud_bgmStreamPrepare(JA_STRM_DK_CLEAR);
        // Fall-through
    }
    case 0x65:
        if (i_this->m25A6 == 0x3C) {
            mDoAud_bgmStreamPlay();
        }
        i_this->m25B4 = i_this->m1150;
        i_this->m25B4.y += REG0_F(16) + -100.0f;
        local_104.x = 0.0f;
        local_104.y = 0.0f;
        local_104.z = i_this->m25D0 + REG0_F(17);

        cMtx_YrotS(*calc_mtx, i_this->m25C0.y);
        cMtx_XrotM(*calc_mtx, i_this->m25C0.x);
        MtxPosition(&local_104, &local_108);
        local_108 += i_this->m25B4;
        cLib_addCalc2(&i_this->m25A8.x, local_108.x, 0.1f, 100.0f);
        if (i_this->m25A2 == 0) {
            i_this->m25A8.y = REG0_F(18) + 9950.0f;
        } else {
            cLib_addCalc2(&i_this->m25A8.y, local_108.y + REG0_F(13), 0.1f, 100.0f);
        }
        cLib_addCalc2(&i_this->m25A8.z, local_108.z, 0.1f, 100.0f);
        break;
    case 0x6E:
        i_this->m25C8 = 40.0f;

        i_this->m25A8.x = -25267.0f;
        i_this->m25A8.y = -948.0f;
        i_this->m25A8.z = 22916.0f;
        i_this->m25A0 = 0x6F;
        // Fall-through
    case 0x6F: {
        i_this->m25B4.x = 3600.0f;
        f32 fVar17 = actor->current.pos.y;
        if (fVar17 < 30000.0f) {
            i_this->m25B4.y = (fVar17 - 6000.0f) + REG0_F(19);
        }
        i_this->m25B4.z = -3800.0f;
        cLib_addCalc2(&i_this->m25A8.z, 30449.0f, 0.02f, i_this->m25CC * 75.33f);
        if (i_this->m25A6 > REG0_S(2)) {
            cLib_addCalc2(&i_this->m25CC, REG0_S(1) + 1.5f, 1.0f, REG0_F(2) + 0.02f);
        }
        local_108.x = 4444.0f;
        local_108.y = 9800.0f;
        local_108.z = -4500.0f;

        player->setPlayerPosAndAngle(&local_108, (s16)0);
        break;
    }
    case 0x70:
        i_this->m25B4 = i_this->m2CC;

        i_this->m25A0++;
        i_this->m25A6 = 0;
        i_this->m25C8 = dVar16;
        // Fall-through
    case 0x71:
        if (i_this->m25A6 == 0x78) {
            local_104 = center_pos;
            local_104.y = 10300.0f;
            eff_hane_set(i_this, &local_104, 0x27, -1);
        }

        if (i_this->m25A6 > REG0_S(7) + 0x43) {
            cLib_addCalc2(&i_this->m25B4.y, REG0_F(4) + 9900.0f, 0.5f, REG0_F(6) + 200.0f);
        }
        i_this->m25A8 = i_this->m2CC;
        i_this->m25A8.y = REG0_F(5) + 10000.0f;
        i_this->m25A8.x += REG0_F(7) + 500.0f;

        local_108 = i_this->m2CC;

        local_108.x += REG0_F(11) -200.0f;
        local_108.z += REG0_F(12) -150.0f;
        local_108.y = player->current.pos.y;

        player->setPlayerPosAndAngle(&local_108, 10000);
        if (i_this->m25A6 == REG0_S(2) + 0x6E) {
            player->changeDemoMode(daPy_demo_c::DEMO_SMILE_e);
        }
        if (i_this->m25A6 == REG0_S(2) + 0x82) {
            player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
        }
        if (i_this->m25A6 == REG0_S(4) + 0xBE) {
            i_this->m25A0++;
            i_this->m25A6 = 0;
        }
        break;
    case 0x72:
        i_this->m25B4.x = 4386.0f;
        i_this->m25B4.y = 10020.0f;
        i_this->m25B4.z = -4368.0f;

        i_this->m25A8.x = 4144.0f;
        i_this->m25A8.y = 10061.0f;
        i_this->m25A8.z = -4131.0f;

        if (i_this->m25A6 == 10) {
            dComIfGs_onStageBossEnemy();
            mDoAud_seStart(JA_SE_OBJ_TOGE_IN, NULL, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->m25A6 == 0x28) {
            i_this->m25A0 = 0x96;
        }
        break;
    case 0x96:
        i_this->m25A0 = 0;
        camera->mCamera.Reset(i_this->m25B4, i_this->m25A8);
        camera->mCamera.Start();
        camera->mCamera.SetTrimSize(0);
        dComIfGp_event_reset();
        fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
        break;
    default:
        break;
    }

    if (i_this->m25A0 != 0 && r28) {
        f32 fx = i_this->m25D4 * cM_ssin(i_this->m25A4 * 0x3300);
        f32 fy = i_this->m25D4 * cM_scos(i_this->m25A4 * 0x3000);
        f32 fz = i_this->m25D4 * cM_ssin(i_this->m25A4 * 0x3700);
        local_e4.x = i_this->m25A8.x + fx;
        local_e4.y = i_this->m25A8.y + fy;
        local_e4.z = i_this->m25A8.z + fz;
        local_f0.x = i_this->m25B4.x + fx;
        local_f0.y = i_this->m25B4.y + fy;
        local_f0.z = i_this->m25B4.z + fz;
        s16 r20 = 0;

        if (i_this->m25D4 > 0.1f) {
            r20 = (50.0f + REG0_F(6)) * cM_scos(i_this->m25A4 * 0x1c00);
        }

        if (i_this->m25A0 < 10) {
            dBgS_LinChk linChk;
            linChk.Set(&local_f0, &local_e4, actor);
            if (dComIfG_Bgsp()->LineCross(&linChk)) {
                local_e4 = linChk.GetCross();
            }
        }

        camera->mCamera.Set(local_f0, local_e4, r20, i_this->m25C8);
        cLib_addCalc0(&i_this->m25D4, 1.0f, REG0_F(16) + 1.0f);
        JUTReport(0x1e, 0x1ae, "K MAIN COUNT  %d", i_this->m25A4);
        JUTReport(0x19a, 0x1ae, "K SUB  COUNT  %d", i_this->m25A6);

        i_this->m25A6++;
        i_this->m25A4++;
    }
    if (r27) {
        mDoAud_seStart(JA_SE_ATM_MJT_SHUTTER, &center_pos, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
}

/* 0000A7C8-0000B204       .text eff_hane_move__FP9bdk_classP9bdk_eff_s */
void eff_hane_move(bdk_class* i_this, bdk_eff_s* i_eff) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1 = -130.0f;
    f32 fVar2 = 2.0f;

    cXyz vec1;
    cXyz vec2;
    cXyz vec3;
    dBgS_GndChk gndChk;
    dBgS_LinChk linChk;

    if (i_eff->m040 != 0) {
        i_eff->m040--;
    }
    cMtx_YrotS(*calc_mtx, i_eff->m030.y);
    vec1.x = 0.0f;
    vec1.y = 0.0f;
    vec1.z = i_eff->m020;

    MtxPosition(&vec1, &vec2);
    vec2.y = i_eff->m01C;
    i_eff->m010 = i_eff->m004;
    i_eff->m004 += vec2;
    vec1 = i_eff->m004 - i_eff->m010;
    if (vec1.abs() > 0.0f) {
        cMtx_YrotS(*calc_mtx, cM_atan2s(vec1.x, vec1.z));

        vec1.x = 0.0f;
        vec1.y = 30.0f;
        vec1.z = 20.0f;
        MtxPosition(&vec1, &vec2);

        vec1 = i_eff->m004;
        vec1.y += 30.0f;
        vec2 += i_eff->m004;

        linChk.Set(&vec1, &vec2, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            i_eff->m004.x = i_eff->m010.x;
            i_eff->m004.z = i_eff->m010.z;
            i_eff->m020 = 0;
        }
    }

    vec1 = i_eff->m004;
    vec1.y += 200.0f;
    gndChk.SetPos(&vec1);
    f32 height = dComIfG_Bgsp()->GroundCross(&gndChk) + 20.0f;

    i_eff->m01C -= (0.1f + REG8_F(14));

    if (i_eff->m01C < REG8_F(15) + -5.0f) {
        i_eff->m01C = REG8_F(15) + -5.0f;
    }

    if (i_eff->m004.y <= height) {
        i_eff->m004.y = height;
        cLib_addCalc0(&i_eff->m020, 1.0f, 0.1f);
        i_eff->m030.y += i_eff->m036.x;
        cLib_addCalcAngleS2(&i_eff->m036.x, 0, 10, 10);
        cLib_addCalcAngleS2(&i_eff->m036.z, 0, 10, 10);
        cLib_addCalcAngleS2(&i_eff->m030.x, 0, 10, 200);
        cLib_addCalcAngleS2(&i_eff->m030.z, 0, 10, 200);
    } else {
        i_eff->m030.x = i_eff->m028 * cM_ssin(i_eff->m03C * 0x500);
        i_eff->m030.z = i_eff->m028 * cM_scos(i_eff->m03C * 0x400);

        f32 fVar3;
        f32 fVar4;
        if (i_eff->m040 != 0) {
            fVar3 = REG8_F(7) + 15000.0f;
            fVar4 = 1000.0f;
            fVar1 = REG8_F(8) + -300.0f;
            fVar2 = 10.0f;
        } else {
            fVar3 = 8000.0f;
            fVar4 = 200.0f;
        }
        cLib_addCalc2(&i_eff->m028, fVar3, 1.0f, fVar4);
    }

    i_eff->m036.y += i_eff->m036.z;
    if (i_eff->m004.y > REG8_F(11) + 9930.0f) {
        cLib_addCalc2(&i_eff->m024, fVar1, 0.1f, fVar2);
    } else {
        cLib_addCalc0(&i_eff->m024, 0.1f, 1.3f);
    }
    MtxTrans(i_eff->m004.x, i_eff->m004.y, i_eff->m004.z, FALSE);
    cMtx_YrotM(*calc_mtx, i_eff->m036.y);
    MtxTrans(0.0f, -i_eff->m024, 0.0f, TRUE);
    cMtx_XrotM(*calc_mtx, i_eff->m030.x);
    cMtx_ZrotM(*calc_mtx, i_eff->m030.z);
    MtxTrans(0.0f, i_eff->m024, 0.0f, TRUE);
    f32 scale = i_eff->m02C;
    MtxScale(scale, scale, scale, TRUE);
    i_eff->m044->setBaseTRMtx(*calc_mtx);

    if (i_eff->m03E != 0) {
        i_eff->m03E--;
    }

    if (i_eff->m004.y < 9700.0f || i_eff->m03E == 0 || land_area_check(&i_eff->m004, 3000.0f) == FALSE) {
        i_eff->m001 = 1;
    } else {
        i_eff->m048.SetC(i_eff->m004);
        dComIfG_Ccsp()->Set(&i_eff->m048);
    }

    fopAc_ac_c* tgActor;
    CcAtInfo hit_atInfo;
    if (i_eff->m048.ChkTgHit() != NULL && i_eff->m040 == 0) {
        CcAtInfo hit_atInfo;
        cCcD_Stts* stts = i_eff->m048.GetTgHitObj()->GetStts();
        if (stts == NULL) {
            tgActor = NULL;
        } else {
            tgActor = stts->GetActor();
        }

        if (tgActor != NULL) {
            vec3 = i_eff->m004 - tgActor->current.pos;

            if (i_eff->m020 < 5.0f) {
                i_eff->m030.y = cM_atan2s(vec3.x, vec3.z) + (s16)cM_rndFX(4000.0f);
                i_eff->m020 = 10.0f + cM_rndF(5.0f) + REG0_F(8);
                i_eff->m01C = 10.0f + cM_rndF(5.0f) + REG0_F(9);
            }

            i_eff->m036.z = cM_rndFX(REG0_F(10) + 1500.0f);
            i_eff->m036.x = cM_rndFX(REG0_F(16) + 1500.0f);
            i_eff->m040 = cM_rndF(30.0f) + 30.0f;
        }
    }
    if (i_eff->m001 && (cLib_addCalc0(&i_eff->m02C, 1.0f, 0.05f), i_eff->m02C < 0.05f)) {
        i_eff->m000 = 0;
    }
}

/* 0000B204-0000B278       .text eff_Grock_move__FP9bdk_classP9bdk_eff_s */
void eff_Grock_move(bdk_class* i_this, bdk_eff_s* eff) {
    f32 fVar1 = 0.0f;
    if (eff->m03C == 1) {
        fVar1 = -10.0f;
    }
    MtxTrans(eff->m004.x, eff->m004.y + fVar1, eff->m004.z, 0);
    eff->m044->setBaseTRMtx(*calc_mtx);
}

/* 0000B278-0000B30C       .text my_effect_move__FP9bdk_class */
void my_effect_move(bdk_class* i_this) {
    bdk_eff_s* eff = &i_this->m261C[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m261C); i++, eff++) {
        if (eff->m000 != 0) {
            eff->m03C++;
            if (eff->m000 == 1) {
                eff_hane_move(i_this, eff);
            } else if (eff->m000 == 2) {
                eff_Grock_move(i_this, eff);
            }
        }
    }
}

/* 0000B30C-0000BD74       .text daBdk_Execute__FP9bdk_class */
static BOOL daBdk_Execute(bdk_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();

    i_this->m260C = actor->current.pos;
    i_this->m260C.y = 9800.0f;
    i_this->m2C4++;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m2EC[i] != 0) {
            i_this->m2EC[i]--;
        }
    }
    if (i_this->m2F8 != 0) {
            i_this->m2F8--;
    }
    if (i_this->m2FA != 0) {
            i_this->m2FA--;
    }
    if (i_this->m1138 != 0) {
        i_this->m1138--;
    }
    if (!l_HIO.m005) {
        i_this->mpMorf->play(&actor->eyePos, 0, 0);
        move(i_this);

        if (i_this->mAction != ACTION_START && i_this->mAction < 0x64) {
            i_this->mAcch.CrrPos(*dComIfG_Bgsp());
            if (i_this->mAcch.ChkGroundHit()) {
                actor->speed.y = -10.0f;
                i_this->m2586 = 3;
            }
            if (i_this->m2586 != 0) {
                i_this->m2586--;
            }
            i_this->mAcchCir.SetWall(50.0f, 300.0f);
            i_this->mAcch.SetGroundUpY(0.0f);
        }
        damage_check(i_this);
    }
    f32 fVar1;
    if (i_this->m2B4 == 1) {
        fVar1 = l_HIO.m008 * 0.85f;
    } else {
        fVar1 = l_HIO.m008;
    }
    actor->scale.z = fVar1;
    actor->scale.y = fVar1;
    actor->scale.x = fVar1;

    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos);
    cMtx_YrotM(mDoMtx_stack_c::get(), actor->shape_angle.y);
    cMtx_XrotM(mDoMtx_stack_c::get(), actor->shape_angle.x);
    cMtx_ZrotM(mDoMtx_stack_c::get(), actor->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    J3DModel* model_2BC = i_this->mp2BC;
    model_2BC->setBaseScale(actor->scale);
    model_2BC->setBaseTRMtx(*calc_mtx);
    i_this->mpMorf->calc();

    col_set(i_this);

    cXyz offset;
    cXyz out;
    if (i_this->m113A) {
        i_this->mHeadTgSph.OffTgShield();
        cMtx_YrotS(*calc_mtx, -actor->shape_angle.y);
        offset = i_this->m1150 - i_this->m1144;
        MtxPosition(&offset, &out);
        s16 angle = out.z * (REG8_F(0xF) + - 200.0f);
        if (angle > 8000) {
            angle = 8000;
        } else {
            if (angle < -8000) {
                angle = -8000;
            }
        }

        s16 iVar4 = (REG0_F(5) + - 2000.0f) * i_this->m1140 * cM_ssin(i_this->m1130 * (REG8_S(4) + 2500));
        s16 iVar11 = i_this->m113C * 4000.0f;
        cLib_addCalc2(&i_this->m113C, 1.0f, 1.0f, REG0_F(4) + 0.01f);
        if (i_this->m25A6 > REG0_S(9) + 0x41) {
            cLib_addCalc2(&i_this->m1140, 1.0f, 1.0f, REG0_F(0x2) + 0.4f);
        }
        cLib_addCalcAngleS2(&i_this->m1120, angle + iVar4 + 4500, 4, iVar11);
        cLib_addCalcAngleS2(&i_this->m1122, 4, 10, iVar11);
        i_this->m1130++;

        if (i_this->m1138 != 0) {
            i_this->m1134 = 0;
            i_this->m1132 = 0;

            offset.x = 0.0f;
            offset.y = 0.0f;
            offset.z = i_this->m1138 * (REG0_F(7) + 500.0f);

            cMtx_YrotS(*calc_mtx, i_this->m1136);
            MtxPosition(&offset, &out);
            i_this->m112E = out.z * cM_ssin(i_this->m2C4 * (REG0_S(4) + 7000));
            i_this->m112C = out.x * cM_ssin(i_this->m2C4 * (REG0_S(4) + 7000));
        }
        if (3000 < i_this->m1134) {
            i_this->m1130++;
        }

        i_this->m1124 = i_this->m1132 * cM_ssin(i_this->m1130 * 1500);
        i_this->m1126 = i_this->m1132 * cM_scos(i_this->m1130 * 1200);
        i_this->m1128 = i_this->m1132 * cM_ssin(i_this->m1130 * 1500 + 0x4000);
        i_this->m112A = i_this->m1132 * cM_scos(i_this->m1130 * 1200 + 0x4000);
        cLib_addCalcAngleS2(&i_this->m1132, i_this->m1134, 2, 500);
        i_this->m1134 = 1500;
    } else {
        i_this->m1138 = 0;
        i_this->m1134 = 0;
        i_this->m1132 = 0;
    }
    for (s32 i = 0; i < 4; i++) {
        tail_control(i_this, &i_this->m300[i]);
    }
    actor->shape_angle.y = actor->current.angle.y;
    actor->shape_angle.z = actor->current.angle.z;
    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x18), *calc_mtx); // j_dk_atama1 joint

    offset.x = REG0_F(10) + 120.0f;
    offset.y = 0.0f;
    offset.z = REG0_F(12) + - 120.0f;
    MtxPosition(&offset, &actor->eyePos);
    actor->attention_info.position = actor->eyePos;
    s16 angle;
    if (i_this->mF10) {
        offset = player->current.pos - actor->current.pos;

        angle = cM_atan2s(offset.x, offset.z) - actor->shape_angle.y;
        if (angle > 7000) {
            angle = 7000;
        } else {
            if (angle < -7000) {
                angle = -7000;
            }
        }
    } else {
        angle = 0;
    }
    i_this->mF10 = 0;
    cLib_addCalcAngleS2(&i_this->mF12, angle, 4, 0x800);
    cLib_addCalcAngleS2(&i_this->mF14, 0, 0x10, 0x200);

    kamen_break_move(i_this);
    my_effect_move(i_this);
    obj_move(i_this);
    demo_camera(i_this);
    kankyo_cont(i_this);
    for (s32 i = 0; i < ARRAY_SIZE(i_this->m6078); i++) {
        if (i_this->m6078[i] != 0) {
            i_this->m6078[i]--;
        }
    }
    if (i_this->m2618 != 0 && (i_this->m2618--, i_this->m2618 == 0)) {
        dComIfGp_particle_setToon(
            dPa_name::ID_SCENE_A136, &i_this->m260C, &actor->shape_angle, NULL, 0xB9,
            &i_this->m6110, (s8)fopAcM_GetRoomNo(actor)
        );
    }
    if (i_this->m2619 != 0) {
        fopAcM_seStartCurrent(actor, JA_SE_CM_DK_NAIL, 0);
        for (s32 i = 0; i < ARRAY_SIZE(i_this->m1174); i++) {
            foot_eff_pos[i] = i_this->m1174[i];
            foot_eff_pos[i].y -= REG0_F(0x9) + 200.0f;

            if (foot_eff_pos[i].y < 9800.0f) {
                foot_eff_pos[i].y = 9800.0f;
            }
        }
        if (foot_eff_pos[0].y > 9810.0f || (i_this->m2584 == 0)) {
            i_this->m2619 = 0;

            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mp6214); i++) {
                if (i_this->mp6214[i]) {
                    i_this->mp6214[i]->becomeInvalidEmitter();
                    i_this->mp6214[i] = NULL;
                }
            }
        } else {
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mp6214); i++) {
                if (i_this->mp6214[i]) {
                    s32 num = i & 1;
                    i_this->mp6214[i]->setGlobalTranslation(foot_eff_pos[num].x, foot_eff_pos[num].y, foot_eff_pos[num].z);
                }
            }
        }
    }
    i_this->m2584 = 0;
    return TRUE;
}

/* 0000BD74-0000BD7C       .text daBdk_IsDelete__FP9bdk_class */
static BOOL daBdk_IsDelete(bdk_class* i_this) {
    return TRUE;
}

/* 0000BD7C-0000BF08       .text daBdk_Delete__FP9bdk_class */
static BOOL daBdk_Delete(bdk_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    dComIfG_resDelete(&i_this->mPhase, "Bdk");
    mDoHIO_deleteChild(l_HIO.mNo);
    if (actor->heap) {
        dComIfG_Bgsp()->Release(i_this->pm_bgw);
        dComIfG_Bgsp()->Release(i_this->mp63BC[0]);
        dComIfG_Bgsp()->Release(i_this->mp63BC[1]);
        dComIfG_Bgsp()->Release(i_this->mp63BC[2]);
        i_this->mpMorf->stopZelAnime();
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m910); i++) {
        mDoAud_seDeleteObject(&i_this->m910[i]);
    }

    mDoAud_seDeleteObject(&center_pos);
    mDoAud_seDeleteObject(&wind_se_pos);
    mDoAud_seDeleteObject(&i_this->m2CC);

    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m6080); i++) {
        i_this->m6080[i].remove();
        i_this->m6130[i].remove();
    }
    i_this->m6110.remove();
    i_this->m61B0.remove();

    return TRUE;
}

/* 0000BF08-0000C684       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_actor) {
    bdk_class* i_this = (bdk_class *)i_actor;
    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bdk", BDK_BDL_DK),
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bdk", BDK_BCK_FLY1),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        dComIfG_getObjectRes("Bdk", BDK_BAS_FLY1),
        0x80000,
        0x11000022
    );

    if (!i_this->mpMorf || !i_this->mpMorf->getModel()) {
        return FALSE;
    }

    for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        // j_dk_kubi1, (j_dk_tosaka_A1 to j_dk_tosaka_B2), j_dk_o_lA2, j_dk_o_lB2, j_dk_o_rA2, j_dk_o_rB2 joints
        if (i == 0x17 || (0x1F <= i && i <= 0x24) || i == 0x3A || i == 0x3C || i == 0x3E || i == 0x40) {
            i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }

    i_this->mpMorf->getModel()->setUserArea((u32)i_this);

    i_this->mp2BC = mDoExt_J3DModel__create(i_this->mpMorf->getModel()->getModelData(), 0, 0x11020203);
    if (i_this->mp2BC == NULL) {
        return FALSE;
    }

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Bdk", BDK_BDL_DK_KAMEN4);
    i_this->mp8F0 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (!i_this->mp8F0) {
        return FALSE;
    }

    static u16 kamen_break_bdl[] = {BDK_BDL_BUHINA, BDK_BDL_BUHINB, BDK_BDL_BUHINC, BDK_BDL_BUHIND};

    for (s32 i = 0; i < 0x4; i++) {
        i_this->m8FC[i] = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectRes("Bdk", kamen_break_bdl[i])
        , 0x80000, 0x11000022);
        if (!i_this->m8FC[i]) {
            return FALSE;
        }
    }
    i_this->bva = new mDoExt_bvaAnm();
    JUT_ASSERT(0x1864, i_this->bva);

    s32 bva = i_this->bva->init(i_this->mp8F0, (J3DAnmVisibilityFull *)dComIfG_getObjectRes("Bdk", BDK_BVA_HIBIWARE1), 1, 0, 1.0f, 0, -1, FALSE, 0);
    if (bva == 0) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes("Bdk", BDK_BDL_DK_TAIL);
    JUT_ASSERT(0x1878, modelData != NULL);
    for (int i = 0; i < 4; i++) {
        for(s32 j = 0; j < 9; j++) {
            i_this->m300[i].m000[j] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
            if (i_this->m300[i].m000[j] == NULL) {
                return FALSE;
            }
        }
    }

    for (s32 i = 0; i < 0x28; i++) {
        if (i == 0x27) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Bdk", BDK_BDL_GROCK00);
        } else if (i < 0x27) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Bdk", BDK_BDL_GHANE00);
        }
        JUT_ASSERT(0x189C, modelData != NULL);
        i_this->m261C[i].m044 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (i_this->m261C[i].m044 == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes("Bdk", BDK_BDL_S_TSHUTTER);
    JUT_ASSERT(0x18A9, modelData != NULL);
    for (s32 i = 0; i < 3; i++) {
        i_this->mp6310[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (i_this->mp6310[i] == NULL) {
            return FALSE;
        }

        i_this->mp63BC[i] = new dBgW();
        if (i_this->mp63BC[i] == NULL) {
            return FALSE;
        }
        if (i_this->mp63BC[i]->Set((cBgD_t*)(dComIfG_getObjectRes("Bdk", BDK_DZB_S_TSHUTTER)), dBgW::MOVE_BG_e, &i_this->m632C[i]) == TRUE) {
            return FALSE;
        }
        i_this->mp63BC[i]->SetCrrFunc(dBgS_MoveBGProc_Typical);
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bdk", BDK_BDL_S_TTOGE);
    JUT_ASSERT(0x18C4, modelData != NULL);
    i_this->mp62D8 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (i_this->mp62D8 == NULL) {
        return FALSE;
    }

    i_this->pm_bgw = new dBgW();
    JUT_ASSERT(0x18CE, i_this->pm_bgw != NULL);

    i_this->pm_bgw->Set((cBgD_t*)(dComIfG_getObjectRes("Bdk", BDK_DZB_S_TTOGE)), dBgW::MOVE_BG_e, &i_this->m62DC);
    i_this->pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);

    static Vec kosi1_offset[] = {{0.0f, 0.0f, 0.0f}};
    static Vec mune1_offset[] = {{105.0f, 0.0f, 40.0f}};
    static Vec mune2_offset[] = {{-15.0f, 0.0f, 25.0f}};
    static Vec mune3_offset[] = {{-15.0f, 0.0f, 110.0f}};
    static Vec kubi1_offset[] = {
        {-80.0f, 0.0f, 35.0f},
        {0.0f, 0.0f, -5.0f}
    };
    static Vec atama_offset[] = {{40.0f, 0.0f, 5.0f}};
    static Vec tubasaL1_0_offset[] = {{0.0f, -30.0f, -5.0f}};
    static Vec tubasaL1_1_offset[] = {
        {50.0f, 0.0f, 10.0f},
        {300.0f, -75.0f, -9.0f},
    };
    static Vec tubasaL1_2_offset[] = {
        {90.0f, -110.0f, 0.0f},
        {110.0f, -100.0f, 30.0f},
    };
    static Vec tubasaR1_0_offset[] = {{0.0f, 30.0f, -5.0f}};
    static Vec tubasaR1_1_offset[] = {
        {50.0f, 0.0f, 10.0f},
        {300.0f, 75.0f, -9.0f},
    };
    static Vec tubasaR1_2_offset[] = {
        {90.0f, 110.0f, 0.0f},
        {110.0f, 100.0f, 30.0f},
    };

    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x02, // kosi1: joint
            /* mRadius     */ 132.0f,
            /* mpOffsets   */ kosi1_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x15, // mune1: joint
            /* mRadius     */ 140.0f,
            /* mpOffsets   */ mune1_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x16, // mune2: joint
            /* mRadius     */ 148.0f,
            /* mpOffsets   */ mune2_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x16, // mune2: joint
            /* mRadius     */ 112.0f,
            /* mpOffsets   */ mune3_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x17, // kubi3: joint
            /* mRadius     */ 85.0f,
            /* mpOffsets   */ kubi1_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_DELETE_e,
            /* mJointIndex */ 0x18, // atama: joint
            /* mRadius     */ 90.0f,
            /* mpOffsets   */ atama_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x25, // tubasaL1_0: joint
            /* mRadius     */ 100.0f,
            /* mpOffsets   */ tubasaL1_0_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x25, // tubasaL1_0: joint
            /* mRadius     */ 55.0f,
            /* mpOffsets   */ tubasaL1_1_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL2_e,
            /* mJointIndex */ 0x25, // tubasaL1_0: joint
            /* mRadius     */ 110.0f,
            /* mpOffsets   */ tubasaL1_2_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x2F, // tubasaR1_0: joint
            /* mRadius     */ 100.0f,
            /* mpOffsets   */ tubasaR1_0_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 0x2F, // tubasaR1_0: joint
            /* mRadius     */ 55.0f,
            /* mpOffsets   */ tubasaR1_1_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL2_e,
            /* mJointIndex */ 0x2F, // tubasaR1_0: joint
            /* mRadius     */ 110.0f,
            /* mpOffsets   */ tubasaR1_2_offset,
        },
    };
    i_this->mp63C8 = JntHit_create(i_this->mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (i_this->mp63C8 !=NULL) {
        fopAcM_SetJntHit(i_actor, i_this->mp63C8);
    }

    return TRUE;
}

/* 0000C6CC-0000CCA8       .text daBdk_Create__FP10fopAc_ac_c */
static cPhs_State daBdk_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph head_at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 70.0f,
        }},
    };
    static dCcD_SrcSph head_tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 120.0f,
        }},
    };
    static dCcD_SrcSph tosaka_tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* Radius */ 30.0f,
        }},
    };
    static dCcD_SrcSph body_cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 250.0f,
        }},
    };
    static dCcD_SrcSph foot_cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
        }},
    };
    static dCcD_SrcSph wind_at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_WIND,
            /* SrcObjAt  Atp     */ 10,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e | dCcG_AtSPrm_NoHitMark_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 300.0f,
        }},
    };
    static dCcD_SrcSph kamen_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 70.0f,
        }},
    };
    static dCcD_SrcSph eff_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_WIND,
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
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 100.0f,
        }},
    };

    fopAcM_ct(a_this, bdk_class);
    bdk_class* i_this = (bdk_class*)a_this;
    fopAc_ac_c* actor = &i_this->actor;

    cPhs_State phase_state = dComIfG_resLoad(&i_this->mPhase, "Bdk");
    if (phase_state == cPhs_COMPLEATE_e) {
        for (s32 i = 0; i < 4; i++) {
            i_this->m6080[i].setFollowOff();
        }
        for (s32 i = 0; i < 3; i++) {
            i_this->m6130[i].setFollowOff();
        }

        i_this->m6110.setFollowOff();

        i_this->m2B4 = fopAcM_GetParam(actor);
        i_this->m2B4 = 1;

        if (!fopAcM_entrySolidHeap(actor, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }

        if (i_this->pm_bgw && dComIfG_Bgsp()->Regist(i_this->pm_bgw, actor)) {
            return cPhs_ERROR_e;
        }

        for (s32 i = 0; i < 3; i++) {
            if (i_this->mp63BC[i] != NULL && dComIfG_Bgsp()->Regist(i_this->mp63BC[i], actor)) {
                return cPhs_ERROR_e;
            }
        }

        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x2A;

        l_HIO.mNo = mDoHIO_createChild("戦闘用大怪鳥", &l_HIO);
        i_this->mAcch.Set(fopAcM_GetPosition_p(actor), fopAcM_GetOldPosition_p(actor), actor, 1 , &i_this->mAcchCir, fopAcM_GetSpeed_p(actor));
        i_this->mAcch.OffSameActorChk();

        i_this->mAcchCir.SetWall(400.0f, 500.0f);
        i_this->mStts.Init(0xff, 0xff, actor);

        i_this->mHeadAtSph.Set(head_at_sph_src);
        i_this->mHeadTgSph.Set(head_tg_sph_src);
        i_this->mBodyCCSph.Set(body_cc_sph_src);
        i_this->mFootCCSph[0].Set(foot_cc_sph_src);
        i_this->mFootCCSph[1].Set(foot_cc_sph_src);

        i_this->mHeadAtSph.SetStts(&i_this->mStts);
        i_this->mHeadTgSph.SetStts(&i_this->mStts);
        i_this->mBodyCCSph.SetStts(&i_this->mStts);
        i_this->mBodyCCSph.OnTgNoHitMark();
        i_this->mFootCCSph[0].SetStts(&i_this->mStts);
        i_this->mFootCCSph[1].SetStts(&i_this->mStts);

        i_this->mTosakaTgSph.Set(tosaka_tg_sph_src);
        i_this->mTosakaTgSph.SetStts(&i_this->mStts);

        for (s32 i = 0; i < 0xA; i++) {
            i_this->mWindAtSph[i].Set(wind_at_sph_src);
            i_this->mWindAtSph[i].SetStts(&i_this->mStts);
        }

        i_this->mA14.Init(0xff, 0xff, NULL);
        for (s32 i = 0; i < 0x4; i++) {
            i_this->mA50[i].Set(kamen_sph_src);
            i_this->mA50[i].SetStts(&i_this->mA14);
        }

        i_this->m603C.Init(0xff, 0xff, NULL);
        for (s32 i = 0; i < 0x28; i++) {
            i_this->m261C[i].m048.Set(eff_sph_src);
            i_this->m261C[i].m048.SetStts(&i_this->m603C);
        }
        center_pos.x = 3600.0f;
        center_pos.y = 9800.0f;
        center_pos.z = -3800.0f;

        center_pos2.x = 3600.0f;
        center_pos2.y = 9720.0f;
        center_pos2.z = -3800.0f;

        if (dComIfGs_isStageBossEnemy() || REG0_S(0) != 0) {
            dComIfGs_onStageBossEnemy();
            i_this->mAction = ACTION_AFTER_FIGHT;
            actor->current.pos.x = 300000.0f;
            actor->current.pos.y = 300000.0f;
            actor->current.pos.z = 300000.0f;
            i_this->m6320 = -630.0f;
            i_this->m6324 = -70.0f;
            i_this->m62D4 = -500.0f;
        } else {
            if (i_this->m2B4 == 0x1) {
                i_this->mAction = ACTION_T_FLY;
                actor->current.pos = center_pos;
                actor->current.pos.y = 5000.0f;
                i_this->m6320 = -630.0f;
                i_this->m6324 = -70.0f;
                mDoAud_bgmStart(JA_BGM_MJ_TOWER_BATTLE);
                for (s32 i = 0; i < 0xA; i++) {
                    i_this->mWindAtSph[i].SetAtType(AT_TYPE_UNK400000);
                }
                i_this->m2EC[0] = 0x168;
            } else {
                actor->gravity = REG0_F(4) + -5.0f;
                actor->speedF = l_HIO.m020;
                i_this->m2CA = -1;
                i_this->m1120 = -2000;
                actor->health = 20;
                actor->max_health = 20;
                actor->current.pos.y = 11000.0f;
            }
        }
    }
    #if VERSION > VERSION_DEMO
    i_this->m6224 = actor->tevStr;
    #endif
    return phase_state;
}
static actor_method_class l_daBdk_Method = {
    (process_method_func)daBdk_Create,
    (process_method_func)daBdk_Delete,
    (process_method_func)daBdk_Execute,
    (process_method_func)daBdk_IsDelete,
    (process_method_func)daBdk_Draw,
};

actor_process_profile_definition g_profile_BDK = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BDK,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bdk_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BDK,
    /* Actor SubMtd */ &l_daBdk_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
