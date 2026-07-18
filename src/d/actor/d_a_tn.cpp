/**
 * d_a_tn.cpp
 * Enemy - Darknut / Mini-Boss - Darknut (Tower of the Gods) / タートナック (Taatonakku)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_tn.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_mant.h"
#include "d/actor/d_a_player.h"
#include "d/d_camera.h"
#include "d/d_jnt_hit.h"
#include "d/d_s_play.h"
#include "d/d_meter.h"
#include "d/d_snap.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_material.h"
#include "res/Object/Tn.h"
#include "JSystem/JUtility/JUTReport.h"

enum Action {
    ACTION_JYUNKAI = 0,
    ACTION_STAND = 1,
    ACTION_FIGHT_RUN = 4,
    ACTION_FIGHT = 5,
    ACTION_P_LOST = 8,
    ACTION_B_NIGE = 9,
    ACTION_DEFENCE = 10,
    ACTION_HUKKI = 11,
    ACTION_WEPON_SEARCH = 12,
    ACTION_AITE_MIRU = 14,
    ACTION_D_SIT = 17,
    ACTION_D_MAHI = 18,
    ACTION_FAIL = 20,
    ACTION_YOGAN_FAIL = 21,
    ACTION_D_DOZOU = 23,
    ACTION_S_DEMO = 25,
};

enum BehaviorType {
    BEHAVIOR_ROAMS_AROUND = 0,
    BEHAVIOR_GUARDS_AREA = 4,
    BEHAVIOR_UNK_12 = 12,
    BEHAVIOR_MINIBOSS = 13,
    BEHAVIOR_MSWORD_CHAMBER_AMBUSH = 14,
    BEHAVIOR_FROZEN_IN_TIME = 15,
};

enum EquipmentType {
    EQUIPMENT_NORMAL = 0,
    EQUIPMENT_HELMET = 1,
    EQUIPMENT_SHIELD = 2,
    EQUIPMENT_HELMET_AND_SHIELD = 3,
    EQUIPMENT_SHIELD_AND_CAPE = 4,
    EQUIPMENT_HELMET_SHIELD_AND_CAPE = 5,
};

enum RemainingEquipmentPieces {
    EQUIPMENT_PIECE_BODY_ARMOR = 1,
    EQUIPMENT_PIECE_HELMET = 2,
    EQUIPMENT_PIECE_SHIELD = 4,
    EQUIPMENT_PIECE_UNKNOWN = 8,
};

static bool hio_set;
static tnHIO_c l_tnHIO;
static s8 search_sp;
static fopAc_ac_c* target_info[10];
static s32 target_info_count;

static s8 joint_check[] = {-1,   -1,   0x0C, 0x0B, 0x07, 0x03, 0x0A, 0x06, 0x02, -1, 0x13, 0x09, 0x05, 0x01, 0x11, 0x64, 0x64,
                           0x64, 0x64, 0x08, 0x04, 0x00, 0x10, 0x14, -1,   -1,   -1, 0x0D, 0x12, -1,   -1,   -1,   -1};

static f32 joint_scale_x = 1.0f;
static f32 joint_scale_y = 1.0f;
static f32 joint_scale_z = 1.0f;

/* 000000EC-00000220       .text anm_init__FP8tn_classifUcfi */
static void anm_init(tn_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (i_this->m03EC == 0) {
        if (soundFileIdx >= 0) {
            i_this->mpBodyMorf->setAnm(
                (J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx),
                loopMode,
                morf,
                speed,
                0.0f,
                -1.0f,
                dComIfG_getObjectRes("Tn", soundFileIdx)
            );
        } else {
            i_this->mpBodyMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    }
}

/* 00000220-000002D4       .text tate_anm_init__FP8tn_classifUcf */
static void tate_anm_init(tn_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed) {
    if (i_this->m03EC == 0) {
        i_this->mpShieldMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000002D4-00000398       .text yoroi_anm_init__FP8tn_classifUcf */
static void yoroi_anm_init(tn_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed) {
    if (i_this->m03EC != 0 || !(i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR)) {
        return;
    }
    i_this->mpArmorMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
}

/* 00000398-00000730       .text yari_off_check__FP8tn_class */
static void yari_off_check(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->m0C38 == 0) {
        return;
    }

    fopAc_ac_c* boko_actor = fopAcM_SearchByID(i_this->mBokoPcId);
    daBoko_c* boko = (daBoko_c*)boko_actor;
    if (boko) {
        fopAcM_cancelCarryNow(boko_actor);

        if (i_this->m0C38 != 2) {
            boko->setRotAngleSpeed(cM_rndFX(2000.0f));
            s16 angleY = actor->shape_angle.y + 0x8000 + (s16)cM_rndFX(8000.0f);
            f32 speedY = 20.0f + cM_rndF(10.0f);
            f32 speedForward = 20.0f + cM_rndF(10.0f);
            boko->moveStateInit(speedForward, speedY, angleY);
        }

        cXyz offset;
        dBgS_LinChk linChk;
        linChk.Set(&actor->eyePos, &boko_actor->current.pos, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            MtxP mtx = i_this->mpBodyMorf->getModel()->getAnmMtx(TN_MAIN_JNT_J_TN_MUNE1_e);
            MTXCopy(mtx, *calc_mtx);
            boko->setMatrix(*calc_mtx);
            offset.set(0.0f, 0.0f, 0.0f);
            MtxPosition(&offset, &boko_actor->current.pos);
        }
        fopAcM_monsSeStart(actor, JA_SE_CV_TN_DROP_SWORD, 0);
    }

    i_this->m0C38 = 0;
    i_this->m0C34 = 0;
}

/* 00000BA4-00001074       .text smoke_set_s__FP8tn_classf */
static void smoke_set_s(tn_class* i_this, f32 rate) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    s32 attribCode;
    attribCode = 0;
    cXyz startPos = i_this->m041C;
    startPos.y += 100.0f;
    cXyz endPos = i_this->m041C;
    endPos.y -= 100.0f;
    linChk.Set(&startPos, &endPos, actor);

    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        endPos = linChk.GetCross();
        i_this->m041C.y = endPos.y;
        attribCode = dComIfG_Bgsp()->GetAttributeCode(linChk);
    } else {
        i_this->m041C.y -= 20000.0f;
    }

    if (i_this->m0433 != 0 && attribCode != dBgS_Attr_GRASS_e) {
        return;
    }

    i_this->m0433++;

    switch (attribCode) {
        case dBgS_Attr_NORMAL_e:
        case dBgS_Attr_DIRT_e:
        case dBgS_Attr_WOOD_e:
        case dBgS_Attr_STONE_e:
        case dBgS_Attr_SAND_e:
            {
                i_this->mSmokeCb1.remove();
                JPABaseEmitter* emitter1 = dComIfGp_particle_setToon(
                    dPa_name::ID_AK_JT_ELEMENTSMOKE00,
                    &i_this->m041C,
                    &i_this->m0428,
                    NULL,
                    l_tnHIO.m01E,
                    &i_this->mSmokeCb1,
                    fopAcM_GetRoomNo(actor)
                );
                if (emitter1) {
                    emitter1->setRate(rate);
                    emitter1->setSpread(1.0f);
                    JGeometry::TVec3<f32> scale;
                    scale.x = scale.y = scale.z = 1.0f + REG0_F(19);
                    emitter1->setGlobalDynamicsScale(scale);
                    scale.x = scale.y = scale.z = 3.0f + REG0_F(11);
                    emitter1->setGlobalParticleScale(scale);
                }
                break;
            }
        case dBgS_Attr_GRASS_e:
            JPABaseEmitter* emitter2 = dComIfGp_particle_set(dPa_name::ID_AK_JN_ELEMENTKUSA00, &i_this->m041C, &i_this->m0428);
            if (emitter2) {
                emitter2->setRate(rate * 0.5f);
                emitter2->setMaxFrame(3);
            }
            break;
    }
}

/* 00001074-00001244       .text ground_smoke_set__FP8tn_class */
static void ground_smoke_set(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_18;

    if (i_this->m0430 == 0) {
        return;
    }
    i_this->m0430--;
    if (i_this->m0430 >= l_tnHIO.m020) {
        i_this->m0428.x = 0;
        i_this->m0428.z = 0;
        local_18.x = 0.0f;
        local_18.y = 0.0f;
        MtxTrans(actor->current.pos.x, actor->current.pos.y + 7.5f, actor->current.pos.z, false);
        if (i_this->m0432 == 0) {
            local_18.z = REG0_F(4) + -200.0f;
            cMtx_YrotM(*calc_mtx, i_this->m042E);
            MtxPosition(&local_18, &i_this->m041C);
            i_this->m0428.y = i_this->m042E;
            smoke_set_s(i_this, REG0_F(15) + 3.0f);
            i_this->m042E = i_this->m042E + 2000 + REG0_S(7);
        } else if (i_this->m0432 == 1) {
            cMtx_YrotM(*calc_mtx, actor->current.angle.y);
            cMtx_YrotM(*calc_mtx, i_this->m042E);
            local_18.z = -55.0f;
            MtxPosition(&local_18, &i_this->m041C);
            i_this->m0428.y = i_this->m042E;
            smoke_set_s(i_this, REG0_F(20) + 4.0f);
            i_this->m042E += 0x1FA0;
        }
    } else {
        i_this->m041C.y = i_this->mDamageReaction.mSpawnY + 25000.0f;
    }
    if (i_this->m0430 == 0) {
        i_this->mSmokeCb1.remove();
        i_this->m0433 = 0;
    }
}

/* 00001244-0000149C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        int r28 = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();
        fopAc_ac_c* actor = &i_this->actor;
        if (i_this != NULL) {
            if (
                (jntNo >= TN_MAIN_JNT_J_TN_KATA_L1_e && jntNo < TN_MAIN_JNT_J_TN_YUBI_L2_e && (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD))
#if VERSION == VERSION_DEMO
                && i_this->mEnemyIce.mFreezeTimer == 0 && (i_this->mDamageReaction.mAction != ACTION_S_DEMO || i_this->m0414_demo == 0)
#else
                && i_this->mEnemyIce.mFreezeTimer == 0
#endif
            )
            {
                model->setAnmMtx(jntNo, i_this->mpShieldMorf->getModel()->getAnmMtx(jntNo));
            }
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (r28 < 100) {
                cMtx_YrotM(*calc_mtx, i_this->mDamageReaction.m088[r28].y);
                cMtx_XrotM(*calc_mtx, i_this->mDamageReaction.m088[r28].x);
                cMtx_ZrotM(*calc_mtx, i_this->mDamageReaction.m088[r28].z);
            }
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            cXyz offset;
            offset.x = 0.0f;
            offset.y = 0.0f;
            offset.z = 0.0f;
            cXyz local_38;
            if ((u32)r28 <= 6 || r28 == 7) {
                offset.x = 0.0f;
            } else if (r28 == 0x12) {
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 200.0f;
                MtxPosition(&offset, &local_38);
                offset.x = 0.0f;
                offset.y = 0.0f;
                offset.z = 0.0f;
                MtxPosition(&offset, &actor->eyePos);
                actor->attention_info.position = actor->eyePos;
                actor->attention_info.position.y += l_tnHIO.m024;
                i_this->m0414 = cM_atan2s(local_38.x - actor->eyePos.x, local_38.z - actor->eyePos.z);
                offset.x = 20.75f;
                offset.y = 0.0f;
                offset.z = 10.0f;
                MtxPosition(&offset, &i_this->m1384);
                offset.y = -45.0f;
            }
            if (r28 < 100) {
                MtxPosition(&offset, &i_this->mDamageReaction.m100[r28]);
            }
        }
    }
    return TRUE;
}

/* 0000149C-00001630       .text nodeCallBack_P__FP7J3DNodei */
static BOOL nodeCallBack_P(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        int r29 = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();
        if (i_this != NULL) {
            if (
                (jntNo >= TN_MAIN_JNT_J_TN_KATA_L1_e && jntNo < TN_MAIN_JNT_J_TN_YUBI_L2_e && (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD))
#if VERSION == VERSION_DEMO
                && i_this->mEnemyIce.mFreezeTimer == 0 && (i_this->mDamageReaction.mAction != ACTION_S_DEMO || i_this->m0414_demo == 0)
#else
                && i_this->mEnemyIce.mFreezeTimer == 0
#endif
            )
            {
                model->setAnmMtx(jntNo, i_this->mpShieldMorf->getModel()->getAnmMtx(jntNo));
                MTXCopy(model->getAnmMtx(jntNo), J3DSys::mCurrentMtx);
            }
            if (r29 < 100) {
                MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
                cXyz offset;
                offset.x = 0.0f;
                offset.z = 0.0f;
                offset.y = 0.0f;
                if (r29 == 0x11) {
                    offset.x = 17.5f;
                    offset.y = -8.75f;
                    offset.z = 0.0f;
                    MtxPosition(&offset, &i_this->m13A8);
                } else if (r29 == 0x10) {
                    MtxPosition(&offset, &i_this->m13B4);
                } else if (r29 == 0x14) {
                    offset.y = 0.0f;
                    MtxPosition(&offset, &i_this->m0C3C);
                    offset.x = -50.0f;
                    MtxPosition(&offset, &i_this->m139C);
                    offset.x = 165.0f;
                    MtxPosition(&offset, &i_this->m1390);
                }
                MtxPosition(&offset, &i_this->mDamageReaction.m100[r29]);
            }
        }
    }
    return TRUE;
}

/* 00001630-000016F0       .text nodeCallBack_mimi__FP7J3DNodei */
static BOOL nodeCallBack_mimi(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();
        if (i_this != NULL && (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_HELMET)) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cMtx_YrotM(*calc_mtx, -0x8000);
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 000016F0-00001770       .text nodeCallBack_kata__FP7J3DNodei */
static BOOL nodeCallBack_kata(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();
        model->setAnmMtx(jntNo, i_this->mpBodyMorf->getModel()->getAnmMtx(jntNo));
        MTXCopy(model->getAnmMtx(jntNo), J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 00001770-000018B0       .text part_draw__FP8tn_classSc */
static void part_draw(tn_class* i_this, s8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model;

    for (s32 i = 0; i < ARRAY_SSIZE(i_this->mParts); i++) {
        if (i_this->mParts[i].m08 >= 0) {
            if (i == 0) {
                if (param_2 != 0) {
                    dMat_control_c::iceEntryDL(i_this->mpArmorMorf, -1, NULL);
                } else {
                    model = i_this->mpArmorMorf->getModel();
                    i_this->mParts[i].mpPartBrkAnm->entry(model->getModelData());
                    g_env_light.setLightTevColorType(model, &actor->tevStr);
                    i_this->mpArmorMorf->entryDL();
                }
            } else if (i != 2 || (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD)) {
                model = i_this->mParts[i].mpPartModel;
                if (param_2 != 0) {
                    dMat_control_c::iceUpdateDL(model, -1, NULL);
                } else {
                    if (i < 3) {
                        i_this->mParts[i].mpPartBrkAnm->entry(model->getModelData());
                    }
                    g_env_light.setLightTevColorType(model, &actor->tevStr);
                    mDoExt_modelUpdateDL(model);
                }
            }
        }
    }
}

/* 000018B0-00001B7C       .text daTn_Draw__FP8tn_class */
static BOOL daTn_Draw(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_24;

    J3DModel* model = i_this->mpBodyMorf->getModel();
    if (i_this->m1518 != 0 || i_this->m02C1 != 0) {
        return TRUE;
    }
    if (i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(i_this->mpBodyMorf, -1, NULL);
        part_draw(i_this, 1);
        return TRUE;
    }
    if (i_this->mEquipmentType >= EQUIPMENT_SHIELD_AND_CAPE) {
        dSnap_RegistFig(DSNAP_TYPE_TN_MIGHTY, actor, 1.0f, 1.0f, 1.0f);
    } else if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD) {
        dSnap_RegistFig(DSNAP_TYPE_TN_SHIELD, actor, 1.0f, 1.0f, 1.0f);
    } else {
        dSnap_RegistFig(DSNAP_TYPE_TN_NO_SHIELD, actor, 1.0f, 1.0f, 1.0f);
    }
    g_env_light.setLightTevColorType(model, &actor->tevStr);
    i_this->mpBrkAnm->entry(model->getModelData());
    J3DShape* shape = model->getModelData()->getMaterialNodePointer(0)->getShape();
    if ((DEMO_SELECT(REG17_S(1), REG0_S(1)) != 0) || i_this->m1400 != 0) {
        shape->hide();
    } else {
        shape->show();
    }
    i_this->mpBodyMorf->entryDL();
    local_24.set(actor->current.pos.x, actor->current.pos.y + VERSION_SELECT(400.0f, 400.0f, 300.0f, 400.0f) + REG8_F(18), actor->current.pos.z);
    i_this->mShadowId = dComIfGd_setShadow(
        i_this->mShadowId,
        1,
        model,
        &local_24,
        REG8_F(19) + 1300.0f,
        200.0f,
        actor->current.pos.y,
        i_this->mDamageReaction.mAcch.GetGroundH(),
        i_this->mDamageReaction.mAcch.m_gnd,
        &actor->tevStr,
        0,
        1.0f,
        dDlst_shadowControl_c::getSimpleTex()
    );
    if (i_this->mShadowId != 0) {
        if (i_this->m0C34 != 0) {
            fopAc_ac_c* boko_actor = fopAcM_SearchByID(i_this->mBokoPcId);
            if (boko_actor != NULL && boko_actor->model != NULL) {
                dComIfGd_addRealShadow(i_this->mShadowId, boko_actor->model);
            }
        }
        if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_HELMET) {
            dComIfGd_addRealShadow(i_this->mShadowId, i_this->mParts[1].mpPartModel);
        }
        if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
            dComIfGd_addRealShadow(i_this->mShadowId, i_this->mpArmorMorf->getModel());
        }
        if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD) {
            dComIfGd_addRealShadow(i_this->mShadowId, i_this->mpShieldMorf->getModel());
        }
    }
    part_draw(i_this, 0);
    return TRUE;
}

/* 00001B7C-00002020       .text way_pos_check__FP8tn_classP4cXyz */
static void way_pos_check(tn_class* i_this, cXyz* r31) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    dBgS_GndChk gndChk;
    cXyz sp2C;
    cXyz sp20;
    cXyz sp14;
    cXyz sp08;
    sp2C.x = 0.0f;
    sp2C.y = 50.0f;
    sp14 = actor->current.pos;
    sp14.y += 50.0f;
    for (int i = 0; i < 100; i++) {
        sp2C.z = 300.0f + cM_rndF(200.0f);
        MtxRotY(cM_rndF(M_PI * 2), 0);
        MtxPosition(&sp2C, &sp20);
        sp08.x = actor->current.pos.x + sp20.x;
        sp08.y = actor->current.pos.y + sp20.y;
        sp08.z = actor->current.pos.z + sp20.z;
        *r31 = sp08;
        linChk.Set(&sp14, &sp08, actor);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            gndChk.SetPos(&sp08);
            if (i_this->mDamageReaction.mAcch.GetGroundH() - dComIfG_Bgsp()->GroundCross(&gndChk) < 200.0f) {
                break;
            }
        }
    }
}

/* 000021B8-00002480       .text ground_4_check__FP8tn_classisf */
static u8 ground_4_check(tn_class* i_this, int r18, s16 r20, f32 f29) {
    static f32 xad[] = {
        0.0f,
        0.0f,
        1.0f,
        -1.0f,
    };
    static f32 zad[] = {
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
    };
    static u8 check_bit[] = {
        0x01,
        0x02,
        0x04,
        0x08,
    };
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_GndChk gndChk;
    int i;
    u8 r19 = 0;
    cMtx_YrotS(*calc_mtx, r20);
    cXyz sp14;
    sp14.y = 100.0f;
    for (i = 0; i < r18; i++) {
        sp14.x = xad[i] * f29;
        sp14.z = zad[i] * f29;
        cXyz sp8;
        MtxPosition(&sp14, &sp8);
        sp8 += actor->current.pos;
        gndChk.SetPos(&sp8);
        sp8.y = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (sp8.y == -G_CM3D_F_INF) {
            sp8.y = G_CM3D_F_INF;
        }
        if (i_this->mDamageReaction.mAcch.GetGroundH() - sp8.y > 200.0f) {
            r19 |= check_bit[i];
        }
    }
    return r19;
}

/* 00002480-00002870       .text daTn_other_bg_check__FP8tn_classP10fopAc_ac_c */
static BOOL daTn_other_bg_check(tn_class* i_this, fopAc_ac_c* r23) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp08;
    if (r23) {
        sp08 = r23->current.pos;
        sp08.y += 50.0f;
        sp14 = actor->current.pos;
        sp14.y = actor->eyePos.y;
        linChk.Set(&sp14, &sp08, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00002870-0000289C       .text get_view_H__FP8tn_class */
static s16 get_view_H(tn_class* i_this) {
    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_HELMET) {
        return l_tnHIO.m036;
    }
    return l_tnHIO.m034;
}

/* 0000289C-00002918       .text s_w_sub__FPvPv */
static void* s_w_sub(void* param_1, void*) {
    if (fopAcM_IsActor(param_1) && fopAcM_GetName(param_1) == fpcNm_BOKO_e) {
        daBoko_c* boko = (daBoko_c*)param_1;
        if (!fopAcM_checkCarryNow(boko)) {
            if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
                target_info[target_info_count] = boko;
                target_info_count++;
            }
        }
    }
    return NULL;
}

