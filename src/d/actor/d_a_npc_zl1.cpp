/**
 * d_a_npc_zl1.cpp
 * NPC - Tetra
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_zl1.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_branch.h"
#include "d/d_bg_s_func.h"
#include "d/d_bg_s_roof_chk.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/actor/d_a_player.h"
#include "d/res/res_zl.h"
#include "d/d_snap.h"


extern dCcD_SrcCyl dNpc_cyl_src;

class daNpc_Zl1_HIO_c : public mDoHIO_entry_c{
public:
struct hio_prm_c {
        s16 mMaxHeadX;
        s16 mMaxHeadY;
        s16 mMinHeadX;
        s16 mMinHeadY;
        s16 mMaxBackboneX;
        s16 mMaxBackboneY;
        s16 mMinBackboneX;
        s16 mMinBackboneY;
        s16 mMaxTurnStep;
        s16 field_18;
        f32 field_1C;
        u8 field_20;
        u8 field_21;
        u8 field_22;
        u8 field_23;
        f32 field_24;
        f32 field_28;
        s16 field_2C;
        s16 field_2E;
        s16 field_30;
        s16 field_32;
        f32 field_34;
        f32 field_38;
        f32 field_3C;
        f32 field_40;
        f32 field_44;
        f32 field_48;
        f32 field_4C;
        f32 field_50;
        f32 field_54;
        f32 field_58;
        s16 field_5C;
        s16 field_5E;
    };  // Size: 0x58

    daNpc_Zl1_HIO_c();
    virtual ~daNpc_Zl1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
    /* Place member variables here */
};

static daNpc_Zl1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];

static int l_check_wrk;

static char l_BCKName[30];

static char l_BTPName[30];

static char l_BTKName[30];



/* 000000EC-00000150       .text __ct__15daNpc_Zl1_HIO_cFv */
daNpc_Zl1_HIO_c::daNpc_Zl1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        0x18E2,
        0x2328,
        0xE71E,
        0xDCD8,
        0x0BB8,
        0x03E8,
        0xF8E4,
        0xFC18,
        0x1000,
        0x0800,
        140.0f,
        0,
        0,
        0,
        0,
        200.0f,
        200.0f,
        0x0028,
        0x0014,
        0x0000,
        0x003C,
        130.0f,
        0.04f,
        10.0f,
        0.0f,
        1.0f,
        1.0f,
        200.0f,
        0.25f,
        25.0f,
        10.0f,
        0x0180,
        0x1388
    };
    memcpy(&mPrmTbl,&a_prm_tbl,0x58);
    mNo = -1;
    field_0x8 = -1;
}

static const char* l_evn_tbl[4] = {
    "yuukaigo",
    "ooi",
    "majyuu_shinnyuu",
    "nakaniwa"
};

/* 00000198-000001F8       .text __ct__18daNpc_Zl1_matAnm_cFv */
daNpc_Zl1_matAnm_c::daNpc_Zl1_matAnm_c() {
    field_0x7C = false;
    mOffset.y = 0.0f;
    mOffset.x = 0.0f;
}

/* 000001F8-0000028C       .text calc__18daNpc_Zl1_matAnm_cCFP11J3DMaterial */
void daNpc_Zl1_matAnm_c::calc(J3DMaterial* mat) const {
    J3DMaterialAnm::calc(mat);

    for(u32 i = 0; i < 8; i++) {
        if(getTexMtxAnm(i)) {
            J3DTextureSRTInfo& srt = mat->getTexMtx(i)->getTexMtxInfo().mSRT;
            if(field_0x7C) {
                srt.mTranslationX = mOffset.x;
                srt.mTranslationY = mOffset.y;
            }
        }
    }

}

/* 0000028C-000002D8       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Zl1_c* actor = (daNpc_Zl1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_Head(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000002D8-00000400       .text _nodeCB_Head__11daNpc_Zl1_cFP7J3DNodeP8J3DModel */
void daNpc_Zl1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {
    static cXyz a_eye_pos_off(20.0f, -16.0f, 0.0f);

    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));

    mDoMtx_stack_c::multVecZero(&field_0x770);
    mDoMtx_stack_c::YrotM(-field_0x83C);
    mDoMtx_stack_c::ZrotM(-field_0x83E);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &field_0x74C);

    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);

    MtxP mtx = mDoMtx_stack_c::get();
    MTXCopy(mtx, i_pModel->getAnmMtx(jointIdx));
}

/* 0000043C-00000488       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Zl1_c* actor = (daNpc_Zl1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_BackBone(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000488-00000528       .text _nodeCB_BackBone__11daNpc_Zl1_cFP7J3DNodeP8J3DModel */
void daNpc_Zl1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {
    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    MtxP mtx = mDoMtx_stack_c::get();
    MTXCopy(mtx, i_pModel->getAnmMtx(jointIdx));
}

/* 00000528-00000548       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* ac) {
    return ((daNpc_Zl1_c*)ac)->CreateHeap();
}

/* 00000548-000005C0       .text searchActor_Branch__FPvPv */
void* searchActor_Branch(void* i_param1, void*) {
    if(l_check_wrk < 20 && fopAcM_IsActor(i_param1) && fopAcM_GetName(i_param1) == PROC_BRANCH) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param1;
        l_check_wrk++;
    }
    return NULL;
}

/* 000005C0-00000638       .text searchActor_Bm1__FPvPv */
void* searchActor_Bm1(void* i_param1, void*) {
    if(l_check_wrk < 20 && fopAcM_IsActor(i_param1) && fopAcM_GetName(i_param1) == PROC_NPC_BM1) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param1;
        l_check_wrk++;
    }
    return NULL;
}

/* 00000638-00000824       .text set_startPos__11daNpc_Zl1_cFi */
BOOL daNpc_Zl1_c::set_startPos(int param_1) {
    static const Vec a_chk_playerPos[][3] = {
        {
            {0.0f, -1145.0f, -4005.0f},
            {0.0f, -2099.0f, 3913.0f},
            {0.0f, -1145.0f, -3542.0f}
        },
        {
            {-4.0f, 0.0f, 2695.0f},
            {0.0f, 149.0f, -955.0f},
            {0.0f, -1997.0f, -7758.0f}
        }
    };

    static const Vec a_set_tetoraPos[][3] = {
        {
            {-75.0f, -1146.0f, -4160.0f},
            {80.0f, -2100.0f, 4193.0f},
            {-75.0f, -1146.0f, -3700.0f}
        },
        {
            {92.0f, 0.0f, 2842.0f},
            {-129.0f, 149.0f, -1132.0f},
            {107.0f, -1978.0f, -7559.0f}
        }
    };

    static const f32 a_set_tetoraAng[2][3] = {
        {16.0f, -171.0f, 16.0f},
        {-159.0f, 15.0f, -153.0f}
    };

    int temp2;
    f32 temp = G_CM3D_F_INF;
    if(param_1 == 0 || param_1 == 1) {
        cXyz diff;
        cXyz chkPlayerPos;
        for(int i = 0; i < 3; i++) {
            chkPlayerPos = a_chk_playerPos[param_1][i];
            diff = chkPlayerPos - dComIfGp_getPlayer(0)->current.pos;
            f32 absDiff = cXyz(diff.x, 0.0f, diff.z).abs();
            if(temp > absDiff) {
                temp = absDiff;
                temp2 = i;
            }
        }
        if(temp2 < 3) {
            current.pos = a_set_tetoraPos[param_1][temp2];
            current.angle.y = cM_deg2s(a_set_tetoraAng[param_1][temp2]);
            mObjAcch.SetOld();
        }
    }
    return TRUE;
}

/* 00000824-000008B8       .text init_ZL1_0__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_0() {
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
        set_action(&daNpc_Zl1_c::demo_action1, NULL);
#if VERSION != VERSION_DEMO
        fopAcM_ClearStatusMap(this);
#endif
        field_0x7D2 = true;
        return true;
    }
    return false;
}

/* 000008B8-0000094C       .text init_ZL1_1__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_1() {
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0101)) {
        set_action(&daNpc_Zl1_c::demo_action1, NULL);
        fopAcM_OffStatus(this, fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e);
        field_0x7CE = true;
        return true;
    }
    return false;
}

/* 0000094C-000009EC       .text init_ZL1_2__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_2() {
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2401)) {
        set_action(&daNpc_Zl1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* 000009EC-00000AE4       .text init_ZL1_3__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_3() {
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0801)) {
        cXyz temp(-123.0f, 0.0f, -100.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        mDoMtx_stack_c::multVec(&temp, &field_0x764);
        field_0x764.y = 400.0f;
        set_action(&daNpc_Zl1_c::demo_action2, NULL);
        fopAcM_OffStatus(this, fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e);
        return true;
    }
    return false;
}

/* 00000AE4-00000B48       .text init_ZL1_4__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_4() {
    set_action(&daNpc_Zl1_c::wait_action1, NULL);
    fopAcM_OffStatus(this, fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e);
    return true;
}

/* 00000B48-00000CC0       .text init_ZL1_5__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_5() {
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D02)) {
        set_action(&daNpc_Zl1_c::optn_action1, NULL);
        fopAcM_OffStatus(this, fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e);
#if VERSION != VERSION_DEMO
        if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3804)) {
            fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
            field_0x84A = 6;
            mEventIdx[4] = field_0x84A + -3;
            fopAcM_orderOtherEventId(this, mEventIdx[mEventIdx[4]]);
            dComIfGp_evmng_cancelStartDemo();
        } else {
#endif
            if(!strcmp(dComIfGp_getStartStageName(), "Hyrule")) {
                set_startPos(1);
            }
            if(!strcmp(dComIfGp_getStartStageName(), "Hyroom")) {
                set_startPos(0);
            }
#if VERSION != VERSION_DEMO
        }
#endif

        gravity = -4.5f;
        return true;
    }
    return false;
}

/* 00000CC0-00000D24       .text init_ZL1_6__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_6() {
    set_action(&daNpc_Zl1_c::demo_action1, NULL);
#if VERSION != VERSION_DEMO
    fopAcM_ClearStatusMap(this);
#endif
    return true;
}

/* 00000D24-00000D88       .text init_ZL1_7__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::init_ZL1_7() {
    set_action(&daNpc_Zl1_c::demo_action1, NULL);
#if VERSION != VERSION_DEMO
    fopAcM_ClearStatusMap(this);
#endif
    return true;
}

/* 00000D88-00000FB0       .text createInit__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::createInit() {
    bool ret;
    int temp = 0xff;
    for(int i = 0; i < 4; i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xff);
    }
    mEventCut.setActorInfo2("Zl1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    switch(field_0x84F) {
        case 6:
        case 7:
            break;
    }
    
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    field_0x7BC = -1;
    gravity = 0.0f;
    field_0x849 = 0x11;


    switch(field_0x84F) {
        case 0:
            ret = init_ZL1_0();
            break;
        case 1:
            ret = init_ZL1_1();
            break;
        case 2:
            ret = init_ZL1_2();
            break;
        case 3:
            ret = init_ZL1_3();
            break;
        case 4:
            ret = init_ZL1_4();
            break;
        case 5:
            ret = init_ZL1_5();
            temp = 0x8C;
            break;
        case 6:
            ret = init_ZL1_6();
            break;
        case 7:
            ret = init_ZL1_7();
            break;
        default:
            ret = false;
            break;
    }

    if(!ret) {
        return false;
    }

    field_0x73E = current.angle;
    shape_angle = field_0x73E;
    mStts.Init(temp, 0xff, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    play_animation();
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 00000FB0-000010F4       .text play_animation__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::play_animation() {
    u32 mtrlSnd = 0;
    if(field_0x848 == 1 && field_0x7D0 == true) {
        setEyeCtrl();
    } else {
        clrEyeCtrl();
    }
    play_btp_anm();
    play_btk_anm();
    if(mObjAcch.ChkGroundHit()) {
        mtrlSnd = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    field_0x7C3 = mpMorf->play(&eyePos, mtrlSnd, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    if(mpMorf->getFrame() < mFrame) {
        field_0x7C3 = 1;
    }
    mFrame = mpMorf->getFrame();

    switch(field_0x847) {
        case 0xD:
        case 0xE:
            mBtpAnmFrame = mpMorf->getFrame();
            break;
        default:
            break;
    }

    switch(field_0x848) {
        case 6:
        case 7:
        case 8:
            mBtkAnmFrame = mpMorf->getFrame();
            break;
        default:
            break;
    }
}

/* 000010F4-000011EC       .text swoon_OnShip__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::swoon_OnShip() {
    daShip_c* pShip = dComIfGp_getShipActor();
    csXyz angle;
    if(pShip != NULL) {
        cXyz pos(-23.88f, 58.66f, -12.44f);
        angle.set(0x471C, 0x156, 0x4147);
        mDoMtx_stack_c::copy(pShip->getBodyMtx());

        mDoMtx_stack_c::transM(pos.x, pos.y, pos.z);
        mDoMtx_stack_c::XYZrotM(angle.x, angle.y, angle.z);

        MtxP pMtx = mDoMtx_stack_c::get();
        current.pos.set(pMtx[0][3], pMtx[1][3], pMtx[2][3]);
        current.angle.y = pShip->shape_angle.y - (s16)0x8000;
        return true;
    }
    return false;
}

/* 000011EC-000013A0       .text setMtx__11daNpc_Zl1_cFb */
void daNpc_Zl1_c::setMtx(bool param_1) {

    bool temp = false;
    int temp2;
    daBranch_c* actor;

    mpMorf->getModel()->setBaseScale(scale);

    if(field_0x7CE) {
#if VERSION != VERSION_DEMO
        if(!fpcM_IsCreating(mProcId1)) {
            if(mProcId1 != 0xffffffff) {
                if(fopAcM_SearchByID(mProcId1, (fopAc_ac_c **)&actor) == 1) {
                    if(actor != NULL) {
                        temp = true;
                        mDoMtx_stack_c::copy(actor->getJointMtx("wood2"));
                        mDoMtx_stack_c::transM(120.28999f, -88.36f, -19.130001f);
                    }
                }
            }
        }
#else
        actor = (daBranch_c*)searchByID(mProcId1, &temp2);
        if(actor != NULL) {
            if(temp2 == 0) {
            temp = true;
            mDoMtx_stack_c::copy(actor->getJointMtx("wood2"));
            mDoMtx_stack_c::transM(120.28999f, -88.36f, -19.130001f);
            }
        }
#endif
    } else if(field_0x7CA) {
        temp = swoon_OnShip();
    }

    if(!temp) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(field_0x73E);
    }
    
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    if(mpModel != NULL) {
        mpModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_bbone_jnt_num));
        mpModel->calc();
    }

    if(!field_0x7D9) {
        setWaterRipple();
        setEff();
    }
    setAttention(param_1);
}

