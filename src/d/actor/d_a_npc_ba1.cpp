/**
* d_a_npc_ba1.cpp
* NPC - Link's Grandma
*/

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ba1.h"
#include "d/actor/d_a_npc_fa1.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_letter.h"
#include "d/d_snap.h"
#include "res/Object/Ba.h"

class daNpc_Ba1_HIO_c : mDoHIO_entry_c {
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
        s16 mCalcAngleTarget;
        f32 mAttPosOffsetY;
        /* 0x18 */ u8 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ f32 m20;
    };  // Size: 0x2C

    daNpc_Ba1_HIO_c();
    virtual ~daNpc_Ba1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;

};

/* 000000EC-00000150       .text __ct__15daNpc_Ba1_HIO_cFv */
daNpc_Ba1_HIO_c::daNpc_Ba1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x1554,
        /* mMaxHeadY         */ 0x2000,
        /* mMinHeadX         */ 0xEC78,
        /* mMinHeadY         */ 0xE000,
        /* mMaxBackboneX     */ 0x0000,
        /* mMaxBackboneY     */ 0x1000,
        /* mMinBackboneX     */ 0X0000,
        /* mMinBackboneY     */ 0xF000,
        /* mMaxTurnStep      */ 0x0400,
        /* mCalcAngleTarget  */ 0x0400,
        /* mAttPosOffsetY    */ 115.0f,
        /* m18               */ 0.0f,
        /* m1C.              */ 500.0f,
        /* m20               */ 300.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}


static daNpc_Ba1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;


/* 00000198-00000210       .text searchActor_Fa__FPvPv */
static void* searchActor_Fa(void* i_param_1, void *) {
    if(l_check_wrk < 0x14 && fopAcM_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_FA1_e){
        l_check_inf[l_check_wrk] =(fopAc_ac_c*)i_param_1;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 00000210-0000025C       .text nodeCallBack_Ba1__FP7J3DNodei */
static BOOL nodeCallBack_Ba1(J3DNode* i_param_1, int i_param_2) {
    if(i_param_2 == 0){
        if(j3dSys.getModel()->getUserArea() != NULL){
            reinterpret_cast<daNpc_Ba1_c*>(j3dSys.getModel()->getUserArea())->nodeBa1Control(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000025C-000003AC       .text nodeBa1Control__11daNpc_Ba1_cFP7J3DNodeP8J3DModel */
void daNpc_Ba1_c::nodeBa1Control(J3DNode* i_node, J3DModel* i_model) {
    
    static cXyz a_eye_pos_off(20.0f, -16.0f, 0.0f);
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    if(jointIdx == m_hed_jnt_num){
        mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    } 
    if(jointIdx == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(),j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx,mDoMtx_stack_c::get());
}

/* 000003E8-00000408       .text daNpc_Ba1_XyCheck_cB__FPvi */
static bool daNpc_Ba1_XyCheck_cB(void* i_this, int i_itemBtn) {
    return static_cast<daNpc_Ba1_c*>(i_this)->XyCheck_cB(i_itemBtn);
}

/* 00000408-00000428       .text XyCheck_cB__11daNpc_Ba1_cFi */
bool daNpc_Ba1_c::XyCheck_cB(int i_itemBtn) {
    /* Nonmatching */
    if (dComIfGp_getSelectItem(i_itemBtn) == dItemNo_FAIRY_BOTTLE_e) {
        return TRUE;
    }
    return FALSE;
}

/* 00000428-00000448       .text daNpc_Ba1_XyEvent_cB__FPvi */
static s16 daNpc_Ba1_XyEvent_cB(void* i_this, int param_1) {
    return static_cast<daNpc_Ba1_c*>(i_this)->XyEvent_cB(param_1);
}

/* 00000448-00000450       .text XyEvent_cB__11daNpc_Ba1_cFi */
s16 daNpc_Ba1_c::XyEvent_cB(int param_1) {
    UNUSED(param_1);
    return mEventIdTable[0];
}

char* l_evn_tbl[] = {
    "Use_Fairy","Ba1_Get_Itm","Ganbaru","tale_1", "None", "tale_2",
};

/* 00000450-000004F8       .text init_BA1_0__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::init_BA1_0() {
    bool ret;
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
        set_action(&daNpc_Ba1_c::wait_action1, NULL);
        mpClothModel = 0;
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

/* 000004F8-000005F4       .text init_BA1_1__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::init_BA1_1() {
    // This int + bool thing is weird, but can't get it to match without ...
    int res;
    bool ret;
    res = dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520);
    ret = res == 0;
    if(!ret) { // weird, but couldn't get it to match without this ...
        return ret;
    } else {
        res = dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001) != 0;
        ret = res;
        if(ret) {
            if(dComIfGs_checkCollect(1)) {
                current.pos.set(-290.f, 0.f, 110.f);
                current.angle.y = 0;
            }
            set_action(&daNpc_Ba1_c::wait_action2, NULL);
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            mpClothModel = 0;
        }
        
    }
    return ret;
}

/* 000005F4-00000648       .text init_BA1_2__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::init_BA1_2() {
    mpClothModel = 0;
    set_action(&daNpc_Ba1_c::demo_action1, NULL);
    return true;
}

/* 00000648-00000734       .text init_BA1_3__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::init_BA1_3() {
    /* Nonmatching */
    int res; // Same as init_1
    bool ret;
    res = dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520);
    ret = res;
    if(!ret) {
        return ret;
    } else {
        res = dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED);
        ret = res ==0;
        if(ret) {
            attention_info.distances[1] = 0x1B;
            attention_info.distances[3] = 0x1C;
            actor_status &= ~0x180; // Fakematch, didn't find a fitting accessor that would match
            set_action(&daNpc_Ba1_c::wait_action3, NULL);
            gravity = 0.f;
            eventInfo.setXyCheckCB((dEvt_info_c::CallbackFunc)&daNpc_Ba1_XyCheck_cB);
            eventInfo.setXyEventCB(&daNpc_Ba1_XyEvent_cB);
        } 
    } 
    return ret;
}

/* 00000734-000007E8       .text init_BA1_4__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::init_BA1_4() {
    // Same as 1 and 3
    int res;
    bool ret;
    res = dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520);
    ret = res;
    if (!ret) {
        return ret;
    }else {
        res = dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED);
        ret = res;
        if(ret) {
            mpClothModel = 0;
            set_action(&daNpc_Ba1_c::wait_action4, NULL);
        }
    }
    
    return ret;
}

/* 000007E8-000009DC       .text createInit__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::createInit() {
    for(int i = 0; i < 6; i++){
        mEventIdTable[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[1] = 171;
    attention_info.distances[3] = 171;
    gravity = -4.5;
    m79C = current.pos;
    mEventCut.setActorInfo2("Ba1", this);
    mAnmNum = 10;
    bool init_success;
    switch (mSpecificType) {
        case 0:
        init_success = init_BA1_0();
        break;
        case 1:
        init_success = init_BA1_1();
        break;
        case 2:
        init_success = init_BA1_2();
        break;
        case 3:
        init_success = init_BA1_3();
        break;
        case 4:
        init_success = init_BA1_4();
        break;
        default:
        init_success = false;
        break;
    }
    if (init_success) {
        m78A = current.angle;
        shape_angle = m78A;
    } else {
        return false;
    }
    m7F2 = dComIfGs_getEventReg(dSv_event_flag_c::UNK_A60F);
    mStts.Init(0xFF,0xFF,this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
    
}

/* 000009DC-00000B44       .text setMtx__11daNpc_Ba1_cFb */
void daNpc_Ba1_c::setMtx(bool param_1) {
    if(!mbInDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if(mpMorf->getFrame() < mPrevMorfFrame){
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        if (mSpecificType != 3) {
            mObjAcch.CrrPos(*dComIfG_Bgsp());
        }
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(m78A.y);
    
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    
    if (mpClothModel != NULL) {
        mpClothModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_footL_jnt_num));
        mpClothModel->calc();
    }
    setAttention(param_1);
}

/* 00000B44-00000B58       .text anmNum_toResID__11daNpc_Ba1_cFi */
int daNpc_Ba1_c::anmNum_toResID(int param_1) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_BA_BCK_WAIT01_e,
        dRes_ID_BA_BCK_TALK01_e,
        dRes_ID_BA_BCK_TALK02_e,
        dRes_ID_BA_BCK_TALK03_e,
        dRes_ID_BA_BCK_HOLD_e,
        dRes_ID_BA_BCK_WAIT02_e,
        dRes_ID_BA_BCK_TALK04_e,
        dRes_ID_BA_BCK_SLEEP_e,
        dRes_ID_BA_BCK_05_BA_CUT8_WAIT_e,
        dRes_ID_BA_BCK_GETUP_e,
    };
    return a_bck_resID_tbl[param_1];
    
}

/* 00000B58-00000B6C       .text btpNum_toResID__11daNpc_Ba1_cFi */
int daNpc_Ba1_c::btpNum_toResID(int param_1) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_BA_BTP_MABA01_e,
        dRes_ID_BA_BTP_BA_T01_e,
        dRes_ID_BA_BTP_BA_T02_e,
        dRes_ID_BA_BTP_BA_T03_e,
        dRes_ID_BA_BTP_BA_T04_e,
        dRes_ID_BA_BTP_BA_T05_e,
        dRes_ID_BA_BTP_BA_T06_e,
        dRes_ID_BA_BTP_BA_T07_e,
        dRes_ID_BA_BTP_BA_T08_e,
        dRes_ID_BA_BTP_BA_T09_e,
        dRes_ID_BA_BTP_BA_T10_e,
        dRes_ID_BA_BTP_BA_WAKE_e,
    };
    return a_btp_resID_tbl[param_1];
}

