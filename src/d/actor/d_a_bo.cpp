/**
 * d_a_bo.cpp
 * Enemy - Boko Baba
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bo.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/d_cc_uty.h"
#include "d/d_material.h"
#include "d/d_camera.h"
#include "d/actor/d_a_player_main.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_controller_pad.h"

static s16 pl_cut_real_no_dt[32] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

static u8 nokezoru_on_off_dt[32] = {
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1,
};

/* 000000EC-000001E8       .text smoke_set__FP8bo_class */
static void smoke_set(bo_class* i_this) {
    GXColor color = {0xA0, 0xA0, 0x80, 0xFF};
    i_this->mSmoke.remove();
    dComIfGp_particle_setToon(0x2027, &i_this->m39C, &i_this->shape_angle, NULL, 0xB9, &i_this->mSmoke, fopAcM_GetRoomNo(i_this));
    JPABaseEmitter* emitter = i_this->mSmoke.getEmitter();
    if (emitter != NULL) {
        JGeometry::TVec3<f32> scale(3.0f, 3.0f, 3.0f);
        emitter->setGlobalParticleScale(scale);
        emitter->setRate(30.0f);
        emitter->setMaxFrame(1);
        emitter->setAwayFromCenterSpeed(10.0f);
        emitter->setAwayFromAxisSpeed(10.0f);
        emitter->setStatus(0x40);
        i_this->mSmoke.setColor(color);
    }
}

/* 000001E8-00000638       .text nodeCallBack_UP__FP7J3DNodei */
static BOOL nodeCallBack_UP(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        int jntNo = ((J3DJoint*)node)->getJntNo();
        BOOL changed = FALSE;
        J3DModel* model = j3dSys.getModel();
        bo_class* i_this = (bo_class*)model->getUserArea();
        if (i_this != NULL) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            cXyz zero;
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo <= 10) {
                f32 f = 0.025f * jntNo;
                cMtx_YrotM(*calc_mtx, i_this->m33C * f);
                cMtx_XrotM(*calc_mtx, i_this->m33A * f);
                cMtx_ZrotM(*calc_mtx, i_this->m33E * f);
                changed = TRUE;
            }
            if (jntNo == 1) {
                zero.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m2F8);
                changed = TRUE;
            }
            if (jntNo == 10) {
                zero.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m328);
                changed = TRUE;
            }
            if (jntNo == 11) {
                zero.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m2E0);
                changed = TRUE;
            }
            if (jntNo == 4) {
                zero.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m310);
                changed = TRUE;
            }
            if (jntNo >= 5 && jntNo <= 7) {
                s16 k = 8 - jntNo;
                f32 f = 1.75f;
                f = k * f;
                cMtx_YrotM(*calc_mtx, i_this->m354 * f);
                cMtx_ZrotM(*calc_mtx, i_this->m356 * f);
                changed = TRUE;
            }
            if (jntNo == 8) {
                cMtx_YrotM(*calc_mtx, i_this->m336 + REG12_S(3));
                cMtx_XrotM(*calc_mtx, i_this->m338 + REG12_S(5));
                zero.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m31C);
                changed = TRUE;
            }
            if (jntNo == 12 && i_this->m2CC) {
                zero.set(0.0f, 0.0f, 0.0f);
                cXyz pos;
                MtxPosition(&zero, &pos);
                f32 dx = i_this->m31C.x - pos.x;
                f32 dz = i_this->m31C.z - pos.z;
                csXyz angle;
                if (i_this->m2CD) {
                    angle.x = -0x5FB4;
                    angle.y = cM_atan2s(dx, dz) + 0x7FFF;
                    angle.z = 0;
                    player->setPlayerPosAndAngle(&pos, &angle);
                } else {
                    angle.x = 0x5BCC;
                    angle.y = cM_atan2s(dx, dz);
                    angle.z = 0;
                    player->setPlayerPosAndAngle(&pos, &angle);
                }
                changed = TRUE;
            }
            if (changed) {
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
        int jntNo = ((J3DJoint*)node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bo_class* i_this = (bo_class*)model->getUserArea();
        if (i_this != NULL && jntNo == 9) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz zero(0.0f, 0.0f, 0.0f);
            MtxPosition(&zero, &i_this->m304);
        }
    }
    return TRUE;
}

/* 000006C8-0000079C       .text execute__22yodare_ato_PcallBack_cFP14JPABaseEmitterP15JPABaseParticle */
void yodare_ato_PcallBack_c::execute(JPABaseEmitter*, JPABaseParticle* ptcl) {
    JGeometry::TVec3<f32> ptclPos;
    ptcl->getGlobalPosition(ptclPos);
    cXyz pos(ptclPos.x, ptclPos.y + 20.0f, ptclPos.z);
    mGndChk.SetPos(&pos);
    pos.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (pos.y > ptclPos.y) {
        dComIfGp_particle_set(0x8108, &pos);
    }
}

/* 0000079C-00000930       .text draw_SUB__FP8bo_class */
static void draw_SUB(bo_class* i_this) {
    if (i_this->mType == 0 || i_this->mType == 2) {
        if (i_this->mType == 2) {
            i_this->m304 = i_this->current.pos;
            i_this->mpBrk->play();
        }
        mDoMtx_stack_c::transS(i_this->m304.x, i_this->m304.y + i_this->m394, i_this->m304.z);
        mDoMtx_stack_c::YrotM(i_this->m348);
        mDoMtx_stack_c::XrotM(i_this->shape_angle.x);
        mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);
        mDoMtx_stack_c::transM(0.0f, -i_this->m394, 0.0f);
        i_this->mpUpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpUpMorf->calc();
        if (i_this->mType == 0) {
            enemy_fire(&i_this->mEnemyFire);
        }
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        mDoMtx_stack_c::transS(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z);
        mDoMtx_stack_c::YrotM(i_this->current.angle.y);
        mDoMtx_stack_c::XrotM(i_this->shape_angle.x);
        mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);
        i_this->mpDwMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpDwMorf->calc();
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
}

/* 00000930-00000AD4       .text daBO_Draw__FP8bo_class */
static BOOL daBO_Draw(bo_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    if (REG13_S(5) != 0) {
        return TRUE;
    }
    bool iced = false;
    if (i_this->mType == 0 || i_this->mType == 2) {
        g_env_light.setLightTevColorType(i_this->mpUpMorf->getModel(), &a_this->tevStr);
    }
    if ((i_this->mType == 0 || i_this->mType == 1) && i_this->mEnemyIce.mLightShrinkTimer == 0) {
        g_env_light.setLightTevColorType(i_this->mpDwMorf->getModel(), &a_this->tevStr);
    }
    dSnap_RegistFig(DSNAP_TYPE_UNKB2, a_this, a_this->current.pos, i_this->m348, 1.0f, 1.0f, 1.0f);
    if (i_this->mType == 0 && i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(i_this->mpUpMorf, -1, &i_this->mInvisModel);
        iced = true;
    }
    if (!iced && (i_this->mType == 0 || i_this->mType == 2)) {
        J3DModel* model = i_this->mpUpMorf->getModel();
        if (i_this->mType == 2) {
            i_this->mpBrk->entry(model->getModelData());
        }
        i_this->mpUpMorf->entryDL();
        if (i_this->mType == 2) {
            i_this->mpBrk->remove(model->getModelData());
        }
    }
    if ((i_this->mType == 0 || i_this->mType == 1) && i_this->mEnemyIce.mLightShrinkTimer == 0) {
        i_this->mpDwMorf->entryDL();
    }
    return TRUE;
}