/* 000013A0-000013F0       .text bckResID__11daNpc_Zl1_cFi */
char* daNpc_Zl1_c::bckResID(int param_1) {
    static const char* a_BCKName_tbl[] = {
        "wait",
        "wait02",
        "talk01",
        "talk02",
        "talk03",
        "fall",
        "hang",
        "hang_mov",
        "wait03",
        "walk",
        "land",
        "run",
        "look",
        "swoon",
        "wake",
        "wait04",
        "wait05"
    };
    strcpy(l_BCKName, a_BCKName_tbl[param_1]);
    return strcat(l_BCKName, ".bck");
}

/* 000013F0-00001440       .text btpResID__11daNpc_Zl1_cFi */
char* daNpc_Zl1_c::btpResID(int param_1) {
    static const char* a_BTPName_tbl[] = {
        "hang",
        "maba_a",
        "zl_t01",
        "zl_t02",
        "zl_t03",
        "zl_t04",
        "zl_t05",
        "zl_t06",
        "fall",
        "hang_m1",
        "hang_m2",
        "hang_m3",
        "maba_a",
        "swoon",
        "wake",
        "zl_t07",
        "zl_t08"
    };

    strcpy(l_BTPName, a_BTPName_tbl[param_1]);
    return strcat(l_BTPName, ".btp");
}

/* 00001440-00001490       .text btkResID__11daNpc_Zl1_cFi */
char* daNpc_Zl1_c::btkResID(int param_1) {
    static const char* a_BTKName_tbl[] = {
        "center",
        "maba_a",
        "zl_st01",
        "zl_st02",
        "hang_m2",
        "hang_m3",
        "look",
        "swoon",
        "wake",
        "zl_t07"
    };

    strcpy(l_BTKName, a_BTKName_tbl[param_1]);
    return strcat(l_BTKName, ".btk");

}

/* 00001490-00001590       .text setBtp__11daNpc_Zl1_cFScb */
bool daNpc_Zl1_c::setBtp(s8 param_1, bool param_2) {
    J3DModel* model = mpMorf->getModel();

    if(param_1 < 0) {
        return false;
    }
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern *)dComIfG_getObjectRes(mArcName, btpResID(param_1));
    JUT_ASSERT(VERSION_SELECT(0x38A, 0x39C, 0x39C, 0x39C), a_btp != NULL);

    field_0x847 = param_1;
    mBtpAnmFrame = 0;
    mTimer = 0;
    return mBtpAnm.init(model->getModelData(), a_btp, 1, 0, 1.0f, 0, -1, param_2, 0) != 0;
}

/* 00001590-00001610       .text setMat__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::setMat() {
    J3DModel* model = mpMorf->getModel();
    u16 materialNum = mBtkAnm.getBtkAnm()->getUpdateMaterialNum();
    for (u16 i = 0; i < materialNum; i++) {
        u16 materialID = mBtkAnm.getBtkAnm()->getUpdateMaterialID(i);
        field_0x6D4[i] = (daNpc_Zl1_matAnm_c *)model->getModelData()->getMaterialNodePointer(materialID)->getMaterialAnm();
    }
}

/* 00001610-00001728       .text setBtk__11daNpc_Zl1_cFScb */
bool daNpc_Zl1_c::setBtk(s8 param_1, bool param_2) {
        J3DModel* model = mpMorf->getModel();

    if(param_1 < 0) {
        return false;
    }
    J3DAnmTextureSRTKey* a_btk = (J3DAnmTextureSRTKey *)dComIfG_getObjectRes(mArcName, btkResID(param_1));
    JUT_ASSERT(VERSION_SELECT(0x3B3, 0x3C5, 0x3C5, 0x3C5), a_btk != NULL);

    field_0x848 = param_1;
    mBtkAnmFrame = 0;
    if(mBtkAnm.init(model->getModelData(), a_btk, 1, 0, 1.0f, 0, -1, param_2, 0) != 0) {
        if(!param_2) {
            setMat();
        }
        return true;

    }
    return false;

}

/* 00001728-00001794       .text init_texPttrnAnm__11daNpc_Zl1_cFScb */
bool daNpc_Zl1_c::init_texPttrnAnm(s8 param_1, bool param_2) {
    static const s8 a_btk_num_tbl[] = {
        0, 1, 2, 1, 1, 1, 3, 1, 0, 0, 4, 5, 6, 7, 8, 9, 1
    };
    
    if(setBtp(param_1, param_2) == false) {
        return false;

    } else {
        return setBtk(a_btk_num_tbl[param_1], param_2);
    }
}

/* 00001794-00001830       .text play_btp_anm__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::play_btp_anm() {
    u16 frame = mBtpAnm.getBtpAnm()->getFrameMax() & 0xff;
    if(field_0x847 != 1 || cLib_calcTimer(&mTimer) == 0) {
        mBtpAnmFrame ++;
        if((u16)mBtpAnmFrame >= frame) {
            if(field_0x847 != 1) {
                mBtpAnmFrame = frame;
            } else {
                mTimer = cLib_getRndValue(0x3C, 0x5A);
                mBtpAnmFrame = 0;
            }
        }
    }
}

/* 00001830-000019EC       .text eye_ctrl__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::eye_ctrl() {
    f32 temp;
    f32 temp2;
    f32 temp3;
#if VERSION != VERSION_DEMO
    if(field_0x7D1) {
        temp = field_0x842 / (f32)(l_HIO.mPrmTbl.field_5E);
        temp2 = field_0x840 / (f32)(l_HIO.mPrmTbl.field_5E);
        temp = temp * 0.1f;
        temp2 = temp2 * 0.1f;
        
        temp = cLib_minMaxLimit(temp, -1.0f, 1.0f);
        temp2 = cLib_minMaxLimit(temp2, -1.0f, 1.0f);

    } else {
        temp = 0.0f;
        temp2 = temp;
    }
#else
    if(field_0x7D1) {
        temp = field_0x842 / (f32)(l_HIO.mPrmTbl.field_5E);
        temp2 = field_0x840 / (f32)(l_HIO.mPrmTbl.field_5E);
        temp3 = -1.0f;
        f32 temp4 = 1.0f;
        temp = 0.1f * temp;
        temp2 = 0.1f * temp2;
        temp = cLib_minMaxLimit(temp, temp3, temp4);
        
        temp2 = cLib_minMaxLimit(temp2, temp3, temp4);

    } else {
        temp = 0.0f;
        temp2 = temp;
    }
#endif


    if(field_0x6D4[0] != NULL) {
        cLib_addCalc(&field_0x6D4[0]->getNowOffsetX(), temp2, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&field_0x6D4[0]->getNowOffsetY(), temp, 0.5f, 0.1f, 0.03f);
    }
    temp2 *= -1.0f;
    if(field_0x6D4[1] != NULL) {
        cLib_addCalc(&field_0x6D4[1]->getNowOffsetX(), temp2, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&field_0x6D4[1]->getNowOffsetY(), temp, 0.5f, 0.1f, 0.03f);
    }
}

/* 000019EC-00001A44       .text play_btk_anm__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::play_btk_anm() {
    u16 frame = mBtkAnm.getBtkAnm()->getFrameMax() & 0xff;
    if(field_0x7D0) {
        eye_ctrl();
    } else {
        mBtkAnmFrame++;
        if((u16)mBtkAnmFrame >= frame) {
            mBtkAnmFrame = frame;
        }
    }

}

/* 00001A44-00001AE0       .text setAnm_anm__11daNpc_Zl1_cFPQ211daNpc_Zl1_c9anm_prm_c */
void daNpc_Zl1_c::setAnm_anm(daNpc_Zl1_c::anm_prm_c* param_1) {
    s8 temp = param_1->field_0x0;
    if(temp < 0 || field_0x849 == temp) {
        return;
    }
    dNpc_setAnmFNDirect(mpMorf,
        param_1->mLoopMode,
        param_1->mMorf,
        param_1->mPlaySpeed,
        bckResID(temp),
        0,
        mArcName
    );
    field_0x849 = param_1->field_0x0;
    field_0x7C3 = 0;
    field_0x7C4 = 0;
    mFrame = 0.0f;
}