/* 00000B6C-00000C7C       .text setBtp__11daNpc_Ba1_cFbi */
bool daNpc_Ba1_c::setBtp(bool i_param_1, int i_btp_num) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    int res_id = btpNum_toResID(i_btp_num);
    m_hed_tex_pttrn = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes("Ba",res_id));
    JUT_ASSERT(0x239,m_hed_tex_pttrn != NULL);
    int iVar1 = mHeadBtpAnm.init(model_data,m_hed_tex_pttrn,1,2,1.0f,0,-1,i_param_1,0);
    bool o_retval = iVar1 == 1;
    if(o_retval){
        mBlinkFrame = 0;
        mBlinkTimer = 0;
    }
    return o_retval;
}

/* 00000C7C-00000CA4       .text iniTexPttrnAnm__11daNpc_Ba1_cFb */
bool daNpc_Ba1_c::iniTexPttrnAnm(bool i_param_1) {
    return setBtp(i_param_1, mBtpNum);
}

/* 00000CA4-00000D50       .text plyTexPttrnAnm__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::plyTexPttrnAnm() {
    // 100% identical to the one in bm1
    if(mBtpNum != 0 || !cLib_calcTimer(&mBlinkTimer)){
        mBlinkFrame += 1;
        if(mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()){
            if(mBtpNum != 0){
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }else{
                mBlinkTimer = cM_rndF(60.0f) + 30.0f;
                mBlinkFrame = 0;
                
            }
        }
    }
}

/* 00000D50-00000D8C       .text setAnm_tex__11daNpc_Ba1_cFSc */
void daNpc_Ba1_c::setAnm_tex(s8 i_btp_num) {
    if(mBtpNum != i_btp_num){
        mBtpNum = i_btp_num;
        iniTexPttrnAnm(true);
    }
}

