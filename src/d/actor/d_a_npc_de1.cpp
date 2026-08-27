/**
 * d_a_npc_de1.cpp
 * NPC - Deku Tree
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_de1.h"
#include "d/actor/d_a_cc.h"
#include "d/actor/d_a_leaflift.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_w_sv.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_audio.h"
#include "res/Object/De.h"
#include "f_pc/f_pc_executor.h"
#include "f_pc/f_pc_name.h"
#include "f_pc/f_pc_manager.h"

static fopAc_ac_c* l_check_inf[0x64];
static int l_check_wrk;
static daNpc_De1_HIO_c l_HIO;

/* 000000EC-00000144       .text __ct__15daNpc_De1_HIO_cFv */
daNpc_De1_HIO_c::daNpc_De1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* m00 */ 100.0f,
        /* m04 */ 150.0f,
        /* m08 */ 1.0f,
        /* m0C */ 800.0f,
        /* m10 */ 44.0f,
        /* m14 */ 100.0f,
        /* m18 */ 976.0f,
        /* m1C */ 0.0f,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    mNum = -1;
}

/* 00000144-000001BC       .text searchActor_leafLift__FPvPv */
void* searchActor_leafLift(void* i_actorP, void*) {
    if (l_check_wrk < 0x64 && fopAc_IsActor(i_actorP) && fpcM_GetName(i_actorP) == fpcNm_LEAF_LIFT_e) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actorP;
        l_check_wrk++;
    }

    return NULL;
}

/* 000001BC-0000033C       .text createInit__11daNpc_De1_cFv */
bool daNpc_De1_c::createInit() {
    mEventCut.setActorInfo2("De1", this);
    attention_info.flags = 0xa;
    attention_info.distances[1] = 0x15;
    attention_info.distances[3] = 0x16;
    gravity = 0.0f;
    mHomePos = current.pos;

    switch (mType) {
    case 0:
        if (dComIfGs_isEventBit(0x1801)) {
            set_action(&daNpc_De1_c::wait_action2, NULL);
        } else {
            set_action(&daNpc_De1_c::wait_action1, NULL);
        }
        break;
    case 1:
        set_action(&daNpc_De1_c::wait_action2, NULL);
        break;
    }

    shape_angle = current.angle;
    mpMorf->setMorf(0.0f);
    mMorfFrame = 1;
    setMtx();
    return TRUE;
}

void daNpc_De1_c::setMtx() {
    if (!mNoPlayMorf) {
        mPlayMorfResult = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mPlayMorfResult = 1;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    if (cLib_calcTimer(&mSoundTimer) == 0 && mPlayMorfResult && mCurAnmIdx == 3) {
        fopAcM_seStartCurrent(this, JA_SE_CV_DEKU_AGONY, 0);
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::scaleM(l_HIO.mPrm.m08, l_HIO.mPrm.m08, l_HIO.mPrm.m08);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpBgWSv->CopyBackVtx();
    mpMorf->calc();

    J3DModel* model = mpMorf->getModel();
    dBgWSv* bgw = mpBgWSv;
    Vec* vtx = (Vec*)model->getCurrentVtxPos();
    if (bgw->GetVtxTbl() == NULL) {
        bgw->SetVtxTbl(vtx);
        bgw->CopyBackVtx();
    } else {
        bgw->SetVtxTbl(vtx);
    }
    bgw->Move();

    followPa_happa();
    setDemoStartCenter();
    if (mType == 0 && !dComIfGs_isEventBit(0x1801)) {
        cc_set();
    }
    setAttention();
}

/* 00000550-00000658       .text anmResID__11daNpc_De1_cFiPiPi */
BOOL daNpc_De1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    static const int a_anm_idx_tbl[][2] = {
        {dRes_ID_DE_BCK_WAIT01_e, -1},
        {dRes_ID_DE_BCK_SLEEP_e, -1},
        {dRes_ID_DE_BCK_WAKE_e, -1},
        {dRes_ID_DE_BCK_SUFFER_e, -1},
        {dRes_ID_DE_BCK_TALK01_e, -1},
        {dRes_ID_DE_BCK_TALK02_e, -1},
        {dRes_ID_DE_BCK_TALK03_e, -1},
    };
    JUT_ASSERT(284, 0 <= i_num && i_num < ANM_END);
    JUT_ASSERT(285, o_bck_num && o_bas_num);
    *o_bck_num = a_anm_idx_tbl[i_num][0];
    *o_bas_num = a_anm_idx_tbl[i_num][1];
    return TRUE;
}

/* 00000658-00000744       .text setAnm_anm__11daNpc_De1_cFPQ211daNpc_De1_c9anm_prm_c */
BOOL daNpc_De1_c::setAnm_anm(daNpc_De1_c::anm_prm_c* i_anmPrmP) {
    BOOL ret = FALSE;
    if (i_anmPrmP->mAnmIdx >= 0 && mCurAnmIdx != i_anmPrmP->mAnmIdx) {
        mCurAnmIdx = i_anmPrmP->mAnmIdx;
        if (mpMorf != NULL) {
            int bckResId;
            int basResId;
            anmResID(mCurAnmIdx, &bckResId, &basResId);
            if (bckResId >= 0) {
                dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mPlaySpeed, bckResId, basResId, "De");
            }
            if (mCurAnmIdx == 3) {
                set_pa_happa();
            } else {
                del_pa_happa();
            }
            ret = TRUE;
        }
        mPrevMorfFrame = 0.0f;
        field_0x7A5 = 0;
        mPlayMorfResult = 0;
    }
    return ret;
}

