/**
 * d_a_toge.cpp
 * Object - Wind Temple - Floor spikes
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_toge.h"
#include "d/res/res_htoge1.h"
#include "d/actor/d_a_wind_tag.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "m_Do/m_Do_ext.h"

const char daToge_c::m_arcname[] = "Htoge1";
const s16 daToge_c::m_dzbidx = HTOGE1_DZB_HTOGE1A;
const s16 daToge_c::m_bdlidx = HTOGE1_BDL_HTOGE1;
const u32 daToge_c::m_heapsize = 0x5000;
const f32 daToge_c::m_y_min = -150.0f;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0x1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 55.0f,
        /* Height */ 150.0f,
    }},
};

/* 00000078-0000013C       .text _delete__8daToge_cFv */
BOOL daToge_c::_delete() {
    dComIfG_resDelete(&m_Phs, m_arcname);

    if (mpBgW1 != NULL && mpBgW1->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW1);
    }

    if (mpBgW2 != NULL && mpBgW2->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW2);
    }

    return TRUE;
}

/* 0000013C-0000015C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daToge_c*>(i_this)->CreateHeap();
}

/* 0000015C-00000290       .text CreateHeap__8daToge_cFv */
BOOL daToge_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, HTOGE1_BDL_HTOGE1);
    JUT_ASSERT(0x11A, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000U, 0x11000002U);

    if (!mpModel) {
        return FALSE;
    }

    mpModel->setUserArea((u32)this);

    mpBgW1 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(m_arcname, HTOGE1_DZB_HTOGE1A), cBgW::MOVE_BG_e, &mtx1);
    mpBgW2 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(m_arcname, HTOGE1_DZB_HTOGE1B), cBgW::MOVE_BG_e, &mtx2);

    if (mpBgW1 == NULL || mpBgW2 == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00000290-00000348       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        u32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daToge_c* i_this = (daToge_c*)model->getUserArea();
        if (i_this != NULL) {
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::transM(0.0f, i_this->unk470, 0.0f);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());

            mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
            mDoMtx_copy(mDoMtx_stack_c::get(), i_this->mtx2);
        }
    }

    return TRUE;
}

/* 00000348-000004F4       .text Create__8daToge_cFv */
BOOL daToge_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

    fopAcM_setCullSizeBox(this, -80.0f, 0.0f, -80.0f, 80.0f, 120.0f, 80.0f);
    mStts.Init(0xFF, 0xFF, this);

    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    mSwitchNo = daToge_prm::getSwitchNo(this);

    if (dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this))) {
        unk470 = m_y_min;
        mEventState = 2;
    }

    set_mtx();
    cMtx_copy(mtx1, mtx2);

    JUTNameTab* jointName = mpModel->getModelData()->getJointName();
    for (u16 i = 0; i < mpModel->getModelData()->getJointNum(); i++) {
        if (strcmp("toge", jointName->getName(i)) == 0) {
            mpModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            break;
        }
    }

    mpModel->calc();

    dComIfG_Bgsp()->Regist(mpBgW1, this);
    dComIfG_Bgsp()->Regist(mpBgW2, this);

    mpBgW1->Move();
    mpBgW2->Move();

    return TRUE;
}

/* 000004F4-00000620       .text _create__8daToge_cFv */
cPhs_State daToge_c::_create() {
    fopAcM_SetupActor(this, daToge_c);

    cPhs_State phase_state = dComIfG_resLoad(&m_Phs, m_arcname);

    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1400)) {
            return cPhs_ERROR_e;
        }

        Create();
    }

    return phase_state;
}

/* 000007D8-00000868       .text set_mtx__8daToge_cFv */
void daToge_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), mtx1);
}

