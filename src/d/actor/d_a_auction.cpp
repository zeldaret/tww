//
// Generated by dtk
// Translation Unit: d_a_auction.cpp
//

#include "d/actor/d_a_auction.h"
#include "d/actor/d_a_npc_auction.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_camera.h"
#include "d/d_procname.h"
#include "d/res/res_auction.h"
#include "m_Do/m_Do_controller_pad.h"

// TODO: Remove this. It's just here to make the code more readable.
#define RAND_RANGE(a, b) (a + cM_rndF(b - a))

/* Structs are almost definitely not accurate */
struct NpcDatStruct {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
};

struct NpcMsgDatStruct {
    /* 0x00 */ s16 field_0x00;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
};

struct NpcCameraDatStruct { // Probably wrong
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ s16 field_0x08;
};

static cXyz l_camera_pos[3][2] = {
    cXyz(-265.0f, 48.0f, -631.0f),
    cXyz(332.0f, 232.0f, 286.0f),


    cXyz(-50.0f, 202.0f, 137.0f),
    cXyz(-87.0f, 239.0f, 330.0f),


    cXyz(-216.0f, 205.0f, 5.0f),
    cXyz(-379.0f, 238.0f, 115.0f),
};

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0f, 0.5f};


static daAuction_c::ItemData l_item_dat[] = {
    {dItem_JOY_PENDANT_e, 0x1D10, 40, 0x0F01},
    {COLLECT_MAP_27, 0x1D11, 5, 0x1080},
    {COLLECT_MAP_18, 0x1D12, 60, 0x1040},
    {KAKERA_HEART, 0x1D13, 80, 0x1020},
};

// Items obtained through the auction at some point during dev?
static daAuction_c::ItemData l_item_dat2[] = {
    {POSTMAN_STATUE, 0x1D14, 30, 0x1008},
    {PRESIDENT_STATUE, 0x1D15, 40, 0x1004},
};
static s16 l_item_dat22[] = {0x002A, 0x00F9};

static NpcDatStruct l_npc_dat[7] = {
    NULL,
};

static NpcMsgDatStruct l_npc_msg_dat[12] = {
    NULL,
};

static NpcCameraDatStruct l_npc_camera_dat[7] = {
    { 150.0f, 70.0f, -500 },
    { 200.0f, 100.0f, 0 },
    { 200.0f, 100.0f, 0 },
    { 200.0f, 100.0f, 0 },
    { 200.0f, 100.0f, 0 },
    { 200.0f, 100.0f, 0 },
    { 200.0f, 150.0f, 0 },
};

static f32 l_npc_emitter_ofsy[8] = {
    120.0f,
    180.0f,
    180.0f,
    180.0f,
    180.0f,
    210.0f,
    180.0f,
};

static f32 l_npc_camera_ofsy[8] = {
    150.0f,
    210.0f,
    210.0f,
    210.0f,
    210.0f,
    210.0f,
    240.0f,
    210.0f,
};

static s16 l_rest_msg_time1[4] = {
    30000,
    10000,
    5000,
    -1000,
};

static s16 l_rest_msg_time2[4] = {
    15000,
    10000,
    5000,
    -1000,
};

static u32 l_rest_msg_no[3] = {
};

static u32 l_rest_se_no[3] = {

};

static u32 l_link_face[8] = {

};

#ifdef DEBUG
// TODO: Figure out what these are
static daAuction_HIO_c l_HIO;
#endif

static daAuction_c::ProcFunc_t moveProc[] = {
    daAuction_c::executeWait,
    daAuction_c::executeNormal,
    daAuction_c::executeStart,
};

extern void dAuction_screen_delete();
extern void dAuction_screen_slotHide();
extern void dAuction_screen_gaugeHide();
extern void dAuction_screen_gaugeShow();
extern void dAuction_screen_gaugeUp();
extern void dAuction_screen_gaugeDown();
extern void dAuction_screen_talkStart();
extern void dAuction_screen_talkEnd();
extern uint dAuction_screen_create();

/* 000000EC-000002FC       .text __ct__11daAuction_cFv */
daAuction_c::daAuction_c() {
    // TODO: Refactor this
    for (int i = 0; i < 8; i++) {
        m738[i] = -1;
        m80C[i] = i;
        mAucMdlNo[i] = 0xFF;
    }

    // Shuffles lists randomly (I think)
    for (int i = 0; i < 100; i++) {
        int rnd1 = getRand(6);
        int rnd2 = getRand(6);

        u8 tmp = m80C[rnd1 + 1];
        m80C[rnd1 + 1] = m80C[rnd2 + 1];
        m80C[rnd2 + 1] = tmp;
    }

    mMoveState = 0;
    m820 = 1;
    m821 = 0;
    m7EC = 0;
    m7F0 = 0;
    m81C = 0xFF;
    m81D = 0xFF;
    mpEmitter = NULL;
    m836 = 0;

    eyePos = current.pos;
    m832 = 0;
}

/* 00000644-00000664       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daAuction_c*>(i_this)->createHeap();
}

/* 00000664-000006F4       .text _create__11daAuction_cFv */
s32 daAuction_c::_create() {
    fopAcM_SetupActor(this, daAuction_c);

    s32 phase_state = dComIfG_resLoad(&mPhs, "Pspl");

    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2400)) {
            return cPhs_ERROR_e;
        }

        return createInit();
    }

    return phase_state;
}

