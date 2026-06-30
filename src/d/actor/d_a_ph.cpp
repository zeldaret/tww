/**
 * d_a_ph.cpp
 * Enemy - Peahat/Seahat
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_ph.h"
#include "d/actor/d_a_coming2.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_sea.h"
#include "d/actor/d_a_ship.h"
#include "d/d_jnt_hit.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "res/Object/ph.h"
#include "res/Object/sh.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "f_op/f_op_kankyo_mng.h"
#include "m_Do/m_Do_lib.h"

enum Actor_Type { ACTOR_TYPE_PEAHAT = 0, ACTOR_TYPE_SEAHAT = 1, ACTOR_TYPE_DEFAULT = 0xFF };

enum Action {
    ACTION_FLY_MOVE = 0,
    ACTION_HANE_MOVE = 1,
    ACTION_BUNRI_MOVE = 2,
    ACITON_FUJYOU_MOVE = 3,
    ACTION_DAMAGE_DEAD_MOVE = 4,
    ACTION_WIND_MOVE = 5,
    ACTION_WATER_MOVE = 6
};

enum Mode {
    MODE_FLY_MOVE_0 = 0,
    MODE_FLY_MOVE_1 = 1,
    MODE_FLY_MOVE_2 = 2,
    MODE_FLY_MOVE_3 = 3,
    MODE_FLY_MOVE_4 = 4,
    MODE_FLY_MOVE_5 = 5,
    MODE_FLY_MOVE_6 = 6,
    MODE_FLY_MOVE_7 = 7,
    MODE_FLY_MOVE_8 = 8,
    MODE_HANE_MOVE_10 = 10,
    MODE_HANE_MOVE_11 = 11,
    MODE_BUNRI_MOVE_20 = 20,
    MODE_BUNRI_MOVE_21 = 21,
    MODE_BUNRI_MOVE_22 = 22,
    MODE_BUNRI_MOVE_23 = 23,
    MODE_BUNRI_MOVE_24 = 24,
    MODE_BUNRI_MOVE_25 = 25,
    MODE_BUNRI_MOVE_26 = 26,
    MODE_FUJYOU_MOVE_30 = 30,
    MODE_FUJYOU_MOVE_31 = 31,
    MODE_FUJYOU_MOVE_32 = 32,
    MODE_FUJYOU_MOVE_33 = 33,
    MODE_FUJYOU_MOVE_34 = 34,
    MODE_FUJYOU_MOVE_35 = 35,
    MODE_FUJYOU_MOVE_36 = 36,
    MODE_DAMAGE_DEAD_MOVE_40 = 40,
    MODE_DAMAGE_DEAD_MOVE_41 = 41,
    MODE_DAMAGE_DEAD_MOVE_42 = 42,
    MODE_DAMAGE_DEAD_MOVE_43 = 43,
    MODE_DAMAGE_DEAD_MOVE_44 = 44,
    MODE_DAMAGE_DEAD_MOVE_45 = 45,
    MODE_DAMAGE_DEAD_MOVE_46 = 46,
    MODE_DAMAGE_DEAD_MOVE_47 = 47,
    MODE_DAMAGE_DEAD_MOVE_48 = 48,
    MODE_DAMAGE_DEAD_MOVE_49 = 49,
    MODE_WIND_MOVE_50 = 50,
    MODE_WIND_MOVE_51 = 51,
    MODE_WIND_MOVE_52 = 52,
    MODE_WIND_MOVE_53 = 53,
    MODE_WIND_MOVE_54 = 54,
    MODE_WATER_MOVE_60 = 60,
    MODE_WATER_MOVE_61 = 61,
    MODE_WATER_MOVE_70 = 70,
    MODE_WATER_MOVE_71 = 71
};

/* 00000078-00000158       .text nodeCallBack_UP__FP7J3DNodei */
static BOOL nodeCallBack_UP(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();
        ph_class* i_this = (ph_class*)model->getUserArea();
        s32 jntNo = joint->getJntNo();
        if (i_this != NULL) {
            u8 var_r0;
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            var_r0 = 0;
            if (jntNo == 0) {
                cXyz offset;
                offset.x = 0.0f;
                offset.y = -80.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m02D8);
                var_r0 = 1;
            }
            if (var_r0 != 0) {
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 00000158-0000025C       .text nodeCallBack_DW__FP7J3DNodei */
static BOOL nodeCallBack_DW(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();
        ph_class* i_this = (ph_class*)model->getUserArea();
        s32 jntNo = joint->getJntNo();
        if (i_this != NULL) {
            u8 var_r0;
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            var_r0 = 0;
            cXyz offset;
            if (jntNo == 1) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m02C0);
                var_r0 = 1;
            }
            if (jntNo == 0) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &i_this->m02CC);
                var_r0 = 1;
            }
            if (var_r0 != 0) {
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 0000025C-000003FC       .text daPH_Draw__FP8ph_class */
static BOOL daPH_Draw(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    cXyz local_28;

    J3DModel* bodyModel = i_this->mpBodyMorf->getModel();
    J3DModel* propellerModel = i_this->mpPropellerMorf->getModel();
    g_env_light.setLightTevColorType(bodyModel, &actor->tevStr);
    g_env_light.setLightTevColorType(propellerModel, &actor->tevStr);
    if (i_this->mType == ACTOR_TYPE_SEAHAT) {
        dSnap_RegistFig(DSNAP_TYPE_PH_SEAHAT, actor, actor->attention_info.position, actor->shape_angle.y, 1.0f, 1.0f, 1.0f);
    } else {
        dSnap_RegistFig(DSNAP_TYPE_PH_PEAHAT, actor, actor->attention_info.position, actor->shape_angle.y, 1.0f, 1.0f, 1.0f);
    }
    if (i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(i_this->mpBodyMorf, -1, &i_this->mBodyInvisibleModel);
        if ((i_this->m02FC.x) && (!i_this->m037C)) {
            dMat_control_c::iceEntryDL(i_this->mpPropellerMorf, -1, &i_this->mPropellerInvisibleModel);
        }
        return TRUE;
    }
    i_this->mpBodyMorf->entryDL();
    i_this->mpPropellerMorf->entryDL();
    local_28 = actor->current.pos;
    local_28 += i_this->mHaniCheck;
    if (!fopAcM_checkCarryNow(actor)) {
        fVar1 = 36.0f;
        if (i_this->mType == ACTOR_TYPE_SEAHAT) {
            fVar1 = 70.0f;
        }
        dComIfGd_setSimpleShadow2(&local_28, i_this->mAcch.GetGroundH(), fVar1, i_this->mAcch.m_gnd, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }
    return TRUE;
}

/* 000003FC-000007C0       .text anm_init__FP8ph_classifUcfii */
static void anm_init(ph_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx, int param_7) {
#if VERSION < VERSION_USA
    i_this->mCurrBckIdx = bckFileIdx;
#endif
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        if (param_7 == 0) {
#if VERSION >= VERSION_USA
            i_this->mCurrBckIdx = bckFileIdx;
#endif
            if (soundFileIdx >= 0) {
                i_this->mpPropellerMorf->setAnm(
                    (J3DAnmTransform*)dComIfG_getObjectRes("PH", bckFileIdx),
                    loopMode,
                    morf,
                    speed,
                    0.0f,
                    -1.0f,
                    dComIfG_getObjectRes("PH", soundFileIdx)
                );
            } else {
                i_this->mpPropellerMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("PH", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
            }
        } else if (soundFileIdx >= 0) {
            i_this->mpBodyMorf->setAnm(
                (J3DAnmTransform*)dComIfG_getObjectRes("PH", bckFileIdx),
                loopMode,
                morf,
                speed,
                0.0f,
                -1.0f,
                dComIfG_getObjectRes("PH", soundFileIdx)
            );
        } else {
            i_this->mpBodyMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("PH", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    } else if (param_7 == 0) {
        if (soundFileIdx >= 0) {
            i_this->mpPropellerMorf->setAnm(
                (J3DAnmTransform*)dComIfG_getObjectRes("SH", bckFileIdx),
                loopMode,
                morf,
                speed,
                0.0f,
                -1.0f,
                dComIfG_getObjectRes("SH", soundFileIdx)
            );
        } else {
            i_this->mpPropellerMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("SH", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    } else if (soundFileIdx >= 0) {
        i_this->mpBodyMorf
            ->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("SH", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("SH", soundFileIdx));
    } else {
        i_this->mpBodyMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("SH", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000007C0-0000097C       .text puropera_sound__FP8ph_class */
static void puropera_sound(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    bool var_r30 = false;
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        if (((i_this->m0354 & 1) == 0) && (abs(i_this->m033A) < 0x1000)) {
            var_r30 = true;
            i_this->m0354 |= 1;
        }
        if (((i_this->m0354 & 2) == 0) && ((s16)cLib_distanceAngleS(i_this->m033A, 0x6000) < 0x1000)) {
            var_r30 = true;
            i_this->m0354 |= 2;
        }
        if (((i_this->m0354 & 4) == 0) && ((s16)cLib_distanceAngleS(i_this->m033A, -0x4000) < 0x1000)) {
            var_r30 = true;
            i_this->m0354 |= 4;
        }
        if (var_r30) {
            fopAcM_seStart(actor, JA_SE_CM_PH_FLY, 0);
            if ((i_this->m0354 & 7) == 7) {
                i_this->m0354 = 0;
            }
        }
    } else {
        u32 uVar3 = i_this->m0348 / 81.0f;
        if (uVar3 > 100) {
            uVar3 = 100;
        }
        fopAcM_seStart(actor, JA_SE_CM_SH_PROPELLER, uVar3);
    }
}

/* 0000097C-00000AE4       .text zaisitu_sound__FP8ph_classP8cCcD_Obj */
static BOOL zaisitu_sound(ph_class* i_this, cCcD_Obj* hitObj) {
    fopAc_ac_c* actor = &i_this->actor;

    if (hitObj != NULL) {
        if ((hitObj->ChkAtType(AT_TYPE_SWORD)) || (hitObj->ChkAtType(AT_TYPE_UNK800)) || (hitObj->ChkAtType(AT_TYPE_MACHETE)) ||
            (hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD)) || (hitObj->ChkAtType(AT_TYPE_MOBLIN_SPEAR)))
        {
            fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x42);
        } else if ((hitObj->ChkAtType(AT_TYPE_BOOMERANG)) || (hitObj->ChkAtType(AT_TYPE_BOKO_STICK)) || (hitObj->ChkAtType(AT_TYPE_STALFOS_MACE))) {
            fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x42);
        } else {
            if (hitObj->ChkAtType(AT_TYPE_WIND)) {
                return TRUE;
            }
            fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
        }
    }
    return FALSE;
}

/* 00000AE4-00000B4C       .text puropera_kaiten__FP8ph_class */
static void puropera_kaiten(ph_class* i_this) {
    i_this->m033A += i_this->m0348;
    cLib_addCalcAngleS2(&i_this->m0348, i_this->m034A, 1, i_this->m034C);
    cLib_addCalcAngleS2(&i_this->m034C, 0x100, 1, 0x10);
    puropera_sound(i_this);
}

/* 00000B4C-00000D2C       .text fuwafuwa_set__FP8ph_class */
static void fuwafuwa_set(ph_class* i_this) {
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        i_this->mFuwafuwaValue[0] += 700;
        i_this->mFuwafuwaValue[1] += 200;
        i_this->mFuwafuwaValue[2] += 200;
        i_this->mHaniTarget.y = cM_ssin(i_this->mFuwafuwaValue[0]) * 30.0f;
        i_this->mHaniTarget.x = cM_scos(i_this->mFuwafuwaValue[1]) * 200.0f;
        i_this->mHaniTarget.z = cM_scos(i_this->mFuwafuwaValue[2]) * 200.0f;
    } else {
        i_this->mFuwafuwaValue[0] += (s16)(REG12_F(0) + 350.0f);
        i_this->mFuwafuwaValue[1] += (s16)(REG12_F(1) + 100.0f);
        i_this->mFuwafuwaValue[2] += (s16)(REG12_F(1) + 100.0f);
        i_this->mHaniTarget.y = cM_ssin(i_this->mFuwafuwaValue[0]) * (REG12_F(2) + 30.0f);
        i_this->mHaniTarget.x = cM_scos(i_this->mFuwafuwaValue[1]) * (REG12_F(3) + 1000.0f);
        i_this->mHaniTarget.z = cM_scos(i_this->mFuwafuwaValue[2]) * (REG12_F(3) + 1000.0f);
    }
}

/* 00000D2C-000011F4       .text fly_angle_set__FP8ph_classUc */
static void fly_angle_set(ph_class* i_this, u8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    Vec pos;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 angleY = actor->current.angle.y;
    s16 angleZ = actor->current.angle.z;
    s16 maxSpeed = 0x200;
    switch (param_2) {
        case 1:
            pos.x = actor->current.pos.x - player->current.pos.x;
            pos.y = actor->current.pos.y - (player->current.pos.y + i_this->m0378);
            pos.z = actor->current.pos.z - player->current.pos.z;
            cLib_addCalcAngleS2(&actor->current.angle.x, cM_atan2s(pos.y, std::sqrtf(SQUARE(pos.x) + SQUARE(pos.z))), 1, 0x200);
            // Fall-through
        case 3:
            angleY = fopAcM_searchPlayerAngleY(actor);
            cLib_addCalcAngleS2(&actor->current.angle.y, angleY, 1, 0x500);
            break;
        case 2:
            pos.x = actor->current.pos.x - player->current.pos.x;
            pos.y = actor->current.pos.y - (player->current.pos.y + i_this->m0378);
            pos.z = actor->current.pos.z - player->current.pos.z;
            cLib_addCalcAngleS2(&actor->current.angle.x, cM_atan2s(pos.y, std::sqrtf(SQUARE(pos.x) + SQUARE(pos.z))), 1, 0x200);
            pos.y = actor->current.pos.y - player->current.pos.y;
            cLib_addCalcAngleS2(&actor->shape_angle.x, cM_atan2s(pos.y, std::sqrtf(SQUARE(pos.x) + SQUARE(pos.z))), 1, 0x200);
            maxSpeed = 0x500;
            break;
        case 4:
            pos.x = actor->current.pos.x - player->current.pos.x;
            pos.y = actor->current.pos.y - (player->current.pos.y + i_this->m0378);
            pos.z = actor->current.pos.z - player->current.pos.z;
            cLib_addCalcAngleS2(&actor->current.angle.x, (s16)cM_atan2s(pos.y, std::sqrtf(SQUARE(pos.x) + SQUARE(pos.z))), 1, 0x200);
            cLib_addCalcAngleS2(&actor->shape_angle.x, actor->current.angle.x, 1, 0x200);
            i_this->mFuwafuwaValue[4] += 3000;
            angleZ = cM_ssin(i_this->mFuwafuwaValue[4]) * 7000.0f;
            break;
    }
    if ((param_2 <= 1) || (param_2 == 3)) {
        if (i_this->mType == ACTOR_TYPE_PEAHAT) {
            i_this->mFuwafuwaValue[3] += 800;
            cLib_addCalcAngleS2(&actor->shape_angle.x, cM_ssin(i_this->mFuwafuwaValue[3]) * 4000.0f, 1, 0x200);
        } else {
            i_this->mFuwafuwaValue[3] += 900;
            cLib_addCalcAngleS2(&actor->shape_angle.x, cM_ssin(i_this->mFuwafuwaValue[3]) * 4000.0f, 1, 0x200);
        }
    }
    if (param_2 != 4) {
        cLib_addCalcAngleS2(&actor->shape_angle.y, angleY, 1, maxSpeed);
    }
    cLib_addCalcAngleS2(&actor->shape_angle.z, angleZ, 1, 0x200);
}

/* 000011F4-00001A10       .text body_atari_check__FP8ph_class */
static BOOL body_atari_check(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 sVar1;
    bool bVar3;
    cCcD_Obj* hitObj;
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;
    CcAtInfo atInfo;

    atInfo.pParticlePos = NULL;
    i_this->mStts.Move();
    if (i_this->mCountDownTimers[4] != 0) {
        return FALSE;
    }
    if (i_this->mBodySph.ChkTgHit()) {
        i_this->mHitType = 0;
        hitObj = i_this->mBodySph.GetTgHitObj();
        if (hitObj == NULL) {
            return FALSE;
        }
        i_this->mCountDownTimers[4] = 8;
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        bVar3 = false;
        switch (hitObj->GetAtType()) {
            case AT_TYPE_GRAPPLING_HOOK:
#if VERSION > VERSION_DEMO
                bVar3 = true;
#endif
                if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                    if ((i_this->m02FC.x) && (!i_this->m037C)) {
                        actor->stealItemLeft = i_this->m0344;
#if VERSION >= VERSION_USA
                        if (i_this->mCurrBckIdx != dRes_INDEX_PH_BCK_PFLY_e) {
                            anm_init(i_this, dRes_INDEX_PH_BCK_PFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 0);
                        }
#endif
                        if (actor->stealItemLeft > 0) {
                            sVar1 = actor->health;
                            actor->health = 10;
                            atInfo.mpObj = i_this->mBodySph.GetTgHitObj();
                            cc_at_check(actor, &atInfo);
                            i_this->m0343 = i_this->m0343 + 1;
                            actor->health = sVar1;
                            if (i_this->m0344 > 0) {
                                i_this->m0344--;
                            }
                        }
                        dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &actor->attention_info.position);
#if VERSION == VERSION_DEMO
                        bVar3 = true;
#endif
                        i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                        i_this->mAtCyl.ClrAtSet();
                        i_this->mAction = ACTION_HANE_MOVE;
                        i_this->mMode = MODE_HANE_MOVE_10;
                    } else {
                        actor->stealItemLeft = 0;
#if VERSION > VERSION_DEMO
                        bVar3 = false;
#endif
                        i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                        i_this->mMode = MODE_DAMAGE_DEAD_MOVE_40;
                    }
                }
                break;
            case AT_TYPE_SWORD:
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
                    i_this->mHitType = 3;
                }
                i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_40;
                break;
            case AT_TYPE_WIND:
                i_this->mHitType = 2;
                bVar3 = true;
                i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mAtCyl.ClrAtSet();
                i_this->mAction = ACTION_WIND_MOVE;
                i_this->mMode = MODE_WIND_MOVE_50;
                break;
            case AT_TYPE_FIRE:
            case AT_TYPE_FIRE_ARROW:
                i_this->mBodyEnemyFire.mFireDuration = 100;
                if (i_this->m02FC.x) {
                    i_this->mPropellerEnemyFire.mFireDuration = 100;
                }
                i_this->mHitType = 1;
                i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_43;
                break;
            case AT_TYPE_LIGHT_ARROW:
                actor->current.pos += i_this->mHaniCheck;
                i_this->mHaniCheck.setall(0.0f);
                i_this->mHaniTarget.setall(0.0f);
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mParticleScale = 1.0f;
                if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                    i_this->mEnemyIce.mParticleScale = 4.0f;
                }
                i_this->mEnemyIce.mYOffset = 0.0f;
                if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                    i_this->mEnemyIce.mYOffset = 100.0f;
                }
                actor->attention_info.flags = 0;
                if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PH_DIE, 0);
                } else {
                    fopAcM_monsSeStart(actor, JA_SE_CV_SH_DIE, 0);
                }
                i_this->mHitType = 1;
                i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_43;
                break;
            case AT_TYPE_ICE_ARROW:
                bVar3 = true;
                actor->current.pos += i_this->mHaniCheck;
                i_this->mHaniCheck.setall(0.0f);
                i_this->mHaniTarget.setall(0.0f);
                enemy_fire_remove(&i_this->mBodyEnemyFire);
                enemy_fire_remove(&i_this->mPropellerEnemyFire);
                i_this->mEnemyIce.mParticleScale = i_this->m039C + 1.0f;
                i_this->m0342 = 1;
                i_this->mEnemyIce.mFreezeDuration = 200;
                i_this->mHitType = 1;
                // Fall-through
            case AT_TYPE_NORMAL_ARROW:
                i_this->mHitType = 1;
                i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_43;
                break;
            case AT_TYPE_BOMB:
                i_this->mHitType = 8;
                i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_43;
                break;
            case AT_TYPE_SKULL_HAMMER:
                i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_47;
                i_this->mHitType = 6;
                if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                    i_this->mHitType = 7;
                    i_this->mMode = MODE_DAMAGE_DEAD_MOVE_43;
                }
                break;
            case AT_TYPE_HOOKSHOT:
                if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                    i_this->mHitType = 9;
                    bVar3 = true;
                    if ((i_this->m02FC.x) && (!i_this->m037C)) {
                        dScnPly_ply_c::setPauseTimer(2);
                        i_this->mAction = ACTION_BUNRI_MOVE;
                        i_this->mMode = MODE_BUNRI_MOVE_20;
                    }
                } else {
                    i_this->mHitType = 1;
                    i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                    i_this->mMode = MODE_DAMAGE_DEAD_MOVE_43;
                }
                break;
            case AT_TYPE_BOOMERANG:
                if (((i_this->mAction != ACTION_BUNRI_MOVE) && (i_this->m02FC.x)) && (!i_this->m037C)) {
                    i_this->mHitType = 4;
                    mDoAud_onEnemyDamage();
                    dScnPly_ply_c::setPauseTimer(2);
                    i_this->mAction = ACTION_BUNRI_MOVE;
                    i_this->mMode = MODE_BUNRI_MOVE_20;
                    return TRUE;
                }
                i_this->mHitType = 5;
                // Fall-through
            default:
                i_this->mAction = ACTION_DAMAGE_DEAD_MOVE;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_40;
        }
        if (!bVar3) {
            fopAc_ac_c* const player_actor = dComIfGp_getPlayer(0);
            local_40 = *i_this->mBodySph.GetTgHitPosP();
            atInfo.mpObj = i_this->mBodySph.GetTgHitObj();
            cc_at_check(actor, &atInfo);
            if ((i_this->mHitType == 3) || (i_this->mHitType == 6) || (i_this->mHitType == 7) || (actor->health <= 0)) {
                local_58.setall(1.0f);
                local_4c.setall(2.0f);
                if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                    local_4c.setall(REG8_F(9) + 3.25f);
                    local_58.setall(1.25f);
                }
                dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, &local_40, &player_actor->shape_angle, &local_58);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &local_40, &player_actor->shape_angle, &local_4c);
            } else {
                dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, &local_40, &player_actor->shape_angle);
            }
            return TRUE;
        }
    }
    return FALSE;
}

