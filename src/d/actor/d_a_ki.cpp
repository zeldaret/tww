/**
 * d_a_ki.cpp
 * Enemy - Keese
 */

#include "d/actor/d_a_ki.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-000001B4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000001B4-0000023C       .text ki_a_d_sub__FPvPv */
void ki_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 0000023C-0000027C       .text ki_check__FP8ki_class */
void ki_check(ki_class*) {
    /* Nonmatching */
}

/* 0000027C-000003A4       .text anm_init__FP8ki_classifUcfi */
void anm_init(ki_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 000003A4-00000478       .text tex_anm_set__FP8ki_classUs */
void tex_anm_set(ki_class*, unsigned short) {
    /* Nonmatching */
}

/* 00000478-000004C4       .text ki_eye_tex_anm__FP8ki_class */
void ki_eye_tex_anm(ki_class*) {
    /* Nonmatching */
}

/* 000004C4-00000820       .text ki_player_bg_check__FP8ki_class */
void ki_player_bg_check(ki_class*) {
    /* Nonmatching */
}

/* 00000C58-00000F04       .text daKi_Draw__FP8ki_class */
static BOOL daKi_Draw(ki_class*) {
    /* Nonmatching */
}

/* 00000F04-00001118       .text ki_pos_move__FP8ki_classSc */
void ki_pos_move(ki_class*, signed char) {
    /* Nonmatching */
}

/* 00001118-0000171C       .text ki_wait_move__FP8ki_class */
void ki_wait_move(ki_class*) {
    /* Nonmatching */
}

/* 0000171C-00001A34       .text ki_fly_move__FP8ki_class */
void ki_fly_move(ki_class*) {
    /* Nonmatching */
}

/* 00001A34-00001D84       .text ki_fire_set_move__FP8ki_class */
void ki_fire_set_move(ki_class*) {
    /* Nonmatching */
}

/* 00001D84-00002A18       .text ki_atack_move__FP8ki_class */
void ki_atack_move(ki_class*) {
    /* Nonmatching */
}

/* 00002A18-00002E28       .text wall_angle_get__FP8ki_class */
void wall_angle_get(ki_class*) {
    /* Nonmatching */
}

/* 00002E28-00003114       .text ki_damage_move__FP8ki_class */
void ki_damage_move(ki_class*) {
    /* Nonmatching */
}

/* 00003114-00003278       .text ki_fail_move__FP8ki_class */
void ki_fail_move(ki_class*) {
    /* Nonmatching */
}

/* 00003278-000035D0       .text ki_path_move__FP8ki_class */
void ki_path_move(ki_class*) {
    /* Nonmatching */
}

/* 000035D0-00003E04       .text daKi_Execute__FP8ki_class */
static BOOL daKi_Execute(ki_class*) {
    /* Nonmatching */
}

/* 00003E04-00003E0C       .text daKi_IsDelete__FP8ki_class */
static BOOL daKi_IsDelete(ki_class*) {
    return TRUE;
}

/* 00003E0C-00003EB8       .text daKi_Delete__FP8ki_class */
static BOOL daKi_Delete(ki_class*) {
    /* Nonmatching */
}

/* 00003EB8-000042B8       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00004364-000046F4       .text daKi_Create__FP10fopAc_ac_c */
static cPhs_State daKi_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
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
            /* Radius */ 30.0f,
        },
    };
    static dCcD_SrcSph tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 40.0f,
        },
    };
    static dCcD_SrcSph co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsPlayer_e,
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
            /* Radius */ 80.0f,
        },
    };
}

static actor_method_class l_daKi_Method = {
    (process_method_func)daKi_Create,
    (process_method_func)daKi_Delete,
    (process_method_func)daKi_Execute,
    (process_method_func)daKi_IsDelete,
    (process_method_func)daKi_Draw,
};

actor_process_profile_definition g_profile_KI = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KI,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(ki_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KI,
    /* Actor SubMtd */ &l_daKi_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
