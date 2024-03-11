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
    if (mHeldItemType == dItem_WIND_WAKER_e)
        return;
    
    deleteEquipItem(FALSE);
    mHeldItemType = dItem_WIND_WAKER_e;
    JKRHeap* oldHeap = setItemHeap();
    
    J3DModelData* modelData = initModel(&mpHeldItemModel, LINK_BDL_TAKT, 0x37221222);
    u8* buffer = new(0x20) u8[0x400];
    dComIfGp_getAnmArchive()->readIdxResource(buffer, 0x400, LKANM_BRK_TTAKT);
    mpHeldItemBrk = (J3DAnmTevRegKey*)J3DAnmLoaderDataBase::load(buffer);
    mpHeldItemBrk->setFrame(0.0f);
    mpHeldItemBrk->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpHeldItemBrk);
    
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
int daPy_lk_c::getTactPlayRightArmAnm(s32 r4) {
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
int daPy_lk_c::getTactPlayLeftArmAnm(s32 r4) {
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
    if (mHeldItemType != dItem_WIND_WAKER_e || mpHeldItemModel == NULL) {
        return FALSE;
    } else {
        MTXMultVec(mpHeldItemModel->getBaseTRMtx(), &l_tact_top, out);
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
    m32E4.makeEmitter(0x50, mpHeldItemModel->getBaseTRMtx(), &current.pos, NULL);
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
    
    m32E4.makeEmitter(0x51, mpHeldItemModel->getBaseTRMtx(), &current.pos, NULL);
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
BOOL daPy_lk_c::procTactPlayEnd_init(int) {
    /* Nonmatching */
}

/* 8014F210-8014F4DC       .text procTactPlayEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayEnd() {
    /* Nonmatching */
}

/* 8014F4DC-8014F690       .text procTactPlayOriginal_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayOriginal_init() {
    /* Nonmatching */
}

/* 8014F690-8014F8A0       .text procTactPlayOriginal__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayOriginal() {
    /* Nonmatching */
}
