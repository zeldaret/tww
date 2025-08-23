/**
 * d_a_ep.cpp
 * Object - Torches
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_ep.h"
#include "d/res/res_ep.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_a_obj.h"
#include "d/actor/d_a_player.h"
#include "d/d_s_play.h"
#include "d/d_bg_s_lin_chk.h"
#include "m_Do/m_Do_lib.h"

void daEp_ToFore(ep_class* i_this) {
}

void daEp_ToBack(ep_class* i_this) {
}

/* 00000078-00000158       .text ga_draw__FP8ep_class */
void ga_draw(ep_class* i_this) {
    ep_ga_s* ga = i_this->mEpGa;
    for (s32 i = 0; i < 2; i++, ga++) {
        if (ga->mbEnabled == 1) {
            MtxTrans(ga->mPos.x, ga->mPos.y, ga->mPos.z, false);
            cMtx_YrotM(*calc_mtx, ga->rotY);
            cMtx_XrotM(*calc_mtx, ga->rotX);
            MtxScale(ga->scaleXZ, ga->scaleXZ * ga->scaleY, ga->scaleXZ, true);
            MtxTrans(0.0f, -18.0f, 0.0f, true);
            ga->mpModel->setBaseTRMtx(*calc_mtx);
            mDoExt_modelUpdateDL(ga->mpModel);
        }
    }
}

/* 00000158-000001F8       .text ep_draw__FP8ep_class */
void ep_draw(ep_class* i_this) {
    GXColor color;
    color.r = 0xEB;
    color.g = 0x7D;
    color.b = 0x0;
    color.a = 0x0;
    dComIfGd_setAlphaModelColor(color);

    if (REG0_S(1) == 0) {
        dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_SPHERE, i_this->mAlphaModelMtx, i_this->mAlphaModelAlpha);
    } else {
        dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_TWO_SPHERES, i_this->mAlphaModelMtx, i_this->mAlphaModelAlpha);
    }
}

/* 000001F8-000002E0       .text daEp_Draw__FP8ep_class */
static BOOL daEp_Draw(ep_class* i_this) {
    if ((i_this->mType == 0) || (i_this->mType == 3)) {
        if (i_this->mbShouldDrawModel != 1) {
            dComIfGd_setListBG();
            g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->actor.current.pos, &i_this->actor.tevStr);
            g_env_light.setLightTevColorType(i_this->mpModel, &i_this->actor.tevStr);
            mDoExt_modelUpdateDL(i_this->mpModel);
            dComIfGd_setList();
        }

        if (i_this->mbHasGa != 0) {
            ga_draw(i_this);
        }
    }

    if (i_this->mbNoEp != 1) {
        ep_draw(i_this);
    }
    return TRUE;
}

/* 000002E0-00000344       .text ep_switch_event_end__FP8ep_class */
BOOL ep_switch_event_end(ep_class*) {
    BOOL ret = FALSE;
    if (dComIfGp_evmng_endCheck("SHOKUDAI_SWITCH")) {
        dComIfGp_event_reset();
        ret = TRUE;
    }
    return ret;
}

/* 00000344-000003E8       .text ep_switch_event_begin__FP8ep_class */
s32 ep_switch_event_begin(ep_class* i_this) {
    BOOL ret = FALSE;
    if (!i_this->actor.eventInfo.checkCommandDemoAccrpt()) {
        fopAcM_orderOtherEvent(&i_this->actor, "SHOKUDAI_SWITCH");
    } else {
        i_this->actor.eventInfo.onCondition(dEvtCnd_UNK2_e);
        ret = dComIfGp_evmng_getMyStaffId("SHOKUDAI");
        if (ret == -1) {
            ep_switch_event_end(i_this);
        }
    }
    return ret;
}

