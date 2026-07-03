/**
 * d_a_npc_pm1.cpp
 * NPC - Maggie (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_pm1.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/Pm.h"

// struct anm_prm_c {
//     /* 0x0 */ s8 mAnmIdx;
//     /* 0x1 */ u8 field_0x1[2];
//     /* 0x3 */ s8 mTexAnmIdx;
//     /* 0x4 */ f32 mMorf;
//     /* 0x8 */ f32 mPlaySpeed;
//     /* 0xC */ int mLoopMode;
// };  // Size: 0x10

static daNpc_Pm1_HIO_c l_HIO;

/* 000000EC-00000144       .text __ct__15daNpc_Pm1_HIO_cFv */
daNpc_Pm1_HIO_c::daNpc_Pm1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* field_0                */ 0x1FFE,
        /* field_2                */ 0x38E0,
        /* field_4                */ 0xE002,
        /* field_6                */ 0xC720,
        /* field_8                */ 0x0000,
        /* field_A                */ 0x0000,
        /* field_C                */ 0x0000,
        /* field_E                */ 0x0000,
        /* field_10               */ 0x0800,
        /* field_12               */ 0x0800,
        /* mAttentionArrowYOffset */ 150.0f,
        /* field_18               */ 0.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    this->mNo = -1;
    this->field_0x8 = -1;
}

