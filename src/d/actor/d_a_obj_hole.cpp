/**
 * d_a_obj_hole.cpp
 * Object - Grotto
 */

#include "d/actor/d_a_obj_hole.h"
#include "d/res/res_aana.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_acch.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

#include "weak_data_1811.h" // IWYU pragma: keep

static daObj_Hole_HIO_c l_HIO;

const char daObj_Hole_c::m_arc_name[] = "Aana";

/* 000000EC-0000010C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_actor) {
    return static_cast<daObj_Hole_c*>(i_actor)->_createHeap();
}

/* 0000010C-00000148       .text __ct__16daObj_Hole_HIO_cFv */
daObj_Hole_HIO_c::daObj_Hole_HIO_c() {
    mNo = -1;
    m05 = 0;
    m08 = 65.0f;
    m0C = 0;
    m10 = 2.0f;
}

/* 00000148-000002BC       .text setMtx__12daObj_Hole_cFv */
void daObj_Hole_c::setMtx() {
    cXyz adjustPos;
    adjustPos.x = current.pos.x;
    adjustPos.y = current.pos.y;
    adjustPos.z = current.pos.z;
    adjustPos.y += l_HIO.m10;

    if (mMode != MODE_EVENT) {
        shape_angle.y = fopCamM_GetAngleY(dComIfGp_getCamera(0)) + 0x8000;
    }

    if (mHasModel == 0xFF) {
        f32 scaleMag = l_HIO.m08 * scale.x;

        if (l_HIO.m0C != 0) {
            scaleMag += l_HIO.m0C * 10;
        }
        else {
            scaleMag += mScaleLocal * 10;
        }

        scaleMag /= l_HIO.m08;

        cXyz scaleVec;
        scaleVec.setall(scaleMag);
        mpMdl->setBaseScale(scaleVec);

        mDoMtx_stack_c::transS(adjustPos);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, 0, shape_angle.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);

        mpMdl->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 000002BC-000003F0       .text getPosAndAngle__12daObj_Hole_cFv */
void daObj_Hole_c::getPosAndAngle() {
    cXyz posUp(0.0f, 10.0f, 0.0f);
    posUp += current.pos;

    cXyz posDown(0.0f, -100.0f, 0.0f);
    posDown += current.pos;

    csXyz unused_angle(0, 0, 0);

    mLinChk.Set(&posUp, &posDown, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk) != 0) {
        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinChk);
        
        triPla->CalcAngleXz(&shape_angle.x, &shape_angle.z);
        triPla->getCrossY(current.pos, &current.pos.y);
    }
}

/* 000003F0-00000410       .text modeWaitInit__12daObj_Hole_cFv */
void daObj_Hole_c::modeWaitInit() {
    getPosAndAngle();
}

/* 00000410-000004F0       .text modeWait__12daObj_Hole_cFv */
void daObj_Hole_c::modeWait() {
    f32 scaleMag = l_HIO.m08 * scale.x;

    if (l_HIO.m0C != 0) {
        scaleMag += l_HIO.m0C * 10;
    }
    else {
        scaleMag += mScaleLocal * 10;
    }

    if (dLib_checkPlayerInCircle(current.pos, scaleMag, 20.0f)) {
        modeProcInit(MODE_EVENT);
    }
}

// Required to make rodata match
static const u8 dummy5[] = { 0x00, 0xFF, 0x00, 0x80};

/* 000004F0-000004F4       .text modeEventInit__12daObj_Hole_cFv */
void daObj_Hole_c::modeEventInit() {
    return;
}

/* 000004F4-000005D0       .text modeEvent__12daObj_Hole_cFv */
void daObj_Hole_c::modeEvent() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        int staffId = dComIfGp_evmng_getMyStaffId("Ypit00");

        if (dComIfGp_evmng_endCheck("DEFAULT_PITFALL")) {
            if (mExitIdx != 0xFF) {
                dLib_setNextStageBySclsNum(mExitIdx, current.roomNo);
            }
            else {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0, current.roomNo);
            }
        }
    }
    else {
        fopAcM_orderOtherEvent(this, "DEFAULT_PITFALL");
    }
}

/* 000005D0-000006C0       .text modeProc__12daObj_Hole_cFQ212daObj_Hole_c6Proc_ei */
void daObj_Hole_c::modeProc(daObj_Hole_c::Proc_e proc, int newMode) {
    typedef void (daObj_Hole_c::*daObjHole_mode_t)(void);

    struct mode_struct {
        daObjHole_mode_t init;
        daObjHole_mode_t exec;
        const char* name;
    };

    static const mode_struct mode_tbl[] = {
        {
            &daObj_Hole_c::modeWaitInit,
            &daObj_Hole_c::modeWait,
            "WAIT"
        },
        {
            &daObj_Hole_c::modeEventInit,
            &daObj_Hole_c::modeEvent,
            "EVENT"
        }
    };

    if (proc == PROC_INIT) {
        mMode = newMode;
        (this->*mode_tbl[mMode].init)();
    }
    else if (proc == PROC_EXEC) {
        (this->*mode_tbl[mMode].exec)();
    }
}