/* 000003E8-000004C4       .text ep_switch_event_move__FP8ep_class */
BOOL ep_switch_event_move(ep_class* i_this) {
    BOOL ret = FALSE;
    if (dComIfGp_evmng_getIsAddvance(i_this->m7E0)) {
        static char* actions[] = { "WAIT", "FIRE" };

        ret = dComIfGp_evmng_getMyActIdx(i_this->m7E0, actions, ARRAY_SIZE(actions), FALSE, 0);
        switch (ret) {
            case 1:
                mDoAud_seStart(JA_SE_OBJ_TORCH_IGNITION, &i_this->mPosTop);
                break;
            
            case 0:
            default:
                ret = FALSE;
                dComIfGp_evmng_cutEnd(i_this->m7E0);
                break;
        }
    }
    return ret;
}

/* 000004C4-00000B48       .text ga_move__FP8ep_class */
void ga_move(ep_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    ep_ga_s* ga = &i_this->mEpGa[0];
    cXyz sp88;
    cXyz sp7C;
    cXyz sp70;
    cXyz sp64;
    cXyz sp58;

    sp88.set(0.0f, 0.0f, 10.0f);
    sp58.set(10000.0f, 10000.0f, 10000.0f);

    player->getBokoFlamePos(&sp58);

    dBgS_LinChk linChk;

    for (s32 i = 0; i < 2; i++, ga++) {
        if (ga->mbEnabled != 0) {
            if (ga->m3B != 0) {
                ga->m3B--;
            } else {
                ga->m3B = cM_rndF(10.0f);
                ga->m1C.x = i_this->mPosTop.x + cM_rndFX(150.0f);
                ga->m1C.y = i_this->mPosTop.y + cM_rndFX(100.0f);
                ga->m1C.z = i_this->mPosTop.z + cM_rndFX(150.0f);

                if (i == 0) {
                    sp64 = sp58 - ga->mPos;

                    if (sp64.abs() < 300.0f) {
                        ga->m1C.x = sp58.x + cM_rndFX(100.0f);
                        ga->m1C.y = sp58.y + cM_rndFX(100.0f);
                        ga->m1C.z = sp58.z + cM_rndFX(100.0f);
                    }
                }

                if (i_this->m4D0 == 0) {
                    ga->m1C.y += 1000.0f;
                }

                if (std::fabsf(i_this->mPosTop.y - ga->mPos.y) > 500.0f) {
                    ga->mbEnabled = 2;
                } else {
                    ga->mbEnabled = 1;
                }
            }

            sp70 = ga->m1C - ga->mPos;

            cLib_addCalcAngleS2(&ga->rotY, cM_atan2s(sp70.x, sp70.z), 2, 0x1000);
            cLib_addCalcAngleS2(&ga->rotX, -cM_atan2s(sp70.y, std::sqrtf(sp70.x * sp70.x + sp70.z * sp70.z)), 2, 0x1000);
            
            cMtx_YrotS(*calc_mtx, ga->rotY);
            cMtx_XrotM(*calc_mtx, ga->rotX);

            MtxPosition(&sp88, &sp7C);

            ga->m10 = ga->mPos;
            ga->mPos += sp7C;

            if (i_this->m7D4 != 0) {
                cXyz sp4C;

                cMtx_YrotS(*calc_mtx, i_this->m7DC);
                sp4C.set(0.0f, 1.0f, i_this->m7D8 * (REG0_F(9) + 5.0f));
                MtxPosition(&sp4C, &sp7C);
                ga->mPos += sp7C;

                sp7C = ga->m10 + (ga->mPos - ga->m10) * 1.05f;

                linChk.Set(&ga->m10, &sp7C, &i_this->actor);
                if (dComIfG_Bgsp()->LineCross(&linChk)) {
                    ga->mPos = linChk.GetCross();
                }
            }
            ga->scaleY = cM_ssin(ga->m38);
            ga->m38 += 0x3E00;
        }
    }
}