/* 00001A10-00001C18       .text hajiki_check__FP8ph_class */
static BOOL hajiki_check(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    bool bVar1;
    cCcD_Obj* hitObj;
    cXyz local_28;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bVar1 = false;
    if (i_this->mTgCyl.ChkTgHit()) {
        hitObj = i_this->mTgCyl.GetTgHitObj();
        if (zaisitu_sound(i_this, hitObj)) {
            i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.ClrAtSet();
            i_this->mAction = ACTION_WIND_MOVE;
            i_this->mMode = MODE_WIND_MOVE_50;
            return TRUE;
        }
        if ((hitObj != NULL) && (hitObj->ChkAtType(AT_TYPE_SWORD))) {
            bVar1 = true;
        }
    }
    if (i_this->mTgCyl.ChkAtShieldHit()) {
        local_28 = *i_this->mTgCyl.GetAtHitPosP();
        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &local_28);
        fopAcM_seStart(actor, JA_SE_OBJ_COL_SWS_NMTLP, 0);
        bVar1 = true;
    }
    if (i_this->mAtCyl.ChkAtShieldHit()) {
        bVar1 = true;
    }
    if (bVar1) {
        actor->current.angle.y = cM_atan2s(
            (actor->current.pos.x + i_this->mHaniCheck.x) - player->current.pos.x,
            (actor->current.pos.z + i_this->mHaniCheck.z) - player->current.pos.z
        );
        if (i_this->mType == ACTOR_TYPE_PEAHAT) {
            actor->speedF = 28.0f;
        } else {
            actor->speedF = 48.0f;
        }
        i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mAtCyl.ClrAtSet();
        i_this->mAction = ACTION_HANE_MOVE;
        i_this->mMode = MODE_HANE_MOVE_10;
        return TRUE;
    }
    return FALSE;
}

/* 00001C18-00001C90       .text ph_wall_hit_check__FP8ph_class */
static BOOL ph_wall_hit_check(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->mAcch.ChkWallHit()) {
        actor->current.angle.y += 0x4000;
        if (i_this->mType == ACTOR_TYPE_PEAHAT) {
            actor->speedF = 28.0f;
        } else {
            actor->speedF = 48.0f;
        }
        i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mAtCyl.ClrAtSet();
        i_this->mAction = ACTION_HANE_MOVE;
        i_this->mMode = MODE_HANE_MOVE_10;
        return TRUE;
    }
    return FALSE;
}