/* 000006C0-00000700       .text _execute__12daObj_Hole_cFv */
bool daObj_Hole_c::_execute() {
    modeProc(PROC_EXEC, MODE_NULL);
    setMtx();
    return false;
}

/* 00000700-00000738       .text debugDraw__12daObj_Hole_cFv */
void daObj_Hole_c::debugDraw() {
    cXyz pos = current.pos;
    pos.y += l_HIO.m10;
}

/* 00000738-000007BC       .text _draw__12daObj_Hole_cFv */
bool daObj_Hole_c::_draw() {
    if (l_HIO.m05 != 0) {
        debugDraw();
    }

    if (mHasModel == 0xFF) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpMdl, &tevStr);

        mDoExt_modelUpdateDL(mpMdl);
    }

    return true;
}

/* 000007BC-00000864       .text createInit__12daObj_Hole_cFv */
void daObj_Hole_c::createInit() {
    modeProcInit(MODE_WAIT);

    fopAcM_SetMtx(this, mpMdl->getBaseTRMtx());
    fopAcM_setCullSizeFar(this, 10.0f);

    mAcchCir.SetWall(100.0f, 10.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));

    mAcch.SetWallNone();
    mAcch.SetRoofNone();

    setMtx();
}

/* 00000864-00000928       .text _createHeap__12daObj_Hole_cFv */
BOOL daObj_Hole_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, AANA_BDL_AANA);

    JUT_ASSERT(0x13D, modelData != NULL);

    mpMdl = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);

    if (mpMdl == NULL) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/* 00000928-0000096C       .text getArg__12daObj_Hole_cFv */
void daObj_Hole_c::getArg() {
    u16 param = fopAcM_GetParamBit(fopAcM_GetParam(this), 0, 16);
    mExitIdx = param & 0xFF;
    mHasModel = param >> 8;

    mScaleLocal = home.angle.z;
    if (mScaleLocal == 0xFFFF) {
        mScaleLocal = 0;
    }
    
    if (mHasModel >= 1) {
        mHasModel = 0xFF;
    }
}

/* 0000096C-00000BA8       .text _create__12daObj_Hole_cFv */
cPhs_State daObj_Hole_c::_create() {
    fopAcM_SetupActor(this, daObj_Hole_c);

    cPhs_State result = dComIfG_resLoad(&mPhs, m_arc_name);
    if (result == cPhs_COMPLEATE_e) {
        getArg();

        if (mHasModel == 0xFF) {
            u32 heapResult = fopAcM_entrySolidHeap(this, createHeap_CB, 0x1000);

            if (heapResult == 0) {
                return cPhs_ERROR_e;
            }
        }

        createInit();
    }

    return result;
}

/* 0000122C-0000125C       .text _delete__12daObj_Hole_cFv */
bool daObj_Hole_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    return true;
}

/* 0000125C-0000127C       .text daObj_HoleCreate__FPv */
static cPhs_State daObj_HoleCreate(void* i_actor) {
    return static_cast<daObj_Hole_c*>(i_actor)->_create();
}

/* 0000127C-000012A0       .text daObj_HoleDelete__FPv */
static BOOL daObj_HoleDelete(void* i_actor) {
    return static_cast<daObj_Hole_c*>(i_actor)->_delete();
}

/* 000012A0-000012C4       .text daObj_HoleExecute__FPv */
static BOOL daObj_HoleExecute(void* i_actor) {
    return static_cast<daObj_Hole_c*>(i_actor)->_execute();
}

/* 000012C4-000012E8       .text daObj_HoleDraw__FPv */
static BOOL daObj_HoleDraw(void* i_actor) {
    return static_cast<daObj_Hole_c*>(i_actor)->_draw();
}

/* 000012E8-000012F0       .text daObj_HoleIsDelete__FPv */
static BOOL daObj_HoleIsDelete(void* i_actor) {
    return TRUE;
}

static actor_method_class daObj_HoleMethodTable = {
    (process_method_func)daObj_HoleCreate,
    (process_method_func)daObj_HoleDelete,
    (process_method_func)daObj_HoleExecute,
    (process_method_func)daObj_HoleIsDelete,
    (process_method_func)daObj_HoleDraw,
};

actor_process_profile_definition g_profile_OBJ_HOLE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_HOLE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Hole_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_HOLE,
    /* Actor SubMtd */ &daObj_HoleMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
