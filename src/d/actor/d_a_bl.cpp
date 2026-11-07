/**
 * d_a_bl.cpp
 * Enemy - Bubble
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bl.h"
#include "d/actor/d_a_player.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "d/d_s_play.h"
#include "d/d_material.h"
#include "d/d_path.h"
#include "d/d_bg_s_lin_chk.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "f_op/f_op_camera.h"
#include "res/Object/Bl.h"

/* 00000078-00000178       .text draw_SUB__FP8bl_class */
void draw_SUB(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(a_this->scale);
    MtxTrans(a_this->current.pos.x, a_this->current.pos.y + i_this->m314, a_this->current.pos.z, false);
    mDoMtx_YrotM(*calc_mtx, a_this->shape_angle.y);
    mDoMtx_XrotM(*calc_mtx, a_this->shape_angle.x);
    mDoMtx_ZrotM(*calc_mtx, a_this->shape_angle.z);
    MtxTrans(0.0f, -i_this->m314, 0.0f, true);
    model->setBaseTRMtx(*calc_mtx);
    i_this->mpMorf->calc();
    enemy_fire(&i_this->mEnemyFire);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &a_this->current.pos, &a_this->tevStr);
}


/* 00000178-000002F8       .text daBL_Draw__FP8bl_class */
static BOOL daBL_Draw(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    J3DModel* model = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(model, &a_this->tevStr);
    if (i_this->mSwitchNo != 0xFF && !dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
        return TRUE;
    }
    dSnap_RegistFig(DSNAP_TYPE_UNKB4, a_this, 1.0f, 1.0f, 1.0f);
    if (i_this->mEnemyIce.mFreezeTimer > 0x14) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, &i_this->mInvisibleModel);
        return TRUE;
    }
    if (i_this->m2D3 == 0) {
        i_this->mpBtkOff->entry(model->getModelData());
    } else {
        i_this->mpBtkOn->entry(model->getModelData());
    }
    i_this->mpMorf->entryDL();
    if (a_this->health > 0) {
        dComIfGd_setSimpleShadow2(&a_this->current.pos, i_this->mAcch.GetGroundH(), 30.0f, i_this->mAcch.m_gnd);
    }
    if (i_this->m2D3 == 0) {
        i_this->mpBtkOff->remove(model->getModelData());
    } else {
        i_this->mpBtkOn->remove(model->getModelData());
    }
    return TRUE;
}


/* 000002F8-000003F8       .text smoke_set__FP8bl_class */
void smoke_set(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    if (i_this->mSmokeCb.getEmitter() == NULL) {
        dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE01, &i_this->m698[3], &a_this->shape_angle, NULL, 0xB9, &i_this->mSmokeCb, fopAcM_GetRoomNo(a_this));
    }
    JPABaseEmitter* emitter = i_this->mSmokeCb.getEmitter();
    if (emitter != NULL) {
        GXColor color = {0xA0, 0xA0, 0x80, 0xB4};
        JGeometry::TVec3<f32> scale;
        scale.x = scale.y = scale.z = 1.6f;
        emitter->setGlobalParticleScale(scale);
        i_this->mSmokeCb.getEmitter()->setRate(10.0f);
        i_this->mSmokeCb.getEmitter()->setMaxFrame(1);
        i_this->mSmokeCb.getEmitter()->setAwayFromCenterSpeed(8.0f);
        i_this->mSmokeCb.getEmitter()->setStatus(JPAEmtrStts_Immortal);
        i_this->mSmokeCb.setColor(color);
    }
}


/* 000003F8-000004AC       .text fire_move_set__FP8bl_class */
void fire_move_set(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    u16 name; if (i_this->mType == 0) { name = dPa_name::ID_AK_SN_BUBBLERED00; } else { name = dPa_name::ID_AK_SN_BUBBLEBLUE00; }
    if (i_this->mFollowCb1.getEmitter() == NULL) {
        dComIfGp_particle_set(name, &a_this->current.pos, NULL, NULL, 0xFF, &i_this->mFollowCb1, fopAcM_GetRoomNo(a_this));
        if (i_this->mType == 1) {
            i_this->mSph.SetTgSe(dCcG_SE_METAL);
            i_this->mSph.SetTgHitMark(dCcg_TgHitMark_Purple_e);
            i_this->mSph.OnTgShield();
        }
    }
}


/* 000004AC-00000578       .text fire_emitter_clr__FP8bl_class */
void fire_emitter_clr(bl_class* i_this) {
    JPABaseEmitter* emitter = i_this->mFollowCb1.getEmitter();
    if (emitter != NULL && i_this->mTimers[2] == 0) {
        if (i_this->mType == 0) {
            JGeometry::TVec3<s16> rot;
            rot.x = 0;
            rot.y = dComIfGp_getPlayer(0)->shape_angle.y + 0x8000;
            rot.z = 0;
            emitter->setGlobalRotation(rot);
            i_this->mFollowCb1.getEmitter()->setRate(3.0f);
            i_this->mFollowCb1.getEmitter()->setLifeTime(10);
            i_this->mFollowCb1.getEmitter()->setDirectionalSpeed(50.0f);
            i_this->mTimers[2] = 0x15;
        } else {
            i_this->mTimers[2] = 1;
        }
    }
    i_this->mFollowCb0.remove();
}


/* 00000578-000006E0       .text fire_kaiten_keisan__FP8bl_class */
void fire_kaiten_keisan(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    JPABaseEmitter* emitter = i_this->mFollowCb1.getEmitter();
    if (emitter != NULL) {
        if (i_this->mType == 0) {
            emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
            fopAcM_seStart(a_this, JA_SE_CM_BL_FLAME_BURNING, 0);
        } else {
            fopAcM_seStart(a_this, JA_SE_CM_BL_CURSE_BURNING, 0);
            camera_process_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
            MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0), *calc_mtx);
            mDoMtx_YrotM(*calc_mtx, camera->mAngle.y - a_this->shape_angle.y);
            i_this->mFollowCb1.getEmitter()->setGlobalRTMatrix(*calc_mtx);
        }
    }
}


/* 000006E0-00000820       .text shock_damage_check__FP8bl_class */
BOOL shock_damage_check(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (!(i_this->mType & 0x80) && i_this->m2D3 != 0) {
        return FALSE;
    }
    if (player->checkHammerQuake()) {
        cXyz sp18;
        sp18 = player->getSwordTopPos();
        sp18.x -= a_this->current.pos.x;
        sp18.z -= a_this->current.pos.z;
        if (std::sqrtf(SQUARE(sp18.x) + SQUARE(sp18.z)) < 1000.0f) {
            i_this->mTimers[2] = 0;
            fire_emitter_clr(i_this);
            return TRUE;
        }
    }
    return FALSE;
}


/* 00000820-0000094C       .text anm_init__FP8bl_classifUcfi */
void anm_init(bl_class* i_this, int anmResIdx, float morf, unsigned char loopMode, float playSpeed, int soundResIdx) {
    i_this->mAnmIdx = anmResIdx;
    if (soundResIdx >= 0) {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BL", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, dComIfG_getObjectRes("BL", soundResIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BL", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
    }
}


