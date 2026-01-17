/**
 * d_a_npc_ls1.cpp
 * NPC - Aryll
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ls1.h"
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
    /* Apparent match */
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
        {0, 0, 0}, // probably padding
        700.0f,
        200.0f,
        2.0f,
        9.0f,
        50.0f,
        0x1A2C,
        {0, 0}, // also probably padding
        9.0f
    };
    memcpy(&field_0x0C, &a_prm_tbl, 0x38);
    field_0x04 = -1;
    field_0x08 = -1;
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
    field_0x7C = 0;
    field_0x70 = 0.0f;
    field_0x6C = 0.0f;
}

/* 000001F8-0000028C       .text calc__18daNpc_Ls1_matAnm_cCFP11J3DMaterial */
void daNpc_Ls1_matAnm_c::calc(J3DMaterial* param_1) const {
    J3DMaterialAnm::calc(param_1);
    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i)) {
            J3DTexMtx* tex_mtx_p = param_1->getTexMtx(i);
            if (field_0x7C != 0) {
                tex_mtx_p->getTextureSRT().mTranslationX = field_0x6C;
                tex_mtx_p->getTextureSRT().mTranslationY = field_0x70;
            }
        }
    }
}

/* 0000028C-000002D8       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param2) {
    if (i_param2 == 0 && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* a_actor = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        a_actor->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 000002D8-000003F8       .text _nodeCB_Head__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_Head(J3DNode* param_1, J3DModel* param_2) {
    static cXyz a_eye_pos_off(14.0f, 18.0f, 0.0f); 
    
    J3DJoint* jnt_p = (J3DJoint *) param_1;
    u16 jnt_no = jnt_p->getJntNo();
    
    mDoMtx_stack_c::copy(param_2->getAnmMtx(jnt_no));

    field_0x7E4.x = mDoMtx_stack_c::get()[0][3];
    field_0x7E4.y = mDoMtx_stack_c::get()[1][3];
    field_0x7E4.z = mDoMtx_stack_c::get()[2][3];
    
    mDoMtx_stack_c::XrotM(field_0x842);
    mDoMtx_stack_c::ZrotM(-field_0x844);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &field_0x7B4);
    
    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    param_2->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000434-00000480       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param2) {
    if (i_param2 == 0 && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* a_actor = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        a_actor->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000480-00000520       .text _nodeCB_BackBone__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_BackBone(J3DNode* param_1, J3DModel* param_2) {
    J3DJoint* jnt_p = (J3DJoint *) param_1;
    u16 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(param_2->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    param_2->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000520-0000056C       .text nodeCB_Hand_L__FP7J3DNodei */