/* 00000144-00000300       .text nodeCallBack_Pm__FP7J3DNodei */
static BOOL nodeCallBack_Pm(J3DNode* i_node, int i_calc_timing) {
    /* Nonmatching */
    if (i_calc_timing == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Pm1_c* actor = (daNpc_Pm1_c*)model->getUserArea();
        if (actor) {
            static cXyz a_att_pos_offst(0.0f, 0.0f, 0.0f);
            static cXyz a_eye_pos_offst(20.0f, -25.0f, 0.0f);
            u16 jointIdx = ((J3DJoint*)i_node)->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointIdx));
            if (jointIdx == actor->getHeadJntNum()) {
                MTXMultVec(mDoMtx_stack_c::get(), &a_att_pos_offst, actor->getAttPos());
                mDoMtx_stack_c::YrotM(-actor->getHead_y());
                mDoMtx_stack_c::ZrotM(-actor->getHead_x());
                MTXMultVec(mDoMtx_stack_c::get(), &a_eye_pos_offst, actor->getEyePos());
            } else if (jointIdx == actor->getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM(actor->getBackbone_y());
                mDoMtx_stack_c::ZrotM(actor->getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 0000033C-0000044C       .text createInit__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::createInit() {
    /* Nonmatching */
    this->mEventCut.setActorInfo2("Pm1", this);
    // this->attention_info.flags = Action_Talk|LockOn_Talk;
    this->attention_info.flags = 0x280 | 0x26d; //CREATE ENUM
    this->attention_info.distances[1] = 0xab;
    this->attention_info.distances[3] = 0xa9;
    this->gravity = -4.0f;
    (this->field_0x798).x = this->current.pos.x;
    (this->field_0x798).y = this->current.pos.y;
    (this->field_0x798).z = this->current.pos.z;
    this->set_action(&daNpc_Pm1_c::wait_action1, NULL);
    this->shape_angle.x = this->current.angle.x;
    this->shape_angle.y = this->current.angle.y;
    this->shape_angle.z = this->current.angle.z;
    this->mStts.Init(0xff, 0xff, (fopAc_ac_c*)this);
    this->mCyl.SetStts(&this->mStts);
    this->mCyl.Set(dNpc_cyl_src);
    this->mpMorf->setMorf(0.0);
    this->field_0x7BC = 1;
    this->setMtx();
    return 1;
}

/* 0000044C-0000055C       .text setMtx__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setMtx() {
    /* Nonmatching */
    BOOL sVar1;
    char cVar2;
    int bVar3;

    if (this->field_0x7C7 == 0) {
        this->playTexPatternAnm();
        sVar1 = this->mpMorf->play(&this->eyePos, 0, 0);
        this->field_0x7B4 = sVar1;
        if (this->mpMorf->getFrame() < this->field_0x7A4) {
            this->field_0x7B4 = 1;
        }
        this->field_0x7A4 = this->mpMorf->getFrame();
        this->mObjAcch.CrrPos(g_dComIfG_gameInfo.play.mBgS);
    }
    cVar2 = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    this->tevStr.mRoomNo = cVar2;
    bVar3 = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    this->tevStr.mEnvrIdxOverride = bVar3;

    mDoMtx_stack_c::transS(this->current.pos.x, this->current.pos.y, this->current.pos.z);
    mDoMtx_stack_c::YrotM(this->current.angle.y);
    this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    this->mpMorf->calc();
    this->setAttention();
}

/* 0000055C-00000664       .text anmResID__11daNpc_Pm1_cFiPiPi */
BOOL daNpc_Pm1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    /* Nonmatching */
    bool bVar1;
    u32 uVar2;
    static const int a_anm_idx_tbl[2][2] = {
        {dRes_ID_PM_BCK_WAIT01_e, dRes_ID_PM_BAS_WAIT01_e},
        {dRes_ID_PM_BCK_TALK01_e, dRes_ID_PM_BAS_TALK01_e},
    };
    bVar1 = false;
    if ((i_num > 0) && (i_num < 2)) {
        bVar1 = true;
    }
    if (!bVar1) {
        uVar2 = JUTAssertion::getSDevice();
        JUTAssertion::showAssert(uVar2, "d_a_npc_pm1.cpp", 0x11b, "0 <= i_num && i_num < ANM_END");
        OSPanic("d_a_npc_pm1.cpp", 0x11b, "Halt");
    }
    bVar1 = false;
    if ((o_bck_num != (int*)0x0) && (o_bas_num != (int*)0x0)) {
        bVar1 = true;
    }
    if (!bVar1) {
        uVar2 = JUTAssertion::getSDevice();
        JUTAssertion::showAssert(uVar2, "d_a_npc_pm1.cpp", 0x11c, "o_bck_num && o_bas_num");
        OSPanic("d_a_npc_pm1.cpp", 0x11c, "Halt");
    }
    *o_bck_num = a_anm_idx_tbl[i_num][0];
    *o_bas_num = a_anm_idx_tbl[i_num][1];
    return true;
}

/* 00000664-00000700       .text BtpNum2ResID__11daNpc_Pm1_cFiPi */
void daNpc_Pm1_c::BtpNum2ResID(int i_num, int* param_2) {
    /* Nonmatching */
    bool bVar1;
    u32 uVar2;
    static const int a_btp_arc_ix_tbl[1] = {dRes_ID_PM_BTP_MABA01_e};

    bVar1 = false;
    if ((i_num > 0) && (i_num < 1)) {
        bVar1 = true;
    }
    if (!bVar1) {
        uVar2 = JUTAssertion::getSDevice();
        JUTAssertion::showAssert(uVar2, "d_a_npc_pm1.cpp", 0x131, "0 <= i_num && i_num < TEXPATTERN_END");
        OSPanic("d_a_npc_pm1.cpp", 0x131, "Halt");
    }
    *param_2 = a_btp_arc_ix_tbl[i_num];
}

/* 00000700-00000744       .text setAnm_tex__11daNpc_Pm1_cFSc */
void daNpc_Pm1_c::setAnm_tex(signed char param_1) {
    /* Nonmatching */
    if ((param_1 >= 0) && (param_1 != this->field_0x7CD)) {
        this->field_0x7CD = param_1;
        this->initTexPatternAnm(true);
    }
}

/* 00000744-00000860       .text init_btp__11daNpc_Pm1_cFbi */
u8 daNpc_Pm1_c::init_btp(bool i_modify, int i_num) {
    /* Nonmatching */
    J3DAnmTexPattern* anm_tex_pattern;
    u32 assertion_device;
    int is_btp_anm;
    J3DModelData* mdl_data;
    int btpId;

    mdl_data = this->mpMorf->getModel()->getModelData();
    if (i_num >= 0) {
        this->BtpNum2ResID(i_num, &btpId);
        anm_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Pm", btpId);
        this->m_head_tex_pattern = anm_tex_pattern;
        if (this->m_head_tex_pattern == (J3DAnmTexPattern*)0x0) {
            assertion_device = JUTAssertion::getSDevice();
            JUTAssertion::showAssert(assertion_device, "d_a_npc_pm1.cpp", 0x152, "m_head_tex_pattern != 0");
            OSPanic("d_a_npc_pm1.cpp", 0x152, "Halt");
        }
        is_btp_anm = this->mBtpAnm.init(mdl_data, this->m_head_tex_pattern, 1, 2, 1.0, 0, -1, i_modify, 0);
        if (is_btp_anm == 0) {
            return 0;
        }
        this->mBtpFrame = 0;
        this->mTimer = 0;
    }
    return 1;
}

/* 00000860-000008A4       .text initTexPatternAnm__11daNpc_Pm1_cFb */
BOOL daNpc_Pm1_c::initTexPatternAnm(bool i_modify) {
    /* Nonmatching */
    BOOL ret = FALSE;
    if (this->init_btp(i_modify, (int)this->field_0x7CD) != 0) {
        ret = TRUE;
    }
    return ret;
}

/* 000008A4-00000968       .text playTexPatternAnm__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::playTexPatternAnm() {
    /* Nonmatching */
    bool timer_ended = true;

    if (this->field_0x7CD == 0) {
        timer_ended = (cLib_calcTimer(&this->mTimer) == 0) ? true : false;
    }

    if (timer_ended) {
        s16 anm_duration = this->m_head_tex_pattern->getFrameMax();

        if (!(++this->mBtpFrame < anm_duration)) {
            if (this->field_0x7CD != 0) {
                this->mBtpFrame = this->m_head_tex_pattern->getFrameMax();
            } else {
                this->mBtpFrame = 0;
                this->mTimer = cM_rndF(60.0f) + 30.0f;
            }
        }
    }
}

