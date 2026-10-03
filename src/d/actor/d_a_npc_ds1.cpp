/**
 * d_a_npc_ds1.cpp
 * NPC - Doc Bandam (Windfall Potion Shop shopkeeper)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ds1.h"
#include "d/actor/d_a_player.h"
#include "d/d_item.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "res/Object/Ds.h"
#include "m_Do/m_Do_controller_pad.h"

class daNpc_Ds1_childHIO_c {
public:
    daNpc_Ds1_childHIO_c();
    virtual ~daNpc_Ds1_childHIO_c() {};

public:
    /* 0x04 */ dNpc_HIO_c mNpc;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
};  // Size: 0x48

class daNpc_Ds1_HIO_c : public JORReflexible{
public:
    daNpc_Ds1_HIO_c();
    virtual ~daNpc_Ds1_HIO_c() {};

public:
    /* 0x04 */ s8 mChildId;
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ daNpc_Ds1_childHIO_c mChild[1];
};


static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};

static fpc_ProcID l_msgId;
static msg_class* l_msg;
static daNpc_Ds1_HIO_c l_HIO;

/* 000000EC-00000108       .text __ct__20daNpc_Ds1_childHIO_cFv */
daNpc_Ds1_childHIO_c::daNpc_Ds1_childHIO_c() {
}

/* 00000108-00000194       .text daNpc_Ds1_checkCreateDrugChuchu__FUc */
bool daNpc_Ds1_checkCreateDrugChuchu(u8 itemId) {
    if(itemId == dItemNo_RED_JELLY_e || (itemId == dItemNo_GREEN_JELLY_e && dComIfGs_isEventBit(dSv_event_flag_c::UNK_0D04))
    ||(itemId == dItemNo_BLUE_JELLY_e && dComIfGs_isEventBit(dSv_event_flag_c::UNK_0D02))){
        return true;
    }
    return false;
}

/* 00000194-00000298       .text __ct__15daNpc_Ds1_HIO_cFv */
daNpc_Ds1_HIO_c::daNpc_Ds1_HIO_c() {
    mChild[0].mNpc.m04 = -80.0f;
    mChild[0].mNpc.mMaxHeadX = 0x1ffe;
    mChild[0].mNpc.mMaxHeadY = 0x38e0;
    mChild[0].mNpc.mMaxBackboneX = 0;
    mChild[0].mNpc.mMaxBackboneY = 0x1c70;
    mChild[0].mNpc.mMinHeadX = -0x1ffe;
    mChild[0].mNpc.mMinHeadY = 0;
    mChild[0].mNpc.mMinBackboneX = 0;
    mChild[0].mNpc.mMinBackboneY = 0;
    mChild[0].mNpc.mMaxTurnStep = 0x1000;
    mChild[0].mNpc.mMaxHeadTurnVel = 0x800;
    mChild[0].mNpc.mAttnYOffset = 60.0f;
    mChild[0].mNpc.m22 = 0;
    mChild[0].mNpc.mMaxAttnDistXZ = 300.0f;
    mChild[0].field_0x2C = 300.0f;
    mChild[0].field_0x30 = 300.0f;
    mChild[0].field_0x34 = 0.65f;
    mChild[0].field_0x38 = 0.9f;
    mChild[0].field_0x3C = 0.5f;
    mChild[0].field_0x40 = 27.0f;
    mChild[0].field_0x44 = 20.0f;
    mChildId = -1;
    field_0x08 = -1;
}


static const int l_bck_ix_tbl[] = {
    dRes_INDEX_DS_BCK_WAIT01_e,
    dRes_INDEX_DS_BCK_TALK01_e,
    dRes_INDEX_DS_BCK_AMAZED_e,
    dRes_INDEX_DS_BCK_WAIT01_e,
    dRes_INDEX_DS_BCK_FLUT_e,
    dRes_INDEX_DS_BCK_WALK_e,
    dRes_INDEX_DS_BCK_MAKE_e,
    dRes_INDEX_DS_BCK_WAIT02_e,
    dRes_INDEX_DS_BCK_MEGANE_e,
    dRes_INDEX_DS_BCK_FLUT_e
};

static const int l_btp_ix_tbl[] = {
    dRes_INDEX_DS_BTP_MABA01_e,
    dRes_INDEX_DS_BTP_MABA02_e
};


/* 000002F8-00000318       .text daNpc_Ds1_XyEventCB__FPvi */
static s16 daNpc_Ds1_XyEventCB(void* i_this, int i_itemBtn) {
    return ((daNpc_Ds1_c*)i_this)->XyEventCB(i_itemBtn);
}

/* 00000318-00000550       .text XyEventCB__11daNpc_Ds1_cFi */
s16 daNpc_Ds1_c::XyEventCB(int itemBtn) {
    s16 ret = -1;
    u8 itemId = dComIfGp_getSelectItem(itemBtn);
    if((u8)(itemId + ~dItemNo_KNIGHTS_CREST_e) <= 1 || itemId == dItemNo_BLUE_JELLY_e){
        if(!daNpc_Ds1_checkCreateDrugChuchu(itemId) &&( 
            (itemId == dItemNo_RED_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_RED_JELLY_e) >= 0xa) ||
            (itemId == dItemNo_GREEN_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_GREEN_JELLY_e) >= DEMO_SELECT(0x14, 0xf))||
            (itemId == dItemNo_BLUE_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_BLUE_JELLY_e) >= DEMO_SELECT(0x14, 0xf)))) {
                ret = mEventIdx[2];
                field_0x887 = 5;
                field_0x888 = 2;
                setAction(&daNpc_Ds1_c::event_action, NULL);
        }
        else{
            if(!daNpc_Ds1_checkCreateDrugChuchu(itemId)){
                ret = mEventIdx[3];
                field_0x887 = 6;
                field_0x888 = 3;
                setAction(&daNpc_Ds1_c::event_action, NULL);
            }
        }
        mDrugChuchuNo = itemId;
    } else {
        field_0x888 = 4;
    }
    return ret;
}

char daNpc_Ds1_c::m_arcname[] = "Ds";


/* 00000550-00000718       .text nodeCallBack_Ds__FP7J3DNodei */
static BOOL nodeCallBack_Ds(J3DNode* node, int calcTiming) {
    if(calcTiming == 0){
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Ds1_c* i_this = (daNpc_Ds1_c*)model->getUserArea();
        s32 jntNo = joint->getJntNo();
        
        if(i_this != NULL){
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if(jntNo == i_this->getHeadJntNum()){
                cXyz offset;
                cXyz dest;
                offset.setall(0.0f);
                cMtx_YrotM(*calc_mtx, -i_this->getHead_y());
                cMtx_ZrotM(*calc_mtx, -i_this->getHead_x());
                MtxPosition(&offset, &dest);
                i_this->setAttentionBasePos(dest);
                offset.set(28.0f, 20.0f, 0.0f);
                MtxPosition(&offset, &dest);
                i_this->setEyePos(dest);
                i_this->incAttnSetCount();
            }
            else if(jntNo == i_this->getBackboneJntNum()){
                mDoMtx_XrotM(*calc_mtx, i_this->getBackbone_y());
                mDoMtx_ZrotM(*calc_mtx, i_this->getBackbone_x());
            }
            MTXCopy(*calc_mtx, j3dSys.mCurrentMtx);
            model->setAnmMtx(jntNo, *calc_mtx);
        }
        
    }
    return TRUE;
}


/* 00000718-00000824       .text initTexPatternAnm__11daNpc_Ds1_cFb */
BOOL daNpc_Ds1_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData(); 
    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname, l_btp_ix_tbl[mBtpResIDIndex]);
    JUT_ASSERT(DEMO_SELECT(0x1DE, 0x1E8), m_head_tex_pattern != NULL);
    if(!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify)){
        return FALSE;
    }else{
        mBtpAnmFrame = 0;
        mTimer = 0;
        return TRUE;
    }
    return FALSE;

}