/* 00002918-00002BF4       .text search_wepon__FP8tn_class */
static s32 search_wepon(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    target_info_count = 0;
    for (int i = 0; i < ARRAY_SIZE(target_info); i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(&s_w_sub, i_this);

    f32 f29 = 50.0f;
    if (target_info_count != 0) {
        fopAc_ac_c* r25;
        int i = 0;
        while (i < target_info_count) {
            r25 = target_info[i];
            cXyz sp18;
            sp18.x = r25->current.pos.x - actor->eyePos.x;
            sp18.y = 50.0f + r25->current.pos.y - actor->eyePos.y;
            sp18.z = r25->current.pos.z - actor->eyePos.z;
            f32 f4 = std::sqrtf(SQUARE(sp18.x) + SQUARE(sp18.z));
            if (f4 < f29 && !daTn_other_bg_check(i_this, r25)) {
                if (std::fabsf(r25->current.pos.y + 50.0f - actor->eyePos.y) <= l_tnHIO.m038) {
                    s16 angleDiff = i_this->m0414 - cM_atan2s(sp18.x, sp18.z);
                    if (angleDiff < 0) {
                        angleDiff = -angleDiff;
                    }
                    if ((u16)angleDiff < 0x1800) {
                        return fopAcM_GetID(r25);
                    }
                    cMtx_YrotS(*calc_mtx, -actor->current.angle.y);
                    cXyz sp0C;
                    MtxPosition(&sp18, &sp0C);
                    if (std::fabsf(sp0C.x) < l_tnHIO.m03C && std::fabsf(sp0C.y) < l_tnHIO.m040 && sp0C.z > l_tnHIO.m048 && sp0C.z < l_tnHIO.m044) {
                        return fopAcM_GetID(r25);
                    }
                }
            }
            i++;
            if (i == target_info_count) {
                i = 0;
                f29 += 50.0f;
                if (f29 > 1500.0f) {
                    return fpcM_ERROR_PROCESS_ID_e;
                }
            }
        }
    } else {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    return fpcM_ERROR_PROCESS_ID_e;
}

/* 00002BF4-00002C78       .text s_b_sub__FPvPv */
static void* s_b_sub(void* param_1, void*) {
    if (fopAcM_IsActor(param_1) && fopAcM_GetName(param_1) == fpcNm_BOMB_e) {
        daBomb_c* bomb = (daBomb_c*)param_1;
        if (!bomb->chk_state(daBomb_c::STATE_0)) {
            if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
                target_info[target_info_count] = bomb;
                target_info_count++;
            }
        }
    }
    return NULL;
}

/* 00002C78-00002F84       .text search_bomb__FP8tn_classi */
static fopAc_ac_c* search_bomb(tn_class* i_this, int r26) {
    fopAc_ac_c* actor = &i_this->actor;
    if (!(i_this->m141C & 0x0200)) {
        return NULL;
    }

    target_info_count = 0;
    for (int i = 0; i < ARRAY_SIZE(target_info); i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(&s_b_sub, i_this);

    f32 f29 = 50.0f;
    if (target_info_count != 0) {
        fopAc_ac_c* r24;
        int i = 0;
        while (i < target_info_count) {
            r24 = target_info[i];
            cXyz sp28;
            sp28.x = r24->current.pos.x - actor->current.pos.x;
            sp28.y = 50.0f + r24->current.pos.y - actor->eyePos.y;
            sp28.z = r24->current.pos.z - actor->current.pos.z;
            f32 f0 = std::sqrtf(sp28.x * sp28.x + sp28.z * sp28.z);
            if (f0 < f29 && !(f0 > 30.0f + i_this->mPlayerDistance) && (!daTn_other_bg_check(i_this, r24) || !r26)) {
                if (r26) {
                    if (std::fabsf(r24->current.pos.y + 50.0f - actor->eyePos.y) <= l_tnHIO.m038) {
                        s16 angleDiff = i_this->m0414 - cM_atan2s(sp28.x, sp28.z);
                        if (angleDiff < 0) {
                            angleDiff = -angleDiff;
                        }
                        if ((u16)angleDiff < get_view_H(i_this)) {
                            return r24;
                        }
                        cMtx_YrotS(*calc_mtx, -actor->current.angle.y);
                        cXyz sp10;
                        MtxPosition(&sp28, &sp10);
                        if (std::fabsf(sp10.x) < l_tnHIO.m03C && std::fabsf(sp10.y) < l_tnHIO.m040 && sp10.z > l_tnHIO.m048 && sp10.z < l_tnHIO.m044) {
                            return r24;
                        }
                    }
                } else {
                    return r24;
                }
            }
            i++;
            if (i == target_info_count) {
                i = 0;
                f29 += 50.0f;
                if (f29 > 1500.0f) {
                    return NULL;
                }
            }
        }
    } else {
        return NULL;
    }

    return NULL;
}

/* 00002F84-00002FD8       .text daTn_bomb_view_check__FP8tn_class */
static BOOL daTn_bomb_view_check(tn_class* i_this) {
    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
        return FALSE;
    }
    i_this->m1418 = search_bomb(i_this, 1);
    return i_this->m1418 != NULL ? TRUE : FALSE;
}

/* 00002FD8-00003018       .text daTn_bomb_check__FP8tn_class */
static BOOL daTn_bomb_check(tn_class* i_this) {
    i_this->m1418 = search_bomb(i_this, 0);
    if (i_this->m1418) {
        return TRUE;
    }
    return FALSE;
}

/* 00003018-00003094       .text daTn_wepon_view_check__FP8tn_class */
static BOOL daTn_wepon_view_check(tn_class* i_this) {
    if (i_this->m03FC != 0) {
        return FALSE;
    }
    i_this->mBokoPcId = search_wepon(i_this);
    if (i_this->mBokoPcId != fpcM_ERROR_PROCESS_ID_e) {
        if (fopAcM_SearchByID(i_this->mBokoPcId)) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00003094-000033E8       .text daTn_player_bg_check__FP8tn_classP4cXyz */
static s32 daTn_player_bg_check(tn_class* i_this, cXyz* r23) {
    fopAc_ac_c* actor = &i_this->actor;
    if (search_sp != 0) {
        return FALSE;
    }
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp08;
    sp08 = *r23;
    sp08.y += 75.0f;
    sp14 = actor->current.pos;
    sp14.y = actor->eyePos.y;
    linChk.Set(&sp14, &sp08, actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        i_this->mDamageReaction.m713 = 0;
        return TRUE;
    }
    return FALSE;
}

/* 000033E8-00003598       .text daTn_player_view_check__FP8tn_classP4cXyzss */
static BOOL daTn_player_view_check(tn_class* i_this, cXyz* r30, s16 r27, s16 r31) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (search_sp != 0) {
        return TRUE;
    }
    if (daTn_player_bg_check(i_this, r30)) {
        return FALSE;
    }
    if (std::fabsf(player->current.pos.y + 50.0f - actor->eyePos.y) > l_tnHIO.m038) {
        return FALSE;
    }
    s16 angleDiff = i_this->m0414 - r27;
    if (angleDiff < 0) {
        angleDiff = -angleDiff;
    }
    if ((u16)angleDiff < r31) {
        i_this->mDamageReaction.m713 = 1;
        return TRUE;
    }
    cMtx_YrotS(*calc_mtx, -actor->current.angle.y);
    cXyz sp14;
    sp14.x = r30->x - actor->current.pos.x;
    sp14.y = r30->y - actor->current.pos.y;
    sp14.z = r30->z - actor->current.pos.z;
    cXyz sp08;
    MtxPosition(&sp14, &sp08);
    if (std::fabsf(sp08.x) < l_tnHIO.m03C && std::fabsf(sp08.y) < l_tnHIO.m040 && sp08.z > l_tnHIO.m048 && sp08.z < l_tnHIO.m044) {
        i_this->mDamageReaction.m713 = 2;
        return TRUE;
    } else {
        i_this->mDamageReaction.m713 = 0;
        return FALSE;
    }
}

/* 00003598-000035DC       .text daTn_player_way_check__FP8tn_class */
static BOOL daTn_player_way_check(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    s16 angleDiff = actor->current.angle.y - player->shape_angle.y;
    if (angleDiff < 0) {
        angleDiff = -angleDiff;
    }
    if ((u16)angleDiff < 0x4000) {
        return FALSE;
    }
    return TRUE;
}

/* 000035DC-00003664       .text wait_set__FP8tn_class */
static void wait_set(tn_class* i_this) {
    anm_init(i_this, dRes_INDEX_TN_BCK_AKYORO1_e, 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
    yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKYORO1_e, 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f);
    i_this->mCountDownTimers[1] = cM_rndF(30.0f) + 50.0f;
}

/* 00003664-000036CC       .text walk_set__FP8tn_class */
static void walk_set(tn_class* i_this) {
    anm_init(i_this, dRes_INDEX_TN_BCK_AWALK1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_AWALK1_e);
    yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YWALK1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f);
}

/* 000036CC-0000379C       .text fight_run_set__FP8tn_class */
static void fight_run_set(tn_class* i_this) {
    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
        anm_init(i_this, dRes_INDEX_TN_BCK_AWALK1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.5f, dRes_INDEX_TN_BAS_AWALK1_e);
        yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YWALK1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.5f);
    } else {
        if (i_this->m0C34 != 0) {
            anm_init(i_this, dRes_INDEX_TN_BCK_BRUN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_BRUN1_e);
        } else {
            anm_init(i_this, dRes_INDEX_TN_BCK_BRUN2_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_BRUN2_e);
        }
        yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIHON1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
    }
}

/* 0000379C-00003C0C       .text path_check__FP8tn_class */
static void path_check(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    static u8 check_index[255];
    cXyz local_c8;
    cXyz local_d4;

    if (i_this->ppd != NULL && (i_this->m0C34 != 0 || i_this->m13FF != 0)) {
        dBgS_LinChk chk;
        local_c8 = actor->current.pos;
        local_c8.y += 100.0f;
        dPnt* point = &i_this->ppd->m_points[0];
        for (s32 i = 0; i < i_this->ppd->m_num; i++, point++) {
            local_d4.x = point->m_position.x;
            local_d4.y = (100.0f + point->m_position.y);
            local_d4.z = point->m_position.z;
            chk.Set(&local_c8, &local_d4, actor);
            if (!dComIfG_Bgsp()->LineCross(&chk)) {
                check_index[i] = 1;
            } else {
                check_index[i] = 0;
            }
        }

        f32 fDist = 0.0f;
        bool r7 = false;

        for (s32 j = 0; j < 100; j++) {
            point = &i_this->ppd->m_points[0];

            for (s32 i = 0; i < i_this->ppd->m_num; i++, point++) {
                if (check_index[i] != 0) {
                    f32 x = actor->current.pos.x - point->m_position.x;
                    f32 y = actor->current.pos.y - point->m_position.y;
                    f32 z = actor->current.pos.z - point->m_position.z;

                    if (std::sqrtf(SQUARE(x) + SQUARE(y) + SQUARE(z)) < fDist) {
                        i_this->m1425 = i - (u8)i_this->m1426;
                        if (i_this->m1425 >= (s8)i_this->ppd->m_num) {
                            i_this->m1425 = i_this->ppd->m_num;
                        } else if (i_this->m1425 < 0) {
                            i_this->m1425 = 0;
                        }
                        r7 = true;
                        break;
                    }
                }
            }

            if (r7) {
                break;
            }

            fDist += 50.0f;
        }
        if (!r7) {
            i_this->m1424 = 0;
        } else {
            i_this->m1424 = i_this->mPathIndex + 1;
        }
    }
}

static s8 s_check;

/* 00003C0C-00004388       .text jyunkai__FP8tn_class */
static void jyunkai(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 maxSpeed;
    f32 f31;
    cXyz local_3c;

    if (i_this->mBehaviorType == BEHAVIOR_GUARDS_AREA) {
        i_this->mDamageReaction.mAction = ACTION_STAND;
        i_this->mDamageReaction.mMode = 0x32;
        return;
    }
    i_this->mCoCyl.SetR(REG0_F(14) + 40.0f);
    switch (i_this->mDamageReaction.mMode) {
        case -10:
            i_this->mCountDownTimers[1] = 60;
            i_this->mDamageReaction.mMode = -9;
        // Fall-through
        case -9:
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->mDamageReaction.mMode = 2;
            }
            actor->speedF = 0.0f;
            if (i_this->mCountDownTimers[1] > 30) {
                return;
            }
            break;
        case 0:
            walk_set(i_this);
        // Fall-through
        case -1:
            i_this->mDamageReaction.mMode = 1;
            if (i_this->m0C34 != 0 || i_this->m13FF != 0) {
                if (i_this->m1424 != 0) {
                    i_this->m1425 += i_this->m1426;
                    if (i_this->m1425 >= (s8)i_this->ppd->m_num) {
                        if (dPath_ChkClose(i_this->ppd)) {
                            i_this->m1425 = 0;
                        } else {
                            i_this->m1426 = -1;
                            i_this->m1425 = i_this->ppd->m_num - 2;
                        }
                        if ((s32)i_this->ppd->m_nextID != 0xFFFF) {
                            i_this->ppd = dPath_GetRoomPath(i_this->ppd->m_nextID, fopAcM_GetRoomNo(actor));
                            JUT_ASSERT(VERSION_SELECT(1974, 1979, 1986, 1986), i_this->ppd != NULL);
                        }
                    } else if (i_this->m1425 < 0) {
                        i_this->m1426 = 1;
                        i_this->m1425 = 1;
                    }
                    dPnt* point = &i_this->ppd->m_points[i_this->m1425];
                    i_this->mPathXyz = point->m_position;
                } else {
                    way_pos_check(i_this, &i_this->mPathXyz);
                }
            } else {
                way_pos_check(i_this, &i_this->mPathXyz);
                i_this->mCountDownTimers[1] = cM_rndF(25.0f) + 30.0f;
            }
            i_this->mCountDownTimers[2] = 30;
        // Fall-through
        case 1:
            if (i_this->m0C34 != 0 || i_this->m13FF != 0) {
                maxSpeed = 0x400;
                f31 = l_tnHIO.m04C;
            } else {
                maxSpeed = 0x1000;
                f31 = l_tnHIO.m050;
            }
            local_3c.x = i_this->mPathXyz.x - actor->current.pos.x;
            local_3c.z = i_this->mPathXyz.z - actor->current.pos.z;
            i_this->mDamageReaction.m4D0 = cM_atan2s(local_3c.x, local_3c.z);
            if (i_this->m1424 != 0 && (i_this->m0C34 != 0 || i_this->m13FF != 0)) {
                if (std::sqrtf(SQUARE(local_3c.x) + SQUARE(local_3c.z)) < (f31 * 0.25f) * 15.0f) {
                    dPnt* point = i_this->ppd->m_points;
                    point = &point[i_this->m1425];
                    if (point->mArg3 == 3 || point->mArg3 == 7 || point->mArg3 == 8) {
                        wait_set(i_this);
                        if (point->mArg3 >= 7) {
                            i_this->mCountDownTimers[1] = cM_rndF(80.0f) + 70.0f;
                        }
                        i_this->mDamageReaction.mMode = 2;
                    } else {
                        i_this->mDamageReaction.mMode = -1;
                    }
                }
            } else {
                if ((std::sqrtf(SQUARE(local_3c.x) + SQUARE(local_3c.z)) < (f31 * 0.25f) * 2.0f) ||
                    (i_this->mCountDownTimers[2] == 0 &&
                    (i_this->mDamageReaction.mAcch.ChkWallHit() || ground_4_check(i_this, 1, actor->current.angle.y, 200.0f))))
                {
                    wait_set(i_this);
                    i_this->mDamageReaction.mMode = 2;
                }
            }
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, maxSpeed);
            cLib_addCalc2(&actor->speedF, f31, 1.0f, 5.0f);
            break;
        case 2:
            actor->speedF = 0.0f;
            if (i_this->mCountDownTimers[1] == 0) {
                if (i_this->m1424 != 0 && (i_this->m0C34 != 0 || i_this->m13FF != 0)) {
                    dPnt* point = i_this->ppd->m_points;
                    point = &point[i_this->m1425];
                    if (point->mArg3 == 7 || point->mArg3 == 8) {
                        i_this->mDamageReaction.mMode = 4;
                        i_this->mCountDownTimers[1] = cM_rndF(100.0f) + 100.0f;
                        if (point->mArg3 == 7) {
                            i_this->mDamageReaction.m4D0 += -0x4000;
                        } else {
                            i_this->mDamageReaction.m4D0 += 0x4000;
                        }
                        break;
                    }
                }
                i_this->mDamageReaction.mMode = 0;
                if (i_this->m0C34 == 0 && i_this->m13FF == 0 && i_this->m03EA == 0) {
                    i_this->m13FF = 1;
                }
            }
            break;
        case 4:
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x1000);
        // Fall-through
        case 3:
            actor->speedF = 0.0f;
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->mDamageReaction.mMode = 0;
            }
            break;
    }
    s32 r3 = fopAcM_otoCheck(actor, 1000.0f);
    if (i_this->mMantPcId != 0xFFFF) {
        mant_class* mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
        if (mant_actor != NULL && mant_actor->m1C0E != 0) {
            r3 |= 2;
        }
    }
    r3 += search_sp;
    if (i_this->m0C34 != 0 || i_this->m13FF != 0) {
        if (r3 != 0 || (i_this->mPlayerDistance < l_tnHIO.m028 &&
                        daTn_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->mTargetAngle, get_view_H(i_this))))
        {
            i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
            i_this->mDamageReaction.mMode = -10;
            fopAcM_monsSeStart(actor, JA_SE_CV_TN_FOUND, 0);
        }
    }
    if (i_this->m0C34 == 0 && daTn_wepon_view_check(i_this)) {
        i_this->mDamageReaction.mAction = ACTION_WEPON_SEARCH;
        i_this->mDamageReaction.mMode = -1;
    }
    if (daTn_bomb_view_check(i_this)) {
        i_this->mDamageReaction.mAction = ACTION_B_NIGE;
        i_this->mDamageReaction.mMode = 0;
    }
}

/* 00004388-000043D4       .text shot_s_sub__FPvPv */
static void* shot_s_sub(void* param_1, void*) {
    if (fopAcM_IsActor(param_1) && fopAcM_GetName(param_1) == fpcNm_HIMO2_e) {
        return param_1;
    }
    return NULL;
}

