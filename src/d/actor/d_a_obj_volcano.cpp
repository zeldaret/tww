/**
 * d_a_obj_volcano.cpp
 * Object - Fire Mountain Exterior - Lava
 */

#include "d/actor/d_a_obj_volcano.h"
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
        /* SrcObjTg  Type    */ AT_TYPE_ICE_ARROW,
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
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 300.0f,
        /* Height */ 3000.0f,
    },
};


/* 00000078-000003CC       .text StartFire__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::StartFire() {
    /* Nonmatching */
}

/* 000003CC-00000470       .text StopFire__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::StopFire() {
    /* Nonmatching */
}

/* 00000470-00000758       .text CreateHeap__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000758-000009C8       .text Create__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Create() {
    /* Nonmatching */
}

/* 000009C8-00000BA0       .text Mthd_Create__Q212daObjVolcano5Act_cFv */
cPhs_State daObjVolcano::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000E58-00000E60       .text Delete__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000E60-00000EC0       .text Mthd_Delete__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 00000EC0-00000F84       .text set_mtx__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000F84-00000FDC       .text init_mtx__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000FDC-0000103C       .text daObjVolcano_fire_demo_wait__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fire_demo_wait() {
    /* Nonmatching */
}

/* 0000103C-00001160       .text daObjVolcano_fire_demo_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fire_demo_main() {
    /* Nonmatching */
}

/* 00001160-00001284       .text daObjVolcano_fire_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fire_main() {
    /* Nonmatching */
}

/* 00001284-000013E4       .text daObjVolcano_freeze_demo_wait__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_freeze_demo_wait() {
    /* Nonmatching */
}

/* 000013E4-00001558       .text daObjVolcano_freeze_demo_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_freeze_demo_main() {
    /* Nonmatching */
}

/* 00001558-000015E8       .text daObjVolcano_freeze_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_freeze_main() {
    /* Nonmatching */
}

/* 000015E8-0000164C       .text daObjVolcano_fail_demo_wait__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fail_demo_wait() {
    /* Nonmatching */
}

/* 0000164C-00001740       .text daObjVolcano_fail_demo_main__Q212daObjVolcano5Act_cFv */
void daObjVolcano::Act_c::daObjVolcano_fail_demo_main() {
    /* Nonmatching */
}

/* 00001740-0000199C       .text Execute__Q212daObjVolcano5Act_cFPPA3_A4_f */
BOOL daObjVolcano::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 0000199C-00001A2C       .text set_material__Q212daObjVolcano5Act_cFP11J3DMaterialUc */
void daObjVolcano::Act_c::set_material(J3DMaterial*, unsigned char) {
    /* Nonmatching */
}

/* 00001A2C-00001B8C       .text Draw__Q212daObjVolcano5Act_cFv */
BOOL daObjVolcano::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjVolcano {
namespace {
/* 00001B8C-00001BAC       .text Mthd_Create__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->Mthd_Create();
}

/* 00001BAC-00001BCC       .text Mthd_Delete__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->Mthd_Delete();
}

/* 00001BCC-00001BEC       .text Mthd_Execute__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->MoveBGExecute();
}

/* 00001BEC-00001C18       .text Mthd_Draw__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->Draw();
}

/* 00001C18-00001C44       .text Mthd_IsDelete__Q212daObjVolcano29@unnamed@d_a_obj_volcano_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjVolcano::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVolcano

actor_process_profile_definition g_profile_Obj_Volcano = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Volcano,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVolcano::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Volcano,
    /* Actor SubMtd */ &daObjVolcano::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
