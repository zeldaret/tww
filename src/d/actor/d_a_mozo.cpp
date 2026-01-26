/**
 * d_a_mozo.cpp
 * Enemy - Moblin Statue / モ石像 (Mo Sekizou)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mozo.h"
#include "d/res/res_mozo.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_lib.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_cc_d.h"

static dCcD_SrcCps cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_FIRE,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK8,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 50.0f,
    }},
};


static daMozo_HIO_c l_HIO;

/* 000000EC-000001D0       .text __ct__12daMozo_HIO_cFv */
daMozo_HIO_c::daMozo_HIO_c() {
    /* Nonmatching */
    m3C = 0.0f;
    m40 = -300.0f;
    m44 = 600.0f;
    mNo = -1;
    m08 = -1;
    mpBeamChild = &mBeamChild;
    mpFireChild = &mFireChild;
    mpBeamChild->m04 = 1000.0f;
    mpBeamChild->m08 = 1200.0f;
    mpBeamChild->m0C = 0x2000;
    mpBeamChild->m0E = 0x2800;
    mpBeamChild->m10 = 0;
    mpFireChild->m04 = 1000.0f;
    mpFireChild->m08 = 1200.0f;
    mpFireChild->m0C = 0x2000;
    mpFireChild->m0E = 0x2800;
    mpFireChild->m10 = 0;
}

/* 000002D0-00000568       .text daMozo_nodeCallBackBeam__FP8daMozo_cP8J3DModelP7J3DNodei */
static BOOL daMozo_nodeCallBackBeam(daMozo_c*, J3DModel*, J3DNode*, int) {
    /* Nonmatching */
}

/* 00000568-00000728       .text daMozo_nodeCallBackFire__FP8daMozo_cP8J3DModelP7J3DNodei */
static BOOL daMozo_nodeCallBackFire(daMozo_c*, J3DModel*, J3DNode*, int) {
    /* Nonmatching */
}

/* 00000728-0000078C       .text daMozo_nodeCallBack__FP7J3DNodei */
static BOOL daMozo_nodeCallBack(J3DNode* node, int calcTiming) {
    /* Nonmatching */
    J3DJoint* joint = (J3DJoint*)node;
    s32 jntNo = joint->getJntNo();
    J3DModel* model = j3dSys.getModel();
    daMozo_c* i_this = (daMozo_c*)model->getUserArea();

    switch (i_this->field_0x376) {
    case 0: return daMozo_nodeCallBackBeam(i_this, model, node, calcTiming);
    case 1: return daMozo_nodeCallBackFire(i_this, model, node, calcTiming);
    }

    return TRUE;
}

/* 0000078C-000007AC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daMozo_c*>(i_this)->CreateHeap();
}

/* 000007AC-00000A24       .text CreateHeap__8daMozo_cFv */
BOOL daMozo_c::CreateHeap() {
    J3DModelData* mdlData = (J3DModelData*)dComIfG_getObjectRes("Mozo", MOZO_INDEX_BDL_MOZ);
    
    mDoExt_McaMorf* newMorf =  new mDoExt_McaMorf(
        mdlData,
        0,
        0,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("Mozo", MOZO_INDEX_BCK_MOZ)),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        0,
        0,
        0,
        0x11020203
    );
    
    mAnimMorf = newMorf;

    m_brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Mozo", MOZO_INDEX_BRK_MOZ);
    JUT_ASSERT(0x16A, m_brk != NULL);

    m_btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Mozo", MOZO_INDEX_BTK_MOZ);
    JUT_ASSERT(0x16D, m_btk != NULL);

    int brkInitResult = mBrkAnm.init(mdlData, m_brk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    int btkInitResult = mBtkAnm.init(mdlData, m_btk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);

    return mdlData != 0 && mAnimMorf != 0 && mAnimMorf->getModel() != 0 && brkInitResult != 0 && btkInitResult != 0;
}

