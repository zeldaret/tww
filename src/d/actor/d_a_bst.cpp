/**
 * d_a_bst.cpp
 * Boss - Gohdan
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bst.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_camera.h"
#include "d/d_cc_uty.h"
#include "d/d_meter.h"
#include "d/d_snap.h"
#include "d/res/res_bst.h"
#include "d/d_s_play.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_graphic.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "JSystem/JUtility/JUTReport.h"

class daBst_HIO_c : public JORReflexible {
public:
    daBst_HIO_c();
    virtual ~daBst_HIO_c() {}
    void genMessage(JORMContext* ctx) {}

public:
    /* 0x4 */ s8 m4;
    /* 0x5 */ u8 m5;
    /* 0x6 */ u8 m6;
};

/* 000000EC-00000110       .text __ct__11daBst_HIO_cFv */
daBst_HIO_c::daBst_HIO_c() {
    m4 = -1;
    m5 = 0;
    m6 = 0;
}

static bst_class* boss;
static bst_class* hand[2];
static fpc_ProcID msg;
static s8 msg_end;
static u8 hio_set;
static daBst_HIO_c l_HIO;
static u16 set_bdl_d[3] = {BST_BDL_BST, BST_BDL_LHAND, BST_BDL_RHAND};
static u16 set_za_bdl[3] = {BST_BDL_MUNE, BST_BDL_UDEL, BST_BDL_UDER};
static u16 set_bck_d[3] = {BST_BCK_BST_SLEEP, BST_BCK_LH_SLEEP, BST_BCK_RH_SLEEP};
static u16 fly_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_FLY, BST_BCK_RH_FLY};
static u16 damage_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_DAMAGE, BST_BCK_RH_DAMAGE};
static u16 down_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_DOWN, BST_BCK_RH_DOWN};

/* 00000110-00000174       .text message_set__FP9bst_classUl */
static BOOL message_set(bst_class* i_this, unsigned long msg_no) {
    fopAc_ac_c* actor = &i_this->actor;
    if (msg == fpcM_ERROR_PROCESS_ID_e) {
        msg = fopMsgM_messageSet(msg_no, actor);
        msg_end = 0;
        return TRUE;
    }
    return FALSE;
}

/* 00000174-000001FC       .text message_cont__FP9bst_class */
static void message_cont(bst_class* i_this) {
    if (msg == fpcM_ERROR_PROCESS_ID_e) {
        return;
    }
    msg_class* msg_obj = fopMsgM_SearchByID(msg);
    if (msg_obj == NULL) {
        return;
    }
    if (msg_obj->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
        if (msg_end != 0) {
            msg_obj->mStatus = fopMsgStts_MSG_ENDS_e;
            fopMsgM_messageSendOn();
        }
    } else if (msg_obj->mStatus == fopMsgStts_BOX_CLOSED_e) {
        msg_obj->mStatus = fopMsgStts_MSG_DESTROYED_e;
        msg = fpcM_ERROR_PROCESS_ID_e;
    }
}

/* 000001FC-00000268       .text set_hand_AT__FP9bst_classUc */
static void set_hand_AT(bst_class* i_this, u8 param_2) {
    for (int i = 0; i < (s32)ARRAY_SIZE(i_this->mFingerSphs); i++) {
        if (param_2 != 0) {
            i_this->mFingerSphs[i].OnAtSetBit();
        } else {
            i_this->mFingerSphs[i].OffAtSetBit();
        }
        i_this->mFingerSphs[i].SetAtSpl(dCcG_At_Spl_UNK1);
    }
}

/* 00000268-000002C0       .text set_hand_CO__FP9bst_classUc */
static void set_hand_CO(bst_class* i_this, u8 param_2) {
    for (int i = 0; i < (s32)ARRAY_SIZE(i_this->mFingerSphs); i++) {
        if (param_2 != 0) {
            i_this->mFingerSphs[i].OnCoSetBit();
        } else {
            i_this->mFingerSphs[i].OffCoSetBit();
        }
    }
}

/* 000002C0-000003E8       .text anm_init__FP9bst_classifUcfi */
static void anm_init(bst_class* i_this, int param_2, float morf, u8 loop_mode, float play_speed, int sound_idx) {
    if (sound_idx >= 0) {
        i_this->m02B8->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bst", param_2), loop_mode, morf, play_speed, 0.0f, -1.0f, dComIfG_getObjectRes("Bst", sound_idx)
        );
    } else {
        i_this->m02B8->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bst", param_2), loop_mode, morf, play_speed, 0.0f, -1.0f, NULL);
    }
}

/* 000003E8-00000514       .text nodeCallBackHead__FP7J3DNodei */
static BOOL nodeCallBackHead(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jnt_no = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bst_class* i_this = (bst_class*)model->getUserArea();
        if (i_this != NULL) {
            cMtx_copy(model->getAnmMtx(jnt_no), *calc_mtx);
            if (jnt_no == 9) {
                cMtx_YrotM(*calc_mtx, -i_this->m2E78[1]);
            } else if (jnt_no == 12) {
                cMtx_YrotM(*calc_mtx, i_this->m2E78[1]);
            } else if (jnt_no == 10) {
                cMtx_YrotM(*calc_mtx, -i_this->m2E78[0]);
            } else if (jnt_no == 11) {
                cMtx_YrotM(*calc_mtx, i_this->m2E78[0]);
            }
            model->setAnmMtx(jnt_no, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}
/* 00000550-000005B4       .text beam_draw__FP9bst_class */
static void beam_draw(bst_class* i_this) {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0390); i++) {
        if (i_this->m04E4[i]) {
            mDoExt_modelUpdateDL(i_this->m0390[i]);
        }
    }
}

/* 000005B4-00000950       .text daBst_Draw__FP9bst_class */
static BOOL daBst_Draw(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz shadow_pos;
    cXyz temp;
    J3DModel* model_2C8;
    if (i_this->mBstPartType != bst_class::Type_HEAD_e && boss->m2E9A > 0 && boss->m2E9A < 10) {
        return TRUE;
    }
    J3DModel* model_2B8 = i_this->m02B8->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    g_env_light.setLightTevColorType(model_2B8, &actor->tevStr);
    i_this->mpTexMtxAnimator->entry(model_2B8->getModelData());
    i_this->mpTevRegAnimator->entry(model_2B8->getModelData());
    i_this->m02B8->entryDL();
    i_this->mpTexMtxAnimator->remove(model_2B8->getModelData());
    i_this->mpTevRegAnimator->remove(model_2B8->getModelData());
    J3DModel* model_388 = i_this->m0388;
    for (u16 i = 0; i < model_2B8->getModelData()->getJointNum(); i++) {
        model_388->setAnmMtx(i, model_2B8->getAnmMtx(i));
    }
    for (u16 i = 0; i < model_2B8->getModelData()->getWEvlpMtxNum(); i++) {
        model_388->setWeightAnmMtx(i, model_2B8->getWeightAnmMtx(i));
    }
    cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(0), *calc_mtx);
    temp.setall(0.0f);
    MtxPosition(&temp, &shadow_pos);
    shadow_pos.y += REG0_F(1) * 10.0f;
    i_this->mShadowID = dComIfGd_setRealShadow(i_this->mShadowID, TRUE, model_388, &shadow_pos, (REG0_F(2) * 10.0f) + 2000.0f, 0.0f, &actor->tevStr);
    model_2C8 = i_this->m02C8;
    i_this->mpBtkAnm->entry(model_2C8->getModelData());
    i_this->mpBrkAnm->entry(model_2C8->getModelData());
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->home.pos, &i_this->mEnvLight);
    g_env_light.setLightTevColorType(model_2C8, &i_this->mEnvLight);
    mDoExt_modelUpdateDL(model_2C8);
    if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
        if (i_this->m2E98 > 1) {
            mDoGph_gInf_c::setBlureRate(i_this->m2E98);
            mDoGph_gInf_c::onBlure();
        } else if (i_this->m2E98 == 1) {
            i_this->m2E98 = 0;
            mDoGph_gInf_c::offBlure();
        }
        beam_draw(i_this);
        // yup, this is a static var.
        static cXyz center_pos(0.0f, 0.0f, 0.0f);
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &center_pos, &i_this->m2F20);
        g_env_light.setLightTevColorType(i_this->m2FDC, &i_this->m2F20);
        i_this->m2FE0->entry(i_this->m2FDC->getModelData());
        mDoExt_modelUpdateDL(i_this->m2FDC);
        g_env_light.setLightTevColorType(i_this->m2FD0, &i_this->m2F20);
        i_this->m2FD8->entry(i_this->m2FD0->getModelData());
        i_this->m2FD4->entry(i_this->m2FD0->getModelData());
        mDoExt_modelUpdateDL(i_this->m2FD0);
    }
    dSnap_RegistFig(DSNAP_TYPE_BST, actor, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00000950-00000B1C       .text pos_move__FP9bst_classUc */
static void pos_move(bst_class* i_this, u8 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz vec;
    if (!param_2) {
        vec = i_this->mTargetPos - actor->current.pos;
        s16 y_angle = cM_atan2s(vec.x, vec.z);
        f32 dist = std::sqrtf(vec.x * vec.x + vec.z * vec.z);
        s16 unk_angle = -cM_atan2s(vec.y, dist);
        cLib_addCalcAngleS2(&actor->current.angle.y, y_angle, REG0_S(3) + 5, i_this->m10EC.x * i_this->m10EC.y);
        cLib_addCalcAngleS2(&actor->current.angle.x, unk_angle, REG0_S(3) + 5, i_this->m10EC.x * i_this->m10EC.y);
    }
    cLib_addCalc2(&i_this->m10EC.y, 1.0f, 1.0f, 0.05f);
    vec.x = 0.0f;
    vec.y = 0.0f;
    vec.z = actor->speedF;
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    MtxPosition(&vec, &actor->speed);
    actor->current.pos += actor->speed;
}

static u16 start_bck_d[] = {BST_BCK_BST_START, BST_BCK_LH_START, BST_BCK_RH_START};
static u16 start2_bck_d[] = {0, BST_BCK_LH_START2, BST_BCK_RH_START2};
static u16 start_smoke_name[] = {dPa_name::ID_SCENE_A1DE, dPa_name::ID_SCENE_A1DC, dPa_name::ID_SCENE_A1DD};

/* 00000B1C-00000E58       .text stay__FP9bst_class */
static void stay(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    i_this->mState = 10;
    switch (i_this->mDamage) {
    case 0:
        anm_init(i_this, set_bck_d[i_this->mBstPartType], 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mDamage++;
        break;
    case 2:
        anm_init(i_this, start_bck_d[i_this->mBstPartType], 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mDamage++;
        break;
    case 4: {
        cXyz vec;
        vec.x = 0.0f;
        vec.y = 0.0f;
        if (i_this->mBstPartType != bst_class::Type_HEAD_e) {
            anm_init(i_this, start2_bck_d[i_this->mBstPartType], 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            vec.z = REG0_F(11) + 400.0f;
        } else {
            vec.z = 10000.0f;
        }
        dComIfGp_particle_setToon(
            start_smoke_name[i_this->mBstPartType], &actor->current.pos, &actor->current.angle, NULL, 0xB9, &i_this->mPa_smokeEcallBack, fopAcM_GetRoomNo(actor)
        );
        dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        boss->m2ECC = REG0_F(10) + 15.0f;
        i_this->mDamage++;
        cMtx_YrotS(*calc_mtx, actor->current.angle.y);
        cXyz pos_vec;
        MtxPosition(&vec, &pos_vec);
        i_this->mTargetPos = actor->current.pos + pos_vec;
        i_this->m10FC[3] = 0xF;
        // fallthrough
    }
    case 5:
        if (i_this->mBstPartType != bst_class::Type_HEAD_e && i_this->m10FC[3] != 0) {
            for (s32 i = 2; i <= 16; i++) {
                cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(i), *calc_mtx);
                cXyz pos_vec;
                cXyz vec(0.0f, 0.0f, 0.0f);
                MtxPosition(&vec, &pos_vec);
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_81D5, &pos_vec);
            }
        }
        cLib_addCalc2(&actor->current.pos.x, i_this->mTargetPos.x, 0.05f, 10.0f);
        cLib_addCalc2(&actor->current.pos.z, i_this->mTargetPos.z, 0.05f, 10.0f);
        break;
    case 1:
    case 3:
        return;
    }
}

static u16 fly_btk_d[] = {BST_BTK_BST, BST_BTK_LHAND, BST_BTK_RHAND};
static u16 fly_brk_d[] = {BST_BRK_BST, BST_BRK_LHAND, BST_BRK_RHAND};
static u16 damage_btk_d[] = {BST_BTK_BST_DAMAGE, BST_BTK_LH_DAMAGE, BST_BTK_RH_DAMAGE};
static u16 damage_brk_d[] = {BST_BRK_BST_DAMAGE, BST_BRK_LH_DAMAGE, BST_BRK_RH_DAMAGE};

/* 00000E58-000014E8       .text fly__FP9bst_class */
static void fly(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (i_this->mBstPartType != bst_class::Type_HEAD_e && i_this->m10D8 == 6) {
        actor->health = 4;
    }
    i_this->m10D8 = 1;
    if (i_this->mState == 0) {
        set_hand_CO(i_this, 1);
    }
    if (boss->m2E9A != 0 || ((i_this->mUpdateLastFacingDirIfMultipleOf32 & 0x1F) == 0 && cM_rndF(1.0f) < 0.5f)) {
        i_this->mLastCheckedPlayerFacingDir = player->shape_angle.y;
    }
    switch (i_this->mDamage) {
    case 0: {
        anm_init(i_this, fly_bck_d[i_this->mBstPartType], 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", damage_brk_d[i_this->mBstPartType]);
        i_this->mpTevRegAnimator->init(i_this->m02B8->getModel()->getModelData(), reg_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        i_this->mpTevRegAnimator->setFrame(REG0_S(8) + 0x1D);
        i_this->m02D4 = 1;
        i_this->m02C4 = 1;
        i_this->mDamage++;
        break;
    }
    case 1: {
        J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", fly_brk_d[i_this->mBstPartType]);
        i_this->mpTevRegAnimator->init(i_this->m02B8->getModel()->getModelData(), reg_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
        J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", fly_btk_d[i_this->mBstPartType]);
        i_this->mpTexMtxAnimator->init(i_this->m02B8->getModel()->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
        i_this->mDamage++;
        i_this->m10EC.y = 0.0f;
        // fallthrough
    }
    case 2: {
        cMtx_YrotS(*calc_mtx, i_this->mLastCheckedPlayerFacingDir);
        cXyz vec;
        vec.z = REG0_F(4) + 800.0f;
        vec.y = REG0_F(3) + 200.0f;
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            vec.x = 0.0f;
            vec.z = REG0_F(4) + 1000.0f;
            if (boss->m2E7C == 11) {
                vec.y = REG0_F(3) + 350.0f;
            }
        } else if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
            vec.x = -(REG0_F(2) + 800.0f);
        } else if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
            vec.x = REG0_F(2) + 800.0f;
        }
        cXyz pos_vec;
        MtxPosition(&vec, &pos_vec);
        i_this->mTargetPos = player->current.pos + pos_vec;
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            vec = i_this->mTargetPos;
            vec.y = 0.0f;
            f32 dist = vec.abs();
            if (dist > REG0_F(9) + 1350.0f) {
                f32 tmp = (REG0_F(9) + 1350.0f) / dist;
                i_this->mTargetPos.x *= tmp;
                i_this->mTargetPos.z *= tmp;
            }
        }
        vec = i_this->mTargetPos - actor->current.pos;
        if (vec.abs() > REG0_F(12) + 300.0f) {
            f32 speed_target;
            if (i_this->mBstPartType == bst_class::Type_HEAD_e && boss->m2E7C == 11) {
                speed_target = 10.0f;
            } else {
                speed_target = 30.0f;
            }
            cLib_addCalc2(&actor->speedF, speed_target, 1.0f, REG0_F(13) + 2.0f);
        } else {
            cLib_addCalc0(&actor->speedF, 1.0f, REG0_F(14) + 1.0f);
        }
        i_this->m10EC.x = REG0_F(5) + 1500.0f;
        cLib_addCalcAngleS2(&actor->shape_angle.y, fopAcM_searchPlayerAngleY(actor), 10, 0x400);
        s16 target_x;
        if (i_this->mBstPartType == bst_class::Type_HEAD_e && boss->m2E7C == 11) {
            target_x = 0;
        } else {
            target_x = 3000;
        }
        cLib_addCalcAngleS2(&actor->shape_angle.x, target_x, 10, 256);
        cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 8, 512);
        cLib_addCalc2(&i_this->m10EC.z, REG0_F(11) + 50.0f, 1.0f, 2.0f);
        break;
    }
    }
    pos_move(i_this, 0);
    if (i_this->mBstPartType == bst_class::Type_HEAD_e && i_this->mBombArrowDropTimer == 0 && (dComIfGs_getArrowNum() == 0 || dComIfGs_getBombNum() == 0)) {
        i_this->mBombArrowDropTimer = 600;
        i_this->mActionType = bst_class::ACTION_HANA_DEMO_e;
        i_this->mDamage = 0;
    }
}

static u16 downa_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_GOO, BST_BCK_RH_GOO};