/* 00000D8C-00000E34       .text setAnm_anm__11daNpc_Ba1_cFPQ211daNpc_Ba1_c9anm_prm_c */
BOOL daNpc_Ba1_c::setAnm_anm(daNpc_Ba1_c::anm_prm_c* i_anmPrmP) {
    if(mAnmNum == i_anmPrmP->mAnmNum){
        return 1;
    }
    mAnmNum = i_anmPrmP->mAnmNum;
    dNpc_setAnmIDRes(
        mpMorf,
        i_anmPrmP->mLoopMode,
        i_anmPrmP->mMorf,
        i_anmPrmP->mSpeed,
        anmNum_toResID(mAnmNum),
        -1,
        "Ba"
    );
    mPrevMorfFrame = 0;
    m7EF = 0;
    mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00000E34-00000EA0       .text setAnm_NUM__11daNpc_Ba1_cFii */
void daNpc_Ba1_c::setAnm_NUM(int i_param_1, int i_param_2) {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[11] = {
        {0, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8, 1, J3DFrameCtrl::EMode_NONE},
        {5, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {7, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {8, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {9, 0xB, 0, 8, 1, J3DFrameCtrl::EMode_NONE},
        {0, 9, 0, 0, 1, J3DFrameCtrl::EMode_LOOP},
    };
    if(i_param_2 != 0){
        setAnm_tex(a_anm_prm_tbl[i_param_1].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param_1]);
}

/* 00000EA0-00000F20       .text setAnm__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::setAnm() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[8] = {
        {-1, -1, 0, 0, 0, -1},
        {0, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0, 0, -1},
        {0, 2, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {7, 7, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0, 0, -1},
        {0, 9, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {0, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
    };
    if(a_anm_prm_tbl[mStatus].mBtpNum >= 0){
        setAnm_tex(a_anm_prm_tbl[mStatus].mBtpNum);
    }
    if(a_anm_prm_tbl[mStatus].mAnmNum >= 0){
        setAnm_anm(&a_anm_prm_tbl[mStatus]);
    }
    return true;
}

/* 00000F20-00000F24       .text chg_anmTag__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::chg_anmTag() {}

/* 00000F24-00000F28       .text control_anmTag__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::control_anmTag() {}

/* 00000F28-00000F6C       .text chg_anmAtr__11daNpc_Ba1_cFUc */
void daNpc_Ba1_c::chg_anmAtr(u8 i_param_1) {
    if ((i_param_1 >= 0x15) || (i_param_1 == m80E)) {
        return;
    }
    m80E = i_param_1;
    setAnm_ATR(1);
}

/* 00000F6C-00000FA4       .text control_anmAtr__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::control_anmAtr() {
    switch(m80E) {
        case 5:
        case 6:
            switch (mLookBackState) {
                case 1:
                    break;
                default:
                    mLookBackState = 1;
                    m_jnt.setTrn();
                    break;
            }
            break;
        case 7:
        case 8:
        default:
            return;
    }
}

/* 00000FA4-0000100C       .text setAnm_ATR__11daNpc_Ba1_cFi */
void daNpc_Ba1_c::setAnm_ATR(int i_param_1) {
    static anm_prm_c a_anm_prm_tbl[21] = {
        {0, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {0, 1, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2, 2, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {1, 3, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {3, 2, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2, 3, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2,4, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2, 6, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {3, 5, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {3, 6, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {7, 7, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {6, 8, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {6, 1, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {5, 0XA, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {5, 1, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {5, 9, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {0, 8, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
    };
    if (i_param_1 != 0) {
        setAnm_tex(a_anm_prm_tbl[m80E].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[m80E]);
    
}

/* 0000100C-000010D0       .text anmAtr__11daNpc_Ba1_cFUs */
void daNpc_Ba1_c::anmAtr(u16 i_param_1) {
    u32 mesgAnimeTagInfo;
    switch(i_param_1) {
        case 6:
            if (m819 == 0) {
                m80E = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m819++;
            }
            mesgAnimeTagInfo = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if(mesgAnimeTagInfo != 0xFF && mMesgAnimeTagInfo != mesgAnimeTagInfo){
                mMesgAnimeTagInfo = mesgAnimeTagInfo;
                chg_anmTag();
            }
            break;
        case 0xE:
            m819 = 0;
            break;
        default:
            break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 000010D0-000011A0       .text eventOrder__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::eventOrder() {
    s8 condition = m812;
    if(condition == 1 || condition == 2){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(mSpecificType == 3 && !dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)){
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        }
        if(m812 == 1){
            fopAcM_orderSpeakEvent(this);
        }
    }else if(condition >= 3){
        mEventIdx = condition - 3;
        fopAcM_orderOtherEventId(this,mEventIdTable[mEventIdx]);
    }
}

/* 000011A0-0000123C       .text checkOrder__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()){
        if(dComIfGp_evmng_startCheck(mEventIdTable[mEventIdx])){
            m812 = 0;
        }
    }else if(checkCommandTalk() && (m812 == 1 || m812 == 2)){
        m812 = 0;
        m809 = true;
    }
}

/* 0000123C-000012E8       .text chk_talk__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::chk_talk() {
    bool ret = true;
    mItemNo = 0xFF;
    if(dComIfGp_event_chkTalkXY()){
        if(dComIfGp_evmng_ChkPresentEnd()){
            mItemNo = dComIfGp_event_getPreItemNo();
            
        } else {
            ret = false;
        }
        mItemNo = dComIfGp_event_getPreItemNo();
        
    }
    
    return ret;
}

/* 000012E8-0000137C       .text chk_drct__11daNpc_Ba1_cFf */
bool daNpc_Ba1_c::chk_drct(float i_param_1) {
    s16 target = cLib_targetAngleY(
        &current.pos,
        &dComIfGp_getPlayer(0)->current.pos
    ) - current.angle.y;
    return abs(target) < cM_deg2s(i_param_1);
}

/* 0000137C-000013BC       .text chk_partsNotMove__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::chk_partsNotMove() {
    return mJointHeadY == m_jnt.getHead_y() &&
    mJointBackboneY == m_jnt.getBackbone_y() &&
    mActorAngleY == current.angle.y;
}

/* 000013BC-0000155C       .text lookBack__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f,0.0f,0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = mHeadOnlyFollow;
    
    switch(mLookBackState){
        case 1:
        dstPos = dNpc_playerEyePos(-20.0f);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
        case 2:
        dstPos.set(m79C);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
        case 3:
        desiredYrot = mTargetYRot;
        break;
    }
    cLib_addCalcAngleS2(&mLookAtMaxVel,l_HIO.mPrmTbl.mCalcAngleTarget,4,0x800);
    if(!m_jnt.trnChk()){
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y,dstPos_p,src_pos,desiredYrot,mLookAtMaxVel,headOnlyFollow);
}

/* 0000155C-000016C8       .text next_msgStatus__11daNpc_Ba1_cFPUl */
u16 daNpc_Ba1_c::next_msgStatus(unsigned long* i_msg_no) {
    u16 ret = 0xF;
    switch(*i_msg_no) {
        case 0x7EB:
            *i_msg_no = 0x7EC;
            break;
        case 0x7EF:
            *i_msg_no = 0x7F0;
            break;
        case 0x7F3:
            *i_msg_no = 0x7F4;
            break;
        case 0x7F4:
        // Moving this case bellow the goto 
        // (thus removing the need for the label) 
        // does not match ...
        // Maybe a missing inline ?
        noBottle: 
            if(dComIfGs_checkEmptyBottle()) {
                *i_msg_no = 0x7F5;
            } else {
                *i_msg_no = 0x7F9;
            }
            break;
        case 0x7F6:
            *i_msg_no = 0x7F7;
            break;
        case 0x7FB:
        case 0x7FC:
        case 0x7FD:
        case 0x7FA:
            if(dComIfGs_isGetBottleItem(0x55)) {
                if(!dComIfGs_checkEmptyBottle()) {
                    *i_msg_no = 0x803;
                }
                else if(dComIfGs_checkBottle(0x55)) {
                    *i_msg_no = 0x7FE;
                } else {
                    *i_msg_no = 0x7FF;
                }
                break;
            }
            goto noBottle; // I don't like this ...
        case 0x7FF:
            switch(mpCurrMsg->mSelectNum) {
                case 0:
                *i_msg_no = 0x800;
                break;
                case 1:
                *i_msg_no = 0x802;
                break;
            }
            break;
        default:
            ret = 0x10;
            break;
    }
    return ret;
}

/* 000016C8-00001738       .text getMsg_BA1_0__11daNpc_Ba1_cFv */
u32 daNpc_Ba1_c::getMsg_BA1_0() {  
    if (m7FA) {
        return 0x7d8;
    }
    else if (mbHoldEvent) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0608) ? 0x7e7 : 0x7e6;
    }
    else {
        return m7FB ? 0x7e5 : 0x7e4;
    }
}

/* 00001738-00001818       .text getMsg_BA1_1__11daNpc_Ba1_cFv */
u32 daNpc_Ba1_c::getMsg_BA1_1() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20)) {
        if (dComIfGs_checkCollect(1)) {
            return 0x80b;
        }
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0740) ? 0x7ee : 0x7ef;
        
    }
    else {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0780)) {
            return 0x7ed;
        }
        else {
            if (dComIfGs_checkCollect(0)) {
                return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0602) ? 0x7ea : 0x7eb;
            }
            else {
                return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0601) ? 0x7e9 : 0x7e8;
            }
        }
    }
}

/* 00001818-00001908       .text getMsg_BA1_3__11daNpc_Ba1_cFv */
u32 daNpc_Ba1_c::getMsg_BA1_3() {
    /* Nonmatching */
    
    if (m7F0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
            return 0x801;
        }
        return 0x7f6;
    }
    else {
        if (dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_A60F, 0);
            
            if(m7F2 >= 3) {
                if (m7FA) {
                    return 0x7fd;
                }
                m7FA = true;
                return 0x7fc;
            } else {
                if (m7FA) {
                    return 0x7fa;
                }
                m7FA = true;
                return 0x7fb;
            }
        }
        else {
            return 0x7f1;
        }
    }
}

/* 00001908-00001928       .text getMsg_BA1_4__11daNpc_Ba1_cFv */
u32 daNpc_Ba1_c::getMsg_BA1_4() {
    return getMsg_BA1_3();
}

/* 00001928-000019AC       .text getMsg__11daNpc_Ba1_cFv */
u32 daNpc_Ba1_c::getMsg() {
    u32 ret = 0;
    switch ((mSpecificType)) {
        case 0:
            ret = getMsg_BA1_0();
            break;
        case 1:
            ret = getMsg_BA1_1();
            break;
        case 3:
            ret = getMsg_BA1_3();
            break;
        case 4:
            ret = getMsg_BA1_4();
            break;
    }
    return ret;
}

/* 000019AC-00001A2C       .text chkAttention__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 00001A2C-00001A94       .text setAttention__11daNpc_Ba1_cFb */
void daNpc_Ba1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY,
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
    eyePos.y += mEyeOffset;
}

/* 00001A94-00001AC8       .text searchByID__11daNpc_Ba1_cFUi */
fopAc_ac_c* daNpc_Ba1_c::searchByID(fpc_ProcID i_procID) {
    fopAc_ac_c* o_actor = NULL;
    fopAcM_SearchByID(i_procID,&o_actor);
    return o_actor;
}

/* 00001AC8-00001B78       .text partner_srch_sub__11daNpc_Ba1_cFPFPvPv_Pv */
bool daNpc_Ba1_c::partner_srch_sub(void* (*i_searchFunc)(void*, void*)) {
    bool o_retval = false;
    mPartnerProcID = -1;
    l_check_wrk = 0;
    for(int i = 0; i < 20; i++){
        l_check_inf[i] = 0;
    }
    fpcM_Search(i_searchFunc,this);
    if(l_check_wrk != 0){
        mPartnerProcID = fopAcM_GetID(l_check_inf[0]);     
        o_retval = true;
    }
    return o_retval;
}

/* 00001B78-00001B90       .text partner_srch__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::partner_srch() {
    if (m818 == 1) {
        m818++;
    }
}

/* 00001B90-00001CA8       .text check_useFairyArea__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::check_useFairyArea() {
    bool ret;
    f32 mag = std::sqrtf((dComIfGp_getPlayer(0)->current.pos - current.pos).abs2XZ());
    ret = FALSE;
    if (
        std::abs(dComIfGp_getPlayer(0)->current.pos.y - current.pos.y) < 100.0f 
        && mag < l_HIO.mPrmTbl.m1C
    ) {
        ret = TRUE;
    }
    return ret;
}

/* 00001CA8-00001CF8       .text checkCommandTalk__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::checkCommandTalk() {
    bool ret;
    ret = false;
    
    if (eventInfo.checkCommandTalk() != 0) {
        ret = dComIfGp_event_chkTalkXY() == 0;
    }
    return ret;
}

/* 00001CF8-00001D7C       .text charDecide__11daNpc_Ba1_cFi */
bool daNpc_Ba1_c::charDecide(int i_param_1) {
    mType = 0;
    mSpecificType = -1;
    switch (i_param_1) {
        case 0:
            mSpecificType = 0;
            break;
        case 1:
            mSpecificType = 1;
            break;
        case 2:
            mSpecificType = 2;
            break;
        case 3:
            mSpecificType = 3;
            break;
        case 4:
            mSpecificType = 4;
            break;
        default:
            return false;
    }
    return true;
}

/* 00001D7C-00001E10       .text eInit_SET_PLYER_GOL___11daNpc_Ba1_cFv */
void daNpc_Ba1_c::eInit_SET_PLYER_GOL_() {
    cXyz tmp, target;
    tmp.set(0, 0, 50);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&tmp, &target);
    dComIfGp_evmng_setGoal(&target);
}

/* 00001E10-00001ECC       .text eInit_PLYER_INI_POS___11daNpc_Ba1_cFv */
void daNpc_Ba1_c::eInit_PLYER_INI_POS_() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz tmp, target;
    tmp.set(0, 0, 180);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&tmp, &target);
    player->setPlayerPosAndAngle(
        &target,
        cLib_targetAngleY(&target, &current.pos)
    );
}

/* 00001ECC-00001EE8       .text eInit_USE_FAIRY_END___11daNpc_Ba1_cFv */
void daNpc_Ba1_c::eInit_USE_FAIRY_END_() {
    attention_info.distances[1] = 0x5B;
    attention_info.distances[3] = 0x59;
    mFairyUsed = true;
    
}

/* 00001EE8-00001F04       .text eInit_MOV_POS___11daNpc_Ba1_cFv */
void daNpc_Ba1_c::eInit_MOV_POS_() {
    m7F5 = true;
    mpClothModel = NULL;
    m7F7 = true;
    m7FE = true;
}

/* 00001F04-00001F48       .text eInit_SET_PLYER_TRN_ANG___11daNpc_Ba1_cFv */
void daNpc_Ba1_c::eInit_SET_PLYER_TRN_ANG_() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    player->mDemo.setMoveAngle(
        cLib_targetAngleY(
            &dComIfGp_getPlayer(0)->current.pos, 
            &current.pos)
        );
    }

/* 00001F48-000020AC       .text eInit_ACTOR_DRW_CONTROL___11daNpc_Ba1_cFPiPi */
void daNpc_Ba1_c::eInit_ACTOR_DRW_CONTROL_(int* i_param_1, int* i_param_2) {
    if(i_param_1 != NULL) {
        daPy_py_c* player = daPy_getPlayerActorClass();
        switch (*i_param_1) {
            case 0:
            player->onNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
            break;
            case 1:
            player->offNoResetFlg0(daPy_py_c::daPyFlg0_NO_DRAW);
            break;
        }
        
    }
    if(i_param_2 != NULL) {
        cXyz tmp;
        switch (*i_param_2) {
            case 0:
            m7F7 = 1;
            break;
            case 1:
            m7F7 = 0;
            break;
            case 2:
            setAnm_NUM( 10, 1);
            m7F7 = 1;
            return;
            case 3:
            current.angle.y = cLib_targetAngleY(&current.pos,  &dComIfGp_getPlayer(0)->current.pos);
            attention_info.distances[1] = 0xAB;
            attention_info.distances[3] = 0xAB;
            tmp.set(0, 0, 90);
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(current.angle.y);
            mDoMtx_stack_c::multVec(&tmp, &current.pos);
            m7F7 = 0;
            break;
        }
    }
}

/* 000020AC-000020C8       .text eInit_setEvTimer__11daNpc_Ba1_cFPi */
void daNpc_Ba1_c::eInit_setEvTimer(int* i_param_1) {
    mEvTimer = 0;
    if (i_param_1 != NULL) {
        mEvTimer = *i_param_1;
    }
}

/* 000020C8-000020E8       .text eInit_CHK_FAIRY___11daNpc_Ba1_cFPi */
void daNpc_Ba1_c::eInit_CHK_FAIRY_(int* i_param_1) {
    eInit_setEvTimer(i_param_1);
}

/* 000020E8-000020F8       .text eInit_prmFloat__11daNpc_Ba1_cFPff */
f32 daNpc_Ba1_c::eInit_prmFloat(float* i_param_1, float i_param_2) {
    /* Nonmatching */
    if (i_param_1 != NULL) {
        return *i_param_1;
    }
    return i_param_2;
}

/* 000020F8-00002130       .text eInit_SET_EYE_OFF___11daNpc_Ba1_cFPf */
void daNpc_Ba1_c::eInit_SET_EYE_OFF_(float* i_param_1) {
    mEyeOffset = eInit_prmFloat(i_param_1, 0.0f);
}

/* 00002130-00002168       .text eInit_EYE_OFF_ZRO___11daNpc_Ba1_cFPf */
void daNpc_Ba1_c::eInit_EYE_OFF_ZRO_(float* i_param_1) {
    mEyeOffsetZero = eInit_prmFloat(i_param_1, 0.0f);
}

/* 00002168-00002188       .text eInit_CHK_FAIRY_MOV_1__11daNpc_Ba1_cFPi */
void daNpc_Ba1_c::eInit_CHK_FAIRY_MOV_1(int* i_param_1) {
    eInit_setEvTimer(i_param_1);
}

/* 00002188-00002358       .text event_actionInit__11daNpc_Ba1_cFi */
void daNpc_Ba1_c::event_actionInit(int i_staff_idx) {
    /* Nonmatching */
    int *act_no_p;
    int *prm_0_p;
    int *prm_1_p;
    int *timer_p;
    float *atten_p;
    float *speed_p;
    act_no_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx,"ActNo");
    prm_0_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx,"prm_0");
    prm_1_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx,"prm_1");
    timer_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx,"Timer");
    atten_p = dComIfGp_evmng_getMyFloatP(i_staff_idx,"Atten");
    speed_p = dComIfGp_evmng_getMyFloatP(i_staff_idx,"Speed");
    if (act_no_p != NULL) {
        mActNo = *act_no_p;
        switch (mActNo) {
            case 0:
            setAnm_NUM(9, 1);
            break;
            case 1:
            eInit_SET_PLYER_GOL_();
            break;
            case 2:
            eInit_PLYER_INI_POS_();
            break;
            case 3:
            eInit_USE_FAIRY_END_();
            break;
            case 4:
            eInit_MOV_POS_();
            break;
            case 5:
            eInit_SET_PLYER_TRN_ANG_();
            break;
            case 6:
            eInit_ACTOR_DRW_CONTROL_(prm_0_p,prm_1_p);
            break;
            case 7:
            eInit_CHK_FAIRY_(timer_p);
            break;
            case 8:
            eInit_SET_EYE_OFF_(atten_p);
            break;
            case 9:
            eInit_EYE_OFF_ZRO_(speed_p);
            break;
            case 10:
            eInit_CHK_FAIRY_MOV_1(timer_p);
            break;
            
        }
    }
}

