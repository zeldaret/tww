/**
 * d_a_ph.cpp
 * Enemy - Peahat/Seahat
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_ph.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 00000078-00000158       .text nodeCallBack_UP__FP7J3DNodei */
static BOOL nodeCallBack_UP(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000158-0000025C       .text nodeCallBack_DW__FP7J3DNodei */
static BOOL nodeCallBack_DW(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000025C-000003FC       .text daPH_Draw__FP8ph_class */
static BOOL daPH_Draw(ph_class*) {
    /* Nonmatching */
}

/* 000003FC-000007C0       .text anm_init__FP8ph_classifUcfii */
void anm_init(ph_class*, int, float, unsigned char, float, int, int) {
    /* Nonmatching */
}

/* 000007C0-0000097C       .text puropera_sound__FP8ph_class */
void puropera_sound(ph_class*) {
    /* Nonmatching */
}

/* 0000097C-00000AE4       .text zaisitu_sound__FP8ph_classP8cCcD_Obj */
void zaisitu_sound(ph_class*, cCcD_Obj*) {
    /* Nonmatching */
}

/* 00000AE4-00000B4C       .text puropera_kaiten__FP8ph_class */
void puropera_kaiten(ph_class*) {
    /* Nonmatching */
}

/* 00000B4C-00000D2C       .text fuwafuwa_set__FP8ph_class */
void fuwafuwa_set(ph_class*) {
    /* Nonmatching */
}

/* 00000D2C-000011F4       .text fly_angle_set__FP8ph_classUc */
void fly_angle_set(ph_class*, unsigned char) {
    /* Nonmatching */
}

/* 000011F4-00001A10       .text body_atari_check__FP8ph_class */
void body_atari_check(ph_class*) {
    /* Nonmatching */
}

/* 00001A10-00001C18       .text hajiki_check__FP8ph_class */
void hajiki_check(ph_class*) {
    /* Nonmatching */
}

/* 00001C18-00001C90       .text ph_wall_hit_check__FP8ph_class */
void ph_wall_hit_check(ph_class*) {
    /* Nonmatching */
}

/* 00001C90-00001E10       .text ph_hani_check__FP8ph_classffUc */
void ph_hani_check(ph_class*, float, float, unsigned char) {
    /* Nonmatching */
}

/* 00001E10-00001F0C       .text shibuki_set__FP8ph_class4cXyzf */
void shibuki_set(ph_class*, cXyz, float) {
    /* Nonmatching */
}

/* 00001F0C-00002318       .text sea_water_check__FP8ph_classUc */
void sea_water_check(ph_class*, unsigned char) {
    /* Nonmatching */
}

/* 00002318-0000263C       .text ph_fly_move__FP8ph_class */
void ph_fly_move(ph_class*) {
    /* Nonmatching */
}

/* 0000263C-00002E18       .text ph_fly_sea_move__FP8ph_class */
void ph_fly_sea_move(ph_class*) {
    /* Nonmatching */
}

/* 00002E18-00002F50       .text ph_hane_move__FP8ph_class */
void ph_hane_move(ph_class*) {
    /* Nonmatching */
}

/* 00002F50-00003768       .text ph_bunri_move__FP8ph_class */
void ph_bunri_move(ph_class*) {
    /* Nonmatching */
}

/* 00003768-00003F34       .text ph_fujyou_move__FP8ph_class */
void ph_fujyou_move(ph_class*) {
    /* Nonmatching */
}

/* 00003F34-0000405C       .text dead_item__FP8ph_class */
void dead_item(ph_class*) {
    /* Nonmatching */
}

/* 0000405C-00004988       .text ph_damage_dead_move__FP8ph_class */
void ph_damage_dead_move(ph_class*) {
    /* Nonmatching */
}

/* 00004988-00005134       .text ph_wind_move__FP8ph_class */
void ph_wind_move(ph_class*) {
    /* Nonmatching */
}

/* 00005134-00005628       .text ph_water_move__FP8ph_class */
void ph_water_move(ph_class*) {
    /* Nonmatching */
}

/* 00005628-0000573C       .text BG_check__FP8ph_class */
void BG_check(ph_class*) {
    /* Nonmatching */
}

/* 0000573C-0000583C       .text UP_draw_SUB__FP8ph_class */
void UP_draw_SUB(ph_class*) {
    /* Nonmatching */
}

/* 0000583C-0000591C       .text DW_draw_SUB__FP8ph_class */
void DW_draw_SUB(ph_class*) {
    /* Nonmatching */
}

/* 0000591C-000061A4       .text daPH_Execute__FP8ph_class */
static BOOL daPH_Execute(ph_class*) {
    /* Nonmatching */
}

/* 000061A4-000061AC       .text daPH_IsDelete__FP8ph_class */
static BOOL daPH_IsDelete(ph_class*) {
    return TRUE;
}

/* 000061AC-00006224       .text daPH_Delete__FP8ph_class */
static BOOL daPH_Delete(ph_class*) {
    /* Nonmatching */
}

/* 00006224-000062B4       .text useArrowHeapInit__FP10fopAc_ac_c */
static BOOL useArrowHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000062B4-00006700       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00006700-00006D1C       .text daPH_Create__FP10fopAc_ac_c */
static cPhs_State daPH_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcCyl at_hit_puropera_co_cyl = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK8,
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
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcCyl tg_hit_puropera_co_cyl = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_NoTgHitInfSet_e,
            /* SrcObjTg  Type    */ AT_TYPE_SWORD | AT_TYPE_WIND,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsPlayer_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcSph body_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK2000,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };
}

static actor_method_class l_daPH_Method = {
    (process_method_func)daPH_Create,
    (process_method_func)daPH_Delete,
    (process_method_func)daPH_Execute,
    (process_method_func)daPH_IsDelete,
    (process_method_func)daPH_Draw,
};

actor_process_profile_definition g_profile_PH = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_PH,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(ph_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_PH,
    /* Actor SubMtd */ &l_daPH_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
