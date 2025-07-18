/**
 * d_a_npc_kk1.cpp
 * NPC - Mila (poor)
 */

#include "d/actor/d_a_npc_kk1.h"
#include "SSystem/SComponent/c_counter.h"
#include "c/c_dylink.h"
#include "d/actor/d_a_obj_roten.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_swc00.h"
#include "d/actor/d_a_tama.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "weak_bss_936_to_1036.h" //Needed to align bss

#define SHORT2DEG_ANGLE(deg) ((deg) / (65536.0f / 360.0f))
#define LINKPOS (dComIfGp_getLinkPlayer()->current.pos)







static daNpc_Kk1_HIO_c l_HIO;

#define L_CHECK_SZ 20
fopAc_ac_c* l_check_inf[L_CHECK_SZ];
s32 l_check_wrk;


inline int daNpc_Kk1_c::getSWbit() {
    return this->mSWbit;
}



/* 000000EC-00000150       .text __ct__15daNpc_Kk1_HIO_cFv */
daNpc_Kk1_HIO_c::daNpc_Kk1_HIO_c() {

    static daNpc_Kk1_c::prm_tbl a_prm_tbl[] = {0x2000251C, 0xE002DAE4, 0x00002AF8, 0x0000D508, 0x064004B0, 150.0, 0x000000D2, 0x0028005A,
0x001E0014, 0x00041000, 40.0, 3.0, 0x3E4CCCCD, 0.5, 13.0, 1.0,
0x3DCCCCCD, 10.0, 1.0, 0x3E4CCCCD, 1000.0};
    memcpy(&field_0xC,a_prm_tbl,0x54);
    mNo = -1;
    field_0xA = -1;
    return;
}

char* l_evn_tbl[] = {
    "run_start", 
#if VERSION > VERSION_JPN
    "run_start_2",
#endif
     "catch",
    "get_empty_btl", 
    "bye", 
    "otoboke", 
    "runaway", 
    "bye_2",
};




/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_arg1) {
    daNpc_Kk1_c* user_area;

    if (i_arg1 == 0) {
        user_area = (daNpc_Kk1_c*)j3dSys.mModel->getUserArea();
        if (user_area != NULL) {
            user_area->_nodeCB_Head(i_node, j3dSys.mModel);
        }
    }
    return 1;
}

/* 000001E4-00000304       .text _nodeCB_Head__11daNpc_Kk1_cFP7J3DNodeP8J3DModel */
void daNpc_Kk1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {

    static cXyz a_eye_pos_off(14.0f,18.0f,0.0f);
    u16 joint_number = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(joint_number));
    mDoMtx_stack_c::multVecZero(&field_0x750);
    mDoMtx_stack_c::multVec(&a_eye_pos_off,&field_0x72C);
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(),j3dSys.mCurrentMtx);
    i_model->setAnmMtx(joint_number, mDoMtx_stack_c::now);

}


/* 00000340-0000038C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode *i_node, int param_2) {

  if (param_2 == 0) {
    J3DModel* model = (J3DModel*)j3dSys.mModel;
    if ((J3DModel *)(j3dSys.mModel)->getUserArea() != (J3DModel *)0x0) {
    ((daNpc_Kk1_c*)(model->getUserArea()))->_nodeCB_BackBone(i_node,model);

    }
  }
  return 1;
}

/* 0000038C-0000042C       .text _nodeCB_BackBone__11daNpc_Kk1_cFP7J3DNodeP8J3DModel */
void daNpc_Kk1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    u16 joint_number = static_cast<J3DJoint*>(i_node)->getJntNo();
    MTXCopy(i_model->getAnmMtx(joint_number), mDoMtx_stack_c::now);
    mDoMtx_stack_c::XrotM(this->m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-this->m_jnt.getBackbone_x());

    MTXCopy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
    i_model->setAnmMtx(joint_number, mDoMtx_stack_c::now);
}

/* 0000042C-0000044C       .text CheckCreateHeap__FP10fopAc_ac_c */
static int CheckCreateHeap(fopAc_ac_c* i_npc) {

  return ((daNpc_Kk1_c*)i_npc)->CreateHeap();

}



/* 0000044C-000004EC       .text searchActor_SWC00__FPvPv */
void* searchActor_SWC00(void* i_swc, void* i_kk1) {
    swc00_class* swc_act = (swc00_class*)(i_swc);
    daNpc_Kk1_c* kk1_act = (daNpc_Kk1_c*)(i_kk1);
    if (
        l_check_wrk < L_CHECK_SZ  && fopAc_IsActor(swc_act) && 
        fopAcM_GetName(swc_act) == PROC_SWC00 && daSwc00_getType(swc_act) == 0 &&
        daSwc00_getSw1No(swc_act) == kk1_act->getSWbit()
    ){
        l_check_inf[l_check_wrk] = swc_act;
        l_check_wrk++;
    }
    return NULL;
}
   