/* 00001C90-00001E10       .text ph_hani_check__FP8ph_classffUc */
static BOOL ph_hani_check(ph_class* i_this, f32 maxDist2D, f32 maxDist3D, u8 param_4) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 x;
    f32 y;
    f32 z;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (param_4 == 0) {
        x = (actor->current.pos.x + i_this->mHaniCheck.x) - player->current.pos.x;
        y = (actor->current.pos.y + i_this->mHaniCheck.y) - player->current.pos.y;
        z = (actor->current.pos.z + i_this->mHaniCheck.z) - player->current.pos.z;
    } else {
        x = i_this->m032C.x - player->current.pos.x;
        y = i_this->m032C.y - player->current.pos.y;
        z = i_this->m032C.z - player->current.pos.z;
    }
    if (std::sqrtf(SQUARE(x) + SQUARE(z)) < maxDist2D) {
        if (std::sqrtf(SQUARE(y)) < maxDist3D) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00001E10-00001F0C       .text shibuki_set__FP8ph_class4cXyzf */
static void shibuki_set(ph_class* i_this, cXyz param_2, f32 param_3) {
    fopAc_ac_c* actor = &i_this->actor;
    param_3 += i_this->m039C;
    fopKyM_createWpillar(&param_2, param_3, 0.5f, 0);
    if (i_this->mAction == ACTION_BUNRI_MOVE) {
        fopAcM_seStart(actor, JA_SE_CM_SH_LANDING_SEA, 0);
    } else if ((i_this->m02FC.x) && (!i_this->m037C)) {
        fopAcM_seStart(actor, JA_SE_CM_SH_RIPPLE, 0);
    }
}

/* 00001F0C-00002318       .text sea_water_check__FP8ph_classUc */
static s32 sea_water_check(ph_class* i_this, u8 param_2) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 dVar6;
    f32 fVar7;
    cXyz local_3c;

    s32 iVar4 = 0;
    u8 bVar2 = 0;
    i_this->m05BC = actor->current.pos;
#if VERSION > VERSION_DEMO
    i_this->m05BC.y = i_this->m032C.y;
#endif
    i_this->m05BC += i_this->mHaniCheck;
    if (((param_2 == 0) || (param_2 == 2)) && (!actor->gravity)) {
        actor->gravity = -5.0f;
    }
    if (daSea_ChkArea(actor->current.pos.x, actor->current.pos.z)) {
        dVar6 = daSea_calcWave(actor->current.pos.x, actor->current.pos.z);
        if (fopAcM_searchPlayerDistance(actor) > 50000.0f) {
            dVar6 = dComIfGp_getPlayer(0)->current.pos.y + 200.0f;
        }
        i_this->m05BC.y = dVar6;
        fVar7 = 100.0f;
        if (i_this->mMode == MODE_FLY_MOVE_3) {
            fVar7 = 300.0f;
        }
        if (actor->current.pos.y + i_this->mHaniCheck.y < (dVar6 + fVar7)) {
            if ((param_2 == 0) || (param_2 == 2)) {
                actor->gravity = 0.0f;
                i_this->mHaniTarget.y = 0.0f;
                if (param_2 == 0) {
                    actor->speed.setall(0.0f);
                }
                i_this->m0370 += 1000;
                fVar1 = ((cM_ssin(i_this->m0370) * 2.0f) + 2.0f);
                cLib_addCalc2(&actor->current.pos.y, dVar6 - fVar1, 1.0f, i_this->m0398);
                cLib_addCalc2(&i_this->m0398, 100.0f, 1.0f, 30.0f);
            }
            iVar4 = 1;
            bVar2 = 1;
        }
    } else if (i_this->mAcch.MaskWaterIn()) {
        iVar4 = 2;
        fVar7 = i_this->mAcch.m_wtr.GetHeight();
        i_this->m05BC.y = fVar7;
        if (actor->current.pos.y + i_this->mHaniCheck.y < fVar7 + 100.0f) {
            if ((param_2 == 0) || (param_2 == 2)) {
                actor->gravity = 0.0f;
                if (param_2 == 0) {
                    actor->speed.setall(0.0f);
                }
                i_this->m0370 += 1000;
                if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                    fVar1 = (cM_ssin(i_this->m0370) * 2.0f) + 2.0f;
                } else {
                    fVar1 = (cM_ssin(i_this->m0370) * 40.0f) + 20.0f;
                }
                cLib_addCalc2(&actor->current.pos.y, fVar7 - fVar1, 1.0f, i_this->m0398);
                cLib_addCalc2(&i_this->m0398, 30.0f, 1.0f, 3.0f);
            }
            iVar4 = 1;
        }
    }
    if ((u8)iVar4 != 0) {
        if ((i_this->mMode != MODE_FLY_MOVE_3) && (i_this->mMode != MODE_WATER_MOVE_61)) {
            actor->speedF = 0.0f;
        }
        if (((u8)iVar4 == 1) && (i_this->m0341 == 0)) {
            local_3c.setall(1.0f);
            if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                local_3c.setall(4.0f);
            }
            i_this->mRippleCb.remove();
            dComIfGp_particle_setShipTail(dPa_name::ID_AK_JN_HAMON00, &i_this->m05BC, NULL, &local_3c, 0xFF, &i_this->mRippleCb);
            i_this->m0370 = 0;
            i_this->m0341 = 1;
            i_this->mRippleCb.setRate(0.0f);
            shibuki_set(i_this, i_this->m05BC, 0.5f);
        }
        iVar4 = (!bVar2) ? 0 : 1;
        iVar4++;
    } else {
        if (i_this->m0341 != 0) {
            i_this->mRippleCb.remove();
            i_this->m0341 = 0;
            i_this->m0398 = 0.0f;
        }
        iVar4 = 0;
    }
    return iVar4;
}

/* 00002318-0000263C       .text ph_fly_move__FP8ph_class */
static void ph_fly_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mMode) {
        case MODE_FLY_MOVE_0:
            anm_init(i_this, dRes_INDEX_PH_BCK_PFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 0);
            anm_init(i_this, dRes_INDEX_PH_BCK_BFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 1);
            i_this->mBodySph.SetTgType(
                AT_TYPE_BOMB | AT_TYPE_BOOMERANG | AT_TYPE_NORMAL_ARROW | AT_TYPE_HOOKSHOT | AT_TYPE_SKULL_HAMMER | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW |
                AT_TYPE_LIGHT_ARROW | AT_TYPE_GRAPPLING_HOOK
            );
            i_this->m034A = 0x1000;
            i_this->m034C = 0;
            i_this->mMode++;
            // Fall-through
        case MODE_FLY_MOVE_1:
            cLib_addCalcAngleS2(&actor->current.angle.x, 0, 1, 0x200);
            cLib_addCalc0(&actor->speedF, 0.2f, 0.5f);
            actor->speed.y = 0.0f;
            fly_angle_set(i_this, 0);
            fuwafuwa_set(i_this);
            if ((i_this->mCountDownTimers[0] == 0) && (ph_hani_check(i_this, i_this->mHaniCheckDist2D, i_this->mHaniCheckDist3D, 0))) {
                i_this->m0378 = 150.0f;
                i_this->mMode++;
            }
            break;
        case MODE_FLY_MOVE_2:
            {
                f32 f31 = 250.0f;
                cLib_addCalc2(&actor->speedF, 8.0f, 0.5f, 1.0f);
                fly_angle_set(i_this, 1);
                fuwafuwa_set(i_this);
                if (ph_hani_check(i_this, f31, 25400.0f, 0)) {
                    i_this->m034A = 0x2000;
                    i_this->m034C = 0;
                    i_this->mCountDownTimers[0] = 20;
                    i_this->mMode++;
                }
                break;
            }
        case MODE_FLY_MOVE_3:
            i_this->mTargetAngle = fopAcM_searchPlayerAngleY(actor);
            i_this->m0378 = 80.0f;
            i_this->mHaniTarget.setall(0.0f);
            i_this->mMode++;
            // Fall-through
        case MODE_FLY_MOVE_4:
            {
                f32 f1 = 16.0f;
                cLib_addCalc2(&actor->speedF, f1, 1.0f, 2.0f);
                fly_angle_set(i_this, 2);
                cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mTargetAngle, 1, 0x500);
                cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x500);
                if (i_this->mCountDownTimers[0] == 0) {
                    i_this->m034A = 0x1000;
                    i_this->m034C = 0;
                    i_this->m0378 = 150.0f;
                    int r0 = 60;
                    i_this->mCountDownTimers[0] = DEMO_SELECT(cM_rndF(r0) + r0, cM_rndF(60.0f) + 60.0f);
                    i_this->mAtCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mAtCyl.OnAtHitBit();
                    for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                        i_this->mFuwafuwaValue[i] = 0;
                    }
                    i_this->mMode = MODE_FLY_MOVE_1;
                }
                break;
            }
    }
    puropera_kaiten(i_this);
    if ((sea_water_check(i_this, 1)) &&
        (actor->current.pos.y + i_this->mHaniCheck.y < (DEMO_SELECT((i_this->m05BC.y + 200.0f) + REG8_F(8), i_this->m05BC.y + 200.0f))))
    {
        actor->current.angle.x = 0;
    }
    if ((!body_atari_check(i_this)) && (!ph_wall_hit_check(i_this))) {
        hajiki_check(i_this);
    }
}

/* 0000263C-00002E18       .text ph_fly_sea_move__FP8ph_class */
static void ph_fly_sea_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 fVar2;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daShip_c* ship = dComIfGp_getShipActor();
    if (REG8_S(3) != 0) {
        return;
    }
    switch (i_this->mMode) {
        case MODE_FLY_MOVE_0:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                i_this->mFuwafuwaValue[i] = 0;
            }
            actor->current.angle.z = 0;
            if (i_this->mCurrBckIdx != dRes_INDEX_PH_BCK_PFLY_e) {
                anm_init(i_this, dRes_INDEX_PH_BCK_PFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 0);
                anm_init(i_this, dRes_INDEX_PH_BCK_BFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 1);
            }
            i_this->mAtCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.OnAtHitBit();
            i_this->mBodySph.SetTgType(
                AT_TYPE_BOMB | AT_TYPE_BOOMERANG | AT_TYPE_NORMAL_ARROW | AT_TYPE_HOOKSHOT | AT_TYPE_SKULL_HAMMER | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW |
                AT_TYPE_LIGHT_ARROW | AT_TYPE_GRAPPLING_HOOK
            );
            i_this->m0378 = 150.0f;
            i_this->m034A = 0x1000;
            i_this->m034C = 0;
            i_this->mMode++;
            // Fall-through
        case MODE_FLY_MOVE_1:
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                if (i_this->m0372 > 0) {
                    i_this->m0372--;
                }
                if ((i_this->m0372 == 0) && (ph_hani_check(i_this, i_this->mHaniCheckDist2D, i_this->mHaniCheckDist3D, 1))) {
                    i_this->m0378 = 150.0f;
                    i_this->m034A = 0x2000;
                    i_this->m034C = 0;
                    i_this->mMode++;
                }
            }
            cLib_addCalc0(&actor->speedF, 1.0f, REG12_F(6) + 5.0f);
            cLib_addCalcAngleS2(&actor->shape_angle.z, actor->current.angle.z, 1, 0x200);
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x200);
            fuwafuwa_set(i_this);
            i_this->mTargetAngle = fopAcM_searchPlayerAngleY(actor);
            break;
        case MODE_FLY_MOVE_2:
            i_this->mCountDownTimers[0] = 57;
            i_this->mTargetAngle = fopAcM_searchPlayerAngleY(actor);
            actor->shape_angle.z = 0;
            i_this->m0378 = 80.0f;
            i_this->mHaniTarget.setall(0.0f);
            i_this->mMode++;
            // Fall-through
        case MODE_FLY_MOVE_3:
            if (!ph_hani_check(i_this, i_this->m038C, 25400.0f, 1)) {
                i_this->mMode = MODE_FLY_MOVE_4;
            } else {
                if (i_this->mCountDownTimers[2] == 0) {
                    fVar1 = i_this->m032C.x - actor->current.pos.x;
                    fVar2 = i_this->m032C.z - actor->current.pos.z;
                    if (std::sqrtf(SQUARE(fVar1) + SQUARE(fVar2)) > i_this->m038C) {
                        i_this->mCountDownTimers[2] = 30;
                        i_this->mMode = MODE_FLY_MOVE_4;
                        break;
                    }
                }
                if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                    i_this->m0372 = 60;
                    i_this->mMode = MODE_FLY_MOVE_0;
                    if (fopAcM_searchActorDistance(actor, ship) < (REG12_F(7) + 200.0f)) {
                        i_this->mMode = MODE_FLY_MOVE_7;
                    }
                } else if (i_this->mCountDownTimers[0] == 0) {
                    i_this->m0372 = 60;
                    i_this->mMode = MODE_FLY_MOVE_0;
                } else {
                    f32 f1 = 98.0f;
                    cLib_addCalc2(&actor->speedF, f1, 1.0f, 10.0f);
                    if (i_this->mCountDownTimers[1] == 0) {
                        i_this->mCountDownTimers[1] = 15;
                        i_this->m0341 = 0;
                    }
                }
            }
            break;
        case MODE_FLY_MOVE_4:
            i_this->mCountDownTimers[0] = 30;
            actor->current.angle.z = 0;
            i_this->m0378 = 150.0f;
            i_this->m034A = 0x1000;
            i_this->m034C = 0;
            i_this->mMode++;
            // Fall-through
        case MODE_FLY_MOVE_5:
            cLib_addCalcAngleS2(&actor->shape_angle.z, actor->current.angle.z, 1, 0x200);
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x200);
            cLib_addCalc0(&actor->speedF, 1.0f, REG12_F(6) + 5.0f);
            i_this->mTargetAngle = fopAcM_searchPlayerAngleY(actor);
            if (i_this->mCountDownTimers[0] == 0) {
                i_this->mMode++;
            }
            break;
        case MODE_FLY_MOVE_6:
            cLib_addCalc2(&actor->speedF, 150.0f, 0.5f, 1.0f);
            fVar1 = i_this->m032C.x - actor->current.pos.x;
            fVar2 = i_this->m032C.z - actor->current.pos.z;
            i_this->mTargetAngle = cM_atan2s(fVar1, fVar2);
            if (std::sqrtf(SQUARE(fVar1) + SQUARE(fVar2)) < 50.0f) {
                i_this->m0372 = 60;
                i_this->mMode = 0;
            }
            break;
        case MODE_FLY_MOVE_7:
            for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                i_this->mFuwafuwaValue[i] = 0;
            }
            actor->current.angle.z = 0;
            if (i_this->mCurrBckIdx != dRes_INDEX_PH_BCK_PFLY_e) {
                anm_init(i_this, dRes_INDEX_PH_BCK_PFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 0);
                anm_init(i_this, dRes_INDEX_PH_BCK_BFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 1);
            }
            actor->speedF = 98.0f;
            i_this->mTargetAngle = cM_atan2s(i_this->m032C.x - ship->current.pos.x, i_this->m032C.z - ship->current.pos.z);
            i_this->mMode++;
            // Fall-through
        case MODE_FLY_MOVE_8:
            cLib_addCalcAngleS2(&actor->shape_angle.z, actor->current.angle.z, 1, 0x200);
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x200);
            cLib_addCalc0(&actor->speedF, 1.0f, REG12_F(6) + 5.0f);
            if (actor->speedF < 1.0f) {
                if (!ph_hani_check(i_this, i_this->m038C, 25400.0f, 1)) {
                    i_this->mMode = MODE_FLY_MOVE_4;
                } else {
                    i_this->mMode = MODE_FLY_MOVE_0;
                    actor->speedF = 0.0f;
                }
            }
            // Fall-through
        default:
            break;
    }
    if ((i_this->mMode >= MODE_FLY_MOVE_4) && (i_this->mMode <= MODE_FLY_MOVE_6) && (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) &&
        (ph_hani_check(i_this, i_this->mHaniCheckDist2D, i_this->mHaniCheckDist3D, 1)))
    {
        i_this->m0378 = 150.0f;
        i_this->m034A = 0x2000;
        i_this->m034C = 0;
        i_this->mMode = MODE_FLY_MOVE_2;
    }
    puropera_kaiten(i_this);
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mTargetAngle, 1, 0x500);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x500);
    sea_water_check(i_this, 1);
    fVar1 = i_this->m05BC.y + 500.0f + REG12_F(8);
    if (i_this->mMode == MODE_FLY_MOVE_3) {
        cLib_addCalcAngleS2(&actor->shape_angle.x, REG12_F(11) + 4096.0f, 1, 0x800);
        fVar1 = player->current.pos.y;
    }
    cLib_addCalc2(&actor->current.pos.y, fVar1, 1.0f, REG12_F(10) + 50.0f);
    if ((!body_atari_check(i_this)) && (!ph_wall_hit_check(i_this))) {
        hajiki_check(i_this);
    }
}