/* 000014E8-00001C14       .text down_attack__FP9bst_class */
static void down_attack(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    bool bVar2 = true;
    s8 bVar4 = false;
    cXyz target_diff;
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x200);
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage += 1;
        i_this->m10EC.y = 0.0f;
        i_this->mTargetPos = player->current.pos;
        i_this->mTargetPos.y += REG0_F(7) + 300.0f;
        i_this->m10FC[0] = 100;
        // fallthrough
    case 1: {
        cLib_addCalc2(&actor->speedF, 40.0f, 1.0f, REG0_F(13) + 1.0f);
        i_this->m10EC.x = REG0_F(5) + 2000.0f;
        target_diff = i_this->mTargetPos - actor->current.pos;
        if (target_diff.abs() < REG0_F(12) + 200.0f || i_this->m10FC[0] == 0) {
            i_this->mDamage++;
        }
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x400);
        break;
    }
    case 2: {
        bVar2 = false;
        cLib_addCalc2(&actor->current.pos.x, i_this->mTargetPos.x, 0.5f, std::abs(actor->speed.x));
        cLib_addCalc2(&actor->current.pos.y, i_this->mTargetPos.y, 0.5f, std::abs(actor->speed.y));
        cLib_addCalc2(&actor->current.pos.z, i_this->mTargetPos.z, 0.5f, std::abs(actor->speed.z));
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x4000);
        target_diff = i_this->mTargetPos - actor->current.pos;
        if (target_diff.abs() < REG0_F(13) + 50.0f) {
            anm_init(i_this, downa_bck_d[i_this->mBstPartType], 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mDamage++;
            actor->speed.y = 0.0f;
            i_this->m10FC[0] = 30;
            if (REG0_S(0) == 1) {
                i_this->m2E6E = actor->shape_angle.y + 0x4000;
            } else {
                i_this->m2E6E = actor->shape_angle.y - 0x4000;
            }
            if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
                i_this->mFacingDir = 0x4000;
            } else {
                i_this->mFacingDir = -0x4000;
            }
            fopAcM_seStartCurrent(actor, JA_SE_CM_BST_HAND_GRIP, 0);
        }
        break;
    }
    case 3:
        bVar2 = false;
        cLib_addCalc2(&i_this->m1114, -200.0f, 1.0f, 25.0f);
        cLib_addCalc2(&actor->current.pos.x, i_this->mTargetPos.x, 0.5f, std::abs(actor->speed.x));
        cLib_addCalc2(&actor->current.pos.z, i_this->mTargetPos.z, 0.5f, std::abs(actor->speed.z));
        cLib_addCalcAngleS2(&actor->shape_angle.z, i_this->mFacingDir, 4, 0x1000);
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m2E6E, 4, 0x1000);
        actor->current.pos.y += actor->speed.y;
        if (i_this->m10FC[0] == 0) {
            set_hand_AT(i_this, 1);
            actor->speed.y -= REG0_F(3) + 60.0f;
            if (actor->current.pos.y <= REG0_F(4) + 150.0f) {
                actor->current.pos.y = REG0_F(4) + 150.0f;
                actor->speed.y = 0.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->m112A = REG0_S(7) + 10;
                fopAcM_seStartCurrent(actor, JA_SE_CM_BST_1_HAND_ATTACK, 0);
                i_this->mDamage++;
                i_this->m10FC[0] = 30;
                cXyz particle_pos;
                particle_pos = actor->current.pos;
                particle_pos.y = 1.0f;
                dComIfGp_particle_setProjection(dPa_name::ID_SCENE_C1D6, &particle_pos);
                dComIfGp_particle_setToon(dPa_name::ID_SCENE_A1D8, &particle_pos, NULL, NULL, 0xB9, &i_this->mPa_smokeEcallBack, fopAcM_GetRoomNo(actor));
            }
        } else {
            actor->speed.y += REG0_F(14) + 0.5f;
        }
        break;
    case 4:
        bVar2 = false;
        cLib_addCalc2(&i_this->m1114, -200.0f, 1.0f, 25.0f);
        if (i_this->m10FC[0] == 0) {
            bVar4 = true;
        }
        break;
    }
    if (bVar2) {
        pos_move(i_this, 0);
    }
    if (bVar4 || i_this->mAcch.ChkWallHit()) {
        i_this->mActionType = bst_class::ACTION_FLY_e;
        i_this->mDamage = 0;
        fopAcM_seStartCurrent(actor, JA_SE_CM_BST_HAND_GRIP_OPEN, 0);
        if (!bVar4) {
            s32 hand_index = 2 - i_this->mBstPartType;
            if (hand[hand_index]->mActionType == bst_class::ACTION_DOWN_ATTACK_e) {
                hand[hand_index]->mActionType = bst_class::ACTION_FLY_e;
                hand[hand_index]->mDamage = 0;
                hand[hand_index]->actor.speedF = 0.0f;
            }
        }
    }
}

static u16 paa_bck_d[] = {0, BST_BCK_LH_PAA, BST_BCK_RH_PAA};

/* 00001C14-000023C8       .text paa_attack__FP9bst_class */
static void paa_attack(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar6;
    cXyz local_38;
    cXyz cStack_44;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bool r27;
    s8 r26;
    r27 = true;
    r26 = false;
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x200);
    cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 10, 0x400);
    cLib_addCalc2(&i_this->m1118, -40.0f, 1.0f, 10.0f);
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage += 1;
        i_this->m10EC.y = 0.0f;
        i_this->m111C = player->shape_angle.y;
        anm_init(i_this, paa_bck_d[i_this->mBstPartType], 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m10FC[0] = REG0_S(1) + 0x50;
        // fallthrough
    case 1:
        local_38 = i_this->mTargetPos - actor->current.pos;
        if (local_38.abs() > REG0_F(0xc) + 200.0f) {
            cLib_addCalc2(&actor->speedF, 40.0f, 1.0f, REG0_F(0xd) + 2.0f);
        } else {
            cLib_addCalc0(&actor->speedF, 1.0f, (REG0_F(0xd) + 2.0f));
        }
        i_this->m10EC.x = REG0_F(5) + 8000.0f;
        cMtx_YrotS(*calc_mtx, (int)i_this->m111C);
        if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
            local_38.x = -(REG0_F(2) + 700.0f);
            sVar6 = 0x4000;
        } else {
            local_38.x = REG0_F(2) + 700.0f;
            sVar6 = -0x4000;
        }
        local_38.y = REG0_F(3);
        local_38.z = REG0_F(4);
        MtxPosition(&local_38, &cStack_44);
        i_this->mTargetPos = player->current.pos + cStack_44;
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m111C + sVar6, 10, 0x800);
        if (i_this->m10FC[0] == 0) {
            i_this->mDamage++;
            i_this->mTargetPos = player->current.pos;
            sVar6 = fopAcM_searchPlayerAngleY(actor);
            actor->current.angle.y = sVar6;
        }
        break;
    case 2:
        cLib_addCalc2(&actor->speedF, REG0_F(0xe) + 140.0f, 1.0f, REG0_F(0xf) + 10.0f);
        i_this->m10EC.x = REG0_F(5) + 10000.0f;
        local_38 = i_this->mTargetPos - actor->current.pos;
        if (local_38.abs() < REG0_F(0x10) + 200.0f) {
            i_this->mDamage++;
            i_this->m10FC[0] = REG0_S(7) + 0x1e;
        }
        break;
    case 3:
        r27 = false;
        if (i_this->m10FC[0] >= 0x1C) {
            if (i_this->m10FC[0] == 0x1c) {
                if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
                    fopAcM_seStartCurrent(actor, JA_SE_CM_BST_HAND_CLAP, 0);
                    csXyz local_70 = actor->shape_angle;
                    local_70.y += 0x4000;
                    dComIfGp_particle_setProjection(dPa_name::ID_SCENE_C1D7, &i_this->mTargetPos, &local_70);
                    dComIfGp_particle_setToon(
                        dPa_name::ID_SCENE_A1DA, &i_this->mTargetPos, &local_70, NULL, 0xB9, &i_this->mPa_smokeEcallBack, fopAcM_GetRoomNo(actor)
                    );
                }
                i_this->m112A = REG0_S(8) + 5;
            }
            set_hand_AT(i_this, 1);
        }
        if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
            sVar6 = 0x4000;
        } else {
            sVar6 = -0x4000;
        }
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m111C + sVar6, 1, 0x1000);
        cLib_addCalc2(&actor->current.pos.x, i_this->mTargetPos.x, 1.0f, std::fabsf(actor->speed.x));
        cLib_addCalc2(&actor->current.pos.z, i_this->mTargetPos.z, 1.0f, std::fabsf(actor->speed.z));
        if (i_this->m10FC[0] == 0) {
            i_this->mDamage++;
            actor->speedF = 0.0f;
            i_this->m10FC[0] = REG0_S(3) + 0x1e;
            actor->current.angle.y += 0x8000;
            cMtx_YrotS(*calc_mtx, (int)i_this->m111C);
            if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
                local_38.x = -(REG0_F(2) + 4000.0f);
            } else {
                local_38.x = REG0_F(2) + 4000.0f;
            }
            local_38.y = REG0_F(3);
            local_38.z = REG0_F(4);
            MtxPosition(&local_38, &cStack_44);
            i_this->mTargetPos += cStack_44;
        }
        break;
    case 4:
        cLib_addCalc2(&actor->speedF, 40.0f, 1.0f, REG0_F(0xd) + 1.0f);
        i_this->m10EC.x = REG0_F(5) + 2000.0f;
        if (i_this->m10FC[0] == 0) {
            r26 = true;
        }
        break;
    }
    if (r27) {
        pos_move(i_this, 0);
    }
    if (actor->current.pos.y <= REG0_F(4) + 30.0f) {
        actor->current.pos.y = REG0_F(4) + 30.0f;
    }
    if ((r26) || (i_this->mAcch.ChkWallHit())) {
        i_this->mActionType = bst_class::ACTION_FLY_e;
        i_this->mDamage = 0;
        i_this->mStateTimer = (s16)(int)(cM_rndF(100.0f) + 100.0f);
        if (!r26) {
            s32 hand_index = 2 - i_this->mBstPartType;
            if (hand[hand_index]->mActionType == bst_class::ACTION_PAA_ATTACK_e) {
                hand[hand_index]->mActionType = bst_class::ACTION_FLY_e;
                hand[hand_index]->mDamage = 0;
                hand[hand_index]->mStateTimer = (s16)(int)(cM_rndF(100.0f) + 100.0f);
            }
        }
    }
}

static u16 awasu_bck_d[] = {0, BST_BCK_LH_AWASE, BST_BCK_RH_AWASU};

/* 00002404-00002E08       .text kumi_attack__FP9bst_class */
static void kumi_attack(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar5;
    cXyz local_38;
    cXyz cStack_44;
    cXyz local_50;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bool r27;
    s8 r26;
    r27 = true;
    r26 = false;
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x200);
    cLib_addCalc2(&i_this->m1110, 30.0f, 1.0f, 10.0f);
    cLib_addCalc2(&i_this->m1118, -80.0f, 1.0f, 10.0f);
    cLib_addCalc2(&i_this->m1114, -200.0f, 1.0f, 30.0f);
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage++;
        i_this->m10EC.y = 0.0f;
        i_this->m111C = player->shape_angle.y;
        anm_init(i_this, awasu_bck_d[i_this->mBstPartType], 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m10FC[0] = REG0_S(1) + 0x46;
        // fallthrough
    case 1:
        local_38 = i_this->mTargetPos - actor->current.pos;
        if (local_38.abs() > REG0_F(0xc) + 200.0f) {
            cLib_addCalc2(&actor->speedF, 40.0f, 1.0f, REG0_F(0xd) + 2.0f);
        } else {
            cLib_addCalc0(&actor->speedF, 1.0f, (REG0_F(0xd) + 2.0f));
        }
        i_this->m10EC.x = REG0_F(5) + 8000.0f;
        cMtx_YrotS(*calc_mtx, (int)i_this->m111C);
        if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
            local_38.x = -(REG0_F(2) + 500.0f);
            sVar5 = 0x4000;
        } else {
            local_38.x = REG0_F(2) + 500.0f;
            sVar5 = -0x4000;
        }
        local_38.y = REG0_F(3) + 400.0f;
        local_38.z = 0.0f;
        MtxPosition(&local_38, &cStack_44);
        i_this->mTargetPos = player->current.pos + cStack_44;
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m111C + sVar5, 10, 0x800);
        if (i_this->m10FC[0] == 0) {
            i_this->mDamage++;
            i_this->mTargetPos = player->current.pos;
            i_this->mTargetPos.y += REG0_F(3) + 500.0f;
            sVar5 = fopAcM_searchPlayerAngleY(actor);
            actor->current.angle.y = sVar5;
        }
        break;
    case 2:
        cLib_addCalc2(&actor->speedF, REG0_F(0xe) + 100.0f, 1.0f, REG0_F(0xf) + 8.0f);
        i_this->m10EC.x = REG0_F(5) + 10000.0f;
        local_38 = i_this->mTargetPos - actor->current.pos;
        if (local_38.abs() < REG0_F(0x10) + 100.0f) {
            i_this->mDamage++;
        }
        break;
    case 3:
        r27 = false;
        if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
            sVar5 = 0x4000;
        } else {
            sVar5 = -0x4000;
        }
        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m111C + sVar5, 1, 0x1000);
        cLib_addCalc2(&actor->current.pos.x, i_this->mTargetPos.x, 1.0f, std::fabsf(actor->speed.x));
        cLib_addCalc2(&actor->current.pos.y, i_this->mTargetPos.y, 1.0f, std::fabsf(actor->speed.y) + 10.0f);
        cLib_addCalc2(&actor->current.pos.z, i_this->mTargetPos.z, 1.0f, std::fabsf(actor->speed.z));
        local_38 = hand[0]->actor.current.pos - hand[1]->actor.current.pos;
        if (local_38.abs() < 1.0f) {
            i_this->mDamage++;
            i_this->m10FC[0] = REG0_S(3) + 10;
            fopAcM_seStartCurrent(actor, JA_SE_CM_BST_HAND_SHAKE, 0);
            actor->speed.y = 0.0f;
        }
        break;
    case 4:
        r27 = false;
        actor->current.pos.y = actor->current.pos.y + actor->speed.y;
        if (i_this->m10FC[0] <= 1) {
            if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
                i_this->mFacingDir = 0x4000;
            } else {
                i_this->mFacingDir = -0x4000;
            }
            cLib_addCalcAngleS2(&actor->shape_angle.z, i_this->mFacingDir, 1, 0x1000);
            set_hand_AT(i_this, 1);
            actor->speed.y = actor->speed.y - (REG0_F(3) + 60.0f);
            if (actor->current.pos.y <= REG0_F(4) + 150.0f) {
                actor->current.pos.y = REG0_F(4) + 150.0f;
                actor->speed.y = 0.0f;
                if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
                    local_50 = i_this->mTargetPos;
                    local_50.y = 1.0f;
                    dComIfGp_particle_setProjection(dPa_name::ID_SCENE_C1D6, &local_50);
                    dComIfGp_particle_setToon(dPa_name::ID_SCENE_A1D9, &local_50, NULL, NULL, 0xb9, &i_this->mPa_smokeEcallBack, fopAcM_GetRoomNo(actor));
                    dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                    fopAcM_seStartCurrent(actor, JA_SE_CM_BST_2_HAND_ATTACK, 0);
                }
                i_this->m112A = REG0_S(7) + 10;
                i_this->mDamage++;
                i_this->m10FC[0] = 0x28;
            }
        } else {
            actor->speed.y += REG0_F(0xe) + 1.0f;
            if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
                i_this->mFacingDir = -0x1000;
            } else {
                i_this->mFacingDir = 0x1000;
            }
            cLib_addCalcAngleS2(&actor->shape_angle.z, i_this->mFacingDir, 10, 0x200);
        }
        break;
    case 5:
        r27 = false;
        if (i_this->m10FC[0] == 0) {
            r26 = true;
        }
        break;
    }
    if (r27) {
        pos_move(i_this, 0);
    }
    if ((r26) || (i_this->mAcch).ChkWallHit()) {
        i_this->mActionType = bst_class::ACTION_FLY_e;
        i_this->mDamage = 0;
        actor->speedF = 0.0f;
        actor->current.angle.y = actor->current.angle.y + 0x8000;
        i_this->mStateTimer = (s16)(int)(cM_rndF(100.0f) + 100.0f);
        i_this->mState = 0x28;
        fopAcM_seStartCurrent(actor, JA_SE_CM_BST_HAND_RELEASE, 0);
        if (!r26) {
            s32 hand_index = 2 - i_this->mBstPartType;
            if (hand[hand_index]->mActionType == bst_class::ACTION_KUMI_ATTACK_e) {
                hand[hand_index]->mActionType = bst_class::ACTION_FLY_e;
                hand[hand_index]->mDamage = 0;
                hand[hand_index]->actor.speedF = 0.0f;
                hand[hand_index]->actor.current.angle.y += 0x8000;
                hand[hand_index]->mStateTimer = (s16)(int)(cM_rndF(100.0f) + 100.0f);
                hand[hand_index]->mState = 0x28;
                fopAcM_seStartCurrent(&hand[hand_index]->actor, JA_SE_CM_BST_HAND_RELEASE, 0);
            }
        }
    }
}

