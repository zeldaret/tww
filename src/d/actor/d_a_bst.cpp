/**
 * d_a_bst.cpp
 * Boss - Gohdan
 */

#include "d/actor/d_a_bst.h"
#include "d/actor/d_a_bomb.h"
#include "d/d_camera.h"
#include "d/d_snap.h"
#include "d/res/res_bst.h"
#include "d/d_s_play.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_graphic.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

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

static const u16 set_bdl_d[3] = {BST_BDL_BST, BST_BDL_LHAND, BST_BDL_RHAND};
static const u16 set_za_bdl[3] = {BST_BDL_MUNE, BST_BDL_UDEL, BST_BDL_UDER};
static const u16 set_bck_d[3] = {BST_BCK_BST_SLEEP, BST_BCK_LH_SLEEP, BST_BCK_RH_SLEEP};

static const u16 set_btk_d[3] = {BST_BTK_BST_START, BST_BTK_LH_START, BST_BTK_RH_START};
static const u16 set_brk_d[3] = {BST_BRK_BST_START, BST_BRK_LH_START, BST_BRK_RH_START};

static const u16 set_za_btk_d[3] = {BST_BTK_MUNE_START, BST_BTK_UDEL_START, BST_BTK_UDER_START};
static const u16 set_za_brk_d[3] = {BST_BRK_MUNE_START, BST_BRK_UDEL_START, BST_BRK_UDER_START};

static dCcD_SrcCyl core_cyl_src = {
    /* Nonmatching */
    {},
    {}
};
static dCcD_SrcCyl cc_cyl_src = {
    /* Nonmatching */
    {},
    {}
};
static dCcD_SrcSph eye_sph_src = {
    /* Nonmatching */
    {},
    {}
};
static dCcD_SrcSph beam_sph_src = {
    /* Nonmatching */
    {},
    {}
};
static dCcD_SrcSph finger_sph_src = {
    /* Nonmatching */
    {},
    {}
};

/* 00000110-00000174       .text message_set__FP9bst_classUl */
static BOOL message_set(bst_class* i_this, unsigned long msg_no) {
    /* Nonmatching */
    if (msg == -1) {
        msg = fopMsgM_messageSet(msg_no, i_this);
        msg_end = 0;
        return TRUE;
    }
    return FALSE;
}

/* 00000174-000001FC       .text message_cont__FP9bst_class */
static void message_cont(bst_class* i_this) {
    if (msg == -1) {
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
        msg = -1;
    }
}

/* 000001FC-00000268       .text set_hand_AT__FP9bst_classUc */
static void set_hand_AT(bst_class* i_this, unsigned char param_2) {
    /* Nonmatching */
    s32 j = 0;
    s32 i = 0;

    if (param_2 != 0) {
        for (; i < (s32)ARRAY_SIZE(i_this->mCcD_fingers); i++) {
            dCcD_Sph& sphere = i_this->mCcD_fingers[i];
            sphere.OnAtSetBit();
            sphere.SetAtSpl(dCcG_At_Spl_UNK1);
        }
    } else {
        for (; j < (s32)ARRAY_SIZE(i_this->mCcD_fingers); j++) {
            dCcD_Sph& sphere = i_this->mCcD_fingers[j];
            sphere.OffAtSetBit();
            sphere.SetAtSpl(dCcG_At_Spl_UNK1);
        }
    }
}

