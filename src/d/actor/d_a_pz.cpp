/**
 * d_a_pz.cpp
 * NPC - Princess Zelda
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_pz.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_material.h"
#include "d/d_particle_name.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_item.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "m_Do/m_Do_mtx.h"

const u32 daPz_c::m_heapsize = 0xA740;
const char daPz_c::m_arc_name[] = "PZ";
const f32 daPz_c::m_smoke_ef = 1.25f;
const f32 daPz_c::m_grass_ef = 1.5f;
const f32 daPz_c::m_splash_ef = 1.0f;
static daPz_HIO_c l_HIO;

const dCcD_SrcCyl daPz_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    }},
};


/* 000000EC-00000310       .text __ct__10daPz_HIO_cFv */
daPz_HIO_c::daPz_HIO_c() {
    m02C = 0;
    m02D = 1;
    m032 = 0;
    m033 = 0;
    for (int i = 0; i < 10; i++) {
        m034[i] = 0;
    }

    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0x1FFE;
    mNpc.mMaxHeadY = 0x2710;
    mNpc.mMaxBackboneX = 0x1B58;
    mNpc.mMaxBackboneY = 0x32C8;
    mNpc.mMinHeadX = -0x9C4;
    mNpc.mMinHeadY = -0x2710;
    mNpc.mMinBackboneX = -0x1B58;
    mNpc.mMinBackboneY = -0x32C8;
    mNpc.mMaxTurnStep = 0x1000;
    mNpc.mMaxHeadTurnVel = 0x800;
    mNpc.mAttnYOffset = 50.0f;
    mNpc.mMaxAttnAngleY = 0x32C8;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0f;

    m040 = 60.0f;
    m02F = 0;
    m054 = 0x2000;
    m058 = 200.0f;
    m044 = 1.2f;
    m04C = 0.9f;
    m048 = 2.0f;
    m050 = 10.0f;
    m031 = 0;

    mAttackAimRange[0] = 100.0f;
    mAttackShootChance[0] = 0.0f;
    mAttackAimZeroChance[0] = 100.0f;
    mAttackWaitTimer[0] = 30;
    mFollowTimerBase[0] = 300;
    mFollowTimerRange[0] = 0;
    mAttackTimerBase[0] = 30;
    mAttackTimerRange[0] = 0;
    m0A0 = 1000.0f;
    mTalkTimer[0] = 60;
    m100 = 3000.0f;

    mAttackAimRange[2] = 100.0f;
    mAttackShootChance[2] = 100.0f;
    mAttackAimZeroChance[2] = 80.0f;
    mAttackWaitTimer[2] = 30;
    mFollowTimerBase[2] = 100;
    mFollowTimerRange[2] = 100;
    mAttackTimerBase[2] = 30;
    mAttackTimerRange[2] = 60;
    m0A8 = 1000.0f;
    mTalkTimer[2] = 600;
    m108 = 800.0f;
    m0AC = 100.0f;
    m0E2[0] = 4;
    m0E2[1] = 6;
    m0E2[2] = 4;
    m0E2[3] = 6;

    m0B0 = -2.5f;
    mBackStepSpeedY = 20.0f;
    mBackStepSpeedF = 20.0f;
    mSideStepSpeedY = 20.0f;
    mSideStepSpeedF = 20.0f;
    mDownSpeedY = 4.0f;
    mDownSpeedF = 15.0f;
    mDownTimer = 14;
    m0D8 = 30.0f;
    m0DC = 40;
    m0DE = 40;
    m0E0 = 5;
    m0D0 = 600.0f;
    m0EC = 800.0f;
    m0D4 = 15.0f;
    m0F0 = 2.0f;
    m0F4 = 1.0f;
}

/* 00000310-00000340       .text stealItem_CB__FPv */
static BOOL stealItem_CB(void* actor) {
    if (actor != NULL) {
        daItem_c* item = (daItem_c*)actor;
        item->scale.setall(1.0f);
        item->setFlag(daItem_c::FLAG_HOOK);
    }
    return TRUE;
}

/* 00000340-0000038C       .text nodeHeadControl_CB__FP7J3DNodei */
static BOOL nodeHeadControl_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeHeadControl(i_node, model);
        }
    }
    return TRUE;
}

