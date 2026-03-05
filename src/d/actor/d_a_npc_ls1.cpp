/**
 * d_a_npc_ls1.cpp
 * NPC - Aryll
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ls1.h"
#include "d/actor/d_a_npc_bm1.h"
#include "d/actor/d_a_player_main.h"
#if VERSION > VERSION_DEMO
#include "d/d_bg_s_func.h"
#endif
#include "f_op/f_op_camera.h"
#include "d/res/res_link.h"
#include "d/res/res_ls.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_lib.h"

static daNpc_Ls1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000150       .text __ct__15daNpc_Ls1_HIO_cFv */
daNpc_Ls1_HIO_c::daNpc_Ls1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        0x2EE0,
        0x4650,
        0xFC18,
        0xB9B0,
        0x0BB8,
        0x1B58,
        0x0000,
        0xE4A8,
        0x1000,
        0x0960,
        110.0f,
        0,
        700.0f,
        200.0f,
        2.0f,
        9.0f,
        50.0f,
        0x1A2C,
        9.0f
    };
    memcpy(&mPrm, &a_prm_tbl, 0x38);
    m04 = -1;
    m08 = -1;
}

daNpc_Ls1_HIO_c::~daNpc_Ls1_HIO_c() {}

static const char* l_evn_tbl[] = {
    "zelda_fly",
    "omedeto",
    "get_telescope",
    "eTalk"
};

/* 00000198-000001F8       .text __ct__18daNpc_Ls1_matAnm_cFv */
daNpc_Ls1_matAnm_c::daNpc_Ls1_matAnm_c() {
    mbMove = 0;
    mOffset.y = 0.0f;
    mOffset.x = 0.0f;
}

/* 000001F8-0000028C       .text calc__18daNpc_Ls1_matAnm_cCFP11J3DMaterial */
void daNpc_Ls1_matAnm_c::calc(J3DMaterial* i_material) const {
    J3DMaterialAnm::calc(i_material);
    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i)) {
            J3DTexMtx* tex_mtx_p = i_material->getTexMtx(i);
            if (mbMove != 0) {
                tex_mtx_p->getTextureSRT().mTranslationX = mOffset.x;
                tex_mtx_p->getTextureSRT().mTranslationY = mOffset.y;
            }
        }
    }
}