/* 00000744-00000774       .text setAnm_NUM__11daNpc_De1_cFi */
void daNpc_De1_c::setAnm_NUM(int i_anmIdx) {
    static anm_prm_c a_anm_prm_tbl[] = {
        {ANM_WAIT01, 8.0f, 1.0f, 2},
        {ANM_SLEEP, 8.0f, 1.0f, 2},
        {ANM_WAKE, 8.0f, 1.0f, 0},
        {ANM_SUFFER, 8.0f, 1.0f, 2},
        {ANM_TALK01, 8.0f, 1.0f, 2},
        {ANM_TALK02, 8.0f, 1.0f, 2},
        {ANM_TALK03, 8.0f, 1.0f, 2},
    };
    setAnm_anm(&a_anm_prm_tbl[i_anmIdx]);
}

/* 00000774-000007AC       .text setAnm__11daNpc_De1_cFv */
void daNpc_De1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {-1, 0.0f, 0.0f, -1},
        {ANM_WAIT01, 8.0f, 1.0f, 2},
        {-1, 0.0f, 0.0f, -1},
        {ANM_WAIT01, 8.0f, 1.0f, 2},
        {-1, 0.0f, 0.0f, -1},
        {ANM_WAIT01, 8.0f, 1.0f, 2},
        {ANM_SLEEP, 8.0f, 1.0f, 2},
        {-1, 0.0f, 0.0f, -1},
    };
    setAnm_anm(&a_anm_prm_tbl[mStatus]);
}

/* 000007AC-000007B8       .text chngAnmTag__11daNpc_De1_cFv */
void daNpc_De1_c::chngAnmTag() {
    switch (mAnmTag) {
    case 0:
        break;
    }
}

/* 000007B8-000007C4       .text ctrlAnmTag__11daNpc_De1_cFv */
void daNpc_De1_c::ctrlAnmTag() {
    switch (mAnmAtr) {
    case 0:
        break;
    }
}

/* 000007C4-00000800       .text chngAnmAtr__11daNpc_De1_cFUc */
void daNpc_De1_c::chngAnmAtr(unsigned char i_anmAtr) {
    if (i_anmAtr < 4 && i_anmAtr != mAnmAtr) {
        mAnmAtr = i_anmAtr;
        setAnm_ATR();
    }
}

/* 00000800-00000848       .text ctrlAnmAtr__11daNpc_De1_cFv */
void daNpc_De1_c::ctrlAnmAtr() {
    switch (mAnmAtr) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        if (mPlayMorfResult) {
            mAnmAtr = 0;
            setAnm_ATR();
        }
        break;
    }
}

