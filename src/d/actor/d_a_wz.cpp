/**
 * d_a_wz.cpp
 * Enemy - Wizzrobe / Mini-Boss - Wizzrobe (Wind Temple)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_wz.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_sea.h"
#include "d/d_s_play.h"
#include "d/d_material.h"
#include "d/d_snap.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_graphic.h"
#include "res/Object/wz.h"
#include "res/Object/wzb.h"

enum Action { ACTION_DOUSA = 0, ACTION_ITAI = 1, ACTION_DEMO = 3, ACTION_TAMA_DOUSA = 100, ACTION_SUMMON_DOUSA = 200 };

enum Mode {
    MODE_DOUSA_0 = 0,
    MODE_DOUSA_1 = 1,
    MODE_DOUSA_2 = 2,
    MODE_DOUSA_3 = 3,
    MODE_DOUSA_4 = 4,
    MODE_DOUSA_5 = 5,
    MODE_DOUSA_6 = 6,
    MODE_DOUSA_7 = 7,
    MODE_DOUSA_8 = 8,
    MODE_ITAI_10 = 10,
    MODE_ITAI_11 = 11,
    MODE_ITAI_12 = 12,
    MODE_ITAI_13 = 13,
    MODE_ITAI_20 = 20,
    MODE_ITAI_21 = 21,
    MODE_ITAI_22 = 22,
    MODE_ITAI_40 = 40,
    MODE_ITAI_41 = 41,
    MODE_ITAI_42 = 42,
    MODE_ITAI_43 = 43,
    MODE_DEMO_50 = 50,
    MODE_DEMO_60 = 60,
    MODE_DEMO_70 = 70,
    MODE_DEMO_80 = 80,
    MODE_DEMO_81 = 81,
    MODE_DEMO_82 = 82,
    MODE_DEMO_83 = 83,
    MODE_DEMO_84 = 84,
    MODE_DEMO_85 = 85,
    MODE_DEMO_86 = 86,
    MODE_DEMO_87 = 87,
    MODE_DEMO_90 = 90,
    MODE_DEMO_91 = 91,
    MODE_DEMO_92 = 92,
    MODE_TAMA_DOUSA_100 = 100,
    MODE_TAMA_DOUSA_101 = 101,
    MODE_TAMA_DOUSA_102 = 102,
    MODE_TAMA_DOUSA_103 = 103,
    MODE_TAMA_DOUSA_104 = 104,
    MODE_SUMMON_DOUSA_200 = 200,
    MODE_SUMMON_DOUSA_201 = 201,
    MODE_SUMMON_DOUSA_202 = 202,
};

enum BehaviorType {
    BEHAVIOR_ATTACK = 0,
    BEHAVIOR_ATTACK_AND_SUMMON = 1,
    BEHAVIOR_MINIBOSS = 2,
    BEHAVIOR_UNKNOWN_3 = 3,
    BEHAVIOR_UNKNOWN_10 = 10,
    BEHAVIOR_UNKNOWN_11 = 11,
    BEHAVIOR_SPAWNER_ORB_1 = 12,
    BEHAVIOR_SPAWNER_ORB_2 = 13
};

static u8 come_flag;

/* 00000078-00000140       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        wz_class* i_this = (wz_class*)model->getUserArea();
        if ((i_this != NULL) && (jntNo == 0x11)) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz offset;
            offset.setall(0.0f);
            MtxPosition(&offset, &i_this->m2FC);
            model->setAnmMtx(jntNo, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000140-00000208       .text rod_nodeCallBack__FP7J3DNodei */
static BOOL rod_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        wz_class* i_this = (wz_class*)model->getUserArea();
        if ((i_this != NULL) && (jntNo == 0x2)) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz offset;
            offset.setall(0.0f);
            MtxPosition(&offset, &i_this->m320);
            model->setAnmMtx(jntNo, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000208-00000360       .text draw_SUB__FP8wz_class */
static void draw_SUB(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();

    model->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::now);
    i_this->mpMorf->calc();
    if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
        if (i_this->mIsMiniBoss) {
            i_this->mpMaskMorf->getModel()->setBaseTRMtx(i_this->mpMorf->getModel()->getAnmMtx(0x13));
            i_this->mpMaskMorf->calc();
        }
        model = i_this->mpWandMorf->getModel();
        model->setBaseScale(i_this->m308);
        i_this->mpWandMorf->getModel()->setBaseTRMtx(i_this->mpMorf->getModel()->getAnmMtx(0x11));
        i_this->mpWandMorf->calc();
        enemy_fire(&i_this->mEnemyFire);
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
}

#if VERSION < VERSION_USA
const GXColor unused_4261[] = {0xFF, 0x00, 0xFF, 0xFF};
#endif

/* 00000360-000006D0       .text hontai_draw__FP8wz_class */
static void hontai_draw(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
#if VERSION < VERSION_USA
    cXyz sp14;
#endif
    cXyz local_38;

    J3DModel* model = i_this->mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    J3DModel* wandModel = i_this->mpWandMorf->getModel();
    if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
        if ((i_this->mEnableSpawnSwitch != 0xFF) && (!dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, dComIfGp_roomControl_getStayNo()))) {
            return;
        }
#if VERSION < VERSION_USA
        dSnap_RegistFig(DSNAP_TYPE_WZ, actor, 1.0f, 1.0f, 1.0f);
#else
        if ((!i_this->mIsMiniBoss) && (i_this->m3EA >= 0x80)) {
            dSnap_RegistFig(DSNAP_TYPE_WZ, actor, 1.0f, 1.0f, 1.0f);
        }
#endif
    }
    g_env_light.setLightTevColorType(model, &actor->tevStr);
    g_env_light.setLightTevColorType(wandModel, &actor->tevStr);
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = i_this->m3EA;
    }
    if (i_this->mIsMiniBoss) {
        wandModel = i_this->mpMaskMorf->getModel();
        modelData = wandModel->getModelData();
        g_env_light.setLightTevColorType(wandModel, &actor->tevStr);
        for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
            modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = i_this->m3EA;
        }
#if VERSION < VERSION_USA
        dSnap_RegistFig(DSNAP_TYPE_WZ_MINIBOSS, actor, 1.0f, 1.0f, 1.0f);
#else
        if (i_this->m3EA >= 0x80) {
            dSnap_RegistFig(DSNAP_TYPE_WZ_MINIBOSS, actor, 1.0f, 1.0f, 1.0f);
        }
#endif
    }
    if (i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, NULL);
        if (i_this->mIsMiniBoss) {
            dMat_control_c::iceEntryDL(i_this->mpMaskMorf, -1, NULL);
        }
    } else {
        i_this->mpBrkAnm->entry(model->getModelData());
        f32 fVar1 = i_this->mBehaviorType + i_this->mIsMiniBoss;
        if (i_this->m351 != false) {
            fVar1 = 3.0f;
        }
        i_this->mpBrkAnm->setFrame(fVar1);
        i_this->mpMorf->entryDL();
#if VERSION < VERSION_USA
        if ((REG8_S(1) != 0) && (i_this->mMode == MODE_DEMO_50)) {
            sp14 = actor->current.pos;
            sp14.y += 20.0f;
        }
#endif
        if (i_this->mIsMiniBoss) {
            i_this->mpMaskMorf->entryDL();
            i_this->mMaskInvisibleModel.entry();
        }
        i_this->mpBrkAnm->remove(model->getModelData());
        i_this->mInvisibleModel.entry();
        if (i_this->m3EA != 0) {
            i_this->mpWandMorf->entryDL();
            local_38.set(actor->current.pos.x, actor->current.pos.y + REG8_F(18), actor->current.pos.z);
            i_this->mShadowId = dComIfGd_setShadow(
                i_this->mShadowId,
                1,
                i_this->mpMorf->getModel(),
                &local_38,
                REG8_F(19) + 700.0f,
                40.0f,
                actor->current.pos.y,
                i_this->mAcch.GetGroundH(),
                i_this->mAcch.m_gnd,
                &actor->tevStr,
                0,
                1.0f,
                dDlst_shadowControl_c::getSimpleTex()
            );
            if (i_this->mShadowId != 0) {
                dComIfGd_addRealShadow(i_this->mShadowId, i_this->mpWandMorf->getModel());
                if (i_this->mIsMiniBoss) {
                    dComIfGd_addRealShadow(i_this->mShadowId, i_this->mpMaskMorf->getModel());
                }
            }
        }
    }
}

/* 000006D0-0000074C       .text summon_door_draw__FP8wz_class */
static void summon_door_draw(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();

    g_env_light.setLightTevColorType(model, &actor->tevStr);
    i_this->mpBtkAnm->entry(model->getModelData());
    i_this->mpMorf->updateDL();
    i_this->mpBtkAnm->remove(model->getModelData());
}

/* 0000074C-00000814       .text damage_ball_draw__FP8wz_class */
static BOOL damage_ball_draw(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->m3F4 != 0) {
        MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
        MtxScale(0.6f, 0.6f, 0.6f, true);
        cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
        MTXCopy(*calc_mtx, i_this->m2CC);
        GXColor color;
        color.r = 0xEB;
        color.g = 0x50;
        color.b = 0x0;
        color.a = 0x0;
        dComIfGd_setAlphaModelColor(color);
        dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_TWO_SPHERES, i_this->m2CC, i_this->m3F4);
    }
}

/* 00000814-000008C0       .text daWZ_Draw__FP8wz_class */
static BOOL daWZ_Draw(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if ((i_this->mBehaviorType == BEHAVIOR_UNKNOWN_10) || (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_11)) {
        if (actor->scale.x) {
            dComIfGd_setSimpleShadow2(
                &actor->current.pos,
                i_this->mAcch.GetGroundH(),
                30.0f,
                i_this->mAcch.m_gnd,
                0,
                1.0f,
                dDlst_shadowControl_c::getSimpleTex()
            );
        }
        if (i_this->m3F4 != 0) {
            damage_ball_draw(i_this);
        }
        return TRUE;
    }
    if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
        hontai_draw(i_this);
    } else {
        summon_door_draw(i_this);
    }
    return TRUE;
}

/* 000008C0-000009EC       .text anm_init__FP8wz_classifUcfi */
static void anm_init(wz_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->m400 = bckFileIdx;
    if (soundFileIdx >= 0) {
        i_this->mpMorf
            ->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("WZ", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("WZ", soundFileIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("WZ", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000009EC-00000A58       .text rod_size_set__FP8wz_classUc */
static void rod_size_set(wz_class* i_this, u8 param_2) {
    f32 fVar1;

    if (param_2 == 0) {
        cLib_addCalc2(&i_this->m308.x, 1.0f, 0.2f, 0.5f);
    } else {
        cLib_addCalc0(&i_this->m308.x, 0.2f, 0.5f);
    }
    fVar1 = i_this->m308.x;
    i_this->m308.z = fVar1;
    i_this->m308.y = fVar1;
}

/* 00000A58-00001258       .text body_atari_check__FP8wz_class */
static BOOL body_atari_check(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_3c;
    cXyz local_48;
    CcAtInfo atInfo;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    i_this->mHitType = 0;
    if (i_this->mBodyCoCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = i_this->mBodyCoCyl.GetTgHitObj();
        if (hitObj == NULL) {
            return FALSE;
        }
        if (i_this->m34F != 0) {
            return FALSE;
        }
        i_this->m34F = 1;
        atInfo.pParticlePos = NULL;
        bool r29 = false;
        switch (hitObj->GetAtType()) {
            case AT_TYPE_GRAPPLING_HOOK:
                if (actor->stealItemLeft > 0) {
                    s8 r29_2 = actor->health;
                    actor->health = 10;
                    atInfo.mpObj = i_this->mBodyCoCyl.GetTgHitObj();
                    cc_at_check(actor, &atInfo);
                    i_this->m353++;
                    actor->health = r29_2;
                }
                dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
                r29 = true;
                i_this->mHitType = 9;
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x44);
                fopAcM_monsSeStart(actor, JA_SE_CV_WZ_NO_DAMAGE, 0);
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
                r29 = true;
                i_this->mHitType = 3;
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x44);
                fopAcM_monsSeStart(actor, JA_SE_CV_WZ_NO_DAMAGE, 0);
                break;
            case AT_TYPE_BOOMERANG:
                r29 = true;
                i_this->mHitType = 4;
                dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
                fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x44);
                fopAcM_monsSeStart(actor, JA_SE_CV_WZ_NO_DAMAGE, 0);
                break;
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
                break;
            case AT_TYPE_ICE_ARROW:
                i_this->mF40.remove();
                i_this->mF54.remove();
                i_this->mF68.remove();
#if VERSION > VERSION_DEMO
                i_this->m308.setall(0.0f);
#endif
                i_this->mEnemyIce.m00C = 2;
                i_this->mEnemyIce.mFreezeDuration = 200;
                actor->attention_info.flags = 0;
                r29 = true;
                break;
            case AT_TYPE_LIGHT_ARROW:
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 1.0f;
                i_this->mEnemyIce.mYOffset = 80.0f;
                actor->attention_info.flags = 0;
                i_this->mBodyCoCyl.OffTgSetBit();
                i_this->mBodyCoCyl.ClrTgHit();
                rod_size_set(i_this, 1);
                i_this->mF40.remove();
                i_this->mF54.remove();
                i_this->mF68.remove();
                break;
            case AT_TYPE_NORMAL_ARROW:
                i_this->mHitType = 5;
            default:
                i_this->mHitType = 0;
                fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x20);
        }
        if (!r29) {
            local_3c = *i_this->mBodyCoCyl.GetTgHitPosP();
            atInfo.mpObj = i_this->mBodyCoCyl.GetTgHitObj();
            cc_at_check(actor, &atInfo);
            if ((i_this->mHitType == 1) || (i_this->mHitType == 7) || (i_this->mHitType == 8) || (actor->health <= 0)) {
                dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_3c);
                local_48.setall(2.0f);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_3c, &player->shape_angle, &local_48);
            } else {
                dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &local_3c, &player->shape_angle);
            }
        }
        i_this->mAction = ACTION_ITAI;
        i_this->mMode = MODE_ITAI_10;
        return TRUE;
    }
    i_this->m34F = 0;
    return FALSE;
}

