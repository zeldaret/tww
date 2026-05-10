/**
 * d_a_bpw.cpp
 * Boss - Jalhalla
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bpw.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_pw.h"
#include "d/d_lib.h"
#include "d/d_snap.h"
#include "d/res/res_bpw.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"
#if VERSION == VERSION_DEMO
#include "m_Do/m_Do_controller_pad.h"
#else
#include "m_Do/m_Do_graphic.h"
#endif

enum Actor_Type {
    ACTOR_TYPE_BODY = 0,
    ACTOR_TYPE_KANTERA = 1,
    ACTOR_TYPE_DAMAGE_BALL = 2,
    ACTOR_TYPE_TORITUKI = 3,
};

enum Damage_Action {
    DAMAGE_ACTION_LINE = 0,
    DAMAGE_ACTION_DAMAGE_BALL = 1,
};

enum Action {
    ACTION_MOVE_DOUSA = 0,
    ACTION_ATTACK_KOUGEKI = 1,
    ACTION_BODY_DOWN_KARADA_TAORE = 2,
    ACTION_DAMAGE = 3,
    ACTION_SEPARATION_BUNRI_DOUSA = 4,
    ACTION_START_DEMO = 20,
};

enum Action_State {
    ACTION_STATE_DAMAGE_CARRIED = 0x54,
    ACTION_STATE_DAMAGE_THROWN = 0x55,
    ACTION_STATE_DAMAGE_HIT = 0x65,
    ACTION_STATE_SEPARATE_BUNRI_DOUSA_INIT = 0x6E,
    ACTION_STATE_SEPARATE_BUNRI_DOUSA_EXECUTE = 0x6F,
    ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_INIT = 0x72,
    ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_GATHER = 0x73,
    ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_GROW = 0x74,
    ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_FINISH = 0x75,
};

static bool GOUEN_FIRE_HIT;
static fopAc_ac_c* check_info[100];
static s32 get_check_count;

/* 00000078-00000258       .text body_nodeCallBack__FP7J3DNodei */
static BOOL body_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        cXyz local_28;
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bpw_class* i_this = (bpw_class*)model->getUserArea();
        if (i_this != NULL) {
            if ((((jntNo == 0) || (jntNo == 2)) || (jntNo - 0x1d <= (u32)1)) || (jntNo == 0x25)) {
                MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            }
            if (jntNo == 0) {
                local_28.x = 0.0f;
                local_28.y = i_this->m4A0;
                local_28.z = 0.0f;
                MtxPosition(&local_28, &i_this->m358);
                local_28.x = 0.0f;
                local_28.y = -50.0f;
                local_28.z = 0.0f;
                MtxPosition(&local_28, &i_this->m370);
            }
            if (jntNo == 2) {
                local_28.x = 0.0f;
                local_28.y = 0.0f;
                local_28.z = 0.0f;
                MtxPosition(&local_28, &i_this->m394);
            }
            if (jntNo == 0x1d) {
                local_28.x = 0.0f;
                local_28.y = 0.0f;
                local_28.z = 0.0f;
                MtxPosition(&local_28, &i_this->m3B8);
            }
            if (jntNo == 0x1e) {
                local_28.x = 0.0f;
                local_28.y = 0.0f;
                local_28.z = 0.0f;
                MtxPosition(&local_28, &i_this->mChildActorPos);
            }
            if (jntNo == 0x25) {
                local_28.x = 0.0f;
                local_28.y = 0.0f;
                local_28.z = 0.0f;
                MtxPosition(&local_28, &i_this->m3C4);
            }
            if (((jntNo == 0) || (jntNo == 2)) || (jntNo - 0x1d <= (u32)1 || (jntNo == 0x25))) {
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 00000294-000003C4       .text kantera_nodeCallBack__FP7J3DNodei */
static BOOL kantera_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        cXyz local_28;
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bpw_class* i_this = (bpw_class*)model->getUserArea();
        if (i_this != NULL) {
            if ((jntNo == 0) || (jntNo == 1)) {
                MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            }
            if (jntNo == 1) {
                cMtx_YrotM(*calc_mtx, i_this->mKanteraDousaRot.y);
                cMtx_XrotM(*calc_mtx, i_this->mKanteraDousaRot.x);
                cMtx_ZrotM(*calc_mtx, i_this->mKanteraDousaRot.z);
                local_28.x = 0.0f;
                local_28.y = -100.0f;
                local_28.z = 0.0f;
                MtxPosition(&local_28, &i_this->m358);
            }
            if ((jntNo == 0) || (jntNo == 1)) {
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

const u32 unused_4324[] = {
    0xFFFFFFFF,
    0xFF0000FF,
    0xFF00FFFF,
};

/* 000003C4-000004F0       .text draw_SUB__FP9bpw_class */
void draw_SUB(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos.x + i_this->m3AC.x, actor->current.pos.y + i_this->m3AC.y, actor->current.pos.z + i_this->m3AC.z);
    mDoMtx_stack_c::YrotM(i_this->m3D6.y);
    mDoMtx_stack_c::XrotM(i_this->m3D6.x);
    mDoMtx_stack_c::YrotM(-i_this->m3D6.y);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::now);
    if (i_this->mType != ACTOR_TYPE_DAMAGE_BALL) {
        if (i_this->mType != ACTOR_TYPE_TORITUKI) {
            i_this->mpMorf->calc();
        }
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    }
}

/* 000004F0-000005D8       .text kantera_draw_SUB__FP9bpw_class */
void kantera_draw_SUB(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
    cMtx_ZrotM(*calc_mtx, actor->shape_angle.z);
    MtxTrans(i_this->m3AC.x, i_this->m3AC.y, i_this->m3AC.z, true);
    model->setBaseTRMtx(*calc_mtx);
    i_this->mpMorf->calc();
    dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
}

/* 000005D8-00000998       .text body_draw__FP9bpw_class */
void body_draw(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28;
    cXyz local_34;

    J3DModel* model = i_this->mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = i_this->m47E;
    }
    if (i_this->m3E0 == 0) {
        dComIfGd_setListMaskOff();
    }
    dSnap_RegistFig(DSNAP_TYPE_UNKCE, actor, 1.0f, 1.0f, 1.0f);
    if (i_this->m3E0 != 0) {
        i_this->mpLightFreezeBrkAnm->entry(model->getModelData());
    } else if (i_this->m3E1 != 0) {
        i_this->mpLightStunBrkAnm->entry(model->getModelData());
    } else if (i_this->m3E2 == 2) {
        i_this->mpCurseStartBrkAnm->entry(model->getModelData());
    } else if (i_this->m3E2 == 1) {
        i_this->mpCurseEndBrkAnm->entry(model->getModelData());
    } else {
        i_this->mpDefaultBrkAnm->entry(model->getModelData());
    }
    i_this->mpMorf->entryDL();
    dComIfGd_setList();
    if (i_this->m3E0 == 0) {
        i_this->mInvisibleModel.entryMaskOff();
    } else {
        i_this->mInvisibleModel.entry();
    }
    if (i_this->m3E0 != 0) {
        i_this->mpLightFreezeBrkAnm->remove(model->getModelData());
    } else if (i_this->m3E1 != 0) {
        i_this->mpLightStunBrkAnm->remove(model->getModelData());
    } else if (i_this->m3E2 == 2) {
        i_this->mpCurseStartBrkAnm->remove(model->getModelData());
    } else if (i_this->m3E2 == 1) {
        i_this->mpCurseEndBrkAnm->remove(model->getModelData());
    } else {
        i_this->mpDefaultBrkAnm->remove(model->getModelData());
    }
    if ((i_this->m47E == 0) || (fopAcM_checkCarryNow(actor))) {
        return;
    }
    dSnap_RegistFig(DSNAP_TYPE_UNKCB, actor, 1.0f, 1.0f, 1.0f);
    local_28.set(actor->current.pos.x, actor->current.pos.y + 400.0f + REG8_F(18), actor->current.pos.z);
    i_this->mShadowId = dComIfGd_setShadow(
        i_this->mShadowId,
        1,
        i_this->mpMorf->getModel(),
        &local_28,
        REG8_F(19) + 1300.0f,
        200.0f,
        actor->current.pos.y,
        i_this->mAcch.GetGroundH(),
        i_this->mAcch.m_gnd,
        &actor->tevStr,
        0,
        1.0f,
        &dDlst_shadowControl_c::mSimpleTexObj
    );
    if ((i_this->mShadowId != 0) && (i_this->mAttWaitTimer != 4)) {
        bpw_class* pfVar3 = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
        if (pfVar3 != NULL) {
            dComIfGd_addRealShadow(i_this->mShadowId, pfVar3->mpMorf->getModel());
        }
    }
    if (REG8_S(1) != 0) {
        local_34 = i_this->mBodyPos;
        // optimized out?
        for (s32 i = 3; i != 0; i--) {
        }
        local_34.y += 100.0f;
        local_34 = actor->current.pos;
        local_34.y += 100.0f;
    }
}

/* 00000998-00000B64       .text kantera_draw__FP9bpw_class */
void kantera_draw(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_20;
    cXyz local_2c;
    cXyz local_38;

    J3DModel* model = i_this->mpMorf->getModel();
    local_20.setall(0.0f);
    if (i_this->m3E7 == 0) {
        i_this->mpLanternGlowBrkAnm->entry(model->getModelData());
    }
    i_this->mpMorf->entryDL();
    if (i_this->m3E7 == 0) {
        i_this->mpLanternGlowBrkAnm->remove(model->getModelData());
    }
    if (i_this->m3E7 == 0) {
        cMtx_copy(i_this->mpMorf->getModel()->getBaseTRMtx(), *calc_mtx);
        MtxPosition(&local_20, &local_2c);
        MtxTrans(local_2c.x, local_2c.y, local_2c.z, false);
        MtxScale(3.0f, 3.0f, 3.0f, true);
        cMtx_copy(*calc_mtx, i_this->m2D4);
        GXColor color;
        color.r = 0xeb;
        color.g = 0x7d;
        color.b = 0;
        color.a = 0;
        dComIfGd_setAlphaModelColor(color);
        dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_THREE_SPHERES, i_this->m2D4, i_this->m47E);
    }
    if (i_this->mActionState >= 2) {
        local_38.set(actor->current.pos.x, actor->current.pos.y + 400.0f + REG12_F(18), actor->current.pos.z);
        i_this->mShadowId = dComIfGd_setShadow(
            i_this->mShadowId,
            1,
            i_this->mpMorf->getModel(),
            &local_38,
            REG12_F(19) + 1300.0f,
            200.0f,
            actor->current.pos.y,
            i_this->mAcch.GetGroundH(),
            i_this->mAcch.m_gnd,
            &actor->tevStr
        );
    }
}

/* 00000B64-00000C20       .text damage_ball_draw__FP9bpw_class */
static void damage_ball_draw(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    MtxScale(0.8f, 0.8f, 0.8f, true);
    cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
    cMtx_copy(*calc_mtx, i_this->m2D4);
    GXColor color;
    color.r = 0xeb;
    color.g = 0x50;
    color.b = 0;
    color.a = 0;
    dComIfGd_setAlphaModelColor(color);
    dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_TWO_SPHERES, i_this->m2D4, i_this->m47E);
}

const u32 unused_4576[] = {
    0xFFFFFFFF,
};

/* 00000C20-00000C24       .text line_draw__FP9bpw_class */
void line_draw(bpw_class*) {
    /* Empty function */
}

/* 00000C24-00000CF0       .text torituki_draw__FP9bpw_class */
void torituki_draw(bpw_class* i_this) {
    J3DModelData* modelData = i_this->mpMorf->getModel()->getModelData();
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        modelData->getMaterialNodePointer(i)->getTevKColor(3)->mColor.a = i_this->m47E;
    }
    dComIfGd_setListMaskOff();
    i_this->mpMorf->updateDL();
    dComIfGd_setList();
    i_this->mInvisibleModel.entryMaskOff();
}

/* 00000CF0-00000DF4       .text daBPW_Draw__FP9bpw_class */
static BOOL daBPW_Draw(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* model = i_this->mpMorf->getModel();
#if VERSION > VERSION_DEMO
    if (i_this->m408 > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->m408);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->m408 == 1) {
        i_this->m408 = 0;
        mDoGph_gInf_c::offBlure();
    }
#endif
    if (i_this->mType != ACTOR_TYPE_DAMAGE_BALL) {
        dKy_getEnvlight().setLightTevColorType(model, &actor->tevStr);
    }
    switch (i_this->mType) {
    case ACTOR_TYPE_BODY:
        body_draw(i_this);
        break;
    case ACTOR_TYPE_KANTERA:
        kantera_draw(i_this);
        break;
    case ACTOR_TYPE_DAMAGE_BALL:
        if (i_this->mUnknownParam2 == DAMAGE_ACTION_LINE) {
            line_draw(i_this);
        }
        if (i_this->mUnknownParam2 == DAMAGE_ACTION_DAMAGE_BALL) {
            damage_ball_draw(i_this);
        }
        break;
    case ACTOR_TYPE_TORITUKI:
        torituki_draw(i_this);
        break;
    }
    return TRUE;
}

/* 00000DF4-00000F20       .text anm_init__FP9bpw_classifUcfi */
void anm_init(bpw_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    i_this->m3F8 = bckFileIdx;
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("BPW", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("BPW", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("BPW", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000F20-000015CC       .text body_atari_check__FP9bpw_class */
BOOL body_atari_check(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    bool bVar2;
    cXyz local_4c;
    cXyz local_58;
    CcAtInfo atInfo;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mHitType = 0;
    if (i_this->m47E == 0) {
        return 0;
    }
    i_this->mStts.Move();
    if (!i_this->mBodyCoSph.ChkTgHit()) {
        return 0;
    }
    cCcD_Obj* hitObj = i_this->mBodyCoSph.GetTgHitObj();
    if (hitObj == NULL) {
        return 0;
    }
    bVar2 = false;
    atInfo.mpObj = i_this->mBodyCoSph.GetTgHitObj();
    i_this->mHitType = 1;
    if (i_this->m3E0 == 0) {
        switch (hitObj->GetAtType()) {
        case AT_TYPE_LIGHT:
            i_this->mHitType = 10;
            if (i_this->mBodyAction != ACTION_DAMAGE) {
                i_this->mBodyAction = ACTION_DAMAGE;
                i_this->mActionState = 0x50;
            }
            break;
        case AT_TYPE_LIGHT_ARROW:
            i_this->mHitType = 0xb;
            if (i_this->mBodyAction != ACTION_DAMAGE) {
                i_this->mBodyAction = ACTION_DAMAGE;
                i_this->mActionState = 0x50;
            }
            break;
        }
        return 1;
    }
    if (i_this->mActionState != 0x53) {
        return 0;
    }
    switch (hitObj->GetAtType()) {
    case AT_TYPE_DARKNUT_SWORD:
    case AT_TYPE_MOBLIN_SPEAR:
    case AT_TYPE_UNK800:
    case AT_TYPE_MACHETE:
    case AT_TYPE_SWORD:
        fopAcM_seStart(actor, JA_SE_LK_SW_HIT_S, 0x44);
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
            i_this->mHitType = 2;
            anm_init(i_this, BPW_BCK_BOYON_L1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        } else {
            anm_init(i_this, BPW_BCK_BOYON_S1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        break;
    case AT_TYPE_HOOKSHOT:
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x44);
        i_this->mHitType = 0xc;
        anm_init(i_this, BPW_BCK_BOYON_S1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        break;
    case AT_TYPE_WIND:
        bVar2 = true;
        i_this->mHitType = 4;
        break;
    case AT_TYPE_LIGHT:
        bVar2 = true;
        i_this->mHitType = 10;
        break;
    case AT_TYPE_BOOMERANG:
        i_this->mHitType = 5;
        // fallthrough
    case AT_TYPE_STALFOS_MACE:
    case AT_TYPE_BOKO_STICK:
        fopAcM_seStart(actor, JA_SE_LK_W_WEP_HIT, 0x44);
        anm_init(i_this, BPW_BCK_BOYON_S1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        break;
    case AT_TYPE_SKULL_HAMMER:
        fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x44);
        i_this->mHitType = 8;
        if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
            i_this->mHitType = 9;
        }
        anm_init(i_this, BPW_BCK_BOYON_L1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        break;
    case AT_TYPE_BOMB:
        i_this->mHitType = 7;
        anm_init(i_this, BPW_BCK_BOYON_L1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        break;
    case AT_TYPE_ICE_ARROW:
        i_this->mHitType = 6;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x44);
        anm_init(i_this, BPW_BCK_BOYON_S1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        break;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mHitType = 11;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x44);
        anm_init(i_this, BPW_BCK_BOYON_S1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        break;
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_FIRE:
    case AT_TYPE_NORMAL_ARROW:
        i_this->mHitType = 6;
        // fallthrough
    default:
        i_this->mHitType = 0;
        fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x44);
        anm_init(i_this, BPW_BCK_BOYON_S1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        break;
    }
    if (!bVar2) {
        local_4c = *i_this->mBodyCoSph.GetTgHitPosP();
        local_58.setall(2.0f);
        dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, &local_4c, &player->shape_angle, &local_58);
    }
    return FALSE;
}

/* 000015CC-00001658       .text BG_check__FP9bpw_class */
void BG_check(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mAcchCir.SetWall(i_this->m498, i_this->m49C);
    actor->current.pos.y = actor->current.pos.y - i_this->m48C;
    actor->old.pos.y = actor->old.pos.y - i_this->m48C;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    actor->current.pos.y = actor->current.pos.y + i_this->m48C;
    actor->old.pos.y = actor->old.pos.y + i_this->m48C;
}

/* 00001658-00001798       .text wall_HIT_check__FP9bpw_class */
s32 wall_HIT_check(bpw_class* i_this) {
    cXyz acStack_24;
    cXyz cStack_30;
    cXyz cStack_3c;
    cXyz local_48;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    local_48.x = REG21_F(4) + 6.0f;
    local_48.y = local_48.x;
    local_48.z = local_48.x;
    if (i_this->mAcchCir.ChkWallHit()) {
        dComIfG_Bgsp()->GetTriPnt(i_this->mAcchCir, &acStack_24, &cStack_30, &cStack_3c);
        if (dComIfG_Bgsp()->GetAttributeCode(i_this->mAcchCir) == dBgS_Attr_DAMAGE_e) {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &acStack_24, &player->shape_angle, &local_48);
#if VERSION > VERSION_DEMO
            i_this->m408 = 0xb5;
#endif
            return 2;
        } else {
            dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHIT, &acStack_24, &player->shape_angle, &local_48);
            return 1;
        }
    } else {
        return 0;
    }
}

/* 00001798-00001894       .text alpha_anime__FP9bpw_class */
void alpha_anime(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m3E0 == 0) {
        if (dComIfGp_getDetect().chk_light(&actor->current.pos)) {
            cLib_addCalcAngleS2(&i_this->m47E, 0, 1, 0x14);
            i_this->m480 = 0;
            i_this->m478 = 0;
        } else {
            i_this->m478 += 0x400;
            cLib_addCalcAngleS2(&i_this->m480, 0x96, 1, 10);
            i_this->m47E = i_this->m480 + cM_ssin(i_this->m478) * 30.0f;
        }
    }
}

/* 00001894-000018EC       .text fuwafuwa_calc__FP9bpw_class */
void fuwafuwa_calc(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m47C += 700;
    actor->current.pos.y = i_this->mAcch.GetGroundH() + 30.0f;
    actor->current.pos.y += cM_ssin(i_this->m47C) * 30.0f;
}

/* 000018EC-00001A50       .text kankyou_hendou__FP9bpw_class */
void kankyou_hendou(bpw_class* i_this) {
    /* Nonmatching - missing "b" instruction for case 0; equivalent */
    f32 fVar1;
    u8 bVar2;

    fVar1 = 0.0f;
    bVar2 = 1;

    switch (i_this->mKankyouHendouState) {
    case 0:
        break;
    case 1:
        fVar1 = 1.0f;
        if (i_this->mSomeCountdownTimers[5] == 1) {
            i_this->mKankyouHendouState = 0;
        }
        break;
    case 2:
        fVar1 = 1.0f;
        bVar2 = 2;
        if (i_this->mSomeCountdownTimers[5] == 1) {
            i_this->mKankyouHendouState = 4;
        }
        break;
    case 3:
        fVar1 = 1.0f;
        bVar2 = 3;
        if (i_this->mSomeCountdownTimers[5] == 1) {
            i_this->mKankyouHendouState = 5;
        }
        break;
    case 4:
        bVar2 = 2;
        break;
    case 5:
        bVar2 = 3;
        break;
    case 6:
        fVar1 = 1.0f;
        bVar2 = 0;
        break;
    }

    cLib_addCalc2(&i_this->m3EC, fVar1, 1.0f, 0.1f);

    if (i_this->mKankyouHendouState < 6) {
        fVar1 = i_this->m3EC;
        if (fVar1 > 0.5f) {
            dKy_custom_colset(4, bVar2, fVar1);
        } else {
            dKy_custom_colset(bVar2, 4, 1.0f - fVar1);
        }
    } else {
        fVar1 = i_this->m3EC;
        if (fVar1 > 0.5f) {
            dKy_custom_colset(3, bVar2, fVar1);
        } else {
            dKy_custom_colset(bVar2, 3, 1.0f - fVar1);
        }
    }
}

/* 00001A50-00001CBC       .text noroi_check__FP9bpw_class */
void noroi_check(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daPy_py_c* player2 = (daPy_py_c*)player;
    fopAc_ac_c* pdVar4;

    if ((!player2->checkConfuse()) && (i_this->m47E != 0)) {
        if ((i_this->mAttWaitTimer != 1) && (i_this->mAttWaitTimer != 2 && (i_this->mAttWaitTimer != 0))) {
            return;
        }
        if ((((i_this->m3F6 != 0) && (i_this->m3E6 == 0)) && (i_this->mBodyAction != ACTION_BODY_DOWN_KARADA_TAORE)) &&
            ((i_this->mActionState != 10 && (i_this->mActionState != 0xb)) && (i_this->mActionState != 0xc && (i_this->mActionState != 0xd))))
        {
            if (((i_this->m3F8 == 0x2a) || (i_this->m3F8 == 0x1d)) || (i_this->m3F8 == 0x1c || (i_this->m3F8 == 0x2b))) {
                f32 f31 = 530.0f;
                if (fopAcM_searchPlayerDistance(actor) < f31) {
                    i_this->mBodyAction = ACTION_BODY_DOWN_KARADA_TAORE;
                    i_this->mActionState = 0x4d;
                }
            }
        } else if (
            (((i_this->mActionState == 5) || (i_this->mActionState == 6)) || (i_this->mBodyAction == ACTION_BODY_DOWN_KARADA_TAORE)) &&
            (i_this->mSomeCountdownTimers[3] == 0 && (i_this->mBodyAtSph.ChkAtHit()))
        )
        {
            pdVar4 = i_this->mBodyAtSph.GetAtHitAc();
            if ((pdVar4 != NULL) && (pdVar4 == player)) {
                actor->speedF = 0.0f;
                i_this->m490 = 0.0f;
                i_this->mBodyCoSph.OffTgSetBit();
                i_this->mBodyCoSph.ClrTgHit();
                player2->onConfuse();
                i_this->mSomeCountdownTimers[3] = DEMO_SELECT(REG11_F(17) + 0x14, 0x14);
                s32 r31 = ACTOR_TYPE_BODY;
                csXyz local_28 = actor->shape_angle;
                camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
                i_this->mFire1DousaPos = player2->getHeadTopPos();
                dComIfGp_particle_set(dPa_name::ID_IT_JN_PIYOHIT00, &i_this->mFire1DousaPos);
                r31 |= ACTOR_TYPE_TORITUKI;
                local_28.y = fopCamM_GetAngleY(camera);
                fopAcM_create(PROC_BPW, r31, &i_this->mFire1DousaPos, fopAcM_GetRoomNo(actor), &local_28);
            }
        }
    }
}

/* 00001CBC-00001DA0       .text fire_and_emitter_clear__FP9bpw_class */
void fire_and_emitter_clear(bpw_class* i_this) {
    bpw_class* pfVar1;

    if (i_this->m400 != fpcM_ERROR_PROCESS_ID_e) {
        pfVar1 = (bpw_class*)fopAcM_SearchByID(i_this->m400);
        if ((pfVar1 != NULL) && (pfVar1->mUnknownParam2 == DAMAGE_ACTION_LINE)) {
            fopAcM_delete(&pfVar1->actor);
            i_this->m400 = fpcM_ERROR_PROCESS_ID_e;
        }
    }
#if VERSION == VERSION_DEMO
    if (i_this->m534_demo) {
        i_this->m534_demo->becomeInvalidEmitter();
        i_this->mFire1Dousa_Pa_followEcallBack.remove();
        i_this->m534_demo = NULL;
    }
    if (i_this->m538_demo) {
        i_this->m538_demo->becomeInvalidEmitter();
        i_this->mFire1Dousa_Pa_followEcallBack2.remove();
        i_this->m538_demo = NULL;
    }
    if (i_this->m53C_demo) {
        i_this->m53C_demo->becomeInvalidEmitter();
        i_this->m590.remove();
        i_this->m53C_demo = NULL;
    }
    if (i_this->m508_demo) {
        i_this->m508_demo->becomeInvalidEmitter();
        i_this->m508_demo = NULL;
    }
    if (i_this->m50C_demo) {
        i_this->m50C_demo->becomeInvalidEmitter();
        i_this->m50C_demo = NULL;
    }
    if (i_this->m510_demo) {
        i_this->m510_demo->becomeInvalidEmitter();
        i_this->m510_demo = NULL;
        i_this->m50C.remove();
    }
#else
    i_this->mFire1Dousa_Pa_followEcallBack.remove();
    i_this->mFire1Dousa_Pa_followEcallBack2.remove();
    i_this->m590.remove();
    i_this->m540.remove();
    i_this->m52C.remove();
    i_this->m50C.remove();
#endif
}

/* 00001DA0-00001F40       .text noroi_brk_check__FP9bpw_classUc */
void noroi_brk_check(bpw_class* i_this, u8 param_2) {
    J3DAnmTevRegKey* pBrk;

    J3DModel* model = i_this->mpMorf->getModel();
    switch (param_2) {
    case 0:
        if (i_this->m3E2 != 2) {
            i_this->m3E2 = 2;
            pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_NOROI_S1);
            i_this->mpCurseStartBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
        }
        break;
    case 1:
        if (i_this->m3E2 == 2) {
            i_this->m3E2 = 1;
            pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_NOROI_E1);
            i_this->mpCurseEndBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
        }
        break;
    case 2:
        i_this->m3E2 = 0;
        pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_DEFAULT);
        i_this->mpDefaultBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
        break;
    }
}

