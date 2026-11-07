/**
 * d_a_bo.cpp
 * Enemy - Boko Baba
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bo.h"
#include "d/actor/d_a_boko.h"
#if VERSION > VERSION_DEMO
#include "d/actor/d_a_player_main.h"
#endif
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "res/Object/Bo.h"
#include "d/actor/d_a_player.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/d_material.h"

enum Actor_Anm_Type {
    ACTOR_ANM_TYPE_HEAD = 0,
    ACTOR_ANM_TYPE_BUD = 1,
};

enum Action { ACTION_ATTACK = 0, ACTION_EAT = 1, ACTION_BUD_DEATH = 2, ACTION_HEAD_DEATH_NORMAL = 3, ACTION_HEAD_DEATH_SPECIAL = 4 };

enum Mode {
    MODE_ATTACK_0 = 0,
    MODE_ATTACK_1 = 1,
    MODE_ATTACK_2 = 2,
    MODE_ATTACK_3 = 3,
    MODE_ATTACK_4 = 4,
    MODE_ATTACK_5 = 5,
    MODE_ATTACK_6 = 6,
    MODE_ATTACK_7 = 7,
    MODE_EAT_10 = 10,
    MODE_EAT_11 = 11,
    MODE_EAT_12 = 12,
    MODE_EAT_13 = 13,
    MODE_EAT_14 = 14,
    MODE_BUD_DEATH_20 = 20,
    MODE_BUD_DEATH_21 = 21,
    MODE_BUD_DEATH_22 = 22,
    MODE_HEAD_DEATH_NORMAL_30 = 30,
    MODE_HEAD_DEATH_NORMAL_31 = 31,
    MODE_HEAD_DEATH_NORMAL_32 = 32,
    MODE_HEAD_DEATH_NORMAL_33 = 33,
    MODE_HEAD_DEATH_NORMAL_34 = 34,
    MODE_HEAD_DEATH_SPECIAL_40 = 40,
    MODE_HEAD_DEATH_SPECIAL_41 = 41,
    MODE_HEAD_DEATH_SPECIAL_50 = 50,
    MODE_HEAD_DEATH_SPECIAL_51 = 51
};

/* 000000EC-000001E8       .text smoke_set__FP8bo_class */
static void smoke_set(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    JGeometry::TVec3<f32> scale;
    scale.set(3.0f, 3.0f, 3.0f);
    GXColor eff_col = {0xA0, 0xA0, 0x80, 0xFF};
    i_this->mSmokeCb.remove();
#if VERSION == VERSION_DEMO
    i_this->m3D0_demo = dComIfGp_particle_setToon(
        dPa_name::ID_AK_JT_ELEMENTSMOKE01,
        &i_this->m39C,
        &actor->shape_angle,
        NULL,
        0xB9,
        &i_this->mSmokeCb,
        fopAcM_GetRoomNo(actor)
    );
    if (i_this->m3D0_demo != NULL) {
        i_this->m3D0_demo->setGlobalParticleScale(scale);
        i_this->m3D0_demo->setRate(30.0f);
        i_this->m3D0_demo->setMaxFrame(1);
        i_this->m3D0_demo->setAwayFromCenterSpeed(10.0f);
        i_this->m3D0_demo->setAwayFromAxisSpeed(10.0f);
        i_this->m3D0_demo->becomeImmortalEmitter();
        i_this->mSmokeCb.setColor(eff_col);
    }
#else
    dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE01, &i_this->m39C, &actor->shape_angle, NULL, 0xB9, &i_this->mSmokeCb, fopAcM_GetRoomNo(actor));
    JPABaseEmitter* emitter = i_this->mSmokeCb.getEmitter();
    if (emitter != NULL) {
        emitter->setGlobalParticleScale(scale);
        emitter->setRate(30.0f);
        emitter->setMaxFrame(1);
        emitter->setAwayFromCenterSpeed(10.0f);
        emitter->setAwayFromAxisSpeed(10.0f);
        emitter->becomeImmortalEmitter();
        i_this->mSmokeCb.setColor(eff_col);
    }
#endif
}

/* 000001E8-00000638       .text nodeCallBack_UP__FP7J3DNodei */
static BOOL nodeCallBack_UP(J3DNode* node, int calcTiming) {
    f32 dVar4;
    csXyz local_88;
    cXyz offset;
    cXyz local_80;

    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        s32 var_r25 = 0;
        J3DModel* model = j3dSys.getModel();
        bo_class* i_this = (bo_class*)model->getUserArea();
        if (i_this != NULL) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo <= BO_UE1_JNT_J_BOKOBABA_SITA1_e) {
                dVar4 = (jntNo * 0.025f);
                cMtx_YrotM(*calc_mtx, i_this->m33A.y * dVar4);
                cMtx_XrotM(*calc_mtx, i_this->m33A.x * dVar4);
                cMtx_ZrotM(*calc_mtx, i_this->m33A.z * dVar4);
                var_r25 = 1;
            }
            if (jntNo == BO_UE1_JNT_BOKOBABA_SKLROOT_e) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m2F8);
                var_r25 = 1;
            }
            if (jntNo == BO_UE1_JNT_J_BOKOBABA_SITA1_e) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m328);
                var_r25 = 1;
            }
            if (jntNo == BO_UE1_JNT_J_BOKOBABA_SITA2_e) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m2E0);
                var_r25 = 1;
            }
            if (jntNo == BO_UE1_JNT_J_BOKOBABA_NECK3_e) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m310);
                var_r25 = 1;
            }
            if ((jntNo >= BO_UE1_JNT_J_BOKOBABA_NECK4_e) && (jntNo <= BO_UE1_JNT_J_BOKOBABA_NECK5_e)) {
                s16 r0 = (BO_UE1_JNT_J_BOKOBABA_ATAMA_e - jntNo);
                f32 f0 = 1.75f;
                dVar4 = (s16)r0 * f0;
                cMtx_YrotM(*calc_mtx, i_this->m352.y * dVar4);
                cMtx_ZrotM(*calc_mtx, i_this->m352.z * dVar4);
                var_r25 = 1;
            }
            if (jntNo == BO_UE1_JNT_J_BOKOBABA_ATAMA_e) {
                cMtx_YrotM(*calc_mtx, i_this->m334.y + REG12_S(3));
                cMtx_XrotM(*calc_mtx, i_this->m334.z + REG12_S(5));
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m31C);
                var_r25 = 1;
            }
            if ((jntNo == BO_UE1_JNT_J_BOKOBABA_SITA3_e) && (i_this->m2CC != 0)) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &local_80);
                f32 temp_f1 = i_this->m31C.x - local_80.x;
                f32 temp_f2 = i_this->m31C.z - local_80.z;
                if (i_this->m2CD != 0) {
                    local_88.x = -0x5FB4;
                    local_88.y = cM_atan2s(temp_f1, temp_f2) + 0x7FFF;
                    local_88.z = 0;
                    player->setPlayerPosAndAngle(&local_80, &local_88);
                } else {
                    local_88.x = 0x5BCC;
                    local_88.y = cM_atan2s(temp_f1, temp_f2);
                    local_88.z = 0;
                    player->setPlayerPosAndAngle(&local_80, &local_88);
                }
                var_r25 = 1;
            }
            if (var_r25) {
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 00000638-000006C8       .text nodeCallBack_DW__FP7J3DNodei */
static BOOL nodeCallBack_DW(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bo_class* i_this = (bo_class*)model->getUserArea();
        if ((i_this != NULL) && (jntNo == BO_SITA1_JNT_J_JH_ME_E_e)) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz offset;
            offset.x = 0.0f;
            offset.y = 0.0f;
            offset.z = 0.0f;
            MtxPosition(&offset, &i_this->m304);
        }
    }
    return TRUE;
}

/* 000006C8-0000079C       .text execute__22yodare_ato_PcallBack_cFP14JPABaseEmitterP15JPABaseParticle */
void yodare_ato_PcallBack_c::execute(JPABaseEmitter* emitter, JPABaseParticle* ptcl) {
    JGeometry::TVec3<f32> ptclPos;
    ptcl->getGlobalPosition(ptclPos);
    cXyz pos(ptclPos.x, ptclPos.y + 20.0f, ptclPos.z);
    mGndChk.SetPos(&pos);
    pos.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (pos.y > ptclPos.y) {
        dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODAPOTA00, &pos);
    }
}

