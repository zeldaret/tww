/**
 * d_a_player_bottle.inc
 *
 * Code relating to various bottled items and bottle interactions.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/d_camera.h"
#include "d/d_procname.h"

/* 80151E40-80151E60       .text changeBottleDrinkFace__9daPy_lk_cFi */
int daPy_lk_c::changeBottleDrinkFace(int param_0) {
    if ((param_0 == 0x55) || (param_0 == 0x54)) {
        return true;
    }
    return false;
}

/* 80151E60-80152128       .text setBottleModel__9daPy_lk_cFUs */
void daPy_lk_c::setBottleModel(u16) {
    /* Nonmatching */
}

/* 80152128-801521A0       .text makeFairy__9daPy_lk_cFP4cXyzUl */
void daPy_lk_c::makeFairy(cXyz* param_0, u32 param_1) {
    onResetFlg0(daPyRFlg0_FAIRY_USE);
    resetCurse();
    fopAcM_fastCreate(PROC_NPC_FA1, param_1, param_0, fopAcM_GetRoomNo(this), &shape_angle);
}

/* 801521A0-80152300       .text procBottleDrink_init__9daPy_lk_cFUs */
BOOL daPy_lk_c::procBottleDrink_init(u16 param_0) {
    if (!dComIfGp_event_compulsory(this)) {
        return false;
    }

    mDemo.setDemoType(5);
    int iVar1 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_BOTTLE_DRINK_e);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    setSingleMoveAnime(
        ANM_BINDRINKPRE,
        1.0f,
        daPy_HIO_bottle_c0::m.field_0x5C,
        daPy_HIO_bottle_c0::m.field_0xC,
        daPy_HIO_bottle_c0::m.field_0x60
    );
    if (changeBottleDrinkFace(param_0)) {
        setTextureAnime(0x85, 0);
    }
    keepItemData();
    setBottleModel(param_0);
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK2000_e);
    m3570 = 1;
    dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &m3570, 0);
    initShipRideUseItem(iVar1, 2);
    return true;
}

/* 80152300-80152624       .text procBottleDrink__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleDrink() {
    /* Nonmatching */
}

/* 80152624-801527CC       .text procBottleOpen_init__9daPy_lk_cFUs */
BOOL daPy_lk_c::procBottleOpen_init(u16 param_0) {
    if (mCurProc == daPyProc_BOTTLE_OPEN_e) {
        return true;
    }

    if (mDemo.getDemoMode() != 0x3d) {
        if (!dComIfGp_event_compulsory(this)) {
            return false;
        }
        mDemo.setDemoType(5);
    } else {
        param_0 = dComIfGp_event_getPreItemNo();
    }
    int iVar1 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_BOTTLE_OPEN_e);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    setSingleMoveAnime(
        ANM_BINOPENPRE,
        1.0f,
        daPy_HIO_bottle_c0::m.field_0x3C,
        daPy_HIO_bottle_c0::m.field_0x6,
        daPy_HIO_bottle_c0::m.field_0x40
    );
    keepItemData();
    setBottleModel(param_0);
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK4000_e);
    if (mEquipItem == dItem_FAIRY_BOTTLE_e) {
        m3570 = 3;
    } else {
        m3570 = 2;
    }
    if (mDemo.getDemoMode() != 0x3d) {
        dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &m3570, 0);
    }
    initShipRideUseItem(iVar1, 2);
    m34D4 = 0;
    m34D6 = 0;
    m34D0 = -1;
    m34D8 = 0;
    return true;
}

/* 801527CC-80152ED0       .text procBottleOpen__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleOpen() {
    /* Nonmatching */
    static const Vec splash_scale = {0.3f, 0.3f, 0.3f};
    static const Vec ripple_scale = {0.5f, 0.5f, 0.5f};
}

/* 80152ED0-80153064       .text procBottleSwing_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procBottleSwing_init(int param_0) {
    /* Nonmatching - missing "lwz" instruction */
    BOOL bVar1;
    int iVar2;
    fopAc_ac_c* iVar3;

    iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_BOTTLE_SWING_e);
    if ((int)param_0 != 0) {
        deleteEquipItem(FALSE);
        setBottleModel(0x50);
    }
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    iVar3 = dComIfGp_att_getCatghTarget();
    if (iVar3 != 0) {
        if (iVar3->current.pos.y > mpCLModel->getBaseScale()->y) {
            bVar1 = false;
        } else {
            bVar1 = true;
        }
    } else if (m35D0 > 10.0f + current.pos.y) {
        bVar1 = true;
    } else {
        bVar1 = false;
    }
    if (bVar1) {
        setSingleMoveAnime(
            ANM_BINSWINGU,
            daPy_HIO_bottle_c0::m.field_0x20,
            daPy_HIO_bottle_c0::m.field_0x24,
            daPy_HIO_bottle_c0::m.field_0x2,
            daPy_HIO_bottle_c0::m.field_0x2C
        );
        m35A0 = daPy_HIO_bottle_c0::m.field_0x28;
    } else {
        setSingleMoveAnime(
            ANM_BINSWINGS,
            daPy_HIO_bottle_c0::m.field_0x10,
            daPy_HIO_bottle_c0::m.field_0x14,
            daPy_HIO_bottle_c0::m.field_0x0,
            daPy_HIO_bottle_c0::m.field_0x1C
        );
        m35A0 = daPy_HIO_bottle_c0::m.field_0x18;
    }
    m3570 = 0;
    m3574 = 0;
    m34D4 = 0;
    voiceStart(7);
    initShipRideUseItem(iVar2, 2);
    return true;
}

/* 80153064-80153338       .text procBottleSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleSwing() {
    /* Nonmatching */
}

/* 80153338-80153438       .text procBottleGet_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleGet_init() {
    int iVar1 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_BOTTLE_GET_e);
    setSingleMoveAnime(
        ANM_BINGET,
        daPy_HIO_bottle_c0::m.field_0x30,
        daPy_HIO_bottle_c0::m.field_0x34,
        daPy_HIO_bottle_c0::m.field_0x4,
        daPy_HIO_bottle_c0::m.field_0x38
    );
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK1000_e);
    m3628 = fpcM_ERROR_PROCESS_ID_e;
    m3570 = 0;
    dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &m3570, 0);
    if (mEquipItem == dItem_FOREST_WATER_e) {
        m32F0.makeEmitter(dPa_name::ID_COMMON_020D, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    }
    initShipRideUseItem(iVar1, 2);
    return true;
}

/* 80153438-80153554       .text procBottleGet__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleGet() {
    /* Nonmatching - floats */
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    setShipRidePosUseItem();
    if ((frameCtrl.getRate() < 0.01f) && (checkEndMessage(mEquipItem + 0x65))) {
        dComIfGp_event_reset();
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        deleteEquipItem(FALSE);
        endDemoMode();
    } else {
        if (frameCtrl.getFrame() >= 9.0f) {
            m355E = 1;
        }
    }
    if (frameCtrl.checkPass(39.0f)) {
        mDoAud_seStart(JA_SE_ME_ITEM_GET_S);
        g_dComIfG_gameInfo.play.field_0x4977 = 2;
    }
    return true;
}
