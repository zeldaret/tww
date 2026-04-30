/**
 * d_a_gm.cpp
 * Mini-Boss - Mothula / Enemy - Mothula Larva
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_gm.h"
#include "d/d_camera.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "d/res/res_gm.h"
#include "d/actor/d_a_player.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

enum Action {
    ACTION_DOUSA = 0,
    ACTION_HANE_RAKKA = 1,
    ACTION_UCHIWA_DOUSA = 2,
    ACTION_TOTUGEKI = 3,
    ACTION_KABEHARI = 4,
    ACTION_FLY_DAMAGE = 5,
    ACTION_GROUND_ATTACK = 10,
    ACTION_DEMO = 20
};

enum Mode {
    MODE_DOUSA_0 = 0,
    MODE_DOUSA_1 = 1,
    MODE_DOUSA_2 = 2,
    MODE_DOUSA_3 = 3,
    MODE_DOUSA_4 = 4,
    MODE_HANE_RAKKA_10 = 10,
    MODE_HANE_RAKKA_11 = 11,
    MODE_HANE_RAKKA_12 = 12,
    MODE_UCHIWA_DOUSA_20 = 20,
    MODE_UCHIWA_DOUSA_21 = 21,
    MODE_UCHIWA_DOUSA_22 = 22,
    MODE_TOTUGEKI_30 = 30,
    MODE_TOTUGEKI_31 = 31,
    MODE_TOTUGEKI_32 = 32,
    MODE_TOTUGEKI_33 = 33,
    MODE_TOTUGEKI_34 = 34,
    MODE_TOTUGEKI_37 = 37,
    MODE_TOTUGEKI_38 = 38,
    MODE_KABEHARI_40 = 40,
    MODE_KABEHARI_41 = 41,
    MODE_KABEHARI_42 = 42,
    MODE_KABEHARI_43 = 43,
    MODE_FLY_DAMAGE_50 = 50,
    MODE_FLY_DAMAGE_51 = 51,
    MODE_FLY_DAMAGE_52 = 52,
    MODE_GROUND_ATTACK_60 = 60,
    MODE_GROUND_ATTACK_61 = 61,
    MODE_GROUND_ATTACK_62 = 62,
    MODE_GROUND_ATTACK_63 = 63,
    MODE_GROUND_ATTACK_70 = 70,
    MODE_GROUND_ATTACK_71 = 71,
    MODE_GROUND_ATTACK_72 = 72,
    MODE_GROUND_ATTACK_73 = 73,
    MODE_GROUND_ATTACK_74 = 74,
    MODE_GROUND_ATTACK_75 = 75,
    MODE_GROUND_ATTACK_76 = 76,
    MODE_GROUND_ATTACK_77 = 77,
    MODE_GROUND_ATTACK_80 = 80,
    MODE_GROUND_ATTACK_81 = 81,
    MODE_GROUND_ATTACK_82 = 82,
    MODE_GROUND_ATTACK_83 = 83,
    MODE_GROUND_ATTACK_84 = 84,
    MODE_GROUND_ATTACK_85 = 85,
    MODE_GROUND_ATTACK_90 = 90,
    MODE_GROUND_ATTACK_91 = 91,
    MODE_GROUND_ATTACK_100 = 100,
    MODE_GROUND_ATTACK_101 = 101,
    MODE_DEMO_200 = 200,
    MODE_DEMO_201 = 201,
    MODE_DEMO_202 = 202,
    MODE_DEMO_203 = 203,
    MODE_DEMO_205 = 205,
    MODE_DEMO_206 = 206,
    MODE_DEMO_207 = 207,
    MODE_DEMO_208 = 208,
    MODE_DEMO_220 = 220,
    MODE_DEMO_221 = 221,
    MODE_DEMO_222 = 222,
    MODE_DEMO_223 = 223,
};

/* 000000EC-0000032C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();
        gm_class* i_this = (gm_class*)model->getUserArea();
        s32 jntNo = joint->getJntNo();
        if ((i_this != NULL) && (i_this->m02CD == 0)) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz offset;
            switch (jntNo) {
            case 3:
                offset.setall(0.0f);
                MtxPosition(&offset, &i_this->m03FC);
                break;
            case 4:
                offset.setall(0.0f);
                MtxPosition(&offset, &i_this->m03F0);
                cMtx_YrotM(*calc_mtx, i_this->m043A);
                cMtx_XrotM(*calc_mtx, i_this->m0438);
                cMtx_ZrotM(*calc_mtx, i_this->m043C);
                break;
            case 5:
                offset.setall(0.0f);
                MtxPosition(&offset, &i_this->m03E4);
                offset.x = 70.0f;
                MtxPosition(&offset, &i_this->m03A8);
                break;
            case 12:
            case 14:
            case 16:
            case 18:
                s32 iVar2 = (int)(jntNo - 0xc) >> 1;
                cMtx_YrotM(*calc_mtx, i_this->m0414[iVar2].y);
                cMtx_XrotM(*calc_mtx, i_this->m0414[iVar2].x);
                cMtx_ZrotM(*calc_mtx, i_this->m0414[iVar2].z);
            }
            if ((((jntNo != 12) && (jntNo != 14)) && (jntNo != 16)) && (jntNo != 18)) {
                cMtx_YrotM(*calc_mtx, i_this->m042E);
                cMtx_XrotM(*calc_mtx, i_this->m042C);
                cMtx_ZrotM(*calc_mtx, i_this->m0430);
            }
            model->setAnmMtx(jntNo, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000368-0000048C       .text draw_SUB__FP8gm_class */
static void draw_SUB(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos.x + i_this->m03B4.x, actor->current.pos.y + i_this->m03B4.y, actor->current.pos.z + i_this->m03B4.z);
    mDoMtx_stack_c::XrotM(i_this->m043E.x);
    mDoMtx_stack_c::ZrotM(i_this->m043E.z);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::YrotM(i_this->m0320);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    if (i_this->m02CD == 0) {
        i_this->mpMorf->calc();
        enemy_fire(&i_this->mEnemyFire);
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
}

/* 0000048C-00000908       .text daGM_Draw__FP8gm_class */
static BOOL daGM_Draw(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_30;
    cXyz local_48;

    J3DModel* pJVar11 = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(pJVar11, &actor->tevStr);
    dSnap_RegistFig(DSNAP_TYPE_GM, actor, actor->attention_info.position, actor->shape_angle.y, 1.0f, 1.0f, 1.0f);
    if ((i_this->m02CD == 0) && (i_this->mEnemyIce.mFreezeTimer > 20)) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, &i_this->mInvisibleModel);
        return TRUE;
    }
    if (i_this->m02CD == 0) {
        s32 iVar7 = 0;
        for (u16 i = 0; i < pJVar11->getModelData()->getJointNum(); i++) {
            J3DMaterial* mat = pJVar11->getModelData()->getJointNodePointer(i)->getMesh();
            while (mat) {
                J3DShape* pJVar3 = mat->getShape();
                switch (iVar7) {
                case 2:
                    if (!(i_this->m02CC & 8)) {
                        pJVar3->show();
                    } else {
                        pJVar3->hide();
                    }
                    break;
                case 3:
                    if (!(i_this->m02CC & 2)) {
                        pJVar3->show();
                    } else {
                        pJVar3->hide();
                    }
                    break;
                case 4:
                    if (!(i_this->m02CC & 1)) {
                        pJVar3->show();
                    } else {
                        pJVar3->hide();
                    }
                    break;
                case 5:
                    if (!(i_this->m02CC & 4)) {
                        pJVar3->show();
                    } else {
                        pJVar3->hide();
                    }
                    break;
                default:
                    pJVar3->show();
                    break;
                }
                mat = mat->getNext();
                iVar7++;
            }
        }
        switch (i_this->m0324) {
        case 1:
            i_this->mDamageBrkAnm->entry(pJVar11->getModelData());
            break;
        case 2:
            i_this->mAtackBrkAnm->entry(pJVar11->getModelData());
            break;
        case 3:
            i_this->mDeadBrkAnm->entry(pJVar11->getModelData());
            break;
        default:
            i_this->mBodyGlowBrkAnm->entry(pJVar11->getModelData());
            break;
        }
        i_this->mpMorf->entryDL();
        switch (i_this->m0324) {
        case 1:
            i_this->mDamageBrkAnm->remove(pJVar11->getModelData());
            break;
        case 2:
            i_this->mAtackBrkAnm->remove(pJVar11->getModelData());
            break;
        case 3:
            i_this->mDeadBrkAnm->remove(pJVar11->getModelData());
            break;
        default:
            i_this->mBodyGlowBrkAnm->remove(pJVar11->getModelData());
            break;
        }
    } else {
        i_this->mpMorf->updateDL();
    }
    int i;
    J3DModelData* pJVar6 = pJVar11->getModelData();
    J3DModel* pJVar9 = i_this->m0444;
    for (i = 0; i < pJVar6->getJointNum(); i++) {
        pJVar9->setAnmMtx(i, pJVar11->getAnmMtx(i));
    }
    for (int i = 0; i < pJVar6->getWEvlpMtxNum(); i++) {
        pJVar9->setWeightAnmMtx(i, pJVar11->getWeightAnmMtx(i));
    }
    local_30.set(
        actor->current.pos.x + i_this->m03B4.x, REG8_F(18) + (10.0f + (actor->current.pos.y + i_this->m03B4.y)), actor->current.pos.z + i_this->m03B4.z
    );
    i_this->mShadowId = dComIfGd_setRealShadow(
        i_this->mShadowId, TRUE, i_this->m0444, &local_30, REG8_F(19) + 900.0f, (actor->current.pos.y + i_this->m03B4.y) - i_this->mAcch.GetGroundH(), NULL
    );
    if (REG8_S(1) == 0) {
        return TRUE;
    }
    f32 f0 = i_this->m0360[0].x;
    f32 f1 = 0.0f;
    if ((f0 != f1) || (i_this->m0360[0].z != f1)) {
        f0 = i_this->m0360[1].x;
        f1 = 0.0f;
        if ((f0 != f1) || (i_this->m0360[1].z != f1)) {
            for (s32 i = 0; i < ARRAY_SSIZE(i_this->m0360); i++) {
                local_48 = actor->current.pos + i_this->m03B4;
            }
        }
    }
    return TRUE;
}

