/**
 * d_a_ship.cpp
 * King of Red Lions
 */

#include "d/actor/d_a_ship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_kankyo_wether.h"
#include "d/actor/d_a_sea.h"
#include "d/d_path.h"
#include "m_Do/m_Do_controller_pad.h"
#include "f_op/f_op_camera.h"
#include "d/actor/d_a_tornado.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_grid.h"
#include "d/res/res_ship.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

static char l_arcName[] = "Ship";
static Vec l_cannon_top = {85.0f, 0.0f, 10.0f};
static Vec l_tiller_top_offset = {34.0f, 0.0f, 15.0f};


const s16 daShip_HIO_c0::tiller_speed = 0x02BC;
const s16 daShip_HIO_c0::cannon_no_gravity_timer = 0x0008;
const s16 daShip_HIO_c0::throw_start_angle_speed = 0x1194;
const s16 daShip_HIO_c0::throw_return_angle_speed = 0x0E10;
const f32 daShip_HIO_c0::paddle_speed = 10.0f;
const f32 daShip_HIO_c0::min_speed = 0.0f;
const f32 daShip_HIO_c0::wind_inc_speed = 55.0f;
const f32 daShip_HIO_c0::r_inc_speed = 0.0f;
const f32 daShip_HIO_c0::r_wind_inc_speed = 0.0f;
const f32 daShip_HIO_c0::fly_rate = 0.6f;
const f32 daShip_HIO_c0::wind_rate = 0.5f;
const f32 daShip_HIO_c0::ef_dis_speed = 2.0f;
const f32 daShip_HIO_c0::ef_speed_rate = 0.7f;
const f32 daShip_HIO_c0::ef_front_x = -80.0f;
const f32 daShip_HIO_c0::ef_front_y = -50.0f;
const f32 daShip_HIO_c0::ef_front_z = -150.0f;
const f32 daShip_HIO_c0::ef_back_x = -40.0f;
const f32 daShip_HIO_c0::ef_back_y = -100.0f;
const f32 daShip_HIO_c0::ef_back_z = -350.0f;
const f32 daShip_HIO_c0::ef_sp_max_speed = 30.0f;
const f32 daShip_HIO_c0::ef_pitch = 1.0f;
const f32 daShip_HIO_c0::ef_ind_scroll = -0.04f;
const f32 daShip_HIO_c0::ef_ind_scale = 4.0f;
const f32 daShip_HIO_c0::cannon_speed = 110.0f;
const f32 daShip_HIO_c0::cannon_gravity = -2.5f;
const f32 daShip_HIO_c0::whirl_init_speed = 10.0f;
const f32 daShip_HIO_c0::whirl_inc_speed = 30.0f;
const f32 daShip_HIO_c0::whirl_distance = 4000.0f;
const f32 daShip_HIO_c0::tornado_init_speed = 30.0f;
const f32 daShip_HIO_c0::tornado_inc_speed = 40.0f;
const f32 daShip_HIO_c0::tornado_distance = 6000.0f;
const f32 daShip_HIO_c0::tornado_pull_speed = 5.0f;
const f32 daShip_HIO_c0::throw_start_speedF = 150.0f;
const f32 daShip_HIO_c0::throw_start_speed_y = 50.0f;

static daShip_HIO_c0 l_HIO;
cXyz daShip_c::l_rope_base_vec(0.0f, -10.0f, 0.0f);

/* 000000EC-0000023C       .text bodyJointCallBack__8daShip_cFi */
BOOL daShip_c::bodyJointCallBack(int jno) {
    J3DModel *pModel = mpBodyAnm->getModel();
    
    if ((jno == 10) || (jno == 5)) {
        mDoMtx_stack_c::ZrotS(m0366);
    }
    else if (jno == 7) {
        mDoMtx_stack_c::ZrotS(-mSailAngle);
    }
    else if (jno == 6) {
        mDoMtx_stack_c::ZrotS(0xC000);
        mDoMtx_stack_c::revConcat(pModel->getAnmMtx(jno));
        mpSalvageArmModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoMtx_stack_c::YrotM(-0x8000);
        mpCannonModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoMtx_stack_c::scaleS(m03E8, m03E8, m03E8);
    }
    mDoMtx_stack_c::revConcat(pModel->getAnmMtx(jno));
    pModel->setAnmMtx(jno, mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    return TRUE;
}

/* 0000023C-00000284       .text daShip_bodyJointCallBack__FP7J3DNodei */
static BOOL daShip_bodyJointCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daShip_c* i_this = reinterpret_cast<daShip_c*>(model->getUserArea());
        if (i_this) {
            i_this->bodyJointCallBack(jntNo);
        }
    }
    return TRUE;
}

/* 00000284-0000033C       .text cannonJointCallBack__8daShip_cFi */
BOOL daShip_c::cannonJointCallBack(int jno) {
    if (jno == 1) {
        mDoMtx_stack_c::XrotS(m0394);
    }
    else {
        mDoMtx_stack_c::YrotS(-m0396);
    }
    mDoMtx_stack_c::revConcat(mpCannonModel->getAnmMtx(jno));
    mpCannonModel->setAnmMtx(jno, mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    return TRUE;
}

/* 0000033C-00000380       .text daShip_cannonJointCallBack__FP7J3DNodei */
static BOOL daShip_cannonJointCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daShip_c* i_this = reinterpret_cast<daShip_c*>(model->getUserArea());
        i_this->cannonJointCallBack(jntNo);
    }
    return TRUE;
}

/* 00000380-00000414       .text craneJointCallBack__8daShip_cFv */
BOOL daShip_c::craneJointCallBack() {
    mDoMtx_stack_c::ZrotS(-(m0398 + m039C));
    mDoMtx_stack_c::revConcat(mpSalvageArmModel->getAnmMtx(1));
    mpSalvageArmModel->setAnmMtx(1, mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    return TRUE;
}

/* 00000414-00000450       .text daShip_craneJointCallBack__FP7J3DNodei */
static BOOL daShip_craneJointCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daShip_c* i_this = reinterpret_cast<daShip_c*>(model->getUserArea());
        i_this->craneJointCallBack();
    }
    return TRUE;
}

/* 00000450-00000474       .text headJointCallBack0__8daShip_cFv */
BOOL daShip_c::headJointCallBack0() {
    J3DAnmTransform* tempAnmTransform;
    if (mAnmTransform) {
        tempAnmTransform = mpHeadAnm->getAnm();
        mpHeadAnm->mpAnm = mAnmTransform;
        mAnmTransform = tempAnmTransform;
    }
    return TRUE;
}

/* 00000474-000004B0       .text daShip_headJointCallBack0__FP7J3DNodei */
static BOOL daShip_headJointCallBack0(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daShip_c* i_this = reinterpret_cast<daShip_c*>(model->getUserArea());
        i_this->headJointCallBack0();
    }
    return TRUE;
}

/* 000004B0-000005E4       .text headJointCallBack1__8daShip_cFi */
BOOL daShip_c::headJointCallBack1(int jno) {    
    MtxP jointAnmMtx = mpHeadAnm->getModel()->getAnmMtx(jno);
    float fVar1 = jointAnmMtx[0][3];
    float fVar2 = jointAnmMtx[1][3];
    float fVar3 = jointAnmMtx[2][3];
    
    short sVar5 = shape_angle.y + m03A2 * (jno + -2);
    mDoMtx_stack_c::YrotS(sVar5);
    mDoMtx_stack_c::ZXYrotM(m03A0, m03A2, 0);
    mDoMtx_stack_c::YrotM(-sVar5);
    mDoMtx_stack_c::concat(mpHeadAnm->getModel()->getAnmMtx(jno));
    
    mDoMtx_stack_c::get()[0][3] = fVar1;
    mDoMtx_stack_c::get()[1][3] = fVar2;
    mDoMtx_stack_c::get()[2][3] = fVar3;

    mpHeadAnm->getModel()->setAnmMtx(jno, mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    return TRUE;
}

/* 000005E4-00000628       .text daShip_headJointCallBack1__FP7J3DNodei */
static BOOL daShip_headJointCallBack1(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daShip_c* i_this = reinterpret_cast<daShip_c*>(model->getUserArea());
        i_this->headJointCallBack1(jntNo);
    }
    return TRUE;
}

/* 00000628-00000AD8       .text draw__8daShip_cFv */
BOOL daShip_c::draw() {
    static GXColor rope_color = {0xC8, 0x96, 0x32, 0xFF};
    J3DModel* model = mpBodyAnm->getModel();
    J3DModel* model_00 = mpHeadAnm->getModel();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    g_env_light.setLightTevColorType(model_00, &tevStr);

    dComIfGd_setListP1();
    
    if (m02A0 && m02A4) {
        j3dSys.onFlag(0x4);
        j3dSys.onFlag(0x8);
        
        cXyz local_5c(current.pos.x, current.pos.y + m03D8 + 5.0f, current.pos.z);
        
        f32 x = local_5c.x;
        f32 y = local_5c.y;
        f32 z = local_5c.z;
        z += cM_scos(m037C) * 10000.0f * cM_scos(shape_angle.y);
        y -= cM_ssin(m037C) * 10000.0f;
        x += cM_scos(m037C) * 10000.0f * cM_ssin(shape_angle.y);
        cXyz local_68(x, y, z);
        Mtx MStack_50;
        cMtx_lookAt(MStack_50, &local_5c, &local_68, m037E);
        mDoMtx_stack_c::YrotS(0xC000);
        mDoMtx_stack_c::XrotM(-0x8000);
        mDoMtx_stack_c::scaleM(1.0f, 2.0f, 0.25f);
        mDoMtx_stack_c::concat(MStack_50);
        mDoMtx_stack_c::revConcat(m02A8);
        m02A0->setEffectMtx(mDoMtx_stack_c::get());
        m02A4->setTranslationX(m03D4);
    }

    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) || dComIfGp_getAttention().Lockon() || daPy_getPlayerLinkActorClass()->getBodyAngleX() > -0x1000) {
        mDoExt_modelEntryDL(model);
    }

    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) || daPy_getPlayerLinkActorClass()->checkNoControll() || !dComIfGp_checkCameraAttentionStatus(0, 0x22)) {
        offStateFlg(daSFLG_HEAD_NO_DRAW_e);
        mDoExt_modelEntryDL(model_00);
    }
    else {
        onStateFlg(daSFLG_HEAD_NO_DRAW_e);
    }
    
    if (mPart == PART_CANNON_e) {
        g_env_light.setLightTevColorType(mpCannonModel, &tevStr);
        mDoExt_modelEntryDL(mpCannonModel);
    }
    else if (mPart == PART_CRANE_e) {
        g_env_light.setLightTevColorType(mpSalvageArmModel, &tevStr);
        mDoExt_modelEntryDL(mpSalvageArmModel);
        if (mRopeCnt >= 2) {
            mRopeLine.update(mRopeCnt, 5.0f, rope_color, 0, &tevStr);
            dComIfGd_set3DlineMat(&mRopeLine);
        }
        g_env_light.setLightTevColorType(mpLinkModel, &tevStr);
        mDoExt_modelUpdateDL(mpLinkModel);
    }

    dComIfGd_setList();

    mShadowId = dComIfGd_setShadow(mShadowId, 0, model, &current.pos, 1500.0f, 250.0f,
                                         current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, 
                                         &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
                                         
    if (mShadowId != 0) {
        dComIfGd_addRealShadow(mShadowId, model_00);
        if (mPart == PART_CANNON_e) {
            dComIfGd_addRealShadow(mShadowId, mpCannonModel);
        }
        else if (mPart == PART_CRANE_e) {
            dComIfGd_addRealShadow(mShadowId, mpSalvageArmModel);
        }
    }
    
    return TRUE;
}

/* 00000B14-00000B34       .text daShip_Draw__FP8daShip_c */
static BOOL daShip_Draw(daShip_c* i_this) {
    return ((daShip_c*)i_this)->draw();
}

/* 00000B34-00000DAC       .text checkForceMessage__8daShip_cFv */
BOOL daShip_c::checkForceMessage() {
    if (dComIfGs_isGetItem(1, 0) && !dComIfGs_isEventBit(0x908)) {
        mNextMessageNo = 0x5E0;
    }
    else if (dComIfGs_isSymbol(1) && !dComIfGs_isEventBit(0xA80)) {
        mNextMessageNo = 0x5EC;
    }
    else if (dComIfGs_isSymbol(2) && !dComIfGs_isEventBit(0xA08)) {
        mNextMessageNo = 0x5F6;
    }
    else if (dComIfGs_isEventBit(dSv_evtBit_c::ENDLESS_NIGHT) && !dComIfGs_isEventBit(0xA01)) {
        mNextMessageNo = 0x607;
    }
    else if (dComIfGs_checkGetItem(dItem_BOMB_BAG_e) && !dComIfGs_isEventBit(0x1F02)) {
        mNextMessageNo = 0x624;
    }
    else if (dComIfGs_isSymbol(0) && !dComIfGs_isEventBit(0x2F20)) {
        mNextMessageNo = 0xD5A;
    }
    else if (dComIfGs_isEventBit(0x2D10) && !daPy_getPlayerActorClass()->checkMasterSwordEquip()) {
        mNextMessageNo = 0xD65;
    }
    else if (dComIfGs_isEventBit(0x3E01) && !dComIfGs_isEventBit(0x3F80)) {
        mNextMessageNo = 0x1688;
    }
    else if (dComIfGs_isEventBit(0x2D02) && !dComIfGs_isEventBit(0x3201)) {
        mNextMessageNo = 0x1645;
    }
    else {
        return FALSE;
    }
    return TRUE;
}

