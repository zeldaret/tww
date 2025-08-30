/**
 * d_a_mdoor.cpp
 * Object - Wooden/Metal bars (Forbidden Woods, Cabana Maze, Dragon Roost Cavern, Earth Temple, etc.)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mdoor.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/res/res_mdoor.h"
#include "f_op/f_op_actor_mng.h"

const char daMdoor_c::M_arcname[] = "Mdoor";

/* 00000078-00000084       .text getSwbit__9daMdoor_cFv */
u8 daMdoor_c::getSwbit() {
    return (fopAcM_GetParam(this) >> 0) & 0xFF;
}

/* 00000084-00000090       .text getType__9daMdoor_cFv */
u8 daMdoor_c::getType() {
    return (fopAcM_GetParam(this) >> 8) & 0xFF;
}

/* 00000090-0000009C       .text getToolId__9daMdoor_cFv */
u8 daMdoor_c::getToolId() {
    return (fopAcM_GetParam(this) >> 16) & 0xFF;
}

/* 0000009C-000000A8       .text getShapeType__9daMdoor_cFv */
u8 daMdoor_c::getShapeType() {
    return (fopAcM_GetParam(this) >> 24) & 0xFF;
}

/* 000000A8-000000C8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* a_this) {
    return ((daMdoor_c*)a_this)->CreateHeap();
}

/* 000000C8-00000230       .text CreateHeap__9daMdoor_cFv */
BOOL daMdoor_c::CreateHeap() {
    s32 modelRes;
    s32 bgdRes;

    switch (getShapeType()) {
        case 1:
            modelRes = MDOOR_BDL_MORI2;
            bgdRes = MDOOR_DZB_MORI2;
            break;
        
        default:
            modelRes = MDOOR_BDL_MORI1;
            bgdRes = MDOOR_DZB_MORI1;
            break;
    }

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, modelRes));
    JUT_ASSERT(144, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModel == NULL) {
        return FALSE;
    }

    mpBgW = new dBgW();
    if (mpBgW == NULL) {
        return FALSE;
    }

    cBgD_t* pData = (cBgD_t*)dComIfG_getObjectRes(M_arcname, bgdRes);
    if (pData == NULL) {
        return FALSE;
    }

    calcMtx();

    if (mpBgW->Set(pData, cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx()) == TRUE) {
        return FALSE;
    }
    return TRUE;
}

/* 00000230-0000029C       .text calcMtx__9daMdoor_cFv */
void daMdoor_c::calcMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m2CC, current.pos.z);
    mDoMtx_stack_c::YrotM(home.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 0000029C-00000344       .text smokeInit__9daMdoor_cFv */
void daMdoor_c::smokeInit() {
    JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_COMMON_2022, &current.pos, &shape_angle, NULL, 0xAA, &m290, fopAcM_GetRoomNo(this));
    if (emitter != NULL) {
        emitter->setRate(16.0f);
        emitter->setSpread(0.35f);

        JGeometry::TVec3<f32> vec;
        vec.set(2.0f, 2.0f, 2.0f);
        emitter->setGlobalScale(vec);
    }
}

/* 00000344-00000370       .text smokeEnd__9daMdoor_cFv */
void daMdoor_c::smokeEnd() {
    m290.remove();
}