/* 00002E08-0000318C       .text harai_attack__FP9bst_class */
static void harai_attack(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar2;
    f32 dVar4;
    cXyz local_34;

    u8 cVar3 = 0;
    set_hand_CO(i_this, 1);
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x200);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x1000);
    if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
        i_this->mFacingDir = 0x4000;
        dVar4 = -(REG0_F(0xb) + 50.0f);
    } else {
        i_this->mFacingDir = -0x4000;
        dVar4 = (REG0_F(0xb) + 50.0f);
    }
    cLib_addCalcAngleS2(&actor->shape_angle.z, i_this->mFacingDir, 8, 0x400);
    cLib_addCalc2(&i_this->m1110, dVar4, 1.0f, 10.0f);
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage++;
        i_this->m10EC.y = 0.0f;
        actor->speedF = 0.0f;
        i_this->m10FC[0] = REG0_S(5) + 0x14;
        sVar2 = fopAcM_searchPlayerAngleY(actor);
        actor->current.angle.y = sVar2;
        anm_init(i_this, fly_bck_d[i_this->mBstPartType], 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        // fallthrough
    case 1:
        cVar3 = 1;
        cLib_addCalc2(&actor->speedF, 60.0f, 1.0f, REG0_F(0xd) + 2.0f);
        i_this->m10EC.x = REG0_F(5) + 2000.0f;
        if (i_this->m10FC[0] == 0) {
            i_this->mDamage++;
            i_this->m10FC[0] = REG0_S(6) + 0x3c;
        }
        break;
    case 2:
        cVar3 = 1;
        sVar2 = (REG0_S(4) + 0x15e);
        if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
            actor->current.angle.y = actor->current.angle.y + sVar2;
        } else {
            actor->current.angle.y = actor->current.angle.y - sVar2;
        }
        local_34 = actor->current.pos;
        local_34.y = 0.0f;
        if (i_this->m10FC[0] != 0) {
            if (!(local_34.abs() > 1700.0f)) {
                break;
            }
        }
        i_this->m10FC[0] = 0x1e;
        i_this->mDamage++;
        break;
    case 3:
        cVar3 = 1;
        cLib_addCalc0(&actor->speedF, 1.0f, (REG0_F(0xd) + 3.0f));
        if (i_this->m10FC[0] == 0) {
            i_this->mActionType = bst_class::ACTION_FLY_e;
            i_this->mDamage = 0;
            i_this->mStateTimer = (s16)(int)(cM_rndF(60.0f) + 60.0f);
        }
        break;
    }
    actor->current.angle.x = 0;
    cLib_addCalc2(&actor->current.pos.y, REG0_F(7) + 180.0f, 0.2f, 10.0f);
    pos_move(i_this, cVar3);
}

static u16 sleep_btk_d[] = {BST_BCK_BST_SLEEP, BST_BTK_LH_END, BST_BTK_RH_END};
static u16 sleep_brk_d[] = {BST_BRK_BST, BST_BRK_LH_END, BST_BRK_RH_END};

/* 0000318C-00003470       .text sleep__FP9bst_class */
static void sleep(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->m10D8 = 6;
    set_hand_CO(i_this, 1);
    i_this->mState = 10;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    cLib_addCalc2(&i_this->m10EC.z, REG0_F(11) + 50.0f, 1.0f, 2.0f);
    switch (i_this->mDamage) {
    case 0: {
        anm_init(i_this, down_bck_d[i_this->mBstPartType], 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", sleep_brk_d[i_this->mBstPartType]);
        i_this->mpTevRegAnimator->init(i_this->m02B8->getModel()->getModelData(), reg_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", sleep_btk_d[i_this->mBstPartType]);
        i_this->mpTexMtxAnimator->init(i_this->m02B8->getModel()->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        i_this->mDamage++;
        fopAcM_seStart(actor, JA_SE_CM_BST_HAND_EYE_CLOSE, 0);
        // fallthrough
    }
    case 1:
        if (i_this->m10FC[0] == 0) {
            i_this->mTargetPos.x = cM_rndFX(1500.0f);
            i_this->mTargetPos.y = cM_rndF(200.0f) + 600.0f;
            if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
                i_this->mTargetPos.y += 350.0f;
            }
            i_this->mTargetPos.z = cM_rndFX(1500.0f);
            i_this->m10FC[0] = cM_rndF(30.0f);
        }
        i_this->m10EC.x = REG0_F(5) + 500.0f;
        actor->speedF = REG0_F(6) + 10.0f;
        if (i_this->m10FC[1] == 0) {
            i_this->mActionType = bst_class::ACTION_FLY_e;
            i_this->mDamage = 0;
            fopAcM_seStart(actor, JA_SE_CM_BST_HAND_EYE_OPEN, 0);
        }
    default:
        return pos_move(i_this, 0);
    }
}

/* 00003470-000035BC       .text beam_set__FP9bst_class */
static void beam_set(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    for (s32 i = 0; i < 10; i++) {
        if (i_this->m04E4[i]) {
            continue;
        }
        i_this->m04E4[i] = 1;
        cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(REG0_S(5) + 3), *calc_mtx);
        cXyz vec(0.0f, 0.0f, 0.0f);
        MtxPosition(&vec, &i_this->m03B8[i]);
        i_this->m04A8[i] = actor->shape_angle;
        cMtx_YrotS(*calc_mtx, i_this->m04A8[i].y);
        cMtx_XrotM(*calc_mtx, i_this->m04A8[i].x);
        vec.set(0.0f, 0.0f, REG0_F(12) + 160.0f);
        MtxPosition(&vec, &i_this->m0430[i]);
        i_this->m10A8[i] = 1.0f;
        return;
    }
}

static u16 charge_e_name[] = {dPa_name::ID_SCENE_81C2, dPa_name::ID_SCENE_81C3};

/* 000035BC-00003B94       .text beam_attack__FP9bst_class */
static void beam_attack(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    bool bVar3 = false;
    i_this->m2E74[0] = 10;
    i_this->m2E74[1] = 10;
    if (i_this->mBombArrowDropTimer < 120) {
        i_this->mBombArrowDropTimer = 120;
    }
    cXyz actor_vec = player->current.pos - actor->current.pos;
    actor_vec.y += i_this->m10D0;
    s16 angle = cM_atan2s(actor_vec.x, actor_vec.z);
    cLib_addCalcAngleS2(&actor->shape_angle.y, angle, 4, 0x800);
    f32 fVar13 = std::sqrtf(actor_vec.x * actor_vec.x + actor_vec.z * actor_vec.z);
    cLib_addCalcAngleS2(&actor->shape_angle.x, -cM_atan2s(actor_vec.y, fVar13), 4, 0x800);
    cLib_addCalc2(&actor->current.pos.y, REG0_F(0xb) + 400.0f, 0.05f, 30.0f);
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage++;
        anm_init(i_this, 7, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_seStart(actor, JA_SE_CM_BST_MOUTH_OPEN, 0);
        break;
    case 1:
        if (i_this->m02B8->isStop()) {
            i_this->mDamage++;
            anm_init(i_this, 8, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m10FC[0] = 0x2d;
            for (s32 i = 0; i < 2; i++) {
                i_this->m2ED8[i] = dComIfGp_particle_set(charge_e_name[i], &actor->current.pos);
            }
        }
        break;
    case 2:
        fopAcM_seStart(actor, JA_SE_CM_BST_BEAM_PREPARE, 0);
        i_this->mRoomState = 5;
        if (i_this->m10FC[0] == 0) {
            for (s32 i = 0; i < 2; i++) {
                if (i_this->m2ED8[i] != NULL) {
                    i_this->m2ED8[i]->becomeInvalidEmitter();
                    i_this->m2ED8[i] = NULL;
                }
            }
            i_this->mDamage++;
            anm_init(i_this, 6, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m10FC[0] = REG0_S(4) + 0x32;
        }
        break;
    case 3:
        cLib_addCalc2(&i_this->m10D0, REG0_F(6), 0.1f, REG0_F(5) + 20.0f);
        if ((i_this->m10FC[0] & 3U) == 0) {
            i_this->mRoomState = 6;
            beam_set(i_this);
            fopAcM_seStart(actor, JA_SE_CM_BST_BEAM_FIRE, 0);
        }
        if (i_this->m10FC[0] == 0) {
            bVar3 = true;
        }
        break;
    }
    f32 dist = fopAcM_searchActorDistance(actor, dComIfGp_getPlayer(0));
    if (dist < REG0_F(9) + 500.0f || bVar3) {
        i_this->mRoomState = 8;
        i_this->mActionType = bst_class::ACTION_FLY_e;
        i_this->mDamage = 0;
        actor->speedF = 0.0f;
        fopAcM_seStart(actor, JA_SE_CM_BST_MOUTH_CLOSE, 0);
        s16 sVar6;
        if (actor->health == 0) {
            sVar6 = cM_rndF(50.0f) + 100.0f;
        } else if (actor->health == 1) {
            sVar6 = cM_rndF(70.0f) + 120.0f;
        } else if (actor->health == 2) {
            sVar6 = cM_rndF(80.0f) + 140.0f;
        } else if (actor->health == 3) {
            sVar6 = cM_rndF(90.0f) + 150.0f;
        } else {
            sVar6 = cM_rndF(100.0f) + 150.0f;
        }
        i_this->m2E7E[1] = sVar6;
    }
    for (s32 i = 0; i < 2; i++) {
        JPABaseEmitter* emitter = i_this->m2ED8[i];
        if (emitter != NULL) {
            emitter->setGlobalRTMatrix(i_this->m02B8->getModel()->getAnmMtx(0));
        }
    }
}

/* 00003B94-00003DD8       .text damage__FP9bst_class */
static void damage(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mState = 10;
    switch (i_this->mDamage) {
    default:
        return;
    case 0: {
        if (i_this->mBstPartType != bst_class::Type_HEAD_e) {
            anm_init(i_this, damage_bck_d[i_this->mBstPartType], 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", damage_brk_d[i_this->mBstPartType]);
        i_this->mpTevRegAnimator->init(i_this->m02B8->getModel()->getModelData(), reg_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", damage_btk_d[i_this->mBstPartType]);
        i_this->mpTexMtxAnimator->init(i_this->m02B8->getModel()->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        i_this->mDamage++;
        i_this->m10FC[0] = 30;
        break;
    }
    case 1:
        break;
    }
    if (i_this->m10FC[0] == 0) {
        if (i_this->mBstPartType != bst_class::Type_HEAD_e && actor->health <= 0) {
            i_this->mActionType = bst_class::ACTION_SLEEP_e;
            i_this->m10FC[1] = 300;
            if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
                if (hand[0]->mActionType != bst_class::ACTION_SLEEP_e) {
                    mDoAud_bgmStart(JA_BGM_UNK_120);
                }
            } else if (hand[1]->mActionType != bst_class::ACTION_SLEEP_e) {
                mDoAud_bgmStart(JA_BGM_UNK_121);
            }
        } else {
            i_this->mActionType = bst_class::ACTION_FLY_e;
            actor->speedF = 0.0f;
        }
        i_this->mDamage = 0;
    }
}

/* 00003DD8-00003EC4       .text bom_eat_check__FP9bst_class */
static BOOL bom_eat_check(bst_class* i_this) {
    if (i_this->mHandHurtCyl.ChkCoHit()) {

        cCcD_Obj* hit_obj = i_this->mHandHurtCyl.GetCoHitObj();
        if (hit_obj != NULL) {
            fopAc_ac_c* actor = (fopAc_ac_c*)hit_obj->GetAc();
            daBomb_c* bomb = (daBomb_c*)actor;
            if (actor != NULL && fopAcM_GetName(actor) == PROC_BOMB && bomb->getBombCheck_Flag() == 0 && bomb->getBombRestTime() > 1) {
                i_this->mBombId = fopAcM_GetID(bomb);
                bomb->setBombCheck_Flag();
                bomb->change_state(daBomb_c::STATE_2);
                bomb->setBombNoHit();
                bomb->setBombRestTime(200);
                return TRUE;
            }
        }
    }
    return FALSE;
}

/* 00003EC4-000049A8       .text head_damage__FP9bst_class */
static void head_damage(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz v;
    f32 dist;
    static u16 bomb_eff_name[] = {dPa_name::ID_SCENE_81E4, dPa_name::ID_SCENE_81E5, dPa_name::ID_SCENE_81E6, dPa_name::ID_SCENE_81E7};

    i_this->mState = 10;
    i_this->m2E74[0] = 10;
    i_this->m2E74[1] = 10;
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 8, 512);
    cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 8, 512);
    cLib_addCalc0(&i_this->m10EC.z, 1.0f, 5.0f);
    switch (i_this->mDamage) {
    case 0: {
        i_this->mDamage++;
        i_this->m10FC[0] = 40;
        actor->speedF = 0.0f;
        actor->speed.y = 0.0f;
        J3DAnmTevRegKey* key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_BST_END);
        i_this->mpTevRegAnimator->init(i_this->m02B8->getModel()->getModelData(), key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_BST_END);
        i_this->mpTexMtxAnimator->init(i_this->m02B8->getModel()->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        fopAcM_seStart(actor, JA_SE_CM_BST_HEAD_EYE_CLOSE, 0);
        mDoAud_bgmStart(JA_BGM_UNK_123);
        // fallthrough
    }
    case 1:
        v = actor->current.pos;
        v.y = 0.0f;
        dist = v.abs();
        if (dist > REG0_F(9) + 1350.0f) {
            dist = (REG0_F(9) + 1350.0f) / dist;
            cLib_addCalc2(&actor->current.pos.x, v.x * dist, 0.2f, 30.0f);
            cLib_addCalc2(&actor->current.pos.z, v.z * dist, 0.2f, 30.0f);
        }
        if (i_this->m10FC[0] == 0) {
            actor->current.pos.y += actor->speed.y;
            actor->speed.y -= REG0_F(13) + 5.0f;
            if (actor->current.pos.y <= REG0_F(14)) {
                actor->current.pos.y = REG0_F(14);
                dComIfGp_getVibration().StartShock(REG0_S(2) + 7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                dComIfGp_particle_setToon(dPa_name::ID_SCENE_A1DB, &actor->current.pos, NULL, NULL, 0xB9, &i_this->mPa_smokeEcallBack, fopAcM_GetRoomNo(actor));
                i_this->m112A = REG0_S(7) + 4;
                mDoAud_seStart(JA_SE_CM_BST_HEAD_FALL, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                mDoAud_seStart(JA_SE_CM_BST_MOUTH_OPEN, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                anm_init(i_this, BST_BCK_KUTI_OPEN, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mDamage++;
                actor->speed.y = 0.0f;
            }
        }
        break;
    case 2:
        if (i_this->m02B8->isStop()) {
            anm_init(i_this, BST_BCK_KUTI_OPEN_LOOP, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m10FC[0] = 300;
            i_this->mDamage++;
        }
        break;
    case 3:
        if (bom_eat_check(i_this)) {
            i_this->mDamage++;
            i_this->m10FC[0] = 10;
        } else if (i_this->m10FC[0] == 0) {
            i_this->mActionType = bst_class::ACTION_HEAD_HUKKI_e;
            i_this->mDamage = 0;
            mDoAud_bgmStart(JA_BGM_UNK_122);
            break;
        } else {
            break;
        }
        // Fall-through
    case 4: {
        fopAc_ac_c* bomb = fopAcM_SearchByID(i_this->mBombId);
        if (bomb != NULL) {
            bomb->gravity = 0.0f;
            bomb->speedF = 0.0f;
            bomb->speed.setall(0.0f);
            bomb->current.angle.setall(0);
            bomb->shape_angle.setall(0);
            cLib_addCalc2(&bomb->current.pos.x, actor->current.pos.x, 1.0f, 30.0f);
            cLib_addCalc2(&bomb->current.pos.y, actor->current.pos.y + 90.0f + REG0_F(0xb), 1.0f, 30.0f);
            cLib_addCalc2(&bomb->current.pos.z, actor->current.pos.z, 1.0f, 30.0f);
        }
        if (i_this->m10FC[0] != 0) {
            break;
        }
        anm_init(i_this, BST_BCK_BOM_NOMI, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mDamage++;
        i_this->m2EE0[0] = dComIfGp_particle_set(dPa_name::ID_SCENE_81E3, &actor->current.pos);
        fopAcM_seStart(actor, JA_SE_CM_BST_MOUTH_CLOSE, 0);
        i_this->m10FC[0] = 0x3c;
        // fallthrough
    }
    case 5:
        if (i_this->m10FC[0] == 0x32) {
            fopAcM_seStart(actor, JA_SE_CM_BST_BOMB_EAT, 0);
        }
        if (i_this->m10FC[0] == 0x1e) {
            fopAcM_seStart(actor, JA_SE_CM_BST_BEF_EXPLODE, 0);
        }
        if (i_this->m02B8->isStop()) {
            if (i_this->m2EE0[0] != NULL) {
                i_this->m2EE0[0]->becomeInvalidEmitter();
                i_this->m2EE0[0] = NULL;
            }
            fopAc_ac_c* bomb = fopAcM_SearchByID(i_this->mBombId);
            if (bomb != NULL) {
                fopAcM_delete(bomb);
            }
            actor->health--;
            if ((actor->health <= 0) || (l_HIO.m6 != 0)) {
                i_this->m2E9A = 0x32;
                i_this->mActionType = bst_class::ACTION_END_DEMO_e;
                i_this->mDamage = 0;
                anm_init(i_this, BST_BCK_BST_DEAD, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                hand[0]->mActionType = bst_class::ACTION_END_DEMO_e;
                hand[0]->mDamage = 10;
                hand[1]->mActionType = bst_class::ACTION_END_DEMO_e;
                hand[1]->mDamage = 10;
                fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0);
                mDoAud_bgmStop(30);
                mDoAud_bgmStreamPrepare(JA_STRM_BST_CLEAR);
            } else {
                anm_init(i_this, BST_BCK_BOM_BAKUHATU, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mDamage++;
            }
            fopAcM_seStart(actor, JA_SE_CM_BST_EXPLODE, 0);
            for (s32 i = 0; i < 4; i++) {
                i_this->m2EE0[i + 1] = dComIfGp_particle_set(bomb_eff_name[i], &actor->current.pos);
            }
            i_this->m10FC[3] = 0x51;
        }
        break;
    case 6:
        if ((int)i_this->m02B8->getFrame() == 8) {
            fopAcM_seStart(actor, JA_SE_CM_BST_JUMP_S, 0);
        }
        if (i_this->m02B8->isStop()) {
            i_this->m10FC[0] = 0x1e;
            i_this->mDamage++;
            mDoAud_bgmStart(JA_BGM_BST_BATTLE);
        }
        break;
    case 7:
        if (i_this->m10FC[0] == 0) {
            i_this->mActionType = bst_class::ACTION_HEAD_HUKKI_e;
            i_this->mDamage = 0;
        }
        break;
    }
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m2EE0[i] != NULL) {
            if ((i >= 1) && (i_this->m10FC[3] == 1)) {
                i_this->m2EE0[i]->becomeInvalidEmitter();
                i_this->m2EE0[i] = NULL;
            } else {
                i_this->m2EE0[i]->setGlobalRTMatrix(i_this->m02B8->getModel()->getAnmMtx(0));
            }
        }
    }
}

/* 000049A8-00004BCC       .text head_hukki__FP9bst_class */
static void head_hukki(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage++;
        i_this->m10FC[0] = REG0_S(0) + 40;
        i_this->m10F8 = 0.0f;
        i_this->m10EC.y = 0.0f;
        // fallthrough
    case 1:
        cLib_addCalc2(&i_this->m10F8, REG0_F(4) + 4000.0f, 1.0f, REG0_F(5) + 100.0f);
        if (i_this->m10FC[0] == 0) {
            i_this->mDamage++;
            i_this->m10FC[0] = REG0_S(1) + 80;
        }
        break;
    case 2:
        cLib_addCalc0(&i_this->m10F8, 1.0f, REG0_F(6) + 50.0f);
        if (i_this->m10FC[0] == 0) {
            i_this->mActionType = bst_class::ACTION_FLY_e;
            i_this->mDamage = 0;
            actor->speedF = 0.0f;
            i_this->m10EC.y = 0.0f;
            i_this->mEyeHealth[1] = 2;
            i_this->mEyeHealth[0] = 2;
        }
        break;
    }
    actor->shape_angle.x = i_this->m10F8 * cM_ssin(i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 700));
    actor->shape_angle.z = i_this->m10F8 * cM_ssin(i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 600));
    cLib_addCalc2(&actor->current.pos.y, REG0_F(11) + 400.0f, 0.05f, i_this->m10EC.y * 40.0f);
    cLib_addCalc2(&i_this->m10EC.z, REG0_F(11) + 50.0f, 1.0f, 2.0f);
    cLib_addCalc2(&i_this->m10EC.y, 1.0f, 1.0f, 0.02f);
}

/* 00004BCC-000051E0       .text col_set__FP9bst_class */
static void col_set(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz vec;
    cXyz pos_vec;
    if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
        cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(8), *calc_mtx);
        vec.set(REG0_F(0) + (-30.0f), REG0_F(1), REG0_F(2) + (-100.0f));
        MtxPosition(&vec, &pos_vec);
        i_this->mHeadHurtCyl.SetC(pos_vec);
        i_this->mHeadHurtCyl.SetH(REG0_F(3) + 600.0f);
        i_this->mHeadHurtCyl.SetR(REG0_F(4) + 180.0f);
        dComIfG_Ccsp()->Set(&i_this->mHeadHurtCyl);
        i_this->mHandHurtCyl.OffTgSetBit();
        vec.set(REG0_F(5) + 150.0f, REG0_F(6), REG0_F(7) + 70.0f);
        MtxPosition(&vec, &pos_vec);
        i_this->mHandHurtCyl.SetC(pos_vec);
        i_this->mHandHurtCyl.SetH(REG0_F(8) + 100.0f);
        i_this->mHandHurtCyl.SetR(REG0_F(9) + 100.0f);
        dComIfG_Ccsp()->Set(&i_this->mHandHurtCyl);
        vec.set(REG0_F(11) + 250.0f, 0.0f, 0.0f);
        MtxPosition(&vec, &actor->eyePos);
        vec.setall(0.0f);
        for (s32 i = 0; i < 2; i++) {
            cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(i + 4), *calc_mtx);
            MtxPosition(&vec, &pos_vec);
            s16 unk = i_this->m2E74[i];
            if (unk != 0 || i_this->mEyeHealth[i] <= 0) {
                if (unk != 0) {
                    i_this->m2E74[i]--;
                }
                pos_vec.y += 10000.0f;
                cLib_addCalcAngleS2(&i_this->m2E78[i], REG0_S(8) + 11000, 1, 0x400);
            } else {
                cLib_addCalcAngleS2(&i_this->m2E78[i], 0, 8, 0x200);
            }
            i_this->mEyeSphs[i].SetC(pos_vec);
            i_this->mEyeSphs[i].SetR(REG0_F(14) + 60.0f);
            dComIfG_Ccsp()->Set(&i_this->mEyeSphs[i]);
        }
    } else {
        vec.setall(0.0f);
        f32 radius = 0.0f;
        if (i_this->mActionType == bst_class::ACTION_HARAI_ATTACK_e) {
            radius = REG0_F(16) + 50.0f;
        }
        for (s32 i = 0; i < 15; i++) {
            cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(i + 2), *calc_mtx);
            MtxPosition(&vec, &pos_vec);
            i_this->mFingerSphs[i].SetC(pos_vec);
            i_this->mFingerSphs[i].SetR(REG0_F(14) + 50.0f + radius);
            dComIfG_Ccsp()->Set(&i_this->mFingerSphs[i]);
        }
        cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(17), *calc_mtx);
        static f32 te_x[4] = {70.0f, 70.0f, 70.0f, 70.0f};
        static f32 te_y[4] = {70.0f, -70.0f, 70.0f, -70.0f};
        static f32 te_z[4] = {90.0f, 90.0f, -30.0f, -30.0f};
        for (s32 i = 0; i < 4; i++) {
            vec.x = te_x[i];
            if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
                vec.x *= -1.0f;
            }
            vec.y = te_y[i];
            vec.z = te_z[i];
            MtxPosition(&vec, &pos_vec);
            i_this->mFingerSphs[i + 15].SetC(pos_vec);
            i_this->mFingerSphs[i + 15].SetR(REG0_F(15) + 65.0f + radius);
            dComIfG_Ccsp()->Set(&i_this->mFingerSphs[i + 15]);
        }
        if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
            vec.set(-(REG0_F(15) + 100.0f), REG0_F(16), -(REG0_F(17) + 40.0f));
            MtxPosition(&vec, &pos_vec);
            vec.set(-(REG0_F(15) + 100.0f), REG0_F(16), REG0_F(18) + 10.0f);
            MtxPosition(&vec, &actor->eyePos);
        } else {
            vec.set(REG0_F(15) + 100.0f, REG0_F(16), REG0_F(17) + 40.0f);
            MtxPosition(&vec, &pos_vec);
            vec.set(REG0_F(15) + 100.0f, REG0_F(16), -(REG0_F(18) + 10.0f));
            MtxPosition(&vec, &actor->eyePos);
        }
        i_this->mHandHurtCyl.SetC(pos_vec);
        i_this->mHandHurtCyl.SetH(REG0_F(8) + 140.0f);
        i_this->mHandHurtCyl.SetR(REG0_F(9) + 150.0f);
        dComIfG_Ccsp()->Set(&i_this->mHandHurtCyl);
    }
    actor->attention_info.position = actor->eyePos;
}

