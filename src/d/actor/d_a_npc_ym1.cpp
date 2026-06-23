/**
 * d_a_npc_ym1.cpp
 * NPC - Mesa & Abe
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ym1.h"
#include "JSystem/JUtility/JUTAssert.h"

static char* strings0[]={"Ym1","Ym2","d_a_npc_ym1.cpp"};

/* 000000EC-00000108       .text __ct__20daNpc_Ym1_childHIO_cFv */
daNpc_Ym1_childHIO_c::daNpc_Ym1_childHIO_c() {
    /* Nonmatching */
}

/* 00000150-0000020C       .text __ct__15daNpc_Ym1_HIO_cFv */
daNpc_Ym1_HIO_c::daNpc_Ym1_HIO_c() {
    /* Nonmatching */
}
daNpc_Ym1_HIO_c l_HIO;

/* 00000268-00000290       .text area_check__FP10fopAc_ac_cP4cXyzUl */
static void area_check(fopAc_ac_c* i_param_1, cXyz*, unsigned long i_param_3) {
    /* Nonmatching */
    if(i_param_3 == 0){
        ((daNpc_Ym1_c*)i_param_1)->setKariFlg();
    }
    return;
}

/* 00000290-0000029C       .text setKariFlg__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::setKariFlg() {
    /* Nonmatching */
    this->mKariFlag = 1;
    return;
}

/* 0000029C-000002E8       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_param_1, int i_param_2) {

    if(i_param_2 == 0){
        u32 model = j3dSys.getModel()->getUserArea();
        if(model){
            ((daNpc_Ym1_c*)model)->_nodeCB_Head(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000002E8-00000400       .text _nodeCB_Head__11daNpc_Ym1_cFP7J3DNodeP8J3DModel */