/* 00001F40-00001F90       .text next_att_wait_check__FP9bpw_class */
BOOL next_att_wait_check(bpw_class* i_this) {
    if (i_this->mAttWaitTimer != 1) {
        if ((i_this->mAttWaitTimer != 2) && (i_this->mAttWaitTimer != 0)) {
            i_this->mBodyAction = ACTION_MOVE_DOUSA;
            i_this->mActionState = 10;
            return TRUE;
        }
    }
    i_this->mAttWaitTimer = 1;
    i_this->mBodyAction = ACTION_MOVE_DOUSA;
    i_this->mActionState = 0;
    return FALSE;
}

/* 00001F90-00002114       .text next_status_clear__FP9bpw_classUc */
void next_status_clear(bpw_class* i_this, u8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;

    actor->gravity = 0.0f;
    actor->speed.setall(0.0f);
    actor->speedF = 0.0f;
    i_this->m490 = 0.0f;
    i_this->m3E6 = 0;
    i_this->m3E5 = 0;
    i_this->m4A8 = REG8_F(16) + 220.0f;
    i_this->m3AC.y = 340.0f;
    noroi_brk_check(i_this, 1);
    actor->shape_angle.x = 0;
    i_this->m4A4 = 300.0f;
    if (param_2 == 0) {
        i_this->m478 = 0;
        i_this->m480 = 0;
        i_this->m3E0 = 0;
    }
    if (i_this->m3E1 != 0) {
        J3DModel* model = i_this->mpMorf->getModel();
        i_this->m3E1 = 0;
        J3DAnmTevRegKey* pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_DEFAULT);
        i_this->mpDefaultBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
    }
    if (i_this->mAttWaitTimer == 0) {
        i_this->mAttWaitTimer = 1;
    }
    i_this->m47A = 0x500;
    i_this->mBodyCoSph.OffTgShield();
    i_this->mBodyAtSph.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
    i_this->mBodyAtSph.OnAtHitBit();
    i_this->mBodyCoSph.OnTgSetBit();
    i_this->mBodyCoSph.ClrCoSet();
    i_this->m498 = 350.0f;
    i_this->m49C = 400.0f;
}

/* 00002114-0000242C       .text light_on_off__FP9bpw_class */
void light_on_off(bpw_class* i_this) {
    static s16 light_on_dt[] = {0x0000, 0x0001, 0x0002, 0x0001, 0x0002, 0x0000, 0x0002, 0x0000, 0x0001};
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar1;
    int iVar2;

    s32 iVar3 = cM_rndF(2.99f);
    sVar1 = i_this->m3F6;
    if (sVar1 != 0) {
        u8 switchNo = i_this->mLightState;
        if (sVar1 == 3) {
            dComIfGs_onSwitch(switchNo, fopAcM_GetRoomNo(actor));
            s32 r28 = switchNo;
            r28++;
            dComIfGs_onSwitch(r28, fopAcM_GetRoomNo(actor));
            r28++;
            dComIfGs_onSwitch(r28, fopAcM_GetRoomNo(actor));
        } else if (sVar1 == 4) {
            dComIfGs_offSwitch(switchNo, fopAcM_GetRoomNo(actor));
            s32 r28 = switchNo;
            r28++;
            dComIfGs_offSwitch(r28, fopAcM_GetRoomNo(actor));
            r28++;
            dComIfGs_offSwitch(r28, fopAcM_GetRoomNo(actor));
        } else if (i_this->mSomeCountdownTimers[7] == 0) {
            iVar3 *= 3.0f;
            iVar2 = i_this->mLightState + light_on_dt[iVar3];
            if (sVar1 == 2) {
                dComIfGs_onSwitch(iVar2, fopAcM_GetRoomNo(actor));
            } else {
                dComIfGs_offSwitch(iVar2, fopAcM_GetRoomNo(actor));
            }
            if (REG0_S(1) != 0) {
                dComIfGs_offSwitch(iVar2, fopAcM_GetRoomNo(actor));
            }
            iVar3++;
            iVar2 = i_this->mLightState + light_on_dt[iVar3];
            if (i_this->m3F6 == 2) {
                dComIfGs_onSwitch(iVar2, fopAcM_GetRoomNo(actor));
            } else {
                dComIfGs_offSwitch(iVar2, fopAcM_GetRoomNo(actor));
            }
            if (REG0_S(1) != 0) {
                dComIfGs_offSwitch(iVar2, fopAcM_GetRoomNo(actor));
            }
            iVar3++;
            iVar3 = i_this->mLightState + light_on_dt[iVar3];
            if (i_this->m3F6 == 2) {
                dComIfGs_offSwitch(iVar3, fopAcM_GetRoomNo(actor));
            } else {
                dComIfGs_onSwitch(iVar3, fopAcM_GetRoomNo(actor));
            }
            if (REG0_S(1) != 0) {
                dComIfGs_offSwitch(iVar3, fopAcM_GetRoomNo(actor));
            }
            i_this->mSomeCountdownTimers[7] = REG0_S(4) + DEMO_SELECT(180, 240);
            i_this->mSomeCountdownTimers[7] += (int)cM_rndF((s32)(REG0_S(5) + DEMO_SELECT(90, 120)));
        }
    }
}

/* 0000242C-000024B0       .text skull_search_sub__FPvPv */
void* skull_search_sub(void* param_1, void* param_2) {
    UNUSED(param_2);
    fopAc_ac_c* actor = (fopAc_ac_c*)param_1;

    if ((get_check_count < 100) && (fopAcM_IsActor(actor))) {
        if ((fopAcM_GetName(actor) == PROC_BL) && (actor->health > 0)) {
            check_info[get_check_count] = actor;
            get_check_count++;
        }
    }
    return FALSE;
}

/* 000024B0-000026F8       .text search_get_skull__FP9bpw_classUc */
void search_get_skull(bpw_class* i_this, u8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* actor2;

    get_check_count = 0;
    fpcM_Search(skull_search_sub, i_this);
    if (get_check_count != 0) {
        for (s32 i = 0; i < get_check_count; i++) {
            actor2 = check_info[i];
            if (fopAcM_checkCarryNow(actor2)) {
                return;
            }
            switch (param_2) {
            case 0:
                if (fopAcM_searchActorDistance(actor, actor2) > 300.0f) {
                    if ((s16)cLib_distanceAngleS(actor->current.angle.y, fopAcM_searchActorAngleY(actor, actor2)) < 22000) {
                        actor2->current.angle.y = fopAcM_searchActorAngleY(actor2, actor);
                        actor2->speedF = cM_rndFX(5.0f) + 10.0f;
                        actor2->shape_angle.x -= (s16)((fopAcM_GetID(actor2) & 3) * 0x300 + 0x1000);
                        actor2->speed.y = 0.0f;
                    }
                } else {
                    actor2->speedF = 0.0f;
                }
                break;
            case 1:
                if ((s16)cLib_distanceAngleS(actor->current.angle.y, fopAcM_searchActorAngleY(actor, actor2)) < 22000) {
                    if (i_this->mActionState == 0x35) {
                        actor2->speedF = cM_rndFX(3.0f) + 3.0f;
                    } else {
                        actor2->speedF = cM_rndFX(5.0f) + 20.0f;
                        actor2->speed.y += cM_rndF(5.0f) + 5.0f;
                    }
                    if (actor2->speed.y > 20.0f) {
                        actor2->speed.y = 20.0f;
                    }
                    actor2->current.angle.y = fopAcM_searchActorAngleY(actor, actor2);
                    actor2->current.angle.y += (int)cM_rndFX(4096.0f);
                    actor2->shape_angle.x += -0x2000;
                }
                break;
            case 2:
                actor2->speedF = 0.0f;
                break;
            }
        }
    }
}

/* 000026F8-000027EC       .text maai_sub__FP9bpw_class */
void maai_sub(bpw_class* i_this) {
    f32 dVar4;
    cXyz local_2c;
    cXyz local_38;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* actor = &i_this->actor;
    dVar4 = std::fabsf(player->getSpeedF());
    if (!(fopAcM_searchPlayerDistance(actor) > 500.0f)) {
        cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor));
        local_2c.x = 0.0f;
        local_2c.y = 0.0f;
        local_2c.z = -500.0f;
        MtxPosition(&local_2c, &local_38);
        local_38 += player->current.pos;
        dVar4 *= 1.5f;
        cLib_addCalc2(&actor->current.pos.x, local_38.x, 1.0f, dVar4);
        cLib_addCalc2(&actor->current.pos.z, local_38.z, 1.0f, dVar4);
    }
}

/* 000027EC-000029B8       .text gouen_maai_sub__FP9bpw_class */
void gouen_maai_sub(bpw_class* i_this) {
    f32 dVar3;
    f32 dVar4;
    cXyz local_3c;
    cXyz local_48;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* actor = &i_this->actor;
    dVar4 = (REG9_F(7) + 2.0f);
    dVar3 = fopAcM_searchPlayerDistance(actor);
    if (dVar3 > REG9_F(9) + 500.0f) {
        cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor));
        local_3c.x = 0.0f;
        local_3c.y = 0.0f;
        local_3c.z = REG9_F(9) + 500.0f;
        MtxPosition(&local_3c, &local_48);
        local_48 += player->current.pos;
        cLib_addCalc2(&actor->current.pos.x, local_48.x, 1.0f, dVar4);
        cLib_addCalc2(&actor->current.pos.z, local_48.z, 1.0f, dVar4);
    }
    dVar3 = fopAcM_searchPlayerDistance(actor);
    if (dVar3 < (REG9_F(10) + 200.0f)) {
        cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor));
        dVar3 = (REG9_F(8) + 10.0f);
        local_3c.x = 0.0f;
        local_3c.y = 0.0f;
        local_3c.z = -(REG9_F(10) + 200.0f);
        MtxPosition(&local_3c, &local_48);
        local_48 += player->current.pos;
        cLib_addCalc2(&actor->current.pos.x, local_48.x, 1.0f, dVar3);
        cLib_addCalc2(&actor->current.pos.z, local_48.z, 1.0f, dVar3);
    }
}

/* 000029B8-00002BA8       .text kantera_pos_search__FP9bpw_class */
s32 kantera_pos_search(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 fVar2;
    fopAc_ac_c* pfVar3;
    cXyz local_44;
    cXyz local_50;

    if (i_this->m3FC != fpcM_ERROR_PROCESS_ID_e) {
        pfVar3 = fopAcM_SearchByID(i_this->m3FC);
        if (pfVar3 != NULL) {
            fVar1 = (pfVar3->current).pos.x - i_this->mBodyPos.x;
            fVar2 = (pfVar3->current).pos.z - i_this->mBodyPos.z;
            cMtx_YrotS(*calc_mtx, (s16)cM_atan2s(fVar1, fVar2));
            local_44.x = -120.0f;
            local_44.y = -20.0f;
            local_44.z = -320.0f;
            MtxPosition(&local_44, &local_50);
            local_50 += pfVar3->current.pos;
            cLib_addCalc2(&actor->current.pos.x, local_50.x, 1.0f, 120.0f);
            cLib_addCalc2(&actor->current.pos.y, local_50.y, 1.0f, 120.0f);
            cLib_addCalc2(&actor->current.pos.z, local_50.z, 1.0f, 120.0f);
            i_this->m476 = (s16)cM_atan2s(fVar1, fVar2);
            f32 fVar_x = actor->current.pos.x - local_50.x;
            f32 fVar_y = actor->current.pos.y - local_50.y;
            f32 fVar_z = actor->current.pos.z - local_50.z;
            fVar1 = std::sqrtf(fVar_x * fVar_x + fVar_y * fVar_y + fVar_z * fVar_z);
            if (fVar1 < 2.0f) {
                return 1;
            }
        }
    }
    return 0;
}

