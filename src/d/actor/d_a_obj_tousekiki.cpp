/**
 * d_a_obj_tousekiki.cpp
 * Object - Catapult (Tetra's Ship)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_tousekiki.h"
#include "d/actor/d_a_obj_pirateship.h"
#include "d/res/res_touseki.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"

static daObjPirateship::Act_c* l_p_ship;

const char daObj_Tousekiki_c::M_arcname[] = "Touseki";

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* a_this) {
    return ((daObj_Tousekiki_c*)a_this)->CreateHeap();
}

/* 0000010C-000002BC       .text CreateHeap__17daObj_Tousekiki_cFv */
BOOL daObj_Tousekiki_c::CreateHeap() {
    mMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes(M_arcname, TOUSEKI_INDEX_BDL_ATOSK_A),
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, TOUSEKI_INDEX_BCK_ATOSK_NAGE),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11000002
    );
    if (mMorf == NULL) {
        return false;
    }

    mMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, TOUSEKI_INDEX_BCK_ATOSK_NAGE), 0, 0.0f, 1.0f, 0.0f, -1.0f, NULL);
    m2D0 = 0xFFFF;
    mMorf->setFrame(mMorf->getEndFrame() - 1.0f);
    mModel = mMorf->getModel();
    if (mModel == NULL) {
        return false;
    }
    return true;
}

/* 000002BC-000002DC       .text daObj_TousekikiCreate__FPv */
static cPhs_State daObj_TousekikiCreate(void* i_this) {
    return ((daObj_Tousekiki_c*)i_this)->_create();
}

/* 000002DC-000004F4       .text _create__17daObj_Tousekiki_cFv */
cPhs_State daObj_Tousekiki_c::_create() {
#if VERSION == VERSION_DEMO
    cPhs_State PVar1 = dComIfG_resLoad(&mPhase, M_arcname);
    if (PVar1 == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(this, daObj_Tousekiki_c);
#else
    fopAcM_SetupActor(this, daObj_Tousekiki_c);

    cPhs_State PVar1 = dComIfG_resLoad(&mPhase, M_arcname);
    if (PVar1 == cPhs_COMPLEATE_e) {
#endif
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x900)) {
            return cPhs_ERROR_e;
        }

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
        MTXCopy(mDoMtx_stack_c::get(), m2A0);
        mModel->setBaseScale(scale);

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
        mModel->setBaseTRMtx(mDoMtx_stack_c::get());

        MTXCopy(mDoMtx_stack_c::get(), m2A0);
        l_p_ship = (daObjPirateship::Act_c*)fopAcM_SearchByID(parentActorID);
        fopAcM_SetMtx(this, mModel->getBaseTRMtx());
        MTXCopy(mModel->getBaseTRMtx(), m2A0);
    }
    return PVar1;
}

bool daObj_Tousekiki_c::_delete() {
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    return true;
}

/* 000006E8-00000718       .text daObj_TousekikiDelete__FPv */
static BOOL daObj_TousekikiDelete(void* v_this) {
    return ((daObj_Tousekiki_c*)v_this)->_delete();
}

void daObj_Tousekiki_c::demo_move() {
    static cXyz touseki_offset(0.0f, 700.0f, 850.0f);
    cMtx_multVec(l_p_ship->mModel->getBaseTRMtx(), &touseki_offset, &current.pos);
    if (dDemo_setDemoData(this, dDemo_actor_c::ENABLE_ANM_FRAME_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ROTATE_e, mMorf, "Touseki") == 0) {
        shape_angle = l_p_ship->shape_angle;
        current.angle = shape_angle;
    }
}

void daObj_Tousekiki_c::set_mtx() {
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), m2A0);
}

bool daObj_Tousekiki_c::_execute() {
    demo_move();
    set_mtx();
    return false;
}

/* 00000718-000008A4       .text daObj_TousekikiExecute__FPv */
static BOOL daObj_TousekikiExecute(void* v_this) {
    return ((daObj_Tousekiki_c*)v_this)->_execute();
}

bool daObj_Tousekiki_c::_draw() {
    if (l_p_ship->m2CC == 0) {
        return true;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    mMorf->updateDL();
    return true;
}

/* 000008A4-00000934       .text daObj_TousekikiDraw__FPv */
static BOOL daObj_TousekikiDraw(void* v_this) {
    return ((daObj_Tousekiki_c*)v_this)->_draw();
}

/* 00000934-0000093C       .text daObj_TousekikiIsDelete__FPv */
static BOOL daObj_TousekikiIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_TousekikiMethodTable = {
    (process_method_func)daObj_TousekikiCreate,
    (process_method_func)daObj_TousekikiDelete,
    (process_method_func)daObj_TousekikiExecute,
    (process_method_func)daObj_TousekikiIsDelete,
    (process_method_func)daObj_TousekikiDraw,
};

actor_process_profile_definition g_profile_Obj_Tousekiki = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Tousekiki,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Tousekiki_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Tousekiki,
    /* Actor SubMtd */ &daObj_TousekikiMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