/* 00000824-000008B0       .text playTexPatternAnm__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::playTexPatternAnm() {
    if(cLib_calcTimer(&mTimer) == 0){
        if(mBtpAnmFrame >= m_head_tex_pattern->getFrameMax()){
            mBtpAnmFrame -= m_head_tex_pattern->getFrameMax();
            mTimer = cM_rndF(100.0f) + 30.0f;
        }
        else{
            mBtpAnmFrame++;
        }
    }
}

/* 000008B0-000009A8       .text setAnm__11daNpc_Ds1_cFScf */
void daNpc_Ds1_c::setAnm(s8 param1, f32 param2) {    static u32 play_mode_tbl[10] = {
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_LOOP,
    };
    static f32 morf_frame_tbl[10] = {8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f};
    static f32 play_speed_tbl[10] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    
    if(param1 != field_0x885 || field_0x885 == -1){
        field_0x885 = param1;
        if(param2 < 0){
            param2 = morf_frame_tbl[param1];
        }
        dNpc_setAnm_2(mpMorf, play_mode_tbl[param1], param2, play_speed_tbl[param1], l_bck_ix_tbl[param1], -1, m_arcname);
        if(param1 == 4 || param1 == 6 || (u8)((param1 - 8) & 0xff) <= 1 || param1 == 7){
            mJntCtrl.onHeadLock();
            mJntCtrl.onBackBoneLock();
        }
        else{
            mJntCtrl.offHeadLock();
            mJntCtrl.offBackBoneLock();
        }
    }
}

/* 000009A8-000009EC       .text setTexAnm__11daNpc_Ds1_cFSc */
void daNpc_Ds1_c::setTexAnm(s8 value) {
    if(mBtpResIDIndex != value || mBtpResIDIndex == -1){
        mBtpResIDIndex = value;
        initTexPatternAnm(true);
    }
}

/* 000009EC-00000CAC       .text setAnmFromMsgTag__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::setAnmFromMsgTag() {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnm(0, -1.0f);
            setTexAnm(0);
            break;
        case 1:
            setAnm(1, -1.0f);
            setTexAnm(0);
            break;
        case 2:
            setAnm(2, -1.0f);
            setTexAnm(1);
            break;
        case 3:
            setAnm(3, -1.0f);
            setTexAnm(0);
            break;
        case 4:
            setAnm(4, -1.0f);
            setTexAnm(1);
            break;
        case 5:
            setAnm(9, -1.0f);
            setTexAnm(1);
            break;
    }
    
    if(field_0x885 == 1 && mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f) && ++field_0x886 > 1){
        setAnm(0, -1.0f);
        field_0x886 = 0;
    }
    if(field_0x885 == 9 && mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f) && ++field_0x886> 4){
        setAnm(0, -1.0f);
        field_0x886 = 0;
    }
    if(field_0x885 == 3 && mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f) && ++field_0x886 > 1){
        setAnm(2, -1.0f);
        field_0x886 = 0;
    }
    
    dComIfGp_setMesgAnimeAttrInfo(0xff);
}

/* 00000CAC-00000DB0       .text chkAttention__11daNpc_Ds1_cF4cXyzs */
bool daNpc_Ds1_c::chkAttention(cXyz pos, short) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 f1 = l_HIO.mChild[mType].field_0x30;
    f32 f2 = l_HIO.mChild[mType].field_0x2C;
    cXyz tmp = player->current.pos - pos;
    cXyz vecProd1;
    vecProd1.set(0,0,1);
    cXyz vecProd2;
    vecProd2.set(1,0,0);

    f32 f3 = vecProd1.inprod(tmp);

    f32 temp = std::fabsf(vecProd2.inprod(tmp));

    return f1 > f3 && f2 > temp; 
}

/* 00000DB0-00000EAC       .text eventOrder__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::eventOrder() {
    if(field_0x887 == 3){
        fopAcM_orderOtherEventId(this, mEventIdx[1]);
    }
    else if(field_0x887 == 4){
        fopAcM_orderOtherEventId(this, mEventIdx[0]);
    }
    else if(field_0x887 == 5){
        fopAcM_orderOtherEventId(this, mEventIdx[2]);
    }
    else if(field_0x887 == 6){
        fopAcM_orderOtherEventId(this, mEventIdx[3]);
    }
    else if(field_0x887 == 1 || field_0x887 == 2){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if(field_0x887 == 1) fopAcM_orderSpeakEvent(this);
    }
}

/* 00000EAC-000011F8       .text checkOrder__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()){
        if(field_0x887 == 3){
            field_0x887 = 0;
            mShopCam.setCamAction(NULL);
            setAction(&daNpc_Ds1_c::getdemo_action, NULL);
        }
        else if(field_0x887 == 4){
            field_0x887 = 0;
            mShopCam.setCamAction(NULL);
            setAction(&daNpc_Ds1_c::event_action, NULL);
        }
        else if(field_0x887 == 5){
            field_0x887 = 0;
        }
        else if(field_0x887 == 5) {
            field_0x887 = 0;
        }
    }
    else if(eventInfo.checkCommandTalk() && (field_0x887 == 1 || field_0x887 == 2)){
        if( dComIfGp_event_chkTalkXY()){
            field_0x887 = 0;
            if(field_0x888 != 2){
                field_0x761 = 1;
                talkInit();
            }
            mDrugChuchuNo = dComIfGp_event_getPreItemNo();
        }
        else{
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1120)){
                mShopCam.shop_cam_action_init();
                cXyz playerPos;
                playerPos.set(10.0f, 0.0f, 100.0f);
                daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                player->setPlayerPosAndAngle(&playerPos, -0x6000);
            }
            else {
                
                mShopCam.ds_normal_cam_action_init();
                cXyz playerPos;
                playerPos.set(-115.0f, 0.0f, 100.0f);
                daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                player->setPlayerPosAndAngle(&playerPos, -0x6000);
            }
            field_0x887 = 0;
            field_0x761 = 1;
            talkInit();
        }
    }
}

/* 000011F8-00001698       .text next_msgStatus__11daNpc_Ds1_cFPUl */
u16 daNpc_Ds1_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
    case 0x1DB1:
    case 0x1DB2:
    case 0x1DB3:
    case 0x1DB5:
    case 0x1DB6:
    case 0x1DB7:
    case 0x1DB8:
    case 0x1DBB:
    case 0x1DBC:
    case 0x1DC9:
    case 0x1DCE:
        *pMsgNo += 1;
        break;
    case 0x1dcf:
        if(mDrugChuchuNo == dItemNo_RED_JELLY_e) {
            *pMsgNo = 0x1dd0;
            break;
        }
        *pMsgNo = 0x1dde;
        break;
    case 0x1dc0:
        if(CPad_CHECK_TRIG_B(0)){
            *pMsgNo = 0x1ddc;
            break;
        }
        dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
        dComIfGp_setAStatusForce(dActStts_CANCEL_e);
        msgStatus = fopMsgStts_MSG_DISPLAYED_e;
        break;
    case 0x1dc1:
        *pMsgNo = 0x1dc0;
        break;
    case 0x1ddb:
        *pMsgNo = 0x1dc0;
        break;
    case 0x1dd1:
    case 0x1dd2:
    case 0x1dd3:
        if(CPad_CHECK_TRIG_B(0)){
            *pMsgNo = 0x1ddc;
            break;
        }
        dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
        dComIfGp_setAStatusForce(dActStts_CANCEL_e);
        *pMsgNo += 3;
        break;
    case 0x1dc3:
        if(!daNpc_Ds1_checkCreateDrugChuchu(mDrugChuchuNo)) {
            *pMsgNo = 0x1dc8;
            break;
        }
        if((mDrugChuchuNo == dItemNo_RED_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_RED_JELLY_e) >= 5) 
        || (mDrugChuchuNo == dItemNo_GREEN_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_GREEN_JELLY_e) >= 5)
        || (mDrugChuchuNo == dItemNo_BLUE_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_BLUE_JELLY_e) >= 5)){
            *pMsgNo = 0x1dc4;
            break;
        }
        *pMsgNo = 0x1dc7;
        break;
    case 0x1dc4:
        if(dComIfGs_checkEmptyBottle()) {
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
        }
        *pMsgNo = 0x1dc5;
        break;
    case 0x1dc8:
        if((mDrugChuchuNo == dItemNo_RED_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_RED_JELLY_e) >= 0xa) 
        || (mDrugChuchuNo == dItemNo_GREEN_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_GREEN_JELLY_e) >= DEMO_SELECT(0x14, 0xf))
        || (mDrugChuchuNo == dItemNo_BLUE_JELLY_e && dComIfGs_getBeastNum(dBeastIdx_BLUE_JELLY_e) >= DEMO_SELECT(0x14, 0xf))){
            *pMsgNo = 0x1dc9;
            break;
        }
        *pMsgNo = 0x1dce;
        break;
    case 0x1dd7:
    case 0x1dd8:
    case 0x1dd9:
    case 0x1dda:
        *pMsgNo = 0x1dc0;
        break;
    case 0x1dcb:
        if(dComIfGs_checkEmptyBottle()) {
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
        }
        *pMsgNo = 0x1dcc; 
        break;
    case 0x1dd4:
    case 0x1dd5:
    case 0x1dd6:
        if(dComIfGp_checkMesgCancelButton()) {
            *pMsgNo = *pMsgNo - 3;
            break;
        }
        if(l_msg->mSelectNum == 0){
            u32 rupee = dComIfGp_getMessageRupee();
            u8 boughtErrorStatus = dShop_BoughtErrorStatus(&mShopItems, 0, rupee);
            if(boughtErrorStatus & 8) {
                *pMsgNo = 0x1dd7;
                break;
            }
            if(boughtErrorStatus & 0x10) {
                *pMsgNo = 0x1dd8;
                break;
            }
            if(boughtErrorStatus & 0x20) {
                *pMsgNo = 0x1dd9;
                break;
            }
            int selectedItemNo = mShopItems.getSelectItemNo();
            if(!checkItemGet(selectedItemNo, 0)){
                fopAcM_seStart(this, JA_SE_SHOP_BOUGHT, 0);
                mShopItems.hideSelectItem();
                mItemNo = mShopItems.getSelectItemNo();
                dComIfGp_setItemRupeeCount(-rupee);
                field_0x887 = 3;
                field_0x888 = 4;
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
            }
            
            fopAcM_seStart(this, JA_SE_SHOP_BOUGHT, 0);
            mShopItems.hideSelectItem();
            mItemNo = mShopItems.getSelectItemNo();
            int tempItemNo = mShopItems.getSelectItemNo();
            execItemGet(tempItemNo);
            dComIfGp_setItemRupeeCount(-rupee);
            *pMsgNo = 0x1dda;
            break;
        }
        *pMsgNo -= 3;
        break;

    case 0x1db9:
        if(l_msg->mSelectNum == 0) {
            *pMsgNo = 0x1dbb;
            break;
        }
        *pMsgNo = 0x1dba;
        break;
    
    default:
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    }
    
    return msgStatus;
}