/* 00000DAC-00001734       .text setInitMessage__8daShip_cFv */
void daShip_c::setInitMessage() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        return;
    }
    else if (!dComIfGs_isGetItem(1, 0)) {
        mNextMessageNo = 0x5de;
    }
    else if (checkForceMessage()) {
        return;
    }
    else if (dComIfGs_isEventBit(0x2110) && !dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) {
        mNextMessageNo = 0x623;
    }
    else if (checkStateFlg(daSFLG_UNK800000_e)) {
        mNextMessageNo = 0x636;
    }
    else if (dComIfGs_isEventBit(0x3D02)) {
        if (!strcmp(dComIfGp_getStartStageName(), "GanonA") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonB") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonC") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonD") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonE") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonN") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonM") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonL") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonJ") ||
            !strcmp(dComIfGp_getStartStageName(), "Xboss0") ||
            !strcmp(dComIfGp_getStartStageName(), "Xboss1") ||
            !strcmp(dComIfGp_getStartStageName(), "Xboss2") ||
            !strcmp(dComIfGp_getStartStageName(), "Xboss3") ||
            !strcmp(dComIfGp_getStartStageName(), "GanonK") ||
            !strcmp(dComIfGp_getStartStageName(), "GTower") ||
            !strcmp(dComIfGp_getStartStageName(), "Hyrule") ||
            !strcmp(dComIfGp_getStartStageName(), "Hyroom") ||
            !strcmp(dComIfGp_getStartStageName(), "kenroom")) {
            mNextMessageNo = 0xd77;
        }
        else {
            mNextMessageNo = 0xd78;
        }
    }
    else if (dComIfGs_isEventBit(0x2C02)) {
        mNextMessageNo = 0xd76;
    }
    else if (dComIfGs_isEventBit(0x2C01)) {
        mNextMessageNo = 0xd75;
    }
    else if (dComIfGs_isEventBit(0x2D08)) {
        if (!strcmp(dComIfGp_getStartStageName(), "Hyrule")) {
            mNextMessageNo = 0xd74;
        }
        else {
            mNextMessageNo = 0xd73;
        }
    }
    else if (dComIfGs_isEventBit(0x4004)) {
        if (dComIfGs_getTriforceNum() == 8) {
            mNextMessageNo = 0xd72;
        }
        else {
            mNextMessageNo = 0xd71;
        }
    }
    else if (dComIfGs_isEventBit(0x2E02)) {
        mNextMessageNo = 0xd70;
    }
    else if (dComIfGs_isEventBit(0x1610)) {
        mNextMessageNo = 0xd6f;
    }
    else if (dComIfGs_isEventBit(0x3A02)) {
        if (dComIfGs_isTact(4)) {
            mNextMessageNo = 0xd6e;
        }
        else {
            mNextMessageNo = 0xd6d;
        }
    }
    else if (dComIfGs_isEventBit(0x2E04)) {
        mNextMessageNo = 0xd6c;
    }
    else if (dComIfGs_isEventBit(0x1620)) {
        mNextMessageNo = 0xd6b;
    }
    else if (dComIfGs_isTact(3) || dComIfGs_isTact(4)) {
        mNextMessageNo = 0xd6a;
    }
    else if (dComIfGs_isEventBit(0x3910)) {
        if (!dComIfGs_isEventBit(0x3380)) {
            mNextMessageNo = 0xd7b;
        }
        else {
            mNextMessageNo = 0xd69;
        }
    }
    else if (dComIfGs_isEventBit(0x3040)) {
        mNextMessageNo = 0xd68;
    }
    else if (dComIfGs_isEventBit(0x3810)) {
        mNextMessageNo = 0xd67;
    }
    else if (daPy_getPlayerActorClass()->checkMasterSwordEquip()) {
        mNextMessageNo = 0xd66;
    }
    else if (dComIfGs_isEventBit(0x2D10)) {
        mNextMessageNo = 0xd65;
    }
    else if (dComIfGs_isEventBit(0x1E40)) {
        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_DUNGEON_e) {
            mNextMessageNo = 0xd63;
        }
        else {
            mNextMessageNo = 0xd64;
        }
    }
    else if (dComIfGs_isEventBit(0x2F20)) {
        mNextMessageNo = 0xd62;
    }
    else if (dComIfGs_isSymbol(0)) {
        mNextMessageNo = 0xd5a;
    }
    else if (dComIfGs_isEventBit(0x1940)) {
        mNextMessageNo = 0xd61;
    }
    else if (dComIfGs_isEventBit(0x3E10)) {
        if (!dComIfGs_isEventBit(0x3E01)) {
            mNextMessageNo = 0x1687;
        }
        else {
            if (dComIfGs_isEventBit(0x3F80)) {
                mNextMessageNo = 0x1689;
            }
            else {
                mNextMessageNo = 0x1688;
            }
        }
    }
    else if (dComIfGs_isEventBit(0x1F02)) {
        mNextMessageNo = 0xd60;
    }
    else if (dComIfGs_isEventBit(0x1F04)) {
        if (!dComIfGs_isEventBit(0x2110)) {
            mNextMessageNo = 0x621;
        }
        else {
            if (dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) {
                mNextMessageNo = 0x624;
            }
            else {
                mNextMessageNo = 0x623;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA02)) {
        if (dComIfGs_isEventBit(0x2A01)) {
            mNextMessageNo = 0xd5f;
        }
        else {
            if (dComIfGs_isEventBit(0xA01)) {
                mNextMessageNo = 0x608;
            }
            else {
                mNextMessageNo = 0x607;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA08)) {
        if (dComIfGs_isEventBit(0x2A02)) {
            mNextMessageNo = 0xd5e;
        }
        else {
            if (dComIfGs_isEventBit(0xA04)) {
                mNextMessageNo = 0x5f9;
            }
            else {
                mNextMessageNo = 0x5f8;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA20)) {
        if (dComIfGs_isSymbol(2)) {
            mNextMessageNo = 0x5f6;
        }
        else {
            if (dComIfGs_isEventBit(0x2B80)) {
                mNextMessageNo = 0x5f5;
            }
            else {
                mNextMessageNo = 0x5f4;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA80)) {
        if (dComIfGs_isEventBit(0x1980)) {
            mNextMessageNo = 0xd5d;
        }
        else {
            cXyz* windVec = dKyw_get_wind_vec();
            if (abs(cM_atan2s(windVec->x, windVec->z)) < 0x1000) {
                mNextMessageNo = 0x5ee;
            }
            else {
                mNextMessageNo = 0x5ef;
            }
        }
    }
    else if (dComIfGs_isEventBit(0x902)) {
        if (dComIfGs_isSymbol(1)) {
            mNextMessageNo = 0x5ec;
        }
        else {
            if (dComIfGs_isEventBit(0xA10)) {
                mNextMessageNo = 0x5eb;
            }
            else {
                mNextMessageNo = 0x5ea;
            }
        }
    }
    else {
        if (dComIfGs_isEventBit(dSv_evtBit_c::RODE_KORL)) {
            mNextMessageNo = 0xd5c;
        }
        else {
            if (dComIfGs_isEventBit(0x908)) {
                mNextMessageNo = 0x5df;
            }
            else {
                mNextMessageNo = 0x5e0;
            }
        }
    }
}

/* 00001734-00001BD0       .text setNextMessage__8daShip_cFP9msg_class */
BOOL daShip_c::setNextMessage(msg_class* msg) {
    u32 currMessageNo;
    
    currMessageNo = mNextMessageNo;
    if (currMessageNo != 0x5dd && currMessageNo != 0x5de && currMessageNo != 0x5df &&
        currMessageNo != 0x5eb && currMessageNo != 0x5ee && currMessageNo != 0x5ef &&
        currMessageNo != 0x5f5 && currMessageNo != 0x5f9 &&
        currMessageNo != 0x608 && currMessageNo != 0x609 && currMessageNo != 0x60a &&
        currMessageNo != 0x621 && currMessageNo != 0x623 && currMessageNo != 0x636 &&
        (currMessageNo < 0xd5c || currMessageNo > 0xd78) &&
        currMessageNo != 0xd7b && currMessageNo != 0x164c &&
        currMessageNo != 0x1650 && currMessageNo != 0x1651 &&
        currMessageNo != 0x1684 && currMessageNo != 0x1685 &&
        currMessageNo != 0x1687 && currMessageNo != 0x1689)
        {
        if (currMessageNo == 0x5e4) {
            dComIfGs_onEventBit(0x908);
        }
        else if (currMessageNo == 0x5ea) {
            dComIfGs_onEventBit(0xa10);
        }
        else if (currMessageNo == 0x5ed) {
            dComIfGs_onEventBit(0xa80);
        }
        else if (currMessageNo == 0x5f4) {
            dComIfGs_onEventBit(0x2b80);
        }
        else if (currMessageNo == 0x5f7) {
            dComIfGs_onEventBit(0xa08);
        }
        else if (currMessageNo == 0x5f8) {
            dComIfGs_onEventBit(0xa04);
        }
        else if (currMessageNo == 0x607) {
            dComIfGs_onEventBit(0xa01);
        }
        else if (currMessageNo == 0x622) {
            dComIfGs_onEventBit(0x1f01);
        }
        else if (currMessageNo == 0x624) {
            dComIfGs_onEventBit(0x1f02);
        }
        else if (currMessageNo == 0xd5b) {
            dComIfGs_onEventBit(0x2f20);
        }
        else if (currMessageNo == 0x1682) {
            dComIfGs_onEventBit(0x3d04);
            mNextMessageNo = 0;
        }
        else if (currMessageNo == 0x1688) {
            dComIfGs_onEventBit(0x3f80);
        }
        else {
            if (currMessageNo == 0x168c) {
                dComIfGs_onEventBit(0x3840);
            }
            else {
                if (currMessageNo == 0x5e0) {
                    mNextMessageNo = 0x5e1;
                }
                else if (currMessageNo == 0x5e1) {
                    mNextMessageNo = 0x5e2;
                }
                else if (currMessageNo == 0x5e2) {
                    if (msg->mSelectNum == 0) {
                        mNextMessageNo = 0x5e4;
                    }
                    else {
                        mNextMessageNo = 0x5e3;
                    }
                }
                else if (currMessageNo == 0x5e3) {
                    mNextMessageNo = 0x5e1;
                }
                else if (currMessageNo == 0x5ec) {
                    mNextMessageNo = 0x5ed;
                }
                else if (currMessageNo == 0x5f6) {
                    mNextMessageNo = 0x5f7;
                }
                else if (currMessageNo == 0xd5a) {
                    mNextMessageNo = 0xd5b;
                }
                else if (currMessageNo == 0x1645) {
                    mNextMessageNo = 0x1646;
                }
                else if (currMessageNo == 0x1646) {
                    mNextMessageNo = 0x1647;
                }
                else if (currMessageNo == 0x1647) {
                    mNextMessageNo = 0x1648;
                }
                else if (currMessageNo == 0x1648) {
                    mNextMessageNo = 0x1649;
                }
                else if (currMessageNo == 0x1649) {
                    mNextMessageNo = 0x164a;
                }
                else if (currMessageNo == 0x164a) {
                    mNextMessageNo = 0x164b;
                }
                else if (currMessageNo == 0x164b) {
                    dComIfGs_onEventBit(0x3201);
                    mNextMessageNo = 0x164c;
                }
                else if (currMessageNo == 0x164d) {
                    mNextMessageNo = 0x164e;
                }
                else if (currMessageNo == 0x164e) {
                    mNextMessageNo = 0x164f;
                }
                else if (currMessageNo == 0x164f) {
                    dComIfGs_onEventBit(0x3380);
                    if (dComIfGs_getTriforceNum() > 0) {
                        mNextMessageNo = 0x1650;
                    }
                    else {
                        mNextMessageNo = 0x1651;
                    }
                }
                else if (currMessageNo == 0x1683) {
                    dComIfGs_onEventBit(0x3e20);
                    if (dComIfGs_getItem(12) != dItem_NONE_e) {
                        mNextMessageNo = 0x1685;
                    }
                    else {
                        mNextMessageNo = 0x1684;
                    }
                }
                return FALSE;
            }
        }
    }
    return TRUE;
}

/* 00001BD0-00001C24       .text seStart__8daShip_cFUlP4cXyz */
void daShip_c::seStart(u32 i_seNum, cXyz* i_sePos) {
    mDoAud_seStart(i_seNum, i_sePos, 0, m034A);
}

/* 00001C24-00001D50       .text setSailAngle__8daShip_cFv */
void daShip_c::setSailAngle() {
    short sVar1;
    cXyz* windVec = dKyw_get_wind_vec();
    if (mTornadoActor) {
        sVar1 = (s16)(m03AA + 0x4000) - shape_angle.y;
    }
    else {
        sVar1 = cM_atan2s(windVec->x, windVec->z) - shape_angle.y;
    }
    if (sVar1 > 0x800) {
        m0380 = -0x1555;
    }
    else {
        if (sVar1 < -0x800) {
            m0380 = 0x1555;
        }
        else if (m0380 == 0) {
            if (sVar1 >= 0) {
                m0380 = -0x1555;
            }
            else {
                m0380 = 0x1555;
            }
        }
    }
    cLib_addCalcAngleS(&mSailAngle, m0380, 0x10, 0x800, 0x20);
    m0378 = mSailAngle >> 1;
    if (mSailAngle * m0380 < 0) {
        if (!checkStateFlg(daSFLG_UNK2_e)) {
            seStart(JA_SE_SHIP_SAIL_MOVE, &m0444);
            onStateFlg(daSFLG_UNK2_e);
        }
    }
    else {
        offStateFlg(daSFLG_UNK2_e);
    }
}

/* 00001D50-00001E08       .text setControllAngle__8daShip_cFs */
void daShip_c::setControllAngle(short angle) {
    short sVar1 = angle - m036C;
    short sVar2 = sVar1 * 0.05f;
    if (sVar2 == 0) {
        if (sVar1 > 0) {
            sVar2 = 1;
        }
        else if (sVar1 < 0) {
            sVar2 = -1;
        }
    }
    m036E += sVar2;
    m036C += m036E;
    cLib_addCalcAngleS(&m036E, 0, 0x14, 0x1000, 4);
}

/* 00001E08-00001E9C       .text getMaxWaterY__8daShip_cFP4cXyz */
void daShip_c::getMaxWaterY(cXyz* shipPos) {    
    if (daSea_ChkArea(shipPos->x, shipPos->z)) {
        shipPos->y = daSea_calcWave(shipPos->x, shipPos->z);
        if (m03F8 > shipPos->y) {
            shipPos->y = m03F8;
        }
    }
    else {
        if (m03F8 != -G_CM3D_F_INF) {
            shipPos->y = m03F8;
        }
        else {
            shipPos->y = m03F4;
        }
    }
}

/* 00001E9C-00002314       .text setWaveAngle__8daShip_cFPsPs */
void daShip_c::setWaveAngle(short* param1, short* param2) {
    static cXyz local_front(0.0f, 0.0f, 180.0f);
    static cXyz local_back(0.0f, 0.0f, -190.0f);
    static cXyz local_right(-80.0f, 0.0f, 0.0f);
    static cXyz local_left(80.0f, 0.0f, 0.0f);

    mDoMtx_stack_c::transS(current.pos);
    
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);

    cXyz frontPos;
    cXyz leftPos;
    cXyz rightPos;
    cXyz backPos;
    
    mDoMtx_stack_c::multVec(&local_front, &frontPos);
    mDoMtx_stack_c::multVec(&local_back, &backPos);
    mDoMtx_stack_c::multVec(&local_right, &rightPos);
    mDoMtx_stack_c::multVec(&local_left, &leftPos);

    getMaxWaterY(&frontPos);
    getMaxWaterY(&backPos);
    getMaxWaterY(&rightPos);
    getMaxWaterY(&leftPos);

    cXyz local_9c = frontPos - backPos;
    cXyz local_a8 = rightPos - leftPos;

    *param2 = cM_atan2s(-local_a8.y, local_a8.absXZ());
    *param1 = cM_atan2s(-local_9c.y, local_9c.absXZ());
    
    short iVar3 = *param1 - m0370;
    short iVar2 = *param2 - m0372;
    
    m0376 += (iVar2 * 0.045f);
    m0372 += m0376;
    
    cLib_addCalcAngleS(&m0376, 0, 0x14, 0x1000, 4);
    m0374 += (iVar3 * 0.045f);
    m0370 += m0374;
    cLib_addCalcAngleS(&m0374, 0, 0x14, 0x1000, 4);
}

/* 00002314-000023E0       .text getWaterY__8daShip_cFv */
f32 daShip_c::getWaterY() {
    float waterY;
    BOOL waterHit = mAcch.ChkWaterHit();
    if (waterHit) {
        m03F8 = mAcch.m_wtr.GetHeight();
    }
    else {
        m03F8 = -G_CM3D_F_INF;
    }
    if (daSea_ChkArea(current.pos.x, current.pos.z)) {
        waterY = daSea_calcWave(current.pos.x, current.pos.z);
        if (!waterHit || waterY > m03F8) {
            return waterY;
        }
    }
    if (waterHit) {
        waterY = m03F8;
    }
    else {
        daPy_lk_c* link = daPy_getPlayerLinkActorClass();
        if (link && link->mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK44_e ) {
            waterY = 0.0f;
        }
        else {
            waterY = m03F4;
        }
    }
    return waterY;
}

/* 000023E0-00002824       .text setYPos__8daShip_cFv */
void daShip_c::setYPos() {
    float fVar5;
    float fVar4;
    float fVar2;
    
    m03F4 = getWaterY();
    if (!checkStateFlg(daSFLG_UNK10_e)) {
        onStateFlg(daSFLG_UNK10_e);
        if (mCurMode != MODE_START_MODE_WARP_e && mCurMode != MODE_START_MODE_THROW_e && m0351 != 11) {
            current.pos.y = m03F4;
        }
    }

    if (mCurMode == 12 || mCurMode == 15 || mCurMode == 14) {
        return;
    }

    fVar2 = m03F4 - current.pos.y;
    
    if (checkStateFlg(daSFLG_FLY_e)) {
        if (mCurMode == MODE_START_MODE_WARP_e || mCurMode == MODE_START_MODE_THROW_e) {
            return;
        }
        if (fVar2 >= 0.0f) {
            onStateFlg(daSFLG_LAND_e);
            if (!checkStateFlg(daSFLG_UNK2000000_e)) {
                offStateFlg(daSFLG_FLY_e);
                if (speed.y < -15.0f) {
                    speed.y = -15.0f;
                }
                m03D0 = speed.y * 0.5f;
                speedF *= 0.85f;
                m0388 = 30;
            }
        }
    }
    else {
        fVar2 = std::abs(speedF) / 55.0f;
        if (fVar2 > 1.0f) {
            fVar2 = 1.0f;
        }

        current.pos.y += fVar2 * ((m03F4 - current.pos.y) * 0.1f);
        m03D0 += (m03F4 - current.pos.y) * 0.05f;

        if (m03D0 > 20.0f) {
            m03D0 = 20.0f;
        }
        else if (m03D0 < -20.0f) {
            m03D0 = -20.0f;
        }   

        current.pos.y += m03D0;
        m03B0 += 1000.0f + cM_rndF(1000.0f) + 500.0f * fVar2;
        current.pos.y += fVar2 * 0.25f * cM_ssin(m03B0) + 0.6f;

        cLib_addCalc(&m03D0, 0.0f, 0.05f, 1.0f, 0.05f);

        fVar4 = current.pos.y;
        fVar5 = m03F4 + 40.0f;
        if (fVar4 > fVar5) {
            current.pos.y = fVar5;
        }
        else {
            fVar5 = m03F4 - 60.0f;
            if (fVar4 < fVar5) {
                current.pos.y = fVar5;
            }
        }

        m03AE += (fVar2 * 0.5f + 1.0f) * (cM_rndF(800.0f) + 800.0f);
        m03AC += (fVar2 * 0.5f + 1.0f) * (cM_rndF(600.0f) + 600.0f);

        m0370 += fVar2 * 100.0f * cM_ssin(m03AE) + 30.0f;
        m0372 += fVar2 * 115.0f * cM_ssin(m03AC) + 35.0f;
    }
}

/* 00002824-00002CC4       .text checkOutRange__8daShip_cFv */
BOOL daShip_c::checkOutRange() {
    dPnt* pnt;
    dPath* path;
    cXyz* closestPoint;
    cXyz* nextPoint;
    cXyz* prevPoint;
    int lastIndex;
    int closestIndex;
    int pathIndex;
    BOOL bVar4;
    BOOL bVar5;

    if (m034B == 0xFF) {
        return FALSE;
    }

    pathIndex = 0;
    bVar4 = FALSE;
    bVar5 = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SEA_e;
    path = dPath_GetRoomPath(m034B, -1);
    while (path) {
        pnt = path->m_points;
        if (path->m_num < 3) {
            path = dPath_GetNextRoomPath(path, -1);
            pathIndex++;
            continue;
        }
        if (bVar5) {
            if (
                (pathIndex == 0 && dComIfGs_isEventBit(0x902)) ||
                (pathIndex == 1 && dComIfGs_isSymbol(2)) ||
                (pathIndex == 2 && daPy_getPlayerActorClass()->checkMasterSwordEquip())
            ) {
                path = dPath_GetNextRoomPath(path, -1);
                pathIndex++;
                continue;
            } 
        }

        float minDist = FLOAT_MAX;
        
        for (int i = 0; i < path->m_num; pnt++, i++) {
            float dx = current.pos.x - pnt->m_position.x;
            float dz = current.pos.z - pnt->m_position.z;
            
            float distXZ = dx * dx + dz * dz;
            
            if (minDist > distXZ) {
                closestIndex = i;
                minDist = distXZ;
                closestPoint = &pnt->m_position;
            }
        }

        lastIndex = path->m_num - 1;

        if (closestIndex == lastIndex) {
            nextPoint = &path->m_points->m_position;
        }
        else {
            nextPoint = &(path->m_points + closestIndex + 1)->m_position;
        }

        if (closestIndex == 0) {
            prevPoint = &(path->m_points + lastIndex)->m_position;
        }
        else {
            prevPoint = &(path->m_points + closestIndex - 1)->m_position;
        }

        s16 angleNext = cM_atan2s(nextPoint->x - closestPoint->x, nextPoint->z - closestPoint->z);
        s16 anglePrev = cM_atan2s(closestPoint->x - prevPoint->x, closestPoint->z - prevPoint->z);
        s16 angleCurrent = cM_atan2s(current.pos.x - closestPoint->x, current.pos.z - closestPoint->z);

        s16 diffNext = angleCurrent - angleNext;
        s16 diffPrev = cM_atan2s(current.pos.x - prevPoint->x, current.pos.z - prevPoint->z) - anglePrev;
        
        if ((s16)(angleNext - anglePrev) >= 0) {
            if (diffNext < 0) {
                m038C = angleNext + 0x4000;
                bVar4 = TRUE;
            }
            if (diffPrev < 0) {
                m038C = anglePrev + 0x4000;
                bVar4 = TRUE;
            }
        } 
        else if (diffNext < 0 && diffPrev < 0) {
            float dxNext = nextPoint->x - current.pos.x;
            float dzNext = nextPoint->z - current.pos.z;
            float distNext = std::sqrtf(dxNext * dxNext + dzNext * dzNext);
            
            float dxPrev = prevPoint->x - current.pos.x;
            float dzPrev = prevPoint->z - current.pos.z;
            float distPrev = std::sqrtf(dxPrev * dxPrev + dzPrev * dzPrev);
            
            if (distNext > distPrev) {
                m038C = anglePrev + 0x4000;
            }
            else {
                m038C = angleNext + 0x4000;
            }
            
            bVar4 = TRUE;
        }
        
        if (bVar4) {
            if (dComIfGp_getMiniGameType() == 1) {
                mNextMessageNo = 0x60a;
            }
            else if (bVar5 && pathIndex != 3) {
                mNextMessageNo = 0x609;
            }
            else {
                mNextMessageNo = 0x5dd;
            }

            onStateFlg(daSFLG_UNK400000_e);
            return TRUE;
        }
        path = dPath_GetNextRoomPath(path, -1);
        pathIndex++;
    }
    return FALSE;
}

/* 00002CC4-00002CFC       .text decrementShipSpeed__8daShip_cFf */
void daShip_c::decrementShipSpeed(float decrementSpeed) {
    cLib_addCalc(&speedF, decrementSpeed, 0.05f, 0.1f, 0.015f);
}

/* 00002CFC-00002D5C       .text firstDecrementShipSpeed__8daShip_cFf */
void daShip_c::firstDecrementShipSpeed(float decrementSpeed) {
    if (cLib_addCalc(&speedF, decrementSpeed, 0.1f, 5.0f, 1.0f) < 3.0f) {
        m03E0 = 10000.0f;
    }
}

/* 00002D5C-00002D90       .text getAimControllAngle__8daShip_cFs */
s16 daShip_c::getAimControllAngle(short referenceAngle) {
    s16 aimControlAngle = (s16)(shape_angle.y - referenceAngle) * 7;
    if (aimControlAngle > 0x600) {
        aimControlAngle = 0x600;
    } else if (aimControlAngle < -0x600) {
        aimControlAngle = -0x600;
    }
    return aimControlAngle;
}

/* 00002D90-00002EE0       .text setMoveAngle__8daShip_cFs */
void daShip_c::setMoveAngle(short moveAngle) {
    float turnRate;
    float maxTurnRate;
    float minTurnRate;
    short initialAngle;
    bool cannotMove = FALSE;
    if (mTornadoActor || mWhirlActor != 0) {
        cannotMove = TRUE;
    }
    if (!cannotMove) {
        initialAngle = shape_angle.y;
        turnRate = 4.0f - std::abs(speedF) / 55.0f * 3.0f;
        maxTurnRate = 3.6f;
        minTurnRate = 0.1f;
        if (turnRate > maxTurnRate) {
            turnRate = maxTurnRate;
        }
        else if (turnRate < minTurnRate) {
            turnRate = minTurnRate;
        }
        if (m0388 >= 0xF) {
            turnRate = maxTurnRate;
        }
        else {
            turnRate += ((3.6f - turnRate) * m0388) / 15.0f;
        }
        shape_angle.y += (s32)(-turnRate * (moveAngle >> 6));
        setControllAngle(getAimControllAngle(initialAngle));
        current.angle.y = shape_angle.y;
    }
}

/* 00002EE0-00002FBC       .text changeDemoEndProc__8daShip_cFv */
void daShip_c::changeDemoEndProc() {  
    offStateFlg(daSFLG_UNK8000_e);  
    if (checkStateFlg(daSFLG_UNK80000_e)) {
        mpHeadAnm->setPlaySpeed(-1.0f);
        offStateFlg(daSFLG_UNK80000_e);
    }
    if ((m0351 == 8) || checkStateFlg(daSFLG_UNK4000000_e)) {
        m0366 = 0;
        offStateFlg(daSFLG_UNK4000000_e);
    }
    gravity = -2.5f;
    
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        if (mPart == PART_WAIT_e) {
            procPaddleMove_init();
        }
        else if (mPart == PART_CANNON_e) {
            procCannonReady_init();
        }
        else if (mPart == PART_CRANE_e) {
            procCraneReady_init();
        }
        else {
            procSteerMove_init();
        }
    }
    else {
        procWait_init();
    }
}

/* 00002FBC-000031E4       .text setCrashData__8daShip_cFs */
void daShip_c::setCrashData(short param1) {
    float fVar1;
    float fVar2;
    daPy_lk_c *link;
    s16 iVar5;
    if (!dComIfGp_event_runCheck()) {
        link = daPy_getPlayerLinkActorClass();
        if (!link->checkNoDamageMode() && !link->checkNoControll()) {
            if (!checkForceMove()) {
                link->onShipDrop(param1);
                procWait_init();
            }
        }
        onStateFlg(daSFLG_UNK8000000_e);
        if (m03B6 == 0) {
            if (speedF > l_HIO.wind_inc_speed) {
                speedF = l_HIO.wind_inc_speed;
            }
            speedF *= l_HIO.ef_speed_rate;
            iVar5 = param1 - shape_angle.y;
            fVar1 = cM_ssin(iVar5);
            fVar2 = cM_scos(iVar5);
            m0370 += fVar2 * 3072.0f;
            m0374 += fVar2 * 500.0f;
            m0372 -= fVar1 * 3072.0f;
            m0376 -= fVar1 * 500.0f;
            m03B6 = 30;
        }
        else {
            m03B6--;
        }
    }
}

/* 000031E4-00003490       .text checkNextMode__8daShip_cFi */
BOOL daShip_c::checkNextMode(int i_curMode) {
    if (checkStateFlg(daSFLG_UNK4_e) != 0) {
        setCrashData(shape_angle.y + 0x8000);
        offStateFlg(daSFLG_UNK4_e);
        return TRUE;
    }

    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        if (mNextMode == MODE_GET_OFF_FIRST_e) {
            procGetOff_init();
        }
        else {
            procWait_init();
        }
        return TRUE;
    }
    
    if (!dComIfGp_event_runCheck()) {
        cXyz* tgRVecP;
        cXyz* tgHitPos;
        dCcD_GObjInf* tgHitObj;
        
        tgRVecP = NULL;
        tgHitPos = NULL;
        tgHitObj = NULL;

        if (mSph.ChkTgHit()) {
            tgRVecP = mSph.GetTgRVecP();
            tgHitPos = mSph.GetTgHitPosP();
            tgHitObj = mSph.GetTgHitGObj();
            
        }
        else {
            dCcD_Cyl* cyl = mCyl;
            for(int i = 0; i < 3; i++, cyl++) {
                if (cyl->ChkTgHit()) {
                    tgRVecP = cyl->GetTgRVecP();
                    tgHitPos = cyl->GetTgHitPosP();
                    tgHitObj = cyl->GetTgHitGObj();
                }
            }
        }

        if (tgHitObj && !(tgHitObj->GetAtType() - AT_TYPE_WIND)) {
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                onStateFlg((daSHIP_SFLG)(daSFLG_FLY_e | daSFLG_UNK2000000_e));
            }
        }
        else {
            if (tgRVecP) {
                short sVar2;
                if (tgRVecP->abs2XZ() < 0.1f) {
                    cXyz local_20 = current.pos - *tgHitPos;
                    if (local_20.abs2XZ() < 0.1f) {
                        sVar2 = shape_angle.y + 0x8000;
                    }
                    else {
                        sVar2 = cM_atan2s(local_20.x, local_20.z);
                    }
                }
                else {
                    sVar2 = cM_atan2s(tgRVecP->x, tgRVecP->z);
                }
                setCrashData(sVar2);
                return TRUE;
            }
        }
    }

    if (i_curMode == mNextMode) {
        return FALSE;
    }
    else if (mNextMode == MODE_PADDLE_MOVE_e) {
        procPaddleMove_init();
    }
    else if (mNextMode == MODE_STEER_MOVE_e) {
        procSteerMove_init();
    }
    else if (mNextMode == 9) {
        procCannonReady_init();
    }
    else if (mNextMode == 10) {
        procCraneReady_init();
    }
    else if (mNextMode == MODE_TACT_WARP_e) {
        procTactWarp_init();
    }
    else {
        return FALSE;
    }
    return TRUE;
}

