/**
 * d_a_bl.cpp
 * Enemy - Bubble
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bl.h"
#include "res/Object/Bl.h"
#include "d/actor/d_a_player.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"

enum Action {
    ACTION_DOUSA = 0,
    ACTION_KOUGEKI = 1,
    ACTION_SAGARIMASU = 2,
    ACTION_KAZE_MOVE = 3,
    ACTION_ITAIYO_NE_SAN = 4,
    ACTION_HOOK_ATARI = 5,
    ACTION_COME_WAIT = 6,
    ACTION_NORMAL_SKULL = 10
};

enum Mode {
    MODE_DOUSA_0 = 0,
    MODE_DOUSA_1 = 1,
    MODE_DOUSA_2 = 2,
    MODE_DOUSA_3 = 3,
    MODE_DOUSA_4 = 4,
    MODE_DOUSA_5 = 5,
    MODE_DOUSA_6 = 6,
    MODE_DOUSA_7 = 7,
    MODE_KOUGEKI_10 = 10,
    MODE_KOUGEKI_11 = 11,
    MODE_KOUGEKI_12 = 12,
    MODE_KOUGEKI_13 = 13,
    MODE_KOUGEKI_14 = 14,
    MODE_KOUGEKI_15 = 15,
    MODE_SAGARIMASU_20 = 20,
    MODE_SAGARIMASU_21 = 21,
    MODE_KAZE_MOVE_30 = 30,
    MODE_KAZE_MOVE_31 = 31,
    MODE_KAZE_MOVE_32 = 32,
    MODE_KAZE_MOVE_33 = 33,
    MODE_KAZE_MOVE_34 = 34,
    MODE_KAZE_MOVE_35 = 35,
    MODE_KAZE_MOVE_36 = 36,
    MODE_KAZE_MOVE_37 = 37,
    MODE_KAZE_MOVE_38 = 38,
    MODE_KAZE_MOVE_39 = 39,
    MODE_ITAIYO_NE_SAN_40 = 40,
    MODE_ITAIYO_NE_SAN_41 = 41,
    MODE_ITAIYO_NE_SAN_42 = 42,
    MODE_ITAIYO_NE_SAN_43 = 43,
    MODE_HOOK_ATARI_60 = 60,
    MODE_HOOK_ATARI_61 = 61,
    MODE_COME_WAIT_70 = 70,
    MODE_NORMAL_SKULL_100 = 100,
    MODE_NORMAL_SKULL_101 = 101,
    MODE_NORMAL_SKULL_102 = 102,
    MODE_NORMAL_SKULL_103 = 103,
    MODE_NORMAL_SKULL_104 = 104,
    MODE_NORMAL_SKULL_105 = 105
};

/* 00000078-00000178       .text draw_SUB__FP8bl_class */
static void draw_SUB(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    MtxTrans(actor->current.pos.x, actor->current.pos.y + i_this->m314, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
    cMtx_ZrotM(*calc_mtx, actor->shape_angle.z);
    MtxTrans(0.0f, -i_this->m314, 0.0f, true);
    model->setBaseTRMtx(*calc_mtx);
    i_this->mpMorf->calc();
    enemy_fire(&i_this->mEnemyFire);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
}

/* 00000178-000002F8       .text daBL_Draw__FP8bl_class */
static BOOL daBL_Draw(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    J3DModel* model = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(model, &actor->tevStr);
    if ((i_this->m2D5 != 0xFF) && (!dComIfGs_isSwitch(i_this->m2D5, dComIfGp_roomControl_getStayNo()))) {
        return TRUE;
    }
    dSnap_RegistFig(DSNAP_TYPE_BL, actor, 1.0f, 1.0f, 1.0f);
    if (i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, &i_this->mInvisibleModel);
        return TRUE;
    }
    if (i_this->m2D3 == 0) {
        i_this->m2BC->entry(model->getModelData());
    } else {
        i_this->m2C0->entry(model->getModelData());
    }
    i_this->mpMorf->entryDL();
    if (actor->health > 0) {
        dComIfGd_setSimpleShadow2(&actor->current.pos, i_this->mAcch.GetGroundH(), 30.0f, i_this->mAcch.m_gnd, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }
    if (i_this->m2D3 == 0) {
        i_this->m2BC->remove(model->getModelData());
    } else {
        i_this->m2C0->remove(model->getModelData());
    }
    return TRUE;
}

/* 000002F8-000003F8       .text smoke_set__FP8bl_class */
static void smoke_set(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->m6C8.getEmitter() == NULL) {
        dComIfGp_particle_setToon(
            dPa_name::ID_AK_JT_ELEMENTSMOKE01,
            &i_this->m6BC_cXyz,
            &actor->shape_angle,
            NULL,
            0xB9,
            &i_this->m6C8,
            fopAcM_GetRoomNo(actor)
        );
    }
    if (i_this->m6C8.getEmitter() != NULL) {
        GXColor eff_col = {0xA0, 0xA0, 0x80, 0xB4};
        JGeometry::TVec3<f32> scale;
        scale.set(1.6f, 1.6f, 1.6f);
        i_this->m6C8.getEmitter()->setGlobalParticleScale(scale);
        i_this->m6C8.getEmitter()->setRate(10.0f);
        i_this->m6C8.getEmitter()->setMaxFrame(1);
        i_this->m6C8.getEmitter()->setAwayFromCenterSpeed(8.0f);
        i_this->m6C8.getEmitter()->becomeImmortalEmitter();
        i_this->m6C8.setColor(eff_col);
    }
}

/* 000003F8-000004AC       .text fire_move_set__FP8bl_class */
static void fire_move_set(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    u16 particleId;
    if (i_this->m2D0 == 0) {
        particleId = dPa_name::ID_AK_SN_BUBBLERED00;
    } else {
        particleId = dPa_name::ID_AK_SN_BUBBLEBLUE00;
    }
    if (i_this->m6FC.getEmitter() == NULL) {
        dComIfGp_particle_set(particleId, &actor->current.pos, NULL, NULL, 0xFF, &i_this->m6FC, fopAcM_GetRoomNo(actor));
        if (i_this->m2D0 == 1) {
            i_this->mBodyCoSph.SetTgSe(5);
            i_this->mBodyCoSph.SetTgHitMark(dCcg_TgHitMark_Purple_e);
            i_this->mBodyCoSph.OnTgShield();
        }
    }
}

/* 000004AC-00000578       .text fire_emitter_clr__FP8bl_class */
static void fire_emitter_clr(bl_class* i_this) {
    if ((i_this->m6FC.getEmitter() != NULL) && (i_this->m2EC[2] == 0)) {
        if (i_this->m2D0 == 0) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            JGeometry::TVec3<s16> rot;
            rot.x = 0;
            rot.y = player->shape_angle.y + 0x8000;
            rot.z = 0;
            i_this->m6FC.getEmitter()->setGlobalRotation(rot);
            i_this->m6FC.getEmitter()->setRate(3.0f);
            i_this->m6FC.getEmitter()->setLifeTime(10);
            i_this->m6FC.getEmitter()->setDirectionalSpeed(50.0f);
            i_this->m2EC[2] = 21;
        } else {
            i_this->m2EC[2] = 1;
        }
    }
    i_this->m6E8.remove();
}

/* 00000578-000006E0       .text fire_kaiten_keisan__FP8bl_class */
static void fire_kaiten_keisan(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->m6FC.getEmitter() != NULL) {
        if (i_this->m2D0 == 0) {
            i_this->m6FC.getEmitter()->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(BL_JNT_HEAD_e));
            fopAcM_seStart(actor, JA_SE_CM_BL_FLAME_BURNING, 0);
        } else {
            fopAcM_seStart(actor, JA_SE_CM_BL_CURSE_BURNING, 0);
            camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
            MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(BL_JNT_HEAD_e), *calc_mtx);
            cMtx_YrotM(*calc_mtx, fopCamM_GetAngleY(camera) - actor->shape_angle.y);
            i_this->m6FC.getEmitter()->setGlobalRTMatrix(*calc_mtx);
        }
    }
}

/* 000006E0-00000820       .text shock_damage_check__FP8bl_class */
static BOOL shock_damage_check(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz swordTopPos;

    if (((i_this->m2D0 & 0x80) == 0) && (i_this->m2D3 != 0)) {
        return FALSE;
    }
    if (player->checkHammerQuake()) {
#if VERSION == VERSION_DEMO
        fire_emitter_clr(i_this);
#elif VERSION == VERSION_JPN
        i_this->m2EC[2] = 0;
        fire_emitter_clr(i_this);
#endif
        swordTopPos = player->getSwordTopPos();
        swordTopPos.x -= actor->current.pos.x;
        swordTopPos.z -= actor->current.pos.z;
        if (std::sqrtf(SQUARE(swordTopPos.x) + SQUARE(swordTopPos.z)) < 1000.0f) {
#if VERSION >= VERSION_USA
            i_this->m2EC[2] = 0;
            fire_emitter_clr(i_this);
#endif
            return TRUE;
        }
    }
    return FALSE;
}

