/**
 * d_a_ks.cpp
 * Enemy - Morth
 */

// Fakematch? Having sym off before d_a_ks.h but then turning it on before
// d_a_player_main.h fixes the weak function ordering of
// `daPy_py_c::getSwordTopPos() const` and `daPy_py_c::getHeadTopPos() const`
// in this TU.
#pragma sym off
#include "d/actor/d_a_ks.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "f_op/f_op_camera.h"
#include "d/d_snap.h"
#pragma sym on
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_gm.h"
#include "d/res/res_ks.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

static int KS_ALL_COUNT = 0;
static int KUTTUKU_ALL_COUNT = 0;
static BOOL HEAVY_IN = FALSE;
static int GORON_COUNT = 0;

/* 00000078-000002CC       .text draw_SUB__FP8ks_class */
void draw_SUB(ks_class* i_this) {
    J3DModel* pBodyModel = i_this->mpBodyMorf->getModel();
    J3DModel* pEyeModel = i_this->mpEyeMorf->getModel();

    cXyz local_24 = dComIfGp_getCamera(0)->mLookat.mEye - i_this->current.pos;

    int iVar3 = cM_atan2s(local_24.x, local_24.z);
    int iVar4 = (s16)-cM_atan2s(local_24.y, std::sqrtf(local_24.x * local_24.x + local_24.z * local_24.z));
    
    f32 fVar1 = 0.0f;
    if (i_this->m2D0) {
        fVar1 = i_this->m304;
    }

    mDoMtx_stack_c::transS(i_this->current.pos.x, i_this->current.pos.y + fVar1, i_this->current.pos.z);
    
    mDoMtx_stack_c::YrotM(iVar3);
    mDoMtx_stack_c::XrotM(iVar4);
    mDoMtx_stack_c::ZrotM(i_this->shape_angle.z + i_this->m2FA);

    cXyz local_18;
    local_18.setall(1.0f);

    i_this->m2FA += i_this->m2FE;

    mDoMtx_stack_c::scaleM(1.0f,1.0f,1.0f);

    mDoMtx_stack_c::ZrotM(i_this->shape_angle.z - i_this->m2FA);

    pBodyModel->setBaseTRMtx(mDoMtx_stack_c::get());

    mDoMtx_stack_c::transS(i_this->current.pos.x, i_this->current.pos.y + fVar1, i_this->current.pos.z);

    mDoMtx_stack_c::YrotM(i_this->shape_angle.y);
    mDoMtx_stack_c::XrotM(i_this->shape_angle.x);
    mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);

    mDoMtx_stack_c::scaleM(local_18);

    pEyeModel->setBaseTRMtx(mDoMtx_stack_c::get());

    enemy_fire(&i_this->mEnemyFire);
}

/* 000002CC-00000568       .text daKS_Draw__FP8ks_class */
static BOOL daKS_Draw(ks_class* i_this) {
    fopAc_ac_c* actor = i_this;

#if VERSION > VERSION_DEMO
    cXyz local_24 = i_this->current.pos - dComIfGp_getCamera(0)->mLookat.mEye;
    if (local_24.abs() < REG0_F(10) + 100.0f) {
        return TRUE;
    }
#endif

    J3DModel* pBodyModel = i_this->mpBodyMorf->getModel();
    J3DModel* pEyeModel = i_this->mpEyeMorf->getModel();

    cXyz local_18 = i_this->current.pos;
    local_18.y += 40.0f;

    dSnap_RegistFig(DSNAP_TYPE_KS, actor, 1.0f, 1.0f, 1.0f);

    if (i_this->m2C8 == 6) {
        return TRUE;
    }

    if (i_this->m2D0 == 0 && i_this->m2CD == 0) {
        draw_SUB(i_this);
    }

    i_this->m2CD = 0;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
    g_env_light.setLightTevColorType(pBodyModel, &i_this->tevStr);

    i_this->mpBodyBrkAnm->entry(pBodyModel->getModelData());
    i_this->mpBodyBrkAnm->setFrame(i_this->m320);

    i_this->mpBodyMorf->updateDL();

    i_this->mpBodyBrkAnm->remove(pBodyModel->getModelData());
    
    g_env_light.setLightTevColorType(pEyeModel, &i_this->tevStr);
    
    i_this->mpEyeBtkAnm->entry(pEyeModel->getModelData());
    i_this->mpEyeBtkAnm->setFrame(i_this->m302);

    i_this->mpEyeBrkAnm->entry(pEyeModel->getModelData());
    i_this->mpEyeBrkAnm->setFrame(i_this->m320);

    i_this->mpEyeMorf->updateDL();

    i_this->mpEyeBrkAnm->remove(pEyeModel->getModelData());
    i_this->mpEyeBtkAnm->remove(pEyeModel->getModelData());
    
    return TRUE;
}

/* 00000568-0000074C       .text naraku_check__FP8ks_class */
void naraku_check(ks_class* i_this) {
    cXyz local_24;
    cXyz local_18;

    if (i_this->mAcch.GetGroundH() != -G_CM3D_F_INF && dComIfG_Bgsp()->ChkPolySafe(i_this->mAcch.m_gnd) && dComIfG_Bgsp()->GetGroundCode(i_this->mAcch.m_gnd) == 4) {
        i_this->m2D3++;

        if (i_this->current.pos.y < -500.0f || i_this->m2D3 > 0x32) {
            i_this->speedF = 0.0;
            i_this->speed.setall(0.0f);
            i_this->gravity = 0.0f;

            fopAcM_delete(i_this);

            return;
        }
    }

    if (i_this->mAcch.ChkWaterIn() && i_this->current.pos.y < i_this->mAcch.m_wtr.GetHeight() + 20.0f) {
        if (!i_this->m2CF) {
            local_24 = i_this->current.pos;

            i_this->m2CF = 1;

            local_18.setall(0.5f);

            i_this->m52C.remove();
            dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &i_this->current.pos, NULL, &local_18, 0xFF, &i_this->m52C);
            i_this->m52C.setRate(0.0f);
        }

        cLib_addCalc2(&i_this->current.pos.y, i_this->mAcch.m_wtr.GetHeight() + 20.0f, 1.0f, 10.0);
        
        i_this->gravity = 0.0f;
        i_this->speed.y = 0.0f;
    }
    else if (i_this->m2CF && (i_this->mAcch.ChkGroundHit() || i_this->current.pos.y > i_this->mAcch.m_wtr.GetHeight() + 100.0f)) {
        i_this->m2CF = 0;

        i_this->m52C.remove();
    }
}

