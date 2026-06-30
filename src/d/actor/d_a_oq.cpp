/**
 * d_a_oq.cpp
 * Enemy - Octorok
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_coming2.h"
#include "d/actor/d_a_oq.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_sea.h"
#include "d/d_jnt_hit.h"
#include "res/Object/oq.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "f_op/f_op_kankyo_mng.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/actor/d_a_bomb.h"

enum Action {
    ACTION_DOUSA = 10,
    ACTION_KOUGEKI = 11,
    ACTION_ITAI = 20,
    ACTION_TAMA_SHOOT = 30,
    ACTION_WAKIDASI = 100,
};

enum Mode {
    MODE_DOUSA_0 = 0,
    MODE_DOUSA_1 = 1,
    MODE_DOUSA_2 = 2,
    MODE_DOUSA_3 = 3,
    MODE_DOUSA_10 = 10,
    MODE_DOUSA_11 = 11,
    MODE_KOUGEKI_20 = 20,
    MODE_KOUGEKI_21 = 21,
    MODE_KOUGEKI_22 = 22,
    MODE_KOUGEKI_23 = 23,
    MODE_KOUGEKI_24 = 24,
    MODE_KOUGEKI_25 = 25,
    MODE_KOUGEKI_26 = 26,
    MODE_ITAI_30 = 30,
    MODE_ITAI_31 = 31,
    MODE_ITAI_32 = 32,
    MODE_ITAI_33 = 33,
    MODE_TAMA_SHOOT_40 = 40,
    MODE_TAMA_SHOOT_41 = 41,
    MODE_TAMA_SHOOT_42 = 42,
    MODE_WAKIDASI_50 = 50,
    MODE_WAKIDASI_51 = 51,
    MODE_WAKIDASI_52 = 52,
    MODE_WAKIDASI_53 = 53,
};

static s16 hazure_shoot_timer;
static csXyz roll_dt[] = {
    csXyz(0, 0x1000, 0x1000),
    csXyz(0, 0x1000, -0x1000),
    csXyz(0, -0x1000, 0x1000),
    csXyz(0, -0x1000, -0x1000),
};

/* 000000EC-00000208       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        oq_class* i_this = (oq_class*)model->getUserArea();
        if (i_this) {
            if (jntNo == 7 || jntNo == 8) {
                MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            }
            cXyz offset;
            if (jntNo == 8) {
                offset.x = 40.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m0334);
            }
            if (jntNo == 8) {
                offset.x = 20.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m0328);
            }
            if (jntNo == 7 || jntNo == 8) {
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 00000208-00000310       .text draw_SUB__FP8oq_class */
static void draw_SUB(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model;

    model = i_this->mpMorf->getModel();
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y + i_this->m0320, actor->current.pos.z);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    mDoMtx_stack_c::scaleM(actor->scale.x, actor->scale.y, actor->scale.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        i_this->mpMorf->calc();
        enemy_fire(&i_this->mEnemyFire);
    }
    if ((i_this->m02C0 != 3) && (i_this->m02C0 != 2)) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    }
}

/* 00000310-000004DC       .text daOQ_Draw__FP8oq_class */
static BOOL daOQ_Draw(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model;

    if ((i_this->m02C0 == 3) || (i_this->m02C0 == 2)) {
        return TRUE;
    }
    model = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(model, &actor->tevStr);
#if VERSION == VERSION_DEMO
    dSnap_RegistFig(DSNAP_TYPE_OQ, actor, 1.0f, 1.0f, 1.0f);
#else
    if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4 || (i_this->m02C0 == 5))) {
        dSnap_RegistFig(DSNAP_TYPE_OQ, actor, 2.75f, 2.75f, 2.75f);
    }
    if (i_this->m02C0 == 0) {
        dSnap_RegistFig(DSNAP_TYPE_OQ, actor, 1.0f, 1.0f, 1.0f);
    }
#endif
    if (((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) && (i_this->mEnemyIce.mFreezeTimer > 20)) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, NULL);
        return TRUE;
    }
    if (((i_this->m02C0 == 0) || (i_this->m02C0 == 1)) || (i_this->m02C0 == 4 || (i_this->m02C0 == 5))) {
        if (i_this->m02C0 != 0) {
            i_this->mpBrkAnm->entry(model->getModelData());
            i_this->mpBrkAnm->setFrame(i_this->m0318);
        }
        i_this->mpMorf->entryDL();
        if (i_this->m02C0 != 0) {
            i_this->mpBrkAnm->remove(model->getModelData());
        }
    } else if (i_this->m02C0 == 6) {
        i_this->mpMorf->updateDL();
        dComIfGd_setSimpleShadow2(&actor->current.pos, i_this->mAcch.GetGroundH(), 40.0f, i_this->mAcch.m_gnd, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }
    return TRUE;
}

/* 000004DC-00000608       .text anm_init__FP8oq_classifUcfi */
static void anm_init(oq_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->mCurrBckIdx = bckFileIdx;
    if (soundFileIdx >= 0) {
        i_this->mpMorf
            ->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("OQ", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("OQ", soundFileIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("OQ", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000608-00000D50       .text body_atari_check__FP8oq_class */
static BOOL body_atari_check(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    bool bVar2;
    fopAc_ac_c* hitActor;
    cCcD_Obj* hitObj;
    s8 sVar6;
    cXyz local_5c;
    cXyz local_68;
    CcAtInfo local_34;
    CcAtInfo local_50;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        if (i_this->mCurrBckIdx == dRes_INDEX_OQ_BCK_SHIP_HIT_e) {
            if ((i_this->mpMorf->isStop()) && (i_this->mMode != MODE_DOUSA_10) && (i_this->mMode != MODE_DOUSA_11)) {
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_10;
            }
        } else if (i_this->mBodyAtCyl.ChkAtHit()) {
            hitActor = i_this->mBodyAtCyl.GetAtHitAc();
            if (hitActor != NULL) {
                if ((hitActor == (fopAc_ac_c*)dComIfGp_getShipActor() || (hitActor == (fopAc_ac_c*)player)) &&
                    (i_this->mCurrBckIdx != dRes_INDEX_OQ_BCK_SHIP_HIT_e))
                {
                    i_this->m030C = REG8_F(17) + 300.0f;
                    anm_init(i_this, dRes_INDEX_OQ_BCK_SHIP_HIT_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                }
            }
        }
        cLib_addCalc2(&i_this->m030C, REG8_F(12) + 175.0f, 1.0f, 5.0f);
    }
    i_this->mHitType = 0;
    if (i_this->mBodyCoCyl.ChkTgHit()) {
        hitObj = i_this->mBodyCoCyl.GetTgHitObj();
        if (hitObj == NULL) {
            return FALSE;
        }
        local_34.pParticlePos = NULL;
        bVar2 = false;
        switch (hitObj->GetAtType()) {
            case AT_TYPE_GRAPPLING_HOOK:
                if (actor->stealItemLeft > 0) {
                    sVar6 = actor->health;
                    actor->health = 10;
                    local_34.mpObj = i_this->mBodyCoCyl.GetTgHitObj();
                    cc_at_check(actor, &local_34);
                    actor->health = sVar6;
                }
                dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
                bVar2 = true;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x20);
                break;
            case AT_TYPE_SWORD:
                fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x20);
                i_this->mHitType = 0;
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
                    i_this->mHitType = 1;
                }
                break;
            case AT_TYPE_WIND:
                bVar2 = true;
                i_this->mHitType = 3;
                break;
            case AT_TYPE_BOOMERANG:
                i_this->mHitType = 4;
            case AT_TYPE_BOKO_STICK:
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x20);
                break;
            case AT_TYPE_SKULL_HAMMER:
                fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x20);
                i_this->mHitType = 7;
                if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                    i_this->mHitType = 8;
                }
                break;
            case AT_TYPE_BOMB:
                i_this->mHitType = 6;
                break;
            case AT_TYPE_FIRE_ARROW:
            case AT_TYPE_FIRE:
                i_this->mEnemyFire.mFireDuration = 100;
                i_this->mHitType = 5;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x20);
                break;
            case AT_TYPE_ICE_ARROW:
                i_this->mEnemyIce.mFreezeDuration = 200;
                bVar2 = true;
                i_this->mHitType = 5;
                actor->attention_info.flags = 0;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x20);
                break;
            case AT_TYPE_LIGHT_ARROW:
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 1.0f;
                i_this->mEnemyIce.mYOffset = 80.0f;
                actor->attention_info.flags = 0;
            case AT_TYPE_NORMAL_ARROW:
                i_this->mHitType = 5;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x20);
                break;
            default:
                i_this->mHitType = 0;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x20);
        }
        if (!bVar2) {
            local_5c = *i_this->mBodyCoCyl.GetTgHitPosP();
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_5c);
            local_68.setall(2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_5c, &player->shape_angle, &local_68);
            fopAcM_monsSeStart(actor, JA_SE_CV_OQ_DIE, 0);
            local_50.pParticlePos = NULL;
            local_50.mpObj = i_this->mBodyCoCyl.GetTgHitObj();
            cc_at_check(actor, &local_50);
            i_this->mAction = ACTION_ITAI;
            i_this->mMode = MODE_ITAI_30;
        }
        return TRUE;
    }
    return FALSE;
}

