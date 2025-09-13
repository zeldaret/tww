/**
 * d_a_bst.cpp
 * Boss - Gohdan
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bst.h"
#include "d/actor/d_a_bomb.h"
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
    /* 0x4 */ s8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
};

static u8 hio_set;
static daBst_HIO_c l_HIO;

/* 000000EC-00000110       .text __ct__11daBst_HIO_cFv */
daBst_HIO_c::daBst_HIO_c() {
    field_0x4 = -1;
    field_0x5 = 0;
    field_0x6 = 0;
}

static bst_class* boss;
static bst_class* hand[2];

static fpc_ProcID msg;
static s8 msg_end;


static u16 set_bdl_d[3] = {BST_BDL_BST, BST_BDL_LHAND, BST_BDL_RHAND};
static u16 set_za_bdl[3] = {BST_BDL_MUNE, BST_BDL_UDEL, BST_BDL_UDER};
static u16 set_bck_d[3] = {BST_BCK_BST_SLEEP, BST_BCK_LH_SLEEP, BST_BCK_RH_SLEEP};
static u16 fly_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_FLY, BST_BCK_RH_FLY};
static u16 damage_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_DAMAGE, BST_BCK_RH_DAMAGE};
static u16 down_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_DOWN, BST_BCK_RH_DOWN};

/* 00000110-00000174       .text message_set__FP9bst_classUl */
static BOOL message_set(bst_class* i_this, unsigned long msg_no) {
    if (msg == fpcM_ERROR_PROCESS_ID_e) {
        msg = fopMsgM_messageSet(msg_no, i_this);
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
static void set_hand_AT(bst_class* i_this, unsigned char param_2) {
    for (int i = 0; i < (s32)ARRAY_SIZE(i_this->mCcD_fingers); i++) {
        if (param_2 != 0) {
            i_this->mCcD_fingers[i].OnAtSetBit();
        } else {
            i_this->mCcD_fingers[i].OffAtSetBit();
        }
        i_this->mCcD_fingers[i].SetAtSpl(dCcG_At_Spl_UNK1);
    }
}

/* 00000268-000002C0       .text set_hand_CO__FP9bst_classUc */
static void set_hand_CO(bst_class* i_this, unsigned char param_2) {
    for (int i = 0; i < (s32)ARRAY_SIZE(i_this->mCcD_fingers); i++) {
        if (param_2 != 0) {
            i_this->mCcD_fingers[i].OnCoSetBit();
        } else {
            i_this->mCcD_fingers[i].OffCoSetBit();
        }
    }
}

/* 000002C0-000003E8       .text anm_init__FP9bst_classifUcfi */
static void anm_init(bst_class* i_this, int param_2, float morf, unsigned char loop_mode, float play_speed, int sound_idx) {
    if (sound_idx >= 0) {
        void* sound = dComIfG_getObjectRes("Bst", sound_idx);
        J3DAnmTransform* bckAnm = (J3DAnmTransform*) dComIfG_getObjectRes("Bst", param_2);
        i_this->field_0x02B8->setAnm(bckAnm, loop_mode, morf, play_speed, 0.0f, -1.0f, sound);
    } else {
        J3DAnmTransform* bckAnm = (J3DAnmTransform*) dComIfG_getObjectRes("Bst", param_2);
        i_this->field_0x02B8->setAnm(bckAnm, loop_mode, morf, play_speed, 0.0f, -1.0f, NULL);
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
            mDoMtx_copy(model->getAnmMtx(jnt_no), *calc_mtx);

            if (jnt_no == 9) {
                mDoMtx_YrotM(*calc_mtx, -i_this->field_0x2E78[1]);
            } else if (jnt_no == 12) {
                mDoMtx_YrotM(*calc_mtx, i_this->field_0x2E78[1]);
            } else if (jnt_no == 10) {
                mDoMtx_YrotM(*calc_mtx, -i_this->field_0x2E78[0]);
            } else if (jnt_no == 11) {
                mDoMtx_YrotM(*calc_mtx, i_this->field_0x2E78[0]);
            }

            model->setAnmMtx(jnt_no, *calc_mtx);
            mDoMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000550-000005B4       .text beam_draw__FP9bst_class */
static void beam_draw(bst_class* i_this) {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->field_0x0390); i++) {
        if (i_this->field_0x04E4[i]) {
            mDoExt_modelUpdateDL(i_this->field_0x0390[i]);
        }
    }
}

/* 000005B4-00000950       .text daBst_Draw__FP9bst_class */
static BOOL daBst_Draw(bst_class* i_this) {
    /* Nonmatching */
    cXyz temp;
    cXyz shadow_pos;

    if (i_this->field_0x02B4 != 0 && boss->field_0x2E9A > 0 && boss->field_0x2E9A < 10) {
        return TRUE;
    }
    J3DModel* model_2B8 = i_this->field_0x02B8->getModel();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
    g_env_light.setLightTevColorType(model_2B8, &i_this->tevStr);

    i_this->mpTexMtxAnimator->entry(model_2B8->getModelData());
    i_this->mpTevRegAnimator->entry(model_2B8->getModelData());
    i_this->field_0x02B8->entryDL();

    i_this->mpTexMtxAnimator->remove(model_2B8->getModelData());
    i_this->mpTevRegAnimator->remove(model_2B8->getModelData());

    J3DModel* model_388 = i_this->field_0x0388;
    for (u16 i = 0; i < model_2B8->getModelData()->getJointNum(); i++) {
        model_388->setAnmMtx(i, model_2B8->getAnmMtx(i));
    }
    for (u16 i = 0; i < model_2B8->getModelData()->getWEvlpMtxNum(); i++) {
        model_388->setWeightAnmMtx(i, model_2B8->getWeightAnmMtx(i));
    }
    mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(0), *calc_mtx);

    shadow_pos.setall(0.0f);
    MtxPosition(&temp, &shadow_pos);
    shadow_pos.y += REG0_F(1) * 10.0f;

    i_this->mShadowID = dComIfGd_setRealShadow(
        i_this->mShadowID,
        TRUE,
        model_388,
        &shadow_pos,
        (REG0_F(2) * 10.0f) + 2000.0f,
        0.0f,
        &i_this->tevStr
    );

    J3DModel* model_2C8 = i_this->field_0x02C8;
    i_this->mpBtkAnm->entry(model_2C8->getModelData());
    i_this->mpBrkAnm->entry(model_2C8->getModelData());

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->home.pos, &i_this->mEnvLight);
    g_env_light.setLightTevColorType(model_2C8, &i_this->mEnvLight);
    mDoExt_modelUpdateDL(model_2C8);
    if (i_this->field_0x02B4 == 0) {
        if (i_this->field_0x2E98 > 1) {
            mDoGph_gInf_c::setBlureRate(i_this->field_0x2E98);
            mDoGph_gInf_c::onBlure();
        } else if (i_this->field_0x2E98 == 1) {
            i_this->field_0x2E98 = 0;
            mDoGph_gInf_c::offBlure();
        }

        beam_draw(i_this);
        // yup, this is a static var.
        static cXyz center_pos(0.0f, 0.0f, 0.0f);

        g_env_light.settingTevStruct(TEV_TYPE_BG0, &center_pos, &i_this->field_0x2F20);
        g_env_light.setLightTevColorType(i_this->field_0x2FDC, &i_this->field_0x2F20);
        i_this->field_0x2FE0->entry(i_this->field_0x2FDC->getModelData());

        mDoExt_modelUpdateDL(i_this->field_0x2FDC);
        g_env_light.setLightTevColorType(i_this->field_0x2FD0, &i_this->field_0x2F20);

        i_this->field_0x2FD8->entry(i_this->field_0x2FD0->getModelData());
        i_this->field_0x2FD4->entry(i_this->field_0x2FD0->getModelData());
        mDoExt_modelUpdateDL(i_this->field_0x2FD0);
    }
    dSnap_RegistFig(DSNAP_TYPE_BST, i_this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 00000950-00000B1C       .text pos_move__FP9bst_classUc */
static void pos_move(bst_class* i_this, unsigned char param_2) {
    cXyz vec;

    if (!param_2) {
        vec = i_this->mTargetPos - i_this->current.pos;

        s16 y_angle = cM_atan2s(vec.x, vec.z);
        f32 dist = std::sqrtf(vec.x * vec.x + vec.z * vec.z);

        s16 unk_angle = -cM_atan2s(vec.y, dist);
        cLib_addCalcAngleS2(&i_this->current.angle.y, y_angle, REG0_S(3) + 5,
            i_this->field_0x10EC.x * i_this->field_0x10EC.y);
        cLib_addCalcAngleS2(&i_this->current.angle.x, unk_angle, REG0_S(3) + 5,
            i_this->field_0x10EC.x * i_this->field_0x10EC.y);
    }
    cLib_addCalc2(&i_this->field_0x10EC.y, 1.0f, 1.0f, 0.05f);

    vec.x = 0.0f;
    vec.y = 0.0f;
    vec.z = i_this->speedF;

    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    MtxPosition(&vec, &i_this->speed);
    i_this->current.pos += i_this->speed;
}

static u16 start_bck_d[] = {BST_BCK_BST_START, BST_BCK_LH_START, BST_BCK_RH_START};
static u16 start2_bck_d[] = {0, BST_BCK_LH_START2, BST_BCK_RH_START2};
static u16 start_smoke_name[] = {dPa_name::ID_SCENE_A1DE, dPa_name::ID_SCENE_A1DC, dPa_name::ID_SCENE_A1DD};

/* 00000B1C-00000E58       .text stay__FP9bst_class */
static void stay(bst_class* i_this) {
    /* Nonmatching */
    fopAcM_OffStatus(i_this, 0);

    i_this->attention_info.flags = 0;
    i_this->mState = 10;

    switch (i_this->mDamage) {
        case 0:
            anm_init(i_this, set_bck_d[i_this->field_0x02B4], 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mDamage++;
            break;
        case 2:
            anm_init(i_this, start_bck_d[i_this->field_0x02B4], 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mDamage++;
            break;
        case 4: {
            cXyz vec;
            vec.x = 0.0f;
            vec.y = 0.0f;
            if (i_this->field_0x02B4 != 0) {
                anm_init(i_this, start2_bck_d[i_this->field_0x02B4], 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                vec.z = REG0_F(11) + 400.0f;
            } else {
                vec.z = 10000.0f;
            }
            dComIfGp_particle_setToon(
                start_smoke_name[i_this->field_0x02B4],
                &i_this->current.pos,
                &i_this->current.angle,
                NULL,
                0xB9,
                &i_this->mPa_smokeEcallBack,
                fopAcM_GetRoomNo(i_this)
            );

            dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            boss->field_0x2ECC = REG0_F(10) + 15.0f;
            i_this->mDamage++;
            mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);

            cXyz pos_vec;
            MtxPosition(&vec, &pos_vec);
            i_this->mTargetPos = i_this->current.pos + pos_vec;
            i_this->field_0x10FC[3] = 0xF;

            // fall-through.
        }
        case 5:
            if (i_this->field_0x02B4 != 0 && i_this->field_0x10FC[3] != 0) {
                for (s32 i = 2; i <= 16; i++) {
                    mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(i), *calc_mtx);

                    cXyz pos_vec;
                    cXyz vec(0.0f, 0.0f, 0.0f);
                    MtxPosition(&vec, &pos_vec);

                    dComIfGp_particle_setSimple(dPa_name::ID_SCENE_81D5, &pos_vec);
                }
            }
            cLib_addCalc2(&i_this->current.pos.x, i_this->mTargetPos.x, 0.05f, 10.0f);
            cLib_addCalc2(&i_this->current.pos.z, i_this->mTargetPos.z, 0.05f, 10.0f);
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
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    if (i_this->field_0x02B4 != 0 && i_this->field_0x10D8 == 6) {
        i_this->health = 4;
    }
    i_this->field_0x10D8 = 1;
    if (i_this->mState == 0) {
        set_hand_CO(i_this, 1);
    }

    if (boss->field_0x2E9A != 0 || (i_this->field_0x10D4 & 0x1F) == 0) {
        if (cM_rndF(1.0f) < 0.5f) {
            i_this->field_0x10E8 = player->shape_angle.y;
        }
    }

    switch (i_this->mDamage) {
        case 0: {
            anm_init(i_this, fly_bck_d[i_this->field_0x02B4], 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);

            J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", damage_brk_d[i_this->field_0x02B4]);
            i_this->mpTevRegAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                reg_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
            );

            i_this->mpTevRegAnimator->setFrame(REG0_S(8) + 0x1D);
            i_this->field_0x02D4 = 1;
            i_this->field_0x02C4 = 1;
            i_this->mDamage++;
            break;
        }
        case 1: {
            J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", fly_brk_d[i_this->field_0x02B4]);
            i_this->mpTevRegAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                reg_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
            );

            J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", fly_btk_d[i_this->field_0x02B4]);
            i_this->mpTexMtxAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
            );

            i_this->mDamage++;
            i_this->field_0x10EC.y = 0.0f;
            break;
        }
        case 3: {
            mDoMtx_YrotS(*calc_mtx, i_this->field_0x10E8);

            cXyz vec;
            vec.z = REG0_F(4) + 800.0f;
            vec.y = REG0_F(3) + 200.0f;
            if (i_this->field_0x02B4 == 0) {
                vec.x = 0.0;
                vec.z = REG0_F(4) + 1000.0f;
                if (boss->field_0x2E7C == 11) {
                    vec.y = REG0_F(3) + 350.0f;
                }
            } else if (i_this->field_0x02B4 == 1) {
                vec.x = -(REG0_F(2) + 800.0f);
            } else if (i_this->field_0x02B4 == 2) {
                vec.x = REG0_F(2) + 800.0f;
            }

            cXyz pos_vec;
            MtxPosition(&vec, &pos_vec);
            i_this->mTargetPos = i_this->current.pos + pos_vec;

            if (i_this->field_0x02B4 == 0) {
                f32 dist = i_this->mTargetPos.absXZ();
                if (dist > REG0_F(9) + 1350.0f) {
                    dist /= REG0_F(9) + 1350.0f;
                    i_this->mTargetPos.x *= dist;
                    i_this->mTargetPos.z *= dist;
                }
            }

            cXyz target_diff = i_this->mTargetPos - i_this->current.pos;
            if (target_diff.abs() > REG0_F(12) + 300.0f) {
                f32 speed_target;
                if (i_this->field_0x02B4 == 0 && boss->field_0x2E7C == 11) {
                    speed_target = 10.0f;
                } else {
                    speed_target = 30.0f;
                }
                cLib_addCalc2(&i_this->speedF, speed_target, 1.0f, REG0_F(13) + 2.0f);
            } else {
                cLib_addCalc0(&i_this->speedF, 1.0f, REG0_F(14) + 1.0f);
            }

            i_this->field_0x10EC.x = REG0_F(5) + 1500.0f;

            cLib_addCalcAngleS2(
                &i_this->shape_angle.y,
                fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0)),
                10,
                0x400
            );

            s16 target_x;
            if (i_this->field_0x02B4 == 0 && boss->field_0x2E7C == 11) {
                target_x = 0;
            } else {
                target_x = 3000;
            }

            cLib_addCalcAngleS2(&i_this->shape_angle.x, target_x, 10, 256);
            cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 8, 512);
            cLib_addCalc2(&i_this->field_0x10EC.z, REG0_F(11) + 50.0f, 1.0f, 2.0f);
            break;
        }
    }

    pos_move(i_this, 0);
    if (i_this->field_0x02B4 == 0 && i_this->field_0x2E84 == 0
            && (dComIfGs_getArrowNum() == 0 || dComIfGs_getBombNum() == 0)) {
        i_this->field_0x2E84 = 600;
        i_this->field_0x10D6 = 20;
        i_this->mDamage = 0;
    }
}

