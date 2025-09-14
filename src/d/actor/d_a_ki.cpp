/**
 * d_a_ki.cpp
 * Enemy - Keese
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_ki.h"
#include "d/actor/d_a_player.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_path.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "d/res/res_ki.h"
#include "m_Do/m_Do_hostIO.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_uty.h"
#include "d/d_bg_s_lin_chk.h"
#include "JSystem/JUtility/JUTReport.h"

class kiHIO_c : public JORReflexible {
public:
    kiHIO_c() {
        m05 = 0;
        m06 = 0;
        m07 = 0;
        m10 = 1.0f;
        m08 = 1.0f;
        m14 = 1.5f;
        m18 = 2.0f;
        m1C = 55.0f;
        m20 = 175.0f;
        m24 = 60.0f;
        m28 = 30.0f;
        m2C = 3.0f;
        m30 = 7.0f;
        m44 = 30.0f;
        m34 = 65.0f;
        m38 = 100.0f;
        m40 = 7.0f;
        m3C = 15.0f;
        m4C = 30;
        m48 = 0.2f;
        m54 = 3;
        m52 = 7;
        m50 = 0x12C;
        m4E = 0x320;
        m0C = 500.0f;
        m58 = 80.0f;
    }
    virtual ~kiHIO_c() {}

    void genMessage(JORMContext* ctx) {}

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ s16 m4C;
    /* 0x4E */ s16 m4E;
    /* 0x50 */ s16 m50;
    /* 0x52 */ s16 m52;
    /* 0x54 */ s16 m54;
    /* 0x58 */ f32 m58;
}; // size = 0x5C

static bool hio_set;
static kiHIO_c l_kiHIO;
static s32 ki_all_count;
static s32 ki_fight_count;

static u16 ki_tex_anm_idx[] = {KI_BTP_AKE1, KI_BTP_TOJI1, KI_BTP_METOJI1, KI_BTP_GURU1};
static u16 ki_tex_max_frame[] = { 2, 2, 3, 2 };
static u8 ki_tex_loop[] = { 0, 0, 0, 0 };

/* 000000EC-000001B4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        ki_class* pvVar3 = (ki_class*)model->getUserArea();

        if (pvVar3 != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cMtx_YrotM(*calc_mtx, pvVar3->m328);
            cMtx_ZrotM(*calc_mtx, pvVar3->m326);
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 000001B4-0000023C       .text ki_a_d_sub__FPvPv */
void* ki_a_d_sub(void* ac1, void*) {
    if (fopAcM_IsActor(ac1) && fopAcM_GetName(ac1) == PROC_KI) {
        ki_class* ki = (ki_class*)ac1;
        ki_all_count++;
        if (ki->mAction == ki_class::ACT_ATTACK_MOVE_INDEX_e && ki->mBehaviorType < 10) {
            ki_fight_count++;
        }
    }
    return NULL;
}

/* 0000023C-0000027C       .text ki_check__FP8ki_class */
void ki_check(ki_class* i_this) {
    ki_fight_count = 0;
    ki_all_count = 0;
    fpcM_Search(ki_a_d_sub, &i_this->actor);
}

/* 0000027C-000003A4       .text anm_init__FP8ki_classifUcfi */
void anm_init(ki_class* i_this, int anmResIdx, float morf, unsigned char loopMode, float playSpeed, int soundResIdx) {
    if (soundResIdx >= 0) {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Ki", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, dComIfG_getObjectRes("Ki", soundResIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Ki", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
    }
}

/* 000003A4-00000478       .text tex_anm_set__FP8ki_classUs */
void tex_anm_set(ki_class* i_this, unsigned short idx) {
    J3DAnmTexPattern* pJVar2;

    i_this->m335 = 1;
    pJVar2 = (J3DAnmTexPattern*)dComIfG_getObjectRes("Ki", ki_tex_anm_idx[idx]);
    i_this->m336 = ki_tex_max_frame[idx];
    i_this->m337 = ki_tex_loop[idx];
    i_this->m32C = pJVar2;
    i_this->m334 = 0;
    i_this->m32C->setFrame(0.0f);

    u16 materialNum = pJVar2->getUpdateMaterialNum();
    for (u16 i = 0; i < materialNum; i++) {
        i_this->m330[i].setAnmTexPattern(pJVar2);
    }
}

/* 00000478-000004C4       .text ki_eye_tex_anm__FP8ki_class */
void ki_eye_tex_anm(ki_class* i_this) {
    if (i_this->m335 != 0) {
        if (i_this->m334 < i_this->m336) {
            i_this->m334++;
        } else if (i_this->m337 != 0) {
            i_this->m334 = 0;
        } else {
            i_this->m335 = 0;
        }
    }
}

/* 000004C4-00000820       .text ki_player_bg_check__FP8ki_class */
BOOL ki_player_bg_check(ki_class* i_this) {
    fopEn_enemy_c* a_this = (fopEn_enemy_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if (std::fabsf(player->speedF) < 0.1f && player->checkGrabWear()) {
        return TRUE;
    }

    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp08;

    sp08 = player->eyePos;
    sp14 = a_this->eyePos;
    linChk.Set(&sp14, &sp08, a_this);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 00000C58-00000F04       .text daKi_Draw__FP8ki_class */
static BOOL daKi_Draw(ki_class* i_this) {
    fopEn_enemy_c* a_this = (fopEn_enemy_c*)&i_this->actor;

    if (i_this->m2D4 != 0) {
        return TRUE;
    }

    J3DModel* pModel = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(pModel, &a_this->tevStr);

    if (i_this->mEnemyIce.mFreezeTimer > 0x14) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, NULL);
        return TRUE;
    }

    a_this->model = pModel;
    dSnap_RegistFig(0xae, a_this, 1.0f, 1.0f, 1.0f);
    pModel->getModelData()->setTexNoAnimator(i_this->m32C, i_this->m330);
    i_this->m32C->setFrame(i_this->m334);

    f32 fVar1 = 30.0f;
    if (i_this->mDamageType == 0) {
        J3DModelData* pModelData = pModel->getModelData();
        J3DJoint* joint = pModelData->getJointNodePointer(0);
        J3DMaterial* material = pModelData->getMaterialNodePointer(0);
        J3DShape* shape = material->getShape();

        shape->hide();
        i_this->mpMorf->entryDL();
        dComIfGd_setListMaskOff();
        shape->show();
        pModel->getMatPacket(0)->unlock();
        
        material = pModelData->getMaterialNodePointer(1);
        material->getShape()->hide();
        joint->entryIn();
        material->getShape()->show();

        dComIfGd_setList();
    } else {
        J3DModelData* pModelData = pModel->getModelData();
        i_this->m920->entry(pModelData, i_this->m920->getFrame());
        
        dComIfGd_setListMaskOff();
        i_this->mpMorf->entryDL();
        dComIfGd_setList();
        fVar1 = 45.0f;
    }

#if VERSION == VERSION_DEMO
    dComIfGd_setSimpleShadow2(&a_this->current.pos, i_this->mAcch.GetGroundH(), fVar1, i_this->mAcch.m_gnd);
#else
    if (i_this->m540 != 0 && strcmp(dComIfGp_getStartStageName(), "GanonK") != 0) {
        cXyz sp08(a_this->current.pos.x, a_this->current.pos.y, a_this->current.pos.z);
        i_this->m2E0 = dComIfGd_setShadow(i_this->m2E0, 1, pModel, &sp08, 400.0f, fVar1, sp08.y, i_this->mAcch.GetGroundH(), i_this->mAcch.m_gnd, &a_this->tevStr);
    }
#endif
    return TRUE;
}