static BOOL nodeCB_Hand_L(J3DNode* i_node, int i_param2) {
    if (i_param2 == 0 && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* a_actor = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        a_actor->_nodeCB_Hand_L(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 0000056C-000005F4       .text _nodeCB_Hand_L__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_Hand_L(J3DNode* param_1, J3DModel* param_2) {
    J3DJoint* jnt_p = (J3DJoint *) param_1;
    u16 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(param_2->getAnmMtx(jnt_no));

    mDoMtx_copy(mDoMtx_stack_c::get(), field_0x72C);
    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    param_2->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000005F4-00000640       .text nodeCB_Hand_R__FP7J3DNodei */
static BOOL nodeCB_Hand_R(J3DNode* i_node, int i_param2) {
    if (i_param2 == 0 && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* a_actor = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        a_actor->_nodeCB_Hand_R(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000640-000006C8       .text _nodeCB_Hand_R__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_nodeCB_Hand_R(J3DNode* param_1, J3DModel* param_2) {
    J3DJoint* jnt_p = (J3DJoint *) param_1;
    u16 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(param_2->getAnmMtx(jnt_no));

    mDoMtx_copy(mDoMtx_stack_c::get(), field_0x75C);
    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    param_2->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000006C8-00000714       .text Ls_hand_nodeCB_Hand_L__FP7J3DNodei */
static BOOL Ls_hand_nodeCB_Hand_L(J3DNode* i_node, int i_param2) {
    if (i_param2 == 0 && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* a_actor = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        a_actor->_Ls_hand_nodeCB_Hand_L(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000714-00000770       .text _Ls_hand_nodeCB_Hand_L__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_Ls_hand_nodeCB_Hand_L(J3DNode* param_1, J3DModel* param_2) {
    J3DJoint* jnt_p = (J3DJoint *) param_1;
    int jnt_no = jnt_p->getJntNo();

    mDoMtx_copy(field_0x72C, j3dSys.mCurrentMtx);
    param_2->setAnmMtx(jnt_no, field_0x72C);
}

/* 00000770-000007BC       .text Ls_hand_nodeCB_Hand_R__FP7J3DNodei */
static BOOL Ls_hand_nodeCB_Hand_R(J3DNode* i_node, int i_param2) {
    if (i_param2 == 0 && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ls1_c* a_actor = (daNpc_Ls1_c*) j3dSys.getModel()->getUserArea();
        a_actor->_Ls_hand_nodeCB_Hand_R(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 000007BC-00000818       .text _Ls_hand_nodeCB_Hand_R__11daNpc_Ls1_cFP7J3DNodeP8J3DModel */
void daNpc_Ls1_c::_Ls_hand_nodeCB_Hand_R(J3DNode* param_1, J3DModel* param_2) {
    J3DJoint* jnt_p = (J3DJoint *) param_1;
    int jnt_no = jnt_p->getJntNo();

    mDoMtx_copy(field_0x75C, j3dSys.mCurrentMtx);
    param_2->setAnmMtx(jnt_no, field_0x75C);
}

/* 00000818-00000838       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ls1_c*)i_this)->CreateHeap();
}

/* 00000838-000008B0       .text searchActor_Bm1__FPvPv */
void* searchActor_Bm1(void* param_1, void* param_2) {
    UNUSED(param_2);

    if (l_check_wrk < 0x14 && fopAc_IsActor(param_1) && fpcM_GetName(param_1) == PROC_NPC_BM1) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)param_1;
        l_check_wrk++;
    }

    return NULL;
}

/* 000008B0-00000900       .text searchActor_kamome_Set_NOSTOP_DEMO__FPvPv */
void* searchActor_kamome_Set_NOSTOP_DEMO(void* param_1, void* param_2) {
    UNUSED(param_2);

    if (fopAc_IsActor(param_1) && fpcM_GetName(param_1) == PROC_KAMOME) {
        fopAcM_OnStatus((fopAc_ac_c*)param_1, fopAcStts_UNK4000_e);
    }

    return NULL;
}

/* 00000900-00000950       .text searchActor_kamome_Clr_NOSTOP_DEMO__FPvPv */
void* searchActor_kamome_Clr_NOSTOP_DEMO(void* param_1, void* param_2) {
    UNUSED(param_2);

    if (fopAc_IsActor(param_1) && fpcM_GetName(param_1) == PROC_KAMOME) {
        fopAcM_OffStatus((fopAc_ac_c*)param_1, fopAcStts_UNK4000_e);
    }
    
    return NULL;
}

/* 00000950-000009B4       .text init_LS1_0__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::init_LS1_0() {
    /* Apparent match */
    set_action(&daNpc_Ls1_c::wait_action1, NULL);
    fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
    return true;
}

/* 000009B4-00000A00       .text init_LS1_1__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::init_LS1_1() {
    /* Apparent match */
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
    for (int i = 0; i < ARRAY_SSIZE(field_0x814); i++) {
        field_0x814[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    mEventCut.setActorInfo2("Ls1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;    
    
    switch (field_0x855) {
        case 3:
        case 4:
            break;
    }
    
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = 0.0f;
    field_0x84F = 0xE;

    bool res;
    switch (field_0x855) {
        case 0:
            res = init_LS1_0();
            break;
        case 1:
            res = init_LS1_1();
            break;
        case 2:
            res = init_LS1_2();
            break;
        case 3:
            res = init_LS1_3();
            break;
        case 4:
            res = init_LS1_4();
            break;
        default:
            res = 0;
            break;
    }

    if (!res) {
        return false;
    }

    field_0x7A6 = current.angle;
    shape_angle = field_0x7A6;
    
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    
    play_animation();
    
    if (field_0x855) {
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
    if (field_0x84E == 0 && field_0x838 == 1) {
        setEyeCtrl();
    } else {
        clrEyeCtrl();
    }

    play_btp_anm();
    play_btk_anm();

    if (mObjAcch.ChkGroundHit()) {
        snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    field_0x830 = mpMorf->play(&eyePos, snd_id, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    if (mpMorf->getFrame() < field_0x800) {
        field_0x830 = 1;
    }

    field_0x800 = mpMorf->getFrame();
}

/* 00000D48-00000EF0       .text setMtx__11daNpc_Ls1_cFb */
void daNpc_Ls1_c::setMtx(bool param_1) {
    /* Apparent match */
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(field_0x7A6);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    field_0x6E8->calc();
    if (field_0x6D0) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        if (field_0x841) {
            mDoMtx_stack_c::transM(5.7f, -17.5f, -1.0f);
            mDoMtx_stack_c::scaleM(field_0x6D4, field_0x6D4, field_0x6D4);
            mDoMtx_stack_c::XYZrotM(-0x1D27, 0x3B05, -0x5C71);
        } else {
            mDoMtx_stack_c::transM(5.5f, -3.0f, -2.0f);
            mDoMtx_stack_c::scaleM(field_0x6D4, field_0x6D4, field_0x6D4);
            mDoMtx_stack_c::XYZrotM(-0x1D27, 0x3B05, -0x5C71);
        }
        field_0x6D0->setBaseTRMtx(mDoMtx_stack_c::get());
        field_0x6D0->calc();
    }
    setAttention(param_1);
}

/* 00000EF0-00000F04       .text bckResID__11daNpc_Ls1_cFi */
int daNpc_Ls1_c::bckResID(int param_1) {
    /* Apparent match */
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
    return a_resID_tbl[param_1];
}

/* 00000F04-00000F18       .text btpResID__11daNpc_Ls1_cFi */
int daNpc_Ls1_c::btpResID(int param_1) {  
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
    return a_resID_tbl[param_1];
}

/* 00000F18-00000F2C       .text btkResID__11daNpc_Ls1_cFi */
int daNpc_Ls1_c::btkResID(int param_1) {
    /* Apparent match */
    static const int a_resID_tbl[] = {
        LS_BTK_LS,
        LS_BTK_LS_DEMOLOOK,
        LS_BTK_LS_DEMOWAIT
    };
    return a_resID_tbl[param_1];
}

/* 00000F2C-00001030       .text setBtp__11daNpc_Ls1_cFScb */
bool daNpc_Ls1_c::setBtp(s8 param_1, bool param_2) {
    /* Apparent match */
    J3DModel* morf_model_p = mpMorf->getModel();

    if (param_1 < 0) {
        return false;
    }
    
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*) dComIfG_getObjectIDRes(field_0x6E0, btpResID(param_1));
    JUT_ASSERT(0x302, a_btp != NULL);
    field_0x84D = param_1;
    field_0x71C = 0;
    field_0x71E = 0;

    return field_0x708.init(morf_model_p->getModelData(), a_btp, TRUE, 0, 1.0f, 0, -1, param_2, 0) != 0;
}

/* 00001030-000010B0       .text setMat__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::setMat() {
    J3DModel* model_p = mpMorf->getModel();
    u16 material_num = field_0x6F0.getBtkAnm()->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        u16 material_id = field_0x6F0.getBtkAnm()->getUpdateMaterialID(i);
        field_0x6D8[i] = (daNpc_Ls1_matAnm_c *)model_p->getModelData()->getMaterialNodePointer(material_id)->getMaterialAnm();
    }
}

/* 000010B0-000011CC       .text setBtk__11daNpc_Ls1_cFScb */
bool daNpc_Ls1_c::setBtk(s8 param_1, bool param_2) {
    /* Apparent match */
    J3DModel* morf_model_p = mpMorf->getModel();

    if (param_1 < 0) {
        return false;
    }
    
    J3DAnmTextureSRTKey* a_btk = (J3DAnmTextureSRTKey *)dComIfG_getObjectIDRes(field_0x6E0, btkResID(param_1));
    JUT_ASSERT(0x32C, a_btk != NULL);

    field_0x84E = param_1;
    field_0x704 = 0;

    if (field_0x6F0.init(morf_model_p->getModelData(), a_btk, TRUE, 0, 1.0f, 0, -1, param_2, 0) != 0) {
        if (!param_2) {
            setMat();
        }
        return true;
    }

    return false;
}

/* 000011CC-00001238       .text init_texPttrnAnm__11daNpc_Ls1_cFScb */
bool daNpc_Ls1_c::init_texPttrnAnm(s8 param_1, bool param_2) {
    /* Apparent match */
    static const u8 a_btk_num_tbl[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2
    };

    if (setBtp(param_1, param_2) == false) {
        return false;
    } 

    return setBtk(a_btk_num_tbl[param_1],param_2);
}

/* 00001238-000012D4       .text play_btp_anm__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::play_btp_anm() {
    u8 frame_max = field_0x708.getBtpAnm()->getFrameMax();
    if (field_0x84D != 1 || cLib_calcTimer(&field_0x71E) == 0) {
        field_0x71C++;
        if (field_0x71C >= frame_max) {
            if (field_0x84D != 1) {
                field_0x71C = frame_max;
            } else {
                field_0x71E = cLib_getRndValue(0x3C, 0x5A);
                field_0x71C = 0;
            }
        }
    }
}

/* 000012D4-00001490       .text eye_ctrl__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::eye_ctrl() {
    /* Apparent match */
    f32 fVar1, fVar2;
    if (field_0x839 != 0) {
        fVar1 = ((f32)field_0x848 / (f32)l_HIO.field_0x0C.field_0x30);
        fVar2 = ((f32)field_0x846 / (f32)l_HIO.field_0x0C.field_0x30);

        fVar1 = -0.1f * fVar1;
        fVar2 = -0.1f * fVar2;

        fVar1 = cLib_minMaxLimit(fVar1, -1.0f, 1.0f);
        fVar2 = cLib_minMaxLimit(fVar2, -1.0f, 1.0f);
    } else {
        fVar1 = 0.0f;
        fVar2 = fVar1;
    }

    if (field_0x6D8[0]) {
        cLib_addCalc(&field_0x6D8[0]->getNowOffsetX(), fVar2, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&field_0x6D8[0]->getNowOffsetY(), fVar1, 0.5f, 0.1f, 0.03f);
    }

    fVar2 *= -1.0f;
    if (field_0x6D8[1]) {
        cLib_addCalc(&field_0x6D8[1]->getNowOffsetX(), fVar2, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&field_0x6D8[1]->getNowOffsetY(), fVar1, 0.5f, 0.1f, 0.03f);
    }
}

/* 00001490-000014E8       .text play_btk_anm__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::play_btk_anm() {
    u8 duration = field_0x6F0.getBtkAnm()->getFrameMax();
    if (field_0x838 != 0) {
        eye_ctrl();
    } else {
        field_0x704++;
        if (field_0x704 >= duration) {
            field_0x704 = duration;
        }
    }
}

/* 000014E8-00001584       .text setAnm_anm__11daNpc_Ls1_cFPQ211daNpc_Ls1_c9anm_prm_c */
void daNpc_Ls1_c::setAnm_anm(daNpc_Ls1_c::anm_prm_c* param_1) {
    if (param_1->field_0x00 < 0 || field_0x84F == param_1->field_0x00) {
        return;
    } else {
        int id = bckResID(param_1->field_0x00);
        dNpc_setAnmIDRes(
            mpMorf, 
            param_1->field_0x0C, 
            param_1->field_0x04, param_1->field_0x08, 
            id, -1, 
            field_0x6E0
        );
        field_0x84F = param_1->field_0x00;
        field_0x830 = 0;
        field_0x831 = 0;
        field_0x800 = 0.0f;
    }
}

/* 00001584-000015F4       .text setAnm_NUM__11daNpc_Ls1_cFii */
void daNpc_Ls1_c::setAnm_NUM(int param_1, int param_2) {
    /* Apparent match */
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
        init_texPttrnAnm(a_anm_prm_tbl[param_1].field_0x01, true);
    }
    setAnm_anm(&a_anm_prm_tbl[param_1]);
}

/* 000015F4-00001660       .text setAnm__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::setAnm() {
    /* Apparent match */
    static anm_prm_c a_anm_prm_tbl[6] = {
        { -1, -1, 0.0f, 0.0f, -1 },
        {  0,  1, 8.0f, 1.0f,  2 },
        {  5,  1, 8.0f, 1.0f,  2 },
        { 10,  2, 8.0f, 1.0f,  2 },
        {  5,  1, 8.0f, 1.0f,  2 },
        { -1, -1, 0.0f, 0.0f, -1 }
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x851].field_0x01, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x851]);
}

/* 00001660-000016F8       .text chngAnmTag__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::chngAnmTag() {
    switch (field_0x84C) {
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
    /* Matching, but at what cost? */
    if ((s32)field_0x84C < 0xE) {
        if ((s32)field_0x84C == 0) {
            return;
        } else if ((s32)field_0x84C < 0) {
            return;
        }
        return;
    }

    switch (field_0x84C) {
        case 0xFF:
            break;
    }

    return;
}

/* 0000171C-00001820       .text chngAnmAtr__11daNpc_Ls1_cFUc */
void daNpc_Ls1_c::chngAnmAtr(u8 param_1) {
    /* Apparent match */
    if ((field_0x84B == 3 || field_0x84B == 5) && (param_1 == 3 || param_1 == 5)) {
        init_texPttrnAnm(8, true);
        field_0x84B = param_1;
        return;
    }
    
    if (param_1 == field_0x84B || param_1 > 0x11) {
        return;
    } 

    field_0x84B = param_1;
    setAnm_ATR(1);
    
    switch (param_1) {
        case 1:
            field_0x81E = cLib_getRndValue(0x3C, 0x5A);
            break;
        case 3:
        case 5:
            field_0x81E = (g_Counter.mCounter0 & 3) + 3;
            break;
        case 7:
            field_0x6D4 = 0.0f;
            break;
        case 12:
        case 14:
        case 15:
        case 16:
            field_0x81E = 2;
            break;
        default:
            break;
    }

    return;
}

/* 00001820-00001A60       .text ctrlAnmAtr__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::ctrlAnmAtr() {  
    switch(field_0x84B) {
    case 1:
        if (cLib_calcTimer(&field_0x81E) == 0) {
            field_0x84B = 2;
            setAnm_ATR(1);
        }
        break;
    case 2:
        if (field_0x830 != 0) {
            field_0x84B = 1;
            setAnm_ATR(1);
        }
        break;
    case 3:
    case 5:
        if ((field_0x830 != 0) && cLib_calcTimer(&field_0x81E) == 0) {
            field_0x81E = (g_Counter.mCounter0 & 3) + 3;
            switch (field_0x84B) {
                case 3:
                    field_0x84B = 5;
                    break;
                case 4:
                    break;
                case 5:
                    field_0x84B = 3;
                    break;
                default:
                    break;
            }
            setAnm_ATR(0);
        }
        break;
    case 7:
        if (mpMorf->checkFrame(23.0f) != 0) {
            field_0x6D4 = 1.0f;
        }
        break;
    case 0xc:
    case 0xe:
    case 0xf:
    case 0x10:
        if ((field_0x830 != 0) && (cLib_calcTimer(&field_0x81E) == 0)) {
            switch (field_0x84B) {
            case 12:
                if (field_0x84F != 10) {
                    setAnm_NUM(10,1);
                    init_texPttrnAnm(2,true);
                } 
                break;                     
            case 14:
                if (field_0x84F != 5) {
                    setAnm_NUM(5,1);
                    init_texPttrnAnm(8, true);
                } 
                break;
            case 15: 
                if(field_0x84F != 0xb) {
                    setAnm_NUM(0xb,1);
                    init_texPttrnAnm(8, true);
                }
                break;
            case 16:
                if (field_0x84F != 4) {
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
    /* Apparent match */
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
        init_texPttrnAnm(a_anm_prm_tbl[field_0x84B].field_0x01, true);
    }

    setAnm_anm(&a_anm_prm_tbl[field_0x84B]);
}

/* 00001ACC-00001B88       .text anmAtr__11daNpc_Ls1_cFUs */
void daNpc_Ls1_c::anmAtr(u16 param_1) {
    u8 tmp;
    switch (param_1) {
        case 6:
            if (field_0x857 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x857++;
            }
            tmp = dComIfGp_getMesgAnimeTagInfo();
            if (tmp!= 0xFF && tmp != field_0x84C) {
                dComIfGp_setMesgAnimeTagInfo(0xFF);
                field_0x84C = tmp;
                chngAnmTag();
            }
            break;
        case 14:
            field_0x857 = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00001B88-00001C30       .text next_msgStatus__11daNpc_Ls1_cFPUl */
u16 daNpc_Ls1_c::next_msgStatus(u32* param_1) {
    u16 result = 0xF;
    switch (*param_1) {
        case 0xBB9:
            if (dComIfGs_getClearCount()) {
                *param_1 = 0xBDA;
                break;
            }
            *param_1 = 0xBBA;
            break;
        case 0xBBA:
        case 0xBDA:
            *param_1 = 0xBBB;
            break;
        case 0xBBB:
            *param_1 = 0xBBC;
            break;
        case 0xBBC:
            *param_1 = 0xBBD;
            break;
        case 0xBBD:
            *param_1 = 0xBDC;
            break;
        case 0xBBE:
            *param_1 = 0xBBF;
            break;
        case 0xBC5:
            *param_1 = 0xBC6;
            break;
        default:
            result = 0x10;
            break;
    }
    return result;
}

/* 00001C30-00001D48       .text getMsg_LS1_0__11daNpc_Ls1_cFv */
u32 daNpc_Ls1_c::getMsg_LS1_0() { 
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
        if (field_0x835 != 0) {
            field_0x835 = 0;
            return dComIfGs_getpCollect()->checkCollect(0) != 0 ? 0xBC4 : 0xBC5;
        }
        if (dComIfGs_isEventBit(0x280)) {
            return 0xBC9;
        } else {
            return dComIfGs_getpCollect()->checkCollect(0) != 0 ? 0xBC8 : 0xBC7;
        }
    } 
    
    if (field_0x836) {
        field_0x836 = 0;
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
    switch (field_0x855) {
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
    if (field_0x850 == 1 || field_0x850 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x850 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (field_0x850 >= 3) {
        field_0x81C = field_0x850 - 3;
        fopAcM_orderOtherEventId(this, field_0x814[field_0x81C]);
    }
}

/* 00001E38-00001F78       .text checkOrder__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::checkOrder() {
    /* Nonmatching */
}

/* 00001F78-00002010       .text chk_talk__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::chk_talk() {
    bool result;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            field_0x832 = dComIfGp_event_getPreItemNo();
            result = true;
        } else {
            result = false;
        }
    } else {
        field_0x832 = 0xFF;
        result = true;
    }
    return result;
}

/* 00002010-00002050       .text chk_parts_notMov__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::chk_parts_notMov() {
    bool result = false;
    if (field_0x806 != m_jnt.getHead_y() || 
        field_0x808 != m_jnt.getBackbone_y() ||
        field_0x804 != current.angle.y) {
            result = true;
    }
    return result;
}

/* 00002050-000020A4       .text searchByID__11daNpc_Ls1_cFUiPi */
fopAc_ac_c* daNpc_Ls1_c::searchByID(fpc_ProcID param_1, int* param_2) {
    fopAc_ac_c* actor_p;

    actor_p = NULL;
    *param_2 = 0;
    if (!fopAcM_SearchByID(param_1, &actor_p)) {
        *param_2 = 1;
    }

    return actor_p;
}

/* 000020A4-00002154       .text partner_search_sub__11daNpc_Ls1_cFPFPvPv_Pv */
bool daNpc_Ls1_c::partner_search_sub(void* (*param_1)(void*, void*)) {
    bool result = 0;
    field_0x78C = fpcM_ERROR_PROCESS_ID_e;

    l_check_wrk = 0;
    for (int i = 0; i < ARRAY_SSIZE(l_check_inf); i++) {
        l_check_inf[i] = NULL;
    }

    fpcEx_Search(param_1, this);

    if (l_check_wrk != 0) {
        field_0x78C = fpcM_GetID(l_check_inf[0]);
        result = true;
    }

    return result;
}

/* 00002154-000021D4       .text partner_search__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::partner_search() {
    bool tmp = false;
    if (field_0x856 == 1) {
        switch (field_0x855) {
            case 0:
                tmp = partner_search_sub(searchActor_Bm1);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                tmp = true;
                break;
            default:
                break;
        }
        if (tmp) {
            field_0x856++;
        }
    }
}

/* 000021D4-0000220C       .text setEyeCtrl__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::setEyeCtrl() {
    for (int i = 0; i < ARRAY_SSIZE(field_0x6D8); i++) {
        daNpc_Ls1_matAnm_c* mat_anm_p = field_0x6D8[i];
        if (mat_anm_p) {
            mat_anm_p->setMoveFlag();
        }
    }
    field_0x839 = 1;
}

/* 0000220C-00002244       .text clrEyeCtrl__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::clrEyeCtrl() {
    for (int i = 0; i < ARRAY_SSIZE(field_0x6D8); i++) {
        daNpc_Ls1_matAnm_c* mat_anm_p = field_0x6D8[i];
        if (mat_anm_p) {
            mat_anm_p->clrMoveFlag();
        }
    }
    field_0x839 = 0;
}

/* 00002244-00002464       .text lookBack__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::lookBack() {
    /* Nonmatching */
}

/* 00002464-000024E4       .text chkAttention__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::chkAttention() {
    if (!dComIfGp_getAttention().LockonTruth()) {
        return this == (daNpc_Ls1_c*) dComIfGp_getAttention().ActionTarget(0);
    } else {
        return this == (daNpc_Ls1_c*) dComIfGp_getAttention().LockonTarget(0);
    }
}

/* 000024E4-0000253C       .text setAttention__11daNpc_Ls1_cFb */
void daNpc_Ls1_c::setAttention(bool param_1) {
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_HIO.field_0x0C.field_0x14,
        current.pos.z
    );

    if (field_0x80C == 0 && !param_1) {
        return;
    }

    eyePos.set(
        field_0x7B4.x,
        field_0x7B4.y,
        field_0x7B4.z
    );
}

/* 0000253C-00002670       .text decideType__11daNpc_Ls1_cFi */
bool daNpc_Ls1_c::decideType(int param_1) {
    /* Apparent match, stringBase offsets issue */
    if (field_0x854 > 0) {
        return true;
    }

    field_0x854 = 1;
    field_0x855 = -1;

    switch (param_1) {
        case 0:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
                field_0x855 = 0;
            }    
            break;
        case 1:
            field_0x855 = 1;
            break;
        case 2:
            field_0x855 = 2;
            break;
        case 3:
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
                field_0x855 = 3;
            }
            break;
        case 4:
            field_0x855 = 4;
            break;
    }
    
    if (field_0x855 < 0) {
        return 0;
    }

    strcpy(field_0x6E0, "Ls");
    bool result = false;
    if (field_0x854 != -1 && field_0x855 != -1) {
        result = true;
    }
    
    return result;
}

/* 00002670-00002724       .text cut_init_LOK_PLYER__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_LOK_PLYER(int param_1) {
    /* Apparent match */
    int* prm_p = (int*)dComIfGp_evmng_getMyIntegerP(param_1, "prm_0");
    int prm = 0;

    field_0x853 = 1;
    field_0x840 = 0;

    m_jnt.offBackBoneLock();
    m_jnt.offHeadLock();

    if (prm_p) {
        prm = *prm_p;
    }

    if (cLib_checkBit<int>(prm, 1 << 3) != 0) {
        m_jnt.setTrn();
    } else {
        if (cLib_checkBit<int>(prm, 1)) {
            field_0x840 = 1;
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
BOOL daNpc_Ls1_c::cut_move_LOK_PLYER() {
    return TRUE;
}

/* 0000272C-00002760       .text cut_init_PLYER_MOV__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_PLYER_MOV(int param_1) {
    UNUSED(param_1);
    dComIfGp_evmng_setGoal(&field_0x7CC[1]);
}

/* 00002760-00002768       .text cut_move_PLYER_MOV__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::cut_move_PLYER_MOV() {
    return TRUE;
}

/* 00002768-0000276C       .text cut_init_WAI__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_WAI(int param_1) {
    UNUSED(param_1);
}

/* 0000276C-000027C0       .text cut_move_WAI__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::cut_move_WAI() {
    if (field_0x84F != 1) {
        return TRUE;
    }
    
    if (field_0x830 != 0) {
        setAnm_NUM(0, 1);
        return TRUE;
    }
        
    return FALSE;
}

/* 000027C0-00002828       .text cut_init_ANM_CHG__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::cut_init_ANM_CHG(int param_1) {
    /* Apparent match */   
    int* anm_no_p = (int*)dComIfGp_evmng_getMyIntegerP(param_1, "AnmNo");
    int anm_no = field_0x84F;

    if (anm_no_p) {
        anm_no = *anm_no_p;
    }

    setAnm_NUM(anm_no, 1);
}

/* 00002828-00002830       .text cut_move_ANM_CHG__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::cut_move_ANM_CHG() {
    return TRUE;
}

/* 00002830-000029B0       .text privateCut__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::privateCut(int) {
    /* Nonmatching */
    static const char* a_cut_tbl[] = {
        "LOK_PLYER",
        "PLYER_MOV",
        "WAI",
        "ANM_CHG"
    };
}

/* 000029B0-000029D4       .text endEvent__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::endEvent() {
    dComIfGp_event_reset();
    field_0x84B = 0xFF;
    field_0x84C = 0xFF;
}

/* 000029D4-00002A0C       .text isEventEntry__11daNpc_Ls1_cFv */
int daNpc_Ls1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00002A0C-00002BD0       .text event_proc__11daNpc_Ls1_cFi */
void daNpc_Ls1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00002BD0-00002C7C       .text set_action__11daNpc_Ls1_cFM11daNpc_Ls1_cFPCvPvPv_iPv */
BOOL daNpc_Ls1_c::set_action(ProcFunc param_1, void* param_2) {
    if (field_0x720 != param_1) {
        if (field_0x720) {
            field_0x856 = 9;
            (this->*field_0x720)(param_2);
        }
        field_0x720 = param_1;
        field_0x856 = 0;
        (this->*field_0x720)(param_2);
    }
    return TRUE;
}

/* 00002C7C-00002D70       .text setStt__11daNpc_Ls1_cFSc */
void daNpc_Ls1_c::setStt(s8 param_1) {
    u8 prev_0x851 = field_0x851;
    field_0x851 = param_1;
    switch (field_0x851) {
        case 1:
            field_0x850 = 0;
            field_0x826 = cLib_getRndValue(0x3C, 0x5A);
            break;
        case 2:
            field_0x850 = 0;
            field_0x833 = 0;
            field_0x822 = 0;
            break;
        case 3:
            field_0x850 = 0;
            break;
        case 4:
            field_0x850 = 0;
            field_0x6D4 = 1.0f;
            break;
        case 5:
            fpcEx_Search(searchActor_kamome_Set_NOSTOP_DEMO, this);
            field_0x850 = 0;
            field_0x84B = 0xFF;
            field_0x84C = 0xFF;
            field_0x857 = 0;
            field_0x852 = prev_0x851;
            break;
    }
    setAnm();
}

/* 00002D70-00002EF8       .text chk_areaIN__11daNpc_Ls1_cFffs4cXyz */
bool daNpc_Ls1_c::chk_areaIN(float, float, short, cXyz) {
    /* Nonmatching */
}

/* 00002EF8-00002FD8       .text get_playerEvnPos__11daNpc_Ls1_cFi */
cXyz daNpc_Ls1_c::get_playerEvnPos(int param_2) {
    /* Apparent match */
    const Vec pos[] = {
        { 200.0f, 0.0f, -200.0f },
        { 100.0f, 0.0f,  -80.0f }
    };

    cXyz sp14;
    cXyz sp08;

    sp14 = pos[param_2]; 
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&pos[param_2], &sp08);
    return sp08;
}

/* 00002FD8-00003154       .text chkTelescope_sph__11daNpc_Ls1_cF4cXyzff */
void daNpc_Ls1_c::chkTelescope_sph(cXyz, float, float) {
    /* Nonmatching */
}

/* 00003154-00003258       .text chkTelescope__11daNpc_Ls1_cF4cXyzff */
BOOL daNpc_Ls1_c::chkTelescope(cXyz param_1, float param_2, float param_3) {
    /* Apparent match */
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

    BOOL result = FALSE;
    if (fabs(sp08.x) < param_2 && (sp08.z > param_3)) {
        result = TRUE;
    }

    return result;
}

/* 00003258-000036B0       .text telescope_proc__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::telescope_proc() {
    /* Nonmatching */
}

/* 000036B0-000037A4       .text wait_1__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::wait_1() {
    if (field_0x850 < 3) {
        field_0x850 = 0;
        if (chk_areaIN(l_HIO.field_0x0C.field_0x20, 100.0f, 0x7FFF, current.pos)) {
            field_0x850 = 4;
        }
    }
    
    field_0x853 = 0;
    
    if (field_0x84F == 0) {
        if (cLib_calcTimer(&field_0x826) == 0) {
            setAnm_NUM(1, 1);
        }
        return true;
    }
    
    if (field_0x830 != 0) {
        field_0x826 = cLib_getRndValue(0x3C, 0x5A);
        setAnm_NUM(0, 1);
    }

    return true;
}

/* 000037A4-00003A0C       .text wait_2__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::wait_2() {
    /* Nonmatching */
}

/* 00003A0C-00003B24       .text wait_3__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::wait_3() {
    /* Nonmatching */
}

/* 00003B24-00003BE4       .text wait_4__11daNpc_Ls1_cFv */
bool daNpc_Ls1_c::wait_4() {
    /* Nonmatching */
    if (field_0x83F != 0) {
        if (chk_talk()) {
            setStt(5);
            field_0x853 = 1;
            field_0x840 = 0;
            m_jnt.setTrn();
        }
        return true;
    } 

    field_0x850 = 2;
    field_0x840 = 1;

    if (field_0x83E != 0) {
        field_0x824 = cLib_getRndValue(0xF, 0x1E);
    }

    if (cLib_calcTimer(&field_0x824) != 0) {
        field_0x853 = 1;
        return true;
    } 

    field_0x853 = 0;

    return true;
}

/* 00003BE4-00003CD8       .text talk_1__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::talk_1() {
    /* Nonmatching */
    BOOL res = chk_parts_notMov();
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg == NULL) {
        return res;
    }
    switch (mpCurrMsg->mStatus) {
    case 2:
    case 6:
        break;
    case 19:
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
        field_0x832 = 0xff;
        field_0x83F = 0;
        setStt(field_0x852);
        field_0x824 = cLib_getRndValue(0xF, 0x1E);
        endEvent();
        break;  
    }
    return res;
}