static u16 downa_bck_d[] = {BST_BCK_BST_FLY, BST_BCK_LH_GOO, BST_BCK_RH_GOO};

/* 000014E8-00001C14       .text down_attack__FP9bst_class */
static void down_attack(bst_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    s8 bVar2 = true;
    s8 bVar4 = false;

    cLib_addCalcAngleS2(&i_this->shape_angle.x, 0, 10, 0x200);

    switch (i_this->mDamage) {
        case 0:
            i_this->mDamage = 1;

            i_this->field_0x10EC.y = 0.0f;
            i_this->mTargetPos = player->current.pos;
            i_this->mTargetPos.y += REG0_F(7) + 300.0f;
            i_this->field_0x10FC[0] = 100;
            break;
        case 1: {
            cLib_addCalc2(&i_this->speedF, 40.0f, 1.0f, REG0_F(13) + 1.0f);
            i_this->field_0x10EC.x = REG0_F(5) + 2000.0f;

            cXyz target_diff = i_this->mTargetPos - i_this->current.pos;
            if (target_diff.abs() < REG0_F(12) + 200.0f || i_this->field_0x10FC[0] == 0) {
                i_this->mDamage++;
            }
            cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 4, 0x400);
            break;
        }
        case 2: {
            bVar2 = false;
            cLib_addCalc2(&i_this->current.pos.x, i_this->mTargetPos.x, 0.5f, std::abs(i_this->speed.x));
            cLib_addCalc2(&i_this->current.pos.y, i_this->mTargetPos.y, 0.5f, std::abs(i_this->speed.y));
            cLib_addCalc2(&i_this->current.pos.z, i_this->mTargetPos.z, 0.5f, std::abs(i_this->speed.z));

            cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 4, 0x4000);

            cXyz target_diff = i_this->mTargetPos - i_this->current.pos;
            if (target_diff.abs() < REG0_F(13) + 50.0f) {
                anm_init(i_this, downa_bck_d[i_this->field_0x02B4], 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->mDamage++;
                i_this->speed.y = 0.0f;

                i_this->field_0x10FC[0] = 30;
                if (REG0_S(0) == 1) {
                    i_this->field_0x2E6E = i_this->shape_angle.y + 0x4000;
                } else {
                    i_this->field_0x2E6E = i_this->shape_angle.y - 0x4000;
                }

                if (i_this->field_0x02B4 == 2) {
                    i_this->mFacingDir = 0x4000;
                } else {
                    i_this->mFacingDir = -0x4000;
                }
                fopAcM_seStartCurrent(i_this, JA_SE_CM_BST_HAND_GRIP, 0);
            }
            break;
        }
        case 3:
            bVar2 = false;
            cLib_addCalc2(&i_this->field_0x1114, -200.0f, 1.0f, 25.0f);
            cLib_addCalc2(&i_this->current.pos.x, i_this->mTargetPos.x, 0.5f, std::abs(i_this->speed.x));
            cLib_addCalc2(&i_this->current.pos.z, i_this->mTargetPos.z, 0.5f, std::abs(i_this->speed.z));

            cLib_addCalcAngleS2(&i_this->shape_angle.z, i_this->mFacingDir, 4, 0x1000);
            cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->field_0x2E6E, 4, 0x1000);
            i_this->current.pos.y += i_this->speed.y;

            if (i_this->field_0x10FC[0] == 0) {
                set_hand_AT(i_this, 1);
                i_this->speed.y -= REG0_F(3) + 60.0f;

                if (i_this->current.pos.y <= REG0_F(4) + 150.0f) {
                    i_this->current.pos.y = REG0_F(4) + 150.0f;
                    i_this->speed.y = 0.0f;

                    dComIfGp_getVibration().StartShock(
                        REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f)
                    );
                    i_this->field_0x112A = REG0_S(7) + 10;

                    fopAcM_seStartCurrent(i_this, JA_SE_CM_BST_1_HAND_ATTACK, 0);
                    i_this->mDamage++;
                    i_this->field_0x10FC[0] = 30;

                    cXyz particle_pos;
                    particle_pos.x = i_this->current.pos.x;
                    particle_pos.z = i_this->current.pos.z;
                    particle_pos.y = 1.0f;

                    dComIfGp_particle_setProjection(dPa_name::ID_SCENE_C1D6, &particle_pos);
                    dComIfGp_particle_setToon(
                        dPa_name::ID_SCENE_A1D8,
                        &particle_pos,
                        NULL,
                        NULL,
                        0xB9,
                        &i_this->mPa_smokeEcallBack,
                        fopAcM_GetRoomNo(i_this)
                    );
                }
            } else {
                i_this->speed.y += REG0_F(14) + 0.5f;
            }
            break;
        case 4:
            bVar2 = false;
            cLib_addCalc2(&i_this->field_0x1114, -200.0f, 1.0f, 25.0f);
            if (i_this->field_0x10FC[0] == 0) {
                bVar4 = true;
            }
            break;
    }

    if (bVar2) {
        pos_move(i_this, 0);
    }
    if (bVar4 || i_this->mBgS_Acch.ChkWallHit()) {
        i_this->field_0x10D6 = 1;
        i_this->mDamage = 0;

        fopAcM_seStartCurrent(i_this, JA_SE_CM_BST_HAND_GRIP_OPEN, 0);
        if (!bVar4) {
            s32 hand_index = 2 - i_this->field_0x02B4;
            if (hand[hand_index]->field_0x10D6 == 10) {
                hand[hand_index]->field_0x10D6 = 1;
                hand[hand_index]->mDamage = 0;
                hand[hand_index]->speedF = 0.0f;
            }
        }
    }
}

/* 00001C14-000023C8       .text paa_attack__FP9bst_class */
static void paa_attack(bst_class*) {
    /* Nonmatching */
}

/* 00002404-00002E08       .text kumi_attack__FP9bst_class */
static void kumi_attack(bst_class*) {
    /* Nonmatching */
}

/* 00002E08-0000318C       .text harai_attack__FP9bst_class */
static void harai_attack(bst_class*) {
    /* Nonmatching */
}

static u16 sleep_btk_d[] = {BST_BCK_BST_SLEEP, BST_BTK_LH_END, BST_BTK_RH_END};
static u16 sleep_brk_d[] = {BST_BRK_BST, BST_BRK_LH_END, BST_BRK_RH_END};

