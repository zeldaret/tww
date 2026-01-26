/**
 * d_a_kaji.cpp
 * Object - Ship's wheel (Tetra's Ship)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kaji.h"
#include "d/res/res_kaji.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_obj_pirateship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

static daObjPirateship::Act_c* l_p_ship;

const char daKaji_c::M_arcname[] = "Kaji";

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daKaji_c*)i_this)->CreateHeap();
}

/* 00000098-000001F4       .text CreateHeap__8daKaji_cFv */
BOOL daKaji_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, KAJI_INDEX_BDL_ASODA);
    JUT_ASSERT(0x55, modelData != NULL);
    
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Kaji", KAJI_INDEX_BCK_KJ_WAIT),
        J3DFrameCtrl::EMode_LOOP, 0.0f, 0, -1, 1,
        dComIfG_getObjectRes("Kaji", KAJI_INDEX_BAS_KJ_WAIT),
        0x00080000,
        0x11000002
    );
    
    return mpMorf && mpMorf->getModel();
}

cPhs_State daKaji_c::_create() {
    fopAcM_SetupActor(this, daKaji_c);
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x660)) {
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(shape_angle.y);
            mDoMtx_stack_c::scaleM(scale);
            MTXCopy(mDoMtx_stack_c::get(), mMtx);
            
            l_p_ship = (daObjPirateship::Act_c*)fopAcM_SearchByID(parentActorID);
        } else {
            return cPhs_ERROR_e;
        }
        
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -80.0f, -80.0f, -20.0f, 80.0f, 80.0f, 20.0f);
        
        MTXCopy(mpMorf->getModel()->getBaseTRMtx(), mMtx);
    }
    
    return phase_state;
}

bool daKaji_c::_delete() {
    dComIfG_resDelete(&mPhs, M_arcname);
    return TRUE;
}

bool daKaji_c::_execute() {
    // Copy the ship's transform (plus an offset) to the helm.
    cXyz offset(0.0f, 740.0f, -858.0f);
    offset.y += REG10_F(10);
    offset.z += REG10_F(11);
    cMtx_multVec(l_p_ship->mModel->getBaseTRMtx(), &offset, &current.pos);
    
    daObjPirateship::Act_c* ship = l_p_ship;
    shape_angle = ship->shape_angle;
    current.angle = shape_angle;
    
    mpMorf->play(NULL, 0, 0);
    
    set_mtx();
    
    return FALSE;
}

bool daKaji_c::_draw() {
    if (!l_p_ship->m2CC) {
        return true;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    mpMorf->update();
    return true;
}

/* 000001F4-00000344       .text daKajiCreate__FPv */
static cPhs_State daKajiCreate(void* i_this) {
    return ((daKaji_c*)i_this)->_create();
}

/* 00000344-00000374       .text daKajiDelete__FPv */
static BOOL daKajiDelete(void* i_this) {
    return ((daKaji_c*)i_this)->_delete();
}

/* 00000374-000004D4       .text daKajiExecute__FPv */
static BOOL daKajiExecute(void* i_this) {
    return ((daKaji_c*)i_this)->_execute();
}

/* 000004D4-00000568       .text daKajiDraw__FPv */
static BOOL daKajiDraw(void* i_this) {
    return ((daKaji_c*)i_this)->_draw();
}

/* 00000568-00000570       .text daKajiIsDelete__FPv */
static BOOL daKajiIsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daKajiMethodTable = {
    (process_method_func)daKajiCreate,
    (process_method_func)daKajiDelete,
    (process_method_func)daKajiExecute,
    (process_method_func)daKajiIsDelete,
    (process_method_func)daKajiDraw,
};

actor_process_profile_definition g_profile_Kaji = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Kaji,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daKaji_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Kaji,
    /* Actor SubMtd */ &daKajiMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