/* 00003490-0000358C       .text setPartOnAnime__8daShip_cFUc */
void daShip_c::setPartOnAnime(u8 i_part) {
    J3DAnmTransform* pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, SHIP_BCK_FN_MAST_ON2);
    mpBodyAnm->setAnm(pAnimRes, J3DFrameCtrl::EMode_NONE, 3.0f, 1.0f, 0.0f, -1.0f, NULL);
    m0392 = SHIP_BCK_FN_MAST_ON2;
    mPart = i_part;
    if (mPart == PART_STEER_e) {
        seStart(JA_SE_SHIP_SAIL_OUT, &m0444);
        m03E8 = 1.0f;
    }
    else if (mPart == PART_CANNON_e) {
        seStart(JA_SE_LK_SHIP_CANNON_OUT, &m0444);
        m03E8 = 0.001f;
    }
    else if (mPart == PART_CRANE_e) {
        seStart(JA_SE_LK_SHIP_CRANE_OUT, &m0444);
        m03E8 = 0.001f;
    }
}

/* 0000358C-0000366C       .text setPartOffAnime__8daShip_cFv */
void daShip_c::setPartOffAnime() {
    J3DAnmTransform* pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, SHIP_BCK_FN_MAST_OFF2);
    mpBodyAnm->setAnm(pAnimRes, J3DFrameCtrl::EMode_NONE, 3.0f, 1.0f, 0.0f, -1.0f, NULL);
    if (mPart == PART_CRANE_e) {
        seStart(JA_SE_LK_SHIP_CRANE_IN, &m0444);
    }
    else if (mPart == PART_CANNON_e) {
        seStart(JA_SE_LK_SHIP_CANNON_IN, &m0444);
    }
    else {
        seStart(JA_SE_SHIP_SAIL_IN, &m0444);
    }
    m0392 = SHIP_BCK_FN_MAST_OFF2;
    offStateFlg(daSFLG_SAIL_ON_e);
}

/* 0000366C-00003844       .text setPartAnimeInit__8daShip_cFUc */
void daShip_c::setPartAnimeInit(u8 i_part) {
    float fVar1 = 1.0f - mpBodyAnm->getFrame() / mpBodyAnm->getEndFrame();
    if (i_part == 0) {
        if (m0392 == SHIP_BCK_FN_MAST_ON2) {
            setPartOffAnime();
            mpBodyAnm->setFrame(fVar1 * mpBodyAnm->getEndFrame());
        }
    }
    else if (mPart != i_part) {
        if (m0392 == SHIP_BCK_FN_MAST_ON2) {
            setPartOffAnime();
            mpBodyAnm->setFrame(fVar1 * mpBodyAnm->getEndFrame());
        }
        else if (mpBodyAnm->getPlaySpeed() < 0.01f) {
            setPartOnAnime(i_part);
        }
    }
    else if (m0392 == SHIP_BCK_FN_MAST_OFF2) {
        setPartOnAnime(i_part);
        mpBodyAnm->setFrame(fVar1 * mpBodyAnm->getEndFrame());
    }
}

/* 00003844-00003A44       .text setSelfMove__8daShip_cFi */
void daShip_c::setSelfMove(int param_1) {
    BOOL bVar1;
    short sVar2;
    float fVar6;
    
    if (param_1) {
        sVar2 = mStickMVal * 8192.0f * -cM_ssin(mStickMAng);
    }
    else {
        sVar2 = 0;
    }
    cLib_addCalcAngleS(&m0366, sVar2, 4, 700, 0x100);
    setMoveAngle(m0366);
    if (!checkStateFlg(daSFLG_FLY_e)) {
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e) || dComIfGp_event_runCheck() || daPy_getPlayerLinkActorClass()->checkNoControll()) {
            firstDecrementShipSpeed(0.0f);
        }
        else {
            if (m03E0 <= speedF) {
                firstDecrementShipSpeed(m03E0);
            }
            else {
                if (dComIfGp_getDoStatus() == dActStts_STOP_e && (CPad_CHECK_HOLD_A(0))) {
                    fVar6 = cLib_addCalc(&speedF, 0.0f, 0.1f, 1.0f, 0.1f);
                }
                else {
                    fVar6 = g_mDoCPd_cpadInfo[0].mTriggerRight * 10.0f; //Not sure if this is a macro either
                    bVar1 = FALSE;
                    if (mAcch.ChkWallHit()) {
                        for (int i = 0; i < m03CC; i++) {
                            if (mAcchCir[i].ChkWallHit() && cLib_distanceAngleS(mAcchCir[i].GetWallAngleY(), shape_angle.y) > 0x5000) {
                                bVar1 = TRUE;
                            }
                        }
                    }
                    if (bVar1 && speedF > fVar6) {
                        firstDecrementShipSpeed(fVar6);
                    }
                    else {
                        decrementShipSpeed(fVar6);
                    }
                }
            }
        }
    }
}

/* 00003A44-00003AA0       .text procWait_init__8daShip_cFv */
BOOL daShip_c::procWait_init() {  
    mCurMode = MODE_WAIT_e;
    mProc = &daShip_c::procWait;
    m037A = 0;
    if (m0392 != SHIP_BCK_FN_MAST_OFF2) {
        setPartOffAnime();
    }
    return TRUE;
}

/* 00003AA0-00003B94       .text procWait__8daShip_cFv */
BOOL daShip_c::procWait() {  
    cLib_addCalc(&speedF, 0.0f, 0.1f, 1.0f, 0.05f);
    
    if (mpBodyAnm->getFrame() >= 7.0f) {
        mPart = PART_WAIT_e;
        m03E8 = 1.0f;
    }

    if (mNextMode == MODE_READY_FIRST_e) {
        procReady_init();
    }
    else if (mNextMode == MODE_PADDLE_MOVE_e) {
        procPaddleMove_init();
    }
    else if (mNextMode == MODE_START_MODE_WARP_e) {
        procStartModeWarp_init();
    }
    else if (mNextMode == MODE_START_MODE_THROW_e) {
        procStartModeThrow_init();
    }
    else {
        setControllAngle(0);
        cLib_addCalcAngleS(&m0366, 0, 2, 0x1000, 0x400);
    }

    return TRUE;
}

/* 00003B94-00003BC4       .text procReady_init__8daShip_cFv */
BOOL daShip_c::procReady_init() {
    mProc = &daShip_c::procReady;
    mCurMode = MODE_READY_FIRST_e;
    return TRUE;
}

/* 00003BC4-00003C7C       .text procReady__8daShip_cFv */
BOOL daShip_c::procReady() {
    short playerAngle;
  
    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e | daPyStts0_UNK1000000_e)) {
        procWait_init();
    }
    else if (mNextMode == MODE_PADDLE_MOVE_e) {
        procPaddleMove_init();
    }
    else {
        if (mNextMode == 4) {
            mCurMode = 4;
        }
        if (mCurMode == MODE_READY_FIRST_e) {
            playerAngle = fopAcM_searchPlayerAngleY(this);
            if ((s16)(playerAngle - shape_angle.y) > 0) {
                playerAngle = -0x800;
            }
            else {
                playerAngle = 0x800;
            }
        }
        else {
            playerAngle = 0;
        }
        setControllAngle(playerAngle);
    }
    return TRUE;
}

/* 00003C7C-00003CEC       .text procGetOff_init__8daShip_cFv */
BOOL daShip_c::procGetOff_init() {
    mCurMode = MODE_GET_OFF_FIRST_e;
    mProc = &daShip_c::procGetOff;
    if (m0392 != SHIP_BCK_FN_MAST_OFF2) {
        setPartOffAnime();
    }
    speedF = 0.0f;
    return TRUE;
}

/* 00003CEC-00003DEC       .text procGetOff__8daShip_cFv */
BOOL daShip_c::procGetOff() {
    if (mpBodyAnm->getFrame() >= 7.0f) {
        mPart = PART_WAIT_e;
        m03E8 = 1.0f;
    }
    if (mNextMode == MODE_GET_OFF_SECOND_e) {
        mCurMode = MODE_GET_OFF_SECOND_e;
    }
    if (mCurMode == MODE_GET_OFF_SECOND_e) {
        if (m036C > 0x800) {
            procWait_init();
        }
        else {
            setControllAngle(0x1000);
            cLib_addCalcAngleS(&m0366, 0, 2, 0x1000, 0x400);
        }
    }
    else {
        setControllAngle(0);
        cLib_addCalcAngleS(&m0366, 0, 2, 0x1000, 0x400);
        
        if (!daPy_getPlayerLinkActorClass()->checkShipGetOff()) {
            procWait_init();
        }
    }
    return TRUE;
}

/* 00003DEC-00003F00       .text procPaddleMove_init__8daShip_cFv */
BOOL daShip_c::procPaddleMove_init() {  
    offStateFlg(daSFLG_UNK4_e);
    
    mCurMode = MODE_PADDLE_MOVE_e;
    
    mProc = &daShip_c::procPaddleMove;

    if (m0392 != SHIP_BCK_FN_MAST_OFF2) {
        setPartOffAnime();
    }

    if (checkStateFlg(daSFLG_JUMP_RIDE_e) != 0) {
        offStateFlg(daSFLG_JUMP_RIDE_e);
        current.pos.y -= 50.0f;
    }
    
    dComIfGs_onEventBit(dSv_evtBit_c::RODE_KORL);
    
    if (dComIfGs_isEventBit(0xA80)) {
        dComIfGs_onEventBit(0x1980);
    }

    if (dComIfGs_isEventBit(0xA08)) {
        dComIfGs_onEventBit(0x2A02);
    }
    
    if (dComIfGs_isEventBit(0xA02)) {
        dComIfGs_onEventBit(0x2A01);
    }

    return TRUE;
}

/* 00003F00-00004004       .text procPaddleMove__8daShip_cFv */
BOOL daShip_c::procPaddleMove() {  
    if (checkNextMode(MODE_PADDLE_MOVE_e)) {
        return TRUE;
    }
    if (mpBodyAnm->getFrame() >= 7.0f) {
        mPart = PART_WAIT_e;
        m03E8 = 1.0f;
    }
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_BOW_AIM_e | daPyStts0_HOOKSHOT_AIM_e | daPyStts0_BOOMERANG_AIM_e | daPyStts0_TELESCOPE_LOOK_e | daPyStts0_BOOMERANG_WAIT_e) || dComIfGp_checkPlayerStatus1(0, daPyStts1_PICTO_BOX_AIM_e)) {
        cLib_addCalcAngleS(&m0366, 0, 4, l_HIO.tiller_speed, 0x100);
        if (!dComIfGp_event_runCheck()) {
            setMoveAngle(m0366);
        }
        firstDecrementShipSpeed(0.0f);
    }
    else {
        if (!dComIfGp_event_runCheck()) {
            setSelfMove(1);
        }
    }
    return TRUE;
}

/* 00004004-00004060       .text procSteerMove_init__8daShip_cFv */
BOOL daShip_c::procSteerMove_init() {
    offStateFlg(daSFLG_UNK4_e);
    mCurMode = MODE_STEER_MOVE_e;
    mProc = &daShip_c::procSteerMove;
    setPartAnimeInit(PART_STEER_e);
    return TRUE;
}

/* 00004060-0000451C       .text procSteerMove__8daShip_cFv */
BOOL daShip_c::procSteerMove() {
    if (checkNextMode(MODE_STEER_MOVE_e)) {
        return TRUE;
    }
    cLib_addCalcAngleS(&m0366, mStickMVal * 8192.0f * -cM_ssin(mStickMAng), 4, 700, 0x100);
    if (!checkStateFlg(daSFLG_FLY_e)) {
        setMoveAngle(m0366);
    }
    setSailAngle();
    if (m0392 == SHIP_BCK_FN_MAST_ON2 && mpBodyAnm->getFrame() >= 7.0f && mPart == PART_STEER_e) {
        onStateFlg(daSFLG_SAIL_ON_e);
    }
    if (!checkStateFlg(daSFLG_FLY_e)) {
        cXyz* windVec = dKyw_get_wind_vec();
        float windPower = *dKyw_get_wind_power() / 0.5f;
        int angleDiff = abs((s16)(cM_atan2s(windVec->x, windVec->z) - shape_angle.y));
        
        float windFactor;
        if (angleDiff < 0x4000) {
            windFactor = 1.0f - angleDiff * (1.0f / 0x10000);
        } else if (angleDiff <= 0x6000) {
            windFactor = 0.75f - (angleDiff - 0x4000) * 5.493164e-05f;
        } else {
            windFactor = 0.3f - (angleDiff - 0x6000) * 0.00032967035f;
            if (windFactor < 0.0f) {
                windFactor = 0.0f;
            }
        }
        
        if (windPower > 1.0f) {
            windPower = 1.0f;
        }
        windPower *= windFactor * 55.0f;
        
        if (mpBodyAnm->mFrameCtrl.checkPass(7.0f)) {
            float targetSpeed = windPower * 2.0f;
            if (targetSpeed > 80.0f) {
                targetSpeed = 80.0f;
            }
            if (speedF < targetSpeed) {
                speedF = targetSpeed;
                if (checkForceMove()) {
                    m03E0 = 10000.0f;
                } else {
                    m03E0 = windPower;
                }
            }
        } else {
            if (m03E0 < speedF) {
                firstDecrementShipSpeed(m03E0);
            } else {
                if (!checkStateFlg(daSFLG_SAIL_ON_e) || windPower <= 0.0f) {
                    decrementShipSpeed(mStickMVal * 10.0f * cM_scos(mStickMAng));
                } else if (speedF >= windPower) {
                    decrementShipSpeed(windPower);
                } else {
                    cLib_addCalc(&speedF, windPower, 0.1f, 0.5f, 0.1f);
                }
            }
        }
        if (!dComIfGp_event_runCheck() && 
            !daPy_getPlayerLinkActorClass()->checkNoControll() && 
            m0392 == SHIP_BCK_FN_MAST_ON2 && 
            mpBodyAnm->getFrame() >= 7.0f && 
            !checkStateFlg(daSFLG_FLY_e) && 
            mFwdVel > 16.5f) {
            if (!checkForceMove() && windPower >= 11.0f) {
                onStateFlg(daSFLG_JUMP_OK_e);
                if (mDoCPd_R_LOCK_TRIGGER(0)) {
                    onStateFlg((daSHIP_SFLG)(daSFLG_FLY_e | daSFLG_JUMP_e));
                    speed.y = windPower;
                    if (speed.y < 15.0f) {
                        speed.y = 15.0f;
                    } else if (speed.y > 40.0f) {
                        speed.y = 40.0f;
                    }
                    m0386 = 0;
                    current.angle.y = shape_angle.y;
                    mJumpRate = (speed.y - 11.0f) * 0.014545455f;
                    m036C >>= 1;
                }
            }
        }
    } else {
        setControllAngle(0);
        m036E = 0;
    }
    if (mPart != PART_STEER_e && mpBodyAnm->getPlaySpeed() < 0.01f) {
        setPartOnAnime(PART_STEER_e);
    }
    return TRUE;
}

/* 0000451C-00004580       .text procCannonReady_init__8daShip_cFv */
BOOL daShip_c::procCannonReady_init() {
    mCurMode = MODE_CANNON_e;
    mProc = &daShip_c::procCannonReady;
    setPartAnimeInit(PART_CANNON_e);
    m0394 = 0;
    return TRUE;
}

/* 00004580-00004634       .text procCannonReady__8daShip_cFv */
BOOL daShip_c::procCannonReady() {
    if (checkNextMode(MODE_CANNON_e)) {
        return TRUE;
    }
    cLib_addCalcAngleS(&m0366, 0, 2, 0x1000, 0x400);
    setMoveAngle(m0366);
    firstDecrementShipSpeed(0.0f);
    if (mpBodyAnm->getPlaySpeed() < 0.01f) {
        if (mPart != PART_CANNON_e) {
            setPartOnAnime(PART_CANNON_e);
        }
        else {
            procCannon_init();
        }
    }
    return TRUE;
}

/* 00004634-0000467C       .text procCannon_init__8daShip_cFv */
BOOL daShip_c::procCannon_init() {  
    mProc = &daShip_c::procCannon;
    m0366 = 0;
    speedF = 0.0f;
    m03A6 = 0;
    m03A8 = 0;
    m037A = 0;
    return TRUE;
}

/* 0000467C-00004B08       .text procCannon__8daShip_cFv */
BOOL daShip_c::procCannon() {
    BOOL bVar1;
    fopAc_ac_c* target;
    cXyz cannonPos;
    
    if (checkNextMode(MODE_CANNON_e)) {
        return TRUE;
    }
    setControllAngle(0); 
    if (!dComIfGp_event_runCheck() && !daPy_getPlayerLinkActorClass()->checkNoControll()) {
        dAttention_c& attention = dComIfGp_getAttention();
        if (attention.Lockon() && attention.GetLockonList(0) && attention.LockonTruth()) {
            target = attention.GetLockonList(0)->getActor();
        }
        else {
            target = NULL;
        }
        
        short prev0396 = m0396;
        short prev0394 = m0394;
        
        if (target) {
            mDoMtx_multVecZero(mpCannonModel->getAnmMtx(2), &cannonPos);

            cannonPos = target->eyePos - cannonPos;

            cLib_addCalcAngleS(&m0396, cM_atan2s(-cannonPos.y, cannonPos.absXZ()) + 0x4000, 5, 0x180, 0x40);
            cLib_addCalcAngleS(&m0394, cM_atan2s(cannonPos.x, cannonPos.z) - shape_angle.y, 5, 0x180, 0x40);
        
        } else if (!mDoCPd_R_LOCK_BUTTON(0)) {
            float adjust = mStickMVal * (m0404 * 4.0f + 1.0f);
            m0396 += (adjust * 384.0f) * cM_scos(mStickMAng);
            m0394 += (s16)((adjust * 384.0f) * cM_ssin(mStickMAng));
        }
        
        if (m0396 > 0x4000) {
            m0396 = 0x4000;
        } else if (m0396 < 0x1556) {
            m0396 = 0x1556;
        }
        
        if (cLib_distanceAngleS(prev0396, m0396) >= 0x80 || cLib_distanceAngleS(prev0394, m0394) >= 0x80) {
            bVar1 = TRUE;
        } else {
            bVar1 = FALSE;
        }
        if (bVar1) {
            seStart(JA_SE_LK_SHIP_CANNON_MOVE, &m1038);
        }
        
        if (m037A == 0 && 
            ((CPad_CHECK_TRIG_X(0) && dComIfGp_getSelectItem(0) == dItem_BOMB_BAG_e) ||
             (CPad_CHECK_TRIG_Y(0) && dComIfGp_getSelectItem(1) == dItem_BOMB_BAG_e) ||
             (CPad_CHECK_TRIG_Z(0) && dComIfGp_getSelectItem(2) == dItem_BOMB_BAG_e))) {
            m037A = 30;
            if (dComIfGs_getBombNum() == 0) {
                mDoAud_seStart(JA_SE_ITEM_TARGET_OUT);
                m037A--;
            }
        } else if (m037A > 0) {
            m037A--;
        }
        
        if (mDoCPd_R_LOCK_BUTTON(0)) {
            setSelfMove(1);
        } else {
            setSelfMove(0);
        }
    }
    return TRUE;
}


