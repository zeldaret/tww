/**
 * d_a_nz.cpp
 * Enemy - Rat
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_nz.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-00000138       .text __ct__10daNZ_HIO_cFv */
daNZ_HIO_c::daNZ_HIO_c() {
    /* Nonmatching */
}

/* 00000180-00000228       .text nodeCallBack_tail__FP7J3DNodei */
static BOOL nodeCallBack_tail(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000264-00000874       .text tail_control__FP8nz_class */
void tail_control(nz_class*) {
    /* Nonmatching */
}

/* 00000BF4-00000C88       .text tail_draw__FP8nz_class */
void tail_draw(nz_class*) {
    /* Nonmatching */
}

/* 00000C88-00000D64       .text nodeCallBack_head__FP7J3DNodei */
static BOOL nodeCallBack_head(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000D64-00000E60       .text nodeCallBack_hand__FP7J3DNodei */
static BOOL nodeCallBack_hand(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000E60-00000F40       .text smoke_set__FP8nz_class */
void smoke_set(nz_class*) {
    /* Nonmatching */
}

/* 00000F40-00001328       .text rakka_line_check__FP8nz_class */
void rakka_line_check(nz_class*) {
    /* Nonmatching */
}

/* 00001578-0000178C       .text daNZ_Draw__FP8nz_class */
static BOOL daNZ_Draw(nz_class*) {
    /* Nonmatching */
}

/* 0000178C-00001888       .text item_poi__FP8nz_class */
void item_poi(nz_class*) {
    /* Nonmatching */
}

/* 00001888-00001F18       .text naraku_water_check__FP8nz_class */
void naraku_water_check(nz_class*) {
    /* Nonmatching */
}

/* 0000206C-0000214C       .text s_a_d_sub__FPvPv */
void s_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 0000214C-000027FC       .text search_get_obj__FP8nz_class */
void search_get_obj(nz_class*) {
    /* Nonmatching */
}

/* 000027FC-00002864       .text s_ana_sub__FPvPv */
void s_ana_sub(void*, void*) {
    /* Nonmatching */
}

/* 00002864-00002990       .text anm_init__FP8nz_classifUcfi */
void anm_init(nz_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00002990-00002EC0       .text search_check__FP8nz_class */
void search_check(nz_class*) {
    /* Nonmatching */
}

/* 00002EC0-00002F3C       .text BG_check__FP8nz_class */
void BG_check(nz_class*) {
    /* Nonmatching */
}

/* 00002F3C-00003090       .text shock_damage_check__FP8nz_class */
void shock_damage_check(nz_class*) {
    /* Nonmatching */
}

/* 00003090-00003240       .text body_atari_check__FP8nz_class */
void body_atari_check(nz_class*) {
    /* Nonmatching */
}

/* 00003240-000042D8       .text nz_move__FP8nz_class */
void nz_move(nz_class*) {
    /* Nonmatching */
}

/* 000042D8-000044B8       .text money_drop__FP8nz_class */
void money_drop(nz_class*) {
    /* Nonmatching */
}

/* 000044B8-0000482C       .text nz2_move__FP8nz_class */
void nz2_move(nz_class*) {
    /* Nonmatching */
}

/* 0000482C-000049E8       .text nz3_move__FP8nz_class */
void nz3_move(nz_class*) {
    /* Nonmatching */
}

/* 000049E8-00005B2C       .text nz4_move__FP8nz_class */
void nz4_move(nz_class*) {
    /* Nonmatching */
}

/* 00005B2C-000061E0       .text nz5_move__FP8nz_class */
void nz5_move(nz_class*) {
    /* Nonmatching */
}

/* 000061E0-000062C8       .text bomb_catch_SUB__FP8nz_class */
void bomb_catch_SUB(nz_class*) {
    /* Nonmatching */
}

/* 000062C8-00006734       .text nezumi_move__FP8nz_classs */
void nezumi_move(nz_class*, short) {
    /* Nonmatching */
}

/* 00006734-000072D8       .text nz6_move__FP8nz_class */
void nz6_move(nz_class*) {
    /* Nonmatching */
}

/* 000072D8-00007B50       .text daNZ_Execute__FP8nz_class */
static BOOL daNZ_Execute(nz_class*) {
    /* Nonmatching */
}

/* 00007B50-00007B58       .text daNZ_IsDelete__FP8nz_class */
static BOOL daNZ_IsDelete(nz_class*) {
    return TRUE;
}

/* 00007B58-00007BE0       .text daNZ_Delete__FP8nz_class */
static BOOL daNZ_Delete(nz_class*) {
    /* Nonmatching */
}

/* 00007BE0-00007EB0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00007EB0-000081AC       .text daNZ_CreateInit__FP8nz_class */
void daNZ_CreateInit(nz_class*) {
    /* Nonmatching */
    static dCcD_SrcCyl body_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK6,
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
            /* Radius */ 50.0f,
            /* Height */ 20.0f,
        }},
    };
}

/* 000081AC-00008294       .text daNZ_Create__FP10fopAc_ac_c */
static cPhs_State daNZ_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daNZ_Method = {
    (process_method_func)daNZ_Create,
    (process_method_func)daNZ_Delete,
    (process_method_func)daNZ_Execute,
    (process_method_func)daNZ_IsDelete,
    (process_method_func)daNZ_Draw,
};

actor_process_profile_definition g_profile_NZ = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NZ,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(nz_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NZ,
    /* Actor SubMtd */ &l_daNZ_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