/* 00000F80-0000173C       .text ep_move__FP8ep_class */
void ep_move(ep_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    cXyz pos;
    pos.set(i_this->mPosTop.x, i_this->mPosTop.y + -240.0f + 235.0f + 15.0f + REG6_F(0), i_this->mPosTop.z);

    switch (i_this->m4D0) {
        case 0:
            if (i_this->m508 != 0) {
                cLib_addCalc0(&i_this->mLightPower, 0.5f, 0.05000000074505806f);

                if (i_this->mSph1.ChkTgHit()) {
                    cCcD_Obj* hitObj = i_this->mSph1.GetTgHitObj();

                    if (hitObj == NULL || !hitObj->ChkAtType(0x600000)) {
                        if (i_this->m505 != 0xff) {
                            i_this->mTimers[3] = i_this->m505 * 10 + 1;
                        }
                        dComIfGs_onSwitch(i_this->m508 - 1, fopAcM_GetRoomNo(&i_this->actor));
                    }
                }

                if (dComIfGs_isSwitch(i_this->m508 - 1, fopAcM_GetRoomNo(&i_this->actor))) {
                    if (i_this->mType != 3) {
                        if (dComIfGp_evmng_existence("SHOKUDAI_SWITCH")) {
                            s32 begin = ep_switch_event_begin(i_this);
                            i_this->m7E0 = begin;
                            if (begin != 0) {
                                i_this->m508 = 0;
                                if (i_this->m7E0 != -1) {
                                    ep_switch_event_move(i_this);
                                }
                            }
                            break;
                        }
                    }
                    mDoAud_seStart(JA_SE_OBJ_TORCH_IGNITION, &i_this->mPosTop);
                    i_this->m508 = 0;
                }
            } else if (i_this->mType != 3 && i_this->m7E0 != -1) {
                if (ep_switch_event_move(i_this)) {
                    i_this->m4D0 = 3;
                    i_this->m4E0 = i_this->actor.scale.x;
                }
            } else {
                i_this->m4D0 = 3;
                i_this->m4E0 = i_this->actor.scale.x;
            }
            break;

        case 3:
            i_this->m4D0++;
        
        case 4:
            cLib_addCalc2(&i_this->mLightPower, i_this->m4E0, 0.5f, 0.2f);
            if (i_this->mType != 2) {
                if (i_this->m7D4 < (s16)(REG0_S(7) + 7)) {
                    dComIfGp_particle_setSimple(1, &pos);
                    if (i_this->m7D4 == 0 && i_this->mSph1.ChkTgHit()) {
                        cCcD_Obj* hitObj = i_this->mSph1.GetTgHitObj();

                        if (hitObj != NULL && hitObj->ChkAtType(0x600000)) {
                            fopAc_ac_c* ac = hitObj->GetAc();

                            if (fopAcM_GetName(ac) == PROC_BDK) {
                                i_this->m7DC = ac->shape_angle.y;
                            } else {
                                i_this->m7DC = player->shape_angle.y;
                            }
                            i_this->m7D4 = REG0_S(2) + 40;
                        }
                    }
                }

                pos.y += 20.0f;
                dComIfGp_particle_setSimple(0x4004, &pos);
            }

            if (i_this->mTimers[3] == 1 && (i_this->m507 == 0xFF || !dComIfGs_isSwitch(i_this->m507, fopAcM_GetRoomNo(&i_this->actor)))) {
                dComIfGs_offSwitch(i_this->mOnSwitchNo, fopAcM_GetRoomNo(&i_this->actor));
            }

            if (i_this->mOnSwitchNo != 0xFF && !dComIfGs_isSwitch(i_this->mOnSwitchNo, fopAcM_GetRoomNo(&i_this->actor))) {
                i_this->m4D0 = 0;
                if (i_this->mOnSwitchNo != 0xff) {
                    i_this->m508 = i_this->mOnSwitchNo + 1;
                }
                mDoAud_seStart(JA_SE_OBJ_TORCH_OFF, &i_this->mPosTop);
            } else {
                mDoAud_seStart(JA_SE_OBJ_TORCH_BURNING, &i_this->mPosTop);
            }

        default:
            if (i_this->mType != 3 && i_this->m7E0 != -1) {
                if (ep_switch_event_end(i_this)) {
                    i_this->m7E0 = -1;
                } else {
                    dComIfGp_evmng_cutEnd(i_this->m7E0);
                }
            }
            break;

        case 10:
            cLib_addCalc0(&i_this->mLightPower, 1.0f, 0.10000000149011612f);
            if (i_this->mLightPower < 0.05f) {
                if (i_this->mType == 0 || i_this->mType == 3) {
                    i_this->m4D0 = 0;
                    if (i_this->mOnSwitchNo != 0xFF) {
                        dComIfGs_offSwitch(i_this->mOnSwitchNo, fopAcM_GetRoomNo(&i_this->actor));
                        i_this->m508 = i_this->mOnSwitchNo + 1;
                    }
                } else {
                    fopAcM_delete(&i_this->actor);
                }
            }
            break;
    }

    i_this->mLight.mPos = i_this->mPosTop;
    i_this->mLight.mColor.r = 600;
    i_this->mLight.mColor.g = 400;
    i_this->mLight.mColor.b = 0x78;
    i_this->mLight.mPower = i_this->mLightPower * 150.0f;
    i_this->mLight.mFluctuation = 250.0f;
    i_this->actor.scale.y = i_this->mLightPower;

    if (i_this->actor.scale.y > 0.5f) {
        i_this->mSph1.OnAtSetBit();
    } else {
        i_this->mSph1.OffAtSetBit();
    }

    cXyz sp3C;
    sp3C.set(i_this->mPosTop.x, i_this->mPosTop.y + 30.0f, i_this->mPosTop.z);

    i_this->mSph1.SetC(sp3C);
    dComIfG_Ccsp()->Set(&i_this->mSph1);

    if (i_this->m7D4 != 0) {
        s16 tmp = REG0_S(2) + 40;
        if (i_this->m7D4 == tmp && i_this->mpEmitter == NULL) {
            pos.set(
                i_this->mPosTop.x,
                i_this->mPosTop.y + -240.0f + 235.0f + 8.0f + REG6_F(4),
                i_this->mPosTop.z
            );

            cXyz scale;
            scale.z = scale.y = scale.x = REG0_F(6) + 1.0f;
            i_this->mpEmitter = dComIfGp_particle_set(dPa_name::ID_COMMON_01EA, &pos, NULL, &scale);
        }

        if (i_this->mpEmitter != NULL) {
            cLib_addCalc2(&i_this->m7D8, (i_this->m7D4 > (s16)(REG0_S(3) + 10)) ? REG0_F(5) + 4.0f : 0.0f, 1.0f, REG0_F(8) + 0.5f);
            cMtx_YrotS(*calc_mtx, i_this->m7DC);

            cXyz sp24;
            cXyz sp18;
            sp24.set(0.0f, 1.0f, i_this->m7D8);
            MtxPosition(&sp24, &sp18);

            JGeometry::TVec3<f32> sp181;
            sp181.set(sp18);
            i_this->mpEmitter->setDirection(sp181);

            if (i_this->m7D4 == 1) {
                i_this->mpEmitter->becomeInvalidEmitter();
                i_this->mpEmitter = NULL;
            }
        }
        i_this->m7D4--;
    }
}

