/**
 * d_a_sss.cpp
 * Enemy - Dexivine (Forbidden Woods, Wind Temple)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_sss.h"
#include "d/d_cc_d.h"
#include "res/Object/Sss.h"

f32 size_d[10] = {10, 10, 9.5, 9.0, 8.5, 8.0, 7.5, 7.0, 6.5, 6.5};
cXyz non_pos;

/* 000000EC-000001F0       .text hand_draw__FP9sss_class */
void hand_draw(sss_class*) {
    /* Nonmatching */
}

/* 000001F0-00000248       .text daSss_Draw__FP9sss_class */
static BOOL daSss_Draw(sss_class* i_this) {
    /* Nonmatching */
    if (i_this->field_0x2B8 != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->eyePos, &i_this->tevStr);
        hand_draw(i_this);
    }
    return TRUE;
}

/* 00000248-000002C8       .text hand_close__FP9sss_class */
void hand_close(sss_class* i_this) {
    /* Nonmatching */
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_TOJIRU_e);
    i_this->field_0x2B4->setAnm(anm, 0, 1, 1, 0, -1, NULL);
}

/* 000002C8-00000348       .text hand_open__FP9sss_class */
void hand_open(sss_class* i_this) {
    /* Nonmatching */
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e);
    i_this->field_0x2B4->setAnm(anm, 0, 1, 1, 0, -1, NULL);
}

/* 00000348-00000444       .text hand_mtx_set__FP9sss_class */
void hand_mtx_set(sss_class*) {
    /* Nonmatching */
}

/* 00000444-000004CC       .text control3__FP9sss_class */
void control3(sss_class* i_this) {
    /* Nonmatching */
    int iVar1;
    int iVar2;
    sss_s* pcVar3;
    int iVar4;

    pcVar3 = i_this->field_0x33C;
    iVar1 = 0;
    iVar2 = 0;
    for (iVar4 = 10; iVar4 != 0; iVar4--) {
        pcVar3->field_0x18 = (JMASSin(i_this->field_0x2BC * 500 + iVar2) * 0.1 + 0.8) * size_d[iVar1];
        iVar1 = iVar1 + 4;
        iVar2 = iVar2 + 100;
        pcVar3 = pcVar3 + 1;
    }
}

/* 000004CC-00000804       .text control1__FP9sss_class */
void control1(sss_class*) {
    /* Nonmatching */
}

/* 00000840-00000B0C       .text control2__FP9sss_class */
void control2(sss_class*) {
    /* Nonmatching */
}

/* 00000B0C-00000F78       .text cut_control1__FP9sss_class */
void cut_control1(sss_class*) {
    /* Nonmatching */
}

/* 00000F78-000014F4       .text cut_control2__FP9sss_class */
void cut_control2(sss_class*) {
    /* Nonmatching */
}

/* 000014F4-00002614       .text hand_move__FP9sss_class */
void hand_move(sss_class*) {
    /* Nonmatching */
}

/* 00002614-00002618       .text hand_main__FP9sss_class */
void hand_main(sss_class*) {
    /* Nonmatching */
}

/* 00002618-0000269C       .text daSss_Execute__FP9sss_class */
static BOOL daSss_Execute(sss_class* i_this) {
    /* Nonmatching */
    int j;

    i_this->field_0x2BC = i_this->field_0x2BC + 1;
    j = 0;
    for (int i = 2; i != 0; i--) {
        if (i_this->field_0x2C2[j] != '\0') {
            i_this->field_0x2C2[j] = i_this->field_0x2C2[j] - 1;
        }
        j = j + 1;
    }
    if (i_this->field_0x2C2[2] != '\0') {
        i_this->field_0x2C2[2] = i_this->field_0x2C2[2] - 1;
    }
    if (!i_this->field_0x2B8) {
        hand_main(i_this);
    } else {
        hand_move(i_this);
    }
    return TRUE;
}

/* 0000269C-000026A4       .text daSss_IsDelete__FP9sss_class */
static BOOL daSss_IsDelete(sss_class*) {
    return TRUE;
}

/* 000026A4-00002720       .text daSss_Delete__FP9sss_class */
static BOOL daSss_Delete(sss_class* i_this) {
    /* Nonmatching */
    dComIfG_resDelete(&i_this->field_0x2AC, "Sss");
    JPABaseEmitter* emitter = i_this->field_0xA10;
    if (emitter) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(JPAEmtrStts_StopEmit);
    }
    emitter = i_this->field_0xA14;
    if (emitter) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(JPAEmtrStts_StopEmit);
    }
    return TRUE;
}

/* 00002720-000028A0       .text useHeapInit__FP9sss_class */
BOOL useHeapInit(sss_class*) {
    /* Nonmatching */
}

/* 000028A0-000028C0       .text daSss_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSss_solidHeapCB(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    return useHeapInit((sss_class*)i_actor);
}

/* 000028C0-00002BB4       .text daSss_Create__FP10fopAc_ac_c */
static cPhs_State daSss_Create(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    static dCcD_SrcSph tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 20.0f,
        }},
    };
    static dCcD_SrcSph bm_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_BOOMERANG | AT_TYPE_WIND,
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
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 80.0f,
        }},
    };

    fopAcM_ct(i_actor, sss_class);

    sss_class* i_this = (sss_class*) i_actor;

    cPhs_State state = dComIfG_resLoad(&i_this->field_0x2AC, "Sss");
    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_actor, daSss_solidHeapCB, 0x3040)) {
            non_pos.x = 0;
            non_pos.y = 30000;
            non_pos.z = -20000;
            i_this->field_0x2B8 = fopAcM_GetParam(i_this);
            if (i_this->field_0x2B8 == 0xFF) {
                i_this->field_0x2B8 = 0;
            }
            if (i_this->field_0x2B8 != 1) {
                i_this->field_0x2B8 = 0x23;
            }
            i_this->field_0x2B9 = fopAcM_GetParam(i_this) >> 8;
            i_this->field_0x2BA = fopAcM_GetParam(i_this) >> 0x10;
            if (i_this->field_0x2BA == 0xFF) {
                i_this->field_0x2BA = false;
            }
            i_this->health = 2;
            i_this->field_0x2BC = cM_rndF(10000);
            i_this->field_0x51C.Init(0xFF, 0xFF, i_this);
            for (int i = 0; i < 3; i++) {
                i_this->field_0x558[i].Set(tg_sph_src);
                i_this->field_0x558[i].SetStts(&i_this->field_0x51C);
            }
            i_this->field_0x8DC.Set(bm_sph_src);
            i_this->field_0x8DC.SetStts(&i_this->field_0x51C);
            i_this->field_0x2C8 = i_this->current.pos;
            if (!i_this->field_0x2BA) {
                i_this->field_0x2C8.y = i_this->field_0x2C8.y + 230;
            }
            daSss_Execute(i_this);
        } else {
            state = cPhs_ERROR_e;
        }
    }
    return state;
}

static actor_method_class l_daSss_Method = {
    (process_method_func)daSss_Create,
    (process_method_func)daSss_Delete,
    (process_method_func)daSss_Execute,
    (process_method_func)daSss_IsDelete,
    (process_method_func)daSss_Draw,
};

actor_process_profile_definition g_profile_SSS = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_SSS_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sss_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_SSS_e,
    /* Actor SubMtd */ &l_daSss_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