/* 000006F4-00000770       .text createHeap__11daAuction_cFv */
BOOL daAuction_c::createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectIDRes("Pspl", 0));

    if (modelData == NULL) {
        return FALSE;
    }

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    if (mpModel == NULL) {
        return FALSE;
    }

    return TRUE;
}

/* 00000770-000008C4       .text createInit__11daAuction_cFv */
s32 daAuction_c::createInit() {
    mEvtStartIdx = dComIfGp_evmng_getEventIdx("AUCTION_START");
    mEvtGetItemIdx = dComIfGp_evmng_getEventIdx("AUCTION_GET_ITEM");
    mEvtNoItemIdx = dComIfGp_evmng_getEventIdx("AUCTION_NO_ITEM");
    mEvtStart2Idx = dComIfGp_evmng_getEventIdx("AUCTION_START2");
    mEvtEnd2Idx = dComIfGp_evmng_getEventIdx("AUCTION_END2");

    mNpcEvtInfo.setActorInfo("Auction", this);
    m824 = 0;
    m826 = 0xFF;
    dComIfGp_setNpcNameMessageID(l_npc_msg_dat[getAucMdlNo(m824)].field_0x00);

    mCurrAuctionItemIndex = 0;

    s16 nameMsgID = l_item_dat[mCurrAuctionItemIndex].mNameMsgID;
    mCurrItemNameMsgNo = l_item_dat[mCurrAuctionItemIndex].mStartingBid;

    dComIfGp_setItemNameMessageID(nameMsgID);
    dComIfGp_setMessageCountNumber(mCurrItemNameMsgNo);

    setMtx();

    return cPhs_COMPLEATE_e;
}

/* 000008C4-0000092C       .text _delete__11daAuction_cFv */
BOOL daAuction_c::_delete() {
    dComIfG_resDelete(&mPhs, "Pspl");

    if (heap != NULL && mpEmitter != NULL) {
        mpEmitter->becomeInvalidEmitter();
    }

    return TRUE;
}

/* 0000092C-00000998       .text _draw__11daAuction_cFv */
BOOL daAuction_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG2, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    if (mFlags & 4) {
        mDoExt_modelUpdateDL(mpModel);
    }

    return TRUE;
}

/* 00000998-00000B10       .text _execute__11daAuction_cFv */
BOOL daAuction_c::_execute() {
    checkOrder();

    if (!dComIfGp_event_runCheck() || eventInfo.checkCommandTalk()) {
        (this->*moveProc[mMoveState])();
    } else {
        eventMove();
    }

    eventOrder();

    if (mpEmitter != NULL) {
        if (m836 & 1) { // Increase alpha
            if (m80A != 0) {
                m80A -= 1;
            } else {
                mAlpha += 4.0f;

                if (mAlpha > 255.0f) {
                    mAlpha = 255.0f;
                    m836 &= ~1;
                }

                mpEmitter->setGlobalAlpha(mAlpha);
            }
        } else if (m836 & 2) {  // Decrease alpha
            mAlpha -= 4.0f;

            if (mAlpha < 0.0f) {
                mpEmitter->becomeInvalidEmitter();
                mpEmitter = NULL;
            } else {
                mpEmitter->setGlobalAlpha(mAlpha);
            }
        }
    }

    setMtx();
    return TRUE;
}

/* 00000B10-00000B44       .text executeWait__11daAuction_cFv */
void daAuction_c::executeWait() {
    for (int i = 0; i < 8; i++) {
        if (m738[i] == -1) {
            return;
        }
    }

    mMoveState = 1;
}

/* 00000B44-00000B48       .text executeNormal__11daAuction_cFv */
void daAuction_c::executeNormal() {}

/* 00000B48-00000B4C       .text executeStart__11daAuction_cFv */
void daAuction_c::executeStart() {}

/* 00000B4C-00000C68       .text checkOrder__11daAuction_cFv */
void daAuction_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        // Might be unrolled loop?
        if (dComIfGp_evmng_startCheck(mEvtStartIdx) && m838 == 3) {
            m838 = 0;
        } else if (dComIfGp_evmng_startCheck(mEvtGetItemIdx) && m838 == 4) {
            m838 = 0;
        } else if (dComIfGp_evmng_startCheck(mEvtNoItemIdx) && m838 == 5) {
            m838 = 0;
        }

        if (dComIfGp_evmng_startCheck(mEvtStart2Idx) && m838 == 6) {
            m838 = 0;
        } else if (dComIfGp_evmng_startCheck(mEvtEnd2Idx) && m838 == 7) {
            m838 = 0;
        }
    }
}

