//
// Generated by dtk
// Translation Unit: d_a_pedestal.cpp
//

#include "d/actor/d_a_pedestal.h"
#include "d/d_procname.h"
#include "d/res/res_hdai1.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

const char daPedestal::daPds_c::m_arcname[] = "Hdai1";

/* 00000078-000000DC       .text _delete__Q210daPedestal7daPds_cFv */
BOOL daPedestal::daPds_c::_delete() {
    if (heap != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }

    mInfiniteEcallBack.end();
    dComIfG_resDelete(&mPhs, m_arcname);

    return TRUE;
}

namespace daPedestal {
/* 000000DC-000000FC       .text CheckCreateHeap__10daPedestalFP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daPds_c*>(i_this)->CreateHeap();
}

}  // namespace daPedestal

/* 000000FC-00000244       .text CreateHeap__Q210daPedestal7daPds_cFv */
BOOL daPedestal::daPds_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, HDAI1_BDL_HDAI1));
    JUT_ASSERT(0xC1, modelData != 0);

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203U);

    if (!mpModel) {
        return FALSE;
    }
    if(!initBrkAnm(3, false)) {
        return FALSE;
    }

    mpBgW = new dBgW();

   if (mpBgW != NULL) {
        return mpBgW->Set((cBgD_t*)dComIfG_getObjectRes(m_arcname, HDAI1_DZB_HDAI), cBgW::MOVE_BG_e, &mMtx) == true ? FALSE : TRUE;
    }

    return FALSE;
}

static char* l_os_name[] = {
    "Os",
    "Os1",
    "Os2"
};

/* 00000244-00000380       .text CreateInit__Q210daPedestal7daPds_cFv */
void daPedestal::daPds_c::CreateInit() {
    mParam = daPds__prm::getParam(this);

    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -150.0f, -20.0f, -150.0f, 150.0f, 250.0f, 150.0f);

    if (!mParam) {
        if (wakeupCheck()) {
            if (subtype <= 2) {
                fopAc_ac_c* pActor = fopAcM_searchFromName(l_os_name[subtype], 0, 0);

                if (pActor != NULL && fopAcM_searchActorDistanceXZ(this, pActor) < 100.0f) {
                    pActor->current.pos.y = current.pos.y;
                }
            }

            current.pos.y -= 240.0f;
        }
    } else if (mParam == 1 && finishCheck()) {
        current.pos.y += 240.0f;
    }

    set_mtx();
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mpBgW->Move();
}

/* 00000380-00000474       .text _create__Q210daPedestal7daPds_cFv */
s32 daPedestal::daPds_c::_create() {
    fopAcM_SetupActor(this, daPedestal::daPds_c);

    s32 phase_state = dComIfG_resLoad(&mPhs, m_arcname);

    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2000)) {
            mpBgW = NULL;
            return cPhs_ERROR_e;
        }

        CreateInit();
    }

    return phase_state;
}

/* 00000474-0000052C       .text getMyStaffId__Q210daPedestal7daPds_cFv */
int daPedestal::daPds_c::getMyStaffId() {
    if (subtype == 0) {
        return dComIfGp_evmng_getMyStaffId("Hdai1");
    } else if (subtype == 1) {
        return dComIfGp_evmng_getMyStaffId("Hdai2");
    } else if (subtype == 2) {
        return dComIfGp_evmng_getMyStaffId("Hdai3");
    }

    return -1;
}

/* 0000052C-000005D8       .text wakeupCheck__Q210daPedestal7daPds_cFv */
BOOL daPedestal::daPds_c::wakeupCheck() {
    if (subtype == 0) {
        if (dComIfGs_isEventBit(0x1780)) {
            return TRUE;
        }
    } else if (subtype == 1) {
        if (dComIfGs_isEventBit(0x1740)) {
            return TRUE;
        }
    } else if (subtype == 2) {
        if (dComIfGs_isEventBit(0x1720)) {
            return TRUE;
        }
    }

    return FALSE;
}