/* 0000318C-00003470       .text sleep__FP9bst_class */
static void sleep(bst_class* i_this) {
    /* Nonmatching */
    i_this->field_0x10D8 = 6;
    set_hand_CO(i_this, 1);

    i_this->mState = 10;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;

    cLib_addCalc2(&i_this->field_0x10EC.z, REG0_F(11) + 50.0f, 1.0f, 2.0f);
    switch (i_this->mDamage) {
        default:
            return;
        case 0: {
            anm_init(i_this, down_bck_d[i_this->field_0x02B4], 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);

            J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", down_bck_d[i_this->field_0x02B4]);
            i_this->mpTevRegAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                reg_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
            );

            J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", sleep_btk_d[i_this->field_0x02B4]);
            i_this->mpTexMtxAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
            );

            i_this->mDamage++;
            fopAcM_seStart(i_this, JA_SE_CM_BST_HAND_EYE_CLOSE, 0);

            // fall-through.
        }
        case 1:
            if (i_this->field_0x10FC[0] == 0) {
                i_this->mTargetPos.x = cM_rndFX(1500.0f);
                i_this->mTargetPos.y = cM_rndF(200.0f) + 600.0f;
                if (i_this->field_0x02B4 == 1) {
                    i_this->mTargetPos.y += 350.0f;
                }
                i_this->mTargetPos.z = cM_rndFX(1500.0f);
                i_this->field_0x10FC[0] = cM_rndF(30.0f);
            }
            i_this->field_0x10EC.x = REG0_F(5) + 500.0f;
            i_this->speedF = REG0_F(6) + 10.0f;
            if (i_this->field_0x10FC[1] == 0) {
                i_this->field_0x10D6 = 1;
                i_this->mDamage = 0;
                fopAcM_seStart(i_this, JA_SE_CM_BST_HAND_EYE_OPEN, 0);
            }
            break;
    }

    pos_move(i_this, 0);
}

/* 00003470-000035BC       .text beam_set__FP9bst_class */
static void beam_set(bst_class* i_this) {
    /* Nonmatching */
    for (s32 i = 0; i < 10; i++) {
        if (i_this->field_0x04E4[i]) {
            continue;
        }
        i_this->field_0x04E4[i] = 1;

        mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(REG0_S(5) + 3), *calc_mtx);
        cXyz vec(0.0f, 0.0f, 0.0f);
        MtxPosition(&vec, &i_this->field_0x03B8[i]);

        i_this->field_0x04A8[i] = i_this->shape_angle;
        mDoMtx_YrotS(*calc_mtx, i_this->field_0x04A8[i].y);
        mDoMtx_XrotM(*calc_mtx, i_this->field_0x04A8[i].x);

        vec.set(0.0f, 0.0f, REG0_F(12) + 160.0f);
        // MtxPosition call here.
        MtxPosition(&vec, &i_this->field_0x0430[i]);

        i_this->field_0x10A8[i] = 1.0f;
        return;
    }
}

/* 000035BC-00003B94       .text beam_attack__FP9bst_class */
static void beam_attack(bst_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    s8 bVar3 = false;
    i_this->field_0x2E74[0] = 10;
    i_this->field_0x2E74[1] = 10;
    if (i_this->field_0x2E84 < 120) {
        i_this->field_0x2E84 = 120;
    }

    cXyz actor_vec = player->current.pos - i_this->current.pos;
    actor_vec.y += i_this->field_0x10D0;

    s16 angle = cM_atan2s(actor_vec.x, actor_vec.z);
    cLib_addCalcAngleS2(&i_this->shape_angle.y, angle, 4, 0x800);

    f32 dist = fopAcM_searchActorDistance(i_this, dComIfGp_getPlayer(0));
    if (dist < REG0_F(9) + 500.0f || bVar3) {
        i_this->mRoomState = 8;
        i_this->field_0x10D6 = 1;
        i_this->mDamage = 0;
        i_this->speedF = 0.0f;

        fopAcM_seStart(i_this, JA_SE_CM_BST_MOUTH_CLOSE, 0);
        s16 sVar6;
        if (i_this->health == 0) {
            sVar6 = cM_rndF(50.0f) + 100.0f;
        } else if (i_this->health == 1) {
            sVar6 = cM_rndF(70.0f) + 120.0f;
        } else if (i_this->health == 2) {
            sVar6 = cM_rndF(80.0f) + 140.0f;
        } else if (i_this->health == 3) {
            sVar6 = cM_rndF(90.0f) + 150.0f;
        } else {
            sVar6 = cM_rndF(100.0f) + 150.0f;
        }
        i_this->field_0x2E7E[1] = sVar6;
    }

    for (s32 i = 0; i < 2; i++) {
        JPABaseEmitter* emitter = i_this->field_0x2ED8[i];
        if (emitter != NULL) {
            emitter->setGlobalRTMatrix(i_this->field_0x02B8->getModel()->getAnmMtx(0));
        }
    }
}

/* 00003B94-00003DD8       .text damage__FP9bst_class */
static void damage(bst_class* i_this) {
    /* Nonmatching */
    i_this->mState = 10;

    switch (i_this->mDamage) {
        default:
            return;
        case 0: {
            if (i_this->field_0x02B4 != 0) {
                anm_init(i_this, damage_bck_d[i_this->field_0x02B4], 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }

            J3DAnmTevRegKey* reg_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", damage_brk_d[i_this->field_0x02B4]);
            i_this->mpTevRegAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                reg_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
            );

            J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", damage_btk_d[i_this->field_0x02B4]);
            i_this->mpTexMtxAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
            );

            i_this->mDamage++;
            i_this->field_0x10FC[0] = 30;
            break;
        }
        case 1:
            break;
    }

    if (i_this->field_0x10FC[0] == 0) {
        if (i_this->field_0x02B4 != 0 && i_this->health <= 0) {
            i_this->field_0x10D6 = 6;
            i_this->field_0x10FC[1] = 300;

            if (i_this->field_0x02B4 == 1) {
                if (hand[0]->field_0x10D6 != 6) {
                    mDoAud_bgmStart(JA_BGM_UNK_120);
                }
            } else if (hand[1]->field_0x10D6 != 6) {
                mDoAud_bgmStart(JA_BGM_UNK_121);
            }
        } else {
            i_this->field_0x10D6 = 1;
            i_this->speedF = 0.0f;
        }

        i_this->mDamage = 0;
    }
}