/* 00000968-00000A34       .text setAnm_anm__11daNpc_Pm1_cFPQ211daNpc_Pm1_c9anm_prm_c */
BOOL daNpc_Pm1_c::setAnm_anm(daNpc_Pm1_c::anm_prm_c* param_1) {
    /* Nonmatching */
    BOOL ret = 0;

    if ((param_1->mBckResIndex >= 0) && (this->mBckResIndex != param_1->mBckResIndex)) {
        this->mBckResIndex = param_1->mBckResIndex;

        if (this->mpMorf != (mDoExt_McaMorf*)0x0) {
            int local_14[3];
            int local_18;
            this->anmResID((int)this->mBckResIndex, local_14, &local_18);
            if (local_14[0] >= 0) {
                dNpc_setAnmIDRes(this->mpMorf, param_1->mLoopMode, param_1->mMorf, param_1->mSpeed, local_14[0], local_18, "Pm");
            }
            ret = 1;
        }
        this->field_0x7A4 = 0.0f;
        this->field_0x7B5 = 0;
        this->field_0x7B4 = 0;
    }
    return ret;
}

/* 00000A34-00000A9C       .text setAnm__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setAnm() {
    /* Nonmatching */
    static daNpc_Pm1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0.0f, 0.0f, -1},
        {0, 0, 8.0f, 1.0f, 2},
        {-1, -1, 0.0f, 0.0f, -1},
    };
    this->setAnm_tex(a_anm_prm_tbl[field_0x7D0].mResIndex);
    this->setAnm_anm(&a_anm_prm_tbl[field_0x7D0]);
}

/* 00000A9C-00000AA8       .text chngAnmTag__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::chngAnmTag() {
    /* Nonmatching */
    if ((BOOL)this->field_0x7CC != 0)
        return;
}