/* 000005D8-00000684       .text finishCheck__Q210daPedestal7daPds_cFv */
BOOL daPedestal::daPds_c::finishCheck() {
    if (subtype == 0) {
        if (dComIfGs_isEventBit(0x1710)) {
            return TRUE;
        }
    } else if (subtype == 1) {
        if (dComIfGs_isEventBit(0x1704)) {
            return TRUE;
        }
    } else if (subtype == 2) {
        if (dComIfGs_isEventBit(0x1B01)) {
            return TRUE;
        }
    }

    return FALSE;
}

/* 00000684-0000073C       .text setAction__Q210daPedestal7daPds_cFMQ210daPedestal7daPds_cFPCvPvPv_iPv */
BOOL daPedestal::daPds_c::setAction(ActionFunc_t action, void* param_1) {
    if (mAction != NULL) {
        unk30C = 0xFF;
        (this->*mAction)(param_1);
    }

    mAction = action;
    unk30C = 0;
    unk310 = 0;
    unk312 = 0;
    unk314 = 0;
    unk316 = 0;
    unk31C = 0.0f;
    (this->*mAction)(param_1);

    return TRUE;
}

/* 0000073C-000007C4       .text action__Q210daPedestal7daPds_cFPv */
void daPedestal::daPds_c::action(void* param_1) {
    if (!mAction) {
        setAction(&waitAction, NULL);
    }

    (this->*mAction)(param_1);
}

/* 000007C4-000007E0       .text waitAction__Q210daPedestal7daPds_cFPv */
BOOL daPedestal::daPds_c::waitAction(void*) {
    if (unk30C == 0) {
        unk30C += 1;
    }

    return TRUE;
}

typedef void (daPedestal::daPds_c::* eventInitFunc)(int);
static eventInitFunc event_init_tbl[] = {
    &daPedestal::daPds_c::initialDefault,
    &daPedestal::daPds_c::initialMoveEvent,
    &daPedestal::daPds_c::initialEffectSet,
    &daPedestal::daPds_c::initialEffectEnd,
};

typedef BOOL (daPedestal::daPds_c::* eventActionFunc)(int);
static eventActionFunc event_action_tbl[] = {
    &daPedestal::daPds_c::actionDefault,
    &daPedestal::daPds_c::actionMoveEvent,
    &daPedestal::daPds_c::actionDefault,
    &daPedestal::daPds_c::actionDefault,
};

static char* cut_name_tbl[] = {
    "WAIT",
    "MOVE",
    "EFFSET",
    "EFFEND"
};

/* 000007E0-000008E4       .text eventProc__Q210daPedestal7daPds_cFv */
BOOL daPedestal::daPds_c::eventProc() {
    int staffIdx = getMyStaffId();

    if (dComIfGp_event_runCheck()) {
        if (staffIdx != -1) {
            int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);

            if (actIdx == -1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            } else {
                if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                    (this->*event_init_tbl[actIdx])(staffIdx);
                }

                if((this->*event_action_tbl[actIdx])(staffIdx)) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }
        }

        return TRUE;
    }

    return FALSE;
}

/* 000008E4-000008E8       .text initialDefault__Q210daPedestal7daPds_cFi */
void daPedestal::daPds_c::initialDefault(int) {}

/* 000008E8-000008F0       .text actionDefault__Q210daPedestal7daPds_cFi */
BOOL daPedestal::daPds_c::actionDefault(int) {
    return TRUE;
}

/* 000008F0-000009A8       .text initialMoveEvent__Q210daPedestal7daPds_cFi */
void daPedestal::daPds_c::initialMoveEvent(int staffIdx) {
    f32* pSpeed = dComIfGp_evmng_getMyFloatP(staffIdx, "Speed");

    if (pSpeed) {
        speed.y = *pSpeed;
    } else {
        speed.y = 1.0f;
    }

    f32* pDist = dComIfGp_evmng_getMyFloatP(staffIdx, "Dist");
    if (pDist) {
        unk304 = current.pos.y + *pDist;
    } else {
        unk304 = current.pos.y;
    }
}

