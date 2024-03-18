/**
 * d_a_am2.cpp
 * Enemy - Armos
 */

#include "d/actor/d_a_am2.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_s_play.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_snap.h"
#include "d/actor/d_a_player.h"
#include "d/d_jnt_hit.h"
#include "d/d_cc_uty.h"
#include "SSystem/SComponent/c_lib.h"
#include "f_op/f_op_camera_mng.h"
#include "f_op/f_op_kankyo_mng.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

enum Action {
    ACTION_DOUSA       = 0x0,
    ACTION_MAHI        = 0x1,
    ACTION_ITAI        = 0x2,
    ACTION_HANDOU_MOVE = 0x3,
    ACTION_MODORU_MOVE = 0x4,
};

enum AM2_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    AM2_BCK_BURUBURU=0x6,
    AM2_BCK_DAMAGE=0x7,
    AM2_BCK_DEAD1=0x8,
    AM2_BCK_DEAD2=0x9,
    AM2_BCK_DEAD3=0xA,
    AM2_BCK_JUMP=0xB,
    AM2_BCK_MAHI=0xC,
    AM2_BCK_SLEEP=0xD,
    AM2_BCK_START=0xE,
    AM2_BCK_WAIT=0xF,
    
    /* BDLM */
    AM2_BDL_AM2=0x12,
    
    /* BRK */
    AM2_BRK_AM2=0x15,
    
    /* BTK */
    AM2_BTK_AM2=0x18,
};

/* 00000078-000001B0       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        am2_class* i_this = (am2_class*)model->getUserArea();
        if (i_this) {
            cMtx_copy(model->getAnmMtx(jntNo), *calc_mtx);

            cXyz offset;
            switch (jntNo) {
            case 1: // coa (core/weak spot)
                offset.x = 0.0f;
                offset.y = 50.0f;
                offset.z = -40.0f;
                MtxPosition(&offset, &i_this->mWeakPos);
                break;
            case 2: // eye
                offset.x = 30.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->mEyeballPos);
                break;
            case 3: // toge (needles)
                offset.x = -10.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->mNeedlePos);
                break;
            }

            model->setAnmMtx(jntNo, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 000001B0-00000278       .text draw_SUB__FP9am2_class */