/* 0000094C-00000C08       .text skull_atari_check__FP8bl_class */
BOOL skull_atari_check(bl_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* a_this = i_this;

    i_this->mStts.Move();
    if (a_this->health == 0) {
        return TRUE;
    }
    if (shock_damage_check(i_this)) {
        i_this->mAction = 3;
        i_this->mMode = 0x22;
        return TRUE;
    }
    if (!i_this->mSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->mTimers[4] != 0) {
        return FALSE;
    }

    a_this->current.angle.y = fopAcM_searchPlayerAngleY(a_this) + 0x8000;
    bool noSe = false;
    CcAtInfo atInfo; // unused; matches blue/red_body (emits csXyz dtor here)
    i_this->mTimers[4] = 8;
    i_this->m2D4 = 0;
    switch (hitObj->GetAtType()) {
    case AT_TYPE_SWORD:
        i_this->m2D4 = 6;
        break;
    case AT_TYPE_WIND:
        noSe = true;
        i_this->m2D4 = 1;
        i_this->mAction = 3;
        i_this->mMode = 0x24;
        break;
    case AT_TYPE_SKULL_HAMMER:
        i_this->m2D4 = 4;
        if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
            a_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->m2D4 = 5;
            a_this->speed.y = 30.0f;
            a_this->speedF = 20.0f;
        }
        break;
    case AT_TYPE_BOOMERANG:
    case AT_TYPE_BOKO_STICK:
        i_this->m2D4 = 3;
        break;
    case AT_TYPE_BOMB:
        a_this->speed.y = 30.0f;
    case AT_TYPE_FIRE:
        i_this->mEnemyFire.mFireDuration = 1000;
        break;
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_ICE_ARROW:
    case AT_TYPE_LIGHT_ARROW:
        break;
    case AT_TYPE_HOOKSHOT:
        noSe = true;
        i_this->m2D4 = 7;
        i_this->mAction = 5;
        i_this->mMode = 0x3C;
        break;
    }

    cXyz hitPos = *i_this->mSph.GetTgHitPosP();
    if (!noSe) {
        fopAcM_seStart(a_this, JA_SE_OBJ_BREAK_STONE, 0);
        a_this->health = 0;
        a_this->attention_info.flags = 0;
        i_this->mAction = 0xA;
        i_this->mMode = 0x67;
    }
    return TRUE;
}


/* 00000C44-00001768       .text blue_body_atari_check__FP8bl_class */
BOOL blue_body_atari_check(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->mStts.Move();
    if (shock_damage_check(i_this)) {
        i_this->mAction = 3;
        i_this->mMode = 0x22;
        return TRUE;
    }
    if (!i_this->mSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->mTimers[4] != 0) {
        return FALSE;
    }

    i_this->current.angle.y = fopAcM_searchPlayerAngleY(i_this) + 0x8000;
    bool noDamage = false;
    CcAtInfo atInfo;
    i_this->mTimers[4] = 8;
    i_this->m2D4 = 0;
    switch (hitObj->GetAtType()) {
    case AT_TYPE_GRAPPLING_HOOK:
        if (i_this->m2D3 != 0) {
            i_this->stealItemLeft = i_this->m2EA;
            if (i_this->stealItemLeft > 0) {
                s8 health = i_this->health;
                i_this->health = 10;
                atInfo.mpObj = i_this->mSph.GetTgHitObj();
                atInfo.pParticlePos = NULL;
                cc_at_check(i_this, &atInfo);
                i_this->health = health;
            }
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
            if (i_this->m2EA > 0) {
                i_this->m2EA--;
            }
            dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &i_this->attention_info.position);
            noDamage = true;
        } else {
            i_this->stealItemLeft = 0;
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x33);
        }
        break;
    case AT_TYPE_SWORD:
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_SW_HIT_S, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_SW_HIT_S, 0x42);
        }
        if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EA ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EB ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_TURN ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_ROLL ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SWORD ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_STICK ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_MACHETE ||
            player->getCutType() == daPy_py_c::CUT_TYPE_BT_JUMPCUT ||
            player->getCutType() == daPy_py_c::CUT_TYPE_BT_ROLLCUT ||
            player->getCutType() == daPy_py_c::CUT_TYPE_BT_VERTICALJUMPCUT ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_CLUB ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_DN_SWORD ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SPEAR ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXA ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXB ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXMJ ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_KESA)
        {
            i_this->m2D4 = 6;
        }
        break;
    case AT_TYPE_BOMB:
        if (i_this->m2D3 == 0) {
            i_this->m2D4 = 2;
            break;
        }
    case AT_TYPE_WIND:
        noDamage = true;
        i_this->m2D4 = 1;
        i_this->mAction = 3;
        i_this->mMode = 0x24;
        if (!i_this->mAcch.ChkGroundHit() && i_this->gravity > -2.0f) {
            i_this->mMode = 0x1E;
        }
        break;
    case AT_TYPE_SKULL_HAMMER:
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_HAMMER_HIT, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_HAMMER_HIT, 0x42);
        }
        i_this->m2D4 = 4;
        if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
            i_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->m2D4 = 5;
        }
        if (i_this->m2D3 == 0) {
            i_this->health = 0;
        }
        break;
    case AT_TYPE_BOOMERANG:
    case AT_TYPE_BOKO_STICK:
        noDamage = true;
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_W_WEP_HIT, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_W_WEP_HIT, 0x42);
        }
        i_this->m2D4 = 3;
        break;
    case AT_TYPE_FIRE:
    case AT_TYPE_FIRE_ARROW:
        if (i_this->m2D3 == 0) {
            i_this->mEnemyFire.mFireDuration = 100;
            fopAcM_seStart(a_this, JA_SE_CM_BL_WIND_HIT, 0);
            fopAcM_monsSeStart(a_this, JA_SE_CV_BL_DAMAGE, 0);
            i_this->mSph.OffAtSetBit();
            i_this->mSph.OffAtSetBit();
            i_this->attention_info.flags = 0;
            i_this->mTimers[2] = 0;
            fire_emitter_clr(i_this);
        }
        break;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 40.0f;
        fopAcM_seStart(a_this, JA_SE_CM_BL_WIND_HIT, 0);
        fopAcM_monsSeStart(a_this, JA_SE_CV_BL_DAMAGE, 0);
        i_this->current.angle.x = 0;
        i_this->current.angle.z = 0;
        i_this->m2D3 = 0;
        i_this->shape_angle.x = 0;
        i_this->shape_angle.z = 0;
        i_this->gravity = 0.0f;
        i_this->speedF = 0.0f;
        i_this->mTimers[0] = 0;
        i_this->speed.x = 0.0f;
        i_this->speed.y = 0.0f;
        i_this->speed.z = 0.0f;
        i_this->mSph.OffAtSetBit();
        i_this->mSph.OffAtSetBit();
        i_this->attention_info.flags = 0;
        i_this->mTimers[2] = 0;
        fire_emitter_clr(i_this);
        break;
    case AT_TYPE_ICE_ARROW:
        if (i_this->m2D3 == 0) {
            noDamage = true;
            i_this->m2D3 = 0;
            i_this->current.angle.x = 0;
            i_this->current.angle.z = 0;
            i_this->shape_angle.x = 0;
            i_this->shape_angle.z = 0;
            i_this->gravity = 0.0f;
            i_this->speedF = 0.0f;
            i_this->mTimers[0] = 0;
            i_this->speed.x = 0.0f;
            i_this->speed.y = 0.0f;
            i_this->speed.z = 0.0f;
            i_this->mSph.OffAtSetBit();
            i_this->mSph.OffAtSetBit();
            i_this->mEnemyIce.mFreezeDuration = 200;
            enemy_fire_remove(&i_this->mEnemyFire);
            i_this->attention_info.flags = 0;
        } else {
            noDamage = true;
            i_this->m2D4 = 1;
            i_this->mAction = 3;
            i_this->mMode = 0x1E;
        }
        break;
    case AT_TYPE_HOOKSHOT:
        noDamage = true;
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
        }
        i_this->m2D4 = 7;
        i_this->mAction = 5;
        i_this->mMode = 0x3C;
        break;
    default:
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
        }
        break;
    }

    cXyz hitPos = *i_this->mSph.GetTgHitPosP();
    if (i_this->m2D3 != 0 && i_this->m2D4 != 7 && i_this->m2D4 != 1) {
        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &hitPos);
        i_this->mAction = 2;
        i_this->mMode = 0x14;
        return TRUE;
    }
    if (!noDamage) {
        atInfo.mpObj = i_this->mSph.GetTgHitObj();
        atInfo.pParticlePos = NULL;
        cc_at_check(i_this, &atInfo);
        if (i_this->m2D4 == 6 || i_this->m2D4 == 5 || i_this->m2D4 == 4 || i_this->health <= 0) {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &hitPos);
            cXyz scale(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &hitPos, &player->shape_angle, &scale);
        } else {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &hitPos, &player->shape_angle);
        }
        i_this->mAction = 4;
        i_this->mMode = 0x28;
    }
    return TRUE;
}


