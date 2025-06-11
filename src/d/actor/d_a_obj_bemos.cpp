/**
 * d_a_obj_bemos.cpp
 * Enemy - Beamos
 */

#include "d/actor/d_a_obj_bemos.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 70.0f,
        /* Height */ 210.0f,
    },
};


static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_BOMB | AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 65.0f,
    },
};


/* 000000EC-00000194       .text __ct__13daBemos_HIO_cFv */
daBemos_HIO_c::daBemos_HIO_c() {
    /* Nonmatching */
}

/* 00000194-0000033C       .text set_mtx__9daBemos_cFv */
void daBemos_c::set_mtx() {
    /* Nonmatching */
}

/* 0000033C-0000035C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000035C-00000498       .text CreateHeap1__9daBemos_cFv */
void daBemos_c::CreateHeap1() {
    /* Nonmatching */
}

/* 00000498-000006EC       .text CreateHeap2__9daBemos_cFv */
void daBemos_c::CreateHeap2() {
    /* Nonmatching */
}

/* 000006EC-000007A8       .text CreateHeap3__9daBemos_cFv */
void daBemos_c::CreateHeap3() {
    /* Nonmatching */
}

/* 000007A8-00000808       .text CreateHeap__9daBemos_cFv */
void daBemos_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000808-00000A4C       .text CreateInit1__9daBemos_cFv */
void daBemos_c::CreateInit1() {
    /* Nonmatching */
}

/* 00000A4C-00000CBC       .text CreateInit2__9daBemos_cFv */
void daBemos_c::CreateInit2() {
    /* Nonmatching */
}

/* 00000CBC-00001384       .text CreateInit3__9daBemos_cFv */
void daBemos_c::CreateInit3() {
    /* Nonmatching */
}

/* 00001384-0000148C       .text CreateInit__9daBemos_cFv */
void daBemos_c::CreateInit() {
    /* Nonmatching */
}

/* 0000148C-000016E4       .text blue_range_check__9daBemos_cFiP5csXyz */
void daBemos_c::blue_range_check(int, csXyz*) {
    /* Nonmatching */
}

/* 000016E4-0000199C       .text red_range_check__9daBemos_cFiP5csXyz */
void daBemos_c::red_range_check(int, csXyz*) {
    /* Nonmatching */
}

/* 0000199C-000019AC       .text yellow_range_check__9daBemos_cFiP5csXyz */
void daBemos_c::yellow_range_check(int, csXyz*) {
    /* Nonmatching */
}

/* 000019AC-00001BF0       .text blue_eye_wait_init__9daBemos_cFv */
void daBemos_c::blue_eye_wait_init() {
    /* Nonmatching */
}

/* 00001BF0-00001CAC       .text blue_eye_wait__9daBemos_cFv */
void daBemos_c::blue_eye_wait() {
    /* Nonmatching */
}

/* 00001CAC-00001E14       .text blue_eye_charge_init__9daBemos_cFv */
void daBemos_c::blue_eye_charge_init() {
    /* Nonmatching */
}

/* 00001E14-00002174       .text blue_eye_charge__9daBemos_cFv */
void daBemos_c::blue_eye_charge() {
    /* Nonmatching */
}

/* 00002174-000021A4       .text blue_eye_search_init__9daBemos_cFv */
void daBemos_c::blue_eye_search_init() {
    /* Nonmatching */
}

/* 000021A4-000023F0       .text blue_eye_search__9daBemos_cFv */
void daBemos_c::blue_eye_search() {
    /* Nonmatching */
}

/* 000023F0-00002630       .text red_eye_wait_init__9daBemos_cFv */
void daBemos_c::red_eye_wait_init() {
    /* Nonmatching */
}

/* 00002630-00002724       .text red_eye_wait__9daBemos_cFv */
void daBemos_c::red_eye_wait() {
    /* Nonmatching */
}

/* 00002724-0000288C       .text red_eye_charge_init__9daBemos_cFv */
void daBemos_c::red_eye_charge_init() {
    /* Nonmatching */
}

/* 0000288C-00002C04       .text red_eye_charge__9daBemos_cFv */
void daBemos_c::red_eye_charge() {
    /* Nonmatching */
}

/* 00002C04-00002C3C       .text red_eye_search_init__9daBemos_cFv */
void daBemos_c::red_eye_search_init() {
    /* Nonmatching */
}

/* 00002C3C-00002EF4       .text red_eye_search__9daBemos_cFv */
void daBemos_c::red_eye_search() {
    /* Nonmatching */
}

/* 00002EF4-00003040       .text eye_break_init__9daBemos_cFv */
void daBemos_c::eye_break_init() {
    /* Nonmatching */
}

/* 00003040-00003498       .text eye_break__9daBemos_cFv */
void daBemos_c::eye_break() {
    /* Nonmatching */
}

/* 00003498-000034BC       .text eye_dummy__9daBemos_cFv */
void daBemos_c::eye_dummy() {
    /* Nonmatching */
}

/* 000034BC-00003638       .text yellow_eye_wait_init__9daBemos_cFv */
void daBemos_c::yellow_eye_wait_init() {
    /* Nonmatching */
}

/* 00003638-00003798       .text yellow_eye_wait__9daBemos_cFv */
void daBemos_c::yellow_eye_wait() {
    /* Nonmatching */
}

/* 00003798-00003890       .text yellow_eye_search_init__9daBemos_cFv */
void daBemos_c::yellow_eye_search_init() {
    /* Nonmatching */
}

/* 00003890-00003A80       .text yellow_eye_search__9daBemos_cFv */
void daBemos_c::yellow_eye_search() {
    /* Nonmatching */
}

/* 00003A80-00003C5C       .text event_move__9daBemos_cFv */
void daBemos_c::event_move() {
    /* Nonmatching */
}

/* 00003C5C-00003F00       .text guard_proc__9daBemos_cFv */
void daBemos_c::guard_proc() {
    /* Nonmatching */
}

/* 00003F00-00003F70       .text getBeamActor__9daBemos_cFv */
void daBemos_c::getBeamActor() {
    /* Nonmatching */
}

/* 00003F70-00003F90       .text daBemosCreate__FPv */
static s32 daBemosCreate(void* i_this) {
    return ((daBemos_c*)i_this)->_create();
}

/* 00003F90-0000403C       .text _create__9daBemos_cFv */
cPhs_State daBemos_c::_create() {
    /* Nonmatching */
}

/* 00004ACC-00004BC0       .text daBemosDelete__FPv */
static BOOL daBemosDelete(void*) {
    /* Nonmatching */
}

/* 00004BC0-00004CF0       .text daBemosExecute__FPv */
static BOOL daBemosExecute(void*) {
    /* Nonmatching */
}

/* 00004CF0-00004E10       .text daBemosDraw__FPv */
static BOOL daBemosDraw(void*) {
    /* Nonmatching */
}

/* 00004E10-00004E18       .text daBemosIsDelete__FPv */
static BOOL daBemosIsDelete(void*) {
    return TRUE;
}

static actor_method_class daBemosMethodTable = {
    (process_method_func)daBemosCreate,
    (process_method_func)daBemosDelete,
    (process_method_func)daBemosExecute,
    (process_method_func)daBemosIsDelete,
    (process_method_func)daBemosDraw,
};

actor_process_profile_definition g_profile_Bemos = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Bemos,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBemos_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Bemos,
    /* Actor SubMtd */ &daBemosMethodTable,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