/* 00000820-0000094C       .text anm_init__FP8bl_classifUcfi */
static void anm_init(bl_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->mCurrBckIdx = bckFileIdx;
    if (soundFileIdx >= 0) {
        i_this->mpMorf
            ->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BL", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("BL", soundFileIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BL", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 0000094C-00000C08       .text skull_atari_check__FP8bl_class */
static BOOL skull_atari_check(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    fopAc_ac_c* player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)player_actor;
    i_this->mStts.Move();
    if (actor->health == 0) {
        return TRUE;
    }
    if (shock_damage_check(i_this)) {
        i_this->mAction = ACTION_KAZE_MOVE;
        i_this->mMode = MODE_KAZE_MOVE_34;
        return TRUE;
    }
    if (!i_this->mBodyCoSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mBodyCoSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->m2EC[4] != 0) {
        return FALSE;
    }
    actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
    bool r0 = false;
    i_this->m2EC[4] = 8;
    i_this->mHitType = 0;
    switch (hitObj->GetAtType()) {
        case AT_TYPE_SWORD:
            i_this->mHitType = 6;
            break;
        case AT_TYPE_WIND:
            r0 = true;
            i_this->mHitType = 1;
            i_this->mAction = ACTION_KAZE_MOVE;
            i_this->mMode = MODE_KAZE_MOVE_36;
            break;
        case AT_TYPE_SKULL_HAMMER:
            i_this->mHitType = 4;
            if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                actor->current.angle.y = player->shape_angle.y - 0x4000;
                i_this->mHitType = 5;
                actor->speed.y = 30.0f;
                actor->speedF = 20.0f;
            }
            break;
        case AT_TYPE_BOOMERANG:
        case AT_TYPE_BOKO_STICK:
            i_this->mHitType = 3;
            break;
        case AT_TYPE_BOMB:
            actor->speed.y = 30.0f;
        // Fall-through
        case AT_TYPE_FIRE:
            i_this->mEnemyFire.mFireDuration = 1000;
            break;
        case AT_TYPE_HOOKSHOT:
            r0 = true;
            i_this->mHitType = 7;
            i_this->mAction = ACTION_HOOK_ATARI;
            i_this->mMode = MODE_HOOK_ATARI_60;
            break;
        case AT_TYPE_FIRE_ARROW:
        case AT_TYPE_ICE_ARROW:
        case AT_TYPE_LIGHT_ARROW:
            break;
    }
    // Required to match
    cXyz sp8 = *i_this->mBodyCoSph.GetTgHitPosP();
    csXyz tmp;
    if (!r0) {
        fopAcM_seStart(actor, JA_SE_OBJ_BREAK_STONE, 0);
        actor->health = 0;
        actor->attention_info.flags = 0;
        i_this->mAction = ACTION_NORMAL_SKULL;
        i_this->mMode = MODE_NORMAL_SKULL_103;
    }
    return TRUE;
}

/* 00000C44-00001768       .text blue_body_atari_check__FP8bl_class */
static BOOL blue_body_atari_check(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* hitObj;
    cXyz local_4c;
    cXyz local_58;
    CcAtInfo atInfo;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if (shock_damage_check(i_this)) {
        i_this->mAction = ACTION_KAZE_MOVE;
        i_this->mMode = MODE_KAZE_MOVE_34;
        return TRUE;
    }
    if (!i_this->mBodyCoSph.ChkTgHit()) {
        return FALSE;
    }
    hitObj = i_this->mBodyCoSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->m2EC[4] != 0) {
        return FALSE;
    }
    actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
    bool r29 = false;
    i_this->m2EC[4] = 8;
    i_this->mHitType = 0;
    switch (hitObj->GetAtType()) {
        case AT_TYPE_GRAPPLING_HOOK:
            if (i_this->m2D3 != 0) {
                actor->stealItemLeft = i_this->m2EA;
                if (actor->stealItemLeft > 0) {
                    s8 r27 = actor->health;
                    actor->health = 10;
                    atInfo.mpObj = i_this->mBodyCoSph.GetTgHitObj();
                    atInfo.pParticlePos = NULL;
                    cc_at_check(actor, &atInfo);
                    actor->health = r27;
                }
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
                if (i_this->m2EA > 0) {
                    i_this->m2EA--;
                }
                dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
                r29 = true;
            } else {
                actor->stealItemLeft = 0;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x33);
            }
            break;
        case AT_TYPE_SWORD:
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x42);
            }
            if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EA || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EB ||
                player->getCutType() == daPy_py_c::CUT_TYPE_CUT_TURN || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_ROLL ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SWORD || player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_STICK ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_MACHETE || player->getCutType() == daPy_py_c::CUT_TYPE_BT_JUMPCUT ||
                player->getCutType() == daPy_py_c::CUT_TYPE_BT_ROLLCUT || player->getCutType() == daPy_py_c::CUT_TYPE_BT_VERTICALJUMPCUT ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_CLUB || player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_DN_SWORD ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SPEAR || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXA ||
                player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXB || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXMJ ||
                player->getCutType() == daPy_py_c::CUT_TYPE_CUT_KESA)
            {
                i_this->mHitType = 6;
            }
            break;
        case AT_TYPE_BOMB:
            if (i_this->m2D3 == 0) {
                i_this->mHitType = 2;
                break;
            }
        case AT_TYPE_WIND:
            r29 = true;
            i_this->mHitType = 1;
            i_this->mAction = ACTION_KAZE_MOVE;
            i_this->mMode = MODE_KAZE_MOVE_36;
            if ((!i_this->mAcch.ChkGroundHit()) && (actor->gravity > -2.0f)) {
                i_this->mMode = MODE_KAZE_MOVE_30;
            }
            break;
        case AT_TYPE_SKULL_HAMMER:
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x42);
            }
            i_this->mHitType = 4;
            if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                actor->current.angle.y = player->shape_angle.y - 0x4000;
                i_this->mHitType = 5;
            }
            if (i_this->m2D3 == 0) {
                actor->health = 0;
            }
            break;
        case AT_TYPE_BOOMERANG:
        case AT_TYPE_BOKO_STICK:
            r29 = true;
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x42);
            }
            i_this->mHitType = 3;
            break;
        case AT_TYPE_FIRE:
        case AT_TYPE_FIRE_ARROW:
            if (i_this->m2D3 == 0) {
                i_this->mEnemyFire.mFireDuration = 100;
                fopAcM_seStart(actor, JA_SE_CM_BL_WIND_HIT, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_BL_DAMAGE, 0);
                i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mBodyCoSph.ClrAtSet();
                actor->attention_info.flags = 0;
                i_this->m2EC[2] = 0;
                fire_emitter_clr(i_this);
            }
            break;
        case AT_TYPE_LIGHT_ARROW:
            i_this->mEnemyIce.mLightShrinkTimer = 1;
            i_this->mEnemyIce.mParticleScale = 1.0f;
            i_this->mEnemyIce.mYOffset = 40.0f;
            fopAcM_seStart(actor, JA_SE_CM_BL_WIND_HIT, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_BL_DAMAGE, 0);
            actor->current.angle.x = 0;
            actor->current.angle.z = 0;
            i_this->m2D3 = 0;
            actor->shape_angle.x = 0;
            actor->shape_angle.z = 0;
            actor->gravity = 0.0f;
            actor->speedF = 0.0f;
            i_this->m2EC[0] = 0;
            actor->speed.setall(0.0f);
            i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyCoSph.ClrAtSet();
            actor->attention_info.flags = 0;
            i_this->m2EC[2] = 0;
            fire_emitter_clr(i_this);
            break;
        case AT_TYPE_ICE_ARROW:
            if (i_this->m2D3 == 0) {
                r29 = true;
                i_this->m2D3 = 0;
                actor->current.angle.x = 0;
                actor->current.angle.z = 0;
                actor->shape_angle.x = 0;
                actor->shape_angle.z = 0;
                actor->gravity = 0.0f;
                actor->speedF = 0.0f;
                i_this->m2EC[0] = 0;
                actor->speed.setall(0.0f);
                i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mBodyCoSph.ClrAtSet();
                i_this->mEnemyIce.mFreezeDuration = 200;
                enemy_fire_remove(&i_this->mEnemyFire);
                actor->attention_info.flags = 0;
            } else {
                r29 = true;
                i_this->mHitType = 1;
                i_this->mAction = ACTION_KAZE_MOVE;
                i_this->mMode = MODE_KAZE_MOVE_30;
            }
            break;
        case AT_TYPE_HOOKSHOT:
            r29 = true;
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
            }
            i_this->mHitType = 7;
            i_this->mAction = ACTION_HOOK_ATARI;
            i_this->mMode = MODE_HOOK_ATARI_60;
            break;
        default:
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
            }
    }
    local_4c = *i_this->mBodyCoSph.GetTgHitPosP();
    if ((i_this->m2D3 != 0) && (i_this->mHitType != 7) && (i_this->mHitType != 1)) {
        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &local_4c);
        i_this->mAction = ACTION_SAGARIMASU;
        i_this->mMode = MODE_SAGARIMASU_20;
        return TRUE;
    }
    if (!r29) {
        atInfo.mpObj = i_this->mBodyCoSph.GetTgHitObj();
        atInfo.pParticlePos = NULL;
        cc_at_check(actor, &atInfo);
        if ((i_this->mHitType == 6) || (i_this->mHitType == 5) || (i_this->mHitType == 4) || (actor->health <= 0)) {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_4c);
            local_58.setall(2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_4c, &player->shape_angle, &local_58);
        } else {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &local_4c, &player->shape_angle);
        }
        i_this->mAction = ACTION_ITAIYO_NE_SAN;
        i_this->mMode = MODE_ITAIYO_NE_SAN_40;
    }
    return TRUE;
}