/* 00002358-00002518       .text eMove_MOV_POS___11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::eMove_MOV_POS_() {
    bool ret;
    cXyz temp;
    
    temp.set(503, 0, -91);
    if(cLib_calcTimer(&mEvTimer)) {
        return FALSE;
    } else {
        if((int)mEyeOffset != 0) {
            cLib_chaseF(&mEyeOffset, 0.0f, 2.0f);
            return FALSE;
            
        } else {
            f32 mag = std::sqrtf((temp - current.pos).abs2XZ());
            ret = mag < 4.0f;
            m78A.y = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos);
            m7F5 = true;
            if(ret != 0) {
                current.angle.y = m78A.y;
                m7F5 = false;
                speedF = 0.0;
                mEyeOffset = 0.0;
            } else {
                cLib_addCalcAngleS(
                    &current.angle.y,
                    cLib_targetAngleY(&current.pos, &temp),
                    4,
                    0x400,
                    0
                );
                cLib_chaseF(&speedF, 4.0f, 0.4f);
            }
            return ret;
        }
    }
}

/* 00002518-00002574       .text eMove_CHK_FAIRY___11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::eMove_CHK_FAIRY_() {
    if(cLib_calcTimer(&mEvTimer) == 0) {
        return !partner_srch_sub(searchActor_Fa);
    }
    return false;
}

/* 00002574-00002608       .text eMove_EYE_OFF_ZRO___11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::eMove_EYE_OFF_ZRO_() {
    bool ret;
    
    ret = (int) mEyeOffsetZero == 0;
    
    if (ret) {
        mEyeOffset = 0.0;
    } else {
        cLib_chaseF(&mEyeOffset,0.0,mEyeOffsetZero);
        ret = (int) mEyeOffset == 0;
        if (ret) {
            mEyeOffset = 0.0;
        }
    }
    return ret;
}

/* 00002608-0000269C       .text eMove_CHK_FAIRY_MOV_1__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::eMove_CHK_FAIRY_MOV_1() {
    bool ret = false;
    if(!cLib_calcTimer(&mEvTimer)) {
        if(partner_srch_sub(searchActor_Fa)) {
            daNpc_Fa1_c * actor_fa;
            actor_fa = (daNpc_Fa1_c*) searchByID(mPartnerProcID);
            if(actor_fa != NULL) {
                ret = actor_fa->mMode == 5;
            }
        }
    }
    if(ret) {
        eInit_PLYER_INI_POS_();
    }
    return ret;
}

/* 0000269C-00002704       .text event_action__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::event_action() {
    bool ret;
    switch(mActNo) {
        case 4:
        ret =  eMove_MOV_POS_();
        break;
        case 7:
        ret = eMove_CHK_FAIRY_();
        break;
        case 9:
        ret = eMove_EYE_OFF_ZRO_();
        break;  
        case 10:
        ret = eMove_CHK_FAIRY_MOV_1();
        break;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 8:
        case 0:
        default:
        ret = true;
        break;
    }
    return ret;
}

/* 00002704-00002764       .text cut_init_START_TALE1__11daNpc_Ba1_cFi */
void daNpc_Ba1_c::cut_init_START_TALE1(int i_staff_idx) {
    int *timer_p;
    timer_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx,"Timer");
    mEvTimer = 0;
    if(timer_p != NULL) {
        mEvTimer = *timer_p;
    }
}

