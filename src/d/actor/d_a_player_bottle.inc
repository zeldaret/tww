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
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"

/* 80151E40-80151E60       .text changeBottleDrinkFace__9daPy_lk_cFi */
int daPy_lk_c::changeBottleDrinkFace(int param_0) {
    if (param_0 == dItem_SOUP_BOTTLE_e || param_0 == dItem_HALF_SOUP_BOTTLE_e) {
        return true;
    }
    return false;
}

/* 80151E60-80152128       .text setBottleModel__9daPy_lk_cFUs */
void daPy_lk_c::setBottleModel(u16 param_0) {
    mEquipItem = param_0;
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_BOTTLEEMP, 0x37221222);
    u8* buffer = new (0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, LKANM_BTK_TBOTTLE, dComIfGp_getAnmArchive());
    mpEquipItemBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpEquipItemBtk->setFrame(0.0f);
    mpEquipItemBtk->searchUpdateMaterialID(tmp_modelData);
    tmp_modelData->entryTexMtxAnimator(mpEquipItemBtk);
    if (param_0 == dItem_RED_POTION_e || param_0 == dItem_GREEN_POTION_e || param_0 == dItem_BLUE_POTION_e ||
        param_0 == dItem_HALF_SOUP_BOTTLE_e || param_0 == dItem_SOUP_BOTTLE_e || param_0 == dItem_WATER_BOTTLE_e ||
        param_0 == dItem_FOREST_WATER_e)
    {
        u16 bdl;
        if (param_0 == dItem_HALF_SOUP_BOTTLE_e) {
            bdl = LINK_BDL_BINLIQUIDH;
        } else {
            bdl = LINK_BDL_BINLIQUID;
        }
        tmp_modelData = initModel(&mpBottleContentsModel, bdl, 0x13000022);
        buffer = new (0x20) u8[0x400];
        JKRReadIdxResource(buffer, 0x400, LKANM_BRK_TBINLIQUID, dComIfGp_getAnmArchive());
        mpEquipItemBrk = static_cast<J3DAnmTevRegKey*>(J3DAnmLoaderDataBase::load(buffer));
        if (param_0 == dItem_RED_POTION_e) {
            mpEquipItemBrk->setFrame(0.0f);
        } else if (param_0 == dItem_GREEN_POTION_e) {
            mpEquipItemBrk->setFrame(1.0f);
        } else if (param_0 == dItem_BLUE_POTION_e) {
            mpEquipItemBrk->setFrame(2.0f);
        } else if (param_0 == dItem_SOUP_BOTTLE_e || param_0 == dItem_HALF_SOUP_BOTTLE_e) {
            mpEquipItemBrk->setFrame(4.0f);
        } else {
            mpEquipItemBrk->setFrame(3.0f);
        }
        mpEquipItemBrk->searchUpdateMaterialID(tmp_modelData);
        tmp_modelData->entryTevRegAnimator(mpEquipItemBrk);
    } else if (param_0 == dItem_FAIRY_BOTTLE_e) {
        tmp_modelData = initModel(&mpBottleContentsModel, LINK_BDL_BINFAIRY, 0x13000022);
    } else if (param_0 == dItem_FIREFLY_BOTTLE_e) {
        tmp_modelData = initModel(&mpBottleContentsModel, LINK_BDL_BINHO, 0x13000022);
        buffer = new (0x20) u8[0x400];
        JKRReadIdxResource(buffer, 0x400, LKANM_BRK_TBINHO, dComIfGp_getAnmArchive());
        mpEquipItemBrk = static_cast<J3DAnmTevRegKey*>(J3DAnmLoaderDataBase::load(buffer));
        mpEquipItemBrk->searchUpdateMaterialID(tmp_modelData);
        tmp_modelData->entryTevRegAnimator(mpEquipItemBrk);
        m3600 = 0.0f;
    }
    if (param_0 != dItem_EMPTY_BOTTLE_e && mCurProc != daPyProc_BOTTLE_DRINK_e) {
        tmp_modelData = initModel(&mpBottleCapModel, LINK_BDL_BOTTLECAP, 0x13000022);
        m355E = 1;
    }
    mDoExt_setCurrentHeap(oldHeap);
    if (param_0 == dItem_FOREST_WATER_e) {
        m32F0.makeEmitter(dPa_name::ID_COMMON_020D, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    }
}