/* 00004B08-00004B7C       .text procCraneReady_init__8daShip_cFv */
BOOL daShip_c::procCraneReady_init() {  
    mCurMode = MODE_CRANE_e;
    mProc = &daShip_c::procCraneReady;
    mCraneBaseAngle = 0x3000;
    m039C = 0;
    setPartAnimeInit(PART_CRANE_e);
    mRopeCnt = 0;
    return TRUE;
}

/* 00004B7C-00004CD0       .text procCraneReady__8daShip_cFv */
BOOL daShip_c::procCraneReady() {
    float fVar1;
    
    if (checkNextMode(MODE_CRANE_e)) {
        return TRUE;
    }
    cLib_addCalcAngleS(&m0366, 0, 2, 0x1000, 0x400);
    setMoveAngle(m0366);
    firstDecrementShipSpeed(0.0f);
    if (mpBodyAnm->getPlaySpeed() < 0.01f) {
        if (mPart != PART_CRANE_e) {
            setPartOnAnime(PART_CRANE_e);
        }
        else {
            incRopeCnt(2, 0);
            if (mRopeCnt == 20) {
                procCrane_init();
            }
        }
    }
    if (mPart == PART_CRANE_e) {
        fVar1 = (mpBodyAnm->getFrame() - 5.0f) * 0.33333334f;
        if (fVar1 > 1.0f) {
            fVar1 = 1.0f;
        } 
        else if (fVar1 < 0.0f) {
            fVar1 = 0.0f;
        }
        m0398 = fVar1 * mCraneBaseAngle;
    }
    return TRUE;
}

/* 00004CD0-00004D70       .text procCrane_init__8daShip_cFv */
BOOL daShip_c::procCrane_init() {
    mProc = &daShip_c::procCrane;
    speedF = 0.0f;
    m0366 = 0;
    mRipple.setRate(0.0f);
    offStateFlg(daSFLG_UNK800_e);
    mCurMode = MODE_CRANE_e;
    if (cM_rnd() < 0.5f) {
        m0353 = 1;
    }
    else {
        m0353 = 0;
    }
    return TRUE;
}

/* 00004D70-000050C4       .text procCrane__8daShip_cFv */
BOOL daShip_c::procCrane() {
    s16 sVar3;
    s16 sVar1;
    s16 sVar2;

    if (checkNextMode(MODE_CRANE_e)) {
        offStateFlg(daSFLG_UNK800_e);
        return TRUE;
    }
    setControllAngle(0);
    if (!dComIfGp_event_runCheck() && !daPy_getPlayerLinkActorClass()->checkNoControll()) {
        if (m0398 == mCraneBaseAngle) {
            if(std::fabsf(speedF) < 3.0f &&
              ((CPad_CHECK_HOLD_X(0) && dComIfGp_getSelectItem(0) == dItem_GRAPPLING_HOOK_e) ||
               (CPad_CHECK_HOLD_Y(0) && dComIfGp_getSelectItem(1) == dItem_GRAPPLING_HOOK_e) ||
               (CPad_CHECK_HOLD_Z(0) && dComIfGp_getSelectItem(2) == dItem_GRAPPLING_HOOK_e))) {
                sVar1 = mRopeCnt;
                incRopeCnt(2, 0);
                if (mRopeCnt == 250) {
                    sVar3 = 0;
                    if (mCraneBaseAngle > 0) {
                        setControllAngle(0xA00);
                    }
                    else {
                        setControllAngle(-0xA00);
                    }
                    if (m0353 && (sVar1 != mRopeCnt)) {
                        dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
                    }
                }
                else if (mCraneBaseAngle > 0) {
                    sVar3 = 0x800;
                }
                else {
                    sVar3 = -0x800;
                }
            }
            else {
                incRopeCnt(-2, 20);
                if (mRopeCnt == 20) {
                    sVar3 = 0;
                }
                else if (mCraneBaseAngle > 0) {
                    sVar3 = -0x800;
                }
                else {
                    sVar3 = 0x800;
                }
            }
            cLib_chaseAngleS(&m039C, sVar3, 0x100);
            if (mRopeCnt == 20 && !mDoCPd_R_LOCK_BUTTON(0) && mStickMVal > 0.1f) {
                sVar2 = mCraneBaseAngle;
                if ((mStickMAng < -0x2000) && (mStickMAng > -0x6000)) {
                    mCraneBaseAngle = 0x3000;
                    m03A6 = 0;
                    onStateFlg(daSFLG_UNK10000000_e);
                }
                else if ((mStickMAng > 0x2000) && (mStickMAng < 0x6000)) {
                    mCraneBaseAngle = -0x3000;
                    m03A6 = 0;
                    onStateFlg(daSFLG_UNK10000000_e);
                }
                if (sVar2 * mCraneBaseAngle < 0) {
                    seStart(JA_SE_LK_SHIP_CRANE_ARM, &m102C);
                }
            }
        }
        else {
            cLib_chaseAngleS(&m03A6, 0x1800, 0x100);
            cLib_addCalcAngleS(&m0398, mCraneBaseAngle, 5, m03A6, 0x100);
        }
        if (mDoCPd_R_LOCK_BUTTON(0) && mRopeCnt == 20) {
            setSelfMove(1);
            if (cM_rnd() < 0.5f) {
                m0353 = 1;
            }
            else {
                m0353 = 0;
            }
        }
        else {
            setSelfMove(0);
        }
    }
    return TRUE;
}

/* 000050C4-000051F8       .text procCraneUp_init__8daShip_cFv */
BOOL daShip_c::procCraneUp_init() {    
    if (mProc == &daShip_c::procCraneUp) {
        return FALSE;
    }

    mProc = &daShip_c::procCraneUp;

    if (mCraneBaseAngle > 0) {
        m03A6 = 0x800;
    }
    else {
        m03A6 = -0x800;
    }

    seStart(JA_SE_LK_SHIP_CRANE_SALVAGE, &current.pos);

    mCurMode = MODE_CRANE_UP_e;

    mRipple.setRate(1.0f);

    offStateFlg(daSFLG_UNK40000_e);

    dComIfGp_getVibration().StartShock(7, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    dComIfGp_getVibration().StartQuake(4, 1, cXyz(0.0f, 1.0f, 0.0f));

    speedF = 0.0f;
    return TRUE;
}

/* 000051F8-000053F0       .text procCraneUp__8daShip_cFv */
BOOL daShip_c::procCraneUp() {
    short sVar1;
    
    if (mCraneBaseAngle > 0) {
        sVar1 = 0x800;
    }
    else {
        sVar1 = -0x800;
    }
    cLib_addCalcAngleS(&m039C, sVar1, 5, 0x1800, 0x100);
    if (mRipple.getEmitter() == NULL) {
        setControllAngle(0);
        onStateFlg(daSFLG_UNK40000_e);
        dComIfGp_getVibration().StopQuake(-1);
    }
    else {
        setControllAngle(m03A6);
        if (cLib_distanceAngleS(m036C, m03A6) < 0x400) {
            if (mCraneBaseAngle > 0) {
                if (m03A6 > 0x400) {
                    m03A6 = cM_rnd() * 256.0f;
                }
                else {
                    m03A6 = cM_rnd() * 1024.0f + 2048.0f;
                    seStart(JA_SE_LK_SHIP_CRANE_SALVAGE, &current.pos);
                }
            }
            else {
                if (m03A6 < -0x400) {
                    m03A6 = cM_rnd() * -256.0f;
                }
                else {
                    m03A6 = -2048.0f - cM_rnd() * 1024.0f;
                    seStart(JA_SE_LK_SHIP_CRANE_SALVAGE, &current.pos);
                }
            }
        }
    }
    incRopeCnt(-1, 20);
    if (mRopeCnt == 20) {
        if (dComIfGp_event_runCheck()) {
            if (daPy_getPlayerLinkActorClass()->getBaseAnimeFrameRate() < 0.01f) {
                dComIfGp_evmng_cutEnd(mEvtStaffId);
            }
        }
        else {
            procCrane_init();
        }
    }
    return TRUE;
}

/* 000053F0-0000542C       .text procToolDemo_init__8daShip_cFv */
BOOL daShip_c::procToolDemo_init() {
    mProc = &daShip_c::procToolDemo;
    mCurMode = 7;
    offStateFlg(daSFLG_FLY_e);
    return TRUE;
}

/* 0000542C-00005530       .text procToolDemo__8daShip_cFv */
BOOL daShip_c::procToolDemo() {
    dDemo_actor_c* demoActor = dComIfGp_demo_getActor(demoActorID);
    if (demoActor) {
        if (demoActor->checkEnable(dDemo_actor_c::ENABLE_TRANS_e)) {
            current.pos.x = demoActor->getTrans()->x;
            current.pos.z = demoActor->getTrans()->z;
        }
        if (demoActor->checkEnable(dDemo_actor_c::ENABLE_ROTATE_e)) {
            csXyz demoRot = *demoActor->getRatate();
            short prevShapeAngleY = shape_angle.y;
            shape_angle.y = demoRot.y;
            current.angle.y = shape_angle.y;
            short angleDiff = shape_angle.y - prevShapeAngleY;
            if (angleDiff > 0) {
                angleDiff = 0x2000;
            }
            else if (angleDiff < 0) {
                angleDiff = -0x2000;
            }
            else {
                angleDiff = 0;
            }
            cLib_addCalcAngleS(&m0366, angleDiff, 4, 700, 0x100);
            setControllAngle(getAimControllAngle(prevShapeAngleY));
        }
    }
    else {
        changeDemoEndProc();
    }
    return TRUE;
}

/* 00005530-00005574       .text procZevDemo_init__8daShip_cFv */
BOOL daShip_c::procZevDemo_init() {
    mProc = &daShip_c::procZevDemo;
    mCurMode = 7;
    offStateFlg(daSFLG_FLY_e);
    m0350 = 4;
    return TRUE;
}

/* 00005574-00006310       .text procZevDemo__8daShip_cFv */
BOOL daShip_c::procZevDemo() {
    float fVar3;
    short sVar5; 
    short sVar15;
    float fVar17;
    cXyz local_7c;
    cXyz local_70;
    cXyz local_64;
    
    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && m0392 != SHIP_BCK_FN_MAST_OFF2) {
        setPartOffAnime();
    }
    if (mEvtStaffId != -1) {
        cXyz* posP = dComIfGp_evmng_getMyXyzP(mEvtStaffId, "pos");
        int* angleP = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "angle");
        f32* speedP = dComIfGp_evmng_getMyFloatP(mEvtStaffId, "speed");
        int* partP = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "part");
        int* talkP = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "talk");
        int* atn_actorP = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "atn_actor");

        if (atn_actorP && dComIfGp_event_getPt1()) {
            m0428 = &dComIfGp_event_getPt1()->eyePos;
        }
        else {
            m0428 = dComIfGp_evmng_getMyXyzP(mEvtStaffId, "atn_pos");
        }

        if (m0351 && partP && (m0350 == 4 || m0350 != *partP)) {
            m0350 = *partP;
            setPartAnimeInit(*partP);
        }

        if (talkP && *talkP == 1) { 
            if (!checkStateFlg(daSFLG_UNK8000_e)) {
                m038A = SHIP_BCK_FN_TALK_A;
                mAnmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, m038A);
                mFrameCtrl.init(mAnmTransform->getFrameMax());
                onStateFlg(daSFLG_UNK8000_e);
            }
        }
        else {
            offStateFlg(daSFLG_UNK8000_e);
        }

        if (dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "tact")) {
            daPy_getPlayerLinkActorClass()->onNoResetFlg1(daPy_py_c::daPyFlg1_SHIP_TACT);
        }
        else {
            daPy_getPlayerLinkActorClass()->offNoResetFlg1(daPy_py_c::daPyFlg1_SHIP_TACT);
        }

        if (m0351 == 0 || m0351 == 8) {
            if (angleP) {
                sVar15 = (s16)*angleP;
            }
            else {
                sVar15 = shape_angle.y;
            }

            if (posP) {
                initStartPos(posP, sVar15);
            }
            else {
                initStartPos(&current.pos, sVar15);
            }

            if (speedP) {
                speedF = *speedP;
            }

            if (partP || m0351 == 8) {
                if (m0351 == 8) {
                    m0350 = 0;
                }
                else {
                    m0350 = *partP;
                }

                mPart = m0350;
                mRopeCnt = 0;

                u16 fileIndex;
                if (mPart != PART_WAIT_e) {
                    fileIndex = SHIP_BCK_FN_MAST_ON2;
                }
                else {
                    fileIndex = SHIP_BCK_FN_MAST_OFF2;
                    m03E8 = 0.001f;
                }
                if (m0392 != fileIndex) {
                    mpBodyAnm->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, fileIndex), J3DFrameCtrl::EMode_NONE, 0.0f, 1.0f, 0.0f, -1.0f, NULL);
                    m0392 = fileIndex;
                    mpBodyAnm->setFrame(mpBodyAnm->getEndFrame() - 0.001f);
                    mpBodyAnm->getAnm()->setFrame(mpBodyAnm->getEndFrame() - 0.001f);
                    mpBodyAnm->play(NULL, 0, 0);
                }
            }
            setControllAngle(0);
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
        else if (m0351 == 1 || m0351 == 3) {
            if (posP == NULL) {
                posP = dComIfGp_evmng_getGoal();
            }
            
            if (m0351 == 1) {
                local_7c = *posP - current.pos;
            }
            else {
                local_70 = current.pos - *posP;

                fVar17 = local_70.absXZ();

                if (!dComIfGp_evmng_getMyFloatP(mEvtStaffId, "rad")) {
                    JUT_ASSERT(0xE9D, 0);
                }

                fVar3 = *dComIfGp_evmng_getMyFloatP(mEvtStaffId, "rad");

                if (fVar17 < 0.1f) {
                    sVar15 = 0x4000;
                    local_64.set(posP->x, posP->y, posP->z + fVar3);
                }
                else {
                    sVar15 = (s16)(cM_atan2s(local_70.x, local_70.z) + 0x4000);
                    local_64 = *posP + local_70 * (fVar3 / fVar17);
                }

                local_64.x += fVar3 * cM_ssin(sVar15);
                local_64.z += fVar3 * cM_scos(sVar15);
                local_7c = local_64 - current.pos;
            }

            fVar17 = local_7c.absXZ();

            if (fVar17 < 10.0f) {
                speedF = 0.0f;
                dComIfGp_evmng_cutEnd(mEvtStaffId);
            }
            else {
                if (speedP && *speedP <= -0.5f) {
                    if (m03E0 <= speedF) {
                        firstDecrementShipSpeed(m03E0);
                    }
                    else {
                        if (*speedP < -1.5f) {
                            cLib_addCalc(&speedF, 0.0f, 0.1f, 1.0f, 0.1f);
                        }
                        else { 
                            decrementShipSpeed(0.0f);
                        }
                    }
                }
                else {
                    speedF = fVar17 * 0.2f;
                    if (speedP) {
                        fVar3 = *speedP;
                    }
                    else {
                        fVar3 = 55.0f;
                    }
                    if (speedF > fVar3) {
                        speedF = fVar3;
                    }
                }
            }
            if (fVar17 > 1.0f) {
                sVar15 = shape_angle.y;
                cLib_addCalcAngleS(&shape_angle.y, cM_atan2s(local_7c.x, local_7c.z), 3, 0x2000, 0x80);
                current.angle.y = shape_angle.y;
                
                sVar5 = shape_angle.y - sVar15;
                if (sVar5 > 0) {
                    sVar5 = 0x2000;
                }
                else if (sVar5 < 0) {
                    sVar5 = -0x2000;
                }
                else {
                    sVar5 = 0;
                }

                cLib_addCalcAngleS(&m0366, sVar5, 4, 700, 0x100);
                setControllAngle(getAimControllAngle(sVar15));
            }
            else {
                setControllAngle(0);
            }
        }
        else if (m0351 == 4) {
            if (!checkStateFlg(daSFLG_UNK10000_e)) {
                mpHeadAnm->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, SHIP_BCK_FN_LOSE1), J3DFrameCtrl::EMode_NONE, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
                onStateFlg(daSFLG_UNK10000_e);
                m03B4 = SHIP_BCK_FN_LOSE1;
            }

            speedF = 0.0f;
            setControllAngle(0);

            if (mpHeadAnm->getPlaySpeed() < 0.01f) {
                dComIfGp_evmng_cutEnd(mEvtStaffId);
            }
        }
        else if (m0351 == 5) {
            if (speedP) {
                firstDecrementShipSpeed(*speedP);
            }
            setControllAngle(0);
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
        else if (m0351 == 6) {
            partP = dComIfGp_evmng_getMyIntegerP(mEvtStaffId, "prm0");

            u16 fileIndex;
            if (partP == NULL || !(*partP & 1)) {
                fileIndex = SHIP_BCK_FN_LOOK_R;
            }
            else {
                fileIndex = SHIP_BCK_FN_LOOK_L;
            }

            if (partP && (s32)*partP == 2) {
                fVar17 = -1.0f;
            }
            else {
                fVar17 = 1.0f;
            }

            if (!checkStateFlg(daSFLG_UNK80000_e) && fVar17 > 0.0f) {
                mpHeadAnm->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, fileIndex), J3DFrameCtrl::EMode_NONE, 5.0f, fVar17, 0.0f, -1.0f, NULL);
                m03B4 = fileIndex;
                onStateFlg(daSFLG_UNK80000_e);
            }
            else if (checkStateFlg(daSFLG_UNK80000_e) && fVar17 < 0.0f) {
                offStateFlg(daSFLG_UNK80000_e);
                mpHeadAnm->setPlaySpeed(-1.0f);
            }

            setControllAngle(0);

            if (std::fabsf(mpHeadAnm->getPlaySpeed()) <= 0.1f) {
                dComIfGp_evmng_cutEnd(mEvtStaffId);
            }
        }
        else if (m0351 == 7) {
            speedF = 150.0f;
            speedP = dComIfGp_evmng_getMyFloatP(mEvtStaffId, "gravity");
            if (speedP) {
                gravity = *speedP;
            }
            
            speed.y = 50.0f;
            onStateFlg(daSFLG_FLY_e);

            if (angleP) {
                current.angle.y = (s16)*angleP;
            }

            shape_angle.y += 4500;
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
        else if (m0351 == 10) {
            cLib_addCalcAngleS(&m0370, 0, 10, 0x1000, 0x200);
            cLib_addCalcAngleS(&m0372, 0, 10, 0x1000, 0x200);
            cLib_addCalcAngleS(&m0384, 0, 10, 0x1000, 0x200);
            cLib_addCalcAngleS(&m036C, 0, 10, 0x1000, 0x200);

            onStateFlg(daSFLG_FLY_e);
            if (speed.y < 15.0f) {
                speed.y += 1.0f;
            }
            
            m0366 = 0;
            m036E = 0;
            m0374 = 0;
            m0376 = 0;
            m0386 = 0;
            gravity = 0.0f;
            speedF = 0.0f;
            current.pos.y += speed.y;
            dComIfGp_evmng_cutEnd(mEvtStaffId);
        }
        else {
            if (m0351 == 11) {
                if (m03F4 > current.pos.y && gravity >= 0.0f) {
                    offStateFlg(daSFLG_FLY_e);
                    m03F4 = current.pos.y;
                    dComIfGp_evmng_cutEnd(mEvtStaffId);
                }
                else {
                    m0370 = 0;
                    m0372 = 0;
                    m0384 = 0;
                    m036C = 0;
                    m0366 = 0;
                    m036E = 0;
                    m0374 = 0;
                    m0376 = 0;
                    m0386 = 0;
                    onStateFlg(daSFLG_FLY_e);
                    if (gravity < 0.0f) {
                        gravity = 0.0f;
                        current.pos.y += 500.0f;
                        speed.y = 0.0f;
                    }
                    else {
                        speed.y -= 1.0f;
                        if (speed.y < -15.0f) {
                            speed.y = -15.0f;
                        }
                    }
                }
            }
            else {
                return TRUE;
            }
        }
        if (mpBodyAnm->getPlaySpeed() < 0.01f) {
            if (m0350 != 4 && m0350 != 0 && mPart != m0350) {
                setPartOnAnime(m0350);
            }
        }
    }
    else {
        changeDemoEndProc();
    }
    return TRUE;
}