/* 0000173C-00001834       .text daEp_set_mtx__FP8ep_class */
void daEp_set_mtx(ep_class* i_this) {
    if ((i_this->mType == 0) || (i_this->mType == 3)) {
        MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, false);
        cMtx_YrotM(*calc_mtx, i_this->actor.current.angle.y);
        cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);
        cMtx_ZrotM(*calc_mtx, i_this->actor.current.angle.z);

        i_this->mpModel->setBaseTRMtx(*calc_mtx);

        cXyz sp08;
        sp08.x = sp08.z = 0.0f;
        sp08.y = REG0_F(0) + 140.0f;
        MtxPosition(&sp08, &i_this->mPosTop);
    } else {
        i_this->mPosTop = i_this->actor.current.pos;
    }
}

/* 00001834-00001E30       .text daEp_Execute__FP8ep_class */
static BOOL daEp_Execute(ep_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;

    i_this->mbNoEp = 0;
    i_this->mbShouldDrawModel = 0;

    if ((i_this->mType == 0) || (i_this->mType == 3)) {
        i_this->mCyl.SetC(a_this->current.pos);
        dComIfG_Ccsp()->Set(&i_this->mCyl);
        if (i_this->mCyl.ChkTgHit()) {
            daObj::HitSeStart(&a_this->current.pos, fopAcM_GetRoomNo(a_this), &i_this->mCyl, 11);
        }
        fopAcM_rollPlayerCrash(a_this, 35.0f, 0);

        mDoLib_clipper::changeFar(1000000.0f);
        i_this->mbShouldDrawModel  = fopAcM_checkCullingBox(i_this->mpModel->getBaseTRMtx(), -30.0f, 0.0f, -30.0f, 30.0f, 180.0f, 30.0f);
        mDoLib_clipper::resetFar();

        if (i_this->mbHasGa != 0) {
            ga_move(i_this);
        }
    }

    for (s32 i = 0; i < 3; i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }

    if ((i_this->mTimers[3] != 0) && (i_this->mTimers[3] < 10000)) {
        i_this->mTimers[3]--;
    }

    if (i_this->mTimers[0] == 0) {
        i_this->mTimers[0] = cM_rndF(REG0_F(2) + 5.0f) + REG0_F(3);
        i_this->mAlphaModelAlphaTarget = 8.0f + cM_rndF(REG0_F(6) + 4.0f) + REG0_F(7);
    }

    if (i_this->mTimers[1] == 0) {
        if (i_this->m7D4 != 0) {
            i_this->mTimers[1] = cM_rndF(5.0f);
            i_this->mAlphaModelScaleTarget = cM_rndF(0.2f) + 0.55f;
        } else {
            i_this->mTimers[1] = cM_rndF(6.0f) + 3.0f;
            i_this->mAlphaModelScaleTarget = cM_rndF(0.075f) + 0.75f;
        }
    }

    cLib_addCalc2(&i_this->mAlphaModelAlpha, i_this->mAlphaModelAlphaTarget, 1.0f, REG0_F(4) + 0.1f + 0.9f);
    cLib_addCalc2(&i_this->mAlphaModelScale, i_this->mAlphaModelScaleTarget, 0.4f, 0.04f);

    MtxTrans(i_this->mPosTop.x, i_this->mPosTop.y, i_this->mPosTop.z, false);

    cMtx_YrotM(*calc_mtx, i_this->mAlphaModelRotY);
    cMtx_XrotM(*calc_mtx, i_this->mAlphaModelRotX);

    f32 scale = i_this->mAlphaModelScale * i_this->mLightPower;
    MtxScale(scale, scale, scale, true);
    cMtx_copy(*calc_mtx, i_this->mAlphaModelMtx);

    mDoLib_clipper::changeFar(1000000.0f);
    i_this->mbNoEp = fopAcM_checkCullingBox(i_this->mAlphaModelMtx, -160.0f, -160.0f, -160.0f, 160.0f, 160.0f, 160.0f);
    mDoLib_clipper::resetFar();

    ep_move(i_this);

    i_this->mAlphaModelRotY += 0xd0;
    i_this->mAlphaModelRotX += 0x100;

    if (i_this->m4D0 > 0) {
        if (i_this->m4D0 < 10) {
            i_this->mGroundCheckTimer++;
            if ((i_this->mGroundCheckTimer & 0xF) == 0) {
                dBgS_ObjGndChk_Spl gndChk;

                cXyz sp08 = i_this->mPosTop;
                sp08.y += 200.0f;
                
                gndChk.SetPos(&sp08);
                
                f32 fVar6 = dComIfG_Bgsp()->GroundCross(&gndChk);
                if ((fVar6 != -G_CM3D_F_INF) && (i_this->mPosTop.y < fVar6)) {
                    i_this->m4D0 = 10;
                }
            }
        }
    }
    return TRUE;
}

