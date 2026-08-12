/**
 * d_a_obj_hcbh.cpp
 * Object - Tower of the Gods - Pillar with Companion Statue's face on it.
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hcbh.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_particle_name.h"
#include "d/d_bg_w.h"
#include "d/d_vibration.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_name.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "SSystem/SComponent/c_math.h"
#include "res/Object/Hcbh.h"
#include <math.h>

namespace {
    const char l_arcname[] = "Hcbh";

    const dCcD_SrcCyl l_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_UNK8 | AT_TYPE_BOMB | AT_TYPE_SKULL_HAMMER | AT_TYPE_DARKNUT_SWORD,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 70.0f,
            /* Height */ 556.0f,
        }},
    };

    const dCcD_SrcSph l_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
            /* Radius */ 35.0f,
        }},
    };

    const Vec l_co_sph_offset[6] = {
        {0.0f, 157.0f, 0.0f},
        {0.0f, 227.0f, 0.0f},
        {0.0f, 297.0f, 0.0f},
        {0.0f, 367.0f, 0.0f},
        {0.0f, 437.0f, 0.0f},
        {0.0f, 507.0f, 0.0f},
    };
} // namespace

/* 00000078-000000D8       .text chk_appear__11daObjHcbh_cFv */
bool daObjHcbh_c::chk_appear() {
    int swSave = param_get_swSave();
    bool appear = TRUE;
    if (swSave != 0xFF) {
        appear = fopAcM_isSwitch(this, swSave) == 0;
    }
    return appear;
}

/* 000000D8-0000029C       .text set_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::set_mtx() {
    int i;
    f32 offset = 50.0f * JMASSin(mTiltX);
    mDoMtx_stack_c::transS(current.pos.x, mFallY, current.pos.z);
    mDoMtx_stack_c::YrotM(mFaceDirY);
    mDoMtx_stack_c::transM(0.0f, offset, 0.0f);
    mDoMtx_stack_c::XrotM(mTiltX);
    mDoMtx_stack_c::transM(0.0f, -offset, 0.0f);
    mDoMtx_stack_c::YrotM(-mFaceDirY);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    for (i = 0; i < 4; i++) {
        mDoMtx_stack_c::transS(mFacePos[i]);
        mDoMtx_stack_c::YrotM(mFaceAngY[i]);
        mDoMtx_stack_c::XrotM(mFaceAngX[i]);
        mDoMtx_stack_c::YrotM(-mFaceAngY[i]);
        mDoMtx_stack_c::XYZrotM(shape_angle);
        mpFaceModel[i]->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 0000029C-0000030C       .text init_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::init_mtx() {
    mpModel->setBaseScale(scale);
    for (int i = 0; i < 4; i++) {
        mpFaceModel[i]->setBaseScale(scale);
    }
    set_mtx();
}

/* 0000030C-00000330       .text solidHeapCB__11daObjHcbh_cFP10fopAc_ac_c */
BOOL daObjHcbh_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHcbh_c*)i_this)->create_heap();
}

/* 00000330-00000500       .text create_heap__11daObjHcbh_cFv */
bool daObjHcbh_c::create_heap() {
    bool ok = true;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_HCBH_BDL_HCBH2_e);
    if (modelData == NULL) {
        JUT_ASSERT(499, 0);
        ok = false;
    } else {
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        static s32 bdl_table[4] = {
            dRes_INDEX_HCBH_BDL_HCBH1A_e,
            dRes_INDEX_HCBH_BDL_HCBH1B_e,
            dRes_INDEX_HCBH_BDL_HCBH1C_e,
            dRes_INDEX_HCBH_BDL_HCBH1D_e,
        };
        for (int i = 0; i < 4; i++) {
            J3DModelData* faceData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, bdl_table[i]);
            if (faceData == NULL) {
                ok = false;
                break;
            }
            mpFaceModel[i] = mDoExt_J3DModel__create(faceData, 0x80000, 0x11000022);
        }
        mpBgW1 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_HCBH_DZB_HCBH2_e), cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx());
        mpBgW2 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_HCBH_DZB_HCBH1_e), cBgW::MOVE_BG_e, &mpFaceModel[0]->getBaseTRMtx());
        if (mpModel == NULL || mpFaceModel[0] == NULL || mpFaceModel[1] == NULL ||
            mpFaceModel[2] == NULL || mpFaceModel[3] == NULL || mpBgW1 == NULL || mpBgW2 == NULL)
        {
            ok = false;
        }
    }
    return ok;
}

