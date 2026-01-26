/**
 * d_a_kt.cpp
 * NPC - Unused - Small bird
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kt.h"
#include "d/res/res_kt.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_player.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_mtx.h"

static f32 kt_scale = 1.5f;

/* 00000078-000001BC       .text kotori_draw__FP8kt_class */
void kotori_draw(kt_class* i_this) {
    kt_scale = REG0_F(0) + 1.0f;
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y + i_this->mLiftY, i_this->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, i_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->mAngleRoll);
    cMtx_ZrotM(*calc_mtx, i_this->current.angle.z);
    f32 scaleMag = kt_scale * 0.2f;
    MtxScale(scaleMag, scaleMag, scaleMag, true);
    J3DModel* model = i_this->mpModel;
    model->setBaseTRMtx(*calc_mtx);
    mDoExt_modelUpdate(model);
    if (i_this->mWingScale < 10.0f) {
        MtxTrans(0.0, 130.0f, 80.0f, true);
        MtxScale(1.0f, i_this->mWingScale, 1.0f, true);
        i_this->mpModelWing->setBaseTRMtx(*calc_mtx);
        mDoExt_modelUpdate(i_this->mpModelWing);
    }
}

/* 000001BC-000001E0       .text daKt_Draw__FP8kt_class */
static BOOL daKt_Draw(kt_class* i_this) {
    kotori_draw(i_this);
    return TRUE;
}