/* 000043D4-00004CFC       .text fight_run__FP8tn_class */
static void fight_run(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 maxSpeed;
    cXyz local_54;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 stickPosX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    i_this->mDamageReaction.m710 = 1;
    i_this->mDamageReaction.m4D0 = i_this->mTargetAngle;
    if (i_this->m03EC == 0 && i_this->mDamageReaction.mMode != 0) {
        maxSpeed = 0x400;
        if (i_this->mDamageReaction.mMode == 1) {
            maxSpeed = 0x800;
        }
        cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, maxSpeed);
    }
    switch (i_this->mDamageReaction.mMode) {
        case -10:
            if (i_this->mCountDownTimers[4] == 0) {
                anm_init(i_this, dRes_INDEX_TN_BCK_AKIDUKU1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIDUKU1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                i_this->mDamageReaction.mMode = -9;
            } else {
                i_this->mDamageReaction.mMode = 0;
                i_this->mCountDownTimers[1] = 0;
            }
            break;
        case -9:
            actor->speedF = 0.0f;
            if (i_this->mpBodyMorf->isStop()) {
                i_this->mDamageReaction.mMode = 0;
                i_this->mCountDownTimers[1] = 0;
                break;
            }
            break;
        case 0:
            if (i_this->mCountDownTimers[1] == 0) {
                fight_run_set(i_this);
                i_this->mDamageReaction.mMode = 1;
                i_this->m1420 = 0;
            } else {
                actor->speedF = 0.0f;
                break;
            }
        case 1:
            {
                f32 f1 = (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) ? l_tnHIO.m04C * 1.5f : l_tnHIO.m054;
                f32 f3 = 5.0f;
                cLib_addCalc2(&actor->speedF, f1, 1.0f, f3);
                if (daTn_player_way_check(i_this)) {
                    if (i_this->mPlayerDistance < l_tnHIO.m02C) {
                        i_this->mDamageReaction.mMode = 2;
                        i_this->mCountDownTimers[3] = 40;
                        break;
                    }
                } else if (i_this->mPlayerDistance < l_tnHIO.m030) {
                    i_this->mDamageReaction.mAction = ACTION_FIGHT;
                    i_this->mDamageReaction.mMode = 0;
                    return;
                }
                break;
            }
        case 2:
            if (std::fabsf(stickPosX) > 0.1f) {
                if (i_this->m0C34 != 0) {
                    anm_init(i_this, dRes_INDEX_TN_BCK_ASURI_LR1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_ASURI_LR1_e);
                } else {
                    anm_init(i_this, dRes_INDEX_TN_BCK_BSURI_SLR1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_BSURI_SLR1_e);
                }
                if (stickPosX > 0.0f) {
                    i_this->mDamageReaction.mMode = 5;
                } else {
                    i_this->mDamageReaction.mMode = 6;
                }
            } else {
                if (i_this->m0C34 != 0) {
                    anm_init(i_this, dRes_INDEX_TN_BCK_ASURI_FB1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_ASURI_FB1_e);
                } else {
                    anm_init(i_this, dRes_INDEX_TN_BCK_BSURI_SFB1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_BSURI_SFB1_e);
                }
                if (i_this->mPlayerDistance < l_tnHIO.m030) {
                    i_this->mDamageReaction.mMode = 4;
                } else {
                    i_this->mDamageReaction.mMode = 3;
                }
            }
            i_this->mCountDownTimers[1] = cM_rndF(20.0f) + 20.0f;
            break;
        case 3:
            cLib_addCalc2(&actor->speedF, l_tnHIO.m05C, 1.0f, 20.0f);
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->mDamageReaction.mMode = 2;
            }
            break;
        case 4:
            if (i_this->m03FE != 2) {
                cLib_addCalc2(&actor->speedF, -l_tnHIO.m05C, 1.0f, 20.0f);
                if (i_this->mCountDownTimers[1] == 0) {
                    i_this->mDamageReaction.mMode = 2;
                }
            } else {
                i_this->mDamageReaction.mMode = 3;
                anm_init(i_this, dRes_INDEX_TN_BCK_AWALK1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_AWALK1_e);
            }
            break;
        case 5:
            if (i_this->m03FE != 4) {
                i_this->m0418 = 0x4000;
            } else {
                i_this->mDamageReaction.mMode = 6;
                i_this->m0418 = -0x4000;
            }
            goto temp_434;
        case 6:
            if (i_this->m03FE != 8) {
                i_this->m0418 = -0x4000;
            } else {
                i_this->mDamageReaction.mMode = 5;
                i_this->m0418 = 0x4000;
            }
        temp_434:
            cLib_addCalc2(&actor->speedF, l_tnHIO.m060, 1.0f, 30.0f);
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->mDamageReaction.mMode = 2;
            }
            break;
        case 8:
            actor->speedF = 0.0f;
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->mDamageReaction.mMode = 2;
            }
            break;
    }
    if (i_this->mDamageReaction.mMode >= 3) {
        if (i_this->mPlayerDistance > l_tnHIO.m02C + 75.0f) {
            i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
            path_check(i_this);
            wait_set(i_this);
            i_this->mDamageReaction.mMode = 0;
            return;
        }
        if (i_this->m0C34 != 0 && player->checkCutCharge()) {
            i_this->mDamageReaction.mAction = ACTION_FIGHT;
            i_this->mDamageReaction.mMode = 10;
            return;
        }
        if (((i_this->mPlayerDistance < l_tnHIO.m030 + 62.5f) && (i_this->mPlayerDistance > l_tnHIO.m030 - 62.5f)) && i_this->mCountDownTimers[3] == 0) {
            i_this->mCountDownTimers[3] = l_tnHIO.m06C;
            if (cM_rndF(100.0f) < l_tnHIO.m070) {
                i_this->mDamageReaction.mAction = ACTION_FIGHT;
                i_this->mDamageReaction.mMode = 0;
                return;
            }
        }
        if (i_this->m03F2 == 0) {
            bool r27 = false;
            fopAc_ac_c* r28 = (fopAc_ac_c*)fpcM_Search(shot_s_sub, i_this);
            if (r28 != NULL && r28->speedF > 10.0f) {
                local_54 = r28->current.pos - actor->eyePos;
                if (local_54.abs() < r28->speedF * 10.0f) {
                    r27 = true;
                }
            }
            dAttention_c& attention = dComIfGp_getAttention();
            if (daTn_player_way_check(i_this) &&
                (r27 || (player->getCutType() != daPy_py_c::CUT_TYPE_NONE && attention.Lockon() && actor == attention.LockonTarget(0))))
            {
                if (!(i_this->m03D8 & 3) && ((i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD) && cM_rndF(1.0f) <= 0.8f)) {
                    i_this->mDamageReaction.mAction = ACTION_DEFENCE;
                    i_this->mDamageReaction.mMode = 0;
                    if (player->getCutType() == daPy_py_c::CUT_TYPE_JUMPCUT_SWORD) {
                        i_this->mCountDownTimers[1] = 30;
                    } else {
                        i_this->mCountDownTimers[1] = 15;
                    }
                    fopAcM_monsSeStart(actor, JA_SE_CV_TN_GUARD, 0);
                    return;
                }
                if (!(i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR)) {
                    i_this->mDamageReaction.mAction = ACTION_FIGHT;
                    i_this->mDamageReaction.mMode = -0x14;
                    i_this->m03F0 = 10;
                    if (i_this->m0C34 != 0) {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BBACK1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BBACK1_e);
                    } else {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BBACK_S1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BBACK_S1_e);
                    }
                    actor->speedF = REG0_F(3) + -60.0f;
                    actor->speed.y = REG0_F(4) + 80.0f;
                    fopAcM_monsSeStart(actor, JA_SE_CV_TN_JUMP, 0);
                    return;
                }
            }
        }
    }
    if (daTn_player_bg_check(i_this, &i_this->mDamageReaction.m714->current.pos)) {
        i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
        path_check(i_this);
        wait_set(i_this);
        i_this->mDamageReaction.mMode = -10;
    } else {
        if (i_this->m0C34 == 0 && daTn_wepon_view_check(i_this)) {
            i_this->mDamageReaction.mAction = ACTION_WEPON_SEARCH;
            i_this->mDamageReaction.mMode = -1;
        }
        if (daTn_bomb_view_check(i_this)) {
            i_this->mDamageReaction.mAction = ACTION_B_NIGE;
            i_this->mDamageReaction.mMode = 0;
        }
        i_this->m03FE = ground_4_check(i_this, 4, actor->current.angle.y, REG6_F(7) + 90.0f);
        i_this->mCountDownTimers[4] = 50;
    }
}

/* 00004CFC-00005098       .text wepon_hit_check__FP8tn_class */
static fopAc_ac_c* wepon_hit_check(tn_class* i_this) {
    static int atp_0[] = {2, 2, 1, 2, 8, 8};
    static int atp_1[] = {4, 4, 2, 4, DEMO_SELECT(16, 12), DEMO_SELECT(16, 12)};

    int atp;
    int frame;
    int r5;
    int r6;
    cXyz local_28;

    i_this->m13FC = 0;
    i_this->m13D8 = i_this->mWeponSphMove;
    frame = (int)i_this->mpBodyMorf->getFrame();
    if (i_this->m0C48 == 0) {
        r5 = 19;
        r6 = 26;
    } else if (i_this->m0C48 == 1) {
        if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
            r5 = 19;
            r6 = 28;
        } else {
            r5 = 14;
            r6 = 23;
        }
    } else if (i_this->m0C48 == 2) {
        r5 = 7;
        r6 = 9;
    } else if (i_this->m0C48 == 3) {
        r5 = 20;
        r6 = 24;
    } else if (i_this->m0C48 == 4) {
        r5 = 20;
        r6 = 26;
    } else if (i_this->m0C48 == 5) {
        r5 = 0;
        r6 = 1000;
    }
    if (frame < r5 || frame > r6) {
        return NULL;
    }
    if (i_this->m0C66 < 0) {
        return NULL;
    }
    if (i_this->mEquipmentType & EQUIPMENT_HELMET) {
        atp = atp_1[i_this->m0C48];
    } else {
        atp = atp_0[i_this->m0C48];
    }
    i_this->mWeponSph.SetAtAtp(atp);
    i_this->mWepon2Sph.SetAtAtp(atp);
    if (i_this->m0C48 == 3) {
        MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(TN_MAIN_JNT_J_TN_ASI_L3_e), *calc_mtx);
        local_28.set(0.0f, 0.0f, 0.0f);
    } else {
        MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(TN_MAIN_JNT_J_TN_ITEM_R1_e), *calc_mtx);
        if (i_this->m0C48 == 2) {
            local_28.set(0.0f, 0.0f, 0.0f);
        } else {
            local_28.set(0.0f, 0.0f, 150.0f);
        }
    }
    MtxPosition(&local_28, &i_this->mWeponSphMove);
    local_28.z *= 0.3333f;
    MtxPosition(&local_28, &i_this->mWepon2SphMove);
    i_this->mWeponSph.SetAtType(AT_TYPE_UNK8);
    i_this->mWepon2Sph.SetAtType(AT_TYPE_UNK8);
    if (i_this->m13FD == 0) {
        i_this->m13FD++;
        i_this->mWeponSph.StartCAt(i_this->mWeponSphMove);
        i_this->mWepon2Sph.StartCAt(i_this->mWepon2SphMove);
    } else {
        i_this->mWeponSph.SetR(REG0_F(13) + 60.0f);
        i_this->mWeponSph.MoveCAt(i_this->mWeponSphMove);
        i_this->mWepon2Sph.MoveCAt(i_this->mWepon2SphMove);
        i_this->mWepon2Sph.SetR(REG0_F(14) + 40.0f);
        if (i_this->m0C48 <= 1) {
            i_this->mWeponSph.SetAtSpl(dCcG_At_Spl_UNK6);
            i_this->mWepon2Sph.SetAtSpl(dCcG_At_Spl_UNK6);
        } else if (i_this->m0C48 == 4 || i_this->m0C48 == 5) {
            i_this->mWeponSph.SetAtSpl(dCcG_At_Spl_UNK7);
            i_this->mWepon2Sph.SetAtSpl(dCcG_At_Spl_UNK7);
        } else {
            i_this->mWeponSph.SetAtSpl(dCcG_At_Spl_UNK0);
            i_this->mWepon2Sph.SetAtSpl(dCcG_At_Spl_UNK0);
        }
        dComIfG_Ccsp()->Set(&i_this->mWeponSph);
        dComIfG_Ccsp()->Set(&i_this->mWepon2Sph);
        if (i_this->mWeponSph.ChkAtHit() || i_this->mWepon2Sph.ChkAtHit()) {
            cCcD_Obj* hitObj;
            if (i_this->mWeponSph.ChkAtHit()) {
                hitObj = i_this->mWeponSph.GetAtHitObj();
            } else {
                hitObj = i_this->mWepon2Sph.GetAtHitObj();
            }
            if (hitObj != NULL) {
                return dCc_GetAc(hitObj->GetAc());
            }
            JUTReport(440, 220, "TN AT HITOBJ NON");
        }
    }
    return NULL;
}

/* 00005098-00005EB0       .text fight__FP8tn_class */
static void fight(tn_class* i_this) {
    fopEn_enemy_c* actor = &i_this->actor;
    int frame;
    u8 attackType;
    f32 f31;
    f32 f30;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s8 r29 = false;
    s8 r27 = false;
    f31 = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    i_this->mDamageReaction.m710 = 1;
    if ((player->getCutType() == daPy_py_c::CUT_TYPE_CUT_TURN) || (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_ROLL)) {
        r27 = true;
    }
    switch (i_this->mDamageReaction.mMode) {
        case -20:
            if (i_this->mpBodyMorf->isStop()) {
                if (cM_rndF(1.0f) < 0.5f) {
                    if (i_this->m0C34 != 0) {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BAT_JUMP1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BAT_JUMP1_e);
                        i_this->m0C48 = 4;
                        fopAcM_monsSeStart(actor, JA_SE_CV_TN_JUMP, 0);
                    } else {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BAT_KERI1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BAT_KERI1_e);
                        i_this->m0C48 = 3;
                        i_this->m0C67 = 1;
                    }
                    i_this->mDamageReaction.mMode = 1;
                    i_this->mCountDownTimers[2] = 8;
                    i_this->m13FD = 0;
                    i_this->m0C66 = 1;
                } else {
                    r29 = true;
                }
            }
            if (i_this->mDamageReaction.mAcch.ChkGroundHit()) {
                actor->speedF = 0.0f;
            }
            break;
        case 0:
            if (i_this->m0C34 != 0) {
                if (cM_rndF(100.0f) < l_tnHIO.m078) {
                    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
                        anm_init(i_this, dRes_INDEX_TN_BCK_AAT_TATE1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_AAT_TATE1_e);
                    } else {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BAT_TATE1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BAT_TATE1_e);
                    }
                    yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YAT_TATE1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                    i_this->m0C48 = 0;
                } else {
                    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
                        anm_init(i_this, dRes_INDEX_TN_BCK_AAT_YOKO1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_AAT_YOKO1_e);
                    } else {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BAT_YOKO1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BAT_YOKO1_e);
                    }
                    yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YAT_YOKO1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                    i_this->m0C48 = 1;
                    fopAcM_monsSeStart(actor, JA_SE_CV_TN_KAMAE_S, 0);
                }
            } else {
                if (cM_rndF(100.0f) < l_tnHIO.m07C || (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR)) {
                    anm_init(i_this, dRes_INDEX_TN_BCK_BAT_SYOUTEI_S1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BAT_SYOUTEI_S1_e);
                    i_this->m0C48 = 2;
                    fopAcM_monsSeStart(actor, JA_SE_CV_TN_PUNCH_S, 0);
                } else {
                    anm_init(i_this, dRes_INDEX_TN_BCK_BAT_KERI1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BAT_KERI1_e);
                    i_this->m0C48 = 3;
                    fopAcM_monsSeStart(actor, JA_SE_CV_TN_KICK, 0);
                }
            }
            i_this->mDamageReaction.mMode = 1;
            i_this->mCountDownTimers[2] = 8;
            i_this->m13FD = 0;
            i_this->m0C66 = 1;
            i_this->m0C67 = 0;
        case 1:
            {
                if ((i_this->m0C48 == 3 && (i_this->mpBodyMorf->getFrame() >= 12.0f)) && (i_this->mpBodyMorf->getFrame() <= 30.0f)) {
                    if (i_this->m0C67 != 0) {
                        actor->speedF = REG0_F(10) + 80.0f;
                    } else {
                        actor->speedF = REG0_F(9) + 50.0f;
                    }
                } else if ((i_this->m0C48 == 4 && (i_this->mpBodyMorf->getFrame() >= 4.0f)) && (i_this->mpBodyMorf->getFrame() <= 21.0f)) {
                    actor->speedF = REG0_F(16) + 50.0f;
                    frame = (int)i_this->mpBodyMorf->getFrame();
                    if (frame == 20) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_TN_ATTACK_L, 0);
                    }
                } else {
                    cLib_addCalc0(&actor->speedF, 1.0f, REG0_F(10) + 20.0f);
                }
                f31 = 1000.0f;
                f30 = f31;
                attackType = fopEn_enemy_c::OPENING_NONE;
                if (i_this->m0C66 > 0) {
                    if (i_this->m0C48 == 0) {
                        f31 = 0.0f;
                        f30 = 25.0f;
                        attackType = fopEn_enemy_c::OPENING_ROLL_PARRY;
                        frame = (int)i_this->mpBodyMorf->getFrame();
                        if (frame == 20) {
                            fopAcM_monsSeStart(actor, JA_SE_CV_TN_ATTACK_S, 0);
                        }
                    } else {
                        if (i_this->m0C48 == 1) {
                            f31 = 0.0f;
                            f30 = 25.0f;
                            attackType = fopEn_enemy_c::OPENING_JUMP_PARRY;
                            if (REG0_S(2) + 0x11 == (int)i_this->mpBodyMorf->getFrame()) {
                                i_this->m0430 = (REG0_S(3) + 0xE) + l_tnHIO.m020;
                                i_this->m0432 = 0;
                                i_this->m042E = (actor->current.angle.y + 0x2000) + REG0_S(8);
                            }
                            frame = (int)i_this->mpBodyMorf->getFrame();
                            if (frame == 20) {
                                fopAcM_monsSeStart(actor, JA_SE_CV_TN_ATTACK_S, 0);
                            }
                        }
                    }
                    if (i_this->m0C48 == 0 || i_this->m0C48 == 4) {
                        if ((i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) || i_this->m0C48 == 4) {
                            frame = 21;
                        } else {
                            frame = 19;
                        }
                        if (frame == (int)i_this->mpBodyMorf->getFrame()) {
                            dComIfGp_particle_setToon(
                                dPa_name::ID_IT_ST_TN_KENSMOKE00,
                                &actor->current.pos,
                                &actor->shape_angle,
                                NULL,
                                0xB9,
                                &i_this->mSmokeCb2,
                                fopAcM_GetRoomNo(actor)
                            );
                        }
                    }
                }
                actor->setBtAttackData(f31, f30, 10000.0f, attackType);
                actor->setBtMaxDis(l_tnHIO.m0D4);
                actor->setBtNowFrame(i_this->mpBodyMorf->getFrame());
                fopAc_ac_c* wepon_hit_actor = wepon_hit_check(i_this);
                if (wepon_hit_actor != NULL &&
                    fopAcM_GetName(wepon_hit_actor) == fpcNm_PLAYER_e &&
                    player->checkPlayerGuard() &&
                    (i_this->m0C48 == 0 || i_this->m0C48 == 1))
                {
                    i_this->mpBodyMorf->setPlaySpeed(-1.0f);
                    i_this->m0C66 = -1;
                    i_this->mpBodyMorf->play(&actor->eyePos, 0, 0);
                    anm_init(i_this, dRes_INDEX_TN_BCK_AHAJIKI1_e, REG0_F(4) + 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_AHAJIKI1_e);
                    yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YHAJIKI1_e, REG0_F(4) + 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                }
                if (i_this->mpBodyMorf->getFrame() < 10.0f) {
                    i_this->mDamageReaction.m4D0 = i_this->mTargetAngle;
                    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x400);
                }
                if (i_this->mpBodyMorf->isStop()) {
                    r29 = true;
                }
                break;
            }
        case 10:
            i_this->m0C48 = 5;
            i_this->mDamageReaction.mMode = 0xc;
            fopAcM_monsSeStart(actor, JA_SE_CV_TN_KAMAE_L, 0);
        case 12:
            if (std::fabsf(f31) > 0.1f) {
                anm_init(i_this, dRes_INDEX_TN_BCK_AAT_KAITEN_LR1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_AAT_KAITEN_LR1_e);
                if (f31 > 0.0f) {
                    i_this->mDamageReaction.mMode = 0xf;
                } else {
                    i_this->mDamageReaction.mMode = 0x10;
                }
            } else {
                if ((i_this->mPlayerDistance < l_tnHIO.m030 + 25.0f) && (i_this->mPlayerDistance > l_tnHIO.m030 - 25.0f)) {
                    anm_init(i_this, dRes_INDEX_TN_BCK_AAT_KAITEN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    i_this->mDamageReaction.mMode = 0x12;
                } else {
                    if (i_this->mPlayerDistance < l_tnHIO.m030) {
                        i_this->mDamageReaction.mMode = 0xe;
                    } else {
                        i_this->mDamageReaction.mMode = 0xd;
                    }
                    anm_init(i_this, dRes_INDEX_TN_BCK_AAT_KAITEN_FB1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_AAT_KAITEN_FB1_e);
                }
            }
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YAT_KAITEN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f);
            i_this->mCountDownTimers[1] = cM_rndF(20.0f) + 20.0f;
        case 13:
            cLib_addCalc2(&actor->speedF, l_tnHIO.m05C, 1.0f, 20.0f);
            goto temp_a88;
        case 14:
            cLib_addCalc2(&actor->speedF, -l_tnHIO.m05C, 1.0f, 20.0f);
            goto temp_a88;
        case 15:
            i_this->m0418 = 0x4000;
            goto temp_a60;
        case 16:
            i_this->m0418 = -0x4000;
        temp_a60:
            cLib_addCalc2(&actor->speedF, l_tnHIO.m060, 1.0f, 30.0f);
            goto temp_a88;
        case 18:
            actor->speedF = 0.0f;
        temp_a88:
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->mDamageReaction.mMode = 0xc;
            }
            if (!player->checkCutCharge()) {
                r29 = true;
            }
            if (r27) {
                r29 = false;
                i_this->mDamageReaction.mMode = 0x14;
                anm_init(i_this, dRes_INDEX_TN_BCK_AAT_KAITEN2_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_AAT_KAITEN2_e);
                yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YAT_KAITEN2_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_ATTACK_L, 0);
            }
            break;
        case 20:
            if (!i_this->mpBodyMorf->isStop()) {
                break;
            }
            i_this->mDamageReaction.mMode = 0x15;
            anm_init(i_this, dRes_INDEX_TN_BCK_AAT_KAITEN3_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_TN_BAS_AAT_KAITEN3_e);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YAT_KAITEN3_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f);
            i_this->m14F4 = 1;
        case 21:
            actor->speedF = 0.0f;
            if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_ROLL) {
                i_this->m14F6 = 7;
            } else {
                i_this->m14F6 = 3;
            }
            wepon_hit_check(i_this);
            if (!r27) {
                i_this->mDamageReaction.mMode = 0x16;
                anm_init(i_this, dRes_INDEX_TN_BCK_AAT_KAITEN4_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_AAT_KAITEN4_e);
                yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YAT_KAITEN4_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_ATTACK_L, 0);
            }
            if (i_this->mMantPcId != 0xFFFF) {
                mant_class* mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
                if (mant_actor != NULL) {
                    cLib_addCalc2(&mant_actor->m1BF8, REG0_F(6) + 50.0f, 1.0f, 20.0f);
                    cLib_addCalc2(&mant_actor->m1BFC, REG0_F(7) + 0.9f, 1.0f, 0.2f);
                }
            }
            break;
        case 22:
            if (i_this->mpBodyMorf->isStop()) {
                r29 = true;
            }
            break;
    }
    i_this->mCountDownTimers[4] = 50;
    if (r29) {
        if (i_this->mPlayerDistance < l_tnHIO.m02C) {
            if (daTn_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->mTargetAngle, get_view_H(i_this))) {
                if (cM_rndF(1.0f) < 0.5f) {
                    i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                    i_this->mDamageReaction.mMode = 2;
                    i_this->mCountDownTimers[3] = cM_rndF(20.0f) + 10.0f;
                    return;
                }
                i_this->mDamageReaction.mMode = 0;
                return;
            }
            i_this->mDamageReaction.mAction = ACTION_P_LOST;
            i_this->mDamageReaction.mMode = 0;
            return;
        }
        i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
        path_check(i_this);
        wait_set(i_this);
        i_this->mDamageReaction.mMode = 0;
    }
}