/* 00000908-00000A34       .text anm_init__FP8gm_classifUcfi */
static void anm_init(gm_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->mCurrBckIdx = bckFileIdx;
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("GM", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("GM", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("GM", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000A34-00000D00       .text wing_cut_stat__FP8gm_class */
static BOOL wing_cut_stat(gm_class* i_this) {
    /* Nonmatching - retail-only regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    u32 parameters;
    csXyz local_88;
    cXyz local_38;
    cXyz cStack_44;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    static cXyz wing_birth_pos_dt[] = {cXyz(94.0f, -72.0f, -30.0f), cXyz(-94.0f, -72.0f, -30.0f), cXyz(144.0f, 72.0f, -30.0f), cXyz(-144.0f, 72.0f, -30.0f)};
    s32 i;
    s32 uVar4;
    for (i = 0, uVar4 = 1; i < 4; i++, uVar4 *= 2) {
        if (!(i_this->m02CC & uVar4)) {
            parameters = i + 1 | 0x100;
            if (i_this->mAction == ACTION_KABEHARI) {
                parameters = i + 1 | 0x200;
            }
            s16 y = actor->shape_angle.y;
            cMtx_YrotS(*calc_mtx, y);
            local_38.x = wing_birth_pos_dt[i].x;
            local_38.y = wing_birth_pos_dt[i].y;
            local_38.z = wing_birth_pos_dt[i].z;
            MtxPosition(&local_38, &cStack_44);
            cStack_44 += actor->current.pos + i_this->m03B4;
            local_88 = actor->shape_angle;
            local_88.y += -0x8000;
            fopAcM_create(PROC_GM, parameters, &cStack_44, fopAcM_GetRoomNo(actor), &local_88, &actor->scale, 0, NULL);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &cStack_44, &player->shape_angle);
            i_this->m02CC |= uVar4;
            if ((actor->health > 0) && (i_this->m02D1 != 10)) {
                return TRUE;
            }
        }
    }
    if ((actor->health <= 0) || (i_this->m02D1 == 10)) {
        return TRUE;
    }
    return FALSE;
}

/* 00000D3C-0000170C       .text body_atari_check__FP8gm_class */
static BOOL body_atari_check(gm_class* i_this) {
    fopEn_enemy_c* actor = (fopEn_enemy_c*)&i_this->actor;
    bool bVar2;
    cCcD_Obj* pcVar4;
    s8 sVar6;
    cXyz local_4c;
    cXyz local_58;
    CcAtInfo local_40;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if (i_this->mCountDownTimers[3] != 0) {
        return FALSE;
    }
    if ((i_this->mMode == MODE_GROUND_ATTACK_90) || (i_this->mMode == MODE_GROUND_ATTACK_91)) {
        return FALSE;
    }
    if (!i_this->mBodyCyl.ChkTgHit()) {
        i_this->m02D2 = 0;
        return FALSE;
    }
    if (i_this->m02D2 != 0) {
        return FALSE;
    }
    i_this->m02D1 = 0;
    pcVar4 = i_this->mBodyCyl.GetTgHitObj();
    local_4c = *i_this->mBodyCyl.GetTgHitPosP();
    i_this->m02D2 = 1;
    if (pcVar4 == NULL) {
        return FALSE;
    }
    i_this->mCountDownTimers[3] = 8;
    local_40.pParticlePos = NULL;
    bVar2 = false;
    switch (pcVar4->GetAtType()) {
    case AT_TYPE_GRAPPLING_HOOK:
        if (actor->stealItemLeft > 0) {
            sVar6 = actor->health;
            actor->health = 10;
            local_40.mpObj = i_this->mBodyCyl.GetTgHitObj();
            cc_at_check(actor, &local_40);
            i_this->m02D7++;
            actor->health = sVar6;
        }
        dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
        bVar2 = true;
        i_this->m02D1 = 3;
        break;
    case AT_TYPE_SWORD:
        fopAcM_seStart(actor, JA_SE_LK_SW_CRT_HIT, 0x20);
        i_this->m02D1 = 0;
        if (player->getCutType() == 0x06 || player->getCutType() == 0x07 || player->getCutType() == 0x08 || player->getCutType() == 0x09 ||
            player->getCutType() == 0x0A || player->getCutType() == 0x0C || player->getCutType() == 0x0E || player->getCutType() == 0x05 ||
            player->getCutType() == 0x0F || player->getCutType() == 0x10 || player->getCutType() == 0x15 || player->getCutType() == 0x17 ||
            player->getCutType() == 0x19 || player->getCutType() == 0x1A || player->getCutType() == 0x1B || player->getCutType() == 0x1E ||
            player->getCutType() == 0x1F)
        {
            i_this->m02D1 = 1;
        }
        break;
    case AT_TYPE_WIND:
        bVar2 = true;
        i_this->m02D1 = 3;
        if ((i_this->mAction != ACTION_UCHIWA_DOUSA) && ((i_this->m02CC & 0xF) != 0xF)) {
            if (i_this->mMode == MODE_TOTUGEKI_34) {
                i_this->m02D1 = 9;
            }
            i_this->m0330 = 250.0f;
            i_this->mMode = MODE_UCHIWA_DOUSA_20;
            i_this->mAction = ACTION_UCHIWA_DOUSA;
        }
        break;
    case AT_TYPE_BOOMERANG:
        bVar2 = true;
        i_this->m02D1 = 4;
        dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
    case AT_TYPE_BOKO_STICK:
        fopAcM_seStart(actor, JA_SE_LK_W_WEP_CRT_HIT, 0x20);
        break;
    case AT_TYPE_SKULL_HAMMER:
        fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x20);
        i_this->m02D1 = 7;
        if (player->getCutType() == 0x11) {
            i_this->m02D1 = 8;
        }
        break;
    case AT_TYPE_BOMB:
        i_this->m02D1 = 6;
        break;
    case AT_TYPE_HOOKSHOT:
        bVar2 = true;
        i_this->m02D1 = 10;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_CRT_HIT, 0x20);
        break;
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_FIRE:
        i_this->mEnemyFire.mFireDuration = 100;
        actor->health = 0;
        fopAcM_monsSeStart(&i_this->actor, JA_SE_CV_GM_DIE, 0);
        i_this->m02D1 = 5;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_CRT_HIT, 0x20);
        break;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 80.0f;
        actor->health = 0;
        actor->attention_info.flags = 0;
        fopAcM_monsSeStart(&i_this->actor, JA_SE_CV_GM_DIE, 0);
        i_this->m02D1 = 5;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_CRT_HIT, 0x20);
        break;
    case AT_TYPE_ICE_ARROW:
        i_this->mEnemyIce.mFreezeDuration = 200;
        enemy_fire_remove(&i_this->mEnemyFire);
        fopAcM_monsSeStart(actor, JA_SE_CV_GM_DIE, 0);
        actor->health = 0;
        bVar2 = true;
    case AT_TYPE_NORMAL_ARROW:
        i_this->m02D1 = 5;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_CRT_HIT, 0x20);
        break;
    default:
        i_this->m02D1 = 0;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_CRT_HIT, 0x20);
        break;
    }
    if (!bVar2) {
        local_40.mpObj = i_this->mBodyCyl.GetTgHitObj();
        cc_at_check(actor, &local_40);
        if ((((i_this->m02D1 == 1) || (i_this->m02D1 == 7)) || (i_this->m02D1 == 8)) || (actor->health <= 0)) {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_4c);
            local_58.setall(2.0f);
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_4c, &player->shape_angle, &local_58);
        } else {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &local_4c, &player->shape_angle);
        }
    }
    if ((pcVar4->GetAtType() == AT_TYPE_LIGHT_ARROW) || (pcVar4->GetAtType() == AT_TYPE_ICE_ARROW)) {
        return TRUE;
    }
    if ((i_this->m02D1 != 3 && (i_this->m02D1 != 9 && ((i_this->m02CC & 0xF) != 0xF))) && (i_this->m02CD == 0)) {
        i_this->m0330 = 250.0f;
        if (wing_cut_stat(i_this)) {
            if ((i_this->m02CC & 0xF) != 0xF) {
                fopAcM_monsSeStart(actor, JA_SE_CV_GM_DAMAGE, 0);
                actor->setBtNowFrame(1000.0f);
                if (i_this->mAction != ACTION_KABEHARI) {
                    i_this->mMode = MODE_FLY_DAMAGE_50;
                } else {
                    i_this->mMode = MODE_FLY_DAMAGE_52;
                }
                i_this->mAction = ACTION_FLY_DAMAGE;
            } else if (i_this->mAction != ACTION_GROUND_ATTACK) {
                fopAcM_monsSeStart(actor, JA_SE_CV_GM_LOST_WING, 0);
                actor->setBtNowFrame(1000.0f);
                if (i_this->mAction != ACTION_KABEHARI) {
                    i_this->mMode = MODE_GROUND_ATTACK_60;
                } else {
                    i_this->mMode = MODE_GROUND_ATTACK_61;
                }
                i_this->m032C = 60.0f;
                i_this->m0330 = 150.0f;
                i_this->mCountDownTimers[2] = cM_rndF(600.0f) + 600.0f;
                i_this->mAction = ACTION_GROUND_ATTACK;
            }
        }
    }
    return TRUE;
}

/* 0000170C-000017D8       .text BG_check__FP8gm_class */
static void BG_check(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->mAcchCir.SetWall(i_this->m032C, i_this->m0330);
    actor->current.pos += i_this->m03B4;
    actor->old.pos.y += i_this->m03B4.y;
    actor->current.pos.y -= i_this->m0328;
    actor->old.pos.y -= i_this->m0328;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    actor->current.pos.y += i_this->m0328;
    actor->old.pos.y += i_this->m0328;
    actor->current.pos -= i_this->m03B4;
    actor->old.pos.y -= i_this->m03B4.y;
}

/* 000017D8-00001B84       .text Line_check__FP8gm_class4cXyz */
static BOOL Line_check(gm_class* i_this, cXyz destPos) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_ac;
    cXyz local_b8;
    dBgS_LinChk linChk;

    cMtx_XrotS(*calc_mtx, i_this->m043E.x);
    cMtx_ZrotM(*calc_mtx, i_this->m043E.z);
    local_ac.x = 0.0f;
    local_ac.y = 100.0f;
    local_ac.z = 0.0f;
    MtxPosition(&local_ac, &local_b8);
    local_b8 += i_this->m03E4;
    local_b8 += i_this->m03B4;
    local_b8.y += 100.0f;
    destPos.y += 100.0f;
    linChk.Set(&local_b8, &destPos, actor);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        i_this->m03CC = local_b8;
        i_this->m03D8 = destPos;
        return FALSE;
    }
    return TRUE;
}

/* 00001FBC-0000212C       .text ks_set_rtn__FP8gm_class */
static BOOL ks_set_rtn(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    u32 parameters = 4;
    if (i_this->m02CE == 1) {
        if (i_this->m031E >= 0xA) {
            return TRUE;
        }
    } else if (i_this->m031E >= 0x14) {
        return TRUE;
    }
    if (i_this->mMode == MODE_GROUND_ATTACK_83) {
        parameters = 5;
    }
    fopAcM_seStart(actor, JA_SE_CM_GM_KUROBO_OUT, 0);
    csXyz local_30(actor->current.angle);
    local_30.y += cM_rndFX(4096.0f);
    fpc_ProcID fVar4 =
        fopAcM_createChild(PROC_KS, fopAcM_GetID(i_this), parameters, &i_this->m03FC, fopAcM_GetRoomNo(actor), &local_30, &actor->scale, 0, NULL);
    if (fVar4 != fpcM_ERROR_PROCESS_ID_e) {
        i_this->m031E++;
        return FALSE;
    }
    return TRUE;
}

/* 0000212C-00002204       .text wing_ret_set__FP8gm_class */
static void wing_ret_set(gm_class* i_this) {
    for (s32 i = 0; i < 4; i++) {
        cLib_addCalcAngleS2(&i_this->m0414[i].y, 0, 1, 0x200);
        cLib_addCalcAngleS2(&i_this->m0414[i].x, 0, 1, 0x200);
        cLib_addCalcAngleS2(&i_this->m0414[i].z, 0, 1, 0x200);
    }
    cLib_addCalcAngleS2(&i_this->m042E, 0, 1, 0x200);
    cLib_addCalcAngleS2(&i_this->m042C, 0, 1, 0x200);
    cLib_addCalcAngleS2(&i_this->m0430, 0, 1, 0x200);
    cLib_addCalcAngleS2(&i_this->m043A, 0, 1, 0x200);
}

/* 00002204-000022C4       .text fuwafuwa_set__FP8gm_class */
static void fuwafuwa_set(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (!(actor->current.pos.y < player->current.pos.y + 150.0f)) {
        i_this->mCountUpTimers[0] = i_this->mCountUpTimers[0] + 1000;
        i_this->m03C0.y = cM_ssin(i_this->mCountUpTimers[0]) * 100.0f;
        if ((i_this->mMode == MODE_DOUSA_3) || (i_this->mMode == MODE_DOUSA_4)) {
            i_this->m03C0.setall(0.0f);
        }
        cLib_addCalc2(&i_this->m03B4.y, i_this->m03C0.y, 1.0f, 10.0f);
    }
}

/* 000022C4-00002474       .text fly_move__FP8gm_class */
static BOOL fly_move(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar3;
    f32 dVar6;
    f32 dVar7;
    cXyz local_60;
    cXyz local_6c;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 sVar5 = 0x2000;
    if (i_this->mCountDownTimers[0] == 0) {
        if (cM_rnd() < 0.5f) {
            sVar5 = -0x2000;
        }
        sVar3 = dCam_getAngleY(dComIfGp_getCamera(0));
        for (s32 i = 0; i < 2; i++, sVar5 += 0x8000) {
            cMtx_YrotS(*calc_mtx, sVar3 + sVar5);
            local_60.set(0.0f, 0.0f, 300.0f);
            MtxPosition(&local_60, &local_6c);
            local_6c += player->current.pos;
            local_6c.y = actor->current.pos.y + i_this->m03B4.y;
            if (!Line_check(i_this, local_6c)) {
                dVar6 = local_6c.x - (actor->current.pos.x + i_this->m03B4.x);
                dVar7 = local_6c.z - (actor->current.pos.z + i_this->m03B4.z);
                actor->speedF = 10.0f;
                i_this->mCountDownTimers[0] = 20;
                i_this->mCountDownTimers[0] += (s16)cM_rndF(20.0f);
                i_this->m0334 = 0.0f;
                i_this->m0434 = cM_atan2s(dVar6, dVar7);
                return TRUE;
            }
        }
    }
    return FALSE;
}