/* 0000028C-000002D8       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* actor_p = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 000002D8-000003F8       .text _nodeCB_Head__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_Head(J3DNode* i_bode, J3DModel* i_model) {
    static cXyz a_eye_pos_off(14.0f, 18.0f, 0.0f); 
    
    J3DJoint* jnt_p = (J3DJoint *) i_bode;
    s32 jnt_no = jnt_p->getJntNo();
    
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    m7E4.x = mDoMtx_stack_c::get()[0][3];
    m7E4.y = mDoMtx_stack_c::get()[1][3];
    m7E4.z = mDoMtx_stack_c::get()[2][3];
    
    mDoMtx_stack_c::XrotM(mHalfHeadAngleY);
    mDoMtx_stack_c::ZrotM(-mHalfHeadAngleX);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    
    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000434-00000480       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* actor_p = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000480-00000520       .text _nodeCB_BackBone__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint *) i_node;
    s32 jnt_no = jnt_p->getJntNo();
    
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000520-0000056C       .text nodeCB_Hand_L__FP7J3DNodei */
static BOOL nodeCB_Hand_L(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* actor_p = (daNpc_Ls1_c *) j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Hand_L(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 0000056C-000005F4       .text _nodeCB_Hand_L__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_Hand_L(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint *) i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    mDoMtx_copy(mDoMtx_stack_c::get(), mHand_L_Mtx);
    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000005F4-00000640       .text nodeCB_Hand_R__FP7J3DNodei */
static BOOL nodeCB_Hand_R(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* actor_p = (daNpc_Ls1_c *) j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Hand_R(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000640-000006C8       .text _nodeCB_Hand_R__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_Hand_R(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint *) i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    mDoMtx_copy(mDoMtx_stack_c::get(), mHand_R_Mtx);
    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000006C8-00000714       .text Ls_hand_nodeCB_Hand_L__FP7J3DNodei */
static BOOL Ls_hand_nodeCB_Hand_L(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* actor_p = (daNpc_Ls1_c *) j3dSys.getModel()->getUserArea();
        actor_p->_Ls_hand_nodeCB_Hand_L(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000714-00000770       .text _Ls_hand_nodeCB_Hand_L__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_Ls_hand_nodeCB_Hand_L(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint *) i_node;
    int jnt_no = jnt_p->getJntNo();

    mDoMtx_copy(mHand_L_Mtx, j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mHand_L_Mtx);
}

/* 00000770-000007BC       .text Ls_hand_nodeCB_Hand_R__FP7J3DNodei */
static BOOL Ls_hand_nodeCB_Hand_R(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* a_actor = (daNpc_Ls1_c *) j3dSys.getModel()->getUserArea();
        a_actor->_Ls_hand_nodeCB_Hand_R(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 000007BC-00000818       .text _Ls_hand_nodeCB_Hand_R__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_Ls_hand_nodeCB_Hand_R(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint *) i_node;
    int jnt_no = jnt_p->getJntNo();

    mDoMtx_copy(mHand_R_Mtx, j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mHand_R_Mtx);
}

/* 00000818-00000838       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ls1_c*)i_this)->CreateHeap();
}

/* 00000838-000008B0       .text searchActor_Bm1__FPvPv */
void* searchActor_Bm1(void* i_actorP, void* i_unusedP) {
    UNUSED(i_unusedP);

    if (
        l_check_wrk < ARRAY_SSIZE(l_check_inf) && 
        fopAc_IsActor(i_actorP) && 
        fpcM_GetName(i_actorP) == PROC_NPC_BM1
    ) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actorP;
        l_check_wrk++;
    }

    return NULL;
}

/* 000008B0-00000900       .text searchActor_kamome_Set_NOSTOP_DEMO__FPvPv */
void* searchActor_kamome_Set_NOSTOP_DEMO(void* i_actorP, void* i_unusedP) {
    UNUSED(i_unusedP);

    if (fopAc_IsActor(i_actorP) && fpcM_GetName(i_actorP) == PROC_KAMOME) {
        fopAcM_OnStatus((fopAc_ac_c*)i_actorP, fopAcStts_UNK4000_e);
    }

    return NULL;
}

/* 00000900-00000950       .text searchActor_kamome_Clr_NOSTOP_DEMO__FPvPv */
void* searchActor_kamome_Clr_NOSTOP_DEMO(void* i_actorP, void* i_unused) {
    UNUSED(i_unused);

    if (fopAc_IsActor(i_actorP) && fpcM_GetName(i_actorP) == PROC_KAMOME) {
        fopAcM_OffStatus((fopAc_ac_c*) i_actorP, fopAcStts_UNK4000_e);
    }
    
    return NULL;
}

/* 00000950-000009B4       .text init_LS1_0__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::init_LS1_0() {
    set_action(&daNpc_Ls1_c::wait_action1, NULL);
    fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
    return true;
}

/* 000009B4-00000A00       .text init_LS1_1__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::init_LS1_1() {
    set_action(&daNpc_Ls1_c::demo_action1, NULL);
    return true;
}

/* 00000A00-00000A20       .text init_LS1_2__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::init_LS1_2() {
    return init_LS1_1();
}

/* 00000A20-00000A40       .text init_LS1_3__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::init_LS1_3() {
    return init_LS1_0();
}

/* 00000A40-00000A60       .text init_LS1_4__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::init_LS1_4() {
    return init_LS1_1();
}

extern dCcD_SrcCyl dNpc_cyl_src;
/* 00000A60-00000C6C       .text createInit__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::createInit() {
    for (int i = 0; i < ARRAY_SSIZE(mEventIDTbl); i++) {
        mEventIDTbl[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    mEventCut.setActorInfo2("Ls1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;    
    
    switch (mType) {
        case 3:
        case 4:
            break;
    }
    
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = 0.0f;
    mBckResIndex = 0xE;

    bool init_result;
    switch (mType) {
        case 0:
            init_result = init_LS1_0();
            break;
        case 1:
            init_result = init_LS1_1();
            break;
        case 2:
            init_result = init_LS1_2();
            break;
        case 3:
            init_result = init_LS1_3();
            break;
        case 4:
            init_result = init_LS1_4();
            break;
        default:
            init_result = 0;
            break;
    }

    if (!init_result) {
        return false;
    }

    mAngle = current.angle;
    shape_angle = mAngle;
    
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    
    play_animation();
    
    if (mType) {
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    tevStr.mRoomNo =dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);

    return true;
}

/* 00000C6C-00000D48       .text play_animation__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::play_animation() {
    u32 snd_id = 0;
    if (mBtkResIDIndex == 0 && m838 == true) {
        setEyeCtrl();
    } else {
        clrEyeCtrl();
    }

    play_btp_anm();
    play_btk_anm();

    if (mObjAcch.ChkGroundHit()) {
        snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    
    mbMorfAnimStopped = mpMorf->play(&eyePos, snd_id, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = true;
    }

    mPrevMorfFrame = mpMorf->getFrame();
}

/* 00000D48-00000EF0       .text setMtx__11daNpc_Ls1_cFb */
void daNpc_Ls1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    mpMorf->calc();
    mpLsHandModel->calc();

    if (mpTelescopeModel) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        if (m841) {
            mDoMtx_stack_c::transM(5.7f, -17.5f, -1.0f);
            mDoMtx_stack_c::scaleM(mTelescopeScale, mTelescopeScale, mTelescopeScale);
            mDoMtx_stack_c::XYZrotM(-0x1D27, 0x3B05, -0x5C71);
        } else {
            mDoMtx_stack_c::transM(5.5f, -3.0f, -2.0f);
            mDoMtx_stack_c::scaleM(mTelescopeScale, mTelescopeScale, mTelescopeScale);
            mDoMtx_stack_c::XYZrotM(-0x1D27, 0x3B05, -0x5C71);
        }
        mpTelescopeModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpTelescopeModel->calc();
    }
    setAttention(i_setEyePos);
}

/* 00000EF0-00000F04       .text bckResID__11daNpc_Ls1_cFi */
int daNpc_Ls1_c::bckResID(int i_bckResIDIndex) {
    static const int a_resID_tbl[] = {
        LS_BCK_LS_WAIT01,
        LS_BCK_LS_WAIT02,
        LS_BCK_LS_WAIT03,
        LS_BCK_LS_WAIT04,
        LS_BCK_LS_WAIT05,
        LS_BCK_LS_WAIT06,
        LS_BCK_LS_WATASU,
        LS_BCK_LS_FURIMUKI,
        LS_BCK_LS_NOZOKU,
        LS_BCK_LS_GET,
        LS_BCK_LS_WAIT07,
        LS_BCK_LS_TALK01,
        LS_BCK_LS_DEMOWAIT,
        LS_BCK_LS_DEMOLOOK
    };
    return a_resID_tbl[i_bckResIDIndex];
}

/* 00000F04-00000F18       .text btpResID__11daNpc_Ls1_cFi */
int daNpc_Ls1_c::btpResID(int i_btpResIDIndex) {  
    static const int a_resID_tbl[] = {
        LS_BTP_FUAN,
        LS_BTP_MABA,
        LS_BTP_FUAN02,
        LS_BTP_KIZUKU,
        LS_BTP_LS_GET,
        LS_BTP_NGWARAI,
        LS_BTP_NOZOKU,
        LS_BTP_OKORI,
        LS_BTP_WARAI,
        LS_BTP_LS_DEMOLOOK,
        LS_BTP_LS_DEMOWAIT
    };
    return a_resID_tbl[i_btpResIDIndex];
}

/* 00000F18-00000F2C       .text btkResID__11daNpc_Ls1_cFi */
int daNpc_Ls1_c::btkResID(int i_btkResIDIndex) {
    static const int a_resID_tbl[] = {
        LS_BTK_LS,
        LS_BTK_LS_DEMOLOOK,
        LS_BTK_LS_DEMOWAIT
    };
    return a_resID_tbl[i_btkResIDIndex];
}

/* 00000F2C-00001030       .text setBtp__11daNpc_Ls1_cFScb */
bool daNpc_Ls1_c::setBtp(s8 i_btpResIDIndex, bool i_bModify) {
    J3DModel* morf_model_p = mpMorf->getModel();

    if (i_btpResIDIndex < 0) {
        return false;
    }
    
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*) dComIfG_getObjectIDRes(mArcName, btpResID(i_btpResIDIndex));
    JUT_ASSERT(DEMO_SELECT(0x301, 0x302), a_btp != NULL);
    mBtpResIDIndex = i_btpResIDIndex;
    mBtpFrame = 0;
    mTimer1 = 0;

    return mBtpAnm.init(
        morf_model_p->getModelData(), 
        a_btp, TRUE, 
        0, 1.0f, 0, -1, 
        i_bModify, 0
    ) != 0;
}

/* 00001030-000010B0       .text setMat__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::setMat() {
    J3DModel* model_p = mpMorf->getModel();
    u16 material_num = mBtkAnm.getBtkAnm()->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        u16 material_id = mBtkAnm.getBtkAnm()->getUpdateMaterialID(i);
        mpMatAnms[i] = (daNpc_Ls1_matAnm_c *) model_p->getModelData()->getMaterialNodePointer(material_id)->getMaterialAnm();
    }
}

/* 000010B0-000011CC       .text setBtk__11daNpc_Ls1_cFScb */
bool daNpc_Ls1_c::setBtk(s8 i_btkResIDIndex, bool i_bModify) {
    J3DModel* morf_model_p = mpMorf->getModel();

    if (i_btkResIDIndex < 0) {
        return false;
    }
    
    J3DAnmTextureSRTKey* a_btk = (J3DAnmTextureSRTKey *) dComIfG_getObjectIDRes(mArcName, btkResID(i_btkResIDIndex));
    JUT_ASSERT(DEMO_SELECT(0x32B, 0x32C), a_btk != NULL);

    mBtkResIDIndex = i_btkResIDIndex;
    mBtkFrame = 0;

    if (mBtkAnm.init(
        morf_model_p->getModelData(), 
        a_btk, TRUE, 
        0, 1.0f, 0, -1, 
        i_bModify, 0
    ) != 0) {
        if (!i_bModify) {
            setMat();
        }
        return true;
    }

    return false;
}

/* 000011CC-00001238       .text init_texPttrnAnm__11daNpc_Ls1_cFScb */
bool daNpc_Ls1_c::init_texPttrnAnm(s8 i_resIndex, bool i_bModify) {
    static const u8 a_btk_num_tbl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2
    };

    if (setBtp(i_resIndex, i_bModify) == false) {
        return false;
    } 

    return setBtk(a_btk_num_tbl[i_resIndex], i_bModify);
}

/* 00001238-000012D4       .text play_btp_anm__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::play_btp_anm() {
    u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
    if (mBtpResIDIndex != 1 || cLib_calcTimer(&mTimer1) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= frame_max) {
            if (mBtpResIDIndex != 1) {
                mBtpFrame = frame_max;
            } else {
                mTimer1 = cLib_getRndValue(60, 90);
                mBtpFrame = 0;
            }
        }
    }
}

/* 000012D4-00001490       .text eye_ctrl__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::eye_ctrl() {
    f32 mult, fVar2, fVar1, min, max;
    if (mbEyeCtrlSet) {
        fVar1 = ((f32)m848 / (f32)l_HIO.mPrm.m30);
        fVar2 = ((f32)m846 / (f32)l_HIO.mPrm.m30);

        min  = -1.0f;
        max  =  1.0f;
        mult =  0.1f;

        fVar1 = mult * fVar1;
        fVar2 = mult * fVar2;

        fVar1 = cLib_minMaxLimit(fVar1, min, max);
        fVar2 = cLib_minMaxLimit(fVar2, min, max);
    } else {
        fVar1 = 0.0f;
        fVar2 = fVar1;
    }

    if (mpMatAnms[0]) {
        cLib_addCalc(&mpMatAnms[0]->getNowOffsetX(), fVar2, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&mpMatAnms[0]->getNowOffsetY(), fVar1, 0.5f, 0.1f, 0.03f);
    }

    fVar2 *= -1.0f;
    if (mpMatAnms[1]) {
        cLib_addCalc(&mpMatAnms[1]->getNowOffsetX(), fVar2, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&mpMatAnms[1]->getNowOffsetY(), fVar1, 0.5f, 0.1f, 0.03f);
    }
}

/* 00001490-000014E8       .text play_btk_anm__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::play_btk_anm() {
    u8 frame_max = mBtkAnm.getBtkAnm()->getFrameMax();
    if (m838) {
        eye_ctrl();
    } else {
        mBtkFrame++;
        if (mBtkFrame >= frame_max) {
            mBtkFrame = frame_max;
        }
    }
}

/* 000014E8-00001584       .text setAnm_anm__11daNpc_Ls1_cFPQ211daNpc_Ls1_c9anm_prm_c */
void daNpc_Ls1_c::setAnm_anm(daNpc_Ls1_c::anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->mBckResIndex < 0 || mBckResIndex == i_anmPrmP->mBckResIndex) {
        return;
    } else {
        int id = bckResID(i_anmPrmP->mBckResIndex);
        dNpc_setAnmIDRes(
            mpMorf, 
            i_anmPrmP->mLoopMode, 
            i_anmPrmP->mMorf, i_anmPrmP->mSpeed, 
            id, -1, 
            mArcName
        );
        mBckResIndex = i_anmPrmP->mBckResIndex;
        mbMorfAnimStopped = false;
        m831 = 0;
        mPrevMorfFrame = 0.0f;
    }
}