/* 00001AE0-00001B50       .text setAnm_NUM__11daNpc_Zl1_cFii */
void daNpc_Zl1_c::setAnm_NUM(int param_1, int param_2) {
    static daNpc_Zl1_c::anm_prm_c a_anm_prm_tbl[17] = {
        {0, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 8, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {6, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {7, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {8, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {9, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {10, 1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NONE},
        {11, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {12, 12, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {13, 13, 0.0f, 0.0f, J3DFrameCtrl::EMode_NONE},
        {14, 14, 0.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {15, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {16, 15, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    
    if(param_2 != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[param_1].field_0x1, true);
    }
    setAnm_anm(&a_anm_prm_tbl[param_1]);
}

/* 00001B50-00001BBC       .text setAnm__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::setAnm() {
    static daNpc_Zl1_c::anm_prm_c a_anm_prm_tbl[10] = {
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {0, 1, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {8, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {9, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {13, 13, 8.0f, 0.0f, J3DFrameCtrl::EMode_NONE},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {0, 1, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, 1, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, 1, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x84B].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x84B]);
}

/* 00001BBC-00001BC0       .text chngAnmTag__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::chngAnmTag() {
}

/* 00001BC0-00001BC4       .text ctrlAnmTag__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::ctrlAnmTag() {
}

/* 00001BC4-00001DA8       .text chngAnmAtr__11daNpc_Zl1_cFUc */
void daNpc_Zl1_c::chngAnmAtr(u8 param_1) {
    switch(mCurrMsgNo) {
        case 0x15E1:
            m_jnt.onBackBoneLock();
            break;
        case 0x15E2:
        case 0x15ED:
            field_0x84D = 1;
            break;
        case 0x15E3:
            field_0x84D = 5;
            field_0x7BC = 10;
            break;
        case 0x15E4:
            field_0x84D = 1;
            field_0x7BC = -1;
            break;
        case 0x15E7:
            field_0x84D = 2;
            field_0x7D0 = true;
            field_0x758.x = cM_scos(dComIfGp_getPlayer(0)->shape_angle.y) * -20.0f + cM_ssin(dComIfGp_getPlayer(0)->shape_angle.y) * -40.0f + field_0x830.x;

            field_0x758.z = -cM_ssin(dComIfGp_getPlayer(0)->shape_angle.y) * -20.0f + cM_scos(dComIfGp_getPlayer(0)->shape_angle.y) * -40.0f + field_0x830.z;
            field_0x758.y = field_0x830.y;
            break;
        case 0x15EC:
            field_0x84D = 2;
            field_0x7D0 = false;
            field_0x758 = kyoroPos(0xB);
            break;
    }
    if(param_1 == field_0x845 || param_1 > 0x13) {
        return;
    }
    field_0x845 = param_1;
    setAnm_ATR();
    if(field_0x845 == 0xc) {
        mpMorf->setMorf(16.0f);
    }
    
}

/* 00001DA8-00001DB4       .text ctrlAnmAtr__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::ctrlAnmAtr() {
    if(field_0x845 == (s8)19) {
        return;
    }
}

/* 00001DB4-00001E18       .text setAnm_ATR__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::setAnm_ATR() {
    static daNpc_Zl1_c::anm_prm_c a_anm_prm_tbl[19] = {
        {0, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, 2, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 3, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 5, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, 6, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 7, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 7, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {15, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {16, 15, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {15, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {15, 7, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {15, 16, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {8, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {8, 7, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x845].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x845]);
}

/* 00001E18-00001ED4       .text anmAtr__11daNpc_Zl1_cFUs */
void daNpc_Zl1_c::anmAtr(u16 mesgNo) {
    switch(mesgNo) {
        case 6:
            if(field_0x851 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x851++;
            }
            u8 mesgTagInfo = dComIfGp_getMesgAnimeTagInfo();
            if(mesgTagInfo != 0xFF && mesgTagInfo != field_0x846) {
                dComIfGp_clearMesgAnimeTagInfo();
                field_0x846 = mesgTagInfo;
                chngAnmTag();
            }
            break;
        case 0xe:
            field_0x851 = 0;
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00001ED4-00001FA0       .text next_msgStatus__11daNpc_Zl1_cFPUl */
u16 daNpc_Zl1_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;

    switch(*pMsgNo) {
        case 0xCA2:
        case 0xCA3:
            *pMsgNo = 0xC90;
            break;
        case 0xC90: {
            switch(mpCurrMsg->mSelectNum) {
                case 0:
                    ret = fopMsgStts_MSG_ENDS_e;
                    break;
                case 1:
                    *pMsgNo = 0xC91;
                    break;
            }
            break;
        }

        case 0x15E1:
            *pMsgNo = 0x15E2;
            break;

        case 0x15E2:
            *pMsgNo = 0x15E3;
            break;

        case 0x15E3:
            *pMsgNo = 0x15E4;
            break;

        case 0x15E7:
            *pMsgNo = 0x15E8;
            break;

        default:
            ret = fopMsgStts_MSG_ENDS_e;
            break;
    }

    return ret;
}

/* 00001FA0-00001FF0       .text getMsg_ZL1_2__11daNpc_Zl1_cFv */
u32 daNpc_Zl1_c::getMsg_ZL1_2() {
    u32 temp;
    if(dComIfGs_checkCollect(1) != 0) {
        temp = 0xCA2 + (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2908) != 0 ? 1 : 0);
    } else {
        temp = 0xCA1;
    }
    return temp;
}

/* 00001FF0-0000202C       .text getMsg_ZL1_4__11daNpc_Zl1_cFv */
u32 daNpc_Zl1_c::getMsg_ZL1_4() {
    return 0x1005 + (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0810) != 0 ? 1 : 0);
}

/* 0000202C-00002034       .text getMsg_ZL1_5__11daNpc_Zl1_cFv */
u32 daNpc_Zl1_c::getMsg_ZL1_5() {
    return 0x15EE;
}

/* 00002034-000020B0       .text getMsg__11daNpc_Zl1_cFv */
u32 daNpc_Zl1_c::getMsg() {
    u32 msg = 0;
    switch(field_0x84F) {
        case 2:
            msg = getMsg_ZL1_2();
            break;
        case 4:
            msg = getMsg_ZL1_4();
            break;
        case 5:
            msg = getMsg_ZL1_5();
            break;
        case 1:
        case 3:
        case 6:
        case 7:
            break;
    }
    return msg;
}

/* 000020B0-0000213C       .text eventOrder__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::eventOrder() {
    if(field_0x84A == 1 || field_0x84A == 2){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(field_0x84A == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if(field_0x84A >= 3) {
        mEventIdx[4] = field_0x84A - 3;
        fopAcM_orderOtherEventId(this, mEventIdx[mEventIdx[4]]);
    }
}

/* 0000213C-00002280       .text checkOrder__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::checkOrder() {
    static const f32 a_start_pos[] = {-229.76634f, 37.46317f, 305.2134f};
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mEventIdx[mEventIdx[4]]) && field_0x84A >= 3) {
            switch(mEventIdx[4]) {
                case 0:
                    field_0x7D3 = true;
                    break;
                case 2:
                    dComIfGs_setRestartRoom(*(cXyz*)a_start_pos, 0x4000, 0); // fake match probably
                    field_0x7C9 = true;
                    break;
                case 3:
                    daPy_getPlayerActorClass()->onPlayerNoDraw();
#if VERSION != VERSION_DEMO
                    fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
#endif
                    field_0x7D8 = true;
#if VERSION != VERSION_DEMO
                    field_0x79C = 1;
#endif  
                    break;
            }
            field_0x84A = 0;
            field_0x845 = 0xff;
            field_0x846 = 0xff;
        }

    } else if(eventInfo.getCommand() == dEvtCmd_INTALK_e && (field_0x84A == 1 || field_0x84A == 2)) {
        field_0x84A = 0;
        field_0x7D7 = true;
    }
    /* Nonmatching */
}

/* 00002280-00002318       .text chk_talk__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::chk_talk() {
    if(dComIfGp_event_chkTalkXY()) {
        if(dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            return true;
        }
        return false;

    }
    mItemNo = 0xff;
    return true;
}

/* 00002318-00002358       .text chk_parts_notMov__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::chk_parts_notMov() {
    return field_0x794.y != m_jnt.getHead_y() ||
        field_0x794.z != m_jnt.getBackbone_y() ||
        field_0x794.x != current.angle.y;
}

/* 00002358-000023AC       .text searchByID__11daNpc_Zl1_cFUiPi */
fopAc_ac_c* daNpc_Zl1_c::searchByID(fpc_ProcID pid, int* param_2) {
    fopAc_ac_c* actor = NULL;
    *param_2 = 0;
    
    if(!fopAcM_SearchByID(pid, &actor)) {
        *param_2 = 1;
    }
    return actor;
}

/* 000023AC-0000245C       .text partner_search_sub__11daNpc_Zl1_cFPFPvPv_Pv */
bool daNpc_Zl1_c::partner_search_sub(void* (*param_1)(void*, void*)) {
    fpc_ProcID procId;

    bool ret = false;
    mProcId1 = -1;

    l_check_wrk = 0;
    for (s32 i = 0; i < 0x14; i++) {
        l_check_inf[i] = NULL;
    }

    fpcEx_Search(param_1, this);

    if(l_check_wrk != 0) {
        mProcId1 = fopAcM_GetID(l_check_inf[0]);
        ret = true;
    }
    return ret;
}

/* 0000245C-000024F0       .text partner_search__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::partner_search() {
    bool temp;
    if(field_0x850 == 1) {
        switch(field_0x84F) {
            case 1:
                temp = partner_search_sub(searchActor_Branch);
                break;
            case 2:
                temp = partner_search_sub(searchActor_Bm1);
                break;
            case 0:
            case 3:
            default:
                temp = true;
                break;

        }

        if(temp) {
            field_0x850++;
        }
    }
}

/* 000024F0-00002528       .text setEyeCtrl__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::setEyeCtrl() {
    for(int i = 0; i < 2; i++) {
        if(field_0x6D4[i] != NULL){
            field_0x6D4[i]->setMoveFlag();
        }
    }
    field_0x7D1 = true;
}

/* 00002528-00002560       .text clrEyeCtrl__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::clrEyeCtrl() {
    for(int i = 0; i < 2; i++) {
        if(field_0x6D4[i] != NULL){
            field_0x6D4[i]->clrMoveFlag();
        }
    }
    field_0x7D1 = false;
}

/* 00002560-000027CC       .text lookBack__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::lookBack() {
    s8 temp2;
    int temp6;
    cXyz temp3;

    field_0x794.y = m_jnt.getHead_y();
    field_0x794.z = m_jnt.getBackbone_y();
    field_0x794.x = current.angle.y;

    cXyz temp(current.pos);
    temp.y = eyePos.y;

    temp3.set(0.0f, 0.0f, 0.0f);
    
    cXyz* temp4 = NULL;
    s16 targetY = current.angle.y;
    bool temp5 = field_0x7D8;

    temp2 = field_0x84D;

    if(field_0x849 == 0xd || field_0x849 == 0xe) {
        temp2 = 0;
    }

    switch(temp2) {
        case 1:
            field_0x758.set(dNpc_playerEyePos(-20.0f));
            temp3.set(field_0x758);
            temp4 = &temp3;
            field_0x7D0 = true;
            break;
        case 2:
            temp3.set(field_0x758);
            temp4 = &temp3;
            break;
        case 3:
            targetY = field_0x7C0;
            field_0x7D0 = false;
            break;
        case 4:
            fopAc_ac_c* actor = searchByID(mProcId2, &temp6);
            if(actor != NULL && temp6 == 0) {
                field_0x758.set(actor->current.pos);
                field_0x758.y = actor->eyePos.y;
                temp3.set(field_0x758);
                temp4 = &temp3;
                field_0x7D0 = true;
            }
            break;

        case 5:
            kyorokyoro();
            temp3.set(field_0x758);
            temp4 = &temp3;
            field_0x7D0 = true;
            break;
        default:
            field_0x7D0 = false;
            break;
    }
    
    m_jnt.lookAtTarget_2(&current.angle.y, temp4, temp, targetY, l_HIO.mPrmTbl.field_18, temp5);
    field_0x83E = m_jnt.getHead_x()/2;
    field_0x83C = m_jnt.getHead_y()/2;
    field_0x842 = field_0x83E;
    field_0x840 = field_0x83C;
}

/* 000027CC-0000284C       .text chkAttention__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();

    if(attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }

    return this == attention.ActionTarget(0);
}

/* 0000284C-000028A4       .text setAttention__11daNpc_Zl1_cFb */
void daNpc_Zl1_c::setAttention(bool param_1) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrmTbl.field_1C, current.pos.z);

    if(field_0x79C == 0 && !param_1) {
        return;
    }
    eyePos.set(field_0x74C.x, field_0x74C.y, field_0x74C.z);

}

/* 000028A4-000029EC       .text decideType__11daNpc_Zl1_cFi */
bool daNpc_Zl1_c::decideType(int param_1) {
    if(field_0x84E > 0) {
        return true;
    }

    field_0x84E = 1;
    field_0x84F = -1;

    switch(param_1) {
        case 0:
            field_0x84F = 0;
            break;
        case 1:
            field_0x84F = 1;
            break;
        case 2:
            field_0x84F = 2;
            break;
        case 3:
            field_0x84F = 3;
            break;
        case 4:
            field_0x84F = 4;
            break;
        case 5:
            field_0x84F = 5;
            break;
        case 6:
            field_0x84F = 6;
            break;
        case 7:
            field_0x84F = 7;
            break;
        default:
            return false;
    }

    bool ret;
    switch(field_0x84F) {
        case 0:
        case 6:
        case 7:
            strcpy(mArcName, "Zl2");
            break;
        default:
            strcpy(mArcName, "Zl");
            break;
    }
    ret = false;
    if(field_0x84E != -1 && field_0x84F != -1) {
        ret = true;
    }
    return ret;
}

/* 000029EC-000029FC       .text get_prmFloat__11daNpc_Zl1_cFPff */
f32 daNpc_Zl1_c::get_prmFloat(f32* param_1, f32 param_2) {
    if(param_1 == NULL) {
        return param_2;
    }
    return *param_1;
}

/* 000029FC-00002AFC       .text set_LightPos__11daNpc_Zl1_cFv */
cXyz daNpc_Zl1_c::set_LightPos() {
    cXyz temp;
    temp.set(((daPy_py_c*)dComIfGp_getPlayer(0))->getRightHandPos().x,
        ((daPy_py_c*)dComIfGp_getPlayer(0))->getRightHandPos().y, 
        ((daPy_py_c*)dComIfGp_getPlayer(0))->getRightHandPos().z
    );
    temp.y += 5.66f;
    temp.x += cM_scos(((daPy_py_c*)dComIfGp_getPlayer(0))->shape_angle.y) * 10.25f + cM_ssin(((daPy_py_c*)dComIfGp_getPlayer(0))->shape_angle.y) * 11.13f;
    temp.z += -cM_ssin(((daPy_py_c*)dComIfGp_getPlayer(0))->shape_angle.y) * 10.25f + cM_scos(((daPy_py_c*)dComIfGp_getPlayer(0))->shape_angle.y) * 11.13f;
    return temp;

    // mLightInfluence2.mPos.set(mLightInfluence1.mPos);
}

/* 00002AFC-00002B4C       .text init_Light__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::init_Light() {
    mLightInfluence1.mColor.r = 0x5c;
    mLightInfluence1.mColor.g = 0xae;
    mLightInfluence1.mColor.b = 0xff;
    mLightInfluence1.mPower = 139.7f;
    mLightInfluence1.mFluctuation = 93.8f;
    mLightInfluence2.mColor.r = 0xba;
    mLightInfluence2.mColor.g = 0xff;
    mLightInfluence2.mColor.b = 0xff;
    mLightInfluence2.mPower = 270.7f;
    mLightInfluence2.mFluctuation = 93.8f;
}

/* 00002B4C-00002B9C       .text incEnvironment__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::incEnvironment() {
    mRatio = cLib_maxLimit(mRatio + 0.05f, 1.0f);
    if(mRatio >= 1.0f) {
        field_0x7C2 = 0;
    }
}

/* 00002B9C-00002BCC       .text decEnvironment__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::decEnvironment() {
    mRatio = cLib_minLimit(mRatio -0.05f, 0.15f);
}

/* 00002BCC-00002CD0       .text darkProc__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::darkProc() {

    switch(field_0x7C2) {
        case 1:
            incEnvironment();
            break;
        case -1:
            decEnvironment();
            break;
        default:
        case 0:
            mRatio = 1.0f;
            break;
    }

    dKy_set_vrboxcol_ratio(mRatio);
    dKy_set_fogcol_ratio(mRatio);

    f32 temp = (mRatio - 0.15f) * 1.1764705f;
    if(temp > 0.5f) {
#if VERSION == VERSION_DEMO
        temp = 2.0f - temp * 2.0f;
        dKy_fog_startendz_set(300.0f, 2000.0f, temp);
# else
        dKy_fog_startendz_set(300.0f, 2000.0f, 2.0f - temp * 2.0f);
#endif
    } else {
        dKy_set_bgcol_ratio(temp * 0.85f * 2.0f + 0.15f);
        dKy_fog_startendz_set(300.0f, temp * 3000.0f + 500.0f, 1.0f);
    }
}

/* 00002CD0-00002D58       .text cut_init_LOK_PLYER__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_LOK_PLYER(int i_staffIdx) {
    int* pPrm0 = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "prm_0");
    int temp = 0;
    field_0x84D = 1;

    if(pPrm0 != NULL) {
        temp = *pPrm0;
    }

    switch(temp) {
        case 1:
            field_0x7D8 = true;
            break;
        default:
            field_0x7D8 = false;
            m_jnt.setTrn();
            break;
    }
}

/* 00002D58-00002D60       .text cut_move_LOK_PLYER__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_LOK_PLYER() {
    return TRUE;
}

/* 00002D60-00002E20       .text cut_init_LOK_PARTNER__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_LOK_PARTNER(int i_staffIdx) {
    int* pPrm0 = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "prm_0");
    int temp = 0;
    int temp2;
    if(searchByID(mProcId1, &temp2) != NULL || temp2 == 0) {
        field_0x84D = 4;

        mProcId2 = mProcId1;
        if(pPrm0 != NULL) {
            temp = *pPrm0;
        }

        switch(temp) {
            case 1:
                field_0x7D8 = true;
                break;
            default:
                field_0x7D8 = false;
                m_jnt.setTrn();
                break;
        }
    } 
    
}

/* 00002E20-00002E28       .text cut_move_LOK_PARTNER__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_LOK_PARTNER() {
    return TRUE;
}

/* 00002E28-00002E88       .text cut_init_CHG_ANM_ATR__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_CHG_ANM_ATR(int i_staffIdx) {
    int* pAtrNo = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "AtrNo");
    if(pAtrNo != NULL) {
        field_0x845 = *pAtrNo;
        setAnm_ATR();
    }
}

/* 00002E88-00002E90       .text cut_move_CHG_ANM_ATR__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_CHG_ANM_ATR() {
    return TRUE;
}

/* 00002E90-00002F28       .text cut_init_PLYER_TRN_PARTNER__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_PLYER_TRN_PARTNER(int) {
    int temp;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* pActor = searchByID(mProcId1, &temp);
    if(pActor != NULL || temp == 0) {
        dComIfGp_event_setItemPartner(pActor);
        dComIfGp_event_setTalkPartner(pActor);
        player->changeDemoMoveAngle(cLib_targetAngleY(&dComIfGp_getPlayer(0)->current.pos, &pActor->current.pos));
    }
}

/* 00002F28-00002F30       .text cut_move_PLYER_TRN_PARTNER__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_PLYER_TRN_PARTNER() {
    return TRUE;
}

/* 00002F30-00002F74       .text cut_init_PLYER_TRN_TETRA__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_PLYER_TRN_TETRA(int) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    player->changeDemoMoveAngle(cLib_targetAngleY(&player->current.pos, &current.pos));
}

/* 00002F74-00002F7C       .text cut_move_PLYER_TRN_TETRA__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_PLYER_TRN_TETRA() {
    return TRUE;
}

/* 00002F7C-00002FFC       .text cut_init_MAJYU_START__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_MAJYU_START(int) {
    current.pos.set(-37927.0f, 2200.0f, 7852.0f);
    field_0x758.set(-37978.0f, 400.0f, 7766.0f);

    current.angle.y = cLib_targetAngleY(&current.pos, &field_0x758);
    field_0x84D = 2;
    field_0x7D0 = true;
}

/* 00002FFC-00003004       .text cut_move_MAJYU_START__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_MAJYU_START() {
    return TRUE;
}

/* 00003004-00003020       .text cut_init_OKIRU__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_OKIRU(int) {
    mpMorf->setPlaySpeed(1.0f);
    field_0x7C3 = 0;
}

/* 00003020-00003034       .text cut_move_OKIRU__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_OKIRU() {
    return field_0x7C3 != 0 ? TRUE : FALSE;
}

/* 00003034-0000305C       .text cut_init_OKIRU_2__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_OKIRU_2(int) {
    setAnm_NUM(0xE, 1);
}

/* 0000305C-000030B8       .text cut_move_OKIRU_2__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_OKIRU_2() {
    if(field_0x7C3) {
        setAnm_NUM(0x10, 1);
        mpMorf->setMorf(16.0f);
        return TRUE;
    }

    return FALSE;
}

/* 000030B8-00003118       .text cut_init_DRW_ONOFF__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_DRW_ONOFF(int i_staffIdx) {
    int* pOnOff = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "OnOff");
    if(pOnOff != NULL) {
        field_0x7D4 = *pOnOff == 0;
    }

}

/* 00003118-00003120       .text cut_move_DRW_ONOFF__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_DRW_ONOFF() {
    return TRUE;
}

/* 00003120-000031A8       .text cut_init_PLYER_DRW_ONOFF__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_PLYER_DRW_ONOFF(int i_staffIdx) {
    int* pOnOff = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "OnOff");
    if(pOnOff != NULL) {
        switch(*pOnOff) {
            case 0:
                daPy_getPlayerActorClass()->onPlayerNoDraw();
                break;
            default:
                daPy_getPlayerActorClass()->offPlayerNoDraw();
                break;
        }
    }
}

/* 000031A8-000031B0       .text cut_move_PLYER_DRW_ONOFF__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_PLYER_DRW_ONOFF() {
    return TRUE;
}

/* 000031B0-0000333C       .text cut_init_JMP_OFF__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_JMP_OFF(int i_staffIdx) {
    f32* pSpeed = dComIfGp_evmng_getMyFloatP(i_staffIdx, "Speed");
    f32* pSpeedY = dComIfGp_evmng_getMyFloatP(i_staffIdx, "Spd_y");
    f32* pGrvty = dComIfGp_evmng_getMyFloatP(i_staffIdx, "Grvty");
    f32 speedF1 = get_prmFloat(pSpeed, 0.0f);
    f32 speedY = get_prmFloat(pSpeedY, 0.0f);
    f32 grvty = get_prmFloat(pGrvty, 0.0f);

    setAnm_NUM(10, 1);
    field_0x7CA = false;
    field_0x7C8 = false;
    field_0x7C7 = true;
    field_0x7CB = true;
    current.angle.y = current.angle.y + (s16)0x4000;
    speed.y = speedY;
    speedF = speedF1; // maybe rename speed if i have a better idea
    gravity = grvty;
    daPy_getPlayerActorClass()->onPlayerNoDraw();
    field_0x7D3 = false;
    m_jnt.setHead_y(0);
    m_jnt.setHead_x(0);
    m_jnt.setBackBone_y(0);
    m_jnt.setBackBone_x(0);
    field_0x84D = 0;
    field_0x7D8 = false;
    
    m_jnt.offBackBoneLock();

}

/* 0000333C-000033A0       .text cut_move_JMP_OFF__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_JMP_OFF() {
    if(speedF >= 0.1f) {
        cLib_chaseF(&speedF, 0.1f, 0.05f);
    }
    return move_jmp() == 0 ? TRUE : FALSE;
}

/* 000033A0-000034D4       .text cut_init_OMAMORI_ONOFF__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_OMAMORI_ONOFF(int i_staffIdx) {
    int* pOnOff = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "OnOff");
    field_0x7C2 = 0;
    if(pOnOff != NULL) {
        if(*pOnOff == 0) {
#if VERSION != VERSION_DEMO
            mDoAud_seStart(JA_SE_ITM_OMAMORI_TETLA);
#endif
            field_0x7C2 = -1;
            mRatio = 1.0f;
            init_Light();
            field_0x830 = set_LightPos();
            mLightInfluence1.mPos = field_0x830;
            mLightInfluence2.mPos = field_0x830;
        } else {
            field_0x7C2 = 1;
            mRatio = 0.15f;
            mLightInfluence2.mPower = 0.0f;
            mLightInfluence1.mPower = 0.0f;
        }
    }
}

/* 000034D4-000034DC       .text cut_move_OMAMORI_ONOFF__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_OMAMORI_ONOFF() {
    return TRUE;
}

/* 000034DC-0000356C       .text cut_init_SURPRISED__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::cut_init_SURPRISED(int) {
    mDoAud_seStart(JA_SE_ITM_OMAMORI_BLINK);
    dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
}

/* 0000356C-00003574       .text cut_move_SURPRISED__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::cut_move_SURPRISED() {
    return TRUE;
}

/* 00003574-000037E0       .text privateCut__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::privateCut(int i_staffIdx) {

    static char* a_cut_tbl[] = {
        "LOK_PLYER",
        "LOK_PARTNER",
        "CHG_ANM_ATR",
        "PLYER_TRN_PARTNER",
        "PLYER_TRN_TETRA",
        "MAJYU_START",
        "MAJYU_END",
        "OKIRU",
        "OKIRU_2",
        "DRW_ONOFF",
        "PLYER_DRW_ONOFF",
        "JMP_OFF",
        "OMAMORI_ONOFF",
#if VERSION != VERSION_DEMO
        "SURPRISED"
#endif
    };

    if(i_staffIdx != -1) {
#if VERSION != VERSION_DEMO
        mActIdx = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, 0xE, TRUE, 0);
#else
        mActIdx = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, 0xD, TRUE, 0);
#endif
        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        } else {
            if(dComIfGp_evmng_getIsAddvance(i_staffIdx)) {
                switch(mActIdx) {
                    case 0:
                        cut_init_LOK_PLYER(i_staffIdx);
                        break;
                    case 1:
                        cut_init_LOK_PARTNER(i_staffIdx);
                        break;
                    case 2:
                        cut_init_CHG_ANM_ATR(i_staffIdx);
                        break;
                    case 3:
                        cut_init_PLYER_TRN_PARTNER(i_staffIdx);
                        break;
                    case 4:
                        cut_init_PLYER_TRN_TETRA(i_staffIdx);
                        break;
                    case 5:
                        cut_init_MAJYU_START(i_staffIdx);
                        break;
                    case 7:
                        cut_init_OKIRU(i_staffIdx);
                        break;
                    case 8:
                        cut_init_OKIRU_2(i_staffIdx);
                        break;
                    case 9:
                        cut_init_DRW_ONOFF(i_staffIdx);
                        break;
                    case 10:
                        cut_init_PLYER_DRW_ONOFF(i_staffIdx);
                        break;
                    case 0xb:
                        cut_init_JMP_OFF(i_staffIdx);
                        break;
                    case 0xc:
                        cut_init_OMAMORI_ONOFF(i_staffIdx);
                        break;
#if VERSION != VERSION_DEMO
                    case 0xd:
                        cut_init_SURPRISED(i_staffIdx);
                        break;
#endif
                }

            }
            BOOL temp;
            switch(mActIdx) {
                case 0:
                    temp = cut_move_LOK_PLYER();
                    break;
                case 1:
                    temp = cut_move_LOK_PARTNER();
                    break;
                case 2:
                    temp = cut_move_CHG_ANM_ATR();
                    break;
                case 3:
                    temp = cut_move_PLYER_TRN_PARTNER();
                    break;
                case 4:
                    temp = cut_move_PLYER_TRN_TETRA();
                    break;
                case 5:
                    temp = cut_move_MAJYU_START();
                    break;
                case 7:
                    temp = cut_move_OKIRU();
                    break;
                case 8:
                    temp = cut_move_OKIRU_2();
                    break;
                case 9:
                    temp = cut_move_DRW_ONOFF();
                    break;
                case 10:
                    temp = cut_move_PLYER_DRW_ONOFF();
                    break;
                case 0xb:
                    temp = cut_move_JMP_OFF();
                    break;
                case 0xc:
                    temp = cut_move_OMAMORI_ONOFF();
                    break;
#if VERSION != VERSION_DEMO
                case 0xd:
                    temp = cut_move_SURPRISED();
                    break;
#endif
                default:
                    temp = TRUE;
                    break;
            }
            if((temp & 0xFF) != FALSE) {
                dComIfGp_evmng_cutEnd(i_staffIdx);
            }
        }
    }
}

/* 000037E0-00003804       .text endEvent__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::endEvent() {
    dComIfGp_event_reset();
    field_0x845 = -1;
    field_0x846 = -1;
}

/* 00003804-0000383C       .text isEventEntry__11daNpc_Zl1_cFv */
int daNpc_Zl1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 0000383C-00003A1C       .text event_proc__11daNpc_Zl1_cFi */
void daNpc_Zl1_c::event_proc(int i_staffIdx) {
    if(dComIfGp_evmng_endCheck(mEventIdx[mEventIdx[4]])) {
        switch(mEventIdx[4]) {
            case 0:
                field_0x7D3 = false;
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0802);
                field_0x72C = current.pos;
                field_0x738 = current.angle;
                setStt(1);
                break;
            case 1:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0804);
                current.pos.set(-37692.0f, 2200.0f, 8016.0f);
                current.angle.y = -0x5C72;
                field_0x764.y = current.pos.y;
                field_0x72C = current.pos;
                field_0x738 = current.angle;
                field_0x84D = 0;
                setStt(8);
                break;
            case 2:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0801);
                field_0x7C9 = false;
                break;
            case 3:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3804);
                setStt(3);
                field_0x7CB = false;
                break;
        }
        endEvent();

    } else {
        if(!mEventCut.cutProc()) {
            privateCut(i_staffIdx);
        }
    }
}

/* 00003A1C-00003AC8       .text set_action__11daNpc_Zl1_cFM11daNpc_Zl1_cFPCvPvPv_iPv */
bool daNpc_Zl1_c::set_action(ActionFunc i_action, void* param_2) {
    if(mCurrActionFunc != i_action){
        if(mCurrActionFunc != 0){
            field_0x850 = 9;
            (this->*mCurrActionFunc)(param_2);
        }
        mCurrActionFunc = i_action;
        field_0x850 = 0;
        (this->*mCurrActionFunc)(param_2);
    }
    return true;
}

/* 00003AC8-00003B8C       .text setStt__11daNpc_Zl1_cFSc */
void daNpc_Zl1_c::setStt(s8 param_1) {
    s8 temp = field_0x84B;
    field_0x84B = param_1;

    switch(field_0x84B) {
        case 0:
        case 4:
            break;
        case 1:
        case 6:
        case 7:
        case 8:
        case 9:
            field_0x84A = 0;
            break;
        case 2:
            field_0x84A = 0;
            field_0x845 = 0xff;
            field_0x846 = 0xff;
            field_0x851 = 0;
            field_0x84C = temp;
            break;
        case 3:
            speedF = 0.0f;
            speed.y = 0.0f;
            field_0x7B8 = cLib_getRndValue(0x5A, 0xB4);
            field_0x7BA = 0;
            break;
        case 5:
            field_0x7D3 = true;
            field_0x7CA = true;
            break;
    }
    setAnm();
}

/* 00003B8C-00003D14       .text chk_areaIN__11daNpc_Zl1_cFffs4cXyz */
bool daNpc_Zl1_c::chk_areaIN(f32 param_1, f32 param_2, s16 param_3, cXyz param_4) {
    
    f32 abs1 = (dComIfGp_getPlayer(0)->current.pos - param_4).absXZ();
    f32 abs2 = dComIfGp_getPlayer(0)->current.pos.y - param_4.y;
    s16 angleY = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos);
    s16 angle = (angleY - current.angle.y);
    
    if(abs1 < param_1 && std::fabsf(abs2) < param_2 && abs(angle) < param_3) {
        return true;
    }
    return false;
}

/* 00003D14-00003DE8       .text setWaterRipple__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::setWaterRipple() {
    if(!field_0x7CA) {
        if(mObjAcch.ChkWaterIn()) {
            if(mRippleCallBack.getEmitter() == NULL) {
                dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033,&current.pos, NULL, NULL, 0xff, &mRippleCallBack);
            }
            f32 temp = std::fabsf(speedF) * 0.1f;
            f32 temp2 = temp * temp;
            temp2 = cLib_maxLimit(temp2, 1.0f);

            mRippleCallBack.setRate(temp2);
        } else {
            mRippleCallBack.end();
        }
    }
}

/* 00003DE8-00003E74       .text setWaterSplash__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::setWaterSplash() {
    int temp;
    JPABaseEmitter* pEmitter = dComIfGp_particle_setSimpleLand(
        mObjAcch.m_gnd, &field_0x77C, &field_0x744, 1.25f, 0.65f, 1.0f, &tevStr, &temp, 6
    );

    if(pEmitter != NULL) {
        pEmitter->setLifeTime(0xF);
        pEmitter->setRate(4.0f);
        pEmitter->setSpread(0.6f);
        pEmitter->setDirectionalSpeed(11.0f);
    }
}

/* 00003E74-00003F34       .text set_simpleLand__11daNpc_Zl1_cFb */
#if VERSION != VERSION_DEMO
void daNpc_Zl1_c::set_simpleLand(bool param_1) {
#else
void daNpc_Zl1_c::set_simpleLand() {
#endif
    int temp;
    int temp2 = 6;
#if VERSION != VERSION_DEMO
    if(param_1) {
        temp2 = 7;
    }
#endif
    JPABaseEmitter* pEmitter = dComIfGp_particle_setSimpleLand(
        mObjAcch.m_gnd, &field_0x77C, &field_0x744, 1.25f, 0.65f, 0.6f, &tevStr, &temp, temp2
    );

    if(pEmitter != NULL) {
        switch(temp) {
            case 0x24:
                pEmitter->setRate(10.0f);
                pEmitter->setSpread(1.0f);
                pEmitter->setLifeTime(0xF);
                break;
            case 0x23:
                pEmitter->setRate(18.0f);
                pEmitter->setSpread(1.0f);
                break;
        }

    }
}

/* 00003F34-00004118       .text setEff__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::setEff() {
    if(field_0x849 == 0xb || field_0x7C6) {
        if(mObjAcch.ChkWaterIn()) {
            if(!field_0x7C6) {
                field_0x77C.x = current.pos.x + cM_ssin(shape_angle.y) * 40.0f;

                field_0x77C.z = current.pos.z + cM_scos(shape_angle.y) * 40.0f;
                field_0x744.set(0, shape_angle.y + 0x10000 - 0x8000, 0);
            }
            field_0x77C.y = mObjAcch.m_wtr.GetHeight();
            int attrCode = dComIfG_Bgsp()->GetAttributeCode(mObjAcch.m_gnd);

            if(attrCode == 0x13) {
                if(mObjAcch.m_wtr.GetHeight() > current.pos.y + 40.0f) {
                    setWaterSplash();
                }
            }
        } else {
            if(!field_0x7C6) {
                csXyz temp(current.angle.y, 0, 0);
                field_0x744 = temp;
                field_0x77C.set(current.pos);
            }
            
        }
        if(mObjAcch.ChkGroundHit() != false && (mpMorf->checkFrame(13.0f) || mpMorf->checkFrame(27.0f) || field_0x7C6)) {
#if VERSION != VERSION_DEMO
            set_simpleLand(field_0x7C6);
#endif
            field_0x7C6 = false;
#if VERSION == VERSION_DEMO
            set_simpleLand();
#endif
        }
    }
}

/* 00004118-0000498C       .text setFrontWallType__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::setFrontWallType() {
    BOOL ret;

    f32 sin = cM_ssin(shape_angle.y);
    f32 cos = cM_scos(shape_angle.y);
    dBgS_LinChk linChk;
    
    dBgS_ObjRoofChk roofChk;

    cXyz temp;
    cXyz temp2;
    f32 tempX;
    f32 tempY;
    f32 tempZ;

#if VERSION != VERSION_DEMO
    temp.set(current.pos.x, current.pos.y + mAcchCir.GetWallH(), current.pos.z);
#else
    tempZ = current.pos.z;
    tempY = current.pos.y + mAcchCir.GetWallH();
    tempX = current.pos.x;
    temp.set(tempX, tempY, tempZ);
#endif

    f32 wallRadius = mAcchCir.GetWallR() + 25.0f;
#if VERSION != VERSION_DEMO
    tempX = temp.x;
    tempY = temp.y;
    tempZ = temp.z;
    tempZ += cos * wallRadius;
    tempX += sin * wallRadius;
    temp2.set(tempX, tempY, tempZ);
    // temp2.set(temp.z + sin * wallRadius, temp.y, temp.z + cos * wallRadius);
#else
    f32 tempZ2 = temp.z + cos * wallRadius;
    f32 tempY2 = temp.y;
    f32 tempX2 = temp.x + sin * wallRadius;
    temp2.set(tempX2, tempY2, tempZ2);
#endif


    linChk.Set(&temp, &temp2, this);
    
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return FALSE;
    }
    
    cM3dGPla* plane = dComIfG_Bgsp()->GetTriPla(linChk);
    if(std::fabsf(plane->GetNP()->y) > 0.05f){
        return FALSE;
    }
    
    f32 tempX3;
    f32 tempY3;
    f32 tempZ3;
    tempZ3 = current.pos.z;
    tempY3 = current.pos.y + 70.0f + 0.1f;
    tempX3 = current.pos.x;

    temp.set(tempX3, tempY3, tempZ3);

#if VERSION != VERSION_DEMO
    f32 wallRadius2 = mAcchCir.GetWallR() + 25.0f;

    tempZ = temp.z + cos * wallRadius2;
    tempY = temp.y;
    tempX = temp.x + sin * wallRadius2;
    temp2.set(tempX, tempY, tempZ);

#else 
    wallRadius = mAcchCir.GetWallR() + 25.0f;
    f32 tempZ4 = temp.z + cos * wallRadius;
    f32 tempY4 = temp.y;
    f32 tempX4 = temp.x + sin * wallRadius;
    temp2.set(tempX4, tempY4, tempZ4);
#endif


    linChk.Set(&temp, &temp2, this);

    ret = dComIfG_Bgsp()->LineCross(&linChk);
    if (!ret) {
        roofChk.SetPos(current.pos);
        ret = dComIfG_Bgsp()->RoofChk(&roofChk) - current.pos.y > 80.0f ? FALSE : TRUE;
    }
    
    return ret == FALSE;
}

/* 00004FE4-00005128       .text move_jmp__11daNpc_Zl1_cFv */
bool daNpc_Zl1_c::move_jmp() {
    if(mpMorf->getFrame() >= mpMorf->getEndFrame() - 1.0f) {
        setAnm_NUM(8, 1);
        return false;
    }

    if(!field_0x7C7 && mObjAcch.ChkGroundHit()) {
        mpMorf->setPlaySpeed(1.0f);
        gravity = -4.5f;
        speedF = 0.0f;
        speed.y = 0.0f;

        if(!field_0x7C8) {
            field_0x7C6 = true;
            field_0x744 = current.angle;
            field_0x77C = current.pos;
        }
        return true;
    }

    if(!field_0x7C8 && mObjAcch.ChkWaterIn()) {
        field_0x7C6 = true;
        field_0x744 = current.angle;
        field_0x77C = current.pos;
    }
    return true;
}

/* 00005128-000051D8       .text kyoroPos__11daNpc_Zl1_cFi */
cXyz daNpc_Zl1_c::kyoroPos(int param_1) {
    static Vec a_tgt_offst[] = {
        {0.0f, 0.0f, 0.0f},
        {-100.0f, 0.0f, 0.0f},
        {100.0f, 0.0f, 0.0f},
        {-100.0f, 0.0f, 100.0f},
        {100.0f, 0.0f, 100.0f},
        {0.0f, 0.0f, 100.0f},
        {-100.0f, 40.0f, 0.0f},
        {100.0f, 40.0f, 0.0f},
        {-100.0f, 40.0f, 100.0f},
        {100.0f, 40.0f, 100.0f},
        {0.0f, 40.0f, 100.0f},
        {-40.0f, 10.0f, 40.0f}
    };
    cXyz temp1(a_tgt_offst[param_1].x, a_tgt_offst[param_1].y, a_tgt_offst[param_1].z);
    mDoMtx_stack_c::transS(eyePos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    cXyz temp2;
    mDoMtx_stack_c::multVec(&temp1, &temp2);
    return temp2;

}

/* 000051D8-00005294       .text kyorokyoro__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::kyorokyoro() {
    if(cLib_calcTimer(&field_0x7B0) != 0) {
        field_0x758 = kyoroPos(field_0x7B2);
        return TRUE;
    }
    field_0x7B2 = cLib_getRndValue(1, 10);
    if(field_0x849 == 0xB) {
        field_0x7B0 = l_HIO.mPrmTbl.field_2E;
        field_0x7AE = l_HIO.mPrmTbl.field_32;
    } else {
        field_0x7B0 = l_HIO.mPrmTbl.field_2C;
        field_0x7AE = l_HIO.mPrmTbl.field_30;
    }
    return FALSE;
}

/* 00005294-0000537C       .text wait_1__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::wait_1() {
    if(field_0x84F == 4) {
        cLib_addCalcAngleS(&current.angle.y, field_0x738.y, 4 , 0x800, 0x80);
    }
    if(field_0x7D7) {
        if(chk_talk()) {
            setStt(2);
            field_0x84D = 1;
            field_0x7D8 = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }
    field_0x84A = 2;
    field_0x7D8 = true;
    if(mHasAttention) {
        field_0x7B6 = cLib_getRndValue(0xf, 0x1e);
    }
    if(cLib_calcTimer(&field_0x7B6) != 0) {
        field_0x84D = 1;
        return TRUE;
    }
    field_0x84D = 0;
    return TRUE;
}

/* 0000537C-000054D8       .text talk_1__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::talk_1() {
    BOOL ret = chk_parts_notMov();
    if(field_0x7D7) {
        talk(1);
        if(mpCurrMsg == NULL) {
            return ret;
        }

        switch(mpCurrMsg->mStatus){
            case fopMsgStts_BOX_OPENING_e:
                break;
            case fopMsgStts_MSG_TYPING_e:
                break;
            case fopMsgStts_MSG_DESTROYED_e:
                switch(mCurrMsgNo) {
                    case 0xC91:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2908);
                        break;
                    case 0x1005:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0810);
                        break;
                    case 0xC90:
                        dComIfGp_setNextStage("sea", 0xcd, 0x2c, 10, 0.0f, 0, 1, 0);
                        field_0x7D7 = false;
                        return ret;
                }
                mItemNo = 0xFF;
                field_0x7D7 = false;
                setStt(field_0x84C);
                field_0x7B6 = cLib_getRndValue(0xf,0x1e);
                endEvent();
                break;
            default:
                break;

        }
    }
    return ret;
}

/* 000054D8-00005534       .text demo_1__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::demo_1() {
    if(field_0x84F == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
        fopAcM_delete(this);
    }
    return TRUE;
}

/* 00005534-000055C8       .text demo_2__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::demo_2() {
    if(field_0x84A == 1 || field_0x84A >= 3) {
        return TRUE;
    }
    if(chk_areaIN(l_HIO.mPrmTbl.field_24, 100.0f, 0x7FFF, field_0x764)){
        field_0x84A = 4;
    }
    return TRUE;
}

/* 000055C8-000056E8       .text demo_3__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::demo_3() {
    if(field_0x84A == 1 || field_0x84A >= 3) {
        return TRUE;
    }
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0801)) {
        fopAcM_delete(this);
        return TRUE;
    }

    if(field_0x764.abs(dComIfGp_getPlayer(0)->current.pos) < l_HIO.mPrmTbl.field_28) {
        field_0x84A = 5;
    }
    return TRUE;
}

/* 000056E8-00005718       .text demo_4__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::demo_4() {
    if(field_0x84A == 1 || field_0x84A >= 3) {
        return TRUE;
    }
    field_0x84A = 3;
    return TRUE;
}

/* 00005718-00005954       .text optn_1__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::optn_1() {
    f32 temp = l_HIO.mPrmTbl.field_34 + 100.0f;
    f32 actorDist = fopAcM_searchActorDistance2(this, dComIfGp_getPlayer(0));
    if(field_0x7D7) {
        if(chk_talk()) {
            setStt(2);
            field_0x84D = 1;
            field_0x7D8 = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    field_0x84A = 0;
    field_0x7D8 = true;

    if(actorDist >= temp*temp) {
        s16 angle = fopAcM_searchPlayerAngleY(this);
        cLib_addCalcAngleS(&current.angle.y, angle, 4, 0x800, 0x80);
        if(abs((s16)(angle - current.angle.y)) < 0x1800) {
            setStt(4);
            if(actorDist > (l_HIO.mPrmTbl.field_4C * l_HIO.mPrmTbl.field_4C)) {
                field_0x7AE = l_HIO.mPrmTbl.field_32;
                field_0x7B0 = l_HIO.mPrmTbl.field_2E;
            } else {
                field_0x7AE = l_HIO.mPrmTbl.field_30;
                field_0x7B0 = l_HIO.mPrmTbl.field_2C;
            }
            field_0x7B2 = 0;
        } else {
            field_0x84A = 2;
        }
        field_0x84D = 1;
        return TRUE;
    } 
    
    field_0x84A = 2;
    if(field_0x849 == 0xc) {
        if(field_0x7C3 != 0 && cLib_calcTimer(&field_0x7BA) == 0) {
            setAnm_NUM(8, 1);
            field_0x7B8 = cLib_getRndValue(0x5a, 0xb4);
        }
        field_0x84D = 0;
        return TRUE;
    }

    if(cLib_calcTimer(&field_0x7B8) == 0) {
        setAnm_NUM(0xc, 1);
        field_0x7BA = (g_Counter.mCounter0 & 1) + 1;
        field_0x84D = 0;
        return TRUE;
    }

    field_0x84D = 1;
    return TRUE;
}

/* 00005954-00005C68       .text optn_2__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::optn_2() {

    if(field_0x7CC) {
        field_0x7CC = move_jmp(); // maybe rename field to something mIsMoveJumped
        return TRUE;
    }
    

    f32 actorDist = fopAcM_searchActorDistance2(this, dComIfGp_getPlayer(0));

    f32 temp = actorDist - (l_HIO.mPrmTbl.field_34 * l_HIO.mPrmTbl.field_34);
    f32 temp2 = 0.0f;
    if(temp > 0.0f) {
        temp2 = temp;
        temp2 = std::sqrtf(temp2);
        temp2 = l_HIO.mPrmTbl.field_38 * temp2;
        temp2 = cLib_maxLimit(temp2, l_HIO.mPrmTbl.field_3C);
    }

    s16 angle = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
    cLib_addCalcAngleS(&current.angle.y, angle, 4, 0x800, 0x80);
    cLib_chaseF(&speedF, temp2, l_HIO.mPrmTbl.field_44);
    if((int)temp2 == 0 && (int)speedF == 0) {
        setStt(3);
        field_0x84D = 0;
        field_0x7D8 = false;
    }

    if(mObjAcch.ChkWallHit() && setFrontWallType()) {
        setAnm_NUM(10, 1);
        speedF = l_HIO.mPrmTbl.field_58;
        speed.y = l_HIO.mPrmTbl.field_54;

        field_0x7CC = true;
        return TRUE;
    }

#if VERSION != VERSION_DEMO
    if(!mObjAcch.ChkGroundHit() && mObjAcch.GetGroundH() - current.pos.y < -30.1f) {
        setAnm_NUM(10, 1);
        speed.y = l_HIO.mPrmTbl.field_54;
        field_0x7CC = true;
        return TRUE;
    }
#endif
    if(field_0x849 == 0xb) {
        if(temp <= l_HIO.mPrmTbl.field_4C * l_HIO.mPrmTbl.field_4C) {
            setAnm_NUM(9, 1);
        }
    } else if(temp > l_HIO.mPrmTbl.field_4C * l_HIO.mPrmTbl.field_4C) {
        setAnm_NUM(0xb, 1);
    }
    temp = speedF * l_HIO.mPrmTbl.field_50;
    temp = cLib_minLimit(temp, 0.9f);

    mpMorf->setPlaySpeed(temp);
    if(cLib_calcTimer(&field_0x7AE) != 0) {
        field_0x84D = 1;
        return TRUE;
    }
    field_0x84D = 5;

    return TRUE;
}

/* 00005C68-00005C98       .text optn_3__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::optn_3() {
    if(field_0x84A == 1 || field_0x84A >= 3) {
        return TRUE;
    }
    field_0x84A = 6;
    return TRUE;
}

/* 00005C98-00005DB0       .text wait_action1__11daNpc_Zl1_cFPv */
int daNpc_Zl1_c::wait_action1(void*) {
    switch(field_0x850) {
        case 0:
            if(field_0x84F == 2 && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0802)) {
                setStt(9);
                field_0x850++;
            } else {
                setStt(1);
                field_0x850++;
            }
            break;
        case 1:
        case 2:
        case 3:
            mHasAttention = chkAttention();
            switch(field_0x84B) {
                case 9:
                    field_0x79C = demo_4();
                    break;
                case 1:
                    field_0x79C = wait_1();
                    break;
                case 2:
                    field_0x79C = talk_1();
                    break;

            }
            break;
        case 9:
            break;
    }
    return 1;
}

/* 00005DB0-00005E68       .text demo_action1__11daNpc_Zl1_cFPv */
int daNpc_Zl1_c::demo_action1(void*) {
    switch(field_0x850) {
        case 0:
            setStt(6);
            if(field_0x84F == 1) {
                setAnm_NUM(6, 1);
            } else {
                setAnm_NUM(0, 1);
            }
            field_0x850++;
            break;
        case 1:
        case 2:
        case 3:
            switch(field_0x84B) {
                case 6:
                    field_0x79C = demo_1();
                    break;
                }
            break;
        case 9:
            break;
    }
    return 1;
}

/* 00005E68-00005F80       .text demo_action2__11daNpc_Zl1_cFPv */
int daNpc_Zl1_c::demo_action2(void*) {
    switch(field_0x850) {
        case 0:
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0804)) {
                setStt(8);
                current.pos.set(-37692.0f, 2200.0f, 8016.0f);
                current.angle.y = -0x5C72;
                field_0x764.y = current.pos.y;
                field_0x850++;
            } else {
                setStt(7);
                field_0x850++;
            }
            break;
        case 1:
        case 2:
        case 3:
            switch(field_0x84B) {
                case 7:
                    field_0x79C = demo_2();
                    break;
                case 8:
                    field_0x79C = demo_3();
                    break;
            }
            break;
        case 9:
            break;
    }
    return 1;
}

