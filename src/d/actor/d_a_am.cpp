/**
 * d_a_am.cpp
 * Enemy - Armos Knight
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_am.h"
#include "d/res/res_am.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/J3DGraphAnimator/J3DNode.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_particle.h"
#include "d/d_s_play.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_snap.h"
#include "d/actor/d_a_player.h"
#include "d/d_jnt_hit.h"
#include "d/d_cc_uty.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_bomb2.h"

enum Action {
    ACTION_DOUSA       = 0,
    ACTION_MODORU_MOVE = 1,
    ACTION_HANDOU_MOVE = 2,
    ACTION_ITAI_MOVE   = 3,
};

enum Mode {
    MODE_DOUSA_INIT       = 0,
    MODE_DOUSA_OKIRU      = 2,
    MODE_DOUSA_SLEEP_INIT = 9,
    MODE_DOUSA_SLEEP_MAIN = 10,
    MODE_MODORU_MOVE_INIT = 20,
    MODE_MODORU_MOVE_MAIN = 21,
    MODE_MODORU_MOVE_END  = 22,
    MODE_HANDOU_MOVE_INIT = 30,
    MODE_HANDOU_MOVE_MAIN = 31,
    MODE_ITAI_MOVE_INIT   = 40,
};

/* 00000078-0000021C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        am_class* i_this = (am_class*)model->getUserArea();
        if (i_this) {
            if (jntNo >= 1 && jntNo <= 4) {
                MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            }

            cXyz offset;
            switch (jntNo) {
            case 1: // kosi (waist)
                offset.x = 0.0f;
                offset.y = 240.0f;
                offset.z = 60.0f;
                MtxPosition(&offset, &i_this->mEyeballPos);
                offset.x = 0.0f;
                offset.y = 150.0f;
                offset.z = 70.0f;
                MtxPosition(&offset, &i_this->mMouthPos);
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->mWaistPos);
                break;
            case 2: // ago (jaw)
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->mJawPos);
                break;
            case 4: // eye
                cMtx_YrotM(*calc_mtx, i_this->mEyeRot.y);
                cMtx_XrotM(*calc_mtx, i_this->mEyeRot.x);
            }

            if (jntNo >= 1 && jntNo <= 4) {
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 0000021C-000002E4       .text draw_SUB__FP8am_class */
static void draw_SUB(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    i_this->mpMorf->calc();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
}

/* 000002E4-00000378       .text daAM_Draw__FP8am_class */
static BOOL daAM_Draw(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &actor->tevStr);

    dSnap_RegistFig(DSNAP_TYPE_AM, actor, 1.0f, 1.0f, 1.0f);

    i_this->mpMorf->entryDL();

    dComIfGd_setSimpleShadow2(
        &actor->current.pos, i_this->mAcch.GetGroundH(), 90.0f, i_this->mAcch.m_gnd,
        0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );

    return TRUE;
}

/* 00000378-000004A4       .text anm_init__FP8am_classifUcfi */
static void anm_init(am_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->mCurrBckIdx = bckFileIdx;
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("AM", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            dComIfG_getObjectRes("AM", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("AM", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            NULL
        );
    }
}

/* 000004A4-00000784       .text body_atari_check__FP8am_class */
static void body_atari_check(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();

#if VERSION == VERSION_JPN
    if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
        return;
    }
#endif

    i_this->mStts.Move();

    if (i_this->mBodyCyl.ChkTgHit() || i_this->mNeedleCyl.ChkTgHit()) {
        if (i_this->mbIsBodyBeingHit) {
            return;
        }

        cCcD_Obj* hitObj;
        if (i_this->mBodyCyl.ChkTgHit()) {
            hitObj = i_this->mBodyCyl.GetTgHitObj();
        } else {
            hitObj = i_this->mNeedleCyl.GetTgHitObj();
        }
        if (!hitObj) {
            return;
        }
        i_this->mbIsBodyBeingHit = true;

        switch (hitObj->GetAtType()) {
        case AT_TYPE_SWORD:
        case AT_TYPE_MACHETE:
        case AT_TYPE_UNK800:
        case AT_TYPE_DARKNUT_SWORD:
        case AT_TYPE_MOBLIN_SPEAR:
            fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x42);
            break;
        case AT_TYPE_BOOMERANG:
        case AT_TYPE_BOKO_STICK:
        case AT_TYPE_UNK2000:
        case AT_TYPE_STALFOS_MACE:
            fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x42);
            break;
        case AT_TYPE_SKULL_HAMMER:
            fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x42);
#if VERSION > VERSION_JPN
            if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
                return;
            }
#endif
            if (i_this->mAction == ACTION_HANDOU_MOVE) {
                return;
            }
            if (i_this->mAction == ACTION_ITAI_MOVE) {
                return;
            }
            i_this->mAction = ACTION_HANDOU_MOVE;
            i_this->mMode = MODE_HANDOU_MOVE_INIT;
            i_this->mHugeKnockback = 0;
            if (player->getCutType() == 0x11) {
                // If the player hits the Armos Knight with the Skull Hammer's side swing, knock it back much farther than normal.
                i_this->mHugeKnockback = 1;
            }
            break;
        default:
            fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
            break;
        }
    } else {
        i_this->mbIsBodyBeingHit = false;
    }
}

