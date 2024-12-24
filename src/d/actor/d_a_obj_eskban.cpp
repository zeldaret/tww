//
// Generated by dtk
// Translation Unit: d_a_obj_eskban.cpp
//

#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_obj_eskban.h"
#include "d/res/res_eskban.h"
#include "f_op/f_op_actor_mng.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

namespace daObjEskban {
Mtx Act_c::M_tmp_mtx;
const char Act_c::M_arcname[7] = "Eskban";
const char Act_c::M_evname[7] = "Eskban";

}  // namespace daObjEskban

static dCcD_SrcCyl cyl_check_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_BOMB,
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
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 200.0f,
        /* Height */ 600.0f,
    }},
};
static dCcD_SrcCyl cyl_camera_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsOther_e | cCcD_CoSPrm_NoCrr_e,
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
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 1000.0f,
        /* Height */ 100.0f,
    }},
};
static dCcD_SrcSph sph_check_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_BOMB,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsEnemy_e |
            cCcD_CoSPrm_NoCrr_e,
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
        /* Radius */ 300.0f,
    }},
};

/* 000000EC-000001FC       .text CreateHeap__Q211daObjEskban5Act_cFv */
int daObjEskban::Act_c::CreateHeap() {
    J3DModelData* model_data =
        static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, ESKBAN_BDL_ESKBAN));
    JUT_ASSERT(261, model_data != NULL);
    mpModel = mDoExt_J3DModel__create(model_data, 0, 0x11020203U);
    M_smoke = new dPa_smokeEcallBack();
    JUT_ASSERT(264, M_smoke != NULL);
    return mpModel != NULL;
}

/* 000001FC-00000368       .text Create__Q211daObjEskban5Act_cFv */
int daObjEskban::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeBox(this, -500, -1, -500, 500, 500, 500);
    mCheckStts.Init(0xff, 0xff, this);
    mCheckCyl.Set(cyl_check_src);
    mCheckCyl.SetC(this->current.pos);
    mCheckCyl.SetStts(&mCheckStts);

    mCameraStts.Init(0xff, 0xff, this);
    mCameraCyl.Set(cyl_camera_src);
    cXyz offset(300, 450, 300);
    mCameraCyl.SetC(this->current.pos + offset);
    mCameraCyl.SetStts(&mCameraStts);

    mCheckSphStts.Init(0xff, 0xff, this);
    mCheckSph.Set(sph_check_src);
    offset.set(0, 400, 0);
    mCheckSph.SetC(this->current.pos + offset);
    mCheckSph.SetStts(&mCheckSphStts);

    mActorState = 0;
    mRemainingSmokeAnm = 0;
    mIsVisible = 1;
    return TRUE;
}