/* 0000038C-000004FC       .text _nodeHeadControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeHeadControl(J3DNode* i_node, J3DModel* i_model) {
    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    static cXyz top_offset(0.0f, 0.0f, 0.0f);
    static cXyz front_offset(24.0f, -16.0f, 0.0f);

    PSMTXMultVec(mDoMtx_stack_c::now, &top_offset, &mHeadTopPos);
    mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    PSMTXMultVec(mDoMtx_stack_c::now, &front_offset, &mHeadFrontPos);
    mHeadCenterPos.x = mDoMtx_stack_c::now[0][3];
    mHeadCenterPos.y = mDoMtx_stack_c::now[1][3];
    mHeadCenterPos.z = mDoMtx_stack_c::now[2][3];
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 00000538-00000584       .text nodeWaistControl_CB__FP7J3DNodei */
static BOOL nodeWaistControl_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeWaistControl(i_node, model);
        }
    }
    return TRUE;
}

/* 00000584-00000710       .text _nodeWaistControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeWaistControl(J3DNode* i_node, J3DModel* i_model) {
    static s16 tmp_angle;

    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    tmp_angle += 0x1000;
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    if ((s8)m06D3 == 4 || (s8)m06D3 == 5 || (s8)m06D3 == 6) {
        mDoMtx_stack_c::ZrotM(0xDAC);
        mDoMtx_stack_c::YrotM(0x5DC);
    }

    if (REG12_S(6) != 0) {
        mDoMtx_stack_c::XrotM(tmp_angle);
    } else {
        MtxP mtx = mDoMtx_stack_c::now;
        mDoMtx_XrotM(mtx, m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }

    if ((s8)m06D3 == 4 || (s8)m06D3 == 5 || (s8)m06D3 == 6) {
        mDoMtx_stack_c::YrotM(-0x5DC);
        mDoMtx_stack_c::ZrotM(-0xDAC);
    }

    PSMTXCopy(mDoMtx_stack_c::now, mWaistMtx);
    mWaistPos.x = mDoMtx_stack_c::now[0][3];
    mWaistPos.y = mDoMtx_stack_c::now[1][3];
    mWaistPos.z = mDoMtx_stack_c::now[2][3];
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 00000710-0000075C       .text nodeWaist2Control_CB__FP7J3DNodei */
static BOOL nodeWaist2Control_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeWaist2Control(i_node, model);
        }
    }
    return TRUE;
}

/* 0000075C-000007F4       .text _nodeWaist2Control__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeWaist2Control(J3DNode* i_node, J3DModel* i_model) {
    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::YrotM(mWaist2RotY);
    mDoMtx_stack_c::ZrotM(mWaist2RotZ);
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 000007F4-00000840       .text nodeSkirtControl_CB__FP7J3DNodei */
static BOOL nodeSkirtControl_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeSkirtControl(i_node, model);
        }
    }
    return TRUE;
}

/* 00000840-00000920       .text _nodeSkirtControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeSkirtControl(J3DNode* i_node, J3DModel* i_model) {
    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    s16 rot_z = mWaist2RotZ;
    if (rot_z > mWaist2RotY) {
        rot_z = mWaist2RotY;
    }

    mDoMtx_stack_c::XrotM(REG12_S(2));
    mDoMtx_stack_c::YrotM(REG12_S(3));
    mDoMtx_stack_c::ZrotM(-(rot_z + REG12_S(4)));
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 00000920-00000940       .text createHeap_CB__FP10fopAc_ac_c */
static bool createHeap_CB(fopAc_ac_c* i_this) {
    return ((daPz_c*)i_this)->_createHeap();
}

/* 00000940-00000D54       .text bodyCreateHeap__6daPz_cFv */
int daPz_c::bodyCreateHeap() {
    /* Nonmatching */
}

/* 00000D54-00000E74       .text bowCreateHeap__6daPz_cFv */
int daPz_c::bowCreateHeap() {
    /* Nonmatching */
}

/* 00000E74-00000EC0       .text _createHeap__6daPz_cFv */
bool daPz_c::_createHeap() {
    if (bodyCreateHeap() == 0) {
        return false;
    }
    return bowCreateHeap() != 0;
}

/* 00000EC0-00000F20       .text __ct__13daPz_matAnm_cFv */
daPz_matAnm_c::daPz_matAnm_c() {
    mMoveFlag = false;
    mNowOffsetX = 0.0f;
    mNowOffsetY = 0.0f;
}