/* 00006310-00006440       .text procTalkReady_init__8daShip_cFv */
BOOL daShip_c::procTalkReady_init() {
    J3DAnmTransform* pAnimRes;
    
    mProc = &daShip_c::procTalkReady;
    mAnmTransform = NULL;
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        if ((s16)(shape_angle.y - m038C) > 0) {
            m03B4 = SHIP_BCK_FN_LOOK_R;
        }
        else {
            m03B4 = SHIP_BCK_FN_LOOK_L;
        }
    }
    else if ((s16)(fopAcM_searchPlayerAngleY(this) - shape_angle.y) > 0) {
        m03B4 = SHIP_BCK_FN_LOOK_L;
    }
    else {
        m03B4 = SHIP_BCK_FN_LOOK_R;
    }
    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, m03B4);
    mpHeadAnm->setAnm(pAnimRes, 0, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
    seStart(JA_SE_SHIP_LOOK_BACK, &eyePos);
    mCurMode = MODE_TALK_e;
    return TRUE;
}

/* 00006440-000064A8       .text procTalkReady__8daShip_cFv */
BOOL daShip_c::procTalkReady() {
    firstDecrementShipSpeed(0.0f);
    setMoveAngle(0);
    if (mpHeadAnm->getPlaySpeed() <= 0.1f) {
        procTalk_init();
    }
    return TRUE;
}

/* 000064A8-00006558       .text procTalk_init__8daShip_cFv */
BOOL daShip_c::procTalk_init() {
    mProc = &daShip_c::procTalk;
    mCurMode = MODE_TALK_e;
    m0430 = fpcM_ERROR_PROCESS_ID_e;
    m038A = SHIP_BCK_FN_TALK_A;
    mAnmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, m038A);
    mFrameCtrl.init(mAnmTransform->getFrameMax());
    setInitMessage();
    onStateFlg(daSFLG_UNK8000_e);
    return TRUE;
}

/* 00006558-00006720       .text procTalk__8daShip_cFv */
BOOL daShip_c::procTalk() {
    msg_class *msg;
    u16 fileIndex;
    
    firstDecrementShipSpeed(0.0f);
    setMoveAngle(0);
    if (m0430 == fpcM_ERROR_PROCESS_ID_e) {
        if (dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4)) {
            m0430 = fopMsgM_messageSet(mNextMessageNo, &eyePos);
        }
    }
    else {
        msg = fopMsgM_SearchByID(m0430);
        if (msg) {
            if (msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                if (setNextMessage(msg)) {
                    msg->mStatus = fopMsgStts_MSG_ENDS_e;
                }
                else {
                    msg->mStatus = fopMsgStts_MSG_CONTINUES_e;
                    fopMsgM_messageSet(mNextMessageNo);
                }
            } else if (msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
                msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && checkStateFlg(daSFLG_UNK400000_e)){
                    return procTurn_init();
                }
                mpHeadAnm->setPlaySpeed(-1.0f);
                dComIfGp_event_onEventFlag(8);
                changeDemoEndProc();
                return TRUE;
            }
        }
    }
    if (mFrameCtrl.checkState(2)) {
        if (cM_rndF(2.0f) < 1.0f) {
            fileIndex = SHIP_BCK_FN_TALK_A;
        }
        else {
            fileIndex = SHIP_BCK_FN_TALK_B;
        }
        if (fileIndex != m038A) {
            m038A = fileIndex;
            mAnmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, m038A);
            mFrameCtrl.init(mAnmTransform->getFrameMax());
        }
    }
    return TRUE;
}

/* 00006720-0000686C       .text procTurn_init__8daShip_cFv */
BOOL daShip_c::procTurn_init() {
    m0430 = fpcM_ERROR_PROCESS_ID_e;
    mpHeadAnm->setPlaySpeed(-1.0f);
    seStart(JA_SE_SHIP_LOOK_FORWARD, &eyePos);
    mProc = &daShip_c::procTurn;
    m038E = 0;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz cameraPos = camera->mCamera.Eye() - camera->mCamera.Center();
    cameraPos.normalize();
    m0450 = camera->mCamera.Center() + (cameraPos * 1600.0f);
    offStateFlg(daSFLG_UNK8000_e);
    m037A = 10;
    return TRUE;
}

/* 0000686C-00006C78       .text procTurn__8daShip_cFv */
BOOL daShip_c::procTurn() {
    float fVar2;
    short sVar4;
    float fVar5;
    float fVar6;
    cXyz local_c4;
    cXyz local_b8;
    cXyz local_ac;
    
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    local_c4 = current.pos - camera->mCamera.Center();
    fVar5 = local_c4.abs();
    local_ac = camera->mCamera.Center() + (current.pos - m045C);
    local_c4 = m0450 - camera->mCamera.Eye();
    fVar6 = local_c4.abs(); 
    if (fVar6 > 1.0f) {
        fVar2 = fVar6 * 0.5f;
        if (fVar2 > 60.0f) {
            fVar2 = 60.0f;
        }
        else if (fVar2 < 15.0f) {
            if (fVar6 > 15.0f) {
                fVar2 = 15.0f;
            }
            else {
                fVar2 = fVar6;
            }
        }
        local_b8 = camera->mCamera.Eye() + local_c4.normalize() * fVar2;
    }
    else {
        local_b8 = m0450;
    }
    camera->mCamera.Set(local_ac, local_b8);
    if (fVar6 <= 1.0f) {
        sVar4 = shape_angle.y;
        cLib_addCalcAngleS2(&shape_angle.y, m038C, 8, m038E);
        cLib_addCalcAngleS2(&m038E, 0x800, 8, 0x80);
        current.angle.y = shape_angle.y;
        setControllAngle(getAimControllAngle(sVar4));
        if (abs((s16)(shape_angle.y - m038C)) < 0x200) {
            cLib_addCalc(&speedF, 55.0f, 0.1, 5.0f, 1.0f);
        }
        if (abs((s16)(m038C - shape_angle.y)) < 0x100 && !checkOutRange()) {
            if (m037A <= 0) {
                camera->mCamera.Start();
                camera->mCamera.Reset();
                dComIfGp_event_onEventFlag(8);
                changeDemoEndProc();
                m038E = 0;
                onStateFlg(daSFLG_UNK100000_e);
            }
            else {
                m037A--;
            }
        }
    }
    return TRUE;
}

/* 00006C78-00006DE0       .text procTornadoUp_init__8daShip_cFv */
BOOL daShip_c::procTornadoUp_init() {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    onStateFlg((daSHIP_SFLG)(daSFLG_FLY_e | daSFLG_UNK1000_e));
    mCurMode = 12;
    mProc = &daShip_c::procTornadoUp;
    m037A = 1;
    camera->mCamera.Stop();
    speed.y = 0.0f;
    gravity = 0.0f;
    cXyz tornadoPos(mTornadoActor->current.pos.x, mTornadoActor->current.pos.y + 2500.0f, mTornadoActor->current.pos.z + 4000.0f);
    camera->mCamera.Set(current.pos, tornadoPos);
    m03A6 = 0;
    fopAcM_seStartCurrent(mTornadoActor, 0x186C, 0);
    dComIfGs_onEventBit(0x3E40);
    return TRUE;
}

/* 00006DE0-00006FDC       .text procTornadoUp__8daShip_cFv */
BOOL daShip_c::procTornadoUp() {
    int iVar1;
    daTornado_c* tornadoActor = mTornadoActor;
    
    cLib_addCalc(&current.pos.x, tornadoActor->getJointXPos(m037A), 0.5f, 80.0f, 20.0f);
    
    cLib_addCalc(&current.pos.z, tornadoActor->getJointZPos(m037A), 0.5f, 80.0f, 20.0f);

    current.pos.y += speed.y;
    speed.y += 2.0f;
    
    if (speed.y > 50.0f) {
        speed.y = 50.0f;
    }

    if (tornadoActor->getJointYPos(m037A) < current.pos.y && m037A < 11) {
        m037A++;
    }

    shape_angle.y += 0x1C25;

    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cXyz local_3c(tornadoActor->current.pos.x, current.pos.y, tornadoActor->current.pos.z);
    camera->mCamera.Set(local_3c, camera->mCamera.Eye());
    
    if (m03A6 == 0 && current.pos.y > tornadoActor->current.pos.y + 5000.0f) {
        m03A6 = 1;
        iVar1 = (s32)cM_rndF(8.0f) + 0xC6;
        if (iVar1 >= 0xCE) {
            iVar1 = 0xCD;
        }
        dStage_changeScene(iVar1, 0.0f, 0, 0xFF);
    }
    
    return TRUE;
}

/* 00006FDC-0000713C       .text procStartModeWarp_init__8daShip_cFv */
BOOL daShip_c::procStartModeWarp_init() {
    current.pos.y = m03F4 + 5000.0f;
    onStateFlg(daSFLG_FLY_e);
    mProc = &daShip_c::procStartModeWarp;
    mCurMode = MODE_START_MODE_WARP_e;
    if (m0392 != SHIP_BCK_FN_MAST_OFF2) {
        setPartOffAnime();
    }
    m03A6 = 0x1C25;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz local_38(current.pos.x, m03F4 + 1500.0f, current.pos.z + 2000.0f);
    camera->mCamera.Set(current.pos, local_38);
    m037A = 0;
    fopAcM_seStartCurrent(this, 0x186D, 0);
    return TRUE;
}

/* 0000713C-000074D4       .text procStartModeWarp__8daShip_cFv */
BOOL daShip_c::procStartModeWarp() {
    int iVar5;
    GXColor diff;
    GXColor amb;
    cXyz local_30;
    
    daTornado_c* pfVar2 = (daTornado_c*)fopAcM_SearchByID(mTactWarpID);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    shape_angle.y += m03A6;
    current.angle.y = shape_angle.y;
    if (pfVar2) {
        if (!checkStateFlg(daSFLG_UNK8_e)) {
            onStateFlg(daSFLG_UNK8_e);
            pfVar2->current.pos.x = current.pos.x;
            pfVar2->current.pos.z = current.pos.z;
        }
        iVar5 = 0;
        for (int i = 0; i < 11; iVar5++, i++) {
            if (current.pos.y < pfVar2->getJointYPos(i)) break;
        }
        if (iVar5 == 11) {
          iVar5 = 10;
        }
        cLib_chaseF(&current.pos.x, pfVar2->getJointXPos(iVar5), 50.0f);
        cLib_chaseF(&current.pos.z, pfVar2->getJointZPos(iVar5), 50.0f);
        local_30.x = pfVar2->current.pos.x;
        local_30.z = pfVar2->current.pos.z;
    }
    else {
        local_30.x = current.pos.x;
        local_30.z = current.pos.z;
    }
    local_30.y = current.pos.y;
    camera->mCamera.Set(local_30, camera->mCamera.Eye());
    if (m037A == 0) {
        if (current.pos.y < m03F4) {
            current.pos.y = m03F4 - 50.0f;
            speed.y = 0.0f;
            offStateFlg(daSFLG_FLY_e);
            m037A = 1;
            if (pfVar2 != NULL) {
                pfVar2->m31c = 1;
            }
            dKy_get_seacolor(&diff, &amb);
            m03BC.x = 0;
            m03BC.y = shape_angle.y + 0x8000;
            m03BC.z = 0;
            dComIfGp_particle_set(dPa_name::ID_COMMON_0285, &current.pos, &shape_angle, NULL, 0xFF, &m1984, -1, &diff);
            dComIfGp_particle_set(dPa_name::ID_COMMON_0285, &current.pos, &m03BC, NULL, 0xFF, &m1998, -1, &diff);
        }
        if (pfVar2 != NULL) {
            pfVar2->current.pos.y = current.pos.y - 700.0f;
        }
    }
    else if (pfVar2 == NULL || pfVar2->mJointScale[10] < 0.8f) {
        if (pfVar2 != NULL) {
            pfVar2->current.pos.y -= 12.0f;
        }
        m03BC.y = shape_angle.y + 0x8000;
        cLib_chaseS(&m03A6, 0, 0x40);
        if (m03A6 < 0x400) {
            camera->mCamera.Start();
            camera->mCamera.Reset();
            mTactWarpID = fpcM_ERROR_PROCESS_ID_e;
            m1984.remove();
            m1998.remove();
            dComIfGp_evmng_cutEnd(mEvtStaffId);
            procPaddleMove_init();
        }
    }
    return TRUE;
}

/* 000074D4-00007684       .text procTactWarp_init__8daShip_cFv */
BOOL daShip_c::procTactWarp_init() {
    GXColor diff;
    GXColor amb[3];
    
    mCurMode = MODE_TACT_WARP_e;
    mProc = &daShip_c::procTactWarp;
    if (m0392 != SHIP_BCK_FN_MAST_OFF2) {
        setPartOffAnime();
    }
    m03A6 = 0;
    gravity = 0.0f;
    speed.y = 0.0f;
    onStateFlg(daSFLG_FLY_e);
    m037A = 0;
    fopAcM_seStartCurrent(this, 0x186E, 0);
    dCam_getBody()->StartEventCamera(0xe, fopAcM_GetID(this), 0);
    dKy_get_seacolor(amb, &diff);
    m03BC.x = 0;
    m03BC.y = shape_angle.y + 0x8000;
    m03BC.z = 0;
    dComIfGp_particle_set(dPa_name::ID_COMMON_0285, &current.pos, &shape_angle, NULL, 0xFF, &m1984, -1, amb);
    dComIfGp_particle_set(dPa_name::ID_COMMON_0285, &current.pos, &m03BC, NULL, 0xFF, &m1998, -1, amb);
    return TRUE;
}

/* 00007684-0000797C       .text procTactWarp__8daShip_cFv */
BOOL daShip_c::procTactWarp() {
    BOOL res;
    int iVar4;
    
    shape_angle.y += m03A6;
    current.angle.y = shape_angle.y;
    daTornado_c* mpTornado = (daTornado_c*)fopAcM_SearchByID(mTactWarpID);
    if (mpTornado == NULL || fpcM_IsCreating(mTactWarpID)) {
        if (mTactWarpID == fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_onEventFlag(8);
            m1984.remove();
            m1998.remove();
            procPaddleMove_init();
            dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        }
        res = FALSE;
    }
    else {
        if (cLib_chaseS(&m03A6, 0x1C25, 0x40) && (mpTornado->mJointScale[10] > 0.8f)) {
            speed.y += 1.0f;
            if (speed.y > 50.0f) {
                speed.y = 50.0f;
            }
            current.pos.y += speed.y;
            mpTornado->current.pos.y = current.pos.y - 700.0f;
            m1984.remove();
            m1998.remove();
        }
        else {
            if ((!m037A) && (m03A6 > 0x1000)) {
                m037A = 1;
                mpTornado->m31c = 1;
            }
        }
        if (m037A == 1) {
            cLib_chaseF(&mpTornado->current.pos.y, current.pos.y - 700.0f, 20.0f);
            iVar4 = 0;
            for (int i = 0; i < 11; iVar4++, i++) {
                if (current.pos.y < mpTornado->getJointYPos(i)) break;
            }
            if (iVar4 == 11) {
                iVar4 = 10;
            }
              cLib_chaseF(&current.pos.x, mpTornado->getJointXPos(iVar4), 50.0f);
              cLib_chaseF(&current.pos.z, mpTornado->getJointZPos(iVar4), 50.0f);
        }
        if (m037A != 2 && current.pos.y > m03F4 + 5000.0f ) {
            m037A = 2;
            dStage_changeScene(mTactWarpPosNum + 0xC5, 0.0f, 0, 0xFF);
            mDoAud_taktModeMuteOff();
        }
        m03BC.y = shape_angle.y + 0x8000;
        res = TRUE;
    }
    return res;
}

/* 0000797C-00007A90       .text procWhirlDown_init__8daShip_cFv */
BOOL daShip_c::procWhirlDown_init() {
    mProc = &daShip_c::procWhirlDown;
    mCurMode = 15;
    gravity = 0.0f;
    speed.y = 0.0f;
    onStateFlg(daSFLG_FLY_e);
    onStateFlg(daSFLG_UNK1000_e);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz local_38(mWhirlActor->current.pos.x, mWhirlActor->current.pos.y + 2500.0f, mWhirlActor->current.pos.z + 4000.0f);
    camera->mCamera.Set(mWhirlActor->current.pos, local_38);
    m037A = 0;
    return TRUE;
}

/* 00007A90-00007BEC       .text procWhirlDown__8daShip_cFv */
BOOL daShip_c::procWhirlDown() {  
    shape_angle.y += (m0408 / 6.2831855f) * 65536.0f;
    if (mWhirlActor) {
        speedF = 40.0f;
        if (cLib_addCalcPosXZ(&current.pos, mWhirlActor->current.pos, 1.0f, 40.0f, 10.0f) < 10.0f) {
            speed.y -= 0.5f;
            if (speed.y < -10.0f) {
                speed.y = -10.0f;
            }
            current.pos.y += speed.y;
            if (m037A == 0 && current.pos.y < m03F4 - 1000.0f) {
                dComIfGs_onEventBit(0x1940);
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), m03B2, fopAcM_GetRoomNo(this));
                m037A = 1;
            }
        }
    }
    return TRUE;
}

/* 00007BEC-00007DC0       .text procStartModeThrow_init__8daShip_cFv */
BOOL daShip_c::procStartModeThrow_init() {
    current.pos.y = m03F4 + 2500.0f;
    speedF = 100.0f;
    onStateFlg(daSFLG_FLY_e);
    mProc = &daShip_c::procStartModeThrow;
    mCurMode = MODE_START_MODE_THROW_e;
    if (m0392 != SHIP_BCK_FN_MAST_OFF2) {
        setPartOffAnime();
    }
    m03A6 = 3600;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz local_38(current.pos.x + cM_scos(current.angle.y) * 300.0f, 
                  m03F4 + 150.0f, 
                  current.pos.z - cM_ssin(current.angle.y) * 300.0f);
    camera->mCamera.Set(current.pos, local_38);
    current.pos.x -= cM_ssin(current.angle.y) * 4500.0f;
    current.pos.z -= cM_scos(current.angle.y) * 4500.0f;
    m037A = 0;
    return TRUE;
}

/* 00007DC0-0000804C       .text procStartModeThrow__8daShip_cFv */
BOOL daShip_c::procStartModeThrow() {
    GXColor amb;
    GXColor diff;
    
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    shape_angle.y += m03A6;
    camera->mCamera.Set(current.pos, camera->mCamera.Eye());
    if (m037A == 0) {
        if (current.pos.y < m03F4) {
            speed.y = 0.0f;
            speedF = 0.0f;
            offStateFlg(daSFLG_FLY_e);
            m037A++;
            dKy_get_seacolor(&amb, &diff);
            amb.r = amb.r * 0.23529412f + 195.0f;
            amb.g = amb.g * 0.23529412f + 195.0f;
            amb.b = amb.b * 0.23529412f + 195.0f;
            current.pos.y = m03F4;
            dComIfGp_particle_set(dPa_name::ID_SCENE_82D7, &current.pos, &shape_angle, NULL, 0xFF, NULL, -1, &amb);
            dComIfGp_particle_set(dPa_name::ID_SCENE_82D8, &current.pos, &shape_angle, NULL, 0xFF, NULL, -1, &amb);
            current.pos.y = m03F4 - 50.0f;
        }
    }
    else {
        if (cLib_chaseS(&m03A6, 0, 0x100)) {
            m037A++;
            if(m037A == 45) {
                camera->mCamera.Start();
                camera->mCamera.Reset();
                current.angle.y = shape_angle.y;
                dComIfGp_evmng_cutEnd(mEvtStaffId);
                procPaddleMove_init();
            }
        }
    }
    return TRUE;
}