/* 00003DD8-00003EC4       .text bom_eat_check__FP9bst_class */
static BOOL bom_eat_check(bst_class* i_this) {
    if (i_this->mHandHurtCollisionCcD_Cyl.ChkCoHit()) {

        cCcD_Obj* hit_obj = i_this->mHandHurtCollisionCcD_Cyl.GetCoHitObj();
        if (hit_obj != NULL) {
            fopAc_ac_c* actor = (fopAc_ac_c*) hit_obj->GetAc();
            daBomb_c* bomb = (daBomb_c*) actor;

            if (actor != NULL && fopAcM_GetName(actor) == PROC_BOMB &&
                bomb->getBombCheck_Flag() == 0 && bomb->getBombRestTime() > 1)
            {
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
    /* Nonmatching */
    cXyz temp;
    cXyz v;
    f32 dist;

    i_this->mState = 10;
    i_this->field_0x2E74[0] = 10;
    i_this->field_0x2E74[1] = 10;
    cLib_addCalcAngleS2(&i_this->shape_angle.x, 0, 8, 512);
    cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 8, 512);
    cLib_addCalc0(&i_this->field_0x10EC.z, 1.0f, 5.0f);

    switch (i_this->mDamage) {
        case 0: {
            i_this->mDamage++;
            i_this->field_0x10FC[0] = 40;
            i_this->speedF = 0.0f;
            i_this->speed.y = 0.0f;

            J3DAnmTevRegKey* key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_BST_END);
            i_this->mpTevRegAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
            );

            J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_BST_END);
            i_this->mpTexMtxAnimator->init(
                i_this->field_0x02B8->getModel()->getModelData(),
                srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
            );

            fopAcM_seStart(i_this, JA_SE_CM_BST_HEAD_EYE_CLOSE, 0);
            mDoAud_bgmStart(JA_BGM_UNK_123);
            // fallthrough
        }
        case 1:
            v.x = i_this->current.pos.x;
            v.z = i_this->current.pos.z;
            v.y = 0.0f;

            dist = v.abs();
            if (dist > REG0_F(9) + 1350.0f) {
                dist = (REG0_F(9) + 1350.0f) / dist;
                cLib_addCalc2(&i_this->current.pos.x, v.x * dist, 0.2f, 30.0f);
                cLib_addCalc2(&i_this->current.pos.z, v.z * dist, 0.2f, 30.0f);
            }

            if (i_this->field_0x10FC[0] == 0) {
                i_this->current.pos.y += i_this->speed.y;
                i_this->speed.y -= REG0_F(13) + 5.0f;

                if (i_this->current.pos.y <= REG0_F(14)) {
                    i_this->current.pos.y = REG0_F(13);
                    temp.set(0.0f, 1.0f, 0.0f);

                    dComIfGp_getVibration().StartShock(REG0_S(2) + 7, -0x21, temp);
                    dComIfGp_particle_setToon(dPa_name::ID_SCENE_A1DB, &i_this->current.pos);
                    i_this->field_0x112A = REG0_S(7) + 4;

                    fopAcM_seStart(i_this, JA_SE_CM_BST_HEAD_FALL, 0);
                    fopAcM_seStart(i_this, JA_SE_CM_BST_MOUTH_OPEN, 0);
                    anm_init(i_this, BST_BCK_KUTI_OPEN, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    i_this->mDamage++;
                    i_this->speed.y = 0.0f;
                }
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
    }
}

/* 000049A8-00004BCC       .text head_hukki__FP9bst_class */
static void head_hukki(bst_class* i_this) {
    /* Nonmatching */
    switch (i_this->mDamage) {
        case 0:
            i_this->mDamage++;
            i_this->field_0x10FC[0] = REG0_S(0) + 40;
            i_this->field_0x10F8 = 0.0f;
            i_this->field_0x10EC.y = 0.0f;
            // fall-through
        case 1:
            cLib_addCalc2(&i_this->field_0x10F8, REG0_F(4) + 4000.0f, 1.0f, REG0_F(5) + 100.0f);
            if (i_this->field_0x10FC[0] == 0) {
                i_this->mDamage++;
                i_this->field_0x10FC[0] = REG0_S(1) + 80;
            }
            break;
        case 2:
            cLib_addCalc0(&i_this->field_0x10F8, 1.0f, REG0_F(6) + 50.0f);
            if (i_this->field_0x10FC[0] == 0) {
                i_this->field_0x10D6 = 1;
                i_this->mDamage = 0;
                i_this->speedF = 0.0f;
                i_this->field_0x10EC.y = 0.0f;
                i_this->mEyeHealth[1] = 2;
                i_this->mEyeHealth[0] = 2;
            }
            break;
    }

    i_this->shape_angle.x = i_this->field_0x10F8 *
        cM_ssin(i_this->field_0x10D4 * (REG0_S(6) + 700));
    i_this->shape_angle.z = i_this->field_0x10F8 *
        cM_ssin(i_this->field_0x10D4 * (REG0_S(6) + 600));

    cLib_addCalc2(&i_this->current.pos.y, REG0_F(11) + 400.0f, 0.05f, i_this->field_0x10EC.y * 40.0f);
    cLib_addCalc2(&i_this->field_0x10EC.z, REG0_F(11) + 50.0f, 1.0f, 2.0f);
    cLib_addCalc2(&i_this->field_0x10EC.y, 1.0f, 1.0f, 0.02f);
}

/* 00004BCC-000051E0       .text col_set__FP9bst_class */
static void col_set(bst_class* i_this) {
    /* Nonmatching */
    cXyz vec;
    cXyz pos_vec;

    if (i_this->field_0x02B4 == 0) {
        mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(8),  *calc_mtx);

        vec.set(REG0_F(0) + (-30.0f), REG0_F(1), REG0_F(2) + (-100.0f));
        MtxPosition(&vec, &pos_vec);

        i_this->mHeadHurtCollisionCcD_Cyl.SetC(pos_vec);
        i_this->mHeadHurtCollisionCcD_Cyl.SetH(REG0_F(3) + 600.0f);
        i_this->mHeadHurtCollisionCcD_Cyl.SetR(REG0_F(4) + 180.0f);
        dComIfG_Ccsp()->Set(&i_this->mHeadHurtCollisionCcD_Cyl);
        i_this->mHeadHurtCollisionCcD_Cyl.OffTgSetBit();


        vec.set(REG0_F(5) + 150.0f, REG0_F(6), REG0_F(7) + 70.0f);
        MtxPosition(&vec, &pos_vec);

        i_this->mHandHurtCollisionCcD_Cyl.SetC(pos_vec);
        i_this->mHandHurtCollisionCcD_Cyl.SetH(REG0_F(8) + 100.0f);
        i_this->mHandHurtCollisionCcD_Cyl.SetR(REG0_F(9) + 100.0f);
        dComIfG_Ccsp()->Set(&i_this->mHandHurtCollisionCcD_Cyl);

        vec.set(REG0_F(11) + 250.0f, 0.0f, 0.0f);
        MtxPosition(&vec, &i_this->eyePos);

        vec.setall(0.0f);
        for (s32 i = 0; i < 2; i++) {
            mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(i + 4), *calc_mtx);
            MtxPosition(&vec, &pos_vec);

            s16 unk = i_this->field_0x2E74[i];
            if (unk != 0 || i_this->mEyeHealth[i] <= 0) {
                if (unk != 0) {
                    i_this->field_0x2E74[i]--;
                }

                pos_vec.y += 10000.0f;
                cLib_addCalcAngleS2(&i_this->field_0x2E78[i], REG0_S(8) + 11000, 1, 0x400);
            } else {
                cLib_addCalcAngleS2(&i_this->field_0x2E78[i], 0, 8, 0x200);
            }

            i_this->mBstEyeCcD_Spheres[i].SetC(pos_vec);
            i_this->mBstEyeCcD_Spheres[i].SetR(REG0_F(14) + 60.0f);
            dComIfG_Ccsp()->Set(&i_this->mBstEyeCcD_Spheres[i]);
        }
    } else {
        vec.setall(0.0f);
        f32 radius = 0.0f;

        if (i_this->field_0x10D6 == 13) {
            radius = REG0_F(16) + 50.0f;
        }

        for (s32 i = 0; i < 15; i++) {
            mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(i + 2), *calc_mtx);
            MtxPosition(&vec, &pos_vec);

            i_this->mCcD_fingers[i].SetC(pos_vec);
            i_this->mCcD_fingers[i].SetR(REG0_F(14) + 50.0f + radius);

            dComIfG_Ccsp()->Set(&i_this->mCcD_fingers[i]);
        }

        mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(17), *calc_mtx);

        static f32 te_x[4] = {70.0f, 70.0f, 70.0f, 70.0f};
        static f32 te_y[4] = {70.0f, -70.0f, 70.0f, -70.0f};
        static f32 te_z[4] = {90.0f, 90.0f, -30.0f, -30.0f};

        for (s32 i = 0; i < 4; i++) {
            vec.x = te_x[i];
            if (i_this->field_0x02B4 == 2) {
                vec.x = vec.x * -1.0f;
            }
            vec.y = te_y[i];
            vec.z = te_z[i];

            MtxPosition(&vec, &pos_vec);
            i_this->mCcD_fingers[i + 15].SetC(pos_vec);
            i_this->mCcD_fingers[i + 15].SetR(REG0_F(15) + 65.0f + radius);
            dComIfG_Ccsp()->Set(&i_this->mCcD_fingers[i + 15]);
        }

        if (i_this->field_0x02B4 == 2) {
            vec.set(-(REG0_F(15) + 100.0f), REG0_F(16), -(REG0_F(17) + 40.0f));
            MtxPosition(&vec, &pos_vec);

            vec.set(-(REG0_F(15) + 100.0f), REG0_F(16), REG0_F(18) + 10.0f);
            MtxPosition(&vec, &i_this->eyePos);
        } else {
            vec.set(REG0_F(15) + 100.0f, REG0_F(16), REG0_F(17) + 40.0f);
            MtxPosition(&vec, &pos_vec);

            vec.set(REG0_F(15) + 100.0f, REG0_F(16), -(REG0_F(18) + 10.0f));
            MtxPosition(&vec, &i_this->eyePos);
        }

        i_this->mHandHurtCollisionCcD_Cyl.SetC(pos_vec);
        i_this->mHandHurtCollisionCcD_Cyl.SetH(REG0_F(8) + 140.0f);
        i_this->mHandHurtCollisionCcD_Cyl.SetR(REG0_F(9) + 150.0f);
        dComIfG_Ccsp()->Set(&i_this->mHandHurtCollisionCcD_Cyl);
    }

    i_this->attention_info.position = i_this->eyePos;
}

/* 000051E0-00005224       .text player_way_check__FP9bst_class */
static BOOL player_way_check(bst_class* i_this) {
    s16 angle_diff = i_this->shape_angle.y - dComIfGp_getPlayer(0)->shape_angle.y;
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
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    i_this->mCcD_Stts.Move();

    if (i_this->mDamageTimer == 0) {
        s8 bVar1 = false;
        cCcD_Obj* hit_obj;

        if (i_this->field_0x02B4 == 0 && i_this->mHeadHurtCollisionCcD_Cyl.ChkTgHit()) {
            hit_obj = i_this->mHeadHurtCollisionCcD_Cyl.GetTgHitObj();
            bVar1 = true;
        } else {
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mCcD_fingers); i++) {
                if (i_this->mCcD_fingers[i].ChkTgHit()) {
                    hit_obj = i_this->mCcD_fingers[i].GetTgHitObj();
                    bVar1 = true;
                }
            }
        }

        if (bVar1) {
            def_se_set(i_this, hit_obj, 0x42);
            i_this->mDamageTimer = 7;
        }
    }

    if (i_this->mState == 0) {
        if (i_this->field_0x02B4 == 0) {
            if (i_this->mBstEyeCcD_Spheres[0].ChkTgHit() || i_this->mBstEyeCcD_Spheres[1].ChkTgHit() != 0) {
                i_this->mState = 10;
                if (player_way_check(i_this)) {
                    cCcD_Obj* hit_obj;
                    u32 eye_index;
                    if (i_this->mBstEyeCcD_Spheres[0].ChkTgHit()) {
                        eye_index = 0;
                        hit_obj = i_this->mBstEyeCcD_Spheres[0].GetTgHitObj();
                    } else {
                        eye_index = 1;
                        hit_obj = i_this->mBstEyeCcD_Spheres[1].GetTgHitObj();
                    }

                    if (i_this->mRoomState != 1) {
                        i_this->mRoomState = 8;
                    }
                    i_this->field_0x10D6 = 5;
                    i_this->mDamage = 0;

                    fopAcM_seStart(i_this, JA_SE_CM_BST_EYE_HIT, 0);
                    i_this->mEyeHealth[eye_index]--;
                    if (i_this->mEyeHealth[eye_index] <= 0) {
                        // Check the other eye.
                        if (i_this->mEyeHealth[1 - eye_index] <= 0) {
                            i_this->field_0x10D6 = 7;
                            i_this->mDamage = 0;
                        }
                        fopAcM_seStart(i_this, JA_SE_CM_BST_EYE_BREAK, 0);
                    }

                    i_this->mHeadHurtSpeed = REG0_F(11) + 70.0f;
                    i_this->mHeadHurtAngle = REG0_S(2) + 7;

                    cXyz player_vec = i_this->current.pos - player->current.pos;
                    i_this->mHurtRecoilAngle1 = cM_atan2s(player_vec.x, player_vec.z);

                    f32 xz2 = SQUARE(player_vec.x) + SQUARE(player_vec.z);
                    i_this->mHurtRecoilAngle2 = -cM_atan2s(player_vec.y, std::sqrtf(xz2));

                    i_this->speedF = 0.0f;


                    cXyz* hit_pos = i_this->mBstEyeCcD_Spheres[eye_index].GetTgHitPosP();
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0010, hit_pos);

                    cXyz scale;
                    scale.x = scale.y = scale.z = 2.0f;
                    csXyz angle;
                    angle.x = angle.z = 0;
                    angle.y = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0));

                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, hit_pos, &angle, &scale);

                    dKy_SordFlush_set(*hit_pos, 1);
                }
            }
        } else {
            if (i_this->mHandHurtCollisionCcD_Cyl.ChkTgHit()) {
                i_this->mState = 10;
                if (player_way_check(i_this)) {

                    cXyz* hit_pos = i_this->mHandHurtCollisionCcD_Cyl.GetTgHitPosP();

                    cXyz scale(2.0f, 2.0f, 2.0f);
                    csXyz angle;
                    angle.x = angle.z = 0;
                    angle.y = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0));
                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, hit_pos, &angle, &scale);

                    cXyz vec;
                    vec.x = hit_pos->x;
                    vec.y = i_this->mHandHurtCollisionCcD_Cyl.GetTgHitPosP()->y;
                    vec.z = i_this->mHandHurtCollisionCcD_Cyl.GetTgHitPosP()->z;

                    dKy_SordFlush_set(vec, 1);
                    i_this->field_0x10D6 = 5;
                    i_this->mDamage = 0;

                    s32 hand_index = 2 - i_this->field_0x02B4;
                    if (hand[hand_index]->field_0x10D6 > 9) {
                        hand[hand_index]->field_0x10D6 = 1;
                        hand[hand_index]->mDamage = 0;
                        hand[hand_index]->speedF = 0.0f;
                    }
                }
            }
        }
    }
}

static u16 item_smoke_name[2] = {dPa_name::ID_SCENE_A1DF, dPa_name::ID_SCENE_A1E0};

