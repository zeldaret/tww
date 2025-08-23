/**
 * d_a_npc_photo.cpp
 * NPC - Lenzo
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_photo.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_lib_game.h"
#include "d/d_com_inf_game.h"
#include "d/d_a_obj.h"
#include "d/d_path.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_camera.h"
#include "d/res/res_po.h"
#include "d/d_snap.h"
#include "d/d_kankyo_rain.h"
#include "d/d_picture_box.h"
#include "d/actor/d_a_tag_photo.h"

extern dCcD_SrcCyl dNpc_cyl_src;

const char daNpcPhoto_c::m_arcname[] = "Auc";


static const char* l_arcname_tbl[] = {
    "Po"
};

static sPhotoAnmDat l_npc_anm_wait[] = {
    {
        0x00,
        0x08,
        0xFF,
    },
};

static sPhotoAnmDat l_npc_anm_talk[] = {
    {
        0x01,
        0x08,
        0xFF,
    },
};

static sPhotoAnmDat l_npc_anm_walk[] = {
    {
        0x03,
        0x08,
        0xFF,
    },
};

static sPhotoAnmDat l_npc_anm_spit[] = {
    {    
        0x04,
        0x08,
        0x01
    },
    {
        0x00,
        0x08,
        0xFF,
    },
};

static sPhotoAnmDat l_npc_anm_talk2[] = {
    {
        0x02,
        0x08,
        0x03,
    },
    {
        0x00,
        0x08,
        0xFF,
    },
};

static sPhotoAnmDat l_npc_anm_talk4[] = {
    {
        0x02,
        0x08,
        0x01,
    },
    {
        0x01,
        0x08,
        0xFF,
    },
};

struct NpcDatStruct {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ s16 field_0x0E;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s16 field_0x4A;
    /* 0x4C */ s16 field_0x4C;
    /* 0x4E */ s16 field_0x4E;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ bool field_0x52;
    /* 0x53 */ bool field_0x53;
}; // Size: 0x54

static NpcDatStruct l_npc_dat = {
    0.0f,
    0x09C4,
    0x07D0,
    0x1388,
    0x1F40,
    0xFF6A,
    0xFE00,
    0xFC18,
    0xE0C0,
    0x01f4,
    0x0320,
    0x0708,
    0.0f,
    215.0f,
    30.0f,
    0x7FFF,
    200.0f,
    300.0f,
    -50.0f,
    0.3f,
    5.0f,
    1.3f,
    0x03E8,
    0x0006,
    0x0400,
    0x001E,
    0x001E,
    0x270F,
    0x270F,
    true,
    true,
};

static u32 l_msg_1st_talk[] = {
    0x2A31,
    0x2A32,
    0x2A33,
    0x0000
};

static u32 l_msg_2nd_talk[] = {
    0x2A34,
    0x0000
};

static u32 l_msg_1st_photo[] = {
    0x2A35,
    0x2A36,
    0x0000
};

static u32 l_msg_2nd_photo[] = {
    0x2A37,
    0x2A38,
    0x0000
};

static u32 l_msg_1st_order[] = {
    0x2A39,
    0x2A3A,
    0x2A3C,
    0x2A3D,
    0x2A3E,
    0x2A3F,
    0x2A40,
    0x2A41,
    0x2A42,
    0x2A43,
    0x0001,
};

static s16 l_msg_1st_order_c[] = {
    0xFFFF,
    0xFF00,
	0xFF01,
    0xFFFF,
	0x0002
};

static u32 l_msg_1st_order_not_end[] = {
    0x2A44,
    0x2A45,
    0x0000
};

static u16 l_msg_1st_order_not_end_c[] = {
    0xFF02
};

static u32 l_msg_2nd_order[] = {
    0x2A46,
    0x2A47,
    0x2A48,
    0x0003
};

static u8 l_msg_2nd_order_c[] = {
    0xFF,
    0x00,
    0xFF
};

static u32 l_msg_2nd_order_not_end[] = {
    0x2A49,
    0x2A4A,
    0x0000
};

static u16 l_msg_2nd_order_not_end_c[] = {
    0xFF02
};

static u32 l_msg_3rd_order[] = {
    0x2A4B,
    0x2A4C,
    0x2A4D,
    0x2A4E,
    0x0005,
};

static u32 l_msg_3rd_order_c[] = {
    0xFF00FF02
};

static u32 l_msg_3rd_order_not_end[] = {
    0x2A4F,
    0x2A50,
    0x0000,
};

static u16 l_msg_3rd_order_not_end_c[] = {
    0xFFFF
};

static u32 l_msg_3rd_order_end[] = {
    0x2A51,
    0x0000,
};

static u32 l_msg_not_color[] = {
    0x2A52,
    0x2A53,
    0x0000
};

static u16 l_msg_not_color_c[] = {
    0xFF00
};

static u32 l_msg_color[] = {
    0x2A54,
    0x2A55,
    0x0000
};

static u16 l_msg_color_c[] = {
    0xFF01
};

static u32 l_msg_week_1st[] = {
    0x3781,
    0x3782,
    0x3783,
    0x3784,
    0x3785,
    0x0000
};

static u32 l_msg_week0[] = {
    0x3779,
    0x377A,
    0x3785,
    0x0000
};

static u32 l_msg_week1[] = {
    0x3779,
    0x377B,
    0x3785,
    0x0000
};

static u32 l_msg_week2[] = {
    0x3779,
    0x377C,
    0x3785,
    0x0000
};

static u32 l_msg_week3[] = {
    0x3779,
    0x377D,
    0x3785,
    0x0000
};

static u32 l_msg_week4[] = {
    0x3779,
    0x377E,
    0x3785,
    0x0000
};

static u32 l_msg_week5[] = {
    0x3779,
    0x377F,
    0x3785,
    0x0000
};

static u32 l_msg_week6[] = {
    0x3779,
    0x3780,
    0x3785,
    0x0000
};

static u32* l_msg_week[] = {
    l_msg_week0, l_msg_week1, l_msg_week2, l_msg_week3,
    l_msg_week4, l_msg_week5, l_msg_week6,
};


static u32 l_msg_1st_talk_photo[] = {
    0x2A69,
    0x2A6A,
    0x2A6B,
    0x2A6C,
    0x0000
};


static u32 l_msg_talk_photo_0[] = {
    0x2A6E,
    0x2A6F,
    0x0000,
};

static u32 l_msg_talk_photo_1[] = {
    0x2A71,
    0x2A72,
    0x0000,
};

static u32 l_msg_talk_photo_2[] = {
    0x2A74,
    0x2A75,
    0x0000,
};

static u32 l_msg_talk_photo_3[] = {
    0x2A77,
    0x2A78,
    0x0000,
};

static u32 l_msg_talk_photo_4[] = {
    0x2A7A,
    0x2A7B,
    0x0000,
};

static u32 l_msg_talk_photo_5[] = {
    0x2A7D,
    0x2A7E,
    0x0000,
};

static u32 l_msg_talk_photo_6[] = {
    0x2A80,
    0x2A81,
    0x0000,
};

static u32* l_msg_talk_photo[] = {
    l_msg_talk_photo_0, l_msg_talk_photo_1, l_msg_talk_photo_2, l_msg_talk_photo_3,
    l_msg_talk_photo_4, l_msg_talk_photo_5, l_msg_talk_photo_6,
};

static u32 l_msg_buy_photo[] = {
    0x3786,
    0x0000
};

static u32 l_msg_get_photo[] = {
    0x3785,
    0x0000
};

static u32 l_msg_2F[] = {
    0x2A82,
    0x2A83,
    0x2A84
};

static u32 l_msg_down[] = {
    0x2A86,
    0x0000
};

static u32 l_msg_ub4[] = {
    0x2D62,
    0x0000,
};

static u32 l_msg_1st_order_xy[] = {
    0x2A5E,
    0x2A5F,
    0x2A60,
    0x0002
};

static u32 l_msg_2nd_order_xy[] = {
    0x2A61,
    0x2A62,
    0x2A60,
    0x0004
};

static u32 l_msg_3rd_order_xy[] = {
    0x2A64,
    0x2A60,
    0x0006
};

static u32 l_msg_color_xy[] = {
    0x2A58,
    0x2A59,
    0x2A5A,
    0x0007,
    0x2A85,
    0x0008,
    0x2A5B,
    0x0000
};

static u32 l_msg_xy_buy_photo[] = {
    0x3788,
    0x3789,
    0x0009,
    0x378C,
    0x000A,
    0x378D,
    0x000B,
    0x3786,
    0x0000
};

