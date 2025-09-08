/**
 * d_a_bdkobj.cpp
 * Object - Helmaroc King fight objects (wooden bridges, wooden planks floating in water, etc.).
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bdkobj.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/res/res_bdkobj.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "SSystem/SComponent/c_lib.h"

static cXyz non_pos(10000.0f, -10000.0f, 20000.0f);

/* 000000EC-00000104       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
static void ride_call_back(dBgW* param1, fopAc_ac_c* param2, fopAc_ac_c* param3) {
    if (fopAcM_GetName(param3) != PROC_PLAYER) {
        return;
    }
    param2->health = 0xA;
}

/* 00000104-00000184       .text hahen_draw__FP12bdkobj_class */
static void hahen_draw(bdkobj_class* i_this) {
    bdo_eff_s* fragment = i_this->mEffs;
    for (s32 i = 0; i < 3; i++, fragment++) {
        if (fragment->m000 != 0) {
            if (fragment->mpModel != NULL) {
                J3DModel* model = fragment->mpModel;
                g_env_light.setLightTevColorType(model, &i_this->tevStr);
                mDoExt_modelUpdateDL(model);
            }
        }
    }
}

/* 00000184-000002C4       .text daBdkobj_Draw__FP12bdkobj_class */
static BOOL daBdkobj_Draw(bdkobj_class* i_this) {
    fopAc_ac_c* a_this = static_cast<fopAc_ac_c*>(i_this);
    J3DModel* model;
    if (i_this->model) {
        model = a_this->model;
        g_env_light.setLightTevColorType(model, &a_this->tevStr);
        
#if VERSION > VERSION_DEMO
        if (i_this->m298 < 2) {
            cXyz vec = (a_this->current.pos - dComIfGp_getCamera(0)->mLookat.mEye);
            if (vec.abs() > REG8_F(10) + 300.0f) {
                mDoExt_modelUpdateDL(model);
            }
        } else
#endif
        {
            mDoExt_modelUpdateDL(model);
        }
    }
    hahen_draw(i_this);
    return TRUE;
}