/* 00001584-000015F4       .text setAnm_NUM__11daNpc_Ls1_cFii */
void daNpc_Ls1_c::setAnm_NUM(int i_anmPrmIndex, int param_2) {
    static anm_prm_c a_anm_prm_tbl[14] = {
        {  0,  1, 8.0f, 1.0f, 2 },
        {  1,  1, 8.0f, 1.0f, 0 },
        {  2,  1, 8.0f, 1.0f, 2 },
        {  3,  1, 8.0f, 1.0f, 2 },
        {  4,  1, 8.0f, 1.0f, 2 },
        {  5,  1, 8.0f, 1.0f, 2 },
        {  6,  1, 8.0f, 1.0f, 0 },
        {  7,  1, 8.0f, 1.0f, 0 },
        {  8,  6, 8.0f, 1.0f, 2 },
        {  9,  4, 8.0f, 1.0f, 0 },
        { 10,  1, 8.0f, 1.0f, 2 },
        { 11,  1, 8.0f, 1.0f, 2 },
        { 12, 10, 8.0f, 1.0f, 2 },
        { 13, 10, 8.0f, 1.0f, 0 }
    };

    if (param_2 != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmPrmIndex].mResIndex, true);
    }

    setAnm_anm(&a_anm_prm_tbl[i_anmPrmIndex]);
}

/* 000015F4-00001660       .text setAnm__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[6] = {
        { -1, -1, 0.0f, 0.0f, -1 },
        {  0,  1, 8.0f, 1.0f,  2 },
        {  5,  1, 8.0f, 1.0f,  2 },
        { 10,  2, 8.0f, 1.0f,  2 },
        {  5,  1, 8.0f, 1.0f,  2 },
        { -1, -1, 0.0f, 0.0f, -1 }
    };

    init_texPttrnAnm(a_anm_prm_tbl[m851].mResIndex, true);
    setAnm_anm(&a_anm_prm_tbl[m851]);
}

/* 00001660-000016F8       .text chngAnmTag__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::chngAnmTag() {
    switch (mMesgAnimeTag) {
        case 0:
            init_texPttrnAnm(8, 1);
            return;
        case 11:
            init_texPttrnAnm(3, 1);
            return;
        case 12:
            init_texPttrnAnm(5, 1);
            return;
        case 13:
            init_texPttrnAnm(0, 1);
        case 0xFF:
            return;
    }
}

/* 000016F8-0000171C       .text ctrlAnmTag__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::ctrlAnmTag() {
    if ((s32)mMesgAnimeTag < 0xE) {
        if ((s32)mMesgAnimeTag == 0) {
            return;
        } else if ((s32)mMesgAnimeTag < 0) {
            return;
        }
        return;
    }

    switch (mMesgAnimeTag) {
        case 0xFF:
            break;
    }

    return;
}

/* 0000171C-00001820       .text chngAnmAtr__11daNpc_Ls1_cFUc */
void daNpc_Ls1_c::chngAnmAtr(u8 param_1) {
    if ((m84B == 3 || m84B == 5) && (param_1 == 3 || param_1 == 5)) {
        init_texPttrnAnm(8, true);
        m84B = param_1;
        return;
    }
    
    if (param_1 == m84B || param_1 > 17) {
        return;
    } 

    m84B = param_1;
    setAnm_ATR(1);
    
    switch (param_1) {
        case 1:
            mTimer2 = cLib_getRndValue(60, 90);
            break;
        case 3:
        case 5:
            mTimer2 = (g_Counter.mCounter0 & 3) + 3;
            break;
        case 7:
            mTelescopeScale = 0.0f;
            break;
        case 12:
        case 14:
        case 15:
        case 16:
            mTimer2 = 2;
            break;
        default:
            break;
    }

    return;
}

/* 00001820-00001A60       .text ctrlAnmAtr__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::ctrlAnmAtr() {  
    switch(m84B) {
    case 1:
        if (cLib_calcTimer(&mTimer2) == 0) {
            m84B = 2;
            setAnm_ATR(1);
        }
        break;
    case 2:
        if (mbMorfAnimStopped) {
            m84B = 1;
            setAnm_ATR(1);
        }
        break;
    case 3:
    case 5:
        if (mbMorfAnimStopped && cLib_calcTimer(&mTimer2) == 0) {
            mTimer2 = (g_Counter.mCounter0 & 3) + 3;
            switch (m84B) {
                case 3:
                    m84B = 5;
                    break;
                case 4:
                    break;
                case 5:
                    m84B = 3;
                    break;
                default:
                    break;
            }
            setAnm_ATR(0);
        }
        break;
    case 7:
        if (mpMorf->checkFrame(23.0f) != 0) {
            mTelescopeScale = 1.0f;
        }
        break;
    case 12:
    case 14:
    case 15:
    case 16:
        if (mbMorfAnimStopped && (cLib_calcTimer(&mTimer2) == 0)) {
            switch (m84B) {
            case 12:
                if (mBckResIndex != 10) {
                    setAnm_NUM(10,1);
                    init_texPttrnAnm(2,true);
                } 
                break;                     
            case 14:
                if (mBckResIndex != 5) {
                    setAnm_NUM(5,1);
                    init_texPttrnAnm(8, true);
                } 
                break;
            case 15: 
                if(mBckResIndex != 11) {
                    setAnm_NUM(0xB,1);
                    init_texPttrnAnm(8, true);
                }
                break;
            case 16:
                if (mBckResIndex != 4) {
                    setAnm_NUM(4,1);
                    init_texPttrnAnm(8, true);
                }
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
}

/* 00001A60-00001ACC       .text setAnm_ATR__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::setAnm_ATR(int param_1) {
    static anm_prm_c a_anm_prm_tbl[17] = {
        {  5, 1, 8.0f, 1.0f, 2 },
        {  0, 1, 8.0f, 1.0f, 2 },
        {  1, 1, 8.0f, 1.0f, 0 },
        {  2, 8, 8.0f, 1.0f, 2 },
        {  3, 2, 8.0f, 1.0f, 2 },
        {  4, 8, 8.0f, 1.0f, 2 },
        {  7, 1, 8.0f, 1.0f, 0 },
        {  6, 8, 8.0f, 1.0f, 0 },
        {  8, 6, 8.0f, 1.0f, 2 },
        {  9, 4, 8.0f, 1.0f, 0 },
        { 10, 0, 8.0f, 1.0f, 2 },
        { 10, 2, 8.0f, 1.0f, 2 },
        {  3, 2, 8.0f, 1.0f, 2 },
        {  5, 8, 8.0f, 1.0f, 2 },
        { 11, 8, 8.0f, 1.0f, 2 },
        {  3, 8, 8.0f, 1.0f, 2 },
        { 11, 8, 8.0f, 1.0f, 2 }
    };

    if (param_1 != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[m84B].mResIndex, true);
    }

    setAnm_anm(&a_anm_prm_tbl[m84B]);
}

/* 00001ACC-00001B88       .text anmAtr__11daNpc_Ls1_cFUs */
void daNpc_Ls1_c::anmAtr(u16 param_1) {
    u8 mesg_anime_tag;
    switch (param_1) {
        case 6:
            if (m857 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m857++;
            }
            mesg_anime_tag = dComIfGp_getMesgAnimeTagInfo();
            if (mesg_anime_tag!= 0xFF && mesg_anime_tag != mMesgAnimeTag) {
                dComIfGp_setMesgAnimeTagInfo(0xFF);
                mMesgAnimeTag = mesg_anime_tag;
                chngAnmTag();
            }
            break;
        case 14:
            m857 = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00001B88-00001C30       .text next_msgStatus__11daNpc_Ls1_cFPUl */
u16 daNpc_Ls1_c::next_msgStatus(u32* o_msgNoP) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
        case 0xBB9:
            if (dComIfGs_getClearCount()) {
                *o_msgNoP = 0xBDA;
                break;
            }
            *o_msgNoP = 0xBBA;
            break;
        case 0xBBA:
#if VERSION > VERSION_DEMO
        case 0xBDA:
#endif
            *o_msgNoP = 0xBBB;
            break;
        case 0xBBB:
            *o_msgNoP = 0xBBC;
            break;
        case 0xBBC:
            *o_msgNoP = 0xBBD;
            break;
        case 0xBBD:
            *o_msgNoP = 0xBDC;
            break;
        case 0xBBE:
            *o_msgNoP = 0xBBF;
            break;
        case 0xBC5:
            *o_msgNoP = 0xBC6;
            break;
        default:
            msg_status = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msg_status;
}

/* 00001C30-00001D48       .text getMsg_LS1_0__11daNpc_Ls1_cFv */
u32 daNpc_Ls1_c::getMsg_LS1_0() { 
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
        if (m835) {
            m835 = false;
            return dComIfGs_getpCollect()->checkCollect(0) != 0 ? 0xBC4 : 0xBC5;
        }
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0280)) {
            return 0xBC9;
        } else {
            return dComIfGs_getpCollect()->checkCollect(0) != 0 ? 0xBC8 : 0xBC7;
        }
    } 
    
    if (m836) {
        m836 = false;
        return 0xBBE;
    }


    if (dComIfGp_getSelectItem(dItemBtn_X_e) == dItem_TELESCOPE_e) {
        return 0xBCB;
    } 
    
    if (dComIfGp_getSelectItem(dItemBtn_Y_e) == dItem_TELESCOPE_e) {
        return 0xBCC;
    } 

    if (dComIfGp_getSelectItem(dItemBtn_Z_e) == dItem_TELESCOPE_e) {
        return 0xBCD;
    }
    
    return 0xBC0;
}