/* 00000500-000005E8       .text setup_break_condition__11daObjHcbh_cFP10fopAc_ac_c */
void daObjHcbh_c::setup_break_condition(fopAc_ac_c* i_other) {
    if (i_other != NULL) {
        mFaceDirY = cM_atan2s(mCyl.GetC().x - i_other->current.pos.x, mCyl.GetC().z - i_other->current.pos.z);
        static s16 set_anglY[4] = {-0x8000, -0x4000, 0x4000, 0x0000};
        for (int i = 0; i < 4; i++) {
            mFaceAngY[i] = set_anglY[i];
            mFaceAngX[i] = 0;
            mFaceTimer[i] = 15.0f * std::fabsf(JMASSin((set_anglY[i] - mFaceDirY) >> 1));
        }
    }
}

/* 000005E8-00000724       .text checkCollision__11daObjHcbh_cFv */
void daObjHcbh_c::checkCollision() {
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj != NULL) {
            switch (hitObj->GetAtType()) {
            case AT_TYPE_BOMB:
                mBreakMode = 3;
                setup_break_condition(mCyl.GetTgHitAc());
                break;
            case AT_TYPE_SKULL_HAMMER:
                mBreakMode = 2;
                setup_break_condition(mCyl.GetTgHitAc());
                break;
            case AT_TYPE_UNK8: {
                fopAc_ac_c* hitAc = mCyl.GetTgHitAc();
                if (hitAc != NULL && fopAcM_GetProfName(hitAc) == fpcNm_TN_e) {
                    mBreakMode = 1;
                    setup_break_condition(mCyl.GetTgHitAc());
                }
                break;
            }
            case AT_TYPE_DARKNUT_SWORD:
                mBreakMode = 1;
                setup_break_condition(mCyl.GetTgHitAc());
                break;
            }
        }
        mCyl.ClrTgHit();
    }
}

/* 00000724-0000077C       .text co_hitCallback__11daObjHcbh_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjHcbh_c::co_hitCallback(fopAc_ac_c* i_actor, dCcD_GObjInf*, fopAc_ac_c* i_other, dCcD_GObjInf*) {
    daObjHcbh_c* i_this = (daObjHcbh_c*)i_actor;
    if (fopAc_IsActor(i_other) && fopAcM_GetProfName(i_other) == fpcNm_AM_e) {
        i_this->mBreakMode = 4;
    }
}

/* 0000077C-000008F8       .text particle_set__11daObjHcbh_cFv */
void daObjHcbh_c::particle_set() {
    csXyz angle(0, mFaceDirY, 0);
    dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBREAKSHAFTHAHEN00, &current.pos, NULL, NULL, 0xFF, NULL, -1, &tevStr.mColorK0);
    dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBREAKSHAFTHAHEN01, &current.pos, &angle, NULL, 0xFF, NULL, -1, &tevStr.mColorK0);
    if (mBreakMode != 3) {
        dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBREAKSHAFTHIT00, &current.pos, &angle, NULL, 0xFF, NULL, -1, &tevStr.mColorK0);
    }
    mSmokeCallback.remove();
    dComIfGp_particle_setToon(dPa_name::ID_AK_ST_SIRENBREAKSHAFTSMOKE00, &current.pos, &angle, NULL, 0xA0, &mSmokeCallback, -1, &tevStr.mColorK0);
}

/* 000008F8-000009E4       .text make_item__11daObjHcbh_cFv */
void daObjHcbh_c::make_item() {
    int itemNo = param_get_itemNo();
    int itemSaveBitNo = param_get_itemSaveBitNo();
    cXyz pos = current.pos;
    csXyz angle(0, 0, 0);
    pos.y -= 30.0f;
    fopAcM_createItemFromTable(&pos, itemNo, itemSaveBitNo, home.roomNo, 0, &angle, 1, NULL);
    param_on_swSave();
}