/* 00005EB0-00005FFC       .text p_lost__FP8tn_class */
static void p_lost(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->mDamageReaction.m710 = 0;
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            anm_init(i_this, dRes_INDEX_TN_BCK_AKYORO1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKYORO1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
            actor->speedF = 0.0f;
            break;
        case 1:
            mDoExt_McaMorf* r5 = i_this->mpBodyMorf;
            if (r5->isStop()) {
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                path_check(i_this);
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 0;
            }
            break;
    }
    if ((int)i_this->mpBodyMorf->getFrame() > 25) {
        if (daTn_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->mTargetAngle, get_view_H(i_this))) {
            i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
            i_this->mDamageReaction.mMode = -10;
            i_this->mCountDownTimers[1] = 0;
        }
    }
}

/* 00005FFC-00006450       .text wepon_search__FP8tn_class */
static void wepon_search(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 f31;
    cXyz local_30;

    fopAc_ac_c* boko_actor = fopAcM_SearchByID(i_this->mBokoPcId);
    if (i_this->mDamageReaction.mMode < 2 && (boko_actor == NULL || (boko_actor != NULL && fopAcM_checkCarryNow(boko_actor)))) {
        i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
        path_check(i_this);
        wait_set(i_this);
        i_this->mDamageReaction.mMode = 2;
    } else {
        f31 = 10000.0f;
        if (boko_actor != NULL) {
            local_30.x = boko_actor->current.pos.x - actor->current.pos.x;
            local_30.z = boko_actor->current.pos.z - actor->current.pos.z;
            i_this->mDamageReaction.m4D0 = cM_atan2s(local_30.x, local_30.z);
            f31 = std::sqrtf(SQUARE(local_30.x) + SQUARE(local_30.z));
        }
        switch (i_this->mDamageReaction.mMode) {
            case -1:
                i_this->mDamageReaction.mMode = 0;
                i_this->m13FF = 0;
                anm_init(i_this, dRes_INDEX_TN_BCK_AKIDUKU1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIDUKU1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                if (f31 < 900.0f) {
                    i_this->mCountDownTimers[1] = 20;
                } else {
                    i_this->mCountDownTimers[1] = 200;
                }
                i_this->m03EE = 5;
                break;
            case 0:
                actor->speedF = 0.0f;
                if (i_this->m03EE == 0) {
                    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 2, 0x3000);
                    if (i_this->mpBodyMorf->isStop() || i_this->mCountDownTimers[1] == 0) {
                        i_this->mDamageReaction.mMode = 1;
                        i_this->m03EA = l_tnHIO.m082;
                        fight_run_set(i_this);
                    }
                }
                break;
            case 1:
                cLib_addCalc2(&actor->speedF, l_tnHIO.m058, 1.0f, 10.0f);
                cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x1000);
                if (f31 < REG8_F(2) + 150.0f) {
                    i_this->mDamageReaction.mMode = 2;
                    anm_init(i_this, dRes_INDEX_TN_BCK_BHIROU_K1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BHIROU_K1_e);
                    i_this->mCountDownTimers[1] = 29;
                } else if (i_this->m03EA == 0) {
                    i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                    i_this->mCountDownTimers[1] = 0;
                    i_this->m13FF = 1;
                } else if (i_this->mDamageReaction.mAcch.ChkGroundHit() && i_this->mDamageReaction.mAcch.ChkWallHit()) {
                    i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                    path_check(i_this);
                    wait_set(i_this);
                    i_this->mDamageReaction.mMode = 2;
                    i_this->m03FC = 0x46;
                }
                break;
            case 2:
                actor->speedF = 0.0f;
                if (i_this->mCountDownTimers[1] == (s16)(REG0_S(7) + 0x12)) {
                    if (boko_actor != NULL && !fopAcM_checkCarryNow(boko_actor)) {
                        i_this->m0C34 = 2;
                        fopAcM_setCarryNow(boko_actor, 0);
                    } else {
                        i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                        path_check(i_this);
                        wait_set(i_this);
                        i_this->mDamageReaction.mMode = 2;
                    }
                }
                if (i_this->mCountDownTimers[1] < 14) {
                    i_this->mDamageReaction.m710 = 1;
                    i_this->mDamageReaction.m4D0 = i_this->mTargetAngle;
                    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, 0x800);
                }
                if (i_this->mpBodyMorf->isStop()) {
                    i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                    path_check(i_this);
                    wait_set(i_this);
                    i_this->mDamageReaction.mMode = 2;
                }
                break;
        }
    }
}

/* 00006450-00006950       .text b_nige__FP8tn_class */
static void b_nige(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_14;

    if (!daTn_bomb_check(i_this)) {
        i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
        path_check(i_this);
        wait_set(i_this);
        i_this->mDamageReaction.mMode = 2;
    } else {
        local_14.x = i_this->m1418->current.pos.x - actor->current.pos.x;
        local_14.z = i_this->m1418->current.pos.z - actor->current.pos.z;
        i_this->mDamageReaction.m4D0 = cM_atan2s(-local_14.x, -local_14.z);
        switch (i_this->mDamageReaction.mMode) {
            case 0:
                i_this->mDamageReaction.mMode = 1;
                anm_init(i_this, dRes_INDEX_TN_BCK_AKIDUKU1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_FOUND, 0);
                i_this->mCountDownTimers[1] = 10;
            case 1:
                actor->speedF = 0.0f;
                cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0 + 0x8000, 2, 0x3000);
                if (i_this->mCountDownTimers[1] == 0) {
                    i_this->mDamageReaction.mMode = 2;
                    if (i_this->m0C34 != 0) {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BBACK1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BBACK1_e);
                    } else {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BBACK_S1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BBACK_S1_e);
                    }
                    actor->speedF = REG0_F(3) + -60.0f;
                    actor->speed.y = REG0_F(4) + 80.0f;
                    fopAcM_monsSeStart(actor, JA_SE_CV_TN_JUMP, 0);
                }
                break;
            case 2:
                if (i_this->mDamageReaction.mAcch.ChkGroundHit()) {
                    if (i_this->mpBodyMorf->isStop()) {
                        actor->speedF = 0.0f;
                        if (std::sqrtf(SQUARE(local_14.x) + SQUARE(local_14.z)) > 800.0f) {
                            i_this->mDamageReaction.mMode = 4;
                            if (i_this->m0C34 != 0) {
                                anm_init(i_this, dRes_INDEX_TN_BCK_AKAMAE1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                            } else {
                                anm_init(i_this, dRes_INDEX_TN_BCK_BKAMAE_S1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                            }
                        } else {
                            i_this->mDamageReaction.mMode = 3;
                            fight_run_set(i_this);
                        }
                    }
                }
                break;
            case 3:
                actor->speedF = l_tnHIO.m058;
                cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x1000);
                if (std::sqrtf(SQUARE(local_14.x) + SQUARE(local_14.z)) > 800.0f) {
                    i_this->mDamageReaction.mMode = 4;
                    if (i_this->m0C34 != 0) {
                        anm_init(i_this, dRes_INDEX_TN_BCK_AKAMAE1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    } else {
                        anm_init(i_this, dRes_INDEX_TN_BCK_BKAMAE_S1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    }
                }
                break;
            case 4:
                actor->speedF = 0.0f;
                i_this->mDamageReaction.m4D0 = i_this->mTargetAngle;
                cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, 0x1000);
                if (std::sqrtf(SQUARE(local_14.x) + SQUARE(local_14.z)) < 700.0f) {
                    i_this->mDamageReaction.mMode = 0;
                }
                break;
        }
    }
}

/* 00006950-00006AC0       .text defence__FP8tn_class */
static void defence(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->mDamageReaction.m710 = 1;
    i_this->mDamageReaction.m4D0 = i_this->mTargetAngle;
    cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x400);
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            if (i_this->m0C34 != 0) {
                anm_init(i_this, dRes_INDEX_TN_BCK_AGUARD1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                tate_anm_init(i_this, dRes_INDEX_TN_BCK_AGUARD1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
            } else {
                anm_init(i_this, dRes_INDEX_TN_BCK_AGUARD2_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                tate_anm_init(i_this, dRes_INDEX_TN_BCK_AGUARD2_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
            }
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YGUARD1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
        // Fall-through
        case 1:
            actor->speedF = 0.0f;
            i_this->m1444 = 1;
            if (i_this->mCountDownTimers[1] == 0 && player->getCutType() == daPy_py_c::CUT_TYPE_NONE) {
                i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                i_this->mCountDownTimers[1] = 0;
                i_this->mDamageReaction.mMode = 0;
                tate_anm_init(i_this, dRes_INDEX_TN_BCK_ATATE_ON1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f);
            }
            break;
    }
}

/* 00006AC0-00006DD4       .text hukki__FP8tn_class */
static void hukki(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_1c;
    cXyz local_28;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    local_1c.x = i_this->mDamageReaction.m100[10].x - i_this->mDamageReaction.m100[13].x;
    local_1c.z = i_this->mDamageReaction.m100[10].z - i_this->mDamageReaction.m100[13].z;
    cMtx_YrotS(*calc_mtx, cM_atan2s(local_1c.x, local_1c.z));
    local_1c.x = 0.0f;
    local_1c.y = 0.0f;
    i_this->m03F0 = 2;
    switch (i_this->mDamageReaction.mMode) {
        case 10:
            anm_init(i_this, dRes_INDEX_TN_BCK_BOKIRU_A1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BOKIRU_A1_e);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIHON1_e, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
            i_this->mCountDownTimers[2] = 15;
            goto temp_124;
        case 12:
            anm_init(i_this, dRes_INDEX_TN_BCK_BOKIRU_U1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_BOKIRU_U1_e);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIHON1_e, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
            i_this->mCountDownTimers[2] = REG0_S(5) + 15;
        temp_124:
            actor->speedF = 0.0f;
            i_this->mDamageReaction.mMode = 0xD;
            i_this->mDamageReaction.m480 = 0;
            local_1c.z = 125.0f;
            MtxPosition(&local_1c, &i_this->mDamageReaction.m458);
            actor->current.pos.y -= i_this->mDamageReaction.m44C.y;
            actor->old.pos.y -= i_this->mDamageReaction.m44C.y;
            i_this->mDamageReaction.m44C.y = 0.0f;
        // Fall-through
        case 13:
            if (i_this->mCountDownTimers[2] <= REG6_S(5) + 6) {
                cLib_addCalc0(&i_this->mDamageReaction.m458.x, 1.0f, (REG6_F(5) + 100.0f) * 0.25f);
                cLib_addCalc0(&i_this->mDamageReaction.m458.z, 1.0f, (REG6_F(5) + 100.0f) * 0.25f);
                if (i_this->mCountDownTimers[2] >= REG6_S(6) + 1) {
                    local_1c.z = 25.0f;
                    MtxPosition(&local_1c, &local_28);
                    actor->current.pos.x += local_28.x;
                    actor->current.pos.z += local_28.z;
                }
            }
            if (i_this->mpBodyMorf->isStop()) {
                if (!player->checkGrabWear() && i_this->mPlayerDistance < l_tnHIO.m02C) {
                    i_this->mDamageReaction.mMode = 0xE;
                    i_this->mCountDownTimers[1] = 10;
                } else {
                    i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                    path_check(i_this);
                    wait_set(i_this);
                    i_this->mDamageReaction.mMode = 0;
                }
                i_this->mDamageReaction.m488 = 0;
            }
            break;
        case 14:
            i_this->mDamageReaction.m710 = 1;
            i_this->mDamageReaction.m4D0 = i_this->mTargetAngle;
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 3, 0x1000);
            if (i_this->mCountDownTimers[1] != 0) {
                break;
            }
            i_this->mDamageReaction.mAction = ACTION_FIGHT;
            i_this->mDamageReaction.mMode = 0;
            break;
    }
}

/* 00006DD4-00006EB4       .text aite_miru__FP8tn_class */
static void aite_miru(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mCountDownTimers[1] = REG0_S(8) + 20;
            actor->speedF = 0.0f;
            i_this->mDamageReaction.mMode = 1;
        // Fall-through
        case 1:
            cLib_addCalcAngleS2(&i_this->m1404, 12000, 2, 0x1800);
            i_this->mDamageReaction.m710 = 1;
            if (i_this->m1408 != fpcM_ERROR_PROCESS_ID_e) {
                fopAc_ac_c* r3 = fopAcM_SearchByID(i_this->m1408);
                if (r3 != NULL) {
                    i_this->mDamageReaction.m714 = r3;
                }
            }
            if (i_this->mCountDownTimers[1] == 0) {
                i_this->m1408 = fpcM_ERROR_PROCESS_ID_e;
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                i_this->mDamageReaction.mMode = 0;
                path_check(i_this);
            }
            break;
    }
}

/* 00006EB4-00006FF0       .text fail__FP8tn_class */
static void fail(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_18;

    i_this->m03F0 = 5;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    actor->speedF = 0.0f;
    actor->speed.y = 0.0f;
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            {
                local_18 = actor->current.pos;
                local_18.y += l_tnHIO.m018 + 100.0f;
                u8 drop_type = daDisItem_IBALL_e;
                if (i_this->mCountDownTimers[2] >= 1000) {
                    drop_type = daDisItem_NONE1_e;
                }
                fopAcM_createDisappear(actor, &local_18, 10, drop_type, actor->stealItemBitNo);
                if (i_this->m14F8 != 0) {
                    i_this->m1518 = 1;
                    i_this->mDamageReaction.mMode++;
                } else {
                    fopAcM_delete(actor);
                }
                if (i_this->mDisableSpawnOnDeathSwitch != 0) {
                    dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(actor));
                }
                fopAcM_onActor(actor);
                i_this->mDamageReaction.mMode = 1;
            }
        // Fall-through
        case 1:
            break;
    }
}

/* 00006FF0-0000719C       .text yogan_fail__FP8tn_class */
static void yogan_fail(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m03F0 = 5;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    actor->speedF = 0.0f;
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            actor->speed.y = REG0_F(19) + 190.0f;
            i_this->mDamageReaction.m458.y = 0.0f;
            i_this->mDamageReaction.m44C.y = 0.0f;
            if (i_this->m0C34 != 0) {
                i_this->m0C38 = 1;
            }
        // Fall-through
        case 1:
            dComIfGp_particle_setSimple(dPa_name::ID_IT_SN_O_FIREK_KASU, &actor->current.pos);
            dComIfGp_particle_setSimple(dPa_name::ID_IT_SN_O_MAGT_FCHIP, &actor->current.pos);
            if (!(i_this->m03D8 & 3)) {
                i_this->m0428.y = cM_rndF(65536.0f);
                i_this->m0428.x = -0x2000;
                dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &i_this->m1384, &i_this->m0428);
            }
            cLib_addCalcAngleS2(&actor->current.angle.x, -0x4000, 10, 0x200);
            if (actor->speed.y < 0.0f) {
                i_this->mDamageReaction.mAction = ACTION_FAIL;
                i_this->mDamageReaction.mMode = 0;
                i_this->mCountDownTimers[2] = 2000;
            }
            break;
    }
}

/* 0000719C-000072C8       .text d_mahi__FP8tn_class */
static void d_mahi(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            anm_init(i_this, dRes_INDEX_TN_BCK_AMAHI1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YMAHI1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
            i_this->mCountDownTimers[0] = 60;
        // Fall-through
        case 1:
            if (i_this->mCountDownTimers[0] <= 40 && i_this->mCountDownTimers[0] >= 10) {
                if (i_this->mCountDownTimers[0] == 40) {
                    enemy_piyo_set(actor);
                }
                fopAcM_seStart(actor, JA_SE_CM_MD_PIYO, 0);
            }
            actor->speedF = 0.0f;
            if (i_this->mCountDownTimers[0] == 0) {
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                path_check(i_this);
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
            }
            break;
    }
}

/* 000072C8-00007440       .text d_sit__FP8tn_class */
static void d_sit(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m03F0 = 5;
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            anm_init(i_this, dRes_INDEX_TN_BCK_AHAZURE1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_AHAZURE1_e);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YHAZURE1_e, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
        // Fall-through
        case 1:
            actor->speedF = 0.0f;
            if (!i_this->mpBodyMorf->isStop()) {
                break;
            }
            i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
            path_check(i_this);
            wait_set(i_this);
            i_this->mDamageReaction.mMode = 2;
            break;
        case 10:
            i_this->mDamageReaction.mMode = 0xb;
            anm_init(i_this, dRes_INDEX_TN_BCK_AKYORO1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, -1);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKYORO1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f);
            i_this->mCountDownTimers[0] = 55;
        // Fall-through
        case 11:
            actor->speedF = 0.0f;
            if (i_this->mCountDownTimers[0] == 0) {
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                path_check(i_this);
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
            }
            break;
    }
}