/* 0000079C-00000930       .text draw_SUB__FP8bo_class */
static void draw_SUB(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if ((i_this->m2C0 == 0) || (i_this->m2C0 == 2)) {
        if (i_this->m2C0 == 2) {
            i_this->m304 = actor->current.pos;
            i_this->mpBrkAnm->play();
        }
        mDoMtx_stack_c::transS(i_this->m304.x, i_this->m304.y + i_this->m394, i_this->m304.z);
        mDoMtx_stack_c::YrotM(i_this->m348);
        mDoMtx_stack_c::XrotM(actor->shape_angle.x);
        mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
        mDoMtx_stack_c::transM(0.0f, -i_this->m394, 0.0f);
        i_this->mpHeadMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpHeadMorf->calc();
        if (i_this->m2C0 == 0) {
            enemy_fire(&i_this->mEnemyFire);
        }
    }
    if ((i_this->m2C0 == 0) || (i_this->m2C0 == 1)) {
        mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
        mDoMtx_stack_c::YrotM(actor->current.angle.y);
        mDoMtx_stack_c::XrotM(actor->shape_angle.x);
        mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
        i_this->mpBudMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpBudMorf->calc();
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
}

/* 00000930-00000AD4       .text daBO_Draw__FP8bo_class */
static BOOL daBO_Draw(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (REG13_S(5) != 0) {
        return TRUE;
    }
    bool bVar2 = false;
    if ((i_this->m2C0 == 0) || (i_this->m2C0 == 2)) {
        g_env_light.setLightTevColorType(i_this->mpHeadMorf->getModel(), &actor->tevStr);
    }
    if (((i_this->m2C0 == 0) || (i_this->m2C0 == 1)) && (i_this->mEnemyIce.mLightShrinkTimer == 0)) {
        g_env_light.setLightTevColorType(i_this->mpBudMorf->getModel(), &actor->tevStr);
    }
    dSnap_RegistFig(DSNAP_TYPE_BO, actor, actor->current.pos, i_this->m348, 1.0f, 1.0f, 1.0f);
    if ((i_this->m2C0 == 0) && (i_this->mEnemyIce.mFreezeTimer > 20)) {
        dMat_control_c::iceEntryDL(i_this->mpHeadMorf, -1, &i_this->mInvisibleModel);
        bVar2 = true;
    }
    if ((!bVar2) && ((i_this->m2C0 == 0) || (i_this->m2C0 == 2))) {
        J3DModel* model = i_this->mpHeadMorf->getModel();
        if (i_this->m2C0 == 2) {
            i_this->mpBrkAnm->entry(model->getModelData());
        }
        i_this->mpHeadMorf->entryDL();
        if (i_this->m2C0 == 2) {
            i_this->mpBrkAnm->remove(model->getModelData());
        }
    }
    if (((i_this->m2C0 == 0) || (i_this->m2C0 == 1)) && (i_this->mEnemyIce.mLightShrinkTimer == 0)) {
        i_this->mpBudMorf->entryDL();
    }

    return TRUE;
}

/* 00000AD4-00000CD4       .text anm_init__FP8bo_classifUcfii */
static void anm_init(bo_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx, int actorAnmType) {
    i_this->mCurrBckIdx = bckFileIdx;
    if (actorAnmType == ACTOR_ANM_TYPE_HEAD) {
        if (soundFileIdx >= 0) {
            i_this->mpHeadMorf->setAnm(
                (J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx),
                loopMode,
                morf,
                speed,
                0.0f,
                -1.0f,
                dComIfG_getObjectRes("BO", soundFileIdx)
            );
        } else {
            i_this->mpHeadMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    } else {
        if (soundFileIdx >= 0) {
            i_this->mpBudMorf->setAnm(
                (J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx),
                loopMode,
                morf,
                speed,
                0.0f,
                -1.0f,
                dComIfG_getObjectRes("BO", soundFileIdx)
            );
        } else {
            i_this->mpBudMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    }
}

/* 00000CD4-00000E24       .text shock_damage_check__FP8bo_class */
static BOOL shock_damage_check(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if (player->checkHammerQuake()) {
        cXyz swordTopPos = player->getSwordTopPos();
        swordTopPos.x -= actor->current.pos.x;
        swordTopPos.z -= actor->current.pos.z;
        if (std::sqrtf(SQUARE(swordTopPos.x) + SQUARE(swordTopPos.z)) < 1000.0f) {
            fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x31);
            return TRUE;
        }
    }
    return FALSE;
}

static s16 pl_cut_real_no_dt[] = {
    daPy_py_c::CUT_TYPE_NONE,
    daPy_py_c::CUT_TYPE_CUT_A,
    daPy_py_c::CUT_TYPE_CUT_F,
    daPy_py_c::CUT_TYPE_CUT_R,
    daPy_py_c::CUT_TYPE_CUT_L,
    daPy_py_c::CUT_TYPE_BT_JUMPCUT,
    daPy_py_c::CUT_TYPE_CUT_EA,
    daPy_py_c::CUT_TYPE_CUT_EB,
    daPy_py_c::CUT_TYPE_CUT_TURN,
    daPy_py_c::CUT_TYPE_CUT_ROLL,
    daPy_py_c::CUT_TYPE_JUMPCUT_SWORD,
    daPy_py_c::CUT_TYPE_STICK,
    daPy_py_c::CUT_TYPE_JUMPCUT_STICK,
    daPy_py_c::CUT_TYPE_MACHETE,
    daPy_py_c::CUT_TYPE_JUMPCUT_MACHETE,
    daPy_py_c::CUT_TYPE_BT_ROLLCUT,
    daPy_py_c::CUT_TYPE_BT_VERTICALJUMPCUT,
    daPy_py_c::CUT_TYPE_HAMMER_SIDESWING,
    daPy_py_c::CUT_TYPE_HAMMER_FRONTSWING,
    daPy_py_c::CUT_TYPE_JUMPCUT_HAMMER,
    daPy_py_c::CUT_TYPE_CLUB,
    daPy_py_c::CUT_TYPE_JUMPCUT_CLUB,
    daPy_py_c::CUT_TYPE_DN_SWORD,
    daPy_py_c::CUT_TYPE_JUMPCUT_DN_SWORD,
    daPy_py_c::CUT_TYPE_SPEAR,
    daPy_py_c::CUT_TYPE_JUMPCUT_SPEAR,
    daPy_py_c::CUT_TYPE_CUT_EXA,
    daPy_py_c::CUT_TYPE_CUT_EXB,
    daPy_py_c::CUT_TYPE_PG_SWORD,
    daPy_py_c::CUT_TYPE_JUMPCUT_PG_SWORD,
    daPy_py_c::CUT_TYPE_CUT_EXMJ,
    daPy_py_c::CUT_TYPE_CUT_KESA,
};

// nokezoru = recoil/lean back
static s8 nokezoru_on_off_dt[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, DEMO_SELECT(0x02, 0x01),
                                  0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

/* 00000E24-000013A4       .text head_atari_check__FP8bo_class */
static BOOL head_atari_check(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* hitObj;
    s8 sVar4;
    cXyz local_48;
    CcAtInfo atInfo;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if (i_this->mTimers[4] != 0) {
        return FALSE;
    }
    if (shock_damage_check(i_this)) {
        i_this->m2CA = 1;
        return TRUE;
    }
    if (!i_this->mHeadCoSph.ChkTgHit()) {
        return FALSE;
    }
    hitObj = i_this->mHeadCoSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    i_this->m358 = *i_this->mHeadCoSph.GetTgHitPosP();
    i_this->mTimers[4] = REG8_F(10) + 8.0f;
    i_this->m370 = cM_atan2s(player->current.pos.x - i_this->m2E0.x, player->current.pos.z - i_this->m2E0.z);
    i_this->m2CA = 0;
    i_this->m364 = 0;
    i_this->m2CA = 1;
    mDoAud_onEnemyDamage();
    switch (hitObj->GetAtType()) {
        case AT_TYPE_GRAPPLING_HOOK:
            if (actor->stealItemLeft > 0) {
                sVar4 = actor->health;
                actor->health = 10;
                atInfo.mpObj = i_this->mHeadCoSph.GetTgHitObj();
                atInfo.pParticlePos = NULL;
                cc_at_check(actor, &atInfo);
                actor->health = sVar4;
            }
            dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
            i_this->m2CA = 0;
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_NO_DAMAGE, 0);
            fopAcM_seStart(actor, JA_SE_LK_MS_WEP_CRT_HIT, 0x20);
            break;
        case AT_TYPE_SWORD:
            {
                s32 i = 0;
                for (; i < ARRAY_SIZE(pl_cut_real_no_dt); i++) {
                    if (pl_cut_real_no_dt[i] == player->getCutType()) {
                        break;
                    }
                }
                if (i >= ARRAY_SSIZE(pl_cut_real_no_dt)) {
                    return FALSE;
                }
                i_this->m2CA = nokezoru_on_off_dt[i];
                break;
            }
        case AT_TYPE_BOOMERANG:
            i_this->m2CA = 1;
            i_this->m364 = (REG8_S(5) + 5) & 0xFF;
            i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mHeadCoSph.ClrAtSet();
            i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
            i_this->m398 = 1.0f;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &i_this->m358);
            local_48.setall(2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &i_this->m358, &player->shape_angle, &local_48);
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_DIE, 0);
            fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0x20);
            break;
        case AT_TYPE_FIRE:
        case AT_TYPE_FIRE_ARROW:
            i_this->mEnemyFire.mFireDuration = REG8_F(12) + 34.0f;
            i_this->m2D0 = 1;
            actor->attention_info.flags = 0;
            break;
        case AT_TYPE_ICE_ARROW:
            i_this->mEnemyIce.mFreezeDuration = REG8_F(13) + 80.0f;
            i_this->m2D0 = 2;
            i_this->mEnemyIce.m00C = 1;
            actor->attention_info.flags = 0;
            actor->health = 30;
            break;
        case AT_TYPE_LIGHT_ARROW:
            {
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 1.0f;
                i_this->mEnemyIce.mYOffset = REG8_F(13) + 80.0f;
                actor->attention_info.flags = 0;
                i_this->m2D0 = 3;
                u32 r4 = i_this->m2C1 << 8;
                cLib_onBit<u32>(r4, 1);
                fopAcM_create(fpcNm_BO_e, r4, &actor->current.pos, fopAcM_GetRoomNo(actor), &actor->current.angle, &actor->scale, 0, NULL);
                break;
            }
        case AT_TYPE_SKULL_HAMMER:
            if (player->getCutType() != daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                i_this->m2CA = 2;
                break;
            }
        default:
            i_this->m2CA = 1;
            break;
    }
    return TRUE;
}