/* 00000AA8-00000AB4       .text ctrlAnmTag__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::ctrlAnmTag() {
    /* Nonmatching */
    if ((BOOL)this->field_0x7CB != 0)
        return;
}

/* 00000AB4-00000AF4       .text chngAnmAtr__11daNpc_Pm1_cFUc */
void daNpc_Pm1_c::chngAnmAtr(u8 param_1) {
    /* Nonmatching */
    if (param_1 < 1) {
        if (param_1 != this->field_0x7CB) {
            this->field_0x7CB = param_1;
            this->setAnm_ATR(1);
        }
    }
}

/* 00000AF4-00000AF8       .text ctrlAnmAtr__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::ctrlAnmAtr() {
    /* Nonmatching */
}

/* 00000AF8-00000B60       .text setAnm_ATR__11daNpc_Pm1_cFi */
void daNpc_Pm1_c::setAnm_ATR(int param_1) {
    /* Nonmatching */
    static daNpc_Pm1_c::anm_prm_c a_anm_prm_tbl[1] = {0, 0, 8.0f, 1.0f, 2};
    if (param_1 != 0) {
        this->setAnm_tex(a_anm_prm_tbl[this->field_0x7CB].mResIndex);
    }
    this->setAnm_anm(&a_anm_prm_tbl[this->field_0x7CB]);
}

/* 00000B60-00000C1C       .text anmAtr__11daNpc_Pm1_cFUs */
void daNpc_Pm1_c::anmAtr(unsigned short param_1) {
    /* Nonmatching */
    u8 uVar1;

    if (param_1 == 6) {
        if (this->field_0x7D6 == 0) {
            this->field_0x7CC = 0xff;
            this->chngAnmAtr(g_dComIfG_gameInfo.play.mMesgAnime);
            this->field_0x7D6 = this->field_0x7D6 + 1;
        }
        uVar1 = g_dComIfG_gameInfo.play.mMesgAnimeTagInfo;
        if ((g_dComIfG_gameInfo.play.mMesgAnimeTagInfo != 0xff) && (g_dComIfG_gameInfo.play.mMesgAnimeTagInfo != this->field_0x7CC)) {
            g_dComIfG_gameInfo.play.mMesgAnimeTagInfo = 0xff;
            this->field_0x7CC = uVar1;
            this->chngAnmTag();
        }
    } else if (param_1 == 0xe) {
        this->field_0x7D6 = 0;
    }
    this->ctrlAnmAtr();
    this->ctrlAnmTag();
}

/* 00000C1C-00000C74       .text setStt__11daNpc_Pm1_cFSc */
void daNpc_Pm1_c::setStt(s8 param_1) {
    /* Nonmatching */
    s8 prev_7D0 = this->field_0x7D0;
    this->field_0x7D0 = param_1;

    switch (this->field_0x7D0) {
        case 1:
            break;
        case 2:
            this->field_0x7D2 = 1;
            this->field_0x7CB = 0xff;
            this->field_0x7D1 = prev_7D0;
            return;
    }

    this->setAnm();
}

/* 00000C74-00000C7C       .text next_msgStatus__11daNpc_Pm1_cFPUl */
u16 daNpc_Pm1_c::next_msgStatus(u32*) {
    /* Nonmatching */
    return 0x10;
}

/* 00000C7C-00000C84       .text getMsg__11daNpc_Pm1_cFv */
u32 daNpc_Pm1_c::getMsg() {
    /* Nonmatching */
    return 0;
}

/* 00000C84-00000CD4       .text eventOrder__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::eventOrder() {
    /* Nonmatching */
    if (((this->field_0x7CF == 1) || (this->field_0x7CF == 2)) &&
        (this->eventInfo.mCondition = this->eventInfo.mCondition | dEvtCnd_CANTALK_e, this->field_0x7CF == 1))
    {
        fopAcM_orderSpeakEvent(this);
    }
}

