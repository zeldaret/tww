/**
 * d_a_mt.cpp
 * Enemy - Magtail
 */

#include "d/actor/d_a_mt.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-000001E8       .text __ct__10daMt_HIO_cFv */
daMt_HIO_c::daMt_HIO_c() {
    /* Nonmatching */
}

/* 00000230-000002D8       .text anm_init__FP8mt_classifUcfi */
void anm_init(mt_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 000002D8-00000350       .text mt_a_d_sub__FPvPv */
void mt_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000350-00000390       .text mt_check__FP8mt_class */
void mt_check(mt_class*) {
    /* Nonmatching */
}

/* 00000390-00000478       .text mt_bg_check__FP8mt_class */
void mt_bg_check(mt_class*) {
    /* Nonmatching */
}

/* 00000478-0000053C       .text tex_anm_set__FP8mt_classUs */
void tex_anm_set(mt_class*, unsigned short) {
    /* Nonmatching */
}

/* 0000053C-000005EC       .text mt_eye_tex_anm__FP8mt_class */
void mt_eye_tex_anm(mt_class*) {
    /* Nonmatching */
}

/* 000005EC-00000720       .text nodeCallBack_head__FP7J3DNodei */
static BOOL nodeCallBack_head(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000075C-0000098C       .text nodeCallBack_body__FP7J3DNodei */
static BOOL nodeCallBack_body(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000098C-00000B28       .text nodeCallBack_tail__FP7J3DNodei */
static BOOL nodeCallBack_tail(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000B28-0000171C       .text body_control2__FP8mt_class */
void body_control2(mt_class*) {
    /* Nonmatching */
}

/* 00001B54-00001E44       .text wall_check_sub__FP8mt_classP4cXyzP4cXyz */
void wall_check_sub(mt_class*, cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00001E44-00001F10       .text body_wall_check__FP8mt_class */
void body_wall_check(mt_class*) {
    /* Nonmatching */
}

/* 00001F10-000022D8       .text body_control1__FP8mt_class */
void body_control1(mt_class*) {
    /* Nonmatching */
}

/* 000022D8-000028BC       .text body_control3__FP8mt_class */
void body_control3(mt_class*) {
    /* Nonmatching */
}

/* 000028BC-00002AB0       .text body_control4__FP8mt_class */
void body_control4(mt_class*) {
    /* Nonmatching */
}

/* 00002AB0-00003008       .text body_control5__FP8mt_class */
void body_control5(mt_class*) {
    /* Nonmatching */
}

/* 00003008-00003210       .text br_draw__FP8mt_class */
void br_draw(mt_class*) {
    /* Nonmatching */
}

/* 00003210-00003360       .text daMt_shadowDraw__FP8mt_class */
static void daMt_shadowDraw(mt_class*) {
    /* Nonmatching */
}

/* 00003360-0000361C       .text daMt_Draw__FP8mt_class */
static BOOL daMt_Draw(mt_class*) {
    /* Nonmatching */
}

/* 0000361C-000037B0       .text bakuha__FP8mt_class */
void bakuha(mt_class*) {
    /* Nonmatching */
}

/* 000037B0-000042C4       .text mt_move__FP8mt_class */
void mt_move(mt_class*) {
    /* Nonmatching */
}

/* 000042C4-00005088       .text mt_fight__FP8mt_class */
void mt_fight(mt_class*) {
    /* Nonmatching */
}

/* 00005088-00005A04       .text mt_move_maru__FP8mt_class */
void mt_move_maru(mt_class*) {
    /* Nonmatching */
}

/* 00005B9C-00005C54       .text water_damage_se_set__FP8mt_class */
void water_damage_se_set(mt_class*) {
    /* Nonmatching */
}

/* 00005C54-0000614C       .text damage_check__FP8mt_class */
void damage_check(mt_class*) {
    /* Nonmatching */
}

/* 00006188-000074D4       .text daMt_Execute__FP8mt_class */
static BOOL daMt_Execute(mt_class*) {
    /* Nonmatching */
}

/* 00007CC4-00007CCC       .text daMt_IsDelete__FP8mt_class */
static BOOL daMt_IsDelete(mt_class*) {
    /* Nonmatching */
}

/* 00007CCC-00007E18       .text daMt_Delete__FP8mt_class */
static BOOL daMt_Delete(mt_class*) {
    /* Nonmatching */
}

/* 00007E18-00008400       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000084AC-000088A8       .text daMt_Create__FP10fopAc_ac_c */
static cPhs_State daMt_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph eye_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 30.0f,
        },
    };
}

static actor_method_class l_daMt_Method = {
    (process_method_func)daMt_Create,
    (process_method_func)daMt_Delete,
    (process_method_func)daMt_Execute,
    (process_method_func)daMt_IsDelete,
    (process_method_func)daMt_Draw,
};

actor_process_profile_definition g_profile_MT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mt_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MT,
    /* Actor SubMtd */ &l_daMt_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e | fopAcStts_UNK8000000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