/* 000013A4-0000170C       .text nokezori_damage_rtn__FP8bo_class */
static void nokezori_damage_rtn(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* hitObj;
    cXyz local_2c;
    cXyz local_38;

    s16 temp_r29 = i_this->m370 - i_this->m348;
    anm_init(i_this, dRes_INDEX_BO_BCK_DAMAGE1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
    cMtx_YrotS(*calc_mtx, temp_r29);
    local_2c.x = 0.0f;
    local_2c.y = 0.0f;
    local_2c.z = 6250.0f;
    MtxPosition(&local_2c, &local_38);
    i_this->m340.z = local_38.x;
    i_this->m340.y = local_38.z;
    i_this->m334.setall(0);
    actor->scale.y = 1.75f;
    i_this->m37C = 0x4B0;
    hitObj = i_this->mHeadCoSph.GetTgHitObj();
    if (hitObj != NULL) {
        if (hitObj->ChkAtType(AT_TYPE_SWORD)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_NO_DAMAGE, 0);
            fopAcM_seStart(actor, JA_SE_LK_SW_CRT_HIT, 0x20);
        } else if (hitObj->ChkAtType(AT_TYPE_BOKO_STICK)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_NO_DAMAGE, 0);
            fopAcM_seStart(actor, JA_SE_LK_W_WEP_CRT_HIT, 0x20);
        } else if (hitObj->ChkAtType(AT_TYPE_SKULL_HAMMER)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_NO_DAMAGE, 0);
            fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x31);
        } else if (!hitObj->ChkAtType(AT_TYPE_BOOMERANG)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_NO_DAMAGE, 0);
            fopAcM_seStart(actor, JA_SE_LK_MS_WEP_CRT_HIT, 0x20);
        }
    }
    i_this->m398 = 1.0f;
    i_this->m372 = 0;
    i_this->m376 = 0;
    i_this->mTimers[2] = 3;
    if (i_this->m2D0 == 0) {
        i_this->mAction = ACTION_ATTACK;
        i_this->mMode = MODE_ATTACK_5;
    } else {
        i_this->mAction = ACTION_HEAD_DEATH_SPECIAL;
        i_this->mMode = MODE_HEAD_DEATH_SPECIAL_50;
    }
}

/* 0000170C-00001BB8       .text body_atari_check__FP8bo_class */
static BOOL body_atari_check(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* hitObj;
    cXyz local_2c;
    cXyz local_38;

    if (i_this->mTimers[2] != 0) {
        return FALSE;
    }
    if (!i_this->mBodyCyl.ChkTgHit()) {
        return FALSE;
    }
    hitObj = i_this->mBodyCyl.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    switch (hitObj->GetAtType()) {
        case AT_TYPE_FIRE:
        case AT_TYPE_FIRE_ARROW:
            i_this->mEnemyFire.mFireDuration = 80;
            i_this->m2D0 = 1;
            nokezori_damage_rtn(i_this);
            i_this->m2C8 = 0;
            i_this->m372 = 0;
            i_this->m374 = 0;
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_HIT00, &i_this->m328);
            return TRUE;
        case AT_TYPE_ICE_ARROW:
            i_this->mEnemyIce.mFreezeDuration = REG8_F(13) + 80.0f;
            i_this->m2D0 = 2;
            i_this->mEnemyIce.m00C = 1;
            actor->attention_info.flags = 0;
            actor->health = 30;
            nokezori_damage_rtn(i_this);
            i_this->m2C8 = 0;
            i_this->m372 = 0;
            i_this->m374 = 0;
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_HIT00, &i_this->m328);
            return TRUE;
        case AT_TYPE_LIGHT_ARROW:
            {
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 1.0f;
                i_this->mEnemyIce.mYOffset = REG8_F(13) + 80.0f;
                actor->attention_info.flags = 0;
                i_this->m2D0 = 3;
                u32 r4 = i_this->m2C1 << 8;
                cLib_onBit<u32>(r4, 1);
                fopAcM_create(fpcNm_BO_e, r4, &actor->current.pos, fopAcM_GetRoomNo(actor), &actor->current.angle, &actor->scale, 0, NULL);
                nokezori_damage_rtn(i_this);
                i_this->m2C8 = 0;
                i_this->m372 = 0;
                i_this->m374 = 0;
                dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_HIT00, &i_this->m328);
                fopAcM_monsSeStart(actor, JA_SE_CV_BV_DIE, 0);
                fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0x20);
                return TRUE;
            }
        default:
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            local_2c = *i_this->mBodyCyl.GetTgHitPosP();
            i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mHeadCoSph.ClrAtSet();
            i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
            i_this->m398 = 1.0f;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_2c);
            local_38.x = 2.0f;
            local_38.y = 2.0f;
            local_38.z = 2.0f;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_2c, &player->shape_angle, &local_38);
            i_this->m364 = (REG8_S(5) + 5) & 0xFF;
            i_this->mAction = ACTION_BUD_DEATH;
            i_this->mMode = MODE_BUD_DEATH_20;
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_DIE, 0);
            fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0x20);
            return TRUE;
    }
}

/* 00001BB8-00002048       .text damage_check__FP8bo_class */
static BOOL damage_check(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* hitObj;
    cXyz local_34;
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;

    if (head_atari_check(i_this)) {
        s16 temp_r29 = i_this->m370 - i_this->m348;
        if (i_this->m2CA == 2) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            local_4c = *i_this->mHeadCoSph.GetTgHitPosP();
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_4c);
            local_58.x = 2.0f;
            local_58.y = 2.0f;
            local_58.z = 2.0f;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_4c, &player->shape_angle, &local_58);
            i_this->mAction = ACTION_HEAD_DEATH_SPECIAL;
            i_this->mMode = MODE_HEAD_DEATH_SPECIAL_40;
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_DIE, 0);
            fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0x20);
            return TRUE;
        } else {
            i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mHeadCoSph.ClrAtSet();
            i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
            if (i_this->m2CA == 1) {
                nokezori_damage_rtn(i_this);
            } else {
                if ((REG8_F(11)) && (i_this->mMode == MODE_ATTACK_4)) {
                    return FALSE;
                }
                fopAcM_monsSeStart(actor, JA_SE_CV_BV_NO_DAMAGE, 0);
                local_34.x = 0.0f;
                local_34.y = 0.0f;
                local_34.z = 2250.0f;
                cMtx_YrotS(*calc_mtx, temp_r29);
                MtxPosition(&local_34, &local_40);
                anm_init(i_this, dRes_INDEX_BO_BCK_PUNCH1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                i_this->m352.z = local_40.x;
                i_this->m352.y = local_40.z;
                i_this->m388 = -10000.0f;
                i_this->m37E = 0;
                i_this->m380 = 0x1c52;
                i_this->m382 = i_this->m370 - i_this->m348;
                daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_R) {
                    i_this->m382 -= 0x4000;
                } else if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_L) {
                    i_this->m382 += 0x4000;
                }
                i_this->m37C = 0x800;
                hitObj = i_this->mHeadCoSph.GetTgHitObj();
                if (hitObj != NULL) {
                    if (hitObj->ChkAtType(AT_TYPE_SWORD)) {
                        fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x31);
                    } else if (hitObj->ChkAtType(AT_TYPE_BOKO_STICK)) {
                        fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x31);
                    } else {
                        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x31);
                    }
                }
                i_this->mAction = ACTION_ATTACK;
                i_this->mMode = MODE_ATTACK_4;
            }
            i_this->m2C8 = 0;
            i_this->m372 = 0;
            i_this->m374 = 0;
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_HIT00, &i_this->m328);
            return TRUE;
        }
    }
    return FALSE;
}

/* 00002048-00002080       .text angle_initial__FP8bo_class */
static void angle_initial(bo_class* i_this) {
    i_this->m33A.setall(0);
    i_this->m352.setall(0);
    i_this->m334.setall(0);
    i_this->m340.setall(0);
}

