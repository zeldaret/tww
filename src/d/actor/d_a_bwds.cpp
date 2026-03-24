/**
 * d_a_bwds.cpp
 * Enemy - Molgera Larva
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/d_cc_uty.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/actor/d_a_bwds.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_mtx.h"
#include "d/res/res_bwds.h"
#include "d/res/res_bwd.h"
#include "d/actor/d_a_player.h"

enum ActionStatus {
    ACTION_UG_MOVE = 0,
    ACTION_HOOK_ON = 1,
    ACTION_HOOK_CHANCE = 2,
    ACTION_FAIL = 5,
};

enum KOBOSS_HEAD_JOINT {
    JNT_KUBI,
    JNT_AGO,
    JNT_HEAD,
};

static GXColor eff_col;
static u8 hio_set;
daBwds_HIO_c l_HIO;

/* 000000EC-00000144       .text __ct__12daBwds_HIO_cFv */
daBwds_HIO_c::daBwds_HIO_c() {
    mNo = -1;
    m005 = 0;
    m008 = 0.79999995f; // 0x3F4CCCCC
    m00C = 0.7f;
    m010 = 7.0f;
    m014 = 220;
    m018 = 2000.0f;
    m01C = 300.0f;
}

/* 00000144-0000026C       .text anm_init__FP10bwds_classifUcfi */
void anm_init(bwds_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bwds", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Bwds", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bwds", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
    return;
}

/* 0000026C-000002E8       .text body_draw__FP10bwds_class */
void body_draw(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model;
    for (s32 i = 0; i < 0xd - i_this->m04F0; i++) {
        model = i_this->mp02BC[i];
        g_env_light.setLightTevColorType(model, &actor->tevStr);
        mDoExt_modelUpdateDL(model);
    }
}

/* 000002E8-000003E4       .text daBwds_Draw__FP10bwds_class */
static BOOL daBwds_Draw(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    g_env_light.setLightTevColorType(model, &actor->tevStr);
    i_this->mpMorf->entryDL();
    body_draw(i_this);
    for (s32 i = 0; i < 0x2; i++) {
        if (i_this->m1894[i] != 0) {
            g_env_light.setLightTevColorType(i_this->mp18B0[i]->getModel(), &actor->tevStr);
            i_this->mp18C0[i]->entry(i_this->mp18B0[i]->getModel()->getModelData());
            i_this->mp18B8[i]->entry(i_this->mp18B0[i]->getModel()->getModelData());
            i_this->mp18B0[i]->entryDL();
        }
    }
    return TRUE;
}

/* 00000420-00000B5C       .text body_control__FP10bwds_class */
void body_control(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    f32 diff_x, diff_y, diff_z;
    s32 i;
    s16 sVar1, sVar2;
    f32 fVar1 = 0.0f;
    f32 fVar4;
    J3DModel* model = i_this->mpMorf->getModel();
    MTXCopy(model->getAnmMtx(JNT_HEAD), *calc_mtx);
#if VERSION > VERSION_DEMO
    cXyz vec1((REG0_F(0) + 60.0f) * l_HIO.m008, REG0_F(1), REG0_F(2));
#else
    cXyz vec1((REG0_F(0) + 60.0f) * l_HIO.m008, REG0_F(1), REG0_F(2));
#endif
    cXyz vec2;
    cXyz vec3;
    MtxPosition(&vec1, &i_this->m032C[0]);
    i_this->m03E0[0] = actor->shape_angle;

    cXyz* p032c = &i_this->m032C[1];
    csXyz* p03e0 = &i_this->m03E0[1];
    cXyz* p043c = &i_this->m043C[1];

    cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);

    vec1.x = 0.0f;
    vec1.y = 0.0f;
    if (i_this->m04F5 != 0) {
        vec1.z = (REG0_F(6) + -10.0f) * l_HIO.m008;
        fVar1 = REG0_F(5) + 0.85f;
    } else {
        vec1.z = (REG0_F(17) + -5.0f) * l_HIO.m008;
    }

    MtxPosition(&vec1, &vec3);
    if (i_this->m04F5 == 1) {
        vec3.y += REG0_F(15) + -5.0f;
    }
    dBgS_GndChk gndChk;
    for (i = 1; i < 0xf; i++, ++p032c, ++p03e0, ++p043c) {
        f32 fVar2 = (0xe - i) * (REG0_F(17) + 0.5f) + 1.0f;
        f32 fVar3 = p032c->y + p043c->y + vec3.y * fVar2;
        if (i_this->m04F5 == 1) {
            Vec pos;
            pos = p032c[0];
            pos.y += 200.0f;
            gndChk.SetPos(&pos);
            f32 dVar8 = dComIfG_Bgsp()->GroundCross(&gndChk) - 60.0f - 30.0f + REG0_F(16) + 100.0f + REG0_F(19);
            if (fVar3 <= dVar8) {
                fVar3 = dVar8;
            }
        }
        diff_x = p043c->x + (p032c->x - p032c[-1].x) + vec3.x * fVar2;
        diff_y = fVar3 - p032c[-1].y;
        diff_z = p043c->z + (p032c->z - p032c[-1].z) + vec3.z * fVar2;

        sVar2 = (s16)cM_atan2s(diff_x, diff_z);
        sVar1 = -cM_atan2s(diff_y, std::sqrtf(diff_x * diff_x + diff_z * diff_z));

        vec1.x = 0.0f;
        vec1.y = 0.0f;
        vec1.z = (REG0_F(7) + 70.0f) * l_HIO.m008;

        cMtx_YrotS(*calc_mtx, sVar2);
        cMtx_XrotM(*calc_mtx, sVar1);

        MtxPosition(&vec1, &vec2);

        p03e0[-1].y = sVar2;
        p03e0[-1].x = sVar1 + 0x8000;

        p043c->x = p032c->x;
        p043c->y = p032c->y;
        p043c->z = p032c->z;
        p032c->x = p032c[-1].x + vec2.x;
        p032c->y = p032c[-1].y + vec2.y;
        p032c->z = p032c[-1].z + vec2.z;
        p043c->x = fVar1 * (p032c->x - p043c->x);
        p043c->y = fVar1 * (p032c->y - p043c->y);
        p043c->z = fVar1 * (p032c->z - p043c->z);

        if (i < 0xe) {
            J3DModel* iVar5 = i_this->mp02BC[i - 1];
            mDoMtx_stack_c::transS(p032c->x, p032c->y, p032c->z);
            mDoMtx_stack_c::YrotM(p03e0->y);
            mDoMtx_stack_c::XrotM(p03e0->x);
            fVar4 = cM_ssin(i_this->m02F4 * (REG0_S(5) + 3500) + i * (REG0_S(6) + 10000)) * (0.1f + REG0_F(4)) + 1.0f;
            f32 fVar5 = fVar4 * l_HIO.m008;
            mDoMtx_stack_c::scaleM(fVar5, fVar5, l_HIO.m008);
            iVar5->setBaseTRMtx(mDoMtx_stack_c::get());
        }
        if (i >= 3) {
            i_this->m0670[i].SetC(*p032c);
            i_this->m0670[i].SetR((REG0_F(9) + 10.0f) * l_HIO.m008);
            dComIfG_Ccsp()->Set(&i_this->m0670[i]);
        }
    }
}