/* 00001D48-00001D50       .text getMsg_LS1_3__11daNpc_Ls1_cFv */
u32 daNpc_Ls1_c::getMsg_LS1_3() {
    return 0xBD9;
}

/* 00001D50-00001DAC       .text getMsg__11daNpc_Ls1_cFv */
u32 daNpc_Ls1_c::getMsg() {
    u32 result = 0;
    switch (mType) {
        case 0:
            result = getMsg_LS1_0();
            break;       
        case 3:
            result = getMsg_LS1_3();
            break;
        case 4:
        default:
            break;
    }

    return result;
}

/* 00001DAC-00001E38       .text eventOrder__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::eventOrder() {
    if (m850 == 1 || m850 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m850 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (m850 >= 3) {
        mEventIndex = m850 - 3;
        fopAcM_orderOtherEventId(this, mEventIDTbl[mEventIndex]);
    }
}

/* 00001E38-00001F78       .text checkOrder__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIDTbl[mEventIndex]) && m850 >= 3) {
            switch (mEventIndex) {
            case 0:
                dComIfGp_getCamera(0)->mCamera.Stop();
                mDoAud_bgmStreamPlay();
                m834 = true;
                break;
            case 1:
                cLib_targetAngleY(&m7CC[0], &current.pos);
                m83B = true;
                break;
            case 2:
                mTelescopeScale = 0.0f;
                setAnm_NUM(9, 1);
                break;
            }
            m850 = 0;
            m84B = 0xFF;
            mMesgAnimeTag = 0xFF;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (m850 == 1 || m850 == 2) {
            m850 = 0;
            m83F = true;
        }
    }
}

/* 00001F78-00002010       .text chk_talk__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            return true;
        } 
        return false;
    }

    mItemNo = 0xFF;
    return true;
}

/* 00002010-00002050       .text chk_parts_notMov__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::chk_parts_notMov() {
    return mJointHeadY != m_jnt.getHead_y() || 
        mJointBackboneY != m_jnt.getBackbone_y() ||
        mActorAngleY != current.angle.y;
}

/* 00002050-000020A4       .text searchByID__11daNpc_Ls1_cFUiPi */
fopAc_ac_c* daNpc_Ls1_c::searchByID(fpc_ProcID i_PID, int* param_2) {
    fopAc_ac_c* actor_p;

    actor_p = NULL;
    *param_2 = 0;
    if (!fopAcM_SearchByID(i_PID, &actor_p)) {
        *param_2 = 1;
    }

    return actor_p;
}

/* 000020A4-00002154       .text partner_search_sub__11daNpc_Ls1_cFPFPvPv_Pv */
bool daNpc_Ls1_c::partner_search_sub(void* (*i_funcP)(void*, void*)) {
    bool result = false;
    mBm1ProcID = fpcM_ERROR_PROCESS_ID_e;

    l_check_wrk = 0;
    for (int i = 0; i < ARRAY_SSIZE(l_check_inf); i++) {
        l_check_inf[i] = NULL;
    }

    fpcEx_Search(i_funcP, this);

    if (l_check_wrk != 0) {
        mBm1ProcID = fpcM_GetID(l_check_inf[0]);
        result = true;
    }

    return result;
}

/* 00002154-000021D4       .text partner_search__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::partner_search() {
    bool temp = false;
    if (m856 == 1) {
        switch (mType) {
            case 0:
                temp = partner_search_sub(searchActor_Bm1);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                temp = true;
                break;
            default:
                break;
        }
        if (temp) {
            m856++;
        }
    }
}

/* 000021D4-0000220C       .text setEyeCtrl__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::setEyeCtrl() {
    for (int i = 0; i < ARRAY_SSIZE(mpMatAnms); i++) {
        daNpc_Ls1_matAnm_c* mat_anm_p = mpMatAnms[i];
        if (mat_anm_p) {
            mat_anm_p->setMoveFlag();
        }
    }
    mbEyeCtrlSet = true;
}

/* 0000220C-00002244       .text clrEyeCtrl__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::clrEyeCtrl() {
    for (int i = 0; i < ARRAY_SSIZE(mpMatAnms); i++) {
        daNpc_Ls1_matAnm_c* mat_anm_p = mpMatAnms[i];
        if (mat_anm_p) {
            mat_anm_p->clrMoveFlag();
        }
    }
    mbEyeCtrlSet = false;
}

/* 00002244-00002464       .text lookBack__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::lookBack() {
    cXyz player_eye_pos;
    cXyz current_pos;

    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;

    current_pos = current.pos;
    current_pos.y = eyePos.y;

    player_eye_pos.set(0.0f, 0.0f, 0.0f);

    cXyz* player_eye_pos_p = NULL;
    s16 target_y = current.angle.y;
    bool temp_m840 = m840;

    switch (m853) {
        case 1:
            mPlayerEyePos = dNpc_playerEyePos(l_HIO.mPrm.mPlayerEyePosOffsetY);
            player_eye_pos = mPlayerEyePos;
            player_eye_pos_p = &player_eye_pos;
            m838 = true;
            break;
        case 2:
            player_eye_pos = mPlayerEyePos;
            player_eye_pos_p = &player_eye_pos;
            break;
        case 3:
            target_y = m82E;
            m838 = false;
            break;
        case 4:
            {
                int param;
                fopAc_ac_c* actor_p = searchByID(m790, &param);
                if (actor_p && param == 0) {
                    mPlayerEyePos = actor_p->current.pos;
                    mPlayerEyePos.y = actor_p->eyePos.y;
                    player_eye_pos = mPlayerEyePos;
                    player_eye_pos_p = &player_eye_pos;
                    m838 = true;
                }
            }
            break;
        default:
            m838 = false;
            break;
    }

    m_jnt.lookAtTarget_2(&current.angle.y, player_eye_pos_p, current_pos, target_y, l_HIO.mPrm.m12, temp_m840);
    mHalfHeadAngleX = m_jnt.getHead_x() / 2;
    mHalfHeadAngleY = m_jnt.getHead_y() / 2;
    m848 = mHalfHeadAngleX;
    m846 = -mHalfHeadAngleY;
}

/* 00002464-000024E4       .text chkAttention__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 000024E4-0000253C       .text setAttention__11daNpc_Ls1_cFb */
void daNpc_Ls1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_HIO.mPrm.mAttPosOffsetY,
        current.pos.z
    );

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(
        mTransformedEyePos.x,
        mTransformedEyePos.y,
        mTransformedEyePos.z
    );
}

/* 0000253C-00002670       .text decideType__11daNpc_Ls1_cFi */
bool daNpc_Ls1_c::decideType(int i_type) {
    if (m854 > 0) {
        return true;
    }

    m854 = 1;
    mType = -1;

    switch (i_type) {
        case 0:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
                mType = 0;
            }    
            break;
        case 1:
            mType = 1;
            break;
        case 2:
            mType = 2;
            break;
        case 3:
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
                mType = 3;
            }
            break;
        case 4:
            mType = 4;
            break;
    }
    
    if (mType < 0) {
        return 0;
    }

    strcpy(mArcName, "Ls");    
    return m854 != -1 && mType != -1;
}