/* 00002080-00002170       .text wait_initial__FP8bo_class */
static void wait_initial(bo_class* i_this) {
    if (cM_rnd() < 0.5f) {
        anm_init(i_this, dRes_INDEX_BO_BCK_WAIT_L1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
    } else {
        anm_init(i_this, dRes_INDEX_BO_BCK_WAIT_R1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
    }
    i_this->mTimers[0] = cM_rndF(60.0f) + 60.0f;
    i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    i_this->mHeadCoSph.ClrAtSet();
    i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
    i_this->mHeadCoSph.OnCoSetBit();
    angle_initial(i_this);
    i_this->mAction = ACTION_ATTACK;
    i_this->mMode = MODE_ATTACK_2;
}

/* 00002170-000022F8       .text start_bakutsuki_event_camera__FP10fopAc_ac_c */
static void start_bakutsuki_event_camera(fopAc_ac_c* a_this) {
    bo_class* i_this = (bo_class*)a_this;

    static cXyz cam_pos(40.0f, 10.0f, 280.0f);
    static cXyz ctr_pos(0.0f, 50.0f, 50.0f);
    static f32 cam_fovy = 75.0f;
    static s32 cam_timer = 30;
    dComIfGp_getCamera(0)->mCamera.StartEventCamera(
        5,
        fopAcM_GetID(i_this),
        "RelActor",
        "@STARTER",
        "RelUseMask",
        "--or",
        "Timer",
        &cam_timer,
        "Center",
        &ctr_pos,
        "Eye",
        &cam_pos,
        "Fovy",
        &cam_fovy,
        0
    );
}

/* 000022F8-0000233C       .text end_event_camera__FP10fopAc_ac_c */
static void end_event_camera(fopAc_ac_c* a_this) {
    bo_class* i_this = (bo_class*)a_this;

    dComIfGp_getCamera(0)->mCamera.EndEventCamera(fopAcM_GetID(i_this));
}

/**
 * Attacking
 */
/* 0000233C-00002FC4       .text bo_move__FP8bo_class */
static void bo_move(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 frame;
    cXyz local_4c;
    cXyz local_58;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mMode) {
        case MODE_ATTACK_0:
            {
                f32 f31 = 600.0f;
                if (fopAcM_searchPlayerDistance(actor) < f31) {
                    i_this->mBodyCyl.OnTgSetBit();
                    i_this->mHeadCoSph.OnTgSetBit();
                    i_this->mHeadCoSph.OnCoSetBit();
                    fopAcM_seStart(actor, JA_SE_CM_BV_HEAD_POPUP, 0);
                    fopAcM_monsSeStart(actor, JA_SE_CV_BV_ENTER, 0);
                    anm_init(i_this, dRes_INDEX_BO_BCK_DERU_U1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                    anm_init(i_this, dRes_INDEX_BO_BCK_DERU_S1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_BUD);
                    i_this->mHeadCoSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mHeadCoSph.OnAtHitBit();
                    i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK1);
                    i_this->mHeadCoSph.OffAtNoTgHitInfSet();
                    cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
                    i_this->mMode = MODE_ATTACK_1;
                }
                break;
            }
        case MODE_ATTACK_3:
            {
                f32 f2 = 27.0f;
                f32 f1 = 38.0f;
                f32 f3 = 55.0f;
                if (i_this->mCurrBckIdx == dRes_INDEX_BO_BCK_ATTACK1_e) {
                    frame = i_this->mpHeadMorf->getFrame();
                    if ((frame < f2) || (frame >= f3)) {
                        i_this->m34E = fopAcM_searchPlayerAngleY(actor);
                    } else if (frame < f1) {
                        if (f2 == frame) {
                            i_this->mHeadCoSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                            i_this->mHeadCoSph.OnAtHitBit();
                            fopAcM_seStart(actor, JA_SE_CM_BV_ATTACK, 0);
                        } else {
                            s16 r27 = false;
                            if (i_this->mHeadCoSph.ChkAtShieldHit()) {
                                i_this->mMode = MODE_ATTACK_6;
                                r27 = true;
                            } else if (i_this->mHeadCoSph.ChkAtHit()) {
                                fopAc_ac_c* hit_ac = i_this->mHeadCoSph.GetAtHitAc();
                                if ((hit_ac != NULL) && (hit_ac == player)) {
                                    r27 = true;
                                }
                            }
                            if (r27) {
                                i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                                i_this->mHeadCoSph.ClrAtSet();
                                i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
                                anm_init(i_this, dRes_INDEX_BO_BCK_HANEKAERI1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                            }
                        }
                    } else if (i_this->mpHeadMorf->checkFrame(38.0f)) {
                        i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                        i_this->mHeadCoSph.ClrAtSet();
                        i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
                    }
                }
                // Fall-through
            }
        case MODE_ATTACK_6:
            if (i_this->mpHeadMorf->isStop()) {
                i_this->mTimers[1] = cM_rndF(30.0f) + 30.0f;
                wait_initial(i_this);
            }
            break;
        case MODE_ATTACK_1:
            {
                i_this->m34E = fopAcM_searchPlayerAngleY(actor);
                if (i_this->m3D0 == NULL) {
                    i_this->m3D0 = dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_APP00, &actor->current.pos);
                } else {
                    i_this->m3D0->setGlobalRTMatrix(i_this->mpHeadMorf->getModel()->getAnmMtx(BO_UE1_JNT_J_BOKOBABA_AGO_e));
                }
                f32 f1 = 39.0f;
                if (i_this->mpHeadMorf->getFrame() > f1) {
                    i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
                    i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mHeadCoSph.ClrAtSet();
                }
                if (i_this->mpHeadMorf->isStop()) {
                    if (i_this->m3D0 != NULL) {
                        i_this->m3D0->becomeInvalidEmitter();
                        i_this->m3D0 = NULL;
                    }
                    wait_initial(i_this);
                }
                break;
            }
        case MODE_ATTACK_2:
            f32 f31;
            if (i_this->mTimers[3] == 0) {
                if (i_this->m3D4 == NULL) {
                    i_this->m3D4 = dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_WAIT00, &actor->current.pos);
                    if (i_this->m3D4 != NULL) {
                        i_this->m3D4->setParticleCallBackPtr(&i_this->mDroolCb);
                    }
                    i_this->m2C6 = 0;
                } else {
                    i_this->m3D4->setGlobalSRTMatrix(i_this->mpHeadMorf->getModel()->getAnmMtx(BO_UE1_JNT_J_BOKOBABA_AGO_e));
                }
                if (i_this->mTimers[0] == 0) {
                    frame = i_this->mpHeadMorf->getFrame();
                    if (i_this->mCurrBckIdx == dRes_INDEX_BO_BCK_WAIT_R1_e) {
                        anm_init(i_this, dRes_INDEX_BO_BCK_WAIT_L1_e, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                    } else {
                        anm_init(i_this, dRes_INDEX_BO_BCK_WAIT_R1_e, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                    }
                    i_this->mpHeadMorf->setFrame(frame);
                    i_this->mTimers[0] = cM_rndF(60.0f) + 60.0f;
                }
                f31 = 380.0f;
                f32 f30 = 0.5f;
                if ((i_this->mTimers[1] == 0) && (fopAcM_searchPlayerDistance(actor) < f31)) {
                    anm_init(i_this, dRes_INDEX_BO_BCK_ATTACK1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                    if (cM_rnd() < f30) {
                        i_this->mHeadCoSph.SetAtAtp(0);
                        i_this->mAction = ACTION_EAT;
                        i_this->mMode = MODE_EAT_10;
                    } else {
                        i_this->mHeadCoSph.SetAtAtp(1);
                        i_this->mHeadCoSph.OffAtNoTgHitInfSet();
                        i_this->mHeadCoSph.OnCoSetBit();
                        fopAcM_monsSeStart(actor, JA_SE_CV_BV_ATTACK, 0);
                        i_this->mMode = MODE_ATTACK_3;
                    }
                } else {
                    f31 = 900.0f;
                    if (fopAcM_searchPlayerDistance(actor) > f31) {
                        anm_init(i_this, dRes_INDEX_BO_BCK_MODORU_U1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                        anm_init(i_this, dRes_INDEX_BO_BCK_MODORU_S1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_BUD);
                        cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
                        fopAcM_seStart(actor, JA_SE_CM_BV_HEAD_IN_BASE, 0);
                        i_this->mBodyCyl.OffTgSetBit();
                        i_this->mHeadCoSph.OffTgSetBit();
                        i_this->mHeadCoSph.ClrCoSet();
                        i_this->mBodyCyl.ClrTgHit();
                        i_this->mHeadCoSph.ClrTgHit();
                        angle_initial(i_this);
                        i_this->mMode = MODE_ATTACK_0;
                    }
                }
                i_this->m34E = fopAcM_searchPlayerAngleY(actor);
            }
            break;
        case MODE_ATTACK_4:
            if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_R) {
                cMtx_YrotS(*calc_mtx, i_this->m37E);
            } else {
                cMtx_YrotS(*calc_mtx, -i_this->m37E);
            }
            local_4c.x = 0.0f;
            local_4c.y = 0.0f;
            local_4c.z = i_this->m388;
            MtxPosition(&local_4c, &local_58);
            i_this->m334.y = local_58.z;
            i_this->m334.z = local_58.x;
            i_this->m37E += i_this->m380;
            cLib_addCalc0(&i_this->m388, 1.0f, 250.0f);
            cLib_addCalcAngleS2(&i_this->m352.y, 0, 1, 0x87);
            cLib_addCalcAngleS2(&i_this->m352.z, 0, 1, 0x87);
            //! @bug(?): This is probably supposed to be std::fabsf
            if (fabs(i_this->m388) < 1.0f) {
                i_this->m352.setall(0);
                i_this->m334.setall(0);
                i_this->mTimers[0] = 0;
                i_this->mMode = MODE_ATTACK_2;
                if (i_this->m364 != 0) {
                    i_this->mTimers[3] = 45;
                }
            }
            break;
        case MODE_ATTACK_5:
            {
                if (i_this->m364 != 0) {
                    i_this->m364--;
                }
                if (i_this->m364 == 1) {
                    i_this->mAction = ACTION_BUD_DEATH;
                    i_this->mMode = MODE_BUD_DEATH_20;
                    return;
                }
                if ((i_this->m372 < 0x10) && ((i_this->m2C8 & 1) == 0) && ((s16)cLib_distanceAngleS(i_this->m33A.y, i_this->m340.y) < 0x100)) {
                    i_this->m340.y ^= 0xFF00;
                    i_this->m340.y *= 0.1f;
                    i_this->m372++;
                    if (i_this->m372 >= 0x10) {
                        i_this->m340.y = 0;
                        i_this->m33A.y = 0;
                        i_this->m2C8 |= 1;
                    }
                }
                if ((i_this->m374 < 0x10) && ((i_this->m2C8 & 2) == 0) && ((s16)cLib_distanceAngleS(i_this->m33A.z, i_this->m340.z) < 0x100)) {
                    i_this->m340.z ^= 0xFF00;
                    i_this->m340.z *= 0.1f;
                    i_this->m374++;
                    if (i_this->m374 >= 0x10) {
                        i_this->m340.z = 0;
                        i_this->m33A.z = 0;
                        i_this->m2C8 |= 2;
                    }
                }
                if ((i_this->m340.y == 0) && (i_this->m340.z == 0)) {
                    i_this->m376++;
                }
                s16 r0 = 30;
                if (i_this->m376 > r0) {
                    wait_initial(i_this);
                    i_this->m376 = 0;
                    i_this->m398 = 1.0f;
                }
                if (i_this->m2D0 == 0) {
                    body_atari_check(i_this);
                }
                break;
            }
        case MODE_ATTACK_7:
            if (i_this->mpHeadMorf->isStop()) {
                i_this->mMode = MODE_ATTACK_0;
            }
            break;
    }
#if VERSION == VERSION_DEMO
    fopEn_enemy_c* e_this = &i_this->actor;
    e_this->setBtNowFrame(1000.0f);
    if ((i_this->mMode == MODE_ATTACK_3) && (i_this->mCurrBckIdx == dRes_INDEX_BO_BCK_ATTACK1_e)) {
        u8 var_r0 = 0;
        if ((i_this->mpHeadMorf->getFrame() >= 19.0f) && (i_this->mpHeadMorf->getFrame() <= 55.0f)) {
            var_r0 = 1;
        }
        if (var_r0 != 0) {
            e_this->setBtNowFrame(5.0f);
        }
    }
#endif
    cLib_addCalcAngleS2(&i_this->m348, i_this->m34E, 1, 0x800);
    cLib_addCalcAngleS2(&i_this->m33A.y, i_this->m340.y, 1, i_this->m37C);
    cLib_addCalcAngleS2(&i_this->m33A.z, i_this->m340.z, 1, i_this->m37C);
    if (i_this->mMode == MODE_ATTACK_4) {
        s16 r0 = 0x337F;
        if ((s16)cLib_distanceAngleS(fopAcM_searchPlayerAngleY(actor), i_this->m348) > r0) {
            wait_initial(i_this);
            anm_init(i_this, dRes_INDEX_BO_BCK_MODORU_U1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
            anm_init(i_this, dRes_INDEX_BO_BCK_MODORU_S1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_BUD);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
            fopAcM_seStart(actor, JA_SE_CM_BV_HEAD_IN_BASE, 0);
            i_this->mBodyCyl.OffTgSetBit();
            i_this->mHeadCoSph.OffTgSetBit();
            i_this->mHeadCoSph.ClrCoSet();
            i_this->mBodyCyl.ClrTgHit();
            i_this->mHeadCoSph.ClrTgHit();
            i_this->mMode = MODE_ATTACK_7;
            return;
        }
    }
    if ((i_this->mMode != MODE_ATTACK_0) && (i_this->mMode != MODE_ATTACK_5)) {
        if (damage_check(i_this)) {
            return;
        };
    }
}

/**
 * Eating
 */
/* 00002FC4-0000380C       .text bo2_move__FP8bo_class */
static void bo2_move(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
#if VERSION == VERSION_DEMO
    f32 stickPosY;
    f32 stickPosX;
    stickPosX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    stickPosY = g_mDoCPd_cpadInfo[0].mMainStickPosY;
#else
    f32 stickPosX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    f32 stickPosY = g_mDoCPd_cpadInfo[0].mMainStickPosY;
#endif
    f32 f30;
    f32 f31;
    switch (i_this->mMode) {
        case MODE_EAT_10: // Eat attempt
            anm_init(i_this, dRes_INDEX_BO_BCK_TABERU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
            fopAcM_seStart(actor, JA_SE_CM_BV_SHITA, 0);
            i_this->mHeadCoSph.OnAtNoTgHitInfSet();
            i_this->mHeadCoSph.ClrCoSet();
            i_this->m2CB = 0;
            i_this->m2CC = 0;
            i_this->mMode++;
            break;
        case MODE_EAT_11: // Check if it grabbed Link
            {
                f30 = 28.0f;
                f31 = 33.0f;
                if ((i_this->mpHeadMorf->getFrame() >= f30) && (i_this->mpHeadMorf->getFrame() <= f31) && (i_this->mHeadCoSph.ChkAtHit())) {
                    fopAc_ac_c* hit_ac = i_this->mHeadCoSph.GetAtHitAc();
                    if ((hit_ac != NULL) && (hit_ac == player)) {
                        i_this->m2CB = 1;
                    }
                }
                if (i_this->mpHeadMorf->checkFrame(DEMO_SELECT(f30 - 1.0f, 27.0f))) {
                    i_this->mHeadCoSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mHeadCoSph.OnAtHitBit();
                    fopAcM_monsSeStart(actor, JA_SE_CV_BV_BITE, 0);
                }
                if (i_this->mpHeadMorf->checkFrame(f31)) {
                    i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mHeadCoSph.ClrAtSet();
                    i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
                }
                if (i_this->mpHeadMorf->isStop()) {
                    wait_initial(i_this);
                    i_this->mTimers[1] = cM_rndF(30.0f) + 30.0f;
                }
                break;
            }
        case MODE_EAT_12: // Start chewing
            {
                f31 = 33.0f;
                if ((i_this->m2CC == 0) && (i_this->mpHeadMorf->checkFrame(f31) || (i_this->mpHeadMorf->getFrame() >= f31))) {
                    player->changeOriginalDemo();
                    player->changeDemoMode(daPy_demo_c::DEMO_UNK_030_e);
                    s16 sVar6 = cLib_distanceAngleS(player->shape_angle.y, fopAcM_searchActorAngleY(player, actor));
                    i_this->m2CD = 0;
                    if (sVar6 > 0x4000) {
                        i_this->m2CD = 1;
                    }
                    i_this->m2CC = 1;
                }
                if (i_this->mpHeadMorf->isStop()) {
                    anm_init(i_this, dRes_INDEX_BO_BCK_KAMU1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                    emitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_MOG00, &actor->current.pos);
                    if (emitter != NULL) {
                        emitter->setGlobalSRTMatrix(i_this->mpHeadMorf->getModel()->getAnmMtx(BO_UE1_JNT_J_BOKOBABA_AGO_e));
                    }
                    i_this->m376 = 0;
                    i_this->mTimers[1] = 0;
                    i_this->m2D4 = 1;
                    i_this->m2D8 = 1;
                    fopAcM_monsSeStart(actor, JA_SE_CV_BV_EATING, 0);
                    i_this->mMode++;
                }
                break;
            }
        case MODE_EAT_13: // Continue chewing/spit out
            {
                if (i_this->m3D8 == NULL) {
                    i_this->m3D8 = dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_WAIT00, &actor->current.pos);
                    if (i_this->m3D8 != NULL) {
                        i_this->m3D8->setParticleCallBackPtr(&i_this->mDroolCb);
                        i_this->m3D8->setRate(0.07f);
                    }
                    i_this->m2C7 = 0;
                } else {
                    i_this->m3D8->setGlobalSRTMatrix(i_this->mpHeadMorf->getModel()->getAnmMtx(BO_UE1_JNT_J_BOKOBABA_AGO_e));
                }
                if (i_this->mTimers[1] == 0) {
#if VERSION == VERSION_DEMO
                    dComIfGp_setItemLifeCount(-1.0f);
#else
                    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
                    if (!link->checkNoDamageMode()) {
                        link->setDamagePoint(-1.0f);
                    }
#endif
                    i_this->mTimers[1] = 30;
                }
                i_this->m376++;
                s16 r0 = 120;
                if (i_this->m376 > r0) {
                    i_this->m376 = 0;
                    anm_init(i_this, dRes_INDEX_BO_BCK_HAKIDASU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                    fopAcM_monsSeStart(actor, JA_SE_CM_BV_LINK_OUT, 0);
                    end_event_camera(actor);
                    i_this->mMode++;
                } else {
                    if (i_this->mpHeadMorf->checkFrame(0.0f)) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_BV_EATING, 0);
                        emitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODARE_MOG00, &actor->current.pos);
                        if (emitter != NULL) {
                            emitter->setGlobalSRTMatrix(i_this->mpHeadMorf->getModel()->getAnmMtx(BO_UE1_JNT_J_BOKOBABA_AGO_e));
                        }
                    }
                    if ((i_this->m2D4 > 0) && (stickPosX < 0.0f)) {
                        i_this->m2D4 = -1;
                        i_this->m376 += 2;
                    } else if ((i_this->m2D4 < 0) && (stickPosX > 0.0f)) {
                        i_this->m2D4 = 1;
                        i_this->m376 += 2;
                    }
                    if ((i_this->m2D8 > 0) && (stickPosY < 0.0f)) {
                        i_this->m2D8 = -1;
                        i_this->m376 += 2;
                    } else if ((i_this->m2D8 < 0) && (stickPosY > 0.0f)) {
                        i_this->m2D8 = 1;
                        i_this->m376 += 2;
                    }
                    if (CPad_CHECK_TRIG_A(0)) {
                        i_this->m376 += 2;
                    }
                }
                break;
            }
        case MODE_EAT_14:
            {
                f31 = 9.0f;
                if (i_this->mpHeadMorf->checkFrame(f31)) {
                    player->current.angle.y = i_this->m348;
                    player->changeDemoMode(daPy_demo_c::DEMO_LDAM_e);
                    i_this->m2CC = 0;
                    if (i_this->m2CD != 0) {
                        player->changeDemoParam0(0);
                    } else {
                        player->changeDemoParam0(1);
                    }
                }
                if (i_this->mpHeadMorf->isStop()) {
                    dComIfGp_event_reset();
                    wait_initial(i_this);
                    i_this->mTimers[1] = cM_rndF(30.0f) + 30.0f;
                    i_this->mTimers[1] <<= 1;
                }
                break;
            }
    }
    if ((i_this->mMode < MODE_EAT_12) && (i_this->m2CB == 0)) {
        if (damage_check(i_this)) {
            return;
        }
    }
}

/**
 * Bud death
 */
/* 0000380C-00003AD4       .text bo3_move__FP8bo_class */
static void bo3_move(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u8 i_dropType;
    csXyz local_18;

    switch (i_this->mMode) {
        case MODE_BUD_DEATH_20:
            if (i_this->m364 != 0) {
                i_this->m364--;
            }
            if (i_this->m364 == 0) {
                i_this->mBodyCyl.OffTgSetBit();
                i_this->mHeadCoSph.OffTgSetBit();
                i_this->mHeadCoSph.ClrCoSet();
                i_this->mBodyCyl.ClrTgHit();
                i_this->mHeadCoSph.ClrTgHit();
                local_18.x = actor->current.angle.x;
                local_18.y = i_this->m348;
                local_18.z = actor->current.angle.z;
                if (i_this->m2CE == 0) {
                    fopAcM_create(fpcNm_BO_e, 2, &i_this->m304, fopAcM_GetRoomNo(actor), &local_18, &actor->scale, 0, NULL);
                }
                i_this->m2CE = 0;
                i_this->m2C0 = 1;
                anm_init(i_this, dRes_INDEX_BO_BCK_SIORERU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_BUD);
                dScnPly_ply_c::setPauseTimer(4);
                i_this->mMode++;
            }
            break;
        case MODE_BUD_DEATH_21:
            if (i_this->mpBudMorf->checkFrame(43.0f)) {
                i_dropType = daDisItem_IBALL_e;
                if (i_this->m2C1 != 0) {
                    i_dropType = daDisItem_NONE3_e;
                    i_this->mTimers[1] = 50;
                }
                if (i_this->m2D0 != 3) {
                    fopAcM_createDisappear(actor, &actor->current.pos, 5, i_dropType, actor->stealItemBitNo);
                }
            }
            if (i_this->mpBudMorf->isStop()) {
                if (i_this->m2C1 != 0) {
                    i_this->mMode++;
                } else {
                    fopAcM_onActor(actor);
                    fopAcM_delete(actor);
                }
            }
            break;
        case MODE_BUD_DEATH_22:
            if (i_this->mTimers[1] == 0) {
                fopAcM_create(fpcNm_JBO_e, 1, &actor->current.pos, fopAcM_GetRoomNo(actor), &actor->current.angle, &actor->scale, 0, NULL);
                fopAcM_onActor(actor);
                fopAcM_delete(actor);
            }
            break;
    }
#if VERSION == VERSION_DEMO
    if ((i_this->m3D0_demo != NULL) && (i_this->mTimers[2] == 0)) {
        i_this->m3D0_demo->setGlobalAlpha(i_this->m376);
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmokeCb.remove();
            i_this->m3D0_demo = NULL;
        }
    }
#else
    if ((i_this->mSmokeCb.getEmitter() != NULL) && (i_this->mTimers[2] == 0)) {
        i_this->mSmokeCb.getEmitter()->setGlobalAlpha(i_this->m376);
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmokeCb.remove();
        }
    }
#endif
}