/* 000051E0-00005224       .text player_way_check__FP9bst_class */
static BOOL player_way_check(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s16 angle_diff = actor->shape_angle.y - dComIfGp_getPlayer(0)->shape_angle.y;
    if (angle_diff < 0) {
        angle_diff = -angle_diff;
    }
    if ((u16)angle_diff < 0x4000) {
        return FALSE;
    }
    return TRUE;
}

/* 00005224-0000591C       .text damage_check__FP9bst_class */
static void damage_check(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = daPy_getPlayerActorClass();
    i_this->mStts.Move();
    CcAtInfo atInfo;
    atInfo.pParticlePos = NULL;
    if (i_this->mDamageTimer == 0) {
        s8 bVar1 = false;
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            if (i_this->mHeadHurtCyl.ChkTgHit()) {
                atInfo.mpObj = i_this->mHeadHurtCyl.GetTgHitObj();
                bVar1 = true;
            }
        } else {
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mFingerSphs); i++) {
                if (i_this->mFingerSphs[i].ChkTgHit()) {
                    atInfo.mpObj = i_this->mFingerSphs[i].GetTgHitObj();
                    bVar1 = true;
                }
            }
        }
        if (bVar1) {
            def_se_set(actor, atInfo.mpObj, 0x42);
            i_this->mDamageTimer = 7;
        }
    }
    if (i_this->mState == 0) {
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            if (i_this->mEyeSphs[0].ChkTgHit() || i_this->mEyeSphs[1].ChkTgHit() != 0) {
                i_this->mState = 10;
                if (player_way_check(i_this)) {
                    u32 eye_index;
                    if (i_this->mEyeSphs[0].ChkTgHit()) {
                        atInfo.mpObj = i_this->mEyeSphs[0].GetTgHitObj();
                        eye_index = 0;
                    } else {
                        atInfo.mpObj = i_this->mEyeSphs[1].GetTgHitObj();
                        eye_index = 1;
                    }
                    if (i_this->mRoomState != 1) {
                        i_this->mRoomState = 8;
                    }
                    i_this->mActionType = bst_class::ACTION_DAMAGE_e;
                    i_this->mDamage = 0;
                    mDoAud_seStart(JA_SE_CM_BST_EYE_HIT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    i_this->mEyeHealth[eye_index]--;
                    if (i_this->mEyeHealth[eye_index] <= 0) {
                        // Check the other eye.
                        if (i_this->mEyeHealth[1 - eye_index] <= 0) {
                            i_this->mActionType = bst_class::ACTION_HEAD_DAMAGE_e;
                            i_this->mDamage = 0;
                        }
                        mDoAud_seStart(JA_SE_CM_BST_EYE_BREAK, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    }
                    i_this->mHeadHurtSpeed = REG0_F(11) + 70.0f;
                    i_this->mHeadHurtAngle = REG0_S(2) + 7;
                    cXyz player_vec = actor->current.pos - player->current.pos;
                    i_this->mHurtRecoilAngle1 = cM_atan2s(player_vec.x, player_vec.z);
                    i_this->mHurtRecoilAngle2 = -cM_atan2s(player_vec.y, std::sqrtf(SQUARE(player_vec.x) + SQUARE(player_vec.z)));
                    actor->speedF = 0.0f;
                    cXyz* hit_pos = i_this->mEyeSphs[eye_index].GetTgHitPosP();
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0010, hit_pos);
                    cXyz scale;
                    scale.x = scale.y = scale.z = 2.0f;
                    csXyz angle;
                    angle.x = angle.z = 0;
                    angle.y = fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0));
                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, hit_pos, &angle, &scale);
                    dKy_SordFlush_set(*hit_pos, 1);
                }
            }
        } else {
            if (i_this->mHandHurtCyl.ChkTgHit()) {
                i_this->mState = 10;
                if (player_way_check(i_this)) {

                    atInfo.mpObj = i_this->mHandHurtCyl.GetTgHitObj();
                    atInfo.pParticlePos = i_this->mHandHurtCyl.GetTgHitPosP();
                    atInfo.mpActor = cc_at_check(actor, &atInfo);
                    mDoAud_seStart(JA_SE_CM_BST_EYE_HIT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    if (actor->health <= 0) {
                        mDoAud_seStart(JA_SE_CM_BST_EYE_BREAK, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    }
                    i_this->mHeadHurtSpeed = REG0_F(0xb) + 70.0f;
                    i_this->mHeadHurtAngle = REG0_S(2) + 0xf;
                    cXyz player_vec = actor->current.pos - player->current.pos;
                    i_this->mHurtRecoilAngle1 = cM_atan2s(player_vec.x, player_vec.z);
                    i_this->mHurtRecoilAngle2 = -cM_atan2s(player_vec.y, std::sqrtf(SQUARE(player_vec.x) + SQUARE(player_vec.z)));
                    actor->speedF = 0.0f;
                    cXyz* hit_pos = i_this->mHandHurtCyl.GetTgHitPosP();
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0010, hit_pos);
                    cXyz scale;
                    scale.z = 2.0f;
                    scale.y = 2.0f;
                    scale.x = 2.0f;
                    csXyz angle;
                    angle.x = angle.z = 0;
                    angle.y = fopAcM_searchActorAngleY(actor, dComIfGp_getPlayer(0));
                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, hit_pos, &angle, &scale);
                    dKy_SordFlush_set(*hit_pos, 1);
                    i_this->mActionType = bst_class::ACTION_DAMAGE_e;
                    i_this->mDamage = 0;
                    s32 hand_index = 2 - i_this->mBstPartType;
                    if (hand[hand_index]->mActionType >= bst_class::ACTION_DOWN_ATTACK_e) {
                        hand[hand_index]->mActionType = bst_class::ACTION_FLY_e;
                        hand[hand_index]->mDamage = 0;
                        hand[hand_index]->actor.speedF = 0.0f;
                    }
                }
            }
        }
    }
}