/* 00001258-000012F0       .text BG_check__FP8wz_class */
static void BG_check(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mAcchCir.SetWall(i_this->m408, i_this->m40C);
    i_this->m404 = 20.0f;
    actor->current.pos.y -= i_this->m404;
    actor->old.pos.y -= i_this->m404;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    actor->current.pos.y += i_this->m404;
    actor->old.pos.y += i_this->m404;
}

// Unused, but exists according to the debug symbol map.
static BOOL Line_check(wz_class* i_this, cXyz destPos) {
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

/* 00001728-00001780       .text fuwafuwa_calc__FP8wz_class */
static void fuwafuwa_calc(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m3E8 += 2000;
    actor->current.pos.y = (i_this->m32C.y + 15.0f) + (cM_ssin(i_this->m3E8) * 5.0f);
}

/* 00001780-00001B38       .text weapon_shoot__FP8wz_classUc */
static void weapon_shoot(wz_class* i_this, u8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    fpc_ProcID actorId;
    s16 sVar9;
    f32 x;
    f32 y;
    f32 z;
    cXyz local_40;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    u32 r30 = -0x100;
    csXyz local_48(actor->shape_angle);
    local_48 = actor->shape_angle;
    fopAcM_monsSeStart(actor, JA_SE_CV_WZ_ATTACK, 0);
    switch (param_2) {
        case 0:
            {
                r30 |= 0xA;
                x = player->current.pos.x - i_this->m320.x;
                y = (player->current.pos.y + 50.0f) - i_this->m320.y;
                z = player->current.pos.z - i_this->m320.z;
                local_48.x = -cM_atan2s(y, std::sqrtf(SQUARE(x) + SQUARE(z)));
                sVar9 = -3000;
                s32 i = 0;
                for (; i < 3; i++, sVar9 += 3000) {
                    local_48.y = sVar9 + cM_atan2s(x, z);
                    fopAcM_create(fpcNm_WZ_e, r30, &i_this->m320, fopAcM_GetRoomNo(actor), &local_48);
                }
                fopAcM_seStart(actor, JA_SE_CM_WZ_ST_FIREBALL, 0);
                break;
            }
        case 1:
            if ((i_this->m439 != 0xFF) && (i_this->mNextPath != NULL)) {
                local_40 = actor->scale;
                r30 |= 0xB;
                x = i_this->m338.x - i_this->m320.x;
                y = (i_this->m338.y + 300.0f) - i_this->m320.y;
                z = i_this->m338.z - i_this->m320.z;
                local_48.x = -cM_atan2s(y, std::sqrtf(SQUARE(x) + SQUARE(z)));
                local_48.y = cM_atan2s(x, z);
                local_40.setall(1.0f);
                fopAcM_seStart(actor, JA_SE_CM_WZ_ST_SUMMONBALL, 0);
                actorId = fopAcM_createChild(fpcNm_WZ_e, fopAcM_GetID(i_this), r30, &i_this->m320, fopAcM_GetRoomNo(actor), &local_48, &local_40, NULL);
                if (actorId != fpcM_ERROR_PROCESS_ID_e) {
                    i_this->m354 = 1;
                }
            }
    }
}

/* 00001B38-00002528       .text action_dousa__FP8wz_class */
static void action_dousa(wz_class* i_this) {
    static GXColor eff_prm_color_dt[] = {{0xFF, 0x47, 0x00, 0xFF}, {0xFF, 0xFF, 0x08, 0xFF}, {0xFF, 0xFF, 0xA0, 0xFF}};
    static GXColor eff_env_color_dt[] = {{0xFF, 0x00, 0x00, 0xFF}, {0x7D, 0x48, 0x38, 0xFF}, {0x4B, 0xBA, 0xFF, 0xFF}};

    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch (i_this->mMode) {
        case MODE_DOUSA_0:
            {
                f32 f31 = 7500.0f;
                if (fopAcM_searchPlayerDistance(actor) > f31) {
                    break;
                }
                for (s32 i = 0; i < 4; i++) {
                    i_this->m3DE[i] = 0;
                }
                if (i_this->mBehaviorType == BEHAVIOR_ATTACK_AND_SUMMON) {
                    cXyz* pointPos = &i_this->mNextPath->m_points[i_this->m358].m_position;
                    i_this->m338 = *pointPos;
                    i_this->m3F8 = 1;
                }
                actor->scale.setall(1.0f);
                fopAcM_seStart(actor, JA_SE_CM_WZ_APPEAR, 0);
                anm_init(i_this, dRes_INDEX_WZ_BCK_SYUTUGEN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                i_this->mMode++;
                // Fall-through
            }
        case MODE_DOUSA_1:
            i_this->m3EA += 8;
            if (i_this->m3EA < 0xFF) {
                break;
            }
            i_this->m3EA = 0xFF;
            i_this->mMode++;
        case MODE_DOUSA_2:
            i_this->m3D4[0] = 0x5a;
            i_this->m3F8 = 0;
            if ((i_this->mBehaviorType == BEHAVIOR_ATTACK_AND_SUMMON) && (i_this->m354 == 0)) {
                i_this->m3F8 = 1;
                i_this->m3E6 = cM_atan2s(i_this->m338.x - actor->current.pos.x, i_this->m338.z - actor->current.pos.z);
            }
            switch (i_this->m3F8) {
                case 0:
                    anm_init(i_this, dRes_INDEX_WZ_BCK_TAME2_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    break;
                case 1:
                    anm_init(i_this, dRes_INDEX_WZ_BCK_TAME1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    break;
            }
            dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZROD00, &i_this->m320, NULL, NULL, 0xFF, &i_this->mF40);
            if (i_this->mF40.getEmitter() != NULL) {
                i_this->mF40.getEmitter()->setGlobalSRTMatrix(i_this->mpWandMorf->getModel()->getAnmMtx(0x2));
            }
            i_this->mBodyCoCyl.OnTgSetBit();
            i_this->mMode++;
            break;
        case MODE_DOUSA_3:
            if (i_this->mF40.getEmitter() != NULL) {
                i_this->mF40.getEmitter()->setGlobalSRTMatrix(i_this->mpWandMorf->getModel()->getAnmMtx(0x2));
            }
            rod_size_set(i_this, 0);
            if (i_this->m3D4[0] == 0) {
                i_this->mMode++;
                i_this->mF40.remove();
            }
            break;
        case MODE_DOUSA_4:
            anm_init(i_this, dRes_INDEX_WZ_BCK_ATTACK1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            if (i_this->mF54.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZCASTMAGIC00, &i_this->m320, NULL, NULL, 0xFF, &i_this->mF54);
            }
            if (i_this->mF54.getEmitter() != NULL) {
                i_this->mF54.getEmitter()
                    ->setGlobalPrmColor(eff_prm_color_dt[i_this->m3F8].r, eff_prm_color_dt[i_this->m3F8].g, eff_prm_color_dt[i_this->m3F8].b);
                i_this->mF54.getEmitter()
                    ->setGlobalEnvColor(eff_env_color_dt[i_this->m3F8].r, eff_env_color_dt[i_this->m3F8].g, eff_env_color_dt[i_this->m3F8].b);
                i_this->mF54.getEmitter()->setGlobalSRTMatrix(i_this->mpWandMorf->getModel()->getAnmMtx(0x2));
            }
            if (i_this->mF68.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZCASTMAGIC01, &i_this->m320, NULL, NULL, 0xFF, &i_this->mF54);
            }
            if (i_this->mF68.getEmitter() != NULL) {
                i_this->mF68.getEmitter()
                    ->setGlobalPrmColor(eff_prm_color_dt[i_this->m3F8].r, eff_prm_color_dt[i_this->m3F8].g, eff_prm_color_dt[i_this->m3F8].b);
                i_this->mF68.getEmitter()
                    ->setGlobalEnvColor(eff_env_color_dt[i_this->m3F8].r, eff_env_color_dt[i_this->m3F8].g, eff_env_color_dt[i_this->m3F8].b);
                i_this->mF68.getEmitter()->setGlobalSRTMatrix(i_this->mpWandMorf->getModel()->getAnmMtx(0x2));
            }
            switch (i_this->m3F8) {
                case 0:
                    fopAcM_seStart(actor, JA_SE_CM_WZ_PRE_FIREBALL, 0);
                    break;
                case 1:
                    fopAcM_seStart(actor, JA_SE_CM_WZ_PRE_SUMMONBALL, 0);
                    break;
            }
            i_this->mMode++;
            break;
        case MODE_DOUSA_5:
            {
                f32 f31 = 38.0f;
                if (i_this->mF54.getEmitter() != NULL) {
                    i_this->mF54.getEmitter()->setGlobalSRTMatrix(i_this->mpWandMorf->getModel()->getAnmMtx(0x2));
                }
                if (i_this->mF68.getEmitter() != NULL) {
                    i_this->mF68.getEmitter()->setGlobalSRTMatrix(i_this->mpWandMorf->getModel()->getAnmMtx(0x2));
                }
                if ((i_this->m3F8 != 1) && (i_this->mpMorf->getFrame() < f31)) {
                    i_this->m3E6 = fopAcM_searchPlayerAngleY(actor);
                }
                if (i_this->mpMorf->checkFrame(35.0f)) {
                    switch (i_this->m3F8) {
                        case 0:
                            weapon_shoot(i_this, 0);
                            break;
                        case 1:
                            if (i_this->m354 == 0) {
                                weapon_shoot(i_this, 1);
                            } else {
                                weapon_shoot(i_this, 0);
                            }
                            break;
                    }
                }
                if (i_this->mpMorf->isStop()) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_WZ_LAUGH, 0);
                    i_this->mMode = MODE_DOUSA_6;
                    i_this->mF54.remove();
                    i_this->mF68.remove();
                }
                break;
            }
        case MODE_DOUSA_6:
#if VERSION > VERSION_DEMO
            actor->speed.setall(0.0f);
            actor->speedF = 0.0f;
            fopAcM_cancelCarryNow(actor);
            actor->attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
            actor->shape_angle.x = 0;
            actor->current.angle.x = 0;
            actor->shape_angle.z = 0;
            actor->current.angle.z = 0;
#endif
            anm_init(i_this, dRes_INDEX_WZ_BCK_SYUTUGEN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
            actor->attention_info.flags = 0;
            i_this->mBodyCoCyl.OffTgSetBit();
            i_this->mBodyCoCyl.ClrTgHit();
            actor->current.angle.y = actor->shape_angle.y;
            i_this->mMode++;
        // Fall-through
        case MODE_DOUSA_7:
            actor->current.angle.y -= (s16)(REG8_S(3) + 0x700);
            i_this->m3E6 = actor->current.angle.y;
            actor->shape_angle.y = i_this->m3E6;
            rod_size_set(i_this, 1);
            i_this->m3EA -= 8;
            if (i_this->m3EA > 0) {
                break;
            }
            if (i_this->m354 != 0) {
                i_this->m3D4[1] = cM_rndF(100.0f) + 100.0f;
            }
            actor->scale.setall(0.0f);
            i_this->m3EA = 0;
            i_this->mMode++;
        // Fall-through
        case MODE_DOUSA_8:
            if (i_this->m3D4[1] == 0) {
                if ((i_this->mPathIndex != 0xFF) && (i_this->mPath != NULL)) {
                    i_this->m358 = cM_rndF(i_this->mPath->m_num);
                    if (i_this->m358 == i_this->mPath->m_num) {
                        i_this->m358--;
                    }
                    cXyz* pointPos = &i_this->mPath->m_points[i_this->m358].m_position;
                    actor->current.pos = *pointPos;
                    actor->old.pos = actor->current.pos;
                    i_this->m32C = actor->current.pos;
                } else {
                    actor->current.pos.x = i_this->m32C.x + cM_rndFX(200.0f);
                    actor->current.pos.y = i_this->m32C.y;
                    actor->current.pos.z = i_this->m32C.z + cM_rndFX(200.0f);
                }
                i_this->m308.setall(0.0f);
                i_this->mMode = MODE_DOUSA_0;
            }
            break;
    }
    if ((i_this->m3F8 != 1) && (i_this->mMode < MODE_DOUSA_4)) {
        i_this->m3E6 = fopAcM_searchPlayerAngleY(actor);
    }
    body_atari_check(i_this);
}

/* 00002528-00002E3C       .text action_itai__FP8wz_class */
static void action_itai(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_18;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    local_18 = actor->current.pos;
#if VERSION == VERSION_DEMO
    local_18.y += REG12_F(17) + 160.0f;
#endif
    switch (i_this->mMode) {
        case MODE_ITAI_10:
            i_this->m3E6 = player->shape_angle.y;
            actor->current.angle.y = i_this->m3E6;
            actor->shape_angle.y = fopAcM_searchPlayerAngleY(actor);
            i_this->mF40.remove();
            i_this->mF54.remove();
            i_this->mF68.remove();
            for (s32 i = 0; i < 4; i++) {
                i_this->m3DE[i] = 0;
            }
            switch (i_this->mHitType) {
                case 7:
                    actor->speedF = 0.0f;
                    i_this->mBodyCoCyl.OffTgSetBit();
                    i_this->mBodyCoCyl.ClrTgHit();
                    i_this->m308.setall(0.0f);
                    actor->attention_info.flags = 0;
                    anm_init(i_this, dRes_INDEX_WZ_BCK_PRESS1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    i_this->mMode = MODE_ITAI_20;
                    break;
                case 1:
                case 8:
                    anm_init(i_this, dRes_INDEX_WZ_BCK_DAMAGE1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    actor->speedF = 48.0f;
                    i_this->mMode = MODE_ITAI_11;
                    break;
                case 3:
                    anm_init(i_this, dRes_INDEX_WZ_BCK_BATABATA1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    actor->speedF = 32.0f;
                    i_this->mMode = MODE_ITAI_12;
                    break;
                case 4:
                    enemy_piyo_set(actor);
                    fopAcM_seStart(actor, JA_SE_CM_MD_PIYO, 0);
                    anm_init(i_this, dRes_INDEX_WZ_BCK_KIZETU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    actor->speedF = 28.0f;
                    i_this->m3D4[0] = 0x4b;
                    i_this->mMode = MODE_ITAI_13;
                    break;
                case 9:
                    anm_init(i_this, dRes_INDEX_WZ_BCK_KIZETU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    actor->speedF = 28.0f;
                    i_this->mMode = MODE_ITAI_12;
                    break;
                default:
                    anm_init(i_this, dRes_INDEX_WZ_BCK_DAMAGE1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    actor->speedF = 32.0f;
                    i_this->mMode = MODE_ITAI_11;
                    break;
            }
            if ((i_this->mHitType != 7) && (actor->health <= 0)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_WZ_DIE, 0);
                i_this->mMode = MODE_ITAI_40;
                if (i_this->mIsMiniBoss) {
                    i_this->mAction = ACTION_DEMO;
                    i_this->mMode = MODE_DEMO_70;
                }
            } else {
                fopAcM_monsSeStart(actor, JA_SE_CV_WZ_DAMAGE, 0);
            }
            break;
        case MODE_ITAI_11:
            cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
            if (std::fabsf(actor->speedF) < 0.2f) {
                actor->speedF = 0.0f;
                i_this->mBodyCoCyl.OffTgSetBit();
                i_this->mBodyCoCyl.ClrTgHit();
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_6;
            }
            break;
        case MODE_ITAI_12:
            cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
            if (i_this->mpMorf->isStop()) {
                actor->speedF = 0.0f;
                i_this->mBodyCoCyl.OffTgSetBit();
                i_this->mBodyCoCyl.ClrTgHit();
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_6;
            }
            break;
        case MODE_ITAI_13:
            cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
            if (i_this->m3D4[0] == 0) {
                i_this->mBodyCoCyl.OffTgSetBit();
                i_this->mBodyCoCyl.ClrTgHit();
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_6;
            }
            break;
        case MODE_ITAI_20:
            if (i_this->mpMorf->isStop()) {
                if (actor->health <= 0) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_WZ_DIE, 0);
                    i_this->mMode = MODE_ITAI_42;
                    if (i_this->mIsMiniBoss) {
                        i_this->mAction = ACTION_DEMO;
                        i_this->mMode = MODE_DEMO_70;
                    }
                } else {
                    anm_init(i_this, dRes_INDEX_WZ_BCK_PRESS2_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    i_this->mMode = MODE_ITAI_21;
                }
            }
            break;
        case MODE_ITAI_21:
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, dRes_INDEX_WZ_BCK_PRESS3_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mMode = MODE_ITAI_22;
            }
            break;
        case MODE_ITAI_22:
            i_this->m3EA -= 8;
            if (i_this->m3EA < 0) {
                i_this->m3EA = 0;
            }
            if (i_this->mpMorf->isStop()) {
                i_this->m3EA = 0;
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_6;
            }
            break;
        case MODE_ITAI_40:
            i_this->m3E6 = player->shape_angle.y;
            actor->current.angle.y = i_this->m3E6;
            actor->shape_angle.y = fopAcM_searchPlayerAngleY(actor);
            actor->speedF = 40.0f;
#if VERSION == VERSION_DEMO
            if ((REG12_F(13) + (100.0f + i_this->mAcch.GetGroundH())) > actor->current.pos.y) {
                anm_init(i_this, dRes_INDEX_WZ_BCK_DOWN1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            } else {
                anm_init(i_this, dRes_INDEX_WZ_BCK_AIRDOWN1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
#else
            anm_init(i_this, dRes_INDEX_WZ_BCK_AIRDOWN1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
#endif
            i_this->mMode++;
        case MODE_ITAI_41:
            rod_size_set(i_this, 1);
            cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
            if (!i_this->mpMorf->isStop()) {
                break;
            }
            actor->speedF = 0.0f;
            i_this->mMode++;
            // Fall-through
        case MODE_ITAI_42:
            if (i_this->m354 == 0) {
#if VERSION == VERSION_DEMO
                fopAcM_createDisappear(actor, &local_18, 5, daDisItem_IBALL_e, actor->stealItemBitNo);
#else
                if (i_this->m400 == 5) {
                    local_18.y += 160.0f;
                    fopAcM_createDisappear(actor, &local_18, 5, daDisItem_IBALL_e, actor->stealItemBitNo);
                } else {
                    local_18.y += 20.0f;
                    fopAcM_createDisappear(actor, &local_18, 5, daDisItem_IBALL_e, actor->stealItemBitNo);
                }
#endif
                fopAcM_delete(actor);
#if VERSION == VERSION_DEMO
                if (REG12_S(2) == 0) {
                    if (i_this->mDisableSpawnOnDeathSwitch != 0xFF) {
                        dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
                    }
                    if (!strcmp(dComIfGp_getStartStageName(), "kazeMB")) {
                        come_flag++;
                        if (come_flag >= 2) {
                            mDoAud_subBgmStop();
                        }
                    }
                    fopAcM_onActor(actor);
                }
#else
                if (strcmp(dComIfGp_getStartStageName(), "kazeMB")) {
                    if (i_this->mDisableSpawnOnDeathSwitch != 0xFF) {
                        dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
                    }
                    fopAcM_onActor(actor);
                }
#endif
            } else {
                actor->speedF = 0.0f;
                i_this->m3EA = 0;
#if VERSION == VERSION_DEMO
                fopAcM_createDisappear(actor, &local_18, 5, daDisItem_IBALL_e, actor->stealItemBitNo);
#else
                if (i_this->m400 == 5) {
                    local_18.y += 160.0f;
                    fopAcM_createDisappear(actor, &local_18, 5, daDisItem_IBALL_e, actor->stealItemBitNo);
                } else {
                    local_18.y += 20.0f;
                    fopAcM_createDisappear(actor, &local_18, 5, daDisItem_IBALL_e, actor->stealItemBitNo);
                }
#endif
                actor->attention_info.flags = 0;
                fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
                actor->scale.setall(0.0f);
                i_this->m308.setall(0.0f);
                i_this->mBodyCoCyl.OffTgSetBit();
                i_this->mBodyCoCyl.ClrTgHit();
                i_this->mMode++;
            }
            break;
        case MODE_ITAI_43:
            if (i_this->m354 == 0) {
                fopAcM_delete(actor);
#if VERSION == VERSION_DEMO
                if (REG12_S(2) == 0) {
                    if (i_this->mDisableSpawnOnDeathSwitch != 0xFF) {
                        dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
                    }
                    if (!strcmp(dComIfGp_getStartStageName(), "kazeMB")) {
                        come_flag++;
                        if (come_flag >= 2) {
                            mDoAud_subBgmStop();
                        }
                    }
                    fopAcM_onActor(actor);
                }
#else
                if (strcmp(dComIfGp_getStartStageName(), "kazeMB")) {
                    if (i_this->mDisableSpawnOnDeathSwitch != 0xFF) {
                        dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
                    }
                    fopAcM_onActor(actor);
                }
#endif
            }
            break;
    }
    if (actor->health > 0) {
        body_atari_check(i_this);
    }
}

/* 00002E3C-000047C8       .text action_demo__FP8wz_class */
static void action_demo(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* pfVar4;
    fpc_ProcID actorId;
    f32 f3;
    cXyz local_70;
    cXyz local_7c;
    cXyz local_88;
    cXyz local_94;
    cXyz local_a0;

    fopAc_ac_c* const player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    local_94 = actor->current.pos;
    local_94.y += REG12_F(17) + 160.0f;
    switch (i_this->mMode) {
        case MODE_DEMO_50:
            if (fopAcM_searchPlayerDistance(actor) > (REG11_F(1) + 1250.0f)) {
                break;
            }
            actor->eyePos = player_actor->current.pos;
            fopAcM_seStart(actor, JA_SE_CM_WZ_APPEAR, 0);
            i_this->m3E6 = fopAcM_searchPlayerAngleY(actor);
            actor->current.angle.y = i_this->m3E6;
            actor->shape_angle.y = i_this->m3E6;
            mDoAud_bgmAllMute(30);
            actor->current.pos.setall(0.0f);
            i_this->m32C = actor->current.pos;
            i_this->mMode = MODE_DEMO_70;
            break;
        case MODE_DEMO_60:
            switch (i_this->m3DE[0]) {
                case 0:
                    if (come_flag) {
                        anm_init(i_this, dRes_INDEX_WZ_BCK_SYUTUGEN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                        actor->current.pos.x = -250.0f;
                        actor->current.pos.y = 20.0f;
                        actor->current.pos.z = 100.0f;
                        i_this->m3E6 = fopAcM_searchPlayerAngleY(actor);
                        actor->current.angle.y = i_this->m3E6;
                        actor->shape_angle.y = i_this->m3E6;
                        come_flag = false;
                        i_this->m3DE[0]++;
                    }
                    break;
                case 1:
                    i_this->m3EA += 8;
                    if (i_this->m3EA > 0xFF) {
                        i_this->m3EA = 0xFF;
                        i_this->m3DE[0]++;
                    }
                    break;
                case 2:
                    if (come_flag) {
                        come_flag = false;
                        fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
                        i_this->mAction = ACTION_DOUSA;
                        i_this->mMode = MODE_DOUSA_6;
                    }
                    break;
            }
            break;
        case MODE_DEMO_70:
            fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
            if (!actor->eventInfo.checkCommandDemoAccrpt()) {
                dComIfGp_event_onEventFlag(1);
                fopAcM_orderPotentialEvent(actor, 0, 0xFFFF, 0);
                actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
                break;
            }
            player->changeOriginalDemo();
            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);
            i_this->m464 = 50.0f;
            if (actor->health <= 0) {
                actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
                actor->shape_angle.y = fopAcM_searchPlayerAngleY(actor);
                for (s32 i = 0; i < 20; i++) {
                    if (i_this->m3AC[i] != 0) {
                        pfVar4 = fopAcM_SearchByID(i_this->m35C[i]);
                        if ((pfVar4 != NULL) && (!fopAcM_CheckStatus(pfVar4, fopAcStts_UNK4000_e))) {
                            fopAcM_OffStatus(pfVar4, fopAcStts_UNK4000_e);
                            i_this->m3C0[i] = 1;
                        }
                    }
                }
                player->setPlayerPosAndAngle(&player_actor->current.pos, fopAcM_searchPlayerAngleY(actor) + 0x8000);
                if (i_this->m400 != 0xD) {
                    anm_init(i_this, DEMO_SELECT(dRes_INDEX_WZ_BCK_DOWN1_e, dRes_INDEX_WZ_BCK_AIRDOWN1_e), 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    actor->speedF = 40.0f;
                    i_this->mMode = MODE_DEMO_90;
                } else {
                    i_this->mMode = MODE_DEMO_91;
                }
            } else {
                player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
                i_this->m3D4[0] = REG11_F(2) + 45.0f;
                actor->current.pos.setall(0.0f);
                i_this->mMode = MODE_DEMO_80;
            }
            break;
        case MODE_DEMO_80:
            if (i_this->m3D4[0] != 0) {
                break;
            }
            cLib_addCalc2(&i_this->m464, REG11_F(3) + 50.0f, 1.0f, REG12_F(14) + 0.5f);
            local_88.x = 50.0f;
            local_88.y = 0.0f;
            local_88.z = 850.0f;
            player->setPlayerPosAndAngle(&player_actor->current.pos, fopAcM_searchPlayerAngleY(actor) + 0x8000);
            i_this->m43C.x = REG11_F(4);
            i_this->m43C.y = REG11_F(5) + 125.0f;
            i_this->m43C.z = REG11_F(6) + -29.0f;
            i_this->m448.x = REG11_F(7) + 1470.0f;
            i_this->m448.y = REG11_F(8) + 917.0f;
            i_this->m448.z = REG11_F(9) + -222.0f;
            i_this->m3D4[0] = (REG11_F(10) + 20.0f);
            anm_init(i_this, dRes_INDEX_WZ_BCK_S_DEMO_WAIT1_e, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mMode++;
        case MODE_DEMO_81:
            if (REG0_S(8) != 0) {
                i_this->m43C.x = REG11_F(4);
                i_this->m43C.y = REG11_F(5) + 125.0f;
                i_this->m43C.z = REG11_F(6) + -29.0f;
                i_this->m448.x = REG11_F(7) + 1470.0f;
                i_this->m448.y = REG11_F(8) + 917.0f;
                i_this->m448.z = REG11_F(9) + -222.0f;
                i_this->m3D4[0] = (REG11_F(10) + 20.0f);
                break;
            }
            if (i_this->m3D4[0] == 0) {
                switch (i_this->m3DE[0]) {
                    case 0:
                        player->changeDemoMode(daPy_demo_c::DEMO_L_AROUND2_e);
                        i_this->m3D4[0] = (REG11_F(11) + 60.0f);
                        cMtx_YrotS(*calc_mtx, player_actor->shape_angle.y);
                        local_70.x = 0.0f;
                        local_70.y = 0.0f;
                        local_70.z = REG11_F(12) + 40000.0f;
                        MtxPosition(&local_70, &local_7c);
                        actor->eyePos = local_7c + player_actor->current.pos;
                        fopAcM_seStart(actor, JA_SE_CM_WZ_APPEAR, 0);
                        i_this->m3DE[0]++;
                        break;
                    case 1:
                        player->changeDemoMode(daPy_demo_c::DEMO_TBACK_e);
                        i_this->m3D4[0] = (REG11_F(13) + 45.0f);
                        cMtx_YrotS(*calc_mtx, player_actor->shape_angle.y + 0x8000);
                        local_70.x = 0.0f;
                        local_70.y = 0.0f;
                        local_70.z = REG11_F(14) + 40000.0f;
                        MtxPosition(&local_70, &local_7c);
                        actor->eyePos = local_7c + player_actor->current.pos;
                        fopAcM_seStart(actor, JA_SE_CM_WZ_APPEAR, 0);
                        i_this->m3DE[0]++;
                }
            }
            cLib_addCalc2(&i_this->m464, REG11_F(15) + 50.0f, 1.0f, REG12_F(14) + 0.5f);
            f3 = std::fabsf(i_this->m43C.x - (REG11_F(16) + 150.0f));
            f3 *= (REG11_F(19) + 0.01f);
            cLib_addCalc2(&i_this->m43C.x, REG11_F(16) + 150.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m43C.y - (REG11_F(17) + 158.0f));
            f3 *= (REG11_F(19) + 0.01f);
            cLib_addCalc2(&i_this->m43C.y, REG11_F(17) + 158.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m43C.z - (REG11_F(18) + 114.0f));
            f3 *= (REG11_F(19) + 0.01f);
            cLib_addCalc2(&i_this->m43C.z, REG11_F(18) + 114.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m448.x - (int)(REG11_S(0) + 0x492));
            f3 *= (REG11_F(19) + 0.01f);
            cLib_addCalc2(&i_this->m448.x, (int)(REG11_S(0) + 0x492), 1.0f, f3);
            f3 = std::fabsf(i_this->m448.y - (int)(REG11_S(1) + 0x2CD));
            f3 *= (REG11_F(19) + 0.01f);
            cLib_addCalc2(&i_this->m448.y, (int)(REG11_S(1) + 0x2CD), 1.0f, f3);
            f3 = std::fabsf(i_this->m448.z - (int)(REG11_S(2) - 0x336));
            f3 *= (REG11_F(19) + 0.01f);
            cLib_addCalc2(&i_this->m448.z, (int)(REG11_S(2) - 0x336), 1.0f, f3);
            if (i_this->m3DE[0] >= 2) {
                if (i_this->m3D4[0] <= (s16)(REG11_S(3) + 0x14)) {
                    if (i_this->m3DE[0] == 2) {
                        fopAcM_seStart(actor, JA_SE_CM_WZ_APPEAR, 0);
                        i_this->m3DE[0] = 3;
                    }
                    i_this->m3EA += (s16)(REG11_S(4) + 10);
                    if (i_this->m3EA > 0xFF) {
                        i_this->m3EA = 0xFF;
                    }
                }
                if ((REG0_S(9) == 0) && (i_this->m3D4[0] == 0)) {
                    player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
                    i_this->m3D4[0] = REG11_S(5) + 0x1E;
                    i_this->mMode++;
                }
            }
            break;
        case MODE_DEMO_82:
            i_this->m3EA += (s16)(REG11_S(6) + 5);
            if (i_this->m3EA > 0xFF) {
                i_this->m3EA = 0xFF;
            }
            if (i_this->m3D4[0] == 0) {
                i_this->mMode++;
            }
            break;
        case MODE_DEMO_83:
            i_this->m32C = actor->current.pos;
            i_this->m32C.y += 15.0f;
            anm_init(i_this, dRes_INDEX_WZ_BCK_S_DEMO1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mMode++;
        case MODE_DEMO_84:
            i_this->m3E6 = fopAcM_searchPlayerAngleY(actor);
            actor->current.angle.y = i_this->m3E6;
            actor->shape_angle.y = i_this->m3E6;
            local_7c.x = 50.0f;
            local_7c.y = 0.0f;
            local_7c.z = 850.0f;
            player->setPlayerPosAndAngle(&local_7c, fopAcM_searchActorAngleY(player_actor, actor));
            cLib_addCalc2(&i_this->m464, REG8_F(1) + 50.0f, 1.0f, REG12_F(14) + 0.5f);
            i_this->m43C.x = REG8_F(2) + -108.0f;
            i_this->m43C.y = REG8_F(3) + 174.0f;
            i_this->m43C.z = REG8_F(4) + 231.0f;
            i_this->m448.x = REG8_F(5) + 199.0f;
            i_this->m448.y = REG8_F(6) + 50.0f;
            i_this->m448.z = REG8_F(7) + 1092.0f;
            i_this->m3EA += (int)(REG8_F(8) + 5.0f);
            if (i_this->m3EA < 0xFF) {
                break;
            }
            i_this->m3EA = 0xFF;
            if (REG0_S(9) != 0) {
                i_this->mpMorf->setPlaySpeed(0.0f);
                break;
            }
            i_this->m3D4[0] = REG12_F(12);
            i_this->mpMorf->setPlaySpeed(1.0f);
            i_this->mMode++;
            // Fall-through
        case MODE_DEMO_85:
            if (i_this->m3D4[0] != 0) {
                break;
            }
            i_this->mpMorf->setPlaySpeed(1.0f);
            i_this->mMode++;
        case MODE_DEMO_86:
            cLib_addCalc2(&i_this->m464, REG8_F(10) + 45.0f, 1.0f, REG12_F(15) + 0.2f);
            f3 = std::fabsf(i_this->m43C.x - REG8_F(11));
            f3 *= (REG8_F(17) + 0.025f);
            cLib_addCalc2(&i_this->m43C.x, REG8_F(11), 1.0f, f3);
            f3 = std::fabsf(i_this->m43C.y - (REG8_F(12) + 135.0f));
            f3 *= (REG8_F(17) + 0.025f);
            cLib_addCalc2(&i_this->m43C.y, REG8_F(12) + 135.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m43C.z - (REG8_F(13) + -60.0f));
            f3 *= (REG8_F(17) + 0.025f);
            cLib_addCalc2(&i_this->m43C.z, REG8_F(13) + -60.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m448.x - (REG8_F(14) + 50.0f));
            f3 *= (REG8_F(17) + 0.025f);
            cLib_addCalc2(&i_this->m448.x, REG8_F(14) + 50.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m448.y - (REG8_F(15) + 110.0f));
            f3 *= (REG8_F(17) + 0.025f);
            cLib_addCalc2(&i_this->m448.y, REG8_F(15) + 110.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m448.z - (REG8_F(16) + 330.0f));
            f3 *= (REG8_F(17) + 0.025f);
            cLib_addCalc2(&i_this->m448.z, REG8_F(16) + 330.0f, 1.0f, f3);
            if (i_this->mpMorf->checkFrame(159.0f)) {
                if (REG0_S(9) != 0) {
                    i_this->mpMorf->setPlaySpeed(0.0f);
                } else {
                    actor->speedF = -(REG12_F(10) + 10.0f);
                    i_this->m3DE[0] = 0;
                    i_this->m3DE[1] = 0;
                    i_this->m3D4[0] = 2;
                    i_this->mMode++;
                }
            }
            break;
        case MODE_DEMO_87:
            cLib_addCalc0(&actor->speedF, 1.0f, REG12_F(11) + 0.3f);
            if (REG8_S(4) != 0) {
                i_this->m3D4[0] = 1;
                REG8_S(4) = 0;
            }
            if ((i_this->m3DE[0] == 0) && (i_this->m3D4[0] == 0)) {
                local_a0 = actor->scale;
                u32 r23 = -0x100;
                r23 |= 0xD;
                local_a0.x = 4.0f;
                local_a0.y = 4.0f;
                local_a0.z = 4.0f;
                local_88.x = 215.0f;
                local_88.y = 180.0f;
                local_88.z = 100.0f;
                actorId =
                    fopAcM_createChild(fpcNm_WZ_e, fopAcM_GetID(i_this), r23, &local_88, fopAcM_GetRoomNo(actor), &actor->current.angle, &local_a0, 0, NULL);
                if (actorId == fpcM_ERROR_PROCESS_ID_e) {
                    break;
                }
                local_88.x = -250.0f;
                local_88.y = 180.0f;
                local_88.z = 100.0f;
                actorId =
                    fopAcM_createChild(fpcNm_WZ_e, fopAcM_GetID(i_this), r23, &local_88, fopAcM_GetRoomNo(actor), &actor->current.angle, &local_a0, 0, NULL);
                if (actorId == fpcM_ERROR_PROCESS_ID_e) {
                    break;
                }
                i_this->m3DE[0] = 1;
                i_this->m3D4[1] = 0x28;
                i_this->m3D4[2] = (REG12_F(9) + 70.0f);
            }
            if (i_this->m3D4[2] == 1) {
                mDoAud_subBgmStart(JA_BGM_MBOSS);
            }
            if ((i_this->m3DE[0] != 0) && (i_this->m3DE[1] == 0) && (i_this->m3D4[1] == 0)) {
                local_88.x = 215.0f;
                local_88.y = 0.0f;
                local_88.z = 100.0f;
                i_this->m344 = fopAcM_create(fpcNm_TN_e, 0xFFFFFF2C, &local_88, fopAcM_GetRoomNo(actor), &actor->current.angle, NULL, 0xFF, NULL);
                if (i_this->m344 != fpcM_ERROR_PROCESS_ID_e) {
                    i_this->m3DE[1] = 1;
                    come_flag = true;
                }
            }
            if (i_this->m344 != fpcM_ERROR_PROCESS_ID_e) {
                pfVar4 = fopAcM_SearchByID(i_this->m344);
                if (pfVar4 != NULL) {
                    pfVar4->speedF = 0.0f;
                    fopAcM_OnStatus(pfVar4, fopAcStts_UNK4000_e);
                }
            }
            cLib_addCalc2(&i_this->m464, REG12_F(0) + 65.0f, 1.0f, REG12_F(16) + 2.5f);
            f3 = std::fabsf(i_this->m43C.x - REG12_F(1));
            f3 *= (REG12_F(7) + 0.3f);
            cLib_addCalc2(&i_this->m43C.x, REG12_F(1), 1.0f, f3);
            f3 = std::fabsf(i_this->m43C.y - (REG12_F(2) + 90.0f));
            f3 *= (REG12_F(7) + 0.3f);
            cLib_addCalc2(&i_this->m43C.y, REG12_F(2) + 90.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m43C.z - (REG12_F(3) + 440.0f));
            f3 *= (REG12_F(7) + 0.3f);
            cLib_addCalc2(&i_this->m43C.z, REG12_F(3) + 440.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m448.x - REG12_F(4));
            f3 *= (REG12_F(7) + 0.3f);
            cLib_addCalc2(&i_this->m448.x, REG12_F(4), 1.0f, f3);
            f3 = std::fabsf(i_this->m448.y - (REG12_F(5) + 50.0f));
            f3 *= (REG12_F(7) + 0.3f);
            cLib_addCalc2(&i_this->m448.y, REG12_F(5) + 50.0f, 1.0f, f3);
            f3 = std::fabsf(i_this->m448.z - (REG12_F(6) + 570.0f));
            f3 *= (REG12_F(7) + 0.3f);
            cLib_addCalc2(&i_this->m448.z, REG12_F(6) + 570.0f, 1.0f, f3);
            if (((i_this->mpMorf->isStop()) || (i_this->mpMorf->checkFrame(REG12_F(8) + 274.0f))) && (REG0_S(9) == 0)) {
                dComIfGp_getVibration().StopQuake(0x20);
                camera->mCamera.Reset(i_this->m43C, i_this->m448);
                camera->mCamera.Start();
                camera->mCamera.SetTrimSize(0);
                player->cancelOriginalDemo();
                dComIfGp_event_reset();
                fopAcM_monsSeStart(actor, JA_SE_CV_WZ_LAUGH, 0);
                pfVar4 = fopAcM_SearchByID(i_this->m344);
                if (pfVar4 != NULL) {
                    fopAcM_OffStatus(pfVar4, fopAcStts_UNK4000_e);
                }
                if (REG12_S(9) == 0) {
                    i_this->m354 = 1;
                    i_this->m352 = 1;
                } else {
                    i_this->m344 = fpcM_ERROR_PROCESS_ID_e;
                }
                come_flag = true;
                fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_6;
            }
            break;
        case MODE_DEMO_90:
            rod_size_set(i_this, 1);
            player->setPlayerPosAndAngle(&player_actor->current.pos, fopAcM_searchPlayerAngleY(actor) + 0x8000);
            cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
            if (!i_this->mpMorf->isStop()) {
                break;
            }
            actor->speedF = 0.0f;
            i_this->mMode++;
        case MODE_DEMO_91:
            if (REG12_S(4) != 0) {
                break;
            }
            for (s32 i = 0; i < 20; i++) {
                if (i_this->m3C0[i] != 0) {
                    pfVar4 = fopAcM_SearchByID(i_this->m35C[i]);
                    if (pfVar4 != NULL) {
                        fopAcM_OnStatus(pfVar4, fopAcStts_UNK4000_e);
                    }
                    i_this->m3C0[i] = 0;
                }
            }
            fopAcM_createDisappear(actor, &local_94, 5, daDisItem_IBALL_e, actor->stealItemBitNo);
            actor->speedF = 0.0f;
            i_this->m3EA = 0;
            actor->attention_info.flags = 0;
            fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
            actor->scale.setall(0.0f);
            i_this->m308.setall(0.0f);
            i_this->mBodyCoCyl.OffTgSetBit();
            i_this->mBodyCoCyl.ClrTgHit();
            i_this->m3D4[0] = REG12_S(3) + 0x1e;
            i_this->mMode++;
            // Fall-through
        case MODE_DEMO_92:
            if (i_this->m3D4[0] == 0) {
                dComIfGp_getVibration().StopQuake(0x20);
                camera->mCamera.Reset(i_this->m43C, i_this->m448);
                camera->mCamera.Start();
                camera->mCamera.SetTrimSize(0);
                player->cancelOriginalDemo();
                dComIfGp_event_reset();
#if VERSION == VERSION_DEMO
                if (i_this->m354 == 0) {
                    fopAcM_delete(actor);
                    if (REG12_S(2) == 0) {
                        if (i_this->mDisableSpawnOnDeathSwitch != 0xFF) {
                            dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
                        }
                        if (!strcmp(dComIfGp_getStartStageName(), "kazeMB")) {
                            come_flag++;
                            if (come_flag >= 2) {
                                mDoAud_subBgmStop();
                            }
                        }
                        fopAcM_onActor(actor);
                    }
                } else {
                    i_this->mAction = ACTION_ITAI;
                    i_this->mMode = MODE_ITAI_43;
                }
#else
                if ((!strcmp(dComIfGp_getStartStageName(), "kazeMB")) && (i_this->mIsMiniBoss)) {
                    mDoAud_subBgmStop();
                }
                if (i_this->m354 == 0) {
                    fopAcM_delete(actor);
                    if (strcmp(dComIfGp_getStartStageName(), "kazeMB")) {
                        if (i_this->mDisableSpawnOnDeathSwitch != 0xFF) {
                            dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
                        }
                        fopAcM_onActor(actor);
                    }
                } else {
                    i_this->mAction = ACTION_ITAI;
                    i_this->mMode = MODE_ITAI_43;
                }
#endif
            }
            break;
    }
    if (actor->health <= 0) {
        i_this->m43C = actor->current.pos;
        i_this->m43C.y += 50.0f;
        cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor));
        local_70.x = 0.0f;
        local_70.y = 0.0f;
        local_70.z = 400.0f;
        MtxPosition(&local_70, &local_7c);
        local_7c += actor->current.pos;
        i_this->m448.x = local_7c.x - 100.0f;
        i_this->m448.y = local_7c.y + 400.0f;
        i_this->m448.z = local_7c.z - 300.0f;
    }
    if ((i_this->m400 == 0x11) && (i_this->mpMorf->checkFrame(70.0f))) {
        fopAcM_monsSeStart(actor, JA_SE_CV_WZ_LAUGH, 0);
    }
    if (((actor->health > 0) && (i_this->mMode >= MODE_DEMO_81)) || ((actor->health <= 0) && (i_this->mMode >= MODE_DEMO_90))) {
        camera->mCamera.Set(i_this->m43C, i_this->m448, i_this->m464, 0);
    }
}

/* 000047C8-00004810       .text next_tama_move__FP8wz_class4cXyz */
static void next_tama_move(wz_class* i_this, cXyz param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m314 = param_2;
    actor->speedF = 0.0f;
    i_this->mBallCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
    i_this->mBallCoSph.ClrAtSet();
    i_this->mMode = MODE_TAMA_DOUSA_104;
}

/* 00004810-00004BF4       .text summon_call_sub__FP8wz_class */
static void summon_call_sub(wz_class* i_this) {
    /* Nonmatching */
    static s16 enemy_name_dt[] = {
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_MT_e,  // Magtail
        0x7FFF,      // Unused
        fpcNm_MT_e,  // Magtail
        fpcNm_KI_e,  // Keese
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        fpcNm_KI_e,  // Keese
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        fpcNm_BL_e,  // Bubble
        fpcNm_PW_e,  // Poe
        fpcNm_BL_e,  // Bubble
        fpcNm_ST_e,  // Stalfos
        0x7FFF,      // Unused
        fpcNm_RD_e,  // ReDead
        0x7FFF,      // Unused
        fpcNm_ST_e,  // Stalfos
        0x7FFF,      // Unused
        fpcNm_RD_e,  // ReDead
        0x7FFF,      // Unused
        fpcNm_MO2_e, // Moblin
        0x7FFF,      // Unused
        fpcNm_TN_e,  // Darknut
        0x7FFF,      // Unused
        fpcNm_MO2_e, // Moblin
        0x7FFF,      // Unused
        fpcNm_TN_e,  // Darknut
        0x7FFF,      // Unused
        fpcNm_PH_e,  // Peahat
        0x7FFF,      // Unused
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_PH_e,  // Peahat
        0x7FFF,      // Unused
        fpcNm_BB_e,  // Kargaroc
        0x7FFF,      // Unused
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_MT_e,  // Magtail
        0x7FFF,      // Unused
        fpcNm_MT_e,  // Magtail
        fpcNm_KI_e,  // Keese
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        0x7FFF,      // Unused
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_BL_e,  // Bubble
        fpcNm_KI_e,  // Keese
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_KS_e,  // Morth
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        0x7FFF,      // Unused
        fpcNm_BK_e,  // Bokoblin
        0x7FFF,      // Unused
        fpcNm_BK_e,  // Bokoblin
        fpcNm_MO2_e, // Moblin
        fpcNm_BK_e,  // Bokoblin
        fpcNm_BK_e,  // Bokoblin
        fpcNm_BK_e,  // Bokoblin
        fpcNm_MO2_e, // Moblin
        fpcNm_BB_e,  // Kargaroc
        0x7FFF,      // Unused
        fpcNm_KI_e,  // Keese
        0x7FFF,      // Unused
        fpcNm_CC_e,  // ChuChu
        fpcNm_CC_e,  // ChuChu
        fpcNm_KI_e,  // Keese
        fpcNm_KS_e   // Morth
    };
    static u32 enemy_arg_dt[] = {
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Magtail
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Magtail
        0xFFFFFF03,                          // Keese
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF00, 0x0100FF00), // Bubble
        0x00000000,                          // Unused
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF00, 0x0100FF00), // Bubble
        0xFFFFFF03,                          // Keese
        DEMO_SELECT(0x0000FF01, 0x0100FF01), // Bubble
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF01, 0x0100FF01), // Bubble
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF01, 0x0100FF01), // Bubble
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF01, 0x0100FF01), // Bubble
        0x00000000,                          // Unused
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF00, 0x0100FF00), // Bubble
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF00, 0x0100FF00), // Bubble
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF01, 0x0100FF01), // Bubble
        DEMO_SELECT(0x0000FF00, 0x0100FF00), // Bubble
        0xFF000000,                          // Poe
        DEMO_SELECT(0x0000FF01, 0x0100FF01), // Bubble
        0xFFFFFF00,                          // Stalfos
        0x00000000,                          // Unused
        0xFFFFFFFE,                          // ReDead
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Stalfos
        0x00000000,                          // Unused
        0xFFFFFFFE,                          // ReDead
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Moblin
        0x00000000,                          // Unused
        0xFFFFFF20,                          // Darknut
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Moblin
        0x00000000,                          // Unused
        0xFFFFFF20,                          // Darknut
        0x00000000,                          // Unused
        0xFFF0F000,                          // Peahat
        0x00000000,                          // Unused
        0xFFFF0003,                          // Keese
        0x00000000,                          // Unused
        0xFFF0F000,                          // Peahat
        0x00000000,                          // Unused
        0xFFFFFF03,                          // Kargaroc
        0x00000000,                          // Unused
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Magtail
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Magtail
        0xFFFFFF03,                          // Keese
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF00, 0x0100FF00), // Bubble
        0x00000000,                          // Unused
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        DEMO_SELECT(0x0000FF00, 0x0100FF00), // Bubble
        0xFFFFFF03,                          // Keese
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0x00000003,                          // Morth
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        0xFFFF0000,                          // ChuChu
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Bokoblin
        0x00000000,                          // Unused
        0xFFFFFF00,                          // Bokoblin
        0xFFFFFF00,                          // Moblin
        0xFFFFFF00,                          // Bokoblin
        0xFFFFFF20,                          // Bokoblin
        0xFFFFFF00,                          // Bokoblin
        0xFFFFFF00,                          // Moblin
        0xFFFFFF03,                          // Kargaroc
        0x00000000,                          // Unused
        0xFFFFFF03,                          // Keese
        0x00000000,                          // Unused
        0xFFFF0A00,                          // ChuChu
        0xFFFF0B00,                          // ChuChu
        0xFFFF0003,                          // Keese
        0x00000003                           // Morth
    };
    static int birth_dt[] = {
        0x00000008, // Keese
        0x00000000, // Unused
        0x00000002, // Magtail
        0x00000000, // Unused
        0x00000001, // Magtail
        0x00000003, // Keese
        0x00000006, // Keese
        0x00000000, // Unused
        0x00000008, // Keese
        0x00000000, // Unused
        0x00000002, // Bubble
        0x00000000, // Unused
        0x00000006, // Keese
        0x00000000, // Unused
        0x00000001, // Bubble
        0x00000003, // Keese
        0x00000002, // Bubble
        0x00000000, // Unused
        0x00000001, // Bubble
        0x00000000, // Unused
        0x00000001, // Bubble
        0x00000000, // Unused
        0x00000001, // Bubble
        0x00000000, // Unused
        0x00000014, // Morth
        0x00000000, // Unused
        0x0000000F, // Morth
        0x00000000, // Unused
        0x0000000F, // Morth
        0x00000000, // Unused
        0x00000014, // Morth
        0x00000000, // Unused
        0x00000008, // ChuChu
        0x00000000, // Unused
        0x0000000A, // ChuChu
        0x00000000, // Unused
        0x00000008, // ChuChu
        0x00000000, // Unused
        0x00000008, // ChuChu
        0x00000000, // Unused
        0x00000002, // Bubble
        0x00000000, // Unused
        0x00000002, // Bubble
        0x00000000, // Unused
        0x00000001, // Bubble
        0x00000001, // Bubble
        0x00000001, // Poe
        0x00000002, // Bubble
        0x00000001, // Stalfos
        0x00000000, // Unused
        0x00000001, // ReDead
        0x00000000, // Unused
        0x00000001, // Stalfos
        0x00000000, // Unused
        0x00000001, // ReDead
        0x00000000, // Unused
        0x00000001, // Moblin
        0x00000000, // Unused
        0x00000001, // Darknut
        0x00000000, // Unused
        0x00000001, // Moblin
        0x00000000, // Unused
        0x00000001, // Darknut
        0x00000000, // Unused
        0x00000002, // Peahat
        0x00000000, // Unused
        0x00000006, // Keese
        0x00000000, // Unused
        0x00000003, // Peahat
        0x00000000, // Unused
        0x00000002, // Kargaroc
        0x00000000, // Unused
        0x00000004, // Keese
        0x00000000, // Unused
        0x00000001, // Magtail
        0x00000000, // Unused
        0x00000001, // Magtail
        0x00000002, // Keese
        0x00000003, // Keese
        0x00000000, // Unused
        0x00000004, // Keese
        0x00000000, // Unused
        0x00000001, // Bubble
        0x00000000, // Unused
        0x00000003, // Keese
        0x00000000, // Unused
        0x00000001, // Bubble
        0x00000002, // Keese
        0x0000000A, // Morth
        0x00000000, // Unused
        0x00000008, // Morth
        0x00000000, // Unused
        0x00000008, // Morth
        0x00000000, // Unused
        0x0000000A, // Morth
        0x00000000, // Unused
        0x00000004, // ChuChu
        0x00000000, // Unused
        0x00000005, // ChuChu
        0x00000000, // Unused
        0x00000004, // ChuChu
        0x00000000, // Unused
        0x00000004, // ChuChu
        0x00000000, // Unused
        0x00000001, // Bokoblin
        0x00000000, // Unused
        0x00000001, // Bokoblin
        0x00000001, // Moblin
        0x00000001, // Bokoblin
        0x00000001, // Bokoblin
        0x00000001, // Bokoblin
        0x00000001, // Moblin
        0x00000002, // Kargaroc
        0x00000000, // Unused
        0x00000004, // Keese
        0x00000000, // Unused
        0x00000002, // ChuChu
        0x00000002, // ChuChu
        0x00000004, // Keese
        0x00000008  // Morth
    };
    static u32 cc_birth_dt[] = {0x00000000, 0x00000001, 0x00000004, 0x00000003};

    fopAc_ac_c* actor = &i_this->actor;
    wz_class* r25;
    int r20;
    u32 r19_r25;
    int i;
    int j;
    int r30;
    int r17;

    csXyz local_64;
    cXyz local_5c;

    local_5c = actor->current.pos;
    fopAc_ac_c* r3 = fopAcM_SearchByID(i_this->m344);
    if (r3 == NULL) {
        return;
    }
    if (i_this->m3D4[0] != 1) {
        return;
    }
    r25 = (wz_class*)r3;

    r30 = r25->m3EC * 8;
    r30 += r25->m3F0 * 2;
    r17 = birth_dt[r30];
    local_64.setall(0);
    local_64.y = fopAcM_searchPlayerAngleY(actor);
    local_5c = actor->current.pos;
    if (r30 == 0xc0) {
        local_64.x = 0x80;
    }
    r19_r25 = 0;
    for (i = 0, j = 0; i < 20 && j < r17; i++) {
        if (i_this->m35C[i] == fpcM_ERROR_PROCESS_ID_e) {
            r19_r25 = enemy_arg_dt[r30];
            if ((enemy_name_dt[r30] == fpcNm_CC_e) && ((r19_r25 & 0xA00) == 0)) {
                r19_r25 |= (cc_birth_dt[(int)cM_rndF(2.99f)] + 10) * 0x100;
            }
            i_this->m35C[i] = fopAcM_create(enemy_name_dt[r30], r19_r25, &local_5c, fopAcM_GetRoomNo(actor), &local_64);
            if (i_this->m35C[i] != fpcM_ERROR_PROCESS_ID_e) {
                j++;
                i_this->m3AC[i] = 1;
                local_5c = actor->current.pos;
                local_5c.x += cM_rndFX(100.0f);
                local_5c.y += cM_rndFX(100.0f);
                local_5c.z += cM_rndFX(100.0f);
            }
        }
    }
    r25->m3F0++;
    r25->m3F0 &= 3;
    if ((r25->m3EC == 7) || (r25->m3EC == 0xD)) {
        r25->m3F6++;
        if (r25->m3F6 > 7) {
            r25->m3EC = 10;
        }
    }
    r30++;
    if (enemy_name_dt[r30] != 0x7FFF) {
        r20 = birth_dt[r30];
        local_64.setall(0);
        local_64.y = fopAcM_searchPlayerAngleY(actor);
        local_5c = actor->current.pos;
        for (i = 0, j = 0; i < 20 && j < r20; i++) {
            if (i_this->m35C[i] == fpcM_ERROR_PROCESS_ID_e) {
                r19_r25 = enemy_arg_dt[r30];
                if (r30 == DEMO_SELECT(0xD0, 0xCF)) {
                    r19_r25 |= 0xA00;
                    r19_r25 |= (cc_birth_dt[(int)cM_rndF(3.19f)] << 8);
                }
                i_this->m35C[i] = fopAcM_create(enemy_name_dt[r30], r19_r25, &local_5c, fopAcM_GetRoomNo(actor), &local_64);
                if (i_this->m35C[i] != fpcM_ERROR_PROCESS_ID_e) {
                    j++;
                    i_this->m3AC[i] = 1;
                    local_5c = actor->current.pos;
                    local_5c.x += cM_rndFX(100.0f);
                    local_5c.y += cM_rndFX(100.0f);
                    local_5c.z += cM_rndFX(100.0f);
                }
            }
        }
    }
}

