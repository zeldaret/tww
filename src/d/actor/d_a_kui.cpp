/**
 * d_a_kui.cpp
 * Object - Grappling Hook objects
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kui.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_btd.h"
#include "d/actor/d_a_dr2.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_rain.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/res/res_kui.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_executor.h"
#include "JSystem/JUtility/JUTReport.h"

class J3DModelData;

/* 00000078-000000C4       .text s_a_i_sub__FPvPv */
static void* s_a_i_sub(void* search, void*) {
    if (fopAcM_IsActor(search) && fopAcM_GetName(search) == PROC_DR2) {
        return search;
    }
    return NULL;
}

/* 000000C4-000000F0       .text search_dragontail__FP9kui_class */
static dr2_class* search_dragontail(kui_class* i_this) {
    return (dr2_class*)fpcM_Search(&s_a_i_sub, i_this);
}

/* 000000F0-0000013C       .text b_a_i_sub__FPvPv */
static void* b_a_i_sub(void* search, void*) {
    if (fopAcM_IsActor(search) && fopAcM_GetName(search) == PROC_BTD) {
        return search;
    }
    return NULL;
}

/* 0000013C-00000168       .text search_btd__FP9kui_class */
static btd_class* search_btd(kui_class* i_this) {
    return (btd_class*)fpcM_Search(&b_a_i_sub, i_this);
}

/* 00000168-0000037C       .text setEffectMtx__FP10fopAc_ac_cP12J3DModelDataf */
static void setEffectMtx(fopAc_ac_c* a_this, J3DModelData* modelData, float scale) {
    static Mtx mtx_adj = {
        0.5f, 0.0f, 0.0f, 0.5f,
        0.0f, -0.5f, 0.0f, 0.5f,
        0.0f, 0.0f, 1.0f, 0.0f,
    };
    cXyz& eyePos = a_this->eyePos;
    camera_class* camera = dCam_getCamera();

    cXyz look_dir = eyePos - camera->mLookat.mEye;

    cXyz light_dir;
    dKyr_get_vectle_calc(&a_this->tevStr.mLightPosWorld, &eyePos, &light_dir);

    cXyz refl;
    C_VECHalfAngle(&look_dir, &light_dir, &refl);
    Mtx reflMtx;
    C_MTXLookAt(reflMtx, &cXyz::Zero, &cXyz::BaseY, &refl);

    mDoMtx_stack_c::scaleS(scale, scale, 1.0f);
    mDoMtx_stack_c::concat(mtx_adj);
    mDoMtx_stack_c::concat(reflMtx);
    MtxP mtx = mDoMtx_stack_c::get();
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;

    Mtx now_copy;
    PSMTXCopy(mDoMtx_stack_c::get(), now_copy);

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* mat = modelData->getMaterialNodePointer(i);
        for (u32 j = 0; j < 8; j++) {
            J3DTexMtx* texMtx = mat->getTexMtx(j);
            if (texMtx != NULL) {
                switch (texMtx->getTexMtxInfo().mInfo) {
                    case 10:
                    case 11:
                        texMtx->getTexMtxInfo().setEffectMtx(now_copy);
                        break;
                }
            }
        }
    }
}

/* 0000037C-00000540       .text daKui_Draw__FP9kui_class */
static BOOL daKui_Draw(kui_class* i_this) {
    if (i_this->type == 3) {
        u32 light_type = 0;
        if (REG0_S(0) != 0) {
            light_type = 1;
        }

        i_this->eyePos = i_this->current.pos;
        i_this->eyePos.y += REG0_F(10);

        g_env_light.settingTevStruct(light_type, &i_this->eyePos, &i_this->tevStr);
        g_env_light.setLightTevColorType(i_this->mpModel2, &i_this->tevStr);
        g_env_light.setLightTevColorType(i_this->mpModel, &i_this->tevStr);

        setEffectMtx(i_this, i_this->mpModel2->getModelData(), REG0_F(11) + 1.0f);
        setEffectMtx(i_this, i_this->mpModel->getModelData(), REG0_F(12) + 1.0f);

        mDoExt_modelUpdateDL(i_this->mpModel2);
        mDoExt_modelUpdateDL(i_this->mpModel);
    } else if (i_this->type != 1) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
        g_env_light.setLightTevColorType(i_this->mpModel2, &i_this->tevStr);

        dComIfGd_setListBG();
        mDoExt_modelUpdateDL(i_this->mpModel2);
        dComIfGd_setList();

        if (i_this->mpModel) {
            g_env_light.setLightTevColorType(i_this->mpModel, &i_this->tevStr);
            mDoExt_modelUpdateDL(i_this->mpModel);
        }
    }
    return TRUE;
}