/* 00000F20-00000FB4       .text calc__13daPz_matAnm_cCFP11J3DMaterial */
void daPz_matAnm_c::calc(J3DMaterial* i_material) const {
    J3DMaterialAnm::calc(i_material);

    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i) != NULL) {
            J3DTexMtx* tex_mtx = i_material->getTexMtx(i);
            if (mMoveFlag) {
                tex_mtx->getTexMtxInfo().mSRT.mTranslationX = mNowOffsetX;
                tex_mtx->getTexMtxInfo().mSRT.mTranslationY = mNowOffsetY;
            }
        }
    }
}

/* 00000FB4-00001038       .text getGndPos__6daPz_cFv */
void daPz_c::getGndPos() {
    mbHasGanondorf = false;

    fopAc_ac_c* ganondorf;
    if (fopAcM_SearchByName(PROC_GND, &ganondorf)) {
        mGanondorfPos4 = ganondorf->eyePos;
        mGanondorfPosCurrent = ganondorf->current.pos;
        mbHasGanondorf = true;
    }
}

/* 00001038-0000114C       .text checkEyeArea__6daPz_cFR4cXyz */
BOOL daPz_c::checkEyeArea(cXyz& i_pos) {
    s32 angle = cLib_distanceAngleS(shape_angle.y, cLib_targetAngleY(&current.pos, &i_pos));
    f32 dist = (current.pos - i_pos).absXZ();

    if (angle < l_HIO.m054 && dist < l_HIO.m058) {
        return TRUE;
    }
    return FALSE;
}

/* 0000114C-00001194       .text getMsg__6daPz_cFv */
u32 daPz_c::getMsg() {
    u32 msg_no = 0x3562;
    if (m08B0 == 0) {
        msg_no = 0x3562;
    } else if (m08B0 == 2) {
        if (!m0F65) {
            m0F65 = true;
            msg_no = 0x3563;
        } else {
            msg_no = 0x3565;
        }
    }
    return msg_no;
}

/* 00001194-00001208       .text next_msgStatus__6daPz_cFPUl */
u16 daPz_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001208-00001288       .text anmAtr__6daPz_cFUs */
void daPz_c::anmAtr(u16 i_msgStatus) {
    static const s8 anm_atr[] = {
        12, 13,
    };

    switch (i_msgStatus) {
    case 6:
        if (m06CC == 0) {
            u8 msg_attr = dComIfGp_getMesgAnimeAttrInfo();
            m06CC = 1;
            setAnm(anm_atr[msg_attr], false, 0xF);
        }
        break;
    case 0xE:
        m06CC = 0;
        break;
    }
}