/* 0000804C-000085D8       .text setEffectData__8daShip_cFfs */
void daShip_c::setEffectData(float param_1, short param_2) {
    static JGeometry::TVec3<f32> wave_l_direction(0.5f, 1.0f, -0.3f);
    static JGeometry::TVec3<f32> wave_r_direction(-0.5f, 1.0f, -0.3f);
    
    float fVar1;
    float fVar2;
    float fVar3;
    JPABaseEmitter* mEmitter;
    GXColor amb;
    GXColor diff;
    
    if (checkStateFlg(daSFLG_FLY_e) && current.pos.y - 40.0f > param_1) {
        mWaveR.mState = 1;
        mWaveL.mState = 1;
        mSplash.mState = 1;
        mTrack.mState = 1;
    }
    else {
        if (speedF <= 0.0f) {
            mWaveR.mState = 1;
            mWaveL.mState = 1;
            mSplash.mState = 1;
        }
        
    }
    fVar3 = speedF + 150.0f;
    mEffPos.set(current.pos.x + fVar3 * cM_ssin(shape_angle.y), param_1, current.pos.z + fVar3 * cM_scos(shape_angle.y));
    getMaxWaterY(&mEffPos);
    if (!checkStateFlg(daSFLG_FLY_e) || param_1 > current.pos.y) {
        if (std::fabsf(mFwdVel) > 3.0f) {
            if (std::fabsf(speedF) > 3.0f && mFwdVel * speedF > 0.0f) {
                if (mFwdVel > 11.0f) {
                    if (mWaveL.getEmitter() == NULL) {
                        mEmitter = dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mEffPos, &shape_angle, NULL, 0xFF, &mWaveL);
                        mWaveL.setTimer(20);
                        if (mEmitter) {
                            mEmitter->setDirection(wave_l_direction);
                        }
                    }
                    if (mWaveR.getEmitter() == NULL) {
                        mEmitter = dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mEffPos, &shape_angle, NULL, 0xFF, &mWaveR);
                        mWaveR.setTimer(20);
                        if (mEmitter) {
                            mEmitter->setDirection(wave_r_direction);
                        }
                    }
                    if (mSplash.getEmitter() == NULL) {
                        dComIfGp_particle_set(dPa_name::ID_COMMON_0035, &mEffPos, &shape_angle, NULL, 0xFF, &mSplash);
                    }
                }
                if (mTrack.getEmitter() == NULL) {
                    dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0036, &current.pos, &shape_angle, NULL, 0, &mTrack);
                }
                if (checkStateFlg((daSHIP_SFLG)(daSFLG_FLY_e | daSFLG_LAND_e))) {
                    dKy_get_seacolor(&amb, &diff);
                    mEmitter = dComIfGp_particle_set(dPa_name::ID_COMMON_0034, &mEffPos, &shape_angle, NULL, 0xFF, NULL, -1, &amb);
                    if (mEmitter) {
                        fVar1 = 10.0f;
                        fVar2 = (-(speed.y - -15.0f) / 30.0f) * 50.0f + 10.0f;
                        if (fVar2 < 10.0f) {
                            fVar2 = fVar1;
                        }
                        else if (fVar2 > 60.0f) {
                            fVar2 = 60.0f;
                        }
                        mEmitter->setRate(fVar2);
                    }
                    seStart(JA_SE_SHIP_JUMP_ALIGHT, &current.pos);
                }
            }
        }
    }

    mTrack.setIndirectTexData(-0.04f, 4.0f);
    mTrack.setSpeed(mFwdVel);

    if (mFwdVel >= 0.0f) {
        mWaveR.setSpeed(0.7f);
        mWaveL.setSpeed(0.7f);
    }
    else {
        mWaveR.setSpeed(-0.7f);
        mWaveL.setSpeed(-0.7f);
    }

    fVar1 = (s16)(shape_angle.z - param_2) / 16384.0f;

    if (fVar1 > 0.3f) {
        fVar1 = 0.3f;
    }
    else if (fVar1 < -0.3f) {
        fVar1 = -0.3f;
    }

    mWaveR.setPitch(fVar1 + 1.0f);
    mWaveL.setPitch(1.0f - fVar1);

    mSplash.setSpeed(mFwdVel);
    mSplash.setMaxSpeed(30.0f);
    
    cXyz anchorPos1;
    cXyz anchorPos2;

    anchorPos1.set(-80.0f, -50.0f, -150.0f);
    anchorPos2.set(-40.0f, -100.0f, -350.0f);
    mWaveR.setAnchor(&anchorPos1, &anchorPos2);

    anchorPos1.x *= -1.0f;
    anchorPos2.x *= -1.0f;
    mWaveL.setAnchor(&anchorPos1, &anchorPos2);

    mWaveL.setMaxDisSpeed(2.0f);
    mWaveR.setMaxDisSpeed(2.0f);

    mWaveL.setMaxSpeed(40.0f);
    mWaveR.setMaxSpeed(40.0f);
}

/* 000085D8-00008688       .text setRoomInfo__8daShip_cFv */
void daShip_c::setRoomInfo() {
    int roomId;
    if (mAcch.GetGroundH() != -G_CM3D_F_INF) {
        roomId = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
        m03C4 = dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd);
    }
    else {
        roomId = dStage_roomControl_c::mStayNo;
        m03C4 = 0;
    }
    tevStr.mRoomNo = roomId;
    m034A = dComIfGp_getReverb(roomId);
    mStts.SetRoomId(roomId);
    fopAcM_SetRoomNo(this, roomId);
}

/* 00008688-0000882C       .text incRopeCnt__8daShip_cFii */
// Adjusts the length of KORL's Salvage Arm rope
void daShip_c::incRopeCnt(int lengthChange, int minSegmentLimit) {
    int i;
    cXyz* ropeSegments = mRopeLine.getPos(0);
    int currRopeCnt = mRopeCnt;
    cXyz* currRopeSegment = &mRopeLineSegments[currRopeCnt];
    int targetRopeCnt = currRopeCnt + lengthChange;

    // Ensure the new segment index is within valid bounds
    if (targetRopeCnt >= (int)ARRAY_SIZE(mRopeLineSegments)) {
        targetRopeCnt = ARRAY_SIZE(mRopeLineSegments);
    }
    else if (targetRopeCnt < minSegmentLimit) {
        targetRopeCnt = minSegmentLimit;
    }

    lengthChange = targetRopeCnt - currRopeCnt; // Number of segments to increase/decrease the rope by

    if (lengthChange > 0) {
        // Lengthening the rope: Move all segments down by adding a displacement vector
        cXyz ropeDisplacement = l_rope_base_vec * lengthChange;
        for (i = 0; i < mRopeCnt; i++, ropeSegments++) {
            *ropeSegments += ropeDisplacement;
        }
    }
    else {
        // Shortening the rope: Do nothing except skipping over all existing rope segments
        ropeSegments += currRopeCnt;
    }

    for (i = mRopeCnt; i < targetRopeCnt; i++, currRopeSegment++, ropeSegments++) {
        currRopeSegment->set(l_rope_base_vec);
        if (mRopeCnt) {
            ropeSegments->set(*(ropeSegments - 1) - l_rope_base_vec);
        }
    }

    if (lengthChange != 0) {
        if ((minSegmentLimit == 20) && (targetRopeCnt == 20)) {
            seStart(JA_SE_LK_SHIP_CRANE_STOP, &m102C);
        }
        else {
            seStart(JA_SE_LK_SHIP_CRANE_WORK, &m102C);
        }
    }

    mRopeCnt = targetRopeCnt;
}

/* 0000882C-00009314       .text setRopePos__8daShip_cFv */
void daShip_c::setRopePos() {
    /* Nonmatching - regalloc */
    float fVar1;
    float fVar2;
    float fVar17;

    cXyz* r4;
    int iVar11;
    short sVar14;
    int sVar12;
    JPABaseEmitter* emitter;
    cXyz* r3;
    cXyz* ropeSegments;
    cXyz* currentRopeSegment;
    short currentRopeSegmentIndex;
    MtxP pMVar5;

    cXyz spF8;
    cXyz spEC;
    cXyz spE0;
    cXyz spD0;
    cXyz spC8;
    cXyz spBC;

    static cXyz ripple_scale(0.6f, 0.6f, 0.6f);
    static Vec rope_offset = {160.0f, 0.0f, 0.0f};
    static Vec water_drop_scale = {1.5f, 1.0f, 1.5f};
    
    currentRopeSegmentIndex = mRopeCnt;
    
    if (currentRopeSegmentIndex == 0) {
        currentRopeSegment = mRopeLine.getPos(0);
        ropeSegments = mRopeLineSegments;
    }
    else {
        currentRopeSegment = mRopeLine.getPos(0) + currentRopeSegmentIndex - 1;
        ropeSegments = &mRopeLineSegments[currentRopeSegmentIndex - 1];
    }

    spF8 = *currentRopeSegment;

    cMtx_multVec(mpSalvageArmModel->getAnmMtx(1), &rope_offset, currentRopeSegment);

    if (mProc == &daShip_c::procCraneUp) {
        spEC.set(mpLinkModel->getBaseTRMtx()[0][3] - currentRopeSegment->x, 
                     mpLinkModel->getBaseTRMtx()[1][3] - currentRopeSegment->y, 
                     mpLinkModel->getBaseTRMtx()[2][3] - currentRopeSegment->z);
        
        spEC.normalize();

        spEC *= 10.0f;

        currentRopeSegment--;
        ropeSegments--;

        for (int i = mRopeCnt + -2; i >= 0; i--, currentRopeSegment--, ropeSegments--) {
            currentRopeSegment->set(*(currentRopeSegment + 1) + spEC);
            ropeSegments->set(cXyz::Zero);
        }
    }
    else {
        currentRopeSegment--;
        ropeSegments--;

        for (int i = mRopeCnt + -2; i >= 0; i--, currentRopeSegment--, ropeSegments--) {
            spF8 = *currentRopeSegment;

            if (currentRopeSegment->y < m03F4) {
                *ropeSegments *= 0.6f;
            }
            else {
                *ropeSegments *= 0.9f;
            }

            ropeSegments->y -= 3.0f;

            *currentRopeSegment += *ropeSegments;

            spEC.set(*currentRopeSegment - *(currentRopeSegment + 1));

            fVar17 = std::sqrtf(spEC.abs2());

            if (fVar17 < 0.01f) {
                currentRopeSegment->set(*(currentRopeSegment + 1) + l_rope_base_vec);
            }
            else {
                currentRopeSegment->set(*(currentRopeSegment + 1) + (spEC * 10.0f)/fVar17);
            }

            *ropeSegments += (*currentRopeSegment - spF8) * 0.05f;
        }
        if (mRopeCnt == 20 && checkStateFlg(daSFLG_UNK10000000_e)) {
            r4 = mRopeLine.getPos(0);
            mDoMtx_multVecZero(mpSalvageArmModel->getAnmMtx(1), &spE0);
            spE0 -= *r4;

            if (spE0.abs2XZ() < 2500.0f) {
                currentRopeSegment = mRopeLineSegments;
                f32 f2 = cM_scos(shape_angle.x) * 16.0f;

                if (shape_angle.x <= 0) {
                    f2 *= -1.0f;
                }
                
                spD0.set(
                    f2 * cM_ssin(shape_angle.y),
                    0.0f,
                    f2 * cM_scos(shape_angle.y)
                );

                for (int i = 0; i < 20; i++, currentRopeSegment++) {
                    *currentRopeSegment += spD0;
                    spD0 *= 0.95f;
                }
                
                offStateFlg(daSFLG_UNK10000000_e);
            }
        }
    }

    currentRopeSegment = mRopeLine.getPos(0);

    if (mRopeCnt > 2) {
        spC8 = *currentRopeSegment - *(currentRopeSegment + 1);
        sVar14 = 0;
        sVar12 = 0;
    }
    else {
        pMVar5 = mpSalvageArmModel->getAnmMtx(1);
        spC8.set(
            currentRopeSegment->x - pMVar5[0][3],
            currentRopeSegment->y - pMVar5[1][3],
            currentRopeSegment->z - pMVar5[2][3]
        );
        sVar14 = 0x7fff;
        iVar11 = 0x8000 - (m0398 * 2);
        sVar12 = iVar11 - (0x8000 - mCraneBaseAngle) * ((float)m0398 / (float)mCraneBaseAngle);
    }

    fVar17 = mpLinkModel->getBaseTRMtx()[1][3];

    f32 sin = cM_ssin(shape_angle.y);
    f32 cos = cM_scos(shape_angle.y);
    spBC.x = cos * spC8.x - sin * spC8.z;
    spBC.y = spC8.y;
    spBC.z = sin * spC8.x + cos * spC8.z;
    
    mDoMtx_trans(mDoMtx_stack_c::get(), currentRopeSegment->x, currentRopeSegment->y, currentRopeSegment->z);
    fVar1 = std::sqrtf(spBC.y * spBC.y + spBC.z * spBC.z);
    s16 z = sVar12 + cM_atan2s(-spBC.x, fVar1);
    s16 y = shape_angle.y;
    s16 x = sVar14 + cM_atan2s(spBC.z, spBC.y);
    mDoMtx_stack_c::ZXYrotM(x, y, z);
    mDoMtx_stack_c::XrotM(-0x4000);

    if (m0392 == SHIP_BCK_FN_MAST_ON2) {
        J3DTransformInfo sp104;
        mpBodyAnm->getAnm()->getTransform(6, &sp104);
        mDoMtx_stack_c::scaleM(sp104.mScale.x, sp104.mScale.y, sp104.mScale.z);
    }

    mpLinkModel->setBaseTRMtx(mDoMtx_stack_c::get());

    fVar1 = currentRopeSegment->y;

    getMaxWaterY(currentRopeSegment);

    fVar2 = currentRopeSegment->y;

    currentRopeSegment->y = fVar1;

    if (fVar2 > currentRopeSegment->y) {
        ropeSegments = currentRopeSegment;

        r3 = currentRopeSegment;
        for (int i = 0; i < mRopeCnt; i++, ropeSegments++) {
            if (ropeSegments->y <= fVar2) {
                r3 = ropeSegments;
            }
        }

        m1020.x = r3->x;
        m1020.y = fVar2;
        m1020.z = r3->z;

        if (mRipple.getEmitter() == NULL) { 
            dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &m1020, NULL, &ripple_scale, 0xFF, &mRipple);

            if (mRipple.getEmitter() != NULL) {
                mRipple.setRate(0.0f);

                if (m034F == 0) {
                    fopKyM_createWpillar(&m1020, 0.7f, 0.7f, 0);

                    seStart(JA_SE_LK_SHIP_CRANE_DROP, &m1020);

                    dComIfGp_getVibration().StartShock(3, 1, cXyz(0.0f, 1.0f, 0.0f));
                }
            }
        }
    }
    else {
        if (fVar17 < fVar2 && !m034F && mRopeCnt >= 20) {
            m034F = 20;

            seStart(JA_SE_LK_SHIP_CRANE_LIFTUP, &m1020);

            if (mCurMode != MODE_CRANE_UP_e) {
                if (m19AC.getEmitter() == NULL) {
                    ropeSegments = mRopeLine.getPos(0);

                    emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0038, ropeSegments, NULL, NULL, 0xFF, &m19AC);

                    if(emitter) {
                        emitter->setGlobalParticleScale(JGeometry::TVec3<f32>(1.5f, 1.5f, 1.0f));
                        emitter->setEmitterScale(water_drop_scale);
                        emitter->setLifeTime(30);
                    }
                }
                
                fopKyM_createWpillar(&m1020, 0.5f, 0.7f, 0);
                
                dComIfGp_getVibration().StartShock(3, 1, cXyz(0.0f, 1.0f, 0.0f));
                
                if (m19C0.getEmitter() == NULL) {
                    emitter = dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &m1074, NULL, &ripple_scale, 0xFF, &m19C0);
                    
                    if (emitter) {
                        emitter->setVolumeSize(30);
                    }
                }
            }
        }
        mRipple.remove();
    }

    if (m034F) {
        m034F--;
    }

    if (!m19AC.getEmitter()) {
        m19C0.remove();
    }

    m1074.x = mRopeLine.getPos(0)->x + cM_rndFX(20.0f);
    m1074.y = m03F4;
    m1074.z = mRopeLine.getPos(0)->z + cM_rndFX(20.0f);
}

/* 00009314-00009384       .text getAnglePartRate__8daShip_cFv */
f32 daShip_c::getAnglePartRate() {
    float fVar1;
    if (m0392 == SHIP_BCK_FN_MAST_OFF2) {
        fVar1 = 0.33333334f * (3.0f - mpBodyAnm->getFrame());
    }
    else {
        fVar1 = 0.33333334f * (mpBodyAnm->getFrame() - 5.0f);
    }
    if (fVar1 > 1.0f) {
        fVar1 = 1.0f;
    }
    else if (fVar1 < 0.0f) {
        fVar1 = 0.0f;
    }   
    return fVar1;
}

/* 00009384-000095E4       .text setTornadoActor__8daShip_cFv */
void daShip_c::setTornadoActor() {
    cXyz local_20;
    
    mTornadoActor = (daTornado_c*)fopAcM_SearchByID(mTornadoID);
    if (mTornadoActor == NULL) {
        offTornadoFlg();
    }
    else {
        local_20 = current.pos - mTornadoActor->current.pos;
        m0400 = local_20.absXZ();
        m040C = cM_atan2f(local_20.x, local_20.z);
        
        dCam_getBody()->SetTypeForce("Tornado", mTornadoActor);
        m0404 = (6000.0f - m0400) * 0.0004f;
        if (m0404 < 0.0f) {
            m0404 = 0.0f;
        }
        daTornado_c* pfVar2 = mTornadoActor;
        float dx = pfVar2->getJointXPos(0) - current.pos.x;
        float dz = pfVar2->getJointZPos(0) - current.pos.z;
        float distXZ = std::sqrtf(dx * dx + dz * dz);
        if (!checkStateFlg(daSFLG_UNK1000_e) && distXZ < 3500.0f) {
            if(daPy_getPlayerLinkActorClass()->shipSpecialDemoStart()) {
                procTornadoUp_init();
            }
        }
    }
}

/* 000095E4-00009790       .text setWhirlActor__8daShip_cFv */
void daShip_c::setWhirlActor() {
    cXyz local_20;
    
    mWhirlActor = (daTornado_c*)fopAcM_SearchByID(mWhirlID);
    if (mWhirlActor == NULL) {
        offWhirlFlg();
    }
    else {
        local_20 = current.pos - mWhirlActor->current.pos;
        m0400 = local_20.absXZ();
        m040C = cM_atan2f(local_20.x, local_20.z);
        dCam_getBody()->SetTypeForce("Tornado", mWhirlActor);
        m0404 = (4000.0f - m0400) * 0.00028571428f;
        if (m0404 < 0.0f) {
            m0404 = 0.0f;
        }

        if (m0400 < 500.0f && !checkStateFlg(daSFLG_UNK1000_e)) {
            if(daPy_getPlayerLinkActorClass()->shipSpecialDemoStart()) {
                procWhirlDown_init();
            }
        }
    }
}

/* 00009790-00009B4C       .text setHeadAnm__8daShip_cFv */
void daShip_c::setHeadAnm() {
    s32 newFileIndex = -1;
    float speed;
    float morph;

    if (dComIfGp_event_runCheck()) {
        if (mEvtStaffId == -1 &&
            (dComIfGp_evmng_startCheck("SV_TALK_P1_1ST") ||
             dComIfGp_evmng_startCheck("SV_TALK_P1_2ND") ||
             dComIfGp_evmng_startCheck("SV_TALK_P4_1ST"))) {
            newFileIndex = SHIP_BCK_KYAKKAN1;
        } else if (m03B4 == SHIP_BCK_KYAKKAN1 || m03B4 == SHIP_BCK_DAMAGE1) {
            newFileIndex = SHIP_BCK_FN_LOOK_L;
        }
    } 
    else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) { 
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_BOW_AIM_e | daPyStts0_UNK2000_e | daPyStts0_HOOKSHOT_AIM_e | daPyStts0_BOOMERANG_AIM_e | daPyStts0_TELESCOPE_LOOK_e) || 
            dComIfGp_checkPlayerStatus1(0, daPyStts1_PICTO_BOX_AIM_e) || 
            mCurMode == 9) {
            newFileIndex = SHIP_BCK_KYAKKAN1;
        } 
        else if ((!dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02)) &&
                 (mSph.ChkTgHit() || mCyl[0].ChkTgHit() ||
                  mCyl[1].ChkTgHit() || mCyl[2].ChkTgHit())) {
            m03B4 = SHIP_BCK_FN_LOOK_L;
            newFileIndex = SHIP_BCK_DAMAGE1;
        } 
        else if (m03B4 != SHIP_BCK_DAMAGE1 || std::fabsf(mpHeadAnm->getPlaySpeed()) < 0.01f) {
            newFileIndex = SHIP_BCK_FN_LOOK_L;
        }
    } 
    else {
        if ((!dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02)) &&
            (mSph.ChkTgHit() || mCyl[0].ChkTgHit() ||
             mCyl[1].ChkTgHit() || mCyl[2].ChkTgHit())) {
            m03B4 = SHIP_BCK_FN_LOOK_L;
            newFileIndex = SHIP_BCK_DAMAGE1;
        } 
        else if (m03B4 == SHIP_BCK_DAMAGE1 || m03B4 == SHIP_BCK_AKIBI1) {
            if (mpHeadAnm->getPlaySpeed() < 0.01f) {
                newFileIndex = SHIP_BCK_FN_LOOK_L;
            }
        } 
        else if ((m03B4 == SHIP_BCK_FN_LOOK_L || m03B4 == SHIP_BCK_FN_LOOK_R) && 
                 std::fabsf(mpHeadAnm->getPlaySpeed()) < 0.01f && 
                 cM_rnd() < 0.4f && (g_Counter.mTimer & 0x1FF) == 0x1FF && 
                 (!dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02)) &&
                 !checkStateFlg(daSFLG_UNK40000000_e)) {
            newFileIndex = SHIP_BCK_AKIBI1;
        } 
        else if (m03B4 != SHIP_BCK_FN_LOOK_R) {
            newFileIndex = SHIP_BCK_FN_LOOK_L;
        }
    }

    if (m03B4 != newFileIndex && newFileIndex != -1) {
        if (newFileIndex == SHIP_BCK_AKIBI1) {
            speed = 1.0f;
            morph = 5.0f;
        } 
        else if (newFileIndex == SHIP_BCK_DAMAGE1) {
            speed = 1.0f;
            morph = 0.0f;
        }
        else {
            speed = 0.0f;
            morph = 5.0f;
        }
        m03B4 = newFileIndex;
        mpHeadAnm->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, m03B4), 0, morph, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00009B4C-0000B978       .text execute__8daShip_cFv */