/* 00000F04-00001118       .text ki_pos_move__FP8ki_classSc */
void ki_pos_move(ki_class* i_this, s8 arg1) {
    if (arg1 == 0) {
        f32 x = i_this->mPosMove.x - i_this->actor.current.pos.x;
        f32 y = i_this->mPosMove.y - i_this->actor.current.pos.y;
        f32 z = i_this->mPosMove.z - i_this->actor.current.pos.z;
        s16 xzAngle = cM_atan2s(x, z);
        s16 iVar6 = -cM_atan2s(y, std::sqrtf(x * x + z * z));

        cLib_addCalcAngleS2(&i_this->actor.current.angle.y, xzAngle, 5, i_this->m304 * i_this->mPosMoveDist);
        cLib_addCalcAngleS2(&i_this->actor.current.angle.x, iVar6, 5, i_this->m304 * i_this->mPosMoveDist);
        cLib_addCalc2(&i_this->mPosMoveDist, 1.0f, 1.0f, 0.04f);
    }

    cLib_addCalc2(&i_this->actor.speedF, i_this->mPosMoveTarget, 1.0f, i_this->mPosMoveMaxSpeed);
    cXyz sp0C;
    sp0C.x = 0.0f;
    sp0C.y = 0.0f;
    sp0C.z = i_this->actor.speedF;
    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);
    MtxPosition(&sp0C, &i_this->actor.speed);
    i_this->actor.current.pos.x += i_this->actor.speed.x;
    i_this->actor.current.pos.y += i_this->actor.speed.y;
    i_this->actor.current.pos.z += i_this->actor.speed.z;
}

/* 00001118-0000171C       .text ki_wait_move__FP8ki_class */
void ki_wait_move(ki_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz sp58;

    switch(i_this->mBehaviorType) {
        case 0:
            anm_init(i_this, KI_BCK_WAIT1, 10.0f, 2, 1.0f, KI_BAS_WAIT1);
            i_this->mBehaviorType = 1;
            tex_anm_set(i_this, 2);

        case 1:
            sp58 = player->current.pos - i_this->actor.current.pos;
            if (std::sqrtf(sp58.x * sp58.x + sp58.z * sp58.z) < i_this->mMaxAttackMoveDist300) {
                sp58 = player->current.pos - player->old.pos;
                if (sp58.abs() > 1.0f) {
                    i_this->mBehaviorType = 2;
                    i_this->mTimers[0] = 10;
                }
            }
            break;

        case 2:
            if (i_this->mTimers[0] == 0) {
                i_this->mBehaviorType = 3;
                tex_anm_set(i_this, 0);
                i_this->mTimers[0] = 0x28;
                fopAcM_monsSeStart(&i_this->actor, JA_SE_CV_KI_WAKEUP, 0);
            }
            break;

        case 3:
            i_this->m338 = 1;
            if (i_this->mTimers[0] == 0) {
                sp58 = player->current.pos - player->old.pos;
                if (sp58.abs() > 1.0f) {
                    i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
                    i_this->mBehaviorType = 0;
                    i_this->actor.current.angle.x = 0x4000;
                } else {
                    i_this->mBehaviorType = 0;
                }
            }

            sp58 = player->current.pos - i_this->actor.current.pos;

            i_this->m322 = cM_atan2s(sp58.x, sp58.z) - i_this->actor.current.angle.y;
            i_this->m324 = -cM_atan2s(sp58.y, std::sqrtf(sp58.x * sp58.x + sp58.z * sp58.z));
            if (i_this->m322 > 10000) {
                i_this->m322 = 10000;
            } else if (i_this->m322 < -10000) {
                i_this->m322 = -10000;
            }

            if (i_this->m324 > 0x2000) {
                i_this->m324 = 0x1FF6;
            } else if (i_this->m324 < -0x38E) {
                i_this->m324 = -0x38E;
            }
            break;

        case 10:
            i_this->mPosMove = i_this->actor.home.pos;
            i_this->mPosMoveTarget = 20.0f;
            i_this->mPosMoveMaxSpeed = 20.0f;
            i_this->m304 = 10000.0f;
            i_this->mPosMoveDist = 1.0f;
            ki_pos_move(i_this, 0);

            sp58 = i_this->mPosMove - i_this->actor.current.pos;
            if (sp58.abs() < 100.0f) {
                i_this->mBehaviorType = 0xb;
                i_this->mTimers[0] = 0x32;
                anm_init(i_this, KI_BCK_WAIT1, 10.0f, 2, 1.0f, KI_BAS_WAIT1);
            }
            break;

        case 0xb:
            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x, 0.5f, std::fabsf(i_this->actor.speed.x) + 1.0f);
            cLib_addCalc2(&i_this->actor.current.pos.y, i_this->actor.home.pos.y, 0.5f, std::fabsf(i_this->actor.speed.y) + 1.0f);
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z, 0.5f, std::fabsf(i_this->actor.speed.z) + 1.0f);
            if (i_this->mTimers[0] == 0) {
                i_this->mBehaviorType = 0;
                i_this->mTimers[0] = cM_rndF(50.0f) + 70.0f;
            }
            break;
    }

    cLib_addCalcAngleS2(&i_this->actor.shape_angle.y, i_this->actor.current.angle.y, 1, 0x1000);
}