/* 00007440-000079AC       .text stand__FP8tn_class */
static void stand(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_30;

    i_this->mDamageReaction.m710 = 0;
    s32 r30 = fopAcM_otoCheck(actor, 1000.0f);
    if (i_this->mMantPcId != 0xFFFF) {
        mant_class* mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
        if (mant_actor != NULL && mant_actor->m1C0E != 0) {
            r30 |= 2;
        }
    }
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            if (i_this->m0C34 != 0) {
                anm_init(i_this, dRes_INDEX_TN_BCK_ANIOU1_e, i_this->m151C, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            } else {
                anm_init(i_this, dRes_INDEX_TN_BCK_AWAIT1_e, i_this->m151C, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIHON1_e, i_this->m151C, J3DFrameCtrl::EMode_NONE, 1.0f);
        // Fall-through
        case 1:
            cLib_addCalc2(&actor->current.pos.x, actor->home.pos.x, 0.5f, actor->speed.x * 0.25f);
            cLib_addCalc2(&actor->current.pos.z, actor->home.pos.z, 0.5f, actor->speed.z * 0.25f);
            cLib_addCalcAngleS2(&actor->current.angle.y, actor->home.angle.y, 2, 0x800);
            actor->speedF = 0.0f;
            break;
        case 10:
            if (i_this->mCountDownTimers[1] == 30) {
                anm_init(i_this, dRes_INDEX_TN_BCK_AKIDUKU1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
            if (i_this->mCountDownTimers[1] == 0) {
                anm_init(i_this, dRes_INDEX_TN_BCK_AKYORO1_e, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mDamageReaction.mMode = 0xb;
                i_this->mCountDownTimers[3] = cM_rndF(30.0f) + 30.0f;
            }
            break;
        case 11:
            if (i_this->mCountDownTimers[3] == 0) {
                i_this->mDamageReaction.mMode = 0;
            }
            break;
        case 20:
            if (i_this->mCountDownTimers[1] < 10) {
                i_this->mDamageReaction.m710 = 1;
            }
            if (i_this->mCountDownTimers[1] != 0) {
                break;
            }
            i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
            i_this->mCountDownTimers[1] = 0;
            i_this->mDamageReaction.mMode = 0;
            return;
        case 50:
            anm_init(i_this, dRes_INDEX_TN_BCK_AKYORO1_e, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mDamageReaction.mMode++;
            i_this->mCountDownTimers[1] = 50;
        // Fall-through
        case 51:
            actor->speedF = 0.0f;
            if (i_this->mCountDownTimers[1] == 0) {
                fight_run_set(i_this);
                i_this->mDamageReaction.mMode++;
                i_this->mCountDownTimers[2] = 60;
            }
            break;
        case 52:
            local_30 = actor->home.pos - actor->current.pos;
            i_this->mDamageReaction.m4D0 = cM_atan2s(local_30.x, local_30.z);
            if (std::sqrtf(SQUARE(local_30.x) + SQUARE(local_30.z)) < (l_tnHIO.m054 * 0.25f) * 5.0f) {
                i_this->mDamageReaction.mMode = 0;
            }
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->mDamageReaction.m4D0, 4, 0x1000);
            cLib_addCalc2(&actor->speedF, l_tnHIO.m054, 1.0f, 5.0f);
            break;
    }
    if (i_this->mDamageReaction.mMode < 10 && r30 != 0) {
        i_this->mDamageReaction.mMode = 10;
        i_this->mCountDownTimers[1] = cM_rndF(10.0f) + 45.0f;
    }
    if (i_this->mCountDownTimers[2] == 0 && i_this->mDamageReaction.mMode != 0x14) {
        f32 fVar8;
        if (i_this->mRangeOrFrozenAnim != 0xFF) {
            fVar8 = i_this->mRangeOrFrozenAnim * 10.0f;
        } else {
            fVar8 = 500.0f;
        }
        if (i_this->mPlayerDistance < fVar8) {
            if (daTn_player_view_check(i_this, &i_this->mDamageReaction.m714->current.pos, i_this->mTargetAngle, get_view_H(i_this))) {
                if (i_this->mDamageReaction.mMode >= 0x32) {
                    i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                    i_this->mCountDownTimers[1] = 0;
                    i_this->mDamageReaction.mMode = 0;
                } else {
                    i_this->mDamageReaction.mMode = 0x14;
                    anm_init(i_this, dRes_INDEX_TN_BCK_AKIDUKU1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    i_this->mCountDownTimers[1] = 30;
                    fopAcM_monsSeStart(actor, JA_SE_CV_TN_FOUND, 0);
                }
            }
        }
        if (daTn_bomb_view_check(i_this)) {
            i_this->mDamageReaction.mAction = ACTION_B_NIGE;
            i_this->mDamageReaction.mMode = 0;
        }
    }
    if (i_this->m0C34 == 0 && daTn_wepon_view_check(i_this)) {
        i_this->mDamageReaction.mAction = ACTION_WEPON_SEARCH;
        i_this->mDamageReaction.mMode = -1;
    }
}

/* 000079AC-00007B7C       .text d_dozou__FP8tn_class */
static void d_dozou(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->m03F0 = 5;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            i_this->mDamageReaction.mStts.Init(0xFF, 0xFF, actor);
            if (i_this->mRangeOrFrozenAnim == 0) {
                anm_init(i_this, dRes_INDEX_TN_BCK_AKYORO1_e, 1.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1);
                i_this->mpBodyMorf->setFrame(41.0f);
            } else {
                anm_init(i_this, dRes_INDEX_TN_BCK_AAT_YOKO1_e, 1.0f, J3DFrameCtrl::EMode_NONE, 0.0f, dRes_INDEX_TN_BAS_AAT_YOKO1_e);
                i_this->mpBodyMorf->setFrame(27.0f);
            }
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIHON1_e, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
        // Fall-through
        case 1:
            if ((i_this->mEnableSpawnSwitch != 0xFF && dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, fopAcM_GetRoomNo(actor))) ||
                (i_this->mEnableSpawnSwitch == 0xFF && dComIfGs_isEventBit(dSv_event_flag_c::COLORS_IN_HYRULE)))
            {
                i_this->mpBodyMorf->setPlaySpeed(1.0f);
                i_this->mDamageReaction.mMode = 2;
            }
            break;
        case 2:
            if (i_this->mpBodyMorf->isStop()) {
                i_this->mDamageReaction.mStts.Init(0xF0, 0xFF, actor);
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                i_this->mDamageReaction.mMode = 0;
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            }
            break;
    }
}

/* 00007B7C-00008490       .text s_demo__FP8tn_class */
static void s_demo(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int r0;

    i_this->m03F0 = 5;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    int r29 = (int)i_this->mpBodyMorf->getFrame();
    switch (i_this->mDamageReaction.mMode) {
        case 0:
            i_this->mDamageReaction.mMode = 1;
            anm_init(i_this, dRes_INDEX_TN_BCK_ANIOU1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIHON1_e, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
        case 1:
            if ((DEMO_SELECT(REG17_S(0), REG0_S(0)) != 0) || (dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, fopAcM_GetRoomNo(actor)))) {
                mDoAud_bgmAllMute(30);
                anm_init(i_this, dRes_INDEX_TN_BCK_S_DEMO_M1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_TN_BAS_S_DEMO_M1_e);
                yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_S_DEMO_Y1_e, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
                i_this->mDamageReaction.mMode = 2;
            }
            break;
        case 2:
            if (r29 == 0x7f) {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_FOUND, 0);
            }
            if (r29 == 0xac) {
                mDoAud_subBgmStart(JA_BGM_MBOSS);
            }
            if (r29 == 0xc1) {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_KAMAE_L, 0);
            }
            if (r29 == 0xe7 || r29 == 0x106) {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_ATTACK_L, 0);
            }
            if (i_this->mpBodyMorf->isStop()) {
                i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                i_this->mDamageReaction.mMode = 0;
            }
            break;
        case 10:
            {
                i_this->mDamageReaction.mMaxFallDistance = 10000.0f;
                actor->current.pos.y = actor->home.pos.y + 5000.0f;
                actor->speed.y = 0.0f;
#if VERSION == VERSION_DEMO
                i_this->m0414_demo = REG0_S(8) + 0x4000;
                if (!dComIfGp_evmng_existence("btl_of_swroom") && s_check == 0) {
                    return;
                }

#else
                if (!dComIfGp_evmng_existence("btl_of_swroom")) {
                    if (!dComIfGp_evmng_existence("btl_of_swroom2") && s_check == 0) {
                        return;
                    }
                }
#endif
                int staffIdx = dComIfGp_evmng_getMyStaffId("Tn", NULL, 0);
                if (staffIdx != -1 || s_check != 0) {
                    if (s_check == 0) {
                        if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx), "Appear")) {
                            return;
                        }
                    }
                    mDoAud_bgmAllMute(30);
                    actor->current.pos.z -= 50.0f;
#if VERSION == VERSION_DEMO
                    if (s_check == 0) {
                        actor->current.pos.y = actor->home.pos.y + 2000.0f;
                    } else {
                        actor->current.pos.y = actor->home.pos.y + 2750.0f;
                    }
#else
                    if (actor->home.pos.x < 0.0f) {
                        actor->current.pos.x += 250.0f;
                        actor->current.pos.y = actor->home.pos.y + 2750.0f;
                        i_this->m1519 = 1;
                    } else {
                        actor->current.pos.x += -130.0f;
                        actor->current.pos.y = actor->home.pos.y + 2000.0f;
                        i_this->m1519 = 0;
                    }
#endif
                    fopAcM_seStart(actor, JA_SE_CM_TN_FALL_DOWN, 0);
#if VERSION == VERSION_DEMO
                    i_this->m1519 = s_check;
                    s_check++;
                    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                    if (player != NULL) {
                        actor->shape_angle.y = cM_atan2s(player->current.pos.x - actor->current.pos.x, player->current.pos.z - actor->current.pos.z);
                    }
#else
                    s_check++;
#endif
                    anm_init(i_this, dRes_INDEX_TN_BCK_S_DEMO_M2_e, 3.0f, J3DFrameCtrl::EMode_NONE, 0.0f, dRes_INDEX_TN_BAS_S_DEMO_M2_e);
                    yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_S_DEMO_Y2_e, 3.0f, J3DFrameCtrl::EMode_NONE, 0.0f);
                    tate_anm_init(i_this, DEMO_SELECT(dRes_INDEX_TN_BCK_ATATE_ON1_e, dRes_INDEX_TN_BCK_S_DEMO_M2_e), 3.0f, J3DFrameCtrl::EMode_LOOP, 0.0f);
                    i_this->mDamageReaction.mMode = 0xb;
                }
                break;
            }
        case 0xb:
#if VERSION > VERSION_DEMO
            if (dComIfGp_evmng_existence("btl_of_swroom") || dComIfGp_evmng_existence("btl_of_swroom2")) {
                int staffIdx = dComIfGp_evmng_getMyStaffId("Tn", NULL, 0);
                if (staffIdx != -1) {
                    if (!strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx), "Appear2")) {
                        actor->current.pos.x = actor->home.pos.x;
                        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                        if (player != NULL) {
                            actor->shape_angle.y = cM_atan2s(player->current.pos.x - actor->current.pos.x, player->current.pos.z - actor->current.pos.z);
                        }
                    }
                }
            }
#endif
            if (i_this->mDamageReaction.mAcch.ChkGroundHit()) {
                i_this->mpBodyMorf->setPlaySpeed(1.0f);
                i_this->mpArmorMorf->setPlaySpeed(1.0f);
#if VERSION > VERSION_DEMO
                i_this->mpShieldMorf->setPlaySpeed(1.0f);
#endif
                fopAcM_seStart(actor, JA_SE_CM_TN_FALL_LANDING, 0);
                if (i_this->m1519 == 0) {
                    i_this->mDamageReaction.mMode = 0xc;
                } else {
                    i_this->mDamageReaction.mMode = 0xd;
                }
#if VERSION > VERSION_DEMO
                if (actor->home.pos.x < 0.0f) {
                    dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
                } else {
                    dComIfGp_getVibration().StartShock(2, -0x11, cXyz(0.0f, 1.0f, 0.0f));
                }
#endif
            }
            break;
        case 0xc:
            r0 = (int)i_this->mpBodyMorf->getFrame();
            if (r0 == 0x2b) {
                if (s_check == 10) {
                    i_this->mDamageReaction.mMode = 0xd;
                } else {
                    i_this->mpBodyMorf->setPlaySpeed(0.0f);
                    i_this->mpArmorMorf->setPlaySpeed(0.0f);
#if VERSION > VERSION_DEMO
                    i_this->mpShieldMorf->setPlaySpeed(0.0f);
#endif
                }
            }
            break;
        case 0xd:
            i_this->mpBodyMorf->setPlaySpeed(1.0f);
            i_this->mpArmorMorf->setPlaySpeed(1.0f);
#if VERSION > VERSION_DEMO
            i_this->mpShieldMorf->setPlaySpeed(1.0f);
#endif
            r0 = (int)i_this->mpBodyMorf->getFrame();
            if (r0 == 0x2b) {
                s_check = 10;
            }
            if (r29 == 0x3f) {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_KAMAE_L, 0);
            }
            if (r29 == 0x73) {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_ATTACK_L, 0);
            }
            if (r29 == REG0_S(7) + DEMO_SELECT(0xa5, 0xd2)) {
#if VERSION == VERSION_DEMO
                i_this->m0414_demo = 0;
#else
                tate_anm_init(i_this, dRes_INDEX_TN_BCK_ATATE_ON1_e, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f);
#endif
            }
            if (i_this->mpBodyMorf->isStop()) {
                i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                i_this->mDamageReaction.mMode = 0;
                i_this->mDamageReaction.mMaxFallDistance = 1000.0f;
                mDoAud_subBgmStart(JA_BGM_MBOSS);
            }
            break;
        case 0x14:
            i_this->mDamageReaction.mMode = 0x15;
            anm_init(i_this, dRes_INDEX_TN_BCK_ANIOU1_e, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YKIHON1_e, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f);
            i_this->mCountDownTimers[0] = 30;
        case 0x15:
            if (i_this->mCountDownTimers[0] == 0) {
                anm_init(i_this, dRes_INDEX_TN_BCK_AKAMAE1_e, 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->mCountDownTimers[0] = 30;
                i_this->mDamageReaction.mMode = 0x16;
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_KAMAE_L, 0);
            }
            break;
        case 0x16:
            if (i_this->mCountDownTimers[0] == 0) {
                i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                i_this->mDamageReaction.mMode = 2;
                i_this->mCountDownTimers[3] = 60;
            }
            break;
    }
}

/* 00008490-000086D4       .text demo_camera__FP8tn_class */
static void demo_camera(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    dCam_getCamera();
    dCamera_c* camera = dCam_getBody();
    s8 r28 = true;
    switch (i_this->m14F8) {
        case 0:
            r28 = false;
            break;
        case 50:
            {
                if (!actor->eventInfo.checkCommandDemoAccrpt()) {
                    fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                    actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
                    r28 = false;
                    break;
                }
                camera->Stop();
                camera->SetTrimSize(1);
                i_this->m14F8 = 0x33;

                camera_class* r3 = dComIfGp_getCamera(0);
                i_this->mCameraEyePos = r3->mLookat.mEye;
                i_this->mCenterPos = r3->mLookat.mCenter;
                i_this->m1514 = 55.0f;
                i_this->m14FA = 0;
            }
        // Fall-through
        case 51:
            cLib_addCalc2(&i_this->m1514, REG0_F(13) + 30.0f, 0.2f, REG0_F(14) + 0.4f);
            if (i_this->m1518 == 0) {
                cLib_addCalc2(&i_this->mCenterPos.x, actor->current.pos.x, 0.1f, 100.0f);
                cLib_addCalc2(&i_this->mCenterPos.y, actor->current.pos.y + 230.0f + REG0_F(12), 0.1f, 100.0f);
                cLib_addCalc2(&i_this->mCenterPos.z, actor->current.pos.z, 0.1f, 100.0f);
            }
            i_this->m14FA++;
            if (i_this->m14FA > 0x96) {
                camera->SetTrimSize(0);
                camera->Start();
                dMeter_mtrShow();
                dComIfGp_event_reset();
                fopAcM_delete(actor);
                return;
            }
    }
    if (r28) {
        camera->Set(i_this->mCenterPos, i_this->mCameraEyePos, i_this->m1514, 0);
    }
}

/* 000086D4-00008C5C       .text Tn_move__FP8tn_class */
static void Tn_move(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar9;
    cXyz local_40;
    cXyz local_4c;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->m0418 = 0;
    i_this->mDamageReaction.m710 = 0;
    cLib_addCalcAngleS2(&i_this->m1404, 0, 2, 0x800);
    if (i_this->mDamageReaction.mMode <= -100) {
        i_this->m03F0 = 5;
        if (std::fabsf(i_this->mDamageReaction.m478) > 40.0f && !i_this->mDamageReaction.mAcch.ChkGroundHit()) {
            i_this->mWeponSph.SetC(i_this->mDamageReaction.m100[12]);
            i_this->mWeponSph.SetR(60.0f);
            i_this->mWeponSph.OffAtVsPlayerBit();
            i_this->mWeponSph.OnCoSetBit();
            i_this->mWeponSph.SetAtSpl(dCcG_At_Spl_UNK1);
            dComIfG_Ccsp()->Set(&i_this->mWeponSph);
            dComIfG_Ccsp()->SetMass(&i_this->mWeponSph, 3);
            if (i_this->mWeponSph.ChkAtHit() && actor->speed.y < -50.0f) {
                actor->speed.y = 0.0f;
                i_this->mDamageReaction.m474 = 8000.0f;
            }
            i_this->mCoCyl.OffCoSetBit();
        }
    } else {
        i_this->mWeponSph.OnAtVsPlayerBit();
        i_this->mCoCyl.OnCoSetBit();
        if (i_this->mDamageReaction.m48A != 0 && i_this->mDamageReaction.m488 == 0) {
            if (i_this->mDamageReaction.m48A == 1) {
                i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                i_this->mDamageReaction.mMode = 0;
                i_this->mCountDownTimers[1] = 0;
            } else {
                i_this->mDamageReaction.m4D0 = i_this->mTargetAngle;
                actor->speedF = -30.0f;
            }
        } else {
            if (i_this->m1436 != 0) {
                i_this->m1436--;
                local_40 = i_this->m1438 - actor->current.pos;
            } else {
                i_this->mDamageReaction.m714 = player;
                local_40 = i_this->mDamageReaction.m714->current.pos - actor->current.pos;
            }
            i_this->mPlayerDistance = std::sqrtf(SQUARE(local_40.x) + SQUARE(local_40.z));
            i_this->mTargetAngle = cM_atan2s(local_40.x, local_40.z);
            i_this->mCoCyl.SetR(REG0_F(3) + 80.0f);
            if (i_this->m1434 != 0) {
                i_this->m1434--;
                if (i_this->m1434 == 0) {
                    i_this->mDamageReaction.mAction = ACTION_D_MAHI;
                    i_this->mDamageReaction.mMode = 0;
                }
            }
#if VERSION == VERSION_DEMO
            s8 r29 = 0;
#endif
            switch (i_this->mDamageReaction.mAction) {
                case ACTION_JYUNKAI:
                    jyunkai(i_this);
                    break;
                case ACTION_STAND:
                    stand(i_this);
                    break;
                case ACTION_FIGHT_RUN:
                    fight_run(i_this);
                    break;
                case ACTION_FIGHT:
                    fight(i_this);
                    break;
                case ACTION_DEFENCE:
                    defence(i_this);
                    break;
                case ACTION_P_LOST:
                    p_lost(i_this);
                    break;
                case ACTION_B_NIGE:
                    b_nige(i_this);
                    break;
                case ACTION_HUKKI:
                    hukki(i_this);
                    break;
                case ACTION_D_MAHI:
                    d_mahi(i_this);
                    break;
                case ACTION_D_SIT:
                    d_sit(i_this);
                    break;
                case ACTION_D_DOZOU:
                    d_dozou(i_this);
                    break;
                case ACTION_WEPON_SEARCH:
                    wepon_search(i_this);
                    break;
                case ACTION_AITE_MIRU:
                    aite_miru(i_this);
                    break;
                case ACTION_FAIL:
                    fail(i_this);
                    break;
                case ACTION_YOGAN_FAIL:
                    yogan_fail(i_this);
                    break;
                case ACTION_S_DEMO:
                    s_demo(i_this);
            }
#if VERSION == VERSION_DEMO
            if (r29 != 0) {
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                i_this->mDamageReaction.mMode = 0;
            }
#endif
        }
        if (i_this->mBehaviorType == BEHAVIOR_GUARDS_AREA && i_this->mDamageReaction.mAction == ACTION_FIGHT_RUN) {
            local_40 = actor->home.pos - actor->current.pos;
            if (i_this->mRangeOrFrozenAnim != 0xFF) {
                fVar9 = (i_this->mRangeOrFrozenAnim * 10.0f) * 1.5f;
            } else {
                fVar9 = 750.0f;
            }
            if (local_40.abs() > fVar9) {
                if (i_this->mBehaviorType == BEHAVIOR_GUARDS_AREA) {
                    i_this->mDamageReaction.mAction = ACTION_STAND;
                }
                i_this->mDamageReaction.mMode = 0x33;
                i_this->mCountDownTimers[1] = 0;
                i_this->mCountDownTimers[2] = 60;
            }
        }
        local_40.x = 0.0f;
        local_40.y = 0.0f;
        local_40.z = actor->speedF;
        if (i_this->mDamageReaction.mAction != ACTION_HUKKI && i_this->mDamageReaction.mAction != ACTION_FAIL && i_this->mDamageReaction.m48A == 0) {
            i_this->mDamageReaction.m482 = actor->current.angle.y;
            cMtx_YrotS(*calc_mtx, actor->current.angle.y + i_this->m0418);
        } else {
            cMtx_YrotS(*calc_mtx, i_this->mDamageReaction.m4D0);
        }
        MtxPosition(&local_40, &local_4c);
        actor->speed.x = local_4c.x;
        actor->speed.z = local_4c.z;
    }
}