/* 00000300-00000C08       .text top_hahen_move__FP12bdkobj_classP9bdo_eff_s */
static void top_hahen_move(bdkobj_class* i_this, bdo_eff_s* i_eff) {
    bdkobj_class* pActor = static_cast<bdkobj_class*>(i_this);
    cXyz local_14c;
    cXyz cStack344;
    dBgS_GndChk gndChk;
    dBgS_LinChk linChk;

    i_eff->m014 = i_eff->m008;

    if (i_eff->m1A4 > 0.1f) {
        f32 dVar8 = i_eff->m1A4;
        f32 dVar9 = (1.0f - i_eff->m028) * 20.0f;
        if (i_eff->m1A4 > dVar9) {
            dVar8 = dVar9;
        }
        cMtx_YrotS(*calc_mtx, i_eff->m1A8);

        local_14c.set(0.0f, 0.0f, dVar8);

        MtxPosition(&local_14c, &cStack344);
        i_eff->m008 += cStack344;
        i_eff->m030.y += i_eff->m1AA;
    }
    cLib_addCalc0(&i_eff->m1A4, 1.0f, REG0_F(18) + 0.2f);
    cMtx_YrotS(*calc_mtx, i_eff->m030.y);

    local_14c.x = 0.0f;
    local_14c.y = i_eff->m024;
    local_14c.z = i_eff->m020;

    MtxPosition(&local_14c, &cStack344);
    i_eff->m008 += cStack344;
    i_eff->m024 -= 5.0f;

    cXyz* ccmove = i_eff->mStts.GetCCMoveP();
    if (ccmove != NULL) {
        i_eff->m008.x += ccmove->x;
        i_eff->m008.z += ccmove->z;
    }

    local_14c.set(i_eff->m008);
    local_14c.y += 200.0f;

    gndChk.SetPos(&local_14c);

    f32 fVar10 = dComIfG_Bgsp()->GroundCross(&gndChk) + ((REG0_F(3) + 50.0f) * i_eff->m028);
    if (i_eff->m008.y <= fVar10) {
        i_eff->m008.y = fVar10;
        if (i_eff->m024 < REG8_F(9) + -20.0f) {
            i_eff->m024 = i_eff->m024 * -(REG8_F(10) + 0.3f);
            i_eff->m030.y += (s16)cM_rndFX(8000.0f);
            i_eff->m02C = cM_rndFX(200.0f);
        } else {
            i_eff->m024 = 0.0f;
            cLib_addCalc0(&i_eff->m020, 1.0f, REG8_F(12) + 0.75f);
            i_eff->m036.z = 0;
            i_eff->m036.x = (s16)(i_eff->m020 * (REG8_F(8) + 300.0f));
            i_eff->m036.y = (s16)(i_eff->m020 * i_eff->m02C);
        }
    }
    local_14c = i_eff->m008 - i_eff->m014;
    local_14c.y = 0.0f;

    if (local_14c.abs() > 0.0f) {
        cMtx_YrotS(*calc_mtx, cM_atan2s(local_14c.x, local_14c.z));
        local_14c.x = 0.0f;
        local_14c.y = 30.0f;
        local_14c.z = i_eff->m028 * 70.0f;

        MtxPosition(&local_14c, &cStack344);
        local_14c.set(i_eff->m008);
        local_14c.y += 30.0f;

        cStack344 += i_eff->m008;

        linChk.Set(&local_14c, &cStack344, pActor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            i_eff->m008.x = i_eff->m014.x;
            i_eff->m008.z = i_eff->m014.z;
            i_eff->m020 = 0.0f;
        }
    }
    i_eff->m030 += i_eff->m036;
    MtxTrans(i_eff->m008.x, i_eff->m008.y, i_eff->m008.z, 0);
    cMtx_YrotM(*calc_mtx, i_eff->m030.y);
    cMtx_XrotM(*calc_mtx, i_eff->m030.x);
    cMtx_ZrotM(*calc_mtx, i_eff->m030.z);
    f32 scale = i_eff->m028;
    MtxScale(scale, scale, scale, TRUE);
    J3DModel* model = i_eff->mpModel;
    model->setBaseTRMtx(*calc_mtx);

    i_eff->mSph.SetC(i_eff->m008);
    i_eff->mSph.SetR((REG8_F(15) + 85.0f) * i_eff->m028);
    dComIfG_Ccsp()->Set(&i_eff->mSph);
    if (i_eff->mSph.ChkTgHit() != NULL && i_eff->m1A4 < 1.0f) {
        CcAtInfo hit_atInfo;
        hit_atInfo.mpObj = i_eff->mSph.GetTgHitObj();
        hit_atInfo.mpActor = at_power_check(&hit_atInfo);
        if (hit_atInfo.mResultingAttackType == 0x8) {
            i_eff->m1A4 = (REG14_F(4) + 15.0f + cM_rndF(1.0f)) * (1.0f - i_eff->m028);

            if (hit_atInfo.mpActor) {
                i_eff->m1A8 = hit_atInfo.mpActor->shape_angle.y + (s16)cM_rndFX(2000.0f);
            }
            i_eff->m1AA = cM_rndFX(400.0f);
        }
    }

    if (i_eff->m008.y < 8500.0f) {
        i_eff->m000 = 0;
    }
    return;
}

