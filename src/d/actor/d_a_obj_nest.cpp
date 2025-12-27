/**
 * d_a_obj_nest.cpp
 * Object - Kargaroc nest
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_nest.h"
#include "d/res/res_mtorisu.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_w.h"
namespace daObjNest{
    namespace{
        struct Attr_c {
            /* 0x00 */ const f32 field_0x00;
            /* 0x04 */ const f32 field_0x04;
            /* 0x08 */ const f32 field_0x08;
            /* 0x0C */ const f32 field_0x0C;
            /* 0x10 */ const f32 field_0x10;
            /* 0x14 */ const f32 field_0x14;
            /* 0x18 */ const f32 field_0x18;
            /* 0x1C */ const f32 field_0x1C;
            /* 0x20 */ const s16 field_0x20;
            /* 0x20 */ const s16 field_0x22;
            /* 0x24 */ const s16 field_0x24;
            /* 0x28 */ const f32 field_0x28;
            /* 0x2C */ const f32 field_0x2C;
        };

        const Attr_c L_attr = {
            /* field_0x00 */ 30.0f,
            /* field_0x04 */ 100.0f,
            /* field_0x08 */ 400.0f,
            /* field_0x0C */ 400.0f,
            /* field_0x10 */ 400.0f,
            /* field_0x14 */ 50.0f,
            /* field_0x18 */ 100.0f,
            /* field_0x1C */ 50.0f,
            /* field_0x20 */ 0x4650, 
            /* field_0x22 */ 0x4650, 
            /* field_0x24 */ 0x4650,
            /* field_0x28 */ 0.92f,
            /* field_0x2C */ 100.0f,
        };

        inline static const Attr_c& attr() { return L_attr; }
    }
}

Mtx daObjNest::Act_c::M_tmp_mtx;
const char daObjNest::Act_c::M_arcname[] = "MtoriSU";

/* 00000078-0000012C       .text CreateHeap__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, MTORISU_BDL_MTORISU);
    JUT_ASSERT(281, model_data != NULL);
    mpModel = mDoExt_J3DModel__create(model_data, 0x80000,0x11000022);
    return mpModel != NULL;
}

/* 0000012C-000001F0       .text Create__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeSphere(this, 0.0f, 20.0f, 0.0f, 210.0f);
    this->mpBgW->SetRideCallback(rideCB);
    mcXyz_0x2D4 = cXyz::Zero;
    mcsXyz_0x2E0 = csXyz::Zero;
    mcsXyz_0x2E6 = csXyz::Zero;
    return TRUE;
}

/* 000001F0-000002E8       .text Mthd_Create__Q29daObjNest5Act_cFv */
cPhs_State daObjNest::Act_c::Mthd_Create() {
    fopAcM_SetupActor(this, daObjNest::Act_c);
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(
            M_arcname,
            MTORISU_DZB_MTORISU,
            NULL,
#if VERSION == VERSION_DEMO
            0x1820
#else
            0xAA0
#endif
        );
        JUT_ASSERT(329, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 000002E8-000002F0       .text Delete__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Delete() {
    return TRUE;
}

/* 000002F0-0000033C       .text Mthd_Delete__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Mthd_Delete() {
    u32 result = MoveBGDelete();
    dComIfG_resDeleteDemo(&mPhs, M_arcname);
    return result;
}

/* 0000033C-000003D4       .text set_mtx__Q29daObjNest5Act_cFv */
void daObjNest::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
    mDoMtx_stack_c::ZXYrotM(mcsXyz_0x2E6);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000003D4-00000410       .text init_mtx__Q29daObjNest5Act_cFv */
void daObjNest::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000410-00000498       .text rideCB__Q29daObjNest5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjNest::Act_c::rideCB(dBgW* bgw, fopAc_ac_c* i_ac, fopAc_ac_c* i_pt) {
    daObjNest::Act_c * i_this = (daObjNest::Act_c *)i_ac;
    f32 actorDistXZ2 = fopAcM_searchActorDistanceXZ2(i_this,i_pt);
    if (actorDistXZ2 > SQUARE(attr().field_0x04)) {
        f32 fVar = i_pt->speedF * (1.0f / attr().field_0x00);
        i_this->vib_set(cLib_maxLimit(fVar, 1.0f));
    }
}

/* 00000498-00000544       .text vib_set__Q29daObjNest5Act_cFf */
void daObjNest::Act_c::vib_set(float param) {
    mcXyz_0x2D4.x += param * attr().field_0x08;
    mcXyz_0x2D4.y += param * attr().field_0x0C;
    mcXyz_0x2D4.z += param * attr().field_0x10;

    mcXyz_0x2D4.x = cLib_maxLimit(mcXyz_0x2D4.x,attr().field_0x14);
    mcXyz_0x2D4.y = cLib_maxLimit(mcXyz_0x2D4.y,attr().field_0x18);
    mcXyz_0x2D4.z = cLib_maxLimit(mcXyz_0x2D4.z,attr().field_0x1C);
}

/* 00000544-0000070C       .text vib_proc__Q29daObjNest5Act_cFv */
void daObjNest::Act_c::vib_proc() {
    mcsXyz_0x2E0.x += attr().field_0x20;
    mcsXyz_0x2E0.y += attr().field_0x22;
    mcsXyz_0x2E0.z += attr().field_0x24;
    f32 fVar2 = this->mcXyz_0x2D4.abs();
    if (fVar2 < attr().field_0x2C) {
        mcsXyz_0x2E6 = csXyz::Zero;
    }else{
        mcsXyz_0x2E6.x = mcXyz_0x2D4.x * cM_scos(mcsXyz_0x2E0.x);
        mcsXyz_0x2E6.y = mcXyz_0x2D4.y * cM_scos(mcsXyz_0x2E0.y);
        mcsXyz_0x2E6.z = mcXyz_0x2D4.z * cM_scos(mcsXyz_0x2E0.z);
    }

    mcXyz_0x2D4 *= attr().field_0x28;
}

/* 0000070C-0000075C       .text Execute__Q29daObjNest5Act_cFPPA3_A4_f */
BOOL daObjNest::Act_c::Execute(Mtx** pMtx) {
    vib_proc();
    set_mtx();
    *pMtx = &M_tmp_mtx;
    return TRUE;
}

/* 0000075C-000007FC       .text Draw__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    dComIfG_Bgsp();
    return TRUE;
}

namespace daObjNest {
namespace {
/* 000007FC-0000081C       .text Mthd_Create__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->Mthd_Create();
}

/* 0000081C-0000083C       .text Mthd_Delete__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->Mthd_Delete();
}

/* 0000083C-0000085C       .text Mthd_Execute__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->MoveBGExecute();
}

/* 0000085C-00000888       .text Mthd_Draw__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->Draw();
}

/* 00000888-000008B4       .text Mthd_IsDelete__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjNest

actor_process_profile_definition g_profile_Obj_Nest = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Nest,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjNest::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Nest,
    /* Actor SubMtd */ &daObjNest::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLSPHERE_CUSTOM_e,
};