/* 000001E0-000011D4       .text kotori_move__FP8kt_class */
void kotori_move(kt_class* i_this) {
    /* Nonmatching - regalloc */
    f32* r28;
    f32* r27;
    f32* r26;
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    bool dispWing = false;
    u8 ret = 0;
    dBgS_GndChk gndChk;

    f32 dx = player->current.pos.x - *(r28 = &i_this->current.pos.x);
    f32 dz = player->current.pos.z - *(r27 = &i_this->current.pos.z);
    f32 dist_xz = std::sqrtf(dx*dx + dz*dz);
    cLib_addCalcAngleS2(&i_this->mAngleRoll, 0, 2, REG0_S(4) + 0x1000);

    f32 vx = i_this->mTargetPos.x - *r28;
    f32 vy = i_this->mTargetPos.y - *(r26 = &i_this->current.pos.y);
    f32 vz = i_this->mTargetPos.z - *r27;
    s16 angleX = cM_atan2s(vx, vz);
    s16 angleY = -cM_atan2s(vy, std::sqrtf(vx*vx + vz*vz));

    cXyz offs;
    cXyz pt;
    cXyz headTopPos = player->getHeadTopPos();
    f32 dist;
    
    s16* r18;
    s16* r17;
    s16* r16;

    switch (i_this->mMode) {
    case 0:
        i_this->mSpeedFwd = kt_scale * 20.0f + 30.0f;
        if (CPad_CHECK_TRIG_LEFT(0) && fopAcM_GetParam(i_this) == 1000) {
            i_this->mTargetPos.x = player->current.pos.x;
            i_this->mTargetPos.y = player->current.pos.y + 500.0f;
            i_this->mTargetPos.z = player->current.pos.z;
            i_this->mMode = 2;
            i_this->mSpeedLerp = 0.0f;
            break;
        }

        if (i_this->mTimer[2] == 0) {
            i_this->mMode = 1;
            offs.x = 0.0f;
            offs.y = 0.0f;
            offs.z = REG0_F(13) * 100.0f + 3000.0f;
            cMtx_YrotS(*calc_mtx, player->shape_angle.y);

            MtxPosition(&offs, &pt);
            i_this->mTargetPosHome.x = player->current.pos.x + pt.x + cM_rndFX(REG0_F(14) + 200.0f);
            i_this->mTargetPosHome.y = player->current.pos.y + 1000.0f;
            i_this->mTargetPosHome.z = player->current.pos.z + pt.z + cM_rndFX(REG0_F(14) + 200.0f);

            gndChk.SetPos(&i_this->mTargetPosHome);
            i_this->mTargetPosHome.y = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (i_this->mTargetPosHome.y == -G_CM3D_F_INF)
                i_this->mTargetPosHome = player->current.pos;
            i_this->mTargetPos = i_this->mTargetPosHome;
            i_this->mSpeedLerp = 0.0f;
        } else if (i_this->mTimer[0] == 0) {
            i_this->mTimer[0] = cM_rndF(250.0f) + 60.0f;
            i_this->mTargetPos.x = i_this->mTargetPosHome.x + cM_rndFX(2000.0f);
            i_this->mTargetPos.z = i_this->mTargetPosHome.z + cM_rndFX(2000.0f);
            i_this->mTargetPos.y = i_this->mTargetPosHome.y + cM_rndF(1000.0f);
            i_this->mSpeedLerp = 0.0f;
        }

        cLib_addCalc2(&i_this->mSpeedLerp, 1.0f, 1.0f, 0.1f);
        goto calc_012;
    case 1:
        dist = std::sqrtf(vx*vx + vy*vy + vz*vz);
        if (dist < REG0_F(1) * 10.0f + 800.0f) {
            i_this->mMode = 8;
        }
        cLib_addCalc2(&i_this->mSpeedLerp, 3.0f, 1.0f, 0.1f);
calc_012:
        r18 = &i_this->current.angle.y;
        cLib_addCalcAngleS2(r18, angleX, 10, (s16)((REG0_F(2) * 10.0f + 500.0f) * i_this->mSpeedLerp));
        r17 = &i_this->current.angle.x;
        cLib_addCalcAngleS2(r17, angleY, 10, (s16)((REG0_F(2) * 10.0f + 500.0f) * i_this->mSpeedLerp));
        offs.x = 0.0f;
        offs.y = 0.0f;
        offs.z = i_this->mSpeedFwd;
        mDoMtx_YrotS(*calc_mtx, *r18);
        mDoMtx_XrotM(*calc_mtx, *r17);
        MtxPosition(&offs, &i_this->mSpeedVel);
        *r28 += i_this->mSpeedVel.x;
        *r26 += i_this->mSpeedVel.y;
        *r27 += i_this->mSpeedVel.z;
        if (i_this->mLiftYTimer >= 0.0f)
            dispWing = true;
        ret = 2;
        break;
    case 8:
        r16 = &i_this->current.angle.y;
        cLib_addCalcAngleS2(&i_this->current.angle.y, angleX, 10, (s16)((REG0_F(3) * 10.0f + 1500.0f) * i_this->mSpeedLerp));
        cLib_addCalc0(&i_this->mSpeedLerp, 1.0f, REG0_F(4) + 0.05f);
        cLib_addCalc0(&i_this->mSpeedFwd, 1.0f, REG0_F(5) + 1.0f);
        offs.x = 0.0f;
        offs.y = 0.0f;
        offs.z = i_this->mSpeedFwd;
        mDoMtx_YrotS(*calc_mtx, *r16);
        MtxPosition(&offs, &pt);
        *r28 += pt.x;
        *r27 += pt.z;
        cLib_addCalc2(&*r26, i_this->mGroundY, REG0_F(6) + 0.3f, REG0_F(7) + 20.0f);
        if (std::fabsf(*r26 - i_this->mGroundY) < 1.0f) {
            *r26 = i_this->mGroundY;
            i_this->mMode = 10;
        }
        dispWing = true;
        ret = 1;
        break;
    case 2:
        i_this->mTargetPos = headTopPos;
        i_this->mTargetPos.y += 200.0f;
        dist = std::sqrtf(vx*vx + vy*vy + vz*vz);
        if (dist < REG0_F(1) * 10.0f + 800.0f) {
            i_this->mMode = 9;
        }
        cLib_addCalc2(&i_this->mSpeedLerp, 3.0f, 1.0f, 0.1f);
        goto calc_012;
        break;
    case 9:
        i_this->mTargetPos = headTopPos;
        i_this->mTargetPos.y += 100.0f;
        r16 = &i_this->current.angle.y;
        cLib_addCalcAngleS2(&i_this->current.angle.y, angleX, 10, (s16)((REG0_F(3) * 10.0f + 1500.0f) * i_this->mSpeedLerp));
        cLib_addCalc0(&i_this->mSpeedLerp, 1.0f, REG0_F(4) + 0.05f);
        cLib_addCalc0(&i_this->mSpeedFwd, 1.0f, REG0_F(5) + 1.0f);
        offs.x = 0.0f;
        offs.y = 0.0f;
        offs.z = i_this->mSpeedFwd;
        mDoMtx_YrotS(*calc_mtx, *r16);
        MtxPosition(&offs, &pt);
        *r28 += pt.x;
        *r27 += pt.z;
        cLib_addCalc2(&*r26, i_this->mTargetPos.y, REG0_F(6) + 0.5f, REG0_F(7) + 20.0f);
        if (std::fabsf(*r26 - i_this->mTargetPos.y) < 1.0f) {
            i_this->mMode = 20;
            i_this->mSpeedLerp = 0.0f;
        }
        dispWing = true;
        ret = 1;
        break;
    case 20:
        i_this->mTargetPos = headTopPos;
        cLib_addCalc2(&*r28, i_this->mTargetPos.x, 1.0f, i_this->mSpeedLerp);
        cLib_addCalc2(&*r26, i_this->mTargetPos.y, 1.0f, i_this->mSpeedLerp * 0.5f);
        cLib_addCalc2(&*r27, i_this->mTargetPos.z, 1.0f, i_this->mSpeedLerp);
        cLib_addCalc2(&i_this->mSpeedLerp, 1000.0f, 1.0f, REG0_F(16) + 10.0f);
        cLib_addCalcAngleS2(&i_this->current.angle.y, player->shape_angle.y, 2, 0x1000);
        if (std::fabsf(*r26 - i_this->mTargetPos.y) > 1.0f)
            dispWing = true;
        if (CPad_CHECK_TRIG_LEFT(0)) {
            i_this->mMode = 0;
            i_this->mTimer[0] = 0;
            i_this->mLiftYTimer = cM_rndFX(10.0f) + 10.0f;
            i_this->mTargetPosHome.y += 2000.0f;
            i_this->current.angle.x = -0x2000;
            i_this->mTimer[2] = REG0_S(5) + 300;
        }
        break;
    case 10: {
        i_this->mLiftY += i_this->mLiftYTimer;
        i_this->mLiftYTimer -= REG0_F(8) * 0.1f + 5.0f;
        if (i_this->mLiftY <= 0.0f) {
            i_this->mLiftYTimer = REG0_F(9) + 15.0f;
            i_this->mLiftY = 0.0f;
        }
        s16* r16_2 = &i_this->current.angle.y;
        cLib_addCalcAngleS2(&i_this->current.angle.y, angleX, 10, (s16)(REG0_F(10) * 10.0f + 500.0f));
        if (i_this->mTimer[1] == 0 && i_this->mLiftY <= 0.0f) {
            i_this->mTimer[1] = 20.0f + cM_rndF(20.0f);
            i_this->mMode = 11;
        }
        offs.x = 0.0f;
        offs.y = 0.0f;
        offs.z = REG0_F(11) + 10.0f;
        mDoMtx_YrotS(*calc_mtx, *r16_2);
        MtxPosition(&offs, &i_this->mSpeedVel);
        *r28 += i_this->mSpeedVel.x;
        *r27 += i_this->mSpeedVel.z;
        goto calc_11;
        break;
    }
    case 11:
        if (i_this->mTimer[0] == 0) {
            i_this->mTimer[0] = cM_rndF(2.0f) + 10.0f + REG0_F(12);
        }
        if (i_this->mTimer[0] > (s16)(REG0_S(1) + 8)) {
            cLib_addCalcAngleS2(&i_this->mAngleRoll, REG0_S(2) + 0x3000, 2, REG0_S(3) + 0x2000);
        }
        if (i_this->mTimer[1] == 0) {
            i_this->mTimer[1] = 20.0f + cM_rndF(50.0f);
            i_this->mMode = 10;
            i_this->mTargetPos.x = i_this->mTargetPosHome.x + cM_rndFX(1000.0f);
            i_this->mTargetPos.z = i_this->mTargetPosHome.z + cM_rndFX(1000.0f);
        }
calc_11:
        *r26 -= 5.0f;
        if (!i_this->mHitGround || dist_xz < (REG0_F(15) * 100.0f + 1500.0f)) {
            i_this->mMode = 0;
            i_this->mTimer[0] = 0;
            i_this->mLiftYTimer = 10.0f + cM_rndFX(10.0f);
            i_this->mTargetPosHome.y += 2000.0f;
            i_this->current.angle.x = -0x2000;
            i_this->mTimer[2] = REG0_S(5) + 300;
        }
        break;
    }

    i_this->mHitGround = false;
    if (i_this->mMode >= 8) {
        Vec pos;
        pos.x = *r28;
        pos.y = *r26;
        pos.z = *r27;
        pos.y += 1000.0f;
        gndChk.SetPos(&pos);
        i_this->mGroundY = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (*r26 <= i_this->mGroundY) {
            *r26 = i_this->mGroundY;
            i_this->mHitGround = true;
        }
    }

    if (ret == 2) {
        i_this->mLiftY += i_this->mLiftYTimer;
        i_this->mLiftYTimer -= 1.5f;
        if (i_this->mLiftY <= 0.0f) {
            i_this->mLiftYTimer = cM_rndF(5.0f) + 15.0f;
        }
    } else if (ret == 1) {
        cLib_addCalc0(&i_this->mLiftY, 1.0f, 2.0f);
        i_this->mLiftYTimer = 0.0f;
    }

    if (dispWing) {
        i_this->mWingScale = cM_ssin(i_this->mWingTimer);
    } else {
        i_this->mWingScale = 100.0f;
    }
}