/* 00002474-00002AB8       .text action_dousa__FP8gm_class */
static void action_dousa(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar5;
    s16 uVar8;
    f32 dVar12;
    f32 dVar14;
    f32 dVar13;
    f32 fVar15;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dVar14 = (player->current.pos.x - (actor->current.pos.x + i_this->m03B4.x));
    dVar13 = (player->current.pos.z - (actor->current.pos.z + i_this->m03B4.z));
    switch (i_this->mMode) {
    case MODE_DOUSA_0:
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        for (s32 i = 0; i < ARRAY_SIZE(i_this->m0360); i++) {
            i_this->m0360[i].setall(0.0f);
        }
        i_this->mBodyGlowBrkAnm->setFrame(0.0f);
        i_this->m0324 = 0;
        i_this->m032C = 0.0f;
        i_this->m0338.set(-120.0f, 220.0f, 60.0f);
        i_this->m0330 = 250.0f;
        i_this->mCountDownTimers[1] = cM_rndF(30.0f) + 30.0f;
        i_this->mCountDownTimers[0] = 0;
        if (i_this->mCurrBckIdx != GM_BCK_FLY) {
            anm_init(i_this, GM_BCK_FLY, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        i_this->mMode++;
    case MODE_DOUSA_1:
        i_this->m0348.y = player->current.pos.y + 250.0f;
        if (!((fly_move(i_this)) || (std::fabsf(actor->current.pos.y - i_this->m0348.y) > 40.0f))) {
            fVar15 = std::sqrtf(SQUARE(dVar14) + SQUARE(dVar13));
            if (!((fVar15 > 300.0f) || (i_this->mCountDownTimers[1] != 0))) {
                dVar12 = 0.1f;
                uVar8 = i_this->m02CC;
                for (s32 i = 0; i < 4; i++) {
                    if ((uVar8 & 1) != 0) {
                        dVar12 += 0.1f;
                        if (dVar12 > 0.3f) {
                            dVar12 = 0.3f;
                        }
                        uVar8 = (uVar8 >> 1);
                    }
                }
                i_this->mMode = MODE_DOUSA_2;
                if ((cM_rnd() < dVar12) && ((i_this->m02CC & 7) != 7)) {
                    actor->speedF = 0.0f;
                    i_this->mAction = ACTION_TOTUGEKI;
                    i_this->mMode = MODE_TOTUGEKI_30;
                }
            }
        }
        break;
    case MODE_DOUSA_2:
        anm_init(i_this, GM_BCK_ATACK01, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GM_ATTACK, 0);
        i_this->mAtackBrkAnm->setFrame(0.0f);
        i_this->m0324 = 2;
        actor->speedF = 0.0f;
        i_this->mCountDownTimers[1] = cM_rndF(20.0f) + 20.0f;
        i_this->mMode++;
    case MODE_DOUSA_3:
        i_this->m0348.y = player->current.pos.y + 100.0f;
        if (!((std::fabsf(actor->current.pos.y - i_this->m0348.y) > 40.0f) || (i_this->mCountDownTimers[1] != 0))) {
            i_this->m0434 = actor->shape_angle.y;
            actor->current.angle.y = i_this->m0434;
            actor->speedF = 50.0f;
            i_this->mAtSph.OnAtSetBit();
            i_this->mAtSph.OnAtHitBit();
            anm_init(i_this, GM_BCK_ATACK02, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GM_BAS_ATACK02);
            i_this->mMode++;
        }
        break;
    case MODE_DOUSA_4:
        if (i_this->mCountUpTimers[3] == 0) {
            if (i_this->mAtSph.ChkAtShieldHit()) {
                i_this->mAtSph.OffAtSetBit();
                i_this->mAtSph.OffAtSetBit();
                actor->speedF = -25.0f;
                i_this->mCountUpTimers[3] = 1;
            } else {
                if ((s16)player->mDamageWaitTimer != 0) {
                    actor->speedF = -50.0f;
                    i_this->mCountUpTimers[3] = 1;
                }
            }
        }
        cLib_addCalc0(&actor->speedF, 1.0f, 5.0f);
        if (i_this->mpMorf->isStop()) {
            actor->speedF = 0.0f;
            i_this->mCountDownTimers[1] = cM_rndF(20.0f) + 40.0f;
            anm_init(i_this, GM_BCK_ATACK01, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAtSph.OffAtSetBit();
            i_this->mAtSph.OffAtSetBit();
            i_this->mMode = MODE_DOUSA_0;
        }
    }
    fuwafuwa_set(i_this);
    if (((i_this->m02CC & 7) == 7) && (sVar5 = cLib_distanceAngleS(actor->shape_angle.z, 0), sVar5 < 0x100)) {
        i_this->m0436 = -0x4000;
    }
    if (i_this->mMode != MODE_DOUSA_4) {
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->m0434, 1, i_this->m0334);
        i_this->m0334 = 1700.0f;
        cLib_addCalc2(&i_this->m0334, 1700.0f, 1.0f, 3.0f);
        cLib_addCalcAngleS2(&actor->shape_angle.y, (s16)cM_atan2s(dVar14, dVar13), 1, 0x800);
    }
    cLib_addCalc2(&actor->current.pos.y, i_this->m0348.y, 1.0f, 3.0f);
    cLib_addCalcAngleS2(&i_this->m0320, 0, 1, 0x200);
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x200);
    fopAcM_seStart(actor, JA_SE_CM_GM_FLYING, 0);
}

/* 00002AB8-00002C9C       .text action_hane_rakka__FP8gm_class */
static void action_hane_rakka(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mMode) {
    case MODE_HANE_RAKKA_10:
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        actor->gravity = -1.0f;
        actor->speed.y = 7.0f;
        if (i_this->m02CD != 2) {
            actor->speedF = 40.0f;
            if ((i_this->m02CC == 1) || (i_this->m02CC == 3)) {
                actor->current.angle.y += (s16)(cM_rndFX(4096.0f) + 16384.0f);
                i_this->mCountUpTimers[0] = 0x1000;
            } else {
                actor->current.angle.y -= (s16)(cM_rndFX(4096.0f) + 16384.0f);
                i_this->mCountUpTimers[0] = -0x1000;
            }
            i_this->mCountUpTimers[1] = 0x300;
        }
        i_this->mMode++;
    case MODE_HANE_RAKKA_11:
        if ((i_this->mAcch.ChkGroundHit()) || (i_this->m0354.y - 1000.0f > actor->current.pos.y)) {
            actor->shape_angle.x = 0;
            i_this->mCountUpTimers[0] = 0;
            i_this->mCountUpTimers[1] = 0;
            i_this->mMode++;
        }
        break;
    case MODE_HANE_RAKKA_12:
        if (actor->scale.x < 0.1f) {
            fopAcM_delete(actor);
        }
    }
    cLib_addCalc0(&actor->scale.x, 1.0f, 0.02f);
    f32 fVar4 = actor->scale.x;
    actor->scale.y = fVar4;
    actor->scale.z = fVar4;
    cLib_addCalc0(&actor->speedF, 1.0f, 5.0f);
    if (actor->speed.y < 0.0f) {
        actor->shape_angle.y += i_this->mCountUpTimers[0];
        actor->shape_angle.x += i_this->mCountUpTimers[1];
    }
}

static csXyz wing_trans_angle_dt[4] = {
    csXyz(0x2710, -0x2ee0, -0x7d0), csXyz(-0x2710, 0x2ee0, -0x7d0), csXyz(-0x7d0, -0x2ee0, 0x7d0), csXyz(0x7d0, 0x2ee0, 0x7d0)
};

/* 00002C9C-000030FC       .text action_uchiwa_dousa__FP8gm_class */
static void action_uchiwa_dousa(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch (i_this->mMode) {
    case MODE_UCHIWA_DOUSA_20:
        anm_init(i_this, GM_BCK_PAUSE, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
        fopAcM_seStart(actor, JA_SE_CM_GM_HIT_WIND, 0);
        fopAcM_monsSeStart(actor, JA_SE_CV_GM_HIT_WIND, 0);
        i_this->m0330 = 250.0f;
        i_this->mAtSph.OffAtSetBit();
        i_this->mAtSph.OffAtSetBit();
        i_this->mWingCyl.OffAtSetBit();
        i_this->mWingCyl.OffAtSetBit();
        actor->speedF = 60.0f;
        actor->speed.y = 24.0f;
        if (i_this->m02D1 == 3) {
            actor->speedF = 20.0f;
            actor->speed.y = 22.0f;
        }
        i_this->mCountUpTimers[3] = 5000;
        i_this->mpMorf->setPlaySpeed(0.0f);
        i_this->mMode++;
    case MODE_UCHIWA_DOUSA_21:
        cLib_addCalc0(&actor->speedF, 1.0f, 3.0f);
        cLib_addCalc0(&actor->speed.y, 1.0f, 2.0f);
        for (s32 i = 0; i < 4; i++) {
            i_this->m0414[i].y = wing_trans_angle_dt[i].y;
            i_this->m0414[i].x = wing_trans_angle_dt[i].x;
            i_this->m0414[i].z = wing_trans_angle_dt[i].z;
        }
        i_this->mCountUpTimers[0] += 400;
        i_this->mCountUpTimers[1] += 400;
        i_this->mCountUpTimers[2] += 400;
        i_this->m042E = cM_ssin(i_this->mCountUpTimers[0]) * 4000.0f;
        i_this->m042C = cM_scos(i_this->mCountUpTimers[1]) * 4000.0f;
        i_this->m0430 = cM_scos(i_this->mCountUpTimers[2]) * 4000.0f;
        if (i_this->m02D1 != 3) {
            actor->shape_angle.z += i_this->mCountUpTimers[3];
            cLib_addCalcAngleS2(&i_this->mCountUpTimers[3], 0, 1, 0x100);
        }
        if ((actor->speed.y < 0.1f) && (actor->speedF < 0.1f)) {
            actor->speedF = 0.0f;
            i_this->mMode++;
        }
        break;
    case MODE_UCHIWA_DOUSA_22:
        actor->gravity = -0.08f;
        i_this->mCountUpTimers[0] += 400;
        i_this->mCountUpTimers[1] += 400;
        i_this->mCountUpTimers[2] += 400;
        i_this->m042E = cM_ssin(i_this->mCountUpTimers[0]) * 4000.0f;
        i_this->m042C = cM_scos(i_this->mCountUpTimers[1]) * 4000.0f;
        i_this->m0430 = cM_scos(i_this->mCountUpTimers[2]) * 4000.0f;
        if (actor->current.pos.y < i_this->mAcch.GetGroundH() + 150.0f) {
            actor->speed.y = 0.0f;
            actor->gravity = 0.0f;
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = MODE_DOUSA_0;
        }
    }
    cLib_addCalcAngleS2(&i_this->m043A, 0x2000, 1, 0x1000);
}

static void dummy() {
    static GXColor all_line_color_dt[] = {
        0xFF,
        0x00,
        0x00,
        0xFF, // 1
        0x00,
        0xFF,
        0x00,
        0xFF, // 2
        0x00,
        0x00,
        0xFF,
        0xFF, // 3
        0xFF,
        0x00,
        0xFF,
        0xFF // 4
    };
};

/* 000030FC-00003E54       .text action_totugeki__FP8gm_class */
static void action_totugeki(gm_class* i_this) {
    static f32 check_x[] = {-1.0f, 1.0f, 0.0f};
    static f32 check_y[] = {30.0f, 30.0f, 30.0f};
    static f32 check_z[] = {400.0f, 400.0f, 410.0f};

    s32 i;
    fopEn_enemy_c* actor = (fopEn_enemy_c*)&i_this->actor;
    f32 fVar1;
    f32 fVar2;
    cXyz local_ec;
    cXyz local_f8;
    cXyz local_104;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dBgS_LinChk local_e0;
    local_104.setall(0.0f);
    switch (i_this->mMode) {
    case MODE_TOTUGEKI_30:
        for (i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        for (i = 0; i < ARRAY_SIZE(i_this->m0360); i++) {
            i_this->m0360[i].setall(0.0f);
        }
        i_this->mAtackBrkAnm->setFrame(0.0f);
        i_this->m0324 = 2;
        i_this->m0322 = 0;
        for (i = 0; i < ARRAY_SIZE(i_this->m0360); i++) {
            i_this->m0360[i].setall(0.0f);
        }
        if (i_this->mCurrBckIdx != GM_BCK_FLY) {
            anm_init(i_this, GM_BCK_FLY, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        actor->speedF = 0.0f;
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m03C0.setall(0.0f);
        i_this->mMode++;
    case MODE_TOTUGEKI_31:
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x200);
        cLib_addCalcAngleS2(&actor->shape_angle.y, fopAcM_searchPlayerAngleY(actor), 1, 0x1000);
        fVar1 = 400.0f;
        fVar1 += player->current.pos.y;
        cLib_addCalc2(&actor->current.pos.y, fVar1, 1.0f, 20.0f);
        actor->current.angle.y = actor->shape_angle.y;
        if (std::fabsf(actor->current.pos.y - fVar1) < 2.0f) {
            i_this->mpMorf->setPlaySpeed(2.0f);
            i_this->mCountDownTimers[0] = 45;
            i_this->mMode++;
        }
        fopAcM_seStart(actor, JA_SE_CM_GM_FLYING, 0);
        break;
    case MODE_TOTUGEKI_32:
        fopAcM_seStart(actor, JA_SE_CM_GM_FLYING, 0);
        if (i_this->mCountDownTimers[0] > 0xF) {
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor);
        }
        if (fopAcM_searchPlayerDistance(actor) < 500.0f) {
            cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor) + 0x8000);
            local_ec.set(0.0f, 0.0f, 500.0f);
            MtxPosition(&local_ec, &local_f8);
            local_f8 += player->current.pos;
            if (std::fabsf(actor->current.pos.x - local_f8.x) > 20.0f) {
                cLib_addCalc2(&actor->current.pos.x, local_f8.x, 1.0f, 10.0f);
            }
            if (std::fabsf(actor->current.pos.z - local_f8.z) > 20.0f) {
                cLib_addCalc2(&actor->current.pos.z, local_f8.z, 1.0f, 10.0f);
            }
        }
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x1000);
        if (i_this->mCountDownTimers[0] != 0) {
            break;
        }
        if ((Line_check(i_this, player->current.pos)) || ((s16)cLib_distanceAngleS(actor->shape_angle.y, actor->current.angle.y) > 0x500)) {
            break;
        }
        actor->shape_angle.y = actor->current.angle.y;
        i_this->mMode++;
    case MODE_TOTUGEKI_33:
        i_this->m0322++;
        i_this->mpMorf->setPlaySpeed(1.0f);
        anm_init(i_this, GM_BCK_JETATACK, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mWingCyl.OnAtSetBit();
        i_this->mWingCyl.OnAtHitBit();
        i_this->mBodyCyl.SetCoVsGrp(cCcD_CoSPrm_VsPlayer_e);
        i_this->m0320 = 0;
        actor->shape_angle.x = 0;
        actor->speedF = REG8_F(10) + 30.0f;
        actor->gravity = REG8_F(11) + 1.0f;
        actor->speed.y = REG8_F(12) + -85.0f;
        i_this->m02DA = 0;
        i_this->m0348 = player->current.pos;
        i_this->m0348.y = player->current.pos.y + 350.0f;
        i_this->mMode++;
    case MODE_TOTUGEKI_34: {
        fopAcM_seStart(actor, JA_SE_CM_GM_JET, 0);
        actor->setBtNowFrame(1000.0f);
        i_this->m02DA++;
        if ((i_this->m02DA > (s16)REG8_F(7)) && (i_this->m02DA < (s16)(REG8_F(8) + 62.0f))) {
            actor->setBtNowFrame(5.0f);
        }
        if ((actor->speed.y > 0.0f) && (actor->current.pos.y + i_this->m03B4.y > i_this->m0348.y)) {
            i_this->mCountUpTimers[3] = 1;
        }
        if (i_this->mCountUpTimers[3] != 0) {
            cLib_addCalc0(&actor->gravity, 1.0f, 5.0f);
            cLib_addCalc0(&actor->speed.y, 1.0f, 5.0f);
        }
        if (actor->current.pos.y + i_this->m03B4.y < local_104.y) {
            actor->current.pos.y = local_104.y;
        }
        if (actor->current.pos.y < i_this->mAcch.GetGroundH() + 100.0f) {
            actor->current.pos.y = i_this->mAcch.GetGroundH() + 100.0f;
        }
        for (i = 0; i < ARRAY_SSIZE(i_this->m0384); i++) {
            i_this->m0384[i].setall(0.0f);
            cMtx_YrotS(*calc_mtx, actor->current.angle.y);
            local_ec.x = check_x[i];
            local_ec.y = check_y[i];
            local_ec.z = check_z[i];
            MtxPosition(&local_ec, &i_this->m0360[i]);
            i_this->m0360[i] += actor->current.pos;
            i_this->m0360[i] += i_this->m03B4;
            local_104 = actor->current.pos + i_this->m03B4;
            local_e0.Set(&local_104, &i_this->m0360[i], actor);
            if (dComIfG_Bgsp()->LineCross(&local_e0)) {
                i_this->m0384[i] = local_e0.GetCross();
            }
        }
        if (i_this->mAcch.ChkWallHit()) {
            actor->setBtNowFrame(1000.0f);
            i_this->mBodyCyl.SetCoVsGrp(cCcD_CoSPrm_VsGrpAll_e);
            i_this->mMode = MODE_TOTUGEKI_37;
            return;
        }
        f32 f2 = i_this->m0384[0].x;
        f32 f1 = 0.0f;
        if ((f2 != f1) || (i_this->m0384[0].z != f1) || (i_this->m0384[1].x != f1) || (i_this->m0384[1].z != f1)) {
            f1 = 0.0f;
            if (((f2 != f1) || (i_this->m0384[0].z != f1)) && ((f2 = i_this->m0384[1].x, f1 = 0.0f, f2 != f1) || (i_this->m0384[1].z != f1))) {
                actor->speedF = 0.0f;
                actor->gravity = 0.0f;
                actor->speed.y = 0.0f;
                actor->setBtNowFrame(1000.0f);
                i_this->mBodyCyl.SetCoVsGrp(cCcD_CoSPrm_VsGrpAll_e);
                i_this->mMode = MODE_KABEHARI_40;
                i_this->mAction = ACTION_KABEHARI;
            } else {
                local_ec = i_this->m0384[1] - actor->current.pos;
                f2 = i_this->m0384[0].x;
                f1 = 0.0f;
                if ((f2 != f1) || (i_this->m0384[0].z != f1)) {
                    local_ec = i_this->m0384[0] - actor->current.pos;
                }
                actor->shape_angle.y = cM_atan2s(local_ec.x, local_ec.z) + 0x4000;
                cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x1000);
            }
        }
        break;
    }
    case MODE_TOTUGEKI_37:
        for (i = 0; i < ARRAY_SIZE(i_this->m0360); i++) {
            i_this->m0360[i].setall(0.0f);
        }
        actor->gravity = 0.0f;
        actor->speed.y = 0.0f;
        i_this->mCountDownTimers[6] = 0;
        anm_init(i_this, GM_BCK_UMINIGE, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        actor->speedF = 20.0f;
        i_this->mMode++;
    case MODE_TOTUGEKI_38:
        fopAcM_seStart(actor, JA_SE_CM_GM_FLYING, 0);
        fVar1 = player->current.pos.y + 500.0f;
        cLib_addCalc2(&actor->current.pos.y, fVar1, 1.0f, 20.0f);
        fVar1 = i_this->m0354.x - (actor->current.pos.x + i_this->m03B4.x);
        fVar2 = i_this->m0354.z - (actor->current.pos.z + i_this->m03B4.z);
        actor->current.angle.y = cM_atan2s(fVar1, fVar2);
        cLib_addCalcAngleS2(&actor->shape_angle.y, fopAcM_searchPlayerAngleY(actor), 1, 0x1000);
        if ((((i_this->mpMorf->checkFrame(4.0f)) || (i_this->mpMorf->checkFrame(8.0f))) || (i_this->mpMorf->checkFrame(12.0f))) ||
            (i_this->mpMorf->checkFrame(16.0f)))
        {
            ks_set_rtn(i_this);
        }
        if (std::sqrtf(SQUARE(fVar1) + SQUARE(fVar2)) < 40.0f) {
            i_this->mMode = MODE_TOTUGEKI_30;
        }
    }
    cLib_addCalc0(&i_this->m03B4.x, 1.0f, 5.0f);
    cLib_addCalc0(&i_this->m03B4.y, 1.0f, 5.0f);
    cLib_addCalc0(&i_this->m03B4.z, 1.0f, 5.0f);
}

