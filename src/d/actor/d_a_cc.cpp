/**
 * d_a_cc.cpp
 * Enemy - ChuChu
 */

#include "d/actor/d_a_cc.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 00000078-000002AC       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000002E8-00000524       .text draw_SUB__FP8cc_class */
void draw_SUB(cc_class*) {
    /* Nonmatching */
}

/* 00000524-00000900       .text daCC_Draw__FP8cc_class */
static BOOL daCC_Draw(cc_class*) {
    /* Nonmatching */
}

/* 00000900-00000AB0       .text cc_eff_set__FP8cc_classUc */
void cc_eff_set(cc_class*, unsigned char) {
    /* Nonmatching */
}

/* 00000AB0-00000BDC       .text anm_init__FP8cc_classifUcfi */
void anm_init(cc_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00000BDC-00000C74       .text damage_mode_move__FP8cc_class */
void damage_mode_move(cc_class*) {
    /* Nonmatching */
}

/* 00000C74-00000D30       .text s_b_sub__FPvPv */
void s_b_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000D30-00001028       .text naraku_check__FP8cc_class */
void naraku_check(cc_class*) {
    /* Nonmatching */
}

/* 00001028-00001068       .text denki_start__FP8cc_class */
void denki_start(cc_class*) {
    /* Nonmatching */
}

/* 00001068-000010D8       .text denki_end__FP8cc_class */
void denki_end(cc_class*) {
    /* Nonmatching */
}

/* 000010D8-00001344       .text shock_damage_check__FP8cc_class */
void shock_damage_check(cc_class*) {
    /* Nonmatching */
}

/* 00001344-000013B8       .text black_light_check__FP8cc_class */
void black_light_check(cc_class*) {
    /* Nonmatching */
}

/* 000013B8-00001F78       .text body_atari_check__FP8cc_class */
void body_atari_check(cc_class*) {
    /* Nonmatching */
}

/* 00001F78-00002180       .text search_angle_set__FP8cc_class */
void search_angle_set(cc_class*) {
    /* Nonmatching */
}

/* 00002180-00002A20       .text action_nomal_move__FP8cc_class */
void action_nomal_move(cc_class*) {
    /* Nonmatching */
}

/* 00002A20-00002E24       .text action_oyogu__FP8cc_class */
void action_oyogu(cc_class*) {
    /* Nonmatching */
}

/* 00002E24-000032A0       .text action_attack_move__FP8cc_class */
void action_attack_move(cc_class*) {
    /* Nonmatching */
}

/* 000032A0-00003C58       .text action_damage_move__FP8cc_class */
void action_damage_move(cc_class*) {
    /* Nonmatching */
}

/* 00003C58-000040E4       .text action_dead_move__FP8cc_class */
void action_dead_move(cc_class*) {
    /* Nonmatching */
}

/* 000040E4-000042E8       .text deku_come_demo__FP8cc_class */
void deku_come_demo(cc_class*) {
    /* Nonmatching */
}

/* 000042E8-00004518       .text deku_ret_demo__FP8cc_class */
void deku_ret_demo(cc_class*) {
    /* Nonmatching */
}

/* 00004518-00004CAC       .text action_noboru__FP8cc_class */
void action_noboru(cc_class*) {
    /* Nonmatching */
}

/* 00004CAC-0000561C       .text action_up_check__FP8cc_class */
void action_up_check(cc_class*) {
    /* Nonmatching */
}

/* 0000561C-000056CC       .text action_tomaru__FP8cc_class */
void action_tomaru(cc_class*) {
    /* Nonmatching */
}

/* 000056CC-00005778       .text tsubo_search__FPvPv */
void tsubo_search(void*, void*) {
    /* Nonmatching */
}

/* 00005778-000059B8       .text action_tubo_search__FP8cc_class */
void action_tubo_search(cc_class*) {
    /* Nonmatching */
}

/* 000059B8-00005A58       .text BG_check__FP8cc_class */
void BG_check(cc_class*) {
    /* Nonmatching */
}

/* 00005A58-00006214       .text daCC_Execute__FP8cc_class */
static BOOL daCC_Execute(cc_class*) {
    /* Nonmatching */
}

/* 00006214-0000621C       .text daCC_IsDelete__FP8cc_class */
static BOOL daCC_IsDelete(cc_class*) {
    return TRUE;
}

/* 0000621C-00006290       .text daCC_Delete__FP8cc_class */
static BOOL daCC_Delete(cc_class*) {
    /* Nonmatching */
}

/* 00006290-00006A2C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00006A74-00007160       .text daCC_Create__FP10fopAc_ac_c */
static cPhs_State daCC_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcCyl body_co_cyl = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK2000,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsOther_e,
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
        // cM3dGCylS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        },
    };
}

static actor_method_class l_daCC_Method = {
    (process_method_func)daCC_Create,
    (process_method_func)daCC_Delete,
    (process_method_func)daCC_Execute,
    (process_method_func)daCC_IsDelete,
    (process_method_func)daCC_Draw,
};

actor_process_profile_definition g_profile_CC = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_CC,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(cc_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_CC,
    /* Actor SubMtd */ &l_daCC_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