/* 00002BA8-000035F8       .text action_dousa__FP9bpw_class */
void action_dousa(bpw_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_c0;

    dBgS_LinChk linChk;
    switch (i_this->mActionState) {
    case 0:
        i_this->m488 = 1.0f;
        search_get_skull(i_this, 2);
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        if (i_this->m3F8 != 0x2a) {
            anm_init(i_this, BPW_BCK_WAIT1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        i_this->mSomeCountdownTimers[0] = 10;
        i_this->mSomeCountdownTimers[0] += (int)cM_rndF(i_this->mSomeCountdownTimers[0]);
        switch (i_this->m3F6) {
        case 0:
            i_this->m47A = DEMO_SELECT(REG11_F(1) + 0x100, 0x100);
            break;
        case 1:
            i_this->m47A = DEMO_SELECT(REG11_F(2) + 0x300, 0x300);
            break;
        case 2:
            i_this->m47A = DEMO_SELECT(REG11_F(3) + 0x500, 0x500);
            break;
        }
        i_this->mActionState++;
        // fallthrough
    case 1:
        if (i_this->mSomeCountdownTimers[0] == 0) {
            i_this->mActionState++;
            // fallthrough
        case 2:
            i_this->mSomeCountdownTimers[0] = 0x41;
            i_this->m490 = 10.0f;
            i_this->mSomeCountdownTimers[0] += (int)cM_rndF(i_this->mSomeCountdownTimers[0]);
            i_this->m488 = 1.0f;
            if (i_this->m3F6 == 2) {
                i_this->m490 = i_this->m490 * DEMO_SELECT(REG11_F(4) + 1.75f, REG8_F(0) + 1.35f);
                i_this->m488 = 5.0f;
            }
            if (i_this->m3F8 != 0x1d) {
                anm_init(i_this, BPW_BCK_MOVEF1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            i_this->mActionState++;
        case 3:
            if (i_this->mSomeCountdownTimers[0] == 0) {
                i_this->m490 = 0.0f;
                switch (i_this->m3F6) {
                case 0:
                    i_this->mBodyAction = ACTION_ATTACK_KOUGEKI;
                    i_this->mActionState = 0x14;
                    break;
                case 1:
                case 2:
                    if (dComIfGp_getDetect().chk_light(&player->current.pos)) {
                        i_this->mBodyAction = ACTION_ATTACK_KOUGEKI;
                        i_this->mActionState = 0x28;
                    } else if (REG12_S(9) != 0) {
                        i_this->mActionState = 4;
                    } else {
                        if (cM_rnd() < 0.5f) {
                            f32 f5 = 1100.0f;
                            f32 fVar15 = i_this->mBodyPos.x - actor->current.pos.x;
                            f32 fVar3 = i_this->mBodyPos.z - actor->current.pos.z;
                            if (std::sqrtf(SQUARE(fVar15) + SQUARE(fVar3)) < f5) {
                                i_this->mBodyAction = ACTION_BODY_DOWN_KARADA_TAORE;
                                i_this->mActionState = 0x46;
                                break;
                            }
                        }
                        i_this->mActionState = 4;
                    }
                }
                break;
            case 4:
                anm_init(i_this, BPW_BCK_MOVEB1, REG12_F(0) + 15.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mSomeCountdownTimers[0] = (s16)(int)(REG12_F(1) + 40.0f);
                noroi_brk_check(i_this, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_CURSE, 0);
                i_this->mActionState++;
            case 5:
                maai_sub(i_this);
                if (i_this->mSomeCountdownTimers[0] == 0) {
                    i_this->m3E6 = 1;
                    actor->speedF = REG8_F(12) + 75.0f;
                    i_this->m488 = REG8_F(13) + 2.0f;
                    i_this->m490 = 0.0f;
                    anm_init(i_this, BPW_BCK_MOVES1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    i_this->mActionState++;

                    // fallthrough
                case 6: {
                    if (actor->speedF < 1.0f) {
                        actor->speedF = 0.0f;
                    }
                    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
                    local_c0.x = 0.0f;
                    local_c0.y = 0.0f;
                    local_c0.z = 500.0f;
                    MtxPosition(&local_c0, i_this->m328);
                    i_this->m328[0] += actor->current.pos;
                    i_this->m328[0].y += 400.0f;
                    i_this->m304[0] = actor->current.pos;
                    i_this->m304[0].y += 400.0f;
                    linChk.Set(i_this->m304, i_this->m328, actor);
                    if (dComIfG_Bgsp()->LineCross(&linChk)) {
                        actor->speedF = 0.0f;
                    }
                    f32 f0;
                    f32 f1;
                    f1 = actor->speedF;
                    f0 = 0.0f;
                    if (f1 == f0) {
                        noroi_brk_check(i_this, 1);
                        next_status_clear(i_this, 1);
                        if (player->checkConfuse()) {
                            i_this->mBodyAction = ACTION_ATTACK_KOUGEKI;
                            i_this->mActionState = 0x14;
                        } else {
                            i_this->mActionState = 0;
                        }
                    }
                    break;
                }
                case 10:
                    search_get_skull(i_this, 2);
                    for (s32 i = 0; i < 10; i++) {
                        i_this->mSomeCountdownTimers[i + 10] = 0;
                    }
                    if (i_this->m3F8 != 0x2a) {
                        anm_init(i_this, BPW_BCK_WAIT1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                    }
                    i_this->mActionState++;
                case 0xb:
                    cLib_addCalcAngleS2(&i_this->m47E, 0, 1, 10);
                    if (i_this->m47E < 2) {
                        i_this->m47E = 0;
                        if (kantera_pos_search(i_this)) {
                            i_this->mActionState++;
                        }
                    }
                    break;
                case 0xc:
                    cLib_addCalcAngleS2(&i_this->m47E, 0x96, 1, 0x1e);
                    if (i_this->m47E >= 0x95) {
                        i_this->m47E = 0x96;
                        i_this->m480 = 0x96;
                        anm_init(i_this, BPW_BCK_HIROU1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                        kantera_pos_search(i_this);
                        i_this->mActionState++;
                    }
                    break;
                case 0xd:
                    if (i_this->m462 == 0) {
                        kantera_pos_search(i_this);
                    }
                    if (i_this->mpMorf->checkFrame(12.0f)) {
                        fopAcM_seStart(actor, JA_SE_CM_BPW_GET_KANTERA, 0);
                        if (i_this->m3FC != fpcM_ERROR_PROCESS_ID_e) {
                            bpw_class* pfVar6 = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
                            if (pfVar6 != NULL) {
                                pfVar6->actor.gravity = 0.0f;
                                pfVar6->actor.speedF = 0.0f;
                                pfVar6->actor.speed.setall(0.0f);
                                pfVar6->actor.attention_info.flags = 0;
                                pfVar6->mActionState = 0;
                                i_this->m462 = 1;
                            }
                        }
                        i_this->m482 = 0;
                        i_this->m388 = 0.0f;
                        i_this->m38C = 0.0f;
                        i_this->m390 = 0.0f;
                        i_this->mAttWaitTimer = 1;
                    }
                    if (i_this->mpMorf->isStop()) {
                        next_status_clear(i_this, 1);
#if VERSION > VERSION_DEMO
                        i_this->mSomeCountdownTimers[2] = 0;
#endif
                        i_this->mBodyAction = ACTION_ATTACK_KOUGEKI;
                        i_this->mActionState = 0x14;
                    }
                    // fallthrough
                }
            }
        }
    }
    i_this->m4A0 = 0.0f;
    cLib_addCalc2(&actor->speedF, i_this->m490, 1.0f, i_this->m488);
    cLib_addCalc0(&i_this->m48C, 1.0f, 10.0f);
    if ((((i_this->mActionState != 10) && (i_this->mActionState != 0xb)) && (i_this->mActionState != 0xc)) && (i_this->mActionState != 0xd)) {
        if (i_this->mActionState != 6) {
            i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        }
        alpha_anime(i_this);
        fuwafuwa_calc(i_this);
    }
    noroi_check(i_this);
}

/* 00003A30-00004870       .text action_kougeki__FP9bpw_class */
void action_kougeki(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = daPy_getPlayerActorClass();

    switch (i_this->mActionState) {
    case 0x14:
        if (i_this->mSomeCountdownTimers[2] != 0)
            break;
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        if (i_this->m3F8 != 0x2b) {
            anm_init(i_this, BPW_BCK_WARAU1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        i_this->m47A = 0x500;
        i_this->m4A0 = 0.0f;
        i_this->mSomeCountdownTimers[0] = 30;
        i_this->mActionState++;
        // fallthrough
    case 0x15:
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        maai_sub(i_this);
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        switch (i_this->m3F6) {
        case 1:
        case 2:
            if (player->checkConfuse()) {
                i_this->mActionState = 0x3c;
                break;
            }
            // Fall-through
        case 0:
            i_this->mActionState = 0x28;
            f32 f31 = 1050.0f;
            if (fopAcM_searchPlayerDistance(actor) < f31) {
                i_this->mActionState = 0x3c;
            }
            break;
        }
        if (i_this->m3E9 != 0) {
            i_this->mActionState = 0x32;
            i_this->m3E9 = 0;
        }
        break;
    case 0x28:
        if (i_this->mSomeCountdownTimers[2] != 0)
            break;
        anm_init(i_this, BPW_BCK_SUIKOMU1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mSomeCountdownTimers[0] = 30;
        i_this->mSomeCountdownTimers[0] += (int)cM_rndF(i_this->mSomeCountdownTimers[0]);
#if VERSION == VERSION_DEMO
        i_this->m508_demo = dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWINHALE01, &i_this->m394);
#else
        if (i_this->m540.getEmitter() != NULL) {
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWINHALE01, &i_this->m394, NULL, NULL, 0xFF, &i_this->m540);
        }
#endif
        i_this->mActionState++;
        // fallthrough
    case 0x29: {
#if VERSION == VERSION_DEMO
        cXyz local_68 = actor->eyePos;
        actor->eyePos = i_this->m3C4;
        fopAcM_seStart(actor, JA_SE_OBJ_BPW_BREATH_IN, 0);
        actor->eyePos = local_68;
#else
        mDoAud_seStart(JA_SE_OBJ_BPW_BREATH_IN, &i_this->m3C4, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        search_get_skull(i_this, 0);
#if VERSION == VERSION_DEMO
        if (i_this->m508_demo != NULL) {
            i_this->m508_demo->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
        }
#else
        if (i_this->m540.getEmitter() != NULL) {
            i_this->m540.getEmitter()->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
        }
#endif
        if (i_this->mSomeCountdownTimers[1] == 0) {
            JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWINHALE00, &i_this->m394, &actor->shape_angle);
            if (emitter != NULL) {
                emitter->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
            }
            i_this->mSomeCountdownTimers[1] = 6;
        }
        if (i_this->mSomeCountdownTimers[0] != 0) {
            if (fopAcM_searchPlayerDistance(actor) > 300.0f) {
                player->setOutPower(10.0f, fopAcM_searchPlayerAngleY(actor) + 0x8000, 1);
            }
        } else {
#if VERSION == VERSION_DEMO
            if (i_this->m508_demo) {
                i_this->m508_demo->becomeInvalidEmitter();
                i_this->m508_demo = NULL;
            }
#else
            i_this->m540.remove();
#endif
            anm_init(i_this, BPW_BCK_IKI1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mActionState++;
        }
        break;
    }
    case 0x2a:
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        search_get_skull(i_this, 2);
        if (i_this->mpMorf->isStop()) {
            i_this->mSomeCountdownTimers[0] = 0x5a;
            i_this->mSomeCountdownTimers[0] += (int)cM_rndF(i_this->mSomeCountdownTimers[0]);
#if VERSION == VERSION_DEMO
            i_this->m50C_demo = dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWBLOW00, &i_this->m394, NULL, NULL, 0xFF, DEMO_SELECT(NULL, &i_this->m52C));
#else
            if (i_this->m52C.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWBLOW00, &i_this->m394, NULL, NULL, 0xFF, DEMO_SELECT(NULL, &i_this->m52C));
            }
#endif
            i_this->mFire1DousaPos = actor->current.pos;
            i_this->mFire1DousaPos.y = i_this->mAcch.GetGroundH();
            i_this->mFire1DousaRot = actor->shape_angle;
#if VERSION == VERSION_DEMO
            i_this->m50C.remove();
            i_this->m510_demo = dComIfGp_particle_setToon(
                dPa_name::ID_AK_ST_BPWBLOWSMOKE00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xa0, &i_this->m50C, fopAcM_GetRoomNo(actor)
            );
#else
            if (i_this->m50C.getEmitter() == NULL) {
                dComIfGp_particle_setToon(
                    dPa_name::ID_AK_ST_BPWBLOWSMOKE00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xa0, &i_this->m50C, fopAcM_GetRoomNo(actor)
                );
            }
#endif
            anm_init(i_this, BPW_BCK_IKI_WAIT1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mActionState++;
        }
        break;
    case 0x2b: {
#if VERSION == VERSION_DEMO
        cXyz local_5c = actor->eyePos;
        actor->eyePos = i_this->m3C4;
        fopAcM_seStart(actor, JA_SE_OBJ_BPW_BREATH_OUT, 0);
        actor->eyePos = local_5c;
#else
        mDoAud_seStart(JA_SE_OBJ_BPW_BREATH_OUT, &i_this->m3C4, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        search_get_skull(i_this, 1);
#if VERSION == VERSION_DEMO
        if (i_this->m50C_demo != NULL) {
            i_this->m50C_demo->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
        }
#else
        if (i_this->m52C.getEmitter() != NULL) {
            i_this->m52C.getEmitter()->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(2));
        }
#endif
        i_this->mFire1DousaPos = actor->current.pos;
        i_this->mFire1DousaPos.y = i_this->mAcch.GetGroundH();
        i_this->mFire1DousaRot = actor->shape_angle;
        if (i_this->mSomeCountdownTimers[0] != 0) {
            player->setOutPower(14.0f, fopAcM_searchPlayerAngleY(actor), 1);
        } else {
            search_get_skull(i_this, 2);
            fire_and_emitter_clear(i_this);
            next_att_wait_check(i_this);
            i_this->mSomeCountdownTimers[2] = (s16)(int)(REG12_F(7) + 90.0f);
        }
        break;
    }
    case 0x32:
        anm_init(i_this, BPW_BCK_SUIKOMU1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mSomeCountdownTimers[0] = 0x4b;
        i_this->mSomeCountdownTimers[1] = (s16)(int)(REG8_F(2) + 20.0f);
        i_this->mKankyouHendouState = 2;
        i_this->mActionState++;
        // fallthrough
    case 0x33: {
#if VERSION == VERSION_DEMO
        cXyz local_50 = actor->eyePos;
        actor->eyePos = i_this->m3C4;
        fopAcM_seStart(actor, JA_SE_OBJ_BPW_BREATH_IN, 0);
        actor->eyePos = local_50;
#else
        mDoAud_seStart(JA_SE_OBJ_BPW_BREATH_IN, &i_this->m3C4, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
        if (i_this->mSomeCountdownTimers[1] != 0) {
            i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        }
        i_this->m47A = (s16)(int)(REG21_F(2) + 140.0f);
        search_get_skull(i_this, 0);
        if (i_this->mSomeCountdownTimers[0] != 0) {
            if (fopAcM_searchPlayerDistance(actor) > 300.0f) {
                player->setOutPower(10.0f, fopAcM_searchPlayerAngleY(actor) + 0x8000, 1);
            }
        } else {
            anm_init(i_this, BPW_BCK_HONOO1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mActionState++;
        }
        break;
    }
    case 0x34:
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        i_this->m47A = (s16)(int)(REG21_F(2) + 140.0f);
        search_get_skull(i_this, 2);
        if (i_this->mpMorf->isStop()) {
            bpw_class* pfVar6 = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
            if (pfVar6 != NULL) {
                u32 params = ACTOR_TYPE_DAMAGE_BALL;
                params |= DAMAGE_ACTION_LINE << 8;
                i_this->m400 = fopAcM_create(PROC_BPW, params, &pfVar6->m358, fopAcM_GetRoomNo(actor), &actor->current.angle);
                i_this->mSomeCountdownTimers[0] = 0x46;
                i_this->mSomeCountdownTimers[0] += (int)cM_rndF(i_this->mSomeCountdownTimers[0]);
                i_this->m47A = 0x300;
                i_this->mSomeCountdownTimers[5] = 0;
                GOUEN_FIRE_HIT = 0;
                anm_init(i_this, BPW_BCK_HONOO_WAIT1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->mActionState++;
            }
        }
        break;
    case 0x35: {
#if VERSION == VERSION_DEMO
        cXyz local_44 = actor->eyePos;
        actor->eyePos = i_this->m3C4;
        fopAcM_seStart(actor, JA_SE_OBJ_BPW_FIREBLAST, 0);
        actor->eyePos = local_44;
#else
        mDoAud_seStart(JA_SE_OBJ_BPW_FIREBLAST, &i_this->m3C4, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        gouen_maai_sub(i_this);
        bpw_class* pfVar5 = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
        if (pfVar5 != NULL) {
            bpw_class* pfVar8 = (bpw_class*)fopAcM_SearchByID(i_this->m400);
            if (pfVar8 != NULL) {
                pfVar8->actor.current.pos = pfVar5->m358;
                pfVar8->actor.current.angle = actor->shape_angle;
                pfVar8->actor.shape_angle.y = actor->shape_angle.y;
                f32 fVar15 = player->current.pos.x - pfVar8->actor.current.pos.x;
                f32 dVar14 = player->current.pos.y - pfVar8->actor.current.pos.y;
                f32 fVar1 = player->current.pos.z - pfVar8->actor.current.pos.z;
                fVar15 = std::sqrtf(SQUARE(fVar15) + SQUARE(fVar1));
                pfVar8->actor.shape_angle.x = -cM_atan2s(dVar14, fVar15);
            }
        }
        i_this->m47A = (s16)(int)(REG21_F(2) + 140.0f);
        if ((DEMO_SELECT(REG8_S(5), REG8_S(4)) == 0) && (GOUEN_FIRE_HIT != 0 || (i_this->mSomeCountdownTimers[0] == 0))) {
            fire_and_emitter_clear(i_this);
            next_status_clear(i_this, 1);
            next_att_wait_check(i_this);
            GOUEN_FIRE_HIT = 0;
            i_this->mSomeCountdownTimers[0] = 0;
            i_this->mSomeCountdownTimers[5] = REG21_S(0) + 10;
        }
        break;
    }
    case 0x3c:
        i_this->mSomeCountdownTimers[0] = 0x28;
        i_this->mSomeCountdownTimers[0] += (int)cM_rndF(i_this->mSomeCountdownTimers[0]);
        i_this->mKankyouHendouState = 1;
        i_this->mSomeCountdownTimers[5] = 0;
        i_this->mAttWaitTimer = 2;
        if (i_this->m3F8 != 5) {
            anm_init(i_this, BPW_BCK_ATTACK_KAN1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            fopAcM_monsSeStart(actor, JA_SE_CV_BPW_ATTACK, 0);
        }
        i_this->mActionState++;
        // fallthrough
    case 0x3d:
        maai_sub(i_this);
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        fopAcM_seStart(actor, JA_SE_CM_BPW_SWING_KANTERA, 0);
        if (i_this->mSomeCountdownTimers[1] == 0) {
            fopAcM_seStart(actor, JA_SE_OBJ_BPW_FIRE_OUT, 0);
            bpw_class* pfVar7 = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
            if (pfVar7 != NULL) {
                u32 params = ACTOR_TYPE_DAMAGE_BALL;
                params |= DAMAGE_ACTION_DAMAGE_BALL << 8;
                cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
                cXyz local_38;
                local_38.x = 0.0f;
                local_38.y = 0.0f;
                local_38.z = 20.0f;
                cXyz cStack_44;
                MtxPosition(&local_38, &cStack_44);
                cStack_44 += pfVar7->m358;
                i_this->m400 = fopAcM_create(PROC_BPW, params, &cStack_44, fopAcM_GetRoomNo(actor), &actor->current.angle);
                i_this->mSomeCountdownTimers[1] = REG12_S(4) + 7;
                if (player->checkConfuse()) {
                    i_this->mSomeCountdownTimers[1] = REG12_S(4) + 9;
                }
            }
        }
        if (i_this->mSomeCountdownTimers[0] == 0) {
            i_this->mAttWaitTimer = 1;
            i_this->mSomeCountdownTimers[5] = (s16)REG21_S(1) + 90.0f;
            if (!player->checkConfuse()) {
                next_att_wait_check(i_this);
            } else {
                i_this->mActionState = 0x28;
            }
        }
        // fallthrough
    }
    cLib_addCalc0(&actor->speedF, 1.0f, 1.0f);
    alpha_anime(i_this);
    fuwafuwa_calc(i_this);
}

/* 00004870-000051E0       .text action_karada_taore__FP9bpw_class */
void action_karada_taore(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;
    GXColor local_24;
    GXColor local_28;

    daPy_py_c* player = daPy_getPlayerActorClass();
    switch (i_this->mActionState) {
    case 0x46:
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        if (i_this->m3F8 != 0x28) {
            anm_init(i_this, BPW_BCK_TAME1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        fopAcM_monsSeStart(actor, JA_SE_CV_BPW_CURSE, 0);
        noroi_brk_check(i_this, 0);
        actor->speedF = 0.0f;
        search_get_skull(i_this, 2);
        i_this->mActionState++;
        // fallthrough
    case 0x47:
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        if (i_this->mpMorf->checkFrame(DEMO_SELECT(REG11_F(15) + 26.0f, 26.0f))) {
            i_this->mFire1DousaPos = actor->current.pos;
            i_this->mFire1DousaPos.y = i_this->mAcch.GetGroundH();
            i_this->m5E0[1].remove();
            emitter = dComIfGp_particle_setToon(
                dPa_name::ID_AK_ST_BPWJUMPSMOKE00, &i_this->mFire1DousaPos, &actor->shape_angle, NULL, 0xb9, &i_this->m5E0[1], fopAcM_GetRoomNo(actor)
            );
            if (emitter != NULL) {
                dKy_get_seacolor(&local_24, &local_28);
                emitter->setGlobalPrmColor(local_24.r, local_24.g, local_24.b);
                emitter->setGlobalEnvColor(local_28.r, local_28.g, local_28.b);
            }
            fopAcM_seStart(actor, JA_SE_CM_BPW_J_BPRESS_JUMP, 0);
            actor->speed.y = REG8_F(6) + 100.0f;
            actor->gravity = -(REG8_F(7) + 6.0f);
            actor->speedF = REG8_F(8) + 30.0f;
            i_this->m4A8 = DEMO_SELECT(REG11_F(16) + 500.0f, 500.0f);
            i_this->mActionState++;
        }
        break;
    case 0x48:
        if ((i_this->mpMorf->isStop()) && (i_this->m3F8 != 0x19)) {
            anm_init(i_this, BPW_BCK_JUMP1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mAttWaitTimer = 0;
            i_this->mActionState++;
        }
        break;
    case 0x49:
        if (!i_this->mAcch.ChkGroundHit())
            break;
        fopAcM_seStart(actor, JA_SE_CM_BPW_J_BPRESS_PRESS, 0);
        actor->speed.setall(0.0f);
        actor->speedF = 0.0f;
        i_this->mActionState = 0x4a;
    case 0x4a:
        fire_and_emitter_clear(i_this);
        i_this->m47E = 200;
        i_this->m480 = 200;
        i_this->m4A4 = 100.0f;
        search_get_skull(i_this, 2);
        actor->gravity = -3.0f;
        anm_init(i_this, BPW_BCK_PRESS1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m3E8 = 2;
        i_this->mSomeCountdownTimers[6] = (s16)(int)(REG21_F(0) + 20.0f);
        i_this->mFire1DousaPos = actor->current.pos;
        i_this->mFire1DousaPos.y = i_this->mAcch.GetGroundH();
        i_this->m5E0[2].remove();
        emitter = dComIfGp_particle_setToon(
            dPa_name::ID_AK_ST_BPWPRESSSMOKE00, &i_this->mFire1DousaPos, &actor->shape_angle, NULL, 0xb9, &i_this->m5E0[2], fopAcM_GetRoomNo(actor)
        );
        if (emitter != NULL) {
            dKy_get_seacolor(&local_24, &local_28);
            emitter->setGlobalPrmColor(local_24.r, local_24.g, local_24.b);
            emitter->setGlobalEnvColor(local_28.r, local_28.g, local_28.b);
        }
        i_this->mActionState++;
        break;
    case 0x4b:
        cLib_addCalc2(&i_this->m3AC.y, 240.0f, 1.0f, 10.0f);
        i_this->m47E = 200;
        i_this->m480 = 200;
        if (!i_this->mAcch.ChkGroundHit()) {
            break;
        }
        actor->speed.setall(0.0f);
        actor->speedF = 0.0f;
        actor->gravity = 0.0f;
        i_this->mActionState++;
    case 0x4c:
        if (i_this->m3F8 == 0x23) {
            if ((i_this->mpMorf->getFrame() >= DEMO_SELECT(40.0f, REG8_F(1) + 40.0f)) && (i_this->mAttWaitTimer == 0)) {
                i_this->mAttWaitTimer = 1;
            }
            cLib_addCalc2(&i_this->m3AC.y, 340.0f, 1.0f, 10.0f);
        } else if (((i_this->m3F8 == 0x25) && (i_this->mpMorf->getFrame() >= DEMO_SELECT(40.0f, REG8_F(1) + 30.0f))) && (i_this->mAttWaitTimer == 0)) {
            i_this->mAttWaitTimer = 1;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->m3AC.y = 340.0f;
            noroi_brk_check(i_this, 1);
            next_status_clear(i_this, 1);
            if ((!next_att_wait_check(i_this)) && (player->checkConfuse())) {
                i_this->mBodyAction = ACTION_ATTACK_KOUGEKI;
                i_this->mActionState = 0x14;
            }
        }
        break;
    case 0x4d:
        fire_and_emitter_clear(i_this);
        i_this->m47E = 200;
        i_this->m480 = 200;
        i_this->m4A4 = 100.0f;
        i_this->m4A8 = REG8_F(16) + 220.0f;
        search_get_skull(i_this, 2);
        actor->speed.setall(0.0f);
        actor->speedF = 0.0f;
        noroi_brk_check(i_this, 0);
        anm_init(i_this, BPW_BCK_SONOBA_PRESS1, REG12_F(2) + 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_monsSeStart(actor, JA_SE_CV_BPW_CURSE, 0);
        actor->speedF = DEMO_SELECT(REG11_F(12) + 14.75f, 14.75f);
        i_this->mAttWaitTimer = 0;
        i_this->mActionState++;
        break;
    case 0x4e:
        cLib_addCalc2(&i_this->m3AC.y, 240.0f, 1.0f, 10.0f);
        if (i_this->mpMorf->getFrame() <= DEMO_SELECT(REG11_F(11) + 20.0f, 20.0f)) {
            i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        }
        if (i_this->mpMorf->getFrame() >= DEMO_SELECT(REG11_F(13) + 40.0f, 40.0f)) {
            cLib_addCalc0(&actor->speedF, 1.0f, DEMO_SELECT(REG11_F(14) + 0.55f, 0.55f));
        }
        if (i_this->mpMorf->checkFrame(40.0f)) {
            i_this->mFire1DousaPos = actor->current.pos;
            i_this->mFire1DousaPos.y = i_this->mAcch.GetGroundH();
            i_this->m5E0[3].remove();
            emitter = dComIfGp_particle_setToon(
                dPa_name::ID_AK_ST_BPWPRESSSMOKE01, &i_this->mFire1DousaPos, &actor->shape_angle, NULL, 0xb9, &i_this->m5E0[3], fopAcM_GetRoomNo(actor)
            );
            if (emitter != NULL) {
                dKy_get_seacolor(&local_24, &local_28);
                emitter->setGlobalPrmColor(local_24.r, local_24.g, local_24.b);
                emitter->setGlobalEnvColor(local_28.r, local_28.g, local_28.b);
            }
            actor->gravity = -3.0f;
            fopAcM_seStart(actor, JA_SE_CM_BPW_BODY_PRESS, 0);
            i_this->m3E8 = 1;
            i_this->mSomeCountdownTimers[6] = (s16)(int)(REG21_F(1) + 20.0f);
            i_this->m4A8 = REG8_F(17) + 400.0f;
        }
        if (i_this->mpMorf->isStop()) {
            i_this->mSomeCountdownTimers[0] = 5;
#if VERSION == VERSION_DEMO
            i_this->mAttWaitTimer = 1;
#endif
            i_this->mActionState++;
        }
        break;
    case 0x4f:
        if (i_this->mSomeCountdownTimers[0] == 0) {
            anm_init(i_this, BPW_BCK_SONOBA_PRESS2, REG12_F(2) + 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mActionState = 0x4c;
        }
        // fallthrough
    }
    if (i_this->mActionState >= 0x4A) {
        alpha_anime(i_this);
    }
    noroi_check(i_this);
}

/* 000051E0-000062D8       .text action_damage__FP9bpw_class */
void action_damage(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DAnmTevRegKey* pBrk;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    J3DModel* model = i_this->mpMorf->getModel();
    switch (i_this->mActionState) {
    case 0x50:
        search_get_skull(i_this, 2);
        if (i_this->mSomeCountdownTimers[5] == 0) {
            switch (i_this->mKankyouHendouState) {
            case 1:
                i_this->mSomeCountdownTimers[5] = (int)(REG21_S(1) + 90.0f);

                break;
            case 2:
                i_this->mSomeCountdownTimers[5] = REG21_S(0) + 10;
                break;
            case 3:
                i_this->mSomeCountdownTimers[5] = REG21_S(2) + 10;
                break;
            }
        }
        next_status_clear(i_this, 1);
        i_this->m4A4 = 300.0f;
        fire_and_emitter_clear(i_this);
        i_this->m478 = 0;
        i_this->m47E = 200;
        i_this->m480 = 200;
        actor->speedF = 0.0f;
        i_this->m490 = 0.0f;
        anm_init(i_this, BPW_BCK_HIT1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mSomeCountdownTimers[9] = 0;
        i_this->m476 = fopAcM_searchPlayerAngleY(actor);
        actor->current.angle.y = i_this->m476;
        actor->shape_angle.y = i_this->m476;
        i_this->mActionState++;
    case 0x51:
        if ((i_this->mHitType == 10) || (i_this->mHitType == 0xb)) {
            if (i_this->mHitType == 0xb) {
                fopAcM_seStart(actor, JA_SE_CM_BPW_SOLID_END, 0);
                i_this->m47E = 0xFF;
            } else {
                i_this->m47E = i_this->m47E + 1;
                fopAcM_seStart(actor, JA_SE_CM_BPW_BECOME_SOLID, 0);
                if (i_this->mSomeCountdownTimers[9] == 0) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LIGHT_DAMAGE, 0);
                    i_this->mSomeCountdownTimers[9] = 30;
                }
                if (i_this->m3E1 == 0) {
                    i_this->m3E1 = 1;
                    i_this->m3E2 = 0;
                    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_HIT);
                    i_this->mpLightStunBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, 0);
                }
            }
            if (i_this->m47E >= 0xFF) {
                i_this->m47E = 0xFF;
                i_this->m478 = 0;
                fopAcM_seStart(actor, JA_SE_CM_BPW_SOLID_END, 0);
                i_this->mSomeCountdownTimers[0] = 0x12;
                i_this->m3E0 = 1;
                if (((i_this->mAttWaitTimer == 1) || (i_this->mAttWaitTimer == 2)) || (i_this->mAttWaitTimer == 0)) {
                    i_this->mAttWaitTimer = 3;
                }
                pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_HIRARU1);
                i_this->mpLightFreezeBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
                anm_init(i_this, BPW_BCK_DOSUN1, 0.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1);
                i_this->m4A0 = 50.0f;
                i_this->mBodyAtSph.ClrAtSet();
                i_this->mBodyAtSph.ClrAtSet();
                i_this->mActionState++;
            }
        } else {
            i_this->mSomeCountdownTimers[2] = (s16)(int)(REG12_F(7) + 90.0f);
            if (!next_att_wait_check(i_this)) {
                i_this->mBodyAction = ACTION_ATTACK_KOUGEKI;
                i_this->mActionState = 0x14;
            }
            if (i_this->m3F8 != 0x2a) {
                anm_init(i_this, BPW_BCK_WAIT1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            if (i_this->m3E1 != 0) {
                i_this->m3E1 = 0;
                pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_DEFAULT);
                i_this->mpDefaultBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            }
        }
        break;
    case 0x52:
        if (i_this->mpLightFreezeBrkAnm->isStop()) {
            fopAcM_monsSeStart(actor, JA_SE_CV_BPW_BECOME_SOLID, 0);
        }
        if (i_this->mSomeCountdownTimers[0] == 0) {
            cLib_addCalc2(&i_this->m48C, -120.0f, 1.0f, 10.0f);
            actor->gravity = -2.0f;
            if (i_this->mAcch.ChkGroundHit()) {
                actor->gravity = 0.0f;
                actor->speed.setall(0.0f);
                i_this->mBodyCoSph.OnTgShield();
                i_this->mSomeCountdownTimers[6] = REG21_F(1) + 20.0f;
                i_this->m3E8 = 1;
                i_this->mBodyCoSph.OnCoSetBit();
                i_this->m48C = -120.0f;
                i_this->mActionState = 0x53;
                fopAcM_seStart(actor, JA_SE_CM_BPW_SOLID_FALL, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LANDING, 0);
#if VERSION > VERSION_DEMO
                i_this->mSomeCountdownTimers[1] = 0;
#endif
                anm_init(i_this, BPW_BCK_DOSUN1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                actor->gravity = 0.0f;
            }
        }
        break;
    case 0x53:
        if (i_this->m3F8 != 0xc) {
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, BPW_BCK_DOSUN_WAIT1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->mSomeCountdownTimers[1] = DEMO_SELECT(240, 450);
                cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
                i_this->m684 = actor->shape_angle.y;
            }
        }
        if (fopAcM_checkCarryNow(actor)) {
            anm_init(i_this, BPW_BCK_JITA1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mBodyCoSph.ClrCoSet();
            i_this->m3AC.y = 300.0f;
            actor->current.angle.y = player->shape_angle.y;
            i_this->m47A = 0;
            i_this->mSomeCountdownTimers[9] = 0;
            i_this->mActionState++;
        }
        if (i_this->mSomeCountdownTimers[1] == 1) {
            fopAcM_cancelCarryNow(actor);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            actor->current.angle.y = actor->shape_angle.y;
            next_status_clear(i_this, 0);
            next_att_wait_check(i_this);
        }
        break;
    case ACTION_STATE_DAMAGE_CARRIED:
        if (REG8_S(3) != 0) {
            i_this->m684 += player->shape_angle.y - actor->current.angle.y;
            actor->shape_angle.y = i_this->m684;
            actor->current.angle.y = player->shape_angle.y;
        } else {
            actor->current.angle.y = player->shape_angle.y;
            cLib_addCalcAngleS2(&actor->shape_angle.y, player->shape_angle.y, 1, 0x700);
        }
        if (i_this->mSomeCountdownTimers[9] == 0) {
            fopAcM_monsSeStart(actor, JA_SE_CV_BPW_JITABATA, 0);
            i_this->mSomeCountdownTimers[9] = 0x20;
        }
        if (!fopAcM_checkCarryNow(actor)) {
            actor->gravity = -3.0f;
            actor->speed.y = 10.0f;
            i_this->m490 = 120.0f;
            i_this->m47A = 0;
            i_this->m3AC.y = 340.0f;
            if (REG8_S(3) != 0) {
                i_this->m3D6.y = player->shape_angle.y;
                actor->shape_angle.x = -0x4000;
                actor->shape_angle.z = 0;
            } else {
                actor->shape_angle.x = 0;
                actor->shape_angle.z = 0;
            }
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            i_this->m3E5 = 1;
            i_this->m49C = 300.0f;
            i_this->mBodyCoSph.OnCoSetBit();
            fopAcM_monsSeStart(actor, JA_SE_CV_BPW_THROWN, 0);
            anm_init(i_this, BPW_BCK_TAMA1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mActionState = ACTION_STATE_DAMAGE_THROWN;
        } else if (i_this->mSomeCountdownTimers[1] == 1) {
            fopAcM_cancelCarryNow(actor);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            actor->current.angle.y = actor->shape_angle.y;
            next_status_clear(i_this, 0);
            next_att_wait_check(i_this);
        }
        break;
    case ACTION_STATE_DAMAGE_THROWN: {
        fopAcM_seStart(actor, JA_SE_CM_BPW_ROLLING, 0);
        if (REG8_S(3) != 0) {
            i_this->m3D6.x += 5000;
        } else {
            actor->shape_angle.x = actor->shape_angle.x + 0x1000;
        }
        int r25 = wall_HIT_check(i_this);
        if (r25 != 0) {
            i_this->m3E5 = 0;
            i_this->m3D6.setall(0);
            dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(i_this));
            actor->current.angle.y = cM_atan2s(i_this->mBodyPos.x - actor->current.pos.x, i_this->mBodyPos.z - actor->current.pos.z);
            if (r25 == 2) {
                fopAcM_seStart(actor, JA_SE_CM_BPW_DAMAGE_TOGE, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_DAMAGE, 0);
                i_this->mSomeCountdownTimers[6] = (s16)(int)(REG21_F(0) + 20.0f);
                i_this->m3E8 = 2;
                i_this->mActionState = 100;
            } else {
                fopAcM_seStart(actor, JA_SE_CM_BPW_BOUND_NO_DMG, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LANDING, 0);
                actor->shape_angle.x = 0;
                i_this->mSomeCountdownTimers[6] = (s16)(int)(REG21_F(1) + 20.0f);
                i_this->m3E8 = 1;
                i_this->mActionState = 0x5a;
            }
        }
        break;
    }
    case 0x5a:
        actor->speed.y = REG12_F(4) + 30.0f;
        actor->gravity = -(REG12_F(5) + 3.0f);
        actor->speedF = REG12_F(6) + 20.0f;
        i_this->m490 = REG12_F(6) + 20.0f;
        i_this->m47A = 0;
        anm_init(i_this, BPW_BCK_DOSUN1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mActionState++;
        break;
    case 0x5b:
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x2000);
        if (!i_this->mAcch.ChkGroundHit())
            break;
        i_this->mActionState++;
    case 0x5c:
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x2000);
        if (i_this->mpMorf->isStop()) {
#if VERSION > VERSION_DEMO
            i_this->mSomeCountdownTimers[0] = 0;
            i_this->mSomeCountdownTimers[1] = 0;
#endif
            next_status_clear(i_this, 0);
            next_att_wait_check(i_this);
        }
        break;
    case 100:
        actor->speedF = 5.0f;
        i_this->m490 = 5.0f;
        i_this->m47A = 0;
        actor->gravity = -3.0f;
        actor->speed.y = 70.0f;
        anm_init(i_this, BPW_BCK_DAMAGE1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mActionState++;
        break;
    case ACTION_STATE_DAMAGE_HIT:
        actor->shape_angle.y = actor->shape_angle.y + 0x1500;
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x2000);
        if (i_this->mAcch.ChkGroundHit()) {
            i_this->m3E8 = 2;
            i_this->mSomeCountdownTimers[6] = (s16)(int)(REG21_F(0) + 20.0f);
            i_this->mFire1DousaPos = actor->current.pos;
            i_this->mFire1DousaPos.y = i_this->mAcch.GetGroundH();
            i_this->m5E0[0].remove();
            JPABaseEmitter* emitter = dComIfGp_particle_setToon(
                dPa_name::ID_AK_ST_BPWSIRIMOTISMOKE00, &i_this->mFire1DousaPos, &actor->shape_angle, NULL, 0xb9, &i_this->m5E0[0], fopAcM_GetRoomNo(actor)
            );
            if (emitter != NULL) {
                GXColor local_64;
                GXColor local_68;
                dKy_get_seacolor(&local_64, &local_68);
                emitter->setGlobalPrmColor(local_64.r, local_64.g, local_64.b);
                emitter->setGlobalEnvColor(local_68.r, local_68.g, local_68.b);
            }
            fopAcM_seStart(actor, JA_SE_CM_BPW_DAMAGE_EXPLODE, 0);
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWBUNRETUSMOKE00, &actor->current.pos);
#if VERSION > VERSION_DEMO
            u32 uVar14;
            s32 i;
            cXyz local_58;
            csXyz pwAngle = actor->shape_angle;
            local_58 = actor->current.pos;
            int currRandomAngle;
            int pwSpreadAmount = (int)(65536.0f / actor->health);
            local_58.y = i_this->mAcch.GetGroundH() + 20.0f;
            i_this->m3E9 = 0;
            for (i = 0; i < 15; i++) {
                i_this->mChildPoeIds[i] = fpcM_ERROR_PROCESS_ID_e;
            }
            currRandomAngle = (int)cM_rndFX(32768.0f);
            uVar14 = (s16)cM_rndF(4.99f);
            u32 uVar2 = uVar14 << 9 | 0xFF000003;
            for (i = 0; i < actor->health; i++) {
                f32 maxPoeSpread = ((s16)pwSpreadAmount * 0.25f);
                i_this->mChildPoeIds[i] = fopAcM_createChild(PROC_PW, fopAcM_GetID(i_this), uVar2, &local_58, fopAcM_GetRoomNo(actor), &pwAngle);
                currRandomAngle += pwSpreadAmount;
                pwAngle.y = (s16)currRandomAngle;
                pwAngle.y += (int)cM_rndFX((f32)maxPoeSpread);
                uVar14++;
                if (uVar14 > 5) {
                    uVar14 = 0;
                }
                uVar2 = uVar14 << 9 | 0xFF000003;
            }
#endif
            i_this->mBodyAction = ACTION_SEPARATION_BUNRI_DOUSA;
            i_this->mActionState = ACTION_STATE_SEPARATE_BUNRI_DOUSA_INIT;
        }
    }
    cLib_addCalc2(&actor->speedF, i_this->m490, 1.0f, 1.0f);
}

/* 000062D8-00008BAC       .text action_bunri_dousa__FP9bpw_class */
void action_bunri_dousa(bpw_class* i_this) {
    /* Nonmatching - weird issue with inlines */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    pw_class* childPoe;
    f32 fVar9;
    cXyz local_68;
    cXyz local_74;
    cXyz sp70;
    f32 f1;
    f32 f2;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = (camera_class*)dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    switch (i_this->mActionState) {
    case ACTION_STATE_SEPARATE_BUNRI_DOUSA_INIT: {
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        i_this->mKankyouHendouState = 3;
        i_this->mSomeCountdownTimers[5] = 0;
        i_this->mSomeCountdownTimers[0] = 0;
        i_this->mSomeCountdownTimers[1] = 0;
        i_this->mSomeCountdownTimers[2] = 0;
#if VERSION > VERSION_DEMO
        i_this->m47C = 0;
#endif
#if VERSION == VERSION_DEMO
        u32 uVar14;
        s32 i;
        cXyz local_58;
        csXyz pwAngle = actor->shape_angle;
        local_58 = actor->current.pos;
        int currRandomAngle;
        int pwSpreadAmount = (int)(65536.0f / actor->health);
        local_58.y = i_this->mAcch.GetGroundH() + 20.0f;
        i_this->m3E9 = 0;
        for (i = 0; i < 15; i++) {
            i_this->mChildPoeIds[i] = fpcM_ERROR_PROCESS_ID_e;
        }
        currRandomAngle = (int)cM_rndFX(32768.0f);
        uVar14 = (s16)cM_rndF(4.99f);
        u32 uVar2 = uVar14 << 9 | 0xFF000003;
        for (i = 0; i < actor->health; i++) {
            f32 maxPoeSpread = ((s16)pwSpreadAmount * 0.25f);
            i_this->mChildPoeIds[i] = fopAcM_createChild(PROC_PW, fopAcM_GetID(i_this), uVar2, &local_58, fopAcM_GetRoomNo(actor), &pwAngle);
            currRandomAngle += pwSpreadAmount;
            pwAngle.y = (s16)currRandomAngle;
            pwAngle.y += (int)cM_rndFX((f32)maxPoeSpread);
            uVar14++;
            if (uVar14 > 5) {
                uVar14 = 0;
            }
            uVar2 = uVar14 << 9 | 0xFF000003;
        }
        i_this->m47C = 0;
#endif
        anm_init(i_this, BPW_BCK_CORE1, DEMO_SELECT(REG11_F(0), 0.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mBodyAtSph.OffAtSPrmBit(cCcD_TgSPrm_Set_e);
        i_this->mBodyAtSph.ClrAtSet();
        i_this->mBodyCoSph.OffTgSetBit();
        i_this->mBodyCoSph.ClrCoSet();
        i_this->mBodyCoSph.ClrTgHit();
        actor->attention_info.flags = 0;
        i_this->m47A = 0x500;
        actor->gravity = 0.0f;
        actor->speed.setall(0.0f);
        actor->speedF = 0.0f;
        i_this->m3E6 = 0;
        i_this->m3E5 = 0;
        actor->scale.setall(0.0f);
        actor->current.pos = i_this->mBodyPos;
        i_this->mSomeCountdownTimers[0] = DEMO_SELECT(0x186, 0x1A4);
        i_this->mActionState++;
    }
    case ACTION_STATE_SEPARATE_BUNRI_DOUSA_EXECUTE: {
        s8 hpAmountToEndPhaseAt;
        switch (i_this->m3F6) {
        case 0:
            hpAmountToEndPhaseAt = 10;
            break;
        case 1:
            hpAmountToEndPhaseAt = 5;
            break;
        case 2:
            hpAmountToEndPhaseAt = 0;
            break;
        }
        if (actor->health <= 0) {
            if (dComIfGp_getStartStageName()[0] == 'X') {
                dComIfGs_onEventBit(dSv_event_flag_c::JALHALLA_TRIALS_CLEAR);
                dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0480);
                dLib_setNextStageBySclsNum(0, actor->current.roomNo);
                mDoAud_seStart(JA_SE_LK_B_BOSS_WARP, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            } else {
                fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
                i_this->mBodyCoSph.ClrCoSet();
                i_this->mBodyCoSph.OffTgSetBit();
                i_this->mBodyCoSph.ClrTgHit();
                i_this->mActionState = 0x78;
            }
            break;
        }
        if ((i_this->mSomeCountdownTimers[0] != 0) && (actor->health > hpAmountToEndPhaseAt)) {
            break;
        }
        i_this->mBodyCoSph.OnCoSetBit();
        fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
        i_this->mActionState++;
        // fallthrough
    }
    case 0x70:
        for (s32 i = 0; i < actor->health; i++) {
            childPoe = (pw_class*)fopAcM_SearchByID(i_this->mChildPoeIds[i]);
            if ((childPoe != NULL) && (0 < childPoe->health)) {
                childPoe->health = 0x14;
            }
        }
        i_this->m47E = 0;
        i_this->mActionState++;
    case 0x71:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            dComIfGp_event_onEventFlag(1);
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            break;
        }
        player->changeOriginalDemo();
        player->changeDemoMode(daPy_demo_c::DEMO_N_WAIT_e);
        anm_init(i_this, BPW_BCK_CORE1, DEMO_SELECT(REG11_F(0), 0.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m440 = 50.0f;
        i_this->m3E0 = 0;
        i_this->m480 = 0x96;
        i_this->mSomeCountdownTimers[2] = 0xf;
        i_this->m474 = 1;
        sp70.x = 0.0f;
        sp70.y = 0.0f;
        sp70.z = 1625.0f;
        player->setPlayerPosAndAngle(&sp70, fopAcM_searchActorAngleY(player, actor));
        i_this->mActionState++;
    case ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_INIT:
        i_this->m40C.x = 156.0f;
        i_this->m40C.y = 515.0f;
        i_this->m40C.z = 1001.0f;
        i_this->m418.x = 181.0f;
        i_this->m418.y = 603.0f;
        i_this->m418.z = 1196.0f;
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        if (i_this->mSomeCountdownTimers[2] != 0) {
            break;
        }
        actor->current.angle.y = fopAcM_searchPlayerAngleY(actor);
        actor->shape_angle.y = actor->current.angle.y;
        i_this->m476 = actor->shape_angle.y;
        cLib_addCalcAngleS2(&i_this->m47E, i_this->m480, 1, 0xf);
        cLib_addCalc2(&actor->scale.x, 1.0f, 1.0f, 0.1f);
        actor->scale.y = actor->scale.z = actor->scale.x;
        if ((i_this->m3E9 == 0) && (actor->scale.x > 0.9f)) {
            actor->scale.setall(1.0f);
            i_this->m3E9 = 1;
            i_this->mSomeCountdownTimers[5] = REG21_S(2) + 10;
            i_this->mSomeCountdownTimers[1] = 300;
            for (s32 i = 0; i < actor->health; i++) {
                childPoe = (pw_class*)fopAcM_SearchByID(i_this->mChildPoeIds[i]);
                if (childPoe != NULL) {
                    fopAcM_OnStatus(childPoe, fopAcStts_UNK4000_e);
                }
            }
        }
        if (i_this->m3F8 == 9) {
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, BPW_BCK_CORE1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            fopAcM_seStart(actor, JA_SE_OBJ_BPW_MASK_LAUGH, 0);
        }
        sp70.x = 0.0f;
        sp70.y = 0.0f;
        sp70.z = 1625.0f;
        player->setPlayerPosAndAngle(&sp70, fopAcM_searchActorAngleY(player, actor));
        if (i_this->m464 != 0) {
            anm_init(i_this, BPW_BCK_CORE_NIGE1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m464 = 0;
        }
        if ((i_this->mSomeCountdownTimers[1] == 1) || (i_this->m462 >= actor->health)) {
            anm_init(i_this, BPW_BCK_CORE_NIGE1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mSomeCountdownTimers[0] = 30;
            i_this->mActionState++;
        }
        i_this->m3AC.y = 140.0f;
        fuwafuwa_calc(i_this);
        break;
    case ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_GATHER:
        if (i_this->mSomeCountdownTimers[0] == 0) {
            if (REG20_S(1) == 0) {
                REG20_S(0) = 1;
            }
            if (REG20_S(0) == 0) {
                break;
            }
            REG20_S(0) = 0;
            anm_init(i_this, BPW_BCK_HUKKATU1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_seStart(actor, JA_SE_CM_BPW_MASK_TO_BPW, 0);
            i_this->mActionState++;
#if VERSION > VERSION_DEMO
            i_this->m43C = 0.0f;
#endif
        }
        break;
    case ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_GROW:
        fVar2 = std::fabsf(i_this->m40C.x - (REG20_F(12) + 152.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.08f);
        cLib_addCalc2(&i_this->m40C.x, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.y - (REG20_F(13) + 498.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.08f);
        cLib_addCalc2(&i_this->m40C.y, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.z - (REG20_F(14) + 983.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.08f);
        cLib_addCalc2(&i_this->m40C.z, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.x - (REG20_F(15) + 181.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.08f);
        cLib_addCalc2(&i_this->m418.x, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.y - (REG20_F(16) + 504.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.08f);
        cLib_addCalc2(&i_this->m418.y, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.z - (REG20_F(17) + 1196.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.08f);
        cLib_addCalc2(&i_this->m418.z, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        cLib_addCalc0(&i_this->m48C, 1.0f, 10.0f);
        cLib_addCalc2(&i_this->m3AC.y, 340.0f, 1.0f, 10.0f);
        if (i_this->mpMorf->isStop()) {
            if (REG20_S(1) == 0) {
                REG20_S(0) = 1;
            }
            if (REG20_S(0) == 0) {
                break;
            }
            REG20_S(0) = 0;
            anm_init(i_this, BPW_BCK_WAIT1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mSomeCountdownTimers[0] = DEMO_SELECT(REG11_F(10) + 20.0f, 0x14);
            i_this->mActionState++;
        }
        break;
    case ACTION_STATE_SEPARATE_BUNRI_DOUSA_END_FINISH:
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        dComIfGp_getVibration().StopQuake(0x20);
        camera->mCamera.Reset(i_this->m40C, i_this->m418);
        camera->mCamera.Start();
        camera->mCamera.SetTrimSize(0);
        player->cancelOriginalDemo();
        dComIfGp_event_reset();
        next_status_clear(i_this, 1);
        next_att_wait_check(i_this);
        if (actor->health <= 5) {
            i_this->m3F6 = 2;
        } else if (actor->health <= 10) {
            i_this->m3F6 = 1;
        }
        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
        break;
    case 0x78:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            dComIfGp_event_onEventFlag(1);
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            break;
        }
        i_this->mSomeCountdownTimers[5] = 3;
        i_this->m3F6 = 3;
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        actor->gravity = -3.0f;
        actor->speed.setall(0.0f);
        actor->speedF = 0.0f;
        actor->current.pos.y = i_this->mBodyPos.y + 200.0f + REG18_F(0);
        i_this->m48C = REG18_F(1);
        i_this->m3E6 = 0;
        i_this->m3E5 = 0;
        actor->scale.setall(0.0f);
        anm_init(i_this, BPW_BCK_CORE1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        if (i_this->m3FC != fpcM_ERROR_PROCESS_ID_e) {
            fopAc_ac_c* i_actor = fopAcM_SearchByID(i_this->m3FC);
            fopAcM_createDisappear(i_actor, &i_actor->current.pos, 5, daDisItem_NONE3_e, 0xFF);
            fopAcM_delete(i_actor);
        }
        for (s32 i = 0; i < actor->max_health; i++) {
            childPoe = (pw_class*)fopAcM_SearchByID(i_this->mChildPoeIds[i]);
            if ((childPoe != NULL) && (childPoe->m344 != 0)) {
                fopAcM_OnStatus(childPoe, fopAcStts_UNK4000_e);
                i_this->m462 = i;
                i_this->m424 = childPoe->current.pos;
                i_this->m464 = fopAcM_searchPlayerAngleY(childPoe);
            }
        }
        i_this->m47E = 0;
        i_this->m480 = 0x96;
        player->changeOriginalDemo();
        player->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        mDoAud_bgmStop(30);
        i_this->m474 = 1;
        i_this->mSomeCountdownTimers[0] = REG20_F(0) + 135.0f;
        i_this->mActionState++;
        childPoe = (pw_class*)fopAcM_SearchByID(i_this->mChildPoeIds[i_this->m462]);
        if (childPoe != NULL) {
#if VERSION == VERSION_DEMO
            i_this->m424 = childPoe->current.pos;
            i_this->m464 = fopAcM_searchPlayerAngleY(childPoe);
#else
            i_this->m40C = childPoe->current.pos;
#endif
        }
    case 0x79:
#if VERSION > VERSION_DEMO
        childPoe = (pw_class*)fopAcM_SearchByID(i_this->mChildPoeIds[i_this->m462]);
        if (childPoe != NULL) {
            i_this->m424 = childPoe->current.pos;
            i_this->m464 = fopAcM_searchPlayerAngleY(childPoe);
        }
#endif
        i_this->m440 = 50.0f;
#if VERSION == VERSION_DEMO
        i_this->m40C = i_this->m424;
        i_this->m40C.y += 150.0f + REG12_F(17);
#else
        i_this->m40C.x = i_this->m424.x;
        i_this->m40C.z = i_this->m424.z;
        cLib_addCalc2(&i_this->m40C.y, i_this->m424.y + 150.0f + REG12_F(17), 0.1f, 10.0f);
#endif
        cMtx_YrotS(*calc_mtx, i_this->m464);
        local_68.x = 0.0f;
        local_68.y = 0.0f;
        local_68.z = 800.0f;
        MtxPosition(&local_68, &local_74);
#if VERSION == VERSION_DEMO
        local_74 += i_this->m424;
        i_this->m418.x = local_74.x;
        i_this->m418.y = local_74.y + 100.0f;
        i_this->m418.z = local_74.z;
#else
        local_74.x += i_this->m424.x;
        local_74.z += i_this->m424.z;
        local_74.y += i_this->m424.y * 0.3f;
        i_this->m418.x = local_74.x;
        i_this->m418.y = local_74.y + 100.0f;
        i_this->m418.z = local_74.z;
#endif
        if (i_this->mSomeCountdownTimers[0] == 0) {
            i_this->mSomeCountdownTimers[0] = REG20_F(1) + 25.0f;
            if (REG20_S(1) == 0) {
                REG20_S(0) = 1;
            }
            if (REG20_S(0) == 0) {
                break;
            }
            REG20_S(0) = 0;
            player->changeDemoMode(daPy_demo_c::DEMO_N_WAIT_e);
            sp70.x = -36.0f;
            sp70.y = player->current.pos.y;
            sp70.z = -777.0f;
            player->setPlayerPosAndAngle(&sp70, (s16)cM_atan2s(player->current.pos.x - i_this->m424.x, player->current.pos.z - i_this->m424.z));
            i_this->mActionState++;
        }
        break;
    case 0x7a:
        actor->shape_angle.y = fopAcM_searchPlayerAngleY(actor);
        actor->current.angle.y = actor->shape_angle.y;
        i_this->m476 = actor->shape_angle.y;
        cLib_addCalc2(&i_this->m440, REG20_F(2) + 50.0f, 1.0f, 0.5f);
        i_this->m40C.x = -484.0f;
        i_this->m40C.y = 628.0f;
        i_this->m40C.z = -1495.0f;
        i_this->m418.x = -527.0f;
        i_this->m418.y = 698.0f;
        i_this->m418.z = -1645.0f;
        sp70.x = -36.0f;
        sp70.y = player->current.pos.y;
        sp70.z = -777.0f;
        player->setPlayerPosAndAngle(&sp70, fopAcM_searchPlayerAngleY(actor) + 0x8000);
        if (i_this->mSomeCountdownTimers[0] != 0) {
            if (i_this->mSomeCountdownTimers[0] == 1) {
                fopAcM_seStart(actor, JA_SE_OBJ_BPW_MASK_APPEAR, 0);
            }
            break;
        }
        player->changeDemoMode(daPy_demo_c::DEMO_S_SURP_e);
        cLib_addCalc2(&actor->scale.x, 1.0f, 1.0f, 0.1f);
        cLib_addCalcAngleS2(&i_this->m47E, i_this->m480, 1, 0xf);
        fVar9 = actor->scale.x;
        actor->scale.z = fVar9;
        actor->scale.y = fVar9;
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        if (actor->scale.x < 0.9f) {
            break;
        }
        actor->scale.setall(1.0f);
        i_this->mSomeCountdownTimers[0] = REG20_F(9) + 10.0f;
        i_this->mSomeCountdownTimers[1] = REG20_F(10) + 100.0f;
        i_this->mSomeCountdownTimers[4] = REG12_F(12) + 30.0f;
        i_this->mActionState++;
#if VERSION > VERSION_DEMO
        i_this->m43C = 0.0f;
#endif
        // Fall-through
    case 0x7b:
        if (i_this->mSomeCountdownTimers[0] != 0) {
            i_this->mSomeCountdownTimers[1] = REG20_F(10) + 100.0f;
            i_this->mSomeCountdownTimers[4] = REG12_F(12) + 30.0f;
            break;
        }
        cLib_addCalc2(&i_this->m440, REG20_F(11) + 50.0f, 1.0f, 0.5f);
        fVar2 = std::fabsf(i_this->m40C.x - (REG20_F(12) + -114.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.02f);
        cLib_addCalc2(&i_this->m40C.x, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.y - (REG20_F(13) + 95.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.02f);
        cLib_addCalc2(&i_this->m40C.y, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.z - (REG20_F(14) + -293.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.02f);
        cLib_addCalc2(&i_this->m40C.z, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.x - (REG20_F(15) + -169.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.02f);
        cLib_addCalc2(&i_this->m418.x, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.y - (REG20_F(16) + 98.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.02f);
        cLib_addCalc2(&i_this->m418.y, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.z - (REG20_F(17) + -462.0f));
        fVar9 = fVar2 * (REG20_F(18) + 0.02f);
        cLib_addCalc2(&i_this->m418.z, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        if (i_this->m3F8 == 0x1b) {
            if (i_this->mpMorf->checkFrame(1.0f)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LOOK_RIGHT, 0);
            }
            if (i_this->mpMorf->checkFrame(41.0f)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LOOK_LEFT, 0);
            }
            if (i_this->mpMorf->checkFrame(76.0f)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_SURPRISE, 0);
            }
        }
        if (i_this->mSomeCountdownTimers[4] == 1) {
            anm_init(i_this, BPW_BCK_KYORO_GARN1, 8.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        if (i_this->mSomeCountdownTimers[1] != 0) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->mActionState++;
        // fallthrough
    case 0x7c:
        if (i_this->m3F8 == 0x1b) {
            if (i_this->mpMorf->checkFrame(1.0f)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LOOK_RIGHT, 0);
            }
            if (i_this->mpMorf->checkFrame(41.0f)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LOOK_LEFT, 0);
            }
            if (i_this->mpMorf->checkFrame(76.0f)) {
                fopAcM_monsSeStart(actor, JA_SE_CV_BPW_SURPRISE, 0);
            }
        }
        if (!i_this->mpMorf->isStop()) {
            break;
        }
        i_this->mSomeCountdownTimers[0] = REG19_F(0) + 60.0f;
        i_this->mActionState++;
        // fallthrough
    case 0x7d:
        cLib_addCalc2(&i_this->m440, REG19_F(1) + 50.0f, 1.0f, 0.5f);
        i_this->m40C.x = 61.0f;
        i_this->m40C.y = 125.0f;
        i_this->m40C.z = -159.0f;
        i_this->m418.x = -146.0f;
        i_this->m418.y = 39.0f;
        i_this->m418.z = -965.0f;
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        anm_init(i_this, BPW_BCK_CORE_NIGE1, 8.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mSomeCountdownTimers[0] = 4;
        i_this->mActionState++;
#if VERSION > VERSION_DEMO
        i_this->m43C = 0.0f;
#endif
        // fallthrough
    case 0x7e: {
        if (i_this->mSomeCountdownTimers[0] == 0) {
            fopAcM_seStart(actor, JA_SE_CM_BPW_MASK_RUN_AWAY, 0);
        }
        cLib_addCalc2(&i_this->m440, REG19_F(9) + 50.0f, 1.0f, 0.5f);
        fVar2 = std::fabsf(i_this->m40C.x - (REG19_F(10) + -471.0f));
        fVar9 = fVar2 * (REG19_F(12) + 0.05f);
        cLib_addCalc2(&i_this->m40C.x, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.y - (REG19_F(10) + 120.0f));
        fVar9 = fVar2 * (REG19_F(12) + 0.05f);
        cLib_addCalc2(&i_this->m40C.y, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.z - (REG19_F(11) + -498.0f));
        fVar9 = fVar2 * (REG19_F(12) + 0.05f);
        cLib_addCalc2(&i_this->m40C.z, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.x - (REG20_F(15) + 115.0f));
        fVar9 = fVar2 * (REG19_F(12) + 0.05f);
        cLib_addCalc2(&i_this->m418.x, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.y - (REG20_F(16) + 58.0f));
        fVar9 = fVar2 * (REG19_F(12) + 0.05f);
        cLib_addCalc2(&i_this->m418.y, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.z - (REG20_F(17) + -1062.0f));
        fVar9 = fVar2 * (REG19_F(12) + 0.05f);
        cLib_addCalc2(&i_this->m418.z, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        cLib_addCalc2(&actor->current.pos.x, -1130.0f, 1.0f, REG19_F(13) + 20.0f);
        cLib_addCalc2(&actor->current.pos.z, 30.0f, 1.0f, REG19_F(13) + 20.0f);
        f32 dVar7 = actor->current.pos.x - -1130.0f;
        f32 dVar8 = actor->current.pos.z - 30.0f;
        i_this->m476 = cM_atan2s(dVar7, dVar8) + 0x8000;
        sp70.x = -36.0f;
        sp70.y = player->current.pos.y;
        sp70.z = -777.0f;
        player->setPlayerPosAndAngle(&sp70, fopAcM_searchPlayerAngleY(actor) + 0x8000);
        if (std::sqrtf(SQUARE(dVar7) + SQUARE(dVar8)) < 5.0f) {
            actor->gravity = 0.0f;
            actor->speed.setall(0.0f);
            actor->speedF = 0.0f;
            cLib_addCalcAngleS2(&i_this->m476, -0x8000, 1, 0x2000);
            if (REG20_S(1) == 0) {
                REG20_S(0) = 1;
            }
            if (REG20_S(0) == 0) {
                break;
            }
            REG20_S(0) = 0;
            i_this->m47C = 0;
            i_this->mSomeCountdownTimers[0] = REG18_F(5) + 63.0f;
            i_this->mSomeCountdownTimers[1] = REG18_F(6) + 75.0f;
            mDoAud_bgmStreamPrepare(JA_STRM_BOSS_CLEAR);
            i_this->mActionState++;
#if VERSION > VERSION_DEMO
            i_this->m43C = 0.0f;
#endif
        }
        break;
    }
    case 0x7f:
        if (i_this->mSomeCountdownTimers[0] != 0) {
            fopAcM_seStart(actor, JA_SE_CM_BPW_MASK_RUN_AWAY, 0);
        }
        if (i_this->mSomeCountdownTimers[1] == 1) {
            mDoAud_bgmStreamPlay();
        }
        i_this->m47C += REG18_F(2) + 700.0f;
        i_this->m3AC.x = (REG18_F(3) + 30.0f) * cM_ssin(i_this->m47C);
        i_this->m3AC.z = (REG18_F(4) + 30.0f) * cM_ssin(i_this->m47C);
        cLib_addCalcAngleS2(&i_this->m476, -0x8000, 1, 0x2000);
        actor->speed.y = REG19_F(14) + 30.0f;
        cLib_addCalc2(&i_this->m440, REG19_F(15) + 50.0f, 1.0f, 0.5f);
        fVar2 = std::fabsf(i_this->m40C.x - (REG19_F(16) + -538.0f));
        fVar9 = fVar2 * (REG19_F(19) + 0.04f);
        cLib_addCalc2(&i_this->m40C.x, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.y - (REG19_F(17) + 748.0f));
        fVar9 = fVar2 * (REG19_F(19) + 0.04f);
        cLib_addCalc2(&i_this->m40C.y, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.z - (REG19_F(18) + -567.0f));
        fVar9 = fVar2 * (REG19_F(19) + 0.04f);
        cLib_addCalc2(&i_this->m40C.z, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        if (i_this->mSomeCountdownTimers[0] == 1) {
            i_this->m3F6 = 4;
            fopAcM_seStart(actor, JA_SE_OBJ_BPW_LIGHT_ON, 0);
            i_this->mKankyouHendouState = 3;
            i_this->mSomeCountdownTimers[5] = 0;
            anm_init(i_this, BPW_BCK_GATAGATA1, REG12_F(10) + 8.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        if (actor->current.pos.y > 2000.0f) {
            actor->speedF = 0.0f;
            actor->speed.setall(0.0f);
            if (REG20_S(1) == 0) {
                REG20_S(0) = 1;
            }
            if (REG20_S(0) == 0) {
                break;
            }
            REG20_S(0) = 0;
            i_this->m3F6 = 4;
            fopAcM_monsSeStart(actor, JA_SE_CV_BPW_DIE, 0);
            i_this->mSomeCountdownTimers[0] = REG18_F(8) + 40.0f;
            i_this->mActionState++;
        }
        break;
    case 0x80:
        if (i_this->mSomeCountdownTimers[1] == 1) {
            mDoAud_bgmStreamPlay();
        }
        if (i_this->mSomeCountdownTimers[0] != 0)
            break;
        i_this->m480 = 0xFF;
        i_this->m3AC.setall(0.0f);
        i_this->mActionState++;
        // fallthrough
    case 0x81:
        if (i_this->mSomeCountdownTimers[1] == 1) {
            mDoAud_bgmStreamPlay();
        }
        cLib_addCalcAngleS2(&i_this->m47E, i_this->m480, 1, 5);
        cLib_addCalc2(&i_this->m440, REG18_F(9) + 50.0f, 1.0f, 0.5f);
        i_this->m40C.x = -1030.0f;
        i_this->m40C.y = 2017.0f;
        i_this->m40C.z = 119.0f;
        i_this->m418.x = -1332.0f;
        i_this->m418.y = 2722.0f;
        i_this->m418.z = -153.0f;
        actor->shape_angle.y = -0x483f;
        i_this->m476 = -0x483f;
        actor->shape_angle.x = -0x2337;
        actor->shape_angle.z = 0x3e9;
        if (i_this->m47E < 0xFE) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->m3E0 = 1;
        i_this->m47E = 0xFF;
        i_this->mpMorf->setPlaySpeed(0.0f);
        i_this->mSomeCountdownTimers[0] = REG18_F(17) + 40.0f;
        i_this->mActionState++;
        // fallthrough
    case 0x82:
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        i_this->mSomeCountdownTimers[0] = REG18_F(18) + 20.0f;
        actor->gravity = -1.0f;
        i_this->mActionState++;
        // fallthrough
    case 0x83:
        cLib_addCalcAngleS2(&actor->shape_angle.x, REG18_F(19) + 49152.0f, 1, 0x300);
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        actor->gravity = -3.0f;
        i_this->mActionState++;
        // fallthrough
    case 0x84:
        cLib_addCalc2(&i_this->m440, REG6_F(7) + 50.0f, 1.0f, 0.5f);
        i_this->m40C.x = -893.0f;
        i_this->m40C.y = 1874.0f;
        i_this->m40C.z = 66.0f;
        i_this->m418.x = 142.0f;
        i_this->m418.y = 68.0f;
        i_this->m418.z = -1348.0f;
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
        i_this->mActionState++;
#if VERSION > VERSION_DEMO
        i_this->m43C = 0.0f;
#endif
        // fallthrough
    case 0x85:
        cLib_addCalcAngleS2(&actor->shape_angle.x, REG18_F(19) + 49152.0f, 1, 0x300);
        cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 1, 0x300);
        cLib_addCalc2(&i_this->m440, REG6_F(7) + 50.0f, 1.0f, 0.5f);
        fVar2 = std::fabsf(i_this->m40C.x - (REG6_F(8) + -1352.0f));
        fVar9 = fVar2 * (REG6_F(6) + 0.05f);
        cLib_addCalc2(&i_this->m40C.x, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.y - (REG6_F(9) + 174.0f));
        fVar9 = fVar2 * (REG6_F(6) + 0.05f);
        cLib_addCalc2(&i_this->m40C.y, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.z - (REG6_F(10) + 680.0f));
        fVar9 = fVar2 * (REG6_F(6) + 0.05f);
        cLib_addCalc2(&i_this->m40C.z, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        cLib_addCalc0(&i_this->m3AC.y, 1.0f, 3.0f);
        cLib_addCalc2(&i_this->m48C, -120.0f, 1.0f, 3.0f);
        sp70.x = -36.0f;
        sp70.y = player->current.pos.y;
        sp70.z = -777.0f;
        player->setPlayerPosAndAngle(&sp70, fopAcM_searchPlayerAngleY(actor) + 0x8000);
        if (REG6_F(19) + (i_this->mAcch.GetGroundH() + 1350.0f) < actor->current.pos.y) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->mActionState++;
#if VERSION > VERSION_DEMO
        i_this->m43C = 0.0f;
#endif
        // fallthrough
    case 0x86: {
        cLib_addCalc2(&i_this->m440, REG6_F(11) + 50.0f, 1.0f, 0.5f);
        fVar2 = std::fabsf(i_this->m40C.x - (REG6_F(12) + -2340.0f));
        fVar9 = fVar2 * (REG6_F(18) + 0.1f);
        cLib_addCalc2(&i_this->m40C.x, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.y - (REG6_F(13) + 36.0f));
        fVar9 = fVar2 * (REG6_F(18) + 0.1f);
        cLib_addCalc2(&i_this->m40C.y, DEMO_SELECT(fVar2, REG12_F(13) + 186.0f), DEMO_SELECT(1.0f, 0.5f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m40C.z - (REG6_F(14) + 1442.0f));
        fVar9 = fVar2 * (REG6_F(18) + 0.1f);
        cLib_addCalc2(&i_this->m40C.z, fVar2, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.x - (REG6_F(15) + -744.0f));
        fVar9 = fVar2 * (REG6_F(18) + 0.1f);
        cLib_addCalc2(&i_this->m418.x, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.y - (REG6_F(16) + 74.0f));
        fVar9 = fVar2 * (REG6_F(18) + 0.1f);
        cLib_addCalc2(&i_this->m418.y, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
        fVar2 = std::fabsf(i_this->m418.z - (REG6_F(17) + -432.0f));
        fVar9 = fVar2 * (REG6_F(18) + 0.1f);
        cLib_addCalc2(&i_this->m418.z, fVar2, 1.0f, DEMO_SELECT(fVar9, fVar9 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        cLib_addCalc0(&i_this->m3AC.y, 1.0f, 3.0f);
        cLib_addCalc2(&i_this->m48C, -120.0f, 1.0f, 3.0f);
        if (REG12_F(14) + i_this->mAcch.GetGroundH() < actor->current.pos.y) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWBREAKMASK00, &actor->current.pos, &actor->shape_angle);
        if (emitter != NULL) {
            emitter->setGlobalPrmColor(dKy_getEnvlight().mBG0_K0.r, dKy_getEnvlight().mBG0_K0.g, dKy_getEnvlight().mBG0_K0.b);
        }
        fopAcM_seStart(actor, JA_SE_CM_BOSS_EXPLODE, 0);
        sp70 = actor->current.pos;
        sp70.y += REG8_F(5) + 80.0f;
        fopAcM_createDisappear(actor, &sp70, 0xF, daDisItem_HEART_CONTAINER_e, 0xFF);
        fopAcM_seStart(actor, JA_SE_CM_BPW_MASK_BREAK, 0);
        actor->scale.setall(0.0f);
        i_this->mActionState++;
        i_this->mSomeCountdownTimers[0] = REG12_F(16) + 120.0f;
        // fallthrough
    }
    case 0x87: {
        if (i_this->mSomeCountdownTimers[0] != 0) {
#if VERSION > VERSION_DEMO
            cLib_addCalc2(&i_this->m40C.y, REG12_F(13) + 186.0f, 0.3f, REG12_F(14) + 100.0f);
#endif
            break;
        }
        f1 = player->current.pos.x - i_this->mBodyPos.x;
        f2 = player->current.pos.z - i_this->mBodyPos.z;
        sp70.x = -36.0f;
        sp70.y = player->current.pos.y;
        sp70.z = -777.0f;
        player->setPlayerPosAndAngle(&sp70, cM_atan2s(f1, f2) + 0x8000);
        i_this->m40C.setall(0.0f);
        i_this->m3F0 = REG9_F(1) + 1400.0f;
        i_this->m3F4 = REG9_F(2) + -15000.0f;
        i_this->m418.x = (f32)(i_this->m3F0 * cM_ssin(i_this->m3F4));
        i_this->m418.y = REG9_F(3) + 900.0f;
        i_this->m418.z = (f32)(i_this->m3F0 * cM_scos(i_this->m3F4));
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->m462 = 0;
        if (REG0_S(3) == 0) {
            dComIfGs_onStageBossEnemy();
        }
        i_this->mSomeCountdownTimers[1] = REG9_F(4) + 80.0f;
        i_this->mSomeCountdownTimers[2] = REG9_F(5) + 470.0f;
        i_this->mSomeCountdownTimers[9] = 0;
        i_this->mActionState++;
        // fallthrough
    }
    case 0x88: {
        f1 = player->current.pos.x - i_this->mBodyPos.x;
        f2 = player->current.pos.z - i_this->mBodyPos.z;
        sp70.x = -36.0f;
        sp70.y = player->current.pos.y;
        sp70.z = -777.0f;
        player->setPlayerPosAndAngle(&sp70, cM_atan2s(f1, f2) + 0x8000);
        if (i_this->mSomeCountdownTimers[9] == 1) {
            i_this->m3EC = 0.0f;
            i_this->mKankyouHendouState = 6;
        }
        if (i_this->mSomeCountdownTimers[2] != 0) {
            if (i_this->mSomeCountdownTimers[1] == 1) {
                fopAcM_createWarpFlower(&i_this->mBodyPos, 0, fopAcM_GetRoomNo(actor), 0);
                i_this->mSomeCountdownTimers[9] = REG6_S(5) + 30;
            }
            cLib_addCalc2(&i_this->m440, REG9_F(6) + 50.0f, 1.0f, 0.5f);
            i_this->m3F4 += (s32)(REG9_F(7) + 33.0f);
            if (0 < i_this->m3F4) {
                i_this->m3F4 = 0;
            }
            cLib_addCalc2(&i_this->m3F0, REG9_F(8) + 600.0f, 1.0f, REG9_F(9) + 2.0f);
            i_this->m418.x = (f32)(i_this->m3F0 * cM_ssin(i_this->m3F4));
            cLib_addCalc2(&i_this->m418.y, REG9_F(10) + 900.0f, 1.0f, REG9_F(11) + 10.0f);
            i_this->m418.z = (f32)(i_this->m3F0 * cM_scos(i_this->m3F4));
            break;
        }
        fVar2 = 0.0f;
        if (REG9_F(13) != fVar2) {
            i_this->mActionState = 0x87;
            i_this->mSomeCountdownTimers[0] = 0;
            break;
        }
        if (REG9_F(12) != fVar2) {
            i_this->mActionState = 0x87;
            REG9_F(12) = 0.0f;
            i_this->mSomeCountdownTimers[0] = 0;
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        dComIfGp_getVibration().StopQuake(0x20);
        camera->mCamera.Reset(i_this->m40C, i_this->m418);
        camera->mCamera.Start();
        camera->mCamera.SetTrimSize(0);
        player->cancelOriginalDemo();
        dComIfGp_event_reset();
        fopAcM_delete(actor);
        break;
    }
    }
    if (i_this->mActionState >= 0x78) {
        i_this->m3AC.y = 100.0f;
        i_this->m498 = 0.0f;
        i_this->m49C = 160.0f;
    }
    if (i_this->m474 != 0) {
        camera->mCamera.Set(i_this->m40C, i_this->m418, i_this->m440, 0);
    }
}

/* 00008D3C-0000A064       .text action_start_demo__FP9bpw_class */
void action_start_demo(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    switch (i_this->mActionState) {
    case 200:
        actor->scale.setall(0.0f);
        i_this->m47E = 0;
        i_this->mActionState++;
    case 0xc9:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            dComIfGp_event_onEventFlag(1);
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            break;
        } else {
            player->changeOriginalDemo();
            player->changeDemoMode(daPy_demo_c::DEMO_S_SURP_e);
            i_this->m3AC.y = 140.0f;
            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);
            i_this->m440 = REG6_F(0) + 55.0f;
            i_this->mSomeCountdownTimers[0] = (s16)(int)(REG9_F(0) + 40.0f);
            anm_init(i_this, BPW_BCK_CORE1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mActionState++;
        }
        // Fall-through
    case 0xca:
        i_this->m40C.x = 72.0f;
        i_this->m40C.y = 103.0f;
        i_this->m40C.z = 1618.0f;
        i_this->m418.x = 89.0f;
        i_this->m418.y = 108.0f;
        i_this->m418.z = 1788.0f;
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->mSomeCountdownTimers[0] = (s16)(int)(REG9_F(1) + 50.0f);
        i_this->mActionState++;
        // Fall-through
    case 0xcb:
        i_this->m440 = REG6_F(1) + 50.0f;
        i_this->m40C.x = 1646.0f;
        i_this->m40C.y = 1215.0f;
        i_this->m40C.z = -72.0f;
        i_this->m418.x = 1767.0f;
        i_this->m418.y = 1321.0f;
        i_this->m418.z = -129.0f;
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->mSomeCountdownTimers[0] = (s16)(int)(REG9_F(2) + 40.0f);
        i_this->mSomeCountdownTimers[1] = (s16)(int)(REG9_F(3) + 20.0f);
        i_this->mActionState++;
        // Fall-through
    case 0xcc:
        if (i_this->mSomeCountdownTimers[1] == 1) {
            i_this->m3EA = 1;
            mDoAud_bgmStreamPlay();
        }
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        i_this->mSomeCountdownTimers[0] = (s16)(int)(REG9_F(4) + 38.0f);
        i_this->mSomeCountdownTimers[1] = (s16)(int)(REG9_F(5) + 28.0f);
        i_this->mActionState++;
        // Fall-through
    case 0xcd:
        i_this->m440 = REG6_F(2) + 55.0f;
        i_this->m40C.x = 72.0f;
        i_this->m40C.y = 103.0f;
        i_this->m40C.z = 1618.0f;
        i_this->m418.x = 89.0f;
        i_this->m418.y = 108.0f;
        i_this->m418.z = 1788.0f;
        if (i_this->mSomeCountdownTimers[1] == 0) {
            i_this->m3EA = 2;
        }
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->mSomeCountdownTimers[0] = (s16)(int)(REG18_F(0) + 40.0f);
        i_this->mSomeCountdownTimers[1] = (s16)(int)(REG18_F(1) + 110.0f);
        i_this->mSomeCountdownTimers[2] = (s16)(int)(REG18_F(11) + 20.0f);
        i_this->mActionState++;
#if VERSION > VERSION_DEMO
        i_this->m43C = 0.0f;
#endif
        // Fall-through
    case 0xce:
        if (i_this->mSomeCountdownTimers[2] == 1) {
            i_this->m3EA = 3;
        }
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        f32 f3;
        f3 = std::fabsf(i_this->m440 - (REG6_F(3) + 55.0f));
        f3 *= REG18_F(2) + 0.05f;
        cLib_addCalc2(&i_this->m440, REG6_F(3) + 55.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.x);
        f3 *= REG18_F(2) + 0.05f;
        cLib_addCalc2(&i_this->m40C.x, 0.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.y - 233.0f);
        f3 *= REG18_F(2) + 0.05f;
        cLib_addCalc2(&i_this->m40C.y, 233.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.z - 552.0f);
        f3 *= REG18_F(2) + 0.05f;
        cLib_addCalc2(&i_this->m40C.z, 552.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.x);
        f3 *= REG18_F(2) + 0.05f;
        cLib_addCalc2(&i_this->m418.x, 0.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.y - 270.0f);
        f3 *= REG18_F(2) + 0.05f;
        cLib_addCalc2(&i_this->m418.y, 270.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.z - 722.0f);
        f3 *= REG18_F(2) + 0.05f;
        cLib_addCalc2(&i_this->m418.z, 722.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        i_this->m3EA = 4;
        if (i_this->mSomeCountdownTimers[1] != 0) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->m3EA = 5;
        i_this->mSomeCountdownTimers[0] = (s16)(int)(REG18_F(3) + 30.0f);
        i_this->m480 = 0x96;
        fopAcM_seStart(actor, JA_SE_OBJ_BPW_MASK_APPEAR, 0);
        i_this->mActionState++;
        // Fall-through
    case 0xcf:
        cLib_addCalcAngleS2(&i_this->m47E, i_this->m480, 1, 5);
        cLib_addCalc2(&actor->scale.x, 1.0f, 1.0f, 0.1f);
        fVar1 = actor->scale.x;
        actor->scale.z = fVar1;
        actor->scale.y = fVar1;
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        i_this->m3EA = 6;
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->mSomeCountdownTimers[5] = REG21_S(2) + 10;
        i_this->mActionState++;
        break;
    case 0xd0:
        if (i_this->m3F8 == 9) {
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, BPW_BCK_CORE1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            cLib_addCalc2(&i_this->m3AC.y, REG18_F(12) + 100.0f, 1.0f, REG18_F(13) + 10.0f);
            fopAcM_seStart(actor, JA_SE_OBJ_BPW_MASK_LAUGH, 0);
        } else {
            cLib_addCalc2(&i_this->m3AC.y, 140.0f, 1.0f, REG18_F(13) + 10.0f);
        }
        if (i_this->m464 != 0) {
            anm_init(i_this, BPW_BCK_CORE_NIGE1, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m464 = 0;
        }
        if (i_this->m462 < 0xf)
            break;
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0)
            break;
        REG20_S(0) = 0;
        i_this->mSomeCountdownTimers[0] = (s16)(int)(REG18_F(4) + 30.0f);
        i_this->mSomeCountdownTimers[1] = (s16)(int)(REG18_F(5) + 55.0f);
        i_this->mActionState++;
#if VERSION > VERSION_DEMO
        i_this->m43C = 0.0f;
#endif
    case 0xd1: {
        if (i_this->mSomeCountdownTimers[1] != 0) {
            break;
        }
        f32 f3;
        f3 = std::fabsf(i_this->m440 - (REG6_F(4) + 65.0f));
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m440, REG6_F(4) + 65.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.x - 281.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m40C.x, 281.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.y - 93.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m40C.y, 93.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.z - 725.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m40C.z, 725.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.x - 336.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m418.x, 336.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.y - 30.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m418.y, 30.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.z - 877.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m418.z, 877.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        anm_init(i_this, BPW_BCK_OPENING1, REG18_F(7) + 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        bpw_class* lantern = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
        if (lantern != NULL) {
            anm_init(lantern, BPW_BCK_OPENING_KAN1, REG18_F(7) + 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        i_this->mFire1DousaPos = i_this->m3B8;
        i_this->mFire1DousaRot = actor->shape_angle;
#if VERSION == VERSION_DEMO
        i_this->m540_demo =
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWOPENINGSMOKE00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->m554);
#else
        if (i_this->m554.getEmitter() == NULL) {
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWOPENINGSMOKE00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->m554);
        }
#endif
        fopAcM_seStart(actor, JA_SE_CM_BPW_MASK_TO_BPW, 0);
        i_this->mActionState++;
        // Fall-through
    }
    case 0xd2: {
        if (DEMO_SELECT(i_this->m540_demo, i_this->m554.getEmitter()) != NULL) {
            i_this->mFire1DousaPos = i_this->m3B8;
            i_this->mFire1DousaRot = actor->shape_angle;
        }
        f32 f3;
        f3 = std::fabsf(i_this->m440 - (REG6_F(4) + 65.0f));
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m440, REG6_F(4) + 65.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.x - 281.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m40C.x, 281.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.y - 93.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m40C.y, 93.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m40C.z - 725.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m40C.z, 725.0f, DEMO_SELECT(1.0f, 0.1f), DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.x - 336.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m418.x, 336.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.y - 30.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m418.y, 30.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
        f3 = std::fabsf(i_this->m418.z - 877.0f);
        f3 *= REG18_F(8) + 0.08f;
        cLib_addCalc2(&i_this->m418.z, 877.0f, 1.0f, DEMO_SELECT(f3, f3 * i_this->m43C));
#if VERSION > VERSION_DEMO
        cLib_addCalc2(&i_this->m43C, 1.0f, 1.0f, 0.04f);
#endif
        cLib_addCalc2(&i_this->m3AC.y, 340.0f, 1.0f, 5.0f);
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        if (!i_this->mpMorf->isStop()) {
            break;
        }
#if VERSION == VERSION_DEMO
        if (i_this->m540_demo != NULL) {
            i_this->m540_demo->becomeInvalidEmitter();
            i_this->m554.remove();
            i_this->m540_demo = NULL;
        }
#else
        i_this->m554.remove();
#endif
        i_this->mSomeCountdownTimers[0] = (s16)(int)(REG6_F(5) + 40.0f);
        anm_init(i_this, BPW_BCK_OPENING2, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        bpw_class* lantern = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
        if (lantern != NULL) {
            anm_init(lantern, BPW_BCK_OPENING_KAN2, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        i_this->mActionState++;
        // Fall-through
    }
    case 0xd3:
        if (i_this->mSomeCountdownTimers[0] != 0) {
            break;
        }
        if (REG20_S(1) == 0) {
            REG20_S(0) = 1;
        }
        if (REG20_S(0) == 0) {
            break;
        }
        REG20_S(0) = 0;
        i_this->mActionState++;
        // Fall-through
    case 0xd4:
        if (i_this->mSomeCountdownTimers[0] == 0) {
            dComIfGp_getVibration().StopQuake(0x20);
            bpw_class* lantern = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
            if (lantern != NULL) {
                anm_init(lantern, BPW_BCK_KAN_DEFAULT1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
            i_this->mSomeCountdownTimers[1] = 0;
            i_this->m3F6 = 4;
            light_on_off(i_this);
            camera->mCamera.Reset(i_this->m40C, i_this->m418);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
            player->cancelOriginalDemo();
            dComIfGp_event_reset();
            mDoAud_bgmStart(JA_BGM_BIG_POW);
            dComIfGs_onStageBossDemo();
            i_this->m3F6 = 0;
            fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
            i_this->mBodyAction = ACTION_MOVE_DOUSA;
            i_this->mActionState = 0;
        }
    default:
        break;
    }
    if ((i_this->m3F8 == 0x1f) && (i_this->mpMorf->checkFrame(170.0f))) {
        fopAcM_monsSeStart(actor, JA_SE_CV_BPW_LAUGH_ENTER, 0);
    }
    if (((i_this->m3F8 == 0x1f) && (i_this->mpMorf->getFrame() >= 170.0f)) || (i_this->m3F8 == 0x20)) {
        fopAcM_seStart(actor, JA_SE_CM_BPW_SWING_KANTERA, 0);
    }
    if (((i_this->m3F8 == 0x1f) && (i_this->mpMorf->getFrame() >= 60.0f)) || (i_this->m3F8 == 0x20)) {
        fopAcM_seStart(actor, JA_SE_OBJ_BPW_FLYING, 0);
    }
    if (i_this->mActionState >= 0xCA) {
        camera->mCamera.Set(i_this->m40C, i_this->m418, i_this->m440, 0);
    }
    if (i_this->mActionState >= 0xd1) {
        bpw_class* lantern = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
        if (lantern != NULL) {
            lantern->mpMorf->play(NULL, 0, 0);
            if (lantern->mpMorf->checkFrame(REG8_F(9) + 128.0f)) {
                fopAcM_seStart(actor, JA_SE_CM_BPW_KANTERA_APPEAR, 0);
                lantern->m3E7 = 0;
            }
        }
    }
}

/* 0000A064-0000A168       .text vib_mode_check__FP9bpw_class */
void vib_mode_check(bpw_class* i_this) {
    switch (i_this->m3E8) {
    case 0:
        break;
    case 1:
        dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        i_this->m3E8 = 0;
        break;
    case 2:
        dComIfGp_getVibration().StartShock(3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        i_this->m3E8 = 0;
        break;
    case 3:
        if (i_this->mSomeCountdownTimers[6] == 0) {
            dComIfGp_getVibration().StopQuake(-1);
            i_this->m3E8 = 0;
        }
        break;
    }
}

/* 0000A168-0000A494       .text kantera_calc__FP9bpw_class */
void kantera_calc(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bpw_class* pfVar4;

    if (i_this->m3FC != fpcM_ERROR_PROCESS_ID_e) {
        pfVar4 = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
        if (pfVar4 != NULL) {
            switch (i_this->mAttWaitTimer) {
            case 4:
                break;
            case 0:
                cLib_addCalcAngleS2(&pfVar4->actor.shape_angle.x, actor->shape_angle.x + REG12_S(0), 1, 0x1000);
                cLib_addCalcAngleS2(&pfVar4->actor.shape_angle.y, actor->shape_angle.y + REG12_S(1), 1, 0x1000);
                cLib_addCalcAngleS2(&pfVar4->actor.shape_angle.z, actor->shape_angle.z + -0x4000, 1, 0x1000);
                cLib_addCalcAngleS2(&pfVar4->mKanteraDousaRot.x, REG12_S(3), 1, 0x1000);
                cLib_addCalcAngleS2(&pfVar4->mKanteraDousaRot.y, 0x2000, 1, 0x1000);
                cLib_addCalcAngleS2(&pfVar4->mKanteraDousaRot.z, REG12_S(5), 1, 0x1000);
                break;
            case 1:
                if (i_this->mBodyAction != ACTION_START_DEMO) {
                    cLib_addCalcAngleS2(&i_this->m484, 3000, 1, 100);
                    cLib_addCalc2(&i_this->m388, 2000.0f, 1.0f, 1000.0f);
                    cLib_addCalc2(&i_this->m390, 2000.0f, 1.0f, 1000.0f);
                }
                break;
            case 2:
                cLib_addCalcAngleS2(&i_this->m484, 6000, 1, 100);
                cLib_addCalc2(&i_this->m388, 6000.0f, 1.0f, 1000.0f);
                cLib_addCalc2(&i_this->m390, 6000.0f, 1.0f, 1000.0f);
                break;
            case 3:
                pfVar4->actor.current.angle.y = player->shape_angle.y;
                pfVar4->mActionState = 2;
                i_this->mAttWaitTimer = i_this->mAttWaitTimer + 1;
                break;
            }
            if (i_this->mAttWaitTimer != 4) {
                pfVar4->actor.current.pos = i_this->mChildActorPos;
                if (i_this->mAttWaitTimer != 0) {
                    cLib_addCalcAngleS2(&pfVar4->actor.shape_angle.x, actor->shape_angle.x, 1, 0x1000);
                    cLib_addCalcAngleS2(&pfVar4->actor.shape_angle.y, actor->shape_angle.y + 0x4000, 1, 0x1000);
                    cLib_addCalcAngleS2(&pfVar4->actor.shape_angle.z, actor->shape_angle.z, 1, 0x1000);
                    i_this->m482 += i_this->m484;
                    cLib_addCalcAngleS2(&pfVar4->mKanteraDousaRot.x, i_this->m388 * cM_ssin(i_this->m482), 1, 0x1000);
                    cLib_addCalcAngleS2(&pfVar4->mKanteraDousaRot.y, 0, 1, 0x1000);
                    cLib_addCalcAngleS2(&pfVar4->mKanteraDousaRot.z, i_this->m390 * cM_scos(i_this->m482), 1, 0x1000);
                }
            }
        }
    }
}

/* 0000A494-0000A8C8       .text body_execute__FP9bpw_class */
void body_execute(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28 = i_this->m358;

#if VERSION == VERSION_DEMO
    if (CPad_CHECK_HOLD_Z(0) && CPad_CHECK_HOLD_DOWN(0)) {
        dComIfGs_onStageBossEnemy();
        if (dComIfGp_getStartStageName()[0] == 'X') {
            dComIfGs_onEventBit(dSv_event_flag_c::JALHALLA_TRIALS_CLEAR);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0480);
            dLib_setNextStageBySclsNum(0, actor->current.roomNo);
            mDoAud_seStart(JA_SE_LK_B_BOSS_WARP, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            fopAcM_delete(actor);
        } else {
            fopAcM_createWarpFlower(&i_this->mBodyPos, 0, fopAcM_GetRoomNo(actor), 0);
            fopAcM_delete(actor);
            if (i_this->m3FC != fpcM_ERROR_PROCESS_ID_e) {
                i_this = (bpw_class*)fopAcM_SearchByID(i_this->m3FC);
                actor = &i_this->actor;
                fopAcM_createDisappear(actor, &actor->current.pos, 10, daDisItem_NONE3_e, 0xFF);
                fopAcM_delete(actor);
            }
        }
        return;
    }
#endif

    if (REG8_S(2) != 0) {
        actor->speedF = 0.0f;
        actor->attention_info.position = actor->current.pos;
        actor->attention_info.position.y += 700.0f;
        actor->eyePos = actor->current.pos;
        actor->eyePos.y += 300.0f;
        i_this->mBodyCoSph.SetC(local_28);
        i_this->mBodyCoSph.SetR(240.0f);
        dComIfG_Ccsp()->Set(&i_this->mBodyCoSph);
        local_28 = i_this->m370;
        i_this->mBodyAtSph.SetC(local_28);
        i_this->mBodyAtSph.SetR(i_this->m4A8);
        dComIfG_Ccsp()->Set(&i_this->mBodyAtSph);
    } else {
        switch (i_this->mBodyAction) {
        case ACTION_MOVE_DOUSA:
            action_dousa(i_this);
            break;
        case ACTION_ATTACK_KOUGEKI:
            action_kougeki(i_this);
            break;
        case ACTION_BODY_DOWN_KARADA_TAORE:
            action_karada_taore(i_this);
            break;
        case ACTION_DAMAGE:
            action_damage(i_this);
            break;
        case ACTION_SEPARATION_BUNRI_DOUSA:
            action_bunri_dousa(i_this);
            break;
        case ACTION_START_DEMO:
            action_start_demo(i_this);
            break;
        }
        if (i_this->m3E5 == 0) {
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->m476, 1, i_this->m47A);
            cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 1, i_this->m47A);
        }
        i_this->mpMorf->play(NULL, 0, 0);
        if (i_this->m3E0 != 0) {
            i_this->mpLightFreezeBrkAnm->play();
        } else {
            if (i_this->m3E1 != 0) {
                i_this->mpLightStunBrkAnm->play();
            } else {
                if (i_this->m3E2 == 2) {
                    i_this->mpCurseStartBrkAnm->play();
                    fopAcM_seStart(actor, JA_SE_OBJ_BPW_FLYING_CURSE, 0);
                } else if (i_this->m3E2 == 1) {
                    if (i_this->mpCurseEndBrkAnm->isStop()) {
                        noroi_brk_check(i_this, 2);
                    } else {
                        i_this->mpCurseEndBrkAnm->play();
                        fopAcM_seStart(actor, JA_SE_OBJ_BPW_FLYING_CURSE, 0);
                    }
                } else {
                    i_this->mpDefaultBrkAnm->play();
                    if (i_this->mBodyAction != ACTION_START_DEMO) {
                        fopAcM_seStart(actor, JA_SE_OBJ_BPW_FLYING, 0);
                    }
                }
            }
        }
        actor->attention_info.position = actor->current.pos;
        actor->attention_info.position.y += i_this->m4A4 * 2.0f + 100.0f;
        actor->eyePos = actor->current.pos;
        actor->eyePos.y += i_this->m4A4;
        i_this->mBodyCoSph.SetC(local_28);
        i_this->mBodyCoSph.SetR(REG0_S(6) + 260.0f);
        dComIfG_Ccsp()->Set(&i_this->mBodyCoSph);
        local_28 = i_this->m370;
        i_this->mBodyAtSph.SetC(local_28);
        i_this->mBodyAtSph.SetR(i_this->m4A8);
        dComIfG_Ccsp()->Set(&i_this->mBodyAtSph);
        body_atari_check(i_this);
    }
}

/* 0000A8C8-0000A9DC       .text kantera_atari_check__FP9bpw_class */
BOOL kantera_atari_check(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* pcVar4;

    i_this->mStts.Move();
    if (!i_this->mKanteraCoSph.ChkTgHit()) {
        return FALSE;
    }
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    pcVar4 = i_this->mKanteraCoSph.GetTgHitObj();
    if (pcVar4 == NULL) {
        return FALSE;
    }
    switch (pcVar4->GetAtType()) {
    case AT_TYPE_SKULL_HAMMER:
        actor->speedF = 60.0f;
        actor->current.angle.y = player->shape_angle.y;
        i_this->mHitType = 8;
        if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
            i_this->mHitType = 9;
            actor->current.angle.y = player->shape_angle.y + -0x4000;
        }
        fopAcM_seStart(actor, JA_SE_LK_HAMMER_HIT, 0x42);
        return TRUE;
    }
    return FALSE;
}

/* 0000A9DC-0000AD74       .text action_kantera_dousa__FP9bpw_class */
void action_kantera_dousa(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar4;
    fopAc_ac_c* pfVar2;

    switch (i_this->mActionState) {
    case 0:
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        i_this->m3E4 = 0;
        i_this->m3AC.x = 0.0f;
        i_this->m3AC.y = 0.0f;
        i_this->m3AC.z = 0.0f;
        i_this->m498 = 50.0f;
        i_this->m49C = 200.0f;
        i_this->mKanteraCoSph.ClrCoSet();
        i_this->m48C = 60.0f;
        i_this->mActionState++;
        break;
    case 2:
        actor->speed.y = 10.0f;
        actor->speedF = 10.0f;
        i_this->m3AC.y = 140.0f;
        actor->gravity = -3.0f;
        i_this->mActionState++;
    case 3:
        switch (i_this->m462) {
        case 0:
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->mKanteraCoSph.OnCoSetBit();
                actor->speed.y = 17.0f;
                actor->speedF = 0.0f;
                fopAcM_seStart(actor, JA_SE_OBJ_BPW_KANTERA_FALL, 0);
                i_this->m462++;
            }
            break;
        case 1:
            actor->shape_angle.y = actor->shape_angle.y + 0x1000;
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0x2000, 1, 0x700);
            cLib_addCalcAngleS2(&actor->shape_angle.z, 0x4000, 1, 0x600);
            sVar4 = cLib_distanceAngleS(actor->shape_angle.z, 0x4000);
            if ((sVar4 < 0x100) && (i_this->mAcch.ChkGroundHit())) {
                i_this->m462++;
                actor->shape_angle.x = 0x2000;
                actor->shape_angle.z = 0x4000;
            }
            break;
        case 2:
            cLib_addCalcAngleS2(&i_this->mKanteraDousaRot.x, 0, 1, 0x500);
            cLib_addCalcAngleS2(&i_this->mKanteraDousaRot.z, 0, 1, 0x500);
            break;
        }
        break;
    case 4:
        if (i_this->mAcch.ChkWallHit()) {
            actor->current.angle.y = actor->current.angle.y + -0x4000;
        }
        actor->shape_angle.y = actor->shape_angle.y + i_this->m464;
        cLib_addCalcAngleS2(&i_this->m464, 0, 1, 0x200);
        cLib_addCalc0(&actor->speedF, 1.0f, 3.0f);
        if (actor->speedF < 1.0f) {
            actor->current.angle.y = actor->shape_angle.y;
            actor->speedF = 0.0f;
            i_this->m462 = 1;
            i_this->mActionState = 3;
        }
        break;
    case 5:
        pfVar2 = fopAcM_SearchByID(i_this->m404);
        if (pfVar2 != NULL) {
            sVar4 = fopAcM_searchActorAngleY(actor, pfVar2);
            actor->current.angle.y = sVar4;
        }
        cLib_addCalc0(&actor->speedF, 1.0f, 3.0f);
        if (actor->speedF < 1.0f) {
            i_this->m3E4 = 0;
            i_this->mActionState = 3;
        }
    }
    if ((i_this->m3E4 != 0) && (i_this->mActionState != 5)) {
        actor->speedF = 15.0f;
        i_this->mKanteraDousaRot.x = 0;
        i_this->mKanteraDousaRot.y = 0;
        i_this->mKanteraDousaRot.z = 0;
        i_this->mActionState = 5;
    }
    if ((i_this->mActionState != 4) && (kantera_atari_check(i_this))) {
        i_this->m464 = 0x2000;
        i_this->mKanteraDousaRot.x = 0;
        i_this->mKanteraDousaRot.y = 0;
        i_this->mKanteraDousaRot.z = 0;
        i_this->mActionState = 4;
    }
}

/* 0000AD74-0000B004       .text kantera_execute__FP9bpw_class */
void kantera_execute(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cCcD_Obj* pcVar2;
    cXyz local_28;

    local_28 = i_this->m358;
    switch (i_this->mBodyAction) {
    case ACTION_MOVE_DOUSA:
        action_kantera_dousa(i_this);
    }

    i_this->mKanteraCoSph.SetC(local_28);
    i_this->mKanteraCoSph.SetR(70.0f);
    dComIfG_Ccsp()->Set(&i_this->mKanteraCoSph);
    if (i_this->m3E7 == 0) {
        i_this->mpLanternGlowBrkAnm->play();
    }
    if (i_this->mKanteraCoSph.ChkTgHit()) {
        pcVar2 = i_this->mKanteraCoSph.GetTgHitObj();
        switch (pcVar2->GetAtType()) {
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
        default:
            fopAcM_seStart(actor, JA_SE_LK_MS_WEP_HIT, 0x42);
            break;
        }
    }
    if (i_this->mSomeCountdownTimers[0] == 0) {
        i_this->mSomeCountdownTimers[0] = (s16)(int)cM_rndF(5.0f);
        i_this->m47E = (s16)(int)(cM_rndF(5.0f) + 8.0f);
    }
    actor->attention_info.position = i_this->m358;
    actor->attention_info.position.y += 50.0f;
    actor->eyePos = i_this->m358;
    actor->eyePos.y += 50.0f;
}

/* 0000B004-0000B700       .text action_b_fire_1_dousa__FP9bpw_class */
void action_b_fire_1_dousa(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 fVar2;
    cXyz local_c4;
    dBgS_LinChk linChk;

    switch (i_this->mActionState) {
    case 10:
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        i_this->m498 = 0.0f;
        i_this->m49C = 40.0f;
#if VERSION == VERSION_DEMO
        i_this->m534_demo = dComIfGp_particle_set(
            dPa_name::ID_AK_SN_BPWFLAMETHROWER00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFire1Dousa_Pa_followEcallBack
        );
        i_this->m538_demo = dComIfGp_particle_set(
            dPa_name::ID_AK_SN_BPWFLAMETHROWER01, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFire1Dousa_Pa_followEcallBack2
        );
#else
        if (i_this->mFire1Dousa_Pa_followEcallBack.getEmitter() == NULL) {
            dComIfGp_particle_set(
                dPa_name::ID_AK_SN_BPWFLAMETHROWER00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFire1Dousa_Pa_followEcallBack
            );
        }
        if (i_this->mFire1Dousa_Pa_followEcallBack2.getEmitter() == NULL) {
            dComIfGp_particle_set(
                dPa_name::ID_AK_SN_BPWFLAMETHROWER01, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFire1Dousa_Pa_followEcallBack2
            );
        }
#endif
        i_this->mSomeCountdownTimers[0] = 5;
        i_this->m3A0 = actor->current.pos;
        i_this->mActionState++;
        // fallthrough
    case 11:
        i_this->m462 += (s16)(REG6_S(0) + 0x5dc);
        i_this->m494 = (int)(REG6_S(1) + 0x32);
        actor->shape_angle.y += (s32)((REG6_S(2) + 2000.0f) * cM_ssin(i_this->m462));
        i_this->m304[0] = actor->current.pos;
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
        cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
        local_c4.x = 0.0f;
        local_c4.y = 0.0f;
        local_c4.z = 1000.0f;
        MtxPosition(&local_c4, i_this->m328);
        i_this->m328[0] += actor->current.pos;
        linChk.Set(i_this->m304, i_this->m328, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(linChk);
            (i_this->m66C) = *linChk.GetCrossP();
            if (pla->GetNP()->y == 1.0f) {
                i_this->m67E = 0;
            } else {
                fVar1 = i_this->m304[0].x - i_this->m66C.x;
                fVar2 = i_this->m304[0].z - i_this->m66C.z;
                i_this->m67E = 0x4000;
                i_this->m680 = cM_atan2s(fVar1, fVar2);
            }
#if VERSION == VERSION_DEMO
            if (i_this->m53C_demo == NULL) {
                i_this->m53C_demo =
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWFLAMETHROWER02, &i_this->m66C, (csXyz*)&i_this->m67E, NULL, 0xFF, &i_this->m590);
            }
#else
            if (i_this->m590.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWFLAMETHROWER02, &i_this->m66C, (csXyz*)&i_this->m67E, NULL, 0xFF, &i_this->m590);
            }
#endif
        } else {
#if VERSION == VERSION_DEMO
            if (i_this->m53C_demo) {
                i_this->m53C_demo->becomeInvalidEmitter();
                i_this->m590.remove();
                i_this->m53C_demo = NULL;
            }
#else
            i_this->m590.remove();
#endif
        }
        i_this->mFire1DousaPos = actor->current.pos;
        i_this->mFire1DousaRot = actor->shape_angle;
        local_c4 = i_this->m328[0];
        if (i_this->m464 != 0) {
            local_c4 = i_this->m304[0];
        }
        fVar1 = std::fabsf(i_this->m304[0].x - i_this->m328[0].x) * 0.3f;
        cLib_addCalc2(&i_this->m3A0.x, local_c4.x, 1.0f, fVar1);
        fVar1 = std::fabsf(i_this->m304[0].y - i_this->m328[0].y) * 0.3f;
        cLib_addCalc2(&i_this->m3A0.y, local_c4.y, 1.0f, fVar1);
        f32 z = std::fabsf(i_this->m304[0].z - i_this->m328[0].z) * 0.3f;
        cLib_addCalc2(&i_this->m3A0.z, local_c4.z, 1.0f, z);
        f32 fVar_x = i_this->m3A0.x - local_c4.x;
        f32 fVar_y = i_this->m3A0.y - local_c4.y;
        f32 fVar_z = i_this->m3A0.z - local_c4.z;
        fVar1 = std::sqrtf(fVar_x * fVar_x + fVar_y * fVar_y + fVar_z * fVar_z);
        if (fVar1 < 2.0f) {
            i_this->m464++;
            i_this->m464 &= 1;
        }
        break;
    }
}

/* 0000B700-0000BD18       .text action_b_fire_2_dousa__FP9bpw_class */
void action_b_fire_2_dousa(bpw_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_30;

    csXyz local_38 = actor->shape_angle;
    switch (i_this->mActionState) {
    case 0x14:
        fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
        for (s32 i = 0; i < 10; i++) {
            i_this->mSomeCountdownTimers[i + 10] = 0;
        }
        i_this->m498 = 0.0f;
        i_this->m49C = 40.0f;
#if VERSION == VERSION_DEMO
        i_this->m594_demo = dComIfGp_particle_set(
            dPa_name::ID_AK_SN_BPWFIRE00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFireDousa2_Pa_followEcallBack
        );
        i_this->m598_demo = dComIfGp_particle_set(
            dPa_name::ID_AK_SN_BPWFIRE01, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFireDousa2_Pa_followEcallBack2
        );
#else
        if (i_this->mFireDousa2_Pa_followEcallBack.getEmitter() == NULL) {
            dComIfGp_particle_set(
                dPa_name::ID_AK_SN_BPWFIRE00, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFireDousa2_Pa_followEcallBack
            );
        }
        if (i_this->mFireDousa2_Pa_followEcallBack2.getEmitter() == NULL) {
            dComIfGp_particle_set(
                dPa_name::ID_AK_SN_BPWFIRE01, &i_this->mFire1DousaPos, &i_this->mFire1DousaRot, NULL, 0xFF, &i_this->mFireDousa2_Pa_followEcallBack2
            );
        }
#endif
        actor->current.angle.y = cM_atan2s(player->current.pos.x - actor->current.pos.x, player->current.pos.z - actor->current.pos.z);
        actor->current.angle.y += (int)cM_rndFX(DEMO_SELECT(REG11_F(18) + 14384.0f, 14384.0f));
        actor->shape_angle.y = actor->current.angle.y;
        actor->speedF = 15.0f;
        actor->speedF += cM_rndFX(20.0f);
        actor->speed.y = 25.0f;
        actor->speed.y += cM_rndFX(10.0f);
        actor->gravity = -3.0f;
        actor->shape_angle.x = -0x2000;
        i_this->m494 = (s32)(REG6_S(3) + 0x1e);
        i_this->mFire1DousaPos = actor->current.pos;
        i_this->mFire1DousaRot = actor->shape_angle;
        i_this->mActionState++;
        break;
    case 0x15:
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0x4000, 1, 3000);
        i_this->mFire1DousaPos = actor->current.pos;
        i_this->mFire1DousaRot = actor->shape_angle;
        if (i_this->mAcch.ChkGroundHit()) {
            fopAcM_seStart(actor, JA_SE_OBJ_BPW_FIRE_EXPLODE, 0);
            local_30 = actor->current.pos;
            local_30.y = i_this->mAcch.GetGroundH();
            local_38.z = local_38.x = 0;
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWFLOORFIRE01, &local_30, &local_38);
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWFLOORFIRE02, &local_30, &local_38);
            dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWHITFIRE00, &local_30, &actor->current.angle);
#if VERSION == VERSION_DEMO
            if (i_this->m594_demo != NULL) {
                i_this->m594_demo->becomeInvalidEmitter();
                i_this->mFireDousa2_Pa_followEcallBack.remove();
                i_this->m594_demo = NULL;
            }
            if (i_this->m598_demo != NULL) {
                i_this->m598_demo->becomeInvalidEmitter();
                i_this->mFireDousa2_Pa_followEcallBack2.remove();
                i_this->m598_demo = NULL;
            }
#else
            i_this->mFireDousa2_Pa_followEcallBack.remove();
            i_this->mFireDousa2_Pa_followEcallBack2.remove();
#endif
            if (i_this->mSomeCountdownTimers[1] == 0) {
                i_this->mSomeCountdownTimers[1] = (s16)(int)cM_rndF(5.0f);
                i_this->m47E = (s16)(int)(cM_rndF(5.0f) + 8.0f);
            }
            i_this->mSomeCountdownTimers[0] = 0x5a;
            actor->speedF = 0.0f;
            actor->gravity = 0.0f;
            actor->speed.setall(0.0f);
            i_this->m494 = (s32)(REG6_S(4) + 0x23);
            i_this->mActionState = 0x16;
        } else {
            if ((i_this->mAcch.ChkWallHit()) || (i_this->mDamageBallCoSph.ChkAtHit())) {
                dComIfGp_particle_set(dPa_name::ID_AK_SN_BPWHITFIRE00, &actor->current.pos, &actor->current.angle);
                i_this->mActionState = 0x17;
            }
        }
        break;
    case 0x16:
        actor->shape_angle.y += 0x100;
        if (i_this->mSomeCountdownTimers[0] > 0xA) {
            if (i_this->mSomeCountdownTimers[1] == 0) {
                i_this->mSomeCountdownTimers[1] = (s16)(int)cM_rndF(5.0f);
                i_this->m47E = (s16)(int)(cM_rndF(5.0f) + 8.0f);
            }
        } else if (i_this->m47E > 0) {
            i_this->m47E--;
        }
        if (i_this->mSomeCountdownTimers[0] == 0) {
            fopAcM_delete(actor);
        } else {
            fopAcM_seStart(actor, JA_SE_OBJ_BAR_FRAME_BURN, 0);
        }
        break;
    case 0x17:
#if VERSION == VERSION_DEMO
        if (i_this->m594_demo != NULL) {
            i_this->m594_demo->becomeInvalidEmitter();
            i_this->mFireDousa2_Pa_followEcallBack.remove();
            i_this->m594_demo = NULL;
        }
        if (i_this->m598_demo != NULL) {
            i_this->m598_demo->becomeInvalidEmitter();
            i_this->mFireDousa2_Pa_followEcallBack2.remove();
            i_this->m598_demo = NULL;
        }
#else
        i_this->mFireDousa2_Pa_followEcallBack.remove();
        i_this->mFireDousa2_Pa_followEcallBack2.remove();
#endif
        fopAcM_delete(actor);
        break;
    }
}

/* 0000BD18-0000BE50       .text damage_ball_execute__FP9bpw_class */
static void damage_ball_execute(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_18;

    switch (i_this->mBodyAction) {
    case 0:
        action_b_fire_1_dousa(i_this);
        if (i_this->mDamageBallCoSph.ChkAtHit() != 0) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            fopAc_ac_c* pdVar4 = i_this->mDamageBallCoSph.GetAtHitAc();
            if (pdVar4 != NULL && (pdVar4 == player)) {
                GOUEN_FIRE_HIT = 1;
            }
        }
        local_18 = i_this->m3A0;
        break;
    case 1:
        action_b_fire_2_dousa(i_this);
        local_18 = actor->current.pos;
        i_this->mLightInfluence.mPos.x = local_18.x;
        i_this->mLightInfluence.mPos.y = actor->current.pos.y;
        i_this->mLightInfluence.mPos.z = actor->current.pos.z;
        i_this->mLightInfluence.mColor.r = 300;
        i_this->mLightInfluence.mColor.g = 0x96;
        i_this->mLightInfluence.mColor.b = 0x14;
        i_this->mLightInfluence.mPower = 450.0f;
        i_this->mLightInfluence.mFluctuation = 250.0f;
        break;
    }
    i_this->mDamageBallCoSph.SetC(local_18);
    i_this->mDamageBallCoSph.SetR(i_this->m494);
    dComIfG_Ccsp()->Set(&i_this->mDamageBallCoSph);
}

/* 0000BE50-0000C154       .text torituki_execute__FP9bpw_class */
void torituki_execute(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->mActionState) {
    case 0:
        if (dComIfGp_getStartStageName()[0] == 'X') {
            mDoAud_bgmStart(JA_BGM_UNK_150);
        } else {
            mDoAud_bgmStart(JA_BGM_UNK_140);
        }
        i_this->mActionState++;
        // fallthrough
    case 1:
        cLib_addCalc2(&actor->scale.x, 0.4f, 1.0f, 0.1f);
        fVar1 = actor->scale.x;
        actor->scale.z = fVar1;
        actor->scale.y = fVar1;
        if (!(actor->scale.x < 0.3f)) {
            anm_init(i_this, BPW_BCK_TORITUKI1, DEMO_SELECT(REG11_F(0) + 15.0f, 15.0f), J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mSomeCountdownTimers[8] = DEMO_SELECT(0xD2, 0x96);
            actor->scale.setall(0.4f);
            i_this->mActionState++;
            // fallthrough
        case 2:
            actor->shape_angle.y += 1000;
            if (i_this->mSomeCountdownTimers[8] != 0) {
                daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                if (((i_this->mSomeCountdownTimers[8] == 1 || (dComIfGp_getDetect().chk_light(&actor->current.pos))) ||
                     (dComIfGp_checkPlayerStatus1(0, daPyStts1_UNK2000_e))) ||
                    (player->getDamageWaitTimer() != 0 || (player->checkFairyUse())))
                {
                    player->offConfuse();
                    i_this->mSomeCountdownTimers[8] = 0;
                    if (dComIfGp_getStartStageName()[0] == 'X') {
                        mDoAud_bgmStart(JA_BGM_PAST_BIG_POW);
                    } else {
                        mDoAud_bgmStart(JA_BGM_BIG_POW);
                    }
                    i_this->mActionState++;
                }
            }
        }
        break;
    case 3:
        cLib_addCalc0(&actor->scale.x, 1.0f, 0.1f);
        fVar1 = actor->scale.x;
        actor->scale.z = fVar1;
        actor->scale.y = fVar1;
        if (actor->scale.x < 0.1f) {
            fopAcM_delete(actor);
        }
        break;
    }
    i_this->mpMorf->play(NULL, 0, 0);
    cLib_addCalcAngleS2(&i_this->m47E, 0xFF, 1, 10);
    if (i_this->mActionState == 2) {
        actor->current.pos = player->getHeadTopPos();
        i_this->m47C = i_this->m47C + 700;
        actor->current.pos.y += 100.0f;
        actor->current.pos.y += cM_ssin(i_this->m47C) * 30.0f;
    }
}

/* 0000C154-0000C5C0       .text daBPW_Execute__FP9bpw_class */
static BOOL daBPW_Execute(bpw_class* i_this) {
    /* Nonmatching - retail-only fpr regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_1c;
    cXyz local_28;

#if VERSION > VERSION_DEMO
    if (dComIfGp_getStartStageName()[0] == 'X') {
        i_this->m408 = 0x32;
    } else if (i_this->m408 > 2) {
        i_this->m408 -= 2;
    }
#endif
    for (s32 i = 0; i < 10; i++) {
        if (i_this->mSomeCountdownTimers[i] != 0) {
            i_this->mSomeCountdownTimers[i]--;
        }
    }
    switch (i_this->mType) {
    case ACTOR_TYPE_BODY:
        body_execute(i_this);
        light_on_off(i_this);
        break;
    case ACTOR_TYPE_KANTERA:
        kantera_execute(i_this);
        break;
    case ACTOR_TYPE_DAMAGE_BALL:
        damage_ball_execute(i_this);
        break;
    case ACTOR_TYPE_TORITUKI:
        torituki_execute(i_this);
        break;
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_1c.x = 0.0f;
    local_1c.y = 0.0f;
    local_1c.z = actor->speedF;
    MtxPosition(&local_1c, &local_28);
    actor->speed.x = local_28.x;
    actor->speed.z = local_28.z;
    actor->speed.y += actor->gravity;
    if (actor->speed.y < -100.0f) {
        actor->speed.y = -100.0f;
    }
    switch (i_this->mType) {
    case ACTOR_TYPE_BODY:
        if (i_this->mBodyCoSph.ChkCoSet()) {
            fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
        } else {
            fopAcM_posMove(actor, NULL);
        }
        BG_check(i_this);
        draw_SUB(i_this);
        break;
    case ACTOR_TYPE_KANTERA:
        if (i_this->mActionState != 1) {
            fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
            BG_check(i_this);
        }
        kantera_draw_SUB(i_this);
        if (i_this->m3E7 == 0) {
            if (i_this->m5CC.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_JN_TORCH, &i_this->m358, NULL, &actor->scale, 0xFF, &i_this->m5CC);
                i_this->mFire1DousaPos = i_this->m358;
            }
            JPABaseEmitter* emitter = i_this->m5CC.getEmitter();
            if (emitter != NULL) {
                Vec vec1;
                vec1.x = (i_this->m358.x - i_this->mFire1DousaPos.x) * (-0.03f + REG0_F(4));
                if (vec1.x > 1.0f) {
                    vec1.x = 1.0f;
                } else if (vec1.x < -1.0f) {
                    vec1.x = -1.0f;
                }
                vec1.z = (i_this->m358.z - i_this->mFire1DousaPos.z) * (-0.03f + REG0_F(4));
                if (vec1.z > 1.0f) {
                    vec1.z = 1.0f;
                } else if (vec1.z < -1.0f) {
                    vec1.z = -1.0f;
                }
                JGeometry::TVec3<f32> dir;
                dir.x = vec1.x;
                dir.y = 0.1f;
                dir.z = vec1.z;
                emitter->setDirection(dir);
                JGeometry::TVec3<f32> vel;
                vel = actor->current.pos - actor->old.pos;
                Vec vec2;
                vec2.x = 1.0f;
                vec2.y = 1.0f + std::sqrtf(SQUARE(vel.x) + SQUARE(vel.y) + SQUARE(vel.z)) * 0.05f;
                if (vec2.y > 2.0f) {
                    vec2.y = 2.0f;
                }
                JGeometry::TVec3<f32> scale(vec2.x, vec2.y, vec2.x);
                emitter->setGlobalParticleScale(scale);
                i_this->mFire1DousaPos = i_this->m358;
                mDoAud_seStart(JA_SE_OBJ_TORCH_BURNING, &i_this->m358, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
        }
        break;
    case ACTOR_TYPE_DAMAGE_BALL:
        fopAcM_posMove(actor, NULL);
        BG_check(i_this);
        draw_SUB(i_this);
        break;
    case ACTOR_TYPE_TORITUKI:
        draw_SUB(i_this);
        break;
    }
    if (i_this->mType == ACTOR_TYPE_BODY) {
        kantera_calc(i_this);
        vib_mode_check(i_this);
        kankyou_hendou(i_this);
    }
    return TRUE;
}

/* 0000C5C0-0000C5C8       .text daBPW_IsDelete__FP9bpw_class */
static BOOL daBPW_IsDelete(bpw_class*) {
    return TRUE;
}

/* 0000C5C8-0000C770       .text daBPW_Delete__FP9bpw_class */
static BOOL daBPW_Delete(bpw_class* i_this) {
#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&i_this->m358);
    mDoAud_seDeleteObject(&i_this->m3C4);
#endif
    dComIfG_resDeleteDemo(&i_this->mPhase, "BPW");
    if (i_this->mType == ACTOR_TYPE_KANTERA) {
        i_this->m5CC.remove();
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m5E0); i++) {
        i_this->m5E0[i].remove();
    }
#if VERSION == VERSION_DEMO
    if (i_this->m534_demo != NULL) {
        i_this->m534_demo->becomeInvalidEmitter();
        i_this->mFire1Dousa_Pa_followEcallBack.remove();
        i_this->m534_demo = NULL;
    }
    if (i_this->m538_demo != NULL) {
        i_this->m538_demo->becomeInvalidEmitter();
        i_this->mFire1Dousa_Pa_followEcallBack2.remove();
        i_this->m538_demo = NULL;
    }
    if (i_this->m53C_demo != NULL) {
        i_this->m53C_demo->becomeInvalidEmitter();
        i_this->m590.remove();
        i_this->m53C_demo = NULL;
    }
    if (i_this->m508_demo != NULL) {
        i_this->m508_demo->becomeInvalidEmitter();
        i_this->m508_demo = NULL;
    }
    if (i_this->m540_demo != NULL) {
        i_this->m540_demo->becomeInvalidEmitter();
        i_this->m554.remove();
        i_this->m540_demo = NULL;
    }
    if (i_this->m50C_demo != NULL) {
        i_this->m50C_demo->becomeInvalidEmitter();
        i_this->m50C_demo = NULL;
    }
    if (i_this->m594_demo != NULL) {
        i_this->m594_demo->becomeInvalidEmitter();
        i_this->mFireDousa2_Pa_followEcallBack.remove();
        i_this->m594_demo = NULL;
    }
    if (i_this->m598_demo != NULL) {
        i_this->m598_demo->becomeInvalidEmitter();
        i_this->mFireDousa2_Pa_followEcallBack2.remove();
        i_this->m598_demo = NULL;
    }
    if (i_this->m510_demo != NULL) {
        i_this->m510_demo->becomeInvalidEmitter();
        i_this->m50C.remove();
        i_this->m510_demo = NULL;
    }
#else
    i_this->mFire1Dousa_Pa_followEcallBack.remove();
    i_this->mFire1Dousa_Pa_followEcallBack2.remove();
    i_this->m590.remove();
    i_this->m554.remove();
    i_this->mFireDousa2_Pa_followEcallBack.remove();
    i_this->mFireDousa2_Pa_followEcallBack2.remove();
    i_this->m540.remove();
    i_this->m52C.remove();
    i_this->m50C.remove();
#endif
    if (i_this->mUnknownParam2 == DAMAGE_ACTION_DAMAGE_BALL) {
        dKy_plight_cut(&i_this->mLightInfluence);
    }
    if (i_this->mSomeCountdownTimers[8] != 0) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        player->offConfuse();
    }
    return TRUE;
}

/* 0000C770-0000CC40       .text boss_useHeapInit__FP10fopAc_ac_c */
static BOOL boss_useHeapInit(fopAc_ac_c* a_this) {
    /* Nonmatching - retail-only regalloc */
    J3DModel* model;
    J3DAnmTevRegKey* pBrk;
    bpw_class* i_this = (bpw_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BPW", BPW_BDL_BPW),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("BPW", BPW_BCK_WAIT1),
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
        i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(body_nodeCallBack);
    }
    model = i_this->mpMorf->getModel();
    i_this->mpLightFreezeBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpLightFreezeBrkAnm == NULL) {
        return FALSE;
    }
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_HIRARU1);
    if (!i_this->mpLightFreezeBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    i_this->mpLightStunBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpLightStunBrkAnm == NULL) {
        return FALSE;
    }
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_HIT);
    if (!i_this->mpLightStunBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    i_this->mpCurseStartBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpCurseStartBrkAnm == NULL) {
        return FALSE;
    }
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_NOROI_S1);
    if (!i_this->mpCurseStartBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    i_this->mpCurseEndBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpCurseEndBrkAnm == NULL) {
        return FALSE;
    }
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_NOROI_E1);
    if (!i_this->mpCurseEndBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_NONE)) {
        return FALSE;
    }
    i_this->mpDefaultBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpDefaultBrkAnm == NULL) {
        return FALSE;
    }
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_DEFAULT);
    if (!i_this->mpDefaultBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    if (!i_this->mInvisibleModel.create(i_this->mpMorf->getModel())) {
        return FALSE;
    }
    return TRUE;
}

/* 0000CC88-0000CDF0       .text body_create_init__FP9bpw_class */
void body_create_init(bpw_class* i_this) {
    static dCcD_SrcSph body_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_STALFOS_MACE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcSph body_at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_STALFOS_MACE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_NoTgHitInfSet_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKA,
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
    fopAc_ac_c* actor = &i_this->actor;

    actor->max_health = 0xf;
    actor->health = 0xf;
    if (REG0_S(1) != 0) {
        actor->max_health = 1;
        actor->health = 1;
        i_this->m3F6 = 2;
    }
    i_this->mBodyPos = actor->current.pos;
    fopAcM_SetMtx(actor, i_this->mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(actor, -300.0f, -300.0f, -300.0f, 300.0f, 300.0f, 300.0f);
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    actor->attention_info.distances[2] = 4;
    fopAcM_OnStatus(actor, fopAcStts_BOSS_e);
    i_this->mAcch.Set(fopAcM_GetPosition_p(actor), fopAcM_GetOldPosition_p(actor), actor, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(actor));
    i_this->mStts.Init(0xfe, 1, actor);
    actor->attention_info.distances[4] = 0x25;
    fopAcM_OnStatus(actor, fopAcStts_UNK10000_e);
    i_this->mBodyCoSph.Set(body_co_sph_src);
    i_this->mBodyCoSph.SetStts(&i_this->mStts);
    i_this->mBodyCoSph.ClrCoSet();
    i_this->mBodyAtSph.Set(body_at_sph_src);
    i_this->mBodyAtSph.SetStts(&i_this->mStts);
    i_this->m476 = actor->current.angle.y;
    actor->model = i_this->mpMorf->getModel();
}

/* 0000CDF0-0000CFCC       .text kantera_useHeapInit__FP10fopAc_ac_c */
static BOOL kantera_useHeapInit(fopAc_ac_c* a_this) {
    bpw_class* i_this = (bpw_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BPW", BPW_BDL_BPW_KAN1), NULL, NULL, NULL, J3DFrameCtrl::EMode_RESET, 1.0f, 0, -1, 1, NULL, 0x80000, 0x37441422
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpMorf->getModel()->setUserArea((u32)i_this);
    for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(kantera_nodeCallBack);
    }
    J3DModel* model = i_this->mpMorf->getModel();
    i_this->mpLanternGlowBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpLanternGlowBrkAnm == NULL) {
        return FALSE;
    }
    J3DAnmTevRegKey* pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("BPW", BPW_BRK_BPW_KAN1);
    if (!i_this->mpLanternGlowBrkAnm->init(model->getModelData(), pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    return TRUE;
}

/* 0000CFCC-0000D0B8       .text kantera_create_init__FP9bpw_class */
void kantera_create_init(bpw_class* i_this) {
    static dCcD_SrcSph kantera_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
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
            /* Radius */ 15.0f,
        }},
    };
    fopAc_ac_c* actor = &i_this->actor;

    fopAcM_SetMtx(actor, i_this->mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(actor, -100.0f, -100.0f, -100.0f, 100.0f, 100.0f, 100.0f);
    i_this->mAcch.Set(fopAcM_GetPosition_p(actor), fopAcM_GetOldPosition_p(actor), actor, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(actor));
    i_this->mStts.Init(100, 1, actor);
    i_this->mKanteraCoSph.Set(kantera_co_sph_src);
    i_this->mKanteraCoSph.SetStts(&i_this->mStts);
    i_this->mKanteraCoSph.ClrCoSet();
    i_this->mBodyAction = ACTION_MOVE_DOUSA;
    i_this->mActionState = 0;
    i_this->m404 = actor->parentActorID;
    if (i_this->m404 == fpcM_ERROR_PROCESS_ID_e) {
        fopAcM_delete(actor);
    }
}

/* 0000D0B8-0000D1A0       .text fire_useHeapInit__FP10fopAc_ac_c */
static BOOL fire_useHeapInit(fopAc_ac_c* a_this) {
    bpw_class* i_this = (bpw_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BPW", BPW_BDL_BPW_KAN1), NULL, NULL, NULL, J3DFrameCtrl::EMode_RESET, 1.0f, 0, -1, 1, NULL, 0x80000, 0x37441422
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/* 0000D1A0-0000D254       .text damage_ball_create_init__FP9bpw_class */
void damage_ball_create_init(bpw_class* i_this) {
    static dCcD_SrcSph damage_ball_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 4,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsPlayer_e,
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
    fopAc_ac_c* actor = &i_this->actor;

    fopAcM_SetMtx(actor, i_this->mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(actor, -100.0f, -100.0f, -100.0f, 100.0f, 100.0f, 100.0f);
    i_this->mAcch.Set(fopAcM_GetPosition_p(actor), fopAcM_GetOldPosition_p(actor), actor, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(actor));
    i_this->mStts.Init(0xfe, 1, actor);
    i_this->mDamageBallCoSph.Set(damage_ball_co_sph_src);
    i_this->mDamageBallCoSph.SetStts(&i_this->mStts);
}

/* 0000D254-0000D368       .text tori_useHeapInit__FP10fopAc_ac_c */
static BOOL tori_useHeapInit(fopAc_ac_c* a_this) {
    bpw_class* i_this = (bpw_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BPW", BPW_BDL_BPW),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("BPW", BPW_BCK_TORITUKI1),
        J3DFrameCtrl::EMode_RESET,
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
    } else if (!i_this->mInvisibleModel.create(i_this->mpMorf->getModel())) {
        return FALSE;
    }
    return TRUE;
}

/* 0000D368-0000D43C       .text tori_create_init__FP9bpw_class */
void tori_create_init(bpw_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mBodyPos = actor->current.pos;
    fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
    fopAcM_SetMtx(actor, i_this->mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(actor, -300.0f, -300.0f, -300.0f, 300.0f, 300.0f, 300.0f);
    actor->attention_info.flags = 0;
    actor->current.pos = player->getHeadTopPos();
    i_this->mStts.Init(0, 1, actor);
}

/* 0000D43C-0000DB08       .text daBPW_Create__FP10fopAc_ac_c */
static cPhs_State daBPW_Create(fopAc_ac_c* a_this) {
    bpw_class* i_this = (bpw_class*)a_this;
    csXyz sp18 = a_this->shape_angle;
    fopAcM_ct_Retail(a_this, bpw_class);
    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "BPW");
    if (res == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(a_this, bpw_class);
        i_this->mType = fopAcM_GetParam(a_this);
        i_this->mUnknownParam2 = (fopAcM_GetParam(a_this) >> 8);
        i_this->mLightState = (fopAcM_GetParam(a_this) >> 0x10);
        if (i_this->mType == 0xFF) {
            i_this->mType = ACTOR_TYPE_BODY;
        }
        if (i_this->mUnknownParam2 == 0xFF) {
            i_this->mUnknownParam2 = DAMAGE_ACTION_LINE;
        }
        switch (i_this->mType) {
        case ACTOR_TYPE_BODY:
            if (dComIfGs_isStageBossEnemy()) {
                return cPhs_ERROR_e;
            }
            if (!fopAcM_entrySolidHeap(a_this, boss_useHeapInit, 0x36e0)) {
                return cPhs_ERROR_e;
            }
            body_create_init(i_this);
            i_this->m5E0[0].setRateOff(0);
            i_this->m5E0[1].setRateOff(0);
            i_this->m5E0[2].setRateOff(0);
            i_this->m5E0[3].setRateOff(0);
            i_this->m4A4 = 300.0f;
            i_this->m4A0 = 0.0f;
            i_this->m4A8 = REG8_F(16) + 220.0f;
            i_this->m3AC.y = 340.0f;
            i_this->mAttWaitTimer = 1;
            i_this->mChildActorPos = a_this->current.pos;
            for (s32 i = 0; i < 3; i++) {
                i_this->m304[i] = a_this->current.pos;
                i_this->m328[i] = a_this->current.pos;
            }
            i_this->m498 = 350.0f;
            i_this->m49C = 400.0f;
            i_this->mpMorf->play(NULL, 0, 0);
            BG_check(i_this);
            draw_SUB(i_this);
            sp18.y += 0x4000;
            i_this->m3FC = fopAcM_createChild(PROC_BPW, fopAcM_GetID(i_this), ACTOR_TYPE_KANTERA, &i_this->mChildActorPos, fopAcM_GetRoomNo(a_this), &sp18);
            i_this->mAttWaitTimer = 1;
            kantera_calc(i_this);
            if ((dComIfGp_getStartStageName()[0] != 'X') && (REG0_S(9) != 0 || (!dComIfGs_isStageBossDemo()))) {
                fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
                u32 uVar14;
                cXyz local_58;
                csXyz pwAngle = a_this->shape_angle;
                local_58 = a_this->current.pos;
                int currRandomAngle;
                int pwSpreadAmount = (int)(65536.0f / a_this->health);
                local_58.y = i_this->mAcch.GetGroundH() + 20.0f;
                currRandomAngle = (int)cM_rndFX(32768.0f);
                uVar14 = (s16)cM_rndF(4.99f);
                u32 uVar2 = uVar14 << 9 | 0xFF000004;
                for (s32 i = 0; i < 15; i++) {
                    i_this->mChildPoeIds[i] = fopAcM_createChild(PROC_PW, fopAcM_GetID(i_this), uVar2, &local_58, fopAcM_GetRoomNo(a_this), &pwAngle);
                    currRandomAngle += pwSpreadAmount;
                    pwAngle.y = (s16)currRandomAngle;
                    pwAngle.y += (int)cM_rndFX((s16)pwSpreadAmount * 0.25f);
                    uVar14++;
                    if (uVar14 > 5) {
                        uVar14 = 0;
                    }
                    uVar2 = uVar14 << 9 | 0xFF000004;
                }
                i_this->m3F6 = 3;
                light_on_off(i_this);
                i_this->mKankyouHendouState = 3;
                i_this->mSomeCountdownTimers[5] = 0;
                i_this->m3EC = 1.0f;
                kankyou_hendou(i_this);
                i_this->mBodyAction = ACTION_START_DEMO;
                i_this->mActionState = 200;
            } else {
                if (dComIfGp_getStartStageName()[0] == 'X') {
                    mDoAud_bgmStart(JA_BGM_PAST_BIG_POW);
                } else {
                    mDoAud_bgmStart(JA_BGM_BIG_POW);
                }
#if VERSION > VERSION_DEMO
                kankyou_hendou(i_this);
#endif
                i_this->mBodyAction = ACTION_MOVE_DOUSA;
                i_this->mActionState = 0;
            }
            break;
        case ACTOR_TYPE_KANTERA:
            if (!fopAcM_entrySolidHeap(a_this, kantera_useHeapInit, 0x14c0)) {
                return cPhs_ERROR_e;
            }
            kantera_create_init(i_this);
            fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
            if ((dComIfGp_getStartStageName()[0] != 'X') && (REG0_S(9) != 0 || (!dComIfGs_isStageBossDemo()))) {
                i_this->m3E7 = 1;
                anm_init(i_this, BPW_BCK_OPENING_KAN1, REG18_F(4), J3DFrameCtrl::EMode_NONE, 0.0f, -1);
            }
            i_this->m498 = 0.0f;
            i_this->m49C = 200.0f;
            BG_check(i_this);
            kantera_draw_SUB(i_this);
            break;
        case ACTOR_TYPE_DAMAGE_BALL:
            if (!fopAcM_entrySolidHeap(a_this, fire_useHeapInit, 0x14c0)) {
                return cPhs_ERROR_e;
            }
            i_this->m358 = a_this->current.pos;
            damage_ball_create_init(i_this);
            switch (i_this->mUnknownParam2) {
            case DAMAGE_ACTION_LINE:
                i_this->mDamageBallCoSph.SetAtSpl(dCcG_At_Spl_UNK9);
                i_this->mDamageBallCoSph.SetAtAtp(6);
                i_this->mBodyAction = ACTION_MOVE_DOUSA;
                i_this->mActionState = 10;
                break;
            case DAMAGE_ACTION_DAMAGE_BALL:
                dKy_plight_set(&i_this->mLightInfluence);
                i_this->mDamageBallCoSph.SetAtSpl(dCcG_At_Spl_UNK8);
                i_this->mBodyAction = ACTION_ATTACK_KOUGEKI;
                i_this->mActionState = 0x14;
                break;
            }
            BG_check(i_this);
            draw_SUB(i_this);
            break;
        case ACTOR_TYPE_TORITUKI:
            if (!fopAcM_entrySolidHeap(a_this, tori_useHeapInit, 0x10000)) {
                return cPhs_ERROR_e;
            }
            i_this->m3E0 = 1;
            a_this->scale.setall(0.0f);
            tori_create_init(i_this);
            draw_SUB(i_this);
            break;
        }
    }
    return res;
}

static actor_method_class l_daBPW_Method = {
    (process_method_func)daBPW_Create,
    (process_method_func)daBPW_Delete,
    (process_method_func)daBPW_Execute,
    (process_method_func)daBPW_IsDelete,
    (process_method_func)daBPW_Draw,
};

actor_process_profile_definition g_profile_BPW = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BPW,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bpw_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BPW,
    /* Actor SubMtd */ &l_daBPW_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