/* 00000540-00000920       .text demo_camera__FP9kui_class */
static void demo_camera(kui_class* i_this) {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    s8 bVar2 = true;

    switch ((s8)i_this->field_0x2E8) {
        case 0:
            break;
        case 1:
            if (!i_this->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(i_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                i_this->eventInfo.onCondition(dEvtCnd_UNK2_e);
                bVar2 = false;
                break;
            }
            i_this->field_0x2E8 = i_this->field_0x2E8 + 1;
            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(2);
            i_this->field_0x2EA = 0;
            // fallthrough
        case 2:
            i_this->current.pos.y = i_this->home.pos.y + i_this->field_0x30C;

            s32 uVar3 = (s32) i_this->field_0x2EA;
            if (uVar3 < 20) {
                f32 sin_result = cM_ssin((uVar3 & 0x1F) * 0x800);
                i_this->field_0x30C = sin_result * 5.0f;
            } else if (uVar3 <= 27) {
                if (uVar3 == 27) {
                    fopAcM_seStartCurrent(i_this, JA_SE_OBJ_ROPE_SW_ON, 0);
                    dComIfGp_getVibration().StartShock(3, -33, cXyz(0.0f, 1.0f, 0.0f));
                }
                cLib_addCalc2(&i_this->field_0x30C, -70.0f, 1.0f, 10.0f);
            } else if (uVar3 < 42) {
                f32 sin_result = cM_ssin(uVar3 * 0x3A00);
                i_this->field_0x30C = sin_result * 5.0f + (-70.0f);
            }

            i_this->field_0x2F8 = i_this->home.pos;
            i_this->field_0x2F8.y += REG8_F(0) + 200.0f;
            cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
        
            cXyz vec(REG8_F(1) + 800.f, REG8_F(2), REG8_F(3) + 100.0f);
            cXyz posVec;
            MtxPosition(&vec, &posVec);
        
            i_this->field_0x2EC = i_this->home.pos + posVec;
        
            if (i_this->field_0x2EA == 70) {
                i_this->field_0x2E8 = 0;
        
                camera->mCamera.Reset(i_this->field_0x2F8, i_this->field_0x2EC);
                camera->mCamera.Start();
                camera->mCamera.SetTrimSize(0);
        
                dComIfGp_event_reset();
        
                dComIfGs_onSwitch(i_this->mSwitchNo, fopAcM_GetRoomNo(i_this));
                mDoAud_seStart(JA_SE_READ_RIDDLE_1);
            }
            break;
    }

    if ((i_this->field_0x2E8 != 0) && bVar2) {
        camera->mCamera.Set(i_this->field_0x2F8, i_this->field_0x2EC);
        JUTReport(0x19a, 0x1ae, "K SUB  COUNT  %d", i_this->field_0x2EA);
        i_this->field_0x2EA++;
    }
}

/* 00000920-000012E4       .text daKui_Execute__FP9kui_class */
static BOOL daKui_Execute(kui_class* i_this) {
    fopAc_ac_c* actor = i_this;
    static s16 bure_xa_d[2] = {0x1000, 0xF000};

    cXyz temp2;
    cXyz temp;
    daPy_py_c* player;
    s16 target_x_angle;
    Mtx local_mtx;

    player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if (i_this->field_0x2A2 != 0) {
        dr2_class* dragon_tail = search_dragontail(i_this);
        btd_class* btd = search_btd(i_this);

        if (dragon_tail != NULL && btd != NULL) {
            if ((dragon_tail->unk_4BA == 0 || dragon_tail->unk_4BA >= 10) && btd->m02E4 < 10) {
                actor->current.pos = dragon_tail->unk_3B0;
                actor->current.angle = dragon_tail->actor.current.angle;
            } else {
                actor->current.pos.set(0.0f, -10000.0f, 0.0f);
            }
        } else {
            actor->current.pos.set(0.0f, -10000.0f, 0.0f);
        }
    }

    if (i_this->type == 3) {
        if (actor->health == 3) {
            temp2 = player->getLeftHandPos() - actor->home.pos;
            cMtx_YrotS(*calc_mtx, -player->shape_angle.y);

            MtxPosition(&temp2, &temp);
            temp.z *= REG0_F(1) + 1.0f;

            if (REG0_S(0) == 0) {
                target_x_angle = -cM_atan2s(temp.z, -temp.y);
            } else {
                target_x_angle = (s32) cM_atan2s(temp.z, -temp.y);
            }
            s16 unk = std::fabsf((REG0_F(2) + 3000.0f) * cM_ssin(actor->shape_angle.y));

            s8 unk_flag = 0;
            if (target_x_angle > unk) {
                target_x_angle = unk;
                unk_flag = 1;
            } else if (target_x_angle < (s16)-unk) {
                target_x_angle = -unk;
                unk_flag = 2;
            }

            if (unk_flag != 0 && unk > 2000) {
                if (i_this->field_0x2DC[unk_flag] == 0) {
                    i_this->field_0x2DC[unk_flag] = 0x50;
                    i_this->field_0x2DC[0] = REG0_S(3) + 40;

                    dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                    fopAcM_seStartCurrent(actor, JA_SE_OBJ_ST_CHIME, 0);

                    i_this->field_0x2E4 = *(s16*) (bure_xa_d + unk_flag - 1);
                    i_this->field_0x2E4 *= (s16) (REG17_S(4) + 1);
                    i_this->field_0x2E6 = REG17_S(5) + 0x400;
                }
            }

            if (REG0_S(1) == 0) {
                actor->shape_angle.y = -(actor->current.angle.y - player->shape_angle.y);
            } else {
                actor->shape_angle.y = actor->current.angle.y - player->shape_angle.y;
            }
        }
        else {
            target_x_angle = 0;
        }

        cLib_addCalcAngleS2(&actor->current.angle.x, target_x_angle, 4, REG0_S(1) + 0x200);
        if (i_this->field_0x2DC[1] != 0) {
            i_this->field_0x2DC[1]--;
        }
        if (i_this->field_0x2DC[2] != 0) {
            i_this->field_0x2DC[2]--;
        }

        s16 x = 0;
        s16 z = 0;
        f32 unk_f = 1.0f;

        if (i_this->field_0x2DC[0] != 0) {
            i_this->field_0x2DC[0]--;

            s32 iVar10 = (s32) i_this->field_0x2DC[0];
            f32 fVar1 = iVar10 * (REG0_F(16) + 40.0f);

            x = (s16) (fVar1 * cM_ssin(iVar10 * (REG0_S(4) + 0x1900)));
            z = (s16) (fVar1 * cM_scos(iVar10 * (REG0_S(5) + 0x2100)) * 0.25f);

            if ((iVar10 & 1) != 0) {
                unk_f = (iVar10 * (REG0_F(17) + 0.001f)) + 1.0f;
            }

            if (i_this->field_0x2DC[0] == 0 && actor->health == 3 && REG0_S(3) == 0) {
                dComIfGs_onSwitch(i_this->mSwitchNo, fopAcM_GetRoomNo(actor));
            }
        }

        cLib_addCalcAngleS2(&i_this->field_0x2E2, i_this->field_0x2E4, 4, i_this->field_0x2E6);
        cLib_addCalcAngleS2(&i_this->field_0x2E4, 0, 1, REG17_S(6) + 0x80);
        cLib_addCalcAngleS2(&i_this->field_0x2E6, REG17_S(7) + 0x100, 1, REG17_S(8) + 0x40);

        MtxTrans(actor->home.pos.x, actor->home.pos.y, actor->home.pos.z, FALSE);
        mDoMtx_YrotM(*calc_mtx, actor->current.angle.y);

        MtxPush();
        mDoMtx_YrotM(*calc_mtx, actor->shape_angle.y);
        mDoMtx_XrotM(*calc_mtx, x + i_this->field_0x2E2);
        mDoMtx_ZrotM(*calc_mtx, z);
        mDoMtx_YrotM(*calc_mtx, -actor->shape_angle.y);
        MtxScale(unk_f, unk_f, unk_f, TRUE);
        i_this->mpModel->setBaseTRMtx(*calc_mtx);


        MtxPull();
        mDoMtx_YrotM(*calc_mtx, actor->shape_angle.y + REG0_S(5));
        mDoMtx_XrotM(*calc_mtx, actor->current.angle.x + REG0_S(6));
        mDoMtx_YrotM(*calc_mtx, -(actor->shape_angle.y + REG0_S(5) + 0x4000));

        MtxScale(unk_f, 1.0, unk_f, TRUE);
        i_this->mpModel2->setBaseTRMtx(*calc_mtx);
        MtxTrans(0.0, REG0_F(6) + -850.0f, 0.0, TRUE);

        temp2.setall(0.0f);
        MtxPosition(&temp2, &actor->current.pos);

        MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, FALSE);
        mDoMtx_YrotM(*calc_mtx, actor->current.angle.y);
        MtxScale(actor->scale.x, actor->scale.y, actor->scale.z, TRUE);
        cMtx_copy(*calc_mtx, i_this->field_0x2A8);
        i_this->field_0x2D8->Move();
    } else {
        MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, FALSE);
        mDoMtx_YrotM(*calc_mtx, actor->current.angle.y);
        if (i_this->type == 2 || i_this->type == 4) {
            i_this->mpModel->setBaseTRMtx(*calc_mtx);
        }

        i_this->mpModel2->setBaseScale(actor->scale);
        i_this->mpModel2->setBaseTRMtx(*calc_mtx);
        if (i_this->field_0x2A2) {
            cMtx_scale(local_mtx, 4.0f, 4.0f, 4.0f);
        } else {
            cMtx_scale(local_mtx, actor->scale.x, actor->scale.y, actor->scale.z);
        }

        cMtx_concat(*calc_mtx, local_mtx, i_this->field_0x2A8);
        i_this->field_0x2D8->Move();
    }

    if (i_this->type == 2 || i_this->type == 4) {
        BOOL is_switch = dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo());

        if (!is_switch) {
            if (actor->health == 3 && i_this->field_0x308 == 0) {
                i_this->field_0x308 = 1000;
            }            
        } else {
            actor->current.pos.y = actor->home.pos.y - 70.0f;
        }

        if (i_this->field_0x308 != 0) {
            i_this->field_0x308--;

            s16 finished = REG8_S(3) + 970;
            if (i_this->field_0x308 == finished) {
                if (i_this->type == 2) {
                    i_this->field_0x2E8 = 1;
                } else {
                    fopAcM_seStartCurrent(actor, JA_SE_OBJ_ROPE_SW_ON, 0);
                    dComIfGs_onSwitch(i_this->mSwitchNo, fopAcM_GetRoomNo(actor));
                    mDoAud_seStart(JA_SE_READ_RIDDLE_1);
                }
            }
        }
        demo_camera(i_this);
    }

    actor->eyePos = actor->current.pos;
    return TRUE;
}