/* 00001768-000022BC       .text red_body_atari_check__FP8bl_class */
BOOL red_body_atari_check(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->mStts.Move();
    if (shock_damage_check(i_this)) {
        i_this->mAction = 3;
        i_this->mMode = 0x22;
        return TRUE;
    }
    if (!i_this->mSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    if (i_this->mTimers[4] != 0) {
        return FALSE;
    }

    i_this->current.angle.y = fopAcM_searchPlayerAngleY(i_this) + 0x8000;
    bool noDamage = false;
    CcAtInfo atInfo;
    cXyz hitPos = *i_this->mSph.GetTgHitPosP();
    i_this->mTimers[4] = 8;
    i_this->m2D4 = 0;
    u32 atType = hitObj->GetAtType();
    switch (atType) {
    case AT_TYPE_GRAPPLING_HOOK:
        if (i_this->m2D3 != 0) {
            i_this->stealItemLeft = i_this->m2EA;
            if (i_this->stealItemLeft > 0) {
                s8 health = i_this->health;
                i_this->health = 10;
                atInfo.mpObj = i_this->mSph.GetTgHitObj();
                atInfo.pParticlePos = NULL;
                cc_at_check(i_this, &atInfo);
                i_this->health = health;
            }
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
            if (i_this->m2EA > 0) {
                i_this->m2EA--;
            }
            dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &i_this->attention_info.position);
            noDamage = true;
        } else {
            i_this->stealItemLeft = 0;
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x33);
        }
        break;
    case AT_TYPE_SWORD:
        i_this->m2D4 = 8;
        fopAcM_seStart(i_this, JA_SE_LK_SW_HIT_S, 0x33);
        if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EA ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EB ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_TURN ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_ROLL ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SWORD ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_STICK ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_MACHETE ||
            player->getCutType() == daPy_py_c::CUT_TYPE_BT_JUMPCUT ||
            player->getCutType() == daPy_py_c::CUT_TYPE_BT_ROLLCUT ||
            player->getCutType() == daPy_py_c::CUT_TYPE_BT_VERTICALJUMPCUT ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_CLUB ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_DN_SWORD ||
            player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SPEAR ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXA ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXB ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_EXMJ ||
            player->getCutType() == daPy_py_c::CUT_TYPE_CUT_KESA)
        {
            i_this->m2D4 = 6;
        }
        break;
    case AT_TYPE_BOMB:
        if (i_this->m2D3 == 0) {
            i_this->m2D4 = 2;
            break;
        }
    case AT_TYPE_WIND:
        noDamage = true;
        i_this->m2D4 = 1;
        i_this->mAction = 3;
        i_this->mMode = 0x24;
        if (!i_this->mAcch.ChkGroundHit() && i_this->gravity > -2.0f) {
            i_this->mMode = 0x1E;
        }
        break;
    case AT_TYPE_SKULL_HAMMER:
        fopAcM_seStart(i_this, JA_SE_LK_HAMMER_HIT, 0x33);
        i_this->m2D4 = 4;
        if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
            i_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->m2D4 = 5;
        }
        i_this->health = 0;
        break;
    case AT_TYPE_BOOMERANG:
    case AT_TYPE_BOKO_STICK:
        noDamage = true;
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_W_WEP_HIT, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_W_WEP_HIT, 0x42);
        }
        i_this->m2D4 = 3;
        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &hitPos);
        break;
    case AT_TYPE_FIRE:
    case AT_TYPE_NORMAL_ARROW:
    case AT_TYPE_FIRE_ARROW:
        if (i_this->m2D3 == 0 || !(atType & AT_TYPE_FIRE)) {
            if (i_this->m2D3 == 0 && !(atType & AT_TYPE_NORMAL_ARROW)) {
                i_this->mEnemyFire.mFireDuration = 100;
            }
            fopAcM_seStart(a_this, JA_SE_CM_BL_WIND_HIT, 0);
            fopAcM_monsSeStart(a_this, JA_SE_CV_BL_DAMAGE, 0);
            i_this->mSph.OffAtSetBit();
            i_this->mSph.OffAtSetBit();
            i_this->attention_info.flags = 0;
            i_this->mTimers[2] = 0;
            fire_emitter_clr(i_this);
        }
        break;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 40.0f;
        fopAcM_seStart(a_this, JA_SE_CM_BL_WIND_HIT, 0);
        fopAcM_monsSeStart(a_this, JA_SE_CV_BL_DAMAGE, 0);
        i_this->current.angle.x = 0;
        i_this->current.angle.z = 0;
        i_this->m2D3 = 0;
        i_this->shape_angle.x = 0;
        i_this->shape_angle.z = 0;
        i_this->gravity = 0.0f;
        i_this->speedF = 0.0f;
        i_this->mTimers[0] = 0;
        i_this->speed.x = 0.0f;
        i_this->speed.y = 0.0f;
        i_this->speed.z = 0.0f;
        i_this->mSph.OffAtSetBit();
        i_this->mSph.OffAtSetBit();
        i_this->attention_info.flags = 0;
        i_this->mTimers[2] = 0;
        fire_emitter_clr(i_this);
        break;
    case AT_TYPE_ICE_ARROW:
        noDamage = true;
        i_this->m2D3 = 0;
        i_this->current.angle.x = 0;
        i_this->current.angle.z = 0;
        i_this->shape_angle.x = 0;
        i_this->shape_angle.z = 0;
        i_this->gravity = 0.0f;
        i_this->speedF = 0.0f;
        i_this->mTimers[0] = 0;
        i_this->speed.x = 0.0f;
        i_this->speed.y = 0.0f;
        i_this->speed.z = 0.0f;
        i_this->mTimers[2] = 0;
        fire_emitter_clr(i_this);
        i_this->mSph.OffAtSetBit();
        i_this->mSph.OffAtSetBit();
        i_this->mEnemyIce.mFreezeDuration = 200;
        enemy_fire_remove(&i_this->mEnemyFire);
        i_this->attention_info.flags = 0;
        break;
    case AT_TYPE_HOOKSHOT:
        noDamage = true;
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
        }
        i_this->m2D4 = 7;
        i_this->mAction = 5;
        i_this->mMode = 0x3C;
        break;
    default:
        noDamage = true;
        if (i_this->m2D3 == 0) {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x33);
        } else {
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
        }
        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &hitPos);
        break;
    }

    if (!noDamage) {
        atInfo.mpObj = i_this->mSph.GetTgHitObj();
        atInfo.pParticlePos = NULL;
        cc_at_check(i_this, &atInfo);
        if (i_this->m2D4 == 6 || i_this->m2D4 == 5 || i_this->m2D4 == 4 || i_this->health <= 0) {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &hitPos);
            cXyz scale(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &hitPos, &player->shape_angle, &scale);
        } else {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &hitPos, &player->shape_angle);
        }
        if (i_this->m2D3 != 0) {
            anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->speedF = 60.0f + REG8_F(10);
            if (i_this->health <= 0) {
                i_this->speedF = 60.0f + REG8_F(11);
                if (i_this->m2D4 == 5) {
                    i_this->current.angle.y = player->shape_angle.y - 0x4000;
                }
            }
            fopAcM_monsSeStart(a_this, JA_SE_CV_BL_DAMAGE, 0);
            i_this->mAction = 2;
            i_this->mMode = 0x15;
        } else {
            i_this->mAction = 4;
            i_this->mMode = 0x28;
        }
    }
    return TRUE;
}


/* 000022BC-00002354       .text bound_sound_set__FP8bl_class */
void bound_sound_set(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    u32 mapinfo = (u32)(3.3f * a_this->speed.y);
    if (mapinfo > 100) {
        mapinfo = 100;
    }
    fopAcM_seStart(a_this, JA_SE_CM_BL_BOUND, mapinfo);
}