static void draw_SUB(am2_class* i_this) {
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

/* 00000278-00000374       .text daAM2_Draw__FP9am2_class */
static BOOL daAM2_Draw(am2_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(model, &i_this->tevStr);

    dSnap_RegistFig(DSNAP_TYPE_AM2, i_this, 1.0f, 1.0f, 1.0f);
    
    i_this->mpBrkAnm->entry(model->getModelData());
    i_this->mpBtkAnm->entry(model->getModelData());

    i_this->mpMorf->entryDL();

    i_this->mpBrkAnm->remove(model->getModelData());
    i_this->mpBtkAnm->remove(model->getModelData());

    if (!fopAcM_CheckStatus(i_this, fopAcStts_CARRY_e)) {
        dComIfGd_setSimpleShadow2(
            &i_this->current.pos, i_this->mAcch.GetGroundH(), 50.0f, i_this->mAcch.m_gnd,
            0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
        );
    }

    return TRUE;
}

/* 00000374-000004A0       .text anm_init__FP9am2_classifUcfi */
static void anm_init(am2_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->mCurrBckIdx = bckFileIdx;
    if (soundFileIdx >= 0) {
        void* soundAnm = dComIfG_getObjectRes("AM2", soundFileIdx);
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("AM2", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, soundAnm);
    } else {
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("AM2", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000004A0-00000818       .text medama_atari_check__FP9am2_class */
static BOOL medama_atari_check(am2_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bool ret = false;

    if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
        return ret;
    }

    i_this->mStts.Move();
    if (i_this->mEyeSph.ChkTgHit()) {
        cCcD_Obj* hitObj = i_this->mEyeSph.GetTgHitObj();
        if (hitObj) {
            CcAtInfo atInfo;
            cXyz hitPos = *i_this->mEyeSph.GetTgHitPosP();

            if (hitObj->ChkAtType(AT_TYPE_GRAPPLING_HOOK)) {
                if (i_this->mCurrBckIdx != AM2_BCK_SLEEP) {
                    if (i_this->stealItemLeft > 0) {
                        s8 origHealth = i_this->health;
                        i_this->health = 10;
                        atInfo.mpObj = i_this->mEyeSph.GetTgHitObj();
                        atInfo.pParticlePos = NULL;
                        cc_at_check(i_this, &atInfo);
                        i_this->health = origHealth;
                        dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &i_this->attention_info.position);
                    } else {
                        dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, &hitPos);
                    }
                    fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
                }
                return TRUE;
            }
            
            if (hitObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
                ret = true;
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 1.0f;
                i_this->mEnemyIce.mYOffset = 80.0f;
                i_this->attention_info.flags = 0;
                return TRUE;
            }
            
            if (hitObj->ChkAtType(AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW)) {
                ret = true;
                if (i_this->mCurrBckIdx == AM2_BCK_SLEEP) {
                    anm_init(i_this, AM2_BCK_WAIT, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
                    i_this->attention_info.flags = fopAc_Attn_LOCKON_ENEMY_e;
                    fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
                    i_this->mNeedleCyl.OnAtSetBit();
                    i_this->mNeedleCyl.OnAtHitBit();
                    i_this->mNeedleCyl.OnTgSetBit();
                    i_this->mAction = ACTION_DOUSA;
                    i_this->mState = 2;
                } else {
                    dComIfGp_particle_set(0x10, &hitPos, &player->shape_angle);
                    // Using the fopAcM_seStart inline breaks the codegen.
                    // fopAcM_seStart(i_this, JA_SE_CM_AM2_PARALYZED, 0);
                    mDoAud_seStart(JA_SE_CM_AM2_PARALYZED, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                    fopAcM_monsSeStart(i_this, JA_SE_CV_AM2_PARALYZED, 0x42);
                    i_this->mAction = ACTION_MAHI;
                    i_this->mState = 10;
                }
                return TRUE;
            }
        }
    }

    return FALSE;
}

/* 00000818-00000D30       .text week_atari_check__FP9am2_class */
static BOOL week_atari_check(am2_class* i_this) {
    fopAc_ac_c* actor = i_this; // Fixes regswap
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    
    s16 targetAngle = fopAcM_searchPlayerAngleY(actor);
    s16 angleDelta = cLib_distanceAngleS(actor->shape_angle.y, targetAngle);
    if (angleDelta < 0x4000) {
        return FALSE;
    }
    
    i_this->mStts.Move();
    i_this->m2CE = 0;
    
    if (i_this->mWeakSph.ChkTgHit()) {
        if (!i_this->mbIsWeakBeingHit) {
            cCcD_Obj* hitObj = i_this->mWeakSph.GetTgHitObj();
            i_this->mbIsWeakBeingHit = true;
            if (!hitObj) {
                return FALSE;
            }
            
            u8 hitType = 0;
            if (hitObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 1.0f;
                i_this->mEnemyIce.mYOffset = 80.0f;
                actor->attention_info.flags = 0;
                return TRUE;
            }
            
            switch (hitObj->GetAtType()) {
            case AT_TYPE_SWORD:
            case AT_TYPE_MACHETE:
            case AT_TYPE_UNK800:
            case AT_TYPE_DARKNUT_SWORD:
            case AT_TYPE_MOBLIN_SPEAR:
                fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x35);
                if (player->getCutType() == 0x06 || player->getCutType() == 0x07 || player->getCutType() == 0x08 ||
                    player->getCutType() == 0x09 || player->getCutType() == 0x0A || player->getCutType() == 0x0C ||
                    player->getCutType() == 0x0E || player->getCutType() == 0x0F || player->getCutType() == 0x10 ||
                    player->getCutType() == 0x15 || player->getCutType() == 0x19 || player->getCutType() == 0x1A ||
                    player->getCutType() == 0x1B || player->getCutType() == 0x1E || player->getCutType() == 0x1F)
                {
                    hitType = 1;
                    i_this->m2CE = 1;
                }
                break;
            case AT_TYPE_WIND:
                hitType = 2;
                i_this->m2CE = 3;
                break;
            case AT_TYPE_BOOMERANG:
                i_this->m2CE = 4;
                return FALSE;
            case AT_TYPE_BOKO_STICK:
            case AT_TYPE_STALFOS_MACE:
            case AT_TYPE_UNK2000:
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x35);
                break;
            case AT_TYPE_SKULL_HAMMER:
                fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x35);
                hitType = 1;
                i_this->m2CE = 7;
                if (player->getCutType() == 0x11) {
                    i_this->m2CE = 8;
                }
                break;
            case AT_TYPE_BOMB:
                hitType = 1;
                i_this->m2CE = 6;
                break;
            case AT_TYPE_NORMAL_ARROW:
            case AT_TYPE_FIRE_ARROW:
            case AT_TYPE_ICE_ARROW:
                hitType = 1;
                i_this->m2CE = 5;
                // Fall-through
            default:
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x35);
                break;
            }
            
            if (hitType != 2) { // Not hit by wind
                CcAtInfo atInfo;
                cXyz hitPos = *i_this->mWeakSph.GetTgHitPosP();
                atInfo.mpObj = i_this->mWeakSph.GetTgHitObj();
                atInfo.pParticlePos = NULL;
                cc_at_check(actor, &atInfo);
                
                if (hitType == 1) {
                    dComIfGp_particle_set(0x10, &hitPos);
                    cXyz particleScale(2.0f, 2.0f, 2.0f);
                    dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &hitPos, &player->shape_angle, &particleScale);
                } else {
                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &hitPos, &player->shape_angle);
                }
                
                i_this->mAction = ACTION_ITAI;
                i_this->mState = 0x14;
                if (i_this->m2CE == 7 || i_this->m2CE == 8) {
                    actor->health = 0;
                }
            }
            return TRUE;
        }
    } else {
        i_this->mbIsWeakBeingHit = false;
    }
    
    return FALSE;
}

/* 00000D30-00000F54       .text body_atari_check__FP9am2_class */
static BOOL body_atari_check(am2_class* i_this) {
    // For VERSION_JPN, the redundant daPy_py_c* cast is required to fix a regswap.
    // For the other versions, the cast has no effect (it doesn't create another regswap).
    daPy_py_c* player = (daPy_py_c*)daPy_getPlayerActorClass();

    i_this->mStts.Move();

    i_this->m2CE = 0;
    
    if (i_this->mBodyCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = i_this->mBodyCyl.GetTgHitObj();
        if (!hitObj) {
            return FALSE;
        }

        switch (hitObj->GetAtType()) {
        case AT_TYPE_SWORD:
            fopAcM_seStart(i_this, JA_SE_LK_SW_HIT_S, 0x42);
            break;
        case AT_TYPE_BOOMERANG:
        case AT_TYPE_BOKO_STICK:
            fopAcM_seStart(i_this, JA_SE_LK_W_WEP_HIT, 0x42);
            break;
        case AT_TYPE_SKULL_HAMMER:
            fopAcM_seStart(i_this, JA_SE_LK_HAMMER_HIT, 0x42);
            if (i_this->mAction == ACTION_HANDOU_MOVE) {
                break;
            }
            if (i_this->mAction == ACTION_ITAI) {
                break;
            }
            i_this->mAction = ACTION_HANDOU_MOVE;
            i_this->mState = 0x1E;
            i_this->m2CE = 7;
            if (player->getCutType() == 0x11) {
                i_this->m2CE = 8;
            }
            break;
        default:
            fopAcM_seStart(i_this, JA_SE_LK_MS_WEP_HIT, 0x42);
            break;
        }
        return TRUE;
    }
    
    return FALSE;
}

