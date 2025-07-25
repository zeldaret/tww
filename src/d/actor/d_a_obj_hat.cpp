/**
 * d_a_obj_hat.cpp
 * Object - Hats (Traveling Merchants)
 */

#include "d/actor/d_a_obj_hat.h"
#include "d/actor/d_a_npc_roten.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_ro.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"

static const int l_bmd_ix_tbl[] = {RO_BDL_RO_HAT, RO_BDL_RO_HAT2, RO_BDL_RO_HAT3, RO_BDL_RO_HAT};
static const int l_bck_ix_tbl[] = {RO_BCK_HAT_WID, RO_BCK_HAT2_WIND, RO_BCK_HAT3_WID,
                                   RO_BCK_HAT_WID};
static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 70.0f,
        /* Height */ 80.0f,
    },
};



/* 00000078-00000184       .text __ct__10daObjHat_cFv */
daObjHat_c::daObjHat_c() {
    u32 hatno = getPrmHatNo();
    mHatNo = hatno;
    mState = 0;
}

/* 000003AC-000003CC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* actor) {
    return ((daObjHat_c*)actor)->createHeap();
}

/* 000003CC-0000045C       .text _create__10daObjHat_cFv */
cPhs_State daObjHat_c::_create() {
    fopAcM_SetupActor(this, daObjHat_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, "Ro");

    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0uL)) {
            phase_state = createInit();
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 0000045C-000005D4       .text createHeap__10daObjHat_cFv */
BOOL daObjHat_c::createHeap() {
    J3DModelData* pModelData = (J3DModelData*)dComIfG_getObjectIDRes("Ro", l_bmd_ix_tbl[mHatNo]);
    if (pModelData == NULL) {
        return FALSE;
    } else {
        mDoExt_McaMorf* morf = new mDoExt_McaMorf(
            pModelData, NULL, NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectIDRes("Ro", l_bck_ix_tbl[mHatNo]),
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x80000, 0x37441422);

        mpMorf = morf;
        if (mpMorf == NULL || mpMorf->getModel() == NULL) {
            return FALSE;
        } else {
            mpModel = mpMorf->getModel();
            mAcchCir.SetWall(30.0f, 30.0f);
            mAcch.Set(fopAcM_GetPosition_p(this),
                      fopAcM_GetOldPosition_p(this),
                      this,
                      1,
                      &mAcchCir,
                      fopAcM_GetSpeed_p(this),
                      fopAcM_GetAngle_p(this),
                      fopAcM_GetShapeAngle_p(this));
            return TRUE;
        }
    }
    return FALSE;
}

/* 000005D4-000006AC       .text createInit__10daObjHat_cFv */
cPhs_State daObjHat_c::createInit() {
    mStts.Init(2, 0xff, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0f, 0.0f, -50.0f, 50.0f, 200.0f, 50.0f);
    gravity = -5.0f;

    fopAc_ac_c* parent;
    if (fopAcM_SearchByID(fopAcM_GetLinkId(this), &parent) && (parent != NULL)) {
        setSpeed(static_cast<daNpcRoten_c*>(parent)->getWindVec());
    }

    setMtx();
    return cPhs_COMPLEATE_e;
}

/* 000006AC-000006DC       .text _delete__10daObjHat_cFv */
BOOL daObjHat_c::_delete() {
    dComIfG_resDelete(&mPhs, "Ro");
    return TRUE;
}

/* 000006DC-0000073C       .text _draw__10daObjHat_cFv */
BOOL daObjHat_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpMorf->updateDL();
    return TRUE;
}

static daObjHat_c::MoveFunc_t moveProc[] = {
    &daObjHat_c::executeNormal,
};


/* 0000073C-00000884       .text _execute__10daObjHat_cFv */
BOOL daObjHat_c::_execute() {
    (this->*moveProc[mState])();
    f32 xspeed = mMoveNorm.x * speedF;
    f32 yspeed = speed.y + gravity;
    f32 zspeed = mMoveNorm.z * speedF;

    if (yspeed < fopAcM_GetMaxFallSpeed(this)) {
        yspeed = fopAcM_GetMaxFallSpeed(this);
    }
    fopAcM_SetSpeed(this, xspeed, yspeed, zspeed);

    fopAcM_posMove(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());
    if (mAcch.ChkWallHit()) {
        fopAcM_SetSpeedF(this, 0.0f);
    }
    if (mAcch.ChkGroundHit()) {
        cLib_addCalc(&speedF, 0.0f, 0.3f, 1000.0f, 1.0f);
    }

    mCyl.SetC(this->current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
    if (mCyl.ChkTgHit()) {
        setSpeed(*mCyl.GetTgRVecP());
    }

    setMtx();
    return TRUE;
}

/* 00000884-00000888       .text executeNormal__10daObjHat_cFv */
void daObjHat_c::executeNormal() { }

/* 00000888-000008B4       .text getPrmHatNo__10daObjHat_cFv */
u32 daObjHat_c::getPrmHatNo() {
    return daObj::PrmAbstract(this, PRM_HAT_NO_W, PRM_HAT_NO_S) & 3;
}

/* 000008B4-00000964       .text setMtx__10daObjHat_cFv */
void daObjHat_c::setMtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y,
             current.pos.z);

    mDoMtx_stack_c::YrotM(current.angle.y + 0x4000);
    mDoMtx_stack_c::XrotM(current.angle.x);
    mDoMtx_stack_c::ZrotM(current.angle.z + 0x4000);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000964-00000A20       .text setSpeed__10daObjHat_cF4cXyz */
void daObjHat_c::setSpeed(cXyz speed) {
    speed.y = 0;
    speed = speed.normZP();

    mMoveNorm = speed;

    fopAcM_SetSpeedF(this, 20.0f);

    speed.x *= 20.0f;
    speed.y = 50.0f;
    speed.z *= 20.0f;

    fopAcM_SetSpeed(this, speed.x, speed.y, speed.z);
}

/* 00000A20-00000A40       .text daSampleCreate__FPv */
static cPhs_State daSampleCreate(void* i_this) {
    return static_cast<daObjHat_c*>(i_this)->_create();
}

/* 00000A40-00000A60       .text daSampleDelete__FPv */
static BOOL daSampleDelete(void* i_this) {
    return static_cast<daObjHat_c*>(i_this)->_delete();
}

/* 00000A60-00000A80       .text daSampleExecute__FPv */
static BOOL daSampleExecute(void* i_this) {
    return static_cast<daObjHat_c*>(i_this)->_execute();
}

/* 00000A80-00000AA0       .text daSampleDraw__FPv */
static BOOL daSampleDraw(void* i_this) {
    return static_cast<daObjHat_c*>(i_this)->_draw();
}

/* 00000AA0-00000AA8       .text daSampleIsDelete__FPv */
static BOOL daSampleIsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daSampleMethodTable = {
    (process_method_func)daSampleCreate,
    (process_method_func)daSampleDelete,
    (process_method_func)daSampleExecute,
    (process_method_func)daSampleIsDelete,
    (process_method_func)daSampleDraw,
};

actor_process_profile_definition g_profile_OBJ_HAT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_HAT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHat_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_HAT,
    /* Actor SubMtd */ &daSampleMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