/* 00004BF4-00004D18       .text sea_water_check__FP8wz_class */
static s32 sea_water_check(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    bool bVar1;
    f32 fVar3;
    cXyz local_18;

    bVar1 = false;
    i_this->mF04 = actor->current.pos;
    if (daSea_ChkArea(actor->current.pos.x, actor->current.pos.z)) {
        fVar3 = daSea_calcWave(actor->current.pos.x, actor->current.pos.z);
        if (actor->current.pos.y < fVar3 + 50.0f) {
            bVar1 = true;
        }
    } else if (i_this->mAcch.ChkWaterIn()) {
        fVar3 = i_this->mAcch.m_wtr.GetHeight();
        if (actor->current.pos.y < fVar3 + 50.0f)
            bVar1 = true;
    }
    if (bVar1) {
        local_18.setall(2.0f);
        dComIfGp_particle_set(dPa_name::ID_AK_JN_EVAPORATION00, &actor->current.pos, &actor->current.angle, &local_18);
        return TRUE;
    }
    return FALSE;
}

/* 00004D18-00005760       .text action_tama_dousa__FP8wz_class */
static void action_tama_dousa(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    wz_class* pfVar6;
    fpc_ProcID actorId;
    cXyz local_38;
    cXyz local_44;

    csXyz local_7c(actor->current.angle);
    local_38 = actor->scale;
    u32 r29 = -0x100;
    switch (i_this->mMode) {
        case MODE_TAMA_DOUSA_100:
            for (s32 i = 0; i < 4; i++) {
                i_this->m3DE[i] = 0;
            }
            i_this->m410 = 25.0f;
            i_this->mF04 = actor->current.pos;
            i_this->mF10 = actor->shape_angle;
            switch (i_this->mBehaviorType) {
                case BEHAVIOR_UNKNOWN_10:
                    if (i_this->mF18.getEmitter() == NULL) {
                        dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZFIRE00, &i_this->mF04, &i_this->mF10, NULL, 0xFF, &i_this->mF18);
                    }
                    if (i_this->mF2C.getEmitter() == NULL) {
                        dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZFIRE01, &i_this->mF04, &i_this->mF10, NULL, 0xFF, &i_this->mF2C);
                    }
                    break;
                case BEHAVIOR_UNKNOWN_11:
                    if (i_this->mF18.getEmitter() == NULL) {
                        dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZSUMMONSHOT00, &i_this->mF04, &i_this->mF10, NULL, 0xFF, &i_this->mF18);
                    }
                    if (i_this->mF2C.getEmitter() == NULL) {
                        dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZSUMMONSHOT01, &i_this->mF04, &i_this->mF10, NULL, 0xFF, &i_this->mF2C);
                    }
                    break;
            }
            actor->speedF = 45.0f;
            i_this->mMode++;
            // Fall-through
        case MODE_TAMA_DOUSA_101:
            if (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_11) {
                fopAcM_seStart(actor, JA_SE_OBJ_WZ_SUMMON_B_FLY, 0);
                Vec pos;
                pos.x = i_this->m338.x - actor->current.pos.x;
                pos.y = (i_this->m338.y + 300.0f) - actor->current.pos.y;
                pos.z = i_this->m338.z - actor->current.pos.z;
                if (std::sqrtf(SQUARE(pos.x) + SQUARE(pos.y) + SQUARE(pos.z)) < 50.0f) {
                    actor->speedF = 0.0f;
                    i_this->mMode = MODE_TAMA_DOUSA_102;
                    break;
                }
            } else {
                fopAcM_seStart(actor, JA_SE_OBJ_WZ_FIRE_B_FLY, 0);
                if (sea_water_check(i_this)) {
                    i_this->mF18.remove();
                    i_this->mF2C.remove();
                    fopAcM_delete(actor);
                }
            }
            if (i_this->mAcch.ChkGroundHit()) {
                if ((i_this->mBehaviorType != BEHAVIOR_UNKNOWN_11) && (!dComIfG_Bgsp()->ChkMoveBG(i_this->mAcch.m_gnd))) {
                    i_this->m410 = 40.0f;
                    actor->speedF = 0.0f;
                    i_this->mMode = MODE_TAMA_DOUSA_102;
                } else {
                    next_tama_move(i_this, actor->current.pos);
                }
            } else if ((i_this->m3D4[2] == 0) || (i_this->mAcch.ChkWallHit())) {
                next_tama_move(i_this, actor->current.pos);
            } else if ((i_this->mBallCoSph.ChkAtShieldHit()) || (i_this->mBallCoSph.ChkAtHit())) {
                local_44 = *i_this->mBallCoSph.GetAtHitPosP();
                next_tama_move(i_this, local_44);
            } else {
                if (i_this->mBallCoSph.ChkTgHit()) {
                    local_44 = *i_this->mBallCoSph.GetTgHitPosP();
                    next_tama_move(i_this, local_44);
                }
            }
            break;
        case MODE_TAMA_DOUSA_102:
            local_44 = actor->current.pos;
            local_44.y = i_this->mAcch.GetGroundH();
            local_7c.x = 0;
            local_7c.z = 0;
            switch (i_this->mBehaviorType) {
                case BEHAVIOR_UNKNOWN_10:
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZFLOORFIRE01, &local_44, &local_7c);
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZFLOORFIRE02, &local_44, &local_7c);
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZHITFIRE00, &local_44, &actor->current.angle);
                    if (i_this->m3D4[1] == 0) {
                        i_this->m3D4[1] = cM_rndF(5.0f);
                        i_this->m3F4 = cM_rndF(5.0f) + 8.0f;
                    }
