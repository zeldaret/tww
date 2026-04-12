/**
 * d_a_nzg.cpp
 * Enemy - Rat Group
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_nzg.h"
#include "d/d_path.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/res/res_nzg.h"

/* 00000078-000000E4       .text daNZG_Draw__FP9nzg_class */
static BOOL daNZG_Draw(nzg_class* i_this) {
    J3DModel* model = i_this->mpModel;
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
    mDoExt_modelUpdateDL(model);
    return TRUE;
}

//Note: dummy function is required for matching rodata
static f32 dummy40(int arg1) {
    if (arg1 == 1) {
        return 40.0f;
    } else if (arg1 == 2) {
        return 0.0f;
    } else if (arg1 == 3) {
        f64 val = 0.5;
        return val;
    } else if (arg1 == 4) {
        f64 val = 3.0;
        return val;
    } else {
        return 300.0f;
    }
}

/* 000000E4-00000348       .text nzg_00_move__FP9nzg_class */
void nzg_00_move(nzg_class* i_this) {
    /* Nonmatching for Demo */
    //fixes regswap issue in demo for the most part but introduces a misplaced instruction error
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->m2C2[0] != 0 || i_this->m2BE >= i_this->m2C0) {
        return;
    }

    i_this->mCyl.SetC(actor->current.pos);
    i_this->mCyl.SetH(REG8_F(11) + 40.0f);
    i_this->mCyl.SetR(REG8_F(12) + 40.0f);
    dComIfG_Ccsp()->Set(&i_this->mCyl);

    if (i_this->mCyl.ChkCoHit()) {
        fopAc_ac_c* hit_actor = i_this->mCyl.GetCoHitAc();
        if (hit_actor != NULL) {
            s16 hitAC_name = fopAcM_GetName(hit_actor);
            if (hitAC_name != PROC_NZ && hitAC_name != PROC_BOMB && hitAC_name != PROC_Bomb2 && hitAC_name != PROC_ITEM && hitAC_name != PROC_ESA) {
                i_this->m2D4 = fopAcM_GetID(hit_actor);
                i_this->m2BB = 1;
                return;
            }
        }
    }

    u32 parameters = fopAcM_GetParam(actor) & 0xFF000000;

    if (i_this->m2BA == 1) {
        parameters |= 0x100;
    } else if (i_this->m2BA == 2 && cM_rnd() < 0.5f) {
        parameters |= 0x100;
    }

    if (parameters & 0x100 || fopAcM_searchActorDistance(actor, dComIfGp_getPlayer(0)) < i_this->m2CC * 0.5f) {
        if (fopAcM_searchActorDistance(actor, dComIfGp_getPlayer(0)) > i_this->m2D0 * 0.5f) {
            parameters |= 1;
            csXyz child_angle = actor->current.angle;

            child_angle.y += cM_rndFX(8192.0f);
            fpc_ProcID childProcID = fopAcM_createChild(PROC_NZ, fopAcM_GetID(actor), parameters, &actor->current.pos, fopAcM_GetRoomNo(actor), &child_angle, &actor->scale, NULL);

            if (childProcID != fpcM_ERROR_PROCESS_ID_e) {
                i_this->m2C2[0] = (childProcID & 3) * 10 + 20;
                i_this->m2BE++;
            }
        }
    }
}

/* 00000348-00000450       .text nzg_01_move__FP9nzg_class */
void nzg_01_move(nzg_class* i_this) {
    if (i_this->m2D4 != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* ac_id = fopAcM_SearchByID(i_this->m2D4);
        if (ac_id != NULL) {
            f32 pos_x_diff = i_this->actor.current.pos.x - ac_id->current.pos.x;
            f32 pos_z_diff = i_this->actor.current.pos.z - ac_id->current.pos.z;
            pos_x_diff = (pos_x_diff * pos_x_diff) + (pos_z_diff * pos_z_diff);

            if (std::sqrtf(pos_x_diff) < 80.0f) {
                return;
            }
        }
    }
    i_this->m2D4 = fpcM_ERROR_PROCESS_ID_e;
    i_this->m2BB = 0;
}

/* 00000450-000004D0       .text daNZG_Execute__FP9nzg_class */
static BOOL daNZG_Execute(nzg_class* i_this) {
    i_this->m2D0 = 400.0f;
    s32 j = 0;
    for (s32 i = 4; i != 0;  i--) {
        if (i_this->m2C2[j] != 0) {
            i_this->m2C2[j]--;
        }
        j += 1;
    }
    switch (i_this->m2BB) {
        case 0:
            nzg_00_move(i_this);
            break;
        case 1:
            nzg_01_move(i_this);
            break;
    }
    return TRUE;
}