/* 000012E4-000012EC       .text daKui_IsDelete__FP9kui_class */
static BOOL daKui_IsDelete(kui_class*) {
    return TRUE;
}

/* 000012EC-00001340       .text daKui_Delete__FP9kui_class */
static BOOL daKui_Delete(kui_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Kui");
    dComIfG_Bgsp()->Release(i_this->field_0x2D8);
    return TRUE;
}

/* 00001340-00001664       .text daKui_CreateHeap__FP10fopAc_ac_c */
static BOOL daKui_CreateHeap(fopAc_ac_c* a_this) {
    kui_class* i_this = (kui_class*)a_this;
    J3DModelData* modelData;

    if (i_this->type == 3) {
        // Bell body
        modelData = (J3DModelData*)dComIfG_getObjectRes("Kui", KUI_BDL_HKANE1);
        JUT_ASSERT(0x353, modelData != NULL);

        i_this->mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (!i_this->mpModel) {
            return FALSE;
        }

        // Bell handle
        modelData = (J3DModelData*)dComIfG_getObjectRes("Kui", KUI_BDL_HKANE2);
        JUT_ASSERT(0x35F, modelData != NULL);

        i_this->mpModel2 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (!i_this->mpModel2) {
            return FALSE;
        }
    } else {
        // Rope
        modelData = (J3DModelData*)dComIfG_getObjectRes("Kui", KUI_BDL_OBI_ROPETAG);
        JUT_ASSERT(0x36B, modelData != NULL);

        i_this->mpModel2 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
        if (!i_this->mpModel2) {
            return FALSE;
        }

        if (i_this->type == 2 || i_this->type == 4) {
            // Rope swing attachment
            modelData = (J3DModelData*)dComIfG_getObjectRes("Kui", KUI_BDL_MROPESW);
            JUT_ASSERT(0x377, modelData != NULL);

            i_this->mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
            if (!i_this->mpModel) {
                return FALSE;
            }
        }
    }

    dBgW* bgw = new dBgW();
    i_this->field_0x2D8 = bgw;
    if (!i_this->field_0x2D8) {
        return FALSE;
    }

    cBgD_t* pData = (cBgD_t*)dComIfG_getObjectRes("Kui", KUI_DZB_OBI_ROPETAG);
    if (i_this->field_0x2D8->Set(pData, cBgW::MOVE_BG_e, &i_this->field_0x2A8) == true) {
        return FALSE;
    }

    i_this->field_0x2D8->SetCrrFunc(dBgS_MoveBGProc_Typical);

    return TRUE;
}

