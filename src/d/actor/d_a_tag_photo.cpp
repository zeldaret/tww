//
// Generated by dtk
// Translation Unit: d_a_tag_photo.cpp
//

#include "d/actor/d_a_tag_photo.h"
#include "d/d_procname.h"

/* 00000078-000000D0       .text __ct__12daTagPhoto_cFv */
daTagPhoto_c::daTagPhoto_c() {
    /* Nonmatching */
}

/* 000000D0-000000F0       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000F0-00000140       .text phase_1__FP12daTagPhoto_c */
void phase_1(daTagPhoto_c*) {
    /* Nonmatching */
}

/* 00000140-00000198       .text phase_2__FP12daTagPhoto_c */
void phase_2(daTagPhoto_c*) {
    /* Nonmatching */
}

/* 00000198-000001C8       .text _create__12daTagPhoto_cFv */
s32 daTagPhoto_c::_create() {
    /* Nonmatching */
}

/* 000001C8-000001D0       .text createHeap__12daTagPhoto_cFv */
void daTagPhoto_c::createHeap() {
    /* Nonmatching */
}

/* 000001D0-00000298       .text createInit__12daTagPhoto_cFv */
void daTagPhoto_c::createInit() {
    /* Nonmatching */
}

/* 00000298-000002A0       .text _delete__12daTagPhoto_cFv */
BOOL daTagPhoto_c::_delete() {
    /* Nonmatching */
}

/* 000002A0-000002A8       .text _draw__12daTagPhoto_cFv */
BOOL daTagPhoto_c::_draw() {
    /* Nonmatching */
}

/* 000002A8-000002CC       .text setMode__12daTagPhoto_cFUc */
void daTagPhoto_c::setMode(unsigned char) {
    /* Nonmatching */
}

/* 000002CC-00000368       .text _execute__12daTagPhoto_cFv */
BOOL daTagPhoto_c::_execute() {
    /* Nonmatching */
}

/* 00000368-000004A0       .text executeWait__12daTagPhoto_cFv */
void daTagPhoto_c::executeWait() {
    /* Nonmatching */
}

/* 000004A0-000004FC       .text executeTalk__12daTagPhoto_cFv */
void daTagPhoto_c::executeTalk() {
    /* Nonmatching */
}

/* 000004FC-00000500       .text checkOrder__12daTagPhoto_cFv */
void daTagPhoto_c::checkOrder() {
    /* Nonmatching */
}

/* 00000500-00000504       .text eventOrder__12daTagPhoto_cFv */
void daTagPhoto_c::eventOrder() {
    /* Nonmatching */
}

/* 00000504-000005BC       .text eventMove__12daTagPhoto_cFv */
void daTagPhoto_c::eventMove() {
    /* Nonmatching */
}

/* 000005BC-000006C8       .text privateCut__12daTagPhoto_cFv */
void daTagPhoto_c::privateCut() {
    /* Nonmatching */
}

/* 000006C8-00000768       .text eventMesSetInit__12daTagPhoto_cFi */
void daTagPhoto_c::eventMesSetInit(int) {
    /* Nonmatching */
}

/* 00000768-0000079C       .text eventMesSet__12daTagPhoto_cFv */
void daTagPhoto_c::eventMesSet() {
    /* Nonmatching */
}

/* 0000079C-0000087C       .text talk__12daTagPhoto_cFi */
void daTagPhoto_c::talk(int) {
    /* Nonmatching */
}

/* 0000087C-000008CC       .text next_msgStatus__12daTagPhoto_cFPUl */
void daTagPhoto_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 000008CC-000008EC       .text getMsg__12daTagPhoto_cFv */
void daTagPhoto_c::getMsg() {
    /* Nonmatching */
}

/* 000008EC-000008FC       .text setMessage__12daTagPhoto_cFUl */
void daTagPhoto_c::setMessage(unsigned long) {
    /* Nonmatching */
}

/* 000008FC-00000928       .text getPrmTagNo__12daTagPhoto_cFv */
void daTagPhoto_c::getPrmTagNo() {
    /* Nonmatching */
}

/* 00000928-00000948       .text daTagPhotoCreate__FPv */
static s32 daTagPhotoCreate(void*) {
    /* Nonmatching */
}

/* 00000948-00000968       .text daTagPhotoDelete__FPv */
static BOOL daTagPhotoDelete(void*) {
    /* Nonmatching */
}

/* 00000968-00000988       .text daTagPhotoExecute__FPv */
static BOOL daTagPhotoExecute(void*) {
    /* Nonmatching */
}

/* 00000988-000009A8       .text daTagPhotoDraw__FPv */
static BOOL daTagPhotoDraw(void*) {
    /* Nonmatching */
}

/* 000009A8-000009B0       .text daTagPhotoIsDelete__FPv */
static BOOL daTagPhotoIsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daTagPhotoMethodTable = {
    (process_method_func)daTagPhotoCreate,
    (process_method_func)daTagPhotoDelete,
    (process_method_func)daTagPhotoExecute,
    (process_method_func)daTagPhotoIsDelete,
    (process_method_func)daTagPhotoDraw,
};

actor_process_profile_definition g_profile_TAG_PHOTO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TAG_PHOTO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTagPhoto_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0126,
    /* Actor SubMtd */ &daTagPhotoMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