/* 00005F80-000060A0       .text optn_action1__11daNpc_Zl1_cFPv */
int daNpc_Zl1_c::optn_action1(void*) {
    switch(field_0x850) {
        case 0:
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3804)) {
                setStt(5);
                field_0x850++;
            } else {
                setStt(3);
                field_0x850++;
            }
            break;
        case 1:
        case 2:
        case 3:
            mHasAttention = chkAttention();

            switch(field_0x84B) {


                case 3:
                    field_0x79C = optn_1();
                    break;
                case 4:
                    field_0x79C = optn_2();
                    break;
                case 5:
                    field_0x79C = optn_3();
                    break;
                case 2:
                    field_0x79C = talk_1();
                    break;
            }
            break;
        case 9:
            break;
    }
    return 1;
}

/* 000060A0-0000634C       .text demo__11daNpc_Zl1_cFv */
u8 daNpc_Zl1_c::demo() {
    if(demoActorID == 0) {
        if(field_0x7D9) {
            field_0x7D9 = FALSE;
        }
        
    } else {
        if(!field_0x7D9) {
            for(int i = 0; i < 2; i++) {
                if(field_0x6D4[i] != NULL){
                    field_0x6D4[i]->clrMoveFlag();
                }
            }

            field_0x7D9 = TRUE;
            field_0x7D3 = false;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);  
        }
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);

        J3DAnmTexPattern* btp = mBtpAnm.getBtpAnm();
        if(btp != NULL) {
            s16 frame = btp->getFrameMax() & 0xff;
            mBtpAnmFrame++;
            if((u16)mBtpAnmFrame >= (u16)frame) {
                mBtpAnmFrame = frame;
            }
        }

        btp = demo_actor->getP_BtpData(mArcName);
        if(btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, 1, 0, 1.0f, 0, -1, true, 0);
            field_0x847 = 0x11;
            mBtpAnmFrame = 0;
        }

        J3DAnmTextureSRTKey* btk = mBtkAnm.getBtkAnm();
        if(btk != NULL) {
            s16 frame = (btk->getFrameMax() & 0xff);
            mBtkAnmFrame++;
            if((u16)mBtkAnmFrame >= (u16)frame) {
                mBtkAnmFrame = frame;
            }
        }

        btk = demo_actor->getP_BtkData(mArcName);
        if(btk != NULL) {
            mBtkAnm.init(mpMorf->getModel()->getModelData(), btk, 1, 0, 1.0f, 0, -1, true, 0);
            field_0x848 = 10;
            mBtkAnmFrame = 0;
        }

        if(field_0x7CE) {
            cXyz temp = *demo_actor->getTrans();
            if((int)temp.x != 0 || (int)temp.y != 0 || (int)temp.z != 0) { // convert to ints?
                mpModel = NULL;
                field_0x7CE = false;
            }
        }
        #if VERSION == VERSION_DEMO
        dDemo_setDemoData(this, 
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf, 
            mArcName
        );
        #else
        dDemo_setDemoData(this, 
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf, 
            mArcName,
            0, 
            NULL,
            dBgS_GetGndMtrlSndId_Func(current.pos, 10.0f),
            dComIfGp_getReverb(fopAcM_GetRoomNo(this))
        );
        #endif
    }
    return field_0x7D9;
}