/* 00000D8C-00000EC4       .text BG_check__FP8oq_class */
static void BG_check(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u8 var_r3 = 0;

    if (i_this->m02C0 == 0) {
        i_this->mAcchCir.SetWall(REG8_F(10) + 80.0f, REG8_F(0xb) + 100.0f);
        var_r3 = 1;
    }
    if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        i_this->mAcchCir.SetWall(DEMO_SELECT(40.0f, REG8_F(10) + 40.0f), DEMO_SELECT(90.0f, REG8_F(11) + 90.0f));
        var_r3 = false;
    } else if (i_this->m02C0 == 6) {
        i_this->mAcchCir.SetWall(40.0f, 30.0f);
        var_r3 = true;
    }
    if (var_r3 != 0) {
        actor->current.pos.y -= i_this->m0310;
        actor->old.pos.y -= i_this->m0310;
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        actor->current.pos.y += i_this->m0310;
        actor->old.pos.y += i_this->m0310;
    }
}

/* 00000EC4-000011D8       .text Line_check__FP8oq_class4cXyz */
static BOOL Line_check(oq_class* i_this, cXyz destPos) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    cXyz centerPos = actor->current.pos;
    centerPos.y += 40.0f;
    linChk.Set(&centerPos, &destPos, actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 00001610-000016AC       .text shibuki_set__FP8oq_class4cXyzf */
static void shibuki_set(oq_class* i_this, cXyz param_2, f32 param_3) {
    fopAc_ac_c* actor = &i_this->actor;

    if (daSea_ChkArea(actor->current.pos.x, actor->current.pos.z)) {
        param_2.y = daSea_calcWave(actor->current.pos.x, actor->current.pos.z);
    } else if (i_this->mAcch.ChkWaterIn()) {
        param_2.y = i_this->mAcch.m_wtr.GetHeight();
    }
    fopKyM_createWpillar(&param_2, param_3, 1.0f, 0);
}

/* 000016AC-00001930       .text sea_water_check__FP8oq_class */
static BOOL sea_water_check(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    u8 iVar5;
    f32 f0;

    iVar5 = 0;
    i_this->m037C = actor->current.pos;
#if VERSION > VERSION_DEMO
    i_this->m037C.y = i_this->m0340.y;
#endif
    actor->gravity = -3.0f;
    if (daSea_ChkArea(actor->current.pos.x, actor->current.pos.z)) {
        fVar2 = daSea_calcWave(actor->current.pos.x, actor->current.pos.z);
        i_this->m037C.y = fVar2;
        if (actor->current.pos.y < fVar2 + 40.0f) {
            actor->gravity = 0.0f;
            i_this->m02E4 += 0x800;
            f0 = 45.0f + (15.0f * cM_ssin(i_this->m02E4));
            cLib_addCalc2(&actor->current.pos.y, fVar2 - f0, 1.0f, 30.0f);
            iVar5 = 1;
        }
    } else if (i_this->mAcch.ChkWaterIn()) {
        iVar5 = 2;
        fVar2 = i_this->mAcch.m_wtr.GetHeight() + 20.0f;
        i_this->m037C.y = i_this->mAcch.m_wtr.GetHeight();
        actor->gravity = -3.0f;
        if (actor->current.pos.y < fVar2) {
            actor->gravity = 0.0f;
            i_this->m02E4 += 0x800;
            f0 = 45.0f + (15.0f * cM_ssin(i_this->m02E4));
            cLib_addCalc2(&actor->current.pos.y, fVar2 - f0, 1.0f, 30.0f);
            iVar5 = 1;
        }
#if VERSION > VERSION_DEMO
    } else {
        if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
            actor->gravity = 0.0f;
        }
#endif
    }
    if (iVar5 != 0) {
        if ((iVar5 == 1) && (i_this->m02C7 == 0)) {
            if (i_this->m02C0 != 5) {
                cXyz particleScale(1.0f, 1.0f, 1.0f);
                i_this->mRippleCb.remove();
                dComIfGp_particle_setShipTail(dPa_name::ID_AK_JN_HAMON00, &i_this->m037C, NULL, &particleScale, 0xFF, &i_this->mRippleCb);
                i_this->mRippleCb.setRate(0.0f);
            }
            i_this->m02C7 = 1;
            shibuki_set(i_this, actor->current.pos, i_this->m031C);
        }
        return TRUE;
    }
    return FALSE;
}

/* 00001930-0000198C       .text search_y_check__FP8oq_classs */
static void search_y_check(oq_class* i_this, s16 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mTargetAngle, 1, param_2);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, param_2);
}

/* 0000198C-00001B24       .text moguru_check__FP8oq_class */
static BOOL moguru_check(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 var_f31;

    switch (i_this->m02C0) {
        case 0:
            if (i_this->m02C2 == 0) {
                var_f31 = 2000.0f;
            } else {
                var_f31 = 5000.0f;
            }
            if (i_this->mAcch.ChkWallHit()) {
                fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_OQ_DIE, 0);
                i_this->mAction = ACTION_ITAI;
                i_this->mMode = MODE_ITAI_30;
                return TRUE;
            }
            break;
        case 4:
        case 1:
            var_f31 = 5000.0f;
            break;
        case 5:
            var_f31 = (REG12_F(13) + 65.0f);
            var_f31 *= 100.0f;
            break;
    }
    if ((i_this->m02C8 != 0) || (fopAcM_searchPlayerDistance(actor) > var_f31)) {
        i_this->mMode = MODE_DOUSA_10;
        return TRUE;
    }
    return FALSE;
}