/* 00001768-000022BC       .text red_body_atari_check__FP8bl_class */
static BOOL red_body_atari_check(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* hitObj;
    cXyz local_4c;
    cXyz local_58;
    CcAtInfo atInfo;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if (shock_damage_check(i_this)) {
        i_this->mAction = ACTION_KAZE_MOVE;
        i_this->mMode = MODE_KAZE_MOVE_34;
        return TRUE;
    }
    if (!i_this->mBodyCoSph.ChkTgHit()) {
        return FALSE;
    }
    hitObj = i_this->mBodyCoSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->m2EC[4] != 0) {
        return FALSE;
    }
    actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
    bool r29 = false;
    local_4c = *i_this->mBodyCoSph.GetTgHitPosP();
    i_this->m2EC[4] = 8;
    i_this->mHitType = 0;
    switch (hitObj->GetAtType()) {
        case AT_TYPE_GRAPPLING_HOOK:
            if (i_this->m2D3 != 0) {
                actor->stealItemLeft = i_this->m2EA;
                if (actor->stealItemLeft > 0) {
                    s8 r27 = actor->health;
                    actor->health = 10;
                    atInfo.mpObj = i_this->mBodyCoSph.GetTgHitObj();
                    atInfo.pParticlePos = NULL;
                    cc_at_check(actor, &atInfo);
                    actor->health = r27;
                }
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
                if (i_this->m2EA > 0) {
                    i_this->m2EA--;
                }
                dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
                r29 = true;
            } else {
                actor->stealItemLeft = 0;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x33);
            }
            break;
        case AT_TYPE_SWORD:
            i_this->mHitType = 8;
            fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x33);
            if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EA || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EB ||
                player->getCutType() == daPy_py_c::CUT_TYPE_CUT_TURN || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_ROLL ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SWORD || player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_STICK ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_MACHETE || player->getCutType() == daPy_py_c::CUT_TYPE_BT_JUMPCUT ||
                player->getCutType() == daPy_py_c::CUT_TYPE_BT_ROLLCUT || player->getCutType() == daPy_py_c::CUT_TYPE_BT_VERTICALJUMPCUT ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_CLUB || player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_DN_SWORD ||
                player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SPEAR || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXA ||
                player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXB || player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXMJ ||
                player->getCutType() == daPy_py_c::CUT_TYPE_CUT_KESA)
            {
                i_this->mHitType = 6;
            }
            break;
        case AT_TYPE_BOMB:
            if (i_this->m2D3 == 0) {
                i_this->mHitType = 2;
                break;
            }
        case AT_TYPE_WIND:
            r29 = true;
            i_this->mHitType = 1;
            i_this->mAction = ACTION_KAZE_MOVE;
            i_this->mMode = MODE_KAZE_MOVE_36;
            if ((!i_this->mAcch.ChkGroundHit()) && (actor->gravity > -2.0f)) {
                i_this->mMode = MODE_KAZE_MOVE_30;
            }
            break;
        case AT_TYPE_SKULL_HAMMER:
            fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x33);

            i_this->mHitType = 4;
            if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                actor->current.angle.y = player->shape_angle.y - 0x4000;
                i_this->mHitType = 5;
            }
            actor->health = 0;
            break;
        case AT_TYPE_BOOMERANG:
        case AT_TYPE_BOKO_STICK:
            r29 = true;
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x42);
            }
            i_this->mHitType = 3;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &local_4c);
            break;
        case AT_TYPE_FIRE:
        case AT_TYPE_NORMAL_ARROW:
        case AT_TYPE_FIRE_ARROW:
            if ((i_this->m2D3 == 0) || (!hitObj->ChkAtType(AT_TYPE_FIRE))) {
                if ((i_this->m2D3 == 0) && (!hitObj->ChkAtType(AT_TYPE_NORMAL_ARROW))) {
                    i_this->mEnemyFire.mFireDuration = 100;
                }
                fopAcM_seStart(actor, JA_SE_CM_BL_WIND_HIT, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_BL_DAMAGE, 0);
                i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mBodyCoSph.ClrAtSet();
                actor->attention_info.flags = 0;
                i_this->m2EC[2] = 0;
                fire_emitter_clr(i_this);
            }
            break;
        case AT_TYPE_LIGHT_ARROW:
            i_this->mEnemyIce.mLightShrinkTimer = 1;
            i_this->mEnemyIce.mParticleScale = 1.0f;
            i_this->mEnemyIce.mYOffset = 40.0f;
            fopAcM_seStart(actor, JA_SE_CM_BL_WIND_HIT, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_BL_DAMAGE, 0);
            actor->current.angle.x = 0;
            actor->current.angle.z = 0;
            i_this->m2D3 = 0;
            actor->shape_angle.x = 0;
            actor->shape_angle.z = 0;
            actor->gravity = 0.0f;
            actor->speedF = 0.0f;
            i_this->m2EC[0] = 0;
            actor->speed.setall(0.0f);
            i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyCoSph.ClrAtSet();
            actor->attention_info.flags = 0;
            i_this->m2EC[2] = 0;
            fire_emitter_clr(i_this);
            break;
        case AT_TYPE_ICE_ARROW:
            r29 = true;
            i_this->m2D3 = 0;
            actor->current.angle.x = 0;
            actor->current.angle.z = 0;
            actor->shape_angle.x = 0;
            actor->shape_angle.z = 0;
            actor->gravity = 0.0f;
            actor->speedF = 0.0f;
            i_this->m2EC[0] = 0;
            actor->speed.setall(0.0f);
#if VERSION > VERSION_DEMO
            i_this->m2EC[2] = 0;
#endif
            fire_emitter_clr(i_this);
            i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyCoSph.ClrAtSet();
            i_this->mEnemyIce.mFreezeDuration = 200;
            enemy_fire_remove(&i_this->mEnemyFire);
            actor->attention_info.flags = 0;
            break;
        case AT_TYPE_HOOKSHOT:
            r29 = true;
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
            }
            i_this->mHitType = 7;
            i_this->mAction = ACTION_HOOK_ATARI;
            i_this->mMode = MODE_HOOK_ATARI_60;
            break;
        default:
            r29 = true;
            if (i_this->m2D3 == 0) {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x33);
            } else {
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
            }
            dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &local_4c);
            break;
    }
    if (!r29) {
        atInfo.mpObj = i_this->mBodyCoSph.GetTgHitObj();
        atInfo.pParticlePos = NULL;
        cc_at_check(actor, &atInfo);
        if ((i_this->mHitType == 6) || (i_this->mHitType == 5) || (i_this->mHitType == 4) || (actor->health <= 0)) {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_4c);
            local_58.setall(2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_4c, &player->shape_angle, &local_58);
        } else {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &local_4c, &player->shape_angle);
        }
        if (i_this->m2D3 != 0) {
            anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            actor->speedF = REG8_F(10) + 60.0f;
            if (actor->health <= 0) {
                actor->speedF = REG8_F(11) + 60.0f;
                if (i_this->mHitType == 5) {
                    actor->current.angle.y = player->shape_angle.y - 0x4000;
                }
            }
            fopAcM_monsSeStart(actor, JA_SE_CV_BL_DAMAGE, 0);
            i_this->mAction = ACTION_SAGARIMASU;
            i_this->mMode = MODE_SAGARIMASU_21;
        } else {
            i_this->mAction = ACTION_ITAIYO_NE_SAN;
            i_this->mMode = MODE_ITAIYO_NE_SAN_40;
        }
    }
    return TRUE;
}

/* 000022BC-00002354       .text bound_sound_set__FP8bl_class */
static void bound_sound_set(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    u32 uVar1 = actor->speed.y * 3.3f;
    if (uVar1 > 100) {
        uVar1 = 100;
    }
    fopAcM_seStart(actor, JA_SE_CM_BL_BOUND, uVar1);
}