/* 00001288-000012D4       .text eventOrder__6daPz_cFv */
void daPz_c::eventOrder() {
    if (m0F82 == 1 || m0F82 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m0F82 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000012D4-00001338       .text checkOrder__6daPz_cFv */
void daPz_c::checkOrder() {
    if (eventInfo.getCommand() == dEvtCmd_INDEMO_e) {
        m0F82 = 0;
    } else if (eventInfo.getCommand() == dEvtCmd_INTALK_e && (m0F82 == 1 || m0F82 == 2)) {
        m0F82 = 0;
        modeProc((Proc_e)0, 9);
    }
}

/* 00001338-0000151C       .text setFallSplash__6daPz_cFv */
void daPz_c::setFallSplash() {
    /* Nonmatching */
}

/* 0000151C-000015F4       .text setHeadSplash__6daPz_cFv */
void daPz_c::setHeadSplash() {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &mTevstr);
    if (mHeadSplash.getEmitter() == NULL) {
        dComIfGp_particle_set(
            dPa_name::ID_AK_SN_PZSHAKEHEADSPLASH00, &mHeadCenterPos, NULL, NULL, 0xFF, &mHeadSplash
        );
    }

    JPABaseEmitter* emitter = mHeadSplash.getEmitter();
    if (emitter != NULL) {
        emitter->setGlobalPrmColor(mTevstr.mColorC0.r, mTevstr.mColorC0.g, mTevstr.mColorC0.b);
        MtxP mtx = mpMorf->getModel()->getAnmMtx(4);
        mHeadSplash.getEmitter()->setGlobalRTMatrix(mtx);
    }
}

/* 000015F4-00001704       .text setRipple__6daPz_cFv */
void daPz_c::setRipple() {
    /* Nonmatching */
}

/* 00001704-0000175C       .text setJntStatus__6daPz_cFv */
void daPz_c::setJntStatus() {
    m_jnt.setParam(
        l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY,
        l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
        l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep
    );
}

/* 0000175C-00001954       .text demo__6daPz_cFv */
void daPz_c::demo() {
    /* Nonmatching */
}

/* 00001954-00001EEC       .text checkTgHit__6daPz_cFv */
void daPz_c::checkTgHit() {
    /* Nonmatching */
}

/* 00001EEC-00001F10       .text getArg__6daPz_cFv */
void daPz_c::getArg() {
    mArg = (fopAcM_GetParam(this) >> 8) & 0xFF;
    if (mArg == 0xFF) {
        mArg = 0;
    }
}

/* 00001F10-000020B8       .text setAttention__6daPz_cFv */
void daPz_c::setAttention() {
    /* Nonmatching */
}

/* 000020B8-00002114       .text setBowAnm__6daPz_cFScb */
void daPz_c::setBowAnm(signed char, bool) {
    /* Nonmatching */
}

/* 00002114-00002184       .text setBowString__6daPz_cFb */
void daPz_c::setBowString(bool i_show) {
    J3DMaterial* mat = mpBowMcaMorf->getModel()->getModelData()->getJointNodePointer(0)->getMesh()->getNext();
    J3DMaterial* string_mat = mat->getNext();
    if (i_show) {
        mat->getShape()->show();
        string_mat->getShape()->hide();
    } else {
        mat->getShape()->hide();
        string_mat->getShape()->show();
    }
}

/* 00002184-0000246C       .text setAnm__6daPz_cFScbi */
void daPz_c::setAnm(signed char, bool, int) {
    /* Nonmatching */
}

/* 0000246C-00002684       .text setAnmRunSpeed__6daPz_cFv */
void daPz_c::setAnmRunSpeed() {
    /* Nonmatching */
}

/* 00002684-0000274C       .text setEyeBtp__6daPz_cFi */
void daPz_c::setEyeBtp(int) {
    /* Nonmatching */
}

/* 0000274C-00002810       .text setEyeBtk__6daPz_cFi */
void daPz_c::setEyeBtk(int) {
    /* Nonmatching */
}

/* 00002810-00002888       .text setEyeAnm__6daPz_cFSc */
void daPz_c::setEyeAnm(signed char i_eye) {
    static const int a_eye_tbl[][2] = {
        {0x27, 0x1F},
        {0x23, 0x1E},
        {0x24, -1},
        {0x25, -1},
        {0x29, 0x20},
        {0x26, -1},
        {0x2C, -1},
        {0x28, 0x1F},
        {0x2A, -1},
        {0x2B, -1},
    };

    int btp = a_eye_tbl[i_eye][0];
    if (btp != -1) {
        setEyeBtp(btp);
    }
    int btk = a_eye_tbl[i_eye][1];
    if (btk != -1) {
        setEyeBtk(btk);
    }
    mCurEye = i_eye;
}

/* 00002888-00002AE0       .text ctrlEye__6daPz_cFv */
void daPz_c::ctrlEye() {
    /* Nonmatching */
}

/* 00002AE0-00002D38       .text playEyeAnm__6daPz_cFv */
void daPz_c::playEyeAnm() {
    /* Nonmatching */
}

/* 00002D38-00002DC8       .text setMtx__6daPz_cFv */
void daPz_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00002DC8-00002E2C       .text modeWaitInit__6daPz_cFv */
void daPz_c::modeWaitInit() {
    m0924 = 0.0f;
    setAnm(1, false, 0xF);
    m_jnt.mbTrn = false;
    m08EA = true;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    m08EC = 30;
}

/* 00002E2C-00002FE8       .text modeWait__6daPz_cFv */
void daPz_c::modeWait() {
    /* Nonmatching */
}

/* 00002FE8-000031E8       .text modeMoveInit__6daPz_cFv */
void daPz_c::modeMoveInit() {
    /* Nonmatching */
}

/* 000031E8-0000395C       .text modeMove__6daPz_cFv */
void daPz_c::modeMove() {
    /* Nonmatching */
}

/* 0000395C-000039C0       .text modeAttackWaitInit__6daPz_cFv */
void daPz_c::modeAttackWaitInit() {
    m0924 = 0.0f;
    m08EC = 20;
    m08F0 = 10;
    setAnm(2, false, 0xF);
    m08EA = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
}

/* 000039C0-00003D88       .text modeAttackWait__6daPz_cFv */
void daPz_c::modeAttackWait() {
    /* Nonmatching */
}

/* 00003D88-00003F14       .text modeAttackInit__6daPz_cFv */
void daPz_c::modeAttackInit() {
    m08F4 = 30;

    int idx = m08B0;
    if (!m0F65) {
        idx = 0;
    }

    s8 cur_anm = m06D3;
    if (cur_anm != 4 && cur_anm != 5) {
        m08EC = l_HIO.mAttackTimerBase[idx] + cM_rndF(l_HIO.mAttackTimerRange[idx]);
        m08F0 = l_HIO.mAttackWaitTimer[idx];
        setAnm(4, false, 0xF);
    }

    if (cM_rndF(100.0f) < l_HIO.mAttackShootChance[idx]) {
        m0F48 = true;
    } else {
        m0F48 = false;
        if (cM_rndF(100.0f) < l_HIO.mAttackAimZeroChance[idx]) {
            m0F44 = 0.0f;
        } else {
            m0F44 = cM_rndF(l_HIO.mAttackAimRange[idx]);
        }
    }

    m08EA = false;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = false;
}

/* 00003F14-0000445C       .text modeAttack__6daPz_cFv */
void daPz_c::modeAttack() {
    /* Nonmatching */
}

/* 0000445C-000044B4       .text modeDefendInit__6daPz_cFv */
void daPz_c::modeDefendInit() {
    setAnm(10, true, 0xF);
    m08EC = 30;
    m_jnt.mbTrn = false;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    m08EA = true;
}

/* 000044B4-00004630       .text modeDefend__6daPz_cFv */
void daPz_c::modeDefend() {
    /* Nonmatching */
}

/* 00004630-0000470C       .text modeDownInit__6daPz_cFv */
void daPz_c::modeDownInit() {
    attention_info.flags &= ~8;
    attention_info.flags &= ~2;
    setAnm(7, true, 0xF);
    fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);
    setDown();
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    m_jnt.mbTrn = false;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    speed.y = l_HIO.mDownSpeedY;
    m0F70 = l_HIO.mDownSpeedF;
    m08EC = l_HIO.mDownTimer;
}