/* 000011D4-00001240       .text daKt_Execute__FP8kt_class */
static BOOL daKt_Execute(kt_class* i_this) {
    i_this->mWingTimer = i_this->mWingTimer + 0x5e76 + REG0_S(0);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mTimer); i++)
        if (i_this->mTimer[i] != 0)
            --i_this->mTimer[i];
    kotori_move(i_this);
    return TRUE;
}

/* 00001240-00001248       .text daKt_IsDelete__FP8kt_class */
static BOOL daKt_IsDelete(kt_class* i_this) {
    return TRUE;
}

/* 00001248-00001278       .text daKt_Delete__FP8kt_class */
static BOOL daKt_Delete(kt_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Kt");
    return TRUE;
}

/* 00001278-0000134C       .text daKt_solidHeapCB__FP10fopAc_ac_c */
static BOOL daKt_solidHeapCB(fopAc_ac_c* i_ac) {
    kt_class* i_this = (kt_class*)i_ac;

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Kt", KT_INDEX_BMD_KT_MODEL);
    i_this->mpModel = mDoExt_J3DModel__create(modelData, 0x10000, 0x11020203);

    J3DModelData* modelDataWing = (J3DModelData*)dComIfG_getObjectRes("Kt", KT_INDEX_BMD_KT_HANE);
    i_this->mpModelWing = mDoExt_J3DModel__create(modelDataWing, 0x10000, 0x11020203);

    return modelData != NULL && modelDataWing != NULL && i_this->mpModel != NULL && i_this->mpModelWing != NULL;
}