BOOL daShip_c::execute() {
    /* Nonmatching */
    static cXyz sail_offset(0.5f, 155.0f, 50.0f);
    static cXyz sph_offset(-5.0f, 0.0f, 0.0f);
    static f32 cyl_offset[] = {100.0f, -20.0f, -100.0f};

    f32 prev_fwdvel = mFwdVel;
    f32 prev_speedF = speedF;
    m0351 = 0xFF;
    m0404 = 0.0f;
    m0428 = NULL;

    if (mTornadoID != fpcM_ERROR_PROCESS_ID_e) {
        setTornadoActor();
        mWhirlActor = NULL;
    }
    else {
        mTornadoActor = NULL;
        if (mWhirlID != fpcM_ERROR_PROCESS_ID_e) {
            setWhirlActor();
        }
        else {
            mWhirlActor = NULL;
        }
    }

    if (dComIfGp_event_runCheck()) {
        mStickMVal = 0.0f;
        mStickMAng = 0;
        mEvtStaffId = dComIfGp_evmng_getMyStaffId("Ship", this, 0);
        if (mEvtStaffId != -1) {
            char* cutName = dComIfGp_getPEvtManager()->getMyNowCutName(mEvtStaffId);
            if (cutName) {
                m0351 = (cutName[0] - '0') * 10 + (cutName[1] - '0');
            }
        }
        m03B8 = 0;
        offStateFlg(daSFLG_UNK2000000_e);
    }
    else {
        if (daPy_getPlayerLinkActorClass()->checkNoControll()) {
            mStickMVal = 0.0f;
            mStickMAng = 0;
        }
        else {
            mStickMVal = g_mDoCPd_cpadInfo[0].mMainStickValue;
            mStickMAng = g_mDoCPd_cpadInfo[0].mMainStickAngle + 0x8000;
        }
        mEvtStaffId = -1;
    }
    
    offStateFlg(daSHIP_SFLG(daSFLG_JUMP_e | daSFLG_LAND_e | daSFLG_UNK100_e | daSFLG_JUMP_OK_e | daSFLG_SHOOT_CANNON_e | daSFLG_UNK100000_e | daSFLG_UNK8000000_e));
    
    if (m0388 > 0) {
        m0388--;
    }

    if (checkStateFlg(daSFLG_UNK20_e) != 0) {
        speed.y = 5.0f;
        offStateFlg(daSFLG_UNK20_e);
    }

    mpBodyAnm->play(NULL, 0, 0);
    mpHeadAnm->play(NULL, 0, 0);

    if (
        mCurMode != 12 && mCurMode != 15 &&
        mCurMode != MODE_START_MODE_WARP_e && mCurMode != MODE_START_MODE_THROW_e &&
        mCurMode != 7 && mCurMode != MODE_CRANE_UP_e &&
        mCurMode != 8
    ) {
        if(eventInfo.checkCommandTalk()) {
            if (mNextMessageNo == 0x1682) {
                dComIfGp_onMenuCollect();
            }
            
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                procTalkReady_init();
            }
            else {
                procTalk_init();
            }
        }
        else { 
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && checkOutRange()) {
                if (checkStateFlg(daSFLG_FLY_e)) {
                    cLib_addCalcAngleS2(&shape_angle.y, m038C, 8, m038E);
                    cLib_addCalcAngleS2(&m038E, 0x1800, 8, 0x200);
                    current.angle.y = shape_angle.y;
                }
                else {
                    eventInfo.onCondition(dEvtCnd_CANTALK_e);
                    fopAcM_orderSpeakEvent(this);
                }
            }
            else {
                if (checkOutRange()) {
                    firstDecrementShipSpeed(0.0f);   
                }
                eventInfo.onCondition(dEvtCnd_CANTALK_e);
            }
        }
    }

    mpGrid = NULL;
    mpGrid = (daGrid_c*)fopAcM_SearchByID(mGridID);
    dDemo_actor_c* demoActor;
    demoActor = dComIfGp_demo_getActor(demoActorID);

    if (demoActor) {
        procToolDemo_init();
    }
    else if(mEvtStaffId != -1 && m0351 != 2 && m0351 != 9) {
        procZevDemo_init();
    }
    else if (m0351 == 2) {
        procCraneUp_init();
    }

    short sVar26;
    sVar26 = m0366;

    if (mAnmTransform) {
        mFrameCtrl.update();
        mAnmTransform->setFrame(mFrameCtrl.getFrame());
        if (!checkStateFlg(daSFLG_UNK8000_e) && mFrameCtrl.checkState(2)) {
            mAnmTransform = NULL;
        }
    }
    
    BOOL r24;
    if (m0351 == 8 || checkStateFlg(daSFLG_UNK4000000_e)) {
        r24 = TRUE;
    }
    else {
        r24 = FALSE;
    }
    
    if (mProc) {
        (this->*mProc)();
    }

    if (m0351 == 8 || checkStateFlg(daSFLG_UNK4000000_e)) {
        m0366 = -0x2000;
        sVar26 = m0366;
    }
    else if (r24) {
        m0366 = 0;
        sVar26 = 0;
    }
    
    if (!checkStateFlg(daSFLG_FLY_e)) {
        if (
            mCurMode != 12 && mCurMode != 15 &&
            mCurMode != 7 && mCurMode != MODE_CRANE_UP_e &&
            mCurMode != MODE_START_MODE_WARP_e && mCurMode != MODE_START_MODE_THROW_e &&
            !dComIfGp_event_runCheck()
        ) {
            if (mTornadoActor) {
                short sVar16;
                sVar16 = shape_angle.y;
                cLib_addCalcAngleS(&shape_angle.y, m040C * 10430.378f + 20480.0f, 5, 0x2000, 0x200);
                setControllAngle(getAimControllAngle(sVar16));
                current.angle.y = shape_angle.y;
            }
            else {
                if (mWhirlActor) {
                    short sVar16;
                    sVar16 = shape_angle.y;
                    short sVar5;
                    if (m0352) {
                        sVar5 = m040C * 10430.378f + 20480.0f;
                    }
                    else {         
                        sVar5 = m040C * 10430.378f + 32768.0f;
                    }
                    cLib_addCalcAngleS(&shape_angle.y, sVar5, 5, 0x2000, 0x200);
                    setControllAngle(getAimControllAngle(sVar16));
                    current.angle.y = shape_angle.y;
                }
            }
        }
        short sVar16;
        sVar16 = -m0384;
        short sVar5;
        sVar5 = sVar16 * 0.05f;
        if (sVar5 == 0) {
            if (sVar16 > 0) {
                sVar5 = 1;
            }
            else if (sVar16 < 0) {
                sVar5 = -1;
            }
        }
        m0386 += sVar5;
        m0384 += m0386;
        cLib_addCalcAngleS(&m0386, 0, 30, 0x1000, 1);
    }
    else {
        cLib_addCalcAngleS(&m0384, -0x800, 3, 0x500, 0x300);
    }

    m045C = current.pos;

    if (!checkStateFlg(daSFLG_UNK2000000_e)) {
        cLib_chaseS(&m03B8, 0, 0x80);
    }
    else {
        cLib_chaseS(&m03B8, 0x4E8, 0x80);
    }

    float fVar4;
    if (mCurMode != 12 && mCurMode != 15) {
        if (mCurMode != 7 && mCurMode != MODE_CRANE_UP_e) {
            if (
                (dComIfGp_event_runCheck() || daPy_getPlayerLinkActorClass()->checkNoControll()) &&
                mEvtStaffId == -1 &&
                mCurMode != MODE_TALK_e &&
                mCurMode != MODE_START_MODE_THROW_e &&
                !checkStateFlg(daSFLG_UNK100000_e)
            ) {
                if (checkStateFlg(daSFLG_UNK20000000_e)) {
                    if (speedF >= 10.0f) {
                        firstDecrementShipSpeed(10.0f);
                    }
                }
                else {
                    speedF = 0.0f;
                }
            }
            if (!dComIfGp_event_runCheck() && !checkStateFlg(daSFLG_FLY_e) && checkForceMove()) {
                speedF = prev_speedF;
                if (mTornadoActor) {
                    fVar4 = m0404 * 40.0f + 30.0f;
                    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_BOW_AIM_e) || !dComIfGp_checkCameraAttentionStatus(0, 0x20)) {
                        fVar4 *= 1.2f;
                    }
                }
                else {
                    fVar4 = m0404 * 30.0f + 10.0f;
                    // Bug? This room check assumes we're on the sea without checking?
                    if (dComIfGs_getBombNum() == 0 && fopAcM_GetRoomNo(this) == dIsleRoom_OutsetIsland_e) {
                          fVar4 *= 1.2f;
                    }
                }
                firstDecrementShipSpeed(fVar4);
            }

            shape_angle.y += m03B8;
            current.angle.y += m03B8;

            if (checkStateFlg(daSFLG_FLY_e)) {
                if (checkStateFlg(daSFLG_UNK2000000_e)) {
                    cLib_chaseF(&speed.y, 20.0f, 1.0f - gravity);
                    speedF = prev_speedF;
                    cLib_chaseF(&speedF, 55.0f, 3.0f);
                    offStateFlg(daSFLG_UNK2000000_e);
                }

                if (speed.y > 0.0f && speed.y <= -gravity) {
                    onStateFlg(daSFLG_UNK100_e);
                }

                fopAcM_posMoveF(this, mStts.GetCCMoveP());
                
                m1044 = cXyz::Zero;
            }
            else {
                if (checkForceMove() && !dComIfGp_event_runCheck()) {
                    if (mTornadoActor) {
                        if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_BOW_AIM_e) || !dComIfGp_checkCameraAttentionStatus(0, 0x20)) {
                            prev_speedF = 25.0f;
                        }
                        else {
                            prev_speedF = 5.0f;
                        }
                    }
                    else {
                        // Bug? This room check assumes we're on the sea without checking?
                        if (dComIfGs_getBombNum() == 0 && fopAcM_GetRoomNo(this) == dIsleRoom_OutsetIsland_e) {
                            prev_speedF = 10.0f;
                        }
                        else {
                            prev_speedF = 0.6f;
                        }
                    }

                    cLib_chaseF(&m0400, 0.0f, prev_speedF);

                    m0408 = std::fabsf(speedF) / m0400;
                    
                    m040C += m0408;

                    BOOL r23; // BUG: this var is never initialized to FALSE
                    if (mTornadoActor) {
                        current.pos.x = mTornadoActor->current.pos.x + (m0400 * cM_fsin(m040C));
                        current.pos.z = mTornadoActor->current.pos.z + (m0400 * cM_fcos(m040C));
                        r23 = TRUE;
                    }
                    else if (m0352) {
                        current.pos.x = mWhirlActor->current.pos.x + (m0400 * cM_fsin(m040C));
                        current.pos.z = mWhirlActor->current.pos.z + (m0400 * cM_fcos(m040C));
                        r23 = TRUE;
                    }
                    else {
                        prev_speedF = current.pos.y;
                        fopAcM_posMoveF(this, mStts.GetCCMoveP());
                        current.pos.y = prev_speedF;
                    }
                    if (r23) {
                        cXyz sp114(current.pos - old.pos);
                        float dVar27;
                        dVar27 = sp114.absXZ();
                        if (dVar27 > 1.0f) {
                            prev_speedF = speedF / dVar27;
                            current.pos.x = old.pos.x + sp114.x * prev_speedF;
                            current.pos.z = old.pos.z + sp114.z * prev_speedF;
                        }
                    }
                }
                else {
                    speed.x = (speedF * cM_ssin(current.angle.y)) * cM_scos(m0370);
                    speed.y = -speedF * cM_ssin(m0370);
                    speed.z = (speedF * cM_scos(current.angle.y)) * cM_scos(m0370);
                    fopAcM_posMove(this, mStts.GetCCMoveP());
                    if (dComIfGp_event_runCheck()) {
                        m1044 = cXyz::Zero;
                        
                    }
                    else {
                        cXyz sp108;
                        int sp18;
                        if (mAcch.GetGroundH() != -G_CM3D_F_INF && dPath_GetPolyRoomPathVec(mAcch.m_gnd, &sp108, &sp18)) {
                            sp108.normalizeZP();
                            sp108 *= sp18 >> 1;
                            cLib_addCalcPosXZ(&m1044, sp108, 0.5f, 5.0f, 1.0f);
                        }
                        else {
                            cLib_addCalcPosXZ(&m1044, cXyz::Zero, 0.05f, 0.1f, 0.02f);

                        }
                        current.pos += m1044;
                    }
                }
            }
        }
        else {
            m1044 = cXyz::Zero;
            if (mEvtStaffId == -1) {
                cXyz spFC(current.pos - old.pos);
                if (checkStateFlg(daSFLG_FLY_e)) {
                    speedF = spFC.absXZ();
                }
                else {
                    speedF = spFC.abs();
                }
            }
            else {
                speed.x = (speedF * cM_ssin(current.angle.y)) * cM_scos(m0370);
                if (m0351 != 7 && m0351 != 10 && m0351 != 11) {
                    speed.y = -speedF * cM_ssin(m0370);
                }
                speed.z = (speedF * cM_scos(current.angle.y)) * cM_scos(m0370);
                fopAcM_posMove(this, mStts.GetCCMoveP());
            }
        }
    }
    mStts.ClrCcMove();
    
    cXyz spF0 = current.pos;
    
    mAcchCir[3].SetWall(-600.0f - current.pos.y, 250.0f);
    
    mAcch.CrrPos(*dComIfG_Bgsp());

    if (checkForceMove()) {
        current.pos = spF0;
    }

    setRoomInfo();

    if (mCurMode == 14) {
        current.pos.x = spF0.x;
        current.pos.z = spF0.z;
    }

    setYPos();

    float diff = m03F4 - current.pos.y;

    mTrack.mBaseY = m03F4;
    mTrack.mMinY = m03F8;

    s16 sp12;
    s16 sp10;
    if (!checkStateFlg(daSFLG_FLY_e)) {
        setWaveAngle(&sp12, &sp10);
    }
    else {
        sp12 = m037C;
        sp10 = m037E;
    }

    diff += 5.0f;

    if (diff > m03D8) {
        m03D8 = diff;
    }
    else {
        cLib_chaseF(&m03D8, diff, 3.0f);
    }

    m037C = shape_angle.x;
    m037E = shape_angle.z;

    if (mCurMode == 14) {
        shape_angle.x = 0;
        shape_angle.z = 0;
    }
    else {
        shape_angle.x = m0370 + m0384;
        shape_angle.z = m036C + m0372;
    }

    mDoMtx_trans(mDoMtx_stack_c::get(), current.pos.x, current.pos.y, current.pos.z);
    
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    
    J3DModel* mModel1;
    J3DModel* mModel2;
    mModel1 = mpBodyAnm->getModel();
    mModel2 = mpHeadAnm->getModel(); 
    
    mModel1->setBaseTRMtx(mDoMtx_stack_c::get());
    mpBodyAnm->calc();
    
    setHeadAnm();
    
    mModel2->setBaseTRMtx(mModel1->getAnmMtx(4));
    mpHeadAnm->calc();

    if (mPart == PART_CRANE_e) {
        if (m0392 == SHIP_BCK_FN_MAST_OFF2) {
            f32 rate = getAnglePartRate();
            m0398 = rate * mCraneBaseAngle;
            m039C *= getAnglePartRate();
            incRopeCnt(-20, 0);
        }
        mpSalvageArmModel->calc();
        setRopePos();
        mDoMtx_multVecZero(mpSalvageArmModel->getAnmMtx(1), &m102C);
        if (mProc == &daShip_c::procCrane || mProc == &daShip_c::procCraneUp) {
            m0434 = mRopeLine.getPos(0);
        }
        else {
            m0434 = NULL;
        }
    }
    else {
        m19C0.remove();
        mRipple.remove();
        m19AC.remove();

        mRopeCnt = 0;

        m0434 = NULL;

        if (mPart == PART_CANNON_e) {
            mDoMtx_multVecZero(mpCannonModel->getAnmMtx(2), &m1038);
            
            if (mProc != &daShip_c::procCannon) {
                m0396 = getAnglePartRate() * 16384.0f;
                m0394 *= getAnglePartRate();
            
            }
            
            mpCannonModel->calc();
            
            if (m037A == 30) {
                cXyz spE4;
                cMtx_multVec(mpCannonModel->getAnmMtx(2), &l_cannon_top, &spE4);

                csXyz sp1C;
                sp1C.set(getCannonAngleX(), getCannonAngleY(), shape_angle.z);

                daBomb_c* bomb = (daBomb_c *)fopAcM_fastCreate(PROC_BOMB, daBomb_c::prm_make(daBomb_c::STATE_4, FALSE, TRUE), &spE4, tevStr.mRoomNo, &sp1C);

                if (bomb) {
                    dCam_getBody()->ForceLockOn(fpcM_GetID(bomb));

                    bomb->setNoGravityTime(8);

                    bomb->speedF = cM_scos(sp1C.x) * 110.0f;
                    bomb->speed.y = -(cM_ssin(sp1C.x) * 110.0f);

                    bomb->gravity = -2.5f;

                    seStart(JA_SE_LK_SHIP_CANNON_FIRE, &m1038);

                    onStateFlg(daSFLG_SHOOT_CANNON_e);

                    dComIfGp_setItemBombNumCount(-1);

                    mpHeadAnm->setPlaySpeed(1.0f);
                    mpHeadAnm->setFrame(0.0f);
                }
                m037A--;
            }  
        }
    }

    cMtx_multVec(mModel1->getAnmMtx(10), &l_tiller_top_offset, &mTillerTopPos);

    MtxP mMtx = mModel1->getAnmMtx(7);

    m0444.x = mMtx[0][3];
    m0444.y = mMtx[1][3];
    m0444.z = mMtx[2][3];

    cXyz spD8;
    daGrid_c* grid = mpGrid;
    if (grid) {
        static cXyz top_offset(0.0f, 0.0f, -365.0f);
        static cXyz XZ_top_offset(265.0f, 0.0f, 0.0f);

        mpGrid->current.pos = m0444;
        mpGrid->current.angle = shape_angle;

        cMtx_multVecSR(mMtx, &top_offset, &spD8);
        mpGrid->scale.y = spD8.abs() / 365.0f;

        cMtx_multVecSR(mModel1->getAnmMtx(8), &XZ_top_offset, &spD8);
        grid->m2200 = 1.0f - (spD8.abs() / 265.0f); // No idea why this is generating an extra lwz instruction for loading mpGrid when the instructions above don't

        if (mTornadoActor) {
            mpGrid->force_calc_wind_rel_angle(0x3000);
        }
    }

    int iVar23;
    iVar23 = (s16)(m0366 - sVar26);
    int iVar6;
    iVar6 = abs(iVar23);
    iVar23 *= m0366;

    if (iVar23 > 0 && (float)iVar6 > 420.00003f) {
        seStart(JA_SE_LK_SHIP_RUDDER_OUT, &mTillerTopPos);
    }
    else if (iVar23 < 0 && (float)iVar6 > 525.0f) {
        seStart(JA_SE_LK_SHIP_RUDDER_OUT, &mTillerTopPos);
    }

    if (!checkStateFlg(daSFLG_FLY_e)) {
        float shipCruiseSpeed = std::fabsf(speedF) / 55.0f;
        if (shipCruiseSpeed > 1.0f){
            shipCruiseSpeed = 1.0f;
        }
        else if (shipCruiseSpeed < 0.0f) {
            shipCruiseSpeed = 0.0f;
        }
        mDoAud_shipCruiseSePlay(&current.pos, shipCruiseSpeed);
    }
    
    // This should probably use the mDoMtx_multVecZero inline, but it's not getting inlined
    // mDoMtx_multVecZero(mModel2->getAnmMtx(16), &eyePos);
    MtxP jnt_mtx;
    jnt_mtx = mModel2->getAnmMtx(16);
    eyePos.x = jnt_mtx[0][3];
    eyePos.y = jnt_mtx[1][3];
    eyePos.z = jnt_mtx[2][3];

    daPy_lk_c* link;
    link = daPy_getPlayerLinkActorClass();
    cXyz spCC;
    spCC = link->current.pos - current.pos;
    float distXz = (spCC.x * cM_ssin(shape_angle.y) + spCC.z * cM_scos(shape_angle.y));
    attention_info.flags = 0;
    BOOL bVar21 = FALSE;
    attention_info.position.set(eyePos.x, eyePos.y + 30.0f, eyePos.z);

    cXyz spC0;
    if (checkStateFlg(daSFLG_UNK1000000_e)) {
        spC0 = m1068 - eyePos;
        bVar21 = TRUE;
        offStateFlg(daSFLG_UNK1000000_e);
    }
    else if (m0428) {
        spC0 = *m0428 - eyePos;
        bVar21 = TRUE;
    } 
    else if ((mCurMode == 10 || mCurMode == 11) && m0434 && mRopeCnt > 0) {
            spC0 = *m0434 - eyePos;
            bVar21 = TRUE;
    }
    else if (mCurMode == 8 || distXz > 125.0f) {
        if (
            (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && (!dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02))) &&
            dComIfGp_getMiniGameType() != 1 && fopAcM_searchPlayerDistanceXZ2(this) < 250000.0f
        ) {
            spC0 = link->eyePos - eyePos;
            bVar21 = TRUE;
            attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
        }
    }
    else {
        attention_info.position = current.pos;
        if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && dComIfGs_isEventBit(0x908) && !checkStateFlg(daSFLG_UNK800000_e)) {
            if (dComIfGs_isEventBit(0x1980) || !dComIfGs_isEventBit(0x902)) {
                attention_info.flags = fopAc_Attn_ACTION_SHIP_e;
            }
            else {
                if (dComIfGs_isEventBit(0xA80)) {
                    cXyz* windVec = dKyw_get_wind_vec();
                    if (abs(cM_atan2s(windVec->x, windVec->z)) < 0x1000) {
                        attention_info.flags = fopAc_Attn_ACTION_SHIP_e;
                    }
                }
            }
        }
    }

    short sVar16;
    short sVar5;
    if (bVar21) {
        sVar16 = cM_atan2s(-spC0.y, spC0.absXZ()) - shape_angle.x;

        if (sVar16 > 0x2000) {
            sVar16 = 0x2000;
        }
        else if (sVar16 < -0x3000) {
            sVar16 = -0x3000;
        }

        sVar5 = cM_atan2s(spC0.x, spC0.z)- shape_angle.y;

        if (sVar5 > 0x7800) {
            sVar5 = 0x7800;
        }
        else if (sVar5 < -0x7800) {
            sVar5 = -0x7800;
        }

        sVar16 = sVar16 / 6;
        sVar5 = sVar5 / 6;
    }
    else {
        sVar16 = 0;
        sVar5 = 0;
    }

    if (sVar16 == 0 || cLib_distanceAngleS(sVar16, m03A0) > 0x100) {
        cLib_addCalcAngleS(&m03A0, sVar16, 10, 0x400, 4);
    }

    if (sVar5 == 0 || cLib_distanceAngleS(sVar5, m03A2) > 0x100) {
        cLib_addCalcAngleS(&m03A2, sVar5, 10, 0x400, 4);
    }

    if (mCurMode != 8 && checkForceMessage()) {
        attention_info.flags &= ~fopAc_Attn_ACTION_SHIP_e;
        cXyz spB4(attention_info.position - link->current.pos);
        if (
            (!dComIfGp_event_runCheck() && dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) ||
            (
                std::fabsf(current.pos.y - link->current.pos.y) < 50.0f &&
                spB4.abs2XZ() < 62500.0f &&
                fopAcM_seenPlayerAngleY(this) < 0x6000 &&
                mNextMessageNo != 0xD65
            )
        ) {
            fopAcM_orderSpeakEvent(this);
            offStateFlg(daSFLG_UNK400000_e);
            attention_info.flags |= (fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
        }
    }
    if (
        (dComIfGs_isEventBit(0x2D10) && !daPy_getPlayerLinkActorClass()->checkMasterSwordEquip()) ||
        (dComIfGs_isEventBit(0x3804) && !dComIfGs_isEventBit(0x2D02)) ||
        (dComIfGs_isEventBit(0x3E10) && !dComIfGs_isEventBit(0x3F80))
    ) {
        attention_info.flags &= ~fopAc_Attn_ACTION_SHIP_e;
    }
    if (mCurMode != 8 && dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        BOOL r24;
        r24 = TRUE;
        if (dComIfGs_isEventBit(0x1E40) && !dComIfGs_isEventBit(0x3840)) {
            mNextMessageNo = 0x168c;
        }
        else if (dComIfGs_isEventBit(0x2D02) && !dComIfGs_isEventBit(0x3201)) {
            mNextMessageNo = 0x1645;
        }
        else if (dComIfGs_isEventBit(0x1820) && !dComIfGs_isEventBit(0x3380)) {
            mNextMessageNo = 0x164d;
        }
        else if(dComIfGs_getTriforceNum() == 8 && !dComIfGs_isEventBit(0x3D04)) {
            mNextMessageNo = 0x1682;
        }
        else if (dComIfGs_isEventBit(0x3E40) && !dComIfGs_isEventBit(0x3E20)) {
            mNextMessageNo = 0x1683;
        }
        else {
            r24 = FALSE;
        }
        if (r24) {
            fopAcM_orderSpeakEvent(this);
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
            attention_info.flags |= (fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
            offStateFlg(daSFLG_UNK400000_e);
        }
    }

    mTillerAngleRate = m0366 * (1.0f / 0x2000);

    prev_speedF = (speedF * 0.1f) / 55.0f;

    if (prev_speedF > 0.05f) { 
        prev_speedF = 0.05f;
    }
    else if (prev_speedF < -0.05f) {
        prev_speedF = -0.05;
    }

    m03D4 += prev_speedF;
    
    if (m03D4 > 1.0f) {
        m03D4 -= 1.0f;
    }
    else if (m03D4 < 0.0f) {
        m03D4 += 1.0f;
    }

    cXyz spA8(current.pos - old.pos);

    if (speedF >= 0.0f) {
        mFwdVel = spA8.absXZ();
    }
    else {
        mFwdVel = -spA8.absXZ();
    }

    mFwdVel += (m1044.x * cM_ssin(current.angle.y) + m1044.z * cM_scos(current.angle.y));
    
    if (std::fabsf(mFwdVel) <= 0.01f || prev_fwdvel * mFwdVel < 0.0f || mFwdVel * speedF < 0.0f) {
        mWaveL.mState = 1;
        mWaveR.mState = 1;
        mSplash.mState = 1;
        mTrack.mState = 1;
    }

    setEffectData(m03F4, sp10);

    float sin = cM_ssin(shape_angle.y);
    float cos = cM_scos(shape_angle.y);
    
    dCcD_Cyl* cyl = mCyl;
        
    cXyz sp9C;
    for(int i = 0; i < 3; i++, cyl++) {
        sp9C.x = current.pos.x + sin * cyl_offset[i];
        sp9C.y = current.pos.y - 30.0f;
        sp9C.z = current.pos.z + cos * cyl_offset[i];
        cyl->SetC(sp9C);
        dComIfG_Ccsp()->Set(cyl);
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            cyl->SetTgGrp(cCcD_TgSPrm_IsPlayer_e);
        }
        else {
            cyl->SetTgGrp(cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e);
        }
    }

    cMtx_multVec(mpHeadAnm->getModel()->getAnmMtx(8), &sph_offset, &sp9C);

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        mSph.SetTgGrp(cCcD_TgSPrm_IsPlayer_e);
    }
    else {
        mSph.SetTgGrp(cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e);
    }

    mSph.SetC(sp9C);

    if (mCurMode != 9) {
        dComIfG_Ccsp()->Set(&mSph);
    }
    else {
        mSph.ResetTgHit();
    }

    if (mPart == PART_STEER_e) {
        dComIfGp_setPlayerStatus1(0, daPyStts1_SAIL_e);
        mDoAud_setShipSailState(1);
        
    }
    else {
        dComIfGp_clearPlayerStatus1(0, daPyStts1_SAIL_e);
        mDoAud_setShipSailState(0);
    }

    mNextMode = mCurMode;

    offStateFlg(daSFLG_UNK40000000_e);

    return TRUE;
}

