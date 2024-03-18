/**
 * d_a_am.cpp
 * Enemy - Armos Knight
 */

#include "d/actor/d_a_am.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/J3DGraphAnimator/J3DNode.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_procname.h"
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

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

enum Action {
    ACTION_DOUSA       = 0x0,
    ACTION_MODORU_MOVE = 0x1,
    ACTION_HANDOU_MOVE = 0x2,
    ACTION_ITAI_MOVE   = 0x3,
};

enum AM_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    AM_BAS_BOM_NOMI=0x5,
    AM_BAS_BOM_NOMI2=0x6,
    AM_BAS_CLOSE=0x7,
    AM_BAS_CLOSE_LOOP=0x8,
    AM_BAS_DAMAGE=0x9,
    AM_BAS_DAMAGE_END=0xA,
    AM_BAS_DAMAGE_LOOP=0xB,
    AM_BAS_DEAD=0xC,
    AM_BAS_OKIRU=0xD,
    AM_BAS_OPEN=0xE,
    AM_BAS_OPEN_LOOP=0xF,
    AM_BAS_SLEEP=0x10,
    AM_BAS_SLEEP_LOOP=0x11,

    /* BCK */
    AM_BCK_BOM_NOMI=0x14,
    AM_BCK_CLOSE=0x15,
    AM_BCK_CLOSE_LOOP=0x16,
    AM_BCK_DAMAGE=0x17,
    AM_BCK_DAMAGE_END=0x18,
    AM_BCK_DAMAGE_LOOP=0x19,
    AM_BCK_DEAD=0x1A,
    AM_BCK_OKIRU=0x1B,
    AM_BCK_OPEN=0x1C,
    AM_BCK_OPEN_LOOP=0x1D,
    AM_BCK_SLEEP=0x1E,
    AM_BCK_SLEEP_LOOP=0x1F,

    /* BDL */
    AM_BDL_AM=0x22,
};

/* 00000078-0000021C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        am_class* i_this = (am_class*)model->getUserArea();
        if (i_this) {
            if (jntNo >= 1 && jntNo <= 4) {
                cMtx_copy(model->getAnmMtx(jntNo), *calc_mtx);
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
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->scale);
    mDoMtx_stack_c::transS(i_this->current.pos);
    cMtx_YrotM(mDoMtx_stack_c::get(), i_this->shape_angle.y);
    cMtx_XrotM(mDoMtx_stack_c::get(), i_this->shape_angle.x);
    cMtx_ZrotM(mDoMtx_stack_c::get(), i_this->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    i_this->mpMorf->calc();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
}

/* 000002E4-00000378       .text daAM_Draw__FP8am_class */
static BOOL daAM_Draw(am_class* i_this) {
    g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &i_this->tevStr);

    dSnap_RegistFig(DSNAP_TYPE_AM, i_this, 1.0f, 1.0f, 1.0f);

    i_this->mpMorf->entryDL();

    dComIfGd_setSimpleShadow2(
        &i_this->current.pos, i_this->mAcch.GetGroundH(), 90.0f, i_this->mAcch.m_gnd,
        0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );

    return TRUE;
}