/* 00008C5C-00008F9C       .text yoroi_break__FP8tn_classP4cXyzUc */
static void yoroi_break(tn_class* i_this, cXyz* particlePos, u8 param_3) {
    static GXColor prim[] = {
        {0x9F, 0xC1, 0x95, 0x00},
        {0xBC, 0xCF, 0xC8, 0x00},
        {0xBC, 0x98, 0x42, 0x00},
        {0xF0, 0xF5, 0xEB, 0x00},
        {0x0C, 0x14, 0x0A, 0x00},
        {0x50, 0x00, 0x14, 0x00}
    };
    static GXColor env[] = {
        {0x3C, 0x40, 0x50, 0x00},
        {0x60, 0x24, 0x18, 0x00},
        {0x1E, 0x15, 0x36, 0x00},
        {0x9E, 0x94, 0x87, 0x00},
        {0xA8, 0x7D, 0x6C, 0x00},
        {0xEB, 0xD8, 0x82, 0x00}
    };

    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;
    cXyz particle_scale;

    fopAcM_seStart(actor, JA_SE_OBJ_ENM_VAPORIZE, 0);
    if (param_3 == 0) {
        particle_scale.x = 0.6f;
        particle_scale.y = 0.6f;
        particle_scale.z = 0.6f;
    } else {
        particle_scale.x = 0.4f;
        particle_scale.y = 0.4f;
        particle_scale.z = 0.4f;
    }
    dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUBAKUEN, particlePos, NULL, &particle_scale);
    dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, particlePos, NULL, &particle_scale);

    GXColor prmColor;
    f32 tmp = (actor->tevStr.mColorK0.r / 255.0f);
    prmColor.r = tmp * prim[i_this->mArmorColorIndex].r;
    tmp = (actor->tevStr.mColorK0.g / 255.0f);
    prmColor.g = tmp * prim[i_this->mArmorColorIndex].g;
    tmp = (actor->tevStr.mColorK0.b / 255.0f);
    prmColor.b = tmp * prim[i_this->mArmorColorIndex].b;

    GXColor envColor;
    tmp = (actor->tevStr.mColorK0.r / 255.0f);
    envColor.r = tmp * env[i_this->mArmorColorIndex].r;
    tmp = (actor->tevStr.mColorK0.g / 255.0f);
    envColor.g = tmp * env[i_this->mArmorColorIndex].g;
    tmp = (actor->tevStr.mColorK0.b / 255.0f);
    envColor.b = tmp * env[i_this->mArmorColorIndex].b;

    if (param_3 == 0) {
        emitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_TN_YOROIHAHENL00, particlePos);
        if (emitter != NULL) {
            emitter->setGlobalPrmColor(prmColor.r, prmColor.g, prmColor.b);
            emitter->setGlobalEnvColor(envColor.r, envColor.g, envColor.b);
        }
    }
    emitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_TN_YOROIHAHENS00, particlePos);
    if (emitter != NULL) {
        emitter->setGlobalPrmColor(prmColor.r, prmColor.g, prmColor.b);
        emitter->setGlobalEnvColor(envColor.r, envColor.g, envColor.b);
    }
}

/* 00008F9C-00009E2C       .text damage_check__FP8tn_class */
static u8 damage_check(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 r3;
    s8 r26_2;
    mant_class* mant_actor;
    csXyz local_a0;
    csXyz local_a8;
    CcAtInfo atInfo;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    atInfo.mDamage = 0;
    atInfo.pParticlePos = NULL;
    u8 r26 = 0;
    u8 r30 = 0;
    i_this->mDamageReaction.mStts.Move();
    if (i_this->m1444 != 0) {
        i_this->m1444--;
        MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(TN_MAIN_JNT_J_TN_ITEM_L1_e), *calc_mtx);
        cXyz local_50(0.0f, 0.0f, 0.0f);
        MtxPosition(&local_50, &i_this->m13E4);
        i_this->mDefenceSph.SetR(70.0f);
        i_this->mDefenceSph.SetC(i_this->m13E4);
    } else {
        cXyz local_5c = actor->current.pos;
        local_5c.y = -20000.0f;
        i_this->mDefenceSph.SetC(local_5c);
    }
    dComIfG_Ccsp()->Set(&i_this->mDefenceSph);
    if (i_this->mDefenceSph.ChkTgHit()) {
        def_se_set(actor, i_this->mDefenceSph.GetTgHitObj(), 0x40);
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
        cXyz local_68(0.0f, 0.0f, -10.0f);
        MtxPosition(&local_68, &i_this->mDamageReaction.m42C);
        i_this->mDamageReaction.m4D4 = -10.0f;
        return 0;
    }
    if (i_this->m03F0 == 0 && (i_this->mHeadSph.ChkTgHit() || i_this->mTgCyl.ChkTgHit())) {
        i_this->m03F0 = REG0_S(7) + 5;
        if (i_this->mHeadSph.ChkTgHit()) {
            r26 = 1;
            atInfo.mpObj = i_this->mHeadSph.GetTgHitObj();
            atInfo.pParticlePos = i_this->mHeadSph.GetTgHitPosP();
        } else if (i_this->mTgCyl.ChkTgHit()) {
            r26 = 2;
            atInfo.mpObj = i_this->mTgCyl.GetTgHitObj();
            atInfo.pParticlePos = i_this->mTgCyl.GetTgHitPosP();
        }
        cCcD_Obj* hitObj = atInfo.mpObj;
        if (hitObj->ChkAtType(AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW)) {
            s8 r25 = 0;
            if (hitObj->ChkAtType(AT_TYPE_ICE_ARROW)) {
                if ((r26 == 2 && !(i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR)) ||
                    (r26 == 1 && !(i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_HELMET)))
                {
                    i_this->mEnemyIce.mFreezeDuration = REG0_S(4) + 60;
                    i_this->mEnemyIce.m00C = 1;
                    actor->health = actor->health + 4;
                    i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                    i_this->mDamageReaction.mMode = -10;
                    r25 = 1;
                    anm_init(i_this, dRes_INDEX_TN_BCK_AHAKAI1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1);
                    tate_anm_init(i_this, dRes_INDEX_TN_BCK_AHAKAI1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 0.0f);
                    yoroi_anm_init(i_this, dRes_INDEX_TN_BCK_YHAKAI1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 0.0f);
                }
            } else {
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                r25 = 2;
            }
            if (r25 != 0) {
                if (r25 == 2) {
                    for (s32 i = 0; i < ARRAY_SSIZE(i_this->mParts); i++) {
                        if (i <= 1 && i_this->mParts[i].m08 >= 0) {
                            yoroi_break(i_this, &i_this->mParts[i].m0C, (u8)i);
                        }
                        i_this->mParts[i].m08 = -1;
                    }
                }
                enemy_fire_remove(&i_this->mEnemyFire);
                i_this->m0430 = 0;
                i_this->m144C[0].remove();
                i_this->m144C[1].remove();
                i_this->m144C[2].remove();
                i_this->mSmokeCb1.remove();
                i_this->mSmokeCb2.remove();
                i_this->mDamageReaction.mParticleCallBack.remove();
                if (i_this->m0C34 != 0) {
                    i_this->m0C38 = 2;
                }
                if (i_this->mMantPcId != 0xFFFF) {
                    mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
                    if (mant_actor != NULL) {
                        fopAcM_delete(mant_actor);
                    }
                    i_this->mMantPcId = 0xFFFF;
                }
                return 0;
            }
        }
        if (atInfo.mpObj->ChkAtType(AT_TYPE_FIRE | AT_TYPE_FIRE_ARROW)) {
            if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
                i_this->mEnemyFire.mFireDuration = REG0_S(2) + 40;
            } else {
                i_this->mEnemyFire.mFireDuration = REG0_S(2) + 100;
            }
        }
        if ((r26 == 2 && (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR)) ||
            (r26 == 1 && (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_HELMET)))
        {
            fopAc_ac_c* hitActor = dCc_GetAc(atInfo.mpObj->GetAc());
            if (hitActor != NULL && fopAcM_GetName(hitActor) == fpcNm_PLAYER_e) {
                if (r26 == 1) {
                    if (player->getCutType() == daPy_py_c::CUT_TYPE_BT_JUMPCUT) {
                        at_power_check(&atInfo);
                        mDoAud_onEnemyDamage();
                        mDoAud_bgmHitSound(atInfo.mHitSoundId);
                        i_this->m02DD |= 2;
                        fopAcM_OffStatus(actor, fopAcStts_CULL_e);
                        i_this->mDamageReaction.mAction = ACTION_D_SIT;
                        i_this->mDamageReaction.mMode = 10;
                        dScnPly_ply_c::setPauseTimer(REG0_S(7) + 6);
                        fopAcM_seStart(actor, JA_SE_CM_TN_HELMET_OUT, 0);
                        cXyz* particlePos = i_this->mTgCyl.GetTgHitPosP();
                        cXyz local_74(2.0f, 2.0f, 2.0f);
                        local_a0.x = local_a0.z = 0;
                        local_a0.y = fopAcM_searchPlayerAngleY(actor);
                        dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, particlePos, &local_a0, &local_74);
                        dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, particlePos);
                    } else {
                        def_se_set(actor, atInfo.mpObj, 0x40);
                    }
                } else if (r26 == 2) {
                    r3 = i_this->mTargetAngle - actor->current.angle.y;
                    if (r3 < 0) {
                        r3 = -r3;
                    }
                    cXyz* particlePos = i_this->mTgCyl.GetTgHitPosP();
                    cXyz local_80(2.0f, 2.0f, 2.0f);
                    local_a8.x = local_a8.z = 0;
                    local_a8.y = fopAcM_searchPlayerAngleY(actor);
                    r26_2 = false;
                    if (i_this->mMantPcId != 0xFFFF) {
                        mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
                        if (mant_actor != NULL && (mant_actor->m2834 != 0 || mant_actor->m2836 != 0)) {
                            r26_2 = true;
                        }
                    }
                    if ((u16)r3 > 0x4000 && !r26_2) {
                        i_this->m02DD |= 1;
                        fopAcM_OffStatus(actor, fopAcStts_CULL_e);
                        i_this->mDamageReaction.mAction = ACTION_D_SIT;
                        i_this->mDamageReaction.mMode = 0;
                        dScnPly_ply_c::setPauseTimer(REG0_S(7) + 6);
                        at_power_check(&atInfo);
                        mDoAud_onEnemyDamage();
                        mDoAud_bgmHitSound(atInfo.mHitSoundId);
                        dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, particlePos, &local_a8, &local_80);
                        dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, particlePos);
                        if (i_this->mMantPcId != 0xFFFF) {
                            mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
                            if (mant_actor != NULL) {
                                fopAcM_delete(mant_actor);
                            }
                            i_this->mMantPcId = 0xFFFF;
                        }
                        def_se_set(actor, atInfo.mpObj, 0x21);
                        fopAcM_monsSeStart(actor, JA_SE_CV_TN_NO_DAMAGE, 0);
                    } else {
                        def_se_set(actor, atInfo.mpObj, 0x40);
                        dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, particlePos, &local_a8, &local_80);
                        i_this->m1402 = 0xF;
                        at_power_check(&atInfo);
                        actor->health -= atInfo.mDamage;
                        if (actor->health <= 0) {
                            fopAcM_OnStatus(actor, fopAcStts_UNK200000_e);
                            i_this->mRemainingEquipmentPieces &= ~EQUIPMENT_PIECE_BODY_ARMOR;
                            i_this->mDamageReaction.mAction = ACTION_D_SIT;
                            i_this->mDamageReaction.mMode = 10;
                            dScnPly_ply_c::setPauseTimer(REG0_S(7) + 6);
                            i_this->mParts[0].m08 = -1;
                            yoroi_break(i_this, &i_this->mParts[0].m0C, 0);
                            if (i_this->mEquipmentType & EQUIPMENT_HELMET) {
                                actor->health = 20;
                            } else {
                                actor->health = 10;
                            }
                            if (i_this->mMantPcId != 0xFFFF) {
                                mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
                                if (mant_actor != NULL) {
                                    fopAcM_delete(mant_actor);
                                }
                                i_this->mMantPcId = 0xFFFF;
                            }
                        }
                    }
                }
                return 0;
            }
            if (!(atInfo.mpObj->ChkAtType(DEMO_SELECT(AT_TYPE_NORMAL_ARROW | AT_TYPE_HOOKSHOT, AT_TYPE_HOOKSHOT) | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW))) {
                def_se_set(actor, atInfo.mpObj, 0x40);
            }
            return 0;
        }
        s8 r25 = actor->health;
        at_power_check(&atInfo);
        if (atInfo.mResultingAttackType == 10 || atInfo.mResultingAttackType == 0xe) {
            actor->health = 20;
        }
        actor->stealItemBitNo = i_this->m1400;
        atInfo.mpActor = cc_at_check(actor, &atInfo);
        if (atInfo.mResultingAttackType == 10 || atInfo.mResultingAttackType == 0xe) {
            actor->health = r25;
            if (atInfo.mResultingAttackType == 0xe && i_this->m1400 == 0) {
                i_this->m1400 = 1;
            }
        }
        i_this->m03F2 = 0x19;
        dKy_Sound_set(actor->current.pos, 100, fopAcM_GetID(actor), 5);
        if (l_tnHIO.m007 == 1) {
            actor->health = 10;
        }
        if (l_tnHIO.m007 == 2) {
            actor->health = 0;
        }
        i_this->m141C |= atInfo.mPlCutBit;
        if (atInfo.mResultingAttackType == 10) {
            i_this->m1434 = DEMO_SELECT(REG13_S(3), REG0_S(3)) + 8;
        } else {
            i_this->m1434 = 0;
        }
        if (atInfo.mResultingAttackType == 1) {
            r3 = i_this->mTargetAngle - actor->current.angle.y;
            if (r3 < 0) {
                r3 = -r3;
            }
            if (player->getCutType() == daPy_py_c::CUT_TYPE_BT_JUMPCUT) {
                r30 = 2;
            } else if ((u16)r3 > 0x4000) {
                if (atInfo.mbDead != 0) {
                    r30 = 3;
                } else if (r26 == 1) {
                    r30 = 4;
                } else {
                    r30 = 5;
                }
            } else if (atInfo.mbDead != 0) {
                r30 = 1;
            } else if (r26 == 1) {
                r30 = 4;
            } else {
                r30 = 5;
            }
        } else if (atInfo.mResultingAttackType == 2) {
            r30 = 7;
            cMtx_YrotS(*calc_mtx, atInfo.m0C.y);
        } else {
            if (atInfo.mbDead != 0) {
                r30 = 7;
            } else {
                r30 = 4;
            }
            cMtx_YrotS(*calc_mtx, atInfo.m0C.y);
        }
    }
    switch (r30) {
        case 1:
            i_this->mDamageReaction.m424 |= 0x10;
            i_this->mDamageReaction.m428 = 26.0f;
            cMtx_YrotS(*calc_mtx, i_this->mTargetAngle);
            break;
        case 2:
            i_this->mDamageReaction.m424 |= 0x40;
            cMtx_YrotS(*calc_mtx, actor->current.angle.y + 0x8000);
            i_this->mDamageReaction.m428 = 26.0f;
            break;
        case 3:
            i_this->mDamageReaction.m424 |= 0x40;
            i_this->mDamageReaction.m428 = 26.0f;
            cMtx_YrotS(*calc_mtx, i_this->mTargetAngle);
            break;
        case 4:
            i_this->mDamageReaction.m424 |= 0x10;
            i_this->mDamageReaction.m428 = 23.0f;
            cMtx_YrotS(*calc_mtx, i_this->mTargetAngle);
            break;
        case 5:
            i_this->mDamageReaction.m424 |= 0x20;
            i_this->mDamageReaction.m428 = 23.0f;
            cMtx_YrotS(*calc_mtx, i_this->mTargetAngle);
            anm_init(i_this, dRes_INDEX_TN_BCK_BDOWN_A1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mDamageReaction.m48A = 10;
            i_this->mDamageReaction.m474 = 5000.0f;
            i_this->mDamageReaction.m70E = 7;
            if (i_this->m041A == 0) {
                i_this->m041A = 3;
                i_this->m0428.x = 0;
            }
            break;
        case 7:
            i_this->mDamageReaction.m424 |= 0x10;
            i_this->mDamageReaction.m428 = 26.0f;
    }
    if (i_this->mDamageReaction.m424 != 0) {
        cXyz local_8c(0.0f, 0.0f, -10.0f);
        MtxPosition(&local_8c, &i_this->mDamageReaction.m42C);
        if (i_this->mDamageReaction.m428 < 25.0f) {
            i_this->mDamageReaction.m4D4 = -l_tnHIO.m0D0;
        } else {
            i_this->mDamageReaction.m428 = cM_rndF(10.0f) + 70.0f;
        }
    }
    if (r30 != 0) {
        if (actor->health <= 0 && atInfo.mbDead != 0) {
            fopAcM_monsSeStart(actor, JA_SE_CV_TN_DIE, 0);
            if (fopAcM_CheckStatus(actor, fopAcStts_BOSS_e)) {
                if (s_check == 0) {
                    i_this->m14F8 = 0x32;
                    mDoAud_subBgmStop();
                } else {
                    s_check = 0;
                }
            }
        } else {
            fopAcM_monsSeStart(actor, JA_SE_CV_TN_DAMAGE, 0);
        }
    }
    return atInfo.mDamage;
}

static s32 j_dt[] = {TN_MAIN_JNT_J_TN_MUNE1_e, TN_MAIN_JNT_J_TN_ATAMA1_e, TN_MAIN_JNT_J_TN_ITEM_L1_e};

/* 00009E68-0000AC54       .text part_move__FP8tn_classi */
static void part_move(tn_class* i_this, int partIndex) {
    fopAc_ac_c* actor = &i_this->actor;
    mant_class* mant_actor;
    J3DModel* model;
    int iVar12;
    tn_p* part;
    f32 dVar14;
    f32 fVar15;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    part = &i_this->mParts[partIndex];
    dBgS_GndChk gndChk;
    cXyz local_134(0.0f, 0.0f, 0.0f);
    part->m42++;
    iVar12 = j_dt[partIndex];
    if (part->m44 != 0) {
        part->m44--;
    }
    switch (part->m08) {
        case 0:
            MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(iVar12), *calc_mtx);
            MtxPosition(&local_134, &part->m0C);
            if (((i_this->m02DD & 1) != 0 && partIndex == 0) ||
                ((i_this->m02DD & 2) != 0 && partIndex == 1) ||
                ((i_this->m02DD & 4) != 0 && partIndex == 2))
            {
                part->m08 = 1;
                if (partIndex == 0) {
                    part->m44 = 0xd;
                    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
                    local_134.x = 0.0f;
                    local_134.y = 0.0f;
                    local_134.z = REG0_F(7) + 15.0f;
                    MtxPosition(&local_134, &part->m24);
                } else {
                    part->m44 = 0;
                }
            }
            break;
        case 1:
            MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(iVar12), *calc_mtx);
            MtxPosition(&local_134, &part->m0C);
            if (part->m44 == 0) {
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_DROP_SWORD, 0);
                part->m08 = 5;
                part->m44 = 30;
                part->m09 = 1;
                part->m30.y = actor->current.angle.y + REG0_S(5);
                part->m30.z = 0x4000;
                if (partIndex == 0) {
                    i_this->mRemainingEquipmentPieces &= ~EQUIPMENT_PIECE_BODY_ARMOR;
                    fopAcM_OnStatus(actor, fopAcStts_UNK200000_e);
                } else if (partIndex == 1) {
                    i_this->mRemainingEquipmentPieces &= ~EQUIPMENT_PIECE_HELMET;
                    cMtx_YrotS(*calc_mtx, player->shape_angle.y);
                    local_134.x = 0.0f;
                    local_134.y = 20.0f;
                    local_134.z = -20.0f;
                    MtxPosition(&local_134, &part->m24);
                    part->m36.x = cM_rndFX(3000.0f);
                    part->m36.y = cM_rndFX(3000.0f);
                } else if (partIndex == 2) {
                    i_this->mRemainingEquipmentPieces &= ~EQUIPMENT_PIECE_SHIELD;
                }
                i_this->m02DC--;
            }
            break;
        case 5:
            part->m18 = part->m0C;
            part->m0C += part->m24;
            part->m24.y = part->m24.y - 5.0f;
            part->m30 += part->m36;
            local_134 = part->m0C - part->m18;
            if (local_134.abs() > 0.0f) {
                dBgS_LinChk linChk;
                cMtx_YrotS(*calc_mtx, cM_atan2s(local_134.x, local_134.z));
                local_134.x = 0.0f;
                local_134.y = 30.0f;
                local_134.z = 20.0f;
                cXyz cStack_140;
                MtxPosition(&local_134, &cStack_140);
                local_134 = part->m0C;
                local_134.y += 30.0f;
                cStack_140 += part->m0C;
                linChk.Set(&local_134, &cStack_140, actor);
                if (dComIfG_Bgsp()->LineCross(&linChk)) {
                    part->m0C.x = part->m18.x;
                    part->m0C.z = part->m18.z;
                    part->m24.x *= -0.3f;
                    part->m24.z *= -0.3f;
                }
            }
            local_134 = part->m0C;
            local_134.y += 100.0f;
            gndChk.SetPos(&local_134);
            fVar15 = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (partIndex == 0) {
                fVar15 += 35.0f;
            } else if (partIndex == 1) {
                fVar15 += DEMO_SELECT(REG13_F(1), REG0_F(1));
            } else if (partIndex == 2) {
                fVar15 += -15.0f;
            } else if (partIndex == 3) {
                fVar15 += DEMO_SELECT(REG13_F(3), REG0_F(3));
            }
            if (part->m0C.y <= fVar15) {
                part->m0C.y = fVar15;
                if (part->m24.y < -30.0f) {
                    if (partIndex == 1) {
                        part->m24.y = 20.0f;
                        part->m24.x = cM_rndFX(20.0f);
                        part->m24.z = cM_rndFX(20.0f);
                        part->m36.x = cM_rndFX(3000.0f);
                        part->m36.y = cM_rndFX(3000.0f);
                        fopAcM_seStart(actor, JA_SE_OBJ_TN_HELMET_FALL, 0);
                    } else {
                        part->m24.y = 10.0f;
                        part->m24.x *= 0.5f;
                        part->m24.z *= 0.5f;
                        fopAcM_seStart(actor, JA_SE_OBJ_TN_ARMOR_FALL, 0);
                    }
                    part->m44 = 0x14;
                } else {
                    part->m24.x = part->m24.y = part->m24.z = 0.0f;
                    part->m36.x = part->m36.y = part->m36.z = 0;
                    cLib_addCalcAngleS2(&part->m30.x, 0, 1, 0xc00);
                    cLib_addCalcAngleS2(&part->m30.z, 0x4000, 1, 0xc00);
                }
            }
            if (part->m44 == 1) {
                part->m08 = -1;
                yoroi_break(i_this, &part->m0C, partIndex);
                if (partIndex == 0 && i_this->mMantPcId != 0xFFFF) {
                    mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
                    if (mant_actor != NULL) {
                        fopAcM_delete(mant_actor);
                    }
                    i_this->mMantPcId = 0xFFFF;
                }
            }
            break;
    }
    if (partIndex == 0) {
        model = i_this->mpArmorMorf->getModel();
    } else {
        model = part->mpPartModel;
    }
    switch (part->m09) {
        case 0:
            MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(iVar12), *calc_mtx);
            if (partIndex == 0 && i_this->m1402 != 0) {
                fVar15 = (i_this->m1402 * cM_scos(i_this->m1402 * 0x5100) * -0.0033f) + 1.0f;
                MtxScale(fVar15, fVar15, fVar15, true);
                dVar14 = (i_this->m1402 * (REG0_F(16) + 0.01f));
                MtxRotY(dVar14 * cM_scos(i_this->m1402 * 0x3900), 1);
                MtxRotX(dVar14 * cM_ssin(i_this->m1402 * 0x4200), 1);
            }