static dCcD_SrcCyl l_cyl_src2 = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_NoCoHitInfSet_e | cCcD_CoSPrm_VsGrpAll_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_Set_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
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
        /* Radius */ 40.0f,
        /* Height */ 160.0f,
    }},
};

static char* l_npc_staff_id = {
    "Po"
};

static const int l_bck_ix_tbl[] = {
    PO_BCK_WAIT01,
    PO_BCK_TALK01,
    PO_BCK_TALK02,
    PO_BCK_WALK01,
    PO_BCK_SPIT,
};

static const int l_btp_ix_tbl[] = {
    PO_BTP_MABA01,
    PO_BTP_MABA02
};

struct SaveDatStruct {
    /* 0x00 */ u16 field_0x00;
    /* 0x02 */ u16 field_0x02;
    /* 0x04 */ u16 field_0x04;
    /* 0x06 */ u16 field_0x06;
}; // Size: 0x08

static const SaveDatStruct l_save_dat = {
    0x1208,
    0x1701,
    0x1601,
    0xC407,
};


struct PsoData {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
};  // Size: 0x18

static PsoData l_pso_photo = {
    0.0f,
    100.0f,
    -30.0f,
    40.0f,
    90.0f,
    0x0000,
    0xFF,
    0x04
};

static cXyz l_counter_pos[] = {
    cXyz(-490.0f, 0.0f, -10.0f), 
    cXyz(-260.0f, 0.0f, -250.0f)
};

static cXyz l_gallery_pos(-260.0f, 500.0f, 400.0f);

/* 000000EC-000002D0       .text __ct__12daNpcPhoto_cFv */
daNpcPhoto_c::daNpcPhoto_c() {
    field_0x9C3 = 0;
    field_0x9C2 = false;
    field_0x9C0 = 0;
    field_0x9C1 = 0;
    field_0x984 = 0.0f;
    field_0x9A8 = 0;
    field_0x988 = 60.0f;
    field_0x958.x = 0.0f;
    field_0x958.y = 0.0f;
    field_0x958.z = 0.0f;
    field_0x9CD = false;
    field_0x9D6 = 0;
    field_0x994 = true;
    field_0x9AE = home.angle.y;
    field_0x9C8 = false;
    field_0x9C7 = true;
    field_0x98C = -1.0f;
}

/* 00000740-00000858       .text daNpc_Photo_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Photo_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpcPhoto_c* i_this = (daNpcPhoto_c*)model->getUserArea();
        s32 jntNo = joint->getJntNo();
        cMtx_copy(model->getAnmMtx(jntNo), *calc_mtx);
        
        if(jntNo == i_this->m_jnt.getHeadJntNum()) {
            mDoMtx_XrotM(*calc_mtx, i_this->m_jnt.getHead_y());
            mDoMtx_ZrotM(*calc_mtx, -i_this->m_jnt.getHead_x());
        }

        if(jntNo == i_this->m_jnt.getBackboneJntNum()) {
            mDoMtx_XrotM(*calc_mtx, i_this->m_jnt.getBackbone_y());
            mDoMtx_ZrotM(*calc_mtx, -i_this->m_jnt.getBackbone_x());
        }

        model->setAnmMtx(jntNo, *calc_mtx);
        cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 00000858-00000878       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpcPhoto_c*>(i_this)->createHeap();
}

/* 00000878-0000095C       .text phase_1__FP12daNpcPhoto_c */
static cPhs_State phase_1(daNpcPhoto_c* i_this) {
    fopAcM_SetupActor(i_this, daNpcPhoto_c);
    s16 arg0 = i_this->getPrmArg0();
    if(arg0 != 255){
        if(arg0 == 0){
            if(!dComIfGs_checkGetItem(dItem_COLLECT_MAP_20_e) && arg0 != dComIfGp_getStartStagePoint()){
                return cPhs_STOP_e;
            }
        } else{
            if(dComIfGs_checkGetItem(dItem_COLLECT_MAP_20_e) || arg0 != dComIfGp_getStartStagePoint()) {
                return cPhs_STOP_e;
            }
            i_this->field_0x9C1 = 4;
        }
    }
    i_this->field_0x9C2 = true;
    return cPhs_NEXT_e;
}

/* 0000095C-000009D4       .text phase_2__FP12daNpcPhoto_c */
static cPhs_State phase_2(daNpcPhoto_c* i_this) {
    cPhs_State phase_state = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[0]);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0)) {
            return i_this->createInit();
        } else {
            i_this->mpMorf = NULL;
            return cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 000009D4-00000A04       .text _create__12daNpcPhoto_cFv */
cPhs_State daNpcPhoto_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        NULL,
    };
    return dComLbG_PhaseHandler(&mPhs2, l_method, this);
}

/* 00000A04-00000CA0       .text createHeap__12daNpcPhoto_cFv */
BOOL daNpcPhoto_c::createHeap() {
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectIDRes(l_arcname_tbl[0], PO_BDL_PO);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[field_0x9C8]),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000,0x11020022
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x4A7, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(0x4AC, m_jnt.getBackboneJntNum() >= 0);

    if (!initTexPatternAnm(false, -1)) {
        return FALSE;
    } 

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            modelData->getJointNodePointer(i)->setCallBack(daNpc_Photo_nodeCallBack);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    return TRUE;
    

    return FALSE;
}

/* 00000CA0-00000CC0       .text daNpcPhoto_XyCheckCB__FPvi */
static s16 daNpcPhoto_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daNpcPhoto_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 00000CC0-00000CE0       .text daNpcPhoto_XyEventCB__FPvi */
static s16 daNpcPhoto_XyEventCB(void* i_this, int i_itemBtn) {
    return ((daNpcPhoto_c*)i_this)->XyEventCB(i_itemBtn);
}

/* 00000CE0-00001048       .text createInit__12daNpcPhoto_cFv */
cPhs_State daNpcPhoto_c::createInit() {
    int temp = 0xFF;

    u8 pathIndex = getPrmRailID();
    if(pathIndex != 0xFF) {
        mPathRun.setInf(pathIndex, fopAcM_GetRoomNo(this), true);
        if(mPathRun.mPath == NULL) {
            return cPhs_ERROR_e;
        }

        dPath_GetNextRoomPath(mPathRun.mPath, -1);
        
        if(dComIfGs_isEventBit(l_save_dat.field_0x02)) {
            cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
            old.pos = point;
            current.pos = old.pos;
            mPathRun.incIdxLoop();
            field_0x9A8 = 1;
            field_0x9C1 = 2;
        }
        temp = 0xFE;
    }
    gravity = -9.0f;

    mPhotoLinkBackEventIdx = dComIfGp_evmng_getEventIdx("PHOTO_LINK_BACK",0xff);
    mPhotoGetItemEventIdx = dComIfGp_evmng_getEventIdx("PHOTO_GET_ITEM",0xff);
    mPhotoGetItem2EventIdx = dComIfGp_evmng_getEventIdx("PHOTO_GET_ITEM2",0xff);
    mPhotoGetPhotoEventIdx = dComIfGp_evmng_getEventIdx("PHOTO_GET_PHOTO",0xff);
    mPhotoGalleryEventIdx = dComIfGp_evmng_getEventIdx("PHOTO_GALLERY",0xff);
    mPhotoCounterTalk0EventIdx = dComIfGp_evmng_getEventIdx("PHOTO_COUNTER_TALK0",0xff);
    mPhotoCounterTalk1EventIdx = dComIfGp_evmng_getEventIdx("PHOTO_COUNTER_TALK1",0xff);
    mPhotoDateUB4EventIdx = dComIfGp_evmng_getEventIdx("PHOTO_DATE_UB4",0xff);
    field_0x9A6 = mPhotoCounterTalk0EventIdx;

    mEventCut.setActorInfo2(l_npc_staff_id, this);
    
    field_0x9B6 = 0;
    field_0x9BC = false;
    field_0x9BD = false;

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 173;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 173;
    attention_info.flags = fopAc_Attn_UNK1000000_e | fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    eventInfo.setXyCheckCB(&daNpcPhoto_XyCheckCB);
    eventInfo.setXyEventCB(&daNpcPhoto_XyEventCB);

    if (field_0x9C1 == 4) {
        field_0x9D7 = false;
        field_0x9D8 = false;
    } else {
        field_0x9D7 = l_npc_dat.field_0x52;
        field_0x9D8 = l_npc_dat.field_0x53;
    }

    field_0x9B2 = l_npc_dat.field_0x28;
    mObjAcch.CrrPos(*dComIfG_Bgsp());

    if(mObjAcch.GetGroundH() != -G_CM3D_F_INF) {
        current.pos.y = home.pos.y = mObjAcch.GetGroundH();
    }

    setMtx();
    mpMorf->getModel()->calc();
    mStts.Init(temp, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos + field_0x958, field_0x988, 150.0f);
    field_0x6F8[0].Set(l_cyl_src2);
    field_0x6F8[0].SetStts(&mStts);
    field_0x6F8[1].Set(l_cyl_src2);
    field_0x6F8[1].SetStts(&mStts);
    return 4;
}