/* 00000784-00000D14       .text medama_atari_check__FP8am_class */
static BOOL medama_atari_check(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cCcD_Obj* hitObj = i_this->mEyeSph.GetTgHitObj();
    bool ret = false;

    if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
        return ret;
    }

    i_this->mStts.Move();
    if (!i_this->mEyeSph.ChkTgHit()) {
        return ret;
    }
    if (!hitObj) {
        return ret;
    }

    CcAtInfo atInfo;
    atInfo.pParticlePos = NULL;
    cXyz hitPos = *i_this->mEyeSph.GetTgHitPosP();

    switch (hitObj->GetAtType()) {
    case AT_TYPE_GRAPPLING_HOOK:
        if (i_this->mCurrBckIdx != AM_BCK_SLEEP && i_this->mCurrBckIdx != AM_BCK_SLEEP_LOOP) {
            if (actor->stealItemLeft > 0) {
                actor->max_health = 10;
                actor->health = 10;
                atInfo.mpObj = i_this->mEyeSph.GetTgHitObj();
                atInfo.pParticlePos = NULL;
                cc_at_check(actor, &atInfo);
                actor->max_health = 10;
                actor->health = 10;
                dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &actor->attention_info.position);
            } else {
                dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, &hitPos);
            }
            fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
        }
        break;
    case AT_TYPE_SWORD:
    case AT_TYPE_MACHETE:
    case AT_TYPE_UNK800:
    case AT_TYPE_DARKNUT_SWORD:
    case AT_TYPE_MOBLIN_SPEAR:
        fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x42);
        break;
    case AT_TYPE_BOOMERANG:
    case AT_TYPE_BOKO_STICK:
    case AT_TYPE_UNK2000:
    case AT_TYPE_STALFOS_MACE:
        fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x42);
        break;
    case AT_TYPE_LIGHT_ARROW:
        ret = true;
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 80.0f;
        actor->attention_info.flags = 0;
        break;
    case AT_TYPE_NORMAL_ARROW:
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_ICE_ARROW:
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
        ret = true;
        if (i_this->mCurrBckIdx == AM_BCK_SLEEP || i_this->mCurrBckIdx == AM_BCK_SLEEP_LOOP) {
            anm_init(i_this, AM_BCK_OKIRU, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mNeedleCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mNeedleCyl.OnAtHitBit();
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = MODE_DOUSA_OKIRU;
        } else {
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->mEyeballPos, &player->shape_angle);
            fopAcM_seStart(actor, JA_SE_CM_AM_EYE_DAMAGE, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_AM_EYE_DAMAGE, 0x42);
            i_this->mAction = ACTION_ITAI_MOVE;
            i_this->mMode = MODE_ITAI_MOVE_INIT;
        }
        break;
    default:
        dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, &hitPos);
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
        break;
    }

    if (ret) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 00000D14-00000F04       .text bomb_move_set__FP8am_classUc */
static void bomb_move_set(am_class* i_this, u8 alwaysMoveY) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->mSwallowedActorPID == fpcM_ERROR_PROCESS_ID_e) {
        return;
    }
    fopAc_ac_c* swallowedActor = fopAcM_SearchByID(i_this->mSwallowedActorPID);
    if (!swallowedActor) {
        return;
    }

    cMtx_YrotS(*calc_mtx, actor->shape_angle.y);

    cXyz mouthOffset(0.0f, 120.0f, 40.0f);
    cXyz mouthPos;
    MtxPosition(&mouthOffset, &mouthPos);
    mouthPos += actor->current.pos;

    // Pull the bomb into the Armos Knight's mouth by 50 units per frame on each axis.
    cLib_addCalc2(&swallowedActor->current.pos.x, mouthPos.x, 1.0f, 50.0f);
    if (alwaysMoveY || mouthPos.y - 10.0f < swallowedActor->current.pos.y) {
        cLib_addCalc2(&swallowedActor->current.pos.y, mouthPos.y, 1.0f, 50.0f);
    }
    cLib_addCalc2(&swallowedActor->current.pos.z, mouthPos.z, 1.0f, 50.0f);

    swallowedActor->gravity = 0.0f;
    swallowedActor->speedF = 0.0f;
    swallowedActor->speed.setall(0.0f);
    swallowedActor->current.angle.setall(0);
    swallowedActor->shape_angle.setall(0);
    swallowedActor->current.angle.y = actor->shape_angle.y;
    swallowedActor->shape_angle.y = actor->shape_angle.y;

    if (fpcM_GetName(swallowedActor) == PROC_BOMB) {
        daBomb_c* bomb = (daBomb_c*)swallowedActor;
        if (i_this->mCountDownTimers[1] == 1) {
            bomb->scale.setall(0.0f);
            bomb->setBombNoEff();
        } else if (i_this->mCountDownTimers[1] > 1) {
            bomb->scale.setall(1.0f);
        }
        bomb->setBombRestTime(100);
    } else if (fpcM_GetName(swallowedActor) == PROC_Bomb2) {
        daBomb2::Act_c* bomb2 = (daBomb2::Act_c*)swallowedActor;
        if (i_this->mCountDownTimers[1] == 1) {
            bomb2->scale.setall(0.0f);
            bomb2->remove_fuse_effect();
        } else if (i_this->mCountDownTimers[1] > 1) {
            bomb2->scale.setall(1.0f);
        }
        bomb2->set_time(100);
    }
}