/* 00000848-0000087C       .text setAnm_ATR__11daNpc_De1_cFv */
void daNpc_De1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {ANM_WAIT01, 8.0f, 1.0f, 2},
        {ANM_TALK01, 8.0f, 1.0f, 2},
        {ANM_TALK02, 8.0f, 1.0f, 2},
        {ANM_TALK03, 8.0f, 1.0f, 2},
    };
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 0000087C-00000938       .text anmAtr__11daNpc_De1_cFUs */
void daNpc_De1_c::anmAtr(unsigned short i_msgStatus) {
    if (i_msgStatus == fopMsgStts_MSG_TYPING_e) {
        if (mMsgTypingState == 0) {
            mAnmTag = 0xFF;
            chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mMsgTypingState++;
        }
        u8 tagInfo = dComIfGp_getMesgAnimeTagInfo();
        if (tagInfo != 0xFF && tagInfo != mAnmTag) {
            dComIfGp_clearMesgAnimeTagInfo();
            mAnmTag = tagInfo;
            chngAnmTag();
        }
    } else if (i_msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
        mMsgTypingState = 0;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000938-000009B4       .text setStt__11daNpc_De1_cFSc */
void daNpc_De1_c::setStt(signed char i_stt) {
    s8 prev_stt = mStatus;
    mStatus = i_stt;
    switch (mStatus) {
    case 2:
    case 4:
        mAnmAtr = 0xFF;
        mTalk02State = prev_stt;
        return;
    case 7:
        attention_info.flags |= fopAc_Attn_ENEMYFLAG_NOLOCKON_e;
        attention_info.distances[2] = 0x22;
        break;
    case 1:
        break;
    }
    setAnm();
}

/* 000009B4-00000C98       .text next_msgStatus__11daNpc_De1_cFPUl */
u16 daNpc_De1_c::next_msgStatus(unsigned long* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
    case 0x139D:
        *pMsgNo = 0x139E;
        break;
    case 0x139F:
        *pMsgNo = 0x13A0;
        break;
    case 0x13A1:
        *pMsgNo = 0x13A2;
        break;
    case 0x13A3:
        *pMsgNo = 0x13A4;
        break;
    case 0x13A4:
        *pMsgNo = 0x13A5;
        break;
    case 0x13A5:
        *pMsgNo = 0x13A6;
        break;
    case 0x13A8:
        *pMsgNo = 0x13A9;
        break;
    case 0x13AC:
        *pMsgNo = 0x13A9;
        break;
    case 0x13A9:
    case 0x13C5:
        if (dComIfGs_isEventBit(0x1D40)) {
            *pMsgNo = 0x13AA;
        } else {
            *pMsgNo = 0x13AB;
        }
        break;
    case 0x13AA:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *pMsgNo = 0x13AD;
            break;
        case 1:
            *pMsgNo = 0x13C7;
            break;
        default:
            goto default_msg;
        }
        break;
    case 0x13AB:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *pMsgNo = 0x13AD;
            break;
        case 1:
            *pMsgNo = 0x13CC;
            break;
        default:
            goto default_msg;
        }
        break;
    case 0x13CC:
        *pMsgNo = 0x13CD;
        break;
    case 0x13CD:
        *pMsgNo = 0x13CE;
        break;
    case 0x13CE:
        *pMsgNo = 0x13CF;
        break;
    case 0x13CF:
        *pMsgNo = 0x13D0;
        break;
    case 0x13D0:
        *pMsgNo = 0x13D1;
        break;
    case 0x13C7:
        *pMsgNo = 0x13C8;
        break;
    case 0x13C8:
        *pMsgNo = 0x13C9;
        break;
    case 0x13C9:
        *pMsgNo = 0x13CA;
        break;
    case 0x13CA:
        *pMsgNo = 0x13CB;
        break;
    case 0x13AD:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            if (dComIfGs_isEventBit(0x0102)) {
                *pMsgNo = 0x13B0;
            } else if (dComIfGs_isEventBit(0x3940)) {
                *pMsgNo = 0x13AF;
            } else {
                dComIfGs_onEventBit(0x3940);
                *pMsgNo = 0x13AE;
            }
            break;
        case 1:
            *pMsgNo = 0x13B6;
            break;
        default:
            goto default_msg;
        }
        break;
    case 0x13B6:
        if (dComIfGs_isEventBit(0x1820)) {
            if (dComIfGs_isStageBossEnemy(6)) {
                *pMsgNo = 0x13C2;
            } else {
                *pMsgNo = 0x13C4;
            }
        } else {
            *pMsgNo = 0x13C0;
        }
        break;
    case 0x13C0:
        *pMsgNo = 0x13C1;
        break;
    case 0x13C2:
        *pMsgNo = 0x13C3;
        break;
    case 0x13AE:
    case 0x13AF:
    case 0x13B0:
    case 0x13C1:
    case 0x13C3:
    case 0x13C4:
        *pMsgNo = 0x13C5;
        break;
    default_msg:
        *pMsgNo = 0x13C6;
        break;
    default:
        status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return status;
}

/* 00000C98-00000D6C       .text getMsg__11daNpc_De1_cFv */
u32 daNpc_De1_c::getMsg() {
    u32 msg = 0;
    switch (mType) {
    case 0:
        if (dComIfGs_checkGetItem(0x20)) {
            msg = dLib_setFirstMsg(0x0E40, 0x139F, 0x13A1);
        } else {
            msg = dLib_setFirstMsg(0x0E80, 0x139C, 0x139D);
        }
        break;
    case 1:
        if (dComIfGs_isEventBit(0x1C40)) {
            if (field_0x7A7) {
                msg = 0x13AC;
            } else {
                field_0x7A7 = 1;
                msg = 0x13A8;
            }
        } else {
            msg = dLib_setFirstMsg(0x1C20, 0x13A3, 0x13A7);
        }
        break;
    }
    return msg;
}

/* 00000D6C-00000E14       .text eventOrder__11daNpc_De1_cFv */
void daNpc_De1_c::eventOrder() {
    static char* a_demo_name_tbl[] = {
        "LIFT_UP",
        "DE_CHUCHU",
        "contact",
    };
    if (mDemoMode == 1 || mDemoMode == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mDemoMode == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mDemoMode >= 3) {
        if (mDemoMode == 3) {
            fopAcM_orderOtherEvent2(this, a_demo_name_tbl[mDemoMode - 3], 1, 0xF);
        } else {
            fopAcM_orderOtherEvent2(this, a_demo_name_tbl[mDemoMode - 3], 1, 0xFFFF);
        }
    }
}