/* 0000171C-00001A34       .text ki_fly_move__FP8ki_class */
void ki_fly_move(ki_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->m540 = 1;

    cXyz sp28 = i_this->mPosMove - i_this->actor.current.pos;
    f32 sqrt = std::sqrtf(sp28.x * sp28.x + sp28.z * sp28.z);
    
    switch (i_this->mBehaviorType) {
        case 0:
            anm_init(i_this, KI_BCK_FLY1, 10.0f, 2, l_kiHIO.m08, KI_BAS_FLY1);
            i_this->mBehaviorType = 1;
            tex_anm_set(i_this, 0);
            i_this->mPosMoveTarget = l_kiHIO.m28;
            i_this->mPosMoveMaxSpeed = 2.0f;
            i_this->m304 = 3000.0f;

        case 1:
            if (i_this->mTimers[1] == 0 || sqrt < 50.0f) {
                i_this->mTimers[1] = cM_rndF(50.0f) + 50.0f;
                i_this->mPosMove = i_this->actor.home.pos;
                i_this->mPosMove.x += cM_rndFX(l_kiHIO.m0C);
                i_this->mPosMove.y -= cM_rndF(200.0f);
                i_this->mPosMove.z += cM_rndFX(l_kiHIO.m0C);
                i_this->mPosMoveDist = 0.0f;
            }
        
            if (i_this->mTimers[0] == 0) {
                sp28 = player->current.pos - i_this->actor.current.pos;
                if (std::sqrtf(sp28.x * sp28.x + sp28.z * sp28.z) < i_this->mMaxAttackMoveDist300) {
                    i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
                    i_this->mBehaviorType = 0;
                }
            }
            break;
    }

#if VERSION > VERSION_DEMO
    if ((i_this->mTimers[2] == 0) && i_this->mAcch.ChkWallHit()) {
        i_this->actor.current.angle.y -= -0x8000;
        i_this->mTimers[2] = 20;
    }
#endif

    ki_pos_move(i_this, 0);

    cLib_addCalcAngleS2(&i_this->actor.shape_angle.y, i_this->actor.current.angle.y, 1, 0x2000);
}