/* 00000A20-00000E30       .text _create__11daObjHcbh_cFv */
cPhs_State daObjHcbh_c::_create() {
    cPhs_State phase = cPhs_ERROR_e;
    fopAcM_ct(this, daObjHcbh_c);
    if (fpcM_IsFirstCreating(this)) {
        mFallY = current.pos.y;
        mTiltX = 0;
        for (int i = 0; i < 4; i++) {
            mFacePos[i] = current.pos;
            mFaceAngX[i] = 0;
            mFaceAngY[i] = 0;
        }
        mAppear = chk_appear();
    }
    if (mAppear == 1) {
        phase = dComIfG_resLoad(&mPhs, l_arcname);
    }
    if (phase == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x2D00)) {
            if (dComIfG_Bgsp()->Regist(mpBgW1, this)) {
                phase = cPhs_ERROR_e;
            } else if (dComIfG_Bgsp()->Regist(mpBgW2, this)) {
                phase = cPhs_ERROR_e;
            } else {
            cullMtx = mpModel->getBaseTRMtx();
            init_mtx();
            mAcchCir.SetWall(589.0f, 70.0f);
            mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, &current.angle, &shape_angle);
            mAcch.ClrWaterNone();
            mAcch.ClrRoofNone();
            mAcch.SetRoofCrrHeight(589.0f);
            mAcch.CrrPos(*dComIfG_Bgsp());
            mAcch.ClrGroundLanding();
            mStts.Init(0xFF, 0xFF, this);
            mCyl.Set(l_cyl_src);
            mCyl.SetStts(&mStts);
            mCyl.SetC(current.pos);
            mCyl.SetCoHitCallback(co_hitCallback);
            for (int i = 0; i < 6; i++) {
                mSph[i].Set(l_sph_src);
                mSph[i].SetStts(&mStts);
                mSph[i].SetR(70.0f);
                cXyz pos(current.pos.x, current.pos.y + l_co_sph_offset[i].y, current.pos.z);
                mSph[i].SetC(pos);
            }
            mSmokeCallback.setTevStr(&tevStr);
            mSmokeCallback.setRateOff(0);
            mSmokeCallback.setFollowOff();
            mActProc = &daObjHcbh_c::wait_act_proc;
            fopAcM_setCullSizeBox(this, -40.0f, 0.0f, -40.0f, 100.0f, 589.0f, 100.0f);
        }
        } else {
            phase = cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 000011F4-000012F4       .text _delete__11daObjHcbh_cFv */
bool daObjHcbh_c::_delete() {
    if (mAppear == 1) {
        dComIfG_resDelete(&mPhs, l_arcname);
        if (heap != NULL) {
            if (mpBgW1 != NULL) {
                if (mpBgW1->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mpBgW1);
                }
                mpBgW1 = NULL;
            }
            if (mpBgW2 != NULL) {
                if (mpBgW2->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mpBgW2);
                }
                mpBgW2 = NULL;
            }
        }
        mSmokeCallback.remove();
    }
    return TRUE;
}