/* 00002764-00002820       .text cut_move_START_TALE1__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::cut_move_START_TALE1() {
    /* Nonmatching */
    if(cLib_calcTimer(&mEvTimer) == 0) {
        if(dComIfGs_getClearCount() != 0) {
            dComIfGp_setNextStage(
                "LinkRM", 
                202, 
                0,
                8,
                0.0,
                0,
                1,
                0
            );
        } else {
            dComIfGp_setNextStage(
                "LinkRM", 
                200, 
                0,
                8,
                0.0,
                0,
                1,
                0
            );
            
        }
    }
    return mEvTimer == 0;
}

/* 00002820-00002948       .text privateCut__11daNpc_Ba1_cFi */
void daNpc_Ba1_c::privateCut(int i_staff_idx) {
    static char* a_cut_tbl[] = {
        "ACTION",
        "START_TALE1"
    };
    
    if(i_staff_idx != -1) {
        mActionIndex = dComIfGp_evmng_getMyActIdx(i_staff_idx,a_cut_tbl,ARRAY_SIZE(a_cut_tbl),1,0);
        if (mActionIndex == -1) {
            dComIfGp_evmng_cutEnd(i_staff_idx);
        } else {
            if (dComIfGp_evmng_getIsAddvance(i_staff_idx)) {
                switch(mActionIndex){
                    case 0:
                    event_actionInit(i_staff_idx);
                    break;
                    case 1:
                    cut_init_START_TALE1(i_staff_idx);
                }
            }
            bool endCut;
            switch (mActionIndex) {
                case 0:
                endCut = event_action();
                break;
                case 1:
                endCut = cut_move_START_TALE1();
                break;
                default:
                endCut = true;
                break;
            }
            if(endCut) {
                dComIfGp_evmng_cutEnd(i_staff_idx);
            }
        }
    }
}

