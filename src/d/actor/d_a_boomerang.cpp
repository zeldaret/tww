/**
 * d_a_boomerang.cpp
 * Item - Boomerang
 */

#include "d/actor/d_a_boomerang.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

#include "assets/l_sightMatDL.h"
#include "assets/l_sightDL__d_a_boomerang.h"
#include "d/d_cc_d.h"

static dCcD_SrcCps l_at_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_BOOMERANG,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e | cCcD_AtSPrm_NoTgHitInfSet_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ dCcG_SE_UNK4,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_Unk1_e,
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
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 3.0f,
    },
};


/* 800E0C08-800E0D44       .text initBlur__18daBoomerang_blur_cFPA4_fs */
void daBoomerang_blur_c::initBlur(MtxP, s16) {
    /* Nonmatching */
}

/* 800E0D44-800E101C       .text copyBlur__18daBoomerang_blur_cFPA4_fs */
void daBoomerang_blur_c::copyBlur(MtxP, s16) {
    /* Nonmatching */
}

/* 800E101C-800E13A4       .text draw__18daBoomerang_blur_cFv */
void daBoomerang_blur_c::draw() {
    /* Nonmatching */
}

/* 800E13A4-800E14F0       .text draw__25daBoomerang_sightPacket_cFv */
void daBoomerang_sightPacket_c::draw() {
    /* Nonmatching */
}

/* 800E14F0-800E1718       .text setSight__25daBoomerang_sightPacket_cFP4cXyzi */
void daBoomerang_sightPacket_c::setSight(cXyz*, int) {
    /* Nonmatching */
}

/* 800E1718-800E1754       .text play__25daBoomerang_sightPacket_cFi */
void daBoomerang_sightPacket_c::play(int) {
    /* Nonmatching */
}

/* 800E1754-800E1998       .text draw__13daBoomerang_cFv */
BOOL daBoomerang_c::draw() {
    /* Nonmatching */
}

/* 800E1998-800E19B8       .text daBoomerang_Draw__FP13daBoomerang_c */
static BOOL daBoomerang_Draw(daBoomerang_c* i_this) {
    return ((daBoomerang_c*)i_this)->draw();
}

/* 800E19B8-800E1A14       .text getFlyMax__13daBoomerang_cFv */
float daBoomerang_c::getFlyMax() {
    /* Nonmatching */
}

/* 800E1A14-800E1AAC       .text rockLineCallback__13daBoomerang_cFP10fopAc_ac_c */
void daBoomerang_c::rockLineCallback(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 800E1AAC-800E1AD0       .text daBoomerang_rockLineCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daBoomerang_rockLineCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 800E1AD0-800E1B20       .text setAimActor__13daBoomerang_cFP10fopAc_ac_c */
void daBoomerang_c::setAimActor(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 800E1B20-800E1C20       .text setLockActor__13daBoomerang_cFP10fopAc_ac_ci */
void daBoomerang_c::setLockActor(fopAc_ac_c*, int) {
    /* Nonmatching */
}

/* 800E1C20-800E1C58       .text resetLockActor__13daBoomerang_cFv */
void daBoomerang_c::resetLockActor() {
    /* Nonmatching */
}

/* 800E1C58-800E1CFC       .text setRoomInfo__13daBoomerang_cFv */
void daBoomerang_c::setRoomInfo() {
    /* Nonmatching */
}

/* 800E1CFC-800E1DA8       .text setKeepMatrix__13daBoomerang_cFv */
void daBoomerang_c::setKeepMatrix() {
    /* Nonmatching */
}

/* 800E1DA8-800E1E6C       .text setAimPos__13daBoomerang_cFv */
void daBoomerang_c::setAimPos() {
    /* Nonmatching */
}

/* 800E1E6C-800E1F94       .text checkBgHit__13daBoomerang_cFP4cXyzP4cXyz */
void daBoomerang_c::checkBgHit(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 800E1F94-800E239C       .text procWait__13daBoomerang_cFv */
void daBoomerang_c::procWait() {
    /* Nonmatching */
}

/* 800E239C-800E2AF4       .text procMove__13daBoomerang_cFv */
void daBoomerang_c::procMove() {
    /* Nonmatching */
}

/* 800E2AF4-800E2BD0       .text execute__13daBoomerang_cFv */
BOOL daBoomerang_c::execute() {
    /* Nonmatching */
}

/* 800E2BD0-800E2BF0       .text daBoomerang_Execute__FP13daBoomerang_c */
static BOOL daBoomerang_Execute(daBoomerang_c* i_this) {
    return ((daBoomerang_c*)i_this)->execute();
}

/* 800E2BF0-800E2BF8       .text daBoomerang_IsDelete__FP13daBoomerang_c */
static BOOL daBoomerang_IsDelete(daBoomerang_c*) {
    return TRUE;
}

/* 800E2BF8-800E2C00       .text daBoomerang_Delete__FP13daBoomerang_c */
static BOOL daBoomerang_Delete(daBoomerang_c*) {
    return TRUE;
}

/* 800E2C00-800E2CC8       .text createHeap__13daBoomerang_cFv */
void daBoomerang_c::createHeap() {
    /* Nonmatching */
}

/* 800E2CC8-800E2CE8       .text daBoomerang_createHeap__FP10fopAc_ac_c */
static BOOL daBoomerang_createHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 800E2CE8-800E2EF0       .text create__13daBoomerang_cFv */
cPhs_State daBoomerang_c::create() {
    /* Nonmatching */
}

/* 800E33F0-800E3410       .text daBoomerang_Create__FP10fopAc_ac_c */
static cPhs_State daBoomerang_Create(fopAc_ac_c* i_this) {
    return ((daBoomerang_c*)i_this)->create();
}

static actor_method_class l_daBoomerang_Method = {
    (process_method_func)daBoomerang_Create,
    (process_method_func)daBoomerang_Delete,
    (process_method_func)daBoomerang_Execute,
    (process_method_func)daBoomerang_IsDelete,
    (process_method_func)daBoomerang_Draw,
};

actor_process_profile_definition g_profile_BOOMERANG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BOOMERANG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBoomerang_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BOOMERANG,
    /* Actor SubMtd */ &l_daBoomerang_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
