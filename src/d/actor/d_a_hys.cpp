/**
 * d_a_hys.cpp
 * Object - Eye switch
 */

#include "d/actor/d_a_hys.h"
#include "d/res/res_hys.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

#include "weak_data_1811.h" // IWYU pragma: keep

const char* daHys_c::m_arcname[2] = {"Hys", "Hys"};

/* Model file indexes. */
const s16 daHys_c::m_bdlidx[2] = {HYS_BDL_HYS, HYS_BDL_HYS};
/* Texture animation file indexes. */
const s16 daHys_c::m_btpidx[2] = {HYS_BTP_HYS, HYS_BTP_HYS};
/* Collision mesh file indexes. */
const s16 daHys_c::m_dzbidx[2] = {HYS_DZB_HYS, HYS_DZB_HYS};
const u32 daHys_c::m_heapsize[2] = {0xA00, 0xA00};
const f32 daHys_c::m_tg_r[2] = {35.0f, 70.0f};

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
    },
};

/* 00000078-000000B8       .text Delete__7daHys_cFv */
BOOL daHys_c::Delete() {
    dComIfG_resDelete(&mPhs, m_arcname[mType]);
    return TRUE;
}

/* 000000B8-00000250       .text CreateHeap__7daHys_cFv */
BOOL daHys_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectRes(m_arcname[mType], m_bdlidx[mType]);
    JUT_ASSERT(0x106, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020022);
    if (mpModel == NULL) {
        return FALSE;
    }

    J3DAnmTexPattern* pbtp = (J3DAnmTexPattern *)dComIfG_getObjectRes(m_arcname[mType], m_btpidx[mType]);
    JUT_ASSERT(0x114, pbtp != NULL);

    if (!mBtpAnm.init(modelData, pbtp, FALSE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, FALSE, FALSE)) {
        return FALSE;
    }
    field_0x458 = 0;
    return TRUE;
}

cPhs_State daHys_c::_create() {
    fopAcM_SetupActor(this, daHys_c);

    mType = fopAcM_GetParam(this) >> 8;
    cPhs_State res = dComIfG_resLoad(&mPhs, m_arcname[mType]);
    if (res == cPhs_COMPLEATE_e) {
        res = MoveBGCreate(m_arcname[mType], m_dzbidx[mType], dBgS_MoveBGProc_TypicalRotY, m_heapsize[mType]);
        if (res == cPhs_ERROR_e) {
            return cPhs_ERROR_e;
        }
    }

    return res;
}

/* 00000250-00000368       .text Create__7daHys_cFv */
BOOL daHys_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -240.0f, -240.0f, -90.0f, 240.0f, 240.0f, 90.0f);

    mStts.Init(255, 255, this);
    mSph.Set(l_sph_src);
    mSph.SetStts(&mStts);
    mSph.SetR(m_tg_r[mType]);

    set_mtx();
    mSwitchNo = fopAcM_GetParam(this) & 0xFF;

    if (fopAcM_isSwitch(this, mSwitchNo)) {
        field_0x450 = 1;
        field_0x458 = 3;
    } else {
        field_0x450 = 0;
        field_0x458 = 0;
    }

    if (mType == 1) {
        scale.setall(2.0f);
    }

    return TRUE;
}

/* 00000368-000003F8       .text set_mtx__7daHys_cFv */
void daHys_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), mBgMtx);
}

/* 000003F8-000004A4       .text Execute__7daHys_cFPPA3_A4_f */
BOOL daHys_c::Execute(Mtx** mtx) {
    mode_proc_call();

    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mBgMtx);

    *mtx = &mBgMtx;
    return TRUE;
}

/* 000004A4-00000560       .text mode_proc_call__7daHys_cFv */
void daHys_c::mode_proc_call() {
    typedef void (daHys_c::*ModeFunc)();
    static const ModeFunc mode_proc[2] = {
        &daHys_c::mode_wait,
        &daHys_c::mode_sw_on,
    };

    (this->*mode_proc[field_0x450])();
    mSph.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mSph);
}

/* 00000560-00000600       .text mode_wait__7daHys_cFv */
void daHys_c::mode_wait() {
    if (mSph.ChkTgHit()) {
        cCcD_Obj* obj = mSph.GetTgHitObj();
        if (obj != NULL && (obj->ChkAtType(AT_TYPE_NORMAL_ARROW) ||
                            obj->ChkAtType(AT_TYPE_FIRE_ARROW) ||
                            obj->ChkAtType(AT_TYPE_ICE_ARROW) ||
                            obj->ChkAtType(AT_TYPE_LIGHT_ARROW))) {
            mSph.ClrTgHit();
            mode_sw_on_init();
            return;
        }
    }

    if (field_0x458 != 0) {
        field_0x458--;
    }
}

/* 00000600-00000690       .text mode_sw_on_init__7daHys_cFv */
void daHys_c::mode_sw_on_init() {
    fopAcM_onSwitch(this, mSwitchNo);
    field_0x450 = 1;
    fopAcM_seStart(this, JA_SE_OBJ_ARROW_SW_ON, 0);
}

/* 00000690-000006F8       .text mode_sw_on__7daHys_cFv */
void daHys_c::mode_sw_on() {
    if (!fopAcM_isSwitch(this, mSwitchNo)) {
        mode_wait_init();
    } else {
        if (field_0x458 < 3) {
            field_0x458++;
        }
    }
}

/* 000006F8-00000704       .text mode_wait_init__7daHys_cFv */
void daHys_c::mode_wait_init() {
    field_0x450 = 0;
}

/* 00000704-00000778       .text Draw__7daHys_cFv */
BOOL daHys_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mBtpAnm.entry(mpModel->getModelData(), field_0x458);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

/* 00000778-00000904       .text daHys_Create__FPv */
static cPhs_State daHys_Create(void* i_this) {
    return ((daHys_c*)i_this)->_create();
}

/* 00000BBC-00000BDC       .text daHys_Delete__FPv */
static BOOL daHys_Delete(void* i_this) {
    return ((daHys_c*)i_this)->MoveBGDelete();
}

/* 00000BDC-00000C08       .text daHys_Draw__FPv */
static BOOL daHys_Draw(void* i_this) {
    return ((daHys_c*)i_this)->MoveBGDraw();
}

// Fakematch to fix weak func order/.text section splitting of dBgS_MoveBgActor::Draw().
#pragma nosyminline off

/* 00000C08-00000C28       .text daHys_Execute__FPv */
static BOOL daHys_Execute(void* i_this) {
    return ((daHys_c*)i_this)->MoveBGExecute();
}

/* 00000C28-00000C30       .text daHys_IsDelete__FPv */
static BOOL daHys_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daHysMethodTable = {
    (process_method_func)daHys_Create,
    (process_method_func)daHys_Delete,
    (process_method_func)daHys_Execute,
    (process_method_func)daHys_IsDelete,
    (process_method_func)daHys_Draw,
};

actor_process_profile_definition g_profile_Hys = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Hys,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daHys_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Hys,
    /* Actor SubMtd */ &daHysMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