/* 00000E14-00000F8C       .text checkOrder__11daNpc_De1_cFv */
void daNpc_De1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck("LIFT_UP") && mDemoMode == 3) {
            mDemoMode = 0;
        } else if (dComIfGp_evmng_startCheck("DE_CHUCHU") && mDemoMode == 4) {
            mDoAud_bgmStart(JA_BGM_DEKU_PINCH);
            mDemoMode = 0;
        } else if (dComIfGp_evmng_startCheck("contact") && mDemoMode == 5) {
            dComIfGs_onEventBit(0x1801);
            dComIfGp_setNextStage("Omori", 0xD5, 0, 8, 0.0f, 0, 1, 0);
            mDemoMode = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mDemoMode == 1 || mDemoMode == 2) {
            mDemoMode = 0;
            mPartnerNearPlayer = 1;
        }
    }
}

/* 00000F8C-000010B8       .text chkAttention__11daNpc_De1_cFv */
bool daNpc_De1_c::chkAttention() {
    fopAc_ac_c* partner = searchByID(mPartnerID);
    bool ret = false;
    if (partner) {
        f32 dist = l_HIO.mPrm.m04;
        if (mNearPlayer) {
            dist += 50.0f;
        }

        ret = dist >= (dComIfGp_getPlayer(0)->current.pos - partner->current.pos).absXZ();
    }
    return ret;
}

/* 000010B8-00001194       .text setAttention__11daNpc_De1_cFv */
void daNpc_De1_c::setAttention() {
    cXyz offset(0.0f, 1100.0f, 700.0f);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&offset, &mAttentionPos);
    mAttentionBasePos = mAttentionPos;
    attention_info.position.set(mAttentionBasePos.x, mAttentionBasePos.y + l_HIO.mPrm.m00, mAttentionBasePos.z);
    eyePos.set(mAttentionPos.x, mAttentionPos.y, mAttentionPos.z);
}

/* 00001194-000011C8       .text searchByID__11daNpc_De1_cFUi */
fopAc_ac_c* daNpc_De1_c::searchByID(fpc_ProcID i_id) {
    fopAc_ac_c* p_actor = NULL;
    fopAcM_SearchByID(i_id, &p_actor);
    return p_actor;
}

/* 000011C8-0000124C       .text setDemoStartCenter__11daNpc_De1_cFv */
void daNpc_De1_c::setDemoStartCenter() {
    cXyz offset(l_HIO.mPrm.m10, l_HIO.mPrm.m14, l_HIO.mPrm.m18);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&offset, &mDemoCenterPos);
}

/* 0000124C-00001300       .text partner_srch__11daNpc_De1_cFv */
BOOL daNpc_De1_c::partner_srch() {
    BOOL ret = FALSE;
    mPartnerID = fpcM_ERROR_PROCESS_ID_e;
    l_check_wrk = 0;
    for (int i = 0; i < 100; i++) {
        l_check_inf[i] = NULL;
    }
    fpcEx_Search(searchActor_leafLift, this);
    if (l_check_wrk != 0) {
        mPartnerID = fopAcM_GetID(l_check_inf[0]);
        ret = TRUE;
    }
    return ret;
}

/* 00001300-000013F0       .text ccCreate__11daNpc_De1_cFv */
void daNpc_De1_c::ccCreate() {
    u32 a_prm_tbl[10] = {
        0x00000002,
        0x00000102,
        0x00000002,
        0x00000102,
        0x00000002,
        0x00000102,
        0x00000002,
        0x00000102,
        0x00000002,
        0x00000102,
    };
    for (int i = 0; i < 10; i++) {
#if VERSION == VERSION_DEMO
        s8 roomNo = current.roomNo;
        m_cc_ID[i] = fopAcM_create(fpcNm_CC_e, a_prm_tbl[i], &current.pos, roomNo, NULL, NULL, -1, NULL);
#else
        m_cc_ID[i] = fopAcM_create(fpcNm_CC_e, a_prm_tbl[i], &current.pos, current.roomNo, NULL, NULL, -1, NULL);
#endif
        JUT_ASSERT(883, m_cc_ID[ i] != fpcM_ERROR_PROCESS_ID_e);
    }
}

/* 000013F0-000014A0       .text cc_set__11daNpc_De1_cFv */
void daNpc_De1_c::cc_set() {
    cXyz offset(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 10; i++) {
        fopAc_ac_c* p_actor = searchByID(m_cc_ID[i]);
        if (p_actor != NULL) {
            mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_c0_jnt_num[i]));
            mDoMtx_copy(mDoMtx_stack_c::get(), ((cc_class*)p_actor)->m7EC);
        }
    }
}

/* 000014A0-00001524       .text set_pa_happa__11daNpc_De1_cFv */
void daNpc_De1_c::set_pa_happa() {
#if VERSION == VERSION_DEMO
    mPaHappa.end();
    mpPaHappa = dComIfGp_particle_set(dPa_name::ID_IT_SN_DEKU_HAPPA00, &mPaHappaPos, &current.angle, NULL, 0xFF, &mPaHappa, fopAcM_GetRoomNo(this));
#else
    mPaHappa.end();
    dComIfGp_particle_set(dPa_name::ID_IT_SN_DEKU_HAPPA00, &mPaHappaPos, &current.angle, NULL, 0xFF, &mPaHappa, fopAcM_GetRoomNo(this));
#endif
}