static u16 item_smoke_name[2] = {dPa_name::ID_SCENE_A1DF, dPa_name::ID_SCENE_A1E0};

/* 0000591C-00005D9C       .text hana_demo__FP9bst_class */
static void hana_demo(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mState = 10;
    s16 angle = cM_atan2s(-actor->current.pos.x, -actor->current.pos.z);
    cLib_addCalcAngleS2(&actor->shape_angle.y, angle, 10, 0x400);
    cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x400);
    cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 10, 0x400);
    cLib_addCalc2(&actor->current.pos.y, REG0_F(11) + 400.0f, 0.05f, 30.0f);
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage++;
        i_this->m10FC[0] = 40;
        actor->speedF = 0.0f;
        actor->speed.y = 0.0f;
        anm_init(i_this, BST_BCK_HANA_DEMO, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m2E9A = 1;
        fopAcM_seStartCurrent(actor, JA_SE_CM_BST_HAND_STRAIN, 0);
        // fallthrough
    case 1:
        cXyz vec = actor->current.pos;
        vec.y = 0.0f;
        f32 dist = vec.abs();
        if (dist > REG0_F(9) + 1350.0f) {
            f32 angle = (REG0_F(9) + 1350.0f) / dist;
            cLib_addCalc2(&actor->current.pos.x, vec.x * angle, 0.2f, 30.0f);
            cLib_addCalc2(&actor->current.pos.z, vec.z * angle, 0.2f, 30.0f);
        }
        if ((s32)i_this->m02B8->getFrame() > 26) {
            fopAc_ac_c* item = fopAcM_SearchByID(i_this->mCreatedItemId);
            if (item != NULL) {
                fopAcM_OnStatus(item, fopAcStts_UNK4000_e);
            }
        }
        if ((s32)i_this->m02B8->getFrame() == 26) {
            int itemNo;
            if (dComIfGs_getArrowNum() == 0) {
                itemNo = dItem_ARROW_10_e;
                cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(6), *calc_mtx);
                i_this->m2E9E = 0;
            } else {
                itemNo = dItem_BOMB_5_e;
                cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(7), *calc_mtx);
                i_this->m2E9E = 1;
            }
            vec.set(REG0_F(2) + 60.0f, REG0_F(3), REG0_F(4));
            if (itemNo != -35) {
                mDoAud_seStart(JA_SE_OBJ_BOMB_EXPLODE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                cXyz pos_vec;
                MtxPosition(&vec, &pos_vec);
                i_this->mCreatedItemId = fopAcM_createItem(&pos_vec, itemNo, -1, fopAcM_GetRoomNo(actor), 0, NULL, 0xB, NULL);
                mDoAud_seStart(JA_SE_CM_BST_ITEM_OUT_NOSE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(0), *calc_mtx);
                vec.setall(0.0f);
                MtxPosition(&vec, &pos_vec);
                dComIfGp_particle_setToon(
                    item_smoke_name[i_this->m2E9E], &pos_vec, &actor->shape_angle, NULL, 0xB9, &i_this->mPa_smokeEcallBack, fopAcM_GetRoomNo(actor)
                );
            }
        }
        break;
    }
}