/* 00000C68-00000EF8       .text eventOrder__11daAuction_cFv */
void daAuction_c::eventOrder() {
    if (m821 == 1) {
        mMoveState = 2;
        m838 = 3;
        m822 = m821;
        m821 = 0;
    } else if (m821 == 2) {
        mMoveState = 2;
        m838 = 6;
        m822 = m821;
        m821 = 0;
    }

    if (m838 == 1 || m838 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m838 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (m838 == 3) {
        if (dComIfGs_isEventBit(0x4008)) {
            mCurrAuctionItemIndex = dComIfGs_getEventReg(0xCD03);
            mCurrItemNameMsgNo += 0xA;
        } else {
            mCurrAuctionItemIndex = getItemNo();
        }

        dComIfGp_setItemNameMessageID(l_item_dat[mCurrAuctionItemIndex].mNameMsgID);
        mCurrItemNameMsgNo = l_item_dat[mCurrAuctionItemIndex].mStartingBid;
        dComIfGp_setMessageCountNumber(mCurrItemNameMsgNo);

        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mEvtStartIdx, 0, 0xFF7F);
        dComIfGp_startMiniGame(5);
    } else if (m838 == 4) {
        fopAcM_orderOtherEventId(this, mEvtGetItemIdx, 0xFF, 0xFF7F);
    } else if (m838 == 5) {
        fopAcM_orderOtherEventId(this, mEvtNoItemIdx, 0xFF, 0xFF7F);
    } else if (m838 == 6) {
        mCurrAuctionItemIndex &= 1;

        s16 nameMsgID = l_item_dat2[mCurrAuctionItemIndex].mNameMsgID;
        mCurrItemNameMsgNo = l_item_dat2[mCurrAuctionItemIndex].mStartingBid;

        dComIfGp_setItemNameMessageID(nameMsgID);
        dComIfGp_setMessageCountNumber(mCurrItemNameMsgNo);
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mEvtStart2Idx, 0, 0xFF7F);
        dComIfGp_startMiniGame(5);
    } else if (m838 == 7) {
        fopAcM_orderOtherEventId(this, mEvtEnd2Idx, 0xFF, 0xFF7F);
    }
}

/* 00000EF8-0000104C       .text eventMove__11daAuction_cFv */
void daAuction_c::eventMove() {
    if (dComIfGp_evmng_endCheck(mEvtStartIdx)) {
        dComIfGp_event_reset();

        if (m824 != 0) {
            m838 = 5;
        } else {
            m838 = 4;
        }
    } else if (dComIfGp_evmng_endCheck(mEvtGetItemIdx) || dComIfGp_evmng_endCheck(mEvtNoItemIdx) || dComIfGp_evmng_endCheck(mEvtEnd2Idx)) {
        dComIfGp_event_reset();
        dComIfGp_endMiniGame(5);
        fopAcM_delete((fopAc_ac_c*)mpTimer);
        dAuction_screen_delete();
    } else if (dComIfGp_evmng_endCheck(mEvtStart2Idx)) {
        dComIfGp_event_reset();
        m838 = 7;
    } else {
        bool attn = mNpcEvtInfo.getAttnFlag();
        if (mNpcEvtInfo.cutProc()) {
            if (!mNpcEvtInfo.getAttnFlag()) {
                mNpcEvtInfo.setAttnFlag(attn);
            }
        } else {
            privateCut();
        }
    }
}

/* 0000104C-00001300       .text privateCut__11daAuction_cFv */
void daAuction_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET",
        "MES_END",
        "START",
        "MAIN",
        "GET_ITEM",
        "CAMERA_OFF",
        "GET_ITEM_NPC",
        "GET_ITEM_MES",
        "CAMERA_OFF_NPC",
        "END",
        "CAMERA_TEST",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId("Auction");

    if (staffIdx == -1) {
        return;
    }

    mAction = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);

    if (mAction == -1) {
        dComIfGp_evmng_cutEnd(staffIdx);
        return;
    }

    if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
        switch (mAction) {
        case 0:
            eventTalkInit(staffIdx);
            break;
        case 2:
            eventStartInit();
            break;
        case 3:
            eventMainInit();
            break;
        case 4:
            eventGetItemInit();
            break;
        case 5:
            eventCameraOffInit();
            break;
        case 6:
            eventGetItemNpcInit(staffIdx);
            break;
        case 7:
            eventGetItemMesInit();
            break;
        case 9:
            eventEndInit();
            break;
        case 10:
            eventCameraTestInit();
            break;
        }
    }

    bool evtRes;
    switch (mAction) {
    case 0:
        evtRes = eventMesSet();
        break;
    case 1:
        evtRes = eventMesEnd();
        break;
    case 2:
        evtRes = eventStart();
        break;
    case 3:
        evtRes = eventMain();
        break;
    case 4:
        evtRes = eventGetItem();
        break;
    case 7:
        evtRes = false; // TODO: __ptmf_test
        break;
    case 8:
        evtRes = eventCameraOffNpc();
        break;
    case 9:
        evtRes = eventEnd();
        break;
    case 10:
        evtRes = eventCameraTest();
        break;
    default:
        evtRes = true;
    }

    if (evtRes) {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
    
    dCamera_c* pCam = dCam_getBody();

    // This could probably be simplified
    if (m835 & 1) {
        pCam->Stop();
        m835 &= ~1;
        m835 |= 4;
    }

    if (m835 & 2) {
        pCam->Start();
        m835 &= ~0xE;
    }

    if (m835 & 4 && m835 & 8) {
        pCam->Set(m78C, m798);
    }

}

/* 00001300-000013C0       .text eventTalkInit__11daAuction_cFi */
void daAuction_c::eventTalkInit(int staffIdx) {
    s32* pMsg = (s32*)dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");

    if (pMsg != NULL) {
        switch (*pMsg) {
        case 0x1CF4:
            mDoAud_seStart(JA_SE_AUC_ITEM_SHOW);
        default:
            setMessage(*pMsg);
        }
    } else {
        setMessage(0);
    }
}

