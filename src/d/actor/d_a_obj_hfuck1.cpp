//
// Generated by dtk
// Translation Unit: d_a_obj_hfuck1.cpp
//

#include "d/actor/d_a_obj_hfuck1.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/actor/d_a_player.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

namespace {
    static const char l_arcname[] = "Hfuck1";

    static const dCcD_SrcSph l_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_HOOKSHOT,
            /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_OTHER,
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
            /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_CON_HIT | G_TG_SPRM_NO_HIT_MARK,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 90.0f,
        },
    };

    static const Vec l_hook_offset = { 0.0f, 0.0f, 0.0f };
};

/* 00000078-00000100       .text init_mtx__13daObjHfuck1_cFv */
void daObjHfuck1_c::init_mtx() {
    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000100-00000124       .text solidHeapCB__13daObjHfuck1_cFP10fopAc_ac_c */
BOOL daObjHfuck1_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHfuck1_c*)i_this)->create_heap();
}

/* 00000124-00000224       .text create_heap__13daObjHfuck1_cFv */
bool daObjHfuck1_c::create_heap() {
    bool ret = true;

    J3DModelData* pModelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcname, 0x04));

    if (!pModelData) {
        JUT_ASSERT(0xf5, 0);
        ret = false;
    } else {
        mpModel = mDoExt_J3DModel__create(pModelData, 0x80000, 0x11000022);
        mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, 0x07), cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx());

        if (!mpModel || !mpBgW)
            ret = false;
    }

    return ret;
}

/* 00000224-000002AC       .text checkCollision__13daObjHfuck1_cFv */
bool daObjHfuck1_c::checkCollision() {
    bool ret = false;
    if (mSph.ChkTgHit()) {
        cCcD_Obj* at = mSph.GetTgHitObj();
        if (at != NULL && at->ChkAtType(AT_TYPE_HOOKSHOT)) {
            mpHookshotActor = mSph.GetTgHitAc();
            ret = true;
        }
        mSph.ClrTgHit();
    }
    return ret;
}

/* 000002AC-000004B0       .text _create__13daObjHfuck1_cFv */
s32 daObjHfuck1_c::_create() {
    fopAcM_SetupActor(this, daObjHfuck1_c);

    s32 ret = dComIfG_resLoad(&mPhs, l_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xc20)) {
            if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
                ret = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
                init_mtx();
                mStts.Init(0xFF, 0xFF, this);
                mSph.Set(l_sph_src);
                mSph.SetStts(&mStts);

                mDoMtx_stack_c::transS(current.pos);
                mDoMtx_stack_c::XYZrotM(shape_angle);
                mDoMtx_stack_c::transM(0.0f, 0.0f, -50.0f);
                cXyz center;
                mDoMtx_stack_c::multVecZero(&center);
                mSph.SetC(center);
                mSph.SetR(90.0f);
            }
        } else {
            ret = cPhs_ERROR_e;
        }
    }

    return ret;
}

/* 00000668-000006FC       .text _delete__13daObjHfuck1_cFv */
bool daObjHfuck1_c::_delete() {
    dComIfG_resDelete(&mPhs, l_arcname);

    if (heap != NULL && mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }

        mpBgW = NULL;
    }

    return true;
}

/* 000006FC-000007CC       .text _execute__13daObjHfuck1_cFv */
bool daObjHfuck1_c::_execute() {
    mpBgW->Move();
    mStts.Move();
    if (mpHookshotActor != NULL) {
        if (fopAcM_IsActor(mpHookshotActor) == TRUE && fopAcM_GetName(mpHookshotActor) == PROC_HOOKSHOT) {
            if (daPy_getPlayerActorClass() != NULL) {
                daPy_getPlayerActorClass()->setHookshotCarryOffset(fopAcM_GetID(this), (const cXyz*)&l_hook_offset);
            }
        }
        mpHookshotActor = NULL;
    }

    if (!checkCollision())
        dComIfG_Ccsp()->Set(&mSph);

    return true;
}

/* 000007CC-0000082C       .text _draw__13daObjHfuck1_cFv */
bool daObjHfuck1_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mpModel, &mTevStr);
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

/* 0000082C-0000084C       .text daObjHfuck1_Create__FP10fopAc_ac_c */
static BOOL daObjHfuck1_Create(fopAc_ac_c* i_this) {
    return ((daObjHfuck1_c*)i_this)->_create();
}

/* 0000084C-00000870       .text daObjHfuck1_Delete__FP13daObjHfuck1_c */
static BOOL daObjHfuck1_Delete(daObjHfuck1_c* i_this) {
    return i_this->_delete();
}

/* 00000870-00000894       .text daObjHfuck1_Execute__FP13daObjHfuck1_c */
static BOOL daObjHfuck1_Execute(daObjHfuck1_c* i_this) {
    return i_this->_execute();
}

/* 00000894-000008B8       .text daObjHfuck1_Draw__FP13daObjHfuck1_c */
static BOOL daObjHfuck1_Draw(daObjHfuck1_c* i_this) {
    return i_this->_draw();
}

/* 000008B8-000008C0       .text daObjHfuck1_IsDelete__FP13daObjHfuck1_c */
static BOOL daObjHfuck1_IsDelete(daObjHfuck1_c* i_this) {
    return TRUE;
}

static actor_method_class l_daObjHfuck1_Method = {
    (process_method_func)daObjHfuck1_Create,
    (process_method_func)daObjHfuck1_Delete,
    (process_method_func)daObjHfuck1_Execute,
    (process_method_func)daObjHfuck1_IsDelete,
    (process_method_func)daObjHfuck1_Draw,
};

actor_process_profile_definition g_profile_Obj_Hfuck1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 3,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Hfuck1,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daObjHfuck1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x005B,
    /* Actor SubMtd */ &l_daObjHfuck1_Method,
    /* Status       */ fopAcStts_UNK200000_e | fopAcStts_UNK40000_e | fopAcStts_CULL_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_3_e,
};