/**
 * Head death (normal)
 */
/* 00003AD4-00003E8C       .text bo4_move__FP8bo_class */
static void bo4_move(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    csXyz local_28;
    cXyz local_20;

    switch (i_this->mMode) {
        case MODE_HEAD_DEATH_NORMAL_30:
            i_this->mHeadCoSph.OffTgSetBit();
            i_this->mHeadCoSph.ClrCoSet();
            i_this->mHeadCoSph.ClrAtSet();
            i_this->mHeadCoSph.ClrTgHit();
            i_this->mHeadCoSph.ClrTgHit();
            anm_init(i_this, dRes_INDEX_BO_BCK_DAMAGE1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
            actor->speed.y = 30.0f;
            actor->gravity = -3.0f;
            actor->speedF = 10.0f;
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            i_this->m390 = actor->current.pos.y - 80.0f;
            i_this->mMode++;
            break;
        case MODE_HEAD_DEATH_NORMAL_31:
            actor->shape_angle.x -= 0x1200;
            if ((actor->speed.y < 0.0f) && (actor->current.pos.y < i_this->m390)) {
                actor->current.pos.y = i_this->m390;
                actor->shape_angle.x = 0x8000;
                actor->speed.y = 0.0f;
                actor->gravity = 0.0f;
                actor->speedF = 0.0f;
                i_this->mTimers[1] = 10;
                fopAcM_seStart(actor, JA_SE_CM_BV_HEAD_TO_BOKO, 0);
                dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_DEAD00, &i_this->m328);
                i_this->mTimers[2] = 10;
                i_this->m376 = 180;
                i_this->m39C = i_this->m328;
                smoke_set(i_this);
                anm_init(i_this, dRes_INDEX_BO_BCK_BOU1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
                i_this->mMode++;
            }
            break;
        case MODE_HEAD_DEATH_NORMAL_32:
            if (i_this->mTimers[1] == 0) {
                i_this->m394 = 200.0f;
                actor->current.pos.y = i_this->m390 - 200.0f;
                actor->speed.y = 10.0f;
                actor->gravity = -1.0f;
                i_this->mMode++;
            }
            break;
        case MODE_HEAD_DEATH_NORMAL_33:
            actor->shape_angle.z += 0x1000;
            if (actor->shape_angle.z > 0x4000) {
                local_28.x = 0;
                local_28.y = i_this->m348 + 0xC000;
                local_28.z = 0;
                local_20 = i_this->m310;
                local_20.y = i_this->m390 + 30.0f;
                fopAcM_create(fpcNm_BOKO_e, daBoko_c::Type_BOKO_STICK_e, &local_20, fopAcM_GetRoomNo(actor), &local_28, &actor->scale, 0, NULL);
                actor->scale.setall(0.0f);
                i_this->m398 = 0.0f;
                i_this->mTimers[1] = 10;
                i_this->mMode++;
            }
            break;
        case MODE_HEAD_DEATH_NORMAL_34:
            if ((i_this->mTimers[1] == 0) && (DEMO_SELECT(i_this->m3D0_demo, i_this->mSmokeCb.getEmitter()) == NULL)) {
                fopAcM_delete(actor);
            }
            break;
    }
#if VERSION == VERSION_DEMO
    if ((i_this->m3D0_demo != NULL) && (i_this->mTimers[2] == 0)) {
        i_this->m3D0_demo->setGlobalAlpha(i_this->m376);
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmokeCb.remove();
            i_this->m3D0_demo = NULL;
        }
    }
#else
    if ((i_this->mSmokeCb.getEmitter() != NULL) && (i_this->mTimers[2] == 0)) {
        i_this->mSmokeCb.getEmitter()->setGlobalAlpha(i_this->m376);
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmokeCb.remove();
        }
    }