/* 00000CD4-00000D14       .text checkOrder__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::checkOrder() {
    /* Nonmatching */
    u16 event_command;

    event_command = this->eventInfo.mCommand;
    if (event_command == dEvtCmd_INDEMO_e) {
        return;
    }
    if (event_command != dEvtCmd_INTALK_e) {
        return;
    }
    if ((this->field_0x7CF != 1) && (this->field_0x7CF != 2)) {
        return;
    }
    this->field_0x7CF = 0;
    this->field_0x7C5 = 1;
}

/* 00000D14-00000EA4       .text lookBack__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::lookBack() {
    /* Nonmatching */
    cXyz* dstPos;
    s16 desiredYRot;
    s8 sVar1;
    bool headOnlyFollow;
    cXyz targetPos;
    cXyz srcPos;

    srcPos = current.pos;
    srcPos.y = eyePos.y;
    targetPos.x = 0.0f;
    targetPos.y = 0.0f;
    targetPos.z = 0.0f;
    dstPos = NULL;
    desiredYRot = current.angle.y;
    headOnlyFollow = mHeadOnlyFollow;
    sVar1 = field_0x7D2;

    switch (sVar1) {
        case 1:
            targetPos = dNpc_playerEyePos(-20.0f);
            dstPos = &targetPos;
            srcPos = current.pos;
            srcPos.y = eyePos.y;
            break;
        case 2:
            targetPos = field_0x798;
            dstPos = &targetPos;
            srcPos = current.pos;
            srcPos.y = eyePos.y;
            break;
        case 3:
            desiredYRot = field_0x7B2;
            break;
        case 0:
            break;
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&field_0x7B0, l_HIO.mPrmTbl.field_12, 4, 0x800);
    } else {
        field_0x7B0 = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, srcPos, desiredYRot, field_0x7B0, headOnlyFollow);
}

/* 00000EA4-00000F24       .text chkAttention__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::chkAttention() {
    /* Nonmatching */
    if (dComIfGp_getAttention().LockonTruth()) {
        return this == (daNpc_Pm1_c*)dComIfGp_getAttention().LockonTarget(0);
    } else {
        return this == (daNpc_Pm1_c*)dComIfGp_getAttention().ActionTarget(0);
    }
}

/* 00000F24-00000F88       .text setAttention__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setAttention() {
    /* Nonmatching */
    float fVar1;
    float fVar2;

    fVar1 = this->current.pos.z;
    fVar2 = this->current.pos.y + l_HIO.mPrmTbl.mAttentionArrowYOffset;
    this->attention_info.position.x = this->current.pos.x;
    this->attention_info.position.y = fVar2;
    this->attention_info.position.z = fVar1;
    if ((this->field_0x7BC == 0) && (this->field_0x7C0 == 0)) {
        return;
    }
    fVar2 = (this->mEyePos).z;
    fVar1 = (this->mEyePos).y;
    this->eyePos.x = (this->mEyePos).x;
    this->eyePos.y = fVar1;
    this->eyePos.z = fVar2;
    this->field_0x7BC = 0;
}

/* 00000F88-00000FB4       .text decideType__11daNpc_Pm1_cFi */
bool daNpc_Pm1_c::decideType(int i_type) {
    /* Nonmatching */
    this->field_0x7D3 = -1;
    switch (fopAcM_GetName(this)) {
        case fpcNm_NPC_PM1_e:
            this->field_0x7D3 = 0;
            this->field_0x7D4 = 0;
            break;
    }
    return 1;
}

/* 00000FB4-0000103C       .text event_actionInit__11daNpc_Pm1_cFi */
void daNpc_Pm1_c::event_actionInit(int param_1) {
    /* Nonmatching */
    int* pActNo;

    pActNo = dComIfGp_evmng_getMyIntegerP(param_1, "ActNo");
    dComIfGp_evmng_getMyIntegerP(param_1, "Timer");
    if (pActNo != NULL) {
        this->field_0x7CA = *pActNo;
    }
}

/* 0000103C-0000104C       .text event_action__11daNpc_Pm1_cFv */
u8 daNpc_Pm1_c::event_action() {
    /* Nonmatching */
    if ((BOOL)this->field_0x7CA > 0) {
        return 1;
    }
    return 1;
}