/* 00002670-00002724       .text cut_init_LOK_PLYER__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_LOK_PLYER(int param_1) {
    int* prm_p = (int*)dComIfGp_evmng_getMyIntegerP(param_1, "prm_0");
    int prm = 0;

    m853 = 1;
    m840 = 0;

    m_jnt.offBackBoneLock();
    m_jnt.offHeadLock();

    if (prm_p) {
        prm = *prm_p;
    }

    if (cLib_checkBit<int>(prm, 1 << 3) != 0) {
        m_jnt.setTrn();
    } else {
        if (cLib_checkBit<int>(prm, 1)) {
            m840 = 1;
        }
        if (cLib_checkBit<int>(prm, 1 << 1)) {
            m_jnt.onBackBoneLock();
        }
        if (cLib_checkBit<int>(prm, 1 << 2)) {
            m_jnt.onHeadLock();
        }
    }
}

/* 00002724-0000272C       .text cut_move_LOK_PLYER__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::cut_move_LOK_PLYER() {
    return TRUE;
}

/* 0000272C-00002760       .text cut_init_PLYER_MOV__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_PLYER_MOV(int param_1) {
    UNUSED(param_1);
    dComIfGp_evmng_setGoal(&m7CC[1]);
}

/* 00002760-00002768       .text cut_move_PLYER_MOV__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::cut_move_PLYER_MOV() {
    return TRUE;
}

/* 00002768-0000276C       .text cut_init_WAI__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_WAI(int param_1) {
    UNUSED(param_1);
}

/* 0000276C-000027C0       .text cut_move_WAI__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::cut_move_WAI() {
    if (mBckResIndex != 1) {
        return TRUE;
    }
    
    if (mbMorfAnimStopped) {
        setAnm_NUM(0, 1);
        return TRUE;
    }
        
    return FALSE;
}

/* 000027C0-00002828       .text cut_init_ANM_CHG__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_ANM_CHG(int param_1) {
    int* anm_no_p = (int*)dComIfGp_evmng_getMyIntegerP(param_1, "AnmNo");
    int anm_no = mBckResIndex;

    if (anm_no_p) {
        anm_no = *anm_no_p;
    }

    setAnm_NUM(anm_no, 1);
}

/* 00002828-00002830       .text cut_move_ANM_CHG__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::cut_move_ANM_CHG() {
    return TRUE;
}

/* 00002830-000029B0       .text privateCut__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "LOK_PLYER",
        "PLYER_MOV",
        "WAI",
        "ANM_CHG"
    };

    if (i_staffIdx == -1) {
        return;
    }

    mActionIndex = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SSIZE(a_cut_tbl), TRUE, 0);

    if (mActionIndex == -1) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
        return;
    }

    if (dComIfGp_evmng_getIsAddvance(i_staffIdx)) {
        switch (mActionIndex) {
            case 0:
                cut_init_LOK_PLYER(i_staffIdx);
                break;
            case 1:
                cut_init_PLYER_MOV(i_staffIdx);
                break;
            case 2:
                cut_init_WAI(i_staffIdx);
                break;
            case 3:
                cut_init_ANM_CHG(i_staffIdx);
                break;
        }
    }

    bool cut_end;
    switch (mActionIndex) {
        case 0:
            cut_end = cut_move_LOK_PLYER();
            break;
        case 1:
            cut_end = cut_move_PLYER_MOV();
            break;
        case 2:
            cut_end = cut_move_WAI();
            break;
        case 3:
            cut_end = cut_move_ANM_CHG();
            break;
        default:
            cut_end = TRUE;
    }
    if (cut_end) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
}

/* 000029B0-000029D4       .text endEvent__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::endEvent() {
    dComIfGp_event_reset();
    m84B = 0xFF;
    mMesgAnimeTag = 0xFF;
}

/* 000029D4-00002A0C       .text isEventEntry__11daNpc_Ls1_cFv */
int daNpc_Ls1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00002A0C-00002BD0       .text event_proc__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIDTbl[mEventIndex])) {
        switch (mEventIndex) {
        case 0:
            if (m835) {
                if (dComIfGp_getScopeMesgStatus() == 0) {
                    dComIfGs_onEventBit(1);
                    setStt(3);
                    m850 = 1;
                    mEventIndex = 3;
                    eventInfo.setEventId(mEventIDTbl[mEventIndex]);
                    m_jnt.offBackBoneLock();
                    m834 = false;
                    m840 = 0;
                    m83B = false;
                } else {
                    return;
                }
            } else {
                if (!fopMsgM_releaseScopeMode()) {
                    return;
                }
                dComIfGp_getCamera(0)->mCamera.Start();
                daPy_getPlayerLinkActorClass()->onNoResetFlg0(daPy_py_c::daPyFlg0_SCOPE_CANCEL);
                mDoAud_bgmStop(4);
                mDoAud_bgmStart(0x8000000E);
                m835 = true;
                return;
            }
            break;
        case 1:
            m850 = 5;
            break;
        case 2:
            setStt(2);
            m850 = 1;
            m836 = true;
            break;
        }
        endEvent();
    } else {
        if (mEventCut.cutProc()) {
            return;
        }
        privateCut(i_staffIdx);
    }
    return;
}

/* 00002BD0-00002C7C       .text set_action__11daNpc_Ls1_cFM11daNpc_Ls1_cFPCvPvPv_iPv */
BOOL daNpc_Ls1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc) {
            m856 = 9;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        m856 = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00002C7C-00002D70       .text setStt__11daNpc_Ls1_cFSc */
void daNpc_Ls1_c::setStt(s8 param_1) {
    u8 prev_m851 = m851;
    m851 = param_1;
    switch (m851) {
        case 1:
            m850 = 0;
            mTimer5 = cLib_getRndValue(60, 90);
            break;
        case 2:
            m850 = 0;
            m833 = 0;
            mTimer3 = 0;
            break;
        case 3:
            m850 = 0;
            break;
        case 4:
            m850 = 0;
            mTelescopeScale = 1.0f;
            break;
        case 5:
            fpcEx_Search(searchActor_kamome_Set_NOSTOP_DEMO, this);
            m850 = 0;
            m84B = 0xFF;
            mMesgAnimeTag = 0xFF;
            m857 = 0;
            m852 = prev_m851;
            break;
    }
    setAnm();
}

/* 00002D70-00002EF8       .text chk_areaIN__11daNpc_Ls1_cFffs4cXyz */
bool daNpc_Ls1_c::chk_areaIN(f32 param_1, f32 param_2, s16 param_3, cXyz param_4) {
    f32 abs_xz = (dComIfGp_getLinkPlayer()->current.pos - param_4).absXZ();
    f32 fVar1 = dComIfGp_getLinkPlayer()->current.pos.y - param_4.y;
    s16 sVar = cLib_targetAngleY(&param_4, &dComIfGp_getLinkPlayer()->current.pos) - current.angle.y;

    if (abs_xz < param_1 && std::fabsf(fVar1) < param_2 && abs(sVar) < param_3) {
        return true;
    } else {
        return false;
    }
}

/* 00002EF8-00002FD8       .text get_playerEvnPos__11daNpc_Ls1_cFi */
cXyz daNpc_Ls1_c::get_playerEvnPos(int param_1) {
    const Vec pos[] = {
        { 200.0f, 0.0f, -200.0f },
        { 100.0f, 0.0f,  -80.0f },
    };

    cXyz sp14;
    cXyz sp08;

    sp14.set(pos[param_1].x, pos[param_1].y, pos[param_1].z);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&pos[param_1], &sp08);
    
    return sp08;
}

/* 00002FD8-00003154       .text chkTelescope_sph__11daNpc_Ls1_cF4cXyzff */
bool daNpc_Ls1_c::chkTelescope_sph(cXyz param_1, float param_2, float param_3) {
    bool chk;
    cXyz sp24;
    cXyz sp18;
    cXyz sp0C;

    sp24.set(319.5, 0.0f, 186.5f);

    mDoLib_project(&param_1, &sp18);

    sp18.z = sp18.y;
    sp18.y = 0.0f;

    sp0C.x = sp18.x - sp24.x;
    sp0C.y = 0.0f;
    sp0C.z = sp18.z - sp24.z;

    chk = false;
    if (sp0C.normalizeRS()) {
        sp0C *= param_2;
        sp18 += sp0C;
        chk = param_3 > std::sqrtf((sp18.x - sp24.x) * (sp18.x - sp24.x) + (sp18.z - sp24.z) * (sp18.z - sp24.z)); 
    }
    return chk;
}