/* 0000470C-00004C20       .text modeDown__6daPz_cFv */
void daPz_c::modeDown() {
    /* Nonmatching */
}

/* 00004C20-00004C78       .text modeAfraidInit__6daPz_cFv */
void daPz_c::modeAfraidInit() {
    setAnm(11, true, 0xF);
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
}

/* 00004C78-00004E8C       .text modeAfraid__6daPz_cFv */
void daPz_c::modeAfraid() {
    /* Nonmatching */
}

/* 00004E8C-00004F08       .text modeSideStepInit__6daPz_cFv */
void daPz_c::modeSideStepInit() {
    if (m06C8 != 2 && m06C8 != 3) {
        setAnm(11, true, 0xF);
    }
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    speed.y = l_HIO.mSideStepSpeedY;
    m0F70 = l_HIO.mSideStepSpeedF;
}

/* 00004F08-00005098       .text modeSideStep__6daPz_cFv */
void daPz_c::modeSideStep() {
    /* Nonmatching */
}

/* 00005098-00005114       .text modeBackStepInit__6daPz_cFv */
void daPz_c::modeBackStepInit() {
    if (m06C8 != 2 && m06C8 != 3) {
        setAnm(11, true, 0xF);
    }
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    speed.y = l_HIO.mBackStepSpeedY;
    m0F70 = l_HIO.mBackStepSpeedF;
}

/* 00005114-0000527C       .text modeBackStep__6daPz_cFv */
void daPz_c::modeBackStep() {
    /* Nonmatching */
}

/* 0000527C-00005304       .text modeTalkInit__6daPz_cFv */
void daPz_c::modeTalkInit() {
    setAnm(2, true, 0xF);
    speedF = 0.0f;
    m0924 = 0.0f;
    m08EA = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
    if (m08B0 == 0) {
        m0F80 = true;
    } else {
        m0F7C = l_HIO.mTalkTimer[m08B0];
    }
}