#if VERSION == VERSION_DEMO
                    dKy_arrowcol_chg_on(0, 0);
#else
                    if (strcmp(dComIfGp_getStartStageName(), "sea")) {
                        dKy_arrowcol_chg_on(0, 0);
                    }
#endif
                    fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
                    i_this->m3D4[0] = 0x50;
                    fopAcM_seStart(actor, JA_SE_OBJ_WZ_FIRE_B_IMP, 0);
                    break;
                case BEHAVIOR_UNKNOWN_11:
                    r29 |= 0xC;
                    local_38.setall(5.0f);
                    local_44 = actor->current.pos;
                    for (s32 i = 0; i < 10; i++) {
                        actorId = fopAcM_createChild(
                            fpcNm_WZ_e,
                            fopAcM_GetID(i_this),
                            r29,
                            &local_44,
                            fopAcM_GetRoomNo(actor),
                            &actor->current.angle,
                            &local_38,
                            NULL,
                            NULL
                        );
                        if (actorId != fpcM_ERROR_PROCESS_ID_e) {
                            break;
                        }
                    }
                    if (actorId == fpcM_ERROR_PROCESS_ID_e) {
                        pfVar6 = (wz_class*)fopAcM_SearchByID(i_this->m344);
                        if (pfVar6 != NULL) {
                            pfVar6->m354 = 0;
                        }
                    }
                    i_this->mBallCoSph.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mBallCoSph.ClrAtSet();
                    i_this->mBallCoSph.OffTgSetBit();
                    i_this->mBallCoSph.ClrTgHit();
                    actor->scale.setall(0.0f);
                    i_this->m3D4[0] = REG0_S(0) + 30;
                    break;
            }
            i_this->mF18.remove();
            i_this->mF2C.remove();
            i_this->mMode++;
            break;
        case MODE_TAMA_DOUSA_103:
            if (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_10) {
                actor->shape_angle.y = actor->shape_angle.y + 0x100;
                if (i_this->m3D4[0] > 0xA) {
                    if (i_this->m3D4[1] == 0) {
                        i_this->m3D4[1] = cM_rndF(5.0f);
                        i_this->m3F4 = cM_rndF(5.0f) + 8.0f;
                    }
                } else if (i_this->m3F4 > 0) {
                    i_this->m3F4--;
                }
            }
            if (i_this->m3D4[0] == 0) {
                fopAcM_delete(actor);
            } else if (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_10) {
                fopAcM_seStart(actor, JA_SE_OBJ_BAR_FRAME_BURN, 0);
            }
            break;
        case MODE_TAMA_DOUSA_104:
            switch (i_this->mBehaviorType) {
                case BEHAVIOR_UNKNOWN_10:
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZHITFIRE00, &i_this->m314, &actor->current.angle);
                    break;
                case BEHAVIOR_UNKNOWN_11:
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZHITSUMMON00, &i_this->m314, &actor->current.angle);
                    pfVar6 = (wz_class*)fopAcM_SearchByID(i_this->m344);
                    if (pfVar6 != NULL) {
                        pfVar6->m354 = 0;
                    }
                    break;
            }
            i_this->mF18.remove();
            i_this->mF2C.remove();
            fopAcM_delete(actor);
            break;
    }
}

