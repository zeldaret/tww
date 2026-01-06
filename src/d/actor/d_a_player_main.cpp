/**
 * d_a_player_main.cpp
 * 
 * Main file for the Link (Player) actor.
 * 
 * Much of Link's code is spread across various `.inc` files and included directly
 * into this one to make the file size more managable.
 * The original split locations are indicated in the map file.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_demo_item.h"
#include "d/actor/d_a_npc_fa1.h"
#include "d/actor/d_a_obj_movebox.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_sea.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "d/d_kankyo_wether.h"
#include "d/d_path.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_kankyo.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/actor/d_a_itembase.h"
#include "d/d_item_data.h"
#include "d/d_item.h"
#include "f_op/f_op_camera_mng.h"
#include "f_op/f_op_overlap_mng.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"
#include "d/d_material.h"
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"
#include "d/actor/d_a_hookshot.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_npc_sarace.h"
#include "d/actor/d_a_boomerang.h"
#include "SSystem/SComponent/c_counter.h"
#include "m_Do/m_Do_graphic.h"

JGeometry::TVec3<f32> l_hammer_splash_particle_scale(0.67f, 0.67f, 0.67f);

#include "d/actor/d_a_player_main_data.inc"

#include "d/actor/d_a_player_HIO_data.inc"

#if VERSION > VERSION_DEMO
cXyz l_debug_keep_pos;
csXyz l_debug_current_angle;
csXyz l_debug_shape_angle;
#endif

GXColor l_freeze_fade_color = {0xFF, 0xFF, 0xFF, 0xFF};

u8 daPy_matAnm_c::m_maba_timer;
u8 daPy_matAnm_c::m_maba_flg;
u8 daPy_matAnm_c::m_eye_move_flg;
u8 daPy_matAnm_c::m_morf_frame;

#include "d/actor/d_a_player_particle.inc"

#include "d/actor/d_a_player_dproc.inc"

#include "d/actor/d_a_player_ladder.inc"

#include "d/actor/d_a_player_hang.inc"

#include "d/actor/d_a_player_climb.inc"

#include "d/actor/d_a_player_whide.inc"

#include "d/actor/d_a_player_crawl.inc"

#include "d/actor/d_a_player_grab.inc"

#include "d/actor/d_a_player_swim.inc"

#include "d/actor/d_a_player_battle.inc"

#include "d/actor/d_a_player_ship.inc"

#include "d/actor/d_a_player_rope.inc"

#include "d/actor/d_a_player_boomerang.inc"

#include "d/actor/d_a_player_bow.inc"

#include "d/actor/d_a_player_hook.inc"

#include "d/actor/d_a_player_fan.inc"

#include "d/actor/d_a_player_tact.inc"

#include "d/actor/d_a_player_vomit.inc"

#include "d/actor/d_a_player_hammer.inc"

#include "d/actor/d_a_player_pushpull.inc"

#include "d/actor/d_a_player_bottle.inc"

#include "d/actor/d_a_player_weapon.inc"

#include "d/actor/d_a_player_food.inc"

#include "d/actor/d_a_player_sword.inc"

/* 80102E8C-80102EAC       .text daPy_createHeap__FP10fopAc_ac_c */
static BOOL daPy_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->createHeap();
}

/* 80102EAC-80102F1C       .text __ct__13daPy_matAnm_cFv */
daPy_matAnm_c::daPy_matAnm_c() {
    mEyePosOld.x = 0.0f;
    mEyePosOld.y = 0.0f;
    mEyePos.x = 0.0f;
    mEyePos.y = 0.0f;
    
    m_maba_flg = 0;
    m_eye_move_flg = 0;
    m_maba_timer = 0;
    m_morf_frame = 0;
}

/* 80102F64-80103074       .text calc__13daPy_matAnm_cCFP11J3DMaterial */
void daPy_matAnm_c::calc(J3DMaterial* mat) const {
    // Fakematch?
    daPy_matAnm_c* i_this = const_cast<daPy_matAnm_c*>(this);
    
    J3DMaterialAnm::calc(mat);
    
    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i)) {
            J3DTextureSRTInfo& srt = mat->getTexMtx(i)->getTexMtxInfo().mSRT;
            if (getMorfFrame() != 0) {
                f32 temp = 1.0f / (m_morf_frame + 1);
                srt.mTranslationX = mEyePosOld.x * (1.0f - temp) + (srt.mTranslationX * temp);
                srt.mTranslationY = mEyePosOld.y * (1.0f - temp) + (srt.mTranslationY * temp);
            } else if (getEyeMoveFlg() != 0) {
                srt.mTranslationX = mEyePos.x;
                srt.mTranslationY = mEyePos.y;
            }
            i_this->mEyePosOld.x = srt.mTranslationX;
            i_this->mEyePosOld.y = srt.mTranslationY;
        }
    }
}

/* 80103074-801030BC       .text seStartOnlyReverb__9daPy_lk_cFUl */
void daPy_lk_c::seStartOnlyReverb(u32 i_seNum) {
    mDoAud_seStart(i_seNum, &current.pos, 0, mReverb);
}

/* 801030BC-80103104       .text seStartMapInfo__9daPy_lk_cFUl */
void daPy_lk_c::seStartMapInfo(u32 i_seNum) {
    mDoAud_seStart(i_seNum, &current.pos, mMtrlSndId, mReverb);
}

/* 80103104-8010314C       .text seStartSwordCut__9daPy_lk_cFUl */
void daPy_lk_c::seStartSwordCut(u32 i_seNum) {
    mDoAud_seStart(i_seNum, &mSwordTopPos, 0, mReverb);
}

/* 8010314C-801031A4       .text voiceStart__9daPy_lk_cFUl */
void daPy_lk_c::voiceStart(u32 param_1) {
    mDoAud_linkVoiceStart(param_1, &eyePos, mDoAud_getLinkVoiceVowel(param_1), mReverb);
}

/* 801031A4-801031DC       .text itemButton__9daPy_lk_cCFv */
BOOL daPy_lk_c::itemButton() const {
    if (mReadyItemBtn == dItemBtn_X_e) {
        return itemButtonX();
    } else if (mReadyItemBtn == dItemBtn_Y_e) {
        return itemButtonY();
    } else {
        return itemButtonZ();
    }
}

/* 801031DC-80103214       .text itemTrigger__9daPy_lk_cCFv */
BOOL daPy_lk_c::itemTrigger() const {
    if (mReadyItemBtn == dItemBtn_X_e) {
        return itemTriggerX();
    } else if (mReadyItemBtn == dItemBtn_Y_e) {
        return itemTriggerY();
    } else {
        return itemTriggerZ();
    }
}

/* 80103214-80103258       .text getReadyItem__9daPy_lk_cFv */
int daPy_lk_c::getReadyItem() {
    if (mReadyItemBtn == dItemBtn_X_e) {
        return dComIfGp_getSelectItem(dItemBtn_X_e);
    } else if (mReadyItemBtn == dItemBtn_Y_e) {
        return dComIfGp_getSelectItem(dItemBtn_Y_e);
    } else {
        return dComIfGp_getSelectItem(dItemBtn_Z_e);
    }
}

/* 80103258-801032E4       .text checkGroupItem__9daPy_lk_cFii */
BOOL daPy_lk_c::checkGroupItem(int param_1, int itemNo) {
    if (param_1 == daPyItem_DRINK_BOTTLE_e) {
        return checkDrinkBottleItem(itemNo);
    } else if (param_1 == daPyItem_OPEN_BOTTLE_e) {
        return checkOpenBottleItem(itemNo);
    } else if (param_1 == daPyItem_ESA_e) {
        return isEsa(itemNo);
    } else if (param_1 == daPyItem_BOW_e) {
        return checkBowItem(itemNo);
    } else if (param_1 == daPyItem_PHOTOBOX_e) {
        return checkPhotoBoxItem(itemNo);
    } else {
        return param_1 == itemNo;
    }
}

/* 801032E4-801033E4       .text checkSetItemTrigger__9daPy_lk_cFii */
BOOL daPy_lk_c::checkSetItemTrigger(int param_1, int param_2) {
    if (param_2 == 0 || !daPy_dmEcallBack_c::checkCurse()) {
        if (itemTriggerX() && checkGroupItem(param_1, dComIfGp_getSelectItem(dItemBtn_X_e))) {
            mReadyItemBtn = dItemBtn_X_e;
            return TRUE;
        }
        if (itemTriggerY() && checkGroupItem(param_1, dComIfGp_getSelectItem(dItemBtn_Y_e))) {
            mReadyItemBtn = dItemBtn_Y_e;
            return TRUE;
        }
        if (itemTriggerZ() && checkGroupItem(param_1, dComIfGp_getSelectItem(dItemBtn_Z_e))) {
            mReadyItemBtn = dItemBtn_Z_e;
            return TRUE;
        }
    }
    return FALSE;
}

/* 801033E4-80103450       .text auraJointCB0__9daPy_lk_cFi */
BOOL daPy_lk_c::auraJointCB0(int jntNo) {
    mpYmgcs00Model->setAnmMtx(jntNo, mpCLModel->getAnmMtx(jntNo));
    mDoMtx_copy(mpCLModel->getAnmMtx(jntNo), j3dSys.mCurrentMtx);
    return TRUE;
}

/* 80103450-80103494       .text daPy_auraCallback__FP7J3DNodei */
static BOOL daPy_auraCallback(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        i_this->auraJointCB0(jntNo);
    }
    return TRUE;
}

/* 80103494-80103A88       .text jointBeforeCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
BOOL daPy_lk_c::jointBeforeCB(int jnt_no, J3DTransformInfo* param_2, Quaternion* param_3) {
    static Mtx root_mtx;
    static Quaternion norm_quat = {0.0f, 0.0f, 0.0f, 1.0f};
    Quaternion local_20;
    Quaternion afStack_30;

    csXyz local_38(0, 0, 0);
    if (jnt_no == 0xF) {
        local_38.set(m3566, m3568, m3564);
    } else if (jnt_no == 0x1F) {
        m34C6 = 2;
        m3668.mScale = param_2->mScale;
        m3668.mRotation = param_2->mRotation;
        m3668.mTranslate = param_2->mTranslate;
        param_2->mTranslate.x = param_2->mTranslate.x - mFootData[1].field_0x030;
    } else if (jnt_no == 0x24) {
        m34C6 = 2;
        m3668.mScale = param_2->mScale;
        m3668.mRotation = param_2->mRotation;
        m3668.mTranslate = param_2->mTranslate;
        param_2->mTranslate.x = param_2->mTranslate.x - mFootData[0].field_0x030;
    } else if (jnt_no == 0x10) {
        local_38.y = m3516;
        local_38.z = m351A;
    } else if (jnt_no == 0x11) {
        local_38.y = m3518;
        local_38.z = m351A;
    } else if (jnt_no == 2) {
        local_38.set(-mBodyAngle.z, mBodyAngle.y, mBodyAngle.x);
        m34C6 = 2;
        m3668.mScale = param_2->mScale;
        m3668.mRotation = param_2->mRotation;
        m3668.mTranslate = param_2->mTranslate;
        param_2->mTranslate.y = param_2->mTranslate.y + m35D8;
    } else if (jnt_no == 0) {
        local_38.x = m34F2;
        local_38.z = m34F4;
    } else if (
        (jnt_no == 0xA || jnt_no == 0xB) &&
        dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
        m_old_fdata->getOldFrameFlg() != false
    ) {
        if (dComIfGp_getShipActor() != NULL) {
            if (!fpcM_IsCreating(fopAcM_GetID(dComIfGp_getShipActor()))) {
                if (!checkShipNotNormalMode()) {
                    setShipRideArmAngle(jnt_no, param_2);
                    param_2->mTranslate.x = 0.0f;
                    param_2->mTranslate.y = 0.0f;
                    param_2->mTranslate.z = 0.0f;
                    JMAQuatLerp(m_old_fdata->getOldFrameQuaternion(jnt_no), &norm_quat,
                                (1.0f - m_old_fdata->getOldFrameRate()), param_3);
                }
            }
        }
    }

#if VERSION == VERSION_DEMO
    if (
        !checkModeFlg(ModeFlg_WHIDE | ModeFlg_SWIM | ModeFlg_CRAWL) &&
        mCurProc != daPyProc_VOMIT_WAIT_e && mCurProc != daPyProc_ELEC_DAMAGE_e && mCurProc != daPyProc_DEMO_DOOR_OPEN_e
    )
#else
    if (!checkResetFlg0(daPyRFlg0_UNK800000))
#endif
    {
        if (jnt_no == 0x1A) {
            JMAEulerToQuat(0, m34F8, m3528 + (m34F6 + -0x8000) + m350E, param_3);
        } else if (jnt_no == 0x1B) {
            JMAEulerToQuat(0, m34FC, m34FA + m3510, param_3);
        } else if (jnt_no == 0x1C) {
            JMAEulerToQuat(0, m3500, m34FE + m3512, param_3);
        }
    }

    if (jnt_no == 0) {
        if (m34C2 == 1) {
            param_2->mTranslate.x = 0.0f;
            param_2->mTranslate.z = 0.0f;
        } else if (m34C2 == 5) {
            param_2->mTranslate.x = 0.0f;
            param_2->mTranslate.y = m35E0;
            param_2->mTranslate.z = 0.0f;
        }
    }
    if (jnt_no == 0x1E && (m34E0 != 0 || m34E4 != 0)) {
        local_38.y = m34E4;
        local_38.z = m34E0;
    }
    if (local_38.x != 0 || local_38.y != 0 || local_38.z != 0) {
        m34C6 = m34C6 | 1;
        m3658 = *param_3;
        if (local_38.x != 0 || local_38.y != 0) {
            local_20 = *param_3;
            JMAEulerToQuat(local_38.x, local_38.y, 0, &afStack_30);
            mDoMtx_QuatConcat(&local_20, &afStack_30, param_3);
        }
        if (local_38.z != 0) {
            local_20 = *param_3;
            JMAEulerToQuat(0, 0, local_38.z, &afStack_30);
            mDoMtx_QuatConcat(&local_20, &afStack_30, param_3);
        }
    }
    if ((checkUpperGuardAnime() && mCurProc != daPyProc_BACK_JUMP_e) ||
        checkGrabAnime() ||
        m_anm_heap_upper[UPPER_MOVE0_e].mIdx == LKANM_BCK_ATNBOKO ||
        m_anm_heap_upper[UPPER_MOVE0_e].mIdx == LKANM_BCK_ATNHAM ||
        checkUpperReadyThrowAnime())
    {
        if (jnt_no == 0) {
            m3648 = *param_3;
        } else if (jnt_no == 1) {
            mDoMtx_copy(J3DSys::mCurrentMtx, root_mtx);
            mDoMtx_quat(mDoMtx_stack_c::now, &m3648);
            mDoMtx_stack_c::inverse();
            mDoMtx_concat(J3DSys::mCurrentMtx, mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        } else if (jnt_no == 0x1D) {
            mDoMtx_copy(root_mtx, J3DSys::mCurrentMtx);
        }
    }
    return true;
}

/* 80103A88-80103AAC       .text daPy_jointBeforeCallback__FUlUsP16J3DTransformInfoP10Quaternion */
static BOOL daPy_jointBeforeCallback(u32 userArea, u16 jnt_no, J3DTransformInfo* param_2, Quaternion* param_3) {
    return reinterpret_cast<daPy_lk_c*>(userArea)->jointBeforeCB(jnt_no, param_2, param_3);
}

/* 80103AAC-80103C1C       .text jointAfterCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
BOOL daPy_lk_c::jointAfterCB(int jnt_no, J3DTransformInfo* param_2, Quaternion* param_3) {
    if (m34C6 != 0) {
        if ((m34C6 & 1) != 0) {
            *param_3 = m3658;
        }
        if ((m34C6 & 2) != 0) {
            *param_2 = m3668;
        }
        m34C6 = 0;
    }
    if (jnt_no == 0x22) {
        mDoMtx_copy(mpCLModel->getAnmMtx(0x22), mFootData[1].field_0x088[2]);
    } else if (jnt_no == 0x27) {
        mDoMtx_copy(mpCLModel->getAnmMtx(0x27), mFootData[0].field_0x088[2]);
    } else if (jnt_no == 0x20) {
        mDoMtx_copy(mpCLModel->getAnmMtx(0x20), mFootData[1].field_0x088[0]);
    } else if (jnt_no == 0x21) {
        mDoMtx_copy(mpCLModel->getAnmMtx(0x21), mFootData[1].field_0x088[1]);
    } else if (jnt_no == 0x25) {
        mDoMtx_copy(mpCLModel->getAnmMtx(0x25), mFootData[0].field_0x088[0]);
    } else if (jnt_no == 0x26) {
        mDoMtx_copy(mpCLModel->getAnmMtx(0x26), mFootData[0].field_0x088[1]);
    }
    return true;
}

/* 80103C1C-80103C40       .text daPy_jointAfterCallback__FUlUsP16J3DTransformInfoP10Quaternion */
static BOOL daPy_jointAfterCallback(u32 userArea, u16 jnt_no, J3DTransformInfo* param_2, Quaternion* param_3) {
    return reinterpret_cast<daPy_lk_c*>(userArea)->jointAfterCB(jnt_no, param_2, param_3);
}

/* 80103C40-80103EE4       .text jointCB0__9daPy_lk_cFi */
BOOL daPy_lk_c::jointCB0(int param_1) {
    static f32 guard_rate = 0.0f;

    if (checkEquipAnime()) {
        if (!checkModeFlg(ModeFlg_00000001)) {
            if (param_1 == 1 || param_1 == 0xD) {
                m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
            } else if (param_1 == 4 || param_1 == 0x1c) {
                m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
            }
        }
    } else if (checkUpperReadyAnime() ||
               checkUpperAnime(LKANM_BCK_ROPETHROW) ||
               (mCurProc != daPyProc_GRAB_WAIT_e && checkGrabAnime()))
    {
        if (param_1 == 0xF) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
        } else if (param_1 == 0x1C) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        }
    } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
               !checkShipNotNormalMode())
    {
        if (param_1 == 0xF) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        } else if (param_1 == 0x1C) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
        }
    } else if (checkUpperGuardAnime()) {
        if (param_1 == 0 || param_1 == 0xD) {
            if (param_1 == 0) {
                guard_rate = m_pbCalc[PART_UPPER_e]->getRatio(2);
            }
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        } else if (param_1 == 4 || param_1 == 0x1C) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, guard_rate);
        }
    } else if (dComIfGp_checkPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e) &&
               (mCurProc != daPyProc_TACT_PLAY_e || mProcVar0.m3570 != 0))
    {
        if (param_1 == 4) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        } else if (param_1 == 8) {
            m_pbCalc[PART_UPPER_e]->setRatio(1, 1.0f);
            m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
        } else if (param_1 == 0xC) {
            m_pbCalc[PART_UPPER_e]->setRatio(1, 0.0f);
        }
    }
    return true;
}

/* 80103EE4-80103F28       .text daPy_jointCallback0__FP7J3DNodei */
static BOOL daPy_jointCallback0(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        i_this->jointCB0(jntNo);
    }
    return TRUE;
}

/* 80103F28-80104178       .text jointCB1__9daPy_lk_cFv */
BOOL daPy_lk_c::jointCB1() {
    if (m_old_fdata->getOldFrameFlg() == false) {
        return false;
    }

    J3DTransformInfo* trans_info;
    Quaternion* quaternion;
    trans_info = m_old_fdata->getOldFrameTransInfo(0x21);
    quaternion = m_old_fdata->getOldFrameQuaternion(0x21);
    mDoMtx_stack_c::ZrotS(mFootData[1].field_0x008);
    mDoMtx_stack_c::revConcat(mpCLModel->getAnmMtx(0x20));
    mpCLModel->setAnmMtx(0x20, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(trans_info->mTranslate.x, trans_info->mTranslate.y, trans_info->mTranslate.z);
    mDoMtx_stack_c::quatM(quaternion);
    trans_info++;
    quaternion++;
    mDoMtx_stack_c::ZrotM(mFootData[1].field_0x00A);
    mpCLModel->setAnmMtx(0x21, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(trans_info->mTranslate.x, trans_info->mTranslate.y, trans_info->mTranslate.z);
    mDoMtx_stack_c::quatM(quaternion);
    trans_info++;
    quaternion++;
    mDoMtx_stack_c::ZrotM(mFootData[1].field_0x002);
    mpCLModel->setAnmMtx(0x22, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(trans_info->mTranslate.x, trans_info->mTranslate.y, trans_info->mTranslate.z);
    mDoMtx_stack_c::quatM(quaternion);
    mpCLModel->setAnmMtx(0x23, mDoMtx_stack_c::get());

    trans_info = m_old_fdata->getOldFrameTransInfo(0x26);
    quaternion = m_old_fdata->getOldFrameQuaternion(0x26);
    mDoMtx_stack_c::ZrotS(mFootData[0].field_0x008);
    mDoMtx_stack_c::revConcat(mpCLModel->getAnmMtx(0x25));
    mpCLModel->setAnmMtx(0x25, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(trans_info->mTranslate.x, trans_info->mTranslate.y, trans_info->mTranslate.z);
    mDoMtx_stack_c::quatM(quaternion);
    trans_info++;
    quaternion++;
    mDoMtx_stack_c::ZrotM(mFootData[0].field_0x00A);
    mpCLModel->setAnmMtx(0x26, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(trans_info->mTranslate.x, trans_info->mTranslate.y, trans_info->mTranslate.z);
    mDoMtx_stack_c::quatM(quaternion);
    trans_info++;
    quaternion++;
    mDoMtx_stack_c::ZrotM(mFootData[0].field_0x002);
    mpCLModel->setAnmMtx(0x27, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(trans_info->mTranslate.x, trans_info->mTranslate.y, trans_info->mTranslate.z);
    mDoMtx_stack_c::quatM(quaternion);
    mpCLModel->setAnmMtx(0x28, mDoMtx_stack_c::get());

    return true;
}

/* 80104178-801041B4       .text daPy_jointCallback1__FP7J3DNodei */
static BOOL daPy_jointCallback1(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->jointCB1();
    }
    return TRUE;
}

static mDoExt_offCupOnAupPacket l_offCupOnAupPacket1;
static mDoExt_offCupOnAupPacket l_offCupOnAupPacket2;
static mDoExt_onCupOffAupPacket l_onCupOffAupPacket1;
static mDoExt_onCupOffAupPacket l_onCupOffAupPacket2;

/* 801041B4-801041EC       .text setAnimeHeap__9daPy_lk_cFP12JKRSolidHeap */
JKRHeap* daPy_lk_c::setAnimeHeap(JKRSolidHeap* animeHeap) {
    animeHeap->freeAll();
    return mDoExt_setCurrentHeap(animeHeap);
}

/* 801041EC-80104240       .text setItemHeap__9daPy_lk_cFv */
JKRHeap* daPy_lk_c::setItemHeap() {
    if (!checkResetFlg0(daPyRFlg0_UNK4000)) {
        mCurrItemHeapIdx ^= 1;
        onResetFlg0(daPyRFlg0_UNK4000);
    }
    return setAnimeHeap(mpItemHeaps[mCurrItemHeapIdx]);
}

/* 80104240-80104280       .text setBlurPosResource__9daPy_lk_cFUs */
void daPy_lk_c::setBlurPosResource(u16 index) {
    JKRReadIdxResource(mSwBlur.mpPosBuffer, sizeof(Vec) * 2 * 0x300, index, dComIfGp_getAnmArchive());
}

/* 80104280-80104364       .text getItemAnimeResource__9daPy_lk_cFUs */
J3DAnmTransform* daPy_lk_c::getItemAnimeResource(u16 index) {
    JKRReadIdxResource(m_item_bck_buffer, 0x1000, index, dComIfGp_getAnmArchive());
    JKRHeap* oldHeap = setAnimeHeap(mpItemAnimeHeap);
    mDoExt_transAnmBas* bas = new mDoExt_transAnmBas(NULL);
    J3DAnmLoaderDataBase::setResource(bas, m_item_bck_buffer);
    mDoExt_setCurrentHeap(oldHeap);
    return bas;
}

/* 80104364-801043F0       .text getAnimeResource__9daPy_lk_cFP14daPy_anmHeap_cUsUl */
J3DAnmTransform* daPy_lk_c::getAnimeResource(daPy_anmHeap_c* anmHeap, u16 index, u32 bufferSize) {
    J3DAnmTransform* bck;
    JKRReadIdxResource(anmHeap->m_buffer, bufferSize, index, dComIfGp_getAnmArchive());
    JKRHeap* oldHeap = setAnimeHeap(anmHeap->mpAnimeHeap);
    bck = static_cast<J3DAnmTransform*>(J3DAnmLoaderDataBase::load(anmHeap->m_buffer));
    mDoExt_setCurrentHeap(oldHeap);
    anmHeap->mIdx = index;
    anmHeap->field_0x2 = -1;
    return bck;
}

/* 801043F0-801044E8       .text getUnderUpperAnime__9daPy_lk_cFPC15daPy_anmIndex_cPP15J3DAnmTransformPP15J3DAnmTransformiUl */
void daPy_lk_c::getUnderUpperAnime(const daPy_anmIndex_c* anmIndex, J3DAnmTransform** pUnderBck, J3DAnmTransform** pUpperBck, int r7, u32 bufferSize) {
    if (m_anm_heap_under[r7].mIdx != anmIndex->mUnderBckIdx) {
        *pUnderBck = getAnimeResource(&m_anm_heap_under[r7], anmIndex->mUnderBckIdx, bufferSize);
    } else {
        *pUnderBck = getNowAnmPackUnder((daPy_UNDER)r7);
    }
    if (anmIndex->mUnderBckIdx != anmIndex->mUpperBckIdx) {
        if (bufferSize == 0xB400) {
            bufferSize = 0x4800;
        }
        if (m_anm_heap_upper[r7].mIdx != anmIndex->mUpperBckIdx) {
            *pUpperBck = getAnimeResource(&m_anm_heap_upper[r7], anmIndex->mUpperBckIdx, bufferSize);
        } else {
            *pUpperBck = getNowAnmPackUpper((daPy_UPPER)r7);
        }
    } else {
        *pUpperBck = NULL;
        m_anm_heap_upper[r7].mIdx = -1;
    }
}

/* 801044E8-80104564       .text setTextureAnimeResource__9daPy_lk_cFP16J3DAnmTexPatterni */
void daPy_lk_c::setTextureAnimeResource(J3DAnmTexPattern* btp, int r31) {
    btp->searchUpdateMaterialID(mpCLModelData);
    mpAnmTexPatternData = btp;
    m3530 = r31;
    u16 material_num = btp->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        m_texNoAnms[i].setAnmTexPattern(btp);
    }
}

/* 80104564-80104600       .text loadTextureAnimeResource__9daPy_lk_cFUli */
J3DAnmTexPattern* daPy_lk_c::loadTextureAnimeResource(u32 btpIdx, BOOL isDemo) {
    J3DAnmTexPattern* btp;
    if (isDemo) {
        JKRReadIdResource(m_tex_anm_heap.m_buffer, 0x1000, btpIdx, dComIfGp_getLkDemoAnmArchive());
    } else {
        JKRReadIdxResource(m_tex_anm_heap.m_buffer, 0x1000, btpIdx, dComIfGp_getAnmArchive());
    }
    JKRHeap* oldHeap = setAnimeHeap(m_tex_anm_heap.mpAnimeHeap);
    btp = static_cast<J3DAnmTexPattern*>(J3DAnmLoaderDataBase::load(m_tex_anm_heap.m_buffer));
    mDoExt_setCurrentHeap(oldHeap);
    return btp;
}

/* 80104600-801046CC       .text checkBossBgm__9daPy_lk_cFv */
BOOL daPy_lk_c::checkBossBgm() {
    u32 mainBgm = mDoAud_checkPlayingMainBgmFlag();
    u32 subBgm = mDoAud_checkPlayingSubBgmFlag();
    if (mainBgm == JA_BGM_GOMA || mainBgm == JA_BGM_GOMA_2 || mainBgm == JA_BGM_KINDAN_BOSS ||
        mainBgm == JA_BGM_DK_BATTLE || mainBgm == JA_BGM_MJ_TOWER_BATTLE || mainBgm == JA_BGM_BST_BATTLE ||
        mainBgm == JA_BGM_RANE_BATTLE || mainBgm == JA_BGM_PAST_GOMA_2 || mainBgm == JA_BGM_BIG_POW ||
        mainBgm == JA_BGM_PAST_BIG_POW || mainBgm == JA_BGM_PAST_BKM || mainBgm == JA_BGM_PAST_GOMA ||
        mainBgm == JA_BGM_PAST_RANE || mainBgm == JA_BGM_GANON_BATTLE || mainBgm == JA_BGM_BGN_KUGUTSU ||
        mainBgm == JA_BGM_BGN_TARABA || mainBgm == JA_BGM_BGN_HAYAMUSHI || subBgm == JA_BGM_MBOSS ||
        subBgm == JA_BGM_MBOSS_S || subBgm == JA_BGM_P_GANON_1 || subBgm == JA_BGM_P_GANON_2 ||
        subBgm == JA_BGM_DIOCTA_BATTLE || subBgm == JA_BGM_DIOCTA_2)
    {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 801046CC-801046EC       .text checkMabaAnimeBtp__9daPy_lk_cFi */
BOOL daPy_lk_c::checkMabaAnimeBtp(int anmIdx) {
    if (anmIdx >= LKANM_BTP_TMABAA && anmIdx <= LKANM_BTP_TMABAJ) {
        return TRUE;
    }
    return FALSE;
}

/* 801046EC-80104A08       .text checkNormalFace__9daPy_lk_cFv */
u16 daPy_lk_c::checkNormalFace() {
    if (mCurProc == daPyProc_SHIP_CRANE_e) {
        return daPyFace_TMABAA;
    }
    if (mFace != daPyFace_UNKNOWN) {
        return mFace;
    }
    if (checkResetFlg0(daPyRFlg0_UNK40000)) {
        return daPyFace_TMABAG;
    }
    if (checkUpperAnime(LKANM_BCK_GRABWAITB)) {
        return daPyFace_TMABAJ_TEYORIME;
    }
    if (checkUpperAnime(LKANM_BCK_GRABWAIT)) {
        return daPyFace_TMABAE;
    }
    if (daPy_dmEcallBack_c::checkCurse() || checkRestHPAnime()) {
        return daPyFace_TMABAF;
    }
    if (checkNoDamageMode()) {
        return daPyFace_TMABAC;
    }
    if (daPy_dmEcallBack_c::checkFlame()) {
        return daPyFace_TDAMDASH;
    }
    if (checkNoResetFlg1(daPyFlg1_CONFUSE)) {
        return daPyFace_TMABAH_TABEKOBE;
    }
    if (checkNoResetFlg0(daPyFlg0_HEAVY_STATE)) {
        return daPyFace_TMABAH;
    }
    if (checkNoResetFlg1(daPyFlg1_UNK1000000) && !checkModeFlg(ModeFlg_00000001)) {
        return daPyFace_TDASHKAZE;
    }
    if (checkUpperReadyAnime() || checkNoResetFlg1(daPyFlg1_UNK400) ||
        (mpAttnActorLockOn != NULL && fopAcM_GetGroup(mpAttnActorLockOn) == fopAc_ENEMY_e) ||
        checkEquipHeavyBoots() ||
        mEquipItem == dItem_SKULL_HAMMER_e)
    {
        return daPyFace_TMABAC;
    }
    if (checkBossBgm()) {
        return daPyFace_TMABAC;
    }
    if (checkAttentionLock()) {
        return daPyFace_TMABACB;
    }
    if (mEquipItem != daPyItem_NONE_e) {
        return daPyFace_TMABAB;
    }
    if (m_anm_heap_under[UNDER_MOVE1_e].mIdx == LKANM_BCK_WALKSLOPE) {
        return daPyFace_TMABAC;
    }
    if (mCurProc == daPyProc_MOVE_e) {
        f32 fVar2;
        if (m3580 == 8) {
            fVar2 = 1.0f;
        } else {
            fVar2 = cM_scos(m34E2);
        }
        if ((mVelocity * fVar2) / mMaxNormalSpeed >= 0.9f) {
            return daPyFace_TMABACC;
        }
    }
    if (mCurProc == daPyProc_WAIT_e && !dComIfGp_event_runCheck()) {
        f32 dVar7 = cM_rnd();
        if (((m_tex_anm_heap.mIdx == LKANM_BTP_TMABAA || m_tex_anm_heap.mIdx == LKANM_BTP_TMABAB) && dVar7 < 0.01f) ||
            (m_tex_anm_heap.mIdx == LKANM_BTP_TMABACC && dVar7 >= 0.01f))
        {
            return daPyFace_TMABACC;
        }
        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_DUNGEON_e ||
            dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SUBDUNGEON_e)
        {
            return daPyFace_TMABAB;
        }
    }
    return daPyFace_TMABAA;
}

/* 80104A08-80104E08       .text setTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setTextureAnime(u16 param_1, int param_2) {
    BOOL bVar3;
    f32 dVar9;

    if (param_1 == 0) {
        param_1 = checkNormalFace();
    }
    u16 btp_idx = mTexAnmIndexTable[param_1].mBtpIdx;
    u16 btk_idx = mTexAnmIndexTable[param_1].mBtkIdx;
    if ((param_1 < 0x13 &&
         checkMabaAnimeBtp(m_tex_anm_heap.mIdx)) &&
        mFace == daPyFace_UNKNOWN)
    {
        param_2 = m3530;
        bVar3 = true;
    } else {
        bVar3 = false;
    }
    if (m_tex_anm_heap.mIdx == btp_idx) {
        if (mFace == daPyFace_UNKNOWN && !checkModeFlg(ModeFlg_00000100 | ModeFlg_00000400)) {
            m3530 = param_2;
        }
    } else {
        m_tex_anm_heap.mIdx = btp_idx;
        if (m_tex_anm_heap.field_0x2 == 0xFFFF && m_tex_anm_heap.field_0x4 == 0xFFFF) {
            setTextureAnimeResource(loadTextureAnimeResource(btp_idx, 0), param_2);
        }
    }
    dVar9 = cM_rnd();
    if (m_tex_scroll_heap.mIdx != btk_idx) {
        if (bVar3 && checkModeFlg(ModeFlg_00000001) &&
            daPy_matAnm_c::m_maba_flg != 0 &&
            !dComIfGp_event_runCheck() &&
            mpAttnActorLockOn == NULL &&
            btk_idx == LKANM_BTK_TMABA)
        {
            if (daPy_matAnm_c::getMabaTimer() == 0) {
                if (dVar9 < 0.44f) {
                    btk_idx = LKANM_BTK_TMABA;
                } else {
                    param_2 = 0;
                    if (dVar9 < 0.51f) {
                        btk_idx = LKANM_BTK_TEUP;
                    } else if (dVar9 < 0.58f) {
                        btk_idx = LKANM_BTK_TEDW;
                    } else if (dVar9 < 0.65f) {
                        btk_idx = LKANM_BTK_TEL;
                    } else if (dVar9 < 0.72f) {
                        btk_idx = LKANM_BTK_TER;
                    } else if (dVar9 < 0.79f) {
                        btk_idx = LKANM_BTK_TEDL;
                    } else if (dVar9 < 0.86f) {
                        btk_idx = LKANM_BTK_TEDR;
                    } else if (dVar9 < 0.93f) {
                        btk_idx = LKANM_BTK_TEUR;
                    } else {
                        btk_idx = LKANM_BTK_TEUL;
                    }
                }
                m_tex_scroll_heap.mIdx = btk_idx;
                if (m_tex_scroll_heap.field_0x2 == 0xFFFF &&
                    m_tex_scroll_heap.field_0x4 == 0xFFFF)
                {
                    setTextureScrollResource(loadTextureScrollResource(btk_idx, 0), param_2);
                }
                if (btk_idx != LKANM_BTK_TMABA) {
                    daPy_matAnm_c::onMabaFlg();
                }
            }
        } else {
            m_tex_scroll_heap.mIdx = btk_idx;
            if (m_tex_scroll_heap.field_0x2 == 0xFFFF && m_tex_scroll_heap.field_0x4 == 0xFFFF)
            {
                setTextureScrollResource(loadTextureScrollResource(btk_idx, 0), param_2);
            }
        }
    } else if (bVar3 && checkModeFlg(ModeFlg_00000001) && !dComIfGp_event_runCheck() &&
               daPy_matAnm_c::getMabaTimer() == 0 && mpAttnActorLockOn == NULL && btk_idx == LKANM_BTK_TMABA &&
               m_tex_scroll_heap.field_0x2 == 0xFFFF && m_tex_scroll_heap.field_0x4 == 0xFFFF && cM_rnd() < 0.025f)
    {
        if (dVar9 < 0.125f) {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TEUP;
        } else if (dVar9 < 0.25f) {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TEDW;
        } else if (dVar9 < 0.375f) {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TEL;
        } else if (dVar9 < 0.5f) {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TER;
        } else if (dVar9 < 0.625f) {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TEDL;
        } else if (dVar9 < 0.75f) {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TEDR;
        } else if (dVar9 < 0.875f) {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TEUL;
        } else {
            m_tex_scroll_heap.mIdx = LKANM_BTK_TEUR;
        }
        setTextureScrollResource(loadTextureScrollResource(m_tex_scroll_heap.mIdx, 0), 0);
        daPy_matAnm_c::onMabaFlg();
    }
}

/* 80104E08-80104EC8       .text setPriTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setPriTextureAnime(u16 r4, int r30) {
    u16 btpIdx = mTexAnmIndexTable[r4].mBtpIdx;
    u16 btkIdx = mTexAnmIndexTable[r4].mBtkIdx;
    if (m_tex_anm_heap.field_0x2 != btpIdx) {
        m_tex_anm_heap.field_0x2 = btpIdx;
        if (m_tex_anm_heap.field_0x4 == 0xFFFF) {
            setTextureAnimeResource(loadTextureAnimeResource(btpIdx, FALSE), r30);
        }
    }
    if (m_tex_scroll_heap.field_0x2 != btkIdx) {
        m_tex_scroll_heap.field_0x2 = btkIdx;
        if (m_tex_scroll_heap.field_0x4 == 0xFFFF) {
            setTextureScrollResource(loadTextureScrollResource(btkIdx, FALSE), r30);
        }
    }
}

/* 80104EC8-80104F74       .text resetPriTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::resetPriTextureAnime() {
    if (m_tex_anm_heap.field_0x2 != 0xFFFF) {
        m_tex_anm_heap.field_0x2 = 0xFFFF;
        if (m_tex_anm_heap.field_0x4 == 0xFFFF) {
            setTextureAnimeResource(loadTextureAnimeResource(m_tex_anm_heap.mIdx, FALSE), 0);
        }
    }
    if (m_tex_scroll_heap.field_0x2 != 0xFFFF) {
        m_tex_scroll_heap.field_0x2 = 0xFFFF;
        if (m_tex_scroll_heap.field_0x4 == 0xFFFF) {
            setTextureScrollResource(loadTextureScrollResource(m_tex_scroll_heap.mIdx, FALSE), 0);
        }
    }
}

/* 80104F74-80105040       .text setDemoTextureAnime__9daPy_lk_cFUsUsiUs */
void daPy_lk_c::setDemoTextureAnime(u16 btpIdx, u16 btkIdx, int r30, u16 r31) {
    if (m_tex_anm_heap.field_0x4 != btpIdx || m_tex_anm_heap.field_0x6 != r31) {
        m_tex_anm_heap.field_0x4 = btpIdx;
        m_tex_anm_heap.field_0x6 = r31;
        setTextureAnimeResource(loadTextureAnimeResource(btpIdx, TRUE), r30);
    }
    if (m_tex_scroll_heap.field_0x4 != btkIdx || m_tex_scroll_heap.field_0x6 != r31) {
        m_tex_scroll_heap.field_0x4 = btkIdx;
        m_tex_scroll_heap.field_0x6 = r31;
        setTextureScrollResource(loadTextureScrollResource(btkIdx, TRUE), r30);
    }
}

/* 80105040-80105164       .text resetDemoTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::resetDemoTextureAnime() {
    if (m_tex_anm_heap.field_0x4 != 0xFFFF) {
        m_tex_anm_heap.field_0x4 = 0xFFFF;
        m_tex_anm_heap.field_0x6 = 0xFFFF;
        if (m_tex_anm_heap.field_0x2 != 0xFFFF) {
            setTextureAnimeResource(loadTextureAnimeResource(m_tex_anm_heap.field_0x2, FALSE), 0);
        } else if (m_tex_anm_heap.mIdx != 0xFFFF) {
            setTextureAnimeResource(loadTextureAnimeResource(m_tex_anm_heap.mIdx, FALSE), 0);
        } else {
            setTextureAnime(0, 0);
        }
    }

    if (m_tex_scroll_heap.field_0x4 != 0xFFFF) {
        m_tex_scroll_heap.field_0x4 = 0xFFFF;
        m_tex_scroll_heap.field_0x6 = 0xFFFF;
        if (m_tex_scroll_heap.field_0x2 != 0xFFFF) {
            setTextureScrollResource(loadTextureScrollResource(m_tex_scroll_heap.field_0x2, FALSE), 0);
        } else if (m_tex_scroll_heap.mIdx != 0xFFFF) {
            setTextureScrollResource(loadTextureScrollResource(m_tex_scroll_heap.mIdx, FALSE), 0);
        } else {
            setTextureAnime(0, 0);
        }
    }
}

/* 80105164-80105220       .text setTextureScrollResource__9daPy_lk_cFP19J3DAnmTextureSRTKeyi */
void daPy_lk_c::setTextureScrollResource(J3DAnmTextureSRTKey* btk, int r31) {
    btk->searchUpdateMaterialID(mpCLModelData);
    mpTexScrollResData = btk;
    m3532 = r31;
    u16 material_num = btk->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        m_texMtxAnm[i].setAnmTransform(btk);
    }
    daPy_matAnm_c::setMorfFrame(3);
    daPy_matAnm_c::offMabaFlg();
    daPy_matAnm_c::setMabaTimer(75.0f + cM_rndF(30.0f));
}

/* 80105220-801052BC       .text loadTextureScrollResource__9daPy_lk_cFUli */
J3DAnmTextureSRTKey* daPy_lk_c::loadTextureScrollResource(u32 btkIdx, BOOL isDemo) {
    J3DAnmTextureSRTKey* btk;
    if (isDemo) {
        JKRReadIdResource(m_tex_scroll_heap.m_buffer, 0x800, btkIdx, dComIfGp_getLkDemoAnmArchive());
    } else {
        JKRReadIdxResource(m_tex_scroll_heap.m_buffer, 0x800, btkIdx, dComIfGp_getAnmArchive());
    }
    JKRHeap* oldHeap = setAnimeHeap(m_tex_scroll_heap.mpAnimeHeap);
    btk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(m_tex_scroll_heap.m_buffer));
    mDoExt_setCurrentHeap(oldHeap);
    return btk;
}

/* 801052BC-8010552C       .text playTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::playTextureAnime() {
    if (m_tex_anm_heap.field_0x4 != 0xFFFF) {
        if (mCurProc == daPyProc_DEMO_TOOL_e) {
            m3530 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
            m3532 = m3530;
        } else if (m_tex_anm_heap.field_0x6 == 0xFFFE &&
                   checkMabaAnimeBtp(m_tex_anm_heap.field_0x4))
        {
            if (m3530 != 0) {
                m3530++;
                if (m3530 >= mpAnmTexPatternData->getFrameMax()) {
                    m3530 = 0;
                }
            } else {
                if (cM_rnd() < 0.012f) {
                    m3530++;
                }
            }
            m3532 = m3530;
        } else {
            m3530++;
            m3532++;
        }
    } else if (m_tex_anm_heap.field_0x2 != 0xFFFF) {
        if (checkModeFlg(ModeFlg_SWIM)) {
            m3530 = 0;
            m3532 = 0;
        } else {
            m3530 = mFrameCtrlUpper[UPPER_MOVE2_e].getFrame();
            m3532 = m3530;
        }
    } else if (checkModeFlg(ModeFlg_00000400) || m34C3 == 9 || m34C3 == 10) {
        m3530 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
        m3532 = m3530;
    } else if (checkModeFlg(ModeFlg_00000100)) {
        if (m3530 != 0) {
            m3530++;
            if (m3530 >= mpAnmTexPatternData->getFrameMax()) {
                m3530 = 0;
            }
        } else {
            if (cM_rnd() < 0.012f) {
                m3530++;
            }
        }
        if (m_tex_scroll_heap.mIdx == LKANM_BTK_TABEKOBE) {
            m3532++;
            if (m3532 >= mpTexScrollResData->getFrameMax()) {
                m3532 = 0;
            }
        } else {
            m3532 = m3530;
        }
    }
    if (m3530 >= mpAnmTexPatternData->getFrameMax()) {
        if (mpAnmTexPatternData->getFrameMax() == 0) {
            m3530 = 0;
        } else {
            m3530 = mpAnmTexPatternData->getFrameMax();
        }
    }
    if (m3532 >= mpTexScrollResData->getFrameMax()) {
        if (mpTexScrollResData->getFrameMax() == 0) {
            m3532 = 0;
        } else {
            m3532 = mpTexScrollResData->getFrameMax();
        }
    }
}

/* 8010552C-8010558C       .text checkPlayerGuard__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkPlayerGuard() const {
    return mCurProc == daPyProc_CROUCH_DEFENSE_e || checkUpperGuardAnime() || checkGuardSlip();
}

/* 8010558C-801056E4       .text setOutPower__9daPy_lk_cFfsi */
void daPy_lk_c::setOutPower(f32 param_1, s16 param_2, int param_3) {
    f32 fVar1 = m3644;
    if (fVar1 < 0.1f) {
        m3640 = param_2;
        m3644 = param_1;
    } else {
        f32 dVar5 = fVar1 * cM_ssin(m3640) + param_1 * cM_ssin(param_2);
        f32 dVar4 = fVar1 * cM_scos(m3640) + param_1 * cM_scos(param_2);
        m3640 = cM_atan2s(dVar5, dVar4);
        dVar4 = std::sqrtf(dVar5 * dVar5 + dVar4 * dVar4);
        m3644 = dVar4;
    }
    if (param_3 != 0) {
        onNoResetFlg1(daPyFlg1_UNK10000000);
    }
}

/* 801056E4-80105814       .text checkSightLine__9daPy_lk_cFfP4cXyz */
BOOL daPy_lk_c::checkSightLine(f32 param_1, cXyz* param_2) {  
    camera_class* cam = dComIfGp_getCamera(mCameraInfoIdx);
    cXyz* pcVar2 = fopCamM_GetEye_p(cam);
    cXyz local_44 = (*fopCamM_GetCenter_p(cam) - *pcVar2);
    *param_2 = (local_44.normalize() * param_1) + *pcVar2;
    dBgS_LinChk* linChk;
    if (mEquipItem == dItem_BOOMERANG_e) {
        linChk = &mBoomerangLinChk;
    } else {
        linChk = &mRopeLinChk;
    }
    linChk->Set(pcVar2, param_2, this);
    BOOL temp_r3 = dComIfG_Bgsp()->LineCross(linChk);
    if (temp_r3) {
        param_2->set(*linChk->GetCrossP());
    }
    return temp_r3;
}

/* 80105814-80105910       .text setBootsModel__9daPy_lk_cFPP8J3DModel */
void daPy_lk_c::setBootsModel(J3DModel** pBootModels) {
    u16 bootsJointIdx;
    if (checkEquipHeavyBoots()) {
        // TODO: add enum for link's joint numbers
        pBootModels[0]->setAnmMtx(0x01, mpCLModel->getAnmMtx(0x26)); // RlegB_jnt joint
        pBootModels[1]->setAnmMtx(0x01, mpCLModel->getAnmMtx(0x21)); // LlegB_jnt joint
        bootsJointIdx = 2;
    } else {
        bootsJointIdx = 1;
    }
    
    J3DModel* bootModel = pBootModels[0];
    bootModel->setAnmMtx(bootsJointIdx, mpCLModel->getAnmMtx(0x28)); // Rtoe_jnt joint
    bootModel->setAnmMtx(bootsJointIdx+1, mpCLModel->getAnmMtx(0x27)); // Rfoot_jnt joint
    
    bootModel = pBootModels[1];
    bootModel->setAnmMtx(bootsJointIdx, mpCLModel->getAnmMtx(0x23)); // Ltoe_jnt joint
    bootModel->setAnmMtx(bootsJointIdx+1, mpCLModel->getAnmMtx(0x22)); // Lfoot_jnt joint
}

/* 80105910-80106660       .text setItemModel__9daPy_lk_cFv */
s32 daPy_lk_c::setItemModel() {
    f32 fVar1;
    f32 fVar2;
    f32 dVar15;
    f32 dVar16;
    f32 dVar17;

    MtxP pMVar14 = mpCLModel->getAnmMtx(0xD);
    MtxP pMVar13 = mpCLModel->getAnmMtx(0x8);
    MtxP pMVar6 = mpCLModel->getAnmMtx(0xC);
    daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
    if (boko != NULL && mEquipItem == daPyItem_BOKO_e) {
        mDoMtx_stack_c::transS(40.0f, 47.0f, 2.1f);
        mDoMtx_stack_c::XYZrotM(0x3E38, -0x5D4, 0x66F8);
        if (fopAcM_GetParam(boko) == daBoko_c::Type_STALFOS_MACE_e || fopAcM_GetParam(boko) == daBoko_c::Type_DARKNUT_SWORD_e) {
            mDoMtx_stack_c::transM(0.0f, 0.0f, 20.0f);
        } else if (fopAcM_GetParam(boko) == daBoko_c::Type_MOBLIN_SPEAR_e) {
            mDoMtx_stack_c::transM(0.0f, 0.0f, 70.0f);
        } else if (fopAcM_GetParam(boko) == daBoko_c::Type_PGANON_SWORD_e) {
            mDoMtx_stack_c::transM(0.0f, 0.0f, 30.0f);
        }
        mDoMtx_stack_c::revConcat(pMVar13);
        MtxP mtx = mDoMtx_stack_c::now;
        boko->setMatrix(mtx);
    }
    if (mpEquipItemBtk != NULL) {
        dVar16 = mpEquipItemBtk->getFrame();
        if ((dVar16 > 0.0f || cM_rnd() < 0.02f)) {
            dVar16 += 1.0f;
            if (dVar16 >= mpEquipItemBtk->getFrameMax()) {
                dVar16 = 0.0f;
            }
            mpEquipItemBtk->setFrame(dVar16);
        }
    }
    mpPodmsModel->setBaseTRMtx(pMVar14);
    if (mpEquipItemModel != NULL) {
        if (mEquipItem == daPyItem_UNK10A_e) {
            mDoMtx_stack_c::transS(50.0f, -48.0f, -14.0f);
            mDoMtx_stack_c::XYZrotM(-0x33FC, -0x2CC, 0x3519);
            mDoMtx_stack_c::revConcat(dComIfGp_getShipActor()->mpHeadAnm->getModel()->getAnmMtx(0x0A));
            mpEquipItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
        } else if (mEquipItem == daPyItem_UNK104_e) {
            mDoMtx_stack_c::transS(14.5f, 34.5f, 0.0f);
            mDoMtx_stack_c::XYZrotM(0, -0x4000, -0x2AAA);
            mDoMtx_stack_c::revConcat(mpCLModel->getAnmMtx(3));
            mpEquipItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
        } else if (mEquipItem == dItem_TELESCOPE_e) {
            mDoMtx_stack_c::transS(8.0f, 15.0f, 1.0f);
            mDoMtx_stack_c::XYZrotM(-0x4000, 0x4444, -0x41F);
            mDoMtx_stack_c::revConcat(pMVar13);
            mpEquipItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
        } else if (mEquipItem == dItem_HYOI_PEAR_e) {
            if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < 9.0f) {
                mDoMtx_stack_c::transS(-1.5f, -44.0f, 16.0f);
                mDoMtx_stack_c::XYZrotM(-0x6EEE, 0x9BE, 0x368A);
                mDoMtx_stack_c::revConcat(pMVar13);
                mpEquipItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
            } else {
                mpEquipItemModel->setBaseTRMtx(mpCLModel->getAnmMtx(0xF));
            }
        } else if (mEquipItem == dItem_DEKU_LEAF_e || mEquipItem == daPyItem_SWORD_e ||
                   mEquipItem == dItem_WIND_WAKER_e || mEquipItem == dItem_SKULL_HAMMER_e ||
                   mEquipItem == dItem_HOOKSHOT_e || mEquipItem == dItem_TINGLE_TUNER_e ||
                   checkBottleItem(mEquipItem) || checkPhotoBoxItem(mEquipItem))
        {
            mpEquipItemModel->setBaseTRMtx(pMVar13);
            if (mEquipItem == dItem_DEKU_LEAF_e &&
                (mCurProc != daPyProc_FAN_SWING_e && mCurProc != daPyProc_FAN_GLIDE_e))
            {
                setShapeFanLeaf();
            } else if (checkBottleItem(mEquipItem)) {
                if (mpBottleContentsModel != NULL) {
                    if (mEquipItem == dItem_FIREFLY_BOTTLE_e) {
                        cXyz bottleScale; // ?
                        fVar1 =
                            1.0f + 0.1f * cM_ssin(cM_rad2s(
                                              (37.699112f * mpEquipItemBrk->getFrame()) / mpEquipItemBrk->getFrameMax()
                                          ));
                        bottleScale.setall(fVar1);
                        mDoMtx_stack_c::transS(11.0f, 0.0f, 0.0f);
                        mDoMtx_stack_c::revConcat(pMVar13);
                        mpBottleContentsModel->setBaseTRMtx(mDoMtx_stack_c::get());
                        mpBottleContentsModel->setBaseScale(bottleScale);
                        simpleAnmPlay(mpEquipItemBrk);
                    } else {
                        mpBottleContentsModel->setBaseTRMtx(pMVar13);
                    }
                }
                if (mpBottleCapModel != NULL) {
                    mpBottleCapModel->setBaseTRMtx(pMVar13);
                }
            } else if (mEquipItem == dItem_HOOKSHOT_e && boko != NULL) {
                if (fopAcM_GetParam(boko) != daBoko_c::Type_BOKO_STICK_e) {
                    if (fopAcM_GetParam(boko) == daBoko_c::Type_MACHETE_e) {
                        m35EC += 1.0f;
                    } else {
                        m35EC -= 1.0f;
                    }
                    fVar2 = mSwordAnim.getBckAnm()->getFrameMax();
                    fVar1 = m35EC;
                    if (fVar1 < 0.0f) {
                        m35EC = fVar1 + fVar2;
                    } else if (fVar1 >= fVar2) {
                        m35EC = fVar1 - fVar2;
                    }
                }
            } else if (mEquipItem == dItem_WIND_WAKER_e &&
                       mCurProc != daPyProc_TACT_WAIT_e && mpEquipItemBrk != NULL)
            {
                fVar1 = mpEquipItemBrk->getFrame() - 1.0f;
                if (fVar1 < 0.0f) {
                    fVar1 = 0.0f;
                }
                mpEquipItemBrk->setFrame(fVar1);
            }
        } else if (checkBowItem(mEquipItem)) {
            mpEquipItemModel->setBaseTRMtx(pMVar6);
        } else {
            if (mEquipItem == daPyItem_UNK102_e) {
                mpEquipItemModel->setBaseTRMtx(mpCLModel->getAnmMtx(0x4));
            }
        }
        if (mSwordAnim.getBckAnm() != NULL && mCurProc != daPyProc_DEMO_TALISMAN_WAIT_e) {
            mSwordAnim.entry(mpEquipItemModel->getModelData(), m35EC);
            if (mpSwordModel1 != NULL) {
                mSwordAnim.entry(mpSwordModel1->getModelData(), m35EC);
            }
        }
        if (mpParachuteFanMorf != NULL) {
            mpParachuteFanMorf->calc();
        } else {
            mpEquipItemModel->calc();
        }
    }
    mpEquippedSwordModel = mpSwgripmsModel;
    s32 r27;
    if (!checkSwordEquip()) {
        r27 = 0;
        mSwgripmsabBckAnim.entry(mpSwgripmsModel->getModelData(), 0.0f);
        mpTswgripmsabBrk->setFrame(0.0f);
    } else {
        if (checkNormalSwordEquip()) {
            r27 = 1;
            mpEquippedSwordModel = mpSwgripaModel;
        } else if (checkFinalMasterSwordEquip()) {
            r27 = 3;
            mSwgripmsabBckAnim.entry(mpSwgripmsModel->getModelData(), 1.0f);
            mpTswgripmsabBrk->setFrame(1.0f);
            if (mpEquipItemModel != NULL && mEquipItem == daPyItem_SWORD_e) {
                mpEquipItemModel->getModelData()
                    ->getJointNodePointer(0x00)
                    ->getMesh()
                    ->getShape()
                    ->show();
            }
        } else {
            if (dComIfGs_getSelectEquip(0) == dItem_MASTER_SWORD_2_e) {
                mSwgripmsabBckAnim.entry(mpSwgripmsModel->getModelData(), 1.0f);
                r27 = 4;
            } else {
                mSwgripmsabBckAnim.entry(mpSwgripmsModel->getModelData(), 0.0f);
                r27 = 2;
            }
            mpTswgripmsabBrk->setFrame(0.0f);
            if (mpEquipItemModel != NULL && mEquipItem == daPyItem_SWORD_e) {
                mpEquipItemModel->getModelData()
                    ->getJointNodePointer(0x00)
                    ->getMesh()
                    ->getShape()
                    ->hide();
            }
        }
    }
    dVar16 = mpTswgripmsBtk->getFrame();
    if (dVar16 > 0.1f || cM_rnd() < 0.02f) {
        dVar16 += 1.0f;
        if (dVar16 >= mpTswgripmsBtk->getFrameMax()) {
            dVar16 = 0.0f;
        }
        mpTswgripmsBtk->setFrame(dVar16);
    }
    if (mEquipItem == daPyItem_SWORD_e) {
        mpEquippedSwordModel->setBaseTRMtx(pMVar13);
        mDoAud_setLinkSwordType(r27, 1);
    } else {
        mDoMtx_stack_c::transS(-11.25f, 4.5f, 0.45f);
        mDoMtx_stack_c::ZrotM(-0x1C71);
        mDoMtx_stack_c::revConcat(pMVar14);
        mpEquippedSwordModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoAud_setLinkSwordType(r27, 2);
    }
    mpEquippedSwordModel->calc();
    int r27_2;
    if (dComIfGs_getSelectEquip(1) == dItem_MIRROR_SHIELD_e) {
        r27_2 = 2;
        mpEquippedShieldModel = mpShmsModel;
        if (mpTshmsBtk != NULL) {
            dVar16 = mpTshmsBtk->getFrame();
            if ((dVar16 > 0.0f || cM_rnd() < 0.02f)) {
                dVar16 += 1.0f;
                if (dVar16 >= mpTshmsBtk->getFrameMax()) {
                    dVar16 = 0.0f;
                }
                mpTshmsBtk->setFrame(dVar16);
            }
        }
    } else if (dComIfGs_getSelectEquip(1) != dItem_NONE_e) {
        r27_2 = 1;
        mpEquippedShieldModel = mpShaModel;
    } else {
        r27_2 = 0;
        mpEquippedShieldModel = mpShaModel;
    }
    if (mCurProc == daPyProc_DEMO_LAST_COMBO_e) {
        mpEquippedShieldModel->setBaseTRMtx(mpCLModel->getBaseTRMtx());
        mDoAud_setLinkShieldType(r27_2, 1);
    } else if ((mCurProc != daPyProc_DEMO_TOOL_e && mEquipItem == daPyItem_SWORD_e) ||
               (mCurProc == daPyProc_DEMO_TOOL_e && m34D4 == 1) ||
               (checkPlayerGuard() && mEquipItem != dItem_SKULL_HAMMER_e) ||
               mCurProc == daPyProc_GUARD_CRASH_e)
    {
        mpEquippedShieldModel->setBaseTRMtx(pMVar6);
        mDoAud_setLinkShieldType(r27_2, 1);
    } else {
        if (r27_2 == 2) {
            mDoMtx_stack_c::transS(15.5f, 4.75f, -0.2f);
        } else {
            mDoMtx_stack_c::transS(15.5f, 4.75f, 0.0f);
        }
        mDoMtx_stack_c::ZrotM(-0x4000);
        mDoMtx_stack_c::revConcat(pMVar14);
        mpEquippedShieldModel->setBaseTRMtx(mDoMtx_stack_c::get());
        if (r27_2 == 2 && (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_WALK ||
                           m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_WALKS ||
                           m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_DASHS ||
                           m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_DASH))
        {
            MtxP mtx = mDoMtx_stack_c::get();
            dVar16 = mtx[0][3];
            dVar15 = mtx[1][3];
            dVar17 = mtx[2][3];
            u16 uVar10 =
                cM_rad2s((((2*M_PI) * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - 22.0f)) /
                          mFrameCtrlUnder[UNDER_MOVE0_e].getEnd()));
            mDoMtx_stack_c::YrotS(
                (-5500.0f * std::abs(mVelocity / mMaxNormalSpeed) * cM_ssin(uVar10 & 0xFFFF)));
            mDoMtx_stack_c::concat(mpEquippedShieldModel->getBaseTRMtx());
            mDoMtx_stack_c::now[0][3] = dVar16;
            mDoMtx_stack_c::now[1][3] = dVar15;
            mDoMtx_stack_c::now[2][3] = dVar17;
            mpEquippedShieldModel->setBaseTRMtx(mDoMtx_stack_c::get());
        }
        mDoAud_setLinkShieldType(r27_2, 2);
    }
    mAtngshaBck.entry(mpEquippedShieldModel->getModelData(), m35E8);
    mpEquippedShieldModel->calc();
    mpYmsls00Model->setBaseTRMtx(mpEquippedShieldModel->getBaseTRMtx());
    simpleAnmPlay(mpYmsls00Btk);
    if (checkEquipHeavyBoots()) {
        setBootsModel(&mpHbootsModels[0]);
        mDoAud_setLinkBootsType(1);
    } else {
        mDoAud_setLinkBootsType(0);
    }
    if (dComIfGs_getSelectEquip(2) == dItem_POWER_BRACELETS_e) {
        mpPringModel->setAnmMtx(0x1, mpCLModel->getAnmMtx(0x7));
        mpPringModel->setAnmMtx(0x2, mpCLModel->getAnmMtx(0xB));
    }
    return false;
}

/* 80106660-801066DC       .text checkUpperReadyAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkUpperReadyAnime() const {
    return checkBoomerangReadyAnime() || checkBowReadyAnime() || checkRopeReadyAnime() || checkHookshotReadyAnime();
}

/* 801066DC-80106750       .text checkUpperReadyThrowAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkUpperReadyThrowAnime() const {
    return checkBoomerangAnime() || checkBowAnime() || checkRopeAnime() || checkHookshotReadyAnime();
}

/* 80106750-801067D8       .text checkNoCollisionCorret__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNoCollisionCorret() {
    if (checkModeFlg(ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP | ModeFlg_LADDER | ModeFlg_CAUGHT) ||
        mDemo.getDemoType() == 1 ||
        mDemo.getDemoMode() == daPy_demo_c::DEMO_OPEN_TREASURE_e ||
        mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK_030_e ||
        checkResetFlg0(daPyRFlg0_CRAWL_AUTO_MOVE) ||
        eventInfo.checkCommandDoor() ||
        mCurProc == daPyProc_VERTICAL_JUMP_e ||
        mCurProc == daPyProc_CRAWL_END_e ||
        mCurProc == daPyProc_VOMIT_WAIT_e ||
        mCurProc == daPyProc_DEMO_DOOR_OPEN_e ||
        mCurProc == daPyProc_HOOKSHOT_FLY_e)
    {
        return true;
    }
    return false;
}

/* 801067D8-80106BD0       .text setDrawHandModel__9daPy_lk_cFv */
s32 daPy_lk_c::setDrawHandModel() {
    u8 uVar4;
    u8 uVar5;

    mpLhandShape->hide();
    mpRhandShape->hide();
    if (mCurProc == daPyProc_DEMO_TOOL_e) {
        uVar4 = mLeftHandIdx;
        uVar5 = mRightHandIdx;
    } else if (checkGrabAnime() || checkBoomerangThrowAnime() || checkBoomerangCatchAnime()) {
        uVar4 = 0;
        uVar5 = 0;
    } else if (checkHookshotReadyAnime()) {
        uVar4 = 3;
        uVar5 = 0;
    } else if (checkBowReadyAnime()) {
        uVar4 = 3;
        uVar5 = 10;
    } else if (checkBowShootAnime()) {
        uVar4 = 6;
        uVar5 = 10;
    } else if (checkBoomerangReadyAnime()) {
        uVar4 = 0;
        uVar5 = 7;
    } else if (checkBottleItem(mEquipItem) || checkPhotoBoxItem(mEquipItem)) {
        uVar4 = 6;
        uVar5 = mRightHandIdx;
    } else if (checkBowItem(mEquipItem)) {
        uVar4 = mLeftHandIdx;
        uVar5 = 8;
    } else if (mEquipItem == daPyItem_BOKO_e) {
        uVar4 = 3;
        uVar5 = 9;
    } else if (mEquipItem == daPyItem_SWORD_e) {
        uVar4 = 3;
        if (dComIfGs_getSelectEquip(1) != dItem_NONE_e) {
            uVar5 = 8;
        } else {
            uVar5 = mRightHandIdx;
        }
    } else if ((mEquipItem == dItem_GRAPPLING_HOOK_e && !checkModeFlg(ModeFlg_ROPE)) ||
               (mEquipItem == dItem_SKULL_HAMMER_e && mCutType == 0))
    {
        uVar4 = 3;
        uVar5 = 8;
    } else if (mEquipItem == dItem_BOOMERANG_e) {
        uVar4 = 0;
        uVar5 = mRightHandIdx;
    } else if (mEquipItem == dItem_WIND_WAKER_e) {
        uVar4 = 5;
        uVar5 = mRightHandIdx;
    } else if (mEquipItem == dItem_HOOKSHOT_e) {
        uVar4 = 2;
        uVar5 = mRightHandIdx;
    } else if (mEquipItem == dItem_DEKU_LEAF_e) {
        uVar4 = 3;
        uVar5 = mRightHandIdx;
    } else if (mEquipItem == dItem_TELESCOPE_e) {
        uVar4 = 1;
        uVar5 = mRightHandIdx;
    } else {
        if (mEquipItem == daPyItem_NONE_e && checkUpperAnime(LKANM_BCK_TAKEBOTH)) {
            uVar4 = 1;
        } else if (mEquipItem == daPyItem_NONE_e && checkItemEquipAnime()) {
            uVar4 = 0;
        } else {
            uVar4 = mLeftHandIdx;
        }
        if (checkPlayerGuard() || mCurProc == daPyProc_GUARD_CRASH_e) {
            uVar5 = 8;
        } else if (mEquipItem == daPyItem_NONE_e && checkUpperAnime(LKANM_BCK_TAKEBOTH)) {
            uVar5 = 7;
        } else if (mEquipItem == daPyItem_NONE_e && checkItemEquipAnime()) {
            uVar5 = 0;
        } else {
            uVar5 = mRightHandIdx;
        }
    }
    if (checkPlayerGuard()) {
        uVar5 = 8;
    }
    if (uVar4 == 0) {
        mpLhandShape = mpCLModelData->getJointNodePointer(0x8)->getMesh()->getShape();
    } else {
        mpLhandShape =
            mpHandsModel->getModelData()->getJointNodePointer(uVar4)->getMesh()->getShape();
        mpHandsModel->setAnmMtx(uVar4, mpCLModel->getAnmMtx(8));
    }
    mpLhandShape->show();
    if (uVar5 == 0) {
        mpRhandShape = mpCLModelData->getJointNodePointer(0xC)->getMesh()->getShape();
    } else {
        mpRhandShape =
            mpHandsModel->getModelData()->getJointNodePointer(uVar5)->getMesh()->getShape();
        mpHandsModel->setAnmMtx(uVar5, mpCLModel->getAnmMtx(0xC));
    }
    mpRhandShape->show();
    return true;
}

/* 80106BD0-80106C40       .text entryDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::entryDLSetLight(J3DModel* model, u32 param_2) {
    g_env_light.setLightTevColorType(model, &tevStr);
    if (param_2 != 0) {
        dMat_control_c::iceEntryDL(model, -1, NULL);
    } else {
        mDoExt_modelEntryDL(model);
    }
}

/* 80106C40-80106CB0       .text updateDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::updateDLSetLight(J3DModel* model, u32 param_2) {
    g_env_light.setLightTevColorType(model, &tevStr);
    if (param_2 != 0) {
        dMat_control_c::iceUpdateDL(model, -1, NULL);
    } else {
        mDoExt_modelUpdateDL(model);
    }
}

/* 80106CB0-80106D8C       .text hideHatAndBackle__9daPy_lk_cFP11J3DMaterial */
void daPy_lk_c::hideHatAndBackle(J3DMaterial* mtl) {
    for (int i = 0; mtl != NULL; i++) {
        // If NOT frozen, hide materials that were already drawn earlier:
        // * "face"
        // * "ear(2)" (hair)
        // If CaughtShapeHide or wearing casual clothes, hide material:
        // * "ear(3)" (hat)
        if ((!checkFreezeState() && (i == 2 || i == 5)) ||
            (i == 4 && (checkCaughtShapeHide() || checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES))))
        {
            mtl->getShape()->hide();
        } else {
            mtl->getShape()->show();
        }
        mtl = mtl->getNext();
    }
    if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
        // Hide material:
        // * "ear(8)" (belt buckle)
        mpCLModelData->getJointNodePointer(0x29)->getMesh()->getShape()->hide();
    }
}

/* 80106D8C-80106E50       .text drawMirrorLightModel__9daPy_lk_cFv */
void daPy_lk_c::drawMirrorLightModel() {
    if (checkResetFlg0(daPyRFlg0_UNK200000)) {
        mDoMtx_stack_c::transS(l_ms_light_local_start);
        mDoMtx_stack_c::YrotM(-0x8000);
        mDoMtx_stack_c::revConcat(mpEquippedShieldModel->getBaseTRMtx());
#if VERSION == VERSION_DEMO
        mMirrorPacket.update(mDoMtx_stack_c::get(), 0xFF);
#else
        mMirrorPacket.update(mDoMtx_stack_c::get(), 0xFF, 60.0f);
#endif
        dComIfGd_getXluList()->entryImm(&mMirrorPacket, 0xFF);
        updateDLSetLight(mpYmsls00Model, 0);
    }
}

/* 80106E50-80107210       .text drawShadow__9daPy_lk_cFv */
void daPy_lk_c::drawShadow() {
    J3DJoint* link_root_joint = mpCLModelData->getJointNodePointer(0x00);
    MtxP pMVar3 = mpCLModel->getAnmMtx(0);
    cXyz local_30;

    local_30.x = pMVar3[0][3];
    local_30.y = pMVar3[1][3];
    local_30.z = pMVar3[2][3];
    if (checkGrabWear()) {
        if (-G_CM3D_F_INF != mAcch.GetGroundH() && dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
            dComIfGd_setSimpleShadow2(&local_30, mAcch.GetGroundH(), 30.0f, mAcch.m_gnd, 0, 1.0f,
                                      &dDlst_shadowControl_c::mSimpleTexObj);
        }
    } else {
        J3DJoint* pJVar7 = mpCLModelData->getJointNodePointer(0x8);
        pJVar7->getMesh()->getShape()->show();
        mpCLModelData->getJointNodePointer(0xC)->getMesh()->getShape()->show();
        if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
            J3DMaterial* mtl = link_root_joint->getMesh();
            // Hide material:
            // * "ear(3)" (hat)
            for (int i = 0; i < 4; i++) {
                mtl = mtl->getNext();
            }
            mtl->getShape()->hide();
        }
        f32 f31;
        if (checkModeFlg(ModeFlg_HANG)) {
            f31 = mHangGroundH;
        } else {
            f31 = mAcch.GetGroundH();
        }
        f32 f1;
        if (!strcmp(dComIfGp_getStartStageName(), "M_DaiB") ||
            !strcmp(dComIfGp_getStartStageName(), "Xboss2"))
        {
            f1 = 1400.0f;
        } else {
            f1 = m_HIO->mBasic.m.field_0x10;
        }
        int iVar4 = dComIfGd_setShadow(mShadowId, 0, mpCLModel, &local_30, f1, 30.0f, current.pos.y,
                                       f31, mAcch.m_gnd, &tevStr, 0, 1.0f,
                                       &dDlst_shadowControl_c::mSimpleTexObj);
        mShadowId = iVar4;
        if ((u32)mShadowId != 0) {
            if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES) && !checkCaughtShapeHide()) {
                dComIfGd_addRealShadow(mShadowId, mpKatsuraModel);
            }
            if (checkSwordEquip()
#if VERSION == VERSION_DEMO
                && !checkLastDemoSwordNoDraw(1)
#else
                && !checkDemoSwordNoDraw(1)
#endif
            ) {
                dComIfGd_addRealShadow(mShadowId, mpEquippedSwordModel);
            }
            if ((mpEquipItemModel != NULL
#if VERSION == VERSION_DEMO
                && !checkLastDemoSwordNoDraw(0)
#else
                && !checkDemoSwordNoDraw(0)
#endif
            ) &&
                (!checkBowItem(mEquipItem) || !checkPlayerGuard()))
            {
                dComIfGd_addRealShadow(mShadowId, mpEquipItemModel);
            }
            if (dComIfGs_getSelectEquip(1) != dItem_NONE_e
#if VERSION == VERSION_DEMO
                && !checkLastDemoSwordNoDraw(1)
#else
                && !checkDemoShieldNoDraw()
#endif
            ) {
                dComIfGd_addRealShadow(mShadowId, mpEquippedShieldModel);
            }
            fopAc_ac_c* pfVar10;
            if (mActorKeepGrab.getID() != fpcM_ERROR_PROCESS_ID_e) {
                pfVar10 = fopAcM_SearchByID(mActorKeepGrab.getID());
                if (pfVar10 != NULL && fopAcM_GetModel(pfVar10) != NULL) {
                    dComIfGd_addRealShadow(mShadowId, fopAcM_GetModel(pfVar10));
                }
            } else if (mActorKeepEquip.getID() != fpcM_ERROR_PROCESS_ID_e) {
                pfVar10 = fopAcM_SearchByID(mActorKeepEquip.getID());
                if (pfVar10 != NULL && fopAcM_GetModel(pfVar10) != NULL) {
                    dComIfGd_addRealShadow(mShadowId, fopAcM_GetModel(pfVar10));
                }
            }
        }
    }
}

/* 80107210-8010728C       .text offBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::offBodyEffect() {
    if (m334C.getEmitter() != NULL) {
        m334C.getEmitter()->stopDrawParticle();
    }
    if (m336C.getEmitter() != NULL) {
        m336C.getEmitter()->stopDrawParticle();
    }
    if (m32E4.getEmitter() != NULL) {
        m32E4.getEmitter()->stopDrawParticle();
    }
    if (m3460[0].getEmitter() != NULL) {
        m3460[0].getEmitter()->stopDrawParticle();
    }
    if (m3460[1].getEmitter() != NULL) {
        m3460[1].getEmitter()->stopDrawParticle();
    }
}

/* 8010728C-80107308       .text onBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::onBodyEffect() {
    if (m334C.getEmitter() != NULL) {
        m334C.getEmitter()->playDrawParticle();
    }
    if (m336C.getEmitter() != NULL) {
        m336C.getEmitter()->playDrawParticle();
    }
    if (m32E4.getEmitter() != NULL) {
        m32E4.getEmitter()->playDrawParticle();
    }
    if (m3460[0].getEmitter() != NULL) {
        m3460[0].getEmitter()->playDrawParticle();
    }
    if (m3460[1].getEmitter() != NULL) {
        m3460[1].getEmitter()->playDrawParticle();
    }
}

/* 80107308-80108204       .text draw__9daPy_lk_cFv */
BOOL daPy_lk_c::draw() {
    if (mSightPacket.getDrawFlg()) {
        mSightPacket.setSight();
    }
    g_env_light.settingTevStruct(TEV_TYPE_PLAYER, &current.pos, &tevStr);
    if (checkPlayerNoDraw()) {
        offBodyEffect();
        drawMirrorLightModel();
        return TRUE;
    }
    
    if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
        offBodyEffect();
    } else {
        onBodyEffect();
    }
    
    GXColorS10 origFog;
    f32 origFogStartZ, origFogEndZ;
    origFog.r = tevStr.mFogColor.r;
    origFog.g = tevStr.mFogColor.g;
    origFog.b = tevStr.mFogColor.b;
    origFogStartZ = tevStr.mFogStartZ;
    origFogEndZ = tevStr.mFogEndZ;
    if (!checkFreezeState() && mCurProc != daPyProc_ELEC_DAMAGE_e &&
        (daPy_dmEcallBack_c::checkCurse() || checkConfuse() || mDamageWaitTimer > 0)
    ) {
        cXyz sp18;
        mDoLib_pos2camera(&current.pos, &sp18);
        f32 f2 = std::abs(cM_ssin(g_Counter.mTimer * 0x800));
        if (daPy_dmEcallBack_c::checkCurse() || checkConfuse()) {
            tevStr.mFogColor.r = 0x80;
            tevStr.mFogColor.g = 0x00;
            tevStr.mFogColor.b = 0xFF;
        } else {
            tevStr.mFogColor.r = 0xFF;
            tevStr.mFogColor.g = 0x3C;
            tevStr.mFogColor.b = 0x3C;
        }
        tevStr.mFogStartZ = -sp18.z - 200.0f + 200.0f * f2;
        tevStr.mFogEndZ = tevStr.mFogStartZ + 300.0f;
    }
    
    J3DMaterial* mtl;
    u16 material_num = mpAnmTexPatternData->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        u16 matID = mpAnmTexPatternData->getUpdateMaterialID(i);
        if (matID != 0xFFFF) {
            mtl = mpCLModelData->getMaterialNodePointer(matID);
            J3DMaterialAnm* mtlAnm = mtl->getMaterialAnm();
            u8 texNo = mpAnmTexPatternData->getAnmTable()[i].mTexNo;
            mtlAnm->setTexNoAnm(texNo, &m_texNoAnms[i]);
            if (matID != 0xE) {
                // Not mouth (i.e. it's eyeL, eyeR, mayuL, or mayuR)
                mtl = mpCLModelData->getMaterialNodePointer(matID+1);
                mtlAnm = mtl->getMaterialAnm();
                mtlAnm->setTexNoAnm(texNo, &m_texNoAnms[i]);
            }
        }
    }
    
    mpCLModelData->setTexMtxAnimator(mpTexScrollResData, m_texMtxAnm, NULL);
    mpAnmTexPatternData->setFrame(m3530);
    mpTexScrollResData->setFrame(m3532);
    g_env_light.setLightTevColorType(mpCLModel, &tevStr);
    J3DJoint* link_root_joint = mpCLModelData->getJointNodePointer(0x00); // link_root joint
    mpCLModelData->getJointNodePointer(0x08)->getMesh()->getShape()->hide(); // cl_LhandA joint
    mpCLModelData->getJointNodePointer(0x0C)->getMesh()->getShape()->hide(); // cl_RhandA joint
    
    mtl = link_root_joint->getMesh();
    // Show material:
    // * "ear(3)" (hat)
    for (int i = 0; i < 4; i++) {
        mtl = mtl->getNext();
    }
    mtl->getShape()->show();
    
    J3DJoint* cl_eye_joint = mpCLModelData->getJointNodePointer(0x13); // cl_eye joint
    J3DJoint* cl_mayu_joint = mpCLModelData->getJointNodePointer(0x15); // cl_mayu joint
    setDrawHandModel();
    j3dSys.setModel(mpCLModel);
    j3dSys.setTexture(mpCLModelData->getTexture());
    j3dSys.getModel()->unlock();
    
    BOOL r24 = field_0x2b0 <= -85.0f;
    if (r24) {
        for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
            mpZOffBlendShape[i]->hide();
            mpZOffNoneShape[i]->hide();
            mpZOnShape[i]->hide();
        }
        mpCLModelData->getJointNodePointer(0x08)->getMesh()->getShape()->hide(); // cl_LhandA joint
        mpCLModelData->getJointNodePointer(0x0C)->getMesh()->getShape()->hide(); // cl_RhandA joint
        mtl = link_root_joint->getMesh();
        for (int i = 0; mtl != NULL; i++, mtl = mtl->getNext()) {
            if (i != 3) {
                // Hide materials:
                // * "sleeve" (arms and tunic bottom)
                // * "mouth"
                // * "face"
                // * "ear(3)" (hat)
                // * "ear(2)" (hair)
                // * "ear" (torso and ears)
                mtl->getShape()->hide();
            } else {
                // Show materials:
                // * "ear(4)" (legs)
                mtl->getShape()->show();
            }
        }
    } else if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
        for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
            mpZOffBlendShape[i]->hide();
            mpZOffNoneShape[i]->hide();
            mpZOnShape[i]->hide();
        }
        mtl = link_root_joint->getMesh();
        for (int i = 0; mtl != NULL; i++, mtl = mtl->getNext()) {
            if (i != 0 && i != 3) {
                // Hide materials:
                // * "mouth"
                // * "face"
                // * "ear(3)" (hat)
                // * "ear(2)" (hair)
                // * "ear" (torso and ears)
                mtl->getShape()->hide();
            } else {
                // Show materials:
                // * "sleeve" (arms and tunic bottom)
                // * "ear(4)" (legs)
                mtl->getShape()->show();
            }
        }
        mpCLModelData->getJointNodePointer(0x14)->getMesh()->getShape()->hide(); // cl_hana joint
    } else {
        if (!checkFreezeState()) {
            dComIfGd_setListP0();
            l_onCupOffAupPacket2.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOffBlendShape[i]->hide();
                mpZOnShape[i]->hide();
                mpZOffNoneShape[i]->show();
            }
            cl_eye_joint->entryIn();
            cl_mayu_joint->entryIn();
            l_offCupOnAupPacket2.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOffBlendShape[i]->show();
                mpZOffNoneShape[i]->hide();
            }
            cl_eye_joint->entryIn();
            cl_mayu_joint->entryIn();
            mtl = link_root_joint->getMesh();
            for (int i = 0; mtl != NULL; i++, mtl = mtl->getNext()) {
                if (i != 2 && i != 5) {
                    // Hide materials:
                    // * "sleeve" (arms and tunic bottom)
                    // * "mouth"
                    // * "ear(4)" (legs)
                    // * "ear(3)" (hat)
                    // * "ear" (torso and ears)
                    // This leaves the following materials of the link_root joint visible:
                    // * "face"
                    // * "ear(2)" (hair)
                    mtl->getShape()->hide();
                }
            }
            link_root_joint->entryIn();
            if (checkMaskDraw()) {
                entryDLSetLight(mpYamuModel, checkFreezeState());
            }
            j3dSys.setModel(mpCLModel);
            j3dSys.setTexture(mpCLModelData->getTexture());
            hideHatAndBackle(link_root_joint->getMesh());
            l_onCupOffAupPacket1.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOffBlendShape[i]->hide();
                mpZOnShape[i]->show();
                mpZOffNoneShape[i]->hide();
            }
            cl_eye_joint->entryIn();
            cl_mayu_joint->entryIn();
            l_offCupOnAupPacket1.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOnShape[i]->hide();
            }
        } else {
            hideHatAndBackle(link_root_joint->getMesh());
        }
        if (
            (!checkNormalSwordEquip() && dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_FF1_e)
            || checkCaughtShapeHide()
#if VERSION > VERSION_DEMO
            || checkDemoShieldNoDraw()
#endif
        ) {
            mpCLModelData->getJointNodePointer(0x0D)->getMesh()->getShape()->hide(); // cl_podA joint
        } else {
            mpCLModelData->getJointNodePointer(0x0D)->getMesh()->getShape()->show(); // cl_podA joint
        }
    }
    
    dComIfGd_setListP1();
    if (checkFreezeState()) {
        dMat_control_c::iceEntryDL(mpCLModel, -1, NULL);
    } else {
        mDoExt_modelEntryDL(mpCLModel);
    }
    mtl = link_root_joint->getMesh();
    while (mtl != NULL) {
        mtl->getShape()->show();
        mtl = mtl->getNext();
    }
    mpCLModelData->getJointNodePointer(0x14)->getMesh()->getShape()->show(); // cl_hana joint
    mpCLModelData->getJointNodePointer(0x29)->getMesh()->getShape()->show(); // cl_back joint
    if (!r24) {
        entryDLSetLight(mpHandsModel, checkFreezeState());
        if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES) && !checkCaughtShapeHide()
#if VERSION > VERSION_DEMO
            && !dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)
#endif
        ) {
            entryDLSetLight(mpKatsuraModel, checkFreezeState());
        }
        if (checkFreezeState() && checkMaskDraw()) {
            entryDLSetLight(mpYamuModel, checkFreezeState());
        }
        if (dComIfGs_getSelectEquip(2) == dItem_POWER_BRACELETS_e) {
            entryDLSetLight(mpPringModel, checkFreezeState());
        }
        if (checkMasterSwordEquip() && !checkCaughtShapeHide()
#if VERSION > VERSION_DEMO
            && !checkDemoShieldNoDraw()
#endif
        ) {
            updateDLSetLight(mpPodmsModel, checkFreezeState());
        }
    }
    if (checkEquipHeavyBoots()) {
        entryDLSetLight(mpHbootsModels[0], checkFreezeState());
        entryDLSetLight(mpHbootsModels[1], checkFreezeState());
    }
    
    tevStr.mFogColor.r = origFog.r;
    tevStr.mFogColor.g = origFog.g;
    tevStr.mFogColor.b = origFog.b;
    tevStr.mFogStartZ = origFogStartZ;
    tevStr.mFogEndZ = origFogEndZ;
    
    if (!r24) {
        if (mCurProc == daPyProc_CUT_F_e || mCurProc == daPyProc_BT_VERTICAL_JUMP_CUT_e) {
            updateDLSetLight(mpSwordTipStabModel, 0);
        } else if (checkModeFlg(ModeFlg_SWIM) && checkNoResetFlg0(daPyFlg0_UNK100) && !(mCurProc == daPyProc_DEMO_DEAD_e && m34D6 == 0)) {
            GXColor spc;
            GXColor sp8;
            dKy_get_seacolor(&spc, &sp8);
            J3DGXColorS10 sp10;
            sp10.mColor.r = spc.r;
            sp10.mColor.g = spc.g;
            sp10.mColor.b = spc.b;
            int matID = mpSuimenMunyaModel->getModelData()->getMaterialNum() - 1;
            for (; matID >= 0; matID--) {
                mpSuimenMunyaModel->getModelData()->getMaterialNodePointer(matID)->setTevColor(0, &sp10);
            }
            mDoExt_modelUpdateDL(mpSuimenMunyaModel);
        }
        if (!r24 && !dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
            if (checkSwordEquip()
#if VERSION == VERSION_DEMO
                && !checkLastDemoSwordNoDraw(1)
#else
                && !checkDemoSwordNoDraw(1)
#endif
            ) {
                entryDLSetLight(mpEquippedSwordModel, checkFreezeState());
            }
        }
        if (dComIfGs_getSelectEquip(1) != dItem_NONE_e && !checkCaughtShapeHide()
#if VERSION == VERSION_DEMO
            && !checkLastDemoSwordNoDraw(1)
#else
            && !checkDemoShieldNoDraw()
#endif
        ) {
            entryDLSetLight(mpEquippedShieldModel, checkFreezeState());
        }
        dComIfGd_setList();
        drawMirrorLightModel();
        dComIfGd_setListP1();
        
        if (mpBottleContentsModel != NULL) {
            updateDLSetLight(mpBottleContentsModel, 0);
        }
        if (mpEquipItemModel && !checkCaughtShapeHide()
#if VERSION == VERSION_DEMO
            && !checkLastDemoSwordNoDraw(0)
#else
            && !checkDemoSwordNoDraw(0)
#endif
        ) {
            if (!checkBowItem(mEquipItem) || !checkPlayerGuard()) {
                if (mEquipItem == dItem_HOOKSHOT_e) {
                    if (mActorKeepEquip.getActor()) {
                        daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
                        mpEquipItemModel->setAnmMtx(4, hookshot->getMtxTop());
                    }
                }
                entryDLSetLight(mpEquipItemModel, checkFreezeState());
                if (mpSwordModel1 != NULL) {
                    if (checkChanceMode() || checkNoResetFlg1(daPyFlg1_SOUP_POWER_UP) || checkFinalMasterSwordEquip()) {
                        updateDLSetLight(mpSwordModel1, 0);
                    }
                }
            }
        }
        if (mpBottleCapModel != NULL && m355E != 0) {
            updateDLSetLight(mpBottleCapModel, 0);
        }
        
        if (!dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
            f32 frame = mYaura00rBrk.getBrkAnm()->getFrame();
            if (frame > 0.0f) {
                daPy_aura_c* auraEntry = &mMagicArmorAuraEntries[0];
                mYaura00rBrk.entry(auraEntry->getModel()->getModelData(), frame);
                for (int i = 0; i < (s32)ARRAY_SIZE(mMagicArmorAuraEntries); i++, auraEntry++) {
                    mpYaura00Btk->setFrame(auraEntry->getFrame());
                    updateDLSetLight(auraEntry->getModel(), 0);
                }
            }
            frame = mYmgcs00Brk.getBrkAnm()->getFrame();
            if (frame > 0.0f) {
                mYmgcs00Brk.entry(mpYmgcs00Model->getModelData(), frame);
                mDoExt_modelEntryDL(mpYmgcs00Model);
            }
        }
    }
    if (fanWindEffectDraw()) {
        updateDLSetLight(mpYuchw00Model, 0);
    }
    if (fanWindCrashEffectDraw()) {
        updateDLSetLight(mpYbafo00Model, 0);
    }
    dComIfGd_setList();
    if (mCurProc != daPyProc_DEMO_CAUGHT_e && !dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        drawShadow();
    }
    if (mSwBlur.field_0x014 > 0) {
        dComIfGd_entryZSortXluList(&mSwBlur, mSwBlur.field_0x304[0]);
    }
    
    return TRUE;
}

/* 80108204-80108224       .text daPy_Draw__FP9daPy_lk_c */
static BOOL daPy_Draw(daPy_lk_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->draw();
}

/* 80108224-8010841C       .text setAtnList__9daPy_lk_cFv */
void daPy_lk_c::setAtnList() {
    mpAttention = &dComIfGp_getAttention();
    mpAttnEntryA = NULL;
    mpAttnEntryX = NULL;
    mpAttnEntryY = NULL;
    mpAttnEntryZ = NULL;
    mpAttnActorLockOn = NULL;
    mpAttnActorAction = NULL;
    mpAttnActorA = NULL;
    mpAttnActorX = NULL;
    mpAttnActorY = NULL;
    mpAttnActorZ = NULL;
    if (checkAttentionLock()) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
    }
    if (mActorKeepThrow.getActor() != NULL &&
        dComIfGp_checkPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e))
    {
        mpAttnActorLockOn = mActorKeepThrow.getActor();
        mpAttnActorA = mpAttnActorLockOn;
    } else {
        if (checkAttentionLock()) {
            mpAttnEntryA = mpAttention->GetLockonList(0);
            if (mpAttnEntryA != NULL && mpAttention->LockonTruth()) {
                mpAttnActorLockOn = mpAttnEntryA->getActor();
                mpAttnActorA = mpAttnActorLockOn;
                onResetFlg0(daPyRFlg0_ATTENTION_LOCK);
            }
            m34E6 = shape_angle.y;
        }
    }
    if (mpAttnActorLockOn == NULL) {
        mpAttnEntryA = mpAttention->getActionBtnB();
        if (mpAttnEntryA != NULL) {
            mpAttnActorAction = mpAttnEntryA->getActor();
            mpAttnActorA = mpAttnActorAction;
        }
    }
    mpAttnEntryX = mpAttention->getActionBtnX();
    if (mpAttnEntryX != NULL) {
        mpAttnActorX = mpAttnEntryX->getActor();
    }
    mpAttnEntryY = mpAttention->getActionBtnY();
    if (mpAttnEntryY != NULL) {
        mpAttnActorY = mpAttnEntryY->getActor();
    }
    mpAttnEntryZ = mpAttention->getActionBtnZ();
    if (mpAttnEntryZ != NULL) {
        mpAttnActorZ = mpAttnEntryZ->getActor();
    }
}

/* 8010841C-8010848C       .text setActor__16daPy_actorKeep_cFv */
void daPy_actorKeep_c::setActor() {
    if (mID != fpcM_ERROR_PROCESS_ID_e) {
        mActor = fopAcM_SearchByID(mID);
        if (mActor == NULL) {
            mID = fpcM_ERROR_PROCESS_ID_e;
        }
    } else {
        mActor = NULL;
    }
}

/* 8010848C-801084AC       .text setData__16daPy_actorKeep_cFP10fopAc_ac_c */
void daPy_actorKeep_c::setData(fopAc_ac_c* actor) {
    mActor = actor;
    mID = fopAcM_GetID(actor);
}

/* 801084AC-801084C0       .text clearData__16daPy_actorKeep_cFv */
void daPy_actorKeep_c::clearData() {
    mID = fpcM_ERROR_PROCESS_ID_e;
    mActor = NULL;
}

/* 801084C0-80108564       .text setActorPointer__9daPy_lk_cFv */
void daPy_lk_c::setActorPointer() {
    mActorKeepRope.setActor();
    mActorKeepGrab.setActor();
    mActorKeepThrow.setActor();
    mActorKeepEquip.setActor();
    
    if (mEquipItem == daPyItem_BOKO_e) {
        fopAc_ac_c* actor = mActorKeepEquip.getActor();
        if (actor == NULL || !fopAcM_checkCarryNow(actor)) {
            mActorKeepEquip.clearData();
            mEquipItem = daPyItem_NONE_e;
        }
    }
    
    if (m3630 != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* sp8;
        if (!fopAcM_SearchByID(m3630, &sp8)) {
            m3630 = fpcM_ERROR_PROCESS_ID_e;
        }
    }
}

/* 80108564-80108634       .text setTalkStatus__9daPy_lk_cFv */
BOOL daPy_lk_c::setTalkStatus() {
    if (checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000))) {
        return false;
    }
    if (mpAttnEntryA != NULL) {
        if (mpAttnEntryA->mType == fopAc_Attn_TYPE_SPEAK_e ||
            (mpAttnEntryA->mType == fopAc_Attn_TYPE_TALK_e && mpAttnActorA == mpAttnActorLockOn))
        {
            if ((mpAttnActorA->attention_info.flags & fopAc_Attn_TALKFLAG_NOTALK_e)) {
                return false;
            }
            if ((mpAttnActorA->attention_info.flags & fopAc_Attn_TALKFLAG_CHECK_e)) {
                dComIfGp_setDoStatus(dActStts_CHECK_e);
            } else if ((mpAttnActorA->attention_info.flags & fopAc_Attn_TALKFLAG_READ_e)) {
                dComIfGp_setDoStatus(dActStts_READ_e);
            } else if ((mpAttnActorA->attention_info.flags & fopAc_Attn_TALKFLAG_LOOK_e)) {
                dComIfGp_setDoStatus(dActStts_LOOK_e);
            } else {
                dComIfGp_setDoStatus(dActStts_SPEAK_e);
            }
            return true;
        }
    }
    return false;
}

/* 80108634-801086C8       .text setHintActor__9daPy_lk_cFv */
int daPy_lk_c::setHintActor() {
    if (dComIfGp_att_getZHint() != 0 && !dComIfGp_event_runCheck() && mDemo.getDemoType() == 0) {
        setDoButtonQuake();
        onResetFlg0(daPyRFlg0_UNK100);
        dComIfGp_setDoStatus(dActStts_ba_sake__dupe_31);
        return true;
    }
    return false;
}

/* 801086C8-801088E8       .text setDoStatusBasic__9daPy_lk_cFv */
void daPy_lk_c::setDoStatusBasic() {
    f32 fVar1;

    if (dComIfGp_getDoStatus() == dActStts_BLANK_e) {
        int direction = getDirectionFromShapeAngle();
        if (checkHeavyStateOn()) {
            fVar1 = m_HIO->mBasic.m.field_0x1C * m_HIO->mMove.m.field_0x80;
        } else {
            fVar1 = m_HIO->mBasic.m.field_0x1C;
        }
        if (checkAttentionLock() ||
            (mActorKeepThrow.getActor() != NULL && mpAttnActorLockOn == mActorKeepThrow.getActor()))
        {
            if (mStickDistance > 0.05f && direction != DIR_FORWARD) {
                if (mEquipItem == daPyItem_BOKO_e && direction == DIR_BACKWARD) {
                    dComIfGp_setDoStatus(dActStts_THROW_e);
                } else {
                    dComIfGp_setDoStatus(dActStts_JUMP_e);
                }
            } else {
                if (!checkPlayerGuard() && (mEquipItem == daPyItem_BOKO_e ||
                                            mEquipItem == daPyItem_SWORD_e ||
                                            mEquipItem == dItem_SKULL_HAMMER_e))
                {
                    if (mEquipItem == daPyItem_BOKO_e) {
                        dComIfGp_setDoStatus(dActStts_THROW_e);
                    } else {
                        dComIfGp_setDoStatus(dActStts_UNK43);
                    }
                } else if (mEquipItem == daPyItem_BOKO_e) {
                    dComIfGp_setDoStatus(dActStts_THROW_e);
                } else {
                    dComIfGp_setDoStatus(dActStts_ATTACK_e);
                }
            }
        } else if (checkNoUpperAnime() && mEquipItem != daPyItem_NONE_e &&
                   checkModeFlg(ModeFlg_00000004) && mStickDistance <= fVar1)
        {
            if (mEquipItem == daPyItem_BOKO_e) {
                dComIfGp_setDoStatus(dActStts_THROW_e);
            } else {
                dComIfGp_setDoStatus(dActStts_PUT_AWAY_e);
            }
        } else if (mStickDistance > fVar1) {
            if (mEquipItem == daPyItem_BOKO_e) {
                dComIfGp_setDoStatus(dActStts_THROW_e);
            } else {
                dComIfGp_setDoStatus(dActStts_ATTACK_e);
            }
        }
    }
}

/* 801088E8-80108A9C       .text setDoStatus__9daPy_lk_cFv */
void daPy_lk_c::setDoStatus() {
    if (setHintActor()) {
        return;
    }
    
    if (mpAttnActorLockOn == NULL && mpAttnEntryA == NULL) {
        if (checkResetFlg0(daPyRFlg0_UNK8)) {
            dComIfGp_setRStatus(dActStts_GRAB_e);
            if (mFrontWallType == 7 || mFrontWallType == 8 || mFrontWallType == 9) {
                dComIfGp_setDoStatus(dActStts_CLIMB_e);
            } else if (mFrontWallType == 2) {
                dComIfGp_setDoStatus(dActStts_SIDLE_e);
            }
            return;
        } else if (mFrontWallType == 2) {
            dComIfGp_setDoStatus(dActStts_SIDLE_e);
            return;
        }
    }
    if (mpAttnEntryA != NULL) {
        // TODO: is there an inline for checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) ?
        if ((!checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000))) &&
            (mpAttnEntryA->mType == fopAc_Attn_TYPE_DOOR_e || (mpAttnEntryA->mType == fopAc_Attn_TYPE_TREASURE_e)))
        {
            dComIfGp_setDoStatus(dActStts_OPEN_e);
        } else if ((!checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000))) &&
                   mpAttnEntryA->mType == fopAc_Attn_TYPE_SHIP_e)
        {
            if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                dComIfGp_setDoStatus(dActStts_GET_IN_SHIP_e);
            }
        } else if (mpAttnEntryA->mType == fopAc_Attn_TYPE_CARRY_e) {
            if (!fopAcM_CheckStatus(mpAttnActorA, fopAcStts_CARRY_e)) {
                if (fopAcM_GetName(mpAttnActorA) == PROC_BOKO) {
                    dComIfGp_setDoStatus(dActStts_PICK_UP_e);
                } else {
                    dComIfGp_setDoStatus(dActStts_LIFT_e);
                }
            }
        } else if (!setTalkStatus()) {
            setSpecialBattle(0);
        }
    }
    setDoStatusBasic();
}

/* 80108A9C-80108B08       .text getDirectionFromAngle__9daPy_lk_cFs */
int daPy_lk_c::getDirectionFromAngle(s16 angle) {
    if (abs(angle) > 0x6000) {
        return DIR_BACKWARD;
    } else if (angle >= 0x2000) {
        return DIR_LEFT;
    } else if (angle <= -0x2000) {
        return DIR_RIGHT;
    } else {
        return DIR_FORWARD;
    }
}

/* 80108B08-80108B38       .text getDirectionFromShapeAngle__9daPy_lk_cFv */
int daPy_lk_c::getDirectionFromShapeAngle() {
    return getDirectionFromAngle(m34E8 - shape_angle.y);
}

/* 80108B38-80108B68       .text getDirectionFromCurrentAngle__9daPy_lk_cFv */
int daPy_lk_c::getDirectionFromCurrentAngle() {
    return getDirectionFromAngle(m34E8 - current.angle.y);
}

/* 80108B68-80108D80       .text setNormalSpeedF__9daPy_lk_cFffff */
void daPy_lk_c::setNormalSpeedF(f32 param_1, f32 param_2, f32 param_3, f32 param_4) {
    s16 uVar2;
    f32 dVar6;
    f32 dVar10;

    if (dComIfGp_event_runCheck() || checkHeavyStateOn() || checkGrabWear()) {
        dVar10 = mMaxNormalSpeed * mStickDistance;
    } else {
        dVar10 = mStickDistance * (mMaxNormalSpeed * mStickDistance);
    }
    if (mDemo.getDemoMode() == daPy_demo_c::DEMO_KEEP_e || getSlidePolygon() != NULL) {
        return;
    }
    if (mAcch.ChkWallHit()) {
        uVar2 = 0;
        dBgS_AcchCir* pdVar4 = &mAcchCir[0];
        for (int i = 0; i < 3; i++, pdVar4++) {
            if (pdVar4->ChkWallHit()) {
                uVar2 = (current.angle.y + 0x8000) - pdVar4->GetWallAngleY();
                break;
            }
        }
        if (abs(uVar2) < 0x4000) {
            dVar10 *= (1.0f - cM_scos(uVar2) * m_HIO->mBasic.m.field_0x14);
        }
    }
    f32 temp_f3;
    if (dVar10 < mVelocity) {
        f32 temp_f0 = mVelocity - dVar10;
        if (temp_f0 > param_3) {
            temp_f3 = param_3;
        } else {
            temp_f3 = temp_f0;
        }
        if (temp_f3 < param_4) {
            temp_f3 = param_4;
        }
        param_1 = 0.0f;
        dVar6 = dVar10;
    } else {
        temp_f3 = param_3;
        dVar6 = 0.0f;
    }
    if (!cM3d_IsZero(param_1)) {
        mVelocity += param_1;
        if (mVelocity > dVar10) {
            mVelocity = dVar10;
        }
    } else {
        cLib_addCalc(&mVelocity, dVar6, param_2, temp_f3, param_4);
    }
}

/* 80108D80-8010959C       .text posMoveFromFootPos__9daPy_lk_cFv */
void daPy_lk_c::posMoveFromFootPos() {
    if (m_old_fdata->getOldFrameFlg() == false) {
        m34BC = 2;
        speedF = 0.0f;
        static const Vec rtoe_pos_offset = {-14.05f, 0.0f, 5.02f};
        static const Vec rheel_pos_offset = {-10.85f, 0.0f, -6.52f};
        mFootData[0].field_0x018 = rtoe_pos_offset;
        mFootData[0].field_0x00C = rheel_pos_offset;
        mFootData[1].field_0x018.x = -rtoe_pos_offset.x;
        mFootData[1].field_0x018.y = rtoe_pos_offset.y;
        mFootData[1].field_0x018.z = rtoe_pos_offset.z;
        mFootData[1].field_0x00C.x = -rheel_pos_offset.x;
        mFootData[1].field_0x00C.y = rheel_pos_offset.y;
        mFootData[1].field_0x00C.z = rheel_pos_offset.z;
        return;
    }

    cXyz spB0[2];
    cXyz sp98[2];
    mDoMtx_concat(m37B4, mpCLModel->getAnmMtx(0x22), mDoMtx_stack_c::get());
    mDoMtx_stack_c::multVec(&l_toe_pos, &spB0[1]);
    mDoMtx_stack_c::multVec(&l_heel_pos, &sp98[1]);
    mDoMtx_concat(m37B4, mpCLModel->getAnmMtx(0x27), mDoMtx_stack_c::get());
    mDoMtx_stack_c::multVec(&l_toe_pos, &spB0[0]);
    mDoMtx_stack_c::multVec(&l_heel_pos, &sp98[0]);
    mDoMtx_concat(m37B4, mpCLModel->getAnmMtx(0x1E), mDoMtx_stack_c::get());
    MtxP r26 = mDoMtx_stack_c::get();
    f32 f31 = cM_ssin(m34E0);
    f32 f30 = cM_scos(m34E0);
    f32 sp0C[2];
    cXyz sp80[2];
    for (int i = 0; i < 2; i++) {
        sp80[i] = sp98[i] + spB0[i];
        sp80[i] *= 0.5f;
        f32 f2 = r26[1][3] + f30 * (sp80[i].y - r26[1][3]);
        sp0C[i] = f2 + f31 * (sp80[i].z - r26[2][3]);
    }
    if (sp0C[0] < sp0C[1]) {
        m34BC = 0;
    } else {
        m34BC = 1;
    }
    cXyz sp7C;
    cXyz sp68;
    sp68 = spB0[m34BC] - mFootData[m34BC].field_0x018;
    f32 f31_2 = sp68.absXZ();
    if (m3598 < 1.0f && std::abs(m35B4 - mStickDistance) < 0.2f) {
        f31_2 = ((f31_2 * 0.3f) + 0.7f * m359C);
    }
    sp7C.z = mVelocity * (1.0f - m3598);
    if (mVelocity < 0.0f) {
        sp7C.z -= (f31_2 * m3598);
    } else {
        sp7C.z += (f31_2 * m3598);
    }
    s16 r3;
    if (!mAcch.ChkGroundHit() || !dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd) || m3580 == 8) {
        r3 = 0;
    } else {
        r3 = getGroundAngle(&mAcch.m_gnd, current.angle.y);
    }
    sp7C.z *= cM_scos(r3);
    if (r3 < 0) {
        sp7C.z *= 0.85f;
    }
    if (std::abs(sp7C.z) < 0.05f) {
        speedF = 0.0f;
        speed.x = 0.0f;
        speed.z = 0.0f;
    } else {
        speedF = sp7C.z;
        if (mCurProc == daPyProc_SWIM_MOVE_e) {
            u16 r3 =
                cM_rad2s(M_PI * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() / mFrameCtrlUnder[UNDER_MOVE0_e].getEnd()));
            f32 f30;
            f30 = std::abs(cM_scos(r3 & 0xFFFF));
            f32 f1 =
                ((speedF * (1.0f - m_HIO->mSwim.m.field_0x60)) + m_HIO->mSwim.m.field_0x60 * (speedF * f30)) /
                (1.0f + (m_HIO->mSwim.m.field_0x7C * getSwimTimerRate()));
            speed.x = f1 * cM_ssin(current.angle.y);
            speed.z = f1 * cM_scos(current.angle.y);
        } else if (mCurProc != daPyProc_CUT_ROLL_e || !dComIfGp_event_runCheck() ||
                   checkPlayerDemoMode() || mDemo.getDemoMode() == daPy_demo_c::DEMO_CUT_ROLL_e)
        {
            speed.x = speedF * cM_ssin(current.angle.y);
            speed.z = speedF * cM_scos(current.angle.y);
        } else {
            speed.x = 0.0f;
            speed.z = 0.0f;
        }
    }
    m36AC = m36A0;
    if (!checkModeFlg(
            // Note: These flags combine into 0x11612832.
            ModeFlg_MIDAIR | ModeFlg_WHIDE | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP | ModeFlg_CLIMB |
            ModeFlg_PUSHPULL | ModeFlg_LADDER | ModeFlg_CRAWL | ModeFlg_CAUGHT
        ) &&
        !dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 && !checkHeavyStateOn() &&
        mCurrAttributeCode == dBgS_Attr_ICE_e &&
        !checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) && !mAcch.ChkWallHit() &&
        mAcch.ChkGroundHit())
    {
        cLib_addCalc(&m36A0.x, 0.0f, 0.03f, 100.0f, 0.5f);
        cLib_addCalc(&m36A0.z, 0.0f, 0.03f, 100.0f, 0.5f);
        m36A0 += (mOldSpeed - speed) * 0.75f;
        speed += (mOldSpeed - speed) * 0.25f;
    } else {
        m36A0.x = 0.0f;
        m36A0.z = 0.0f;
    }
    m36A0.y = 0.0f;
    setBeltConveyerPower();
    setWindAtPower();
    f32 f1 = speed.y;
    if (checkHeavyStateOn()) {
        speed.y += gravity * 2.25f;
        if (speed.y < (maxFallSpeed * 1.5f)) {
            speed.y = maxFallSpeed * 1.5f;
        }
    } else {
        speed.y += gravity;
        if (speed.y < maxFallSpeed) {
            speed.y = maxFallSpeed;
        }
    }
    if (speed.y <= 0.0f && f1 > 0.0f) {
        m35F0 = current.pos.y;
    }
    current.pos += speed;
    for (int i = 0; i < 2; i++) {
        mFootData[i].field_0x018 = spB0[i];
        mFootData[i].field_0x00C = sp98[i];
    }
    m359C = f31_2;
}

/* 8010959C-80109E80       .text posMove__9daPy_lk_cFv */
void daPy_lk_c::posMove() {
    mDoExt_MtxCalcAnmBlendTblOld* pmVar10 = m_pbCalc[PART_UNDER_e];
    cXyz sp8C = m3700;
    J3DAnmTransform* pJVar5 = pmVar10->getAnmTransform(0);
    J3DTransformInfo spB8;
    pJVar5->getTransform(0, &spB8);
    pJVar5 = pmVar10->getAnmTransform(1);
    if (pJVar5 != NULL) {
        J3DTransformInfo sp98;
        pJVar5->getTransform(0, &sp98);
        f32 fVar2 = pmVar10->getRatio(1);
        f32 fVar4 = 1.0f - fVar2;
        spB8.mTranslate.x = spB8.mTranslate.x * fVar4 + sp98.mTranslate.x * fVar2;
        spB8.mTranslate.y = spB8.mTranslate.y * fVar4 + sp98.mTranslate.y * fVar2;
        spB8.mTranslate.z = spB8.mTranslate.z * fVar4 + sp98.mTranslate.z * fVar2;
    }
    J3DTransformInfo* pJVar11 = m_old_fdata->getOldFrameTransInfo(0);
    f32 dVar15 = cM_ssin(shape_angle.y);
    f32 dVar14 = cM_scos(shape_angle.y);
    cXyz sp80;
    cXyz sp74;
    if (m34C2 == 11) {
        sp80 = current.pos - old.pos;
        pJVar11->mTranslate.x -= (-dVar15 * sp80.z) + (dVar14 * sp80.x);
        pJVar11->mTranslate.y -= sp80.y;
        pJVar11->mTranslate.z -= (dVar14 * sp80.z) + (dVar15 * sp80.x);
    } else if (m34C2 == 10) {
        sp80.set(
            spB8.mTranslate.x - pJVar11->mTranslate.x,
            spB8.mTranslate.y - pJVar11->mTranslate.y,
            spB8.mTranslate.z - pJVar11->mTranslate.z
        );
        sp74.x = (dVar15 * sp80.z) + (dVar14 * sp80.x);
        sp74.y = sp80.y;
        sp74.z = (dVar14 * sp80.z) - (dVar15 * sp80.x);
        current.pos -= sp74;
        old.pos -= sp74;
        pJVar11->mTranslate.x = spB8.mTranslate.x;
        pJVar11->mTranslate.y = spB8.mTranslate.y;
        pJVar11->mTranslate.z = spB8.mTranslate.z;
    } else if (m34C2 == 2 || m34C2 == 6) {
        pJVar11->mTranslate.x = spB8.mTranslate.x;
        pJVar11->mTranslate.z = spB8.mTranslate.z;
        if (m34C2 == 6) {
            pJVar11->mTranslate.y = spB8.mTranslate.y;
        }
    } else if (m34C2 == 4) {
        m3700.x = 0.0f;
        m3700.z = 0.0f;
        sp8C.x = 0.0f;
        sp8C.z = 0.0f;
        sp8C.y = spB8.mTranslate.y;
        pJVar11->mTranslate.x = 0.0f;
        pJVar11->mTranslate.z = 0.0f;
        pJVar11->mTranslate.y = spB8.mTranslate.y;
        m35E0 = spB8.mTranslate.y;
        m34C2 = 5;
    } else if (m34C2 == 7 || m34C2 == 3) {
        sp8C.x = spB8.mTranslate.x;
        sp8C.y = spB8.mTranslate.y;
        sp8C.z = spB8.mTranslate.z;
        if (m34C2 == 7) {
            m34C2 = 5;
        } else {
            m34C2 = 1;
        }
    }
    m3700 = spB8.mTranslate;
    posMoveFromFootPos();
    if (!checkNoCollisionCorret()) {
        current.pos += *mStts.GetCCMoveP();
        if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0) {
            if (!checkNoResetFlg1(daPyFlg1_UNK10000000) || !checkHeavyStateOn()) {
                current.pos.x += m3644 * cM_ssin(m3640);
                current.pos.z += m3644 * cM_scos(m3640);
            }
            if (mWhirlId != fpcM_ERROR_PROCESS_ID_e) {
                fopAc_ac_c* local_110 = fopAcM_SearchByID(mWhirlId);
                if (local_110 != NULL) {
                    cXyz sp68 = current.pos - local_110->current.pos;
                    s16 iVar7 = cM_atan2s(sp68.x, sp68.z) + 0x5000;
                    cLib_chaseF(&m3610, 40.0f, 5.0f);
                    current.pos.x += m3610 * cM_ssin(iVar7);
                    current.pos.z += m3610 * cM_scos(iVar7);
                    f32 dVar13 = sp68.absXZ();
                    if (dVar13 < 500.0f) {
                        startRestartRoom(5, 0xC9, -1.0f, 0);
                    }
                } else {
                    m3610 = 0.0f;
                }
            } else {
                m3610 = 0.0f;
            }
            if (mAcch.ChkGroundHit() && dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
                s16 uVar8 = getGroundAngle(&mAcch.m_gnd, 0);
                current.pos.z += m36A0.z * cM_scos(uVar8);
                uVar8 = getGroundAngle(&mAcch.m_gnd, 0x4000);
                current.pos.x += m36A0.x * cM_scos(uVar8);
            }
            current.pos += m36B8;
            if (mCurProc != daPyProc_FAN_GLIDE_e) {
                current.pos.x += m3730.x;
                current.pos.z += m3730.z;
            }
        }
    } else if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 && daPy_getPlayerActorClass() == this &&
               mCurProc == daPyProc_HANG_MOVE_e)
    {
        f32 dVar13 = mStts.GetCCMoveP()->absXZ();
        if (dVar13 > 1.0f) {
            if ((s16)(cM_atan2s(mStts.GetCCMoveP()->x, mStts.GetCCMoveP()->z) - shape_angle.y) >= 0) {
                current.pos.x += dVar13 * cM_scos(shape_angle.y);
                current.pos.z -= dVar13 * cM_ssin(shape_angle.y);
            } else {
                current.pos.x -= dVar13 * cM_scos(shape_angle.y);
                current.pos.z += dVar13 * cM_ssin(shape_angle.y);
            }
        }
    }
    m3644 = 0.0f;
    mStts.GetCCMoveP()->x = mStts.GetCCMoveP()->y = mStts.GetCCMoveP()->z = 0.0f;
    if (m34C2 == 1 || m34C2 == 8 || m34C2 == 9 || m34C2 == 5) {
        cXyz sp5C;
        if (m34C2 == 1 || m34C2 == 5) {
            sp5C = m3700 - sp8C;
        } else {
            sp5C = sp8C - m3700;
        }
        current.pos.x += (sp5C.z * dVar15) + (sp5C.x * dVar14);
        current.pos.z += (sp5C.z * dVar14) - (sp5C.x * dVar15);
        if (m34C2 == 5) {
            current.pos.y += sp5C.y;
        }
    }
}

/* 80109E80-80109ED8       .text setShapeAngleToAtnActor__9daPy_lk_cFv */
void daPy_lk_c::setShapeAngleToAtnActor() {
    if (mpAttnActorLockOn != NULL) {
        s16 targetAngle = cLib_targetAngleY(&current.pos, &mpAttnActorLockOn->eyePos);
        cLib_addCalcAngleS(&shape_angle.y, targetAngle, 2, 0x2000, 0x800);
    }
}

/* 80109ED8-80109F4C       .text cancelItemUpperReadyAnime__9daPy_lk_cFv */
BOOL daPy_lk_c::cancelItemUpperReadyAnime() {
    if (dComIfGp_getDoStatus() == dActStts_RETURN_e && doTrigger()) {
        seStartOnlyReverb(JA_SE_CANCEL_1);
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        procWait_init();
        return true;
    }
    return false;
}

/* 80109F4C-8010A204       .text checkBodyAngleX__9daPy_lk_cFs */
s16 daPy_lk_c::checkBodyAngleX(s16 param_1) {
    cXyz sp38;
#if VERSION <= VERSION_JPN
    cXyz sp5C;
    cXyz sp50;
#endif
    cXyz sp2C;

    mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x2), &sp38);

#if VERSION <= VERSION_JPN
    sp5C = eyePos - sp38;
    mDoMtx_stack_c::ZXYrotS(param_1 - mBodyAngle.x, shape_angle.y, 0);
    mDoMtx_stack_c::YrotM(-shape_angle.y);
    mDoMtx_stack_c::multVec(&sp5C, &sp50);
    sp2C = sp50 + sp38;
#else
    static Vec top_vec = {0.0f, 70.0f, 0.0f};
    if (param_1 >= 0) {
        top_vec.z = 25.0f;
    } else {
        top_vec.z = -25.0f;
    }
    mDoMtx_stack_c::transS(sp38);
    mDoMtx_stack_c::ZXYrotM(param_1, shape_angle.y, 0);
    mDoMtx_stack_c::multVec(&top_vec, &sp2C);
#endif

    mLinkLinChk.Set(&sp38, &sp2C, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        cXyz local_4c = (mLinkLinChk.GetCross() - sp38);
#if VERSION <= VERSION_JPN
        f32 f1 = (cM_ssin(param_1) * local_4c.abs()) / sp50.abs();
#else
        f32 f1 = (cM_ssin(param_1) * local_4c.abs()) / std::sqrtf(SQUARE(70.0f) + SQUARE(25.0f));
#endif
        if (f1 > 1.0f) {
            f1 = 1.0f;
        } else if (f1 < -1.0f) {
            f1 = -1.0f;
        }
        f32 f2 = std::sqrtf(1.0f - (f1 * f1));
        param_1 = cM_atan2s(f1, f2);
    }
    return param_1;
}

/* 8010A204-8010A2F4       .text setBodyAngleToCamera__9daPy_lk_cFv */
BOOL daPy_lk_c::setBodyAngleToCamera() {
    BOOL bVar1;
    s16 local_16;
    s16 local_18;

    if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x10) != 0) {
        bVar1 = dCam_getBody()->CalcSubjectAngle(&local_16, &local_18);
        if (bVar1 != 0) {
            shape_angle.y = local_18;
            current.angle.y = local_18;
#if VERSION <= VERSION_JPN
            mBodyAngle.x = checkBodyAngleX(local_16);
#else
            mBodyAngle.x = checkBodyAngleX(mBodyAngle.x);
            s16 sVar2 = mBodyAngle.x;
            mBodyAngle.x = checkBodyAngleX(local_16);
            if (mBodyAngle.x != local_16) {
                mBodyAngle.x = sVar2;
            }
#endif
        } else {
            camera_class* cam = dComIfGp_getCamera(mCameraInfoIdx);
            shape_angle.y = cam->mAngle.y;
            current.angle.y = shape_angle.y;
            mBodyAngle.x = cam->mAngle.x;
        }
        return bVar1;
    }
    return false;
}

/* 8010A2F4-8010A4D4       .text setBodyAngleXReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::setBodyAngleXReadyAnime() {
    s16 sVar3;
    cXyz local_1c;
    cXyz local_28;

    mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x2), &local_1c);
    if (mpAttnActorLockOn != NULL) {
        local_28 = mpAttnActorLockOn->eyePos - local_1c;
        local_28.y = local_28.y - 20.0f;
        if (local_28.abs() < 1.0f) {
            sVar3 = 0;
        } else {
            sVar3 = cM_atan2s(-local_28.y, local_28.absXZ());
            if (sVar3 > 0x2000) {
                sVar3 = 0x2000;
            } else if (sVar3 < -0x2000) {
                sVar3 = -0x2000;
            }
        }
    } else {
        sVar3 = 0;
    }
    cLib_addCalcAngleS(&mBodyAngle.x, sVar3, 4, 0xc00, 0x180);
}

/* 8010A4D4-8010A96C       .text setSpeedAndAngleNormal__9daPy_lk_cFs */
void daPy_lk_c::setSpeedAndAngleNormal(s16 param_1) {
    BOOL bVar2;
    s16 sVar6;
    s16 sVar7;
    f32 dVar11;
    f32 dVar10;
    f32 dVar9;

    if (mStickDistance > 0.05f) {
        bVar2 = false;
        dVar11 = mStickDistance * mStickDistance;
        if (checkHeavyStateOn()) {
            dVar11 *= 1.0f / (m_HIO->mMove.m.field_0x80 * m_HIO->mMove.m.field_0x80);
        }
        if (checkGrabWear()) {
            dVar11 *= 1.0f / (m_HIO->mMove.m.field_0x74 * m_HIO->mMove.m.field_0x74);
        }
        if ((!checkAttentionLock() && cLib_distanceAngleS(m34E8, current.angle.y) > 0x7800) &&
            mCurProc != daPyProc_MOVE_TURN_e)
        {
            if (checkModeFlg(ModeFlg_00000001)) {
                return;
            }
            if (mCurProc == daPyProc_MOVE_e) {
                if ((speedF / mMaxNormalSpeed > m_HIO->mSlip.m.field_0x4) &&
                    getDirectionFromAngle(m34EA - m34DC) == DIR_BACKWARD)
                {
                    return;
                }
                if (speedF / mMaxNormalSpeed <= m_HIO->mSlip.m.field_0x4) {
                    cLib_addCalcAngleS(&current.angle.y, m34E8, m_HIO->mMove.m.field_0x6,
                                       param_1, m_HIO->mMove.m.field_0x4);
                    return;
                }
                bVar2 = true;
            } else {
                cLib_addCalcAngleS(&current.angle.y, m34E8, m_HIO->mMove.m.field_0x6, param_1,
                                   m_HIO->mMove.m.field_0x4);
            }
        } else {
            if (dComIfGp_event_runCheck()) {
                sVar6 = param_1;
                sVar7 = m_HIO->mMove.m.field_0x4;
            } else {
                sVar6 = param_1 * dVar11;
                if (sVar6 < 10) {
                    sVar6 = 10;
                }
                sVar7 = m_HIO->mMove.m.field_0x4 * dVar11;
                if (sVar7 < 1) {
                    sVar7 = 1;
                }
            }
            cLib_addCalcAngleS(&current.angle.y, m34E8, m_HIO->mMove.m.field_0x6, sVar6,
                               sVar7);
        }
        if (!bVar2) {
            dVar9 = cM_scos(m34E8 - current.angle.y);
            if (mVelocity > 0.5f * mMaxNormalSpeed) {
                if (dVar9 < 0.7f) {
                    dVar9 = 0.7f;
                }
            } else if (dVar9 < 0.0f) {
                dVar9 = 0.0f;
            }
            if (dComIfGp_event_runCheck()) {
                dVar9 *= m_HIO->mMove.m.field_0x14 * mStickDistance;
            } else {
                dVar10 = 0.5f - (0.5f * std::abs(mVelocity / mMaxNormalSpeed));
                if (checkHeavyStateOn()) {
                    dVar10 *= m_HIO->mMove.m.field_0x80;
                }
                if (checkGrabWear()) {
                    dVar10 *= m_HIO->mMove.m.field_0x74;
                }
                if (mStickDistance > dVar10) {
                    dVar9 *= m_HIO->mMove.m.field_0x14 * dVar11;
                } else {
                    dVar9 = 0.0f;
                }
            }
        } else {
            dVar9 = 0.0f;
        }
    } else {
        dVar9 = 0.0f;
    }
    if ((!checkAttentionLock() && mCurProc != daPyProc_MOVE_TURN_e) &&
        mStickDistance > 0.05f)
    {
        sVar6 = shape_angle.y;
        cLib_addCalcAngleS(&shape_angle.y, m34E8, m_HIO->mMove.m.field_0x6,
                           (s16)(param_1 << 1), (s16)(m_HIO->mMove.m.field_0x4 << 1));
        sVar7 = current.angle.y;
        if ((s16)(sVar6 - sVar7) * (s16)(shape_angle.y - sVar7) <= 0) {
            shape_angle.y = sVar7;
        }
    }
    setNormalSpeedF(dVar9, m_HIO->mMove.m.field_0x24, m_HIO->mMove.m.field_0x1C,
                    m_HIO->mMove.m.field_0x20);
}

/* 8010A96C-8010AA90       .text setSpeedAndAngleAtn__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtn() {
    s16 sVar1;
    f32 fVar2;

    if (mDirection == DIR_FORWARD) {
        return setSpeedAndAngleNormal(m_HIO->mMove.m.field_0x0);
    } else if (mDirection == DIR_BACKWARD) {
        return setSpeedAndAngleAtnBack();
    } else {
        if (mStickDistance > 0.05f) {
            if (getDirectionFromCurrentAngle() == DIR_BACKWARD) {
                current.angle.y += 0x8000;
                mVelocity *= -1.0f;
            }
            sVar1 = current.angle.y;
            cLib_addCalcAngleS(&current.angle.y, m34E8, m_HIO->mAtnMove.m.field_0x4,
                               m_HIO->mAtnMove.m.field_0x0, m_HIO->mAtnMove.m.field_0x2);
            fVar2 = m_HIO->mAtnMove.m.field_0x8 * mStickDistance *
                    cM_scos(current.angle.y - sVar1);
        } else {
            fVar2 = 0.0f;
        }
    }
    shape_angle.y = m34E6;
    return setNormalSpeedF(fVar2, m_HIO->mAtnMove.m.field_0x18,
                           m_HIO->mAtnMove.m.field_0x10, m_HIO->mAtnMove.m.field_0x14);
}

/* 8010AA90-8010AB84       .text setSpeedAndAngleAtnBack__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtnBack() {
    f32 f1;
    if (mStickDistance > 0.05f) {
        if (getDirectionFromCurrentAngle() == DIR_BACKWARD) {
            current.angle.y += 0x8000;
            mVelocity *= -1.0f;
        }
        s16 origAngleY = current.angle.y;
        cLib_addCalcAngleS(
            &current.angle.y, m34E8,
            m_HIO->mAtnMoveB.m.field_0x4,
            m_HIO->mAtnMoveB.m.field_0x0,
            m_HIO->mAtnMoveB.m.field_0x2
        );
        f1 = (m_HIO->mAtnMoveB.m.field_0x8 * mStickDistance) * cM_scos(current.angle.y - origAngleY);
    } else {
        f1 = 0.0f;
    }
    shape_angle.y = m34E6;
    setNormalSpeedF(
        f1,
        m_HIO->mAtnMoveB.m.field_0x18,
        m_HIO->mAtnMoveB.m.field_0x10,
        m_HIO->mAtnMoveB.m.field_0x14
    );
}

/* 8010AB84-8010AC8C       .text setSpeedAndAngleAtnActor__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtnActor() {
    f32 f1;
    if (mStickDistance > 0.05f) {
        if (getDirectionFromCurrentAngle() == DIR_BACKWARD) {
            current.angle.y += 0x8000;
            mVelocity *= -1.0f;
        }
        s16 origAngleY = current.angle.y;
        cLib_addCalcAngleS(
            &current.angle.y, m34E8,
            m_HIO->mAtnMove.m.field_0x4,
            m_HIO->mAtnMove.m.field_0x0,
            m_HIO->mAtnMove.m.field_0x2
            );
        f1 = (m_HIO->mAtnMove.m.field_0x8 * mStickDistance) * cM_scos(current.angle.y - origAngleY);
    } else {
        f1 = 0.0f;
    }
    setShapeAngleToAtnActor();
    setNormalSpeedF(
        f1,
        m_HIO->mAtnMove.m.field_0x18,
        m_HIO->mAtnMove.m.field_0x10,
        m_HIO->mAtnMove.m.field_0x14
    );
}

/* 8010AC8C-8010ACEC       .text setFrameCtrl__9daPy_lk_cFP12J3DFrameCtrlUcssff */
void daPy_lk_c::setFrameCtrl(J3DFrameCtrl* frameCtrl, u8 attribute, s16 start, s16 end, f32 rate, f32 frame) {
    frameCtrl->setAttribute(attribute);
    frameCtrl->setEnd(end);
    frameCtrl->setRate(rate);
    frameCtrl->setStart(start);
    frameCtrl->setFrame(frame);
    if (rate >= 0.0f) {
        frameCtrl->setLoop(start);
    } else {
        frameCtrl->setLoop(end);
    }
}

/* 8010ACEC-8010AD2C       .text checkAtnWaitAnime__9daPy_lk_cFv */
BOOL daPy_lk_c::checkAtnWaitAnime() {
    if (
        (
            mpAttnActorLockOn != NULL &&
            (
                fopAcM_GetGroup(mpAttnActorLockOn) == fopAc_ENEMY_e ||
                fopAcM_GetName(mpAttnActorLockOn) == PROC_BOOMERANG
            )
        ) ||
        mDemo.getDemoMode() == daPy_demo_c::DEMO_A_WAIT_e
    ) {
        return true;
    }
    return false;
}

/* 8010AD2C-8010B798       .text setBlendMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendMoveAnime(f32 param_1) {
    f32 f1_1;
    if (m3580 == 8) {
        f1_1 = 1.0f;
    } else {
        f1_1 = cM_scos(m34E2);
    }
    f32 f30 = (std::abs(mVelocity * f1_1) / mMaxNormalSpeed);
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE1_e];
    f32 f29;
    f32 f28;
    if (dComIfGp_event_runCheck() || checkPlayerDemoMode()) {
        f29 = m_HIO->mMove.m.field_0x44;
        f28 = m_HIO->mMove.m.field_0x64;
    } else if (checkHeavyStateOn()) {
        f29 = m_HIO->mMove.m.field_0x78;
        f28 = m_HIO->mMove.m.field_0x7C;
    } else {
        f29 = m_HIO->mMove.m.field_0x40;
        f28 = m_HIO->mMove.m.field_0x60;
    }
    daPy_ANM r28 = ANM_WAITS;
    daPy_ANM r27;
    daPy_ANM r26;
    if (checkGrabWear()) {
        r27 = ANM_WALKBARREL;
        r26 = ANM_WALKBARREL;
    } else if (checkHeavyStateOn()) {
        if ((m373C.abs2XZ() > SQUARE(5.0f) &&
                (cLib_distanceAngleS(cM_atan2s(m373C.x, m373C.z), shape_angle.y) >= 0x4000)) ||
            ((checkNoResetFlg1(daPyFlg1_UNK10000000) && m3644 > 5.0f) &&
                cLib_distanceAngleS(m3640, shape_angle.y) >= 0x4000))
        {
            r27 = ANM_WALKHBOOTSKAZE;
            r26 = ANM_WALKHBOOTSKAZE;
            if (!checkNoResetFlg1(daPyFlg1_UNK1000000)) {
                param_1 = m_HIO->mBasic.m.field_0xC;
                onNoResetFlg1(daPyFlg1_UNK1000000);
            }
        } else {
            r27 = ANM_WALKHBOOTS;
            r26 = ANM_WALKHBOOTS;
            if (checkNoResetFlg1(daPyFlg1_UNK1000000)) {
                param_1 = m_HIO->mBasic.m.field_0xC;
                offNoResetFlg1(daPyFlg1_UNK1000000);
            }
        }
    } else if (m3580 != 8 && m34E2 <= -0x11C7) {
        r27 = ANM_WALKSLOPE;
        r26 = ANM_WALKSLOPE;
        if (!checkNoResetFlg1(daPyFlg1_UNK80)) {
            param_1 = m_HIO->mBasic.m.field_0xC;
            onNoResetFlg1(daPyFlg1_UNK80);
        }
    } else {
        r27 = ANM_WALK;
        if ((m3730.abs2XZ() > SQUARE(5.0f) &&
                (cLib_distanceAngleS(cM_atan2s(m3730.x, m3730.z), shape_angle.y) >= 0x4000)) ||
            ((checkNoResetFlg1(daPyFlg1_UNK10000000) && m3644 > 5.0f) &&
                cLib_distanceAngleS(m3640, shape_angle.y) >= 0x4000))
        {
            r26 = ANM_DASHKAZE;
            if (!checkNoResetFlg1(daPyFlg1_UNK1000000)) {
                param_1 = m_HIO->mBasic.m.field_0xC;
                onNoResetFlg1(daPyFlg1_UNK1000000);
            }
        } else {
            r26 = ANM_DASH;
            if (checkNoResetFlg1(daPyFlg1_UNK1000000)) {
                param_1 = m_HIO->mBasic.m.field_0xC;
                offNoResetFlg1(daPyFlg1_UNK1000000);
            }
        }
        if (checkNoResetFlg1(daPyFlg1_UNK80)) {
            param_1 = m_HIO->mBasic.m.field_0xC;
            offNoResetFlg1(daPyFlg1_UNK80);
        }
    }
    BOOL r25 = false;
    f32 f31 = m36A0.abs2XZ();
    f32 f25 = m3730.abs2XZ();
    f32 f1_2 = m36B8.abs2XZ();
    BOOL bVar3;
    if (f31 > f25) {
        if (f31 > f1_2) {
            f1_2 = f31;
        }
        bVar3 = true;
    } else if (f25 > f1_2) {
        f1_2 = f25;
        bVar3 = false;
    } else {
        bVar3 = false;
    }
    if (mStickDistance < 0.05f &&
        ((f1_2 >= 25.0f || ((f1_2 >= 0.09f && ((m34C3 == 9 || m34C3 == 10)))))))
    {
        seStartMapInfo(JA_SE_LK_SLIP_SUS);
        if ((m34C3 != 9 && (bVar3)) || ((m34C3 != 10 && (!bVar3)))) {
            if (bVar3) {
                setSingleMoveAnime(ANM_SLIPICE, m_HIO->mIceSlip.m.field_0x10,
                                   m_HIO->mIceSlip.m.field_0x14,
                                   m_HIO->mIceSlip.m.field_0x0,
                                   m_HIO->mIceSlip.m.field_0x18);
                m34C3 = 9;
            } else {
                setSingleMoveAnime(ANM_WAITQ, m_HIO->mMove.m.field_0x84, 0.0f, -1,
                                   m_HIO->mBasic.m.field_0xC);
                setTextureAnime(0x68, 0);
                m34C3 = 10;
            }
            voiceStart(35);
        }
        if (checkGrabAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        freeGrabItem();
        if (mEquipItem == daPyItem_BOKO_e) {
            deleteEquipItem(FALSE);
        }
        m3598 = 0.0f;
    } else {
        if (m34C3 == 9) {
            param_1 = m_HIO->mBasic.m.field_0xC;
        }
        if (f30 < m_HIO->mMove.m.field_0x2C || checkHeavyStateOn()) {
            if (checkHeavyStateOn()) {
                f25 = f30 / m_HIO->mMove.m.field_0x80;
                if (f25 > 0.55f) {
                    r25 = true;
                }
            } else {
                f25 = f30 / m_HIO->mMove.m.field_0x2C;
            }
            r28 = ANM_WAITS;
            int r24;
            f32 in_f27; // Bug? This variable is uninitialized in some paths. TODO: Look into this.
            #ifdef __clang__
            // Just a quick hack to hide clangd's warning for now.
            in_f27 = 0.0f;
            #endif
            if (checkModeFlg(ModeFlg_00000001)) {
                if (checkAttentionLock()) {
                    if (checkUpperGuardAnime()) {
                        setMoveAnime(0.0f, m_HIO->mAtnMove.m.field_0x24,
                                     m_HIO->mAtnMove.m.field_0x28, ANM_ATNRS, ANM_ATNWRS, 2,
                                     m_HIO->mBasic.m.field_0xC);
                        return;
                    }
                }
                f32 f1 = m3598 = 0.0f;
                r24 = 2;
                if ((checkNoResetFlg1(daPyFlg1_CONFUSE) && mDemo.getDemoType() == 0) &&
                    !dComIfGp_event_runCheck())
                {
                    if (m_anm_heap_under[UNDER_MOVE0_e].mIdx != LKANM_BCK_WAITQ) {
                        setSingleMoveAnime(ANM_WAITQ, m_HIO->mMove.m.field_0x84, f1, -1,
                                           m_HIO->mBasic.m.field_0xC);
                        m34C3 = 2;
                    }
                    return;
                }
                if (shape_angle.y != m34DE && !checkAttentionLock()) {
                    s16 r3 = (s16)(shape_angle.y - m34DE);
                    if (r3 > 0) {
                        r27 = ANM_ATNWLS;
                    } else {
                        r27 = ANM_ATNWRS;
                    }
                    f25 = (0.5f + 0.001f * abs(r3));
                    if (f25 > 1.0f) {
                        f25 = 1.0f;
                    }
                    if (!checkNoResetFlg1(daPyFlg1_UNK800000)) {
                        param_1 = m_HIO->mBasic.m.field_0xC;
                    }
                    onNoResetFlg1(daPyFlg1_UNK800000);
                    f29 = m_HIO->mAtnMove.m.field_0x28;
                } else if (checkRestHPAnime()) {
                    r28 = ANM_WAITB;
                    in_f27 = m_HIO->mMove.m.field_0x3C;
                    if (checkNoResetFlg1(daPyFlg1_UNK800000)) {
                        param_1 = m_HIO->mBasic.m.field_0xC;
                    }
                    offNoResetFlg1(daPyFlg1_UNK800000);
                } else {
                    in_f27 = m_HIO->mMove.m.field_0x38;
                    if (checkNoResetFlg1(daPyFlg1_UNK800000)) {
                        param_1 = m_HIO->mBasic.m.field_0xC;
                    }
                    offNoResetFlg1(daPyFlg1_UNK800000);
                }
            } else {
                m3598 = (1.0f - ((1.0f - f28) * f25));
                r24 = 1;
                in_f27 = m_HIO->mMove.m.field_0x38;
            }
            setMoveAnime(f25, in_f27, f29, r28, r27, r24, param_1);
            if (r28 == ANM_WAITB && (!dComIfGp_event_runCheck() || mDemo.getDemoType() != 3) &&
                mFrameCtrlUnder[UNDER_MOVE0_e].checkPass(15.0f))
            {
                if (dComIfGs_getLife() <= 2) {
                    voiceStart(21);
                } else {
                    voiceStart(20);
                }
            }
        } else if (f30 < m_HIO->mMove.m.field_0x30) {
            f32 f1 = (f30 - m_HIO->mMove.m.field_0x2C) /
                    (m_HIO->mMove.m.field_0x30 - m_HIO->mMove.m.field_0x2C);
            setMoveAnime(f1, f29, m_HIO->mMove.m.field_0x48, r27, r26, 1, param_1);
            m3598 = (f28 * (1.0f - f1));
        } else {
            f32 f1;
            if (f31 >= 169.0f) {
                f1 = 1.7f * m_HIO->mMove.m.field_0x48;
                onResetFlg0(daPyRFlg0_UNK40000);
            } else {
                f1 = m_HIO->mMove.m.field_0x48;
            }
            setMoveAnime(1.0f, f1, f1, r26, r26, 1, param_1);
            m3598 = 0.0f;
        }
    }
    if (f30 >= 0.9f || (r25)) {
        onResetFlg0(daPyRFlg0_UNK10);
    }
    if (!checkModeFlg(ModeFlg_00000001)) {
        if (frameCtrl.checkPass(4.0f)) {
            onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
        } else if (frameCtrl.checkPass(20.0f)) {
            onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
        } else {
            resetFootEffect();
        }
    }
    if (m34C3 != 9 && m34C3 != 10) {
        if (f30 > m_HIO->mMove.m.field_0x34) {
            setHandModel(r26);
        } else if (f30 > 0.0f) {
            setHandModel(r27);
        } else {
            setHandModel(r28);
        }
    }
}

/* 8010B798-8010BB08       .text setBlendAtnBackMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnBackMoveAnime(f32 param_1) {
    f32 fVar1;
    int iVar4;
    f32 dVar6;
    f32 dVar7;

    dVar6 = param_1;
    if (m3580 == 8) {
        fVar1 = 1.0f;
    } else {
        fVar1 = cM_scos(m34E2);
    }
    dVar7 = (std::abs(mVelocity * fVar1) / mMaxNormalSpeed);
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE1_e];
    if (dVar7 < m_HIO->mAtnMoveB.m.field_0x1C) {
        fVar1 = dVar7 / m_HIO->mAtnMoveB.m.field_0x1C;
        if (checkModeFlg(ModeFlg_00000001)) {
            iVar4 = 2;
            m3598 = 0.0f;
        } else {
            iVar4 = 4;
            m3598 = 1.0f;
        }
        setMoveAnime(fVar1, m_HIO->mMove.m.field_0x38, m_HIO->mAtnMoveB.m.field_0x24,
                     ANM_WAITS, ANM_ATNWB, iVar4, param_1);
        if (!checkModeFlg(ModeFlg_00000001)) {
            if (frameCtrl.checkPass(2.0f)) {
                onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
            } else if (frameCtrl.checkPass(12.0f)) {
                onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
            }
        }
    } else if (dVar7 < m_HIO->mAtnMoveB.m.field_0x20) {
        fVar1 = (dVar7 - m_HIO->mAtnMoveB.m.field_0x1C) /
                (m_HIO->mAtnMoveB.m.field_0x20 - m_HIO->mAtnMoveB.m.field_0x1C);
        dVar6 = fVar1;
        setMoveAnime(fVar1, m_HIO->mAtnMoveB.m.field_0x24, m_HIO->mAtnMoveB.m.field_0x28,
                     ANM_ATNWB, ANM_ATNDB, 4, param_1);
        m3598 = 1.0f - dVar6;
        if (frameCtrl.checkPass(5.0f) || frameCtrl.checkPass(15.0f)) {
            onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
        } else if (frameCtrl.checkPass(3.0f) || frameCtrl.checkPass(13.0f)) {
            onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
        }
    } else {
        if (m36A0.abs2XZ() >= SQUARE(7.0f)) {
            fVar1 = 1.9f * m_HIO->mAtnMoveB.m.field_0x28;
            onResetFlg0(daPyRFlg0_UNK40000);
        } else {
            fVar1 = m_HIO->mAtnMoveB.m.field_0x28;
        }
        setMoveAnime(1.0f, fVar1, fVar1, ANM_ATNDB, ANM_ATNDB, 4, dVar6);
        m3598 = 0.0f;
        if (frameCtrl.checkPass(5.0f) || frameCtrl.checkPass(15.0f)) {
            onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
        } else if (frameCtrl.checkPass(3.0f) || frameCtrl.checkPass(13.0f)) {
            onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
        }
    }
    if (dVar7 >= 0.9f) {
        onResetFlg0(daPyRFlg0_UNK10);
    }
    if (!getFootOnGround()) {
        resetFootEffect();
    }
    setHandModel(ANM_ATNDB);
}

/* 8010BB08-8010C010       .text setBlendAtnMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnMoveAnime(f32 f30) {
    s16 r3;
    if (mAcch.ChkGroundHit() || !dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
        r3 = 0;
    } else {
        r3 = getGroundAngle(&mAcch.m_gnd, current.angle.y);
    }
    f32 f31 = std::abs((mVelocity * cM_scos(r3)) / mMaxNormalSpeed);
    int iVar6 = current.angle.y - shape_angle.y;
    f32 f2 = cM_ssin(iVar6);
    f32 fVar4 = cM_scos(iVar6);
    u8 uVar1 = mDirection;
    if (mDemo.getDemoMode() == daPy_demo_c::DEMO_A_WAIT_e) {
        if (mDemo.getParam0() == 1) {
            mDirection = DIR_LEFT;
        } else {
            mDirection = DIR_RIGHT;
        }
    } else if (mStickDistance > 0.05f) {
        if (mpAttnActorLockOn == NULL &&
            (fVar4 <= m_HIO->mAtnMoveB.m.field_0x30 || (fVar4 >= m_HIO->mAtnMoveB.m.field_0x2C)))
        {
            if (fVar4 <= m_HIO->mAtnMoveB.m.field_0x30) {
                mDirection = DIR_BACKWARD;
            } else {
                mDirection = DIR_FORWARD;
            }
        } else {
            if (uVar1 == DIR_BACKWARD || uVar1 == DIR_FORWARD) {
                mDirection = DIR_RIGHT;
                mMaxNormalSpeed = m_HIO->mAtnMove.m.field_0xC;
            }
            if (f2 > 0.0f) {
                mDirection = DIR_LEFT;
            } else if (f2 < 0.0f) {
                mDirection = DIR_RIGHT;
            }
        }
    }
    u8 uVar2 = mDirection;
    if (uVar1 != uVar2) {
        f30 = m_HIO->mBasic.m.field_0xC;
    }
    if (uVar2 == DIR_BACKWARD) {
        mMaxNormalSpeed = m_HIO->mAtnMoveB.m.field_0xC;
        setBlendAtnBackMoveAnime(f30);
    } else if (uVar2 == DIR_FORWARD) {
        mMaxNormalSpeed = m_HIO->mMove.m.field_0x18;
        setBlendMoveAnime(f30);
    } else {
        daPy_ANM dVar8;
        daPy_ANM dVar9;
        if (uVar2 != DIR_RIGHT && uVar2 != DIR_LEFT) {
            mDirection = DIR_RIGHT;
            f30 = m_HIO->mBasic.m.field_0xC;
        }
        J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE1_e];
        f32 f29;
        if (checkHeavyStateOn()) {
            f29 = 0.6f;
        } else {
            f29 = 1.0f;
        }
        if (f31 < m_HIO->mAtnMove.m.field_0x1C) {
            f32 f1 = f31 / m_HIO->mAtnMove.m.field_0x1C;
            if (mDirection == DIR_LEFT) {
                dVar8 = ANM_ATNLS;
                dVar9 = ANM_ATNWLS;
            } else {
                dVar8 = ANM_ATNRS;
                dVar9 = ANM_ATNWRS;
            }
            if (checkModeFlg(ModeFlg_00000001)) {
                iVar6 = 2;
                m3598 = 0.0f;
            } else {
                iVar6 = 4;
                m3598 = 1.0f;
            }
            f32 f2 = m_HIO->mAtnMove.m.field_0x24;
            f32 f3 = m_HIO->mAtnMove.m.field_0x28 * f29;
            setMoveAnime(f1, f2, f3, dVar8, dVar9, iVar6, f30);
        } else {
            if (f31 < m_HIO->mAtnMove.m.field_0x20) {
                f32 f28 = (f31 - m_HIO->mAtnMove.m.field_0x1C) /
                          (m_HIO->mAtnMove.m.field_0x20 - m_HIO->mAtnMove.m.field_0x1C);
                if (mDirection == DIR_LEFT) {
                    dVar8 = ANM_ATNWLS;
                    dVar9 = ANM_ATNDLS;
                } else {
                    dVar8 = ANM_ATNWRS;
                    dVar9 = ANM_ATNDRS;
                }
                f32 f2 = m_HIO->mAtnMove.m.field_0x28 * f29;
                f32 f3 = m_HIO->mAtnMove.m.field_0x2C * f29;
                setMoveAnime(f28, f2, f3, dVar8, dVar9, 4, f30);
                m3598 = 1.0f - (f28 * m3598);
            } else {
                if (mDirection == DIR_LEFT) {
                    dVar9 = ANM_ATNDLS;
                } else {
                    dVar9 = ANM_ATNDRS;
                }
                f32 f2;
                if (m36A0.abs2XZ() >= SQUARE(7.0f)) {
                    f2 = 1.9f * m_HIO->mAtnMove.m.field_0x2C;
                    onResetFlg0(daPyRFlg0_UNK40000);
                } else {
                    f2 = m_HIO->mAtnMove.m.field_0x2C * f29;
                }
                setMoveAnime(1.0f, f2, f2, dVar9, dVar9, 4, f30);
                m3598 = 0.0f;
            }
        }
        if (f31 >= 0.9f) {
            onResetFlg0(daPyRFlg0_UNK10);
        }
        if (!checkModeFlg(ModeFlg_00000001)) {
            if (mDirection == DIR_LEFT) {
                if (frameCtrl.checkPass(2.0f)) {
                    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
                } else if (frameCtrl.checkPass(10.0f)) {
                    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
                } else {
                    resetFootEffect();
                }
            } else {
                if (frameCtrl.checkPass(10.0f)) {
                    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
                } else if (frameCtrl.checkPass(2.0f)) {
                    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
                } else {
                    resetFootEffect();
                }
            }
        }
        setHandModel(dVar9);
    }
}

/* 8010C010-8010C100       .text setAnimeEquipSword__9daPy_lk_cFi */
void daPy_lk_c::setAnimeEquipSword(BOOL r4) {
    if (!checkSwordEquip()) {
        return;
    }
    m3562 = daPyItem_SWORD_e;
    f32 rate = m_HIO->mCut.m.field_0x8;
    f32 start = m_HIO->mCut.m.field_0xC;
    s16 end = m_HIO->mCut.m.field_0x0;
    f32 f3 = m_HIO->mCut.m.field_0x10;
    setActAnimeUpper(LKANM_BCK_REST, UPPER_MOVE2_e, rate, start, end, f3);
    setPriTextureAnime(0x72, 0);
    dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
    if (mActorKeepThrow.getActor() != NULL) {
        daBoomerang_c* boomerang = (daBoomerang_c*)mActorKeepThrow.getActor();
        boomerang->onCancelFlg();
    }
    if (!r4) {
        onNoResetFlg1(daPyFlg1_UNK4000000);
    } else {
        offNoResetFlg1(daPyFlg1_UNK4000000);
    }
}

/* 8010C100-8010C158       .text setAnimeEquipSingleItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeEquipSingleItem(u16 bckIdx) {
    setActAnimeUpper(
        bckIdx, UPPER_MOVE2_e,
        m_HIO->mItem.m.field_0x14,
        m_HIO->mItem.m.field_0x18,
        m_HIO->mItem.m.field_0x2,
        m_HIO->mItem.m.field_0x1C
    );
    setPriTextureAnime(0x74, 0);
}

/* 8010C158-8010C1D4       .text setAnimeEquipItem__9daPy_lk_cFv */
void daPy_lk_c::setAnimeEquipItem() {
    if (mActorKeepThrow.getActor() != NULL) {
        if (getReadyItem() == dItem_BOOMERANG_e) {
            return;
        }
        daBoomerang_c* boomerang = (daBoomerang_c*)mActorKeepThrow.getActor();
        boomerang->onCancelFlg();
    }
    u8 itemNo = getReadyItem();
    m3562 = itemNo;
    dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
    setAnimeUnequipItem(m3562);
}

/* 8010C1D4-8010C284       .text setAnimeUnequipSword__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequipSword() {
    f32 rate;
    f32 start;
    s16 end;
    f32 f3;
    if (checkModeFlg(
        // These combine to: 0x01FD2810
        ModeFlg_WHIDE |
        ModeFlg_ROPE |
        ModeFlg_IN_SHIP |
        ModeFlg_CLIMB |
        ModeFlg_SWIM |
        ModeFlg_00080000 |
        ModeFlg_GRAB |
        ModeFlg_PUSHPULL |
        ModeFlg_LADDER |
        ModeFlg_CROUCH |
        ModeFlg_CRAWL
    ) || dComIfGp_event_runCheck() || checkPlayerDemoMode()) {
        rate = m_HIO->mCut.m.field_0x20;
        start = m_HIO->mCut.m.field_0x24;
        end = m_HIO->mCut.m.field_0x4;
        f3 = m_HIO->mCut.m.field_0x28;
    } else {
        rate = m_HIO->mCut.m.field_0x14;
        start = m_HIO->mCut.m.field_0x18;
        end = m_HIO->mCut.m.field_0x2;
        f3 = m_HIO->mCut.m.field_0x1C;
    }
    
    setActAnimeUpper(LKANM_BCK_REST, UPPER_MOVE2_e, rate, start, end, f3);
    setPriTextureAnime(0x72, 0);
}

/* 8010C284-8010C3C0       .text setAnimeUnequipItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeUnequipItem(u16 i_itemNo) {
    if (i_itemNo == dItem_BOOMERANG_e ||
        i_itemNo == dItem_GRAPPLING_HOOK_e ||
        i_itemNo == dItem_TELESCOPE_e ||
        checkPhotoBoxItem(i_itemNo) ||
        i_itemNo == dItem_HOOKSHOT_e ||
        i_itemNo == dItem_DEKU_LEAF_e ||
        i_itemNo == dItem_TINGLE_TUNER_e ||
        i_itemNo == dItem_WIND_WAKER_e ||
        checkBottleItem(i_itemNo)
    ) {
        setAnimeEquipSingleItem(LKANM_BCK_TAKEL);
    } else if (checkBowItem(i_itemNo)) {
        setAnimeEquipSingleItem(LKANM_BCK_TAKER);
    } else if (i_itemNo == dItem_SKULL_HAMMER_e) {
        f32 rate = m_HIO->mItem.m.field_0x24;
        f32 start = m_HIO->mItem.m.field_0x28;
        s16 end = m_HIO->mItem.m.field_0x4;
        f32 f3 = m_HIO->mItem.m.field_0x2C;
        setActAnimeUpper(LKANM_BCK_TAKEBOTH, UPPER_MOVE2_e, rate, start, end, f3);
    } else {
        f32 rate = m_HIO->mItem.m.field_0x8;
        f32 start = m_HIO->mItem.m.field_0xC;
        s16 end = m_HIO->mItem.m.field_0x0;
        f32 f3 = m_HIO->mItem.m.field_0x10;
        setActAnimeUpper(LKANM_BCK_TAKE, UPPER_MOVE2_e, rate, start, end, f3);
        setPriTextureAnime(0x73, 0);
    }
}

/* 8010C3C0-8010C430       .text setAnimeUnequip__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequip() {
    if (mEquipItem == daPyItem_SWORD_e) {
        setAnimeUnequipSword();
    } else if (mEquipItem == daPyItem_BOKO_e) {
        deleteEquipItem(FALSE);
        m_old_fdata->initOldFrameMorf(5.0f, 0, 0x2A);
    } else {
        setAnimeUnequipItem(mEquipItem);
    }
    m3562 = daPyItem_NONE_e;
}

/* 8010C430-8010C4A4       .text checkBossGomaStage__9daPy_lk_cFv */
BOOL daPy_lk_c::checkBossGomaStage() {
    if (strcmp(dComIfGp_getStartStageName(), "M_DragB") == 0 ||
        strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0)
    {
        return TRUE;
    }
    return FALSE;
}

/* 8010C4A4-8010C4C8       .text checkSingleItemEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkSingleItemEquipAnime() const {
    return checkUpperAnime(LKANM_BCK_TAKEL) ||
        checkUpperAnime(LKANM_BCK_TAKER);
}

/* 8010C4C8-8010C528       .text checkItemEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkItemEquipAnime() const {
    return checkUpperAnime(LKANM_BCK_TAKE) ||
        checkSingleItemEquipAnime() ||
        checkUpperAnime(LKANM_BCK_TAKEBOTH);
}

/* 8010C528-8010C570       .text checkEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkEquipAnime() const {
    return checkUpperAnime(LKANM_BCK_REST) ||
        checkItemEquipAnime();
}

/* 8010C570-8010C71C       .text deleteEquipItem__9daPy_lk_cFi */
void daPy_lk_c::deleteEquipItem(BOOL param_1) {
    fopAc_ac_c* equip_actor = mActorKeepEquip.getActor();
    
    if (param_1 && (mEquipItem != daPyItem_NONE_e && mEquipItem != daPyItem_BOKO_e)) {
        if (mEquipItem == daPyItem_SWORD_e) {
            seStartOnlyReverb(JA_SE_LK_SW_PUTIN_S);
        } else {
            seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        }
    }
    
    if (mEquipItem == daPyItem_SWORD_e) {
        mDoAud_bgmSetSwordUsing(0);
    } else if (mEquipItem == daPyItem_BOKO_e) {
        if (equip_actor != NULL) {
            fopAcM_cancelCarryNow(equip_actor);
        }
    } else if (equip_actor != NULL) {
        fopAcM_delete(equip_actor);
    }
    
    if ((mEquipItem == dItem_GRAPPLING_HOOK_e && checkRopeAnime()) ||
        (mEquipItem == dItem_BOOMERANG_e && checkBoomerangAnime()) ||
        (mEquipItem == dItem_HOOKSHOT_e && checkHookshotReadyAnime()) ||
        (checkBowItem(mEquipItem) && checkBowAnime())
    ) {
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
    }
    
    mActorKeepEquip.clearData();
    mEquipItem = daPyItem_NONE_e;
    mpEquipItemModel = NULL;
    if (mSwordAnim.getBckAnm() != NULL) {
        mSwordAnim.changeBckOnly(NULL);
    }
    mpParachuteFanMorf = NULL;
    mpEquipItemBtk = NULL;
    mpBottleContentsModel = NULL;
    mpBottleCapModel = NULL;
    mpEquipItemBrk = NULL;
    mpSwordBtk = NULL;
    mpSwordModel1 = NULL;
    m3454.end();
    mpSwordTipStabModel = NULL;
    mpCutfBrk = NULL;
    mpCutfBtk = NULL;
    mpCutfBpk = NULL;
    offNoResetFlg1(daPyFlg1_UNK200000);
}

/* 8010C71C-8010C7F4       .text setFallVoice__9daPy_lk_cFv */
void daPy_lk_c::setFallVoice() {
    if (!checkNoResetFlg0(daPyFlg0_NO_FALL_VOICE) &&
        (!checkNoResetFlg0(daPyFlg0_UNK80) || m35D0 < mAcch.GetGroundH() || m3580 == 4 ||
         -G_CM3D_F_INF == mAcch.GetGroundH()) &&
        (m35F0 - current.pos.y > 500.0f))
    {
        if (current.pos.y - mAcch.GetGroundH() >= 100.0f * m_HIO->mFall.m.field_0x14) {
            voiceStart(12);
            onNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
            setTextureAnime(0x56, 0);
        }
    }
}

/* 8010C7F4-8010C854       .text keepItemData__9daPy_lk_cFv */
/* Saves which item the player was holding in their hand so it can be restored later. */
void daPy_lk_c::keepItemData() {
    mKeepItem = mEquipItem;
    
    deleteEquipItem(FALSE);
    
    if (mKeepItem == daPyItem_BOKO_e) {
        mKeepItem = daPyItem_NONE_e;
    } else if (mKeepItem == daPyItem_NONE_e) {
        mKeepItem = daPyItem_UNK10B_e;
    }
}

/* 8010C854-8010C8D4       .text returnKeepItemData__9daPy_lk_cFv */
/* Restores which item the player was holding in their hand. */
void daPy_lk_c::returnKeepItemData() {
    if (mKeepItem == daPyItem_NONE_e) {
        return;
    }
    
    deleteEquipItem(FALSE);
    mEquipItem = mKeepItem;
    mKeepItem = daPyItem_NONE_e;
    
    if (mEquipItem == daPyItem_UNK10B_e) {
        mEquipItem = daPyItem_NONE_e;
    } else if (mEquipItem == daPyItem_SWORD_e) {
#if VERSION == VERSION_DEMO
        setSwordModel();
#else
        setSwordModel(TRUE);
#endif
    } else {
        makeItemType();
    }
}

/* 8010C8D4-8010CB70       .text makeItemType__9daPy_lk_cFv */
void daPy_lk_c::makeItemType() {
    if (mEquipItem == dItem_GRAPPLING_HOOK_e) {
        fopAc_ac_c* rope = (fopAc_ac_c*)fopAcM_fastCreate(PROC_HIMO2, 0, &current.pos);
        mActorKeepEquip.setData(rope);
    } else if (mEquipItem == dItem_HOOKSHOT_e) {
        fopAc_ac_c* hookshot = (fopAc_ac_c*)fopAcM_fastCreate(PROC_HOOKSHOT, 0, &current.pos);
        mActorKeepEquip.setData(hookshot);
        setHookshotModel();
    } else if (mEquipItem == dItem_BOOMERANG_e) {
        fopAc_ac_c* boomerang = (fopAc_ac_c*)fopAcM_fastCreate(PROC_BOOMERANG, 0, &current.pos);
        mActorKeepEquip.setData(boomerang);
    } else if (mEquipItem == dItem_BOMB_BAG_e) {
        fopAc_ac_c* bomb = (fopAc_ac_c*)fopAcM_fastCreate(PROC_BOMB, daBomb_c::prm_make(daBomb_c::STATE_3, false, false), &current.pos);
        mActorKeepGrab.setData(bomb);
        mEquipItem = daPyItem_NONE_e;
        if (mActorKeepGrab.getActor() != NULL) {
            setActAnimeUpper(LKANM_BCK_GRABWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, 5.0f);
            mActivePlayerBombs++;
            fopAcM_setCarryNow(mActorKeepGrab.getActor(), FALSE);
            dComIfGp_setItemBombNumCount(-1);
            m35C8 = 17.0f;
        }
        return;
    } else if (checkBowItem(mEquipItem)) {
        setBowModel();
        return;
    } else if (mEquipItem == dItem_TELESCOPE_e) {
        setScopeModel();
        return;
    } else if (checkPhotoBoxItem(mEquipItem)) {
        setPhotoBoxModel();
        return;
    } else if (mEquipItem == dItem_TINGLE_TUNER_e) {
        setTinkleCeiverModel();
        return;
    } else if (mEquipItem == dItem_DEKU_LEAF_e) {
        setSmallFanModel();
        return;
    } else if (mEquipItem == dItem_WIND_WAKER_e) {
        mEquipItem = dItem_NONE_e;
        setTactModel();
        return;
    } else if (mEquipItem == dItem_SKULL_HAMMER_e) {
        setHammerModel();
        return;
    } else if (mEquipItem == dItem_EMPTY_BOTTLE_e) {
        setBottleModel(mEquipItem);
        return;
    } else {
        return;
    }
    
    if (mActorKeepEquip.getActor() == NULL) {
        mEquipItem = daPyItem_NONE_e;
        offResetFlg0(daPyRFlg0_UNK80);
    }
}

/* 8010CB70-8010CBC8       .text setScopeModel__9daPy_lk_cFv */
void daPy_lk_c::setScopeModel() {
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpEquipItemModel, LINK_BDL_TELESCOPE, 0x37221222);
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8010CBC8-8010CC78       .text setPhotoBoxModel__9daPy_lk_cFv */
void daPy_lk_c::setPhotoBoxModel() {
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpEquipItemModel, LINK_BDL_CAMERA, 0x37221222);
    mDoExt_setCurrentHeap(oldHeap);
    if (mEquipItem == CAMERA) {
        mpEquipItemModel->getModelData()->getJointNodePointer(0x02)->getMesh()->getShape()->hide(); // frash joint
    } else {
        mpEquipItemModel->getModelData()->getJointNodePointer(0x02)->getMesh()->getShape()->show(); // frash joint
    }
}

/* 8010CC78-8010CD34       .text changeDragonShield__9daPy_lk_cFi */
BOOL daPy_lk_c::changeDragonShield(int param_1) {
    if (checkNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD)) {
        offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
        return true;
    } else if (dComIfGs_getMagic() != 0) {
        onNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
        m3548 = m_HIO->mItem.mMagicShield.m.field_0x0;
        mTinkleShieldTimer = 0;
        if (param_1 != 0) {
            dComIfGp_setItemMagicCount(-1);
        }
    } else if (param_1 != 0) {
        seStartSystem(JA_SE_ITEM_TARGET_OUT);
    }
    return true;
}

/* 8010CD34-8010CFB4       .text checkNewItemChange__9daPy_lk_cFUc */
BOOL daPy_lk_c::checkNewItemChange(u8 param_1) {
    u32 uVar4 = dComIfGp_getSelectItem(param_1);

    if (uVar4 == dItem_MAGIC_ARMOR_e) {
        return changeDragonShield(1);
    }
    if (uVar4 == dItem_IRON_BOOTS_e || uVar4 == WATER_BOOTS || uVar4 == dItem_TINGLE_TUNER_e || uVar4 == NORMAL_SAIL ||
        isEsa(uVar4) || isDaizaItem(uVar4) || isEmono(uVar4) || checkBottleItem(uVar4) ||
        (uVar4 >= dItem_FATHER_LETTER_e && uVar4 <= KAISEN_PRESENT2))
    {
        if (mAcch.ChkGroundHit() && (!daPy_lk_c::checkPlayerFly())) {
            if (uVar4 == dItem_IRON_BOOTS_e || uVar4 == WATER_BOOTS) {
                procBootsEquip_init(uVar4);
            } else {
                if (isEsa(uVar4)) {
                    if (uVar4 == dItem_HYOI_PEAR_e) {
                        return procFoodSet_init();
                    } else {
                        return procFoodThrow_init();
                    }
                } else if (uVar4 == dItem_TINGLE_TUNER_e) {
                    fopAcM_orderTalkEvent(this, (fopAc_ac_c*)dComIfGp_getAgb());
                } else if (checkDrinkBottleItem(uVar4)) {
                    return procBottleDrink_init(uVar4);
                } else if (checkOpenBottleItem(uVar4)) {
                    return procBottleOpen_init(uVar4);
                } else {
                    if (uVar4 == dItem_EMPTY_BOTTLE_e) {
                        return procBottleSwing_init(1);
                    } else {
                        if (dComIfGs_checkGetItemNum(uVar4) != 0) {
                            return procNotUse_init(uVar4);
                        } else {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        if (uVar4 != dItem_EMPTY_BOTTLE_e) {
            return false;
        }
    }
    if (mEquipItem != uVar4 && uVar4 != dItem_NONE_e) {
        if (uVar4 == dItem_BOMB_BAG_e &&
            (mActivePlayerBombs >= 3 || dComIfGs_getBombNum() == 0))
        {
            seStartSystem(JA_SE_ITEM_TARGET_OUT);
            return false;
        } else {
            mReadyItemBtn = param_1;
            setAnimeEquipItem();
        }
    }
    return false;
}

/* 8010CFB4-8010D26C       .text checkItemChangeFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkItemChangeFromButton() {
    if (checkModeFlg(ModeFlg_00000004) &&
        !checkEquipAnime() &&
        mActorKeepGrab.getActor() == NULL &&
        !checkPlayerGuard()
    ) {
        if (!daPy_dmEcallBack_c::checkCurse()) {
            if (swordTrigger() && checkSwordEquip() && mEquipItem != daPyItem_SWORD_e) {
                setAnimeEquipSword(1);
            } else if (itemTriggerX()) {
                if (checkNewItemChange(0)) {
                    mReadyItemBtn = dItemBtn_X_e;
                    return TRUE;
                }
            } else if (itemTriggerY()) {
                if (checkNewItemChange(1)) {
                    mReadyItemBtn = dItemBtn_Y_e;
                    return TRUE;
                }
            } else if (itemTriggerZ()) {
                if (checkNewItemChange(2)) {
                    mReadyItemBtn = dItemBtn_Z_e;
                    return TRUE;
                }
            } else if (doTrigger()) {
                if (dComIfGp_getDoStatus() == dActStts_PUT_AWAY_e) {
                    setAnimeUnequip();
                }
            }
        } else {
            if (checkEquipDragonShield() && checkSetItemTrigger(dItem_MAGIC_ARMOR_e, 0)) {
                offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
            } else if (mAcch.ChkGroundHit() && !daPy_lk_c::checkPlayerFly()) {
                if (checkEquipHeavyBoots() && checkSetItemTrigger(dItem_IRON_BOOTS_e, 0)) {
                    return procBootsEquip_init(dItem_IRON_BOOTS_e);
                } else if (checkSetItemTrigger(daPyItem_DRINK_BOTTLE_e, 0)) {
                    return procBottleDrink_init(dComIfGp_getSelectItem(mReadyItemBtn));
                } else if (checkSetItemTrigger(dItem_FAIRY_BOTTLE_e, 0)) {
                    return procBottleOpen_init(dItem_FAIRY_BOTTLE_e);
                } else if (doTrigger()) {
                    if (dComIfGp_getDoStatus() == dActStts_PUT_AWAY_e) {
                        setAnimeUnequip();
                    }
                }
            } else if (doTrigger()) {
                if (dComIfGp_getDoStatus() == dActStts_PUT_AWAY_e) {
                    setAnimeUnequip();
                }
            }
        }
    }
    return FALSE;
}

/* 8010D26C-8010D754       .text checkItemAction__9daPy_lk_cFv */
void daPy_lk_c::checkItemAction() {
    if (mEquipItem == dComIfGp_getSelectItem(dItemBtn_X_e) &&
        mEquipItem != dComIfGp_getSelectItem(dItemBtn_Y_e) &&
        mEquipItem != dComIfGp_getSelectItem(dItemBtn_Z_e))
    {
        mReadyItemBtn = dItemBtn_X_e;
    } else if ((mEquipItem == dComIfGp_getSelectItem(dItemBtn_Y_e) &&
                mEquipItem != dComIfGp_getSelectItem(dItemBtn_X_e)) &&
               mEquipItem != dComIfGp_getSelectItem(dItemBtn_Z_e))
    {
        mReadyItemBtn = dItemBtn_Y_e;
    } else if ((mEquipItem == dComIfGp_getSelectItem(dItemBtn_Z_e) &&
                mEquipItem != dComIfGp_getSelectItem(dItemBtn_X_e)) &&
               mEquipItem != dComIfGp_getSelectItem(dItemBtn_Y_e))
    {
        mReadyItemBtn = dItemBtn_Z_e;
    }
    if (checkEquipAnime() || checkUpperAnime(LKANM_BCK_BOOMTHROW) || checkUpperAnime(LKANM_BCK_BOOMCATCH) ||
        checkUpperAnime(LKANM_BCK_ROPETHROW))
    {
        J3DFrameCtrl& frameCtrl = mFrameCtrlUpper[UPPER_MOVE2_e];
        if (checkUpperAnime(LKANM_BCK_BOOMCATCH)) {
            if (!(frameCtrl.getRate() < 0.01f)) {
                if (!(mStickDistance > 0.05f)) {
                    return;
                }
                if (!(frameCtrl.getFrame() > m_HIO->mItem.mBoom.m.field_0x2C)) {
                    return;
                }
            }
            resetActAnimeUpper(UPPER_MOVE2_e, m_HIO->mBasic.m.field_0xC);
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                procShipPaddle_init();
            }
        } else if (checkUpperAnime(LKANM_BCK_BOOMTHROW)) {
            if (frameCtrl.getRate() < 0.01f ||
                ((mStickDistance > 0.05f &&
                  (frameCtrl.getFrame() > m_HIO->mItem.mBoom.m.field_0x10))))
            {
                resetActAnimeUpper(UPPER_MOVE2_e, m_HIO->mBasic.m.field_0xC);
            } else {
                if (frameCtrl.checkPass(m_HIO->mItem.mBoom.m.field_0x14)) {
                    throwBoomerang();
                }
            }
        } else if (checkUpperAnime(LKANM_BCK_ROPETHROW)) {
            if (frameCtrl.getRate() < 0.01f) {
                mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
                mFrameCtrlUnder[UNDER_MOVE1_e].setRate(0.0f);
                mFrameCtrlUpper[UPPER_MOVE0_e].setRate(m_HIO->mAtnMove.m.field_0x24);
                mFrameCtrlUpper[UPPER_MOVE1_e].setRate(0.0f);
            }
        } else if (checkEquipAnime()) {
            if (mEquipItem == daPyItem_SWORD_e &&
                ((checkUpperAnime(LKANM_BCK_REST) && frameCtrl.checkPass(7.0f - frameCtrl.getRate())) ||
                 (checkUpperAnime(LKANM_BCK_TAKE) && frameCtrl.checkPass(7.0f - frameCtrl.getRate())) ||
                 (checkUpperAnime(LKANM_BCK_TAKEBOTH) &&
                  frameCtrl.checkPass(m_HIO->mItem.m.field_0x30 - frameCtrl.getRate())) ||
                 (checkSingleItemEquipAnime() &&
                  frameCtrl.checkPass(m_HIO->mItem.m.field_0x20 - frameCtrl.getRate()))))
            {
                seStartOnlyReverb(JA_SE_LK_SW_PUTIN_S);
            }
            if (std::fabsf(frameCtrl.getRate()) < 0.01f) {
                resetActAnimeUpper(UPPER_MOVE2_e, m_HIO->mBasic.m.field_0xC);
            } else if ((checkUpperAnime(LKANM_BCK_REST) && frameCtrl.checkPass(7.0f)) ||
                        (checkUpperAnime(LKANM_BCK_TAKE) && frameCtrl.checkPass(7.0f)) ||
                        (checkUpperAnime(LKANM_BCK_TAKEBOTH) && frameCtrl.checkPass(m_HIO->mItem.m.field_0x30)) ||
                        (checkSingleItemEquipAnime() && frameCtrl.checkPass(m_HIO->mItem.m.field_0x20)))
            {
                if ((mEquipItem != daPyItem_NONE_e && mEquipItem != daPyItem_SWORD_e) ||
                    (m3562 != daPyItem_NONE_e && m3562 != daPyItem_SWORD_e))
                {
                    seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
                }
                BOOL var_r28;
                if (mEquipItem == daPyItem_NONE_e) {
                    var_r28 = 0;
                } else {
                    var_r28 = 1;
                }
                deleteEquipItem(FALSE);
                mEquipItem = m3562;
                if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0) {
                    if (mEquipItem != daPyItem_SWORD_e || !checkNoResetFlg1(daPyFlg1_UNK4000000)) {
                        if ((checkAttentionLock() || mEquipItem != daPyItem_SWORD_e) || var_r28) {
                            onResetFlg0(daPyRFlg0_UNK80);
                        }
                    }
                }
                if (mCurProc == daPyProc_DEMO_STAND_ITEM_PUT_e) {
                    resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
                } else if (mEquipItem == daPyItem_SWORD_e) {
                    seStartOnlyReverb(JA_SE_LK_SW_PULLOUT_S);
#if VERSION == VERSION_DEMO
                    setSwordModel();
#else
                    setSwordModel(FALSE);
#endif
                } else {
                    makeItemType();
                }
            }
        }
    }
}

/* 8010D754-8010D810       .text getSlidePolygon__9daPy_lk_cFv */
cM3dGPla* daPy_lk_c::getSlidePolygon() {
    if (((!checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000))) &&
         mAcch.ChkGroundHit()) &&
        dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd))
    {
        cM3dGPla* iVar2 = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
        int iVar3 = dComIfG_Bgsp()->GetSpecialCode(mAcch.m_gnd);
        if (iVar2 != NULL && dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd) != 8 && iVar3 == 1) {
            return iVar2;
        }
    }
    return NULL;
}

/* 8010D810-8010D8B0       .text checkJumpCutFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkJumpCutFromButton() {
    if (((mEquipItem == daPyItem_SWORD_e &&
          ((checkResetFlg0(daPyRFlg0_UNK80) || swordTrigger()))) ||
         ((mEquipItem == daPyItem_BOKO_e && swordTrigger()))) ||
        (((mEquipItem == dItem_SKULL_HAMMER_e && itemTrigger()) &&
          mEquipItem == getReadyItem())))
    {
        return procJumpCut_init(1);
    }
    return false;
}

/* 8010D8B0-8010DB58       .text orderTalk__9daPy_lk_cFv */
int daPy_lk_c::orderTalk() {
    if ((dComIfGp_getDoStatus() == dActStts_SPEAK_e || dComIfGp_getDoStatus() == dActStts_LOOK_e ||
         dComIfGp_getDoStatus() == dActStts_READ_e || dComIfGp_getDoStatus() == dActStts_CHECK_e) &&
        talkTrigger())
    {
        fopAcM_orderTalkEvent(this, mpAttnActorA);
        return true;
    }
    if ((mpAttnEntryX != NULL && ((mpAttnEntryX->mType == fopAc_Attn_TYPE_SPEAK_e ||
                                     ((mpAttnEntryX->mType == fopAc_Attn_TYPE_TALK_e &&
                                       mpAttnActorLockOn == mpAttnActorX))))) &&
        itemTriggerX())
    {
        if (((isEsa(dComIfGp_getSelectItem(dItemBtn_X_e))) &&
             dComIfGp_getSelectItem(dItemBtn_X_e) != dItem_HYOI_PEAR_e) &&
            m3630 != fpcM_ERROR_PROCESS_ID_e)
        {
            seStartSystem(JA_SE_ITEM_TARGET_OUT);
            return false;
        }
        fopAcM_orderTalkXBtnEvent(this, mpAttnActorX);
        return true;
    }
    if ((mpAttnEntryY != NULL && ((mpAttnEntryY->mType == fopAc_Attn_TYPE_SPEAK_e ||
                                     ((mpAttnEntryY->mType == fopAc_Attn_TYPE_TALK_e &&
                                       mpAttnActorLockOn == mpAttnActorY))))) &&
        itemTriggerY())
    {
        if (((isEsa(dComIfGp_getSelectItem(dItemBtn_Y_e))) &&
             dComIfGp_getSelectItem(dItemBtn_Y_e) != dItem_HYOI_PEAR_e) &&
            m3630 != fpcM_ERROR_PROCESS_ID_e)
        {
            seStartSystem(JA_SE_ITEM_TARGET_OUT);
            return false;
        }
        fopAcM_orderTalkYBtnEvent(this, mpAttnActorY);
        return true;
    }
    if (mpAttnEntryZ != NULL && (((mpAttnEntryZ->mType == fopAc_Attn_TYPE_SPEAK_e ||
                                     ((mpAttnEntryZ->mType == fopAc_Attn_TYPE_TALK_e &&
                                       mpAttnActorLockOn == mpAttnActorZ))) &&
                                    itemTriggerZ())))
    {
        if (((isEsa(dComIfGp_getSelectItem(dItemBtn_Z_e))) &&
             dComIfGp_getSelectItem(dItemBtn_Z_e) != dItem_HYOI_PEAR_e) &&
            m3630 != fpcM_ERROR_PROCESS_ID_e)
        {
            seStartSystem(JA_SE_ITEM_TARGET_OUT);
            return false;
        }
        fopAcM_orderTalkZBtnEvent(this, mpAttnActorZ);
        return true;
    }
    return false;
}

/* 8010DB58-8010E448       .text checkNextActionFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionFromButton() {
    int direction;

    if (checkResetFlg0(daPyRFlg0_UNK80)) {
        if (mEquipItem == daPyItem_SWORD_e) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
            return changeCutProc();
        }
        if (checkPhotoBoxItem(mEquipItem) || mEquipItem == dItem_TELESCOPE_e) {
            return procScope_init(mEquipItem);
        }
        if (mEquipItem == dItem_DEKU_LEAF_e) {
            return procFanSwing_init();
        }
        if (checkBowItem(mEquipItem)) {
            return checkNextBowMode();
        }
        if (mEquipItem == dItem_HOOKSHOT_e) {
            return checkNextHookshotMode();
        }
        if (mEquipItem == dItem_BOOMERANG_e) {
            return checkNextBoomerangMode();
        }
        if (mEquipItem == dItem_GRAPPLING_HOOK_e) {
            return checkNextRopeMode();
        }
        if (mEquipItem == dItem_WIND_WAKER_e) {
            return procTactWait_init(-1);
        }
    }
    if (checkGrabAnime()) {
        if (checkNextActionGrab()) {
            return true;
        }
        setDoStatusBasic();
    } else if (checkHookshotReadyAnime()) {
        if (checkNextActionHookshotReady()) {
            return true;
        }
        setDoStatusBasic();
    } else if (checkBowAnime()) {
        if (checkNextActionBowReady()) {
            return true;
        }
        setDoStatusBasic();
    } else {
        if (checkBoomerangThrowAnime()) {
            return true;
        }
        if (checkBoomerangReadyAnime()) {
            if (checkNextActionBoomerangReady()) {
                return true;
            }
            setDoStatusBasic();
        } else if (checkRopeAnime()) {
            if (checkNextActionRopeReady()) {
                return true;
            }
            setDoStatusBasic();
        } else {
            setDoStatus();
            if (spActionTrigger() && dComIfGp_getRStatus() == dActStts_GRAB_e) {
                return procPushPullWait_init(1);
            }
            if (orderTalk()) {
                return true;
            }
            if (doTrigger()) {
                if (dComIfGp_getDoStatus() == dActStts_ba_sake__dupe_31) {
                    fopAcM_orderZHintEvent(this, dComIfGp_att_getZHint());
                    return true;
                }
                if (dComIfGp_getDoStatus() == dActStts_GET_IN_SHIP_e) {
                    return procShipReady_init();
                }
                if (dComIfGp_getDoStatus() == dActStts_CLIMB_e) {
                    if (mFrontWallType == 7) {
                        return procHangWallCatch_init();
                    } else {
                        return procVerticalJump_init();
                    }
                }
                if (dComIfGp_getDoStatus() == dActStts_OPEN_e) {
                    if (mpAttnEntryA->mType == 5) {
                        fopAcM_orderDoorEvent(this, mpAttnActorA);
                        changeWaitProc();
                    } else {
                        fopAcM_orderTreasureEvent(this, mpAttnActorA);
                    }
                    return true;
                }
                if (dComIfGp_getDoStatus() == dActStts_LIFT_e ||
                    dComIfGp_getDoStatus() == dActStts_PICK_UP_e)
                {
                    return procGrabReady_init();
                }
                if (dComIfGp_getDoStatus() == dActStts_UNK43) {
                    return procJumpCut_init(0);
                }
                if (dComIfGp_getDoStatus() == dActStts_SIDLE_e) {
                    return procWHideReady_init(NULL, &m3724);
                }
            }
        }
    }
    if (!checkEquipAnime() && !checkPlayerGuard()) {
        if (!daPy_dmEcallBack_c::checkCurse()) {
            if (mEquipItem == daPyItem_SWORD_e) {
                if (checkNoResetFlg0(daPyFlg0_UNK4)) {
                    return procCutTurnCharge_init();
                }
                if (swordTrigger() && abs(m3578) > 0xF800) {
                    return procCutTurn_init(1);
                }
                if (swordTrigger() || m34C5 != 0) {
                    return changeCutProc();
                }
            } else if (mEquipItem == daPyItem_BOKO_e) {
                if (checkNoResetFlg0(daPyFlg0_UNK4)) {
                    return procCutTurnCharge_init();
                }
                if (swordTrigger() && mActorKeepEquip.getActor() != NULL) {
                    if (abs(m3578) > 0xF800) {
                        return procCutTurn_init(1);
                    } else if ((fopAcM_GetParam(mActorKeepEquip.getActor()) == 0) ||
                               (fopAcM_GetParam(mActorKeepEquip.getActor()) == 1))
                    {
                        return procWeaponNormalSwing_init();
                    } else if (fopAcM_GetParam(mActorKeepEquip.getActor()) == 4) {
                        return procWeaponSideSwing_init();
                    } else {
                        return procWeaponFrontSwingReady_init();
                    }
                }
                if (doTrigger() && dComIfGp_getDoStatus() == dActStts_THROW_e) {
                    return procWeaponThrow_init();
                }
            }
            if (itemTrigger() && mEquipItem == getReadyItem()) {
                if (mEquipItem == dItem_HOOKSHOT_e) {
                    if (!checkHookshotReadyAnime()) {
                        return checkNextHookshotMode();
                    }
                } else if (mEquipItem == dItem_GRAPPLING_HOOK_e) {
                    if (!checkRopeAnime()) {
                        return checkNextRopeMode();
                    }
                } else {
                    if (mEquipItem == dItem_BOOMERANG_e) {
                        return checkNextBoomerangMode();
                    }
                    if (checkBowItem(mEquipItem)) {
                        return checkNextBowMode();
                    }
                    if (mEquipItem == dItem_DEKU_LEAF_e) {
                        return procFanSwing_init();
                    }
                    if (mEquipItem == dItem_EMPTY_BOTTLE_e) {
                        return procBottleSwing_init(0);
                    }
                    if (mEquipItem == dItem_SKULL_HAMMER_e) {
                        direction = getDirectionFromShapeAngle();
                        if (mStickDistance > 0.05f &&
                            ((direction == DIR_LEFT || direction == DIR_RIGHT)))
                        {
                            return procHammerSideSwing_init();
                        } else {
                            return procHammerFrontSwingReady_init();
                        }
                    }
                    if (checkPhotoBoxItem(mEquipItem) || mEquipItem == dItem_TELESCOPE_e) {
                        return procScope_init(mEquipItem);
                    }
                    if (mEquipItem == dItem_WIND_WAKER_e) {
                        return procTactWait_init(-1);
                    }
                }
            }
        }
        if (changeSpecialBattle())
            return true;
    }
    if ((dComIfGp_getRStatus() == dActStts_BLANK_e && !checkUpperReadyThrowAnime()) &&
        !checkEquipAnime())
    {
        if (!checkGrabAnime()) {
            if (checkNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND)) {
                dComIfGp_setRStatus(dActStts_CALL_e);
                if (spActionTrigger()) {
                    return procCall_init();
                }
            } else if (mEquipItem == daPyItem_BOKO_e) {
                dComIfGp_setRStatus(dActStts_DROP_e);
                if (spActionTrigger()) {
                    deleteEquipItem(FALSE);
                    m_old_fdata->initOldFrameMorf(5.0f, 0, 0x2A);
                    return true;
                }
            } else if (dComIfGs_getSelectEquip(1) == dItem_NONE_e ||
                       mEquipItem == daPyItem_NONE_e)
            {
                if (checkModeFlg(ModeFlg_00000001)) {
                    dComIfGp_setRStatus(dActStts_CROUCH_e);
                    if (spActionButton()) {
                        return procCrouch_init();
                    }
                }
            } else {
                if (checkGuardAccept()) {
                    dComIfGp_setRStatus(dActStts_DEFEND_e);
                    if (spActionButton()) {
                        return procCrouchDefense_init();
                    }
                }
            }
        }
    }
    if (doTrigger()) {
        if (dComIfGp_getDoStatus() == dActStts_JUMP_e) {
            direction = getDirectionFromShapeAngle();
            if (direction == DIR_LEFT || direction == DIR_RIGHT) {
                return procSideStep_init(direction);
            }
            if (direction == DIR_BACKWARD) {
                return procBackJump_init();
            }
        } else if (dComIfGp_getDoStatus() == dActStts_ATTACK_e) {
            if (!checkAttentionLock() && mStickDistance > 0.05f) {
                shape_angle.y = m34E8;
            }
            return procFrontRoll_init(m_HIO->mRoll.m.field_0xC);
        }
    }
    if ((daPy_getPlayerActorClass() == this && !dComIfGp_event_runCheck()) &&
        !checkGrabWear())
    {
        onResetFlg0(daPyRFlg0_SUBJECT_ACCEPT);
        if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x1000)) {
            return procSubjectivity_init(0);
        }
    }
    return checkItemChangeFromButton();
}

/* 8010E448-8010E75C       .text setShieldGuard__9daPy_lk_cFv */
void daPy_lk_c::setShieldGuard() {
    f32 local_18 = m_pbCalc[PART_UPPER_e]->getRatio(2);
    if (checkGuardSlip() ||
        (!checkEquipAnime() && !checkGrabAnime() && checkAttentionLock() && mEquipItem != daPyItem_BOKO_e &&
         dComIfGs_getSelectEquip(1) != dItem_NONE_e && checkGuardAccept() &&
         (mActorKeepEquip.getID() == fpcM_ERROR_PROCESS_ID_e || mActorKeepEquip.getActor() != NULL)))
    {
        dComIfGp_setRStatus(dActStts_DEFEND_e);
    }
    u16 uVar3;
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        uVar3 = LKANM_BCK_ATNGHAM;
    } else {
        uVar3 = LKANM_BCK_ATNG;
    }
    if (!checkGuardSlip()) {
        if (spActionButton() && dComIfGp_getRStatus() == dActStts_DEFEND_e) {
            freeGrabItem();
            if (!checkUpperAnime(uVar3)) {
                resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
                setActAnimeUpper(uVar3, UPPER_MOVE2_e, m_HIO->mAtnMove.m.field_0x24, 0.0f, -1,
                                 m_HIO->mBasic.m.field_0xC);
            } else {
                f32 dVar6 = 1.0f;
                if (local_18 < dVar6) {
                    if (m_HIO->mBasic.m.field_0xC > 0.01f) {
                        cLib_chaseF(&local_18, dVar6, dVar6 / m_HIO->mBasic.m.field_0xC);
                    } else {
                        local_18 = 1.0f;
                    }
                    m_pbCalc[PART_UPPER_e]->setRatio(2, local_18);
                }
            }
            if (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_ATNLS ||
                m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_ATNRS)
            {
                mAnmRatioUpper[UPPER_MOVE2_e].getAnmTransform()->setFrame(
                    mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
            }
        } else {
            if (checkUpperGuardAnime()) {
                if (m_HIO->mBasic.m.field_0xC > 0.01f) {
                    cLib_chaseF(&local_18, 0.0f, 1.0f / m_HIO->mBasic.m.field_0xC);
                } else {
                    local_18 = 0.0f;
                }
                if (local_18 <= 0.0f) {
                    resetActAnimeUpper(UPPER_MOVE2_e, m_HIO->mBasic.m.field_0xC);
                } else {
                    m_pbCalc[PART_UPPER_e]->setRatio(2, local_18);
                }
            }
        }
    }
    if (checkPlayerGuard()) {
        mCyl.OnTgShield();
    } else {
        mCyl.OffTgShield();
    }
}

/* 8010E75C-8010E7C4       .text checkItemModeActorPointer__9daPy_lk_cFv */
BOOL daPy_lk_c::checkItemModeActorPointer() {
    if (mActorKeepEquip.getActor() != NULL) {
        return true;
    }
    mActorKeepEquip.clearData();
    resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
    mEquipItem = daPyItem_NONE_e;
    procWait_init();
    return false;
}

/* 8010E7C4-8010E828       .text checkNextActionItemFly__9daPy_lk_cFv */
void daPy_lk_c::checkNextActionItemFly() {
    if (!daPy_dmEcallBack_c::checkCurse()) {
        if (checkBowItem(mEquipItem)) {
            checkNextActionBowFly();
        } else if (mEquipItem == dItem_BOOMERANG_e) {
            checkNextActionBoomerangFly();
        }
    }
}

/* 8010E828-8010EC78       .text checkNextMode__9daPy_lk_cFi */
BOOL daPy_lk_c::checkNextMode(int r29) {
    f32 f31 = mMaxNormalSpeed;
    setFrontWallType();
    
    if (checkNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP)) {
        return procVomitJump_init(2);
    }
    if (checkNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP_SHORT)) {
        return procVomitJump_init(3);
    }
    
    BOOL r24 = checkAttentionLock() ||
        (mActorKeepThrow.getActor() != NULL && mpAttnActorLockOn == mActorKeepThrow.getActor()) ||
        checkUpperReadyThrowAnime() ||
        mDemo.getDemoMode() == daPy_demo_c::DEMO_A_WAIT_e;
    
    if (r24) {
        mMaxNormalSpeed = m_HIO->mAtnMove.m.field_0xC;
    } else {
        mMaxNormalSpeed = m_HIO->mMove.m.field_0x18;
    }
    
    if (changeSlideProc()) {
        return true;
    }
    if (checkNextActionFromButton()) {
        return true;
    }
    if (r29 != 0 && !(mStickDistance > 0.05f) && !spActionButton()) {
        mMaxNormalSpeed = f31;
        return false;
    }

    BOOL r3;
    if (r24) {
        if (checkBoomerangAnime()) {
            r3 = checkNextBoomerangMode();
        } else if (checkBowAnime()) {
            r3 = checkNextBowMode();
        } else if (checkHookshotReadyAnime()) {
            r3 = checkNextHookshotMode();
        } else if (checkRopeAnime()) {
            r3 = checkNextRopeMode();
        } else if (mpAttnActorLockOn != NULL || (mDemo.getDemoMode() == daPy_demo_c::DEMO_A_WAIT_e)) {
            if (std::abs(mVelocity) <= 0.001f) {
                r3 = procAtnActorWait_init();
            } else {
                r3 = procAtnActorMove_init();
            }
        } else if (std::abs(mVelocity) <= 0.001f) {
            r3 = changeWaitProc();
        } else {
            r3 = procAtnMove_init();
        }
    } else {
        mDirection = DIR_NONE;
        int direction = getDirectionFromCurrentAngle();
        if (std::abs(mVelocity) <= 0.001f) {
            if (cLib_distanceAngleS(m34E8, current.angle.y) > 0x7800 && mStickDistance > 0.05f)
            {
                r3 = procWaitTurn_init();
                if (!r3 && !dComIfGp_event_runCheck() && mDemo.getDemoType() == 0)
                {
                    r3 = changeWaitProc();
                }
            } else {
                r3 = changeWaitProc();
            }
        } else if (mCurProc == daPyProc_MOVE_TURN_e && current.angle.y != shape_angle.y) {
            r3 = procMoveTurn_init(0);
        } else if (cLib_distanceAngleS(m34E8, current.angle.y) > 0x7800 &&
                   mStickDistance > 0.05f)
        {
            if ((speedF / mMaxNormalSpeed > m_HIO->mSlip.m.field_0x4) &&
                mCurrAttributeCode != dBgS_Attr_ICE_e &&
                (!checkGrabAnime() && getDirectionFromAngle(m34EA - m34DC) == DIR_BACKWARD))
            {
                r3 = procSlip_init();
            } else {
                r3 = procMoveTurn_init(1);
            }
        } else if (direction == DIR_BACKWARD && mStickDistance > 0.05f) {
            r3 = procMoveTurn_init(1);
        } else {
            r3 = procMove_init();
        }
    }
    
    if (!r3) {
        r3 = checkJumpFlower();
    }
    return r3;
}

/* 8010EC78-8010ED68       .text checkIceSlipFall__9daPy_lk_cFv */
BOOL daPy_lk_c::checkIceSlipFall() {
    f32 fVar1;
    f32 fVar2;

    s16 sVar3 = cM_atan2s(m36A0.x, m36A0.z);
    if (m34C3 == 1) {
        fVar1 = 15.0f;
        fVar2 = 169.0f;
    } else {
        fVar1 = 10.0f;
        fVar2 = 49.0f;
    }
    f32 dVar5 = fVar2;
    f32 dVar6 = fVar1;
    if (cLib_distanceAngleS(sVar3, current.angle.y) > 0x7000 && mVelocity >= dVar6 &&
        m36A0.abs2XZ() >= dVar5)
    {
        m34D0--;
        if (m34D0 == 0) {
            return procIceSlipFall_init();
        }
    } else {
        m34D0 = 0x14;
    }
    return false;
}

/* 8010ED68-8010F9AC       .text setFrontWallType__9daPy_lk_cFv */
void daPy_lk_c::setFrontWallType() {
    BOOL cVar8;
    cM3dGPla* pVVar6;
    cM3dGPla* uVar7;
    int iVar9;
    int iVar10;
    f32 dVar13;
    f32 dVar12;
    f32 dVar14;
    f32 dVar15;
    f32 dVar16;
    cXyz spA8;
    cXyz sp9C;
    cXyz sp90;
    cXyz sp84;
    cXyz sp78;
    cXyz sp6C;
    cXyz sp60;
    cXyz sp54;

    dVar16 = mAcchCir[0].GetWallR();
    if (mFrontWallType != 0) {
        return;
    }
    mFrontWallType = 1;
    if (!mAcch.ChkWallHit() && !checkModeFlg(ModeFlg_HOOKSHOT | ModeFlg_PUSHPULL)) {
        return;
    }
    if (checkGrabWear()) {
        return;
    }
    dVar15 = cM_ssin(shape_angle.y);
    dVar14 = cM_scos(shape_angle.y);
    iVar9 = 2;
    dVar13 = (dVar15 * (25.0f + dVar16));
    dVar12 = (dVar14 * (25.0f + dVar16));
    for (; iVar9 >= 0; iVar9--) {
        spA8.set(current.pos.x, current.pos.y + ((mAcchCir[iVar9]).GetWallH()), current.pos.z);
        sp9C.set(spA8.x + dVar13, spA8.y, spA8.z + dVar12);
        mLinkLinChk.Set(&spA8, &sp9C, this);
        if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            break;
        }
    }
    if (iVar9 == -1) {
        return;
    }
    pVVar6 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
    if (std::abs(pVVar6->GetNP()->y) > 0.05f) {
        return;
    }
    m352C = cM_atan2s(pVVar6->GetNP()->x, pVVar6->GetNP()->z);
    if (cLib_distanceAngleS(m352C, shape_angle.y + 0x8000) <= 0x2000) {
        if (checkModeFlg(ModeFlg_MIDAIR)) {
            m3724 = mLinkLinChk.GetCross();
        } else {
            dVar12 = cM3d_SignedLenPlaAndPos(pVVar6, &current.pos);
            m3724.set(
                current.pos.x - (dVar12 * pVVar6->GetNP()->x),
                current.pos.y,
                current.pos.z - (dVar12 * pVVar6->GetNP()->z)
            );
            iVar10 = dComIfG_Bgsp()->GetWallCode(mLinkLinChk);
            if (iVar10 != 4 && iVar10 != 5) {
                iVar9 = 2;
                dVar12 = 2.0f * dVar12;
                for (; iVar9 >= 0; iVar9--) {
                    spA8.set(current.pos.x, current.pos.y + ((mAcchCir[iVar9]).GetWallH()), current.pos.z);
                    sp9C.set(spA8.x - (dVar12 * pVVar6->GetNP()->x), spA8.y, spA8.z - (dVar12 * pVVar6->GetNP()->z));
                    mLinkLinChk.Set(&spA8, &sp9C, this);
                    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        sp90 = *pVVar6->GetNP() - *dComIfG_Bgsp()->GetTriPla(mLinkLinChk)->GetNP();
                        dVar13 = sp90.abs();
                        if (dVar13 < 0.001f) {
                            break;
                        }
                    }
                }
                if (iVar9 == -1) {
                    return;
                }
            }
        }
        iVar10 = dComIfG_Bgsp()->GetWallCode(mLinkLinChk);
        if (iVar10 == 2 || current.pos.y - m35D4 < 125.0f) {
            return;
        }
        if (checkNoResetFlg0(daPyFlg0_UNK100)) {
            if ((iVar10 == 3 && !checkModeFlg(ModeFlg_SWIM)) && !checkModeFlg(ModeFlg_MIDAIR)) {
                onResetFlg0(daPyRFlg0_UNK8);
                mPolyInfo = mLinkLinChk;
                if (checkModeFlg(ModeFlg_PUSHPULL)) {
                    return;
                }
            } else {
                if (iVar10 == 1) {
                    if (checkModeFlg(ModeFlg_MIDAIR)) {
                        f32 x = m3724.x - 15.0f * pVVar6->GetNP()->x;
                        f32 z = m3724.z - 15.0f * pVVar6->GetNP()->z;
                        spA8.set(x, 150.0f + current.pos.y, z);
                        mGndChk.SetPos(&spA8);
                        dVar16 = dComIfG_Bgsp()->GroundCross(&mGndChk);
                        if (dVar16 >= current.pos.y) {
                            uVar7 = dComIfG_Bgsp()->GetTriPla(mGndChk);
                            if (cBgW_CheckBGround(uVar7->GetNP()->y)) {
                                sp78.set(pVVar6->GetNP()->z, 0.0f, pVVar6->GetNP()->x);
                                sp78.normalize();
                                cM3dGPla spC8(&sp78, -(sp78.x * m3724.x + sp78.z * m3724.z));
                                uVar7 = dComIfG_Bgsp()->GetTriPla(mGndChk);
                                if (cM3d_3PlaneCrossPos(*pVVar6, *uVar7, spC8, &sp84) &&
                                    (sp84.y - current.pos.y <= 150.0f))
                                {
                                    m3724 = sp84;
                                    mFrontWallType = 7;
                                    return;
                                }
                            }
                        }
                    }
                    mPolyInfo = mLinkLinChk;
                    mFrontWallType = 3;
                    return;
                }
                if (iVar10 == 4 || (iVar10 == 5 && !checkModeFlg(ModeFlg_MIDAIR))) {
                    if (iVar10 == 4) {
                        mFrontWallType = 4;
                    } else {
                        mFrontWallType = 5;
                    }
                    dComIfG_Bgsp()->GetTriPnt(mLinkLinChk, &sp6C, &sp60, &sp54);
                    mPolyInfo = mLinkLinChk;
                    if (std::abs(sp6C.y - sp60.y) < 1.0f) {
                        m3724.x = 0.5f * (sp6C.x + sp60.x);
                        if (sp54.y > sp6C.y) {
                            m3724.y = sp6C.y;
                            m35F8 = sp54.y;
                        } else {
                            m3724.y = sp54.y;
                            m35F8 = sp6C.y;
                        }
                        m3724.z = 0.5f * (sp6C.z + sp60.z);
                    } else if (std::abs(sp6C.y - sp54.y) < 1.0f) {
                        m3724.x = 0.5f * (sp6C.x + sp54.x);
                        if (sp60.y > sp6C.y) {
                            m3724.y = sp6C.y;
                            m35F8 = sp60.y;
                        } else {
                            m3724.y = sp60.y;
                            m35F8 = sp6C.y;
                        }
                        m3724.z = 0.5f * (sp6C.z + sp54.z);
                    } else {
                        m3724.x = 0.5f * (sp60.x + sp54.x);
                        if (sp6C.y > sp60.y) {
                            m3724.y = sp60.y;
                            m35F8 = sp6C.y;
                        } else {
                            m3724.y = sp6C.y;
                            m35F8 = sp60.y;
                        }
                        m3724.z = 0.5f * (sp60.z + sp54.z);
                    }
                    return;
                }
            }
        }
        spA8.set(current.pos.x, current.pos.y + (0.1f + m_HIO->mWallCatch.m.field_0x18), current.pos.z);
        sp9C.set(spA8.x + (dVar15 * (50.0f + dVar16)), spA8.y, spA8.z + (dVar14 * (50.0f + dVar16)));
        mLinkLinChk.Set(&spA8, &sp9C, this);
        cVar8 = dComIfG_Bgsp()->LineCross(&mLinkLinChk);
        if (cVar8 == 0) {
            mRoofChk.SetPos(current.pos);
            dVar12 = dComIfG_Bgsp()->RoofChk(&mRoofChk);
            if ((dVar12 - current.pos.y) > 10.0f + m_HIO->mWallCatch.m.field_0x18) {
                cVar8 = 0;
            } else {
                cVar8 = 1;
            }
        }
        if (cVar8 != 0) {
            if (!checkGrabAnime() && !checkModeFlg(ModeFlg_MIDAIR | ModeFlg_SWIM)) {
                spA8.set(current.pos.x, current.pos.y + 149.9f, current.pos.z);
                sp9C.set(
                    spA8.x + (2.0f * dVar16) * cM_ssin(current.angle.y),
                    spA8.y,
                    spA8.z + (2.0f * dVar16) * cM_scos(current.angle.y)
                );
                cXyz sp48;
                uVar7 = getWHideModePolygon(&spA8, &sp9C, &sp48, 4);
                if (uVar7 != 0) {
                    mFrontWallType = 2;
                }
            }
            return;
        }
        spA8.set(
            m3724.x - 15.0f * pVVar6->GetNP()->x,
            current.pos.y + (m_HIO->mWallCatch.m.field_0x18 + 0.1f),
            m3724.z - 15.0f * pVVar6->GetNP()->z
        );
        mGndChk.SetPos(&spA8);
        dVar16 = dComIfG_Bgsp()->GroundCross(&mGndChk);
        if (!checkModeFlg(ModeFlg_SWIM) && dVar16 < current.pos.y) {
            return;
        }
        if (dVar16 == -G_CM3D_F_INF || !cBgW_CheckBGround(dComIfG_Bgsp()->GetTriPla(mGndChk)->GetNP()->y)) {
            return;
        }
        cXyz sp3C;
        cXyz sp30(pVVar6->GetNP()->z, 0.0f, -pVVar6->GetNP()->x);
        sp30.normalize();
        cM3dGPla spB4(&sp30, -(sp30.x * m3724.x + sp30.z * m3724.z));
        if (!cM3d_3PlaneCrossPos(*pVVar6, *dComIfG_Bgsp()->GetTriPla(mGndChk), spB4, &sp3C)) {
            return;
        }
        m3724 = sp3C;
        f32 fVar3 = m3724.y - current.pos.y;
        if (checkModeFlg(ModeFlg_SWIM)) {
            if ((fVar3 <= 0.1f + m_HIO->mSwim.m.field_0x6C) && fVar3 >= -5.0f) {
                mFrontWallType = 7;
            }
        } else if (checkModeFlg(ModeFlg_MIDAIR)) {
            if (((dVar16 - mAcch.GetGroundH()) > 125.0f) && (mCurProc != daPyProc_HOOKSHOT_FLY_e || fVar3 < 100.0f)) {
                mFrontWallType = 7;
            }
        } else if (fVar3 >= 0.1f + m_HIO->mWallCatch.m.field_0x18) {
            // TODO?
        } else if (!checkGrabAnime() || !(fVar3 >= 0.1f + m_HIO->mWallCatch.m.field_0xC)) {
            if (fVar3 < 27.09f) {
                return;
            } else if (fVar3 < m_HIO->mWallCatch.m.field_0xC + 0.1f) {
                mFrontWallType = 6;
            } else if (fVar3 < m_HIO->mWallCatch.m.field_0x10 + 0.1f) {
                mFrontWallType = 7;
            } else if (fVar3 < m_HIO->mWallCatch.m.field_0x14 + 0.1f) {
                mFrontWallType = 8;
            } else {
                mFrontWallType = 9;
            }
        }
    }
}

/* 8010F9AC-8010FEC4       .text changeFrontWallTypeProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeFrontWallTypeProc() {
    f32 fVar2;
    f32 fVar3;
    int iVar8;
    s16 sVar5;

    setFrontWallType();
    sVar5 = m3544;
    m3544 = 0;
    if (mStickDistance <= 0.05f && !checkModeFlg(ModeFlg_MIDAIR)) {
        return false;
    }
    if (checkModeFlg(ModeFlg_MIDAIR)) {
        if (mFrontWallType == 7) {
            voiceStart(10);
            return procHangStart_init();
        }
        if (!checkNoResetFlg1(daPyFlg1_VINE_CATCH)) {
            if (mFrontWallType == 3) {
                deleteEquipItem(TRUE);
                shape_angle.y = m352C + 0x8000;
                procClimbMoveUpDown_init(1);
                m35E0 = 43.67353f;
                m_old_fdata->initOldFrameMorf(5.0f, 0, 0x2A);
                mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
                return true;
            }
            if (mFrontWallType == 4) {
                fVar2 = cM_ssin(m352C);
                fVar3 = cM_scos(m352C);
                iVar8 = (int)((current.pos.y - m3724.y) / 37.5f) - 1;
                if (iVar8 < 1) {
                    return procFall_init(1, m_HIO->mWallCatch.m.field_0x54);
                }
                shape_angle.y = m352C + 0x8000;
                current.angle.y = shape_angle.y;
                current.pos.x = (m3724.x + 20.5f * fVar2) - fVar3;
                current.pos.y = m3724.y + 37.5f * iVar8;
                current.pos.z = (m3724.z + 20.5f * fVar3) + fVar2;
                deleteEquipItem(TRUE);
                m35E0 = 43.67353f;
                if (current.pos.y > m35F8 - 150.0f) {
                    current.pos.y = m35F8 - 150.0f;
                    m370C = current.pos;
                    procLadderUpEnd_init(1);
                } else {
                    procLadderMove_init(1, 0, &current.pos);
                    mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
                }
                m_old_fdata->initOldFrameMorf(5.0f, 0, 0x2A);
                return true;
            }
        }
    } else if (!checkResetFlg0(daPyRFlg0_UNK8)) {
        if (mFrontWallType == 3) {
            if (checkNoResetFlg1(daPyFlg1_VINE_CATCH)) {
                return false;
            }
            if (checkModeFlg(ModeFlg_SWIM)) {
                shape_angle.y = m352C + 0x8000;
                current.pos.y = current.pos.y - 60.0f;
                procClimbMoveUpDown_init(1);
                m35E0 = 43.67353f;
                m_old_fdata->initOldFrameMorf(5.0f, 0, 0x2A);
                mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
                return true;
            }
            return procClimbUpStart_init();
        }
        if (mFrontWallType == 4) {
            if (checkNoResetFlg1(daPyFlg1_VINE_CATCH)) {
                return false;
            }
            if (checkModeFlg(ModeFlg_SWIM)) {
                fVar3 = cM_ssin(m352C);
                fVar2 = cM_scos(m352C);
                shape_angle.y = m352C + 0x8000;
                current.angle.y = shape_angle.y;
                iVar8 = (int)((current.pos.y - m3724.y) / 37.5f) - 2;
                current.pos.x = (m3724.x + 20.5f * fVar3) - fVar2;
                current.pos.y = m3724.y + 37.5f * iVar8;
                current.pos.z = (m3724.z + 20.5f * fVar2) + fVar3;
                while (m35D0 - current.pos.y > m_HIO->mSwim.m.field_0x24) {
                    current.pos.y += 37.5f;
                }
                procLadderMove_init(1, 0, &current.pos);
                m35E0 = 43.67353f;
                m_old_fdata->initOldFrameMorf(5.0f, 0, 0x2A);
                return true;
            }
            return procLadderUpStart_init();
        }
        if (mFrontWallType == 5) {
            if (checkNoResetFlg1(daPyFlg1_VINE_CATCH)) {
                return false;
            }
            return procLadderDownStart_init();
        }
        m3544 = sVar5 + 1;
        if (mFrontWallType == 6) {
            if (m3544 > m_HIO->mSmallJump.m.field_0x2) {
                return procSmallJump_init(0);
            }
            return false;
        }
        if (m3544 > m_HIO->mWallCatch.m.field_0x8) {
            if (mFrontWallType == 7) {
                return procHangWallCatch_init();
            }
            if (mFrontWallType == 8 || mFrontWallType == 9) {
                return procVerticalJump_init();
            }
            m3544 = 0;
        }
    }
    return false;
}

/* 8010FEC4-8010FFB0       .text changeSlideProc__9daPy_lk_cFv */
int daPy_lk_c::changeSlideProc() {
    s16 sVar4;

    cM3dGPla* pfVar1 = getSlidePolygon();
    if (pfVar1 != NULL) {
        sVar4 = cM_atan2s(pfVar1->GetNP()->x, pfVar1->GetNP()->z);
        if (m34C3 != 0) {
            cLib_addCalc(&mVelocity, 0.0f, 0.4f, 5.0f, 1.0f);
            m3526--;
            if (mVelocity > 5.0f || m3526 > 0) {
                return false;
            }
        }
        if (cLib_distanceAngleS(sVar4, shape_angle.y) < m_HIO->mSlide.m.field_0x8) {
            return procSlideFront_init(sVar4);
        } else {
            return procSlideBack_init(sVar4);
        }
    } else {
        m3526 = 8;
        return false;
    }
}

/* 8010FFB0-80110028       .text changeWaitProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeWaitProc() {
    if (checkGrabAnime()) {
        return procGrabWait_init();
    } else if (checkUpperAnime(LKANM_BCK_BOOMCATCH)) {
        return procBoomerangCatch_init();
    } else if (daPy_getPlayerActorClass() != this) {
        return procControllWait_init();
    } else {
        return procWait_init();
    }
}

/* 80110028-8011029C       .text changeLandProc__9daPy_lk_cFf */
BOOL daPy_lk_c::changeLandProc(f32 param_1) {
    BOOL bVar2;
    f32 dVar6;
    f32 dVar7;

    dVar7 = m35F0 - current.pos.y;
    if (mCurrAttributeCode != dBgS_Attr_GIANT_FLOWER_e &&
        ((dVar7 >= (100.0f * m_HIO->mFall.m.field_0x14))))
    {
        if (dVar7 >= (100.0f * m_HIO->mFall.m.field_0x10)) {
            return procLandDamage_init(2);
        } else {
            return procLandDamage_init(1);
        }
    }
    dVar6 = param_1;
    int direction = getDirectionFromAngle(current.angle.y - shape_angle.y);
    if (mCurProc == daPyProc_CUT_EX_MJ_e && ((m34C5 != 0 || checkNoResetFlg0(daPyFlg0_UNK4)))) {
        bVar2 = true;
    } else {
        bVar2 = false;
    }
    if ((((!checkGrabAnime() && mStickDistance > 0.5f) && direction != DIR_BACKWARD) &&
         (!bVar2)) &&
        (((mCurProc == daPyProc_CUT_EX_MJ_e || (m3688.y - current.pos.y >= 300.0f)) &&
          ((!checkNoResetFlg1(daPyFlg1_UNK8000000) &&
            getDirectionFromCurrentAngle() == DIR_FORWARD)))))
    {
        voiceStart(7);
        if (direction == DIR_FORWARD) {
            speedF = m_HIO->mMove.m.field_0x18;
            procFrontRoll_init(m_HIO->mFall.m.field_0x38);
        } else {
            procSideRoll_init();
        }
    } else {
        if (((dVar7 >= (0.5f * (m_HIO->mFall.m.field_0x14 * 100.0f))) &&
             !checkBossGomaStage()) &&
            mCurrAttributeCode != dBgS_Attr_GIANT_FLOWER_e)
        {
            procLandDamage_init(0);
        } else {
            if (mCurProc == daPyProc_VOMIT_JUMP_e) {
                procVomitLand_init();
            } else if (bVar2) {
                checkNextMode(0);
            } else {
                procLand_init(dVar6, 0);
            }
        }
    }
    return true;
}

/* 8011029C-80110338       .text setDamagePoint__9daPy_lk_cFf */
BOOL daPy_lk_c::setDamagePoint(f32 amount) {
    if (!checkNoDamageMode()) {
        dComIfGp_setItemLifeCount(amount);
        if (amount < 0.0f) {
            offNoResetFlg1(daPyFlg1_SOUP_POWER_UP);
#if VERSION > VERSION_JPN
            if (!checkFinalMasterSwordEquip())
#endif
            {
                offNoResetFlg1(daPyFlg1_UNK200000);
            }
        }
        return TRUE;
    } else {
        seStartMapInfo(JA_SE_LK_MGC_SHIELD_DEF);
        return FALSE;
    }
}

/* 80110338-80110448       .text checkNormalDamage__9daPy_lk_cFi */
BOOL daPy_lk_c::checkNormalDamage(int param_1) {
    if (checkGrabAnime() || mCurProc != daPyProc_MOVE_e ||
        (std::abs(mVelocity * (m3580 == 8 ? 1.0f : cM_scos(m34E2)) / mMaxNormalSpeed) < 0.9f) ||
        (!checkNoDamageMode() && !dComIfGs_checkBottle(dItem_FAIRY_BOTTLE_e) && dComIfGs_getLife() <= param_1))
    {
        return true;
    }
    return false;
}

/* 80110448-801104E4       .text setDashDamage__9daPy_lk_cFv */
void daPy_lk_c::setDashDamage() {
    setActAnimeUpper(LKANM_BCK_DAMDASH, UPPER_MOVE2_e, m_HIO->mMove.m.field_0x48, 0.0f, -1,
                     m_HIO->mBasic.m.field_0xC);
    setPriTextureAnime(0x40, 0);
    mFrameCtrlUpper[UPPER_MOVE2_e].setFrame(mFrameCtrlUnder[UNDER_MOVE1_e].getFrame());
    mDamageWaitTimer = m_HIO->mDam.m.field_0x2;
    voiceStart(2);
    seStartOnlyReverb(JA_SE_LK_DAMAGE_NORMAL);
}

/* 801104E4-8011054C       .text checkAtHitEnemy__9daPy_lk_cFP12dCcD_GObjInf */
BOOL daPy_lk_c::checkAtHitEnemy(dCcD_GObjInf* param_1) {
    if ((param_1->ChkAtHit() && param_1->GetAtHitAc() != NULL) &&
        (fopAcM_GetGroup(param_1->GetAtHitAc()) == fopAc_ENEMY_e))
    {
        return true;
    }
    return false;
}

/* 8011054C-801105D8       .text checkElecReturnDamage__9daPy_lk_cFP12dCcD_GObjInfP4cXyz */
BOOL daPy_lk_c::checkElecReturnDamage(dCcD_GObjInf* param_1, cXyz* param_2) {
    if (param_1->ChkAtHit() && param_1->GetAtHitGObj() != NULL) {
        dCcD_GObjInf* gobj_p = (dCcD_GObjInf*)param_1->GetAtHitGObj();
        if (gobj_p->GetTgSpl() == dCcG_Tg_Spl_UNK1) {
            param_2->x = param_1->GetAtHitPosP()->x;
            param_2->y = param_1->GetAtHitPosP()->y;
            param_2->z = param_1->GetAtHitPosP()->z;
            return true;
        }
    }
    return false;
}

/* 801105D8-80110654       .text checkWallAtributeDamage__9daPy_lk_cFP12dBgS_AcchCir */
s32 daPy_lk_c::checkWallAtributeDamage(dBgS_AcchCir* param_1) {
    if (param_1->ChkWallHit() && dComIfG_Bgsp()->ChkPolySafe(*param_1)) {
        int attrib_code = dComIfG_Bgsp()->GetAttributeCode(*param_1);
        if ((attrib_code == dBgS_Attr_DAMAGE_e || attrib_code == dBgS_Attr_ELECTRICITY_e)) {
            return attrib_code;
        }
    }
    return false;
}

/* 80110654-80110F3C       .text changeDamageProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeDamageProc() {
    if (!checkModeFlg(ModeFlg_DAMAGE) && mDamageWaitTimer > 0) {
        mDamageWaitTimer--;
        if (mDamageWaitTimer == 0) {
            if (checkDashDamageAnime()) {
                resetActAnimeUpper(UPPER_MOVE2_e, m_HIO->mBasic.m.field_0xC);
            } else if (checkModeFlg(ModeFlg_SWIM)) {
                resetPriTextureAnime();
            }
        }
    }
    
    if (checkNoResetFlg0(daPyFlg0_UNK1000000)) {
        offNoResetFlg0(daPyFlg0_UNK1000000);
        changePlayer(this);
        return procLargeDamage_init(-5, 1, 0, 0);
    }
    
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if (dComIfGp_event_runCheck() ||
        checkPlayerDemoMode() ||
#if VERSION > VERSION_JPN
        checkNoControll() ||
#endif
        mCurProc == daPyProc_SHIP_READY_e ||
        (
            dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
            ship && ship->checkForceMove()
        )
    ) {
        offNoResetFlg0(daPyFlg0_SHIP_DROP);
        return FALSE;
    }
    
    BOOL r30;
    int damage;
    s32 attribCode = dBgS_Attr_NORMAL_e;
    
    if (checkNoResetFlg1(daPyFlg1_UNK4) || (
        mAcch.ChkGroundHit() &&
        !checkModeFlg(ModeFlg_HANG) &&
        mCurrAttributeCode == dBgS_Attr_FREEZE_e
    )) {
        changePlayer(this);
        return dProcFreezeDamage_init();
    }
    
    if (
        dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
        checkNoResetFlg0(daPyFlg0_SHIP_DROP)
    ) {
        offNoResetFlg0(daPyFlg0_SHIP_DROP);
        changePlayer(this);
        return procLargeDamage_init(-2, 1, 0, 0);
    }
    
    if (!checkModeFlg(ModeFlg_DAMAGE) && mDamageWaitTimer == 0) {
        if (mAcch.ChkGroundHit() && (
            mCurrAttributeCode == dBgS_Attr_DAMAGE_e ||
            mCurrAttributeCode == dBgS_Attr_ELECTRICITY_e
        )) {
            attribCode = mCurrAttributeCode;
        } else {
            for (int i = 0; attribCode == dBgS_Attr_NORMAL_e && i < (s32)ARRAY_SIZE(mAcchCir); i++) {
                attribCode = checkWallAtributeDamage(&mAcchCir[i]);
            }
        }
    }
    
    if (attribCode != dBgS_Attr_NORMAL_e) {
        r30 = TRUE;
        damage = 1;
    } else {
        r30 = FALSE;
        damage = mStts.GetDmg();
        if (mCyl.ChkTgHit() && mCyl.GetTgHitGObj() && mCyl.GetTgHitGObj()->GetAtType() == AT_TYPE_BOMB) {
            damage = 1;
        }
    }
    
    dCcG_At_Spl spl;
    if (mCyl.ChkTgHit()) {
        dCcD_GObjInf* gobj = mCyl.GetTgHitGObj();
        if (gobj) {
            spl = gobj->GetAtSpl();
        } else {
            spl = mStts.GetAtSpl();
        }
    } else {
        spl = dCcG_At_Spl_UNK0;
    }
    
    if (checkModeFlg(ModeFlg_04000000)) {
        if (r30 || (mCyl.ChkTgHit() && !checkSuccessGuard(spl))) {
            setDamagePoint(-damage);
            mDamageWaitTimer = m_HIO->mDam.m.field_0x2;
            
            voiceStart(2);
            
            seStartOnlyReverb(JA_SE_LK_DAMAGE_NORMAL);
            changePlayer(this);
            if (mCyl.ChkTgHit() && !checkSuccessGuard(spl)) {
                setDamageEmitter();
            } else if (attribCode == dBgS_Attr_ELECTRICITY_e) {
                setDamageElecEmitter();
            }
            if (daPy_dmEcallBack_c::checkElec()) {
                if (checkModeFlg(ModeFlg_ROPE)) {
                    return procElecDamage_init(NULL);
                } else if (checkModeFlg(ModeFlg_SWIM)) {
                    return procElecDamage_init(NULL);
                }
            }
            if (checkModeFlg(ModeFlg_SWIM) && !checkNoDamageMode()) {
                setPriTextureAnime(0x40, 0);
            }
        }
    } else {
        if (mAtCps[0].GetAtType() != AT_TYPE_BOKO_STICK && mAtCps[0].GetAtType() != AT_TYPE_WATER) {
            cXyz sp8;
            if (checkElecReturnDamage(&mAtCps[0], &sp8) ||
                checkElecReturnDamage(&mAtCps[1], &sp8) ||
                checkElecReturnDamage(&mAtCps[2], &sp8)
            ) {
                setDamagePoint(-1.0f);
                onResetFlg0(daPyRFlg0_UNK80000);
                setDamageElecEmitter();
                changePlayer(this);
                
                if (procElecDamage_init(&sp8)) {
                    return TRUE;
                }
                
                if (daPy_lk_c::checkPlayerFly()) {
                    return procLargeDamage_init(-1, 1, 0, 0);
                } else {
                    return procDamage_init();
                }
            }
        }
        
        if (mCyl.ChkTgHit() && !checkGuardSlip() &&
            (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) || !checkNoDamageMode())
        ) {
            freeRopeItem();
            freeHookshotItem();
            
            if (!checkSuccessGuard(spl)) {
                if (mEquipItem == daPyItem_BOKO_e) {
                    deleteEquipItem(FALSE);
                }
                
                setDamageEmitter();
                changePlayer(this);
                setDamagePoint(-damage);
                fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
                if (daPy_dmEcallBack_c::checkElec()) {
                    if (procElecDamage_init(NULL)) {
                        return TRUE;
                    }
                }
                
                if (checkModeFlg(ModeFlg_IN_SHIP)) {
                    return procLargeDamage_init(-9, 1, 0, 0);
                }
                
                if (checkGrabWear() &&
                    mCyl.GetTgHitAc() && fopAcM_GetName(mCyl.GetTgHitAc()) == PROC_NZ &&
                    grab_actor != NULL
                ) {
                    cXyz* damage_vec = getDamageVec(&mCyl);
                    grab_actor->shape_angle.y = cM_atan2s(damage_vec->x, damage_vec->z);
                    grab_actor->shape_angle.x = 0x2000;
                    return procLargeDamage_init(-4, 1, 0, 0);
                }
                if (spl == 7 || spl == 2 || spl == 10) {
                    return procLargeDamage_init(-6, 0, 0, 0);
                }
                if (daPy_lk_c::checkPlayerFly() || spl == 6 || spl == 1 || spl == 9) {
                    return procLargeDamage_init(-1, 1, 0, 0);
                }
                if (checkNormalDamage(damage)) {
                    return procDamage_init();
                }
                setDashDamage();
            } else {
                u8 hitSe = mCyl.GetTgHitObjSe();
                if (hitSe == dCcG_SE_UNK6) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_N_BDY_MPLT);
                } else if (hitSe == dCcG_SE_UNK2 || hitSe == dCcG_SE_UNK5) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_SWS_NMTLP);
                } else if (hitSe == dCcG_SE_UNK4) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_NWHP_NMTL);
                } else {
                    seStartOnlyReverb(JA_SE_OBJ_COL_SWM_NSWL);
                }
                
                if (mCurProc == daPyProc_CROUCH_DEFENSE_e) {
                    return procCrouchDefenseSlip_init();
                } else {
                    return procGuardSlip_init();
                }
            }
        } else if (r30) {
            changePlayer(this);
            if (mEquipItem == daPyItem_BOKO_e) {
                deleteEquipItem(FALSE);
            }
            setDamagePoint(-damage);
            
            if (attribCode == dBgS_Attr_ELECTRICITY_e) {
                setDamageElecEmitter();
                if (procElecDamage_init(NULL)) {
                    return TRUE;
                }
            }
            
            if (checkNormalDamage(damage)) {
                return procPolyDamage_init();
            }
            
            setDashDamage();
        }
    }
    
    mStts.ClrTg();
    mStts.ClrAt();
    
    return FALSE;
}

/* 80110F3C-80111424       .text changeAutoJumpProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeAutoJumpProc() {
    if ((!checkModeFlg(ModeFlg_MIDAIR | ModeFlg_ROPE | ModeFlg_IN_SHIP | ModeFlg_CLIMB |
                       ModeFlg_SWIM | ModeFlg_LADDER | ModeFlg_CAUGHT)) &&
        !mAcch.ChkGroundHit())
    {
        f32 dVar11 = mAcch.GetGroundH() - current.pos.y;
        mLavaGndChk.SetPos(&current.pos);
        if (checkNoResetFlg0(daPyFlg0_HOVER_BOOTS)) {
            offNoResetFlg0(daPyFlg0_HOVER_BOOTS);
            return procFall_init(2, m_HIO->mWallCatch.m.field_0x54);
        }
        
        if (dVar11 < -30.1f) {
            f32 dVar8 = speed.x + m3730.x + m36A0.x + m36B8.x;
            f32 dVar9 = speed.z + m3730.z + m36A0.z + m36B8.z;
            f32 dVar10 = std::sqrtf(dVar8 * dVar8 + dVar9 * dVar9);
            if (dVar10 > 0.001f) {
                s16 sVar3 = cM_atan2s(dVar8, dVar9);
                dVar9 = cM_ssin(sVar3);
                dVar8 = cM_scos(sVar3);
                current.pos.y = current.pos.y - speed.y;
                cXyz local_74;
                cXyz local_68;
                local_74.x = current.pos.x;
                local_74.y = current.pos.y - 5.0f;
                local_74.z = current.pos.z;
                local_68.x = local_74.x - (50.0f * dVar9);
                local_68.y = local_74.y;
                local_68.z = local_74.z - (50.0f * dVar8);
                mLinkLinChk.Set(&local_74, &local_68, this);
                cM3dGPla* pcVar4;
                if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                    pcVar4 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
                } else {
                    pcVar4 = NULL;
                }
                dVar10 = mVelocity;
                if (dComIfGs_getLife() != 0 || dComIfGs_checkBottle(dItem_FAIRY_BOTTLE_e)) {
                    if (m357C != 3 && !checkGrabWear() && dVar10 >= m_HIO->mAutoJump.m.field_0x14 &&
                        mStickDistance > 0.85f && cLib_distanceAngleS(sVar3, shape_angle.y) < 0x800)
                    {
                        if (pcVar4 != NULL) {
                            current.pos.x = mLinkLinChk.GetCrossP()->x;
                            current.pos.z = mLinkLinChk.GetCrossP()->z;
                        }
                        return procAutoJump_init();
                    }
                    if (pcVar4 != NULL && std::abs(pcVar4->GetNP()->y) <= 0.05f &&
                        dComIfG_Bgsp()->GetWallCode(mLinkLinChk) != 2 && dVar11 < -125.0f &&
                        m35D0 - current.pos.y < -125.0f && current.pos.y - m35D4 > 125.0f)
                    {
                        current.pos.x = mLinkLinChk.GetCrossP()->x;
                        current.pos.z = mLinkLinChk.GetCrossP()->z;
                        if (dComIfG_Bgsp()->GetWallCode(mLinkLinChk) == 1) {
                            mPolyInfo = mLinkLinChk;
                            return procClimbDownStart_init(
                                cM_atan2s(pcVar4->mNormal.x, pcVar4->mNormal.z));
                        }
                        if (procHangFallStart_init(pcVar4)) {
                            return true;
                        }
                    }
                }
                f32 fVar1;
                if (mCurProc == daPyProc_FRONT_ROLL_e) {
                    fVar1 = 0.0f;
                } else {
                    fVar1 = m_HIO->mWallCatch.m.field_0x54;
                }
                dVar11 = fVar1;
                if (pcVar4 != NULL) {
                    current.pos.x = current.pos.x + 35.0f * pcVar4->GetNP()->x;
                    current.pos.z = current.pos.z + 35.0f * pcVar4->GetNP()->z;
                } else {
                    current.pos.x = current.pos.x + 35.0f * dVar9;
                    current.pos.z = current.pos.z + 35.0f * dVar8;
                }
            } else {
                dVar11 = m_HIO->mWallCatch.m.field_0x54;
            }
            if (mStaffIdx != -1 && dComIfGp_evmng_getMyIntegerP(mStaffIdx, "fall")) {
                return procFall_init(0, dVar11);
            } else {
                return procFall_init(1, dVar11);
            }
        }
    }
    return false;
}

/* 80111424-80111A80       .text changeDemoProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeDemoProc() {
    static const Vec tact_scale = {2.5f, 2.5f, 2.5f};

    if (!dComIfGp_event_runCheck()) {
        return false;
    }
    if (checkNoResetFlg1(daPyFlg1_SHIP_TACT)) {
        if (mEquipItem != daPyItem_UNK10A_e) {
            deleteEquipItem(FALSE);
            setTactModel();
            mEquipItem = daPyItem_UNK10A_e;
            mpEquipItemModel->setBaseScale(tact_scale);
        }
    } else if (mEquipItem == daPyItem_UNK10A_e) {
        deleteEquipItem(FALSE);
    }
    u32 demo_mode = mDemo.getDemoMode();
    JUT_ASSERT(VERSION_SELECT(9293, 9293, 9342, 9342), (demo_mode < daPy_demo_c::DEMO_LAST_e) || (demo_mode == daPy_demo_c::DEMO_NEW_ANM0_e));
    if (demo_mode != daPy_demo_c::DEMO_NEW_ANM0_e && demo_mode != daPy_demo_c::DEMO_UNK_030_e &&
        demo_mode != daPy_demo_c::DEMO_LDAM_e && demo_mode != daPy_demo_c::DEMO_PFALL_e &&
        demo_mode != daPy_demo_c::DEMO_SFALL_e && demo_mode != daPy_demo_c::DEMO_INIT_WAIT_e &&
        demo_mode != daPy_demo_c::DEMO_VOLCANO_e && demo_mode != daPy_demo_c::DEMO_S_WARP_e)
    {
        if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && !dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e))
        {
            if (!mAcch.ChkGroundHit() || daPy_lk_c::checkPlayerFly()) {
                return false;
            }
        }
    }
    if (demo_mode == daPy_demo_c::DEMO_NEW_ANM0_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return dProcTool_init();
    }
    if (mDemoProcInitFuncTable[demo_mode] != NULL) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return (this->*mDemoProcInitFuncTable[demo_mode])();
    }
    if (demo_mode == daPy_demo_c::DEMO_INIT_WAIT_e) {
        int var_r28;
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            return true;
        }
        var_r28 = procWait_init();
        if (var_r28 != 0) {
            m_old_fdata->initOldFrameMorf(0.0f, 0, 0x2A);
        }
        return var_r28;
    }
    if ((demo_mode == daPy_demo_c::DEMO_N_TALK_e) || demo_mode == daPy_demo_c::DEMO_E_TALK_e) {
        if (checkModeFlg(ModeFlg_04000000)) {
            return true;
        }
        if ((dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && fopAcM_getTalkEventPartner(this) != NULL) &&
            fopAcM_getTalkEventPartner(this) == dComIfGp_getShipActor())
        {
            return procShipPaddle_init();
        }
        onNoResetFlg0(daPyFlg0_UNK100000);
        fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
        if (grab_actor != NULL) {
            if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e) && !checkGrabSpecialHeavyState()) {
                return procGrabThrow_init(0);
            } else {
                return procGrabPut_init();
            }
        } else {
            return dProcTalk_init();
        }
    } else if (demo_mode == daPy_demo_c::DEMO_LDAM_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        if ((mCurProc == daPyProc_LARGE_DAMAGE_UP_e) || mCurProc == daPyProc_LARGE_DAMAGE_WALL_e) {
            return false;
        }
        if (checkModeFlg(ModeFlg_SWIM)) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            return false;
        } else {
            return procLargeDamage_init(-3, 1, 0, 0);
        }
    } else if (demo_mode == daPy_demo_c::DEMO_UNK_027_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return procLargeDamageUp_init(-3, 1, 0, 0);
    } else if (demo_mode == daPy_demo_c::DEMO_BJUMP_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        if (mCurProc == daPyProc_BACK_JUMP_LAND_e) {
            return false;
        }
        return procBackJump_init();
    } else if (demo_mode == daPy_demo_c::DEMO_PFALL_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return procFall_init(1, m_HIO->mWallCatch.m.field_0x54);
    } else if (demo_mode == daPy_demo_c::DEMO_SFALL_e) {
        if (mCurProc == daPyProc_LAND_e) {
            return true;
        }
        return procSlowFall_init();
    } else if (demo_mode == daPy_demo_c::DEMO_LWAIT_e) {
        if ((!checkModeFlg(
                 ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP | ModeFlg_CLIMB | ModeFlg_SWIM |
                 ModeFlg_LADDER | ModeFlg_04000000 | ModeFlg_CAUGHT
             ) &&
             (checkUpperReadyThrowAnime() || m34C3 == 2 || m34C3 == 1 || m34C3 == 4 || m34C3 == 9 || m34C3 == 10 ||
              mCurProc == daPyProc_GRAB_WAIT_e)) ||
            dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e))
        {
            onNoResetFlg0(daPyFlg0_UNK100000);
            return dProcLookWait_init();
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            return true;
        }
    } else if (demo_mode == daPy_demo_c::DEMO_TACT_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        if (mCurProc == daPyProc_TACT_PLAY_e || mCurProc == daPyProc_TACT_PLAY_END_e) {
            return true;
        }
        return procTactWait_init(mDemo.getParam0());
    } else if (demo_mode == daPy_demo_c::DEMO_UNK_051_e) {
        fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
        if (grab_actor == NULL || grab_actor != dComIfGp_getCb1Player()) {
            deleteEquipItem(FALSE);
            freeGrabItem();
            mActorKeepGrab.setData(dComIfGp_getCb1Player());
            fopAcM_setCarryNow(mActorKeepGrab.getActor(), TRUE);
        }
        return procGrabWait_init();
    } else if (demo_mode == daPy_demo_c::DEMO_BO_OPEN_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return procBottleOpen_init(dComIfGp_event_getPreItemNo());
    } else if (((checkNoResetFlg0(daPyFlg0_UNK100000) || mCurProc == daPyProc_SUBJECTIVITY_e) ||
                checkUpperReadyThrowAnime()) &&
               (demo_mode == daPy_demo_c::DEMO_KM_WAIT_e || demo_mode == daPy_demo_c::DEMO_N_WAIT_e ||
                demo_mode == daPy_demo_c::DEMO_N_WALK_e || demo_mode == daPy_demo_c::DEMO_N_DASH_e ||
                (demo_mode == daPy_demo_c::DEMO_A_WAIT_e || demo_mode == daPy_demo_c::DEMO_UNK_018_e)))
    {
        offNoResetFlg0(daPyFlg0_UNK100000);
        if (checkUpperReadyThrowAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            return procShipPaddle_init();
        } else {
            return checkNextMode(0);
        }
    }
    return false;
}

/* 80111A80-80111B80       .text changeDeadProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeDeadProc() {
    if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 && dComIfGs_getLife() == 0 &&
        !checkModeFlg(ModeFlg_DAMAGE))
    {
        if (dComIfGs_checkBottle(dItem_FAIRY_BOTTLE_e)) {
            makeFairy(&current.pos, daNpc_Fa1_c::Type_LINK_DOWN_e);
            dComIfGs_setBottleItemIn(dItem_FAIRY_BOTTLE_e, dItem_EMPTY_BOTTLE_e);
            return false;
        }
        if (mAcch.ChkGroundHit() || dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) ||
            checkModeFlg(ModeFlg_SWIM))
        {
            return dProcDead_init();
        }
        return procFall_init(1, m_HIO->mWallCatch.m.field_0x54);
    } else {
        return false;
    }
}

/* 80111B80-80111D64       .text getDamageVec__9daPy_lk_cFP12dCcD_GObjInf */
cXyz* daPy_lk_c::getDamageVec(dCcD_GObjInf* i_hitObj) {
    cXyz* vec = i_hitObj->GetTgRVecP();
    cXyz sp40;

    f32 var_f31 = vec->abs2XZ();
    if (checkResetFlg0(daPyRFlg0_UNK80000)) {
        sp40.set(cM_ssin(shape_angle.y) * -10.0f, 0.0f, cM_scos(shape_angle.y) * -10.0f);
        i_hitObj->SetTgRVec(sp40);
    } else if (var_f31 < 0.1f) {
        sp40 = current.pos - *i_hitObj->GetTgHitPosP();
        var_f31 = sp40.abs2();
        if (var_f31 < 0.1f) {
            sp40.x = cM_ssin(shape_angle.y) * -10.0f;
            sp40.y = 0.0f;
            sp40.z = cM_scos(shape_angle.y) * -10.0f;
        } else {
            sp40 *= 10.0f / std::sqrtf(var_f31);
        }
        i_hitObj->SetTgRVec(sp40);
    }
    return vec;
}

/* 80111D64-80111E54       .text setOldRootQuaternion__9daPy_lk_cFsss */
void daPy_lk_c::setOldRootQuaternion(s16 param_1, s16 param_2, s16 param_3) {
    Quaternion afStack_28;
    Quaternion local_38;

    if (m_old_fdata->getOldFrameFlg() != false) {
        Quaternion* pQVar1 = m_old_fdata->getOldFrameQuaternion(0);
        if (param_1 != 0 || param_2 != 0) {
            JMAEulerToQuat(param_1, param_2, 0, &afStack_28);
            local_38 = *pQVar1;
            mDoMtx_QuatConcat(&afStack_28, &local_38, m_old_fdata->getOldFrameQuaternion(0));
        }
        if (param_3 != 0) {
            JMAEulerToQuat(0, 0, param_3, &afStack_28);
            local_38 = *pQVar1;
            mDoMtx_QuatConcat(&afStack_28, &local_38, m_old_fdata->getOldFrameQuaternion(0));
        }
    }
}

/* 80111E54-80111EFC       .text checkRestHPAnime__9daPy_lk_cFv */
BOOL daPy_lk_c::checkRestHPAnime() {
    if (!checkPlayerGuard() && checkNoUpperAnime() && mpAttnActorLockOn == NULL &&
        ((mDemo.getDemoType() == 0 && !checkModeFlg(ModeFlg_IN_SHIP) &&
          dComIfGs_getLife() <= m_HIO->mMove.m.field_0xE) ||
         mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK_018_e))
    {
        return true;
    }
    return false;
}

/* 80111EFC-80111F5C       .text checkHeavyStateOn__9daPy_lk_cFv */
BOOL daPy_lk_c::checkHeavyStateOn() {
    if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 &&
        (getHeavyStateAndBoots() || checkGrabSpecialHeavyState())
    ) {
        return TRUE;
    }
    return FALSE;
}

/* 80111F5C-80111F7C       .text checkBottleItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkBottleItem(int itemNo) const {
    return itemNo >= dItem_EMPTY_BOTTLE_e && itemNo <= UNK_BOTTLE_60;
}

/* 80111F7C-80111FEC       .text checkDrinkBottleItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkDrinkBottleItem(int itemNo) const {
    return itemNo == dItem_RED_POTION_e || itemNo == dItem_GREEN_POTION_e || itemNo == dItem_BLUE_POTION_e || itemNo == dItem_SOUP_BOTTLE_e || itemNo == dItem_HALF_SOUP_BOTTLE_e;
}

/* 80111FEC-8011201C       .text checkOpenBottleItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkOpenBottleItem(int itemNo) const {
    return itemNo == dItem_FIREFLY_BOTTLE_e || itemNo == dItem_WATER_BOTTLE_e || itemNo == dItem_FOREST_WATER_e || itemNo == dItem_FAIRY_BOTTLE_e;
}

/* 8011201C-80112044       .text checkBowItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkBowItem(int itemNo) const {
    return itemNo == dItem_BOW_e || itemNo == dItem_MAGIC_ARROW_e || itemNo == dItem_LIGHT_ARROW_e;
}

/* 80112044-80112064       .text checkPhotoBoxItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkPhotoBoxItem(int itemNo) const {
    return itemNo == CAMERA || itemNo == CAMERA2;
}

/* 80112064-80112100       .text checkScopeEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::checkScopeEnd() {
    if (dComIfGp_getScopeMesgStatus() == fopMsgStts_UNKB_e &&
        (cancelTrigger() || checkNoResetFlg0(daPyFlg0_SCOPE_CANCEL)))
    {
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e) || cancelTrigger()) {
            seStartSystem(JA_SE_ITM_SUBMENU_OUT);
        }
        return true;
    }
    return false;
}

/* 80112100-8011215C       .text setSubjectMode__9daPy_lk_cFv */
void daPy_lk_c::setSubjectMode() {
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000_e);
    seStartSystem(JA_SE_SUBJ_VIEW_IN);
}

/* 8011215C-801121C8       .text checkMaskDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::checkMaskDraw() {
    dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
    if (demo_actor == NULL && dComIfGs_isCollect(4, 1)) {
        return true;
    } else {
        return false;
    }
}

/* 801121C8-80112280       .text checkSubjectEnd__9daPy_lk_cFi */
BOOL daPy_lk_c::checkSubjectEnd(BOOL i_playSound) {
    // TODO: these trigger/button checks are likely inlines
    if(dComIfGp_event_runCheck() || (mItemTrigger & (BTN_A | BTN_B)) || (mItemButton & BTN_L) || dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x2000)) {
        if(i_playSound) {
            seStartSystem(JA_SE_SUBJ_VIEW_OUT);
        }

        onResetFlg0(daPyRFlg0_UNK10000000);
        return true;
    }

    return false;
}

/* 80112280-80112330       .text checkGuardAccept__9daPy_lk_cFv */
BOOL daPy_lk_c::checkGuardAccept() {
    if (checkModeFlg(ModeFlg_00000040) && !checkBowAnime()) {
        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_MISC_e ||
            strcmp(dComIfGp_getStartStageName(), "Ojhous") == 0 ||
            strcmp(dComIfGp_getStartStageName(), "Orichh") == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/* 80112330-80112348       .text cancelNoDamageMode__9daPy_lk_cFv */
void daPy_lk_c::cancelNoDamageMode() {
    offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
    mTinkleShieldTimer = 0;
}

/* 80112348-80112954       .text commonProcInit__9daPy_lk_cFQ29daPy_lk_c9daPy_PROC */
BOOL daPy_lk_c::commonProcInit(daPy_PROC proc) {
    ProcInitTableEntry& procInit = mProcInitTable[proc];
    
    BOOL temp_r29;
    BOOL resetDemoAnime = FALSE;
    BOOL temp_r28;
    
    if (mCurProc == daPyProc_SLIP_e) {
        mDoAud_seStop(JA_SE_LK_RUN_SLIP);
    } else if (mCurProc == daPyProc_GRAB_MISS_e || (mCurProc == daPyProc_GRAB_READY_e && proc != daPyProc_GRAB_MISS_e)) {
        mActorKeepRope.clearData();
    } else if (mCurProc == daPyProc_DEMO_TALISMAN_WAIT_e) {
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        mpEquipItemModel = NULL;
    } else if (mCurProc == daPyProc_FAN_SWING_e) {
        setSmallFanModel();
    } else if (mCurProc == daPyProc_FAN_GLIDE_e) {
        deleteEquipItem(FALSE);
        maxFallSpeed = m_HIO->mAutoJump.m.field_0x10;
        setSmallFanModel();
        mEquipItem = dItem_DEKU_LEAF_e;
        m35F0 = m3688.y;
        m3730 = cXyz::Zero;
        m34E0 = 0;
        m34E4 = 0;
    } else if (mCurProc == daPyProc_SLOW_FALL_e) {
        maxFallSpeed = m_HIO->mAutoJump.m.field_0x10;
    } else if (mCurProc == daPyProc_DEMO_TOOL_e) {
        resetDemoAnime = TRUE;
        speed.y = 0.0f;
    } else if (mCurProc == daPyProc_DEMO_GET_ITEM_e || mCurProc == daPyProc_DEMO_GET_DANCE_e) {
        dKy_Itemgetcol_chg_off();
        if (mCurProc == daPyProc_DEMO_GET_ITEM_e && m34D8 != 0) {
            m34C2 = 0xB;
        }
    } else if (mCurProc == daPyProc_DEMO_PRESENT_e || mCurProc == daPyProc_NOT_USE_e) {
        daItemBase_c* item = (daItemBase_c*)fopAcM_getItemEventPartner(this);
        if (item && (fopAcM_GetName(item) == PROC_ITEM || fopAcM_GetName(item) == PROC_Demo_Item)) {
            item->dead();
        }
    } else if (mCurProc == daPyProc_DEMO_LETTER_READ_e) {
        deleteEquipItem(FALSE);
    } else if (mCurProc == daPyProc_CUT_ROLL_END_e) {
        if (m33A8.getEmitter()) {
            m33A8.getEmitter()->setGlobalAlpha(0);
        }
    } else if (mCurProc == daPyProc_SHIP_BOW_e) {
        deleteArrow();
    }
    
    returnKeepItemData();
    
    if (checkModeFlg(ModeFlg_SWIM)) {
        temp_r28 = TRUE;
    } else {
        temp_r28 = FALSE;
    }
    
    // TODO: is this an inline?
    if (checkModeFlg(ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_SWIM | ModeFlg_CAUGHT)) {
        m34C2 = 0xA;
    }
    
    if (checkModeFlg(ModeFlg_MIDAIR)) {
        temp_r29 = FALSE;
    } else {
        temp_r29 = TRUE;
    }
    
    mCurProc = proc;
    mCurProcFunc = procInit.mProcFunc;
    m3598 = 0.0f;
    mModeFlg = procInit.mProcFlags;
    
    if (m34C2 == 1) {
        m34C2 = 2;
    }
    
    // TODO: is this an inline?
    if (checkModeFlg(ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_SWIM | ModeFlg_CAUGHT)) {
        m34C2 = 0xB;
    }
    
    if (checkModeFlg(ModeFlg_HANG)) {
        mAcch.OffLineCheck();
    } else {
        mAcch.OnLineCheck();
    }
    
    dComIfGp_clearPlayerStatus0(0, ~(daPyStts0_BOOMERANG_WAIT_e | daPyStts0_UNK10_e));
    dComIfGp_clearPlayerStatus1(0, ~(daPyStts1_SAIL_e | daPyStts1_UNK8000_e | daPyStts1_UNK40000_e) & 0x000FFFFF);
    
    gravity = m_HIO->mAutoJump.m.field_0xC;
    m34F2 = 0;
    m34F4 = 0;
    onResetFlg0(daPyRFlg0_UNK8000000);
    m34C5 = 0;
    offNoResetFlg0(daPyFlg0_UNK4);
    offResetFlg0(daPyRFlg0_UNK2);
    offNoResetFlg1(daPyFlg1_UNK8000000);
    
    m3544 = 0;
    mSightPacket.offDrawFlg();
    mSightPacket.offLockFlg();
    m35C4 = 0.0f;
    mFanSwingCb.onAlphaOutFlg();
    shape_angle.x = 0;
    shape_angle.z = 0;
    m34EC = 0;
    
    if (!(checkEquipAnime() && checkModeFlg(ModeFlg_00000004)) && !checkModeFlg(ModeFlg_00001000)) {
        if (!(checkGrabAnime() || checkBoomerangThrowAnime()) || !checkModeFlg(ModeFlg_00004000)) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
            if (!checkModeFlg(ModeFlg_GRAB)) {
                freeGrabItem();
            }
        }
    }
    
    if (!checkModeFlg(ModeFlg_GRAB) && !checkGrabAnime() && mActorKeepGrab.getActor()) {
        freeGrabItem();
    }
    
    if (temp_r29 && checkModeFlg(ModeFlg_MIDAIR)) {
        m3688 = current.pos;
        m35F0 = m3688.y;
        m35F4 = m3688.y;
    }
    
    if (mCurProc != daPyProc_SWIM_MOVE_e) {
        mSwimTailEcallBack[0].onEnd();
        mSwimTailEcallBack[1].onEnd();
    }
    
    if (!checkModeFlg(ModeFlg_SWIM)) {
        m3608 = 0.0f;
    }
    
    resetFootEffect();
    
    if (resetDemoAnime) {
        resetDemoTextureAnime();
    }
    
    m338C.end();
    m33A8.end();
    m32E4.end();
    m32F0.end();
    mSmokeEcallBack.remove();
    
    if (!checkGrabWear()) {
        m35D8 = 0.0f;
    }
    
    offNoResetFlg1(static_cast<daPy_FLG1>(daPyFlg1_UNK80 | daPyFlg1_UNK800000 | daPyFlg1_UNK1000000));
    
    m35EC = 0.0f;
    
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_HAMMERDAM));
    } else if (checkBowItem(mEquipItem) && !checkBowAnime()) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_ARROWRELORDA));
    }
    
    m35E8 = 0.0f;
    
    if (!checkModeFlg(ModeFlg_ROPE) && mCurProc != daPyProc_ROPE_SUBJECT_e && mCurProc != daPyProc_ROPE_MOVE_e) {
        freeRopeItem();
    }
    if (!checkModeFlg(ModeFlg_HOOKSHOT)) {
        freeHookshotItem();
    }
    if (temp_r28 && !checkModeFlg(ModeFlg_SWIM)) {
        swimOutAfter(FALSE);
    }
    
    dComIfGp_setAdvanceDirection(0);
    
    setBgCheckParam();
    
    return TRUE;
}

/* 80112954-80112A24       .text procScope_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procScope_init(int param_1) {
    commonProcInit(daPyProc_SCOPE_e);
    mVelocity = 0.0f;
    setBlendMoveAnime(m_HIO->mBasic.m.field_0xC);
    current.angle.y = shape_angle.y;
    seStartSystem(JA_SE_ITM_SUBMENU_IN_1);
    offNoResetFlg0(daPyFlg0_SCOPE_CANCEL);
    if (param_1 == 0x20) {
        dComIfGp_setPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e);
    } else {
        dComIfGp_setPlayerStatus1(0, daPyStts1_PICTO_BOX_AIM_e);
    }
    return true;
}

/* 80112A24-80112AA8       .text procScope__9daPy_lk_cFv */
BOOL daPy_lk_c::procScope() {
    if (checkScopeEnd()) {
        procWait_init();
    } else {
        if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x10)) {
            shape_angle.y = fopCamM_GetAngleY(dComIfGp_getCamera(mCameraInfoIdx));
            current.angle.y = shape_angle.y;
        }
    }
    offNoResetFlg0(daPyFlg0_SCOPE_CANCEL);
    return true;
}

/* 80112AA8-80112B18       .text procSubjectivity_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSubjectivity_init(BOOL i_crouch) {
    commonProcInit(daPyProc_SUBJECTIVITY_e);

    mVelocity = 0.0f;

    setSubjectMode();

    if(!i_crouch) {
        setBlendMoveAnime(m_HIO->mBasic.m.field_0xC);
    }

    mProcVar0.m3570 = i_crouch;

    return true;
}

/* 80112B18-80112BEC       .text procSubjectivity__9daPy_lk_cFv */
BOOL daPy_lk_c::procSubjectivity() {
    dComIfGp_setAStatus(dActStts_RETURN_e);

    if(
        checkSubjectEnd(FALSE) ||
        (mProcVar0.m3570 != 0 && !spActionButton() // Player released R while crouching
    )) {
        seStartSystem(JA_SE_SUBJ_VIEW_OUT);
        if(mProcVar0.m3570 != 0) {
            if(mEquipItem == daPyItem_NONE_e) {
                return procCrouch_init();
            }

            return procCrouchDefense_init();
        }

        changeWaitProc();
    }
    else {
        setBodyAngleToCamera();
    }

    return true;
}

/* 80112BEC-80112C90       .text procCall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCall_init() {
    commonProcInit(daPyProc_CALL_e);
    mVelocity = 0.0f;
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(ANM_YOBU, 1.0f, 0.0f, -1, m_HIO->mBasic.m.field_0xC);
    current.angle.y = shape_angle.y;
    if (mEquipItem == daPyItem_BOKO_e) {
        deleteEquipItem(FALSE);
    }
    voiceStart(0x2A);
    return TRUE;
}

/* 80112C90-80112D38       .text procCall__9daPy_lk_cFv */
BOOL daPy_lk_c::procCall() {
    if (dComIfGp_getCb1Player() != NULL) {
        s16 targetAngle = cLib_targetAngleY(&current.pos, &dComIfGp_getCb1Player()->eyePos);
        cLib_addCalcAngleS(&shape_angle.y, targetAngle, 2, 0x2000, 0x800);
        current.angle.y = shape_angle.y;
    }
    
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (dComIfGp_getCb1Player() != NULL) {
            daPy_py_c* partner = (daPy_py_c*)dComIfGp_getCb1Player();
            partner->onNpcCallCommand();
        }
        checkNextMode(0);
    }
    
    return TRUE;
}

/* 80112D38-80112DF4       .text procControllWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procControllWait_init() {
    if (mCurProc == daPyProc_CONTROLL_WAIT_e) {
        return false;
    }
    int iVar3 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_CONTROLL_WAIT_e);
    mVelocity = 0.0f;
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(ANM_NENRIKI, 1.0f, 0.0f, -1, m_HIO->mBasic.m.field_0xC);
    current.angle.y = shape_angle.y;
    deleteEquipItem(FALSE);
    initShipRideUseItem(iVar3, 2);
    return true;
}

/* 80112DF4-80112E60       .text procControllWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procControllWait() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePosUseItem();
        if (daPy_getPlayerActorClass() == this) {
            procShipPaddle_init();
        }
    } else {
        checkNextMode(0);
    }
    return true;
}

/* 80112E60-80113044       .text procWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWait_init() {
    if (mDemo.getDemoMode() == daPy_demo_c::DEMO_KM_WAIT_e && m_tex_scroll_heap.field_0x6 == 0xFFFF) {
        changeTextureAnime(LKANM_BTP_TMABACC, LKANM_BTK_TEUR, -1);
        voiceStart(38);
        m34D0 = 0x14;
    }
    if (mCurProc == daPyProc_WAIT_e) {
        return false;
    }
    if (!dComIfGp_event_runCheck() && mCurProc == daPyProc_FREE_WAIT_e &&
        mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > 0.01f && checkNoUpperAnime())
    {
        return false;
    }
    int iVar3 = checkPlayerGuard();
    commonProcInit(daPyProc_WAIT_e);
    mVelocity = 0.0f;
    int iVar4 = checkRestHPAnime();
    if (iVar4 != 0 && iVar3 == 0) {
        s32 uVar2 = m_tex_anm_heap.mIdx == mTexAnmIndexTable[daPyFace_TMABAF].mBtpIdx;
        u16 uVar1 = m3530;
        setSingleMoveAnime(ANM_WAITATOB, m_HIO->mMove.m.field_0x68,
                           m_HIO->mMove.m.field_0x6C, m_HIO->mMove.m.field_0x10,
                           m_HIO->mMove.m.field_0x70);
        if (uVar2 == 0) {
            onModeFlg(ModeFlg_00000400);
            offModeFlg(ModeFlg_00000100);
        } else {
            setTextureAnime(0xe, uVar1);
        }
    } else {
        setBlendMoveAnime(m_HIO->mBasic.m.field_0xC);
    }
    current.angle.y = shape_angle.y;
    mDirection = DIR_NONE;
    m35A0 = 0.0f;
    f32 dVar5 = cM_rndF(150.0f);
    m34D2 = (s16)(300.0f + dVar5);
    return true;
}

/* 80113044-801133FC       .text procWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procWait() {
    if (m36A0.abs2XZ() <= SQUARE(1.0f / 1000.0f) && m36AC.abs2XZ() >= SQUARE(5.0f)) {
        return procIceSlipAlmostFall_init();
    }
    if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 && spLTrigger() && mAcch.ChkWallHit()) {
        dBgS_AcchCir* pdVar5 = &mAcchCir[0];
        for (int i = 0; i < 3; i++, pdVar5++) {
            if (pdVar5->ChkWallHit()) {
                s16 sVar4 = pdVar5->GetWallAngleY() + 0x8000;
                if (cLib_distanceAngleS(shape_angle.y, sVar4) <= 0x2000) {
                    shape_angle.y = sVar4;
                    current.angle.y = shape_angle.y;
                    m34E6 = shape_angle.y;
                }
                break;
            }
        }
    }
    s16 sVar2 = shape_angle.y;
    if (checkAttentionLock()) {
        setSpeedAndAngleAtn();
    } else {
        setSpeedAndAngleNormal(m_HIO->mMove.m.field_0x0);
    }
    m35A0 = 0.0f;
    if (!checkNextMode(0)) {
        if (m34C3 == 0) {
            if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f || !checkRestHPAnime()) {
                setBlendMoveAnime(m_HIO->mBasic.m.field_0xC);
                offModeFlg(ModeFlg_00000400);
                onModeFlg(ModeFlg_00000100);
            }
        } else if (checkRestHPAnime() &&
                   m_anm_heap_under[UNDER_MOVE0_e].mIdx != LKANM_BCK_WAITB)
        {
            s32 uVar3 = m_tex_anm_heap.mIdx == mTexAnmIndexTable[daPyFace_TMABAF].mBtpIdx;
            u16 uVar1 = m3530;
            setSingleMoveAnime(ANM_WAITATOB, m_HIO->mMove.m.field_0x68,
                               m_HIO->mMove.m.field_0x6C, m_HIO->mMove.m.field_0x10,
                               m_HIO->mMove.m.field_0x70);
            if (uVar3 == 0) {
                onModeFlg(ModeFlg_00000400);
                offModeFlg(ModeFlg_00000100);
            } else {
                setTextureAnime(0xe, uVar1);
            }
        } else {
            m35A0 = 0.005f * (s16)(shape_angle.y - sVar2);
            setBlendMoveAnime(-1.0f);
        }
        if (mDemo.getDemoMode() == daPy_demo_c::DEMO_KM_WAIT_e) {
            if (m34D0 != 0) {
                m34D0--;
            } else if (cM_rnd() < 0.05f) {
                voiceStart(38);
                m34D0 = 0x14;
            }
        }
        if (!dComIfGp_event_runCheck() && m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_WAITS &&
            checkNoUpperAnime() && daPy_matAnm_c::m_eye_move_flg == 0 && m3566 == 0 && m3568 == 0 && m3564 == 0)
        {
            m34D2--;
            if (m34D2 == 0) {
                procFreeWait_init();
            }
        } else {
            m34D2 = (s16)(300.0f + cM_rndF(150.0f));
        }
    }
    return true;
}

/* 801133FC-801134A0       .text procFreeWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFreeWait_init() {
    daPy_ANM dVar1;
    f32 dVar2;

    commonProcInit(daPyProc_FREE_WAIT_e);
    mVelocity = 0.0f;
    dVar2 = cM_rnd();
    mProcVar0.m3570 = 0;
    if (dVar2 < 0.3333f) {
        dVar1 = ANM_FREEA;
    } else {
        if (dVar2 < 0.6666f) {
            dVar1 = ANM_FREEB;
            mProcVar0.m3570 = 1;
        } else {
            dVar1 = ANM_FREED;
        }
    }
    setSingleMoveAnime(dVar1, 1.0f, 0.0f, -1, 5.0f);
    current.angle.y = shape_angle.y;
    mDirection = DIR_NONE;
    return true;
}

/* 801134A0-801135C4       .text procFreeWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procFreeWait() {
    if (checkAttentionLock()) {
        setSpeedAndAngleAtn();
    } else {
        setSpeedAndAngleNormal(m_HIO->mMove.m.field_0x0);
    }
    if (mProcVar0.m3570 != 0) {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].checkPass(168.0f)) {
            voiceStart(48);
        } else {
            if (mFrameCtrlUnder[UNDER_MOVE0_e].checkPass(105.0f)) {
                voiceStart(47);
            }
        }
    }
    if (!checkNextMode(0) && dComIfGp_event_runCheck()) {
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
        procWait_init();
    }
    return true;
}

/* 801135C4-80113628       .text procMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procMove_init() {
    if (mCurProc == daPyProc_MOVE_e) {
        return false;
    }
    commonProcInit(daPyProc_MOVE_e);
    setBlendMoveAnime(m_HIO->mBasic.m.field_0xC);
    m34D0 = 0x14;
    return true;
}

/* 80113628-801136D4       .text procMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procMove() {
    setSpeedAndAngleNormal(m_HIO->mMove.m.field_0x0);
    if (!checkNextMode(0) && !changeFrontWallTypeProc() && !checkIceSlipFall()) {
        if (mDemo.getDemoMode() == daPy_demo_c::DEMO_N_WALK_e) {
            // Fakematch? Regalloc doesn't match unless all three of these vars are given temps.
            f32 vel = mVelocity;
            f32 temp1 = mMaxNormalSpeed;
            f32 temp2 = m_HIO->mMove.m.field_0x2C;
            if (vel > temp1 * temp2) {
                vel = temp1 * temp2;
                mVelocity = vel;
            }
        }
        setBlendMoveAnime(-1.0f);
    }
    return true;
}

/* 801136D4-80113738       .text procAtnMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnMove_init() {
    if (mCurProc == daPyProc_ATN_MOVE_e) {
        return false;
    }
    commonProcInit(daPyProc_ATN_MOVE_e);
    setBlendAtnMoveAnime(m_HIO->mBasic.m.field_0xC);
    m34D0 = 0x14;
    return true;
}

/* 80113738-801137B4       .text procAtnMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnMove() {
    setSpeedAndAngleAtn();
    if (!checkNextMode(0) && (mDirection != DIR_FORWARD || !changeFrontWallTypeProc()) && !checkIceSlipFall()) {
        setBlendAtnMoveAnime(-1.0f);
    }
    return true;
}

/* 801137B4-8011388C       .text procAtnActorWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorWait_init() {
    s16 sVar2;

    if (mCurProc == daPyProc_ATN_ACTOR_WAIT_e) {
        return false;
    }
    commonProcInit(daPyProc_ATN_ACTOR_WAIT_e);
    if (mpAttnActorLockOn != NULL) {
        sVar2 = fopAcM_searchActorAngleY(this, mpAttnActorLockOn);
    } else {
        sVar2 = 0;
    }
    if (mDirection == DIR_LEFT || (mDirection != DIR_RIGHT && sVar2 - shape_angle.y >= 0)) {
        mDirection = DIR_LEFT;
    } else {
        mDirection = DIR_RIGHT;
    }
    if (checkAtnWaitAnime()) {
        setBlendAtnMoveAnime(m_HIO->mBasic.m.field_0xC);
    } else {
        setBlendMoveAnime(m_HIO->mBasic.m.field_0xC);
    }
    return true;
}

/* 8011388C-801138FC       .text procAtnActorWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorWait() {
    setSpeedAndAngleAtnActor();
    if (!checkNextMode(0)) {
        if (checkAtnWaitAnime()) {
            setBlendAtnMoveAnime(-1.0f);
        } else {
            setBlendMoveAnime(-1.0f);
        }
    }
    return true;
}

/* 801138FC-80113960       .text procAtnActorMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorMove_init() {
    if (mCurProc == daPyProc_ATN_ACTOR_MOVE_e) {
        return false;
    }
    commonProcInit(daPyProc_ATN_ACTOR_MOVE_e);
    setBlendAtnMoveAnime(m_HIO->mBasic.m.field_0xC);
    m34D0 = 0x14;
    return true;
}

/* 80113960-801139C0       .text procAtnActorMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorMove() {
    setSpeedAndAngleAtnActor();
    if (!checkNextMode(0) && !checkIceSlipFall()) {
        setBlendAtnMoveAnime(-1.0f);
    }
    return true;
}

/* 801139C0-80113AC4       .text procSideStep_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSideStep_init(int param_1) {
    daPy_ANM dVar1;

    commonProcInit(daPyProc_SIDE_STEP_e);
    mDirection = param_1;
    if (param_1 == DIR_LEFT) {
        dVar1 = ANM_ATNJL;
        current.angle.y = shape_angle.y + 0x4000;
    } else {
        dVar1 = ANM_ATNJR;
        current.angle.y = shape_angle.y + -0x4000;
    }
    setSingleMoveAnime(dVar1, m_HIO->mSideStep.m.field_0xC, m_HIO->mSideStep.m.field_0x10,
                       m_HIO->mSideStep.m.field_0x4, m_HIO->mSideStep.m.field_0x14);
    mVelocity = cM_scos(m_HIO->mSideStep.m.field_0x2) * m_HIO->mSideStep.m.field_0x8;
    speed.y = cM_ssin(m_HIO->mSideStep.m.field_0x2) * m_HIO->mSideStep.m.field_0x8;
    gravity = m_HIO->mSideStep.m.field_0x18;
    mProcVar0.m3570 = 0;
    voiceStart(5);
    return true;
}

/* 80113AC4-80113BDC       .text procSideStep__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStep() {
    if (m_HIO->mSideStep.m.field_0x0 != 0) {
        if (mpAttnActorLockOn != NULL) {
            s16 sVar2 = fopAcM_searchActorAngleY(this, mpAttnActorLockOn);
            cLib_addCalcAngleS(&shape_angle.y, sVar2, 5, 0x5e8, 0x13c);
        }
        if (mDirection == DIR_LEFT) {
            current.angle.y = shape_angle.y + 0x4000;
        } else {
            current.angle.y = shape_angle.y + -0x4000;
        }
    }
    checkNextActionItemFly();
    if (mAcch.ChkGroundHit()) {
        procSideStepLand_init();
    } else {
        if (checkJumpCutFromButton()) {
            return true;
        }
        if (checkFanGlideProc(0)) {
            return true;
        }
        if (current.pos.y < m3688.y - m_HIO->mSideStep.m.field_0x30) {
            procFall_init(2, m_HIO->mSideStep.m.field_0x2C);
        }
    }
    checkItemChangeFromButton();
    return true;
}

/* 80113BDC-80113CBC       .text procSideStepLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStepLand_init() {
    daPy_ANM dVar2;

    commonProcInit(daPyProc_SIDE_STEP_LAND_e);
    mVelocity = 0.0f;
    if (mDirection == DIR_LEFT) {
        dVar2 = ANM_ATNJLLAND;
    } else {
        dVar2 = ANM_ATNJRLAND;
    }
    setSingleMoveAnime(dVar2, m_HIO->mSideStep.m.field_0x1C,
                       m_HIO->mSideStep.m.field_0x20, m_HIO->mSideStep.m.field_0x6,
                       m_HIO->mSideStep.m.field_0x24);
    m34BE = 3;
    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
    current.angle.y += 0x8000;
    if (checkHeavyStateOn()) {
        dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    }
    return true;
}

/* 80113CBC-80113D30       .text procSideStepLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStepLand() {
    resetFootEffect();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mSideStep.m.field_0x28) {
            checkNextMode(1);
        }
    }
    return true;
}

/* 80113D30-80113DBC       .text procCrouchDefense_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefense_init() {
    commonProcInit(daPyProc_CROUCH_DEFENSE_e);
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(ANM_DIFENCE, m_HIO->mCrouch.m.field_0x10, 0.0f, -1,
                       m_HIO->mCrouch.m.field_0x14);
    current.angle.y = shape_angle.y;
    m34D4 = 0;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK80000_e);
    return true;
}

/* 80113DBC-80114014       .text procCrouchDefense__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefense() {
    dComIfGp_setRStatus(dActStts_DEFEND_e);
    if (dCam_getBody()->ChangeModeOK(4) && current.pos.y >= m35D0) {
        onResetFlg0(daPyRFlg0_SUBJECT_ACCEPT);
        if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x1000) && !dComIfGp_event_runCheck()) {
            return procSubjectivity_init(1);
        }
    }
    cLib_addCalc(&mVelocity, 0.0f, m_HIO->mMove.m.field_0x24, m_HIO->mMove.m.field_0x1C,
                 m_HIO->mMove.m.field_0x20);
    if (checkAttentionLock() || !spActionButton()) {
        current.angle.y = shape_angle.y;
        mDirection = DIR_RIGHT;
        checkNextMode(0);
    } else {
        s16 uVar2 = m34E8 - shape_angle.y;
        f32 fVar1 = mStickDistance * cM_scos(uVar2);
        s16 sVar5;
        if (fVar1 >= 0.0f) {
            sVar5 = m_HIO->mCrouch.m.field_0x2 * fVar1;
        } else {
            sVar5 = m_HIO->mCrouch.m.field_0x0 * fVar1;
        }
        cLib_addCalcAngleS(&mBodyAngle.x, sVar5, 4, 0xc00, 0x180);
        cLib_addCalcAngleS(&mBodyAngle.y,
                           m_HIO->mCrouch.m.field_0x4 * mStickDistance * cM_ssin(uVar2), 4,
                           0xc00, 0x180);
    }
    return true;
}

/* 80114014-801142F4       .text procCrouchDefenseSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefenseSlip_init() {
    commonProcInit(daPyProc_CROUCH_DEFENSE_SLIP_e);
    cXyz* damage_vec = getDamageVec(&mCyl);
    current.angle.y = cM_atan2s(damage_vec->x, damage_vec->z);
    dCcD_GObjInf* pfVar3 = mCyl.GetTgHitGObj();
    f32 dVar5;
    if (
        pfVar3 != NULL &&
        (
            pfVar3->GetAtSpl() == dCcG_At_Spl_UNK5 ||
            pfVar3->GetAtSpl() == dCcG_At_Spl_UNK6 ||
            pfVar3->GetAtSpl() == dCcG_At_Spl_UNK7
        )
    ) {
        setSingleMoveAnime(ANM_DIFENCEA, m_HIO->mNockback.m.field_0x8,
                           m_HIO->mNockback.m.field_0xC, m_HIO->mNockback.m.field_0x0,
                           m_HIO->mNockback.m.field_0x10);
        dVar5 = damage_vec->absXZ();
        mVelocity =
            (m_HIO->mNockback.m.field_0x18 * dVar5) + m_HIO->mNockback.m.field_0x14;
        m34D0 = m_HIO->mNockback.m.field_0x2;
        m35A0 = m_HIO->mNockback.m.field_0x1C;
        m35A4 = m_HIO->mNockback.m.field_0x20;
        m35A8 = m_HIO->mNockback.m.field_0x24;
        m35AC = m_HIO->mNockback.m.field_0x28;
        dVar5 = cM_rnd();
        mProcVar0.m3570 = (dVar5 < 0.2f) ? 1 : 0;
    } else {
        setSingleMoveAnime(ANM_DIFENCEA, m_HIO->mGuard.m.field_0x4,
                           m_HIO->mGuard.m.field_0x8, m_HIO->mGuard.m.field_0x0,
                           m_HIO->mGuard.m.field_0xC);
        dVar5 = damage_vec->absXZ();
        mVelocity = (m_HIO->mGuard.m.field_0x14 * dVar5) + m_HIO->mGuard.m.field_0x10;
        m34D0 = m_HIO->mGuard.m.field_0x2;
        m35A0 = m_HIO->mGuard.m.field_0x18;
        m35A4 = m_HIO->mGuard.m.field_0x1C;
        m35A8 = m_HIO->mGuard.m.field_0x20;
        m35AC = m_HIO->mGuard.m.field_0x24;
        mProcVar0.m3570 = 0;
    }
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_ATNGAHAMA));
        m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    } else {
        m35E8 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    }
    m34BE = 3;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK80000_e);
    return true;
}

/* 801142F4-801143D4       .text procCrouchDefenseSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefenseSlip() {
    dComIfGp_setRStatus(dActStts_DEFEND_e);
    if (m34D0 > 0) {
        m34D0--;
    }
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    } else {
        m35E8 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    }
    f32 dVar2 = cLib_addCalc(&mVelocity, 0.0f, m35A0, m35A4, m35A8);
    if (dVar2 <= 0.001f) {
        if (mProcVar0.m3570 != 0) {
            return procNockBackEnd_init();
        }
        if (m34D0 == 0) {
            return procCrouchDefense_init();
        }
    } else {
        if (mVelocity < m35AC) {
            resetFootEffect();
        }
    }
    return true;
}

/* 801143D4-80114440       .text procCrouch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouch_init() {
    commonProcInit(daPyProc_CROUCH_e);
    setSingleMoveAnime(ANM_CROUCH, m_HIO->mCrouch.m.field_0x18, 0.0f, -1,
                       m_HIO->mCrouch.m.field_0x1C);
    deleteEquipItem(FALSE);
    current.angle.y = shape_angle.y;
    return true;
}

/* 80114440-8011476C       .text procCrouch__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouch() {
    cXyz acStack_20;
    cXyz cStack_2c;
    cXyz cStack_38;
    cXyz local_5c;
    cXyz local_68;

    dComIfGp_setRStatus(dActStts_CROUCH_e);
    if (dCam_getBody()->ChangeModeOK(4) && current.pos.y >= m35D0) {
        onResetFlg0(daPyRFlg0_SUBJECT_ACCEPT);
        if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x1000) && !dComIfGp_event_runCheck()) {
            return procSubjectivity_init(1);
        }
    }
    cLib_addCalc(&mVelocity, 0.0f, m_HIO->mMove.m.field_0x24, m_HIO->mMove.m.field_0x1C,
                 m_HIO->mMove.m.field_0x20);
    if (!spActionButton() ||
        (checkAttentionLock() && dComIfGs_getSelectEquip(1) != dItem_NONE_e && checkGuardAccept()))
    {
        checkNextMode(0);
    } else {
        if ((m_old_fdata->getOldFrameRate() < 0.01f && mStickDistance > 0.05f) &&
            !(m35D0 > current.pos.y + 15.0f))
        {
            mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
            mDoMtx_stack_c::ZXYrotM(m34E2, shape_angle.y, 0);
            mDoMtx_stack_c::multVec(&l_crawl_start_front_offset, &acStack_20);
            mDoMtx_stack_c::multVec(&l_crawl_top_offset, &cStack_2c);
            if (getCrawlMoveVec(&cStack_2c, &acStack_20, &cStack_38)) {
                local_5c = current.pos - cStack_38;
                local_5c.y += 5.0f;
                mGndChk.SetPos(&local_5c);
                local_5c.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
                local_68 = current.pos - local_5c;
                if (cLib_distanceAngleS(cM_atan2s(-local_68.y, local_68.absXZ()), m34E2) > 0x100) {
                    return true;
                }
            }
            procCrawlStart_init();
        }
    }
    return true;
}

/* 8011476C-80114804       .text procWaitTurn_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn_init() {
    if (mCurProc == daPyProc_WAIT_TURN_e) {
        return false;
    }
    commonProcInit(daPyProc_WAIT_TURN_e);
    setSingleMoveAnime(ANM_ROT, m_HIO->mBasic.m.field_0x4, 0.0f, -1,
                       m_HIO->mBasic.m.field_0xC);
    if (dComIfGp_event_runCheck()) {
        mVelocity = 0.0f;
    }
    m34D4 = m34E8;
    current.angle.y = shape_angle.y;
    return true;
}

/* 80114804-80114908       .text procWaitTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn() {
    cLib_addCalc(&mVelocity, 0.0f, m_HIO->mMove.m.field_0x24, m_HIO->mMove.m.field_0x1C,
                 m_HIO->mMove.m.field_0x20);
    if (changeSlideProc()) {
        return true;
    }
    s16 sVar1 = cLib_addCalcAngleS(&shape_angle.y, m34D4, m_HIO->mTurn.m.field_0x4,
                                   m_HIO->mTurn.m.field_0x0, m_HIO->mTurn.m.field_0x2);
    current.angle.y = shape_angle.y;
    if (checkNextActionFromButton()) {
        return true;
    }
    if (sVar1 == 0) {
        if (dComIfGp_event_runCheck()) {
            if (mDemo.getDemoMode() == daPy_demo_c::DEMO_WAIT_TURN_e) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
            } else {
                checkNextMode(0);
            }
        } else {
            checkNextMode(0);
        }
    }
    return true;
}

/* 80114908-801149EC       .text procMoveTurn_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procMoveTurn_init(int param_1) {
    if (mCurProc == daPyProc_MOVE_TURN_e) {
        return false;
    }
    commonProcInit(daPyProc_MOVE_TURN_e);
    setBlendMoveAnime(m_HIO->mBasic.m.field_0xC);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800_e);
    if (param_1 != 0) {
        m34D4 = (m_HIO->mMove.m.field_0x0 * 4) + 0x4A56;
        m34D6 = m_HIO->mMove.m.field_0x0 * 2;
        m34D0 = 2;
        current.angle.y = m34E8;
        mVelocity *= 0.5f;
    } else {
        m34D4 = m_HIO->mMove.m.field_0x0 * 2;
        m34D6 = m_HIO->mMove.m.field_0x0;
        m34D0 = 3;
    }
    return true;
}

/* 801149EC-80114A60       .text procMoveTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procMoveTurn() {
    setSpeedAndAngleNormal(m_HIO->mMove.m.field_0x0);
    cLib_addCalcAngleS(&shape_angle.y, current.angle.y, m34D0, m34D4, m34D6);
    if (!checkNextMode(0)) {
        setBlendMoveAnime(-1.0f);
    }
    return true;
}

/* 80114A60-80114B28       .text procSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlip_init() {
    commonProcInit(daPyProc_SLIP_e);
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(ANM_SLIP, m_HIO->mSlip.m.field_0xC, 0.0f, -1,
                       m_HIO->mSlip.m.field_0x1C);
    mVelocity = speedF * m_HIO->mSlip.m.field_0x8;
    if (m_HIO->mSlip.m.field_0x0 == 1) {
        mVelocity = mMaxNormalSpeed;
    } else if (m_HIO->mSlip.m.field_0x0 == 2 && mVelocity > mMaxNormalSpeed) {
        mVelocity = mMaxNormalSpeed;
    }
    m34BE = 2;
    seStartMapInfo(JA_SE_LK_RUN_SLIP);
    return true;
}

/* 80114B28-80114D2C       .text procSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlip() {
    f32 dVar5 = cLib_addCalc(&mVelocity, 0.0f, m_HIO->mSlip.m.field_0x18,
                             m_HIO->mSlip.m.field_0x10, m_HIO->mSlip.m.field_0x14);
    if (dVar5 <= 0.001f) {
        if (mStickDistance > 0.05f) {
            current.angle.y = shape_angle.y + 0x8000;
            shape_angle.y = shape_angle.y + 0x100;
            mVelocity = mMaxNormalSpeed * 0.5f;
            procMoveTurn_init(0);
        } else {
            checkNextMode(0);
        }
    } else if (mAcch.ChkWallHit()) {
        mVelocity = 0.0f;
        checkNextMode(0);
        return true;
    } else {
        if (mVelocity < m_HIO->mSlip.m.field_0x20) {
            resetFootEffect();
        }
        cXyz local_1c;
        cXyz local_28;
        local_1c = current.pos;
        local_1c.y += 2.5f;
        local_28.x = local_1c.x + 50.0f * cM_ssin(current.angle.y);
        local_28.y = local_1c.y;
        local_28.z = local_1c.z + 50.0f * cM_scos(current.angle.y);
        mLinkLinChk.Set(&local_1c, &local_28, this);
        if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            cM3dGPla* iVar3 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
            if (cBgW_CheckBWall(iVar3->GetNP()->y)) {
                mVelocity = 0.0f;
                checkNextMode(0);
            }
        }
    }
    return true;
}

/* 80114D2C-80114DE4       .text procSlideFront_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procSlideFront_init(s16 param_1) {
    if (mCurProc == daPyProc_SLIDE_FRONT_e || mCurProc == daPyProc_SLIDE_BACK_e) {
        return false;
    }
    commonProcInit(daPyProc_SLIDE_FRONT_e);
    m3526 = 8;
    current.angle.y = param_1;
    setSingleMoveAnime(ANM_SLIDEF, m_HIO->mSlide.m.field_0xC, m_HIO->mSlide.m.field_0x10,
                       m_HIO->mSlide.m.field_0x0, m_HIO->mSlide.m.field_0x14);
    mMaxNormalSpeed = m_HIO->mSlide.m.field_0x44;
    m34BE = 4;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK100_e);
    return true;
}

/* 80114DE4-80114EE8       .text procSlideFront__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFront() {
    cM3dGPla* pfVar2 = getSlidePolygon();
    if (pfVar2 != NULL) {
        s16 iVar3 = cM_atan2s(pfVar2->GetNP()->x, pfVar2->GetNP()->z);
        cLib_addCalcAngleS(&current.angle.y, iVar3, 4, 0x1000, 0x400);
        cLib_addCalcAngleS(&shape_angle.y, current.angle.y, 4, 0x1000, 0x400);
        mVelocity += (1.0f + 0.5f * (1.0f - pfVar2->GetNP()->y)) * m_HIO->mSlide.m.field_0x48 *
                     cM_scos(current.angle.y - iVar3);
        if (mVelocity > mMaxNormalSpeed) {
            mVelocity = mMaxNormalSpeed;
        }
        seStartMapInfo(JA_SE_LK_SLIP_SUS);
    } else {
        procSlideFrontLand_init();
    }
    return true;
}

/* 80114EE8-80114FA0       .text procSlideBack_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procSlideBack_init(s16 param_1) {
    if (mCurProc == daPyProc_SLIDE_BACK_e || mCurProc == daPyProc_SLIDE_FRONT_e) {
        return false;
    }
    commonProcInit(daPyProc_SLIDE_BACK_e);
    m3526 = 8;
    current.angle.y = param_1;
    setSingleMoveAnime(ANM_SLIDEB, m_HIO->mSlide.m.field_0x18, m_HIO->mSlide.m.field_0x1C,
                       m_HIO->mSlide.m.field_0x2, m_HIO->mSlide.m.field_0x20);
    mMaxNormalSpeed = m_HIO->mSlide.m.field_0x44;
    m34BE = 3;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK200_e);
    return true;
}

/* 80114FA0-801150B0       .text procSlideBack__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBack() {
    cM3dGPla* pfVar2 = getSlidePolygon();
    if (pfVar2 != NULL) {
        s16 iVar3 = cM_atan2s(pfVar2->GetNP()->x, pfVar2->GetNP()->z);
        cLib_addCalcAngleS(&current.angle.y, iVar3, 4, 0x1000, 0x400);
        cLib_addCalcAngleS(&shape_angle.y, current.angle.y + 0x8000, 4, 0x1000, 0x400);
        mVelocity += (1.0f + 0.5f * (1.0f - pfVar2->GetNP()->y)) * m_HIO->mSlide.m.field_0x48 *
                     cM_scos(current.angle.y - iVar3);
        if (mVelocity > mMaxNormalSpeed) {
            mVelocity = mMaxNormalSpeed;
        }
        seStartMapInfo(JA_SE_LK_SLIP_SUS);
    } else {
        procSlideBackLand_init();
    }
    return true;
}

/* 801150B0-80115118       .text procSlideFrontLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFrontLand_init() {
    commonProcInit(daPyProc_SLIDE_FRONT_LAND_e);
    setSingleMoveAnime(ANM_SLIDEFLAND, m_HIO->mSlide.m.field_0x24,
                       m_HIO->mSlide.m.field_0x28, m_HIO->mSlide.m.field_0x4,
                       m_HIO->mSlide.m.field_0x30);
    mVelocity *= 0.5f;
    return true;
}

/* 80115118-801151C8       .text procSlideFrontLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFrontLand() {
    cLib_addCalc(&mVelocity, 0.0f, 0.5f, 5.0f, 1.0f);
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        current.angle.y = shape_angle.y;
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mSlide.m.field_0x2C) {
            s16 sVar1 = current.angle.y;
            current.angle.y = shape_angle.y;
            if (!checkNextMode(1)) {
                current.angle.y = sVar1;
            }
        }
    }
    return true;
}

/* 801151C8-80115220       .text procSlideBackLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBackLand_init() {
    commonProcInit(daPyProc_SLIDE_BACK_LAND_e);
    setSingleMoveAnime(ANM_SLIDEBLAND, m_HIO->mSlide.m.field_0x34,
                       m_HIO->mSlide.m.field_0x38, m_HIO->mSlide.m.field_0x6,
                       m_HIO->mSlide.m.field_0x40);
    return true;
}

/* 80115220-801152D0       .text procSlideBackLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBackLand() {
    cLib_addCalc(&mVelocity, 0.0f, 0.5f, 5.0f, 1.0f);
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        current.angle.y = shape_angle.y;
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mSlide.m.field_0x3C) {
            s16 sVar1 = current.angle.y;
            current.angle.y = shape_angle.y;
            if (!checkNextMode(1)) {
                current.angle.y = sVar1;
            }
        }
    }
    return true;
}

/* 801152D0-80115478       .text procFrontRoll_init__9daPy_lk_cFf */
BOOL daPy_lk_c::procFrontRoll_init(f32 param_1) {
    commonProcInit(daPyProc_FRONT_ROLL_e);
    setSingleMoveAnime(ANM_ROLLF, m_HIO->mRoll.m.field_0x8, param_1,
                       m_HIO->mRoll.m.field_0x0, m_HIO->mRoll.m.field_0x14);
    mVelocity = speedF * m_HIO->mRoll.m.field_0x18 + m_HIO->mRoll.m.field_0x1C;
    if (checkHeavyStateOn()) {
        mVelocity *= m_HIO->mMove.m.field_0x80;
    }
    if (mVelocity < m_HIO->mRoll.m.field_0x20) {
        mVelocity = m_HIO->mRoll.m.field_0x20;
    } else {
        param_1 = m_HIO->mRoll.m.field_0x1C +
                  m_HIO->mMove.m.field_0x18 * m_HIO->mRoll.m.field_0x18;
        if (checkHeavyStateOn()) {
            param_1 *= m_HIO->mMove.m.field_0x80;
        }
        if (mVelocity > param_1) {
            mVelocity = param_1;
        }
    }
    current.angle.y = shape_angle.y;
    if (mAcchCir[0].ChkWallHit() &&
        cLib_distanceAngleS(current.angle.y + 0x8000, mAcchCir[0].GetWallAngleY()) <= m_HIO->mRoll.m.field_0x4)
    {
        mProcVar0.m3570 = 0;
    } else {
        mProcVar0.m3570 = 1;
    }
    offNoResetFlg0(daPyFlg0_UNK8);
    m34D4 = 0;
    voiceStart(7);
    return true;
}

/* 80115478-80115628       .text procFrontRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRoll() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > 6.0f) {
        m34BE = 4;
        endFlameDamageEmitter();
    }
    if (getSlidePolygon() != NULL) {
        cLib_addCalc(&mVelocity, 0.0f, 0.5f, 2.5f, 0.1f);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (mStickDistance <= 0.05f) {
            mVelocity -= m_HIO->mRoll.m.field_0x20;
        }
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mRoll.m.field_0x10) {
            checkNextMode(1);
        } else {
            if (speedF >= m_HIO->mRoll.m.field_0x3C &&
                !checkNoResetFlg1(daPyFlg1_UNK100000))
            {
                if (checkNoResetFlg0(daPyFlg0_UNK8) ||
                    (mProcVar0.m3570 != 0 && mAcch.ChkWallHit() && mAcchCir[0].ChkWallHit() &&
                     cLib_distanceAngleS(current.angle.y + 0x8000, mAcchCir[0].GetWallAngleY()) <=
                         m_HIO->mRoll.m.field_0x4 &&
                     mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= m_HIO->mRoll.m.field_0x34 &&
                     mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() <= m_HIO->mRoll.m.field_0x38))
                {
                    if (!checkNoResetFlg0(daPyFlg0_UNK8)) {
                        m3620 = dComIfG_Bgsp()->GetMtrlSndId(mAcchCir[0]);
                    }
                    procFrontRollCrash_init();
                }
            }
        }
    }
    return true;
}

/* 80115628-801157D8       .text procFrontRollCrash_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRollCrash_init() {
    commonProcInit(daPyProc_FRONT_ROLL_CRASH_e);
    setSingleMoveAnime(ANM_ROLLFMIS, 0.0f, m_HIO->mRoll.m.field_0x28,
                       m_HIO->mRoll.m.field_0x2, m_HIO->mRoll.m.field_0x2C);
    mVelocity = speedF * m_HIO->mRoll.m.field_0x40;
    speed.y = m_HIO->mRoll.m.field_0x44;
    offNoResetFlg0(daPyFlg0_UNK8);
    current.angle.y += 0x8000;
    dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    voiceStart(8);
    mDoAud_seStart(JA_SE_LK_BODYATTACK, &current.pos, m3620, mReverb);
    onResetFlg0(daPyRFlg0_FRONT_ROLL_CRASH);
    dKy_Sound_set(current.pos, 100, fopAcM_GetID(this), 5);
    if (mAcch.ChkWallHit() && mAcchCir[0].ChkWallHit()) {
        fopAc_ac_c* actor = dComIfG_Bgsp()->GetActorPointer(mAcchCir[0]);
        if (actor != 0 && fopAcM_GetName(actor) == PROC_Obj_Movebox) {
            daObjMovebox::Act_c* movebox = (daObjMovebox::Act_c*)actor;
            movebox->set_rollCrash();
        }
    }
    return true;
}

/* 801157D8-801158AC       .text procFrontRollCrash__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRollCrash() {
    if (!checkModeFlg(ModeFlg_MIDAIR)) {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            checkNextMode(0);
        } else {
            if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mRoll.m.field_0x30) {
                checkNextMode(1);
            }
        }
    }
    if (mAcch.ChkGroundHit() && checkModeFlg(ModeFlg_MIDAIR)) {
        mVelocity = 0.0f;
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(m_HIO->mRoll.m.field_0x24);
        voiceStart(9);
        offModeFlg(ModeFlg_MIDAIR);
        onModeFlg(ModeFlg_00008000);
    }
    return true;
}

/* 801158AC-8011590C       .text procNockBackEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd_init() {
    commonProcInit(daPyProc_NOCK_BACK_END_e);
    setSingleMoveAnime(ANM_ROLLFMIS, m_HIO->mNockback.m.field_0x2C,
                       m_HIO->mNockback.m.field_0x30, m_HIO->mNockback.m.field_0x4,
                       m_HIO->mNockback.m.field_0x34);
    mVelocity = 0.0f;
    return true;
}

/* 8011590C-80115968       .text procNockBackEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mNockback.m.field_0x38) {
            checkNextMode(1);
        }
    }
    return true;
}

/* 80115968-80115A18       .text procSideRoll_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideRoll_init() {
    daPy_ANM dVar2;

    commonProcInit(daPyProc_SIDE_ROLL_e);
    if ((s16)(current.angle.y - shape_angle.y) > 0) {
        dVar2 = ANM_MROLLL;
    } else {
        dVar2 = ANM_MROLLR;
    }
    setSingleMoveAnime(dVar2, m_HIO->mFall.m.field_0x3C, m_HIO->mFall.m.field_0x40,
                       m_HIO->mFall.m.field_0x8, m_HIO->mFall.m.field_0x48);
    mVelocity = m_HIO->mFall.m.field_0x4C;
    if (checkHeavyStateOn()) {
        mVelocity *= m_HIO->mMove.m.field_0x80;
    }
    m34BE = 4;
    return true;
}

/* 80115A18-80115B08       .text procSideRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideRoll() {
    s16 sVar1;
    f32 dVar3;
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (frameCtrl.getRate() < 0.01f) {
        current.angle.y = shape_angle.y;
        if (mStickDistance <= 0.05f) {
            mVelocity = 0.0f;
        }
        checkNextMode(0);
    } else {
        if (frameCtrl.checkPass(10.0f)) {
            endFlameDamageEmitter();
        } else {
            if (frameCtrl.getFrame() > m_HIO->mFall.m.field_0x44) {
                sVar1 = current.angle.y;
                dVar3 = mVelocity;
                current.angle.y = shape_angle.y;
                if (!checkNextMode(1)) {
                    current.angle.y = sVar1;
                    mVelocity = dVar3;
                }
            }
        }
    }
    return true;
}

/* 80115B08-80115BFC       .text procBackJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJump_init() {
    f32 fVar1;

    if (mCurProc == daPyProc_BACK_JUMP_e) {
        return false;
    }
    commonProcInit(daPyProc_BACK_JUMP_e);
    if (checkHeavyStateOn()) {
        mVelocity = 0.5f * m_HIO->mBackJump.m.field_0x10;
        fVar1 = 1.5f * m_HIO->mBackJump.m.field_0x4;
    } else {
        mVelocity = m_HIO->mBackJump.m.field_0x10;
        fVar1 = m_HIO->mBackJump.m.field_0x4;
    }
    setSingleMoveAnime(ANM_ROLLB, fVar1, m_HIO->mBackJump.m.field_0x8,
                       m_HIO->mBackJump.m.field_0x0, m_HIO->mBackJump.m.field_0xC);
    speed.y = m_HIO->mBackJump.m.field_0x14;
    gravity = m_HIO->mBackJump.m.field_0x18;
    current.angle.y = shape_angle.y + 0x8000;
    voiceStart(7);
    return true;
}

/* 80115BFC-80115CA0       .text procBackJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJump() {
    if (mAcch.ChkGroundHit() && mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        procBackJumpLand_init();
    } else {
        if (checkFanGlideProc(0)) {
            return true;
        }
        if (current.pos.y < m3688.y - m_HIO->mBackJump.m.field_0x1C) {
            procFall_init(2, m_HIO->mBackJump.m.field_0x20);
        }
    }
    checkItemChangeFromButton();
    return true;
}

/* 80115CA0-80115DA8       .text procBackJumpLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJumpLand_init() {
    commonProcInit(daPyProc_BACK_JUMP_LAND_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_ROLLBLAND, m_HIO->mBackJump.m.field_0x24,
                       m_HIO->mBackJump.m.field_0x28, m_HIO->mBackJump.m.field_0x2,
                       m_HIO->mBackJump.m.field_0x2C);
    m34BE = 3;
    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
    current.angle.y = shape_angle.y;
    if (checkHeavyStateOn()) {
        dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    }
    if ((mEquipItem == daPyItem_SWORD_e || mEquipItem == daPyItem_BOKO_e) &&
        !daPy_dmEcallBack_c::checkCurse() && checkNoUpperAnime())
    {
        mProcVar0.m3570 = 1;
    } else {
        mProcVar0.m3570 = 0;
    }
    return true;
}

/* 80115DA8-80115E88       .text procBackJumpLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJumpLand() {
    resetFootEffect();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (dComIfGp_event_runCheck()) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else {
            checkNextMode(0);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mBackJump.m.field_0x30) {
        checkNextMode(1);
    } else {
        if (mProcVar0.m3570 != 0) {
            mProcVar0.m3570 = 0;
            if (abs(m3578) > 0xf800 && mEquipItem == daPyItem_SWORD_e) {
                procCutTurn_init(1);
            }
        }
    }
    return true;
}

/* 80115E88-80115EA4       .text checkAutoJumpFlying__9daPy_lk_cCFv */
int daPy_lk_c::checkAutoJumpFlying() const {
    if (mCurProc != daPyProc_AUTO_JUMP_e) {
        return -1;
    }
    return m34D0;
}

/* 80115EA4-8011602C       .text procAutoJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAutoJump_init() {
    commonProcInit(daPyProc_AUTO_JUMP_e);
    m3688 = current.pos;
    m35F0 = m3688.y;
    m35F4 = m3688.y;
    setSingleMoveAnime(ANM_JMPST, m_HIO->mAutoJump.m.field_0x20,
                       m_HIO->mAutoJump.m.field_0x2C, m_HIO->mAutoJump.m.field_0x2,
                       m_HIO->mAutoJump.m.field_0x30);
    if (speedF > m_HIO->mMove.m.field_0x18) {
        speedF = m_HIO->mMove.m.field_0x18;
    } else if (speedF < m_HIO->mAutoJump.m.field_0x14) {
        speedF = m_HIO->mAutoJump.m.field_0x14;
    }
    mVelocity =
        speedF * cM_scos(m_HIO->mAutoJump.m.field_0x6) * m_HIO->mAutoJump.m.field_0x18;
    speed.y =
        speedF * cM_ssin(m_HIO->mAutoJump.m.field_0x6) * m_HIO->mAutoJump.m.field_0x18;
    mProcVar0.m3570 = 0;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    current.angle.y = shape_angle.y;
    voiceStart(6);
    onNoResetFlg0(daPyFlg0_UNK20000);
    offNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
    m34D0 = -1;
    m34D2 = 3;
    return true;
}

/* 8011602C-801163D4       .text procAutoJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procAutoJump() {
    if (m34D0 == 0) {
        if (mStickDistance > 0.05f && getDirectionFromCurrentAngle() == DIR_BACKWARD) {
            cLib_chaseF(&mVelocity, 0.0f, (m_HIO->mAutoJump.m.field_0x3C * mStickDistance));
        } else if (mStickDistance <= 0.05f) {
            cLib_chaseF(&mVelocity, 0.0f, (0.1f * m_HIO->mAutoJump.m.field_0x3C));
        } else {
            cLib_chaseF(&mVelocity, m_HIO->mMove.m.field_0x18,
                        m_HIO->mAutoJump.m.field_0x1C);
        }
    } else {
        cLib_chaseF(&mVelocity, m_HIO->mMove.m.field_0x18, m_HIO->mAutoJump.m.field_0x1C);
    }
    checkNextActionItemFly();
    if (checkJumpFlower() || checkJumpRideShip()) {
        return true;
    }
    if (mAcch.ChkGroundHit()) {
        return changeLandProc(m_HIO->mAutoJump.m.field_0x24);
    }
    if (checkFanGlideProc(0)) {
        return true;
    }
    if (!checkGrabAnime() &&
        (changeFrontWallTypeProc() || changeRopeSwingProc() || checkJumpCutFromButton() || checkItemChangeFromButton()))
    {
        return true;
    }
    m34C2 = 1;
    if (m34D0 > 0) {
        m34D0--;
        dComIfGp_setDoStatus(dActStts_LET_GO_e);
        if (mAcch.ChkWallHit() || mCyl.ChkCoHit()) {
            m34D2--;
        }
        if (doTrigger() || m34D2 == 0) {
            if (doTrigger() && mActorKeepGrab.getActor() != NULL) {
                mActorKeepGrab.getActor()->speedF = speedF;
            }
            freeGrabItem();
            m34D0 = 0;
        }
        if (m34D0 == 0) {
            gravity = m_HIO->mAutoJump.m.field_0xC;
        }
        if (speed.y > 0.0f) {
            speed.y -= 0.5f;
            if (speed.y <= 0.0f) {
                speed.y = 0.0f;
            }
        }
    } else if (speed.y < -gravity && mProcVar0.m3570 != 2) {
        if (mActorKeepGrab.getActor() != NULL && fopAcM_GetName(mActorKeepGrab.getActor()) == PROC_NPC_MD &&
            dComIfGs_isEventBit(dSv_event_flag_c::UNK_1620))
        {
            speed.y = 5.0f;
            gravity = 0.0f;
            m34D0 = m_HIO->mAutoJump.m.field_0x8;
        }
        setSingleMoveAnime(ANM_JMPEDS, 0.0f, 0.0f, -1, m_HIO->mAutoJump.m.field_0x38);
        m34C2 = 2;
        mProcVar0.m3570 = 2;
        offModeFlg(ModeFlg_00000400);
        setTextureAnime(0x37, 0);
        resetSeAnime();
    } else if (m3688.y > current.pos.y && (m_tex_anm_heap.mIdx != mTexAnmIndexTable[daPyFace_TLAVADAM].mBtpIdx)) {
        setTextureAnime(0x37, 0);
    }
    setFallVoice();
    return true;
}

/* 801163D4-8011651C       .text procLand_init__9daPy_lk_cFfi */
BOOL daPy_lk_c::procLand_init(f32 param_1, int param_2) {
    commonProcInit(daPyProc_LAND_e);
    mVelocity = 0.0f;
    if (param_2 != 0) {
        setSingleMoveAnime(ANM_JMPEDS, param_1, m_HIO->mItem.mFan.m.field_0x54,
                           m_HIO->mItem.mFan.m.field_0x6, m_HIO->mItem.mFan.m.field_0x58);
    } else {
        setSingleMoveAnime(ANM_JMPEDS, param_1, m_HIO->mAutoJump.m.field_0x28,
                           m_HIO->mAutoJump.m.field_0x4, m_HIO->mAutoJump.m.field_0x34);
    }
    m34BE = 3;
    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
    if (current.angle.y != shape_angle.y) {
        if (cLib_distanceAngleS(current.angle.y, shape_angle.y) > 0x6000) {
            current.angle.y = shape_angle.y;
        } else {
            current.angle.y = current.angle.y + 0x8000;
        }
    }
    if (checkHeavyStateOn()) {
        dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    }
    return true;
}

/* 8011651C-801165B4       .text procLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procLand() {
    resetFootEffect();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (mDemo.getDemoMode() == daPy_demo_c::DEMO_SFALL_e) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else {
            checkNextMode(0);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mAutoJump.m.field_0x40) {
        checkNextMode(1);
    }
    return true;
}

/* 801165B4-80116768       .text procLandDamage_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procLandDamage_init(int param_1) {
    if (param_1 == 2) {
        if (!dComIfGp_event_runCheck()) {
            setDamagePoint(-2.0f);
        }
        dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    } else if (param_1 == 1) {
        if (!dComIfGp_event_runCheck()) {
            setDamagePoint(-1.0f);
        }
        dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    } else {
        dComIfGp_getVibration().StartShock(2, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    }
    commonProcInit(daPyProc_LAND_DAMAGE_e);
    mVelocity = 0.0f;
    if (param_1 == 0) {
        m34D0 = m_HIO->mFall.m.field_0xC;
        offModeFlg(ModeFlg_DAMAGE);
    } else {
        m34D0 = m_HIO->mFall.m.field_0x2;
        mDamageWaitTimer = m_HIO->mDam.m.field_0x0;
    }
    setSingleMoveAnime(ANM_LANDDAMA, m_HIO->mFall.m.field_0x1C, m_HIO->mFall.m.field_0x20,
                       m_HIO->mFall.m.field_0x4, m_HIO->mFall.m.field_0x24);
    mProcVar0.m3570 = 0;
    seStartOnlyReverb(JA_SE_LK_FALL_DAMAGE);
    voiceStart(13);
    m34BE = 5;
    return true;
}

/* 80116768-80116864       .text procLandDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLandDamage() {
    resetFootEffect();
    if (mProcVar0.m3570 != 0) {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            checkNextMode(0);
        } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mFall.m.field_0x30) {
            checkNextMode(1);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
        } else {
            f32 fVar1;
            if (checkModeFlg(ModeFlg_DAMAGE)) {
                fVar1 = m_HIO->mFall.m.field_0x28;
            } else {
                fVar1 = m_HIO->mFall.m.field_0x50;
            }
            setSingleMoveAnime(ANM_LANDDAMAST, fVar1, m_HIO->mFall.m.field_0x2C,
                               m_HIO->mFall.m.field_0x6, m_HIO->mFall.m.field_0x34);
            mProcVar0.m3570 = 1;
        }
    }
    return true;
}

/* 80116864-80116A38       .text procFall_init__9daPy_lk_cFif */
BOOL daPy_lk_c::procFall_init(int param_1, f32 param_2) {
    BOOL bVar1;
    BOOL bVar2;

    if (mDemo.getDemoMode() == daPy_demo_c::DEMO_PFALL_e) {
        mAcch.SetGrndNone();
        mAcch.OnLineCheckNone();
    }
    if (mCurProc == daPyProc_SHIP_GET_OFF_e) {
        bVar1 = false;
    } else {
        bVar1 = true;
    }
    if (mCurProc == daPyProc_FALL_e) {
        return false;
    }
    if (mCurProc == daPyProc_SLIDE_FRONT_e || mCurProc == daPyProc_SLIDE_BACK_e) {
        bVar2 = true;
    } else {
        bVar2 = false;
    }
    commonProcInit(daPyProc_FALL_e);
    if (param_1 == 1) {
        mVelocity = 0.0f;
        speed.y = 0.0f;
        current.angle.y = shape_angle.y;
    }
    if (param_1 == 2) {
        m34D6 = 1;
    } else {
        m34D6 = 0;
    }
    setSingleMoveAnime(ANM_JMPEDS, 0.0f, 0.0f, -1, param_2);
    setTextureAnime(0x37, 0);
    resetSeAnime();
    mProcVar0.m3570 = 0;
    if (current.angle.y == shape_angle.y && !checkGrabAnime()) {
        if (mVelocity > 1.0f) {
            m34D0 = 2;
        } else {
            m34D0 = 1;
        }
    } else {
        m34D0 = 0;
    }
    m34D2 = 8;
    if (cLib_distanceAngleS(current.angle.y, shape_angle.y) < 0x4800 && !bVar2) {
        m34D4 = 1;
    } else {
        m34D4 = 0;
    }
    offNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
    m3574 = bVar1;
    return true;
}

/* 80116A38-80116C14       .text procFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procFall() {
    if ((mProcVar0.m3570 == 0 && m3688.y > current.pos.y) &&
        (m_tex_anm_heap.mIdx != mTexAnmIndexTable[daPyFace_TLAVADAM].mBtpIdx))
    {
        setTextureAnime(0x37, 0);
        mProcVar0.m3570 = 1;
    }
    if (m34D6 != 0) {
        cLib_addCalc(&mVelocity, 0.0f, 0.2f, 1.0f, 0.1f);
    }
    checkNextActionItemFly();
    if (checkJumpFlower() || (m3574 != 0 && checkJumpRideShip())) {
        return true;
    }
    if (mAcch.ChkGroundHit()) {
        changeLandProc(m_HIO->mAutoJump.m.field_0x24);
    } else {
        if (checkFanGlideProc(0)) {
            return true;
        }
        setFallVoice();
        if (m34D0 == 1) {
            if ((int)m34D2 > 0) {
                m34D2--;
            }
            if (mStickDistance > 0.05f && getDirectionFromShapeAngle() == 0 && m34D2 == 0) {
                if (changeFrontWallTypeProc()) {
                    return true;
                }
            }
        } else if (m34D0 == 2) {
            if (changeFrontWallTypeProc() || changeRopeSwingProc()) {
                return true;
            }
        }
        if (m34D4 != 0 && checkJumpCutFromButton()) {
            return true;
        }
    }
    checkItemChangeFromButton();
    return true;
}

/* 80116C14-80116CC4       .text procSlowFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlowFall_init() {
    if (mCurProc == daPyProc_SLOW_FALL_e) {
        return true;
    }
    commonProcInit(daPyProc_SLOW_FALL_e);
    maxFallSpeed = -20.0f;
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_MSTEPOVER_JMPED, 0.0f, 0.0f, -1, m_HIO->mBasic.m.field_0xC);
    mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getEnd() - 0.001f);
    mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(
        mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    return true;
}

/* 80116CC4-80116D3C       .text procSlowFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlowFall() {
    if (current.pos.y - mAcch.GetGroundH() < 200.0f) {
        cLib_chaseF(&maxFallSpeed, -5.0f, 1.0f);
    }
    if (mAcch.ChkGroundHit()) {
        procLand_init(m_HIO->mItem.mFan.m.field_0x50, 1);
    }
    return true;
}

/* 80116D3C-80116EB4       .text procSmallJump_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSmallJump_init(int param_1) {
    commonProcInit(daPyProc_SMALL_JUMP_e);
    setSingleMoveAnime(ANM_JMPST, m_HIO->mSmallJump.m.field_0x4,
                       m_HIO->mSmallJump.m.field_0x8, m_HIO->mSmallJump.m.field_0x0,
                       m_HIO->mSmallJump.m.field_0xC);
    if (param_1 == 0) {
        mVelocity = m_HIO->mSmallJump.m.field_0x10;
        speed.y = std::sqrtf(
            -gravity * ((m3724.y - current.pos.y) + m_HIO->mSmallJump.m.field_0x14) * 2.0f);
        mProcVar0.m3570 = 2;
    } else {
        mVelocity = 2.0f * m_HIO->mSmallJump.m.field_0x10;
        speed.y = 20.0f;
        mProcVar0.m3570 = 0;
    }
    if (checkHeavyStateOn()) {
        gravity *= 0.44444445f;
    }
    voiceStart(5);
    return true;
}

/* 80116EB4-80116F54       .text procSmallJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procSmallJump() {
    if (mAcch.ChkGroundHit()) {
        changeLandProc(m_HIO->mAutoJump.m.field_0x24);
    } else if (checkFanGlideProc(0)) {
        return true;
    } else if (speed.y < -gravity) {
        procFall_init(mProcVar0.m3570, m_HIO->mSmallJump.m.field_0x18);
        setTextureAnime(0x37, 0);
    }
    return true;
}

/* 80116F54-80116FEC       .text procVerticalJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procVerticalJump_init() {
    commonProcInit(daPyProc_VERTICAL_JUMP_e);
    setSingleMoveAnime(ANM_VJMP, m_HIO->mWallCatch.m.field_0x3C, 0.0f,
                       m_HIO->mWallCatch.m.field_0x6, m_HIO->mWallCatch.m.field_0x40);
    m34D0 = 0;
    m34D4 = m352C + 0x8000;
    if (mFrontWallType == 9) {
        mProcVar0.m3570 = 1;
    } else {
        mProcVar0.m3570 = 0;
    }
    mVelocity = 0.0f;
    speed.y = 0.0f;
    return true;
}

/* 80116FEC-80117088       .text procVerticalJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procVerticalJump() {
    int iVar1;

    cLib_addCalcAngleS(&shape_angle.y, m34D4, 2, 0x1000, 0x400);
    current.angle.y = shape_angle.y;
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        shape_angle.y = m34D4;
        current.angle.y = shape_angle.y;
        if (mProcVar0.m3570 != 0) {
            iVar1 = procHangStart_init();
        } else {
            iVar1 = procHangWallCatch_init();
        }
        if (iVar1 == 0) {
            procWait_init();
        }
    }
    return true;
}

/* 80117088-801170F0       .text procGuardCrash__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardCrash() {
    cLib_addCalc(&mVelocity, 0.0f, 0.5f, 1.25f, 0.25f);
    if (m34D0 > 0) {
        m34D0--;
    } else {
        checkNextMode(0);
    }
    return true;
}

/* 801170F0-80117448       .text procDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procDamage_init() {
    cXyz* damage_vec = getDamageVec(&mCyl);
    f32 f31 = cM_ssin(shape_angle.y);
    f32 f30 = cM_scos(shape_angle.y);
    commonProcInit(daPyProc_DAMAGE_e);
    mDamageWaitTimer = m_HIO->mDam.m.field_0x0;
    cXyz local_54(damage_vec->z * -f31 + damage_vec->x * f30, damage_vec->y, damage_vec->z * f30 + damage_vec->x * f31);
    m34D4 = cM_atan2s(local_54.z, local_54.y);
    m34D6 = cM_atan2s(-local_54.x, std::sqrtf(local_54.y * local_54.y + local_54.z * local_54.z));
    if (m34D4 > m_HIO->mDam.mDamage.m.field_0x2) {
        m34D4 = m_HIO->mDam.mDamage.m.field_0x2;
    } else {
        if (m34D4 < -m_HIO->mDam.mDamage.m.field_0x2) {
            m34D4 = -m_HIO->mDam.mDamage.m.field_0x2;
        }
    }
    if (m34D6 > m_HIO->mDam.mDamage.m.field_0x2) {
        m34D6 = m_HIO->mDam.mDamage.m.field_0x2;
    } else {
        if (m34D6 < -m_HIO->mDam.mDamage.m.field_0x2) {
            m34D6 = -m_HIO->mDam.mDamage.m.field_0x2;
        }
    }
    int direction = getDirectionFromAngle(cM_atan2s(local_54.x, local_54.z));
    daPy_ANM dVar2;
    if (direction == DIR_BACKWARD) {
        dVar2 = ANM_DAMF;
    } else if (direction == DIR_LEFT) {
        dVar2 = ANM_DAMR;
    } else if (direction == DIR_RIGHT) {
        dVar2 = ANM_DAML;
    } else {
        dVar2 = ANM_DAMB;
    }
    setSingleMoveAnime(dVar2, m_HIO->mDam.mDamage.m.field_0x14, m_HIO->mDam.mDamage.m.field_0x18,
                       m_HIO->mDam.mDamage.m.field_0x0, m_HIO->mDam.mDamage.m.field_0x8);
    current.angle.y = cM_atan2s(damage_vec->x, damage_vec->z);
    if (dVar2 != ANM_DAMR) {
        m34BE = 2;
    }
    if (dVar2 != ANM_DAML) {
        m34BE = 1;
    }
    mVelocity =
        (m_HIO->mDam.mDamage.m.field_0x10 * damage_vec->absXZ()) + m_HIO->mDam.mDamage.m.field_0xC;
    voiceStart(2);
    seStartOnlyReverb(JA_SE_LK_DAMAGE_NORMAL);
    mProcVar0.mDamageAnm = dVar2;
    offNoResetFlg0(daPyFlg0_UNK2);
    dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    return true;
}

/* 80117448-801176FC       .text procDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procDamage() {
    f32 fVar1;
    f32 fVar2;
    s16 uVar4;
    f32 dVar5;
    f32 dVar6;

    dVar6 = (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - m_HIO->mDam.mDamage.m.field_0x28);
    cLib_addCalcAngleS(&m3566, 0, 4, 0x800, 0x100);
    if (dVar6 < 0.0f) {
        uVar4 = ((16384.0f * mFrameCtrlUnder[UNDER_MOVE0_e].getFrame()) /
                 m_HIO->mDam.mDamage.m.field_0x28);
        fVar1 = cM_ssin(uVar4);
        if (uVar4 < 0x2000) {
            uVar4 = uVar4 << 1;
        } else {
            uVar4 = 0x4000;
        }
        fVar2 = cM_ssin(uVar4);
    } else {
        uVar4 = (16384.0f * (1.0f - (dVar6 / (mFrameCtrlUnder[UNDER_MOVE0_e].getEnd() -
                                              m_HIO->mDam.mDamage.m.field_0x28))));
        fVar1 = 1.0f - cM_scos(uVar4);
        fVar2 = 1.0f - cM_scos(uVar4 < 0x2000 ? 0 : (s16)((uVar4 - 0x2000) * 2));
    }
    m3564 = m34D4 * fVar1;
    m3566 = 0;
    m3568 = m34D6 * fVar1;
    mBodyAngle.x = m34D4 * fVar2;
    mBodyAngle.z = m34D6 * fVar2;
    mBodyAngle.y = 0;
    dVar5 = cLib_addCalc(&mVelocity, 0.0f, m_HIO->mDam.mDamage.m.field_0x1C,
                         m_HIO->mDam.mDamage.m.field_0x20, m_HIO->mDam.mDamage.m.field_0x24);
    if (dVar5 <= 0.001f && mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    } else if (mVelocity < m_HIO->mDam.mDamage.m.field_0x2C) {
        resetFootEffect();
    }
    return true;
}

/* 801176FC-80117794       .text procPolyDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procPolyDamage_init() {
    commonProcInit(daPyProc_POLY_DAMAGE_e);
    mDamageWaitTimer = m_HIO->mDam.m.field_0x0;
    setSingleMoveAnime(ANM_DAM, m_HIO->mDam.mDamage.m.field_0x30, m_HIO->mDam.mDamage.m.field_0x34,
                       m_HIO->mDam.mDamage.m.field_0x4, m_HIO->mDam.mDamage.m.field_0x38);
    mVelocity = 0.0f;
    voiceStart(2);
    seStartOnlyReverb(JA_SE_LK_DAMAGE_NORMAL);
    offNoResetFlg0(daPyFlg0_UNK2);
    return true;
}

/* 80117794-801177CC       .text procPolyDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procPolyDamage() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    }
    return true;
}

/* 801177CC-80117EAC       .text procLargeDamage_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamage_init(int param_1, int param_2, s16 param_3, s16 param_4) {
    f32 fVar2;
    s16 sVar3;
    cXyz* damage_vec;
    int iVar7;

    if (mCurProc == daPyProc_LARGE_DAMAGE_e) {
        return false;
    }
    commonProcInit(daPyProc_LARGE_DAMAGE_e);
    if (mDemo.getDemoMode() != daPy_demo_c::DEMO_LDAM_e) {
        mDamageWaitTimer = m_HIO->mDam.m.field_0x0;
    } else {
        mDamageWaitTimer = 0;
    }
    if (param_1 == -4) {
        param_1 = -1;
        m34D0 = 5;
    } else {
        m34D0 = 0;
    }
    if (param_1 == -5) {
        iVar7 = 0;
        if ((!strcmp(dComIfGp_getStartStageName(), "kinBOSS")) ||
            (!strcmp(dComIfGp_getStartStageName(), "Xboss1")))
        {
            m32E4.makeEmitter(dPa_name::ID_SCENE_80F6, mpCLModel->getAnmMtx(0x1), &current.pos, NULL);
        }
        dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    } else if (param_1 == -3) {
        iVar7 = mDemo.getParam0();
        if (iVar7 == 0) {
            current.angle.y = shape_angle.y;
        } else if (iVar7 == 2) {
            current.angle.y = shape_angle.y + 0x4000;
        } else if (iVar7 == 3) {
            current.angle.y = shape_angle.y + -0x4000;
        } else {
            current.angle.y = shape_angle.y + 0x8000;
        }
    } else if (param_1 == -2 || param_1 == -9) {
        if (param_1 == -2) {
            current.angle.y = m3550;
            setDamagePoint(-1.0f);
        } else {
            damage_vec = getDamageVec(&mCyl);
            current.angle.y = cM_atan2s(damage_vec->x, damage_vec->z);
        }
        sVar3 = current.angle.y - shape_angle.y;
        if (std::abs(sVar3) < 8192.0f) {
            if (sVar3 >= 0) {
                sVar3 = 0x2000;
            } else {
                sVar3 = -0x2000;
            }
            current.angle.y = sVar3 + shape_angle.y;
        }
        iVar7 = getDirectionFromAngle(sVar3);
        seStartOnlyReverb(JA_SE_LK_DAMAGE_LARGE);
        dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    } else if (param_1 == -1 || param_1 == -6) {
        damage_vec = getDamageVec(&mCyl);
        current.angle.y = cM_atan2s(damage_vec->x, damage_vec->z);
        iVar7 = getDirectionFromAngle(current.angle.y - shape_angle.y);
        seStartOnlyReverb(JA_SE_LK_DAMAGE_LARGE);
        dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    } else if (param_1 == -10) {
        iVar7 = getDirectionFromAngle(current.angle.y - shape_angle.y);
    } else if (param_1 == -7) {
        iVar7 = 0;
        current.angle.y = shape_angle.y;
        fVar2 =
            ((2.0f * m_HIO->mDam.mHuDamage.m.field_0x20) / -m_HIO->mDam.mHuDamage.m.field_0x1C) *
            m_HIO->mDam.mHuDamage.m.field_0x18;
        current.pos.x = current.pos.x - fVar2 * cM_ssin(shape_angle.y);
        current.pos.z = current.pos.z - fVar2 * cM_scos(shape_angle.y);
        mDamageWaitTimer = 0;
        mAcch.m_flags = mAcch.m_flags | 4;
        mAcch.m_flags = mAcch.m_flags | 0x4000;
    } else {
        if (param_1 == 0x60) {
            iVar7 = 1;
        } else if (param_1 == 0x5d) {
            iVar7 = 2;
        } else if (param_1 == 0x5e) {
            iVar7 = 3;
        } else {
            iVar7 = 0;
        }
        setOldRootQuaternion(param_3, 0, param_4);
    }
    if (iVar7 == 0) {
        mProcVar0.mDamageAnm = ANM_DAMFB;
        m34D4 = 0x3fff;
        m34D6 = 4;
        shape_angle.y = current.angle.y;
    } else if (iVar7 == 3) {
        mProcVar0.mDamageAnm = ANM_DAMFL;
        m34D4 = 0x3fff;
        m34D6 = 0;
        shape_angle.y = current.angle.y + 0x4000;
    } else if (iVar7 == 2) {
        mProcVar0.mDamageAnm = ANM_DAMFR;
        m34D4 = -0x3fff;
        m34D6 = 0;
        shape_angle.y = current.angle.y + -0x4000;
    } else {
        mProcVar0.mDamageAnm = ANM_DAMFF;
        m34D4 = -0x3fff;
        m34D6 = 4;
        shape_angle.y = current.angle.y + 0x8000;
    }
    if (param_2 != 0) {
        fVar2 = m_HIO->mDam.mLaDamage.m.field_0x14;
        gravity = m_HIO->mDam.mLaDamage.m.field_0x1C;
        mMaxNormalSpeed = m_HIO->mDam.mLaDamage.m.field_0x18;
        m34D6 = m34D6 | 8;
        m34D8 = m_HIO->mDam.mLaDamage.m.field_0x2;
        m35A0 = m_HIO->mDam.mLaDamage.m.field_0x64;
    } else {
        fVar2 = m_HIO->mDam.mHuDamage.m.field_0x14;
        gravity = m_HIO->mDam.mHuDamage.m.field_0x1C;
        mMaxNormalSpeed = m_HIO->mDam.mHuDamage.m.field_0x18;
        m34D8 = m_HIO->mDam.mHuDamage.m.field_0x2;
        m35A0 = m_HIO->mDam.mHuDamage.m.field_0x64;
    }
    setSingleMoveAnime(mProcVar0.mDamageAnm, 1.0f, 0.0f, -1, fVar2);
    if (param_1 < 0) {
        if (param_1 != -7) {
            voiceStart(3);
        }
        fVar2 = 0.0f;
        if (param_1 != -5) {
            if (m34D0 > 0) {
                mVelocity = 0.0f;
                speed.y = fVar2;
            } else {
                if (param_2 != 0) {
                    mVelocity = m_HIO->mDam.mLaDamage.m.field_0x18;
                    speed.y = m_HIO->mDam.mLaDamage.m.field_0x20;
                } else {
                    mVelocity = m_HIO->mDam.mHuDamage.m.field_0x18;
                    speed.y = m_HIO->mDam.mHuDamage.m.field_0x20;
                }
            }
        }
    } else {
        if (param_2 != 0) {
            mVelocity = m_HIO->mDam.mLaDamage.m.field_0x64;
        } else {
            mVelocity = m_HIO->mDam.mHuDamage.m.field_0x64;
        }
        current.pos.x = current.pos.x + 35.0f * cM_ssin(current.angle.y);
        current.pos.z = current.pos.z + 35.0f * cM_scos(current.angle.y);
        speed.y = 0.0f;
    }
    offNoResetFlg0(daPyFlg0_UNK2);
    mBodyAngle.x = 0;
    mBodyAngle.y = 0;
    mBodyAngle.z = 0;
    if (param_1 == -7) {
        m34D6 = m34D6 | 2;
        mProcVar0.m3570 = -4;
    }
    return true;
}

/* 80117EAC-8011810C       .text procLargeDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamage() {
    if ((int)m34D0 > 0) {
        m34D0--;
        if (m34D0 == 0) {
            mVelocity = m_HIO->mDam.mLaDamage.m.field_0x18;
            speed.y = m_HIO->mDam.mLaDamage.m.field_0x20;
        } else {
            return true;
        }
    }
    s16* psVar3;
    if ((m34D6 & 4)) {
        psVar3 = &m34F2;
    } else {
        psVar3 = &m34F4;
    }
    cLib_chaseAngleS(psVar3, m34D4, m34D8);
    if ((m34D6 & 1)) {
        if (mAcch.ChkGroundHit()) {
            if (changeSlideProc()) {
                mVelocity = 0.0f;
            } else {
                if ((m34D6 & 2)) {
                    voiceStart(2);
                    seStartSystem(JA_SE_MAJUTOU_JAIL_DOOR);
                    mAcch.ClrWallNone();
                    mAcch.OffLineCheckNone();
                }
                procLargeDamageUp_init(mProcVar0.m3570, (u32)m34D6 >> 3 & 1, m34F2, m34F4);
            }
        } else if (mAcch.ChkWallHit() && mVelocity > m35A0) {
            dBgS_AcchCir* pdVar7 = &mAcchCir[0];
            for (int i = 0; i < 3; i++, pdVar7++) {
                if (pdVar7->ChkWallHit()) {
                    cXyz local_1c;
                    cXyz local_28;
                    local_1c.set(current.pos.x, current.pos.y + pdVar7->GetWallH(), current.pos.z);
                    local_28.set(
                        local_1c.x + cM_ssin(current.angle.y) * (pdVar7->GetWallR() + 25.0f),
                        local_1c.y,
                        local_1c.z + cM_scos(current.angle.y) * (pdVar7->GetWallR() + 25.0f));
                    mLinkLinChk.Set(&local_1c, &local_28, this);
                    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        return procLargeDamageWall_init(mProcVar0.m3570, (u32)m34D6 >> 3 & 1, m34F2,
                                                        m34F4);
                        break;
                    }
                }
            }
        }
    } else {
        m34D6 = m34D6 | 1;
    }
    return true;
}

/* 8011810C-80118504       .text procLargeDamageUp_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamageUp_init(int param_1, int param_2, s16 param_3, s16 param_4) {
    daPy_ANM dVar4;
    s16 sVar3;
    f32 dVar7;
    f32 dVar6;
    f32 dVar5;

    if (mCurProc == daPyProc_LARGE_DAMAGE_UP_e) {
        return false;
    }
    commonProcInit(daPyProc_LARGE_DAMAGE_UP_e);
    if (param_1 == -3) {
        dVar4 = ANM_DAMFFUP;
        dVar6 = 0.0f;
        sVar3 = -1;
        dVar5 = 5.0f;
        dVar7 = 0.5f;
        m34D0 = 0;
        m35A0 = 36.0f;
    } else if (param_1 == -1 || param_1 == -2) {
        dVar4 = ANM_DAMFBUP;
        dVar6 = 7.0f;
        sVar3 = -1;
        dVar5 = m_HIO->mDam.mLaDamage.m.field_0x40;
        m35A0 = 36.0f;
        if (param_1 == -1) {
            m34D0 = 0x1e;
            dVar7 = 0.0f;
        } else {
            m34D0 = 0;
            dVar7 = 0.5f;
        }
    } else if (param_1 == -4 || dComIfGp_evmng_startCheck("ICE_FAILED")) {
        dVar4 = ANM_DAMFBUP;
        dVar7 = 0.0f;
        dVar6 = 7.0f;
        sVar3 = m_HIO->mDam.mHuDamage.m.field_0x6;
        dVar5 = m_HIO->mDam.mHuDamage.m.field_0x40;
        m35A0 = m_HIO->mDam.mHuDamage.m.field_0x3C;
        if (param_1 == -4) {
            m34D0 = 0x28;
        } else {
            m34D0 = 30000;
            dProcFreezeDamage_init_sub(0);
        }
        m34BE = 6;
        dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        seStartMapInfo(JA_SE_LK_FALL_DOWN);
    } else {
        m34D0 = 0;
        m34BE = 6;
        dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        seStartMapInfo(JA_SE_LK_FALL_DOWN);
        if (param_1 == ANM_DAMFB) {
            dVar4 = ANM_DAMFBUP;
            if (param_2 != 0) {
                dVar7 = m_HIO->mDam.mLaDamage.m.field_0x34;
                dVar6 = m_HIO->mDam.mLaDamage.m.field_0x38;
                sVar3 = m_HIO->mDam.mLaDamage.m.field_0x6;
                dVar5 = m_HIO->mDam.mLaDamage.m.field_0x40;
                m35A0 = m_HIO->mDam.mLaDamage.m.field_0x3C;
            } else {
                dVar7 = m_HIO->mDam.mHuDamage.m.field_0x34;
                dVar6 = m_HIO->mDam.mHuDamage.m.field_0x38;
                sVar3 = m_HIO->mDam.mHuDamage.m.field_0x6;
                dVar5 = m_HIO->mDam.mHuDamage.m.field_0x40;
                m35A0 = m_HIO->mDam.mHuDamage.m.field_0x3C;
            }
        } else if (param_1 == ANM_DAMFL) {
            dVar4 = ANM_DAMFLUP;
            if (param_2 != 0) {
                dVar7 = m_HIO->mDam.mLaDamage.m.field_0x44;
                dVar6 = m_HIO->mDam.mLaDamage.m.field_0x48;
                sVar3 = m_HIO->mDam.mLaDamage.m.field_0x8;
                dVar5 = m_HIO->mDam.mLaDamage.m.field_0x50;
                m35A0 = m_HIO->mDam.mLaDamage.m.field_0x4C;
            } else {
                dVar7 = m_HIO->mDam.mHuDamage.m.field_0x44;
                dVar6 = m_HIO->mDam.mHuDamage.m.field_0x48;
                sVar3 = m_HIO->mDam.mHuDamage.m.field_0x8;
                dVar5 = m_HIO->mDam.mHuDamage.m.field_0x50;
                m35A0 = m_HIO->mDam.mHuDamage.m.field_0x4C;
            }
        } else if (param_1 == ANM_DAMFR) {
            dVar4 = ANM_DAMFRUP;
            if (param_2 != 0) {
                dVar7 = m_HIO->mDam.mLaDamage.m.field_0x54;
                dVar6 = m_HIO->mDam.mLaDamage.m.field_0x58;
                sVar3 = m_HIO->mDam.mLaDamage.m.field_0xA;
                dVar5 = m_HIO->mDam.mLaDamage.m.field_0x60;
                m35A0 = m_HIO->mDam.mLaDamage.m.field_0x5C;
            } else {
                dVar7 = m_HIO->mDam.mHuDamage.m.field_0x54;
                dVar6 = m_HIO->mDam.mHuDamage.m.field_0x58;
                sVar3 = m_HIO->mDam.mHuDamage.m.field_0xA;
                dVar5 = m_HIO->mDam.mHuDamage.m.field_0x60;
                m35A0 = m_HIO->mDam.mHuDamage.m.field_0x5C;
            }
        } else {
            dVar4 = ANM_DAMFFUP;
            if (param_2 != 0) {
                dVar7 = m_HIO->mDam.mLaDamage.m.field_0x24;
                dVar6 = m_HIO->mDam.mLaDamage.m.field_0x28;
                sVar3 = m_HIO->mDam.mLaDamage.m.field_0x4;
                dVar5 = m_HIO->mDam.mLaDamage.m.field_0x30;
                m35A0 = m_HIO->mDam.mLaDamage.m.field_0x2C;
            } else {
                dVar7 = m_HIO->mDam.mHuDamage.m.field_0x24;
                dVar6 = m_HIO->mDam.mHuDamage.m.field_0x28;
                sVar3 = m_HIO->mDam.mHuDamage.m.field_0x4;
                dVar5 = m_HIO->mDam.mHuDamage.m.field_0x30;
                m35A0 = m_HIO->mDam.mHuDamage.m.field_0x2C;
            }
        }
    }
    m35E4 = 1.0f;
    if (dComIfGs_getLife() == 0) {
        sVar3 = -1;
    }
    m35A4 = 2.0f / (m35A0 - dVar6);
    setSingleMoveAnime(dVar4, dVar7, dVar6, sVar3, dVar5);
    setOldRootQuaternion(param_3, 0, param_4);
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    mProcVar0.m3570 = param_1;
    return true;
}

/* 80118504-80118640       .text procLargeDamageUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamageUp() {
    m35E4 = m35A4 * (m35A0 - mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    resetFootEffect();
    if (m34D0 > 0) {
        if (!dComIfGp_evmng_startCheck("ICE_FAILED")) {
            m34D0--;
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        }
        if (m34D0 == 0 || (mProcVar0.m3570 == -4 && g_mDoCPd_cpadInfo[0].mMainStickValue > 0.05f)) {
            mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.5f);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (dComIfGp_event_runCheck()) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else {
            checkNextMode(0);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m35A0) {
        checkNextMode(1);
    }
    return true;
}

/* 80118640-801189AC       .text procLargeDamageWall_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamageWall_init(int param_1, int param_2, s16 param_3, s16 param_4) {
    f32 fVar1;
    f32 fVar2;
    s16 sVar3;
    f32 fVar5;
    s16 sVar6;
    s16 sVar7;
    s16 sVar10;

    if (mCurProc == daPyProc_LARGE_DAMAGE_WALL_e) {
        return false;
    }
    cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
    sVar6 = cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z);
    if (param_1 < 0 || !cBgW_CheckBWall(triPla->GetNP()->y) || cLib_distanceAngleS(sVar6, current.angle.y + -0x8000) > 0x1555) {
        return false;
    }
    commonProcInit(daPyProc_LARGE_DAMAGE_WALL_e);
    sVar7 = cM_atan2s(triPla->GetNP()->y, triPla->GetNP()->absXZ());
    current.angle.y = sVar6;
    current.pos.x = mLinkLinChk.GetCrossP()->x;
    current.pos.z = mLinkLinChk.GetCrossP()->z;
    setOldRootQuaternion(param_3, 0, param_4);
    sVar3 = sVar7;
    if (param_1 == 0x5c) {
        mProcVar0.mDamageAnm = ANM_DAMFBUP;
        if (param_2) {
            fVar1 = m_HIO->mDam.mLaDamage.m.field_0x74;
            fVar2 = m_HIO->mDam.mLaDamage.m.field_0x78;
            sVar10 = m_HIO->mDam.mLaDamage.m.field_0xE;
            fVar5 = m_HIO->mDam.mLaDamage.m.field_0x7C;
        } else {
            fVar1 = m_HIO->mDam.mHuDamage.m.field_0x74;
            fVar2 = m_HIO->mDam.mHuDamage.m.field_0x78;
            sVar10 = m_HIO->mDam.mHuDamage.m.field_0xE;
            fVar5 = m_HIO->mDam.mHuDamage.m.field_0x7C;
        }
        m34F2 = sVar3 + -0x4000;
        m34D0 = 0;
    } else if (param_1 == 0x59) {
        mProcVar0.mDamageAnm = ANM_DAMFLUP;
        if (param_2) {
            fVar1 = m_HIO->mDam.mLaDamage.m.field_0x80;
            fVar2 = m_HIO->mDam.mLaDamage.m.field_0x84;
            sVar10 = m_HIO->mDam.mLaDamage.m.field_0x10;
            fVar5 = m_HIO->mDam.mLaDamage.m.field_0x88;
        } else {
            fVar1 = m_HIO->mDam.mHuDamage.m.field_0x80;
            fVar2 = m_HIO->mDam.mHuDamage.m.field_0x84;
            sVar10 = m_HIO->mDam.mHuDamage.m.field_0x10;
            fVar5 = m_HIO->mDam.mHuDamage.m.field_0x88;
        }
        m34F4 = sVar3 + -0x4000;
        m34D0 = 1;
    } else if (param_1 == 0x5a) {
        mProcVar0.mDamageAnm = ANM_DAMFRUP;
        if (param_2) {
            fVar1 = m_HIO->mDam.mLaDamage.m.field_0x8C;
            fVar2 = m_HIO->mDam.mLaDamage.m.field_0x90;
            sVar10 = m_HIO->mDam.mLaDamage.m.field_0x12;
            fVar5 = m_HIO->mDam.mLaDamage.m.field_0x94;
        } else {
            fVar1 = m_HIO->mDam.mHuDamage.m.field_0x8C;
            fVar2 = m_HIO->mDam.mHuDamage.m.field_0x90;
            sVar10 = m_HIO->mDam.mHuDamage.m.field_0x12;
            fVar5 = m_HIO->mDam.mHuDamage.m.field_0x94;
        }
        m34F4 = 0x4000 - sVar3;
        m34D0 = 1;
    } else {
        mProcVar0.mDamageAnm = ANM_DAMFFUP;
        if (param_2) {
            fVar1 = m_HIO->mDam.mLaDamage.m.field_0x68;
            fVar2 = m_HIO->mDam.mLaDamage.m.field_0x6C;
            sVar10 = m_HIO->mDam.mLaDamage.m.field_0xC;
            fVar5 = m_HIO->mDam.mLaDamage.m.field_0x70;
        } else {
            fVar1 = m_HIO->mDam.mHuDamage.m.field_0x68;
            fVar2 = m_HIO->mDam.mHuDamage.m.field_0x6C;
            sVar10 = m_HIO->mDam.mHuDamage.m.field_0xC;
            fVar5 = m_HIO->mDam.mHuDamage.m.field_0x70;
        }
        m34F2 = 0x4000 - sVar3;
        m34D0 = 0;
    }
    setSingleMoveAnime(mProcVar0.mDamageAnm, fVar1, fVar2, sVar10, fVar5);
    mVelocity = 0.0f;
    speed.y = 0.0f;
    gravity = 0.0f;
    dComIfGp_getVibration().StartShock(6, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    m34D0 = param_2;
    return true;
}

/* 801189AC-801189F0       .text procLargeDamageWall__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamageWall() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        procLargeDamage_init(mProcVar0.m3570, m34D0, m34F2, m34F4);
    }
    return true;
}

/* 801189F0-80118BC4       .text procLavaDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procLavaDamage_init() {
    if (mCurProc == daPyProc_LAVA_DAMAGE_e) {
        if (speed.y <= 0.0f) {
            speed.y = 30.0f;
        }
        gravity = -2.5f;
        return true;
    }
    commonProcInit(daPyProc_LAVA_DAMAGE_e);
    f32 dVar3 = current.pos.absXZ();
    dVar3 = ((1.0f / 1700.0f) * (1700.0f - dVar3) - 0.25f);
    if (dVar3 < 0.0) {
        dVar3 = 0.0f;
    }
    gravity = -2.5f;
    mVelocity = 15.0f + (40.0f * dVar3);
    speed.y = 32.0f + (36.0f * dVar3);
    setSingleMoveAnime(ANM_LAVADAM, m_HIO->mRestart.m.field_0x0, 0.0f, -1, m_HIO->mRestart.m.field_0x4);
    m32E4.makeEmitter(dPa_name::ID_SCENE_8078, mpCLModel->getAnmMtx(0), &current.pos, NULL);
    voiceStart(4);
    seStartMapInfo(JA_SE_LK_FALL_MAGMA);
    current.angle.y = cM_atan2s(current.pos.x, current.pos.z);
    mDamageWaitTimer = m_HIO->mDam.m.field_0x0;
    setDamagePoint(-1.0f);

    return true;
}

/* 80118BC4-80118C58       .text procLavaDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLavaDamage() {
    if (mAcch.ChkGroundHit()) {
        int direction = getDirectionFromAngle(current.angle.y - shape_angle.y);
        daPy_ANM anm;
        if (direction == DIR_FORWARD) {
            anm = ANM_DAMFB;
        } else if (direction == DIR_BACKWARD) {
            anm = ANM_DAMFF;
        } else if (direction == DIR_LEFT) {
            anm = ANM_DAMFR;
        } else { // DIR_RIGHT
            anm = ANM_DAMFL;
        }
        procLargeDamageUp_init(anm, 1, 0, 0);
    }
    return true;
}

/* 80118C58-80118E6C       .text procElecDamage_init__9daPy_lk_cFPC4cXyz */
BOOL daPy_lk_c::procElecDamage_init(const cXyz* param_1) {
    if (!dComIfGp_event_compulsory(this)) {
        return false;
    }
    mDemo.setDemoType(5);
    int iVar2 = checkShipRideUseItem(0);
    if (checkModeFlg(ModeFlg_SWIM)) {
        current.pos.y += m35C4;
        m34D4 = 1;
        swimOutAfter(1);
    } else {
        m34D4 = 0;
    }
    commonProcInit(daPyProc_ELEC_DAMAGE_e);
    if (!mAcch.ChkGroundHit()) {
        gravity = 0.0f;
        if (m34D4 == 0) {
            onModeFlg(ModeFlg_MIDAIR);
        }
    }
    mVelocity = 0.0f;
    speed.y = 0.0f;
    setSingleMoveAnime(ANM_DAMBIRI, m_HIO->mDam.mElecDamage.m.field_0x4, 0.0f, -1,
                       m_HIO->mDam.mElecDamage.m.field_0x8);
    mDamageWaitTimer = m_HIO->mDam.m.field_0x0;
    m34D0 = m_HIO->mDam.mElecDamage.m.field_0x0;
    if (param_1 != 0) {
        m370C = current.pos - *param_1;
        m34D6 = 1;
    } else {
        if (mCyl.ChkTgHit()) {
            cXyz* damage_vec = getDamageVec(&mCyl);
            m370C = *damage_vec;
            m34D6 = 1;
        } else {
            m34D6 = 0;
        }
    }
    initShipRideUseItem(iVar2, 0);
    seStartOnlyReverb(JA_SE_LK_ELEC_PARALYSED);
    voiceStart(44);
    dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    return true;
}

/* 80118E6C-80118F40       .text procElecDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procElecDamage() {
    setShipRidePosUseItem();
    if (m34D0 > 0) {
        m34D0--;
    } else {
        dComIfGp_event_reset();
        endDemoMode();
        if (mAcch.ChkGroundHit() && m34D6 == 0) {
            checkNextMode(0);
        } else {
            if (m34D6 != 0) {
                current.angle.y = cM_atan2s(m370C.x, m370C.z);
            } else {
                current.angle.y = shape_angle.y + 0x8000;
            }
            procLargeDamage_init(-10, 1, 0, 0);
        }
    }
    return true;
}

/* 80118F40-80119248       .text procGuardSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardSlip_init() {
    daPy_ANM dVar5;

    cXyz* damage_vec = getDamageVec(&mCyl);
    commonProcInit(daPyProc_GUARD_SLIP_e);
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        dVar5 = ANM_ATNGAHAM;
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_ATNGAHAMA));
    } else if (mDirection == DIR_LEFT) {
        dVar5 = ANM_ATNGAL;
    } else {
        dVar5 = ANM_ATNGAR;
    }
    dCcD_GObjInf* iVar4 = mCyl.GetTgHitGObj();
    if (iVar4 != NULL && (iVar4->GetAtSpl() == dCcG_At_Spl_UNK5 ||
                          iVar4->GetAtSpl() == dCcG_At_Spl_UNK6 ||
                          iVar4->GetAtSpl() == dCcG_At_Spl_UNK7))
    {
        setSingleMoveAnime(dVar5, m_HIO->mNockback.m.field_0x8,
                           m_HIO->mNockback.m.field_0xC, m_HIO->mNockback.m.field_0x0,
                           m_HIO->mNockback.m.field_0x10);
        mVelocity = (m_HIO->mNockback.m.field_0x18 * damage_vec->absXZ()) +
                    m_HIO->mNockback.m.field_0x14;
        m34D0 = m_HIO->mNockback.m.field_0x2;
        m35A0 = m_HIO->mNockback.m.field_0x1C;
        m35A4 = m_HIO->mNockback.m.field_0x20;
        m35A8 = m_HIO->mNockback.m.field_0x24;
        m35AC = m_HIO->mNockback.m.field_0x28;
        mProcVar0.m3570 = (cM_rnd() < 0.2f) ? 1 : 0;
    } else {
        setSingleMoveAnime(dVar5, m_HIO->mGuard.m.field_0x4, m_HIO->mGuard.m.field_0x8,
                           m_HIO->mGuard.m.field_0x0, m_HIO->mGuard.m.field_0xC);
        mVelocity =
            (m_HIO->mGuard.m.field_0x14 * damage_vec->absXZ()) + m_HIO->mGuard.m.field_0x10;
        m34D0 = m_HIO->mGuard.m.field_0x2;
        m35A0 = m_HIO->mGuard.m.field_0x18;
        m35A4 = m_HIO->mGuard.m.field_0x1C;
        m35A8 = m_HIO->mGuard.m.field_0x20;
        m35AC = m_HIO->mGuard.m.field_0x24;
        mProcVar0.m3570 = 0;
    }
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    } else {
        m35E8 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    }
    current.angle.y = cM_atan2s(damage_vec->x, damage_vec->z);
    m34BE = 3;
    m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
    return true;
}

/* 80119248-80119334       .text procGuardSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardSlip() {
    if (m34D0 > 0) {
        m34D0--;
    }
    setShapeAngleToAtnActor();
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    } else {
        m35E8 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    }
    if (cLib_addCalc(&mVelocity, 0.0f, m35A0, m35A4, m35A8) <= 0.001f) {
        if (mProcVar0.m3570 != 0) {
            return procNockBackEnd_init();
        }
        if (m34D0 == 0) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
            checkNextMode(0);
        }
    } else {
        if (mVelocity < m35AC) {
            resetFootEffect();
        }
    }
    return true;
}

/* 80119334-80119478       .text procIceSlipFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFall_init() {
    commonProcInit(daPyProc_ICE_SLIP_FALL_e);
    int direction = getDirectionFromAngle(cM_atan2s(-m36A0.x, -m36A0.z) - shape_angle.y);
    if (direction == DIR_FORWARD) {
        mProcVar0.mDamageAnm = ANM_DAMFB;
        m34D4 = 0x3fff;
        m34D6 = 1;
    } else if (direction == DIR_RIGHT) {
        mProcVar0.mDamageAnm = ANM_DAMFL;
        m34D4 = 0x3fff;
        m34D6 = 0;
    } else if (direction == DIR_LEFT) {
        mProcVar0.mDamageAnm = ANM_DAMFR;
        m34D4 = -0x3fff;
        m34D6 = 0;
    } else { // DIR_BACKWARD
        mProcVar0.mDamageAnm = ANM_DAMFF;
        m34D4 = -0x3fff;
        m34D6 = 1;
    }
    setSingleMoveAnime(mProcVar0.mDamageAnm, 1.0f, 0.0f, -1, m_HIO->mIceSlip.m.field_0x20);
    mVelocity = 0.0f;
    speed.y = m_HIO->mIceSlip.m.field_0x1C;
    mBodyAngle.x = 0;
    mBodyAngle.y = 0;
    mBodyAngle.z = 0;
    voiceStart(36);
    return true;
}

/* 80119478-80119500       .text procIceSlipFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFall() {
    s16* psVar1;

    if (m34D6 == 1) {
        psVar1 = &m34F2;
    } else {
        psVar1 = &m34F4;
    }
    cLib_chaseAngleS(psVar1, m34D4, m_HIO->mIceSlip.m.field_0x2);
    if (mAcch.ChkGroundHit() && !changeSlideProc()) {
        procIceSlipFallUp_init(mProcVar0.m3570, m34F2, m34F4);
    }
    return true;
}

/* 80119500-80119688       .text procIceSlipFallUp_init__9daPy_lk_cFiss */
BOOL daPy_lk_c::procIceSlipFallUp_init(int param_1, s16 param_2, s16 param_3) {
    f32 fVar1;
    f32 fVar2;
    f32 fVar3;
    daPy_ANM dVar5;
    s16 sVar6;

    commonProcInit(daPyProc_ICE_SLIP_FALL_UP_e);
    m34BE = 6;
    dComIfGp_getVibration().StartShock(3, -0x3f, cXyz(0.0f, 1.0f, 0.0f));
    seStartMapInfo(JA_SE_LK_FALL_DOWN);
    if (param_1 == ANM_DAMFB) {
        dVar5 = ANM_DAMFBUP;
        fVar1 = m_HIO->mIceSlip.m.field_0x34;
        fVar2 = m_HIO->mIceSlip.m.field_0x38;
        sVar6 = m_HIO->mIceSlip.m.field_0x6;
        fVar3 = m_HIO->mIceSlip.m.field_0x40;
        m35A0 = m_HIO->mIceSlip.m.field_0x3C;
    } else if (param_1 == ANM_DAMFL) {
        dVar5 = ANM_DAMFLUP;
        fVar1 = m_HIO->mIceSlip.m.field_0x44;
        fVar2 = m_HIO->mIceSlip.m.field_0x48;
        sVar6 = m_HIO->mIceSlip.m.field_0x8;
        fVar3 = m_HIO->mIceSlip.m.field_0x50;
        m35A0 = m_HIO->mIceSlip.m.field_0x4C;
    } else if (param_1 == ANM_DAMFR) {
        dVar5 = ANM_DAMFRUP;
        fVar1 = m_HIO->mIceSlip.m.field_0x54;
        fVar2 = m_HIO->mIceSlip.m.field_0x58;
        sVar6 = m_HIO->mIceSlip.m.field_0xA;
        fVar3 = m_HIO->mIceSlip.m.field_0x60;
        m35A0 = m_HIO->mIceSlip.m.field_0x5C;
    } else {
        dVar5 = ANM_DAMFFUP;
        fVar1 = m_HIO->mIceSlip.m.field_0x24;
        fVar2 = m_HIO->mIceSlip.m.field_0x28;
        sVar6 = m_HIO->mIceSlip.m.field_0x4;
        fVar3 = m_HIO->mIceSlip.m.field_0x30;
        m35A0 = m_HIO->mIceSlip.m.field_0x2C;
    }
    m35E4 = 1.0f;
    m35A4 = 2.0f / (m35A0 - fVar2);
    setSingleMoveAnime(dVar5, fVar1, fVar2, sVar6, fVar3);
    setOldRootQuaternion(param_2, 0, param_3);
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    return true;
}

/* 80119688-8011970C       .text procIceSlipFallUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFallUp() {
    m35E4 = m35A4 * (m35A0 - mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    resetFootEffect();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m35A0) {
            checkNextMode(1);
        }
    }
    return true;
}

/* 8011970C-801197D4       .text procIceSlipAlmostFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipAlmostFall_init() {
    commonProcInit(daPyProc_ICE_SLIP_ALMOST_FALL_e);
    current.angle.y = cM_atan2s(m36AC.x, m36AC.z);
    int direction = getDirectionFromAngle(current.angle.y - shape_angle.y);
    daPy_ANM anm;
    if (direction == DIR_BACKWARD) {
        anm = ANM_DAMF;
    } else if (direction == DIR_LEFT) {
        anm = ANM_DAMR;
    } else if (direction == DIR_RIGHT) {
        anm = ANM_DAML;
    } else { // DIR_FORWARD
        anm = ANM_DAMB;
    }
    setSingleMoveAnime(anm, m_HIO->mIceSlip.m.field_0x64, m_HIO->mIceSlip.m.field_0x68,
                       m_HIO->mIceSlip.m.field_0xC, m_HIO->mIceSlip.m.field_0x70);
    setTextureAnime(6, 0);
    mVelocity = 0.0f;
    return true;
}

/* 801197D4-80119864       .text procIceSlipAlmostFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipAlmostFall() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        current.angle.y = shape_angle.y;
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mIceSlip.m.field_0x6C) {
            s16 sVar1 = current.angle.y;
            current.angle.y = shape_angle.y;
            if (!checkNextMode(1)) {
                current.angle.y = sVar1;
            }
        }
    }
    return true;
}

/* 80119864-801198E0       .text procBootsEquip_init__9daPy_lk_cFUs */
BOOL daPy_lk_c::procBootsEquip_init(u16 param_1) {
    commonProcInit(daPyProc_BOOTS_EQUIP_e);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_SETBOOTS, m_HIO->mItem.mBoots.m.field_0x4, m_HIO->mItem.mBoots.m.field_0x8,
                       m_HIO->mItem.mBoots.m.field_0x0, m_HIO->mItem.mBoots.m.field_0x10);
    mProcVar0.m3570 = param_1;
    return true;
}

/* 801198E0-80119A5C       .text procBootsEquip__9daPy_lk_cFv */
BOOL daPy_lk_c::procBootsEquip() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    if (frameCtrl.checkPass(11.0f)) {
        if (checkEquipHeavyBoots()) {
            offNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
        } else {
            onNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
        }
    }
    if (frameCtrl.getRate() < 0.01f) {
#if VERSION <= VERSION_JPN
        checkNextMode(0);
#else
        if (checkGrabAnime()) {
            initGrabNextMode();
        } else {
            checkNextMode(0);
        }
#endif
    } else {
        if (frameCtrl.getFrame() > m_HIO->mItem.mBoots.m.field_0xC) {
#if VERSION <= VERSION_JPN
            checkNextMode(1);
#else
            if (checkGrabAnime()) {
                if (mStickDistance > 0.05f) {
                    initGrabNextMode();
                }
            } else {
                checkNextMode(1);
            }
#endif
        } else {
            if (frameCtrl.checkPass(15.0f) && checkEquipHeavyBoots()) {
                dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
            }
        }
    }
    return true;
}

/* 80119A5C-80119BA0       .text procNotUse_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procNotUse_init(int param_1) {
    if (!dComIfGp_event_compulsory(this)) {
        return false;
    }
    mDemo.setDemoType(5);
    commonProcInit(daPyProc_NOT_USE_e);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_PRESENTATIONB, m_HIO->mTurn.m.field_0x34,
                       m_HIO->mTurn.m.field_0x38, m_HIO->mTurn.m.field_0x10,
                       m_HIO->mTurn.m.field_0x3C);
    keepItemData();
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK800_e);
    m3628 = fpcM_ERROR_PROCESS_ID_e;
    mProcVar0.m3570 = param_1;
    m3574 = 5;
    dCam_getBody()->StartEventCamera(0x12, fopAcM_GetID(this), "Type", &m3574, 0);
    if (isDaizaItem(mProcVar0.m3570)) {
        m3624 = 0xf0c;
    } else {
        m3624 = 0x835;
    }
    m34D4 = 0;
    return true;
}

/* 80119BA0-80119DA0       .text procNotUse__9daPy_lk_cFv */
BOOL daPy_lk_c::procNotUse() {
    if (m34D4 == 0 && !checkBottleItem((u16)mProcVar0.mBottleItem)) {
        dComIfGp_event_setItemPartnerId(fopAcM_createItemForPresentDemo(
            &current.pos,
            mProcVar0.mBottleItem,
            daDitem_c::FLAG_UNK01 | daDitem_c::FLAG_UNK04,
            -1,
            fopAcM_GetRoomNo(this),
            &shape_angle,
            &scale
        ));
        m34D4 = 1;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        daItemBase_c* item = (daItemBase_c*)fopAcM_getItemEventPartner(this);
        if (item != NULL && (fopAcM_GetName(item) == PROC_ITEM || fopAcM_GetName(item) == PROC_Demo_Item)) {
            item->show();
        }
        if (m34D4 == 0 && checkBottleItem((u16)mProcVar0.mBottleItem)) {
            setBottleModel(mProcVar0.mBottleItem);
            m34D4 = 1;
        }
        if (m3628 == fpcM_ERROR_PROCESS_ID_e) {
            m3628 = fopMsgM_messageSet(m3624);
        } else {
            msg_class* msg_p = fopMsgM_SearchByID(m3628);
            if (msg_p != 0) {
                if (msg_p->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                    if (m3624 == 0xf0c && msg_p->mSelectNum == 1) {
                        msg_p->mStatus = fopMsgStts_MSG_CONTINUES_e;
                        m3624 = 0xf10;
                        fopMsgM_messageSet(m3624);
                        dComIfGs_setReserveItemEmpty(mReadyItemBtn);
                    } else {
                        msg_p->mStatus = fopMsgStts_MSG_ENDS_e;
                    }
                } else if (msg_p->mStatus == fopMsgStts_BOX_CLOSED_e) {
                    msg_p->mStatus = fopMsgStts_MSG_DESTROYED_e;
                    if (item != NULL && (fopAcM_GetName(item) == PROC_ITEM || fopAcM_GetName(item) == PROC_Demo_Item)) {
                        item->dead();
                    }
                    dComIfGp_event_reset();
                    dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
                    endDemoMode();
                }
            }
        }
    }
    return true;
}

/* 80119DA0-80119EBC       .text getGroundAngle__9daPy_lk_cFP13cBgS_PolyInfos */
s16 daPy_lk_c::getGroundAngle(cBgS_PolyInfo* param_1, s16 param_2) {
    cM3dGPla* plane = dComIfG_Bgsp()->GetTriPla(*param_1);
    if (plane == NULL || !cBgW_CheckBGround(plane->GetNP()->y)) {
        return 0;
    }
    cXyz* norm = plane->GetNP();
    f32 cos = cM_scos((cM_atan2s(norm->x, norm->z) - param_2));
    f32 xz = (std::sqrtf(norm->x * norm->x + norm->z * norm->z));
    xz *= cos;
    return cM_atan2s(xz, norm->y);
}

/* 80119EBC-8011A508       .text setLegAngle__9daPy_lk_cFfiPsPs */
int daPy_lk_c::setLegAngle(f32 param_1, int param_2, s16* param_3, s16* param_4) {
    f32 dVar8;
    f32 dVar9;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    f32 dVar13;
    cXyz spE8;
    cXyz spDC;
    cXyz spD0;
    cXyz spC4;
    cXyz spB8;
    cXyz spAC;
    cXyz spA0;
    cXyz sp94;
    cXyz sp88;
    cXyz sp7C;
    cXyz sp70;
    cXyz sp64;
    cXyz sp58;

    if (std::abs(param_1) < 0.1f) {
        return false;
    }
    dVar9 = 0.5f * param_1;
    if (dVar9 > 10.0f) {
        dVar9 = 10.0f;
    }
    dVar8 = param_1;
    mDoMtx_concat(m37B4, mFootData[param_2].field_0x088[0], mDoMtx_stack_c::get());
    spE8.set(0.0f, mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);

    mDoMtx_concat(m37B4, mFootData[param_2].field_0x088[1], mDoMtx_stack_c::get());
    spDC.set(0.0f, mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);

    mDoMtx_concat(m37B4, mFootData[param_2].field_0x088[2], mDoMtx_stack_c::get());
    spD0.set(0.0f, mDoMtx_stack_c::get()[1][3] + 3.25f, mDoMtx_stack_c::get()[2][3]);
    spAC = spDC - spE8;
    spA0 = spD0 - spDC;
    spB8.x = spD0.x;
    spB8.y = spD0.y;
    spB8.z = spD0.z;
    spB8.y += dVar8;
    spB8.z += dVar9;
    if (spB8.y >= spE8.y) {
        return false;
    }
    sp7C = spB8 - spE8;
    dVar9 = sp7C.abs2();
    if (cM3d_IsZero(dVar9)) {
        return false;
    }
    dVar10 = spAC.abs2();
    dVar11 = spA0.abs2();
    dVar8 = std::sqrtf(dVar10);
    dVar12 = std::sqrtf(dVar11);
    dVar13 = std::sqrtf(dVar9);
    if ((dVar8 + dVar12) <= dVar13) {
        return false;
    }
    dVar8 = (((dVar9 + dVar10) - dVar11) / (2.0f * dVar9));
    sp58.x = 0.0f;
    sp58.y = spE8.y + (dVar8 * sp7C.y);
    sp58.z = spE8.z + (dVar8 * sp7C.z);
    f32 f4 = dVar10 - (dVar8 * (dVar9 * dVar8));
    if (f4 < 0.0f) {
        f4 = 0.0f;
    }
    dVar9 = std::sqrtf(f4);
    sp70.x = 0.0f;
    sp70.y = sp7C.z;
    sp70.z = -sp7C.y;
    dVar8 = sp70.abs();
    if (cM3d_IsZero(dVar8)) {
        return false;
    }
    f32 f2 = dVar9 / dVar8;
    spC4.x = 0.0f;
    spC4.y = sp58.y + f2 * sp70.y;
    spC4.z = sp58.z + f2 * sp70.z;
    sp94 = spC4 - spE8;
    sp88 = spB8 - spC4;
    mDoMtx_concat(m37B4, mpCLModel->getAnmMtx(0), mDoMtx_stack_c::get());
    sp64.set(0.0f, mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
    s16 r29 = cM_atan2s(-sp64.y, -sp64.z);
    s16 r27 = cM_atan2s(sp94.y, sp94.z);
    s16 r26 = cM_atan2s(sp88.y, sp88.z);
    s16 r3 = r27 - r29;
    if (r3 > 0x6000) {
        r27 = r29 + 0x6000;
    } else if (r3 < -0x4000) {
        r27 = r29 + -0x4000;
    }
    s16 r0 = r26 - r27;
    if (r0 > 0) {
        r26 = r27;
    } else if (r0 < -0x7000) {
        r26 = r27 + -0x7000;
    }
    *param_3 = cM_atan2s(spAC.y, spAC.z) - r27;
    *param_4 = cM_atan2s(spA0.y, spA0.z) - r26;
    return true;
}

/* 8011A508-8011ABB0       .text footBgCheck__9daPy_lk_cFv */
void daPy_lk_c::footBgCheck() {
    u32 r28;
    f32 sp18[2];
    int sp10[2];
    int i;
    f32* r26;

    MtxP r30 = mpCLModel->getBaseTRMtx();
    u32 r29 = checkModeFlg(ModeFlg_00000001);
    mDoMtx_concat(m37B4, mpCLModel->getAnmMtx(0x1E), mDoMtx_stack_c::get());
    MtxP r31 = mDoMtx_stack_c::get();

    daPy_footData_c* r25_r26;
    f32 f28 = cM_ssin(m34E0);
    f32 f27 = cM_scos(m34E0);
    r25_r26 = mFootData;
    r26 = sp18;
    for (i = 0; i < 2; i++, r25_r26++, r26++) {
        cXyz sp74;
        cXyz sp68;
        cXyz sp5C;
        cXyz sp50;
        sp74 = (r25_r26->field_0x018 + r25_r26->field_0x00C) * 0.5f;
        sp50 = sp74 - r25_r26->field_0x024;
        if (sp50.abs2XZ() < SQUARE(10.0f) && r29 != 0) {
            if (r25_r26->field_0x001 != 0) {
                r25_r26->field_0x001--;
            } else {
                sp74 = r25_r26->field_0x024;
            }
        } else {
            r25_r26->field_0x001 = 5;
        }
        r25_r26->field_0x024 = sp74;
        f32 f26 = r31[1][3] + (f27 * (sp74.y - r31[1][3])) + (f28 * (sp74.z - r31[2][3]));
        mDoMtx_multVec(r30, &sp74, &sp68);
        sp5C.set(sp68.x, current.pos.y + 30.1f, sp68.z);
        r25_r26->field_0x034.SetPos(&sp5C);
        f32 f1 = dComIfG_Bgsp()->GroundCross(&r25_r26->field_0x034);
        if (checkNoResetFlg0(daPyFlg0_UNK80000000) && current.pos.y > f1) {
            f1 = current.pos.y;
            sp10[i] = 1;
        } else {
            sp10[i] = 0;
        }
        if (f1 != -G_CM3D_F_INF && sp5C.y - f1 < 60.2f) {
            *r26 = f1;
            r25_r26->field_0x000 = 1;
        } else {
            *r26 = current.pos.y;
            r25_r26->field_0x000 = 0;
        }
        if (checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) && *r26 <= current.pos.y) {
            *r26 = current.pos.y;
        }
        *r26 -= (sp74.y - f26);
    }

    int r23;
    if (!mAcch.ChkGroundHit() || checkModeFlg(
                                     // Note: These flags combine into 0x1045A822.
                                     ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP | ModeFlg_00008000 |
                                     ModeFlg_CLIMB | ModeFlg_SWIM | ModeFlg_LADDER | ModeFlg_CAUGHT
                                 ))
    {
        r23 = 2;
    } else if (sp18[0] > sp18[1]) {
        r23 = 1;
    } else {
        r23 = 0;
    }
    f32 f1;
    if (r23 == 2 || mCurProc == daPyProc_DEMO_TOOL_e || std::abs(m35C4) > 1.0f) {
        f1 = 0.0f;
    } else {
        if (sp18[0] > sp18[1]) {
            f1 = sp18[1];
        } else {
            f1 = sp18[0];
        }
        f1 -= current.pos.y;
    }
    cLib_addCalc(&m35B8, f1, 0.5f, 7.5f, 2.5f);
    r30[1][3] += m35B8;
    m37B4[1][3] = m37B4[1][3] - m35B8;
    s16 sp0C[2];
    s16 sp08[2];
    if (r23 == 2) {
        for (int i = 0; i < 2; i++) {
            sp0C[i] = 0;
            sp08[i] = 0;
            mFootData[i].field_0x030 = 0.0f;
        }
    } else {
        r28 = r23 + 1 & 1;
        r25_r26 = &mFootData[r28];
        daPy_footData_c* temp_foot_data = &mFootData[r23];
        temp_foot_data->field_0x030 = 0.0f;
        if (!setLegAngle(sp18[r23] - r30[1][3], r23, &sp0C[r23], &sp08[r23])) {
            sp0C[r23] = 0;
            sp08[r23] = 0;
        }
        f32 f1 = sp18[r28] - r30[1][3];
        if (f1 > 0.0f || r29 != 0) {
            r25_r26->field_0x030 = 0.3f * f1;
            if (!setLegAngle(0.7f * f1, r28, &sp0C[r28], &sp08[r28])) {
                sp0C[r28] = 0;
                sp08[r28] = 0;
            }
        } else {
            r25_r26->field_0x030 = 0.0f;
            sp0C[r28] = 0;
            sp08[r28] = 0;
        }
    }

    for (i = 0; i < 2; i++) {
        r25_r26 = &mFootData[i];
        if (r25_r26->field_0x008 * sp0C[i] < 0 && abs(sp0C[i] - r25_r26->field_0x008) >= 0x8000) {
            if (sp0C[i] >= 0) {
                sp0C[i] -= 0x4000;
            } else {
                sp0C[i] += 0x4000;
            }
        }
        cLib_addCalcAngleS(&r25_r26->field_0x008, sp0C[i], 2, 0x1800, 0x10);
        cLib_addCalcAngleS(&r25_r26->field_0x006, sp08[i], 2, 0x1800, 0x10);
        r25_r26->field_0x00A = r25_r26->field_0x006 - r25_r26->field_0x008;
        r25_r26->field_0x002 = -(m34E0 + r25_r26->field_0x006);
    }

    r25_r26 = mFootData;
    for (i = 0; i < 2; i++, r25_r26++) {
        s16 r4;
        if (sp10[i] == 0 && r25_r26->field_0x000 != 0 && r29 != 0) {
            r4 = getGroundAngle(&r25_r26->field_0x034, shape_angle.y);
            r25_r26->field_0x002 = r25_r26->field_0x002 + r4;
            r4 = getGroundAngle(&r25_r26->field_0x034, shape_angle.y + -0x4000);
        } else {
            r4 = 0;
        }
        cLib_addCalcAngleS(&r25_r26->field_0x004, r4, 2, 0x1800, 0x10);
    }
}

/* 8011ABB0-8011AC78       .text setWaterY__9daPy_lk_cFv */
void daPy_lk_c::setWaterY() {
    if (!daSea_ChkArea(current.pos.x, current.pos.z)) {
        if (mAcch.ChkWaterHit()) {
            onNoResetFlg0(daPyFlg0_UNK80);
        } else {
            offNoResetFlg0(daPyFlg0_UNK80);
        }
        m35D0 = mAcch.m_wtr.GetHeight();
        dPa_control_c::offStatus(1);
    } else {
        onNoResetFlg0(daPyFlg0_UNK80);
        m35D0 = daSea_calcWave(current.pos.x, current.pos.z);
        if (mAcch.m_wtr.GetHeight() > m35D0) {
            m35D0 = mAcch.m_wtr.GetHeight();
            dPa_control_c::offStatus(1);
        } else {
            dPa_control_c::onStatus(1);
        }
    }
}

/* 8011AC78-8011AD9C       .text autoGroundHit__9daPy_lk_cFv */
void daPy_lk_c::autoGroundHit() {
    u32 uVar4 = checkNoResetFlg0(daPyFlg0_UNK80000000);
    offNoResetFlg0(daPyFlg0_UNK80000000);
    if (mTinkleHoverTimer == 0) {
        offNoResetFlg0(daPyFlg0_HOVER_BOOTS);
    }
    if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0) {
        if (mTinkleHoverTimer > 0) {
            mTinkleHoverTimer--;
        }
    }
    if (daPy_lk_c::checkPlayerFly()) {
        return;
    }
    f32 fVar1 = mAcch.GetGroundH();
    f32 fVar2 = fVar1 - current.pos.y;
    if (mAcch.ChkGroundHit()) {
        return;
    }
    if (fVar2 < 0.0f) {
        if (fVar2 >= -30.1f && uVar4 == 0) {
            current.pos.y = fVar1;
            mAcch.SetGroundHit();
            speed.y = 0.0f;
            return;
        }
    }
    if (!checkNoResetFlg0(daPyFlg0_HOVER_BOOTS)) {
        return;
    }
    if (!(mTinkleHoverTimer > 0)) {
        return;
    }
    if (dComIfGp_event_runCheck() && mDemo.getDemoType() != 5) {
        return;
    }
    current.pos.y = old.pos.y;
    mAcch.SetGroundHit();
    speed.y = 0.0f;
    onNoResetFlg0(daPyFlg0_UNK80000000);
}

/* 8011AD9C-8011AE20       .text checkAttentionPosAngle__9daPy_lk_cFP10fopAc_ac_cPP4cXyz */
BOOL daPy_lk_c::checkAttentionPosAngle(fopAc_ac_c* actor, cXyz** pOutPos) {
    if (actor) {
        s16 targetAngle = cLib_targetAngleY(&current.pos, &actor->eyePos);
        int angleDiff = cLib_distanceAngleS(targetAngle, m34DE);
        if (angleDiff <= 0x6000) {
            *pOutPos = &actor->eyePos;
            if (actor->group == fopAc_ENEMY_e) {
                onNoResetFlg1(daPyFlg1_UNK400);
            }
            return TRUE;
        }
    }
    return FALSE;
}

/* 8011AE20-8011BE08       .text setNeckAngle__9daPy_lk_cFv */
void daPy_lk_c::setNeckAngle() {
    /* Nonmatching - regalloc */
    cXyz spC4;
    cXyz spB8;
    cXyz spAC;
    cXyz spA0;
    cXyz sp94;
    cXyz sp88;

    offNoResetFlg1(daPyFlg1_UNK400);
    MtxP r25;
    r25 = mpCLModel->getAnmMtx(0xF);
    cXyz* sp18;
    sp18 = NULL;
    s16 r30;
    s16 r29;
    BOOL r28;
    r28 = false;
    mDoMtx_multVecSR(mpCLModel->getAnmMtx(0x1), &cXyz::BaseZ, &sp94);

    fopAc_ac_c* r24;
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e)) {
        r24 = fopAcM_getTalkEventPartner(this);
    } else {
        r24 = mpAttnActorLockOn;
    }
    if (r24 == NULL) {
        r24 = dCam_getBody()->GetForceLockOnActor();
    }

    fopAc_ac_c* r23_2;
    if (mpAttention->GetLockonList(0) != NULL) {
        r23_2 = mpAttention->GetLockonList(0)->getActor();
    } else {
        r23_2 = NULL;
    }

    if (dComIfGp_checkPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e)) {
        mDoMtx_multVec(mpCLModel->getAnmMtx(0x8), &l_tact_top, &spA0);
        sp18 = &spA0;
        r28 = true;
    } else if (mCurProc == daPyProc_CALL_e) {
        if (dComIfGp_getCb1Player() != NULL) {
            sp18 = &dComIfGp_getCb1Player()->eyePos;
            r28 = true;
        }
    } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && !checkShipNotNormalMode()) {
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e) && fopAcM_getTalkEventPartner(this) != NULL &&
            dComIfGp_getShipActor() != NULL && fopAcM_getTalkEventPartner(this) == dComIfGp_getShipActor() &&
            cLib_distanceAngleS(cLib_targetAngleY(&current.pos, &dComIfGp_getShipActor()->eyePos), m34DE) <= 0x6000)
        {
            sp18 = &dComIfGp_getShipActor()->eyePos;
            r28 = true;
        } else {
            spA0.set(r25[0][3] + 20000.0f * cM_ssin(m34DE), r25[1][3], r25[2][3] + 20000.0f * cM_scos(m34DE));
            sp18 = &spA0;
        }
    } else if (mCurProc == daPyProc_SHIP_CRANE_e) {
        if (m34D4 == 0 && dComIfGp_getShipActor() != NULL) {
            sp18 = dComIfGp_getShipActor()->m0434;
            r28 = true;
        }
    } else if (m_tex_anm_heap.mIdx == LKANM_BTP_TDASHKAZE) {
        if (checkHeavyStateOn() && m373C.abs2XZ() > SQUARE(5.0f)) {
            spA0.set(current.pos.x - 100.0f * m373C.x, 120.0f + current.pos.y, current.pos.z - 100.0f * m373C.z);
        } else if (!checkHeavyStateOn() && m3730.abs2XZ() > SQUARE(5.0f)) {
            spA0.set(current.pos.x - 100.0f * m3730.x, 120.0f + current.pos.y, current.pos.z - 100.0f * m3730.z);
        } else {
            spA0.set(
                current.pos.x - (100.0f * m3644) * cM_ssin(m3640),
                120.0f + current.pos.y,
                current.pos.z - (100.0f * m3644) * cM_scos(m3640)
            );
        }
        sp18 = &spA0;
        r28 = true;
    } else if (r24 != NULL && cLib_distanceAngleS(cLib_targetAngleY(&current.pos, &r24->eyePos), m34DE) <= 0x6000) {
        sp18 = &(r24->eyePos);
        r28 = true;
    } else if (checkModeFlg(ModeFlg_00000080 | ModeFlg_08000000)) {
        if (!dComIfGp_event_runCheck() || mDemo.getDemoMode() == daPy_demo_c::DEMO_RD_STOP_e) {
            if (dComIfGp_att_getLookTarget() != NULL) {
                sp18 = &dComIfGp_att_getLookTarget()->eyePos;
                r28 = true;
            } else if (
                checkAttentionPosAngle(r23_2, &sp18) ||
                checkAttentionPosAngle(mpAttnActorAction, &sp18) ||
                checkAttentionPosAngle(mpAttnActorX, &sp18) ||
                checkAttentionPosAngle(mpAttnActorY, &sp18) ||
                checkAttentionPosAngle(mpAttnActorZ, &sp18)
            ) {
                r28 = true;
            } else if (
                dComIfGp_getDetect().chk_attention(&spA0) &&
                cLib_distanceAngleS(cLib_targetAngleY(&current.pos, &spA0), m34DE) <= 0x6000
            ) {
                sp18 = &spA0;
                r28 = true;
            } else if (m34C3 == 10) {
                spA0.set(
                    current.pos.x - 10.0f * (m3730.x + m36B8.x),
                    120.0f + current.pos.y,
                    current.pos.z - 10.0f * (m3730.z + m36B8.z)
                );
                if (cLib_distanceAngleS(cLib_targetAngleY(&current.pos, &spA0), m34DE) <= 0x6000) {
                    sp18 = &spA0;
                    r28 = true;
                }
            }
        } else if (mCurProc == daPyProc_BOTTLE_OPEN_e) {
            r24 = mActorKeepRope.getActor();
            if (r24 != NULL) {
                sp18 = &(r24->eyePos);
                r28 = true;
            }
        } else {
            u32 mode = mDemo.getDemoMode();
            if (
                mCurProc == daPyProc_DEMO_LOOK_WAIT_e ||
                mode == daPy_demo_c::DEMO_INIT_WAIT_e ||
                mode == daPy_demo_c::DEMO_N_WAIT_e ||
                mode == daPy_demo_c::DEMO_N_WALK_e ||
                mode == daPy_demo_c::DEMO_N_DASH_e
            ) {
                r24 = getDemoLookActor();
                if (r24 != NULL) {
                    sp18 = &r24->eyePos;
                    r28 = true;
                }
            }
        }
    }

    mDoMtx_multVec(r25, &l_head_center_offset, &spC4);
    mDoMtx_multVec(r25, &l_eye_offset, &sp88);
    spAC = sp88 - spC4;

    s16 r23_3;
    s16 r24_2;
    s16 r27;
    s16 r25_2;
    s16 r23;
    s16 r4;
    r24_2 = cM_atan2s(-spAC.y, spAC.absXZ()) - m3564;
    r25_2 = (cM_atan2s(spAC.x, spAC.z) - m34DE) - m3566;
    if (checkModeFlg(ModeFlg_00000080 | ModeFlg_08000000) && sp18 != NULL && !checkUpperAnime(LKANM_BCK_DAMDASH)) {
        spB8 = *sp18 - spC4;
        r27 = cM_atan2s(-spB8.y, spB8.absXZ());
        r23_3 = cM_atan2s(spB8.x, spB8.z) - m34DE;
        if (spB8.absXZ() < 30.0f) {
            r23_3 = m3566;
        }
        if (r27 > 8000) {
            r27 = 8000;
        } else if (r27 < -10000) {
            r27 = -10000;
        }
        if (r23_3 > m_HIO->mShip.m.field_0x0) {
            r23_3 = m_HIO->mShip.m.field_0x0;
        } else if (r23_3 < -m_HIO->mShip.m.field_0x0) {
            r23_3 = -m_HIO->mShip.m.field_0x0;
        }
        if (checkModeFlg(ModeFlg_00000080) && m_anm_heap_upper[UPPER_MOVE0_e].mIdx != LKANM_BCK_DASHKAZE &&
            m_anm_heap_upper[UPPER_MOVE1_e].mIdx != LKANM_BCK_DASHKAZE)
        {
            if (r28) {
                r30 = (r27 >> 1) - r24_2;
                r29 = (r23_3 >> 1) - r25_2;
                r4 = r30;
                r23 = r29;
            } else {
                r4 = r27 - r24_2;
                r23 = r23_3 - r25_2;
            }
        } else {
            if (r28) {
                r30 = r27 - r24_2;
                r29 = r23_3 - r25_2;
            }
            r4 = 0;
            r23 = 0;
        }
    } else if (mCurProc == daPyProc_DAMAGE_e) {
        r4 = m3564;
        r23 = m3566;
    } else if ((mCurProc == daPyProc_LADDER_MOVE_e || mCurProc == daPyProc_CLIMB_MOVE_UP_DOWN_e) &&
               mDirection == DIR_FORWARD)
    {
        r4 = -0x1800;
        r23 = 0;
    } else if (mCurProc == daPyProc_CLIMB_MOVE_SIDE_e) {
        if (abs(m34D4) <= 0x4000) {
            r4 = -0x1800 * cM_scos(m34D4);
        } else {
            r4 = 0;
        }
        r23 = 0x1800 * cM_ssin(m34D4);
    } else if (m34C3 == 1 && m3580 != 8) {
        r28 = false;
        r4 = m34E2 >> 1;
        if (r4 > 8000) {
            r4 = 8000;
        } else if (r4 < -10000) {
            r4 = -10000;
        }
        r23 = 0;
    } else {
        r28 = false;
        r4 = 0;
        r23 = 0;
    }
    if (mCurProc == daPyProc_SHIP_CRANE_e) {
        r23 = 0;
        r29 = 0;
    }

    cLib_addCalcAngleS(&m3564, r4, 3, 0x1000, 0x100);
    cLib_addCalcAngleS(&m3566, r23, 3, 0x1000, 0x100);
    if (checkModeFlg(ModeFlg_00000080)) {
        s16 r4 = r25_2 + m3566;
        if (r4 > m_HIO->mShip.m.field_0x0) {
            m3566 = m_HIO->mShip.m.field_0x0 - r25_2;
        } else if (r4 < -m_HIO->mShip.m.field_0x0) {
            m3566 = -(m_HIO->mShip.m.field_0x0 + r25_2);
        }
    }
    if (mCurProc != daPyProc_DAMAGE_e) {
        cLib_addCalcAngleS(&m3568, 0, 3, 0x1000, 0x100);
    }

    f32 f31;
    f32 f30;
    f32 f29;
    if (r28 || mCurProc == daPyProc_FAN_GLIDE_e || mCurProc == daPyProc_ICE_SLIP_ALMOST_FALL_e ||
        mCurProc == daPyProc_CLIMB_MOVE_SIDE_e || m34C3 == 9 ||
        ((mCurProc == daPyProc_GRAB_HEAVY_WAIT_e || mCurProc == daPyProc_GRAB_WAIT_e || mCurProc == daPyProc_WAIT_e) &&
         m35A0 != 0.0f))
    {
        f32 f0;
        f32 f1;
        if (r28) {
            f1 = r29 / 8192.0f;
            f0 = r30 / 8192.0f;
        } else if (mCurProc == daPyProc_FAN_GLIDE_e) {
            cXyz sp58;
            sp58 = current.pos - old.pos;
            f0 = cM_scos(cM_atan2s(sp58.x, sp58.z) - shape_angle.y);
            f1 = -m34F4 / 6144.0f;
        } else if (mCurProc == daPyProc_ICE_SLIP_ALMOST_FALL_e) {
            s16 r0 = current.angle.y - shape_angle.y;
            f0 = std::abs(cM_scos(r0));
            f1 = cM_ssin(r0);
        } else if (mCurProc == daPyProc_CLIMB_MOVE_SIDE_e) {
            f0 = -cM_scos(m34D4);
            f1 = cM_ssin(m34D4);
        } else if (mCurProc == daPyProc_GRAB_HEAVY_WAIT_e || mCurProc == daPyProc_GRAB_WAIT_e ||
                   mCurProc == daPyProc_WAIT_e)
        {
            f0 = 0.0f;
            f1 = m35A0;
        } else {
            s16 r0 = cM_atan2s(m36A0.x, m36A0.z) - shape_angle.y;
            f0 = std::abs(cM_scos(r0));
            f1 = cM_ssin(r0);
        }
        f32 f6 = std::sqrtf(f1 * f1 + f0 * f0);
        if (f6 > 1.0f) {
            f32 f2 = 1.0f / f6;
            f0 = f0 * f2;
            f1 = f1 * f2;
        }
        if (f1 > 0.0f) {
            f31 = 0.12f * f1;
            f30 = -0.16f * f1;
        } else {
            f31 = 0.16f * f1;
            f30 = -0.12f * f1;
        }
        if (f0 > 0.0f) {
            f29 = f0 * -0.12f;
        } else {
            f29 = f0 * -0.07f;
        }
        daPy_matAnm_c::setMorfFrame(0);
        daPy_matAnm_c::onEyeMoveFlg();
    } else {
        f32 f1;
        f1 = m351C / 4096.0f;

        if (f1 > 1.0f) {
            f1 = 1.0f;
        } else if (f1 < -1.0f) {
            f1 = -1.0f;
        }
        if (!checkNoResetFlg1(daPyFlg1_CONFUSE) && !checkNoResetFlg1(daPyFlg1_UNK1000000) && m351C != 0) {
            if (m351C > 0) {
                f31 = -0.16f * f1;
                f30 = 0.12f * f1;
                daPy_matAnm_c::onEyeMoveFlg();
            } else {
                f31 = -0.12f * f1;
                f30 = 0.16f * f1;
                daPy_matAnm_c::onEyeMoveFlg();
            }
        } else {
            m_tex_eye_scroll[0]->setNowOffsetX(0.0f);
            m_tex_eye_scroll[1]->setNowOffsetX(0.0f);
            m_tex_eye_scroll[0]->setNowOffsetY(0.0f);
            m_tex_eye_scroll[1]->setNowOffsetY(0.0f);
            if (daPy_matAnm_c::getEyeMoveFlg() != 0) {
                daPy_matAnm_c::setMorfFrame(3);
            }
            daPy_matAnm_c::offEyeMoveFlg();
        }
        f29 = 0.0f;
    }
    if (daPy_matAnm_c::getEyeMoveFlg() != 0) {
        cLib_addCalc(&m_tex_eye_scroll[0]->mEyePos.x, f31, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&m_tex_eye_scroll[1]->mEyePos.x, f30, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(&m_tex_eye_scroll[0]->mEyePos.y, f29, 0.5f, 0.08f, 0.02f);
        m_tex_eye_scroll[1]->mEyePos.y = m_tex_eye_scroll[0]->mEyePos.y;
    }
}

/* 8011BE08-8011BEA4       .text checkOriginalHatAnimation__9daPy_lk_cFv */
void daPy_lk_c::checkOriginalHatAnimation() {
    if (
        checkModeFlg(ModeFlg_WHIDE | ModeFlg_SWIM | ModeFlg_CRAWL) ||
        mCurProc == daPyProc_VOMIT_WAIT_e ||
        mCurProc == daPyProc_ELEC_DAMAGE_e ||
        mCurProc == daPyProc_DEMO_DOOR_OPEN_e ||
        (!strcmp(dComIfGp_getStartStageName(), "GTower") && dComIfGp_getStartStageLayer() == 9)
    ) {
        onResetFlg0(daPyRFlg0_UNK800000);
    }
}

/* 8011BEA4-8011CBA4       .text setHatAngle__9daPy_lk_cFv */
void daPy_lk_c::setHatAngle() {
    if (m_old_fdata->getOldFrameFlg() == false || checkFreezeState()) {
        return;
    }

    cXyz spAC;
    cXyz spA0;
    cXyz sp94;
    cXyz sp88;
    cXyz sp7C;
    cXyz sp70;
    cXyz sp64;

    s16 r25;
    s16 r26;

    s16 r27;
    s16 r26_2;

    s16 r26_3;
    s16 r27_2;

    s16 r26_4;
    s16 r27_3;

    MtxP head_jnt_mtx = mpCLModel->getAnmMtx(0xF);
    BOOL r31 = dComIfGp_evmng_startCheck(l_tact_wind_change_event_label) ||
               dComIfGp_evmng_startCheck(l_tact_wind_change_event_label2) ||
               mCurProc == daPyProc_FAN_GLIDE_e ||
               mWindCyl.ChkTgHit();

    mDoMtx_multVec(head_jnt_mtx, &l_head_center_offset, &sp70);
    mDoMtx_multVec(head_jnt_mtx, &l_eye_offset, &sp64);
    cXyz sp58 = sp64 - sp70;
    s16 r3_3;
    r3_3 = cM_atan2s(sp58.x, sp58.z);
    if (sp70.y - head_jnt_mtx[1][3] < 0.0f) {
        r3_3 += 0x8000;
    }
    f32 f31;
    f31 = cM_ssin(r3_3);
    f32 f30;
    f30 = cM_scos(r3_3);
    MtxP hat_a_jnt_mtx = mpCLModel->getAnmMtx(0x1A);
    spA0.x = hat_a_jnt_mtx[0][3];
    spA0.y = hat_a_jnt_mtx[1][3];
    spA0.z = hat_a_jnt_mtx[2][3];
    f32 sp18;
    dKyw_get_AllWind_vec(&spA0, &spAC, &sp18);
    if (r31) {
        sp18 = 1.0f;
    }
    f32 f29 = (sp18 * sp18) * 25.0f;
    mDoMtx_multVecSR(mpCLModel->getAnmMtx(0xF), &l_neck_front, &sp88);
    mDoMtx_multVecSR(mpCLModel->getAnmMtx(0xF), &l_neck_top, &sp7C);

    r25 = m3528;
    r26 = m352A;
    if (sp7C.y < 0.0f) {
        m3528 = cM_atan2s(sp88.y, -sp88.absXZ());
        m352A = cM_atan2s(sp88.x, sp88.z) + 0x8000;
    } else {
        m3528 = cM_atan2s(sp88.y, sp88.absXZ());
        m352A = cM_atan2s(sp88.x, sp88.z);
    }
    if (std::abs(sp88.y) > 0.7f) {
        m352A = r26;
    }
    s16 r28_r29;
    r28_r29 = (s16)(m3528 - r25) >> 1;
    s16 r25_r28;
    r25_r28 = (s16)(m352A - r26) >> 1;
    if (r28_r29 > 0x200) {
        r28_r29 = 0x200;
    } else if (r28_r29 < -0x200) {
        r28_r29 = -0x200;
    }
    if (r25_r28 > 0x800) {
        r25_r28 = 0x800;
    } else if (r25_r28 < -0x800) {
        r25_r28 = -0x800;
    }
    sp94.x = m3718.x - spA0.x;
    sp94.y = (m3718.y - spA0.y) - 7.5f;
    sp94.z = m3718.z - spA0.z;
    if (!checkModeFlg(ModeFlg_WHIDE) || checkGrabWear()) {
        sp94 += spAC * f29;
    }
    if (std::abs(sp94.x) < 0.01f) {
        sp94.x = 0.0f;
    }
    if (std::abs(sp94.z) < 0.01f) {
        sp94.z = 0.0f;
    }
    r26_2 = m34F6;
    r27 = m34F8;
    f32 f28;
    f28 = (sp94.z * f30) + (sp94.x * f31);
    s16 r4_3;
    r4_3 = cM_atan2s(-f28, -sp94.y);
    if (m34F6 < 0) {
        r4_3 = 0x7800;
    } else if (r4_3 < 0x800 && -0x7800 < r4_3) {
        r4_3 = 0x800;
    } else if (0x7800 < r4_3 || r4_3 <= -0x7800) {
        r4_3 = 0x7800;
    }
    cLib_addCalcAngleS2(&m34F6, r4_3, 5, 0x400);
    m34F6 = m3502 + r28_r29 + m34F6;
    s16 r4_4 = m3528;
    s16 r0_2;
    r0_2 = m34F6 + -0x4000 + r4_4;
    if (r0_2 < -0x3000) {
        m34F6 = 0x1000 - r4_4;
    } else if (r0_2 > 0x3800) {
        m34F6 = 0x7800 - r4_4;
    }
    f32 f0_2 = std::sqrtf((f28 * f28) + sp94.y * sp94.y);
    s16 r4_5 = cM_atan2s(-((sp94.x * f30) - (sp94.z * f31)), f0_2);
    if (r4_5 > 0x3800) {
        r4_5 = 0x3800;
    } else if (r4_5 < -0x3800) {
        r4_5 = -0x3800;
    }
    cLib_addCalcAngleS2(&m34F8, r4_5, 5, 0x400);
    m34F8 = m34F8 + (m3504 - r25_r28);
    if (m34F8 > 0x3800) {
        m34F8 = 0x3800;
    } else if (m34F8 < -0x3800) {
        m34F8 = -0x3800;
    }
    m3502 = (s16)(m34F6 - r26_2) * 0.2f;
    m3504 = (s16)(m34F8 - r27) * 0.2f;
    s16 r3 = m34F6 - r26_2;
    s16 r4 = m34F8 - r27;
    m34FA -= r3;
    m34FC -= r4;
    r27_2 = m34FA;
    r26_3 = m34FC;
    cLib_addCalcAngleS2(&m34FA, 0, 5, 0x400);
    cLib_addCalcAngleS2(&m34FC, 0, 5, 0x400);
    m34FA = m3506 + r28_r29 + m34FA;
    m34FC = m34FC + (m3508 - r25_r28);
    if (m34FA > 0x1000) {
        m34FA = 0x1000;
    } else if (m34FA < -0x800) {
        m34FA = -0x800;
    }
    s16 r0 = m34FC + m34F8;
    if (r0 > 0x3800) {
        m34FC = 0x3800 - m34F8;
    } else if (r0 < -0x3800) {
        m34FC = -0x3800 - m34F8;
    }
    m3506 = (m34FA - r27_2) * 0.2f;
    m3508 = (m34FC - r26_3) * 0.2f;
    r3 = m34FA - r27_2;
    r4 = m34FC - r26_3;
    m34FE -= r3;
    m3500 -= r4;
    r27_3 = m34FE;
    r26_4 = m3500;
    cLib_addCalcAngleS2(&m34FE, 0, 5, 0x400);
    cLib_addCalcAngleS2(&m3500, 0, 5, 0x400);
    m34FE = m350A + r28_r29 + m34FE;
    m3500 = m3500 + (m350C - r25_r28);
    if (m34FE > 0x1000) {
        m34FE = 0x1000;
    } else if (m34FE < -0x800) {
        m34FE = -0x800;
    }
    s16 r4_6 = m3500 + m34FC + m34F8;
    if (r4_6 > 0x3800) {
        m3500 = (0x3800 - m34F8) - m34FC;
    } else if (r4_6 < -0x3800) {
        m3500 = (-0x3800 - m34F8) - m34FC;
    }
    m350A = (s16)((m34FE - r27_3) * 0.2f);
    m350C = (s16)((m3500 - r26_4) * 0.2f);
    f32 f28_2 = (f29 + (m3718.abs(spA0) * 0.65f)) / 30.0f;
    if (f28_2 > 1.0f) {
        f28_2 = 1.0f;
    }
    f32 f29_2;
    f29_2 = f28_2;
    if (r31 && !checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
        f28_2 = 3.5f;
        f29_2 = 1.0f;
        mDoAud_seStart(JA_SE_LK_HAT_SWING, &eyePos, 0, mReverb);
    }
    s16 r25_2 = (s16)(1500.0f + (4060.0f * f28_2));
    m3514 = m3514 + r25_2;
    f32 f0 = cM_scos(m3514);
    m350E = (s16)((2280.0f * f29_2) * f0);
    m3510 = (s16)((3908.0f * f29_2) * cM_scos(m3514 - 3.0f * r25_2));
    m3512 = (s16)((7568.0f * f29_2) * cM_scos(m3514 - 6.0f * r25_2));
    m3718 = spA0;
    if (checkModeFlg(ModeFlg_SWIM)) {
        m351A = 0;
        m3516 = 0;
        m3518 = 0;
    } else {
        f32 f5 = 0.5f + 0.25f * (1.0f + f0);
        cXyz sp4C;
        sp4C.x = (spAC.x * f30) - (spAC.z * f31);
        sp4C.z = (spAC.x * f31) + (spAC.z * f30);
        m3516 = (s16)(-8192.0f * sp4C.x * sp18 * f5);
        m3518 = m3516;
        m351A = (s16)(-8192.0f * sp4C.z * sp18 * f5);
        if (m3516 > 0x1000) {
            m3516 = 0x1000;
        } else if (m3518 < -0x1000) {
            m3518 = -0x1000;
        }
    }
}

/* 8011CBA4-8011CCF4       .text setMoveSlantAngle__9daPy_lk_cFv */
void daPy_lk_c::setMoveSlantAngle() {
    f32 fVar1 = std::abs(speedF / mMaxNormalSpeed);
    if (checkModeFlg(ModeFlg_02000000)) {
        mBodyAngle.z = 0;
        m351C = 0;
        return;
    }

    if (mCurProc == daPyProc_MOVE_e && fVar1 > m_HIO->mMove.m.field_0x4C) {
        cLib_addCalcAngleS(
            &m351C,
            m_HIO->mMove.m.field_0x50 * (s16)(m34DE - shape_angle.y) *
                ((fVar1 - m_HIO->mMove.m.field_0x4C) / (1.0f - m_HIO->mMove.m.field_0x4C)),
            m_HIO->mMove.m.field_0xC,
            m_HIO->mMove.m.field_0x8,
            m_HIO->mMove.m.field_0xA
        );
    } else {
        s16 sVar2 = m351C * m_HIO->mMove.m.field_0x54;
        if (sVar2 == 0) {
            m351C = 0;
        } else {
            m351C = m351C - sVar2;
        }
    }

    shape_angle.z = m351C >> 1;
    mBodyAngle.z = shape_angle.z;
}

/* 8011CCF4-8011CDB4       .text setWaistAngle__9daPy_lk_cFv */
void daPy_lk_c::setWaistAngle() {
    f32 fVar1;
    s16 sVar2;

    if (checkModeFlg(ModeFlg_00000001 | ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE |
                     ModeFlg_IN_SHIP | ModeFlg_00008000 | ModeFlg_CLIMB | ModeFlg_SWIM |
                     ModeFlg_LADDER | ModeFlg_CAUGHT))
    {
        sVar2 = 0;
    } else {
        fVar1 = std::abs(mVelocity / (mMaxNormalSpeed));
        if (fVar1 > 1.0f) {
            fVar1 = 1.0f;
        }
        if (m3580 == 8) {
            sVar2 = 0;
        } else {
            sVar2 = 0.7f * m34E2 * fVar1;
        }
    }
    cLib_addCalcAngleS(&m34E0, sVar2, 2, 0x800, 0x200);
}

/* 8011CDB4-8011D070       .text setWorldMatrix__9daPy_lk_cFv */
void daPy_lk_c::setWorldMatrix() {
    BOOL bVar1;
    daShip_c* ship;
    f32 dVar6;
    cXyz local_44;
    Mtx afStack_38;

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m35C4 + m3608, current.pos.z);
    ship = dComIfGp_getShipActor();
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && ship != NULL) {
        mDoMtx_stack_c::ZXYrotM(m353C, ship->shape_angle.y, m353E);
        mDoMtx_stack_c::YrotM(shape_angle.y - ship->shape_angle.y);
        mDoMtx_copy(mDoMtx_stack_c::get(), afStack_38);
        bVar1 = true;
    } else if (checkModeFlg(ModeFlg_CLIMB)) {
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
        mDoMtx_stack_c::transM(0.0f, 0.0f, 20.5f);
        mDoMtx_stack_c::YrotM(m34EC);
        mDoMtx_stack_c::transM(0.0f, 0.0f, -20.5f);
        bVar1 = false;
    } else {
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y + m34EC, shape_angle.z);
        bVar1 = false;
    }

    mpCLModel->setBaseScale(scale);
    mpCLModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::inverse();
    mDoMtx_copy(mDoMtx_stack_c::get(), m37B4);
    if (bVar1) {
        mDoMtx_stack_c::YrotS(-shape_angle.y);
        mDoMtx_stack_c::concat(afStack_38);
        mDoMtx_stack_c::multVecSR(&cXyz::BaseZ, &local_44);
        shape_angle.x = cM_atan2s(-local_44.y, local_44.z);
        mDoMtx_stack_c::multVecSR(&cXyz::BaseX, &local_44);
        dVar6 = std::sqrtf(local_44.y * local_44.y + local_44.z * local_44.z);
        if (local_44.y >= 0.0f) {
            shape_angle.z = cM_atan2s(dVar6, local_44.x);
        } else {
            shape_angle.z = cM_atan2s(-dVar6, local_44.x);
        }
    }
}

/* 8011D070-8011D0E4       .text setAtParam__9daPy_lk_cFUli11dCcG_At_SplUcUcUcf */
void daPy_lk_c::setAtParam(u32 type, int atp, dCcG_At_Spl spl, u8 se, u8 hitMark, u8 cutType, f32 radius) {
    dCcD_Cps* cps = mAtCps;
    if (type == AT_TYPE_SWORD && checkNoResetFlg1(daPyFlg1_SOUP_POWER_UP)) {
        atp *= 2;
    }
    if (type != AT_TYPE_SWORD) {
        mCutCount = 0;
    }
    for (int i = 0; i < ARRAY_SIZE(mAtCps); i++, cps++) {
        cps->SetAtType(type);
        cps->SetAtAtp(atp);
        cps->SetAtSpl(spl);
        cps->SetAtSe(se);
        cps->SetAtHitMark(hitMark);
        cps->SetR(radius);
    }
    mCutType = cutType;
    offResetFlg0(daPyRFlg0_UNK8000000);
    offNoResetFlg0(daPyFlg0_UNK10000000);
}

/* 8011D0E4-8011D110       .text resetCurse__9daPy_lk_cFv */
void daPy_lk_c::resetCurse() {
    if (daPy_dmEcallBack_c::checkCurse()) {
        endDamageEmitter();
    }
}

/* 8011D110-8011D4D0       .text checkLightHit__9daPy_lk_cFv */
void daPy_lk_c::checkLightHit() {
    static JGeometry::TVec3<f32> normal_scale(1.0f, 1.0f, 1.0f);
    static JGeometry::TVec3<f32> boss_scale(2.5f, 2.5f, 2.5f);
    BOOL lightHit = FALSE;
    cXyz lightVec;

    if (dComIfGp_getDetect().chk_light(&current.pos)) {
        lightHit = TRUE;
        resetCurse();
    } else {
        lightHit = FALSE;
    }
    if (dComIfGs_getSelectEquip(1) == dItem_MIRROR_SHIELD_e) {
        mDoMtx_multVecSR(mpEquippedShieldModel->getBaseTRMtx(), &l_ms_light_local_vec, &lightVec);
        if (lightHit) {
            onResetFlg0(daPyRFlg0_UNK200000);
        } else if (mLightCyl.ChkTgHit() && mLightCyl.GetTgRVecP()->inprod(lightVec) < 0.0f) {
            onResetFlg0(daPyRFlg0_UNK200000);
        }
        if (mFanLightCps.ChkAtHit()) {
            if (m3438.getEmitter() == NULL) {
                dComIfGp_particle_setP1(dPa_name::ID_SCENE_8232, &current.pos, NULL, NULL, 0xFF,
                                        &m3438);
            }
            cM3d_lineVsPosSuisenCross(mFanLightCps.GetStart(), mFanLightCps.GetEnd(),
                                      *mFanLightCps.GetAtHitPosP(), &m3438.getPos());
            s16 angleY = cM_atan2s(lightVec.x, lightVec.z);
            m3438.setAngle(cM_atan2s(-lightVec.y, lightVec.absXZ()), angleY, 0);
            if (m3438.getEmitter() != NULL) {
                if (mFanLightCps.GetAtHitAc() != 0 &&
                    (fopAcM_GetName(mFanLightCps.GetAtHitAc()) == PROC_BPW))
                {
                    m3438.getEmitter()->setGlobalScale(boss_scale);
                } else {
                    m3438.getEmitter()->setGlobalScale(normal_scale);
                }
            }
        } else {
            m3438.end();
        }
    } else {
        m3438.end();
    }
    if (checkResetFlg0(daPyRFlg0_UNK200000)) {
        if (!mFanLightCps.ChkAtSet()) {
            seStartOnlyReverb(JA_SE_OBJ_MIRROR_REFLECT);
        } else {
            seStartOnlyReverb(JA_SE_OBJ_MIRROR_LIGHT);
        }
        resetCurse();
    }
    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e) &&
        checkResetFlg0(daPyRFlg0_UNK200000))
    {
        if (m342C.getEmitter() == NULL) {
            m342C.makeEmitter(dPa_name::ID_SCENE_8226, mpEquippedShieldModel->getBaseTRMtx(),
                              &current.pos, NULL);
        }
    } else if (m342C.getEmitter() != NULL) {
        m342C.getEmitter()->setGlobalAlpha(0);
        m342C.end();
    }
}

/* 8011D4D0-8011D6C4       .text setSwordAtCollision__9daPy_lk_cFv */
void daPy_lk_c::setSwordAtCollision() {
    cXyz local_34;
    cXyz local_58;
    cXyz local_7c;

    if (mEquipItem == daPyItem_SWORD_e) {
        local_34 = ((mSwordTopPos - m36C4) * m35FC) + m36C4;
        local_58 = ((m36D0 - m36DC) * m35FC) + m36DC;
    } else {
        local_34 = mSwordTopPos;
        local_58 = m36D0;
    }
    mAtCps[0].SetStartEnd(m36C4, local_34);
    mAtCps[1].SetStartEnd(local_58, local_34);
    mAtCps[2].SetStartEnd(m36C4, local_58);
    if (checkResetFlg0(daPyRFlg0_UNK1)) {
        local_7c = cXyz::Zero;
    } else {
        local_7c = mSwordTopPos - m36D0;
    }
    mAtCps[0].SetAtVec(local_7c);
    mAtCps[1].SetAtVec(local_7c);
    mAtCps[2].SetAtVec(local_7c);
}

/* 8011D6C4-8011D788       .text getBlurTopRate__9daPy_lk_cFv */
f32 daPy_lk_c::getBlurTopRate() {
    if (mCurProc == daPyProc_DEMO_LAST_COMBO_e) {
        return 0.0f;
    }
    
    if (mEquipItem == daPyItem_SWORD_e) {
        if (checkNormalSwordEquip()) {
            return 0.5f;
        } else {
            return 1.0f;
        }
    }
    
    if (mEquipItem == daPyItem_BOKO_e) {
        if (mActorKeepEquip.getActor() == NULL) {
            return 0.0f;
        }
        daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
        if (mCurProc == daPyProc_JUMP_CUT_e || mCurProc == daPyProc_JUMP_CUT_LAND_e) {
            return boko->getJumpBlurRate();
        } else {
            return boko->getBlurRate();
        }
    }
    
    return 0.0f;
}

/* 8011D788-8011EC0C       .text setCollision__9daPy_lk_cFv */
void daPy_lk_c::setCollision() {
    MtxP link_root_mtx = mpCLModel->getAnmMtx(0x00);
    MtxP ltoe_jnt_mtx = mpCLModel->getAnmMtx(0x23);
    MtxP rtoe_jnt_mtx = mpCLModel->getAnmMtx(0x28);
    cXyz spD0;
    spD0.x = 0.5f * (link_root_mtx[0][3] + mpCLModel->getAnmMtx(0xE)[0][3]);
    spD0.z = 0.5f * (link_root_mtx[2][3] + mpCLModel->getAnmMtx(0xE)[2][3]);
    if (mCurProc == daPyProc_JUMP_CUT_e) {
        spD0.x -= 15.0f * cM_ssin(shape_angle.y);
        spD0.z -= 15.0f * cM_scos(shape_angle.y);
    }
    if (checkGrabWear()) {
        mCyl.SetR(50.0f);
    } else {
        mCyl.SetR(30.0f);
    }
    if (checkModeFlg(ModeFlg_IN_SHIP)) {
        mCyl.OnCoSPrmBit(cCcD_CoSPrm_NoCrr_e);
    } else {
        mCyl.OffCoSPrmBit(cCcD_CoSPrm_NoCrr_e);
    }
    if (checkModeFlg(ModeFlg_CRAWL)) {
        f32 fVar3 = cM_ssin(shape_angle.x);
        if (fVar3 >= 0.0f) {
            spD0.y = current.pos.y - 50.0f * fVar3;
            mCyl.SetH(50.0f + (35.0f * fVar3));
        } else {
            spD0.y = current.pos.y + 25.0f * fVar3;
            mCyl.SetH(50.0f - (65.0f * fVar3));
        }
    } else if (mCurProc == daPyProc_FRONT_ROLL_e) {
        spD0.y = current.pos.y;
        mCyl.SetH(81.25f);
    } else if (mCurProc == daPyProc_BACK_JUMP_e) {
        spD0.y = 30.0f + current.pos.y;
        mCyl.SetH(81.25f);
    } else if (mCurProc == daPyProc_BT_JUMP_CUT_e || (mCurProc == daPyProc_BT_JUMP_e && speed.y <= 0.0f)) {
        spD0.y = link_root_mtx[1][3];
        mCyl.SetH(125.0f - (spD0.y - current.pos.y));
        mCyl.SetR(22.5f);
    } else {
        if (mCurProc == daPyProc_ROPE_SWING_e) {
            spD0.y = (ltoe_jnt_mtx[1][3] > link_root_mtx[1][3]) ? link_root_mtx[1][3] : ltoe_jnt_mtx[1][3];
        } else {
            spD0.y = (ltoe_jnt_mtx[1][3] > rtoe_jnt_mtx[1][3]) ? rtoe_jnt_mtx[1][3] : ltoe_jnt_mtx[1][3];
        }
        mCyl.SetH(40.1f + (mpCLModel->getAnmMtx(0xE)[1][3] - spD0.y));
    }
    mCyl.SetC(spD0);
    if (checkModeFlg(ModeFlg_DAMAGE) || checkGuardSlip() || mCurProc == daPyProc_VOMIT_WAIT_e || mDamageWaitTimer != 0)
    {
        mCyl.OffTgSetBit();
        mCyl.ClrTgHit();
    } else if (mDamageWaitTimer == 0) {
        mCyl.OnTgSetBit();
    }
    dComIfG_Ccsp()->Set(&mCyl);
    dComIfG_Ccsp()->SetMass(&mCyl, 1);
    mWindCyl.SetC(spD0);
    mWindCyl.SetH(mCyl.GetH());
    mWindCyl.SetR(mCyl.GetR());
    dComIfG_Ccsp()->Set(&mWindCyl);
    mLightCyl.SetC(spD0);
    mLightCyl.SetH(mCyl.GetH());
    mLightCyl.SetR(mCyl.GetR());
    dComIfG_Ccsp()->Set(&mLightCyl);

    cXyz spC4;
    cXyz spB8;
    if (checkResetFlg0(daPyRFlg0_UNK2)) {
        if (checkResetFlg0(daPyRFlg0_UNK1)) {
            setCutWaterSplash();
            if (mCurProc == daPyProc_CUT_TURN_e || mCurProc == daPyProc_CUT_ROLL_e) {
                mAtCyl.StartCAt(current.pos);
            } else {
                setSwordAtCollision();
            }
            onNoResetFlg0(daPyFlg0_CUT_AT_FLG);
            if (mpCutfBrk != NULL) {
                if (checkModeFlg(ModeFlg_PARRY)) {
                    mpCutfBrk->setFrame(2.0f);
                } else if (checkNoResetFlg1(daPyFlg1_SOUP_POWER_UP)) {
                    mpCutfBrk->setFrame(1.0f);
                } else {
                    mpCutfBrk->setFrame(0.0f);
                }
            }
            if (mCurProc != daPyProc_CUT_F_e && mCurProc != daPyProc_BT_VERTICAL_JUMP_CUT_e &&
                mCurProc != daPyProc_FAN_SWING_e)
            {
                int iVar12;
                if ((mCurProc == daPyProc_HAMMER_FRONT_SWING_e) || (mCurProc == daPyProc_WEAPON_FRONT_SWING_e)) {
                    iVar12 = 2.5f * mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
                } else {
                    iVar12 = 10.0f * mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
                }
                mSwBlur.initSwBlur(mpCLModel->getBaseTRMtx(), iVar12, getBlurTopRate(), getSwordBlurColor());
                if (mCurProc == daPyProc_CUT_TURN_e || mCurProc == daPyProc_CUT_ROLL_e) {
                    static const GXColor n_roll_prm0 = {0xC8, 0xFF, 0x40, 0xFF};
                    static const GXColor n_roll_prm1 = {0xFF, 0xFF, 0xDC, 0xFF};
                    static const GXColor n_roll_env = {0xC8, 0xFF, 0x78, 0xFF};
                    static const GXColor nm_roll_prm0 = {0xC8, 0xFF, 0x40, 0xFF};
                    static const GXColor nm_roll_prm1 = {0xFF, 0xFF, 0xDC, 0xFF};
                    static const GXColor nm_roll_env = {0xC8, 0xFF, 0x78, 0xFF};
                    static const GXColor fm_roll_prm0 = {0xC8, 0xFF, 0x40, 0xFF};
                    static const GXColor fm_roll_prm1 = {0xFF, 0xFF, 0xDC, 0xFF};
                    static const GXColor fm_roll_env = {0xC8, 0xFF, 0x78, 0xFF};
                    static const GXColor n_turn_prm0 = {0x40, 0x60, 0x40, 0xFF};
                    static const GXColor n_turn_prm1 = {0xDC, 0xE6, 0xDC, 0xFF};
                    static const GXColor n_turn_env = {0xA0, 0xE6, 0xA0, 0xFF};
                    static const GXColor nm_turn_prm0 = {0x40, 0x40, 0x60, 0xFF};
                    static const GXColor nm_turn_prm1 = {0xDC, 0xDC, 0xE6, 0xFF};
                    static const GXColor nm_turn_env = {0xA0, 0xA0, 0xE6, 0xFF};
                    static const GXColor fm_turn_prm0 = {0x40, 0x40, 0xFF, 0xFF};
                    static const GXColor fm_turn_prm1 = {0xDC, 0xDC, 0xFF, 0xFF};
                    static const GXColor fm_turn_env = {0x78, 0x78, 0xFF, 0xFF};
                    const GXColor* prm0;
                    const GXColor* prm1;
                    const GXColor* env;
                    f32 dVar27;
                    if (mEquipItem == daPyItem_BOKO_e) {
                        u32 uVar6;
                        if (mActorKeepEquip.getActor() == NULL) {
                            uVar6 = 0;
                        } else {
                            uVar6 = fopAcM_GetParam(mActorKeepEquip.getActor());
                        }
                        if (uVar6 == 0) {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x48;
                        } else if (uVar6 == 1) {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x4C;
                        } else if (uVar6 == 2) {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x50;
                        } else if (uVar6 == 3) {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x54;
                        } else if (uVar6 == 4) {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x58;
                        } else {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x5C;
                        }
                        dVar27 *= 1.5f;
                        prm0 = &nm_turn_prm0;
                        prm1 = &nm_turn_prm1;
                        env = &nm_turn_env;
                    } else if (mCurProc == daPyProc_CUT_ROLL_e || checkNoResetFlg1(daPyFlg1_SOUP_POWER_UP)) {
                        if (checkNormalSwordEquip()) {
                            if (mCurProc == daPyProc_CUT_ROLL_e) {
                                dVar27 = m_HIO->mCut.mCutRoll.m.field_0x18;
                            } else {
                                dVar27 = m_HIO->mCut.mCutTurn.m.field_0x38;
                            }
                            prm0 = &n_roll_prm0;
                            prm1 = &n_roll_prm1;
                            env = &n_roll_env;
                        } else if (checkFinalMasterSwordEquip()) {
                            if (mCurProc == daPyProc_CUT_ROLL_e) {
                                dVar27 = m_HIO->mCut.mCutRoll.m.field_0x1C;
                            } else {
                                dVar27 = m_HIO->mCut.mCutTurn.m.field_0x3C;
                            }
                            prm0 = &fm_roll_prm0;
                            prm1 = &fm_roll_prm1;
                            env = &fm_roll_env;
                        } else {
                            if (mCurProc == daPyProc_CUT_ROLL_e) {
                                dVar27 = m_HIO->mCut.mCutRoll.m.field_0x1C;
                            } else {
                                dVar27 = m_HIO->mCut.mCutTurn.m.field_0x3C;
                            }
                            prm0 = &nm_roll_prm0;
                            prm1 = &nm_roll_prm1;
                            env = &nm_roll_env;
                        }
                    } else {
                        if (checkNormalSwordEquip()) {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x38;
                            prm0 = &n_turn_prm0;
                            prm1 = &n_turn_prm1;
                            env = &n_turn_env;
                        } else if (checkFinalMasterSwordEquip()) {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x3C;
                            prm0 = &fm_turn_prm0;
                            prm1 = &fm_turn_prm1;
                            env = &fm_turn_env;
                        } else {
                            dVar27 = m_HIO->mCut.mCutTurn.m.field_0x3C;
                            prm0 = &nm_turn_prm0;
                            prm1 = &nm_turn_prm1;
                            env = &nm_turn_env;
                        }
                    }
                    JPABaseEmitter* emitter1 = dComIfGp_particle_setP1(
                        dPa_name::ID_COMMON_0025,
                        &current.pos,
                        &shape_angle,
                        NULL,
                        0xFF,
                        &m331C,
                        fopAcM_GetRoomNo(this),
                        prm0,
                        env,
                        NULL
                    );
                    JPABaseEmitter* emitter2 = dComIfGp_particle_setP1(
                        dPa_name::ID_COMMON_0026,
                        &current.pos,
                        &shape_angle,
                        NULL,
                        0xFF,
                        &m332C,
                        fopAcM_GetRoomNo(this),
                        prm1,
                        env,
                        NULL
                    );
                    JPABaseEmitter* emitter3 = dComIfGp_particle_setP1(
                        dPa_name::ID_COMMON_0028,
                        &current.pos,
                        &shape_angle,
                        NULL,
                        0xFF,
                        &m333C,
                        fopAcM_GetRoomNo(this),
                        prm0,
                        env,
                        NULL
                    );
                    if (emitter1 != NULL) {
                        emitter1->mGlobalParticleScale.x = dVar27;
                    }
                    if (emitter2 != NULL) {
                        emitter2->mGlobalParticleScale.x = dVar27;
                    }
                    if (emitter3 != NULL) {
                        emitter3->mGlobalParticleScale.x = dVar27;
                    }
                }
            }
        } else if (mCurProc == daPyProc_CUT_ROLL_e) {
            cXyz* pcVar23 = &mSwBlur.field_0x304[0];
            s16 r27 = m_HIO->mCut.mCutRoll.m.field_0x4 / 10;
            cXyz spAC = (old.pos - current.pos) * 0.1f;
            mDoMtx_stack_c::copy(mpCLModel->getBaseTRMtx());
            mDoMtx_stack_c::push();
            mDoMtx_stack_c::inverse();
            cXyz spA0;
            mDoMtx_stack_c::multVec(&m36C4, &spA0);
            mDoMtx_stack_c::pop();
            for (int i = 0; i < 10; i++, pcVar23++) {
                mDoMtx_stack_c::multVec(&spA0, pcVar23);
                *pcVar23 += spAC * i;
                mDoMtx_stack_c::YrotM(r27);
            }
            mDoMtx_stack_c::copy(mpCLModel->getBaseTRMtx());
            mDoMtx_stack_c::YrotM(-(r27 >> 1));
            mDoMtx_stack_c::multVec(&spA0, &spB8);
            if (m331C.getAlpha() == 0xFF) {
                m331C.setPosArray(&mSwBlur.field_0x304[0], 10);
                m332C.setPosArray(&mSwBlur.field_0x304[0], 10);
                m333C.setPosArray(&mSwBlur.field_0x304[0], 10);
            }
            mAtCyl.MoveCAt(current.pos);
            seStartSwordCut(JA_SE_LK_SUGOI_KAITEN);
        } else {
            int r26 = mSwBlur.field_0x018;
            int r23 = (int)(10.0f * mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
            if (mCurProc != daPyProc_CUT_F_e && mCurProc != daPyProc_BT_VERTICAL_JUMP_CUT_e &&
                mCurProc != daPyProc_FAN_SWING_e)
            {
                if (mCurProc == daPyProc_JUMP_CUT_LAND_e) {
                    r23 = 0x95;
                } else if ((mCurProc == daPyProc_HAMMER_FRONT_SWING_e) || (mCurProc == daPyProc_WEAPON_FRONT_SWING_e)) {
                    r23 = (int)(2.5f * mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
                } else if (mCurProc == daPyProc_WEAPON_SIDE_SWING_e) {
                    r23 = (int)(10.0f * mFrameCtrlUnder[UNDER_MOVE0_e].getFrame()) + -5;
                }
                mSwBlur.copySwBlur(mpCLModel->getBaseTRMtx(), r23);
            }
            if (mCurProc == daPyProc_CUT_TURN_e) {
                mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &mSwBlur.mpPosBuffer[r23 * 2 + 3], &spB8);
                mAtCyl.MoveCAt(current.pos);
                if (m331C.getAlpha() == 0xFF) {
                    s16 sVar16 = mSwBlur.field_0x018 - r26;
                    m331C.setPosArray(&mSwBlur.field_0x304[0], sVar16);
                    m332C.setPosArray(&mSwBlur.field_0x304[0], sVar16);
                    m333C.setPosArray(&mSwBlur.field_0x304[0], sVar16);
                }
                mSwBlur.field_0x014 = 0;
            } else {
                setSwordAtCollision();
            }
        }

        if (mCurProc == daPyProc_CUT_TURN_e || mCurProc == daPyProc_CUT_ROLL_e) {
            mDoAud_bgmNowKaitengiri();
            mAtCyl.OnAtSetBit();
            mAtCps[0].OffAtSetBit();
            mAtCps[1].OffAtSetBit();
            mAtCps[2].OffAtSetBit();
        } else {
            mAtCyl.OffAtSetBit();
            mAtCps[0].OnAtSetBit();
            if (checkResetFlg0(daPyRFlg0_UNK1)) {
                mAtCps[1].OffAtSetBit();
                mAtCps[2].OffAtSetBit();
            } else {
                mAtCps[1].OnAtSetBit();
                mAtCps[2].OnAtSetBit();
            }
        }
        dComIfG_Ccsp()->Set(&mAtCyl);
        dComIfG_Ccsp()->SetMass(&mAtCyl, 1);
        int i;
        dCcD_Cps* pdVar21 = &mAtCps[0];
        for (i = 0; i < 3; i++, pdVar21++) {
            dComIfG_Ccsp()->Set(pdVar21);
            dComIfG_Ccsp()->SetMass(pdVar21, 1);
        }
    } else {
        if (mSwBlur.field_0x014 < 10) {
            mSwBlur.field_0x014 = 0;
        } else {
            mSwBlur.field_0x014 += -10;
        }
        if (mCurProc == daPyProc_BOTTLE_OPEN_e && m34D6 != 0) {
            mAtCps[0].OnAtSetBit();
            dComIfG_Ccsp()->Set(&mAtCps[0]);
            if (m34D4 != 0) {
                mAtCps[1].OnAtSetBit();
                dComIfG_Ccsp()->Set(&mAtCps[1]);
            } else {
                mAtCps[1].OffAtSetBit();
            }
        } else {
            int i;
            dCcD_Cps* pdVar21 = &mAtCps[0];
            for (i = 0; i < 3; i++, pdVar21++) {
                pdVar21->ResetAtHit();
                pdVar21->OffAtSetBit();
            }
        }
        mAtCyl.ResetAtHit();
        mAtCyl.OffAtSetBit();
        offNoResetFlg0(daPyFlg0_CUT_AT_FLG);
        m331C.remove();
        m332C.remove();
        m333C.remove();
    }
    if (fanWindCrashEffectDraw()) {
        f32 fVar3 = mpYbafo00Btk->getFrame() + 1.0f;
        if (fVar3 > mpYbafo00Btk->getFrameMax() - 0.5f) {
            fVar3 = mpYbafo00Btk->getFrameMax() - 0.001f;
        }
        mpYbafo00Btk->setFrame(fVar3);
    }

    BOOL bVar5 = false;
    cXyz sp94;
    cXyz sp88;
    f32 in_f31;
    if ((int)m3534 != 0) {
        sp94.x = mFanWindCps.GetEndP()->x;
        sp94.y = mFanWindCps.GetEndP()->y;
        sp94.z = mFanWindCps.GetEndP()->z;
        f32 dVar27 = m3534 / 10.0f;
        f32 fVar4 =
            (dVar27 * (m_HIO->mItem.mFan.m.field_0x18 - m_HIO->mItem.mFan.m.field_0x1C) + m_HIO->mItem.mFan.m.field_0x1C);
        spC4.set(
            fVar4 * cM_ssin(m3536) * cM_scos(m3538), -fVar4 * cM_ssin(m3538), fVar4 * cM_scos(m3536) * cM_scos(m3538)
        );
        sp88 = sp94 + spC4;
        mArrowLinChk.Set(&sp94, &sp88, this);
        if (dComIfG_Bgsp()->LineCross(&mArrowLinChk)) {
            cM3dGPla* pfVar15 = dComIfG_Bgsp()->GetTriPla(mArrowLinChk);
            sp88.set(*mArrowLinChk.GetCrossP());
            if (!cBgW_CheckBGround(pfVar15->GetNP()->y)) {
                m3534 = 0;
                m33E8.end();
                mpYuchw00Brk->setFrame(mpYuchw00Brk->getFrameMax() - 0.001f);
                mpYbafo00Btk->setFrame(0.0f);
                mDoMtx_stack_c::transS(sp88.x, sp88.y, sp88.z);
                mDoMtx_stack_c::ZXYrotM(
                    cM_atan2s(-pfVar15->GetNP()->y, pfVar15->GetNP()->absXZ()),
                    cM_atan2s(-pfVar15->GetNP()->x, -pfVar15->GetNP()->z),
                    0
                );
                mpYbafo00Model->setBaseTRMtx(mDoMtx_stack_c::get());
                JPABaseEmitter* emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0049, &sp88);
                if (emitter != NULL) {
                    emitter->setGlobalRTMatrix(mDoMtx_stack_c::get());
                    emitter->setGlobalPrmColor(tevStr.mColorK0.r, tevStr.mColorK0.g, tevStr.mColorK0.b);
                }
            } else {
                sp88.y += 70.0f;
                m3538 = getGroundAngle(&mArrowLinChk, m3536);
            }
        }
        bVar5 = true;
        in_f31 = (70.0f + (230.0f * (1.0f - dVar27)));
        if ((int)m3534 != 0) {
            m3534--;
            mDoMtx_stack_c::transS(sp88.x, sp88.y, sp88.z);
            mDoMtx_stack_c::ZXYrotM(m3538, m3536, 0);
            mpYuchw00Model->setBaseTRMtx(mDoMtx_stack_c::get());
            mYuchw00Bck.play();
            mYuchw00Bck.entry(mpYuchw00Model->getModelData());
            simpleAnmPlay(mpYuchw00Btk);
        }
    } else if (fanWindEffectDraw()) {
        mYuchw00Bck.play();
        mYuchw00Bck.entry(mpYuchw00Model->getModelData());
        simpleAnmPlay(mpYuchw00Btk);
        f32 dVar27 = (1.0f + mpYuchw00Brk->getFrame());
        if (dVar27 > (mpYuchw00Brk->getFrameMax() - 0.5f)) {
            dVar27 = (mpYuchw00Brk->getFrameMax() - 0.001f);
            m33E8.end();
        }
        mpYuchw00Brk->setFrame(dVar27);
    } else {
        if (mpYbafo00Btk->getFrame() < 5.0f) {
            mDoMtx_multVecZero(mpYbafo00Model->getBaseTRMtx(), &sp94);
            sp88.set(
                sp94.x,
                10.0f + sp94.y,
                sp94.z
            );
            spC4 = cXyz::Zero;
            bVar5 = true;
            in_f31 = 120.0f;
        }
    }

    if (bVar5) {
        mFanWindCps.SetStartEnd(sp94, sp88);
        mFanWindCps.SetAtVec(spC4);
        mFanWindCps.SetR(in_f31);
        dComIfG_Ccsp()->Set(&mFanWindCps);
        dComIfG_Ccsp()->SetMass(&mFanWindCps, 1);
    } else {
        mFanWindCps.ResetAtHit();
    }
    if (fanWindEffectDraw()) {
        mDoAud_seStart(JA_SE_LK_FAN_WIND, mFanWindCps.GetEndP(), 0, mReverb);
    }
    if (m353A != 0) {
        if (mCurProc == daPyProc_FAN_GLIDE_e) {
            cXyz local_10c;
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0), &local_10c);
            mFanWindSph.SetC(local_10c);
        } else {
            mFanWindSph.SetC(current.pos);
        }
        dComIfG_Ccsp()->Set(&mFanWindSph);
        dComIfG_Ccsp()->SetMass(&mFanWindSph, 1);
        m353A--;
    } else {
        mFanWindSph.ResetAtHit();
    }
    if (checkResetFlg0(daPyRFlg0_UNK200000)) {
        mDoMtx_multVec(mpEquippedShieldModel->getBaseTRMtx(), &l_ms_light_local_start, &sp94);
        cXyz local_118;
        mDoMtx_multVecSR(mpEquippedShieldModel->getBaseTRMtx(), &l_ms_light_local_vec, &local_118);
        sp88 = sp94 + local_118;
        mMirLightLinChk.Set(&sp94, &sp88, this);
        if (dComIfG_Bgsp()->LineCross(&mMirLightLinChk)) {
            sp88.set(*mMirLightLinChk.GetCrossP());
            local_118 = sp88 - sp94;
        }
        mFanLightCps.SetStartEnd(sp94, sp88);
        mFanLightCps.SetAtVec(local_118);
        mFanLightCps.OnAtSetBit();
        dComIfG_Ccsp()->Set(&mFanLightCps);
        dComIfG_Ccsp()->SetMass(&mFanLightCps, 1);
    } else {
        mFanLightCps.ResetAtHit();
        mFanLightCps.OffAtSetBit();
    }
}

/* 8011EC0C-8011EEBC       .text setAttentionPos__9daPy_lk_cFv */
void daPy_lk_c::setAttentionPos() {
    cXyz* pcVar3;
    cXyz afStack_18;

    attention_info.position.x = current.pos.x;
    attention_info.position.z = current.pos.z;
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if (checkModeFlg(ModeFlg_CRAWL)) {
        {
            static const Vec offset = {0.0f, 30.0f, 20.0f};
            mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &offset, &attention_info.position);
        }
    } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e)) {
        {
            static const Vec offset = {0.0f, 70.0f, 0.0f};
            mDoMtx_stack_c::ZXYrotS(mBodyAngle.x, shape_angle.y, 0);
            mDoMtx_stack_c::multVec(&offset, &afStack_18);
            attention_info.position.y = 26.3f + current.pos.y;
            pcVar3 = &attention_info.position;
            *pcVar3 += afStack_18;
        }
    } else if (checkModeFlg(ModeFlg_CROUCH)) {
        attention_info.position.x += 20.0f * cM_ssin(shape_angle.y);
        attention_info.position.y = 46.25f + current.pos.y;
        attention_info.position.z += 20.0f * cM_scos(shape_angle.y);
    } else if (checkModeFlg(ModeFlg_ROPE)) {
        attention_info.position = current.pos;
    } else if (checkModeFlg(ModeFlg_HANG)) {
        attention_info.position.y = 92.5f + mCyl.GetCP()->y;
    } else if (checkModeFlg(ModeFlg_SWIM)) {
        attention_info.position.y = 20.05f + current.pos.y;
    } else if (checkModeFlg(ModeFlg_WHIDE) && checkNoResetFlg0(daPyFlg0_UNK10000)) {
        attention_info.position.y = (92.5f + mpCLModel->getBaseTRMtx()[1][3]) - 30.0f;
    } else if (checkModeFlg(ModeFlg_IN_SHIP) && ship != NULL && !ship->getFlyFlg()) {
        // !@bug(?): l_ship_offset is probably supposed to be x, not z.
        attention_info.position.x = ship->current.pos.x + cM_ssin(ship->shape_angle.y) * l_ship_offset.z;
        if (checkNoResetFlg0(daPyFlg0_UNK80)) {
            attention_info.position.y = 92.5f + (m35D0 + l_ship_offset.y);
        } else {
            attention_info.position.y = 92.5f + mpCLModel->getBaseTRMtx()[1][3];
        }
        attention_info.position.z = ship->current.pos.z + cM_scos(ship->shape_angle.y) * l_ship_offset.z;
        return;
    } else {
        attention_info.position.y = 92.5f + mpCLModel->getBaseTRMtx()[1][3];
    }
}

/* 8011EEBC-8011EF94       .text setRoomInfo__9daPy_lk_cFv */
int daPy_lk_c::setRoomInfo() {
    int sVar5 = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
    tevStr.mRoomNo = sVar5;
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
    mReverb = dComIfGp_getReverb(sVar5);
    mStts.SetRoomId(sVar5);
    current.roomNo = sVar5;
    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SEA_e) {
        if (dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd)) {
            mRestartPoint = 0;
        } else {
            mRestartPoint = dComIfG_Bgsp()->GetLinkNo(mAcch.m_gnd);
        }
    } else {
        mRestartPoint = 0xFF;
    }
    return sVar5;
}

/* 8011EF94-8011F9C0       .text setDemoData__9daPy_lk_cFv */
void daPy_lk_c::setDemoData() {
    dDemo_actor_c* demo_actor_p = dComIfGp_demo_getActor(demoActorID);
    cXyz* pos_p = NULL;
    s16 angle;
    u32 demo_mode = daPy_demo_c::DEMO_N_WAIT_e;
    int* prm0_p = NULL;
    int* prm1_p = NULL;
    if (!dComIfGp_event_runCheck()) {
        if (checkPlayerDemoMode()) {
            endDemoMode();
        }
        if (m3554 > 0) {
            m3554--;
        } else {
            offNoResetFlg1(daPyFlg1_FOREST_WATER_USE);
        }
        return;
    }
    dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
    if (dComIfGp_event_chkEventFlag(0x20) == 0) {
        if (mCurProc == daPyProc_SCOPE_e) {
            procWait_init();
        } else if (mCurProc == daPyProc_SHIP_SCOPE_e) {
            procShipPaddle_init();
        }
    }
    if (mCurProc == daPyProc_SUBJECTIVITY_e) {
        procWait_init();
    }
    if (mDemo.getDemoType() == 4 && !dComIfGp_evmng_checkStartDemo()) {
        mDemo.setDemoType(2);
    }
    if (demo_actor_p != NULL) {
        demo_actor_p->setModel(mpCLModel);
        mStaffIdx = -1;
        if (mDemo.getDemoType() != 1) {
            mDemo.setDemoType(1);
            freeGrabItem();
            freeRopeItem();
            freeHookshotItem();
            deleteEquipItem(FALSE);
            procWait_init();
        }
        if (demo_actor_p->checkEnable(dDemo_actor_c::ENABLE_ANM_e)) {
            demo_mode = demo_actor_p->getAnmId();
        }
        if (demo_actor_p->checkEnable(dDemo_actor_c::ENABLE_TRANS_e)) {
            pos_p = demo_actor_p->getTrans();
        } else {
            pos_p = &current.pos;
        }
        if (demo_actor_p->checkEnable(dDemo_actor_c::ENABLE_ROTATE_e)) {
            angle = demo_actor_p->getRatate()->y;
        } else {
            angle = shape_angle.y;
        }
        if (demo_actor_p->checkEnable(dDemo_actor_c::ENABLE_SHAPE_e)) {
            if (dComIfGs_getClearCount() == 0) {
                u32 shape = demo_actor_p->getShapeId();
                if ((checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES) && shape == 0) ||
                    (!checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES) && shape == 1))
                {
                    ResTIMG casualLinktex = *mpCurrLinktex;
                    *mpCurrLinktex = mOtherLinktex;
                    mOtherLinktex = casualLinktex;
                    if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
                        offNoResetFlg1(daPyFlg1_CASUAL_CLOTHES);
                    } else {
                        onNoResetFlg1(daPyFlg1_CASUAL_CLOTHES);
                    }
                }
            }
        }
    } else {
        if (mDemo.getDemoType() == 0 && dComIfGp_event_runCheck()) {
            mDemo.setDemoType(2);
        }
        if (mStaffIdx != -1) {
            char* cut_name = dComIfGp_getPEvtManager()->getMyNowCutName(mStaffIdx);
            if (cut_name != NULL) {
                // Take the first 3 chars in cut_name, convert them to integers, and calculate
                // demo_mode
                demo_mode = ((cut_name[0] - '0') * 100 + (cut_name[1] - '0') * 10 + (cut_name[2] - '0'));
                if (
                    mDemo.getDemoType() != 4 &&
                    (
                        demo_mode == daPy_demo_c::DEMO_N_WAIT_e ||
                        demo_mode == daPy_demo_c::DEMO_KM_WAIT_e ||
                        demo_mode == daPy_demo_c::DEMO_A_WAIT_e
                    )
                ) {
                    if (mAcch.ChkGroundHit() && !daPy_lk_c::checkPlayerFly()) {
                        mVelocity = 0.0f;
                        speedF = 0.0f;
                    }
                }
                pos_p = dComIfGp_evmng_getMyXyzP(mStaffIdx, "pos");
                if (pos_p == NULL) {
                    pos_p = dComIfGp_evmng_getGoal();
                }
                int* angle_p = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "angle");
                if (angle_p != NULL) {
                    angle = *angle_p;
                } else if (demo_mode == daPy_demo_c::DEMO_WAIT_TURN_e) {
                    angle = mDemo.getMoveAngle();
                } else {
                    angle = shape_angle.y;
                }
                prm0_p = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "prm0");
                prm1_p = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "prm1");
                if (mDemo.getDemoType() == 2) {
                    f32* stick_p = dComIfGp_evmng_getMyFloatP(mStaffIdx, "stick");
                    if (stick_p != NULL) {
                        mDemo.setStick(*stick_p);
                    } else {
                        mDemo.setStick(1.0f);
                    }
                }
                int* face_p = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "face");
                if (face_p != NULL) {
                    if (*face_p == 0) {
                        resetDemoTextureAnime();
                    } else if (*face_p == 1) {
                        changeTextureAnime(LKANM_BTP_TMABAI, LKANM_BTK_TMABA, -1);
                    }
                }
            }
        }
    }
    if ((demo_mode == daPy_demo_c::DEMO_SHIP_e) && dComIfGp_getShipActor() == NULL) {
        demo_mode = daPy_demo_c::DEMO_N_WAIT_e;
    }
    if (mDemo.getDemoType() == 4) {
        if (mDemo.getDemoMode() == daPy_demo_c::DEMO_KEEP_e) {
            if (mDemo.getTimer() != 0) {
                mDemo.decTimer();
                cXyz sp5C = current.pos - home.pos;
                if (sp5C.abs2XZ() > SQUARE(300.0f)) {
                    mDemo.setTimer(0);
                    dComIfGp_evmng_cutEnd(mStaffIdx);
                }
            } else {
                dComIfGp_evmng_cutEnd(mStaffIdx);
            }
        }
        return;
    }
    if (mDemo.getDemoType() == 1 || (mDemo.getDemoType() == 2 && mStaffIdx != -1)) {
        if (prm0_p != NULL) {
            mDemo.setParam0(*prm0_p);
        } else {
            mDemo.setParam0(0);
        }
        if (prm1_p != NULL) {
            mDemo.setParam1(*prm1_p);
        } else {
            mDemo.setParam1(0);
        }
        if ((demo_mode == daPy_demo_c::DEMO_INIT_WAIT_e) || (demo_mode == daPy_demo_c::DEMO_POS_INIT_e)) {
            mVelocity = 0.0f;
            speedF = 0.0f;
            mStts.ClrCcMove();
            setPlayerPosAndAngle(pos_p, angle);
            mDemo.setMoveAngle(angle);
            if (demo_mode == daPy_demo_c::DEMO_INIT_WAIT_e && mDemo.getParam0() != 0) {
                deleteEquipItem(FALSE);
                if (mDemo.getParam0() == 1 && checkSwordEquip()) {
#if VERSION == VERSION_DEMO
                    setSwordModel();
#else
                    setSwordModel(TRUE);
#endif
                } else if (mDemo.getParam0() == 2) {
                    mEquipItem = daPyItem_NONE_e;
                } else if (mDemo.getParam0() == 3) {
                    mEquipItem = daPyItem_NONE_e;
                    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                        dComIfGp_clearPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
                    }
                }
                mDemo.setParam0(0);
            }
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                if (dComIfGp_getShipActor() != NULL) {
                    dComIfGp_getShipActor()->initStartPos(&current.pos, shape_angle.y);
                }
            }
        } else if (demo_mode == daPy_demo_c::DEMO_CUT_ROLL_e) {
            cXyz sp50 = *pos_p - current.pos;
            s16 r24 = current.angle.y;
            current.angle.y = cM_atan2s(sp50.x, sp50.z);
            shape_angle.y = current.angle.y;
            m34EC -= (s16)(current.angle.y - r24);
        } else if ((demo_mode == daPy_demo_c::DEMO_N_WALK_e) || (demo_mode == daPy_demo_c::DEMO_N_DASH_e)) {
            cXyz sp44 = *pos_p - current.pos;
            if (std::abs(mVelocity) / mMaxNormalSpeed < m_HIO->mMove.m.field_0x2C) {
                demo_mode = daPy_demo_c::DEMO_N_WALK_e;
            }
            f32 dVar22 = sp44.abs2XZ();
            if (dVar22 < 100.0f || (dVar22 < 2500.0f && std::abs(mVelocity) < 0.001f)) {
                demo_mode = daPy_demo_c::DEMO_N_WAIT_e;
                mVelocity = 0.0f;
            } else if ((demo_mode == daPy_demo_c::DEMO_N_WALK_e && dVar22 < 400.0f) || dVar22 < 2500.0f) {
                mDemo.setStick(0.0f);
            }
            mDemo.setMoveAngle(cM_atan2s(sp44.x, sp44.z));
        } else if ((demo_mode == daPy_demo_c::DEMO_WAIT_TURN_e) || (demo_mode == daPy_demo_c::DEMO_SURPRISED_e)) {
            mDemo.setMoveAngle(angle);
        }
        mDemo.setDemoMode(demo_mode);
    } else if (mDemo.getDemoType() != 3) {
        mDemo.setDemoMode(demo_mode);
    }
    if ((checkModeFlg(ModeFlg_00080000) || (mDemo.getDemoMode() == daPy_demo_c::DEMO_N_TALK_e)) ||
        (mDemo.getDemoMode() == daPy_demo_c::DEMO_E_TALK_e))
    {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK10_e);
    } else {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK10_e);
    }
    if (mStaffIdx != -1 && (demo_mode == daPy_demo_c::DEMO_N_WAIT_e || demo_mode == daPy_demo_c::DEMO_INIT_WAIT_e ||
                            demo_mode == daPy_demo_c::DEMO_A_WAIT_e || demo_mode == daPy_demo_c::DEMO_KEEP_e ||
                            demo_mode == daPy_demo_c::DEMO_PFALL_e || demo_mode == daPy_demo_c::DEMO_UNK_018_e ||
                            demo_mode == daPy_demo_c::DEMO_KM_WAIT_e || demo_mode == daPy_demo_c::DEMO_CUT_ROLL_e ||
                            demo_mode == daPy_demo_c::DEMO_POS_INIT_e || demo_mode == daPy_demo_c::DEMO_SHIP_e ||
                            demo_mode == daPy_demo_c::DEMO_UNK_051_e))
    {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
}

/* 8011F9C0-8011FF50       .text setStickData__9daPy_lk_cFv */
void daPy_lk_c::setStickData() {
    m34CA = mItemButton;
    mItemTrigger = 0;
    mItemButton = 0;
    if (daPy_getPlayerActorClass() != this) {
        mStickDistance = 0.0f;
        m34E8 = 0;
    } else {
        if (checkBowMiniGame()) {
            mStickDistance = g_mDoCPd_cpadInfo[0].mMainStickValue;
            m34DC = g_mDoCPd_cpadInfo[0].mMainStickAngle + 0x8000;
            m34E8 = m34DC + dCam_getControledAngleY(dComIfGp_getCamera(mCameraInfoIdx));
            if (CPad_CHECK_HOLD_A(0)) {
                mItemButton |= BTN_A;
            }
        } else if (
            (dComIfGp_event_runCheck() || checkPlayerDemoMode()) &&
            !dComIfGp_checkPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e) &&
            mCurProc != daPyProc_NOT_USE_e && mCurProc != daPyProc_BOTTLE_GET_e
        ) {
            if ((mDemo.getDemoMode() == daPy_demo_c::DEMO_N_WALK_e) ||
                (mDemo.getDemoMode() == daPy_demo_c::DEMO_N_DASH_e))
            {
                if (dComIfGp_demo_getActor(demoActorID) != NULL) {
                    mStickDistance = 1.0f;
                } else {
                    mStickDistance = mDemo.getStick();
                }
            } else {
                mStickDistance = 0.0f;
            }
            m34E8 = mDemo.getMoveAngle();
            if (mDemo.getDemoMode() == daPy_demo_c::DEMO_KEEP_e) {
                mItemButton = m34CA;
            }
        } else if (fopOvlpM_IsPeek() == 1) {
            mStickDistance = 0.0f;
            m34E8 = 0;
        } else {
            mStickDistance = g_mDoCPd_cpadInfo[0].mMainStickValue;
            if (checkNoResetFlg1(daPyFlg1_CONFUSE) && !dComIfGp_event_runCheck()) {
                m34DC = g_mDoCPd_cpadInfo[0].mMainStickAngle;
            } else {
                m34DC = g_mDoCPd_cpadInfo[0].mMainStickAngle + 0x8000;
            }
            m34E8 = m34DC + dCam_getControledAngleY(dComIfGp_getCamera(mCameraInfoIdx));
            u8 bVar2 = dComIfGp_getButtonActionMode();
            bool bVar1 = false;
            if (CPad_CHECK_TRIG_B(0)) {
                if ((dComIfGp_getButtonActionMode() & 2) != 0) {
                    mItemTrigger |= BTN_B;
                } else {
                    bVar1 = true;
                }
            }
            if (CPad_CHECK_TRIG_A(0)) {
                if ((bVar2 & 1) != 0) {
                    mItemTrigger |= BTN_A;
                } else {
                    bVar1 = true;
                }
            }
            if (CPad_CHECK_TRIG_X(0)) {
                if (((bVar2 & 4) != 0) && mTinkleHoverTimer == 0) {
                    mItemTrigger |= BTN_X;
                } else {
                    bVar1 = true;
                }
            }
            if (CPad_CHECK_TRIG_Y(0)) {
                if (((bVar2 & 8) != 0) && mTinkleHoverTimer == 0) {
                    mItemTrigger |= BTN_Y;
                } else {
                    bVar1 = true;
                }
            }
            if (CPad_CHECK_TRIG_Z(0)) {
                if (((bVar2 & 0x20) != 0) && mTinkleHoverTimer == 0) {
                    mItemTrigger |= BTN_Z;
                } else {
                    bVar1 = true;
                }
            }
            if (CPad_CHECK_TRIG_L(0)) {
                mItemTrigger |= BTN_L;
            }
            if (mDoCPd_R_LOCK_TRIGGER(0)) {
                mItemTrigger |= BTN_R;
            }
            if (CPad_CHECK_HOLD_A(0) && ((bVar2 & 1) != 0)) {
                mItemButton |= BTN_A;
            }
            if (CPad_CHECK_HOLD_B(0) && ((bVar2 & 2) != 0)) {
                mItemButton |= BTN_B;
            }
            if (mTinkleHoverTimer == 0) {
                if (CPad_CHECK_HOLD_X(0) && ((bVar2 & 4) != 0)) {
                    mItemButton |= BTN_X;
                }
                if (CPad_CHECK_HOLD_Y(0) && ((bVar2 & 8) != 0)) {
                    mItemButton |= BTN_Y;
                }
                if (CPad_CHECK_HOLD_Z(0) && ((bVar2 & 0x20) != 0)) {
                    mItemButton |= BTN_Z;
                }
            }
            if (CPad_CHECK_HOLD_L(0)) {
                mItemButton |= BTN_L;
            }
            if (mDoCPd_R_LOCK_BUTTON(0)) {
                mItemButton |= BTN_R;
            }
            if (checkHeavyStateOn()) {
                mStickDistance = mStickDistance * m_HIO->mMove.m.field_0x80;
            }
            if (checkGrabWear()) {
                mStickDistance = mStickDistance * m_HIO->mMove.m.field_0x74;
            }
#if VERSION == VERSION_DEMO
            if (bVar1)
#else
            if (bVar1 && !dComIfGp_event_runCheck())
#endif
            {
                seStartSystem(JA_SE_ITEM_TARGET_OUT);
            }
        }
    }
    s16 angle_diff = m34DC - m34EA;
    int abs_v = abs(angle_diff);
    if (((abs_v < m_HIO->mCut.mCutTurnR.m.field_0x6) &&
         (abs_v > m_HIO->mCut.mCutTurnR.m.field_0x8)) &&
        (m3578 * angle_diff >= 0))
    {
        m3578 = m3578 + angle_diff;
        m3524 = m_HIO->mCut.mCutTurnR.m.field_0x2;
    } else if (m3578 * angle_diff < 0) {
        m3578 = angle_diff;
        m3524 = m_HIO->mCut.mCutTurnR.m.field_0x2;
    } else if (m_HIO->mCut.mCutTurnR.m.field_0x0 == 0) {
        if (m3524 > 0) {
            m3524--;
        } else {
            m3578 = 0;
        }
    }
}

/* 8011FF50-801200F8       .text setBgCheckParam__9daPy_lk_cFv */
void daPy_lk_c::setBgCheckParam() {
    mAcchCir[0].SetWallH(30.1f);
    mAcchCir[1].SetWallH(89.9f);
    mAcchCir[2].SetWallH(125.0f);
    
    if (mCurProc == daPyProc_ROPE_SWING_START_e) {
        mAcchCir[0].SetWallH(-125.0f);
        mAcchCir[1].SetWallH(-89.9f);
        mAcchCir[2].SetWallH(0.0f);
    } else if (mCurProc == daPyProc_LARGE_DAMAGE_WALL_e || checkModeFlg(ModeFlg_CLIMB | ModeFlg_LADDER)) {
        mAcchCir[0].SetWallR(5.0f);
    } else if (checkModeFlg(ModeFlg_PUSHPULL)) {
        mAcchCir[0].SetWallR(40.0f);
    } else if (checkModeFlg(ModeFlg_WHIDE)) {
        mAcchCir[0].SetWallR(m_HIO->mWall.m.field_0x50);
        if (checkNoResetFlg0(daPyFlg0_UNK10000)) {
            mAcchCir[2].SetWallH(89.9f);
        }
    } else if (checkModeFlg(ModeFlg_SWIM)) {
        mAcchCir[0].SetWallR(67.5f);
        mAcchCir[0].SetWallH(-5.0f);
        mAcchCir[1].SetWallH(0.0f);
        mAcchCir[2].SetWallH(20.0f);
    } else if (checkModeFlg(ModeFlg_CRAWL) && mCurProc != daPyProc_CRAWL_END_e) {
        mAcchCir[0].SetWallR(30.0f);
        mAcchCir[0].SetWallH(10.0f);
        mAcchCir[1].SetWallH(50.0f);
        mAcchCir[2].SetWallH(50.0f);
    } else if (checkModeFlg(ModeFlg_HANG)) {
        mAcchCir[0].SetWallR(12.5f);
        mAcchCir[0].SetWallH(25.0f);
        mAcchCir[1].SetWallH(25.0f);
        mAcchCir[2].SetWallH(25.0f);
    } else if (checkGrabWear()) {
        mAcchCir[0].SetWallR(50.0f);
    } else {
        mAcchCir[0].SetWallR(35.0f);
    }
    
    mAcchCir[1].SetWallR(mAcchCir[0].GetWallR());
    mAcchCir[2].SetWallR(mAcchCir[0].GetWallR());
}

/* 801200F8-8012010C       .text setParamData__9daPy_lk_cFiiii */
u32 daPy_lk_c::setParamData(int roomNo, int spawnType, int eventInfoIdx, int extraParams) {
    return (roomNo & 0x3F) | (spawnType & 0xF) << 0xC | eventInfoIdx << 0x18 | extraParams;
}

/* 8012010C-8012024C       .text checkLavaFace__9daPy_lk_cFP4cXyzi */
BOOL daPy_lk_c::checkLavaFace(cXyz* oldPos, int attributeCode) {
    if (mDemo.getDemoType() == 5) {
        return FALSE;
    }
    
    if (oldPos != NULL) {
        cXyz pos(current.pos.x, oldPos->y + 20.0f, current.pos.z);
        mLavaGndChk.SetPos(&pos);
        m35D4 = dComIfG_Bgsp()->GroundCross(&mLavaGndChk);
        if (mAcch.GetGroundH() > m35D4) {
            m35D4 = -G_CM3D_F_INF;
        }
        if (m35D4 > current.pos.y) {
            attributeCode = dComIfG_Bgsp()->GetAttributeCode(mLavaGndChk);
        } else {
            return FALSE;
        }
    }
    
    if (attributeCode == dBgS_Attr_LAVA_e) {
        if (oldPos != NULL) {
            current.pos.y = m35D4;
        }
        if (checkBossGomaStage()) {
            return procLavaDamage_init();
        } else {
            return dProcLavaDamage_init();
        }
    } else if (attributeCode == dBgS_Attr_VOID_e) {
        startRestartRoom(5, 0xC9, -1.0f, 0);
    }
    
    return FALSE;
}

/* 8012024C-80120724       .text checkFallCode__9daPy_lk_cFv */
void daPy_lk_c::checkFallCode() {
    int iVar1;
    s32 bVar2;
    u32 uVar3;
    BOOL bVar4;
    f32 dVar5;
    f32 dVar6;
    cXyz local_44;

    if (m3580 == 4 || -G_CM3D_F_INF == mAcch.GetGroundH()) {
        bVar4 = m35D0 > mAcch.GetGroundH() ? TRUE : FALSE;
        if (((((!bVar4) && checkModeFlg(ModeFlg_MIDAIR)) &&
              (!checkModeFlg(ModeFlg_HOOKSHOT) && (m35F4 - current.pos.y > 100.0f * m_HIO->mFall.m.field_0x14))) ||
             (bVar4 && checkModeFlg(ModeFlg_SWIM))) ||
            (mAcch.ChkGroundHit() && (!checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)))))
        {
            startRestartRoom(5, 0xC9, -1.0f, 0);
            mAcch.ClrGroundHit();
        }
        return;
    }
    if (checkNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG) && checkModeFlg(ModeFlg_SWIM)) {
        startRestartRoom(5, 0xC9, -1.0f, 0);
        return;
    }
    iVar1 = dComIfG_Bgsp()->GetExitId(mAcch.m_gnd);
    bVar2 = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if (iVar1 == 0x3f) {
        return;
    }
    if ((checkModeFlg(ModeFlg_SWIM) || mAcch.ChkGroundHit()) || mCurProc == daPyProc_FAN_GLIDE_e ||
        ((dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && ship != NULL && !ship->checkForceMove()) ||
         (m3580 == 5 && m35F4 - current.pos.y > 500.0f)))
    {
        dComIfGs_startFwaterTimer();
        dVar6 = speedF;
        dVar5 = 1.5f;
        if (dVar6 < dVar5) {
            dVar5 = dVar5;
        } else if (dVar6 > m_HIO->mMove.m.field_0x18) {
            dVar5 = m_HIO->mMove.m.field_0x18;
        } else {
            dVar5 = dVar6;
        }
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            uVar3 = 1;
            if (dComIfGp_getShipActor() != NULL) {
                dComIfGp_getShipActor()->onSceneChange();
            }
        } else {
            if (checkModeFlg(ModeFlg_CRAWL)) {
                if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() >= 0.0f) {
                    uVar3 = 2;
                } else {
                    uVar3 = 3;
                }
            } else {
                uVar3 = 0;
            }
        }
        if (m3580 == 5) {
            mAcch.ClrGroundHit();
        }
        if (!eventInfo.checkCommandDoor()) {
            if (!dComIfGp_event_compulsory(this)) {
                return;
            }
        }
        if (dStage_changeSceneExitId(mAcch.m_gnd, dVar5, uVar3, bVar2)) {
            onNoResetFlg1(daPyFlg1_UNK100000);
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3E10)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3E01);
            }
            daPy_py_c::changePlayer((daPy_py_c*)this);
            if ((!strcmp(dComIfGp_getStartStageName(), "GanonM")) && current.roomNo == 1) {
                seStartSystem(JA_SE_LK_MAZE_WARP_IN);
            }
            if (!eventInfo.checkCommandDoor()) {
                mDemo.setDemoType(3);
                if (m3580 == 5) {
                    mDemo.setDemoMode(daPy_demo_c::DEMO_PFALL_e);
                } else if ((checkModeFlg(ModeFlg_SWIM) || m34C3 == 1) || m34C3 == 4) {
                    mDemo.setDemoMode(daPy_demo_c::DEMO_KEEP_e);
                    mVelocity *= 0.75f;
                } else {
                    mDemo.setDemoMode(daPy_demo_c::DEMO_N_WALK_e);
                }
                local_44 = current.pos - old.pos;
                dVar5 = local_44.abs();
                if (dVar5 > 0.1f) {
                    mDemo.setMoveAngle(cM_atan2s(local_44.x, local_44.z));
                } else {
                    mDemo.setMoveAngle(current.angle.y);
                }
            }
        }
    }
}

/* 80120724-80120BBC       .text startRestartRoom__9daPy_lk_cFUlifi */
BOOL daPy_lk_c::startRestartRoom(u32 mode, int eventInfoIdx, f32 param_3, int i_point) {
    if (!checkNoResetFlg0(daPyFlg0_UNK4000) && (i_point != 0 || dComIfGp_event_compulsory(this))) {
        mDemo.setOriginalDemoType();
        if (i_point == 0) {
            mDemo.setDemoMode(daPy_demo_c::DEMO_N_WAIT_e);
        }
        onNoResetFlg0(daPyFlg0_UNK4000);
        changePlayer(this);

        if (dComIfGp_getMiniGameType() == 1) {
            dComIfGp_setNextStage("sea", 1, 48);
            seStartSystem(JA_SE_FORCE_BACK);
            daNpc_Sarace_c::ship_race_result = 3;
            mTinkleShieldTimer = 0;
            return TRUE;
        }

        u32 stageType = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo());
        setDamagePoint(param_3);
        mTinkleShieldTimer = 0;

        if (stageType == dStageType_SEA_e && !dComIfGs_isEventBit(dSv_event_flag_c::RODE_KORL) &&
            (current.roomNo == dIsleRoom_WindfallIsland_e || current.roomNo == dIsleRoom_OutsetIsland_e) &&
            dStage_chkPlayerId(0x80, current.roomNo))
        {
            dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0x80, current.roomNo, -1, 0.0f, mode);
            u32 roomParam = setParamData(-1, 0, eventInfoIdx, 0);
            dComIfGs_setRestartRoomParam(roomParam);
            seStartSystem(JA_SE_FORCE_BACK);
            return TRUE;
        }

        if (checkNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG) && mCurProc != daPyProc_DEMO_DEAD_e) {
            i_point = mDekuSpRestartPoint;
        } else {
            i_point = mRestartPoint;
            if (i_point != 0xFF && !dComIfGs_checkSeaLandingEvent(current.roomNo)) {
                i_point = 0xFF;
            }
        }

        if (i_point == 0xFF) {
            if (stageType == dStageType_SEA_e) {
                cXyz* pos;
                if (dComIfGp_getShipActor()) {
                    pos = &dComIfGp_getShipActor()->current.pos;
                } else {
                    pos = &current.pos;
                }

                int quad_x = (1.0f / 50000.0f) * (350000.0f + pos->x);
                int quad_z = (1.0f / 50000.0f) * (350000.0f + pos->z);
                if (quad_x < 0) {
                    quad_x = 0;
                } else if (quad_x > 13) {
                    quad_x = 13;
                }
                if (quad_z < 0) {
                    quad_z = 0;
                } else if (quad_z > 13) {
                    quad_z = 13;
                }

                int subsector_z = quad_z & 1;
                int subsector_x = quad_x & 1;
                int sector_z = quad_z >> 1;
                int sector_x = quad_x >> 1;
                int sector_num = sector_z * 7 + sector_x;
                int scls_idx = subsector_x + (sector_num << 2) + (subsector_z << 1);

                dStage_changeScene(scls_idx, 0.0f, mode, -1);
            } else {
                if (mCurProc == daPyProc_DEMO_DEAD_e) {
                    dStage_changeScene(0, 0.0f, mode, -1);
                } else {
                    int roomNo = dComIfGs_getRestartRoomNo();
                    u32 roomParam = setParamData(roomNo, 0, eventInfoIdx, 0);
                    dStage_restartRoom(roomParam, mode);
                    seStartSystem(JA_SE_FORCE_BACK);
                }
                return TRUE;
            }
        } else if (checkNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG)) {
            dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, 41, -1, 0.0f, mode);
        } else {
            dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, current.roomNo, -1, 0.0f, mode);
        }

        if (mCurProc != daPyProc_DEMO_DEAD_e) {
            u32 roomParam = setParamData(-1, 0, eventInfoIdx, 0);
            dComIfGs_setRestartRoomParam(roomParam);
            seStartSystem(JA_SE_FORCE_BACK);
        }

        return TRUE;
    }

    return FALSE;
}

/* 80120BBC-80120BE0       .text checkSuccessGuard__9daPy_lk_cFi */
BOOL daPy_lk_c::checkSuccessGuard(int atSpl) {
    if (!mCyl.ChkTgShieldHit() || atSpl >= dCcG_At_Spl_UNK8) {
        return FALSE;
    }
    return TRUE;
}

/* 80120BE0-80120F94       .text setShapeAngleOnGround__9daPy_lk_cFv */
void daPy_lk_c::setShapeAngleOnGround() {
    s16 sVar2;
    int iVar3;
    f32 dVar8;
    f32 dVar7;
    cXyz local_44;
    cXyz local_50;
    cXyz local_68;
    cM3dGPla* triPla;

    if (!checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000))) {
        if (m35E4 < 0.0f) {
            m35E4 = 0.0f;
        } else if (m35E4 > 1.0f) {
            m35E4 = 1.0f;
        }
        if (checkModeFlg(ModeFlg_CRAWL)) {
            mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
            mDoMtx_stack_c::YrotM(shape_angle.y);
            mDoMtx_stack_c::multVec(&l_crawl_front_up_offset, &local_44);
            mDoMtx_stack_c::multVec(&l_crawl_back_up_offset, &local_50);
            mGndChk.SetPos(&local_44);
            local_44.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (-G_CM3D_F_INF != local_44.y) {
                triPla = dComIfG_Bgsp()->GetTriPla(mGndChk);
            } else {
                triPla = NULL;
            }
            if (triPla != NULL) {
                dVar8 = triPla->GetNP()->y;
            } else {
                dVar8 = -1.0f;
            }
            mGndChk.SetPos(&local_50);
            local_50.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (-G_CM3D_F_INF != local_50.y) {
                triPla = dComIfG_Bgsp()->GetTriPla(mGndChk);
            } else {
                triPla = NULL;
            }
            if (triPla != NULL) {
                dVar7 = triPla->GetNP()->y;
            } else {
                dVar7 = -1.0f;
            }
            local_68 = local_44 - local_50;
            sVar2 = cM_atan2s(-local_68.y, local_68.absXZ());
            iVar3 = cLib_distanceAngleS(sVar2, shape_angle.x);
            if (((iVar3 < 0x1000 && dVar8 > 0.0f) && dVar7 > 0.0f) &&
                (std::abs((dVar8 - dVar7)) > 0.05f))
            {
                shape_angle.x = sVar2 * m35E4;
            } else {
                shape_angle.x = m34E2 * m35E4;
            }
        } else {
            shape_angle.x = m34E2 * m35E4;
        }
        shape_angle.z = m35E4 * getGroundAngle(&mAcch.m_gnd, shape_angle.y + -0x4000);
    }
}

/* 80120F94-801211B8       .text setStepsOffset__9daPy_lk_cFv */
void daPy_lk_c::setStepsOffset() {
    f32 fVar1;
    f32 dVar5;
    f32 dVar6;
    cXyz local_2c;

    cLib_addCalc(&m35C4, 0.0f, 0.5f, 25.0f, 5.0f);
    dVar6 = (cM_ssin(m34E2) / cM_scos(m34E2));
    local_2c.x = current.pos.x + speedF * cM_ssin(current.angle.y);
    local_2c.y = 30.1f + current.pos.y;
    local_2c.z = current.pos.z + speedF * cM_scos(current.angle.y);
    mGndChk.SetPos(&local_2c);
    dVar5 = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (checkNoResetFlg0(daPyFlg0_UNK80000000) && current.pos.y > dVar5) {
        dVar5 = current.pos.y;
    }
    fVar1 = (dVar5 - current.pos.y) - (-speedF * dVar6);
    if (fVar1 > 0.0f) {
        current.pos.y = dVar5;
        m35C4 -= fVar1 * 0.7f;
    } else if (!checkNoResetFlg0(daPyFlg0_UNK80000000)) {
        local_2c = old.pos - current.pos;
        fVar1 = local_2c.y - (dVar6 * local_2c.absXZ());
        if (fVar1 >= 0.0f) {
            m35C4 += fVar1 * 0.7f;
        }
    }
}

/* 801211B8-8012135C       .text setBeltConveyerPower__9daPy_lk_cFv */
void daPy_lk_c::setBeltConveyerPower() {
    f32 fVar1;
    f32 dVar4;
    f32 dVar5;
    int local_58;
    cXyz cStack_3c;

    if (!checkHeavyStateOn() && !dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 &&
        !checkNoResetFlg0((daPy_FLG0)(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) &&
        (mAcch.ChkGroundHit() || checkModeFlg(ModeFlg_SWIM)))
    {
        if (dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd) && dPath_GetPolyRoomPathVec(mAcch.m_gnd, &cStack_3c, &local_58)) {
            cStack_3c.normalizeZP();
        } else {
            cStack_3c = cXyz::Zero;
            local_58 = 0;
        }
        cStack_3c *= local_58;
        dVar4 = m36B8.abs2XZ();
        dVar5 = cStack_3c.abs2XZ();
        if (dVar4 > dVar5) {
            fVar1 = 3.0f;
        } else {
            fVar1 = 1.0f;
        }
        cLib_addCalcPosXZ(&m36B8, cStack_3c, 0.5f, fVar1, 0.5f);
    } else {
        m36B8 = cXyz::Zero;
    }
}

/* 8012135C-801216A8       .text setWindAtPower__9daPy_lk_cFv */
void daPy_lk_c::setWindAtPower() {
    f32 dVar6;
    cXyz local_58;
    f32 fVar2;
    f32 fVar1;

    if (mWindCyl.ChkTgHit()) {
        dCcD_GObjInf* iVar4 = mWindCyl.GetTgHitGObj();
        if (iVar4 != NULL && iVar4->GetAtSpl() == dCcG_At_Spl_UNK1) {
            m34BA = 1;
        } else {
            m34BA = 0;
        }
    }
    if (mWindCyl.ChkTgHit() && (mDamageWaitTimer == 0 || m34BA == 0) && !dComIfGp_event_runCheck() &&
        mDemo.getDemoType() == 0 && mCurProc != daPyProc_FAN_GLIDE_e)
    {
        local_58 = *mWindCyl.GetTgRVecP();
        dVar6 = local_58.absXZ();
        if (m34BA != 0) {
            fVar1 = 27.0f;
            fVar2 = 18.0f;
        } else {
            fVar1 = 30.0f;
            fVar2 = 1.0f;
        }
        if (dVar6 < 1.0f) {
            local_58 = (current.pos - *mWindCyl.GetTgHitPosP()) * fVar1;
            dVar6 = local_58.absXZ();
        }
        if (dVar6 > fVar1) {
            local_58 *= (fVar1 / dVar6);
        }
    } else {
        local_58 = cXyz::Zero;
        if (m34BA != 0) {
            fVar2 = 1.0f;
        } else {
            fVar2 = 3.0f;
        }
    }
    if (mCurProc != daPyProc_FAN_GLIDE_e) {
        if (dComIfGp_event_runCheck() || checkPlayerDemoMode()) {
            m373C.x = 0.0f;
            m373C.z = 0.0f;
        } else {
            cLib_addCalcPosXZ(&m373C, local_58, 0.5f, fVar2, 0.5f);
        }
        if (checkHeavyStateOn() || dComIfGp_event_runCheck() || checkPlayerDemoMode()) {
            m3730.x = 0.0f;
            m3730.z = 0.0f;
        } else {
            cLib_addCalcPosXZ(&m3730, local_58, 0.5f, fVar2, 0.5f);
        }
    }
}

/* 801216A8-80121870       .text checkRoofRestart__9daPy_lk_cFv */
void daPy_lk_c::checkRoofRestart() {
    if (!mAcch.ChkRoofHit()) { return; }
    if (!mAcch.ChkGroundHit()) { return; }
    if (mCurProc == daPyProc_CRAWL_START_e) { return; }
    if (mCurProc == daPyProc_CRAWL_END_e) { return; }
    if (mCurProc == daPyProc_WHIDE_READY_e) { return; }
    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_BOSS_e) { return; }
#if VERSION > VERSION_DEMO
    if (
        dComIfG_Bgsp()->ChkMoveBG(mAcch.m_roof) &&
        fopAcM_GetName(dComIfG_Bgsp()->GetActorPointer(mAcch.m_roof)) == PROC_BRIDGE
    ) {
        return;
    }
#endif

    f32 dVar9 = mAcch.GetRoofHeight();
    if (dVar9 > mAcch.GetGroundH()) {
        f32 dVar10 = mHeadTopPos.y - 10.0f;
        f32 dVar8 = 10.0f + current.pos.y;
        if (dVar10 < dVar8) {
            dVar10 = dVar8;
        }
        if (dVar9 < dVar10) {
            if (checkModeFlg(ModeFlg_WHIDE)) {
                cXyz local_8;

                local_8.set(
                    current.pos.x + (35.0f - m_HIO->mWall.m.field_0x50) * cM_ssin(shape_angle.y),
                    current.pos.y,
                    current.pos.z + (35.0f - m_HIO->mWall.m.field_0x50) * cM_scos(shape_angle.y)
                );

                mRoofChk.SetPos(local_8);
                dVar9 = dComIfG_Bgsp()->RoofChk(&mRoofChk);
                if (dVar9 >= dVar10) {
                    return;
                }
            }
            if (startRestartRoom(5, 0xC9, -1.0f, 0)) {
                voiceStart(43);
            }
        }
    }
}

/* 80121870-80122D30       .text execute__9daPy_lk_cFv */
BOOL daPy_lk_c::execute() {
#if VERSION > VERSION_DEMO
    if (setGetDemo()) {
        return TRUE;
    }
#endif
    
    if (checkNoResetFlg1(daPyFlg1_UNK200)) {
        fopMsgM_demoMsgFlagOn();
        if (checkEndMessage(0x14A3)) {
            offNoResetFlg1(daPyFlg1_UNK200);
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_9EFF, 0);
            dComIfGp_event_reset();
            mDemo.setDemoType(0);
        }
        return TRUE;
    }
    
    if (dComIfGs_checkBottle(dItem_FOREST_WATER_e)) {
        if (dComIfGs_getFwaterTimer() == 0) {
            if (dComIfGp_event_compulsory(this)) {
                onNoResetFlg1(daPyFlg1_UNK200);
                dComIfGs_setBottleItemIn(dItem_FOREST_WATER_e, dItem_WATER_BOTTLE_e);
                mDemo.setDemoType(5);
                m3628 = fpcM_ERROR_PROCESS_ID_e;
#if VERSION > VERSION_JPN
                if (mCurProc == daPyProc_SCOPE_e) {
                    procWait_init();
                }
#endif
            }
        }
    }
    
    if (checkNoControll()) {
        attention_info.flags = 0;
        fopAcM_SetStatusMap(this, 0x10);
        if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            mStts.SetWeight(0xFF);
            mStts.ClrCcMove();
        } else {
            mStts.SetWeight(120);
        }
    } else {
        attention_info.flags = ~0;
        fopAcM_SetStatusMap(this, 0x01);
        mStts.SetWeight(120);
    }
    
    if (checkEquipHeavyBoots() &&
        dComIfGp_getSelectItem(dItemBtn_X_e) != dItem_IRON_BOOTS_e &&
        dComIfGp_getSelectItem(dItemBtn_Y_e) != dItem_IRON_BOOTS_e &&
        dComIfGp_getSelectItem(dItemBtn_Z_e) != dItem_IRON_BOOTS_e
    ) {
        offNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
    } else if (checkEquipDragonShield() &&
        dComIfGp_getSelectItem(dItemBtn_X_e) != dItem_MAGIC_ARMOR_e &&
        dComIfGp_getSelectItem(dItemBtn_Y_e) != dItem_MAGIC_ARMOR_e &&
        dComIfGp_getSelectItem(dItemBtn_Z_e) != dItem_MAGIC_ARMOR_e
    ) {
        offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
    }
    
    if (dComIfGp_event_runCheck()) {
        mStaffIdx = dComIfGp_evmng_getMyStaffId("Link", this);
        if (eventInfo.checkCommandDoor() && !dComIfGp_event_chkEventFlag(0x4) && mEquipItem == daPyItem_BOKO_e) {
            fopAc_ac_c* equip_actor = mActorKeepEquip.getActor();
            if (equip_actor) {
                s16 angle = shape_angle.y + 0x8000;
                equip_actor->speed.y = 0.0f;
                equip_actor->speedF = 5.0f;
                equip_actor->current.angle.y = angle;
            }
            deleteEquipItem(FALSE);
        }
    }
    
#if VERSION > VERSION_DEMO
    current.pos = l_debug_keep_pos;
    shape_angle = l_debug_shape_angle;
    current.angle = l_debug_current_angle;
#endif
    
    mCameraInfoIdx = dComIfGp_getPlayerCameraID(0);
    m3748 = current.pos;
    
    if (mCurProc != daPyProc_HOOKSHOT_FLY_e &&
        !dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
        !checkModeFlg(ModeFlg_ROPE | ModeFlg_CLIMB | ModeFlg_LADDER) &&
        mCurProc != daPyProc_DEMO_TOOL_e &&
        mAcch.GetGroundH() != -G_CM3D_F_INF &&
        !checkNoResetFlg0((daPy_FLG0)(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) &&
        dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd) &&
        dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd)
    ) {
        dComIfG_Bgsp()->MoveBgCrrPos(mAcch.m_gnd, mAcch.ChkGroundHit(), &current.pos, &current.angle, &shape_angle);
        dComIfG_Bgsp()->MoveBgCrrPos(mAcch.m_gnd, mAcch.ChkGroundHit(), &old.pos, NULL, NULL);
    }
    
    cXyz oldPos = old.pos;
    m34DE = shape_angle.y;
    m35B4 = mStickDistance;
    m34EA = m34DC;
    
    dComIfGp_setDoStatus(dActStts_BLANK_e);
    dComIfGp_setRStatus(dActStts_BLANK_e);
    
    if (mEquipItem == daPyItem_BOKO_e) {
        dComIfGp_setAStatus(dActStts_SWING_e);
    } else if (checkSwordEquip()) {
        dComIfGp_setAStatus(dActStts_sword_01);
    } else {
        dComIfGp_setAStatus(dActStts_BLANK_e);
    }
    
    mFrontWallType = 0;
    
    if (checkResetFlg0(daPyRFlg0_POISON_CURSE)) {
        setDamageCurseEmitter();
    }
    
    if (checkResetFlg0(daPyRFlg0_UNK8000000)) {
        mCutType = 0;
    }
    
    mResetFlg0 = 0;
    
    daPy_matAnm_c::decMorfFrame();
    daPy_matAnm_c::decMabaTimer();
    
    if (mCurProc == daPyProc_BOTTLE_SWING_e && eventInfo.checkCommandCatch()) {
        mDemo.setDemoType(5);
    }
    
    setActorPointer();
    setAtnList();
    fopAc_ac_c* zTarget = dComIfGp_att_getZHint();
    if (zTarget) {
        stopDoButtonQuake(FALSE);
    } else {
        stopDoButtonQuake(TRUE);
    }
    
    if (m34C2 == 8) {
        if (m_old_fdata->getOldFrameMorfCounter() <= 0.0f) {
            m34C2 = 9;
        }
    } else {
        m34C2 = 0;
    }
    
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
    fopAc_ac_c* equip_actor = mActorKeepEquip.getActor();
    
    if (grab_actor && !fopAcM_checkCarryNow(grab_actor)) {
        freeGrabItem();
    }
    
    if (mEquipItem == daPyItem_BOKO_e) {
        if (equip_actor == NULL || !fopAcM_checkCarryNow(equip_actor)) {
            deleteEquipItem(FALSE);
        }
    }
    
    if (!checkFreezeState()) {
        if (!checkNoResetFlg1(daPyFlg1_UNK40000000)) {
            animeUpdate();
        }
    } else if (!checkNoResetFlg1(daPyFlg1_UNK40000)) {
        mDoGph_gInf_c::fadeIn(0.02f, l_freeze_fade_color);
        onNoResetFlg1(daPyFlg1_UNK40000);
    }
    
    setDemoData();
    setStickData();
    
    if (mEquipItem == dItem_GRAPPLING_HOOK_e &&
        (mCurProc == daPyProc_ROPE_SUBJECT_e || mCurProc == daPyProc_ROPE_MOVE_e) &&
        mActorKeepEquip.getActor() != NULL && fopAcM_GetParam(mActorKeepEquip.getActor()) == 2
    ) {
        procRopeReady_init();
    }
    
    if (mDemo.getDemoType() != 5) {
        if (!changeDemoProc() && !changeDeadProc() &&
            mCurProc != daPyProc_DEMO_LAVA_DAMAGE_e && mCurProc != daPyProc_DEMO_FREEZE_DAMAGE_e
        ) {
            if (!changeAutoJumpProc()) {
                changeSwimProc();
            }
        }
        changeDamageProc();
        changeBoomerangCatchProc();
    }
    
    checkItemAction();
    
    if (mEquipItem == daPyItem_SWORD_e && (m34C4 == 2 || m34C4 == 3)) {
        if (mAtCps[0].ChkAtHit() || mAtCps[1].ChkAtHit() || mAtCps[2].ChkAtHit()) {
            m34C4 += 2;
        }
    }
    if (m3522 > 0) {
        m3522--;
    } else {
        m34C4 = 0;
    }
    
    setShieldGuard();
    
    if (checkAtHitEnemy(&mAtCps[0]) || checkAtHitEnemy(&mAtCps[1]) || checkAtHitEnemy(&mAtCps[2])) {
        onNoResetFlg0(daPyFlg0_UNK10000000);
    }
    
    if (mCurProcFunc != NULL) {
        (this->*mCurProcFunc)();
    }
    
    playTextureAnime();
    cXyz sp14 = current.pos;
    posMove();
    mOldSpeed = speed;
    cXyz sp8 = current.pos;
    mAcch.ClrGroundHit();
    mAcch.CrrPos(*dComIfG_Bgsp());
    setWaterY();
    autoGroundHit();
    checkLavaFace(&oldPos, dBgS_Attr_NORMAL_e);
    
    if (checkModeFlg(ModeFlg_SWIM)) {
        if (checkNoResetFlg0(daPyFlg0_UNK100) && !checkSwimFallCheck()) {
            current.pos.y = m35D0;
        }
        if (mCurProc != daPyProc_DEMO_DEAD_e) {
            if (mAcch.GetGroundH() + 84.9f > current.pos.y && mAcch.ChkGroundHit()) {
                current.pos.y = mAcch.GetGroundH() + 84.9f;
                if (speed.y < 0.0f) {
                    speed.y = 0.0f;
                }
            }
        } else if (mAcch.ChkGroundHit()) {
            current.pos.y = mAcch.GetGroundH();
            if (speed.y < 0.0f) {
                speed.y = 0.0f;
            }
        }
    } else if (mCurProc == daPyProc_DEMO_TOOL_e) {
        current.pos = sp14;
        if (m3574 != 0 && mAcch.GetGroundH() != -G_CM3D_F_INF) {
            current.pos.y = mAcch.GetGroundH();
        }
    } else if (mCurProc == daPyProc_HOOKSHOT_FLY_e ||
        dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) ||
        checkModeFlg(ModeFlg_ROPE | ModeFlg_LADDER | ModeFlg_CAUGHT)
    ) {
        current.pos = sp8;
    } else if (mCurProc == daPyProc_DEMO_DOOR_OPEN_e ||
        mCurProc == daPyProc_HANG_WAIT_e ||
        mCurProc == daPyProc_HANG_MOVE_e ||
        mCurProc == daPyProc_HANG_UP_e ||
        mCurProc == daPyProc_HANG_START_e ||
        mCurProc == daPyProc_HANG_FALL_START_e
    ) {
        current.pos.x = sp8.x;
        current.pos.z = sp8.z;
    }
    
    int roomNo;
    if (mAcch.GetGroundH() != -G_CM3D_F_INF) {
        roomNo = setRoomInfo();
        m357C = m3580;
        m3580 = dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd);
        if (checkNoResetFlg0(daPyFlg0_UNK80000000)) {
            mCurrAttributeCode = dBgS_Attr_NORMAL_e;
        } else {
            mCurrAttributeCode = dComIfG_Bgsp()->GetAttributeCode(mAcch.m_gnd);
        }
        dStage_RoomCheck(&mAcch.m_gnd);
        checkFallCode();
        
        if (mAcch.ChkGroundHit()) {
            if (!checkModeFlg(ModeFlg_HANG) && (mCurrAttributeCode == dBgS_Attr_LAVA_e || mCurrAttributeCode == dBgS_Attr_VOID_e)) {
                checkLavaFace(NULL, mCurrAttributeCode);
            } else {
                if (checkNoResetFlg0(daPyFlg0_UNK20000)) {
                    onResetFlg0(daPyRFlg0_AUTO_JUMP_LAND);
                }
                offNoResetFlg0(daPyFlg0_UNK20000);
                if (checkNoResetFlg0(daPyFlg0_UNK400000)) {
                    onResetFlg0(daPyRFlg0_ROPE_JUMP_LAND);
                }
                offNoResetFlg0(daPyFlg0_UNK400000);
                if (current.pos.y < 2000.0f && dComIfG_Bgsp()->GetSpecialCode(mAcch.m_gnd) != 1) {
                    cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
                    if (cBgW_CheckBGround(triPla->GetNP()->y)) {
                        offNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG);
                    }
                }
            }
            
            if (!checkNoResetFlg0((daPy_FLG0)(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) &&
                dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd)
            ) {
                dComIfG_Bgsp()->MoveBgTransPos(mAcch.m_gnd, true, &m3724, NULL, NULL);
            }
            
            if (checkNoResetFlg0(daPyFlg0_UNK80000000)) {
                mMtrlSndId = 0;
                m34E2 = 0;
            } else {
                mMtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);
                m34E2 = getGroundAngle(&mAcch.m_gnd, shape_angle.y);
            }
            
            if (checkModeFlg(ModeFlg_02000000)) {
                setShapeAngleOnGround();
            }
        } else {
            if (checkModeFlg(ModeFlg_SWIM) && m3580 == 4) {
                startRestartRoom(5, 0xC9, -1.0f, 0);
            }
            m34E2 = 0;
            if (mCurProc == daPyProc_DEMO_TOOL_e) {
                mMtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);
            } else if (mCurProc == daPyProc_SHIP_READY_e || mCurProc == daPyProc_SHIP_GET_OFF_e) {
                mMtrlSndId = 9;
            } else {
                mMtrlSndId = 0;
            }
        }
        
        if (mpSeAnmFrameCtrl) {
            f32 rate = mpSeAnmFrameCtrl->getRate();
            f32 frame = mpSeAnmFrameCtrl->getFrame();
            mJAIZelAnime.setAnimSound(&current.pos, frame, rate, mMtrlSndId, mReverb);
        }
        
        if (!daPy_lk_c::checkPlayerFly() &&
            mCurProc != daPyProc_DEMO_TOOL_e &&
            (m34C3 == 1 || m34C3 == 4 || m34C3 == 0xA || m34C3 == 9)
        ) {
            setStepsOffset();
        }
        
        u8 groupInfo = dComIfG_Bgsp()->GetGrpSoundId(mAcch.m_gnd);
        mDoAud_setLinkGroupInfo(groupInfo);
    } else {
        mRestartPoint = 0xFF;
        m34E2 = 0;
        mMtrlSndId = 0;
        m357C = m3580;
        m3580 = -1;
        mCurrAttributeCode = dBgS_Attr_UNK1B_e;
        roomNo = fopAcM_GetRoomNo(this);
        checkFallCode();
    }
    
    equip_actor = mActorKeepEquip.getActor();
    if (equip_actor) {
        equip_actor->tevStr.mRoomNo = tevStr.mRoomNo;
        equip_actor->tevStr.mEnvrIdxOverride = tevStr.mEnvrIdxOverride;
        equip_actor->current.roomNo = roomNo;
    }
    
    setWorldMatrix();
    setWaistAngle();
    
    if (m_old_fdata->getOldFrameFlg()) {
        footBgCheck();
    }
    
    if (mCurProc != daPyProc_DAMAGE_e) {
        cLib_addCalcAngleS(&mBodyAngle.z, 0, 4, 0xC00, 0x180);
        if (mCurProc != daPyProc_FAN_GLIDE_e) {
            setMoveSlantAngle();
        }
        if (!checkModeFlg(ModeFlg_SUBJECT)) {
            cLib_addCalcAngleS(&mBodyAngle.x, 0, 4, 0xC00, 0x180);
        }
        if (!checkModeFlg(ModeFlg_40000000)) {
            cLib_addCalcAngleS(&mBodyAngle.y, 0, 4, 0xC00, 0x180);
        }
    }
    
    setNeckAngle();
    setHatAngle();
    
    mpCLModelData->getJointNodePointer(0x00)->setMtxCalc(m_pbCalc[PART_UNDER_e]); // link_root joint
    mpCLModelData->getJointNodePointer(0x02)->setMtxCalc(m_pbCalc[PART_UPPER_e]); // body_chn joint
    mpCLModelData->getJointNodePointer(0x1D)->setMtxCalc(m_pbCalc[PART_UNDER_e]); // wash_chn joint
    
#if VERSION > VERSION_DEMO
    checkOriginalHatAnimation();
#endif
    
    static const Vec nsword_top = {45.0f, -31.0f, 0.0f};
    static const Vec msword_top = {57.0f, 48.0f, 0.0f};
    static const Vec boomerang_catch = {12.5f, 47.5f, 36.6f};
    static const Vec hookshot_root = {22.0f, 0.0f, 0.0f};
    static const Vec hammer_top = {160.0f, 70.0f, 0.0f};
    static const Vec hammer_root = {8.0f, 0.0f, 0.0f};
    static const Vec fan_top = {55.0f, 0.0f, 0.0f};
    static const Vec head_offset = {40.0f, 0.0f, 0.0f};
    
    mpCLModel->calc();
    cMtx_multVec(mpCLModel->getAnmMtx(0x0F), &head_offset, &mHeadTopPos);
    checkRoofRestart();
    mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x08), &mLeftHandPos);
    mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x0C), &mRightHandPos);
    cMtx_multVec(mpCLModel->getAnmMtx(0x00), &boomerang_catch, &m36F4);
    cMtx_multVec(mpCLModel->getAnmMtx(0x08), &hookshot_root, &mHookshotRootPos);
    mpKatsuraModel->setBaseTRMtx(mpCLModel->getAnmMtx(0x0F));
    mpKatsuraModel->calc();
    mpYamuModel->setBaseTRMtx(mpCLModel->getAnmMtx(0x0F));
    mpYamuModel->calc();
    setItemModel();
    
    if (mCurProc == daPyProc_CUT_F_e || mCurProc == daPyProc_BT_VERTICAL_JUMP_CUT_e) {
        if (checkNormalSwordEquip()) {
            mpSwordTipStabModel->setBaseTRMtx(mpEquipItemModel->getAnmMtx(0x03));
        } else {
            mpSwordTipStabModel->setBaseTRMtx(mpEquipItemModel->getAnmMtx(0x04));
        }
    }
    
    cMtx_multVec(mpCLModel->getAnmMtx(0x13), &l_eye_offset, &eyePos);
    
    m36D0 = mSwordTopPos;
    m36DC = m36C4;
    
    if (mEquipItem == daPyItem_BOKO_e
#if VERSION > VERSION_DEMO
        && mActorKeepEquip.getActor()
#endif
    ) {
        daBoko_c* boko = static_cast<daBoko_c*>(mActorKeepEquip.getActor());
        boko->getTopPos(&mSwordTopPos);
        boko->getBlurRootPos(&m36C4);
    } else if (mEquipItem == dItem_SKULL_HAMMER_e) {
        cMtx_multVec(mpEquipItemModel->getBaseTRMtx(), &hammer_top, &mSwordTopPos);
        cMtx_multVec(mpEquipItemModel->getBaseTRMtx(), &hammer_root, &m36C4);
    } else if (mEquipItem == daPyItem_SWORD_e) {
        if (checkNormalSwordEquip()) {
            cMtx_multVec(mpEquipItemModel->getAnmMtx(0x01), &nsword_top, &mSwordTopPos);
            mDoMtx_multVecZero(mpEquipItemModel->getAnmMtx(0x02), &m36C4);
        } else {
            mDoMtx_multVecZero(mpEquipItemModel->getAnmMtx(0x01), &m36C4);
            cMtx_multVec(mpEquipItemModel->getAnmMtx(0x01), &msword_top, &mSwordTopPos);
        }
    } else if (mCurProc == daPyProc_FAN_SWING_e) {
        mDoMtx_multVecZero(mpEquipItemModel->getBaseTRMtx(), &m36C4);
        cMtx_multVec(mpEquipItemModel->getAnmMtx(0x06), &fan_top, &mSwordTopPos);
    } else {
        mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x0D), &m36C4);
        mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x0D), &mSwordTopPos);
    }
    
    checkLightHit();
    setFootEffect();
    setCollision();
    setAttentionPos();
    setGrabItemPos();
    setWaterRipple();
    setAuraEffect();
    setHammerWaterSplash();
    setLightSaver();
    
    if (!checkNoResetFlg0((daPy_FLG0)(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000))) {
        if (mAcch.ChkGroundHit() && !daPy_lk_c::checkPlayerFly()) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e | dEvtCnd_CANDOOR_e | dEvtCnd_CANGETITEM_e | dEvtCnd_UNK10_e | dEvtCnd_CANCATCH_e);
        } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) || (checkModeFlg(ModeFlg_SWIM) && checkNoResetFlg0(daPyFlg0_UNK100))) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
        }
    }
#if VERSION > VERSION_DEMO
    eventInfo.onCondition(dEvtCnd_CANGETITEM_e);
#endif
    
    JPABaseEmitter* emitter = mSmokeEcallBack.getEmitter();
    if (emitter) {
        emitter->setGlobalRTMatrix(mpCLModel->getAnmMtx(0x23));
    }
    
    setWaterDrop();
    
    if (daPy_dmEcallBack_c::getTimer() > 0) {
        daPy_dmEcallBack_c::decTimer();
        if (daPy_dmEcallBack_c::checkFlame()) {
            seStartOnlyReverb(JA_SE_LK_BURNING);
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x00), &mLightInfluence.mPos);
            mLightInfluence.mPower = 150.0f;
        } else if (daPy_dmEcallBack_c::checkCurse()) {
            seStartOnlyReverb(JA_SE_LK_CURSE_BURNING);
        }
        if (daPy_dmEcallBack_c::getTimer() == 0) {
            endDamageEmitter();
        }
    }
    
    offNoResetFlg1((daPy_FLG1)(daPyFlg1_NPC_CALL_COMMAND | daPyFlg1_VINE_CATCH));
    
    if (dComIfGp_event_runCheck() || checkNoControll()) {
        dComIfGp_setDoStatus(dActStts_BLANK_e);
        dComIfGp_setRStatus(dActStts_BLANK_e);
    } else {
        if (dComIfGp_getDoStatus() == dActStts_UNK43) {
            dComIfGp_setDoStatus(dActStts_JUMP_e);
        }
#if VERSION > VERSION_DEMO
        if (checkResetFlg0(daPyRFlg0_UNK10000000)) {
            dComIfGp_setAStatus(dActStts_BLANK_e);
        }
#endif
    }
    offNoResetFlg1((daPy_FLG1)(daPyFlg1_UNK4 | daPyFlg1_FORCE_VOMIT_JUMP | daPyFlg1_FORCE_VOMIT_JUMP_SHORT | daPyFlg1_UNK10000000));
    
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        mDoAud_setLinkOnBoard(1);
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    } else {
        mDoAud_setLinkOnBoard(2);
        fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
    }
    
    mDoAud_setLinkHp(dComIfGs_getLife(), dComIfGs_getMaxLife());
    
    mShieldFrontRangeYAngle = shape_angle.y + mBodyAngle.y;
    mFace = daPyFace_UNKNOWN;
    
    if (checkConfuse()) {
        seStartMapInfo(JA_SE_LK_NOW_CURSE_PW);
    }
    
    if (checkBowAnime()) {
        dComIfGp_setPlayerStatus0(0, daPyStts0_BOW_AIM_e);
    } else {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_BOW_AIM_e);
    }
    
    mWhirlId = fpcM_ERROR_PROCESS_ID_e;
    
#if VERSION > VERSION_DEMO
    l_debug_keep_pos = current.pos;
    l_debug_shape_angle = shape_angle;
    l_debug_current_angle = current.angle;
#endif
    
    return TRUE;
}

/* 80122D30-80122D50       .text daPy_Execute__FP9daPy_lk_c */
static BOOL daPy_Execute(daPy_lk_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->execute();
}

/* 80122D50-80122D58       .text daPy_IsDelete__FP9daPy_lk_c */
static BOOL daPy_IsDelete(daPy_lk_c*) {
    return TRUE;
}

/* 80122D58-80123058       .text playerDelete__9daPy_lk_cFv */
BOOL daPy_lk_c::playerDelete() {
    int i;
    for (i = 0; i < (int)ARRAY_SIZE(mFootEffect); i++) {
        mFootEffect[i].getSmokeCallBack()->remove();
        mFootEffect[i].getOtherCallBack()->remove();
    }
    mFanSwingCb.deleteCallBack();
    m338C.end();
    m33A8.end();
    m3280.remove();
    m334C.end();
    m336C.end();
    mSwimTailEcallBack[0].remove();
    mSwimTailEcallBack[1].remove();
    m32E4.end();
    m32F0.end();
    m33E8.end();
    mSmokeEcallBack.remove();
    m331C.remove();
    m332C.remove();
    m333C.remove();
    m3400.end();
    m3410.end();
    m3438.end();
    m342C.end();
    m3454.end();
    m3460[0].end();
    m3460[1].end();
    
    endDamageEmitter();
    dKy_plight_cut(&mLightInfluence);
    mDoAud_seDeleteObject(&mSwordTopPos);
    mDoAud_seDeleteObject(&mRopePos);
    mDoAud_seDeleteObject(&m338C.getPos());
    mDoAud_seDeleteObject(mFanWindCps.GetEndP());
    
    for (i = 0; i < (int)ARRAY_SIZE(m_anm_heap_under); i++) {
        mDoExt_destroySolidHeap(m_anm_heap_under[i].mpAnimeHeap);
    }
    for (i = 0; i < (int)ARRAY_SIZE(m_anm_heap_upper); i++) {
        mDoExt_destroySolidHeap(m_anm_heap_upper[i].mpAnimeHeap);
    }
    
    mDoExt_destroySolidHeap(m_tex_anm_heap.mpAnimeHeap);
    mDoExt_destroySolidHeap(m_tex_scroll_heap.mpAnimeHeap);
    mDoExt_destroySolidHeap(mpItemHeaps[0]);
    mDoExt_destroySolidHeap(mpItemHeaps[1]);
    mDoExt_destroySolidHeap(mpItemAnimeHeap);
    
    mJAIZelAnime.stop();
    
    if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
        *mpCurrLinktex = mOtherLinktex;
    }
    
    dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
    dComIfGp_clearPlayerStatus1(0, daPyStts1_UNK40000_e);
    dComIfGp_setMetronomeOff();
    
    cancelNoDamageMode();
    
    return TRUE;
}

/* 80123058-80123078       .text daPy_Delete__FP9daPy_lk_c */
static BOOL daPy_Delete(daPy_lk_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->playerDelete();
}

/* 80123078-80123360       .text initTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::initTextureAnime() {
    m_tex_anm_heap.m_buffer = new(0x20) u8[0x1000];
    JUT_ASSERT(VERSION_SELECT(20789, 20789, 20869, 20869), m_tex_anm_heap.m_buffer != NULL);
    
    JKRReadIdxResource(m_tex_anm_heap.m_buffer, 0x1000, LKANM_BTP_TMABAA, dComIfGp_getAnmArchive());
    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(J3DAnmLoaderDataBase::load(m_tex_anm_heap.m_buffer));
    btp->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btp->getUpdateMaterialNum();
    m_texNoAnms = new J3DTexNoAnm[material_num];
    JUT_ASSERT(VERSION_SELECT(20805, 20805, 20885, 20885), m_texNoAnms != NULL);
    
    for (u16 i = 0; i < material_num; i++) {
        u16 matID = btp->getUpdateMaterialID(i);
        if (matID != 0xFFFF) {
            J3DMaterialAnm* mat_anm = new J3DMaterialAnm();
            JUT_ASSERT(VERSION_SELECT(20814, 20814, 20894, 20894), mat_anm != NULL);
            
            if (matID != 1 && matID != 4) {
                // Not eyeL or eyeR (i.e. it's mouth, mayuL, or mayuR)
                // Set the animation on the specified material
                mpCLModelData->getMaterialNodePointer(matID)->change();
                mpCLModelData->getMaterialNodePointer(matID)->setMaterialAnm(mat_anm);
                if (matID != 0xE) {
                    // Not mouth (i.e. it's mayuL or mayuR)
                    // Additionally, set the animation on mayuLdamA and mayuLdamB or mayuRdamA and mayuRdamB
                    mpCLModelData->getMaterialNodePointer(matID+1)->change();
                    mpCLModelData->getMaterialNodePointer(matID+1)->setMaterialAnm(mat_anm);
                    mpCLModelData->getMaterialNodePointer(matID+2)->change();
                    mpCLModelData->getMaterialNodePointer(matID+2)->setMaterialAnm(mat_anm);
                }
            } else {
                // eyeL or eyeR
                // Don't the animation on the specified material
                // Instead, set it on eyeLdamA and eyeLdamB or eyeRdamA and eyeRdamB
                mpCLModelData->getMaterialNodePointer(matID+1)->change();
                mpCLModelData->getMaterialNodePointer(matID+1)->setMaterialAnm(mat_anm);
                mpCLModelData->getMaterialNodePointer(matID+2)->change();
                mpCLModelData->getMaterialNodePointer(matID+2)->setMaterialAnm(mat_anm);
            }
        }
        
        m_texNoAnms[i].setAnmIndex(i);
    }
}

/* 80123360-80123830       .text initTextureScroll__9daPy_lk_cFv */
void daPy_lk_c::initTextureScroll() {
    m_tex_scroll_heap.m_buffer = new(0x20) u8[0x800];
    JUT_ASSERT(VERSION_SELECT(20757, 20864, 20944, 20944), m_tex_scroll_heap.m_buffer != NULL);
    
    JKRReadIdxResource(m_tex_scroll_heap.m_buffer, 0x800, LKANM_BTK_TMABA, dComIfGp_getAnmArchive());
    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(m_tex_scroll_heap.m_buffer));
    btk->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btk->getUpdateMaterialNum();
    JUT_ASSERT(VERSION_SELECT(20771, 20878, 20958, 20958), material_num == 2);
    
    m_texMtxAnm = new J3DTexMtxAnm[material_num];
    JUT_ASSERT(VERSION_SELECT(20774, 20881, 20961, 20961), m_texMtxAnm != NULL);
    
    for (u16 no = 0; no < material_num; no++) {
        u16 matID = btk->getUpdateMaterialID(no);
        if (matID == 0xFFFF) {
            continue;
        }
        
        m_tex_eye_scroll[no] = new daPy_matAnm_c();
        JUT_ASSERT(VERSION_SELECT(20785, 20892, 20972, 20972), m_tex_eye_scroll[no] != NULL);
        
        mpCLModelData->getMaterialNodePointer(matID)->change();
        mpCLModelData->getMaterialNodePointer(matID)->setMaterialAnm(m_tex_eye_scroll[no]);
        
        J3DMaterial* mtl = mpCLModelData->getMaterialNodePointer(matID);
        u8 texMtxID = btk->getUpdateTexMtxID(no);
        if (texMtxID == 0xFF) {
            continue;
        }
        
        J3DTexMtx* tmtx;
        if (mtl->getTexMtx(texMtxID) == NULL) {
            tmtx = new J3DTexMtx();
            JUT_ASSERT(VERSION_SELECT(20797, 20904, 20984, 20984), tmtx != NULL);
            mtl->setTexMtx(texMtxID, tmtx);
        }
        if (mtl->getTexCoord(texMtxID) != NULL) {
            mtl->getTexCoord(texMtxID)->setTexGenMtx(GX_TEXMTX0 + (texMtxID & 0xFF) * 3);
        }
        tmtx = mtl->getTexMtx(texMtxID);
        
        m_texMtxAnm[no].setAnmTransform(btk);
        m_texMtxAnm[no].setAnmIndex(no);
        
        J3DTexMtxInfo& tmtxinfo = tmtx->getTexMtxInfo();
        tmtxinfo.mInfo = (tmtxinfo.mInfo & 0x7F) | btk->getTexMtxCalcType() << 7;
        tmtxinfo.mCenter.x = btk->getSRTCenter(no).x;
        tmtxinfo.mCenter.y = btk->getSRTCenter(no).y;
        tmtxinfo.mCenter.z = btk->getSRTCenter(no).z;
        
        JUT_ASSERT(VERSION_SELECT(20814, 20921, 21001, 21001), mtl->getMaterialAnm() != NULL);
        
        mtl->getMaterialAnm()->setTexMtxAnm(texMtxID, &m_texMtxAnm[no]);
    }
}

/* 80123834-8012469C       .text createHeap__9daPy_lk_cFv */
BOOL daPy_lk_c::createHeap() {
    J3DModelData* tmp_modelData;
    J3DAnmTransform* bck;
    J3DAnmTevRegKey* brk;
    int ret;
    
    mpCLModelData = initModel(&mpCLModel, LINK_BDL_CL, 0x37221222);
    tmp_modelData = initModel(&mpHandsModel, LINK_BDL_HANDS, 0x37221222);
    tmp_modelData = initModel(&mpKatsuraModel, LINK_BDL_KATSURA, 0x37221222);
    tmp_modelData = initModel(&mpYamuModel, LINK_BDL_YAMU, 0x37221222);
    tmp_modelData = initModel(&mpPringModel, LINK_BDL_PRING, 0x37221222);
    tmp_modelData = initModel(&mpSwgripaModel, LINK_BDL_SWGRIPA, 0x37221222);
    
    tmp_modelData = initModel(&mpSwgripmsModel, LINK_BDL_SWGRIPMS, 0x37221222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_SWGRIPMSAB);
    ret = mSwgripmsabBckAnim.init(mpSwgripmsModel->getModelData(), bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(VERSION_SELECT(20966, 20966, 21046, 21046), FALSE); }
    mpTswgripmsabBrk = entryBrk(tmp_modelData, LINK_BRK_TSWGRIPMSAB);
    mpTswgripmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSWGRIPMS);
    
    tmp_modelData = initModel(&mpPodmsModel, LINK_BDL_PODMS, 0x37221222);
    
    tmp_modelData = initModel(&mpShaModel, LINK_BDL_SHA, 0x37221222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_ATNGSHA);
    ret = mAtngshaBck.init(mpShaModel->getModelData(), bck, false, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(VERSION_SELECT(20983, 20983, 21063, 21063), FALSE); }
    
    tmp_modelData = initModel(&mpShmsModel, LINK_BDL_SHMS, 0x37221222);
    mpTshmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSHMS);
    J3DSkinDeform* shmsSkinDeform = new J3DSkinDeform();
    if (!shmsSkinDeform) { JUT_ASSERT(VERSION_SELECT(20997, 20997, 21077, 21077), FALSE); }
    if (mpShmsModel->setSkinDeform(shmsSkinDeform, 1) != J3DErrType_Success ) { JUT_ASSERT(VERSION_SELECT(21000, 21000, 21080, 21080), FALSE); }
    
    tmp_modelData = initModel(&mpYmsls00Model, LINK_BDL_YMSLS00, 0x13000222);
    mpYmsls00Btk = entryBtk(tmp_modelData, LINK_BTK_YMSLS00);
    
    tmp_modelData = initModel(&mpHbootsModels[0], LINK_BDL_HBOOTS, 0x37221222);
    tmp_modelData = initModel(&mpHbootsModels[1], LINK_BDL_HBOOTS, 0x37221222);
    
    tmp_modelData = initModel(&mpSuimenMunyaModel, LINK_BDL_SUIMEN_MUNYA, 0x11001222);
    mpSuimenMunyaBtk = entryBtk(tmp_modelData, LINK_BTK_SUIMEN_MUNYA);
    
    tmp_modelData = initModel(&mpYuchw00Model, LINK_BDL_YUCHW00, 0x13000222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_YUCHW00);
    ret = mYuchw00Bck.init(tmp_modelData, bck, 1, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(VERSION_SELECT(21033, 21033, 21113, 21113), FALSE); }
    mpYuchw00Btk = entryBtk(tmp_modelData, LINK_BTK_YUCHW00);
    mpYuchw00Brk = entryBrk(tmp_modelData, LINK_BRK_YUCHW00);
    mpYuchw00Brk->setFrame(mpYuchw00Brk->getFrameMax()-0.001f);
    
    tmp_modelData = initModel(&mpYbafo00Model, LINK_BDL_YBAFO00, 0x13000222);
    mpYbafo00Btk = entryBtk(tmp_modelData, LINK_BTK_YBAFO00);
    mpYbafo00Btk->setFrame(mpYbafo00Btk->getFrameMax()-0.001f);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_YAURA00));
    JUT_ASSERT(VERSION_SELECT(21050, 21050, 21130, 21130), tmp_modelData != NULL);
    daPy_aura_c* aura_p = mMagicArmorAuraEntries;
    for (int i = 0; i < 6; i++) {
        aura_p->setModel(mDoExt_J3DModel__create(tmp_modelData, 0x00080000, 0x11001222));
        JUT_ASSERT(VERSION_SELECT(21059, 21059, 21139, 21139), aura_p->getModel() != NULL);
        aura_p++;
    }
    mpYaura00Btk = entryBtk(tmp_modelData, LINK_BTK_YAURA00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YAURA00_R);
    ret = mYaura00rBrk.init(tmp_modelData, brk, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(VERSION_SELECT(21067, 21067, 21147, 21147), FALSE); }
    mYaura00rBrk.entryFrame(0.0f);
    
    tmp_modelData = initModel(&mpYmgcs00Model, LINK_BDL_YMGCS00, 0x11001222);
    mpYmgcs00Btk = entryBtk(tmp_modelData, LINK_BTK_YMGCS00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YMGCS00_MS);
    ret = mYmgcs00Brk.init(tmp_modelData, brk, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(VERSION_SELECT(21081, 21081, 21161, 21161), FALSE); }
    mYmgcs00Brk.entryFrame(0.0f);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_BOMB));
    JUT_ASSERT(VERSION_SELECT(21089, 21089, 21169, 21169), tmp_modelData != NULL);
    mpBombBrk = entryBrk(tmp_modelData, LINK_BRK_BOMB);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GWP00));
    JUT_ASSERT(VERSION_SELECT(21096, 21096, 21176, 21176), tmp_modelData != NULL);
    mpGwp00BrkData = entryBrk(tmp_modelData, LINK_BRK_GWP00);
    mpGwp00BtkData = entryBtk(tmp_modelData, LINK_BTK_GWP00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROW));
    JUT_ASSERT(VERSION_SELECT(21104, 21104, 21184, 21184), tmp_modelData != NULL);
    mpIceArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TTIPICE);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROWGLITTER));
    JUT_ASSERT(VERSION_SELECT(21111, 21111, 21191, 21191), tmp_modelData != NULL);
    mpLightArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TARROWGLITTER);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER00));
    JUT_ASSERT(VERSION_SELECT(21118, 21118, 21198, 21198), tmp_modelData != NULL);
    mpGicer00Btk = entryBtk(tmp_modelData, LINK_BTK_GICER00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER01));
    JUT_ASSERT(VERSION_SELECT(21125, 21125, 21205, 21205), tmp_modelData != NULL);
    mpGicer01Btk = entryBtk(tmp_modelData, LINK_BTK_GICER01);
    
    const int numCLJoints = 0x2A;
    m_old_fdata = new mDoExt_MtxCalcOldFrame(new J3DTransformInfo[numCLJoints], new Quaternion[numCLJoints]);
    JUT_ASSERT(VERSION_SELECT(21153, 21153, 21233, 21233), m_old_fdata != NULL);
    
    m_pbCalc[PART_UNDER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUnder), mAnmRatioUnder);
    JUT_ASSERT(VERSION_SELECT(21159, 21159, 21239, 21239), m_pbCalc[PART_UNDER_e] != NULL);
    
    m_pbCalc[PART_UPPER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUpper), mAnmRatioUpper);
    JUT_ASSERT(VERSION_SELECT(21165, 21165, 21245, 21245), m_pbCalc[PART_UPPER_e] != NULL);
    
    initTextureScroll();
    initTextureAnime();
    
    m_HIO = new daPy_HIO_c();
    JUT_ASSERT(VERSION_SELECT(21174, 21174, 21254, 21254), m_HIO != NULL);
    
    m_anm_heap_under[UNDER_MOVE0_e].m_buffer = new(0x20) u8[0xB400];
    JUT_ASSERT(VERSION_SELECT(21179, 21179, 21259, 21259), m_anm_heap_under[UNDER_MOVE0_e].m_buffer != NULL);
    
    m_sanm_buffer = new(0x20) u8[0x200];
    JUT_ASSERT(VERSION_SELECT(21186, 21186, 21266, 21266), m_sanm_buffer != NULL);
    
    m_item_bck_buffer = new(0x20) u8[0x1000];
    JUT_ASSERT(VERSION_SELECT(21189, 21189, 21269, 21269), m_item_bck_buffer != NULL);
    
    return TRUE;
}

/* 8012469C-801249F8       .text createAnimeHeap__9daPy_lk_cFPP12JKRSolidHeapQ29daPy_lk_c14daPy_HEAP_TYPE */
void daPy_lk_c::createAnimeHeap(JKRSolidHeap** pHeap, daPy_HEAP_TYPE heapType) {
    u32 heapSize;
    // TODO: Should these heap sizes be sizeof()s instead of magic numbers?
    if (heapType == HEAP_TYPE_ITEM_ANIME_e) {
        heapSize = 0x50;
    } else if (heapType == HEAP_TYPE_UNDER_UPPER_e || heapType == HEAP_TYPE_TEXTURE_ANIME_e) {
        heapSize = 0x40;
    } else { // heapType == HEAP_TYPE_TEXTURE_SCROLL_e
        heapSize = 0xA0;
    }
    
    *pHeap = mDoExt_createSolidHeapFromGameToCurrent(heapSize, 0x20);
    
    if (heapType == HEAP_TYPE_ITEM_ANIME_e) {
        mDoExt_transAnmBas* tmp_trans_bas = new mDoExt_transAnmBas(NULL);
        JUT_ASSERT(VERSION_SELECT(21227, 21227, 21307, 21307), tmp_trans_bas != NULL);
    } else if (heapType == HEAP_TYPE_UNDER_UPPER_e) {
        J3DAnmTransformKey* tmp_trans = new J3DAnmTransformKey;
        JUT_ASSERT(VERSION_SELECT(21230, 21230, 21310, 21310), tmp_trans != NULL);
    } else if (heapType == HEAP_TYPE_TEXTURE_ANIME_e) {
        J3DAnmTexPattern* tmp_tp = new J3DAnmTexPattern;
        JUT_ASSERT(VERSION_SELECT(21233, 21233, 21313, 21313), tmp_tp != NULL);
    } else { // heapType == HEAP_TYPE_TEXTURE_SCROLL_e
        J3DAnmTextureSRTKey* tmp_tk = new J3DAnmTextureSRTKey;
        JUT_ASSERT(VERSION_SELECT(21236, 21236, 21316, 21316), tmp_tk != NULL);
    }
    
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(*pHeap);
}

/* 80124A40-80124B30       .text initModel__9daPy_lk_cFPP8J3DModeliUl */
J3DModelData* daPy_lk_c::initModel(J3DModel** i_model, int i_fileIndex, u32 i_differedDlistFlag) {
    J3DModelData* tmp_modelData;
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, i_fileIndex));
    JUT_ASSERT(VERSION_SELECT(21260, 21260, 21340, 21340), tmp_modelData != NULL);
    *i_model = mDoExt_J3DModel__create(tmp_modelData, 0x00080000, i_differedDlistFlag);
    JUT_ASSERT(VERSION_SELECT(21264, 21264, 21344, 21344), *i_model != NULL);
    return tmp_modelData;
}

/* 80124B30-80124BE4       .text entryBtk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTextureSRTKey* daPy_lk_c::entryBtk(J3DModelData* param_1, int param_2) {
    J3DAnmTextureSRTKey* btk_anm =
        static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(l_arcName, param_2));
    JUT_ASSERT(VERSION_SELECT(21293, 21293, 21373, 21373), btk_anm != NULL);
    btk_anm->searchUpdateMaterialID(param_1);
    param_1->entryTexMtxAnimator(btk_anm);
    btk_anm->setFrame(0.0f);
    return btk_anm;
}

/* 80124BE4-80124C98       .text entryBrk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTevRegKey* daPy_lk_c::entryBrk(J3DModelData* param_1, int param_2) {
    J3DAnmTevRegKey* brk_anm =
        static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(l_arcName, param_2));
    JUT_ASSERT(VERSION_SELECT(21315, 21315, 21395, 21395), brk_anm != NULL);
    brk_anm->searchUpdateMaterialID(param_1);
    param_1->entryTevRegAnimator(brk_anm);
    brk_anm->setFrame(0.0f);
    return brk_anm;
}

/* 80124C98-80125CC8       .text playerInit__9daPy_lk_cFv */
void daPy_lk_c::playerInit() {
    if (!fopAcM_entrySolidHeap(this, daPy_createHeap, 0xB0000)) {
        JUT_ASSERT(VERSION_SELECT(21350, 21350, 21430, 21430), FALSE);
    }
    
    fopAcM_SetMtx(this, mpCLModel->getBaseTRMtx());
    
    mpCLModel->setUserArea(reinterpret_cast<u32>(this));
    mpYmgcs00Model->setUserArea(reinterpret_cast<u32>(this));
    for (u16 i = 0; i < mpYmgcs00Model->getModelData()->getJointNum(); i++) {
        mpYmgcs00Model->getModelData()->getJointNodePointer(i)->setCallBack(daPy_auraCallback);
    }
    
    mpCLModelData->getJointNodePointer(0x01)->setCallBack(daPy_jointCallback0); // center joint
    mpCLModelData->getJointNodePointer(0x0D)->setCallBack(daPy_jointCallback0); // cl_podA joint
    mpCLModelData->getJointNodePointer(0x04)->setCallBack(daPy_jointCallback0); // chest_jnt joint
    mpCLModelData->getJointNodePointer(0x08)->setCallBack(daPy_jointCallback0); // cl_LhandA joint
    mpCLModelData->getJointNodePointer(0x0C)->setCallBack(daPy_jointCallback0); // cl_RhandA joint
    mpCLModelData->getJointNodePointer(0x1C)->setCallBack(daPy_jointCallback0); // hatC_jnt
    mpCLModelData->getJointNodePointer(0x0F)->setCallBack(daPy_jointCallback0); // head_jnt
    mpCLModelData->getJointNodePointer(0x00)->setCallBack(daPy_jointCallback0); // link_root joint
    mpCLModelData->getJointNodePointer(0x28)->setCallBack(daPy_jointCallback1); // cl_back joint
    
    m_pbCalc[PART_UNDER_e]->setUserArea(reinterpret_cast<u32>(this));
    m_pbCalc[PART_UNDER_e]->setBeforeCalc(daPy_jointBeforeCallback);
    m_pbCalc[PART_UNDER_e]->setAfterCalc(daPy_jointAfterCallback);
    m_pbCalc[PART_UPPER_e]->setUserArea(reinterpret_cast<u32>(this));
    m_pbCalc[PART_UPPER_e]->setBeforeCalc(daPy_jointBeforeCallback);
    m_pbCalc[PART_UPPER_e]->setAfterCalc(daPy_jointAfterCallback);
    
    int i;
    J3DMaterial* mtl = mpCLModelData->getJointNodePointer(0x13)->getMesh(); // cl_eye joint
    int zoff_blend_cnt = 0;
    int zoff_none_cnt = 0;
    int zon_cnt = 0;
    for (i = 0; i < 2; i++) {
        while (mtl) {
            mtl->setMaterialMode(1);
            if (mtl->getZMode()->getCompareEnable() == 0) {
                if ((u8)mtl->getBlend()->getType() == GX_BM_BLEND) {
                    mpZOffBlendShape[zoff_blend_cnt++] = mtl->getShape();
                    JUT_ASSERT(VERSION_SELECT(21406, 21406, 21486, 21486), zoff_blend_cnt <= 4);
                } else {
                    mpZOffNoneShape[zoff_none_cnt++] = mtl->getShape();
                    JUT_ASSERT(VERSION_SELECT(21410, 21410, 21490, 21490), zoff_none_cnt <= 4);
                }
            } else {
                mpZOnShape[zon_cnt++] = mtl->getShape();
                JUT_ASSERT(VERSION_SELECT(21414, 21414, 21494, 21494), zon_cnt <= 4);
            }
            mtl = mtl->getNext();
        }
        mtl = mpCLModelData->getJointNodePointer(0x15)->getMesh(); // cl_mayu joint
    }
    
    JUT_ASSERT(VERSION_SELECT(21421, 21421, 21501, 21501), zon_cnt == 4);
    JUT_ASSERT(VERSION_SELECT(21422, 21422, 21502, 21502), zoff_none_cnt == 4);
    JUT_ASSERT(VERSION_SELECT(21423, 21423, 21503, 21503), zoff_blend_cnt == 4);
    
    mpLhandShape = mpCLModelData->getJointNodePointer(0x08)->getMesh()->getShape(); // cl_LhandA joint
    mpRhandShape = mpCLModelData->getJointNodePointer(0x0C)->getMesh()->getShape(); // cl_RhandA joint
    J3DModelData* handsModelData = mpHandsModel->getModelData();
    for (u16 i = 0x01; i < 0x0B; i++) {
        handsModelData->getJointNodePointer(i)->getMesh()->getShape()->hide();
    }
    
    u32 buffer_start = reinterpret_cast<u32>(m_anm_heap_under[UNDER_MOVE0_e].m_buffer) + 0x2400;
    m_anm_heap_under[UNDER_MOVE1_e].m_buffer = reinterpret_cast<void*>(buffer_start);
    buffer_start = reinterpret_cast<u32>(m_anm_heap_under[UNDER_MOVE0_e].m_buffer) + 0x4800;
    m_anm_heap_upper[UPPER_MOVE0_e].m_buffer = reinterpret_cast<void*>(buffer_start);
    for (int i = UPPER_MOVE1_e; i <= UPPER_MOVE2_e; i++) {
        buffer_start = reinterpret_cast<u32>(m_anm_heap_upper[UPPER_MOVE0_e].m_buffer) + i*0x2400;
        m_anm_heap_upper[i].m_buffer = reinterpret_cast<void*>(buffer_start);
    }
    
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, ARRAY_SIZE(mAcchCir), mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    mAcch.ClrWaterNone();
    mAcch.SetWaterCheckOffset(500.0f);
    mAcch.OnLineCheck();
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(125.0f);
    mMaxNormalSpeed = m_HIO->mMove.m.field_0x18;
    gravity = m_HIO->mAutoJump.m.field_0xC;
    maxFallSpeed = m_HIO->mAutoJump.m.field_0x10;
    mAcchCir[0].SetWall(30.1f, 35.0f);
    mAcchCir[1].SetWall(89.9f, 35.0f);
    mAcchCir[2].SetWall(125.0f, 35.0f);
    mHeadTopPos.setall(0.0f);
    mHeight = 125.0f;
    mEquipItem = daPyItem_NONE_e;
    mKeepItem = daPyItem_NONE_e;
    mCameraInfoIdx = dComIfGp_getPlayerCameraID(0);
    mpAttention = &dComIfGp_getAttention();
    
    mStts.Init(120, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.OnTgShieldFrontRange();
    mShieldFrontRangeYAngle = shape_angle.y + mBodyAngle.y;
    mCyl.SetTgShieldFrontRangeYAngle(&mShieldFrontRangeYAngle);
    mWindCyl.Set(l_wind_cyl_src);
    mWindCyl.SetStts(&mStts);
    mLightCyl.Set(l_wind_cyl_src);
    mLightCyl.SetStts(&mStts);
    mLightCyl.SetTgType(AT_TYPE_LIGHT);
    mAtCps[0].Set(l_at_cps_src);
    mAtCps[0].SetStts(&mStts);
    mAtCps[1].Set(l_at_cps_src);
    mAtCps[1].SetStts(&mStts);
    mAtCps[2].Set(l_at_cps_src);
    mAtCps[2].SetStts(&mStts);
    mAtCyl.Set(l_at_cyl_src);
    mAtCyl.SetStts(&mStts);
    mFanWindCps.Set(l_fan_wind_cps_src);
    mFanWindCps.SetR(70.0f);
    mFanWindCps.SetStts(&mStts);
    mFanWindSph.Set(l_fan_wind_sph_src);
    mFanWindSph.SetStts(&mStts);
    mFanLightCps.Set(l_fan_wind_cps_src);
    mFanLightCps.SetStts(&mStts);
    mFanLightCps.SetAtType(AT_TYPE_LIGHT);
    mFanLightCps.SetR(20.0f);
    
    for (int i = 0; i < (int)ARRAY_SIZE(m_anm_heap_under); i++) {
        createAnimeHeap(&m_anm_heap_under[i].mpAnimeHeap, HEAP_TYPE_UNDER_UPPER_e);
        m_anm_heap_under[i].mIdx = -1;
        m_anm_heap_under[i].field_0x2 = -1;
        m_anm_heap_under[i].field_0x4 = -1;
    }
    for (int i = 0; i < (int)ARRAY_SIZE(m_anm_heap_upper); i++) {
        createAnimeHeap(&m_anm_heap_upper[i].mpAnimeHeap, HEAP_TYPE_UNDER_UPPER_e);
        m_anm_heap_upper[i].mIdx = -1;
        m_anm_heap_upper[i].field_0x2 = -1;
        m_anm_heap_upper[i].field_0x4 = -1;
    }
    createAnimeHeap(&m_tex_anm_heap.mpAnimeHeap, HEAP_TYPE_TEXTURE_ANIME_e);
    m_tex_anm_heap.mIdx = -1;
    m_tex_anm_heap.field_0x2 = -1;
    m_tex_anm_heap.field_0x4 = -1;
    m_tex_anm_heap.field_0x6 = -1;
    createAnimeHeap(&m_tex_scroll_heap.mpAnimeHeap, HEAP_TYPE_TEXTURE_SCROLL_e);
    m_tex_scroll_heap.mIdx = -1;
    m_tex_scroll_heap.field_0x2 = -1;
    m_tex_scroll_heap.field_0x4 = -1;
    m_tex_scroll_heap.field_0x6 = -1;
    mSeAnmIdx = -1;
    m34F0 = -1;
    
    mpItemHeaps[0] = mDoExt_createSolidHeapFromGameToCurrent(0xE600, 0x20);
    u8* dummy_data = new u8[0xE600];
    JUT_ASSERT(VERSION_SELECT(21571, 21571, 21651, 21651), dummy_data != NULL);
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(mpItemHeaps[0]);
    
    mpItemHeaps[1] = mDoExt_createSolidHeapFromGameToCurrent(0xE600, 0x20);
    dummy_data = new u8[0xE600];
    JUT_ASSERT(VERSION_SELECT(21577, 21577, 21657, 21657), dummy_data != NULL);
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(mpItemHeaps[1]);
    
    createAnimeHeap(&mpItemAnimeHeap, HEAP_TYPE_ITEM_ANIME_e);
    
    mActorKeepEquip.clearData();
    mActorKeepThrow.clearData();
    mActorKeepGrab.clearData();
    mActorKeepRope.clearData();
    m3628 = fpcM_ERROR_PROCESS_ID_e;
    mWhirlId = fpcM_ERROR_PROCESS_ID_e;
    mTactZevPartnerId = fpcM_ERROR_PROCESS_ID_e;
    m3630 = fpcM_ERROR_PROCESS_ID_e;
    
    ResTIMG* blur_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_BLUR);
    mSwBlur.mpTex = blur_img;
    
    current.angle.z = 0;
    shape_angle.z = 0;
    m3526 = 8;
    m3648.w = 1.0f;
    resetSeAnime();
    
    ResTIMG* tmp_tex = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_I4_BALL128B);
    JUT_ASSERT(VERSION_SELECT(21607, 21607, 21687, 21687), tmp_tex != NULL);
    mSightPacket.setSightTex(tmp_tex);
    ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_ROCK_MARK);
    JUT_ASSERT(VERSION_SELECT(21613, 21613, 21693, 21693), tmp_img != NULL);
    void* tmp_img_data = reinterpret_cast<void*>(reinterpret_cast<u32>(tmp_img) + tmp_img->imageOffset);
    mSightPacket.setLockTex(tmp_img_data);
    mSightPacket.setImage(tmp_img);
    
    int startMode = getStartMode();
    u8 lastMode = dComIfGs_getLastSceneMode();
    if (startMode == 0xE) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD4);
    } else if (startMode == 0xC) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD0);
    } else if (startMode == 0x6) {
        mEventIdx = dComIfGp_evmng_startDemo(0xCF);
    } else if (startMode == 0xA) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD2);
    } else if (startMode == 0xB) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD3);
    } else if (startMode == 0x9 || lastMode == 0x6) {
        mEventIdx = dComIfGp_evmng_startDemo(0xCB);
    } else if (startMode == 0x2 && (lastMode == 0x4 || lastMode == 0x5)) {
        mEventIdx = dComIfGp_evmng_startDemo(0xC9);
    } else if (startMode == 0xF) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD5);
    } else {
        mEventIdx = dComIfGp_evmng_startDemo(getStartEvent());
    }
    
    onNoResetFlg0(daPyFlg0_UNK100);
    mLavaGndChk.OffWaterGrp();
    mDemo.setStick(1.0f);
    endDamageEmitter();
    mMirrorPacket.init(NULL);
    
    mLightInfluence.mColor.r = 600;
    mLightInfluence.mColor.g = 400;
    mLightInfluence.mColor.b = 120;
    mLightInfluence.mFluctuation = 250.0f;
    mLightInfluence.mPos = current.pos;
    mLightInfluence.mPower = 0.0f;
    dKy_plight_set(&mLightInfluence);
    
    m352E = 900;
    mFace = daPyFace_UNKNOWN;
    m34DE = shape_angle.y;
    
    ResTIMG* linktex_casual = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_LINKTEXBCI4);
    int num_linktex_headers_seen = 0;
    J3DTexture* texture = mpCLModelData->getTexture();
    JUT_ASSERT(VERSION_SELECT(21684, 21684, 21764, 21764), texture != NULL);
    JUTNameTab* textureName = mpCLModelData->getTextureName();
    JUT_ASSERT(VERSION_SELECT(21686, 21686, 21766, 21766), textureName != NULL);
    for (u16 i = 0; i < texture->getNum(); i++) {
        const char* texName = textureName->getName(i);
        if (strcmp(texName, "linktexS3TC") != 0) {
            continue;
        }
        if (num_linktex_headers_seen == 0) {
            // Link's model's TEX1 section has two headers for the linktexS3TC texture.
            // They seem identical except the first has alpha enabled and the second does not.
            // The second is the one that is actually used, so we have to skip over the first one.
            num_linktex_headers_seen += 1;
            continue;
        }
        
        mpCurrLinktex = texture->getResTIMG(i);
        mOtherLinktex = *mpCurrLinktex;
        
        // Modify the linktexS3TC texture in Link's model to be the casual clothes texture.
        texture->setResTIMG(i, *linktex_casual);
        
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80) || dComIfGs_getClearCount() != 0) {
            onNoResetFlg1(daPyFlg1_CASUAL_CLOTHES);
        }
        if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
            break;
        }
        
        // If Link isn't wearing the casual clothes, then load the hero's clothes texture from the backup and swap them.
        ResTIMG casualLinktex = *mpCurrLinktex;
        *mpCurrLinktex = mOtherLinktex;
        mOtherLinktex = casualLinktex;
        break;
    }
}

/* 80125CC8-80125D30       .text phase_1__FP9daPy_lk_c */
cPhs_State phase_1(daPy_lk_c* i_this) {
    dComIfGp_setPlayer(0, i_this);
    dComIfGp_setLinkPlayer(i_this);

    fopAcM_setStageLayer(i_this);
    i_this->attention_info.flags = ~0;

    i_this->attention_info.position.x = i_this->current.pos.x;
    i_this->attention_info.position.y = i_this->current.pos.y + 125.0f;
    i_this->attention_info.position.z = i_this->current.pos.z;

    return cPhs_NEXT_e;
}

/* 80125D30-80125DB4       .text phase_2__FP9daPy_lk_c */
cPhs_State phase_2(daPy_lk_c* i_this) {
    cPhs_State result;

    if (dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0)) == NULL)  {
        result = cPhs_INIT_e;
    } else {
        fopAcM_SetupActor(i_this, daPy_lk_c);
        i_this->playerInit();

        result = cPhs_NEXT_e;
    }

    return result;
}

/* 80125DB4-80126F00       .text __ct__9daPy_lk_cFv */
daPy_lk_c::daPy_lk_c() {}

/* 80126F00-8012704C       .text __dt__15daPy_footData_cFv */
daPy_footData_c::~daPy_footData_c() {}

/* 8012704C-80127160       .text __ct__15daPy_footData_cFv */
daPy_footData_c::daPy_footData_c() {}

/* 80127160-80127B50       .text makeBgWait__9daPy_lk_cFv */
cPhs_State daPy_lk_c::makeBgWait() {
    cXyz local_38;
    cXyz local_44;
    cXyz local_50;

#if VERSION > VERSION_DEMO
    if ((int)m352E != 0) {
        m352E--;
    }
#endif

    mAcch.CrrPos(*dComIfG_Bgsp());

    if (
        mAcch.GetGroundH() == -G_CM3D_F_INF
    #if VERSION > VERSION_DEMO
        || (
            m352E != 0 && dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd) &&
            fopAcM_GetName(dComIfG_Bgsp()->GetActorPointer(mAcch.m_gnd)) == PROC_TBOX
        )
#endif
    ) {
        return cPhs_INIT_e;
    }

#if VERSION == VERSION_DEMO
    if (((fopAcM_GetParam(this) & 0x80) != 0)) {
        m352E--;
        if (m352E != 0) {
            if (!dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd) ||
                fopAcM_GetName(dComIfG_Bgsp()->GetActorPointer(mAcch.m_gnd)) != PROC_OBJ_IKADA)
            {
                return cPhs_INIT_e;
            }
            current.pos.y = mAcch.GetGroundH();
        }
    }
#else
    if (((fopAcM_GetParam(this) & 0x80) != 0) && m352E != 0) {
        if (!dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd) ||
            fopAcM_GetName(dComIfG_Bgsp()->GetActorPointer(mAcch.m_gnd)) != PROC_OBJ_IKADA)
        {
            return cPhs_INIT_e;
        }
        current.pos.y = mAcch.GetGroundH();
        m352E = 0;
    }
#endif

    setWaterY();
    u32 uVar5 = fopAcM_GetParam(this) & 0x40;
    if (uVar5 == 0) {
        dComIfGs_setRestartRoom(current.pos, shape_angle.y, getStartRoomNo());
    }
    setRoomInfo();
    int startMode = getStartMode();
    u8 sceneMode = dComIfGs_getLastSceneMode();
    if (startMode == 2 || startMode == 9 || sceneMode == 6 || (startMode == 5 && sceneMode == 1) ||
        (sceneMode == 5 &&
         (!strcmp(dComIfGp_getStartStageName(), "Pjavdou") || !strcmp(dComIfGp_getStartStageName(), "ShipD") ||
          (!strcmp(dComIfGp_getStartStageName(), "Siren") && fopAcM_GetRoomNo(this) == 0 && current.pos.z > 1400.0f &&
           current.pos.x < 400.0f && current.pos.x > -400.0f))))
    {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::MET_KORL)) {
            if (changeSwimProc()) {
                procSwimWait_init(0);
                m34C2 = 0;
            } else {
                procWait_init();
            }
        } else {
            daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
            if (ship == NULL) {
                return cPhs_INIT_e;
            }
#if VERSION > VERSION_JPN
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3E10)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3E01);
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3F80);
            }
#endif
            s16 sVar6;
            if (uVar5 != 0) {
                s16 sVar2 = shape_angle.y;
                sVar6 = sVar2 + 0x4000;
                m34DE = sVar2;
            } else {
                sVar6 = shape_angle.y;
            }
            ship->initStartPos(&current.pos, sVar6);
            if (ship->getSailOn()) {
                procShipSteer_init();
            } else {
                procShipPaddle_init();
            }
            if (uVar5 != 0) {
                procTactPlayEnd_init(-2);
            } else if (sceneMode == 6) {
                ship->setStartModeThrow();
            } else if (sceneMode == 4 || sceneMode == 5) {
                mDemo.setDemoType(4);
                mDoAud_subBgmStop();
                procShipRestart_init();
            } else if (startMode == 9) {
                ship->setStartModeWarp();
#if VERSION > VERSION_DEMO
                local_38.set(current.pos.x, current.pos.y + 1500.0f, current.pos.z);
                fpc_ProcID uVar8 = fopAcM_create(PROC_TORNADO, 2, &local_38, fopAcM_GetRoomNo(this));
                ship->setTactWarpID(uVar8);
#endif
            }
        }
    } else if (startMode == 4) {
        mDemo.setDemoType(4);
        mDoAud_bgmStart(JA_BGM_I_MAJU_JAIL);
        procLargeDamage_init(-7, 0, 0, 0);
    } else if (sceneMode == 4 || sceneMode == 5) {
        if (changeSwimProc()) {
            procSwimWait_init(0);
            m34C2 = 0;
        } else {
            current.pos.y = mAcch.GetGroundH();
            mDemo.setDemoType(4);
            mDoAud_subBgmStop();
            procLargeDamageUp_init(sceneMode == 4 ? -1 : -2, 1, 0, 0);
        }
    } else if (startMode == 1 || startMode == 5) {
        if (mEventIdx == 0xFF) {
            mVelocity = dComIfGs_getLastSceneSpeedF();
            mDemo.setDemoType(4);
            mDemo.setDemoMode(daPy_demo_c::DEMO_KEEP_e);
            mDemo.setMoveAngle(current.angle.y);
            mDemo.setTimer(0x23);
            if (changeSwimProc()) {
                if (startMode == 1) {
                    mVelocity = 0.5f * m_HIO->mSwim.m.field_0xC;
                }
                speedF = mVelocity;
                procSwimMove_init(0);
            } else if (startMode == 1) {
                mVelocity = m_HIO->mMove.m.field_0x2C * m_HIO->mMove.m.field_0x18;
                speedF = mVelocity;
                procMove_init();
            } else if (sceneMode == 2) {
                m34E8 = shape_angle.y;
                procCrawlMove_init(0, 0);
            } else if (sceneMode == 3) {
                shape_angle.y += 0x8000;
                current.angle.y = shape_angle.y;
                m34DE = shape_angle.y;
                m34E8 = shape_angle.y + 0x8000;
                procCrawlMove_init(0, 0);
            } else {
                if (mVelocity > m_HIO->mMove.m.field_0x18) {
                    mVelocity = m_HIO->mMove.m.field_0x18;
                }
                speedF = mVelocity;
                procMove_init();
            }
        } else if (changeSwimProc()) {
            procSwimWait_init(0);
            m34C2 = 0;
        } else {
            procWait_init();
        }
    } else if (startMode == 7) {
        local_44.set(current.pos.x + 200.0f * cM_ssin(shape_angle.y), 150.0f + current.pos.y,
                     current.pos.z + 200.0f * cM_scos(shape_angle.y));
        dComIfGs_setRestartRoom(local_44, shape_angle.y, getStartRoomNo());
        procVomitJump_init(1);
        mAcch.ClrGroundHit();
    } else if (startMode == 0xd) {
        procSmallJump_init(1);
    } else if (startMode == 0xf) {
        procSlowFall_init();
    } else if (startMode == 0xe) {
        mDemo.setDemoType(4);
        mDemo.setDemoMode(daPy_demo_c::DEMO_N_WAIT_e);
        procWait_init();
        csXyz auStack_58(0, 0, 0);
        fpc_ProcID fVar11 = fopAcM_createChild(PROC_FM, fopAcM_GetID(this), 0, &current.pos,
                                               fopAcM_GetRoomNo(this), &auStack_58, NULL, 0xFF, 0);
        if (fVar11 != fpcM_ERROR_PROCESS_ID_e) {
            onNoResetFlg0(daPyFlg0_NO_DRAW);
        }
    } else if (changeSwimProc()) {
        procSwimWait_init(0);
        m34C2 = 0;
    } else if (current.pos.y - mAcch.GetGroundH() > 30.1f) {
        procFall_init(1, 0.0f);
    } else {
        procWait_init();
    }
    m_old_fdata->initOldFrameMorf(0.0f, 0, 0x2A);
    setWorldMatrix();
    mpCLModelData->getJointNodePointer(0)->setMtxCalc(m_pbCalc[PART_UNDER_e]);
    mpCLModelData->getJointNodePointer(0x02)->setMtxCalc(m_pbCalc[PART_UPPER_e]);
    mpCLModelData->getJointNodePointer(0x1D)->setMtxCalc(m_pbCalc[PART_UNDER_e]);

#if VERSION > VERSION_DEMO
    checkOriginalHatAnimation();
    animeUpdate();
#endif

    mpCLModel->calc();
    mpKatsuraModel->setBaseTRMtx(mpCLModel->getAnmMtx(0xF));
    mpKatsuraModel->calc();
    mpYamuModel->setBaseTRMtx(mpCLModel->getAnmMtx(0xF));
    mpYamuModel->calc();
    setItemModel();
    mCyl.SetC(current.pos);
    setAttentionPos();
    m3580 = dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd);
    m357C = m3580;
    if (sceneMode == 4) {
        mDoMtx_multVecZero(mpCLModel->getAnmMtx(0), &local_50);
        dComIfGp_particle_setP1(dPa_name::ID_SCENE_8089, &local_50);
    }
    if ((dComIfGs_getLastSceneMode() & 0x8000) != 0) {
        changeDragonShield(0);
    } else {
        mTinkleShieldTimer = (s16)(dComIfGs_getLastSceneMode() >> 0x10);
    }

#if VERSION > VERSION_DEMO
    if ((dComIfGs_getLastSceneMode() & 0x4000) != 0) {
        onNoResetFlg1(daPyFlg1_SOUP_POWER_UP);
    }

    l_debug_keep_pos = current.pos;
    l_debug_shape_angle = shape_angle;
    l_debug_current_angle = current.angle;
#endif

    return cPhs_NEXT_e;
}

/* 80127B50-80127B70       .text phase_3__FP9daPy_lk_c */
cPhs_State phase_3(daPy_lk_c* i_this) {
    return i_this->makeBgWait();
}

/* 80127B70-80127BA0       .text daPy_Create__FP10fopAc_ac_c */
static cPhs_State daPy_Create(fopAc_ac_c* i_this) {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        (cPhs__Handler)phase_3,
        (cPhs__Handler)NULL,
    };
    daPy_lk_c* a_this = (daPy_lk_c*)i_this;

    return dComLbG_PhaseHandler(a_this->getPhase(), l_method, a_this);
}

/* 80127BA0-80127CC0       .text setSeAnime__9daPy_lk_cFPC14daPy_anmHeap_cP12J3DFrameCtrl */
void daPy_lk_c::setSeAnime(const daPy_anmHeap_c* anmHeap, J3DFrameCtrl* frameCtrl) {
    if (reinterpret_cast<JUTDataFileHeader*>(anmHeap->m_buffer)->mSeAnmOffset == -1) {
        resetSeAnime();
    } else if (mSeAnmIdx == anmHeap->mIdx && m34F0 == anmHeap->field_0x6 && mSeAnmRate * frameCtrl->getRate() >= 0.0f) {
        mpSeAnmFrameCtrl = frameCtrl;
    } else {
        JUTDataFileHeader* fileHeader = reinterpret_cast<JUTDataFileHeader*>(anmHeap->m_buffer);
        
        u32 data_size = fileHeader->mFileSize - fileHeader->mSeAnmOffset;
        const u32 l_sanm_buffer_size = 0x200;
        JUT_ASSERT(VERSION_SELECT(22228, 22228, 22318, 22318), data_size < l_sanm_buffer_size);
        
        u8* seAnmPtr = reinterpret_cast<u8*>(anmHeap->m_buffer) + fileHeader->mSeAnmOffset;
        cLib_memCpy(m_sanm_buffer, seAnmPtr, data_size);
        mpSeAnmFrameCtrl = frameCtrl;
        mSeAnmIdx = anmHeap->mIdx;
        m34F0 = anmHeap->field_0x6;
        mSeAnmRate = frameCtrl->getRate();
        initSeAnime();
    }
}

/* 80127CC0-80127DEC       .text initSeAnime__9daPy_lk_cFv */
void daPy_lk_c::initSeAnime() {
    if (mpSeAnmFrameCtrl) {
        s16 loop = mpSeAnmFrameCtrl->getLoop();
        u32 direction = mpSeAnmFrameCtrl->getRate() >= 0.0f ? 1 : -1;
        mJAIZelAnime.initActorAnimSound(m_sanm_buffer, direction, loop);
    }
    
    if (mpSeAnmFrameCtrl->getAttribute() == J3DFrameCtrl::EMode_LOOP) {
        f32 position = mpSeAnmFrameCtrl->getFrame() - mpSeAnmFrameCtrl->getRate();
        if (position <= mpSeAnmFrameCtrl->getStart()) {
            position = mpSeAnmFrameCtrl->getEnd() - position;
        } else if (position >= mpSeAnmFrameCtrl->getEnd()) {
            position = position - mpSeAnmFrameCtrl->getEnd();
        }
        mJAIZelAnime.setPlayPosition(position);
    }
}

/* 80127DEC-80127E08       .text resetSeAnime__9daPy_lk_cFv */
void daPy_lk_c::resetSeAnime() {
    mSeAnmIdx = -1;
    m34F0 = -1;
    mpSeAnmFrameCtrl = NULL;
}

/* 80127E08-8012821C       .text setMoveAnime__9daPy_lk_cFfffQ29daPy_lk_c8daPy_ANMQ29daPy_lk_c8daPy_ANMif */
int daPy_lk_c::setMoveAnime(f32 f27, f32 f28, f32 f25, daPy_ANM r27, daPy_ANM r28, int r29, f32 f29) {
    J3DAnmTransform* r3 = mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform();
    J3DFrameCtrl& frameCtrl0 = mFrameCtrlUnder[UNDER_MOVE0_e];
    J3DFrameCtrl& frameCtrl1 = mFrameCtrlUnder[UNDER_MOVE1_e];
    f32 f31;
    if ((m34C3 == 0 || m34C3 == 9) || m34C3 == 10) {
        f31 = 0.0f;
    } else {
        f31 = r3->getFrame() / r3->getFrameMax();
    }
    const daPy_anmIndex_c* r25 = getAnmData(r27);
    const daPy_anmIndex_c* r24 = getAnmData(r28);
    J3DAnmTransform* sp14;
    J3DAnmTransform* sp10;
    getUnderUpperAnime(r25, &sp14, &sp10, 0, 0x2400);
    J3DAnmTransform* sp0C;
    J3DAnmTransform* sp08;
    getUnderUpperAnime(r24, &sp0C, &sp08, 1, 0x2400);
    mAnmRatioUnder[UNDER_MOVE0_e].setRatio(1.0f - f27);
    mAnmRatioUnder[UNDER_MOVE1_e].setRatio(f27);
    mAnmRatioUpper[UPPER_MOVE0_e].setRatio(1.0f - f27);
    mAnmRatioUpper[UPPER_MOVE1_e].setRatio(f27);
    f32 f3 = sp14->getFrameMax();
    f32 f26 = sp0C->getFrameMax();
    f32 f30 = 1.0f / f3;
    f27 = (f28 + (f27 * (((f25 * f3) / f26) - f28)));
    setFrameCtrl(&frameCtrl0, sp14->getAttribute(), 0, f3, f27, (f31 * f3));
    sp14->setFrame(frameCtrl0.getFrame());
    setFrameCtrl(&frameCtrl1, sp0C->getAttribute(), 0, f26, (f30 * (f27 * f26)),
                 (f31 * f26));
    sp0C->setFrame(frameCtrl1.getFrame());
    mAnmRatioUnder[UNDER_MOVE0_e].setAnmTransform(sp14);
    mAnmRatioUnder[UNDER_MOVE1_e].setAnmTransform(sp0C);
    if (sp10 != NULL) {
        f32 f2 = sp10->getFrameMax();
        mAnmRatioUpper[UPPER_MOVE0_e].setAnmTransform(sp10);
        setFrameCtrl(&mFrameCtrlUpper[UPPER_MOVE0_e], sp10->getAttribute(), 0, f2,
                     (f30 * (f27 * f2)), (f31 * f2));
        sp10->setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getFrame());
    } else {
        mAnmRatioUpper[UPPER_MOVE0_e].setAnmTransform(sp14);
    }
    if (sp08 != NULL) {
        f32 f2 = sp08->getFrameMax();
        mAnmRatioUpper[UPPER_MOVE1_e].setAnmTransform(sp08);
        setFrameCtrl(&mFrameCtrlUpper[UPPER_MOVE1_e], sp08->getAttribute(), 0, f2,
                     (f30 * (f27 * f2)), (f31 * f2));
        sp08->setFrame(mFrameCtrlUpper[UPPER_MOVE1_e].getFrame());
    } else {
        mAnmRatioUpper[UPPER_MOVE1_e].setAnmTransform(sp0C);
    }
    if (f29 >= 0.0f) {
        m_old_fdata->initOldFrameMorf(f29, 0, 0x2A);
    }
    if (mDirection == DIR_BACKWARD ||
        (mCurProc == daPyProc_ROPE_SWING_e && !checkModeFlg(ModeFlg_00000400)))
    {
        setTextureAnime(mAnmDataTable[r28].mTexAnmIdx, 0);
    } else {
        setTextureAnime(mAnmDataTable[r27].mTexAnmIdx, 0);
    }
    if (r29 == 5 || r29 == 2) {
        setSeAnime(&m_anm_heap_under[UNDER_MOVE0_e], &frameCtrl0);
    } else {
        setSeAnime(&m_anm_heap_under[UNDER_MOVE1_e], &frameCtrl1);
    }
    m34C3 = r29;
    return true;
}

/* 8012821C-80128494       .text setSingleMoveAnime__9daPy_lk_cFQ29daPy_lk_c8daPy_ANMffsf */
BOOL daPy_lk_c::setSingleMoveAnime(daPy_ANM anm, f32 rate, f32 start, s16 end, f32 param_5) {
    const daPy_anmIndex_c* anmData = getAnmData(anm);
    J3DAnmTransform* under_bck;
    J3DAnmTransform* upper_bck;
    getUnderUpperAnime(anmData, &under_bck, &upper_bck, 0, 0xB400);
    m_anm_heap_under[UNDER_MOVE1_e].mIdx = -1;
    m_anm_heap_upper[UPPER_MOVE1_e].mIdx = -1;
    mAnmRatioUpper[UPPER_MOVE0_e].setRatio(1.0f);
    mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);
    mAnmRatioUnder[UNDER_MOVE0_e].setRatio(1.0f);
    mAnmRatioUnder[UNDER_MOVE1_e].setRatio(0.0f);
    mAnmRatioUnder[UNDER_MOVE0_e].setAnmTransform(under_bck);
    mAnmRatioUnder[UNDER_MOVE1_e].setAnmTransform(NULL);
    
    s16 endUnder = end < 0 ? under_bck->getFrameMax() : end;
    f32 frame = rate < 0.0f ? endUnder-0.001f : start;
    setFrameCtrl(&mFrameCtrlUnder[UNDER_MOVE0_e], under_bck->getAttribute(), start, endUnder, rate, frame);
    under_bck->setFrame(frame);
    
    if (upper_bck) {
        mAnmRatioUpper[UPPER_MOVE0_e].setAnmTransform(upper_bck);
        s16 endUpper = end < 0 ? upper_bck->getFrameMax() : end;
        frame = rate < 0.0f ? endUpper-0.001f : start;
        // Note: It uses under_bck->getAttribute() again here instead of using upper_bck->getAttribute().
        setFrameCtrl(&mFrameCtrlUpper[UPPER_MOVE0_e], under_bck->getAttribute(), start, endUpper, rate, frame);
        upper_bck->setFrame(frame);
    } else {
        mAnmRatioUpper[UPPER_MOVE0_e].setAnmTransform(under_bck);
    }
    mAnmRatioUpper[UPPER_MOVE1_e].setAnmTransform(NULL);
    
    if (param_5 >= 0.0f) {
        m_old_fdata->initOldFrameMorf(param_5, 0, 0x2A);
    }
    
    setTextureAnime(mAnmDataTable[anm].mTexAnmIdx, 0);
    setHandModel(anm);
    setSeAnime(&m_anm_heap_under[UNDER_MOVE0_e], &mFrameCtrlUnder[UNDER_MOVE0_e]);
    m34C3 = 0;
    
    return TRUE;
}

/* 80128494-801285F8       .text setActAnimeUpper__9daPy_lk_cFUsQ29daPy_lk_c10daPy_UPPERffsf */
BOOL daPy_lk_c::setActAnimeUpper(u16 bckIdx, daPy_UPPER upperIdx, f32 rate, f32 start, s16 end, f32 f30) {
    J3DAnmTransform* bck = getAnimeResource(&m_anm_heap_upper[upperIdx], bckIdx, 0x2400);
    resetPriTextureAnime();
    mAnmRatioUpper[upperIdx].setAnmTransform(bck);
    mAnmRatioUpper[upperIdx].setRatio(1.0f);
    if (end < 0) {
        end = bck->getFrameMax();
    }
    
    f32 frame = rate < 0.0f ? end - 0.001f : start;
    setFrameCtrl(&mFrameCtrlUpper[upperIdx], bck->getAttribute(), start, end, rate, frame);
    bck->setFrame(frame);
    
    if (f30 >= 0.0f) {
        m_old_fdata->initOldFrameMorf(f30, 2, 0x1D);
    }
    
    return TRUE;
}

/* 801285F8-801286C0       .text resetActAnimeUpper__9daPy_lk_cFQ29daPy_lk_c10daPy_UPPERf */
BOOL daPy_lk_c::resetActAnimeUpper(daPy_UPPER upperIdx, f32 f31) {
    if (checkDashDamageAnime()) {
        mDamageWaitTimer = m_HIO->mDam.m.field_0x0;
    }
    
    mAnmRatioUpper[upperIdx].setAnmTransform(NULL);
    mAnmRatioUpper[upperIdx].setRatio(0.0f);
    m_anm_heap_upper[upperIdx].mIdx = -1;
    mFrameCtrlUpper[upperIdx].init(0);
    if (f31 >= 0.0f) {
        m_old_fdata->initOldFrameMorf(f31, 2, 0x1D);
    }
    resetPriTextureAnime();
    deleteArrow();
    
    return TRUE;
}

/* 801286C0-801287E8       .text animeUpdate__9daPy_lk_cFv */
void daPy_lk_c::animeUpdate() {
    J3DAnmTransform* underPack0 = getNowAnmPackUnder(UNDER_MOVE0_e);
    J3DAnmTransform* underPack1 = getNowAnmPackUnder(UNDER_MOVE1_e);
    J3DAnmTransform* upperPack0 = getNowAnmPackUpper(UPPER_MOVE0_e);
    J3DAnmTransform* upperPack1 = getNowAnmPackUpper(UPPER_MOVE1_e);
    mFrameCtrlUnder[UNDER_MOVE0_e].update();
    underPack0->setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    if (underPack1) {
        mFrameCtrlUnder[UNDER_MOVE1_e].update();
        underPack1->setFrame(mFrameCtrlUnder[UNDER_MOVE1_e].getFrame());
    }
    if (upperPack0 && upperPack0 != underPack0) {
        mFrameCtrlUpper[UPPER_MOVE0_e].update();
        upperPack0->setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getFrame());
    }
    if (upperPack1 && upperPack1 != underPack1) {
        mFrameCtrlUpper[UPPER_MOVE1_e].update();
        upperPack1->setFrame(mFrameCtrlUpper[UPPER_MOVE1_e].getFrame());
    }
    
    // Bug? This loop starts past the end of the array and immediately stops, without running a single iteration.
    // Maybe the array used to be more than 2 elements long but was shrank later.
    for (int i = 2; i < 2; i++) {
        J3DAnmTransform* underPack2 = getNowAnmPackUnder((daPy_UNDER)i);
        if (underPack2) {
            mFrameCtrlUnder[i].update();
            underPack2->setFrame(mFrameCtrlUnder[i].getFrame());
        }
    }
    
    J3DAnmTransform* upperPack2 = getNowAnmPackUpper(UPPER_MOVE2_e);
    if (upperPack2) {
        mFrameCtrlUpper[UPPER_MOVE2_e].update();
        upperPack2->setFrame(mFrameCtrlUpper[UPPER_MOVE2_e].getFrame());
    }
    
    if (mpParachuteFanMorf) {
        mpParachuteFanMorf->play(NULL, 0, 0);
    }
}

/* 801287E8-8012887C       .text simpleAnmPlay__9daPy_lk_cFP10J3DAnmBase */
void daPy_lk_c::simpleAnmPlay(J3DAnmBase* i_anm) {
    f32 frame = i_anm->getFrame() + 1.0f;
    if (frame >= i_anm->getFrameMax()) {
        if (i_anm->getAttribute() == 2) {
            frame -= i_anm->getFrameMax();
        } else {
            frame = i_anm->getFrameMax() - 0.001f;
        }
    }
    i_anm->setFrame(frame);
}

/* 8012887C-801288A0       .text setHandModel__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::setHandModel(daPy_ANM anmIdx) {
    mLeftHandIdx = mAnmDataTable[anmIdx].mLeftHandIdx;
    mRightHandIdx = mAnmDataTable[anmIdx].mRightHandIdx;
}

/* 801288A0-8012894C       .text getAnmData__9daPy_lk_cCFQ29daPy_lk_c8daPy_ANM */
const daPy_anmIndex_c* daPy_lk_c::getAnmData(daPy_ANM anm) const {
    if (mEquipItem == daPyItem_SWORD_e) {
        if (anm < (s32)ARRAY_SIZE(mSwordAnmIndexTable)) {
            return &mSwordAnmIndexTable[anm];
        }
    } else if (mEquipItem == daPyItem_BOKO_e) {
        if (anm < (s32)ARRAY_SIZE(mBokoAnmIndexTable)) {
            return &mBokoAnmIndexTable[anm];
        }
    } else if (mEquipItem == dItem_SKULL_HAMMER_e) {
        if (anm < (s32)ARRAY_SIZE(mHammerAnmIndexTable)) {
            return &mHammerAnmIndexTable[anm];
        }
    } else if (mEquipItem == dItem_BOOMERANG_e || mEquipItem == dItem_DEKU_LEAF_e || mEquipItem == dItem_TELESCOPE_e) {
        if (anm == ANM_DASH) {
            return &mSwordAnmIndexTable[anm];
        }
    }
    return &mAnmDataTable[anm].mAnmIdx;
}

/* 8012894C-80128988       .text checkGrabWeapon__9daPy_lk_cFi */
BOOL daPy_lk_c::checkGrabWeapon(int r4) {
    if (mEquipItem == daPyItem_BOKO_e && mActorKeepEquip.getActor() != NULL) {
        daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
        if (r4 == daBoko_c::Type_COUNT_e || fopAcM_GetParam(boko) == r4) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 80128988-801289A8       .text onDekuSpReturnFlg__9daPy_lk_cFUc */
void daPy_lk_c::onDekuSpReturnFlg(u8 i_point) {
    if (i_point != 0xFF) {
        mDekuSpRestartPoint = i_point;
    }
    onNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG);
}

/* 801289A8-80128AA4       .text changeTextureAnime__9daPy_lk_cFUsUsi */
void daPy_lk_c::changeTextureAnime(u16 btpIdx, u16 btkIdx, int r7) {
    if (!dComIfGp_event_runCheck()) {
        return;
    }
    if (r7 == -1) {
        if (m_tex_anm_heap.field_0x4 != btpIdx || m_tex_anm_heap.field_0x6 != 0xFFFE) {
            m_tex_anm_heap.field_0x4 = btpIdx;
            m_tex_anm_heap.field_0x6 = 0xFFFE;
            setTextureAnimeResource(loadTextureAnimeResource(btpIdx, FALSE), 0);
        }
        if (m_tex_scroll_heap.field_0x4 != btkIdx || m_tex_scroll_heap.field_0x6 != 0xFFFE) {
            m_tex_scroll_heap.field_0x4 = btkIdx;
            m_tex_scroll_heap.field_0x6 = 0xFFFE;
            setTextureScrollResource(loadTextureScrollResource(btkIdx, FALSE), 0);
        }
    } else {
        setDemoTextureAnime(btpIdx, btkIdx, 0, r7);
    }
}

/* 80128AA4-80128B50       .text setThrowDamage__9daPy_lk_cFP4cXyzsffi */
BOOL daPy_lk_c::setThrowDamage(cXyz* r4, s16 r5, f32 f30, f32 f31, int r6) {
    setPlayerPosAndAngle(r4, r5);
    mVelocity = f30;
    speed.y = f31;
    setDamagePoint(-r6);
    onNoResetFlg0(daPyFlg0_UNK1000000);
    return TRUE;
}

/* 80128B50-80128C10       .text setPlayerPosAndAngle__9daPy_lk_cFP4cXyzs */
void daPy_lk_c::setPlayerPosAndAngle(cXyz* param_1, s16 param_2) {
    if (!(dComIfGp_event_runCheck()) && dComIfGp_getScopeType() != 1) {
        return;
    }
    if (param_1 != NULL) {
        current.pos = *param_1;
        old.pos = current.pos;
    }
    shape_angle.y = param_2;
    current.angle.y = param_2;
    m34DE = shape_angle.y;
#if VERSION > VERSION_DEMO
    l_debug_keep_pos = current.pos;
    l_debug_shape_angle = shape_angle;
    l_debug_current_angle = current.angle;
#endif
}

/* 80128C10-80128CE4       .text setPlayerPosAndAngle__9daPy_lk_cFP4cXyzP5csXyz */
void daPy_lk_c::setPlayerPosAndAngle(cXyz* param_1, csXyz* param_2) {
    if (!(dComIfGp_event_runCheck())) {
        return;
    }
    if (param_1 != NULL) {
        current.pos = *param_1;
        old.pos = current.pos;
    }
    if (param_2 != NULL) {
        shape_angle = *param_2;
        current.angle.y = shape_angle.y;
        m34DE = shape_angle.y;
    }
#if VERSION > VERSION_DEMO
    l_debug_keep_pos = current.pos;
    l_debug_shape_angle = shape_angle;
    l_debug_current_angle = current.angle;
#endif
}

/* 80128CE4-80128DC0       .text setPlayerPosAndAngle__9daPy_lk_cFPA4_f */
void daPy_lk_c::setPlayerPosAndAngle(MtxP param_1) {
    if (dComIfGp_event_runCheck()) {
        current.pos.x = param_1[0][3];
        current.pos.y = param_1[1][3];
        current.pos.z = param_1[2][3];
        old.pos = current.pos;
        mDoMtx_MtxToRot(param_1, &shape_angle);
        current.angle.y = shape_angle.y;
        m34DE = shape_angle.y;
#if VERSION > VERSION_DEMO
        l_debug_keep_pos = current.pos;
        l_debug_shape_angle = shape_angle;
        l_debug_current_angle = current.angle;
#endif
    }
}

/* 80128DC0-80128F8C       .text endDemoMode__9daPy_lk_cFv */
void daPy_lk_c::endDemoMode() {
    if (mCurProc != daPyProc_LARGE_DAMAGE_e) {
        current.angle.y = shape_angle.y;
    }
    offNoResetFlg0(daPyFlg0_UNK100000);
    dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK10_e);
    mDemo.setDemoType(0);
    mDemo.setDemoMode(daPy_demo_c::DEMO_UNK00_e);
    mDemo.setParam0(0);
    mDemo.setParam1(0);
    mDemo.setStick(1.0f);
    resetDemoTextureAnime();
    if (mEquipItem == daPyItem_UNK104_e || mEquipItem == daPyItem_UNK10A_e) {
        deleteEquipItem(FALSE);
        offNoResetFlg1(daPyFlg1_SHIP_TACT);
    }
    mDoAud_taktModeMuteOff();
    if (mAcch.ChkGroundHit() &&
        !checkModeFlg(
            ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP | ModeFlg_CLIMB | ModeFlg_SWIM |
            ModeFlg_LADDER | ModeFlg_04000000 | ModeFlg_CAUGHT
        ) &&
        mCurProc != daPyProc_LARGE_DAMAGE_UP_e &&
        mCurProc != daPyProc_DEMO_DEAD_e &&
        mCurProc != daPyProc_DEMO_LAVA_DAMAGE_e)
    {
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e)) {
            procScope_init(0x20);
            return;
        }
        changeWaitProc();
        return;
    }
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
        if (ship == NULL) {
            checkNextMode(0);
        } else if (daPy_getPlayerActorClass() != this) {
            procControllWait_init();
        } else if (ship->getPart() == daShip_c::PART_CANNON_e) {
            procShipCannon_init();
        } else if (ship->getPart() == daShip_c::PART_CRANE_e) {
            procShipCrane_init();
        } else if (ship->getPart() == daShip_c::PART_STEER_e) {
            procShipSteer_init();
        } else {
            procShipPaddle_init();
        }
    } else if (mCurProc == daPyProc_DEMO_BOSS_WARP_e) {
        procWait_init();
    }
}

/* 80128F8C-8012901C       .text getBokoFlamePos__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::getBokoFlamePos(cXyz* outPos) {
    if (mEquipItem == daPyItem_BOKO_e) {
#if VERSION == VERSION_DEMO
        daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
        if (boko->getFlameTimer() != 0)
#else
        daBoko_c* boko = (daBoko_c*)fopAcM_SearchByID(mActorKeepEquip.getID());
        if (boko && boko->getFlameTimer() != 0)
#endif
        {
            *outPos = mSwordTopPos;
            return TRUE;
        }
    }
    return FALSE;
}

#include "d/actor/d_a_player_HIO.inc"

static actor_method_class2 l_daPy_Method = {
    (process_method_func)daPy_Create,
    (process_method_func)daPy_Delete,
    (process_method_func)daPy_Execute,
    (process_method_func)daPy_IsDelete,
    (process_method_func)daPy_Draw,
};

actor_process_profile_definition2 g_profile_PLAYER = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 5,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_PLAYER,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daPy_lk_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_PLAYER,
    /* Actor SubMtd */ (actor_method_class*)&l_daPy_Method,
    /* Status       */ fopAcStts_FREEZE_e,
    /* Group        */ fopAc_PLAYER_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
    /* field_0x30   */ 2,
};