/* 000013C0-00001400       .text eventMesSet__11daAuction_cFv */
bool daAuction_c::eventMesSet() {
    talk(0);

    return mCurrMsgBsPcId != fpcM_ERROR_PROCESS_ID_e;
}

/* 00001400-00001434       .text eventMesEnd__11daAuction_cFv */
bool daAuction_c::eventMesEnd() {
    return talk(0) == fopMsgStts_BOX_CLOSED_e;
}

/* 00001434-00001634       .text eventStartInit__11daAuction_cFv */
void daAuction_c::eventStartInit() {
    m820 = ~1;

    if (m822 == 2) {
        mTimerID = dTimer_createTimer(4, 0x1E, 1, 0, 221.0f, 439.0f, 32.0f, 419.0f);
    } else {
        mTimerID = dTimer_createTimer(4, 0x3C, 1, 0, 221.0f, 439.0f, 32.0f, 419.0f);
    }

    JUT_ASSERT(0x861, mTimerID != fpcM_ERROR_PROCESS_ID_e);

    mGaugeID = dAuction_screen_create();

    JUT_ASSERT(0x863, mGaugeID != fpcM_ERROR_PROCESS_ID_e);

    mpTimer = NULL;
    m830 = 1;

    dComIfGp_setMiniGameRupee(0);
    dComIfGp_setAuctionRupee(0);

    dAuction_screen_slotHide();
    dAuction_screen_gaugeHide();
    dAuction_screen_talkEnd();

    mCurrAuctionItemPID = fopAcM_create(PROC_ShopItem, l_item_dat[mCurrAuctionItemIndex].mItemID, &current.pos);
    dKy_custom_colset(0, 4, 1.0f);

    mLight.mPos.x = 0.0f;
    mLight.mPos.y = 50.0f;
    mLight.mPos.z = -200.0f;
    mLight.mColor.r = 0x96;
    mLight.mColor.g = 0x64;
    mLight.mColor.b = 0x3C;
    mLight.mPower = 450.0f;
    mLight.mFluctuation = 0.0f;

    dKy_efplight_set(&mLight);
    mFlags |= 4;

    dAuction_screen_talkEnd();
}

/* 00001634-000016AC       .text eventStart__11daAuction_cFv */
bool daAuction_c::eventStart() {
    if (mpTimer == NULL) {
        mpTimer = (dTimer_c*)fopMsgM_SearchByID(mTimerID);
        
        if (mpTimer != NULL) {
            mpTimer->mpScrnDraw->setShowType(0);
        }
    }

    dComIfGp_setDoStatusForce(0x3E);
    dComIfGp_setAStatusForce(0x3E);

    return mpTimer != NULL;
}

/* 000016AC-0000188C       .text eventMainInit__11daAuction_cFv */
void daAuction_c::eventMainInit() {
    m804 = 0xE10;

    for (int i = 0; i < 7; i++) {
        m7C4[i] = 0.0f;
    }

    if (m822 == 2) {
        m81F = 1;
    } else {
        m81F = 0;
    }

    m7E0 = 0.0f;
    m7E4 = 1.0f;
    m82A = 0;

    for (int i = 0; i < 3; i++) {
        s16 restMsgTime;
        if (m822 == 2) {
            restMsgTime = l_rest_msg_time2[i];
        } else {
            restMsgTime = l_rest_msg_time1[i];
        }

        if (60000 > restMsgTime) break;

        m82A += 1;
    }

    m82B = 0;
    m835 = 0;
    m834 = 0;
    m82E = 0;

    dComIfG_TimerStart(0, 4);

    if (m822 == 1) {
        dAuction_screen_gaugeShow();
    }

    m836 |= 1;

    daPy_py_c* pLink = (daPy_py_c*)dComIfGp_getLinkPlayer();

    pLink->changeOriginalDemo();
    mCurLinkAnm = 1;
    dComIfGp_event_setTalkPartner(this);
    m82F = 0;

    m78C = l_camera_pos[m82F][0];
    m798 = l_camera_pos[m82F][1];

    dAuction_screen_talkEnd();
}

static daAuction_c::ProcFunc_t eventProc[] = {
    daAuction_c::eventMainKai,
    daAuction_c::eventMainUri,
    daAuction_c::eventMainMsgSet,
    daAuction_c::eventMainMsgEnd,
    daAuction_c::eventMainMsgBikonC,
    daAuction_c::eventMainMsgBikonW,
};

/* 0000188C-00001A98       .text eventMain__11daAuction_cFv */
bool daAuction_c::eventMain() {
    daPy_lk_c* pLink = (daPy_lk_c*)dComIfGp_getLinkPlayer();

    if (pLink->getBaseAnimeFrameRate() == 0.0f && mCurLinkAnm != 1 && mCurLinkAnm != 0x1D && mCurLinkAnm != 0x25) {
        setLinkAnm(1);
    }

    mFlags &= 4;

    if (dComIfG_getTimerMode() == 4) {
        dComIfG_TimerStop(2);
    }

    (this->*eventProc[m81F])();

    if (m832 != 0) {
        pLink->setFace((daPy_py_c::daPy_FACE)mFace);
    }

    if (m822 == 1) {
        dComIfGp_setAuctionGauge((s16)m7C4[0]);
    }
    
    if (m81F <= 1 && m82B != 0) {
        dComIfGp_setNpcNameMessageID(l_npc_msg_dat[getAucMdlNo(m824)].field_0x00);

        if (dComIfG_getTimerMode() == 4) {
            dComIfG_TimerStop(2);
        }

        dAuction_screen_slotHide();
        dAuction_screen_gaugeHide();

        m82B = 1;
        m834 = 0;
        m836 |= 2;

        // Might be incorrect
        pLink->cancelOriginalDemo();

        if (m835 & 4) {
            m835 |= 2;
            m835 &= ~1;
        }

        mDoAud_seStart(JA_SE_AUC_END);

        return true;
    }

    return false;
}

