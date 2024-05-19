//
// Generated by dtk
// Translation Unit: d_a_auction.cpp
//

#include "d/actor/d_a_auction.h"
#include "d/d_procname.h"
#include "d/res/res_auction.h"
#include "d/d_camera.h"

/* Structs are almost definitely not accurate */
struct NpcDatStruct {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ s32 field_0x04;
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
static cXyz l_camera_pos[6] = {
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
static char l_item_dat22[] = {0x00, 0x2A, 0x00, 0xF9};

static NpcDatStruct l_npc_dat[7] = {
    NULL,
};

static NpcMsgDatStruct l_npc_msg_dat[12] = {
    NULL,
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
extern void dAuction_screen_talkEnd();
extern uint dAuction_screen_create();

/* 000000EC-000002FC       .text __ct__11daAuction_cFv */
daAuction_c::daAuction_c() {
    // TODO: Refactor this
    for (int i = 0; i < 8; i++) {
        m738[i] = -1;
        m80C[i] = i;
        m814[i] = 0xFF;
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
    dComIfGp_setNpcNameMessageID(l_npc_msg_dat[m814[m824]].field_0x00);

    mCurrAuctionItemIndex = 0;

    dComIfGp_setItemNameMessageID(l_item_dat[mCurrAuctionItemIndex].mItemID);
    mCurrItemNameMsgNo = l_item_dat[mCurrAuctionItemIndex].mNameMsgID;

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

        dComIfGp_setItemNameMessageID(l_item_dat[mCurrAuctionItemIndex].mItemID);
        mCurrItemNameMsgNo = l_item_dat[mCurrAuctionItemIndex].mNameMsgID;
        dComIfGp_setMessageCountNumber(mCurrItemNameMsgNo);

        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), mEvtStartIdx, 0, 0xFF7F);
        dComIfGp_startMiniGame(5);
    } else if (m838 == 4) {
        fopAcM_orderOtherEventId(this, mEvtGetItemIdx, 0xFF, 0xFF7F);
    } else if (m838 == 5) {
        fopAcM_orderOtherEventId(this, mEvtNoItemIdx, 0xFF, 0xFF7F);
    } else if (m838 == 6) {
        mCurrAuctionItemIndex &= 1;
        mCurrItemNameMsgNo = l_item_dat2[mCurrAuctionItemIndex].mNameMsgID;
        dComIfGp_setItemNameMessageID(l_item_dat2[mCurrAuctionItemIndex].mItemID);
        dComIfGp_setMessageCountNumber(mCurrItemNameMsgNo);
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), mEvtStart2Idx, 0, 0xFF7F);
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
    /* Nonmatching */
}

/* 000016AC-0000188C       .text eventMainInit__11daAuction_cFv */
void daAuction_c::eventMainInit() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 00001A98-000022A8       .text eventMainKai__11daAuction_cFv */
void daAuction_c::eventMainKai() {
    /* Nonmatching */
}

/* 000022A8-00002760       .text eventMainUri__11daAuction_cFv */
void daAuction_c::eventMainUri() {
    /* Nonmatching */
}

/* 00002760-0000279C       .text eventMainMsgSet__11daAuction_cFv */
void daAuction_c::eventMainMsgSet() {
    /* Nonmatching */
}

/* 0000279C-0000294C       .text eventMainMsgEnd__11daAuction_cFv */
void daAuction_c::eventMainMsgEnd() {
    /* Nonmatching */
}

/* 0000294C-00002B90       .text eventMainMsgBikonC__11daAuction_cFv */
void daAuction_c::eventMainMsgBikonC() {
    /* Nonmatching */
}

/* 00002B90-00002C1C       .text eventMainMsgBikonW__11daAuction_cFv */
void daAuction_c::eventMainMsgBikonW() {
    /* Nonmatching */
}

/* 00002C1C-00002D4C       .text eventGetItemInit__11daAuction_cFv */
void daAuction_c::eventGetItemInit() {
    /* Nonmatching */
}

/* 00002D4C-00002D54       .text eventGetItem__11daAuction_cFv */
bool daAuction_c::eventGetItem() {
    /* Nonmatching */
}

/* 00002D54-00002D70       .text eventCameraOffInit__11daAuction_cFv */
void daAuction_c::eventCameraOffInit() {
    /* Nonmatching */
}

/* 00002D70-00002E00       .text eventGetItemNpcInit__11daAuction_cFi */
void daAuction_c::eventGetItemNpcInit(int) {
    /* Nonmatching */
}

/* 00002E00-00002E40       .text eventGetItemMesInit__11daAuction_cFv */
void daAuction_c::eventGetItemMesInit() {
    /* Nonmatching */
}

/* 00002E40-00002EA0       .text eventCameraOffNpc__11daAuction_cFv */
bool daAuction_c::eventCameraOffNpc() {
    /* Nonmatching */
}

/* 00002EA0-00002EDC       .text eventEndInit__11daAuction_cFv */
void daAuction_c::eventEndInit() {
    /* Nonmatching */
}

/* 00002EDC-00002F60       .text eventEnd__11daAuction_cFv */
bool daAuction_c::eventEnd() {
    /* Nonmatching */
}

/* 00002F60-00002F64       .text eventCameraTestInit__11daAuction_cFv */
void daAuction_c::eventCameraTestInit() {
    /* Nonmatching */
}

/* 00002F64-00002F6C       .text eventCameraTest__11daAuction_cFv */
bool daAuction_c::eventCameraTest() {
    /* Nonmatching */
}

/* 00002F6C-0000369C       .text next_msgStatus__11daAuction_cFPUl */
u16 daAuction_c::next_msgStatus(u32* pMsgNo) {
    /* Nonmatching */
}

/* 0000369C-000036AC       .text setMessage__11daAuction_cFUl */
void daAuction_c::setMessage(unsigned long) {
    /* Nonmatching */
}

/* 000036AC-000036E4       .text setMessage2__11daAuction_cFUl */
void daAuction_c::setMessage2(unsigned long) {
    /* Nonmatching */
}

/* 000036E4-00003754       .text setMtx__11daAuction_cFv */
void daAuction_c::setMtx() {
    /* Nonmatching */
}

/* 00003754-00003828       .text getItemNo__11daAuction_cFv */
u8 daAuction_c::getItemNo() {
    /* Nonmatching */
}

/* 00003828-0000387C       .text getNpcActorP__11daAuction_cFi */
void daAuction_c::getNpcActorP(int) {
    /* Nonmatching */
}

/* 0000387C-000039FC       .text setCameraNpc__11daAuction_cFis */
void daAuction_c::setCameraNpc(int, short) {
    /* Nonmatching */
}

/* 000039FC-00003A3C       .text setLinkAnm__11daAuction_cFUc */
void daAuction_c::setLinkAnm(unsigned char) {
    /* Nonmatching */
}

/* 00003A3C-00003A74       .text getPiconDispOfs__11daAuction_cFUc */
void daAuction_c::getPiconDispOfs(unsigned char) {
    /* Nonmatching */
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