/* 00002354-00002458       .text fuwafuwa_keisan__FP8bl_class */
void fuwafuwa_keisan(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    f32 step = 3.0f;
    if (i_this->mAction == 1) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        i_this->m304 += 1000;
        i_this->m318 = player->current.pos.y + 80.0f;
        i_this->m318 += 10.0f * cM_ssin(i_this->m304);
        step = 6.0f;
    } else {
        i_this->m304 += 500;
        i_this->m318 = i_this->m320 + 100.0f;
        i_this->m318 += 40.0f * cM_ssin(i_this->m304);
    }
    cLib_addCalc2(&a_this->current.pos.y, i_this->m318, 1.0f, step);
}


/* 00002458-000024E4       .text BG_check__FP8bl_class */
void BG_check(bl_class* i_this) {
    if (i_this->mMode != 2) {
        i_this->mAcchCir.SetWall(40.0f, 40.0f);
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        i_this->mAcch.OnLineCheck();
        if (i_this->m2D1 == 0 && i_this->mAcch.GetGroundH() == -1000000000.0f) {
            i_this->m320 = i_this->mAcch.GetGroundH();
        }
    }
}


/* 000024E4-00002804       .text Line_check__FP8bl_class4cXyz */
BOOL Line_check(bl_class* i_this, cXyz destPos) {
    fopAc_ac_c* a_this = i_this;
    dBgS_LinChk linChk;
    cXyz centerPos = a_this->current.pos;
    centerPos.y += 100.0f;
    destPos.y += 100.0f;
    linChk.Set(&centerPos, &destPos, a_this);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}


/* 00002C3C-00002CC4       .text roll_check__FP8bl_class */
BOOL roll_check(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    cLib_addCalcAngleS2(&a_this->shape_angle.x, 0, 1, 0x1000);
    cLib_addCalcAngleS2(&a_this->shape_angle.z, 0, 1, 0x1000);
    i_this->m2F8[0] = 0;
    i_this->m2F8[1] = 0;
    if (abs(a_this->shape_angle.x) < 0x200 && abs(a_this->shape_angle.z) < 0x200) {
        return TRUE;
    }
    return FALSE;
}


/* 00002CC4-00003054       .text way_check__FP8bl_classs */
s16 way_check(bl_class* i_this, s16 angle) {
    fopAc_ac_c* a_this = i_this;
    dBgS_LinChk linChk;
    cXyz offset;
    cXyz endPos;
    s16 checkAngle = angle;
    s16 step = 0x2000;
    if (cM_rndFX(1.0f) < 0.5f) {
        step = -0x2000;
    }
    for (int i = 0; i < 8; i++) {
        mDoMtx_YrotS(*calc_mtx, checkAngle);
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 300.0f;
        MtxPosition(&offset, &endPos);
        endPos += a_this->current.pos;
        linChk.Set(&a_this->current.pos, &endPos, a_this);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            return checkAngle;
        }
        checkAngle += step;
    }
    return angle;
}