/* 00000F04-00001138       .text bomb_nomi_check__FP8am_class */
static BOOL bomb_nomi_check(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();

    if (i_this->mCurrBckIdx != AM_BCK_OPEN && i_this->mCurrBckIdx != AM_BCK_OPEN_LOOP &&
        i_this->mCurrBckIdx != AM_BCK_DAMAGE && i_this->mCurrBckIdx != AM_BCK_DAMAGE_LOOP)
    {
        return FALSE;
    }

    s16 angleToPlayer = fopAcM_searchPlayerAngleY(actor);
    s16 angleDiff = cLib_distanceAngleS(actor->shape_angle.y, angleToPlayer);
    if (angleDiff > 0x2000) {
        return FALSE;
    }

    if (i_this->mMouthSph.ChkCoHit()) {
        cCcD_Obj* hitObj = i_this->mMouthSph.GetCoHitObj();
        if (hitObj) {
            fopAc_ac_c* hitActor = hitObj->GetAc();
            if (hitActor) {
                if (fpcM_GetName(hitActor) == PROC_BOMB) {
                    daBomb_c* bomb = (daBomb_c*)hitActor;
                    if (!bomb->getBombCheck_Flag() && bomb->getBombRestTime() > 1) {
                        if (i_this->mMouthPos.y - (20.0f + REG8_F(1)) < bomb->current.pos.y) {
                            // Swallow the bomb.
                            bomb->setBombCheck_Flag();
                            bomb->change_state((daBomb_c::State_e)2);
                            i_this->mSwallowedActorPID = fopAcM_GetID(bomb);
                            bomb->setBombNoHit();
                            bomb_move_set(i_this, 0);
                            i_this->mAction = ACTION_ITAI_MOVE;
                            i_this->mMode = 44;
                            return TRUE;
                        }
                    }
                } else if (fpcM_GetName(hitActor) == PROC_Bomb2) {
                    daBomb2::Act_c* bomb2 = (daBomb2::Act_c*)hitActor;
                    if (!bomb2->chk_eat() && bomb2->get_time() > 1) {
                        if (i_this->mMouthPos.y - (20.0f + REG8_F(1)) < bomb2->current.pos.y) {
                            // Swallow the bomb.
                            bomb2->set_eat();
                            i_this->mSwallowedActorPID = fopAcM_GetID(bomb2);
                            bomb2->set_no_hit();
                            bomb_move_set(i_this, 0);
                            i_this->mAction = ACTION_ITAI_MOVE;
                            i_this->mMode = 44;
                            return TRUE;
                        }
                    }
                }
            }
        }
    }

    return FALSE;
}

/* 00001138-000011E4       .text BG_check__FP8am_class */
static void BG_check(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->mAcchCir.SetWall(30.0f + REG12_F(3), 150.0f + REG12_F(4));

    actor->current.pos.y -= i_this->mCorrectionOffsetY;
    actor->old.pos.y -= i_this->mCorrectionOffsetY;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    actor->current.pos.y += i_this->mCorrectionOffsetY;
    actor->old.pos.y += i_this->mCorrectionOffsetY;
}