#if VERSION == VERSION_DEMO
            if (partIndex == 2) {
                cMtx_ZrotM(*calc_mtx, i_this->m0414_demo);
            }
#endif
            model->setBaseTRMtx(*calc_mtx);
            break;
        case 1:
            MtxTrans(part->m0C.x, part->m0C.y, part->m0C.z, false);
            cMtx_YrotM(*calc_mtx, part->m30.y);
            cMtx_XrotM(*calc_mtx, part->m30.x);
            cMtx_ZrotM(*calc_mtx, part->m30.z);
            model->setBaseTRMtx(*calc_mtx);
            break;
    }
    if (partIndex == 0) {
        i_this->mpArmorMorf->calc();
        if (i_this->mMantPcId != 0xFFFF) {
            mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
            if (mant_actor != NULL) {
                MTXCopy(i_this->mpArmorMorf->getModel()->getAnmMtx(REG6_S(5) + (s16)TN_YOROI1_JNT_J_YOROI_KATA_R1_e), *calc_mtx);
                local_134.x = DEMO_SELECT(REG13_F(0), REG0_F(0)) + 2.0f;
                local_134.y = DEMO_SELECT(REG13_F(1), REG0_F(1)) + 15.0f;
                local_134.z = DEMO_SELECT(REG13_F(2), REG0_F(2)) + -43.0f;
                MtxPosition(&local_134, &mant_actor->m1BE0);
                MTXCopy(i_this->mpArmorMorf->getModel()->getAnmMtx(REG6_S(6) + (s16)TN_YOROI1_JNT_J_YOROI_KATA_L1_e), *calc_mtx);
                local_134.x = DEMO_SELECT(REG13_F(3), REG0_F(3)) + 2.0f;
                local_134.y = DEMO_SELECT(REG13_F(4), REG0_F(4)) + 15.0f;
                local_134.z = DEMO_SELECT(REG13_F(5), REG0_F(5)) + 43.0f;
                MtxPosition(&local_134, &mant_actor->m1BEC);
                mant_actor->current.pos = actor->eyePos;
                mant_actor->current.angle = actor->current.angle;
            }
        }
    }
    if (partIndex < 3) {
        part->mpPartBrkAnm->setFrame(i_this->mArmorColorIndex);
    }
}

/* 0000AC54-0000AEA8       .text spin_blur_set__FP8tn_class */
static void spin_blur_set(tn_class* i_this) {
    static const GXColor turn_prim0 = {0x40, 0x40, 0xFF, 0xFF};
    static const GXColor turn_prim1 = {0xDC, 0xDC, 0xFF, 0xFF};
    static const GXColor turn_env = {0x78, 0x78, 0xFF, 0xFF};
    static const GXColor roll_prim0 = {0xC8, 0xFF, 0x40, 0xFF};
    static const GXColor roll_prim1 = {0xFF, 0xFF, 0xDC, 0xFF};
    static const GXColor roll_env = {0xC8, 0xFF, 0x78, 0xFF};
    static u16 spin_eff_name[] = {dPa_name::ID_AK_JN_ROUNDATTACK00, dPa_name::ID_AK_JN_ROUNDATTACK01, dPa_name::ID_AK_JN_ROUNDATTACK02};

    fopAc_ac_c* actor = &i_this->actor;
    const GXColor* pPrmColor;
    JPABaseEmitter* emitter;
    const GXColor* pEnvColor;
    cXyz local_30;
    cXyz cStack_3c;

    if (i_this->m14F4 != 0) {
        local_30.set(0.0f, 0.0f, REG0_F(4) + 250.0f);
        MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(TN_MAIN_JNT_J_TN_ITEM_R1_e), *calc_mtx);
        MtxPosition(&local_30, &cStack_3c);
        local_30 = cStack_3c - actor->current.pos;
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m147C); i++) {
            cMtx_YrotS(*calc_mtx, i * (REG0_S(2) + -800));
            MtxPosition(&local_30, &i_this->m147C[i]);
            VECAdd(&i_this->m147C[i], &actor->current.pos, &i_this->m147C[i]);
        }
        for (s32 i = 0; i <= 2; i++) {
            if (i_this->m14F6 == 0) {
                i_this->m144C[i].remove();
            } else {
                if (i_this->m14F4 == 1) {
                    if (i_this->m14F6 >= 5) {
                        if (i == 1) {
                            pPrmColor = &roll_prim1;
                        } else {
                            pPrmColor = &roll_prim0;
                        }
                        pEnvColor = &roll_env;
                    } else {
                        if (i == 1) {
                            pPrmColor = &turn_prim1;
                        } else {
                            pPrmColor = &turn_prim0;
                        }
                        pEnvColor = &turn_env;
                    }
                    emitter = dComIfGp_particle_set(
                        spin_eff_name[i],
                        &actor->current.pos,
                        &actor->shape_angle,
                        &actor->scale,
                        0xFF,
                        &i_this->m144C[i],
                        fopAcM_GetRoomNo(actor),
                        pPrmColor,
                        pEnvColor,
                        NULL
                    );
                    if (emitter != NULL) {
                        emitter->setGlobalParticleWidthScale(REG0_F(17) + 1.5f);
                    }
                    i_this->m14F4++;
                }
                i_this->m144C[i].setPosArray(i_this->m147C, 10);
            }
        }
        if (i_this->m14F6 == 0) {
            i_this->m14F4 = 0;
        } else {
            i_this->m14F6--;
        }
    }
    return;
}

/* 0000AEA8-0000BCE4       .text daTn_Execute__FP8tn_class */
static BOOL daTn_Execute(tn_class* i_this) {
    /* Nonmatching - retail-only regalloc */
    fopEn_enemy_c* actor = (fopEn_enemy_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    mant_class* mant_actor;
    daBoko_c* boko_actor;

#if VERSION > VERSION_DEMO
    if (i_this->m1520 != 0) {
        i_this->m1520--;
        if (i_this->m1520 == 0) {
            fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
        }
    }
#endif

    if (enemy_ice(&i_this->mEnemyIce)) {
        if (i_this->mEnemyIce.mLightShrinkTimer == 0) {
            if (i_this->mEnemyIce.mFreezeTimer == 23) {
                i_this->mpBodyMorf->setPlaySpeed(1.0f);
                i_this->mpShieldMorf->setPlaySpeed(1.0f);
                i_this->mpArmorMorf->setPlaySpeed(1.0f);
                fopAcM_monsSeStart(actor, JA_SE_CV_TN_JUMP, 0);
            }
            i_this->mpBodyMorf->play(&actor->eyePos, 0, 0);
            i_this->mpArmorMorf->play(NULL, 0, 0);
            i_this->mpShieldMorf->play(NULL, 0, 0);
        }
        J3DModel* model = i_this->mpBodyMorf->getModel();
        model->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpBodyMorf->calc();
        i_this->mpShieldMorf->calc();
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->mParts); i++) {
            if (i_this->mParts[i].m08 >= 0) {
                part_move(i_this, i);
            }
        }
        i_this->m02DD = 0;
        if (i_this->mEnemyIce.mFreezeTimer == 1) {
            path_check(i_this);
            wait_set(i_this);
            tate_anm_init(i_this, dRes_INDEX_TN_BCK_ATATE_ON1_e, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f);
        }
        return TRUE;
    }
    if (actor->home.pos.y - actor->current.pos.y > 4000.0f) {
        fopAcM_delete(actor);
        return TRUE;
    }
    u8 r25 = 0;
    if (l_tnHIO.m006 == 0 || CPad_CHECK_TRIG_B(0) || CPad_CHECK_HOLD_Y(0)) {
        i_this->m03D8++;
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->mCountDownTimers); i++) {
            if (i_this->mCountDownTimers[i] != 0) {
                i_this->mCountDownTimers[i]--;
            }
        }
        if (i_this->m03EA != 0) {
            i_this->m03EA--;
        }
        if (i_this->m03FC != 0) {
            i_this->m03FC--;
        }
        if (i_this->m1402 != 0) {
            i_this->m1402--;
        }
        if (i_this->mDamageReaction.m48A != 0) {
            i_this->mDamageReaction.m48A--;
        }
        if (i_this->m03F0 != 0) {
            i_this->m03F0--;
        }
        if (i_this->m03F2 != 0) {
            i_this->m03F2--;
        }
        if (i_this->m140C != 0) {
            boko_actor = (daBoko_c*)fopAcM_SearchByID(i_this->mBokoPcId);
            if (boko_actor != NULL) {
                i_this->m140C = 0;
                fopAcM_setCarryNow(boko_actor, 0);
            }
        }
        if (i_this->m02C1 != 0) {
            if ((DEMO_SELECT(REG17_S(0), REG0_S(0)) != 0) || (dComIfGs_isSwitch(i_this->m02C1 - 1, fopAcM_GetRoomNo(actor)))) {
                i_this->m02C1 = 0;
            } else {
                fopAcM_OffStatus(actor, 0);
                actor->attention_info.flags = 0;
                boko_actor = (daBoko_c*)fopAcM_SearchByID(i_this->mBokoPcId);
                if (boko_actor != NULL) {
                    MtxTrans(-10000.0f, -10000.0f, 0.0f, false);
                    boko_actor->setMatrix(*calc_mtx);
                }
                if (i_this->mMantPcId != 0xFFFF) {
                    mant_actor = (mant_class*)fopAcM_SearchByID(i_this->mMantPcId);
                    if (mant_actor != NULL) {
                        mant_actor->m1BE0.x = -10000.0f;
                        mant_actor->m1BE0.y = 20000.0f;
                        mant_actor->m1BE0.z = -21000.0f;
                        mant_actor->m1BEC.x = -10000.0f;
                        mant_actor->m1BEC.y = 20000.0f;
                        mant_actor->m1BEC.z = -21000.0f;
                    }
                }
                return TRUE;
            }
        }
        if (i_this->m14F8 == 0) {
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
        } else {
            actor->attention_info.flags = 0;
            fopAcM_OffStatus(actor, 0);
        }
        if (i_this->m03EE == 0) {
            i_this->mpBodyMorf->play(&actor->eyePos, 0, 0);
            i_this->mpArmorMorf->play(NULL, 0, 0);
            if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD) {
                i_this->mpShieldMorf->play(NULL, 0, 0);
            }
        }
        i_this->mpBrkAnm->setFrame(i_this->mArmorColorIndex);
        actor->setBtAttackData(100.0f, 100.0f, 10000.0f, fopEn_enemy_c::OPENING_NONE);
        actor->setBtNowFrame(0.0f);
        r25 = damage_check(i_this);
        Tn_move(i_this);
        demo_camera(i_this);
        ground_smoke_set(i_this);
        if (i_this->m03EE != 0) {
            i_this->m03EE--;
        }
        i_this->mDamageReaction.mpEnemy = actor;
        i_this->mDamageReaction.mEnemyType = damagereaction::TYPE_DARKNUT;
    }
    actor->shape_angle = actor->current.angle;
    int r3 = damage_reaction(&i_this->mDamageReaction);
    if (r3 != 0) {
        i_this->m0430 = 1;
        i_this->m1408 = fpcM_ERROR_PROCESS_ID_e;
        switch (r3) {
            case 1:
                anm_init(i_this, dRes_INDEX_TN_BCK_BDOWN_A1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                if (i_this->m0C34 != 0 && (actor->health <= 0 || r25 >= 4 || cM_rndF(1.0f) < 0.5f)) {
                    i_this->m0C38 = 1;
                }
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                break;
            case 2:
                anm_init(i_this, dRes_INDEX_TN_BCK_BDOWN_U1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                break;
            case 5:
                if (i_this->mDamageReaction.mAction != ACTION_FIGHT_RUN && i_this->mDamageReaction.mAction != ACTION_HUKKI) {
                    wait_set(i_this);
                    i_this->mDamageReaction.mAction = ACTION_FIGHT_RUN;
                    i_this->mDamageReaction.mMode = 0;
                    i_this->mCountDownTimers[1] = 30;
                }
                i_this->m041A = 5;
                i_this->m0428.x = -0x4000;
                break;
            case 10:
                wait_set(i_this);
                i_this->mDamageReaction.mMode = 2;
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
                path_check(i_this);
                break;
            case 0x14:
                i_this->m041A = 1;
                i_this->m0428.x = -0x4000;
                i_this->m0430 = l_tnHIO.m020 + 0x10;
                i_this->m0432 = 1;
                i_this->mDamageReaction.m4C8[2] = l_tnHIO.m080;
                break;
            case 0x15:
                i_this->m041A = 1;
                i_this->m0428.x = 0;
                i_this->mDamageReaction.m4C8[2] = l_tnHIO.m080;
                break;
            case 0x1e:
                anm_init(i_this, dRes_INDEX_TN_BCK_BDOWN_U1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                if (i_this->m0C34 != 0) {
                    i_this->m0C38 = 1;
                }
                i_this->mDamageReaction.mAction = ACTION_JYUNKAI;
        }
    }
    J3DModel* model = i_this->mpBodyMorf->getModel();
    model->setBaseTRMtx(*calc_mtx);
    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD) {
        model = i_this->mpShieldMorf->getModel();
        model->setBaseTRMtx(*calc_mtx);
    }
    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_SHIELD) {
        i_this->mpShieldMorf->calc();
    }
    i_this->mpBodyMorf->calc();
    enemy_fire(&i_this->mEnemyFire);
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->current.angle.y);
    cXyz local_a8;
    local_a8.x = 0.0f;
    local_a8.y = 0.0f;
    local_a8.z = 35.0f;
    cXyz cStack_b4;
    MtxPosition(&local_a8, &cStack_b4);
    i_this->mCoCyl.SetC(cStack_b4);
    dComIfG_Ccsp()->Set(&i_this->mCoCyl);
    dComIfG_Ccsp()->SetMass(&i_this->mCoCyl, 3);
    cXyz local_c0 = i_this->m1384;
    cXyz local_cc = actor->current.pos;
    if (i_this->m03F0 != 0) {
        local_c0.y -= 20000.0f;
        local_cc.y -= 20000.0f;
    }
    if (i_this->mDamageReaction.mAction == ACTION_DEFENCE) {
        local_c0.y -= 20000.0f;
        local_cc.y -= 100.0f;
    }
    i_this->mTgCyl.SetC(local_cc);
    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_BODY_ARMOR) {
        i_this->mTgCyl.OnTgShield();
    } else {
        i_this->mTgCyl.OffTgShield();
    }
    dComIfG_Ccsp()->Set(&i_this->mTgCyl);
    i_this->mHeadSph.SetC(local_c0);
    if (i_this->mRemainingEquipmentPieces & EQUIPMENT_PIECE_HELMET) {
        if (player->getCutType() == daPy_py_c::CUT_TYPE_CUT_KESA) {
            i_this->mHeadSph.OffTgSetBit();
        } else {
            i_this->mHeadSph.OnTgSetBit();
            i_this->mHeadSph.OnTgShield();
            i_this->mHeadSph.SetTgHitMark(dCcg_TgHitMark_Purple_e);
        }
    } else {
        i_this->mHeadSph.OffTgShield();
        i_this->mHeadSph.SetTgHitMark(dCcG_TgHitMark_Unk1_e);
    }
    dComIfG_Ccsp()->Set(&i_this->mHeadSph);
    if (i_this->m041A != 0) {
        i_this->m041A--;
        if (i_this->m041A == 0) {
            i_this->m0428.y = actor->current.angle.y;
            dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &i_this->m1384, &i_this->m0428);
        }
    }
    if (i_this->mDamageReaction.mAcch.ChkGroundHit()) {
        s16 r23 = 0x7FFF;
        s16 r22 = 0x7FFF;
        if (i_this->mDamageReaction.m480 != 0) {
            dBgS_GndChk gndChk;
            f32 f31 = 100.0f;
            cXyz pos;
            pos = actor->current.pos;
            pos.y += (50.0f - i_this->mDamageReaction.m44C.y);
            gndChk.SetPos(&pos);
            pos.y = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (pos.y != -G_CM3D_F_INF) {
                Vec tmp;
                tmp.x = pos.x;
                tmp.y = pos.y + 50.0f;
                tmp.z = pos.z + f31;
                gndChk.SetPos(&tmp);
                f32 f1 = dComIfG_Bgsp()->GroundCross(&gndChk);
                if (f1 != -G_CM3D_F_INF) {
                    r22 = (s16)-cM_atan2s(f1 - pos.y, tmp.z - pos.z);
                    if (r22 > 0x2000 || r22 < -0x2000) {
                        r22 = 0;
                    }
                }
                tmp.x = pos.x + f31;
                tmp.y = pos.y + 50.0f;
                tmp.z = pos.z;
                gndChk.SetPos(&tmp);
                f1 = dComIfG_Bgsp()->GroundCross(&gndChk);
                if (f1 != -G_CM3D_F_INF) {
                    r23 = (s16)cM_atan2s(f1 - pos.y, tmp.x - pos.x);
                    if (r23 > 0x2000 || r23 < -0x2000) {
                        r23 = 0;
                    }
                }
            }
        } else {
            r23 = 0;
            r22 = 0;
        }
        if (r22 != 0x7FFF) {
            cLib_addCalcAngleS2(&i_this->mDamageReaction.m48C.x, r22, 1, 0x400);
        }
        if (r23 != 0x7FFF) {
            cLib_addCalcAngleS2(&i_this->mDamageReaction.m48C.z, r23, 1, 0x400);
        }
    }
    if (i_this->m0C34 != 0) {
        boko_actor = (daBoko_c*)fopAcM_SearchByID(i_this->mBokoPcId);
        if (boko_actor != NULL) {
            if (fopAcM_checkCarryNow(boko_actor)) {
                MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(TN_MAIN_JNT_J_TN_ITEM_R1_e), *calc_mtx);
                cMtx_YrotM(*calc_mtx, REG8_S(1));
                cMtx_XrotM(*calc_mtx, REG8_S(2));
                cMtx_ZrotM(*calc_mtx, REG8_S(3) + 0x8000);
                MtxTrans(REG8_F(9), REG8_F(10), REG8_F(11) + 85.0f, true);
                boko_actor->setMatrix(*calc_mtx);
            } else {
                fopAcM_setCarryNow(boko_actor, 0);
            }
        } else if (i_this->m140C == 0) {
            i_this->m0C34 = 0;
        }
        yari_off_check(i_this);
    }
    for (s32 i = 0; i < ARRAY_SSIZE(i_this->mParts); i++) {
        if (i_this->mParts[i].m08 >= 0) {
            part_move(i_this, i);
        }
    }
    i_this->m02DD = 0;
    spin_blur_set(i_this);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    return TRUE;
}

/* 0000BCE4-0000BCEC       .text daTn_IsDelete__FP8tn_class */
static BOOL daTn_IsDelete(tn_class*) {
    return TRUE;
}

