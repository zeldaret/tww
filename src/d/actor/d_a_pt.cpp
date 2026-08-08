/**
 * d_a_pt.cpp
 * Enemy - Miniblin / プチブリン (Petit Blin)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_pt.h"
#if VERSION > VERSION_DEMO
#include "d/actor/d_a_esa.h"
#endif
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_sea.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "res/Object/pt.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_kankyo_mng.h"

enum Action {
    ACTION_WAIT = 0,
    ACTION_MOVE = 1,
    ACTION_ATTACK = 2,
    ACTION_KOKE = 3,
    ACTION_PLES = 4,
    ACTION_BAT = 5,
};

/* 000000EC-00000110       .text __ct__10daPt_HIO_cFv */
daPt_HIO_c::daPt_HIO_c() {
    mNo = 0xFF;
    m05 = 0;
    m06 = 0;
}

static bool hio_set;
static daPt_HIO_c l_HIO;
static cXyz p_check_d[] = {
    cXyz(100.0f, 0.0f, 0.0f),
    cXyz(-100.0f, 0.0f, 0.0f),
    cXyz(0.0f, 100.0f, 0.0f),
    cXyz(0.0f, -100.0f, 0.0f),
    cXyz(0.0f, 0.0f, 100.0f),
    cXyz(0.0f, 0.0f, -100.0f),
};
static cXyz p_off_d[] = {
    cXyz(-3.0f, 0.0f, 0.0f),
    cXyz(3.0f, 0.0f, 0.0f),
    cXyz(0.0f, -3.0f, 0.0f),
    cXyz(0.0f, 3.0f, 0.0f),
    cXyz(0.0f, 0.0f, -3.0f),
    cXyz(0.0f, 0.0f, 3.0f),
};