/* 00002270-00002278       .text daEp_IsDelete__FP8ep_class */
static BOOL daEp_IsDelete(ep_class*) {
    return TRUE;
}

/* 00002278-000022D4       .text daEp_Delete__FP8ep_class */
static BOOL daEp_Delete(ep_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Ep");
    dKy_plight_cut(&i_this->mLight);
    mDoAud_seDeleteObject(&i_this->mPosTop);
    return TRUE;
}

/* 000022D4-00002518       .text daEp_CreateHeap__FP10fopAc_ac_c */
static BOOL daEp_CreateHeap(fopAc_ac_c* a_this) {
    ep_class* i_this = (ep_class*)a_this;
    J3DModelData* modelData;

    if (i_this->mbHasObm == 0) {
        modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Ep", EP_BDL_VKTSD));
    } else {
        modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Ep", EP_BDL_OBM_SHOKUDAI1));
    }
    JUT_ASSERT(DEMO_SELECT(996, 997), modelData != NULL);

#if VERSION == VERSION_DEMO
    i_this->mpModel = mDoExt_J3DModel__create(modelData, 0x0, 0x11020203);
#else
    i_this->mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
#endif
    if (i_this->mpModel == NULL) {
        return FALSE;
    }

    if (i_this->mbHasGa != 0) {
        modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Ep", EP_BDL_EP_GA));
        JUT_ASSERT(DEMO_SELECT(1007, 1010), modelData != NULL);
        
        for (s32 i = 0; i < 2; i++) {
#if VERSION == VERSION_DEMO
            i_this->mEpGa[i].mpModel = mDoExt_J3DModel__create(modelData, 0x0, 0x11020203);
#else
            i_this->mEpGa[i].mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
#endif
            if (i_this->mEpGa[i].mpModel == NULL) {
                return FALSE;
            }

            if (i == 0 || cM_rndF(1.0f) < 0.5f) {
                i_this->mEpGa[i].mbEnabled = true;
                i_this->mEpGa[i].mPos = a_this->current.pos;
                i_this->mEpGa[i].mPos.y += 140.0f;
                i_this->mEpGa[i].scaleXZ = cM_rndF(0.3f) + 0.3f;
                i_this->mEpGa[i].m38 = cM_rndF(30000.0f);
            }
        }
    }
    return TRUE;
}