/* 00001214-00001640       .text kaidan_hahen_move__FP12bdkobj_classP9bdo_eff_s */
static void kaidan_hahen_move(bdkobj_class* i_this, bdo_eff_s* i_eff) {
    dBgS_ObjGndChk_Spl gndChk;
    cXyz local_78;

    i_eff->m030 += i_eff->m036;
    i_eff->m008.y += i_eff->m024;
    i_eff->m024 -= 3.0f;

    local_78.set(i_eff->m008);
    local_78.y += 5000.0f;

    gndChk.SetPos(&local_78);

    f32 fVal1 = dComIfG_Bgsp()->GroundCross(&gndChk);
    f32 fVal2 = 0.0f;
    if (fVal1 != -G_CM3D_F_INF) {
        if (i_eff->m008.y <= fVal1) {
            i_eff->m008.y = fVal1;
            i_eff->m024 = fVal2;
            cLib_addCalcAngleS2(&i_eff->m036.y, 0, 1, 10);
            cLib_addCalcAngleS2(&i_eff->m036.z, 0, 1, 10);

            fVal2 = cM_ssin(i_eff->m1AC * (REG0_S(7) + 1800));
            cLib_addCalcAngleS2(&i_eff->m030.x, (REG0_F(11) + 950.0f) * fVal2, 10, 400);

            fVal2 = cM_ssin(i_eff->m1AC * (REG0_S(6) + 2000)) * (5.0f + REG0_F(10));
        }
    } else {
        i_eff->m000 = 0;
    }

    MtxTrans(i_eff->m008.x, i_eff->m008.y + fVal2, i_eff->m008.z, 0);
    cMtx_YrotM(*calc_mtx, i_eff->m030.y);
    cMtx_XrotM(*calc_mtx, i_eff->m030.x);
    cMtx_ZrotM(*calc_mtx, i_eff->m030.z);

    f32 scale = i_eff->m028;
    MtxScale(scale, scale, scale, TRUE);
    J3DModel* model = i_eff->mpModel;
    model->setBaseTRMtx(*calc_mtx);

    return;
}

/* 000018E8-00001970       .text hahen_move__FP12bdkobj_class */
static void hahen_move(bdkobj_class* i_this) {
    bdo_eff_s* fragment = i_this->mEffs;
    for (s32 i = 0; i < 3; i++, fragment++) {
        if (fragment->m000 != 0) {
            fragment->m1AC++;
            if (fragment->m000 == 1) {
                top_hahen_move(i_this, fragment);
            } else {
                kaidan_hahen_move(i_this, fragment);
            }
        }
    }
}