/* 000011E4-00001504       .text Line_check__FP8am_class4cXyz */
static BOOL Line_check(am_class* i_this, cXyz destPos) {
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

/* 0000193C-00001B00       .text medama_move__FP8am_class */
static void medama_move(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (i_this->mCurrBckIdx == AM_BCK_SLEEP || i_this->mCurrBckIdx == AM_BCK_SLEEP_LOOP) {
        i_this->mEyeRot.setall(0);
        return;
    }

    f32 diffX = actor->current.pos.x - player->current.pos.x;
    f32 diffY = actor->eyePos.y - player->current.pos.y;
    f32 diffZ = actor->current.pos.z - player->current.pos.z;

    i_this->mTargetEyeRot.y = cM_atan2s(diffX, diffZ);
    if (i_this->mTargetEyeRot.y < -0x71C) {
        i_this->mTargetEyeRot.y = -0x71C;
    } else if (i_this->mTargetEyeRot.y > 0x71C) {
        i_this->mTargetEyeRot.y = 0x71C;
    }

    i_this->mTargetEyeRot.x = cM_atan2s(diffY, std::sqrtf(diffX*diffX + diffZ*diffZ));
    if (i_this->mTargetEyeRot.x < -0x38E) {
        i_this->mTargetEyeRot.x = -0x38E;
    } else if (i_this->mTargetEyeRot.x > 0x38E) {
        i_this->mTargetEyeRot.x = 0x38E;
    }

    cLib_addCalcAngleS2(&i_this->mEyeRot.x, i_this->mTargetEyeRot.x, 1, 0x500);
    cLib_addCalcAngleS2(&i_this->mEyeRot.y, i_this->mTargetEyeRot.y, 1, 0x500);
}

/* 00001B00-00002564       .text action_dousa__FP8am_class */
static void action_dousa(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mMode) {
    case MODE_DOUSA_INIT:
        for (int i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        anm_init(i_this, AM_BCK_SLEEP_LOOP, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mMode += 1;
        // Fall-through
    case 1: {
        if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            break;
        }
        fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
        f32 f31 = 1000.0f;
        if (fopAcM_searchPlayerDistance(actor) < f31) {
#if VERSION > VERSION_DEMO
            f32 yDist = player->current.pos.y - actor->current.pos.y;
            yDist = std::sqrtf(yDist*yDist); // ???
            if (yDist > 300.0f) {
                break;
            }
#endif
            if (Line_check(i_this, player->current.pos)) {
                anm_init(i_this, AM_BCK_OKIRU, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(actor, JA_SE_CV_AM_AWAKE, 0);
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                i_this->mNeedleCyl.OnAtSetBit();
                i_this->mNeedleCyl.OnAtHitBit();
                i_this->mMode += 1; // MODE_DOUSA_OKIRU
            }
        }
        break;
    }
    case MODE_DOUSA_OKIRU:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mMode += 1;
        // Fall-through
    case 3:
        if (i_this->mCurrBckIdx != AM_BCK_CLOSE && i_this->mCurrBckIdx != AM_BCK_CLOSE_LOOP) {
            if (i_this->mCurrBckIdx != AM_BCK_DAMAGE_END) {
                fopAcM_seStart(actor, JA_SE_CM_AM_NEEDLE_OUT, 0);
                fopAcM_seStart(actor, JA_SE_CM_AM_MOUTH_CLOSE, 0);
            }
            anm_init(i_this, AM_BCK_CLOSE, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mCountDownTimers[2] = 6;
        }
        i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(actor);
        i_this->mMode += 1;
        // Fall-through
    case 4: {
        if (i_this->mCountDownTimers[2] == 1) {
            i_this->mNeedleCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mNeedleCyl.OnAtHitBit();
        }
        if (i_this->mCountDownTimers[2] != 0) {
            break;
        }
        if (i_this->mType & 1) {
            f32 xDist = actor->current.pos.x - i_this->mSpawnPos.x;
            f32 zDist = actor->current.pos.z - i_this->mSpawnPos.z;
            f32 xzDist = std::sqrtf(xDist*xDist + zDist*zDist);
            if (xzDist > i_this->mAreaRadius) {
                i_this->mAction = ACTION_MODORU_MOVE;
                i_this->mMode = MODE_MODORU_MOVE_INIT;
                return;
            }
        } else {
            f32 f31 = 2000.0f;
            if (fopAcM_searchPlayerDistance(actor) > f31) {
                i_this->mMode = MODE_DOUSA_SLEEP_INIT;
                break;
            }
#if VERSION > VERSION_DEMO
            f32 yDist = player->current.pos.y - actor->current.pos.y;
            yDist = std::sqrtf(yDist*yDist); // ???
            if (yDist > 300.0f) {
                i_this->mMode = MODE_DOUSA_SLEEP_INIT;
                break;
            }
#endif
        }
        s16 yRotDiff = cLib_distanceAngleS(actor->shape_angle.y, i_this->mTargetAngleY);
        if (yRotDiff < 0x100) {
            i_this->mMode += 1;
        }
        break;
    }
    case 5:
        actor->speedF = 30.0f;
        actor->gravity = -11.0f;
        actor->speed.y = 40.0f;
        fopAcM_monsSeStart(actor, JA_SE_CV_AM_JUMP, 0);
        if (!Line_check(i_this, player->current.pos) || player->getDamageWaitTimer() != 0) {
            actor->speedF = 0.0f;
        }
        i_this->mMode += 1;
        break;
    case 6:
        if (i_this->mCurrBckIdx == AM_BCK_CLOSE) {
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, AM_BCK_CLOSE_LOOP, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
        }
        if (!i_this->mAcch.ChkGroundHit()) {
            break;
        }
        fopAcM_seStart(actor, JA_SE_CM_AM_JUMP, 0);
        i_this->mSmokeCbs[0].remove();
        dComIfGp_particle_setToon(
            dPa_name::ID_SCENE_A125, &i_this->mWaistPos, &actor->shape_angle, NULL,
            0xB9, &i_this->mSmokeCbs[0], fopAcM_GetRoomNo(actor)
        );
        dComIfGp_getVibration().StartShock(3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        actor->speedF = 0.0f;
        i_this->mCountDownTimers[0] = 0;
        if (i_this->mCountUpTimers[0] < 2) {
            i_this->mCountDownTimers[0] = 10;
        }
        i_this->mMode += 1;
        // Fall-through
    case 7:
        if (i_this->mCountDownTimers[0] != 0) {
            break;
        }
        i_this->mCountUpTimers[0]++;
        if (i_this->mCountUpTimers[0] > 2) {
            i_this->mCountDownTimers[0] = 100;
            i_this->mCountUpTimers[0] = 0;
            anm_init(i_this, AM_BCK_DAMAGE, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_seStart(actor, JA_SE_CM_AM_NEEDLE_IN, 0);
            fopAcM_seStart(actor, JA_SE_CM_AM_MOUTH_OPEN, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_AM_OPEN_MOUTH, 0);
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->mNeedleCyl.OffAtSetBit();
#if VERSION == VERSION_DEMO
            if (i_this->m033C_demo == NULL)
#else
            if (i_this->mSmokeCbs[2].getEmitter() == NULL)
#endif
            {
#if VERSION == VERSION_DEMO
                i_this->mSmokeCbs[2].remove();
                i_this->m033C_demo = 
#endif
                dComIfGp_particle_setToon(
                    dPa_name::ID_SCENE_A154, &i_this->mWaistPos, &actor->shape_angle, NULL,
                    0xB9, &i_this->mSmokeCbs[2], fopAcM_GetRoomNo(actor)
                );
            }
            i_this->mMode = 8;
        } else {
            i_this->mMode = 3;
        }
        break;
    case 8:
        if (i_this->mAcch.ChkGroundHit()) {
            actor->gravity = -6.0f;
            actor->speed.y = 15.0f;
            fopAcM_seStart(actor, JA_SE_CM_AM_JUMP_S, 0);
            i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(actor);
        }
        if (i_this->mCountDownTimers[0] == 0) {
#if VERSION == VERSION_DEMO
            if (i_this->m033C_demo) {
                i_this->m033C_demo->becomeInvalidEmitter();
                i_this->m033C_demo = NULL;
                i_this->mSmokeCbs[2].remove();
            }
#else
            i_this->mSmokeCbs[2].remove();
#endif
            i_this->mMode = 3;
        }
        break;
    case MODE_DOUSA_SLEEP_INIT:
        anm_init(i_this, AM_BCK_SLEEP, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_seStart(actor, JA_SE_CM_AM_NEEDLE_IN, 0);
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        actor->attention_info.flags = 0;
        i_this->mMode += 1;
        break;
    case MODE_DOUSA_SLEEP_MAIN:
        if (i_this->mpMorf->isStop()) {
            i_this->mMode = 0;
        }
        break;
    }

    medama_move(i_this);

    if (i_this->mMode != 2 && medama_atari_check(i_this)) {
#if VERSION == VERSION_DEMO
        if (i_this->m033C_demo) {
            i_this->m033C_demo->becomeInvalidEmitter();
            i_this->m033C_demo = NULL;
            i_this->mSmokeCbs[2].remove();
        }
#else
        i_this->mSmokeCbs[2].remove();
#endif
    } else if (bomb_nomi_check(i_this)) {
#if VERSION == VERSION_DEMO
        if (i_this->m033C_demo) {
            i_this->m033C_demo->becomeInvalidEmitter();
            i_this->m033C_demo = NULL;
            i_this->mSmokeCbs[2].remove();
        }
#else
        i_this->mSmokeCbs[2].remove();
#endif
    }
}

/* 00002564-000028C4       .text action_modoru_move__FP8am_class */
static void action_modoru_move(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->mMode) {
    case MODE_MODORU_MOVE_INIT: {
        anm_init(i_this, AM_BCK_CLOSE_LOOP, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mNeedleCyl.OnAtSetBit();
        i_this->mNeedleCyl.OnAtHitBit();
        actor->gravity = -11.0f;
        actor->speed.y = 40.0f;
        actor->speedF = 15.0f;
        fopAcM_monsSeStart(actor, JA_SE_CV_AM_JUMP, 0x42);

        f32 xDistToSpawn = i_this->mSpawnPos.x - actor->current.pos.x;
        f32 zDistToSpawn = i_this->mSpawnPos.z - actor->current.pos.z;
        i_this->mTargetAngleY = cM_atan2s(xDistToSpawn, zDistToSpawn);
        i_this->mMode += 1;
        break;
    }
    case MODE_MODORU_MOVE_MAIN: {
        f32 xDistToSpawn = i_this->mSpawnPos.x - actor->current.pos.x;
        f32 zDistToSpawn = i_this->mSpawnPos.z - actor->current.pos.z;
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->mSmokeCbs[0].remove();
            dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A125, &i_this->mWaistPos, &actor->shape_angle, NULL,
                0xB9, &i_this->mSmokeCbs[0], fopAcM_GetRoomNo(actor)
            );

            dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            fopAcM_seStart(actor, JA_SE_CM_AM_JUMP, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_AM_JUMP, 0x42);

            actor->speed.y = 40.0f;
            actor->speedF = 15.0f;
            i_this->mTargetAngleY = cM_atan2s(xDistToSpawn, zDistToSpawn);
        }

        f32 xzDist = std::sqrtf(SQUARE(xDistToSpawn) + SQUARE(zDistToSpawn));
        if (xzDist < 20.0f) {
            i_this->mTargetAngleY = i_this->mSpawnRotY;
            actor->speedF = 0.0f;
            i_this->mMode += 1;
        }
        break;
    }
    case MODE_MODORU_MOVE_END: {
        s16 angleDiff = cLib_distanceAngleS(actor->shape_angle.y, i_this->mTargetAngleY);
        if (angleDiff < 0x100) {
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->mNeedleCyl.OffAtSetBit();
            actor->attention_info.flags = 0;
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = MODE_DOUSA_INIT;
        }
        break;
    }
    }
}

/* 000028C4-00002A6C       .text action_handou_move__FP8am_class */
static void action_handou_move(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();
    switch (i_this->mMode) {
    case MODE_HANDOU_MOVE_INIT: {
        actor->speedF = 20.0f;
        s16 angleToPlayer = fopAcM_searchPlayerAngleY(actor);
        actor->current.angle.y = angleToPlayer + 0x8000;
        if (i_this->mHugeKnockback == 1) {
            actor->current.angle.y = player->shape_angle.y - 0x4000;
            actor->speedF = 40.0f;
        }
        i_this->mTargetAngleY = actor->current.angle.y;
        if (i_this->mCurrBckIdx != AM_BCK_CLOSE && i_this->mCurrBckIdx != AM_BCK_CLOSE_LOOP) {
            fopAcM_seStart(actor, JA_SE_CM_AM_NEEDLE_OUT, 0);
            fopAcM_seStart(actor, JA_SE_CM_AM_MOUTH_CLOSE, 0);
            anm_init(i_this, AM_BCK_CLOSE, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        i_this->mMode += 1;
        // Fall-through
    }
    case MODE_HANDOU_MOVE_MAIN: {
        cLib_addCalc0(&actor->speedF, 0.8f, 2.0f);
        if (actor->speedF < 0.1f) {
            actor->speedF = 0.0f;
            i_this->mCountDownTimers[2] = 6;
            actor->current.angle.y = actor->shape_angle.y;
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = 3;
        }
        break;
    }
    }
}

/* 00002A6C-000034F4       .text action_itai_move__FP8am_class */
static void action_itai_move(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->mMode) {
    case MODE_ITAI_MOVE_INIT:
        i_this->mEyeRot.setall(0);
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        actor->speedF = -20.0f;
        actor->current.angle.y = fopAcM_searchPlayerAngleY(actor);
        i_this->mTargetAngleY = actor->current.angle.y;
        fopAcM_seStart(actor, JA_SE_CM_AM_NEEDLE_IN, 0);
        anm_init(i_this, AM_BCK_DAMAGE, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mMode += 1;
        // Fall-through
    case 41:
        cLib_addCalc0(&actor->speedF, 0.8f, 2.0f);
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mCountDownTimers[0] = 100;
        actor->speedF = 0.0f;
        anm_init(i_this, AM_BCK_DAMAGE_LOOP, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mMode += 1;
        break;
    case 42:
        if (i_this->mCountDownTimers[0] != 0) {
            break;
        }
        anm_init(i_this, AM_BCK_DAMAGE_END, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_seStart(actor, JA_SE_CM_AM_NEEDLE_OUT, 0);
        fopAcM_seStart(actor, JA_SE_CM_AM_MOUTH_CLOSE, 0);
        i_this->mMode += 1;
        break;
    case 43:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mNeedleCyl.OnAtSetBit();
        i_this->mNeedleCyl.OnAtHitBit();
        i_this->mCountUpTimers[0] = 0;
        i_this->mAction = ACTION_DOUSA;
        i_this->mMode = 3;
        break;
    case 44:
        i_this->mSmokeCbs[3].remove();
        i_this->mStts.SetWeight(0xFF);
        dComIfGp_particle_setToon(
            dPa_name::ID_SCENE_A155, &i_this->mJawPos, &actor->shape_angle, NULL,
            0xB9, &i_this->mSmokeCbs[3], fopAcM_GetRoomNo(actor)
        );
        fopAcM_seStart(actor, JA_SE_CM_AM_MOUTH_CLOSE, 0);
        anm_init(i_this, AM_BCK_BOM_NOMI, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        mDoAud_onEnemyDamage();
        i_this->mEyeRot.setall(0);
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mCountDownTimers[1] = 10;
        i_this->mMode += 1;
        // Fall-through
    case 45:
        bomb_move_set(i_this, 0);
        if (i_this->mpMorf->checkFrame(3.0f)) {
            fopAcM_seStart(actor, JA_SE_CM_AM_EAT_BOMB, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_AM_EAT_BOMB, 0);
        }
        if (i_this->mpMorf->checkFrame(6.0f)) {
            i_this->mSmokeCbs[1].remove();
            i_this->mNeedleCyl.OnAtSetBit();
            i_this->mNeedleCyl.OnAtHitBit();
            dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A126, &i_this->mJawPos, &actor->shape_angle, NULL,
                0xB9, &i_this->mSmokeCbs[1], fopAcM_GetRoomNo(actor)
            );
            i_this->m033C = dComIfGp_particle_set(dPa_name::ID_SCENE_8157, &i_this->mJawPos);
            i_this->m0340 = dComIfGp_particle_set(dPa_name::ID_SCENE_8156, &i_this->mJawPos);
        }

        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mCountDownTimers[0] = 100;
        i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(actor);
        i_this->mMode += 1;
        break;
    case 46:
        bomb_move_set(i_this, 1);
        actor->shape_angle.y += 0x1000;
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->mSmokeCbs[0].remove();
            fopAcM_seStart(actor, JA_SE_CM_AM_JUMP, 0);
            dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A125, &i_this->mWaistPos, &actor->shape_angle, NULL,
                0xB9, &i_this->mSmokeCbs[0], fopAcM_GetRoomNo(actor)
            );
            dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            fopAcM_seStart(actor, JA_SE_CM_AM_JUMP_L, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_AM_JITABATA, 0);
            actor->speed.y = 25.0f;
            actor->gravity = -10.0f;
            actor->speedF = 10.0f;
        }

        if (i_this->mCountDownTimers[0] != 0) {
            break;
        }
        anm_init(i_this, AM_BCK_DEAD, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8127, &i_this->mWaistPos);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8128, &i_this->mWaistPos);

        fopAcM_seStart(actor, JA_SE_CM_AM_BEF_EXPLODE, 0);
        i_this->mTargetAngleY = actor->current.angle.y;

        if (i_this->m033C) {
            i_this->m033C->becomeInvalidEmitter();
            i_this->m033C = NULL;
        }
        if (i_this->m0340) {
            i_this->m0340->becomeInvalidEmitter();
            i_this->m0340 = NULL;
        }
        actor->speedF = 0.0f;
        i_this->mMode += 1;
        break;
    case 47:
        bomb_move_set(i_this, 1);
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        cXyz centerPos = actor->current.pos;
        centerPos.y += 150.0f;
        if (i_this->mSwallowedActorPID != fpcM_ERROR_PROCESS_ID_e) {
            fopAc_ac_c* swallowedActor = fopAcM_SearchByID(i_this->mSwallowedActorPID);
            if (swallowedActor) {
                swallowedActor->scale.setall(1.0f);
                if (fpcM_GetName(swallowedActor) == PROC_BOMB) {
                    daBomb_c* bomb = (daBomb_c*)swallowedActor;
                    bomb->setBombRestTime(1);
                } else if (fpcM_GetName(swallowedActor) == PROC_Bomb2) {
                    daBomb2::Act_c* bomb2 = (daBomb2::Act_c*)swallowedActor;
                    bomb2->set_time(1);
                }
            }
        }

        fopAcM_seStart(actor, JA_SE_CM_AM_EXPLODE, 0);
        fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0);

        fopAcM_createDisappear(actor, &centerPos, 5, daDisItem_IBALL_e);
        fopAcM_onActor(actor);
        fopAcM_delete(actor);
        break;
    }

    if (i_this->m033C) {
        i_this->m033C->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
    }
    if (i_this->m0340) {
        i_this->m0340->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
    }

    if (i_this->mMode == 41 || i_this->mMode == 42) {
        bomb_nomi_check(i_this);
    }
}

/* 000034F4-000039A4       .text daAM_Execute__FP8am_class */
static BOOL daAM_Execute(am_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    fopAcM_setGbaName(actor, dItem_BOW_e, 0xC, 0x2A);

    if (enemy_ice(&i_this->mEnemyIce)) {
        J3DModel* model = i_this->mpMorf->getModel();
        model->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpMorf->calc();
        return TRUE;
    }

    for (int i = 0; i < ARRAY_SIZE(i_this->mCountDownTimers); i++) {
        if (i_this->mCountDownTimers[i] != 0) {
            i_this->mCountDownTimers[i]--;
        }
    }

    switch (i_this->mAction) {
    case ACTION_DOUSA:
        action_dousa(i_this);
        break;
    case ACTION_MODORU_MOVE:
        action_modoru_move(i_this);
        break;
    case ACTION_HANDOU_MOVE:
        action_handou_move(i_this);
        break;
    case ACTION_ITAI_MOVE:
        action_itai_move(i_this);
        break;
    }

    if (i_this->mAction != ACTION_ITAI_MOVE && i_this->mSpawnPosY - 1500.0f > actor->current.pos.y) {
        anm_init(i_this, AM_BCK_DEAD, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);

        dComIfGp_particle_set(dPa_name::ID_SCENE_8127, &i_this->mWaistPos);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8128, &i_this->mWaistPos);

        fopAcM_seStart(actor, JA_SE_CM_AM_BEF_EXPLODE, 0);

        i_this->mTargetAngleY = actor->current.angle.y;

        if (i_this->m033C) {
            i_this->m033C->becomeInvalidEmitter();
            i_this->m033C = NULL;
        }
        if (i_this->m0340) {
            i_this->m0340->becomeInvalidEmitter();
            i_this->m0340 = NULL;
        }

        actor->speedF = 0.0f;
        i_this->mAction = ACTION_ITAI_MOVE;
        i_this->mMode = 47;
    }

    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mTargetAngleY, 1, 0x500);
    if (i_this->mMode != 46 && i_this->mMode != 47 && i_this->mMode != 31) {
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x500);
    }

    if (i_this->mCountDownTimers[1] == 0) {
        i_this->mpMorf->play(NULL, 0, 0);
    }

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    cXyz offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = actor->speedF;
    cXyz rotOffset;
    MtxPosition(&offset, &rotOffset);
    actor->speed.x = rotOffset.x;
    actor->speed.z = rotOffset.z;
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -100.0f) {
        actor->speed.y = -100.0f;
    }

    body_atari_check(i_this);

    actor->attention_info.position = actor->current.pos;
    actor->attention_info.position.y += 330.0f;
    actor->eyePos = actor->current.pos;
    actor->eyePos.y += 250.0f;

    cXyz needlePos = actor->current.pos;

    i_this->mEyeSph.SetC(i_this->mEyeballPos);
    i_this->mEyeSph.SetR(60.0f);
    dComIfG_Ccsp()->Set(&i_this->mEyeSph);

    i_this->mMouthSph.SetC(i_this->mMouthPos);
    i_this->mMouthSph.SetR(100.0f);
    dComIfG_Ccsp()->Set(&i_this->mMouthSph);

    i_this->mBodyCyl.SetC(actor->current.pos);
    i_this->mBodyCyl.SetH(300.0f);
    i_this->mBodyCyl.SetR(80.0f);
    dComIfG_Ccsp()->Set(&i_this->mBodyCyl);

    needlePos.y += 40.0f;
    i_this->mNeedleCyl.SetC(needlePos);
    i_this->mNeedleCyl.SetH(30.0f);
    i_this->mNeedleCyl.SetR(130.0f);
    dComIfG_Ccsp()->Set(&i_this->mNeedleCyl);

    fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
    BG_check(i_this);
    draw_SUB(i_this);

    return TRUE;
}