/* 00002E18-00002F50       .text ph_hane_move__FP8ph_class */
static void ph_hane_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mMode) {
        case MODE_HANE_MOVE_10:
            i_this->m0378 = 100.0f;
            i_this->m034A = 0x1000;
            i_this->m034C = 0;
            i_this->m036E = 0;
            i_this->mCountDownTimers[0] = 15;
            i_this->mFuwafuwaValue[4] = 0;
            i_this->mMode++;
        // Fall-through
        case MODE_HANE_MOVE_11:
            actor->shape_angle.y += 0x500;
            cLib_addCalc0(&actor->speedF, 0.5f, 1.0f);
            fly_angle_set(i_this, 4);
            if ((i_this->mCountDownTimers[0] == 0) && (actor->speedF < 0.1f)) {
                i_this->mAction = ACTION_FLY_MOVE;
                if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                    i_this->mCountDownTimers[0] = 60;
                    i_this->mAtCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                    i_this->mAtCyl.OnAtHitBit();
                    for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                        i_this->mFuwafuwaValue[i] = 0;
                    }
                    i_this->mMode = MODE_FLY_MOVE_1;
                } else {
                    i_this->mMode = MODE_FLY_MOVE_0;
                }
            }
            break;
    }
    body_atari_check(i_this);
    puropera_kaiten(i_this);
}

/* 00002F50-00003768       .text ph_bunri_move__FP8ph_class */
static void ph_bunri_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 sVar6;
    s16 sVar3;
    f32 dVar12;
    f32 dVar11;

    switch (i_this->mMode) {
        case MODE_BUNRI_MOVE_20:
            i_this->m037C = 1.0f;
            i_this->mBodySph.OnCoSetBit();
            i_this->mTgCyl.OffTgSetBit();
            i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.ClrAtSet();
            i_this->mBodySph.SetTgType(~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
            i_this->mHaniTarget = i_this->mHaniCheck;
            i_this->mHaniTarget.y = 0.0f;
            if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                i_this->m0350 = 900;
                fopAcM_seStart(actor, JA_SE_CM_PH_CUT_PROPELLER, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_PH_CUT_PROPELLER, 0);
            } else {
                i_this->m0350 = 150;
                fopAcM_seStart(actor, JA_SE_CM_SH_CUT_PROP, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_SH_CUT_PROP, 0);
            }
            actor->speedF = 0.0f;
            anm_init(i_this, dRes_INDEX_PH_BCK_PAWAY_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
            anm_init(i_this, dRes_INDEX_PH_BCK_BDAMAGE_e, 1.0f, J3DFrameCtrl::EMode_NONE, 2.0f, -1, 1);
            i_this->mMode++;
        case MODE_BUNRI_MOVE_21:
            if (!i_this->mpBodyMorf->isStop()) {
                break;
            }
            i_this->m0308 = actor->current.pos;
            if (i_this->mType != ACTOR_TYPE_SEAHAT) {
                actor->speed.y = 10.0f;
                actor->gravity = -3.0f;
            } else {
                actor->speed.y = 10.0f;
                actor->gravity = -10.0f;
            }
            i_this->mMode++;
        // Fall-through
        case MODE_BUNRI_MOVE_22:
            if ((!daSea_ChkArea(actor->current.pos.x, actor->current.pos.z)) && (i_this->mAcch.ChkGroundHit())) {
                anm_init(i_this, dRes_INDEX_PH_BCK_BCHAKUCHI_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
                fopAcM_seStart(actor, JA_SE_CM_PH_FALL, dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd));
                i_this->mMode++;
            }
            break;
        case MODE_BUNRI_MOVE_23:
            if (!i_this->mpBodyMorf->isStop()) {
                break;
            }
            i_this->mMode++;
            // Fall-through
        case MODE_BUNRI_MOVE_24:
            if (i_this->m0350 == 0) {
                i_this->mAction = ACITON_FUJYOU_MOVE;
                i_this->mMode = MODE_FUJYOU_MOVE_30;
                break;
            }
            dVar12 = i_this->m0308.x - actor->current.pos.x;
            dVar11 = i_this->m0308.z - actor->current.pos.z;
            i_this->mBodySph.SetTgType(~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
            actor->current.angle.y += cM_rndFX(16384.0f);
            if (std::sqrtf(SQUARE(dVar12) + SQUARE(dVar11)) >= 200.0f) {
                if ((s16)cLib_distanceAngleS(actor->current.angle.y, cM_atan2s(dVar12, dVar11)) < 0x2000) {
                    actor->current.angle.y = cM_atan2s(dVar12, dVar11);
                } else {
                    sVar6 = actor->current.angle.y + 0x2000;
                    sVar3 = actor->current.angle.y + -0x2000;
                    if ((s16)cLib_distanceAngleS(sVar6, (s16)cM_atan2s(dVar12, dVar11)) < (s16)cLib_distanceAngleS(sVar3, (s16)cM_atan2s(dVar12, dVar11))) {
                        actor->current.angle.y = sVar6;
                    } else {
                        actor->current.angle.y = sVar3;
                    }
                }
            }
            anm_init(i_this, dRes_INDEX_PH_BCK_BJUMP_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->mMode = MODE_BUNRI_MOVE_25;
            // Fall-through
        case MODE_BUNRI_MOVE_25:
            if (i_this->mpBodyMorf->getFrame() < 7.0f) {
                cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x1000);
            }
            if (i_this->mpBodyMorf->checkFrame(7.0f)) {
                actor->speedF = 5.0f;
                actor->gravity = -3.0f;
                actor->speed.y = 20.0f;
                fopAcM_monsSeStart(actor, JA_SE_CV_PH_JUMP, 0);
                i_this->mMode++;
            }
            break;
        case MODE_BUNRI_MOVE_26:
            if (i_this->mAcch.ChkGroundHit()) {
                fopAcM_seStart(actor, JA_SE_CM_PH_JUMP, dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd));
                actor->speedF = 0.0f;
                i_this->mMode = MODE_BUNRI_MOVE_24;
            }
            break;
    }
    if ((i_this->mMode >= MODE_BUNRI_MOVE_24) && (i_this->m0350 > 0)) {
        i_this->m0350--;
    }
    cLib_addCalcAngleS2(&actor->current.angle.x, 0, 1, 0x500);
    cLib_addCalcAngleS2(&actor->shape_angle.x, actor->current.angle.x, 1, 0x500);
    cLib_addCalcAngleS2(&actor->current.angle.z, 0, 1, 0x500);
    cLib_addCalcAngleS2(&actor->shape_angle.z, actor->current.angle.z, 1, 0x500);
    if (body_atari_check(i_this)) {
        s16 r27 = i_this->mMode;
        if (i_this->mHitType == 2) {
            fopAcM_seStart(actor, JA_SE_CM_PH_HIT_WIND, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_PH_CUT_PROPELLER, 0);
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            actor->speedF = 30.0f;
            i_this->mMode = r27;
            i_this->mAction = ACTION_BUNRI_MOVE;
        }
    }
    int r3 = sea_water_check(i_this, 1);
    if (r3 != 0) {
        i_this->mAction = ACTION_WATER_MOVE;
        if (r3 == 2) {
            i_this->mMode = MODE_WATER_MOVE_60;
        } else {
            i_this->mMode = MODE_WATER_MOVE_70;
        }
    }
}