/* 00001524-00001550       .text del_pa_happa__11daNpc_De1_cFv */
void daNpc_De1_c::del_pa_happa() {
#if VERSION == VERSION_DEMO
    if (mpPaHappa != NULL) {
        mpPaHappa->becomeInvalidEmitter();
        mpPaHappa = NULL;
    }
    mPaHappa.end();
#else
    mPaHappa.end();
#endif
}

/* 00001550-000015CC       .text followPa_happa__11daNpc_De1_cFv */
void daNpc_De1_c::followPa_happa() {
#if VERSION == VERSION_DEMO
    if (mpPaHappa != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_branchL_jnt_num));
        mDoMtx_stack_c::multVecZero(&mPaHappaPos);
    }
#else
    if (mPaHappa.getEmitter() != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_branchL_jnt_num));
        mDoMtx_stack_c::multVecZero(&mPaHappaPos);
    }
#endif
}

/* 000015CC-0000165C       .text decideType__11daNpc_De1_cFi */
BOOL daNpc_De1_c::decideType(int) {
    BOOL ret = TRUE;
    mHeapType = -1;
    switch (fpcM_GetName(this)) {
    case fpcNm_NPC_DE1_e:
        mHeapType = 0;
        if (!dComIfGs_isSymbol(2)) {
            mType = 0;
        } else {
            mType = 1;
        }
        break;
    default:
        ret = FALSE;
        break;
    }
    return ret;
}

/* 0000165C-00001858       .text event_actionInit__11daNpc_De1_cFi */
void daNpc_De1_c::event_actionInit(int i_staffIdx) {
    int* pActNo = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    int* pTimer = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    int* pNum = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Num");

    if (pActNo != NULL) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        mActNo = *pActNo;
        switch (mActNo) {
        case 1:
            if (pNum != NULL) {
                fopAc_ac_c* partner = searchByID(m_cc_ID[*pNum]);
                if (partner != NULL) {
                    dComIfGp_event_setItemPartner(partner);
                }
            }
            break;
        case 2:
            if (pTimer != NULL) {
                mTimer = *pTimer;
            } else {
                mTimer = 0;
            }
            if (pNum != NULL) {
                mDemoTimer = *pNum;
            } else {
                mDemoTimer = 0;
            }
            break;
        case 3:
            if (pNum != NULL) {
                setAnm_NUM(*pNum);
            }
            break;
        case 4:
            mDoAud_seStart(JA_SE_CV_DEKU_AGONY_L, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
            mSoundTimer = 84;
            break;
        case 5:
            player->changeOriginalDemo();
            player->changeDemoMode(24);
            player->onFrollCrashFlg(29);
            break;
        }
    }
}

/* 00001858-00001938       .text event_action__11daNpc_De1_cFv */
BOOL daNpc_De1_c::event_action() {
    BOOL ret = FALSE;
    switch (mActNo) {
    case 0: {
        fopAc_ac_c* partner = searchByID(mPartnerID);
        if (partner != NULL && ((daLlift_c*)partner)->MoveUpLift()) {
            ret = TRUE;
        }
        break;
    }
    case 2:
        if (cLib_calcTimer(&mTimer) == 0) {
            if (mDemoTimer >= 0 && mDemoTimer < 10) {
                fopAc_ac_c* cc = searchByID(m_cc_ID[mDemoTimer]);
                if (cc != NULL) {
                    ((cc_class*)cc)->m2FB = 1;
                }
            }
            ret = TRUE;
        }
        break;
    case 1:
    case 3:
    case 4:
    case 5:
        ret = TRUE;
        break;
    }
    return ret;
}

/* 00001938-00001A40       .text privateCut__11daNpc_De1_cFv */
void daNpc_De1_c::privateCut() {
    static char* cut_name_tbl[] = {
        "ACTION",
    };
    int staffIdx = dComIfGp_evmng_getMyStaffId("De1", NULL, 0);
    if (staffIdx != -1) {
        mCutType = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, 1, 1, 0);
        if (mCutType == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch (mCutType) {
                case 0:
                    event_actionInit(staffIdx);
                    break;
                }
            }

            int ret;
            switch (mCutType) {
            case 0:
                ret = event_action();
                break;
            default:
                ret = 1;
                break;
            }

            if ((u8)ret) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }
    }
}

/* 00001A40-00001A60       .text endEvent__11daNpc_De1_cFv */
void daNpc_De1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
}

/* 00001A60-00001B90       .text event_proc__11daNpc_De1_cFv */
void daNpc_De1_c::event_proc() {
    if (dComIfGp_evmng_endCheck("LIFT_UP")) {
        endEvent();
        mDemoMode = 1;
        setStt(3);
    } else if (dComIfGp_evmng_endCheck("DE_CHUCHU")) {
        dComIfGs_onTmpBit(0x308);
        endEvent();
        setStt(7);
    } else if (dComIfGp_evmng_endCheck("contact")) {
        endEvent();
        set_action(&daNpc_De1_c::wait_action2, NULL);
    } else {
        if (!mEventCut.cutProc()) {
            privateCut();
        }
    }
}