/* 000009A8-00000AEC       .text actionMoveEvent__Q210daPedestal7daPds_cFi */
BOOL daPedestal::daPds_c::actionMoveEvent(int) {
    current.pos.y += speed.y;

    BOOL ret = FALSE;

    if (speed.y < 0.0f) {
        if (current.pos.y <= unk304) {
            current.pos.y = unk304;
            speed.y = 0.0f;
            ret = TRUE;
        }
    } else if (speed.y > 0.0f) {
        if (current.pos.y >= unk304) {
            current.pos.y = unk304;
            speed.y = 0.0f;
            ret = TRUE;
        }
    } else {
        current.pos.y = unk304;
        ret = TRUE;
    }

    if (ret) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_DAI_STOP, 0);
    } else {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_DAI_MOVE, 0);
    }

    return ret;
}

/* 00000AEC-00000B40       .text initialEffectSet__Q210daPedestal7daPds_cFi */
void daPedestal::daPds_c::initialEffectSet(int) {
    mInfiniteEcallBack.makeEmitter(0x826DU, &current.pos, &shape_angle, NULL);
    initBrkAnm(0, true);
}

/* 00000B40-00000B80       .text initialEffectEnd__Q210daPedestal7daPds_cFi */
void daPedestal::daPds_c::initialEffectEnd(int) {
    mInfiniteEcallBack.end();
    initBrkAnm(2, true);
}

/* 00000B80-00000C10       .text set_mtx__Q210daPedestal7daPds_cFv */
void daPedestal::daPds_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000C10-00000D58       .text initBrkAnm__Q210daPedestal7daPds_cFUcb */
BOOL daPedestal::daPds_c::initBrkAnm(u8 param_1, bool param_2) {
    struct AnmTableEntry {
        /* 0x00 */ int loopMode;
        /* 0x04 */ f32 speed;
        /* 0x08 */ s32 unk_4;
    };  // Size: 0x0C

    static AnmTableEntry brkAnmTbl[] = {
        {J3DFrameCtrl::LOOP_REPEAT_e,   1.0f,  0},
        {J3DFrameCtrl::LOOP_ONCE_e,     0.0f,  0},
        {J3DFrameCtrl::LOOP_ONCE_e,     0.0f,  0},
        {J3DFrameCtrl::LOOP_ONCE_e,     0.0f, -1},
    };

    J3DModelData* modelData = mpModel->getModelData();
    bool ret = false;

    J3DAnmTevRegKey* a_brk = (J3DAnmTevRegKey*)(dComIfG_getObjectRes(m_arcname, HDAI1_BRK_HDAI1));
    JUT_ASSERT(0x28C, a_brk != 0);


    if (mBrk.init(modelData, a_brk, TRUE, brkAnmTbl[param_1].loopMode, brkAnmTbl[param_1].speed, 0, -1, param_2, 0)) {
        unk30E = param_1;
        if (brkAnmTbl[param_1].unk_4 < 0) {
            mBrk.setFrame(mBrk.getEndFrame());
        }

        unk308 = mBrk.getFrame();

        ret = true;
    }

    return ret;
}

/* 00000D58-00000D98       .text playBrkAnm__Q210daPedestal7daPds_cFv */
void daPedestal::daPds_c::playBrkAnm() {
    unk30F = mBrk.play();
    unk308 = mBrk.getFrame();
}

/* 00000D98-00000E48       .text _execute__Q210daPedestal7daPds_cFv */
BOOL daPedestal::daPds_c::_execute() {
    playBrkAnm();

    if (!eventProc()) {
        action(NULL);
    }

    set_mtx();
    mpBgW->Move();

    if (mInfiniteEcallBack.getEmitter() != NULL) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_DAI_LIGHT, 0);
    }

    return TRUE;
}