/* 00003768-00003F34       .text ph_fujyou_move__FP8ph_class */
static void ph_fujyou_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mMode) {
        case MODE_FUJYOU_MOVE_30:
            fopAcM_seStart(actor, JA_SE_CM_PH_RECOVER, 0);
            i_this->m0388 = actor->current.pos.y + 200.0f;
            i_this->mBodySph.OffCoSetBit();
            i_this->mTgCyl.OnTgSetBit();
            i_this->mAtCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.OnAtHitBit();
            anm_init(i_this, dRes_INDEX_PH_BCK_PHUKKI_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
            anm_init(i_this, dRes_INDEX_PH_BCK_BHUKKI_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->mMode++;
            // Fall-through
        case MODE_FUJYOU_MOVE_31:
            cLib_addCalc2(&i_this->m02FC.x, i_this->m03A0 + 1.0f, 1.0f, (i_this->m03A0 + 0.3f) + 0.3f);
            i_this->m02FC.y = i_this->m02FC.z = i_this->m02FC.x;
            if (i_this->m02FC.x > i_this->m03A0 + 0.8f) {
                i_this->m02FC.setall(i_this->m03A0 + 1.0f);
            }
            if (i_this->mpBodyMorf->isStop()) {
                i_this->m034A = 0x1000;
                i_this->m034C = 0;
                i_this->m0384 = 0.0f;
                for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                    i_this->mFuwafuwaValue[i] = 0;
                }
                actor->gravity = -3.0f;
                i_this->mMode++;
            }
            break;
        case MODE_FUJYOU_MOVE_32:
            i_this->m033A += (s16)(i_this->m0384 * 1000.0f);
            puropera_sound(i_this);
            cLib_addCalc2(&i_this->m0384, 4.0f, 0.03f, 0.05f);
            i_this->mFuwafuwaValue[4] += (s16)(i_this->m0384 * 200.0f);
            cLib_addCalcAngleS2(&actor->current.angle.z, cM_ssin(i_this->mFuwafuwaValue[4]) * 4000.0f, 1, 0x1000);
            actor->shape_angle.z = actor->current.angle.z;
            actor->speed.y = i_this->m0384;
            i_this->mFuwafuwaValue[0] += 2000;
            i_this->mFuwafuwaValue[1] += 1200;
            i_this->mFuwafuwaValue[2] += 1200;
            i_this->mHaniTarget.y = cM_ssin(i_this->mFuwafuwaValue[0]) * 10.0f;
            i_this->mHaniTarget.x = cM_scos(i_this->mFuwafuwaValue[1]) * 20.0f;
            i_this->mHaniTarget.z = cM_scos(i_this->mFuwafuwaValue[2]) * 20.0f;
            if (actor->current.pos.y > i_this->m0388) {
                i_this->mAtCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mAtCyl.OnAtHitBit();
                for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                    i_this->mFuwafuwaValue[i] = 0;
                }
                actor->current.angle.z = 0;
                i_this->mAction = ACTION_FLY_MOVE;
                i_this->mBodySph.SetTgType(
                    AT_TYPE_BOMB | AT_TYPE_BOOMERANG | AT_TYPE_NORMAL_ARROW | AT_TYPE_HOOKSHOT | AT_TYPE_SKULL_HAMMER | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW |
                    AT_TYPE_LIGHT_ARROW | AT_TYPE_GRAPPLING_HOOK
                );
                actor->gravity = -3.0f;
                i_this->mMode = MODE_FLY_MOVE_1;
            }
            break;
        case MODE_FUJYOU_MOVE_33:
            fopAcM_seStart(actor, JA_SE_CM_SH_RECOVER_PROP, 0);
            i_this->mBodySph.OffCoSetBit();
            anm_init(i_this, dRes_INDEX_SH_BCK_PHUKKI_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
            anm_init(i_this, dRes_INDEX_SH_BCK_BHUKKI_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->mMode++;
            // Fall-through
        case MODE_FUJYOU_MOVE_34:
            cLib_addCalc2(&i_this->m02FC.x, i_this->m03A0 + 1.0f, 1.0f, (i_this->m03A0 + 0.3f) + 0.3f);
            i_this->m02FC.y = i_this->m02FC.z = i_this->m02FC.x;
            if (i_this->m02FC.x > i_this->m03A0 + 0.8f) {
                i_this->m02FC.setall(i_this->m03A0 + 1.0f);
            }
            if (i_this->mpBodyMorf->isStop()) {
                i_this->m034A = 0x1000;
                i_this->m034C = 0;
                i_this->m0384 = 0.0f;
                for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                    i_this->mFuwafuwaValue[i] = 0;
                }
                actor->gravity = -3.0f;
                i_this->mMode++;
            }
            break;
        case MODE_FUJYOU_MOVE_35:
            i_this->m033A += (s16)(i_this->m0384 * 1000.0f);
            puropera_sound(i_this);
            cLib_addCalc2(&i_this->m0384, 6.0f, 0.3f, 0.5f);
            i_this->mFuwafuwaValue[4] += (s16)(i_this->m0384 * 200.0f);
            cLib_addCalcAngleS2(&actor->current.angle.z, cM_ssin(i_this->mFuwafuwaValue[4]) * 4000.0f, 1, 0x1000);
            actor->shape_angle.z = actor->current.angle.z;
            actor->speed.y = i_this->m0384;
            i_this->mFuwafuwaValue[0] += 2000;
            i_this->mFuwafuwaValue[1] += 1200;
            i_this->mFuwafuwaValue[2] += 1200;
            i_this->mHaniTarget.y = cM_ssin(i_this->mFuwafuwaValue[0]) * 10.0f;
            i_this->mHaniTarget.x = cM_scos(i_this->mFuwafuwaValue[1]) * 20.0f;
            i_this->mHaniTarget.z = cM_scos(i_this->mFuwafuwaValue[2]) * 20.0f;
            if (std::fabsf(actor->current.pos.y - (i_this->m05BC.y + 500.0f)) < 10.0f) {
                i_this->mAction = ACTION_FLY_MOVE;
                i_this->mMode = MODE_FLY_MOVE_4;
            }
            break;
        case MODE_FUJYOU_MOVE_36:
            i_this->m033A += (s16)(i_this->m0384 * 1000.0f);
            puropera_sound(i_this);
            actor->speed.y = 70.0f;
            if (actor->current.pos.y > i_this->m05BC.y + 500.0f) {
                i_this->mAction = ACTION_FLY_MOVE;
                i_this->mMode = MODE_FLY_MOVE_0;
            }
            break;
    }
    if ((i_this->mType != ACTOR_TYPE_SEAHAT) && (sea_water_check(i_this, 1)) && (actor->current.pos.y + i_this->mHaniCheck.y < i_this->m05BC.y + 100.0f)) {
        actor->gravity = 0.0f;
    }
    if ((!body_atari_check(i_this)) && (hajiki_check(i_this))) {
        anm_init(i_this, dRes_INDEX_PH_BCK_PFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 0);
        i_this->m02FC.setall(i_this->m03A0 + 1.0f);
    }
}

/* 00003F34-0000405C       .text dead_item__FP8ph_class */
static void dead_item(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u8 i_scale;
    cXyz local_28;

    local_28 = actor->current.pos;
    local_28 += i_this->mHaniCheck;
    local_28.y += 40.0f;
    i_scale = (i_this->m039C * 2.0f) + 5.0f;
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        fopAcM_createDisappear(actor, &local_28, i_scale, daDisItem_IBALL_e, actor->stealItemBitNo);
    } else {
        fopAcM_createDisappear(actor, &local_28, i_scale, daDisItem_IBALL_e);
        daComing2::Act_c* coming2 = (daComing2::Act_c*)actor;
        coming2->pluss_coming_point1();
    }
    fopAcM_onActor(actor);
    fopAcM_delete(actor);
}

/* 0000405C-00004988       .text ph_damage_dead_move__FP8ph_class */
static void ph_damage_dead_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch (i_this->mMode) {
        case MODE_DAMAGE_DEAD_MOVE_40:
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            if ((actor->health <= 0) || (i_this->mHitType == 3)) {
                actor->speedF = 25.0f;
                i_this->m034E = 0x2000;
            } else {
                actor->speedF = 15.0f;
                i_this->m034E = 0x1000;
            }
            if (i_this->m0341 != 0) {
                i_this->m034E = -0x8000;
            }
            if (actor->health > 0) {
                fopAcM_monsSeStart(actor, JA_SE_CV_PH_DAMAGE, 0);
            } else {
                if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PH_DIE, 0);
                } else {
                    fopAcM_monsSeStart(actor, JA_SE_CV_SH_DIE, 0);
                }
            }
            i_this->mCountDownTimers[0] = 0;
            if (i_this->m02FC.x) {
                anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHIWA_e, dRes_INDEX_PH_BCK_PUCHI_CHAKU_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
            }
            anm_init(i_this, dRes_INDEX_PH_BCK_BDAMAGE_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->mMode++;
            // Fall-through
        case MODE_DAMAGE_DEAD_MOVE_41:
            cLib_addCalc0(&actor->speedF, 0.5f, 1.0f);
            if ((actor->health <= 0) && (actor->speedF < 5.0f)) {
                cLib_addCalc0(&i_this->m02FC.x, 0.3f, i_this->m03A0 + 1.0f);
                i_this->m02FC.y = i_this->m02FC.z = i_this->m02FC.x;
                cLib_addCalc0(&actor->scale.x, 0.3f, i_this->m039C + 1.0f);
                actor->scale.y = actor->scale.z = actor->scale.x;
            }
            actor->shape_angle.y += i_this->m034E;
            cLib_addCalcAngleS2(&i_this->m034E, 0, 1, 0x200);
            if (i_this->mpBodyMorf->isStop()) {
                if (actor->health > 0) {
                    actor->speedF = 0.0f;
                    i_this->mAction = ACTION_BUNRI_MOVE;
                    i_this->mMode = MODE_BUNRI_MOVE_24;
                } else {
                    dead_item(i_this);
                }
            }
            break;
        case MODE_DAMAGE_DEAD_MOVE_42:
            if (i_this->mCountDownTimers[0] == 0) {
                i_this->mAction = ACTION_BUNRI_MOVE;
                i_this->mMode = MODE_BUNRI_MOVE_24;
            }
            break;
        case MODE_DAMAGE_DEAD_MOVE_43:
            actor->current.angle.y = cM_atan2s(
                (actor->current.pos.x + i_this->mHaniCheck.x) - player->current.pos.x,
                (actor->current.pos.z + i_this->mHaniCheck.z) - player->current.pos.z
            );
            actor->speedF = 25.0f;
            i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.ClrAtSet();
            actor->health = 0;
            i_this->mFuwafuwaValue[4] = 0;
            if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                fopAcM_monsSeStart(actor, JA_SE_CV_PH_DIE, 0);
            } else {
                fopAcM_monsSeStart(actor, JA_SE_CV_SH_DIE, 0);
            }
            anm_init(i_this, dRes_INDEX_PH_BCK_BDAMAGE_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->m0320.setall(i_this->m039C + 1.0f);
            if (i_this->m0342 != 0) {
                actor->speed.setall(0.0f);
                actor->speedF = 0.0f;
                i_this->mCountDownTimers[0] = 0;
                i_this->mMode = MODE_DAMAGE_DEAD_MOVE_46;
            } else {
                if (!i_this->mAcch.ChkGroundHit()) {
                    actor->speed.y = 0.0f;
                    actor->gravity = 0.0f;
                    i_this->mMode = MODE_DAMAGE_DEAD_MOVE_44;
                    i_this->mCountDownTimers[0] = 60;
                    if (i_this->mHitType == 7) {
                        i_this->mCountDownTimers[0] = 0;
                    }
                    anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHIWA_e, dRes_INDEX_PH_BCK_PUCHI_CHAKU_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
                    if (i_this->mHitType == 6) {
                        i_this->mCountDownTimers[0] = 0;
                        actor->speedF = 15.0f;
                        actor->speed.y = 20.0f;
                        actor->gravity = -5.0f;
                        i_this->mMode = MODE_DAMAGE_DEAD_MOVE_45;
                    }
                } else {
                    i_this->mMode = MODE_DAMAGE_DEAD_MOVE_46;
                }
            }
            break;
        case MODE_DAMAGE_DEAD_MOVE_44:
            cLib_addCalc0(&actor->speedF, 0.5f, 0.5f);
            actor->shape_angle.y += 0x500;
            fly_angle_set(i_this, 4);
            if (i_this->mCountDownTimers[0] != 0) {
                if (!i_this->mpPropellerMorf->isStop()) {
                    break;
                }
            }
            dead_item(i_this);
            break;
        case MODE_DAMAGE_DEAD_MOVE_45:
            if (i_this->mCountDownTimers[0] == 1) {
                actor->gravity = -5.0f;
                actor->speed.y = 23.0f;
                if (1 < i_this->mFuwafuwaValue[4]) {
                    actor->speed.y = 15.0f;
                }
                actor->speedF = 5.0f;
                i_this->m0320.x = i_this->m039C + 0.8f;
                i_this->m0320.y = i_this->m039C + 1.2f;
            }
            if ((i_this->mCountDownTimers[0] == 0) && (i_this->mAcch.ChkGroundHit())) {
                actor->speedF = 0.0f;
                i_this->m0320.x = i_this->m039C + 1.2f;
                i_this->m0320.y = i_this->m039C + 0.8f;
                i_this->mCountDownTimers[0] = 3;
                i_this->mFuwafuwaValue[4]++;
                if (i_this->mFuwafuwaValue[4] > 2) {
                    dead_item(i_this);
                }
            }
            cLib_addCalc2(&actor->scale.x, i_this->m0320.x, 0.5f, 0.5f);
            cLib_addCalc2(&actor->scale.y, i_this->m0320.y, 0.5f, 0.5f);
            break;
        case MODE_DAMAGE_DEAD_MOVE_46:
            cLib_addCalc0(&actor->speedF, 0.5f, 0.5f);
            actor->shape_angle.y += 0x500;
            if (i_this->mCountDownTimers[0] == 0) {
                dead_item(i_this);
            }
            break;
        case MODE_DAMAGE_DEAD_MOVE_47:
            actor->shape_angle.x = 0;
            actor->shape_angle.z = 0;
            actor->current.angle.x = 0;
            actor->current.angle.z = 0;
            i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.ClrAtSet();
            i_this->mBodySph.OffCoSetBit();
            i_this->mBodySph.OffTgSetBit();
            actor->speedF = 0.0f;
            actor->gravity = -3.0f;
            actor->attention_info.flags = 0;
            actor->health = 0;
            i_this->mFuwafuwaValue[4] = 0;
            if (i_this->m02FC.x) {
                anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHIWA_e, dRes_INDEX_PH_BCK_PUCHI_CHAKU_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
            }
            anm_init(i_this, dRes_INDEX_PH_BCK_BDAMAGE_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->m0380 = 10.0f;
            if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                fopAcM_monsSeStart(actor, JA_SE_CV_PH_DIE, 0);
            } else {
                fopAcM_monsSeStart(actor, JA_SE_CV_SH_DIE, 0);
            }
            i_this->mMode++;
            // Fall-through
        case MODE_DAMAGE_DEAD_MOVE_48:
            cLib_addCalc2(&actor->scale.y, 0.1f, 1.0f, 0.5f);
            cLib_addCalc2(&actor->scale.x, 1.7f, 1.0f, 0.7f);
            if (i_this->m02FC.x) {
                i_this->m02FC = actor->scale;
            }
            if (actor->scale.y < 0.1f) {
                actor->scale.y = 0.1f;
                actor->scale.x = 1.7f;
                i_this->mCountDownTimers[0] = 20;
                i_this->mMode++;
            }
            break;
        case MODE_DAMAGE_DEAD_MOVE_49:
            if (i_this->mCountDownTimers[0] == 0) {
                dead_item(i_this);
            }
            break;
    }
    actor->current.angle.x = 0;
    actor->current.angle.z = 0;
    cLib_addCalcAngleS2(&actor->shape_angle.x, actor->current.angle.x, 1, 0x500);
    cLib_addCalcAngleS2(&actor->shape_angle.z, actor->current.angle.z, 1, 0x500);
    if (actor->health > 0) {
        u8 r31 = i_this->m0341;
        body_atari_check(i_this);
        int r3 = sea_water_check(i_this, 0);
        if ((r3 != 0) && (r31 == 0) && (i_this->m0341 != 0)) {
            i_this->mAction = ACTION_WATER_MOVE;
            if (r3 == 2) {
                i_this->mMode = MODE_WATER_MOVE_60;
            } else {
                i_this->mMode = MODE_WATER_MOVE_70;
            }
        }
    }
}