/* 00000F54-00000FF4       .text BG_check__FP9am2_class */
static void BG_check(am2_class* i_this) {
    f32 halfHeight = 40.0f + g_regHIO.mChild[8].mFloatRegs[12];
    i_this->mAcchCir.SetWall(halfHeight, i_this->mAcchRadius);

    i_this->current.pos.y -= i_this->mCorrectionOffsetY;
    i_this->old.pos.y -= i_this->mCorrectionOffsetY;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    i_this->current.pos.y += i_this->mCorrectionOffsetY;
    i_this->old.pos.y += i_this->mCorrectionOffsetY;
}

/* 00000FF4-00001344       .text Line_check__FP9am2_class4cXyz */
static BOOL Line_check(am2_class* i_this, cXyz destPos) {
    fopAc_ac_c* actor = i_this;
    dBgS_LinChk linChk;
    cXyz centerPos = actor->current.pos;
    centerPos.y += 100.0f + g_regHIO.mChild[12].mFloatRegs[19];
    i_this->mLinChkCenter = centerPos;
    i_this->mLinChkDest = destPos;
    linChk.Set(&centerPos, &destPos, actor);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 0000177C-00001A24       .text naraku_check__FP9am2_class */
static BOOL naraku_check(am2_class* i_this) {
    // Checks if the Armos has fallen into an abyss.
    if (i_this->mAcch.GetGroundH() != -1000000000.0f &&
        dComIfG_Bgsp()->ChkPolySafe(i_this->mAcch.m_gnd) &&
        dComIfG_Bgsp()->GetGroundCode(i_this->mAcch.m_gnd) == 4) // Abyss ground code
    {
        i_this->mInAbyssTimer++;
        dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(i_this));
        
        if (i_this->current.pos.y < -500.0f || i_this->mInAbyssTimer > 50) {
            i_this->speedF = 0.0f;
            i_this->speed.setall(0.0f);
            i_this->gravity = 0.0f;
            return TRUE;
        }
    }
    
    if (i_this->mAcch.ChkWaterIn()) {
        if (!i_this->mbMadeWaterSplash) {
            cXyz waterPillarPos = i_this->current.pos;
            if (i_this->mCountDownTimers[4] == 0) {
                i_this->mCountDownTimers[4] = 1*30;
                waterPillarPos.y = i_this->mAcch.m_wtr.GetHeight();
                f32 centerY = i_this->current.pos.y + 80.0f;
                f32 scaleY = (0.1f + g_regHIO.mChild[8].mFloatRegs[1]) * (waterPillarPos.y - centerY);
                if (scaleY < 0.0f) {
                    scaleY = 0.3f;
                } else if (scaleY > 1.0f) {
                    scaleY = 1.0f;
                }
                fopKyM_createWpillar(&waterPillarPos, 1.0f, scaleY, 0);
                fopAcM_seStart(i_this, JA_SE_OBJ_FALL_WATER_M, 0);
                
                i_this->mbMadeWaterSplash = true;
                
                cXyz particleScale(1.0f, 1.0f, 1.0f);
                i_this->mRippleCb.end();
                dComIfGp_particle_setShipTail(0x33, &i_this->current.pos, NULL, &particleScale, 0xFF, &i_this->mRippleCb);
                i_this->mRippleCb.setRate(0.0f);
            }
        }
        
        f32 waterSinkDepth = 80.0f + g_regHIO.mChild[12].mFloatRegs[0];
        if (i_this->current.pos.y < i_this->mAcch.m_wtr.GetHeight() - waterSinkDepth) {
            i_this->speedF = 0.0f;
            i_this->speed.setall(0.0f);
            i_this->gravity = 0.0f;
            return TRUE;
        }
    } else if (i_this->mbMadeWaterSplash) {
        i_this->mbMadeWaterSplash = false;
        i_this->mRippleCb.end();
    }
    
    return FALSE;
}

