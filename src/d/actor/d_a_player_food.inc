/**
 * d_a_player_food.inc
 *
 * Code relating to the All-Purpose Bait and Hyoi Pear items.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "f_op/f_op_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_procname.h"

/* 80154334-801543A0       .text setHyoiModel__9daPy_lk_cFv */
void daPy_lk_c::setHyoiModel() {
    if (mHeldItemType == dItem_HYOI_PEAR_e) {
        return;
    }
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpHeldItemModel, LINK_BDL_HYOINOMI, 0x13000022);
    mDoExt_setCurrentHeap(oldHeap);
    mHeldItemType = dItem_HYOI_PEAR_e;
}

/* 801543A0-801546F4       .text procFoodThrow_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFoodThrow_init() {
    if (mCurProc == daPyProc_FOOD_THROW_e) {
        return TRUE;
    }
    if (m3630 != fpcM_ERROR_PROCESS_ID_e) {
        mDoAud_seStart(JA_SE_ITEM_TARGET_OUT);
        return FALSE;
    }
    
    dBgS* bgs = dComIfG_Bgsp(); // This is kinda weird, maybe fakematch
    
    if (dComIfGp_event_runCheck() == FALSE) {
        if (!dComIfGp_event_compulsory(this)) {
            return FALSE;
        } else {
            mDemo.setSpecialDemoType();
        }
    } else {
        deleteEquipItem(FALSE);
    }
    
    int temp = checkShipRideUseItem(1);
    
    commonProcInit(daPyProc_FOOD_THROW_e);
    
    if (temp == 0) {
        f32 offset1 = cM_ssin(shape_angle.y) * 150.0f;
        f32 offset2 = cM_scos(shape_angle.y) * 150.0f;
        cXyz start;
        start.set(
            attention_info.position.x,
            attention_info.position.y - 50.0f,
            attention_info.position.z
        );
        cXyz end;
        end.set(
            start.x + offset1,
            start.y,
            start.z + offset2
        );
        mLinkLinChk.Set(&start, &end, this);
        if (bgs->LineCross(&mLinkLinChk)) {
            end.x = start.x - offset1;
            end.z = start.z - offset2;
            mLinkLinChk.Set(&start, &end, this);
            if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                shape_angle.y += 0x8000;
            } else {
                end.x = start.x + offset2;
                end.z = start.z - offset1;
                mLinkLinChk.Set(&start, &end, this);
                if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                    shape_angle.y += 0x4000;
                } else {
                    end.x = start.x - offset2;
                    end.z = start.z + offset1;
                    mLinkLinChk.Set(&start, &end, this);
                    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        shape_angle.y -= 0x4000;
                    }
                }
            }
        }
    }
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    
    daPy_matAnm_c::m_maba_flg = 0;
    daPy_matAnm_c::m_maba_timer = 1;
    setSingleMoveAnime(ANM_ESAMAKI, daPy_HIO_food_c0::m.field_0x4, daPy_HIO_food_c0::m.field_0x8, daPy_HIO_food_c0::m.field_0x0, daPy_HIO_food_c0::m.field_0xC);
    keepItemData();
    
    if (mDemo.getDemoType() == 5) {
        m3570 = 6;
        dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &m3570, 0);
    }
    
    initShipRideUseItem(temp, 2);
    m3630 = fpcM_ERROR_PROCESS_ID_e;
    
    return TRUE;
}

/* 801546F4-80154880       .text procFoodThrow__9daPy_lk_cFv */
BOOL daPy_lk_c::procFoodThrow() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    setShipRidePosUseItem();
    if (frameCtrl.getRate() < 0.01f) {
        if (mDemo.getDemoType() != 5) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else {
            dComIfGp_event_reset();
            uint playerPID = fopAcM_GetID(this);
            dCam_getBody()->EndEventCamera(playerPID);
            endDemoMode();
        }
    } else if (frameCtrl.checkPass(9.0f)) {
        seStartOnlyReverb(JA_SE_LK_ESA_THROW);
        void* esa = fopAcM_fastCreate(PROC_ESA, 0xFFFF0014, &mLeftHandPos, fopAcM_GetRoomNo(this), &shape_angle);
        if (esa) {
            m3630 = fopAcM_GetID(esa);
            if (mDemo.getDemoType() != 5) {
                u8 btnIdx = dComIfGp_event_getTalkXYBtn();
                if (btnIdx == 1) {
                    dComIfGs_setReserveBaitEmpty(0);
                } else if (btnIdx == 2) {
                    dComIfGs_setReserveBaitEmpty(1);
                } else {
                    dComIfGs_setReserveBaitEmpty(2);
                }
            } else {
                dComIfGs_setReserveBaitEmpty(mLastUsedItemButtonIdx);
            }
        }
    }
    return TRUE;
}

/* 80154880-80154A48       .text procFoodSet_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFoodSet_init() {
    if (mCurProc == daPyProc_FOOD_SET_e) {
        if (mDemo.getParam0() == 1) {
            if (mHeldItemType == dItem_HYOI_PEAR_e) {
                u8 btnIdx = dComIfGp_event_getTalkXYBtn();
                if (btnIdx == 1) {
                    dComIfGs_setEquipBottleItemEmpty(0);
                } else if (btnIdx == 2) {
                    dComIfGs_setEquipBottleItemEmpty(1);
                } else {
                    dComIfGs_setEquipBottleItemEmpty(2);
                }
            }
            
            deleteEquipItem(FALSE);
        } else {
            setHyoiModel();
        }
        return TRUE;
    }
    
    if (dComIfGp_event_runCheck() == FALSE) {
        if (!dComIfGp_event_compulsory(this)) {
            return FALSE;
        }
        mDemo.setDemoType(5);
    }
    
    int temp = checkShipRideUseItem(1);
    commonProcInit(daPyProc_FOOD_SET_e);
    current.angle.y = shape_angle.y;
    
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_SETHYOINOMI, daPy_HIO_food_c0::m.field_0x10, daPy_HIO_food_c0::m.field_0x14, daPy_HIO_food_c0::m.field_0x2, daPy_HIO_food_c0::m.field_0x18);
    keepItemData();
    setHyoiModel();
    
    if (mDemo.getDemoType() == 5) {
        m3570 = 1;
        dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &m3570, 0);
    }
    
    initShipRideUseItem(temp, 2);
    m34D0 = 1*30;
    
    return TRUE;
}

/* 80154A48-80154B80       .text procFoodSet__9daPy_lk_cFv */
BOOL daPy_lk_c::procFoodSet() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    
    setShipRidePosUseItem();
    
    if (frameCtrl.getRate() > 0.0f && frameCtrl.checkPass(9.0f)) {
        seStartOnlyReverb(JA_SE_LK_HYOI_SET);
    }
    
    if (fabsf(frameCtrl.getRate()) < 0.01f) {
        if (mDemo.getDemoType() != 5) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else if (m34D0 < 0) {
            dComIfGp_event_reset();
            deleteEquipItem(FALSE);
            uint playerPID = fopAcM_GetID(this);
            dCam_getBody()->EndEventCamera(playerPID);
            endDemoMode();
        } else if (m34D0 == 0) {
            m34D0 = -1;
            frameCtrl.setRate(-daPy_HIO_food_c0::m.field_0x10);
        } else if (m34D0 > 0) {
            m34D0--;
        }
    }
    
    return TRUE;
}