/* 00005D9C-00006088       .text end_demo__FP9bst_class */
static void end_demo(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mState = 10;
    fopAcM_OffStatus(actor, 0);
    actor->attention_info.flags = 0;
    switch (i_this->mDamage) {
    case 0:
        i_this->mDamage++;
        // fallthrough
    case 1:
        if ((s32)i_this->m02B8->getFrame() == 20) {
            fopAcM_seStart(actor, JA_SE_CM_BST_JUMP_L, 0);
        }
        break;
    case 2:
        anm_init(i_this, BST_BCK_BST_HIRAKU, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mDamage++;
        i_this->m2EF4 = dComIfGp_particle_set(dPa_name::ID_SCENE_81E8, &actor->current.pos);
        if (i_this->m2EF4 != NULL) {
            i_this->m2EF4->setGlobalRTMatrix(i_this->m02B8->getModel()->getAnmMtx(0));
        }
        break;
    case 3:
        break;
    case 10:
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            anm_init(i_this, fly_bck_d[i_this->mBstPartType], 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        } else {
            anm_init(i_this, set_bck_d[i_this->mBstPartType], 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        i_this->mDamage++;
        // fallthrough
    case 11:
        cLib_addCalc2(&actor->current.pos.x, actor->home.pos.x, 0.1f, REG0_F(9) + 5.0f);
        cLib_addCalc2(&actor->current.pos.y, actor->home.pos.y, 0.1f, REG0_F(9) + 5.0f);
        cLib_addCalc2(&actor->current.pos.z, actor->home.pos.z, 0.1f, REG0_F(9) + 5.0f);
        cLib_addCalcAngleS2(&actor->shape_angle.y, actor->home.angle.y, 10, 0x80);
        cLib_addCalcAngleS2(&actor->shape_angle.x, actor->home.angle.x, 10, 0x80);
        cLib_addCalcAngleS2(&actor->shape_angle.z, actor->home.angle.z, 10, 0x80);
        break;
    }
    if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
        for (s32 i = 0; i < 4; i++) {
            if (i_this->m2EE0[i + 1] != NULL) {
                if (i_this->m10FC[3] == 1) {
                    i_this->m2EE0[i + 1]->becomeInvalidEmitter();
                    i_this->m2EE0[i + 1] = NULL;
                } else {
                    i_this->m2EE0[i + 1]->setGlobalRTMatrix(i_this->m02B8->getModel()->getAnmMtx(0));
                }
            }
        }
    }
}

/* 00006088-00006418       .text move__FP9bst_class */
static void move(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1;
    cXyz vec;
    cXyz pos_vec;
    cXyz pos_diff;
    if (i_this->mBstPartType != bst_class::Type_HEAD_e && boss->m2E9A > 0 && boss->m2E9A < 10) {
        if (boss->m2E7C == 11) {
            i_this->mActionType = bst_class::ACTION_FLY_e;
        } else {
            i_this->mActionType = bst_class::ACTION_SLEEP_e;
        }
        i_this->mDamage = 0;
        actor->speedF = 0.0f;
    } else {
        set_hand_AT(i_this, 0);
        set_hand_CO(i_this, 0);
        i_this->mHeadHurtCyl.ClrAtSet();
        bVar1 = false;
        switch (i_this->mActionType) {
        case bst_class::ACTION_STAY_e:
            bVar1 = true;
            stay(i_this);
            break;
        case bst_class::ACTION_FLY_e:
            bVar1 = true;
            fly(i_this);
            break;
        case bst_class::ACTION_DAMAGE_e:
            damage(i_this);
            break;
        case bst_class::ACTION_SLEEP_e:
            sleep(i_this);
            break;
        case bst_class::ACTION_HEAD_DAMAGE_e:
            head_damage(i_this);
            break;
        case bst_class::ACTION_HEAD_HUKKI_e:
            head_hukki(i_this);
            break;
        case bst_class::ACTION_DOWN_ATTACK_e:
            bVar1 = true;
            down_attack(i_this);
            break;
        case bst_class::ACTION_PAA_ATTACK_e:
            bVar1 = true;
            paa_attack(i_this);
            break;
        case bst_class::ACTION_KUMI_ATTACK_e:
            bVar1 = true;
            kumi_attack(i_this);
            break;
        case bst_class::ACTION_HARAI_ATTACK_e:
            bVar1 = true;
            harai_attack(i_this);
            break;
        case bst_class::ACTION_BEAM_ATTACK_e:
            beam_attack(i_this);
            break;
        case bst_class::ACTION_HANA_DEMO_e:
            hana_demo(i_this);
            break;
        case bst_class::ACTION_END_DEMO_e:
            end_demo(i_this);
            break;
        }
        if (bVar1) {
            pos_diff = actor->current.pos - actor->old.pos;
            u32 dist = (u32)(pos_diff.abs() * 3.5f);
            if (dist > 100) {
                dist = 100;
            }
            if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
                fopAcM_seStart(actor, JA_SE_CM_BST_HEAD_WORKING, dist);
            } else {
                fopAcM_seStart(actor, JA_SE_CM_BST_HAND_WORKING, dist);
            }
        }
        damage_check(i_this);
        dCcD_Stts* stts = &i_this->mStts;
        if (stts != NULL) {
            actor->current.pos.x += stts->GetCCMoveP()->x;
            actor->current.pos.y += stts->GetCCMoveP()->y;
            actor->current.pos.z += stts->GetCCMoveP()->z;
        }
        if (i_this->mHeadHurtSpeed > 0.01f) {
            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = i_this->mHeadHurtSpeed;
            cMtx_YrotS(*calc_mtx, i_this->mHurtRecoilAngle1);
            cMtx_XrotM(*calc_mtx, i_this->mHurtRecoilAngle2);
            MtxPosition(&vec, &pos_vec);
            actor->current.pos += pos_vec;
            cLib_addCalc0(&i_this->mHeadHurtSpeed, 1.0f, 4.0f);
        }
    }
}

/* 00006418-00006DC0       .text main_cont__FP9bst_class */
static void main_cont(bst_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    if (i_this->m2E9A == 0) {
        if (i_this->mBombArrowDropTimer != 0) {
            i_this->mBombArrowDropTimer--;
        }
        for (s32 i = 0; i < 3; i++) {
            if (i_this->m2E7E[i] != 0) {
                i_this->m2E7E[i]--;
            }
        }
        switch (i_this->m2E7C) {
        case 0:
            i_this->m2E7C = 1;
            break;
        case 1:
            if (!dComIfGs_isStageBossEnemy() || REG0_S(5) != 0) {
                fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
                if (dComIfGs_isStageBossDemo()) {
                    i_this->m2FE4 = 1;
                    mDoAud_bgmStart(JA_BGM_BST_BATTLE);
                    boss->mActionType = bst_class::ACTION_FLY_e;
                    hand[0]->mActionType = bst_class::ACTION_FLY_e;
                    hand[1]->mActionType = bst_class::ACTION_FLY_e;
                    boss->mDamage = 0;
                    hand[1]->mDamage = 0;
                    hand[0]->mDamage = 0;
                    i_this->m2E7C = 10;
                    J3DAnmTevRegKey* key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_UDEL);
                    hand[0]->mpBrkAnm->init(hand[0]->m02C8->getModelData(), key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                    J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_UDEL);
                    hand[0]->mpBtkAnm->init(hand[0]->m02C8->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                    key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_UDER);
                    hand[1]->mpBrkAnm->init(hand[1]->m02C8->getModelData(), key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                    srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_UDER);
                    hand[1]->mpBtkAnm->init(hand[1]->m02C8->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                    key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_MUNE);
                    boss->mpBrkAnm->init(boss->m02C8->getModelData(), key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                    srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_MUNE);
                    boss->mpBtkAnm->init(boss->m02C8->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                    i_this->mBombArrowDropTimer = 400;
                    i_this->m2FE0->setPlaySpeed(1.0f);
                } else {
                    hand[1]->mState = 10;
                    hand[0]->mState = 10;
                    boss->mState = 10;
                    if (player->current.pos.abs() < 700.0f) {
                        i_this->m2E9A = 10;
                        i_this->m2E7C = 2;
                    }
                }
            }
            break;
        case 9:
            break;
        case 10:
            i_this->m2E7C += 1;
            fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
            i_this->m2E7E[0] = 100;
            break;
        case 11:
            if (i_this->m2E7E[0] == 0 && boss->mActionType != 14) {
                boss->mAcchCir.SetWall(200.0f, 300.0f);
                hand[0]->mAcchCir.SetWall(200.0f, 200.0f);
                hand[1]->mAcchCir.SetWall(200.0f, 200.0f);
                if (cM_rndF(1.0f) < 0.2f || REG0_S(1) != 0) {
                    if (cM_rndF(1.0f) < 0.5f) {
                        if (hand[0]->mActionType < bst_class::ACTION_DOWN_ATTACK_e && hand[0]->mStateTimer == 0) {
                            hand[0]->mActionType = bst_class::ACTION_HARAI_ATTACK_e;
                            hand[0]->mDamage = 0;
                        }
                    } else if (hand[1]->mActionType < bst_class::ACTION_DOWN_ATTACK_e && hand[1]->mStateTimer == 0) {
                        hand[1]->mActionType = bst_class::ACTION_HARAI_ATTACK_e;
                        hand[1]->mDamage = 0;
                    }
                } else {
                    f32 threshold;
                    if (actor->health == 0) {
                        threshold = 1.0f - 0.3f;
                    } else if (actor->health == 1) {
                        threshold = 0.5f;
                    } else if (actor->health == 2) {
                        threshold = 0.3f;
                    } else if (actor->health == 3) {
                        threshold = 0.2f;
                    }
                    if (cM_rndF(1.0f) < threshold || REG0_S(0) != 0) {
                        if (hand[0]->mActionType < bst_class::ACTION_DAMAGE_e && hand[1]->mActionType < bst_class::ACTION_DAMAGE_e &&
                            hand[0]->mStateTimer == 0 && hand[1]->mStateTimer == 0)
                        {
                            hand[0]->mActionType = bst_class::ACTION_KUMI_ATTACK_e;
                            hand[0]->mDamage = 0;
                            hand[1]->mActionType = bst_class::ACTION_KUMI_ATTACK_e;
                            hand[1]->mDamage = 0;
                        }
                    } else if (cM_rndF(1.0f) < 0.5f) {
                        if (hand[0]->mActionType < bst_class::ACTION_DAMAGE_e && hand[1]->mActionType < bst_class::ACTION_DAMAGE_e &&
                            hand[0]->mStateTimer == 0 && hand[1]->mStateTimer == 0)
                        {
                            hand[0]->mActionType = bst_class::ACTION_PAA_ATTACK_e;
                            hand[0]->mDamage = 0;
                            hand[1]->mActionType = bst_class::ACTION_PAA_ATTACK_e;
                            hand[1]->mDamage = 0;
                        }
                    } else if (cM_rndF(1.0f) < 0.5f) {
                        if (hand[0]->mActionType < bst_class::ACTION_DAMAGE_e && hand[0]->mStateTimer == 0) {
                            hand[0]->mActionType = bst_class::ACTION_DOWN_ATTACK_e;
                            hand[0]->mDamage = 0;
                        }
                    } else {
                        if (hand[1]->mActionType < bst_class::ACTION_DAMAGE_e && hand[1]->mStateTimer == 0) {
                            hand[1]->mActionType = bst_class::ACTION_DOWN_ATTACK_e;
                            hand[1]->mDamage = 0;
                        }
                    }
                }
                s16 unk;
                if (actor->health == 0) {
                    unk = cM_rndF(30.0f) + 30.0f;
                } else if (actor->health == 1) {
                    unk = cM_rndF(40.0f) + 50.0f;
                } else {
                    unk = cM_rndF(50.0f) + 70.0f;
                }
                i_this->m2E7E[0] = unk;
            }
            boss->m2E74[1] = 10;
            boss->m2E74[0] = 10;
            if (i_this->m2E7E[2] == 0 && hand[0]->mActionType == bst_class::ACTION_SLEEP_e && hand[1]->mActionType == bst_class::ACTION_SLEEP_e) {
                i_this->m2E7C = 12;
                hand[0]->m10FC[1] = 100;
                hand[1]->m10FC[1] = 100;
                fopAcM_seStart(&boss->actor, JA_SE_CM_BST_HEAD_EYE_OPEN, 0);
                mDoAud_bgmStart(JA_BGM_UNK_122);
                i_this->m2E7E[1] = cM_rndF(50.0f) + 150.0f;
            }
            break;
        case 12:
            if (i_this->m2E7E[1] == 0 && boss->mActionType == bst_class::ACTION_FLY_e) {
                boss->mActionType = bst_class::ACTION_BEAM_ATTACK_e;
                boss->mDamage = 0;
                boss->m10D0 = REG0_F(7) + (-500.0f);
            }
            hand[0]->mActionType = bst_class::ACTION_SLEEP_e;
            hand[0]->m10FC[1] = 3;
            hand[1]->m10FC[1] = 3;
            if (boss->mActionType == bst_class::ACTION_HEAD_DAMAGE_e && boss->mDamage >= 7) {
                i_this->m2E7C = 11;
                i_this->m2E7E[2] = 50;
            }
            break;
        case 100:
            break;
        }
    }
}

/* 00006DC0-00006FA4       .text beam_eff_set__FP4cXyzsUc */
static void beam_eff_set(cXyz* pos, short y, u8 set_angle) {
    if (!set_angle) {
        dComIfGp_particle_set(dPa_name::ID_SCENE_81BF, pos);
        dComIfGp_particle_set(dPa_name::ID_SCENE_A1C0, pos);
        dComIfGp_particle_set(dPa_name::ID_SCENE_A1C1, pos);
    } else {
        csXyz angle(-0x4000, y, 0);
        dComIfGp_particle_set(dPa_name::ID_SCENE_81BF, pos, &angle);
        dComIfGp_particle_set(dPa_name::ID_SCENE_A1C0, pos, &angle);
        dComIfGp_particle_set(dPa_name::ID_SCENE_A1C1, pos, &angle);
    }
}

/* 00006FA4-00007308       .text beam_wall_check__FP4cXyzP4cXyz */
static BOOL beam_wall_check(cXyz* pos_1, cXyz* pos_2) {
    dBgS_LinChk chk;
    cXyz start = *pos_1 - *pos_2;
    start.y += 50.0f;
    cXyz end(*pos_1);
    end.y = start.y;
    chk.Set(&start, &end, NULL);
    if (dComIfG_Bgsp()->LineCross(&chk)) {
        *pos_1 = chk.mLin.GetEnd();
        return TRUE;
    }
    return FALSE;
}

/* 00007740-00007B58       .text beam_move__FP9bst_class */
static void beam_move(bst_class* i_this) {
    /* Nonmatching - regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    cXyz* pos1;
    cXyz* pos2;
    J3DModel* model;
    s8 beam_set;
    dBgS_GndChk chk;
    for (s32 i = 0; i < 10; i++) {
        if (i_this->m04E4[i] == 0) {
            continue;
        }
        pos1 = &i_this->m03B8[i];
        pos2 = &i_this->m0430[i];
        VECAdd(pos1, pos2, pos1);
        model = i_this->m0390[i];
        mDoMtx_stack_c::transS(i_this->m03B8[i]);
        mDoMtx_stack_c::YrotM(i_this->m04A8[i].y);
        mDoMtx_stack_c::XrotM(i_this->m04A8[i].x);
        mDoMtx_stack_c::scaleM(1.0f, 1.0f, i_this->m10A8[i]);
        model->setBaseTRMtx(mDoMtx_stack_c::now);
        cLib_addCalc2(&i_this->m10A8[i], REG0_F(4) + 5.0f, 1.0f, REG0_F(5) + 0.5f);
        beam_set = FALSE;
        f32 fVar1 = 500.0f;
        chk.m_pos.set(i_this->m03B8[i].x, i_this->m03B8[i].z + fVar1, i_this->m03B8[i].y);
        f32 ground_cross = dComIfG_Bgsp()->GroundCross(&chk);
        if (ground_cross >= i_this->m03B8[i].y) {
            i_this->m03B8[i].y = ground_cross;
            beam_eff_set(pos1, 0, 0);
            beam_set = TRUE;
        } else {
            if (beam_wall_check(pos1, pos2)) {
                beam_eff_set(pos1, i_this->m04A8[i].y, 1);
                beam_set = TRUE;
            }
        }
        if (i_this->m03B8[i].y > 2000.0f) {
            i_this->m04E4[i] = 0;
        }
        if (beam_set) {
            i_this->m04E4[i] = 0;
            dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            mDoAud_seStart(JA_SE_CM_BST_BEAM_BOMB, pos1, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->m04E4[i] == 1) {
            i_this->mCcD_beams[i].StartCAt(*pos1);
            i_this->m04E4[i]++;
        } else {
            i_this->mCcD_beams[i].MoveCAt(*pos1);
        }
        dComIfG_Ccsp()->Set(&i_this->mCcD_beams[i]);
    }
}

/* 00007CF0-0000815C       .text end_brkbtk_set__FP9bst_class */
static void end_brkbtk_set(bst_class* i_this) {
    J3DAnmTevRegKey* tev_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_LH_END);
    hand[0]->mpTevRegAnimator->init(hand[0]->m02B8->getModel()->getModelData(), tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_LH_END);
    hand[0]->mpTexMtxAnimator->init(hand[0]->m02B8->getModel()->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    tev_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_RH_END);
    hand[1]->mpTevRegAnimator->init(hand[1]->m02B8->getModel()->getModelData(), tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_RH_END);
    hand[1]->mpTexMtxAnimator->init(hand[1]->m02B8->getModel()->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    tev_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_BST_END);
    boss->mpTevRegAnimator->init(boss->m02B8->getModel()->getModelData(), tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_BST_END);
    boss->mpTexMtxAnimator->init(boss->m02B8->getModel()->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    tev_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_UDEL_END);
    hand[0]->mpBrkAnm->init(hand[0]->m02C8->getModelData(), tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_UDEL_END);
    hand[0]->mpBtkAnm->init(hand[0]->m02C8->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    tev_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_UDER_END);
    hand[1]->mpBrkAnm->init(hand[1]->m02C8->getModelData(), tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_UDER_END);
    hand[1]->mpBtkAnm->init(hand[1]->m02C8->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    tev_key = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_MUNE_END);
    boss->mpBrkAnm->init(boss->m02C8->getModelData(), tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
    srt_key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_MUNE_END);
    boss->mpBtkAnm->init(boss->m02C8->getModelData(), srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
}

/* 0000815C-00009FCC       .text demo_camera__FP9bst_class */
void demo_camera(bst_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    bst_class* pbVar5;
    int iVar13;
    int iVar14;
    J3DAnmTevRegKey* pJVar7;
    J3DAnmTextureSRTKey* pJVar8;
    JPABaseEmitter* pJVar9;
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;
    daPy_py_c* player = daPy_getPlayerActorClass();
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    s8 bVar2 = true;
    switch (i_this->m2E9A) {
    case 1:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            bVar2 = false;
            break;
        }
        i_this->m2E9A++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->msFrameCount = 0;
        i_this->m2EC8 = 55.0f;
        i_this->m2EC4 = 0.0f;
        i_this->m2E98 = 100;
        // fallthrough
    case 2:
        if (i_this->msFrameCount > (s16)(REG0_S(4) + 33)) {
            cLib_addCalc2(&i_this->m2EC4, -650.0f, 0.5f, REG0_F(3) + 50.0f);
            if (i_this->msFrameCount > (s16)(REG0_S(4) + 45)) {
                cLib_addCalc2(&i_this->m2EC8, 30.0f, 0.5f, REG0_F(3) + 10.0f);
            }
        }
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y + (REG0_S(1) + 0xAF0));
        if (i_this->m2E9E != 0) {
            local_40.x = REG0_F(9) + -100.0f;
        } else {
            local_40.x = REG0_F(10);
        }
        local_40.y = REG0_F(0xb) + i_this->m2EC4;
        local_40.z = REG0_F(0xc);
        MtxPosition(&local_40, &local_4c);
        i_this->m2EAC = actor->eyePos + local_4c;
        cMtx_XrotM(*calc_mtx, REG0_S(2) + 4000);
        local_40.x = 0.0f;
        local_40.y = REG0_F(7);
        local_40.z = REG0_F(8) + 850.0f;
        MtxPosition(&local_40, &local_4c);
        i_this->m2EA0 = actor->current.pos + local_4c;
        if (0x50 < i_this->msFrameCount) {
            i_this->mActionType = bst_class::ACTION_FLY_e;
            i_this->mDamage = 0;
            camera->mCamera.SetTrimSize(0);
            camera->mCamera.Start();
            dMeter_mtrShow();
            dComIfGp_event_reset();
            i_this->m2E9A = 0;
            i_this->m2E98 = 1;
        }
        break;
    case 10:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            bVar2 = false;
            break;
        }
        i_this->m2E9A++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->msFrameCount = 0;
        i_this->m2EC8 = 55.0f;
        i_this->m2EC4 = 0.0f;
        i_this->m2EA0.x = (boss->actor.current.pos.x + REG0_F(1)) - 3200.0f;
        i_this->m2EA0.y = (boss->actor.current.pos.y + REG0_F(2)) - 1100.0f;
        i_this->m2EA0.z = (boss->actor.current.pos.z + REG0_F(3)) - 300.0f;
        i_this->m2EAC = boss->actor.current.pos;
        i_this->m2EAC.y = i_this->m2EAC.y + (REG0_F(0) - 250.0f);
        mDoAud_bgmStreamPlay();
        i_this->m2FE0->setPlaySpeed(1.0f);
        i_this->m2E98 = 0x78;
        // fallthrough
    case 11:
        local_4c.x = -635.0f;
        local_4c.y = 0.0f;
        local_4c.z = 0.0f;
        player->setPlayerPosAndAngle(&local_4c, 0x4000);
        cLib_addCalc2(&i_this->m2EA0.z, boss->actor.current.pos.z + REG0_F(3) + 300.0f, 0.02f, 1.4f);
        if (i_this->msFrameCount == 0x3c) {
            message_set(i_this, 0x170d);
        }
        if (i_this->msFrameCount == 0xb4) {
            msg_end = 1;
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = REG0_S(4) + 200;
        if ((int)iVar13 == iVar14) {
            message_set(i_this, 0x170e);
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = REG0_S(4) + 0x122;
        if ((int)iVar13 == iVar14) {
            msg_end = 1;
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = REG0_S(4) + iVar14;
        if ((int)iVar13 == (int)iVar14 + 0x14) {
            message_set(i_this, 0x170f);
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = (int)REG0_S(4) + 0x14;
        if ((int)iVar13 == REG0_S(4) + iVar14 + 0x186) {
            msg_end = 1;
        }
        if (!((int)i_this->msFrameCount == (REG0_S(4) + iVar14) + (iVar14 + 0x19a))) {
            break;
        }
        i_this->m2E9A = 0xc;
        i_this->msFrameCount = 0;
        i_this->m2EAC = hand[0]->actor.current.pos;
        i_this->m2EAC.y += REG0_F(4) + 200.0f;
        i_this->m2EA0 = hand[0]->actor.current.pos;
        i_this->m2EA0.x += REG0_F(5) - 2000.0f;
        i_this->m2EA0.y += REG0_F(6);
        // fallthrough
    case 12:
        cLib_addCalc2(&i_this->m2EA0.x, hand[0]->actor.current.pos.x - 1200.0f, 0.1f, i_this->m2EC4 * 40.0f);
        cLib_addCalc2(&i_this->m2EC4, 1.0f, 1.0f, 0.01f);
        cLib_addCalc2(&i_this->m2EAC.x, hand[0]->actor.current.pos.x, 0.02f, 50.0f);
        cLib_addCalc2(&i_this->m2EAC.z, hand[0]->actor.current.pos.z, 0.02f, 50.0f);
        if (i_this->msFrameCount == 0x14) {
            hand[0]->m02D4 = 1;
            hand[0]->m02C4 = 1;
            pbVar5 = hand[0];
            mDoAud_seStart(JA_SE_CM_BST_HAND_LIGHT, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
        }
        if (i_this->msFrameCount == 0x3b) {
            i_this->mRoomState = 1;
        }
        if (i_this->msFrameCount == 0x3c) {
            hand[0]->mDamage = 2;
            pbVar5 = hand[0];
            mDoAud_seStart(JA_SE_CM_BST_HAND_EYE_OPEN, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
        }
        if (i_this->msFrameCount == 0x5a) {
            hand[0]->mDamage = 4;
            pbVar5 = hand[0];
            mDoAud_seStart(JA_SE_CM_BST_HAND_OUT_WALL, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
        }
        if (i_this->msFrameCount == 0xa9) {
            i_this->mRoomState = 0;
        }
        if (i_this->msFrameCount != 0xaa) {
            break;
        }
        i_this->m2E9A = 0xd;
        i_this->msFrameCount = 0;
        i_this->m2EC4 = 0.0f;
        i_this->m2EAC = hand[1]->actor.current.pos;
        i_this->m2EAC.y += REG0_F(4) + 200.0f;
        i_this->m2EA0 = hand[1]->actor.current.pos;
        i_this->m2EA0.x += REG0_F(5) - 2000.0f;
        i_this->m2EA0.y += REG0_F(6);
        // fallthrough
    case 13:
        cLib_addCalc2(&i_this->m2EA0.x, hand[1]->actor.current.pos.x - 1200.0f, 0.1f, i_this->m2EC4 * 40.0f);
        cLib_addCalc2(&i_this->m2EC4, 1.0f, 1.0f, 0.01f);
        cLib_addCalc2(&i_this->m2EAC.x, hand[1]->actor.current.pos.x, 0.02f, 50.0f);
        cLib_addCalc2(&i_this->m2EAC.z, hand[1]->actor.current.pos.z, 0.02f, 50.0f);
        if (i_this->msFrameCount == 0x14) {
            hand[1]->m02D4 = 1;
            hand[1]->m02C4 = 1;
            pbVar5 = hand[1];
            mDoAud_seStart(JA_SE_CM_BST_HAND_LIGHT, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
        }
        if (i_this->msFrameCount == 0x3b) {
            i_this->mRoomState = 1;
            i_this->m2ED0 = 0.0f;
        }
        if (i_this->msFrameCount == 0x3c) {
            hand[1]->mDamage = 2;
            pbVar5 = hand[1];
            mDoAud_seStart(JA_SE_CM_BST_HAND_EYE_OPEN, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
        }
        if (i_this->msFrameCount == 0x5a) {
            hand[1]->mDamage = 4;
            pbVar5 = hand[1];
            mDoAud_seStart(JA_SE_CM_BST_HAND_OUT_WALL, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
        }
        if (i_this->msFrameCount == 0xa9) {
            i_this->mRoomState = 0;
        }
        if (i_this->msFrameCount != 0xaa) {
            break;
        }
        i_this->m2E9A = 0xe;
        i_this->msFrameCount = 0;
        i_this->m2EC4 = 0.0f;
        i_this->m2EAC = boss->actor.current.pos;
        i_this->m2EAC.y += REG0_F(7) + 300.0f;
        i_this->m2EA0 = boss->actor.current.pos;
        i_this->m2EA0.x += REG0_F(8) - 2000.0f;
        i_this->m2EA0.y += REG0_F(7) + 300.0f;
        // fallthrough
    case 14:
        if (i_this->msFrameCount >= 0x1E) {
            if (i_this->msFrameCount <= 0x5A) {
                cLib_addCalc2(&i_this->m2EA0.x, boss->actor.current.pos.x - 1000.0f, 0.2f, i_this->m2EC4 * 100.0f);
                cLib_addCalc2(&i_this->m2EC4, 1.0f, 1.0f, 0.05f);
            }
            if (i_this->msFrameCount == 0x1e) {
                boss->m02D4 = 1;
                boss->m02C4 = 1;
                pbVar5 = boss;
                mDoAud_seStart(JA_SE_CM_BST_HEAD_LIGHT, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
            }
            if (i_this->msFrameCount == 0x3b) {
                i_this->mRoomState = 1;
                i_this->m2ED0 = 0.0f;
            }
            if (i_this->msFrameCount == 0x3c) {
                boss->mDamage = 2;
                pbVar5 = boss;
                mDoAud_seStart(JA_SE_CM_BST_HEAD_EYE_OPEN, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
            }
            if (i_this->msFrameCount == 0x5a) {
                boss->mDamage = 4;
                pbVar5 = boss;
                mDoAud_seStart(JA_SE_CM_BST_HEAD_OUT_WALL, &pbVar5->actor.current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&pbVar5->actor)));
            }
            if (i_this->msFrameCount == 0x96) {
                i_this->m2E9A = 0xf;
                boss->mActionType = bst_class::ACTION_FLY_e;
                hand[0]->mActionType = bst_class::ACTION_FLY_e;
                hand[1]->mActionType = bst_class::ACTION_FLY_e;
                boss->mDamage = 0;
                hand[1]->mDamage = 0;
                hand[0]->mDamage = 0;
                i_this->m2EAC = boss->actor.eyePos;
                i_this->m2EAC.y += REG0_F(0);
                i_this->m2EA0 = player->current.pos;
                i_this->m2EA0.x -= REG0_F(1) + 500.0f;
                i_this->m2EA0.y += REG0_F(2) + 100.0f;
                i_this->m2EC8 = REG0_F(4) + 75.0f;
                pJVar7 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_UDEL);
                hand[0]->mpBrkAnm->init(hand[0]->m02C8->getModelData(), pJVar7, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                pJVar8 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_UDEL);
                hand[0]->mpBtkAnm->init(hand[0]->m02C8->getModelData(), pJVar8, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                pJVar7 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_UDER);
                hand[1]->mpBrkAnm->init(hand[1]->m02C8->getModelData(), pJVar7, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                pJVar8 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_UDER);
                hand[1]->mpBtkAnm->init(hand[1]->m02C8->getModelData(), pJVar8, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                pJVar7 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_MUNE);
                boss->mpBrkAnm->init(boss->m02C8->getModelData(), pJVar7, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                pJVar8 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_MUNE);
                boss->mpBtkAnm->init(boss->m02C8->getModelData(), pJVar8, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
                i_this->mBombArrowDropTimer = 500;
            }
        }
        break;
    case 15:
        cLib_addCalc2(&i_this->m2EAC.x, boss->actor.current.pos.x, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m2EAC.y, boss->actor.eyePos.y + REG0_F(0), 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m2EAC.z, boss->actor.current.pos.z, 0.1f, 50.0f);
        i_this->m2EA0 = player->current.pos;
        i_this->m2EA0.x -= REG0_F(1) + 500.0f;
        i_this->m2EA0.y += REG0_F(2) + 100.0f;
        cLib_addCalc2(&i_this->m2EC8, 55.0f, 0.1f, 0.4f);
        if (i_this->msFrameCount == 200) {
            local_58.setall(0.0f);
            pJVar9 = dComIfGp_particle_set(dPa_name::ID_SCENE_81E9, &local_58);
            i_this->m2EF8 = pJVar9;
            JAIZelBasic::zel_basic->field_0x1dd4 = 1;
        }
        if (i_this->msFrameCount == 300) {
            camera->mCamera.SetTrimSize(0);
            camera->mCamera.Start();
            dMeter_mtrShow();
            dComIfGp_event_reset();
            i_this->m2E9A = 0;
            i_this->m2E7C = 10;
            g_dComIfG_gameInfo.save.getMemory().getBit().onStageBossDemo();
            mDoAud_bgmStart(JA_BGM_BST_BATTLE);
            i_this->m2FE4 = 1;
            i_this->m2E98 = 1;
        }
        break;
    case 50:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            bVar2 = false;
            break;
        }
        i_this->m2E9A++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->msFrameCount = 0;
        i_this->m2EC8 = 55.0f;
        i_this->m2EC4 = 0.0f;
        i_this->m2EA0.x = (REG0_F(2) + -500.0f) - 800.0f;
        player->changeOriginalDemo();
        end_brkbtk_set(i_this);
        pJVar9 = i_this->m2EF8;
        if (pJVar9 != NULL) {
            pJVar9->becomeInvalidEmitter();
            i_this->m2EF8 = NULL;
            JAIZelBasic::zel_basic->field_0x1dd4 = 0;
        }
        i_this->m2FE4 = 0;
        i_this->m2E98 = 0x96;
        // fallthrough
    case 51:
        local_4c.x = REG0_F(1) + -300.0f;
        local_4c.y = 0.0f;
        local_4c.z = 0.0f;
        player[0].setPlayerPosAndAngle(&local_4c, 0x4000);
        actor->current.pos.x = 300.0f;
        actor->current.pos.z = 0.0f;
        actor->shape_angle.y = -0x4000;
        i_this->m2EAC = actor->current.pos;
        i_this->m2EAC.y += REG0_F(0) + 300.0f;
        i_this->m2EA0.y = REG0_F(3) + 200.0f;
        i_this->m2EA0.z = 0.0f;
        cLib_addCalc2(&i_this->m2EA0.x, (REG0_F(2) + -500.0f) - 100.0f, 0.2f, i_this->m2EC4 * 10.0f);
        cLib_addCalc2(&i_this->m2EC4, 1.0f, 1.0f, 0.05f);
        if (i_this->msFrameCount < 0x50) {
            i_this->m2ECC = REG0_F(9) + 10.0f;
        }
        if (i_this->msFrameCount == 0x5a) {
            boss->mDamage = 2;
            i_this->mRoomState = 2;
            i_this->m2ED0 = 0.0f;
        }
        if (i_this->msFrameCount == 100) {
            i_this->mRoomState = 3;
        }
        if ((i_this->msFrameCount > 100) && (i_this->msFrameCount < 0x212)) {
            mDoAud_seStart(JA_SE_CM_BST_GOKOU, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->msFrameCount == 0x78) {
            message_set(i_this, 0x1710);
        }
        if (i_this->msFrameCount == 0xf0) {
            msg_end = 1;
        }
        if ((int)i_this->msFrameCount == REG0_S(4) + 0x104) {
            message_set(i_this, 0x1711);
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = REG0_S(4) + 0x15e;
        if (iVar13 == iVar14) {
            msg_end = 1;
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = iVar14 + 0x14;
        if ((int)i_this->msFrameCount == REG0_S(4) + iVar14) {
            message_set(i_this, 0x1712);
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = REG0_S(4) + 0x14;
        if ((int)iVar13 == (int)REG0_S(4) + iVar14 + 500) {
            msg_end = 1;
        }
        if ((int)i_this->msFrameCount == (int)REG0_S(4) + iVar14 + (int)REG0_S(4) + 0x208) {
            message_set(i_this, 0x1713);
        }
        iVar13 = i_this->msFrameCount;
        iVar14 = (int)REG0_S(4) * 2 + 0x1cc;
        if ((int)iVar13 == REG0_S(4) + iVar14 + 0xaa) {
            msg_end = 1;
        }
        if (!((int)i_this->msFrameCount == REG0_S(4) + iVar14 + 200)) {
            break;
        }
        i_this->m2E9A++;
        i_this->msFrameCount = 0;
        i_this->m2EC4 = 0.0f;
        i_this->m2EAC.y = REG0_F(0x10) + 4800.0f;
        i_this->m2EAC.x = 0.0f;
        i_this->m2EAC.z = 0.0f;
        i_this->m2EA0.x = REG0_F(0xd) + -700.0f;
        i_this->m2EA0.y = REG0_F(0xe) + 100.0f;
        i_this->m2EA0.z = REG0_F(0xf) + -300.0f;
        mDoAud_bgmStreamPlay();
        i_this->m2E98 = 1;
        // fallthrough
    case 52:
        if (i_this->msFrameCount <= 0x1e) {
            break;
        }
        i_this->m2E9A++;
        i_this->msFrameCount = 0;
        i_this->m2EC4 = 0.0f;
        player->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
        // fallthrough
    case 53:
        i_this->m2EAC = player->current.pos;
        i_this->m2EAC.y += REG0_F(10) + 100.0f;
        i_this->m2EA0 = player->current.pos;
        i_this->m2EA0.x += REG0_F(0xb) + 150.0f;
        i_this->m2EA0.y += REG0_F(0xc) + 50.0f;
        if (i_this->msFrameCount <= (short)(REG0_S(3) + 0x41)) {
            break;
        }
        i_this->m2E9A++;
        i_this->msFrameCount = 0;
        i_this->m2EC4 = 0.0f;
        i_this->m2EAC.y = REG0_F(0x10) + 4800.0f;
        i_this->m2EAC.x = 0.0f;
        i_this->m2EAC.z = 0.0f;
        i_this->m2EA0.x = REG0_F(0xd) + -700.0f;
        i_this->m2EA0.y = REG0_F(0xe) + 100.0f;
        i_this->m2EA0.z = REG0_F(0xf) + -300.0f;
        i_this->mDamage = 10;
        i_this->mRoomState = 4;
        i_this->m2ED0 = 1.0f;
        dComIfGs_onStageBossEnemy();
        local_40.x = 0.0f;
        local_40.y = 0.0f;
        local_40.z = 0.0f;
        fopAcM_createWarpFlower(&local_40, 0, fopAcM_GetRoomNo(actor), 0);
        // fallthrough
    case 54:
        if ((int)i_this->msFrameCount == REG0_S(4) + 0x16) {
            player->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
        }
        if ((int)i_this->msFrameCount == REG0_S(5) + 0x96) {
            player->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
        }
        cLib_addCalc2(&i_this->m2EAC.y, REG0_F(8) + 200.0f, 0.8f, REG0_F(9) + 300.0f);
        if ((int)i_this->msFrameCount != REG0_S(6) + 0xfa) {
            break;
        }
        i_this->m2E9A++;
        i_this->msFrameCount = 0;
        i_this->m2EC4 = 0.0f;
        i_this->m2EAC = actor->current.pos;
        i_this->m2EAC.y += REG0_F(10) + 100.0f;
        i_this->m2E98 = 100;
        // fallthrough
    case 55:
        cLib_addCalc2(&i_this->m2EAC.x, actor->current.pos.x, 0.2f, 20.0f);
        cLib_addCalc2(&i_this->m2EAC.y, actor->current.pos.y + 100.0f + REG0_F(10), 0.2f, 20.0f);
        cLib_addCalc2(&i_this->m2EAC.z, actor->current.pos.z, 0.2f, 20.0f);
        i_this->m2EA0 = actor->current.pos;
        i_this->m2EA0.x = i_this->m2EA0.x - (REG0_F(0xb) + 1300.0f);
        i_this->m2EA0.y = i_this->m2EA0.y - (REG0_F(0xc) + 450.0f);
        i_this->m2EA0.z = i_this->m2EA0.z - (REG0_F(0xd) + 500.0f);
        local_40 = actor->home.pos - actor->current.pos;
        if (local_40.abs() < 10.0f) {
            dComIfGp_particle_setToon(
                start_smoke_name[i_this->mBstPartType],
                &actor->current.pos,
                &actor->shape_angle,
                NULL,
                0xB9,
                &i_this->mPa_smokeEcallBack,
                fopAcM_GetRoomNo(actor)
            );
            dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            mDoAud_seStart(JA_SE_CM_BST_HEAD_IN_WALL, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            i_this->m2ECC = REG0_F(9) + 10.0f;
            i_this->m112A = REG0_S(8) + 3;
            actor->current.pos = actor->home.pos;
            i_this->m2E9A = 0x38;
            i_this->msFrameCount = 0;
            end_brkbtk_set(i_this);
        }
        break;
    case 56:
        if (i_this->msFrameCount == REG0_S(4) + 50) {
            anm_init(i_this, BST_BCK_HANA_DEMO, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            mDoAud_seStart(JA_SE_CM_BST_HAND_STRAIN, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            i_this->m2E98 = 1;
        }
        if ((s32)i_this->m02B8->getFrame() == 26) {
            cXyz boss_pos;
            cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(7), *calc_mtx);
            cXyz offset(REG0_F(2) + 60.0f, REG0_F(3), REG0_F(4));
            mDoAud_seStart(JA_SE_OBJ_BOMB_EXPLODE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            MtxPosition(&offset, &boss_pos);
            cXyz item_scale(1.0f, 1.0f, 1.0f);
            csXyz item_angle = actor->shape_angle;
            item_angle.y += (s16)(REG0_S(7) + -300);
            i_this->mCreatedItemId = fopAcM_createItemForBoss(&boss_pos, 0, fopAcM_GetRoomNo(actor), &item_angle, &item_scale, 1);
            mDoAud_seStart(JA_SE_CM_BST_ITEM_OUT_NOSE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(0), *calc_mtx);
            cXyz vec(0.0f, 0.0f, 0.0f);
            MtxPosition(&vec, &boss_pos);
            dComIfGp_particle_set(item_smoke_name[1], &boss_pos, &actor->shape_angle, NULL, 0xB9, &i_this->mPa_smokeEcallBack, fopAcM_GetRoomNo(actor));
        }
        if ((s32)i_this->m02B8->getFrame() > 26) {
            fopAc_ac_c* actor = fopAcM_SearchByID(i_this->mCreatedItemId);
            if (actor != NULL) {
                i_this->m2E9A = 57;
                actor->speedF = REG0_F(6) + 65.0f;
            }
        }
        break;
    case 57: {
        fopAc_ac_c* actor = fopAcM_SearchByID(i_this->mCreatedItemId);
        if (actor != NULL) {
            cLib_addCalc2(&i_this->m2EAC.x, actor->current.pos.x, 0.1f, 100.0f);
            cLib_addCalc2(&i_this->m2EAC.y, actor->current.pos.y, 0.1f, 100.0f);
            cLib_addCalc2(&i_this->m2EAC.z, actor->current.pos.z, 0.1f, 100.0f);
            i_this->m2EC8 = REG0_F(4) + 55.0f;
        }
        if (i_this->msFrameCount == 170) {
            camera->mCamera.SetTrimSize(0);
            camera->mCamera.Start();
            dMeter_mtrShow();
            dComIfGp_event_reset();
            i_this->m2E9A = 0;
            i_this->m2E7C = 100;
            i_this->m2E98 = 1;
        }
        break;
    }
    }
    if ((i_this->m2E9A != 0) && bVar2) {
        f32 x = i_this->m2ECC * cM_ssin(i_this->msFrameCount * 0x3300);
        f32 y = i_this->m2ECC * cM_scos(i_this->msFrameCount * 0x3000);
        f32 z = i_this->m2ECC * cM_scos(i_this->msFrameCount * 0x3500);
        cXyz camera_center;
        camera_center.x = i_this->m2EA0.x + x;
        camera_center.y = i_this->m2EA0.y + y;
        camera_center.z = i_this->m2EA0.z + z;
        cXyz camera_eye;
        camera_eye.x = i_this->m2EAC.x - x;
        camera_eye.y = i_this->m2EAC.y - y;
        camera_eye.z = i_this->m2EAC.z - z;
        s16 bank = 7.5f * i_this->m2ECC * cM_scos(i_this->mUpdateLastFacingDirIfMultipleOf32 * 0x1C00);
        camera->mCamera.Set(camera_eye, camera_center, bank, i_this->m2EC8);
        cLib_addCalc0(&i_this->m2ECC, 1.0f, 1.0f);
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->msFrameCount);
        i_this->msFrameCount++;
    }
}

/* 00009FCC-0000A1A4       .text bst_kankyo__FP9bst_class */
void bst_kankyo(bst_class* i_this) {
    switch (i_this->mRoomState) {
    case 0:
        dKy_custom_colset(3, 0, 0.0f);
        break;
    case 1:
        dKy_custom_colset(3, 0, i_this->m2ED0);
        cLib_addCalc2(&i_this->m2ED0, 1.0f, 1.0f, 0.1f);
        break;
    case 2:
        dKy_custom_colset(0, 4, i_this->m2ED0);
        cLib_addCalc2(&i_this->m2ED0, 1.0f, 1.0f, 0.25f);
        break;
    case 3:
        dKy_custom_colset(3, 4, i_this->m2ED0);
        cLib_addCalc0(&i_this->m2ED0, 1.0f, 0.02f);
        break;
    case 4:
        dKy_custom_colset(5, 3, i_this->m2ED0);
        cLib_addCalc0(&i_this->m2ED0, 1.0f, 0.05f);
        break;
    case 5:
        dKy_custom_colset(1, 0, i_this->m2ED0);
        cLib_addCalc0(&i_this->m2ED0, 1.0f, 0.1f);
        break;
    case 6:
        dKy_custom_colset(1, 2, i_this->m2ED0);
        cLib_addCalc2(&i_this->m2ED0, 1.0f, 1.0f, 0.5f);
        if (i_this->m2ED0 >= 1.0f) {
            i_this->mRoomState = 7;
        }
        break;
    case 7:
        dKy_custom_colset(1, 2, i_this->m2ED0);
        cLib_addCalc0(&i_this->m2ED0, 1.0f, 0.5f);
        break;
    case 8:
        dKy_custom_colset(1, 0, i_this->m2ED0);
        cLib_addCalc2(&i_this->m2ED0, 1.0f, 1.0f, 0.1f);
        if (i_this->m2ED0 >= 1.0f) {
            i_this->mRoomState = 1;
        }
        break;
    }
}

/* 0000A1A4-0000A9C8       .text daBst_Execute__FP9bst_class */
static BOOL daBst_Execute(bst_class* i_this) {
    /* Nonmatching - "unk" variables */
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz vec;
    cXyz vec2;
    vec.setall(0.0f);
    i_this->mUpdateLastFacingDirIfMultipleOf32++;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m10FC); i++) {
        if (i_this->m10FC[i] != 0) {
            i_this->m10FC[i]--;
        }
    }
    if (i_this->mState != 0) {
        i_this->mState--;
    }
    if (i_this->mDamageTimer != 0) {
        i_this->mDamageTimer--;
    }
    if (i_this->mHeadHurtAngle != 0) {
        i_this->mHeadHurtAngle--;
    }
    if (i_this->m112A != 0) {
        i_this->m112A--;
    }
    if (i_this->m112C != 0) {
        i_this->m112C--;
    }
    if (i_this->mStateTimer != 0) {
        i_this->mStateTimer--;
    }
    if (l_HIO.m5 == 0) {
        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            if (i_this->m2FE4 != 0) {
                dCam_getBody()->SetTypeForce("Test01", NULL);
            }
            main_cont(i_this);
            if (i_this->mActionType != bst_class::ACTION_HEAD_DAMAGE_e) {
                fopAcM_OffStatus(actor, 0);
                actor->attention_info.flags = 0;
            }
            if (i_this->mActionType != bst_class::ACTION_BEAM_ATTACK_e) {
                for (s32 i = 0; i < 2; i++) {
                    if (i_this->m2ED8[i] != 0) {
                        i_this->m2ED8[i]->becomeInvalidEmitter();
                        i_this->m2ED8[i] = NULL;
                    }
                }
                if (i_this->mRoomState == 7) {
                    i_this->mRoomState = 8;
                }
            }
            if (player->current.pos.y <= -150.0f) {
                i_this->m2FD8->setPlaySpeed(1.0f);
                i_this->m2FD8->setPlayMode(J3DFrameCtrl::EMode_LOOP);
            } else {
                i_this->m2FD8->setPlayMode(J3DFrameCtrl::EMode_NONE);
            }
            i_this->m2FE0->play();
            i_this->m2FD8->play();
            i_this->m2FD4->play();
            mDoMtx_stack_c::transS(0.0f, 0.0f, 0.0f);
            i_this->m2FD0->setBaseTRMtx(mDoMtx_stack_c::now);
            i_this->m2FDC->setBaseTRMtx(mDoMtx_stack_c::now);
        }
        move(i_this);
        if (i_this->mActionType != 0 && i_this->mActionType != bst_class::ACTION_END_DEMO_e) {
            i_this->mAcch.CrrPos(*dComIfG_Bgsp());
            i_this->mAcch.SetGroundUpY(0.0f);
        }
        i_this->m02B8->play(&actor->eyePos, 0, 0);
        if (i_this->m02C4 != 0) {
            i_this->mpTevRegAnimator->play();
            i_this->mpTexMtxAnimator->play();
        }
        if (i_this->m02D4 != 0) {
            i_this->mpBrkAnm->play();
            i_this->mpBtkAnm->play();
        }
    }
    vec2.x = i_this->m10EC.z * cM_ssin(i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 700));
    vec2.y = i_this->m10EC.z * cM_ssin(i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 750));
    vec2.z = i_this->m10EC.z * cM_scos(i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 720));
    cLib_addCalc0(&i_this->m10EC.z, 1.0f, 1.0f);
    i_this->m02B8->getModel()->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos.x + vec2.x, actor->current.pos.y + vec2.y, actor->current.pos.z + vec2.z);
    s16 hurtAng = i_this->mHeadHurtAngle;
    s16 faceDir = i_this->mUpdateLastFacingDirIfMultipleOf32;
    s16 unk4 = hurtAng * (REG0_F(14) + 500.0f) * cM_ssin(faceDir * 0x2100);
    s16 unk5 = hurtAng * (REG0_F(14) + 500.0f) * cM_scos(faceDir * 0x2300);
    s16 bossFaceDir = boss->mUpdateLastFacingDirIfMultipleOf32;
    s16 unk6 = i_this->m112A * (REG0_F(14) + 150.0f) * cM_ssin(bossFaceDir * 0x3600);
    s16 unk7 = i_this->m112A * (REG0_F(14) + 150.0f) * cM_scos(bossFaceDir * 0x4300);
    s16 unk8 = i_this->m112C * (REG0_F(14) + 100.0f) * cM_scos(bossFaceDir * 0x3A00);
    cLib_addCalc0(&i_this->m10F8, 1.0f, REG0_F(3) + 30.0f);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y + unk4 + unk6);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x + unk5 + unk7 + unk8);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    mDoMtx_stack_c::transM(REG0_F(5) + i_this->m1110, REG0_F(6) + i_this->m1114, REG0_F(7) + i_this->m1118);
    cLib_addCalc0(&i_this->m1110, 1.0f, 5.0f);
    cLib_addCalc0(&i_this->m1114, 1.0f, 10.0f);
    cLib_addCalc0(&i_this->m1118, 1.0f, 5.0f);
    i_this->m02B8->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
    i_this->m0388->setBaseTRMtx(mDoMtx_stack_c::now);
    i_this->m02B8->calc();
    MtxTrans(actor->home.pos.x, actor->home.pos.y, actor->home.pos.z, FALSE);
    cMtx_YrotM(*calc_mtx, actor->home.angle.y);
    cMtx_XrotM(*calc_mtx, actor->home.angle.x);
    cMtx_ZrotM(*calc_mtx, actor->home.angle.z);
    i_this->m02C8->setBaseTRMtx(*calc_mtx);
    col_set(i_this);
    if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
        beam_move(i_this);
        demo_camera(i_this);
        bst_kankyo(i_this);
        message_cont(i_this);
        for (s32 j = 0, i = 0; j < 2; j++) {
            fpc_ProcID proc_id = i_this->m2E90[j];
            fopAc_ac_c* actor = (fopAc_ac_c*)fopAcM_SearchByID(proc_id);
            if (actor != NULL) {
                cMtx_copy(i_this->m02B8->getModel()->getAnmMtx(j + 4), *calc_mtx);
                MtxPosition(&vec, &actor->current.pos);
                actor->max_health = 2;
                actor->health = i_this->mEyeHealth[j];
                if (i_this->m2E74[j] == 0 && i_this->mEyeHealth[j] > 0 && i_this->mActionType != bst_class::ACTION_HEAD_DAMAGE_e &&
                    i_this->mActionType != bst_class::ACTION_END_DEMO_e && i_this->mActionType != bst_class::ACTION_STAY_e)
                {
                    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                    actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
                    if ((s8)i == 0) {
                        i++;
                        fopAcM_seStart(actor, JA_SE_CM_BST_HEAD_WORKING, 0);
                    }
                } else {
                    fopAcM_OffStatus(actor, 0);
                    actor->attention_info.flags = 0;
                }
            }
        }
    }
    return TRUE;
}

/* 0000A9C8-0000A9D0       .text daBst_IsDelete__FP9bst_class */
static BOOL daBst_IsDelete(bst_class*) {
    return TRUE;
}

/* 0000A9D0-0000AADC       .text daBst_Delete__FP9bst_class */
static BOOL daBst_Delete(bst_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Bst");
    if (i_this->mHioSet != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.m4);
    }
    if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m2E90); i++) {
            fopAc_ac_c* actor = (fopAc_ac_c*)fopAcM_SearchByID(i_this->m2E90[i]);
            if (actor != NULL) {
                fopAcM_delete(actor);
            }
        }
    }
    i_this->mPa_smokeEcallBack.remove();
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m03B8); i++) {
        mDoAud_seDeleteObject(&i_this->m03B8[i]);
    }
    return TRUE;
}