/* 00001A98-000022A8       .text eventMainKai__11daAuction_cFv */
void daAuction_c::eventMainKai() {
    if (dComIfG_getTimerMode() == 4) {
        dComIfG_TimerReStart(2);
    }

    if (dComIfG_getTimerRestTimeMs() <= 0) {
        m82B = 1;
    } else {
        if (g_mDoCPd_cpadInfo[0].mButtonTrig.b) {
            setMessage2(0x1CFC);
            mDoAud_seStart(JA_SE_AUC_QUIT);
        } else {
            // I think this uses std::abs in kiosk build?
            m7E0 = m7E0 + m7E4;
            if (m7E0 >= 1.0f) {
                m7E0 = 1.0f;
                m7E4 = -1.0f;
            } else if (m7E0 <= -1.0f) {
                m7E0 = -1.0f;
                m7E4 = 1.0f;
            }

            if (m7C4[0] < 100.0f) {
                m7C4[0] += 0.02f;
            }

            if (g_mDoCPd_cpadInfo[0].mButtonTrig.a) {
                m7C4[0] += l_npc_dat[0].field_0x00 + cM_rndF(l_npc_dat[0].field_0x04 - l_npc_dat[0].field_0x00);

                mDoAud_seStart(JA_SE_AUC_BID_GAUGE, NULL, m7C4[0]);
            }

            if (m7C4[0] > 100.0f) {
                m7C4[0] = 100.0f;
            }

            if (m806 != 0) {
                m806 -= 1;

                if (m806 == 0) {
                    if (m834 & 2) {
                        m82F = getRand(3);
                        m78C = l_camera_pos[m82F][0];
                        m798 = l_camera_pos[m82F][1];
                    }

                    m834 &= ~6;
                }
            } else {
                for (int i = 1; i < 7; i++) {
                    m7C4[i] += cM_rndF(l_npc_dat[i].field_0x04 - l_npc_dat[i].field_0x00) + l_npc_dat[i].field_0x00;
                }
            }

            int idx;
            int end = 7;

            if ((m834 & 2)) {
                end = 1;
            }

            for (idx = 0; idx < end; idx++) {
                if (m7C4[idx] >= 100.0f && mCurrItemNameMsgNo < l_npc_dat[idx].field_0x0C) {
                    break;
                }
            }

            if (idx < end) {
                m828 = idx;

                s16 prevItemNameMsgNo = mCurrItemNameMsgNo;

                if (idx != 0) {
                    f32 f = 1.0f;
                    if (dComIfG_getTimerRestTimeMs() < 30000) {
                        f = 2.0f;
                    } else if (dComIfG_getTimerRestTimeMs() < 60000) {
                        f = 1.5f;
                    }

                    mCurrItemNameMsgNo += (s16)(f * (s16)(l_npc_dat[idx].field_0x08 + cM_rndF(l_npc_dat[idx].field_0x0A - l_npc_dat[idx].field_0x08)));
                    m800 = mCurrItemNameMsgNo;

                    end = 0x1CF9;

                    m82C = 4;
                    m7C4[idx] = 0.0f;

                    nextBet();
                } else {
                    m800 = mCurrItemNameMsgNo + 1;
                    dComIfGp_setMessageSetNumber(mCurrItemNameMsgNo + 1);
                    end = 0x1CFA;
                    setLinkAnm(0x48);
                    mpTimer->mpScrnDraw->setShowType(1);

                    dAuction_screen_gaugeUp();
                    dComIfGp_getVibration().StartShock(5, 1, cXyz(0.0f, 1.0f, 0.0f));
                    dComIfGp_getVibration().StartShock(4, 0x3E, cXyz(0.0f, 1.0f, 0.0f));
                }

                m806 = (cM_rndF(0.0f) + 1.0f) * 60.0f;
                m7F0 = end;
                m81F = 4;

                if (m830 != 0) {
                    m830 = 0;
                } else if (m826 != 0xFF && idx != 0 && dComIfG_getTimerRestTimeMs() > l_rest_msg_time1[0] && getRand(3) == 0) {
                    u32 msgParam;

                    if (mCurrItemNameMsgNo <= 0x64) {
                        msgParam = 0x1CFD;
                    } else if (mCurrItemNameMsgNo <= 0x96) {
                        msgParam = 0x1CFE;
                    } else if (mCurrItemNameMsgNo <= 0xC8) {
                        msgParam = 0x1CFF;
                    } else {
                        msgParam = 0x1D00;
                    }

                    // onCameraOld might be used somewhere here?
                    dComIfGp_setMessageCountNumber(prevItemNameMsgNo);
                    dComIfGp_setNpcNameMessageID(l_npc_msg_dat[getAucMdlNo(m824)].field_0x00);
                    setMessage2(msgParam);
                    setCameraNpc(m824, 0);
                    if (m824 == 0 && mCurLinkAnm != 0x1D) {
                        setLinkAnm(0x14);
                    }

                    m834 |= 0x20;
                    m829 = m827;
                    m830 = 1;
                }

                if (m81F == 4) {
                    u8 tmp = m828;
                    m829 = tmp;
                    m827 = tmp;
                    dComIfGp_setMessageCountNumber(m800);
                    dComIfGp_setNpcNameMessageID(l_npc_msg_dat[getAucMdlNo(m827)].field_0x00);
                }

                m835 |= 9;
                m835 &= ~2;
            } else if (dComIfG_getTimerRestTimeMs() < l_rest_msg_time1[m82A]) {
                setMessage2(l_rest_msg_no[m82A]);
                mDoAud_seStart(l_rest_se_no[m82A]);
                m82A += 1;
            }
        }
        if (m834 & 2) {
            m834 |= 4;
            m798.set(0.0f, 50.0f, -210.0f);
            m78C.set(getNpcActorP(0)->current.pos);

            m78C.x += cM_ssin(m808) * 256.0f;
            m78C.y += 100.0f;
            m808 += 200;
            mDoAud_seStart(JA_SE_CM_AUC_PARALYZED);
        }
    }

    dComIfGp_setDoStatusForce(0x25);
    dComIfGp_setAStatusForce(0x27);
}