/* 00005760-00005B64       .text action_summon_dousa__FP8wz_class */
static void action_summon_dousa(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;
    fopAc_ac_c* pfVar8;
    wz_class* pfVar9;
    u8 cVar10;
    fpc_ProcID local_38;

    cVar10 = 0;
    switch (i_this->mMode) {
        case MODE_SUMMON_DOUSA_200:
            {
                for (s32 i = 0; i < 4; i++) {
                    i_this->m3DE[i] = 0;
                }
                for (s32 i = 0; i < 5; i++) {
                    emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZSUMMONWIND00, &actor->current.pos);
                    JGeometry::TVec3<f32> scale;
                    scale.set(actor->scale.x, actor->scale.y, actor->scale.z);
                    if (emitter != NULL) {
                        emitter->setGlobalScale(scale);
                    }
                }
                fopAcM_seStart(actor, JA_SE_OBJ_WZ_SUMMON_B_SMN, 0);
                emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_WIZSUMMONSMOKE00, &actor->current.pos);
                JGeometry::TVec3<f32> scale;
                scale.set(actor->scale.x, actor->scale.y, actor->scale.z);
                if (emitter != NULL) {
                    emitter->setGlobalScale(scale);
                }
                i_this->m3D4[0] = 0x28;
                for (s32 i = 0; i < 20; i++) {
                    i_this->m35C[i] = fpcM_ERROR_PROCESS_ID_e;
                    i_this->m3AC[i] = 0;
                }
                i_this->mMode++;
                break;
            }
        case MODE_SUMMON_DOUSA_201:
            if (i_this->mBehaviorType == BEHAVIOR_SPAWNER_ORB_1) {
                summon_call_sub(i_this);
            }
            if (i_this->mpBtkAnm->isStop()) {
                i_this->mMode++;
                if (i_this->mBehaviorType == BEHAVIOR_SPAWNER_ORB_2) {
                    fopAcM_delete(actor);
                }
            }
            break;
        case MODE_SUMMON_DOUSA_202:
            for (s32 i = 0; i < 20; i++) {
                if (i_this->m3AC[i] != 0) {
                    pfVar8 = fopAcM_SearchByID(i_this->m35C[i]);
#if VERSION <= VERSION_JPN
                    if (pfVar8 == NULL)
#else
                    s16 bVar5 = false;
                    if ((pfVar8 != NULL) && (strcmp(dComIfGp_getStartStageName(), "kazeMB") == 0)) {
                        f32 fVar2 = pfVar8->current.pos.x;
                        f32 fVar3 = pfVar8->current.pos.z;
                        fVar2 = std::sqrtf(SQUARE(fVar2) + SQUARE(fVar3));
                        if ((fVar2 > 1800.0f) || (pfVar8->current.pos.y < -200.0f) || (pfVar8->current.pos.y > 2100.0f)) {
                            bVar5 = true;
                        }
                    }
                    if ((pfVar8 == NULL) || (bVar5))
#endif
                    {
                        i_this->m3AC[i] = 0;
                        i_this->m35C[i] = fpcM_ERROR_PROCESS_ID_e;
                    }
                } else {
                    cVar10++;
                }
            }
            if (cVar10 == 20) {
                local_38 = i_this->m344;
                pfVar9 = (wz_class*)fopAcM_SearchByID(local_38);
                if (pfVar9 != NULL) {
                    pfVar9->m354 = 0;
                }
                fopAcM_delete(actor);
            }
            break;
    }
    i_this->mpMorf->play(NULL, 0, 0);
    i_this->mpBtkAnm->play();
}