/* 00002518-00002608       .text daEp_CreateInit__FP10fopAc_ac_c */
void daEp_CreateInit(fopAc_ac_c* a_this) {
    ep_class* i_this = (ep_class*)a_this;

    i_this->m4D0 = 0;
    i_this->m508 = 0;

    fopAcM_SetMtx(a_this, i_this->mAlphaModelMtx);
    fopAcM_SetMin(a_this, -160.0f, -160.0f, -160.0f);
    fopAcM_SetMax(a_this, 160.0f, 160.0f, 160.0f);
    i_this->mAlphaModelRotX = cM_rndF(32768.0f);
    i_this->mAlphaModelRotY = cM_rndF(32768.0f);
    a_this->attention_info.position.x = a_this->current.pos.x;
    a_this->attention_info.position.y = a_this->current.pos.y + 100.0f;
    a_this->attention_info.position.z = a_this->current.pos.z;
    a_this->eyePos.x = a_this->current.pos.x;
    a_this->eyePos.y = a_this->current.pos.y + 130.0f;
    a_this->eyePos.z = a_this->current.pos.z;

    daEp_set_mtx(i_this);

    i_this->mbNoEp = 0;
    i_this->mbShouldDrawModel = 0;
}

/* 00002608-00002840       .text daEp_Create__FP10fopAc_ac_c */
static cPhs_State daEp_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK20000,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_FIRE | AT_TYPE_UNK20000 | AT_TYPE_FIRE_ARROW | AT_TYPE_WIND | AT_TYPE_UNK400000,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };
    static dCcD_SrcCyl co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 35.0f,
            /* Height */ 120.0f,
        }},
    };

    ep_class* i_this = (ep_class*)a_this;