/* 00001970-00001CF0       .text tower_kaidan_move__FP12bdkobj_class */
static void tower_kaidan_move(bdkobj_class* i_this) {
    if (i_this->pm_bgw != NULL) {
        if (i_this->health != 0) {
            i_this->health--;
        }
        if ((fopAcM_GetParam(i_this) & 0xf) == 0xf) {
            dComIfG_Bgsp()->Release(i_this->pm_bgw);
            i_this->pm_bgw = NULL;
            i_this->model = NULL;
            i_this->m299 = 100;

            dComIfGp_particle_set(dPa_name::ID_SCENE_8143, &i_this->current.pos, &i_this->current.angle);
            dComIfGp_particle_set(dPa_name::ID_SCENE_8144, &i_this->current.pos, &i_this->current.angle);
            dComIfGp_particle_set(dPa_name::ID_SCENE_8145, &i_this->current.pos, &i_this->current.angle);
            GXColor prim_col;
            prim_col.r = 0x46;
            prim_col.g = 0x3C;
            prim_col.b = 0x28;
            prim_col.a = 0xB4;
            i_this->m918.remove();
            i_this->m918.setColor(prim_col);
#if VERSION == VERSION_DEMO
            i_this->m938_demo =
#endif
                dComIfGp_particle_setToon(
                    dPa_name::ID_SCENE_A146, &i_this->current.pos, &i_this->current.angle, NULL, 0xB4, &i_this->m918, (s8)fopAcM_GetRoomNo(i_this)
                );
#if VERSION == VERSION_DEMO
            JPABaseEmitter* emitter = i_this->m938_demo;
#else
            JPABaseEmitter* emitter = i_this->m918.getEmitter();
#endif
            if (emitter != NULL) {
                emitter->becomeImmortalEmitter();
                i_this->m938 = 0xB4;
            }

            fopAcM_seStartCurrent(i_this, JA_SE_OBJ_MJ_WBOARD_BRK, 0);
            for (s32 i = 0; i < 2; i++) {
                i_this->mEffs[i].m000 = 2;
                i_this->mEffs[i].m1AC = cM_rndF(65536.0f);
                i_this->mEffs[i].m028 = (0.7f + cM_rndFX(0.25f));
                i_this->mEffs[i].m008.x = i_this->current.pos.x + cM_rndFX(500.0f);
                i_this->mEffs[i].m008.y = i_this->current.pos.y;
                i_this->mEffs[i].m008.z = i_this->current.pos.z + cM_rndFX(500.0f);
                i_this->mEffs[i].m030.y = cM_rndF(65536.0f);
                i_this->mEffs[i].m030.z = cM_rndF(65536.0f);
                i_this->mEffs[i].m036.y = cM_rndFX(800.0f);
                i_this->mEffs[i].m030.x = cM_rndFX(10000.0f);
                i_this->mEffs[i].m036.z = cM_rndFX(800.0f);
            }
            fopAcM_OffStatus(i_this, fopAcStts_CULL_e);
        }
    } else {
#if VERSION == VERSION_DEMO
        if (i_this->m938_demo != NULL) {
            if ((i_this->m299 <= 0x5A) && (i_this->m938 != 0)) {
                i_this->m938 -= 2;
            }

            i_this->m938_demo->setGlobalAlpha(i_this->m938);

            if (i_this->m299 == 1) {
                i_this->m938_demo->becomeInvalidEmitter();
            }
        }
#else
        if (i_this->m918.getEmitter() != NULL) {
            if ((i_this->m299 <= 0x5A) && (i_this->m938 != 0)) {
                i_this->m938 -= 2;
            }
            i_this->m918.getEmitter()->setGlobalAlpha(i_this->m938);
        }
#endif
    }
}

