/**
 * d_a_obj_ikada.cpp
 * Object - Various Great Sea ships (Beedle, Submarines, Skull Platforms/Rafts, and Salvage Corp.)
 */

#include "d/actor/d_a_obj_ikada.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

const dCcD_SrcSph daObj_Ikada_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 75.0f,
    },
};


/* 000000EC-00000254       .text __ct__17daObj_Ikada_HIO_cFv */
daObj_Ikada_HIO_c::daObj_Ikada_HIO_c() {
    /* Nonmatching */
}

/* 000002D8-00000324       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000324-00000458       .text _nodeControl__13daObj_Ikada_cFP7J3DNodeP8J3DModel */
void daObj_Ikada_c::_nodeControl(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 00000458-00000494       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
void pathMove_CB(cXyz*, cXyz*, cXyz*, void*) {
    /* Nonmatching */
}

/* 00000494-000007A0       .text _pathMove__13daObj_Ikada_cFP4cXyzP4cXyzP4cXyz */
void daObj_Ikada_c::_pathMove(cXyz*, cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 000007A0-000007C8       .text ride_CB__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_CB(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000007C8-00000A00       .text _ride__13daObj_Ikada_cFP10fopAc_ac_c */
void daObj_Ikada_c::_ride(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000A00-00000A20       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000A20-00000AA4       .text setCollision__13daObj_Ikada_cFv */
void daObj_Ikada_c::setCollision() {
    /* Nonmatching */
}

/* 00000AA4-00000DFC       .text checkTgHit__13daObj_Ikada_cFv */
void daObj_Ikada_c::checkTgHit() {
    /* Nonmatching */
}

/* 00000E38-00000F04       .text pathMove__13daObj_Ikada_cFv */
void daObj_Ikada_c::pathMove() {
    /* Nonmatching */
}

/* 00000F04-00000FBC       .text HandleRight__13daObj_Ikada_cFv */
void daObj_Ikada_c::HandleRight() {
    /* Nonmatching */
}

/* 00000FBC-00001074       .text HandleLeft__13daObj_Ikada_cFv */
void daObj_Ikada_c::HandleLeft() {
    /* Nonmatching */
}

/* 00001074-000012EC       .text createWave__13daObj_Ikada_cFv */
void daObj_Ikada_c::createWave() {
    /* Nonmatching */
}

/* 000012EC-00001528       .text setWave__13daObj_Ikada_cFv */
void daObj_Ikada_c::setWave() {
    /* Nonmatching */
}

/* 00001528-00001690       .text incRopeCnt__13daObj_Ikada_cFii */
void daObj_Ikada_c::incRopeCnt(int, int) {
    /* Nonmatching */
}

/* 00001690-00001DEC       .text setRopePos__13daObj_Ikada_cFv */
void daObj_Ikada_c::setRopePos() {
    /* Nonmatching */
}

/* 00001DEC-000024A4       .text setMtx__13daObj_Ikada_cFv */
void daObj_Ikada_c::setMtx() {
    /* Nonmatching */
}

/* 000024A4-000027A4       .text modeProc__13daObj_Ikada_cFQ213daObj_Ikada_c6Proc_ei */
void daObj_Ikada_c::modeProc(daObj_Ikada_c::Proc_e, int) {
    /* Nonmatching */
}

/* 000027A4-000027A8       .text modeWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeWaitInit() {
    /* Nonmatching */
}

/* 000027A8-00002840       .text modeWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeWait() {
    /* Nonmatching */
}

/* 00002840-00002844       .text modeCraneUpInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpInit() {
    /* Nonmatching */
}

/* 00002844-0000289C       .text modeCraneUp__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUp() {
    /* Nonmatching */
}

/* 0000289C-000028B0       .text modeCraneUpWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpWaitInit() {
    /* Nonmatching */
}

/* 000028B0-000028F8       .text modeCraneUpWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpWait() {
    /* Nonmatching */
}

/* 000028F8-00002904       .text modeCraneDownInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownInit() {
    /* Nonmatching */
}

/* 00002904-000029B0       .text modeCraneDown__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDown() {
    /* Nonmatching */
}

/* 000029B0-000029C4       .text modeCraneDownWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownWaitInit() {
    /* Nonmatching */
}

/* 000029C4-00002A0C       .text modeCraneDownWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownWait() {
    /* Nonmatching */
}