/* 00001698-00001794       .text getMsg__11daNpc_Ds1_cFv */
u32 daNpc_Ds1_c::getMsg() {
    u32 ret;
    if(field_0x7D0 != 0) {
        ret = field_0x7D0;
        field_0x7D0 = 0;
    }
    else{
        if(dComIfGp_event_chkTalkXY()){
            if(mDrugChuchuNo == dItemNo_RED_JELLY_e || mDrugChuchuNo == dItemNo_GREEN_JELLY_e || mDrugChuchuNo == dItemNo_BLUE_JELLY_e){
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1120);
                ret = 0x1DC3;
            }
            else{
                if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1120)){
                    ret = 0x1DDD;
                }
                else{
                    ret = 0x1DC2;
                }
            }
        }
        else{
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1120)){
                ret = 0x1DDB;
            }
            else{
                ret = 0x1DB1;
            }
        }
    }
    
    return ret;
}

/* 00001794-00001850       .text setCollision__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::setCollision() {
    cXyz cylPos;
    cXyz center;
    cylPos.set(0.0f, 0.0f, 0.0f);
    cylPos.z = -16.0f;
    
    MtxTrans(current.pos.x, current.pos.y, current.pos.z, false);
    cMtx_YrotM(*calc_mtx, field_0x756.y);
    MtxPosition(&cylPos, &center);
#if VERSION > VERSION_DEMO
    mCyl.SetC(center);
    mCyl.SetR(46.0f);
    mCyl.SetH(130.0f);
#else
    f32 radius = 46.0f;
    f32 height = 130.0f;
    mCyl.SetC(center);
    mCyl.SetR(radius);
    mCyl.SetH(height);
#endif
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 00001850-0000185C       .text talkInit__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::talkInit() {
    field_0x899 = 0;
}

/* 0000185C-00001884       .text daNpc_Ds1_shopMsgCheck__FUl */
BOOL daNpc_Ds1_shopMsgCheck(u32 msgNo) {
    if((msgNo >= 0x1DD1 && msgNo <= 0x1DDA) || msgNo == 0x1DC0) return TRUE;
    return FALSE;
}

/* 00001884-000018AC       .text daNpc_Ds1_shopStickMoveMsgCheck__FUl */
BOOL daNpc_Ds1_shopStickMoveMsgCheck(u32 msgNo) {
    if((msgNo >= 0x1DD1 && msgNo <= 0x1DD3) || msgNo == 0x1DC0) return TRUE;
    return FALSE;
}

/* 000018AC-00001B04       .text normal_talk__11daNpc_Ds1_cFv */
u16 daNpc_Ds1_c::normal_talk() {
    u16 ret = l_msg->mStatus;
    if(ret == fopMsgStts_MSG_DISPLAYED_e){
        l_msg->mStatus = next_msgStatus(&mMsgNo);
        if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e){
            fopMsgM_messageSet(mMsgNo);
        }
    }
    else if(ret == fopMsgStts_BOX_CLOSED_e){
        if(mMsgNo == 0x1DCA){
            int beastIdx;
            s16 itemNum;
            if(mDrugChuchuNo == dItemNo_RED_JELLY_e){
                beastIdx = dBeastIdx_RED_JELLY_e;
                itemNum = -0xa;
            }
            else if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e){
                beastIdx = dBeastIdx_GREEN_JELLY_e;
                itemNum = DEMO_SELECT(-0x14, -0xf);
            }
            else {
                beastIdx = dBeastIdx_BLUE_JELLY_e;
                itemNum = DEMO_SELECT(-0x14, -0xf);
            }
            dComIfGp_setItemBeastNumCount(beastIdx, itemNum);
        }
        else if(mMsgNo == 0x1DC4){
            int beastIdx;
            if(mDrugChuchuNo == dItemNo_RED_JELLY_e){
                beastIdx = dBeastIdx_RED_JELLY_e;
            }
            else if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e){
                beastIdx = dBeastIdx_GREEN_JELLY_e;
            }
            else {
                beastIdx = dBeastIdx_BLUE_JELLY_e;
            }
            dComIfGp_setItemBeastNumCount(beastIdx, -5);
        }
        if(mMsgNo == 0x1DCA){
            field_0x887 = 4;
        }
        else if(mMsgNo == 0x1DCB || mMsgNo == 0x1DC4){
            field_0x887 = 3;
        }
        else if(mMsgNo == 0x1DCD || mMsgNo == 0x1DCC){
            field_0x887 = 0;
            if(mDrugChuchuNo != dItemNo_RED_JELLY_e){
                if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e) dComIfGs_onEventBit(dSv_event_flag_c::UNK_0D04);
                else dComIfGs_onEventBit(dSv_event_flag_c::UNK_0D02);
            }
            dComIfGp_setNextStage("Pdrgsh", 1, fopAcM_GetRoomNo(this));
        }
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
    }
    else if(ret == fopMsgStts_MSG_PREPARING_e) fopMsgM_demoMsgFlagOn();
    cXyz zoomPos = mShopCam.getItemZoomPos(100.0f);
    mShopItems.Item_ZoomUp(zoomPos);
    mpShopCursor->hide();
    return ret;
}

