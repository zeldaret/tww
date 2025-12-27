/**
 * d_a_mtoge.cpp
 * Object - Forsaken Fortress - Spikes
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mtoge.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_mtoge.h"
#include "f_op/f_op_actor_mng.h"

const char daMtoge_c::M_arcname[] = "Mtoge";

enum Action {
    ACT_WAIT,
    ACT_HIND,
    ACT_UP,
    ACT_ARRIVAL,
    ACT_DOWN,
};

/* 00000078-00000084       .text getSwbit__9daMtoge_cFv */
u8 daMtoge_c::getSwbit() {
    return fopAcM_GetParam(this) & 0xFF;
}

/* 00000084-000000A4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daMtoge_c*>(i_this)->CreateHeap();
}

/* 000000A4-000001E8       .text CreateHeap__9daMtoge_cFv */
BOOL daMtoge_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, MTOGE_BMD_S_MTOGE));
    JUT_ASSERT(0x70, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203U);

    if (!mpModel) {
        return FALSE;
    }

    mpBgW = new dBgW();

    if (!mpBgW)
        return FALSE;

    cBgD_t* pData = (cBgD_t*)dComIfG_getObjectRes(M_arcname, MTOGE_DZB_S_MTOGE);

    if (!pData) {
        return FALSE;
    }

    calcMtx();

    if (mpBgW->Set(pData, cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx()) == true) {
        return FALSE;
    }

    return TRUE;
}

/* 000001E8-00000254       .text calcMtx__9daMtoge_cFv */
void daMtoge_c::calcMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + mHeightOffset, current.pos.z);
    mDoMtx_stack_c::YrotM(home.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000254-00000384       .text CreateInit__9daMtoge_cFv */
BOOL daMtoge_c::CreateInit() {
    s32 sw = getSwbit();

    if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
        JUT_ASSERT(0xA8, FALSE);
    }

    tevStr.mRoomNo = fopAcM_GetRoomNo(this);

    if (sw == 0xFF) {
        mAction = ACT_WAIT;
    } else if (dComIfGs_isSwitch(sw + 1, fopAcM_GetRoomNo(this))) {
        mAction = ACT_WAIT;
        mHeightOffset = -300.0f;
    } else if (!dComIfGs_isSwitch(sw, fopAcM_GetRoomNo(this))) {
        mAction = ACT_HIND;
        mHeightOffset = -300.0f;
    } else {
        mAction = ACT_ARRIVAL;
    }

    calcMtx();
    mpBgW->Move();

    return TRUE;
}

/* 00000384-0000041C       .text create__9daMtoge_cFv */
cPhs_State daMtoge_c::create() {
    fopAcM_SetupActor(this, daMtoge_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhaseProcReq, M_arcname);
    if (phase_state != cPhs_COMPLEATE_e) {
        return phase_state;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x15C0U)) {
        return cPhs_ERROR_e;
    }

    CreateInit();

    return cPhs_COMPLEATE_e;
}

/* 0000041C-00000424       .text daMtoge_actionWait__FP9daMtoge_c */
BOOL daMtoge_actionWait(daMtoge_c*) {
    return TRUE;
}

/* 00000424-000004D4       .text daMtoge_actionHind__FP9daMtoge_c */
BOOL daMtoge_actionHind(daMtoge_c* i_this) {
    s32 swbit = i_this->getSwbit();

    if (dComIfGs_isSwitch(swbit, fopAcM_GetRoomNo(i_this)) != 0) {
        i_this->setAction(ACT_UP);
        fopAcM_SetSpeedF(i_this, 0.0f);

        fopAcM_seStart(i_this, JA_SE_OBJ_TOGE_OUT, 0);
    }

    return TRUE;
}

/* 000004D4-00000550       .text daMtoge_actionUp__FP9daMtoge_c */
BOOL daMtoge_actionUp(daMtoge_c* i_this) {
    cLib_chaseF(&i_this->speedF, 30.0f, 4.0f);

    if (cLib_chaseF(&i_this->mHeightOffset, 0.0f, fopAcM_GetSpeedF(i_this))) {
        i_this->setAction(ACT_ARRIVAL);
    }

    i_this->calcMtx();
    i_this->mpBgW->Move();

    return TRUE;
}

/* 00000550-00000600       .text daMtoge_actionArrival__FP9daMtoge_c */
BOOL daMtoge_actionArrival(daMtoge_c* i_this) {
    s32 swbit = i_this->getSwbit();

    if (dComIfGs_isSwitch(swbit, fopAcM_GetRoomNo(i_this)) == 0) {
        i_this->setAction(ACT_DOWN);
        fopAcM_SetSpeedF(i_this, 0.0f);

        fopAcM_seStart(i_this, JA_SE_OBJ_TOGE_IN, 0);
    }

    return TRUE;
}

/* 00000600-0000067C       .text daMtoge_actionDown__FP9daMtoge_c */
BOOL daMtoge_actionDown(daMtoge_c* i_this) {
    cLib_chaseF(&i_this->speedF, 30.0f, 4.0f);

    if (cLib_chaseF(&i_this->mHeightOffset, -300.0f, fopAcM_GetSpeedF(i_this)) != 0) {
        i_this->setAction(ACT_HIND);
    }

    i_this->calcMtx();
    i_this->mpBgW->Move();

    return TRUE;
}

BOOL daMtoge_c::execute() {
    static BOOL (*l_action[])(daMtoge_c*) = {
        daMtoge_actionWait,
        daMtoge_actionHind,
        daMtoge_actionUp,
        daMtoge_actionArrival,
        daMtoge_actionDown,
    };

    l_action[mAction](this);

    return TRUE;
}

BOOL daMtoge_c::draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    mDoExt_modelUpdateDL(mpModel);

    return TRUE;
}

/* 0000067C-000006DC       .text daMtoge_Draw__FP9daMtoge_c */
static BOOL daMtoge_Draw(daMtoge_c* i_this) {
    return i_this->draw();
}

/* 000006DC-00000718       .text daMtoge_Execute__FP9daMtoge_c */
static BOOL daMtoge_Execute(daMtoge_c* i_this) {
    return i_this->execute();
}

/* 00000718-00000720       .text daMtoge_IsDelete__FP9daMtoge_c */
static BOOL daMtoge_IsDelete(daMtoge_c*) {
    return TRUE;
}

/* 00000720-00000790       .text daMtoge_Delete__FP9daMtoge_c */
static BOOL daMtoge_Delete(daMtoge_c* i_this) {
    if (i_this->heap != NULL) {
        dComIfG_Bgsp()->Release(i_this->mpBgW);
    }

    dComIfG_resDelete(&i_this->mPhaseProcReq, i_this->M_arcname);

    i_this->~daMtoge_c();

    return TRUE;
}

/* 00000790-000007B0       .text daMtoge_Create__FP10fopAc_ac_c */
static cPhs_State daMtoge_Create(fopAc_ac_c* i_this) {
    return static_cast<daMtoge_c*>(i_this)->create();
}

static actor_method_class l_daMtoge_Method = {
    (process_method_func)daMtoge_Create,
    (process_method_func)daMtoge_Delete,
    (process_method_func)daMtoge_Execute,
    (process_method_func)daMtoge_IsDelete,
    (process_method_func)daMtoge_Draw,
};

actor_process_profile_definition g_profile_MTOGE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MTOGE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daMtoge_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MTOGE,
    /* Actor SubMtd */ &l_daMtoge_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