/* 00000370-000005E0       .text CreateInit__9daMdoor_cFv */
BOOL daMdoor_c::CreateInit() {
    fopAc_ac_c* a_this = (fopAc_ac_c*)this;
    s32 uVar1;
    u8 bVar5;
    
    uVar1 = getSwbit();
    bVar5 = getType();

    if (dComIfG_Bgsp()->Regist(mpBgW, a_this)) {
        JUT_ASSERT(236, FALSE);
    }

    a_this->tevStr.mRoomNo = fopAcM_GetRoomNo(a_this);
    m2CC = 0.0f;
    m2C8 = 0xFF;

    switch (bVar5) {
        case 0:
            if (dComIfGs_isEventBit(0x1101)) {
                setAction(daMdoor_c::ACT_WAIT3_e);
            } else {
                setAction(daMdoor_c::ACT_DEMO_WAIT_e);
                m2CC = 280.0f;
            }
            m2C6 = dComIfGp_evmng_getEventIdx("MORI1_EVENT", 0xFF);
            break;

        case 1:
            if (dComIfGs_isEventBit(0x1101)) {
                setAction(daMdoor_c::ACT_WAIT7_e);
                m2CC = 280.0f;
            } else {
                dComIfGs_offEventBit(0x1140);
                setAction(daMdoor_c::ACT_GENOCIDE_e);
                m2C6 = dComIfGp_evmng_getEventIdx("DEFAULT_STOP_OPEN", 0xFF);
                m2C4 = 1;
            }
            break;

        case 2:
            if (uVar1 == 0xFF || dComIfGs_isSwitch(uVar1, fopAcM_GetRoomNo(a_this))) {
                setAction(daMdoor_c::ACT_WAIT11_e);
                m2CC = 280.0f;
            } else {
                m2C8 = getToolId();
                m2C6 = dComIfGp_evmng_getEventIdx("DEFAULT_STOP_OPEN", getToolId());
                if (m2C8 != 0xFF) {
                    setAction(daMdoor_c::ACT_SWITCH12_e);
                } else {
                    setAction(daMdoor_c::ACT_SWITCH8_e);
                }
            }
            break;

        default:
            setAction(daMdoor_c::ACT_WAIT0_e);
            break;
    }

    a_this->attention_info.position.y += 150.0f;
    a_this->eyePos.y += 150.0f;
    calcMtx();
    mpBgW->Move();
    return TRUE;
}

/* 000005E0-00000698       .text create__9daMdoor_cFv */
cPhs_State daMdoor_c::create() {
    cPhs_State ret = dComIfG_resLoad(&mPhase, M_arcname);
#if VERSION == VERSION_DEMO
    if (ret != cPhs_COMPLEATE_e) {
        return ret;
    }
    fopAcM_SetupActor(this, daMdoor_c);
#else
    fopAcM_SetupActor(this, daMdoor_c);
    if (ret != cPhs_COMPLEATE_e) {
        return ret;
    }
#endif

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1640)) {
        return cPhs_ERROR_e;
    }

    CreateInit();
    return cPhs_COMPLEATE_e;
}

/* 00000698-00000958       .text demoProc__9daMdoor_cFv */
void daMdoor_c::demoProc() {
    static char* action_table[] = {
        "WAIT", "CLOSE", "STOP_OPEN",
    };

    s32 actIdx = dComIfGp_evmng_getMyActIdx(m2C0, action_table, ARRAY_SIZE(action_table), 0, 0);

    if (dComIfGp_evmng_getIsAddvance(m2C0)) {
        switch (actIdx) {
            case 1:
                speedF = 0.0f;
                setFlag(1);
                fopAcM_seStart(this, JA_SE_OBJ_CAGE_CLOSE, 0);
                break;
                
            case 2:
                speedF = 0.0f;
                if (getShapeType() != 1) {
                    dComIfGp_particle_set(dPa_name::ID_SCENE_81B2, &current.pos, &current.angle);
                }
                fopAcM_seStart(this, JA_SE_OBJ_CAGE_OPEN, 0);
                break;
        }
    }

    switch (actIdx) {
        case 1:
            cLib_chaseF(&speedF, 60.0f, 6.0f);
            if (cLib_chaseF(&m2CC, 0.0f, speedF)) {
                dComIfGp_evmng_cutEnd(m2C0);
                if (chkFlag(1)) {
                    clrFlag(1);
                    if (getShapeType() != 1) {
                        dComIfGp_particle_set(dPa_name::ID_SCENE_81B2, &current.pos, &current.angle);
                    }
                    smokeInit();
                }
            }
            calcMtx();
            mpBgW->Move();
            break;

        case 2:
            cLib_chaseF(&speedF, 30.0f, 3.0f);
            if (cLib_chaseF(&m2CC, 280.0f, speedF)) {
                dComIfGp_evmng_cutEnd(m2C0);
            }
            calcMtx();
            mpBgW->Move();
            break;

        default:
            dComIfGp_evmng_cutEnd(m2C0);
            break;
    }
}