/* 0000074C-00000788       .text tyaku_check__FP8ks_class */
BOOL tyaku_check(ks_class* i_this) {
    if (i_this->mAcch.ChkGroundHit()) {
        return TRUE;
    }

    if (i_this->mAcch.ChkWaterIn()) {
        i_this->speed.y = 0.0f;
        i_this->gravity = 0.0f;
        return TRUE;
    }

    return FALSE;
}

/* 00000788-0000087C       .text ks_kuttuki_check__FP8ks_class */
BOOL ks_kuttuki_check(ks_class* i_this) {        
    fopAc_ac_c* mAtHitAc;    
    if (i_this->mSph.ChkAtHit() && !i_this->mSph.ChkAtShieldHit()) {
        mAtHitAc = i_this->mSph.GetAtHitAc();
        if (mAtHitAc && mAtHitAc == dComIfGp_getLinkPlayer() && KUTTUKU_ALL_COUNT >= 0 && KUTTUKU_ALL_COUNT < 20 && GORON_COUNT == 0) {
            i_this->mSph.OffTgSetBit();
            i_this->mSph.ClrCoSet();
            i_this->mSph.ClrTgHit();

            if (i_this->m2CF) {
                i_this->m2CF = 0;

                i_this->m52C.remove();
            }
            
            i_this->mAction = 4;
            i_this->mMode = 40;

            return TRUE;
        }
    }
    return FALSE;
}

/* 0000087C-000008F4       .text gm_birth_delet__FP8ks_class */
void gm_birth_delet(ks_class* i_this) {
    if (i_this->mGmID) {
        gm_class* i_gm = (gm_class*)fopAcM_SearchByID(i_this->mGmID);
        if (i_gm && fopAc_IsActor(i_gm) && fopAcM_GetName(i_gm) == PROC_GM && i_gm->m31E > 0) {
            i_gm->m31E--;
        }
    }
}

/* 000008F4-00000A98       .text shock_damage_check__FP8ks_class */
BOOL shock_damage_check(ks_class* i_this) {
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();

    if (link->checkHammerQuake()) {
        cXyz mSwordTopPos = link->getSwordTopPos();

        mSwordTopPos.x -= i_this->current.pos.x;
        mSwordTopPos.y -= i_this->current.pos.y;
        mSwordTopPos.z -= i_this->current.pos.z;
        
        float distXZ = std::sqrtf(mSwordTopPos.x * mSwordTopPos.x + mSwordTopPos.z * mSwordTopPos.z);
        
        if (distXZ < 200.0f) {
            if (std::sqrtf(mSwordTopPos.y * mSwordTopPos.y) < 40.0f) {
                i_this->mAction = 3;
                i_this->mMode = 32;

                return TRUE;
            }
        }
    }
    return FALSE;
}

/* 00000A98-00000DE8       .text body_atari_check__FP8ks_class */
BOOL body_atari_check(ks_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    cXyz mTgHitPos;
    cXyz mParticleScale;
    
    i_this->mStts.Move();
    
    if (i_this->mSph.ChkTgHit()) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

        cCcD_Obj* mTgHitObj = i_this->mSph.GetTgHitObj();

        mTgHitPos = *i_this->mSph.GetTgHitPosP();

        if (!mTgHitObj) {
            return FALSE;
        }

        a_this->current.angle.y = fopAcM_searchPlayerAngleY(a_this) + 0x8000;
        
        i_this->mAction = 3;

        switch (mTgHitObj->GetAtType()) {
            case AT_TYPE_WIND: {
                a_this->current.angle.y = cM_atan2s(a_this->current.pos.x - mTgHitPos.x, a_this->current.pos.z - mTgHitPos.z);
                
                i_this->mAction = 2;
                i_this->mMode = 20;

                return FALSE;
            }
#if VERSION > VERSION_DEMO
            case AT_TYPE_UNK8: {
                i_this->mMode = 32;

                a_this->health = 0;

                i_this->mMode = 30;

                return FALSE;
            }
#endif
            case AT_TYPE_SWORD: {
                if (i_this->mMode != 43 || i_this->m2CE) {
                    dScnPly_ply_c::setPauseTimer(2);
#if VERSION > VERSION_DEMO
                    a_this->stealItemBitNo = 1;
#endif
                }
                
                mParticleScale.setall(REG8_F(0) + 0.8f); 
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &mTgHitPos, &player->shape_angle, &mParticleScale);     
                
                break;
            }
            case AT_TYPE_SKULL_HAMMER: {
                if (player->getCutType() == 0x12 || player->getCutType() == 0x13) {
                    a_this->speedF = 0.0f;
                    a_this->gravity = 0.0f;
                    a_this->speed.setall(0.0f);

                    a_this->health = 0;

                    dScnPly_ply_c::setPauseTimer(2);

#if VERSION > VERSION_DEMO
                    a_this->stealItemBitNo = 1;
#endif

                    i_this->mMode = 32;

                    return TRUE;
                }

                break;
            }
            case AT_TYPE_FIRE:
            case AT_TYPE_FIRE_ARROW: {
                i_this->mEnemyFire.mFireDuration = 100;

                break;
            }
            case AT_TYPE_ICE_ARROW: {
                i_this->mEnemyIce.mFreezeDuration = 200;

                i_this->m2D0 = 1;

                i_this->mEnemyIce.mParticleScale = 0.2f;
                i_this->mEnemyIce.mYOffset = 0.0f;

                enemy_fire_remove(&i_this->mEnemyFire);

                break;
            }
            case AT_TYPE_LIGHT_ARROW: {
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 0.2f;
                i_this->mEnemyIce.mYOffset = 0.0f;

                i_this->m2D0 = 1;

                break;
            }
            default: {
                mParticleScale.setall(REG8_F(0) + 0.8f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &mTgHitPos, &player->shape_angle, &mParticleScale);
                break;
            }
        }

        a_this->health = 0;

        i_this->mMode = 30;
        
        return TRUE;
    }
    else {
        return shock_damage_check(i_this) ? 1 : 0;
    }
}

/* 00000DE8-00000EBC       .text speed_keisan__FP8ks_classs */
void speed_keisan(ks_class* i_this, short i_speed) {
    cMtx_YrotS(*calc_mtx, i_speed);
    
    s16 sVar1 = i_this->m30C * cM_ssin(i_this->m2F0[0]);

    cXyz local_14;
    local_14.x = sVar1;
    local_14.y = 0.0f;
    local_14.z = 0.0f;

    cXyz local_8;
    MtxPosition(&local_14, &local_8);
    
    i_this->current.pos.x += local_8.x;
    i_this->current.pos.z += local_8.z;
}