#endif
}

/**
 * Head death (special)
 */
/* 00003E8C-000042B8       .text bo5_move__FP8bo_class */
static void bo5_move(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mMode) {
        case MODE_HEAD_DEATH_SPECIAL_40: // Skull Hammer death
            i_this->m376 = 3;
            i_this->mBodyCyl.OffTgSetBit();
            i_this->mHeadCoSph.OffTgSetBit();
            i_this->mHeadCoSph.ClrCoSet();
            i_this->mBodyCyl.ClrTgHit();
            i_this->mHeadCoSph.ClrTgHit();
            dScnPly_ply_c::setPauseTimer(2);
            anm_init(i_this, dRes_INDEX_BO_BCK_KUSIZASI1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_DIE, 0);
            fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0x20);
            i_this->mMode++;
            break;
        case MODE_HEAD_DEATH_SPECIAL_41:
            if (!i_this->mpHeadMorf->checkFrame(15.0f)) {
                break;
            }
            i_this->m376--;
            if (i_this->m376 > 0) {
                break;
            }
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
            anm_init(i_this, dRes_INDEX_BO_BCK_DERU_U1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1, ACTOR_ANM_TYPE_HEAD);
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_DEAD00, &i_this->m328, NULL, NULL, 0xFF, NULL, -1, &actor->tevStr.mColorK0);
            i_this->m39C = i_this->m328;
            i_this->mTimers[2] = 10;
            i_this->m376 = 180;
            smoke_set(i_this);
            fopAcM_seStart(actor, JA_SE_CM_MONS_EXPLODE, 0);
            i_this->m2CE = 1;
            i_this->mAction = ACTION_BUD_DEATH;
            i_this->mMode = MODE_BUD_DEATH_20;
            break;
        case MODE_HEAD_DEATH_SPECIAL_50: // Elemental arrow death
            i_this->mBodyCyl.OffTgSetBit();
            i_this->mHeadCoSph.OffTgSetBit();
            i_this->mHeadCoSph.ClrCoSet();
            i_this->mBodyCyl.ClrTgHit();
            i_this->mHeadCoSph.ClrTgHit();
            dScnPly_ply_c::setPauseTimer(2);
            anm_init(i_this, dRes_INDEX_BO_BCK_KARERU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, ACTOR_ANM_TYPE_HEAD);
            actor->attention_info.flags = 0;
            fopAcM_monsSeStart(actor, JA_SE_CV_BV_DIE, 0);
            fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0x20);
            i_this->mMode++;
        // Fall-through
        case MODE_HEAD_DEATH_SPECIAL_51:
            if (i_this->mTimers[0] == 0) {
                if (i_this->mpHeadMorf->isStop()) {
                    i_this->mTimers[2] = 10;
                    i_this->m376 = 180;
                    i_this->m2CE = 1;
                    i_this->mAction = ACTION_BUD_DEATH;
                    i_this->mMode = MODE_BUD_DEATH_20;
                }
            }
            break;
    }
}