/* 00001CF0-00002274       .text daBdkobj_Execute__FP12bdkobj_class */
static BOOL daBdkobj_Execute(bdkobj_class* i_this) {
    /* Nonmatching */
    if (i_this->m298 == 2) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->current.pos, &i_this->tevStr);
        tower_kaidan_move(i_this);
    } else {
        g_env_light.settingTevStruct(TEV_TYPE_BG3, &i_this->current.pos, &i_this->tevStr);
    }

    if (i_this->m299 != 0) {
        i_this->m299--;
    }

    if (i_this->m298 == 2) {
        if (i_this->model != NULL) {
            MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, 0);
            cMtx_YrotM(*calc_mtx, i_this->current.angle.y);
            cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
            cMtx_ZrotM(*calc_mtx, i_this->current.angle.z);
            i_this->model->setBaseTRMtx(*calc_mtx);
            if (i_this->pm_bgw != NULL) {
                MTXCopy(*calc_mtx, i_this->mMtx);
                i_this->pm_bgw->Move();
            }
        }
    } else {
        if (i_this->model != NULL) {
            i_this->mCyl.SetC(i_this->current.pos);
            if (i_this->m298 == 0) {
                i_this->mCyl.SetH(REG6_F(0) + 100.0f);
                i_this->mCyl.SetR(REG6_F(1) + 100.0f);
            } else if (i_this->m298 == 1) {
                i_this->mCyl.SetH(REG6_F(2) + 900.0f);
                i_this->mCyl.SetR(REG6_F(3) + 100.0f);
            }

            if (i_this->mCyl.ChkTgHit()) {
                CcAtInfo hit_atInfo;
                hit_atInfo.mpObj = i_this->mCyl.GetTgHitObj();
                fopAc_ac_c* at = at_power_check(&hit_atInfo);
                if (at != NULL && hit_atInfo.mResultingAttackType == 0xB) {
                    i_this->eyePos = i_this->current.pos;

                    u16 uVar8;
                    u16 uVar6;
                    u16 uVar4;
                    if (i_this->m298 == 0) {
                        uVar8 = dPa_name::ID_SCENE_A13D;
                        uVar6 = dPa_name::ID_SCENE_813E;
                        uVar4 = dPa_name::ID_SCENE_813F;
                    } else {
                        uVar8 = dPa_name::ID_SCENE_A140;
                        uVar6 = dPa_name::ID_SCENE_8141;
                        uVar4 = dPa_name::ID_SCENE_8142;
                    }
                    static csXyz eff_ang = at->shape_angle;
                    eff_ang.z = 0;
                    eff_ang.x = 0;

                    i_this->m918.remove();
                    dComIfGp_particle_setToon(uVar8, &i_this->current.pos, &eff_ang, NULL, 0xB9, &i_this->m918, (s8)fopAcM_GetRoomNo(i_this));
                    dComIfGp_particle_set(
                        uVar6,
                        &i_this->current.pos,
                        &eff_ang,
                        NULL,
                        0xFF,
                        NULL,
                        (s8)fopAcM_GetRoomNo(i_this),
                        &i_this->tevStr.mColorK0,
                        &i_this->tevStr.mColorK0
                    );
                    dComIfGp_particle_set(
                        uVar4,
                        &i_this->current.pos,
                        &at->shape_angle,
                        NULL,
                        0xFF,
                        NULL,
                        (s8)fopAcM_GetRoomNo(i_this),
                        &i_this->tevStr.mColorK0,
                        &i_this->tevStr.mColorK0
                    );

                    i_this->model = NULL;
                    for (int i = 0; i < 3; i++) {
                        i_this->mEffs[i].m000 = 1;
                        i_this->mEffs[i].m028 = cM_rndFX(0.25f) + 0.7f;
                        i_this->mEffs[i].m008 = i_this->current.pos;
                        i_this->mEffs[i].m008.y += REG8_F(12) + 100.0f;
                        i_this->mEffs[i].m024 = REG8_F(16) + (cM_rndF(20.0f) + 60.0f);
                        i_this->mEffs[i].m030.y = at->shape_angle.y + (s16)cM_rndFX(10000.0f);
                        i_this->mEffs[i].m020 = REG8_F(14) + (cM_rndF(15.0f) + 20.0f);
                        i_this->mEffs[i].m036.x = cM_rndFX(6000.0f);
                        i_this->mEffs[i].m036.z = cM_rndFX(6000.0f);
                    }
                    fopAcM_OffStatus(i_this, fopAcStts_CULL_e);
                    return TRUE;
                }
            }
        } else {
            i_this->mCyl.SetC(non_pos);
        }

        if (i_this->model != NULL) {
            MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, 0);
            cMtx_YrotM(*calc_mtx, i_this->current.angle.y);
            cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
            cMtx_ZrotM(*calc_mtx, i_this->current.angle.z);
            i_this->model->setBaseTRMtx(*calc_mtx);
            dComIfG_Ccsp()->Set(&i_this->mCyl);
        }
    }
    hahen_move(i_this);
    return TRUE;
}

/* 00002274-0000227C       .text daBdkobj_IsDelete__FP12bdkobj_class */
static BOOL daBdkobj_IsDelete(bdkobj_class*) {
    return TRUE;
}

/* 0000227C-000022E8       .text daBdkobj_Delete__FP12bdkobj_class */
static BOOL daBdkobj_Delete(bdkobj_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Bdkobj");
    i_this->m918.remove();
    if (i_this->pm_bgw != NULL) {
        dComIfG_Bgsp()->Release(i_this->pm_bgw);
    }
    return TRUE;
}
static u16 bdl_data[] = {
    BDKOBJ_BDL_S_TBLOCK,
    BDKOBJ_BDL_S_TPOLE,
    BDKOBJ_BDL_S_TOWER_BRIDGE,
};
static u16 hahen_bdl_data[] = {
    BDKOBJ_BDL_SHAHENS,
    BDKOBJ_BDL_SHAHENL,
    BDKOBJ_BDL_GWOOD00,
};