/* 00000EBC-00001314       .text action_dousa_move__FP8ks_class */
void action_dousa_move(ks_class* i_this) { 
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();

    switch (i_this->mMode) {
        case 0:
            i_this->m30C = 0.0f;

            i_this->gravity = -3.0f;
            
            for (int i = 0; i < 5; i++) {
                i_this->m2F0[i] = 0;
            }

            i_this->mMode++;
            // Fall-through
        case 1:
            cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 1, 0x1000);
            
            if (fopAcM_searchPlayerDistance(i_this) > 10000.0f) {
                break;
            }
            
            if (i_this->shape_angle.z > 0x100) {
                return;
            }

            i_this->shape_angle.z = 0;

            fopAcM_seStart(i_this, JA_SE_CM_KS_MOVE, 0);

            if (tyaku_check(i_this) != 0) {
                i_this->gravity = -3.0f;

                i_this->speed.y = 1.0f;
                i_this->speed.y += cM_rndF(5.0f);
            }

            i_this->current.angle.y = i_this->m2FC + fopAcM_searchPlayerAngleY(i_this);
            
            i_this->mMode++;
            // Fall-through
        case 2:
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->current.angle.y = i_this->m2FC + fopAcM_searchPlayerAngleY(i_this);
            }

            if (KUTTUKU_ALL_COUNT >= 0 && KUTTUKU_ALL_COUNT < 0x14 && 
                (link->getSpeedF() > 12.0f || HEAVY_IN) && 
                fopAcM_searchPlayerDistance(i_this) < 500.0f &&
                !dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e) &&
                tyaku_check(i_this)) {
                
                i_this->mAction = 1;
                i_this->mMode = 10;

                return;
            }

            if (link->getSpeedF() <= 12.0f || dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
                cLib_addCalc0(&i_this->speedF, 0.3f, cM_rndF(1.0f) + 0.3f);
                
                cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 1, 0x1000);
                
                i_this->m2FC = 0;
                break;
            }

            if (i_this->m2FC == 0) {
                i_this->m2FC = (fopAcM_GetID(i_this) & 0xf) * cM_rndFX(512.0f);
            }

            i_this->shape_angle.z = cM_rndFX(2000.0f);

            speed_keisan(i_this, i_this->current.angle.y);

            i_this->speedF = 12.0f;

            i_this->m2F0[0] += 1000;

            i_this->m30C = 10.0f;

            if (tyaku_check(i_this)) {
                fopAcM_seStart(i_this, JA_SE_CM_KS_MOVE, 0);

                i_this->gravity = -3.0f;

                i_this->speed.y = 1.0f;
                i_this->speed.y += cM_rndF(5.0f);
            }
            break;
        case 3:
            if (fopAcM_searchPlayerDistance(i_this) < 500.0f) {
                i_this->current.angle.y = fopAcM_searchPlayerAngleY(i_this);
            }
            break;
    }

    if (i_this->mMode == 2 || i_this->mMode == 3) {
        cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 1, 0x1000);
    }
    
    if (body_atari_check(i_this) != 0) {
        fopAcM_seStart(i_this, JA_SE_LK_LAST_HIT, 0);
    }
}

/* 00001314-00001630       .text action_kougeki_move__FP8ks_class */
void action_kougeki_move(ks_class* i_this) {    
    fopAc_ac_c* actor = i_this;
    cXyz head_top_pos = daPy_getPlayerActorClass()->getHeadTopPos();

    i_this->m31C = 20.0f;

    if (head_top_pos.y > actor->current.pos.y) {
        i_this->m31C = 60.0f;
    }

    switch (i_this->mMode) {
        case 10: {
            i_this->mSph.OffCoSetBit();

            actor->speedF = 26.0f;
            actor->gravity = -4.0f;
            actor->speed.y = 28.0f;

            for (int i = 0; i < 5; i++) {
                i_this->m2F0[i] = 0;
            }

            i_this->m30C = 0.0f;

            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor);
            
            fopAcM_seStart(actor, JA_SE_CM_KS_ATTACK, 0);
            
            fopAcM_monsSeStart(actor, JA_SE_CV_KS_ATTACK, 0);
            
            i_this->mMode++;
            
            break;
        }
        case 11: {
            if (actor->speedF > 0.0f && i_this->m2F0[1] == 0 && i_this->mSph.ChkAtShieldHit()) {
                actor->gravity = -4.0f;
                actor->speed.y = 25.0f;
                actor->speedF *= -0.5f;
                
                i_this->m2F0[1] = 1;
            }

            if (!i_this->m2F0[1] && ks_kuttuki_check(i_this)) {
                return;
            }

            if (!i_this->mAcch.ChkGroundHit() && !i_this->mAcch.ChkWaterIn()) {
                break;
            }

            i_this->mSph.OnCoSetBit();

            i_this->m2E8[2] = (s16)(cM_rndF(20.0f) + 20.0f);

            i_this->mMode++;
            // Fall-through
        }
        case 12:
            ks_kuttuki_check(i_this);

            if (tyaku_check(i_this)) {
                actor->gravity = -4.0f;
                actor->speed.y = 1.0f;
                actor->speed.y += cM_rndF(5.0f);
                actor->speedF = 16.0f;
            }
        
            if (i_this->m2E8[2] == 0) {
                actor->speedF = 0.0f;
                i_this->m31C = 20.0f;
                i_this->mAction = 0;
                i_this->mMode = 0;
            }
            break;
    }

    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x1000);
    
    if (body_atari_check(i_this)) {
        fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0);
    }
}