/* 00000958-00000960       .text daMdoor_actionWait__FP9daMdoor_c */
BOOL daMdoor_actionWait(daMdoor_c*) {
    return TRUE;
}

/* 00000960-000009E8       .text daMdoor_actionDemoWait__FP9daMdoor_c */
BOOL daMdoor_actionDemoWait(daMdoor_c* i_this) {
    if (dComIfGp_evmng_startCheck(i_this->m2C6)) {
        i_this->nextAction();
        i_this->m2C0 = dComIfGp_evmng_getMyStaffId("Mori1", NULL, 0);
        i_this->demoProc();
    }
    return TRUE;
}

/* 000009E8-00000A4C       .text daMdoor_actionDemo__FP9daMdoor_c */
BOOL daMdoor_actionDemo(daMdoor_c* i_this) {
    if (dComIfGp_evmng_endCheck(i_this->m2C6)) {
        i_this->nextAction();
        return TRUE;
    }
    i_this->demoProc();
    return TRUE;
}

/* 00000A4C-00000AF4       .text daMdoor_actionGenocide__FP9daMdoor_c */
BOOL daMdoor_actionGenocide(daMdoor_c* i_this) {
    if (fopAcM_myRoomSearchEnemy(fopAcM_GetRoomNo(i_this)) == NULL) {
        if (i_this->m2C4 > 0) {
            i_this->m2C4--;
        } else {
            switch (i_this->getType()) {
                case 1:
                    mDoAud_subBgmStop();
                    break;
            }
            fopAcM_orderOtherEventId(i_this, i_this->m2C6, i_this->m2C8, 0xFFFF, 0, 1);
            i_this->nextAction();
        }
    }
    return TRUE;
}

/* 00000AF4-00000C6C       .text daMdoor_actionOpen__FP9daMdoor_c */
BOOL daMdoor_actionOpen(daMdoor_c* i_this) {
    if (dComIfGp_evmng_endCheck(i_this->m2C6)) {
        i_this->nextAction();
        dComIfGp_event_reset();
        return TRUE;
    }

    if (i_this->m2C4 > 0) {
        i_this->m2C4--;
        if (i_this->m2C4 == 0) {
            i_this->speedF = 0.0f;
            if (i_this->getShapeType() != 1) {
                dComIfGp_particle_set(dPa_name::ID_SCENE_81B2, &i_this->current.pos, &i_this->current.angle);
            }
            fopAcM_seStart(i_this, JA_SE_OBJ_CAGE_OPEN, 0);
        }
    }

    if (i_this->m2C4 == 0) {
        cLib_chaseF(&i_this->speedF, 30.0f, 3.0f);
        cLib_chaseF(&i_this->m2CC, 280.0f, i_this->speedF);
        i_this->calcMtx();
        i_this->mpBgW->Move();
    }
    return TRUE;
}

/* 00000C6C-00000CE8       .text daMdoor_actionSwitch__FP9daMdoor_c */
BOOL daMdoor_actionSwitch(daMdoor_c* i_this) {
    s32 uVar1 = i_this->getSwbit();
    if (dComIfGs_isSwitch(uVar1, fopAcM_GetRoomNo(i_this))) {
        fopAcM_orderOtherEventId(i_this, i_this->m2C6, i_this->m2C8, 0xFFFF, 0, 1);
        i_this->nextAction();
    }
    return TRUE;
}

/* 00000CE8-00000DD0       .text daMdoor_actionReady__FP9daMdoor_c */
BOOL daMdoor_actionReady(daMdoor_c* i_this) {
    if (i_this->eventInfo.checkCommandDemoAccrpt()) {
        i_this->m2C0 = dComIfGp_evmng_getMyStaffId("SHUTTER_DOOR", NULL, 0);
        i_this->demoProc();
        i_this->nextAction();
        s32 uVar2 = i_this->getSwbit();
        if (uVar2 != 0xFF) {
            dComIfGs_isSwitch(uVar2, fopAcM_GetRoomNo(i_this));
        }

        switch (i_this->getType()) {
            case 1:
                dComIfGs_onEventBit(0x1140);
                break;
        }
    } else {
        fopAcM_orderOtherEventId(i_this, i_this->m2C6, i_this->m2C8, 0xFFFF, 0, 1);
    }
    return TRUE;
}