/* 0000634C-000063DC       .text shadowDraw__11daNpc_Zl1_cFv */
void daNpc_Zl1_c::shadowDraw() {
    cXyz pos(current.pos.x,current.pos.y+150.0f,current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId, 
#if VERSION > VERSION_JPN
        0, 
#else
        1,
#endif
        mpMorf->getModel(), 
        &pos, 800.0f, 40.0f, current.pos.y, 
        mObjAcch.GetGroundH(), mObjAcch.m_gnd, 
        &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
}

const u32 unused[] = {
    0x00FF0080,
    0xFFFF0080,
    0x00FF0080,
    0xFF000080,
    0x0000FF80,
    0xFFFF0080,
    0xFF000080,
#if VERSION != VERSION_DEMO
    0x00000000
#endif
};

/* 000063DC-000069D8       .text _draw__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* modelData = pModel->getModelData();

    if(field_0x7D2 || field_0x7D4) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mpMorf->calc();
    pModel->unlock();
    dComIfGd_setListP0();
    J3DMaterialAnm* pMatAnm = field_0x860[2]->getMaterialAnm();

    field_0x860[1]->setMaterialAnm(pMatAnm);
    field_0x860[0]->setMaterialAnm(pMatAnm);

    pMatAnm = field_0x860[5]->getMaterialAnm();

    field_0x860[4]->setMaterialAnm(pMatAnm);
    field_0x860[3]->setMaterialAnm(pMatAnm);

    pMatAnm = field_0x878[2]->getMaterialAnm();

    field_0x878[1]->setMaterialAnm(pMatAnm);
    field_0x878[0]->setMaterialAnm(pMatAnm);

    pMatAnm = field_0x878[5]->getMaterialAnm();

    field_0x878[4]->setMaterialAnm(pMatAnm);
    field_0x878[3]->setMaterialAnm(pMatAnm);

    mBtpAnm.entry(modelData, mBtpAnmFrame);

    mOnCupOffAupPacket2.entryOpa();
    
    field_0x890[2]->hide();
    field_0x890[5]->hide();
    field_0x890[1]->hide();
    field_0x890[4]->hide();
    field_0x890[0]->show();
    field_0x890[3]->show();
    mJoint2->entryIn();

    field_0x8A8[2]->hide();
    field_0x8A8[5]->hide();
    field_0x8A8[1]->hide();
    field_0x8A8[4]->hide();
    field_0x8A8[0]->show();
    field_0x8A8[3]->show();
    mJoint3->entryIn();

    mOffCupOnAupPacket2.entryOpa();

    mBtkAnm.entry(modelData, mBtkAnmFrame);

    field_0x890[0]->hide();
    field_0x890[3]->hide();
    field_0x890[2]->show();
    field_0x890[5]->show();
    mJoint2->entryIn();

    field_0x8A8[0]->hide();
    field_0x8A8[3]->hide();
    field_0x8A8[2]->show();
    field_0x8A8[5]->show();
    mJoint3->entryIn();
    mBtkAnm.remove(modelData);
    
    J3DMaterial* pMat = mJoint1->getMesh();
    for (int no = 0; pMat != NULL; no++) {
        if(no == 0 || no == 1) {
            pMat->getShape()->show();
        } else {
            pMat->getShape()->hide();
        }
        pMat = pMat->getNext();
    }

    mJoint1->entryIn();

    pMat = mJoint1->getMesh();
    for (int no = 0; pMat != NULL; no++) {
        if(no == 0 || no == 1) {
            pMat->getShape()->hide();
        } else {
            pMat->getShape()->show();
        }
        pMat = pMat->getNext();
    }

    mOnCupOffAupPacket1.entryOpa();

    field_0x890[1]->show();
    field_0x890[4]->show();
    field_0x890[2]->hide();
    field_0x890[5]->hide();
    mJoint2->entryIn();

    field_0x8A8[1]->show();
    field_0x8A8[4]->show();
    field_0x8A8[2]->hide();
    field_0x8A8[5]->hide();
    mJoint3->entryIn();
    mOffCupOnAupPacket1.entryOpa();

    field_0x890[1]->hide();
    field_0x890[4]->hide();
    field_0x8A8[1]->hide();
    field_0x8A8[4]->hide();

    dComIfGd_setListP1();
    mpMorf->entry();
    dComIfGd_setList();
    mBtpAnm.remove(modelData);
    if(mpModel != NULL) {
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        mDoExt_modelEntryDL(mpModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK72, this, 1.0f, 1.0f, 1.0f);

    // doesnt do anything?
    cXyz temp;
    if(l_HIO.mPrmTbl.field_20 != 0 && field_0x84F == 3){
        temp = field_0x764;
        temp.y = dComIfGp_getPlayer(0)->current.pos.y;
    }
    return TRUE;
}

/* 000069D8-00006C88       .text _execute__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::_execute() {
    if(!field_0x7D5) {
        field_0x72C = current.pos;
        field_0x738 = current.angle;
        field_0x7D5 = true;
    }
    
    s16 temp = field_0x7BC < 0 ? l_HIO.mPrmTbl.mMaxTurnStep : l_HIO.mPrmTbl.field_5C;

    m_jnt.setParam(
    l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY, l_HIO.mPrmTbl.mMinBackboneX,
    l_HIO.mPrmTbl.mMinBackboneY, l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
    l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY, temp);

    if(field_0x7D2 && demoActorID == 0) {
        return TRUE;
    }

    partner_search();
    checkOrder();

    if(!demo()) {
        int temp = -1;

        if(dComIfGp_event_runCheck()  && eventInfo.checkCommandTalk() == false) {
            temp = isEventEntry();
        }

        if(temp >= 0 || field_0x7C9) {
            event_proc(temp);
        } else {
            (this->*mCurrActionFunc)(NULL);
        }

        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        field_0x7C7 = mObjAcch.ChkGroundHit() ? TRUE : FALSE;
        field_0x7C8 = mObjAcch.ChkWaterIn() ? TRUE : FALSE;
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        play_animation();
    } else {
#if VERSION > VERSION_JPN
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        field_0x7C7 = mObjAcch.ChkGroundHit();
        field_0x7C8 = mObjAcch.ChkWaterIn();
#endif
        field_0x7D2 = false;
    }
    eventOrder();
    field_0x73E = current.angle;
    if(!field_0x7D3) {
        shape_angle = current.angle;
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    darkProc();
    setMtx(false);
    if(!field_0x7D9 && !field_0x7CA && !field_0x7CB) {
        setCollision(50.0f, 140.0f);
    }
    return TRUE;
}

/* 00006C88-00006CF4       .text _delete__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::_delete() {
#if VERSION > VERSION_DEMO
    dComIfG_resDeleteDemo(&mPhs, mArcName);
    if(heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }

    dKy_plight_cut(&mLightInfluence1);
    dKy_efplight_cut(&mLightInfluence2);
    mRippleCallBack.end();
    return TRUE;
#else 
    if(mStateIsComplaete) {
        l_HIO.removeHIO();
        dComIfG_resDelete(&mPhs, mArcName);
        dKy_plight_cut(&mLightInfluence1);
        dKy_efplight_cut(&mLightInfluence2);
        mRippleCallBack.end();
        if(mpMorf != NULL) {
            mpMorf->stopZelAnime();
        }
    }
    return TRUE;

#endif
}

/* 00006CF4-00006E20       .text _create__11daNpc_Zl1_cFv */
cPhs_State daNpc_Zl1_c::_create() {
    static u32 a_siz_tbl[] = {
        0,
        0
    };

    cPhs_State state;
#if VERSION != VERSION_DEMO
    fopAcM_SetupActor(this, daNpc_Zl1_c);
#endif
    if(!decideType(fopAcM_GetParam(this) & 0xFF)) { // idk if this is supposed to be here
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mStateIsComplaete = state == cPhs_COMPLEATE_e;
    if(!mStateIsComplaete) {
        return state;
    } 
#if VERSION == VERSION_DEMO
    l_HIO.entryHIO("海賊ゼルダ");
    fopAcM_SetupActor(this, daNpc_Zl1_c);
#endif

    if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[field_0x84E])) {
#if VERSION == VERSION_DEMO
        mStateIsComplaete = false;

#endif
        return cPhs_ERROR_e;
    } else {

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -50.0f, -20.0f, -50.0f, 50.0f, 140.0f, 50.0f);

        if(createInit() == 0) {
            return cPhs_ERROR_e;
        }
    }
    return state;
}
daNpc_Zl1_c::daNpc_Zl1_c() {}

