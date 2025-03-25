/**
 * d_a_ship.cpp
 * King of Red Lions
 */

#include "d/actor/d_a_ship.h"
#include "d/d_procname.h"
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

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

static char l_arcName[5] = "Ship";
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
    J3DModel *pModel = this->m0298->getModel();
    
    if ((jno == 10) || (jno == 5)) {
        cMtx_ZrotS(mDoMtx_stack_c::get(), this->m0366);
    }
    else if (jno == 7) {
        cMtx_ZrotS(mDoMtx_stack_c::get(), -this->m0364);
    }
    else if (jno == 6) {
        cMtx_ZrotS(mDoMtx_stack_c::get(), 0xC000);
        cMtx_concat(pModel->getAnmMtx(jno), mDoMtx_stack_c::get(), mDoMtx_stack_c::get());
        this->mpSalvageArmModel->setBaseTRMtx(mDoMtx_stack_c::get());
        cMtx_YrotM(mDoMtx_stack_c::get(), -0x8000);
        this->mpCannonModel->setBaseTRMtx(mDoMtx_stack_c::get());
        cMtx_scale(mDoMtx_stack_c::get(), this->m03E8, this->m03E8, this->m03E8);
    }
    cMtx_concat(pModel->getAnmMtx(jno), mDoMtx_stack_c::get(), mDoMtx_stack_c::get());
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
        cMtx_XrotS(mDoMtx_stack_c::get(), this->m0394);
    }
    else {
        cMtx_YrotS(mDoMtx_stack_c::get(), -this->m0396);
    }
    cMtx_concat(this->mpCannonModel->getAnmMtx(jno), mDoMtx_stack_c::get(), mDoMtx_stack_c::get());
    this->mpCannonModel->setAnmMtx(jno, mDoMtx_stack_c::get());
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
    mDoMtx_stack_c::ZrotS(-(this->m0398 + this->m039C));
    mDoMtx_stack_c::revConcat(this->mpSalvageArmModel->getAnmMtx(1));
    this->mpSalvageArmModel->setAnmMtx(1, mDoMtx_stack_c::get());
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
    if (this->mAnmTransform) {
        tempAnmTransform = this->m029C->getAnm();
        this->m029C->mpAnm = this->mAnmTransform;
        this->mAnmTransform = tempAnmTransform;
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
    MtxP jointAnmMtx = this->m029C->getModel()->getAnmMtx(jno);
    float fVar1 = jointAnmMtx[0][3];
    float fVar2 = jointAnmMtx[1][3];
    float fVar3 = jointAnmMtx[2][3];
    
    short sVar5 = this->shape_angle.y + this->m03A2 * (jno + -2);
    mDoMtx_stack_c::YrotS(sVar5);
    mDoMtx_ZXYrotM(mDoMtx_stack_c::get(), this->m03A0, this->m03A2, 0);
    mDoMtx_stack_c::YrotM(-sVar5);
    mDoMtx_stack_c::concat(this->m029C->getModel()->getAnmMtx(jno));
    
    mDoMtx_stack_c::get()[0][3] = fVar1;
    mDoMtx_stack_c::get()[1][3] = fVar2;
    mDoMtx_stack_c::get()[2][3] = fVar3;

    this->m029C->getModel()->setAnmMtx(jno, mDoMtx_stack_c::get());
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
    J3DModel* model = this->m0298->getModel();
    J3DModel* model_00 = this->m029C->getModel();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &this->current.pos, &this->tevStr);
    g_env_light.setLightTevColorType(model, &this->tevStr);
    g_env_light.setLightTevColorType(model_00, &this->tevStr);

    dComIfGd_setListP1();
    
    if (this->m02A0 && this->m02A4) {
        j3dSys.onFlag(0x4);
        j3dSys.onFlag(0x8);
        
        cXyz local_5c(this->current.pos.x, this->current.pos.y + this->m03D8 + 5.0f, this->current.pos.z);
        
        f32 x = local_5c.x;
        f32 y = local_5c.y;
        f32 z = local_5c.z;
        z += cM_scos(this->m037C) * 10000.0f * cM_scos(this->shape_angle.y);
        y -= cM_ssin(this->m037C) * 10000.0f;
        x += cM_scos(this->m037C) * 10000.0f * cM_ssin(this->shape_angle.y);
        cXyz local_68(x, y, z);
        Mtx MStack_50;
        cMtx_lookAt(MStack_50, &local_5c, &local_68, this->m037E);
        mDoMtx_stack_c::YrotS(0xC000);
        mDoMtx_stack_c::XrotM(-0x8000);
        mDoMtx_stack_c::scaleM(1.0f, 2.0f, 0.25f);
        mDoMtx_stack_c::concat(MStack_50);
        mDoMtx_stack_c::revConcat(this->m02A8);
        this->m02A0->setEffectMtx(mDoMtx_stack_c::get());
        this->m02A4->setTranslationX(this->m03D4);
    }

    if (dComIfGp_checkPlayerStatus0(0, 0x10000) == 0 || dComIfGp_getAttention().Lockon() || daPy_getPlayerLinkActorClass()->getBodyAngleX() > -0x1000) {
        mDoExt_modelEntryDL(model);
    }

    if (dComIfGp_checkPlayerStatus0(0, 0x10000) == 0 || daPy_getPlayerLinkActorClass()->checkNoControll() || dComIfGp_checkCameraAttentionStatus(0, 0x22) == 0) {
        offStateFlg(daSFLG_HEAD_NO_DRAW_e);
        mDoExt_modelEntryDL(model_00);
    }
    else {
        onStateFlg(daSFLG_HEAD_NO_DRAW_e);
    }
    
    if (this->mShipMode == 2) { //UsingCannon
        g_env_light.setLightTevColorType(this->mpCannonModel, &this->tevStr);
        mDoExt_modelEntryDL(this->mpCannonModel);
    }
    else if (this->mShipMode == 3) { //UsingSalvageArm
        g_env_light.setLightTevColorType(this->mpSalvageArmModel, &this->tevStr);
        mDoExt_modelEntryDL(this->mpSalvageArmModel);
        if (this->mCurrentRopeSegmentIndex >= 2) {
            this->mRopeLine.update(this->mCurrentRopeSegmentIndex, 5.0f, rope_color, 0, &this->tevStr);
            dComIfGd_set3DlineMat(&this->mRopeLine);
        }
        g_env_light.setLightTevColorType(this->mpLinkModel, &this->tevStr);
        mDoExt_modelUpdateDL(this->mpLinkModel);
    }

    dComIfGd_setList();

    this->mShadowId = dComIfGd_setShadow(this->mShadowId, 0, model, &this->current.pos, 1500.0f, 250.0f,
                                         this->current.pos.y, this->mAcch.GetGroundH(), this->mAcch.m_gnd, 
                                         &this->tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
                                         
    if (this->mShadowId != 0) {
        dComIfGd_addRealShadow(this->mShadowId, model_00);
        if (this->mShipMode == UsingCannon) {
            dComIfGd_addRealShadow(this->mShadowId, this->mpCannonModel);
        }
        else if (this->mShipMode == 3) { //UsingSalvageArm
            dComIfGd_addRealShadow(this->mShadowId, this->mpSalvageArmModel);
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
        this->mNextMessageID = 0x5E0;
    }
    else if (dComIfGs_isSymbol(1) && !dComIfGs_isEventBit(0xA80)) {
        this->mNextMessageID = 0x5EC;
    }
    else if (dComIfGs_isSymbol(2) && !dComIfGs_isEventBit(0xA08)) {
        this->mNextMessageID = 0x5F6;
    }
    else if (dComIfGs_isEventBit(0xA02) && !dComIfGs_isEventBit(0xA01)) {
        this->mNextMessageID = 0x607;
    }
    else if (dComIfGs_checkGetItem(dItem_BOMB_BAG_e) && !dComIfGs_isEventBit(0x1F02)) {
        this->mNextMessageID = 0x624;
    }
    else if (dComIfGs_isSymbol(0) && !dComIfGs_isEventBit(0x2F20)) {
        this->mNextMessageID = 0xD5A;
    }
    else if (dComIfGs_isEventBit(0x2D10) && !daPy_getPlayerActorClass()->checkMasterSwordEquip()) {
        this->mNextMessageID = 0xD65;
    }
    else if (dComIfGs_isEventBit(0x3E01) && !dComIfGs_isEventBit(0x3F80)) {
        this->mNextMessageID = 0x1688;
    }
    else if (dComIfGs_isEventBit(0x2D02) && !dComIfGs_isEventBit(0x3201)) {
        this->mNextMessageID = 0x1645;
    }
    else {
        return FALSE;
    }
    return TRUE;
}

/* 00000DAC-00001734       .text setInitMessage__8daShip_cFv */
void daShip_c::setInitMessage() {
    if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
        return;
    }
    else if (dComIfGs_isGetItem(1, 0) == 0) {
        this->mNextMessageID = 0x5de;
    }
    else if (checkForceMessage()) {
        return;
    }
    else if (dComIfGs_isEventBit(0x2110) && !dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) {
        this->mNextMessageID = 0x623;
    }
    else if (checkStateFlg(daSFLG_UNK800000_e)) {
        this->mNextMessageID = 0x636;
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
            this->mNextMessageID = 0xd77;
        }
        else {
            this->mNextMessageID = 0xd78;
        }
    }
    else if (dComIfGs_isEventBit(0x2C02)) {
        this->mNextMessageID = 0xd76;
    }
    else if (dComIfGs_isEventBit(0x2C01)) {
        this->mNextMessageID = 0xd75;
    }
    else if (dComIfGs_isEventBit(0x2D08)) {
        if (strcmp(dComIfGp_getStartStageName(), "Hyrule") == 0) {
            this->mNextMessageID = 0xd74;
        }
        else {
            this->mNextMessageID = 0xd73;
        }
    }
    else if (dComIfGs_isEventBit(0x4004)) {
        if (dComIfGs_getTriforceNum() == 8) {
            this->mNextMessageID = 0xd72;
        }
        else {
            this->mNextMessageID = 0xd71;
        }
    }
    else if (dComIfGs_isEventBit(0x2E02)) {
        this->mNextMessageID = 0xd70;
    }
    else if (dComIfGs_isEventBit(0x1610)) {
        this->mNextMessageID = 0xd6f;
    }
    else if (dComIfGs_isEventBit(0x3A02)) {
        if (dComIfGs_isTact(4)) {
            this->mNextMessageID = 0xd6e;
        }
        else {
            this->mNextMessageID = 0xd6d;
        }
    }
    else if (dComIfGs_isEventBit(0x2E04)) {
        this->mNextMessageID = 0xd6c;
    }
    else if (dComIfGs_isEventBit(0x1620)) {
        this->mNextMessageID = 0xd6b;
    }
    else if (dComIfGs_isTact(3) || dComIfGs_isTact(4)) {
        this->mNextMessageID = 0xd6a;
    }
    else if (dComIfGs_isEventBit(0x3910)) {
        if (dComIfGs_isEventBit(0x3380) == 0) {
            this->mNextMessageID = 0xd7b;
        }
        else {
            this->mNextMessageID = 0xd69;
        }
    }
    else if (dComIfGs_isEventBit(0x3040)) {
        this->mNextMessageID = 0xd68;
    }
    else if (dComIfGs_isEventBit(0x3810)) {
        this->mNextMessageID = 0xd67;
    }
    else if (daPy_getPlayerActorClass()->checkMasterSwordEquip()) {
        this->mNextMessageID = 0xd66;
    }
    else if (dComIfGs_isEventBit(0x2D10)) {
        this->mNextMessageID = 0xd65;
    }
    else if (dComIfGs_isEventBit(0x1E40)) {
        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == 1) {
            this->mNextMessageID = 0xd63;
        }
        else {
            this->mNextMessageID = 0xd64;
        }
    }
    else if (dComIfGs_isEventBit(0x2F20)) {
        this->mNextMessageID = 0xd62;
    }
    else if (dComIfGs_isSymbol(0)) {
        this->mNextMessageID = 0xd5a;
    }
    else if (dComIfGs_isEventBit(0x1940)) {
        this->mNextMessageID = 0xd61;
    }
    else if (dComIfGs_isEventBit(0x3E10)) {
        if (!dComIfGs_isEventBit(0x3E01)) {
            this->mNextMessageID = 0x1687;
        }
        else {
            if (dComIfGs_isEventBit(0x3F80)) {
                this->mNextMessageID = 0x1689;
            }
            else {
                this->mNextMessageID = 0x1688;
            }
        }
    }
    else if (dComIfGs_isEventBit(0x1F02)) {
        this->mNextMessageID = 0xd60;
    }
    else if (dComIfGs_isEventBit(0x1F04)) {
        if (!dComIfGs_isEventBit(0x2110)) {
            this->mNextMessageID = 0x621;
        }
        else {
            if (dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) {
                this->mNextMessageID = 0x624;
            }
            else {
                this->mNextMessageID = 0x623;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA02)) {
        if (dComIfGs_isEventBit(0x2A01)) {
            this->mNextMessageID = 0xd5f;
        }
        else {
            if (dComIfGs_isEventBit(0xA01)) {
                this->mNextMessageID = 0x608;
            }
            else {
                this->mNextMessageID = 0x607;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA08)) {
        if (dComIfGs_isEventBit(0x2A02)) {
            this->mNextMessageID = 0xd5e;
        }
        else {
            if (dComIfGs_isEventBit(0xA04)) {
                this->mNextMessageID = 0x5f9;
            }
            else {
                this->mNextMessageID = 0x5f8;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA20)) {
        if (dComIfGs_isSymbol(2)) {
            this->mNextMessageID = 0x5f6;
        }
        else {
            if (dComIfGs_isEventBit(0x2B80)) {
                this->mNextMessageID = 0x5f5;
            }
            else {
                this->mNextMessageID = 0x5f4;
            }
        }
    }
    else if (dComIfGs_isEventBit(0xA80)) {
        if (dComIfGs_isEventBit(0x1980)) {
            this->mNextMessageID = 0xd5d;
        }
        else {
            cXyz* windVec = dKyw_get_wind_vec();
            if (abs(cM_atan2s(windVec->x, windVec->z)) < 0x1000) {
                this->mNextMessageID = 0x5ee;
            }
            else {
                this->mNextMessageID = 0x5ef;
            }
        }
    }
    else if (dComIfGs_isEventBit(0x902)) {
        if (dComIfGs_isSymbol(1)) {
            this->mNextMessageID = 0x5ec;
        }
        else {
            if (dComIfGs_isEventBit(0xA10)) {
                this->mNextMessageID = 0x5eb;
            }
            else {
                this->mNextMessageID = 0x5ea;
            }
        }
    }
    else {
        if (dComIfGs_isEventBit(0x2A08)) {
            this->mNextMessageID = 0xd5c;
        }
        else {
            if (dComIfGs_isEventBit(0x908)) {
                this->mNextMessageID = 0x5df;
            }
            else {
                this->mNextMessageID = 0x5e0;
            }
        }
    }
    return;
}

/* 00001734-00001BD0       .text setNextMessage__8daShip_cFP9msg_class */
BOOL daShip_c::setNextMessage(msg_class* msg) {
    uint currMessageID;
    
    currMessageID = this->mNextMessageID;
    if ((((((currMessageID != 0x5dd) && (currMessageID != 0x5de)) && (currMessageID != 0x5df)) &&
         (((currMessageID != 0x5eb && (currMessageID != 0x5ee)) &&
          ((currMessageID != 0x5ef && ((currMessageID != 0x5f5 && (currMessageID != 0x5f9)))))))) &&
        ((currMessageID != 0x608 &&
         ((((((currMessageID != 0x609 && (currMessageID != 0x60a)) && (currMessageID != 0x621)) &&
            ((currMessageID != 0x623 && (currMessageID != 0x636)))) &&
           ((currMessageID < 0xd5c || (currMessageID > 0xd78)))) &&
          ((currMessageID != 0xd7b && (currMessageID != 0x164c)))))))) &&
       ((currMessageID != 0x1650 &&
        ((((currMessageID != 0x1651 && (currMessageID != 0x1684)) && (currMessageID != 0x1685)) &&
         ((currMessageID != 0x1687 && (currMessageID != 0x1689)))))))) {
        if (currMessageID == 0x5e4) {
            dComIfGs_onEventBit(0x908);
        }
        else if (currMessageID == 0x5ea) {
            dComIfGs_onEventBit(0xa10);
        }
        else if (currMessageID == 0x5ed) {
            dComIfGs_onEventBit(0xa80);
        }
        else if (currMessageID == 0x5f4) {
            dComIfGs_onEventBit(0x2b80);
        }
        else if (currMessageID == 0x5f7) {
            dComIfGs_onEventBit(0xa08);
        }
        else if (currMessageID == 0x5f8) {
            dComIfGs_onEventBit(0xa04);
        }
        else if (currMessageID == 0x607) {
            dComIfGs_onEventBit(0xa01);
        }
        else if (currMessageID == 0x622) {
            dComIfGs_onEventBit(0x1f01);
        }
        else if (currMessageID == 0x624) {
            dComIfGs_onEventBit(0x1f02);
        }
        else if (currMessageID == 0xd5b) {
            dComIfGs_onEventBit(0x2f20);
        }
        else if (currMessageID == 0x1682) {
            dComIfGs_onEventBit(0x3d04);
            this->mNextMessageID = 0;
        }
        else if (currMessageID == 0x1688) {
            dComIfGs_onEventBit(0x3f80);
        }
        else {
            if (currMessageID == 0x168c) {
                dComIfGs_onEventBit(0x3840);
            }
            else {
                if (currMessageID == 0x5e0) {
                    this->mNextMessageID = 0x5e1;
                }
                else if (currMessageID == 0x5e1) {
                    this->mNextMessageID = 0x5e2;
                }
                else if (currMessageID == 0x5e2) {
                    if (msg->mSelectNum == 0) {
                        this->mNextMessageID = 0x5e4;
                    }
                    else {
                        this->mNextMessageID = 0x5e3;
                    }
                }
                else if (currMessageID == 0x5e3) {
                    this->mNextMessageID = 0x5e1;
                }
                else if (currMessageID == 0x5ec) {
                    this->mNextMessageID = 0x5ed;
                }
                else if (currMessageID == 0x5f6) {
                    this->mNextMessageID = 0x5f7;
                }
                else if (currMessageID == 0xd5a) {
                    this->mNextMessageID = 0xd5b;
                }
                else if (currMessageID == 0x1645) {
                    this->mNextMessageID = 0x1646;
                }
                else if (currMessageID == 0x1646) {
                    this->mNextMessageID = 0x1647;
                }
                else if (currMessageID == 0x1647) {
                    this->mNextMessageID = 0x1648;
                }
                else if (currMessageID == 0x1648) {
                    this->mNextMessageID = 0x1649;
                }
                else if (currMessageID == 0x1649) {
                    this->mNextMessageID = 0x164a;
                }
                else if (currMessageID == 0x164a) {
                    this->mNextMessageID = 0x164b;
                }
                else if (currMessageID == 0x164b) {
                    dComIfGs_onEventBit(0x3201);
                    this->mNextMessageID = 0x164c;
                }
                else if (currMessageID == 0x164d) {
                    this->mNextMessageID = 0x164e;
                }
                else if (currMessageID == 0x164e) {
                    this->mNextMessageID = 0x164f;
                }
                else if (currMessageID == 0x164f) {
                    dComIfGs_onEventBit(0x3380);
                    if (dComIfGs_getTriforceNum() > 0) {
                        this->mNextMessageID = 0x1650;
                    }
                    else {
                        this->mNextMessageID = 0x1651;
                    }
                }
                else if (currMessageID == 0x1683) {
                    dComIfGs_onEventBit(0x3e20);
                    if (dComIfGs_getItem(12) != 0xFF) { //InvalidItem
                        this->mNextMessageID = 0x1685;
                    }
                    else {
                        this->mNextMessageID = 0x1684;
                    }
                }
                return FALSE;
            }
        }
    }
    return TRUE;
}

/* 00001BD0-00001C24       .text seStart__8daShip_cFUlP4cXyz */
void daShip_c::seStart(unsigned long i_seNum, cXyz* i_sePos) {
    mDoAud_seStart(i_seNum, i_sePos, 0, this->m034A);
    return;
}

/* 00001C24-00001D50       .text setSailAngle__8daShip_cFv */
void daShip_c::setSailAngle() {
    short sVar1;
    cXyz* windVec = dKyw_get_wind_vec();
    if (this->mTornadoActor) {
        sVar1 = (short)(this->m03AA + 0x4000) - this->shape_angle.y;
    }
    else {
        sVar1 = cM_atan2s(windVec->x, windVec->z) - this->shape_angle.y;
    }
    if (sVar1 > 0x800) {
        this->m0380 = -0x1555;
    }
    else {
        if (sVar1 < -0x800) {
            this->m0380 = 0x1555;
        }
        else if (this->m0380 == 0) {
            if (sVar1 >= 0) {
                this->m0380 = -0x1555;
            }
            else {
                this->m0380 = 0x1555;
            }
        }
    }
    cLib_addCalcAngleS(&this->m0364, this->m0380, 0x10, 0x800, 0x20);
    this->m0378 = this->m0364 >> 1;
    if (this->m0364 * this->m0380 < 0) {
        if (checkStateFlg(daSFLG_UNK2_e) == 0) {
            seStart(0x2825, &this->m0444);
            onStateFlg(daSFLG_UNK2_e);
        }
    }
    else {
        offStateFlg(daSFLG_UNK2_e);
    }
    return;
}

/* 00001D50-00001E08       .text setControllAngle__8daShip_cFs */
void daShip_c::setControllAngle(short angle) {
    short sVar1 = angle - this->m036C;
    short sVar2 = sVar1 * 0.05f;
    if (sVar2 == 0) {
        if (sVar1 > 0) {
            sVar2 = 1;
        }
        else if (sVar1 < 0) {
            sVar2 = -1;
        }
    }
    this->m036E += sVar2;
    this->m036C += this->m036E;
    cLib_addCalcAngleS(&this->m036E, 0, 0x14, 0x1000, 4);
    return;
}

/* 00001E08-00001E9C       .text getMaxWaterY__8daShip_cFP4cXyz */
void daShip_c::getMaxWaterY(cXyz* shipPos) {    
    if (daSea_ChkArea(shipPos->x, shipPos->z) & 0xff) {
        shipPos->y = daSea_calcWave(shipPos->x, shipPos->z);
        if (this->m03F8 > shipPos->y) {
            shipPos->y = this->m03F8;
        }
    }
    else {
        if (this->m03F8 != -1e+09f) {
            shipPos->y = this->m03F8;
        }
        else {
            shipPos->y = this->m03F4;
        }
    }
    return;
}

/* 00001E9C-00002314       .text setWaveAngle__8daShip_cFPsPs */
void daShip_c::setWaveAngle(short* param1, short* param2) {
    static cXyz local_front(0.0f, 0.0f, 180.0f);
    static cXyz local_back(0.0f, 0.0f, -190.0f);
    static cXyz local_right(-80.0f, 0.0f, 0.0f);
    static cXyz local_left(80.0f, 0.0f, 0.0f);

    mDoMtx_stack_c::transS(this->current.pos);
    
    mDoMtx_ZXYrotM(mDoMtx_stack_c::get(), this->shape_angle.x, this->shape_angle.y, this->shape_angle.z);

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

    *param2 = cM_atan2s(-local_a8.y, cXyz(local_a8.x, 0.0f, local_a8.z).abs());
    *param1 = cM_atan2s(-local_9c.y, cXyz(local_9c.x, 0.0f, local_9c.z).abs());
    
    short iVar3 = *param1 - this->m0370;
    short iVar2 = *param2 - this->m0372;
    
    this->m0376 += (iVar2 * 0.045f);
    this->m0372 += this->m0376;
    
    cLib_addCalcAngleS(&this->m0376, 0, 0x14, 0x1000, 4);
    this->m0374 += (iVar3 * 0.045f);
    this->m0370 += this->m0374;
    cLib_addCalcAngleS(&this->m0374, 0, 0x14, 0x1000, 4);
    return;
}

/* 00002314-000023E0       .text getWaterY__8daShip_cFv */
f32 daShip_c::getWaterY() {
    float waterY;
    s32 waterHit = this->mAcch.ChkWaterHit();
    if (waterHit) {
        this->m03F8 = this->mAcch.m_wtr.GetHeight();
    }
    else {
        this->m03F8 = -1e9f;
    }
    if (daSea_ChkArea(this->current.pos.x, this->current.pos.z) & 0xff) {
        waterY = daSea_calcWave(this->current.pos.x, this->current.pos.z);
        if (!waterHit || waterY > this->m03F8) {
            return waterY;
        }
    }
    if (waterHit) {
        waterY = this->m03F8;
    }
    else {
        daPy_lk_c* link = daPy_getPlayerLinkActorClass();
        if (link && link->mDemo.getDemoMode() == 0x44 ) {
            waterY = 0.0f;
        }
        else {
            waterY = this->m03F4;
        }
    }
    return waterY;
}

/* 000023E0-00002824       .text setYPos__8daShip_cFv */
void daShip_c::setYPos() {
    float fVar5;
    float fVar4;
    float fVar2;
    
    this->m03F4 = getWaterY();
    if (!checkStateFlg(daSFLG_UNK10_e)) {
        onStateFlg(daSFLG_UNK10_e);
        if (!(this->m034C == 13 || this->m034C == 16 || this->m0351 == 11)) {
            this->current.pos.y = this->m03F4;
        }
    }

    if (this->m034C == 12 || this->m034C == 15 || this->m034C == 14) {
        return;
    }

    fVar2 = this->m03F4 - this->current.pos.y;
    
    if (checkStateFlg(daSFLG_UNK1_e)) {
        if (this->mStateFlag == 13 || this->mStateFlag == 16) {
            return;
        }
        if (fVar2 >= 0.0f && !(onStateFlg(daSFLG_UNK80_e), checkStateFlg(daSFLG_UNK2000000_e))) {
            offStateFlg(daSFLG_UNK1_e);
            if (this->speed.y < -15.0f) {
                this->speed.y = -15.0f;
            }
            this->m03D0 = this->speed.y * 0.5f;
            this->speedF *= 0.85f;
            this->m0388 = 30;
        }
    }
    else {
        fVar2 = std::abs(this->speedF) / 55.0f;
        if (fVar2 > 1.0f) {
            fVar2 = 1.0f;
        }

        this->current.pos.y += fVar2 * ((this->m03F4 - this->current.pos.y) * 0.1f);
        this->m03D0 += (this->m03F4 - this->current.pos.y) * 0.05f;

        if (this->m03D0 > 20.0f) {
            this->m03D0 = 20.0f;
        }
        else if (this->m03D0 < -20.0f) {
            this->m03D0 = -20.0f;
        }   

        this->current.pos.y += this->m03D0;
        this->m03B0 += 1000.0f + cM_rndF(1000.0f) + 500.0f * fVar2;
        this->current.pos.y += fVar2 * 0.25f * cM_ssin(this->m03B0) + 0.6f;

        cLib_addCalc(&this->m03D0, 0.0f, 0.05f, 1.0f, 0.05f);

        fVar4 = this->current.pos.y;
        fVar5 = this->m03F4 + 40.0f;
        if (fVar4 > fVar5) {
            this->current.pos.y = fVar5;
        }
        else {
            fVar5 = this->m03F4 - 60.0f;
            if (fVar4 < fVar5) {
                this->current.pos.y = fVar5;
            }
        }

        this->m03AE += (fVar2 * 0.5f + 1.0f) * (cM_rndF(800.0f) + 800.0f);
        this->m03AC += (fVar2 * 0.5f + 1.0f) * (cM_rndF(600.0f) + 600.0f);

        this->m0370 += fVar2 * 100.0f * cM_ssin(this->m03AE) + 30.0f;
        this->m0372 += fVar2 * 115.0f * cM_ssin(this->m03AC) + 35.0f;
    }
    return;
}

/* 00002824-00002CC4       .text checkOutRange__8daShip_cFv */
BOOL daShip_c::checkOutRange() {
    if (this->m034B == 0xFF) {
        return FALSE;
    }

    int pathIndex = 0;
    BOOL bVar4 = FALSE;
    BOOL bVar5 = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == 7;
    dPath* pInPath = dPath_GetRoomPath(this->m034B, -1);
    while (pInPath) {
        dPath__Point* dPathPnt = pInPath->mpPnt;
        if (pInPath->m_num < 3) {
            pInPath = dPath_GetNextRoomPath(pInPath, -1);
            pathIndex++;
            continue;
        }
        if (bVar5) {
            if (pathIndex == 0 && dComIfGs_isEventBit(0x902) || pathIndex == 1 && dComIfGs_isSymbol(2) || pathIndex == 2 && daPy_getPlayerActorClass()->checkMasterSwordEquip()) {
                pInPath = dPath_GetNextRoomPath(pInPath, -1);
                pathIndex++;
                continue;
            } 
        }

        float minDist = FLOAT_MAX;
        
        int closestIndex;
        cXyz* closestPoint;

        for (int i = 0; i < pInPath->m_num; dPathPnt++, i++) {
            float dx = this->current.pos.x - dPathPnt->mPos.x;
            float dz = this->current.pos.z - dPathPnt->mPos.z;
            
            float distXZ = dx * dx + dz * dz;
            
            if (minDist > distXZ) {
                closestIndex = i;
                minDist = distXZ;
                closestPoint = &dPathPnt->mPos;
            }
        }

        int lastIndex = pInPath->m_num - 1;

        cXyz* nextPoint;
        if (closestIndex == lastIndex) {
            nextPoint = &pInPath->mpPnt->mPos;
        }
        else {
            nextPoint = &(pInPath->mpPnt + closestIndex + 1)->mPos;
        }

        cXyz* prevPoint;
        if (closestIndex == 0) {
            prevPoint = &(pInPath->mpPnt + lastIndex)->mPos;
        }
        else {
            prevPoint = &(pInPath->mpPnt + closestIndex - 1)->mPos;
        }

        short angleNext = cM_atan2s(nextPoint->x - closestPoint->x, nextPoint->z - closestPoint->z);
        short anglePrev = cM_atan2s(closestPoint->x - prevPoint->x, closestPoint->z - prevPoint->z);
        short angleCurrent = cM_atan2s(this->current.pos.x - closestPoint->x, this->current.pos.z - closestPoint->z);

        short diffNext = angleCurrent - angleNext;
        short diffPrev = cM_atan2s(this->current.pos.x - prevPoint->x, this->current.pos.z - prevPoint->z) - anglePrev;
        
        if ((s16)(angleNext - anglePrev) >= 0) {
            if (diffNext < 0) {
                this->m038C = angleNext + 0x4000;
                bVar4 = TRUE;
            }
            if (diffPrev < 0) {
                this->m038C = anglePrev + 0x4000;
                bVar4 = TRUE;
            }
        } 
        else if (diffNext < 0 && diffPrev < 0) {
            float dxNext = nextPoint->x - this->current.pos.x;
            float dzNext = nextPoint->z - this->current.pos.z;
            float distNext = std::sqrtf(dxNext * dxNext + dzNext * dzNext);
            
            float dxPrev = prevPoint->x - this->current.pos.x;
            float dzPrev = prevPoint->z - this->current.pos.z;
            float distPrev = std::sqrtf(dxPrev * dxPrev + dzPrev * dzPrev);
            
            if (distNext > distPrev) {
                this->m038C = anglePrev + 0x4000;
            }
            else {
                this->m038C = angleNext + 0x4000;
            }
            
            bVar4 = TRUE;
        }
        
        if (bVar4) {
            if (dComIfGp_getMiniGameType() == 1) {
                this->mNextMessageID = 0x60a;
            }
            else if ((bVar5) && (pathIndex != 3)) {
                this->mNextMessageID = 0x609;
            }
            else {
                this->mNextMessageID = 0x5dd;
            }

            onStateFlg(daSFLG_UNK400000_e);
            return TRUE;
        }
        pInPath = dPath_GetNextRoomPath(pInPath, -1);
        pathIndex++;
    }
    return FALSE;
}

/* 00002CC4-00002CFC       .text decrementShipSpeed__8daShip_cFf */
void daShip_c::decrementShipSpeed(float decrementSpeed) {
    cLib_addCalc(&this->speedF, decrementSpeed, 0.05f, 0.1f, 0.015f);
    return;
}

/* 00002CFC-00002D5C       .text firstDecrementShipSpeed__8daShip_cFf */
void daShip_c::firstDecrementShipSpeed(float decrementSpeed) {
    if (cLib_addCalc(&this->speedF, decrementSpeed, 0.1f, 5.0f, 1.0f) < 3.0f) {
      this->m03E0 = 10000.0f;
    }
    return;
}

/* 00002D5C-00002D90       .text getAimControllAngle__8daShip_cFs */
s16 daShip_c::getAimControllAngle(short referenceAngle) {
    s16 aimControlAngle = (s16)(this->shape_angle.y - referenceAngle) * 7;
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
    if (this->mTornadoActor || this->mWhirlActor != 0) {
        cannotMove = TRUE;
    }
    if (!cannotMove) {
        initialAngle = this->shape_angle.y;
        turnRate = 4.0f - std::abs(this->speedF) / 55.0f * 3.0f;
        maxTurnRate = 3.6f;
        minTurnRate = 0.1f;
        if (turnRate > maxTurnRate) {
            turnRate = maxTurnRate;
        }
        else if (turnRate < minTurnRate) {
            turnRate = minTurnRate;
        }
        if (this->m0388 >= 0xF) {
            turnRate = maxTurnRate;
        }
        else {
            turnRate += ((3.6f - turnRate) * this->m0388) / 15.0f;
        }
        this->shape_angle.y += (int)(-turnRate * (moveAngle >> 6));
        setControllAngle(getAimControllAngle(initialAngle));
        this->current.angle.y = this->shape_angle.y;
    }
    return;
}

/* 00002EE0-00002FBC       .text changeDemoEndProc__8daShip_cFv */
void daShip_c::changeDemoEndProc() {  
    offStateFlg(daSFLG_UNK8000_e);  
    if (checkStateFlg(daSFLG_UNK80000_e)) {
        this->m029C->setPlaySpeed(-1.0f);
        offStateFlg(daSFLG_UNK80000_e);
    }
    if ((this->m0351 == 8) || checkStateFlg(daSFLG_UNK4000000_e)) {
        this->m0366 = 0;
        offStateFlg(daSFLG_UNK4000000_e);
    }
    this->gravity = -2.5f;
    
    if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
        if (this->mShipMode == Idle) {
            procPaddleMove_init();
        }
        else if (this->mShipMode == 2) { //UsingCannon
            procCannonReady_init();
        }
        else if (this->mShipMode == 3) { //UsingSalvageArm
            procCraneReady_init();
        }
        else {
            procSteerMove_init();
        }
    }
    else {
        procWait_init();
    }
    return;
}

/* 00002FBC-000031E4       .text setCrashData__8daShip_cFs */
void daShip_c::setCrashData(short param1) {
    float fVar1;
    float fVar2;
    daPy_lk_c *link;
    s16 iVar5;
    if (dComIfGp_event_runCheck() == 0) {
        link = daPy_getPlayerLinkActorClass();
        if (!link->checkNoDamageMode() && !link->checkNoControll()) {
            if (!checkForceMove()) {
                link->onShipDrop(param1);
                procWait_init();
            }
        }
        onStateFlg(daSFLG_UNK8000000_e);
        if (this->m03B6 == 0) {
            if (this->speedF > l_HIO.wind_inc_speed) {
                this->speedF = l_HIO.wind_inc_speed;
            }
            this->speedF *= l_HIO.ef_speed_rate;
            iVar5 = param1 - this->shape_angle.y;
            fVar1 = cM_ssin(iVar5);
            fVar2 = cM_scos(iVar5);
            this->m0370 += fVar2 * 3072.0f;
            this->m0374 += fVar2 * 500.0f;
            this->m0372 -= fVar1 * 3072.0f;
            this->m0376 -= fVar1 * 500.0f;
            this->m03B6 = 30;
        }
        else {
            this->m03B6--;
        }
    }
    return;
}

/* 000031E4-00003490       .text checkNextMode__8daShip_cFi */
BOOL daShip_c::checkNextMode(int param_1) {
    cXyz local_8;
    cXyz local_20;
    cXyz local_14;
    
    if (checkStateFlg(daSFLG_UNK4_e) != 0) {
        setCrashData(this->shape_angle.y + 0x8000);
        offStateFlg(daSFLG_UNK4_e);
        return TRUE;
    }

    if (!dComIfGp_checkPlayerStatus0(0, 0x10000)) {
        if (this->m034D == 5) {
            procGetOff_init();
        }
        else {
            procWait_init();
        }
        return TRUE;
    }
    
    if (dComIfGp_event_runCheck() == 0) {
        cXyz* tgRVecP;
        cXyz* tgHitPos;
        dCcD_GObjInf* tgHitObj;
        
        tgRVecP = NULL;
        tgHitPos = NULL;
        tgHitObj = NULL;

        if (mSph.ChkTgHit()) {
            tgRVecP = this->mSph.GetTgRVecP();
            tgHitPos = this->mSph.GetTgHitPosP();
            tgHitObj = this->mSph.GetTgHitGObj();
            
        }
        else {
            dCcD_Cyl* cyl = this->mCyl;
            for(int i = 0; i < 3; i++, cyl++) {
                if (cyl->ChkTgHit()) {
                    tgRVecP = cyl->GetTgRVecP();
                    tgHitPos = cyl->GetTgHitPosP();
                    tgHitObj = cyl->GetTgHitGObj();
                }
            }
        }

        if (tgHitObj && (tgHitObj->GetAtType() - AT_TYPE_WIND) == 0) {
            if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
                onStateFlg((daSHIP_SFLG)(daSFLG_UNK1_e | daSFLG_UNK2000000_e));
            }
        }
        else {
            if (tgRVecP) {
                short sVar2;
                local_14.set(tgRVecP->x, 0.0f, tgRVecP->z);
                if (PSVECSquareMag(&local_14) < 0.1f) {
                    local_20 = this->current.pos - *tgHitPos;
                    local_8.set(local_20.x, 0.0f, local_20.z);
                    if (PSVECSquareMag(&local_8) < 0.1f) {
                        sVar2 = this->shape_angle.y + 0x8000;
                    }
                    else {
                        sVar2 = cM_atan2s(local_8.x, local_8.z);
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

    if (param_1 == this->m034D) {
        return FALSE;
    }
    else if (this->m034D == 2) {
        procPaddleMove_init();
    }
    else if (this->m034D == 1) {
        procSteerMove_init();
    }
    else if (this->m034D == 9) {
        procCannonReady_init();
    }
    else if (this->m034D == 10) {
        procCraneReady_init();
    }
    else if (this->m034D == 14) {
        procTactWarp_init();
    }
    else {
        return FALSE;
    }
    return TRUE;
}

/* 00003490-0000358C       .text setPartOnAnime__8daShip_cFUc */
void daShip_c::setPartOnAnime(unsigned char shipMode) {
    J3DAnmTransform* pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, 11);
    this->m0298->setAnm(pAnimRes, J3DFrameCtrl::EMode_NONE, 3.0f, 1.0f, 0.0f, -1.0f, NULL);
    this->m0392 = 11;
    this->mShipMode = shipMode;
    if (this->mShipMode == 1) { //Sailing
        seStart(0x2831, &this->m0444);
        this->m03E8 = 1.0;
    }
    else if (this->mShipMode == 2) { //UsingCannon
        seStart(0x284f, &this->m0444);
        this->m03E8 = 0.001f;
    }
    else if (this->mShipMode == 3) { //UsingSalvageArm
        seStart(0x284a, &this->m0444);
        this->m03E8 = 0.001f;
    }
    return;
}

/* 0000358C-0000366C       .text setPartOffAnime__8daShip_cFv */
void daShip_c::setPartOffAnime() {
    J3DAnmTransform* pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, 10);
    this->m0298->setAnm(pAnimRes, J3DFrameCtrl::EMode_NONE, 3.0f, 1.0f, 0.0f, -1.0f, NULL);
    if (this->mShipMode == 3) { //UsingSalvageArm
        seStart(0x284B, &this->m0444);
    }
    else if (this->mShipMode == 2) { //UsingCannon
        seStart(0x2850, &this->m0444);
    }
    else {
        seStart(0x2832, &this->m0444);
    }
    this->m0392 = 10;
    offStateFlg(daSFLG_UNK200_e);
    return;
}

/* 0000366C-00003844       .text setPartAnimeInit__8daShip_cFUc */
void daShip_c::setPartAnimeInit(unsigned char param_1) {
    float fVar1 = 1.0f - this->m0298->getFrame() / this->m0298->getEndFrame();
    if (param_1 == 0) {
        if (this->m0392 == 11) {
            setPartOffAnime();
            this->m0298->setFrame(fVar1 * this->m0298->getEndFrame());
        }
    }
    else if (this->mShipMode != param_1) {
        if (this->m0392 == 11) {
            setPartOffAnime();
            this->m0298->setFrame(fVar1 * this->m0298->getEndFrame());
        }
        else if (this->m0298->getPlaySpeed() < 0.01f) {
            setPartOnAnime(param_1);
        }
    }
    else if (this->m0392 == 10) {
        setPartOnAnime(param_1);
        this->m0298->setFrame(fVar1 * this->m0298->getEndFrame());
    }
    return;
}

/* 00003844-00003A44       .text setSelfMove__8daShip_cFi */
void daShip_c::setSelfMove(int param_1) {
    BOOL bVar1;
    short sVar2;
    int iVar3;
    int iVar4;
    float fVar5;
    float fVar6;
    
    if (param_1) {
        sVar2 = this->mStickMVal * 8192.0f * -cM_ssin(this->mStickMAng);
    }
    else {
        sVar2 = 0;
    }
    cLib_addCalcAngleS(&this->m0366, sVar2, 4, 700, 0x100);
    setMoveAngle(this->m0366);
    if (!checkStateFlg(daSFLG_UNK1_e)) {
        if (dComIfGp_checkPlayerStatus0(0, 0x2000) || dComIfGp_event_runCheck() || daPy_getPlayerLinkActorClass()->checkNoControll()) {
            firstDecrementShipSpeed(0.0f);
        }
        else {
            if (this->m03E0 <= this->speedF) {
                firstDecrementShipSpeed(this->m03E0);
            }
            else {
                if (dComIfGp_getDoStatus() == 0x13 && (CPad_CHECK_HOLD_A(0))) { //m_Do_controller_pad::g_mDoCPd_cpadInfo[0].mButton0 & 1
                    fVar6 = cLib_addCalc(&this->speedF, 0.0f, 0.1f, 1.0f, 0.1f);
                }
                else {
                    fVar6 = g_mDoCPd_cpadInfo[0].mTriggerRight * 10.0f; //Not sure if this is a macro either
                    bVar1 = FALSE;
                    if (this->mAcch.ChkWallHit()) {
                        for (int i = 0; i < this->m03CC; i++) {
                            if (this->mAcchCir[i].ChkWallHit() && cLib_distanceAngleS(this->mAcchCir[i].GetWallAngleY(), this->shape_angle.y) > 0x5000) {
                                bVar1 = TRUE;
                            }
                        }
                    }
                    if (bVar1 && this->speedF > fVar6) {
                        firstDecrementShipSpeed(fVar6);
                    }
                    else {
                        decrementShipSpeed(fVar6);
                    }
                }
            }
        }
    }
    return;
}

/* 00003A44-00003AA0       .text procWait_init__8daShip_cFv */
BOOL daShip_c::procWait_init() {  
    this->m034C = 0;
    this->mProc = &daShip_c::procWait;
    this->m037A = 0;
    if (this->m0392 != 10) {
        setPartOffAnime();
    }
    return TRUE;
}

/* 00003AA0-00003B94       .text procWait__8daShip_cFv */
BOOL daShip_c::procWait() {  
    cLib_addCalc(&this->speedF, 0.0f, 0.1f, 1.0f, 0.05f);
    
    if (this->m0298->getFrame() >= 7.0f) {
        this->mShipMode = Idle;
        this->m03E8 = 1.0f;
    }

    if (this->m034D == 3) {
        procReady_init();
    }
    else if (this->m034D == 2) {
        procPaddleMove_init();
    }
    else if (this->m034D == 13) {
        procStartModeWarp_init();
    }
    else if (this->m034D == 16) {
        procStartModeThrow_init();
    }
    else {
        setControllAngle(0);
        cLib_addCalcAngleS(&this->m0366, 0, 2, 0x1000, 0x400);
    }

    return TRUE;
}

/* 00003B94-00003BC4       .text procReady_init__8daShip_cFv */
BOOL daShip_c::procReady_init() {
    this->mProc = &daShip_c::procReady;
    this->m034C = 3;
    return TRUE;
}

/* 00003BC4-00003C7C       .text procReady__8daShip_cFv */
BOOL daShip_c::procReady() {
    short playerAngle;
  
    if (dComIfGp_checkPlayerStatus0(0, 0x1010000) == 0) {
        procWait_init();
    }
    else if (this->m034D == 2) {
        procPaddleMove_init();
    }
    else {
        if (this->m034D == 4) {
            this->m034C = 4;
        }
        if (this->m034C == 3) {
            playerAngle = fopAcM_searchPlayerAngleY(this);
            if ((short)(playerAngle - this->shape_angle.y) > 0) {
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
    this->m034C = 5;
    this->mProc = &daShip_c::procGetOff;
    if (this->m0392 != 10) {
        setPartOffAnime();
    }
    this->speedF = 0.0f;
    return TRUE;
}

/* 00003CEC-00003DEC       .text procGetOff__8daShip_cFv */
BOOL daShip_c::procGetOff() {
    if (this->m0298->getFrame() >= 7.0f) {
        this->mShipMode = Idle;
        this->m03E8 = 1.0f;
    }
    if (this->m034D == 6) {
        this->m034C = 6;
    }
    if (this->m034C == 6) {
        if (this->m036C > 0x800) {
            procWait_init();
        }
        else {
            setControllAngle(0x1000);
            cLib_addCalcAngleS(&this->m0366, 0, 2, 0x1000, 0x400);
        }
    }
    else {
        setControllAngle(0);
        cLib_addCalcAngleS(&this->m0366, 0, 2, 0x1000, 0x400);
        
        if (!daPy_getPlayerLinkActorClass()->checkShipGetOff()) {
            procWait_init();
        }
    }
    return TRUE;
}

/* 00003DEC-00003F00       .text procPaddleMove_init__8daShip_cFv */
BOOL daShip_c::procPaddleMove_init() {  
    offStateFlg(daSFLG_UNK4_e);
    
    this->m034C = 2;
    
    this->mProc = &daShip_c::procPaddleMove;

    if (this->m0392 != 10) {
        setPartOffAnime();
    }

    if (checkStateFlg(daSFLG_UNK2000_e) != 0) {
        offStateFlg(daSFLG_UNK2000_e);
        this->current.pos.y -= 50.0f;
    }
    
    dComIfGs_onEventBit(0x2A08);
    
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
    if (checkNextMode(2)) {
        return TRUE;
    }
    if (this->m0298->getFrame() >= 7.0f) {
        this->mShipMode = Idle;
        this->m03E8 = 1.0f;
    }
    if (dComIfGp_checkPlayerStatus0(0, 0x685000) || dComIfGp_checkPlayerStatus1(0, 8)) {
        cLib_addCalcAngleS(&this->m0366, 0, 4, l_HIO.tiller_speed, 0x100);
        if (dComIfGp_event_runCheck() == 0) {
            setMoveAngle(this->m0366);
        }
        firstDecrementShipSpeed(0.0f);
    }
    else {
        if (dComIfGp_event_runCheck() == 0) {
            setSelfMove(1);
        }
    }
    return TRUE;
}

/* 00004004-00004060       .text procSteerMove_init__8daShip_cFv */
BOOL daShip_c::procSteerMove_init() {
    offStateFlg(daSFLG_UNK4_e);
    this->m034C = 1;
    this->mProc = &daShip_c::procSteerMove;
    setPartAnimeInit(1);
    return TRUE;
}

/* 00004060-0000451C       .text procSteerMove__8daShip_cFv */
BOOL daShip_c::procSteerMove() {
    if (checkNextMode(1)) {
        return TRUE;
    }
    cLib_addCalcAngleS(&this->m0366, this->mStickMVal * 8192.0f * -cM_ssin(this->mStickMAng), 4, 700, 0x100);
    if (checkStateFlg(daSFLG_UNK1_e) == 0) {
        setMoveAngle(this->m0366);
    }
    setSailAngle();
    if (this->m0392 == 11 && this->m0298->getFrame() >= 7.0f && this->mShipMode == Sailing) { // Sailing
        onStateFlg(daSFLG_UNK200_e);
    }
    if (checkStateFlg(daSFLG_UNK1_e) == 0) {
        cXyz* windVec = dKyw_get_wind_vec();
        float windPower = *dKyw_get_wind_power() / 0.5f;
        int angleDiff = abs((short)(cM_atan2s(windVec->x, windVec->z) - this->shape_angle.y));
        
        float windFactor;
        if (angleDiff < 0x4000) {
            windFactor = 1.0f - angleDiff * 1.5258789e-05f;
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
        
        if (this->m0298->mFrameCtrl.checkPass(7.0f)) {
            float targetSpeed = windPower * 2.0f;
            if (targetSpeed > 80.0f) {
                targetSpeed = 80.0f;
            }
            if (this->speedF < targetSpeed) {
                this->speedF = targetSpeed;
                if (checkForceMove()) {
                    this->m03E0 = 10000.0f;
                } else {
                    this->m03E0 = windPower;
                }
            }
        } else {
            if (this->m03E0 < this->speedF) {
                firstDecrementShipSpeed(this->m03E0);
            } else {
                if (!checkStateFlg(daSFLG_UNK200_e) || windPower <= 0.0f) {
                    decrementShipSpeed(this->mStickMVal * 10.0f * cM_scos(this->mStickMAng));
                } else if (this->speedF >= windPower) {
                    decrementShipSpeed(windPower);
                } else {
                    cLib_addCalc(&this->speedF, windPower, 0.1f, 0.5f, 0.1f);
                }
            }
        }
        if (dComIfGp_event_runCheck() == 0 && 
            !daPy_getPlayerLinkActorClass()->checkNoControll() && 
            this->m0392 == 11 && 
            this->m0298->getFrame() >= 7.0f && 
            !checkStateFlg(daSFLG_UNK1_e) && 
            this->mFwdVel > 16.5f) {
            if (!checkForceMove() && windPower >= 11.0f) {
                onStateFlg(daSFLG_UNK4000_e);
                if (g_mDoCPd_cpadInfo[0].mTrigLockR) { //m_Do_controller_pad::g_mDoCPd_cpadInfo[0].mTriggerRightEdge
                    onStateFlg((daSHIP_SFLG)(daSFLG_UNK1_e | daSFLG_UNK40_e));
                    this->speed.y = windPower;
                    if (this->speed.y < 15.0f) {
                        this->speed.y = 15.0f;
                    } else if (this->speed.y > 40.0f) {
                        this->speed.y = 40.0f;
                    }
                    this->m0386 = 0;
                    this->current.angle.y = this->shape_angle.y;
                    this->m03E4 = (this->speed.y - 11.0f) * 0.014545455f;
                    this->m036C >>= 1;
                }
            }
        }
    } else {
        setControllAngle(0);
        this->m036E = 0;
    }
    if (this->mShipMode != Sailing && this->m0298->getPlaySpeed() < 0.01f) { // Sailing
        setPartOnAnime(1);
    }
    return TRUE;
}

/* 0000451C-00004580       .text procCannonReady_init__8daShip_cFv */
BOOL daShip_c::procCannonReady_init() {
    this->m034C = 9;
    this->mProc = &daShip_c::procCannonReady;
    setPartAnimeInit(2);
    this->m0394 = 0;
    return TRUE;
}

/* 00004580-00004634       .text procCannonReady__8daShip_cFv */
BOOL daShip_c::procCannonReady() {
    if (checkNextMode(9)) {
        return TRUE;
    }
    cLib_addCalcAngleS(&this->m0366, 0, 2, 0x1000, 0x400);
    setMoveAngle(this->m0366);
    firstDecrementShipSpeed(0.0f);
    if (this->m0298->getPlaySpeed() < 0.01f) {
        if (this->mShipMode != 2) { //UsingCannon
            setPartOnAnime(2);
        }
        else {
            procCannon_init();
        }
    }
    return TRUE;
}

/* 00004634-0000467C       .text procCannon_init__8daShip_cFv */
BOOL daShip_c::procCannon_init() {  
    this->mProc = &daShip_c::procCannon;
    this->m0366 = 0;
    this->speedF = 0.0f;
    this->m03A6 = 0;
    this->m03A8 = 0;
    this->m037A = 0;
    return TRUE;
}

/* 0000467C-00004B08       .text procCannon__8daShip_cFv */
BOOL daShip_c::procCannon() {
    BOOL bVar1;
    fopAc_ac_c* target;
    cXyz cannonPos;
    
    if (checkNextMode(9)) {
        return TRUE;
    }
    setControllAngle(0); 
    if (!(dComIfGp_event_runCheck() || daPy_getPlayerLinkActorClass()->checkNoControll())) {
        if (dComIfGp_getAttention().Lockon() && dComIfGp_getAttention().GetLockonList(0) && dComIfGp_getAttention().LockonTruth()) {
            target = dComIfGp_getAttention().GetLockonList(0)->getActor();
        }
        else {
            target = NULL;
        }
        
        short prev0396 = this->m0396;
        short prev0394 = this->m0394;
        
        if (target) {
            cannonPos.x = this->mpCannonModel->mpNodeMtx[2][0][3];
            cannonPos.y = this->mpCannonModel->mpNodeMtx[2][1][3];
            cannonPos.z = this->mpCannonModel->mpNodeMtx[2][2][3];

            cannonPos = target->eyePos - cannonPos;

            cLib_addCalcAngleS(&this->m0396, cM_atan2s(-cannonPos.y, cXyz(cannonPos.x, 0.0f, cannonPos.z).abs()) + 0x4000, 5, 0x180, 0x40);
            cLib_addCalcAngleS(&this->m0394, cM_atan2s(cannonPos.x, cannonPos.z) - this->shape_angle.y, 5, 0x180, 0x40);
        
        } else if (!g_mDoCPd_cpadInfo[0].mHoldLockR) {
            float adjust = this->mStickMVal * (this->m0404 * 4.0f + 1.0f);
            this->m0396 = prev0396 + adjust * (384.0f * cM_scos(this->mStickMAng));
            this->m0394 += (short)(adjust * cM_ssin(this->mStickMAng));
        }
        
        if (this->m0396 > 0x4000) {
            this->m0396 = 0x4000;
        } else if (this->m0396 < 0x1556) {
            this->m0396 = 0x1556;
        }
        
        if (cLib_distanceAngleS(prev0396, this->m0396) >= 0x80 || cLib_distanceAngleS(prev0394, this->m0394) >= 0x80) {
            bVar1 = TRUE;
        } else {
            bVar1 = FALSE;
        }
        if (bVar1) {
            seStart(0x2051, &this->m1038);
        }
        
        if (this->m037A == 0 && 
            ((CPad_CHECK_TRIG_X(0) && dComIfGp_getSelectItem(0) == dItem_BOMB_BAG_e) ||
             (CPad_CHECK_TRIG_Y(0) && dComIfGp_getSelectItem(1) == dItem_BOMB_BAG_e) ||
             (CPad_CHECK_TRIG_Z(0) && dComIfGp_getSelectItem(2) == dItem_BOMB_BAG_e))) {
            this->m037A = 30;
            if (dComIfGs_getBombNum() == 0) {
                mDoAud_seStart(0x883);
                this->m037A--;
            }
        } else if (this->m037A > 0) {
            this->m037A--;
        }
        
        if (g_mDoCPd_cpadInfo[0].mHoldLockR) {
            setSelfMove(1);
        } else {
            setSelfMove(0);
        }
    }
    return TRUE;
}


/* 00004B08-00004B7C       .text procCraneReady_init__8daShip_cFv */
BOOL daShip_c::procCraneReady_init() {  
    this->m034C = 10;
    this->mProc = &daShip_c::procCraneReady;
    this->m039A = 0x3000;
    this->m039C = 0;
    setPartAnimeInit(3);
    this->mCurrentRopeSegmentIndex = 0;
    return TRUE;
}

/* 00004B7C-00004CD0       .text procCraneReady__8daShip_cFv */
BOOL daShip_c::procCraneReady() {
    float fVar1;
    float fVar2;
    int iVar3;
    
    if (checkNextMode(10)) {
        return TRUE;
    }
    cLib_addCalcAngleS(&this->m0366, 0, 2, 0x1000, 0x400);
    setMoveAngle(this->m0366);
    firstDecrementShipSpeed(0.0f);
    if (this->m0298->getPlaySpeed() < 0.01f) {
        if (this->mShipMode != 3) { //UsingSalvageArm
            setPartOnAnime(3);
        }
        else {
            incRopeCnt(2, 0);
            if (this->mCurrentRopeSegmentIndex == 20) {
                procCrane_init();
            }
        }
    }
    if (this->mShipMode == 3) { //UsingSalvageArm
        fVar1 = (this->m0298->getFrame() - 5.0f) * 0.33333334f;
        if (fVar1 > 1.0f) {
            fVar1 = 1.0f;
        } 
        else if (fVar1 < 0.0f) {
            fVar1 = 0.0f;
        }
        this->m0398 = fVar1 * this->m039A;
    }
    return TRUE;
}

/* 00004CD0-00004D70       .text procCrane_init__8daShip_cFv */
BOOL daShip_c::procCrane_init() {
    this->mProc = &daShip_c::procCrane;
    this->speedF = 0.0f;
    this->m0366 = 0;
    this->mRipple.setRate(0.0f);
    offStateFlg(daSFLG_UNK800_e);
    this->m034C = 10;
    if (cM_rnd() < 0.5f) {
        this->m0353 = 1;
    }
    else {
        this->m0353 = 0;
    }
    return TRUE;
}

/* 00004D70-000050C4       .text procCrane__8daShip_cFv */
BOOL daShip_c::procCrane() {
    s16 sVar3;
    s16 sVar1;
    s16 sVar2;

    if (checkNextMode(10)) {
        offStateFlg(daSFLG_UNK800_e);
        return TRUE;
    }
    setControllAngle(0);
    dComIfG_play_c* play = &g_dComIfG_gameInfo.play;
    if (dComIfGp_event_runCheck() == 0 && !daPy_getPlayerLinkActorClass()->checkNoControll()) {
        if (this->m0398 == this->m039A) {
            if(std::fabsf(this->speedF) < 3.0f &&
              ((CPad_CHECK_HOLD_X(0) && dComIfGp_getSelectItem(0) == dItem_GRAPPLING_HOOK_e) ||
               (CPad_CHECK_HOLD_Y(0) && dComIfGp_getSelectItem(1) == dItem_GRAPPLING_HOOK_e) ||
               (CPad_CHECK_HOLD_Z(0) && dComIfGp_getSelectItem(2) == dItem_GRAPPLING_HOOK_e))) {
                sVar1 = this->mCurrentRopeSegmentIndex;
                incRopeCnt(2, 0);
                if (this->mCurrentRopeSegmentIndex == 250) {
                    sVar3 = 0;
                    if (this->m039A > 0) {
                        setControllAngle(0xA00);
                    }
                    else {
                        setControllAngle(-0xA00);
                    }
                    if (this->m0353 && (sVar1 != this->mCurrentRopeSegmentIndex)) {
                        //dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
                        play->getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f)); //Fakematch
                    }
                }
                else if (this->m039A > 0) {
                    sVar3 = 0x800;
                }
                else {
                    sVar3 = -0x800;
                }
            }
            else {
                incRopeCnt(-2, 20);
                if (this->mCurrentRopeSegmentIndex == 20) {
                    sVar3 = 0;
                }
                else if (this->m039A > 0) {
                    sVar3 = -0x800;
                }
                else {
                    sVar3 = 0x800;
                }
            }
            cLib_chaseAngleS(&this->m039C, sVar3, 0x100);
            if (this->mCurrentRopeSegmentIndex == 20 && !g_mDoCPd_cpadInfo[0].mHoldLockR && this->mStickMVal > 0.1f) {
                sVar2 = this->m039A;
                if ((this->mStickMAng < -0x2000) && (this->mStickMAng > -0x6000)) {
                    this->m039A = 0x3000;
                    this->m03A6 = 0;
                    onStateFlg(daSFLG_UNK10000000_e);
                }
                else if ((this->mStickMAng > 0x2000) && (this->mStickMAng < 0x6000)) {
                    this->m039A = -0x3000;
                    this->m03A6 = 0;
                    onStateFlg(daSFLG_UNK10000000_e);
                }
                if (sVar2 * this->m039A < 0) {
                    seStart(0x284C, &this->m102C);
                }
            }
        }
        else {
            cLib_chaseAngleS(&this->m03A6, 0x1800, 0x100);
            cLib_addCalcAngleS(&this->m0398, this->m039A, 5, this->m03A6, 0x100);
        }
        if (g_mDoCPd_cpadInfo[0].mHoldLockR && this->mCurrentRopeSegmentIndex == 20) {
            setSelfMove(1);
            if (cM_rnd() < 0.5f) {
                this->m0353 = 1;
            }
            else {
                this->m0353 = 0;
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
    if (this->mProc == &daShip_c::procCraneUp) {
        return FALSE;
    }

    this->mProc = &daShip_c::procCraneUp;

    if (this->m039A > 0) {
        this->m03A6 = 0x800;
    }
    else {
        this->m03A6 = -0x800;
    }

    seStart(0x381e, &this->current.pos);

    this->m034C = 11;

    this->mRipple.setRate(1.0f);

    offStateFlg(daSFLG_UNK40000_e);

    dComIfGp_getVibration().StartShock(7, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    dComIfGp_getVibration().StartQuake(4, 1, cXyz(0.0f, 1.0f, 0.0f));

    this->speedF = 0.0f;
    return TRUE;
}

/* 000051F8-000053F0       .text procCraneUp__8daShip_cFv */
BOOL daShip_c::procCraneUp() {
    short sVar1;
    
    if (this->m039A > 0) {
        sVar1 = 0x800;
    }
    else {
        sVar1 = -0x800;
    }
    cLib_addCalcAngleS(&this->m039C, sVar1, 5, 0x1800, 0x100);
    if (this->mRipple.getEmitter() == NULL) {
        setControllAngle(0);
        onStateFlg(daSFLG_UNK40000_e);
        dComIfGp_getVibration().StopQuake(-1);
    }
    else {
        setControllAngle(this->m03A6);
        if (cLib_distanceAngleS(this->m036C, this->m03A6) < 0x400) {
            if (this->m039A > 0) {
                if (this->m03A6 > 0x400) {
                    this->m03A6 = cM_rnd() * 256.0f;
                }
                else {
                    this->m03A6 = cM_rnd() * 1024.0f + 2048.0f;
                    seStart(0x381E, &this->current.pos);
                }
            }
            else {
                if (this->m03A6 < -0x400) {
                    this->m03A6 = cM_rnd() * -256.0f;
                }
                else {
                    this->m03A6 = -2048.0f - cM_rnd() * 1024.0f;
                    seStart(0x381E, &this->current.pos);
                }
            }
        }
    }
    incRopeCnt(-1, 20);
    if (this->mCurrentRopeSegmentIndex == 20) {
        if (dComIfGp_event_runCheck()) {
            if (daPy_getPlayerLinkActorClass()->getBaseAnimeFrameRate() < 0.01f) {
                dComIfGp_evmng_cutEnd(this->mEvtStaffId);
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
    this->mProc = &daShip_c::procToolDemo;
    this->m034C = 7;
    offStateFlg(daSFLG_UNK1_e);
    return TRUE;
}

/* 0000542C-00005530       .text procToolDemo__8daShip_cFv */
BOOL daShip_c::procToolDemo() {
    dDemo_actor_c* demoActor = dComIfGp_demo_get()->mDemoObj.getActor(this->demoActorID);
    if (demoActor) {
        if ((demoActor->mFlags & 2) != 0) {
            this->current.pos.x = demoActor->mTranslation.x;
            this->current.pos.z = demoActor->mTranslation.z;
        }
        if ((demoActor->mFlags & 8) != 0) {
            csXyz demoRot = demoActor->mRotation;
            short prevShapeAngleY = this->shape_angle.y;
            this->shape_angle.y = demoRot.y;
            this->current.angle.y = this->shape_angle.y;
            short angleDiff = this->shape_angle.y - prevShapeAngleY;
            if (angleDiff > 0) {
                angleDiff = 0x2000;
            }
            else if (angleDiff < 0) {
                angleDiff = -0x2000;
            }
            else {
                angleDiff = 0;
            }
            cLib_addCalcAngleS(&this->m0366, angleDiff, 4, 700, 0x100);
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
    this->mProc = &daShip_c::procZevDemo;
    this->m034C = 7;
    offStateFlg(daSFLG_UNK1_e);
    this->m0350 = 4;
    return TRUE;
}

/* 00005574-00006310       .text procZevDemo__8daShip_cFv */
BOOL daShip_c::procZevDemo() {
    float fVar3;
    short sVar5; 
    short sVar15;
    short uVar16;
    u16 fileIndex;
    float fVar17;
    cXyz local_7c;
    cXyz local_70;
    cXyz local_64;
    
    if (!dComIfGp_checkPlayerStatus0(0, 0x10000) && this->m0392 != 10) {
        setPartOffAnime();
    }
    if ((s32)this->mEvtStaffId != fpcM_ERROR_PROCESS_ID_e) {
        cXyz* posP = dComIfGp_evmng_getMyXyzP(this->mEvtStaffId, "pos");
        u32* angleP = dComIfGp_evmng_getMyIntegerP(this->mEvtStaffId, "angle");
        float* speedP = dComIfGp_evmng_getMyFloatP(this->mEvtStaffId, "speed");
        u32* partP = dComIfGp_evmng_getMyIntegerP(this->mEvtStaffId, "part");
        s32* talkP = (s32*)dComIfGp_evmng_getMyIntegerP(this->mEvtStaffId, "talk");
        u32* atn_actorP = dComIfGp_evmng_getMyIntegerP(this->mEvtStaffId, "atn_actor");

        if (atn_actorP && g_dComIfG_gameInfo.play.getEvent().getPt1()) {
            this->m0428 = &dComIfGp_event_getPt1()->eyePos;
        }
        else {
            this->m0428 = dComIfGp_evmng_getMyXyzP(this->mEvtStaffId, "atn_pos");
        }

        if (this->m0351 && partP && (this->m0350 == 4 || this->m0350 != (s32)*partP)) {
            this->m0350 = *partP;
            setPartAnimeInit(*partP);
        }

        if (talkP && *talkP == 1) { 
            if (checkStateFlg(daSFLG_UNK8000_e) == 0) {
                this->m038A = 12;
                this->mAnmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, this->m038A);
                this->mFrameCtrl.init(this->mAnmTransform->getFrameMax());
                onStateFlg(daSFLG_UNK8000_e);
            }
        }
        else {
            offStateFlg(daSFLG_UNK8000_e);
        }

        if (dComIfGp_evmng_getMyIntegerP(this->mEvtStaffId, "tact")) {
            daPy_getPlayerLinkActorClass()->onNoResetFlg1(daPy_py_c::daPyFlg1_SHIP_TACT);
        }
        else {
            daPy_getPlayerLinkActorClass()->offNoResetFlg1(daPy_py_c::daPyFlg1_SHIP_TACT);
        }

        if (this->m0351 == 0 || this->m0351 == 8) {
            if (angleP) {
                sVar15 = (short)*angleP;
            }
            else {
                sVar15 = this->shape_angle.y;
            }

            if (posP) {
                initStartPos(posP, sVar15);
            }
            else {
                initStartPos(&current.pos, sVar15);
            }

            if (speedP) {
                this->speedF = *speedP;
            }

            if (partP || this->m0351 == 8) {
                if (this->m0351 == 8) {
                    this->m0350 = 0;
                }
                else {
                    this->m0350 = *partP;
                }

                this->mShipMode = this->m0350;
                this->mCurrentRopeSegmentIndex = 0;

                if (this->mShipMode != Idle) {
                    fileIndex = 11;
                }
                else {
                    fileIndex = 10;
                    this->m03E8 = 0.001f;
                }
                if (this->m0392 != fileIndex) {
                    this->m0298->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, fileIndex), J3DFrameCtrl::EMode_NONE, 0.0f, 1.0f, 0.0f, -1.0f, NULL);
                    this->m0392 = fileIndex;
                    this->m0298->setFrame(this->m0298->getEndFrame() - 0.001f);
                    this->m0298->getAnm()->setFrame(this->m0298->getEndFrame() - 0.001f);
                    this->m0298->play(NULL, 0, 0);
                }
            }
            setControllAngle(0);
            dComIfGp_evmng_cutEnd(this->mEvtStaffId);
        }
        else if (this->m0351 == 1 || this->m0351 == 3) {
            if (posP == NULL) {
                posP = dComIfGp_evmng_getGoal();
            }
            
            if (this->m0351 == 1) {
                local_7c = *posP - this->current.pos;
            }
            else {
                local_70 = this->current.pos - *posP;

                fVar17 = cXyz(local_70.x, 0.0f, local_70.z).abs();

                if (!dComIfGp_evmng_getMyFloatP(this->mEvtStaffId, "rad")) {
                    JUT_ASSERT(0xE9D, 0);
                }

                fVar3 = *dComIfGp_evmng_getMyFloatP(this->mEvtStaffId, "rad");

                if (fVar17 < 0.1f) {
                    sVar15 = 0x4000;
                    local_64.set(posP->x, posP->y, posP->z + fVar3);
                }
                else {
                    sVar15 = (short)(cM_atan2s(local_70.x, local_70.z) + 0x4000);
                    local_64 = *posP + local_70 * (fVar3 / fVar17);
                }

                local_64.x += fVar3 * cM_ssin(sVar15);
                local_64.z += fVar3 * cM_scos(sVar15);
                local_7c = local_64 - this->current.pos;
            }

            fVar17 = cXyz(local_7c.x, 0.0f, local_7c.z).abs();

            if (fVar17 < 10.0f) {
                this->speedF = 0.0f;
                dComIfGp_evmng_cutEnd(this->mEvtStaffId);
            }
            else {
                if (speedP && *speedP <= -0.5f) {
                    if (this->m03E0 <= this->speedF) {
                        firstDecrementShipSpeed(this->m03E0);
                    }
                    else {
                        if (*speedP < -1.5f) {
                            cLib_addCalc(&this->speedF, 0.0f, 0.1f, 1.0f, 0.1f);
                        }
                        else { 
                            decrementShipSpeed(0.0f);
                        }
                    }
                }
                else {
                    this->speedF = fVar17 * 0.2f;
                    if (speedP) {
                        fVar3 = *speedP;
                    }
                    else {
                        fVar3 = 55.0f;
                    }
                    if (this->speedF > fVar3) {
                        this->speedF = fVar3;
                    }
                }
            }
            if (fVar17 > 1.0f) {
                sVar15 = this->shape_angle.y;
                cLib_addCalcAngleS(&this->shape_angle.y, cM_atan2s(local_7c.x, local_7c.z), 3, 0x2000, 0x80);
                this->current.angle.y = this->shape_angle.y;
                
                sVar5 = this->shape_angle.y - sVar15;
                if (sVar5 > 0) {
                    sVar5 = 0x2000;
                }
                else if (sVar5 < 0) {
                    sVar5 = -0x2000;
                }
                else {
                    sVar5 = 0;
                }

                cLib_addCalcAngleS(&this->m0366, sVar5, 4, 700, 0x100);
                setControllAngle(getAimControllAngle(sVar15));
            }
            else {
                setControllAngle(0);
            }
        }
        else if (this->m0351 == 4) {
            if (checkStateFlg(daSFLG_UNK10000_e) == 0) {
                this->m029C->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, 9), J3DFrameCtrl::EMode_NONE, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
                onStateFlg(daSFLG_UNK10000_e);
                this->m03B4 = 9;
            }

            this->speedF = 0.0f;
            setControllAngle(0);

            if (this->m029C->getPlaySpeed() < 0.01f) {
                dComIfGp_evmng_cutEnd(this->mEvtStaffId);
            }
        }
        else if (this->m0351 == 5) {
            if (speedP) {
                firstDecrementShipSpeed(*speedP);
            }
            setControllAngle(0);
            dComIfGp_evmng_cutEnd(this->mEvtStaffId);
        }
        else if (this->m0351 == 6) {
            partP = dComIfGp_evmng_getMyIntegerP(this->mEvtStaffId, "prm0");

            if (partP == NULL || (*partP & 1) == 0) {
                fileIndex = 8;
            }
            else {
                fileIndex = 7;
            }

            if (partP && (s32)*partP == 2) {
                fVar17 = -1.0f;
            }
            else {
                fVar17 = 1.0f;
            }

            if (!checkStateFlg(daSFLG_UNK80000_e) && fVar17 > 0.0f) {
                this->m029C->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, fileIndex), J3DFrameCtrl::EMode_NONE, 5.0f, fVar17, 0.0f, -1.0f, NULL);
                this->m03B4 = (short)fileIndex;
                onStateFlg(daSFLG_UNK80000_e);
            }
            else if (checkStateFlg(daSFLG_UNK80000_e) && fVar17 < 0.0f) {
                offStateFlg(daSFLG_UNK80000_e);
                this->m029C->setPlaySpeed(-1.0f);
            }

            setControllAngle(0);

            if (std::fabsf(this->m029C->getPlaySpeed()) <= 0.1f) {
                dComIfGp_evmng_cutEnd(this->mEvtStaffId);
            }
        }
        else if (this->m0351 == 7) {
            this->speedF = 150.0f;
            speedP = dComIfGp_evmng_getMyFloatP(this->mEvtStaffId, "gravity");
            if (speedP) {
                this->gravity = *speedP;
            }
            
            this->speed.y = 50.0f;
            onStateFlg(daSFLG_UNK1_e);

            if (angleP) {
                this->current.angle.y = (short)*angleP;
            }

            this->shape_angle.y += 4500;
            dComIfGp_evmng_cutEnd(this->mEvtStaffId);
        }
        else if (this->m0351 == 10) {
            cLib_addCalcAngleS(&this->m0370, 0, 10, 0x1000, 0x200);
            cLib_addCalcAngleS(&this->m0372, 0, 10, 0x1000, 0x200);
            cLib_addCalcAngleS(&this->m0384, 0, 10, 0x1000, 0x200);
            cLib_addCalcAngleS(&this->m036C, 0, 10, 0x1000, 0x200);

            onStateFlg(daSFLG_UNK1_e);
            if (this->speed.y < 15.0f) {
                this->speed.y += 1.0f;
            }
            
            this->m0366 = 0;
            this->m036E = 0;
            this->m0374 = 0;
            this->m0376 = 0;
            this->m0386 = 0;
            this->gravity = 0.0f;
            this->speedF = 0.0f;
            this->current.pos.y += this->speed.y;
            dComIfGp_evmng_cutEnd(this->mEvtStaffId);
        }
        else {
            if (this->m0351 == 11) {
                if (this->m03F4 > this->current.pos.y && this->gravity >= 0.0f) {
                    offStateFlg(daSFLG_UNK1_e);
                    this->m03F4 = this->current.pos.y;
                    dComIfGp_evmng_cutEnd(this->mEvtStaffId);
                }
                else {
                    this->m0370 = 0;
                    this->m0372 = 0;
                    this->m0384 = 0;
                    this->m036C = 0;
                    this->m0366 = 0;
                    this->m036E = 0;
                    this->m0374 = 0;
                    this->m0376 = 0;
                    this->m0386 = 0;
                    onStateFlg(daSFLG_UNK1_e);
                    if (this->gravity < 0.0f) {
                        this->gravity = 0.0f;
                        this->current.pos.y += 500.0f;
                        this->speed.y = 0.0f;
                    }
                    else {
                        this->speed.y -= 1.0f;
                        if (this->speed.y < -15.0f) {
                            this->speed.y = -15.0f;
                        }
                    }
                }
            }
            else {
                return TRUE;
            }
        }
        if (this->m0298->getPlaySpeed() < 0.01f) {
            if (this->m0350 != 4 && this->m0350 != 0 && this->mShipMode != this->m0350) {
                setPartOnAnime(this->m0350);
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
    int iVar1;
    short sVar2;
    J3DAnmTransform* pAnimRes;
    
    this->mProc = &daShip_c::procTalkReady;
    this->mAnmTransform = NULL;
    if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
        if ((short)(this->shape_angle.y - this->m038C) > 0) {
            this->m03B4 = 8;
        }
        else {
            this->m03B4 = 7;
        }
    }
    else if ((short)(fopAcM_searchPlayerAngleY(this) - this->shape_angle.y) > 0) {
        this->m03B4 = 7;
    }
    else {
        this->m03B4 = 8;
    }
    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, this->m03B4);
    this->m029C->setAnm(pAnimRes, 0, 5.0f, 1.0f, 0.0f, -1.0f, NULL);
    seStart(0x6915, &this->eyePos);
    this->m034C = 8;
    return TRUE;
}

/* 00006440-000064A8       .text procTalkReady__8daShip_cFv */
BOOL daShip_c::procTalkReady() {
    firstDecrementShipSpeed(0.0f);
    setMoveAngle(0);
    if (this->m029C->getPlaySpeed() <= 0.1f) {
        procTalk_init();
    }
    return TRUE;
}

/* 000064A8-00006558       .text procTalk_init__8daShip_cFv */
BOOL daShip_c::procTalk_init() {
    this->mProc = &daShip_c::procTalk;
    this->m034C = 8;
    this->m0430 = -1;
    this->m038A = 12;
    this->mAnmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, this->m038A);
    this->mFrameCtrl.init(this->mAnmTransform->getFrameMax());
    setInitMessage();
    onStateFlg(daSFLG_UNK8000_e);
    return TRUE;
}

/* 00006558-00006720       .text procTalk__8daShip_cFv */
BOOL daShip_c::procTalk() {
    msg_class *msg;
    u16 sVar4;
    
    firstDecrementShipSpeed(0.0f);
    setMoveAngle(0);
    if (this->m0430 == 0xFFFFFFFF) {
        if (dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4)) {
            this->m0430 = fopMsgM_messageSet(this->mNextMessageID, &this->eyePos);
        }
    }
    else {
        msg = fopMsgM_SearchByID(this->m0430);
        if (msg) {
            if (msg->mStatus == 14) {
                if (setNextMessage(msg)) {
                    msg->mStatus = 16;
                }
                else {
                    msg->mStatus = 15;
                    fopMsgM_messageSet(this->mNextMessageID);
                }
            } else if (msg->mStatus == 18) {
                msg->mStatus = 19;
                if (dComIfGp_checkPlayerStatus0(0, 0x10000) && checkStateFlg(daSFLG_UNK400000_e)){
                    return procTurn_init();
                }
                this->m029C->setPlaySpeed(-1.0f);
                dComIfGp_event_onEventFlag(8);
                changeDemoEndProc();
                return TRUE;
            }
        }
    }
    if (this->mFrameCtrl.checkState(2)) {
        if (cM_rndF(2.0f) < 1.0f) {
            sVar4 = 12;
        }
        else {
            sVar4 = 13;
        }
        if (sVar4 != this->m038A) {
            this->m038A = sVar4;
            this->mAnmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, this->m038A);
            this->mFrameCtrl.init(this->mAnmTransform->getFrameMax());
        }
    }
    return TRUE;
}

/* 00006720-0000686C       .text procTurn_init__8daShip_cFv */
BOOL daShip_c::procTurn_init() {
    this->m0430 = -1;
    this->m029C->setPlaySpeed(-1.0f);
    seStart(0x6916, &this->eyePos);
    this->mProc = &daShip_c::procTurn;
    this->m038E = 0;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz cameraPos = camera->mCamera.Eye() - camera->mCamera.Center();
    cameraPos.normalize();
    this->m0450 = camera->mCamera.Center() + (cameraPos * 1600.0f);
    offStateFlg(daSFLG_UNK8000_e);
    this->m037A = 10;
    return TRUE;
}

/* 0000686C-00006C78       .text procTurn__8daShip_cFv */
BOOL daShip_c::procTurn() {
    float fVar1;
    float fVar2;
    short sVar4;
    float fVar5;
    float fVar6;
    cXyz local_c4;
    cXyz local_b8;
    cXyz local_ac;
    
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    local_c4 = this->current.pos - camera->mCamera.Center();
    fVar5 = local_c4.abs();
    local_ac = camera->mCamera.Center() + (this->current.pos - this->m045C);
    local_c4 = this->m0450 - camera->mCamera.Eye();
    fVar6 = local_c4.abs(); 
    if (fVar6 > 1.0f) {
        fVar2 = fVar6 * 0.5f;
        fVar1 = 60.0f;
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
        local_b8 = this->m0450;
    }
    camera->mCamera.Set(local_ac, local_b8);
    if (fVar6 <= 1.0f) {
        sVar4 = this->shape_angle.y;
        cLib_addCalcAngleS2(&this->shape_angle.y, this->m038C, 8, this->m038E);
        cLib_addCalcAngleS2(&this->m038E, 0x800, 8, 0x80);
        this->current.angle.y = this->shape_angle.y;
        setControllAngle(getAimControllAngle(sVar4));
        if (abs((short)(this->shape_angle.y - this->m038C)) < 0x200) {
            cLib_addCalc(&this->speedF, 55.0f, 0.1, 5.0f, 1.0f);
        }
        if (abs((short)(this->m038C - this->shape_angle.y)) < 0x100 && !checkOutRange()) {
            if (this->m037A <= 0) {
                camera->mCamera.Start();
                camera->mCamera.Reset();
                dComIfGp_event_onEventFlag(8);
                changeDemoEndProc();
                this->m038E = 0;
                onStateFlg(daSFLG_UNK100000_e);
            }
            else {
                this->m037A--;
            }
        }
    }
    return TRUE;
}

/* 00006C78-00006DE0       .text procTornadoUp_init__8daShip_cFv */
BOOL daShip_c::procTornadoUp_init() {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    onStateFlg((daSHIP_SFLG)(daSFLG_UNK1_e | daSFLG_UNK1000_e));
    this->m034C = 12;
    this->mProc = &daShip_c::procTornadoUp;
    this->m037A = 1;
    camera->mCamera.Stop();
    this->speed.y = 0.0f;
    this->gravity = 0.0f;
    cXyz tornadoPos(this->mTornadoActor->current.pos.x, this->mTornadoActor->current.pos.y + 2500.0f, this->mTornadoActor->current.pos.z + 4000.0f);
    camera->mCamera.Set(this->current.pos, tornadoPos);
    this->m03A6 = 0;
    fopAcM_seStartCurrent(this->mTornadoActor, 0x186C, 0);
    dComIfGs_onEventBit(0x3E40);
    return TRUE;
}

/* 00006DE0-00006FDC       .text procTornadoUp__8daShip_cFv */
BOOL daShip_c::procTornadoUp() {
    int iVar1;
    daTornado_c* tornadoActor = this->mTornadoActor;
    
    cLib_addCalc(&this->current.pos.x, tornadoActor->getJointXPos(this->m037A), 0.5f, 80.0f, 20.0f);
    
    cLib_addCalc(&this->current.pos.z, tornadoActor->getJointZPos(this->m037A), 0.5f, 80.0f, 20.0f);

    this->current.pos.y += this->speed.y;
    this->speed.y += 2.0f;
    
    if (this->speed.y > 50.0f) {
        this->speed.y = 50.0f;
    }

    if (tornadoActor->getJointYPos(this->m037A) < this->current.pos.y && this->m037A < 11) {
        this->m037A++;
    }

    this->shape_angle.y += 0x1C25;

    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cXyz local_3c(tornadoActor->current.pos.x, this->current.pos.y, tornadoActor->current.pos.z);
    camera->mCamera.Set(local_3c, camera->mCamera.Eye());
    
    if (this->m03A6 == 0 && this->current.pos.y > tornadoActor->current.pos.y + 5000.0f) {
        this->m03A6 = 1;
        iVar1 = (int)cM_rndF(8.0f) + 0xC6;
        if (iVar1 >= 0xCE) {
            iVar1 = 0xCD;
        }
        dStage_changeScene(iVar1, 0.0f, 0, 0xFF);
    }
    
    return TRUE;
}

/* 00006FDC-0000713C       .text procStartModeWarp_init__8daShip_cFv */
BOOL daShip_c::procStartModeWarp_init() {
    this->current.pos.y = this->m03F4 + 5000.0f;
    onStateFlg(daSFLG_UNK1_e);
    this->mProc = &daShip_c::procStartModeWarp;
    this->m034C = 13;
    if (this->m0392 != 10) {
        setPartOffAnime();
    }
    this->m03A6 = 0x1C25;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz local_38(this->current.pos.x, this->m03F4 + 1500.0f, this->current.pos.z + 2000.0f);
    camera->mCamera.Set(this->current.pos, local_38);
    this->m037A = 0;
    fopAcM_seStartCurrent(this, 0x186D, 0);
    return TRUE;
}

/* 0000713C-000074D4       .text procStartModeWarp__8daShip_cFv */
BOOL daShip_c::procStartModeWarp() {
    int iVar5;
    _GXColor diff;
    _GXColor amb;
    cXyz local_30;
    
    daTornado_c* pfVar2 = (daTornado_c*)fopAcM_SearchByID(this->mTactWarpID);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    this->shape_angle.y += this->m03A6;
    this->current.angle.y = this->shape_angle.y;
    if (pfVar2) {
        if (checkStateFlg(daSFLG_UNK8_e) == 0) {
            onStateFlg(daSFLG_UNK8_e);
            pfVar2->current.pos.x = this->current.pos.x;
            pfVar2->current.pos.z = this->current.pos.z;
        }
        iVar5 = 0;
        for (int i = 0; i < 11; iVar5++, i++) {
            if (this->current.pos.y < pfVar2->getJointYPos(i)) break;
        }
        if (iVar5 == 11) {
          iVar5 = 10;
        }
        cLib_chaseF(&this->current.pos.x, pfVar2->getJointXPos(iVar5), 50.0f);
        cLib_chaseF(&this->current.pos.z, pfVar2->getJointZPos(iVar5), 50.0f);
        local_30.x = pfVar2->current.pos.x;
        local_30.z = pfVar2->current.pos.z;
    }
    else {
        local_30.x = this->current.pos.x;
        local_30.z = this->current.pos.z;
    }
    local_30.y = this->current.pos.y;
    camera->mCamera.Set(local_30, camera->mCamera.Eye());
    if (this->m037A == 0) {
        if (this->current.pos.y < this->m03F4) {
            this->current.pos.y = this->m03F4 - 50.0f;
            this->speed.y = 0.0f;
            offStateFlg(daSFLG_UNK1_e);
            this->m037A = 1;
            if (pfVar2 != NULL) {
                pfVar2->m31c = 1;
            }
            dKy_get_seacolor(&diff, &amb);
            this->m03BC.x = 0;
            this->m03BC.y = this->shape_angle.y + 0x8000;
            this->m03BC.z = 0;
            dComIfGp_particle_set(0x285, &this->current.pos, &this->shape_angle, NULL, 0xFF, &this->m1984, -1, &diff);
            dComIfGp_particle_set(0x285, &this->current.pos, &this->m03BC, NULL, 0xFF, &this->m1998, -1, &diff);
        }
        if (pfVar2 != NULL) {
            pfVar2->current.pos.y = this->current.pos.y - 700.0f;
        }
    }
    else if (pfVar2 == NULL || pfVar2->mJointScale[10] < 0.8f) {
        if (pfVar2 != NULL) {
            pfVar2->current.pos.y -= 12.0f;
        }
        this->m03BC.y = this->shape_angle.y + 0x8000;
        cLib_chaseS(&this->m03A6, 0, 0x40);
        if (this->m03A6 < 0x400) {
            camera->mCamera.Start();
            camera->mCamera.Reset();
            this->mTactWarpID = fpcM_ERROR_PROCESS_ID_e;
            this->m1984.end();
            this->m1998.end();
            dComIfGp_evmng_cutEnd(this->mEvtStaffId);
            procPaddleMove_init();
        }
    }
    return TRUE;
}

/* 000074D4-00007684       .text procTactWarp_init__8daShip_cFv */
BOOL daShip_c::procTactWarp_init() {
    _GXColor diff;
    _GXColor amb[3];
    
    this->m034C = 14;
    this->mProc = &daShip_c::procTactWarp;
    if (this->m0392 != 10) {
        setPartOffAnime();
    }
    this->m03A6 = 0;
    this->gravity = 0.0f;
    this->speed.y = 0.0f;
    onStateFlg(daSFLG_UNK1_e);
    this->m037A = 0;
    fopAcM_seStartCurrent(this, 0x186E, 0);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    dCam_getBody()->StartEventCamera(0xe, fopAcM_GetID(this), 0);
    dKy_get_seacolor(amb, &diff);
    this->m03BC.x = 0;
    this->m03BC.y = this->shape_angle.y + 0x8000;
    this->m03BC.z = 0;
    dComIfGp_particle_set(0x0285, &this->current.pos, &this->shape_angle, NULL, 0xFF, &this->m1984, -1, amb);
    dComIfGp_particle_set(0x0285, &this->current.pos, &this->m03BC, NULL, 0xFF, &this->m1998, -1, amb);
    return TRUE;
}

/* 00007684-0000797C       .text procTactWarp__8daShip_cFv */
BOOL daShip_c::procTactWarp() {
    float fVar1;
    int iVar2;
    dCamera_c *this_00;
    BOOL uVar3;
    int iVar4;
    fpc_ProcID fVar5;
    int iVar6;
    
    this->shape_angle.y += this->m03A6;
    this->current.angle.y = this->shape_angle.y;
    daTornado_c* pfVar2 = (daTornado_c*)fopAcM_SearchByID(this->mTactWarpID);
    if (!pfVar2 || fpcM_IsCreating(this->mTactWarpID)) {
        if (this->mTactWarpID == fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_onEventFlag(8);
            this->m1984.end();
            this->m1998.end();
            procPaddleMove_init();
            camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
            dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        }
        uVar3 = 0;
    }
    else {
        if (cLib_chaseS(&this->m03A6, 0x1C25, 0x40) && (pfVar2->mJointScale[10] > 0.8f)) {
            this->speed.y += 1.0f;
            if (this->speed.y > 50.0f) {
                this->speed.y = 50.0f;
            }
            this->current.pos.y += this->speed.y;
            pfVar2->current.pos.y = this->current.pos.y - 700.0f;
            this->m1984.end();
            this->m1998.end();
        }
        else {
            if ((this->m037A == 0) && (this->m03A6 > 0x1000)) {
                this->m037A = 1;
                pfVar2->m31c = 1;
            }
        }
        if (this->m037A == 1) {
            cLib_chaseF(&pfVar2->current.pos.y, this->current.pos.y - 700.0f, 20.0f);
            iVar4 = 0;
            for (int i = 0; i < 11; iVar4++, i++) {
                if (this->current.pos.y < pfVar2->getJointYPos(i)) break;
            }
            if (iVar4 == 11) {
                iVar4 = 10;
            }
              cLib_chaseF(&this->current.pos.x, pfVar2->getJointXPos(iVar4), 50.0f);
              cLib_chaseF(&this->current.pos.z, pfVar2->getJointZPos(iVar4), 50.0f);
        }
        if (this->m037A != 2 && this->current.pos.y > this->m03F4 + 5000.0f ) {
            this->m037A = 2;
            dStage_changeScene(this->mTactWarpPosNum + 0xC5, 0.0f, 0, 0xFF);
            mDoAud_taktModeMuteOff();
        }
        this->m03BC.y = this->shape_angle.y + 0x8000;
        uVar3 = 1;
    }
    return uVar3;
}

/* 0000797C-00007A90       .text procWhirlDown_init__8daShip_cFv */
BOOL daShip_c::procWhirlDown_init() {
    this->mProc = &daShip_c::procWhirlDown;
    this->m034C = 15;
    this->gravity = 0.0f;
    this->speed.y = 0.0f;
    onStateFlg(daSFLG_UNK1_e);
    onStateFlg(daSFLG_UNK1000_e);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz local_38(this->mWhirlActor->current.pos.x, this->mWhirlActor->current.pos.y + 2500.0f, this->mWhirlActor->current.pos.z + 4000.0f);
    camera->mCamera.Set(this->mWhirlActor->current.pos, local_38);
    this->m037A = 0;
    return TRUE;
}

/* 00007A90-00007BEC       .text procWhirlDown__8daShip_cFv */
BOOL daShip_c::procWhirlDown() {  
    this->shape_angle.y += (this->m0408 / 6.2831855f) * 65536.0f;
    if (this->mWhirlActor) {
        this->speedF = 40.0f;
        if (cLib_addCalcPosXZ(&this->current.pos, this->mWhirlActor->current.pos, 1.0f, 40.0f, 10.0f) < 10.0f) {
            this->speed.y -= 0.5f;
            if (this->speed.y < -10.0f) {
                this->speed.y = -10.0f;
            }
            this->current.pos.y += this->speed.y;
            if (this->m037A == 0 && this->current.pos.y < this->m03F4 - 1000.0f) {
                dComIfGs_onEventBit(0x1940);
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), this->m03B2, fopAcM_GetRoomNo(this));
                this->m037A = 1;
            }
        }
    }
    return TRUE;
}

/* 00007BEC-00007DC0       .text procStartModeThrow_init__8daShip_cFv */
BOOL daShip_c::procStartModeThrow_init() {
    this->current.pos.y = this->m03F4 + 2500.0f;
    this->speedF = 100.0f;
    onStateFlg(daSFLG_UNK1_e);
    this->mProc = &daShip_c::procStartModeThrow;
    this->m034C = 16;
    if (this->m0392 != 10) {
        setPartOffAnime();
    }
    this->m03A6 = 3600;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    cXyz local_38(this->current.pos.x + cM_scos(this->current.angle.y) * 300.0f, 
                  this->m03F4 + 150.0f, 
                  this->current.pos.z - cM_ssin(this->current.angle.y) * 300.0f);
    camera->mCamera.Set(this->current.pos, local_38);
    this->current.pos.x -= cM_ssin(this->current.angle.y) * 4500.0f;
    this->current.pos.z -= cM_scos(this->current.angle.y) * 4500.0f;
    this->m037A = 0;
    return TRUE;
}

/* 00007DC0-0000804C       .text procStartModeThrow__8daShip_cFv */
BOOL daShip_c::procStartModeThrow() {
    _GXColor amb;
    _GXColor diff;
    
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    this->shape_angle.y += this->m03A6;
    camera->mCamera.Set(this->current.pos, camera->mCamera.Eye());
    if (this->m037A == 0) {
        if (this->current.pos.y < this->m03F4) {
            this->speed.y = 0.0f;
            this->speedF = 0.0f;
            offStateFlg(daSFLG_UNK1_e);
            this->m037A++;
            dKy_get_seacolor(&amb, &diff);
            amb.r = amb.r * 0.23529412f + 195.0f;
            amb.g = amb.g * 0.23529412f + 195.0f;
            amb.b = amb.b * 0.23529412f + 195.0f;
            this->current.pos.y = this->m03F4;
            dComIfGp_particle_set(0x82D7, &this->current.pos, &this->shape_angle, NULL, 0xFF, NULL, -1, &amb);
            dComIfGp_particle_set(0x82D8, &this->current.pos, &this->shape_angle, NULL, 0xFF, NULL, -1, &amb);
            this->current.pos.y = this->m03F4 - 50.0f;
        }
    }
    else {
        if (cLib_chaseS(&this->m03A6, 0, 0x100)) {
            this->m037A++;
            if(this->m037A == 45) {
                camera->mCamera.Start();
                camera->mCamera.Reset();
                this->current.angle.y = this->shape_angle.y;
                dComIfGp_evmng_cutEnd(this->mEvtStaffId);
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
    _GXColor amb;
    _GXColor diff;
    
    if (checkStateFlg(daSFLG_UNK1_e) && this->current.pos.y - 40.0f > param_1) {
        this->mWaveR.mState = 1;
        this->mWaveL.mState = 1;
        this->mSplash.mState = 1;
        this->mTrack.mState = 1;
    }
    else {
        if (this->speedF <= 0.0f) {
            this->mWaveR.mState = 1;
            this->mWaveL.mState = 1;
            this->mSplash.mState = 1;
        }
        
    }
    fVar3 = this->speedF + 150.0f;
    this->mEffPos.set(this->current.pos.x + fVar3 * cM_ssin(this->shape_angle.y), param_1, this->current.pos.z + fVar3 * cM_scos(this->shape_angle.y));
    getMaxWaterY(&this->mEffPos);
    if (!checkStateFlg(daSFLG_UNK1_e) || param_1 > this->current.pos.y) {
        if (std::fabsf(this->mFwdVel) > 3.0f) {
            if (std::fabsf(this->speedF) > 3.0f && this->mFwdVel * this->speedF > 0.0f) {
                if (this->mFwdVel > 11.0f) {
                    if (this->mWaveL.getEmitter() == NULL) {
                        mEmitter = dComIfGp_particle_set(0x37, &this->mEffPos, &this->shape_angle, NULL, 0xFF, &this->mWaveL);
                        this->mWaveL.setTimer(20);
                        if (mEmitter) {
                            mEmitter->setDirection(wave_l_direction);
                        }
                    }
                    if (this->mWaveR.getEmitter() == NULL) {
                        mEmitter = dComIfGp_particle_set(0x37, &this->mEffPos, &this->shape_angle, NULL, 0xFF, &this->mWaveR);
                        this->mWaveR.setTimer(20);
                        if (mEmitter) {
                            mEmitter->setDirection(wave_r_direction);
                        }
                    }
                    if (this->mSplash.getEmitter() == NULL) {
                        dComIfGp_particle_set(0x35, &this->mEffPos, &this->shape_angle, NULL, 0xFF, &this->mSplash);
                    }
                }
                if (this->mTrack.getEmitter() == NULL) {
                    dComIfGp_particle_setShipTail(0x36, &this->current.pos, &this->shape_angle, NULL, 0, &this->mTrack);
                }
                if (checkStateFlg((daSHIP_SFLG)(daSFLG_UNK1_e | daSFLG_UNK80_e))) {
                    dKy_get_seacolor(&amb, &diff);
                    mEmitter = dComIfGp_particle_set(0x34, &this->mEffPos, &this->shape_angle, NULL, 0xFF, NULL, -1, &amb);
                    if (mEmitter) {
                        fVar1 = 10.0f;
                        fVar2 = (-(this->speed.y - -15.0f) / 30.0f) * 50.0f + 10.0f;
                        if (fVar2 < 10.0f) {
                            fVar2 = fVar1;
                        }
                        else if (fVar2 > 60.0f) {
                            fVar2 = 60.0f;
                        }
                        mEmitter->setRate(fVar2);
                    }
                    seStart(0x6914, &this->current.pos);
                }
            }
        }
    }

    this->mTrack.setIndirectTexData(-0.04f, 4.0f);
    this->mTrack.setSpeed(this->mFwdVel);

    if (this->mFwdVel >= 0.0f) {
        this->mWaveR.setSpeed(0.7f);
        this->mWaveL.setSpeed(0.7f);
    }
    else {
        this->mWaveR.setSpeed(-0.7f);
        this->mWaveL.setSpeed(-0.7f);
    }

    fVar1 = (short)(this->shape_angle.z - param_2) / 16384.0f;

    if (fVar1 > 0.3f) {
        fVar1 = 0.3f;
    }
    else if (fVar1 < -0.3f) {
        fVar1 = -0.3f;
    }

    this->mWaveR.setPitch(fVar1 + 1.0f);
    this->mWaveL.setPitch(1.0f - fVar1);

    this->mSplash.setSpeed(this->mFwdVel);
    this->mSplash.setMaxSpeed(30.0f);
    
    cXyz anchorPos1;
    cXyz anchorPos2;

    anchorPos1.set(-80.0f, -50.0f, -150.0f);
    anchorPos2.set(-40.0f, -100.0f, -350.0f);
    this->mWaveR.setAnchor(&anchorPos1, &anchorPos2);

    anchorPos1.x *= -1.0f;
    anchorPos2.x *= -1.0f;
    this->mWaveL.setAnchor(&anchorPos1, &anchorPos2);

    this->mWaveL.setMaxDisSpeed(2.0f);
    this->mWaveR.setMaxDisSpeed(2.0f);

    this->mWaveL.setMaxSpeed(40.0f);
    this->mWaveR.setMaxSpeed(40.0f);
    return;
}

/* 000085D8-00008688       .text setRoomInfo__8daShip_cFv */
void daShip_c::setRoomInfo() {
    int roomId;
    if (this->mAcch.GetGroundH() != -1e+09f) {
        roomId = dComIfG_Bgsp()->GetRoomId(this->mAcch.m_gnd);
        this->tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(this->mAcch.m_gnd);
        this->m03C4 = dComIfG_Bgsp()->GetGroundCode(this->mAcch.m_gnd);
    }
    else {
        roomId = dStage_roomControl_c::mStayNo;
        this->m03C4 = 0;
    }
    this->tevStr.mRoomNo = roomId;
    this->m034A = dComIfGp_getReverb(roomId);
    this->mStts.SetRoomId(roomId);
    fopAcM_SetRoomNo(this, roomId);
    return;
}

/* 00008688-0000882C       .text incRopeCnt__8daShip_cFii */
// Ajusts the length of KORL's Salvage Arm rope
void daShip_c::incRopeCnt(int lengthChange, int minSegmentLimit) {
    cXyz* ropeSegments = this->mRopeLine.mpLines->mpSegments;
    int currentRopeSegmentIndex = this->mCurrentRopeSegmentIndex;
    cXyz* currentRopeSegment = &this->mRopeLineSegments[currentRopeSegmentIndex];
    int targetRopeSegmentIndex = currentRopeSegmentIndex + lengthChange;

    const int maxRopeSegmentIndex = 250;

    // Ensure the new segment index is within valid bounds
    if (targetRopeSegmentIndex >= maxRopeSegmentIndex) {
        targetRopeSegmentIndex = maxRopeSegmentIndex;
    }
    else if (targetRopeSegmentIndex < minSegmentLimit) {
        targetRopeSegmentIndex = minSegmentLimit;
    }

    int  segmentDifference = targetRopeSegmentIndex - currentRopeSegmentIndex; // Number of segments to increase/decrease the rope by

    if (segmentDifference > 0) {
        // Lengthening the rope: Move all segments down by adding a displacement vector
        cXyz ropeDisplacement = l_rope_base_vec * segmentDifference;
        for (currentRopeSegmentIndex= 0; currentRopeSegmentIndex < this->mCurrentRopeSegmentIndex; currentRopeSegmentIndex++, ropeSegments++) {
            PSVECAdd(ropeSegments, &ropeDisplacement, ropeSegments);
        }
    }
    else {
        // Shortening the rope: Simply adjust the pointer
        ropeSegments += currentRopeSegmentIndex;
    }

    for (currentRopeSegmentIndex = this->mCurrentRopeSegmentIndex; currentRopeSegmentIndex < targetRopeSegmentIndex; currentRopeSegmentIndex++, currentRopeSegment++, ropeSegments++) {
        currentRopeSegment->set(l_rope_base_vec);
        if (this->mCurrentRopeSegmentIndex) {
            ropeSegments->set(*(ropeSegments - 1) - l_rope_base_vec);
        }
    }

    if (segmentDifference != 0) {
        if ((minSegmentLimit == 20) && (targetRopeSegmentIndex == 20)) {
            seStart(JA_SE_LK_SHIP_CRANE_STOP, &this->m102C);
        }
        else {
            seStart(JA_SE_LK_SHIP_CRANE_WORK, &this->m102C);
        }
    }

    this->mCurrentRopeSegmentIndex = targetRopeSegmentIndex;
    return;
}

/* 0000882C-00009314       .text setRopePos__8daShip_cFv */
void daShip_c::setRopePos() {
    float fVar1;
    float fVar2;
    u16 uVar3;
    short y;
    bool bVar9;
    J3DModel *pJVar4;
    MtxP pMVar5;
    int iVar6;
    J3DAnmTransform *pJVar7;
    JPABaseEmitter *pJVar8;
    int iVar10;
    int iVar11;
    short sVar12;
    cXyz *pcVar13;
    short sVar14;
    cXyz *this_00;
    cXyz *pcVar16;
    float fVar17;
    cXyz local_190;
    cXyz local_184;
    cXyz local_178;
    cXyz local_16c;
    cXyz cStack_160;
    cXyz cStack_154;
    cXyz local_148;
    cXyz cStack_13c;
    cXyz cStack_130;
    cXyz local_124;
    cXyz local_118;
    cXyz local_10c;
    cXyz cStack_100;
    float local_f4;
    float local_f0;
    float local_e8;
    float local_e4;
    float local_e0;
    float local_fc;
    cXyz local_dc;
    cXyz local_d0;
    cXyz local_c4;
    cXyz local_b8;
    float local_ac;
    float local_a8;
    float local_a4;
    uint uStack_84;
    uint uStack_7c;
    uint uStack_74;
    uint uStack_6c;

    cXyz local_f8;
    cXyz local_ec;

    static cXyz ripple_scale(0.6f, 0.6f, 0.6f);
    static Vec rope_offset = {160.0f, 0.0f, 0.0f};
    static Vec water_drop_scale = {1.5f, 1.0f, 1.5f};
    
    cXyz* ropeSegments;
    cXyz* currentRopeSegment;
    int currentRopeSegmentIndex;

    currentRopeSegmentIndex = this->mCurrentRopeSegmentIndex;
    if (!currentRopeSegmentIndex) {
        currentRopeSegment = this->mRopeLine.mpLines->mpSegments;
        ropeSegments = this->mRopeLineSegments;
    }
    else {
        currentRopeSegment = &this->mRopeLine.mpLines->mpSegments[currentRopeSegmentIndex + -1];
        ropeSegments = this->mRopeLineSegments + currentRopeSegmentIndex;
    }
    local_f8.x = currentRopeSegment->x;
    local_f8.y = currentRopeSegment->y;
    local_f8.z = currentRopeSegment->z;
    PSMTXMultVec(this->mpSalvageArmModel->getAnmMtx(1), &rope_offset, currentRopeSegment);
    if (this->mProc == &daShip_c::procCraneUp) {
        local_ec.set(this->mpLinkModel->getBaseTRMtx()[0][3] - currentRopeSegment->x, 
                     this->mpLinkModel->getBaseTRMtx()[1][3] - currentRopeSegment->y, 
                     this->mpLinkModel->getBaseTRMtx()[2][3] - currentRopeSegment->z);
        local_ec.normalize();
        PSVECScale(&local_ec, &local_ec, 10.0f);
        currentRopeSegment--;
        ropeSegments--;
        for (int i = this->mCurrentRopeSegmentIndex + -2; i >= 0; i--, currentRopeSegment--, ropeSegments--) {
            currentRopeSegment->set(*currentRopeSegment + local_ec);
            ropeSegments->set(cXyz::Zero);
        }
    }
    else {
        currentRopeSegment--;
        ropeSegments--;
        for (int i = this->mCurrentRopeSegmentIndex + -2; i >= 0; i--, currentRopeSegment--, ropeSegments--) {
            local_f8.x = currentRopeSegment->x;
            local_f8.y = currentRopeSegment->y;
            local_f8.z = currentRopeSegment->z;
            if (ropeSegments->y < this->m03F4) {
                PSVECScale(ropeSegments, ropeSegments, 0.6f);
            }
            else {
                PSVECScale(ropeSegments, ropeSegments, 0.9f);
            }
            ropeSegments->y -= 3.0f;
            PSVECAdd(currentRopeSegment, ropeSegments, currentRopeSegment);
            local_ec.set(*currentRopeSegment - *(currentRopeSegment + 1));
            fVar17 = local_ec.abs();
            if (fVar17 < 0.01f) {
                currentRopeSegment->set(*(currentRopeSegment + 1) + l_rope_base_vec);
            }
            else {
                currentRopeSegment->set(*(currentRopeSegment + 1) + (local_ec * 10.0f)/fVar17);
            }
            cStack_160 = (*currentRopeSegment - local_ec) * 0.05f;
            PSVECAdd(ropeSegments, &cStack_160, ropeSegments);
        }
        if (this->mCurrentRopeSegmentIndex == 20 && checkStateFlg(daSFLG_UNK10000000_e)) {
            pMVar5 = this->mpSalvageArmModel->getAnmMtx(0);
            local_d0.x = pMVar5[0][3];
            local_d0.y = pMVar5[1][3];
            local_d0.z = pMVar5[2][3];
            PSVECSubtract(&local_d0, this->mRopeLine.mpLines->mpSegments, &local_d0);
            local_190.x = local_d0.x;
            local_190.y = 0.0f;
            local_190.z = local_d0.z;
            fVar17 = PSVECSquareMag(&local_190);
            if (fVar17 < 2500.0f) {
                pcVar16 = (cXyz *)&this->mRopeLineSegments;
                local_dc.z = cM_scos(this->shape_angle.x) * 16.0f;
                if (this->shape_angle.x <= 0) {
                    local_dc.z *= -1.0f;
                }
                local_dc.x = local_dc.z * cM_ssin(this->shape_angle.y);
                local_dc.y = 0.0;
                local_dc.z = local_dc.z * cM_scos(this->shape_angle.y);
                iVar11 = 0;
                for (int i = 0; i < 20; i++, pcVar16++) {
                    PSVECAdd(pcVar16, &local_dc, pcVar16);
                    PSVECScale(&local_dc, &local_dc, 0.95f);
                }
                offStateFlg(daSFLG_UNK1000000_e);
            }
        }
    }
    currentRopeSegment = this->mRopeLine.mpLines->mpSegments;
    if (this->mCurrentRopeSegmentIndex > 2) {
        local_16c = *currentRopeSegment - *(currentRopeSegment + 1);
        sVar14 = 0;
        sVar12 = 0;
    }
    else {
        pMVar5 = this->mpSalvageArmModel->getAnmMtx(0);
        local_e0 = pcVar16->z - pMVar5[2][3];
        local_e4 = pcVar16->y - pMVar5[1][3];
        local_e8 = pcVar16->x - pMVar5[0][3];
        sVar14 = 0x7fff;
        iVar11 = this->m0398 * -2 + 0x8000;
        iVar11 = iVar11 - (0x8000 - this->m039A) * ((float)this->m0398 / (float)this->m039A);
        sVar12 = (short)iVar11;
    }
    fVar17 = this->mpLinkModel->getBaseTRMtx()[1][3];
    local_f4 = cM_scos(this->shape_angle.y) * local_16c.x - cM_ssin(this->shape_angle.y) * local_16c.z;
    local_f0 = local_16c.y;
    local_fc = cM_ssin(this->shape_angle.y) * local_16c.x - cM_scos(this->shape_angle.y) * local_16c.z;
    PSMTXTrans(mDoMtx_stack_c::get(), pcVar16->x, pcVar16->y, pcVar16->z);
    fVar1 = std::sqrtf(local_f0 * local_f0 + local_fc * local_fc);
    iVar11 = cM_atan2s(-local_f4, fVar1);
    y = this->shape_angle.y;
    iVar6 = cM_atan2s(local_fc, local_f0);
    mDoMtx_ZXYrotM(mDoMtx_stack_c::get(), sVar14 + (short)iVar6, y, sVar12 + (short)iVar11);
    mDoMtx_XrotM(mDoMtx_stack_c::get(),-0x4000);
    if (this->m0392 == 11) {
        pJVar7 = this->m0298->getAnm();
        //(**(code **)((pJVar7->parent).vtbl + 0xc))(pJVar7,6,&local_ac);
        mDoMtx_stack_c::scaleM(local_ac, local_a8, local_a4);
    }
    mDoMtx_stack_c::copy(this->mpLinkModel->getBaseTRMtx());
    fVar1 = currentRopeSegment->y;
    getMaxWaterY(currentRopeSegment);
    fVar2 = currentRopeSegment->y;
    currentRopeSegment->y = fVar1;
    if (fVar2 > currentRopeSegment->y) {
        ropeSegments = currentRopeSegment;
        for (int i = 0; i < this->mCurrentRopeSegmentIndex; i++, ropeSegments++) {
            if (ropeSegments->y <= currentRopeSegment->y) {
                currentRopeSegment = ropeSegments;
            }
        }
        this->m1020.x = pcVar16->x;
        this->m1020.y = fVar2;
        this->m1020.z = pcVar16->z;
        if (this->mRipple.getEmitter() == NULL) { 
            dComIfGp_particle_setShipTail(0x33, &this->m1020, NULL, &ripple_scale, 0xFF, &this->mRipple);
            if (this->mRipple.getEmitter() != NULL) {
                this->mRipple.setRate(0.0f);
                if (this->m034F == 0) {
                    fopKyM_createWpillar(&this->m1020, 0.7f, 0.7f, 0);
                    seStart(0x381C, &this->m1020);
                    dComIfGp_getVibration().StartShock(3, 1, cXyz(0.0f, 1.0f, 0.0f));
                }
            }
        }
    }
    else {
        if (fVar17 < fVar2 && this->m034F == 0 && this->mCurrentRopeSegmentIndex >= 20) {
            this->m034F = 20;
            seStart(0x381D, &this->m1020);
            if (this->m034C != 11) {
                if (this->m19AC.getEmitter() == NULL) {
                    ropeSegments = this->mRopeLine.mpLines->mpSegments;
                    pJVar8 = dComIfGp_particle_setP1(0x38, ropeSegments, NULL, NULL, 0xFF, &this->m19AC);
                    if(pJVar8) {
                        pJVar8->setGlobalParticleScale(JGeometry::TVec3<f32>(1.5f, 1.5f, 1.0f));
                        pJVar8->setEmitterScale(water_drop_scale);
                        pJVar8->setLifeTime(30);
                    }
                }
                
                fopKyM_createWpillar(&this->m1020, 0.5f, 0.7f, 0);
                dComIfGp_getVibration().StartShock(3, 1, cXyz(0.0f, 1.0f, 0.0f));
                
                if (this->m19C0.getEmitter() == NULL) {
                    pJVar8 = dComIfGp_particle_setShipTail(0x33, &this->m1074, NULL, &ripple_scale, 0xFF, &this->m19C0);
                    if (pJVar8) {
                        pJVar8->setVolumeSize(30);
                    }
                }
            }
        }
        this->mRipple.end();
    }
    if (this->m034F) {
        this->m034F--;
    }
    if (this->m19AC.getEmitter() == 0) {
        this->m19C0.end();
    }
    this->m1074.set(this->mRopeLine.mpLines->mpSegments->x + cM_rndFX(20.0f), this->m03F4, this->mRopeLine.mpLines->mpSegments->z + cM_rndFX(20.0f));
    return;
}

/* 00009314-00009384       .text getAnglePartRate__8daShip_cFv */
f32 daShip_c::getAnglePartRate() {
    float fVar1;
    if (this->m0392 == 10) {
        fVar1 = 0.33333334f * (3.0f - this->m0298->getFrame());
    }
    else {
        fVar1 = 0.33333334f * (this->m0298->getFrame() - 5.0f);
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
    float fVar1;
    float fVar5;
    cXyz local_20;
    
    this->mTornadoActor = (daTornado_c*)fopAcM_SearchByID(this->mTornadoID);
    if (!this->mTornadoActor) {
        offTornadoFlg();
    }
    else {
        local_20 = this->current.pos - this->mTornadoActor->current.pos;
        this->m0400 = cXyz(local_20.x, 0.0f, local_20.z).abs();
        this->m040C = cM_atan2f(local_20.x, local_20.z);
        
        dCam_getBody()->SetTypeForce("Tornado", this->mTornadoActor);
        this->m0404 = (6000.0f - this->m0400) * 0.0004f;
        if (this->m0404 < 0.0f) {
            this->m0404 = 0.0f;
        }
        daTornado_c* pfVar2 = this->mTornadoActor;
        float dx = pfVar2->getJointXPos(0) - this->current.pos.x;
        float dz = pfVar2->getJointZPos(0) - this->current.pos.z;
        float distXZ = std::sqrtf(dx * dx + dz * dz);
        if (!checkStateFlg(daSFLG_UNK1000_e) && distXZ < 3500.0f) {
            if(daPy_getPlayerLinkActorClass()->shipSpecialDemoStart()) {
                procTornadoUp_init();
            }
        }
    }
    return;
}

/* 000095E4-00009790       .text setWhirlActor__8daShip_cFv */
void daShip_c::setWhirlActor() {
    cXyz local_20;
    
    this->mWhirlActor = (daTornado_c*)fopAcM_SearchByID(this->mWhirlID);
    if (!this->mWhirlActor) {
        offWhirlFlg();
    }
    else {
        local_20 = this->current.pos - this->mWhirlActor->current.pos;
        this->m0400 = cXyz(local_20.x, 0.0f, local_20.z).abs();
        this->m040C = cM_atan2f(local_20.x, local_20.z);
        dCam_getBody()->SetTypeForce("Tornado", this->mWhirlActor);
        this->m0404 = (4000.0f - this->m0400) * 0.00028571428f;
        if (this->m0404 < 0.0f) {
            this->m0404 = 0.0f;
        }

        if (this->m0400 < 500.0f && !checkStateFlg(daSFLG_UNK1000_e)) {
            if(daPy_getPlayerLinkActorClass()->shipSpecialDemoStart()) {
                procWhirlDown_init();
            }
        }
    }
    return;
}

/* 00009790-00009B4C       .text setHeadAnm__8daShip_cFv */
void daShip_c::setHeadAnm() {
    s32 newState = -1;
    float speed;
    float morph;

    if (dComIfGp_event_runCheck()) {
        if (this->mEvtStaffId == fpcM_ERROR_PROCESS_ID_e &&
            (dComIfGp_evmng_startCheck("SV_TALK_P1_1ST") ||
             dComIfGp_evmng_startCheck("SV_TALK_P1_2ND") ||
             dComIfGp_evmng_startCheck("SV_TALK_P4_1ST"))) {
            newState = 14;
        } else if (this->m03B4 == 14 || this->m03B4 == 6) {
            newState = 7;
        }
    } 
    else if (dComIfGp_checkPlayerStatus0(0, 0x10000)) { 
        if (dComIfGp_checkPlayerStatus0(0, 0x287000) || 
            dComIfGp_checkPlayerStatus1(0, 8) || 
            this->m034C == 9) {
            newState = 14;
        } 
        else if ((!dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02)) &&
                 (this->mSph.ChkTgHit() || this->mCyl[0].ChkTgHit() ||
                  this->mCyl[1].ChkTgHit() || this->mCyl[2].ChkTgHit())) {
            this->m03B4 = 7;
            newState = 6;
        } 
        else if (this->m03B4 != 6 || std::fabsf(this->m029C->getPlaySpeed()) < 0.01f) {
            newState = 7;
        }
    } 
    else {
        if ((!dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02)) &&
            (this->mSph.ChkTgHit() || this->mCyl[0].ChkTgHit() ||
             this->mCyl[1].ChkTgHit() || this->mCyl[2].ChkTgHit())) {
            this->m03B4 = 7;
            newState = 6;
        } 
        else if (this->m03B4 == 6 || this->m03B4 == 5) {
            if (this->m029C->getPlaySpeed() < 0.01f) {
                newState = 7;
            }
        } 
        else if (!(this->m03B4 != 7 && this->m03B4 != 8) && 
                 std::fabsf(this->m029C->getPlaySpeed()) < 0.01f && 
                 cM_rnd() < 0.4f && (g_Counter.mTimer & 0x1FF) == 0x1FF && 
                 (!dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02)) &&
                 !checkStateFlg(daSFLG_UNK40000000_e)) {
            newState = 5;
        } 
        else if (this->m03B4 != 8) {
            newState = 7;
        }
    }

    if (this->m03B4 != newState && newState != -1) {
        if (newState == 5) {
            speed = 1.0f;
            morph = 5.0f;
        } 
        else if (newState == 6) {
            speed = 1.0f;
            morph = 0.0f;
        }
        else {
            speed = 0.0f;
            morph = 5.0f;
        }
        this->m03B4 = (short)newState;
        this->m029C->setAnm((J3DAnmTransform *)dComIfG_getObjectRes(l_arcName, this->m03B4), 0, morph, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00009B4C-0000B978       .text execute__8daShip_cFv */
BOOL daShip_c::execute() {
    float fVar2;
    float fVar3;
    float fVar4;
    uint uVar12;
    Mtx* pMVar13;
    int unaff_r23;
    int iVar23;
    float dVar27;
    float dVar28;
    s16 local_190;
    s16 local_18e;
    int local_188;
    csXyz local_184;
    cXyz cStack_164;
    cXyz cStack_158;
    cXyz cStack_14c;
    cXyz cStack_140;
    cXyz cStack_134;
    cXyz cStack_11c;
    cXyz cStack_110;
    cXyz local_110;
    cXyz local_104;
    cXyz local_e0;
    cXyz local_d4;
    cXyz cStack_c8;
    cXyz cStack_bc;
    cXyz cStack_98;
    BOOL bVar20;
    short sVar16;
    short sVar5;
    int iVar6;  

    static cXyz sail_offset(0.5f, 155.0f, 50.0f);
    static cXyz sph_offset(-5.0f, 0.0f, 0.0f);
    static Vec cyl_offset = {100.0f, -20.0f, -100.0f};

    fVar2 = this->mFwdVel;
    fVar3 = this->speedF;
    this->m0351 = 0xFF;
    this->m0404 = 0.0f;
    this->m0428 = NULL;
    if (this->mTornadoID != fpcM_ERROR_PROCESS_ID_e) {
        setTornadoActor();
        this->mWhirlActor = NULL;
    }
    else {
        this->mTornadoActor = NULL;
        if (this->mWhirlID != fpcM_ERROR_PROCESS_ID_e) {
            setWhirlActor();
        }
        else {
            this->mWhirlActor = NULL;
        }
    }
    if (dComIfGp_event_runCheck()) {
        this->mStickMVal = 0.0f;
        this->mStickMAng = 0;
        this->mEvtStaffId = dComIfGp_evmng_getMyStaffId("Ship", this, 0);
        if (this->mEvtStaffId != fpcM_ERROR_PROCESS_ID_e) {
            char* cutName = dComIfGp_getPEvtManager()->getMyNowCutName(this->mEvtStaffId);
            if (cutName) {
                this->m0351 = (cutName[0] - '0') * 10 + (cutName[1] - '0');
            }
        }
        this->m03B8 = 0;
        offStateFlg(daSFLG_UNK2000000_e);
    }
    else {
        if (daPy_getPlayerLinkActorClass()->checkNoControll()) {
            this->mStickMVal = 0.0f;
            this->mStickMAng = 0;
        }
        else {
            this->mStickMVal = g_mDoCPd_cpadInfo[0].mMainStickValue;
            this->mStickMAng = g_mDoCPd_cpadInfo[0].mMainStickAngle + 0x8000;
        }
        this->mEvtStaffId = fpcM_ERROR_PROCESS_ID_e;
    }
    
    offStateFlg(daSHIP_SFLG(0x81241C0)); //~(daSFLG_UNK40_e | daSFLG_UNK100_e | daSFLG_UNK2000_e | daSFLG_UNK4000_e | daSFLG_UNK10000_e | daSFLG_UNK8000000_e)
    
    if (this->m0388 > 0) {
        this->m0388--;
    }

    if (checkStateFlg(daSFLG_UNK20_e) != 0) {
        this->speed.y = 5.0f;
        offStateFlg(daSFLG_UNK20_e);
    }

    this->m0298->play(NULL, 0, 0);
    this->m029C->play(NULL, 0, 0);

    if(!(this->m034C == 12 || this->m034C == 15 || this->m034C == 13 || this->m034C == 16 || this->m034C == 7 || this->m034C == 11 || this->m034C == 8)) {
        if(this->eventInfo.checkCommandTalk()) {
            if (this->mNextMessageID == 0x1682) {
                dComIfGp_onMenuCollect();
            }
            
            if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
                procTalkReady_init();
            }
            else {
                procTalk_init();
            }
        }
        else { 
            if (dComIfGp_checkPlayerStatus0(0,0x10000) && checkOutRange()) {
                if (checkStateFlg(daSFLG_UNK1_e)) {
                    cLib_addCalcAngleS2(&this->shape_angle.y, this->m038C, 8, this->m038E);
                    cLib_addCalcAngleS2(&this->m038E, 0x1800, 8, 0x200);
                    this->current.angle.y = this->shape_angle.y;
                }
                else {
                    this->eventInfo.onCondition(dEvtCnd_CANTALK_e);
                    fopAcM_orderSpeakEvent(this);
                }
                goto label_1; //Not sure how to structure this logic without this goto statement
            }
            else if (checkOutRange()) {
                firstDecrementShipSpeed(0.0f);   
            }
            this->eventInfo.onCondition(dEvtCnd_CANTALK_e);
        }
    }
    label_1:

    this->mpGrid = NULL;
    this->mpGrid = (daGrid_c*)fopAcM_SearchByID(this->mGridID);
    dDemo_actor_c* demoActor = dComIfGp_demo_getActor(this->demoActorID);

    if (demoActor) {
        procToolDemo_init();
    }
    else {
        if(!(this->mEvtStaffId == fpcM_ERROR_PROCESS_ID_e || this->m0351 == 2 || this->m0351 == 9)) {
            procZevDemo_init();
        }
        else {
            if (this->m0351 == 2) {
                procCraneUp_init();
              }
        }
    }

    short sVar26 = this->m0366;

    if (this->mAnmTransform) {
        this->mFrameCtrl.update();
        this->mAnmTransform->setFrame(this->mFrameCtrl.getFrame());
        if (!checkStateFlg(daSFLG_UNK8000_e) && this->mFrameCtrl.checkState(2)) {
            this->mAnmTransform = NULL;
        }
    }

    if (this->m0351 == 8 || checkStateFlg(daSFLG_UNK4000000_e)) {
        bVar20 = TRUE;
    }
    else {
        bVar20 = FALSE;
    }
    
    if (this->mProc) {
        (this->*mProc)();
    }

    if (this->m0351 == 8 || checkStateFlg(daSFLG_UNK4000000_e)) {
        this->m0366 = -0x2000;
        sVar26 = this->m0366;
    }
    else if (bVar20) {
        this->m0366 = 0;
        sVar26 = 0;
    }
    
    if (!checkStateFlg(daSFLG_UNK1_e)) {
        if (!(this->m034C == 12 || this->m034C == 15 || this->m034C == 7 || this->m034C == 11 || this->m034C == 13 || this->m034C == 16 || dComIfGp_event_runCheck())) {
            if (this->mTornadoActor) {
                sVar16 = this->shape_angle.y;
                cLib_addCalcAngleS(&this->shape_angle.y, this->m040C * 10430.378f + 20480.0f, 5, 0x2000, 0x200);
                setControllAngle(getAimControllAngle(sVar16));
                this->current.angle.y = this->shape_angle.y;
                
            }
            else {
                if (this->mWhirlActor) {
                    sVar16 = this->shape_angle.y;
                    if (this->m0352) {
                        sVar5 = this->m040C * 10430.378f + 20480.0f;
                    }
                    else {         
                        sVar5 = this->m040C * 10430.378f + 32768.0f;
                    }
                    cLib_addCalcAngleS(&this->shape_angle.y, sVar5, 5, 0x2000, 0x200);
                    setControllAngle(getAimControllAngle(sVar16));
                    this->current.angle.y = this->shape_angle.y;
                }
            }
        }
        sVar16 = -this->m0384;
        sVar5 = sVar16 * 0.05f;
        if (sVar5 == 0) {
            if (sVar16 > 0) {
                sVar5 = 1;
            }
            else if (sVar16 < 0) {
                sVar5 = -1;
            }
        }
        this->m0386 += sVar5;
        this->m0384 += this->m0386;
        cLib_addCalcAngleS(&this->m0386, 0, 30, 0x1000, 1);
    }
    else {
        cLib_addCalcAngleS(&this->m0384, -0x800, 3, 0x500, 0x300);
    }

    this->m045C = this->current.pos;

    if (checkStateFlg(daSFLG_UNK2000000_e) == 0) {
        cLib_chaseS(&this->m03B8, 0, 0x80);
    }
    else {
        cLib_chaseS(&this->m03B8, 0x4E8, 0x80);
    }

    if (!(this->m034C == 12 || this->m034C == 15)) {
        if (!(this->m034C == 7 || this->m034C == 11)) {
            if (!(!dComIfGp_event_runCheck() && !daPy_getPlayerLinkActorClass()->checkNoControll() || this->mEvtStaffId != fpcM_ERROR_PROCESS_ID_e || this->m034C == 8 || this->m034C == 16 || checkStateFlg(daSFLG_UNK100000_e))) {
                if (checkStateFlg(daSFLG_UNK20000000_e)) {
                    if (this->speedF >= 10.0f) {
                        firstDecrementShipSpeed(10.0f);
                    }
                    else {
                        this->speedF = 0.0f;
                    }
                }
            }
            float fVar4;
            if (!dComIfGp_event_runCheck() && !checkStateFlg(daSFLG_UNK1_e) && checkForceMove()) {
                this->speedF = fVar3;
                if (this->mTornadoActor) {
                    fVar4 = this->m0404 * 40.0f + 30.0f;
                    if (!dComIfGp_checkPlayerStatus0(0,0x1000) || !dComIfGp_checkCameraAttentionStatus(0,0x20)) {
                        fVar4 *= 1.2f;
                    }
                }
                else {
                    fVar4 = this->m0404 * 30.0f + 10.0f;
                    if (!dComIfGs_getBombNum() && fopAcM_GetRoomNo(this) == 0x2C) {
                          fVar4 *= 1.2f;
                    }
                }
                firstDecrementShipSpeed(fVar4);
            }

            this->shape_angle.y += this->m03B8;
            this->current.angle.y += this->m03B8;

            if (checkStateFlg(daSFLG_UNK1_e)) {
                if (checkStateFlg(daSFLG_UNK2000000_e)) {
                    cLib_chaseF(&this->speed.y, 20.0f, 1.0f - this->gravity);
                    this->speedF = fVar3;
                    cLib_chaseF(&this->speedF, 55.0f, 3.0f);
                    offStateFlg(daSFLG_UNK2000000_e);
                }

                if (this->speed.y > 0.0f && this->speed.y <= -this->gravity) {
                    onStateFlg(daSFLG_UNK100_e);
                }

                fopAcM_posMoveF(this, (cXyz *)&this->mStts);
                
                this->m1044 = cXyz::Zero;
            }
            else {
                if (checkForceMove() && !dComIfGp_event_runCheck()) {
                    if (this->mTornadoActor) {
                        if (!dComIfGp_checkPlayerStatus0(0,0x1000) || !dComIfGp_checkCameraAttentionStatus(0, 0x20)) {
                            fVar3 = 25.0f;
                        }
                        else {
                            fVar3 = 5.0f;
                        }
                    }
                    else {
                        if (!dComIfGs_getBombNum() && fopAcM_GetRoomNo(this) == 0x2C) {
                            fVar3 = 10.0f;
                        }
                        else {
                            fVar3 = 0.6f;
                        }
                    }

                    cLib_chaseF(&this->m0400, 0.0f, fVar3);

                    this->m0408 = std::fabsf(this->speedF) / this->m0400;
                    
                    this->m040C += this->m0408;

                    if (this->mTornadoActor) {
                        this->current.pos.x = this->mTornadoActor->current.pos.x + (this->m0400 * cM_fsin(this->m040C));
                        this->current.pos.z = this->mTornadoActor->current.pos.z + (this->m0400 * cM_fcos(this->m040C));
                        unaff_r23 = 1;
                    }
                    else {
                        if (this->m0352) {
                            this->current.pos.x = this->mWhirlActor->current.pos.x + (this->m0400 * cM_fsin(this->m040C));
                            this->current.pos.z = this->mWhirlActor->current.pos.z + (this->m0400 * cM_fcos(this->m040C));
                            unaff_r23 = 1;
                        }
                        else {
                            fVar3 = this->current.pos.y;
                            fopAcM_posMoveF(this, (cXyz *)&this->mStts);
                            this->current.pos.y = fVar3;
                        }
                    }
                    if (unaff_r23 != 0) {
                        cXyz cStack_110(this->current.pos - this->old.pos);
                        dVar27 = cStack_110.absXZ();
                        if (dVar27 > 1.0f) {
                            fVar3 = this->speedF / dVar27;
                            this->current.pos.x = this->old.pos.x + cStack_110.x * fVar3;
                            this->current.pos.z = this->old.pos.z + cStack_110.z * fVar3;
                        }
                    }
                }
                else {
                    this->speed.x = (this->speedF * cM_ssin(this->current.angle.y)) * cM_scos(this->m0370);
                    this->speed.y = -this->speedF * cM_ssin(this->m0370);
                    this->speed.z = (this->speedF * cM_scos(this->current.angle.y)) * cM_scos(this->m0370);
                    fopAcM_posMove(this, (cXyz *)&this->mStts);
                    if (dComIfGp_event_runCheck()) {
                        this->m1044 = cXyz::Zero;
                        
                    }
                    else {
                        if (this->mAcch.GetGroundH() == -1e+09f || dPath_GetPolyRoomPathVec(*this->mAcch.pm_out_poly_info,&cStack_98, &local_188) & 0xFF) {
                            cStack_11c.normalizeZP();
                            PSVECScale(&cStack_98, &cStack_98, local_188 >> 1);
                            cLib_addCalcPosXZ(&this->m1044, cStack_98, 0.5f, 5.0f, 1.0f);
                        }
                        else {
                            cLib_addCalcPosXZ(&this->m1044, cXyz::Zero, 0.05f, 0.1f, 0.02f);

                        }
                        PSVECAdd(&this->current.pos, &this->m1044, &this->current.pos);
                    }
                }
            }
        }
        else {
            this->m1044 = cXyz::Zero;
            if (this->mEvtStaffId == fpcM_ERROR_PROCESS_ID_e) {
                cXyz cStack_128(this->current.pos - this->old.pos);
                if (checkStateFlg(daSFLG_UNK1_e)) {
                    this->speedF = cStack_128.absXZ();
                }
                else {
                    this->speedF = cStack_128.abs();
                }
            }
            else {
                this->speed.x = (this->speedF * cM_ssin(this->current.angle.y)) * cM_scos(this->m0370);
                if (!(this->m0351 == 7 || this->m0351 == 10 || this->m0351 == 11)) {
                    this->speed.y = -this->speedF * cM_ssin(this->m0370);
                }
                this->speed.z = (this->speedF * cM_scos(this->current.angle.y)) * cM_scos(this->m0370);
                fopAcM_posMove(this, (cXyz*)&this->mStts);
            }
        }
    }
    this->mStts.ClrCcMove();
    
    cXyz local_b0(this->current.pos);
    
    this->mAcchCir[3].SetWall(-600.0f - this->current.pos.y, 250.0f);
    
    this->mAcch.CrrPos(g_dComIfG_gameInfo.play.mBgS);

    if (checkForceMove()) {
        this->current.pos = local_b0;
    }

    setRoomInfo();

    if (this->m034C == 14) {
        this->current.pos.x = local_b0.x;
        this->current.pos.z = local_b0.z;
    }

    setYPos();

    float diff = this->m03F4 - this->current.pos.y;

    this->mTrack.mBaseY = this->m03F4;
    this->mTrack.mMinY = this->m03F8;

    if (!checkStateFlg(daSFLG_UNK1_e)) {
        setWaveAngle(&local_190, &local_18e);
    }
    else {
        local_190 = this->m037C;
        local_18e = this->m037E;
    }

    diff += 5.0f;

    if (diff > this->m03D8) {
        this->m03D8 = diff;
    }
    else {
        cLib_chaseF(&this->m03D8, diff, 3.0f);
    }

    this->m037C = this->shape_angle.x;
    this->m037E = this->shape_angle.z;

    if (this->m034C == 14) {
        this->shape_angle.x = 0;
        this->shape_angle.z = 0;
    }
    else {
        this->shape_angle.x = this->m0370 + this->m0384;
        this->shape_angle.z = this->m036C + this->m0372;
    }

    PSMTXTrans(mDoMtx_stack_c::get(), this->current.pos.x, this->current.pos.y, this->current.pos.z);
    
    mDoMtx_ZXYrotM(mDoMtx_stack_c::get(), this->shape_angle.x, this->shape_angle.y, this->shape_angle.z);
    
    J3DModel* mModel1 = this->m0298->getModel();
    J3DModel* mModel2 = this->m029C->getModel(); 
    
    mModel1->setBaseTRMtx(mDoMtx_stack_c::get());
    this->m0298->calc();
    
    setHeadAnm();
    
    mModel2->setBaseTRMtx(mModel1->getAnmMtx(4));
    this->m029C->calc();

    if (this->mShipMode == UsingSalvageArm) {
        if (this->m0392 == 10) {
            this->m039A = getAnglePartRate() * this->m039A;
            this->m039C *= getAnglePartRate();
            incRopeCnt(-0x14, 0);
        }
        this->mpSalvageArmModel->calc();
        setRopePos();
        mDoMtx_multVecZero(this->mpSalvageArmModel->getAnmMtx(1), &this->m102C);
        if (this->mProc == &daShip_c::procCrane || this->mProc == &daShip_c::procCraneUp) {
            this->m0434 = this->mRopeLine.mpLines->mpSegments;
        }
        else {
            this->m0434 = NULL;
        }
    }
    else {
        this->m19C0.end();
        this->mRipple.end();
        this->m19AC.end();

        this->mCurrentRopeSegmentIndex = 0;

        this->m0434 = NULL;

        if (this->mShipMode == UsingCannon) {
            mDoMtx_multVecZero(this->mpCannonModel->getAnmMtx(2), &this->m1038);
            
            if (this->mProc != &daShip_c::procCannon) {
                this->m0396 = getAnglePartRate() * 16384.0f;
                this->m0394 *= getAnglePartRate();
            
            }
            
            this->mpCannonModel->calc();
            
            if (this->m037A == 30) {
                cMtx_multVec(this->mpCannonModel->getAnmMtx(2), &l_cannon_top, &cStack_bc);

                local_184.set(getCannonAngleX(), this->shape_angle.y + this->m0394, this->shape_angle.z);

                daBomb_c* this_00 = (daBomb_c *)fopAcM_fastCreate(0x128, daBomb_c::prm_make(daBomb_c::STATE_4, FALSE, TRUE), &cStack_bc, this->tevStr.mRoomNo, &local_184);

                int bombId;
                if (this_00) {
                    if (this_00) {
                        bombId = ((base_process_class*)this_00)->mBsPcId;
                    }
                    else {
                        bombId = 0xffffffff;
                    }

                    dCam_getBody()->ForceLockOn(bombId);

                    this_00->setNoGravityTime(8);

                    this_00->speedF = cM_scos(local_184.x) * 110.0f;
                    this_00->speedF = -(cM_ssin(local_184.x) * 110.0f);

                    this_00->gravity = -2.5f;

                    seStart(0x2852, &this->m1038);

                    onStateFlg(daSFLG_UNK20000_e);

                    dComIfGp_setItemBombNumCount(-1);

                    this->m029C->setPlaySpeed(1.0f);
                    this->m029C->setFrame(0.0f);
                }
                this->m037A--;
            }  
        }
    }

    cMtx_multVec(mModel1->getAnmMtx(10), &l_tiller_top_offset, &this->m0438);

    MtxP mMtx = mModel1->getAnmMtx(7);

    this->m0444.x = mMtx[0][3];
    this->m0444.y = mMtx[1][3];
    this->m0444.z = mMtx[2][3];

    if (this->mpGrid) {
        static cXyz top_offset(0.0f, 0.0f, -365.0f);
        static cXyz XZ_top_offset(265.0f, 0.0f, 0.0f);

        this->mpGrid->current.pos = this->m0444;
        this->mpGrid->shape_angle = this->shape_angle;

        cMtx_multVecSR(mMtx, &top_offset, &cStack_c8);
        this->mpGrid->scale.y = cStack_c8.abs() / 365.0f;

        cMtx_multVecSR(mModel1->getAnmMtx(8), &XZ_top_offset, &cStack_c8);
        this->mpGrid->m2220 = 1.0f - (cStack_c8.abs() / 265.0f);

        if (this->mTornadoActor) {
            this->mpGrid->force_calc_wind_rel_angle(0x3000);
        }
    }

    iVar23 = this->m0366 - sVar26;
    iVar6 = abs(iVar23);
    iVar23 *= this->m0366;

    if (iVar23 > 0 && (float)iVar6 > 420.00003f) {
        seStart(JA_SE_LK_SHIP_RUDDER_OUT, &this->m0438);
    }
    else if (iVar23 < 0 && (float)iVar6 > 525.0f) {
        seStart(JA_SE_LK_SHIP_RUDDER_OUT, &this->m0438);
    }

    if (!checkStateFlg(daSFLG_UNK1_e)) {
        float shipCruiseSpeed = std::fabsf(this->speedF) / 55.0f;
        if (shipCruiseSpeed > 1.0f){
            shipCruiseSpeed = 1.0f;
        }
        else if (shipCruiseSpeed < 0.0f) {
            shipCruiseSpeed = 0.0f;
        }
        mDoAud_shipCruiseSePlay(&this->current.pos, shipCruiseSpeed);
    }
    
    pMVar13 = mModel2->mpNodeMtx;
    this->eyePos.x = pMVar13[16][0][3];
    this->eyePos.y = pMVar13[16][1][3];
    this->eyePos.z = pMVar13[16][2][3];

    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    cStack_134 = link->current.pos - this->current.pos;
    float distXz = (cStack_134.x * cM_ssin(this->shape_angle.y) + cStack_134.z * cM_scos(this->shape_angle.y));
    this->attention_info.flags = 0;
    bVar20 = FALSE;
    this->attention_info.position.set(this->eyePos.x, this->eyePos.y + 30.0f, this->eyePos.z);

    if (checkStateFlg(daSFLG_UNK1000000_e)) {
        local_e0 = this->m1068 - this->eyePos;
        bVar20 = TRUE;
        offStateFlg(daSFLG_UNK1000000_e);
    }
    else if (this->m0428) {
        local_e0 = *this->m0428 - this->eyePos;
        bVar20 = TRUE;
    } 
    else if ((this->m034C == 10 || this->m034C == 11) && this->m0434 && this->mCurrentRopeSegmentIndex > 0) {
            local_e0 = *this->m0434 - this->eyePos;
            bVar20 = TRUE;
    }
    else if (this->m034C == 8 || distXz > 125.0f) {
        if (dComIfGp_checkPlayerStatus0(0,0x10000) && dComIfGs_isEventBit(0x3910) || dComIfGs_isEventBit(0x2D02) && dComIfGp_getMiniGameType() != 1 && fopAcM_searchPlayerDistanceXZ2(this) < 250000.0f) {
            local_e0 = link->eyePos - this->eyePos;
            bVar20 = TRUE;
            this->attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
        }
    }
    else {
        this->attention_info.position = this->current.pos;
        if (!dComIfGp_checkPlayerStatus0(0,0x10000) && dComIfGs_isEventBit(0x908) && !checkStateFlg(daSFLG_UNK800000_e)) {
            if (dComIfGs_isEventBit(0x1980) || !dComIfGs_isEventBit(0x902)) {
                
                this->attention_info.flags = fopAc_Attn_ACTION_SHIP_e;
            }
            else {
                if (dComIfGs_isEventBit(0xA80)) {
                    cXyz* windVec = dKyw_get_wind_vec();
                    if (abs(cM_atan2s(windVec->x, windVec->z)) < 0x1000) {
                        this->attention_info.flags = fopAc_Attn_ACTION_SHIP_e;
                    }
                }
            }
        }
    }

    if (bVar20) {
        sVar16 = cM_atan2s(-local_e0.y, local_e0.absXZ()) - this->shape_angle.x;

        if (sVar16 > 0x2000) {
            sVar16 = 0x2000;
        }
        else if (sVar16 < -0x3000) {
            sVar16 = -0x3000;
        }

        sVar5 = cM_atan2s(local_e0.x, local_e0.z)- this->shape_angle.y;

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

    if (sVar16 == 0 || cLib_distanceAngleS(sVar16, this->m03A0) > 0x100) {
        cLib_addCalcAngleS(&this->m03A0, sVar16, 10, 0x400, 4);
    }

    if (sVar5 == 0 || cLib_distanceAngleS(sVar5, this->m03A2) > 0x100) {
        cLib_addCalcAngleS(&this->m03A2, sVar5, 10, 0x400, 4);
    }

    if (!(this->m034C == 8 || !checkForceMessage())) {
        this->attention_info.flags &= ~fopAc_Attn_ACTION_SHIP_e;
        cXyz cStack_170(this->attention_info.position - link->current.pos);
        if ((!dComIfGp_event_runCheck() && dComIfGp_checkPlayerStatus0(0,0x10000)) || std::fabsf(this->current.pos.y - link->current.pos.y) < 50.0f && cStack_170.abs2XZ() < 62500.0f && fopAcM_seenPlayerAngleY(this) < 0x6000 && this->mNextMessageID != 0xD65) {
            fopAcM_orderSpeakEvent(this);
            offStateFlg(daSFLG_UNK400000_e);
            this->attention_info.flags |= (fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
            this->eventInfo.onCondition(dEvtCnd_CANTALK_e);
        }
    }
    if ((!dComIfGs_isEventBit(0x2D10) || daPy_getPlayerLinkActorClass()->checkMasterSwordEquip()) && (!dComIfGs_isEventBit(0x3804) || dComIfGs_isEventBit(0x2D02)) && (!dComIfGs_isEventBit(0x3E10) || dComIfGs_isEventBit(0x3F80))) {
        goto LAB_8055227c;
    }
    this->attention_info.flags &= ~fopAc_Attn_ACTION_SHIP_e;
    LAB_8055227c:
    if (this->m034C != 8 && dComIfGp_checkPlayerStatus0(0, 0x10000)) {
        bVar20 = TRUE;
        if (dComIfGs_isEventBit(0x1E40) && !dComIfGs_isEventBit(0x3840)) {
            this->mNextMessageID = 0x168c;
        }
        else if (dComIfGs_isEventBit(0x2D02) && !dComIfGs_isEventBit(0x3201)) {
            this->mNextMessageID = 0x1645;
        }
        else if (dComIfGs_isEventBit(0x1820) && !dComIfGs_isEventBit(0x3380)) {
            this->mNextMessageID = 0x164d;
        }
        else if(dComIfGs_getTriforceNum() == 8 && !dComIfGs_isEventBit(0x3D04)) {
            this->mNextMessageID = 0x1682;
        }
        else if (dComIfGs_isEventBit(0x3E40) && !dComIfGs_isEventBit(0x3E20)) {
            this->mNextMessageID = 0x1683;
        }
        else {
            bVar20 = FALSE;
        }
        if (bVar20) {
            fopAcM_orderSpeakEvent(this);
            this->eventInfo.onCondition(dEvtCnd_CANTALK_e);
            this->attention_info.flags |= (fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e);
            offStateFlg(daSFLG_UNK400000_e);
        }
    }

    this->m03DC = this->m0366 * 0.00012207031f;

    fVar3 = (this->speedF * 0.1f) / 55.0f;

    if (fVar3 > 0.05f) { 
        fVar3 = 0.05f;
    }
    else if (fVar3 < -0.05f) {
        fVar3 = -0.05;
    }

    this->m03D4 += fVar3;
    
    if (this->m03D4 > 1.0f) {
        this->m03D4 -= 1.0f;
    }
    else if (this->m03D4 < 0.0f) {
        this->m03D4 += 1.0f;
    }

    cXyz cStack_17c(this->current.pos - this->old.pos);

    if (this->speedF >= 0.0f) {
        this->mFwdVel = cStack_17c.absXZ();
    }
    else {
        this->mFwdVel = -cStack_17c.absXZ();
    }

    this->mFwdVel += (this->m1044.x * cM_ssin(this->current.angle.y) + this->m1044.z * cM_scos(this->current.angle.y));
    
    if (std::fabsf(this->mFwdVel) <= 0.01f || fVar2 * this->mFwdVel < 0.0f || this->mFwdVel * this->speedF < 0.0f) {
        this->mWaveL.mState = 1;
        this->mWaveR.mState = 1;
        this->mSplash.mState = 1;
        this->mTrack.mState = 1;
    }

    setEffectData(this->m03F4, local_190);

    float sin = cM_ssin(this->shape_angle.y);
    float cos = cM_scos(this->shape_angle.y);
    
    dCcD_Cyl* cyl = this->mCyl;
    
    float* cyl_offset_ptr = &cyl_offset.x;

    for(int i = 0; i < 3; i++, cyl_offset_ptr++, cyl++) {
        local_104.x = this->current.pos.x + sin * *cyl_offset_ptr;
        local_104.y = this->current.pos.y - 30.0f;
        local_104.z = this->current.pos.z + cos * *cyl_offset_ptr;
        cyl->SetC(local_104);
        dComIfG_Ccsp()->Set(cyl);
        if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
            cyl->SetTgGrp(4);
        }
        else {
            cyl->SetTgGrp(0xC);
        }
    }

    cMtx_multVec(this->m029C->getModel()->getAnmMtx(8), &sph_offset, &local_104);

    if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
        this->mSph.SetTgGrp(4);
    }
    else {
        this->mSph.SetTgGrp(0xC);
    }

    this->mSph.SetC(local_104);

    if (this->m034C != 9) {
        dComIfG_Ccsp()->Set(&this->mSph);
    }
    else {
        this->mSph.ResetTgHit();
    }

    if (this->mShipMode == Sailing) {
        dComIfGp_setPlayerStatus1(0, 0x400);
        mDoAud_setShipSailState(1);
        
    }
    else {
        dComIfGp_clearPlayerStatus1(0, 0x400);
        mDoAud_setShipSailState(0);
    }

    this->m034D = this->m034C;

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
    this->mWaveL.remove();
    this->mWaveR.remove();
    this->mSplash.remove();
    this->mTrack.remove();
    this->mRipple.remove();
    this->m1984.end();
    this->m1998.end();
    this->m19AC.end();
    this->m19C0.end();
    mDoAud_seDeleteObject(&this->m0438);
    mDoAud_seDeleteObject(&this->m0444);
    mDoAud_seDeleteObject(&this->m102C);
    mDoAud_seDeleteObject(&this->m1020);
    mDoAud_seDeleteObject(&this->m1038);
    dComIfGp_clearPlayerStatus1(0, 0x400);
    dComIfG_resDelete(&this->mPhs, l_arcName);
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
    J3DModel* pModel;
    mDoExt_McaMorf* morf;
    
    if (checkStateFlg(daSFLG_UNK200_e)) {
        this->m0392 = 11;
    }
    else {
        this->m0392 = 10;
    }
    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, 0x11);
    JUT_ASSERT(0x1B5C, modelData != 0);
    

    morf = new mDoExt_McaMorf(modelData, NULL, NULL, 
                             (J3DAnmTransformKey *)dComIfG_getObjectRes(l_arcName, m0392), 
                             J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 0, NULL, 0x80000, 0x11200202);
    

    this->m0298 = morf;
    if (this->m0298 && (pModel = this->m0298->getModel(), pModel)) {
        J3DSkinDeform* mSkinDeform = new J3DSkinDeform();
        if (mSkinDeform == NULL) {
            return FALSE;
        }

        if (pModel->setSkinDeform(mSkinDeform, 1)) {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, 0x13);
    JUT_ASSERT(0x1B81, modelData != 0);
    this->mpCannonModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
    
    if (this->mpCannonModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, 0x14);
    JUT_ASSERT(0x1B8E, modelData != 0);
    this->mpSalvageArmModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);

    if (this->mpSalvageArmModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes("Link", 0x2E);
    JUT_ASSERT(0x1B9B, modelData != 0);
    this->mpLinkModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);

    if (this->mpLinkModel == NULL) {
        return FALSE;
    }

    modelData = (J3DModelData *)dComIfG_getObjectRes(l_arcName, 0x12);
    JUT_ASSERT(0x1BA8, modelData != 0);

    this->m03B4 = 7;
    
    morf = new mDoExt_McaMorf(modelData, NULL, NULL, 
                             (J3DAnmTransformKey *)dComIfG_getObjectRes(l_arcName, 7), 
                             J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, 0, NULL, 0x80000, 0x11000002);

    this->m029C = morf;
    if (this->m029C == NULL || this->m029C->getModel() == NULL) {
        return FALSE;
    }
    this->m029C->setMorf(3.0f);
    return this->mRopeLine.init(1, 0xFA, (ResTIMG*)dComIfG_getObjectRes("Always", 0x7E), 0) ? 1 : 0;
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
            /* SrcObjTg  Type    */ 0xFF3DFEFF,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsPlayer_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e| cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0x23,
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
            /* SrcObjTg  Type    */ 0xFF3DFEFF,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsPlayer_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e| cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0x23,
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
    
    if (dComIfGs_isEventBit(0xF80) == 0) {
        return cPhs_ERROR_e;
    }
    
    res = dComIfG_resLoad(&this->mPhs, l_arcName);

    if (((fopAcM_GetParam(this) >> 8) & 0xFF) == 1) {
        this->m03E8 = 1.0f;
        onStateFlg(daSFLG_UNK200_e);
    }
    else {
        this->m03E8 = 0.001f;
        offStateFlg(daSFLG_UNK200_e);
    }

    if (res == cPhs_COMPLEATE_e) {
        if ((fopAcM_entrySolidHeap(this, daShip_createHeap, 0x20000) & 0xff) == 0) {
          return cPhs_ERROR_e;
        }
        
        this->m0298->setFrame(this->m0298->getEndFrame());
        
        pModel = this->m0298->getModel();
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
                    this->m02A0 = pTexMtx;
                    this->m02A4 = pTexMtx;
                }
            }
        }

        C_MTXOrtho(this->m02A8, 50.0f, -50.0f, -50.0f, 50.0f, 0.1f, 100000.0f);
        
        pModel = this->m029C->getModel();
        pModelData = pModel->getModelData();
        
        pModel->setUserArea(reinterpret_cast<u32>(this));
        
        for (u16 jno = 0; jno < pModelData->getJointNum(); jno++) {
            if ((jno == 8) || (jno == 10)) {
                pModelData->getJointTree().getJointNodePointer(jno)->setCallBack(daShip_headJointCallBack0);
            }
            else if (!((jno != 2) && (jno != 3) && (jno != 4) && (jno != 5) && (jno != 6)) || (jno == 7)) {
                pModelData->getJointTree().getJointNodePointer(jno)->setCallBack(daShip_headJointCallBack1);
            }
        }
        
        this->mpCannonModel->setUserArea(reinterpret_cast<u32>(this));
        
        pModelData = this->mpCannonModel->getModelData();
        
        pModelData->getJointTree().getJointNodePointer(1)->setCallBack(daShip_cannonJointCallBack);
        pModelData->getJointTree().getJointNodePointer(2)->setCallBack(daShip_cannonJointCallBack);
        
        this->mpSalvageArmModel->setUserArea(reinterpret_cast<u32>(this));
        this->mpSalvageArmModel->getModelData()->getJointTree().getJointNodePointer(1)->setCallBack(daShip_craneJointCallBack);
        
        this->m034B = fopAcM_GetParam(this);
        this->mShipMode = Idle;
        this->mTornadoID = -1;
        this->mTornadoActor = NULL;
        this->mWhirlID = -1;
        this->mWhirlActor = NULL;
        
        if (this->m034D != 13) {
            this->mTactWarpID = -1;
        }
        
        if (checkStateFlg(daSFLG_UNK200_e) != 0) {
            this->mShipMode = Sailing; // Sailing
            procSteerMove_init();
        }
        else {
            if (this->m034D == 2) {
                procPaddleMove_init();
            }
            else if (this->m034D == 13) {
                procStartModeWarp_init();
            }
            else if (this->m034D == 16) {
                procStartModeThrow_init();
            }
            else {
                procWait_init();
            }
        }

        if ((dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == 7) || !strcmp(dComIfGp_getStartStageName(), "Hyrule") || !strcmp(dComIfGp_getStartStageName(), "Ocean")) {
            this->m03CC = 4;
        }
        else {
            this->m03CC = 3;
        }
        
        this->mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, this->m03CC, &this->mAcchCir[0], fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
        
        this->mAcchCir[0].SetWall(0.0f, 250.0f);
        this->mAcchCir[1].SetWall(75.0f, 250.0f);
        this->mAcchCir[2].SetWall(150.0f, 250.0f);
        this->mAcchCir[3].SetWall(-600.0f-this->current.pos.y, 250.0f);

        this->mAcch.ClrWaterNone();
        this->mAcch.SetWaterCheckOffset(10000.0f);

        this->attention_info.flags = 0;
        this->attention_info.position = this->current.pos;

        this->gravity = -2.5f;
        this->maxFallSpeed = -150.0f;
        this->mGridID = fopAcM_create(0xAC, 1, &this->current.pos, -1, &this->current.angle);

        if (this->mGridID == fpcM_ERROR_PROCESS_ID_e) {
            return cPhs_ERROR_e;
        }

        this->mTactWarpPosNum = -1;
        this->m03E0 = 10000.0f;
        this->mStts.Init(0xF0, 0, this);

        dCcD_Cyl* cyl = mCyl;
        for (int i = 0; i < 3; i++, cyl++) {
            cyl->Set(cyl_src);
            cyl->SetStts((&this->mStts));
        }

        this->mCyl[1].SetR(95.0f);
        this->mSph.Set(sph_src);
        this->mSph.SetStts(&this->mStts);

        this->cull.box.min.x = -325.0f;
        this->cull.box.min.y = -50.0f;
        this->cull.box.min.z = -325.0f;
        this->cull.box.max.x = 325.0f;
        this->cull.box.max.y = 570.0f;
        this->cull.box.max.z = 240.0f;
        
        fopKyM_create(PROC_WIND_ARROW, (int)this, 0, 0, 0);

        offStateFlg(daSFLG_UNK2_e);
        this->mAcch.CrrPos(*dComIfG_Bgsp());

        setRoomInfo();

        this->m03F4 = getWaterY();
        
        if (this->m034C == 13) {
            this->current.pos.y = this->m03F4 + 5000.0f;
        }
        else if (this->m034C == 16) {
            this->current.pos.y = this->m03F4 + 2500.0f;
        }

        mDoMtx_stack_c::transS(this->current.pos.x, this->current.pos.y, this->current.pos.z);
        mDoMtx_ZXYrotM(mDoMtx_stack_c::get(), this->shape_angle.x, this->shape_angle.y, this->shape_angle.z);
        
        this->m0298->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        this->m0298->play(NULL, 0, 0);
        this->m0298->calc();
        
        PSMTXMultVec(this->m0298->getModel()->getAnmMtx(10), &l_tiller_top_offset, &this->m0438);
        
        this->m029C->play(NULL, 0, 0);
        this->m029C->getModel()->setBaseTRMtx(this->m0298->getModel()->getAnmMtx(4));
        this->m029C->calc();
        
        g_dComIfG_gameInfo.play.mpPlayerPtr[2] = this;
        
        this->mTrack.mMinVel = 3.0f;
        this->mWaveL.mMaxParticleVelocity = 40.0f;
        this->mWaveR.mMaxParticleVelocity = 40.0f;
        this->m19C0.mRate = 0.0f;

        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == 7) {
            fopAcM_createChild(0x110, fopAcM_GetID(this), 0, &this->current.pos, -1, NULL);
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
    /* Priority     */ 0x009C,
    /* Actor SubMtd */ &l_daShip_Method,
    /* Status       */ 0x02 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