/* 00005B64-00006108       .text daWZ_Execute__FP8wz_class */
static BOOL daWZ_Execute(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_38;
    cXyz local_44;

    if ((i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) && (i_this->mEnableSpawnSwitch != 0xFF) &&
        (!dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, dComIfGp_roomControl_getStayNo())))
    {
        return TRUE;
    }
    if ((REG12_S(9) == 0) && (i_this->m352 != 0)) {
        fopAc_ac_c* pfVar3 = fopAcM_SearchByID(i_this->m344);
        if (pfVar3 == NULL) {
            i_this->m354 = 0;
            i_this->m344 = fpcM_ERROR_PROCESS_ID_e;
            i_this->m352 = 0;
        }
    }
    i_this->mLightInfluence.mPos = actor->current.pos;
    switch (i_this->mBehaviorType) {
        case BEHAVIOR_UNKNOWN_10:
            i_this->mLightInfluence.mColor.r = REG0_F(3) + 300.0f;
            i_this->mLightInfluence.mColor.g = REG0_F(4) + 50.0f;
            i_this->mLightInfluence.mColor.b = REG0_F(5);
#if VERSION > VERSION_JPN
            i_this->mLightInfluence.mPower = REG0_F(9) + 550.0f;
            i_this->mLightInfluence.mFluctuation = REG0_F(10) + 200.0f;
#endif
            break;
        case BEHAVIOR_UNKNOWN_11:
            i_this->mLightInfluence.mColor.r = REG0_F(6) + 300.0f;
            i_this->mLightInfluence.mColor.g = REG0_F(7) + 300.0f;
            i_this->mLightInfluence.mColor.b = REG0_F(8) + 20.0f;
#if VERSION > VERSION_JPN
            i_this->mLightInfluence.mPower = REG0_F(9) + 550.0f;
            i_this->mLightInfluence.mFluctuation = REG0_F(10) + 200.0f;
#endif
            break;
    }