/* 00001630-00001874       .text action_kaze_move__FP8ks_class */
void action_kaze_move(ks_class* i_this) {
    switch (i_this->mMode) {
        case 20: {
            for (int i = 0; i < 5; i++) {
                i_this->m2F0[i] = 0;
            }
    
            i_this->m2E8[1] = 0x32;
    
            fopAcM_monsSeStart(i_this, JA_SE_CV_KS_BLOW, 0);

            i_this->m310 = i_this->current.pos.y;

            i_this->m30C = 0.0f;

            i_this->speedF = cM_rndF(15.0f) + 10.0f;
            i_this->m314 = cM_rndF(15.0f) + 10.0f;

            i_this->m308 = 0.0f;
            
            i_this->mMode++;
            // Fall-through
        }
        case 21: {
            cLib_addCalc2(&i_this->speed.y, i_this->m314, 0.8f, i_this->m308);
            
            cLib_addCalc2(&i_this->m308, 5.0f, 1.0f, 0.5f);
            
            if (i_this->m310 + 200.0f < i_this->current.pos.y || i_this->m2E8[1] == 0) {
                i_this->mMode++;
            }

            break;
        }
        case 22: {
            cLib_addCalc2(&i_this->gravity, -1.0f, 0.3f, 0.5f);
            
            if (i_this->speed.y < -2.0f) {
                i_this->speed.y = -2.0f;
            }

            cLib_addCalc0(&i_this->speedF, 0.5f, 2.0f);
            
            speed_keisan(i_this, i_this->shape_angle.y);

            i_this->m2F0[0] += 3000;

            i_this->m30C = 2.0f;

            if (tyaku_check(i_this)) {
                i_this->mAction = 0;
                i_this->mMode = 0;
                return;
            }
            break;
        }
    }

    i_this->shape_angle.z += 0x500;

    if (body_atari_check(i_this)) {
        fopAcM_seStart(i_this, JA_SE_LK_LAST_HIT, 0);
    }
}

static u8 item_tbl[4] = {0xA, 0xB, 0xC, 0xA};

/* 00001874-00001A14       .text dead_eff_set__FP8ks_classP4cXyz */
void dead_eff_set(ks_class* i_this, cXyz* i_pos) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    u8 drop_type;
    if (!strcmp(dComIfGp_getStartStageName(), "GanonK") && (i_this->stealItemBitNo != 0)) {
        if (dComIfGs_getLife() <= 8) {
            drop_type = daDisItem_HEART_e;
        }
        else if (cM_rndF(1.0f) < 0.5f) {
            if (dComIfGs_getArrowNum() == 0) {
                drop_type = daDisItem_ARROW_e;
            }
            else if (dComIfGs_getMagic() < dComIfGs_getMaxMagic() / 2) {
                drop_type = daDisItem_MAGIC_e;
            }
            else if (dComIfGs_getArrowNum() < 10) {
                drop_type = daDisItem_ARROW_e;
            }
            else {
                drop_type = item_tbl[(int)cM_rndF(2.99f)];
            }
        }
        else {
            drop_type = daDisItem_NONE13_e;
        }

        fopAcM_createDisappear(i_this, i_pos, 3, drop_type, 0xff);
    }
    else {
        fopAcM_seStart(i_this, JA_SE_CM_KS_DIE, 0);

        dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8068, i_pos);

        gm_birth_delet(i_this);
    }

    fopAcM_delete(a_this);
}

/* 00001A14-00001C5C       .text action_dead_move__FP8ks_class */
void action_dead_move(ks_class* i_this) {
    cXyz local_28;
    
    switch (i_this->mMode) {
        case 30: {
            for (int i = 0; i < 5; i++) {
                i_this->m2F0[i] = 0;
            }

            i_this->mSph.OffTgSetBit();
            i_this->mSph.ClrCoSet();
            i_this->mSph.ClrTgHit();

            fopAcM_monsSeStart(i_this, JA_SE_CV_KS_DAMAGE, 0);

            i_this->speedF = cM_rndF(5.0f) + 15.0f;
            i_this->gravity = -3.0f;
            i_this->speed.y = cM_rndF(5.0f) + 20.0f;

            i_this->mMode++;

            i_this->m2F0[1] = (s16)cM_rndFX(4096.0f);

            i_this->mSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            // Fall-through
        }
        case 31: {
            i_this->shape_angle.z += i_this->m2F0[1];

            if (tyaku_check(i_this)) {
                i_this->gravity = -3.0f;
                i_this->speedF *= 0.5f;

                switch (i_this->m2F0[0]) {
                    case 0:
                        i_this->speed.y = 13.0f;
                        i_this->m2F0[0]++;
                        break;
                    case 1:
                        i_this->speed.y = 7.0f;
                        i_this->m2F0[0]++;
                        break;
                    case 2:
                        local_28 = i_this->current.pos;
                        local_28.y += 20.0f;
                        dead_eff_set(i_this, &local_28);
                        break;
                }
            }
            break;
        }
        case 32: {
            local_28 = i_this->current.pos;
            local_28.y += 45.0f;
            dead_eff_set(i_this, &local_28);
            break;
        }
    }
}

u32 pl_harituki_joint_dt[20] = {
    0x20,
    0x21,
    0x25,
    0x26,
    0x02,
    0x03,
    0x04,
    0x1E,
    0x29,
    0x1F,
    0x24,
    0x08,
    0x06,
    0x07,
    0x05,
    0x0C,
    0x0A,
    0x0B,
    0x09,
    0x0e,
};