/* 000042B8-000048B0       .text daBO_Execute__FP8bo_class */
static BOOL daBO_Execute(bo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;
    cXyz local_2c;
    cXyz local_38;

    if ((i_this->m2C0 == 0) && (enemy_ice(&i_this->mEnemyIce))) {
        if (i_this->mEnemyIce.mLightShrinkTimer != 0) {
            i_this->mpHeadMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
            i_this->mpHeadMorf->calc();
        } else {
            i_this->mHeadCoSph.SetC(i_this->m2E0);
            i_this->mHeadCoSph.SetR(60.0f);
            dComIfG_Ccsp()->Set(&i_this->mHeadCoSph);
        }
        return TRUE;
    }
    for (s32 i = 0; i < ARRAY_SIZE(i_this->mTimers); i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }
    switch (i_this->mAction) {
        case ACTION_ATTACK:
            bo_move(i_this);
            actor->shape_angle = actor->current.angle;
            break;
        case ACTION_EAT:
            bo2_move(i_this);
            if (i_this->m2CB != 0) {
                if (actor->eventInfo.checkCommandDemoAccrpt()) {
                    if (i_this->mAction != ACTION_EAT) {
                        dComIfGp_event_reset();
                    } else {
                        i_this->mMode = MODE_EAT_12;
                        start_bakutsuki_event_camera(actor);
                    }
                    i_this->m2CB = 0;
                } else {
                    fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                    actor->eventInfo.onCondition(dEvtCmd_INDEMO_e);
                }
            }
            break;
        case ACTION_BUD_DEATH:
            bo3_move(i_this);
            break;
        case ACTION_HEAD_DEATH_NORMAL:
            bo4_move(i_this);
            break;
        case ACTION_HEAD_DEATH_SPECIAL:
            bo5_move(i_this);
            break;
    }
    if ((i_this->m2C6 != 0) || ((i_this->mCurrBckIdx != dRes_INDEX_BO_BCK_WAIT_R1_e) && (i_this->mCurrBckIdx != dRes_INDEX_BO_BCK_WAIT_L1_e))) {
        if (i_this->m3D4 != NULL) {
            i_this->m3D4->setGlobalSRTMatrix(i_this->mpHeadMorf->getModel()->getAnmMtx(BO_UE1_JNT_J_BOKOBABA_AGO_e));
            switch (i_this->m2C6) {
                case 0:
                    i_this->m3D4->stopCreateParticle();
                    i_this->m2C6++;
                    break;
                case 1:
                    if (i_this->m3D4->getParticleNumber() == 0) {
                        i_this->m3D4->setParticleCallBackPtr(NULL);
                        i_this->m3D4->becomeInvalidEmitter();
                        i_this->m3D4 = NULL;
                        i_this->m2C6 = 0;
                    }
                    break;
            }
        }
    }
    if ((i_this->m2C7 != 0) || (i_this->mCurrBckIdx != dRes_INDEX_BO_BCK_KAMU1_e)) {
        if (i_this->m3D8 != NULL) {
            i_this->m3D8->setGlobalSRTMatrix(i_this->mpHeadMorf->getModel()->getAnmMtx(BO_UE1_JNT_J_BOKOBABA_AGO_e));
            switch (i_this->m2C7) {
                case 0:
                    i_this->m3D8->stopCreateParticle();
                    i_this->m2C7++;
                    break;
                case 1:
                    if (i_this->m3D8->getParticleNumber() == 0) {
                        i_this->m3D8->setParticleCallBackPtr(NULL);
                        i_this->m3D8->becomeInvalidEmitter();
                        i_this->m3D8 = NULL;
                        i_this->m2C7 = 0;
                    }
                    break;
            }
        }
    }
    cLib_addCalc2(&actor->scale.y, i_this->m398, 1.0f, 0.0875f);
    i_this->mStts.SetWeight(0xFF);
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    local_20.x = 0.0f;
    local_20.y = 0.0f;
    local_20.z = actor->speedF;
    MtxPosition(&local_20, &local_2c);
    actor->speed.x = local_2c.x;
    actor->speed.y = actor->speed.y + actor->gravity;
    actor->speed.z = local_2c.z;
    fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
    if ((i_this->m2C0 == 0) || (i_this->m2C0 == 2)) {
        i_this->mpHeadMorf->play(NULL, 0, 0);
    }
    if ((i_this->m2C0 == 0) || (i_this->m2C0 == 1)) {
        i_this->mpBudMorf->play(NULL, 0, 0);
    }
    if (i_this->m2C0 == 0) {
        if (i_this->mMode != MODE_ATTACK_5) {
            actor->attention_info.position = i_this->m2E0;
            actor->attention_info.position.y += 60.0f;
            actor->eyePos = i_this->m328;
        } else {
            actor->eyePos = i_this->m2F8;
            actor->eyePos.y += 60.0f;
            actor->attention_info.position = actor->eyePos;
        }
    }
    if ((i_this->m2CC != 0) || (i_this->mMode == MODE_EAT_12)) {
        actor->attention_info.position = actor->current.pos;
        actor->attention_info.position.y += 60.0f;
        actor->shape_angle.y = i_this->m348;
    }
    i_this->mHeadCoSph.SetC(i_this->m2E0);
    i_this->mHeadCoSph.SetR(60.0f);
    dComIfG_Ccsp()->Set(&i_this->mHeadCoSph);
    if (i_this->mAction == ACTION_ATTACK) {
        i_this->mBodyCyl.SetC(i_this->m2F8);
        i_this->mBodyCyl.SetH(160.0f);
        i_this->mBodyCyl.SetR(15.0f);
        dComIfG_Ccsp()->Set(&i_this->mBodyCyl);
    }
    if ((i_this->m2C0 == 0) || (i_this->m2C0 == 1)) {
        local_38 = actor->current.pos;
        local_38.y += 10.0f;
        i_this->mFootCoSph.SetC(local_38);
        i_this->mFootCoSph.SetR(45.0f);
        dComIfG_Ccsp()->Set(&i_this->mFootCoSph);
    }
    draw_SUB(i_this);
    return TRUE;
}

/* 000048B0-000048B8       .text daBO_IsDelete__FP8bo_class */
static BOOL daBO_IsDelete(bo_class*) {
    return TRUE;
}