#if VERSION < VERSION_USA
    i_this->mLightInfluence.mPower = REG0_F(9) + 550.0f;
    i_this->mLightInfluence.mFluctuation = REG0_F(10) + 200.0f;
#endif
    if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
        fopAcM_setGbaName(actor, dItemNo_MIRROR_SHIELD_e, 0x11, 0x2F);
        if (enemy_ice(&i_this->mEnemyIce)) {
            i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
            i_this->mpMorf->calc();
            if (i_this->mIsMiniBoss) {
                i_this->mpMaskMorf->getModel()->setBaseTRMtx(i_this->mpMorf->getModel()->getAnmMtx(0x13));
                i_this->mpMaskMorf->calc();
            }
            enemy_fire_remove(&i_this->mEnemyFire);
            rod_size_set(i_this, 1);
#if VERSION > VERSION_DEMO
            BG_check(i_this);
#endif
            return TRUE;
        }
    }
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m3D4[i] != 0) {
            i_this->m3D4[i]--;
        }
    }
    switch (i_this->mAction) {
        case ACTION_DOUSA:
            action_dousa(i_this);
            break;
        case ACTION_TAMA_DOUSA:
            action_tama_dousa(i_this);
            break;
        case ACTION_ITAI:
            action_itai(i_this);
            break;
        case ACTION_SUMMON_DOUSA:
            action_summon_dousa(i_this);
            break;
        case ACTION_DEMO:
            action_demo(i_this);
            break;
    }
    if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
        if ((i_this->mAction != ACTION_ITAI) && (i_this->mAction != ACTION_DEMO)) {
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->m3E6, 1, 0x500);
            cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x500);
        }
        i_this->mpMorf->play(NULL, 0, 0);
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    local_38.x = 0.0f;
    local_38.y = 0.0f;
    local_38.z = actor->speedF;
    MtxPosition(&local_38, &local_44);
    actor->speed.x = local_44.x;
    if (i_this->mBehaviorType >= BEHAVIOR_UNKNOWN_10) {
        actor->speed.y = local_44.y;
    }
    actor->speed.z = local_44.z;
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -100.0f) {
        actor->speed.y = -100.0f;
    }
    fopAcM_posMove(actor, NULL);
    actor->eyePos = actor->current.pos;
    if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
        BG_check(i_this);
#if VERSION == VERSION_DEMO
        if ((i_this->mAction != ACTION_ITAI) && (i_this->mAction != ACTION_DEMO))
#else
        if ((i_this->mAction != ACTION_ITAI) && (i_this->mAction != ACTION_DEMO) && (i_this->mMode != MODE_DOUSA_7))
#endif
        {
            fuwafuwa_calc(i_this);
        }
        actor->attention_info.position = actor->current.pos;
        actor->attention_info.position.y += 190.0f;
        actor->eyePos.y += REG12_F(18) + 120.0f;
        i_this->mBodyCoCyl.SetC(actor->current.pos);
        i_this->mBodyCoCyl.SetH(170.0f);
        i_this->mBodyCoCyl.SetR(50.0f);
        dComIfG_Ccsp()->Set(&i_this->mBodyCoCyl);
    } else if ((i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_1) && (i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_2)) {
        BG_check(i_this);
        i_this->mBallCoSph.SetC(actor->current.pos);
        i_this->mBallCoSph.SetR(i_this->m410);
        dComIfG_Ccsp()->Set(&i_this->mBallCoSph);
        dComIfG_Ccsp()->SetMass(&i_this->mBallCoSph, 1);
    }
    draw_SUB(i_this);
    i_this->mF04 = actor->current.pos;
    i_this->mF10 = actor->shape_angle;

    return TRUE;
}

/* 00006108-00006110       .text daWZ_IsDelete__FP8wz_class */
static BOOL daWZ_IsDelete(wz_class*) {
    return TRUE;
}

/* 00006110-0000627C       .text daWZ_Delete__FP8wz_class */
static BOOL daWZ_Delete(wz_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (actor->health == -128) {
        if (i_this->mIsMiniBoss) {
            mDoAud_subBgmStop();
        }
#if VERSION == VERSION_DEMO
        if (i_this->mDisableSpawnOnDeathSwitch != 0xFF)
#else
        if ((strcmp(dComIfGp_getStartStageName(), "kazeMB")) && (i_this->mDisableSpawnOnDeathSwitch != 0xFF))
#endif
        {
            dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
        }
#if VERSION == VERSION_DEMO
        fopAcM_onActor(actor);
#endif
    }
    if ((i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_1) && (i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_2)) {
        dComIfG_resDeleteDemo(&i_this->mPhase, "WZ");
    } else {
        dComIfG_resDeleteDemo(&i_this->mPhase, "WZB");
    }
    if ((i_this->mBehaviorType == BEHAVIOR_UNKNOWN_10) || (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_11)) {
        dKy_plight_cut(&i_this->mLightInfluence);
    }
    i_this->mF18.remove();
    i_this->mF2C.remove();
    i_this->mF40.remove();
    i_this->mF54.remove();
    i_this->mF68.remove();
    if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
        enemy_fire_remove(&i_this->mEnemyFire);
    }
    return TRUE;
}