/* 00000110-00000238       .text anm_init__FP8pt_classifUcfi */
static void anm_init(pt_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpMorf
            ->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Pt", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Pt", soundFileIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Pt", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000238-00000360       .text daPt_Draw__FP8pt_class */
static BOOL daPt_Draw(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (!i_this->mInitialSpawnWaitsUntilOffScreen) {
        J3DModel* model = i_this->mpMorf->getModel();
        g_env_light.setLightTevColorType(model, &actor->tevStr);
        i_this->mpBtpAnm->entry(model->getModelData());
        i_this->mpBrkAnm->entry(model->getModelData());
        i_this->mpMorf->entryDL();
        if (i_this->m326 != 0) {
#if VERSION == VERSION_DEMO
            dComIfGd_setSimpleShadow2(
                &actor->current.pos,
                i_this->mAcch.GetGroundH(),
                50.0f,
                i_this->mAcch.m_gnd,
                0,
                1.0f,
                dDlst_shadowControl_c::getSimpleTex()
            );
            i_this->m326 = 0;
#else
            cXyz pos(actor->current.pos.x, actor->current.pos.y + 100.0f, actor->current.pos.z);
            i_this->mShadowId = dComIfGd_setShadow(
                i_this->mShadowId,
                1,
                model,
                &pos,
                400.0f,
                50.0f,
                actor->current.pos.y,
                i_this->mAcch.GetGroundH(),
                i_this->mAcch.m_gnd,
                &actor->tevStr,
                0,
                1.0f,
                dDlst_shadowControl_c::getSimpleTex()
            );
            i_this->m326 = 0;
#endif
        }
    }
    dSnap_RegistFig(DSNAP_TYPE_PT, actor, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 0000039C-00000484       .text smoke_set__FP8pt_classSc */
static void smoke_set(pt_class* i_this, s8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;

    if (i_this->m7C0 == 0) {
        i_this->mSmokeCb.remove();
        emitter = dComIfGp_particle_setToon(
            dPa_name::ID_AK_JT_ELEMENTSMOKE00,
            &actor->current.pos,
            &actor->shape_angle,
            NULL,
            0xB9,
            &i_this->mSmokeCb,
            fopAcM_GetRoomNo(actor)
        );
        if (emitter != NULL) {
            emitter->setRate(3.0f);
            emitter->setSpread(0.5f);
            JGeometry::TVec3<f32> scale;
            scale.x = scale.y = scale.z = 1.0f;
            emitter->setGlobalScale(scale);
            scale.x = scale.y = scale.z = DEMO_SELECT(REG0_F(16) + 1.5f, 1.5f);
            emitter->setGlobalParticleScale(scale);
            i_this->m7C0 = param_2;
        }
    }
}

/* 00000484-0000093C       .text damage_check__FP8pt_class */
static void damage_check(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* hitObj;
#if VERSION > VERSION_DEMO
    cXyz local_54;
#endif
    CcAtInfo atInfo;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (i_this->m30E != 0) {
        return;
    }
    i_this->mStts.Move();
    if (i_this->mAtSph.ChkAtHit()) {
        hitObj = i_this->mAtSph.GetAtHitObj();
        fopAc_ac_c* hitActor = dCc_GetAc(hitObj->GetAc());
        if ((hitActor != NULL) && (fopAcM_GetName(hitActor) == fpcNm_PLAYER_e)) {
            if (player->checkPlayerGuard()) {
                i_this->m324 = fopAcM_searchPlayerAngleY(actor);
                i_this->m320 = DEMO_SELECT(REG0_F(18) + 40.0f, 40.0f);
            } else {
                i_this->mAction = ACTION_KOKE;
                i_this->mMode = 2;
                i_this->m30E = 6;
                return;
            }
        }
    }
#if VERSION > VERSION_DEMO
    if (player->checkHammerQuake()) {
        local_54 = player->current.pos - actor->current.pos;
        if (local_54.abs() < 350.0f) {
            i_this->mAction = ACTION_KOKE;
            i_this->mMode = 0;
            i_this->mTimers[1] = cM_rndF(30.0f) + 20.0f;
            smoke_set(i_this, 3);
            i_this->m30E = 10;
            actor->speed.y = 350.0f;
            return;
        }
    }
#endif
    if (!i_this->mCCSph.ChkTgHit()) {
        return;
    }
    i_this->m30E = 6;
    atInfo.mpObj = i_this->mCCSph.GetTgHitObj();
    atInfo.pParticlePos = i_this->mCCSph.GetTgHitPosP();
    if (atInfo.mpObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        enemy_fire_remove(&i_this->mEnemyFire);
        i_this->m7C0 = 0;
        i_this->mSmokeCb.remove();
        return;
    }
    if (atInfo.mpObj->ChkAtType(AT_TYPE_FIRE | AT_TYPE_FIRE_ARROW)) {
        i_this->mEnemyFire.mFireDuration = DEMO_SELECT(REG0_S(2) + 100, 100);
        i_this->m30E = 0x32;
    }
    if (atInfo.mpObj->ChkAtType(AT_TYPE_WIND)) {
        i_this->m324 = fopAcM_searchPlayerAngleY(actor);
        smoke_set(i_this, 5);
#if VERSION == VERSION_DEMO
        i_this->m320 = 100.0f;
#else
        i_this->m320 = cM_rndF(30.0f) + 90.0f;
        i_this->m310 = cM_rndFX(2000.0f);
#endif
        i_this->mAction = ACTION_KOKE;
        i_this->mMode = DEMO_SELECT(0, 10);
        smoke_set(i_this, 10);
        fopAcM_monsSeStart(actor, JA_SE_CV_PT_DAMAGE, 0);
        return;
    }
    cc_at_check(actor, &atInfo);
    if (atInfo.mResultingAttackType == 9) {
        if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
            i_this->mAction = ACTION_BAT;
            smoke_set(i_this, 0x1E);
        } else {
            i_this->mAction = ACTION_PLES;
        }
        i_this->mMode = 0;
        fopAcM_monsSeStart(actor, JA_SE_CV_PT_DIE, 0);
        i_this->m30E = 0x32;
        return;
    }
    i_this->m324 = fopAcM_searchPlayerAngleY(actor);
    smoke_set(i_this, 10);
    if (actor->health <= 0) {
        i_this->m30E = 0x32;
        fopAcM_monsSeStart(actor, JA_SE_CV_PT_DAMAGE, 0);
        i_this->mTimers[1] = DEMO_SELECT(REG0_F(5) + (cM_rndF(60.0f) + 60.0f), cM_rndF(60.0f) + 60.0f);
        i_this->m320 = 80.0f;
    } else {
        fopAcM_monsSeStart(actor, JA_SE_CV_PT_DIE, 0);
        i_this->m320 = 110.0f;
    }
    i_this->mAction = ACTION_ATTACK;
    i_this->mMode = 1;
}

/* 0000093C-00000D74       .text get_z_ang__FP8pt_class */
static s16 get_z_ang(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_f0;
    cXyz cStack_fc;
    cXyz cStack_108;
    dBgS_LinChk linChk;

    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    s16 iVar3 = 0;
    s32 iVar2 = 0;
    for (; iVar2 < 16; iVar2++, iVar3 += 0x1000) {
        MtxPush();
        cMtx_ZrotM(*calc_mtx, iVar3);
        local_f0.x = 10.0f;
        local_f0.y = 2.0f;
        local_f0.z = 0.0f;
        MtxPosition(&local_f0, &cStack_fc);
        local_f0.y = -5.0f;
        MtxPosition(&local_f0, &cStack_108);
        linChk.Set(&cStack_fc, &cStack_108, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            local_f0.x = -10.0f;
            local_f0.y = 2.0f;
            MtxPosition(&local_f0, &cStack_fc);
            local_f0.y = -5.0f;
            MtxPosition(&local_f0, &cStack_108);
            linChk.Set(&cStack_fc, &cStack_108, actor);
            if (dComIfG_Bgsp()->LineCross(&linChk)) {
                MtxPull();
                return iVar3;
            }
        }
        MtxPull();
    }
    return 0xDCF;
}

/* 000011AC-000018EC       .text next_pos_set__FP8pt_class */
static BOOL next_pos_set(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_b4;
    cXyz cStack_c0;
    cXyz cStack_cc;
    cXyz cStack_d8;
    dBgS_LinChk linChk;

    s16 temp_r0 = actor->current.angle.x;
    if ((temp_r0 < 0x2000) && (temp_r0 > -0x2000)) {
        s16 var_r21 = DEMO_SELECT(fopAcM_searchPlayerAngleY(actor), i_this->m2FC);
        if ((i_this->mTimers[1] != 0) ||
            ((i_this->mEnableSpawnSwitch != 0xFF) && (!dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, dComIfGp_roomControl_getStayNo()))) ||
            ((i_this->mDisableRespawnSwitch != 0xFF) && (dComIfGs_isSwitch(i_this->mDisableRespawnSwitch, dComIfGp_roomControl_getStayNo()))))
        {
            var_r21 += 0x8000;
        }
        var_r21 += (s16)cM_rndFX(4000.0f);
        cMtx_YrotS(*calc_mtx, var_r21);
        cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    } else {
        cMtx_YrotS(*calc_mtx, actor->current.angle.y + (s16)cM_rndFX(4000.0f));
        cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    }
    cMtx_ZrotM(*calc_mtx, actor->current.angle.z);
    local_b4.x = 0.0f;
    local_b4.y = DEMO_SELECT(REG6_F(0) + 200.0f, 200.0f);
    local_b4.z = DEMO_SELECT(REG6_F(1) + 200.0f, 200.0f);
    MtxPosition(&local_b4, &cStack_cc);
    cStack_cc += actor->current.pos;
    linChk.Set(&actor->current.pos, &cStack_cc, actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        i_this->m2E8 = linChk.GetCross();
        local_b4.y = -2.0f;
        local_b4.z = -2.0f;
        MtxPosition(&local_b4, &cStack_d8);
        i_this->m2E8 += cStack_d8;
        return TRUE;
    } else {
        local_b4.y = DEMO_SELECT(REG6_F(2) + -400.0f, -400.0f);
        local_b4.z = DEMO_SELECT(REG6_F(3) + 200.0f, 200.0f);
        MtxPosition(&local_b4, &cStack_c0);
        cStack_c0 += actor->current.pos;
        linChk.Set(&cStack_cc, &cStack_c0, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            i_this->m2E8 = linChk.GetCross();
            local_b4.y = 2.0f;
            local_b4.z = 0.0f;
            MtxPosition(&local_b4, &cStack_d8);
            i_this->m2E8 += cStack_d8;
            return TRUE;
        } else {
            local_b4.y = DEMO_SELECT(REG6_F(2) + -50.0f, -50.0f);
            local_b4.z = DEMO_SELECT(REG6_F(3) + -50.0f, -50.0f);
            MtxPosition(&local_b4, &cStack_cc);
            cStack_cc += actor->current.pos;
            linChk.Set(&cStack_c0, &cStack_cc, actor);
            if (dComIfG_Bgsp()->LineCross(&linChk)) {
                i_this->m2E8 = linChk.GetCross();
                local_b4.y = 0.0f;
                local_b4.z = 2.0f;
                MtxPosition(&local_b4, &cStack_d8);
                i_this->m2E8 += cStack_d8;
                return TRUE;
            } else {
                return FALSE;
            }
        }
    }
}

/* 000018EC-00001DC0       .text pt_move__FP8pt_class */
static void pt_move(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar6;
    cXyz local_28;
    cXyz local_34;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    local_34.set(0.0f, 0.0f, DEMO_SELECT(REG0_F(0) + 20.0f, 20.0f));
    switch (i_this->mMode) {
        case 0:
            if (next_pos_set(i_this)) {
                i_this->mMode = 1;
                local_28 = i_this->m2E8 - actor->current.pos;
                i_this->m31C = local_28.abs() * DEMO_SELECT(REG0_F(2) + 0.1f, 0.1f);
                if (!(i_this->m31C > 50.0f)) {
                    break;
                }
                i_this->m31C = 50.0f;
                break;
            } else {
                i_this->mAction = ACTION_ATTACK;
                i_this->mMode = 0;
                return;
            }
        case 1:
            local_28 = i_this->m2E8 - actor->current.pos;
            actor->current.angle.y = cM_atan2s(local_28.x, local_28.z);
            actor->current.angle.x = -cM_atan2s(local_28.y, std::sqrtf(SQUARE(local_28.x) + SQUARE(local_28.z)));
            sVar6 = get_z_ang(i_this);
            if (sVar6 != 0xDCF) {
                actor->current.angle.z = sVar6;
            }
            if (local_28.abs() < local_34.z * 1.5f) {
                if ((cM_rndF(1.0f) < 0.02f) && (actor->current.angle.x < 0x1000) && (actor->current.angle.x > -0x1000)) {
                    i_this->mAction = ACTION_KOKE;
                    i_this->mMode = 0;
                    smoke_set(i_this, 3);
                } else {
                    i_this->mMode = 2;
                    i_this->mTimers[0] = DEMO_SELECT(REG0_F(3) + (cM_rndF(5.0f) + 2.0f), cM_rndF(5.0f) + 2.0f);
                    anm_init(i_this, dRes_INDEX_PT_BCK_WAIT_e, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    fopAcM_seStart(actor, JA_SE_CM_PT_JUMP, 0);
                }
            } else {
                cMtx_YrotS(*calc_mtx, actor->current.angle.y);
                cMtx_XrotM(*calc_mtx, actor->current.angle.x);
                MtxPosition(&local_34, &actor->speed);
                actor->current.pos += actor->speed;
            }
            break;
        case 2:
            cLib_addCalc2(&actor->current.pos.x, i_this->m2E8.x, 1.0f, std::fabsf(actor->speed.x));
            cLib_addCalc2(&actor->current.pos.y, i_this->m2E8.y, 1.0f, std::fabsf(actor->speed.y));
            cLib_addCalc2(&actor->current.pos.z, i_this->m2E8.z, 1.0f, std::fabsf(actor->speed.z));
            sVar6 = get_z_ang(i_this);
            if (sVar6 != 0xDCF) {
                actor->current.angle.z = sVar6;
            }
            if (i_this->mTimers[0] == 0) {
                i_this->mMode = 0;
                anm_init(i_this, dRes_INDEX_PT_BCK_JUMP_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(actor, JA_SE_CV_PT_JUMP, 0);
            }
            break;
    }
#if VERSION == VERSION_DEMO
    if ((actor->current.pos.y - player->current.pos.y > -50.0f) && (fopAcM_searchPlayerDistanceXZ(actor) < REG0_F(13) + 500.0f))
#else
    if ((actor->current.pos.y - i_this->m2F8->y > -50.0f) && (i_this->m304 < 500.0f))
#endif
    {
        i_this->mAction = ACTION_ATTACK;
        i_this->mMode = 0;
    }
}

/* 00001DC0-000020D4       .text view_check__FP8pt_class */
static BOOL view_check(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
#if VERSION == VERSION_DEMO
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
#else
    cXyz local_98;
    local_98 = *i_this->m2F8;
    local_98.y += 100.0f;
#endif
    dBgS_LinChk linChk;
    linChk.Set(&actor->eyePos, DEMO_SELECT(&player->eyePos, &local_98), actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 000020D4-00002528       .text pt_attack__FP8pt_class */
static void pt_attack(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_2c;
    cXyz local_38;

    s16 sVar3 = DEMO_SELECT(fopAcM_searchPlayerAngleY(actor), i_this->m2FC);
    f32 dVar9 = DEMO_SELECT(fopAcM_searchPlayerDistance(actor), i_this->m300);
    if (i_this->mTimers[1] != 0) {
        sVar3 += 0x8000;
    }
    cLib_addCalcAngleS2(&actor->current.angle.y, sVar3, 4, 0x800);
    cLib_addCalcAngleS2(&actor->current.angle.x, 0, 2, 0x1000);
    cLib_addCalcAngleS2(&actor->current.angle.z, 0, 2, 0x1000);
    if ((i_this->mAcch.ChkGroundHit()) && (i_this->m314 < -100.0f)) {
        i_this->mAction = ACTION_KOKE;
        if (cM_rndF(1.0f) < 0.5f) {
            i_this->mMode = 1;
        } else {
            i_this->mMode = 0;
        }
        smoke_set(i_this, 5);
        return;
    }
    switch (i_this->mMode) {
        case 0:
            if (i_this->mTimers[0] == 0) {
                i_this->mMode = 1;
#if VERSION == VERSION_DEMO
                if (i_this->mAcch.ChkGroundHit()) {
                    anm_init(i_this, dRes_INDEX_PT_BCK_JUMP_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    cMtx_YrotS(*calc_mtx, sVar3 + (s16)cM_rndFX(4000.0f));
                    local_2c.x = 0.0f;
                    local_2c.y = REG0_F(7) + (50.0f + cM_rndFX(10.0f));
                    local_2c.z = REG0_F(8) + 30.0f;
                    MtxPosition(&local_2c, &actor->speed);
                    fopAcM_monsSeStart(actor, JA_SE_CV_PT_JUMP, 0);
                }
#endif
            } else {
                actor->speed.setall(0.0f);
            }
            break;
        case 1:
            if (i_this->mAcch.ChkGroundHit()) {
                if (cM_rndF(1.0f) < 0.02f) {
                    i_this->mAction = ACTION_KOKE;
                    i_this->mMode = 0;
                    smoke_set(i_this, 3);
                } else {
                    i_this->mMode = 2;
                    anm_init(i_this, dRes_INDEX_PT_BCK_BWALK_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    actor->speed.setall(0.0f);
#if VERSION > VERSION_DEMO
                    actor->speedF = 0.0f;
#endif
                    fopAcM_seStart(actor, JA_SE_CM_PT_JUMP, 0);
                }
            }
            break;
        case 2:
#if VERSION > VERSION_DEMO
            cLib_addCalc2(&actor->speedF, 20.0f, 1.0f, 4.0f);
#endif
            cMtx_YrotS(*calc_mtx, actor->current.angle.y);
            local_2c.x = 0.0f;
            local_2c.y = 0.0f;
            local_2c.z = DEMO_SELECT(REG0_F(9) + 20.0f, actor->speedF);
            MtxPosition(&local_2c, &local_38);
            actor->speed.x = local_38.x;
            actor->speed.z = local_38.z;
            if ((dVar9 < DEMO_SELECT(REG0_F(10) + 300.0f, 300.0f)) && (!view_check(i_this))) {
                i_this->mTimers[2] = (i_this->m2CC * 3) + 10;
                i_this->mMode = 3;
#if VERSION > VERSION_DEMO
                anm_init(i_this, dRes_INDEX_PT_BCK_WAIT_e, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
#endif
            }
#if VERSION == VERSION_DEMO
            else if (dVar9 > REG0_F(11) + 450.0f)
            {
                i_this->mMode = 0;
                i_this->mTimers[0] = REG0_F(3) + (2.0f + cM_rndF(10.0f));
                anm_init(i_this, dRes_INDEX_PT_BCK_WAIT_e, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
#endif
            break;
        case 3:
            if (i_this->mTimers[2] == 1) {
                anm_init(i_this, dRes_INDEX_PT_BCK_ATACK_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(actor, JA_SE_CV_PT_ATTACK, 0);
                fopAcM_seStart(actor, JA_SE_CM_PT_ATTACK, 0);
            }
            actor->speed.x *= DEMO_SELECT(REG0_F(14) + 0.8f, 0.8f);
            actor->speed.z *= DEMO_SELECT(REG0_F(14) + 0.8f, 0.8f);
            if (((i_this->mTimers[2] == 0) && (i_this->mpMorf->getFrame() >= 11.0f)) && (i_this->mpMorf->getFrame() <= 14.0f)) {
                i_this->m327 = 1;
            }
            if (i_this->mpMorf->isStop()) {
                i_this->mMode = 1;
            }
            break;
    }
    actor->current.pos += actor->speed;
    actor->speed.y -= DEMO_SELECT(REG0_F(12) + 7.0f, 7.0f);
    if (actor->speed.y < -120.0f) {
        actor->speed.y = -120.0f;
    }
    i_this->m326 = 1;
    if ((i_this->mAcch.ChkGroundHit()) && (DEMO_SELECT(fopAcM_searchPlayerDistance(actor), i_this->m300) > 700.0f)) {
        i_this->mAction = ACTION_MOVE;
        i_this->mMode = 0;
    }
}

/* 00002528-00002AC8       .text pt_wait__FP8pt_class */
static void pt_wait(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_b4;
    cXyz local_c0;

    camera_class* camera = static_cast<camera_class*>(dComIfGp_getCamera(0));
    dBgS_LinChk linChk;
    s8 bVar1 = false;
    i_this->m30E = 6;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    if (i_this->mInitialSpawnDelay != 0) {
        i_this->mInitialSpawnDelay--;
        return;
    }
    if ((l_HIO.m06 != 0) && (i_this->mEnableSpawnSwitch != 0xFF)) {
        dComIfGs_onSwitch(i_this->mEnableSpawnSwitch, dComIfGp_roomControl_getStayNo());
    }
    if (((i_this->mEnableSpawnSwitch != 0xFF) && (!dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, dComIfGp_roomControl_getStayNo()))) ||
        ((i_this->mDisableRespawnSwitch != 0xFF) && (dComIfGs_isSwitch(i_this->mDisableRespawnSwitch, dComIfGp_roomControl_getStayNo()))))
    {
        return;
    }
    if (fopAcM_searchPlayerDistance(actor) < (i_this->mNoticeRange * 100.0f)) {
        local_c0 = actor->current.pos;
        local_c0.y += 100.0f;
        linChk.Set(&camera->mLookat.mEye, &local_c0, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            bVar1 = true;
        } else {
            local_b4 = camera->mLookat.mCenter - camera->mLookat.mEye;
            s16 iVar3 = cM_atan2s(local_b4.x, local_b4.z);
            local_b4 = local_c0 - camera->mLookat.mEye;
            cMtx_YrotS(*calc_mtx, -iVar3);
            MtxPosition(&local_b4, &local_c0);
            if (local_c0.z < 0.0f) {
                bVar1 = true;
            }
        }
        if ((i_this->mInitialSpawnWaitsUntilOffScreen == 0) || (bVar1)) {
            fopAcM_OnStatus(actor, 0x36);
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mAction = ACTION_MOVE;
            i_this->mMode = 0;
            i_this->mInitialSpawnWaitsUntilOffScreen = 0;
        }
    }
}

/* 00002AC8-00002F30       .text pt_koke__FP8pt_class */
static void pt_koke(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    cLib_addCalcAngleS2(&actor->current.angle.x, 0, 2, 0x2000);
    cLib_addCalcAngleS2(&actor->current.angle.z, 0, 2, 0x2000);
    switch (i_this->mMode) {
        case 0:
            i_this->mMode = 4;
            anm_init(i_this, dRes_INDEX_PT_BCK_KOKE_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mTimers[0] = 0;
            fopAcM_monsSeStart(actor, JA_SE_CV_PT_TUMBLE, 0);
            break;
        case 1:
            i_this->mMode = 5;
            anm_init(i_this, dRes_INDEX_PT_BCK_SIRIMOTI_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mTimers[0] = 0;
            fopAcM_monsSeStart(actor, JA_SE_CV_PT_TUMBLE, 0);
            fopAcM_seStart(actor, JA_SE_CM_PT_TUMBLE, 0);
            break;
        case 2:
            i_this->mMode = 5;
            anm_init(i_this, dRes_INDEX_PT_BCK_HAPPY_e, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mTimers[0] = cM_rndF(20.0f) + 20.0f;
            fopAcM_monsSeStart(actor, JA_SE_CV_PT_HAPPY, 0);
            break;
        case 4:
            if ((int)i_this->mpMorf->getFrame() == 6) {
                fopAcM_seStart(actor, JA_SE_CM_PT_TUMBLE, 0);
            }
        case 5:
#if VERSION > VERSION_DEMO
            if (i_this->mTimers[1] != 0) {
                break;
            }
#endif
            if ((i_this->mpMorf->isStop()) || (i_this->mTimers[0] == 1)) {
                i_this->mAction = ACTION_MOVE;
                i_this->mMode = 0;
                anm_init(i_this, dRes_INDEX_PT_BCK_JUMP_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
            break;
#if VERSION > VERSION_DEMO
        case 10:
            i_this->mMode = 11;
            anm_init(i_this, dRes_INDEX_PT_BCK_KOKE_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_monsSeStart(actor, JA_SE_CV_PT_TUMBLE, 0);
            break;
        case 11:
            actor->current.angle.y += i_this->m310;
            if ((int)i_this->mpMorf->getFrame() == 6) {
                fopAcM_seStart(actor, JA_SE_CM_PT_TUMBLE, 0);
            }
            if (i_this->m320 < 0.05f) {
                i_this->mMode = 12;
                i_this->mTimers[0] = cM_rndF(30.0f);
            }
            break;
        case 12:
            if (i_this->mTimers[0] == 0) {
                i_this->mAction = ACTION_MOVE;
                i_this->mMode = 0;
                anm_init(i_this, dRes_INDEX_PT_BCK_JUMP_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
            break;
#endif
    }
    i_this->m326 = 1;
#if VERSION > VERSION_DEMO
    actor->current.pos.y += actor->speed.y;
    actor->speed.y -= 7.0f;
#endif
}

/* 00002F30-00003028       .text pt_ples__FP8pt_class */
static s32 pt_ples(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m30E = 5;
    actor->current.angle.z = 0;
    actor->current.angle.x = 0;
    switch (i_this->mMode) {
        case 0:
            i_this->mTimers[0] = 35;
            i_this->mMode = 1;
            anm_init(i_this, dRes_INDEX_PT_BCK_WAIT_e, 1.0f, J3DFrameCtrl::EMode_NONE, 5.0f, -1);
            // Fall-through
        case 1:
            cLib_addCalc2(&actor->scale.y, 0.1f, 1.0f, 0.5f);
            cLib_addCalc2(&actor->scale.x, 1.3f, 0.8f, 0.5f);
            if (i_this->mTimers[0] == 0) {
                return TRUE;
            }
        default:
            i_this->m326 = 1;
#if VERSION > VERSION_DEMO
            actor->current.pos.y += actor->speed.y;
            actor->speed.y -= 7.0f;
#endif
            return FALSE;
    }
}

/* 00003028-000031DC       .text pt_bat__FP8pt_class */
static s32 pt_bat(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_38;

    i_this->m30E = 5;
    switch (i_this->mMode) {
        case 0:
            i_this->mTimers[0] = 150;
            i_this->mMode = 1;
            anm_init(i_this, dRes_INDEX_PT_BCK_WAIT_e, 1.0f, J3DFrameCtrl::EMode_NONE, 5.0f, -1);
            i_this->m324 = (s16)cM_rndFX(6000.0f) + fopAcM_searchPlayerAngleY(actor) + 0x8000;
            cMtx_YrotS(*calc_mtx, i_this->m324);
            local_38.x = 0.0f;
            local_38.y = cM_rndF(20.0f) + 50.0f;
            local_38.z = 100.0f;
            MtxPosition(&local_38, &actor->speed);
            actor->current.angle.y = cM_rndFX(32768.0f);
            // Fall-through
        case 1:
            actor->current.angle.y += 0x400;
            actor->current.angle.x += 0x300;
            if (i_this->mTimers[0] == 0) {
                return TRUE;
            }
        default:
            i_this->m326 = 1;
            actor->current.pos += actor->speed;
            actor->speed.y -= 5.0f;
            if (actor->speed.y < -120.0f) {
                actor->speed.y = -120.0f;
            }
            if ((i_this->mAcch.ChkWallHit()) || ((actor->speed.y < 0.0f) && (i_this->mAcch.ChkGroundHit()))) {
                return TRUE;
            } else {
                return FALSE;
            }
            break;
    }
}

/* 000031DC-000036C0       .text water_check__FP8pt_class */
static s32 water_check(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar4;
    cXyz local_98;
    dBgS_ObjGndChk_Spl gndChk;

    Vec pos;
    pos = actor->current.pos;
    pos.y += 500.0f;
    gndChk.SetPos(&pos);
    fVar4 = dComIfG_Bgsp()->GroundCross(&gndChk);
    if ((fVar4 != -G_CM3D_F_INF) && (actor->current.pos.y <= fVar4)) {
        return TRUE;
    }
    if (daSea_ChkArea(actor->current.pos.x, actor->current.pos.z)) {
        f32 temp_f1_2 = daSea_calcWave(actor->current.pos.x, actor->current.pos.z) - 30.0f;
        if (actor->current.pos.y <= temp_f1_2) {
            actor->current.pos.y = temp_f1_2;
            local_98 = actor->current.pos;
            local_98.y = temp_f1_2;
            fopKyM_createWpillar(&local_98, DEMO_SELECT(REG7_F(9) + 1.0f, 1.0f), DEMO_SELECT(REG7_F(10) + 1.0f, 1.0f), 0);
            fopAcM_seStart(actor, JA_SE_OBJ_FALL_WATER_S, 0);
            return TRUE;
        }
    }
    return FALSE;
}

#if VERSION > VERSION_DEMO
/* 00003B00-00003B4C       .text esa_s_sub__FPvPv */
static void* esa_s_sub(void* param_1, void*) {
    if ((fopAcM_IsActor(param_1)) && (fopAcM_GetName(param_1) == fpcNm_ESA_e)) {
        return param_1;
    } else {
        return NULL;
    }
}
#endif

/* 00003B4C-00003F5C       .text action__FP8pt_class */
static void action(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int iVar2;
    cXyz local_28;
    cXyz cStack_34;

#if VERSION > VERSION_DEMO
    esa_class* esa = (esa_class*)fpcM_Search(esa_s_sub, i_this);
    if (esa != NULL) {
        i_this->m2F8 = &esa->current.pos;
        local_28 = esa->current.pos - actor->current.pos;
        i_this->m300 = local_28.abs();
        local_28.y = 0.0f;
        i_this->m304 = local_28.abs();
        i_this->m2FC = cM_atan2s(local_28.x, local_28.z);
    } else {
        i_this->m2F8 = &dComIfGp_getPlayer(0)->current.pos;
        i_this->m300 = fopAcM_searchPlayerDistance(actor);
        i_this->m304 = fopAcM_searchPlayerDistanceXZ(actor);
        i_this->m2FC = fopAcM_searchPlayerAngleY(actor);
    }
#endif
    iVar2 = 0;
    switch (i_this->mAction) {
        case ACTION_WAIT:
            pt_wait(i_this);
            break;
        case ACTION_MOVE:
            pt_move(i_this);
            break;
        case ACTION_ATTACK:
            pt_attack(i_this);
            break;
        case ACTION_KOKE:
            pt_koke(i_this);
            break;
        case ACTION_PLES:
            iVar2 = pt_ples(i_this);
            break;
        case ACTION_BAT:
            iVar2 = pt_bat(i_this);
            break;
    }
    damage_check(i_this);
    iVar2 += water_check(i_this);
    if (i_this->m320 > 0.01f) {
        local_28.x = 0.0f;
        local_28.y = 0.0f;
        local_28.z = -i_this->m320;
        cMtx_YrotS(*calc_mtx, i_this->m324);
        MtxPosition(&local_28, &cStack_34);
        actor->current.pos += cStack_34;
        cLib_addCalc0(&i_this->m320, 1.0f, DEMO_SELECT(REG8_F(12) + 7.0f, 7.0f));
        if ((actor->health <= 0) && ((i_this->mAcch.ChkWallHit()) || (i_this->m320 < 0.1f))) {
            iVar2++;
        }
        i_this->m326 = 1;
    }
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x2000);
    cLib_addCalcAngleS2(&actor->shape_angle.x, actor->current.angle.x, 4, 0x1000);
    cLib_addCalcAngleS2(&actor->shape_angle.z, actor->current.angle.z, 4, 0x1000);
    i_this->m318 += i_this->m31C;
    i_this->m31C -= 5.0f;
    if (i_this->m318 < 0.0f) {
        i_this->m318 = 0.0f;
    }
    if (i_this->m7C0 != 0) {
        i_this->m7C0--;
        if (i_this->m7C0 == 0) {
            i_this->mSmokeCb.remove();
        }
    }
    if (iVar2 != 0) {
        fopAcM_createDisappear(actor, &actor->eyePos, 5, 4, 0xff);
        fopAcM_delete(actor);
        fopAcM_onActor(actor);
        if (i_this->mBehaviorType == 0) {
            i_this->m2BA = 1;
        } else if (i_this->mDisableRespawnSwitch != 0xFF) {
            dComIfGs_onSwitch(i_this->mDisableRespawnSwitch, dComIfGp_roomControl_getStayNo());
        }
    }
}

/* 00003F5C-000043C8       .text daPt_Execute__FP8pt_class */
static BOOL daPt_Execute(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model;
    cXyz local_2c;
    cXyz local_38;

    local_2c.setall(0.0f);
    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->setPlayMode(J3DFrameCtrl::EMode_NONE);
        i_this->mpMorf->setPlaySpeed(3.0f);
        i_this->mpMorf->play(&actor->eyePos, 0, 0);
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpMorf->calc();
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    i_this->m2D0++;
    if (((i_this->m2D0 & 0x1F) == 0) && (actor->current.pos.y - actor->home.pos.y < -3000.0f)) {
        fopAcM_delete(actor);
        fopAcM_onActor(actor);
        if (i_this->mBehaviorType == 0) {
            i_this->m2BA = 1;
        } else if (i_this->mDisableRespawnSwitch != 0xFF) {
            dComIfGs_onSwitch(i_this->mDisableRespawnSwitch, dComIfGp_roomControl_getStayNo());
        }
        return TRUE;
    }
    for (s32 i = 0; i < ARRAY_SIZE(i_this->mTimers); i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }
    if (i_this->m30E != 0) {
        i_this->m30E--;
    }
    if (l_HIO.m05 == 0) {
        action(i_this);
        if (i_this->mInitialSpawnWaitsUntilOffScreen) {
            return TRUE;
        }
        if (i_this->m326 != 0) {
            dCcD_Stts* stts = &i_this->mStts;
            if (stts != NULL) {
                actor->current.pos.x += stts->GetCCMoveP()->x;
                actor->current.pos.y += stts->GetCCMoveP()->y;
                actor->current.pos.z += stts->GetCCMoveP()->z;
            }
            i_this->m314 = actor->speed.y;
            i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        }
        mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
        if (actor->scale.y < 0.9f) {
            mDoMtx_stack_c::scaleM(actor->scale.x, actor->scale.y, actor->scale.x);
        }
        mDoMtx_stack_c::YrotM(actor->shape_angle.y);
        mDoMtx_stack_c::XrotM(actor->shape_angle.x);
        mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
        mDoMtx_stack_c::transM(0.0f, i_this->m318, 0.0f);
        model = i_this->mpMorf->getModel();
        model->setBaseTRMtx(mDoMtx_stack_c::now);
        if (i_this->m2D6 != 0) {
            i_this->m2D6--;
            if (i_this->m2D6 <= 7) {
                i_this->mpBtpAnm->setFrame(i_this->m2D6);
            }
        } else {
            i_this->m2D6 = cM_rndF(30.0f) + 20.0f;
        }
        i_this->mpMorf->play(&actor->eyePos, 0, 0);
        i_this->mpBrkAnm->setFrame(i_this->m2CC);
        i_this->mpMorf->calc();
        enemy_fire(&i_this->mEnemyFire);
        MTXCopy(model->getAnmMtx(8), *calc_mtx);
        MtxPosition(&local_2c, &actor->eyePos);
        actor->attention_info.position = actor->eyePos;
#if VERSION > VERSION_DEMO
        actor->attention_info.position.y += 30.0f;
#endif
        i_this->mCCSph.SetC(actor->eyePos);
        i_this->mCCSph.SetR(DEMO_SELECT(REG0_F(11) + 40.0f, 40.0f));
        dComIfG_Ccsp()->Set(&i_this->mCCSph);
        if (i_this->m327 != 0) {
            MTXCopy(model->getAnmMtx(0xF), *calc_mtx);
            local_2c.x = DEMO_SELECT(REG0_F(19) + 50.0f, 50.0f);
            local_2c.y = 0.0f;
            local_2c.z = 0.0f;
            MtxPosition(&local_2c, &local_38);
            i_this->m327 = 0;
        } else {
            local_38.x = 20000.0f;
            local_38.y = 50000.0f;
            local_38.z = 20000.0f;
        }
        i_this->mAtSph.SetC(local_38);
        dComIfG_Ccsp()->Set(&i_this->mAtSph);
    }
    return TRUE;
}

/* 000043C8-000043D0       .text daPt_IsDelete__FP8pt_class */
static BOOL daPt_IsDelete(pt_class*) {
    return TRUE;
}

/* 000043D0-00004540       .text daPt_Delete__FP8pt_class */
static BOOL daPt_Delete(pt_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    dComIfG_resDeleteDemo(&i_this->mPhase, "Pt");
    if (i_this->mDC4 != false) {
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    i_this->mSmokeCb.remove();
    enemy_fire_remove(&i_this->mEnemyFire);
    if ((i_this->m2BA != 0) && ((i_this->mEnableSpawnSwitch == 0xFF) || (dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, fopAcM_GetRoomNo(actor)))) &&
        ((i_this->mDisableRespawnSwitch == 0xFF) || (!dComIfGs_isSwitch(i_this->mDisableRespawnSwitch, dComIfGp_roomControl_getStayNo()))))
    {
        fopAcM_prm_class* params = fopAcM_CreateAppend();
        params->base.position = actor->home.pos;
        params->base.angle = actor->home.angle;
        if (i_this->mRespawnDelay != 7) {
            params->base.angle.x = (i_this->mRespawnDelay * 0x14) + 0x14;
        }
        params->base.parameters = fopAcM_GetParam(actor) | 0x10;
        params->room_no = actor->current.roomNo;
        fopAcM_Create(fpcNm_PT_e, NULL, params);
    }
    return TRUE;
}

/* 00004540-000047D4       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    pt_class* i_this = (pt_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Pt", dRes_INDEX_PT_BDL_PT_e),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Pt", dRes_INDEX_PT_BCK_WAIT_e),
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpBtpAnm = new mDoExt_btpAnm();
    if (i_this->mpBtpAnm == NULL) {
        return FALSE;
    }
    J3DAnmTexPattern* pBtp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Pt", dRes_INDEX_PT_BTP_MABATAKI_e);
    if (!i_this->mpBtpAnm->init(i_this->mpMorf->getModel()->getModelData(), pBtp, 1, 0)) {
        return FALSE;
    }
    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm == NULL) {
        return FALSE;
    }
    J3DAnmTevRegKey* pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Pt", dRes_INDEX_PT_BRK_PT_e);
    if (!i_this->mpBrkAnm->init(i_this->mpMorf->getModel()->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    i_this->m2CC = cM_rndF(3.999f);
    return TRUE;
}

/* 0000481C-00004B1C       .text daPt_Create__FP10fopAc_ac_c */
static cPhs_State daPt_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* Radius */ 40.0f,
        }},
    };
    static dCcD_SrcSph at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
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
            /* Radius */ 25.0f,
        }},
    };

    pt_class* i_this = (pt_class*)a_this;

    fopAcM_ct_Retail(a_this, pt_class);
    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "Pt");
    if (res == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(a_this, pt_class);
        i_this->mBehaviorType = fopAcM_GetParam(a_this) & 0xF;
        i_this->mRespawnDelay = (fopAcM_GetParam(a_this) >> 5) & 7;
        i_this->mNoticeRange = (fopAcM_GetParam(a_this) >> 8);
        if ((fopAcM_GetParam(a_this) & 0x10) != 0) {
            i_this->mInitialSpawnWaitsUntilOffScreen = true;
        }
        i_this->mInitialSpawnDelay = a_this->current.angle.x;
        a_this->current.angle.x = 0;
        i_this->mDisableRespawnSwitch = (fopAcM_GetParam(a_this) >> 0x10);
        i_this->mEnableSpawnSwitch = (fopAcM_GetParam(a_this) >> 0x18);
        if ((i_this->mEnableSpawnSwitch != 0xFF) && (!dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, dComIfGp_roomControl_getStayNo()))) {
            i_this->mInitialSpawnWaitsUntilOffScreen = true;
        }
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Puti", 0);
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x4B000)) {
            return cPhs_ERROR_e;
        }
        if (hio_set == false) {
            i_this->mDC4 = true;
            hio_set = true;
            l_HIO.mNo = mDoHIO_createChild("プチブリン", &l_HIO); // Petit Blin
        }
        fopAcM_OnStatus(a_this, fopAcStts_CULL_e);
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->mAction = ACTION_WAIT;
        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mAcchCir.SetWall(50.0f, 50.0f);
        a_this->health = 2;
        a_this->max_health = 2;
        i_this->mStts.Init(100, 0, a_this);
        i_this->mCCSph.Set(cc_sph_src);
        i_this->mCCSph.SetStts(&i_this->mStts);
        i_this->mAtSph.Set(at_sph_src);
        i_this->mAtSph.SetStts(&i_this->mStts);
        a_this->stealItemLeft = 2;
        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mWallRadius = REG0_F(4) + 30.0f;
        i_this->mEnemyIce.mCylHeight = REG0_F(5) + 30.0f;
        i_this->mEnemyIce.mParticleScale = REG0_F(8) + 0.6f;
        i_this->mEnemyIce.mYOffset = REG0_F(9) + 40.0f;
        i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
        i_this->mEnemyFire.mpActor = a_this;
        static u8 fire_j[ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs)] = {
            0x08,
            0xFF,
            0x07,
            0xFA,
            0x0B,
            0xFF,
            0x0D,
            0xFF,
            0x00,
            0x00,
        };
        static f32 fire_sc[ARRAY_SIZE(i_this->mEnemyFire.mParticleScale)] = {
            1.0f,
            0.0f,
            0.7f,
            0.0f,
            0.6f,
            0.0f,
            0.6f,
            0.0f,
            0.0f,
            0.0f,
        };
        for (int i = 0; i < ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
            i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }
        daPt_Execute(i_this);
    }
    return res;
}

static actor_method_class l_daPt_Method = {
    (process_method_func)daPt_Create,
    (process_method_func)daPt_Delete,
    (process_method_func)daPt_Execute,
    (process_method_func)daPt_IsDelete,
    (process_method_func)daPt_Draw,
};

actor_process_profile_definition g_profile_PT = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_PT_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(pt_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_PT_e,
    /* Actor SubMtd */ &l_daPt_Method,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