void daNpc_Ym1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {
    static cXyz a_eye_pos_off(26.0f, -25.0f, 0.0f);
    u16 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::multVecZero(&m870);
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(m_jnt.getHead_x());
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &m84C);
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 0000043C-00000488       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_param_1, int i_param_2) {
    if(i_param_2 == 0){
        u32 model = j3dSys.getModel()->getUserArea();
        if(model){
            ((daNpc_Ym1_c*)model)->_nodeCB_BackBone(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;

}

/* 00000488-00000520       .text _nodeCB_BackBone__11daNpc_Ym1_cFP7J3DNodeP8J3DModel */
void daNpc_Ym1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {

    u16 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000520-00000540       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_param_1) {
    ((daNpc_Ym1_c*)i_param_1)->CreateHeap();
    return;
}

/* 00000540-000005C0       .text init_YM1_0__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::init_YM1_0() {
    BOOL event_bit = dComIfGs_isEventBit(0x520);
    if(event_bit == 0){
        set_action(&daNpc_Ym1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 000005C0-00000640       .text init_YM1_1__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::init_YM1_1() {
    BOOL event_bit = dComIfGs_isEventBit(0x520);
    if(event_bit != 0){
        set_action(&daNpc_Ym1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 00000640-000006E0       .text init_YM2_0__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::init_YM2_0() {
    if(!dComIfGs_isEventBit(0x520) && !dComIfGs_isEventBit(0xe20)){
        set_action(&daNpc_Ym1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 000006E0-00000780       .text init_YM2_1__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::init_YM2_1() {
    /* Nonmatching */
    if(!dComIfGs_isEventBit(0x520) && dComIfGs_isEventBit(0xe20)){
        set_action(&daNpc_Ym1_c::wait_action2, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 00000780-0000080C       .text init_YM2_2__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::init_YM2_2() {
    /* Nonmatching */
    if(dComIfGs_isEventBit(0x520) && !dKy_daynight_check()){
        set_action(&daNpc_Ym1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 0000080C-00000898       .text init_YM2_3__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::init_YM2_3() {
    /* Nonmatching */
    if(dComIfGs_isEventBit(0x520) && dKy_daynight_check() == 1){
        set_action(&daNpc_Ym1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 00000898-000008E4       .text init_YMx_error__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::init_YMx_error() {
    /* Nonmatching */
    set_action(&daNpc_Ym1_c::wait_action1, NULL);
        return TRUE;
}

/* 000008E4-00000B98       .text createInit__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::createInit() {
    /* Nonmatching */
    static u8 a_att_dist_TBL[1][2] = {{}};
    static char* a_staff_tbl[1] = {};
    mEventCut.setActorInfo2(a_staff_tbl[mStaff],this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[1] = a_att_dist_TBL[mSubType][0];
    attention_info.distances[3] = a_att_dist_TBL[mSubType][1];
    m8AB = 0xD;
    bool temp;
    switch(mStaff) {
        case 0:
            temp = init_YM1_0();
            break;
        case 1:
            temp = init_YM1_1();
            break;
        case 2:
            temp = init_YM2_0();
            break;
        case 3:
            temp = init_YM2_1();
            break;
        case 4:
            temp = init_YM2_2();
            break;
        case 5:
            temp = init_YM2_3();
            break;
        case 6:
        case 7:
            temp = init_YMx_error();
            break;
        default:
            temp = false;
            break;
    }

    if(!temp) {
        return false;
    }
        m846 = current.angle;
        shape_angle = m846;
        gravity = -4.5f;
        mStts.Init(0xFF,0xFF,this);
        mCyl.SetStts(&mStts);
        mCyl.Set(dNpc_cyl_src);
        if(mStaff == 0){

            cXyz test(0.0,0.0,80.0);
            mCyl704.SetStts(&mStts);
            mCyl704.Set(dNpc_cyl_src);

            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(current.angle.y);
            cXyz local_28;
            mDoMtx_stack_c::multVec(&test,&local_28);

            mCyl704.SetC(local_28);
            mCyl704.SetR(50.0);
            mCyl704.SetH(30.0);
            dComIfG_Ccsp()->SetMass(&mCyl704,3);
        }

            play_animation();
            if(mStaff != 1){
                mObjAcch.CrrPos(*dComIfG_Bgsp());
            }
            tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
            mpMorf->setMorf(0.0);
            setMtx(true);
            return true;

}

/* 00000B98-00000C04       .text play_animation__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::play_animation() {
    play_texPttrnAnm();
    m898 = mpMorf->play(&eyePos,0,0);
    if(mpMorf->getFrame() < m87C){
        m898 = 1;
    }
    m87C = mpMorf->getFrame();
}

/* 00000C04-00000D34       .text setMtx__11daNpc_Ym1_cFb */
void daNpc_Ym1_c::setMtx(bool i_param_1) {
    J3DModel* mcaMorf = mpMorf->getModel();
    mcaMorf->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(m846);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    mpHeadModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    mpHeadModel->calc();
    if(m6D0 != NULL){
        m6D0->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        m6D0->calc();
    }
    setAttention(i_param_1);
}

/* 00000D34-00000D48       .text bckResID__11daNpc_Ym1_cFi */
int daNpc_Ym1_c::bckResID(int i_param_1) {
    static const int a_res_id_tbl[0xD] = {0,1,2,5,3,8,6,7,4,19,16,17,18};
    return a_res_id_tbl[i_param_1];
}

/* 00000D48-00000D98       .text btpResID__11daNpc_Ym1_cFi */
int daNpc_Ym1_c::btpResID(int i_param_1) {
    static const int a_res_id_tbl[0x1] = {0xE};
    if(a_res_id_tbl[i_param_1] == 0xE){
        switch(mSubType){
            case 1:
                return 0xE;
            case 2:
                return 0xF;

        }
    }
    return a_res_id_tbl[i_param_1];
}

/* 00000D98-00000E98       .text init_texPttrnAnm__11daNpc_Ym1_cFScb */
bool daNpc_Ym1_c::init_texPttrnAnm(signed char i_param_1, bool i_param_2) {
    J3DModel* head = mpHeadModel;
    if(i_param_1 < 0){
        return false;
    }else{
        J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(mArcName,btpResID(i_param_1));
        JUT_ASSERT(VERSION_SELECT(0x270,0x270,0x270,0x270),a_btp != NULL);
        m8AA = i_param_1;
        m6F4 = 0;
        m6F6 = 0;
        return mBtpAnm.init(head->getModelData(),a_btp,true,0,1.0f,0,-1,i_param_2) != 0;
    }
}

/* 00000E98-00000F28       .text play_texPttrnAnm__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::play_texPttrnAnm() {

    if(m8AA || !cLib_calcTimer(&m6F6)){
        m6F4 += 1;
        s16 frame = mBtpAnm.getBtpAnm()->getFrameMax();
        if(m6F4 >= frame){
            if(m8AA != 0){
                m6F4 = frame;
            }else{
                m6F6 = cLib_getRndValue(0x3C,0x5A);
                m6F4 = 0;
            }
        }
    }
}
f32 lHioFillerFloats[1][11] = {{1.0,2.0}};
/* 00000F28-00000FF4       .text setAnm_anm__11daNpc_Ym1_cFPQ211daNpc_Ym1_c9anm_prm_c */
void daNpc_Ym1_c::setAnm_anm(daNpc_Ym1_c::anm_prm_c* i_param_1) {
    /* Nonmatching */
    //if(i_param_1->m0 >= 0 && m8AB != i_param_1->m0){
    s8 temp = i_param_1->m0;
    if(temp < 0 || m8AB == temp) {
        return;
    }





        dNpc_setAnmIDRes(mpMorf,
            i_param_1->mC,
            i_param_1->m4,
            i_param_1->m8,
            bckResID(i_param_1->m0),
            -1,
            mArcName
            
        );
        m8AB = (u32)i_param_1->m0;
        m898 = 0;
        m899 = 0;
        m87C = 0;
        if(m8AB == 8){
            mpMorf->setMorf(l_HIO.m4[mSubType][0]);
        }
    return;
}

/* 00000FF4-00001064       .text setAnm_NUM__11daNpc_Ym1_cFii */
void daNpc_Ym1_c::setAnm_NUM(int i_param_1, int i_param_2) {

    static anm_prm_c a_anm_prm_tbl [13] ={
    {0,0,0,8,1.0,2},
    {1,0,0,8,1.0,2},
    {2,0,0,8,1.0,0},
    {3,0,0,8,1.0,2},
    {4,0,0,8,1.0,2},
    {5,0,0,8,1.0,2},
    {6,0,0,8,1.0,0},
    {7,0,0,8,1.0,2},
    {8,0,0,8,1.0,2},
    {9,0,0,8,1.0,2},
    {10,0,0,8,1.0,2},
    {11,0,0,8,1.0,2},
    {12,0,0,8,1.0,2},
    };
    if(i_param_2 != 0){
        init_texPttrnAnm(a_anm_prm_tbl[i_param_1].m1,true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param_1]);
}

/* 00001064-000010D0       .text setAnm__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::setAnm() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl [12] ={
    {-1,-1,0,0,0,-1},
    {1,0,0,8,1.0,2},
    {3,0,0,8,1.0,2},
    {3,0,0,8,1.0,2},
    {3,0,0,8,1.0,2},
    {-1,-1,0,0,0,-1},
    {5,0,0,8,1.0,2},
    {-1,-1,0,0,0,-1},
    {0,0,0,8,1.0,2},
    {-1,-1,0,0,0,-1},
    {9,0,0,8,1.0,2},
    {10,0,0,8,1.0,2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[m8AD].m1,true);
    setAnm_anm(&a_anm_prm_tbl[m8AD]);
}

/* 000010D0-000010D4       .text chngAnmTag__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::chngAnmTag() {
    return;
}

/* 000010D4-000010D8       .text ctrlAnmTag__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::ctrlAnmTag() {
    return;
}

/* 000010D8-00001118       .text chngAnmAtr__11daNpc_Ym1_cFUc */
void daNpc_Ym1_c::chngAnmAtr(unsigned char i_param_1) {
    if(i_param_1 == m8A8 || i_param_1 > 0xD){
        return;
    }
    m8A8 = i_param_1;
    setAnm_ATR();
    return;
}

/* 00001118-0000111C       .text ctrlAnmAtr__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::ctrlAnmAtr() {
    return;
}

/* 0000111C-00001180       .text setAnm_ATR__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::setAnm_ATR() {
    static daNpc_Ym1_c::anm_prm_c a_anm_prm_tbl[2] = {
        {0, 0, 8.0f, 1.0f, 2},
        {1, 0, 8.0f, 1.0f, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[m8A8].m1, true);
    setAnm_anm(&a_anm_prm_tbl[m8A8]);
}

/* 00001180-0000123C       .text anmAtr__11daNpc_Ym1_cFUs */
void daNpc_Ym1_c::anmAtr(unsigned short i_msgStatus) {
    switch (i_msgStatus) {
        case fopMsgStts_MSG_TYPING_e: {
            if(m8B3 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m8B3++;
            }
            u8 tagInfo = dComIfGp_getMesgAnimeTagInfo();
            if(tagInfo != 0xFF && tagInfo != m8A9){
                dComIfGp_clearMesgAnimeTagInfo();
                m8A9 = tagInfo;
                chngAnmTag();
            }
            break;
        }
        case fopMsgStts_MSG_DISPLAYED_e:
            m8B3 = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 0000123C-000014F0       .text next_msgStatus__11daNpc_Ym1_cFPUl */
u16 daNpc_Ym1_c::next_msgStatus(unsigned long* pMsgNo) {

    u16 o_retval = 0xF;
    switch ((s32) *pMsgNo) {
    case 0x8FD:
        *pMsgNo = 0x8FE;
        break;
    case 0x8FF:
        *pMsgNo = 0x900;
        break;
    case 0x901:
        *pMsgNo = 0x902;
        break;
    case 0x90A:
        *pMsgNo = 0x90B;
        break;
    case 0x904:
        *pMsgNo = 0x905;
        break;
    case 0x905:
        *pMsgNo = 0x906;
        break;
    case 0x907:
        *pMsgNo = 0x908;
        break;
    case 0x908:
        if (dComIfGs_isEventBit(0x3004U) != 0) {
            o_retval = 0x10;
        } else {
            *pMsgNo = 0x909;
        }
        break;
    case 0xA2F:
        if (dKy_daynight_check() == 1) {
            *pMsgNo = 0xA30;
        } else {
            if (dComIfGs_getEventReg(0xBFFFU)) {
                if (dComIfGs_isEventBit(0x3402U)) {
                    *pMsgNo = 0xA31;
                } else {
                    *pMsgNo = 0xA33;
                }
            } else if (dComIfGs_isEventBit(0x3402U) != 0) {
                *pMsgNo = 0xA37;
            } else {
                *pMsgNo = 0xA35;
            }
        }
        break;
    case 0xA31:
        *pMsgNo = 0xA32;
        break;
    case 0xA33:
        *pMsgNo = 0xA34;
        break;
    case 0xA35:
        *pMsgNo = 0xA36;
        break;
    case 0xA37:
        *pMsgNo = 0xA38;
        break;
    case 0xA3B:
        if (dComIfGs_isEventBit(0x3402U) != 0) {
            *pMsgNo = 0xA3C;
        } else {
            *pMsgNo = 0xA3D;
        }
        break;
    case 0xA3E:
        if (dComIfGs_isEventBit(0x3402U) != 0) {
            *pMsgNo = 0xA40;
        } else {
            *pMsgNo = 0xA3F;
        }
        break;
    case 0xA41:
        *pMsgNo = 0xA42;
        break;
    default:
        o_retval = 0x10;
        break;
    }
    return o_retval;
}

/* 000014F0-00001584       .text getMsg_YM1_0__11daNpc_Ym1_cFv */
unsigned long daNpc_Ym1_c::getMsg_YM1_0() {
    if(dComIfGs_checkCollect(0)){
        return dComIfGs_isEventBit(0x10) ? 0x903 : 0x901;
    }else{
        if(dComIfGs_isEventBit(0x20)){
            return 0x8FF;
        }else{
            return dComIfGs_isEventBit(0x2A80) ? 0x8FD : 0x90A;
        }
    }
}

/* 00001584-000015C4       .text getMsg_YM1_1__11daNpc_Ym1_cFv */
unsigned long daNpc_Ym1_c::getMsg_YM1_1() {
    return dComIfGs_isEventBit(0x2904) ? 0x907 : 0x904;
}

/* 000015C4-00001630       .text getMsg_YM2_0__11daNpc_Ym1_cFv */
unsigned long daNpc_Ym1_c::getMsg_YM2_0() {
    if(chk_BlackPig() != 0){
        return 0xA2B + (dComIfGs_isEventBit(0x8) ? 1 : 0);

    }else{
        return 0xA29 + (dComIfGs_isEventBit(0x80) ? 1 : 0);
    }
}

/* 00001630-0000166C       .text getMsg_YM2_1__11daNpc_Ym1_cFv */
unsigned long daNpc_Ym1_c::getMsg_YM2_1() {
    return (dComIfGs_isEventBit(0xB01) ? 1 : 0) + 0xA2D;
}

/* 0000166C-00001718       .text getMsg_YM2_2__11daNpc_Ym1_cFv */
unsigned long daNpc_Ym1_c::getMsg_YM2_2() {

    if(!dComIfGs_isEventBit(0x3140)){
        return 0xA2F;
    }else{
        if(dKy_daynight_check() == 1){
            u32 retval =  dComIfGs_isEventBit(0x3402) ? 1 : 0;
            return retval + 0xA39;
        }else{
            if(!dComIfGs_isEventBit(0x3580)){
                return 0xA3B;
            }else{
                return !dComIfGs_isEventBit(0x3540) ? 0xA3E : 0xA41;
            }
        }
    }
}

/* 00001718-00001738       .text getMsg_YM2_3__11daNpc_Ym1_cFv */
unsigned long daNpc_Ym1_c::getMsg_YM2_3() {
    getMsg_YM2_2();
}

/* 00001738-000017DC       .text getMsg__11daNpc_Ym1_cFv */
u32 daNpc_Ym1_c::getMsg() {
    u32 o_retval = 0;
    switch(mStaff){
        case 0:
            o_retval = getMsg_YM1_0();
            break;
        case 1:
            o_retval = getMsg_YM1_1();
            break;
        case 2:
            o_retval = getMsg_YM2_0();
            break;
        case 3:
            o_retval = getMsg_YM2_1();
            break;
        case 4:
            o_retval = getMsg_YM2_2();
            break;
        case 5:
            o_retval = getMsg_YM2_3();
            break;
    }
    return o_retval;
}

/* 000017DC-0000182C       .text eventOrder__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::eventOrder() {
    if(m8AC == 1 || m8AC == 2){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(m8AC == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } 
}

/* 0000182C-0000186C       .text checkOrder__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()){
        return;
    }
    if(!eventInfo.checkCommandTalk()){
        return;
    }
    if(m8AC != 1 && m8AC != 2){
        return;
    }
    m8AC = 0;
    m8A3 = 1;
    return;
}

/* 0000186C-00001A08       .text set_collision_sp__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::set_collision_sp() {
    /* Nonmatching */
    f32 fVar3;
    f32 fVar2;
    cXyz collisionPos;
    Vec local_48;

    if(m8A3 != 0){
        return;
    }
    switch(m8AB){

        case 1:
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(current.angle.y);
            local_48.x = 0;
            local_48.y = 0;
            local_48.z = 20.0;
            fVar2 = 60.0;
            fVar3 = 140.0;
            mDoMtx_stack_c::multVec(&local_48,&collisionPos);
            break;
        case 5:
        case 6:
        case 7:
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(current.angle.y);
            local_48.x = 0;
            local_48.y = 0;
            local_48.z = 60.0;
            fVar2 = 80.0;
            fVar3 = 150.0;
            mDoMtx_stack_c::multVec(&local_48,&collisionPos);
            break;
        default:
            collisionPos.set(current.pos.x,current.pos.y,current.pos.z);
            fVar2 = 60.0;
            fVar3 = 180.0;
            break;
            
    }
    mCyl.SetC(current.pos);
    mCyl.SetR(fVar2);
    mCyl.SetH(fVar3);
    dComIfG_Ccsp()->Set(&mCyl);

}

/* 00001A08-00001B24       .text set_cutGrass__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::set_cutGrass() {
    /* Nonmatching */
}

/* 00001B24-00001B5C       .text chk_BlackPig__11daNpc_Ym1_cFv */
bool daNpc_Ym1_c::chk_BlackPig() {
    /* Nonmatching */
}

/* 00001B5C-00001B8C       .text chk_nbt_attn__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::chk_nbt_attn() {
    /* Nonmatching */
}

/* 00001B8C-00001C24       .text chk_talk__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::chk_talk() {
    /* Nonmatching */
}

/* 00001C24-00001C64       .text chk_parts_notMov__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::chk_parts_notMov() {
    /* Nonmatching */
}

/* 00001C64-00001DD0       .text lookBack__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::lookBack() {
    /* Nonmatching */
}

/* 00001DD0-00001E50       .text chkAttention__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::chkAttention() {
    /* Nonmatching */
}

/* 00001E50-00001F5C       .text setAttention__11daNpc_Ym1_cFb */
void daNpc_Ym1_c::setAttention(bool) {
    /* Nonmatching */
}

static char* strings[] = {"Halt","Ym","DUMMY",};
#if VERSION == VERSION_DEMO
static char* stringsdemo = {"若者"};
#endif
static char* strings2[] = {"a_mdl_dat != 0","head","m_hed_jnt_num >= 0","backbone","m_bbone_jnt_num >= 0","handL","m_hnd_L_jnt_num >= 0","handR","m_hnd_R_jnt_num >= 0"};

/* 00001F5C-00002088       .text decideType__11daNpc_Ym1_cFi */
bool daNpc_Ym1_c::decideType(int i_param1) {
    /* Nonmatching */
    if (mSubType > 0){
        return true;


    }
        mSubType = -1;
        mStaff = -1;

    switch(base.base.mProcName){
        case 0x13E:
            mSubType = 1;
            switch(i_param1){
                case 0:
                    mStaff = 0;
                    break;
                case 1:
                    mStaff = 1;
                    break;
            }
            break;
        case 0x13F:
            mSubType = 2;
            switch(i_param1){
                case 0:
                    mStaff = 2;
                    break;
                case 1:
                    mStaff = 3;
                    break;
                case 2:
                    mStaff = 4;
                    break;
                case 3:
                    mStaff = 5;
                    break;
            }
    }

    strcpy(mArcName,"Ym");
    return mSubType != -1 && mStaff != -1;

}

/* 00002088-00002128       .text privateCut__11daNpc_Ym1_cFi */
void daNpc_Ym1_c::privateCut(int i_param_1) {
    /* Nonmatching */

}

/* 00002128-0000214C       .text endEvent__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::endEvent() {
    /* Nonmatching */
}

/* 0000214C-00002184       .text isEventEntry__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::isEventEntry() {
    /* Nonmatching */
}

/* 00002184-000021D4       .text event_proc__11daNpc_Ym1_cFi */
void daNpc_Ym1_c::event_proc(int) {
    /* Nonmatching */
}

/* 000021D4-00002280       .text set_action__11daNpc_Ym1_cFM11daNpc_Ym1_cFPCvPvPv_iPv */
void daNpc_Ym1_c::set_action(int (daNpc_Ym1_c::*)(void*), void*) {
    /* Nonmatching */
}

/* 00002280-00002324       .text setStt__11daNpc_Ym1_cFSc */
void daNpc_Ym1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 00002324-00002448       .text chk_areaIN__11daNpc_Ym1_cFf4cXyz */
void daNpc_Ym1_c::chk_areaIN(float, cXyz) {
    /* Nonmatching */
}

/* 00002448-000025B8       .text kari_1__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::kari_1() {
    /* Nonmatching */
}

/* 000025B8-00002770       .text wait_1__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::wait_1() {
    /* Nonmatching */
}

/* 00002770-00002958       .text wait_2__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::wait_2() {
    /* Nonmatching */
}

/* 00002958-00002BA0       .text talk_1__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::talk_1() {
    /* Nonmatching */
}