/* 00004988-00005134       .text ph_wind_move__FP8ph_class */
static void ph_wind_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    fopAc_ac_c* player_actor = dComIfGp_getPlayer(0);
    daPy_py_c* player = (daPy_py_c*)player_actor;
    int r31 = sea_water_check(i_this, 1);
    switch (i_this->mMode) {
        case MODE_WIND_MOVE_50:
            fopAcM_seStart(actor, JA_SE_CM_PH_HIT_WIND, 0);
            fopAcM_monsSeStart(actor, JA_SE_CV_PH_CUT_PROPELLER, 0);
            i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.ClrAtSet();
            i_this->mTgCyl.OffTgSetBit();
            i_this->mBodySph.OnCoSetBit();
            i_this->mBodySph.SetTgType(~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            actor->speed.y = 10.0f - (std::sqrtf(SQUARE((actor->current.pos.y + i_this->mHaniCheck.y) - player->current.pos.y)) * 0.1f);
            if (actor->speed.y < 0.0f) {
                actor->speed.y = 3.0f;
            }
            actor->speedF = 30.0f;
            actor->gravity = 0.0f;
            i_this->m0350 = 0;
            for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                i_this->mFuwafuwaValue[i] = 0;
            }
            actor->current.angle.x = 0;
            actor->current.angle.z = 0;
            i_this->mHaniTarget.setall(0.0f);
            i_this->mFuwafuwaValue[6] = -0x1000;
            i_this->mFuwafuwaValue[5] = -10000;
            if (cM_rnd() < 0.5f) {
                i_this->mFuwafuwaValue[5] = 10000;
                i_this->mFuwafuwaValue[6] = 0x1000;
            }
            anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHIWA_e, dRes_INDEX_PH_BCK_PUCHI_CHAKU_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
            anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_BUCHIWA_e, dRes_INDEX_PH_BCK_BUCHI_CHAKU_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->mMode++;
            // Fall-through
        case MODE_WIND_MOVE_51:
            i_this->mFuwafuwaValue[4] = i_this->mFuwafuwaValue[4] + i_this->mFuwafuwaValue[5];
            cLib_addCalcAngleS2(&actor->shape_angle.z, cM_ssin(i_this->mFuwafuwaValue[4]) * 20000.0f, 1, 0x500);
            cLib_addCalcAngleS2(&actor->shape_angle.x, cM_ssin(i_this->mFuwafuwaValue[4]) * 20000.0f, 1, 0x500);
            actor->shape_angle.y += i_this->mFuwafuwaValue[6];
            cLib_addCalc0(&actor->speedF, 0.3f, 1.0f);
            cLib_addCalc0(&actor->speed.y, 0.3f, 1.0f);
            if (actor->speedF > 0.2f) {
                break;
            }
            i_this->mFuwafuwaValue[5] = 0;
            actor->speedF = 0.0f;
            i_this->mMode++;
            // Fall-through
        case MODE_WIND_MOVE_52:
            if (r31 != 0) {
                i_this->mAction = ACTION_WATER_MOVE;
                if (r31 == 2) {
                    i_this->mMode = MODE_WATER_MOVE_60;
                    return;
                }
                i_this->mMode = MODE_WATER_MOVE_70;
                return;
            }
            actor->gravity = -0.3f;
            actor->shape_angle.y += i_this->mFuwafuwaValue[6];
            cLib_addCalcAngleS2(&i_this->mFuwafuwaValue[6], 0, 1, 0x100);
            fly_angle_set(i_this, 0);
            if (i_this->mAcch.ChkGroundHit()) {
                fopAcM_seStart(actor, JA_SE_CM_PH_FALL, dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd));
                actor->gravity = -3.0f;
                anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHI_CHAKU_e, dRes_INDEX_PH_BCK_PUCHIWA_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
                anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_BUCHI_CHAKU_e, dRes_INDEX_PH_BCK_BUCHIWA_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
                i_this->mMode++;
            }
            break;
        case MODE_WIND_MOVE_53:
            if (r31 != 0) {
                i_this->mAction = ACTION_WATER_MOVE;
                if (r31 == 2) {
                    i_this->mMode = MODE_WATER_MOVE_60;
                    return;
                }
                i_this->mMode = MODE_WATER_MOVE_70;
                return;
            }
            cLib_addCalcAngleS2(&actor->shape_angle.z, actor->current.angle.z, 1, 0x500);
            cLib_addCalcAngleS2(&actor->shape_angle.x, actor->current.angle.x, 1, 0x500);
            actor->shape_angle.y += i_this->mFuwafuwaValue[5];
            if (i_this->mpBodyMorf->isStop()) {
                if (!i_this->m02FC.x) {
                    actor->speedF = 0.0f;
                    i_this->mAction = ACTION_BUNRI_MOVE;
                    i_this->mMode = MODE_BUNRI_MOVE_24;
                    return;
                }
                i_this->mCountDownTimers[1] = cM_rndF(50.0f) + 50.0f;
                actor->shape_angle.x = 0;
                actor->shape_angle.z = 0;
                i_this->mMode++;
            }
            break;
        case MODE_WIND_MOVE_54:
            if (r31 != 0) {
                i_this->mAction = ACTION_WATER_MOVE;
                if (r31 == 2) {
                    i_this->mMode = MODE_WATER_MOVE_60;
                    return;
                }
                i_this->mMode = MODE_WATER_MOVE_70;
                return;
            }
            cLib_addCalc0(&actor->speedF, 0.3f, 1.0f);
            if (actor->speedF > 0.1f) {
                actor->shape_angle.y += i_this->mFuwafuwaValue[5];
            }
            if (i_this->mCountDownTimers[1] == 0) {
                actor->speedF = 0.0f;
                if (!i_this->m02FC.x) {
                    i_this->mAction = ACTION_BUNRI_MOVE;
                    i_this->mMode = MODE_BUNRI_MOVE_24;
                } else {
                    i_this->mAction = ACITON_FUJYOU_MOVE;
                    i_this->mMode = MODE_FUJYOU_MOVE_30;
                }
            }
            break;
    }
    if (body_atari_check(i_this)) {
        actor->shape_angle.x = 0;
        actor->shape_angle.z = 0;
        if (i_this->mHitType == 2) {
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->mFuwafuwaValue[5] = -1000;
                if (cM_rnd() < 0.5f) {
                    i_this->mFuwafuwaValue[5] = 1000;
                }
                actor->speedF = 20.0f;
                if (i_this->mCurrBckIdx != DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHIWA_e, dRes_INDEX_PH_BCK_PUCHI_CHAKU_e)) {
                    anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHIWA_e, dRes_INDEX_PH_BCK_PUCHI_CHAKU_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
                }
                fopAcM_seStart(actor, JA_SE_CM_PH_HIT_WIND, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_PH_CUT_PROPELLER, 0);
                i_this->mMode = MODE_WIND_MOVE_54;
            } else {
                i_this->mAction = ACTION_WIND_MOVE;
                i_this->mMode = MODE_WIND_MOVE_50;
            }
        }
    }
}

/* 00005134-00005628       .text ph_water_move__FP8ph_class */
static void ph_water_move(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    u32 uVar4;
    f32 fVar7;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mMode) {
        case MODE_WATER_MOVE_60:
            i_this->mBodySph.OnCoSetBit();
            i_this->mBodySph.SetTgType(~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
            actor->shape_angle.x = 0;
            actor->shape_angle.z = 0;
            actor->current.angle.x = 0;
            actor->current.angle.z = 0;
            for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                i_this->mFuwafuwaValue[i] = 0;
            }
            i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.ClrAtSet();
            if (i_this->mType != ACTOR_TYPE_SEAHAT) {
                if (!i_this->m02FC.x) {
                    i_this->mCountDownTimers[1] = cM_rndF(200.0f) + 200.0f;
                } else {
                    i_this->mCountDownTimers[1] = cM_rndF(100.0f) + 100.0f;
                }
                anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHI_CHAKU_e, dRes_INDEX_PH_BCK_PUCHIWA_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
                anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_BUCHI_CHAKU_e, dRes_INDEX_PH_BCK_BUCHIWA_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            } else {
                i_this->mCountDownTimers[1] = 150;
                i_this->mAtCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
                i_this->mAtCyl.OnAtHitBit();
                anm_init(i_this, dRes_INDEX_PH_BCK_BJAWS_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 1);
            }
            i_this->mCountDownTimers[2] = 20;
            actor->current.angle.y = cM_atan2s(
                                         (actor->current.pos.x + i_this->mHaniCheck.x) - player->current.pos.x,
                                         (actor->current.pos.z + i_this->mHaniCheck.z) - player->current.pos.z
                                     ) +
                                     0x8000;
            i_this->mMode++;
            // Fall-through
        case MODE_WATER_MOVE_61:
            {
                if (i_this->mCountDownTimers[0] == 0) {
                    i_this->mCountDownTimers[0] = 15;
                    i_this->m0341 = 0;
                }
                cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, 0x700);
                f32 f1 = 30.0f;
                cLib_addCalc2(&actor->speedF, f1, 1.0f, 10.0f);
                uVar4 = actor->speedF * 3.4f;
                if (uVar4 > 100) {
                    uVar4 = 100;
                }
                fopAcM_seStart(actor, JA_SE_CM_SH_CRUISING, uVar4);
                if (!ph_hani_check(i_this, i_this->m038C, 25400.0f, 1)) {
                    i_this->mAction = ACITON_FUJYOU_MOVE;
                    i_this->mMode = MODE_FUJYOU_MOVE_33;
                } else {
                    if (i_this->mCountDownTimers[2] == 0) {
                        fVar7 = i_this->m032C.x - actor->current.pos.x;
                        fVar2 = i_this->m032C.z - actor->current.pos.z;
                        if (std::sqrtf(SQUARE(fVar7) + SQUARE(fVar2)) > i_this->m038C) {
                            i_this->mAction = ACITON_FUJYOU_MOVE;
                            i_this->mMode = MODE_FUJYOU_MOVE_33;
                            break;
                        }
                    }
                    if (i_this->mCountDownTimers[1] == 0) {
                        i_this->mAction = ACITON_FUJYOU_MOVE;
                        i_this->mMode = MODE_FUJYOU_MOVE_33;
                    }
                }
                break;
            }
        case MODE_WATER_MOVE_70:
            i_this->mBodySph.OnCoSetBit();
            i_this->mBodySph.SetTgType(~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
            actor->shape_angle.x = 0;
            actor->shape_angle.z = 0;
            actor->current.angle.x = 0;
            actor->current.angle.z = 0;
            for (s32 i = 0; i < ARRAY_SIZE(i_this->mFuwafuwaValue); i++) {
                i_this->mFuwafuwaValue[i] = 0;
            }
            i_this->mAtCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mAtCyl.ClrAtSet();
            if (!i_this->m02FC.x) {
                i_this->mCountDownTimers[1] = cM_rndF(200.0f) + 200.0f;
            } else {
                i_this->mCountDownTimers[1] = cM_rndF(100.0f) + 100.0f;
            }
            anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_PUCHI_CHAKU_e, dRes_INDEX_PH_BCK_PUCHIWA_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 0);
            anm_init(i_this, DEMO_SELECT(dRes_INDEX_PH_BCK_BUCHI_CHAKU_e, dRes_INDEX_PH_BCK_BUCHIWA_e), 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1, 1);
            i_this->mMode++;
            // Fall-through
        case MODE_WATER_MOVE_71:
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->mAction = ACITON_FUJYOU_MOVE;
                if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                    i_this->mMode = MODE_FUJYOU_MOVE_33;
                } else {
                    i_this->mMode = MODE_FUJYOU_MOVE_30;
                }
            }
            break;
    }
    body_atari_check(i_this);
    sea_water_check(i_this, 2);
}