/* 000048B8-00004998       .text daBO_Delete__FP8bo_class */
static BOOL daBO_Delete(bo_class* i_this) {
    i_this->mSmokeCb.remove();
    if (i_this->m3D0 != NULL) {
        i_this->m3D0->becomeInvalidEmitter();
        i_this->m3D0 = NULL;
    }
    if (i_this->m3D4 != NULL) {
        i_this->m3D4->deleteAllParticle();
        i_this->m3D4->becomeInvalidEmitter();
        i_this->m3D4 = NULL;
    }
    if (i_this->m3D8 != NULL) {
        i_this->m3D8->deleteAllParticle();
        i_this->m3D8->becomeInvalidEmitter();
        i_this->m3D8 = NULL;
    }
    enemy_fire_remove(&i_this->mEnemyFire);
    dComIfG_resDeleteDemo(&i_this->mPhase, "BO");
    return TRUE;
}

/* 00004998-00004D08       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    bo_class* i_this = (bo_class*)a_this;
    J3DModel* model;
    J3DAnmTevRegKey* pBrk;
    int fileIndex;

    fileIndex = dRes_INDEX_BO_BCK_DERU_U1_e;
    if (i_this->m2C0 == 2) {
        fileIndex = dRes_INDEX_BO_BCK_DAMAGE1_e;
    }
    i_this->mpHeadMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BO", dRes_INDEX_BO_BDL_BO_UE1_e),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("BO", fileIndex),
        J3DFrameCtrl::EMode_RESET,
        0.0f,
        0,
        -1,
        1,
        NULL,
        0x00080000,
        0x37441422
    );
    if ((i_this->mpHeadMorf == NULL) || (i_this->mpHeadMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpHeadMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpHeadMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpHeadMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_UP);
    }
    model = i_this->mpHeadMorf->getModel();
    if (i_this->m2C0 == 2) {
        i_this->mpBrkAnm = new mDoExt_brkAnm();
        if (i_this->mpBrkAnm == NULL) {
            return FALSE;
        }
        pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BO", dRes_INDEX_BO_BRK_TO_BOKO1_e);
        if (!i_this->mpBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE)) {
            return FALSE;
        }
    } else {
        i_this->mpBudMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("BO", dRes_INDEX_BO_BDL_BO_SITA1_e),
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("BO", dRes_INDEX_BO_BCK_DERU_S1_e),
            J3DFrameCtrl::EMode_RESET,
            0.0f,
            0,
            -1,
            1,
            NULL,
            0x00080000,
            0x33221202
        );
        if ((i_this->mpBudMorf == NULL) || (i_this->mpBudMorf->getModel() == NULL)) {
            return FALSE;
        }
        i_this->mpBudMorf->getModel()->setUserArea((u32)i_this);
        for (u16 i = 0; i < i_this->mpBudMorf->getModel()->getModelData()->getJointNum(); i++) {
            i_this->mpBudMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_DW);
        }
    }
    if (i_this->m2C0 == 0) {
        if (!i_this->mInvisibleModel.create(i_this->mpHeadMorf->getModel())) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00004D50-000050DC       .text daBO_Create__FP10fopAc_ac_c */
static cPhs_State daBO_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph head_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK2000,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK6,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcSph foot_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcCyl body_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 0.0f,
            /* Height */ 0.0f,
        }},
    };

    bo_class* i_this = (bo_class*)a_this;
    cPhs_State res;

    fopAcM_ct_Retail(a_this, bo_class);
    res = dComIfG_resLoad(&i_this->mPhase, "BO");
    if (res == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(a_this, bo_class);
        i_this->m2C0 = fopAcM_GetParam(a_this);
        i_this->m2C1 = (fopAcM_GetParam(a_this)) >> 8;
        if (i_this->m2C0 == 0xFF) {
            i_this->m2C0 = 0;
        }
        if (i_this->m2C1 == 0xFF) {
            i_this->m2C1 = 0;
        }
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("bbaba", 0);
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x3100)) {
            return cPhs_ERROR_e;
        }
        if ((i_this->m2C0 == 0) || (i_this->m2C0 == 2)) {
            fopAcM_SetMtx(a_this, i_this->mpHeadMorf->getModel()->getBaseTRMtx());
        } else {
            fopAcM_SetMtx(a_this, i_this->mpBudMorf->getModel()->getBaseTRMtx());
        }
        fopAcM_setCullSizeBox(a_this, -150.0f, 0.0f, -150.0f, 150.0f, 330.0f, 150.0f);
        a_this->attention_info.flags = 0;
        a_this->max_health = 1;
        a_this->health = 1;
        i_this->m398 = 1.0f;
        i_this->mStts.Init(0xFF, 1, a_this);
        i_this->mAction = ACTION_ATTACK;
        i_this->mMode = MODE_ATTACK_0;
        if (i_this->m2C0 == 0) {
            i_this->mHeadCoSph.Set(head_co_sph_src);
            i_this->mHeadCoSph.SetStts(&i_this->mStts);
            a_this->stealItemLeft = 3;
            i_this->mBodyCyl.Set(body_cyl_src);
            i_this->mBodyCyl.SetStts(&i_this->mStts);
            i_this->mHeadCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mHeadCoSph.ClrAtSet();
            i_this->mHeadCoSph.SetAtSpl(dCcG_At_Spl_UNK0);
            i_this->mEnemyIce.mpActor = a_this;
            i_this->mEnemyIce.mWallRadius = 15.0f;
            i_this->mEnemyIce.mCylHeight = 160.0f;
            i_this->mEnemyFire.mpMcaMorf = i_this->mpHeadMorf;
            i_this->mEnemyFire.mpActor = a_this;

            static u8 fire_j[ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs)] = {
                BO_UE1_JNT_BOKOBABA_SKLROOT_e,
                BO_UE1_JNT_J_BOKOBABA_NECK2_e,
                BO_UE1_JNT_J_BOKOBABA_NECK4_e,
                BO_UE1_JNT_J_BOKOBABA_HA_e,
                BO_UE1_JNT_J_BOKOBABA_ATAMA_e,
                BO_UE1_JNT_J_BOKOBABA_AGO_e,
                BO_UE1_JNT_J_BOKOBABA_SITA1_e,
                BO_UE1_JNT_J_BOKOBABA_SITA2_e,
                BO_UE1_JNT_J_BOKOBABA_SITA3_e,
                BO_UE1_JNT_J_BOKOBABA_TOGE2_e
            };
            static f32 fire_sc[ARRAY_SIZE(i_this->mEnemyFire.mParticleScale)] = {
                1.0f, // BO_UE1_JNT_BOKOBABA_SKLROOT_e
                1.0f, // BO_UE1_JNT_J_BOKOBABA_NECK2_e
                1.0f, // BO_UE1_JNT_J_BOKOBABA_NECK4_e
                1.0f, // BO_UE1_JNT_J_BOKOBABA_HA_e
                2.0f, // BO_UE1_JNT_J_BOKOBABA_ATAMA_e
                2.0f, // BO_UE1_JNT_J_BOKOBABA_AGO_e
                2.0f, // BO_UE1_JNT_J_BOKOBABA_SITA1_e
                2.0f, // BO_UE1_JNT_J_BOKOBABA_SITA2_e
                2.0f, // BO_UE1_JNT_J_BOKOBABA_SITA3_e
                2.0f  // BO_UE1_JNT_J_BOKOBABA_TOGE2_e
            };

            for (int i = 0; i < ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
                i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
                i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
            }
        }
        if ((i_this->m2C0 == 0) || (i_this->m2C0 == 1)) {
            i_this->mFootCoSph.Set(foot_co_sph_src);
            i_this->mFootCoSph.SetStts(&i_this->mStts);
            if (i_this->m2C0 == 1) {
                i_this->mTimers[0] = REG8_F(14) + 15.0f;
                anm_init(i_this, dRes_INDEX_BO_BCK_DERU_S1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1, ACTOR_ANM_TYPE_BUD);
                i_this->mAction = ACTION_HEAD_DEATH_SPECIAL;
                i_this->mMode = MODE_HEAD_DEATH_SPECIAL_51;
                i_this->m2D0 = 3;
                i_this->mpBudMorf->play(NULL, 0, 0);
                draw_SUB(i_this);
            }
        }
        i_this->m34E = fopAcM_searchPlayerAngleY(a_this);
        i_this->m348 = i_this->m34E;
        i_this->m304 = a_this->current.pos;
        if (i_this->m2C0 == 2) {
            i_this->m394 = 100.0f;
            a_this->attention_info.flags = 0;
            i_this->mAction = ACTION_HEAD_DEATH_NORMAL;
            i_this->mMode = MODE_HEAD_DEATH_NORMAL_30;
            i_this->mpHeadMorf->play(NULL, 0, 0);
            draw_SUB(i_this);
        }
#if VERSION == VERSION_DEMO
        if (i_this->m2C0 == 0) {
            fopEn_enemy_c* e_this = &i_this->actor;
            e_this->initBt(162.5f, 200.0f);
            e_this->setBtAttackData(0.0f, 10.0f, 800.0f, 3);
            e_this->setBtNowFrame(1000.0f);
        }
#endif
        daBO_Execute(i_this);
    }
    return res;
}

static actor_method_class l_daBO_Method = {
    (process_method_func)daBO_Create,
    (process_method_func)daBO_Delete,
    (process_method_func)daBO_Execute,
    (process_method_func)daBO_IsDelete,
    (process_method_func)daBO_Draw,
};

actor_process_profile_definition g_profile_BO = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_BO_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bo_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_BO_e,
    /* Actor SubMtd */ &l_daBO_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