/* 00002BA0-00002C78       .text turn_1__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::turn_1() {
    /* Nonmatching */
}

/* 00002C78-00002DD4       .text NBTwai__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::NBTwai() {
    /* Nonmatching */
}

/* 00002DD4-00002EFC       .text SITwai__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::SITwai() {
    /* Nonmatching */
}

/* 00002EFC-00002FFC       .text wait_action1__11daNpc_Ym1_cFPv */
int daNpc_Ym1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00002FFC-00003100       .text wait_action2__11daNpc_Ym1_cFPv */
int daNpc_Ym1_c::wait_action2(void*) {
    /* Nonmatching */
}

/* 00003100-00003270       .text wait_action3__11daNpc_Ym1_cFPv */
void daNpc_Ym1_c::wait_action3(void*) {
    /* Nonmatching */
}

/* 00003270-00003324       .text wait_action4__11daNpc_Ym1_cFPv */
void daNpc_Ym1_c::wait_action4(void*) {
    /* Nonmatching */
}

/* 00003324-00003390       .text demo_action1__11daNpc_Ym1_cFPv */
void daNpc_Ym1_c::demo_action1(void*) {
    /* Nonmatching */
}

/* 00003390-000034CC       .text demo__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::demo() {
    /* Nonmatching */
}

/* 000034CC-0000359C       .text shadowDraw__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::shadowDraw() {
    /* Nonmatching */
}