/* 00003E54-00004204       .text action_kabehari__FP8gm_class */
static void action_kabehari(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 fVar2;
    f32 fVar3;
    cXyz local_34;
    cXyz local_28;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    local_28.x = 0.0f;
    local_28.y = 0.0f;
    local_28.z = 0.0f;
    switch (i_this->mMode) {
    case MODE_KABEHARI_40:
        i_this->m0330 = 70.0f;
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        i_this->mWingCyl.OffAtSetBit();
        i_this->mWingCyl.OffAtSetBit();
        i_this->m0348 = player->current.pos;
        i_this->m0348.y = player->current.pos.y + 450.0f;
        i_this->m0320 = 0;
        i_this->mCountDownTimers[1] = 50;
        i_this->mMode++;
    case MODE_KABEHARI_41:
        cLib_addCalcAngleS2(&actor->shape_angle.x, -0x4000, 1, 0x200);
        fVar1 = actor->current.pos.x - local_28.x;
        fVar2 = actor->current.pos.y - i_this->m0348.y;
        fVar3 = actor->current.pos.z - local_28.z;
        fVar1 = std::sqrtf(SQUARE(fVar1) + SQUARE(fVar2) + SQUARE(fVar3));
        if (((fVar1 < 4.0f) || (i_this->mAcch.ChkWallHit())) || (i_this->mCountDownTimers[1] == 0)) {
            if (i_this->mCurrBckIdx != GM_BCK_TOMARU) {
                anm_init(i_this, GM_BCK_TOMARU, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            i_this->m0330 = 10.0f;
            actor->shape_angle.x = -0x4000;
            i_this->mMode = MODE_KABEHARI_42;
        }
        break;
    case MODE_KABEHARI_42:
        cLib_addCalcAngleS2(&i_this->m0320, -0x8000, 1, 0x500);
        if ((s16)cLib_distanceAngleS(i_this->m0320, -0x8000) < 0x100) {
            i_this->mCountDownTimers[0] = 10;
            i_this->mMode = MODE_KABEHARI_43;
        }
        break;
    case MODE_KABEHARI_43:
        if (cLib_addCalcAngleS2(&i_this->m0320, -0x8000, 1, 0x500), i_this->mCountDownTimers[0] == 0) {
            if ((i_this->m0322 <= 1) && ((i_this->m02CC & 7) != 7)) {
                actor->shape_angle.y = fopAcM_searchPlayerAngleY(actor);
                actor->current.angle.y = actor->shape_angle.y;
                i_this->mAction = ACTION_TOTUGEKI;
                i_this->mMode = MODE_TOTUGEKI_33;
            } else {
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_0;
            }
        }
    }
    if (i_this->mAction == ACTION_KABEHARI) {
        cMtx_YrotS(*calc_mtx, actor->current.angle.y + 0x8000);
        local_34.set(0.0f, 0.0f, 60.0f);
        MtxPosition(&local_34, &local_28);
        local_28 += i_this->m0384[2];
        cLib_addCalc2(&actor->current.pos.x, local_28.x, 1.0f, 10.0f);
        cLib_addCalc2(&actor->current.pos.y, i_this->m0348.y, 1.0f, 10.0f);
        cLib_addCalc2(&actor->current.pos.z, local_28.z, 1.0f, 10.0f);
        local_34 = i_this->m0384[0] - i_this->m0384[1];
        actor->current.angle.y = cM_atan2s(local_34.x, local_34.z) + 0x4000;
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x1000);
    }
}

/* 00004204-000046F0       .text action_fly_damage__FP8gm_class */
static void action_fly_damage(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 dVar6;

    switch (i_this->mMode) {
    case MODE_FLY_DAMAGE_50:
        i_this->mBodyCyl.SetCoVsGrp(cCcD_CoSPrm_VsGrpAll_e);
        if (i_this->m02D1 != 4) {
            i_this->mDamageBrkAnm->setFrame(0.0f);
            i_this->m0324 = 1;
        } else {
            i_this->mBodyGlowBrkAnm->setFrame(0.0f);
            i_this->m0324 = 0;
        }
        anm_init(i_this, GM_BCK_PAUSE, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        actor->speedF = 30.0f;
        i_this->m0320 = 0;
    case MODE_FLY_DAMAGE_52:
        i_this->mAtSph.OffAtSetBit();
        i_this->mAtSph.OffAtSetBit();
        i_this->mWingCyl.OffAtSetBit();
        i_this->mWingCyl.OffAtSetBit();
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
        dVar6 = 1.0f;
        if (cM_rnd() < 0.5f) {
            dVar6 = -1.0f;
        }
        i_this->mCountUpTimers[16] += (s16)(dVar6 * 10000.0f);
        dVar6 = 1.0f;
        if (cM_rnd() < 0.5f) {
            dVar6 = -1.0f;
        }
        i_this->mCountUpTimers[17] += (s16)(dVar6 * 10000.0f);
        dVar6 = 1.0f;
        if (cM_rnd() < 0.5f) {
            dVar6 = -1.0f;
        }
        i_this->mCountUpTimers[18] += (s16)(dVar6 * 2000.0f);
        i_this->mCountUpTimers[19] = 5000;
        i_this->mCountUpTimers[20] = 5000;
        i_this->mCountUpTimers[21] = 7000;
        actor->speed.setall(0.0f);
        actor->gravity = 0.0f;
        i_this->mMode = MODE_FLY_DAMAGE_51;
    case MODE_FLY_DAMAGE_51:
        for (s32 i = 0, j = 4; i < 4; i++, j += 3) {
            i_this->mCountUpTimers[j] += i_this->mCountUpTimers[16];
            i_this->mCountUpTimers[j + 1] += i_this->mCountUpTimers[17];
            i_this->mCountUpTimers[j + 2] += i_this->mCountUpTimers[18];
            i_this->m0414[i].y = cM_ssin(i_this->mCountUpTimers[j]) * 5000.0f;
            i_this->m0414[i].x = cM_scos(i_this->mCountUpTimers[j + 1]) * 5000.0f;
            i_this->m0414[i].z = cM_scos(i_this->mCountUpTimers[j + 2]) * 3000.0f;
        }
        i_this->mCountUpTimers[0] += i_this->mCountUpTimers[19];
        i_this->mCountUpTimers[1] += i_this->mCountUpTimers[20];
        i_this->mCountUpTimers[2] += i_this->mCountUpTimers[21];
        i_this->m042E = cM_ssin(i_this->mCountUpTimers[0]) * -3500.0f;
        i_this->m042C = cM_scos(i_this->mCountUpTimers[1]) * -3500.0f;
        i_this->m0430 = cM_scos(i_this->mCountUpTimers[2]) * -2000.0f;
        for (s32 i = 0; i < 6; i++) {
            cLib_addCalcAngleS2(&i_this->mCountUpTimers[i + 0x10], 0, 1, 0x50);
        }
        cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
        if (actor->speedF < 0.2f) {
            actor->speedF = 0.0f;
            i_this->mBodyGlowBrkAnm->setFrame(0.0f);
            i_this->m0324 = 0;
            if ((i_this->mCurrBckIdx == GM_BCK_PAUSE) && ((i_this->m02CC & 7) != 7)) {
                i_this->mAction = ACTION_TOTUGEKI;
                i_this->mMode = MODE_TOTUGEKI_37;
            } else {
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_0;
            }
        }
    }
    if (actor->current.pos.y < i_this->mAcch.GetGroundH() + 100.0f) {
        cLib_addCalc2(&actor->current.pos.y, i_this->mAcch.GetGroundH() + 100.0f, 1.0f, 3.0f);
    }
}

/* 000046F0-00005C78       .text action_ground_attack__FP8gm_class */
static void action_ground_attack(gm_class* i_this) {
    fopEn_enemy_c* actor = (fopEn_enemy_c*)&i_this->actor;
    f32 dVar13;
    f32 dVar12;
    cXyz local_54;
    cXyz local_60;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dVar13 = (player->current.pos.x - (actor->current.pos.x + i_this->m03B4.x));
    dVar12 = (player->current.pos.z - (actor->current.pos.z + i_this->m03B4.z));
    switch (i_this->mMode) {
    case MODE_GROUND_ATTACK_60:
        i_this->mBodyCyl.SetCoVsGrp(cCcD_CoSPrm_VsGrpAll_e);
        i_this->mAtSph.SetAtSpl(dCcG_At_Spl_UNK0);
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m0436 = 0;
        actor->speedF = 10.0f;
        i_this->m03B4.setall(0.0f);
        i_this->m03C0.setall(0.0f);
    case MODE_GROUND_ATTACK_61:
        i_this->mBodyGlowBrkAnm->setFrame(0.0f);
        i_this->m0324 = 0;
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        i_this->mAtSph.OffAtSetBit();
        i_this->mAtSph.OffAtSetBit();
        i_this->mWingCyl.OffAtSetBit();
        i_this->mWingCyl.OffAtSetBit();
        actor->initBt(REG8_F(4) + 120.0f, REG8_F(5) + 100.0f);
        actor->setBtAttackData(0.0f, 10.0f, REG8_F(6) + 800.0f, fopEn_enemy_c::OPENING_JUMP_PARRY);
        actor->setBtNowFrame(1000.0f);
        i_this->m0330 = 250.0f;
        if (actor->health <= 0) {
            if (i_this->m02CE != 0) {
                anm_init(i_this, GM_BCK_G_DEAD01, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mMode = MODE_GROUND_ATTACK_100;
                break;
            }
            i_this->mAction = ACTION_DEMO;
            i_this->mMode = MODE_DEMO_200;
            return;
        }
        actor->speed.setall(0.0f);
        actor->speed.y = 10.0f;
        actor->gravity = -3.0f;
        i_this->mMode = MODE_GROUND_ATTACK_62;
    case MODE_GROUND_ATTACK_62:
        actor->shape_angle.x += 0x100;
        if (actor->current.pos.y < i_this->mAcch.GetGroundH() + 80.0f) {
            if (actor->health <= 0) {
                anm_init(i_this, GM_BCK_G_DEAD02, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            } else {
                anm_init(i_this, GM_BCK_G_CHAKUCHI, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
            i_this->m0338.set(-20.0f, 60.0f, 100.0f);
            actor->speedF = 0.0f;
            i_this->mMode++;
        }
        break;
    case MODE_GROUND_ATTACK_63:
        if (i_this->mAcch.ChkGroundHit()) {
            fopAcM_seStart(actor, JA_SE_CM_GM_LANDING, 0);
            i_this->mMode = MODE_GROUND_ATTACK_70;
        }
        break;
    case MODE_GROUND_ATTACK_70:
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        anm_init(i_this, GM_BCK_G_WAIT, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        actor->speedF = 0.0f;
        i_this->mMode++;
    case MODE_GROUND_ATTACK_71:
        if (i_this->mpMorf->checkFrame(23.0f)) {
            i_this->mCountUpTimers[3]++;
            if (i_this->mCountUpTimers[3] > (s16)(REG8_S(5) + 1)) {
                i_this->mMode++;
            }
        }
        break;
    case MODE_GROUND_ATTACK_72:
        i_this->mCountUpTimers[7] = cM_rndF((u8)(fopAcM_GetID(actor) & 7) * 2.0f) + 20.0f;
        i_this->mCountUpTimers[2] = 0;
        cMtx_XrotS(*calc_mtx, (int)i_this->m043E.x);
        cMtx_ZrotM(*calc_mtx, i_this->m043E.z);
        local_54.set(0.0f, 100.0f, 0.0f);
        MtxPosition(&local_54, &local_60);
        local_60 += player->current.pos;
        if (!Line_check(i_this, local_60)) {
            actor->current.angle.y = cM_atan2s(dVar13, dVar12);
        } else {
            if (i_this->m02CE != 1) {
                if (i_this->mCurrBckIdx != GM_BCK_G_WAIT) {
                    anm_init(i_this, GM_BCK_G_WAIT, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                }
                break;
            }
            actor->speedF = 30.0f;
            i_this->m0326 = 0;
            i_this->m0326 = REG8_S(6) + 0x4000;
            if (cM_rnd() < 0.5f) {
                i_this->m0326 = -(REG8_S(6) + 0x4000);
            }
            actor->current.angle.y = cM_atan2s(dVar13, dVar12);
            actor->current.angle.y += i_this->m0326;
        }
        if (i_this->m02CE == 1) {
            i_this->m032C = 60.0f;
            i_this->m0330 = 70.0f;
        }
        anm_init(i_this, GM_BCK_G_WALK, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mMode++;
    case MODE_GROUND_ATTACK_73:
        fopAcM_seStart(actor, JA_SE_CM_GM_FOOTNOTE, 0);
        if ((s16)cLib_distanceAngleS(actor->current.angle.y, actor->shape_angle.y) < 0x100) {
            actor->speedF = 30.0f;
            i_this->mCountUpTimers[2]++;
            if (i_this->mCountUpTimers[2] > i_this->mCountUpTimers[7]) {
                i_this->mMode = MODE_GROUND_ATTACK_70;
                break;
            }
            if (i_this->m02CE != 1) {
                cMtx_YrotS(*calc_mtx, actor->current.angle.y);
                cMtx_XrotM(*calc_mtx, i_this->m043E.x);
                cMtx_ZrotM(*calc_mtx, i_this->m043E.z);
                local_54.set(0.0f, 100.0f, 200.0f);
                MtxPosition(&local_54, &local_60);
                local_60 += i_this->m03E4;
                if (Line_check(i_this, local_60)) {
                    i_this->mMode = MODE_GROUND_ATTACK_70;
                    break;
                }
            } else {
                actor->current.angle.y = cM_atan2s(dVar13, dVar12);
            }
        }
        if (std::sqrtf(SQUARE(dVar13) + SQUARE(dVar12)) > 400.0f) {
            break;
        }
        if (i_this->m02CE == 1) {
            cMtx_YrotS(*calc_mtx, actor->current.angle.y);
            cMtx_XrotM(*calc_mtx, i_this->m043E.x);
            cMtx_ZrotM(*calc_mtx, i_this->m043E.z);
            local_54.set(0.0f, 100.0f, 200.0f);
            MtxPosition(&local_54, &local_60);
            local_60 += i_this->m03E4;
            if (Line_check(i_this, local_60)) {
                i_this->mMode = MODE_GROUND_ATTACK_70;
                break;
            }
        }
        i_this->m02DA = 0;
        i_this->mMode++;
    case MODE_GROUND_ATTACK_74:
        anm_init(i_this, GM_BCK_G_ATACK01, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_GM_ATTACK, 0);
        i_this->m0324 = 2;
        actor->speedF = 0.0f;
        i_this->mMode++;
        break;
    case MODE_GROUND_ATTACK_75:
        fopAcM_seStart(actor, JA_SE_CM_GM_FOOTNOTE, 0);
        actor->current.angle.y =
            cM_atan2s(player->current.pos.x - (actor->current.pos.x + i_this->m03B4.x), player->current.pos.z - (actor->current.pos.z + i_this->m03B4.z));
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GM_BCK_G_ATACK02, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mAtSph.OnAtSetBit();
            i_this->mAtSph.OnAtHitBit();
            i_this->m0324 = 0;
            actor->speedF = 35.0f;
            actor->gravity = -3.0f;
            actor->speed.y = 20.0f;
            i_this->mMode++;
        }
        break;
    case MODE_GROUND_ATTACK_76:
        if ((i_this->mCountUpTimers[4] == 0) && (i_this->mAtSph.ChkAtShieldHit())) {
            i_this->mAtSph.OffAtSetBit();
            i_this->mAtSph.OffAtSetBit();
            actor->speedF = -35.0f;
            i_this->mCountUpTimers[4] = 1;
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, GM_BCK_G_ATACK03, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GM_BAS_G_ATACK03);
            i_this->mAtSph.OffAtSetBit();
            i_this->mAtSph.OffAtSetBit();
            i_this->mCountUpTimers[4] = 0;
            i_this->mMode++;
        }
        break;
    case MODE_GROUND_ATTACK_77:
        if (i_this->mAcch.ChkGroundHit()) {
            actor->speedF = 0.0f;
            i_this->mMode = MODE_GROUND_ATTACK_70;
        }
        break;
    case MODE_GROUND_ATTACK_80:
        i_this->mAtSph.OffAtSetBit();
        i_this->mAtSph.OffAtSetBit();
        if (i_this->m02D1 != 4) {
            fopAcM_monsSeStart(actor, JA_SE_CV_GM_DAMAGE, 0);
            i_this->mDamageBrkAnm->setFrame(0.0f);
            i_this->m0324 = 1;
            i_this->mCountDownTimers[5] = 0;
            anm_init(i_this, GM_BCK_G_DAMAGE, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            actor->speedF = 35.0f;
        } else {
            i_this->mCountDownTimers[5] = 45;
            actor->speedF = 0.0f;
            i_this->mBodyGlowBrkAnm->setFrame(0.0f);
            i_this->m0324 = 0;
        }
        actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
        if (i_this->m02D1 == 1) {
            actor->gravity = -3.0f;
            actor->speed.y = 20.0f;
        }
        i_this->mMode++;
        break;
    case MODE_GROUND_ATTACK_81:
        cLib_addCalc0(&actor->speedF, 1.0f, 1.5f);
        if (i_this->mCountDownTimers[5] == (s16)(REG8_S(7) + 0x2C)) {
            enemy_piyo_set(actor);
            fopAcM_seStart(actor, JA_SE_CM_MD_PIYO, 0);
        }
        if (((i_this->m02D1 == 4) || (!i_this->mpMorf->isStop())) && ((i_this->m02D1 != 4) || (i_this->mCountDownTimers[5] != 0))) {
            break;
        }
        anm_init(i_this, GM_BCK_G_WALK, 2.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, -1);
        i_this->mBodyGlowBrkAnm->setFrame(0.0f);
        i_this->m0324 = 0;
        i_this->mMode++;
        break;
    case MODE_GROUND_ATTACK_82:
        fopAcM_seStart(actor, JA_SE_CM_GM_FOOTNOTE, 0);
        actor->current.angle.y = cM_atan2s(dVar13, dVar12) + 0x8000;
        if ((s16)cLib_distanceAngleS(actor->current.angle.y, actor->shape_angle.y) < 0x100) {
            anm_init(i_this, GM_BCK_G_MACHINGUN, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mCountDownTimers[0] = 4;
            i_this->mCountUpTimers[5] = cM_atan2s(dVar13, dVar12) + 0x8000;
            i_this->mCountUpTimers[6] = 0x4000;
            i_this->mMode++;
        }
        break;
    case MODE_GROUND_ATTACK_83:
        if (i_this->mCountDownTimers[0] == 0) {
            actor->current.angle.y = i_this->mCountUpTimers[5] + i_this->mCountUpTimers[6];
            i_this->mCountDownTimers[0] = 4;
            i_this->mCountUpTimers[6] ^= 0x4000;
        }
        if (ks_set_rtn(i_this)) {
            i_this->mMode = MODE_GROUND_ATTACK_70;
        }
        break;
    case MODE_GROUND_ATTACK_84:
        anm_init(i_this, GM_BCK_G_UCHIWA, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
        actor->speedF = 20.0f;
        i_this->mAtSph.OffAtSetBit();
        i_this->mAtSph.OffAtSetBit();
        fopAcM_seStart(&i_this->actor, JA_SE_CM_GM_HIT_WIND, 0);
        fopAcM_monsSeStart(actor, JA_SE_CV_GM_HIT_WIND, 0);
        i_this->mMode++;
        break;
    case MODE_GROUND_ATTACK_85:
        cLib_addCalc0(&actor->speedF, 1.0f, 3.0f);
        if (i_this->mpMorf->isStop()) {
            i_this->mMode = MODE_GROUND_ATTACK_82;
        }
        break;
    case MODE_GROUND_ATTACK_90:
        i_this->m02CC = 0;
        anm_init(i_this, GM_BCK_G_HANE, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, GM_BAS_G_HANE);
        actor->speedF = 0.0f;
        i_this->mMode++;
        break;
    case MODE_GROUND_ATTACK_91:
        if (i_this->mpMorf->isStop()) {
            actor->speed.y = 0.0f;
            actor->gravity = 0.0f;
            i_this->m043E.setall(0);
            i_this->mAtSph.SetAtSpl(dCcG_At_Spl_UNK5);
            actor->initBt(REG8_F(4) + 200.0f, REG8_F(5) + 100.0f);
            actor->setBtAttackData(0.0f, 10.0f, REG8_F(6) + 880.0f, fopEn_enemy_c::OPENING_JUMP_PARRY);
            actor->setBtNowFrame(1000.0f);
            i_this->mAction = ACTION_TOTUGEKI;
            i_this->mMode = MODE_TOTUGEKI_37;
        }
        break;
    case MODE_GROUND_ATTACK_100:
        i_this->mCountDownTimers[5] = 0;
        actor->gravity = -3.0f;
        i_this->mBodyGlowBrkAnm->setFrame(0.0f);
        i_this->m0324 = 0;
        i_this->mStts.SetWeight(0xFF);
        fopAcM_monsSeStart(actor, JA_SE_CV_GM_DIE, 0);
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        if (i_this->m02D1 == 7) {
            actor->speedF = 0.0f;
            anm_init(i_this, GM_BCK_G_HAMMER, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        } else {
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            actor->speedF = 45.0f;
            actor->gravity = -3.0f;
            actor->speed.y = 45.0f;
#if VERSION > VERSION_DEMO
            i_this->mCountDownTimers[0] = 200;
#endif
            anm_init(i_this, GM_BCK_G_DEAD01, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        i_this->mMode++;
        break;
    case MODE_GROUND_ATTACK_101:
        if (i_this->m02D1 == 7) {
            if (i_this->mpMorf->isStop()) {
                fopAcM_createDisappear(actor, &actor->current.pos, 10, daDisItem_IBALL_e, actor->stealItemBitNo);
                fopAcM_delete(actor);
                fopAcM_onActor(actor);
                if ((i_this->mSwitch != 0xFF) && (i_this->m02D6 != 0)) {
                    dComIfGs_onSwitch(i_this->mSwitch, fopAcM_GetRoomNo(actor));
                }
            }
        } else {
            cLib_addCalc0(&actor->speedF, 1.0f, 1.5f);
            switch (i_this->mCountUpTimers[0]) {
            case 0:
#if VERSION == VERSION_DEMO
                if (i_this->mAcch.ChkGroundHit())
#else
                if ((i_this->mCountDownTimers[0] == 0) || (i_this->mAcch.ChkGroundHit()))
#endif
                {
                    fopAcM_seStart(actor, JA_SE_CM_GM_DIE_LANDING, 0);
                    anm_init(i_this, GM_BCK_G_DEAD02, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    i_this->mCountUpTimers[0] = 1;
                    actor->speedF = 0.0f;
                }
                break;
            case 1:
                if (i_this->mpMorf->isStop()) {
                    i_this->mCountUpTimers[0]++;
                    i_this->mDeadBrkAnm->setFrame(0.0f);
                    i_this->m0324 = 3;
                }
                break;
            case 2:
                if (i_this->mDeadBrkAnm->isStop()) {
                    i_this->mCountUpTimers[0]++;
                }
                break;
            case 3:
#if VERSION == VERSION_DEMO
                if (i_this->mAcch.ChkGroundHit())
#else
                if ((i_this->mCountDownTimers[0] == 0) || (i_this->mAcch.ChkGroundHit()))
#endif
                {
                    i_this->mCountUpTimers[1]++;
                    if (i_this->mCountUpTimers[1] > 0xF) {
                        fopAcM_createDisappear(actor, &actor->current.pos, 10, daDisItem_IBALL_e, actor->stealItemBitNo);
                        if ((i_this->mSwitch != 0xFF) && (i_this->m02D6 != 0)) {
                            dComIfGs_onSwitch(i_this->mSwitch, fopAcM_GetRoomNo(actor));
                        }
                        fopAcM_delete(actor);
                        fopAcM_onActor(actor);
                        i_this->mCountUpTimers[0]++;
                    }
                }
                break;
            }
        }
    }
    actor->setBtNowFrame(1000.0f);
    if ((i_this->mMode >= MODE_GROUND_ATTACK_74) && (i_this->mMode <= MODE_GROUND_ATTACK_77)) {
        i_this->m02DA++;
        if ((i_this->m02DA > (s16)REG8_F(7)) && (i_this->m02DA < (s16)(REG8_F(8) + 17.0f))) {
            actor->setBtNowFrame(5.0f);
        }
    }
    cLib_addCalcAngleS2(&i_this->m0320, 0, 1, 0x800);
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x800);
    if (((i_this->mMode != MODE_GROUND_ATTACK_81) && (i_this->mMode != MODE_GROUND_ATTACK_101)) && (i_this->mMode != MODE_GROUND_ATTACK_85)) {
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x800);
    }
    if (((i_this->mCurrBckIdx != GM_BCK_G_DEAD01) && (i_this->mCurrBckIdx != GM_BCK_G_DEAD02)) && (body_atari_check(i_this))) {
        i_this->mAction = ACTION_GROUND_ATTACK;
        if (i_this->m02D1 == 7) {
            actor->health = 0;
        }
        if (actor->health > 0) {
            i_this->mMode = MODE_GROUND_ATTACK_80;
            if (i_this->m02D1 == 3) {
                i_this->mMode = MODE_GROUND_ATTACK_84;
            }
        } else if (i_this->m02CE != 0) {
            i_this->mMode = MODE_GROUND_ATTACK_100;
        } else {
            i_this->mAction = ACTION_DEMO;
            i_this->mMode = MODE_DEMO_200;
        }
    } else {
        if ((((i_this->mMode == MODE_GROUND_ATTACK_71) || (i_this->mMode == MODE_GROUND_ATTACK_72)) || (i_this->mMode == MODE_GROUND_ATTACK_73)) &&
            (i_this->m02CE != 1 && (i_this->mCountDownTimers[2] == 0)))
        {
            i_this->mMode = MODE_GROUND_ATTACK_90;
        }
        if ((i_this->mAction == ACTION_GROUND_ATTACK) && (i_this->mAcch.ChkGroundHit())) {
            fopAcM_getGroundAngle(actor, &i_this->m043E);
        }
    }
}

/* 00005C78-00006A98       .text action_demo__FP8gm_class */
static void action_demo(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar11;
    cXyz local_e4;
    cXyz local_f0;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    dBgS_CamLinChk_NorWtr local_d8;
    switch (i_this->mMode) {
    case MODE_DEMO_200:
        for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountUpTimers); i++) {
            i_this->mCountUpTimers[i] = 0;
        }
        actor->attention_info.flags = 0;
        if (actor->health > 0) {
            actor->current.pos.set(-100.0f, 570.0f, -1350.0f);
            actor->current.angle.y = 0;
            actor->shape_angle.y = actor->current.angle.y;
            actor->shape_angle.x = -0x4000;
            i_this->m044C = 1;
            anm_init(i_this, GM_BCK_TOMARU, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m0320 = -0x8000;
        }
        i_this->mMode++;
    case MODE_DEMO_201:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            dComIfGp_event_onEventFlag(1);
            fopAcM_orderPotentialEvent(actor, dEvtType_OTHER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
        } else {
            player->changeOriginalDemo();
            player->changeDemoMode(daPy_demo_c::DEMO_N_WAIT_e);
            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);
            i_this->m0478 = 50.0f;
            if (actor->health > 0) {
                i_this->mMode++;
                actor->scale.setall(1.0f);
            } else {
                i_this->mBodyGlowBrkAnm->setFrame(0.0f);
                i_this->m0324 = 0;
                actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
                actor->speedF = 20.0f;
                actor->gravity = -3.0f;
                actor->speed.y = 45.0f;
                player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
                anm_init(i_this, GM_BCK_G_DEAD01, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mMode = MODE_DEMO_220;
            }
        }
        break;
    case MODE_DEMO_202:
        local_f0.x = REG12_F(5) + 73.0f;
        local_f0.y = player->current.pos.y;
        local_f0.z = REG12_F(6) + 1284.0f;
        player->setPlayerPosAndAngle(&local_f0, -0x8000);
        i_this->m045C.x = REG12_F(7) + 74.0f;
        i_this->m045C.y = REG12_F(8) + 107.0f;
        i_this->m045C.z = REG12_F(9) + 1095.0f;
        i_this->m0450.x = REG12_F(10) + 71.0f;
        i_this->m0450.y = REG12_F(11) + 124.0f;
        i_this->m0450.z = REG12_F(12) + 800.0f;
        i_this->mCountDownTimers[0] = 10;
        i_this->mMode++;
    case MODE_DEMO_203:
        if (i_this->mCountDownTimers[0] == 0) {
            player->changeDemoMode(daPy_demo_c::DEMO_N_WALK_e);
            i_this->m044C = 2;
            player->mDemo.setMoveAngle(-0x8000);
            actor->current.pos.x = 100.0f;
            actor->current.pos.y = REG12_F(15) + 450.0f;
            actor->current.pos.z = 1150.0f;
            mDoAud_bgmAllMute(30);
            i_this->mCountDownTimers[0] = 0x3c;
            i_this->mMode = MODE_DEMO_205;
        }
        break;
    case MODE_DEMO_205:
        if (i_this->mCountDownTimers[0] == 0) {
            player->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
            i_this->mCountDownTimers[0] = 50;
            i_this->mMode++;
        }
        break;
    case MODE_DEMO_206:
        if (i_this->mCountDownTimers[0] == 0) {
            player->changeDemoMode(daPy_demo_c::DEMO_TBACK_e);
            i_this->mCountDownTimers[0] = 80;
            actor->current.pos.set(100.0f, 570.0f, 1350.0f);
            i_this->mMode++;
        }
        break;
    case MODE_DEMO_207:
        dVar11 = std::fabsf(i_this->m045C.x - 80.0f) * 0.1f;
        cLib_addCalc2(&i_this->m045C.x, REG12_F(1) + 80.0f, 1.0f, dVar11);
        dVar11 = std::fabsf(i_this->m045C.y - 605.0f) * 0.1f;
        cLib_addCalc2(&i_this->m045C.y, REG12_F(2) + 605.0f, 1.0f, dVar11);
        dVar11 = std::fabsf(i_this->m045C.z - 877.0f) * 0.1f;
        cLib_addCalc2(&i_this->m045C.z, REG12_F(3) + 877.0f, 1.0f, dVar11);
        dVar11 = std::fabsf(i_this->m0450.x - 76.0f) * 0.1f;
        cLib_addCalc2(&i_this->m0450.x, REG12_F(4) + 76.0f, 1.0f, dVar11);
        dVar11 = std::fabsf(i_this->m0450.y - 621.0f) * 0.1f;
        cLib_addCalc2(&i_this->m0450.y, REG12_F(5) + 621.0f, 1.0f, dVar11);
        dVar11 = std::fabsf(i_this->m0450.z - 582.0f) * 0.1f;
        cLib_addCalc2(&i_this->m0450.z, REG12_F(6) + 582.0f, 1.0f, dVar11);
        if (i_this->mCountDownTimers[0] == 0) {
            anm_init(i_this, GM_BCK_JETATACK, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            actor->current.angle.y =
                cM_atan2s(i_this->m0354.x - (actor->current.pos.x + i_this->m03B4.x), i_this->m0354.z - (actor->current.pos.z + i_this->m03B4.z));
            i_this->m0320 = 0;
            actor->shape_angle.x = 0x4000;
            actor->shape_angle.y += -0x8000;
            i_this->mCountDownTimers[0] = 47;
            actor->speedF = 22.0f;
            actor->gravity = 1.0f;
            actor->speed.y = -65.0f;
            player->changeDemoMode(daPy_demo_c::DEMO_UNK00_e);
            i_this->mMode++;
        }
        break;
    case MODE_DEMO_208:
        fopAcM_seStart(actor, JA_SE_CM_GM_JET, 0);
        if (actor->current.pos.y < player->current.pos.y + 220.0f) {
            actor->gravity = 0.0f;
            actor->speed.y = 0.0f;
            cLib_addCalc2(&actor->current.pos.y, player->current.pos.y + 220.0f, 1.0f, 50.0f);
        }
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x1000);
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, REG12_F(16) + 1280.0f);
        dVar11 = REG12_F(17) + 50.0f;
        cLib_addCalc2(&i_this->m045C.x, actor->current.pos.x, 1.0f, dVar11);
        cLib_addCalc2(&i_this->m045C.y, actor->current.pos.y + REG12_F(10), 1.0f, dVar11);
        cLib_addCalc2(&i_this->m045C.z, actor->current.pos.z, 1.0f, dVar11);
        cLib_addCalc2(&i_this->m0450.x, REG12_F(7) + 67.0f, 1.0f, dVar11);
        cLib_addCalc2(&i_this->m0450.y, REG12_F(8) + 95.0f, 1.0f, dVar11);
        cLib_addCalc2(&i_this->m0450.z, REG12_F(9) + 1.0f, 1.0f, dVar11);
        if (i_this->mCountDownTimers[0] == 0) {
            dComIfGp_getVibration().StopQuake(0x20);
            camera->mCamera.Reset(i_this->m045C, i_this->m0450);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
            dComIfGp_event_onEventFlag(8);
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
            actor->current.angle.x = 0;
            i_this->m044C = 0;
            mDoAud_subBgmStart(JA_BGM_MBOSS);
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
            i_this->mAction = ACTION_DOUSA;
            i_this->mMode = MODE_DOUSA_0;
        }
        break;
    case MODE_DEMO_220:
        mDoAud_subBgmStop();
#if VERSION > VERSION_DEMO
        i_this->mCountDownTimers[0] = 200;
#endif
        i_this->mMode++;
    case MODE_DEMO_221: {
        f32 f0 = actor->speedF;
        f32 f1 = 0.0f;
#if VERSION == VERSION_DEMO
        if ((f0 != f1) && (i_this->mAcch.ChkGroundHit()))
#else
        if ((f0 != f1) && ((i_this->mCountDownTimers[0] == 0) || (i_this->mAcch.ChkGroundHit())))
#endif
        {
            if (i_this->mCurrBckIdx != GM_BCK_G_DEAD02) {
                anm_init(i_this, GM_BCK_G_DEAD02, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
            actor->speedF = 0.0f;
        }
        player->setPlayerPosAndAngle(&player->current.pos, (int)(s16)(fopAcM_searchPlayerAngleY(actor) + 0x8000));
        if (((REG8_S(8) == 0) && (f0 = actor->speedF, f1 = 0.0f, f0 == f1)) && (i_this->mCurrBckIdx == GM_BCK_G_DEAD02)) {
            if (i_this->mpMorf->isStop()) {
                i_this->mDeadBrkAnm->setFrame(0.0f);
                i_this->m0324 = 3;
                i_this->mMode++;
            }
        }
        break;
    }
    case MODE_DEMO_222:
        if (i_this->mDeadBrkAnm->isStop()) {
            fopAcM_createDisappear(actor, &actor->current.pos, 10, daDisItem_IBALL_e, actor->stealItemBitNo);
            actor->scale.setall(0.0f);
            i_this->mCountDownTimers[0] = 100;
            i_this->mMode++;
        }
        break;
    case MODE_DEMO_223:
        if (i_this->mCountDownTimers[0] == 0) {
            dComIfGp_getVibration().StopQuake(0x20);
            camera->mCamera.Reset(i_this->m045C, i_this->m0450);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
            player->cancelOriginalDemo();
            dComIfGp_event_onEventFlag(8);
            if ((i_this->mSwitch != 0xFF) && (i_this->m02D6 != 0)) {
                dComIfGs_onSwitch(i_this->mSwitch, fopAcM_GetRoomNo(actor));
            }
            fopAcM_delete(actor);
            fopAcM_onActor(actor);
        }
    }
    if (i_this->mMode >= MODE_DEMO_221) {
        i_this->m045C = actor->current.pos;
        mDoMtx_YrotS(*calc_mtx, fopAcM_searchActorAngleY(player, actor));
        local_e4.set(0.0f, 0.0f, 40.0f);
        MtxPosition(&local_e4, &local_f0);
        local_f0 += player->current.pos;
        i_this->m0450.x = local_f0.x;
        i_this->m0450.y = local_f0.y + 200.0f;
        i_this->m0450.z = local_f0.z;
    }
    if ((i_this->mMode >= MODE_DEMO_203) && (i_this->mMode != MODE_DEMO_220)) {
        camera->mCamera.Set(i_this->m045C, i_this->m0450, i_this->m0478, 0);
    }
}

/* 00006A98-00007770       .text daGM_Execute__FP8gm_class */
static BOOL daGM_Execute(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;
    cXyz local_2c;
    cXyz local_38;

    if (i_this->m02CD == 0) {
        fopAcM_setGbaName(actor, dItem_BOOMERANG_e, 9, 0x26);
        if (i_this->m044C != 1) {
            if (!(i_this->m02CC & 4)) {
                switch (i_this->m02D3) {
                case 0:
                    i_this->m0B78 = dComIfGp_particle_set(dPa_name::ID_AK_SN_GMRINPUN00, &actor->current.pos, &actor->shape_angle);
                    if (i_this->m0B78 != NULL) {
                        i_this->m02D3++;
                    }
                    break;
                case 1:
                    if ((i_this->m0B78 != NULL) && (i_this->mAction == ACTION_FLY_DAMAGE)) {
                        i_this->m02DE = 0;
                        i_this->m02D3++;
                    }
                    break;
                case 2:
                    if (i_this->m0B78 != NULL) {
                        i_this->m0B78->setRate(80.0f);
                        i_this->m0B78->setRandomDirectionSpeed(80.0f);
                        i_this->m0B78->setGlobalPrmColor(0xFF, 0x00, 0x00);
                        i_this->m02D3++;
                    }
                    break;
                case 3:
                    if (i_this->m0B78 != NULL) {
                        i_this->m0B78->setRate(3.0f);
                        i_this->m0B78->setRandomDirectionSpeed(0.0f);
                        i_this->m02D3++;
                    }
                    break;
                case 4:
                    if (i_this->m0B78 != NULL) {
                        i_this->m02DE += 0x11;
                        if (i_this->m02DE > 0xFF) {
                            i_this->m02DE = 0xFF;
                            i_this->m02D3 = 1;
                        }
                        i_this->m0B78->setGlobalPrmColor(0xFF, i_this->m02DE, i_this->m02DE);
                    }
                    break;
                }
                if (i_this->m0B78 != NULL) {
                    i_this->m0B78->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x11));
                }
            } else {
                if (i_this->m0B78 != NULL) {
                    i_this->m0B78->becomeInvalidEmitter();
                    i_this->m02D3 = 0;
                    i_this->m0B78 = NULL;
                }
            }
            if (!(i_this->m02CC & 8)) {
                switch (i_this->m02D4) {
                case 0:
                    i_this->m0B7C = dComIfGp_particle_set(dPa_name::ID_AK_SN_GMRINPUN00, &actor->current.pos, &actor->shape_angle);
                    if (i_this->m0B7C != NULL) {
                        i_this->m02D4++;
                    }
                    break;
                case 1:
                    if ((i_this->m0B7C != NULL) && (i_this->mAction == ACTION_FLY_DAMAGE)) {
                        i_this->m02E0 = 0;
                        i_this->m02D4++;
                    }
                    break;
                case 2:
                    if (i_this->m0B7C != NULL) {
                        i_this->m0B7C->setRate(80.0f);
                        i_this->m0B7C->setRandomDirectionSpeed(80.0f);
                        i_this->m0B7C->setGlobalPrmColor(0xFF, 0x00, 0x00);
                        i_this->m02D4++;
                    }
                    break;
                case 3:
                    if (i_this->m0B7C != NULL) {
                        i_this->m0B7C->setRate(3.0f);
                        i_this->m0B7C->setRandomDirectionSpeed(0.0f);
                        i_this->m02D4++;
                    }
                    break;
                case 4:
                    if (i_this->m0B7C != NULL) {
                        i_this->m02E0 += 0x11;
                        if (i_this->m02E0 > 0xFF) {
                            i_this->m02E0 = 0xFF;
                            i_this->m02D4 = 1;
                        }
                        i_this->m0B7C->setGlobalPrmColor(0xFF, i_this->m02E0, i_this->m02E0);
                    }
                    break;
                }
                if (i_this->m0B7C != NULL) {
                    i_this->m0B7C->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x13));
                    JGeometry::TVec3<s16> rot(0x471c, -0x1555, 0x0000);
                    i_this->m0B7C->setEmitterRotation(rot);
                    JGeometry::TVec3<f32> scale(40.0f, 0.0f, -30.0f);
                    i_this->m0B7C->setEmitterTranslation(scale);
                }
            } else if (i_this->m0B7C != NULL) {
                i_this->m0B7C->becomeInvalidEmitter();
                i_this->m02D4 = 0;
                i_this->m0B7C = NULL;
            }
        }
        if (((i_this->mCountDownTimers[6] != 0) || (i_this->mMode == MODE_TOTUGEKI_34)) || (i_this->mMode == MODE_DEMO_208)) {
            switch (i_this->m02D5) {
            case 0:
                i_this->m0B80 = dComIfGp_particle_set(dPa_name::ID_AK_SN_GMJETATTACKSMOKE00, &actor->current.pos, &actor->shape_angle);
                if (i_this->m0B80 != NULL) {
                    i_this->m02D5++;
                }
                break;
            case 1:
                i_this->m0B84 = dComIfGp_particle_set(dPa_name::ID_AK_SN_GMJETATTACKFIRE00, &actor->current.pos, &actor->shape_angle);
                if (i_this->m0B84 != NULL) {
                    i_this->m02D5++;
                }
            }
            if (i_this->mMode == MODE_TOTUGEKI_34) {
                i_this->mCountDownTimers[6] = 45;
            }
            if (i_this->m0B80 != NULL) {
                i_this->m0B80->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x03));
            }
            if (i_this->m0B84 != NULL) {
                i_this->m0B84->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0x03));
            }
        } else {
            if (i_this->m0B80 != NULL) {
                i_this->m0B80->becomeInvalidEmitter();
                i_this->m02D5 = 0;
                i_this->m0B80 = NULL;
            }
            if (i_this->m0B84 != NULL) {
                i_this->m0B84->becomeInvalidEmitter();
                i_this->m02D5 = 0;
                i_this->m0B84 = NULL;
            }
        }
        if ((i_this->m02CD == 0) && (enemy_ice(&i_this->mEnemyIce))) {
            i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
            i_this->mpMorf->calc();
            actor->attention_info.position = i_this->m03E4;
            actor->attention_info.position.y += 100.0f;
            actor->eyePos = i_this->m03E4;
            return TRUE;
        }
    }
    for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountDownTimers); i++) {
        if (i_this->mCountDownTimers[i] != 0) {
            i_this->mCountDownTimers[i]--;
        }
    }
    switch (i_this->mAction) {
    case ACTION_DOUSA:
        action_dousa(i_this);
        break;
    case ACTION_HANE_RAKKA:
        action_hane_rakka(i_this);
        break;
    case ACTION_UCHIWA_DOUSA:
        action_uchiwa_dousa(i_this);
        break;
    case ACTION_TOTUGEKI:
        action_totugeki(i_this);
        break;
    case ACTION_KABEHARI:
        action_kabehari(i_this);
        break;
    case ACTION_FLY_DAMAGE:
        action_fly_damage(i_this);
        break;
    case ACTION_GROUND_ATTACK:
        action_ground_attack(i_this);
        break;
    case ACTION_DEMO:
        action_demo(i_this);
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    local_20.x = 0.0f;
    local_20.y = 0.0f;
    local_20.z = actor->speedF;
    MtxPosition(&local_20, &local_2c);
    actor->speed.x = local_2c.x;
    actor->speed.z = local_2c.z;
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -100.0f) {
        actor->speed.y = -100.0f;
    }
    if (i_this->m02CD == 0) {
        if (i_this->mAction != ACTION_DEMO) {
            if (i_this->mAction != ACTION_GROUND_ATTACK) {
                body_atari_check(i_this);
            }
            if ((i_this->mAction != ACTION_FLY_DAMAGE) && (i_this->mAction != ACTION_UCHIWA_DOUSA)) {
                wing_ret_set(i_this);
            }
            if (i_this->mAction != ACTION_UCHIWA_DOUSA) {
                cLib_addCalcAngleS2(&actor->shape_angle.z, i_this->m0436, 1, 0x100);
                cLib_addCalcAngleS2(&i_this->m0436, 0, 1, 0x100);
            }
        }
        if (i_this->mCountDownTimers[5] == 0) {
            s8 roomNo = fopAcM_GetRoomNo(actor);
            u32 mtrlSndId = i_this->mAcch.ChkGroundHit() ? dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd) : 0;
            i_this->mpMorf->play(&actor->eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
        }
        switch (i_this->m0324) {
        case 1:
            i_this->mDamageBrkAnm->play();
            break;
        case 2:
            i_this->mAtackBrkAnm->play();
            break;
        case 3:
            i_this->mDeadBrkAnm->play();
            break;
        default:
            i_this->mBodyGlowBrkAnm->play();
            break;
        }
        local_38 = actor->current.pos + i_this->m03B4;
        if (i_this->mAction != ACTION_DEMO) {
            if (i_this->mAction == ACTION_GROUND_ATTACK) {
                actor->attention_info.position = i_this->m03E4;
                actor->attention_info.position.y += 50.0f;
                actor->eyePos = i_this->m03E4;
                local_38 = i_this->m03F0;
            } else {
                actor->attention_info.position = local_38;
                actor->attention_info.position.y += 100.0f;
                actor->eyePos = local_38;
            }
            local_38.y += i_this->m0338.x;
            if (i_this->mMode != MODE_TOTUGEKI_34) {
                i_this->mBodyCyl.SetC(local_38);
                i_this->mBodyCyl.SetH(i_this->m0338.y);
                i_this->mBodyCyl.SetR(i_this->m0338.z);
                dComIfG_Ccsp()->Set(&i_this->mBodyCyl);
            } else {
                local_38 = actor->current.pos + i_this->m03B4;
                local_38.y -= 10.0f;
                i_this->mBodyCyl.SetC(local_38);
                i_this->mBodyCyl.SetH(60.0f);
                i_this->mBodyCyl.SetR(375.0f);
                dComIfG_Ccsp()->Set(&i_this->mBodyCyl);
            }
            local_38 = actor->current.pos + i_this->m03B4;
            local_38.y -= 40.0f;
            i_this->mWingCyl.SetC(local_38);
            i_this->mWingCyl.SetH(60.0f);
            i_this->mWingCyl.SetR(185.0f);
            dComIfG_Ccsp()->Set(&i_this->mWingCyl);
            dComIfG_Ccsp()->SetMass(&i_this->mWingCyl, 3);
            i_this->mAtSph.SetC(i_this->m03A8);
            i_this->mAtSph.SetR(55.0f);
            dComIfG_Ccsp()->Set(&i_this->mAtSph);
        }
        if (((i_this->m044C == 0) && ((i_this->m02CC & 0xF) != 0xF)) && (i_this->mMode != MODE_TOTUGEKI_34)) {
            local_38 = actor->current.pos + i_this->m03B4;
            i_this->mCountUpTimers[22] += 1000;
            i_this->m0408.x = cM_scos(i_this->mCountUpTimers[22]) * 300.0f;
            i_this->m0408.z = cM_scos(i_this->mCountUpTimers[22]) * 300.0f;
            local_38.x += i_this->m0408.x;
            local_38.y = i_this->mAcch.GetGroundH();
            local_38.z += i_this->m0408.z;
            i_this->mWindCyl.SetC(local_38);
            i_this->mWindCyl.SetH(60.0f);
            i_this->mWindCyl.SetR(200.0f);
            dComIfG_Ccsp()->Set(&i_this->mWindCyl);
            if ((i_this->mAction != ACTION_FLY_DAMAGE) && (i_this->mAction != ACTION_UCHIWA_DOUSA)) {
                dComIfG_Ccsp()->SetMass(&i_this->mWindCyl, 3);
            }
        }
    }
    if ((i_this->mMode != MODE_TOTUGEKI_34) && (i_this->mAction != ACTION_DEMO)) {
        fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
    } else {
        fopAcM_posMove(actor, NULL);
    }
    BG_check(i_this);
    draw_SUB(i_this);
    return TRUE;
}

/* 00007770-00007778       .text daGM_IsDelete__FP8gm_class */
static BOOL daGM_IsDelete(gm_class*) {
    return TRUE;
}

/* 00007778-000078C4       .text daGM_Delete__FP8gm_class */
static BOOL daGM_Delete(gm_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    dComIfG_resDeleteDemo(&i_this->mPhase, "GM");
#if VERSION > VERSION_DEMO
    if (actor->heap != NULL) {
        i_this->mpMorf->stopZelAnime();
    }
#endif
    enemy_fire_remove(&i_this->mEnemyFire);
    if (actor->health == -0x80) {
        if ((i_this->mSwitch != 0xFF) && (i_this->m02D6 != 0)) {
            dComIfGs_onSwitch(i_this->mSwitch, fopAcM_GetRoomNo(actor));
        }
        fopAcM_onActor(actor);
    }
    if (i_this->m0B78 != NULL) {
        i_this->m0B78->becomeInvalidEmitter();
        i_this->m0B78 = NULL;
    }
    if (i_this->m0B7C != NULL) {
        i_this->m0B7C->becomeInvalidEmitter();
        i_this->m0B7C = NULL;
    }
    if (i_this->m0B80 != NULL) {
        i_this->m0B80->becomeInvalidEmitter();
        i_this->m0B80 = NULL;
    }
    if (i_this->m0B84 != NULL) {
        i_this->m0B84->becomeInvalidEmitter();
        i_this->m0B84 = NULL;
    }
    return TRUE;
}

/* 000078C4-00007E74       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    gm_class* i_this = (gm_class*)a_this;
    J3DModelData* pJVar3;
    J3DModel* pJVar4;
    J3DAnmTevRegKey* pbrk;
    int ret;

    if (i_this->m02CD == 0) {
        // Body
        i_this->mpMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("GM", GM_BDL_GM), NULL, NULL, NULL, J3DFrameCtrl::EMode_RESET, 1.0f, 0, -1, 1, NULL, 0x80000, 0x37441422
        );
    } else {
        switch (i_this->m02CC) {
        case 1:
        case 2:
            // Bottom of the wing
            i_this->mpMorf = new mDoExt_McaMorf(
                (J3DModelData*)dComIfG_getObjectRes("GM", GM_BDL_HANESL), NULL, NULL, NULL, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203
            );
            break;
        case 3:
        case 4:
            // Top of the wing
            i_this->mpMorf = new mDoExt_McaMorf(
                (J3DModelData*)dComIfG_getObjectRes("GM", GM_BDL_HANEUL), NULL, NULL, NULL, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203
            );
        }
    }
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    if (i_this->m02CD == 0) {
        i_this->mpMorf->getModel()->setUserArea((u32)i_this);
        for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
            i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }
    pJVar4 = i_this->mpMorf->getModel();
    pJVar3 = pJVar4->getModelData();
    if (i_this->m02CD == 0) {
        i_this->mBodyGlowBrkAnm = new mDoExt_brkAnm();
        if (i_this->mBodyGlowBrkAnm == NULL) {
            return FALSE;
        }
        pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("GM", GM_BRK_GM);
        ret = i_this->mBodyGlowBrkAnm->init(pJVar4->getModelData(), pbrk, true, J3DFrameCtrl::EMode_LOOP);
        if (!ret) {
            return FALSE;
        }
        i_this->mAtackBrkAnm = new mDoExt_brkAnm();
        if (i_this->mAtackBrkAnm == NULL) {
            return FALSE;
        }
        pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("GM", GM_BRK_ATACK);
        ret = i_this->mAtackBrkAnm->init(pJVar4->getModelData(), pbrk, true, J3DFrameCtrl::EMode_LOOP);
        if (!ret) {
            return FALSE;
        }
        i_this->mDamageBrkAnm = new mDoExt_brkAnm();
        if (i_this->mDamageBrkAnm == NULL) {
            return FALSE;
        }
        pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("GM", GM_BRK_DAMAGE);
        ret = i_this->mDamageBrkAnm->init(pJVar4->getModelData(), pbrk, true, J3DFrameCtrl::EMode_NONE);
        if (!ret) {
            return FALSE;
        }
        i_this->mDeadBrkAnm = new mDoExt_brkAnm();
        if (i_this->mDeadBrkAnm == NULL) {
            return FALSE;
        }
        pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("GM", GM_BRK_DEAD);
        ret = i_this->mDeadBrkAnm->init(pJVar4->getModelData(), pbrk, true, J3DFrameCtrl::EMode_NONE);
        if (!ret) {
            return FALSE;
        }
        ret = i_this->mInvisibleModel.create(i_this->mpMorf->getModel());
        if (!ret) {
            return FALSE;
        }
    }
    i_this->m0444 = mDoExt_J3DModel__create(pJVar3, 0x20000, 0x11020203);
    if (i_this->m0444 == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00007EBC-0000842C       .text daGM_Create__FP10fopAc_ac_c */
static cPhs_State daGM_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph weapon_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK2,
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
    static dCcD_SrcCyl body_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
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
    static dCcD_SrcCyl wing_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK6,
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
    static dCcD_SrcCyl wind_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_WIND,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e | cCcD_AtSPrm_NoTgHitInfSet_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsOther_e,
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

    gm_class* i_this = (gm_class*)a_this;
    fopEn_enemy_c* actor = (fopEn_enemy_c*)&i_this->actor;
#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(a_this, gm_class);
#endif

    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "GM");
    if (res == cPhs_COMPLEATE_e) {
#if VERSION == VERSION_DEMO
        fopAcM_SetupActor(a_this, gm_class);
#endif
        i_this->m02CC = (fopAcM_GetParam(i_this) >> 0x00);
        i_this->m02CD = (fopAcM_GetParam(i_this) >> 0x08);
        i_this->m02CE = (fopAcM_GetParam(i_this) >> 0x10);
        i_this->mSwitch = (fopAcM_GetParam(i_this) >> 0x18);
        if (i_this->m02CC == 0xFF) {
            i_this->m02CC = 0;
        }
        if (i_this->m02CD == 0xFF) {
            i_this->m02CD = 0;
        }
        if (i_this->m02CE == 0xFF) {
            i_this->m02CE = 0;
        }
        if (i_this->m02CD == 0) {
            i_this->m02D6 = a_this->current.angle.z;
            a_this->current.angle.z = 0;
            a_this->shape_angle.z = 0;
            a_this->current.angle.x = 0;
            a_this->shape_angle.x = 0;
        }
        if ((i_this->mSwitch != 0xFF) && (dComIfGs_isSwitch(i_this->mSwitch, dComIfGp_roomControl_getStayNo()))) {
            return cPhs_ERROR_e;
        }
        if (REG8_S(9) != 0) {
            i_this->m02CE = REG8_S(9) - 1;
        }
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x7400)) {
            return cPhs_ERROR_e;
        }
        a_this->max_health = 12;
        a_this->health = 12;
        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(a_this, -200.0f, -150.0f, -200.0f, 200.0f, 250.0f, 150.0f);
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mStts.Init(100, 1, a_this);
        i_this->m0328 = 0.0f;
        i_this->m0434 = a_this->current.angle.y;
        i_this->m0354 = a_this->current.pos;
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("gmos", 0);
        if (i_this->m02CD == 0) {
            i_this->mBodyCyl.Set(body_co_cyl_src);
            i_this->mBodyCyl.SetStts(&i_this->mStts);
            i_this->mAtSph.Set(weapon_co_sph_src);
            i_this->mAtSph.SetStts(&i_this->mStts);
            i_this->mWingCyl.Set(wing_co_cyl_src);
            i_this->mWingCyl.SetStts(&i_this->mStts);
            i_this->mWindCyl.Set(wind_co_cyl_src);
            i_this->mWindCyl.SetStts(&i_this->mStts);
            i_this->mAtSph.OffAtSetBit();
            i_this->mAtSph.OffAtSetBit();
            i_this->mWingCyl.OffAtSetBit();
            i_this->mWingCyl.OffAtSetBit();
            a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
            if (i_this->m02CE == 1) {
                actor->initBt(REG8_F(4) + 120.0f, REG8_F(5) + 100.0f);
                actor->setBtAttackData(0.0f, 10.0f, REG8_F(6) + 800.0f, fopEn_enemy_c::OPENING_JUMP_PARRY);
                a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 3;
                a_this->stealItemLeft = 1;
            } else {
                actor->initBt(REG8_F(4) + 200.0f, REG8_F(5) + 100.0f);
                actor->setBtAttackData(0.0f, 10.0f, REG8_F(6) + 880.0f, fopEn_enemy_c::OPENING_JUMP_PARRY);
                a_this->stealItemLeft = 3;
                i_this->mAtSph.SetAtSpl(dCcG_At_Spl_UNK5);
            }
            actor->setBtNowFrame(1000.0f);
            a_this->scale.setall(0.0f);
            i_this->mAction = ACTION_DEMO;
            i_this->mMode = MODE_DEMO_200;
            i_this->mEnemyIce.mpActor = a_this;
            i_this->mEnemyIce.mWallRadius = 40.0f;
            i_this->mEnemyIce.mCylHeight = 40.0f;
            i_this->mEnemyIce.m1B0 = 1;
            i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
            i_this->mEnemyFire.mpActor = a_this;
            for (s32 i = 0; i < ARRAY_SSIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
                static s8 fire_j[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                static f32 fire_sc[] = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};

                i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
                i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
            }
            draw_SUB(i_this);
            if (i_this->m02CE == 0) {
                fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
                fopAcM_OnStatus(a_this, fopAcStts_BOSS_e);
                fopAcM_OffStatus(a_this, fopAcStts_SHOWMAP_e);
            } else if (i_this->m02CE == 2) {
                a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("gmos_f", 0);
                a_this->scale.setall(1.0f);
                i_this->mAction = ACTION_DOUSA;
                i_this->mMode = MODE_DOUSA_0;
            } else if (i_this->m02CE == 1) {
                a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("gmos_g", 0);
                i_this->m032C = 60.0f;
                i_this->m0330 = 70.0f;
                a_this->scale.setall(1.0f);
                i_this->m02CC = 0xF;
                a_this->max_health = 2;
                a_this->health = 2;
                i_this->mAction = ACTION_GROUND_ATTACK;
                i_this->mMode = MODE_GROUND_ATTACK_60;
            }
        } else {
            a_this->attention_info.flags = 0;
            i_this->m0330 = 100.0f;
            if ((i_this->m02CC == 2) || (i_this->m02CC == 4)) {
                a_this->shape_angle.y += -0x8000;
            }
            i_this->mAction = ACTION_HANE_RAKKA;
            i_this->mMode = MODE_HANE_RAKKA_10;
        }
    }
    return res;
}

static actor_method_class l_daGM_Method = {
    (process_method_func)daGM_Create,
    (process_method_func)daGM_Delete,
    (process_method_func)daGM_Execute,
    (process_method_func)daGM_IsDelete,
    (process_method_func)daGM_Draw,
};

actor_process_profile_definition g_profile_GM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_GM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(gm_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_GM,
    /* Actor SubMtd */ &l_daGM_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