/* 00001B24-00002270       .text action_dousa__FP8oq_class */
static void action_dousa(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar3;
    bool bVar4;
    f32 var_f31;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bVar4 = false;
    switch (i_this->mMode) {
        case MODE_DOUSA_0:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m02D6); i++) {
                i_this->m02D6[i] = 0;
            }
            i_this->mTimers[4] = REG8_F(11) + 300.0f;
            i_this->m02C7 = 1;
            i_this->m031C = REG8_F(19) + 2.75f;
            i_this->mMode++;
        case MODE_DOUSA_1:
            switch (i_this->m02C0) {
                case 0:
                    i_this->m031C = 1.0f;
                    i_this->mTimers[4] = REG8_F(11) + 300.0f;
                    if (i_this->m02C2 == 0) {
                        var_f31 = 2000.0f;
                    } else {
                        var_f31 = 5000.0f;
                    }
                    break;
                case 1:
                    var_f31 = 5000.0f;
                    i_this->mTimers[4] = REG8_F(11) + 300.0f;
                    break;
                case 5:
                    var_f31 = REG12_F(11) + 60.0f;
                    var_f31 *= 100.0f;
                    break;
                case 4:
                    bVar4 = true;
                    break;
            }
            if (fopAcM_searchPlayerDistance(actor) < var_f31) {
                bVar4 = true;
                if (i_this->m02C0 == 0) {
                    f32 f31 = 400.0f;
                    if (fopAcM_searchPlayerDistance(actor) < f31) {
                        break;
                    }
                    fVar3 = i_this->mAcch.GetRoofHeight();
                    if ((fVar3 != G_CM3D_F_INF) && (fVar3 < REG8_F(8) + 150.0f)) {
                        break;
                    }
                }
            }
            if ((i_this->mTimers[4] == 0) || (bVar4)) {
                i_this->m02C7 = 0;
                i_this->mBodyCoCyl.OnTgSetBit();
                i_this->mBodyCoCyl.OnCoSetBit();
                fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                anm_init(i_this, dRes_INDEX_OQ_BCK_START_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_seStart(actor, JA_SE_CM_OQ_OUT_WATER, 0);
                i_this->mMode++;
            }
            if (i_this->m02C8 != 0) {
                fopAcM_delete(actor);
            }
            break;
        case MODE_DOUSA_2:
            cLib_addCalc2(&actor->scale.x, i_this->m031C, 1.0f, 0.2f);
            actor->scale.y = actor->scale.z = actor->scale.x;
            if (i_this->mpMorf->isStop()) {
                i_this->mBodyAtCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mBodyAtCyl.OnAtHitBit();
                actor->scale.setall(i_this->m031C);
                if (((i_this->m02C0 == 1) || (i_this->m02C0 == 4)) || (i_this->m02C0 == 5)) {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_UMI_NEW_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                } else {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_NOM_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                }
                i_this->mMode++;
            }
            break;
        case MODE_DOUSA_3:
            if (moguru_check(i_this)) {
                return;
            }
            switch (i_this->m02C0) {
                case 4:
                    if (i_this->mTimers[0] == 0) {
                        i_this->mAction = ACTION_KOUGEKI;
                        i_this->mMode = MODE_KOUGEKI_20;
                    }
                    break;
                case 0:
                    var_f31 = 400.0f;
                    if (fopAcM_searchPlayerDistance(actor) < var_f31) {
                        if (i_this->mAcch.ChkWaterIn()) {
                            i_this->mMode = MODE_DOUSA_10;
                        }
                    } else {
                        fVar3 = 4500.0f;
                        if (i_this->m02C2 == 0) {
                            fVar3 = 1800.0f;
                        }
                        var_f31 = fVar3;
                        if (((i_this->mTimers[0] == 0) && (fopAcM_searchPlayerDistance(actor) < var_f31)) &&
                            (std::fabsf(actor->current.pos.y - player->current.pos.y) < 200.0f))
                        {
                            i_this->mAction = ACTION_KOUGEKI;
                            i_this->mMode = MODE_KOUGEKI_20;
                        }
                    }
                    break;
                case 1:
                    var_f31 = 4500.0f;
                    break;
                case 5:
                    var_f31 = REG12_F(12) + 55.0f;
                    var_f31 *= 100.0f;
                    break;
            }
            if ((i_this->m02C0 == 1) || (i_this->m02C0 == 5)) {
                f32 f30 = 1700.0f;
                if (fopAcM_searchPlayerDistance(actor) < f30) {
                    if ((i_this->mCurrBckIdx != dRes_INDEX_OQ_BCK_IKAKU_e) && (i_this->mCurrBckIdx != dRes_INDEX_OQ_BCK_SHIP_HIT_e)) {
                        anm_init(i_this, dRes_INDEX_OQ_BCK_IKAKU_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    }
                } else if ((i_this->mTimers[0] == 0) && (fopAcM_searchPlayerDistance(actor) < var_f31)) {
                    i_this->mAction = ACTION_KOUGEKI;
                    i_this->mMode = MODE_KOUGEKI_20;
                }
            }
            break;
        case MODE_DOUSA_10:
            i_this->mBodyCoCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyAtCyl.ClrAtSet();
            i_this->mBodyCoCyl.OffTgSetBit();
            i_this->mBodyCoCyl.ClrCoSet();
            i_this->mBodyCoCyl.ClrTgHit();
            i_this->m02C7 = 0;
            actor->attention_info.flags = 0;
            fopAcM_seStart(actor, JA_SE_CM_OQ_IN_WATER, 0);
            anm_init(i_this, dRes_INDEX_OQ_BCK_MOGURU_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mMode++;
        case MODE_DOUSA_11:
            cLib_addCalc2(&i_this->m0320, -(REG8_F(6) + 600.0f), 1.0f, REG8_F(7) + 50.0f);
            if (i_this->m0320 < -((REG8_F(6) + 600.0f) - 1.0f)) {
                actor->scale.setall(0.0f);
                fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
                if ((i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
                    fopAcM_delete(actor);
                } else {
                    i_this->m0320 = 0.0f;
                    i_this->mMode = MODE_DOUSA_0;
                }
            }
    }
    i_this->mTargetAngle = fopAcM_searchPlayerAngleY(actor);
    if (i_this->mMode >= MODE_DOUSA_3) {
        body_atari_check(i_this);
    }
    sea_water_check(i_this);
    search_y_check(i_this, 0x500);
}

/* 00002270-00002BEC       .text action_kougeki__FP8oq_class */
static void action_kougeki(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz sp3C;
#if VERSION == VERSION_DEMO
    cXyz sp48;
    cXyz local_44;
#endif
    cXyz local_50;

    fopAc_ac_c* player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)player_actor;

    switch (i_this->mMode) {
        case MODE_KOUGEKI_20:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m02D6); i++) {
                i_this->m02D6[i] = 0;
            }
            search_y_check(i_this, 0x1000);
            i_this->mMode = MODE_KOUGEKI_22;
            fopAcM_seStart(actor, JA_SE_CM_OQ_JUMP, 0);
            if (i_this->m02C7 != 0) {
                if (actor->current.pos.y > player->current.pos.y + 100.0f) {
                    shibuki_set(i_this, actor->current.pos, 1.5f);
                }
                i_this->m02C7 = 0;
                i_this->mRippleCb.remove();
            }
            if (i_this->m02C2 == 0) {
                if (actor->current.pos.y <= player->current.pos.y + 100.0f) {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_AATTACK1_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    actor->gravity = 0.0f;
                    i_this->m02D6[0] = 1;
                    i_this->mMode = MODE_KOUGEKI_21;
                }
            } else {
                actor->gravity = -3.0f;
                actor->speed.y = 40.0f;
                i_this->m02D6[0] = 1;
            }
            break;
        case MODE_KOUGEKI_21:
            search_y_check(i_this, 0x1000);
            cLib_addCalc2(&actor->current.pos.y, player->current.pos.y + 30.0f, 1.0f, 30.0f);
            if (std::fabsf(actor->current.pos.y - (player->current.pos.y + 30.0f)) > 2.0f) {
                break;
            }
            i_this->mMode++;
        case MODE_KOUGEKI_22:
            anm_init(i_this, dRes_INDEX_OQ_BCK_AATTACK2_FUKU_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mMode++;
            break;
        case MODE_KOUGEKI_23:
            if (i_this->mpMorf->checkFrame(1.0f)) {
                if ((REG8_S(5) == 0) && (i_this->m02C2 == 0)) {
                    u32 r4 = ((i_this->m02C2 << 8) & 0xFF00) | 6;
                    sp3C.setall(0.5f);
                    fopAcM_create(fpcNm_OQ_e, r4, &i_this->m0328, fopAcM_GetRoomNo(actor), &actor->current.angle, &sp3C, 0, NULL);
                    csXyz local_64(actor->current.angle);
                    local_64.y += 0x4000;
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_OQROCKATTACK00, &i_this->m0334, &local_64);
                    fopAcM_seStart(actor, JA_SE_CM_OQ_SPIT_ROCK, 0);
                } else if (REG8_S(5) == 0) {
                    local_50.setall(REG8_F(18) + 2.25f);
                    fopAc_ac_c* pfVar5 = (fopAc_ac_c*)fopAcM_fastCreate(
                        fpcNm_BOMB_e,
                        daBomb_c::prm_make(daBomb_c::STATE_4, true, true),
                        &i_this->m0328,
                        fopAcM_GetRoomNo(actor),
                        &actor->current.angle,
                        &local_50,
                        0xFF,
                        NULL,
                        NULL
                    );
                    Vec pos;
                    pos.x = player->current.pos.x - actor->current.pos.x;
                    pos.y = player->current.pos.y - actor->current.pos.y;
                    pos.z = player->current.pos.z - actor->current.pos.z;
                    s16 iVar7 = -cM_atan2s(pos.y, std::sqrtf(SQUARE(pos.x) + SQUARE(pos.z)));
#if VERSION == VERSION_DEMO
                    s16 var_r26 = actor->current.angle.y;
                    if (!(dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e))) {
                        var_r26 += (s16)cM_rndFX(8000.0f);
                    }
                    mDoMtx_YrotS(*calc_mtx, var_r26);
                    mDoMtx_XrotM(*calc_mtx, iVar7);
                    sp48.x = 0.0f;
                    sp48.y = 0.0f;
                    sp48.z = 60.0f + REG12_F(15);
                    MtxPosition(&sp48, &local_44);
                    if (local_44.y > 0.0f) {
                        local_44.y = -3.0f;
                    }
                    pfVar5->speedF = 40.0f;
                    pfVar5->gravity = local_44.y;
                    pfVar5->speed.y = 40.0f + REG12_F(16);
#else
                    if (!(dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e))) {
                        cM_rndFX(8000.0f);
                    }
                    pfVar5->current.angle.x = iVar7 + cM_rndFX(REG12_F(15) + 3000.0f);
                    pfVar5->speedF = REG12_F(16) + 40.0f;
                    pfVar5->speed.y = cM_rndF(REG12_F(17) + 30.0f) + 70.0f;
#endif
                    fopAcM_seStart(actor, JA_SE_CM_OQ_SPIT_BOMB, 0);
                }
                i_this->mMode++;
            }
            break;
        case MODE_KOUGEKI_24:
            if ((i_this->m02C2 == 0) && (i_this->m02D6[0] != 0)) {
                actor->gravity = -3.0f;
                actor->speed.y = 30.0f;
            }
            i_this->m02C7 = 0;
            i_this->mMode++;
        case MODE_KOUGEKI_25:
            if (i_this->mCurrBckIdx == dRes_INDEX_OQ_BCK_AATTACK2_FUKU_e) {
                if (!i_this->mpMorf->isStop()) {
                    break;
                }
                if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_UMI_NEW_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                } else {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_NOM_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                }
            }
            if (i_this->m02D6[0] != 0) {
                if (sea_water_check(i_this)) {
                    if (i_this->m02C7 != 0) {
                        anm_init(i_this, dRes_INDEX_OQ_BCK_AATTACK3_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                        i_this->mMode = MODE_KOUGEKI_26;
                        fopAcM_seStart(actor, JA_SE_CM_OQ_LANDING, 0);
                    }
                } else if (i_this->mAcch.ChkGroundHit()) {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_AATTACK3_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    i_this->mMode = MODE_KOUGEKI_26;
                }
            } else {
                if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_UMI_NEW_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                } else {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_NOM_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                }
                i_this->mMode = MODE_KOUGEKI_26;
            }
            break;
        case MODE_KOUGEKI_26:
            sea_water_check(i_this);
            if (i_this->m02D6[0] != 0) {
                if (!i_this->mpMorf->isStop()) {
                    break;
                }
            }
            if (i_this->m02C2 == 0) {
                i_this->mTimers[0] = 60;
            } else {
                i_this->mTimers[0] = 100;
            }
            if ((i_this->m02C0 == 1) || (i_this->m02C0 == 5)) {
                i_this->mTimers[0] = 100;
            }
            i_this->mTimers[0] += cM_rndF(i_this->mTimers[0]);
            actor->speed.setall(0.0f);
            if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
                if (i_this->mCurrBckIdx != dRes_INDEX_OQ_BCK_UMI_NEW_WAIT_e) {
                    anm_init(i_this, dRes_INDEX_OQ_BCK_UMI_NEW_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                }
            } else if (i_this->mCurrBckIdx != dRes_INDEX_OQ_BCK_NOM_WAIT_e) {
                anm_init(i_this, dRes_INDEX_OQ_BCK_NOM_WAIT_e, REG8_F(3) + 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = MODE_DOUSA_3;
    }
    if (!(body_atari_check(i_this)) && (i_this->mMode >= MODE_KOUGEKI_26)) {
        f32 f31 = 400.0f;
        if ((i_this->m02C0 == 0) && (fopAcM_searchPlayerDistance(actor) < f31)) {
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = MODE_DOUSA_10;
        }
    }
}