/* 00001A34-00001D84       .text ki_fire_set_move__FP8ki_class */
void ki_fire_set_move(ki_class* i_this) {
    fopEn_enemy_c* a_this = (fopEn_enemy_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->m540 = 0;

    switch (i_this->mBehaviorType) {
        case 0:
            a_this->speedF = REG8_F(8) + 35.0f + cM_rndF(10.0f);
            a_this->speed.y = REG8_F(9) + 97.0f + cM_rndF(30.0f);
            anm_init(i_this, KI_BCK_WAIT1, 1.0f, 2, 1.0f, KI_BAS_WAIT1);
            i_this->mBehaviorType = 1;
            i_this->m91C = dComIfGp_particle_set(dPa_name::ID_SCENE_8099, &a_this->current.pos, NULL, NULL, 0xFF, &i_this->m908);

        case 1:
            a_this->shape_angle.x += 0x1400;
            a_this->shape_angle.y += 0x1000;
            if (a_this->speed.y < REG8_F(11) + -70.0f) {
                i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
                i_this->mBehaviorType = 0;
                a_this->shape_angle.x = 0;
                if (i_this->m91C != NULL) {
                    i_this->m908.remove();
                    dComIfGp_particle_forceDeleteEmitter(i_this->m91C);
                    i_this->m91C = NULL;
                }
                dComIfGp_particle_set(dPa_name::ID_SCENE_809A, &a_this->current.pos);
                dComIfGp_particle_set(dPa_name::ID_SCENE_809B, &a_this->current.pos);
            }
            break;

        case 10:
            anm_init(i_this, KI_BCK_FLY1, 10.0f, 2, l_kiHIO.m08, KI_BAS_FLY1);
            i_this->mBehaviorType = 0xb;
            i_this->mTimers[1] = 100;
        
        case 11:
            i_this->m540 = 1;
            a_this->speed.y = 20.0f;
            if (i_this->mTimers[1] == 0) {
                i_this->m2DC = 1;
            }
            break;
    }

    cXyz sp24;
    cXyz sp18;

    sp24.x = 0.0f;
    sp24.y = 0.0f;
    sp24.z = a_this->speedF;

    cMtx_YrotS(*calc_mtx, a_this->current.angle.y);
    MtxPosition(&sp24, &sp18);

    a_this->current.pos.x += sp18.x;
    a_this->current.pos.y += a_this->speed.y;
    a_this->current.pos.z += sp18.z;
    a_this->speed.y -= REG8_F(10) + 8.0f;

    if (fopAcM_searchPlayerDistance(a_this) > 2000.0f && ki_player_bg_check(i_this)) {
        i_this->m2DC = 1;
    }
}

/* 00001D84-00002A18       .text ki_atack_move__FP8ki_class */
void ki_atack_move(ki_class* i_this) {
    fopEn_enemy_c* a_this = (fopEn_enemy_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz sp24;

    i_this->m540 = 1;
    s8 cVar6 = 0;

    if (i_this->mTimers[3] == 0 && i_this->mBehaviorType <= 3) {
        i_this->mTimers[3] = cM_rndF(14.0f) + 15.0f;
        fopAcM_monsSeStart(a_this, JA_SE_CV_KI_ATTACK, 0);
    }

    switch(i_this->mBehaviorType) {
        case 0:
            anm_init(i_this, KI_BCK_FLY1, 10.0f, 2, l_kiHIO.m08, KI_BAS_FLY1);
            i_this->mBehaviorType = 1;
            tex_anm_set(i_this, 0);
            i_this->mTimers[0] = l_kiHIO.m50 + cM_rndF(std::fabsf(l_kiHIO.m4E - l_kiHIO.m50));
            i_this->mTimers[2] = 20;

        case 1:
            i_this->mPosMoveTarget = l_kiHIO.m28;
            i_this->mPosMoveMaxSpeed = 2.0f;
            i_this->mPosMove = player->current.pos;
            i_this->mPosMove.y += 80.0f;

            sp24 = i_this->mPosMove - a_this->current.pos;
            cLib_addCalcAngleS2(&a_this->shape_angle.y, a_this->current.angle.y, 2, 0x1000);
            if (sp24.abs() < 300.0f) {
                i_this->mBehaviorType = 10;
                anm_init(i_this, KI_BCK_FLY2, 5.0f, 2, l_kiHIO.m14, KI_BAS_FLY2);
                i_this->mPosMoveDist = 0.0f;
            }
            break;

        case 2:
            if (i_this->mTimers[2] == 0) {
                ki_check(i_this);
                i_this->mTimers[2] = l_kiHIO.m4C;
                f32 tmp = l_kiHIO.m48;
                if (ki_fight_count >= l_kiHIO.m54) {
                    tmp *= 0.5f;
                    i_this->mTimers[2] <<= 1;
                }

                if (cM_rndF(1.0f) < tmp) {
                    i_this->mBehaviorType = 3;
                    anm_init(i_this, KI_BCK_ATTACK1, 5.0f, 2, l_kiHIO.m18, KI_BAS_ATTACK1);
                    i_this->mPosMove = player->current.pos;
                    i_this->mPosMove.y += 80.0f;
                    a_this->current.angle.y = fopAcM_searchPlayerAngleY(a_this);
                    a_this->speedF = 0.0f;
                    i_this->mPosMoveTarget = l_kiHIO.m44;
                    i_this->mPosMoveMaxSpeed = 3.0f;
                    i_this->mTimers[1] = 30;
                    break;
                }
            }

            cLib_addCalcAngleS2(&a_this->shape_angle.y, fopAcM_searchPlayerAngleY(a_this), 2, 0x1000);
            if (i_this->mTimers[1] == 0) {
                i_this->mTimers[1] = cM_rndF(50.0f) + 20.0f;
                s32 rndFX = cM_rndFX(l_kiHIO.m24 * 182.0444f);
                cMtx_YrotS(*calc_mtx, player->current.angle.y + rndFX);
                sp24.x = 0.0f;
#if VERSION == VERSION_DEMO
                sp24.y = cM_rndF(80.0f) + l_kiHIO.m1C;
#else
                sp24.y = cM_rndF(50.0f) + l_kiHIO.m1C;
#endif
                sp24.z = l_kiHIO.m20;
                MtxPosition(&sp24, &i_this->mPosMove);
                i_this->mPosMove += player->current.pos;
                i_this->mPosMoveDist = 0.0f;
            }

            sp24.x = cM_ssin(i_this->m320 * 0x76C) * 50.0f;
            sp24.y = cM_ssin(i_this->m320 * 0x9C4) * 60.0f;
            sp24.z = cM_scos(i_this->m320 * 0x5DC) * 50.0f;

            cLib_addCalc2(&a_this->current.pos.x, i_this->mPosMove.x + sp24.x, 0.1f, l_kiHIO.m2C * i_this->mPosMoveDist);
            cLib_addCalc2(&a_this->current.pos.y, i_this->mPosMove.y + sp24.y, 0.1f, l_kiHIO.m2C * i_this->mPosMoveDist);
            cLib_addCalc2(&a_this->current.pos.z, i_this->mPosMove.z + sp24.z, 0.1f, l_kiHIO.m2C * i_this->mPosMoveDist);
            cLib_addCalc2(&i_this->mPosMoveDist, 1.0f, 1.0f, 0.05f);
            cVar6 = -1;
            break;

        case 3:
            i_this->m580.SetR(30.0f);
            i_this->mDamageSphere.SetR(20.0f);
            i_this->m6AC.SetR(0.0f);
            if (i_this->mDamageType == 0) {
                i_this->m580.SetAtAtp(1);
            } else {
                i_this->m580.SetAtAtp(2);
            }

            cVar6 = 1;

            if (i_this->mTimers[1] == 10) {
                i_this->mPosMoveTarget = 0.0f;
                i_this->mPosMoveMaxSpeed = 3.0f;
            }

            if (i_this->mTimers[1] == 0) {
                anm_init(i_this, KI_BCK_FLY1, 5.0f, 2, l_kiHIO.m08, KI_BAS_FLY1);
                i_this->mBehaviorType = 1;
            }

            cLib_addCalcAngleS2(&a_this->shape_angle.y, a_this->current.angle.y, 2, 0x2000);

            if (i_this->m580.ChkAtHit() || i_this->mDamageSphere.ChkCoHit()) {
                anm_init(i_this, KI_BCK_FLY2, 2.0f, 2, l_kiHIO.m14, KI_BAS_FLY2);
                i_this->mBehaviorType = 4;
                i_this->mTimers[1] = 30;
                a_this->speedF = -15.0f;
                i_this->mPosMoveTarget = 0.0f;
                i_this->mPosMoveMaxSpeed = 1.0f;
            }
            break;

        case 4:
            if (i_this->mTimers[1] == 0) {
                anm_init(i_this, KI_BCK_FLY1, 3.0f, 2, l_kiHIO.m08, KI_BAS_FLY1);
                i_this->mBehaviorType = 1;
            }
            break;

        case 10:
            i_this->mPosMoveTarget = l_kiHIO.m30;
            ki_check(i_this);

            if (ki_fight_count < l_kiHIO.m52) {
                i_this->mBehaviorType = 2;
                i_this->mTimers[2] = 50;
            }

            cLib_addCalcAngleS2(&a_this->shape_angle.y, fopAcM_searchPlayerAngleY(a_this), 2, 0x1000);
            if (i_this->mTimers[1] == 0) {
                i_this->mTimers[1] = cM_rndF(50.0f) + 50.0f;
                s32 rndFX = cM_rndFX(32768.0f);
                cMtx_YrotS(*calc_mtx, player->current.angle.y + rndFX);
                sp24.x = 0.0f;
                sp24.y = (cM_rndFX(50.0f) + 200.0f) + REG0_F(12);
                sp24.z = l_kiHIO.m20 + REG0_F(13);
                MtxPosition(&sp24, &i_this->mPosMove);
                i_this->mPosMove += player->current.pos;
                i_this->mPosMoveDist = 0.0f;
            }

            sp24.x = cM_ssin(i_this->m320 * 0x76C) * 100.0f;
            sp24.y = cM_ssin(i_this->m320 * 0x9C4) * 60.0f;
            sp24.z = cM_scos(i_this->m320 * 0x5DC) * 100.0f;

            cLib_addCalc2(&a_this->current.pos.x, i_this->mPosMove.x + sp24.x, 0.1f, l_kiHIO.m30 * i_this->mPosMoveDist);
            cLib_addCalc2(&a_this->current.pos.y, i_this->mPosMove.y + sp24.y, 0.1f, l_kiHIO.m30 * i_this->mPosMoveDist);
            cLib_addCalc2(&a_this->current.pos.z, i_this->mPosMove.z + sp24.z, 0.1f, l_kiHIO.m30 * i_this->mPosMoveDist);
            cLib_addCalc2(&i_this->mPosMoveDist, 1.0f, 1.0f, 0.025f);
            cVar6 = -1;
            break;
    }

    i_this->m304 = 10000.0f;
    i_this->mPosMoveDist = 1.0f;

    if (cVar6 >= 0) {
        ki_pos_move(i_this, cVar6);
    }

    if (i_this->mParameters != 3) {
        if (ki_player_bg_check(i_this)) {
            i_this->mTimers[0] = 0;
        }

        if (i_this->mTimers[0] == 0) {
            i_this->mAction = i_this->mParameters;
#if VERSION > VERSION_DEMO
            i_this->mTimers[2] = 0;
#endif

            if (i_this->mKiPathIndex != 0xFF) {
                i_this->mCurrKiPathIndex = i_this->mKiPathIndex + 1;
                i_this->mBehaviorType = 0xFF;
            } else if (i_this->mAction == ki_class::ACT_FIRE_SET_MOVE_e) {
                i_this->mBehaviorType = 10;
            } else if (i_this->mAction == ki_class::ACT_WAIT_MOVE_e) {
                dBgS_LinChk linChk;
                cXyz sp18 = a_this->current.pos;
                sp18.y += 5000.0f;
                linChk.Set(&a_this->current.pos, &sp18, a_this);
                if (dComIfG_Bgsp()->LineCross(&linChk)) {
                    a_this->home.pos = linChk.GetCross();
                    a_this->home.pos.y -= 30.0f;
                    i_this->mBehaviorType = 10;
                    anm_init(i_this, KI_BCK_FLY1, 5.0f, 2, l_kiHIO.m08, KI_BAS_FLY1);
                } else {
                    i_this->mTimers[0] = 50;
                    i_this->mBehaviorType = 1;
                    i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
                }
            } else {
                i_this->mBehaviorType = 0;
                i_this->mTimers[0] = cM_rndF(50.0f) + 100.0f;
            }
        }
    }
}

/* 00002A18-00002E28       .text wall_angle_get__FP8ki_class */
s16 wall_angle_get(ki_class* i_this) {
    fopEn_enemy_c* a_this = (fopEn_enemy_c*)&i_this->actor;
    dBgS_LinChk linChk;
    cXyz sp2C[2];
    cXyz sp20;
    cXyz sp14;

    cMtx_YrotS(*calc_mtx, a_this->shape_angle.y);
    sp20.x = 0.0f;
    sp20.y = 0.0f;
    sp20.z = 100.0f;
    MtxPosition(&sp20, &sp14);
    sp14 += a_this->current.pos;
    sp20.x = 10.0f;
    sp20.y = 0.0f;
    sp20.z = -300.0f;

    for (s32 i = 0; i < 2; i++) {
        MtxPosition(&sp20, &sp2C[i]);
        sp20.x *= -1.0f;
        sp2C[i] += sp14;
        
        linChk.Set(&sp14, &sp2C[i], a_this);

        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            sp2C[i] = linChk.GetCross();
        } else {
            return TRUE;
        }
    }

    sp20 = sp2C[1] - sp2C[0];
    return cM_atan2s(sp20.x, sp20.z) + 0x4000;
}

/* 00002E28-00003114       .text ki_damage_move__FP8ki_class */
void ki_damage_move(ki_class* i_this) {
    bool bVar1 = false;

    i_this->m540 = 1;
    i_this->m314 = 3;

    switch (i_this->mBehaviorType) {
        case 0:
            anm_init(i_this, KI_BCK_DAMAGE1, 2.0f, 0, 1.0f, KI_BAS_DAMAGE1);
            tex_anm_set(i_this, 3);
            i_this->mBehaviorType = 1;

        case 1:
            if (i_this->m31C > 0.1f) {
                cLib_addCalcAngleS2(&i_this->actor.shape_angle.y, i_this->m316, 1, 0x3000);
                cXyz sp1C;
                sp1C.x = 0.0f;
                sp1C.y = 0.0f;
                sp1C.z = -i_this->m31C;
                cMtx_YrotS(*calc_mtx, i_this->m316);
                cMtx_XrotM(*calc_mtx, i_this->mRand2000);
                
                if (i_this->mAcch.ChkWallHit()) {
                    sp1C.z = 0.0f;
                    if (i_this->m31C >= l_kiHIO.m3C) {
                        i_this->mBehaviorType = 2;
                        i_this->mTimers[0] = 0x32;
                        anm_init(i_this, KI_BCK_BITA1, 1.0f, 0, 1.0f, KI_BAS_BITA1);
                        tex_anm_set(i_this, 3);
                        i_this->actor.speed.y = 0.0f;
                        csXyz shapeAngle = i_this->actor.shape_angle;
                        shapeAngle.y -= -0x8000;
                        s16 sVar2 = wall_angle_get(i_this);
                        if (sVar2 != 1) {
                            i_this->actor.current.angle.y = sVar2;
                        }
                        i_this->m904 = cM_rndF(1.9f);
                        bVar1 = true;
                    }
                }

                cXyz sp10;
                MtxPosition(&sp1C, &sp10);
                i_this->actor.current.pos.x += sp10.x;
                i_this->actor.current.pos.y += sp10.y;
                i_this->actor.current.pos.z += sp10.z;
                cLib_addCalc0(&i_this->m31C, 1.0f, l_kiHIO.m40);
                i_this->actor.speedF = 0.0;
            } else {
                i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
                i_this->mBehaviorType = 0;
                bVar1 = true;
            }
            break;

        case 2:
            cLib_addCalcAngleS2(&i_this->actor.shape_angle.y, i_this->actor.current.angle.y, 1, 0x4000);
            if (i_this->mTimers[0] < 30) {
                i_this->actor.current.pos.y += i_this->actor.speed.y;
                i_this->actor.speed.y -= 0.1f;
                if (i_this->m904 == 0) {
                    i_this->actor.shape_angle.z += -0x250;
                } else {
                    i_this->actor.shape_angle.z += 0x250;
                }
            }

            if (i_this->mTimers[0] == 0) {
                i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
                i_this->mBehaviorType = 0;
            }
            break;
    }

    if (bVar1 && i_this->actor.health <= 0) {
        i_this->mAction = ki_class::ACT_FAIL_MOVE_e;
        i_this->mBehaviorType = 0;
    }
}

void* bgn_s_sub(void* ac1, void*) {
    if (fopAcM_IsActor(ac1) && fopAcM_GetName(ac1) == PROC_BGN) {
        return ac1;
    }
    return NULL;
}

/* 00003114-00003278       .text ki_fail_move__FP8ki_class */
void ki_fail_move(ki_class* i_this) {
    fopEn_enemy_c* a_this = (fopEn_enemy_c*)&i_this->actor;
    u8 dropType;

#if VERSION == VERSION_DEMO
    if (fpcM_Search(bgn_s_sub, &i_this->actor) != NULL) {
#else
    if (strcmp(dComIfGp_getStartStageName(), "GanonK") == 0) {
#endif
        if (a_this->health != -10) {
#if VERSION == VERSION_DEMO
            if (dComIfGs_getLife() <= 4) {
#else
            if (dComIfGs_getLife() <= 8) {
#endif
                dropType = daDisItem_HEART_e;
            } else if (cM_rndF(1.0f) < 0.5f) {
#if VERSION == VERSION_DEMO
                if (dComIfGs_getMagic() <= 16) {
                    dropType = daDisItem_MAGIC_e;
                } else if (dComIfGs_getArrowNum() <= 10) {
                    dropType = daDisItem_ARROW_e;
                } else {
                    dropType = daDisItem_HEART_e;
                }
#else
                if (dComIfGs_getArrowNum() == 0) {
                    dropType = daDisItem_ARROW_e;
                } else if (dComIfGs_getMagic() < dComIfGs_getMaxMagic() / 2) {
                    dropType = daDisItem_MAGIC_e;
                } else if (dComIfGs_getArrowNum() < 10) {
                    dropType = daDisItem_ARROW_e;
                } else {
                    static u8 item_tbl[] = {daDisItem_HEART_e, daDisItem_MAGIC_e, daDisItem_ARROW_e, daDisItem_HEART_e};
                    dropType = item_tbl[(s32)cM_rndF(2.99f)];
                }
#endif
            } else {
                dropType = daDisItem_NONE13_e;
            }
        } else {
            dropType = daDisItem_NONE13_e;
        }
        fopAcM_createDisappear(a_this, &a_this->current.pos, 5, dropType, 0xFF);
    } else {
        fopAcM_createDisappear(a_this, &a_this->current.pos, 5, daDisItem_IBALL_e, 0xFF);
    }
    fopAcM_delete(a_this);
    fopAcM_onActor(a_this);
}

/* 00003278-000035D0       .text ki_path_move__FP8ki_class */
void ki_path_move(ki_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch (i_this->mBehaviorType) {
        case 0:
            i_this->m2D6 += i_this->m2D7;
            if (i_this->m2D6 >= (s8)i_this->ppd->m_num) {
                if (dPath_ChkClose(i_this->ppd)) {
                    i_this->m2D6 = 0;
                } else {
                    i_this->m2D7 = -1;
                    i_this->m2D6 = i_this->ppd->m_num - 2;
                }
                
                if ((s32)i_this->ppd->m_nextID != 0xFFFF) {
                    i_this->ppd = dPath_GetRoomPath(i_this->ppd->m_nextID, fopAcM_GetRoomNo(&i_this->actor));
                    JUT_ASSERT(DEMO_SELECT(1693, 1733), i_this->ppd != NULL)
                }
            } else if (i_this->m2D6 < 0) {
                i_this->m2D7 = 1;
                i_this->m2D6 = 1;
            }

        case -1: {
            i_this->mBehaviorType = 1;
            dPnt* point = &i_this->ppd->m_points[0];
            point += i_this->m2D6;
            i_this->mPosMoveTarget = cM_rndF(5.0f) + 30.0f;
            i_this->mPosMoveMaxSpeed = REG0_F(13) + 1.0f;
            i_this->mPosMoveDist = REG0_F(7);
            i_this->mPosMove = point->m_position;
            i_this->mPosMove.x = point->m_position.x + cM_rndFX(150.0f);
            i_this->mPosMove.y = point->m_position.y + cM_rndFX(150.0f);
            i_this->mPosMove.z = point->m_position.z + cM_rndFX(150.0f);
            break;
        }
        case 1:
            f32 x = i_this->mPosMove.x - i_this->actor.current.pos.x;
            f32 y = i_this->mPosMove.y - i_this->actor.current.pos.y;
            f32 z = i_this->mPosMove.z - i_this->actor.current.pos.z;

            if (std::sqrtf(x * x + y * y + z * z) < REG0_F(10) * 10.0f + 200.0f) {
                i_this->mBehaviorType = 0;
                if (i_this->ppd->m_points[i_this->m2D6].mArg3 == 6) {
                    fopAcM_delete(&i_this->actor);
                }
            }
            break;

    }

    i_this->mPosMoveTarget = l_kiHIO.m28;
    i_this->mPosMoveMaxSpeed = 2.0f;
    i_this->m304 = 4000.0f;
    i_this->mPosMoveDist = 1.0f;

    ki_pos_move(i_this, 0);

    cLib_addCalcAngleS2(&i_this->actor.shape_angle.y, i_this->actor.current.angle.y, 1, 0x2000);
    if (fopAcM_searchPlayerDistance(&i_this->actor) < i_this->mMaxAttackMoveDist300) {
        i_this->mCurrKiPathIndex = 0;
        i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
        i_this->mBehaviorType = 0;
    }
}

/* 000035D0-00003E04       .text daKi_Execute__FP8ki_class */
static BOOL daKi_Execute(ki_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s32 i;
    cXyz* ccMoveP;
    s16 tmp;
    CcAtInfo atInfo;
    J3DModel* model;

    i_this->actor.model = NULL;

    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->setPlayMode(J3DFrameCtrl::EMode_NONE);
        i_this->mpMorf->setPlaySpeed(3.0f);
        i_this->mpMorf->play(&i_this->actor.eyePos, 0, 0);
        J3DModel* model = i_this->mpMorf->getModel();
        model->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpMorf->calc();
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    if (i_this->m2DC != 0) {
        cLib_addCalc0(&i_this->actor.scale.x, 1.0f, 0.05f);
        i_this->actor.scale.y = i_this->actor.scale.z = i_this->actor.scale.x;
        if (i_this->actor.scale.x <= 0.04f) {
            fopAcM_delete(&i_this->actor);
            return TRUE;
        }
    }

    if (i_this->m2D4 != 0) {
        if (dComIfGs_isSwitch(i_this->m2D4 - 1, fopAcM_GetRoomNo(&i_this->actor))) {
            i_this->m2D4 = 0;
            i_this->actor.speedF = l_kiHIO.m28;
            i_this->actor.attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        } else {
            fopAcM_OnStatus(&i_this->actor, 0);
            fopAcM_OffStatus(&i_this->actor, 0);
            i_this->actor.attention_info.flags = 0;
            return TRUE;
        }
    }

    fopAcM_OnStatus(&i_this->actor, fopAcStts_SHOWMAP_e);

    if (l_kiHIO.m07 != 0) {
        ki_check(i_this);
        JUTReport(0x104, 0x186,"ALL      %d", ki_all_count);
        JUTReport(0x104, 0x19a,"READY    %d", ki_all_count - ki_fight_count);
        JUTReport(0x104, 0x1ae,"FIGHT    %d", ki_fight_count);
    }

    i_this->m580.SetR(0.0f);
    i_this->mDamageSphere.SetR(40.0f);
    i_this->m6AC.SetR(l_kiHIO.m58);

    if (l_kiHIO.m06 == 0) {
        i_this->m540 = 0;

        for (i = 0; i < 4; i++) {
            if (i_this->mTimers[i] != 0) {
                i_this->mTimers[i]--;
            }
        }

        if (i_this->m314 != 0) {
            i_this->m314--;
        }

        i_this->m320++;

        if (i_this->m338 == 0) {
            i_this->mpMorf->play(&i_this->actor.current.pos, 0, 0);
        } else {
            i_this->m338 = 0;
        }

        if (i_this->mAction == ki_class::ACT_ATTACK_MOVE_e) {
            ki_atack_move(i_this);
        } else if (i_this->mCurrKiPathIndex != 0) {
            ki_path_move(i_this);
        } else if (i_this->mAction == ki_class::ACT_WAIT_MOVE_e) {
            ki_wait_move(i_this);
        } else if (i_this->mAction == ki_class::ACT_FIRE_SET_MOVE_e) {
            ki_fire_set_move(i_this);
        } else if (i_this->mAction == ki_class::ACT_FLY_MOVE_e) {
            ki_fly_move(i_this);
        } else if (i_this->mAction == ki_class::ACT_ATTACK_MOVE_INDEX_e) {
            ki_atack_move(i_this);
        } else if (i_this->mAction == ki_class::ACT_DAMAGE_MOVE_e) {
            ki_damage_move(i_this);
        } else if (i_this->mAction == ki_class::ACT_FAIL_MOVE_e) {
            ki_fail_move(i_this);
        }
        ki_eye_tex_anm(i_this);
    }

    if (i_this->mDamageType != 0) {
        i_this->m920->play();
        if (i_this->mAction != ki_class::ACT_FAIL_MOVE_e) {
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8061, &i_this->actor.current.pos);
            fopAcM_seStart(&i_this->actor, JA_SE_OBJ_TORCH_BURNING, 0);
        }
    }

    ccMoveP = i_this->mStts.GetCCMoveP();
    if (ccMoveP != NULL) {
        i_this->actor.current.pos.x += ccMoveP->x;
        i_this->actor.current.pos.y += ccMoveP->y;
        i_this->actor.current.pos.z += ccMoveP->z;
    }

    MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, false);
    cMtx_YrotM(*calc_mtx, i_this->actor.shape_angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.shape_angle.x);
    cMtx_ZrotM(*calc_mtx, i_this->actor.shape_angle.z);

    model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->actor.scale);
    model->setBaseTRMtx(*calc_mtx);
    i_this->mpMorf->calc();
    enemy_fire(&i_this->mEnemyFire);

    i_this->actor.eyePos = i_this->actor.current.pos;
    i_this->actor.attention_info.position = i_this->actor.eyePos;
    i_this->actor.attention_info.position.y += 50.0f;

    i_this->m580.SetC(i_this->actor.current.pos);
    i_this->m6AC.SetC(i_this->actor.current.pos);
    i_this->mDamageSphere.SetC(i_this->actor.current.pos);

    dComIfG_Ccsp()->Set(&i_this->m580);
    dComIfG_Ccsp()->Set(&i_this->m6AC);
    dComIfG_Ccsp()->Set(&i_this->mDamageSphere);

    if (i_this->m540 != 0) {
#if VERSION > VERSION_DEMO
        i_this->actor.current.pos.y -= REG0_F(5) + 30.0f;
        i_this->actor.old.pos.y -= REG0_F(5) + 30.0f;
#endif
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());

#if VERSION > VERSION_DEMO
        i_this->actor.current.pos.y += REG0_F(5) + 30.0f;
        i_this->actor.old.pos.y += REG0_F(5) + 30.0f;
#endif
    }

    i_this->mStts.Move();
    if (i_this->mDamageSphere.ChkTgHit() && i_this->m314 == 0) {
        i_this->m314 = 10;

        atInfo.mpObj = i_this->mDamageSphere.GetTgHitObj();
        atInfo.pParticlePos = i_this->mDamageSphere.GetTgHitPosP();

        if (atInfo.mpObj->ChkAtType(AT_TYPE_LIGHT_ARROW | AT_TYPE_ICE_ARROW)) {
            if (atInfo.mpObj->ChkAtType(AT_TYPE_ICE_ARROW)) {
                i_this->mEnemyIce.mFreezeDuration = REG0_S(3) + 300;
                i_this->mAction = ki_class::ACT_ATTACK_MOVE_INDEX_e;
                i_this->mBehaviorType = 0;
            } else {
                i_this->mEnemyIce.mLightShrinkTimer = 1;
            }
            enemy_fire_remove(&i_this->mEnemyFire);
            return TRUE;
        }

        if (atInfo.mpObj->ChkAtType(AT_TYPE_FIRE_ARROW | AT_TYPE_FIRE)) {
            i_this->mEnemyFire.mFireDuration = REG0_S(2) + 100;
            i_this->m314 = 0x32;
            i_this->m580.OnAtVsBitSet(cCcD_AtSPrm_VsEnemy_e);
        }

        if (atInfo.mpObj->ChkAtType(AT_TYPE_WIND)) {
#if VERSION == VERSION_DEMO
            i_this->m31C = 130.0f;
#else
            i_this->m31C = 100.0f;
#endif
        } else {
            atInfo.mpActor = cc_at_check(&i_this->actor, &atInfo);

            if (atInfo.mpActor != NULL) {
                if (fpcM_GetName(atInfo.mpActor) == PROC_BGN || fpcM_GetName(atInfo.mpActor) == PROC_BGN2 || fpcM_GetName(atInfo.mpActor) == PROC_BGN3) {
                    i_this->actor.health = -10;
                }
            }

            if (l_kiHIO.m05 != 0) {
                i_this->actor.health = 10;
            }

#if VERSION > VERSION_DEMO
            if (atInfo.mResultingAttackType == 9) {
                i_this->m31C = 150.0f;
            } else
#endif
            if (i_this->mStts.GetAtSpl() == 1) {
                i_this->m31C = l_kiHIO.m38;
            } else {
                i_this->m31C = l_kiHIO.m34;
            }
        }

        i_this->m316 = fopAcM_searchPlayerAngleY(&i_this->actor);
        i_this->mRand2000 = cM_rndF(2000.0f);
        i_this->mAction = ki_class::ACT_DAMAGE_MOVE_e;
        i_this->mBehaviorType = 0;

        fopAcM_monsSeStart(&i_this->actor, JA_SE_CV_KI_DAMAGE, 0);
    }

    if (i_this->m322) {
        tmp = 0x1000;
    } else {
        tmp = 0x200;
    }
    cLib_addCalcAngleS2(&i_this->m326, i_this->m322, 5, tmp);

    if (i_this->m324) {
        tmp = 0x1000;
    } else {
        tmp = 0x200;
    }
    cLib_addCalcAngleS2(&i_this->m328, i_this->m324, 5, tmp);

    i_this->m324 = 0;
    i_this->m322 = 0;
    cLib_addCalcAngleS2(&i_this->actor.shape_angle.z, 0, 1, 0x200);
    return TRUE;
}