/* 00001C5C-000026DC       .text action_omoi__FP8ks_class */
void action_omoi(ks_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    cXyz local_1c;
    cXyz local_10;
    
    daPy_py_c* mpCurPlayerActor = (daPy_py_c*)daPy_getPlayerActorClass();
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    
    if (i_this->m2CE == 1 && HEAVY_IN == TRUE) {
        link->onHeavyState();
    }

    switch (i_this->mMode) {
        case 40: {
            i_this->m52C.remove();

            a_this->speedF = 0.0f;
            a_this->gravity = 0.0f;
            a_this->speed.setall(0.0f);

            if (GORON_COUNT != 0 || KUTTUKU_ALL_COUNT >= 0x14) {
                i_this->m528 = 0;

                fopAcM_OffStatus(a_this, fopAcStts_UNK4000_e);   

                i_this->mMode = 42;

                break;
            }

            for (int i = 0; i < 5; i++) {
                i_this->m2F0[i] = 0;
            }

            if (KUTTUKU_ALL_COUNT >= 0x14) {
                i_this->m300 = 0x13;
            }

            if (KUTTUKU_ALL_COUNT < 0) {
                i_this->m300 = 0;
            }
            else {
                i_this->m300 = KUTTUKU_ALL_COUNT;
            }

            i_this->m528 = link->getModelJointMtx(pl_harituki_joint_dt[i_this->m300]);

            if (KUTTUKU_ALL_COUNT == 0) {
                GORON_COUNT = 0;

                i_this->m2CE = 1;
            }

            KUTTUKU_ALL_COUNT++;

            if (HEAVY_IN == FALSE && KUTTUKU_ALL_COUNT >= 5) {
                link->onHeavyState();
                HEAVY_IN = TRUE;
            }

            i_this->m2D2 = 0;

            i_this->m2E8[1] = 0;
            i_this->m2E8[2] = 0;

            fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);

            fopAcM_setStageLayer(a_this);

            i_this->mMode++;
            // Fall-through
        }
        case 0x29: {
            fopAcM_SetRoomNo(a_this, fopAcM_GetRoomNo(mpCurPlayerActor));
            
            if (!(fopAcM_GetID(a_this) & 1)) {
                a_this->shape_angle.y += i_this->m2FE * 0.25f;
            }
            else {
                a_this->shape_angle.y -= i_this->m2FE * 0.25f;
            }

            if (i_this->m528) {
                local_10.x = i_this->m528[0][3];
                local_10.y = i_this->m528[1][3];
                local_10.z = i_this->m528[2][3];
            }
            else {
                local_10 = mpCurPlayerActor->current.pos;
            }

            if (!(local_10.x || local_10.y || local_10.z)) {
                local_10 = mpCurPlayerActor->current.pos;
            }

            local_1c.x = std::fabsf(mpCurPlayerActor->speed.x * 10.0f);
            if (local_1c.x < REG12_F(16) + 10.0f) {
                local_1c.x = REG12_F(16) + 10.0f;
            }

            local_1c.y = std::fabsf(mpCurPlayerActor->speed.y * 10.0f);
            if (local_1c.y < REG12_F(16) + 10.0f) {
                local_1c.y = REG12_F(16) + 10.0f;
            }

            local_1c.z = std::fabsf(mpCurPlayerActor->speed.z * 10.0f);
            if (local_1c.z < REG12_F(16) + 10.0f) {
                local_1c.z = REG12_F(16) + 10.0f;
            }

            if (std::sqrtf(mpCurPlayerActor->speed.x * mpCurPlayerActor->speed.x + mpCurPlayerActor->speed.y * mpCurPlayerActor->speed.y + mpCurPlayerActor->speed.z * mpCurPlayerActor->speed.z) < REG12_F(17) + 8.0f) {
                local_1c.setall(REG12_F(18) + 8.0f);

                f32 x = a_this->current.pos.x - local_10.x;
                f32 y = a_this->current.pos.y - local_10.y;
                f32 z = a_this->current.pos.z - local_10.z;

                if (std::sqrtf(x * x + y * y + z * z) < 2.0f && i_this->m2E8[1] == 0) {
                    i_this->m2E8[1] = cM_rndF(10.0f) + 10.0f;

                    switch (i_this->m2D2) {
                        case 0: {
                            if (i_this->m300 < 0x13) {
                                i_this->m300++;
                            }
                            else {
                                i_this->m2D2 = 1;
                                i_this->m300--;
                            }
                            break;
                        }
                        case 1: {
                            if (i_this->m300 > 0) {
                                i_this->m300--;
                            }
                            else {
                                i_this->m2D2 = 0;
                                i_this->m300++;
                            }
                            break;
                        }
                    }

                    if (i_this->m300 >= 0x14) {
                        i_this->m300 = 0x13;
                    }
                    else if (i_this->m300 < 0) {
                        i_this->m300 = 1;
                    }

                    i_this->m528 = link->getModelJointMtx(pl_harituki_joint_dt[i_this->m300]);
                }
            }

            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK800000_e) || dComIfGp_checkPlayerStatus1(0, daPyStts1_UNK10_e)) {
                local_1c.setall(100.0f);
            }

            cLib_addCalc2(&a_this->current.pos.x, local_10.x, 1.0f, local_1c.x);
            cLib_addCalc2(&a_this->current.pos.y, local_10.y, 1.0f, local_1c.y);
            cLib_addCalc2(&a_this->current.pos.z, local_10.z, 1.0f, local_1c.z);
            
            if (link->checkFrontRollCrash() || link->getCutType() == 8 || link->getCutType() == 9 || dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
                i_this->mSph.OnCoSetBit();
                i_this->mSph.OnTgSetBit();

                if (i_this->m2CE) {
                    link->offHeavyState();
                    HEAVY_IN = FALSE;

                    KUTTUKU_ALL_COUNT = 0;
                    GORON_COUNT = 0;

                    i_this->m2F0[0] = 0;
                    i_this->m2F0[1] = 0;
                }

                i_this->mMode = 42;

                return;
            }

            if (!link->checkFrontRoll()) {
                if (i_this->m2CE == 0) {
                    return;
                }
                
                if (i_this->m2F0[1]) {
                    i_this->m2F0[1] = 0;
                    i_this->m2E8[2] = 0x32;
                }

                if (i_this->m2E8[2] != 1) {
                    return;
                }

                if (i_this->m2F0[0] <= 0) {
                    return;
                }

                i_this->m2F0[0] = 0;

                return;
            }

            if (i_this->m2CE) {
                if (i_this->m2F0[1]) {
                  return;
                }

                switch (i_this->m2F0[0]) {
                    case 0:
                        GORON_COUNT = KUTTUKU_ALL_COUNT * 0.25f;
                        break;
                    case 1:
                        GORON_COUNT = KUTTUKU_ALL_COUNT * 0.5f;
                        break;
                    case 2:
                        GORON_COUNT = KUTTUKU_ALL_COUNT;
                        break;
                }
                
                if (GORON_COUNT == 0) {
                    GORON_COUNT = 1;
                }
                i_this->m2F0[0]++;
                i_this->m2F0[1] = 1;

                if (i_this->m2F0[0] < 3 && KUTTUKU_ALL_COUNT >= 3) {
                    return;
                }

                i_this->m2CE = 0;

                link->offHeavyState();
                HEAVY_IN = FALSE;

                i_this->m2F0[0] = 0;
                i_this->m2F0[1] = 0;

                if (KUTTUKU_ALL_COUNT > 0) {
                    KUTTUKU_ALL_COUNT--;
                }

                GORON_COUNT = KUTTUKU_ALL_COUNT;

                i_this->mMode = 42;

                return;
            }

            if (KUTTUKU_ALL_COUNT != 0 && GORON_COUNT > 0) {
                GORON_COUNT--;
                KUTTUKU_ALL_COUNT--;

                if (HEAVY_IN && KUTTUKU_ALL_COUNT < 5) {
                    HEAVY_IN = FALSE;
                    link->offHeavyState();
                }

                i_this->mMode = 42;
            }

            break;
        }
        case 42: {
            if (i_this->m528) {
                fopAcM_OffStatus(a_this, fopAcStts_UNK4000_e);
                
                fopAcM_setRoomLayer(a_this, fopAcM_GetRoomNo(a_this));
                
                i_this->m528 = 0;
            }

            i_this->current.angle.y = fopAcM_searchPlayerAngleY(a_this) + 0x8000;
            i_this->current.angle.y += (s16)cM_rndFX(16384.0f);

            i_this->speedF = 15.0f;
            i_this->gravity = -3.0f;
            i_this->speed.y = 26.0f;

            i_this->mMode++;
            // Fall-through
        }
        case 43: {
            if (i_this->mAcch.ChkGroundHit() || i_this->mAcch.ChkWaterIn()) {
                i_this->m2E8[2] = (s16)(cM_rndF(40.0f) + 40.0f);

                i_this->mSph.OnCoSetBit();
                i_this->mSph.OnTgSetBit();

                i_this->mAction = 1;
                i_this->mMode = 12;
            }
            break;
        }
    }

    if (i_this->mMode == 43 && body_atari_check(i_this) && i_this->m2CE) {
        fopAcM_seStart(a_this, JA_SE_LK_LAST_HIT, 0);
        i_this->m2CE = 0;
    }
}