/* 80152128-801521A0       .text makeFairy__9daPy_lk_cFP4cXyzUl */
fopAc_ac_c* daPy_lk_c::makeFairy(cXyz* param_0, u32 param_1) {
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
    mProcVar0.m3570 = 1;
    dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &mProcVar0.m3570, 0);
    initShipRideUseItem(iVar1, 2);
    return true;
}

/* 80152300-80152624       .text procBottleDrink__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleDrink() {
    static const GXColor red = {0xC8, 0x00, 0x00, 0xFF};
    static const GXColor green = {0x00, 0xFA, 0x00, 0xFF};
    static const GXColor blue = {0x00, 0x32, 0x96, 0xFF};

    setShipRidePosUseItem();
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    u16 uVar1 = m_anm_heap_under[UNDER_MOVE0_e].mIdx;
    if (uVar1 == LKANM_BCK_BINDRINKPRE) {
        if (frameCtrl.getRate() < 0.01f) {
            setSingleMoveAnime(ANM_BINDRINKING, daPy_HIO_bottle_c0::m.field_0x64, 0.0f, -1, 0.0f);
            if (changeBottleDrinkFace(mEquipItem)) {
                setTextureAnime(0x86, 0);
            }
            if (mEquipItem != dItem_GREEN_POTION_e) {
                dComIfGp_setItemLifeCount(dComIfGs_getMaxLife());
            }
            if (mEquipItem != dItem_RED_POTION_e) {
                dComIfGp_setItemMagicCount(dComIfGs_getMaxMagic());
            }
            if (mEquipItem == dItem_SOUP_BOTTLE_e || mEquipItem == dItem_HALF_SOUP_BOTTLE_e) {
                onNoResetFlg1(daPyFlg1_UNK8000);
            }
            resetCurse();
        } else {
            if (frameCtrl.checkPass(65.0f)) {
                voiceStart(39);
            }
        }
    } else if (uVar1 == LKANM_BCK_BINDRINKING) {
        if (dComIfGp_getItemNowLife() == dComIfGs_getLife() &&
            dComIfGs_getMagic() == g_dComIfG_gameInfo.play.field_0x48da)
        {
            setSingleMoveAnime(
                ANM_BINDRINKAFTER,
                1.0f,
                daPy_HIO_bottle_c0::m.field_0x68,
                daPy_HIO_bottle_c0::m.field_0xE,
                daPy_HIO_bottle_c0::m.field_0x6C
            );
            if (changeBottleDrinkFace(mEquipItem)) {
                setTextureAnime(0x87, 0);
            }
            if (mEquipItem == dItem_SOUP_BOTTLE_e) {
                setBottleModel(dItem_HALF_SOUP_BOTTLE_e);
                dComIfGs_setEquipBottleItemIn(mReadyItemBtn, dItem_HALF_SOUP_BOTTLE_e);
            } else {
                mpBottleContentsModel = NULL;
                dComIfGs_setEquipBottleItemEmpty(mReadyItemBtn);
            }
            const GXColor* p_Var3;
            if (mEquipItem != dItem_SOUP_BOTTLE_e && mEquipItem != dItem_HALF_SOUP_BOTTLE_e) {
                if (mEquipItem == dItem_RED_POTION_e) {
                    p_Var3 = &red;
                } else if (mEquipItem == dItem_GREEN_POTION_e) {
                    p_Var3 = &green;
                } else {
                    p_Var3 = &blue;
                }
                m33A8.makeEmitterColor(
                    dPa_name::ID_COMMON_0057, mpCLModel->getAnmMtx(0x12), &current.pos, &shape_angle, p_Var3, NULL
                );
            }
        } else {
            if (frameCtrl.checkPass(10.0f)) {
                voiceStart(39);
            }
        }
    } else if (frameCtrl.getRate() < 0.01f) {
        dComIfGp_event_reset();
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        endDemoMode();
    } else {
        if (frameCtrl.checkPass(8.0f)) {
            voiceStart(40);
        }
    }
    return true;
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
        mProcVar0.m3570 = 3;
    } else {
        mProcVar0.m3570 = 2;
    }
    if (mDemo.getDemoMode() != 0x3d) {
        dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &mProcVar0.m3570, 0);
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
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_BOTTLE_SWING_e);
    if (param_0 != 0) {
        deleteEquipItem(FALSE);
        setBottleModel(dItem_EMPTY_BOTTLE_e);
    }
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    fopAc_ac_c* catch_target = dComIfGp_att_getCatghTarget();
    BOOL bVar1;
    if (catch_target != 0) {
        if (catch_target->current.pos.y > mpCLModel->getAnmMtx(0)[1][3]) {
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
    mProcVar0.m3570 = 0;
    m3574 = 0;
    m34D4 = 0;
    voiceStart(7);
    initShipRideUseItem(iVar2, 2);
    return true;
}

/* 80153064-80153338       .text procBottleSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleSwing() {
    setShipRidePosUseItem();
    if (mProcVar0.m3570 == 0) {
        if (eventInfo.checkCommandCatch()) {
            mProcVar0.m3570 = 1;
            u8 bVar5 = dComIfGp_event_getPreItemNo();
            if (bVar5 == dItem_WATER_BOTTLE_e) {
                seStartOnlyReverb(JA_SE_LK_SCOOP_WATER);
                if (!strcmp(dComIfGp_getStartStageName(), "Omori")) {
                    bVar5 = dItem_FOREST_WATER_e;
                    if (dComIfGs_checkBottle(dItem_FOREST_WATER_e)) {
                        m3628 = fpcM_ERROR_PROCESS_ID_e;
                        m3574 = 1;
                    } else {
                        dComIfGs_getpItemRecord()->resetTimer(36000);
                    }
                }
            }
            if (m3574 == 0) {
                setBottleModel(bVar5);
                dComIfGs_setEquipBottleItemIn(mReadyItemBtn, mEquipItem);
                m355E = 0;
            }
            mDemo.setDemoType(5);
        } else {
            if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= 1.0f &&
                mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() <= 4.0f && getReadyItem() == dItem_EMPTY_BOTTLE_e &&
                (dComIfGp_att_getCatghTarget() != NULL || m35D0 > current.pos.y + 10.0f))
            {
                fopAcM_orderCatchEvent(this, dComIfGp_att_getCatghTarget());
            }
        }
    }
    if ((mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) || m34D4 != 0) {
        if (m3574 != 0) {
            if (m34D4 == 0) {
                offModeFlg(ModeFlg_00000400);
                onModeFlg(ModeFlg_00000100);
                setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
                m34D4 = 1;
            }
            if (checkEndMessage(0x14a2)) {
                dComIfGp_event_reset();
                endDemoMode();
            }
        } else {
            if (mProcVar0.m3570 != 0) {
                procBottleGet_init();
            } else {
                if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                    procShipPaddle_init();
                } else {
                    checkNextMode(0);
                }
            }
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m35A0) {
        if (mProcVar0.m3570 == 0 && !dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            checkNextMode(1);
        }
    }
    return true;
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
    mProcVar0.m3570 = 0;
    dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &mProcVar0.m3570, 0);
    if (mEquipItem == dItem_FOREST_WATER_e) {
        m32F0.makeEmitter(dPa_name::ID_COMMON_020D, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    }
    initShipRideUseItem(iVar1, 2);
    return true;
}

/* 80153438-80153554       .text procBottleGet__9daPy_lk_cFv */
BOOL daPy_lk_c::procBottleGet() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    setShipRidePosUseItem();
    if (frameCtrl.getRate() < 0.01f && (checkEndMessage(MSG_NO_FOR_ITEM(mEquipItem)))) {
        dComIfGp_event_reset();
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        deleteEquipItem(FALSE);
        endDemoMode();
    } else if (frameCtrl.getFrame() >= 9.0f) {
        m355E = 1;
    }
    if (frameCtrl.checkPass(39.0f)) {
        mDoAud_seStart(JA_SE_ME_ITEM_GET_S);
        dComIfGp_setMesgBgmOn2();
    }
    return true;
}