/* 000004D0-000004D8       .text daNZG_IsDelete__FP9nzg_class */
static BOOL daNZG_IsDelete(nzg_class*) {
    return TRUE;
}

/* 000004D8-00000508       .text daNZG_Delete__FP9nzg_class */
static BOOL daNZG_Delete(nzg_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhs, "NZG");
    return TRUE;
}

/* 00000508-00000620       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    nzg_class* nzg_this = (nzg_class*)i_this;

    mDoMtx_stack_c::transS(nzg_this->actor.current.pos.x,  nzg_this->actor.current.pos.y,  nzg_this->actor.current.pos.z);
    mDoMtx_stack_c::YrotM(nzg_this->actor.shape_angle.y);

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("NZG",  NZG_BDL_KANA_00);
    JUT_ASSERT(630, modelData != NULL);
    J3DModel* model = mDoExt_J3DModel__create(modelData, 0,0x11020203);

    if (model == NULL) {
        return FALSE;
    }

    nzg_this->mpModel = model;
    model->setBaseScale(nzg_this->actor.scale);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    fopAcM_SetMtx(&nzg_this->actor, model->getBaseTRMtx());
    return TRUE;
}

/* 00000620-00000864       .text daNZG_Create__FP10fopAc_ac_c */
static cPhs_State daNZG_Create(fopAc_ac_c* i_this) {
    static dCcD_SrcCyl body_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e | cCcD_CoSPrm_NoCrr_e,
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
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
            /* Height */ 20.0f,
        }},
    };
#if VERSION == VERSION_DEMO
    nzg_class* nzg_this = (nzg_class*)i_this;
    cPhs_State phase_state = dComIfG_resLoad(&nzg_this->mPhs, "NZG");
    if (phase_state == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(i_this, nzg_class);
#else
    nzg_class* nzg_this = (nzg_class*)i_this;
    fopAcM_SetupActor(i_this, nzg_class);
    cPhs_State phase_state = dComIfG_resLoad(&nzg_this->mPhs, "NZG");
    if (phase_state == cPhs_COMPLEATE_e) {
#endif
        if (!fopAcM_entrySolidHeap(&nzg_this->actor, useHeapInit, 0x680)) {
            return cPhs_ERROR_e;
        }
        nzg_this->m2B8 = fopAcM_GetParam(nzg_this);
        nzg_this->m2B9 = fopAcM_GetParam(nzg_this) >> 8;
        nzg_this->m2BA = fopAcM_GetParam(nzg_this) >> 16;
        nzg_this->m2E9 = fopAcM_GetParam(nzg_this) >> 24;
        if (nzg_this->m2E9 != 0xFF) {
            nzg_this->mpPath = dPath_GetRoomPath(nzg_this->m2E9, fopAcM_GetRoomNo(i_this));
        }
        nzg_this->actor.shape_angle.y = nzg_this->actor.current.angle.y;
        nzg_this->m2CC = nzg_this->m2B8 * 10.0f;
        nzg_this->m2C0 = 1;
        if (nzg_this->m2B9 != 0) {
            nzg_this->m2C0 = nzg_this->m2B9;
        }

        if (nzg_this->m2BA > 2) {
            nzg_this->m2BA = 0;
        }
        nzg_this->mCyl.Set(body_cyl_src);
        nzg_this->mCyl.SetStts(&nzg_this->mStts);
        if (nzg_this->m2BA == 0) {
            csXyz child_angle = nzg_this->actor.current.angle;
            fopAcM_createChild("NpcNz",fpcM_GetID(nzg_this), 0xffffffff,  &nzg_this->actor.current.pos,  fopAcM_GetRoomNo(&nzg_this->actor), &child_angle, &nzg_this->actor.scale, NULL);
        }
    }
    return phase_state;
}

static actor_method_class l_daNZG_Method = {
    (process_method_func)daNZG_Create,
    (process_method_func)daNZG_Delete,
    (process_method_func)daNZG_Execute,
    (process_method_func)daNZG_IsDelete,
    (process_method_func)daNZG_Draw,
};

actor_process_profile_definition g_profile_NZG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NZG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(nzg_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NZG,
    /* Actor SubMtd */ &l_daNZG_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