/* 00000AD4-00000CD4       .text anm_init__FP8bo_classifUcfii */
static void anm_init(bo_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx, int which) {
    i_this->mAnmIdx = bckFileIdx;
    if (which == 0) {
        if (soundFileIdx >= 0) {
            i_this->mpUpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("BO", soundFileIdx));
        } else {
            i_this->mpUpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    } else {
        if (soundFileIdx >= 0) {
            i_this->mpDwMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("BO", soundFileIdx));
        } else {
            i_this->mpDwMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BO", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    }
}

/* 00000CD4-00000E24       .text shock_damage_check__FP8bo_class */
static BOOL shock_damage_check(bo_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (player->checkResetFlg0(daPy_py_c::daPyRFlg0_HAMMER_QUAKE)) {
        cXyz delta = player->getSwordTopPos();
        delta.x -= i_this->current.pos.x;
        delta.z -= i_this->current.pos.z;
        if (std::sqrtf(delta.x * delta.x + delta.z * delta.z) < 1000.0f) {
            fopAcM_seStart(i_this, 0x2855, 0x31);
            return TRUE;
        }
    }
    return FALSE;
}

/* 00000E24-000013A4       .text head_atari_check__FP8bo_class */
static inline u32 make_bo_prm(u8 a) { return (a << 8) | 1; }

static BOOL head_atari_check(bo_class* i_this) {
    fopAc_ac_c* a_this = i_this;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if (i_this->m366[4] != 0) {
        return FALSE;
    }
    if (shock_damage_check(i_this)) {
        i_this->m2CA = 1;
        return TRUE;
    }
    if (!i_this->mHeadSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mHeadSph.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    i_this->m358 = *i_this->mHeadSph.GetTgHitPosP();
    i_this->m366[4] = 8.0f + REG8_F(10);
    i_this->m370 = cM_atan2s(player->current.pos.x - i_this->m2E0.x, player->current.pos.z - i_this->m2E0.z);
    i_this->m2CA = 0;
    i_this->m364 = 0;
    i_this->m2CA = 1;
    mDoAud_onEnemyDamage();

    switch (hitObj->GetAtType()) {
    case AT_TYPE_GRAPPLING_HOOK: {
        if (i_this->stealItemLeft > 0) {
            u8 health = i_this->health;
            i_this->health = 10;
            CcAtInfo atInfo;
            atInfo.mpObj = i_this->mHeadSph.GetTgHitObj();
            atInfo.pParticlePos = NULL;
            cc_at_check(a_this, &atInfo);
            i_this->health = health;
        }
        dComIfGp_particle_set(0x27B, &i_this->attention_info.position);
        i_this->m2CA = 0;
        mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(a_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(a_this)));
        fopAcM_seStart(a_this, 0x2836, 0x20);
        break;
    }
    case AT_TYPE_SWORD: {
        int i;
        for (i = 0; i < 32; i++) {
            if (pl_cut_real_no_dt[i] == player->getCutType()) {
                break;
            }
        }
        if (i >= 32) {
            return FALSE;
        }
        i_this->m2CA = nokezoru_on_off_dt[i];
        break;
    }
    case AT_TYPE_BOOMERANG: {
        i_this->m2CA = 1;
        i_this->m364 = (u8)(REG8_S(5) + 5);
        i_this->mHeadSph.OffAtSetBit();
        i_this->mHeadSph.OffAtSetBit();
        i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);

        i_this->attention_info.flags &= ~fopAc_Attn_LOCKON_BATTLE_e;
        i_this->m398 = 1.0f;
        dComIfGp_particle_set(0x10, &i_this->m358);
        cXyz scale(2.0f, 2.0f, 2.0f);
        dComIfGp_particle_set(0xF, &i_this->m358, &player->shape_angle, &scale);
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(a_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(a_this)));
        fopAcM_seStart(a_this, 0x2828, 0x20);
        break;
    }
    case AT_TYPE_FIRE:
    case AT_TYPE_FIRE_ARROW:
        i_this->mEnemyFire.mFireDuration = 34.0f + REG8_F(12);
        i_this->m2D0 = 1;
        i_this->attention_info.flags = 0;
        break;
    case AT_TYPE_ICE_ARROW:
        i_this->mEnemyIce.mFreezeDuration = 80.0f + REG8_F(13);
        i_this->m2D0 = 2;
        i_this->mEnemyIce.m00C = 1;
        i_this->attention_info.flags = 0;
        i_this->health = 30;
        break;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 80.0f + REG8_F(13);
        i_this->attention_info.flags = 0;
        i_this->m2D0 = 3;
        fopAcM_create(fpcNm_BO_e, make_bo_prm(i_this->m2C1), &i_this->current.pos, fopAcM_GetRoomNo(a_this), &i_this->current.angle, &i_this->scale, 0);
        break;
    case AT_TYPE_SKULL_HAMMER:
        if (player->getCutType() != 0x11) {
            i_this->m2CA = 2;
            break;
        }
    default:
        i_this->m2CA = 1;
        break;
    }
    return TRUE;
}

/* 000013A4-0000164C       .text nokezori_damage_rtn__FP8bo_class */
static void nokezori_damage_rtn(bo_class* i_this) {
    s16 angle = i_this->m370 - i_this->m348;
    anm_init(i_this, 7, 5.0f, 0, 1.0f, -1, 0);
    cMtx_YrotS(*calc_mtx, angle);
    cXyz offset(0.0f, 0.0f, 6250.0f);
    cXyz pos;
    MtxPosition(&offset, &pos);
    i_this->m344 = pos.x;
    i_this->m342 = pos.z;
    i_this->m338 = i_this->m336 = i_this->m334 = 0;
    i_this->scale.y = 1.75f;
    i_this->m37C = 0x4B0;
    cCcD_Obj* hitObj = i_this->mHeadSph.GetTgHitObj();
    if (hitObj != NULL) {
        if (hitObj->GetAtType() & AT_TYPE_SWORD) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_seStart(i_this, 0x2806, 0x20);
        } else if (hitObj->GetAtType() & AT_TYPE_BOKO_STICK) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_seStart(i_this, 0x2835, 0x20);
        } else if (hitObj->GetAtType() & AT_TYPE_SKULL_HAMMER) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_seStart(i_this, 0x2855, 0x31);
        } else if (!(hitObj->GetAtType() & AT_TYPE_BOOMERANG)) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_seStart(i_this, 0x2836, 0x20);
        }
    }
    i_this->m398 = 1.0f;
    i_this->m376 = i_this->m372 = 0;
    i_this->m366[2] = 3;
    if (i_this->m2D0 == 0) {
        i_this->mAction = 0;
        i_this->mMode = 5;
    } else {
        i_this->mAction = 4;
        i_this->mMode = 0x32;
    }
}

