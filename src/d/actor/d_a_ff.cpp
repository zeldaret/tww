/**
 * d_a_ff.cpp
 * Object - Firefly (not collectable)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_ff.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_lib.h"
#include "d/res/res_ff.h"

static s32 ff_count = 0;

/* 00000078-000001E4       .text fire_fly_draw__FP8ff_class */
static void fire_fly_draw(ff_class* i_this) {
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, false);
    MtxScale(i_this->mScale, i_this->mScale, i_this->mScale, true);
    i_this->mpModel[0]->setBaseTRMtx(*calc_mtx);
    if (i_this->mScale > 0.01f) {
        i_this->mBrkAnm[0]->play();
        i_this->mBrkAnm[0]->entry(i_this->mpModel[0]->getModelData());
        dComIfGd_setListMaskOff();
        mDoExt_modelUpdate(i_this->mpModel[0]);
        if (i_this->mGlowScale > 0.01f) {
            cMtx_YrotM(*calc_mtx, i_this->mLiveTimer * 0x100);
            MtxScale(i_this->mGlowScale, i_this->mGlowScale * i_this->mGlowScaleY,
                     i_this->mGlowScale, true);
            i_this->mpModel[1]->setBaseTRMtx(*calc_mtx);
            i_this->mBrkAnm[1]->play();
            i_this->mBrkAnm[1]->entry(i_this->mpModel[1]->getModelData());
            mDoExt_modelUpdate(i_this->mpModel[1]);
        }
        dComIfGd_setList();
    }
}

/* 000001E4-000002EC       .text z_check__FP8ff_classP4cXyz */
static void z_check(ff_class* i_this, cXyz* param_2) {
    u32 local_28;

    if ((param_2->x < 0.0f) || (param_2->x > 638.99f) || (param_2->y < 0.0f) ||
        (param_2->y > 526.99f) || (param_2->z >= 0.0f))
    {
        i_this->mbNotVisibleZ = 1;
    } else {
        GXDrawDone();
        GXPeekZ((u16)param_2->x, (u16)param_2->y, &local_28);
        f32 fVar1 = 0.5f - param_2->z * -1.0f;
        if (fVar1 < 0.0f) {
            fVar1 = 0.0f;
        }
        if ((u32)(fVar1 * 33553002.0f) > local_28) {
            i_this->mbNotVisibleZ = 1;
        } else {
            i_this->mbNotVisibleZ = 0;
        }
    }
}

/* 000002EC-0000037C       .text daFf_Draw__FP8ff_class */
static BOOL daFf_Draw(ff_class* i_this) {
    cXyz cStack_18;

    mDoLib_project(&i_this->current.pos, &cStack_18);
    z_check(i_this, &cStack_18);
    if (i_this->mbNotVisibleZ != 0) {
        cLib_addCalc0(&i_this->mGlowScale, 1.0f, 0.33333f);
    } else {
        cLib_addCalc2(&i_this->mGlowScale, 1.0f, 1.0f, 0.3333f);
    }
    fire_fly_draw(i_this);
    return TRUE;
}