/* 00001B04-00001C4C       .text shop_talk__11daNpc_Ds1_cFv */
u16 daNpc_Ds1_c::shop_talk() {
    mpShopCursor->show();
    if(dShop_now_triggercheck(l_msg, &mStickControl, &mShopItems, &mMsgNo, NULL, NULL)){
        field_0x738 = 1;
        mNextMsgNo = 0;
    }
    u16 ret = l_msg->mStatus;
    if(ret == fopMsgStts_MSG_DISPLAYED_e || ret == fopMsgStts_MSG_CONTINUES_e){
        if (field_0x738 != 0) {
            field_0x738 = 0;
        }
        else{
            mNextMsgNo = mMsgNo;
            l_msg->mStatus = next_msgStatus(&mNextMsgNo);
            if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e){
                fopMsgM_messageSet(mNextMsgNo);
            }
        }
    }
    else if(ret == fopMsgStts_BOX_CLOSED_e){
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
        if(mMsgNo == 0x1DD4 || mMsgNo == 0x1DD5 || mMsgNo == 0x1DD6 || mMsgNo == 0x1DC4){
            field_0x887 = 3;
        }
        mShopItems.mSelectedItemIdx = -1;
    }
    else if(ret == 1){
        fopMsgM_demoMsgFlagOn();
    }
    return ret;
}

/* 00001C4C-00001E84       .text talk__11daNpc_Ds1_cFv */
u16 daNpc_Ds1_c::talk() {
    u16 ret = 0xff;
    if(field_0x899 == 0) {
        l_msgId = -1;
        l_msg = NULL;
        mMsgNo = getMsg();
        mNextMsgNo = 0;
        field_0x899 = 1;
        mItemNo = -1;
    }
    else if(field_0x899 != -1){
        if(l_msgId == -1){
            if(dComIfGp_event_chkTalkXY() && !dComIfGp_evmng_ChkPresentEnd()){
                return 0xff;
            }
            l_msgId = fopMsgM_messageSet(mMsgNo, this);
        }
        else if(l_msg == NULL){
            l_msg = fopMsgM_SearchByID(l_msgId);
            if(l_msg != NULL){
                if(mMsgNo != 0x1DC0) field_0x899 = 2;
                else field_0x899 = 3;
            }
        }
        else{
            setAnmFromMsgTag();
            switch(field_0x899) {
                case 2:
                    ret = normal_talk();
                    break;
                case 3:
                    ret = shop_talk();
                    break;
            }
            if(dComIfGp_checkMesgSendButton()){
                mMsgNo = l_msg->mMsgNo;
                if(!daNpc_Ds1_shopStickMoveMsgCheck(mMsgNo)){
                    if(!daNpc_Ds1_shopMsgCheck(mMsgNo) && 
                    (mShopItems.mSelectedItemIdx = -1, mShopItems.isHide())){
                        mShopItems.showItem();
                    }
                    field_0x899 = 2;
                }
                else{
                    if(mMsgNo == 0x1DC0 && 
                    (mShopItems.mSelectedItemIdx = -1, mShopItems.isHide())){
                        mShopItems.showItem();
                    }
                    field_0x899 = 3;
                }
            }
        }
    }
    mShopCam.SetSelectIdx(mShopItems.mSelectedItemIdx);
    return ret;
}

/* 00001E84-00002158       .text CreateInit__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::CreateInit() {
    cXyz loc2;
    loc2.setall(0.0f);
    field_0x756.x = current.angle.x;
    field_0x756.y = current.angle.y;
    field_0x756.z = current.angle.z;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    gravity = -30.0f;
    switch(mType){
        case 0:
        setAction(&daNpc_Ds1_c::wait_action, NULL);
        break;
    }
    mAttPos.set(current.pos);
    mStts.Init(0xff, 0xff, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    field_0x89A = 0;
    field_0x738 = 0;
    field_0x7D0 = 0;
    mItemNo = 0xff;
    field_0x886 = 0;
    mShopCam.setCamDataIdx(0);
    mShopItems.setItemDataIdx(0);
    mShopCam.setCamAction(NULL);
    mShopItems.setItemSetDataList();
    mShopItems.createItem(3, fopAcM_GetRoomNo(this));
    
    eventInfo.setXyEventCB(daNpc_Ds1_XyEventCB);
    mEventCut.setActorInfo("Ds1", this);
    mEventCut.setJntCtrlPtr(&mJntCtrl);
    field_0x888 = 4;
    mEventIdx[0] = dComIfGp_evmng_getEventIdx("CREATE_DRUG");
    mEventIdx[1] = dComIfGp_evmng_getEventIdx("GET_DRUG");
    mEventIdx[2] = dComIfGp_evmng_getEventIdx("PUT_ITEM");
    mEventIdx[3] = dComIfGp_evmng_getEventIdx("PUT_ITEM_FAIL");

    if(field_0x7D6 != 0){
        mpGtydsModel->setBaseTRMtx(cMtx_getIdentity());
        RoomEffectSet();
    }
    mLightInfluence.mPos.set(-60.0f, 123.0f, -555.0f);
    mLightInfluence.mColor.r = 0;
    mLightInfluence.mColor.g = 0;
    mLightInfluence.mColor.b = 0;
    mLightInfluence.mPower = 0;
    mLightInfluence.mFluctuation = 20.0f;
    dKy_plight_set(&mLightInfluence);
    return TRUE;
}

/* 00002158-000021A8       .text setAttention__11daNpc_Ds1_cFb */
void daNpc_Ds1_c::setAttention(bool attn) {
    if(!attn && attnSetCount>=2) return;
    attention_info.position.set(mAttPos.x, mAttPos.y + l_HIO.mChild[mType].mNpc.mAttnYOffset, mAttPos.z);
}

/* 000021A8-00002524       .text lookBack__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::lookBack() {
    cXyz playerEyePos;
    cXyz srcPos (0,0,0);
    
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    switch (field_0x894) {
        case 1:
            if(field_0x760 != 0){
                playerEyePos = dNpc_playerEyePos(l_HIO.mChild[mType].mNpc.m04);
                dstPos = &playerEyePos;
                srcPos = current.pos;
                srcPos.y = eyePos.y;
                setTexAnm(0);
            }
            else{
                dstPos = NULL;
                setTexAnm(0);
            }
            break;

        case 2:
            if(mShopCam.checkCamAction(NULL)){
                playerEyePos = dNpc_playerEyePos(l_HIO.mChild[mType].mNpc.m04);
            }
            else{
                if(mShopItems.mSelectedItemIdx == -1){
                    playerEyePos = mShopCam.getItemZoomPos(100.0f);
                }
                else{
                    cXyz shopCursorPos = mShopItems.getSelectItemBasePos();
                    playerEyePos = mShopItems.getSelectItemPos();
                    mpShopCursor->setPos(shopCursorPos);

                    mpShopCursor->setScale(l_HIO.mChild[mType].field_0x34,
                                           l_HIO.mChild[mType].field_0x38,
                                           l_HIO.mChild[mType].field_0x3C,
                                           l_HIO.mChild[mType].field_0x40, 
                                           l_HIO.mChild[mType].field_0x44);
                    mpShopCursor->anm_play();
                }
            }
            dstPos = &playerEyePos;
            srcPos = current.pos;
            srcPos.y = eyePos.y;
            
            break;   
    }

    if(checkAction(&daNpc_Ds1_c::event_action)){
        playerEyePos = dNpc_playerEyePos(l_HIO.mChild[mType].mNpc.m04);
        
        dstPos = &playerEyePos;
        srcPos = current.pos;
        srcPos.y = eyePos.y;
    }
    if(mJntCtrl.trnChk()) {
        cLib_addCalcAngleS2(&mVel, l_HIO.mChild[mType].mNpc.mMaxHeadTurnVel, 4, 0x800);
    }
    else mVel = 0;
    

    mJntCtrl.lookAtTarget(&current.angle.y, dstPos, srcPos, desiredYRot, mVel, true);

}

/* 00002524-00002578       .text wait01__11daNpc_Ds1_cFv */
bool daNpc_Ds1_c::wait01() {
    if(field_0x761 != 0){
        field_0x895 = field_0x894;
        field_0x894 = 2;
    }
    else{
        if(field_0x760 != 0) field_0x887 = 2;
        else{
            if(field_0x887 == 2) field_0x887 = 0;
        } 
    }
    return TRUE;
}