/* 000012F4-000013BC       .text wait_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::wait_act_proc() {
    checkCollision();
    if (mBreakMode == 0) {
        dComIfG_Ccsp()->Set(&mCyl);
    } else {
        particle_set();
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_TN_COLUMN_BREAK, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
        mCyl.SetCoHitCallback(NULL);
        mActProc = &daObjHcbh_c::fall_act_proc;
    }
}

/* 000013BC-000017D8       .text fall_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::fall_act_proc() {
    if (mTiltX < 0) {
        mTiltX = -0x8000;
        mTiltSpeed = 0;
    } else {
        if (mTiltX > 0x2000) {
            if (mpBgW1 != NULL && mpBgW1->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW1);
            }
            if (mpBgW2 != NULL && mpBgW2->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW2);
            }
        }
        mTiltSpeed += (s32)(4.0f + 127.0f * JMASSin(mTiltX));
    }
    if (mFallY < -10.0f + home.pos.y) {
        make_item();
        dComIfGp_getVibration().StartShock(8, -0x11, cXyz(0.0f, 1.0f, 0.0f));
        JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_TN_COLUMN_SMASH, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
        fopAcM_delete(this);
    } else {
        mFallSpeed += -0.011f;
        f32 offset = 50.0f * JMASSin(mTiltX);
        mDoMtx_stack_c::transS(current.pos.x, mFallY, current.pos.z);
        mDoMtx_stack_c::YrotM(mFaceDirY);
        mDoMtx_stack_c::transM(0.0f, offset, 0.0f);
        mDoMtx_stack_c::XrotM(mTiltX);
        mDoMtx_stack_c::transM(0.0f, -offset, 0.0f);
        mDoMtx_stack_c::YrotM(-mFaceDirY);
        mDoMtx_stack_c::XYZrotM(shape_angle);
        for (int i = 0; i < 6; i++) {
            cXyz pos = l_co_sph_offset[i];
            mDoMtx_multVec(mDoMtx_stack_c::get(), &pos, &pos);
            mSph[i].MoveCAt(pos);
            dComIfG_Ccsp()->Set(&mSph[i]);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (mFaceTimer[i] > 0) {
            mFaceTimer[i]--;
        } else {
            mFaceFallSpeed[i] += -0.01f;
            mFacePos[i].y += mFaceFallSpeed[i];
            if (mFacePos[i].y < -100.0f + home.pos.y) {
                mFacePos[i].y = -100.0f + home.pos.y;
            }
            mFaceRotSpeed[i] += (s32)(4.0f + 512.0f * JMASSin(mFaceAngX[i]));
            mFaceAngX[i] += mFaceRotSpeed[i];
            if (mFaceAngX[i] > 0x4000) {
                mFaceAngX[i] = 0x4000;
            }
        }
    }
}

/* 000017D8-000018D8       .text _execute__11daObjHcbh_cFv */
bool daObjHcbh_c::_execute() {
    set_mtx();
    mStts.Move();
    mAcch.CrrPos(*dComIfG_Bgsp());
    if (mpBgW1 != NULL && mpBgW1->ChkUsed()) {
        mpBgW1->Move();
    }
    if (mpBgW2 != NULL && mpBgW2->ChkUsed()) {
        mpBgW2->Move();
    }
    mFallY += mFallSpeed;
    mTiltX += mTiltSpeed;
    if (mTiltX >= 0x4000) {
        mTiltX = 0x4000;
    }
    (this->*mActProc)();
    return TRUE;
}

/* 000018D8-0000197C       .text _draw__11daObjHcbh_cFv */
bool daObjHcbh_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    for (int i = 0; i < 4; i++) {
        g_env_light.setLightTevColorType(mpFaceModel[i], &tevStr);
        mDoExt_modelUpdateDL(mpFaceModel[i]);
    }
    return TRUE;
}

/* 0000197C-0000199C       .text daObjHcbh_Create__FP10fopAc_ac_c */
static cPhs_State daObjHcbh_Create(fopAc_ac_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_create();
}

/* 0000199C-000019C0       .text daObjHcbh_Delete__FP11daObjHcbh_c */
static BOOL daObjHcbh_Delete(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_delete();
}

/* 000019C0-000019E4       .text daObjHcbh_Execute__FP11daObjHcbh_c */
static BOOL daObjHcbh_Execute(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_execute();
}

/* 000019E4-00001A08       .text daObjHcbh_Draw__FP11daObjHcbh_c */
static BOOL daObjHcbh_Draw(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_draw();
}

/* 00001A08-00001A10       .text daObjHcbh_IsDelete__FP11daObjHcbh_c */
static BOOL daObjHcbh_IsDelete(daObjHcbh_c*) {
    return TRUE;
}

static actor_method_class l_daObjHcbh_Method = {
    (process_method_func)daObjHcbh_Create,
    (process_method_func)daObjHcbh_Delete,
    (process_method_func)daObjHcbh_Execute,
    (process_method_func)daObjHcbh_IsDelete,
    (process_method_func)daObjHcbh_Draw,
};

actor_process_profile_definition g_profile_Obj_Hcbh = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Hcbh_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHcbh_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Hcbh_e,
    /* Actor SubMtd */ &l_daObjHcbh_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