/* 0000591C-00005D9C       .text hana_demo__FP9bst_class */
static void hana_demo(bst_class* i_this) {
    /* Nonmatching */
    i_this->mState = 10;

    s16 angle = cM_atan2s(-i_this->current.pos.x, -i_this->current.pos.z);
    cLib_addCalcAngleS2(&i_this->shape_angle.y, angle, 10, 0x400);
    cLib_addCalcAngleS2(&i_this->shape_angle.x, 0, 10, 0x400);
    cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 10, 0x400);
    cLib_addCalc2(&i_this->current.pos.y, REG0_F(11) + 400.0f, 0.05f, 30.0f);

    switch (i_this->mDamage) {
        case 0:
            i_this->mDamage++;
            i_this->field_0x10FC[0] = 40;
            i_this->speedF = 0.0f;
            i_this->speed.y = 0.0f;

            anm_init(
                i_this, BST_BCK_HANA_DEMO, 5.0f,
                J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->field_0x2E9A = 1;
            fopAcM_seStartCurrent(i_this, JA_SE_CM_BST_HAND_STRAIN, 0);
            break;
        case 1:
            break;
        default:
            return;
    }

    cXyz vec(i_this->current.pos.x, 0, i_this->current.pos.z);
    f32 dist = vec.abs();
    if (dist > REG0_F(9) + 1350.0f) {
        f32 angle = (REG0_F(9) + 1350.0f) / dist;
        cLib_addCalc2(&i_this->current.pos.x, vec.x * angle, 0.2f, 30.0f);
        cLib_addCalc2(&i_this->current.pos.z, vec.z * angle, 0.2f, 30.0f);
    }

    if ((s32)i_this->field_0x02B8->getFrame() > 26) {
        fopAc_ac_c* item = fopAcM_SearchByID(i_this->mCreatedItemId);
        if (item != NULL) {
            fopAcM_OnStatus(item, fopAcStts_UNK4000_e);
        }
    }

    if ((s32)i_this->field_0x02B8->getFrame() == 26) {
        int itemNo;
        if (dComIfGs_getArrowNum() == 0) {
            itemNo = dItem_ARROW_10_e;
            cMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(6), *calc_mtx);
            i_this->field_0x2E9E = 0;
        } else {
            itemNo = dItem_BOMB_5_e;
            cMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(7), *calc_mtx);
            i_this->field_0x2E9E = 1;
        }

        vec.set(REG0_F(2) + 60.0f, REG0_F(3), REG0_F(4));

        if (itemNo != -35) {
            fopAcM_seStart(i_this, JA_SE_OBJ_BOMB_EXPLODE, 0);

            cXyz pos_vec;
            MtxPosition(&vec, &pos_vec);
            i_this->mCreatedItemId = fopAcM_createItem(
                &pos_vec,
                itemNo,
                -1,
                fopAcM_GetRoomNo(i_this),
                0,
                NULL,
                0xB,
                NULL
            );

            fopAcM_seStart(i_this, JA_SE_CM_BST_ITEM_OUT_NOSE, 0);
            mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(0), *calc_mtx);

            vec.setall(0.0f);
            MtxPosition(&vec, &pos_vec);

            dComIfGp_particle_setToon(
                item_smoke_name[i_this->field_0x2E9E],
                &pos_vec,
                &i_this->shape_angle,
                NULL,
                0xB9,
                &i_this->mPa_smokeEcallBack,
                fopAcM_GetRoomNo(i_this)
            );
        }
    }
}

static u16 set_btk_d[3] = {BST_BTK_BST_START, BST_BTK_LH_START, BST_BTK_RH_START};
static u16 set_brk_d[3] = {BST_BRK_BST_START, BST_BRK_LH_START, BST_BRK_RH_START};
static u16 set_za_btk_d[3] = {BST_BTK_MUNE_START, BST_BTK_UDEL_START, BST_BTK_UDER_START};
static u16 set_za_brk_d[3] = {BST_BRK_MUNE_START, BST_BRK_UDEL_START, BST_BRK_UDER_START};

/* 00005D9C-00006088       .text end_demo__FP9bst_class */
static void end_demo(bst_class* i_this) {
    /* Nonmatching */
    i_this->mState = 10;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;

    switch (i_this->mDamage) {
        case 0:
            i_this->mDamage++;
            // fall-through
        case 1:
            if ((s32)i_this->field_0x02B8->mFrameCtrl.getFrame() == 20) {
                fopAcM_seStart(i_this, JA_SE_CM_BST_JUMP_L, 0);
            }
            break;
        case 2:
            anm_init(
                i_this, BST_BCK_BST_HIRAKU, 1.0f,
                J3DFrameCtrl::EMode_NONE, 1.0f, -1
            );
            i_this->mDamage++;

            i_this->field_0x2EF4 = dComIfGp_particle_set(dPa_name::ID_SCENE_81E8, &i_this->current.pos);
            if (i_this->field_0x2EF4 != NULL) {
                i_this->field_0x2EF4->setGlobalRTMatrix(i_this->field_0x02B8->getModel()->getAnmMtx(0));
            }

            break;
        case 10:
            if (i_this->field_0x02B4 == 0) {
                anm_init(i_this, fly_bck_d[0], 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            } else {
                anm_init(i_this, set_bck_d[i_this->field_0x02B4], 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            }
            i_this->mDamage++;
            // fall-through
        case 11:
            cLib_addCalc2(&i_this->current.pos.x, i_this->home.pos.x, 0.1f, REG0_F(9) + 5.0f);
            cLib_addCalc2(&i_this->current.pos.y, i_this->home.pos.y, 0.1f, REG0_F(9) + 5.0f);
            cLib_addCalc2(&i_this->current.pos.z, i_this->home.pos.z, 0.1f, REG0_F(9) + 5.0f);
            cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->home.angle.y, 10, 0x80);
            cLib_addCalcAngleS2(&i_this->shape_angle.x, i_this->home.angle.x, 10, 0x80);
            cLib_addCalcAngleS2(&i_this->shape_angle.z, i_this->home.angle.z, 10, 0x80);
            break;
    }

    if (i_this->field_0x02B4 == 0) {
        for (s32 i = 0; i < 4; i++) {

        }
    }
}

/* 00006088-00006418       .text move__FP9bst_class */
static void move(bst_class* i_this) {
    /* Nonmatching */
    s8 bVar1;

    if (i_this->field_0x02B4 != 0 && boss->field_0x2E9A > 0 && boss->field_0x2E9A < 10) {
        if (boss->field_0x2E7C == 11) {
            i_this->field_0x10D6 = 1;
        } else {
            i_this->field_0x10D6 = 6;
        }
        i_this->mDamage = 0;
        i_this->speedF = 0.0f;
    } else {
        set_hand_AT(i_this, 0);
        set_hand_CO(i_this, 0);

        i_this->mHeadHurtCollisionCcD_Cyl.OffAtHitBit();
        bVar1 = false;
        switch (i_this->field_0x10D6) {
            case 0:
                bVar1 = true;
                stay(i_this);
                break;
            case 1:
                bVar1 = true;
                fly(i_this);
                break;
            case 5:
                damage(i_this);
                break;
            case 6:
                sleep(i_this);
                break;
            case 7:
                head_damage(i_this);
                break;
            case 8:
                head_hukki(i_this);
                break;
            case 10:
                bVar1 = true;
                down_attack(i_this);
                break;
            case 11:
                bVar1 = true;
                paa_attack(i_this);
                break;
            case 12:
                bVar1 = true;
                kumi_attack(i_this);
                break;
            case 13:
                bVar1 = true;
                harai_attack(i_this);
                break;
            case 14:
                beam_attack(i_this);
                break;
            case 20:
                hana_demo(i_this);
                break;
            case 22:
                end_demo(i_this);
                break;
        }

        if (bVar1) {
            cXyz pos_diff = i_this->current.pos - i_this->old.pos;
            u32 dist = (u32) (pos_diff.abs() * 3.5f);

            if (dist > 100) {
                dist = 100;
            }

            if (i_this->field_0x02B4 == 0) {
                fopAcM_seStart(i_this, JA_SE_CM_BST_HEAD_WORKING, dist);
            } else {
                fopAcM_seStart(i_this, JA_SE_CM_BST_HAND_WORKING, dist);
            }
        }

        damage_check(i_this);

        dCcD_Stts* stts = &i_this->mCcD_Stts;
        if (stts != NULL) {
            i_this->current.pos.x += stts->GetCCMoveP()->x;
            i_this->current.pos.y += stts->GetCCMoveP()->y;
            i_this->current.pos.z += stts->GetCCMoveP()->z;
        }

        cXyz vec;
        if (i_this->mHeadHurtSpeed > 0.01f) {
            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = i_this->mHeadHurtSpeed;
            mDoMtx_YrotS(*calc_mtx, i_this->mHurtRecoilAngle1);
            mDoMtx_XrotM(*calc_mtx, i_this->mHurtRecoilAngle2);

            cXyz pos_vec;
            MtxPosition(&vec, &pos_vec);

            i_this->current.pos += pos_vec;
            cLib_addCalc0(&i_this->mHeadHurtSpeed, 1.0f, 4.0f);
        }
    }
}

/* 00006418-00006DC0       .text main_cont__FP9bst_class */
static void main_cont(bst_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    if (i_this->field_0x2E9A == 0) {
        if (i_this->field_0x2E84 != 0) {
            i_this->field_0x2E84--;
        }

        for (s32 i = 0; i < 3; i++) {
            if (i_this->field_0x2E7E[i] != 0) {
                i_this->field_0x2E7E[i]--;
            }
        }

        switch (i_this->field_0x2E7C) {
            case 0:
                i_this->field_0x2E7C = 1;
                break;
            case 1:
                if (!dComIfGs_isStageBossEnemy() || REG0_S(5) != 0) {
                    fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
                    if (dComIfGs_isStageBossDemo()) {
                        i_this->field_0x2FE4 = 1;
                        mDoAud_bgmStart(JA_BGM_BST_BATTLE);

                        boss->field_0x10D6 = 1;
                        hand[0]->field_0x10D6 = 1;
                        hand[1]->field_0x10D6 = 1;
                        boss->mDamage = 0;
                        hand[1]->mDamage = 0;
                        hand[0]->mDamage = 0;

                        i_this->field_0x2E7C = 10;

                        J3DAnmTevRegKey* key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_UDEL);
                        hand[0]->mpBrkAnm->init(
                            hand[0]->field_0x02C8->getModelData(),
                            key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
                        );

                        J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_UDEL);
                        hand[0]->mpBtkAnm->init(
                            hand[0]->field_0x02C8->getModelData(),
                            srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
                        );

                        key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_UDER);
                        hand[1]->mpBrkAnm->init(
                            hand[1]->field_0x02C8->getModelData(),
                            key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
                        );

                        srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_UDER);
                        hand[1]->mpBtkAnm->init(
                            hand[1]->field_0x02C8->getModelData(),
                            srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
                        );

                        key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_MUNE);
                        boss->mpBrkAnm->init(
                            boss->field_0x02C8->getModelData(),
                            key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
                        );

                        srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_MUNE);
                        boss->mpBtkAnm->init(
                            boss->field_0x02C8->getModelData(),
                            srt_key, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE
                        );
                        i_this->field_0x2E84 = 400;
                        i_this->field_0x2FE0->setPlaySpeed(1.0f);
                    } else {
                        hand[1]->mState = 10;
                        hand[0]->mState = 10;
                        boss->mState = 10;

                        if (player->current.pos.abs() > 700.0f) {
                            i_this->field_0x2E9A = 10;
                            i_this->field_0x2E7C = 2;
                        }
                    }
                }
                break;
            case 10:
                i_this->field_0x2E7C = 11;
                fopAcM_OffStatus(i_this, fopAcStts_UNK4000_e);
                i_this->field_0x2E7E[0] = 100;
                break;
            case 11:
                if (i_this->field_0x2E7E[0] == 0 && boss->field_0x10D6 != 14) {
                    boss->mBgS_AcchCir.SetWall(200.0f, 300.0f);
                    hand[0]->mBgS_AcchCir.SetWall(200.0f, 200.0f);
                    hand[1]->mBgS_AcchCir.SetWall(200.0f, 200.0f);

                    if (cM_rndF(1.0f) < 0.2f || REG0_S(1) != 0) {
                        if (cM_rndF(1.0f) < 0.5f) {
                            if (hand[0]->field_0x10D6 < 10 && hand[0]->mStateTimer == 0) {
                                hand[0]->field_0x10D6 = 13;
                                hand[0]->mDamage = 0;
                            } else if (hand[1]->field_0x10D6 < 10 && hand[1]->mStateTimer == 0) {
                                hand[1]->field_0x10D6 = 13;
                                hand[1]->mDamage = 0;
                            }
                        }
                    } else {
                        f32 threshold;
                        if (i_this->health == 0) {
                            threshold = 1.0f - 0.3f;
                        } else if (i_this->health == 1) {
                            threshold = 0.5f;
                        } else if (i_this->health == 2) {
                            threshold = 0.3f;
                        } else if (i_this->health == 3) {
                            threshold = 0.2f;
                        }

                        if (cM_rndF(1.0f) < threshold || REG0_S(0) != 0) {
                            if (hand[0]->field_0x10D6 < 5 && hand[1]->field_0x10D6 < 5
                                    && hand[0]->mStateTimer == 0 && hand[1]->mStateTimer == 0) {
                                hand[0]->field_0x10D6 = 12;
                                hand[0]->mDamage = 0;
                                hand[1]->field_0x10D6 = 12;
                                hand[1]->mDamage = 0;
                            }
                        } else {
                            if (cM_rndF(1.0f) < 0.5f) {
                                if (hand[0]->field_0x10D6 < 5 && hand[1]->field_0x10D6 < 5
                                        && hand[0]->mStateTimer == 0 && hand[1]->mStateTimer == 0) {
                                    hand[0]->field_0x10D6 = 11;
                                    hand[0]->mDamage = 0;
                                    hand[1]->field_0x10D6 = 11;
                                    hand[1]->mDamage = 0;
                                } else {
                                    if (cM_rndF(1.0f) < 0.5f) {
                                        if (hand[0]->field_0x10D6 < 5 && hand[0]->mStateTimer == 0) {
                                            hand[0]->field_0x10D6 = 10;
                                            hand[0]->mDamage = 0;
                                        }
                                    } else {
                                        if (hand[1]->field_0x10D6 < 5 && hand[1]->mStateTimer == 0) {
                                            hand[1]->field_0x10D6 = 10;
                                            hand[1]->mDamage = 0;
                                        }
                                    }
                                }
                            }
                        }

                        s16 unk;
                        if (i_this->health == 0) {
                            unk = cM_rndF(30.0f) + 30.0f;
                        } else if (i_this->health == 1) {
                            unk = cM_rndF(40.0f) + 50.0f;
                        } else {
                            unk = cM_rndF(50.0f) + 70.0f;
                        }
                        i_this->field_0x2E7E[0] = unk;
                    }

                    boss->field_0x2E74[1] = 10;
                    boss->field_0x2E74[0] = 10;
                    if (i_this->field_0x2E7E[2] == 0 && hand[0]->field_0x10D6 == 6 && hand[1]->field_0x10D6 == 6) {
                        i_this->field_0x2E7C = 12;
                        hand[0]->field_0x10FC[1] = 100;
                        hand[1]->field_0x10FC[1] = 100;

                        fopAcM_seStart(boss, JA_SE_CM_BST_HEAD_EYE_OPEN, 0);
                        mDoAud_bgmStart(JA_BGM_UNK_122);

                        i_this->field_0x2E7E[1] = cM_rndF(50.0f) + 150.0f;
                    }
                }
                break;
            case 12:
                if (i_this->field_0x2E7E[1] == 0 && boss->field_0x10D6 == 1) {
                    boss->field_0x10D6 = 14;
                    boss->mDamage = 0;
                    boss->field_0x10D0 = REG0_F(7) + (-500.0f);
                }
                hand[0]->field_0x10D6 = 6;
                hand[0]->field_0x10FC[1] = 3;
                hand[1]->field_0x10FC[1] = 3;
                if (boss->field_0x10D6 == 7 && boss->mDamage >= 7) {
                    i_this->field_0x2E7C = 11;
                    i_this->field_0x2E7E[2] = 50;
                }
                break;
            case 100:
                break;
        }
    }
}