/* 00002578-00002760       .text talk01__11daNpc_Ds1_cFv */
bool daNpc_Ds1_c::talk01() {
    u16 talkVal = talk();
    if(talkVal == fopMsgStts_BOX_CLOSED_e){
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        field_0x894 = field_0x895;
        if(mMsgNo != 0x1dcd && mMsgNo != 0x1dcc){
            dComIfGp_event_reset();
            if(field_0x887 != 3){
                mShopCam.setCamAction(NULL);
            }
            player->offPlayerNoDraw();
        }
        else{
            setAction(&daNpc_Ds1_c::dummy_action, NULL);
        }
        
        field_0x761 = 0;
        setAnm(0, -1.0f);
        if(mMsgNo == 0x1DB4){
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1120);
        }
    }
    else if(talkVal == 8 && 
            daNpc_Ds1_shopMsgCheck(mMsgNo) && 
            mMsgNo == mShopItems.getSelectItemBuyMsg()){
        dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
        dComIfGp_setAStatusForce(dActStts_CANCEL_e);
    }
    return mpMorf->isMorf();
}

/* 00002760-00002A04       .text getdemo_action__11daNpc_Ds1_cFPv */
BOOL daNpc_Ds1_c::getdemo_action(void*) {
    int staffIdx = dComIfGp_evmng_getMyStaffId("Ds1");
    if(mActionStatus == ACTION_STARTING){
        u8 itemNo;
        if(mItemNo != dItemNo_NONE_e) itemNo = mItemNo;
        else{
            if(mDrugChuchuNo == dItemNo_RED_JELLY_e){
                itemNo = dItemNo_RED_POTION_e;
            }
            else if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e){
                itemNo = dItemNo_GREEN_POTION_e;
            }
            else itemNo = dItemNo_BLUE_POTION_e;
        }
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        player->offPlayerNoDraw();
        field_0x894 = field_0x895;
        mShopCam.setCamAction(NULL);
        
        fpc_ProcID itemPtId = fopAcM_createItemForPresentDemo(&current.pos, itemNo, 0, -1, DEMO_SELECT(-1, fopAcM_GetRoomNo(this)));
        if(itemPtId != -1){
            dComIfGp_event_setItemPartnerId(itemPtId);
        }
        dComIfGp_evmng_cutEnd(staffIdx);
        mActionStatus++;
    }
    else if(mActionStatus != ACTION_ENDING){
        fopMsgM_demoMsgFlagOn();
        dComIfGp_evmng_cutEnd(staffIdx);
        if(dComIfGp_evmng_endCheck(mEventIdx[1])){
            field_0x887 = 1;
            if(mItemNo != 0xff){
                field_0x7D0 = 0x1dda;
                mShopItems.showItem();
                mItemNo = -1;
                mShopItems.mSelectedItemIdx = -1;
            }
            else{
                if(daNpc_Ds1_checkCreateDrugChuchu(mDrugChuchuNo)){
                    field_0x7D0 = 0x1dc6;
                }
                else{
                    field_0x7D0 = 0x1dcd;
                }
            }
            dComIfGp_event_reset();
            if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e){
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0D04);
            }
            else if(mDrugChuchuNo == dItemNo_BLUE_JELLY_e){
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0D02);
            }
            setAction(&daNpc_Ds1_c::wait_action, NULL);
        }
    }
    return TRUE;
}