/* 000026DC-000027A0       .text tsubo_search__FPvPv */
BOOL tsubo_search(void* param_1, void* param_2) {
    ks_class* i_ks1 = (ks_class*)param_1;
    ks_class* i_ks2 = (ks_class*)param_2;
    
    if (fopAc_IsActor(i_ks1) && (fopAcM_GetName(i_ks1) == 0x1cb) &&
        std::fabsf(i_ks1->current.pos.x - i_ks2->current.pos.x) < 20.0f &&
        std::fabsf(i_ks1->current.pos.y - i_ks2->current.pos.y) < 20.0f &&
        std::fabsf(i_ks1->current.pos.z - i_ks2->current.pos.z) < 20.0f) {
        i_ks2->mKsID = fopAcM_GetID(i_ks1);
    }
    return FALSE;
}

/* 000027A0-00002A40       .text action_tubo_search__FP8ks_class */
void action_tubo_search(ks_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    switch (i_this->mMode) {
        case 50: {
            i_this->mKsID = fpcM_ERROR_PROCESS_ID_e;

            fpcEx_Search((fpcLyIt_JudgeFunc)tsubo_search, a_this);

            if (i_this->mKsID == fpcM_ERROR_PROCESS_ID_e) {
                fopAcM_delete(a_this);
            }
            else {
                i_this->mMode++;
            }
            
            break;
        }
        case 51: {
            fopAc_ac_c* mpCurrActor = (fopAc_ac_c*)fopAcM_SearchByID(i_this->mKsID);

            if (mpCurrActor) {
                a_this->current.pos = mpCurrActor->current.pos;

                if (!i_this->m318) {
                    return;
                }

                if (fopAcM_searchPlayerDistance(a_this) > i_this->m318) {
                    return;
                }
            }

            i_this->m31C = 100.0f;

            i_this->mSph.OffAtNoTgHitInfSet();

            i_this->mSph.OnAtVsBitSet(cCcD_AtSPrm_VsOther_e);

            i_this->mSph.OffAtVsBitSet(cCcD_AtSPrm_VsPlayer_e);
            i_this->mSph.OffAtSPrmBit(cCcD_AtSPrm_NoTgHitInfSet_e);

            i_this->mSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);

            i_this->mSph.OnAtHitBit();

            i_this->mSph.SetC(i_this->current.pos);
            i_this->mSph.SetR(i_this->m31C);

            dComIfG_Ccsp()->Set(&i_this->mSph);

            i_this->mMode++;

            break;
        }
        case 52: {
            i_this->mSph.SetC(a_this->current.pos);
            i_this->mSph.SetR(i_this->m31C);

            dComIfG_Ccsp()->Set(&i_this->mSph);

            if (i_this->m2C9 > 0x15 || i_this->m2C9 == 0) {
                i_this->m2C9 = 1;
            }

            for (int i = 0; i < i_this->m2C9; i++) {
                cXyz local_24 = a_this->current.pos;
                local_24.y += cM_rndF(40.0f);

                if (i != 0) {
                    local_24.x += cM_rndFX(40.0f);
                    local_24.z += cM_rndFX(40.0f);
                }

                a_this->shape_angle = a_this->current.angle;
                a_this->shape_angle.x = 0;

                fopAcM_create(PROC_KS, 3, &local_24, fopAcM_GetRoomNo(a_this), &a_this->shape_angle, &a_this->scale, 0);
            }

            fopAcM_delete(a_this);
            break;
        }
    }
}

/* 00002A40-00002BC4       .text action_kb_birth_check__FP8ks_class */
void action_kb_birth_check(ks_class* i_this) {
    switch (i_this->mMode) {
        case 60: {
            i_this->current.pos.y += REG8_F(13) + 30.0f;
            i_this->current.angle.y = cM_rndFX(32767.0f);

            i_this->speedF = REG8_F(8) + 4.0f + cM_rndF(REG8_F(9) + 4.0f);
            i_this->speed.y = REG8_F(10) + 20.0f + cM_rndF(REG8_F(11) + 5.0f);
            i_this->gravity = -(REG8_F(12) + 2.0f);

            i_this->mMode++;
            // Fall-through
        }
        case 61: {
            if (i_this->speed.y <= 0.0f && (i_this->mAcch.ChkGroundHit() || i_this->mAcch.GetGroundH() + (REG8_F(19) + 10.0f) > i_this->current.pos.y )) {
                fopAcM_OffStatus(i_this, fopAcStts_UNK4000_e);

                i_this->speedF = 0.0f;
                i_this->gravity = 0.0f;
                i_this->speed.setall(0.0f);

                i_this->mAction = 0;
                i_this->mMode = 0;
            }
            break;
        }
    } 
}

/* 00002BC4-00002C54       .text BG_check__FP8ks_class */
void BG_check(ks_class* i_this) {
    i_this->mAcchCir.SetWall(30.0f, 30.0f);

    i_this->current.pos.y -= i_this->m304;
    i_this->old.pos.y -= i_this->m304;

    i_this->mAcch.CrrPos(*dComIfG_Bgsp());

    i_this->current.pos.y += i_this->m304;
    i_this->old.pos.y += i_this->m304;
}