/* 00005628-0000573C       .text BG_check__FP8ph_class */
static void BG_check(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 radius;

    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        radius = 40.0f;
        if ((i_this->m02FC.x) && (!i_this->m037C)) {
            radius = 100.0f;
        }
        i_this->mAcchCir.SetWall(40.0f, radius);
    } else {
        i_this->mAcchCir.SetWall(50.0f, 500.0f);
    }
    actor->current.pos += i_this->mHaniCheck;
    actor->old.pos += i_this->mHaniCheck;
    actor->current.pos.y -= i_this->m0380;
    actor->old.pos.y -= i_this->m0380;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    actor->current.pos.y += i_this->m0380;
    actor->old.pos.y += i_this->m0380;
    actor->current.pos -= i_this->mHaniCheck;
    actor->old.pos -= i_this->mHaniCheck;
}

/* 0000573C-0000583C       .text UP_draw_SUB__FP8ph_class */
static void UP_draw_SUB(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    J3DModel* model = i_this->mpPropellerMorf->getModel();
    mDoMtx_stack_c::transS(i_this->m0314.x, i_this->m0314.y, i_this->m0314.z);
    if ((i_this->mMode == MODE_FLY_MOVE_4) || (i_this->mMode == MODE_WIND_MOVE_51) || (i_this->mMode == MODE_FLY_MOVE_3)) {
        mDoMtx_stack_c::YrotM(actor->shape_angle.y);
        mDoMtx_stack_c::XrotM(actor->shape_angle.x);
        mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
        mDoMtx_stack_c::YrotM(i_this->m033A);
    } else {
        mDoMtx_stack_c::YrotM(actor->shape_angle.y);
        mDoMtx_stack_c::YrotM(i_this->m033A);
    }
    mDoMtx_stack_c::scaleM(i_this->m02FC.x, i_this->m02FC.y, i_this->m02FC.z);
    model->setBaseTRMtx(mDoMtx_stack_c::now);
    i_this->mpPropellerMorf->calc();
    enemy_fire(&i_this->mPropellerEnemyFire);
}

/* 0000583C-0000591C       .text DW_draw_SUB__FP8ph_class */
static void DW_draw_SUB(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    J3DModel* model = i_this->mpBodyMorf->getModel();
    mDoMtx_stack_c::transS(
        actor->current.pos.x + i_this->mHaniCheck.x,
        actor->current.pos.y + i_this->mHaniCheck.y,
        actor->current.pos.z + i_this->mHaniCheck.z
    );
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    mDoMtx_stack_c::scaleM(actor->scale.x, actor->scale.y, actor->scale.z);
    model->setBaseTRMtx(mDoMtx_stack_c::now);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    i_this->mpBodyMorf->calc();
    enemy_fire(&i_this->mBodyEnemyFire);
}

/* 0000591C-000061A4       .text daPH_Execute__FP8ph_class */
static BOOL daPH_Execute(ph_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    f32 dVar6;
    cXyz local_2c;
    cXyz local_38;

    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        fopAcM_setGbaName(actor, dItemNo_BOOMERANG_e, 8, 0x25);
    } else {
        fopAcM_setGbaName(actor, dItemNo_BOOMERANG_e, 0x1F, 0x27);
    }
    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpBodyMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
        i_this->mpBodyMorf->calc();
        if ((i_this->m02FC.x) && (!i_this->m037C)) {
            if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                i_this->m02FC.setall(i_this->m03A0);
            } else {
                i_this->m02FC = actor->scale;
            }
            i_this->m02FC.x *= i_this->mEnemyIce.mScaleXZ;
            i_this->m02FC.y *= i_this->mEnemyIce.mScaleY;
            i_this->m02FC.z *= i_this->mEnemyIce.mScaleXZ;
            i_this->m0314 = i_this->m02C0;
            UP_draw_SUB(i_this);
        }
        return TRUE;
    }
    actor->eyePos = i_this->m02C0;
    actor->eyePos.y -= 30.0f;
    actor->eyePos.y -= i_this->m039C * 50.0f;
    for (s32 i = 0; i < ARRAY_SIZE(i_this->mCountDownTimers); i++) {
        if (i_this->mCountDownTimers[i] != 0) {
            i_this->mCountDownTimers[i]--;
        }
    }
    if (REG8_F(0)) {
        i_this->m039C = REG8_F(0) + 8.0f;
        actor->scale.setall(i_this->m039C + 1.0f);
    }
    if (REG8_F(1)) {
        i_this->m03A0 = REG8_F(1) + 5.0f;
    }
    switch (i_this->mAction) {
        case ACTION_FLY_MOVE:
            if (i_this->mType == ACTOR_TYPE_PEAHAT) {
                ph_fly_move(i_this);
            } else {
                ph_fly_sea_move(i_this);
            }
            break;
        case ACTION_HANE_MOVE:
            ph_hane_move(i_this);
            if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                sea_water_check(i_this, 1);
            }
            break;
        case ACTION_BUNRI_MOVE:
            ph_bunri_move(i_this);
            break;
        case ACITON_FUJYOU_MOVE:
            ph_fujyou_move(i_this);
            if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                if ((sea_water_check(i_this, 1)) && (i_this->m0341 != 0)) {
                    fVar2 = (i_this->m039C * 10.0f);
                    if (actor->current.pos.y < i_this->m05BC.y - fVar2) {
                        actor->current.pos.y = i_this->m05BC.y - fVar2;
                    }
                }
            } else {
                sea_water_check(i_this, 1);
            }
            break;
        case ACTION_DAMAGE_DEAD_MOVE:
            ph_damage_dead_move(i_this);
            break;
        case ACTION_WIND_MOVE:
            ph_wind_move(i_this);
            break;
        case ACTION_WATER_MOVE:
            ph_water_move(i_this);
            break;
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    if (i_this->m037C) {
        if (i_this->m02FC.x) {
            dVar6 = 1000.0f;
            puropera_kaiten(i_this);
            cLib_addCalc2(&i_this->m037C, 10.0f, 0.5f, 1.0f);
            if (i_this->mType == ACTOR_TYPE_SEAHAT) {
                cLib_addCalc2(&i_this->m037C, 30.0f, 1.0f, 5.0f);
                i_this->m034A = 0x2000;
                dVar6 = 2000.0f;
            }
            local_2c.x = 0.0f;
            local_2c.y = 0.0f;
            local_2c.z = -i_this->m037C;
            MtxPosition(&local_2c, &local_38);
            i_this->m0314 += local_38;
            i_this->m0314.y += i_this->m037C;
            if (i_this->m0314.y > actor->current.pos.y + dVar6) {
                i_this->m02FC.setall(0.0f);
                i_this->m037C = 0.0f;
            }
        }
    } else {
        i_this->m0314 = i_this->m02C0;
    }
    local_2c.x = 0.0f;
    local_2c.y = 0.0f;
    local_2c.z = actor->speedF;
    MtxPosition(&local_2c, &local_38);
    actor->speed.x = local_38.x;
    actor->speed.z = local_38.z;
    if (((i_this->mAction != ACTION_BUNRI_MOVE) && (i_this->mAction != ACITON_FUJYOU_MOVE)) &&
        (i_this->mAction != ACTION_WIND_MOVE && (i_this->mAction != ACTION_DAMAGE_DEAD_MOVE)))
    {
        actor->speed.y = local_38.y;
    } else {
        actor->speed.y += actor->gravity;
        if (actor->speed.y < -20.0f) {
            actor->speed.y = -20.0f;
        }
    }
    fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
    if (((i_this->mAction == ACTION_HANE_MOVE) && (i_this->m0341 != 0)) && (actor->current.pos.y < i_this->m05BC.y + 40.0f)) {
        actor->current.pos.y = i_this->m05BC.y + 40.0f;
    }
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        cLib_addCalc2(&i_this->mHaniCheck.x, i_this->mHaniTarget.x, 0.3f, 3.0f);
        cLib_addCalc2(&i_this->mHaniCheck.y, i_this->mHaniTarget.y, 0.3f, 3.0f);
        cLib_addCalc2(&i_this->mHaniCheck.z, i_this->mHaniTarget.z, 0.3f, 3.0f);
    } else {
        cLib_addCalc2(&i_this->mHaniCheck.x, i_this->mHaniTarget.x, 1.0f, 30.0f);
        cLib_addCalc2(&i_this->mHaniCheck.y, i_this->mHaniTarget.y, 1.0f, 30.0f);
        cLib_addCalc2(&i_this->mHaniCheck.z, i_this->mHaniTarget.z, 1.0f, 30.0f);
        cLib_addCalc2(&actor->current.pos.x, actor->current.pos.x + i_this->mHaniCheck.x, 1.0f, 30.0f);
        cLib_addCalc2(&actor->current.pos.y, actor->current.pos.y + i_this->mHaniCheck.y, 1.0f, 30.0f);
        cLib_addCalc2(&actor->current.pos.z, actor->current.pos.z + i_this->mHaniCheck.z, 1.0f, 30.0f);
        cLib_addCalc0(&i_this->mHaniCheck.x, 1.0f, 30.0f);
        cLib_addCalc0(&i_this->mHaniCheck.y, 1.0f, 30.0f);
        cLib_addCalc0(&i_this->mHaniCheck.z, 1.0f, 30.0f);
    }
    i_this->mpBodyMorf->play(NULL, 0, 0);
    i_this->mpPropellerMorf->play(NULL, 0, 0);
    DW_draw_SUB(i_this);
    UP_draw_SUB(i_this);
    if (i_this->mAction != ACTION_DAMAGE_DEAD_MOVE) {
        if (i_this->mType == ACTOR_TYPE_PEAHAT) {
            i_this->mAtCyl.SetC(i_this->m02D8);
            i_this->mAtCyl.SetH(60.0f);
            i_this->mAtCyl.SetR(35.0f);
            dComIfG_Ccsp()->Set(&i_this->mAtCyl);
            i_this->mTgCyl.SetC(i_this->m02D8);
            i_this->mTgCyl.SetH(60.0f);
            i_this->mTgCyl.SetR(100.0f);
            dComIfG_Ccsp()->Set(&i_this->mTgCyl);
            i_this->mBodySph.SetC(i_this->m02CC);
            i_this->mBodySph.SetR(40.0f);
            dComIfG_Ccsp()->Set(&i_this->mBodySph);
        } else {
            local_2c = i_this->m02CC;
            local_2c.y -= REG8_F(10) + 150.0f;
            i_this->mTgCyl.SetC(local_2c);
            i_this->mTgCyl.SetH(REG8_F(12) + 500.0f);
            i_this->mTgCyl.SetR(REG8_F(13) + 500.0f);
            dComIfG_Ccsp()->Set(&i_this->mTgCyl);
            local_2c = i_this->m02CC;
            local_2c.y -= REG8_F(10) + 150.0f;
            i_this->mAtCyl.SetC(local_2c);
            i_this->mAtCyl.SetH(REG8_F(14) + 350.0f);
            i_this->mAtCyl.SetR(REG8_F(15) + 250.0f);
            dComIfG_Ccsp()->Set(&i_this->mAtCyl);
            i_this->mBodySph.SetC(i_this->m02CC);
            i_this->mBodySph.SetR(REG8_F(16) + 70.0f + i_this->m039C * (REG8_F(17) + 40.0f));
            dComIfG_Ccsp()->Set(&i_this->mBodySph);
        }
    }
    actor->attention_info.position = i_this->m02C0;
    if (i_this->mType == ACTOR_TYPE_SEAHAT) {
        actor->attention_info.position.y -= 100.0f;
    }
    BG_check(i_this);
    return TRUE;
}

/* 000061A4-000061AC       .text daPH_IsDelete__FP8ph_class */
static BOOL daPH_IsDelete(ph_class*) {
    return TRUE;
}

/* 000061AC-00006224       .text daPH_Delete__FP8ph_class */
static BOOL daPH_Delete(ph_class* i_this) {
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        dComIfG_resDeleteDemo(&i_this->mPhase, "PH");
    } else {
        dComIfG_resDeleteDemo(&i_this->mPhase, "SH");
    }
    i_this->mRippleCb.remove();
    enemy_fire_remove(&i_this->mBodyEnemyFire);
    enemy_fire_remove(&i_this->mPropellerEnemyFire);
    return TRUE;
}