/* 00001B90-00001C3C       .text set_action__11daNpc_De1_cFM11daNpc_De1_cFPCvPvPv_iPv */
BOOL daNpc_De1_c::set_action(ActionFunc i_action, void* i_data) {
    if (mActionFunc != i_action) {
        if (mActionFunc) {
            mActionState = -1;
            (this->*mActionFunc)(i_data);
        }
        mActionFunc = i_action;
        mActionState = 0;
        (this->*mActionFunc)(i_data);
    }
    return TRUE;
}

/* 00001C3C-00001C94       .text wait01__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait01() {
    if (mPartnerNearPlayer) {
        setStt(2);
    } else {
        if (mNearPlayer) {
            mDemoMode = 2;
        } else {
            mDemoMode = 0;
        }
    }
    return TRUE;
}

/* 00001C94-00001D38       .text wait02__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait02() {
    if (mPartnerNearPlayer) {
        setStt(4);
    } else {
        fopAc_ac_c* p_actor = searchByID(mPartnerID);
        if (p_actor != NULL) {
#if VERSION == VERSION_DEMO
            const f32* p_height = &daLlift_c::m_height;
            if (p_actor->current.pos.y < p_actor->home.pos.y + *p_height) {
                setStt(5);
                return TRUE;
            }
#else
            if (p_actor->current.pos.y < p_actor->home.pos.y + daLlift_c::m_height) {
                setStt(5);
                return TRUE;
            }
#endif
        }
        if (mNearPlayer) {
            mDemoMode = 2;
        } else {
            mDemoMode = 0;
        }
    }
    return TRUE;
}

/* 00001D38-00001D8C       .text wait03__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait03() {
    fopAc_ac_c* p_actor = searchByID(mPartnerID);
    if (p_actor != NULL && ((daLlift_c*)p_actor)->checkEndDownLift()) {
        setStt(1);
    }
    return TRUE;
}

/* 00001D8C-00001EA0       .text wait04__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait04() {
    mDemoMode = 0;
    const cXyz& tmp = dComIfGp_getPlayer(0)->current.pos - mDemoCenterPos;
    cXyz vec;
#if VERSION == VERSION_DEMO
    vec.set(tmp.x, 0.0f, tmp.z);
#else
    vec.x = tmp.x;
    vec.y = 0.0f;
    vec.z = tmp.z;
#endif
    f32 dist = PSVECSquareMag(&vec);
    dist = std::sqrtf(dist);
    if (dist < l_HIO.mPrm.m0C) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        mDemoMode = 4;
        *(s16*)((u8*)player + 0x306) = cLib_targetAngleY(&player->current.pos, &current.pos);
    }
    return TRUE;
}

/* 00001EA0-00001F38       .text wait05__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait05() {
    if (mDemoMode == 5) {
        return TRUE;
    }

    mDemoMode = 0;
    int i;
    for (i = 0; i < 10; i++) {
        if (searchByID(m_cc_ID[i]) != NULL) {
            break;
        }
    }
    if (i >= 10) {
        attention_info.flags &= ~fopAc_Attn_ENEMYFLAG_NOLOCKON_e;
        mDemoMode = 5;
    }
    return TRUE;
}

/* 00001F38-00001F90       .text talk01__11daNpc_De1_cFv */
BOOL daNpc_De1_c::talk01() {
    if (mDemoMode != 3) {
        field_0x7A6 = 0xff;
        mIsFirstTalk = 0;
        mPartnerNearPlayer = 0;
        endEvent();
        mDemoMode = 3;
    }
    return TRUE;
}

/* 00001F90-00002020       .text talk02__11daNpc_De1_cFv */
BOOL daNpc_De1_c::talk02() {
    talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case 2:
        case 6:
            break;
        case 0x13:
            field_0x7A6 = 0xff;
            setStt(mTalk02State);
            mIsFirstTalk = 0;
            mPartnerNearPlayer = 0;
            endEvent();
            break;
        }
    }
    return TRUE;
}

/* 00002020-000020C0       .text wait_action1__11daNpc_De1_cFPv */
BOOL daNpc_De1_c::wait_action1(void*) {
    if (mActionState == 0) {
        setStt(6);
        ccCreate();
        mActionState++;
    } else if (mActionState != -1) {
        mNearPlayer = chkAttention();
        switch (mStatus) {
        case 6:
            wait04();
            break;
        case 7:
            wait05();
            break;
        }
    }
    return TRUE;
}