/* 00000378-000004A4       .text anm_init__FP8am_classifUcfi */
static void anm_init(am_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->mCurrBckIdx = bckFileIdx;
    if (soundFileIdx >= 0) {
        void* soundAnm = dComIfG_getObjectRes("AM", soundFileIdx);
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("AM", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, soundAnm);
    } else {
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("AM", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000004A4-00000784       .text body_atari_check__FP8am_class */
static void body_atari_check(am_class* i_this) {
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
            fopAcM_seStart(i_this, JA_SE_LK_SW_HIT_S, 0x42);
            break;
        case AT_TYPE_BOOMERANG:
        case AT_TYPE_BOKO_STICK:
        case AT_TYPE_UNK2000:
        case AT_TYPE_STALFOS_MACE:
            fopAcM_seStart(i_this, JA_SE_LK_W_WEP_HIT, 0x42);
            break;
        case AT_TYPE_SKULL_HAMMER:
            fopAcM_seStart(i_this, JA_SE_LK_HAMMER_HIT, 0x42);
#if VERSION != VERSION_JPN
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
            i_this->mState = 0x1E;
            i_this->mHugeKnockback = 0;
            if (player->getCutType() == 0x11) {
                // If the player hits the Armos Knight with the Skull Hammer's side swing, knock it back much farther than normal.
                i_this->mHugeKnockback = 1;
            }
            break;
        default:
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
            break;
        }
    } else {
        i_this->mbIsBodyBeingHit = false;
    }
}

/* 00000784-00000D14       .text medama_atari_check__FP8am_class */
static BOOL medama_atari_check(am_class* i_this) {
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
            if (i_this->stealItemLeft > 0) {
                i_this->max_health = 10;
                i_this->health = 10;
                atInfo.mpObj = i_this->mEyeSph.GetTgHitObj();
                atInfo.pParticlePos = NULL;
                cc_at_check(i_this, &atInfo);
                i_this->max_health = 10;
                i_this->health = 10;
                dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &i_this->attention_info.position);
            } else {
                dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, &hitPos);
            }
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
        }
        break;
    case AT_TYPE_SWORD:
    case AT_TYPE_MACHETE:
    case AT_TYPE_UNK800:
    case AT_TYPE_DARKNUT_SWORD:
    case AT_TYPE_MOBLIN_SPEAR:
        fopAcM_seStart(i_this, JA_SE_LK_SW_HIT_S, 0x42);
        break;
    case AT_TYPE_BOOMERANG:
    case AT_TYPE_BOKO_STICK:
    case AT_TYPE_UNK2000:
    case AT_TYPE_STALFOS_MACE:
        fopAcM_seStart(i_this, JA_SE_LK_W_WEP_HIT, 0x42);
        break;
    case AT_TYPE_LIGHT_ARROW:
        ret = true;
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 80.0f;
        i_this->attention_info.flags = 0;
        break;
    case AT_TYPE_NORMAL_ARROW:
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_ICE_ARROW:
        // Using the fopAcM_seStart inline multiple times in a single case makes the codegen not match.
        // fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
        mDoAud_seStart(JA_SE_LK_MS_WEP_HIT, &i_this->eyePos, 0x42, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        ret = true;
        if (i_this->mCurrBckIdx == AM_BCK_SLEEP || i_this->mCurrBckIdx == AM_BCK_SLEEP_LOOP) {
            anm_init(i_this, AM_BCK_OKIRU, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
            i_this->attention_info.flags = fopAc_Attn_LOCKON_ENEMY_e;
            i_this->mNeedleCyl.OnAtSPrmBit(AT_SPRM_SET);
            i_this->mNeedleCyl.OnAtHitBit();
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 2;
        } else {
            dComIfGp_particle_set(0x10, &i_this->mEyeballPos, &player->shape_angle);
            // fopAcM_seStart(i_this, JA_SE_CM_AM_EYE_DAMAGE, 0);
            mDoAud_seStart(JA_SE_CM_AM_EYE_DAMAGE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_AM_EYE_DAMAGE, 0x42);
            i_this->mAction = ACTION_ITAI_MOVE;
            i_this->mState = 0x28;
        }
        break;
    default:
        dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, &hitPos);
        fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
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
    if (i_this->mSwallowedActorPID == fpcM_ERROR_PROCESS_ID_e) {
        return;
    }
    fopAc_ac_c* swallowedActor = fopAcM_SearchByID(i_this->mSwallowedActorPID);
    if (!swallowedActor) {
        return;
    }

    cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);

    cXyz mouthOffset(0.0f, 120.0f, 40.0f);
    cXyz mouthPos;
    MtxPosition(&mouthOffset, &mouthPos);
    mouthPos += i_this->current.pos;

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
    swallowedActor->current.angle.y = i_this->shape_angle.y;
    swallowedActor->shape_angle.y = i_this->shape_angle.y;

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
    fopAc_ac_c* actor = i_this;
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
                        f32 offsetY = 20.0f + g_regHIO.mChild[8].mFloatRegs[1];
                        if (i_this->mMouthPos.y - offsetY < bomb->current.pos.y) {
                            // Swallow the bomb.
                            bomb->setBombCheck_Flag();
                            bomb->change_state((daBomb_c::State_e)2);
                            i_this->mSwallowedActorPID = fopAcM_GetID(bomb);
                            bomb->setBombNoHit();
                            bomb_move_set(i_this, 0);
                            i_this->mAction = ACTION_ITAI_MOVE;
                            i_this->mState = 0x2C;
                            return TRUE;
                        }
                    }
                } else if (fpcM_GetName(hitActor) == PROC_Bomb2) {
                    daBomb2::Act_c* bomb2 = (daBomb2::Act_c*)hitActor;
                    if (!bomb2->chk_eat() && bomb2->get_time() > 1) {
                        f32 offsetY = 20.0f + g_regHIO.mChild[8].mFloatRegs[1];
                        if (i_this->mMouthPos.y - offsetY < bomb2->current.pos.y) {
                            // Swallow the bomb.
                            bomb2->set_eat();
                            i_this->mSwallowedActorPID = fopAcM_GetID(bomb2);
                            bomb2->set_no_hit();
                            bomb_move_set(i_this, 0);
                            i_this->mAction = ACTION_ITAI_MOVE;
                            i_this->mState = 0x2C;
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
    f32 halfHeight = 30.0f + g_regHIO.mChild[12].mFloatRegs[3];
    f32 radius = 150.0f + g_regHIO.mChild[12].mFloatRegs[4];
    i_this->mAcchCir.SetWall(halfHeight, radius);

    i_this->current.pos.y -= i_this->mCorrectionOffsetY;
    i_this->old.pos.y -= i_this->mCorrectionOffsetY;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    i_this->current.pos.y += i_this->mCorrectionOffsetY;
    i_this->old.pos.y += i_this->mCorrectionOffsetY;
}

/* 000011E4-00001504       .text Line_check__FP8am_class4cXyz */
static BOOL Line_check(am_class* i_this, cXyz destPos) {
    fopAc_ac_c* actor = i_this;
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
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (i_this->mCurrBckIdx == AM_BCK_SLEEP || i_this->mCurrBckIdx == AM_BCK_SLEEP_LOOP) {
        i_this->mEyeRot.setall(0);
        return;
    }

    f32 diffX = i_this->current.pos.x - player->current.pos.x;
    f32 diffY = i_this->eyePos.y - player->current.pos.y;
    f32 diffZ = i_this->current.pos.z - player->current.pos.z;

    i_this->mTargetEyeRot.y = cM_atan2s(diffX, diffZ);
    if (i_this->mTargetEyeRot.y < -0x71C) {
        i_this->mTargetEyeRot.y = -0x71C;
    } else if (i_this->mTargetEyeRot.y > 0x71C) {
        i_this->mTargetEyeRot.y = 0x71C;
    }

    i_this->mTargetEyeRot.x = cM_atan2s(diffY, sqrtf(diffX*diffX + diffZ*diffZ));
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
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mState) {
    case 0:
        for (int i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        anm_init(i_this, AM_BCK_SLEEP_LOOP, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
        i_this->mState += 1;
        // Fall-through
    case 1:
        if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            break;
        }
        fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
        if (fopAcM_searchPlayerDistance(i_this) < 1000.0f) {
            f32 yDist = player->current.pos.y - i_this->current.pos.y;
            yDist = sqrtf(yDist*yDist); // ???
            if (yDist > 300.0f) {
                break;
            }
            if (Line_check(i_this, player->current.pos)) {
                anm_init(i_this, AM_BCK_OKIRU, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
                fopAcM_monsSeStart(i_this, JA_SE_CV_AM_AWAKE, 0);
                i_this->attention_info.flags = fopAc_Attn_LOCKON_ENEMY_e;
                i_this->mNeedleCyl.OnAtSetBit();
                i_this->mNeedleCyl.OnAtHitBit();
                i_this->mState += 1;
            }
        }
        break;
    case 2:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mState += 1;
        // Fall-through
    case 3:
        if (i_this->mCurrBckIdx != AM_BCK_CLOSE && i_this->mCurrBckIdx != AM_BCK_CLOSE_LOOP) {
            if (i_this->mCurrBckIdx != AM_BCK_DAMAGE_END) {
                fopAcM_seStart(i_this, JA_SE_CM_AM_NEEDLE_OUT, 0);
                // Using the fopAcM_seStart inline multiple times in a single case makes the codegen not match.
                // fopAcM_seStart(i_this, JA_SE_CM_AM_MOUTH_CLOSE, 0);
                mDoAud_seStart(JA_SE_CM_AM_MOUTH_CLOSE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            }
            anm_init(i_this, AM_BCK_CLOSE, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
            i_this->mCountDownTimers[2] = 6;
        }
        i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(i_this);
        i_this->mState += 1;
        // Fall-through
    case 4:
        if (i_this->mCountDownTimers[2] == 1) {
            i_this->mNeedleCyl.OnAtSPrmBit(AT_SPRM_SET);
            i_this->mNeedleCyl.OnAtHitBit();
        }
        if (i_this->mCountDownTimers[2] != 0) {
            break;
        }
        if (i_this->mType & 1) {
            f32 xDist = i_this->current.pos.x - i_this->mSpawnPos.x;
            f32 zDist = i_this->current.pos.z - i_this->mSpawnPos.z;
            f32 xzDist = sqrtf(xDist*xDist + zDist*zDist);
            if (xzDist > i_this->mAreaRadius) {
                i_this->mAction = ACTION_MODORU_MOVE;
                i_this->mState = 0x14;
                return;
            }
        } else {
            if (fopAcM_searchPlayerDistance(i_this) > 2000.0f) {
                i_this->mState = 9;
                break;
            }
            f32 yDist = player->current.pos.y - i_this->current.pos.y;
            yDist = sqrtf(yDist*yDist); // ???
            if (yDist > 300.0f) {
                i_this->mState = 9;
                break;
            }
        }
        s16 yRotDiff = cLib_distanceAngleS(i_this->shape_angle.y, i_this->mTargetAngleY);
        if (yRotDiff < 0x100) {
            i_this->mState += 1;
        }
        break;
    case 5:
        i_this->speedF = 30.0f;
        i_this->gravity = -11.0f;
        i_this->speed.y = 40.0f;
        fopAcM_monsSeStart(i_this, JA_SE_CV_AM_JUMP, 0);
        if (!Line_check(i_this, player->current.pos) || player->getDamageWaitTimer() != 0) {
            i_this->speedF = 0.0f;
        }
        i_this->mState += 1;
        break;
    case 6:
        if (i_this->mCurrBckIdx == AM_BCK_CLOSE) {
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, AM_BCK_CLOSE_LOOP, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
            }
        }
        if (!i_this->mAcch.ChkGroundHit()) {
            break;
        }
        fopAcM_seStart(i_this, JA_SE_CM_AM_JUMP, 0);
        i_this->mSmokeCbs[0].end();
        dComIfGp_particle_setToon(
            0xA125, &i_this->mWaistPos, &i_this->shape_angle, NULL,
            0xB9, &i_this->mSmokeCbs[0], fopAcM_GetRoomNo(i_this)
        );
        dComIfGp_getVibration().StartShock(3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        i_this->speedF = 0.0f;
        i_this->mCountDownTimers[0] = 0;
        if (i_this->mCountUpTimers[0] < 2) {
            i_this->mCountDownTimers[0] = 10;
        }
        i_this->mState += 1;
        // Fall-through
    case 7:
        if (i_this->mCountDownTimers[0] != 0) {
            break;
        }
        i_this->mCountUpTimers[0]++;
        if (i_this->mCountUpTimers[0] > 2) {
            i_this->mCountDownTimers[0] = 100;
            i_this->mCountUpTimers[0] = 0;
            anm_init(i_this, AM_BCK_DAMAGE, 0.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
            // Using the fopAcM_seStart inline multiple times in a single case makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM_NEEDLE_IN, 0);
            mDoAud_seStart(JA_SE_CM_AM_NEEDLE_IN, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            // fopAcM_seStart(i_this, JA_SE_CM_AM_MOUTH_OPEN, 0);
            mDoAud_seStart(JA_SE_CM_AM_MOUTH_OPEN, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_AM_OPEN_MOUTH, 0);
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->mNeedleCyl.OffAtSetBit();
            if (i_this->mSmokeCbs[2].getEmitter() == NULL) {
                dComIfGp_particle_setToon(
                    0xA154, &i_this->mWaistPos, &i_this->shape_angle, NULL,
                    0xB9, &i_this->mSmokeCbs[2], fopAcM_GetRoomNo(i_this)
                );
            }
            i_this->mState = 8;
        } else {
            i_this->mState = 3;
        }
        break;
    case 8:
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->gravity = -6.0f;
            i_this->speed.y = 15.0f;
            fopAcM_seStart(i_this, JA_SE_CM_AM_JUMP_S, 0);
            i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(i_this);
        }
        if (i_this->mCountDownTimers[0] == 0) {
            i_this->mSmokeCbs[2].end();
            i_this->mState = 3;
        }
        break;
    case 9:
        anm_init(i_this, AM_BCK_SLEEP, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        fopAcM_seStart(i_this, JA_SE_CM_AM_NEEDLE_IN, 0);
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->attention_info.flags = 0;
        i_this->mState += 1;
        break;
    case 10:
        if (i_this->mpMorf->isStop()) {
            i_this->mState = 0;
        }
        break;
    }

    medama_move(i_this);

    if (i_this->mState != 2 && medama_atari_check(i_this)) {
        i_this->mSmokeCbs[2].end();
    } else if (bomb_nomi_check(i_this)) {
        i_this->mSmokeCbs[2].end();
    }
}

/* 00002564-000028C4       .text action_modoru_move__FP8am_class */
static void action_modoru_move(am_class* i_this) {
    switch (i_this->mState) {
    case 0x14:
        anm_init(i_this, AM_BCK_CLOSE_LOOP, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
        i_this->mNeedleCyl.OnAtSetBit();
        i_this->mNeedleCyl.OnAtHitBit();
        i_this->gravity = -11.0f;
        i_this->speed.y = 40.0f;
        i_this->speedF = 15.0f;
        fopAcM_monsSeStart(i_this, JA_SE_CV_AM_JUMP, 0x42);

        f32 xDistToSpawn = i_this->mSpawnPos.x - i_this->current.pos.x;
        f32 zDistToSpawn = i_this->mSpawnPos.z - i_this->current.pos.z;
        i_this->mTargetAngleY = cM_atan2s(xDistToSpawn, zDistToSpawn);
        i_this->mState += 1;
        break;
    case 0x15:
        xDistToSpawn = i_this->mSpawnPos.x - i_this->current.pos.x;
        zDistToSpawn = i_this->mSpawnPos.z - i_this->current.pos.z;
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->mSmokeCbs[0].end();
            dComIfGp_particle_setToon(
                0xA125, &i_this->mWaistPos, &i_this->shape_angle, NULL,
                0xB9, &i_this->mSmokeCbs[0], fopAcM_GetRoomNo(i_this)
            );

            dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            // The fopAcM_seStart inline makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM_JUMP, 0);
            mDoAud_seStart(JA_SE_CM_AM_JUMP, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_AM_JUMP, 0x42);

            i_this->speed.y = 40.0f;
            i_this->speedF = 15.0f;
            i_this->mTargetAngleY = cM_atan2s(xDistToSpawn, zDistToSpawn);
        }

        f32 xzDist = sqrtf(xDistToSpawn*xDistToSpawn + zDistToSpawn*zDistToSpawn);
        if (xzDist < 20.0f) {
            i_this->mTargetAngleY = i_this->mSpawnRotY;
            i_this->speedF = 0.0f;
            i_this->mState += 1;
        }
        break;
    case 0x16:
        s16 angleDiff = cLib_distanceAngleS(i_this->shape_angle.y, i_this->mTargetAngleY);
        if (angleDiff < 0x100) {
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->attention_info.flags = 0;
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 0;
        }
        break;
    }
}

/* 000028C4-00002A6C       .text action_handou_move__FP8am_class */
static void action_handou_move(am_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    switch (i_this->mState) {
    case 0x1E:
        i_this->speedF = 20.0f;
        s16 angleToPlayer = fopAcM_searchPlayerAngleY(i_this);
        i_this->current.angle.y = angleToPlayer + 0x8000;
        if (i_this->mHugeKnockback == 1) {
            i_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->speedF = 40.0f;
        }
        i_this->mTargetAngleY = i_this->current.angle.y;
        if (i_this->mCurrBckIdx != AM_BCK_CLOSE && i_this->mCurrBckIdx != AM_BCK_CLOSE_LOOP) {
            fopAcM_seStart(i_this, JA_SE_CM_AM_NEEDLE_OUT, 0);
            // Using the fopAcM_seStart inline multiple times makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM_MOUTH_CLOSE, 0);
            mDoAud_seStart(JA_SE_CM_AM_MOUTH_CLOSE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            anm_init(i_this, AM_BCK_CLOSE, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        }
        i_this->mState += 1;
    case 0x1F:
        cLib_addCalc0(&i_this->speedF, 0.8f, 2.0f);
        if (i_this->speedF < 0.1f) {
            i_this->speedF = 0.0f;
            i_this->mCountDownTimers[2] = 6;
            i_this->current.angle.y = i_this->shape_angle.y;
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 3;
        }
    }
}

/* 00002A6C-000034F4       .text action_itai_move__FP8am_class */
static void action_itai_move(am_class* i_this) {
    switch (i_this->mState) {
    case 0x28:
        i_this->mEyeRot.setall(0);
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->speedF = -20.0f;
        i_this->current.angle.y = fopAcM_searchPlayerAngleY(i_this);
        i_this->mTargetAngleY = i_this->current.angle.y;
        fopAcM_seStart(i_this, JA_SE_CM_AM_NEEDLE_IN, 0);
        anm_init(i_this, AM_BCK_DAMAGE, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        i_this->mState += 1;
        // Fall-through
    case 0x29:
        cLib_addCalc0(&i_this->speedF, 0.8f, 2.0f);
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mCountDownTimers[0] = 100;
        i_this->speedF = 0.0f;
        anm_init(i_this, AM_BCK_DAMAGE_LOOP, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
        i_this->mState += 1;
        break;
    case 0x2A:
        if (i_this->mCountDownTimers[0] != 0) {
            break;
        }
        anm_init(i_this, AM_BCK_DAMAGE_END, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        fopAcM_seStart(i_this, JA_SE_CM_AM_NEEDLE_OUT, 0);
        // Using the fopAcM_seStart inline multiple times in a single case makes the codegen not match.
        // fopAcM_seStart(i_this, JA_SE_CM_AM_MOUTH_CLOSE, 0);
        mDoAud_seStart(JA_SE_CM_AM_MOUTH_CLOSE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        i_this->mState += 1;
        break;
    case 0x2B:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mNeedleCyl.OnAtSetBit();
        i_this->mNeedleCyl.OnAtHitBit();
        i_this->mCountUpTimers[0] = 0;
        i_this->mAction = ACTION_DOUSA;
        i_this->mState = 3;
        break;
    case 0x2C:
        i_this->mSmokeCbs[3].end();
        i_this->mStts.SetWeight(0xFF);
        dComIfGp_particle_setToon(
            0xA155, &i_this->mJawPos, &i_this->shape_angle, NULL,
            0xB9, &i_this->mSmokeCbs[3], fopAcM_GetRoomNo(i_this)
        );
        fopAcM_seStart(i_this, JA_SE_CM_AM_MOUTH_CLOSE, 0);
        anm_init(i_this, AM_BCK_BOM_NOMI, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        mDoAud_onEnemyDamage();
        i_this->mEyeRot.setall(0);
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mCountDownTimers[1] = 10;
        i_this->mState += 1;
        // Fall-through
    case 0x2D:
        bomb_move_set(i_this, 0);
        if (i_this->mpMorf->checkFrame(3.0f)) {
            // The fopAcM_seStart inline makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM_EAT_BOMB, 0);
            mDoAud_seStart(JA_SE_CM_AM_EAT_BOMB, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_AM_EAT_BOMB, 0);
        }
        if (i_this->mpMorf->checkFrame(6.0f)) {
            i_this->mSmokeCbs[1].end();
            i_this->mNeedleCyl.OnAtSetBit();
            i_this->mNeedleCyl.OnAtHitBit();
            dComIfGp_particle_setToon(
                0xA126, &i_this->mJawPos, &i_this->shape_angle, NULL,
                0xB9, &i_this->mSmokeCbs[1], fopAcM_GetRoomNo(i_this)
            );
            i_this->m033C = dComIfGp_particle_set(0x8157, &i_this->mJawPos);
            i_this->m0340 = dComIfGp_particle_set(0x8156, &i_this->mJawPos);
        }

        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mCountDownTimers[0] = 100;
        i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(i_this);
        i_this->mState += 1;
        break;
    case 0x2E:
        bomb_move_set(i_this, 1);
        i_this->shape_angle.y += 0x1000;
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->mSmokeCbs[0].end();
            // The fopAcM_seStart inline makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM_JUMP, 0);
            mDoAud_seStart(JA_SE_CM_AM_JUMP, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            dComIfGp_particle_setToon(
                0xA125, &i_this->mWaistPos, &i_this->shape_angle, NULL,
                0xB9, &i_this->mSmokeCbs[0], fopAcM_GetRoomNo(i_this)
            );
            dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            // The fopAcM_seStart inline makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM_JUMP_L, 0);
            mDoAud_seStart(JA_SE_CM_AM_JUMP_L, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_AM_JITABATA, 0);
            i_this->speed.y = 25.0f;
            i_this->gravity = -10.0f;
            i_this->speedF = 10.0f;
        }

        if (i_this->mCountDownTimers[0] != 0) {
            break;
        }
        anm_init(i_this, AM_BCK_DEAD, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        dComIfGp_particle_set(0x8127, &i_this->mWaistPos);
        dComIfGp_particle_set(0x8128, &i_this->mWaistPos);

        fopAcM_seStart(i_this, JA_SE_CM_AM_BEF_EXPLODE, 0);
        i_this->mTargetAngleY = i_this->current.angle.y;

        if (i_this->m033C) {
            i_this->m033C->becomeInvalidEmitter();
            i_this->m033C = NULL;
        }
        if (i_this->m0340) {
            i_this->m0340->becomeInvalidEmitter();
            i_this->m0340 = NULL;
        }
        i_this->speedF = 0.0f;
        i_this->mState += 1;
        break;
    case 0x2F:
        bomb_move_set(i_this, 1);
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        cXyz centerPos = i_this->current.pos;
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

        fopAcM_seStart(i_this, JA_SE_CM_AM_EXPLODE, 0);
        // Using the fopAcM_seStart inline multiple times in a single case makes the codegen not match.
        // fopAcM_seStart(i_this, JA_SE_LK_LAST_HIT, 0);
        mDoAud_seStart(JA_SE_LK_LAST_HIT, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));

        fopAcM_createDisappear(i_this, &centerPos, 5);
        fopAcM_onActor(i_this);
        fopAcM_delete(i_this);
        break;
    }

    if (i_this->m033C) {
        i_this->m033C->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
    }
    if (i_this->m0340) {
        i_this->m0340->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
    }

    if (i_this->mState == 0x29 || i_this->mState == 0x2A) {
        bomb_nomi_check(i_this);
    }
}

/* 000034F4-000039A4       .text daAM_Execute__FP8am_class */
static BOOL daAM_Execute(am_class* i_this) {
    fopAcM_setGbaName(i_this, dItem_BOW_e, 0xC, 0x2A);

    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
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

    if (i_this->mAction != ACTION_ITAI_MOVE && i_this->mSpawnPosY - 1500.0f > i_this->current.pos.y) {
        anm_init(i_this, AM_BCK_DEAD, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);

        dComIfGp_particle_set(0x8127, &i_this->mWaistPos);
        dComIfGp_particle_set(0x8128, &i_this->mWaistPos);

        fopAcM_seStart(i_this, JA_SE_CM_AM_BEF_EXPLODE, 0);

        i_this->mTargetAngleY = i_this->current.angle.y;

        if (i_this->m033C) {
            i_this->m033C->becomeInvalidEmitter();
            i_this->m033C = NULL;
        }
        if (i_this->m0340) {
            i_this->m0340->becomeInvalidEmitter();
            i_this->m0340 = NULL;
        }

        i_this->speedF = 0.0f;
        i_this->mAction = ACTION_ITAI_MOVE;
        i_this->mState = 0x2F;
    }

    cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->mTargetAngleY, 1, 0x500);
    if (i_this->mState != 0x2E && i_this->mState != 0x2F && i_this->mState != 0x1F) {
        cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 1, 0x500);
    }

    if (i_this->mCountDownTimers[1] == 0) {
        i_this->mpMorf->play(NULL, 0, 0);
    }

    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    cXyz offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = i_this->speedF;
    cXyz rotOffset;
    MtxPosition(&offset, &rotOffset);
    i_this->speed.x = rotOffset.x;
    i_this->speed.z = rotOffset.z;
    i_this->speed.y += i_this->gravity;
    if (i_this->speed.y < -100.0f) {
        i_this->speed.y = -100.0f;
    }

    body_atari_check(i_this);

    i_this->attention_info.position = i_this->current.pos;
    i_this->attention_info.position.y += 330.0f;
    i_this->eyePos = i_this->current.pos;
    i_this->eyePos.y += 250.0f;

    cXyz needlePos = i_this->current.pos;

    i_this->mEyeSph.SetC(i_this->mEyeballPos);
    i_this->mEyeSph.SetR(60.0f);
    dComIfG_Ccsp()->Set(&i_this->mEyeSph);

    i_this->mMouthSph.SetC(i_this->mMouthPos);
    i_this->mMouthSph.SetR(100.0f);
    dComIfG_Ccsp()->Set(&i_this->mMouthSph);

    i_this->mBodyCyl.SetC(i_this->current.pos);
    i_this->mBodyCyl.SetH(300.0f);
    i_this->mBodyCyl.SetR(80.0f);
    dComIfG_Ccsp()->Set(&i_this->mBodyCyl);

    needlePos.y += 40.0f;
    i_this->mNeedleCyl.SetC(needlePos);
    i_this->mNeedleCyl.SetH(30.0f);
    i_this->mNeedleCyl.SetR(130.0f);
    dComIfG_Ccsp()->Set(&i_this->mNeedleCyl);

    fopAcM_posMove(i_this, i_this->mStts.GetCCMoveP());
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
        i_this->mSmokeCbs[i].end();
    }
    i_this->mSmokeCbs[2].end();

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
static BOOL useHeapInit(fopAc_ac_c* i_actor) {
    am_class* i_this = (am_class*)i_actor;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("AM", AM_BDL_AM),
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("AM", AM_BCK_SLEEP_LOOP),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
        NULL,
        0x00000000,
        0x11020203
    );
    if (!i_this->mpMorf || !i_this->mpMorf->getModel()) {
        return FALSE;
    }

    i_this->mpMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }

    static Vec cyl2_eye_offset[] = {
        {0.0f, 0.0f, 70.0f},
        {0.0f, 0.0f, 80.0f},
    };
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ 2, // Cylinder
            /* mJointIndex */ 0x05, // hitomi (pupil) joint
            /* mRadius     */ 5.0f,
            /* mpOffsets   */ cyl2_eye_offset,
        },
    };
    i_this->mEyeJntHit = JntHit_create(i_this->mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (i_this->mEyeJntHit) {
        i_this->jntHit = i_this->mEyeJntHit;
    } else {
        return FALSE;
    }

    return TRUE;
}

/* 00003C00-00003F5C       .text daAM_Create__FP10fopAc_ac_c */
static s32 daAM_Create(fopAc_ac_c* i_actor) {
    fopAcM_SetupActor(i_actor, am_class);

    am_class* i_this = (am_class*)i_actor;

    s32 phase_state = dComIfG_resLoad(&i_this->mPhase, "AM");
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x1C80)) {
            return cPhs_ERROR_e;
        }

        i_this->stealItemLeft = 3;

        i_this->mSmokeCbs[0].setRateOff(0);
        i_this->mSmokeCbs[1].setRateOff(0);
        i_this->mSmokeCbs[3].setRateOff(0);

        i_this->mType = (fopAcM_GetParam(i_this) >> 0x00) & 0xFF;
        i_this->mPrmAreaRadius = (fopAcM_GetParam(i_this) >> 0x08) & 0xFF;
        i_this->mStartsInactive = (fopAcM_GetParam(i_this) >> 0x10) & 0xFF;
        i_this->mSwitch = (fopAcM_GetParam(i_this) >> 0x18) & 0xFF;

        if (i_this->mType == 0xFF) {
            i_this->mType = 0;
        }
        if (i_this->mStartsInactive == 0xFF) {
            i_this->mStartsInactive = 0;
        }
        if (g_regHIO.mChild[8].mShortRegs[9] != 0) {
            i_this->mType = 1;
        }
        if (i_this->mPrmAreaRadius == 0xFF || i_this->mPrmAreaRadius == 0) {
            i_this->mAreaRadius = 400.0f;
        } else {
            i_this->mAreaRadius = i_this->mPrmAreaRadius * 100.0f;
        }
        i_this->mSpawnPosY = i_this->current.pos.y;
        i_this->mSwallowedActorPID = fpcM_ERROR_PROCESS_ID_e;

        if (i_this->mStartsInactive == 0 && i_this->mSwitch != 0xFF && dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            // When mStartsInactive is 0, the Armos Knight starts active and attacking the player.
            // mSwitch being set disables it from spawning again in the future.
            return cPhs_ERROR_e;
        }
        if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            // When mStartsInactive is 1, the Armos Knight is initially inactive.
            // mSwitch being set causes it to become active and attack the player.
            fopAcM_OffStatus(i_this, fopAcStts_SHOWMAP_e);
        }

        i_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("amos", 0);
        i_this->max_health = 10;
        i_this->health = 10;

        fopAcM_SetMtx(i_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(i_this, -100.0f, -10.0f, -80.0f, 120.0f, 400.0f, 100.0f);

        i_this->attention_info.flags = 0;

        i_this->mAcch.Set(
            fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this),
            i_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(i_this)
        );
        i_this->mStts.Init(254, 1, i_this);

        i_this->gravity = -10.0f;

        i_this->mEnemyIce.mpActor = i_this;
        i_this->mEnemyIce.mWallRadius = 80.0f;
        i_this->mEnemyIce.mCylHeight = 300.0f;

        static dCcD_SrcSph eye_co_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_UNK1000,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW | AT_TYPE_GRAPPLING_HOOK,
                /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
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
                /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_CON_HIT | G_TG_SPRM_NO_HIT_MARK,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGSphS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 15.0f,
            },
        };
        i_this->mEyeSph.Set(eye_co_sph_src);
        i_this->mEyeSph.SetStts(&i_this->mStts);

        static dCcD_SrcSph mouth_co_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_UNK1000,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK4 | CO_SPRM_VS_UNK8 | CO_SPRM_NO_CRR,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ 0,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_CON_HIT,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGSphS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 15.0f,
            },
        };
        i_this->mMouthSph.Set(mouth_co_sph_src);
        i_this->mMouthSph.SetStts(&i_this->mStts);

        static dCcD_SrcCyl body_co_cyl_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_UNK1000,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
                /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
                /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK4 | CO_SPRM_VSGRP,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ 0,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ G_TG_MARK_PURPLE_HIT,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ G_TG_SPRM_SHIELD | G_TG_SPRM_NO_CON_HIT,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGCylS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 15.0f,
                /* Height */ 0.0f,
            },
        };
        i_this->mBodyCyl.Set(body_co_cyl_src);
        i_this->mBodyCyl.SetStts(&i_this->mStts);

        static dCcD_SrcCyl sword_co_cyl_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_UNK1000,
                /* SrcObjAt  Atp     */ 2,
                /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_GRP,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK4 | CO_SPRM_VSGRP,
                /* SrcGObjAt Se      */ 0,
                /* SrcGObjAt HitMark */ 0,
                /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK6,
                /* SrcGObjAt Mtrl    */ 0,
                /* SrcGObjAt SPrm    */ 0,
                /* SrcGObjTg Se      */ 0,
                /* SrcGObjTg HitMark */ G_TG_MARK_PURPLE_HIT,
                /* SrcGObjTg Spl     */ 0,
                /* SrcGObjTg Mtrl    */ 0,
                /* SrcGObjTg SPrm    */ G_TG_SPRM_SHIELD | G_TG_SPRM_NO_CON_HIT,
                /* SrcGObjCo SPrm    */ 0,
            },
            // cM3dGCylS
            {
                /* Center */ 0.0f, 0.0f, 0.0f,
                /* Radius */ 15.0f,
                /* Height */ 0.0f,
            },
        };
        i_this->mNeedleCyl.Set(sword_co_cyl_src);
        i_this->mNeedleCyl.SetStts(&i_this->mStts);

        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();

        i_this->mTargetAngleY = i_this->current.angle.y;
        i_this->mSpawnPos = i_this->current.pos;
        i_this->mSpawnRotY = i_this->current.angle.y;

        draw_SUB(i_this);
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
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_AM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(am_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00BD,
    /* Actor SubMtd */ &l_daAM_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
