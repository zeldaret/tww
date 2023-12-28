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
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"

/* 8014D778-8014D7D4       .text getDayNightParamData__9daPy_lk_cFv */
u32 daPy_lk_c::getDayNightParamData() {
    u32 spawnType = dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) ? 2 : 0;
    u32 eventIdx = 0xCC;
    u32 extraParams = dComIfGp_getShipActor() != NULL ? 0x140 : 0x40;
    return setParamData(current.roomNo, spawnType, eventIdx, extraParams);
}

/* 8014D7D4-8014D8AC       .text setTactModel__9daPy_lk_cFv */
void daPy_lk_c::setTactModel() {
    if (mHeldItemType == WIND_TACT)
        return;
    
    deleteEquipItem(0);
    mHeldItemType = WIND_TACT;
    JKRHeap* oldHeap = setItemHeap();
    
    J3DModelData* modelData = initModel(&mpHeldItemModel, LINK_BDL_TAKT, 0x37221222);
    u8* buffer = new(0x20) u8[0x400];
    dComIfGp_getAnmArchive()->readIdxResource(buffer, 0x400, LKANM_BRK_TTAKT);
    mpHeldItemAnimBRK = (J3DAnmTevRegKey*)J3DAnmLoaderDataBase::load(buffer);
    mpHeldItemAnimBRK->setFrame(0.0f);
    mpHeldItemAnimBRK->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpHeldItemAnimBRK);
    
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
    if (mCurProc == PROC_TACT_PLAY_e && m34D0 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* 8014D9A4-8014D9D0       .text getTactMetronomeRate__9daPy_lk_cFv */
f32 daPy_lk_c::getTactMetronomeRate() {
    if (mCurProc == PROC_TACT_WAIT_e) {
        return m35A0 / mDoAud_zelAudio_c::getTact().field_0x30;
    } else {
        return -1.0f;
    }
}

/* 8014D9D0-8014D9F8       .text checkTactLastInput__9daPy_lk_cFv */
BOOL daPy_lk_c::checkTactLastInput() {
    if (mCurProc == PROC_TACT_WAIT_e && m34D2 != -1) {
        return TRUE;
    }
    return FALSE;
}

/* 8014D9F8-8014DA78       .text setTactZev__9daPy_lk_cFUiiPc */
void daPy_lk_c::setTactZev(unsigned int tactZevPartnerPID, int r30, char* r31) {
    if (tactZevPartnerPID != fpcM_ERROR_PROCESS_ID_e) {
        mDoAud_seStart(JA_SE_PRE_TAKT);
    }
    mTactZevPartnerPID = tactZevPartnerPID;
    m34CC = r30;
    m3494 = r31;
}

/* 8014DA78-8014DACC       .text getTactTopPos__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::getTactTopPos(cXyz* out) {
    if (mHeldItemType != WIND_TACT || mpHeldItemModel == NULL) {
        return FALSE;
    } else {
        MTXMultVec(mpHeldItemModel->getBaseTRMtx(), &l_tact_top, out);
        return TRUE;
    }
}

/* 8014DACC-8014DB00       .text getTactNormalWait__9daPy_lk_cCFv */
BOOL daPy_lk_c::getTactNormalWait() const {
    if (mCurProc == PROC_TACT_WAIT_e && m3570 == -1 && m34D2 == -1) {
        return TRUE;
    }
    return FALSE;
}

/* 8014DB00-8014DB2C       .text getTactMusic__9daPy_lk_cCFv */
s32 daPy_lk_c::getTactMusic() const {
    if (mCurProc == PROC_TACT_PLAY_e)
        return m3570;
    if (mCurProc == PROC_TACT_WAIT_e)
        return m3574;
    return -1;
}

/* 8014DB2C-8014DB74       .text getTactTimerCancel__9daPy_lk_cCFv */
int daPy_lk_c::getTactTimerCancel() const {
    if (mCurProc == PROC_TACT_WAIT_e && m35AC <= 0.0f) {
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
    if (mCurProc == PROC_TACT_PLAY_e && m34DA == 0) {
        return TRUE;
    }
    return FALSE;
}

/* 8014DB9C-8014DBEC       .text resetTactCount__9daPy_lk_cFv */
void daPy_lk_c::resetTactCount() {
    if (mCurProc == PROC_TACT_WAIT_e) {
        m34D8 = 0;
        m35A0 = 0.0f;
        m34DA = 0;
        m34D0 = -1;
        mDoAud_tact_reset();
    }
}

/* 8014DBEC-8014E100       .text procTactWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procTactWait_init(int) {
    /* Nonmatching */
}

/* 8014E100-8014E9A4       .text procTactWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactWait() {
    /* Nonmatching */
}

/* 8014E9A4-8014EBA0       .text procTactPlay_init__9daPy_lk_cFlii */
BOOL daPy_lk_c::procTactPlay_init(s32, int, int) {
    /* Nonmatching */
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