/* 000039A4-000039AC       .text daAM_IsDelete__FP8am_class */
static BOOL daAM_IsDelete(am_class* i_this) {
    return TRUE;
}

/* 000039AC-00003A84       .text daAM_Delete__FP8am_class */
static BOOL daAM_Delete(am_class* i_this) {
    dComIfG_resDelete(&i_this->mPhase, "AM");

    for (int i = 0; i < 4; i++) {
        i_this->mSmokeCbs[i].remove();
    }
#if VERSION == VERSION_DEMO
    if (i_this->m033C_demo) {
        i_this->m033C_demo->becomeInvalidEmitter();
        i_this->m033C_demo = NULL;
    }
#else
    i_this->mSmokeCbs[2].remove();
#endif
    if (i_this->m033C) {
        i_this->m033C->becomeInvalidEmitter();
        i_this->m033C = NULL;
    }
    if (i_this->m0340) {
        i_this->m0340->becomeInvalidEmitter();
        i_this->m0340 = NULL;
    }

    return TRUE;
}

/* 00003A84-00003C00       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    am_class* a_this = (am_class*)i_this;

    a_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("AM", AM_BDL_AM),
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("AM", AM_BCK_SLEEP_LOOP),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x00000000,
        0x11020203
    );
    if (!a_this->mpMorf || !a_this->mpMorf->getModel()) {
        return FALSE;
    }

    a_this->mpMorf->getModel()->setUserArea((u32)a_this);
    for (u16 i = 0; i < a_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        a_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }

    static Vec cyl2_eye_offset[] = {
        {0.0f, 0.0f, 70.0f},
        {0.0f, 0.0f, 80.0f},
    };
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ JntHitType_CYL2_e,
            /* mJointIndex */ 0x05, // hitomi (pupil) joint
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ cyl2_eye_offset,
        },
    };
    a_this->mEyeJntHit = JntHit_create(a_this->mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (a_this->mEyeJntHit) {
        i_this->jntHit = a_this->mEyeJntHit;
    } else {
        return FALSE;
    }

    return TRUE;
}

