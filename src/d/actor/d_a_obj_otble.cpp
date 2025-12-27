/**
 * d_a_obj_otble.cpp
 * Object - Generic brown wooden tables
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_otble.h"
#include "d/res/res_okmono.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"

const daObj_Otble::Attr_c daObj_Otble::Act_c::M_attr = {0, 0};

/* 00000078-00000098       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* a_this) {
    return ((daObj_Otble::Act_c*)a_this)->_createHeap();
}

/* 00000098-00000168       .text set_mtx__Q211daObj_Otble5Act_cFv */
void daObj_Otble::Act_c::set_mtx() {
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = current.roomNo;
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), m2A4);
    mBgW->Move();
}

/* 00000168-000001BC       .text _execute__Q211daObj_Otble5Act_cFv */
BOOL daObj_Otble::Act_c::_execute() {
    if (attr()->m00) {
        return TRUE;
    }
    fopAcM_posMoveF(this, NULL);
    set_mtx();
    return TRUE;
}

/* 000001BC-000002E8       .text _draw__Q211daObj_Otble5Act_cFv */
BOOL daObj_Otble::Act_c::_draw() {
    static const f32 size[] = {1.0f, 2.0f};

    if (attr()->m01) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel);
    dComIfGd_setList();

    f32 fVar1 = mObjAcch.GetGroundH();
    cXyz* pFloorNrm = &dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd)->mNormal;
    if (pFloorNrm != NULL && fVar1 != -G_CM3D_F_INF) {
        dComIfGd_setSimpleShadow(&current.pos, fVar1, 100.0f, pFloorNrm, current.angle.y, size[m294], NULL);
    }
    return TRUE;
}

/* 000002E8-00000470       .text _createHeap__Q211daObj_Otble5Act_cFv */
BOOL daObj_Otble::Act_c::_createHeap() {
    static const s32 bdl[] = {OKMONO_BDL_OTABLE, OKMONO_BDL_OTABLEL};
    static const s32 dzb[] = {OKMONO_DZB_OTBLE, OKMONO_DZB_OTBLE_L};

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Okmono", bdl[m294]);
    JUT_ASSERT(191, modelData != NULL);

    mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mModel == NULL) {
        return false;
    }

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    cMtx_copy(mDoMtx_stack_c::get(), m2A4);

    mBgW = new dBgW();
    if (mBgW == NULL) {
        return false;
    }

    if (mBgW->Set((cBgD_t*)dComIfG_getObjectRes("Okmono", dzb[m294]), dBgW::MOVE_BG_e, &m2A4) == TRUE) {
        return false;
    }
    return true;
}

/* 00000470-000005A0       .text CreateInit__Q211daObj_Otble5Act_cFv */
void daObj_Otble::Act_c::CreateInit() {
    dComIfG_Bgsp()->Regist(mBgW, this);

    mObjAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mObjAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    mObjAcch.SetWallNone();
    mObjAcch.SetWaterNone();
    mObjAcch.SetRoofNone();

    fopAcM_SetGravity(this, -6.5f);
    fopAcM_posMoveF(this, NULL);
    set_mtx();
    fopAcM_SetMtx(this, mModel->getBaseTRMtx());

    if (m294 == 1) {
        fopAcM_setCullSizeBox(this, -100.0f, -0.0f, -200.0f, 100.0f, 150.0f, 200.0f);
    } else {
        fopAcM_setCullSizeBox(this, -100.0f, -0.0f, -100.0f, 100.0f, 150.0f, 100.0f);
    }
    fopAcM_setCullSizeFar(this, 10.0f);
}

cPhs_State daObj_Otble::Act_c::_create() {
    static const u32 heapsize[] = {0x1240, 0x1240};

#if VERSION == VERSION_DEMO
    m294 = fopAcM_GetParam(this) & 0xff;
    if (m294 > 1) {
        m294 = 1;
    }

    cPhs_State ret = dComIfG_resLoad(&mPhase, "Okmono");
    if (ret == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(this, daObj_Otble::Act_c);
#else
    fopAcM_SetupActor(this, daObj_Otble::Act_c);
    m294 = fopAcM_GetParam(this) & 0xFF;
    if (m294 > 1) {
        m294 = 1;
    }

    cPhs_State ret = dComIfG_resLoad(&mPhase, "Okmono");
    if (ret == cPhs_COMPLEATE_e) {
#endif
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, heapsize[m294])) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }
    return ret;
}

bool daObj_Otble::Act_c::_delete() {
    dComIfG_resDelete(&mPhase, "Okmono");
    if (mBgW != NULL && mBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mBgW);
    }
    return true;
}

/* 000005A0-000006AC       .text Create__Q211daObj_Otble4MthdFPv */
cPhs_State daObj_Otble::Mthd::Create(void* v_this) {
    return ((daObj_Otble::Act_c*)v_this)->_create();
}

/* 0000071C-0000079C       .text Delete__Q211daObj_Otble4MthdFPv */
BOOL daObj_Otble::Mthd::Delete(void* v_this) {
    return ((daObj_Otble::Act_c*)v_this)->_delete();
}

/* 0000079C-000007BC       .text Execute__Q211daObj_Otble4MthdFPv */
BOOL daObj_Otble::Mthd::Execute(void* v_this) {
    return ((daObj_Otble::Act_c*)v_this)->_execute();
}

/* 000007BC-000007DC       .text Draw__Q211daObj_Otble4MthdFPv */
BOOL daObj_Otble::Mthd::Draw(void* v_this) {
    return ((daObj_Otble::Act_c*)v_this)->_draw();
}

/* 000007DC-000007E4       .text IsDelete__Q211daObj_Otble4MthdFPv */
BOOL daObj_Otble::Mthd::IsDelete(void*) {
    return TRUE;
}

actor_method_class daObj_Otble::Mthd::Table = {
    (process_method_func)daObj_Otble::Mthd::Create,
    (process_method_func)daObj_Otble::Mthd::Delete,
    (process_method_func)daObj_Otble::Mthd::Execute,
    (process_method_func)daObj_Otble::Mthd::IsDelete,
    (process_method_func)daObj_Otble::Mthd::Draw,
};

actor_process_profile_definition g_profile_OBJ_OTBLE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_OTBLE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Otble::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_OTBLE,
    /* Actor SubMtd */ &daObj_Otble::Mthd::Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