/* 0000104C-00001154       .text privateCut__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::privateCut() {
    /* Nonmatching */
    int staffIdx;
    u8 cVar3;
    static char* cut_name_tbl[] = {
        "ACTION",
    };
    staffIdx = dComIfGp_evmng_getMyStaffId("Pm1", (fopAc_ac_c*)0x0, 0);
    if (staffIdx != -1) {
        this->field_0x7C9 = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, 1, 1, 0);
        if (this->field_0x7C9 == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch ((u8)this->field_0x7C9) {
                    case 0:
                        this->event_actionInit(staffIdx);
                        break;
                }
            }
            switch ((u8)this->field_0x7C9) {
                case 0:
                    cVar3 = this->event_action();
                    break;
                default:
                    cVar3 = 1;
                    break;
            }
            if (cVar3 != 0) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }
    }
}

/* 00001154-00001174       .text endEvent__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::endEvent() {
    /* Nonmatching */
    dComIfGp_event_onEventFlag(dEvtFlag_UNK8_e);
    this->field_0x7CB = 0xff;
}

/* 00001174-000011D4       .text event_proc__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::event_proc() {
    /* Nonmatching */
    bool bVar1;

    bVar1 = this->mEventCut.cutProc();

    if (!bVar1) {
        this->privateCut();
    }
    this->lookBack();
    this->shape_angle.x = this->current.angle.x;
    this->shape_angle.y = this->current.angle.y;
    this->shape_angle.z = this->current.angle.z;
}

/* 000011D4-00001280       .text set_action__11daNpc_Pm1_cFM11daNpc_Pm1_cFPCvPvPv_iPv */
BOOL daNpc_Pm1_c::set_action(ActionFunc i_action, void* param_2) {
    /* Nonmatching */
    if (mCurrActionFunc != i_action) {
        if (mCurrActionFunc != 0) {
            field_0x7D5 = -1;
            (this->*mCurrActionFunc)(param_2);
        }
        mCurrActionFunc = i_action;
        field_0x7D5 = 0;
        (this->*mCurrActionFunc)(param_2);
    }
    return true;
}

/* 00001280-00001378       .text wait01__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::wait01() {
    /* Nonmatching */
    bool bVar2;

    if (this->field_0x7C5 != 0) {
        bVar2 = true;
        this->field_0x7B7 = 0xff;
        if (dComIfGp_event_chkTalkXY()) {
            if (dComIfGp_evmng_ChkPresentEnd() != 0) {
                this->field_0x7B7 = dComIfGp_event_getPreItemNo();
            } else {
                bVar2 = false;
            }
        }
        if (bVar2) {
            this->setStt(2);
        }
    } else {
        this->field_0x7CF = 2;
        if (this->field_0x7C4 != 0) {
            this->field_0x7D2 = 1;
        } else {
            this->field_0x7D2 = 3;
            this->field_0x7B2 = (this->mRot).y;
            m_jnt.setTrn();
        }
    }
    return 1;
}

/* 00001378-00001408       .text talk01__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::talk01() {
    /* Nonmatching */
    u8 uVar1;
    msg_class* pmVar2;

    this->talk(1);
    pmVar2 = this->mpCurrMsg;
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
            case 6:
            case 2:
                break;
            case 19:
                this->field_0x7B7 = 0xff;
                this->setStt(this->field_0x7D1);
                this->field_0x7C8 = 0;
                this->field_0x7C5 = 0;
                this->endEvent();
        }
    }
    return TRUE;
}

/* 00001408-000014BC       .text wait_action1__11daNpc_Pm1_cFPv */
int daNpc_Pm1_c::wait_action1(void*) {
    /* Nonmatching */
    if (this->field_0x7D5 == 0) {
        setStt(1);
        this->field_0x7D5 += +1;
    } else if (this->field_0x7D5 != -1) {
        this->field_0x7C4 = this->chkAttention();
        switch (this->field_0x7D0) {
            case 2:
                this->field_0x7C0 = this->talk01();
                break;
            case 1:
                this->field_0x7C0 = this->wait01();
                break;
            default:
                this->field_0x7C0 = 0;
                break;
        }
        this->lookBack();
    }
    return 1;
}