/* 00003054-000039F0       .text action_dousa__FP8bl_class */
void action_dousa(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    s16 angle;
    f32 dz, dx;

    switch (i_this->mMode) {
    case 0:
        i_this->m304 = 0;
        if (fopAcM_searchActorDistance(a_this, dComIfGp_getPlayer(0)) > 1000.0f) {
            break;
        }
        fopAcM_OnStatus(a_this, fopAcStts_SHOWMAP_e);
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        anm_init(i_this, dRes_INDEX_BL_BCK_START01_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mMode++;
        break;
    case 1:
        i_this->m31C = 1.5f;
        if (i_this->mFollowCb0.getEmitter() == NULL) {
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BUBBLEBOOT00, &a_this->current.pos, NULL, NULL, 0xFF, &i_this->mFollowCb0);
            fopAcM_seStart(a_this, JA_SE_CM_BL_ENTER, 0);
        }
        if (i_this->mFollowCb0.getEmitter() != NULL) {
            if (i_this->mType == 0) {
                i_this->mFollowCb0.getEmitter()->setGlobalEnvColor(0x55, 0x1A, 0x0D);
            } else {
                i_this->mFollowCb0.getEmitter()->setGlobalEnvColor(0x0D, 0x20, 0x41);
            }
        }
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        a_this->gravity = 0.0f;
        a_this->speed.y = 0.0f;
        i_this->mMode++;
    case 2:
        if (i_this->mFollowCb0.getEmitter() != NULL) {
            i_this->mFollowCb0.getEmitter()->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
        }
        cLib_addCalc2(&a_this->speed.y, 10.0f, 0.8f, 1.0f);
        if (a_this->current.pos.y < 100.0f + i_this->m320) {
            break;
        }
        fire_move_set(i_this);
        a_this->speed.y = 0.0f;
        fopAcM_seStart(a_this, JA_SE_CM_BL_AGO, 0);
        fopAcM_monsSeStart(a_this, JA_SE_CV_BL_ENTER, 0);
        anm_init(i_this, dRes_INDEX_BL_BCK_START02_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mMode++;
        break;
    case 3:
        if (i_this->mpMorf->checkFrame(10.0f)) {
            i_this->mFollowCb0.remove();
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mMode = 5;
        }
        break;
    case 4:
        fire_move_set(i_this);
        fopAcM_OnStatus(a_this, fopAcStts_SHOWMAP_e);
        i_this->mTimers[3] = 5;
        i_this->mMode = 5;
    case 5:
        fopAcM_OnStatus(a_this, fopAcStts_SHOWMAP_e);
        if (i_this->mAnmIdx != dRes_INDEX_BL_BCK_FLY_e) {
            anm_init(i_this, dRes_INDEX_BL_BCK_FLY_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m2D3 = 1;
            i_this->mStts.SetWeight(2);
            i_this->mSph.OnAtSetBit();
            i_this->mSph.OnAtHitBit();
        }
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        if (i_this->mPathIdx != 0xFF && i_this->mpPath != NULL) {
            dPnt* pnt = &i_this->mpPath->m_points[i_this->mPathPntIdx];
            angle = (s16)cM_atan2s(pnt->m_position.x - a_this->current.pos.x, pnt->m_position.z - a_this->current.pos.z);
            a_this->speedF = i_this->m324;
        } else {
            i_this->mTimers[0] = 100.0f + cM_rndFX(50.0f);
            angle = cM_rndFX(32767.0f);
            if (!a_this->speedF) {
                a_this->speedF = 4.0f + cM_rndF(2.0f);
            }
        }
        i_this->m300 = way_check(i_this, angle);
        i_this->mMode++;
    case 6:
        if (i_this->mPathIdx != 0xFF && i_this->mpPath != NULL) {
            dPnt* pnt = &i_this->mpPath->m_points[i_this->mPathPntIdx];
            dx = pnt->m_position.x - a_this->current.pos.x;
            dz = pnt->m_position.z - a_this->current.pos.z;
            angle = (s16)cM_atan2s(dx, dz);
            if (std::sqrtf(dx * dx + dz * dz) < 80.0f + REG8_F(3)) {
                i_this->mPathPntIdx++;
                if (i_this->mPathPntIdx >= i_this->mpPath->m_num) {
                    i_this->mPathPntIdx = 0;
                }
            }
            i_this->mHomePos = a_this->current.pos;
            if (i_this->mTimers[0] == 0) {
                i_this->m300 = way_check(i_this, angle);
                if (i_this->m300 != angle) {
                    i_this->mTimers[0] = 10.0f + cM_rndF(10.0f);
                }
            }
            break;
        } else {
            f32 hx = a_this->current.pos.x - i_this->mHomePos.x;
            f32 hz = a_this->current.pos.z - i_this->mHomePos.z;
            if (std::sqrtf(hx * hx + hz * hz) < 250.0f) {
                if (i_this->mTimers[0] == 0) {
                    i_this->mMode = 5;
                }
                break;
            }
            i_this->mMode = 7;
        }
    case 7: {
        dx = i_this->mHomePos.x - a_this->current.pos.x;
        dz = i_this->mHomePos.z - a_this->current.pos.z;
        i_this->m300 = cM_atan2s(dx, dz);
        f32 limit = 10.0f;
        if (i_this->mPathIdx != 0xFF && i_this->mpPath != NULL) {
            limit = 80.0f;
        }
        if (std::sqrtf(dx * dx + dz * dz) < limit) {
            i_this->mMode = 5;
        }
        break;
    }
    }

    if (i_this->mMode >= 1 && i_this->mMode <= 3) {
        if (i_this->mFollowCb0.getEmitter() != NULL) {
            i_this->mFollowCb0.getEmitter()->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
        }
    }
    if (i_this->mTimers[3] == 0) {
        fire_kaiten_keisan(i_this);
    }
    s16 step1 = 0x120;
    s16 step2 = 0x400;
    if (i_this->mPathIdx != 0xFF && i_this->mpPath != NULL) {
        step1 = 0x1000;
        step2 = 0x1000;
    }
    cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->m300, 1, step1);
    cLib_addCalcAngleS2(&a_this->shape_angle.y, a_this->current.angle.y, 1, step2);
    if (i_this->mMode >= 3) {
        i_this->m31C = 1.5f;
        fuwafuwa_keisan(i_this);
    }
    if (i_this->mType == 1) {
        if (blue_body_atari_check(i_this)) {
            return;
        }
    } else {
        if (red_body_atari_check(i_this)) {
            return;
        }
    }
    if (i_this->mMode >= 5) {
        if (i_this->mSph.ChkAtShieldHit()) {
            if (!(i_this->mPathIdx != 0xFF && i_this->mpPath != NULL) || i_this->mMode != 7) {
                a_this->current.angle.y = fopAcM_searchActorAngleY(a_this, dComIfGp_getPlayer(0)) + 0x8000;
                a_this->speedF = 50.0f;
                i_this->mAction = 1;
                i_this->mMode = 0xA;
            }
        } else if (i_this->m2D3 != 0 && fopAcM_searchActorDistance(a_this, dComIfGp_getPlayer(0)) < 600.0f) {
            if (Line_check(i_this, dComIfGp_getPlayer(0)->current.pos) &&
                (!(i_this->mPathIdx != 0xFF && i_this->mpPath != NULL) || i_this->mMode != 7))
            {
                i_this->mAction = 1;
                i_this->mMode = 0xA;
            }
        }
    }
}


/* 000039F0-00003F68       .text action_kougeki__FP8bl_class */
void action_kougeki(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    switch (i_this->mMode) {
    case 0xA:
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        i_this->mSph.OnAtSetBit();
        i_this->mSph.OnAtHitBit();
        i_this->m304 = 0;
        anm_init(i_this, dRes_INDEX_BL_BCK_HAKKEN_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_monsSeStart(a_this, JA_SE_CV_BL_FOUND, 0);
        a_this->speedF = 0.0f;
        i_this->mMode++;
        break;
    case 0xB:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mMode++;
    case 0xC:
        anm_init(i_this, dRes_INDEX_BL_BCK_ATACK_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_BL_BAS_ATACK_e);
        a_this->speedF = 10.0f;
        i_this->m302 = cM_rndFX(768.0f) * (fopAcM_GetID(a_this) & 3);
        i_this->mMode++;
    case 0xD:
        if (i_this->mPathIdx != 0xFF && i_this->mpPath != NULL) {
            f32 dx = a_this->current.pos.x - i_this->mHomePos.x;
            f32 dz = a_this->current.pos.z - i_this->mHomePos.z;
            if (std::sqrtf(dx * dx + dz * dz) > 700.0f) {
                anm_init(i_this, dRes_INDEX_BL_BCK_FLY_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                a_this->speedF = 4.0f + cM_rndF(2.0f);
                i_this->mAction = 0;
                i_this->mMode = 7;
                return;
            }
        } else if (fopAcM_searchActorDistance(a_this, dComIfGp_getPlayer(0)) > 700.0f) {
            a_this->speedF = 4.0f + cM_rndF(2.0f);
            i_this->mAction = 0;
            i_this->mMode = 5;
            return;
        }
        break;
    case 0xE:
        cLib_addCalc0(&a_this->speedF, 0.5f, 1.0f);
        if (std::fabsf(a_this->speedF) < 0.2f) {
            a_this->speedF = 0.0f;
            anm_init(i_this, dRes_INDEX_BL_BCK_WARAU_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_monsSeStart(a_this, JA_SE_CV_BL_FOUND, 0);
            i_this->mMode = 0xF;
        }
        break;
    case 0xF:
        if (i_this->mpMorf->isStop()) {
            i_this->mMode = 0xC;
        }
        break;
    }

    i_this->mpMorf->setPlaySpeed(1.0f);
    if (i_this->mMode == 0xD && fopAcM_searchActorDistance(a_this, dComIfGp_getPlayer(0)) < 230.0f) {
        i_this->mpMorf->setPlaySpeed(2.0f);
    }
    if (i_this->mSph.ChkAtShieldHit()) {
        if (i_this->mMode != 0xE) {
            a_this->speedF = -20.0f;
            i_this->mAction = 1;
            i_this->mMode = 0xE;
        }
    } else if (i_this->mSph.ChkAtHit()) {
        fopAc_ac_c* hitAc = i_this->mSph.GetAtHitAc();
        if (hitAc != NULL && hitAc == player && i_this->mMode != 0xF) {
            anm_init(i_this, dRes_INDEX_BL_BCK_OOWARAI_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_monsSeStart(a_this, JA_SE_CV_BL_SUCCESS, 0);
            a_this->speedF = 0.0f;
            i_this->m2F8[0] = 0;
            i_this->mMode = 0xF;
        }
    }
    fire_kaiten_keisan(i_this);
    i_this->m300 = i_this->m302 + fopAcM_searchActorAngleY(a_this, dComIfGp_getPlayer(0));
    cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->m300, 1, 0x1000);
    cLib_addCalcAngleS2(&a_this->shape_angle.y, a_this->current.angle.y, 1, 0x400);
    if (i_this->mMode >= 0xC) {
        fuwafuwa_keisan(i_this);
    }
    if (i_this->mType == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}


/* 00003F68-00004128       .text action_sagarimasu__FP8bl_class */
void action_sagarimasu(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    switch (i_this->mMode) {
    case 0x14:
        anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        a_this->speedF = 20.0f + REG8_F(10);
        if (i_this->m2D4 == 4 || i_this->m2D4 == 5) {
            a_this->speedF = 60.0f + REG8_F(11);
            if (i_this->m2D4 == 5) {
                a_this->current.angle.y = player->shape_angle.y - 0x4000;
            }
        }
        i_this->mMode++;
    case 0x15:
        cLib_addCalc0(&a_this->speedF, 0.8f, 5.0f);
        if (a_this->speedF < 0.1f) {
            i_this->mAction = 1;
            i_this->mMode = 0xA;
            if (i_this->m2D3 != 0 && i_this->mType == 0 && a_this->health <= 0) {
                cXyz pos = a_this->current.pos;
                pos.y += 30.0f;
                fopAcM_createDisappear(a_this, &pos, 5, daDisItem_IBALL_e);
                a_this->attention_info.flags = 0;
                fopAcM_onActor(a_this);
                fopAcM_delete(a_this);
            }
        }
        break;
    }

    fire_kaiten_keisan(i_this);
    if (i_this->mType == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}


/* 00004128-000046BC       .text action_kaze_move__FP8bl_class */
void action_kaze_move(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    cXyz offset;
    cXyz rot;

    switch (i_this->mMode) {
    case 0x1E:
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->mSph.SetTgSe(dCcG_SE_NONE);
        i_this->mSph.SetTgHitMark(dCcG_TgHitMark_None_e);
        i_this->mSph.OffTgShield();
        i_this->mSph.OffAtSetBit();
        i_this->mSph.OffAtSetBit();
        a_this->speedF = 15.0f;
        i_this->m310 = 7.0f;
        i_this->m2F8[0] = 512.0f + cM_rndF(500.0f);
        if (cM_rnd() < 0.5f) {
            i_this->m2F8[0] *= -1;
        }
        if (i_this->mAnmIdx != dRes_INDEX_BL_BCK_UCHIWA_e) {
            anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        i_this->mTimers[2] = 0;
        fire_emitter_clr(i_this);
        fopAcM_seStart(a_this, JA_SE_CM_BL_WIND_HIT, 0);
        fopAcM_monsSeStart(a_this, JA_SE_CV_BL_DAMAGE, 0);
        i_this->mMode++;
    case 0x1F:
        a_this->shape_angle.z += i_this->m2F8[0];
        cLib_addCalc2(&a_this->speed.y, i_this->m310, 0.8f, 2.0f);
        cLib_addCalc0(&a_this->speedF, 0.8f, 3.0f);
        if (a_this->speedF > 0.1f) {
            break;
        }
        i_this->mMode++;
    case 0x20:
        i_this->m2D3 = 0;
        a_this->speedF = 0.0f;
        i_this->mMode++;
    case 0x21:
        cLib_addCalc2(&a_this->gravity, -3.0f, 0.8f, 0.1f);
        cLib_addCalcAngleS2(&a_this->shape_angle.x, -0x7FFF, 1, 0x120);
        if (!i_this->mAcch.ChkGroundHit()) {
            break;
        }
        i_this->mMode++;
    case 0x22:
        a_this->speed.y = 15.0f;
        a_this->gravity = -3.0f;
        bound_sound_set(i_this);
        i_this->mMode++;
    case 0x23:
        cLib_addCalcAngleS2(&a_this->shape_angle.x, 0, 1, 0x400);
        cLib_addCalcAngleS2(&a_this->shape_angle.z, 0, 1, 0x400);
        if (abs(a_this->shape_angle.x) < 0x100 && abs(a_this->shape_angle.z) < 0x100) {
            a_this->shape_angle.x = 0;
            a_this->shape_angle.z = 0;
            if (i_this->mType & 0x80) {
                i_this->mAction = 0xA;
                i_this->mMode = 0x64;
            } else {
                i_this->mMode = 0x26;
            }
        }
        break;
    case 0x24: {
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        a_this->speed.y = 15.0f;
        a_this->gravity = -3.0f;
        bound_sound_set(i_this);
        if (!(i_this->mType & 0x80)) {
            a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        }
        i_this->mSph.OffAtSetBit();
        i_this->mSph.OffAtSetBit();
        a_this->speedF = 30.0f;
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 5000.0f;
        s16 angle = fopAcM_searchActorAngleY(a_this, dComIfGp_getPlayer(0));
        mDoMtx_YrotS(*calc_mtx, angle + 0x8000);
        MtxPosition(&offset, &rot);
        i_this->m2F8[0] = -rot.x;
        i_this->m2F8[1] = rot.z;
        i_this->mStts.SetWeight(0x50);
        i_this->mMode++;
    }
    case 0x25:
        a_this->shape_angle.x += i_this->m2F8[0];
        a_this->shape_angle.z += i_this->m2F8[1];
        if (a_this->speedF < 5.0f) {
            if (roll_check(i_this)) {
                if (i_this->mType & 0x80) {
                    i_this->mAction = 0xA;
                    i_this->mMode = 0x64;
                } else {
                    i_this->mMode = 0x26;
                }
            }
        } else if (i_this->mAcch.ChkGroundHit()) {
            i_this->m2F8[2] = 1;
            a_this->speed.y = 10.0f;
            bound_sound_set(i_this);
        }
        if (i_this->m2F8[2] != 0) {
            cLib_addCalc0(&a_this->speedF, 0.8f, 1.0f);
        }
        break;
    case 0x26:
        i_this->mTimers[1] = 70.0f + cM_rndF(35.0f);
        a_this->speedF = 0.0f;
        i_this->mMode++;
    case 0x27:
        if (i_this->mTimers[1] == 0) {
            anm_init(i_this, dRes_INDEX_BL_BCK_START01_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            a_this->speedF = 0.0f;
            a_this->current.angle.y = a_this->shape_angle.y;
            i_this->mAction = 0;
            i_this->mMode = 1;
        }
        break;
    }
    i_this->mFollowCb0.remove();
    i_this->m31C = 1.0f;
    if (i_this->mType & 0x80) {
        skull_atari_check(i_this);
    } else if (i_this->mType == 1) {
        blue_body_atari_check(i_this);
    } else {
        red_body_atari_check(i_this);
    }
}


/* 000046BC-00004B84       .text action_itaiyo_ne_san__FP8bl_class */
void action_itaiyo_ne_san(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz offset;
    cXyz rot;

    switch (i_this->mMode) {
    case 0x28: {
        i_this->m31C = 1.0f;
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        a_this->gravity = -3.0f;
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->mSph.OffAtSetBit();
        i_this->mSph.OffAtSetBit();
        if (i_this->mAnmIdx != dRes_INDEX_BL_BCK_UCHIWA_e) {
            anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        i_this->mTimers[2] = 0;
        fire_emitter_clr(i_this);
        offset.x = 0.0f;
        offset.y = 0.0f;
        if (a_this->health <= 0) {
            if (i_this->m2D4 == 4) {
                i_this->mTimers[0] = 0;
            } else {
                i_this->mTimers[0] = 50;
                i_this->m310 = 30.0f;
                a_this->speed.y = 30.0f;
                a_this->speedF = 20.0f;
                offset.z = 5000.0f;
                if (i_this->m2D4 == 5) {
                    a_this->current.angle.y = player->shape_angle.y - 0x4000;
                }
                bound_sound_set(i_this);
            }
            a_this->attention_info.flags = 0;
            i_this->mMode = 0x2A;
        } else {
            i_this->mMode = 0x29;
            a_this->speed.y = 15.0f;
            a_this->speedF = 10.0f;
            offset.z = 5000.0f;
            bound_sound_set(i_this);
        }
        s16 angle = fopAcM_searchActorAngleY(a_this, dComIfGp_getPlayer(0));
        mDoMtx_YrotS(*calc_mtx, angle + 0x8000);
        MtxPosition(&offset, &rot);
        i_this->m2F8[0] = -rot.x;
        i_this->m2F8[1] = rot.z;
        break;
    }
    case 0x29:
        if (a_this->speedF < 0.1f && roll_check(i_this)) {
            i_this->mAction = 3;
            i_this->mMode = 0x26;
        }
        cLib_addCalc0(&a_this->speedF, 0.8f, 1.0f);
        if (i_this->mType == 1) {
            blue_body_atari_check(i_this);
        } else {
            red_body_atari_check(i_this);
        }
        break;
    case 0x2A:
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->m310 *= 0.5f;
            if (i_this->m310 < 10.0f) {
                i_this->m310 = 10.0f;
            }
            a_this->speed.y = i_this->m310;
            bound_sound_set(i_this);
            if (i_this->mTimers[0] == 0) {
                cXyz pos = a_this->current.pos;
                pos.y += 30.0f;
                fopAcM_createDisappear(a_this, &pos, 5, 0);
                if (i_this->m2D4 == 4) {
                    cXyz pos2 = a_this->current.pos;
                    pos2.y += 25.0f + REG8_F(2);
                    JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_IT_JN_DOKURO00, &pos2, &a_this->current.angle, &a_this->scale, 0xFF, NULL,
                                                                    fopAcM_GetRoomNo(a_this), &a_this->tevStr.mColorK0, &a_this->tevStr.mColorK0);
                    if (emitter != NULL) {
                        emitter->setAwayFromAxisSpeed(30.0f);
                        emitter->setDirectionalSpeed(20.0f);
                    }
                    i_this->m698[3] = pos2;
                    smoke_set(i_this);
                    i_this->mSph.OffTgSetBit();
                    i_this->mSph.OffCoSetBit();
                    i_this->mSph.ClrTgHit();
                    a_this->scale.setall(0.0f);
                    i_this->m31C = 0.0f;
                    i_this->m2F8[2] = 0xB4;
                    i_this->mTimers[1] = 10;
                    i_this->mMode++;
                } else {
                    fopAcM_onActor(a_this);
                    fopAcM_delete(a_this);
                }
            }
        }
        break;
    case 0x2B:
        if (i_this->mSmokeCb.getEmitter() != NULL) {
            if (i_this->mTimers[1] == 0) {
                i_this->mSmokeCb.getEmitter()->setGlobalAlpha(i_this->m2F8[2]);
                i_this->m2F8[2] -= 4;
                if (i_this->m2F8[2] < 0) {
                    i_this->mSmokeCb.remove();
                }
            }
        } else {
            fopAcM_onActor(a_this);
            fopAcM_delete(a_this);
        }
        break;
    }
    a_this->shape_angle.x += i_this->m2F8[0];
    a_this->shape_angle.z += i_this->m2F8[1];
}


/* 00004B84-00004D3C       .text action_hook_atari__FP8bl_class */
void action_hook_atari(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    switch (i_this->mMode) {
    case 0x3C:
        for (int i = 0; i < 4; i++) {
            i_this->m2F8[i] = 0;
        }
        if (i_this->mFollowCb1.getEmitter() != NULL) {
            i_this->mTimers[2] = 0;
            fire_emitter_clr(i_this);
            anm_init(i_this, dRes_INDEX_BL_BCK_UCHIWA_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mSph.OffAtSetBit();
            i_this->mSph.OffAtSetBit();
            a_this->speedF = 0.0f;
            fopAcM_seStart(a_this, JA_SE_CM_BL_WIND_HIT, 0);
            fopAcM_monsSeStart(a_this, JA_SE_CV_BL_DAMAGE, 0);
        }
        fopAcM_OnStatus(a_this, fopAcStts_SHOWMAP_e);
        i_this->mSph.SetTgSe(0);
        i_this->mSph.SetTgHitMark((CcG_Tg_HitMark)0);
        i_this->mSph.OffTgShield();
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->mMode++;
        break;
    case 0x3D:
        if (!fopAcM_checkHookCarryNow(a_this)) {
            i_this->mAction = 3;
            i_this->mMode = 0x20;
        }
        break;
    }
    i_this->mFollowCb0.remove();
}


/* 00004D3C-00004DBC       .text action_come_wait__FP8bl_class */
void action_come_wait(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    switch (i_this->mMode) {
    case 0x46:
        if (i_this->mSwitchNo != 0xFF && dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
            fopAcM_OnStatus(a_this, fopAcStts_SHOWMAP_e);
            i_this->mAction = 3;
            i_this->mMode = 0x26;
        }
        break;
    }
}


/* 00004DBC-00005104       .text action_normal_skull__FP8bl_class */
void action_normal_skull(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    cXyz pos = a_this->current.pos;

    switch (i_this->mMode) {
    case 0x64:
        i_this->m328 = 30.0f + REG8_F(7);
        a_this->gravity = -3.0f;
        if (!fopAcM_checkCarryNow(a_this)) {
            break;
        }
        a_this->gravity = 0.0f;
        i_this->mSph.OffCoSetBit();
        i_this->mMode++;
    case 0x65:
        if (!fopAcM_checkCarryNow(a_this)) {
            i_this->mSph.OnCoSetBit();
            a_this->gravity = -3.0f;
            if (a_this->speedF > 0.0f) {
                a_this->speed.y = 25.0f;
                a_this->speedF = 35.0f;
                i_this->mMode = 0x66;
            } else {
                a_this->speedF = 0.0f;
                a_this->speed.x = 0.0f;
                a_this->speed.y = 0.0f;
                a_this->speed.z = 0.0f;
                a_this->gravity = -3.0f;
                i_this->mMode = 0x64;
            }
        }
        break;
    case 0x66:
        if (i_this->mAcch.ChkGroundHit() || i_this->mAcch.ChkWallHit()) {
            a_this->speed.x = 0.0f;
            a_this->speed.y = 0.0f;
            a_this->speed.z = 0.0f;
            if (i_this->mEnemyFire.mFireDuration == 0) {
                a_this->speedF = 0.0f;
                a_this->health = 0;
                a_this->attention_info.flags = 0;
                i_this->mMode = 0x68;
            }
        }
        break;
    case 0x67:
        bound_sound_set(i_this);
        i_this->mMode = 0x66;
        break;
    case 0x68: {
        pos.y += 25.0f + REG8_F(2);
        JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_IT_JN_DOKURO00, &pos, &a_this->current.angle, &a_this->scale, 0xFF, NULL,
                                                        fopAcM_GetRoomNo(a_this), &a_this->tevStr.mColorK0, &a_this->tevStr.mColorK0);
        if (emitter != NULL) {
            emitter->setAwayFromAxisSpeed(30.0f);
            emitter->setDirectionalSpeed(20.0f);
        }
        i_this->m698[3] = pos;
        smoke_set(i_this);
        for (int i = 0; i < (int)cM_rndF(1.99f); i++) {
            fopAcM_createItem(&a_this->current.pos, 0, -1, -1, 0, NULL, 4);
        }
        i_this->mSph.OffTgSetBit();
        i_this->mSph.OffCoSetBit();
        i_this->mSph.ClrTgHit();
        i_this->m31C = 0.0f;
        a_this->scale.setall(0.0f);
        i_this->m2F8[3] = 0xB4;
        i_this->mTimers[1] = 10;
        i_this->mMode++;
        break;
    }
    case 0x69:
        if (i_this->mSmokeCb.getEmitter() != NULL) {
            if (i_this->mTimers[1] == 0) {
                i_this->mSmokeCb.getEmitter()->setGlobalAlpha(i_this->m2F8[3]);
                i_this->m2F8[3] -= 4;
                if (i_this->m2F8[3] < 0) {
                    i_this->mSmokeCb.remove();
                }
            }
        } else {
            fopAcM_delete(a_this);
        }
        break;
    }
    i_this->m314 = 24.0f;
    skull_atari_check(i_this);
}


/* 00005104-00005504       .text daBL_Execute__FP8bl_class */
static BOOL daBL_Execute(bl_class* i_this) {
    fopAc_ac_c* a_this = i_this;

    if (i_this->mTimers[2] == 1) {
        i_this->mFollowCb1.remove();
    }
    if (i_this->mTimers[5] == 1) {
        fopAcM_OffStatus(a_this, fopAcStts_UNK4000_e);
    }
    a_this->eyePos = a_this->current.pos;
    a_this->attention_info.position = a_this->current.pos;
    a_this->eyePos.y += 40.0f;
    a_this->attention_info.position.y += 80.0f;

    if (!(i_this->mType & 0x80)) {
        if (i_this->m2D3 == 0) {
            i_this->mpBtkOff->play();
        } else {
            i_this->mpBtkOn->play();
        }
    }

    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpMorf->calc();
        if (i_this->mTimers[2] != 0) {
            i_this->mTimers[2]--;
        }
        return TRUE;
    }

    for (int i = 0; i < 6; i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }

    switch (i_this->mAction) {
    case 0:
        action_dousa(i_this);
        break;
    case 1:
        action_kougeki(i_this);
        break;
    case 2:
        action_sagarimasu(i_this);
        break;
    case 3:
        action_kaze_move(i_this);
        break;
    case 4:
        action_itaiyo_ne_san(i_this);
        break;
    case 5:
        action_hook_atari(i_this);
        break;
    case 6:
        action_come_wait(i_this);
        break;
    case 10:
        action_normal_skull(i_this);
        break;
    }

    if (i_this->mMode != 0) {
        s8 roomNo = fopAcM_GetRoomNo(a_this);
        u32 mtrlSndId;
        if (i_this->mAcch.ChkGroundHit()) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd);
        } else {
            mtrlSndId = 0;
        }
        i_this->mpMorf->play(&a_this->eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
    }

    mDoMtx_YrotS(*calc_mtx, a_this->current.angle.y);
    cXyz offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = a_this->speedF;
    cXyz vel;
    MtxPosition(&offset, &vel);
    a_this->speed.x = vel.x;
    a_this->speed.z = vel.z;
    a_this->speed.y += a_this->gravity;
    if (a_this->speed.y < -55.0f) {
        a_this->speed.y = -55.0f;
    }

    cLib_addCalc2(&a_this->scale.x, i_this->m31C, 0.3f, 0.3f);
    a_this->scale.y = a_this->scale.z = a_this->scale.x;

    cXyz center = a_this->current.pos;
    center.y += 20.0f;
    i_this->mSph.SetC(center);
    i_this->mSph.SetR(i_this->m328);
    dComIfG_Ccsp()->Set(&i_this->mSph);

    if (i_this->mSph.ChkCoSet()) {
        fopAcM_posMove(a_this, i_this->mStts.GetCCMoveP());
    } else {
        fopAcM_posMove(a_this, NULL);
    }
    BG_check(i_this);

    if ((i_this->m2D1 == 0 || a_this->gravity) &&
        i_this->mAcch.GetGroundH() != -G_CM3D_F_INF &&
        dComIfG_Bgsp()->ChkPolySafe(i_this->mAcch.m_gnd) &&
        dComIfG_Bgsp()->GetGroundCode(i_this->mAcch.m_gnd) == 4 &&
        a_this->current.pos.y < i_this->m320 - 500.0f)
    {
        a_this->speedF = 0.0f;
        a_this->speed.setall(0.0f);
        a_this->gravity = 0.0f;
        fopAcM_onActor(a_this);
        fopAcM_delete(a_this);
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
    i_this->mFollowCb0.remove();
    i_this->mFollowCb1.remove();
    i_this->mSmokeCb.remove();
    enemy_fire_remove(&i_this->mEnemyFire);
    dComIfG_resDelete(&i_this->mPhs, "BL");
    return TRUE;
}


/* 0000558C-0000583C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    bl_class* i_this = (bl_class*)a_this;
    J3DModel* model;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BDL_BL_e),
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BCK_START01_e),
        J3DFrameCtrl::EMode_RESET, 0.0f, 0, -1, 1,
        NULL,
        0x80000, 0x37441422
    );
    if (i_this->mpMorf == NULL || (model = i_this->mpMorf->getModel()) == NULL) {
        return FALSE;
    }

    i_this->mpBtkOn = new mDoExt_btkAnm();
    if (i_this->mpBtkOn == NULL) {
        return FALSE;
    }
    if (!i_this->mpBtkOn->init(model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BTK_ON_e), true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    if (i_this->mpBtkOn == NULL) {
        return FALSE;
    }

    i_this->mpBtkOff = new mDoExt_btkAnm();
    if (i_this->mpBtkOff == NULL) {
        return FALSE;
    }
    if (!i_this->mpBtkOff->init(model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("BL", dRes_INDEX_BL_BTK_OFF_e), true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    if (i_this->mpBtkOff == NULL) {
        return FALSE;
    }

    i_this->mpMorf->getModel()->setUserArea((uintptr_t)i_this);
    if (!i_this->mInvisibleModel.create(i_this->mpMorf->getModel())) {
        return FALSE;
    }
    return TRUE;
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
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
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
    static s8 fire_j[] = {
        0, 1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    static f32 fire_sc[] = {
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };

    bl_class* i_this = (bl_class*)a_this;

    fopAcM_ct(a_this, bl_class);

    cPhs_State ret = dComIfG_resLoad(&i_this->mPhs, "BL");
    if (ret == cPhs_COMPLEATE_e) {
        i_this->mType = fopAcM_GetParam(a_this);
        i_this->m2D1 = fopAcM_GetParam(a_this) >> 24;
        i_this->mPathIdx = fopAcM_GetParam(a_this) >> 16;
        i_this->mSwitchNo = fopAcM_GetParam(a_this) >> 8;
        i_this->m324 = a_this->current.angle.z;
        a_this->current.angle.z = 0;
        a_this->shape_angle.z = 0;
        if (i_this->mType == 0xFF) {
            i_this->mType = 0;
        }
        if (i_this->m2D1 == 0xFF) {
            i_this->m2D1 = 0;
        }
        if (REG8_S(8) != 0) {
            i_this->m2D1 = 1;
        }
        if (REG8_S(9) != 0) {
            i_this->mType = REG8_S(9) - 1;
        }

        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x14E0)) {
            return cPhs_ERROR_e;
        }

        if (i_this->mType & 2) {
            i_this->mType ^= 2;
            if (i_this->mPathIdx != 0xFF) {
                i_this->mpPath = dPath_GetRoomPath(i_this->mPathIdx, fopAcM_GetRoomNo(a_this));
                if (i_this->m324 < 4.0f) {
                    i_this->m324 = 4.0f + cM_rndF(2.0f);
                }
            }
            if (REG8_S(9) != 0) {
                i_this->mPathIdx = 0;
                i_this->mpPath = dPath_GetRoomPath(i_this->mPathIdx, fopAcM_GetRoomNo(a_this));
            }
        }

        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        a_this->attention_info.flags = 0;
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this),
                          a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mStts.Init(0x50, 1, a_this);
        a_this->max_health = 2;
        a_this->health = 2;

        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mWallRadius = 50.0f;
        i_this->mEnemyIce.mCylHeight = 50.0f;
        i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
        i_this->mEnemyFire.mpActor = a_this;
        for (int i = 0; i < 10; i++) {
            i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }

        i_this->m328 = 50.0f;
        i_this->m300 = a_this->shape_angle.y;
        i_this->mSph.Set(body_co_sph_src);
        i_this->mSph.SetStts(&i_this->mStts);
        i_this->mSph.OffAtSetBit();
        i_this->mSph.OffAtSetBit();

        a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x29;
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("bable_r", 0);
        a_this->gbaName = 0xE;
        if (i_this->mType == 1) {
            i_this->mSph.SetAtSpl(dCcG_At_Spl_UNK3);
            i_this->mSph.SetAtType(AT_TYPE_UNK800);
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
        i_this->mHomePos = a_this->current.pos;
        fopAcM_posMove(a_this, i_this->mStts.GetCCMoveP());
        BG_check(i_this);
        i_this->m320 = a_this->current.pos.y;
        if (i_this->m2D1 == 0) {
            i_this->m320 = i_this->mAcch.GetGroundH();
        }

        i_this->mAction = 0;
        if (!i_this->mAcch.ChkGroundHit()) {
            a_this->scale.setall(0.0f);
            a_this->gravity = 0.0f;
            a_this->speed.y = 0.0f;
            a_this->current.pos.y = 100.0f + i_this->m320;
            i_this->mMode = 4;
        } else {
            i_this->mMode = 0;
        }

        if (i_this->mSwitchNo != 0xFF && !dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
            fopAcM_OffStatus(a_this, fopAcStts_SHOWMAP_e);
            i_this->mAction = 6;
            i_this->mMode = 0x46;
        }

        if (i_this->mType & 0x80) {
            a_this->max_health = 1;
            a_this->health = 1;
            i_this->m2D3 = 1;
            i_this->mSph.OnCoSetBit();
            a_this->current.angle.y = cM_rndFX(32767.0f);
            a_this->shape_angle.y = a_this->current.angle.y;
            fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
            i_this->mTimers[5] = 4;
            fopAcM_OffStatus(a_this, fopAcStts_SHOWMAP_e);
            a_this->attention_info.flags |= fopAc_Attn_ACTION_CARRY_e;
            i_this->mAction = 0xA;
            i_this->mMode = 0x64;
        } else {
            a_this->stealItemLeft = 1;
            i_this->m2EA = a_this->stealItemLeft;
        }

        draw_SUB(i_this);
    }

    return ret;
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