/* 000020C0-000021AC       .text wait_action2__11daNpc_De1_cFPv */
BOOL daNpc_De1_c::wait_action2(void*) {
    if (mActionState == 0) {
        setStt(1);
        mActionState++;
    } else if (mActionState != -1) {
        if (mActionState == 1) {
            partner_srch();
            mActionState++;
        }
        mNearPlayer = chkAttention();
        switch (mStatus) {
        case 1:
            wait01();
            break;
        case 2:
            talk01();
            break;
        case 3:
            wait02();
            break;
        case 4:
            talk02();
            break;
        case 5:
            wait03();
            break;
        default:
            break;
        }
    }
    return TRUE;
}

/* 000021AC-00002248       .text demo__11daNpc_De1_cFv */
u8 daNpc_De1_c::demo() {
    if (demoActorID == 0) {
        if (mNoPlayMorf != 0) {
            mNoPlayMorf = 0;
        }
    } else {
        mNoPlayMorf = 1;
        dComIfGp_demo_getActor(demoActorID);
        dDemo_setDemoData(this, 0x6a, mpMorf, "De");
    }
    return mNoPlayMorf;
}

/* 00002248-00002358       .text _draw__11daNpc_De1_cFv */
BOOL daNpc_De1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    j3dSys.mDrawBuffer[0] = dComIfGd_getOpaListBG();
    j3dSys.mDrawBuffer[1] = dComIfGd_getXluListBG();
    mpMorf->entryDL();
    j3dSys.mDrawBuffer[0] = dComIfGd_getOpaList();
    j3dSys.mDrawBuffer[1] = dComIfGd_getXluList();
    if (*(u8*)&l_HIO.mPrm.m1C) {
        fopAc_ac_c* p_actor = searchByID(mPartnerID);
        if (p_actor != NULL) {
            cXyz pos = p_actor->current.pos;
            pos.y = 950.0f;
            static const GXColor c1 = { 0xFF, 0x00, 0x00, 0x80 };
            static const GXColor c2 = { 0x00, 0x00, 0xFF, 0x80 };
            static const GXColor c3 = { 0xFF, 0x00, 0x00, 0x80 };
            static const GXColor c4 = { 0x00, 0x00, 0xFF, 0x80 };
            static const GXColor c5 = { 0x00, 0xFF, 0x00, 0x80 };
        }
    }
    dSnap_RegistFig(0xa6, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002358-00002454       .text _execute__11daNpc_De1_cFv */
BOOL daNpc_De1_c::_execute() {
    if (mExecMode == 0) {
        mOrigPos = current.pos;
        mOrigAngle = current.angle;
        mExecMode = 1;
    }

    checkOrder();
    if (!demo()) {
        if (dComIfGp_event_runCheck() && eventInfo.mCommand != dEvtCmd_INTALK_e) {
            event_proc();
        } else {
            (this->*mActionFunc)(NULL);
        }
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        shape_angle = current.angle;
    }

    eventOrder();
    setMtx();
    return TRUE;
}

/* 00002454-00002500       .text _delete__11daNpc_De1_cFv */
BOOL daNpc_De1_c::_delete() {
    dComIfG_resDeleteDemo(&mPhs, "De");
    dComIfG_Bgsp()->Release((cBgW*)mpBgWSv);
#if VERSION == VERSION_DEMO
    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
#else
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
#endif
    del_pa_happa();
    if (l_HIO.mNum >= 0 && (l_HIO.mNum -= 1) < 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    return TRUE;
}

/* 00002500-00002520       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_De1_c*)i_this)->CreateHeap();
}

/* 00002520-000027A4       .text _create__11daNpc_De1_cFv */
cPhs_State daNpc_De1_c::_create() {
#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(this, daNpc_De1_c);
#endif

    cPhs_State state = (cPhs_State)dComIfG_resLoad(&mPhs, "De");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }

    u32 prm = fopAcM_GetParam(this) & 0xFF;
    if (!(u8)decideType(prm)) {
        return cPhs_ERROR_e;
    }

    if (l_HIO.mNum < 0) {
        l_HIO.mNo = mDoHIO_createChild("デクの木", (JORReflexible*)&l_HIO); // Deku Tree
    }
    l_HIO.mNum++;

#if VERSION == VERSION_DEMO
    fopAcM_SetupActor(this, daNpc_De1_c);
#endif

    static u32 a_heap_size_tbl[] = {
        0x272E0,
    };
    if (fopAcM_entrySolidHeap(this, CheckCreateHeap, a_heap_size_tbl[mHeapType])) {
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        dComIfG_Bgsp()->Regist(mpBgWSv, this);
    } else {
        return cPhs_ERROR_e;
    }

    if (!createInit()) {
        state = cPhs_ERROR_e;
    }

    return state;
}

/* 00002AB0-00002E04       .text CreateHeap__11daNpc_De1_cFv */
BOOL daNpc_De1_c::CreateHeap() {
#if VERSION == VERSION_DEMO
    daNpc_De1_c* a_this = this;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectIDRes("De", dRes_ID_DE_BDL_DE_e);
    a_this->mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("De", dRes_ID_DE_BCK_WAIT01_e),
        2,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x00080000,
        0x11000002
    );

    if (a_this->mpMorf == NULL) {
        goto error_early;
    }

    if (a_this->mpMorf->getModel() == NULL) {
        goto error_cleanup;
    }

    a_this->m_branchL_jnt_num = modelData->getJointName()->getIndex("branchL");
    JUT_ASSERT(1729, m_branchL_jnt_num >= 0);

    a_this->m_head_jnt_num = modelData->getJointName()->getIndex("head");
    JUT_ASSERT(1731, m_head_jnt_num >= 0);

    static char* a_jnt_name_tbl[] = {
        "c1", "c2", "c3", "c4", "c5",
        "c6", "c7", "c8", "c9", "c10",
    };

    for (int i = 0; i < 10; i++) {
        a_this->m_c0_jnt_num[ i] = modelData->getJointName()->getIndex(a_jnt_name_tbl[i]);
        JUT_ASSERT(1734, m_c0_jnt_num[ i] >= 0);
    }

    a_this->mpMorf->getModel()->setUserArea(0);

    a_this->mpBgWSv = new dBgWDeform();
    if (a_this->mpBgWSv == NULL) {
        goto error_cleanup;
    }

    if (a_this->mpBgWSv->Set((cBgD_t*)dComIfG_getObjectIDRes("De", dRes_ID_DE_DZB_DE_e), a_this->mpMorf->getModel(), 0)) {
        goto error_cleanup;
    }

    a_this->mAcchCir.SetWall(0.0f, 0.0f);
    cXyz* p_speed = &a_this->speed;
    cXyz* p_old = &a_this->old.pos;
    cXyz* p_pos = &a_this->current.pos;
    a_this->mObjAcch.Set(p_pos, p_old, a_this, 1, &a_this->mAcchCir, p_speed);
    a_this->mObjAcch.SetWaterNone();
    a_this->mObjAcch.SetWallNone();
    a_this->mObjAcch.SetRoofNone();

    return TRUE;

error_cleanup:
    a_this->mpMorf = NULL;
error_early:
    return FALSE;
#else
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectIDRes("De", dRes_ID_DE_BDL_DE_e);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("De", dRes_ID_DE_BCK_WAIT01_e),
        2,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x00080000,
        0x11000002
    );

    if (mpMorf == NULL) {
        goto error_early;
    }

    if (mpMorf->getModel() == NULL) {
        goto error_cleanup;
    }

    m_branchL_jnt_num = modelData->getJointName()->getIndex("branchL");
    JUT_ASSERT(1744, m_branchL_jnt_num >= 0);

    m_head_jnt_num = modelData->getJointName()->getIndex("head");
    JUT_ASSERT(1746, m_head_jnt_num >= 0);

    static char* a_jnt_name_tbl[] = {
        "c1", "c2", "c3", "c4", "c5",
        "c6", "c7", "c8", "c9", "c10",
    };

    for (int i = 0; i < 10; i++) {
        m_c0_jnt_num[ i] = modelData->getJointName()->getIndex(a_jnt_name_tbl[i]);
        JUT_ASSERT(1749, m_c0_jnt_num[ i] >= 0);
    }

    mpMorf->getModel()->setUserArea(0);

    mpBgWSv = new dBgWDeform();
    if (mpBgWSv == NULL) {
        goto error_cleanup;
    }

    {
        J3DModel* model = mpMorf->getModel();
        cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectIDRes("De", dRes_ID_DE_DZB_DE_e);
        if (mpBgWSv->Set(bgd, model, 0)) {
            goto error_cleanup;
        }
    }

    mAcchCir.SetWall(0.0f, 0.0f);
    mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);
    mObjAcch.SetWaterNone();
    mObjAcch.SetWallNone();
    mObjAcch.SetRoofNone();

    return TRUE;