/* 000004EC-00000598       .text init_KK1_0__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::init_KK1_0() {

        //Some event                            Daytime                         Sidequest not finished
  if ((dComIfGs_isEventBit(0x2D01)) && ((dKy_daynight_check() == 0) || (dComIfGs_isEventBit(0xe08) == 0))) {
        set_action(&daNpc_Kk1_c::wait_action1,NULL);
        return true;
  }
  else {
        return false;
  }

}





extern dCcD_SrcCyl dNpc_cyl_src;

/* 00000598-000007B0       .text createInit__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::createInit() {
    for (int i = 0; i < EVENTLENGTH; ++i) {

        mEvtIDTbl[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xFF);
    }
    mEventCut.setActorInfo2("Kk1", this);
    mSWbit = base.mParameters >> 8;

    u8 params = base.mParameters >> 0x10;
    if (params != 0xff) {
        mRunPath.setInf(params, current.roomNo, true);
        if (mRunPath.mPath != NULL) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            set_pthPoint(0);
        }
        else {
            return FALSE;
        }
    }
    if (mRunPath.mPath == NULL) {
        return FALSE;
    }
    
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    switch(field_0x820){
        case 0:
            break;
    }

    attention_info.distances[1] = 0xA9;
    attention_info.distances[3] = 0xA9;

    gravity = -4.5f;
    field_0x81A = 0xC;

    
    bool control=0;
    switch(field_0x820){
        case 0:
            control = init_KK1_0();
            break;
        default:
            control = 0;
            break;
    }
    if(control == 0){
        return false;
    }


    mAngle = current.angle;
    shape_angle = mAngle;
    mStts.Init(0xFF, 0xff, this);
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

/* 000007B0-00000918       .text play_animation__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::play_animation() {

    cXyz floatload;
    u32 mtl_snd_id = 0;
    play_btp_anm();


    if (mObjAcch.ChkGroundHit() != 0) {
        mtl_snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    field_0x7B2 = mpMorf->play(&eyePos,mtl_snd_id,dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    if(mpMorf->getFrame() < mAnimeFrame){
        field_0x7B2 = 1;
    }

    mAnimeFrame = mpMorf->getFrame();

    switch(field_0x81A){
        case 8:
            if (mpMorf->checkFrame(4.0) != 0) {

                floatload.set(0.0,-50.0,-15.0);
                setBikon(floatload);
            }
            break;
        case 9:
            if (mpMorf->checkFrame(4.0) != 0) {

                floatload.set(0.0,-50.0,0.0);
                setBikon(floatload);
            }
            break;
    }
    play_eff_anm();
    return;
}

/* 00000918-00000A98       .text setMtx__11daNpc_Kk1_cFb */
void daNpc_Kk1_c::setMtx(bool param_1) {

    mpMorf->mpModel->setBaseScale(scale);
    PSMTXTrans(mDoMtx_stack_c::get(),current.pos.x,current.pos.y,current.pos.z);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    cXyz someFloat1(0.0,120.0,30.0);
    field_0x7F0.entry(field_0x808->getModelData(),field_0x804);
    PSMTXTrans(mDoMtx_stack_c::get(),current.pos.x,current.pos.y,current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::transM(someFloat1.x,someFloat1.y,someFloat1.z);

    field_0x808->setBaseTRMtx(mDoMtx_stack_c::get());

    (field_0x808->calc)();
    mDoExt_bckAnmRemove(field_0x808->getModelData());
    flwAse();
    setAttention(param_1);
    return;
}

/* 00000A98-00000AAC       .text bckResID__11daNpc_Kk1_cFi */
int daNpc_Kk1_c::bckResID(int param_1) {
    static const u32 a_resID_tbl[] = {9,10,11,12,4,5,6,7,1,2,3,8};
    return a_resID_tbl[param_1];

}

/* 00000AAC-00000AC0       .text btpResID__11daNpc_Kk1_cFi */
int daNpc_Kk1_c::btpResID(int param_1) {

    static const u32 a_resID_tbl_2[] = {0x00000011};
    return a_resID_tbl_2[param_1];
}

/* 00000AC0-00000BC4       .text setBtp__11daNpc_Kk1_cFScb */
bool daNpc_Kk1_c::setBtp(signed char param_1, bool param_2) {

  J3DAnmTexPattern *a_btp;  
  J3DModel* pJVar5 = mpMorf->getModel();
  if (param_1 < 0) {
    return false;
  }
  else {
    a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(&mArcName,btpResID(param_1));
    JUT_ASSERT(VERSION_SELECT(563,563,564,564),a_btp != 0);

    field_0x819 = param_1;
    mBtpFrame = 0;
    field_0x6EE = 0;
    return mBtpAnm.init(pJVar5->getModelData(),a_btp,1,0,1.0,0,-1,param_2,0) != 0;
  }

}

/* 00000BC4-00000BE4       .text init_texPttrnAnm__11daNpc_Kk1_cFScb */
bool daNpc_Kk1_c::init_texPttrnAnm(signed char param_1, bool param_2) {
    return setBtp(param_1, param_2);
}

/* 00000BE4-00000C80       .text play_btp_anm__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::play_btp_anm() {


  u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
  if ((field_0x819 != 0) ||
     (cLib_calcTimer(&field_0x6EE) == 0)) {
    mBtpFrame += 1;
    if (mBtpFrame >= frame_max) {
      if (field_0x819 != 0) {
        mBtpFrame = frame_max;
        return;

      }
      else {
        field_0x6EE = cLib_getRndValue(0x3c,0x5a);
        mBtpFrame = 0;
      }
    }
  }
  return;
}

/* 00000C80-00000CFC       .text play_eff_anm__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::play_eff_anm() {

    s16 temp_r5;
    field_0x800 += 1;
    if(field_0x800 >= 0x1E){ 
        field_0x800 = 0x1D;
    }
    temp_r5 = (short)field_0x7DC.getBtkAnm()->getFrameMax(); //TODO: It seems like the short cast is required here.
    field_0x802 += 1;


    if(field_0x802 >= temp_r5){
        field_0x802 = temp_r5 - 1;
    }
    temp_r5 = (short)field_0x7F0.getBckAnm()->getFrameMax();
    field_0x804 += 1;
    if(field_0x804 >= temp_r5){
        field_0x804 = 0x3B;
    }
    return;



}

/* 00000CFC-00000DDC       .text setAnm_anm__11daNpc_Kk1_cFPQ211daNpc_Kk1_c9anm_prm_c */
void daNpc_Kk1_c::setAnm_anm(daNpc_Kk1_c::anm_prm_c* i_anm_ptr) {

    if (i_anm_ptr->field0 < 0 || field_0x81A == i_anm_ptr->field0) {
        return;
    }

    dNpc_setAnmIDRes(mpMorf,i_anm_ptr->fieldC,i_anm_ptr->field4,i_anm_ptr->field8,bckResID(i_anm_ptr->field0),0xFFFFFFFF,&mArcName);
    field_0x81A = i_anm_ptr->field0;
    delBikon();
    delAse();
    field_0x7BE = 1;
    switch(field_0x81A){
        case 1:
        setAse();
        field_0x804 = 0;
        field_0x802 = 0;
        field_0x800 = 0;
        field_0x7BE = 0;
        break;
    }
    this->field_0x7B2 = 0;
    this->field_0x7B3 = 0;
    this->mAnimeFrame = 0.0;



        



}



    static daNpc_Kk1_c::anm_prm_c a_anm_prm_tblNUM[14] = {
        {0,0,0,8.0,1.0,2},
        {1,0,0,8.0,1.0,2},
            {2,0,0,8.0,1.0,2},
            {3,0,0,8.0,1.0,2},
            {4,0,0,8.0,1.0,2},
        {5,0,0,8.0,1.0,2},
        {6,0,0,8.0,1.0,2},
        {7,0,0,8.0,1.0,2},
        {8,0,0,8.0,1.0,0},
        {9,0,0,8.0,1.0,0},
        {10,0,0,8.0,1.0,0},
        {11,0,0,8.0,1.0,0},
        {0,0,0,0.0,0.0,0},
        {0,0,0,0.0,0.0,0},
        
    };
        static daNpc_Kk1_c::anm_prm_c a_anm_prm_tbl2[8] = {
0xFF,0xFF,0000, 0.0, 0.0, 0xFFFFFFFF,
0x00,00,0000, 8.0, 1.0, 0x00000002,
0xFF,0xFF,0000, 0.0, 0.0, 0xFFFFFFFF,
0x03,00,0000, 8.0, 1.0, 0x00000002,
0x00,00,0000, 8.0, 1.0, 0x00000002,
0xFF,0xFF,0000, 0.0, 0.0, 0xFFFFFFFF,
0x00,00,0000, 8.0, 1.0, 0x00000002,
0x00,00,0000, 8.0, 1.0, 0x00000002,

        };
    static daNpc_Kk1_c::anm_prm_c a_anm_prm_tbl3[13] = {
        {0,0,0,8.0,1.0,2},
        {1,0,0,8.0,1.0,2},
            {2,0,0,8.0,1.0,2},
            {3,0,0,8.0,1.0,2},
            {4,0,0,8.0,1.0,2},
        {5,0,0,8.0,1.0,2},
        {6,0,0,8.0,1.0,2},
        {7,0,0,8.0,1.0,2},
8,00,0000, 8.0, 1.0, 0,
9,00,0000, 8.0, 1.0, 0,
10,00,0000, 8.0, 1.0, 0,
10,00,0000, 8.0, 1.0, 0,
11,00,0000, 8.0, 1.0, 0,


    };


/* 00000DDC-00000E4C       .text setAnm_NUM__11daNpc_Kk1_cFii */
void daNpc_Kk1_c::setAnm_NUM(int i_tblIdx, int param_2) {

    if (param_2 != 0) {
    init_texPttrnAnm(a_anm_prm_tblNUM[i_tblIdx].field1,true);
    }
    setAnm_anm(&a_anm_prm_tblNUM[i_tblIdx]);
    return;


}

/* 00000E4C-00000EB8       .text setAnm__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::setAnm() {

    init_texPttrnAnm(a_anm_prm_tbl2[field_0x81C].field1,true);
    setAnm_anm(&a_anm_prm_tbl2[field_0x81C]);
    return;

}

/* 00000EB8-00000EBC       .text chngAnmTag__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::chngAnmTag() {
    return;
}

/* 00000EBC-00000EC0       .text ctrlAnmTag__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::ctrlAnmTag() {
    return;
}

/* 00000EC0-00000FA0       .text chngAnmAtr__11daNpc_Kk1_cFUc */
void daNpc_Kk1_c::chngAnmAtr(unsigned char i_anmNum) {
    fopAc_ac_c* found_actor;
    int search_failed;
    switch(mCurrMsgNo){
        case 0x1CAC:    //Take off! Go away!
            found_actor = searchByID(mPartnerProcID,&search_failed);
            if(found_actor != NULL && search_failed == 0){
                field_0x738 = found_actor->current.pos;
                field_0x738.y += l_HIO.field_0x20 + 200.0f;
                mWhereToLook = 2;
                mLockBodyRotation = 1;
                field_0x7A2 = l_HIO.field_0x2E;
            }
            break;
    }
    if((i_anmNum == mAnimationNum) || (i_anmNum > 0xD)){
        return;
    }

    mAnimationNum = i_anmNum;
    setAnm_ATR();

    return;

}

/* 00000FA0-00001080       .text ctrlAnmAtr__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::ctrlAnmAtr() {

    switch(mAnimationNum){
    case 8:
        if ((field_0x7B2 != '\0')) {
            current.angle.y += 0x8000;
            setAnm_NUM(0,1);
            mpMorf->setMorf(0.0);
            mAnimationNum = 0;
        }
    case 9:
    case 12:
        return;
    case 11:
        if (this->field_0x7B2 != '\0') {
            setAnm_NUM(6,1);
            this->mAnimationNum = 6;
            return;
        }
        break;
    case 10:
        if(field_0x7B2 != 0){
            setAnm_NUM(0,1);
            mAnimationNum = 0;
        }

        break;
    }
}

/* 00001080-000010E4       .text setAnm_ATR__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::setAnm_ATR() {

  init_texPttrnAnm(a_anm_prm_tbl3[mAnimationNum].field1,true);
  setAnm_anm(((daNpc_Kk1_c::anm_prm_c *)(&a_anm_prm_tbl3[mAnimationNum])));
  return;
}

/* 000010E4-000011A0       .text anmAtr__11daNpc_Kk1_cFUs */
void daNpc_Kk1_c::anmAtr(unsigned short param_1) {

        u8 uVar1;
        switch(param_1){
            case 6:

                if (field_0x822 == 0) {
                    chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                    field_0x822 += 1;
                }
                uVar1 = dComIfGp_getMesgAnimeTagInfo();
                if (( uVar1 != 0xFF) &&
                (uVar1 != field_0x818)) {
                    dComIfGp_clearMesgAnimeTagInfo();
                    field_0x818 = uVar1;
                    chngAnmTag();
                }
                break;
            case 14:
                field_0x822 = 0;
                break;
        }
        ctrlAnmAtr();
        ctrlAnmTag();   //Does nothing

}

/* 000011A0-0000149C       .text next_msgStatus__11daNpc_Kk1_cFPUl */
u16 daNpc_Kk1_c::next_msgStatus(unsigned long* param_1) {

    s32 msg_selection;
    
    u16 message_outcome = 0xF;   //0xF = Continue. 0x10 = Run Away.
    switch (*param_1) { //TODO: Make Enum.
    case 0x1C85:    //Oh! Hi! We meet again! ...What?! Of course! Honestly! I'm working! How dare you suggest that! I'm done with all that sneaking around in the dark. In fact, I head off to a faraway island to work in the evenings now, so I won't be seeing you at night anymore! 
        *param_1 = 0x1C86;
        break;
    case 0x1C86:    //All right? Well, all right. Now, you're keeping me from doing my job, so could you please step aside?
        *param_1 = 0x1CA7;
        break;
    case 0x1CA7:    //This way to the only stall with extra-fun, happy things for sale!
        *param_1 = 0x1CA8;
        break;
    case 0x1C88:    //Hey, you! Come on! Use your head! You can't just stand there like that! You're in my way! Can't you move? 
        *param_1 = 0x1C89;
        break;
    case 0x1C89:    //Oops! That won't do! That won't do at all! Already I'm back to my old habits... I'm terribly sorry! Really, I am!  
        *param_1 = 0x1C8A;
        break;
    case 0x1C8A:    //Umm... 
        *param_1 = 0x1CA9;
        break;
    case 0x1C8B:    //Shh! Shhh! 
        *param_1 = 0x1CAC;  //Take off! Go away! 
        field_0x7B8 = 1;
        break;
    case 0x1C8D:    //Y-Y-You startled me...! Wh-Wh-What do you want? M-M-My heart is racing! You scared me! 
        *param_1 = 0x1C8E;
        break;
    case 0x1C8E:    //Wait... Are you...? ...the kind of creep who goes around at night scaring people?! That's just plain mean! 
        *param_1 = 0x1C8F;
        break;
    case 0x1C8F:    //Just who do you think you are, anyway?!
        switch (mpCurrMsg->mSelectNum) {                  
        case 0:     //An ally of justice!                        
            *param_1 = 0x1C90;
            break;
        case 1:     //A night-creeping rascal!                            
            *param_1 = 0x1CA5;
            mMuuruBadResponse += 1;
            break;
        }
        break;
    case 0x1CA5:    //...Hmph! That's not funny, you know. I can't believe you'd try to make a joke out of this! You're an awful boy!
        *param_1 = 0x1C8F;
        break;
    case 0x1C90:    //A...what!?! An... An ally of justice?! I-I'm not a thief! I swear! I haven't stolen anything! Well, yet. Please let me go! It was just an impulse! That's all! Just a bad idea!
        *param_1 = 0x1C91;
        break;      
    case 0x1C91:    //...Why won't you say anything? Does this mean you're mad at me? Could you at least listen to the circumstances in my life that led up to this moment? Please, you owe me that much!
        switch (mpCurrMsg->mSelectNum) {                 
        case 0:     //Sure                
            *param_1 = 0x1C93;
            break;
        case 1:    //Quiet, you!                             
            *param_1 = 0x1C92;
            mMuuruBadResponse += 1;
            break;
        }
        break;
    case 0x1C92:    //...What?! Why, that's just cruel! You awful boy! Sometimes there are odd circumstances that make people do what they do! How could you be so close-minded? 
        *param_1 = 0x1C91;
        break;
    case 0x1C93:    //I...was once the richest little debutante in this town. Did you know that? But one day, a monstrous bird came and took me away to a terrible place called the Forsaken Fortress, where I was locked up and held captive. Oh, it was awful! My father spent every last Rupee in his coffers in an attempt to get me rescued. 
        *param_1 = 0x1C94;
        break;
    case 0x1C94:    //That's right! Every last bit of our family fortune, gone... That was when my life of poverty began. Now, every day, from morning until night, I'm busy working for the open-air shop. So, as you can see, at least I'm trying to settle into my poor lifestyle. Doesn't that just tug at your heart strings? What do you say about the tragic events in my pitiable life? 
        switch (mpCurrMsg->mSelectNum) {                  
        case 0:     //That's terrible                                   
            *param_1 = 0x1C96;
            break;
        case 1:     //That's kind of funny                              
            *param_1 = 0x1C95;
            mMuuruBadResponse += 1;
            break;
        }
        break;
    case 0x1C95:    //...... 
        *param_1 = 0x1C96;
        break;
    case 0x1C96:    //And to make matters worse, for some reason I still can't figure out, that slob Maggie, who was the poorest girl in town, suddenly got filthy rich! Maggie, of all people! It makes me so mad that I want to do something terrible! Grrrr! 
        *param_1 = 0x1C97;
        break;
    case 0x1C97:    //Do you understand my plight? 
        switch (mpCurrMsg->mSelectNum) {             
        case 0:     //Very well                      
            *param_1 = 0x1C98;
            break;
        case 1:     //Not at all
            *param_1 = ((mMuuruBadResponse > 1) ? 1 : 2)+0x1C99;            
        }
        break;
    case 0x1C98:    //...Then you'll let me go?! 
        msg_selection = mpCurrMsg->mSelectNum;
        switch ((s32) msg_selection) {              
        case 0:     //Unfortunately, no                         
            *param_1 = 0x1C99;
            break;
        case 1:     //I'll let you go                          
            message_outcome = 0x10;
            break;
        }
        break;
    case 0x1C99:    //But...why not?!? 
        switch (mpCurrMsg->mSelectNum) {                
        case 0:     //Because I'm honest 
            *param_1 = ((mMuuruBadResponse > 1) ? 1 : 2)+0x1C9B;       
            break;
        case 1:     //Because I like you
            *param_1 = 0x1C9A;
        }
        break;
       //0x1C9A       ...Hah! You awful boy! I was honest with you, too! And now I'm just angry! Good-bye! 
    case 0x1C9B:    //...Ah hee hee hee hee! I'm sorry! I guess it was a little too complicated for a KID to understand! 
        *param_1 = 0x1C9D;
        break;
       //0x1C9C       ...Oh. That's...really annoying! You know? I just remembered! I have something very important that I'm supposed to be doing. I'll be RIGHT back, so can you just wait here for me? It'll only take a second!  
    case 0x1C9D:    //It's true... I know I'm quibbling over nothing... But being so poor weakens a person's very soul... But...it's time I quit making silly excuses for myself!
        *param_1 = 0x1C9E;
        break;
    case 0x1C9E:    //Thank you so much... 
        *param_1 = 0x1CAA;
        break;
    case 0x1CAA:   //Thanks to you, I didn't have to sink down to the level of a common thief. I will never do anything like that again! Ahhhh... What an amazing feeling! I've let all of my worries out of my heart. Wow! I actually feel refreshed! 
        *param_1 = 0x1C9F;
        break;
    case 0x1C9F:   //Let me at least thank you. Please take this! 
        message_outcome = 0x10;
        break;
    case 0x1CA1:   //Don't look at me like that! I didn't steal it! It washed up on the shore, so I picked it up. Don't tease me like that! It's a tiny bottle made of crystal-clear glass... It's so beautiful. I wish my soul could be that beautiful... 
        *param_1 = 0x1CA2;
        break;
    case 0x1CA2:   //Oh! What am I saying? When you live in poverty, you can say the cheesiest things without blinking an eye. ...Hmph! 
        *param_1 = 0x1CA3;
        break;
    case 0x1CA3:   //So, umm...I guess I should go soon. My father will start worrying. 
        *param_1 = 0x1CA4;
        break;
    case 0x1CA4:   //Good-bye, little ally of justice! ...and good luck to you. 
        *param_1 = 0x1CAB; //'Bye! Thanks for tonight! 
        break;
    default:
        message_outcome = 0x10;  
        break;
    }
    return message_outcome;
}

/* 0000149C-00001534       .text getMsg_KK1_0__11daNpc_Kk1_cFv */
u32 daNpc_Kk1_c::getMsg_KK1_0() {

   if (dKy_daynight_check() == 1) { //If Night
      if (field_0x7BA) {

          field_0x7BA = 0;
          return 0x1CA1;                         //Don't look at me like that! I didn't steal it! It washed up on the shore, so I picked it up. Don't tease me like that! It's a tiny bottle made of crystal-clear glass... It's so beautiful. I wish my soul could be that beautiful...
      }
      else {
          return 0x1C8B;                         //Shh! Shhh!
      }
   }
   else {                           //If Day
      if (!dComIfGs_isEventBit(0xE08)) {      //If Sidequest is available
            if(dComIfGs_isEventBit(0xE10)){   //If working at shop
                return 0x1C87;                   //This way to the only stall with extra-fun happy things for sale! Your happiness is guaranteed! Fun awaits you! Step right up! Stop by! 
            }else{                               //If walking
                return 0x1C88;                   //Hey, you! Come on! Use your head! You can't just stand there like that! You're in my way! Can't you move? 
            }
      }
      else {
          return 0x1C85;                         //Oh! Hi! We meet again! ...What?! Of course! Honestly! I'm working! How dare you suggest that! I'm done with all that sneaking around in the dark. In fact, I head off to a faraway island to work in the evenings now, so I won't be seeing you at night anymore! 
      }
   }
}

/* 00001534-00001570       .text getMsg__11daNpc_Kk1_cFv */
u32 daNpc_Kk1_c::getMsg() {
    u32 result = 0;
    switch((int)field_0x820){
        case 0:
            result = getMsg_KK1_0();
            break;
    }
    return result;
}

/* 00001570-000015FC       .text eventOrder__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::eventOrder() {
    char event_state = field_0x81B; //Event state?
    if ((event_state == 1) || (event_state == 2)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(field_0x81B == 1){
            fopAcM_orderSpeakEvent(this);
        }
    }else if (event_state >= 0x03){
        mEvtIDIdx = (event_state - 3);
        fopAcM_orderOtherEventId(this,mEvtIDTbl[mEvtIDIdx],0x00ff,0xffff,0,1);

    }
}
/* 000015FC-000016DC       .text checkOrder__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::checkOrder() {

    if(eventInfo.checkCommandDemoAccrpt()){
        if(dComIfGp_evmng_startCheck(mEvtIDTbl[mEvtIDIdx]) && field_0x81B >= 0x03){
            switch(mEvtIDIdx){
                case BYE:
                    setAnm_NUM(0,1);
                    break;
                case GET_EMPTY_BTL:
                case OTOBOKE:
                default:
                    break;
            }

            field_0x81B = 0;
            mAnimationNum = -1;
            field_0x818 = -1;
        };

    }
    else{
        if((checkCommandTalk())&&((field_0x81B == 1) ||(field_0x81B == 2))){
            field_0x81B = 0;
            field_0x7C3 = 1;
        }
    }

}

/* 000016DC-00001774       .text chk_talk__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chk_talk() {
    bool o_return;
    if(dComIfGp_event_chkTalkXY()){
        o_return = true;
        if(dComIfGp_evmng_ChkPresentEnd() != 0){
            field_0x7B4 = dComIfGp_event_getPreItemNo();
            o_return = true;
        }else{
            o_return = false;
        }
    }else{
        field_0x7B4 = -1;
        o_return = true;
    }
    return o_return;
}

/* 00001774-000017B4       .text chk_parts_notMov__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chk_parts_notMov() {
    bool o_return = false;
    if((mLookBackHeadY != m_jnt.getHead_y())||
    (mLookBackBackboneY != m_jnt.getBackbone_y())||
    (mLookBackAngleY != current.angle.y)){
        o_return = true;
    }
    return o_return;

}

/* 000017B4-00001808       .text searchByID__11daNpc_Kk1_cFUiPi */
fopAc_ac_c* daNpc_Kk1_c::searchByID(fpc_ProcID i_actor, int* i_searchFailed) {
    fopAc_ac_c *search_actor;
    search_actor = NULL;
    *i_searchFailed = 0;
    if(!fopAcM_SearchByID(i_actor,&search_actor)){
        *i_searchFailed = 1;
    }
    return search_actor;
}




/* 00001808-000018B8       .text partner_search_sub__11daNpc_Kk1_cFPFPvPv_Pv */
bool daNpc_Kk1_c::partner_search_sub(void* (*param_1)(void*,void*)) {

    bool o_return = false;
    mPartnerProcID = -1;
    l_check_wrk = 0;

    for(int i = 0; i != 0x14; i++){
        l_check_inf[i] = 0x0000;
    }
    fpcEx_Search(*param_1, this);
    if(l_check_wrk != 0){
        mPartnerProcID = fopAcM_GetID(l_check_inf[0]);
        o_return = true;

    }

    return o_return;
}

/* 000018B8-00001924       .text partner_search__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::partner_search() {

    bool found_partner;
    if(field_0x821 == 1){

        switch(field_0x820){


            case 0:
                found_partner = partner_search_sub(searchActor_SWC00);
                break;
            default:
                found_partner = 1;
        }
        if(found_partner){
            field_0x821 += 1;
        }
    }
    return;
}


/* 00001924-00001B10       .text lookBack__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::lookBack() {

    mLookBackHeadY = m_jnt.getHead_y();
    mLookBackBackboneY = m_jnt.getBackbone_y();
    mLookBackAngleY = current.angle.y;
    cXyz vec1;
    cXyz vec2 = current.pos;
    vec2.y = eyePos.y;
    
    vec1.setall(0.0);
    
    int Int1;
    fopAc_ac_c *pActor;
    cXyz* vecPtr1 = NULL;
    s16 targetY = current.angle.y;
    s8 state = mWhereToLook;
    bool someBool = mLockBodyRotation;
    switch(state){
        case 1: //Look ahead
            field_0x738 = dNpc_playerEyePos(-20.0);
            vec1 = field_0x738;
            vecPtr1 = &vec1;
            break;
        case 2: //Look in same direction?
            vec1 = field_0x738;
            vecPtr1 = &vec1;
            break;
        case 3: //??
            targetY = field_0x7AC;
            break;
        case 4: //??
            pActor = searchByID(field_0x700,&Int1);
            if (pActor != NULL && Int1 == 0){
                field_0x738 = pActor->current.pos;
                field_0x738.y = pActor->eyePos.y;
                vec1 = field_0x738;
                vecPtr1 = &vec1;      
            }
            break;
        case 5:     //Kyoroyoro
            kyorokyoro();
            vec1 = field_0x738;
            vecPtr1 = &vec1;
            break;
    }
    m_jnt.lookAtTarget_2(&current.angle.y,vecPtr1,vec2,targetY,l_HIO.field_0x1E,someBool);
    return;

}

/* 00001B10-00001B90       .text chkAttention__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chkAttention() {
    fopAc_ac_c* npcPtr;
    if((dComIfGp_getAttention().LockonTruth()) != 0){
        npcPtr = dComIfGp_getAttention().LockonTarget(0);
        return this == npcPtr;

    }else{
        npcPtr = dComIfGp_getAttention().ActionTarget(0);
        return this==npcPtr;
    }


}

/* 00001B90-00001BE8       .text setAttention__11daNpc_Kk1_cFb */
void daNpc_Kk1_c::setAttention(bool i_attn_flag) {

    f32 f1 = current.pos.z; 
    f32 f2 = current.pos.y + l_HIO.field_0x20;   
    f32 f3 = current.pos.x;

    attention_info.position.set(f3,f2,f1);

 
    if(!field_0x778 && !i_attn_flag){return;}

    f2 = field_0x72C.z;
    f1 = field_0x72C.y;

    eyePos.set(field_0x72C.x,f1,f2);

}

/* 00001BE8-00001C70       .text decideType__11daNpc_Kk1_cFi */
bool daNpc_Kk1_c::decideType(int) {
    bool o_retval;
    if(field_0x81F > 0){
        o_retval = true;
    }
    else{
        field_0x81F = 1;
        field_0x820 = 0;
        strcpy(&mArcName,"Kk");
        o_retval = false;
        if((field_0x81F != -1) && (field_0x820 != -1)){
            o_retval = true;
        }
    }
    return o_retval;
}

/* 00001C70-00001D10       .text cut_init_RUN_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUN_START(int param_1) {
    fopAc_ac_c* a_actor;

    int idArray[2];
    a_actor = searchByID(mPartnerProcID,idArray);

    JUT_ASSERT(VERSION_SELECT(1357,1357,1359,1359),a_actor != 0);


    dComIfGp_event_setItemPartner(a_actor);
    mRunPath.nextIdxAuto();
    return;

}

/* 00001D10-00001DD0       .text cut_move_RUN_START__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_RUN_START() {
    daPy_py_c* pdVar2;
    cXyz runPoint = mRunPath.getPoint(mRunPath.getIdx());
    short target = cLib_targetAngleY(&current.pos,&runPoint);
    cLib_addCalcAngleS(&current.angle.y,target,l_HIO.mScale,l_HIO.mMaxStep,0x80);
    if(current.angle.y == target){
        pdVar2 = g_dComIfG_gameInfo.play.mpPlayer[2];
        pdVar2->cancelOriginalDemo();
        return true;
    }
    return false;


}

/* 00001DD0-00001E58       .text cut_init_RUN__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUN(int i_staffIdx) {

    s32* somePtr = (s32*)dComIfGp_evmng_getMyIntegerP(i_staffIdx,"Timer");
    mTimer = -1;
    if(somePtr != NULL){
        mTimer = *somePtr;
    }
    setAnm_NUM(4,1);
    field_0x7B6 = 1;
    field_0x815 = 2;
    field_0x816 = 0;
    return;
}

/* 00001E58-00001EAC       .text cut_move_RUN__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_RUN() {
    bool r3 = this->event_move(0);

    if (this->mTimer < 0) {
        return r3;  
    }
    return cLib_calcTimer(&this->mTimer) == 0;
}

/* 00001EAC-00001F08       .text cut_init_CATCH_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_CATCH_START(int) {

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    player->onPlayerNoDraw();
    setAnm_NUM(8,1);
    mpMorf->setMorf(0.0);

}

/* 00001F08-00001F2C       .text cut_move_CATCH_START__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_CATCH_START() {
    if(field_0x7B2){
        field_0x778 = 0;
        return true;
    }
    return false;
}

/* 00001F2C-00001FAC       .text cut_init_CATCH_END__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_CATCH_END(int param_1) {


    ((daPy_py_c*)dComIfGp_getLinkPlayer())->offPlayerNoDraw();
    current.angle.y += 0x8000;
    setAnm_NUM(0,1);
    mpMorf->setMorf(0.0);
    mWhereToLook = 1;
    mLockBodyRotation = 0;
    m_jnt.mbTrn = true;
    return;


}

/* 00001FAC-00001FB4       .text cut_move_CATCH_END__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_CATCH_END() {
    return true;
}


/* 00001FB4-000022BC       .text cut_init_TRN__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_TRN(int) {
    if(field_0x816 != 5){
        u8 currentPoint = mRunPath.mCurrPointIndex;
        if((currentPoint >= 0x19)&&(currentPoint <= 0x28)){
            u8 sp58[] = {
                0x28, 0x27, 0x26, 0x25,
                0x24, 0x23, 0x22, 0x21,
                0x22, 0x23, 0x24, 0x25,
                0x26, 0x27, 0x28, 0x29,
            };

            mRunPath.mCurrPointIndex = sp58[currentPoint-0x19];
            mWhereToLook = 0;
            mLockBodyRotation = 1;
            return;
        }
        mRunPath.setNearPathIndx(&LINKPOS,100);
        u8 linkPathIndex = mRunPath.mCurrPointIndex;

        mRunPath.setNearPathIndx(&current.pos,100);
        u8 muuruPathIndex = mRunPath.mCurrPointIndex;
        s16 maxPoint = mRunPath.maxPoint();
        s16 midpointIndexFloat = maxPoint / 2.0f + 0.5f; 

        if(muuruPathIndex > linkPathIndex){
            linkPathIndex += mRunPath.maxPoint();
        }

        s16 r26 = linkPathIndex - muuruPathIndex;
        if(r26 > midpointIndexFloat){
            r26 -= maxPoint;
        }
        mRunPath.mCurrPointIndex = currentPoint;
        bool bVar10 = false;
        if (r26 == 0){
            cXyz muuruPoint = mRunPath.getPoint(mRunPath.mCurrPointIndex);
            f32 muuruDistance = (current.pos - muuruPoint).absXZ();
            f32 linkDistance = (LINKPOS - muuruPoint).absXZ();

            bVar10 = (linkDistance < muuruDistance);
        }
        if(r26 > 0 || bVar10){
            mRunPath.decIdxAuto();
            mRunPath.decIdxAuto();
            mRunPath.mbGoingForwards ^=  1;
        }
    }
    mWhereToLook = 0;
    mLockBodyRotation = 1;
}

/* 000022BC-00002364       .text cut_move_TRN__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_TRN() {
    cXyz run_point = mRunPath.getPoint(mRunPath.mCurrPointIndex);
    s16 target = cLib_targetAngleY(&current.pos,&run_point);
    cLib_addCalcAngleS(&current.angle.y,target,l_HIO.mScale,l_HIO.mMaxStep,0x80);
    if(current.angle.y == target){
        shape_angle.y = current.angle.y;
        return true;
    }
    return false;

}

/* 00002364-00002388       .text cut_init_BYE_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_BYE_START(int i_unused_param) {

    ((daPy_py_c*)dComIfGp_getLinkPlayer())->onPlayerNoDraw();
    field_0x7BB = 1;
    return;
}

/* 00002388-00002390       .text cut_move_BYE_START__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_BYE_START() {
    return true;
}

/* 00002390-00002490       .text cut_init_BYE__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_BYE(int param_1) {

    s32* timer_ptr = (s32*)dComIfGp_evmng_getMyIntegerP(param_1,"Timer");
    s32* delay_ptr = (s32*)dComIfGp_evmng_getMyIntegerP(param_1,"Delay");                   
    s32* prm_0_ptr = (s32*)dComIfGp_evmng_getMyIntegerP(param_1,"prm_0");    

  mTimer = 0x1E;

  if(timer_ptr != NULL){
    mTimer = *timer_ptr;
  }
  field_0x79A = -1;
  if(delay_ptr != NULL){
    field_0x79A = *delay_ptr;
  }
  mPrm0 = 0;
  if(prm_0_ptr != NULL){
    mPrm0 = *prm_0_ptr;
  }
  setAnm_NUM(4,1);
  field_0x815 = 2;
  field_0x7B6 = 1;
  return;
}

/* 00002490-00002568       .text cut_move_BYE__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_BYE() {

    event_move(false);
    if (field_0x79A > 0) {
        if (cLib_calcTimer(&field_0x79A) == 0) {
            ((daPy_py_c*)dComIfGp_getLinkPlayer())->setPlayerPosAndAngle(&LINKPOS,-0x3217); //TODO: Unused in Debug Map
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
            player->changeOriginalDemo();

            ((daPy_py_c*)dComIfGp_getLinkPlayer())->changeDemoMode(daPy_demo_c::DEMO_UNK09_e);
            ((daPy_py_c*)dComIfGp_getLinkPlayer())->changeDemoParam0(0x3217);
        }
    }
    if (cLib_calcTimer(&mTimer) == 0) {
        if (mPrm0 == 0) {
        speedF = 0.0;
        }
        return true;
    }
    else {
        return false;
    }

}

/* 00002568-000025C8       .text cut_init_BYE_CONTINUE__11daNpc_Kk1_cFi */

void daNpc_Kk1_c::cut_init_BYE_CONTINUE(int i_staffIdx) {
    s32* timer_ptr = (s32*)dComIfGp_evmng_getMyIntegerP(i_staffIdx,"Timer");
    mTimer = 0x1E;
    if(timer_ptr != NULL){
        mTimer = *timer_ptr;
    }

    return;

}

/* 000025C8-00002620       .text cut_move_BYE_CONTINUE__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_BYE_CONTINUE() {

    this->event_move(0);
    if (cLib_calcTimer(&this->mTimer) == 0) {
        speedF = 0.0;
        return true;  
    }
    return false;
}

/* 00002620-000026BC       .text cut_init_BYE_END__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_BYE_END(int i_unusedParam) {

    ((daPy_py_c*)dComIfGp_getLinkPlayer())->changeOriginalDemo();
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->changeDemoMode(daPy_demo_c::DEMO_UNK04_e);
    s16 angle_y = cLib_targetAngleY(&LINKPOS,&current.pos);
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->setPlayerPosAndAngle(&LINKPOS, angle_y);
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->offPlayerNoDraw();
    field_0x7C0 = 1;
}

/* 000026BC-000026C4       .text cut_move_BYE_END__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_BYE_END() {
    return 1;

}

/* 000026C4-000026C8       .text cut_init_PLYER_TRN__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_PLYER_TRN(int) {
    return;
}

/* 000026C8-000026D0       .text cut_move_PLYER_TRN__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_PLYER_TRN() {
    return true;
}

/* 000026D0-00002744       .text cut_init_OTOBOKE__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_OTOBOKE(int) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    player->changeOriginalDemo();
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->changeDemoMode(daPy_demo_c::DEMO_UNK04_e);
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->setPlayerPosAndAngle(&LINKPOS, current.angle.y);
    mTimer = 2;
    return;
}

/* 00002744-00002798       .text cut_move_OTOBOKE__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_OTOBOKE() {
    if ( cLib_calcTimer(&this->mTimer) == 0) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
        player->cancelOriginalDemo();
        return true;  
    }
    return false;

}

/* 00002798-000028A4       .text cut_init_PLYER_MOV__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_PLYER_MOV(int param_1) {

    cXyz cStack_1c;
    s16 sVar3 = cLib_targetAngleY(&current.pos,&LINKPOS);
    sVar3 = sVar3 - current.angle.y;

    if(abs(sVar3)>0x2000){
        dComIfGp_evmng_setGoal(&LINKPOS);
    }else{
        cXyz local_28;
        local_28.setall(0.0);
        s32 sVar1 = (s16)((sVar3>0)?0x2800:-0x2800);
        int added = current.angle.y+sVar1; //TODO: Necessary unused instruction?
        mDoMtx_stack_c::transS(current.pos.x,current.pos.y,current.pos.z);
        mDoMtx_stack_c::YrotM(current.angle.y+sVar1);
        local_28.z = 150.0;
        mDoMtx_stack_c::multVec(&local_28,&cStack_1c);
        dComIfGp_evmng_setGoal(&cStack_1c);
    }
    return;
}

/* 000028A4-000028AC       .text cut_move_PLYER_MOV__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_PLYER_MOV() {
    return true;

}

/* 000028AC-00002A40       .text cut_init_RUNAWAY_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUNAWAY_START(int param_1) {



    s32* puVar2 = (s32*)dComIfGp_evmng_getMyIntegerP(param_1,"Timer");

    ((daPy_py_c*)dComIfGp_getLinkPlayer())->changeOriginalDemo();
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->changeDemoMode(daPy_demo_c::DEMO_UNK04_e);

    short sVar4 = cLib_targetAngleY(&LINKPOS,&current.pos);
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->setPlayerPosAndAngle(&LINKPOS,sVar4);
    s16 r29=cLib_targetAngleY(&current.pos,&LINKPOS);
    shape_angle.y = r29 + 0x8000;

    

    field_0x7BF = 1;
    speedF = 0.0;
    m_jnt.setHead_y(0);
    m_jnt.setHead_x(0);    
    m_jnt.setBackBone_y(0);
    m_jnt.setBackBone_x(0);

    mWhereToLook = 0;
    if (abs((s16)(r29 - current.angle.y)) > 0x3800) {
        current.angle.y = r29 + 0x8000;

        setAnm_NUM(8,1);

    }
    else {

    cXyz local_28;
    local_28.set(0.0,-50.0,0.0);

    mTimer = 0x26;
    if (puVar2 != NULL) {
      mTimer = *puVar2;
    }
    current.angle.y = r29;
    setAnm_NUM(0,1);

    setBikon(local_28);
  }
  return; 
}

/* 00002A40-00002AD0       .text cut_move_RUNAWAY_START__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_RUNAWAY_START() {
    if(field_0x81A == 8){
        if(field_0x7B2 != 0){
            current.angle.y = cLib_targetAngleY(&current.pos,&LINKPOS);
            setAnm_NUM(0,1);
            mpMorf->setMorf(0.0);
            return true;
        }else{
            return false;
        }
    }else{
      return true;
    }
}

/* 00002AD0-00002B08       .text cut_init_RUNAWAY_END__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUNAWAY_END(int) {
    ((daPy_py_c*)dComIfGp_getLinkPlayer())->offPlayerNoDraw();
    field_0x7B6 = 0;
    speedF = 0.0;
    field_0x7C0 = 1;
    return;
}

/* 00002B08-00002B10       .text cut_move_RUNAWAY_END__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::cut_move_RUNAWAY_END() {
    return true;
}

/* 00002B10-00002D98       .text privateCut__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::privateCut(int param_1) {

    static char* a_cut_tbl[14] = {
        "RUN_START",
        "RUN",
        "CATCH_START",
        "CATCH_END",
        "TRN",
        "BYE_START",
        "BYE",
        "BYE_END",
        "PLYER_TRN",
        "OTOBOKE",
        "PLYER_MOV",
        "RUNAWAY_START",
        "RUNAWAY_END",
        "BYE_CONTINUE",

    };
  int uVar2;

  bool uVar1;
  
  if (param_1 != -1) {
    uVar2 = dComIfGp_evmng_getMyActIdx(param_1,a_cut_tbl,0xe,1,0);
    mCutsceneIndex = uVar2;
    if (mCutsceneIndex == CUT_END) {
        dComIfGp_evmng_cutEnd(param_1);
    }
    else {
      if (dComIfGp_evmng_getIsAddvance(param_1)) {
        switch(mCutsceneIndex) {
        case RUN_START:
          cut_init_RUN_START(param_1);
          break;
        case CUT_RUN:
          cut_init_RUN(param_1);
          break;
        case CUT_CATCH_START:
          cut_init_CATCH_START(param_1);
          break;
        case CUT_CATCH_END:
          cut_init_CATCH_END(param_1);
          break;
        case CUT_TRN:
          cut_init_TRN(param_1);
          break;
        case CUT_BYE_START:
          cut_init_BYE_START(param_1);
          break;
        case CUT_BYE:
          cut_init_BYE(param_1);
          break;
        case CUT_BYE_END:
          cut_init_BYE_END(param_1);
          break;
        case CUT_PLYER_TRN:
          cut_init_PLYER_TRN(param_1);
          break;
        case CUT_OTOBOKE:
          cut_init_OTOBOKE(param_1);
          break;
        case CUT_PLYER_MOV:
          cut_init_PLYER_MOV(param_1);
          break;
        case CUT_RUNAWAY_START:
          cut_init_RUNAWAY_START(param_1);
          break;
        case CUT_RUNAWAY_END:
          cut_init_RUNAWAY_END(param_1);
          break;
        case CUT_BYE_CONTINUE:
          cut_init_BYE_CONTINUE(param_1);
        }
      }
      switch(this->mCutsceneIndex) {
      case RUN_START:
        uVar1 = cut_move_RUN_START();
        break;
      case CUT_RUN:
        uVar1 = cut_move_RUN();
        break;
      case CUT_CATCH_START:
        uVar1 = cut_move_CATCH_START();
        break;
      case CUT_CATCH_END:
        uVar1 = cut_move_CATCH_END();
        break;
      case CUT_TRN:
        uVar1 = cut_move_TRN();
        break;
      case CUT_BYE_START:
        uVar1 = cut_move_BYE_START();
        break;
      case CUT_BYE:
        uVar1 = cut_move_BYE();
        break;
      case CUT_BYE_END:
        uVar1 = cut_move_BYE_END();
        break;
      case CUT_PLYER_TRN:
        uVar1 = cut_move_PLYER_TRN();
        break;
      case CUT_OTOBOKE:
        uVar1 = cut_move_OTOBOKE();
        break;
      case CUT_PLYER_MOV:
        uVar1 = cut_move_PLYER_MOV();
        break;
      case CUT_RUNAWAY_START:
        uVar1 = cut_move_RUNAWAY_START();
        break;
      case CUT_RUNAWAY_END:
        uVar1 = cut_move_RUNAWAY_END();
        break;
      case CUT_BYE_CONTINUE:
        uVar1 = cut_move_BYE_CONTINUE();
        break;
      default:
        uVar1 = 1;
      }
      if ((uVar1 & 0xff) != 0) {
        dComIfGp_evmng_cutEnd(param_1);
      }
    }
  }
  return;
}

/* 00002D98-00002DBC       .text endEvent__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::endEvent() {
    dComIfGp_event_reset();
    mAnimationNum = 0xff;
    field_0x818 = 0xff;
    return;
}

/* 00002DBC-00002DF4       .text isEventEntry__11daNpc_Kk1_cFv */
int daNpc_Kk1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(),NULL,0);

}