/* 000003A4-000004D0       .text Mthd_Create__Q211daObjEskban5Act_cFv */
s32 daObjEskban::Act_c::Mthd_Create() {
    s32 phase_state;
    fopAcM_SetupActor(this, Act_c);
    M_smoke = NULL;

    s32 swSave = param_get_swSave();
    if (fopAcM_isSwitch(this, swSave)) {
        return cPhs_STOP_e;
    }
    phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, ESKBAN_DZB_ESKBAN, NULL, 0x1020);
        JUT_ASSERT(336, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

daObjEskban::Act_c::Act_c() {}

/* 000009C0-00000A10       .text Delete__Q211daObjEskban5Act_cFv */
BOOL daObjEskban::Act_c::Delete() {
    if (M_smoke) {
        M_smoke->end();
        M_smoke = NULL;
    }
    return TRUE;
}

/* 00000A10-00000A68       .text Mthd_Delete__Q211daObjEskban5Act_cFv */
BOOL daObjEskban::Act_c::Mthd_Delete() {
    s32 result = MoveBGDelete();
    if (fpcM_CreateResult(this) != cPhs_STOP_e) {
        dComIfG_resDelete(&mPhs, M_arcname);
    }
    return result;
}

/* 00000A68-00000B00       .text set_mtx__Q211daObjEskban5Act_cFv */
void daObjEskban::Act_c::set_mtx() {
    this->shape_angle = this->current.angle;
    mDoMtx_stack_c::transS(this->current.pos);
    mDoMtx_stack_c::ZXYrotM(this->shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000B00-00000B3C       .text init_mtx__Q211daObjEskban5Act_cFv */
void daObjEskban::Act_c::init_mtx() {
    mpModel->setBaseScale(this->scale);
    set_mtx();
}

/* 00000B3C-00000C80       .text eff_m_break__Q211daObjEskban5Act_cFUsUs */
void daObjEskban::Act_c::eff_m_break(u16 particleID, u16 prm_b) {
    J3DModelData* mdlData =
        static_cast<J3DModelData*>(dComIfG_getObjectRes("Always", ALWAYS_BDL_MPI_KOISHI));
    J3DAnmTexPattern* txPattern =
        static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Always", ALWAYS_BTP_MPI_KOISHI));

    cXyz scale(3.0f, 3.0f, 3.0f);
    JPABaseEmitter* pBEmtr = dComIfGp_particle_set(
        particleID, &this->current.pos, &this->shape_angle, NULL,
        0xff, NULL, -1, NULL, NULL, &scale
    );
    if (!pBEmtr) {
        return;
    }
    pBEmtr->setGlobalRTMatrix(mpModel->getBaseTRMtx());
    dPa_J3DmodelEmitter_c* pMdlEmtr = new dPa_J3DmodelEmitter_c(pBEmtr, mdlData, tevStr, txPattern, prm_b, 0);
    if (!pMdlEmtr) {
        return;
    }
    dComIfGp_particle_addModelEmitter(pMdlEmtr);
}

/* 00000C80-00000D44       .text eff_b_break__Q211daObjEskban5Act_cFUs */
void daObjEskban::Act_c::eff_b_break(u16 particleID) {
    GXColor c0;
    c0.r = tevStr.mColorC0.r;
    c0.g = tevStr.mColorC0.g;
    c0.b = tevStr.mColorC0.b;
    c0.a = tevStr.mColorC0.a;

    cXyz scale(1.0f, 1.0f, 1.0f);
    JPABaseEmitter* pBEmtr = dComIfGp_particle_set(
        particleID, &this->current.pos, NULL, NULL,
        0xff, NULL, -1, &tevStr.mColorK0, &c0, &scale
    );
    if (!pBEmtr) {
        return;
    }
    pBEmtr->setGlobalRTMatrix(mpModel->getBaseTRMtx());
}

/* 00000D44-00000EF0       .text daObjEskban_effect_set__Q211daObjEskban5Act_cFv */
void daObjEskban::Act_c::daObjEskban_effect_set() {
    eff_m_break(0x82b1, 2);
    eff_b_break(0x82b2);

    static cXyz offset_vec(0, 250, 0);
    mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());
    mDoMtx_stack_c::multVec(&offset_vec, &mSmokePos);
    if (!M_smoke) {
        return;
    }
    JPABaseEmitter* pBEmtr = dComIfGp_particle_setToon(0x2027, &mSmokePos, NULL, NULL, 0xc8,
                                                       M_smoke, -1, NULL, NULL, NULL);
    if (!pBEmtr) {
        return;
    }

    pBEmtr->setRate(30);
    pBEmtr->setMaxFrame(1);
    static JGeometry::TVec3<f32> d_scale(3, 3, 3);
    static JGeometry::TVec3<f32> p_scale(7, 7, 7);
    pBEmtr->setGlobalDynamicsScale(d_scale);
    pBEmtr->setGlobalParticleScale(p_scale);
}

/* 00000EF0-00001400       .text Execute__Q211daObjEskban5Act_cFPPA3_A4_f */
int daObjEskban::Act_c::Execute(Mtx** pMtx) {
    dComIfG_Ccsp()->Set(&mCheckCyl);
    dComIfG_Ccsp()->Set(&mCameraCyl);
    dComIfG_Ccsp()->Set(&mCheckSph);
    if (mCheckSph.ChkCoHit()) {
        cCcD_Obj* hitObj = mCheckSph.GetCoHitObj();
        if (hitObj) {
            fopAc_ac_c* hitAct = hitObj->GetAc();
            if (hitAct && fopAcM_GetName(hitAct) == PROC_NPC_MD) {
                cXyz dist = fopAcM_GetPosition(hitAct) - fopAcM_GetPosition(this);
                dist.y = 0;
                if (dist.normalizeRS()) {
                    dist *= 10;
                } else {
                    dist.set(10, 0, 0);
                }
                hitAct->current.pos += dist;
            }
        }
    }
    switch (mActorState) {
    case ST_WAIT: /* 0x148 */ {
        if (!mCameraCyl.ChkCoHit()) {
            break;
        }
        cCcD_Obj* hitObj;
        hitObj = mCameraCyl.GetCoHitObj();
        if (!hitObj) {
            break;
        }
        fopAc_ac_c* hitAct = hitObj->GetAc();
        if (hitAct && fopAcM_GetName(hitAct) == PROC_Bomb2) {
            mActorID = fopAcM_GetID(hitAct);
            fopAcM_orderOtherEvent(this, "Eskban");
            mActorState = ST_DESTROYED;
        }
        break;
    }
    case ST_DESTROYED: /* 0x1d8 */
        if (eventInfo.checkCommandDemoAccrpt()) {
            mActorState = ST_CUTSCENING;
            break;
        }
        fopAcM_orderOtherEvent(this, "Eskban");
        break;
    case ST_CUTSCENING: /* 0x214 */ {
        if (fopAcM_SearchByID(mActorID) == NULL) {
            mActorState = ST_SMOKING;
            mRemainingSmokeAnm = DESTROY_SMOKE_ANM_LEN;
        }
        if (!mCheckCyl.ChkTgHit()) {
            break;
        }
        int staffID = dComIfGp_evmng_getMyStaffId("Eskban");
        dComIfGp_evmng_cutEnd(staffID);
        mActorState = ST_VIBRATING;
        mRemainingVibration = DESTROY_VIBRATION_LEN;
        mRemainingSmokeAnm = DESTROY_SMOKE_ANM_LEN;
        mIsVisible = 0;
        fopAcM_seStartCurrent(this, JA_SE_LK_W_WEP_CRT_HIT, 0);
        dComIfGp_getVibration().StartQuake(7, ~0x20, cXyz(0, 1, 0));
        mDoAud_seStart(JA_SE_READ_RIDDLE_1);
        daObjEskban_effect_set();
        break;
    }
    case ST_SMOKING: /* 0x350 */
        if (mRemainingSmokeAnm > 0) {
            mRemainingSmokeAnm--;
            break;
        } else {
            mActorState = ST_WAIT;
            dComIfGp_event_reset();
            break;
        }
        if (dComIfGp_evmng_endCheck("Eskban") && M_smoke->isEnd()) {
            dComIfGp_getVibration().StopQuake(-1);
            fopAcM_delete(this);
        }
        dComIfGp_event_reset();
        /* fallthrough */
    case ST_VIBRATING: /* 0x388 */
        if (mRemainingVibration > 0) {
            mRemainingVibration--;
            if (mRemainingVibration == DESTROY_VIBRATION_SHOCK_FRAME_IDX) {
                dComIfGp_getVibration().StartShock(6, 0x4, cXyz(0, 1, 0));
            }
        } else if (!fopAcM_isSwitch(this, param_get_swSave())) {
            fopAcM_onSwitch(this, param_get_swSave());
            dComIfGp_getVibration().StopQuake(-1);
            dComIfGp_getVibration().StartQuake(4, ~0x20, cXyz(0, 1, 0));
        }
        if (mRemainingSmokeAnm > 0) {
            mRemainingSmokeAnm--;
            break;
        }
        if (dComIfGp_evmng_endCheck("Eskban") && M_smoke->isEnd()) {
            dComIfGp_getVibration().StopQuake(-1);
            fopAcM_delete(this);
            dComIfGp_event_reset();
        }
    }
    set_mtx();
    *pMtx = &M_tmp_mtx;
    return TRUE;
}

/* 00001400-000014B4       .text Draw__Q211daObjEskban5Act_cFv */
BOOL daObjEskban::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &this->current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    if (!mIsVisible) {
        return TRUE;
    }
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

namespace daObjEskban {
namespace {
/* 000014B4-000014D4       .text Mthd_Create__Q211daObjEskban28@unnamed@d_a_obj_eskban_cpp@FPv */
void Mthd_Create(void* i_this) {
    ((Act_c*)i_this)->Mthd_Create();
}

/* 000014D4-000014F4       .text Mthd_Delete__Q211daObjEskban28@unnamed@d_a_obj_eskban_cpp@FPv */
void Mthd_Delete(void* i_this) {
    ((Act_c*)i_this)->Mthd_Delete();
}

/* 000014F4-00001514       .text Mthd_Execute__Q211daObjEskban28@unnamed@d_a_obj_eskban_cpp@FPv */
void Mthd_Execute(void* i_this) {
    ((Act_c*)i_this)->MoveBGExecute();
}

/* 00001514-00001540       .text Mthd_Draw__Q211daObjEskban28@unnamed@d_a_obj_eskban_cpp@FPv */
void Mthd_Draw(void* i_this) {
    ((Act_c*)i_this)->MoveBGDraw();
}

/* 00001540-0000156C       .text Mthd_IsDelete__Q211daObjEskban28@unnamed@d_a_obj_eskban_cpp@FPv */
void Mthd_IsDelete(void* i_this) {
    ((Act_c*)i_this)->MoveBGIsDelete();
}

static actor_method_class Mthd_Eskban = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjEskban

actor_process_profile_definition g_profile_Obj_Eskban = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Eskban,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjEskban::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x007A,
    /* Actor SubMtd */ &daObjEskban::Mthd_Eskban,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