/* 00001048-000010A4       .text _delete__12daNpcPhoto_cFv */
bool daNpcPhoto_c::_delete() {
    dComIfG_resDelete(getPhaseP(), l_arcname_tbl[0]);
    if(heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return true;
}

/* 000010A4-0000125C       .text _draw__12daNpcPhoto_cFv */
bool daNpcPhoto_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData *model_data = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(model_data, mFrame);
    mpMorf->updateDL();
    mBtpAnm.remove(model_data);

    cXyz shadowPos(
        current.pos.x,
        current.pos.y + 150.0f,
        current.pos.z
    );

    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );

    if (field_0x9C1 == 4) {
        dSnap_Obj obj;

        cXyz temp(
            l_pso_photo.field_0x00,
            l_pso_photo.field_0x04,
            l_pso_photo.field_0x08
        );
        temp += current.pos;
        obj.SetInf(5, this, l_pso_photo.field_0x16, l_pso_photo.field_0x17, 0x7FFF);
        obj.SetGeo(temp, l_pso_photo.field_0x0C, l_pso_photo.field_0x10, l_pso_photo.field_0x14 + current.angle.y);
        dSnap_RegistSnapObj(obj);
    } else {
        dSnap_RegistFig(DSNAP_TYPE_NPC_PHOTO, this, 1.0f, 1.0f, 1.0f);
    }
    return true;
}

static daNpcPhoto_c::MoveFunc_t moveProc[] = {
    &daNpcPhoto_c::executeWait,
    &daNpcPhoto_c::executeTalk,
    &daNpcPhoto_c::executeWalk,
    &daNpcPhoto_c::executeTurn,
};

/* 0000125C-0000151C       .text _execute__12daNpcPhoto_cFv */
bool daNpcPhoto_c::_execute() {
    m_jnt.setParam(
        l_npc_dat.field_0x08, l_npc_dat.field_0x0A, l_npc_dat.field_0x10, 
        l_npc_dat.field_0x12, l_npc_dat.field_0x04, l_npc_dat.field_0x06, 
        l_npc_dat.field_0x0C, l_npc_dat.field_0x0E, l_npc_dat.field_0x14
    );

    chkAttention();
    mEyePos.set(
        current.pos.x,
        current.pos.y + l_npc_dat.field_0x30,
        current.pos.z
    );

    checkOrder();

    if (!dComIfGp_event_runCheck() || (eventInfo.checkCommandTalk() && field_0x9C7)) {
        (this->*moveProc[field_0x9C0])();
    } else {
        eventMove();
    }

    eventOrder();
    playTexPatternAnm();
    playAnm();

    if(field_0x9C8 == 3){
        cLib_chaseF(&speedF, field_0x984, 0.1f);
        float temp = speedF * l_npc_dat.field_0x38;

        if(temp < 0.5f) {
            temp = 0.5f;
        }
        mpMorf->setPlaySpeed(temp);
    } else {
        cLib_chaseF(&speedF, field_0x984, 0.5f);
    }

    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    setCollision(&mCyl, current.pos + field_0x958, field_0x988, 150.0f);

    if (field_0x9C1 == 2) {
        for(int i = 0; i < 2; i++) {
            setCollision(&field_0x6F8[i], 
                cXyz(
                    l_counter_pos[i].x,
                    l_counter_pos[i].y,
                    l_counter_pos[i].z
                ), 
                110.0f, 150.0f
            );
        }
    }
    
    cXyz temp(
        l_npc_dat.field_0x1C,
        l_npc_dat.field_0x20,
        l_npc_dat.field_0x24
    );

    mDoMtx_stack_c::YrotS(current.angle.y);
    mDoMtx_stack_c::multVec(&temp, &temp);
    temp += current.pos;
    attention_info.position = temp;
    eyePos = mEyePos;
    lookBack();
    setMtx();
    return false;
}


/* 0000151C-00001580       .text executeCommon__12daNpcPhoto_cFv */
bool daNpcPhoto_c::executeCommon() {
    if (field_0x9BD) {
        field_0x9BE = 1;
    } else {
        field_0x9BE = 0;
    }
    
    if (field_0x9BC == 1) {
        executeSetMode(1);
    }
    return field_0x9BC;
}

/* 00001580-000017D0       .text executeSetMode__12daNpcPhoto_cFUc */
void daNpcPhoto_c::executeSetMode(u8 param_1) {
    s16 angle;
    field_0x984 = 0.0f;

    switch (param_1) {
        case 0:
            setAnmTbl(l_npc_anm_wait);
            field_0x9A8 = l_npc_dat.field_0x4A + cM_rndF(l_npc_dat.field_0x4C - l_npc_dat.field_0x4A);
            break;
        case 2:
            setAnmTbl(l_npc_anm_walk);
            field_0x9A8 = l_npc_dat.field_0x4E + cM_rndF(l_npc_dat.field_0x50 - l_npc_dat.field_0x4E);
            break;
        case 3:
            cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
            dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
    
            if (angle == current.angle.y) {
                param_1 = 2;
                setAnmTbl(l_npc_anm_walk);
                field_0x9A8 = l_npc_dat.field_0x4E + cM_rndF(l_npc_dat.field_0x50 - l_npc_dat.field_0x4E);
            }
            break;
    }
    field_0x9C0 = param_1;
}

/* 000017D0-00001A80       .text executeWait__12daNpcPhoto_cFv */
void daNpcPhoto_c::executeWait() {
    if(!executeCommon()) {
        field_0x988 = 60.0f;
        field_0x958.x = 0.0f;
        field_0x958.y = 0.0f;
        field_0x958.z = 0.0f;
        field_0x9CD = false;
        
        if(!dComIfGs_isEventBit(l_save_dat.field_0x02)){
            field_0x988 = 150.0f;
            f32 zPos = l_npc_dat.field_0x34;
            field_0x958.x = 0.0f;
            field_0x958.y = 0.0f;
            field_0x958.z = zPos;

            if(mCyl.ChkCoHit()) {
                daNpcPhoto_c* pActor = (daNpcPhoto_c*)mCyl.GetCoHitAc();
                if(pActor && fopAcM_GetProfName(pActor) == PROC_PLAYER) {
                    field_0x9BE = 2;
                }

            }
        } else if(field_0x9C1 == 4 && ((field_0x9C6 & 0x10) == 0)){
            daPy_py_c* link = (daPy_py_c*)dComIfGp_getLinkPlayer();

            if (link->current.pos.y < 10.0f && link->current.pos.x > -300.0f && link->current.pos.z > -500.0f) {
                field_0x9BE = 10;
            }
        } else {
            if(
                dComIfGp_getStartStagePoint() == 0 && 
                (!dComIfGs_isEventBit(l_save_dat.field_0x04) && field_0x9BE != 7) && 
                dComIfGp_getLinkPlayer()->current.pos.y > 400.0f && 
                dComIfGp_getLinkPlayer()->current.pos.x > -600.0f){
                field_0x9BE = 7;
            }

            if(field_0x9C1 == 2){
                eventInfo.setEventId(-1);
                field_0x9C7 = true;

                for (int i = 0; i < 2; i++) {
                    if (field_0x6F8[i].ChkCoHit()) {
                        daNpcPhoto_c* pActor = (daNpcPhoto_c*)field_0x6F8[i].GetCoHitAc();
                        if(pActor != NULL && fopAcM_GetProfName(pActor) == PROC_PLAYER) {
                            field_0x9CD = true;
                            break;
                        }
                    } 
                }
            }

            if(field_0x9C1 == 1 && !field_0x9BD && dComIfGp_getLinkPlayer()->current.pos.y < current.pos.y + -50.0f) {
                executeSetMode(3);
                field_0x9C1 = 3;
            }

            if(field_0x9C1 == 3 && !field_0x9BD) {
                if(field_0x9A8 == 0) {
                    executeSetMode(3);
                } else {
                    field_0x9A8--;
                }
            }
        }
    } 
}