/* 00001664-000018C8       .text daKui_Create__FP10fopAc_ac_c */
static cPhs_State daKui_Create(fopAc_ac_c* a_this) {
    kui_class* i_this;
    cPhs_State result;

    fopAcM_SetupActor(a_this, kui_class);
    i_this = (kui_class*) a_this;

    result = dComIfG_resLoad(&i_this->mPhs, "Kui");
    if (result == cPhs_COMPLEATE_e) {
        if (fopAcM_GetParam(a_this) == -1) {
            return cPhs_ERROR_e;
        }

        i_this->type = fopAcM_GetParam(a_this) & 0xF;
        i_this->field_0x2A2 = fopAcM_GetParam(a_this) & 0xF0;
        i_this->field_0x2A1 = fopAcM_GetParam(a_this) >> 8;
        i_this->mSwitchNo = fopAcM_GetParam(a_this) >> 0x18;

        if (i_this->mSwitchNo == 0xFF) {
            i_this->mSwitchNo = 0;
        }
        if (i_this->type == 3) {
            i_this->field_0x2A1 = 4;
        }

        switch (i_this->field_0x2A1) {
            case 0:
                i_this->scale.x = 0.5f;
                i_this->scale.y = 0.5f;
                break;
            case 1:
                i_this->scale.x = 2.0f;
                i_this->scale.y = 2.0f;
                break;
            case 2:
                i_this->scale.z = 2.0f;
                break;
            case 3:
                i_this->scale.x = 0.5f;
                i_this->scale.y = 0.5f;
                i_this->scale.z = 2.0f;
                break;
            case 4:
                i_this->scale.setall(2.0f);
                break;
            case 5:
                i_this->scale.x = 4.0f;
                i_this->scale.y = REG0_F(2) + 2.0f;
                i_this->scale.z = 4.0f;
                break;
            case 0xff:
            default:
                break;
        }

        if (!fopAcM_entrySolidHeap(i_this, &daKui_CreateHeap, 0x29f4)) {
            return cPhs_ERROR_e;
        }

        if (dComIfG_Bgsp()->Regist(i_this->field_0x2D8, i_this)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(i_this, i_this->mpModel2->getBaseTRMtx());
        if (i_this->type >= 2) {
            fopAcM_SetMin(i_this, -200.0f, -1000.0f, -200.0f);
            fopAcM_SetMax(i_this, 200.0f, 2000.0f, 200.0f);
        } else {
            fopAcM_SetMin(i_this, -200.0f, -200.0f, -200.0f);
            fopAcM_SetMax(i_this, 200.0f, 200.0f, 200.0f);
        }
    }
    return result;
}

static actor_method_class l_daKui_Method = {
    (process_method_func)daKui_Create,
    (process_method_func)daKui_Delete,
    (process_method_func)daKui_Execute,
    (process_method_func)daKui_IsDelete,
    (process_method_func)daKui_Draw,
};

actor_process_profile_definition g_profile_KUI = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KUI,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kui_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KUI,
    /* Actor SubMtd */ &l_daKui_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