/* 0000037C-00000D18       .text fire_fly_move__FP8ff_class */
static void fire_fly_move(ff_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dBgS_GndChk chk;
    f32 step;
    cXyz local_cc;

    i_this->mLiveTimer++;
    if (i_this->mTimers[2] == 0) {
        i_this->mTimers[1] = cM_rndF(50.0f) + 40.0f;
        i_this->mTimers[2] = cM_rndF(200.0f) + 100.0f;
    }
    if (i_this->mTimers[1] == 0) {
        i_this->mScaleTarget = cM_ssin(i_this->mLiveTimer * 1000) * 0.15f * 0.25f + 0.225f;
    } else {
        i_this->mScaleTarget = 0.0f;
    }

    cLib_addCalc2(&i_this->mScale, i_this->mScaleTarget, 0.1f, 0.05f);
    switch (i_this->mMode) {
    case 0:
        Vec pos;
        pos = i_this->current.pos;
        pos.y += 250.0f;
        chk.SetPos(&pos);
        i_this->mGroundY = dComIfG_Bgsp()->GroundCross(&chk) + 12.5f;
        if (i_this->mbNoUseGroundY == 0) {
            i_this->current.pos.y = i_this->mGroundY;
        }
        i_this->mHomePos = i_this->current.pos;
        i_this->mMode++;
        // Fall-through
    case 1: {
        cLib_addCalc2(&i_this->current.pos.x, i_this->mHomePos.x, 0.1f, std::abs(i_this->speed.x));
        cLib_addCalc2(&i_this->current.pos.y, i_this->mHomePos.y, 0.1f, std::abs(i_this->speed.y));
        cLib_addCalc2(&i_this->current.pos.z, i_this->mHomePos.z, 0.1f, std::abs(i_this->speed.z));
        f32 xd = player->current.pos.x - i_this->current.pos.x;
        f32 yd = player->current.pos.y - i_this->current.pos.y;
        f32 zd = player->current.pos.z - i_this->current.pos.z;
        xd = std::sqrtf(xd * xd + yd * yd + zd * zd);
        if (xd < 250.0f) {
            i_this->mMode++;
            xd = cM_rndF(100.0f);
            i_this->mTimers[3] = (xd + 1000.0f);
            i_this->current.angle.x = -0x3000;
            i_this->speedF = 10.0f;
        }
        goto label_870;
    }
    case 2: {
        if (i_this->mTimers[0] == 0) {
            i_this->mScatterPos.x = i_this->mHomePos.x + cM_rndFX(750.0f);
            i_this->mScatterPos.z = i_this->mHomePos.z + cM_rndFX(750.0f);
            i_this->mScatterPos.y = i_this->mHomePos.y + cM_rndFX(225.0f) + 137.5f;
            i_this->mRotVel = 0.0f;
            i_this->mVelocityFwdTarget = cM_rndF(20.0f) + 10.0f;
            f32 xd = i_this->mScatterPos.x - i_this->current.pos.x;
            f32 yd = i_this->mScatterPos.y - i_this->current.pos.y;
            f32 zd = i_this->mScatterPos.z - i_this->current.pos.z;
            f32 dist = std::sqrtf(xd * xd + yd * yd + zd * zd);
            i_this->mTimers[0] = dist / i_this->mVelocityFwdTarget;
            i_this->mTargetRotY = cM_atan2s(xd, zd);
            f32 xz_dist = std::sqrtf(xd * xd + zd * zd);
            i_this->mTargetRotX = -cM_atan2s(yd, xz_dist);
        }
        if (i_this->mTimers[3] == 0) {
            i_this->mMode++;
            i_this->mScatterPos.x = i_this->mHomePos.x;
            i_this->mScatterPos.y = i_this->mHomePos.y;
            i_this->mScatterPos.z = i_this->mHomePos.z;
            i_this->mRotVel = 0.0f;
        }
        break;
    }
    case 3: {
        f32 xd = i_this->mScatterPos.x - i_this->current.pos.x;
        f32 yd = i_this->mScatterPos.y - i_this->current.pos.y;
        f32 zd = i_this->mScatterPos.z - i_this->current.pos.z;
        i_this->mTargetRotY = cM_atan2s(xd, zd);
        f32 xz_dist = std::sqrtf(xd * xd + zd * zd);
        i_this->mTargetRotX = -cM_atan2s(yd, xz_dist);
        if (((xd * xd) + (yd * yd) + (zd * zd)) < 2500.0f) {
            i_this->mMode = 1;
        }
        cLib_addCalc2(&i_this->mRotVel, 10.0f, 1.0f, 0.15f);
        break;
    }
    case 4:
        f32 f30;
        if (i_this->mTimers[4] == 0) {
            i_this->mMode = 2;
            f30 = cM_rndF(100.0f);
            i_this->mTimers[3] = (f30 + 1000.0f);
        } else {
            i_this->mVelImpulse += i_this->m2C0;
            f30 = cM_rndF(1.0f);
            if (f30 < REG13_F(0) + 0.1f) {
                f30 = cM_rndFX(REG13_F(1) + 1.0f);
                i_this->m2C0.x = f30;
            }
            f30 = cM_rndF(1.0f);
            if (f30 < REG13_F(0) + 0.1f) {
                f30 = cM_rndFX(REG13_F(1) + 1.0f);
                i_this->m2C0.z = f30;
            }
            i_this->m2C0.y = REG13_F(2) + 2.0f;
            if (i_this->mVelImpulse.y > REG13_F(3) + 10.0f) {
                i_this->mVelImpulse.y = REG13_F(3) + 10.0f;
            }
        }
        break;
    default:
        goto label_870;
    }

    step = 500.0f;
    cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->mTargetRotY, 10,
                        step * i_this->mRotVel);
    cLib_addCalcAngleS2(&i_this->current.angle.x, i_this->mTargetRotX, 10,
                        step * i_this->mRotVel);
    cLib_addCalc2(&i_this->mRotVel, 1.0f, 1.0f, 0.1f);
    cLib_addCalc2(&i_this->speedF, i_this->mVelocityFwdTarget, 1.0f, 3.0f);
    local_cc.x = 0.0f;
    local_cc.y = 0.0f;
    local_cc.z = i_this->speedF * 0.25f;
    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    MtxPosition(&local_cc, &i_this->speed);
    i_this->current.pos += (i_this->speed + i_this->mVelImpulse);
    cLib_addCalc0(&i_this->mVelImpulse.x, 1.0f, 0.1f);
    cLib_addCalc0(&i_this->mVelImpulse.y, 1.0f, 0.1f);
    cLib_addCalc0(&i_this->mVelImpulse.z, 1.0f, 0.1f);

