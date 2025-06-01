/**
 * d_a_bb.cpp
 * Enemy - Kargaroc
 */

#include "d/actor/d_a_bb.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-000003C8       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000404-000009A4       .text tail_control__FP8bb_class */
void tail_control(bb_class*) {
    /* Nonmatching */
}

/* 000009A4-00000A94       .text tail_draw__FP8bb_class */
void tail_draw(bb_class*) {
    /* Nonmatching */
}

/* 00000A94-00000B90       .text tex_anm_set__FP8bb_classUs */
void tex_anm_set(bb_class*, unsigned short) {
    /* Nonmatching */
}

/* 00000B90-00000C40       .text bb_eye_tex_anm__FP8bb_class */
void bb_eye_tex_anm(bb_class*) {
    /* Nonmatching */
}

/* 00000C40-00000D74       .text anm_init__FP8bb_classifUcfi */
void anm_init(bb_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00000D74-00001048       .text s_a_d_sub__FPvPv */
void s_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001480-000015D4       .text search_esa__FP8bb_class */
void search_esa(bb_class*) {
    /* Nonmatching */
}

/* 000015D4-000015F4       .text kuti_open__FP8bb_classsUl */
void kuti_open(bb_class*, short, unsigned long) {
    /* Nonmatching */
}

/* 000015F4-00001928       .text bb_player_bg_check__FP8bb_class */
void bb_player_bg_check(bb_class*) {
    /* Nonmatching */
}

/* 00001928-00001C50       .text bb_setpos_bg_check__FP8bb_class */
void bb_setpos_bg_check(bb_class*) {
    /* Nonmatching */
}

/* 00001C50-00001DF8       .text bb_player_view_check__FP8bb_class */
void bb_player_view_check(bb_class*) {
    /* Nonmatching */
}

/* 00001DF8-00002250       .text path_check__FP8bb_class */
void path_check(bb_class*) {
    /* Nonmatching */
}

/* 00002250-0000234C       .text daBb_shadowDraw__FP8bb_class */
static void daBb_shadowDraw(bb_class*) {
    /* Nonmatching */
}

/* 0000234C-00002444       .text daBb_Draw__FP8bb_class */
static BOOL daBb_Draw(bb_class*) {
    /* Nonmatching */
}

/* 00002444-00002708       .text bb_pos_move__FP8bb_class */
void bb_pos_move(bb_class*) {
    /* Nonmatching */
}

/* 00002708-00002854       .text bb_ground_pos_move__FP8bb_class */
void bb_ground_pos_move(bb_class*) {
    /* Nonmatching */
}

/* 00002854-00003224       .text bb_path_move__FP8bb_class */
void bb_path_move(bb_class*) {
    /* Nonmatching */
}

/* 00003224-00003F88       .text bb_auto_move__FP8bb_class */
void bb_auto_move(bb_class*) {
    /* Nonmatching */
}

/* 00003F88-00004000       .text bb_water_check__FP8bb_class */
void bb_water_check(bb_class*) {
    /* Nonmatching */
}

/* 00004000-0000404C       .text pl_name_check__FPvPv */
void pl_name_check(void*, void*) {
    /* Nonmatching */
}

/* 0000404C-000044EC       .text bb_kamome_attack__FP8bb_class */
void bb_kamome_attack(bb_class*) {
    /* Nonmatching */
}

/* 000044EC-00005534       .text bb_atack_move__FP8bb_class */
void bb_atack_move(bb_class*) {
    /* Nonmatching */
}

/* 00005534-00005BB4       .text bb_wait_move__FP8bb_class */
void bb_wait_move(bb_class*) {
    /* Nonmatching */
}

/* 00005BB4-00006234       .text bb_su_wait_move__FP8bb_class */
void bb_su_wait_move(bb_class*) {
    /* Nonmatching */
}

/* 00006234-00006278       .text bb_fail_move__FP8bb_class */
void bb_fail_move(bb_class*) {
    /* Nonmatching */
}

/* 00006278-0000696C       .text damage_check__FP8bb_class */
void damage_check(bb_class*) {
    /* Nonmatching */
}

/* 000069A8-00007778       .text daBb_Execute__FP8bb_class */
static BOOL daBb_Execute(bb_class*) {
    /* Nonmatching */
}

/* 00007778-00007780       .text daBb_IsDelete__FP8bb_class */
static BOOL daBb_IsDelete(bb_class*) {
    /* Nonmatching */
}

/* 00007780-000077EC       .text daBb_Delete__FP8bb_class */
static BOOL daBb_Delete(bb_class*) {
    /* Nonmatching */
}

/* 000077EC-00007A68       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00007A68-00007F58       .text daBb_Create__FP10fopAc_ac_c */
static cPhs_State daBb_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph head_at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
            /* Radius */ 62.5f,
        },
    };
    static dCcD_SrcSph head_tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 62.5f,
        },
    };
    static dCcD_SrcSph body_tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 62.5f,
        },
    };
    static dCcD_SrcSph body_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
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
            /* Radius */ 87.5f,
        },
    };
}

static actor_method_class l_daBb_Method = {
    (process_method_func)daBb_Create,
    (process_method_func)daBb_Delete,
    (process_method_func)daBb_Execute,
    (process_method_func)daBb_IsDelete,
    (process_method_func)daBb_Draw,
};

actor_process_profile_definition g_profile_BB = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BB,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bb_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BB,
    /* Actor SubMtd */ &l_daBb_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
