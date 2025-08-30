/**
 * d_a_bita.cpp
 * Object - Wooden platforms (Gohma fight)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bita.h"
#include "d/res/res_bita.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_btd.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

static btd_class* btd = NULL;

static u32 ita_bmd[]    = { BITA_BDL_MBIT1, BITA_BDL_MBIT2 };
static u32 ita_dzb[]    = { BITA_DZB_MBIT1, BITA_DZB_MBIT2 };
static u32 ita_Ef_bmd[] = { BITA_BDL_EF_BTDITA0, BITA_BDL_EF_BTDITA1 };
static u32 ita_Ef[]     = { BITA_BRK_EF_BTDITA0, BITA_BRK_EF_BTDITA1 };

/* 00000078-000000C4       .text b_a_sub__FPvPv */
static void* b_a_sub(void* search, void* user) {
    if (fopAc_IsActor(search) && fopAcM_GetName(search) == PROC_BTD)
        return search;
    return NULL;
}

/* 000000C4-0000018C       .text daBita_Draw__FP10bita_class */
static BOOL daBita_Draw(bita_class* i_this) {
    dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG0, &i_this->current.pos, &i_this->tevStr);
    if (i_this->mMode == bita_class::MODE_DEAD && i_this->mSub == 1) {
        dKy_getEnvlight().setLightTevColorType(i_this->mpModelEf, &i_this->tevStr);
        i_this->mpBrkAnm->entry(i_this->mpModelEf->getModelData());
        mDoExt_modelUpdateDL(i_this->mpModelEf);
        i_this->mpBrkAnm->remove(i_this->mpModelEf->getModelData());
    } else {
        dKy_getEnvlight().setLightTevColorType(i_this->mpModel, &i_this->tevStr);
        mDoExt_modelUpdateDL(i_this->mpModel);
    }
    return TRUE;
}

/* 0000018C-000002D0       .text mode_normal__FP10bita_class */
static void mode_normal(bita_class* i_this) {
    if (btd != NULL) {
        if (btd->m6E16 >= 100) {
            cXyz delta = dComIfGp_getCamera(0)->mLookat.mEye - i_this->current.pos;
            if (delta.abs() < 1500.0f) {
                fopAcM_delete(i_this);
            }
        } else {
            if (i_this->mCyl.ChkTgHit() && i_this->mCyl.GetTgHitObj()->GetAtType() == AT_TYPE_FIRE) {
                i_this->mMode = bita_class::MODE_DEAD;
                i_this->mSub = 0;
            }
        }
    }
}

/* 000002D0-000004B4       .text mode_dead__FP10bita_class */
static void mode_dead(bita_class* i_this) {
    switch (i_this->mSub) {
    case 0:
        i_this->mTimer = 0;
        i_this->field_0x2a7 = cM_rndF(4.0f);
        i_this->mSub = 1;
        break;
    case 1:
        i_this->mTimer++;
        if (i_this->mTimer == 20) {
            fopAcM_seStartCurrent(i_this, JA_SE_OBJ_BTD_BOARD_BURN, 0);
        }
        if (i_this->mTimer == 88) {
            fopAcM_seStartCurrent(i_this, JA_SE_OBJ_BTD_BOARD_BRK, 0);

            s32 type = i_this->mType;
            if (type > 1)
                type = 1;

            if (type == 0) {
                dComIfGp_particle_set(dPa_name::ID_SCENE_80E3, &i_this->current.pos, &i_this->shape_angle);
            } else {
                dComIfGp_particle_set(dPa_name::ID_SCENE_80E4, &i_this->current.pos, &i_this->shape_angle);
            }
        }

        if (i_this->mTimer >= 90)
            fopAcM_delete(i_this);
        break;
    }
}

/* 000004B4-00000584       .text base_mtx_set__FP10bita_class */
static void base_mtx_set(bita_class* i_this) {
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
    cMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
    if (i_this->mMode == bita_class::MODE_DEAD && i_this->mSub >= 1) {
        i_this->mpModelEf->setBaseTRMtx(*calc_mtx);
        if (i_this->mTimer < 60)
            i_this->mpBrkAnm->play();
        fopAcM_SetMtx(i_this, i_this->mpModelEf->getBaseTRMtx());
    } else {
        i_this->mpModel->setBaseTRMtx(*calc_mtx);
    }
}

/* 00000584-00000714       .text daBita_Execute__FP10bita_class */
static BOOL daBita_Execute(bita_class* i_this) {
    if (btd == NULL)
        btd = (btd_class*)fpcM_Search(b_a_sub, i_this);

    if (dComIfGs_getLife() == 0)
        fopAcM_OffStatus(i_this, fopAcStts_UNK4000_e);

    switch (i_this->mMode) {
    case bita_class::MODE_NORMAL:
        mode_normal(i_this);
        break;
    case bita_class::MODE_DEAD:
        mode_dead(i_this);
        break;
    }

    base_mtx_set(i_this);
    cMtx_copy(*calc_mtx, i_this->mMtx);
    i_this->mpBgW->Move();

    if (btd != NULL && i_this->mMode == bita_class::MODE_NORMAL) {
        cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
        cMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
        cXyz offs(0.0f, -80.0f, 160.0f);
        cXyz pos;
        MtxPosition(&offs, &pos);
        VECAdd(&pos, &i_this->current.pos, &pos);
        i_this->mCyl.SetC(pos);
        i_this->mCyl.SetH(60.0f);
        i_this->mCyl.SetR(i_this->scale.x * 400.0f);
        dComIfG_Ccsp()->Set(&i_this->mCyl);
    }

    return TRUE;
}

