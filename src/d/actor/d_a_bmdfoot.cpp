/**
 * d_a_bmdfoot.cpp
 * Boss - Kalle Demos (floor tentacles)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bmdfoot.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-00000114       .text __ct__15daBmdfoot_HIO_cFv */
daBmdfoot_HIO_c::daBmdfoot_HIO_c() {
    /* Nonmatching */
}

/* 00000114-000001D8       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000001D8-000002B0       .text daBmdfoot_Draw__FP13bmdfoot_class */
static BOOL daBmdfoot_Draw(bmdfoot_class*) {
    /* Nonmatching */
}

/* 000002B0-000003D8       .text anm_init__FP13bmdfoot_classifUcfi */
void anm_init(bmdfoot_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 000003D8-00000440       .text housi_off__FP13bmdfoot_class */
void housi_off(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00000440-00000840       .text wait__FP13bmdfoot_class */
void wait(bmdfoot_class*) {
    /* Nonmatching */
}

/* 0000087C-00000D8C       .text attack_1__FP13bmdfoot_class */
void attack_1(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00000D8C-00001180       .text ug_move__FP13bmdfoot_class */
void ug_move(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00001180-00001B00       .text attack_2__FP13bmdfoot_class */
void attack_2(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00001B00-00001CDC       .text damage__FP13bmdfoot_class */
void damage(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00001CDC-00001ED8       .text start__FP13bmdfoot_class */
void start(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00001ED8-00001FB8       .text end__FP13bmdfoot_class */
void end(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00001FB8-000021B8       .text move__FP13bmdfoot_class */
void move(bmdfoot_class*) {
    /* Nonmatching */
}

/* 000021B8-00002204       .text s_a_d_sub__FPvPv */
void s_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 00002204-00002594       .text daBmdfoot_Execute__FP13bmdfoot_class */
static BOOL daBmdfoot_Execute(bmdfoot_class*) {
    /* Nonmatching */
}

/* 00002594-0000259C       .text daBmdfoot_IsDelete__FP13bmdfoot_class */
static BOOL daBmdfoot_IsDelete(bmdfoot_class*) {
    return TRUE;
}

/* 0000259C-000026B0       .text daBmdfoot_Delete__FP13bmdfoot_class */
static BOOL daBmdfoot_Delete(bmdfoot_class*) {
    /* Nonmatching */
}

/* 000026B0-000029B4       .text useHeapInit__FP13bmdfoot_class */
void useHeapInit(bmdfoot_class*) {
    /* Nonmatching */
}

/* 000029FC-00002A1C       .text solidHeapCB__FP10fopAc_ac_c */
static BOOL solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002A1C-00002E88       .text daBmdfoot_Create__FP10fopAc_ac_c */
static cPhs_State daBmdfoot_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };
}

static actor_method_class l_daBmdfoot_Method = {
    (process_method_func)daBmdfoot_Create,
    (process_method_func)daBmdfoot_Delete,
    (process_method_func)daBmdfoot_Execute,
    (process_method_func)daBmdfoot_IsDelete,
    (process_method_func)daBmdfoot_Draw,
};

actor_process_profile_definition g_profile_BMDFOOT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BMDFOOT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bmdfoot_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BMDFOOT,
    /* Actor SubMtd */ &l_daBmdfoot_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