/* 00001A80-00001BB4       .text executeTalk__12daNpcPhoto_cFv */
void daNpcPhoto_c::executeTalk() {
    executeCommon();
    if(!dComIfGp_event_chkTalkXY() || dComIfGp_evmng_ChkPresentEnd()) {
        if(talk2(1) == fopMsgStts_BOX_CLOSED_e){
            field_0x9BC = false;
            executeSetMode(0);
            u8 temp = field_0x9C6;
            if((temp & 1) != 0){
                field_0x9C6 = temp & 254;
                mItemNo = 31;
                field_0x9BE = 4;
                
            } else {
                if((temp & 2) != 0){
                    field_0x9C6 = temp & ~0x02;
                    mItemNo = 38;
                    field_0x9BE = 5;
                    
                } else {
                    if((temp & 4) != 0){
                        field_0x9C6 = temp & ~0x04;
                        field_0x9BE = 3;
                        setAnmTbl(l_npc_anm_spit);
                        field_0x9C9 |= 4;
                    } else {
                        field_0x9C6 = temp | 64;
                    }
                }
            }
        } else {
            setAnmFromMsgTag();
        }
    }
}

/* 00001BB4-00001D98       .text executeWalk__12daNpcPhoto_cFv */
void daNpcPhoto_c::executeWalk() {
    if(!executeCommon()) {
        bool temp = false;
        if(mPathRun.chkPointPass(current.pos, mPathRun.mbGoingForwards) && !mPathRun.nextIdxAuto()) {
            temp = true;
        }

        if (field_0x9BD != 0) {
            executeSetMode(0);
        } else if (!temp) {
            cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
            s16 angle;
            dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
            field_0x9BA = angle;
            field_0x994 = false;
            field_0x9B6 = l_npc_dat.field_0x18;
            field_0x9D6 = 2;
            m_jnt.setTrn(); 
            field_0x984 = l_npc_dat.field_0x3C;

            u8 pointIndex = mPathRun.mCurrPointIndex;

            if (mPathRun.mbGoingForwards) {
                pointIndex--;
            } else {
                pointIndex++;
            }

            cXyz point2 = mPathRun.getPoint(pointIndex);
            if (point2.y - point.y > 400.0f) {
                field_0x984 = l_npc_dat.field_0x3C * l_npc_dat.field_0x40;
            }
    
        } else{
            executeSetMode(0);
            field_0x9C1 = 2;
            field_0x9AE = home.angle.y;
        }
    }
}

/* 00001D98-00001E5C       .text executeTurn__12daNpcPhoto_cFv */
void daNpcPhoto_c::executeTurn() {
    if (!executeCommon()) {
        s16 angle;
        cXyz point = mPathRun.getPoint(mPathRun.mCurrPointIndex);
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle); // maybe not oldpos
        field_0x9BA = angle;
        field_0x994 = false;
        field_0x9D6 = 2;
        if (!m_jnt.trnChk()) {
            executeSetMode(2);
        }
    }
}

/* 00001E5C-00001FDC       .text checkOrder__12daNpcPhoto_cFv */
void daNpcPhoto_c::checkOrder() {
    if(eventInfo.mCommand == dEvtCmd_INDEMO_e){
        if(dComIfGp_evmng_startCheck(mPhotoLinkBackEventIdx) && field_0x9BE == 3){
            field_0x9BE = 0;
        } else if(dComIfGp_evmng_startCheck(mPhotoGetItemEventIdx) && field_0x9BE == 4){
            field_0x9BE = 0;
        } else if(dComIfGp_evmng_startCheck(mPhotoGetItem2EventIdx) && field_0x9BE == 5){
            field_0x9BE = 0;
        } else if(dComIfGp_evmng_startCheck(mPhotoGetPhotoEventIdx) && field_0x9BE == 6){
            field_0x9BE = 0;
        } else if(dComIfGp_evmng_startCheck(mPhotoGalleryEventIdx) && field_0x9BE == 7){
            field_0x9BE = 0;
        } else if(dComIfGp_evmng_startCheck(mPhotoDateUB4EventIdx) && field_0x9BE == 10){
            field_0x9BE = 0;
        }
    } else if(eventInfo.mCommand == dEvtCmd_INTALK_e && (field_0x9BE == 2 || field_0x9BE == 1)){
        field_0x9BC = true;
        executeSetMode(1);
    }
}

/* 00001FDC-000021B8       .text eventOrder__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventOrder() {
    if (field_0x9C6 & 0x40) {
        field_0x9C6 &= ~0x40;
        dComIfGp_event_reset();
        initTexPatternAnm(true, -1);
        field_0x9C9 &= 0x7F;
        field_0x9C7 = true;
        field_0x9BC = false;
        executeSetMode(0);
    }
    u8 temp = field_0x9BE;
    if(temp == 2 || temp == 1){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (field_0x9BE == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if(temp == 3){
        fopAcM_orderChangeEventId(dComIfGp_getLinkPlayer(), this, mPhotoLinkBackEventIdx, 0, 0xFFFF);
    } else if(temp == 4){
        fopAcM_orderChangeEventId(dComIfGp_getLinkPlayer(), this, mPhotoGetItemEventIdx, 0, 0xFFFF);
    } else if(temp == 5){
        fopAcM_orderChangeEventId(dComIfGp_getLinkPlayer(), this, mPhotoGetItem2EventIdx, 0, 0xFFFF);
    } else if(temp == 6){
        fopAcM_orderChangeEventId(dComIfGp_getLinkPlayer(), this, mPhotoGetPhotoEventIdx, 0, 0xFFFF);
    } else if(temp == 7){
        fopAcM_orderOtherEventId(this, mPhotoGalleryEventIdx);
    } else if(temp == 10){
        fopAcM_orderOtherEventId(this, mPhotoDateUB4EventIdx);
    }
}

/* 000021B8-00002368       .text eventMove__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventMove() {
    if(dComIfGp_evmng_endCheck(mPhotoLinkBackEventIdx)){
        field_0x9C6 |= 0x40;
    } else if(dComIfGp_evmng_endCheck(field_0x9A6)){
        field_0x9C6 |= 0x40;
        eventInfo.mEventId = -1;
        field_0x9C7 = true;
        field_0x9BE = 0;
        field_0x9BC = false;
        executeSetMode(0);
    } else if(dComIfGp_evmng_endCheck(mPhotoGetItemEventIdx)){
        field_0x9C6 |= 0x40;
    } else if(dComIfGp_evmng_endCheck(mPhotoGetItem2EventIdx)){
        field_0x9C6 |= 0x40;
    } else if(dComIfGp_evmng_endCheck(mPhotoGetPhotoEventIdx)){
        field_0x9C6 |= 0x40;
    } else if(dComIfGp_evmng_endCheck(mPhotoGalleryEventIdx)){
        field_0x9C6 |= 0x40;
    } else if(dComIfGp_evmng_endCheck(mPhotoDateUB4EventIdx)){
        field_0x9C6 |= 0x40;
        field_0x9C6 |= 0x10;
        field_0x9D7 = true;
        field_0x9D8 = true;
    } else{
        bool temp = mEventCut.getAttnFlag();

        if(mEventCut.cutProc()) {
            if(!mEventCut.getAttnFlag()) {
                mEventCut.setAttnFlag(temp);
            }
        } else {
          privateCut();
          setAnmFromMsgTag();
        }
    }
}

/* 00002368-00002560       .text privateCut__12daNpcPhoto_cFv */
void daNpcPhoto_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET",
        "SE_SET",
        "POS_SET",
        "GET_ITEM",
        "SET_ANGLE",
        "SET_EYE",
        "TURN_TO_PLAYER",
        "CLR_HANME",
        "GET_PHOTO",
        "MES_SET_UB",
        "LOOK_UB"
    };
    enum {
        ACT_MES_SET,
        ACT_SE_SET,
        ACT_POS_SET,
        ACT_GET_ITEM,
        ACT_SET_ANGLE,
        ACT_SET_EYE,
        ACT_TURN_TO_PLAYER,
        ACT_CLR_HANME,
        ACT_GET_PHOTO,
        ACT_MES_SET_UB,
        ACT_LOOK_UB,
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId(l_npc_staff_id);
    if (staffIdx == -1) {
        return;
    }

    mActIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
    if (mActIdx == -1) {
        dComIfGp_evmng_cutEnd(staffIdx);
        return;
    }

    if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
        switch (mActIdx) {
        case ACT_MES_SET:
            eventMesSetInit(staffIdx);
            break;
        case ACT_SE_SET:
            eventSeSetInit(staffIdx);
            break;
        case ACT_POS_SET:
            eventPosSetInit();
            break;
        case ACT_GET_ITEM:
            eventGetItemInit();
            break;
        case ACT_SET_ANGLE:
            eventSetAngleInit();
            break;
        case ACT_SET_EYE:
            eventSetEyeInit();
            break;
        case ACT_TURN_TO_PLAYER:
            eventTurnToPlayerInit();
            break;
        case ACT_CLR_HANME:
            eventClrHanmeInit();
            break;
        case ACT_GET_PHOTO:
            eventGetPhotoInit();
            break;
        case ACT_MES_SET_UB:
            eventMesSetUbInit(staffIdx);
            break;
        }
    }

    bool evtRes;
    switch (mActIdx) {
        case ACT_MES_SET:
            evtRes = eventMesSet();
            break;
        case ACT_GET_ITEM:
            evtRes = eventGetItem();
            break;
        case ACT_SET_EYE:
            evtRes = eventSetEye();
            break;
        case ACT_TURN_TO_PLAYER:
            evtRes = eventTurnToPlayer();
            break;
        case ACT_GET_PHOTO:
            evtRes = eventGetPhoto();
            break;
        case ACT_MES_SET_UB:
            evtRes = eventMesSetUb();
            break;
        case ACT_LOOK_UB:
            evtRes = eventLookUb();
            break;
        default:
            evtRes = true;
            break;
    }
    if (evtRes) {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
}

