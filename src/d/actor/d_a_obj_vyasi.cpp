/**
 * d_a_obj_vyasi.cpp
 * Object - Palm tree blowing in the wind (Gale Isle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_vyasi.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-0000015C       .text SetStopJointAnimation__Q210daObjVyasi5Act_cFP18J3DAnmTransformKeyff */
void daObjVyasi::Act_c::SetStopJointAnimation(J3DAnmTransformKey*, float, float) {
    /* Nonmatching */
}

/* 0000015C-00000194       .text PlayStopJointAnimation__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::PlayStopJointAnimation() {
    /* Nonmatching */
}

/* 00000194-0000021C       .text set_first_process__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_first_process() {
    /* Nonmatching */
}

/* 0000021C-000005B8       .text set_collision__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_collision() {
    /* Nonmatching */
}

/* 000005F4-000009B8       .text JointNodeCallBack__10daObjVyasiFP7J3DNodei */
BOOL daObjVyasi::JointNodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000009F4-000009FC       .text process_none_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_none_init() {
    /* Nonmatching */
}

/* 000009FC-00000A00       .text process_none_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_none_main() {
    /* Nonmatching */
}

/* 00000A00-00000A64       .text process_sag_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sag_init() {
    /* Nonmatching */
}

/* 00000A64-00000AD8       .text process_sag_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sag_main() {
    /* Nonmatching */
}

/* 00000AD8-00000CC0       .text process_sagWind_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sagWind_init() {
    /* Nonmatching */
}

/* 00000CC0-00000D20       .text process_sagWind_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sagWind_main() {
    /* Nonmatching */
}

/* 00000D20-00000D54       .text process_toNormal_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_toNormal_init() {
    /* Nonmatching */
}

/* 00000D54-00000E10       .text process_toNormal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_toNormal_main() {
    /* Nonmatching */
}

/* 00000E10-00000E74       .text process_normal_init__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_normal_init() {
    /* Nonmatching */
}

/* 00000E74-00000ED0       .text process_normal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_normal_main() {
    /* Nonmatching */
}

/* 00000ED0-00000FE4       .text process_init__Q210daObjVyasi5Act_cFi */
void daObjVyasi::Act_c::process_init(int) {
    /* Nonmatching */
}

/* 00000FE4-000010C8       .text process_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_main() {
    /* Nonmatching */
}

/* 000010C8-000010EC       .text solidHeapCB__Q210daObjVyasi5Act_cFP10fopAc_ac_c */
void daObjVyasi::Act_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000010EC-00001290       .text create_heap__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::create_heap() {
    /* Nonmatching */
}

/* 00001290-000016E0       .text _create__Q210daObjVyasi5Act_cFv */
cPhs_State daObjVyasi::Act_c::_create() {
    /* Nonmatching */
}

/* 00001D8C-00001DBC       .text _delete__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_delete() {
    /* Nonmatching */
}

/* 00001DBC-00001E5C       .text set_mtx__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00001E5C-000025A8       .text calc_dif_angle__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::calc_dif_angle() {
    /* Nonmatching */
}

/* 000025A8-00002880       .text quaternion_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::quaternion_main() {
    /* Nonmatching */
}

/* 00002880-00002938       .text leaf_scale_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::leaf_scale_main() {
    /* Nonmatching */
}

/* 00002938-000029BC       .text _execute__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_execute() {
    /* Nonmatching */
}

/* 000029BC-00002A6C       .text _draw__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjVyasi {
namespace {
/* 00002A6C-00002A8C       .text Mthd_Create__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_create();
}

/* 00002A8C-00002AB0       .text Mthd_Delete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_delete();
}

/* 00002AB0-00002AD4       .text Mthd_Execute__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_execute();
}

/* 00002AD4-00002AF8       .text Mthd_Draw__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_draw();
}

/* 00002AF8-00002B00       .text Mthd_IsDelete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVyasi

actor_process_profile_definition g_profile_Obj_Vyasi = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Vyasi,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVyasi::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Vyasi,
    /* Actor SubMtd */ &daObjVyasi::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