/* 00002BEC-000032A4       .text action_tama_shoot__FP8oq_class */
static void action_tama_shoot(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar9;
    cXyz local_30;
    cXyz local_3c;
    cXyz local_6c;
    cXyz local_54;
    cXyz local_60;

    switch (i_this->mMode) {
        case MODE_TAMA_SHOOT_40:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m02D6); i++) {
                i_this->m02D6[i] = 0;
            }
            fVar9 = cM_rndF(3.99f);
            for (s32 i = 0; i < 1; i++) {
                csXyz* temp_r3 = &roll_dt[(s16)fVar9];
                i_this->m034C = *temp_r3;
            }
            i_this->mTimers[0] = 200;
            i_this->mMode++;
            break;
        case MODE_TAMA_SHOOT_41:
            i_this->mTamaAtCoSph.OnAtVsEnemyBit();
            if (i_this->m02D6[0] == 0) {
                if (i_this->mTamaTgCoSph.ChkAtShieldHit()) {
                    local_30 = *i_this->mTamaTgCoSph.GetAtHitPosP();
                    i_this->mTamaTgCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mTamaTgCoSph.ClrAtSet();
                    i_this->mTimers[0] = 200;
                    i_this->mTamaAtCoSph.OffAtVsPlayerBit();
                    i_this->m02D6[0] = 1;
                    actor->speed.setall(0.0f);
                    actor->speedF *= -1.0f;
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &local_30);
                    fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x40);
                } else if (i_this->mTamaTgCoSph.ChkTgHit()) {
                    cCcD_Obj* hitObj = i_this->mTamaTgCoSph.GetTgHitObj();
                    oq_class* pfVar4 = (oq_class*)i_this->mTamaTgCoSph.GetTgHitAc();
                    if ((hitObj != NULL) && ((hitObj->GetAtType()) == AT_TYPE_SWORD)) {
                        local_3c = *i_this->mTamaTgCoSph.GetTgHitPosP();
                        i_this->mTamaTgCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                        i_this->mTamaTgCoSph.ClrAtSet();
                        i_this->mTimers[0] = 200;
                        fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x40);
                        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &local_3c);
                        i_this->mTamaAtCoSph.OffAtVsPlayerBit();
                        i_this->m02D6[0] = 1;
                        actor->speed.setall(0.0f);
                        actor->speedF *= -1.0f;
                    } else {
                        if ((pfVar4 != NULL) && (fopAcM_GetName(pfVar4) == fopAcM_GetName(actor) && (pfVar4->m02C0 == 6))) {
                            fopAcM_delete(&pfVar4->actor);
                        }
#if VERSION > VERSION_DEMO
                        fopAcM_seStart(actor, JA_SE_OBJ_BREAK_ROCK, 0);
#endif
                        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &actor->current.pos);
                        fopAcM_delete(actor);
                    }
                } else if (i_this->mTamaAtCoSph.ChkAtHit()) {
#if VERSION > VERSION_DEMO
                    fopAcM_seStart(actor, JA_SE_OBJ_BREAK_ROCK, 0);
#endif
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &actor->current.pos);
                    fopAcM_delete(actor);
                }
            }
            if (i_this->mTimers[0] == 0) {
                i_this->mTamaAtCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mTamaAtCoSph.ClrAtSet();
                i_this->mTamaTgCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mTamaTgCoSph.ClrAtSet();
                i_this->mTamaTgCoSph.OffTgSetBit();
                i_this->mTamaTgCoSph.ClrTgHit();
                actor->gravity = -3.0f;
                i_this->mMode++;
            }
            break;
        case MODE_TAMA_SHOOT_42:
            cLib_addCalc0(&actor->scale.x, 1.0f, 0.1f);
            actor->scale.y = actor->scale.z = actor->scale.x;
            if (actor->scale.x < 0.1f) {
                fopAcM_delete(actor);
            }
            break;
    }
    actor->shape_angle += i_this->m034C;
    if (daSea_ChkArea(actor->current.pos.x, actor->current.pos.z)) {
        f32 f1 = daSea_calcWave(actor->current.pos.x, actor->current.pos.z);
        if (actor->current.pos.y < (f1 + 40.0f)) {
            local_6c = actor->current.pos;
            local_6c.y = f1;
            shibuki_set(i_this, local_6c, 0.4f);
            fopAcM_delete(actor);
            return;
        }
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_54.x = 0.0f;
    local_54.y = -40.0f;
    local_54.z = 80.0f;
    MtxPosition(&local_54, &local_60);
    local_60 += actor->current.pos;
    if ((!(i_this->mAcch.ChkGroundHit())) && (!(i_this->mAcch.ChkWallHit()))) {
        if (!Line_check(i_this, local_60)) {
            return;
        }
    }
#if VERSION > VERSION_DEMO
    fopAcM_seStart(actor, JA_SE_OBJ_BREAK_ROCK, 0);
#endif
    dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &actor->current.pos);
    fopAcM_delete(actor);
}