/* 0000B9D4-0000B9F4       .text daShip_Execute__FP8daShip_c */
static BOOL daShip_Execute(daShip_c* i_this) {
    return ((daShip_c*)i_this)->execute();
}

/* 0000B9F4-0000B9FC       .text daShip_IsDelete__FP8daShip_c */
static BOOL daShip_IsDelete(daShip_c*) {
    return TRUE;
}

/* 0000B9FC-0000BB1C       .text shipDelete__8daShip_cFv */
BOOL daShip_c::shipDelete() {
    mWaveL.remove();
    mWaveR.remove();
    mSplash.remove();
    mTrack.remove();
    mRipple.remove();
    m1984.remove();
    m1998.remove();
    m19AC.remove();
    m19C0.remove();
    mDoAud_seDeleteObject(&mTillerTopPos);
    mDoAud_seDeleteObject(&m0444);
    mDoAud_seDeleteObject(&m102C);
    mDoAud_seDeleteObject(&m1020);
    mDoAud_seDeleteObject(&m1038);
    dComIfGp_clearPlayerStatus1(0, daPyStts1_SAIL_e);
    dComIfG_resDelete(&mPhs, l_arcName);
    return TRUE;
}

/* 0000BB1C-0000BB40       .text daShip_Delete__FP8daShip_c */
static BOOL daShip_Delete(daShip_c* i_this) {
    ((daShip_c*)i_this)->shipDelete();
    return TRUE;
}

/* 0000BB40-0000BFB8       .text createHeap__8daShip_cFv */
BOOL daShip_c::createHeap() {
    J3DModelData* modelData;
    
    if (checkStateFlg(daSFLG_SAIL_ON_e)) {
        m0392 = SHIP_BCK_FN_MAST_ON2;
    }
    else {
        m0392 = SHIP_BCK_FN_MAST_OFF2;
    }
    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, SHIP_BDL_FN_BODY);
    JUT_ASSERT(0x1B5C, modelData != 0);

    mpBodyAnm = new mDoExt_McaMorf(
        modelData, NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes(l_arcName, m0392),
        J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 0, NULL,
        0x80000, 0x11200202
    );

    if (mpBodyAnm && mpBodyAnm->getModel()) {
        J3DModel* pModel = mpBodyAnm->getModel();
        J3DSkinDeform* mSkinDeform = new J3DSkinDeform();
        if (mSkinDeform == NULL) {
            return FALSE;
        }

        if (pModel->setSkinDeform(mSkinDeform, 1) != J3DErrType_Success) {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, SHIP_BDL_VFNCN);
    JUT_ASSERT(0x1B81, modelData != 0);
    mpCannonModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
    
    if (mpCannonModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, SHIP_BDL_VFNCR);
    JUT_ASSERT(0x1B8E, modelData != 0);
    mpSalvageArmModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);

    if (mpSalvageArmModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes("Link", LINK_BDL_ROPEEND);
    JUT_ASSERT(0x1B9B, modelData != 0);
    mpLinkModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);

    if (mpLinkModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, SHIP_BDL_FN_HEAD_H);
    JUT_ASSERT(0x1BA8, modelData != 0);

    m03B4 = SHIP_BCK_FN_LOOK_L;

    mpHeadAnm = new mDoExt_McaMorf(
        modelData, NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes(l_arcName, SHIP_BCK_FN_LOOK_L),
        J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, 0, NULL,
        0x80000, 0x11000002
    );

    if (mpHeadAnm == NULL || mpHeadAnm->getModel() == NULL) {
        return FALSE;
    }
    mpHeadAnm->setMorf(3.0f);
    if (mRopeLine.init(1, 0xFA, (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE), 0)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0000BFB8-0000BFD8       .text daShip_createHeap__FP10fopAc_ac_c */
static BOOL daShip_createHeap(fopAc_ac_c* i_this) {
    return ((daShip_c*)i_this)->createHeap();
}

/* 0000BFD8-0000C790       .text create__8daShip_cFv */
cPhs_State daShip_c::create() {
    J3DModel* pModel;
    J3DMaterial* pMaterial;
    J3DModelData* pModelData;
    s32 res;

    static dCcD_SrcCyl cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsPlayer_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e| cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK23,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 75.0f,
            /* Height */ 115.0f,
        },
    };
    
    static dCcD_SrcSph sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsPlayer_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e| cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK23,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 75.0f,
        },
    };
    
    fopAcM_SetupActor(this, daShip_c);
    
    if (!dComIfGs_isEventBit(dSv_evtBit_c::MET_KORL)) {
        return cPhs_ERROR_e;
    }
    
    res = dComIfG_resLoad(&mPhs, l_arcName);

    if (((fopAcM_GetParam(this) >> 8) & 0xFF) == 1) {
        m03E8 = 1.0f;
        onStateFlg(daSFLG_SAIL_ON_e);
    }
    else {
        m03E8 = 0.001f;
        offStateFlg(daSFLG_SAIL_ON_e);
    }

    if (res == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, daShip_createHeap, 0x20000)) {
            return cPhs_ERROR_e;
        }
        
        mpBodyAnm->setFrame(mpBodyAnm->getEndFrame());
        
        pModel = mpBodyAnm->getModel();
        pModelData = pModel->getModelData();
        
        pModel->setUserArea(reinterpret_cast<u32>(this));
        
        fopAcM_SetMtx(this, pModel->getBaseTRMtx());
        
        for (u16 jno = 0; jno < pModelData->getJointNum(); jno++) {
            if ((jno == 10) || (jno == 5) || (jno == 7) || (jno == 6)) {
                pModelData->getJointTree().getJointNodePointer(jno)->setCallBack(daShip_bodyJointCallBack);
            }
        }

        for (u16 mno = 0; mno < pModelData->getMaterialNum(); mno++) {
            pMaterial = pModelData->getMaterialNodePointer(mno);
            for(u32 i = 0; i < 8; i++) {
                J3DTexGenBlock* pTexGenBlock = pMaterial->getTexGenBlock();
                J3DTexMtx* pTexMtx = pTexGenBlock->getTexMtx(i);
                if (pTexMtx && pTexMtx->getTexMtxInfo().mInfo == 8) {
                    m02A0 = pTexMtx;
                    m02A4 = pTexMtx;
                }
            }
        }

        C_MTXOrtho(m02A8, 50.0f, -50.0f, -50.0f, 50.0f, 0.1f, 100000.0f);
        
        pModel = mpHeadAnm->getModel();
        pModelData = pModel->getModelData();
        
        pModel->setUserArea(reinterpret_cast<u32>(this));
        
        for (u16 jno = 0; jno < pModelData->getJointNum(); jno++) {
            if (jno == 8 || jno == 10) {
                pModelData->getJointTree().getJointNodePointer(jno)->setCallBack(daShip_headJointCallBack0);
            }
            else if (
                !(jno != 2 && jno != 3 && jno != 4 && jno != 5 && jno != 6) || (jno == 7)
                // Should probably be written as
                // jno == 2 || jno == 3 || jno == 4 || jno == 5 || jno == 6 || jno == 7
                // But the compiler optimizes that differently
            ) {
                pModelData->getJointTree().getJointNodePointer(jno)->setCallBack(daShip_headJointCallBack1);
            }
        }
        
        mpCannonModel->setUserArea(reinterpret_cast<u32>(this));
        
        pModelData = mpCannonModel->getModelData();
        
        pModelData->getJointTree().getJointNodePointer(1)->setCallBack(daShip_cannonJointCallBack);
        pModelData->getJointTree().getJointNodePointer(2)->setCallBack(daShip_cannonJointCallBack);
        
        mpSalvageArmModel->setUserArea(reinterpret_cast<u32>(this));
        mpSalvageArmModel->getModelData()->getJointTree().getJointNodePointer(1)->setCallBack(daShip_craneJointCallBack);
        
        m034B = fopAcM_GetParam(this);
        mPart = PART_WAIT_e;
        mTornadoID = fpcM_ERROR_PROCESS_ID_e;
        mTornadoActor = NULL;
        mWhirlID = fpcM_ERROR_PROCESS_ID_e;
        mWhirlActor = NULL;
        
        if (mNextMode != MODE_START_MODE_WARP_e) {
            mTactWarpID = fpcM_ERROR_PROCESS_ID_e;
        }
        
        if (checkStateFlg(daSFLG_SAIL_ON_e) != 0) {
            mPart = PART_STEER_e;
            procSteerMove_init();
        }
        else {
            if (mNextMode == MODE_PADDLE_MOVE_e) {
                procPaddleMove_init();
            }
            else if (mNextMode == MODE_START_MODE_WARP_e) {
                procStartModeWarp_init();
            }
            else if (mNextMode == MODE_START_MODE_THROW_e) {
                procStartModeThrow_init();
            }
            else {
                procWait_init();
            }
        }

        if ((dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SEA_e) || !strcmp(dComIfGp_getStartStageName(), "Hyrule") || !strcmp(dComIfGp_getStartStageName(), "Ocean")) {
            m03CC = 4;
        }
        else {
            m03CC = 3;
        }
        
        mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, m03CC, &mAcchCir[0], fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
        
        mAcchCir[0].SetWall(0.0f, 250.0f);
        mAcchCir[1].SetWall(75.0f, 250.0f);
        mAcchCir[2].SetWall(150.0f, 250.0f);
        mAcchCir[3].SetWall(-600.0f-current.pos.y, 250.0f);

        mAcch.ClrWaterNone();
        mAcch.SetWaterCheckOffset(10000.0f);

        attention_info.flags = 0;
        attention_info.position = current.pos;

        gravity = -2.5f;
        maxFallSpeed = -150.0f;
        mGridID = fopAcM_create(PROC_GRID, 1, &current.pos, -1, &current.angle);

        if (mGridID == fpcM_ERROR_PROCESS_ID_e) {
            return cPhs_ERROR_e;
        }

        mTactWarpPosNum = -1;
        m03E0 = 10000.0f;
        mStts.Init(0xF0, 0, this);

        dCcD_Cyl* cyl = mCyl;
        for (int i = 0; i < 3; i++, cyl++) {
            cyl->Set(cyl_src);
            cyl->SetStts((&mStts));
        }

        mCyl[1].SetR(95.0f);
        mSph.Set(sph_src);
        mSph.SetStts(&mStts);

        cull.box.min.x = -325.0f;
        cull.box.min.y = -50.0f;
        cull.box.min.z = -325.0f;
        cull.box.max.x = 325.0f;
        cull.box.max.y = 570.0f;
        cull.box.max.z = 240.0f;
        
        fopKyM_create(PROC_WIND_ARROW, (s32)this, 0, 0, 0);

        offStateFlg(daSFLG_UNK2_e);
        mAcch.CrrPos(*dComIfG_Bgsp());

        setRoomInfo();

        m03F4 = getWaterY();
        
        if (mCurMode == MODE_START_MODE_WARP_e) {
            current.pos.y = m03F4 + 5000.0f;
        }
        else if (mCurMode == MODE_START_MODE_THROW_e) {
            current.pos.y = m03F4 + 2500.0f;
        }

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
        
        mpBodyAnm->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        mpBodyAnm->play(NULL, 0, 0);
        mpBodyAnm->calc();
        
        cMtx_multVec(mpBodyAnm->getModel()->getAnmMtx(10), &l_tiller_top_offset, &mTillerTopPos);
        
        mpHeadAnm->play(NULL, 0, 0);
        mpHeadAnm->getModel()->setBaseTRMtx(mpBodyAnm->getModel()->getAnmMtx(4));
        mpHeadAnm->calc();
        
        dComIfGp_setShipActor(this);
        
        mTrack.mMinVel = 3.0f;
        mWaveL.mMaxParticleVelocity = 40.0f;
        mWaveR.mMaxParticleVelocity = 40.0f;
        m19C0.mRate = 0.0f;

        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SEA_e) {
            fopAcM_createChild(PROC_Coming2, fopAcM_GetID(this), 0, &current.pos, -1, NULL);
        }
    }
    return res;
}

/* 0000D018-0000D038       .text daShip_Create__FP10fopAc_ac_c */
static cPhs_State daShip_Create(fopAc_ac_c* i_this) {
    return ((daShip_c*)i_this)->create();
}

static actor_method_class l_daShip_Method = {
    (process_method_func)daShip_Create,
    (process_method_func)daShip_Delete,
    (process_method_func)daShip_Execute,
    (process_method_func)daShip_IsDelete,
    (process_method_func)daShip_Draw,
};

actor_process_profile_definition g_profile_SHIP = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0004,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SHIP,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daShip_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_SHIP,
    /* Actor SubMtd */ &l_daShip_Method,
    /* Status       */ 0x02 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