/* 000022A8-00002760       .text eventMainUri__11daAuction_cFv */
void daAuction_c::eventMainUri() {
    if (dComIfG_getTimerMode() == 4) {
        dComIfG_TimerReStart(2);
    }

    if (dComIfG_getTimerRestTimeMs() <= 0) {
        m82B = 1;
    } else if (m82E != 0 && g_mDoCPd_cpadInfo[0].mButtonTrig.a) {
        setMessage2(0x1D1A);
    } else {
        if (m806 != 0) {
            m806 -= 1;
        } else {
            for (int i = 1; i < 7; i++) {
                m7C4[i] += 2.0f * RAND_RANGE(l_npc_dat[i].field_0x00, l_npc_dat[i].field_0x04);
            }
        }

        int idx;
        for (idx = 1; idx < 7; idx++) {
            if (m7C4[idx] >= 100.0f) {
                m7C4[idx] = 0.0f;
                if (mCurrItemNameMsgNo < l_npc_dat[idx].field_0x0C) {
                    break;
                }
            }
        }

        if (idx < 7) {
            m828 = idx;

            if (idx != 0) {
                float multiplier = 1.0f;

                if (dComIfG_getTimerRestTimeMs() < 30000) {
                    multiplier = 2.0f;
                } else if (dComIfG_getTimerRestTimeMs() < 60000) {
                    multiplier = 1.5f;
                }

                mCurrItemNameMsgNo += (s16)(multiplier * (2 * (s16)RAND_RANGE(l_npc_dat[idx].field_0x08, l_npc_dat[idx].field_0x0A)));
                m800 = mCurrItemNameMsgNo;
                m7F0 = 0x1CF9;
                m82C = 4;
                m82E = 1;
                m806 = cM_rndF(1.0) * 60.0f;
                m81F = 4;

                // onCameraOld might be used here
                if (m830 != 0) {
                    m830 = 0;
                } else if (dComIfG_getTimerRestTimeMs() > l_rest_msg_time1[0] && getRand(3) == 0) {
                    u32 msgParam;

                    if (mCurrItemNameMsgNo <= 0x64) {
                        msgParam = 0x1CFD;
                    } else if (mCurrItemNameMsgNo <= 0x96) {
                        msgParam = 0x1CFE;
                    } else if (mCurrItemNameMsgNo <= 0xC8) {
                        msgParam = 0x1CFF;
                    } else {
                        msgParam = 0x1D00;
                    }

                    dComIfGp_setNpcNameMessageID(l_npc_msg_dat[getAucMdlNo(m824)].field_0x00);
                    setMessage2(msgParam);
                    setCameraNpc(m824, 0);

                    if (m824 == 0) {
                        setLinkAnm(0x14);
                    }

                    m834 |= 0x20;
                    m829 = m827;
                    m830 = 1;
                }

                if (m81F == 4) {
                    u8 m828_val = m828;
                    m829 = m828_val;
                    m827 = m828_val;
                    dComIfGp_setMessageCountNumber(m800);
                    dComIfGp_setNpcNameMessageID(l_npc_msg_dat[getAucMdlNo(m827)].field_0x00);
                }

                m835 |= 9;
                m835 &= ~2;
            }
        } else if (dComIfG_getTimerRestTimeMs() < l_rest_msg_time2[m82A]) {
            setMessage2(l_rest_msg_no[m82A]);
            mDoAud_seStart(l_rest_se_no[m82A]);
            m82A += 1;
        }
    }

    if (m82E != 0) {
        dComIfGp_setDoStatusForce(0x25);
    }
}

/* 00002760-0000279C       .text eventMainMsgSet__11daAuction_cFv */
void daAuction_c::eventMainMsgSet() {
    if (eventMesSet()) {
        m81F = 3;
    }
}

