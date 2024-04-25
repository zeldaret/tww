//
// Generated by dtk
// Translation Unit: d_a_toge.cpp
//

#include "d/actor/d_a_toge.h"
#include "d/actor/d_a_wind_tag.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_ext.h"

const char daToge_c::m_arcname[] = "Htoge1";
const s16 daToge_c::m_bdlidx = 0x07;
const s16 daToge_c::m_dzbidx = 0x04;
const u32 daToge_c::m_heapsize = 0x5000;
const f32 daToge_c::m_y_min = -150.0f;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0x1,
        /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_PLAYER,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK8 | CO_SPRM_VS_UNK2 | CO_SPRM_VS_UNK4 |
            CO_SPRM_VS_UNK8,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_HIT_MARK,
        /* SrcGObjCo SPrm    */ 0,
    },

    // cCcD_SrcCylAttr
    {
        /* Center */ 0.0f,
        0.0f,
        0.0f,
        /* Radius */ 55.0f,
        /* Height */ 150.0f,
    }};

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
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x4);
    JUT_ASSERT(0x11A, modelData != 0);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000U, 0x11000002U);

    if (!mpModel) {
        return FALSE;
    }

    mpModel->setUserArea((u32)this);

    mpBgW1 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(m_arcname, 7), cBgW::MOVE_BG_e, &mtx1);
    mpBgW2 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(m_arcname, 8), cBgW::MOVE_BG_e, &mtx2);

    if (mpBgW1 == NULL || mpBgW2 == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00000290-00000348       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int timing) {
    if (timing == 0) {
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
    cullMtx = mpModel->mBaseTransformMtx;
    f32 scaleZ = scale.z;
    f32 scaleX = scale.x;
    fopAcM_setCullSizeBox(this, -80.0f, 0.0f, -80.0f, 80.0f, 120.0f, 80.0f);
    mStts.Init(0xFF, 0xFF, this);

    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    mSwitchNo = daToge_prm::getSwitchNo(this);

    if (dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this))) {
        this->unk470 = m_y_min;
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
BOOL daToge_c::_create() {
    fopAcM_SetupActor(this, daToge_c);

    s32 ret = dComIfG_resLoad(&m_Phs, m_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1400)) {
            return cPhs_ERROR_e;
        }

        Create();
    }

    return ret;
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
                this->unk485 = 1;
            }
        } else if (fopAcM_isSwitch(this, mSwitchNo) == 0 && mEventState != 4) {
            mEventState = 3;
        }
    } else if (mSwitchNo == 0xFF) {  // Redundant condition (necessary for matching)
        search_wind();

        daWindTag::daWindTag_c* pActor = (daWindTag::daWindTag_c*)fopAcM_SearchByID(mWindTagId);

        if (pActor != NULL) {
            if (pActor->unk498 > 0.0f) {
                if (mEventState != 4) {
                    mEventState = 3;
                }
            } else if (mEventState != 1) {
                this->unk485 = 1;
            }
        }
    }

    toge_move();

    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), mtx1);

    mpBgW2->Move();

    set_collision();

    return TRUE;
}

/* 000009F4-00000A78       .text set_collision__8daToge_cFv */
void daToge_c::set_collision() {
    if (mEventState != 2) {
        cXyz center;
        center.x = current.pos.x;
        center.y = current.pos.y;
        center.z = current.pos.z;

        center.y += (this->unk470 - 10.0f);

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
    u8 r30 = 1;
    switch (mEventState)  // Irregular switch
    {
    case 1:
        if (cLib_calcTimer(&this->unk486) != 0)
            break;
        toge_seStart(JA_SE_OBJ_TOGETOGE_IN);
        mEventState = 2;
        // Fallthrough
    case 2:
        // m_y_min is also -150.0f, so that might be related
        cLib_addCalc(&this->unk470, -150.0f, 0.1f, 30.0f, 15);
        break;
    case 0:
        // ...
        break;
    case 3:
        toge_seStart(JA_SE_OBJ_TOGETOGE_OUT);
        mEventState = 4;
        r30 = 0;
    case 4:
        if (cLib_addCalc(&this->unk470, this->unk474, 0.1f, 30.0f, 15.0f) == 0) {
            if (this->unk470 < 0) {
                this->unk474 = 0;
            } else if (this->unk485 != 0) {
                this->unk486 = 0xA;
                mEventState = 1;
                this->unk485 = 0;
            } else {
                if (r30 != 0) {
                    toge_seStart(JA_SE_OBJ_TOGETOGE_MOVE);
                }
                this->unk474 = -60.0f;
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
static BOOL daToge_Create(void* i_this) {
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
    (process_method_func)daToge_Create,  (process_method_func)daToge_Delete,
    (process_method_func)daToge_Execute, (process_method_func)daToge_IsDelete,
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
    /* Priority     */ 0x018C,
    /* Actor SubMtd */ &daTogeMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