/* 000032A4-0000369C       .text action_itai__FP8oq_class */
static void action_itai(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
#if VERSION > VERSION_DEMO
    JPABaseEmitter* emitter;
#endif

    switch (i_this->mMode) {
        case MODE_ITAI_30:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->m02D6); i++) {
                i_this->m02D6[i] = 0;
            }
            i_this->mBodyAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyAtCyl.ClrAtSet();
            i_this->mBodyCoCyl.OffTgSetBit();
            i_this->mBodyCoCyl.ClrCoSet();
            i_this->mBodyCoCyl.ClrTgHit();
            actor->gravity = 0.0f;
            actor->speed.setall(0.0f);
            i_this->mRippleCb.remove();
            anm_init(i_this, dRes_INDEX_OQ_BCK_DEAD1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mMode++;
            break;
        case MODE_ITAI_31:
            sea_water_check(i_this);
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, dRes_INDEX_OQ_BCK_DEAD2_e, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                fopAcM_seStart(actor, JA_SE_CM_OQ_DIE, 0);
#if VERSION == VERSION_DEMO
                i_this->m037C_demo = dComIfGp_particle_set(dPa_name::ID_AK_JN_OQDEADSPLASH00, &actor->current.pos, NULL, NULL, 0xFF);
#else
                if (i_this->mFollowCb.getEmitter() == NULL) {
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_OQDEADSPLASH00, &actor->current.pos, NULL, NULL, 0xFF, &i_this->mFollowCb);
                }
#endif
                i_this->m034C.y = 5000;
                if ((fopAcM_GetID(i_this) & 1) != 0) {
                    i_this->m034C.y = -5000;
                }
                i_this->mTimers[0] = 10;
                i_this->m02C7 = 0;
                i_this->mMode++;
            }
            break;
        case MODE_ITAI_32:
#if VERSION == VERSION_DEMO
            if (i_this->m037C_demo != NULL) {
                i_this->m037C_demo->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
            }
#else
            emitter = i_this->mFollowCb.getEmitter();
            if (emitter != NULL) {
                emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
            }
#endif
            actor->gravity = 0.5f;
            actor->shape_angle.y += i_this->m034C.y;
            if (i_this->mTimers[0] == 0) {
                anm_init(i_this, dRes_INDEX_OQ_BCK_DEAD3_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mMode++;
            }
            break;
        case MODE_ITAI_33:
#if VERSION == VERSION_DEMO
            if (i_this->m037C_demo != NULL) {
                i_this->m037C_demo->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
            }
#else
            emitter = i_this->mFollowCb.getEmitter();
            if (emitter != NULL) {
                emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0));
            }
#endif
            actor->shape_angle.y += i_this->m034C.y;
            if (i_this->mpMorf->isStop()) {
#if VERSION == VERSION_DEMO
                if (i_this->m037C_demo != NULL) {
                    i_this->m037C_demo->becomeInvalidEmitter();
                }
#else
                i_this->mFollowCb.remove();
#endif
                if (i_this->m02C0 == 5) {
                    oq_class* pfVar5 = (oq_class*)fopAcM_SearchByID(i_this->m0324);
                    if (pfVar5 != NULL) {
                        pfVar5->m02E8++;
                    }
                }
                if ((i_this->m02C0 == 1) || (i_this->m02C0 == 5)) {
                    daComing2::Act_c* coming2 = (daComing2::Act_c*)actor;
                    coming2->pluss_coming_point1();
                }
                fopAcM_createDisappear(actor, &actor->eyePos, 5, daDisItem_IBALL_e);
                fopAcM_delete(actor);
#if VERSION > VERSION_DEMO
                i_this->m02C9 = 1;
#endif
            }
            break;
    }
    cLib_addCalc0(&actor->scale.x, 1.0f, 0.01f);
    actor->scale.y = actor->scale.z = actor->scale.x;
}