/* 00000268-000002C0       .text set_hand_CO__FP9bst_classUc */
static void set_hand_CO(bst_class* i_this, unsigned char param_2) {
    /* Nonmatching */
    s32 j = 0;
    s32 i = 0;

    if (param_2 != 0) {
        for (; i < (s32)ARRAY_SIZE(i_this->mCcD_fingers); i++) {
            i_this->mCcD_fingers[i].OnCoSetBit();
        }
    } else {
        for (; j < (s32)ARRAY_SIZE(i_this->mCcD_fingers); j++) {
            i_this->mCcD_fingers[j].OffCoSetBit();
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
    /* Nonmatching */
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jnt_no = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();

        bst_class* i_this = (bst_class*)model->getUserArea();

        if (i_this != NULL) {
            mDoMtx_copy(model->getAnmMtx(jnt_no), *calc_mtx);
            
            if (jnt_no == 9) {
                mDoMtx_YrotM(*calc_mtx, -i_this->field_0x2E7A);
            } else if (jnt_no == 12) {
                mDoMtx_YrotM(*calc_mtx, i_this->field_0x2E7A);
            } else if (jnt_no == 10) {
                mDoMtx_YrotM(*calc_mtx, -i_this->field_0x2E78);
            } else if (jnt_no == 11) {
                mDoMtx_YrotM(*calc_mtx, i_this->field_0x2E78);
            }

            model->setAnmMtx(jnt_no, *calc_mtx);
            mDoMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000550-000005B4       .text beam_draw__FP9bst_class */
static void beam_draw(bst_class* i_this) {
    /* Nonmatching */
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

    if (i_this->field_0x02B4 == 0 || boss->field_0x2E9A < 1 || boss->field_0x2E9A > 9) {
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
            switch (i_this->field_0x2E98) {
                case 0:
                    mDoGph_gInf_c::setBlureRate(i_this->field_0x2E98);
                    mDoGph_gInf_c::onBlure();
                    break;
                case 1:
                default:
                    i_this->field_0x2E98 = 0;
                    mDoGph_gInf_c::offBlure();
                    break;
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
        dSnap_RegistFig(DSNAP_TYPE_UNKC9, i_this, 1.0f, 1.0f, 1.0f);
    }

    return TRUE;
}

/* 00000950-00000B1C       .text pos_move__FP9bst_classUc */
static void pos_move(bst_class* i_this, unsigned char param_2) {
    /* Nonmatching */
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
    vec.z = fopAcM_GetSpeedF(i_this);

    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    MtxPosition(&vec, &fopAcM_GetSpeed(i_this));
    i_this->current.pos += i_this->speed;
}

/* 00000B1C-00000E58       .text stay__FP9bst_class */
static void stay(bst_class* i_this) {
    /* Nonmatching */
}

/* 00000E58-000014E8       .text fly__FP9bst_class */
static void fly(bst_class*) {
    /* Nonmatching */
}

/* 000014E8-00001C14       .text down_attack__FP9bst_class */
static void down_attack(bst_class*) {
    /* Nonmatching */
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

/* 0000318C-00003470       .text sleep__FP9bst_class */
static void sleep(bst_class*) {
    /* Nonmatching */
}

/* 00003470-000035BC       .text beam_set__FP9bst_class */
static void beam_set(bst_class* i_this) {
    /* Nonmatching */
    for (s32 i = 10; i >= 0; i--) {
        if (i_this->field_0x04E4[i]) {
            continue;
        }

        mDoMtx_copy(i_this->field_0x02B8->getModel()->getAnmMtx(REG0_S(5) + 3), *calc_mtx);
        cXyz vec(0.0f, 0.0f, 0.0f);
        MtxPosition(&vec, &i_this->field_0x03B8[i]);

        i_this->field_0x04A8[i] = i_this->shape_angle;
        mDoMtx_YrotS(*calc_mtx, i_this->field_0x04A8[i].y);
        mDoMtx_XrotM(*calc_mtx, i_this->field_0x04A8[i].x);

        vec.set(0.0f, 0.0f, REG0_F(12) + 160.0f);
        // MtxPosition call here.

        i_this->field_0x10A8[i] = 1.0f;
    }
}

/* 000035BC-00003B94       .text beam_attack__FP9bst_class */
static void beam_attack(bst_class*) {
    /* Nonmatching */
}

/* 00003B94-00003DD8       .text damage__FP9bst_class */
static void damage(bst_class*) {
    /* Nonmatching */
}

/* 00003DD8-00003EC4       .text bom_eat_check__FP9bst_class */
static BOOL bom_eat_check(bst_class* i_this) {
    /* Nonmatching */
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
    i_this->field_0x2E74 = 10;
    i_this->field_0x2E76 = 10;
    cLib_addCalcAngleS2(&i_this->shape_angle.x, 0, 8, 512);
    cLib_addCalcAngleS2(&i_this->shape_angle.z, 0, 8, 512);
    cLib_addCalc0(&i_this->field_0x10EC.z, 1.0f, 5.0f);

    switch (i_this->mDamage) {
        case 0:
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
static void head_hukki(bst_class*) {
    /* Nonmatching */
}

/* 00004BCC-000051E0       .text col_set__FP9bst_class */
static void col_set(bst_class* i_this) {
    /* Nonmatching */
    cXyz vec;
    cXyz pos_vec;

    if (i_this->field_0x02B4 == 0) {
        i_this->field_0x02B8->getModel()->setAnmMtx(8, *calc_mtx);

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

        }
    } else {
        f32 radius = 0.0f;
        vec.setall(0.0f);

        if (i_this->field_0x10D6 == 13) {
            radius = REG0_F(16) + 50.0f;
        }

        if (i_this->field_0x02B4 == 2) {
            vec.set(-(REG0_F(15) + 100.0f), REG0_F(16), -(REG0_F(17) + 40.0f));
            MtxPosition(&vec, &pos_vec);

            vec.set(-(REG0_F(15) + 100.0f), REG0_F(16), REG0_F(18) + 10.0f);
            MtxPosition(&vec, &i_this->eyePos);
        } else {
            vec.set(REG0_F(15) + 100.0f, REG0_F(16), REG0_F(17) + 40.0f);
            MtxPosition(&vec, &pos_vec);

            vec.set(REG0_F(15) + 100.0f, REG0_F(16), REG0_F(18) + 10.0f);
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
    /* Nonmatching */
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
}

/* 0000591C-00005D9C       .text hana_demo__FP9bst_class */
static void hana_demo(bst_class*) {
    /* Nonmatching */
}

/* 00005D9C-00006088       .text end_demo__FP9bst_class */
static void end_demo(bst_class*) {
    /* Nonmatching */
}

/* 00006088-00006418       .text move__FP9bst_class */
static void move(bst_class*) {
    /* Nonmatching */
}

/* 00006418-00006DC0       .text main_cont__FP9bst_class */
static void main_cont(bst_class*) {
    /* Nonmatching */
}

/* 00006DC0-00006FA4       .text beam_eff_set__FP4cXyzsUc */
static void beam_eff_set(cXyz*, short, unsigned char) {
    /* Nonmatching */
}

/* 00006FA4-00007308       .text beam_wall_check__FP4cXyzP4cXyz */
static void beam_wall_check(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00007740-00007B58       .text beam_move__FP9bst_class */
static void beam_move(bst_class*) {
    /* Nonmatching */
}

/* 00007CF0-0000815C       .text end_brkbtk_set__FP9bst_class */
static void end_brkbtk_set(bst_class*) {
    /* Nonmatching */
}

/* 0000815C-00009FCC       .text demo_camera__FP9bst_class */
void demo_camera(bst_class*) {
    /* Nonmatching */
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

    i_this->mUpdateLastFacingDirIfMultipleOf32++;
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
                i_this->actor_status = i_this->actor_status;
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
        i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 700)
    );
    f32 unk2 = i_this->field_0x10EC.z * cM_ssin(
        i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 750)
    );
    f32 unk3 = i_this->field_0x10EC.z * cM_scos(
        i_this->mUpdateLastFacingDirIfMultipleOf32 * (REG0_S(6) + 720)
    );
    cLib_addCalc0(&i_this->field_0x10EC.z, 1.0f, 1.0f);
    i_this->field_0x02B8->getModel()->setBaseScale(i_this->scale);

    mDoMtx_stack_c::transS(i_this->current.pos.x + unk1,
                           i_this->current.pos.y + unk2,
                           i_this->current.pos.z + unk3);

    f32 unk4 = i_this->mHeadHurtAngle * (REG0_F(14) + 500.0f) *
        cM_ssin(i_this->mUpdateLastFacingDirIfMultipleOf32 * 0x2100);
    f32 unk5 = i_this->mHeadHurtAngle * (REG0_F(14) + 500.0f) *
        cM_scos(i_this->mUpdateLastFacingDirIfMultipleOf32 * 0x2300);

    f32 unk6 = i_this->field_0x112A * (REG0_F(14) + 150.0f) *
        cM_ssin(boss->mUpdateLastFacingDirIfMultipleOf32 * 0x3600);
    f32 unk7 = i_this->field_0x112A * (REG0_F(14) + 150.0f) *
        cM_scos(boss->mUpdateLastFacingDirIfMultipleOf32 * 0x4300);
    f32 unk8 = i_this->field_0x112C * (REG0_F(14) + 100.0f) *
        cM_scos(boss->mUpdateLastFacingDirIfMultipleOf32 * 0x3A00);

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
                    actor->attention_info.distances[2] = 4;

                    fopAcM_seStart(i_this, JA_SE_CM_BST_HEAD_WORKING, 0);
                    continue;
                }

                actor->actor_status = actor->actor_status;
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
    fopAcM_SetupActor(a_this, bst_class);

    cPhs_State res;
    bst_class* i_this = (bst_class*) a_this;

    res = dComIfG_resLoad(&i_this->mPhs, "Bst");
    if (res == cPhs_COMPLEATE_e) {
        i_this->mPa_smokeEcallBack.setFollowOff();
        i_this->field_0x02B4 = (u8) fopAcM_GetParam(i_this);
        
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }

        i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->attention_info.distances[2] = 4;
        if (hio_set == 0) {
            i_this->mHioSet = 1;
            hio_set = 1;
            
            // "Deguamos"
            l_HIO.field_0x4 = mDoHIO_createChild("デグアモス", &l_HIO);
        }

        i_this->mBgS_Acch.Set(&i_this->current.pos, &i_this->old.pos, i_this,
            1, &i_this->mBgS_AcchCir, &i_this->speed);
        i_this->mBgS_Acch.OffSameActorChk();

        i_this->mBgS_AcchCir.SetWall(200.0f, 10.0f);

        if (i_this->field_0x02B4 == 0) {
            boss = i_this;
            msg = -1;
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
    i_this->mUpdateLastFacingDirIfMultipleOf32 = fVar;
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