/* 00002354-00002458       .text fuwafuwa_keisan__FP8bl_class */
static void fuwafuwa_keisan(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    f32 maxSpeed = 3.0f;
    if (i_this->mAction == ACTION_KOUGEKI) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        i_this->m304 += 1000;
        i_this->m318 = player->current.pos.y + 80.0f;
        i_this->m318 += cM_ssin(i_this->m304) * 10.0f;
        maxSpeed = 6.0f;
    } else {
        i_this->m304 += 500;
        i_this->m318 = i_this->m320 + 100.0f;
        i_this->m318 += cM_ssin(i_this->m304) * 40.0f;
    }
    cLib_addCalc2(&actor->current.pos.y, i_this->m318, 1.0f, maxSpeed);
}

/* 00002458-000024E4       .text BG_check__FP8bl_class */
static void BG_check(bl_class* i_this) {
    if (i_this->mMode != MODE_DOUSA_2) {
        i_this->mAcchCir.SetWall(40.0f, 40.0f);
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        i_this->mAcch.OnLineCheck();
        if ((i_this->m2D1 == 0) && (i_this->mAcch.GetGroundH() == -G_CM3D_F_INF)) {
            i_this->m320 = i_this->mAcch.GetGroundH();
        }
    }
}

/* 000024E4-00002804       .text Line_check__FP8bl_class4cXyz */
static BOOL Line_check(bl_class* i_this, cXyz destPos) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    cXyz centerPos = actor->current.pos;
    centerPos.y += 100.0f;
    destPos.y += 100.0f;
    linChk.Set(&centerPos, &destPos, actor);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 00002C3C-00002CC4       .text roll_check__FP8bl_class */
static BOOL roll_check(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x1000);
    cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 1, 0x1000);
    i_this->m2F8[0] = 0;
    i_this->m2F8[1] = 0;
    if ((abs(actor->shape_angle.x) < 0x200) && (abs(actor->shape_angle.z) < 0x200)) {
        return TRUE;
    }
    return FALSE;
}

/* 00002CC4-00003054       .text way_check__FP8bl_classs */
static s16 way_check(bl_class* i_this, s16 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_dc;
    cXyz cStack_e8;
    dBgS_LinChk linChk;

    s16 iVar4 = param_2;
    s16 iVar3 = 0x2000;
    if (cM_rndFX(1.0f) < 0.5f) {
        iVar3 = -0x2000;
    }
    for (s32 i = 0; i < 8; i++, iVar4 += iVar3) {
        cMtx_YrotS(*calc_mtx, iVar4);
        local_dc.x = 0.0f;
        local_dc.y = 0.0f;
        local_dc.z = 300.0f;
        MtxPosition(&local_dc, &cStack_e8);
        cStack_e8 += actor->current.pos;
        linChk.Set(&actor->current.pos, &cStack_e8, actor);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            return iVar4;
        }
    }
    return param_2;
}

/* 00003054-000039F0       .text action_dousa__FP8bl_class */
static void action_dousa(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 z;
    f32 x;

    switch (i_this->mMode) {
        case MODE_DOUSA_0:
            {
                i_this->m304 = 0;
                f32 f30 = 1000.0f;
                if (fopAcM_searchPlayerDistance(actor) > f30) {
                    break;
                }
                fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                anm_init(i_this, dRes_INDEX_BL_BCK_START01_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mMode++;
                break;
            }
        case MODE_DOUSA_1:
            i_this->m31C = 1.5f;
            if (i_this->m6E8.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_BUBBLEBOOT00, &actor->current.pos, NULL, NULL, 0xFF, &i_this->m6E8);
                fopAcM_seStart(actor, JA_SE_CM_BL_ENTER, 0);
            }
            if (i_this->m6E8.getEmitter() != NULL) {
                if (i_this->m2D0 == 0) {
                    i_this->m6E8.getEmitter()->setGlobalEnvColor(0x55, 0x1A, 0xD);
                } else {
                    i_this->m6E8.getEmitter()->setGlobalEnvColor(0xD, 0x20, 0x41);
                }
            }
            if (!i_this->mpMorf->isStop()) {
                break;
            }
            actor->gravity = 0.0f;
            actor->speed.y = 0.0f;
            i_this->mMode++;
        case MODE_DOUSA_2:
            if (i_this->m6E8.getEmitter() != NULL) {
                i_this->m6E8.getEmitter()->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(BL_JNT_HEAD_e));
            }
            cLib_addCalc2(&actor->speed.y, 10.0f, 0.8f, 1.0f);
            if (actor->current.pos.y < i_this->m320 + 100.0f) {
                break;
            }
            fire_move_set(i_this);
            actor->speed.y = 0.0f;
            fopAcM_seStart(actor, JA_SE_CM_BL_AGO, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_BL_ENTER, 0);
            anm_init(i_this, dRes_INDEX_BL_BCK_START02_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mMode++;
            break;
        case MODE_DOUSA_3:
            if (i_this->mpMorf->checkFrame(10.0f)) {
                i_this->m6E8.remove();
            }
            if (i_this->mpMorf->isStop()) {
                i_this->mMode = MODE_DOUSA_5;
            }
            break;
        case MODE_DOUSA_4:
            fire_move_set(i_this);
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            i_this->m2EC[3] = 5;
            i_this->mMode = MODE_DOUSA_5;
        case MODE_DOUSA_5:
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            if (i_this->mCurrBckIdx != dRes_INDEX_BL_BCK_FLY_e) {
                anm_init(i_this, dRes_INDEX_BL_BCK_FLY_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m2D3 = 1;
                i_this->mStts.SetWeight(2);
                i_this->mBodyCoSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mBodyCoSph.OnAtHitBit();
            }
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            s16 r29;
            if ((i_this->m2E9 != 0xFF) && (i_this->mpPath != NULL)) {
                dPnt* pnt = i_this->mpPath->m_points;
                r29 = (s16)cM_atan2s(pnt[i_this->m2E8].m_position.x - actor->current.pos.x, pnt[i_this->m2E8].m_position.z - actor->current.pos.z);
                actor->speedF = i_this->m324;
            } else {
                i_this->m2EC[0] = cM_rndFX(50.0f) + 100.0f;
                r29 = cM_rndFX(32767.0f);
                if (!actor->speedF) {
                    actor->speedF = cM_rndF(2.0f) + 4.0f;
                }
            }
            i_this->m300 = way_check(i_this, r29);
            i_this->mMode++;
        // Fall-through
        case MODE_DOUSA_6:
            {
                if ((i_this->m2E9 != 0xFF) && (i_this->mpPath != NULL)) {
                    dPnt* pnt = i_this->mpPath->m_points;
                    x = pnt[i_this->m2E8].m_position.x - actor->current.pos.x;
                    z = pnt[i_this->m2E8].m_position.z - actor->current.pos.z;
                    int r29_2 = cM_atan2s(x, z);
                    if (std::sqrtf(SQUARE(x) + SQUARE(z)) < REG8_F(3) + 80.0f) {
                        i_this->m2E8++;
                        if (i_this->m2E8 >= i_this->mpPath->m_num) {
                            i_this->m2E8 = 0;
                        }
                    }
                    i_this->m2C4 = actor->current.pos;
                    if (i_this->m2EC[0] != 0) {
                        break;
                    }
                    i_this->m300 = way_check(i_this, r29_2);
                    if (i_this->m300 == r29_2) {
                        break;
                    }
                    i_this->m2EC[0] = cM_rndF(10.0f) + 10.0f;
                    break;
                }
                f32 f5 = 250.0f;
                x = actor->current.pos.x - i_this->m2C4.x;
                z = actor->current.pos.z - i_this->m2C4.z;
                if (std::sqrtf(SQUARE(x) + SQUARE(z)) < f5) {
                    if (i_this->m2EC[0] != 0) {
                        break;
                    }
                    i_this->mMode = MODE_DOUSA_5;
                    break;
                }
                i_this->mMode = MODE_DOUSA_7;
                // Fall-through
            }
        case MODE_DOUSA_7:
            x = i_this->m2C4.x - actor->current.pos.x;
            z = i_this->m2C4.z - actor->current.pos.z;
            i_this->m300 = cM_atan2s(x, z);
            f32 f5 = 10.0f;
            if ((i_this->m2E9 != 0xFF) && (i_this->mpPath != NULL)) {
                f5 = 80.0f;
            }
            if (std::sqrtf(SQUARE(x) + SQUARE(z)) < f5) {
                i_this->mMode = MODE_DOUSA_5;
            }
            break;
    }
    if ((i_this->mMode >= MODE_DOUSA_1) && (i_this->mMode <= MODE_DOUSA_3) && (i_this->m6E8.getEmitter() != NULL)) {
        i_this->m6E8.getEmitter()->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(BL_JNT_HEAD_e));
    }
    if (i_this->m2EC[3] == 0) {
        fire_kaiten_keisan(i_this);
    }
    s16 r6 = 0x120;
    s16 r29_3 = 0x400;
    if ((i_this->m2E9 != 0xFF) && (i_this->mpPath != NULL)) {
        r6 = 0x1000;
        r29_3 = 0x1000;
    }
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->m300, 1, r6);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, r29_3);
    if (i_this->mMode >= MODE_DOUSA_3) {
        i_this->m31C = 1.5f;
        fuwafuwa_keisan(i_this);
    }
    if (i_this->m2D0 == 1) {
        if (blue_body_atari_check(i_this)) {
            return;
        }
    } else if (red_body_atari_check(i_this)) {
        return;
    }
    if (i_this->mMode < MODE_DOUSA_5) {
        return;
    }
    if (i_this->mBodyCoSph.ChkAtShieldHit()) {
        if ((i_this->m2E9 == 0xFF) || (i_this->mpPath == NULL) || (i_this->mMode != MODE_DOUSA_7)) {
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            actor->speedF = 50.0f;
            i_this->mAction = ACTION_KOUGEKI;
            i_this->mMode = MODE_KOUGEKI_10;
        }
    } else if (i_this->m2D3 != 0) {
        x = 600.0f;
        if (fopAcM_searchPlayerDistance(actor) < x) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            if (Line_check(i_this, player->current.pos)) {
                if ((i_this->m2E9 == 0xFF) || (i_this->mpPath == NULL) || (i_this->mMode != MODE_DOUSA_7)) {
                    i_this->mAction = ACTION_KOUGEKI;
                    i_this->mMode = MODE_KOUGEKI_10;
                }
            }
        }
    }
}