/* 00003154-00003258       .text chkTelescope__11daNpc_Ls1_cF4cXyzff */
bool daNpc_Ls1_c::chkTelescope(cXyz param_1, float param_2, float param_3) {
    cXyz sp20;
    cXyz sp14;
    cXyz sp08;

    sp20.set(319.5f, 0.0f, 186.5f);

    f32 fov_y = dComIfGd_getView()->mFovy / 40.0f;
    if (fov_y > 1.0f) {
        fov_y = 1.0f;
    }

    mDoLib_project(&param_1, &sp14);

    sp14.z = sp14.y;
    sp14.y = 0.0f;

    sp08.x = fov_y * (sp14.x - sp20.x);
    sp08.y = 0.0f;
    sp08.z = fov_y * (sp14.z - sp20.z);

    return fabs(sp08.x) < param_2 && (sp08.z > param_3);
}

/* 00003258-000036B0       .text telescope_proc__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::telescope_proc() {
    int param;
    daNpc_Bm1_c* bm1_npc_p = (daNpc_Bm1_c *) searchByID(mBm1ProcID, &param);
    if (!bm1_npc_p || param == 1) {
        return false;
    }

    u8 scope_mesg_status = dComIfGp_getScopeMesgStatus();
    if (scope_mesg_status == 0) {
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e) != 0) {
            if (g_dComIfG_gameInfo.play.field_0x4978) {
                daPy_getPlayerLinkActorClass()->setPlayerPosAndAngle(&m7CC[1], 0xCC70);
            }
            dComIfGp_setScopeType(1);
            return true;
        }
        return false;
    }

    if (m833 == 0) {
        mDoAud_bgmStreamPrepare(JA_STRM_DEMO_TETRA_FLY);
        bm1_npc_p->m881 = 1;
        mTimer5 = 150;
        m810 = -1;
        m833 = 1;
        fopMsgM_getScopeMode();
        return true;
    }

    switch(dComIfGp_getScopeMesgStatus()) {
    case fopMsgStts_BOX_CLOSED_e:
        dComIfGp_setScopeMesgStatus(fopMsgStts_BOX_CLOSING_e);
        switch (m833) {
        case 3:
            if (m810 != 0) {
                dComIfGp_getCamera(0)->mCamera.clrFlag(0x800000);
                dComIfGp_getCamera(0)->mCamera.SubjectLockOff();
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0310);
                mTimer5 = 0;
                m833 = 4;
                fopMsgM_getScopeMode();
                return true;
            }
        }
    // fallthrough
    case fopMsgStts_CLOSE_WAIT_e:
    case fopMsgStts_UNKD_e: 
        {
            u32 temp_msg_no;
            switch (m833) {
            case 1:
                temp_msg_no = m810;
                m810 = 0xBC1;
                if (chkTelescope_sph(bm1_npc_p->attention_info.position, 0.0f, l_HIO.mPrm.m2C)) {
                    u32 temp;
                    if (dComIfGp_getCameraZoomScale(0) >= l_HIO.mPrm.m24) {
                        temp = 0xBCB;
                    } else {
                        temp = 0xBCA;
                    }
                    m810 = temp;
                }
                break;
            case 2:
                m810 = 0xBCA;
                if (dComIfGp_getCameraZoomScale(0) >= l_HIO.mPrm.m28) {
                    if (scope_mesg_status == fopMsgStts_CLOSE_WAIT_e) {
                        fopMsgM_forceSendOn();
                    }
                    dComIfGp_getCamera(0)->mCamera.setFlag(0x800000);
                    bm1_npc_p->m882 = 1;
                    mTimer5 = 0;
                    m810 = 0;
                    m833 = 3;
                    fopMsgM_getScopeMode();
                    return true;
                }
                break;
            case 3:
                if (m810 == 0 && bm1_npc_p->m880 != 0) {
                    if (scope_mesg_status == fopMsgStts_CLOSE_WAIT_e) {
                        fopMsgM_forceSendOn();
                    } else if (fopMsgM_releaseScopeMode()) {
                        m810 = 0xBC2;
                        fopMsgM_scopeMessageSet(m810);
                    }
                }
                fopMsgM_getScopeMode();
                return true;
            case 4:
                {
                    cXyz bmp1_npc_att_pos = bm1_npc_p->attention_info.position;
                    bmp1_npc_att_pos.y += 2000.0f;
                    if (chkTelescope(bmp1_npc_att_pos, 60.0f, -30.0f)) {
                        if (scope_mesg_status == fopMsgStts_CLOSE_WAIT_e) {
                            fopMsgM_forceSendOn();
                            break;
                        }
                        if (fopMsgM_releaseScopeMode()) {
                            m850 = 3;
                        }
                    }
                    m810 = 0xBC3;
                }
                break;
            }
            if ((m833 == 1 && temp_msg_no != m810) || cLib_calcTimer(&mTimer5) == 0) {
                if (scope_mesg_status == fopMsgStts_CLOSE_WAIT_e) {
                    fopMsgM_forceSendOn();
                    mTimer5 = 0;
                } else if (fopMsgM_releaseScopeMode()) {
                    mTimer5 = 150;
                    if (m833 == 1 && m810 == 0xBCB) {
                        dComIfGp_getCamera(0)->mCamera.SubjectLockOn(bm1_npc_p);
                        m810 = 0xBCA;
                        mTimer5 = 150;
                        m833 = 2;
                    }
                    if (m810 == 0xBC3) {
                        mTimer3 = cLib_getRndValue(30, 30);
                    }
                    fopMsgM_scopeMessageSet(m810);
                }
            }
        }
        break;
    default:
        break;
    }
    fopMsgM_getScopeMode();
    return true;
}

/* 000036B0-000037A4       .text wait_1__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::wait_1() {
    if (m850 < 3) {
        m850 = 0;
        if (chk_areaIN(l_HIO.mPrm.m29, 100.0f, 0x7FFF, current.pos)) {
            m850 = 4;
        }
    }
    
    m853 = 0;
    
    if (mBckResIndex == 0) {
        if (cLib_calcTimer(&mTimer5) == 0) {
            setAnm_NUM(1, 1);
        }
        return true;
    }
    
    if (mbMorfAnimStopped) {
        mTimer5 = cLib_getRndValue(60, 90);
        setAnm_NUM(0, 1);
    }

    return true;
}

/* 000037A4-00003A0C       .text wait_2__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::wait_2() {
    bool telescope_proc_result = false;

    cLib_addCalcAngleS(&current.angle.y, m7A0.y, 4, 0x800, 0x80);
    
    if (current.angle.y == m7A0.y && mBckResIndex != 0) {
        setAnm_NUM(0, 1);
    }

    if (m83F) {
        if (chk_talk()) {
            setStt(5);
            setAnm_NUM(5,1);
            m853 = 1;
            m_jnt.offBackBoneLock();
            m840 = 0;
            m_jnt.setTrn();
        }
        return TRUE;
    } else {
        if (m850 != 1 && m850 < 3) {
            m850 = 0;
            if (
                chk_areaIN(l_HIO.mPrm.m1C, 100.0f, 0x7FFF, current.pos) 
#if VERSION > VERSION_DEMO
                && dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e)
#endif
            ) {
                telescope_proc_result = telescope_proc();
            }

            if (!telescope_proc_result) {
                m850 = 2;
            }
        }
        m_jnt.onBackBoneLock();
        m840 = 1;
        if (m833 != 0) {
            cXyz base_pos(20.0f, 0.0f, 50.0f);
            if (m833 >= 4) {
                if (mBtpResIDIndex != 2) {
                    init_texPttrnAnm(2, true);
                }
                if (cLib_calcTimer(&mTimer3) != 0) {
                    m853 = 1;
                    return TRUE;
                }
                base_pos.y = 120.0f;
            }
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(current.angle.y);
            mDoMtx_stack_c::multVec(&base_pos, &mPlayerEyePos);
            m853 = 2;
            m838 = true; 
            return TRUE;
        } else {
            if (mbAttention && mBckResIndex == 0) {
                m853 = 1;
                return TRUE;
            } else {
                m853 = 0;
                return TRUE;
            }
        }
    }
}

/* 00003A0C-00003B24       .text wait_3__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::wait_3() {
    cXyz local_18;
    
    local_18.set(40.0f, 140.0f, 100.0f);
    
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(m7A0.y);
    mDoMtx_stack_c::multVec(&local_18, &mPlayerEyePos);

    cLib_addCalcAngleS(
        &current.angle.y, 
        cLib_targetAngleY(&current.pos, &mPlayerEyePos), 
        4, 0x800, 0x80
    );
    
    if (m83F) {
        if (chk_talk()) {
            setStt(5);
            m853 = 1;
            m840 = 0;
            m_jnt.setTrn();;
        }
        return true;
    } 
        
    if (m850 != 1) {
        m850 = 2;
    }

    m840 = 1;
    m853 = 2;
    m838 = true;    

    return true;
}

/* 00003B24-00003BE4       .text wait_4__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::wait_4() {
    if (m83F) {
        if (chk_talk()) {
            setStt(5);
            m853 = 1;
            m840 = 0;
            m_jnt.setTrn();
        }
        return true;
    } 

    m850 = 2;
    m840 = 1;

    if (mbAttention) {
        mTimer4 = cLib_getRndValue(15, 30);
    }

    if (cLib_calcTimer(&mTimer4) != 0) {
        m853 = 1;
        return true;
    } 

    m853 = 0;

    return true;
}

/* 00003BE4-00003CD8       .text talk_1__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::talk_1() {
    BOOL res = chk_parts_notMov();
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg == NULL) {
        return res;
    }
    switch (mpCurrMsg->mStatus) {
    case fopMsgStts_BOX_OPENING_e:
    case fopMsgStts_MSG_TYPING_e:
        break;
    case fopMsgStts_MSG_DESTROYED_e:
        switch (mCurrMsgNo) {
        case 0xBC2:
        case 0xBC3:
        case 0xBC5:
            break;
        case 0xBC4:
        case 0xBC6:
            eventInfo.mEventId = -1;
            break;
        }
        fpcEx_Search(searchActor_kamome_Clr_NOSTOP_DEMO, this);
        mItemNo = 0xFF;
        m83F = false;
        setStt(m852);
        mTimer4 = cLib_getRndValue(15, 30);
        endEvent();
        break;  
    }
    return res;
}

/* 00003CD8-00003EA8       .text wait_action1__11daNpc_Ls1_cFPv */
BOOL daNpc_Ls1_c::wait_action1(void* param_1) {
    UNUSED(param_1);
    switch (m856) {
        case 0:
            m7CC[0] = get_playerEvnPos(0);
            m7CC[1] = get_playerEvnPos(1);
            m856++;
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
                    setStt(3);
                } else {
                    if (dComIfGs_checkGetItem(dItem_TELESCOPE_e)) {
                        m7A0.y = current.angle.y;
                        setStt(2);
                    } else {
                        setStt(1);
                    }
                }
            } else {
                setStt(4);
            }
            break;
        case 9:
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch (m851) {                
                case 1:
                    mbSetEyePos = wait_1();
                    break;
                case 2:
                    mbSetEyePos = wait_2();
                    break;
                case 3:
                    mbSetEyePos = wait_3();
                    break;
                case 4:
                    mbSetEyePos = wait_4();
                    break;
                case 5:
                    mbSetEyePos = talk_1();
                    break;
            }
            break;
        default:
            break;
    }
    return TRUE;
}