/* 00006DC0-00006FA4       .text beam_eff_set__FP4cXyzsUc */
static void beam_eff_set(cXyz* pos, short y, unsigned char set_angle) {
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
    /* Nonmatching */
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
    /* Nonmatching */
    cXyz* pos1;
    cXyz* pos2;
    J3DModel* model;
    s8 beam_set;

    dBgS_GndChk chk;

    for (s32 i = 0; i < 10; i++) {
        if (i_this->field_0x04E4[i] == 0) {
            continue;
        }

        pos1 = &i_this->field_0x03B8[i];
        pos2 = &i_this->field_0x0430[i];
        PSVECAdd(pos1, pos2, pos1);

        model = i_this->field_0x0390[i];
        mDoMtx_stack_c::transS(i_this->field_0x03B8[i]);
        mDoMtx_stack_c::YrotM(i_this->field_0x04A8[i].y);
        mDoMtx_stack_c::XrotM(i_this->field_0x04A8[i].x);
        mDoMtx_stack_c::scaleM(1.0f, 1.0f, i_this->field_0x10A8[i]);
        mDoMtx_stack_c::copy(model->getBaseTRMtx());

        cLib_addCalc2(&i_this->field_0x10A8[i], REG0_F(4) + 5.0f, 1.0f, REG0_F(5) + 0.5f);

        beam_set = FALSE;

        chk.m_pos.z = i_this->field_0x03B8[i].z;
        chk.m_pos.y = i_this->field_0x03B8[i].y + 500.0f;
        chk.m_pos.x = i_this->field_0x03B8[i].x;

        f32 ground_cross = dComIfG_Bgsp()->GroundCross(&chk);
        if (ground_cross >= i_this->field_0x03B8[i].y) {
            i_this->field_0x03B8[i].y = ground_cross;
            beam_eff_set(pos1, 0, 0);
            beam_set = TRUE;
        } else {
            if (beam_wall_check(pos1, pos2)) {
                beam_eff_set(pos1, i_this->field_0x04A8[i].y, 1);
                beam_set = TRUE;
            }
        }

        if (i_this->field_0x03B8[i].y > 2000.0f) {
            i_this->field_0x04E4[i] = 0;
        }

        if (beam_set) {
            i_this->field_0x04E4[i] = 0;
            dComIfGp_getVibration().StartShock(
                REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f)
            );
            mDoAud_seStart(JA_SE_CM_BST_BEAM_BOMB, pos1, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        }

        if (i_this->field_0x04E4[i] == 1) {
            i_this->mCcD_beams[i].StartCAt(*pos1);
            i_this->field_0x04E4[i]++;
        } else {
            i_this->mCcD_beams[i].MoveCAt(*pos1);
        }
        dComIfG_Ccsp()->Set(&i_this->mCcD_beams[i]);
    }
}

/* 00007CF0-0000815C       .text end_brkbtk_set__FP9bst_class */
static void end_brkbtk_set(bst_class* i_this) {
    /* Nonmatching */
    J3DAnmTevRegKey* tev_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_LH_END);
    hand[0]->mpTevRegAnimator->init(
        hand[0]->field_0x02B8->getModel()->getModelData(),
        tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );
    J3DAnmTextureSRTKey* srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_LH_END);
    hand[0]->mpTexMtxAnimator->init(
        hand[0]->field_0x02B8->getModel()->getModelData(),
        srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );

    tev_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_RH_END);
    hand[1]->mpTevRegAnimator->init(
        hand[1]->field_0x02B8->getModel()->getModelData(),
        tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );
    srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_RH_END);
    hand[1]->mpTexMtxAnimator->init(
        hand[1]->field_0x02B8->getModel()->getModelData(),
        srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );

    tev_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_BST_END);
    boss->mpTevRegAnimator->init(
        boss->field_0x02B8->getModel()->getModelData(),
        tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );
    srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_BST_END);
    boss->mpTexMtxAnimator->init(
        boss->field_0x02B8->getModel()->getModelData(),
        srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );

    tev_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_UDEL_END);
    hand[0]->mpBrkAnm->init(
        hand[0]->field_0x02C8->getModelData(),
        tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );
    srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_UDEL_END);
    hand[0]->mpBtkAnm->init(
        hand[0]->field_0x02C8->getModelData(),
        srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );

    tev_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_UDER_END);
    hand[1]->mpBrkAnm->init(
        hand[1]->field_0x02C8->getModelData(),
        tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );
    srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_UDER_END);
    hand[1]->mpBtkAnm->init(
        hand[1]->field_0x02C8->getModelData(),
        srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );

    tev_key = (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_MUNE_END);
    boss->mpBrkAnm->init(
        boss->field_0x02C8->getModelData(),
        tev_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );
    srt_key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_MUNE_END);
    boss->mpBtkAnm->init(
        boss->field_0x02C8->getModelData(),
        srt_key, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE
    );
}