/* 00003CD8-00003EA8       .text wait_action1__11daNpc_Ls1_cFPv */
BOOL daNpc_Ls1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00003EA8-00003F30       .text demo_action1__11daNpc_Ls1_cFPv */
BOOL daNpc_Ls1_c::demo_action1(void* param_1) {
    UNUSED(param_1);
    switch (field_0x856) {
        case 0:
            if (field_0x855 == 1) {
                setAnm_NUM(0xC, 1);
            } else {
                setAnm_NUM(5, 1);
            }
            field_0x856++;
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
    /* Nonmatching */
}

/* 000041B8-00004288       .text shadowDraw__11daNpc_Ls1_cFv */
void daNpc_Ls1_c::shadowDraw() {
    /* Apparent match */
    cXyz pos(
        current.pos.x,
        current.pos.y + 150.0f,
        current.pos.z
    );

    field_0x6E4 = dComIfGd_setShadow(
        field_0x6E4, 1, 
        mpMorf->getModel(), &pos, 
        800.0f, 40.0f, 
        current.pos.y, mObjAcch.GetGroundH(), 
        mObjAcch.m_gnd, &tevStr
    );

    if (field_0x6E4 != 0) {
        if (field_0x6D0) {
            dComIfGd_addRealShadow(field_0x6E4, field_0x6D0);
        }
        dComIfGd_addRealShadow(field_0x6E4, field_0x6E8);
    }
}

/* 00004288-00004418       .text _draw__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::_draw() {
    /* Apparent match */
    J3DModel* model_p = field_0x6E8;
    J3DModel* morf_model_p = mpMorf->getModel();
    J3DModelData* morf_model_info_p = morf_model_p->getModelData();

    if (field_0x83A != 0 || field_0x83C != 0) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);
    g_env_light.setLightTevColorType(model_p, &tevStr);

    field_0x708.entry(morf_model_info_p, field_0x71C);
    field_0x6F0.entry(morf_model_info_p, (f32)field_0x704);
    mpMorf->entryDL(); 

    field_0x6F0.remove(morf_model_info_p);
    field_0x708.remove(morf_model_info_p);

    mDoExt_modelEntryDL(model_p);

    if (field_0x6D0) {
        g_env_light.setLightTevColorType(field_0x6D0, &tevStr);
        mDoExt_modelEntryDL(field_0x6D0);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK49, this, 1.0f, 1.0f, 1.0f);

    // Does nothing
    if (l_HIO.field_0x0C.field_0x18 != 0) {
        cXyz dummy = current.pos;
        dummy.y = dComIfGp_getLinkPlayer()->current.pos.y;
    }

    return TRUE;
}