/* 00006224-000062B4       .text useArrowHeapInit__FP10fopAc_ac_c */
static u8 useArrowHeapInit(fopAc_ac_c* a_this) {
    static Vec sph_offset[] = {{0.0f, 0.0f, 0.0f}};
    static Vec up_sph_offset[] = {{0.0f, -30.0f, 0.0f}};
    static __jnt_hit_data_c search_data_norm[] = {
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x00,
            /* mRadius     */ 26.0f,
            /* mpOffsets   */ sph_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x01,
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ up_sph_offset,
        },
    };
    static __jnt_hit_data_c search_data_sh[] = {
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x00,
            /* mRadius     */ 250.0f,
            /* mpOffsets   */ sph_offset,
        },
        {
            /* mShapeType  */ JntHitType_SPH_e,
            /* mJointIndex */ 0x01,
            /* mRadius     */ 150.0f,
            /* mpOffsets   */ up_sph_offset,
        },
    };

    ph_class* i_this = (ph_class*)a_this;

    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        i_this->mpJntHit = JntHit_create(i_this->mpBodyMorf->getModel(), search_data_norm, ARRAY_SIZE(search_data_norm));
    } else {
        i_this->mpJntHit = JntHit_create(i_this->mpBodyMorf->getModel(), search_data_sh, ARRAY_SIZE(search_data_sh));
    }
    if (i_this->mpJntHit != NULL) {
        fopAcM_SetJntHit(a_this, i_this->mpJntHit);
    } else {
        return FALSE;
    }
    return TRUE;
}

/* 000062B4-00006700       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    ph_class* i_this = (ph_class*)a_this;

    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        i_this->mpPropellerMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("PH", dRes_INDEX_PH_BDL_PHP_e),
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("PH", dRes_INDEX_PH_BCK_PFLY_e),
            J3DFrameCtrl::EMode_LOOP,
            1.0f,
            0,
            -1,
            1,
            NULL,
            0x00080000,
            0x37441422
        );
    } else {
        i_this->mpPropellerMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("SH", dRes_INDEX_SH_BMD_SHP_e),
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("SH", dRes_INDEX_SH_BCK_PFLY_e),
            J3DFrameCtrl::EMode_LOOP,
            1.0f,
            0,
            -1,
            1,
            NULL,
            0,
            0x11020203
        );
    }
    if ((i_this->mpPropellerMorf == NULL) || (i_this->mpPropellerMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpPropellerMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpPropellerMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpPropellerMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_UP);
    }
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        i_this->mpBodyMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("PH", dRes_INDEX_PH_BDL_PHB_e),
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("PH", dRes_INDEX_PH_BCK_BFLY_e),
            J3DFrameCtrl::EMode_LOOP,
            1.0f,
            0,
            -1,
            1,
            NULL,
            0x00080000,
            0x37441422
        );
    } else {
        i_this->mpBodyMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("SH", dRes_INDEX_SH_BMD_SHB_e),
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("SH", dRes_INDEX_SH_BCK_BFLY_e),
            J3DFrameCtrl::EMode_LOOP,
            1.0f,
            0,
            -1,
            1,
            NULL,
            0,
            0x11020203
        );
    }
    if ((i_this->mpBodyMorf == NULL) || (i_this->mpBodyMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpBodyMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpBodyMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpBodyMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_DW);
    }
    if (!i_this->mPropellerInvisibleModel.create(i_this->mpPropellerMorf->getModel())) {
        return FALSE;
    }
    if (!i_this->mBodyInvisibleModel.create(i_this->mpBodyMorf->getModel())) {
        return FALSE;
    }
    if (useArrowHeapInit(a_this)) {
        return TRUE;
    }
    return FALSE;
}

/* 00006700-00006D1C       .text daPH_Create__FP10fopAc_ac_c */
static cPhs_State daPH_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl at_hit_puropera_co_cyl = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */
            DEMO_SELECT(
                cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsPlayer_e,
                cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e
            ),
            /* SrcGObjAt Se      */ dCcG_SE_METAL,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK8,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcCyl tg_hit_puropera_co_cyl = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_NoTgHitInfSet_e,
            /* SrcObjTg  Type    */ AT_TYPE_SWORD | AT_TYPE_WIND,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsPlayer_e,
            /* SrcGObjAt Se      */ dCcG_SE_METAL,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_METAL,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
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
    static dCcD_SrcSph body_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK2000,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | DEMO_SELECT(cCcD_TgSPrm_GrpAll_e, cCcD_TgSPrm_IsEnemy_e),
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | DEMO_SELECT(cCcD_CoSPrm_VsEnemy_e, cCcD_CoSPrm_VsGrpAll_e),
            /* SrcGObjAt Se      */ dCcG_SE_UNK6,
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

    ph_class* i_this = (ph_class*)a_this;
    u32 uVar2;
    u32 uVar6;

    u32 maxHeapSize = 0x2740;
    i_this->mType = (u8)fopAcM_GetParam(a_this);
    if (i_this->mType == ACTOR_TYPE_DEFAULT) {
        i_this->mType = ACTOR_TYPE_PEAHAT;
    }
    if (REG8_S(9) != 0) {
        i_this->mType = ACTOR_TYPE_SEAHAT;
    }
    cPhs_State res;
    if (i_this->mType == ACTOR_TYPE_PEAHAT) {
        res = dComIfG_resLoad(&i_this->mPhase, "PH");
    } else {
        res = dComIfG_resLoad(&i_this->mPhase, "SH");
        maxHeapSize = DEMO_SELECT(0, 0x3E40);
    }
    if (res == cPhs_COMPLEATE_e) {
        fopAcM_ct(a_this, ph_class);
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, maxHeapSize)) {
            return cPhs_ERROR_e;
        }
        uVar6 = (fopAcM_GetParam(a_this) >> 8) & 0xFF;
        uVar2 = (fopAcM_GetParam(a_this) >> 0x10) & 0xFF;
        if (i_this->mType == ACTOR_TYPE_PEAHAT) {
            i_this->mHaniCheckDist2D = 1000.0f;
            i_this->mHaniCheckDist3D = 500.0f;
        } else {
            i_this->mHaniCheckDist2D = 12000.0f;
            i_this->mHaniCheckDist3D = 6000.0f;
            i_this->m039C = 8.0f;
            i_this->m03A0 = 5.0f;
            a_this->scale.setall(i_this->m039C + 1.0f);
        }
        if (uVar6 != 0xFF) {
            i_this->mHaniCheckDist2D = (f32)uVar6 * 100.0f;
        }
        if (uVar2 != 0xFF) {
            i_this->mHaniCheckDist3D = (f32)uVar2 * 100.0f;
        }
        i_this->m038C = i_this->mHaniCheckDist2D + 800.0f;
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        if (i_this->mType == ACTOR_TYPE_PEAHAT) {
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("p_hat", 0);
            a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 3;
            a_this->stealItemLeft = 1;
            i_this->m0344 = a_this->stealItemLeft;
        } else {
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("sea_hat", 0);
            a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x2A;
            a_this->gbaName = 0x1F;
        }
        fopAcM_SetMtx(a_this, i_this->mpBodyMorf->getModel()->getBaseTRMtx());
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mStts.Init(0x50, 4, a_this);
        a_this->max_health = 1;
        a_this->health = 1;
        i_this->m02FC = a_this->scale;
        i_this->mBodySph.Set(body_co_sph_src);
        i_this->mBodySph.SetStts(&i_this->mStts);
        i_this->mBodySph.OffCoSetBit();
        i_this->mAtCyl.Set(at_hit_puropera_co_cyl);
        i_this->mAtCyl.SetStts(&i_this->mStts);
        i_this->mTgCyl.Set(tg_hit_puropera_co_cyl);
        i_this->mTgCyl.SetStts(&i_this->mStts);
        i_this->mFuwafuwaValue[0] = (fopAcM_GetID(i_this) << 0xd) & 0x1FE000;
        i_this->mFuwafuwaValue[1] = (fopAcM_GetID(i_this) << 0xd) & 0x1FE000;
        i_this->mFuwafuwaValue[2] = (fopAcM_GetID(i_this) << 0xd) & 0x1FE000;
        i_this->mFuwafuwaValue[3] = (fopAcM_GetID(i_this) << 0xd) & 0x1FE000;
        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mWallRadius = 40.0f;
        i_this->mEnemyIce.mCylHeight = 40.0f;
        i_this->mEnemyIce.m1B0 = 1;
        i_this->mBodyEnemyFire.mpMcaMorf = i_this->mpBodyMorf;
        i_this->mBodyEnemyFire.mpActor = a_this;

        static u8 fire_j[ARRAY_SIZE(i_this->mBodyEnemyFire.mFlameJntIdxs)] = {
            0x00,
            0x01,
            0x02,
            0x03,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
            0xFF,
        };
        static f32 fire_sc[ARRAY_SIZE(i_this->mBodyEnemyFire.mParticleScale)] = {
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

        for (int i = 0; i < ARRAY_SIZE(i_this->mBodyEnemyFire.mFlameJntIdxs); i++) {
            i_this->mBodyEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mBodyEnemyFire.mParticleScale[i] = fire_sc[i];
            i_this->mBodyEnemyFire.mParticleScale[i] += i_this->m039C;
        }
        i_this->mPropellerEnemyFire.mpMcaMorf = i_this->mpPropellerMorf;
        i_this->mPropellerEnemyFire.mpActor = a_this;

        static u8 fire_j2[ARRAY_SIZE(i_this->mPropellerEnemyFire.mFlameJntIdxs)] = {
            0x00,
            0x01,
            0x03,
            0x04,
            0x05,
            0x07,
            0x08,
            0x09,
            0x0B,
            0x0C,
        };
        static f32 fire_sc2[ARRAY_SIZE(i_this->mPropellerEnemyFire.mParticleScale)] = {
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

        for (int i = 0; i < ARRAY_SIZE(i_this->mPropellerEnemyFire.mFlameJntIdxs); i++) {
            i_this->mPropellerEnemyFire.mFlameJntIdxs[i] = fire_j2[i];
            i_this->mPropellerEnemyFire.mParticleScale[i] = fire_sc2[i];
            i_this->mPropellerEnemyFire.mParticleScale[i] += i_this->m039C;
        }
        i_this->m0380 = 30.0f;
        a_this->gravity = -3.0f;
        BG_check(i_this);
        a_this->gravity = 0.0f;
        i_this->m032C = a_this->current.pos;
        anm_init(i_this, dRes_INDEX_PH_BCK_PFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 0);
        anm_init(i_this, dRes_INDEX_PH_BCK_BFLY_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1, 1);
        if (i_this->mType == ACTOR_TYPE_SEAHAT) {
            i_this->mAtCyl.SetAtSpl(dCcG_At_Spl_UNK9);
#if VERSION == VERSION_DEMO
            fopAcM_setCullSizeBox(a_this, -500.0f, -500.0f, -500.0f, 500.0f, 500.0f, 500.0f);
#else
            fopAcM_setCullSizeBox(a_this, -200.0f, -200.0f, -200.0f, 200.0f, 200.0f, 200.0f);
            fopAcM_setCullSizeFar(a_this, REG8_F(8) / mDoLib_clipper::getFar() + 10000.0f);
#endif
            i_this->mAction = ACTION_FLY_MOVE;
            i_this->mMode = MODE_FLY_MOVE_0;
            fopAcM_OffStatus(a_this, fopAcStts_UNK80000_e);
            i_this->m0341 = 1;
            i_this->m0380 = 100.0f;
            i_this->m02FC.setall(i_this->m03A0);
        } else {
            fopAcM_setCullSizeBox(a_this, -80.0f, -80.0f, -80.0f, 80.0f, 80.0f, 80.0f);
            i_this->mBodySph.SetTgType(
                AT_TYPE_BOMB | AT_TYPE_BOOMERANG | AT_TYPE_NORMAL_ARROW | AT_TYPE_HOOKSHOT | AT_TYPE_SKULL_HAMMER | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW |
                AT_TYPE_LIGHT_ARROW | AT_TYPE_GRAPPLING_HOOK
            );
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->m02FC.setall(0.0f);
                i_this->mAction = ACITON_FUJYOU_MOVE;
                i_this->mMode = MODE_FUJYOU_MOVE_30;
            }
        }
        i_this->mpBodyMorf->play(NULL, 0, 0);
        i_this->mpPropellerMorf->play(NULL, 0, 0);
        DW_draw_SUB(i_this);
        i_this->m0314 = i_this->m02C0;
        UP_draw_SUB(i_this);
    }
    return res;
}

static actor_method_class l_daPH_Method = {
    (process_method_func)daPH_Create,
    (process_method_func)daPH_Delete,
    (process_method_func)daPH_Execute,
    (process_method_func)daPH_IsDelete,
    (process_method_func)daPH_Draw,
};

actor_process_profile_definition g_profile_PH = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_PH_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(ph_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_PH_e,
    /* Actor SubMtd */ &l_daPH_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