/* 0000359C-000037A0       .text _draw__11daNpc_Ym1_cFv */
BOOL daNpc_Ym1_c::_draw() {
    /* Nonmatching */
}

/* 000037A0-00003A5C       .text _execute__11daNpc_Ym1_cFv */
BOOL daNpc_Ym1_c::_execute() {
    /* Nonmatching */
}

/* 00003A5C-00003AB0       .text _delete__11daNpc_Ym1_cFv */
BOOL daNpc_Ym1_c::_delete() {
    /* Nonmatching */
}

/* 00003AB0-00003BDC       .text _create__11daNpc_Ym1_cFv */
cPhs_State daNpc_Ym1_c::_create() {
    /* Nonmatching */
}

/* 0000405C-00004360       .text bodyCreateHeap__11daNpc_Ym1_cFv */
BOOL daNpc_Ym1_c::bodyCreateHeap() {

    J3DModelData *a_mdl_dat;
    mDoExt_McaMorf *pmVar2;
    a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName,0xA);
    a_mdl_dat->getJointName();
    JUT_ASSERT(0x971,a_mdl_dat != 0);
    pmVar2 = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,NULL,
        -0x1,1.0,0,-1,1,NULL,0x80000,0x15021222);
 
    mpMorf = pmVar2;
    pmVar2 = mpMorf;
    if (pmVar2 == NULL) {
        return 0;
    }
    else if (pmVar2->getModel() == NULL) {
        mpMorf = NULL;
        return 0;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x97F,m_hed_jnt_num >= 0);   
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x981,m_bbone_jnt_num >= 0); 
    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(0x983,m_hnd_L_jnt_num >= 0); 
    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(0x985,m_hnd_R_jnt_num >= 0); 
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((u32)this);
    return TRUE;
}

