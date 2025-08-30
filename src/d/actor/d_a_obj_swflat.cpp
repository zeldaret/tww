/**
 * d_a_obj_swflat.cpp
 * Object - Tower of the Gods - Floor switch (requires statues to stay active)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_swflat.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

namespace daObjSwflat {
static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e | cCcD_CoSPrm_NoCrr_e | cCcD_CoSPrm_NoCoHitInfSet_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 10.0f,
        /* Height */ 20.0f,
    }},
};
}


/* 000000EC-00000138       .text __ct__17daObjSwflat_HIO_cFv */
daObjSwflat_HIO_c::daObjSwflat_HIO_c() {
    /* Nonmatching */
}

/* 00000138-00000280       .text CreateHeap__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 000002C8-00000630       .text Create__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Create() {
    /* Nonmatching */
}

/* 00000630-000007BC       .text Mthd_Create__Q211daObjSwflat5Act_cFv */
cPhs_State daObjSwflat::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000974-0000097C       .text Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Delete() {
    /* Nonmatching */
}

/* 0000097C-00000A64       .text Mthd_Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 00000A64-00000AE4       .text set_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000AE4-00000B20       .text init_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000B20-0000121C       .text Execute__Q211daObjSwflat5Act_cFPPA3_A4_f */
BOOL daObjSwflat::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 0000121C-000012D4       .text Draw__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Draw() {
    /* Nonmatching */
}

/* 000012D4-000012DC       .text IsDelete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::IsDelete() {
    /* Nonmatching */
}

namespace daObjSwflat {
namespace {
/* 000012DC-000012FC       .text Mthd_Create__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Mthd_Create();
}

/* 000012FC-0000131C       .text Mthd_Delete__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Mthd_Delete();
}

/* 0000131C-0000133C       .text Mthd_Execute__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->MoveBGExecute();
}

/* 0000133C-00001368       .text Mthd_Draw__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Draw();
}

/* 00001368-00001394       .text Mthd_IsDelete__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjSwflat

actor_process_profile_definition g_profile_Obj_Swflat = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Swflat,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSwflat::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Swflat,
    /* Actor SubMtd */ &daObjSwflat::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLSPHERE_CUSTOM_e,
};
