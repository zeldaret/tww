/**
 * d_a_obj_rcloud.cpp
 * Object - Dragon Roost Island - Clouds near Valoo
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_rcloud.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/res/res_bvkumo.h"

namespace {
const char l_arcname[] = "BVkumo";
const char l_demo41_name[] = "demo41";
const char l_dummy_name[] = "demo41";
const char* l_demo_name[] = {l_demo41_name, l_dummy_name};
const f32 maxDemoFrame = 428.0f;
const f32 endCloudAnimProgress = -1.0f;
} // namespace

#if VERSION == VERSION_DEMO
class daObjRcloud_HIO_c : public JORReflexible {
public:
    daObjRcloud_HIO_c();
    virtual ~daObjRcloud_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ u8 m0C;
};

daObjRcloud_HIO_c::daObjRcloud_HIO_c() {
    mNo = -1;
    m08 = -0.008928572f;
    m0C = 0;
}

static daObjRcloud_HIO_c l_HIO;

#else
namespace L_HIO {
static const f32 m08 = -0.008928572f;
};
#endif

/* 00000078-000000E8       .text init_mtx__13daObjRcloud_cFv */
void daObjRcloud_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000000E8-0000010C       .text solidHeapCB__13daObjRcloud_cFP10fopAc_ac_c */
BOOL daObjRcloud_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<daObjRcloud_c*>(i_this)->create_heap();
}

/* 0000010C-00000238       .text create_heap__13daObjRcloud_cFv */
bool daObjRcloud_c::create_heap() {
    bool result = true;;
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcname, BVKUMO_BDL_BVKUMO));
    J3DAnmTextureSRTKey* pAnm = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(l_arcname, BVKUMO_BTK_BVKUMO));

    if (modelData == NULL || pAnm == FALSE) {
        JUT_ASSERT(DEMO_SELECT(216, 220), FALSE);
        result = false;
    } else {
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
        s32 btkRet = mBtkAnm.init(modelData, pAnm, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1.0f, FALSE, 0);

        if (mpModel == NULL || btkRet == 0) {
            result = false;
        }
    }

    return result;
}

/* 00000238-000003B4       .text _create__13daObjRcloud_cFv */
cPhs_State daObjRcloud_c::_create() {
#if VERSION == VERSION_DEMO
    cPhs_State phase = cPhs_ERROR_e;
    fopAcM_SetupActor(this, daObjRcloud_c);
#else
    fopAcM_SetupActor(this, daObjRcloud_c);
    cPhs_State phase = cPhs_ERROR_e;
#endif

    if (fopAcM_IsFirstCreating(this)) {
        mDemoNameIndex = param_get_arg();
    }

    switch (mDemoNameIndex) {
    case 0:
        if (dComIfGs_isEventBit(0x3908) == 0) {
            phase = dComIfG_resLoad(&mPhase, l_arcname);
            mResourceLoadedFlag = 1;
        }
        break;
    case 1:
        if (dComIfGs_isSymbol(0) == 0) {
            phase = dComIfG_resLoad(&mPhase, l_arcname);
            mResourceLoadedFlag = 1;
        }
        break;
    deafult:
        break;
    }

    if (phase == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x5a0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            init_mtx();
            setup_action(0);
        } else {
            phase = cPhs_ERROR_e;
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("竜の山の雲", &l_HIO);
    }
#endif

    return phase;
}