/* 00000868-000009F4       .text _execute__8daToge_cFv */
BOOL daToge_c::_execute() {
    if (mSwitchNo != 0xFF) {
        if (fopAcM_isSwitch(this, mSwitchNo) != 0) {
            if (mEventState != 1) {
                unk485 = 1;
            }
        } else if (!fopAcM_isSwitch(this, mSwitchNo) && mEventState != 4) {
            mEventState = 3;
        }
    } else if (mSwitchNo == 0xFF) {  // Redundant condition (necessary for matching)
        search_wind();

        daWindTag::daWindTag_c* pActor = (daWindTag::daWindTag_c*)fopAcM_SearchByID(mWindTagId);

        if (pActor != NULL) {
            if (pActor->mOffsY > 0.0f) {
                if (mEventState != 4) {
                    mEventState = 3;
                }
            } else if (mEventState != 1) {
                unk485 = 1;
            }
        }
    }

    toge_move();

    set_mtx();

    mpBgW2->Move();

    set_collision();

    return TRUE;
}

/* 000009F4-00000A78       .text set_collision__8daToge_cFv */
void daToge_c::set_collision() {
    if (mEventState != 2) {
        cXyz center = current.pos;

        center.y += (unk470 - 10.0f);

        mCyl.SetC(center);
        dComIfG_Ccsp()->Set(&mCyl);
    }
}

/* 00000A78-00000AE0       .text search_wind__8daToge_cFv */
void daToge_c::search_wind() {
    fopAc_ac_c* pActor = fopAcM_SearchByName(PROC_WindTag);

    if (pActor != NULL) {
        mWindTagId = fopAcM_GetID(pActor);
    } else {
        mWindTagId = fpcM_ERROR_PROCESS_ID_e;
    }
}

/* 00000AE0-00000C1C       .text toge_move__8daToge_cFv */
void daToge_c::toge_move() {
    bool r30 = true;
    switch (mEventState) {
    case 0:
        break;
    case 1:
        if (cLib_calcTimer(&unk486) != 0)
            break;
        toge_seStart(JA_SE_OBJ_TOGETOGE_IN);
        mEventState = 2;
        // Fallthrough
    case 2:
        // m_y_min is also -150.0f, so that might be related
        cLib_addCalc(&unk470, -150.0f, 0.1f, 30.0f, 15);
        break;
    case 3:
        toge_seStart(JA_SE_OBJ_TOGETOGE_OUT);
        mEventState = 4;
        r30 = false;
        // Fallthrough
    case 4:
        if (cLib_addCalc(&unk470, unk474, 0.1f, 30.0f, 15.0f) == 0) {
            if (unk470 < 0) {
                unk474 = 0;
            } else if (unk485 != 0) {
                unk486 = 0xA;
                mEventState = 1;
                unk485 = 0;
            } else {
                if (r30) {
                    toge_seStart(JA_SE_OBJ_TOGETOGE_MOVE);
                }
                unk474 = -60.0f;
            }
        }
        break;
    }
}

/* 00000C1C-00000CA4       .text toge_seStart__8daToge_cFUl */
void daToge_c::toge_seStart(u32 i_seNum) {
    if (daToge_prm::getSeEnabled(this)) {
        fopAcM_seStart(this, i_seNum, 0);
    }
}

/* 00000CA4-00000D44       .text _draw__8daToge_cFv */
BOOL daToge_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();

    return TRUE;
}

/* 00000D44-00000D64       .text daToge_Create__FPv */
static cPhs_State daToge_Create(void* i_this) {
    return static_cast<daToge_c*>(i_this)->_create();
}

/* 00000D64-00000D84       .text daToge_Delete__FPv */
static BOOL daToge_Delete(void* i_this) {
    return static_cast<daToge_c*>(i_this)->_delete();
}

/* 00000D84-00000DA4       .text daToge_Draw__FPv */
static BOOL daToge_Draw(void* i_this) {
    return static_cast<daToge_c*>(i_this)->_draw();
}

/* 00000DA4-00000DC4       .text daToge_Execute__FPv */
static BOOL daToge_Execute(void* i_this) {
    return static_cast<daToge_c*>(i_this)->_execute();
}

/* 00000DC4-00000DCC       .text daToge_IsDelete__FPv */
static BOOL daToge_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daTogeMethodTable = {
    (process_method_func)daToge_Create,
    (process_method_func)daToge_Delete,
    (process_method_func)daToge_Execute,
    (process_method_func)daToge_IsDelete,
    (process_method_func)daToge_Draw,
};

actor_process_profile_definition g_profile_TOGE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TOGE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daToge_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_TOGE,
    /* Actor SubMtd */ &daTogeMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