/* 00000DD0-00000E60       .text daMdoor_actionReadyOpen__FP9daMdoor_c */
BOOL daMdoor_actionReadyOpen(daMdoor_c* i_this) {
    if (i_this->eventInfo.checkCommandDemoAccrpt()) {
        i_this->nextAction();
        s32 uVar1 = i_this->getSwbit();
        if (uVar1 != 0xFF) {
            dComIfGs_isSwitch(uVar1, fopAcM_GetRoomNo(i_this));
        }
        i_this->m2C4 = 0x14;
    } else {
        fopAcM_orderOtherEventId(i_this, i_this->m2C6, i_this->m2C8, 0xFFFF, 0, 1);
    }
    return TRUE;
}

/* 00000E60-00000ED4       .text daMdoor_actionEvent__FP9daMdoor_c */
BOOL daMdoor_actionEvent(daMdoor_c* i_this) {
    if (dComIfGp_evmng_endCheck(i_this->m2C6)) {
        i_this->nextAction();
        dComIfGp_event_reset();
    } else {
        i_this->demoProc();
    }
    return TRUE;
}

BOOL daMdoor_c::draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

/* 00000ED4-00000F34       .text daMdoor_Draw__FP9daMdoor_c */
static BOOL daMdoor_Draw(daMdoor_c* i_this) {
    return i_this->draw();
}

BOOL daMdoor_c::execute() {
    typedef BOOL (*actionFunc)(daMdoor_c*);
    static actionFunc l_action[] = {
        daMdoor_actionWait,
        daMdoor_actionDemoWait,
        daMdoor_actionDemo,
        daMdoor_actionWait,
        daMdoor_actionGenocide,
        daMdoor_actionReady,
        daMdoor_actionEvent,
        daMdoor_actionWait,
        daMdoor_actionSwitch,
        daMdoor_actionReady,
        daMdoor_actionEvent,
        daMdoor_actionWait,
        daMdoor_actionSwitch,
        daMdoor_actionReadyOpen,
        daMdoor_actionOpen,
        daMdoor_actionWait,
    };
    
    smokeEnd();
    l_action[mAction](this);
    return TRUE;
}

/* 00000F34-00000F84       .text daMdoor_Execute__FP9daMdoor_c */
static BOOL daMdoor_Execute(daMdoor_c* i_this) {
    return i_this->execute();
}

/* 00000F84-00000F8C       .text daMdoor_IsDelete__FP9daMdoor_c */
static BOOL daMdoor_IsDelete(daMdoor_c*) {
    return TRUE;
}

/* 00000F8C-00001054       .text daMdoor_Delete__FP9daMdoor_c */
static BOOL daMdoor_Delete(daMdoor_c* i_this) {
#if VERSION > VERSION_DEMO
    if (i_this->heap != NULL) 
#endif
    {
        dComIfG_Bgsp()->Release(i_this->mpBgW);
    }

#if VERSION > VERSION_DEMO
    i_this->smokeEnd();
#endif
    dComIfG_resDelete(&i_this->mPhase, daMdoor_c::M_arcname);

    i_this->~daMdoor_c();

    return TRUE;
}

/* 00001054-00001074       .text daMdoor_Create__FP10fopAc_ac_c */
static cPhs_State daMdoor_Create(fopAc_ac_c* i_this) {
    return ((daMdoor_c*)i_this)->create();
}

static actor_method_class l_daMdoor_Method = {
    (process_method_func)daMdoor_Create,
    (process_method_func)daMdoor_Delete,
    (process_method_func)daMdoor_Execute,
    (process_method_func)daMdoor_IsDelete,
    (process_method_func)daMdoor_Draw,
};

actor_process_profile_definition g_profile_MDOOR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MDOOR,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daMdoor_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MDOOR,
    /* Actor SubMtd */ &l_daMdoor_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