/* 00002DF4-00002F80       .text event_proc__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::event_proc(int param_1) {

    if (dComIfGp_evmng_endCheck(mEvtIDTbl[mEvtIDIdx])) {
        s16 idx = mEvtIDIdx;


        switch(idx){
            case RUN_START:
#if VERSION > VERSION_JPN
            case RUN_START_2:
#endif
                setStt(5);
                break;

            case CATCH:

                eventInfo.mEventId = -1;  
                switch(mCurrMsgNo) {
                    case 0x1c99:
                    case 0x1c9b:
                    case 0x1c9d:
                    case 0x1c9e:
                    break;
                case 0x1c9a:
                    this->field_0x81B = EVENTLENGTH + 2;
                    this->mWhereToLook = 0;
                    this->mLockBodyRotation = 1;
                    break;
                case 0x1c98:
                case 0x1c9c:
                    this->field_0x81B = EVENTLENGTH - 1;
                    this->mWhereToLook = 1;
                    this->mLockBodyRotation = 1;
                    break;
                case 0x1c9f:
                    setStt(6);
                    this->field_0x81B = EVENTLENGTH - 2;
                    this->mWhereToLook = 0;
                    this->mLockBodyRotation = 1;
                    break;

                }
                break;

            case GET_EMPTY_BTL:


                field_0x81B = 1;
                dComIfGs_onEventBit(0xE08); //Make sidequest available
                field_0x7BA = 1;
                break;

            case BYE:
            case RUNAWAY:
            case BYE_2:
                fopAcM_delete(this);
                break;
            case OTOBOKE:
                break;
            

        }        
        endEvent();
        return;
    }
    if(mEventCut.cutProc() == 0){
        privateCut(param_1);
    }
}

/* 00002F80-00002FB8       .text checkCommandTalk__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::checkCommandTalk() {

    bool retval = false;

    
    if (eventInfo.checkCommandTalk()){
        retval = true;
        if((field_0x816 == 5)&&(field_0x7A4 != 0)){
            retval = false;
        }
    }
    return retval;

}

/* 00002FB8-00003064       .text set_action__11daNpc_Kk1_cFM11daNpc_Kk1_cFPCvPvPv_iPv */
bool daNpc_Kk1_c::set_action(ActionFunc param_1, void* param_2) {
    if(field_0x6F0 != param_1){
        if(field_0x6F0 != 0){
            field_0x821 = 9;
            (this->*field_0x6F0)(param_2);
        }
        field_0x6F0 = param_1;
        field_0x821 = 0;
        (this->*field_0x6F0)(param_2);
    }
    return 1;
}