/* 00002A04-00002BD0       .text privateCut__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::privateCut() {
    ActionFunc temp = &daNpc_Ds1_c::wait_action;
    static char* cut_name_tbl[] = {
        "TALKMSG",
        "CONTINUE_TALK",
        "SHOWITEM",
        "HEADSWING",
        "SOUND",
        "SETANM",
        "MOVEPOS",
        "INITPOS",
        "JNTLOCK",
        "PLAYER_HIDE"
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
    if(staffIdx == -1) return FALSE;
    int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), true, 0);
    if(actIdx == -1){
        dComIfGp_evmng_cutEnd(staffIdx);
    }
    else{
        if(dComIfGp_evmng_getIsAddvance(staffIdx)){
            switch (actIdx) {
                case 0:
                    evn_talk_init(staffIdx);
                    break;
                case 1:
                    evn_continue_talk_init(staffIdx);
                    break;
                case 2:
                    evn_ItemModel_init(staffIdx);
                    break;
                case 3:
                    evn_head_swing_init(staffIdx);
                    break;
                case 5:
                    evn_setAnm_init(staffIdx);
                    break;
                case 6:
                    evn_move_pos_init(staffIdx);
                    break;
                case 7:
                    evn_init_pos_init(staffIdx);
                    break;
                case 8:
                    evn_jnt_lock_init(staffIdx);
                    break;
                case 9:
                    evn_player_hide_init(staffIdx);
                    break;
            }
        }

        int evn_ret = 0;

        switch(actIdx){
            case 0:
            case 1:
                evn_ret = evn_talk();
                break;
            case 5:
                evn_ret = evn_Anm();
                break;
            case 6:
                evn_ret = evn_move_pos();
                break;
            default:
                evn_ret = 1;
                break;
        }

        if(evn_ret != 0){
            dComIfGp_evmng_cutEnd(staffIdx);
        }

    }
    return TRUE;
}

/* 00002BD0-00002E00       .text evn_setAnm_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_setAnm_init(int staffIdx) {
    static GXColor ef_prmColor[] = {
        {0xbc,  0x27, 0x40, 0xff},
        {0x27,  0xbc, 0x40, 0xff},
        {0x27,  0x63, 0xbc, 0xff}
    };

    static GXColor ef_envColor[] = {
        {0xde,  0x80, 0x38, 0xff},
        {0x34,  0xde, 0x38, 0xff},
        {0x38,  0xde, 0x80, 0xff}
    };


    int* anmNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "AnmNo");
    int* count = dComIfGp_evmng_getMyIntegerP(staffIdx, "count");
    f32* hokan = dComIfGp_evmng_getMyFloatP(staffIdx, "hokan");

    if(anmNo != NULL){
        f32 anmFloat = -1.0f;
        if(hokan != NULL){
            anmFloat = *hokan;
        }
        setAnm(*anmNo, anmFloat);
        if(count != NULL) field_0x886 = *count;
        else field_0x886 = 0;
    }

    if (field_0x885 == 6){
        int colorIdx;
        if(mDrugChuchuNo == dItemNo_RED_JELLY_e) colorIdx = 0;
        else if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e) colorIdx = 1;
        else colorIdx = 2;
        if(mpBaseEmitter == NULL){
            mpBaseEmitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_CCDRUGSTORE00, &current.pos, NULL, NULL, -1, NULL, -1, &ef_prmColor[colorIdx], &ef_envColor[colorIdx]);
            mLightInfluence.mColor.r = ef_prmColor[colorIdx].r << 2; 
            mLightInfluence.mColor.g = ef_prmColor[colorIdx].g << 2; 
            mLightInfluence.mColor.b = ef_prmColor[colorIdx].b << 2; 
        }
        if(field_0x76C[0] == NULL){
            field_0x76C[0] = dComIfGp_particle_set(dPa_name::ID_AK_SN_CCDRUGSTORE01, &current.pos, NULL, NULL, -1, NULL, -1, &ef_prmColor[colorIdx], &ef_envColor[colorIdx]);
        }
    }
    return TRUE;
}

/* 00002E00-000030A0       .text evn_Anm__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::evn_Anm() {
    if(mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)){
        field_0x886--;
    }
    if(field_0x886 <= 0) return TRUE;

    if(field_0x885 == 6){
        cXyz output;
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_handL_jnt_num));
        
        mDoMtx_stack_c::multVecZero(&output); 

        if(mpBaseEmitter != NULL) mpBaseEmitter->setGlobalTranslation(output.x, output.y, output.z);
        if(field_0x76C[0] != NULL) field_0x76C[0]->setGlobalTranslation(output.x, output.y, output.z);
        if(mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)){
            if(mpBaseEmitter != NULL){
                mpBaseEmitter->becomeInvalidEmitter();
                mpBaseEmitter = NULL;
            }
            if(field_0x76C[0] != NULL){
                field_0x76C[0]->becomeInvalidEmitter();
                field_0x76C[0] = NULL;
            }
        }
        if(mpMorf->checkFrame(135.0f)){
            dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
            fopAcM_seStart(this, JA_SE_OBJ_CK_CHEMICAL_BOMB, 0);
            mLightInfluence.mPower = 100.0f;
            
        }
        else{
            if(mpMorf->checkFrame(DEMO_SELECT(REG10_F(7)+10.0f, 10.0f))) {
                field_0x7D5 |= 2;
            }
        }
    }
    else if(field_0x885 == 8 && mpMorf->checkFrame(128.0f)) field_0x7D5 |= 1;
    return FALSE;
}

/* 000030A0-00003168       .text evn_talk_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_talk_init(int staffIdx) {
    int* msgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    int* endMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMsgNo");
    l_msgId = -1;
    l_msg = 0;
    if(msgNo != NULL) mMsgNo = *msgNo;
    else mMsgNo = 0;
    if(endMsgNo != NULL) mEndMsgNo = *endMsgNo;
    else mEndMsgNo = 0;

    return TRUE;
}

/* 00003168-000031D0       .text evn_continue_talk_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_continue_talk_init(int staffIdx) {
    int* prm = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMsgNo");
    if(prm != NULL){
        mEndMsgNo = *prm;  
    }
    else mEndMsgNo = 0;
    return TRUE;
}

/* 000031D0-000033AC       .text evn_talk__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::evn_talk() {
    if(l_msgId == fpcM_ERROR_PROCESS_ID_e){
        l_msgId = fopMsgM_messageSet(mMsgNo, &eyePos);
    }
    else if(l_msg == NULL){
        l_msg = fopMsgM_SearchByID(l_msgId);
        fopMsgM_demoMsgFlagOn();
    }
    else{
        setAnmFromMsgTag();
        u16 mode = l_msg->mStatus;
        if(mode == fopMsgStts_MSG_DISPLAYED_e) {
            l_msg->mStatus = next_msgStatus(&mMsgNo);   
            if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e){
                fopMsgM_messageSet(mMsgNo);
            }
        }else{
            if(mode == fopMsgStts_BOX_CLOSED_e){
                if(mMsgNo == 0x1DCA){
                    int beastIdx;
                    s16 itemNum;
                    if(mDrugChuchuNo == dItemNo_RED_JELLY_e){
                        beastIdx = dBeastIdx_RED_JELLY_e;
                        itemNum = -0xa;
                    }
                    else if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e){
                        beastIdx = dBeastIdx_GREEN_JELLY_e;
                        itemNum = DEMO_SELECT(-0x14, -0xf);
                    }
                    else {
                        beastIdx = dBeastIdx_BLUE_JELLY_e;
                        itemNum = DEMO_SELECT(-0x14, -0xf);
                    }
                    dComIfGp_setItemBeastNumCount(beastIdx, itemNum);
                }
                else if(mMsgNo == 0x1DC4){
                    int beastIdx;
                    if(mDrugChuchuNo == dItemNo_RED_JELLY_e){
                        beastIdx = dBeastIdx_RED_JELLY_e;
                    }
                    else if(mDrugChuchuNo == dItemNo_GREEN_JELLY_e){
                        beastIdx = dBeastIdx_GREEN_JELLY_e;
                    }
                    else {
                        beastIdx = dBeastIdx_BLUE_JELLY_e;
                    }
                    dComIfGp_setItemBeastNumCount(beastIdx, DEMO_SELECT(-0xa, -5));
                }
                l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                l_msg = NULL;
                l_msgId = fpcM_ERROR_PROCESS_ID_e;
                
                return TRUE;
            }
            if((mode == fopMsgStts_BOX_OPENING_e || mode == fopMsgStts_MSG_TYPING_e) && mMsgNo == mEndMsgNo){
                mEndMsgNo = 0;
                return TRUE;
            }
        }
    }
    return FALSE;
}

/* 000033AC-00003478       .text evn_jnt_lock_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_jnt_lock_init(int staffIdx) {
    int lockMode;
    int* prm = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");
    if (prm != NULL) lockMode = *prm;
    else lockMode = 0;

    switch (lockMode) {
        case 0:
            mJntCtrl.offHeadLock();
            mJntCtrl.offBackBoneLock();
            break;
        case 1:
            mJntCtrl.onHeadLock();
            mJntCtrl.offBackBoneLock();
            break;
        case 2:
            mJntCtrl.offHeadLock();
            mJntCtrl.onBackBoneLock();
            break;
        case 3:
            mJntCtrl.onHeadLock();
            mJntCtrl.onBackBoneLock();
            break;
    }
    return TRUE;
}

/* 00003478-0000350C       .text evn_player_hide_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_player_hide_init(int staffIdx) {
    int drawMode;
    int* prm = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");
    if (prm != NULL) drawMode = *prm;
    else drawMode = 0;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (drawMode) {
        case 0:
            player->offPlayerNoDraw(); 
            break;
        case 1:
            player->onPlayerNoDraw();
            break;
    }
    return TRUE;
}

/* 0000350C-000035B8       .text evn_head_swing_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_head_swing_init(int staffIdx) {
    int swingMode;
    int* prm = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");
    if (prm != NULL) swingMode = *prm;
    else swingMode = 0;

    switch (swingMode) {
        case 0:
            mHeadAnm.swing_horizone_init(2,0x1000,0x1000,1);
            break;
        case 1:
            mHeadAnm.swing_vertical_init(2,0x1000,0x800,1);
            break;
    }
    return TRUE;
}

/* 000035B8-0000361C       .text evn_ItemModel_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_ItemModel_init(int staffIdx) {
    u32 val;
    int* prm = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");
    if(prm != NULL) val = *prm;
    else val = 0;
    field_0x7D5 = val;
    return TRUE;
}

/* 0000361C-000036D4       .text evn_move_pos_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_move_pos_init(int staffIdx) {
    cXyz* pos = dComIfGp_evmng_getMyXyzP(staffIdx, "pos");
    int* angle = dComIfGp_evmng_getMyIntegerP(staffIdx, "angle");
    if(pos != NULL) mTargetPos.set(*pos);
    else mTargetPos.set(home.pos);
    return TRUE;
}

/* 000036D4-000037F0       .text evn_move_pos__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::evn_move_pos() {
    cLib_addCalcPos2(&current.pos, mTargetPos, 0.25f, 5.0f);
    cXyz temp = mTargetPos - current.pos;
    if(temp.abs() < 1.0f) return TRUE;
    mTargetAngle = cLib_targetAngleY(&current.pos, &mTargetPos);
    cLib_addCalcAngleS2(&current.angle.y, mTargetAngle, 4, 0x1000);
    return FALSE;
}

/* 000037F0-000038F4       .text evn_init_pos_init__11daNpc_Ds1_cFi */
BOOL daNpc_Ds1_c::evn_init_pos_init(int staffIdx) {
    cXyz* pos = dComIfGp_evmng_getMyXyzP(staffIdx, "pos");
    int* angle = dComIfGp_evmng_getMyIntegerP(staffIdx, "angle");

    if(pos != NULL){
        old.pos.set(*pos);
        current.pos.set(old.pos);
    }
    else{
        old.pos.set(home.pos);
        current.pos.set(old.pos);
    }

    if(angle != NULL) current.angle.y = *angle;
    else current.angle.y = home.angle.y;

    return TRUE;
}

/* 000038F4-00003AF8       .text event_action__11daNpc_Ds1_cFPv */
BOOL daNpc_Ds1_c::event_action(void*) {
    if(mActionStatus == ACTION_STARTING){
        dComIfGp_evmng_getMyStaffId("Ds1");
        ((daPy_py_c*)dComIfGp_getPlayer(0))->offPlayerNoDraw();
        field_0x894 = field_0x895;
        mShopCam.setCamAction(NULL);
        field_0x887 = 0;
        mActionStatus++;
    }
    else if(mActionStatus != ACTION_ENDING){
        privateCut();
        if(dComIfGp_evmng_endCheck(mEventIdx[field_0x888])){
            if(field_0x888 == 2){
                field_0x887 = 4;
                field_0x888 = 0;
            }
            else if(field_0x888 == 3 && mMsgNo == 0x1dc4){
                field_0x887 = 3;
                field_0x888 = 4;
            }
            else if(field_0x888 == 0){
                field_0x887 = 1;
                field_0x7D0 = 0x1dcb;
                field_0x888 = 4;
            }
            dComIfGp_event_reset();
            setAction(&daNpc_Ds1_c::wait_action, NULL);
        }
        lookBack();
    }
    return TRUE;
}