/* 00002560-00002758       .text eventMesSetInit__12daNpcPhoto_cFi */
void daNpcPhoto_c::eventMesSetInit(int i_staffId) {
    int* pData = dComIfGp_evmng_getMyIntegerP(i_staffId, "MsgNo");

    if(pData) {
        field_0x980 = NULL;
        field_0x9D0 = NULL;
        u32 msgNo = *pData;

        switch (msgNo) {
            case 0:
                if (!dComIfGs_isEventBit(l_save_dat.field_0x04)) {
                    field_0x980 = l_msg_1st_talk_photo;
                    field_0x9D0 = NULL;
                    dComIfGs_onEventBit(l_save_dat.field_0x04);

                } else {
                    int temp = 0;
                    daTagPhoto_c* ac = (daTagPhoto_c*)dComIfGp_event_getPt2();
                    if(ac != NULL){
                        temp = ac->getTagNo();
                    }
                    field_0x980 = l_msg_talk_photo[(temp & 0xFF)];
                    field_0x9D0 = NULL;
                }
                setMessage(*field_0x980);
                break;
            case 1:
                setMessage(getMsg());
                break;
            case 99:
                mDoAud_seStart(JA_SE_UTSUSHIE_TO_DX);
                field_0x980 ++;

                if (field_0x9D0 != NULL) {
                    field_0x9D0++;
                }
                setMessage(*field_0x980);
                break;
            default:
                setMessage(msgNo);
                break;
        }
    } else {
        field_0x980 ++;

        if (field_0x9D0 != 0) {
            field_0x9D0++;
        }
        setMessage(*field_0x980);
    }
}

/* 00002758-0000278C       .text eventMesSet__12daNpcPhoto_cFv */
bool daNpcPhoto_c::eventMesSet() {
    return talk2(0) == fopMsgStts_BOX_CLOSED_e;
}

/* 0000278C-0000289C       .text eventSeSetInit__12daNpcPhoto_cFi */
void daNpcPhoto_c::eventSeSetInit(int i_staffId) {
    int* seNo = dComIfGp_evmng_getMyIntegerP(i_staffId, "SeNo");

    if(seNo != NULL) {
        switch (*seNo) {
        case 0:
            mDoAud_seStart(JA_SE_UTSUSHIE_TO_DX);
            break;
        default:
            mDoAud_seStart(JA_SE_UTSUSHIE_TO_DX);
            break;
        }
    } else {
        mDoAud_seStart(JA_SE_UTSUSHIE_TO_DX);
    }
}


/* 0000289C-00002C60       .text eventPosSetInit__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventPosSetInit() {
    s16 angle;
    daTagPhoto_c* ac = (daTagPhoto_c*)dComIfGp_event_getPt2();

    if(ac){
        cXyz temp = ac->current.pos;
        dPath* path = dPath_GetNextRoomPath(mPathRun.mPath, fopAcM_GetRoomNo(this));
        
        if(path != NULL){
            dPnt* pnt = dPath_GetPnt(path, ac->getTagNo());
            if(pnt != NULL){
                old.pos = pnt->m_position;
                current.pos = old.pos;
                dBgS_GndChk gndChk;
                
                Vec temp;
                temp.y = current.pos.y;
                temp.z = current.pos.z;
                temp.y += 50.0f;
                temp.x = current.pos.x;

                gndChk.SetPos(&temp);

                f32 floor_y = dComIfG_Bgsp()->GroundCross(&gndChk);
                if(floor_y != -G_CM3D_F_INF){
                    old.pos.y = floor_y;
                    current.pos.y = floor_y;
                }
            }         
        }
        dNpc_calc_DisXZ_AngY(current.pos, temp, NULL, &angle);
        shape_angle.y = current.angle.y = field_0x9AE = angle;
    } else {
        daPy_lk_c* link = daPy_getPlayerLinkActorClass();
        old.pos = l_gallery_pos;
        current.pos = old.pos;
        dNpc_calc_DisXZ_AngY(current.pos, link->current.pos, NULL, &angle);
        shape_angle.y = current.angle.y = field_0x9AE = angle;
    }
    dComIfGp_event_setTalkPartner(this);
    mPathRun.mCurrPointIndex = mPathRun.mPath->m_num - 2;
    mPathRun.mbGoingForwards = false;

    executeSetMode(0);
    field_0x9C1 = 1;
    int temp = cM_rndF(3.0f);
    if (temp == 3) {
        temp = 0;
    }
    mMsgNno = l_msg_2F[temp];
}

/* 00002FE0-0000303C       .text eventGetItemInit__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventGetItemInit() {
    fpc_ProcID itemID = fopAcM_createItemForPresentDemo(&current.pos, mItemNo, 0, -1, fopAcM_GetRoomNo(this));
    if (itemID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemID);
    }
}

/* 0000303C-00003044       .text eventGetItem__12daNpcPhoto_cFv */
bool daNpcPhoto_c::eventGetItem() {
    return true;
}

/* 00003044-000030A8       .text eventSetAngleInit__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventSetAngleInit() {
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    cXyz pos = current.pos - link->current.pos;
    link->changeDemoMoveAngle(cM_atan2s(pos.x, pos.z));
}

/* 000030A8-000030F0       .text eventSetEyeInit__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventSetEyeInit() {
    field_0x9B0 = 0;
    dComIfGp_event_setTalkPartner(this);
}

/* 000030F0-000031F0       .text eventSetEye__12daNpcPhoto_cFv */
bool daNpcPhoto_c::eventSetEye() {
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    s16 temp = link->shape_angle.y + cM_ssin(field_0x9B0) * 12288.0f;
    field_0x9B0 += 0x400;
    mEyePos.x = 0.0f;
    mEyePos.y = 0.0f;
    mEyePos.z = 100.0f;
    mDoMtx_stack_c::YrotS(temp);
    mDoMtx_stack_c::XrotM(-0x1000);
    mDoMtx_stack_c::multVec(&mEyePos, &mEyePos);
    mEyePos += link->eyePos;
    return TRUE;
}

/* 000031F0-00003260       .text eventTurnToPlayerInit__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventTurnToPlayerInit() {
    fopAc_ac_c* link = dComIfGp_getLinkPlayer();
    dNpc_calc_DisXZ_AngY(current.pos, link->current.pos, 0, &field_0x9AE);
}

/* 00003260-00003278       .text eventTurnToPlayer__12daNpcPhoto_cFv */
bool daNpcPhoto_c::eventTurnToPlayer() {
    return current.angle.y == field_0x9AE ? TRUE : FALSE;
}

/* 00003278-000032B8       .text eventClrHanmeInit__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventClrHanmeInit() {
    initTexPatternAnm(true, -1);
    field_0x9C9 &= 0x7F;
}

/* 000032B8-00003300       .text eventGetPhotoInit__12daNpcPhoto_cFv */
void daNpcPhoto_c::eventGetPhotoInit() {
    dComIfGp_setPictureStatusGetOn(dKy_get_dayofweek());
    field_0x9B0 = 10;
}

/* 00003300-0000331C       .text eventGetPhoto__12daNpcPhoto_cFv */
bool daNpcPhoto_c::eventGetPhoto() {
    field_0x9B0--;
    return field_0x9B0 == 0;
}

/* 0000331C-0000333C       .text eventMesSetUbInit__12daNpcPhoto_cFi */
void daNpcPhoto_c::eventMesSetUbInit(int i_staffId) {
    eventMesSetInit(i_staffId);
}

/* 0000333C-00003370       .text eventMesSetUb__12daNpcPhoto_cFv */
bool daNpcPhoto_c::eventMesSetUb() {
    eventLookUb();
    return eventMesSet();
}

