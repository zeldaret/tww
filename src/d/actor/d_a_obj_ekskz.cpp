/**
 * d_a_obj_ekskz.cpp
 * Object - Stone statue blowing strong gust of wind (Gale Isle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ekskz.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl cyl_check_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_SKULL_HAMMER,
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
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 300.0f,
    }},
};


/* 00000078-00000368       .text CreateHeap__Q210daObjEkskz5Act_cFv */
BOOL daObjEkskz::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000368-0000054C       .text Create__Q210daObjEkskz5Act_cFv */
BOOL daObjEkskz::Act_c::Create() {
    /* Nonmatching */
}

/* 0000054C-00000684       .text Mthd_Create__Q210daObjEkskz5Act_cFv */
cPhs_State daObjEkskz::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000C00-00000C64       .text Delete__Q210daObjEkskz5Act_cFv */
BOOL daObjEkskz::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000C64-00000CBC       .text Mthd_Delete__Q210daObjEkskz5Act_cFv */
BOOL daObjEkskz::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 00000CBC-00000D68       .text set_mtx__Q210daObjEkskz5Act_cFv */
void daObjEkskz::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000D68-00000DC0       .text init_mtx__Q210daObjEkskz5Act_cFv */
void daObjEkskz::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000DC0-00000FFC       .text Execute__Q210daObjEkskz5Act_cFPPA3_A4_f */
BOOL daObjEkskz::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 00000FFC-00001124       .text Draw__Q210daObjEkskz5Act_cFv */
BOOL daObjEkskz::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjEkskz {
namespace {
/* 00001124-00001144       .text Mthd_Create__Q210daObjEkskz27@unnamed@d_a_obj_ekskz_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjEkskz::Act_c*)i_this)->Mthd_Create();
}

/* 00001144-00001164       .text Mthd_Delete__Q210daObjEkskz27@unnamed@d_a_obj_ekskz_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjEkskz::Act_c*)i_this)->Mthd_Delete();
}

/* 00001164-00001184       .text Mthd_Execute__Q210daObjEkskz27@unnamed@d_a_obj_ekskz_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjEkskz::Act_c*)i_this)->MoveBGExecute();
}

/* 00001184-000011B0       .text Mthd_Draw__Q210daObjEkskz27@unnamed@d_a_obj_ekskz_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjEkskz::Act_c*)i_this)->Draw();
}

/* 000011B0-000011DC       .text Mthd_IsDelete__Q210daObjEkskz27@unnamed@d_a_obj_ekskz_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjEkskz::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Ekskz = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjEkskz

actor_process_profile_definition g_profile_Obj_Ekskz = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ekskz,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjEkskz::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ekskz,
    /* Actor SubMtd */ &daObjEkskz::Mthd_Ekskz,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