/* 0000279C-0000294C       .text eventMainMsgEnd__11daAuction_cFv */
void daAuction_c::eventMainMsgEnd() {
    if (eventMesEnd()) {
        if (mCurLinkAnm != 1 && mCurLinkAnm != 0x1D) {
            setLinkAnm(1);
        }

        if (m834 & 0x20) {
            m81F = 4;
        } else {
            if (m822 == 2) {
                m81F = 1;
            } else {
                m81F = 0;
            }

            eyePos = current.pos;
            m832 = 0;
        }

        m7E0 = 0.0f;

        if ((m834 & 2) == 0) {
            m82F = getRand(3);
            m78C = l_camera_pos[m82F][0];
            m798 = l_camera_pos[m82F][1];
        }

        mpTimer->mpScrnDraw->setShowType(0);
        dAuction_screen_gaugeDown();
        m834 &= ~0x29;
        dAuction_screen_talkEnd();
        dAuction_screen_gaugeShow();

        return;
    }

    if (dComIfGp_checkMesgSendButton() && ((m7EC >= 0x1D3AU && m7EC <= 0x1D4BU) || (m7EC >= 0x339DU && m7EC <= 0x33A8U))) {
        setCameraNpc(m825, 0);
        m834 |= 8;
        m829 = m825;
    }
}

/* 0000294C-00002B90       .text eventMainMsgBikonC__11daAuction_cFv */
void daAuction_c::eventMainMsgBikonC() {
    m827 = m829 = m828;
    dComIfGp_setMessageCountNumber(m800);
    dComIfGp_setNpcNameMessageID(l_npc_msg_dat[getAucMdlNo(m827)].field_0x00);

    cXyz npcPos = getNpcActorP(m827)->current.pos;
    npcPos.y += getPiconDispOfs(m827) + 30.0f;

    if (cLib_addCalcPos(&m78C, npcPos, 0.4f, 700.0f, 0.1f) == 0.0f) {
        m81F = 5;
        m7A8 = getNpcActorP(m827)->current.pos;
        m7A8.y += getPiconDispOfs(m827);

        dComIfGp_particle_set(0x8153, &m7A8, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this));
        mTimer = 0x1E;

        if (m827 == 0) {
            mDoAud_seStart(JA_SE_AUC_BID_GAUGE_MAX);
        } else {
            mDoAud_seStart(JA_SE_CM_AUC_CALL_BID);
            m832 = 1;
            mFace = l_link_face[getRand(8)];
        }

        eyePos = getNpcActorP(m827)->eyePos;
    }

    dComIfGp_setDoStatusForce(0);
    dComIfGp_setAStatusForce(0x3E);
}

/* 00002B90-00002C1C       .text eventMainMsgBikonW__11daAuction_cFv */
void daAuction_c::eventMainMsgBikonW() {
    if (mTimer != 0) {
        mTimer -= 1;
    } else {
        setMessage2(m7F0);
        setCameraNpc(m827, 0);
        dAuction_screen_talkStart();

        if (m827 != 0) {
            m834 |= 1;
        }
    }

    dComIfGp_setDoStatusForce(0);
    dComIfGp_setAStatusForce(0x3E);
}

/* 00002C1C-00002D4C       .text eventGetItemInit__11daAuction_cFv */
void daAuction_c::eventGetItemInit() {
    if (m822 == 2) {
        uint itemID = fopAcM_createItemForPresentDemo(&current.pos, l_item_dat22[mCurrAuctionItemIndex] & 0xFF);

        if (itemID != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(itemID);
        }

        dComIfGs_onEventBit(l_item_dat2[mCurrAuctionItemIndex].mObtainedEventBit);
    } else {
        uint itemID = fopAcM_createItemForPresentDemo(&current.pos, l_item_dat[mCurrAuctionItemIndex].mItemID & 0xFF);

        if (itemID != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(itemID);
        }

        dComIfGs_onEventBit(l_item_dat[mCurrAuctionItemIndex].mObtainedEventBit);
    }

    setCameraNpc(0, 0);
}

/* 00002D4C-00002D54       .text eventGetItem__11daAuction_cFv */
bool daAuction_c::eventGetItem() {
    return true;
}

/* 00002D54-00002D70       .text eventCameraOffInit__11daAuction_cFv */
void daAuction_c::eventCameraOffInit() {
    offCamera();
}

/* 00002D70-00002E00       .text eventGetItemNpcInit__11daAuction_cFi */
void daAuction_c::eventGetItemNpcInit(int staffIdx) {
    setCameraNpc(m824, 0);

    u32* pTimerData = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");

    if (pTimerData != NULL) {
        mTimer = *pTimerData;
    } else {
        mTimer = 0;
    }

    m834 = 0x10;
    m829 = m824;
}

/* 00002E00-00002E40       .text eventGetItemMesInit__11daAuction_cFv */
void daAuction_c::eventGetItemMesInit() {
    setMessage(l_npc_msg_dat[getAucMdlNo(m824)].field_0x08);
}

/* 00002E40-00002EA0       .text eventCameraOffNpc__11daAuction_cFv */
bool daAuction_c::eventCameraOffNpc() {
    if (eventMesEnd()) {
        m834 = 0;
        offCamera();
        return true;
    }

    return false;
}

/* 00002EA0-00002EDC       .text eventEndInit__11daAuction_cFv */
void daAuction_c::eventEndInit() {
    mBlend = 0.0f;
    mFlags &= ~4;

    dKy_efplight_cut(&mLight);
}

