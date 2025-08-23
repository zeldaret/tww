/**
 * d_a_branch.cpp
 * Object - Forest of Fairies - Tree branch (Tetra)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_branch.h"
#include "d/res/res_kwood_00.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_kankyo.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"

static u16 anim_table[] = {
    KWOOD_00_BCK_SWING02, KWOOD_00_BAS_SWING02,
    KWOOD_00_BCK_SWING,   KWOOD_00_BAS_SWING,
    KWOOD_00_BCK_BREAK,   KWOOD_00_BAS_BREAK,
};

char daBranch_c::m_arcname[] = "Kwood_00";

/* 00000078-00000128       .text set_mtx__10daBranch_cFv */
void daBranch_c::set_mtx() {
    J3DModel* pMdl;

    for (int i = 0; i < (s32)ARRAY_SIZE(mModel); i ++) {
        pMdl = mModel[i];

        if (pMdl) {
            pMdl->setBaseScale(scale);

            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::XYZrotM(current.angle);
            
            pMdl->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
}

/* 00000128-000001E4       .text set_anim__10daBranch_cFiii */
void daBranch_c::set_anim(int i_animIdx, int i_bckIdx, int i_basIdx) {
    if (i_bckIdx > 0 && i_basIdx > 0) {
        mAnims[i_animIdx]->setAnm(
            static_cast<J3DAnmTransform*>(dComIfG_getObjectIDRes(m_arcname, i_bckIdx)),
            -1, 0.0f, 1.0f, 0.0f, -1.0f,
            dComIfG_getObjectIDRes(m_arcname, i_basIdx)
        );
    }
}

/* 000001E4-00000228       .text demoPlay__10daBranch_cFP14mDoExt_McaMorf */
void daBranch_c::demoPlay(mDoExt_McaMorf* morf) {
    dDemo_setDemoData(
        this,
        dDemo_actor_c::ENABLE_ANM_e,
        morf, m_arcname,
        ARRAY_SIZE(anim_table) / 2, anim_table
    );
}

/* 00000228-00000248       .text solidHeapCB__10daBranch_cFP10fopAc_ac_c */
BOOL daBranch_c::solidHeapCB(fopAc_ac_c* i_this) {
    daBranch_c* branch = static_cast<daBranch_c*>(i_this);
    return branch->CreateHeap();
}

/* 00000248-0000049C       .text CreateHeap__10daBranch_cFv */
BOOL daBranch_c::CreateHeap() {
    int bmd[] = { KWOOD_00_BMD_WS, KWOOD_00_BMD_WB };
    int bck[] = { KWOOD_00_BCK_SWING02, KWOOD_00_BCK_BREAK };
    int bas[] = { KWOOD_00_BAS_SWING02, KWOOD_00_BAS_BREAK };

    BOOL status = TRUE;

    for (int i = 0; i < (s32)ARRAY_SIZE(mAnims); i++) {
#if VERSION > VERSION_DEMO
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectIDRes(m_arcname, bmd[i]));
        J3DAnmTransformKey* bckData = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectIDRes(m_arcname, bck[i]));

        JUT_ASSERT(0x1CC, modelData != NULL);
        // Bug: They probably meant to assert that bckData isn't null, but accidentally used the array of bck file IDs.
        JUT_ASSERT(0x1CD, bck != NULL);
#endif

        mAnims[i] = new mDoExt_McaMorf(
            static_cast<J3DModelData*>(dComIfG_getObjectIDRes(m_arcname, bmd[i])),
            NULL, NULL,
            static_cast<J3DAnmTransformKey*>(dComIfG_getObjectIDRes(m_arcname, bck[i])),
            -1, 1.0f, 0, -1, 1, NULL,
            0, 0x11020203
        );

#if VERSION == VERSION_DEMO
        set_anim(i, bck[i], bas[i]);
        mAnims[i]->setFrame(0.0f);
#endif

#if VERSION > VERSION_DEMO
        if (!mAnims[i]) {
            status = FALSE;
            break;
        }
#endif

        mModel[i] = mAnims[i]->getModel();
        if (!mModel[i]) {
            status = FALSE;
            break;
        }

#if VERSION > VERSION_DEMO
        mAnims[i]->setFrame(0.0f);
        set_anim(i, bck[i], bas[i]);
#endif
    }

    return status;
}