/* 000022E8-000024C8       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    s32 iVar4;
    bdkobj_class* i_this = (bdkobj_class*)a_this;

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Bdkobj", bdl_data[i_this->m298]);
    i_this->model = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);

    if (a_this->model == NULL) {
        return FALSE;
    }
    iVar4 = 0;
    if (i_this->m298 == 2) {
        i_this->pm_bgw = new dBgW();

        JUT_ASSERT(DEMO_SELECT(781, 801), i_this->pm_bgw != NULL);
        cBgD_t* dzb = (cBgD_t*)dComIfG_getObjectRes("Bdkobj", BDKOBJ_DZB_S_TOWER_BRIDGE);
        if (i_this->pm_bgw->Set(dzb, cBgW::MOVE_BG_e, &i_this->mMtx) == TRUE) {
            return FALSE;
        }
        i_this->pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
        i_this->pm_bgw->SetRideCallback(ride_call_back);
        iVar4 = -1;
    }
    for (s32 i = 0; i < iVar4 + 3; i++) {
        J3DModelData* hahen_modelData = (J3DModelData*)dComIfG_getObjectRes("Bdkobj", hahen_bdl_data[i_this->m298]);
        i_this->mEffs[i].mpModel = mDoExt_J3DModel__create(hahen_modelData, 0x80000, 0x11000022);
        if (i_this->mEffs[i].mpModel == NULL) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 000024C8-000027B8       .text daBdkobj_Create__FP10fopAc_ac_c */
static cPhs_State daBdkobj_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl cc_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
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
            /* Height */ 450.0f,
        }},
    };
    static dCcD_SrcSph hahen_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
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

    bdkobj_class* i_this = (bdkobj_class*)a_this;
    fopAcM_SetupActor(a_this, bdkobj_class);

    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "Bdkobj");
    if (res == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    }
    if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    i_this->m918.setFollowOff();
    i_this->m298 = fopAcM_GetParam(i_this);
    if (i_this->m298 == 0xFF) {
        i_this->m298 = 0;
    }

    if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x5000)) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMin(i_this, -500.0f, -1500.0f, -500.0f);
    fopAcM_SetMax(i_this, 500.0f, 1500.0f, 500.0f);
    fopAcM_SetMtx(i_this, i_this->model->getBaseTRMtx());

    if (i_this->m298 == 2) {
        return (dComIfG_Bgsp()->Regist(i_this->pm_bgw, i_this) != 0) ? cPhs_ERROR_e : (cPhs_ERROR_e - 1);
    } else {
        i_this->mStts.Init(0xFF, 0xFF, a_this);
        i_this->mCyl.Set(cc_cyl_src);
        i_this->mCyl.SetStts(&i_this->mStts);
        if (i_this->m298 == 0) {
            i_this->mCyl.SetH(REG6_F(0) + 300.0f);
            i_this->mCyl.SetR(REG6_F(1) + 200.0f);
        } else {
            i_this->mCyl.SetH(REG6_F(2) + 300.0f);
            i_this->mCyl.SetR(REG6_F(3) + 200.0f);
        }

        for (s32 i = 0; i < 3; i++) {
            i_this->mEffs[i].mStts.Init(0xC8, 0xFF, a_this);
            i_this->mEffs[i].mSph.Set(hahen_sph_src);
            i_this->mEffs[i].mSph.SetStts(&i_this->mEffs[i].mStts);
        }
    }
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daBdkobj_Method = {
    (process_method_func)daBdkobj_Create,
    (process_method_func)daBdkobj_Delete,
    (process_method_func)daBdkobj_Execute,
    (process_method_func)daBdkobj_IsDelete,
    (process_method_func)daBdkobj_Draw,
};

actor_process_profile_definition g_profile_BDKOBJ = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BDKOBJ,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bdkobj_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BDKOBJ,
    /* Actor SubMtd */ &l_daBdkobj_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