/* 00002948-00002968       .text endEvent__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::endEvent() {
    dComIfGp_event_reset();
    m80E = 0xFF;
}

/* 00002968-000029A0       .text isEventEntry__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(),NULL);
    
}

/* 000029A0-00002B50       .text event_proc__11daNpc_Ba1_cFi */
void daNpc_Ba1_c::event_proc(int i_staff_idx) {
    /* Nonmatching */
    if (dComIfGp_evmng_endCheck(mEventIdTable[mEventIdx])) {
        switch(mEventIdx){
            case 0:
                break;
            case 1:
                if(dComIfGs_checkBottle(dItemNo_HALF_SOUP_BOTTLE_e)) {
                    dComIfGs_setBottleItemIn(dItemNo_HALF_SOUP_BOTTLE_e, dItemNo_SOUP_BOTTLE_e);
                } else {
                    dComIfGs_setEmptyBottleItemIn(dItemNo_SOUP_BOTTLE_e);
                }
                if(dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
                    m812 = 1;
                    m7F0 = 1;
                } else {
                    m812 = 5;
                }
                break;
            case 2:
                dLetter_send(0x9D03);
                dComIfGs_onEventBit(dSv_event_flag_c::GRANDMA_HEALED);
                set_action(&daNpc_Ba1_c::wait_action4, NULL);
                mInitialPos = current.pos;
                mInitialAngle = current.angle;
                m7FE = 0;
                break;
            case 3:
                break;
        }
        endEvent();
        return;
    }
    else {
        if (!mEventCut.cutProc()) {
            privateCut(i_staff_idx);
        }
        lookBack();
    }
}

/* 00002B50-00002BFC       .text set_action__11daNpc_Ba1_cFM11daNpc_Ba1_cFPCvPvPv_iPv */
BOOL daNpc_Ba1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc) {
            m818 = 9;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        m818 = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00002BFC-00002CA8       .text setStt__11daNpc_Ba1_cFSc */
void daNpc_Ba1_c::setStt(s8 i_status) {
    s8 temp = mStatus;
    mEvTimer2 = 0;
    mStatus = i_status;
    switch(mStatus) {
        case 2:
            m80E = 0xFF;
            if(mAnmNum != 4) {
                mLookBackState = 1;
                m_jnt.setTrn();
            }
            mPrevStatus = temp;
            return;
        case 0:
            break;
        case 5:
            m80E = 0xFF;
            mPrevStatus = temp;
            return;
        case 1:
        case 3:
        case 4:
        case 6:
        case 7:
            mHeadOnlyFollow = true;
            break;
    }
    setAnm();
    
}

/* 00002CA8-00002E30       .text wait_0__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::wait_0() {
    cLib_addCalcAngleS(
        &current.angle.y,
        mInitialAngle.y,
        4,
        0x800,
        0
    );
    if(m812 == 1 || m812 >= 3) {
        return 1;
    }
    m812 = 0;
    if(!dComIfGs_isTmpBit(dSv_event_flag_c::UNK_0310)) {
        f32 dist = std::sqrtf((dComIfGp_getPlayer(0)->current.pos - current.pos).abs2XZ());
        if(
            std::fabsf(dComIfGp_getPlayer(0)->current.pos.y - current.pos.y) < 100.0f
            && dist < l_HIO.mPrmTbl.m20
        ) {
            dComIfGs_onTmpBit(dSv_event_flag_c::UNK_0310);
            m812 = 6;
        }
    }
    return 1;
}

/* 00002E30-00002F70       .text wait_1__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::wait_1() {
    /* Nonmatching */
    cLib_addCalcAngleS(
        &current.angle.y,
        mInitialAngle.y,
        4,
        0x800,
        0
    );
    if(m812 == 1 || m812 >= 3) {
        return 1;
    }
    if (m809) {
        if (chk_talk()) {
            setStt(2);
            mHeadOnlyFollow = false;
        }
        return 1;
    }
    else if (mbHoldEvent) {
        setAnm_NUM(4,1);
        m812 = 1;
        mLookBackState = 0;
        mTargetYRot = current.angle.y + -0x638e;
    }
    else {
        m812 = 2;
        if (mbAttention != 0) {
            mEvTimer2 = 60;
        }
        if (cLib_calcTimer(&mEvTimer2) && chk_drct(61.0)) {
            mLookBackState = 1;
        }
        else {
            mLookBackState = 3;
            mTargetYRot = (mInitialAngle).y;
            m_jnt.setTrn();
        }
    }
    
    return 1;
}