/* 000039F0-00003F68       .text action_kougeki__FP8bl_class */
static void action_kougeki(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 x;
    f32 z;

    fopAc_ac_c* player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)player_actor;
    switch (i_this->mMode) {
        case MODE_KOUGEKI_10:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m2F8); i++) {
                i_this->m2F8[i] = 0;
            }
            i_this->mBodyCoSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyCoSph.OnAtHitBit();
            i_this->m304 = 0;
            anm_init(i_this, dRes_INDEX_BL_BCK_HAKKEN_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_monsSeStart(actor, JA_SE_CV_BL_FOUND, 0);
            actor->speedF = 0.0f;
            i_this->mMode++;
            break;
        case MODE_KOUGEKI_11:
            if (!i_this->mpMorf->isStop()) {
                break;
            }
            i_this->mMode++;
        // Fall-through
        case MODE_KOUGEKI_12:
            anm_init(i_this, dRes_INDEX_BL_BCK_ATACK_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_BL_BAS_ATACK_e);
            actor->speedF = 10.0f;
            i_this->m302 = cM_rndFX(768.0f) * (fopAcM_GetID(i_this) & 3);
            i_this->mMode++;
        // Fall-through
        case MODE_KOUGEKI_13:
            if ((i_this->m2E9 != 0xFF) && (i_this->mpPath != NULL)) {
                x = actor->current.pos.x - i_this->m2C4.x;
                z = actor->current.pos.z - i_this->m2C4.z;
                f32 f5 = 700.0f;
                if (std::sqrtf(SQUARE(x) + SQUARE(z)) > f5) {
                    anm_init(i_this, dRes_INDEX_BL_BCK_FLY_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    actor->speedF = cM_rndF(2.0f) + 4.0f;
                    i_this->mAction = ACTION_DOUSA;
                    i_this->mMode = MODE_DOUSA_7;
                    return;
                }
            } else {
                f32 f31 = 700.0f;
                if (fopAcM_searchPlayerDistance(actor) > f31) {
                    actor->speedF = cM_rndF(2.0f) + 4.0f;
                    i_this->mAction = ACTION_DOUSA;
                    i_this->mMode = MODE_DOUSA_5;
                    return;
                }
            }
            break;
        case MODE_KOUGEKI_14:
            cLib_addCalc0(&actor->speedF, 0.5f, 1.0f);
            if (std::fabsf(actor->speedF) < 0.2f) {
                actor->speedF = 0.0f;
                anm_init(i_this, dRes_INDEX_BL_BCK_WARAU_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(actor, JA_SE_CV_BL_FOUND, 0);
                i_this->mMode = MODE_KOUGEKI_15;
            }
            break;
        case MODE_KOUGEKI_15:
            if (i_this->mpMorf->isStop()) {
                i_this->mMode = MODE_KOUGEKI_12;
            }
            break;
    }
    i_this->mpMorf->setPlaySpeed(1.0f);
    if ((i_this->mMode == MODE_KOUGEKI_13) && (fopAcM_searchPlayerDistance(actor) < 230.0f)) {
        i_this->mpMorf->setPlaySpeed(2.0f);
    }
    if (i_this->mBodyCoSph.ChkAtShieldHit()) {
        if (i_this->mMode != MODE_KOUGEKI_14) {
            actor->speedF = -20.0f;
            i_this->mAction = ACTION_KOUGEKI;
            i_this->mMode = MODE_KOUGEKI_14;
        }
    } else if (i_this->mBodyCoSph.ChkAtHit()) {
        fopAc_ac_c* hit_ac = i_this->mBodyCoSph.GetAtHitAc();
        if ((hit_ac != NULL) && (hit_ac == player)) {
            if (i_this->mMode != MODE_KOUGEKI_15) {
                anm_init(i_this, dRes_INDEX_BL_BCK_OOWARAI_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(actor, JA_SE_CV_BL_SUCCESS, 0);
                actor->speedF = 0.0f;
                i_this->m2F8[0] = 0;
                i_this->mMode = MODE_KOUGEKI_15;
            }
        }
    }
    fire_kaiten_keisan(i_this);
    i_this->m300 = i_this->m302 + fopAcM_searchPlayerAngleY(actor);
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->m300, 1, 0x1000);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x400);
    if (i_this->mMode >= MODE_KOUGEKI_12) {
        fuwafuwa_keisan(i_this);
    }
    if (i_this->m2D0 == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}

/* 00003F68-00004128       .text action_sagarimasu__FP8bl_class */
static void action_sagarimasu(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mMode) {
        case MODE_SAGARIMASU_20:
            anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            actor->speedF = REG8_F(10) + 20.0f;
            if ((i_this->mHitType == 4) || (i_this->mHitType == 5)) {
                actor->speedF = REG8_F(11) + 60.0f;
                if (i_this->mHitType == 5) {
                    actor->current.angle.y = player->shape_angle.y - 0x4000;
                }
            }
            i_this->mMode++;
        // Fall-through
        case MODE_SAGARIMASU_21:
            cLib_addCalc0(&actor->speedF, 0.8f, 5.0f);
            if (actor->speedF < 0.1f) {
                i_this->mAction = ACTION_KOUGEKI;
                i_this->mMode = MODE_KOUGEKI_10;
                if ((i_this->m2D3 != 0) && (i_this->m2D0 == 0) && (actor->health <= 0)) {
                    local_28 = actor->current.pos;
                    local_28.y += 30.0f;
                    fopAcM_createDisappear(actor, &local_28, 5, daDisItem_IBALL_e);
                    actor->attention_info.flags = 0;
                    fopAcM_onActor(actor);
                    fopAcM_delete(actor);
                }
            }
            break;
    }
    fire_kaiten_keisan(i_this);
    if (i_this->m2D0 == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}

/* 00004128-000046BC       .text action_kaze_move__FP8bl_class */
static void action_kaze_move(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_2c;
    cXyz local_38;

    switch (i_this->mMode) {
        case MODE_KAZE_MOVE_30:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m2F8); i++) {
                i_this->m2F8[i] = 0;
            }
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mBodyCoSph.SetTgSe(0);
            i_this->mBodyCoSph.SetTgHitMark(dCcG_TgHitMark_None_e);
            i_this->mBodyCoSph.OffTgShield();
            i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyCoSph.ClrAtSet();
            actor->speedF = 15.0f;
            i_this->m310 = 7.0f;
            i_this->m2F8[0] = cM_rndF(500.0f) + 512.0f;
            if (cM_rnd() < 0.5f) {
                i_this->m2F8[0] *= -1;
            }
            if (i_this->mCurrBckIdx != dRes_INDEX_BL_BCK_UCHIWA_e) {
                anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
#if VERSION > VERSION_DEMO
            i_this->m2EC[2] = 0;
#endif
            fire_emitter_clr(i_this);
            fopAcM_seStart(actor, JA_SE_CM_BL_WIND_HIT, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_BL_DAMAGE, 0);
            i_this->mMode++;
        // Fall-through
        case MODE_KAZE_MOVE_31:
            actor->shape_angle.z = actor->shape_angle.z + i_this->m2F8[0];
            cLib_addCalc2(&actor->speed.y, i_this->m310, 0.8f, 2.0f);
            cLib_addCalc0(&actor->speedF, 0.8f, 3.0f);
            if (actor->speedF > 0.1f) {
                break;
            }
            i_this->mMode++;
        // Fall-through
        case MODE_KAZE_MOVE_32:
            i_this->m2D3 = 0;
            actor->speedF = 0.0f;
            i_this->mMode++;
        // Fall-through
        case MODE_KAZE_MOVE_33:
            cLib_addCalc2(&actor->gravity, -3.0f, 0.8f, 0.1f);
            cLib_addCalcAngleS2(&actor->shape_angle.x, -0x7fff, 1, 0x120);
            if (!i_this->mAcch.ChkGroundHit()) {
                break;
            }
            i_this->mMode++;
        // Fall-through
        case MODE_KAZE_MOVE_34:
            actor->speed.y = 15.0f;
            actor->gravity = -3.0f;
            bound_sound_set(i_this);
            i_this->mMode++;
        // Fall-through
        case MODE_KAZE_MOVE_35:
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x400);
            cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 1, 0x400);
            if ((abs(actor->shape_angle.x) < 0x100) && (abs(actor->shape_angle.z) < 0x100)) {
                actor->shape_angle.x = 0;
                actor->shape_angle.z = 0;
                if ((i_this->m2D0 & 0x80) != 0) {
                    i_this->mAction = ACTION_NORMAL_SKULL;
                    i_this->mMode = MODE_NORMAL_SKULL_100;
                } else {
                    i_this->mMode = MODE_KAZE_MOVE_38;
                }
            }
            break;
        case MODE_KAZE_MOVE_36:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m2F8); i++) {
                i_this->m2F8[i] = 0;
            }
            actor->speed.y = 15.0f;
            actor->gravity = -3.0f;
            bound_sound_set(i_this);
            if ((i_this->m2D0 & 0x80) == 0) {
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            }
            i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyCoSph.ClrAtSet();
            actor->speedF = 30.0f;
            local_2c.x = 0.0f;
            local_2c.y = 0.0f;
            local_2c.z = 5000.0f;
            cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor) + 0x8000);
            MtxPosition(&local_2c, &local_38);
            i_this->m2F8[0] = -local_38.x;
            i_this->m2F8[1] = local_38.z;
            i_this->mStts.SetWeight(80);
            i_this->mMode++;
        // Fall-through
        case MODE_KAZE_MOVE_37:
            actor->shape_angle.x += i_this->m2F8[0];
            actor->shape_angle.z += i_this->m2F8[1];
            if (actor->speedF < 5.0f) {
                if (roll_check(i_this)) {
                    if ((i_this->m2D0 & 0x80) != 0) {
                        i_this->mAction = ACTION_NORMAL_SKULL;
                        i_this->mMode = MODE_NORMAL_SKULL_100;
                    } else {
                        i_this->mMode = MODE_KAZE_MOVE_38;
                    }
                }
            } else if (i_this->mAcch.ChkGroundHit()) {
                i_this->m2F8[2] = 1;
                actor->speed.y = 10.0f;
                bound_sound_set(i_this);
            }
            if (i_this->m2F8[2] != 0) {
                cLib_addCalc0(&actor->speedF, 0.8f, 1.0f);
            }
            break;
        case MODE_KAZE_MOVE_38:
            i_this->m2EC[1] = cM_rndF(35.0f) + 70.0f;
            actor->speedF = 0.0f;
            i_this->mMode++;
        // Fall-through
        case MODE_KAZE_MOVE_39:
            if (i_this->m2EC[1] == 0) {
                anm_init(i_this, dRes_INDEX_BL_BCK_START01_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                actor->speedF = 0.0f;
                actor->current.angle.y = actor->shape_angle.y;
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_1;
            }
            break;
        default:
            break;
    }
    i_this->m6E8.remove();
    i_this->m31C = 1.0f;
    if ((i_this->m2D0 & 0x80) != 0) {
        skull_atari_check(i_this);
    } else if (i_this->m2D0 == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}