/* 00004418-00004654       .text _execute__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::_execute() {
    /* Apparent match */
    if (!field_0x83D) {
        field_0x794 = current.pos;
        field_0x7A0 = current.angle;
        field_0x83D = true;
    }
    m_jnt.setParam(
        l_HIO.field_0x0C.field_0x08,
        l_HIO.field_0x0C.field_0x0A,
        l_HIO.field_0x0C.field_0x0C,
        l_HIO.field_0x0C.field_0x0E,
        l_HIO.field_0x0C.field_0x00,
        l_HIO.field_0x0C.field_0x02,
        l_HIO.field_0x0C.field_0x04,
        l_HIO.field_0x0C.field_0x06,
        l_HIO.field_0x0C.field_0x10
    );

    if (field_0x83A != 0 && demoActorID == 0) {
        return TRUE;
    } else {
        partner_search();
        checkOrder();
        if (!demo()) {
            int tmp = -1;
            dBgS* bgs_p = dComIfG_Bgsp();
            if (dComIfGp_event_getMode() != 0 && !eventInfo.checkCommandTalk()) {
                tmp = isEventEntry();
            }

            if (tmp >= 0 || field_0x834 != 0) {
                event_proc(tmp);
            } else {
                (this->*field_0x720)(NULL);
            }

            lookBack();

            if (field_0x855 != 0) {
                fopAcM_posMoveF(this, mStts.GetCCMoveP());
                mObjAcch.CrrPos(*bgs_p);
            }

            play_animation();
        } else {
            field_0x83A = 0;
        }

        eventOrder();
        field_0x7A6 = current.angle;
        if (field_0x83B == 0) {
            shape_angle = current.angle;
        }

        tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
        setMtx(false);

        if (field_0x841 == 0) {
            setCollision(40.0f, 100.0f);
        }
    }

    return TRUE;
}