/* 00002F70-00003110       .text talk_1__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::talk_1() {
    u8 ret;
    
    ret = chk_partsNotMove();
    if (mAnmNum == 4) {
        cLib_addCalcAngleS(
        &current.angle.y,
        mTargetYRot,
        2,
        0x1000,
        1);
        if(!mbMorfAnimStopped) {
            return 1;
        }
    }
    talk(1);
    if (mpCurrMsg != NULL) {
        switch(mpCurrMsg->mStatus) {
            case fopMsgStts_MSG_TYPING_e:
            case fopMsgStts_BOX_OPENING_e:
                break;
            case fopMsgStts_MSG_DESTROYED_e:
                switch (mCurrMsgNo) {
                    case 0x7e4:
                        m7FB = true;
                        break;
                    case 0x7e6:
                        // Unused
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0608);
                        break;
                    case 0x7e8:
                        // After Helmaroc cutscene (prologue)
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0601);
                        break;
                    case 0x7ec:
                        // Sword got
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0602);
                        break;
                    case 0x7f0:
                        // Aryll kidnapped
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0740);
                        break;
                    case 0x800:
                        if (mCurrMsgNo != 0x7f9) {
                            m812 = 4;
                        }
                        mFairyUsed = false;
                        break;
                    case 0x801:
                        m7F0 = 0;
                        break;
                }
                mItemNo = 0xff;
                m809 = false;
                setStt(mPrevStatus);
                mEvTimer2 = 60;
                endEvent();
                mbHoldEvent = false;
        }
    }
    return ret;
}

/* 00003110-00003130       .text talk_2__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::talk_2() {
    talk_1();
}

/* 00003130-00003348       .text wait_2__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::wait_2() {
    cLib_addCalcAngleS(
        &current.angle.y,
        mInitialAngle.y,
        4,
        0x800,
        0
    );
    if(m812 == 1 || m812 >= 3) {
        return 1;
    }
    if (m809) {
        if (m7FF) {
            dComIfGp_setNextStage("LinkRM",201,0,9,0.0,0,1,0);
            return 1;
        }
        else {
            if (chk_talk()) {
                setStt(2);
                mHeadOnlyFollow = false;
            }
            return 1;
        }
    }
    
    else if (!dComIfGs_checkCollect(1) && dComIfGs_isEventBit(dSv_event_flag_c::UNK_3202)) {
        current.pos.x = -290.0;
        current.pos.y = 0.0;
        current.pos.z = 110.0;
        current.angle.y = -0x8000;
        mInitialPos.set(current.pos);

        // Maybe missing a .set(CsXyz) inline function
        mInitialAngle.x = current.angle.x;
        mInitialAngle.y = current.angle.y;
        mInitialAngle.z = current.angle.z;
        if ((dComIfGp_getPlayer(0)->current.pos.y - current.pos.y) < 1.0f) {
            m812 = 1;
            m7FF = 1;
        }
        mLookBackState = 3;
        mTargetYRot = mInitialAngle.y;
        m_jnt.setTrn();
        return 1;
    }
    else {
        m812 = 2;
        if (mbAttention) {
            mEvTimer2 = 60;
        }
        if (cLib_calcTimer(&mEvTimer2) && chk_drct(61.0)) {
            mLookBackState = 1;
        } else {
            mLookBackState = 3;
            mTargetYRot = mInitialAngle.y;
            m_jnt.setTrn();
        }
    }
    return 1;
}

/* 00003348-00003368       .text wait_3__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::wait_3() {
    wait_2();
}

/* 00003368-000034AC       .text ZZZwai__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::ZZZwai() {
    if(m812 == 1 || m812 >= 3) {
        return 1;
    }
    if (mFairyUsed) {
      mFairyUsed = false;
      m812 = 4;
      return 1;
    }
    else if (m809) {
        if (chk_talk()) {
            setStt(5);
        }
        return 1;
    }
    else {
        if (dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
            m812 = 2;
            if (mbAttention) {
                mEvTimer2 = 60;
            }
            if (cLib_calcTimer(&mEvTimer2) && chk_drct(61.0)) {
                mLookBackState = 1;
            } else {
                mLookBackState = 3;
                mTargetYRot = mInitialAngle.y;
                m_jnt.setTrn();
            }
        }
        else {
            m812 = 0;
            if (check_useFairyArea()) {
                m812 = 2;
            }
        }
    }
    return 1;
}

/* 000034AC-0000363C       .text wait_action1__11daNpc_Ba1_cFPv */
BOOL daNpc_Ba1_c::wait_action1(void*) {
    switch(m818) {
        case 0:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
                m7FA = dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0310);
    
                if (m7FA) {
                    dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0310);
                }
                setStt(1);
                m818++;
            }
            else {
                if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0310)) {
                    setStt(1);
                    m818++;
                }
                else {
                    setStt(7);
                    m818++;
                }
            }
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus) {
                case 7:
                    mbSetEyePos = wait_0();
                    break;
                case 1:
                    mbSetEyePos = wait_1();
                    break;
                case 2:
                    mbSetEyePos = talk_1();
                    break;
            }
            lookBack();
        default:
        case 9:

        break;
        

    }
    return 1;

}

/* 0000363C-000036F8       .text wait_action2__11daNpc_Ba1_cFPv */
BOOL daNpc_Ba1_c::wait_action2(void*) {
    switch(m818) {
        case 0:
            setStt(3);
            m818++;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus) {
                case 3:
                    mbSetEyePos =wait_2();
                    break;
                case 2:
                    mbSetEyePos = talk_1();
                    break;
            }
            lookBack();
            break;
        default:
        case 9:
            break;
    }
    return 1;
  }

/* 000036F8-00003730       .text demo_action1__11daNpc_Ba1_cFPv */
BOOL daNpc_Ba1_c::demo_action1(void*) {
    switch (m818) {
        case 9:
            break;
        case 0:
            m818++;
        case 1:
        case 2:
        case 3:
            break;
    }
    return 1;
}

/* 00003730-000037EC       .text wait_action3__11daNpc_Ba1_cFPv */
BOOL daNpc_Ba1_c::wait_action3(void*) {
    switch(m818) {
        case 0:
            setStt(4);
            m818++;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus) {
                case 4:
                    mbSetEyePos = ZZZwai();
                    break;
                case 5:
                    mbSetEyePos =talk_2();
                    break;
            }
            lookBack();
            break;
        default:
        case 9:
            break;
    }
    return 1;
}

/* 000037EC-000038A8       .text wait_action4__11daNpc_Ba1_cFPv */
BOOL daNpc_Ba1_c::wait_action4(void*) {
    switch(m818) {
        case 0:
            setStt(6);
            m818++;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus) {
                case 6:
                    mbSetEyePos = wait_3();
                    break;
                case 2:
                    mbSetEyePos =talk_1();
                    break;
            }
            lookBack();
            break;
        default:
        case 9:
            break;
    }
    return 1;
}