inline BOOL daBranch_c::draw() {
    int activeIdx = 0;
    if (m02B8 == 5) {
        activeIdx = 1;
    }

    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel[activeIdx], &tevStr);

    mAnims[activeIdx]->updateDL();

    return TRUE;
}

/* 0000049C-00000524       .text daBranch_Draw__FP10daBranch_c */
static BOOL daBranch_Draw(daBranch_c* i_this) {
    daBranch_c* branch = static_cast<daBranch_c*>(i_this);
    return branch->draw();
}

inline BOOL daBranch_c::execute() {
    u8 demoId = demoActorID;

    if (demoId == 0) {
        if (m02B8 == 5) {
            if (mAnims[1]) {
                mAnims[1]->play(0, 0, 0);
            }
        }
        else if (m02B8 == 6 && mAnims[0]) {
            mAnims[0]->play(0, 0, 0);
        }
    }
    else {
        dDemo_actor_c* demoActor = dComIfGp_demo_getActor(demoId);

        if (demoActor) {
            m02B8 = demoActor->getShapeId();

            if (m02B8 == 6) {
                demoPlay(mAnims[0]);
            }
            else if (m02B8 == 5) {
                demoPlay(mAnims[1]);
            }
        }
    }

    set_mtx();

    return TRUE;
}

/* 00000524-0000060C       .text daBranch_Execute__FP10daBranch_c */
static BOOL daBranch_Execute(daBranch_c* i_this) {
    daBranch_c* branch = static_cast<daBranch_c*>(i_this);
    return branch->execute();
}

/* 0000060C-00000614       .text daBranch_IsDelete__FP10daBranch_c */
static BOOL daBranch_IsDelete(daBranch_c* i_this) {
    return TRUE;
}

/* 00000614-00000694       .text daBranch_Delete__FP10daBranch_c */
static BOOL daBranch_Delete(daBranch_c* i_this) {
    i_this->~daBranch_c();
    return TRUE;
}

inline cPhs_State daBranch_c::create() {
#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(this, daBranch_c);
#endif

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, daBranch_c::m_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
#if VERSION == VERSION_DEMO
        fopAcM_SetupActor(this, daBranch_c);
#endif

        if (!fopAcM_entrySolidHeap(this, daBranch_c::solidHeapCB, 0x4000)) {
            for (int i = 0; i < (s32)ARRAY_SIZE(mAnims); i++) {
                mAnims[i] = NULL;
            }

            phase_state = cPhs_ERROR_e;
        }
        else {
            fopAcM_SetMtx(this, mModel[0]->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, 0.0f, 0.0f, -50.0f, 300.0f, 100.0f, 50.0f);
            
            m02B8 = 6;
            m02BC = 0;
            m02BD = 0;

            set_mtx();

            for (int i = 0; i < (s32)ARRAY_SIZE(mModel); i++) {
                J3DModelData* modelData = mModel[i]->getModelData();

                for (u16 j = 0; j < modelData->getMaterialNum(); j++) {
                    J3DMaterial* mat = modelData->getMaterialNodePointer(j);
                    if (mat) {
                        mat->getFog()->setType(2);
                    }
                }
            }
        }
    }

    return phase_state;
}

/* 00000694-0000080C       .text daBranch_Create__FP10fopAc_ac_c */
static cPhs_State daBranch_Create(fopAc_ac_c* i_this) {
    daBranch_c* branch = static_cast<daBranch_c*>(i_this);
    return branch->create();
}

static actor_method_class l_daBranch_Method = {
    (process_method_func)daBranch_Create,
    (process_method_func)daBranch_Delete,
    (process_method_func)daBranch_Execute,
    (process_method_func)daBranch_IsDelete,
    (process_method_func)daBranch_Draw,
};

actor_process_profile_definition g_profile_BRANCH = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BRANCH,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBranch_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BRANCH,
    /* Actor SubMtd */ &l_daBranch_Method,
#if VERSION == VERSION_DEMO
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
#else
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
#endif
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