/* 0000164C-00001954       .text body_atari_check__FP8bo_class */
static BOOL body_atari_check(bo_class* i_this) {
    if (i_this->m366[2] != 0) {
        return FALSE;
    }
    if (!i_this->mBodyCyl.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hitObj = i_this->mBodyCyl.GetTgHitObj();
    if (hitObj == NULL) {
        return FALSE;
    }
    switch (hitObj->GetAtType()) {
    case AT_TYPE_FIRE:
    case AT_TYPE_FIRE_ARROW:
        i_this->mEnemyFire.mFireDuration = 0x50;
        i_this->m2D0 = 1;
        nokezori_damage_rtn(i_this);
        i_this->m2C8 = 0;
        i_this->m374 = i_this->m372 = 0;
        dComIfGp_particle_set(0x8109, &i_this->m328);
        return TRUE;
    case AT_TYPE_ICE_ARROW:
        i_this->mEnemyIce.mFreezeDuration = 80.0f + REG8_F(13);
        i_this->m2D0 = 2;
        i_this->mEnemyIce.m00C = 1;
        i_this->attention_info.flags = 0;
        i_this->health = 30;
        nokezori_damage_rtn(i_this);
        i_this->m2C8 = 0;
        i_this->m374 = i_this->m372 = 0;
        dComIfGp_particle_set(0x8109, &i_this->m328);
        return TRUE;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 80.0f + REG8_F(13);
        i_this->attention_info.flags = 0;
        i_this->m2D0 = 3;
        fopAcM_create(fpcNm_BO_e, make_bo_prm(i_this->m2C1), &i_this->current.pos, fopAcM_GetRoomNo(i_this), &i_this->current.angle, &i_this->scale, 0);
        nokezori_damage_rtn(i_this);
        i_this->m2C8 = 0;
        i_this->m374 = i_this->m372 = 0;
        dComIfGp_particle_set(0x8109, &i_this->m328);
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        fopAcM_seStart(i_this, 0x2828, 0x20);
        return TRUE;
    default: {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        cXyz hitPos = *i_this->mBodyCyl.GetTgHitPosP();
        i_this->mHeadSph.OffAtSetBit();
        i_this->mHeadSph.OffAtSetBit();
        i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
        i_this->attention_info.flags &= ~fopAc_Attn_LOCKON_BATTLE_e;
        i_this->m398 = 1.0f;
        dComIfGp_particle_set(0x10, &hitPos);
        cXyz scale(2.0f, 2.0f, 2.0f);
        dComIfGp_particle_set(0xF, &hitPos, &player->shape_angle, &scale);
        i_this->m364 = (u8)(REG8_S(5) + 5);
        i_this->mAction = 2;
        i_this->mMode = 0x14;
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        fopAcM_seStart(i_this, 0x2828, 0x20);
        return TRUE;
    }
    }
}

/* 00001954-00001D6C       .text damage_check__FP8bo_class */
static BOOL damage_check(bo_class* i_this) {
    if (head_atari_check(i_this)) {
        s16 angle = i_this->m370 - i_this->m348;
        cXyz offset;
        cXyz pos;
        if (i_this->m2CA == 2) {
            fopAc_ac_c* player = dComIfGp_getPlayer(0);
            cXyz hitPos = *i_this->mHeadSph.GetTgHitPosP();
            dComIfGp_particle_set(0x10, &hitPos);
            cXyz scale(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(0xF, &hitPos, &player->shape_angle, &scale);
            i_this->mAction = 4;
            i_this->mMode = 0x28;
            mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_seStart(i_this, 0x2828, 0x20);
            return TRUE;
        }
        i_this->mHeadSph.OffAtSetBit();
        i_this->mHeadSph.OffAtSetBit();
        i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
        if (i_this->m2CA == 1) {
            nokezori_damage_rtn(i_this);
        } else {
            if (REG8_F(11) && i_this->mMode == 4) {
                return FALSE;
            }
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            offset.set(0.0f, 0.0f, 2250.0f);
            cMtx_YrotS(*calc_mtx, angle);
            MtxPosition(&offset, &pos);
            anm_init(i_this, 0x12, 2.0f, 0, 1.0f, -1, 0);
            i_this->m356 = pos.x;
            i_this->m354 = pos.z;
            i_this->m388 = -10000.0f;
            i_this->m37E = 0;
            i_this->m380 = 0x1C52;
            i_this->m382 = i_this->m370 - i_this->m348;
            u8 cutType = ((daPy_py_c*)dComIfGp_getPlayer(0))->getCutType();
            if (cutType == 3) {
                i_this->m382 -= 0x4000;
            } else if (cutType == 4) {
                i_this->m382 += 0x4000;
            }
            i_this->m37C = 0x800;
            cCcD_Obj* hitObj = i_this->mHeadSph.GetTgHitObj();
            if (hitObj != NULL) {
                if (hitObj->GetAtType() & AT_TYPE_SWORD) {
                    fopAcM_seStart(i_this, 0x2803, 0x31);
                } else if (hitObj->GetAtType() & AT_TYPE_BOKO_STICK) {
                    fopAcM_seStart(i_this, 0x2833, 0x31);
                } else {
                    fopAcM_seStart(i_this, 0x2834, 0x31);
                }
            }
            i_this->mAction = 0;
            i_this->mMode = 4;
        }
        i_this->m2C8 = 0;
        i_this->m374 = i_this->m372 = 0;
        dComIfGp_particle_set(0x8109, &i_this->m328);
        return TRUE;
    }
    return FALSE;
}

/* 00001D6C-00001DB4       .text angle_initial__FP8bo_class */
static void angle_initial(bo_class* i_this) {
    i_this->m33A = 0;
    i_this->m33C = 0;
    i_this->m33E = 0;
    i_this->m352 = 0;
    i_this->m354 = 0;
    i_this->m356 = 0;
    i_this->m334 = 0;
    i_this->m336 = 0;
    i_this->m338 = 0;
    i_this->m340 = 0;
    i_this->m342 = 0;
    i_this->m344 = 0;
}

/* 00001DB4-00001EB4       .text wait_initial__FP8bo_class */
static void wait_initial(bo_class* i_this) {
    if (cM_rnd() < 0.5f) {
        anm_init(i_this, 0x15, 5.0f, 2, 1.0f, -1, 0);
    } else {
        anm_init(i_this, 0x16, 5.0f, 2, 1.0f, -1, 0);
    }
    i_this->m366[0] = 60.0f + cM_rndF(60.0f);
    i_this->mHeadSph.OffAtSetBit();
    i_this->mHeadSph.OffAtSetBit();
    i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
    i_this->mHeadSph.OnCoSetBit();
    angle_initial(i_this);
    i_this->mAction = 0;
    i_this->mMode = 2;
}

/* 00001EB4-0000220C       .text start_bakutsuki_event_camera__FP10fopAc_ac_c */
static void start_bakutsuki_event_camera(fopAc_ac_c* i_this) {
    static cXyz cam_pos(40.0f, 10.0f, 280.0f);
    static cXyz ctr_pos(0.0f, 50.0f, 50.0f);
    static f32 cam_fovy = 75.0f;
    static int cam_timer = 30;
    dComIfGp_getCamera(0)->mCamera.StartEventCamera(5, fopAcM_GetID(i_this), "RelActor", "@STARTER", "RelUseMask", "--or", "Timer", &cam_timer, "Center", &ctr_pos, "Eye", &cam_pos, "Fovy", &cam_fovy, NULL);
}

/* 0000220C-00002250       .text end_event_camera__FP10fopAc_ac_c */
static void end_event_camera(fopAc_ac_c* i_this) {
    dComIfGp_getCamera(0)->mCamera.EndEventCamera(fopAcM_GetID(i_this));
}

/* 00002250-00002ED8       .text bo_move__FP8bo_class */
static void bo_move(bo_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    switch (i_this->mMode) {
    case 0:
        if (fopAcM_searchActorDistance(i_this, player) < 600.0f) {
            i_this->mBodyCyl.OnTgSetBit();
            i_this->mHeadSph.OnTgSetBit();
            i_this->mHeadSph.OnCoSetBit();
            fopAcM_seStart(i_this, 0x5844, 0);
            mDoAud_monsSeStart(0x484D, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            anm_init(i_this, 9, 5.0f, 0, 1.0f, -1, 0);
            anm_init(i_this, 8, 5.0f, 0, 1.0f, -1, 1);
            i_this->mHeadSph.OnAtSetBit();
            i_this->mHeadSph.OnAtHitBit();
            i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK1);
            i_this->mHeadSph.OffAtNoTgHitInfSet();
            i_this->attention_info.flags |= fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mMode = 1;
        }
        break;
    case 3:
        if (i_this->mAnmIdx == 5) {
            f32 frame = i_this->mpUpMorf->getFrame();
            if (frame < 27.0f || frame >= 55.0f) {
                i_this->m34E = fopAcM_searchActorAngleY(i_this, player);
            } else if (frame < 38.0f) {
                if (frame == 27.0f) {
                    i_this->mHeadSph.OnAtSetBit();
                    i_this->mHeadSph.OnAtHitBit();
                    fopAcM_seStart(i_this, 0x5845, 0);
                } else {
                    s16 hit = 0;
                    if (i_this->mHeadSph.ChkAtShieldHit()) {
                        i_this->mMode = 6;
                        hit = 1;
                    } else if (i_this->mHeadSph.ChkAtHit()) {
                        fopAc_ac_c* hitAc = i_this->mHeadSph.GetAtHitAc();
                        if (hitAc != NULL && hitAc == player) {
                            hit = 1;
                        }
                    }
                    if (hit) {
                        i_this->mHeadSph.OffAtSetBit();
                        i_this->mHeadSph.OffAtSetBit();
                        i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
                        anm_init(i_this, 0xC, 0.0f, 0, 1.0f, -1, 0);
                    }
                }
            } else if (i_this->mpUpMorf->checkFrame(38.0f)) {
                i_this->mHeadSph.OffAtSetBit();
                i_this->mHeadSph.OffAtSetBit();
                i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
            }
        }
    case 6:
        if (i_this->mpUpMorf->isStop()) {
            i_this->m366[1] = 30.0f + cM_rndF(30.0f);
            wait_initial(i_this);
        }
        break;
    case 1:
        i_this->m34E = fopAcM_searchActorAngleY(i_this, player);
        if (i_this->m3D0 == NULL) {
            i_this->m3D0 = dComIfGp_particle_set(0x8106, &i_this->current.pos);
        } else {
            i_this->m3D0->setGlobalRTMatrix(i_this->mpUpMorf->getModel()->getAnmMtx(9));
        }
        if (i_this->mpUpMorf->getFrame() > 39.0f) {
            i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
            i_this->mHeadSph.OffAtSetBit();
            i_this->mHeadSph.OffAtSetBit();
        }
        if (i_this->mpUpMorf->isStop()) {
            if (i_this->m3D0 != NULL) {
                i_this->m3D0->becomeInvalidEmitter();
                i_this->m3D0 = NULL;
            }
            wait_initial(i_this);
        }
        break;
    case 2:
        if (i_this->m366[3] != 0) {
            break;
        }
        if (i_this->m3D4 == NULL) {
            i_this->m3D4 = dComIfGp_particle_set(0x8107, &i_this->current.pos);
            if (i_this->m3D4 != NULL) {
                i_this->m3D4->setParticleCallBackPtr(&i_this->m3DC);
            }
            i_this->m2C6 = 0;
        } else {
            i_this->m3D4->setGlobalSRTMatrix(i_this->mpUpMorf->getModel()->getAnmMtx(9));
        }
        if (i_this->m366[0] == 0) {
            f32 frame = i_this->mpUpMorf->getFrame();
            if (i_this->mAnmIdx == 0x16) {
                anm_init(i_this, 0x15, 20.0f, 2, 1.0f, -1, 0);
            } else {
                anm_init(i_this, 0x16, 20.0f, 2, 1.0f, -1, 0);
            }
            i_this->mpUpMorf->setFrame(frame);
            i_this->m366[0] = 60.0f + cM_rndF(60.0f);
        }
        if (i_this->m366[1] == 0 && fopAcM_searchPlayerDistance(i_this) < 380.0f) {
            anm_init(i_this, 5, 5.0f, 0, 1.0f, -1, 0);
            if (cM_rnd() < 0.5f) {
                i_this->mHeadSph.SetAtAtp(0);
                i_this->mAction = 1;
                i_this->mMode = 0xA;
            } else {
                i_this->mHeadSph.SetAtAtp(1);
                i_this->mHeadSph.OffAtNoTgHitInfSet();
                i_this->mHeadSph.OnCoSetBit();
                mDoAud_monsSeStart(0x484E, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                i_this->mMode = 3;
            }
        } else if (fopAcM_searchPlayerDistance(i_this) > 900.0f) {
            anm_init(i_this, 0x11, 5.0f, 0, 1.0f, -1, 0);
            anm_init(i_this, 0x10, 5.0f, 0, 1.0f, -1, 1);
            i_this->attention_info.flags &= ~fopAc_Attn_LOCKON_BATTLE_e;
            fopAcM_seStart(i_this, 0x5848, 0);
            i_this->mBodyCyl.OffTgSetBit();
            i_this->mHeadSph.OffTgSetBit();
            i_this->mHeadSph.OffCoSetBit();
            i_this->mBodyCyl.ClrTgHit();
            i_this->mHeadSph.ClrTgHit();
            angle_initial(i_this);
            i_this->mMode = 0;
        }
        i_this->m34E = fopAcM_searchPlayerAngleY(i_this);
        break;
    case 4: {
        if (((daPy_py_c*)player)->getCutType() == 3) {
            cMtx_YrotS(*calc_mtx, i_this->m37E);
        } else {
            cMtx_YrotS(*calc_mtx, -i_this->m37E);
        }
        cXyz offset;
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = i_this->m388;
        cXyz pos;
        MtxPosition(&offset, &pos);
        i_this->m336 = pos.z;
        i_this->m338 = pos.x;
        i_this->m37E += i_this->m380;
        cLib_addCalc0(&i_this->m388, 1.0f, 250.0f);
        cLib_addCalcAngleS2(&i_this->m354, 0, 1, 0x87);
        cLib_addCalcAngleS2(&i_this->m356, 0, 1, 0x87);
        if (fabs(i_this->m388) < 1.0) {
            i_this->m352 = 0;
            i_this->m354 = 0;
            i_this->m356 = 0;
            i_this->m334 = 0;
            i_this->m336 = 0;
            i_this->m338 = 0;
            i_this->m366[0] = 0;
            i_this->mMode = 2;
            if (i_this->m364 != 0) {
                i_this->m366[3] = 45;
            }
        }
        break;
    }
    case 5:
        if (i_this->m364 != 0) {
            i_this->m364--;
        }
        if (i_this->m364 == 1) {
            i_this->mAction = 2;
            i_this->mMode = 0x14;
            return;
        }
        if (i_this->m372 < 16 && !(i_this->m2C8 & 1) && (s16)cLib_distanceAngleS(i_this->m33C, i_this->m342) < 0x100) {
            i_this->m342 ^= 0xFF00;
            i_this->m342 *= 0.1f;
            i_this->m372++;
            if (i_this->m372 >= 16) {
                i_this->m342 = 0;
                i_this->m33C = 0;
                i_this->m2C8 |= 1;
            }
        }
        if (i_this->m374 < 16 && !(i_this->m2C8 & 2) && (s16)cLib_distanceAngleS(i_this->m33E, i_this->m344) < 0x100) {
            i_this->m344 ^= 0xFF00;
            i_this->m344 *= 0.1f;
            i_this->m374++;
            if (i_this->m374 >= 16) {
                i_this->m344 = 0;
                i_this->m33E = 0;
                i_this->m2C8 |= 2;
            }
        }
        if (i_this->m342 == 0 && i_this->m344 == 0) {
            i_this->m376++;
        }
        if (i_this->m376 > 30) {
            wait_initial(i_this);
            i_this->m376 = 0;
            i_this->m398 = 1.0f;
        }
        if (i_this->m2D0 == 0) {
            body_atari_check(i_this);
        }
        break;
    case 7:
        if (i_this->mpUpMorf->isStop()) {
            i_this->mMode = 0;
        }
        break;
    }

    cLib_addCalcAngleS2(&i_this->m348, i_this->m34E, 1, 0x800);
    cLib_addCalcAngleS2(&i_this->m33C, i_this->m342, 1, i_this->m37C);
    cLib_addCalcAngleS2(&i_this->m33E, i_this->m344, 1, i_this->m37C);

    if (i_this->mMode == 4 && (s16)cLib_distanceAngleS(fopAcM_searchPlayerAngleY(i_this), i_this->m348) > 0x337F) {
        wait_initial(i_this);
        anm_init(i_this, 0x11, 5.0f, 0, 1.0f, -1, 0);
        anm_init(i_this, 0x10, 5.0f, 0, 1.0f, -1, 1);
        i_this->attention_info.flags &= ~fopAc_Attn_LOCKON_BATTLE_e;
        fopAcM_seStart(i_this, 0x5848, 0);
        i_this->mBodyCyl.OffTgSetBit();
        i_this->mHeadSph.OffTgSetBit();
        i_this->mHeadSph.OffCoSetBit();
        i_this->mBodyCyl.ClrTgHit();
        i_this->mHeadSph.ClrTgHit();
        i_this->mMode = 7;
    } else if (i_this->mMode != 0 && i_this->mMode != 5) {
        if (damage_check(i_this)) {
            return;
        }
    }
}

/* 00002ED8-000034B8       .text bo2_move__FP8bo_class */
static void bo2_move(bo_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 stickX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    f32 stickY = g_mDoCPd_cpadInfo[0].mMainStickPosY;
    JPABaseEmitter* emitter;

    switch (i_this->mMode) {
    case 0xA:
        anm_init(i_this, 0x14, 5.0f, 0, 1.0f, -1, 0);
        fopAcM_seStart(i_this, 0x5849, 0);
        i_this->mHeadSph.OnAtNoTgHitInfSet();
        i_this->mHeadSph.OffCoSetBit();
        i_this->m2CB = 0;
        i_this->m2CC = 0;
        i_this->mMode++;
        break;
    case 0xB: {
        f32 frame = i_this->mpUpMorf->getFrame();
        if (frame >= 28.0f && frame <= 33.0f && i_this->mHeadSph.ChkAtHit()) {
            fopAc_ac_c* hitAc = i_this->mHeadSph.GetAtHitAc();
            if (hitAc != NULL && hitAc == player) {
                i_this->m2CB = 1;
            }
        }
        if (i_this->mpUpMorf->checkFrame(27.0f)) {
            i_this->mHeadSph.OnAtSetBit();
            i_this->mHeadSph.OnAtHitBit();
            mDoAud_monsSeStart(0x4851, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        }
        if (i_this->mpUpMorf->checkFrame(33.0f)) {
            i_this->mHeadSph.OffAtSetBit();
            i_this->mHeadSph.OffAtSetBit();
            i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
        }
        if (i_this->mpUpMorf->isStop()) {
            wait_initial(i_this);
            i_this->m366[1] = 30.0f + cM_rndF(30.0f);
        }
        break;
    }
    case 0xC:
        if (!i_this->m2CC && (i_this->mpUpMorf->checkFrame(33.0f) || i_this->mpUpMorf->getFrame() >= 33.0f)) {
            player->changeOriginalDemo();
            player->changeDemoMode(daPy_demo_c::DEMO_UNK_030_e);
            s16 angle = cLib_distanceAngleS(player->shape_angle.y, fopAcM_searchActorAngleY(player, i_this));
            i_this->m2CD = 0;
            if (angle > 0x4000) {
                i_this->m2CD = 1;
            }
            i_this->m2CC = 1;
        }
        if (i_this->mpUpMorf->isStop()) {
            anm_init(i_this, 0xD, 5.0f, 2, 1.0f, -1, 0);
            emitter = dComIfGp_particle_set(0x810C, &i_this->current.pos);
            if (emitter != NULL) {
                emitter->setGlobalSRTMatrix(i_this->mpUpMorf->getModel()->getAnmMtx(9));
            }
            i_this->m376 = 0;
            i_this->m366[1] = 0;
            i_this->m2D4 = 1;
            i_this->m2D8 = 1;
            mDoAud_monsSeStart(0x4852, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->mMode++;
        }
        break;
    case 0xD:
        if (i_this->m3D8 == NULL) {
            i_this->m3D8 = dComIfGp_particle_set(0x8107, &i_this->current.pos);
            if (i_this->m3D8 != NULL) {
                i_this->m3D8->setParticleCallBackPtr(&i_this->m3DC);
                i_this->m3D8->setRate(0.07f);
            }
            i_this->m2C7 = 0;
        } else {
            i_this->m3D8->setGlobalSRTMatrix(i_this->mpUpMorf->getModel()->getAnmMtx(9));
        }
        if (i_this->m366[1] == 0) {
            if (!daPy_getPlayerLinkActorClass()->checkNoDamageMode()) {
                daPy_getPlayerLinkActorClass()->setDamagePoint(-1.0f);
            }
            i_this->m366[1] = 30;
        }
        i_this->m376++;
        if (i_this->m376 > 120) {
            i_this->m376 = 0;
            anm_init(i_this, 0xB, 5.0f, 0, 1.0f, -1, 0);
            mDoAud_monsSeStart(0x5846, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            end_event_camera(i_this);
            i_this->mMode++;
            break;
        }
        if (i_this->mpUpMorf->checkFrame(0.0f)) {
            mDoAud_monsSeStart(0x4852, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            emitter = dComIfGp_particle_set(0x810C, &i_this->current.pos);
            if (emitter != NULL) {
                emitter->setGlobalSRTMatrix(i_this->mpUpMorf->getModel()->getAnmMtx(9));
            }
        }
        if (i_this->m2D4 > 0 && stickX < 0.0f) {
            i_this->m2D4 = -1;
            i_this->m376 += 2;
        } else if (i_this->m2D4 < 0 && stickX > 0.0f) {
            i_this->m2D4 = 1;
            i_this->m376 += 2;
        }
        if (i_this->m2D8 > 0 && stickY < 0.0f) {
            i_this->m2D8 = -1;
            i_this->m376 += 2;
        } else if (i_this->m2D8 < 0 && stickY > 0.0f) {
            i_this->m2D8 = 1;
            i_this->m376 += 2;
        }
        if (CPad_CHECK_TRIG_A(0)) {
            i_this->m376 += 2;
        }
        break;
    case 0xE:
        if (i_this->mpUpMorf->checkFrame(9.0f)) {
            player->current.angle.y = i_this->m348;
            player->changeDemoMode(daPy_demo_c::DEMO_LDAM_e);
            i_this->m2CC = 0;
            if (i_this->m2CD) {
                player->changeDemoParam0(0);
            } else {
                player->changeDemoParam0(1);
            }
        }
        if (i_this->mpUpMorf->isStop()) {
            dComIfGp_event_reset();
            wait_initial(i_this);
            i_this->m366[1] = 30.0f + cM_rndF(30.0f);
            i_this->m366[1] *= 2;
        }
        break;
    }

    if (i_this->mMode < 0xC && !i_this->m2CB) {
        if (damage_check(i_this)) {
            return;
        }
    }
}

/* 000034B8-0000378C       .text bo3_move__FP8bo_class */
static void bo3_move(bo_class* i_this) {
    switch (i_this->mMode) {
    case 0x14:
        if (i_this->m364 != 0) {
            i_this->m364--;
        }
        if (i_this->m364 == 0) {
            i_this->mBodyCyl.OffTgSetBit();
            i_this->mHeadSph.OffTgSetBit();
            i_this->mHeadSph.OffCoSetBit();
            i_this->mBodyCyl.ClrTgHit();
            i_this->mHeadSph.ClrTgHit();
            csXyz angle;
            angle.x = i_this->current.angle.x;
            angle.y = i_this->m348;
            angle.z = i_this->current.angle.z;
            if (!i_this->m2CE) {
                fopAcM_create(fpcNm_BO_e, 2, &i_this->m304, fopAcM_GetRoomNo(i_this), &angle, &i_this->scale, 0);
            }
            i_this->m2CE = 0;
            i_this->mType = 1;
            anm_init(i_this, 0x13, 5.0f, 0, 1.0f, -1, 1);
            dScnPly_ply_c::setPauseTimer(4);
            i_this->mMode++;
        }
        break;
    case 0x15:
        if (i_this->mpDwMorf->checkFrame(43.0f)) {
            u8 dropType = 0;
            if (i_this->m2C1) {
                dropType = 3;
                i_this->m366[1] = 50;
            }
            if (i_this->m2D0 != 3) {
                fopAcM_createDisappear(i_this, &i_this->current.pos, 5, dropType, i_this->stealItemBitNo);
            }
        }
        if (i_this->mpDwMorf->isStop()) {
            if (i_this->m2C1) {
                i_this->mMode++;
            } else {
                fopAcM_onActor(i_this);
                fopAcM_delete(i_this);
            }
        }
        break;
    case 0x16:
        if (i_this->m366[1] == 0) {
            fopAcM_create(fpcNm_JBO_e, 1, &i_this->current.pos, fopAcM_GetRoomNo(i_this), &i_this->current.angle, &i_this->scale, 0);
            fopAcM_onActor(i_this);
            fopAcM_delete(i_this);
        }
        break;
    }

    if (i_this->mSmoke.getEmitter() != NULL && i_this->m366[2] == 0) {
        i_this->mSmoke.getEmitter()->setGlobalAlpha(i_this->m376);
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmoke.remove();
        }
    }
}

/* 0000378C-00003B30       .text bo4_move__FP8bo_class */
static void bo4_move(bo_class* i_this) {
    switch (i_this->mMode) {
    case 0x1E:
        i_this->mHeadSph.OffTgSetBit();
        i_this->mHeadSph.OffCoSetBit();
        i_this->mHeadSph.OffAtSetBit();
        i_this->mHeadSph.ClrTgHit();
        i_this->mHeadSph.ClrTgHit();
        anm_init(i_this, 7, 5.0f, 0, 1.0f, -1, 0);
        i_this->speed.y = 30.0f;
        i_this->gravity = -3.0f;
        i_this->speedF = 10.0f;
        i_this->current.angle.y = fopAcM_searchPlayerAngleY(i_this) + 0x8000;
        i_this->m390 = i_this->current.pos.y - 80.0f;
        i_this->mMode++;
        break;
    case 0x1F:
        i_this->shape_angle.x -= 0x1200;
        if (i_this->speed.y < 0.0f && i_this->current.pos.y < i_this->m390) {
            i_this->current.pos.y = i_this->m390;
            i_this->shape_angle.x = -0x8000;
            i_this->speedF = i_this->gravity = i_this->speed.y = 0.0f;
            i_this->m366[1] = 10;
            fopAcM_seStart(i_this, 0x5847, 0);
            dComIfGp_particle_set(0x810A, &i_this->m328);
            i_this->m366[2] = 10;
            i_this->m376 = 0xB4;
            i_this->m39C = i_this->m328;
            smoke_set(i_this);
            anm_init(i_this, 6, 0.0f, 0, 1.0f, -1, 0);
            i_this->mMode++;
        }
        break;
    case 0x20:
        if (i_this->m366[1] == 0) {
            i_this->m394 = 200.0f;
            i_this->current.pos.y = i_this->m390 - 200.0f;
            i_this->speed.y = 10.0f;
            i_this->gravity = -1.0f;
            i_this->mMode++;
        }
        break;
    case 0x21:
        i_this->shape_angle.z += 0x1000;
        if (i_this->shape_angle.z > 0x4000) {
            csXyz angle;
            angle.x = 0;
            angle.y = i_this->m348 + 0xC000;
            angle.z = 0;
            cXyz pos = i_this->m310;
            pos.y = 30.0f + i_this->m390;
            fopAcM_create(fpcNm_BOKO_e, 0, &pos, fopAcM_GetRoomNo(i_this), &angle, &i_this->scale, 0);
            i_this->scale.z = i_this->scale.y = i_this->scale.x = 0.0f;
            i_this->m398 = 0.0f;
            i_this->m366[1] = 10;
            i_this->mMode++;
        }
        break;
    case 0x22:
        if (i_this->m366[1] == 0 && i_this->mSmoke.getEmitter() == NULL) {
            fopAcM_delete(i_this);
        }
        break;
    }

    if (i_this->mSmoke.getEmitter() != NULL && i_this->m366[2] == 0) {
        i_this->mSmoke.getEmitter()->setGlobalAlpha(i_this->m376);
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmoke.remove();
        }
    }
}

/* 00003B30-00003D9C       .text bo5_move__FP8bo_class */
static void bo5_move(bo_class* i_this) {
    switch (i_this->mMode) {
    case 0x28:
        i_this->m376 = 3;
        i_this->mBodyCyl.OffTgSetBit();
        i_this->mHeadSph.OffTgSetBit();
        i_this->mHeadSph.OffCoSetBit();
        i_this->mBodyCyl.ClrTgHit();
        i_this->mHeadSph.ClrTgHit();
        dScnPly_ply_c::setPauseTimer(2);
        anm_init(i_this, 0xF, 5.0f, 2, 1.0f, -1, 0);
        i_this->attention_info.flags &= ~fopAc_Attn_LOCKON_BATTLE_e;
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        fopAcM_seStart(i_this, 0x2828, 0x20);
        i_this->mMode++;
        break;
    case 0x29:
        if (i_this->mpUpMorf->checkFrame(15.0f)) {
            i_this->m376--;
            if (i_this->m376 <= 0) {
                i_this->attention_info.flags &= ~fopAc_Attn_LOCKON_BATTLE_e;
                anm_init(i_this, 9, 0.0f, 0, 0.0f, -1, 0);
                dComIfGp_particle_set(0x810A, &i_this->m328, NULL, NULL, 0xFF, NULL, -1, &i_this->tevStr.mColorK0);
                i_this->m39C = i_this->m328;
                i_this->m366[2] = 10;
                i_this->m376 = 0xB4;
                smoke_set(i_this);
                fopAcM_seStart(i_this, 0x5801, 0);
                i_this->m2CE = 1;
                i_this->mAction = 2;
                i_this->mMode = 0x14;
            }
        }
        break;
    case 0x32:
        i_this->mBodyCyl.OffTgSetBit();
        i_this->mHeadSph.OffTgSetBit();
        i_this->mHeadSph.OffCoSetBit();
        i_this->mBodyCyl.ClrTgHit();
        i_this->mHeadSph.ClrTgHit();
        dScnPly_ply_c::setPauseTimer(2);
        anm_init(i_this, 0xE, 5.0f, 0, 1.0f, -1, 0);
        i_this->attention_info.flags = 0;
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        fopAcM_seStart(i_this, 0x2828, 0x20);
        i_this->mMode++;
    case 0x33:
        if (i_this->m366[0] == 0 && i_this->mpUpMorf->isStop()) {
            i_this->m366[2] = 10;
            i_this->m376 = 0xB4;
            i_this->m2CE = 1;
            i_this->mAction = 2;
            i_this->mMode = 0x14;
        }
        break;
    }
}

/* 00003D9C-000047C4       .text daBO_Execute__FP8bo_class */
static BOOL daBO_Execute(bo_class* i_this) {
    if (i_this->mType == 0 && enemy_ice(&i_this->mEnemyIce)) {
        if (i_this->mEnemyIce.mLightShrinkTimer != 0) {
            i_this->mpUpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
            i_this->mpUpMorf->calc();
        } else {
            i_this->mHeadSph.SetC(i_this->m2E0);
            i_this->mHeadSph.SetR(60.0f);
            dComIfG_Ccsp()->Set(&i_this->mHeadSph);
        }
        return TRUE;
    }

    for (int i = 0; i < 5; i++) {
        if (i_this->m366[i] != 0) {
            i_this->m366[i]--;
        }
    }

    switch (i_this->mAction) {
    case 0:
        bo_move(i_this);
        i_this->shape_angle = i_this->current.angle;
        break;
    case 1:
        bo2_move(i_this);
        if (i_this->m2CB) {
            if (i_this->eventInfo.checkCommandDemoAccrpt()) {
                if (i_this->mAction != 1) {
                    dComIfGp_event_reset();
                } else {
                    i_this->mMode = 0xC;
                    start_bakutsuki_event_camera(i_this);
                }
                i_this->m2CB = 0;
            } else {
                fopAcM_orderPotentialEvent(i_this, 2, 0xFFFF, 0);
                i_this->eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
        }
        break;
    case 2:
        bo3_move(i_this);
        break;
    case 3:
        bo4_move(i_this);
        break;
    case 4:
        bo5_move(i_this);
        break;
    }

    if (i_this->m2C6 != 0 || (i_this->mAnmIdx != 0x16 && i_this->mAnmIdx != 0x15)) {
        if (i_this->m3D4 != NULL) {
            i_this->m3D4->setGlobalSRTMatrix(i_this->mpUpMorf->getModel()->getAnmMtx(9));
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
    if (i_this->m2C7 != 0 || i_this->mAnmIdx != 0xD) {
        if (i_this->m3D8 != NULL) {
            i_this->m3D8->setGlobalSRTMatrix(i_this->mpUpMorf->getModel()->getAnmMtx(9));
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

    cLib_addCalc2(&i_this->scale.y, i_this->m398, 1.0f, 0.0875f);
    i_this->mStts.SetWeight(0xFF);
    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    cXyz offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = i_this->speedF;
    cXyz vel;
    MtxPosition(&offset, &vel);
    i_this->speed.x = vel.x;
    i_this->speed.y += i_this->gravity;
    i_this->speed.z = vel.z;
    fopAcM_posMove(i_this, i_this->mStts.GetCCMoveP());

    if (i_this->mType == 0 || i_this->mType == 2) {
        i_this->mpUpMorf->play(NULL, 0, 0);
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        i_this->mpDwMorf->play(NULL, 0, 0);
    }

    if (i_this->mType == 0) {
        if (i_this->mMode != 5) {
            i_this->attention_info.position = i_this->m2E0;
            i_this->attention_info.position.y += 60.0f;
            i_this->eyePos = i_this->m328;
        } else {
            i_this->eyePos = i_this->m2F8;
            i_this->eyePos.y += 60.0f;
            i_this->attention_info.position = i_this->eyePos;
        }
    }
    if (i_this->m2CC || i_this->mMode == 0xC) {
        i_this->attention_info.position = i_this->current.pos;
        i_this->attention_info.position.y += 60.0f;
        i_this->shape_angle.y = i_this->m348;
    }

    i_this->mHeadSph.SetC(i_this->m2E0);
    i_this->mHeadSph.SetR(60.0f);
    dComIfG_Ccsp()->Set(&i_this->mHeadSph);
    if (i_this->mAction == 0) {
        i_this->mBodyCyl.SetC(i_this->m2F8);
        i_this->mBodyCyl.SetH(160.0f);
        i_this->mBodyCyl.SetR(15.0f);
        dComIfG_Ccsp()->Set(&i_this->mBodyCyl);
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        cXyz footPos = i_this->current.pos;
        footPos.y += 10.0f;
        i_this->mFootSph.SetC(footPos);
        i_this->mFootSph.SetR(45.0f);
        dComIfG_Ccsp()->Set(&i_this->mFootSph);
    }
    draw_SUB(i_this);
    return TRUE;
}

/* 000047C4-000047CC       .text daBO_IsDelete__FP8bo_class */
static BOOL daBO_IsDelete(bo_class*) {
    return TRUE;
}

/* 000047CC-000048AC       .text daBO_Delete__FP8bo_class */
static BOOL daBO_Delete(bo_class* i_this) {
    i_this->mSmoke.remove();
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
    dComIfG_resDelete(&i_this->mPhs, "BO");
    return TRUE;
}

/* 000048AC-00004C1C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    bo_class* i_this = (bo_class*)a_this;

    int anmIdx = 9;
    if (i_this->mType == 2) {
        anmIdx = 7;
    }
    i_this->mpUpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BO", 0x1A),
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("BO", anmIdx),
        J3DFrameCtrl::EMode_RESET, 0.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x37441422
    );
    if (i_this->mpUpMorf == NULL || i_this->mpUpMorf->getModel() == NULL) {
        return FALSE;
    }
    i_this->mpUpMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpUpMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpUpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_UP);
    }
    J3DModel* model = i_this->mpUpMorf->getModel();

    if (i_this->mType == 2) {
        i_this->mpBrk = new mDoExt_brkAnm();
        if (i_this->mpBrk == NULL) {
            return FALSE;
        }
        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BO", 0x1D);
        if (!i_this->mpBrk->init(model->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
            return FALSE;
        }
    } else {
        i_this->mpDwMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("BO", 0x19),
            NULL, NULL,
            (J3DAnmTransform*)dComIfG_getObjectRes("BO", 8),
            J3DFrameCtrl::EMode_RESET, 0.0f, 0, -1, 1,
            NULL,
            0x80000,
            0x33221202
        );
        if (i_this->mpDwMorf == NULL || i_this->mpDwMorf->getModel() == NULL) {
            return FALSE;
        }
        i_this->mpDwMorf->getModel()->setUserArea((u32)i_this);
        for (u16 i = 0; i < i_this->mpDwMorf->getModel()->getModelData()->getJointNum(); i++) {
            i_this->mpDwMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_DW);
        }
    }

    if (i_this->mType == 0) {
        if (!i_this->mInvisModel.create(i_this->mpUpMorf->getModel())) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00004C64-00004FF0       .text daBO_Create__FP10fopAc_ac_c */
static cPhs_State daBO_Create(fopAc_ac_c* a_this) {
    fopAcM_ct_Retail(a_this, bo_class);
    bo_class* i_this = (bo_class*)a_this;

    cPhs_State phase = dComIfG_resLoad(&i_this->mPhs, "BO");
    if (phase == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(a_this, bo_class);
        i_this->mType = fopAcM_GetParam(a_this);
        i_this->m2C1 = fopAcM_GetParam(a_this) >> 8;
        if (i_this->mType == 0xFF) {
            i_this->mType = 0;
        }
        if (i_this->m2C1 == 0xFF) {
            i_this->m2C1 = 0;
        }
        i_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("bbaba", 0);

        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x3100)) {
            return cPhs_ERROR_e;
        }

        if (i_this->mType == 0 || i_this->mType == 2) {
            fopAcM_SetMtx(a_this, i_this->mpUpMorf->getModel()->getBaseTRMtx());
        } else {
            fopAcM_SetMtx(a_this, i_this->mpDwMorf->getModel()->getBaseTRMtx());
        }
        fopAcM_setCullSizeBox(a_this, -150.0f, 0.0f, -150.0f, 150.0f, 330.0f, 150.0f);
        a_this->attention_info.flags = 0;
        a_this->max_health = 1;
        a_this->health = 1;
        i_this->m398 = 1.0f;
        i_this->mStts.Init(0xFF, 1, a_this);
        i_this->mAction = 0;
        i_this->mMode = 0;

        static dCcD_SrcSph head_co_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_UNK2000,
                /* SrcObjAt  Atp     */ 1,
                /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
                /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
                /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
                /* SrcGObjAt Se      */ dCcG_SE_UNK6,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ 0,
                /* SrcGObjTg Spl     */ 0,
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
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ 0,
                /* SrcGObjTg Spl     */ 0,
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
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
                /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
                /* SrcObjCo  SPrm    */ 0,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ 0,
                /* SrcGObjTg Spl     */ 0,
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

        if (i_this->mType == 0) {
            i_this->mHeadSph.Set(head_co_sph_src);
            i_this->mHeadSph.SetStts(&i_this->mStts);
            i_this->stealItemLeft = 3;
            i_this->mBodyCyl.Set(body_cyl_src);
            i_this->mBodyCyl.SetStts(&i_this->mStts);
            i_this->mHeadSph.OffAtSetBit();
            i_this->mHeadSph.OffAtSetBit();
            i_this->mHeadSph.SetAtSpl(dCcG_At_Spl_UNK0);
            i_this->mEnemyIce.mpActor = a_this;
            i_this->mEnemyIce.mWallRadius = 15.0f;
            i_this->mEnemyIce.mCylHeight = 160.0f;
            i_this->mEnemyFire.mpMcaMorf = i_this->mpUpMorf;
            i_this->mEnemyFire.mpActor = a_this;
            static u8 fire_j[10] = {1, 3, 5, 6, 8, 9, 10, 11, 12, 13};
            static f32 fire_sc[10] = {1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
            for (int i = 0; i < 10; i++) {
                i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
                i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
            }
        }
        if (i_this->mType == 0 || i_this->mType == 1) {
            i_this->mFootSph.Set(foot_co_sph_src);
            i_this->mFootSph.SetStts(&i_this->mStts);
            if (i_this->mType == 1) {
                i_this->m366[0] = 15.0f + REG8_F(14);
                anm_init(i_this, 8, 0.0f, 0, 0.0f, -1, 1);
                i_this->mAction = 4;
                i_this->mMode = 0x33;
                i_this->m2D0 = 3;
                i_this->mpDwMorf->play(NULL, 0, 0);
                draw_SUB(i_this);
            }
        }
        i_this->m34E = fopAcM_searchPlayerAngleY(a_this);
        i_this->m348 = i_this->m34E;
        i_this->m304 = a_this->current.pos;
        if (i_this->mType == 2) {
            i_this->m394 = 100.0f;
            a_this->attention_info.flags = 0;
            i_this->mAction = 3;
            i_this->mMode = 0x1E;
            i_this->mpUpMorf->play(NULL, 0, 0);
            draw_SUB(i_this);
        }
        daBO_Execute(i_this);
    }
    return phase;
}

static actor_method_class l_daBO_Method = {
    (process_method_func)daBO_Create,
    (process_method_func)daBO_Delete,
    (process_method_func)daBO_Execute,
    (process_method_func)daBO_IsDelete,
    (process_method_func)daBO_Draw,
};

actor_process_profile_definition g_profile_BO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ fpcNm_BO_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bo_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ fpcDwPi_BO_e,
    /* Actor SubMtd */ &l_daBO_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_SHOWMAP_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