label_870:
    if (i_this->current.pos.y < i_this->mGroundY + 12.5f) {
        if (i_this->current.pos.y < i_this->mGroundY) {
            i_this->current.pos.y = i_this->mGroundY;
        }
        cLib_addCalc2(&i_this->mGlowScaleY, 0.5f, 0.2f, 0.1f);
    } else {
        cLib_addCalc2(&i_this->mGlowScaleY, 1.0f, 0.2f, 0.1f);
    }
}

/* 00001098-00001168       .text daFf_Execute__FP8ff_class */
static BOOL daFf_Execute(ff_class* i_this) {
    for (int i = 0; i < 5; i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }
    fire_fly_move(i_this);
    if (i_this->mSph.ChkTgHit() != 0) {
        i_this->mMode = 4;
        i_this->mTimers[4] = REG13_F(9) + (cM_rndF(20.0f) + 30.0f);
    }
    i_this->mSph.SetC(i_this->current.pos);
    dComIfG_Ccsp()->Set(&i_this->mSph);
    return TRUE;
}

/* 00001168-00001170       .text daFf_IsDelete__FP8ff_class */
static BOOL daFf_IsDelete(ff_class*) {
    return TRUE;
}

/* 00001170-000011AC       .text daFf_Delete__FP8ff_class */
static BOOL daFf_Delete(ff_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhs, "Ff");
    ff_count = 0;
    return TRUE;
}