/* 00003E04-00003E0C       .text daKi_IsDelete__FP8ki_class */
static BOOL daKi_IsDelete(ki_class*) {
    return TRUE;
}

/* 00003E0C-00003EB8       .text daKi_Delete__FP8ki_class */
static BOOL daKi_Delete(ki_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Ki");
    
    if (i_this->m339 != 0) {
        hio_set = false;
        mDoHIO_deleteChild(l_kiHIO.mNo);
    }

#if VERSION > VERSION_DEMO
    if (i_this->actor.heap != NULL) {
        i_this->mpMorf->stopZelAnime();
    }
#endif

    if (i_this->mDamageType != 0) {
        i_this->m908.remove();
    }

    enemy_fire_remove(&i_this->mEnemyFire);
    return TRUE;
}

/* 00003EB8-000042B8       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    ki_class* i_this = (ki_class*)a_this;
    J3DModel* model;

    if (i_this->mDamageType == 0) {
        i_this->actor.gbaName = 0x17;
        i_this->mpMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("Ki", KI_BDL_KI),
            NULL, NULL,
            (J3DAnmTransform*)dComIfG_getObjectRes("Ki", KI_BCK_WAIT1),
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, 
            dComIfG_getObjectRes("Ki", KI_BAS_WAIT1),
            0x80000, 0x37221203
        );
#if VERSION == VERSION_DEMO
        model = i_this->mpMorf->getModel();
#else
        if (i_this->mpMorf == NULL || (model = i_this->mpMorf->getModel()) == NULL) {
            return FALSE;
        }
#endif
    } else {
        i_this->actor.gbaName = 6;
        i_this->mpMorf = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("Ki", KI_BDL_FK),
            NULL, NULL,
            (J3DAnmTransform*)dComIfG_getObjectRes("Ki", KI_BCK_WAIT1),
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, 
            dComIfG_getObjectRes("Ki", KI_BAS_WAIT1),
            0x80000, 0x37221203
        );

#if VERSION > VERSION_DEMO
        if (i_this->mpMorf == NULL) {
            return FALSE;
        }
#endif

        model = i_this->mpMorf->getModel();
        if (model == NULL) {
            return FALSE;
        }

        i_this->m920 = new mDoExt_btkAnm();
        if (i_this->m920 == NULL) {
            return FALSE;
        }

        if (!i_this->m920->init(model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Ki", KI_BTK_FK), true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
            return FALSE;
        }
    }

    for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
        if (i == 14) {
            model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }

    J3DAnmTexPattern* anmTexPattern;
    for (s32 i = 0; i < 4; i++) {
        anmTexPattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Ki", ki_tex_anm_idx[i]);
        anmTexPattern->searchUpdateMaterialID(model->getModelData());
    }

    u16 materialCount = anmTexPattern->getUpdateMaterialNum();
    i_this->m330 = new J3DTexNoAnm[materialCount];
    for (u16 i = 0; i < materialCount; i++) {
        i_this->m330[i].setAnmIndex(i); 
    }

    tex_anm_set(i_this, 1);
    i_this->mpMorf->getModel()->setUserArea((u32)i_this);
    return TRUE;
}

/* 00004364-000046F4       .text daKi_Create__FP10fopAc_ac_c */
static cPhs_State daKi_Create(fopAc_ac_c* a_this) {
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
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
            /* Radius */ 30.0f,
        }},
    };
    static dCcD_SrcSph tg_sph_src = {
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };
    static dCcD_SrcSph co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsPlayer_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
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
            /* Radius */ 80.0f,
        }},
    };

    ki_class* i_this = (ki_class*)a_this;

    fopAcM_SetupActor(a_this, ki_class);

    cPhs_State ret = dComIfG_resLoad(&i_this->mPhase, "Ki");
    if (ret == cPhs_COMPLEATE_e) {
        i_this->mParameters = fopAcM_GetParam(a_this);
        if (i_this->mParameters == 0xFF) {
            i_this->mParameters = 0;
        }

        i_this->mAction = i_this->mParameters;
        i_this->m2CD = fopAcM_GetParam(a_this) >> 8 & 0x7f;
        i_this->mDamageType = (fopAcM_GetParam(a_this) >> 8) & 0x80;
        i_this->mKiPathIndex = fopAcM_GetParam(a_this) >> 0x10;
        i_this->m2CF = fopAcM_GetParam(a_this) >> 0x18;
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("keeth", 0);

        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x4E00)) {
            return cPhs_ERROR_e;
        }

        switch (i_this->m2CD) {
            case 0:
                i_this->mMaxAttackMoveDist300 = 300.0f;
                break;

            case 1:
                i_this->mMaxAttackMoveDist300 = 800.0f;
                break;

            case 2:
                i_this->mMaxAttackMoveDist300 = 1500.0f;
                break;

            case 3:
            default:
                i_this->mMaxAttackMoveDist300 = 3000.0f;
                break;
        }

        if (i_this->mKiPathIndex != 0xFF) {
            i_this->ppd = dPath_GetRoomPath(i_this->mKiPathIndex, fopAcM_GetRoomNo(a_this));
            if (i_this->ppd == NULL) {
                return cPhs_ERROR_e;
            }
            i_this->mCurrKiPathIndex = i_this->mKiPathIndex + 1;
            i_this->m2D7 = 1;
        }

        if (i_this->m2CF != 0xFF) {
            i_this->m2D4 = i_this->m2CF + 1;
        }

        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this),
                        a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