/* 000046BC-00004B84       .text action_itaiyo_ne_san__FP8bl_class */
static void action_itaiyo_ne_san(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;
    cXyz local_34;
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;

    fopAc_ac_c* player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)player_actor;
    switch (i_this->mMode) {
        case MODE_ITAIYO_NE_SAN_40:
            i_this->m31C = 1.0f;
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m2F8); i++) {
                i_this->m2F8[i] = 0;
            }
            actor->gravity = -3.0f;
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyCoSph.ClrAtSet();
            if (i_this->mCurrBckIdx != dRes_INDEX_BL_BCK_UCHIWA_e) {
                anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
#if VERSION > VERSION_DEMO
            i_this->m2EC[2] = 0;
#endif
            fire_emitter_clr(i_this);
            local_34.x = 0.0f;
            local_34.y = 0.0f;
            if (actor->health <= 0) {
                if (i_this->mHitType == 4) {
                    i_this->m2EC[0] = 0;
                } else {
                    i_this->m2EC[0] = 50;
                    i_this->m310 = 30.0f;
                    actor->speed.y = 30.0f;
                    actor->speedF = 20.0f;
                    local_34.z = 5000.0f;
                    if (i_this->mHitType == 5) {
                        actor->current.angle.y = player->shape_angle.y + -0x4000;
                    }
                    bound_sound_set(i_this);
                }
                actor->attention_info.flags = 0;
                i_this->mMode = MODE_ITAIYO_NE_SAN_42;
            } else {
                i_this->mMode = MODE_ITAIYO_NE_SAN_41;
                actor->speed.y = 15.0f;
                actor->speedF = 10.0f;
                local_34.z = 5000.0f;
                bound_sound_set(i_this);
            }
            cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor) + 0x8000);
            MtxPosition(&local_34, &local_40);
            i_this->m2F8[0] = -local_40.x;
            i_this->m2F8[1] = local_40.z;
            break;
        case MODE_ITAIYO_NE_SAN_41:
            if ((actor->speedF < 0.1f) && (roll_check(i_this))) {
                i_this->mAction = ACTION_KAZE_MOVE;
                i_this->mMode = MODE_KAZE_MOVE_38;
            }
            cLib_addCalc0(&actor->speedF, 0.8f, 1.0f);
            if (i_this->m2D0 == 1) {
                blue_body_atari_check(i_this);
            } else {
                red_body_atari_check(i_this);
            }
            break;
        case MODE_ITAIYO_NE_SAN_42:
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->m310 *= 0.5f;
                if (i_this->m310 < 10.0f) {
                    i_this->m310 = 10.0f;
                }
                actor->speed.y = i_this->m310;
                bound_sound_set(i_this);
                if (i_this->m2EC[0] == 0) {
                    local_4c = actor->current.pos;
                    local_4c.y += 30.0f;
                    fopAcM_createDisappear(actor, &local_4c, 5, daDisItem_IBALL_e);
                    if (i_this->mHitType == 4) {
                        local_58 = actor->current.pos;
                        local_58.y += REG8_F(2) + 25.0f;
                        emitter = dComIfGp_particle_set(
                            dPa_name::ID_IT_JN_DOKURO00,
                            &local_58,
                            &actor->current.angle,
                            &actor->scale,
                            0xFF,
                            NULL,
                            fopAcM_GetRoomNo(actor),
                            &actor->tevStr.mColorK0,
                            &actor->tevStr.mColorK0,
                            NULL
                        );
                        if (emitter != NULL) {
                            emitter->setAwayFromAxisSpeed(30.0f);
                            emitter->setDirectionalSpeed(20.0f);
                        }
                        i_this->m6BC_cXyz = local_58;
                        smoke_set(i_this);
                        i_this->mBodyCoSph.OffTgSetBit();
                        i_this->mBodyCoSph.ClrCoSet();
                        i_this->mBodyCoSph.ClrTgHit();
                        actor->scale.setall(0.0f);
                        i_this->m31C = 0.0f;
                        i_this->m2F8[2] = 180;
                        i_this->m2EC[1] = 10;
                        i_this->mMode++;
                    } else {
                        fopAcM_onActor(actor);
                        fopAcM_delete(actor);
                    }
                }
            }
            break;
        case MODE_ITAIYO_NE_SAN_43:
            if (i_this->m6C8.getEmitter() != NULL) {
                if (i_this->m2EC[1] == 0) {
                    i_this->m6C8.getEmitter()->setGlobalAlpha(i_this->m2F8[2]);
                    i_this->m2F8[2] -= 4;
                    if (i_this->m2F8[2] < 0) {
                        i_this->m6C8.remove();
                    }
                }
            } else {
                fopAcM_onActor(actor);
                fopAcM_delete(actor);
            }
            break;
    }
    actor->shape_angle.x += i_this->m2F8[0];
    actor->shape_angle.z += i_this->m2F8[1];
}