/* 0000627C-00006684       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    wz_class* i_this = (wz_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("WZ", dRes_INDEX_WZ_BDL_WZ_e),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("WZ", dRes_INDEX_WZ_BCK_TAME1_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x37441422
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }
    if (i_this->mBehaviorType > BEHAVIOR_UNKNOWN_10) {
        return TRUE;
    }
    if (i_this->mIsMiniBoss) {
        i_this->mpMaskMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("WZ", dRes_INDEX_WZ_BDL_WZ_KAMEN_e),
            NULL,
            NULL,
            NULL,
            J3DFrameCtrl::EMode_NONE,
            0.0f,
            0,
            -1,
            1,
            NULL,
            0x80000,
            0x37441422
        );
        if ((i_this->mpMaskMorf == NULL) || (i_this->mpMaskMorf->getModel() == NULL)) {
            return FALSE;
        }
        if (!i_this->mMaskInvisibleModel.create(i_this->mpMaskMorf->getModel())) {
            return FALSE;
        }
    }
    i_this->mpWandMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("WZ", dRes_INDEX_WZ_BDL_WZ_STICK_e),
        NULL,
        NULL,
        NULL,
        J3DFrameCtrl::EMode_LOOP,
        0.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    if ((i_this->mpWandMorf == NULL) || (i_this->mpWandMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpWandMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpWandMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpWandMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(rod_nodeCallBack);
    }
    J3DModel* model = i_this->mpMorf->getModel();
    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm == NULL) {
        return FALSE;
    }
    if (!i_this->mpBrkAnm->init(model->getModelData(), (J3DAnmTevRegKey*)dComIfG_getObjectRes("WZ", dRes_INDEX_WZ_BRK_WZ_e), true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    if (i_this->mInvisibleModel.create(i_this->mpMorf->getModel())) {
        return TRUE;
    }
    return FALSE;
}

/* 000066CC-00006888       .text useHeapInit2__FP10fopAc_ac_c */
static BOOL useHeapInit2(fopAc_ac_c* a_this) {
    wz_class* i_this = (wz_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("WZB", dRes_INDEX_WZB_BDL_YSUMN00_e),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("WZB", dRes_INDEX_WZB_BCK_YSUMN00_e),
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x19000222
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    J3DModel* model = i_this->mpMorf->getModel();
    i_this->mpBtkAnm = new mDoExt_btkAnm();
    if (i_this->mpBtkAnm == NULL) {
        return FALSE;
    }
    if (i_this->mpBtkAnm
            ->init(model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("WZB", dRes_INDEX_WZB_BTK_YSUMN00_e), true, J3DFrameCtrl::EMode_NONE))
    {
        return TRUE;
    }
    return FALSE;
}

/* 00006888-000071C4       .text daWZ_Create__FP10fopAc_ac_c */
static cPhs_State daWZ_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl body_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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

    wz_class* pfVar4;
    wz_class* pfVar9;

    fopAcM_ct_Retail(a_this, wz_class);
    wz_class* i_this = (wz_class*)a_this;
    i_this->mBehaviorType = fopAcM_GetParam(a_this);
    i_this->mDisableSpawnOnDeathSwitch = (fopAcM_GetParam(a_this) >> 8);
    i_this->mEnableSpawnSwitch = (fopAcM_GetParam(a_this) >> 0x10);
    i_this->mPathIndex = (fopAcM_GetParam(a_this) >> 0x18);
    i_this->mEnemySummonTableIndex = a_this->current.angle.z;
    if (i_this->mBehaviorType == 0xFF) {
        i_this->mBehaviorType = BEHAVIOR_ATTACK;
    }
#if VERSION >= VERSION_USA
    if (i_this->mBehaviorType == BEHAVIOR_MINIBOSS) {
        i_this->mBehaviorType = BEHAVIOR_ATTACK_AND_SUMMON;
        i_this->mIsMiniBoss = true;
    }
    if (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_3) {
        i_this->mBehaviorType = BEHAVIOR_ATTACK;
        i_this->m351 = true;
    }
    if (i_this->mEnemySummonTableIndex == 0xFF) {
        i_this->mEnemySummonTableIndex = 0;
    }
#endif
    cPhs_State res;
    if ((i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_1) && (i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_2)) {
        res = dComIfG_resLoad(&i_this->mPhase, "WZ");
    } else {
        res = dComIfG_resLoad(&i_this->mPhase, "WZB");
    }
#if VERSION < VERSION_USA
    if (res == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(a_this, wz_class);
#if VERSION == VERSION_DEMO
        if (REG8_S(9) != 0) {
            if (i_this->mBehaviorType == BEHAVIOR_ATTACK_AND_SUMMON) {
                i_this->mBehaviorType = BEHAVIOR_MINIBOSS;
            }
            if (i_this->mBehaviorType == BEHAVIOR_ATTACK) {
                i_this->mBehaviorType = BEHAVIOR_UNKNOWN_3;
            }
        }
#endif
        if (i_this->mBehaviorType == BEHAVIOR_MINIBOSS) {
            i_this->mBehaviorType = BEHAVIOR_ATTACK_AND_SUMMON;
            i_this->mIsMiniBoss = true;
        }
        if (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_3) {
            i_this->mBehaviorType = BEHAVIOR_ATTACK;
            i_this->m351 = true;
        }
#else
    if (i_this->mBehaviorType > BEHAVIOR_UNKNOWN_10) {
        i_this->mBallCoSph.SetAtType(AT_TYPE_MACHETE);
        i_this->m344 = fopAcM_GetLinkId(a_this);
        if (i_this->m344 == fpcM_ERROR_PROCESS_ID_e) {
            return cPhs_ERROR_e;
        }
        pfVar4 = (wz_class*)fopAcM_SearchByID(i_this->m344);
        if (pfVar4 == NULL) {
            return cPhs_ERROR_e;
        }
        if (i_this->mBehaviorType == BEHAVIOR_SPAWNER_ORB_1) {
            i_this->m344 = pfVar4->m344;
            pfVar9 = (wz_class*)fopAcM_SearchByID(i_this->m344);
            if (pfVar9 == NULL) {
                return cPhs_ERROR_e;
            }
        }
        i_this->m338 = pfVar4->m338;
        i_this->m358 = pfVar4->m358;
        i_this->m354 = pfVar4->m354;
        i_this->m3F0 = pfVar4->m3F0;
        i_this->m3EC = pfVar4->m3EC;
    }
    if (res != cPhs_COMPLEATE_e) {
        if ((res == cPhs_ERROR_e) && (i_this->mBehaviorType == BEHAVIOR_SPAWNER_ORB_1)) {
            pfVar4 = (wz_class*)fopAcM_SearchByID(i_this->m344);
            pfVar4->m354 = 0;
        }
        return res;
    }
#endif
        if ((i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) && (i_this->mDisableSpawnOnDeathSwitch != 0xFF) &&
            (dComIfGs_isSwitch(i_this->mDisableSpawnOnDeathSwitch, dComIfGp_roomControl_getStayNo())))
        {
            return cPhs_ERROR_e;
        }
        if ((i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_1) && (i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_2)) {
            u32 maxHeapSize = 0x3440;
            if (i_this->mBehaviorType >= BEHAVIOR_UNKNOWN_10) {
                maxHeapSize = 0x3640;
            }
            if (!fopAcM_entrySolidHeap(a_this, useHeapInit, maxHeapSize)) {
                return cPhs_ERROR_e;
            }
        } else {
            if (!fopAcM_entrySolidHeap(a_this, useHeapInit2, 0xcc0)) {
#if VERSION >= VERSION_USA
                pfVar4 = (wz_class*)fopAcM_SearchByID(i_this->m344);
                pfVar4->m354 = 0;
#endif
                return cPhs_ERROR_e;
            }
            if (i_this->mBehaviorType == BEHAVIOR_SPAWNER_ORB_2) {
                fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
            }
            J3DModelData* modelData = i_this->mpMorf->getModel()->getModelData();
            J3DTexture* texture = modelData->getTexture();
            if (texture == NULL) {
#if VERSION >= VERSION_USA
                pfVar4 = (wz_class*)fopAcM_SearchByID(i_this->m344);
                pfVar4->m354 = 0;
#endif
                return cPhs_ERROR_e;
            }
            JUTNameTab* textureName = modelData->getTextureName();
            if (textureName == NULL) {
#if VERSION >= VERSION_USA
                pfVar4 = (wz_class*)fopAcM_SearchByID(i_this->m344);
                pfVar4->m354 = 0;
#endif
                return cPhs_ERROR_e;
            }
            for (u16 i = 0; i < texture->getNum(); i++) {
                if (strcmp(textureName->getName(i), "__dummy") == 0) {
                    texture->setResTIMG(i, *mDoGph_gInf_c::getFrameBufferTimg());
                }
            }
            mDoExt_modelTexturePatch(modelData);
        }
        a_this->current.angle.z = 0;
        a_this->shape_angle.z = 0;
#if VERSION < VERSION_USA
        if (i_this->mEnemySummonTableIndex == 0xFF) {
            i_this->mEnemySummonTableIndex = 0;
        }
#endif
        a_this->attention_info.flags = 0;
        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(a_this, -100.0f, -50.0f, -50.0f, 100.0f, 200.0f, 100.0f);
        if (i_this->mBehaviorType < BEHAVIOR_UNKNOWN_10) {
            a_this->stealItemLeft = 3;
            a_this->max_health = 4;
            a_this->health = 4;
            a_this->attention_info.distances[2] = 4;
            switch (i_this->mBehaviorType) {
                case BEHAVIOR_ATTACK:
                    a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("wiz_r", 0);
                    break;
                case BEHAVIOR_ATTACK_AND_SUMMON:
                    a_this->max_health = 8;
                    a_this->health = 8;
                    a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("wiz_s", 0);
                    i_this->m354 = 0;
                    i_this->m3EC = i_this->mEnemySummonTableIndex;
#if VERSION < VERSION_USA
                    if ((s16)REG8_S(6) != 0) {
                        i_this->m3EC = (s16)(REG8_S(6) - 1);
                    }
#endif
                    if (i_this->mIsMiniBoss == true) {
                        i_this->m3EC = 7;
                        fopAcM_OnStatus(a_this, fopAcStts_BOSS_e);
                        a_this->max_health = 12;
                        a_this->health = 12;
                    } else {
                        i_this->m3F0 = (s16)cM_rndF(3.99f);
                        i_this->m3F0 = i_this->m3F0 & 3;
                    }
            }
#if VERSION < VERSION_USA
            if (REG12_S(2) != 0) {
                a_this->max_health = 1;
                a_this->health = 1;
            }
            if (REG12_S(8) != 0) {
                a_this->max_health = 50;
                a_this->health = 50;
            }
#else
        if (REG8_S(1) != 0) {
            a_this->max_health = 127;
            a_this->health = 127;
        }
#endif
            if (i_this->mPathIndex != 0xFF) {
                i_this->mPath = dPath_GetRoomPath(i_this->mPathIndex, fopAcM_GetRoomNo(a_this));
                if (i_this->mPath != NULL) {
                    s32 r4 = cM_rndF(i_this->mPath->m_num);
                    if (r4 == i_this->mPath->m_num) {
                        r4--;
                    }
                    a_this->current.pos = i_this->mPath->m_points[r4].m_position;
                    i_this->mNextPath = dPath_GetNextRoomPath(i_this->mPath, fopAcM_GetRoomNo(a_this));
                }
            }
            i_this->m32C = a_this->current.pos;
            draw_SUB(i_this);
            i_this->mBodyCoCyl.Set(body_co_cyl_src);
            i_this->mBodyCoCyl.SetStts(&i_this->mStts);
            i_this->mBodyCoCyl.OffTgSetBit();
            i_this->mBodyCoCyl.ClrTgHit();
            i_this->m3E6 = fopAcM_searchPlayerAngleY(a_this);
            a_this->current.angle.y = i_this->m3E6;
            a_this->shape_angle.y = i_this->m3E6;
            i_this->m408 = 100.0f;
            i_this->m40C = 110.0f;
            i_this->mEnemyIce.mpActor = a_this;
            i_this->mEnemyIce.mWallRadius = 80.0f;
            i_this->mEnemyIce.mCylHeight = 50.0f;
            i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
            i_this->mEnemyFire.mpActor = a_this;

            static u8 fire_j[ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs)] = {
                WZ_JNT_WIZ_ROOT_e,
                WZ_JNT_WIZ_KOSI_1_e,
                WZ_JNT_WIZ_MUNE_1_e,
                WZ_JNT_WIZ_MUNE_2_e,
                WZ_JNT_WIZ_KATA_L_e,
                WZ_JNT_WIZ_TEKUBI_L1_e,
                WZ_JNT_WIZ_KATA_R1_e,
                WZ_JNT_WIZ_TEKUBI_R1_e,
                WZ_JNT_WIZ_ATAMA_1_e,
                WZ_JNT_WIZ_SHITA_1_e
            };
            static f32 fire_sc[ARRAY_SIZE(i_this->mEnemyFire.mParticleScale)] = {
                1.0f, // WZ_JNT_WIZ_ROOT_e
                1.0f, // WZ_JNT_WIZ_KOSI_1_e
                1.0f, // WZ_JNT_WIZ_MUNE_1_e
                1.0f, // WZ_JNT_WIZ_MUNE_2_e
                1.0f, // WZ_JNT_WIZ_KATA_L_e
                1.0f, // WZ_JNT_WIZ_TEKUBI_L1_e
                1.0f, // WZ_JNT_WIZ_KATA_R1_e
                1.0f, // WZ_JNT_WIZ_TEKUBI_R1_e
                1.0f, // WZ_JNT_WIZ_ATAMA_1_e
                1.0f  // WZ_JNT_WIZ_SHITA_1_e
            };

            for (int i = 0; i < ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
                i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
                i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
            }
            i_this->m3EA = 0;
            i_this->m308.setall(0.0f);
            if (strcmp(dComIfGp_getStartStageName(), "kazeMB") == 0) {
                i_this->mAction = ACTION_DEMO;
                if (i_this->mIsMiniBoss) {
                    a_this->current.pos.setall(0.0f);
                    come_flag = false;
                    i_this->mMode = MODE_DEMO_50;
                } else {
                    fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
                    i_this->mMode = MODE_DEMO_60;
                }
            } else {
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_0;
            }
        } else if ((i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_1) && (i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_2)) {
            i_this->m408 = 0.0f;
            i_this->m40C = 40.0f;
            static dCcD_SrcSph ball_co_sph_src = {
                // dCcD_SrcGObjInf
                {
                    /* Flags             */ 0,
                    /* SrcObjAt  Type    */ AT_TYPE_FIRE,
                    /* SrcObjAt  Atp     */ 2,
                    /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
                    /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
                    /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
                // cM3dGSphS
                {{
                    /* Center */ {0.0f, 0.0f, 0.0f},
                    /* Radius */ 15.0f,
                }},
            };
            i_this->mBallCoSph.Set(ball_co_sph_src);
            i_this->mBallCoSph.SetStts(&i_this->mStts);
            i_this->m3D4[2] = 300;
            i_this->mAction = ACTION_TAMA_DOUSA;
            i_this->mMode = MODE_TAMA_DOUSA_100;
        } else {
            i_this->mAction = ACTION_SUMMON_DOUSA;
            i_this->mMode = MODE_SUMMON_DOUSA_200;
        }
#if VERSION < VERSION_USA
        if (i_this->mBehaviorType > BEHAVIOR_UNKNOWN_10) {
            i_this->mBallCoSph.SetAtType(AT_TYPE_MACHETE);
            i_this->m344 = fopAcM_GetLinkId(a_this);
            if (i_this->m344 == fpcM_ERROR_PROCESS_ID_e) {
                return cPhs_ERROR_e;
            }
            pfVar4 = (wz_class*)fopAcM_SearchByID(i_this->m344);
            if (pfVar4 != NULL) {
                if (i_this->mBehaviorType == BEHAVIOR_SPAWNER_ORB_1) {
                    i_this->m344 = pfVar4->m344;
                    pfVar9 = (wz_class*)fopAcM_SearchByID(i_this->m344);
                    if (pfVar9 != NULL) {
                        return cPhs_ERROR_e;
                    }
                } else {
                    i_this->m338 = pfVar4->m338;
                    i_this->m358 = pfVar4->m358;
                    i_this->m354 = pfVar4->m354;
                    i_this->m3F0 = pfVar4->m3F0;
                    i_this->m3EC = pfVar4->m3EC;
                }
            } else {
                return cPhs_ERROR_e;
            }
        }
#endif
        if ((i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_1) && (i_this->mBehaviorType != BEHAVIOR_SPAWNER_ORB_2)) {
            i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
            i_this->mStts.Init(0xFE, 1, a_this);
            BG_check(i_this);
        }
        if ((i_this->mBehaviorType == BEHAVIOR_UNKNOWN_10) || (i_this->mBehaviorType == BEHAVIOR_UNKNOWN_11)) {
            dKy_plight_set(&i_this->mLightInfluence);
        }
#if VERSION < VERSION_USA
    }
#endif
    return res;
}

static actor_method_class l_daWZ_Method = {
    (process_method_func)daWZ_Create,
    (process_method_func)daWZ_Delete,
    (process_method_func)daWZ_Execute,
    (process_method_func)daWZ_IsDelete,
    (process_method_func)daWZ_Draw,
};

actor_process_profile_definition g_profile_WZ = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_WZ_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(wz_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_WZ_e,
    /* Actor SubMtd */ &l_daWZ_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
