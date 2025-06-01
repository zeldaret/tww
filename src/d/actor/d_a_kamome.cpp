/**
 * d_a_kamome.cpp
 * NPC - Seagull
 */

#include "d/actor/d_a_kamome.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-000001E4       .text anm_init__FP12kamome_classifUcfi */
void anm_init(kamome_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 000001E4-000004B8       .text s_a_d_sub__FPvPv */
void s_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 000008F0-00000A44       .text search_esa__FP12kamome_class */
void search_esa(kamome_class*) {
    /* Nonmatching */
}

/* 00000A44-00000A90       .text s_a_i_sub__FPvPv */
void s_a_i_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000A90-00000ABC       .text search_imouto__FP12kamome_class */
void search_imouto(kamome_class*) {
    /* Nonmatching */
}

/* 00000ABC-00000B84       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000B84-00000CAC       .text daKamome_Draw__FP12kamome_class */
static BOOL daKamome_Draw(kamome_class*) {
    /* Nonmatching */
}

/* 00000CAC-00000F70       .text kamome_pos_move__FP12kamome_class */
void kamome_pos_move(kamome_class*) {
    /* Nonmatching */
}

/* 00000F70-00000FFC       .text kamome_bgcheck__FP12kamome_class */
void kamome_bgcheck(kamome_class*) {
    /* Nonmatching */
}

/* 00000FFC-00001150       .text kamome_ground_pos_move__FP12kamome_class */
void kamome_ground_pos_move(kamome_class*) {
    /* Nonmatching */
}

/* 00001150-000011B8       .text ko_s_sub__FPvPv */
void ko_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 000011B8-000011FC       .text ko_check__FP12kamome_class */
void ko_check(kamome_class*) {
    /* Nonmatching */
}

/* 000011FC-00001304       .text heisou_control__FP12kamome_class */
void heisou_control(kamome_class*) {
    /* Nonmatching */
}

/* 00001304-00001360       .text h_s_sub__FPvPv */
void h_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001360-000013BC       .text search_master__FP12kamome_class */
void search_master(kamome_class*) {
    /* Nonmatching */
}

/* 000013BC-00001A0C       .text kamome_heisou_move__FP12kamome_class */
void kamome_heisou_move(kamome_class*) {
    /* Nonmatching */
}

/* 00001A0C-00002740       .text kamome_path_move__FP12kamome_class */
void kamome_path_move(kamome_class*) {
    /* Nonmatching */
}

/* 00002740-00003628       .text kamome_auto_move__FP12kamome_class */
void kamome_auto_move(kamome_class*) {
    /* Nonmatching */
}

/* 00003628-00004574       .text kamome_imouto_move__FP12kamome_class */
void kamome_imouto_move(kamome_class*) {
    /* Nonmatching */
}

/* 00004574-00004680       .text kamome_imouto2_move__FP12kamome_class */
void kamome_imouto2_move(kamome_class*) {
    /* Nonmatching */
}

/* 00004680-00004768       .text daKamome_setMtx__FP12kamome_class */
void daKamome_setMtx(kamome_class*) {
    /* Nonmatching */
}

/* 00004768-000049F8       .text daKamome_Execute__FP12kamome_class */
static BOOL daKamome_Execute(kamome_class*) {
    /* Nonmatching */
}

/* 000049F8-00004A00       .text daKamome_IsDelete__FP12kamome_class */
static BOOL daKamome_IsDelete(kamome_class*) {
    /* Nonmatching */
}

/* 00004A00-00004A70       .text daKamome_Delete__FP12kamome_class */
static BOOL daKamome_Delete(kamome_class*) {
    /* Nonmatching */
}

/* 00004A70-00004B94       .text createHeap__FP10fopAc_ac_c */
static BOOL createHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00004B94-00004F84       .text daKamome_Create__FP10fopAc_ac_c */
static cPhs_State daKamome_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
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
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 40.0f,
        },
    };
}

static actor_method_class l_daKamome_Method = {
    (process_method_func)daKamome_Create,
    (process_method_func)daKamome_Delete,
    (process_method_func)daKamome_Execute,
    (process_method_func)daKamome_IsDelete,
    (process_method_func)daKamome_Draw,
};

actor_process_profile_definition g_profile_KAMOME = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KAMOME,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kamome_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KAMOME,
    /* Actor SubMtd */ &l_daKamome_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
