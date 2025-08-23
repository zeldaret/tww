/**
 * d_a_wz.cpp
 * Enemy - Wizzrobe / Mini-Boss - Wizzrobe (Wind Temple)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_wz.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 00000078-00000140       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000140-00000208       .text rod_nodeCallBack__FP7J3DNodei */
static BOOL rod_nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000208-00000360       .text draw_SUB__FP8wz_class */
void draw_SUB(wz_class*) {
    /* Nonmatching */
}

/* 00000360-000006D0       .text hontai_draw__FP8wz_class */
void hontai_draw(wz_class*) {
    /* Nonmatching */
}

/* 000006D0-0000074C       .text summon_door_draw__FP8wz_class */
void summon_door_draw(wz_class*) {
    /* Nonmatching */
}

/* 0000074C-00000814       .text damage_ball_draw__FP8wz_class */
static BOOL damage_ball_draw(wz_class*) {
    /* Nonmatching */
}

/* 00000814-000008C0       .text daWZ_Draw__FP8wz_class */
static BOOL daWZ_Draw(wz_class*) {
    /* Nonmatching */
}

/* 000008C0-000009EC       .text anm_init__FP8wz_classifUcfi */
void anm_init(wz_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 000009EC-00000A58       .text rod_size_set__FP8wz_classUc */
void rod_size_set(wz_class*, unsigned char) {
    /* Nonmatching */
}

/* 00000A58-00001258       .text body_atari_check__FP8wz_class */
void body_atari_check(wz_class*) {
    /* Nonmatching */
}

/* 00001258-000012F0       .text BG_check__FP8wz_class */
void BG_check(wz_class*) {
    /* Nonmatching */
}

/* 00001728-00001780       .text fuwafuwa_calc__FP8wz_class */
void fuwafuwa_calc(wz_class*) {
    /* Nonmatching */
}

/* 00001780-00001B38       .text weapon_shoot__FP8wz_classUc */
void weapon_shoot(wz_class*, unsigned char) {
    /* Nonmatching */
}

/* 00001B38-00002528       .text action_dousa__FP8wz_class */
void action_dousa(wz_class*) {
    /* Nonmatching */
}

/* 00002528-00002E3C       .text action_itai__FP8wz_class */
void action_itai(wz_class*) {
    /* Nonmatching */
}

/* 00002E3C-000047C8       .text action_demo__FP8wz_class */
void action_demo(wz_class*) {
    /* Nonmatching */
}

/* 000047C8-00004810       .text next_tama_move__FP8wz_class4cXyz */
void next_tama_move(wz_class*, cXyz) {
    /* Nonmatching */
}

/* 00004810-00004BF4       .text summon_call_sub__FP8wz_class */
void summon_call_sub(wz_class*) {
    /* Nonmatching */
}

/* 00004BF4-00004D18       .text sea_water_check__FP8wz_class */
void sea_water_check(wz_class*) {
    /* Nonmatching */
}

/* 00004D18-00005760       .text action_tama_dousa__FP8wz_class */
void action_tama_dousa(wz_class*) {
    /* Nonmatching */
}

/* 00005760-00005B64       .text action_summon_dousa__FP8wz_class */
void action_summon_dousa(wz_class*) {
    /* Nonmatching */
}

/* 00005B64-00006108       .text daWZ_Execute__FP8wz_class */
static BOOL daWZ_Execute(wz_class*) {
    /* Nonmatching */
}

/* 00006108-00006110       .text daWZ_IsDelete__FP8wz_class */
static BOOL daWZ_IsDelete(wz_class*) {
    return TRUE;
}

/* 00006110-0000627C       .text daWZ_Delete__FP8wz_class */
static BOOL daWZ_Delete(wz_class*) {
    /* Nonmatching */
}

/* 0000627C-00006684       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000066CC-00006888       .text useHeapInit2__FP10fopAc_ac_c */
static BOOL useHeapInit2(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00006888-000071C4       .text daWZ_Create__FP10fopAc_ac_c */
static cPhs_State daWZ_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcCyl body_co_cyl_src = {
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcSph ball_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
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

static actor_method_class l_daWZ_Method = {
    (process_method_func)daWZ_Create,
    (process_method_func)daWZ_Delete,
    (process_method_func)daWZ_Execute,
    (process_method_func)daWZ_IsDelete,
    (process_method_func)daWZ_Draw,
};

actor_process_profile_definition g_profile_WZ = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_WZ,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(wz_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_WZ,
    /* Actor SubMtd */ &l_daWZ_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
