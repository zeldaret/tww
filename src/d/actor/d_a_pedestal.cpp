//
// Generated by dtk
// Translation Unit: d_a_pedestal.cpp
//

#include "d/actor/d_a_pedestal.h"
#include "d/d_procname.h"
#include "d/res/res_hdai1.h"

static char* l_os_name[] = {
    "Os",
    "Os1",
    "Os2"
};

namespace daPedestal {

const char daPds_c::m_arcname[] = "Hdai1";

/* 00000078-000000DC       .text _delete__Q210daPedestal7daPds_cFv */
BOOL daPds_c::_delete() {
    if (heap != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }

    mInfiniteEcallBack.end();
    dComIfG_resDelete(&mPhs, m_arcname);

    return TRUE;
}

/* 000000DC-000000FC       .text CheckCreateHeap__10daPedestalFP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daPds_c*>(i_this)->CreateHeap();
}

/* 000000FC-00000244       .text CreateHeap__Q210daPedestal7daPds_cFv */
BOOL daPds_c::CreateHeap() {
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

/* 00000244-00000380       .text CreateInit__Q210daPedestal7daPds_cFv */
void daPds_c::CreateInit() {
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
s32 daPds_c::_create() {
    fopAcM_SetupActor(this, daPds_c);

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
int daPds_c::getMyStaffId() {
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
BOOL daPds_c::wakeupCheck() {
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
BOOL daPds_c::finishCheck() {
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
void daPds_c::setAction(int (daPds_c::*)(void*), void*) {
    /* Nonmatching */
}

/* 0000073C-000007C4       .text action__Q210daPedestal7daPds_cFPv */
void daPds_c::action(void*) {
    /* Nonmatching */
}

/* 000007C4-000007E0       .text waitAction__Q210daPedestal7daPds_cFPv */
void daPds_c::waitAction(void*) {
    /* Nonmatching */
}

/* 000007E0-000008E4       .text eventProc__Q210daPedestal7daPds_cFv */
void daPds_c::eventProc() {
    /* Nonmatching */
}

/* 000008E4-000008E8       .text initialDefault__Q210daPedestal7daPds_cFi */
void daPds_c::initialDefault(int) {
    /* Nonmatching */
}

/* 000008E8-000008F0       .text actionDefault__Q210daPedestal7daPds_cFi */
void daPds_c::actionDefault(int) {
    /* Nonmatching */
}

/* 000008F0-000009A8       .text initialMoveEvent__Q210daPedestal7daPds_cFi */
void daPds_c::initialMoveEvent(int) {
    /* Nonmatching */
}

/* 000009A8-00000AEC       .text actionMoveEvent__Q210daPedestal7daPds_cFi */
void daPds_c::actionMoveEvent(int) {
    /* Nonmatching */
}

/* 00000AEC-00000B40       .text initialEffectSet__Q210daPedestal7daPds_cFi */
void daPds_c::initialEffectSet(int) {
    /* Nonmatching */
}

/* 00000B40-00000B80       .text initialEffectEnd__Q210daPedestal7daPds_cFi */
void daPds_c::initialEffectEnd(int) {
    /* Nonmatching */
}

/* 00000B80-00000C10       .text set_mtx__Q210daPedestal7daPds_cFv */
void daPds_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000C10-00000D58       .text initBrkAnm__Q210daPedestal7daPds_cFUcb */
BOOL daPds_c::initBrkAnm(u8 param_1, bool param_2) {
    /* Nonmatching */
}

/* 00000D58-00000D98       .text playBrkAnm__Q210daPedestal7daPds_cFv */
void daPds_c::playBrkAnm() {
    /* Nonmatching */
}

/* 00000D98-00000E48       .text _execute__Q210daPedestal7daPds_cFv */
BOOL daPds_c::_execute() {
    /* Nonmatching */
}

/* 00000E48-00000F10       .text _draw__Q210daPedestal7daPds_cFv */
BOOL daPds_c::_draw() {
    /* Nonmatching */
}

/* 00000F10-00000F30       .text daPds_Create__10daPedestalFPv */
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