static u16 set_btk_d[3] = {BST_BTK_BST_START, BST_BTK_LH_START, BST_BTK_RH_START};
static u16 set_brk_d[3] = {BST_BRK_BST_START, BST_BRK_LH_START, BST_BRK_RH_START};
static u16 set_za_btk_d[3] = {BST_BTK_MUNE_START, BST_BTK_UDEL_START, BST_BTK_UDER_START};
static u16 set_za_brk_d[3] = {BST_BRK_MUNE_START, BST_BRK_UDEL_START, BST_BRK_UDER_START};

/* 0000AADC-0000B2D0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    bst_class* i_this = (bst_class*)a_this;
    i_this->m02B8 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bst", set_bdl_d[i_this->mBstPartType]),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bst", set_bck_d[i_this->mBstPartType]),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    if (i_this->m02B8 == NULL || i_this->m02B8->getModel() == NULL) {
        return FALSE;
    }
    if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
        for (u16 i = 0; i < i_this->m02B8->getModel()->getModelData()->getJointNum(); i++) {
            if (i >= 9 && i <= 12) {
                i_this->m02B8->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBackHead);
            }
        }
        i_this->m02B8->getModel()->setUserArea((u32)i_this);
    }
    i_this->m0388 = mDoExt_J3DModel__create(i_this->m02B8->getModel()->getModelData(), 0, 0x11020203);
    if (i_this->m0388 == NULL) {
        return FALSE;
    }
    i_this->mpTexMtxAnimator = new mDoExt_btkAnm();
    if (i_this->mpTexMtxAnimator == NULL) {
        return FALSE;
    }
    J3DAnmTextureSRTKey* key = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", set_btk_d[i_this->mBstPartType]);
    s32 res = i_this->mpTexMtxAnimator->init(i_this->m02B8->getModel()->getModelData(), key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE);
    if (res == 0) {
        return FALSE;
    }
    i_this->mpTevRegAnimator = new mDoExt_brkAnm();
    if (i_this->mpTevRegAnimator == NULL) {
        return FALSE;
    }
    res = i_this->mpTevRegAnimator->init(
        i_this->m02B8->getModel()->getModelData(),
        (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", set_brk_d[i_this->mBstPartType]),
        TRUE,
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        0,
        -1,
        false,
        FALSE
    );
    if (res == 0) {
        return FALSE;
    }
    J3DModelData* modelData;
    if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Bst", BST_BDL_TAMA);
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0390); i++) {
            i_this->m0390[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
            if (i_this->m0390[i] == NULL) {
                return FALSE;
            }
        }
        modelData = (J3DModelData*)dComIfG_getObjectRes("Bst", BST_BDL_HBSITA1);
        i_this->m2FD0 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->m2FD0 == NULL) {
            return FALSE;
        }
        i_this->m2FD4 = new mDoExt_btkAnm();
        if (i_this->m2FD4 == NULL) {
            return FALSE;
        }
        res = i_this->m2FD4->init(
            modelData, (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", BST_BTK_HBSITA1), TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE
        );
        if (res == 0) {
            return FALSE;
        }
        i_this->m2FD8 = new mDoExt_brkAnm();
        if (i_this->m2FD8 == NULL) {
            return FALSE;
        }
        res = i_this->m2FD8->init(
            modelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_HBSITA1), TRUE, J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, false, FALSE
        );
        if (res == 0) {
            return FALSE;
        }
        modelData = (J3DModelData*)dComIfG_getObjectRes("Bst", BST_BDL_HBYOKO1);
        i_this->m2FDC = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->m2FDC == NULL) {
            return FALSE;
        }
        i_this->m2FE0 = new mDoExt_brkAnm();
        if (i_this->m2FE0 == NULL) {
            return FALSE;
        }
        res = i_this->m2FE0->init(
            modelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", BST_BRK_HBYOKO1), TRUE, J3DFrameCtrl::EMode_LOOP, 0.0f, 0, -1, false, FALSE
        );
        if (res == 0) {
            return FALSE;
        }
    }
    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Bst", set_za_bdl[i_this->mBstPartType]));
    i_this->m02C8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m02C8 == NULL) {
        return FALSE;
    }
    i_this->mpBtkAnm = new mDoExt_btkAnm();
    if (i_this->mpBtkAnm == NULL) {
        return FALSE;
    }
    res = i_this->mpBtkAnm->init(
        modelData,
        (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bst", set_za_btk_d[i_this->mBstPartType]),
        TRUE,
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        0,
        -1,
        false,
        FALSE
    );
    if (res == 0) {
        return FALSE;
    }
    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm == NULL) {
        return FALSE;
    }
    res = i_this->mpBrkAnm->init(
        modelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bst", set_za_brk_d[i_this->mBstPartType]), TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
    );
    if (res == 0) {
        return FALSE;
    }
    return TRUE;
}

/* 0000B318-0000B860       .text daBst_Create__FP10fopAc_ac_c */
static cPhs_State daBst_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl cc_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 100.0f,
            /* Height */ 400.0f,
        }},
    };
    static dCcD_SrcCyl core_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 &
                ~AT_TYPE_LIGHT & ~AT_TYPE_GRAPPLING_HOOK,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsOther_e,
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
            /* Radius */ 50.0f,
            /* Height */ 200.0f,
        }},
    };
    static dCcD_SrcSph finger_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 30.0f,
        }},
    };
    static dCcD_SrcSph eye_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 &
                ~AT_TYPE_LIGHT & ~AT_TYPE_GRAPPLING_HOOK,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
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
            /* Radius */ 30.0f,
        }},
    };
    static dCcD_SrcSph beam_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
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
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 60.0f,
        }},
    };

    fopAcM_ct(a_this, bst_class);
    cPhs_State res;
    bst_class* i_this = (bst_class*)a_this;
    fopAc_ac_c* actor = &i_this->actor;
    res = dComIfG_resLoad(&i_this->mPhs, "Bst");
    if (res == cPhs_COMPLEATE_e) {
        i_this->mPa_smokeEcallBack.setFollowOff();
        i_this->mBstPartType = fopAcM_GetParam(i_this) & 0xFF;
        int heap_size = 0x96000;
        if (!fopAcM_entrySolidHeap(actor, useHeapInit, heap_size)) {
            return cPhs_ERROR_e;
        }
        actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
        if (hio_set == 0) {
            i_this->mHioSet = 1;
            hio_set = 1;
            // Possible bug: why is "Armos Knight" here?
            l_HIO.m4 = mDoHIO_createChild("デグアモス", &l_HIO);
        }
        i_this->mAcch.Set(fopAcM_GetPosition_p(actor), fopAcM_GetOldPosition_p(actor), actor, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(actor));
        i_this->mAcch.OffSameActorChk();
        i_this->mAcchCir.SetWall(200.0f, 10.0f);
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            boss = i_this;
            msg = fpcM_ERROR_PROCESS_ID_e;
        }
        if (i_this->mBstPartType == bst_class::Type_LEFT_HAND_e) {
            hand[0] = i_this;
        }
        if (i_this->mBstPartType == bst_class::Type_RIGHT_HAND_e) {
            hand[1] = i_this;
        }
        u8 weight;
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            weight = 255;
        } else {
            weight = 230;
        }
        i_this->mStts.Init(weight, 0xFF, actor);
        i_this->mHandHurtCyl.Set(core_cyl_src);
        i_this->mHandHurtCyl.SetStts(&i_this->mStts);
        if (i_this->mBstPartType == bst_class::Type_HEAD_e) {
            i_this->mHeadHurtCyl.Set(cc_cyl_src);
            i_this->mHeadHurtCyl.SetStts(&i_this->mStts);
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mEyeSphs); i++) {
                i_this->mEyeSphs[i].Set(eye_sph_src);
                i_this->mEyeSphs[i].SetStts(&i_this->mStts);
            }
            actor->health = 3;
            actor->max_health = 3;
            i_this->mEyeHealth[1] = 2;
            i_this->mEyeHealth[0] = 2;
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m2E90); i++) {
                i_this->m2E90[i] = fopAcM_create(PROC_ATT, 100, &actor->current.pos, fopAcM_GetRoomNo(actor));
            }
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mCcD_beams); i++) {
                i_this->mCcD_beams[i].Set(beam_sph_src);
                i_this->mCcD_beams[i].SetStts(&i_this->mStts);
            }
        } else {
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mFingerSphs); i++) {
                i_this->mFingerSphs[i].Set(finger_sph_src);
                i_this->mFingerSphs[i].SetStts(&i_this->mStts);
            }
            actor->health = 4;
            actor->max_health = 4;
        }
    }
    f32 fVar = cM_rndFX(32768.0f);
    i_this->mUpdateLastFacingDirIfMultipleOf32 = fVar;
#if VERSION > VERSION_DEMO
    i_this->mEnvLight = actor->tevStr;
    i_this->m2F20 = actor->tevStr;
#endif
    return res;
}

static actor_method_class l_daBst_Method = {
    (process_method_func)daBst_Create,
    (process_method_func)daBst_Delete,
    (process_method_func)daBst_Execute,
    (process_method_func)daBst_IsDelete,
    (process_method_func)daBst_Draw,
};

actor_process_profile_definition g_profile_BST = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BST,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bst_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BST,
    /* Actor SubMtd */ &l_daBst_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