/* 00005304-0000539C       .text modeTalk__6daPz_cFv */
void daPz_c::modeTalk() {
    m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    m_jnt.mbTrn = true;
    if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        dComIfGp_event_onEventFlag(dEvtFlag_UNK8_e);
        modeProc((Proc_e)0, 2);
    }
}

/* 0000539C-0000549C       .text modeFollowInit__6daPz_cFv */
void daPz_c::modeFollowInit() {
    attention_info.flags |= 8;
    attention_info.flags |= 2;
    m08EC = l_HIO.mFollowTimerBase[m08B0] + cM_rndF(l_HIO.mFollowTimerRange[m08B0]);
    m08F0 = 10;
    m08F4 = 120;
    setAnm(3, false, 0xF);
    m08EA = false;
    m_jnt.mbTrn = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
}

/* 0000549C-000059B8       .text modeFollow__6daPz_cFv */
void daPz_c::modeFollow() {
    /* Nonmatching */
}

/* 000059B8-00005C58       .text modeProc__6daPz_cFQ26daPz_c6Proc_ei */
void daPz_c::modeProc(daPz_c::Proc_e, int) {
    /* Nonmatching */
}

/* 00005C58-000060D8       .text _execute__6daPz_cFv */
bool daPz_c::_execute() {
    /* Nonmatching */
}

/* 000060D8-00006154       .text bowDraw__6daPz_cFv */
void daPz_c::bowDraw() {
    g_env_light.setLightTevColorType(mpBowMcaMorf->getModel(), &tevStr);
    PSMTXCopy(mpMorf->getModel()->getAnmMtx(14), mDoMtx_stack_c::get());
    mpBowMcaMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpBowMcaMorf->updateDL();
}

/* 00006154-00006600       .text bodyDraw__6daPz_cFv */
void daPz_c::bodyDraw() {
    /* Nonmatching */
}

/* 00006600-000066D8       .text drawShadow__6daPz_cFv */
void daPz_c::drawShadow() {
    /* Nonmatching */
}

/* 000066D8-0000676C       .text _draw__6daPz_cFv */
bool daPz_c::_draw() {
    if (mEventIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(mpMorf, -1, &mInvisibleModel);
    } else {
        bodyDraw();
    }
    if (m0F88) {
        bowDraw();
    }
    drawShadow();
    dSnap_RegistFig(DSNAP_TYPE_UNK87, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 0000676C-00006974       .text bodyCreateInit__6daPz_cFv */
void daPz_c::bodyCreateInit() {
    /* Nonmatching */
}

/* 00006974-00006BAC       .text createInit__6daPz_cFv */
void daPz_c::createInit() {
    /* Nonmatching */
}

/* 00006BAC-00006CB0       .text _create__6daPz_cFv */
cPhs_State daPz_c::_create() {
    /* Nonmatching */
}

/* 00007DA0-00007E20       .text _delete__6daPz_cFv */
bool daPz_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    mRipple.end();

    dPa_followEcallBack* follow_cb = &mFallSplash;
    follow_cb->end();
    follow_cb = &mHeadSplash;
    follow_cb->end();

    if (heap != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00007E20-00007E40       .text daPzCreate__FPv */
static cPhs_State daPzCreate(void* i_this) {
    return ((daPz_c*)i_this)->_create();
}

/* 00007E40-00007E64       .text daPzDelete__FPv */
static BOOL daPzDelete(void* i_this) {
    return ((daPz_c*)i_this)->_delete();
}

/* 00007E64-00007E88       .text daPzExecute__FPv */
static BOOL daPzExecute(void* i_this) {
    return ((daPz_c*)i_this)->_execute();
}

/* 00007E88-00007EAC       .text daPzDraw__FPv */
static BOOL daPzDraw(void* i_this) {
    return ((daPz_c*)i_this)->_draw();
}

/* 00007EAC-00007EB4       .text daPzIsDelete__FPv */
static BOOL daPzIsDelete(void*) {
    return TRUE;
}

static actor_method_class daPzMethodTable = {
    (process_method_func)daPzCreate,
    (process_method_func)daPzDelete,
    (process_method_func)daPzExecute,
    (process_method_func)daPzIsDelete,
    (process_method_func)daPzDraw,
};

actor_process_profile_definition g_profile_PZ = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_PZ,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daPz_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_PZ,
    /* Actor SubMtd */ &daPzMethodTable,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