error_cleanup:
    mpMorf = NULL;
error_early:
    return FALSE;
#endif
}

/* 00002E04-00002E24       .text daNpc_De1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_De1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_create();
}

/* 00002E24-00002E44       .text daNpc_De1_Delete__FP11daNpc_De1_c */
static BOOL daNpc_De1_Delete(daNpc_De1_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_delete();
}

/* 00002E44-00002E64       .text daNpc_De1_Execute__FP11daNpc_De1_c */
static BOOL daNpc_De1_Execute(daNpc_De1_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_execute();
}

/* 00002E64-00002E84       .text daNpc_De1_Draw__FP11daNpc_De1_c */
static BOOL daNpc_De1_Draw(daNpc_De1_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_draw();
}

/* 00002E84-00002E8C       .text daNpc_De1_IsDelete__FP11daNpc_De1_c */
static BOOL daNpc_De1_IsDelete(daNpc_De1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_De1_Method = {
    (process_method_func)daNpc_De1_Create,
    (process_method_func)daNpc_De1_Delete,
    (process_method_func)daNpc_De1_Execute,
    (process_method_func)daNpc_De1_IsDelete,
    (process_method_func)daNpc_De1_Draw,
};

actor_process_profile_definition g_profile_NPC_DE1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_DE1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_De1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_DE1_e,
    /* Actor SubMtd */ &l_daNpc_De1_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