/* 0000815C-00009FCC       .text demo_camera__FP9bst_class */
void demo_camera(bst_class* i_this) {
    /* Nonmatching */
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    s8 bVar2 = true;

    switch (i_this->field_0x2E9A) {
        case 1:
            if (!i_this->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(i_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                i_this->eventInfo.onCondition(dEvtCnd_UNK2_e);
                bVar2 = false;
                break;
            }

            i_this->field_0x2E9A++;
            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);

            i_this->msFrameCount = 0;
            i_this->field_0x2EC8 = 55.0f;
            i_this->field_0x2EC4 = 0.0f;
            i_this->field_0x2E98 = 100;
            break;
        case 2:
            if (REG0_S(4) + 33 < i_this->msFrameCount) {
                cLib_addCalc2(&i_this->field_0x2EC4, -650.0f, 0.5f, REG0_F(3) + 50.0f);
            }
            if (REG0_S(4) + 45 < i_this->msFrameCount) {
                cLib_addCalc2(&i_this->field_0x2EC8, 30.0f, 0.5f, REG0_F(3) + 10.0f);
            }
            mDoMtx_YrotS(*calc_mtx, i_this->shape_angle.y + REG0_S(1) + 0xAF0);
            break;
        case 56:
            if (i_this->msFrameCount == REG0_S(4) + 50) {
                fopAcM_seStartCurrent(i_this, JA_SE_CM_BST_HAND_STRAIN, 0);
                i_this->field_0x2E98 = 1;
            }

            if ((s32)i_this->field_0x02B8->getFrame() == 26) {
                cXyz boss_pos;

                mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(7), *calc_mtx);
                cXyz offset(
                    REG0_F(2) + 60.0f,
                    REG0_F(3),
                    REG0_F(4)
                );

                fopAcM_seStart(i_this, JA_SE_OBJ_BOMB_EXPLODE, 0);
                MtxPosition(&offset, &boss_pos);

                cXyz item_scale(1.0f, 1.0f, 1.0f);
                csXyz item_angle(i_this->shape_angle.x,
                    i_this->shape_angle.y + REG0_S(7) + (-300),
                    i_this->shape_angle.z);
                i_this->mCreatedItemId = fopAcM_createItemForBoss(
                    &boss_pos,
                    0,
                    fopAcM_GetRoomNo(i_this),
                    &item_angle,
                    &item_scale,
                    1
                );
                fopAcM_seStart(i_this, JA_SE_CM_BST_ITEM_OUT_NOSE, 0);

                mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(0), *calc_mtx);
                cXyz vec(0.0f, 0.0f, 0.0f);
                MtxPosition(&vec, &boss_pos);

                dComIfGp_particle_set(
                    item_smoke_name[1],
                    &boss_pos,
                    &i_this->shape_angle,
                    NULL,
                    0xB9,
                    &i_this->mPa_smokeEcallBack,
                    i_this->current.roomNo
                );
            }

            if ((s32)i_this->field_0x02B8->getFrame() > 26) {
                fopAc_ac_c* actor = fopAcM_SearchByID(i_this->mCreatedItemId);
                if (actor != NULL) {
                    i_this->field_0x2E9A = 57;
                    actor->speedF = REG0_F(6) + 65.0f;
                }
            }
            break;
        case 57: {
            fopAc_ac_c* actor = fopAcM_SearchByID(i_this->mCreatedItemId);
            if (actor != NULL) {
                cLib_addCalc2(&i_this->field_0x2EAC.x, actor->current.pos.x, 0.1f, 100.0f);
                cLib_addCalc2(&i_this->field_0x2EAC.y, actor->current.pos.y, 0.1f, 100.0f);
                cLib_addCalc2(&i_this->field_0x2EAC.z, actor->current.pos.z, 0.1f, 100.0f);
                i_this->field_0x2EC8 = REG0_F(4) + 55.0f;
            }
            if (i_this->msFrameCount == 170) {
                camera->mCamera.SetTrimSize(0);
                camera->mCamera.Start();
                dMeter_mtrShow();
                dComIfGp_event_reset();

                i_this->field_0x2E9A = 0;
                i_this->field_0x2E7C = 100;
                i_this->field_0x2E98 = 1;
            }
            break;
        }
    }

    if ((i_this->field_0x2E9A != 0) && bVar2) {
        f32 x = i_this->field_0x2ECC * cM_ssin(i_this->msFrameCount * 0x3300);
        f32 y = i_this->field_0x2ECC * cM_scos(i_this->msFrameCount * 0x3000);
        f32 z = i_this->field_0x2ECC * cM_scos(i_this->msFrameCount * 0x3500);

        cXyz camera_center;
        camera_center.x = i_this->field_0x2EA0.x + x;
        camera_center.y = i_this->field_0x2EA0.y + y;
        camera_center.z = i_this->field_0x2EA0.z + z;
        cXyz camera_eye;
        camera_eye.x = i_this->field_0x2EAC.x - x;
        camera_eye.y = i_this->field_0x2EAC.y - y;
        camera_eye.z = i_this->field_0x2EAC.z - z;

        s16 bank = 7.5f * i_this->field_0x2ECC * cM_scos(i_this->field_0x10D4 * 0x1C00);
        camera->mCamera.Set(
            camera_center,
            camera_eye,
            bank,
            i_this->field_0x2EC8
        );
        cLib_addCalc0(&i_this->field_0x2ECC, 1.0f, 1.0f);

        JUTReport(0x19a, 0x1ae, "K SUB COUNT %d", i_this->msFrameCount);
        i_this->msFrameCount++;
    }
}

/* 00009FCC-0000A1A4       .text bst_kankyo__FP9bst_class */
void bst_kankyo(bst_class* i_this) {
    /* Nonmatching */
    switch (i_this->mRoomState) {
        case 0:
            dKy_custom_colset(3, 0, 0.0f);
            break;
        case 1:
            dKy_custom_colset(3, 0, i_this->field_0x2ED0);
            cLib_addCalc2(&i_this->field_0x2ED0, 1.0f, 1.0f, 0.1f);
            break;
        case 2:
            dKy_custom_colset(0, 4, i_this->field_0x2ED0);
            cLib_addCalc2(&i_this->field_0x2ED0, 1.0f, 1.0f, 0.25f);
            break;
        case 3:
            dKy_custom_colset(3, 4, i_this->field_0x2ED0);
            cLib_addCalc0(&i_this->field_0x2ED0, 1.0f, 0.019999999552965164f);
            break;
        case 4:
            dKy_custom_colset(5, 3, i_this->field_0x2ED0);
            cLib_addCalc0(&i_this->field_0x2ED0, 1.0f, 0.05000000074505806f);
            break;
        case 5:
            dKy_custom_colset(1, 3, i_this->field_0x2ED0);
            cLib_addCalc0(&i_this->field_0x2ED0, 1.0f, 0.10000000149011612f);
            break;
        case 6:
            dKy_custom_colset(1, 2, i_this->field_0x2ED0);
            cLib_addCalc2(&i_this->field_0x2ED0, 1.0f, 1.0f, 0.5f);
            if (i_this->field_0x2ED0 >= 1.0f) {
                i_this->mRoomState = 7;
            }
            break;
        case 7:
            dKy_custom_colset(1, 2, i_this->field_0x2ED0);
            cLib_addCalc0(&i_this->field_0x2ED0, 1.0f, 0.5f);
            break;
        case 8:
            dKy_custom_colset(1, 0, i_this->field_0x2ED0);
            cLib_addCalc2(&i_this->field_0x2ED0, 1.0f, 1.0f, 0.1f);
            if (i_this->field_0x2ED0 >= 1.0f) {
                i_this->mRoomState = 1;
            }
            break;
    }
}

/* 0000A1A4-0000A9C8       .text daBst_Execute__FP9bst_class */
static BOOL daBst_Execute(bst_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz vec;

    i_this->field_0x10D4++;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->field_0x10FC); i++) {
        if (i_this->field_0x10FC[i] != 0) {
            i_this->field_0x10FC[i]--;
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
    if (i_this->field_0x112A != 0) {
        i_this->field_0x112A--;
    }
    if (i_this->field_0x112C != 0) {
        i_this->field_0x112C--;
    }
    if (i_this->mStateTimer != 0) {
        i_this->mStateTimer--;
    }

    if (l_HIO.field_0x5 == 0) {
        i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        if (i_this->field_0x02B4 == 0) {
            if (i_this->field_0x2FE4 != 0) {
                dCam_getBody()->SetTypeForce("Test01", NULL);
            }
            main_cont(i_this);
            if (i_this->field_0x10D6 != 7) {
                fopAcM_OffStatus(i_this, 0);
                i_this->attention_info.flags = 0;
            }

            if (i_this->field_0x10D6 != 0xE) {
                // while loop around 0x2ED8
                if (i_this->mRoomState == 7) {
                    i_this->mRoomState = 8;
                }
            }

            if (player->current.pos.y > -150.0f) {
                i_this->field_0x2FD8->setPlayMode(J3DFrameCtrl::EMode_NONE);
            } else {
                i_this->field_0x2FD8->setPlaySpeed(1.0f);
                i_this->field_0x2FD8->setPlayMode(J3DFrameCtrl::EMode_LOOP);
            }

            i_this->field_0x2FE0->play();
            i_this->field_0x2FD8->play();
            i_this->field_0x2FD4->play();
            mDoMtx_stack_c::transS(0.0f, 0.0f, 0.0f);
            i_this->field_0x2FD0->setBaseTRMtx(mDoMtx_stack_c::now);
            i_this->field_0x2FDC->setBaseTRMtx(mDoMtx_stack_c::now);
        }

        move(i_this);
        if (i_this->field_0x10D6 != 0 && i_this->field_0x10D6 != 0x16) {
            i_this->mBgS_Acch.CrrPos(*dComIfG_Bgsp());
            i_this->mBgS_Acch.SetGroundUpY(0.0f);
        }
        i_this->field_0x02B8->play(&i_this->eyePos, 0, 0);
        if (i_this->field_0x02C4 != 0) {
            i_this->mpTevRegAnimator->play();
            i_this->mpTexMtxAnimator->play();
        }
        if (i_this->field_0x02D4 != 0) {
            i_this->mpBrkAnm->play();
            i_this->mpBtkAnm->play();
        }
    }

    f32 unk1 = i_this->field_0x10EC.z * cM_ssin(
        i_this->field_0x10D4 * (REG0_S(6) + 700)
    );
    f32 unk2 = i_this->field_0x10EC.z * cM_ssin(
        i_this->field_0x10D4 * (REG0_S(6) + 750)
    );
    f32 unk3 = i_this->field_0x10EC.z * cM_scos(
        i_this->field_0x10D4 * (REG0_S(6) + 720)
    );
    cLib_addCalc0(&i_this->field_0x10EC.z, 1.0f, 1.0f);
    i_this->field_0x02B8->getModel()->setBaseScale(i_this->scale);

    mDoMtx_stack_c::transS(i_this->current.pos.x + unk1,
                           i_this->current.pos.y + unk2,
                           i_this->current.pos.z + unk3);

    f32 unk4 = i_this->mHeadHurtAngle * (REG0_F(14) + 500.0f) *
        cM_ssin(i_this->field_0x10D4 * 0x2100);
    f32 unk5 = i_this->mHeadHurtAngle * (REG0_F(14) + 500.0f) *
        cM_scos(i_this->field_0x10D4 * 0x2300);

    f32 unk6 = i_this->field_0x112A * (REG0_F(14) + 150.0f) *
        cM_ssin(boss->field_0x10D4 * 0x3600);
    f32 unk7 = i_this->field_0x112A * (REG0_F(14) + 150.0f) *
        cM_scos(boss->field_0x10D4 * 0x4300);
    f32 unk8 = i_this->field_0x112C * (REG0_F(14) + 100.0f) *
        cM_scos(boss->field_0x10D4 * 0x3A00);

    cLib_addCalc0(&i_this->field_0x10F8, 1.0f, REG0_F(3) + 30.0f);
    mDoMtx_stack_c::YrotM(i_this->shape_angle.y + (s16)unk4 + (s16)unk6);
    mDoMtx_stack_c::XrotM(i_this->shape_angle.x + (s16)unk5 + (s16)unk7 + (s16)unk8);
    mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);
    mDoMtx_stack_c::transM(
        REG0_F(5) + i_this->field_0x1110,
        REG0_F(6) + i_this->field_0x1114,
        REG0_F(7) + i_this->field_0x1118
    );

    cLib_addCalc0(&i_this->field_0x1110, 1.0f, 5.0f);
    cLib_addCalc0(&i_this->field_0x1114, 1.0f, 10.0f);
    cLib_addCalc0(&i_this->field_0x1118, 1.0f, 5.0f);

    i_this->field_0x02B8->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
    i_this->field_0x0388->setBaseTRMtx(mDoMtx_stack_c::now);

    i_this->field_0x02B8->calc();

    MtxTrans(i_this->home.pos.x, i_this->home.pos.y, i_this->home.pos.z, FALSE);
    mDoMtx_YrotM(*calc_mtx, i_this->home.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->home.angle.x);
    mDoMtx_ZrotM(*calc_mtx, i_this->home.angle.z);
    i_this->field_0x02C8->setBaseTRMtx(*calc_mtx);

    col_set(i_this);
    if (i_this->field_0x02B4 == 0) {
        beam_move(i_this);
        demo_camera(i_this);
        bst_kankyo(i_this);
        message_cont(i_this);

        for (s32 j = 0; j < 2; j++) {
            fpc_ProcID proc_id = i_this->field_0x2E90[j];
            fopAc_ac_c* actor = (fopAc_ac_c*) fopAcM_SearchByID(proc_id);
            if (actor != NULL) {
                mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(j + 4), *calc_mtx);
                MtxPosition(&vec, &actor->current.pos);
                actor->max_health = 2;
                actor->health = i_this->mEyeHealth[j];

                if (i_this->mEyeHealth[j] > 0 && i_this->field_0x10D6 != 7) {
                    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                    actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;

                    fopAcM_seStart(i_this, JA_SE_CM_BST_HEAD_WORKING, 0);
                    continue;
                }

                fopAcM_OffStatus(i_this, 0);
                actor->attention_info.flags = 0;
            }
        }
    }
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
        mDoHIO_deleteChild(l_HIO.field_0x4);
    }

    if (i_this->field_0x02B4 == 0) {
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->field_0x2E90); i++) {
            fopAc_ac_c* actor = (fopAc_ac_c*) fopAcM_SearchByID(i_this->field_0x2E90[i]);
            if (actor != NULL) {
                fopAcM_delete(actor);
            }
        }
    }
    i_this->mPa_smokeEcallBack.remove();

    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->field_0x03B8); i++) {
        mDoAud_seDeleteObject(&i_this->field_0x03B8[i]);
    }

    return TRUE;
}