/* 00003064-0000311C       .text setStt__11daNpc_Kk1_cFSc */
void daNpc_Kk1_c::setStt(signed char param_1) {

 
 s8 uVar1 = field_0x81C;
 field_0x81C = param_1;
 switch((s8)field_0x81C) {

    case 1:
    case 4:
    case 6:
    case 7:
        field_0x81B = 0;
        field_0x7A4 = 0;
        speedF = 0.0;
        break;
    case 2:
        field_0x81B = 0;
        mAnimationNum = 0xff;
        field_0x818 = 0xff;
        field_0x822 = 0;
        field_0x7A2 = 0;
        field_0x81D = uVar1;
        break;
    case 3:
        field_0x81B = 0;
        break;

    case 5:
        field_0x81B = 0;
        field_0x815 = 2;
        field_0x816 = 0;
        field_0x7B6 = 1;
        break;

    case 0:
   break;


 }
 setAnm();
 return;
}

/* 0000311C-000032D8       .text createTama__11daNpc_Kk1_cFf */
void daNpc_Kk1_c::createTama(float param_1) {

    cXyz plrEyePos;
    csXyz local_5c(0.0f,0.0f,0.0f);

    cXyz local_30 = eyePos;
    local_30.y=15+eyePos.y;
    plrEyePos = dNpc_playerEyePos(-20);


    
    f32 a = (plrEyePos-eyePos).absXZ(); //TODO: Unused abs call?
    local_5c.y = cLib_targetAngleY(&local_30,&plrEyePos);
    local_5c.x = cLib_targetAngleX(&local_30,&plrEyePos);
    daTama_c* tama = (daTama_c *)fopAcM_fastCreate(0x1D6,0,&eyePos,fopAcM_GetRoomNo(this),&local_5c,NULL,0xFF,NULL,NULL);
    fpc_ProcID procID;
    if (tama != NULL) {
        if (this != NULL) {
            procID = base.mBsPcId;

        }
        else {
            procID = -1;
        }
        tama->setPartnerID(procID);
        tama->setDis(param_1);
        tama->setSpd(50);
    }
    return;
}