/* 00003AF8-00003BF0       .text wait_action__11daNpc_Ds1_cFPv */
BOOL daNpc_Ds1_c::wait_action(void*) {
    if(mActionStatus == ACTION_STARTING){
        field_0x894 = 1;
        mActionStatus++;
    }
    else if(mActionStatus != ACTION_ENDING){
        s16 ang = current.angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
        field_0x760 = chkAttention(current.pos, ang);
        bool attn;
        switch (field_0x894) {
            case 1: 
                attn = wait01();
                break;
            case 2:
                attn = talk01();
                break;
            default:
                attn = false;
                break;
        }
        lookBack();
        setAttention(attn);
    }
    return TRUE;
}

/* 00003BF0-00003C0C       .text dummy_action__11daNpc_Ds1_cFPv */
BOOL daNpc_Ds1_c::dummy_action(void*) {
    if(mActionStatus == ACTION_STARTING) mActionStatus++;
    return TRUE;
}

/* 00003C0C-00003EE4       .text RoomEffectSet__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::RoomEffectSet() {
    cXyz particlePos[] = {
        cXyz::Zero,
        cXyz(-158.0f, 160.0f, -663.0f),
        cXyz(18.0f, 160.0f, -652.0f),
        cXyz(-220.0f, 105.0f, -590.0f)
    };

    GXColor colors[] = {
        {0x41, 0x4d, 0x6f, 0xff},
        {0x90, 0x8d, 0x56, 0xff},
        {0x78, 0x46, 0x5a, 0xff},
    };

    field_0x76C[1] = dComIfGp_particle_set(dPa_name::ID_IT_SN_TYDS_LAMP00,   &particlePos[0]);
    field_0x76C[2] = dComIfGp_particle_set(dPa_name::ID_IT_SN_TYDS_SMOKEA00, &particlePos[0]);
    field_0x76C[3] = dComIfGp_particle_set(dPa_name::ID_IT_SN_TYDS_SMOKEB00, &particlePos[0]);
    field_0x76C[4] = dComIfGp_particle_set(dPa_name::ID_IT_SN_TYDS_SMOKEC00, &particlePos[0]);
    field_0x76C[5] = dComIfGp_particle_set(dPa_name::ID_IT_SN_TYDS_FUTTOU00, &particlePos[1], NULL, NULL, 0xff, NULL, -1, &colors[0]);
    field_0x76C[6] = dComIfGp_particle_set(dPa_name::ID_IT_SN_TYDS_FUTTOU00, &particlePos[2], NULL, NULL, 0xff, NULL, -1, &colors[1]);
    if(field_0x76C[6] != NULL){
        field_0x76C[6]->setLifeTime(0xd);
    }
    field_0x76C[7] = dComIfGp_particle_set(dPa_name::ID_IT_SN_TYDS_FUTTOU00, &particlePos[3], NULL, NULL, 0xff, NULL, -1, &colors[2]);
}

/* 00003EE4-00003F20       .text RoomEffectDelete__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::RoomEffectDelete() {
    /* Nonmatching */
    for (int i = 0; i < ARRAY_SIZE(field_0x76C) - 1; i++) {
        if(field_0x76C[1+i] != NULL){
            field_0x76C[1+i]->becomeInvalidEmitter();
        }
    }
}