/* 000073EC-000077C8       .text bodyCreateHeap__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::bodyCreateHeap() {
    enum { 
        EYE_MAX = 6,
    };
    enum {
        EYEBLOW_MAX = 6 

    };

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName, "zl.bdl");
    JUT_ASSERT(VERSION_SELECT(0xED4, 0xF16, 0xF1A, 0xF1A), a_mdl_dat != NULL);

    J3DMaterial * pMat1;

    for (u16 i = 0; i < a_mdl_dat->getMaterialNum(); i++) {
        pMat1 = a_mdl_dat->getMaterialNodePointer(i);
        daNpc_Zl1_matAnm_c * pMatAnm = new daNpc_Zl1_matAnm_c();
        
        pMat1->setMaterialAnm(pMatAnm);
    }

    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL, NULL, NULL,
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020222
    );

    if(!mpMorf){
        return FALSE;
    } else if(mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }

    if(!init_texPttrnAnm(1, false)) {
        mpMorf = NULL;
        return FALSE;
    }
    mJoint1 = a_mdl_dat->getJointNodePointer(0);
    mJoint2 = a_mdl_dat->getJointNodePointer(0xb);
    mJoint3 = a_mdl_dat->getJointNodePointer(0xc);
    J3DMaterial* pMat = mJoint2->getMesh();

    int no;
    for (no = 0; pMat != NULL; pMat = pMat->getNext()) {
        JUT_ASSERT(VERSION_SELECT(0xEFC, 0xF3E, 0xF42, 0xF42), no < EYE_MAX);
        field_0x860[no] = pMat;  
        field_0x890[no++] = pMat->getShape();
    } 


    pMat = mJoint3->getMesh();
    for (no = 0; pMat != NULL; pMat = pMat->getNext()) {
        JUT_ASSERT(VERSION_SELECT(0xF05, 0xF47, 0xF4B, 0xF4B), no < EYEBLOW_MAX);
        field_0x878[no] = pMat;
        field_0x8A8[no++] = pMat->getShape();
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(VERSION_SELECT(0xF0E, 0xF50, 0xF54, 0xF54), m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("chest");
    JUT_ASSERT(VERSION_SELECT(0xF10, 0xF52, 0xF56, 0xF56), m_bbone_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num & 0xffff)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num & 0xffff)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((u32)(this));
    return TRUE;
}

/* 000077C8-000078AC       .text itemCreateHeap__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::itemCreateHeap() {
    if(field_0x84F != 1) {
        mpModel = NULL;
        return TRUE;
    }
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName, "cloth.bdl");
    JUT_ASSERT(VERSION_SELECT(0xF28, 0xF6A, 0xF6E, 0xF6E), a_mdl_dat != NULL);

    mpModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);

    if(mpModel == NULL) {
        return FALSE;
    }
    return TRUE;

}

/* 000078AC-00007974       .text CreateHeap__11daNpc_Zl1_cFv */
BOOL daNpc_Zl1_c::CreateHeap() {
    if(bodyCreateHeap() == FALSE) {
        return FALSE;
    }

    if(itemCreateHeap() == FALSE) {
        mpMorf = NULL;
        return FALSE;
    }

    mLightInfluence1.mPower = 0.0f;
    mLightInfluence2.mPower = 0.0f;
    dKy_plight_priority_set(&mLightInfluence1);
    dKy_efplight_set(&mLightInfluence2);

    mAcchCir.SetWall(30.0f, 50.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    return TRUE;
}

/* 00007974-00007994       .text daNpc_Zl1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Zl1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Zl1_c*)i_this)->_create();
}

/* 00007994-000079B4       .text daNpc_Zl1_Delete__FP11daNpc_Zl1_c */
static BOOL daNpc_Zl1_Delete(daNpc_Zl1_c* i_this) {
    return ((daNpc_Zl1_c*)i_this)->_delete();
}

/* 000079B4-000079D4       .text daNpc_Zl1_Execute__FP11daNpc_Zl1_c */
static BOOL daNpc_Zl1_Execute(daNpc_Zl1_c* i_this) {
    return ((daNpc_Zl1_c*)i_this)->_execute();
}

/* 000079D4-000079F4       .text daNpc_Zl1_Draw__FP11daNpc_Zl1_c */
static BOOL daNpc_Zl1_Draw(daNpc_Zl1_c* i_this) {
    return ((daNpc_Zl1_c*)i_this)->_draw();
}

/* 000079F4-000079FC       .text daNpc_Zl1_IsDelete__FP11daNpc_Zl1_c */
static BOOL daNpc_Zl1_IsDelete(daNpc_Zl1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Zl1_Method = {
    (process_method_func)daNpc_Zl1_Create,
    (process_method_func)daNpc_Zl1_Delete,
    (process_method_func)daNpc_Zl1_Execute,
    (process_method_func)daNpc_Zl1_IsDelete,
    (process_method_func)daNpc_Zl1_Draw,
};

actor_process_profile_definition g_profile_NPC_ZL1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_ZL1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Zl1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_ZL1,
    /* Actor SubMtd */ &l_daNpc_Zl1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