/* 00004360-00004460       .text headCreateHeap__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::headCreateHeap() {
    /* Nonmatching */
}

/* 00004460-00004534       .text itemCreateHeap__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::itemCreateHeap() {
    /* Nonmatching */
}

/* 00004534-000045F8       .text CreateHeap__11daNpc_Ym1_cFv */
void daNpc_Ym1_c::CreateHeap() {
    /* Nonmatching */
}

/* 000045F8-00004618       .text daNpc_Ym1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ym1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_create();
}

/* 00004618-00004638       .text daNpc_Ym1_Delete__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_Delete(daNpc_Ym1_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_delete();
}

/* 00004638-00004658       .text daNpc_Ym1_Execute__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_Execute(daNpc_Ym1_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_execute();
}

/* 00004658-00004678       .text daNpc_Ym1_Draw__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_Draw(daNpc_Ym1_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_draw();
}

/* 00004678-00004680       .text daNpc_Ym1_IsDelete__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_IsDelete(daNpc_Ym1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ym1_Method = {
    (process_method_func)daNpc_Ym1_Create,
    (process_method_func)daNpc_Ym1_Delete,
    (process_method_func)daNpc_Ym1_Execute,
    (process_method_func)daNpc_Ym1_IsDelete,
    (process_method_func)daNpc_Ym1_Draw,
};

actor_process_profile_definition g_profile_NPC_YM1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_YM1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ym1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_YM1_e,
    /* Actor SubMtd */ &l_daNpc_Ym1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_YM2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_YM2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ym1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_YM2_e,
    /* Actor SubMtd */ &l_daNpc_Ym1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
