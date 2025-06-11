/**
 * d_a_bmdhand.cpp
 * Boss - Kalle Demos (ceiling tentacles)
 */

#include "d/actor/d_a_bmdhand.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-00000118       .text __ct__15daBmdhand_HIO_cFv */
daBmdhand_HIO_c::daBmdhand_HIO_c() {
    /* Nonmatching */
}

/* 00000118-000001CC       .text hand_draw__FP13bmdhand_class */
void hand_draw(bmdhand_class*) {
    /* Nonmatching */
}

/* 000001CC-0000022C       .text daBmdhand_Draw__FP13bmdhand_class */
static BOOL daBmdhand_Draw(bmdhand_class*) {
    /* Nonmatching */
}

/* 0000022C-00000310       .text hand_mtx_set__FP13bmdhand_class */
void hand_mtx_set(bmdhand_class*) {
    /* Nonmatching */
}

/* 00000310-00000388       .text control3__FP13bmdhand_class */
void control3(bmdhand_class*) {
    /* Nonmatching */
}

/* 00000388-000006E4       .text control1__FP13bmdhand_class */
void control1(bmdhand_class*) {
    /* Nonmatching */
}

/* 000006E4-00000A1C       .text control2__FP13bmdhand_class */
void control2(bmdhand_class*) {
    /* Nonmatching */
}

/* 00000A1C-00000EFC       .text cut_control__FP13bmdhand_class */
void cut_control(bmdhand_class*) {
    /* Nonmatching */
}

/* 00000EFC-00000FAC       .text cut_control3__FP13bmdhand_class */
void cut_control3(bmdhand_class*) {
    /* Nonmatching */
}

/* 00000FAC-000012DC       .text start_control1__FP13bmdhand_class */
void start_control1(bmdhand_class*) {
    /* Nonmatching */
}

/* 000012DC-0000158C       .text start_control2__FP13bmdhand_class */
void start_control2(bmdhand_class*) {
    /* Nonmatching */
}

/* 0000158C-0000161C       .text hand_close__FP13bmdhand_class */
void hand_close(bmdhand_class*) {
    /* Nonmatching */
}

/* 0000161C-000016AC       .text hand_open__FP13bmdhand_class */
void hand_open(bmdhand_class*) {
    /* Nonmatching */
}

/* 000016AC-00001D30       .text hand_calc__FP13bmdhand_class */
void hand_calc(bmdhand_class*) {
    /* Nonmatching */
}

/* 00002168-000025D4       .text start_hand_calc__FP13bmdhand_class */
void start_hand_calc(bmdhand_class*) {
    /* Nonmatching */
}

/* 000025D4-00002E74       .text hand_move__FP13bmdhand_class */
void hand_move(bmdhand_class*) {
    /* Nonmatching */
}

/* 00002E74-00002EC0       .text s_a_d_sub__FPvPv */
void s_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 00002EC0-00003028       .text daBmdhand_Execute__FP13bmdhand_class */
static BOOL daBmdhand_Execute(bmdhand_class*) {
    /* Nonmatching */
}

/* 00003028-00003030       .text daBmdhand_IsDelete__FP13bmdhand_class */
static BOOL daBmdhand_IsDelete(bmdhand_class*) {
    return TRUE;
}

/* 00003030-000030C4       .text daBmdhand_Delete__FP13bmdhand_class */
static BOOL daBmdhand_Delete(bmdhand_class*) {
    /* Nonmatching */
}

/* 000030C4-00003210       .text useHeapInit__FP13bmdhand_class */
void useHeapInit(bmdhand_class*) {
    /* Nonmatching */
}

/* 00003210-00003230       .text solidHeapCB__FP10fopAc_ac_c */
static BOOL solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00003230-000034FC       .text daBmdhand_Create__FP10fopAc_ac_c */
static cPhs_State daBmdhand_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
            /* Radius */ 100.0f,
        },
    };
}

static actor_method_class l_daBmdhand_Method = {
    (process_method_func)daBmdhand_Create,
    (process_method_func)daBmdhand_Delete,
    (process_method_func)daBmdhand_Execute,
    (process_method_func)daBmdhand_IsDelete,
    (process_method_func)daBmdhand_Draw,
};

actor_process_profile_definition g_profile_BMDHAND = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BMDHAND,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bmdhand_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BMDHAND,
    /* Actor SubMtd */ &l_daBmdhand_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