/* 00003EA8-00003F30       .text demo_action1__11daNpc_Ls1_cFPv */
BOOL daNpc_Ls1_c::demo_action1(void* param_1) {
    UNUSED(param_1);
    switch (m856) {
        case 0:
            if (mType == 1) {
                setAnm_NUM(12, 1);
            } else {
                setAnm_NUM(5, 1);
            }
            m856++;
            break;
        case 1:
        case 2:
        case 3:
        case 9:
            break;
        default:
            break;
    }
    return TRUE;
}

/* 00003F30-000041B8       .text demo__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::demo() {
    if (demoActorID == 0) {
        if (m841) {
            if (mType == 3) {
                mBckResIndex = 14;
                setAnm_NUM(5, 1);
            }
            m841 = false;
        }
    } else {
        if (!m841) {
            for (int i = 0; i < ARRAY_SSIZE(mpMatAnms); i++) {
                if (mpMatAnms[i]) {
                    mpMatAnms[i]->clrMoveFlag();
                }
            }
            m841 = true;
            m83B = false;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }

        dDemo_actor_c* demo_actor_p = dComIfGp_demo_getActor(demoActorID);
        J3DAnmTexPattern* anm_pattern_p = mBtpAnm.getBtpAnm();
        if (anm_pattern_p) {
            u8 frame_max = anm_pattern_p->getFrameMax();
            mBtpFrame++;
            if (mBtpFrame >= frame_max) {
                mBtpFrame = frame_max;
            }
        }

        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData(mArcName);
        if (demo_btp_p) {
            mBtpAnm.init(
                mpMorf->getModel()->getModelData(), 
                demo_btp_p, 1, 
                J3DFrameCtrl::EMode_NONE, 
                1.0f, 0, -1, 
                true, 0
            );
            mBtpResIDIndex = 11;
            mBtpFrame = 0;
        }

        J3DAnmTextureSRTKey* anm_srt_p = mBtkAnm.getBtkAnm();
        if (anm_srt_p) {
            u8 frame_max = anm_srt_p->getFrameMax();
            mBtkFrame++;
            if (mBtkFrame >= frame_max) {
                mBtkFrame = frame_max;
            }
        }

        J3DAnmTextureSRTKey* demo_btk_p = demo_actor_p->getP_BtkData(mArcName);
        if (demo_btk_p) {
            mBtkAnm.init(
                mpMorf->getModel()->getModelData(), 
                demo_btk_p, true, 
                J3DFrameCtrl::EMode_NONE, 
                1.0f, 0, -1, 
                true, 0
            );
            mBtkResIDIndex = 3;
            mBtkFrame = 0;
        }

        if (demo_actor_p->checkEnable(dDemo_actor_c::ENABLE_SHAPE_e)) {
            if (demo_actor_p->getShapeId() == 1) {
                mTelescopeScale = 1.0f;
            } else {
                mTelescopeScale = 0.0f;
            }
        }
#if VERSION > VERSION_DEMO
        dDemo_setDemoData(this, 106, mpMorf, mArcName, 0, NULL, dBgS_GetGndMtrlSndId_Func(current.pos, 10.0f), dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
#else
        dDemo_setDemoData(this, 106, mpMorf, mArcName, 0, NULL);
#endif
    }

    return m841;
}

/* 000041B8-00004288       .text shadowDraw__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::shadowDraw() {
    cXyz pos(
        current.pos.x,
        current.pos.y + 150.0f,
        current.pos.z
    );

    mShadowID = dComIfGd_setShadow(
        mShadowID, 1, 
        mpMorf->getModel(), &pos, 
        800.0f, 40.0f, 
        current.pos.y, mObjAcch.GetGroundH(), 
        mObjAcch.m_gnd, &tevStr
    );

    if (mShadowID != 0) {
        if (mpTelescopeModel) {
            dComIfGd_addRealShadow(mShadowID, mpTelescopeModel);
        }
        dComIfGd_addRealShadow(mShadowID, mpLsHandModel);
    }
}

static void dummy() {
    const GXColor dummy1 = { 0xFF, 0x00, 0x00, 0x80 };
    const GXColor dummy2 = { 0x00, 0x00, 0xFF, 0x80 };
    const GXColor dummy3 = { 0xFF, 0xFF, 0x00, 0x80 };
    const GXColor dummy4 = { 0xFF, 0xFF, 0x00, 0x80 };
    const GXColor dummy5 = { 0x00, 0xFF, 0x00, 0x80 };
}

/* 00004288-00004418       .text _draw__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::_draw() {
    J3DModel* model_p = mpLsHandModel;
    J3DModel* morf_model_p = mpMorf->getModel();
    J3DModelData* morf_model_info_p = morf_model_p->getModelData();

    if (m83A || m83C != 0) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);
    g_env_light.setLightTevColorType(model_p, &tevStr);

    mBtpAnm.entry(morf_model_info_p, mBtpFrame);
    mBtkAnm.entry(morf_model_info_p, (f32)mBtkFrame);
    mpMorf->entryDL(); 

    mBtkAnm.remove(morf_model_info_p);
    mBtpAnm.remove(morf_model_info_p);

    mDoExt_modelEntryDL(model_p);

    if (mpTelescopeModel) {
        g_env_light.setLightTevColorType(mpTelescopeModel, &tevStr);
        mDoExt_modelEntryDL(mpTelescopeModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK49, this, 1.0f, 1.0f, 1.0f);

    // Does nothing
    if (l_HIO.mPrm.m18) {
        cXyz dummy = current.pos;
        dummy.y = dComIfGp_getLinkPlayer()->current.pos.y;
    }

    return TRUE;
}

/* 00004418-00004654       .text _execute__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::_execute() {
    if (!m83D) {
        m794 = current.pos;
        m7A0 = current.angle;
        m83D = true;
    }
    m_jnt.setParam(
        l_HIO.mPrm.mMaxBackBoneX,
        l_HIO.mPrm.mMaxBackBoneY,
        l_HIO.mPrm.mMinBackBoneX,
        l_HIO.mPrm.mMinBackBoneY,
        l_HIO.mPrm.mMaxHeadX,
        l_HIO.mPrm.mMaxHeadY,
        l_HIO.mPrm.mMinHeadX,
        l_HIO.mPrm.mMinHeadY,
        l_HIO.mPrm.mMaxTurnStep
    );

    if (m83A && demoActorID == 0) {
        return TRUE;
    } else {
        partner_search();
        checkOrder();
        if (!demo()) {
            int staff_id = -1;
            dBgS* bgs_p = dComIfG_Bgsp();
            if (dComIfGp_event_getMode() != 0 && eventInfo.checkCommandTalk() == false) {
                staff_id = isEventEntry();
            }

            if (staff_id >= 0 || m834) {
                event_proc(staff_id);
            } else {
                (this->*mCurrProcFunc)(NULL);
            }

            lookBack();

            if (mType != 0) {
                fopAcM_posMoveF(this, mStts.GetCCMoveP());
                mObjAcch.CrrPos(*bgs_p);
            }

            play_animation();
        } else {
            m83A = false;
        }

        eventOrder();
        mAngle = current.angle;
        if (!m83B) {
            shape_angle = current.angle;
        }

        tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
        setMtx(false);

        if (!m841) {
            setCollision(40.0f, 100.0f);
        }
    }

    return TRUE;
}

/* 00004654-000046A8       .text _delete__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::_delete() {
#if VERSION == VERSION_DEMO
    if (mbResLoadIsComplete) {
        l_HIO.removeHIO();
#endif
        dComIfG_resDelete(&mPhs, mArcName);
   
        if (DEMO_SELECT(mpMorf, heap && mpMorf)) {
            mpMorf->stopZelAnime();
        }
#if VERSION == VERSION_DEMO
    }
#endif
    return TRUE;
}

/* 000046A8-000047D4       .text _create__11daNpc_Ls1_cFv */
cPhs_State daNpc_Ls1_c::_create() {
    static int a_siz_tbl[] = {
        0,
        0
    };

    cPhs_State state;

#if VERSION > VERSION_DEMO
    fopAcM_ct(this, daNpc_Ls1_c);
#endif 

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mbResLoadIsComplete = state == cPhs_COMPLEATE_e;
    if (!mbResLoadIsComplete) {
        return state;
    }

#if VERSION == VERSION_DEMO
    l_HIO.entryHIO("アリル"); // Aryll
    fopAcM_ct(this, daNpc_Ls1_c);
#endif

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[m854])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0f, -20.0f, -50.0f, 50.0f, 140.0f, 50.0f);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