/* 00000458-00000494       .text _delete__13daObjRcloud_cFv */
bool daObjRcloud_c::_delete() {
    if (mResourceLoadedFlag == 1) {
        dComIfG_resDelete(&mPhase, l_arcname);
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
#endif

    return true;
}

/* 00000494-00000500       .text wait_act_proc__13daObjRcloud_cFv */
void daObjRcloud_c::wait_act_proc() {
    if (dComIfGp_event_getMode() != 0 && dComIfGp_evmng_startCheck(l_demo_name[mDemoNameIndex]) != 0) {
        setup_action(1);
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.m0C == 1) {
        setup_action(2);
    }
#endif
}

/* 00000500-00000568       .text clouds_lift_start_wait_act_proc__13daObjRcloud_cFv */
void daObjRcloud_c::clouds_lift_start_wait_act_proc() {
    dDemo_manager_c* demo = dComIfGp_demo_get();
    if (demo != NULL) {
        if ((u32)demo->getFrame() > maxDemoFrame) {
            setup_action(2);
        }
    }
}

/* 00000568-000005DC       .text clouds_lift_act_proc__13daObjRcloud_cFv */
void daObjRcloud_c::clouds_lift_act_proc() {
    mCloudAnimProgress += HIO(m08);
    if (mCloudAnimProgress < endCloudAnimProgress) {
        mCloudAnimProgress = -1.0f;
        dComIfGs_onEventBit(0x3908);
        fopAcM_delete(this);
    }
}

/* 000005DC-00000678       .text setup_action__13daObjRcloud_cFi */
void daObjRcloud_c::setup_action(int i_actionIndex) {
    static ProcFunc act_proc[] = {&daObjRcloud_c::wait_act_proc, &daObjRcloud_c::clouds_lift_start_wait_act_proc, &daObjRcloud_c::clouds_lift_act_proc};

    mCurrentActProc = act_proc[i_actionIndex];
    m2BC = i_actionIndex;
}

/* 00000678-000006BC       .text _execute__13daObjRcloud_cFv */
bool daObjRcloud_c::_execute() {
    mBtkAnm.play();
    (this->*mCurrentActProc)();
    return TRUE;
}

/* 000006BC-00000778       .text setTexMtx__13daObjRcloud_cFv */
void daObjRcloud_c::setTexMtx() {
    const J3DModelData* modelData = mpModel->getModelData();

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* material = modelData->getMaterialNodePointer(i);
        for (u32 texMtxID = 0; texMtxID < 8; texMtxID++) {
            J3DTexGenBlock* texGenBlock = material->getTexGenBlock();
            J3DTexMtx* pTexMtx = texGenBlock->getTexMtx(texMtxID);

            if (pTexMtx != NULL) {
                pTexMtx->getMtx()[0][3] += pTexMtx->getTextureSRT().mTranslationX;
                if (m2BC == 2) {
                    pTexMtx->getMtx()[1][3] += mCloudAnimProgress;
                }
            }
        }
    }
}

/* 00000778-00000848       .text _draw__13daObjRcloud_cFv */
bool daObjRcloud_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    J3DModelData* modelData = mpModel->getModelData();
    mBtkAnm.entry(modelData, mBtkAnm.getFrame());
    mpModel->calc();
    mpModel->calcMaterial();
    setTexMtx();
    mpModel->diff();
    mpModel->entry();
    mpModel->viewCalc();
    return TRUE;
}

/* 00000848-00000868       .text daObjRcloud_Create__FP10fopAc_ac_c */
static cPhs_State daObjRcloud_Create(fopAc_ac_c* i_this) {
    return static_cast<daObjRcloud_c*>(i_this)->_create();
}

/* 00000868-0000088C       .text daObjRcloud_Delete__FP13daObjRcloud_c */
static BOOL daObjRcloud_Delete(daObjRcloud_c* i_this) {
    return i_this->_delete();
}

/* 0000088C-000008B0       .text daObjRcloud_Execute__FP13daObjRcloud_c */
static BOOL daObjRcloud_Execute(daObjRcloud_c* i_this) {
    return i_this->_execute();
}

/* 000008B0-000008D4       .text daObjRcloud_Draw__FP13daObjRcloud_c */
static BOOL daObjRcloud_Draw(daObjRcloud_c* i_this) {
    return i_this->_draw();
}

/* 000008D4-000008DC       .text daObjRcloud_IsDelete__FP13daObjRcloud_c */
static BOOL daObjRcloud_IsDelete(daObjRcloud_c*) {
    return TRUE;
}

static actor_method_class l_daObjRcloud_Method = {
    (process_method_func)daObjRcloud_Create,
    (process_method_func)daObjRcloud_Delete,
    (process_method_func)daObjRcloud_Execute,
    (process_method_func)daObjRcloud_IsDelete,
    (process_method_func)daObjRcloud_Draw,
};

actor_process_profile_definition g_profile_Obj_Rcloud = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Rcloud,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjRcloud_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Rcloud,
    /* Actor SubMtd */ &l_daObjRcloud_Method,
#if VERSION == VERSION_DEMO
    /* Status       */ fopAcStts_UNK40000_e,
#else
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
#endif
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