/* 000014BC-00001558       .text demo__11daNpc_Pm1_cFv */
u8 daNpc_Pm1_c::demo() {
    /* Nonmatching */
    if (demoActorID == 0) {
        if (field_0x7C7 != 0) {
            field_0x7C7 = 0;
        }
    } else {
        field_0x7C7 = 1;
        dComIfGp_demo_getActor(demoActorID);
        dDemo_setDemoData(
            this,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf,
            "Pm"
        );
    }
    return field_0x7C7;
}

/* 00001558-000016BC       .text _draw__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_draw() {
    /* Nonmatching */
    J3DModelData* model_data;
    J3DModel* model;

    model = (this->mpMorf)->getModel();
    model_data = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &this->tevStr);
    mBtpAnm.entry(model_data, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);
    dNpc_setShadowModel(this->mpModel, model_data, model);
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    this->mShadowId = dComIfGd_setRealShadow(mShadowId, 1, this->mpModel, &pos, 800.0f, current.pos.y - mObjAcch.GetGroundH(), NULL);

    if (this->mShadowId == 0) {
        dComIfGd_setSimpleShadow(
            &current.pos,
            mObjAcch.GetGroundH(),
            40.0f,
            dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd)->GetNP(),
            0,
            1.0,
            &dDlst_shadowControl_c::mSimpleTexObj
        );
    }
    dSnap_RegistFig(DSNAP_TYPE_PM1, this, 1.0f, 1.0f, 1.0f);

    // Color literals for debug drawing. Unused in non-debug builds.
    (GXColor){0xFF, 0x00, 0x00, 0x80};
    (GXColor){0x00, 0x00, 0xFF, 0x80};

    return 1;
}

/* 000016BC-00001818       .text _execute__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_execute() {
    /* Nonmatching */
    if (this->field_0x7B8 == 0) {
        (this->mPos).x = this->current.pos.x;
        (this->mPos).y = this->current.pos.y;
        (this->mPos).z = this->current.pos.z;
        (this->mRot).x = this->current.angle.x;
        (this->mRot).y = this->current.angle.y;
        (this->mRot).z = this->current.angle.z;
        this->field_0x7B8 = 1;
    }
    m_jnt.setParam(
        l_HIO.mPrmTbl.field_8,
        l_HIO.mPrmTbl.field_A,
        l_HIO.mPrmTbl.field_C,
        l_HIO.mPrmTbl.field_E,
        l_HIO.mPrmTbl.field_0,
        l_HIO.mPrmTbl.field_2,
        l_HIO.mPrmTbl.field_4,
        l_HIO.mPrmTbl.field_6,
        l_HIO.mPrmTbl.field_10
    );
    this->checkOrder();
    if (this->demo() == 0) {
        if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            this->event_proc();

        } else {
            (this->*mCurrActionFunc)(NULL);
            this->shape_angle.x = this->current.angle.x;
            this->shape_angle.y = this->current.angle.y;
            this->shape_angle.z = this->current.angle.z;
        }
    }
    this->eventOrder();
    if (this->field_0x7C7 == 0) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    this->setMtx();
    this->setCollision(50.0, 130.0);
    return 1;
}