/* 00002A0C-00002A24       .text modeCraneTurnInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneTurnInit() {
    /* Nonmatching */
}

/* 00002A24-00002AEC       .text modeCraneTurn__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneTurn() {
    /* Nonmatching */
}

/* 00002AEC-00002B04       .text modeCraneResetInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneResetInit() {
    /* Nonmatching */
}

/* 00002B04-00002BB4       .text modeCraneReset__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneReset() {
    /* Nonmatching */
}

/* 00002BB4-00002BC0       .text modeCraneWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneWaitInit() {
    /* Nonmatching */
}

/* 00002BC0-00002C08       .text modeCraneWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneWait() {
    /* Nonmatching */
}

/* 00002C08-00002C60       .text modePathMoveInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveInit() {
    /* Nonmatching */
}

/* 00002C60-00002DC0       .text modePathMove__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMove() {
    /* Nonmatching */
}

/* 00002DC0-00002DC4       .text modeStopInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopInit() {
    /* Nonmatching */
}

/* 00002DC4-00002F04       .text modeStop__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStop() {
    /* Nonmatching */
}

/* 00002F04-00002F10       .text modePathMoveTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveTerryInit() {
    /* Nonmatching */
}

/* 00002F10-00003228       .text modePathMoveTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveTerry() {
    /* Nonmatching */
}

/* 00003228-00003234       .text modeStopTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopTerryInit() {
    /* Nonmatching */
}

/* 00003234-0000342C       .text modeStopTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopTerry() {
    /* Nonmatching */
}

/* 0000342C-00003430       .text modeStopBombTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopBombTerryInit() {
    /* Nonmatching */
}

/* 00003430-000034D0       .text modeStopBombTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopBombTerry() {
    /* Nonmatching */
}

/* 000034D0-00003750       .text epProc__13daObj_Ikada_cFv */
void daObj_Ikada_c::epProc() {
    /* Nonmatching */
}

/* 00003750-00003CA0       .text _execute__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_execute() {
    /* Nonmatching */
}

/* 00003CA0-00003CD4       .text debugDraw__13daObj_Ikada_cFv */
void daObj_Ikada_c::debugDraw() {
    /* Nonmatching */
}

/* 00003CD4-00003EE0       .text _draw__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_draw() {
    /* Nonmatching */
}

/* 00003EE0-00003F34       .text getArg__13daObj_Ikada_cFv */
void daObj_Ikada_c::getArg() {
    /* Nonmatching */
}

/* 00003F34-00004838       .text createInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::createInit() {
    /* Nonmatching */
}

/* 00004838-00004B60       .text _createHeap__13daObj_Ikada_cFv */
void daObj_Ikada_c::_createHeap() {
    /* Nonmatching */
}

/* 00004B60-00004C18       .text _create__13daObj_Ikada_cFv */
cPhs_State daObj_Ikada_c::_create() {
    /* Nonmatching */
}

/* 00005320-0000543C       .text _delete__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_delete() {
    /* Nonmatching */
}

/* 0000543C-0000545C       .text daObj_IkadaCreate__FPv */
static s32 daObj_IkadaCreate(void*) {
    /* Nonmatching */
}

/* 0000545C-00005480       .text daObj_IkadaDelete__FPv */
static BOOL daObj_IkadaDelete(void*) {
    /* Nonmatching */
}

/* 00005480-000054A4       .text daObj_IkadaExecute__FPv */
static BOOL daObj_IkadaExecute(void*) {
    /* Nonmatching */
}

/* 000054A4-000054C8       .text daObj_IkadaDraw__FPv */
static BOOL daObj_IkadaDraw(void*) {
    /* Nonmatching */
}

/* 000054C8-000054D0       .text daObj_IkadaIsDelete__FPv */
static BOOL daObj_IkadaIsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daObj_IkadaMethodTable = {
    (process_method_func)daObj_IkadaCreate,
    (process_method_func)daObj_IkadaDelete,
    (process_method_func)daObj_IkadaExecute,
    (process_method_func)daObj_IkadaIsDelete,
    (process_method_func)daObj_IkadaDraw,
};

actor_process_profile_definition g_profile_OBJ_IKADA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_IKADA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Ikada_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_IKADA,
    /* Actor SubMtd */ &daObj_IkadaMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