/* 00000EDC-00001004       .text easy_bg_check2__FP10bwds_class */
void easy_bg_check2(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_54;

    for (s32 i = 0; i < 0x14; i++) {
        local_54.x = actor->current.pos.x;
        local_54.y = actor->current.pos.y;
        local_54.z = actor->current.pos.z;
        local_54.y = 0.0f;
        f32 fVar3 = local_54.abs();

        if (!(fVar3 > 3800.0f)) {
            break;
        }
        actor->current.pos.x *= 0.99f;
        actor->current.pos.z *= 0.99f;
    }
    return;
}

/* 00001004-00001198       .text pos_move__FP10bwds_classs */
void pos_move(bwds_class* i_this, s16 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_2c;
    cXyz local_38;
    local_2c = i_this->m02FC - actor->current.pos;
    cLib_addCalcAngleS2(&actor->current.angle.y, param_2 + cM_atan2s(local_2c.x, local_2c.z), REG0_S(3) + 5, i_this->m030C * i_this->m0310);
    cLib_addCalc2(&i_this->m0310, 1.0f, 1.0f, 0.05f);
    local_2c.x = 0.0f;
    local_2c.y = 0.0f;
    local_2c.z = actor->speedF;
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    MtxPosition(&local_2c, &local_38);
    actor->speed.x = local_38.x;
    actor->speed.z = local_38.z;
    actor->current.pos += actor->speed;
    i_this->actor.current.angle.x = -cM_atan2s(actor->speed.y, std::sqrtf(actor->speed.x * actor->speed.x + actor->speed.z * actor->speed.z));
}