/* 0000369C-00003BC4       .text action_wakidasi__FP8oq_class */
static void action_wakidasi(oq_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* pfVar5;
    oq_class* pfVar6;
    fpc_ProcID fVar6;
    cXyz local_58;
    cXyz local_64;
    fpc_ProcID local_4c[7];

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (i_this->m02E8 > REG8_F(0) + 16.0f) {
        fopAcM_delete(actor);
    } else {
        switch (i_this->mMode) {
            case MODE_WAKIDASI_50:
                for (s32 i = 0; i < ARRAY_SIZE(i_this->m02D6); i++) {
                    i_this->m02D6[i] = 0;
                }
                for (s32 i = 0; i < ARRAY_SIZE(i_this->m02EC); i++) {
                    i_this->m02EC[i] = fpcM_ERROR_PROCESS_ID_e;
                }
                fopAcM_OffStatus(actor, fopAcStts_CULL_e);
                i_this->mMode++;
            case MODE_WAKIDASI_51:
                if (fopAcM_searchPlayerDistance(actor) < i_this->m0314) {
                    i_this->m02E6 = 0;
                    i_this->mTimers[0] = 0;
                    i_this->mMode++;
                }
                break;
            case MODE_WAKIDASI_52:
                if ((i_this->mTimers[0] == 0) && (i_this->mTimers[1] == 0)) {
                    if (fopAcM_searchPlayerDistance(actor) > i_this->m0314 + 500.0f) {
                        i_this->mMode = MODE_WAKIDASI_51;
                    } else {
                        if (i_this->m02E6 == 0) {
                            i_this->m02E6 = REG12_F(4) + 2.0f;
                            i_this->m02E6 += (s16)cM_rndF(REG12_F(5) + 1.99f);
                        }
                        for (s32 i = 0, j = 0; i < ARRAY_SIZE(i_this->m02EC); i++) {
                            local_4c[i] = fpcM_ERROR_PROCESS_ID_e;
                            if (i_this->m02EC[i] != -1) {
                                pfVar5 = fopAcM_SearchByID(i_this->m02EC[i]);
                                if (pfVar5 == NULL) {
                                    i_this->m02EC[i] = fpcM_ERROR_PROCESS_ID_e;
                                } else {
                                    local_4c[j] = i_this->m02EC[i];
                                    j++;
                                }
                            }
                        }
                        for (s32 i = 0; i < ARRAY_SIZE(i_this->m02EC); i++) {
                            i_this->m02EC[i] = local_4c[i];
                        }
                        i_this->mMode++;
                    }
                }
                break;
            case MODE_WAKIDASI_53:
                s16 sVar2 = player->shape_angle.y;
                cMtx_YrotS(*calc_mtx, sVar2 + (s16)cM_rndFX(REG12_F(1) + 7000.0f));
                local_58.x = 0.0f;
                local_58.y = 0.0f;
                local_58.z = (REG12_F(2) + 3500.0f) + (cM_rndF(REG12_F(3) + 2500.0f));
                MtxPosition(&local_58, &local_64);
                local_64 += player->current.pos;
                local_64.y -= REG12_F(9) + 100.0f;
                f32 temp_f2 = local_64.x - actor->current.pos.x;
                f32 temp_f0 = local_64.z - actor->current.pos.z;
                if (std::sqrtf(SQUARE(temp_f2) + SQUARE(temp_f0)) > i_this->m0314) {
                    i_this->mTimers[1] = REG8_S(3) + 100;
                    i_this->mMode = MODE_WAKIDASI_52;
                } else {
                    for (s32 i = 0; i < ARRAY_SIZE(i_this->m02EC); i++) {
                        if (i_this->m02EC[i] == -1) {
                            u32 r5 = 0x5;
                            r5 |= 0x100;
                            fVar6 = fopAcM_createChild(fpcNm_OQ_e, fopAcM_GetID(i_this), r5, &local_64, fopAcM_GetRoomNo(actor), &actor->current.angle);
                            if (fVar6 != fpcM_ERROR_PROCESS_ID_e) {
                                i_this->m02EC[i] = fVar6;
                                i_this->m02E6--;
                                if (i_this->m02E6 == 0) {
                                    i_this->mTimers[0] = REG12_F(7) + 90.0f;
                                    i_this->mTimers[0] += (s16)cM_rndF(REG12_F(8) + 50.0f);
                                }
                            }
                            i_this->mTimers[1] = REG8_S(3) + 100;
                            i_this->mMode = MODE_WAKIDASI_52;
                            return;
                        }
                    }
                    pfVar6 = (oq_class*)fopAcM_SearchByID(i_this->m02EC[0]);
                    if (pfVar6 != NULL) {
                        pfVar6->m02C8 = 1;
                    }
                    i_this->mTimers[1] = REG8_S(3) + 100;
                    i_this->mMode = MODE_WAKIDASI_52;
                }
        }
    }
}