/* 0000BCEC-0000BE58       .text daTn_Delete__FP8tn_class */
static BOOL daTn_Delete(tn_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    dComIfG_resDeleteDemo(&i_this->mPhaseTkwn, "Tkwn");
    dComIfG_resDeleteDemo(&i_this->mPhaseTn, "Tn");
    if (i_this->m1433 != 0) {
        hio_set = false;
        mDoHIO_deleteChild(l_tnHIO.mNo);
    }
    i_this->m144C[0].remove();
    i_this->m144C[1].remove();
    i_this->m144C[2].remove();
    i_this->mSmokeCb1.remove();
    i_this->mSmokeCb2.remove();
    i_this->mDamageReaction.mParticleCallBack.remove();
#if VERSION > VERSION_DEMO
    if (actor->heap != NULL) {
        i_this->mpBodyMorf->stopZelAnime();
    }
#endif
    if (i_this->mMantPcId != 0xFFFF) {
        fopAc_ac_c* mant_actor = fopAcM_SearchByID(i_this->mMantPcId);
        if (mant_actor != NULL) {
            fopAcM_delete(mant_actor);
        }
    }
    if (actor->health == -128) {
        if (fopAcM_CheckStatus(actor, fopAcStts_BOSS_e)) {
            if (s_check == 0) {
                mDoAud_subBgmStop();
            } else {
                s_check = 0;
            }
        }
    }
#if VERSION > VERSION_DEMO
    enemy_fire_remove(&i_this->mEnemyFire);
#endif
    return TRUE;
}

/* 0000BE58-0000BEBC       .text useArrowHeapInit__FP10fopAc_ac_c */
static BOOL useArrowHeapInit(fopAc_ac_c* a_this) {
    static Vec kosi_cyl_offset[] = {{0.0f, 20.0f, 0.0f}, {0.0f, -20.0f, 0.0f}};
    static Vec asi_cyl_offset[] = {{20.0f, 0.0f, 0.0f}, {-20.0f, 0.0f, 0.0f}};
    static Vec mune_cyl_offset[] = {{30.0f, 0.0f, 0.0f}, {-10.0f, 0.0f, 0.0f}};
    static Vec kata_l_cyl_offset[] = {{40.0f, -5.0f, 0.0f}, {-20.0f, 0.0f, 0.0f}};
    static Vec kata_r_cyl_offset[] = {{40.0f, 5.0f, 0.0f}, {-20.0f, 0.0f, 0.0f}};
    static Vec kubi_cyl_offset[] = {{20.0f, 0.0f, 0.0f}, {-25.0f, 0.0f, 0.0f}};
    static Vec atama_cyl_offset[] = {{40.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
    static Vec mimi_cyl_offset[] = {{20.0f, 0.0f, 3.0f}, {0.0f, 0.0f, 0.0f}};
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ TN_MAIN_JNT_TN_SKLROOT_e,
            /* mRadius     */ 20.0f,
            /* mpOffsets   */ kosi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_ASI_L1_e,
            /* mRadius     */ 10.0f,
            /* mpOffsets   */ asi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_ASI_R1_e,
            /* mRadius     */ 10.0f,
            /* mpOffsets   */ asi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_DELETE_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_KUBI1_e,
            /* mRadius     */ 30.0f,
            /* mpOffsets   */ kubi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_DELETE_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_ATAMA1_e,
            /* mRadius     */ 25.0f,
            /* mpOffsets   */ atama_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_DELETE_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_MIMI_L1_e,
            /* mRadius     */ 19.0f,
            /* mpOffsets   */ mimi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_DELETE_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_MIMI_R1_e,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ mimi_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_MUNE1_e,
            /* mRadius     */ 30.0f,
            /* mpOffsets   */ mune_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_KATA_L1_e,
            /* mRadius     */ 18.0f,
            /* mpOffsets   */ kata_l_cyl_offset,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ TN_MAIN_JNT_J_TN_KATA_R1_e,
            /* mRadius     */ 18.0f,
            /* mpOffsets   */ kata_r_cyl_offset,
        },
    };

    tn_class* i_this = (tn_class*)a_this;
    fopAc_ac_c* actor = &i_this->actor;

    i_this->mpJntHit = JntHit_create(i_this->mpBodyMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (i_this->mpJntHit != NULL) {
        fopAcM_SetJntHit(actor, i_this->mpJntHit);
    } else {
        return FALSE;
    }
    return TRUE;
}

/* 0000BEBC-0000C498       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    static u16 part_bmd[] = {
        0,
        dRes_INDEX_TN_BMD_TN_KABUTO1_e, // Regular Darknut helmet
        dRes_INDEX_TN_BMD_TN_TATE1_e    // Shield
    };
    static u16 part_brk[] = {dRes_INDEX_TN_BRK_TN_YOROI1_e, dRes_INDEX_TN_BRK_TN_KABUTO1_e, dRes_INDEX_TN_BRK_TN_TATE1_e};

    tn_class* i_this = (tn_class*)a_this;
    J3DModelData* modelData;
    J3DModel* model;

    i_this->mpBodyMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BMD_TN_MAIN_e),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BCK_ANIOU1_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x00000000,
        0x11020203
    );
    model = i_this->mpBodyMorf->getModel();
    model->setUserArea((u32)i_this);
    int r3;
    for (u16 i = 0; i <= ARRAY_SSIZE(joint_check) - 1; i++) {
        r3 = joint_check[i];
        if (r3 >= 0) {
            if (r3 == 0x0E || r3 == 0x0F || r3 == 0x10 || r3 == 0x11 || r3 == 0x14) {
                model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_P);
            } else {
                model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            }
        } else if (i == TN_MAIN_JNT_J_TN_MIMI_L1_e || i == TN_MAIN_JNT_J_TN_MIMI_R1_e) {
            model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_mimi);
        }
    }
    i_this->mpShieldMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BMD_TN_MAIN_e),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BCK_ATATE_ON1_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x00000000,
        0x11020203
    );
    model = i_this->mpShieldMorf->getModel();
    model->setUserArea((u32)i_this);
    model->getModelData()->getJointNodePointer(TN_MAIN_JNT_J_TN_MUNE1_e)->setCallBack(nodeCallBack_kata);
    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm == NULL) {
        return FALSE;
    }
    if (!i_this->mpBrkAnm->init(
            i_this->mpBodyMorf->getModel()->getModelData(),
            (J3DAnmTevRegKey*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BRK_TN_MAIN_e),
            true,
            J3DFrameCtrl::EMode_LOOP
        ))
    {
        return FALSE;
    }
    for (s32 i = 0; i < ARRAY_SSIZE(i_this->mParts); i++) {
        if (i == 0) {
            i_this->mpArmorMorf = new mDoExt_McaMorf(
                (J3DModelData*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BMD_TN_YOROI1_e), // Body armor
                NULL,
                NULL,
                (J3DAnmTransformKey*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BCK_YKIHON1_e),
                J3DFrameCtrl::EMode_LOOP,
                1.0f,
                0,
                -1,
                1,
                NULL,
                0x00000000,
                0x11020203
            );
            i_this->mParts[i].mpPartModel = i_this->mpArmorMorf->getModel();
        } else {
            if (i == 1 && (i_this->mEquipmentType & EQUIPMENT_HELMET)) {
                modelData = (J3DModelData*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BMD_TN_KABUTO2_e); // Mighty Darknut helmet
            } else {
                modelData = (J3DModelData*)dComIfG_getObjectRes("Tn", part_bmd[i]);
            }
            i_this->mParts[i].mpPartModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        }
        if (i_this->mParts[i].mpPartModel == NULL) {
            return FALSE;
        }
        if (i < 3) {
            i_this->mParts[i].mpPartBrkAnm = new mDoExt_brkAnm();
            if (i_this->mParts[i].mpPartBrkAnm == 0) {
                return FALSE;
            }
            if (i == 1 && (i_this->mEquipmentType & EQUIPMENT_HELMET)) {
                if (!i_this->mParts[i].mpPartBrkAnm->init(
                        i_this->mParts[i].mpPartModel->getModelData(),
                        (J3DAnmTevRegKey*)dComIfG_getObjectRes("Tn", dRes_INDEX_TN_BRK_TN_KABUTO2_e),
                        true,
                        J3DFrameCtrl::EMode_NONE
                    ))
                {
                    return FALSE;
                }
            } else {
                if (!i_this->mParts[i].mpPartBrkAnm->init(
                        i_this->mParts[i].mpPartModel->getModelData(),
                        (J3DAnmTevRegKey*)dComIfG_getObjectRes("Tn", part_brk[i]),
                        true,
                        J3DFrameCtrl::EMode_NONE
                    ))
                {
                    return FALSE;
                }
            }
        }
    }
    s32 temp_r0;
    if ((u8)useArrowHeapInit(a_this)) {
        temp_r0 = 4;
    } else {
        temp_r0 = 0;
    }
    return temp_r0;
}

/* 0000C4E0-0000CBFC       .text daTn_Create__FP10fopAc_ac_c */
static cPhs_State daTn_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl co_cyl_src = {
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
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 90.0f,
            /* Height */ 125.0f,
        }},
    };
    static dCcD_SrcCyl tg_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
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
            /* Radius */ 45.0f,
            /* Height */ 137.5f,
        }},
    };
    static dCcD_SrcSph head_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_METAL,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 55.0f,
        }},
    };
    static dCcD_SrcSph wepon_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8 | AT_TYPE_SKULL_HAMMER,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
            /* Radius */ 100.0f,
        }},
    };
    static dCcD_SrcSph wepon2_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8 | AT_TYPE_SKULL_HAMMER,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
            /* Radius */ 62.5f,
        }},
    };
    static dCcD_SrcSph defence_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_METAL,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 62.5f,
        }},
    };

    cXyz local_30;

    fopAcM_ct_Retail(a_this, tn_class);
    tn_class* i_this = (tn_class*)a_this;
    fopEn_enemy_c* e_this = (fopEn_enemy_c*)a_this;
    cPhs_State res = dComIfG_resLoad(&i_this->mPhaseTkwn, "Tkwn");
    if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    cPhs_State res2 = dComIfG_resLoad(&i_this->mPhaseTn, "Tn");
#if VERSION == VERSION_DEMO
    if (res2 == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    }
#endif
    if (res2 != cPhs_COMPLEATE_e) {
        return res2;
    }
    fopAcM_ct_Demo(a_this, tn_class);
    i_this->mSmokeCb2.setFollowOff();
    a_this->gbaName = 3;
    if (strcmp(dComIfGp_getStartStageName(), "ITest63") == 0 || strcmp(dComIfGp_getStartStageName(), "GanonJ") == 0) {
        search_sp = 1;
    } else {
        search_sp = 0;
    }
    i_this->mBehaviorType = fopAcM_GetParam(a_this) & 0xF;
    i_this->mArmorColorIndex = (fopAcM_GetParam(a_this) >> 4) & 0xF;
    i_this->mRangeOrFrozenAnim = (fopAcM_GetParam(a_this) >> 8) & 0xFF;
    i_this->mPathIndex = (fopAcM_GetParam(a_this) >> 16) & 0xFF;
    i_this->mEnableSpawnSwitch = (fopAcM_GetParam(a_this) >> 24) & 0xFF;
    i_this->mDisableSpawnOnDeathSwitch = a_this->current.angle.z;
    if (REG0_S(0) != 0 || (i_this->mDisableSpawnOnDeathSwitch != 0 && i_this->mDisableSpawnOnDeathSwitch <= 0x7F)) {
        fopAcM_OnStatus(a_this, fopAcStts_BOSS_e);
        search_sp = 1;
    }
    if (i_this->mEnableSpawnSwitch != 0xFF) {
        i_this->m02C1 = i_this->mEnableSpawnSwitch + 1;
        fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
#if VERSION > VERSION_DEMO
        i_this->m1520 = 10;
#endif
    }
    i_this->mEquipmentType = (a_this->current.angle.x >> 5) & 7;
    a_this->current.angle.x = a_this->current.angle.z = 0;
    if (i_this->mArmorColorIndex > 5) {
        i_this->mArmorColorIndex = 5;
    }
    if (i_this->mEquipmentType > EQUIPMENT_HELMET_SHIELD_AND_CAPE) {
        i_this->mEquipmentType = EQUIPMENT_HELMET_SHIELD_AND_CAPE;
    }
    if (i_this->mEquipmentType < EQUIPMENT_SHIELD) {
        i_this->mRemainingEquipmentPieces = EQUIPMENT_PIECE_BODY_ARMOR | EQUIPMENT_PIECE_HELMET | EQUIPMENT_PIECE_UNKNOWN;
    } else {
        i_this->mRemainingEquipmentPieces = EQUIPMENT_PIECE_BODY_ARMOR | EQUIPMENT_PIECE_HELMET | EQUIPMENT_PIECE_SHIELD | EQUIPMENT_PIECE_UNKNOWN;
    }
    if (i_this->mDisableSpawnOnDeathSwitch == 0xFF) {
        i_this->mDisableSpawnOnDeathSwitch = 0;
    }
    if (i_this->mDisableSpawnOnDeathSwitch != 0 && (dComIfGs_isSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(a_this)))) {
        return cPhs_ERROR_e;
    }
    s_check = 0;
    if (i_this->mBehaviorType == BEHAVIOR_MINIBOSS || i_this->mBehaviorType == BEHAVIOR_MSWORD_CHAMBER_AMBUSH) {
        fopAcM_OnStatus(a_this, fopAcStts_BOSS_e);
#if VERSION > VERSION_DEMO
        search_sp = 1;
#endif
        if (i_this->mBehaviorType == BEHAVIOR_MINIBOSS) {
            i_this->mDamageReaction.mMode = 0;
        } else {
            i_this->mDamageReaction.mMode = 10;
            a_this->current.pos.y += 1000.0f;
            fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
        }
        i_this->mDamageReaction.mAction = ACTION_S_DEMO;
        i_this->mBehaviorType = BEHAVIOR_ROAMS_AROUND;
        i_this->m02C1 = 0;
    } else if (i_this->mBehaviorType == BEHAVIOR_UNK_12) {
        i_this->mDamageReaction.mAction = ACTION_S_DEMO;
        i_this->mBehaviorType = BEHAVIOR_ROAMS_AROUND;
        i_this->mDamageReaction.mMode = 0x14;
    }
    if (i_this->mBehaviorType == BEHAVIOR_GUARDS_AREA) {
        i_this->mDamageReaction.mAction = ACTION_STAND;
    } else if (i_this->mBehaviorType == BEHAVIOR_FROZEN_IN_TIME) {
        i_this->mDamageReaction.mAction = ACTION_D_DOZOU;
        i_this->m02C1 = 0;
    }
    a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Tn", 0);
    if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x29808)) {
        return cPhs_ERROR_e;
    }
    if (hio_set == false) {
        l_tnHIO.mNo = mDoHIO_createChild("タートナック", &l_tnHIO); // Taatonakku
        i_this->m1433 = 1;
        hio_set = true;
    }
    fopAcM_SetMin(a_this, -200.0f, -50.0f, -100.0f);
    fopAcM_SetMax(a_this, 125.0f, 250.0f, 250.0f);
    fopAcM_SetMtx(a_this, i_this->mpBodyMorf->getModel()->getBaseTRMtx());
    e_this->initBt(220.5f, 125.0f);
    i_this->mDamageReaction.m70C = 1;
    i_this->mDamageReaction.mSpawnY = a_this->current.pos.y;
    i_this->mDamageReaction.mMaxFallDistance = 1000.0f;
    i_this->mDamageReaction.mInvincibleTimer = 5;
    a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    if (i_this->mPathIndex != 0xFF) {
        i_this->ppd = dPath_GetRoomPath(i_this->mPathIndex, fopAcM_GetRoomNo(a_this));
        if (i_this->ppd == NULL) {
            return cPhs_ERROR_e;
        }
        i_this->m1424 = i_this->mPathIndex + 1;
        i_this->m1426 = 1;
    }
    i_this->mDamageReaction.mAcch
        .Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mDamageReaction.mAcchCir, fopAcM_GetSpeed_p(a_this));
    i_this->mDamageReaction.mAcchCir.SetWall(50.0f, 50.0f);
    i_this->mDamageReaction.mAcch.ClrRoofNone();
    i_this->mDamageReaction.mAcch.SetRoofCrrHeight(100.0f);
    if (i_this->mEquipmentType & EQUIPMENT_HELMET) {
        a_this->health = 30;
        a_this->max_health = 30;
    } else {
        a_this->health = 15;
        a_this->max_health = 15;
    }
    i_this->mDamageReaction.mStts.Init(0xF0, 0xFF, a_this);
    i_this->mCoCyl.Set(co_cyl_src);
    i_this->mCoCyl.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mTgCyl.Set(tg_cyl_src);
    i_this->mTgCyl.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mHeadSph.Set(head_sph_src);
    i_this->mHeadSph.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mWeponSph.Set(wepon_sph_src);
    i_this->mWeponSph.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mWepon2Sph.Set(wepon2_sph_src);
    i_this->mWepon2Sph.SetStts(&i_this->mDamageReaction.mStts);
    i_this->mDefenceSph.Set(defence_sph_src);
    i_this->mDefenceSph.SetStts(&i_this->mDamageReaction.mStts);
    i_this->m02DC = 3;
    local_30.set(a_this->current.pos.x, a_this->current.pos.y + REG0_F(12), a_this->current.pos.z);
    i_this->mBokoPcId = fopAcM_create(fpcNm_BOKO_e, daBoko_c::Type_DARKNUT_SWORD_e, &local_30, fopAcM_GetRoomNo(a_this));
    i_this->m140C = 1;
    i_this->m0C34 = 1;
    if (i_this->mEquipmentType < EQUIPMENT_SHIELD_AND_CAPE) {
        i_this->mMantPcId = 0xFFFF;
    } else {
        i_this->mMantPcId = fopAcM_create(fpcNm_MANT_e, mant_class::Type_DARKNUT_e, &a_this->current.pos, fopAcM_GetRoomNo(a_this));
    }
    i_this->mEnemyIce.mpActor = a_this;
    i_this->mEnemyIce.mWallRadius = REG0_F(6) + 70.0f;
    i_this->mEnemyIce.mCylHeight = REG0_F(7) + 200.0f;
    i_this->mEnemyIce.mParticleScale = 1.5f;
    i_this->mEnemyIce.mDeathSwitch = i_this->mDisableSpawnOnDeathSwitch;
    i_this->mEnemyFire.mpMcaMorf = i_this->mpBodyMorf;
    i_this->mEnemyFire.mpActor = a_this;

    static u8 fire_j[ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs)] = {
        TN_MAIN_JNT_J_TN_ATAMA1_e,
        TN_MAIN_JNT_J_TN_MUNE1_e,
        TN_MAIN_JNT_J_TN_UDE_R1_e,
        TN_MAIN_JNT_J_TN_UDE_R2_e,
        TN_MAIN_JNT_J_TN_UDE_L1_e,
        TN_MAIN_JNT_J_TN_UDE_L2_e,
        TN_MAIN_JNT_J_TN_ASI_R1_e,
        TN_MAIN_JNT_J_TN_ASI_R2_e,
        TN_MAIN_JNT_J_TN_ASI_L1_e,
        TN_MAIN_JNT_J_TN_ASI_L2_e
    };
    static f32 fire_sc[ARRAY_SIZE(i_this->mEnemyFire.mParticleScale)] = {
        2.3f, // TN_MAIN_JNT_J_TN_ATAMA1_e
        2.3f, // TN_MAIN_JNT_J_TN_MUNE1_e
        1.4f, // TN_MAIN_JNT_J_TN_UDE_R1_e
        1.2f, // TN_MAIN_JNT_J_TN_UDE_R2_e
        1.4f, // TN_MAIN_JNT_J_TN_UDE_L1_e
        1.2f, // TN_MAIN_JNT_J_TN_UDE_L2_e
        1.4f, // TN_MAIN_JNT_J_TN_ASI_R1_e
        1.2f, // TN_MAIN_JNT_J_TN_ASI_R2_e
        1.4f, // TN_MAIN_JNT_J_TN_ASI_L1_e
        1.2f  // TN_MAIN_JNT_J_TN_ASI_L2_e
    };

    for (int i = 0; i < ARRAY_SIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
        i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
        i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
    }
    i_this->m151C = 1.0f;
    a_this->stealItemLeft = 5;
    for (s32 i = 0; i < ARRAY_SSIZE(i_this->mParts); i++) {
        daTn_Execute(i_this);
    }
    i_this->m151C = 10.0f;
    if (i_this->mDamageReaction.mAction == 0x17) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::COLORS_IN_HYRULE)) {
            fopAcM_OffStatus(a_this, fopAcStts_UNK4000_e);
        } else {
            fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
        }
    }
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daTn_Method = {
    (process_method_func)daTn_Create,
    (process_method_func)daTn_Delete,
    (process_method_func)daTn_Execute,
    (process_method_func)daTn_IsDelete,
    (process_method_func)daTn_Draw,
};

actor_process_profile_definition g_profile_TN = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_TN_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(tn_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_TN_e,
    /* Actor SubMtd */ &l_daTn_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