/* 00001198-000019CC       .text ug_move__FP10bwds_class */
void ug_move(bwds_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_34;
    cXyz cStack_40;
    s16 sVar5 = 0;
    switch (i_this->m02F8) {
    case -10:
        anm_init(i_this, BWDS_BCK_KOBOSS_PAKUPAKU, 2.0f, 2, 1.0f, -1);
        i_this->m02F8 = 3;
        i_this->m030C = REG0_F(3) + 3000.0f;
        actor->speedF = l_HIO.m010;
        actor->speed.y = REG0_F(13) + 60.0f + cM_rndF(20.0f);
        actor->current.angle.y = cM_rndFX(32768.0f);
        local_34.x = 0.0f;
        local_34.y = 0.0f;
        local_34.z = 2000.0f;
        cMtx_YrotS(*calc_mtx, actor->current.angle.y);
        MtxPosition(&local_34, &cStack_40);
        i_this->m02FC = actor->current.pos + cStack_40;

        if (cM_rndF(1.0f) < 0.3535f) {
            i_this->m0500 = 0;
        } else {
            i_this->m0500 = cM_rndFX(REG0_F(9) + 3000.0f);
        }
        mDoAud_seStart(JA_SE_CM_BWD_C_JUMP_OUT, &actor->eyePos, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        mDoAud_seStart(JA_SE_CV_BWD_C_ATTACK, &actor->eyePos, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        break;
    case 0:
        anm_init(i_this, BWDS_BCK_KOBOSS_CLOSE, 2.0f, 0, 1.0f, -1);
        actor->current.pos.y = i_this->m0504;
        i_this->m02F8++;
        actor->shape_angle.z = 0;
        i_this->m181C = 1;
        // FALL-THROUGH
    case 1: {
        actor->current.pos.y = i_this->m0504;
        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->m02FC = player->current.pos;
        i_this->m030C = REG0_F(3) + 3000.0f;
        actor->speedF = l_HIO.m010;

        local_34 = i_this->m02FC - actor->current.pos;

        f32 fVar8 = local_34.abs();
        f32 fVar1 = fVar8 * 7.0f;
        if (fVar1 > l_HIO.m018) {
            fVar1 = l_HIO.m018;
        }
        sVar5 = fVar1 * cM_ssin(i_this->m02F4 * (REG0_S(3) + 0x514));

        if (fVar8 < 600.0f + REG0_F(12)) {
            anm_init(i_this, BWDS_BCK_KOBOSS_PAKUPAKU, 2.0f, 2, 1.0f, -1);
            i_this->m02F8++;
            actor->speedF = l_HIO.m010;
            actor->speed.y = REG0_F(13) + 50.0f;
            actor->current.angle.y = fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0));
            local_34.x = 0.0f;
            local_34.y = 0.0f;
            local_34.z = 2000.0f;
            cMtx_YrotS(*calc_mtx, actor->current.angle.y);

            MtxPosition(&local_34, &cStack_40);
            i_this->m02FC = actor->current.pos + cStack_40;

            if (cM_rndF(1.0f) < 0.3535f) {
                i_this->m0500 = 0;
            } else {
                i_this->m0500 = cM_rndFX(REG0_F(9) + 3000.0f);
            }
            mDoAud_seStart(JA_SE_CM_BWD_C_JUMP_OUT, &actor->eyePos, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            mDoAud_seStart(JA_SE_CV_BWD_C_ATTACK, &actor->eyePos, 0x0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        break;
    }
    case 2:
        i_this->m0670[0].OnAtSetBit();
        i_this->m0670[0].OnCoSetBit();
        // FALL-THROUGH
    case 3:
        i_this->m02FB = 1;
        actor->speed.y -= REG0_F(6) + 2.7f;
        if (actor->current.pos.y <= i_this->m0504) {
            i_this->m02F8 = 4;
            actor->speedF = REG0_F(5) + 5.0f;
            i_this->m0314[0] = REG0_S(3) + 0x23;
            fopAcM_OffStatus(actor, 0);
            actor->attention_info.flags = 0;
            i_this->m04F5 = 2;
            fopAcM_seStart(actor, JA_SE_CM_BWD_C_IN_SAND, 0);
        }
        break;
    case 4:
        i_this->m04F5 = 2;
        actor->speed.y = REG0_F(8) + -20.0f;
        if (i_this->m0314[0] == 0) {
            i_this->m02F8 = 5;
            actor->speed.y = 0.0f;
            actor->speedF = l_HIO.m010;
            i_this->m0314[0] = 0x1e;

            i_this->m0314[1] = cM_rndF(50.0f) + 120.0f;
            i_this->m0314[2] = cM_rndF(30.0f) + 30.0f;
        }
        break;
    case 5:
        actor->shape_angle.z = 0;
        i_this->m0500 = 0;
        if (i_this->m0314[0] == 0) {
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->m0314[0] = cM_rndF(20.0f) + 20.0f;
            i_this->m02FC.x = actor->current.pos.x;
            i_this->m02FC.y = actor->current.pos.y;
            i_this->m02FC.z = actor->current.pos.z;

            i_this->m02FC.x += cM_rndFX(REG0_F(12) + 600.0f);
            i_this->m02FC.z += cM_rndFX(REG0_F(12) + 600.0f);
        }
        if (i_this->m0314[2] == 0) {
            i_this->m0314[2] = cM_rndF(60.0f) + 40.0f;
            actor->speed.y = REG0_F(14) + 30.0f;
            actor->current.pos.y += actor->speed.y;
        }
        actor->speed.y -= REG0_F(15) + 3.0f;
        i_this->m030C = REG0_F(4) + 1000.0f;
        actor->speedF = l_HIO.m010;

        if (actor->current.pos.y <= i_this->m0504) {
            actor->current.pos.y = i_this->m0504;
            actor->speed.y = 0.0f;
            if (i_this->m0314[1] == 0) {
                i_this->m02F8 = 0;
            }
        }
        break;
    }
    pos_move(i_this, sVar5);
    if (actor->speed.y < 0.0f) {
        actor->shape_angle.z += i_this->m0500;
    }
    return;
}

/* 000019CC-00001B38       .text hook_on__FP10bwds_class */
void hook_on(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    cXyz local_34;
    i_this->m031E = 3;
    switch (i_this->m02F8) {
    case 0:
        anm_init(i_this, BWDS_BCK_KOBOSS_CLOSE, 2.0f, 0, 1.0f, -1);
        i_this->m02F8++;
        local_34 = player->eyePos - actor->eyePos;

        actor->current.angle.y = cM_atan2s(local_34.x, local_34.z);
        actor->current.angle.x = -cM_atan2s(local_34.y, std::sqrtf(local_34.x * local_34.x + local_34.z * local_34.z));
        actor->speedF = 0.0f;
        break;
    case 1:
        if (!fopAcM_CheckStatus(actor, fopAcStts_HOOK_CARRY_e)) {
            i_this->m02F6 = ACTION_HOOK_CHANCE;
            i_this->m02F8 = 0;
        }
        break;
    }
    return;
}

/* 00001B38-00001DCC       .text hook_chance__FP10bwds_class */
void hook_chance(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m0670[0].OnCoSetBit();
    switch (i_this->m02F8) {
    case 0:
        anm_init(i_this, BWDS_BCK_KOBOSS_PAKUPAKU, 2.0f, 2, 1.0f, -1);
        i_this->m02F8++;
        i_this->m0314[0] = l_HIO.m014;
        // FALL-THROUGH
    case 1:
        if (actor->current.pos.y <= i_this->m0504 + 100.0f + REG0_F(14)) {
            actor->current.pos.y = i_this->m0504 + 100.0f + REG0_F(14);

            actor->speed.y = REG6_F(7) + cM_rndF(REG0_F(6) + 40.0f);
            actor->speed.x = cM_rndFX(REG0_F(8) + 5.0f);
            actor->speed.z = cM_rndFX(REG0_F(8) + 5.0f);
            if (cM_rndF(1.0f) < 0.5f) {
                i_this->m04FC = 0;
            } else {
                i_this->m04FC = REG0_S(5) + 0x7f00;
            }

            i_this->m0500 = cM_rndFX(32768.0f);
            i_this->m0502 = cM_rndFX(REG0_F(5) + 2500.0f);
            if (cM_rndF(1.0f) < 0.5f) {
                if (cM_rndF(1.0f) < 0.5f) {
                    anm_init(i_this, BWDS_BCK_KOBOSS_CLOSE, 5.0f, 0, 1.0f, -1);
                } else {
                    anm_init(i_this, BWDS_BCK_KOBOSS_PAKUPAKU, 5.0f, 2, 1.0f, -1);
                }
            }
        }
        if (i_this->m0314[0] == 0) {
            i_this->m02F6 = ACTION_UG_MOVE;
            i_this->m02F8 = 3;
        }
        break;
    }

    actor->current.angle.y += i_this->m0502;
    cLib_addCalcAngleS2(&actor->shape_angle.z, i_this->m0500, 1, REG0_S(6) + 0x800);
    cLib_addCalcAngleS2(&actor->current.angle.x, i_this->m04FC, 1, REG0_S(6) + 0x800);
    i_this->m04F5 = 1;
    actor->current.pos += actor->speed;
    actor->speed.y -= (REG0_F(4) + 5.0f);
    i_this->m02FB = 1;
    return;
}

/* 00001DCC-00002178       .text fail__FP10bwds_class */
void fail(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = daPy_getPlayerActorClass();

    i_this->m031E = 3;
    i_this->m04F5 = 1;
    switch (i_this->m02F8) {
    case 0:
        cXyz local_34;
        local_34.x = 0.0f;
        local_34.y = REG0_F(19) + 60.0f;
        local_34.z = REG0_F(20) + -30.0f;
        player = daPy_getPlayerActorClass();
        s16 angle = fopAcM_searchActorAngleY(actor, player);
        cMtx_YrotS(*calc_mtx, angle);
        MtxPosition(&local_34, &actor->speed);
        i_this->m02F8++;
        i_this->m0314[0] = REG0_S(4) + 10;
        // FALL-THROUGH
    case 1:
        if (i_this->m0314[0] == 0) {
            i_this->m0314[0] = REG0_S(5) + 1;
            cXyz local_40 = i_this->m032C[0xc - i_this->m04F0 + REG0_S(7)];
            cXyz local_34;
            local_34.x = 0.5f;
            local_34.y = 0.5f;
            local_34.z = 0.5f;

            csXyz local_54(0, 0, 0);
            local_54.x = cM_rndF(65536.0f);
            local_54.y = cM_rndF(65536.0f);
            // dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_40);
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BWK_SIBOUBAKUEN00, &local_40, &local_54, &local_34);
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BWK_SIBOUFLASH00, &local_40, &local_54, &local_34);
            i_this->m04F0++;
            if (i_this->m04F0 >= REG0_S(8) + 0xd) {
                i_this->m02F8++;
            }
        }
        break;
    case 2:
        if (actor->current.pos.y <= i_this->m0504 + 100.0f + REG0_F(14) + 5.0f) {
            fopAcM_createDisappear(actor, &actor->current.pos, 10, daDisItem_HEART_e, -1);
            fopAcM_delete(actor);
        }
        break;
    }

    actor->current.pos += actor->speed;
    actor->speed.y -= REG0_F(4) + 5.0f;

    if (actor->current.pos.y <= i_this->m0504 + 100.0f + REG0_F(14)) {
        actor->current.pos.y = i_this->m0504 + 100.0f + REG0_F(14);
        actor->speed.x = 0.0f;
        actor->speed.y = 0.0f;
        actor->speed.z = 0.0f;
    } else {
        actor->current.angle.y = cM_atan2s(actor->speed.x, actor->speed.z);
        actor->current.angle.x = -cM_atan2s(actor->speed.y, std::sqrtf(actor->speed.x * actor->speed.x + actor->speed.z * actor->speed.z));
    }

    return;
}

/* 000021B4-0000245C       .text damage_check__FP10bwds_class */
void damage_check(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();
    CcAtInfo local_2c;
    cXyz local_38;
    if (i_this->m031E == 0) {
        if (fopAcM_CheckStatus(actor, fopAcStts_HOOK_CARRY_e)) {
            local_38.x = 0.0f;
            local_38.y = 0.0f;
            local_38.z = 0.0f;

            player->setHookshotCarryOffset(fopAcM_GetID(actor), &local_38);
            i_this->m02F6 = ACTION_HOOK_ON;
            i_this->m02F8 = 0;
            i_this->m031E = 10;
            mDoAud_seStart(JA_SE_LK_HS_SPIKE, &actor->eyePos, 0x20, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            fopAcM_seStart(actor, JA_SE_CV_BWD_C_HS_DAMAGE, 0);
        } else {
            i_this->m0508.Move();
            local_2c.pParticlePos = NULL;
            if (i_this->m0670[0].ChkTgHit()) {
                if (i_this->m02FB == 1) {
                    i_this->m031E = 6;
                    local_2c.mpObj = i_this->m0670[0].GetTgHitObj();
                    local_2c.pParticlePos = i_this->m0670[0].GetTgHitPosP();
                    cc_at_check(actor, &local_2c);

                    if (actor->health <= 0) {
                        i_this->m02F6 = ACTION_FAIL;
                        i_this->m02F8 = 0;
                        fopAcM_seStart(actor, JA_SE_CV_BWD_C_DIE, 0);
                    } else {
                        i_this->m0320 = REG0_F(11) + 80.0f;
                        i_this->m0328 = REG0_S(2) + 7;
                        fopAcM_seStart(actor, JA_SE_CV_BWD_C_DAMAGE, 0);
                    }
                }
            }
            for (s32 i = 3; i < 0xf; i++) {
                if (i_this->m0670[i].ChkTgHit()) {
                    def_se_set(actor, i_this->m0670[i].GetTgHitObj(), 0x40);
                    break;
                }
            }
            if (i_this->m04F4 != 0) {
                fopAcM_delete(actor);
            }
        }
    }
}

/* 0000245C-00002590       .text move__FP10bwds_class */
void move(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_1c;
    cXyz cStack_28;
    switch (i_this->m02F6) {
    case 0:
        ug_move(i_this);
        break;
    case 1:
        hook_on(i_this);
        break;
    case 2:
        hook_chance(i_this);
        break;
    case 5:
        fail(i_this);
        break;
    }

    if (actor->current.pos.y <= i_this->m0504 + 20.0f) {
        i_this->m02FA = 1;
    } else {
        i_this->m02FA = 0;
    }
    damage_check(i_this);
    i_this->m02FB = 0;

    if (i_this->m0320 > 0.01f) {
        local_1c.x = 0.0f;
        local_1c.y = 0.0f;
        local_1c.z = i_this->m0320;
        cMtx_YrotS(*calc_mtx, i_this->m0324);
        cMtx_XrotM(*calc_mtx, i_this->m0326);
        MtxPosition(&local_1c, &cStack_28);
        actor->current.pos += cStack_28;
        cLib_addCalc0(&i_this->m0320, 1.0f, 7.0f);
    }
    return;
}

/* 00002590-000031B4       .text daBwds_Execute__FP10bwds_class */
static BOOL daBwds_Execute(bwds_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    cXyz local_bc(0.0f, 0.0f, 0.0f);
    cXyz cStack_c8;

    i_this->m02F4++;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m0314[i] != 0) {
            i_this->m0314[i]--;
        }
    }
    if (i_this->m031E != 0) {
        i_this->m031E--;
    }
    if (i_this->m0328 != 0) {
        i_this->m0328--;
    }

    if (l_HIO.m005 == 0) {
        i_this->m0670[0].OffAtSetBit();
        i_this->m0670[0].OffCoSetBit();
        move(i_this);
        easy_bg_check2(i_this);

#if VERSION > VERSION_DEMO
        i_this->m1810.x = actor->current.pos.x;
        i_this->m1810.z = actor->current.pos.z;
#endif
        dBgS_GndChk gndChk;
        Vec local_b0;
        local_b0 = actor->current.pos;
        local_b0.y += REG0_F(13) + 2500.0f;
        gndChk.SetPos(&local_b0);

        f32 fVar11 = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (fVar11 < 850.0f && fVar11 != -G_CM3D_F_INF) {
            i_this->m1804.y = fVar11;
#if VERSION > VERSION_DEMO
            i_this->m1810.y = fVar11;
#endif
            i_this->m0504 = (s32)(((fVar11 - 60.0f) - 30.0f) + REG0_F(16));
        }

        i_this->mpMorf->play(&actor->eyePos, 0, 0);
    }

    actor->shape_angle.y = actor->current.angle.y;
    actor->shape_angle.x = actor->current.angle.x;
    J3DModel* pJVar8 = i_this->mpMorf->getModel();
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);

    f32 fVar3 = i_this->m0328 * 500.0f;
    s16 s1 = fVar3 * cM_ssin(i_this->m02F4 * 0x2100);
    s16 s2 = fVar3 * cM_scos(i_this->m02F4 * 0x2300);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y + s1);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x + s2);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    mDoMtx_stack_c::scaleM(l_HIO.m008, l_HIO.m008, l_HIO.m008);

    pJVar8->setBaseTRMtx(mDoMtx_stack_c::get());
    i_this->mpMorf->calc();
    MTXCopy(pJVar8->getAnmMtx(JNT_HEAD), *calc_mtx);

    local_bc.set(REG0_F(0), REG0_F(1), REG0_F(2));
    MtxPosition(&local_bc, &actor->eyePos);

    if (i_this->m02FA != 0) {
        actor->eyePos.y += 90.0f;
    }

    actor->attention_info.position.x = actor->eyePos.x;
    actor->attention_info.position.y = actor->eyePos.y;
    actor->attention_info.position.z = actor->eyePos.z;
    actor->attention_info.position.y += 10.0f;

    local_bc.set(REG0_F(0) + 50.0f, REG0_F(1), REG0_F(2));
    MtxPosition(&local_bc, &cStack_c8);
    i_this->m0670[0].SetC(cStack_c8);
    if (i_this->m02FA != 0) {
        cStack_c8.y += 60.0f;
        i_this->m0670[0].SetR((REG0_F(11) + 40.0f) * l_HIO.m008);
    } else {
        if (i_this->m04F5 == 1) {
            i_this->m0670[0].SetR((REG0_F(11) + 80.0f) * l_HIO.m008);
        } else {
            i_this->m0670[0].SetR((REG0_F(10) + 60.0f) * l_HIO.m008);
        }
    }

    dComIfG_Ccsp()->Set(&i_this->m0670[0]);
    i_this->m0544.SetR(l_HIO.m01C * l_HIO.m008);
    i_this->m0544.SetC(cStack_c8);
    dComIfG_Ccsp()->Set(&i_this->m0544);
    body_control(i_this);
    i_this->m04F5 = 0;

    local_bc.set(0.0f, 0.0f, 0.0f);
    J3DModel* model;
    for (s32 i = 0; i < 0xd - i_this->m04F0; i++) {
        model = i_this->mp02BC[i];
        MTXCopy(model->getBaseTRMtx(), *calc_mtx);
        MtxPosition(&local_bc, &cStack_c8);
        dComIfGp_particle_setSimple(dPa_name::ID_IT_SN_O_BWK_BODY_SUNA00, &cStack_c8);
    }

    if (i_this->m181C != 0) {
        if (i_this->m181C == 1) {
            i_this->m181C++;
            i_this->m1820[0].remove();
#if VERSION > VERSION_DEMO
            dComIfGp_particle_setToon(
                dPa_name::ID_IT_ST_BWK_IDOU_MOKO00, &i_this->m1810, &actor->shape_angle, NULL, 0xFF, i_this->m1820, (s16)fopAcM_GetRoomNo(actor)
            );
            i_this->m1820[0].setColor(eff_col);
            dComIfGp_particle_set(
                dPa_name::ID_IT_ST_BWK_IDOU_SUNA00, &i_this->m1810, &actor->shape_angle, NULL, 0xFF, &i_this->m1880, (s16)fopAcM_GetRoomNo(actor)
            );
#else
            i_this->m1804.x = actor->current.pos.x;
            i_this->m1804.z = actor->current.pos.z;
            dComIfGp_particle_setToon(
                dPa_name::ID_IT_ST_BWK_IDOU_MOKO00, &i_this->m1804, &actor->shape_angle, NULL, 0xFF, i_this->m1820, (s16)fopAcM_GetRoomNo(actor)
            );
            i_this->m1820[0].setColor(eff_col);
            dComIfGp_particle_set(
                dPa_name::ID_IT_ST_BWK_IDOU_SUNA00, &i_this->m1804, &actor->shape_angle, NULL, 0xFF, &i_this->m1880, (s16)fopAcM_GetRoomNo(actor)
            );
#endif
        }
        if (i_this->m181C < 0 || actor->current.pos.y > i_this->m1804.y) {
            i_this->m181C = 0;
            i_this->m1820[0].remove();
            i_this->m1880.remove();
        }
        if (i_this->m181C != 0) {
            fopAcM_seStart(actor, JA_SE_CM_BWD_C_MOVE_SAND, 0);
        }
    }

    if (i_this->m02F6 == 0) {
        if (i_this->m181D == 0) {
            if (actor->current.pos.y > i_this->m1804.y && actor->old.pos.y <= i_this->m1804.y) {
                if (i_this->m1894[0] == 0) {
                    i_this->m1894[0] = 1;
                    i_this->m1898[0].x = actor->current.pos.x;
                    i_this->m1898[0].y = actor->current.pos.y;
                    i_this->m1898[0].z = actor->current.pos.z;
                }
                i_this->m181D = REG0_S(5) + 5;
                i_this->m1804.x = actor->current.pos.x;
                i_this->m1804.z = actor->current.pos.z;
                i_this->m1820[1].remove();
                dComIfGp_particle_setToon(
                    dPa_name::ID_IT_ST_BWK_OUT_SMOKE00, &i_this->m1804, NULL, NULL, eff_col.r, &i_this->m1820[1], (s16)fopAcM_GetRoomNo(actor)
                );
                i_this->m1820[1].setColor(eff_col);
                dComIfGp_particle_set(dPa_name::ID_IT_SN_BWK_OUT_SUNA00, &i_this->m1804);
            }
        } else {
            i_this->m181D--;
            if (i_this->m181D == 0) {
                i_this->m1820[1].remove();
            }
        }

        if (i_this->m181E == 0) {
            if (actor->current.pos.y < i_this->m1804.y && actor->old.pos.y >= i_this->m1804.y) {
                if (i_this->m1894[1] == 0) {
                    i_this->m1894[1] = 1;
                    i_this->m1898[1].x = actor->current.pos.x;
                    i_this->m1898[1].y = actor->current.pos.y;
                    i_this->m1898[1].z = actor->current.pos.z;
                }
                i_this->m1820[2].remove();
                i_this->m181E = REG0_S(5) + 5;
                i_this->m1804.x = actor->current.pos.x;
                i_this->m1804.z = actor->current.pos.z;
                dComIfGp_particle_setToon(
                    dPa_name::ID_IT_ST_BWK_DIVE_SMOKE00, &i_this->m1804, NULL, NULL, eff_col.r, &i_this->m1820[2], (s16)fopAcM_GetRoomNo(actor)
                );
                i_this->m1820[2].setColor(eff_col);
                dComIfGp_particle_set(dPa_name::ID_IT_SN_BWK_DIVE_SUNA00, &i_this->m1804);
            }
        } else {
            i_this->m181E--;
            if (i_this->m181E == 0) {
                i_this->m1820[2].remove();
            }
        }
    }

    for (s32 i = 0; i < 2; i++) {
        if (i_this->m1894[i] != 0) {
            f32 fVar14 = i_this->m1894[i] - 1.0f;
            i_this->mp18B0[i]->setFrame(fVar14);
            i_this->mp18B8[i]->setFrame(fVar14);
            i_this->mp18C0[i]->setFrame(fVar14);
            mDoMtx_stack_c::transS(i_this->m1898[i].x, i_this->m1898[i].y, i_this->m1898[i].z);
            mDoMtx_stack_c::scaleM(l_HIO.m00C, l_HIO.m00C, l_HIO.m00C);
            i_this->mp18B0[i]->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
            i_this->mp18B0[i]->calc();
            i_this->m1894[i]++;
            if (i_this->m1894[i] > 60) {
                i_this->m1894[i] = 0;
            }
        }
    }
    return TRUE;
}