/* 00003C00-00003F5C       .text daAM_Create__FP10fopAc_ac_c */
static cPhs_State daAM_Create(fopAc_ac_c* i_this) {
    fopAcM_SetupActor(i_this, am_class);

    am_class* a_this = (am_class*)i_this;

    cPhs_State phase_state = dComIfG_resLoad(&a_this->mPhase, "AM");
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x1C80)) {
            return cPhs_ERROR_e;
        }

        i_this->stealItemLeft = 3;

        a_this->mSmokeCbs[0].setRateOff(0);
        a_this->mSmokeCbs[1].setRateOff(0);
        a_this->mSmokeCbs[3].setRateOff(0);

        a_this->mType = (fopAcM_GetParam(a_this) >> 0x00) & 0xFF;
        a_this->mPrmAreaRadius = (fopAcM_GetParam(a_this) >> 0x08) & 0xFF;
        a_this->mStartsInactive = (fopAcM_GetParam(a_this) >> 0x10) & 0xFF;
        a_this->mSwitch = (fopAcM_GetParam(a_this) >> 0x18) & 0xFF;

        if (a_this->mType == 0xFF) {
            a_this->mType = 0;
        }
        if (a_this->mStartsInactive == 0xFF) {
            a_this->mStartsInactive = 0;
        }
        if (REG8_S(9) != 0) {
            a_this->mType = 1;
        }
        if (a_this->mPrmAreaRadius == 0xFF || a_this->mPrmAreaRadius == 0) {
            a_this->mAreaRadius = 400.0f;
        } else {
            a_this->mAreaRadius = a_this->mPrmAreaRadius * 100.0f;
        }
        a_this->mSpawnPosY = i_this->current.pos.y;
        a_this->mSwallowedActorPID = fpcM_ERROR_PROCESS_ID_e;

        if (a_this->mStartsInactive == 0 && a_this->mSwitch != 0xFF && dComIfGs_isSwitch(a_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            // When mStartsInactive is 0, the Armos Knight starts active and attacking the player.
            // mSwitch being set disables it from spawning again in the future.
            return cPhs_ERROR_e;
        }
        if (a_this->mStartsInactive == 1 && a_this->mSwitch != 0xFF && !dComIfGs_isSwitch(a_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            // When mStartsInactive is 1, the Armos Knight is initially inactive.
            // mSwitch being set causes it to become active and attack the player.
            fopAcM_OffStatus(i_this, fopAcStts_SHOWMAP_e);
        }

        i_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("amos", 0);
        i_this->max_health = 10;
        i_this->health = 10;

        fopAcM_SetMtx(i_this, a_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(i_this, -100.0f, -10.0f, -80.0f, 120.0f, 400.0f, 100.0f);

        i_this->attention_info.flags = 0;

        a_this->mAcch.Set(
            fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this),
            i_this, 1, &a_this->mAcchCir, fopAcM_GetSpeed_p(i_this)
        );
        a_this->mStts.Init(254, 1, i_this);

        i_this->gravity = -10.0f;

        a_this->mEnemyIce.mpActor = i_this;
        a_this->mEnemyIce.mWallRadius = 80.0f;
        a_this->mEnemyIce.mCylHeight = 300.0f;

        static dCcD_SrcSph eye_co_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW | AT_TYPE_GRAPPLING_HOOK,
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
                /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGSphS
            {{
                /* Center */ {0.0f, 0.0f, 0.0f},
                /* Radius */ 15.0f,
            }},
        };
        a_this->mEyeSph.Set(eye_co_sph_src);
        a_this->mEyeSph.SetStts(&a_this->mStts);

        static dCcD_SrcSph mouth_co_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsOther_e | cCcD_CoSPrm_NoCrr_e,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ 0,
                /* SrcGObjTg Spl     */ 0,
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
        a_this->mMouthSph.Set(mouth_co_sph_src);
        a_this->mMouthSph.SetStts(&a_this->mStts);

        static dCcD_SrcCyl body_co_cyl_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
                /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
                /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGCylS
            {{
                /* Center */ {0.0f, 0.0f, 0.0f},
                /* Radius */ 15.0f,
                /* Height */ 0.0f,
            }},
        };
        a_this->mBodyCyl.Set(body_co_cyl_src);
        a_this->mBodyCyl.SetStts(&a_this->mStts);

        static dCcD_SrcCyl sword_co_cyl_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
                /* SrcObjAt  Atp     */ 2,
                /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK6,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGCylS
            {{
                /* Center */ {0.0f, 0.0f, 0.0f},
                /* Radius */ 15.0f,
                /* Height */ 0.0f,
            }},
        };
        a_this->mNeedleCyl.Set(sword_co_cyl_src);
        a_this->mNeedleCyl.SetStts(&a_this->mStts);

        a_this->mNeedleCyl.OffAtSetBit();
        a_this->mNeedleCyl.OffAtSetBit();

        a_this->mTargetAngleY = i_this->current.angle.y;
        a_this->mSpawnPos = i_this->current.pos;
        a_this->mSpawnRotY = i_this->current.angle.y;

        draw_SUB(a_this);
    }

    return phase_state;
}

static actor_method_class l_daAM_Method = {
    (process_method_func)daAM_Create,
    (process_method_func)daAM_Delete,
    (process_method_func)daAM_Execute,
    (process_method_func)daAM_IsDelete,
    (process_method_func)daAM_Draw,
};

actor_process_profile_definition g_profile_AM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_AM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(am_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_AM,
    /* Actor SubMtd */ &l_daAM_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