/* 000032D8-0000345C       .text chk_areaIN__11daNpc_Kk1_cFf4cXyz */
bool daNpc_Kk1_c::chk_areaIN(float i_distanceThreshold, cXyz i_position) {

    float distanceXZ = (LINKPOS - i_position).absXZ();

    s16 angle_diff = cLib_targetAngleY(&current.pos,&LINKPOS) - current.angle.y;
    float distance_threshold = i_distanceThreshold;
    if (abs(angle_diff) > 0x4E38) {
    distance_threshold *= 0.5f;
    }
    bool o_result = (distanceXZ < i_distanceThreshold);
    if (o_result && ((g_Counter.mCounter0 % 3) == 0)) {
        createTama(distance_threshold);

    }
    return o_result;
}

/* 0000345C-00003578       .text startEvent_check__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::startEvent_check() {





    u32 is_area_in = chk_areaIN(l_HIO.field_0x5C,current.pos);
    if (is_area_in) {
    float dist_to_link = current.pos.abs(LINKPOS);
        if ((dist_to_link < REG9_F(0) + 210.0f) ||
            (field_0x6BA != 0)) {
            return true;
        }
    }
    return false;
}


/* 00003578-00003600       .text chkHitPlayer__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chkHitPlayer() {

    bool o_result = false;
    if (mCyl.ChkCoHit()){
        cCcD_Obj* hit_obj = mCyl.GetCoHitObj();
        if(hit_obj != NULL) {

            fopAc_ac_c* hit_actor = dCc_GetAc(hit_obj);

            if(hit_actor != NULL){
                o_result = fopAcM_GetName(hit_actor) == PROC_PLAYER;
            }
        }
    }
    return o_result;
}

/* 00003600-000036A8       .text set_pthPoint__11daNpc_Kk1_cFUc */
void daNpc_Kk1_c::set_pthPoint(unsigned char i_pointIndex) {

    if(mRunPath.mPath != NULL){
        mRunPath.mCurrPointIndex = i_pointIndex;
        current.pos = mRunPath.getPoint(mRunPath.mCurrPointIndex);
        if(mRunPath.nextIdx()){
            cXyz runpoint = mRunPath.getPoint(mRunPath.mCurrPointIndex);
            current.angle.y = cLib_targetAngleY(&current.pos,&runpoint);
        }
    }
}


/* 000036A8-00003940       .text event_move__11daNpc_Kk1_cFb */
bool daNpc_Kk1_c::event_move(bool i_param_1) {

    f32 speed;
    if(!mRunPath.isPath()){
        return true;
    }

    if (!dPath_ChkClose(mRunPath.getPath())){
        return true;
    }
    if(field_0x7B6){
        if(mRunPath.chkPointPass(current.pos,mRunPath.getDir())){
            mRunPath.nextIdxAuto();
            if(i_param_1){
                s8 point_arg = mRunPath.pointArg(mRunPath.mCurrPointIndex);
                if( point_arg >= 0){
                    point_arg += 1;
                }
                if((point_arg != 2) && (point_arg != 3)){
                    field_0x7B6 = 0;

                }
                else{
                    field_0x815 = point_arg;
                    field_0x816 = 0;
                    field_0x7B6 = 1;
                }
            }

        }
    }

    cXyz runpoint = mRunPath.getPoint(mRunPath.mCurrPointIndex);

    s16 target = cLib_targetAngleY(&current.pos,&runpoint);
    s16 store_angle = current.angle.y;
    cLib_addCalcAngleS(&current.angle.y,target,l_HIO.mScale,l_HIO.mMaxStep,0x80);
    f32 target_float;
    float play_speed;
    if(field_0x815 == 2){
        if(field_0x7B6 == 0){
            target_float = 0.0;
        }else{
            target_float = l_HIO.field_0x44;
        }
        play_speed = speedF * l_HIO.field_0x4C;
        speed = l_HIO.field_0x48;
    }else{

        if(field_0x7B6 == 0){
            target_float = 0.0;
        }else{
            target_float = l_HIO.field_0x50;
        }
        play_speed = speedF * l_HIO.field_0x58;
        speed = l_HIO.field_0x54;
    }
    cLib_chaseF(&speedF,target_float,speed);
    mpMorf->setPlaySpeed(cLib_minLimit(play_speed,0.5f));
    if((int)target_float == 0){
        current.angle.y = store_angle;
        if((int)speedF == 0){
            speedF = 0.0;
            s8 point_arg = mRunPath.pointArg(mRunPath.mCurrPointIndex);
            if((s32)point_arg >= 0){
                point_arg += 1;
            }
            field_0x816 = point_arg;
            return true;
            
        }
    }

    return false;

}

