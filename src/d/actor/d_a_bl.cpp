/**
 * d_a_bl.cpp
 * Enemy - Bubble
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bl.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 00000078-00000178       .text draw_SUB__FP8bl_class */
void draw_SUB(bl_class*) {
    /* Nonmatching */
}

/* 00000178-000002F8       .text daBL_Draw__FP8bl_class */
static BOOL daBL_Draw(bl_class*) {
    /* Nonmatching */
}

/* 000002F8-000003F8       .text smoke_set__FP8bl_class */
void smoke_set(bl_class*) {
    /* Nonmatching */
}

/* 000003F8-000004AC       .text fire_move_set__FP8bl_class */
void fire_move_set(bl_class*) {
    /* Nonmatching */
}

/* 000004AC-00000578       .text fire_emitter_clr__FP8bl_class */
void fire_emitter_clr(bl_class*) {
    /* Nonmatching */
}

/* 00000578-000006E0       .text fire_kaiten_keisan__FP8bl_class */
void fire_kaiten_keisan(bl_class*) {
    /* Nonmatching */
}

/* 000006E0-00000820       .text shock_damage_check__FP8bl_class */
void shock_damage_check(bl_class*) {
    /* Nonmatching */
}

/* 00000820-0000094C       .text anm_init__FP8bl_classifUcfi */
void anm_init(bl_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 0000094C-00000C08       .text skull_atari_check__FP8bl_class */
void skull_atari_check(bl_class*) {
    /* Nonmatching */
}

/* 00000C44-00001768       .text blue_body_atari_check__FP8bl_class */
void blue_body_atari_check(bl_class*) {
    /* Nonmatching */
}

/* 00001768-000022BC       .text red_body_atari_check__FP8bl_class */
void red_body_atari_check(bl_class*) {
    /* Nonmatching */
}

/* 000022BC-00002354       .text bound_sound_set__FP8bl_class */
void bound_sound_set(bl_class*) {
    /* Nonmatching */
}

/* 00002354-00002458       .text fuwafuwa_keisan__FP8bl_class */
void fuwafuwa_keisan(bl_class*) {
    /* Nonmatching */
}

/* 00002458-000024E4       .text BG_check__FP8bl_class */
void BG_check(bl_class*) {
    /* Nonmatching */
}

/* 000024E4-00002804       .text Line_check__FP8bl_class4cXyz */
void Line_check(bl_class*, cXyz) {
    /* Nonmatching */
}

/* 00002C3C-00002CC4       .text roll_check__FP8bl_class */
void roll_check(bl_class*) {
    /* Nonmatching */
}

/* 00002CC4-00003054       .text way_check__FP8bl_classs */
void way_check(bl_class*, short) {
    /* Nonmatching */
}

/* 00003054-000039F0       .text action_dousa__FP8bl_class */
void action_dousa(bl_class*) {
    /* Nonmatching */
}

/* 000039F0-00003F68       .text action_kougeki__FP8bl_class */
void action_kougeki(bl_class*) {
    /* Nonmatching */
}

/* 00003F68-00004128       .text action_sagarimasu__FP8bl_class */
void action_sagarimasu(bl_class*) {
    /* Nonmatching */
}

/* 00004128-000046BC       .text action_kaze_move__FP8bl_class */
void action_kaze_move(bl_class*) {
    /* Nonmatching */
}

/* 000046BC-00004B84       .text action_itaiyo_ne_san__FP8bl_class */
void action_itaiyo_ne_san(bl_class*) {
    /* Nonmatching */
}

/* 00004B84-00004D3C       .text action_hook_atari__FP8bl_class */
void action_hook_atari(bl_class*) {
    /* Nonmatching */
}

/* 00004D3C-00004DBC       .text action_come_wait__FP8bl_class */
void action_come_wait(bl_class*) {
    /* Nonmatching */
}

/* 00004DBC-00005104       .text action_normal_skull__FP8bl_class */
void action_normal_skull(bl_class*) {
    /* Nonmatching */
}

/* 00005104-00005504       .text daBL_Execute__FP8bl_class */
static BOOL daBL_Execute(bl_class*) {
    /* Nonmatching */
}

/* 00005504-0000550C       .text daBL_IsDelete__FP8bl_class */
static BOOL daBL_IsDelete(bl_class*) {
    return TRUE;
}

/* 0000550C-0000558C       .text daBL_Delete__FP8bl_class */
static BOOL daBL_Delete(bl_class*) {
    /* Nonmatching */
}

/* 0000558C-0000583C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00005884-00005D88       .text daBL_Create__FP10fopAc_ac_c */
static cPhs_State daBL_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph body_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK4,
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

static actor_method_class l_daBL_Method = {
    (process_method_func)daBL_Create,
    (process_method_func)daBL_Delete,
    (process_method_func)daBL_Execute,
    (process_method_func)daBL_IsDelete,
    (process_method_func)daBL_Draw,
};

actor_process_profile_definition g_profile_BL = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BL,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bl_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BL,
    /* Actor SubMtd */ &l_daBL_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