/* 00004B84-00004D3C       .text action_hook_atari__FP8bl_class */
static void action_hook_atari(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mMode) {
        case MODE_HOOK_ATARI_60:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m2F8); i++) {
                i_this->m2F8[i] = 0;
            }
            if (i_this->m6FC.getEmitter() != NULL) {
#if VERSION > VERSION_DEMO
                i_this->m2EC[2] = 0;
#endif
                fire_emitter_clr(i_this);
                anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mBodyCoSph.ClrAtSet();
                actor->speedF = 0.0f;
                fopAcM_seStart(actor, JA_SE_CM_BL_WIND_HIT, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_BL_DAMAGE, 0);
            }
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            i_this->mBodyCoSph.SetTgSe(0);
            i_this->mBodyCoSph.SetTgHitMark(dCcG_TgHitMark_None_e);
            i_this->mBodyCoSph.OffTgShield();
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mMode++;
            break;
        case MODE_HOOK_ATARI_61:
            if (!fopAcM_CheckStatus(actor, fopAcStts_HOOK_CARRY_e)) {
                i_this->mAction = ACTION_KAZE_MOVE;
                i_this->mMode = MODE_KAZE_MOVE_32;
            }
    }
    i_this->m6E8.remove();
}

/* 00004D3C-00004DBC       .text action_come_wait__FP8bl_class */
static void action_come_wait(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mMode) {
        case MODE_COME_WAIT_70:
            if ((i_this->m2D5 != 0xFF) && (dComIfGs_isSwitch(i_this->m2D5, dComIfGp_roomControl_getStayNo()))) {
                fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
                i_this->mAction = ACTION_KAZE_MOVE;
                i_this->mMode = MODE_KAZE_MOVE_38;
            }
    }
}

/* 00004DBC-00005104       .text action_normal_skull__FP8bl_class */
static void action_normal_skull(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;
    cXyz local_28;

    local_28 = actor->current.pos;
    switch (i_this->mMode) {
        case MODE_NORMAL_SKULL_100:
            i_this->m328 = REG8_F(7) + 30.0f;
            actor->gravity = -3.0f;
            if (!fopAcM_checkCarryNow(actor)) {
                break;
            }
            actor->gravity = 0.0f;
            i_this->mBodyCoSph.OffCoSetBit();
            i_this->mMode++;
        case MODE_NORMAL_SKULL_101:
            if (!fopAcM_checkCarryNow(actor)) {
                i_this->mBodyCoSph.OnCoSetBit();
                actor->gravity = -3.0f;
                if (fopAcM_GetSpeedF(actor) > 0.0f) {
                    actor->speed.y = 25.0f;
                    actor->speedF = 35.0f;
                    i_this->mMode = MODE_NORMAL_SKULL_102;
                } else {
                    actor->speedF = 0.0f;
                    actor->speed.setall(0.0f);
                    actor->gravity = -3.0f;
                    i_this->mMode = MODE_NORMAL_SKULL_100;
                }
            }
            break;
        case MODE_NORMAL_SKULL_102:
            if ((i_this->mAcch.ChkGroundHit()) || (i_this->mAcch.ChkWallHit())) {
                actor->speed.setall(0.0f);
                if (i_this->mEnemyFire.mFireDuration == 0) {
#if VERSION >= VERSION_USA
                    actor->speedF = 0.0f;
                    actor->health = 0;
                    actor->attention_info.flags = 0;
#endif
                    i_this->mMode = MODE_NORMAL_SKULL_104;
                }
            }
            break;
        case MODE_NORMAL_SKULL_103:
            bound_sound_set(i_this);
            i_this->mMode = MODE_NORMAL_SKULL_102;
            break;
        case MODE_NORMAL_SKULL_104:
            local_28.y += REG8_F(2) + 25.0f;
            emitter = dComIfGp_particle_set(
                dPa_name::ID_IT_JN_DOKURO00,
                &local_28,
                &actor->current.angle,
                &actor->scale,
                0xFF,
                NULL,
                fopAcM_GetRoomNo(actor),
                &actor->tevStr.mColorK0,
                &actor->tevStr.mColorK0,
                NULL
            );
            if (emitter != NULL) {
                emitter->setAwayFromAxisSpeed(30.0f);
                emitter->setDirectionalSpeed(20.0f);
            }
            i_this->m6BC_cXyz = local_28;
            smoke_set(i_this);
            for (s32 i = 0; i < (s32)cM_rndF(1.99f); i++) {
                fopAcM_createItem(&actor->current.pos, dItemNo_HEART_e, -1, -1, daItemType_0_e, NULL, daItemAct_4_e, NULL);
            }
            i_this->mBodyCoSph.OffTgSetBit();
            i_this->mBodyCoSph.ClrCoSet();
            i_this->mBodyCoSph.ClrTgHit();
#if VERSION < VERSION_USA
            actor->scale.setall(0.0f);
            i_this->m31C = 0.0f;
#else
            i_this->m31C = 0.0f;
            actor->scale.setall(0.0f);
#endif
            i_this->m2F8[ARRAY_SIZE(i_this->m2F8) - 1] = 180;
            i_this->m2EC[1] = 10;
            i_this->mMode++;
            break;
        case MODE_NORMAL_SKULL_105:
            emitter = i_this->m6C8.getEmitter();
            if (emitter != NULL) {
                if (i_this->m2EC[1] == 0) {
                    emitter->setGlobalAlpha(i_this->m2F8[ARRAY_SIZE(i_this->m2F8) - 1]);
                    i_this->m2F8[ARRAY_SIZE(i_this->m2F8) - 1] -= 4;
                    if (i_this->m2F8[ARRAY_SIZE(i_this->m2F8) - 1] < 0) {
                        i_this->m6C8.remove();
                    }
                }
            } else {
                fopAcM_delete(actor);
            }
    }
    i_this->m314 = VERSION_SELECT(REG8_F(0) + 24.0f, REG8_F(0) + 24.0f, 24.0f, 24.0f);
    skull_atari_check(i_this);
}

/* 00005104-00005504       .text daBL_Execute__FP8bl_class */
static BOOL daBL_Execute(bl_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;
    cXyz local_2c;
    cXyz local_38;

    if (i_this->m2EC[2] == 1) {
        i_this->m6FC.remove();
    }
#if VERSION > VERSION_DEMO
    if (i_this->m2EC[5] == 1) {
        fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
    }
#endif
    actor->eyePos = actor->current.pos;
    actor->attention_info.position = actor->current.pos;
    actor->eyePos.y += 40.0f;
    actor->attention_info.position.y += 80.0f;
    if ((i_this->m2D0 & 0x80) == 0) {
        if (i_this->m2D3 == 0) {
            i_this->m2BC->play();
        } else {
            i_this->m2C0->play();
        }
    }
    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpMorf->calc();
        if (i_this->m2EC[2] != 0) {
            i_this->m2EC[2]--;
        }
        return TRUE;
    }
    for (s32 i = 0; i < ARRAY_SIZE(i_this->m2EC); i++) {
        if (i_this->m2EC[i] != 0) {
            i_this->m2EC[i]--;
        }
    }
    switch (i_this->mAction) {
        case ACTION_DOUSA:
            action_dousa(i_this);
            break;
        case ACTION_KOUGEKI:
            action_kougeki(i_this);
            break;
        case ACTION_SAGARIMASU:
            action_sagarimasu(i_this);
            break;
        case ACTION_KAZE_MOVE:
            action_kaze_move(i_this);
            break;
        case ACTION_ITAIYO_NE_SAN:
            action_itaiyo_ne_san(i_this);
            break;
        case ACTION_HOOK_ATARI:
            action_hook_atari(i_this);
            break;
        case ACTION_COME_WAIT:
            action_come_wait(i_this);
            break;
        case ACTION_NORMAL_SKULL:
            action_normal_skull(i_this);
    }
    if (i_this->mMode != MODE_DOUSA_0) {
        s8 roomNo = fopAcM_GetRoomNo(actor);
        u32 mtrlSndId = i_this->mAcch.ChkGroundHit() ? dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd) : 0;
        i_this->mpMorf->play(&actor->eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_20.x = 0.0f;
    local_20.y = 0.0f;
    local_20.z = actor->speedF;
    MtxPosition(&local_20, &local_2c);
    actor->speed.x = local_2c.x;
    actor->speed.z = local_2c.z;
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -55.0f) {
        actor->speed.y = -55.0f;
    }
    cLib_addCalc2(&actor->scale.x, i_this->m31C, 0.3f, 0.3f);
    actor->scale.y = actor->scale.z = actor->scale.x;
    local_38 = actor->current.pos;
    local_38.y += 20.0f;
    i_this->mBodyCoSph.SetC(local_38);
    i_this->mBodyCoSph.SetR(i_this->m328);
    dComIfG_Ccsp()->Set(&i_this->mBodyCoSph);
    if (i_this->mBodyCoSph.ChkCoSet()) {
        fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
    } else {
        fopAcM_posMove(actor, NULL);
    }
    BG_check(i_this);
    if ((i_this->m2D1 == 0) || (actor->gravity)) {
        if ((i_this->mAcch.GetGroundH() != -G_CM3D_F_INF) &&
            (dComIfG_Bgsp()->ChkPolySafe(i_this->mAcch.m_gnd) && (dComIfG_Bgsp()->GetGroundCode(i_this->mAcch.m_gnd) == 4)))
        {
            if (actor->current.pos.y < i_this->m320 - 500.0f) {
                actor->speedF = 0.0f;
                actor->speed.setall(0.0f);
                actor->gravity = 0.0f;
                fopAcM_onActor(actor);
                fopAcM_delete(actor);
            }
        }
    }
    draw_SUB(i_this);
    return TRUE;
}