/* 00003940-000039F0       .text kyoroPos__11daNpc_Kk1_cFi */
cXyz daNpc_Kk1_c::kyoroPos(int i_offset_index) {

    static f32 a_tgt_offst[12][3] = {
        0.0,    0.0,    0.0, 
        -100.0, 0.0,    0.0, 
        100.0,  0.0,    0.0, 
        -100.0, 0.0,    100.0, 
        100.0,  0.0,    100.0, 
        0.0,    0.0,    100.0, 
        -100.0, 40.0,   0.0, 
        100.0,  40.0,   0.0,
        -100.0, 40.0,   100.0, 
        100.0,  40.0,   100.0, 
        0.0,    40.0,  100.0, 
        -40.0,  10.0,  40.0
    };
    Vec offset_vec, o_output_vec;
    offset_vec.x = a_tgt_offst[i_offset_index][0];
    offset_vec.y = a_tgt_offst[i_offset_index][1];
    offset_vec.z = a_tgt_offst[i_offset_index][2];
    mDoMtx_stack_c::transS(eyePos);
    mDoMtx_stack_c::YrotM(this->current.angle.y);
    mDoMtx_stack_c::multVec(&offset_vec,&o_output_vec);
    return (cXyz)o_output_vec;

}

/* 000039F0-00003A84       .text kyorokyoro__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::kyorokyoro() {



    if(cLib_calcTimer(&field_0x794)){
        field_0x738 = kyoroPos(mKyoroRNG);
        return true;
    }
    int rng = cLib_getRndValue(1,10);
    mKyoroRNG = rng;
    field_0x794 = l_HIO.field_0x28;
    field_0x792 = l_HIO.field_0x2A; 
    return false;   //Return value not used
}

/* 00003A84-00003C9C       .text chk_attn__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chk_attn() {

    f32 distToLinkXZ = (current.pos-LINKPOS).absXZ();
    f32 heightDiff = current.pos.y - LINKPOS.y;
    s16 iVar3 = cLib_targetAngleY(&current.pos, &LINKPOS) - current.angle.y;
    if ((s32)mWhereToLook == 1) {
        return distToLinkXZ < 200.0f && 
        SHORT2DEG_ANGLE(abs(iVar3)) < 90.0f && //TODO: Possible inline (cAngle::s2d())
        std::fabsf(heightDiff) < 300.0f;
    }else{
        return distToLinkXZ < 200.0f && 
        SHORT2DEG_ANGLE(abs(iVar3)) < 60.0f &&
        std::fabsf(heightDiff) < 300.0f;
    }


}
/* 00003C9C-00003D9C       .text setBikon__11daNpc_Kk1_cF4cXyz */
void daNpc_Kk1_c::setBikon(cXyz param_1) {

    JPABaseEmitter *pJVar1;
    cXyz cStack_18;

    delBikon();
    PSMTXTrans(mDoMtx_stack_c::get(),current.pos.x,current.pos.y,current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    PSMTXMultVec(mDoMtx_stack_c::get(),&param_1,&cStack_18);

    dPa_control_c* particle = g_dComIfG_gameInfo.play.getParticle();
    pJVar1 = particle->set(0,0x8152,&cStack_18,NULL,NULL,0xFF,NULL,-1,NULL,NULL,NULL);

    if(pJVar1 != NULL){
        mDoAud_seStart(0x58BD,&current.pos);
    }
    return;
}

/* 00003D9C-00003DA0       .text delBikon__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::delBikon() {
    return;
}

/* 00003DA0-00003E18       .text setAse__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::setAse() {

    JPABaseEmitter* pJVar1;
    delAse();
    dPa_control_c* particle = g_dComIfG_gameInfo.play.getParticle();
    pJVar1 = particle->set(0,0x819E,&current.pos,&current.angle,NULL,0xFF,NULL,-1,NULL,NULL,NULL);
    field_0x810 = pJVar1;
    return;
}

/* 00003E18-00003EA4       .text flwAse__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::flwAse() {

    JGeometry::TVec3<f32> out;
    if (field_0x810 != NULL) {
        mDoMtx_stack_c::copy(mpMorf->mpModel->getAnmMtx(m_hed_jnt_num));
        mDoMtx_stack_c::multVecZero(out);
        field_0x810->setGlobalTranslation(out);

    }
    return;
}

/* 00003EA4-00003ED0       .text delAse__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::delAse() {
    JPABaseEmitter* Ase = field_0x810;
    if(field_0x810 == NULL){
        return;
    }
    Ase->becomeInvalidEmitter();
    field_0x810 = NULL;
    return;
}

/* 00003ED0-0000415C       .text wait_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_1() {
    if(field_0x7C3 != 0){
        if(chk_talk() != 0){
            setStt(2);
            setAnm_NUM(0,1);
            mWhereToLook = 1;
            mLockBodyRotation = 0;
            m_jnt.setTrn();
        }
        return TRUE;
    }
    field_0x81B = 2;
    mWhereToLook = 0;
    mLockBodyRotation = 1;

    cXyz sp20;
    if(field_0x7B6 != 0){
        sp20 = mRunPath.getPoint(mRunPath.mCurrPointIndex);
        s16 temp_r3 = cLib_targetAngleY(&current.pos,&sp20);
        cLib_addCalcAngleS(&current.angle.y,temp_r3,l_HIO.mScale,l_HIO.mMaxStep, 0x80);
        temp_r3 = temp_r3 - current.angle.y;
        if(abs(temp_r3) < 0x1800){
            setStt('\x03');
            field_0x7B7 = 0;
        }
        return TRUE;
    }

    if(field_0x81A == 0xB){
        if(field_0x7B2 != 0){
            setAnm_NUM(0,1);
            field_0x7A4 = cLib_getRndValue(0x3C, 0x1E);
            field_0x7B7 = 1;
        }
        return TRUE;
    }

    cXyz sp14(-100.0f,0.0f,0.0f);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_YrotM(mDoMtx_stack_c::get(),field_0x718.y);

    mDoMtx_stack_c::multVec(&sp14,&sp20);
    s16 temp_r3_r2 = cLib_targetAngleY(&current.pos,&sp20);
    
    cLib_addCalcAngleS(&current.angle.y,temp_r3_r2,l_HIO.mScale,l_HIO.mMaxStep, 0x80);
    temp_r3_r2 = temp_r3_r2 - current.angle.y;
    if(field_0x7B7 == 0){

        if(temp_r3_r2 == 0){
            setAnm_NUM(0xB,1);
        }
        return TRUE;
    }
    if(cLib_calcTimer(&field_0x7A4) == 0){
        if(mRunPath.mPath != NULL){
            u32 temp_r3_3 = mRunPath.maxPoint();
            if((temp_r3_3 > 2) && (((daObj_Roten_c*)temp_r3_3)->getCreateCount() > 1)){
                field_0x7B6 = 1;
                return TRUE;
            }
        }
        field_0x7B7 = 0;

    }   
    return TRUE;
}

/* 0000415C-0000449C       .text walk_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::walk_1() {

    short sVar2;
    float fVar3;
    short target;
    float fVar7;
    cXyz local_40;

    local_40 = mRunPath.getPoint(mRunPath.mCurrPointIndex);
    if (dPath_ChkClose(mRunPath.mPath)) {
        return 1;
    }
    u8 idx;
    fVar7 = (current.pos-local_40).absXZ();
    if ((field_0x7B6) && (fVar7 < l_HIO.field_0x34) ) {
        bool r29 = (mRunPath.nextIdxAuto() == 0);
        if (!r29 && mRunPath.mbGoingForwards){
            idx = mRunPath.mCurrPointIndex;
            if( idx >= ((daObj_Roten_c*)r29)->getCreateCount() ){
                mRunPath.decIdx();
                mRunPath.decIdx();
                r29 = true;
            }
        }
        if (r29 != 0) {
            field_0x7B6 = 0;
            mRunPath.mbGoingForwards ^= 1;
        }
    }

    target = cLib_targetAngleY(&current.pos,&local_40);

    sVar2 = current.angle.y;
    cLib_addCalcAngleS(&current.angle.y,target,l_HIO.mScale,l_HIO.mMaxStep,0x80);
    fVar7 = l_HIO.field_0x38;
    if (!field_0x7B6 || field_0x7C3 || chk_attn()) {
        fVar7 = 0.0;
    }
    cLib_chaseF(&speedF,fVar7,l_HIO.field_0x3C);
    fVar3 = speedF*l_HIO.field_0x40;
    fVar3 = cLib_minLimit(fVar3,0.5f);
    mpMorf->mFrameCtrl.setRate(fVar3);
    if ((int)fVar7 == 0) {
        current.angle.y = sVar2;
        if ((s32)speedF == 0) {
            if (field_0x7C3) {
                if(chk_talk()){
                    setStt(1);
                    setAnm_NUM(0,1);
                    mWhereToLook = 1;
                    mLockBodyRotation = 0;
                    m_jnt.setTrn();
                }
                return 1;
            }
            if (!field_0x7B6) {
                setStt('\x01');
                field_0x7B7 = 0;
                field_0x7B6 = 0;
                return 1;
            }
            setStt('\a');
            field_0x7B7 = 0;
            field_0x7B6 = 0;
            return 1;
        }
    }
    field_0x81B = 2;
    mWhereToLook = 0;
    mLockBodyRotation = 1;
    return 1;
}


/* 0000449C-00004614       .text wait_2__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_2() {

    int sp8;
    cLib_addCalcAngleS(&current.angle.y,field_0x718.y,4,0x800,0x80);
    if(field_0x7C3 != 0){
        if(chk_talk() != 0){
            setStt(2);
            mWhereToLook = 1;
            mLockBodyRotation = 0;
            field_0x7C5 = 0;            
            m_jnt.setTrn();
        }
        return 1;
    }
    mWhereToLook = 0;
    mLockBodyRotation = 1;
    s8 temp_r0 = field_0x81B;
#if VERSION > VERSION_JPN
    if(temp_r0 == 3 || temp_r0 == 4){   //Difference is likely due to the removal of RUN_START_2
#else
    if(temp_r0 == 3){
#endif
        return 1;
    }

    if(field_0x7B8 != 0){
        u8 temp_r4 = mSWbit;
        if((temp_r4 != 0xFF) && (dComIfGs_isSwitch(temp_r4,current.roomNo) != 0)){
#if VERSION > VERSION_JPN
            fopAc_ac_c* temp_r3 = searchByID(mPartnerProcID,&sp8);
            if((temp_r3 != NULL) && (sp8 == 0)){
                s16 difference = cLib_targetAngleY(&temp_r3->current.pos,&LINKPOS)-temp_r3->current.angle.y;
                if(abs(difference) < 0x4000){
                    field_0x81B = 4;
                }else{
                    field_0x81B = 3;
                }
                mStts.SetWeight(0xD9);
                return 1;
            }
#else
                field_0x81B = 3;
                mStts.SetWeight(0xD9);
                return 1;
#endif

        }
    }
    field_0x81B = 2;
    return 1;

}

/* 00004614-0000466C       .text init_CMT_WAI__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::init_CMT_WAI() {

    field_0x7A4 = cLib_getRndValue(0x5a,0xb4);
    this->mWhereToLook = 5;
    this->mLockBodyRotation = 1;
    setAnm_NUM(0,1);
    return;
}

/* 0000466C-00004754       .text move_CMT_WAI__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::move_CMT_WAI() {

    short sVar2;
    uint uVar1;

    
    sVar2 = cLib_calcTimer(&field_0x7A4);
    if (sVar2 == 0) {
    if ((field_0x81B != 1) && (field_0x81B < 3)) {
        uVar1 = chk_areaIN(l_HIO.field_0x5C,current.pos);
        if ((uVar1 & 0xff) != 0) {

            field_0x81B = EVENTLENGTH;



        return;
        }
    }
    field_0x816 = 0;
    setAnm_NUM(3,1);
    field_0x7B6 = 1;
    }
    else if (((field_0x81B != 1) && (field_0x81B < 3)) &&
            (startEvent_check() != 0)) {
        field_0x81B = EVENTLENGTH+1;
    }
    return;
}

/* 00004754-000047D4       .text init_CMT_TRN__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::init_CMT_TRN() {
   
    field_0x7AA = current.angle.y;
    s16 uVar1 = cLib_getRndValue(0x5A,0xB4);
    field_0x7A4 = uVar1;
    mTimer = l_HIO.field_0x2C;
    field_0x794 = l_HIO.field_0x28;
    field_0x792 = l_HIO.field_0x2A;
    mWhereToLook = 0;
    mLockBodyRotation = 1;
    setAnm_NUM(0,1);
    return;
}

/* 000047D4-00004A14       .text move_CMT_TRN__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::move_CMT_TRN() {

    short sVar1;
    uint uVar2;
    short sVar3;
    short sVar4;
    cXyz local_20;
    
    sVar1 = field_0x7AA + 0x8000;
    sVar3 = current.angle.y;
    uVar2 = cLib_calcTimer(&mTimer);
    if ((short)uVar2 != 0) {
        s8 temp_r0 = field_0x81B;
        if((temp_r0 != 1) && (temp_r0 < 3) && startEvent_check() != 0){
        field_0x81B = EVENTLENGTH+1;
        }
    }else if (field_0x7A4 == 0) {
        local_20 = mRunPath.getPoint(mRunPath.mCurrPointIndex);
        sVar3 = cLib_targetAngleY(&current.pos,&local_20);
        sVar1 = cLib_addCalcAngleS(&current.angle.y,sVar3,l_HIO.mScale,l_HIO.mMaxStep,0x80);
        uVar2 = (uint)sVar1;
        if ((field_0x81B != 1) && ((char)field_0x81B < 3)) {

            if (startEvent_check() != 0) {
                field_0x81B = EVENTLENGTH+1;
                return;
            }
            if (current.angle.y == (int)sVar3) {
                field_0x816 = 0;
                setAnm_NUM(3,1);
                field_0x7B6 = 1;
            }
        }
    }else {
        uVar2 = cLib_addCalcAngleS(&current.angle.y,sVar1,l_HIO.mScale,l_HIO.mMaxStep,0x80);
        //uVar2 = (uint)sVar4;
        //sVar4 = current.angle.y;
        if (current.angle.y == sVar1) {
            if (current.angle.y != sVar3) {
                mWhereToLook = 5;
                mLockBodyRotation = true;
            }
            if (cLib_calcTimer(&field_0x7A4) == 0) {
                if ((field_0x81B != '\x01') && ((char)field_0x81B < '\x03')) {
                    if (chk_areaIN(l_HIO.field_0x5C,current.pos)) {
                        field_0x81B = EVENTLENGTH;

                    }
                }
                mWhereToLook = 0;
                mLockBodyRotation = true;
            }
        }
        if (((field_0x81B != '\x01') && ((char)field_0x81B < '\x03')) &&
        (uVar2 = startEvent_check(), (uVar2 & 0xff) != 0)) {
        field_0x81B = EVENTLENGTH+1;
        }
    }
}

/* 00004A14-00004A84       .text init_CMT_PCK__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::init_CMT_PCK() {

    setAnm_NUM(1,1);
    field_0x7A4 = l_HIO.field_0x26;
    mWhereToLook = 0;
    mLockBodyRotation = 1;
    mEvtIDIdx = EVENTLENGTH-6;
    eventInfo.mEventId = mEvtIDTbl[mEvtIDIdx];
}

/* 00004A84-00004C34       .text move_CMT_PCK__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::move_CMT_PCK() {

    cXyz sp8;
    s16 temp_r3;
    u8 temp_r0;
    u8 temp_r0_2;

    if (field_0x7A4 == 0) {
        sp8 = mRunPath.getPoint(mRunPath.mCurrPointIndex);

        temp_r3 = cLib_targetAngleY(&current.pos,&sp8);
        cLib_addCalcAngleS(&current.angle.y, temp_r3, l_HIO.mScale, l_HIO.mMaxStep, 0x80);
        temp_r0 = field_0x81B;
        if (((s8) temp_r0 != 1) && ((s8) temp_r0 < 3)) {
            if (startEvent_check() != 0) {
                field_0x81B = EVENTLENGTH+1;
                return;
            }
            if (current.angle.y == temp_r3) {
                field_0x816 = 0;
                setAnm_NUM(3, 1);
                field_0x7B6 = 1;
            }
        }
    } else if ((u8) field_0x7C3 == 0) {
        temp_r0_2 = field_0x81B;
        if (((s8) temp_r0_2 != 1) && ((s8) temp_r0_2 < 3) && (chkHitPlayer() != 0)) {
            field_0x81B = 1;
            return;
        }
        if (!cLib_calcTimer(&field_0x7A4)) {
            setAnm_NUM(0, 1);
            eventInfo.mEventId = -1;
            field_0x81B = 0;
            return;
        }
        mDoAud_seStart(0x509BU, &current.pos);
        field_0x81B = 2;
    }
}

/* 00004C34-00004DD0       .text cmmt_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::cmmt_1() {


    u8 temp_r0_4;

    switch (field_0x816) {
    case 1:
        move_CMT_WAI();
        return 1;
    case 4:
        move_CMT_TRN();
        return 1;
    case 5:
        move_CMT_PCK();
        return 1;
    case 0:
    default:
        if ((field_0x81B != 1) && (field_0x81B < 3) && (field_0x81A != 1) && (startEvent_check() != 0)) {
            field_0x81B = EVENTLENGTH+1;
        }
        mWhereToLook = 0;
        mLockBodyRotation = 1;
        if (event_move( 1) != 0) {
            if ((field_0x81B == 1) || (field_0x81B >= 3)) {
                return 1;
            }
            temp_r0_4 = field_0x816;
            switch ((s8) temp_r0_4) {    
            case 1:                       
                init_CMT_WAI();
                break;
            case 4:                          
                init_CMT_TRN();
                break;
            case 5:                              
                init_CMT_PCK();
                break;
            case 0:
            default:                               
                field_0x816 = 0;
                setAnm_NUM(3, 1);
                field_0x7B6 = 1;
                break;
            }

        }
        if ((field_0x81B == 1) || (field_0x81B >= 3)) {
            return 1;
        }
        field_0x81B = 0;
        return 1;
    }
}

/* 00004DD0-00004F74       .text wait_3__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_3() {




    float distToLinkXZ = (current.pos-LINKPOS).absXZ();

    field_0x7C5 = distToLinkXZ > 300.0f;
    if (field_0x7C5) {
        cLib_addCalcAngleS(&current.angle.y,field_0x718.y,4,0x800,0x80);
    }
    if (field_0x7C3 != 0) {
        if (chk_talk()) {
            setStt(2);
            this->mWhereToLook = 1;
            this->mLockBodyRotation = 0;
            this->field_0x7C5 = 0;
            m_jnt.mbTrn = true;

        }
        return 1;
    }
    else {
        mWhereToLook = 0;
        mLockBodyRotation = 1;
        if (chk_attn()) {
            this->mWhereToLook = 1;
        }
        if ((this->field_0x81B != 1) && (field_0x81B < 3)) {
            this->field_0x81B = 2;
        }
    }
    return 1;
}

/* 00004F74-00005170       .text wait_4__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_4() {

    short target;
    int iVar2;
    float fVar4;
    cXyz local_20 [2];
    fVar4 = (current.pos-LINKPOS).absXZ();



    if (this->field_0x7C3) {
        if (chk_talk()) {
            setStt('\x02');
            setAnm_NUM(0,1);
            this->mWhereToLook = 1;
            this->mLockBodyRotation = 0;
            m_jnt.mbTrn = true;
        }
        return 1;
    }
    else {
    this->field_0x81B = 2;
    this->mWhereToLook = 1;
    this->mLockBodyRotation = 0;
    this->field_0x7B6 = fVar4 > 300.0f;
    if (this->field_0x7B6) {
        local_20[0] = mRunPath.getPoint(mRunPath.mCurrPointIndex);

        target = cLib_targetAngleY(&current.pos,local_20);
        cLib_addCalcAngleS(&current.angle.y,target,l_HIO.mScale,l_HIO.mMaxStep,0x80);
        s16 diff = target - current.angle.y;
        iVar2 = abs(diff);
        if (iVar2 < 0x1800) {
        setStt('\x03');
        field_0x7B7 = 0;
        }
        this->mWhereToLook = 0;
        this->mLockBodyRotation = 1;
    }
    }
    return 1;
}

/* 00005170-000052B4       .text talk_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::talk_1() {

 msg_class *pmVar3;
 int uVar4;
 short sVar5;
 
    int uVar6 = chk_parts_notMov();
    talk(1);
    pmVar3 = mpCurrMsg;
    if (pmVar3 == NULL) {
        return 1;
    }
    switch(pmVar3->mStatus){
        case 6:
        case 2:
            break;
        case 19:
            field_0x7B4 = 0xff;
            field_0x7C3 = 0;

            setStt(field_0x81D);
            uVar4 = cLib_getRndValue(0xF,0x1E);
            field_0x79E = uVar4;

            switch(mCurrMsgNo){
                case 0x1CA9:                        //Welcome to you, sir! This way to Windfall's outdoor shop, chock-full of fun and happy products!
                    dComIfGs_onEventBit(0xE10); //Intro text seen
                    break;
                case 0x1CAB:                    //'Bye! Thanks for tonight!
                    field_0x81B = EVENTLENGTH-1;  
                    break;
                case 0x1CAC:                    //Take off! Go away!
                    mWhereToLook = 1;
                    mLockBodyRotation = 0;
                    field_0x7A2 = 0;
                    break;
                default:
                    break;
            }
            endEvent();
            break;
    }
    sVar5 = cLib_calcTimer(&field_0x7A2);
    if ((sVar5 != 0) && (field_0x7A2 == 1)) {
        this->mWhereToLook = 1;
        this->mLockBodyRotation = 0;
    }
    return uVar6;
}


/* 000052B4-000053F4       .text wait_action1__11daNpc_Kk1_cFPv */
int daNpc_Kk1_c::wait_action1(void* arg0) {

    u8 temp_r0 = this->field_0x821;
    switch ((s8) temp_r0) {

    case 0:         
        if (dKy_daynight_check() == 0) {
            this->field_0x7B7 = 0;
            setStt(1);
            this->field_0x821 += 1;
        } else {
            setStt(4);
            this->field_0x821 += 1;
        }
        break;

    case 9:   
    default:                                    
        break;
    case 1:
    case 2:
    case 3:
        field_0x7C2 = chkAttention();

        switch (field_0x81C) {
        case 1:
            field_0x778 = wait_1();
            break;
        case 2:
            field_0x778 = talk_1();
            break;
        case 3:
            field_0x778 = walk_1();
            break;
        case 4:
            field_0x778 = wait_2();
            break;
        case 5:
            field_0x778 = cmmt_1();
            break;
        case 6:
            field_0x778 = wait_3();
            break;
        case 7:
            field_0x778 = wait_4();
            break;
        }
        break;
    }
    return 1;
}

/* 000053F4-00005534       .text demo__11daNpc_Kk1_cFv */
u8 daNpc_Kk1_c::demo() {

    J3DAnmTexPattern *pJVar2;
 
    if (demoActorID == 0) {
    if (field_0x7C6 != 0) {
        field_0x7C6 = 0;
    }
    }
    else {
        if (field_0x7C6 == NULL) {
            field_0x7C6 = 1;
            field_0x7BF = 0;

            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);

        }
         dDemo_actor_c* this_00 = dComIfGp_demo_getActor(demoActorID);

        pJVar2 = mBtpAnm.getBtpAnm();

        if (pJVar2 != NULL) {

            u8 cmp = pJVar2 ->getFrameMax();
            mBtpFrame += 1;
            if (mBtpFrame >= cmp) {
                mBtpFrame = cmp;
            }
        }

        pJVar2 = (J3DAnmTexPattern*)(this_00)->getP_BtpData(&mArcName);
        if (pJVar2 != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(),pJVar2,1,0,1.0,0,-1,true,0);
    
            field_0x819 = 1;
            mBtpFrame = 0;
        }
        dDemo_setDemoData(this,0x6A,mpMorf,&mArcName);


    }
    return field_0x7C6;

}