#if VERSION == VERSION_DEMO
    cPhs_State ret = dComIfG_resLoad(&i_this->mPhase, "Ep");
    if (ret == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(a_this, ep_class);
#else
    fopAcM_SetupActor(a_this, ep_class);
    cPhs_State ret = dComIfG_resLoad(&i_this->mPhase, "Ep");
    if (ret == cPhs_COMPLEATE_e) {
#endif
        i_this->mType = fopAcM_GetParam(a_this) & 0x3F;
        if (i_this->mType == 0x3F) {
            i_this->mType = 0;
        }

        i_this->mbHasGa = (fopAcM_GetParam(a_this) >> 6) & 1;
        i_this->mbHasObm = (fopAcM_GetParam(a_this) >> 7) & 1;
        i_this->m505 = fopAcM_GetParam(a_this) >> 8;
        i_this->m507 = fopAcM_GetParam(a_this) >> 0x10;
        i_this->mOnSwitchNo = fopAcM_GetParam(a_this) >> 0x18;

        i_this->mStts.Init(0xFF, 0xFF, a_this);
        i_this->mSph1.Set(sph_src);
        i_this->mSph1.SetStts(&i_this->mStts);

        if ((i_this->mType == 0) || (i_this->mType == 3)) {
            u32 maxHeapSize;
            if (i_this->mbHasObm == 0) {
                maxHeapSize = 0x4C0;
            } else {
                maxHeapSize = 0x4E0;
            }

            if (i_this->mbHasGa != 0) {
                maxHeapSize += 0x9A0;
            }
#if VERSION == VERSION_DEMO
            if (!fopAcM_entrySolidHeap(a_this, daEp_CreateHeap, 0x369C)) {
#else
            if (!fopAcM_entrySolidHeap(a_this, daEp_CreateHeap, maxHeapSize)) {
#endif
                return cPhs_ERROR_e;
            }

            i_this->mCyl.Set(co_cyl_src);
            i_this->mCyl.SetStts(&i_this->mStts);
            i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this), NULL, NULL);
            i_this->mAcchCir.SetWall(10.0f, 20.0f);
            i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        }

        daEp_CreateInit(a_this);

        if (i_this->mOnSwitchNo != 0xFF && !dComIfGs_isSwitch(i_this->mOnSwitchNo, fopAcM_GetRoomNo(a_this))) {
            i_this->m508 = i_this->mOnSwitchNo + 1;
        }

        i_this->mTimers[3] = 20000;
        dKy_plight_set(&i_this->mLight);
        i_this->mGroundCheckTimer = cM_rndF(255.0f);
    }
    
    i_this->m7E0 = -1;
    return ret;
}

ep_class::ep_class() {
    m860 = j3dDefaultLightInfo;
}

static actor_method_class l_daEp_Method = {
    (process_method_func)daEp_Create,
    (process_method_func)daEp_Delete,
    (process_method_func)daEp_Execute,
    (process_method_func)daEp_IsDelete,
    (process_method_func)daEp_Draw,
};

actor_process_profile_definition g_profile_EP = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_EP,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(ep_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_EP,
    /* Actor SubMtd */ &l_daEp_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
