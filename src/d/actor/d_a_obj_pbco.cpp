/**
 * d_a_obj_pbco.cpp
 * Object - Windfall Island - Bomb Shop - Flip up countertop/counter door
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_pbco.h"
#include "d/res/res_pbco.h"
#include "d/d_com_inf_game.h"
#include "d/d_item.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

static daObj_Pbco_HIO_c l_HIO;
const char daObj_Pbco_c::M_arcname[] = "Pbco";

/* 000000EC-00000104       .text __ct__16daObj_Pbco_HIO_cFv */
daObj_Pbco_HIO_c::daObj_Pbco_HIO_c() {
    mNo = -1;
}

/* 00000104-0000018C       .text set_mtx__12daObj_Pbco_cFv */
void daObj_Pbco_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 0000018C-000001AC       .text CheckCreateHeap__FP10fopAc_ac_c */
static int CheckCreateHeap(fopAc_ac_c* i_this) {
    daObj_Pbco_c* a_this = static_cast<daObj_Pbco_c*>(i_this);
    return a_this->CreateHeap();
}

/* 000001AC-00000348       .text CreateHeap__12daObj_Pbco_cFv */
BOOL daObj_Pbco_c::CreateHeap() {
    J3DModelData* modelData;
    if (dComIfGs_isEventBit(0x0a02) && !checkItemGet(dItem_PEARL_NAYRU_e, TRUE)) {
        modelData = (J3DModelData*)(dComIfG_getObjectRes(M_arcname, PBCO_INDEX_BDL_PBCO));
    } else {
        modelData = (J3DModelData*)(dComIfG_getObjectRes(M_arcname, PBCO_INDEX_BDL_PBC2));
    }
    JUT_ASSERT(0xa9, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (dComIfGs_isEventBit(0x0a02) && !checkItemGet(dItem_PEARL_NAYRU_e, TRUE)) {
        mpBgW = NULL;
    } else {
        mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, PBCO_INDEX_DZB_PBCO), cBgW::MOVE_BG_e,
                            &mpModel->getBaseTRMtx());
        if (mpBgW == NULL) {
            return FALSE;
        }
    }
    return mpModel != NULL;
}

/* 00000348-000003A4       .text CreateInit__12daObj_Pbco_cFv */
cPhs_State daObj_Pbco_c::CreateInit() {
    set_mtx();
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    if (mpBgW) {
        dComIfG_Bgsp()->Regist(mpBgW, this);
    }
    return cPhs_COMPLEATE_e;
}

cPhs_State daObj_Pbco_c::_create() {
    fopAcM_SetupActor(this, daObj_Pbco_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x10000)) {
            phase_state = CreateInit();
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 000003A4-00000434       .text daObj_PbcoCreate__FPv */
static cPhs_State daObj_PbcoCreate(void* i_this) {
    return static_cast<daObj_Pbco_c*>(i_this)->_create();
}

bool daObj_Pbco_c::_delete() {
    if (mpBgW != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    dComIfG_resDeleteDemo(&mPhs, M_arcname);
    return TRUE;
}

/* 00000434-0000048C       .text daObj_PbcoDelete__FPv */
static BOOL daObj_PbcoDelete(void* i_this) {
    static_cast<daObj_Pbco_c*>(i_this)->_delete();
    return TRUE;
}

bool daObj_Pbco_c::_execute() {
    if (mpBgW != NULL)
        mpBgW->Move();
    set_mtx();
    return FALSE;
}

/* 0000048C-000004D0       .text daObj_PbcoExecute__FPv */
static BOOL daObj_PbcoExecute(void* i_this) {
    return static_cast<daObj_Pbco_c*>(i_this)->_execute();
}

bool daObj_Pbco_c::_draw() {
    dKy_tevstr_c* pTevStr;
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, pTevStr = &tevStr);
    g_env_light.setLightTevColorType(mpModel, pTevStr);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

/* 000004D0-0000053C       .text daObj_PbcoDraw__FPv */
static BOOL daObj_PbcoDraw(void* i_this) {
    daObj_Pbco_c* a_this = (daObj_Pbco_c*)i_this;
    return a_this->_draw();
}

/* 0000053C-00000544       .text daObj_PbcoIsDelete__FPv */
static BOOL daObj_PbcoIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_PbcoMethodTable = {
    (process_method_func)daObj_PbcoCreate,
    (process_method_func)daObj_PbcoDelete,
    (process_method_func)daObj_PbcoExecute,
    (process_method_func)daObj_PbcoIsDelete,
    (process_method_func)daObj_PbcoDraw,
};

actor_process_profile_definition g_profile_Obj_Pbco = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Pbco,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Pbco_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Pbco,
    /* Actor SubMtd */ &daObj_PbcoMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