/* 00003F20-000041D0       .text _draw__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::_draw() {
    /* Nonmatching (demo) */
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(modelData, mBtpAnmFrame);
    mpMorf->updateDL();
    modelData->getMaterialTable().removeTexNoAnimator(mBtpAnm.getBtpAnm());
    if(field_0x7D5 & 1){
        g_env_light.setLightTevColorType(mpFlascoModel, &tevStr);
        mpFlascoModel->setBaseTRMtx(model->getAnmMtx(m_handL_jnt_num));
        mDoExt_modelUpdateDL(mpFlascoModel);
    }
    else{
        g_env_light.setLightTevColorType(mpFlascoModel, &tevStr);
        mDoMtx_stack_c::transS(DEMO_SELECT(REG10_F(0) + -90.0f, -90.0f), DEMO_SELECT(REG10_F(1) + 95.0f, 95.0f),DEMO_SELECT(REG10_F(2) + -580.0f, -580.0f));
        mDoMtx_stack_c::ZXYrotM(0x76C, 0, 0);
        mpFlascoModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoExt_modelUpdateDL(mpFlascoModel);
    }

    if(field_0x7D5 & 2){
        g_env_light.setLightTevColorType(mpJarModel, &tevStr);
        mpJarModel->setBaseTRMtx(model->getAnmMtx(m_handR_jnt_num));
        mDoExt_modelUpdateDL(mpJarModel);
        
    }
    else{
        g_env_light.setLightTevColorType(mpJarModel, &tevStr);
        mDoMtx_stack_c::transS(DEMO_SELECT(REG10_F(3) + -11.0f, -11.0f), DEMO_SELECT(REG10_F(4) + 101.0f, 101.0f), DEMO_SELECT(REG10_F(5) + -545.0f, -545.0f));
        mDoMtx_stack_c::ZXYrotM(DEMO_SELECT(REG10_S(3) + -0x8000, -0x8000), DEMO_SELECT(REG10_S(4) + 0x3C8C, 0x3C8C), DEMO_SELECT(REG10_S(5), 0));
        mpJarModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoExt_modelUpdateDL(mpJarModel);
    }
    cXyz pos;
    pos.set(current.pos.x, current.pos.y + 130.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(mShadowId, 
                                     1, 
                                     mpMorf->getModel(), 
                                     &pos, 
                                     800.0f, 
                                     20.0f, 
                                     current.pos.y, 
                                     mAcch.GetGroundH(), 
                                     mAcch.m_gnd, 
                                     &tevStr);

    if(mShopItems.mSelectedItemIdx >= 0){
        mpShopCursor->draw();
    }
    if(field_0x7D6 != 0){
        mGtydsAnm.entry(mpGtydsModel->getModelData());
        mDoExt_modelUpdateDL(mpGtydsModel);
    }
    dSnap_RegistFig(DSNAP_TYPE_DS1, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

#if VERSION > VERSION_DEMO
static cXyz se_pos[4] = {
    cXyz(-158.0f, 160.0f, -663.0f),
    cXyz(18.0f, 160.0f, -652.0f),
    cXyz(-220.0f, 105.0f, -590.0f),
    cXyz(-225.0f, 260.0f, -590.0f),
};
#endif
/* 000041D0-00004554       .text _execute__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::_execute() {
    s16 maxSpineRotY;
    s16 minHeadRotY;
    s16 minSpineRotY;
    s16 maxHeadRotY;

    if(!checkAction(&daNpc_Ds1_c::event_action)){
        maxHeadRotY = l_HIO.mChild[mType].mNpc.mMaxHeadY;
        maxSpineRotY = l_HIO.mChild[mType].mNpc.mMaxBackboneY;
        minHeadRotY = l_HIO.mChild[mType].mNpc.mMinHeadY;
        minSpineRotY = l_HIO.mChild[mType].mNpc.mMinBackboneY;
    }
    else{
        maxHeadRotY = 0x38e0;
        maxSpineRotY = 0x1c70;
        minHeadRotY = -0x1c70;
        minSpineRotY = -0x38e0;
    }
    
    mJntCtrl.setParam(l_HIO.mChild[mType].mNpc.mMaxBackboneX, 
                      maxSpineRotY, 
                      l_HIO.mChild[mType].mNpc.mMinBackboneX,
                      minSpineRotY,
                      l_HIO.mChild[mType].mNpc.mMaxHeadX,
                      maxHeadRotY,
                      l_HIO.mChild[mType].mNpc.mMinHeadX,
                      minHeadRotY,
                      l_HIO.mChild[mType].mNpc.mMaxTurnStep);

    playTexPatternAnm();
    s8 roomNo = fopAcM_GetRoomNo(this);
    u32 mtrlSndId;
#if VERSION > VERSION_DEMO
    if(!mAcch.ChkGroundHit()){
        mtrlSndId = 0;
    }
    else{
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);
    }
#else
    if(mAcch.ChkGroundHit() != FALSE){
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);    
    }
    else{
        mtrlSndId = 0;
    }
#endif
    
    field_0x75E = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
    if(mpMorf->getFrame() < mPrevMorfFrame){
        field_0x75E = 1;
    }
    mPrevMorfFrame = mpMorf->getFrame();
    checkOrder();
    (this->*mCurrActionFunc)(NULL);
    mShopCam.move();
    mShopItems.Item_Move();
    eventOrder();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);


    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    setCollision();



    if(field_0x7D6 != 0){
#if VERSION == VERSION_DEMO
        static cXyz se_pos[3] = {
            cXyz(-158.0f, 160.0f, -663.0f),
            cXyz(18.0f, 160.0f, -652.0f),
            cXyz(-220.0f, 105.0f, -590.0f),
        };
#endif
        mDoAud_seStart(JA_SE_OBJ_CK_BOIL_L,
                       &se_pos[0], 
                       0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                       
        mDoAud_seStart(JA_SE_OBJ_CK_BOIL_C,
                       &se_pos[1], 
                       0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        mDoAud_seStart(JA_SE_OBJ_CK_BOIL_R,
                       &se_pos[2], 
                       0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        u8 chk = field_0x7D7;
        field_0x7D7++;
        if(chk>=0x32){
            mDoAud_seStart(JA_SE_OBJ_CK_FLASK_STEAM,
                           DEMO_SELECT(&cXyz(-225.0f, 260.0f, -590.0f), &se_pos[3]), 
                           0,
                           dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            field_0x7D7 = 0;
        }
        mGtydsAnm.play();
    }
    cLib_addCalc0(&mLightInfluence.mPower, 0.25f, 20.0f);
    return TRUE;

}

/* 00004554-0000465C       .text _delete__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::_delete() {
    dKy_plight_cut(&mLightInfluence);
    dComIfG_resDeleteDemo(&mPhs, m_arcname);
#if VERSION > VERSION_DEMO
    if(heap != NULL && mpMorf != NULL){
#else
    if(mpMorf != NULL){
#endif
        mpMorf->stopZelAnime();
    }
#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&se_pos[0]);
    mDoAud_seDeleteObject(&se_pos[1]);
    mDoAud_seDeleteObject(&se_pos[2]);
    mDoAud_seDeleteObject(&se_pos[3]);   
#endif
    RoomEffectDelete();
    if(l_HIO.field_0x08 >= 0 && (l_HIO.field_0x08 -= 1, l_HIO.field_0x08 < 0)){
        mDoHIO_deleteChild(l_HIO.mChildId);
    }
    return TRUE;
}

/* 0000465C-0000467C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->CreateHeap();
}

/* 0000467C-000047BC       .text _create__11daNpc_Ds1_cFv */
cPhs_State daNpc_Ds1_c::_create() {
#if VERSION > VERSION_DEMO
    fopAcM_ct(this, daNpc_Ds1_c);
    cPhs_State phase = dComIfG_resLoad(&mPhs, m_arcname);
    if(phase == cPhs_COMPLEATE_e){
#else
    cPhs_State phase = dComIfG_resLoad(&mPhs, m_arcname);
    if(phase == cPhs_COMPLEATE_e){
        fopAcM_ct(this, daNpc_Ds1_c);
#endif
        mType = fopAcM_GetParam(this) >> 0x14 & 0xf;
        switch(mType) {
            case 0:
                mType=0;
                break;
            
            default:
                mType=0;
                break;
        }
        if(!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0x8340)) return cPhs_ERROR_e;
        cullMtx = mpMorf->getModel()->getBaseTRMtx();
        if(l_HIO.field_0x08 < 0){
            l_HIO.mChildId = mDoHIO_createChild("薬屋店員", &l_HIO);
        }
        l_HIO.field_0x08++;
        if(!CreateInit()) return cPhs_ERROR_e;
    }
    return phase;
}

/* 00004E08-000052D4       .text CreateHeap__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BDL_CK_e));
    mpMorf = new mDoExt_McaMorf( modelData,
                                      NULL,
                                      NULL,
                                      static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BCK_WAIT01_e)),
                                      J3DFrameCtrl::EMode_LOOP,
                                      1.0, 0, -1, 1, NULL, 0, 0x11020203);
    if(mpMorf == NULL || mpMorf->getModel() == NULL){
#if VERSION > VERSION_DEMO
        mpMorf = NULL;
#endif
        return false;
    }
    m_head_jnt_num = modelData->getJointName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(0x9CE, 0x9DF), m_head_jnt_num >= 0);

    m_backbone_jnt_num = modelData->getJointName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(0x9D1, 0x9E2), m_backbone_jnt_num >= 0);

    m_handL_jnt_num = modelData->getJointName()->getIndex("handL");
    JUT_ASSERT(DEMO_SELECT(0x9D4, 0x9E5), m_handL_jnt_num >= 0);
    m_handR_jnt_num = modelData->getJointName()->getIndex("handR");
    JUT_ASSERT(DEMO_SELECT(0x9D6, 0x9E7), m_handR_jnt_num >= 0);

    switch(mType){
        case 0:
            mBtpResIDIndex = 1;
            break;
    }

#if VERSION > VERSION_DEMO
    if(!initTexPatternAnm(false)) return false;
#else 
    initTexPatternAnm(false);
#endif

    J3DModelData* gtydsModel = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BDL_GTYDS00_e));
    J3DAnmTextureSRTKey* pAnm = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BTK_GTYDS00_e));
    mpGtydsModel = mDoExt_J3DModel__create(gtydsModel, 0, 0x11020203);
    mGtydsAnm.init(gtydsModel, pAnm, true, J3DFrameCtrl::EMode_LOOP);
    field_0x7D6 = 1;
    J3DModelData* flascoModel = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BDL_CK_FLASCO_e));
    J3DModelData* jarModel = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BDL_CK_JAR_e));
    if(flascoModel == NULL || jarModel == NULL) return false;

    mpFlascoModel = mDoExt_J3DModel__create(flascoModel, 0, 0x11020203);
    mpJarModel = mDoExt_J3DModel__create(jarModel, 0, 0x11020203);
    if(mpFlascoModel == NULL || mpJarModel == NULL) return false;

    for (u16 i = 0; i<modelData->getJointNum(); i++) {
        if(i == m_head_jnt_num || i == m_backbone_jnt_num){
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ds);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 0.0f);
#if VERSION > VERSION_DEMO
    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);
#else
    cXyz* acchSpeed = &speed;
    cXyz* oldPos = &old.pos;
    cXyz* pos = &current.pos;
    mAcch.Set(pos, oldPos, this, 1, &mAcchCir, acchSpeed);
#endif
    J3DAnmTevRegKey* regKey = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BRK_SHOP_CURSOR01_e));
    J3DModelData* cursorModel = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, dRes_INDEX_DS_BMD_SHOP_CURSOR01_e));
    mpShopCursor = ShopCursor_create(cursorModel, regKey, l_HIO.mChild[mType].field_0x34);
    if(mpShopCursor != NULL) return true;
    else return false;
}

/* 000052D4-000052F4       .text daNpc_Ds1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ds1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_create();
}

/* 000052F4-00005314       .text daNpc_Ds1_Delete__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_Delete(daNpc_Ds1_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_delete();
}

/* 00005314-00005334       .text daNpc_Ds1_Execute__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_Execute(daNpc_Ds1_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_execute();
}

/* 00005334-00005354       .text daNpc_Ds1_Draw__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_Draw(daNpc_Ds1_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_draw();
}

/* 00005354-0000535C       .text daNpc_Ds1_IsDelete__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_IsDelete(daNpc_Ds1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ds1_Method = {
    (process_method_func)daNpc_Ds1_Create,
    (process_method_func)daNpc_Ds1_Delete,
    (process_method_func)daNpc_Ds1_Execute,
    (process_method_func)daNpc_Ds1_IsDelete,
    (process_method_func)daNpc_Ds1_Draw,
};

actor_process_profile_definition g_profile_NPC_DS1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_DS1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ds1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_DS1_e,
    /* Actor SubMtd */ &l_daNpc_Ds1_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