/* 00005504-0000550C       .text daBL_IsDelete__FP8bl_class */
static BOOL daBL_IsDelete(bl_class*) {
    return TRUE;
}

/* 0000550C-0000558C       .text daBL_Delete__FP8bl_class */
static BOOL daBL_Delete(bl_class* i_this) {
    i_this->m6E8.remove();
    i_this->m6FC.remove();
    i_this->m6C8.remove();
    enemy_fire_remove(&i_this->mEnemyFire);
    dComIfG_resDeleteDemo(&i_this->mPhase, "BL");
    return TRUE;
}

/* 0000558C-0000583C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    bl_class* i_this = (bl_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BDL_BL_e),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BCK_START01_e),
        J3DFrameCtrl::EMode_RESET,
        0.0f,
        0,
        -1,
        1,
        NULL,
        0x00080000,
        0x37441422
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    J3DModel* model = i_this->mpMorf->getModel();
    i_this->m2C0 = new mDoExt_btkAnm();
    if (i_this->m2C0 == NULL) {
        return FALSE;
    }
    if (!i_this->m2C0->init(model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BTK_ON_e), true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    if (i_this->m2C0 == NULL) {
        return FALSE;
    }
    i_this->m2BC = new mDoExt_btkAnm();
    if (i_this->m2BC == NULL) {
        return FALSE;
    }
    if (!i_this->m2BC->init(model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BTK_OFF_e), true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    if (i_this->m2BC == NULL) {
        return FALSE;
    }
    i_this->mpMorf->getModel()->setUserArea((u32)i_this);
    if (i_this->mInvisibleModel.create(i_this->mpMorf->getModel())) {
        return TRUE;
    }
    return FALSE;
}

/* 00005884-00005D88       .text daBL_Create__FP10fopAc_ac_c */
static cPhs_State daBL_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph body_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_WOOD,
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

    bl_class* i_this = (bl_class*)a_this;

    fopAcM_ct_Retail(a_this, bl_class);
    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "BL");
    if (res == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(a_this, bl_class);
        i_this->m2D0 = fopAcM_GetParam(a_this);
        i_this->m2D1 = (fopAcM_GetParam(a_this) >> 0x18);
        i_this->m2E9 = (fopAcM_GetParam(a_this) >> 0x10);
        i_this->m2D5 = (fopAcM_GetParam(a_this) >> 8);
        i_this->m324 = a_this->current.angle.z;
        a_this->current.angle.z = 0;
        a_this->shape_angle.z = 0;
        if (i_this->m2D0 == 0xFF) {
            i_this->m2D0 = 0;
        }
        if (i_this->m2D1 == 0xFF) {
            i_this->m2D1 = 0;
        }
        if (REG8_S(8) != 0) {
            i_this->m2D1 = 1;
        }
        if (REG8_S(9) != 0) {
            i_this->m2D0 = REG8_S(9) - 1;
        }
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x14E0)) {
            return cPhs_ERROR_e;
        }
        if ((i_this->m2D0 & 2) != 0) {
            i_this->m2D0 ^= 2;
            if (i_this->m2E9 != 0xFF) {
                i_this->mpPath = dPath_GetRoomPath(i_this->m2E9, fopAcM_GetRoomNo(a_this));
                if (i_this->m324 < 4.0f) {
                    i_this->m324 = cM_rndF(2.0f) + 4.0f;
                }
            }
            if (REG8_S(9) != 0) {
                i_this->m2E9 = 0;
                i_this->mpPath = dPath_GetRoomPath(i_this->m2E9, fopAcM_GetRoomNo(a_this));
            }
        }
        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        a_this->attention_info.flags = 0;
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mStts.Init(80, 1, a_this);
        a_this->max_health = 2;
        a_this->health = 2;
        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mWallRadius = 50.0f;
        i_this->mEnemyIce.mCylHeight = 50.0f;
        i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
        i_this->mEnemyFire.mpActor = a_this;

        static u8 fire_j[ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs)] = {
            BL_JNT_HEAD_e,
            BL_JNT_AGO_e,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
        };
        static f32 fire_sc[ARRAY_SIZE(i_this->mEnemyFire.mParticleScale)] = {
            1.0f, // BL_JNT_HEAD_e
            1.0f, // BL_JNT_AGO_e
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
            1.0f,
        };

        for (int i = 0; i < ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
            i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }
        i_this->m328 = 50.0f;
#if VERSION == VERSION_DEMO
        draw_SUB(i_this);
#endif
        i_this->m300 = a_this->shape_angle.y;
        i_this->mBodyCoSph.Set(body_co_sph_src);
        i_this->mBodyCoSph.SetStts(&i_this->mStts);
        i_this->mBodyCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mBodyCoSph.ClrAtSet();
        a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x29;
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("bable_r", 0);
        a_this->gbaName = 0xe;
        if (i_this->m2D0 == 1) {
            i_this->mBodyCoSph.SetAtSpl(dCcG_At_Spl_UNK3);
            i_this->mBodyCoSph.SetAtType(AT_TYPE_UNK800);
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("bable", 0);
            a_this->gbaName = 0xF;
        }
        a_this->gravity = -3.0f;
        a_this->speed.y += a_this->gravity;
        if (a_this->speed.y < -55.0f) {
            a_this->speed.y = -55.0f;
        }
        i_this->m31C = 1.0f;
        i_this->m314 = 24.0f;
        i_this->m2C4 = a_this->current.pos;
        fopAcM_posMove(a_this, i_this->mStts.GetCCMoveP());
        BG_check(i_this);
        i_this->m320 = a_this->current.pos.y;
        if (i_this->m2D1 == 0) {
            i_this->m320 = i_this->mAcch.GetGroundH();
        }
        i_this->mAction = ACTION_DOUSA;
        if (!i_this->mAcch.ChkGroundHit()) {
#if VERSION > VERSION_DEMO
            a_this->scale.setall(0.0f);
#endif
            a_this->gravity = 0.0f;
            a_this->speed.y = 0.0f;
            a_this->current.pos.y = i_this->m320 + 100.0f;
            i_this->mMode = MODE_DOUSA_4;
        } else {
            i_this->mMode = MODE_DOUSA_0;
        }
        if ((i_this->m2D5 != 0xFF) && (!dComIfGs_isSwitch(i_this->m2D5, dComIfGp_roomControl_getStayNo()))) {
            fopAcM_OffStatus(a_this, fopAcStts_SHOWMAP_e);
            i_this->mAction = ACTION_COME_WAIT;
            i_this->mMode = MODE_COME_WAIT_70;
        }
        if ((i_this->m2D0 & 0x80) != 0) {
            a_this->max_health = 1;
            a_this->health = 1;
            i_this->m2D3 = 1;
            i_this->mBodyCoSph.OnCoSetBit();
            a_this->current.angle.y = cM_rndFX(32767.0f);
            a_this->shape_angle.y = a_this->current.angle.y;
#if VERSION > VERSION_DEMO
            fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
            i_this->m2EC[5] = 4;
#endif
            fopAcM_OffStatus(a_this, fopAcStts_SHOWMAP_e);
            cLib_onBit<u32>(a_this->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            i_this->mAction = ACTION_NORMAL_SKULL;
            i_this->mMode = MODE_NORMAL_SKULL_100;
        } else {
            a_this->stealItemLeft = 1;
            i_this->m2EA = a_this->stealItemLeft;
        }
#if VERSION > VERSION_DEMO
        draw_SUB(i_this);
#endif
    }
    return res;
}

static actor_method_class l_daBL_Method = {
    (process_method_func)daBL_Create,
    (process_method_func)daBL_Delete,
    (process_method_func)daBL_Execute,
    (process_method_func)daBL_IsDelete,
    (process_method_func)daBL_Draw,
};

actor_process_profile_definition g_profile_BL = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_BL_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bl_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_BL_e,
    /* Actor SubMtd */ &l_daBL_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