/* 00001818-0000189C       .text _delete__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_delete() {
    /* Nonmatching */
    fopAcM_RegisterDeleteID(this);

    dComIfG_resDeleteDemo(&mPhase, "Pm");

    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    if (l_HIO.field_0x8 >= 0) {
        l_HIO.field_0x8 += -1;
        if (l_HIO.field_0x8 < 0) {
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return true;
}

/* 0000189C-000018BC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_actor) {
    return ((daNpc_Pm1_c*)i_actor)->CreateHeap();
}

/* 000018BC-00001A2C       .text _create__11daNpc_Pm1_cFv */
cPhs_State daNpc_Pm1_c::_create() {
    /* Nonmatching */
    cPhs_State is_load;
    static int a_heap_size_tbl[] = {0x272E0};
    fopAcM_RegisterCreateID(this);
    fopAcM_ct_Retail(this, daNpc_Pm1_c);

    if (this->decideType(fopAcM_GetParam(this) & 0xff) == 0) {
        return cPhs_ERROR_e;
    }
    is_load = dComIfG_resLoad(&this->mPhase, "Pm");
    if (is_load != cPhs_COMPLEATE_e) {
        return is_load;
    }
    if (l_HIO.field_0x8 < 0) {
        l_HIO.mNo = mDoHIO_createChild("貧乏マギ−", &l_HIO);
    }
    l_HIO.field_0x8 += 1;
    if (fopAcM_entrySolidHeap(this, CheckCreateHeap, a_heap_size_tbl[field_0x7D3])) {
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox((fopAc_ac_c*)this, -50.0, -20.0, -50.0, 50.0, 150.0, 50.0);
    } else {
        return cPhs_ERROR_e;
    }
    if (createInit() == 0) {
        is_load = cPhs_ERROR_e;
    }
    return is_load;
}

/* 00001E5C-00002168       .text CreateHeap__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::CreateHeap() {
    /* Nonmatching */
    static u8 a_tex_pattern_num_tbl[1] = {0};
    J3DModelData* a_mdl_data;

    a_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Pm", dRes_ID_PM_BDL_PM_e);
    JUT_ASSERT(DEMO_SELECT(1310, 1319), a_mdl_data != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_data,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Pm", dRes_ID_PM_BCK_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11020002
    );
    if (mpMorf) {
        if (mpMorf->getModel()) {
            m_head_jnt_num = a_mdl_data->getJointName()->getIndex("head");
            JUT_ASSERT(DEMO_SELECT(1329, 1338), m_head_jnt_num >= 0);
            m_backbone_jnt_num = a_mdl_data->getJointName()->getIndex("backbone");
            JUT_ASSERT(DEMO_SELECT(1331, 1340), m_backbone_jnt_num >= 0);
            field_0x7CD = a_tex_pattern_num_tbl[field_0x7D3];
            if (initTexPatternAnm(false) != 0) {
                mpModel = mDoExt_J3DModel__create(a_mdl_data, 0x20000, 0x11020203);
                if (mpModel != NULL) {
                    for (u16 i = 0; i < a_mdl_data->getJointNum(); i += 1) {
                        if ((i == m_head_jnt_num) || (i == m_backbone_jnt_num)) {
                            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Pm);
                        }
                    }
                    mpMorf->getModel()->setUserArea((u32)this);
                    mAcchCir.SetWall(30.0f, 50.0f);
                    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
                    return TRUE;
                }
            }
        }
        mpMorf = NULL;
    }
    return FALSE;
}

/* 00002168-00002188       .text daNpc_Pm1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Pm1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_create();
}

/* 00002188-000021A8       .text daNpc_Pm1_Delete__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Delete(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_delete();
}

/* 000021A8-000021C8       .text daNpc_Pm1_Execute__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Execute(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_execute();
}

/* 000021C8-000021E8       .text daNpc_Pm1_Draw__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Draw(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_draw();
}

/* 000021E8-000021F0       .text daNpc_Pm1_IsDelete__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_IsDelete(daNpc_Pm1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Pm1_Method = {
    (process_method_func)daNpc_Pm1_Create,
    (process_method_func)daNpc_Pm1_Delete,
    (process_method_func)daNpc_Pm1_Execute,
    (process_method_func)daNpc_Pm1_IsDelete,
    (process_method_func)daNpc_Pm1_Draw,
};

actor_process_profile_definition g_profile_NPC_PM1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_PM1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Pm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_PM1_e,
    /* Actor SubMtd */ &l_daNpc_Pm1_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