/* 00002C54-00003054       .text daKS_Execute__FP8ks_class */
static BOOL daKS_Execute(ks_class* i_this) {    
    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpBodyMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpEyeMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        if (i_this->m2D0 && (i_this->m320++, i_this->m320 > 7.0f)) {
            i_this->m320 = 7.0f;
        }
        return TRUE;
    }

    for (int i = 0; i < 4; i++) {
        if (i_this->m2E8[i]) {
            i_this->m2E8[i]--;
        }
    }

    if (i_this->mGmID != 0 && i_this->mAction != 3) {
        fopAc_ac_c* mpGmActor = fopAcM_SearchByID(i_this->mGmID);

        bool bVar5 = false;

        if (mpGmActor && ((fopAcM_GetParam(mpGmActor) & 0xff0000) == 0xff0000 || (fopAcM_GetParam(mpGmActor) & 0xff0000) == 0)) {
            if (fopAcM_GetName(mpGmActor) == PROC_GM) {
                if (mpGmActor->health <= 0) {
                    bVar5 = true;
                }
            }
            else {
                bVar5 = true;
            }

            if (bVar5) {
                if (i_this->mAction != 4) {
                    i_this->mAction = 3;
                    i_this->mMode = 30;
                }
                else {
                    if (i_this->mMode != 43) {
                        daPy_py_c* link = (daPy_py_c*)daPy_getPlayerLinkActorClass();
                        link->offHeavyState();

                        HEAVY_IN = FALSE;
                        GORON_COUNT = 0;

                        i_this->m2F0[0] = 0;
                        i_this->m2F0[1] = 0;

                        i_this->mMode = 42;
                    }
                }
            }
        }
    }

    switch(i_this->mAction) {
        case 0:
            action_dousa_move(i_this);
            ks_kuttuki_check(i_this);
            break;
        case 1:
            action_kougeki_move(i_this);
            break;
        case 2:
            action_kaze_move(i_this);
            break;
        case 3:
            action_dead_move(i_this);
            break;
        case 4:
            action_omoi(i_this);
            break;
        case 10:
            action_tubo_search(i_this);
            break;
        case 20:
            action_kb_birth_check(i_this);
            break;
    }

    if (i_this->m2C8 == 6) {
        return TRUE;
    }

    if (i_this->m302 && (i_this->m302++, i_this->m302 > 7)) {
        i_this->m302 = 0;
    }

    if (i_this->m2E8[0] == 0) {
        i_this->m2E8[0] = cM_rndFX(25.0f) + 50.0f;

        i_this->m302 = 1;
    }
    
    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);

    cXyz local_18;
    local_18.x = 0.0f;
    local_18.y = 0.0f;
    local_18.z = i_this->speedF;

    cXyz local_c;
    MtxPosition(&local_18, &local_c);

    i_this->speed.x = local_c.x;
    i_this->speed.z = local_c.z;

    if (i_this->mMode != 41 && !i_this->mAcch.ChkGroundHit() && !i_this->mAcch.ChkWaterIn()) {
        i_this->speed.y += i_this->gravity;

        if (i_this->speed.y < -20.0f) {
            i_this->speed.y = -20.0f;
        }
    }

    i_this->eyePos = i_this->current.pos;

    i_this->attention_info.position = i_this->eyePos;

    i_this->mSph.SetC(i_this->current.pos);
    i_this->mSph.SetR(i_this->m31C);

    dComIfG_Ccsp()->Set(&i_this->mSph);

    if (i_this->mSph.ChkCoSet() && (i_this->mAction == 0 || i_this->mAction == 2)) {
        fopAcM_posMove(i_this, i_this->mStts.GetCCMoveP());
    }
    else {
        fopAcM_posMove(i_this, NULL);
    }

    if (i_this->mMode != 41) {
        BG_check(i_this);
        naraku_check(i_this);
    }

    draw_SUB(i_this);

    i_this->m2CD = 1;

    return TRUE;
}

/* 00003054-0000305C       .text daKS_IsDelete__FP8ks_class */
static BOOL daKS_IsDelete(ks_class* i_this) {
    return TRUE;
}

/* 0000305C-000030F4       .text daKS_Delete__FP8ks_class */
static BOOL daKS_Delete(ks_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhs, "KS");

    i_this->m52C.remove();

    enemy_fire_remove(&i_this->mEnemyFire);

    KS_ALL_COUNT--;
    if (KS_ALL_COUNT == 0) {
        daPy_lk_c* link = daPy_getPlayerLinkActorClass();
        link->offHeavyState();

        KUTTUKU_ALL_COUNT = 0;
        HEAVY_IN = FALSE;
        GORON_COUNT = 0;
    }

    return TRUE;
}