/* 00002EDC-00002F60       .text eventEnd__11daAuction_cFv */
bool daAuction_c::eventEnd() {
    mBlend += 0.05f;
    if (mBlend > 1.0f) {
        mBlend = 1.0f;
    }

    dKy_custom_colset(4, 0, mBlend);

    // "return mBlend == 1.0f" doesn't match for some reason
    return mBlend == 1.0f ? true : false;
}

/* 00002F60-00002F64       .text eventCameraTestInit__11daAuction_cFv */
void daAuction_c::eventCameraTestInit() {
    /* Nonmatching */
}

/* 00002F64-00002F6C       .text eventCameraTest__11daAuction_cFv */
bool daAuction_c::eventCameraTest() {
    return true;
}

/* 00002F6C-0000369C       .text next_msgStatus__11daAuction_cFPUl */
u16 daAuction_c::next_msgStatus(u32* pMsgNo) {
    /* Nonmatching */
}

/* 0000369C-000036AC       .text setMessage__11daAuction_cFUl */
void daAuction_c::setMessage(u32 msg) {
    mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
    mCurrMsgNo = msg;
}

/* 000036AC-000036E4       .text setMessage2__11daAuction_cFUl */
void daAuction_c::setMessage2(u32 msg) {
    setMessage(msg);
    m81F = 2;
    dAuction_screen_gaugeHide();
}

/* 000036E4-00003754       .text setMtx__11daAuction_cFv */
void daAuction_c::setMtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00003754-00003828       .text getItemNo__11daAuction_cFv */
u8 daAuction_c::getItemNo() {
    int i;
    int rand_max = 0;

    for (i = 0; i < 4; i++) {
        if (!dComIfGs_isEventBit(l_item_dat[i].mObtainedEventBit)) {
            rand_max += 1;
        }
    }

    int rand = getRand(rand_max);

    for (i = 0; i < 3; i++) {
        if (!dComIfGs_isEventBit(l_item_dat[i].mObtainedEventBit)) {
            if (rand == 0) break;

            rand -= 1;
        }
    }

    return i;
}

/* 00003828-0000387C       .text getNpcActorP__11daAuction_cFi */
fopAc_ac_c* daAuction_c::getNpcActorP(int idx) {
    if (idx != 0) {
        return fopAcM_SearchByID(m738[idx]);
    }

    return dComIfGp_getPlayer(0);
}

/* 0000387C-000039FC       .text setCameraNpc__11daAuction_cFis */
void daAuction_c::setCameraNpc(int, short) {
    /* Nonmatching */
}

/* 000039FC-00003A3C       .text setLinkAnm__11daAuction_cFUc */
void daAuction_c::setLinkAnm(u8 linkAnm) {
    if (linkAnm == 1 && m826 == 0) {
        linkAnm = 0x1D;
    }

    daPy_lk_c* pLink = (daPy_lk_c*)dComIfGp_getLinkPlayer();

    pLink->changeDemoMode(linkAnm);
    pLink->changeDemoParam0(3);
    mCurLinkAnm = linkAnm;
}

/* 00003A3C-00003A74       .text getPiconDispOfs__11daAuction_cFUc */
f32 daAuction_c::getPiconDispOfs(u8 param) {
    if (param == 0) {
        return l_npc_emitter_ofsy[0];
    }

    daNpcAuction_c* pNpcActor = (daNpcAuction_c*)getNpcActorP(param);
    return pNpcActor->getPiconOfsY();
}

/* 00003A74-00003BA4       .text nextBet__11daAuction_cFv */
void daAuction_c::nextBet() {
    /* Nonmatching */
}

/* 00003BA4-00003C08       .text getRand__11daAuction_cFi */
int daAuction_c::getRand(int max) {
    int rnd = (int)cM_rndF(max);

    if (rnd == max) {
        rnd = 0;
    }

    return rnd;
}

/* 00003C08-00003C28       .text daAuctionCreate__FPv */
static s32 daAuctionCreate(void* i_this) {
    return static_cast<daAuction_c*>(i_this)->_create();
}

/* 00003C28-00003C48       .text daAuctionDelete__FPv */
static BOOL daAuctionDelete(void* i_this) {
    return static_cast<daAuction_c*>(i_this)->_delete();
}

/* 00003C48-00003C68       .text daAuctionExecute__FPv */
static BOOL daAuctionExecute(void* i_this) {
    return static_cast<daAuction_c*>(i_this)->_execute();
}

/* 00003C68-00003C88       .text daAuctionDraw__FPv */
static BOOL daAuctionDraw(void* i_this) {
    return static_cast<daAuction_c*>(i_this)->_draw();
}

/* 00003C88-00003C90       .text daAuctionIsDelete__FPv */
static BOOL daAuctionIsDelete(void*) {
    return TRUE;
}

static actor_method_class daAuctionMethodTable = {
    (process_method_func)daAuctionCreate,
    (process_method_func)daAuctionDelete,
    (process_method_func)daAuctionExecute,
    (process_method_func)daAuctionIsDelete,
    (process_method_func)daAuctionDraw,
};

actor_process_profile_definition g_profile_AUCTION = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_AUCTION,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daAuction_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x01E0,
    /* Actor SubMtd */ &daAuctionMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};

#undef RAND_RANGE