/* 00000E48-00000F10       .text _draw__Q210daPedestal7daPds_cFv */
BOOL daPedestal::daPds_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    dComIfGd_setListBG();

    J3DModelData* modelData = mpModel->getModelData();

    mBrk.entry(modelData);
    mDoExt_modelUpdateDL(mpModel);
    modelData->getMaterialTable().removeTevRegAnimator(mBrk.getBrkAnm());

    dComIfGd_setList();

    return TRUE;
}

namespace daPedestal {

/* 00000F10-00000F30       .text daPedestal::daPds_create__10daPedestalFPv */
static s32 daPds_Create(void* i_this) {
    return static_cast<daPds_c*>(i_this)->_create();
}

/* 00000F30-00000F54       .text daPds_Delete__10daPedestalFPv */
static BOOL daPds_Delete(void* i_this) {
    return (u8) static_cast<daPds_c*>(i_this)->_delete();
}

/* 00000F54-00000F78       .text daPds_Draw__10daPedestalFPv */
static BOOL daPds_Draw(void* i_this) {
    return (u8) static_cast<daPds_c*>(i_this)->_draw();
}

/* 00000F78-00000F9C       .text daPds_Execute__10daPedestalFPv */
static BOOL daPds_Execute(void* i_this) {
    return (u8) static_cast<daPds_c*>(i_this)->_execute();
}

/* 00000F9C-00000FA4       .text daPds_IsDelete__10daPedestalFPv */
static BOOL daPds_IsDelete(void*) {
    return TRUE;
}

/* 00000FA4-00001008       .text execute__Q210daPedestal25daPds_infiniteEcallBack_cFP14JPABaseEmitter */
void daPds_infiniteEcallBack_c::execute(JPABaseEmitter* emitter) {
    if (mpPos != NULL) {
        emitter->setGlobalTranslation(mpPos->x, mpPos->y, mpPos->z);
    }

    if (mpAngle != NULL) {
        JGeometry::TVec3<s16> rot;

        rot.x = mpAngle->x;
        rot.y = mpAngle->y;
        rot.z = mpAngle->z;

        emitter->setGlobalRotation(rot);
    }
}

/* 00001008-00001044       .text end__Q210daPedestal25daPds_infiniteEcallBack_cFv */
void daPds_infiniteEcallBack_c::end() {
    if (mpEmitter != NULL) {
        mpEmitter->becomeInvalidEmitter();
        mpEmitter->setEmitterCallBackPtr(NULL);

        mpEmitter = NULL;
        mpPos = NULL;
        mpAngle = NULL;
    }
}

/* 00001044-000010D4       .text makeEmitter__Q210daPedestal25daPds_infiniteEcallBack_cFUsPC4cXyzPC5csXyzPC4cXyz */
void daPds_infiniteEcallBack_c::makeEmitter(unsigned short particleID, const cXyz* pos, const csXyz* angle, const cXyz* scale) {
    end();
    dComIfGp_particle_set(particleID, pos, angle, scale, 0xFF, this);

    mpPos = pos;
    mpAngle = angle;
}

/* 00001288-0000128C       .text setup__Q210daPedestal25daPds_infiniteEcallBack_cFP14JPABaseEmitterPC4cXyzPC5csXyzSc */
void daPds_infiniteEcallBack_c::setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, signed char) {
    mpEmitter = emitter;
}

static actor_method_class daActMethodTable = {
    (process_method_func)daPds_Create,
    (process_method_func)daPds_Delete,
    (process_method_func)daPds_Execute,
    (process_method_func)daPds_IsDelete,
    (process_method_func)daPds_Draw,
};

}; // namespace daPedestal

actor_process_profile_definition g_profile_PEDESTAL = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_PEDESTAL,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daPedestal::daPds_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0091,
    /* Actor SubMtd */ &daPedestal::daActMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