/* 00003BC4-00004274       .text daOQ_Execute__FP8oq_class */
static BOOL daOQ_Execute(oq_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar9;
    f32 dVar8;
    cXyz local_44;
    cXyz local_50;

    if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        fopAcM_setGbaName(actor, dItemNo_BOOMERANG_e, 0x41, 0x42);
    }
    if (((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) && (enemy_ice(&i_this->mEnemyIce))) {
        i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpMorf->calc();
        enemy_fire_remove(&i_this->mEnemyFire);
        return TRUE;
    }
    for (s32 i = 0; i < ARRAY_SIZE(i_this->mTimers); i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }
    switch (i_this->mAction) {
        case ACTION_DOUSA:
            action_dousa(i_this);
            break;
        case ACTION_KOUGEKI:
            action_kougeki(i_this);
            break;
        case ACTION_ITAI:
            action_itai(i_this);
            break;
        case ACTION_TAMA_SHOOT:
            action_tama_shoot(i_this);
            break;
        case ACTION_WAKIDASI:
            action_wakidasi(i_this);
            break;
    }
    if ((i_this->m02C0 == 3) || (i_this->m02C0 == 2)) {
        return TRUE;
    }
#if VERSION > VERSION_DEMO
    if (i_this->m02C9 != 0) {
        return TRUE;
    }
#endif
    i_this->mpMorf->play(NULL, 0, 0);
    if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        if (i_this->m02C0 != 0) {
            if (dKy_daynight_check()) {
                i_this->m0318 += 1.0f;
                if (i_this->m0318 > 89.0f) {
                    i_this->m0318 = 0.0f;
                }
            } else {
                cLib_addCalc0(&i_this->m0318, 1.0f, 10.0f);
            }
        } else {
            if (((i_this->mCurrBckIdx == dRes_INDEX_OQ_BCK_NOM_WAIT_e) && (i_this->mAcch.ChkWaterIn())) && (i_this->mpMorf->checkFrame(18.0f))) {
                csXyz local_58(actor->current.angle);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_OQWAITSPLASH00, &actor->current.pos, &local_58);
                local_58.y += 0x8000;
                dComIfGp_particle_set(dPa_name::ID_AK_JN_OQWAITSPLASH00, &actor->current.pos, &local_58);
            }
        }
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    local_44.x = 0.0f;
    local_44.y = 0.0f;
    local_44.z = actor->speedF;
    MtxPosition(&local_44, &local_50);
    actor->speed.x = local_50.x;
    actor->speed.z = local_50.z;
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -100.0f) {
        actor->speed.y = -100.0f;
    }
    if (i_this->mBodyCoCyl.ChkCoSet()) {
        fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
    } else {
        fopAcM_posMove(actor, NULL);
    }
    BG_check(i_this);
    if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        actor->attention_info.position = actor->current.pos;
        actor->attention_info.position.y += 250.0f;
        actor->eyePos = actor->current.pos;
        actor->eyePos.y += 130.0f;
        i_this->mBodyCoCyl.SetC(actor->current.pos);
        if ((i_this->m02C0 == 1) || (i_this->m02C0 == 5)) {
            actor->attention_info.position = actor->current.pos;
            actor->attention_info.position.y += 550.0f;
            actor->eyePos = actor->current.pos;
            actor->eyePos.y += 250.0f;
            dVar9 = (REG8_F(13) + 175.0f);
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                if (fopAcM_searchPlayerDistance(actor) < REG8_F(14) + 250.0f) {
                    if (i_this->m02D6[5] == 0) {
                        i_this->m02D6[5] = 1;
                        i_this->mTimers[5] = REG8_F(15) + 30.0f;
                    }
                } else {
                    i_this->m02D6[5] = 0;
                }
            }
            if (i_this->mTimers[5] != 0) {
                dVar9 = (REG8_F(16) + 250.0f);
            }
            dVar8 = i_this->m030C;
            i_this->mBodyAtCyl.SetC(actor->current.pos);
            i_this->mBodyAtCyl.SetH(600.0f);
            i_this->mBodyAtCyl.SetR(dVar9);
            dComIfG_Ccsp()->Set(&i_this->mBodyAtCyl);
            i_this->mBodyCoCyl.SetH(600.0f);
            i_this->mBodyCoCyl.SetR(dVar8);
            dComIfG_Ccsp()->Set(&i_this->mBodyCoCyl);
        } else {
            i_this->mBodyCoCyl.SetH(170.0f);
            i_this->mBodyCoCyl.SetR(80.0f);
            dComIfG_Ccsp()->Set(&i_this->mBodyCoCyl);
        }
    } else if (i_this->m02C0 == 6) {
        actor->eyePos = actor->current.pos;
        actor->attention_info.position = actor->current.pos;
        if (i_this->m02C2 == 0) {
            i_this->mTamaAtCoSph.SetC(actor->current.pos);
            if (i_this->m02D6[0] == 0) {
                i_this->mTamaAtCoSph.SetR(15.0f);
            } else {
                i_this->mTamaAtCoSph.SetR(40.0f);
            }
            dComIfG_Ccsp()->Set(&i_this->mTamaAtCoSph);
            i_this->mTamaTgCoSph.SetC(actor->current.pos);
            i_this->mTamaTgCoSph.SetR(60.0f);
            dComIfG_Ccsp()->Set(&i_this->mTamaTgCoSph);
        }
    }
    draw_SUB(i_this);
    return TRUE;
}

/* 00004274-0000427C       .text daOQ_IsDelete__FP8oq_class */
static BOOL daOQ_IsDelete(oq_class*) {
    return TRUE;
}

/* 0000427C-00004300       .text daOQ_Delete__FP8oq_class */
static BOOL daOQ_Delete(oq_class* i_this) {
#if VERSION == VERSION_DEMO
    if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        i_this->mRippleCb.remove();
    }
    if (i_this->m037C_demo != NULL) {
        i_this->m037C_demo->becomeInvalidEmitter();
    }
#endif
    dComIfG_resDeleteDemo(&i_this->mPhase, "OQ");
#if VERSION > VERSION_DEMO
    i_this->mRippleCb.remove();
    i_this->mFollowCb.remove();
#endif
    if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        enemy_fire_remove(&i_this->mEnemyFire);
    }
    return TRUE;
}

/* 00004300-000046C0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    oq_class* i_this = (oq_class*)a_this;
    J3DModelData* modelData;
    J3DModel* model;
    J3DAnmTevRegKey* pBrk;

    if (i_this->m02C0 != 6) {
        if (i_this->m02C0 == 0) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("OQ", dRes_INDEX_OQ_BMD_OQ_e);
        } else {
            modelData = (J3DModelData*)dComIfG_getObjectRes("OQ", dRes_INDEX_OQ_BMD_RED_OQ_e);
        }
        i_this->mpMorf = new mDoExt_McaMorf(
            modelData,
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("OQ", dRes_INDEX_OQ_BCK_START_e),
            J3DFrameCtrl::EMode_RESET,
            1.0f,
            0,
            -1,
            1,
            NULL,
            0x00000000,
            0x11020203
        );
        if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
            return FALSE;
        }
        i_this->mpMorf->getModel()->setUserArea((u32)i_this);
        for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
            i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
        if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
            model = i_this->mpMorf->getModel();
            i_this->mpBrkAnm = new mDoExt_brkAnm();
            if (i_this->mpBrkAnm == NULL) {
                return FALSE;
            }
            pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("OQ", dRes_INDEX_OQ_BRK_RED_OQ_e);
            if (!i_this->mpBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE)) {
                return FALSE;
            }
        }
    } else {
        i_this->mpMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("OQ", dRes_INDEX_OQ_BDL_ISI_e),
            NULL,
            NULL,
            NULL,
            J3DFrameCtrl::EMode_RESET,
            0.0f,
            0,
            -1,
            1,
            NULL,
            0x00000000,
            0x11020203
        );
        if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
            return FALSE;
        }
    }
    if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
        if (!i_this->mInvisibleModel.create(i_this->mpMorf->getModel())) {
            return FALSE;
        }
    }
#if VERSION > VERSION_DEMO
    if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
#endif
        static Vec head0_offset[] = {{-25.0f, 0.0f, 0.0f}};
        static Vec head1_offset_tbl[] = {{20.0f, 0.0f, 0.0f}, {60.0f, 0.0f, 0.0f}};
        static Vec head2_offset[] = {{5.0f, 0.0f, 0.0f}};
        static __jnt_hit_data_c search_data[] = {
            {
                /* mShapeType  */ JntHitType_SPH_e,
                /* mJointIndex */ 0x03,
                /* mRadius     */ 50.0f,
                /* mpOffsets   */ head0_offset,
            },
            {
                /* mShapeType  */ JntHitType_CYL_e,
                /* mJointIndex */ 0x04,
                /* mRadius     */ 32.0f,
                /* mpOffsets   */ head1_offset_tbl,
            },
            {
                /* mShapeType  */ JntHitType_SPH_e,
                /* mJointIndex */ 0x06,
                /* mRadius     */ 43.0f,
                /* mpOffsets   */ head2_offset,
            },
        };
        i_this->mpJntHit_c = JntHit_create(i_this->mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
        if (i_this->mpJntHit_c != NULL) {
            fopAcM_SetJntHit(a_this, i_this->mpJntHit_c);
        }
#if VERSION > VERSION_DEMO
        else {
            return FALSE;
        }
    }
#endif
    return TRUE;
}