/* 00003370-000033E4       .text eventLookUb__12daNpcPhoto_cFv */
bool daNpcPhoto_c::eventLookUb() {  
    fopAc_ac_c* pActor = fopAcM_searchFromName("Ub4", 0, 0);
    if (pActor != NULL) {
      mLookAtPos = pActor->eyePos;
      field_0x9D6 = 1;
      field_0x994 = false;
    }
    return true;
}

/* 000033E4-0000357C       .text talk2__12daNpcPhoto_cFi */
u16 daNpcPhoto_c::talk2(int i_param) {
    u16 status = 0xFF;
    if(mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {

        if(i_param == 1) {
            mCurrMsgNo = getMsg();
        }

        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
        field_0x9D5 = 1;
        setMsgCamera();
    } else if(mpCurrMsg){
        status = mpCurrMsg->mStatus;
        switch(status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                
                if(mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
                break;

            case fopMsgStts_MSG_TYPING_e:
                if (field_0x9D5 != 0) {
                    field_0x9D5 = 0;
                    setMsgCamera();
                }
                break;
                
            case fopMsgStts_BOX_CLOSED_e:
                if (field_0x9D4) {
                    dCamera_c* pCam = dCam_getBody();
                    pCam->Start();
                }
                
                if ((field_0x9C6 & 0x20) != 0) {
                    field_0x9C6 &= ~0x20;
                    field_0x9C6 |= 0x40;
                }
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                 mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
                break;
        }
        if(status != fopMsgStts_MSG_TYPING_e) {
            field_0x9D5 = 1;
        }
        anmAtr(status);
    } else {
        mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
    }
    return status;
}

static cXyz l_msg_camera[][2] = {
    {cXyz(-1336.0f, -497.0f, 928.0f), cXyz(185.0f, -26.0f, 0.0f)},
    {cXyz(-1213.0f, -902.0f, -244.0f), cXyz(284.0f, 36.0f, 280.0f)},
    {cXyz(-29.0f, 252.0f, -1634.0f), cXyz(5.0f, -91.0f, 178.0f)},
};

/* 0000357C-000036DC       .text setMsgCamera__12daNpcPhoto_cFv */
void daNpcPhoto_c::setMsgCamera() {
    if (field_0x9D0 != NULL) {
        dCamera_c* pCam = dCam_getBody();
        if (*(s8*)field_0x9D0 >= 0) {
            pCam->Stop();
            cXyz temp = l_msg_camera[*(s8*)field_0x9D0][0];
            cXyz temp2 = l_msg_camera[*(s8*)field_0x9D0][1];
            mDoMtx_stack_c::YrotS(current.angle.y);
            mDoMtx_stack_c::multVec(&temp, &temp);
            mDoMtx_stack_c::multVec(&temp2, &temp2);
            temp += attention_info.position;
            temp2 += attention_info.position;
            pCam->Set(temp, temp2, 60.0f, 0);
            field_0x9D4 = true;
        } else {
            pCam->Start();
            field_0x9D4 = false;
        }
    }
}

/* 000036DC-000038E8       .text next_msgStatus__12daNpcPhoto_cFPUl */
u16 daNpcPhoto_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;

    switch(*pMsgNo) {
        case 0x378A:
        case 0x378B:
            field_0x9C6 |= 0x20;
            status = fopMsgStts_MSG_ENDS_e;
            break;

        case 0x2A3A:
        case 0x2A3D:
        
            if(mpCurrMsg->mSelectNum != 0) {
                *pMsgNo = 0x2A3B;
                field_0x980 = NULL;
                field_0x9D0 = NULL;
                break;
            }

        default:
            if(field_0x980 != NULL) {
                field_0x980++;
                if (field_0x9D0 != NULL) {
                    field_0x9D0++;
                }
                switch(*field_0x980) {
                
                case 7:
                case 8:
                case 11:
                    status = fopMsgStts_MSG_ENDS_e;
                    break;
                case 9:
                    if(mpCurrMsg->mSelectNum == 0) {
                        if(dComIfGs_getRupee() < dComIfGp_getMessageRupee()){
                            *pMsgNo = 0x378B;
                        } else {
                            field_0x980++;
                            if (field_0x9D0 != NULL) {
                                field_0x9D0++;
                            }
                            *pMsgNo = *field_0x980;
                            dComIfGp_setItemRupeeCount(-dComIfGp_getMessageRupee());
                            dComIfGs_onTmpBit(0x301);
                        }
                    } else {
                        field_0x980 = NULL;
                        *pMsgNo = 0x378A;
                    }
                    break;
                case 10:
                    status = fopMsgStts_MSG_ENDS_e;
                    break;
                case 6:
                    field_0x9C6 |= 1;
                    field_0x9CC = true;

                case 2:
                case 4:
                    dPb_erasePicture();
                case 1:
                case 3:
                case 5: {
                    u8 reg = dComIfGs_getEventReg(l_save_dat.field_0x06);
                    reg++;
                    dComIfGs_setEventReg(l_save_dat.field_0x06, reg);
                }
                case 0:
                    field_0x980 = NULL;
                    field_0x9D0 = NULL;
                    status = fopMsgStts_MSG_ENDS_e;
                    break;
                default:
                    *pMsgNo = *field_0x980;
                    break;
                }
            } else {
                status = fopMsgStts_MSG_ENDS_e;  
            }
    }
    return status;
}

/* 000038E8-00003E68       .text getMsg__12daNpcPhoto_cFv */
u32 daNpcPhoto_c::getMsg() {
    u32 msgNo = 0;
    u8 eventReg = dComIfGs_getEventReg(l_save_dat.field_0x06);
    field_0x980 = 0;
    field_0x9D0 = 0;
    
    if(g_dComIfG_gameInfo.play.getEvent().chkPhoto()) {
        if (eventReg < 1) {
            msgNo = 0x2A5C;
        } else if (eventReg < 3) {
            if (eventReg == 2) {
                msgNo = 0x2A57;
            } else {
                if (isPhotoOk()) {
                    field_0x980 = l_msg_1st_order_xy;
                    field_0x9D0 = 0;
                } else {
                    msgNo = 0x2A5D;
                }
            }
        } else if (eventReg < 5) {
            if (eventReg == 4) {
              msgNo = 0x2A57;
            } else {
                if (isPhotoOk()) {
                    field_0x980 = l_msg_2nd_order_xy;
                    field_0x9D0 = 0;
                } else {
                    msgNo = 0x2A5D;
                }
            }
        } else if (eventReg < 6) {
            if (isPhotoOk()) {
                field_0x980 = l_msg_3rd_order_xy;
                field_0x9D0 = 0;
            } else {
                msgNo = 0x2A5D;
            }
        } else {
            msgNo = 0x2A63;
        }
    } else if(dComIfGp_event_chkTalkXY()) {
        u32 itemNo = dComIfGp_event_getPreItemNo();

        if(itemNo == CAMERA2 && dComIfGs_isTmpBit(0x302)) {
            if (dComIfGs_getPictureNum() < 3) {
                field_0x980 = l_msg_xy_buy_photo;
                mItemNo = SALVAGE_ITEM1;
            } else {
                msgNo = 0x3787;
            }
        } else if(itemNo == dItem_FIREFLY_BOTTLE_e) {
            if(eventReg >= 6 && !dComIfGs_checkGetItem(CAMERA2)) {
                field_0x980 = l_msg_color_xy;
                field_0x9D0 = 0;
                dComIfGs_setEquipBottleItemEmpty();
                mItemNo = CAMERA2;
            } else{
                msgNo = 0x2A57;
            }
        } else {
            msgNo = 0x2A56;
        }
    } else if (field_0x9C1 == 3) {
        field_0x980 = l_msg_down;
        field_0x9D0 = 0;
    } else if (field_0x9C1 == 4) {
        field_0x980 = l_msg_ub4;
        field_0x9D0 = 0;
    } else if (dComIfGs_isEventBit(l_save_dat.field_0x04)) {
        if(field_0x9C1 == 1) {
            msgNo = mMsgNno;
        } else {
            if(dComIfGs_checkGetItem(CAMERA2)) {
                if(dComIfGs_isTmpBit(0x301)) {
                    field_0x980 = (u32*)l_msg_buy_photo;
                    field_0x9D0 = 0;
                } else {
                    if(dComIfGs_isTmpBit(0x302)) {
                        field_0x980 = l_msg_get_photo;
                        field_0x9D0 = 0;
                        
                    } else {
                        if(isPhotoDxOk()) {
                            dComIfGs_onTmpBit(0x302);
                            if(dComIfGs_isEventBit(0x3808) == 0) {
                                dComIfGs_onEventBit(0x3808);
                                field_0x980 = (u32*)l_msg_week_1st;
                                field_0x9D0 = 0;
                            } else {
                                field_0x980 = l_msg_week[dKy_get_dayofweek()];
                                field_0x9D0 = 0;
                            }
                        } else {
                            field_0x980 = l_msg_color;
                            field_0x9D0 = (u8*)l_msg_color_c;
                        }
                    }

                }
            } else {
                eventReg = dComIfGs_getEventReg(l_save_dat.field_0x06);
                if (eventReg < 1) {
                    field_0x980 = l_msg_1st_order;
                    field_0x9D0 = (u8*)l_msg_1st_order_c;
                } else if (eventReg < 2) {
                    field_0x980 = l_msg_1st_order_not_end;
                    field_0x9D0 = (u8*)l_msg_1st_order_not_end_c;
                } else if (eventReg < 3) {
                    field_0x980 = l_msg_2nd_order;
                    field_0x9D0 = (u8*)l_msg_2nd_order_c;
                } else if (eventReg < 4) {
                    field_0x980 = l_msg_2nd_order_not_end;
                    field_0x9D0 = (u8*)l_msg_2nd_order_not_end_c;
                } else if (eventReg < 5) {
                    field_0x980 = l_msg_3rd_order;
                    field_0x9D0 = (u8*)l_msg_3rd_order_c;
                } else if (eventReg < 6) {
                    field_0x980 = l_msg_3rd_order_not_end;
                    field_0x9D0 = (u8*)l_msg_3rd_order_not_end_c;
                } else if (field_0x9CC == 1) {
                    field_0x980 = l_msg_3rd_order_end;
                    field_0x9D0 = 0;
                } else {
                    field_0x980 = l_msg_not_color;
                    field_0x9D0 = (u8*)l_msg_not_color_c;
                }
            }
        } 
    } else if(dComIfGs_checkGetItem(CAMERA) || dComIfGs_checkGetItem(CAMERA2)) {
        if(!dComIfGs_isEventBit(l_save_dat.field_0x02)) {
            field_0x980 = l_msg_1st_photo;
            field_0x9D0 = 0;
            dComIfGs_onEventBit(l_save_dat.field_0x02);
            initTexPatternAnm(true, 1);
        } else {
            field_0x980 = l_msg_2nd_photo;
            field_0x9D0 = 0;
        }
    } else {
        if(dComIfGs_isEventBit(l_save_dat.field_0x00) == 0) {
            field_0x980 = l_msg_1st_talk;
            field_0x9D0 = 0;
            dComIfGs_onEventBit(l_save_dat.field_0x00);
            field_0x9C6 |= 4;
        } else {
            field_0x980 = l_msg_2nd_talk;
            field_0x9D0 = 0;
            field_0x9C6 |= 4;
        }
    }
    if (field_0x980 != NULL) {
        msgNo = *field_0x980;
    }
    return msgNo;
}

/* 00003E68-00003E78       .text setMessage__12daNpcPhoto_cFUl */
void daNpcPhoto_c::setMessage(u32 msg) {
    mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
    mCurrMsgNo = msg;
}

/* 00003E78-00003FD8       .text setAnmFromMsgTag__12daNpcPhoto_cFv */
void daNpcPhoto_c::setAnmFromMsgTag() {
    switch(dComIfGp_getMesgAnimeAttrInfo()){
        case 0:
            setAnmTbl(l_npc_anm_wait);
            field_0x9C9 &= 0x7f;
            break;
        case 1:
            setAnmTbl(l_npc_anm_talk);
            field_0x9C9 &= 0x7f;

            break;
        case 2:
            setAnmTbl(l_npc_anm_talk2);
            field_0x9C9 &= 0x7f;
            break;
        case 3:
            setAnmTbl(l_npc_anm_wait);
            initTexPatternAnm(true, 0);
            field_0x9C9 &= 0x7f;
            break;
        case 4:
            setAnmTbl(l_npc_anm_talk2);
            field_0x9C9 &= 0x7f;
            break;
        case 5:
            setAnmTbl(l_npc_anm_wait);
            initTexPatternAnm(true, 1);
            field_0x9C9 |= 0x80;
            mFrame = 1;
            break;
        case 6:
            setAnmTbl(l_npc_anm_talk);
            initTexPatternAnm(true, 0);
            field_0x9C9 &= 0x7f;
            break;
        case 9:
            setAnmTbl(l_npc_anm_spit);
            field_0x9C9 &= 0x7f;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xFF);
}

/* 00003FD8-00004004       .text getPrmRailID__12daNpcPhoto_cFv */
u8 daNpcPhoto_c::getPrmRailID() {
    return daObj::PrmAbstract(this, PRM_RAIL_ID_W, PRM_RAIL_ID_S);
}

/* 00004004-00004030       .text getPrmArg0__12daNpcPhoto_cFv */
u8 daNpcPhoto_c::getPrmArg0() {
    return daObj::PrmAbstract(this, PRM_ARG0_W, PRM_ARG0_S);
}

/* 00004030-000040B8       .text setMtx__12daNpcPhoto_cFv */
void daNpcPhoto_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000040B8-0000432C       .text chkAttention__12daNpcPhoto_cFv */
void daNpcPhoto_c::chkAttention() {
    if(mEventCut.getAttnFlag()) {
        mLookAtPos = mEventCut.getAttnPos();
        field_0x9D6 = 1;
        if (field_0x9D7) {
            field_0x994 = false;
                m_jnt.setTrn();
        } else {
            field_0x994 = true;
        }
        if (!field_0x9BD) {
          field_0x9BD = true;
        }
        
    } else {
        fopAc_ac_c* link = dComIfGp_getLinkPlayer();
        f32 temp = l_npc_dat.field_0x2C;
        s16 angle;
        f32 temp3;
        int temp2 = field_0x9B2;
        dNpc_calc_DisXZ_AngY(current.pos, link->current.pos, &temp3, &angle);
        if (field_0x9BD != NULL) {
            temp += 40.0f;
            temp2 += 1820;
        }
        
        angle -= shape_angle.y;
       
        if((temp > temp3  && temp2 > abs(angle)) || field_0x9CD != NULL) {
            mLookAtPos = dNpc_playerEyePos(l_npc_dat.field_0x00);
            field_0x9D6 = 1;
            if (field_0x9D7) {
                field_0x994 = false;
            } else {
                field_0x994 = true;
            }
            if (!field_0x9D8) {
                field_0x9BA = field_0x9AE;
                field_0x994 = false;
                field_0x9D6 = 2;
                   m_jnt.setTrn();
            }
            if (!field_0x9BD) {
                field_0x9BD = true;
            }
        } else {
            if (field_0x9BD == true) {
                field_0x9BD = false;
                field_0x9AC = 30;
            }
            field_0x9D6 = 0;
            if ((field_0x9C0 == 0) && (field_0x9C1 != 3)) {
                if (field_0x9AC != 0) {
                    field_0x9AC--;
                } else {
                    field_0x9BA = field_0x9AE;
                    field_0x994 = false;
                    field_0x9D6 = 2;
                    m_jnt.setTrn();
                }
            }
        }  
    }
    field_0x9B6 = l_npc_dat.field_0x16;
}

/* 0000432C-00004478       .text lookBack__12daNpcPhoto_cFv */
void daNpcPhoto_c::lookBack() {
    short target = field_0x9B6;
    short desiredYRot = current.angle.y;
    cXyz* dstTemp = NULL;
    cXyz temp2;
    cXyz dstPos = eyePos;
    bool temp3 = field_0x994;
    
    switch(field_0x9D6) {
        case 1:
            temp2 = mLookAtPos;
            dstTemp = &temp2;
            break;
        case 2:
            desiredYRot = field_0x9BA;
            break;
        case 0:
        default:
            break;
    }
    
    if (field_0x9BC && field_0x9D7) {
        temp3 = false;
        m_jnt.setTrn();
    }

    if (m_jnt.trnChk()) {
        if(mEventCut.getTurnSpeed() != 0) {
            target = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&field_0x9B8, target, 4, 0x800);
    } else {
        field_0x9B8 = 0;
    }
    
    m_jnt.lookAtTarget(&current.angle.y, dstTemp, dstPos, desiredYRot, field_0x9B8, temp3);
    shape_angle = current.angle;
}

/* 00004478-000045C0       .text initTexPatternAnm__12daNpcPhoto_cFbi */
BOOL daNpcPhoto_c::initTexPatternAnm(bool i_modify, int i_param2) {
    J3DModelData *modelData = mpMorf->getModel()->getModelData();
    if(i_param2 == -1) {
        if(dComIfGs_isEventBit(l_save_dat.field_0x02)) {
            i_param2 = 1;
        } else {
            i_param2 = 0;
        }
    }
    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_btp_ix_tbl[i_param2]);
    JUT_ASSERT(0xBAA, m_head_tex_pattern != NULL);
    
    if(!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }
    mFrame = 0;
    mTimer = 0;
    return TRUE;
}