/* 0000AADC-0000B2D0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    /* Nonmatching */
    bst_class* i_this = (bst_class*) a_this;

    i_this->field_0x02B8 = new mDoExt_McaMorf(
        (J3DModelData*) dComIfG_getObjectRes("Bst", set_bdl_d[i_this->field_0x02B4]),
        NULL,
        NULL,
        (J3DAnmTransformKey*) dComIfG_getObjectRes("Bst", set_bck_d[i_this->field_0x02B4]),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    if (i_this->field_0x02B8 == NULL || i_this->field_0x02B8->getModel() == NULL) {
        return FALSE;
    }

    if (i_this->field_0x02B4 == 0) {
        for (u16 i = 0; i < i_this->field_0x02B8->getModel()->getModelData()->getJointNum(); i++) {
            if (i >= 9 && i <= 12) {
                i_this->field_0x02B8->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBackHead);
            }
        }
        i_this->field_0x02B8->getModel()->setUserArea((u32)i_this);
    }

    i_this->field_0x0388 = mDoExt_J3DModel__create(
        i_this->field_0x02B8->getModel()->getModelData(), 0, 0x11020203);
    if (i_this->field_0x0388 == NULL) {
        return FALSE;
    }

    i_this->mpTexMtxAnimator = new mDoExt_btkAnm();
    if (i_this->mpTexMtxAnimator == NULL) {
        return FALSE;
    }
    J3DAnmTextureSRTKey* key = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", set_btk_d[i_this->field_0x02B4]);
    s32 res = i_this->mpTexMtxAnimator->init(
        i_this->field_0x02B8->getModel()->getModelData(),
        key,
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

    i_this->mpTevRegAnimator = new mDoExt_brkAnm();
    if (i_this->mpTevRegAnimator == NULL) {
        return FALSE;
    }
    res = i_this->mpTevRegAnimator->init(
        i_this->field_0x02B8->getModel()->getModelData(),
        (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", set_brk_d[i_this->field_0x02B4]),
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

    if (i_this->field_0x02B4 == 0) {
        J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectRes("Bst", BST_BDL_TAMA);
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->field_0x0390); i++) {
            i_this->field_0x0390[i] = mDoExt_J3DModel__create(
                modelData, 0, 0x11020203);
            if (i_this->field_0x0390[i] == NULL) {
                return FALSE;
            }
        }

        modelData = (J3DModelData*) dComIfG_getObjectRes("Bst", BST_BDL_HBSITA1);
        i_this->field_0x2FD0 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->field_0x2FD0 == NULL) {
            return FALSE;
        }

        i_this->field_0x2FD4 = new mDoExt_btkAnm();
        if (i_this->field_0x2FD4 == NULL) {
            return FALSE;
        }

        res = i_this->field_0x2FD4->init(
            modelData,
            (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", BST_BTK_HBSITA1),
            TRUE,
            J3DFrameCtrl::EMode_LOOP,
            1.0f,
            0,
            -1,
            false,
            FALSE
        );
        if (res == 0) {
            return FALSE;
        }

        i_this->field_0x2FD8 = new mDoExt_brkAnm();
        if (i_this->field_0x2FD8 == NULL) {
            return FALSE;
        }
        res = i_this->field_0x2FD8->init(
            modelData,
            (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_HBSITA1),
            TRUE,
            J3DFrameCtrl::EMode_NONE,
            0.0f,
            0,
            -1,
            false,
            FALSE
        );
        if (res == 0) {
            return FALSE;
        }

        modelData = (J3DModelData*) dComIfG_getObjectRes("Bst", BST_BDL_HBYOKO1);
        i_this->field_0x2FDC = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->field_0x2FDC == NULL) {
            return FALSE;
        }

        i_this->field_0x2FE0 = new mDoExt_brkAnm();
        if (i_this->field_0x2FE0 == NULL) {
            return FALSE;
        }
        res = i_this->field_0x2FE0->init(
            modelData,
            (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", BST_BRK_HBYOKO1),
            TRUE,
            J3DFrameCtrl::EMode_LOOP,
            1.0f,
            0,
            -1,
            false,
            FALSE
        );
        if (res == 0) {
            return FALSE;
        }
    }

    J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectRes("Bst", set_za_bdl[i_this->field_0x02B4]);
    i_this->field_0x02C8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->field_0x02C8 == NULL) {
        return FALSE;
    }

    i_this->mpBtkAnm = new mDoExt_btkAnm();
    if (i_this->mpBtkAnm == NULL) {
        return FALSE;
    }
    res = i_this->mpBtkAnm->init(
        modelData,
        (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Bst", set_za_btk_d[i_this->field_0x02B4]),
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
        modelData,
        (J3DAnmTevRegKey*) dComIfG_getObjectRes("Bst", set_za_brk_d[i_this->field_0x02B4]),
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

    return TRUE;
}

/* 0000B318-0000B860       .text daBst_Create__FP10fopAc_ac_c */
static cPhs_State daBst_Create(fopAc_ac_c* a_this) {
    /* Nonmatching */
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
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT & ~AT_TYPE_GRAPPLING_HOOK,
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
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT & ~AT_TYPE_GRAPPLING_HOOK,
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

    fopAcM_SetupActor(a_this, bst_class);

    cPhs_State res;
    bst_class* i_this = (bst_class*) a_this;

    res = dComIfG_resLoad(&i_this->mPhs, "Bst");
    if (res == cPhs_COMPLEATE_e) {
        i_this->mPa_smokeEcallBack.setFollowOff();
        i_this->field_0x02B4 = fopAcM_GetParam(i_this) & 0xFF;

        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }

        i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
        if (hio_set == 0) {
            i_this->mHioSet = 1;
            hio_set = 1;

            // Possible bug: why is "Armos Knight" here?
            l_HIO.field_0x4 = mDoHIO_createChild("デグアモス", &l_HIO);
        }

        i_this->mBgS_Acch.Set(&i_this->current.pos, &i_this->old.pos, i_this,
            1, &i_this->mBgS_AcchCir, &i_this->speed);
        i_this->mBgS_Acch.OffSameActorChk();

        i_this->mBgS_AcchCir.SetWall(200.0f, 10.0f);

        if (i_this->field_0x02B4 == 0) {
            boss = i_this;
            msg = fpcM_ERROR_PROCESS_ID_e;
        }
        if (i_this->field_0x02B4 == 1) {
            hand[0] = i_this;
        }
        if (i_this->field_0x02B4 == 2) {
            hand[1] = i_this;
        }

        u8 weight;
        if (i_this->field_0x02B4 == 0) {
            weight = 255;
        } else {
            weight = 230;
        }
        i_this->mCcD_Stts.Init(weight, 0xFF, i_this);
        i_this->mHandHurtCollisionCcD_Cyl.Set(core_cyl_src);
        i_this->mHandHurtCollisionCcD_Cyl.SetStts(&i_this->mCcD_Stts);

        if (i_this->field_0x02B4 == 0) {
            i_this->mHeadHurtCollisionCcD_Cyl.Set(cc_cyl_src);
            i_this->mHeadHurtCollisionCcD_Cyl.SetStts(&i_this->mCcD_Stts);

            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mBstEyeCcD_Spheres); i++) {
                i_this->mBstEyeCcD_Spheres[i].Set(eye_sph_src);
                i_this->mBstEyeCcD_Spheres[i].SetStts(&i_this->mCcD_Stts);
            }

            i_this->health = 3;
            i_this->max_health = 3;
            i_this->mEyeHealth[1] = 2;
            i_this->mEyeHealth[0] = 2;

            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->field_0x2E90); i++) {
                i_this->field_0x2E90[i] = fopAcM_create(
                    PROC_ATT,
                    100,
                    &i_this->current.pos,
                    i_this->current.roomNo);
            }

            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mCcD_beams); i++) {
                i_this->mCcD_beams[i].Set(beam_sph_src);
                i_this->mCcD_beams[i].SetStts(&i_this->mCcD_Stts);
            }
        } else {
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mCcD_fingers); i++) {
                i_this->mCcD_fingers[i].Set(finger_sph_src);
                i_this->mCcD_fingers[i].SetStts(&i_this->mCcD_Stts);
            }
            i_this->health = 4;
            i_this->max_health = 4;
        }
    }
    f32 fVar = cM_rndFX(32768.0f);
    i_this->field_0x10D4 = fVar;
    i_this->mEnvLight = i_this->tevStr;
    i_this->field_0x2F20 = i_this->tevStr;

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