/* 000030F4-000034B0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_act) {
    J3DModel* mpBodyModel;
    J3DModel* mpEyeModel;

    ks_class* i_this = (ks_class*)i_act;

    i_this->mpBodyMorf = new mDoExt_McaMorf((J3DModelData *)dComIfG_getObjectRes("KS", KS_BDL_KS_BODY), NULL, NULL, NULL, 
                                            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203);
    if (i_this->mpBodyMorf == NULL || i_this->mpBodyMorf->getModel() == NULL)
        return FALSE;
    mpBodyModel = i_this->mpBodyMorf->getModel();

    i_this->mpBodyBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBodyBrkAnm == NULL)
        return FALSE;

    if (i_this->mpBodyBrkAnm->init(mpBodyModel->getModelData(), (J3DAnmTevRegKey *)dComIfG_getObjectRes("KS", KS_BRK_KS_BODY), TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, FALSE, 0) == 0)
        return FALSE;

    
    i_this->mpEyeMorf = new mDoExt_McaMorf((J3DModelData *)dComIfG_getObjectRes("KS", KS_BDL_KS_EYE), NULL, NULL, 
                                      (J3DAnmTransformKey *)dComIfG_getObjectRes("KS", KS_BCK_MABATAKI), 
                                      J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);

    if (i_this->mpEyeMorf == NULL || i_this->mpEyeMorf->getModel() == NULL)
        return FALSE;
    mpEyeModel = i_this->mpEyeMorf->getModel();

    i_this->mpEyeBtkAnm = new mDoExt_btkAnm();
    if (i_this->mpEyeBtkAnm == NULL)
        return FALSE;

    if (i_this->mpEyeBtkAnm->init(mpEyeModel->getModelData(), (J3DAnmTextureSRTKey *)dComIfG_getObjectRes("KS", KS_BTK_KS_EYE), TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, FALSE, 0) == 0)
        return FALSE;
    
    i_this->mpEyeBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpEyeBrkAnm == NULL)
        return FALSE;

    if (i_this->mpEyeBrkAnm->init(mpEyeModel->getModelData(), (J3DAnmTevRegKey *)dComIfG_getObjectRes("KS", KS_BRK_KS_EYE), TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, FALSE, 0) == 0) {
        return FALSE;
    }
    return TRUE; 
}

static dCcD_SrcSph body_co_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_STALFOS_MACE,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_NoTgHitInfSet_e,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
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
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 15.0f,
    },
};

static s8 fire_j[10] = {
    0,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
     
};

static f32 fire_sc[10] = {
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
};

/* 000034F8-00003A94       .text daKS_Create__FP10fopAc_ac_c */
static cPhs_State daKS_Create(fopAc_ac_c* i_this) {
    fopAcM_SetupActor(i_this, ks_class);
    ks_class* a_this = (ks_class*)i_this;
    
    cPhs_State res;
    u32 parameters;
    res = dComIfG_resLoad(&a_this->mPhs, "KS");
    if (res == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x1060)) {
            return cPhs_ERROR_e;
        }

        a_this->m2C8 = fopAcM_GetParam(i_this);
        a_this->m2C9 = fopAcM_GetParam(i_this) >> 8;
        a_this->m2CA = fopAcM_GetParam(i_this) >> 0x10;

        if (a_this->m2C8 == 0xff) {
            a_this->m2C8 = 0;
        }

        if (a_this->m2C8 <= 1 && (a_this->m2C9 > 0x15 || a_this->m2C9 == 0)) {
            a_this->m2C9 = 1;
        }

        if (a_this->m2CA == 0xff) {
            a_this->m2CA = 0;
        }

        a_this->m318 = a_this->m2CA * 10.0f;

        if (a_this->m2C8 <= 1) {
            parameters = 2;
            if (a_this->m2C8 == 0) {
              parameters = 3;
            }

            for (int i = 0; i < a_this->m2C9; i++) {
                cXyz local_4c = i_this->current.pos;
                if (i != 0) {
                    if (i_this->current.angle.x != 0) {
                        local_4c.y += cM_rndFX(120.0f);
                        f32 ground_y = a_this->mAcch.GetGroundH();
                        if (local_4c.y < ground_y) {
                            local_4c.y = ground_y + cM_rndF(120.0f);
                        }
                    }
                    else {
                        local_4c.x += cM_rndFX(40.0f);
                        local_4c.z += cM_rndFX(40.0f);
                    }
                }
                i_this->shape_angle = i_this->current.angle;
                i_this->shape_angle.x = 0;

                fopAcM_create(PROC_KS, parameters, &local_4c, fopAcM_GetRoomNo(i_this), &i_this->shape_angle, &i_this->scale, 0);
            }

            return cPhs_ERROR_e;
        }

        if (KS_ALL_COUNT == 0) {
            KUTTUKU_ALL_COUNT = 0;
            HEAVY_IN = FALSE;
            GORON_COUNT = 0;
        }

        KS_ALL_COUNT++;

        fopAcM_SetMtx(i_this, a_this->mpBodyMorf->getModel()->getBaseTRMtx());

        fopAcM_setCullSizeBox(i_this, -20.0f, -20.0f, -20.0f, 20.0f, 20.0f, 20.0f);
        
        i_this->attention_info.flags = 0;
        
        a_this->mAcch.Set(fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this), i_this, 1, &a_this->mAcchCir, fopAcM_GetSpeed_p(i_this), NULL, NULL);
        
        a_this->mStts.Init(2, 1, i_this);
        
        i_this->max_health = 1;
        i_this->health = 1;

        a_this->m304 = 25.0f;

        a_this->m2E8[0] = cM_rndFX(25.0f) + 50.0f;

        a_this->m2DC.setall(1.0f);

        a_this->m2FE = (fopAcM_GetID(i_this) & 7) * 0x32 + 1000;

        a_this->mSph.Set(body_co_sph_src);
        a_this->mSph.SetStts(&a_this->mStts);

        a_this->mEnemyIce.mpActor = i_this;
        a_this->mEnemyIce.mWallRadius = 20.0f;
        a_this->mEnemyIce.mCylHeight = 20.0f;
        a_this->mEnemyIce.m1B0 = 1;

        a_this->mEnemyFire.mpMcaMorf = a_this->mpBodyMorf;
        a_this->mEnemyFire.mpActor = i_this;

        for (int i = 0; i < 10; i++) {
            a_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            a_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }

        i_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("kuro_s", 0);
        
        if (a_this->m2C8 == 4 || a_this->m2C8 == 5) {
            a_this->mGmID = fopAcM_GetLinkId(i_this);
            if (a_this->mGmID == fpcM_ERROR_PROCESS_ID_e) {
                return cPhs_ERROR_e;
            }

            fopAc_ac_c* i_act = fopAcM_SearchByID(a_this->mGmID);
            if (i_act && fopAc_IsActor(i_act) && fopAcM_GetName(i_act) == PROC_GM && a_this->m2C8 == 5) {
                i_this->current.angle.y += cM_rndFX(8192.0f);
                i_this->speedF = cM_rndF(6.0f) + 34.0f;
                i_this->speed.y = cM_rndF(8.0f) + 22.0f;
            }
        }

        a_this->m31C = 20.0f;

        if (a_this->m2C8 == 6) {
            a_this->mSph.OffTgSetBit();
            a_this->mSph.OffCoSetBit();
            a_this->mSph.ClrTgHit();

            a_this->mAction = 10;
            a_this->mMode = 50;

            return res;
        }
        
        if (a_this->m2C8 == 7) {
            fopAcM_OnStatus(i_this, fopAcStts_UNK4000_e);

            a_this->mAction = 20;
            a_this->mMode = 60;

            return res;
        }

        if (a_this->m2C8 == 2) {
            a_this->mAction = 0;
            a_this->mMode = 3;

            fopAcM_SetGravity(i_this, -3.0f);

            BG_check(a_this);
            
            if (!a_this->mAcch.ChkGroundHit()) {
                i_this->gravity = 0.0f;
            }

        }
    }
    
    return res;
}

static actor_method_class l_daKS_Method = {
    (process_method_func)daKS_Create,
    (process_method_func)daKS_Delete,
    (process_method_func)daKS_Execute,
    (process_method_func)daKS_IsDelete,
    (process_method_func)daKS_Draw,
};

actor_process_profile_definition g_profile_KS = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KS,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(ks_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KS,
    /* Actor SubMtd */ &l_daKS_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