/* 00001A24-00002240       .text action_dousa__FP9am2_class */
static void action_dousa(am2_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    
    cXyz offset;
    cXyz rotOffset;
    if (i_this->mState == 4 || i_this->mState == 5) {
        cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
        offset.set(0.0f, 0.0f, 200.0f);
        MtxPosition(&offset, &rotOffset);
        rotOffset += i_this->current.pos;
        rotOffset.y += 100.0f + g_regHIO.mChild[12].mFloatRegs[19];
    }
    
    switch (i_this->mState) {
    case 0:
        for (int i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        i_this->mAcchRadius = 80.0f + g_regHIO.mChild[8].mFloatRegs[11];
        if (i_this->mCurrBckIdx != AM2_BCK_WAIT) {
            anm_init(i_this, AM2_BCK_WAIT, 10.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        }
        i_this->mState++;
        // Fall-through
    case 1:
        f32 playerDist = fopAcM_searchPlayerDistance(i_this);
        if (playerDist < i_this->mAreaRadius) {
            cXyz centerPos = player->current.pos;
            centerPos.y += 100.0f + g_regHIO.mChild[12].mFloatRegs[19];
            if (Line_check(i_this, centerPos)) {
                i_this->attention_info.flags = fopAc_Attn_LOCKON_ENEMY_e;
                fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
                anm_init(i_this, AM2_BCK_START, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
                fopAcM_monsSeStart(i_this, JA_SE_CV_AM2_AWAKE, 0);
                i_this->mEyeSph.OnTgSetBit();
                i_this->mWeakSph.OnTgSetBit();
                i_this->mState += 1;
            }
        }
        break;
    case 2:
        if (i_this->mpMorf->checkFrame(24.0f)) {
            fopAcM_seStart(i_this, JA_SE_CM_AM2_SPIKE_OUT, 0);
        }
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mState++;
        // Fall-through
    case 3:
        for (int i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        i_this->speedF = 0.0f;
        playerDist = fopAcM_searchPlayerDistance(i_this);
        f32 radiusAdjust = 200.0f;
        if (playerDist > i_this->mAreaRadius + radiusAdjust) {
            i_this->mState = 6;
        } else {
            i_this->mNeedleCyl.OnAtSetBit();
            i_this->mNeedleCyl.OnAtHitBit();
            i_this->mNeedleCyl.OnTgSetBit();
            i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(i_this);
            i_this->gravity = -3.0f;
            i_this->speed.y = 12.0f;
            if (i_this->mCurrBckIdx != AM2_BCK_JUMP) {
                anm_init(i_this, AM2_BCK_JUMP, 2.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
            }
            i_this->mState++;
        }
        break;
    case 4:
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->gravity = -3.0f;
            i_this->speed.y = 12.0f;
            fopAcM_seStart(i_this, JA_SE_CM_AM2_LANDING, 0);
            i_this->mState = 3;
            s16 angleDiff = cLib_distanceAngleS(i_this->shape_angle.y, i_this->current.angle.y);
            if (angleDiff < 0x1000) {
                if (Line_check(i_this, rotOffset) || player->getDamageWaitTimer() == 0) {
                    i_this->mState = 5;
                }
            }
        }
        break;
    case 5:
        if (i_this->speedF > 0.0f && i_this->mNeedleCyl.ChkAtShieldHit()) {
            i_this->speedF = 9.0f;
            i_this->speedF *= -1.0f;
            i_this->speed.y = 0.0f;
        }
        if (i_this->mAcch.ChkGroundHit()) {
            fopAcM_seStart(i_this, JA_SE_CM_AM2_LANDING, 0);
            i_this->mSmokeCb.end();
            // Using the fopAcM_seStart inline multiple times in a single case makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM_JUMP_S, 0);
            mDoAud_seStart(JA_SE_CM_AM_JUMP_S, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            
            dComIfGp_particle_setToon(0xA125, &i_this->current.pos, &i_this->shape_angle, NULL, 0xB9, &i_this->mSmokeCb, fopAcM_GetRoomNo(i_this));
            if (i_this->mSmokeCb.getEmitter()) {
                i_this->mSmokeCb.getEmitter()->setRate(12.0f);
                JGeometry::TVec3<f32> scale;
                scale.set(0.45f, 0.45f, 0.45f);
                i_this->mSmokeCb.getEmitter()->setGlobalScale(scale);
            }
            
            if (i_this->mCountUpTimers[0] > 8) {
                i_this->mState = 3;
            } else {
                i_this->speedF = 9.0f;
                i_this->gravity = -8.0f;
                i_this->speed.y = 20.0f;
                i_this->mCountUpTimers[1] = 0;
                if (!Line_check(i_this, rotOffset) || player->getDamageWaitTimer() != 0) {
                    i_this->speedF = 0.0f;
                }
                i_this->mCountUpTimers[0]++;
            }
        }
        break;
    case 6:
        anm_init(i_this, AM2_BCK_SLEEP, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        fopAcM_seStart(i_this, JA_SE_CM_AM2_SPIKE_IN, 0);
        i_this->mWeakSph.OffTgSetBit();
        i_this->mWeakSph.ClrTgHit();
        i_this->mState++;
        // Fall-through
    case 7:
        if (i_this->mpMorf->isStop()) {
            for (int i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
                i_this->mCountUpTimers[i] = 0;
            }
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->mNeedleCyl.OffTgSetBit();
            i_this->mNeedleCyl.ClrTgHit();
            i_this->m304 = i_this->current.pos;
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 1;
        }
        break;
    }
    
    cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->mTargetAngleY, 1, 0x500);
    cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 1, 0x500);
    
    if (naraku_check(i_this)) {
        if (i_this->mbNotInHomeRoom) {
            // If it fell into an abyss when it's not in its original room, just delete it, don't try to respawn.
            // Note: You cannot actually carry Armos through doors in the final game, so this may just be a sanity check.
            fopAcM_delete(i_this);
        } else {
            i_this->mAction = ACTION_MODORU_MOVE;
            i_this->mState = 0x28;
        }
    } else if (!medama_atari_check(i_this)) {
        if (i_this->mState < 3 || !week_atari_check(i_this)) {
            body_atari_check(i_this);
        }
    }
}

/* 00002240-00002B08       .text action_mahi__FP9am2_class */
static void action_mahi(am2_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* actor = i_this; // Fixes regswaps
    
    switch (i_this->mState) {
    case 0xA:
        for (int i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffTgSetBit();
        i_this->mNeedleCyl.ClrTgHit();
        
        i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(actor) + 0x8000;
        actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
        i_this->mCountDownTimers[2] = 0;
        i_this->mCountDownTimers[3] = 0;
        actor->speedF = 20.0f;
        
        fopAcM_seStart(actor, JA_SE_CM_AM2_SPIKE_IN, 0);
        anm_init(i_this, AM2_BCK_DAMAGE, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        
        i_this->mState++;
        break;
    case 0xB:
        cLib_addCalc0(&actor->speedF, 0.5f, 1.0f);
        if (actor->speedF < 0.2f) {
            if (i_this->mpMorf->isStop()) {
                actor->speedF = 0.0f;
                i_this->mCountDownTimers[2] = 20*30;
                anm_init(i_this, AM2_BCK_MAHI, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
                i_this->mState++;
            }
        }
        break;
    case 0xC:
        if (i_this->mCountDownTimers[3] == 0 || i_this->mCountDownTimers[3] > 3) {
            actor->attention_info.flags |= fopAc_Attn_ACTION_CARRY_e;
        }
        if (naraku_check(i_this)) {
            if (i_this->mbNotInHomeRoom) {
                fopAcM_delete(actor);
            } else {
                i_this->mAction = ACTION_MODORU_MOVE;
                i_this->mState = 0x28;
            }
        } else {
            if (i_this->mCountUpTimers[1] != 0 && i_this->mAcch.ChkGroundHit()) {
                fopAcM_seStart(actor, JA_SE_CM_AM2_JUMP, 0);
                i_this->mCountUpTimers[1] = 0;
            }
            if (fopAcM_CheckStatus(actor, fopAcStts_CARRY_e)) {
                i_this->mAcchRadius = 40.0f + g_regHIO.mChild[8].mFloatRegs[10];
                i_this->mbMadeWaterSplash = false;
                i_this->mRippleCb.end();
                i_this->mPickedUpYPos = actor->current.pos.y;
                fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
                actor->current.angle.y = player->shape_angle.y;
                actor->gravity = 0.0f;
                actor->speed.setall(0.0f);
                actor->speedF = 0.0f;
                i_this->mbNotInHomeRoom = false;
                i_this->mBodyCyl.OffCoSetBit();
                i_this->mState++;
            }
        }
        break;
    case 0xD:
        actor->current.angle.y = player->shape_angle.y;
        if (actor->home.roomNo != actor->current.roomNo) {
            i_this->mbNotInHomeRoom = true;
        }
        if (i_this->mPickedUpYPos + 10.0f <= actor->current.pos.y) {
            cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x1000);
        }
        if (!fopAcM_CheckStatus(actor, fopAcStts_CARRY_e)) {
            i_this->mAcchRadius = 40.0f + g_regHIO.mChild[8].mFloatRegs[10];
            i_this->mBodyCyl.OnCoSetBit();
            if (actor->speedF > 0.0f) {
                actor->gravity = -5.0f;
                actor->speed.y = 25.0f;
                actor->speedF = 35.0f;
                i_this->mAcch.OnLineCheck();
                i_this->mState = 0xE;
            } else {
                actor->gravity = -3.0f;
                i_this->mCountUpTimers[1] = 1;
                i_this->mState = 0xC;
            }
        }
        break;
    case 0xE:
        if (i_this->mAcch.ChkWallHit()) {
            actor->speedF = 0.0f;
        }
        if (naraku_check(i_this)) {
            if (i_this->mbNotInHomeRoom) {
                fopAcM_delete(actor);
            } else {
                i_this->mAcch.OffLineCheck();
                i_this->mAction = ACTION_MODORU_MOVE;
                i_this->mState = 0x28;
            }
        } else {
            if (i_this->mAcch.ChkGroundHit()) {
                dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(actor));
                
                i_this->mAcch.OffLineCheck();
                i_this->mbMadeWaterSplash = false;
                i_this->mRippleCb.end();
                
                if (i_this->mCountUpTimers[0] == 0) {
                    i_this->mSmokeCb.end();
                    fopAcM_seStart(actor, JA_SE_CM_AM2_LANDING, 0);
                    
                    dComIfGp_particle_setToon(0xA125, &actor->current.pos, &actor->shape_angle, NULL, 0xB9, &i_this->mSmokeCb, fopAcM_GetRoomNo(actor));
                    if (i_this->mSmokeCb.getEmitter()) {
                        i_this->mSmokeCb.getEmitter()->setRate(12.0f);
                        JGeometry::TVec3<f32> scale;
                        scale.set(0.8f, 0.8f, 0.8f);
                        i_this->mSmokeCb.getEmitter()->setGlobalScale(scale);
                    }
                    
                    actor->speedF = 7.0f;
                    actor->speed.y = 25.0f;
                    actor->gravity = -14.0f;
                    i_this->mCountUpTimers[0]++;
                } else {
                    actor->speedF = 0.0f;
                    i_this->mCountUpTimers[0] = 0;
                    i_this->mState = 0xC;
                }
            }
            
            cLib_addCalc0(&actor->speedF, 0.5f, 1.0f);
        }
        break;
    case 0xF:
        if (naraku_check(i_this)) {
            if (i_this->mbNotInHomeRoom) {
                fopAcM_delete(actor);
            } else {
                i_this->mAction = ACTION_MODORU_MOVE;
                i_this->mState = 0x28;
                return;
            }
        }
        
        actor->shape_angle.y += 0x1000;
        if (i_this->mAcch.ChkGroundHit()) {
            actor->gravity = -3.0f;
            actor->attention_info.flags = fopAc_Attn_LOCKON_ENEMY_e;
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 3;
        }
        break;
    }
    
    i_this->mTargetAngleY = actor->current.angle.y;
    
    if (i_this->mState >= 0xC && i_this->mState != 0xF) {
        if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF) {
            if (!dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
                i_this->mCountDownTimers[2] = 20*30;
                body_atari_check(i_this);
                return;
            }
            
            i_this->mSwitch = 0xFF;
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 0;
            
            if (fopAcM_CheckStatus(actor, fopAcStts_CARRY_e)) {
                fopAcM_cancelCarryNow(actor);
                actor->attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
                actor->gravity = -4.0f;
                actor->speed.y = 20.0f;
            }
            
            return;
        }
        
        if (i_this->mCountDownTimers[2] == 0) {
            if (i_this->mCurrBckIdx != AM2_BCK_BURUBURU) {
                anm_init(i_this, AM2_BCK_BURUBURU, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
                i_this->mCountDownTimers[3] = 20*30;
                actor->attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
                fopAcM_seStart(i_this, JA_SE_CM_AM2_RECOVER, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_AM2_AWAKE, 0);
            }
            
            if (i_this->mCountDownTimers[3] == 1) {
                if (fopAcM_CheckStatus(actor, fopAcStts_CARRY_e)) {
                    fopAcM_cancelCarryNow(actor);
                    actor->attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
                }
                fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
                actor->gravity = -4.0f;
                actor->speed.y = 20.0f;
                i_this->mBodyCyl.OnCoSetBit();
                i_this->mState = 0xF;
            }
        }
    }
    
    if (fopAcM_CheckStatus(actor, fopAcStts_CARRY_e) || i_this->mState == 0xF || !week_atari_check(i_this)) {
        body_atari_check(i_this);
    }
}

/* 00002B08-000032AC       .text action_itai__FP9am2_class */
static void action_itai(am2_class* i_this) {
    switch (i_this->mState) {
    case 0x14:
        for (int i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffTgSetBit();
        i_this->mNeedleCyl.ClrTgHit();
        
        i_this->mTargetAngleY = fopAcM_searchPlayerAngleY(i_this) + 0x8000;
        i_this->current.angle.y = fopAcM_searchPlayerAngleY(i_this) + 0x8000;
        i_this->speedF = 20.0f;
        
        fopAcM_monsSeStart(i_this, JA_SE_CV_AM2_DAMAGE, 0x42);
        dComIfGp_particle_set(0x81AE, &i_this->mWeakPos, &i_this->shape_angle);
        
        if (i_this->health > 0) {
            anm_init(i_this, AM2_BCK_DAMAGE, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
            if (i_this->mCountDownTimers[2] > 5) {
                i_this->speedF = 5.0f;
            }
            i_this->mState++;
        } else {
            i_this->mState = 0x16;
        }
        break;
    case 0x15:
        cLib_addCalc0(&i_this->speedF, 0.5f, 1.0f);
        if (i_this->speedF < 0.2f) {
            i_this->speedF = 0.0f;
            i_this->gravity = -3.0f;
            if (i_this->mCountDownTimers[2] < 5) {
                i_this->mAction = ACTION_DOUSA;
                i_this->mState = 3;
            } else {
                anm_init(i_this, AM2_BCK_MAHI, 1.0f, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, -1);
                i_this->mAction = ACTION_MAHI;
                i_this->mState = 0xC;
            }
        }
        break;
    case 0x16:
        i_this->mEyeSph.OffTgSetBit();
        i_this->mWeakSph.OffTgSetBit();
        i_this->mEyeSph.ClrTgHit();
        i_this->mWeakSph.ClrTgHit();
        anm_init(i_this, AM2_BCK_DEAD1, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        i_this->mState++;
        break;
    case 0x17:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mNeedleCyl.OnAtSetBit();
        i_this->mNeedleCyl.OnAtHitBit();
        i_this->speed.y = 25.0f;
        i_this->gravity = -10.0f;
        i_this->speedF = 10.0f;
        i_this->mCountDownTimers[0] = 100;
        i_this->current.angle.y = fopAcM_searchPlayerAngleY(i_this);
        anm_init(i_this, AM2_BCK_DEAD2, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        i_this->mState++;
        // Fall-through
    case 0x18:
        if (i_this->speed.y > 0.0f && i_this->mCountUpTimers[1] == 0) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_AM2_JUMP, 0x42);
            i_this->mCountUpTimers[1] = 1;
        }
        
        i_this->shape_angle.y += 0x1000;
        
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->mSmokeCb.end();
            dComIfGp_particle_setToon(0xA125, &i_this->current.pos, &i_this->shape_angle, NULL, 0xB9, &i_this->mSmokeCb, fopAcM_GetRoomNo(i_this));
            if (i_this->mSmokeCb.getEmitter()) {
                i_this->mSmokeCb.getEmitter()->setRate(12.0f);
                JGeometry::TVec3<f32> scale;
                scale.set(0.45f, 0.45f, 0.45f);
                i_this->mSmokeCb.getEmitter()->setGlobalScale(scale);
            }
            
            // Using the fopAcM_seStart inline multiple times in a single case makes the codegen not match.
            // fopAcM_seStart(i_this, JA_SE_CM_AM2_JUMP2, 0);
            mDoAud_seStart(JA_SE_CM_AM2_JUMP2, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_AM_JITABATA, 0x42);
            
            i_this->speed.y = 25.0f;
            i_this->gravity = -10.0f;
            i_this->speedF = 10.0f;
        }
        
        if (i_this->mCountDownTimers[0] == 0) {
            anm_init(i_this, AM2_BCK_DEAD3, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
            fopAcM_seStart(i_this, JA_SE_CM_AM2_BEF_EXPLODE, 0);
            
            i_this->speedF = 0.0f;
            
            i_this->mState++;
        }
        break;
    case 0x19:
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        
        cXyz centerPos = i_this->current.pos;
        centerPos.y += 50.0f;
        dComIfGp_particle_set(0x81AF, &i_this->current.pos, &i_this->shape_angle);
        dComIfGp_particle_set(0x81B0, &i_this->current.pos, &i_this->shape_angle);
        fopAcM_seStart(i_this, JA_SE_CM_AM2_EXPLODE, 0);
        fopAcM_createDisappear(i_this, &centerPos, 5);
        fopAcM_onActor(i_this);
        fopAcM_delete(i_this);
        break;
    }
    
    if (naraku_check(i_this)) {
        if (i_this->mbNotInHomeRoom || i_this->health <= 0) {
            if (i_this->mState != 0x19) {
                anm_init(i_this, AM2_BCK_DEAD3, 1.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
                fopAcM_seStart(i_this, JA_SE_CM_AM2_BEF_EXPLODE, 0);
                i_this->speedF = 0.0f;
                i_this->mState = 0x19;
            }
        } else {
            i_this->mAction = ACTION_MODORU_MOVE;
            i_this->mState = 0x28;
        }
    }
}

/* 000032AC-000034A4       .text action_handou_move__FP9am2_class */
static void action_handou_move(am2_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    switch (i_this->mState) {
    case 0x1E:
        i_this->speedF = 40.0f;
        s16 angleToPlayer = fopAcM_searchPlayerAngleY(i_this);
        i_this->current.angle.y = angleToPlayer + 0x8000;
        if (i_this->m2CE == 8) {
            i_this->current.angle.y = player->shape_angle.y - 0x4000;
            i_this->speedF = 40.0f;
        }
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffAtSetBit();
        i_this->mNeedleCyl.OffTgSetBit();
        i_this->mNeedleCyl.ClrTgHit();
        i_this->mTargetAngleY = i_this->current.angle.y;
        i_this->mState++;
    case 0x1F:
        fopAcM_seStart(i_this, JA_SE_CM_AM2_SLIP, 0);
        cLib_addCalc0(&i_this->speedF, 0.8f, 2.0f);
        if (i_this->speedF < 0.1f) {
            i_this->speedF = 0.0f;
            i_this->current.angle.y = i_this->shape_angle.y;
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 3;
            if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
                i_this->attention_info.flags = 0;
                i_this->mCountDownTimers[2] = 20*30;
                i_this->mAction = ACTION_MAHI;
                i_this->mState = 0xC;
            }
        }
    }
    
    if (naraku_check(i_this)) {
        if (i_this->mbNotInHomeRoom) {
            fopAcM_delete(i_this);
        } else {
            i_this->mAction = ACTION_MODORU_MOVE;
            i_this->mState = 0x28;
        }
    }
}

/* 000034A4-0000379C       .text action_modoru_move__FP9am2_class */
static void action_modoru_move(am2_class* i_this) {
    // Respawns the Armos back at its spawn point after it falls into an abyss.
    switch (i_this->mState) {
    case 0x28:
        dCam_getBody()->ForceLockOff(fopAcM_GetID(i_this));
        i_this->mInAbyssTimer = 0;
        i_this->mbMadeWaterSplash = false;
        i_this->mRippleCb.end();
        anm_init(i_this, AM2_BCK_WAIT, 10.0f, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, -1);
        fopAcM_seStart(i_this, JA_SE_CM_AM2_WTR_RECOVER, 0);
        i_this->mState++;
        // Fall-through
    case 0x29:
        cLib_addCalc0(&i_this->scale.x, 1.0f, 0.1f);
        i_this->scale.y = i_this->scale.z = i_this->scale.x;
        
        if (i_this->scale.x < 0.1f) {
            i_this->speedF = 0.0f;
            i_this->speed.setall(0.0f);
            i_this->gravity = -3.0f;
            i_this->mbMadeWaterSplash = false;
            i_this->mRippleCb.end();
            
            i_this->current.angle.y = i_this->shape_angle.y;
            i_this->current.pos = i_this->mSpawnPos;
            i_this->scale.setall(0.0f);
            i_this->shape_angle.y = i_this->mSpawnRotY;
            i_this->current.angle.y = i_this->shape_angle.y;
            i_this->current.pos = i_this->mSpawnPos;
            i_this->mTargetAngleY = i_this->current.angle.y;
            
            i_this->mState++;
        }
        break;
    case 0x2A:
        i_this->shape_angle.y = i_this->mSpawnRotY;
        i_this->current.angle.y = i_this->shape_angle.y;
        i_this->current.pos = i_this->mSpawnPos;
        i_this->mTargetAngleY = i_this->current.angle.y;
        
        cLib_addCalc2(&i_this->scale.x, 1.0f, 1.0f, 0.1f);
        i_this->scale.y = i_this->scale.z = i_this->scale.x;
        
        if (i_this->scale.x > 0.9f) {
            i_this->mCountUpTimers[1] = 0;
            i_this->scale.setall(1.0f);
            i_this->mWeakSph.OffTgSetBit();
            i_this->mNeedleCyl.OffAtSetBit();
            i_this->mNeedleCyl.OffCoSetBit();
            i_this->mNeedleCyl.OffTgSetBit();
            i_this->mWeakSph.ClrTgHit();
            i_this->mNeedleCyl.ClrTgHit();
            i_this->mAction = ACTION_DOUSA;
            i_this->mState = 0;
            
            if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
                i_this->attention_info.flags = 0;
                i_this->mCountDownTimers[2] = 20*30;
                i_this->mAction = ACTION_MAHI;
                i_this->mState = 0xC;
            }
        }
        break;
    }
}

/* 0000379C-00003AB8       .text daAM2_Execute__FP9am2_class */
static BOOL daAM2_Execute(am2_class* i_this) {
    fopAc_ac_c* actor = i_this; // Fixes regswaps
    
    for (int i = 0; i < ARRAY_SIZE(i_this->mCountDownTimers); i++) {
        if (i_this->mCountDownTimers[i] != 0) {
            i_this->mCountDownTimers[i]--;
        }
    }

    fopAcM_setGbaName(i_this, dItem_BOW_e, 0xB, 0x29);

    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpMorf->calc();
        return TRUE;
    }
    
    fopAcM_OnStatus(actor, fopAcStts_FREEZE_e);

    switch (i_this->mAction) {
    case ACTION_DOUSA:
        action_dousa(i_this);
        break;
    case ACTION_MAHI:
        action_mahi(i_this);
        break;
    case ACTION_ITAI:
        action_itai(i_this);
        break;
    case ACTION_HANDOU_MOVE:
        action_handou_move(i_this);
        break;
    case ACTION_MODORU_MOVE:
        action_modoru_move(i_this);
        break;
    }

    i_this->mpMorf->play(NULL, 0, 0);

    i_this->mpBtkAnm->play();
    i_this->mpBrkAnm->play();

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cXyz offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = actor->speedF;
    cXyz rotOffset;
    MtxPosition(&offset, &rotOffset);
    actor->speed.x = rotOffset.x;
    actor->speed.z = rotOffset.z;
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -50.0f) {
        actor->speed.y = -50.0f;
    }

    actor->attention_info.position = actor->current.pos;
    actor->attention_info.position.y += 120.0f;
    actor->eyePos = i_this->mEyeballPos;
    actor->eyePos.y -= 15.0f + g_regHIO.mChild[8].mFloatRegs[2];

    i_this->mBodyCyl.SetC(i_this->current.pos);
    i_this->mBodyCyl.SetH(150.0f);
    i_this->mBodyCyl.SetR(35.0f);
    dComIfG_Ccsp()->Set(&i_this->mBodyCyl);

    i_this->mNeedleCyl.SetC(i_this->mNeedlePos);
    i_this->mNeedleCyl.SetH(20.0f);
    i_this->mNeedleCyl.SetR(55.0f + g_regHIO.mChild[8].mFloatRegs[3]);
    dComIfG_Ccsp()->Set(&i_this->mNeedleCyl);

    i_this->mEyeSph.SetC(i_this->mEyeballPos);
    i_this->mEyeSph.SetR(30.0f);
    dComIfG_Ccsp()->Set(&i_this->mEyeSph);

    i_this->mWeakSph.SetC(i_this->mWeakPos);
    i_this->mWeakSph.SetR(30.0f);
    dComIfG_Ccsp()->Set(&i_this->mWeakSph);

    if (i_this->mBodyCyl.ChkCoSet()) {
        fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
    } else {
        fopAcM_posMove(actor, NULL);
    }
    
    if (i_this->mAction != ACTION_MODORU_MOVE) {
        BG_check(i_this);
    }
    
    draw_SUB(i_this);

    return TRUE;
}

/* 00003AB8-00003AC0       .text daAM2_IsDelete__FP9am2_class */
static BOOL daAM2_IsDelete(am2_class* i_this) {
    return TRUE;
}

/* 00003AC0-00003B18       .text daAM2_Delete__FP9am2_class */
static BOOL daAM2_Delete(am2_class* i_this) {
    dComIfG_resDelete(&i_this->mPhase, "AM2");

    i_this->mSmokeCb.end();
    i_this->mRippleCb.end();

    return TRUE;
}

/* 00003B18-00003E28       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_actor) {
    am2_class* i_this = (am2_class*)i_actor;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("AM2", AM2_BDL_AM2),
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("AM2", AM2_BCK_WAIT),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
        NULL,
        0x00000000,
        0x11020203
    );
    if (!i_this->mpMorf || !i_this->mpMorf->getModel()) {
        return FALSE;
    }
    J3DModel* model = i_this->mpMorf->getModel();
    
    i_this->mpBtkAnm = new mDoExt_btkAnm();
    if (!i_this->mpBtkAnm) { return FALSE; }
    J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("AM2", AM2_BTK_AM2);
    int ret = i_this->mpBtkAnm->init(model->getModelData(), pbtk, TRUE, 2, 1.0f, 0, -1, false, 0);
    if (!ret) { return FALSE; }
    if (!i_this->mpBtkAnm) { return FALSE; }
    
    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (!i_this->mpBrkAnm) { return FALSE; }
    J3DAnmTevRegKey* pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("AM2", AM2_BRK_AM2);
    ret = i_this->mpBrkAnm->init(model->getModelData(), pbrk, TRUE, 2, 1.0f, 0, -1, false, 0);
    if (!ret) { return FALSE; }
    if (!i_this->mpBrkAnm) { return FALSE; }
    
    i_this->mpMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }

    static Vec cyl_eye_offset[] = {
        {80.0f, -25.0f, 0.0f},
        {80.0f, -30.0f, 0.0f},
    };
    static Vec sph_offset[] = {
        {50.0f, 30.0f, 0.0f},
    };
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ 2, // Cylinder
            /* mJointIndex */ 0x00, // body joint
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ cyl_eye_offset,
        },
        {
            /* mShapeType  */ 1, // Sphere
            /* mJointIndex */ 0x00, // body joint
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ sph_offset,
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

/* 00003E70-00004250       .text daAM2_Create__FP10fopAc_ac_c */
static s32 daAM2_Create(fopAc_ac_c* i_actor) {
    fopAcM_SetupActor(i_actor, am2_class);

    am2_class* i_this = (am2_class*)i_actor;

    s32 phase_state = dComIfG_resLoad(&i_this->mPhase, "AM2");
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x1AA0)) {
            return cPhs_ERROR_e;
        }

        i_this->mSmokeCb.setRateOff(0);

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
            i_this->mAreaRadius = 600.0f;
        } else {
            i_this->mAreaRadius = i_this->mPrmAreaRadius * 100.0f;
        }

        if (i_this->mStartsInactive == 0 && i_this->mSwitch != 0xFF && dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            return cPhs_ERROR_e;
        }

        i_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("amos2", 0);
        i_this->max_health = 2;
        i_this->health = 2;
        i_this->stealItemLeft = 3;
        i_this->model = i_this->mpMorf->getModel();
        
        fopAcM_SetMtx(i_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(i_this, -50.0f, 0.0f, -20.0f, 60.0f, 180.0f, 60.0f);

        i_this->attention_info.flags = 0;

        i_this->mAcch.Set(
            fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this),
            i_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(i_this)
        );
        i_this->mStts.Init(254, 1, i_this);

        i_this->gravity = -3.0f;

        i_this->mEnemyIce.mpActor = i_this;
        i_this->mEnemyIce.mWallRadius = 50.0f;
        i_this->mEnemyIce.mCylHeight = 100.0f;
        i_this->attention_info.distances[4] = 9;
        
        fopAcM_OnStatus(i_this, fopAcStts_UNK8000000_e);

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
        i_this->mEyeSph.OffTgSetBit();

        static dCcD_SrcSph week_co_sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_UNK1000,
                /* SrcObjAt  Atp     */ 0,
                /* SrcObjAt  SPrm    */ 0,
                /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
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
        i_this->mWeakSph.Set(week_co_sph_src);
        i_this->mWeakSph.SetStts(&i_this->mStts);
        i_this->mWeakSph.OffTgSetBit();

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
                /* SrcObjAt  Atp     */ 1,
                /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_PLAYER,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_VS_UNK4 | CO_SPRM_VS_UNK8,
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
        i_this->mNeedleCyl.OffCoSetBit();
        i_this->mNeedleCyl.OffTgSetBit();

        i_this->m304 = i_this->current.pos;
        i_this->mTargetAngleY = i_this->current.angle.y;
        i_this->mSpawnPos = i_this->current.pos;
        i_this->mSpawnRotY = i_this->shape_angle.y;
        
        BG_check(i_this);
        draw_SUB(i_this);
        
        if (i_this->mStartsInactive == 1 && i_this->mSwitch != 0xFF && !dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo())) {
            i_this->attention_info.flags = 0;
            i_this->mCountDownTimers[2] = 20*30;
            i_this->mAction = ACTION_MAHI;
            i_this->mState = 0xC;
        }
        
        i_this->mAcchRadius = 40.0f + g_regHIO.mChild[8].mFloatRegs[10];
    }

    return phase_state;
}

static actor_method_class l_daAM2_Method = {
    (process_method_func)daAM2_Create,
    (process_method_func)daAM2_Delete,
    (process_method_func)daAM2_Execute,
    (process_method_func)daAM2_IsDelete,
    (process_method_func)daAM2_Draw,
};

actor_process_profile_definition g_profile_AM2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_AM2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(am2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00BE,
    /* Actor SubMtd */ &l_daAM2_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