/* 00004654-000046A8       .text _delete__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::_delete() {
    dComIfG_resDelete(&field_0x6C4, field_0x6E0);

    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }

    return TRUE;
}

/* 000046A8-000047D4       .text _create__11daNpc_Ls1_cFv */
cPhs_State daNpc_Ls1_c::_create() {
    /* Apparent match */
    static int a_siz_tbl[] = {
        0,
        0
    };

    cPhs_State state;
    fopAcM_SetupActor(this, daNpc_Ls1_c);

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&field_0x6C4, field_0x6E0);
    field_0x837 = state == cPhs_COMPLEATE_e;
    if (!field_0x837) {
        return state;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[field_0x854])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, this->mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0f, -20.0f, -50.0f, 50.0f, 140.0f, 50.0f);

    if (createInit() == 0) {
        return cPhs_ERROR_e;
    }

    return state;
}

daNpc_Ls1_c::daNpc_Ls1_c() {}

/* 00004C98-00005250       .text bodyCreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::bodyCreateHeap() {
    /* Apparent match */
    J3DModelData* a_mdl_dat = (J3DModelData*) dComIfG_getObjectIDRes(field_0x6E0, LS_BDL_LS);
    JUT_ASSERT(0xBC9, a_mdl_dat != NULL);

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

    if (field_0x855 == 4 || dComIfGs_getClearCount() != 0) {
        ResTIMG* tex_info_p = (ResTIMG*) dComIfG_getObjectIDRes(field_0x6E0, LS_BTI_LSBODY02);
        
        J3DTexture* a_texture = a_mdl_dat->getTexture();
        JUT_ASSERT(0xBE7, a_texture != NULL);
        
        JUTNameTab* a_textureName = a_mdl_dat->getTextureName();
        JUT_ASSERT(0xBE9, a_textureName != NULL);

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
    JUT_ASSERT(0xBFA, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0xBFC, m_bbone_jnt_num >= 0);

    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(0xBFE, m_hnd_L_jnt_num >= 0);

    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(0xC00, m_hnd_R_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hnd_L_jnt_num)->setCallBack(nodeCB_Hand_L);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hnd_R_jnt_num)->setCallBack(nodeCB_Hand_R);
    mpMorf->getModel()->setUserArea((u32)this);
    
    return TRUE;
}