/* 000045C0-00004638       .text playTexPatternAnm__12daNpcPhoto_cFv */
void daNpcPhoto_c::playTexPatternAnm() {
    if (((field_0x9C9 & 0x80) == 0) && cLib_calcTimer(&mTimer)== 0) {
        if (mFrame >= m_head_tex_pattern->getFrameMax()) {
            mFrame -= m_head_tex_pattern->getFrameMax();
            mTimer = 0x78;
        } else {
            mFrame++;
        }
    }
}

/* 00004638-0000474C       .text playAnm__12daNpcPhoto_cFv */
void daNpcPhoto_c::playAnm() {
    field_0x9C9 &= 0xFE;
    u32 mtrlSndId;
    s8 roomNo = fopAcM_GetRoomNo(this);
    
    if (mObjAcch.ChkGroundHit()) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    else {
        mtrlSndId = 0;
    }
    
    if(mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(roomNo))){
        field_0x9C9 &= ~0x4;
        if (mpAnmDat != 0) {
            if (field_0x9CA > 0) {
                field_0x9CA--;
                if (field_0x9CA == 0) {
                    mpAnmDat++;
                    if (setAnmTbl(mpAnmDat) != 0) {
                        field_0x9C9 |= 1;
                    }
                } else {
                    setAnm(mpAnmDat->field_0x00, 0, 0.0f);
                }
            }
        }
    }
}