/* 00005534-000055C4       .text shadowDraw__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::shadowDraw() {

    cXyz local_18(current.pos.x,current.pos.y + 150.0f, current.pos.z);

    
    GXTexObj* tex = dDlst_shadowControl_c::getSimpleTex();
    mShadowID = dComIfGd_setShadow(mShadowID,1,mpMorf->getModel(),&local_18,800.0f,40.0f,current.pos.y,mObjAcch.GetGroundH(),
    mObjAcch.m_gnd,&tevStr,0,1.0,tex);

}

/* 000055C4-00005798       .text _draw__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::_draw() {

    J3DModelData *model_data;
    J3DModel *model;

    GXColor unused_green   = {0x00,0xFF,0x00,0x80};
    GXColor unused_yellow  = {0xFF,0xFF,0x00,0x80};
    GXColor unused_red     = {0xFF,0x00,0x00,0x80};
    GXColor unused_blue    = {0x00,0x00,0xFF,0x80};
    GXColor unused_yellow2 = {0xFF,0xFF,0x00,0x80};
    GXColor unused_green2  = {0x00,0xFF,0x00,0x80};

    model = mpMorf->getModel();
    model_data = model->getModelData();

    if ((field_0x7BD) || (field_0x7C0)) {
        return 1;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR,&current.pos,&tevStr);
    g_env_light.setLightTevColorType(model,&tevStr);

    mBtpAnm.entry(model_data,mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);
    if (!field_0x7BE) {
        field_0x7C8.entry(field_0x808->getModelData(),field_0x800);

        field_0x7DC.entry(field_0x808->getModelData(),field_0x802);
        mDoExt_modelEntryDL(field_0x808);
        field_0x7DC.remove(field_0x808->getModelData());
        field_0x7C8.remove(field_0x808->getModelData());

    }
    shadowDraw();
    dSnap_RegistFig(0x58,(fopAc_ac_c *)this,1.0,1.0,1.0);

    if (l_HIO.field_0x24) {
        cXyz somevec = current.pos;
        somevec.y = eyePos.y;
        somevec = mRunPath.getPoint(mRunPath.getIdx());
    }
 return 1;
}
// const GXColor unusedcolor = {0x00,0xFF,0x00,0x80};
// const GXColor unusedcolor2 = GXCOLOR
//Needed to fill .rodata


/* 00005798-000059EC       .text _execute__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::_execute() {

    float radius;
    int cVar1;
    int iVar3;

    if (!field_0x7C1) {
        field_0x70C = current.pos;
        field_0x718 = current.angle;
        field_0x7C1 = 1;
    }
    m_jnt.setParam(
        l_HIO.field_0x14,l_HIO.field_0x16,
        l_HIO.field_0x18,l_HIO.field_0x1A,
        l_HIO.field_0xC,l_HIO.field_0xE,
        l_HIO.field_0x10,l_HIO.field_0x12,
        l_HIO.field_0x1C
    );

    if ((field_0x7BD ) && (!demoActorID)) {
        return true;
    }
    partner_search();
    checkOrder();

    if (!demo()) {
        iVar3 = -1;
        if ((dComIfGp_event_runCheck())){
            if (checkCommandTalk() == 0) {
                iVar3 = isEventEntry();
            }
        }
            if (iVar3 >= 0) {
            event_proc(iVar3);
            }
            else {
            (this->*field_0x6F0)(NULL);
            }
            field_0x6BA = 0;
            lookBack();
            fopAcM_posMoveF(this,mStts.GetCCMoveP());
            mObjAcch.CrrPos(*dComIfG_Bgsp());
            play_animation();
    }
    else {
        field_0x7BD = 0;
    }
    eventOrder();
    mAngle = current.angle;

    if (!field_0x7BF) {
        shape_angle = current.angle;
    }

    cVar1 = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mRoomNo = cVar1;
    u8 bVar2 = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = bVar2;
    setMtx(false);
    if (!(field_0x7C6 ) && !(field_0x7BB)) {
        if (field_0x81A == 1) {
        radius = 60.0;
        }
        else {
        radius = 40.0;
        }
        setCollision(radius,140.0);
    }

    return true;
}


/* 000059EC-00005A58       .text _delete__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::_delete() {
    cDyl_Unlink(0x1D6);
    dComIfG_resDelete(&field_0x6C4,&mArcName);
    delBikon();
    delAse();
    if(heap != NULL && mpMorf != NULL){
        mpMorf->stopZelAnime();
    }
    return 1;
}
static u32 a_siz_tbl[2] = {0x0,0x0};
/* 00005A58-00005B98       .text _create__11daNpc_Kk1_cFv */
cPhs_State daNpc_Kk1_c::_create() {


    fopAcM_SetupActor(this,daNpc_Kk1_c);


    if (!decideType(base.mParameters & 0xff)) {
        return cPhs_ERROR_e;
    }

    s32 resLoadResult = dComIfG_resLoad(&field_0x6C4,&mArcName);
    field_0x7BC = resLoadResult == cPhs_COMPLEATE_e;
    
    if((u8)field_0x7BC == 0){
        return resLoadResult;
    }

    s32 linkresult = cDyl_LinkASync(0x1D6);
    if(linkresult != cPhs_COMPLEATE_e){
        return linkresult;
    }

    if (!fopAcM_entrySolidHeap(this,CheckCreateHeap,a_siz_tbl[field_0x81F])) {
        return cPhs_ERROR_e;
    }
    cullMtx = (MtxP)mpMorf->mpModel->getBaseTRMtx();
    fopAcM_SetMtx(this,cullMtx);
    fopAcM_setCullSizeBox(this,-50.0,-20.0,-50.0,50.0,140.0,50.0);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return resLoadResult;
}