/* 00000A24-00000AAC       .text set_mtx__8daMozo_cFv */
void daMozo_c::set_mtx() {
    J3DModel* mdl = mAnimMorf->getModel();
    mdl->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
        
    mdl->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000AAC-00000C38       .text anime_proc__8daMozo_cFv */
void daMozo_c::anime_proc() {
    /* Nonmatching */
}

/* 00000C38-00000C90       .text wait_proc_init__8daMozo_cFv */
void daMozo_c::wait_proc_init() {
    /* Nonmatching */
}

/* 00000C90-00000D58       .text wait_proc__8daMozo_cFv */
void daMozo_c::wait_proc() {
    /* Nonmatching */
}

/* 00000D58-00000DE0       .text search_beam_proc_init__8daMozo_cFv */
void daMozo_c::search_beam_proc_init() {
    /* Nonmatching */
}

/* 00000DE0-00001230       .text search_beam_proc__8daMozo_cFv */
void daMozo_c::search_beam_proc() {
    /* Nonmatching */
}

/* 00001230-000012C0       .text search_fire_proc_init__8daMozo_cFv */
void daMozo_c::search_fire_proc_init() {
    /* Nonmatching */
}

/* 000012C0-000017F4       .text search_fire_proc__8daMozo_cFv */
void daMozo_c::search_fire_proc() {
    /* Nonmatching */
}

/* 000017F4-00001874       .text towait_proc_init__8daMozo_cFv */
void daMozo_c::towait_proc_init() {
    /* Nonmatching */
}

/* 00001874-00001B3C       .text towait_proc__8daMozo_cFv */
void daMozo_c::towait_proc() {
    /* Nonmatching */
}

/* 00001B3C-00001D8C       .text checkRange__8daMozo_cFi */
void daMozo_c::checkRange(int) {
    /* Nonmatching */
}

/* 00001D8C-00001F70       .text setAnm__8daMozo_cFif */
void daMozo_c::setAnm(int, float) {
    /* Nonmatching */
}

/* 00001F70-00002228       .text CreateInit__8daMozo_cFv */
cPhs_State daMozo_c::CreateInit() {
    /* Nonmatching */
    J3DModelData* mdlData = mAnimMorf->getModel()->getModelData();

    u8 temp = fopAcM_GetParam(this) & 0xFF;
    if (temp == 0xFF) {
        temp = 0;
    }
    field_0x376 = cLib_minMaxLimit<u8>(temp, 0, 2);

    mAnimMorf->getModel()->setUserArea((u32)this);
    for (u16 i = 0; i < mdlData->getJointNum(); i++) {
        if (i == 2) {
            mdlData->getJointNodePointer(i)->setCallBack(daMozo_nodeCallBack);
        }
    }

    mQuatRotation = ZeroQuat;

    fopAcM_setCullSizeBox(this, -1000.0f, -1000.0f, -1000.0f, 1000.0f, 1000.0f, 1000.0f);
    fopAcM_SetMtx(this, mAnimMorf->getModel()->getBaseTRMtx());

    // TODO: Insert missing code here

    set_mtx();
    mAnimMorf->calc();
    wait_proc_init();

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("モ石像", &l_HIO); // "Mo Statue" (mo sekizou)
    }

    return cPhs_COMPLEATE_e;
}

/* 00002228-000023B0       .text _create__8daMozo_cFv */
cPhs_State daMozo_c::_create() {
    fopAcM_SetupActor(this, daMozo_c);

    cPhs_State result = dComIfG_resLoad(&mPhs, "Mozo");

    if (result == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1AA0)) {
            result = CreateInit();
            _execute();
        } else {
            return cPhs_ERROR_e;
        }
    }

    return result;
}

/* 000023B0-0000242C       .text _delete__8daMozo_cFv */
bool daMozo_c::_delete() {
    /* Nonmatching */
}

/* 0000242C-00002498       .text getBeamActor__8daMozo_cFUi */
fopAc_ac_c* daMozo_c::getBeamActor(fpc_ProcID apid) {
    fopAc_ac_c* ac = fopAcM_SearchByID(apid);
    if (ac == NULL)
        return NULL;
    if (fopAc_IsActor(ac) && fopAcM_GetProfName(ac) == PROC_Beam)
        return ac;
    return NULL;
}

/* 00002498-00002588       .text event_move__8daMozo_cFv */
void daMozo_c::event_move() {
    /* Nonmatching */
}

/* 00002588-000025DC       .text _execute__8daMozo_cFv */
bool daMozo_c::_execute() {
    mAnimMorf->calc();

    (this->*mCurrentProc)();
    event_move();
    set_mtx();

    return true;
}

/* 000025DC-0000267C       .text _draw__8daMozo_cFv */
bool daMozo_c::_draw() {
    /* Nonmatching */
    J3DModelData* mdlData = mAnimMorf->getModel()->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mAnimMorf->getModel(), &tevStr);

    mBrkAnm.entry(mdlData);
    mBtkAnm.entry(mdlData);
    mAnimMorf->entryDL();

    return true;
}

/* 0000267C-000026A0       .text daMozo_Draw__FP8daMozo_c */
static BOOL daMozo_Draw(daMozo_c* i_this) {
    return i_this->_draw();
}

/* 000026A0-000026C4       .text daMozo_Execute__FP8daMozo_c */
static BOOL daMozo_Execute(daMozo_c* i_this) {
    return i_this->_execute();
}

/* 000026C4-000026CC       .text daMozo_IsDelete__FP8daMozo_c */
static BOOL daMozo_IsDelete(daMozo_c*) {
    return TRUE;
}

/* 000026CC-000026F0       .text daMozo_Delete__FP8daMozo_c */
static BOOL daMozo_Delete(daMozo_c* i_this) {
    return i_this->_delete();
}

/* 000026F0-00002710       .text daMozo_Create__FP10fopAc_ac_c */
static cPhs_State daMozo_Create(fopAc_ac_c* i_this) {
    return static_cast<daMozo_c*>(i_this)->_create();
}

static actor_method_class l_daMozo_Method = {
    (process_method_func)daMozo_Create,
    (process_method_func)daMozo_Delete,
    (process_method_func)daMozo_Execute,
    (process_method_func)daMozo_IsDelete,
    (process_method_func)daMozo_Draw,
};

actor_process_profile_definition g_profile_MOZO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MOZO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daMozo_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MOZO,
    /* Actor SubMtd */ &l_daMozo_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