/* 0000134C-00001530       .text daKt_Create__FP10fopAc_ac_c */
static cPhs_State daKt_Create(fopAc_ac_c* i_ac) {
    fopAcM_SetupActor(i_ac, kt_class);
    kt_class* i_this = (kt_class*)i_ac;

    cPhs_State rt = dComIfG_resLoad(&i_this->mPhs, "Kt");
    if (rt == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, daKt_solidHeapCB, 0)) {
            s32 num = fopAcM_GetParam(i_this);
            if (num < 1000) {
                i_this->current.pos.y = REG0_F(0) * 10.0f + 2500.0f;
                fopAcM_SetParam(i_this, 1000);
                for (s32 i = 0; i < num; i++) {
                    fopAcM_prm_class* params = fopAcM_CreateAppend();
                    params->base.position = i_this->current.pos;
                    params->base.angle.set(0, 0, 0);
                    params->base.parameters = 1001 + i;
                    fpcM_Create(PROC_KT, NULL, params);
                }
            }

            i_this->mpModel->setBaseScale(i_this->scale);
            i_this->mpModelWing->setBaseScale(i_this->scale);
            i_this->current.pos.y += 2500.0f;
            i_this->mTargetPosHome = i_this->mHomePos = i_this->current.pos;
            i_this->mTimer[2] = REG0_S(5) + 500;
        } else {
            rt = cPhs_ERROR_e;
        }
    }

    return rt;
}

static actor_method_class l_daKt_Method = {
    (process_method_func)daKt_Create,
    (process_method_func)daKt_Delete,
    (process_method_func)daKt_Execute,
    (process_method_func)daKt_IsDelete,
    (process_method_func)daKt_Draw,
};

actor_process_profile_definition g_profile_KT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kt_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KT,
    /* Actor SubMtd */ &l_daKt_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