/* 00006118-0000638C       .text bodyCreateHeap__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::bodyCreateHeap() {

    J3DModelData *a_mdl_dat;
    mDoExt_McaMorf *pmVar2;

    

    a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(&mArcName,0xD);
    a_mdl_dat->getJointName();
#if VERSION > VERSION_JPN
    JUT_ASSERT(0xDD6,a_mdl_dat != 0);   //Line 3542
#else
    JUT_ASSERT(0xDBD,a_mdl_dat != 0);   //Line 3517
#endif

    pmVar2 = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,NULL,
        -0x1,1.0,0,-1,1,NULL,0x80000,0x11020022);
 

    mpMorf = pmVar2;
    pmVar2 = mpMorf;
    if (pmVar2 == NULL) {
        return 0;
    }
    else if (pmVar2->mpModel == NULL) {
        mpMorf = NULL;
        return 0;
    }


    if (!init_texPttrnAnm(0,false)) {
        mpMorf = NULL;
        return 0;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
#if VERSION > VERSION_JPN
    JUT_ASSERT(0xDEA,m_hed_jnt_num >= 0);   //Line 3562
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0xDEC,m_bbone_jnt_num >= 0); //Line 3564
#else
    JUT_ASSERT(0xDD1,m_hed_jnt_num >= 0);   //Line 3537
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0xDD3,m_bbone_jnt_num >= 0); //Line 3539
#endif
    mpMorf->mpModel->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->mpModel->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->mpModel->setUserArea((u32)this);
    return 1;
}

/* 0000638C-000065E0       .text effcCreateHeap__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::effcCreateHeap() {

 J3DModelData *pModel;
 J3DModel *pJVar1;
 J3DAnmColor *a_bpk;

 int iVar4;
 J3DAnmTextureSRTKey *a_btk;
 J3DAnmTransform *a_bck;
 
 pModel = (J3DModelData*)dComIfG_getObjectIDRes(&mArcName,0xE);
 
    pJVar1 = mDoExt_J3DModel__create(pModel,0x0,0x11020203);
    field_0x808 = pJVar1;
    if(field_0x808 != NULL){

    a_bpk = (J3DAnmColor*)dComIfG_getObjectIDRes(&mArcName,0xF);
    JUT_ASSERT(VERSION_SELECT(3560,3560,3585,3585),0 != a_bpk);
    iVar4 = field_0x7C8.init(field_0x808->getModelData(),a_bpk,true,0,0.0,0,-1,false,0);
    if(iVar4 == 0){
        return 0;
    }
    a_btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectIDRes(&mArcName,0x10);
    JUT_ASSERT(VERSION_SELECT(3568,3568,3593,3593),0 != a_btk);
    iVar4 = field_0x7DC.init(field_0x808->getModelData(),a_btk,true,0,0.0,0,-1,false,0);
    if(iVar4 == 0){
        return 0;
    }
    a_bck = (J3DAnmTransform*)dComIfG_getObjectIDRes(&mArcName,0x0);

    JUT_ASSERT(VERSION_SELECT(3576,3576,3601,3601),0 != a_bck);
    iVar4 = field_0x7F0.init(field_0x808->getModelData(),a_bck,true,0,0.0,0,-1,false);
    if(iVar4 == 0){
        return 0;
    }
    field_0x800 = 0;
    field_0x802 = 0;
    field_0x804 = 0;
    }
 return 1;
}

/* 000065E0-00006684       .text CreateHeap__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::CreateHeap() {


    
    if (!bodyCreateHeap()) {
        return 0;

    }
    else {
    if (!effcCreateHeap()) {
        mpMorf = NULL;
        return 0;

    }
    else {
        mAcchCir.SetWall(30.0,40.0);
        mObjAcch.Set(&current.pos,&old.pos,this,1,&mAcchCir,&speed,NULL,NULL);
        return 1;

    }
    }
}

/* 00006684-000066A4       .text daNpc_Kk1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kk1_Create(fopAc_ac_c* obj) {
    (static_cast<daNpc_Kk1_c*>(obj))->_create();

}

/* 000066A4-000066C4       .text daNpc_Kk1_Delete__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_Delete(daNpc_Kk1_c* obj) {
    (static_cast<daNpc_Kk1_c*>(obj))->_delete();
}

/* 000066C4-000066E4       .text daNpc_Kk1_Execute__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_Execute(daNpc_Kk1_c* obj) {
    (static_cast<daNpc_Kk1_c*>(obj))->_execute();
}

/* 000066E4-00006704       .text daNpc_Kk1_Draw__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_Draw(daNpc_Kk1_c* obj) {
    (static_cast<daNpc_Kk1_c*>(obj))->_draw();
}

/* 00006704-0000670C       .text daNpc_Kk1_IsDelete__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_IsDelete(daNpc_Kk1_c*) {
    return true;
}



static actor_method_class l_daNpc_Kk1_Method = {
    (process_method_func)daNpc_Kk1_Create,
    (process_method_func)daNpc_Kk1_Delete,
    (process_method_func)daNpc_Kk1_Execute,
    (process_method_func)daNpc_Kk1_IsDelete,
    (process_method_func)daNpc_Kk1_Draw,
};

actor_process_profile_definition g_profile_NPC_KK1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_KK1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kk1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x166,
    /* Actor SubMtd */ &l_daNpc_Kk1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