daNpc_Ls1_c::daNpc_Ls1_c() {}

/* 00004C98-00005250       .text bodyCreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*) dComIfG_getObjectIDRes(mArcName, LS_BDL_LS);
    JUT_ASSERT(DEMO_SELECT(0xBB3, 0xBC9), a_mdl_dat != NULL);

    for (u16 i = 0; i < a_mdl_dat->getMaterialNum(); i++) {
        J3DMaterial* mat = a_mdl_dat->getMaterialNodePointer(i);
        mat->setMaterialAnm(new daNpc_Ls1_matAnm_c());
    }

    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat, 
        NULL, NULL, 
        NULL, 
        J3DFrameCtrl::EMode_NULL, 
        1.0f, 0, -1, 1, 
        NULL, 
        0x80000, 
        0x11020222
    );

    if (!mpMorf) {
        return FALSE;
    } else if (!mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    if (mType == 4 || dComIfGs_getClearCount() != 0) {
        ResTIMG* tex_info_p = (ResTIMG*) dComIfG_getObjectIDRes(mArcName, LS_BTI_LSBODY02);
        
        J3DTexture* a_texture = a_mdl_dat->getTexture();
        JUT_ASSERT(DEMO_SELECT(0xBD1, 0xBE7), a_texture != NULL);
        
        JUTNameTab* a_textureName = a_mdl_dat->getTextureName();
        JUT_ASSERT(DEMO_SELECT(0xBD3, 0xBE9), a_textureName != NULL);

        for (u16 i = 0; i < a_texture->getNum(); i++) {
            const char* name = a_textureName->getName(i);
            if (strcmp(name, "lsbody01") == 0) {
                a_texture->setResTIMG(i, *tex_info_p);
            }
        }        
    }

    if (!init_texPttrnAnm(0, false)) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(0xBE4, 0xBFA), m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(0xBE6, 0xBFC), m_bbone_jnt_num >= 0);

    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(DEMO_SELECT(0xBE8, 0xBFE), m_hnd_L_jnt_num >= 0);

    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(DEMO_SELECT(0xBEA, 0xC00), m_hnd_R_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hnd_L_jnt_num)->setCallBack(nodeCB_Hand_L);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hnd_R_jnt_num)->setCallBack(nodeCB_Hand_R);
    mpMorf->getModel()->setUserArea((u32)this);
    
    return TRUE;
}

/* 00005250-00005428       .text handCreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::handCreateHeap() {
    mpLsHandModel = NULL;
    J3DModelData* a_mdl_dat = (J3DModelData*) dComIfG_getObjectIDRes(mArcName, LS_BDL_LSHAND);
    JUT_ASSERT(DEMO_SELECT(0xC09, 0xC1F), a_mdl_dat != NULL);
    mpLsHandModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);

    if (!mpLsHandModel) {
        return FALSE;
    }

    m_lsHnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("ls_handL");
    JUT_ASSERT(DEMO_SELECT(0xC11, 0xC27), m_lsHnd_L_jnt_num >= 0);

    m_lsHnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("ls_handR");
    JUT_ASSERT(DEMO_SELECT(0xC13, 0xC29), m_lsHnd_R_jnt_num >= 0);

    mpLsHandModel->getModelData()->getJointNodePointer(m_lsHnd_L_jnt_num)->setCallBack(Ls_hand_nodeCB_Hand_L);
    mpLsHandModel->getModelData()->getJointNodePointer(m_lsHnd_R_jnt_num)->setCallBack(Ls_hand_nodeCB_Hand_R);
    mpLsHandModel->setUserArea((u32)this);
    return TRUE;
}

/* 00005428-000054F8       .text itemCreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::itemCreateHeap() {
    mpTelescopeModel = NULL;

    J3DModelData* a_mdl_dat = (J3DModelData *) 
#if VERSION > VERSION_DEMO
        dComIfG_getObjectRes("Link", LINK_BDL_TELESCOPE);
#else
        dComIfG_getObjectIDRes("Link", LINK_BDL_TELESCOPE);
#endif

    JUT_ASSERT(DEMO_SELECT(0xC2D, 0xC43), a_mdl_dat != NULL);
    
    mpTelescopeModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    
    if (!mpTelescopeModel) {
        return FALSE;
    }
    
    return TRUE;
}

/* 000054F8-000055BC       .text CreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }

    if (!handCreateHeap()) {
        this->mpMorf = NULL;
        return FALSE;
    }

    if (!itemCreateHeap()) {
        this->mpMorf = NULL;
        return FALSE;
    }

    mAcchCir.SetWall(30.0f, 40.0f);
    cXyz* speed_p = &speed;
    cXyz* old_pos_p = &old.pos;
    cXyz* current_pos_p = &current.pos;
    mObjAcch.Set(current_pos_p, old_pos_p, this, 1, &mAcchCir, speed_p, NULL, NULL);

    return TRUE;
}

/* 000055BC-000055DC       .text daNpc_Ls1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ls1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ls1_c*)i_this)->_create();
}

/* 000055DC-000055FC       .text daNpc_Ls1_Delete__FP11daNpc_Ls1_c */
static BOOL daNpc_Ls1_Delete(daNpc_Ls1_c* i_this) {
    return ((daNpc_Ls1_c*)i_this)->_delete();
}

/* 000055FC-0000561C       .text daNpc_Ls1_Execute__FP11daNpc_Ls1_c */
static BOOL daNpc_Ls1_Execute(daNpc_Ls1_c* i_this) {
    return ((daNpc_Ls1_c*)i_this)->_execute();
}

/* 0000561C-0000563C       .text daNpc_Ls1_Draw__FP11daNpc_Ls1_c */
static BOOL daNpc_Ls1_Draw(daNpc_Ls1_c* i_this) {
    return ((daNpc_Ls1_c*)i_this)->_draw();
}

/* 0000563C-00005644       .text daNpc_Ls1_IsDelete__FP11daNpc_Ls1_c */
static BOOL daNpc_Ls1_IsDelete(daNpc_Ls1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ls1_Method = {
    (process_method_func)daNpc_Ls1_Create,
    (process_method_func)daNpc_Ls1_Delete,
    (process_method_func)daNpc_Ls1_Execute,
    (process_method_func)daNpc_Ls1_IsDelete,
    (process_method_func)daNpc_Ls1_Draw,
};

actor_process_profile_definition g_profile_NPC_LS1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_LS1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ls1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_LS1,
    /* Actor SubMtd */ &l_daNpc_Ls1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