/* 000011AC-0000138C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    static u32 ho_bmd[] = {FF_BMD_HO, FF_BMD_HOP};
    static u32 ho_brk[] = {FF_BRK_HO, FF_BRK_HOP};
    ff_class* a_this = (ff_class*)i_this;

    for (int i = 0; i < 2; i++) {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Ff", ho_bmd[i]);
        JUT_ASSERT(DEMO_SELECT(717, 719), modelData != NULL);
#if VERSION > VERSION_DEMO
        if (modelData == NULL) {
            return FALSE;
        }
#endif
        a_this->mpModel[i] = mDoExt_J3DModel__create(modelData, 0x10000, 0x11020203);
        if (a_this->mpModel[i] == NULL) {
            return FALSE;
        }
        a_this->mBrkAnm[i] = new mDoExt_brkAnm();
        if (a_this->mBrkAnm[i] == NULL) {
            return FALSE;
        }
        int iVar6 = a_this->mBrkAnm[i]->init(
            a_this->mpModel[i]->getModelData(),
            (J3DAnmTevRegKey*)dComIfG_getObjectRes("Ff", ho_brk[i]),
            true, J3DFrameCtrl::EMode_LOOP, 0.9f + cM_rndF(0.15f), 0, -1, false, 0
        );
#if VERSION > VERSION_DEMO
        if (iVar6 == 0) {
            return FALSE;
        }
#endif
    }
    return TRUE;
}

/* 000013D4-0000164C       .text daFf_Create__FP10fopAc_ac_c */
static cPhs_State daFf_Create(fopAc_ac_c* i_this) {
    fopAcM_SetupActor(i_this, ff_class);
    ff_class* a_this = (ff_class*)i_this;
    cPhs_State phase_state = dComIfG_resLoad(&a_this->mPhs, "Ff");

    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(a_this, useHeapInit, 0x2320)) {
            int uVar1 = fopAcM_GetParam(a_this) & 0xFF;
            if (uVar1 != 0) {
                fopAcM_SetParam(a_this, fopAcM_GetParam(a_this) & 0xFF00);
                for (int i = 0; i < uVar1; i++) {
                    fopAcM_prm_class* pfVar4 = fopAcM_CreateAppend();
                    pfVar4->base.position.x = a_this->current.pos.x + cM_rndFX(500.0f);
                    pfVar4->base.position.y = a_this->current.pos.y;
                    pfVar4->base.position.z = a_this->current.pos.z + cM_rndFX(500.0f);
                    pfVar4->base.angle.z = 0;
                    pfVar4->base.angle.y = 0;
                    pfVar4->base.angle.x = 0;
                    pfVar4->base.parameters = fopAcM_GetParam(a_this);
                    fopAcM_create(PROC_FF, NULL, pfVar4);
                }
            }
            a_this->mbNoUseGroundY = fopAcM_GetParam(a_this) >> 8;
            ff_count++;
            a_this->cullMtx = a_this->mpModel[0]->getBaseTRMtx();
            a_this->mHomePos = a_this->current.pos;
            a_this->m2EC = a_this->mHomePos;
            a_this->mLiveTimer = cM_rndF(32768.0f);
            a_this->mTimers[2] = cM_rndF(100.0f);
            static dCcD_SrcSph cc_sph_src = {
                // dCcD_SrcGObjInf
                {
                    /* Flags             */ 0,
                    /* SrcObjAt  Type    */ 0,
                    /* SrcObjAt  Atp     */ 0,
                    /* SrcObjAt  SPrm    */ 0,
                    /* SrcObjTg  Type    */ AT_TYPE_WIND,
                    /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
                    /* SrcObjCo  SPrm    */ 0,
                    /* SrcGObjAt Se      */ 0,
                    /* SrcGObjAt HitMark */ 0,
                    /* SrcGObjAt Spl     */ 0,
                    /* SrcGObjAt Mtrl    */ 0,
                    /* SrcGObjAt SPrm    */ 0,
                    /* SrcGObjTg Se      */ 0,
                    /* SrcGObjTg HitMark */ 0,
                    /* SrcGObjTg Spl     */ 0,
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
            a_this->mStts.Init(200, 0, a_this);
            a_this->mSph.Set(cc_sph_src);
            a_this->mSph.SetStts(&a_this->mStts);
        } else {
            return phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

static actor_method_class l_daFf_Method = {
    (process_method_func)daFf_Create,
    (process_method_func)daFf_Delete,
    (process_method_func)daFf_Execute,
    (process_method_func)daFf_IsDelete,
    (process_method_func)daFf_Draw,
};

actor_process_profile_definition g_profile_FF = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_FF,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(ff_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_FF,
    /* Actor SubMtd */ &l_daFf_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