/* 00000714-0000071C       .text daBita_IsDelete__FP10bita_class */
static BOOL daBita_IsDelete(bita_class* i_this) {
    return TRUE;
}

/* 0000071C-00000778       .text daBita_Delete__FP10bita_class */
static BOOL daBita_Delete(bita_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Bita");
    if (i_this->heap != NULL)
        dComIfG_Bgsp()->Release(i_this->mpBgW);
    return TRUE;
}

/* 00000778-00000A18       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_ac) {
    bita_class* i_this = (bita_class*)i_ac;

    s32 type = i_this->mType;
    if (type > 1)
        type = 1;

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Bita", ita_bmd[type]);
    JUT_ASSERT(0x23b, modelData != NULL);
    J3DModel* model = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (model == NULL)
        return FALSE;
    i_this->mpModel = model;

    modelData = (J3DModelData*)dComIfG_getObjectRes("Bita", ita_Ef_bmd[type]);
    JUT_ASSERT(0x247, modelData != NULL);
    model = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (model == NULL)
        return FALSE;
    i_this->mpModelEf = model;

    i_this->mpBrkAnm = new mDoExt_brkAnm();
    if (i_this->mpBrkAnm == NULL)
        return FALSE;
    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bita", ita_Ef[type]);
    if (!i_this->mpBrkAnm->init(i_this->mpModelEf->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0))
        return FALSE;

    i_this->mpBgW = new dBgW();
    if (i_this->mpBgW == NULL)
        return FALSE;
    cBgD_t* dzb = (cBgD_t*)dComIfG_getObjectRes("Bita", ita_dzb[type]);
    if (i_this->mpBgW->Set(dzb, dBgW::MOVE_BG_e, &i_this->mMtx) == true)
        return FALSE;

    i_this->mpBgW->SetCrrFunc(dBgS_MoveBGProc_Typical);
    return TRUE;
}

/* 00000A60-00000D24       .text daBita_Create__FP10fopAc_ac_c */
static cPhs_State daBita_Create(fopAc_ac_c* i_ac) {
    static dCcD_SrcCyl body_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_FIRE,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK6,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
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
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
            /* Height */ 20.0f,
        }},
    };

    fopAcM_SetupActor(i_ac, bita_class);
    bita_class* i_this = (bita_class*)i_ac;

    cPhs_State rt = dComIfG_resLoad(&i_this->mPhs, "Bita");
    if (rt == cPhs_COMPLEATE_e) {
        btd = NULL;
        i_this->mType = (fopAcM_GetParam(i_this) >> 0) & 0xFF;
        i_this->mPrmScale = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
        if (i_this->mType == 0xFF)
            i_this->mType = 0;

        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x30c0))
            return cPhs_ERROR_e;

        if (dComIfG_Bgsp()->Regist(i_this->mpBgW, i_this))
            return cPhs_ERROR_e;

        switch (i_this->mPrmScale) {
        case 1: i_this->scale.setall(1.5f); break;
        case 2: i_this->scale.setall(2.0f); break;
        case 3: i_this->scale.setall(3.0f); break;
        default: i_this->scale.y = i_this->scale.z = i_this->scale.x = 1.0f; break;
        }

        fopAcM_SetMtx(i_this, i_this->mpModel->getBaseTRMtx());
        fopAcM_SetMin(i_this, i_this->scale.x * -1000.0f, -500.0f, i_this->scale.z * -1000.0f);
        fopAcM_SetMax(i_this, i_this->scale.x * 1000.0f, 500.0f, i_this->scale.z * 1000.0f);
        i_this->mpModel->setBaseScale(i_this->scale);
        i_this->mpModelEf->setBaseScale(i_this->scale);
        i_this->shape_angle = i_this->current.angle;
        base_mtx_set(i_this);
        i_this->mpBgW->Move();
        i_this->mCyl.Set(body_cyl_src);
        i_this->mCyl.SetStts(&i_this->mStts);
    }

    return rt;
}

static actor_method_class l_daBita_Method = {
    (process_method_func)daBita_Create,
    (process_method_func)daBita_Delete,
    (process_method_func)daBita_Execute,
    (process_method_func)daBita_IsDelete,
    (process_method_func)daBita_Draw,
};

actor_process_profile_definition g_profile_BITA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BITA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bita_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BITA,
    /* Actor SubMtd */ &l_daBita_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