/* 000038A8-00003A18       .text demo__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::demo() {
    if(demoActorID == 0){
        if(mbInDemo != 0){
            mbInDemo = 0;
        }
    }else{
        mbInDemo = 1;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if(m_hed_tex_pttrn){
            mBlinkFrame += 1;
            if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demopattern = demo_actor->getP_BtpData("Ba");
        if(demopattern){
            m_hed_tex_pttrn = demopattern;        
            if(mHeadBtpAnm.init(mpMorf->getModel()->getModelData(),m_hed_tex_pttrn,1,2,1.0f,0,-1,true,FALSE)){
                mBtpNum = dRes_ID_BA_BTP_BA_T02_e;
                mBlinkFrame = 0;
            }
        }
        dDemo_setDemoData(this,0x6A, mpMorf,"Ba");
        m78A.x = current.angle.x;
        m78A.y = current.angle.y;
        m78A.z = current.angle.z;

        shape_angle.x = m78A.x;
        shape_angle.y = m78A.y;
        shape_angle.z = m78A.z;
        
    }
    return mbInDemo;
}

/* 00003A18-00003AA8       .text shadowDraw__11daNpc_Ba1_cFv */
void daNpc_Ba1_c::shadowDraw() {
    cXyz temp(current.pos.x,current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(
        mShadowID,
        1,
        mpMorf->getModel(),
        &temp,
        800.0f,
        40.0f,
        current.pos.y,
        mObjAcch.GetGroundH(),
        mObjAcch.m_gnd,
        &tevStr,
        0,
        1.0,
        dDlst_shadowControl_c::getSimpleTex()
    );

}

static void dummy() {
    const GXColor dummy1 = { 0xFF, 0x00, 0x00, 0x80 };
    const GXColor dummy2 = { 0x00, 0x00, 0xFF, 0x80 };
    const GXColor dummy3 = { 0xFF, 0xFF, 0x00, 0x80 };
    const GXColor dummy4 = { 0xFF, 0xFF, 0x00, 0x80 };
}

/* 00003AA8-00003C0C       .text _draw__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::_draw() {

    J3DModel* morf_model = mpMorf->getModel();
    J3DModelData* model_data = morf_model->getModelData();

    if(mbInitGrandma0 || m7F7) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR,&current.pos,&tevStr);
    g_env_light.setLightTevColorType(morf_model,&tevStr);

    mHeadBtpAnm.entry(model_data,mBlinkFrame);
    mpMorf->entryDL();
    mHeadBtpAnm.remove(model_data);
    if(mpClothModel != NULL) {
        g_env_light.setLightTevColorType(mpClothModel, &tevStr);
        mDoExt_modelEntryDL(mpClothModel);
    }
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_NPC_BA1, this, 1.0f, 1.0f, 1.0f);

    if((u8)l_HIO.mPrmTbl.m18 != 0){
        cXyz somevec;
        if(mSpecificType == 0) {
            somevec = current.pos;
            somevec.y = eyePos.y;
        }
        if(mSpecificType == 3) {
            somevec = current.pos;
            somevec.y = eyePos.y;
        }

    }
    return 1;
}

/* 00003C0C-00003E1C       .text _execute__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::_execute() {
    if(!mbRanExecute) {
        mInitialPos = current.pos;
        mInitialAngle = current.angle;
        mbRanExecute = true;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.mMaxBackboneX ,l_HIO.mPrmTbl.mMaxBackboneY,
        l_HIO.mPrmTbl.mMinBackboneX,l_HIO.mPrmTbl.mMinBackboneY,
        l_HIO.mPrmTbl.mMaxHeadX,l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX,l_HIO.mPrmTbl.mMinHeadY,
        l_HIO.mPrmTbl.mMaxTurnStep);
    if(mbInitGrandma0 && demoActorID == 0) {
        return TRUE;
    }
    m7F6 = false;
    mbInitGrandma0 = false;
    partner_srch();
    checkOrder();
    if(!demo()) {
        s32 cond = -1;
        if(dComIfGp_event_runCheck() && checkCommandTalk() == false){
            cond = isEventEntry();
        }
        if(cond >= 0){
            mbSetEyePos = 1;
            event_proc(cond);
        }else{
            (this->*mCurrProcFunc)(NULL);
        }
        if(!m7F6) {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if(!m7F5) {
            m78A = current.angle;
            shape_angle = m78A;
        }
    }
    eventOrder();
    setMtx(false);
    if(!mbInDemo && !m7FE){
        f32 radius = 50;
        if(m7FD) {
            radius = 30;
        }
        setCollision(radius,110.0f);
    }
    return TRUE;
}

/* 00003E1C-00003E78       .text _delete__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::_delete() {
    dComIfG_resDelete(&mPhs,"Ba");
    if(heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return 1;

}

/* 00003E78-00003E98       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    static_cast<daNpc_Ba1_c*>(i_this)->CreateHeap();
}

/* 00003E98-00003FB8       .text _create__11daNpc_Ba1_cFv */
cPhs_State daNpc_Ba1_c::_create() {
    static int a_size_tbl[] = {
        0x272E0
    };

    fopAcM_ct_Retail(this, daNpc_Ba1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs,"Ba");
    if(state != cPhs_COMPLEATE_e) {
        return state;
    } else {
        if(charDecide(fpcM_GetParam(this) & 0xFF) == 0) {
            return cPhs_ERROR_e;
        }
        if(!fopAcM_entrySolidHeap(this,CheckCreateHeap,a_size_tbl[mType])){
            return cPhs_ERROR_e;
        }
        fopAcM_SetMtx(this,mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this,-50.0,-20.0,-50.0,50.0,120.0,50.0);
        if(!createInit()){
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 000043E8-00004658       .text create_Anm__11daNpc_Ba1_cFv */
J3DModelData* daNpc_Ba1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ba",10);
    JUT_ASSERT(0xB0C,a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(
            "Ba", 
            7
        ),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11020022
    );
    if(mpMorf == NULL ){
        return NULL;
    }else if(mpMorf->getModel() == NULL){
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0xB20,m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0xB23,m_bbone_jnt_num >= 0);    
    m_footL_jnt_num = a_mdl_dat->getJointName()->getIndex("footL");
    JUT_ASSERT(0xB26,m_footL_jnt_num >= 0);    

    return a_mdl_dat;  
}

/* 00004658-00004714       .text create_itm_Mdl__11daNpc_Ba1_cFv */
bool daNpc_Ba1_c::create_itm_Mdl() {
    mpClothModel = NULL;
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ba",9);
    JUT_ASSERT(0xB38,a_mdl_dat != NULL);
    mpClothModel = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000002);
    return true;
}

/* 00004714-0000485C       .text CreateHeap__11daNpc_Ba1_cFv */
BOOL daNpc_Ba1_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* modeldat;
    J3DModelData* anm_model = create_Anm();
    if(!anm_model) {
        return 0;
    }
    mBtpNum = 1;
    if(!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return 0;
    }
    if(create_itm_Mdl()) {
        for(u16 i = 0; i < anm_model->getJointNum(); i++){
            if((i == m_hed_jnt_num) ||( i == m_bbone_jnt_num)){
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ba1);
            }
        }
        mpMorf->getModel()->setUserArea((u32)this);
        mAcchCir.SetWall(30.0f,50.0f);
        mObjAcch.Set(
            fopAcM_GetPosition_p(this),
            fopAcM_GetOldPosition_p(this),
            this,
            1,
            &mAcchCir,
            fopAcM_GetSpeed_p(this),
            NULL,
            NULL
        );
        return 1;
    } else {
        mpMorf = NULL;
        return 0;
    }
}

/* 0000485C-0000487C       .text daNpc_Ba1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ba1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ba1_c*)i_this)->_create();
}

/* 0000487C-0000489C       .text daNpc_Ba1_Delete__FP11daNpc_Ba1_c */
static BOOL daNpc_Ba1_Delete(daNpc_Ba1_c* i_this) {
    return ((daNpc_Ba1_c*)i_this)->_delete();
}

/* 0000489C-000048BC       .text daNpc_Ba1_Execute__FP11daNpc_Ba1_c */
static BOOL daNpc_Ba1_Execute(daNpc_Ba1_c* i_this) {
    return ((daNpc_Ba1_c*)i_this)->_execute();
}

/* 000048BC-000048DC       .text daNpc_Ba1_Draw__FP11daNpc_Ba1_c */
static BOOL daNpc_Ba1_Draw(daNpc_Ba1_c* i_this) {
    return ((daNpc_Ba1_c*)i_this)->_draw();
}

/* 000048DC-000048E4       .text daNpc_Ba1_IsDelete__FP11daNpc_Ba1_c */
static BOOL daNpc_Ba1_IsDelete(daNpc_Ba1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ba1_Method = {
    (process_method_func)daNpc_Ba1_Create,
    (process_method_func)daNpc_Ba1_Delete,
    (process_method_func)daNpc_Ba1_Execute,
    (process_method_func)daNpc_Ba1_IsDelete,
    (process_method_func)daNpc_Ba1_Draw,
};

actor_process_profile_definition g_profile_NPC_BA1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BA1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ba1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BA1_e,
    /* Actor SubMtd */ &l_daNpc_Ba1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