#if VERSION == VERSION_DEMO
        i_this->mAcchCir.SetWall(10.0f, 20.0f);
        i_this->mAcch.SetGroundUpY(REG0_F(8) + 30.0f);
#else
        i_this->mAcchCir.SetWall(20.0f, 50.0f);
#endif
        a_this->health = 1;
        a_this->max_health = 1;
        i_this->m320 = cM_rndF(10000.0f);

        i_this->mStts.Init(0x32, 2, a_this);

        i_this->m580.Set(at_sph_src);
        i_this->m6AC.Set(co_sph_src);
        i_this->mDamageSphere.Set(tg_sph_src);

        i_this->m580.SetStts(&i_this->mStts);
        i_this->m6AC.SetStts(&i_this->mStts);
        i_this->mDamageSphere.SetStts(&i_this->mStts);

        if (i_this->mDamageType != 0) {
            i_this->m580.SetAtType(AT_TYPE_FIRE);
#if VERSION == VERSION_DEMO
            i_this->mDamageSphere.SetTgType(~(AT_TYPE_WATER | AT_TYPE_FIRE | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
#else
            i_this->mDamageSphere.SetTgType(~(AT_TYPE_WATER | AT_TYPE_FIRE | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
#endif
        }

        i_this->m580.OffAtVsBitSet(cCcD_AtSPrm_VsEnemy_e);
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;

        if (!hio_set) {
            l_kiHIO.mNo = mDoHIO_createChild("キース", &l_kiHIO);
            i_this->m339 = 1;
            hio_set = true;
        }

        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mWallRadius = REG0_F(4) + 30.0f;
        i_this->mEnemyIce.mCylHeight = REG0_F(5) + 30.0f;
        i_this->mEnemyIce.mParticleScale = 0.5f;
        i_this->mEnemyIce.mYOffset = 10.0f;
        i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
        i_this->mEnemyFire.mpActor = a_this;

        for (s32 i = 0; i < 10; i++) {
            static s8 fire_j[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
            static f32 fire_sc[] = { 1.0f, 0.8f, 0.7f, 0.6f, 0.5f, 1.0f, 0.8f, 0.7f, 0.6f, 0.5f };

            i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }

        daKi_Execute(i_this);
    }
    return ret;
}

static actor_method_class l_daKi_Method = {
    (process_method_func)daKi_Create,
    (process_method_func)daKi_Delete,
    (process_method_func)daKi_Execute,
    (process_method_func)daKi_IsDelete,
    (process_method_func)daKi_Draw,
};

actor_process_profile_definition g_profile_KI = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KI,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(ki_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KI,
    /* Actor SubMtd */ &l_daKi_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