/* 000031B4-000031BC       .text daBwds_IsDelete__FP10bwds_class */
static BOOL daBwds_IsDelete(bwds_class* i_this) {
    return TRUE;
}

/* 000031BC-00003278       .text daBwds_Delete__FP10bwds_class */
static BOOL daBwds_Delete(bwds_class* i_this) {
#if VERSION > VERSION_DEMO
    dComIfG_resDelete(&i_this->m02AC, "Bwds");
#else
    dComIfG_deleteObjectRes("Bwds");
#endif

    if (i_this->m18C8 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }

    for (s32 i = 0; i < 3; i++) {
        i_this->m1820[i].remove();
    }
    i_this->m1880.remove();

    return TRUE;
}
static u16 body_bdl[] = {
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_BODY,
    BWDS_BDL_KOBOSS_SHIPPO,
};
static u32 s_bdl[] = {
    BWD_BDL_GSP00,
    BWD_BDL_GSP01,
};
static u32 s_btk[] = {
    BWD_BTK_GSP00,
    BWD_BTK_GSP01,
};
static u32 s_brk[] = {
    BWD_BRK_GSP00,
    BWD_BRK_GSP01,
};
static u32 s_bck[] = {
    BWD_BCK_GSP00,
    BWD_BCK_GSP01,
};
/* 00003278-00003634       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_actor) {
    J3DModelData* modelData;
    J3DModel* model;
    bwds_class* i_this = (bwds_class*)i_actor;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bwds", BWDS_BDL_KOBOSS_HEAD),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bwds", BWDS_BCK_KOBOSS_CLOSE),
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );

    if (!i_this->mpMorf || !i_this->mpMorf->getModel()) {
        return FALSE;
    } else {
        for (s32 i = 0; i < 0xd; i++) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Bwds", body_bdl[i]);
            model = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
            i_this->mp02BC[i] = model;
            if (i_this->mp02BC[i] == NULL) {
                return FALSE;
            }
        }

        for (s32 i = 0; i < 0x2; i++) {
            i_this->mp18B0[i] = new mDoExt_McaMorf(
                (J3DModelData*)dComIfG_getObjectRes("Bwd", s_bdl[i]),
                NULL,
                NULL,
                (J3DAnmTransformKey*)dComIfG_getObjectRes("Bwd", s_bck[i]),
                J3DFrameCtrl::EMode_LOOP,
                1.0f,
                0,
                -1,
                0,
                NULL,
                0,
                0x11020203
            );

            if (!i_this->mp18B0[i] || !i_this->mp18B0[i]->getModel()) {
                return FALSE;
            }
            modelData = i_this->mp18B0[i]->getModel()->getModelData();
            i_this->mp18B8[i] = new mDoExt_btkAnm();
            if (!i_this->mp18B8[i]) {
                return FALSE;
            }

            int ret = i_this->mp18B8[i]->init(
                modelData, (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bwd", s_btk[i]), TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0
            );

            if (!ret) {
                return FALSE;
            }

            i_this->mp18C0[i] = new mDoExt_brkAnm();

            ret = i_this->mp18C0[i]->init(
                modelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bwd", s_brk[i]), TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0
            );

            if (!ret) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/* 0000367C-000039A4       .text daBwds_Create__FP10fopAc_ac_c */