/* 00004708-00004DBC       .text daOQ_Create__FP10fopAc_ac_c */
static cPhs_State daOQ_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl body_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_METAL,
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
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcCyl body_at_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_STALFOS_MACE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_METAL,
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
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcSph tama_at_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_STALFOS_MACE,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcSph tama_tg_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_STALFOS_MACE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_NoTgHitInfSet_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };

    oq_class* i_this = (oq_class*)a_this;
    csXyz local_70;
    cXyz local_5c;
    cXyz local_68;

    u32 maxHeapSize = 0x3C80;
    i_this->m02C0 = (u8)fopAcM_GetParam(a_this);
    i_this->m02C2 = (u8)(fopAcM_GetParam(a_this) >> 8);
    i_this->m0314 = (fopAcM_GetParam(a_this) >> 0x10) & 0xFF;
    fopAcM_ct(a_this, oq_class);
    if (i_this->m02C0 == 0xFF) {
        i_this->m02C0 = 0;
    }
    if ((i_this->m0314 == 255.0f) || (i_this->m0314 == 0.0f)) {
        i_this->m0314 = 80000.0f;
    } else {
        i_this->m0314 *= 1000.0f;
    }
    if (i_this->m02C0 == 3) {
#if VERSION > VERSION_DEMO
        a_this->group = fopAc_ACTOR_e;
#endif
        i_this->mAction = ACTION_WAKIDASI;
        i_this->mMode = MODE_WAKIDASI_50;
        return cPhs_COMPLEATE_e;
    }
    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "OQ");
    if (res == cPhs_COMPLEATE_e) {
        if (i_this->m02C0 == 0) {
            maxHeapSize = 0x2E00;
        }
        if (i_this->m02C0 == 6) {
            maxHeapSize = 0x9E0;
        }
        if ((i_this->m02C2 == 0xFF) || (1 < i_this->m02C2)) {
            i_this->m02C2 = 0;
        }
        if ((i_this->m02C0 != 3) && (i_this->m02C0 != 2) && (!fopAcM_entrySolidHeap(a_this, useHeapInit, maxHeapSize))) {
            return cPhs_ERROR_e;
        } else if (i_this->m02C0 == 2) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            u32 r28 = 0x04;
            r28 |= 0x100;
            hazure_shoot_timer = 100;
            for (s32 i = 0; i < 1; i++) {
                MtxP mtx = *calc_mtx;
                f32 temp_f31;
                f32 temp_f30;
                f32 temp_f29;
                temp_f29 = 0.0f;
                temp_f30 = 1000.0f;
                temp_f31 = 40.0f;
                cMtx_YrotS(mtx, 0);
                local_5c.x = temp_f29;
                local_5c.y = temp_f29;
                local_5c.z = temp_f30;
                MtxPosition(&local_5c, &local_68);
                local_68 += player->current.pos;
                local_68.y -= temp_f31;
            }
            local_68.x += cM_rndFX(200.0f);
            local_68.z += cM_rndFX(200.0f);
            local_70 = a_this->current.angle;
            local_70.y = cM_atan2s(local_68.x - player->current.pos.x, local_68.z - player->current.pos.z);
            fopAcM_create(fpcNm_OQ_e, r28, &local_68, fopAcM_GetRoomNo(a_this), &local_70, &a_this->scale, 0, NULL);
            return cPhs_ERROR_e;
        }
        a_this->max_health = 1;
        a_this->health = 1;
        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        a_this->attention_info.flags = 0;
#if VERSION > VERSION_DEMO
        i_this->m0340 = a_this->current.pos;
#endif
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mStts.Init(200, 1, a_this);
        i_this->m0310 = 50.0f;
        if (i_this->m02C0 != 6) {
            if ((i_this->m02C0 == 0) || (i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
                a_this->gbaName = 0x1B;
                i_this->mEnemyIce.mpActor = a_this;
                i_this->mEnemyIce.mWallRadius = 170.0f;
                i_this->mEnemyIce.mCylHeight = 80.0f;
                i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
                i_this->mEnemyFire.mpActor = a_this;

                static u8 fire_j[ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs)] = {
                    0x03,
                    0x04,
                    0x05,
                    0x06,
                    0x07,
                    0x08,
                    0x0A,
                    0x0E,
                    0x0F,
                    0x13,
                };
                static f32 fire_sc[ARRAY_SIZE(i_this->mEnemyFire.mParticleScale)] = {
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

                for (int i = 0; i < ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
                    i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
                    i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
                }
            }
            if (i_this->m02C0 == 4) {
                i_this->mStts.SetWeight(0xFE);
                i_this->mTimers[0] = hazure_shoot_timer;
                i_this->mTimers[0] += (s16)cM_rndF(50.0f);
                hazure_shoot_timer += 100;
            }
            if ((i_this->m02C0 == 1) || (i_this->m02C0 == 4) || (i_this->m02C0 == 5)) {
                i_this->m030C = REG8_F(12) + 175.0f;
                i_this->m02C2 = 1;
            }
            if (i_this->m02C0 == 5) {
                i_this->m0324 = fopAcM_GetLinkId(a_this);
                if (i_this->m0324 == fpcM_ERROR_PROCESS_ID_e) {
                    return cPhs_ERROR_e;
                }
                a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
            }
            if (REG8_S(9) != 0) {
                i_this->m02C2 ^= 1;
            }
            a_this->gravity = -3.0f;
            fopAcM_setCullSizeBox(a_this, -250.0f, 0.0f, -80.0f, 250.0f, 200.0f, 80.0f);
            i_this->mBodyCoCyl.Set(body_co_cyl_src);
            i_this->mBodyCoCyl.SetStts(&i_this->mStts);
            i_this->mBodyAtCyl.Set(body_at_cyl_src);
            i_this->mBodyAtCyl.SetStts(&i_this->mStts);
            i_this->mBodyCoCyl.OffTgSetBit();
            i_this->mBodyCoCyl.ClrCoSet();
            i_this->mBodyCoCyl.ClrTgHit();
            i_this->mBodyAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mBodyAtCyl.ClrAtSet();
            if (i_this->m02C0 == 0) {
                i_this->mBodyCoCyl.SetTgGrp(cCcD_TgSPrm_IsEnemy_e);
                a_this->stealItemLeft = 1;
                i_this->mAcch.ClrRoofNone();
                a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Oq", 0);
                a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 3;
            } else {
                a_this->gbaName = 0x41;
                a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Oqw", 0);
                a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x2A;
            }
            a_this->scale.setall(0.0f);
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = MODE_DOUSA_0;
        } else if (i_this->m02C2 == 0) {
            i_this->mTamaAtCoSph.Set(tama_at_co_sph_src);
            i_this->mTamaAtCoSph.SetStts(&i_this->mStts);
            i_this->mTamaTgCoSph.Set(tama_tg_co_sph_src);
            i_this->mTamaTgCoSph.SetStts(&i_this->mStts);
            fopAcM_setCullSizeBox(a_this, -50.0f, -50.0f, -50.0f, 50.0f, 50.0f, 50.0f);
            a_this->speedF = 40.0f;
            i_this->mAction = ACTION_TAMA_SHOOT;
            i_this->mMode = MODE_TAMA_SHOOT_40;
        }
        i_this->mTargetAngle = a_this->current.angle.y;
        if ((i_this->m02C0 != 3) && (i_this->m02C0 != 2)) {
            draw_SUB(i_this);
        }
    }
    return res;
}

static actor_method_class l_daOQ_Method = {
    (process_method_func)daOQ_Create,
    (process_method_func)daOQ_Delete,
    (process_method_func)daOQ_Execute,
    (process_method_func)daOQ_IsDelete,
    (process_method_func)daOQ_Draw,
};

actor_process_profile_definition g_profile_OQ = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_OQ_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(oq_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_OQ_e,
    /* Actor SubMtd */ &l_daOQ_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
