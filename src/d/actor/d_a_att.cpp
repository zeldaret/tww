//
// Generated by dtk
// Translation Unit: d_a_att.cpp
//

#include "d/actor/d_a_att.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_bgn.h"

#if VERSION == VERSION_USA
#include "weak_data_1811.h" // IWYU pragma: keep
#endif

static bgn_class* boss;
static cXyz non_pos(-30000.0f, -30000.0f, -30000.0f);

/* 000000EC-000000F4       .text daAtt_Draw__FP9att_class */
static BOOL daAtt_Draw(att_class* i_this) {
    return TRUE;
}

/* 000000F4-00000140       .text boss_s_sub__FPvPv */
static void* boss_s_sub(void* search, void*) {
    if (fopAcM_IsActor(search) && fopAcM_GetName(search) == PROC_BGN) {
        return search;
    }
    return NULL;
}

/* 00000140-0000052C       .text daAtt_Execute__FP9att_class */
static BOOL daAtt_Execute(att_class* i_this) {
#if VERSION == VERSION_USA
    if (i_this->m2B5 == 101) {
        i_this->attention_info.position = i_this->eyePos = i_this->current.pos;
        fopAcM_OffStatus(i_this, 0);
        i_this->attention_info.flags = 0;
        i_this->mSph.SetC(i_this->current.pos);
        dComIfG_Ccsp()->Set(&i_this->mSph);
    }
#endif
    if (i_this->m2B5 == 100) {
        i_this->attention_info.position = i_this->eyePos = i_this->current.pos;
    } else {
        boss = (bgn_class*)fpcM_Search(&boss_s_sub, i_this);
        if (boss == NULL) {
            return TRUE;
        }
        int r30 = i_this->m2B5;
        
        if (i_this->m550 != 0) {
            i_this->m550--;
        }
        
        if (i_this->m550 == 0 && (i_this->mCyl.ChkTgHit() || i_this->mSph.ChkTgHit())) {
            i_this->m550 = 10;
            boss->mAAA8[r30].m308--;
            if (boss->mAAA8[r30].m308 <= 0) {
                boss->mAAA8[r30].m2D0 = 1;
                boss->mAAA8[r30].m304 = 6000.0f;
                mDoAud_seStart(JA_SE_LK_W_WEP_HIT, NULL, 0x21, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                if (r30 <= 1) {
                    if (boss->mAAA8[1-r30].m2D0 != 0) {
                        boss->mC7B0 = 600;
                    }
                }
            } else {
                boss->mAAA8[r30].m300 = 15;
                mDoAud_seStart(JA_SE_CM_BGN_D_STRING_PLINK, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            }
        }
        
        i_this->current.pos = boss->mC33C[r30];
        cXyz sp08 = i_this->current.pos;
        
        if (
            boss->m02B5 == 0
            &&
            (boss->mC748 != 0 || boss->mC74C != 0 || r30 != 7)
            &&
            (boss->mAAA8[r30].m2D0 == 0 && boss->mAAA8[r30].m2EC < 1.0f)
         ) {
            i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mCyl.SetR(200.0f);
            i_this->mCyl.SetC(sp08);
            sp08.y += 1000.0f;
            i_this->mSph.SetC(sp08);
            i_this->eyePos = sp08;
            i_this->attention_info.position = sp08;
        } else {
            fopAcM_OffStatus(i_this, 0);
            i_this->attention_info.flags = 0;
            i_this->mCyl.SetC(non_pos);
            i_this->mSph.SetC(non_pos);
        }
        
        dComIfG_Ccsp()->Set(&i_this->mCyl);
        dComIfG_Ccsp()->Set(&i_this->mSph);
    }
    return TRUE;
}

/* 00000568-00000570       .text daAtt_IsDelete__FP9att_class */
static BOOL daAtt_IsDelete(att_class* i_this) {
    return TRUE;
}

/* 00000570-00000578       .text daAtt_Delete__FP9att_class */
static BOOL daAtt_Delete(att_class* i_this) {
    return TRUE;
}

/* 00000578-00000768       .text daAtt_Create__FP10fopAc_ac_c */
static cPhs_State daAtt_Create(fopAc_ac_c* i_this) {
#if VERSION == VERSION_USA
    static dCcD_SrcSph sita_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_HOOKSHOT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 90.0f,
        },
    };
#endif
    static dCcD_SrcCyl cc_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 200.0f,
            /* Height */ 2000.0f,
        },
    };
    static dCcD_SrcSph bm_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 200.0f,
        },
    };
    
    att_class* a_this = (att_class*)i_this;
    fopAcM_SetupActor(i_this, att_class);
    
    a_this->m2B5 = fopAcM_GetParam(a_this) & 0xFF;
    a_this->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
    
#if VERSION == VERSION_USA
    if (a_this->m2B5 == 101) {
        fopAcM_OnStatus(a_this, fopAcStts_UNK10000000_e);
        a_this->mStts.Init(0xFF, 0xFF, a_this);
        
        a_this->mSph.Set(sita_sph_src);
        a_this->mSph.SetStts(&a_this->mStts);
    }
#endif
    
    if (a_this->m2B5 < 10) {
        boss = NULL;
        
        a_this->mStts.Init(0xFF, 0xFF, a_this);
        
        a_this->mCyl.Set(cc_cyl_src);
        a_this->mCyl.SetStts(&a_this->mStts);
        
        a_this->mSph.Set(bm_sph_src);
        a_this->mSph.SetStts(&a_this->mStts);
    }
    
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daAtt_Method = {
    (process_method_func)daAtt_Create,
    (process_method_func)daAtt_Delete,
    (process_method_func)daAtt_Execute,
    (process_method_func)daAtt_IsDelete,
    (process_method_func)daAtt_Draw,
};

actor_process_profile_definition g_profile_ATT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ATT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(att_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x019C,
    /* Actor SubMtd */ &l_daAtt_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