static cPhs_State daBwds_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_HOOKSHOT & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcSph body_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_HOOKSHOT & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
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
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcSph hs_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_HOOKSHOT,
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
            /* Radius */ 15.0f,
        }},
    };

    bwds_class* i_this = (bwds_class*)a_this;
    fopAcM_SetupActor(&i_this->actor, bwds_class);

    cPhs_State res = dComIfG_resLoad(&i_this->m02AC, "Bwds");
    if (res == cPhs_COMPLEATE_e) {
        i_this->m02B4 = fopAcM_GetParam(a_this);
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x4B000)) {
            return cPhs_ERROR_e;
        }
        if (hio_set == 0) {
            i_this->m18C8 = 1;
            hio_set = 1;
            l_HIO.mNo = mDoHIO_createChild("風ボス（子）", &l_HIO); // "Wind Boss (Child)"
        }
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x4;
        a_this->health = 4;
        a_this->max_health = 4;
        i_this->m0508.Init(0xFA, 0, a_this);
        i_this->m0544.Set(hs_sph_src);
        i_this->m0544.SetStts(&i_this->m0508);

        for (s32 i = 0; i < 0xf; i++) {
            i_this->m0670[i].SetStts(&i_this->m0508);
            if (i == 0) {
                i_this->m0670[i].Set(cc_sph_src);
            } else {
                i_this->m0670[i].Set(body_sph_src);
            }
            i_this->m032C[i].x = a_this->current.pos.x;
            i_this->m032C[i].y = a_this->current.pos.y;
            i_this->m032C[i].z = a_this->current.pos.z;
        }
        if (i_this->m02B4 == 0x23) {
            i_this->m02F8 = -10;
        }

        eff_col.r = 0xa0;
        eff_col.g = 0xa0;
        eff_col.b = 0x80;
        eff_col.a = 0x96;
    }
    return res;
}

static actor_method_class l_daBwds_Method = {
    (process_method_func)daBwds_Create,
    (process_method_func)daBwds_Delete,
    (process_method_func)daBwds_Execute,
    (process_method_func)daBwds_IsDelete,
    (process_method_func)daBwds_Draw,
};

actor_process_profile_definition g_profile_BWDS = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BWDS,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bwds_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BWDS,
    /* Actor SubMtd */ &l_daBwds_Method,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