/* 00005250-00005428       .text handCreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::handCreateHeap() {
    /* Apparent match */
    field_0x6E8 = NULL;
    J3DModelData* a_mdl_dat = (J3DModelData*) dComIfG_getObjectIDRes(field_0x6E0, LS_BDL_LSHAND);
    JUT_ASSERT(0xC1F, a_mdl_dat != NULL);
    field_0x6E8 = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);

    if (!field_0x6E8) {
        return FALSE;
    }

    m_lsHnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("ls_handL");
    JUT_ASSERT(0xC27, m_lsHnd_L_jnt_num >= 0);

    m_lsHnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("ls_handR");
    JUT_ASSERT(0xC29, m_lsHnd_R_jnt_num >= 0);

    field_0x6E8->getModelData()->getJointNodePointer(m_lsHnd_L_jnt_num)->setCallBack(Ls_hand_nodeCB_Hand_L);
    field_0x6E8->getModelData()->getJointNodePointer(m_lsHnd_R_jnt_num)->setCallBack(Ls_hand_nodeCB_Hand_R);
    field_0x6E8->setUserArea((u32)this);
    return TRUE;
}

/* 00005428-000054F8       .text itemCreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::itemCreateHeap() {
    /* Apparent match */
    field_0x6D0 = NULL;

    J3DModelData* a_mdl_dat = (J3DModelData *) dComIfG_getObjectRes("Link", LINK_BDL_TELESCOPE);
    JUT_ASSERT(0xC43, a_mdl_dat != NULL);
    
    field_0x6D0 = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    
    if (!field_0x6D0) {
        return FALSE;
    }
    
    return TRUE;
}

/* 000054F8-000055BC       .text CreateHeap__11daNpc_Ls1_cFv */
BOOL daNpc_Ls1_c::CreateHeap() {
    /* Apparent match */
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
    mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, NULL, NULL);

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