/* 0000474C-0000481C       .text setAnm__12daNpcPhoto_cFUcif */
void daNpcPhoto_c::setAnm(u8 param_1, int param_2, f32 param_3) {
    if(field_0x98C >= 0.0f) {
        param_3 = field_0x98C;
        field_0x98C = -1.0f;
    }

    J3DAnmTransform* pAnmRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[param_1]));
    mpMorf->setAnm(pAnmRes, param_2, param_3, 1.0f, 0.0f, -1.0f, NULL);
    field_0x9C8 = param_1;
}

/* 0000481C-000048D0       .text setAnmTbl__12daNpcPhoto_cFP12sPhotoAnmDat */
bool daNpcPhoto_c::setAnmTbl(sPhotoAnmDat* i_anmDat) {
    if((field_0x9C9 & 4) != 0){
        return false;
    }
    if(i_anmDat->field_0x00 == 0xFF) {
        mpAnmDat = 0;
        return true;
    }
    mpAnmDat = i_anmDat;
    field_0x9CA = mpAnmDat->field_0x02;
    
    int temp = 2;
    if(field_0x9CA > 0) {
        temp = 0;
    }
    if(field_0x9C8 != mpAnmDat->field_0x00 || temp == 0) {
        setAnm(mpAnmDat->field_0x00, temp, mpAnmDat->field_0x01);
    }

    return false;
}

/* 000048D0-00004950       .text XyCheckCB__12daNpcPhoto_cFi */
s16 daNpcPhoto_c::XyCheckCB(int i_itemBtn) {
    if(dComIfGs_isTmpBit(0x302) && !dComIfGs_isTmpBit(0x301)){
        attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    } else {
        attention_info.flags = fopAc_Attn_UNK1000000_e | fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    }
    return 1;
}

/* 00004950-00004A5C       .text XyEventCB__12daNpcPhoto_cFi */
s16 daNpcPhoto_c::XyEventCB(int i_itemBtn) {
    s16 eventIdx;
    u8 itemNo = dComIfGp_getSelectItem(i_itemBtn);
    if(itemNo == CAMERA2 && dComIfGs_isTmpBit(0x302)){
        if(dComIfGs_getPictureNum() < 3){
            eventIdx = mPhotoGetPhotoEventIdx;
            field_0x9C7 = false;
        } else {
            return dComIfGp_evmng_getEventIdx("DEFAULT_TALK_XY",0xff);
        }
    } else {
        if(itemNo == dItem_FIREFLY_BOTTLE_e && dComIfGs_getEventReg(l_save_dat.field_0x06) >= 6 && !dComIfGs_checkGetItem(CAMERA2)){
            eventIdx = mPhotoGetItem2EventIdx;
            field_0x9C7 = false;
        } else {
            eventIdx = dComIfGp_evmng_getEventIdx("DEFAULT_TALK_XY",0xff);
        }
    }
    return eventIdx;
}

/* 00004A5C-00004B08       .text isPhotoOk__12daNpcPhoto_cFv */
BOOL daNpcPhoto_c::isPhotoOk() {
    u8 reg = dComIfGs_getEventReg(l_save_dat.field_0x06);

    reg = reg & 0xff;
    if (reg == 1) {
        if (dComIfGp_getPictureResult() == 1) {
            return TRUE;
        }
    } else if (reg == 3) {
        if (dComIfGp_getPictureResult() == 2) {
            return TRUE;
        }
    } else if ((reg == 5) && (dComIfGp_getPictureResult() == 3)) {
        return TRUE;
    }
    return FALSE;
}

/* 00004B08-00004CCC       .text isPhotoDxOk__12daNpcPhoto_cFv */
BOOL daNpcPhoto_c::isPhotoDxOk() {
    switch(dKy_get_dayofweek()){
        case 0:
            if(dComIfGs_isEventBit(0x2D02)) {
                return TRUE;
            }
            break;
        case 1:
            if(dComIfGs_isEventBit(0x3910)) {
                return TRUE;
            }
            break;
        case 2:
            if (dComIfGs_isEventBit(0x3002) ||
                dComIfGs_isEventBit(0x3001) ||
                dComIfGs_isEventBit(0x3008) ||
                dComIfGs_isEventBit(0x3004) ||
                dComIfGs_isEventBit(0x3020) ||
                dComIfGs_isEventBit(0x3010) ||
                dComIfGs_isEventBit(0x3180)) {
                return TRUE;
            }
            break;
        case 3:
            if(dComIfGs_isEventBit(0x3920)) {
                return TRUE;
            }
            break;
        case 4:
            if(dComIfGs_isEventBit(0x1001)) {
                return TRUE;
            }
            break;
        case 5:
            if(dComIfGs_isEventBit(0x2D20)) {
                return TRUE;
            }
            break;
        case 6:
            if(dComIfGs_isEventBit(0x2D40)) {
                return TRUE;
            }
            break;
    }
    return FALSE;
}

/* 00004CCC-00004D44       .text setCollision__12daNpcPhoto_cFP8dCcD_Cyl4cXyzff */
void daNpcPhoto_c::setCollision(dCcD_Cyl* cyl, cXyz center, f32 radius, f32 height) {
    cyl->SetC(center);
    cyl->SetR(radius);
    cyl->SetH(height);
    dComIfG_Ccsp()->Set(cyl);
}

/* 00004D44-00004D64       .text daNpc_PhotoCreate__FPv */
static cPhs_State daNpc_PhotoCreate(void* i_this) {
    return static_cast<daNpcPhoto_c*>(i_this)->_create();
}

/* 00004D64-00004D88       .text daNpc_PhotoDelete__FPv */
static BOOL daNpc_PhotoDelete(void* i_this) {
    return static_cast<daNpcPhoto_c*>(i_this)->_delete();
}

/* 00004D88-00004DAC       .text daNpc_PhotoExecute__FPv */
static BOOL daNpc_PhotoExecute(void* i_this) {
    return static_cast<daNpcPhoto_c*>(i_this)->_execute();
}

/* 00004DAC-00004DD0       .text daNpc_PhotoDraw__FPv */
static BOOL daNpc_PhotoDraw(void* i_this) {
    return static_cast<daNpcPhoto_c*>(i_this)->_draw();
}

/* 00004DD0-00004DD8       .text daNpc_PhotoIsDelete__FPv */
static BOOL daNpc_PhotoIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_PhotoMethodTable = {
    (process_method_func)daNpc_PhotoCreate,
    (process_method_func)daNpc_PhotoDelete,
    (process_method_func)daNpc_PhotoExecute,
    (process_method_func)daNpc_PhotoIsDelete,
    (process_method_func)daNpc_PhotoDraw,
};

actor_process_profile_definition g_profile_NPC_PHOTO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_PHOTO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcPhoto_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_PHOTO,
    /* Actor SubMtd */ &daNpc_PhotoMethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
