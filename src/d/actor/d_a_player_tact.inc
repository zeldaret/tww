/**
 * d_a_player_tact.inc
 *
 * Code relating to the Wind Waker item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "f_op/f_op_camera.h"
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"
#include "d/d_procname.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_player_HIO.h"
#include "JSystem/JKernel/JKRHeap.h"

extern const Vec l_tact_top;

/* 8014D778-8014D7D4       .text getDayNightParamData__9daPy_lk_cFv */
u32 daPy_lk_c::getDayNightParamData() {
    u32 spawnType = dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) ? 2 : 0;
    u32 eventIdx = 0xCC;
    u32 extraParams = dComIfGp_getShipActor() != NULL ? 0x140 : 0x40;
    return setParamData(current.roomNo, spawnType, eventIdx, extraParams);
}

/* 8014D7D4-8014D8AC       .text setTactModel__9daPy_lk_cFv */
void daPy_lk_c::setTactModel() {
    if (mEquipItem == dItem_WIND_WAKER_e)
        return;
    
    deleteEquipItem(FALSE);
    mEquipItem = dItem_WIND_WAKER_e;
    JKRHeap* oldHeap = setItemHeap();
    
    J3DModelData* modelData = initModel(&mpEquipItemModel, LINK_BDL_TAKT, 0x37221222);
    u8* buffer = new(0x20) u8[0x400];
    dComIfGp_getAnmArchive()->readIdxResource(buffer, 0x400, LKANM_BRK_TTAKT);
    mpEquipItemBrk = (J3DAnmTevRegKey*)J3DAnmLoaderDataBase::load(buffer);
    mpEquipItemBrk->setFrame(0.0f);
    mpEquipItemBrk->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpEquipItemBrk);
    
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8014D8AC-8014D8F4       .text checkNpcStatus__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNpcStatus() {
    daPy_py_c* partner = (daPy_py_c*)dComIfGp_getCb1Player();
    if (partner) {
        if (!partner->checkNpcNotChange() && partner->current.roomNo == current.roomNo) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 8014D8F4-8014D938       .text getTactPlayRightArmAnm__9daPy_lk_cFl */
u16 daPy_lk_c::getTactPlayRightArmAnm(s32 r4) {
    if (r4 == 1)
        return LKANM_BCK_ACTIONTAKTRUP;
    else if (r4 == 3)
        return LKANM_BCK_ACTIONTAKTRDW;
    else if (r4 == 2)
        return LKANM_BCK_WAITTAKTRHANDL;
    else if (r4 == 4)
        return LKANM_BCK_WAITTAKTRHANDR;
    else
        return LKANM_BCK_WAITTAKT;
}

/* 8014D938-8014D97C       .text getTactPlayLeftArmAnm__9daPy_lk_cFl */
u16 daPy_lk_c::getTactPlayLeftArmAnm(s32 r4) {
    if (r4 == 1)
        return LKANM_BCK_WAITTAKTLHANDU;
    else if (r4 == 3)
        return LKANM_BCK_WAITTAKTLHANDD;
    else if (r4 == 2)
        return LKANM_BCK_WAITTAKTLHANDL;
    else if (r4 == 4)
        return LKANM_BCK_WAITTAKTLHANDR;
    else
        return LKANM_BCK_WAITTAKT;
}

/* 8014D97C-8014D9A4       .text checkEndTactMusic__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkEndTactMusic() const {
    if (mCurProc == daPyProc_TACT_PLAY_e && m34D0 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* 8014D9A4-8014D9D0       .text getTactMetronomeRate__9daPy_lk_cFv */
f32 daPy_lk_c::getTactMetronomeRate() {
    if (mCurProc == daPyProc_TACT_WAIT_e) {
        return m35A0 / mDoAud_zelAudio_c::getTact().field_0x30;
    } else {
        return -1.0f;
    }
}

/* 8014D9D0-8014D9F8       .text checkTactLastInput__9daPy_lk_cFv */
BOOL daPy_lk_c::checkTactLastInput() {
    if (mCurProc == daPyProc_TACT_WAIT_e && m34D2 != -1) {
        return TRUE;
    }
    return FALSE;
}

/* 8014D9F8-8014DA78       .text setTactZev__9daPy_lk_cFUiiPc */
void daPy_lk_c::setTactZev(uint tactZevPartnerPID, int r30, char* r31) {
    if (tactZevPartnerPID != fpcM_ERROR_PROCESS_ID_e) {
        mDoAud_seStart(JA_SE_PRE_TAKT);
    }
    mTactZevPartnerPID = tactZevPartnerPID;
    m34CC = r30;
    m3494 = r31;
}

/* 8014DA78-8014DACC       .text getTactTopPos__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::getTactTopPos(cXyz* out) {
    if (mEquipItem != dItem_WIND_WAKER_e || mpEquipItemModel == NULL) {
        return FALSE;
    } else {
        MTXMultVec(mpEquipItemModel->getBaseTRMtx(), &l_tact_top, out);
        return TRUE;
    }
}

/* 8014DACC-8014DB00       .text getTactNormalWait__9daPy_lk_cCFv */
BOOL daPy_lk_c::getTactNormalWait() const {
    if (mCurProc == daPyProc_TACT_WAIT_e && m3570 == -1 && m34D2 == -1) {
        return TRUE;
    }
    return FALSE;
}

/* 8014DB00-8014DB2C       .text getTactMusic__9daPy_lk_cCFv */
s32 daPy_lk_c::getTactMusic() const {
    if (mCurProc == daPyProc_TACT_PLAY_e)
        return m3570;
    if (mCurProc == daPyProc_TACT_WAIT_e)
        return m3574;
    return -1;
}

/* 8014DB2C-8014DB74       .text getTactTimerCancel__9daPy_lk_cCFv */
int daPy_lk_c::getTactTimerCancel() const {
    if (mCurProc == daPyProc_TACT_WAIT_e && m35AC <= 0.0f) {
        if (m35AC <= -100.0f) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}

/* 8014DB74-8014DB9C       .text checkTactPlayMelody__9daPy_lk_cFv */
BOOL daPy_lk_c::checkTactPlayMelody() {
    if (mCurProc == daPyProc_TACT_PLAY_e && m34DA == 0) {
        return TRUE;
    }
    return FALSE;
}

/* 8014DB9C-8014DBEC       .text resetTactCount__9daPy_lk_cFv */
void daPy_lk_c::resetTactCount() {
    if (mCurProc == daPyProc_TACT_WAIT_e) {
        m34D8 = 0;
        m35A0 = 0.0f;
        m34DA = 0;
        m34D0 = -1;
        mDoAud_tact_reset();
    }
}

/* 8014DBEC-8014E100       .text procTactWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procTactWait_init(int r30) {
    if (mCurProc == daPyProc_TACT_WAIT_e) {
        if (m3570 != r30) {
            m34D8 = 0;
            m34DA = 0;
            m34D2 = -1;
        }
        m3570 = r30;
        if (m3570 != -4) {
            g_dComIfG_gameInfo.play.field_0x4947 = 1;
        } else {
            g_dComIfG_gameInfo.play.field_0x4947 = 0;
        }
        return TRUE;
    } else if (r30 == -1) {
        if (!dComIfGp_event_compulsory(this, NULL, -1)) {
            return FALSE;
        }
        mDemo.setDemoType(5);
    }
    
    int r31 = checkShipRideUseItem(1);
    if (r31 == 0) {
        if (r30 == -1) {
            f32 f31 = 200.0f * cM_ssin(shape_angle.y);
            f32 f30 = 200.0f * cM_scos(shape_angle.y);
            cXyz startPos(
                attention_info.position.x,
                attention_info.position.y - 50.0f,
                attention_info.position.z
            );
            cXyz endPos(
                startPos.x + f31,
                startPos.y,
                startPos.z + f30
            );
            mLinkLinChk.Set(&startPos, &endPos, this);
            if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                endPos.x = startPos.x - f31;
                endPos.z = startPos.z - f30;
                mLinkLinChk.Set(&startPos, &endPos, this);
                if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                    shape_angle.y += 0x8000;
                } else {
                    endPos.x = startPos.x + f30;
                    endPos.z = startPos.z - f31;
                    mLinkLinChk.Set(&startPos, &endPos, this);
                    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        shape_angle.y += 0x4000;
                    } else {
                        endPos.x = startPos.x - f30;
                        endPos.z = startPos.z + f31;
                        mLinkLinChk.Set(&startPos, &endPos, this);
                        if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                            shape_angle.y -= 0x4000;
                        }
                    }
                }
                current.angle.y = shape_angle.y;
            }
        } else if (r30 == -4 || r30 == -5) {
            if (fopAcM_getTalkEventPartner(this)) {
                shape_angle.y = fopAcM_searchActorAngleY(this, fopAcM_getTalkEventPartner(this));
            }
        }
    }
    
    commonProcInit(daPyProc_TACT_WAIT_e);
    daPy_matAnm_c::offMabaFlg();
    daPy_matAnm_c::setMabaTimer(1);
    setSingleMoveAnime(ANM_WAITTAKT, daPy_HIO_tact_c0::m.field_0x0, 0.0f, -1, daPy_HIO_tact_c0::m.field_0x4);
    setActAnimeUpper(LKANM_BCK_WAITTAKT, UPPER_MOVE1_e, daPy_HIO_tact_c0::m.field_0x0, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);
    setActAnimeUpper(LKANM_BCK_WAITTAKT, UPPER_MOVE2_e, daPy_HIO_tact_c0::m.field_0x0, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE2_e].setRatio(0.0f);
    mVelocity = 0.0f;
    m34D4 = 0;
    m34D6 = 0;
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);
    
    if (r30 == -1) {
        dCam_getBody()->StartEventCamera(0xC, fopAcM_GetID(this), 0);
        mDoAud_seStart(JA_SE_TAKT_USE_BEGIN);
    }
    
    mDoAud_tact_reset();
    mDoAud_tact_setBeat(0);
    mDoAud_tact_setVolume(0.0f);
    mDoAud_tact_ambientPlay();
    
    setTactModel();
    initShipRideUseItem(r31, 2);
    
    m34D2 = -1;
    m32E4.makeEmitter(0x50, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    m3570 = r30;
    m34D8 = 0;
    m3574 = -1;
    m35A0 = 0.0f;
    m34DA = 0;
    m3624 = 0;
    m35A4 = 0.0f;
    m35A8 = 0.0f;
    if (m3570 == 6 || m3570 == 7) {
        m35AC = 600.0f;
    } else {
        m35AC = 900.0f;
    }
    m34D0 = -1;
    setTactZev(-1, -1, NULL);
    
    if (m3570 != -4) {
        g_dComIfG_gameInfo.play.field_0x4947 = 1;
    }
    mDoAud_taktModeMute();
    
    return TRUE;
}

/* 8014E100-8014E9A4       .text procTactWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactWait() {
    /* Nonmatching */
}

/* 8014E9A4-8014EBA0       .text procTactPlay_init__9daPy_lk_cFlii */
BOOL daPy_lk_c::procTactPlay_init(s32 r27, int r30, int r31) {
    int r28 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_TACT_PLAY_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);
    m3570 = r27;
    if (r31 == 0) {
        m3628 = fopMsgM_messageSet(0x5AD + r27);
    } else {
        m3628 = fpcM_ERROR_PROCESS_ID_e;
    }
    mDoAud_tact_setVolume(0.0f);
    resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
    resetActAnimeUpper(UPPER_MOVE1_e, -1.0f);
    m34DA = 0xA;
    
    daPy_ANM anm;
    if (r27 == 0) {
        anm = ANM_TAKTKAZE;
    } else if (r27 == 1) {
        anm = ANM_TAKTSIPPU;
    } else if (r27 == 5) {
        anm = ANM_TAKTCHUYA;
    } else if (r27 == 4) {
        anm = ANM_TAKTFUJIN;
    } else if (r27 == 2) {
        anm = ANM_TAKTAYATSURI;
    } else {
        anm = ANM_TAKTCHISIN;
    }
    setSingleMoveAnime(anm, 1.0f, 0.0f, -1, 3.0f);
    
    initShipRideUseItem(r28, 2);
    
    if (r28 != 0 && m3570 == 1) {
        stage_stag_info_class* stag_info = dComIfGp_getStageStagInfo();
        if (dStage_stagInfo_GetSTType(stag_info) == dStageType_SEA_e && m34CC != 1 && r30 != 0) {
            daShip_c* ship = dComIfGp_getShipActor();
            uint warpID = fopAcM_create(PROC_TORNADO, 1, &current.pos, current.roomNo);
            ship->setTactWarpID(warpID);
        }
    }
    
    m32E4.makeEmitter(0x51, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    m34D0 = 0;
    m3574 = r30;
    m3624 = 0;
    m34D8 = r31;
    
    return TRUE;
}

/* 8014EBA0-8014EFD4       .text procTactPlay__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlay() {
    /* Nonmatching */
}

/* 8014EFD4-8014F210       .text procTactPlayEnd_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procTactPlayEnd_init(int r30) {
    int r28 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_TACT_PLAY_END_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);
    initShipRideUseItem(r28, 2);
    m3570 = r30;
    mVelocity = 0.0f;
    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    
    if (r30 == -1) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        fopAcM_orderChangeEvent(this, fopAcM_SearchByID(mTactZevPartnerPID), m3494, 0, -1);
        mDemo.setDemoType(2);
    } else if (r30 == 0) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        fopAcM_create(PROC_WBIRD, NULL, &current.pos, dComIfGp_roomControl_getStayNo());
    } else if (r30 == 2) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        dComIfGp_event_setTalkPartner(dComIfGp_getCb1Player());
        fopAcM_orderChangeEvent(this, dComIfGp_getCb1Player(), l_tact_event_label, 0, -1);
        mDoAud_seStart(JA_SE_CTRL_LINK_TO_NPC, 0);
    } else if (r30 == 5) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        fopAcM_orderChangeEvent(this, l_tact_night_event_label, 0, -1);
    }
    
    m3574 = 0;
    m34D6 = shape_angle.y + 0x4000;
    
    return TRUE;
}

/* 8014F210-8014F4DC       .text procTactPlayEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayEnd() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts1_UNK10000_e)) {
        setShipRidePos(0);
        if (m3570 == 0 && !dComIfGp_evmng_startCheck(l_tact_wind_change_event_label) && !dComIfGp_evmng_startCheck(l_tact_wind_change_event_label2)) {
            cLib_addCalcAngleS(&shape_angle.y, m34D6, 5, 0x1000, 0x100);
        }
    }
    
    if (m3570 == 0) {
        dComIfGp_setAStatus(0x07);
    } else if (m3570 == 5) {
        if (dComIfGp_evmng_endCheck(l_tact_night_event_label) && !checkNoResetFlg0(daPyFlg0_UNK4000)) {
            onNoResetFlg0(daPyFlg0_UNK4000);
            fopAc_ac_c* ship;
            BOOL hasShip;
            if (dComIfGp_getShipActor() != NULL) {
                ship = dComIfGp_getShipActor();
                hasShip = TRUE;
            } else {
                ship = this; // Use Link's position and angle for the ship if it doesn't exist.
                hasShip = FALSE;
            }
            dComIfGs_setTurnRestart(
                current.pos, shape_angle.y, fopAcM_GetRoomNo(this), getDayNightParamData(),
                ship->current.pos, ship->shape_angle.y, hasShip
            );
            if (dComIfG_getTimerMode() == 3 && dComIfG_getTimerPtr() != NULL) {
                dComIfG_getTimerPtr()->deleteRequest();
            }
            dStage_turnRestart();
            mDoAud_taktModeMuteOff();
        }
    } else if (m3570 == 2) {
        if (dComIfGp_evmng_endCheck(l_tact_event_label)) {
            dComIfGp_event_reset();
            changePlayer(dComIfGp_getCb1Player());
            endDemoMode();
        }
    } else if (m3570 == 1) {
        if (m3574 == 0) {
            if (dComIfGp_getMesgStatus() == 0) {
                dComIfGp_fmapOpenOn();
                m3574 = 1;
            }
        } else {
            dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
            daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
            if (ship == NULL || ship->getTactWarpPosNum() < 0) {
                dComIfGp_event_reset();
                endDemoMode();
                if (ship != NULL) {
                    fopAcM_delete(ship->getTactWarpID());
                    ship->setTactWarpID(fpcM_ERROR_PROCESS_ID_e);
                }
            } else {
                if (dComIfG_getTimerMode() == 3 && dComIfG_getTimerPtr() != NULL) {
                    dComIfG_getTimerPtr()->deleteRequest();
                }
                procShipPaddle_init();
                ship->m034D = 0xE; // TODO inline
            }
        }
    }
    
    return TRUE;
}

/* 8014F4DC-8014F690       .text procTactPlayOriginal_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayOriginal_init() {
    if (mCurProc == daPyProc_TACT_PLAY_ORIGINAL_e) {
        return TRUE;
    }
    commonProcInit(daPyProc_TACT_PLAY_ORIGINAL_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);
    m34D0 = 0;
    daPy_matAnm_c::offMabaFlg();
    daPy_matAnm_c::setMabaTimer(1);
    setSingleMoveAnime(ANM_WAITTAKT, daPy_HIO_tact_c0::m.field_0x0, 0.0f, -1, daPy_HIO_tact_c0::m.field_0x4);
    
    m3570 = dComIfGp_event_getTactFreeMStick(m34D0);
    setActAnimeUpper(getTactPlayRightArmAnm(m3570), UPPER_MOVE1_e, 0.0f, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);
    
    m3574 = dComIfGp_event_getTactFreeCStick(m34D0);
    setActAnimeUpper(getTactPlayLeftArmAnm(m3574), UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE2_e].setRatio(0.0f);
    
    setTextureAnime(0, 0);
    m3530 = 3;
    mDoAud_tact_setStickPos(m3570, m3574);
    mDoAud_tact_playArmSwing(m3570, m3574);
    setTactModel();
    m32E4.makeEmitter(0x51, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    m34D6 = 0xF;
    m34DA = 0;
    mDoAud_taktModeMute();
    
    return TRUE;
}

/* 8014F690-8014F8A0       .text procTactPlayOriginal__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayOriginal() {
    mDoAud_seStart(JA_SE_LK_WTAKT_USING, 0);
    
    if (m_old_fdata->getOldFrameRate() < 0.01f) {
        if (m34D6 > 0) {
            m34D6--;
            if (m34D6 == 0) {
                m34D0++;
            }
        } else if (m34D0 == 5) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            mDoAud_tact_stopArmSwing();
        } else {
            m34D6 = 0xF;
            
            m3570 = dComIfGp_event_getTactFreeMStick(m34D0);
            setActAnimeUpper(getTactPlayRightArmAnm(m3570), UPPER_MOVE1_e, daPy_HIO_tact_c0::m.field_0x8, 0.0f, -1, 5.0f);
            mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);
            if (m3570 == 0 || m3570 == 2 || m3570 == 4) {
                mFrameCtrlUpper[UPPER_MOVE1_e].setRate(daPy_HIO_tact_c0::m.field_0x0);
                mFrameCtrlUpper[UPPER_MOVE1_e].setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
            }
            
            m3574 = dComIfGp_event_getTactFreeCStick(m34D0);
            setActAnimeUpper(getTactPlayLeftArmAnm(m3574), UPPER_MOVE2_e, daPy_HIO_tact_c0::m.field_0x0, 0.0f, -1, 5.0f);
            mAnmRatioUpper[UPPER_MOVE2_e].setRatio(0.0f);
            mFrameCtrlUpper[UPPER_MOVE2_e].setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
            
            mDoAud_tact_setStickPos(m3570, m3574);
            mDoAud_tact_playArmSwing(m3570, m3574);
        }
    }
    
    if (m34D6 != 0 && m34DA != 0) {
        mDoAud_tact_play();
    }
    m34DA = 1;
    
    return TRUE;
}
