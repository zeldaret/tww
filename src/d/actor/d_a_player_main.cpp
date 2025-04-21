/**
 * d_a_player_main.cpp
 * 
 * Main file for the Link (Player) actor.
 * 
 * Much of Link's code is spread across various `.inc` files and included directly
 * into this one to make the file size more managable.
 * The original split locations are indicated in the map file.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_obj_movebox.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "d/d_procname.h"
#include "d/d_kankyo.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/actor/d_a_itembase.h"
#include "d/d_item_data.h"
#include "d/d_item.h"
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

#include "weak_bss_3569.h" // IWYU pragma: keep

JGeometry::TVec3<f32> l_hammer_splash_particle_scale(0.67f, 0.67f, 0.67f);

#include "d/actor/d_a_player_main_data.inc"

#include "d/actor/d_a_player_HIO_data.inc"

static void dummydatafunc(f32* temp, f64* temp2) {
    // temporary hack to improve diffs until sdata2 offsets are figured out
    *temp = 2.0f;
    *temp = -1000000000.0f;
    *temp = -1.0f;
    *temp = 0.0f;
    *temp = 0.08f;
    *temp = 1.0f;
    *temp = 12.0f;
    *temp = 13.0f;
    *temp = 150.0f;
    *temp = 30.0f;
    *temp = 0.65f;
    *temp = 0.35f;
    *temp = 32768.0f;
    *temp = 16384.0f;
    *temp = 10.0f;
    *temp2 = 4503601774854144.0;
    *temp2 = 4503599627370496.0;
    *temp = 25.0f;
    *temp = -0.05f;
    *temp2 = 0.5;
    *temp2 = 3.0;
    *temp = 0.6f;
    *temp = 0.01f;
    *temp = 0.001f;
    *temp = 15.0f;
    *temp = 1.5f;
    *temp = 3.1415927f;
    *temp = 0.5f;
    *temp = 0.3f;
    *temp = 1.2f;
    *temp = 0.4f;
    *temp = 5.0f;
    *temp = 0.1f;
    *temp = 0.8f;
    *temp = 60.0f;
    *temp = 4.0f;
    *temp = 0.25f;
    *temp = 0.75f;
    *temp = 16.0f;
    *temp = 8.0f;
    *temp = 18.0f;
    *temp = 3.0f;
    *temp = 0.2f;
    *temp = 0.05f;
    *temp = 45.0f;
    *temp = 11.0f;
    *temp = 17.5f;
    *temp = 1000000000.0f;
    OSReport("Adanmae");
    OSReport("d_a_player_dproc.inc");
    OSReport("0");
    OSReport("Halt");
    OSReport("Link");
    OSReport("DEFAULT_GETITEM");
    OSReport("GanonK");
    OSReport("GTower");
    OSReport("d_a_player_bow.inc");
    OSReport("d_a_player_hook.inc");
    OSReport("d_a_player_fan.inc");
    OSReport("d_a_player_hammer.inc");
    OSReport("Type");
    OSReport("Omori");
    OSReport("d_a_player_sword.inc");
    OSReport("M_DaiB");
    OSReport("Xboss2");
    OSReport("M_DragB");
    OSReport("Xboss0");
    OSReport("fall");
    OSReport("d_a_player_main.cpp");
    OSReport("(demo_mode < daPy_demo_c::DEMO_LAST_e) || (demo_mode == daPy_demo_c::DEMO_NEW_ANM0_e)");
    OSReport("Ojhous");
    OSReport("Orichh");
    OSReport("kinBOSS");
    OSReport("Xboss1");
    OSReport("ICE_FAILED");
    OSReport("pos");
    OSReport("angle");
    OSReport("prm0");
    OSReport("prm1");
    OSReport("stick");
    OSReport("face");
    OSReport("GanonM");
    OSReport("sea");
    OSReport("m_tex_anm_heap.m_buffer != 0");
    OSReport("m_texNoAnms != 0");
    OSReport("mat_anm != 0");
    OSReport("m_tex_scroll_heap.m_buffer != 0");
    OSReport("material_num == 2");
    OSReport("m_texMtxAnm != 0");
    OSReport("m_tex_eye_scroll[no] != 0");
    OSReport("tmtx != 0");
    OSReport("mtl->getMaterialAnm() != 0");
    OSReport("tmp_modelData != 0");
    OSReport("aura_p->getModel() != 0");
    OSReport("m_old_fdata != 0");
    OSReport("m_pbCalc[PART_UNDER_e] != 0");
    OSReport("m_pbCalc[PART_UPPER_e] != 0");
    OSReport("m_HIO != 0");
    OSReport("m_anm_heap_under[UNDER_MOVE0_e].m_buffer != 0");
    OSReport("m_sanm_buffer != 0");
    OSReport("m_item_bck_buffer != 0");
    OSReport("tmp_trans_bas != 0");
    OSReport("tmp_trans != 0");
    OSReport("tmp_tp != 0");
    OSReport("tmp_tk != 0");
    OSReport("*i_model != 0");
    OSReport("btk_anm != 0");
    OSReport("brk_anm != 0");
    OSReport("zoff_blend_cnt <= 4");
    OSReport("zoff_none_cnt <= 4");
    OSReport("zon_cnt <= 4");
    OSReport("zon_cnt == 4");
    OSReport("zoff_none_cnt == 4");
    OSReport("zoff_blend_cnt == 4");
    OSReport("dummy_data != 0");
    OSReport("Always");
    OSReport("tmp_tex != 0");
    OSReport("tmp_img != 0");
    OSReport("texture != 0");
    OSReport("textureName != 0");
    OSReport("linktexS3TC");
    OSReport("Pjavdou");
    OSReport("ShipD");
    OSReport("Siren");
    OSReport("data_size < l_sanm_buffer_size");
}

cXyz l_debug_keep_pos;
csXyz l_debug_current_angle;
csXyz l_debug_shape_angle;

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
    daPy_matAnm_c* i_this = const_cast<daPy_matAnm_c*>(this);
    
    J3DMaterialAnm::calc(mat);
    
    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i)) {
            J3DTextureSRTInfo& srt = mat->getTexMtx(i)->getTexMtxInfo().mSRT;
            if (m_morf_frame != 0) {
                f32 temp = 1.0f / (m_morf_frame + 1);
                srt.mTranslationX = mEyePosOld.x * (1.0f - temp) + (srt.mTranslationX * temp);
                srt.mTranslationY = mEyePosOld.y * (1.0f - temp) + (srt.mTranslationY * temp);
            } else if (m_eye_move_flg != 0) {
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
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->auraJointCB0(jntNo);
    }
    return TRUE;
}

/* 80103494-80103A88       .text jointBeforeCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
BOOL daPy_lk_c::jointBeforeCB(int jnt_no, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
    static Mtx root_mtx;
    static Quaternion norm_quat = {0.0f, 0.0f, 0.0f, 1.0f};
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
    u16 uVar1;
    bool bVar2;
    int iVar3;

    if (checkEquipAnime()) {
        if (!checkModeFlg(ModeFlg_00000001)) {
            if ((param_1 == 1) || (param_1 == 0xd)) {
                m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
            } else if ((param_1 == 4) || (param_1 == 0x1c)) {
                m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
            }
        }
    } else if ((checkUpperReadyAnime()) ||
               (checkUpperAnime(LKANM_BCK_ROPETHROW)) ||
               ((mCurProc != daPyProc_GRAB_WAIT_e) && checkGrabAnime()))
    {
        if (param_1 == 0xf) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
        } else if (param_1 == 0x1c) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        }
    } else if ((dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) &&
               (!checkShipNotNormalMode()))
    {
        if (param_1 == 0xf) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        } else if (param_1 == 0x1c) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
        }
    } else if (checkUpperGuardAnime()) {
        if ((param_1 == 0) || (param_1 == 0xd)) {
            if (param_1 == 0) {
                guard_rate = m_pbCalc[PART_UPPER_e]->getRatio(2);
            }
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        } else if ((param_1 == 4) || (param_1 == 0x1c)) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, guard_rate);
        }
    } else if ((dComIfGp_checkPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e)) &&
               ((mCurProc != daPyProc_TACT_PLAY_e || (mProcVar0.m3570 != 0))))
    {
        if (param_1 == 4) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        } else if (param_1 == 8) {
            m_pbCalc[PART_UPPER_e]->setRatio(1, 1.0f);
            m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
        } else if (param_1 == 0xc) {
            m_pbCalc[PART_UPPER_e]->setRatio(1, 0.0f);
        }
    }
    return true;
}

/* 80103EE4-80103F28       .text daPy_jointCallback0__FP7J3DNodei */
static BOOL daPy_jointCallback0(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->jointCB0(jntNo);
    }
    return TRUE;
}

/* 80103F28-80104178       .text jointCB1__9daPy_lk_cFv */
BOOL daPy_lk_c::jointCB1() {
    Quaternion* pQVar2;
    J3DTransformInfo* pJVar4;

    if (m_old_fdata->getOldFrameFlg() == false) {
        return false;
    }
    pJVar4 = m_old_fdata->getOldFrameTransInfo(0x21);
    pQVar2 = m_old_fdata->getOldFrameQuaternion(0x21);
    mDoMtx_stack_c::ZrotS(mFootData[1].field_0x008);
    mDoMtx_stack_c::revConcat(mpCLModel->getAnmMtx(0x20));
    mpCLModel->setAnmMtx(0x20, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(pJVar4->mTranslate.x, pJVar4->mTranslate.y, pJVar4->mTranslate.z);
    mDoMtx_stack_c::quatM((pQVar2));
    pJVar4++;
    pQVar2++;
    mDoMtx_stack_c::ZrotM(mFootData[1].field_0x00A);
    mpCLModel->setAnmMtx(0x21, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(pJVar4->mTranslate.x, pJVar4->mTranslate.y, pJVar4->mTranslate.z);
    mDoMtx_stack_c::quatM((pQVar2));
    pJVar4++;
    pQVar2++;
    mDoMtx_stack_c::ZrotM(mFootData[1].field_0x002);
    mpCLModel->setAnmMtx(0x22, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(pJVar4->mTranslate.x, pJVar4->mTranslate.y, pJVar4->mTranslate.z);
    mDoMtx_stack_c::quatM((pQVar2));
    mpCLModel->setAnmMtx(0x23, mDoMtx_stack_c::get());
    pJVar4 = m_old_fdata->getOldFrameTransInfo(0x26);
    pQVar2 = m_old_fdata->getOldFrameQuaternion(0x26);
    mDoMtx_stack_c::ZrotS(mFootData[0].field_0x008);
    mDoMtx_stack_c::revConcat(mpCLModel->getAnmMtx(0x25));
    mpCLModel->setAnmMtx(0x25, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(pJVar4->mTranslate.x, pJVar4->mTranslate.y, pJVar4->mTranslate.z);
    mDoMtx_stack_c::quatM((pQVar2));
    pJVar4++;
    pQVar2++;
    mDoMtx_stack_c::ZrotM(mFootData[0].field_0x00A);
    mpCLModel->setAnmMtx(0x26, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(pJVar4->mTranslate.x, pJVar4->mTranslate.y, pJVar4->mTranslate.z);
    mDoMtx_stack_c::quatM((pQVar2));
    pJVar4++;
    pQVar2++;
    mDoMtx_stack_c::ZrotM(mFootData[0].field_0x002);
    mpCLModel->setAnmMtx(0x27, mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(pJVar4->mTranslate.x, pJVar4->mTranslate.y, pJVar4->mTranslate.z);
    mDoMtx_stack_c::quatM((pQVar2));
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
        JKRReadResource(m_tex_anm_heap.m_buffer, 0x1000, btpIdx, dComIfGp_getLkDemoAnmArchive());
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
s32 daPy_lk_c::checkNormalFace() {
    /* Nonmatching - missing "clrlwi" instruction */
    if (mCurProc == daPyProc_SHIP_CRANE_e) {
        return daPyFace_TMABAA;
    }
    if (mFace != daPyFace_UNKNOWN) {
        return 0xFFFF0000;
    }
    if ((checkResetFlg0(daPyRFlg0_UNK40000))) {
        return daPyFace_TMABAG;
    }
    if (checkUpperAnime(LKANM_BCK_GRABWAITB)) {
        return daPyFace_TMABAJ_TEYORIME;
    }
    if (checkUpperAnime(LKANM_BCK_GRABWAIT)) {
        return daPyFace_TMABAE;
    }
    if ((daPy_dmEcallBack_c::checkCurse()) || (checkRestHPAnime())) {
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
    if (checkNoResetFlg1(daPyFlg1_UNK1000000) && (!checkModeFlg(ModeFlg_00000001))) {
        return daPyFace_TDASHKAZE;
    }
    if (((checkUpperReadyAnime() || ((checkNoResetFlg1(daPyFlg1_UNK400) ||
                                      ((mpAttnActorLockOn != NULL) &&
                                       (fopAcM_GetGroup(mpAttnActorLockOn) == fopAc_ENEMY_e))))) ||
         (checkNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS))) ||
        (mEquipItem == dItem_SKULL_HAMMER_e))
    {
        return daPyFace_TMABAC;
    }
    if (checkBossBgm()) {
        return daPyFace_TMABAC;
    }
    if (mpAttention->Lockon()) {
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
    if ((mCurProc == daPyProc_WAIT_e) && (!dComIfGp_event_runCheck())) {
        f32 dVar7 = cM_rnd();
        if ((((m_tex_anm_heap.mIdx == LKANM_BTP_TMABAA) ||
              (m_tex_anm_heap.mIdx == LKANM_BTP_TMABAB)) &&
             (dVar7 < 0.01f)) ||
            (((m_tex_anm_heap.mIdx == LKANM_BTP_TMABACC && (dVar7 >= 0.01f)))))
        {
            return daPyFace_TMABACC;
        }
        if (((dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_DUNGEON_e) ||
             dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SUBDUNGEON_e))
        {
            return daPyFace_TMABAB;
        }
    }
    return daPyFace_TMABAA;
}

/* 80104A08-80104E08       .text setTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setTextureAnime(u16 param_1, int param_2) {
    /* Nonmatching - missing "mr" instruction */
    BOOL bVar3;
    f32 dVar9;

    if (param_1 == 0) {
        param_1 = checkNormalFace();
    }
    u16 btp_idx = mTexAnmIndexTable[param_1].mBtpIdx;
    u16 btk_idx = mTexAnmIndexTable[param_1].mBtkIdx;
    if (((param_1 < 0x13) &&
         (checkMabaAnimeBtp(m_tex_anm_heap.mIdx))) &&
        (mFace == daPyFace_UNKNOWN))
    {
        param_2 = m3530;
        bVar3 = true;
    } else {
        bVar3 = false;
    }
    if (m_tex_anm_heap.mIdx == btp_idx) {
        if ((mFace == daPyFace_UNKNOWN) && (!checkModeFlg(ModeFlg_00000100 | ModeFlg_00000400))) {
            m3530 = param_2;
        }
    } else {
        m_tex_anm_heap.mIdx = btp_idx;
        if ((m_tex_anm_heap.field_0x2 == 0xFFFF) && (m_tex_anm_heap.field_0x4 == 0xFFFF)) {
            setTextureAnimeResource(loadTextureAnimeResource(btp_idx, 0), param_2);
        }
    }
    dVar9 = cM_rnd();
    if (m_tex_scroll_heap.mIdx != btk_idx) {
        if ((((bVar3) && (checkModeFlg(ModeFlg_00000001))) && (daPy_matAnm_c::m_maba_flg != 0)) &&
            (((!dComIfGp_event_runCheck() && (mpAttnActorLockOn == NULL)) && (btk_idx == LKANM_BTK_TMABA))))
        {
            if (daPy_matAnm_c::m_maba_timer == 0) {
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
                if ((m_tex_scroll_heap.field_0x2 == 0xFFFF) &&
                    (m_tex_scroll_heap.field_0x4 == 0xFFFF))
                {
                    setTextureScrollResource(loadTextureScrollResource(btk_idx, 0), param_2);
                }
                if (btk_idx != LKANM_BTK_TMABA) {
                    daPy_matAnm_c::onMabaFlg();
                }
            }
        } else {
            m_tex_scroll_heap.mIdx = btk_idx;
            if ((m_tex_scroll_heap.field_0x2 == 0xFFFF) && (m_tex_scroll_heap.field_0x4 == 0xFFFF))
            {
                setTextureScrollResource(loadTextureScrollResource(btk_idx, 0), param_2);
            }
        }
    } else if (((((bVar3) && (checkModeFlg(ModeFlg_00000001))) && (!dComIfGp_event_runCheck())) &&
                ((daPy_matAnm_c::m_maba_timer == 0 && (mpAttnActorLockOn == NULL)))) &&
               (((btk_idx == LKANM_BTK_TMABA && ((m_tex_scroll_heap.field_0x2 == 0xFFFF &&
                                      (m_tex_scroll_heap.field_0x4 == 0xFFFF)))) &&
                 (cM_rnd() < 0.025f))))
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
    return;
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
    /* Nonmatching */
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
        JKRReadResource(m_tex_scroll_heap.m_buffer, 0x800, btkIdx, dComIfGp_getLkDemoAnmArchive());
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
        } else if ((m_tex_anm_heap.field_0x6 == 0xFFFE) &&
                   (checkMabaAnimeBtp(m_tex_anm_heap.field_0x4)))
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
    } else if ((checkModeFlg(ModeFlg_00000400)) || ((m34C3 == 9) || (m34C3 == 10))) {
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
    return;
}

/* 8010552C-8010558C       .text checkPlayerGuard__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkPlayerGuard() const {
    /* Nonmatching */
    bool guard = false;
    if (mCurProc == daPyProc_CROUCH_DEFENSE_e || checkUpperGuardAnime() || checkGuardSlip()) {
        guard = true;
    }
    return guard;
}

/* 8010558C-801056E4       .text setOutPower__9daPy_lk_cFfsi */
void daPy_lk_c::setOutPower(f32, s16, int) {
    /* Nonmatching */
}

/* 801056E4-80105814       .text checkSightLine__9daPy_lk_cFfP4cXyz */
BOOL daPy_lk_c::checkSightLine(f32, cXyz*) {
    /* Nonmatching */
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
void daPy_lk_c::setItemModel() {
    /* Nonmatching */
}

/* 80106660-801066DC       .text checkUpperReadyAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkUpperReadyAnime() const {
    /* Nonmatching */
}

/* 801066DC-80106750       .text checkUpperReadyThrowAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkUpperReadyThrowAnime() const {
    /* Nonmatching */
}

/* 80106750-801067D8       .text checkNoCollisionCorret__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNoCollisionCorret() {
    /* Nonmatching */
}

/* 801067D8-80106BD0       .text setDrawHandModel__9daPy_lk_cFv */
void daPy_lk_c::setDrawHandModel() {
    /* Nonmatching */
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
void daPy_lk_c::hideHatAndBackle(J3DMaterial*) {
    /* Nonmatching */
}

/* 80106D8C-80106E50       .text drawMirrorLightModel__9daPy_lk_cFv */
void daPy_lk_c::drawMirrorLightModel() {
    /* Nonmatching */
}

/* 80106E50-80107210       .text drawShadow__9daPy_lk_cFv */
void daPy_lk_c::drawShadow() {
    /* Nonmatching */
}

/* 80107210-8010728C       .text offBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::offBodyEffect() {
    /* Nonmatching */
}

/* 8010728C-80107308       .text onBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::onBodyEffect() {
    /* Nonmatching */
}

/* 80107308-80108204       .text draw__9daPy_lk_cFv */
BOOL daPy_lk_c::draw() {
    /* Nonmatching - regalloc (maybe the same issue as linkDraw in d_a_obj_figure.cpp?) */
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
    
    s16 origFogR, origFogG, origFogB;
    f32 origFogStartZ, origFogEndZ;
    origFogR = tevStr.mFogColor.r;
    origFogG = tevStr.mFogColor.g;
    origFogB = tevStr.mFogColor.b;
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
    
    u16 material_num = mpAnmTexPatternData->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        u16 matID = mpAnmTexPatternData->getUpdateMaterialID(i);
        if (matID != 0xFFFF) {
            J3DMaterial* mtl = mpCLModelData->getMaterialNodePointer(matID);
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
    
    J3DMaterial* mtl = link_root_joint->getMesh();
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
                mtl->getShape()->hide();
            } else {
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
                mtl->getShape()->hide();
            } else {
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
                    mtl->getShape()->hide();
                }
            }
            link_root_joint->entryIn();
            if (checkMaskDraw()) {
                entryDLSetLight(mpYamuModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
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
        if ((!checkNormalSwordEquip() && dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_FF1_e) ||
            checkCaughtShapeHide() || checkDemoShieldNoDraw())
        {
            mpCLModelData->getJointNodePointer(0x0D)->getMesh()->getShape()->hide(); // cl_podA joint
        } else {
            mpCLModelData->getJointNodePointer(0x0D)->getMesh()->getShape()->show(); // cl_podA joint
        }
    }
    
    // regalloc issues with j3dSys from here on
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
        entryDLSetLight(mpHandsModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
        if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES) && !checkCaughtShapeHide() && !dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
            entryDLSetLight(mpKatsuraModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
        }
        if (checkFreezeState() && checkMaskDraw()) {
            entryDLSetLight(mpYamuModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
        }
        if (dComIfGs_getSelectEquip(2) == dItem_POWER_BRACELETS_e) {
            entryDLSetLight(mpPringModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
        }
        if (checkMasterSwordEquip() && !checkCaughtShapeHide() && !checkDemoShieldNoDraw()) {
            updateDLSetLight(mpPodmsModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
        }
    }
    if (checkEquipHeavyBoots()) {
        entryDLSetLight(mpHbootsModels[0], checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
        entryDLSetLight(mpHbootsModels[1], checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
    }
    
    tevStr.mFogColor.r = origFogR;
    tevStr.mFogColor.g = origFogG;
    tevStr.mFogColor.b = origFogB;
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
            if (checkSwordEquip() && !checkDemoSwordNoDraw(TRUE)) {
                entryDLSetLight(mpEquippedSwordModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
            }
        }
        if (dComIfGs_getSelectEquip(1) != dItem_NONE_e && !checkCaughtShapeHide() && !checkDemoShieldNoDraw()) {
            entryDLSetLight(mpEquippedShieldModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
        }
        dComIfGd_setList();
        drawMirrorLightModel();
        dComIfGd_setListP1();
        
        if (mpBottleContentsModel != NULL) {
            updateDLSetLight(mpBottleContentsModel, 0);
        }
        if (mpEquipItemModel && !checkCaughtShapeHide() && !checkDemoSwordNoDraw(FALSE)) {
            if (!checkBowItem(mEquipItem) || !checkPlayerGuard()) {
                if (mEquipItem == dItem_HOOKSHOT_e) {
                    if (mActorKeepEquip.getActor()) {
                        daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
                        mpEquipItemModel->setAnmMtx(4, hookshot->getMtxTop());
                    }
                }
                entryDLSetLight(mpEquipItemModel, checkNoResetFlg1(daPyFlg1_FREEZE_STATE));
                if (mpSwordModel1 != NULL) {
                    if (checkChanceMode() || checkNoResetFlg1(daPyFlg1_UNK8000) || checkFinalMasterSwordEquip()) {
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
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 80108634-801086C8       .text setHintActor__9daPy_lk_cFv */
int daPy_lk_c::setHintActor() {
    /* Nonmatching */
}

/* 801086C8-801088E8       .text setDoStatusBasic__9daPy_lk_cFv */
void daPy_lk_c::setDoStatusBasic() {
    /* Nonmatching */
}

/* 801088E8-80108A9C       .text setDoStatus__9daPy_lk_cFv */
void daPy_lk_c::setDoStatus() {
    /* Nonmatching */
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
void daPy_lk_c::setNormalSpeedF(f32, f32, f32, f32) {
    /* Nonmatching */
}

/* 80108D80-8010959C       .text posMoveFromFootPos__9daPy_lk_cFv */
void daPy_lk_c::posMoveFromFootPos() {
    /* Nonmatching */
    static const Vec rtoe_pos_offset = {-14.05f, 0.0f, 5.02f};
    static const Vec rheel_pos_offset = {-10.85f, 0.0f, -6.52f};
}

/* 8010959C-80109E80       .text posMove__9daPy_lk_cFv */
void daPy_lk_c::posMove() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 80109F4C-8010A204       .text checkBodyAngleX__9daPy_lk_cFs */
BOOL daPy_lk_c::checkBodyAngleX(s16) {
    /* Nonmatching */
    static Vec top_vec = {0.0f, 70.0f, 0.0f};
}

/* 8010A204-8010A2F4       .text setBodyAngleToCamera__9daPy_lk_cFv */
BOOL daPy_lk_c::setBodyAngleToCamera() {
    /* Nonmatching */
}

/* 8010A2F4-8010A4D4       .text setBodyAngleXReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::setBodyAngleXReadyAnime() {
    /* Nonmatching */
}

/* 8010A4D4-8010A96C       .text setSpeedAndAngleNormal__9daPy_lk_cFs */
void daPy_lk_c::setSpeedAndAngleNormal(s16) {
    /* Nonmatching */
}

/* 8010A96C-8010AA90       .text setSpeedAndAngleAtn__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtn() {
    /* Nonmatching */
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
            daPy_HIO_atnMoveB_c0::m.field_0x4,
            daPy_HIO_atnMoveB_c0::m.field_0x0,
            daPy_HIO_atnMoveB_c0::m.field_0x2
        );
        f1 = (daPy_HIO_atnMoveB_c0::m.field_0x8 * mStickDistance) * cM_scos(current.angle.y - origAngleY);
    } else {
        f1 = 0.0f;
    }
    shape_angle.y = m34E6;
    setNormalSpeedF(
        f1,
        daPy_HIO_atnMoveB_c0::m.field_0x18,
        daPy_HIO_atnMoveB_c0::m.field_0x10,
        daPy_HIO_atnMoveB_c0::m.field_0x14
    );
}

/* 8010AB84-8010AC8C       .text setSpeedAndAngleAtnActor__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtnActor() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 8010AD2C-8010B798       .text setBlendMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendMoveAnime(f32) {
    /* Nonmatching */
}

/* 8010B798-8010BB08       .text setBlendAtnBackMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnBackMoveAnime(f32) {
    /* Nonmatching */
}

/* 8010BB08-8010C010       .text setBlendAtnMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnMoveAnime(f32) {
    /* Nonmatching */
}

/* 8010C010-8010C100       .text setAnimeEquipSword__9daPy_lk_cFi */
void daPy_lk_c::setAnimeEquipSword(BOOL r4) {
    if (!checkSwordEquip()) {
        return;
    }
    m3562 = daPyItem_SWORD_e;
    f32 rate = daPy_HIO_cut_c0::m.field_0x8;
    f32 start = daPy_HIO_cut_c0::m.field_0xC;
    s16 end = daPy_HIO_cut_c0::m.field_0x0;
    f32 f3 = daPy_HIO_cut_c0::m.field_0x10;
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
    f32 rate = daPy_HIO_item_c0::m.field_0x14;
    f32 start = daPy_HIO_item_c0::m.field_0x18;
    s16 end = daPy_HIO_item_c0::m.field_0x2;
    f32 f3 = daPy_HIO_item_c0::m.field_0x1C;
    setActAnimeUpper(bckIdx, UPPER_MOVE2_e, rate, start, end, f3);
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
    ) || dComIfGp_event_runCheck() || mDemo.getDemoType() != 0) {
        rate = daPy_HIO_cut_c0::m.field_0x20;
        start = daPy_HIO_cut_c0::m.field_0x24;
        end = daPy_HIO_cut_c0::m.field_0x4;
        f3 = daPy_HIO_cut_c0::m.field_0x28;
    } else {
        rate = daPy_HIO_cut_c0::m.field_0x14;
        start = daPy_HIO_cut_c0::m.field_0x18;
        end = daPy_HIO_cut_c0::m.field_0x2;
        f3 = daPy_HIO_cut_c0::m.field_0x1C;
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
        f32 rate = daPy_HIO_item_c0::m.field_0x24;
        f32 start = daPy_HIO_item_c0::m.field_0x28;
        s16 end = daPy_HIO_item_c0::m.field_0x4;
        f32 f3 = daPy_HIO_item_c0::m.field_0x2C;
        setActAnimeUpper(LKANM_BCK_TAKEBOTH, UPPER_MOVE2_e, rate, start, end, f3);
    } else {
        f32 rate = daPy_HIO_item_c0::m.field_0x8;
        f32 start = daPy_HIO_item_c0::m.field_0xC;
        s16 end = daPy_HIO_item_c0::m.field_0x0;
        f32 f3 = daPy_HIO_item_c0::m.field_0x10;
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
    if (((!checkNoResetFlg0(daPyFlg0_NO_FALL_VOICE)) &&
         ((((!checkNoResetFlg0(daPyFlg0_UNK80) || (m35D0 < mAcch.GetGroundH())) || (m3580 == 4)) ||
           (C_BG_MIN_HEIGHT == mAcch.GetGroundH())))) &&
        (m35F0 - current.pos.y > 500.0f))
    {
        if (current.pos.y - mAcch.GetGroundH() >= 100.0f * daPy_HIO_fall_c0::m.field_0x14) {
            voiceStart(12);
            onNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
            setTextureAnime(0x56, 0);
        }
    }
    return;
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
        setSwordModel(TRUE);
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
        return;
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
BOOL daPy_lk_c::changeDragonShield(int) {
    /* Nonmatching */
}

/* 8010CD34-8010CFB4       .text checkNewItemChange__9daPy_lk_cFUc */
BOOL daPy_lk_c::checkNewItemChange(u8) {
    /* Nonmatching */
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
    if ((mEquipItem == dComIfGp_getSelectItem(dItemBtn_X_e)) &&
        (mEquipItem != dComIfGp_getSelectItem(dItemBtn_Y_e)) &&
        (mEquipItem != dComIfGp_getSelectItem(dItemBtn_Z_e)))
    {
        mReadyItemBtn = dItemBtn_X_e;
    } else if (((mEquipItem == dComIfGp_getSelectItem(dItemBtn_Y_e)) &&
                (mEquipItem != dComIfGp_getSelectItem(dItemBtn_X_e))) &&
               (mEquipItem != dComIfGp_getSelectItem(dItemBtn_Z_e)))
    {
        mReadyItemBtn = dItemBtn_Y_e;
    } else if (((mEquipItem == dComIfGp_getSelectItem(dItemBtn_Z_e)) &&
                (mEquipItem != dComIfGp_getSelectItem(dItemBtn_X_e))) &&
               (mEquipItem != dComIfGp_getSelectItem(dItemBtn_Y_e)))
    {
        mReadyItemBtn = dItemBtn_Z_e;
    }
    if ((((checkEquipAnime()) || (checkUpperAnime(LKANM_BCK_BOOMTHROW))) ||
         (checkUpperAnime(LKANM_BCK_BOOMCATCH))) ||
        (checkUpperAnime(LKANM_BCK_ROPETHROW)))
    {
        J3DFrameCtrl& frameCtrl = mFrameCtrlUpper[UPPER_MOVE2_e];
        if (checkUpperAnime(LKANM_BCK_BOOMCATCH)) {
            if (!(frameCtrl.getRate() < 0.01f)) {
                if (!(mStickDistance > 0.05f)) {
                    return;
                }
                if (!(frameCtrl.getFrame() > daPy_HIO_boom_c0::m.field_0x2C)) {
                    return;
                }
            }
            resetActAnimeUpper(UPPER_MOVE2_e, daPy_HIO_basic_c0::m.field_0xC);
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                procShipPaddle_init();
            }
        } else if (checkUpperAnime(LKANM_BCK_BOOMTHROW)) {
            if ((frameCtrl.getRate() < 0.01f) ||
                ((mStickDistance > 0.05f &&
                  (frameCtrl.getFrame() > daPy_HIO_boom_c0::m.field_0x10))))
            {
                resetActAnimeUpper(UPPER_MOVE2_e, daPy_HIO_basic_c0::m.field_0xC);
            } else {
                if (frameCtrl.checkPass(daPy_HIO_boom_c0::m.field_0x14)) {
                    throwBoomerang();
                }
            }
        } else if (checkUpperAnime(LKANM_BCK_ROPETHROW)) {
            if (frameCtrl.getRate() < 0.01f) {
                mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
                mFrameCtrlUnder[UNDER_MOVE1_e].setRate(0.0f);
                mFrameCtrlUpper[UPPER_MOVE0_e].setRate(daPy_HIO_atnMove_c0::m.field_0x24);
                mFrameCtrlUpper[UPPER_MOVE1_e].setRate(0.0f);
            }
        } else {
            if (checkEquipAnime()) {
                if ((mEquipItem == daPyItem_SWORD_e) &&
                    (((checkUpperAnime(LKANM_BCK_REST) &&
                       (frameCtrl.checkPass(7.0f - frameCtrl.getRate()))) ||
                      ((((checkUpperAnime(LKANM_BCK_TAKE) &&
                          (frameCtrl.checkPass(7.0f - frameCtrl.getRate()))) ||
                         ((checkUpperAnime(LKANM_BCK_TAKEBOTH) &&
                           (frameCtrl.checkPass(daPy_HIO_item_c0::m.field_0x30 -
                                                frameCtrl.getRate()))))) ||
                        ((checkSingleItemEquipAnime() &&
                          (frameCtrl.checkPass(daPy_HIO_item_c0::m.field_0x20 -
                                               frameCtrl.getRate())))))))))
                {
                    seStartOnlyReverb(JA_SE_LK_SW_PUTIN_S);
                }
                if (std::fabsf(frameCtrl.getRate()) < 0.01f) {
                    resetActAnimeUpper(UPPER_MOVE2_e, daPy_HIO_basic_c0::m.field_0xC);
                } else {
                    if (((((checkUpperAnime(LKANM_BCK_REST)) &&
                           (frameCtrl.checkPass(7.0f))) ||
                          ((checkUpperAnime(LKANM_BCK_TAKE) &&
                            (frameCtrl.checkPass(7.0f))))) ||
                         ((checkUpperAnime(LKANM_BCK_TAKEBOTH) &&
                           (frameCtrl.checkPass(daPy_HIO_item_c0::m.field_0x30))))) ||
                        ((checkSingleItemEquipAnime() &&
                          (frameCtrl.checkPass(daPy_HIO_item_c0::m.field_0x20)))))
                    {
                        if (((mEquipItem != daPyItem_NONE_e) && (mEquipItem != daPyItem_SWORD_e)) ||
                            ((m3562 != daPyItem_NONE_e && (m3562 != daPyItem_SWORD_e))))
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
                        if ((!dComIfGp_event_runCheck()) && (mDemo.getDemoType() == 0)) {
                            if ((mEquipItem != daPyItem_SWORD_e) ||
                                (!checkNoResetFlg1(daPyFlg1_UNK4000000)))
                            {
                                if (((mpAttention->Lockon()) || (mEquipItem != daPyItem_SWORD_e)) ||
                                    var_r28)
                                {
                                    onResetFlg0(daPyRFlg0_UNK80);
                                }
                            }
                        }
                        if (mCurProc == daPyProc_DEMO_STAND_ITEM_PUT_e) {
                            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
                        } else if (mEquipItem == daPyItem_SWORD_e) {
                            seStartOnlyReverb(JA_SE_LK_SW_PULLOUT_S);
                            setSwordModel(0);
                        } else {
                            makeItemType();
                        }
                    }
                }
            }
        }
    }
    return;
}

/* 8010D754-8010D810       .text getSlidePolygon__9daPy_lk_cFv */
cM3dGPla* daPy_lk_c::getSlidePolygon() {
    /* Nonmatching */
}

/* 8010D810-8010D8B0       .text checkJumpCutFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkJumpCutFromButton() {
    /* Nonmatching */
}

/* 8010D8B0-8010DB58       .text orderTalk__9daPy_lk_cFv */
int daPy_lk_c::orderTalk() {
    /* Nonmatching */
}

/* 8010DB58-8010E448       .text checkNextActionFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionFromButton() {
    /* Nonmatching */
}

/* 8010E448-8010E75C       .text setShieldGuard__9daPy_lk_cFv */
void daPy_lk_c::setShieldGuard() {
    /* Nonmatching */
}

/* 8010E75C-8010E7C4       .text checkItemModeActorPointer__9daPy_lk_cFv */
BOOL daPy_lk_c::checkItemModeActorPointer() {
    /* Nonmatching */
}

/* 8010E7C4-8010E828       .text checkNextActionItemFly__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionItemFly() {
    /* Nonmatching */
}

/* 8010E828-8010EC78       .text checkNextMode__9daPy_lk_cFi */
BOOL daPy_lk_c::checkNextMode(int) {
    /* Nonmatching */
}

/* 8010EC78-8010ED68       .text checkIceSlipFall__9daPy_lk_cFv */
BOOL daPy_lk_c::checkIceSlipFall() {
    /* Nonmatching */
}

/* 8010ED68-8010F9AC       .text setFrontWallType__9daPy_lk_cFv */
void daPy_lk_c::setFrontWallType() {
    /* Nonmatching */
}

/* 8010F9AC-8010FEC4       .text changeFrontWallTypeProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeFrontWallTypeProc() {
    /* Nonmatching */
}

/* 8010FEC4-8010FFB0       .text changeSlideProc__9daPy_lk_cFv */
int daPy_lk_c::changeSlideProc() {
    /* Nonmatching */
}

/* 8010FFB0-80110028       .text changeWaitProc__9daPy_lk_cFv */
void daPy_lk_c::changeWaitProc() {
    /* Nonmatching */
}

/* 80110028-8011029C       .text changeLandProc__9daPy_lk_cFf */
BOOL daPy_lk_c::changeLandProc(f32) {
    /* Nonmatching */
}

/* 8011029C-80110338       .text setDamagePoint__9daPy_lk_cFf */
BOOL daPy_lk_c::setDamagePoint(f32 amount) {
    if (!checkNoDamageMode()) {
        dComIfGp_setItemLifeCount(amount);
        if (amount < 0.0f) {
            offNoResetFlg1(daPyFlg1_UNK8000);
            if (!checkFinalMasterSwordEquip()) {
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
BOOL daPy_lk_c::checkNormalDamage(int) {
    /* Nonmatching */
}

/* 80110448-801104E4       .text setDashDamage__9daPy_lk_cFv */
void daPy_lk_c::setDashDamage() {
    /* Nonmatching */
}

/* 801104E4-8011054C       .text checkAtHitEnemy__9daPy_lk_cFP12dCcD_GObjInf */
BOOL daPy_lk_c::checkAtHitEnemy(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 8011054C-801105D8       .text checkElecReturnDamage__9daPy_lk_cFP12dCcD_GObjInfP4cXyz */
BOOL daPy_lk_c::checkElecReturnDamage(dCcD_GObjInf* param_1, cXyz* param_2) {
    if ((param_1->ChkAtHit()) && (param_1->GetAtHitGObj() != NULL)) {
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
    if ((param_1->ChkWallHit()) && (dComIfG_Bgsp()->ChkPolySafe(*param_1))) {
        int attrib_code = dComIfG_Bgsp()->GetAttributeCode(*param_1);
        if ((attrib_code == dBgS_Attr_DAMAGE_e || (attrib_code == dBgS_Attr_ELECTRICITY_e))) {
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
                resetActAnimeUpper(UPPER_MOVE2_e, daPy_HIO_basic_c0::m.field_0xC);
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
        mDemo.getDemoType() != 0 ||
        checkNoControll() ||
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
    } else if (
        dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
        checkNoResetFlg0(daPyFlg0_SHIP_DROP)
    ) {
        offNoResetFlg0(daPyFlg0_SHIP_DROP);
        changePlayer(this);
        return procLargeDamage_init(-2, 1, 0, 0);
    } else if (!checkModeFlg(ModeFlg_DAMAGE) && mDamageWaitTimer == 0) {
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
            mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x2;
            
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
                    cXyz* damageVec = getDamageVec(&mCyl);
                    grab_actor->shape_angle.y = cM_atan2s(damageVec->x, damageVec->z);
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
    /* Nonmatching */
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
    JUT_ASSERT(9342, (demo_mode < daPy_demo_c::DEMO_LAST_e) ||
                         (demo_mode == daPy_demo_c::DEMO_NEW_ANM0_e));
    if ((((demo_mode != daPy_demo_c::DEMO_NEW_ANM0_e) &&
          (demo_mode != daPy_demo_c::DEMO_UNK1E_e)) &&
         (demo_mode != daPy_demo_c::DEMO_UNK09_e)) &&
        (((demo_mode != daPy_demo_c::DEMO_UNK11_e && (demo_mode != daPy_demo_c::DEMO_UNK40_e)) &&
          ((demo_mode != daPy_demo_c::DEMO_UNK04_e &&
            ((demo_mode != daPy_demo_c::DEMO_UNK2F_e &&
              (demo_mode != daPy_demo_c::DEMO_UNK3E_e))))))))
    {
        if ((!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
             !dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)))
        {
            if ((!mAcch.ChkGroundHit() ||
                 (checkModeFlg(ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP |
                               ModeFlg_CLIMB | ModeFlg_SWIM | ModeFlg_LADDER | ModeFlg_CAUGHT))))
            {
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
    if (demo_mode == daPy_demo_c::DEMO_UNK04_e) {
        int var_r28;
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            return true;
        }
        var_r28 = procWait_init();
        if (var_r28 != 0) {
            m_old_fdata->initOldFrameMorf(0.0f, 0, 0x2A);
        }
        return var_r28;
    } else if ((demo_mode == daPy_demo_c::DEMO_UNK06_e) || (demo_mode == daPy_demo_c::DEMO_UNK08_e)) {
        if (checkModeFlg(ModeFlg_04000000)) {
            return true;
        }
        if (((dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) &&
             (fopAcM_getTalkEventPartner(this) != NULL)) &&
            (fopAcM_getTalkEventPartner(this) == dComIfGp_getShipActor()))
        {
            return procShipPaddle_init();
        } else {
            onNoResetFlg0(daPyFlg0_UNK100000);
            fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
            if (grab_actor != NULL) {
                if ((fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e)) &&
                    (!checkGrabSpecialHeavyState()))
                {
                    return procGrabThrow_init(0);
                } else {
                    return procGrabPut_init();
                }
            } else {
                return dProcTalk_init();
            }
        }
    } else if (demo_mode == daPy_demo_c::DEMO_UNK09_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        if ((mCurProc == daPyProc_LARGE_DAMAGE_UP_e) || (mCurProc == daPyProc_LARGE_DAMAGE_WALL_e))
        {
            return false;
        }
        if (checkModeFlg(ModeFlg_SWIM)) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            return false;
        } else {
            return procLargeDamage_init(-3, 1, 0, 0);
        }
    } else if (demo_mode == daPy_demo_c::DEMO_UNK1B_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return procLargeDamageUp_init(-3, 1, 0, 0);
    } else if (demo_mode == daPy_demo_c::DEMO_UNK10_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        if (mCurProc == daPyProc_BACK_JUMP_LAND_e) {
            return false;
        }
        return procBackJump_init();
    } else if (demo_mode == daPy_demo_c::DEMO_UNK11_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    } else if (demo_mode == daPy_demo_c::DEMO_UNK40_e) {
        if (mCurProc == daPyProc_LAND_e) {
            return true;
        }
        return procSlowFall_init();
    } else if (demo_mode == daPy_demo_c::DEMO_UNK1F_e) {
        if (((!checkModeFlg(ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP |
                            ModeFlg_CLIMB | ModeFlg_SWIM | ModeFlg_LADDER | ModeFlg_04000000 |
                            ModeFlg_CAUGHT)) &&
             (((((checkUpperReadyThrowAnime() || (m34C3 == 2)) || (m34C3 == 1)) ||
                ((m34C3 == 4 || (m34C3 == 9)))) ||
               ((m34C3 == 10 || (mCurProc == daPyProc_GRAB_WAIT_e)))))) ||
            (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)))
        {
            onNoResetFlg0(daPyFlg0_UNK100000);
            return dProcLookWait_init();
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            return true;
        }
    } else if (demo_mode == daPy_demo_c::DEMO_UNK22_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        if ((mCurProc == daPyProc_TACT_PLAY_e) || (mCurProc == daPyProc_TACT_PLAY_END_e)) {
            return true;
        }
        return procTactWait_init(mDemo.getParam0());
    } else if (demo_mode == daPy_demo_c::DEMO_UNK33_e) {
        fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
        if ((grab_actor == NULL) || (grab_actor != dComIfGp_getCb1Player())) {
            deleteEquipItem(FALSE);
            freeGrabItem();
            mActorKeepGrab.setData(dComIfGp_getCb1Player());
            fopAcM_setCarryNow(mActorKeepGrab.getActor(), TRUE);
        }
        return procGrabWait_init();
    } else if (demo_mode == daPy_demo_c::DEMO_UNK3D_e) {
        onNoResetFlg0(daPyFlg0_UNK100000);
        return procBottleOpen_init(dComIfGp_event_getPreItemNo());
    } else if ((((checkNoResetFlg0(daPyFlg0_UNK100000)) || (mCurProc == daPyProc_SUBJECTIVITY_e)) ||
                (checkUpperReadyThrowAnime())) &&
               (((demo_mode == daPy_demo_c::DEMO_UNK2A_e || (demo_mode - 1 <= 2)) ||
                 ((demo_mode == daPy_demo_c::DEMO_UNK17_e ||
                   (demo_mode == daPy_demo_c::DEMO_UNK12_e))))))
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
    if ((((!dComIfGp_event_runCheck()) && (mDemo.getDemoType() == 0)) &&
         (dComIfGs_getLife() == 0)) &&
        (!checkModeFlg(ModeFlg_DAMAGE)))
    {
        if (dComIfGs_checkBottle(dItem_FAIRY_BOTTLE_e)) {
            makeFairy(&current.pos, 5);
            dComIfGs_setBottleItemIn(dItem_FAIRY_BOTTLE_e, dItem_EMPTY_BOTTLE_e);
            return false;
        }
        if (((mAcch.ChkGroundHit()) || (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e))) ||
            (checkModeFlg(ModeFlg_SWIM)))
        {
            return dProcDead_init();
        }
        return procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    } else {
        return false;
    }
}

/* 80111B80-80111D64       .text getDamageVec__9daPy_lk_cFP12dCcD_GObjInf */
cXyz* daPy_lk_c::getDamageVec(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 80111D64-80111E54       .text setOldRootQuaternion__9daPy_lk_cFsss */
void daPy_lk_c::setOldRootQuaternion(s16, s16, s16) {
    /* Nonmatching */
}

/* 80111E54-80111EFC       .text checkRestHPAnime__9daPy_lk_cFv */
BOOL daPy_lk_c::checkRestHPAnime() {
    if ((((!checkPlayerGuard()) && (checkNoUpperAnime())) &&
         (mpAttnActorLockOn == NULL)) &&
        ((((mDemo.getDemoType() == 0 && (!checkModeFlg(ModeFlg_IN_SHIP))) &&
           (dComIfGs_getLife() <= daPy_HIO_move_c0::m.field_0xE)) ||
          (mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK12_e))))
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
    if ((dComIfGp_getScopeMesgStatus() == 11) &&
        ((cancelTrigger()) || (checkNoResetFlg0(daPyFlg0_SCOPE_CANCEL))))
    {
        if ((dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e)) || (cancelTrigger())) {
            mDoAud_seStart(JA_SE_ITM_SUBMENU_OUT);
        }
        return true;
    }
    return false;
}

/* 80112100-8011215C       .text setSubjectMode__9daPy_lk_cFv */
void daPy_lk_c::setSubjectMode() {
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000_e);
    mDoAud_seStart(JA_SE_SUBJ_VIEW_IN);
}

/* 8011215C-801121C8       .text checkMaskDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::checkMaskDraw() {
    dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
    if ((demo_actor == NULL) && (dComIfGs_isCollect(4, 1))) {
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
            mDoAud_seStart(JA_SE_SUBJ_VIEW_OUT);
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
        mDoAud_seStop(JA_SE_LK_RUN_SLIP, 0);
    } else if (mCurProc == daPyProc_GRAB_MISS_e || (mCurProc == daPyProc_GRAB_READY_e && proc != daPyProc_GRAB_MISS_e)) {
        mActorKeepRope.clearData();
    } else if (mCurProc == daPyProc_DEMO_TALISMAN_WAIT_e) {
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        mpEquipItemModel = NULL;
    } else if (mCurProc == daPyProc_FAN_SWING_e) {
        setSmallFanModel();
    } else if (mCurProc == daPyProc_FAN_GLIDE_e) {
        deleteEquipItem(FALSE);
        maxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
        setSmallFanModel();
        mEquipItem = dItem_DEKU_LEAF_e;
        m35F0 = m3688.y;
        m3730 = cXyz::Zero;
        m34E0 = 0;
        m34E4 = 0;
    } else if (mCurProc == daPyProc_SLOW_FALL_e) {
        maxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
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
    
    gravity = daPy_HIO_autoJump_c0::m.field_0xC;
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
    mSmokeEcallBack.end();
    
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
    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    current.angle.y = shape_angle.y;
    mDoAud_seStart(JA_SE_ITM_SUBMENU_IN_1);
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
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
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
        mDoAud_seStart(JA_SE_SUBJ_VIEW_OUT);
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
    setSingleMoveAnime(ANM_YOBU, 1.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);
    current.angle.y = shape_angle.y;
    if (mEquipItem == daPyItem_BOKO_e) {
        deleteEquipItem(FALSE);
    }
    voiceStart(0x2A);
    return TRUE;
}

/* 80112C90-80112D38       .text procCall__9daPy_lk_cFv */
BOOL daPy_lk_c::procCall() {
    if (dComIfGp_getCb1Player()) {
        s16 targetAngle = cLib_targetAngleY(&current.pos, &dComIfGp_getCb1Player()->eyePos);
        cLib_addCalcAngleS(&shape_angle.y, targetAngle, 2, 0x2000, 0x800);
        current.angle.y = shape_angle.y;
    }
    
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (dComIfGp_getCb1Player()) {
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
    setSingleMoveAnime(ANM_NENRIKI, 1.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);
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
    /* Nonmatching */
}

/* 80113044-801133FC       .text procWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procWait() {
    /* Nonmatching */
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
    if (mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    } else {
        setSpeedAndAngleNormal(daPy_HIO_move_c0::m.field_0x0);
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
    if ((!checkNextMode(0)) && (dComIfGp_event_runCheck())) {
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
    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    m34D0 = 0x14;
    return true;
}

/* 80113628-801136D4       .text procMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procMove() {
    /* Nonmatching - regalloc */
    setSpeedAndAngleNormal(daPy_HIO_move_c0::m.field_0x0);
    if (((!checkNextMode(0)) && (!changeFrontWallTypeProc())) && (!checkIceSlipFall())) {
        if ((mDemo.getDemoMode() == 2) &&
            (mVelocity > mMaxNormalSpeed * daPy_HIO_move_c0::m.field_0x2C))
        {
            mVelocity = mMaxNormalSpeed * daPy_HIO_move_c0::m.field_0x2C;
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
    setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    m34D0 = 0x14;
    return true;
}

/* 80113738-801137B4       .text procAtnMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnMove() {
    setSpeedAndAngleAtn();
    if ((!checkNextMode(0)) &&
        (((mDirection != DIR_NONE) || (!changeFrontWallTypeProc())) && (!checkIceSlipFall())))
    {
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
    if ((mDirection == DIR_LEFT) || ((mDirection != DIR_RIGHT) && !(sVar2 - shape_angle.y < 0))) {
        mDirection = DIR_LEFT;
    } else {
        mDirection = DIR_RIGHT;
    }
    if (checkAtnWaitAnime()) {
        setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
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
    setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    m34D0 = 0x14;
    return true;
}

/* 80113960-801139C0       .text procAtnActorMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorMove() {
    setSpeedAndAngleAtnActor();
    if ((!checkNextMode(0)) && (!checkIceSlipFall())) {
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
    setSingleMoveAnime(dVar1, daPy_HIO_sideStep_c0::m.field_0xC, daPy_HIO_sideStep_c0::m.field_0x10,
                       daPy_HIO_sideStep_c0::m.field_0x4, daPy_HIO_sideStep_c0::m.field_0x14);
    mVelocity = cM_scos(daPy_HIO_sideStep_c0::m.field_0x2) * daPy_HIO_sideStep_c0::m.field_0x8;
    speed.y = cM_ssin(daPy_HIO_sideStep_c0::m.field_0x2) * daPy_HIO_sideStep_c0::m.field_0x8;
    gravity = daPy_HIO_sideStep_c0::m.field_0x18;
    mProcVar0.m3570 = 0;
    voiceStart(5);
    return true;
}

/* 80113AC4-80113BDC       .text procSideStep__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStep() {
    if (daPy_HIO_sideStep_c0::m.field_0x0 != 0) {
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
        if (current.pos.y < m3688.y - daPy_HIO_sideStep_c0::m.field_0x30) {
            procFall_init(2, daPy_HIO_sideStep_c0::m.field_0x2C);
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
    setSingleMoveAnime(dVar2, daPy_HIO_sideStep_c0::m.field_0x1C,
                       daPy_HIO_sideStep_c0::m.field_0x20, daPy_HIO_sideStep_c0::m.field_0x6,
                       daPy_HIO_sideStep_c0::m.field_0x24);
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
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_sideStep_c0::m.field_0x28) {
            checkNextMode(1);
        }
    }
    return true;
}

/* 80113D30-80113DBC       .text procCrouchDefense_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefense_init() {
    commonProcInit(daPyProc_CROUCH_DEFENSE_e);
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(ANM_DIFENCE, daPy_HIO_crouch_c0::m.field_0x10, 0.0f, -1,
                       daPy_HIO_crouch_c0::m.field_0x14);
    current.angle.y = shape_angle.y;
    m34D4 = 0;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK80000_e);
    return true;
}

/* 80113DBC-80114014       .text procCrouchDefense__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefense() {
    /* Nonmatching */
}

/* 80114014-801142F4       .text procCrouchDefenseSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefenseSlip_init() {
    /* Nonmatching */
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
    setSingleMoveAnime(ANM_CROUCH, daPy_HIO_crouch_c0::m.field_0x18, 0.0f, -1,
                       daPy_HIO_crouch_c0::m.field_0x1C);
    deleteEquipItem(FALSE);
    current.angle.y = shape_angle.y;
    return true;
}

/* 80114440-8011476C       .text procCrouch__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouch() {
    /* Nonmatching */
}

/* 8011476C-80114804       .text procWaitTurn_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn_init() {
    if (mCurProc == daPyProc_WAIT_TURN_e) {
        return false;
    }
    commonProcInit(daPyProc_WAIT_TURN_e);
    setSingleMoveAnime(ANM_ROT, daPy_HIO_basic_c0::m.field_0x4, 0.0f, -1,
                       daPy_HIO_basic_c0::m.field_0xC);
    if (dComIfGp_event_runCheck()) {
        mVelocity = 0.0f;
    }
    m34D4 = m34E8;
    current.angle.y = shape_angle.y;
    return true;
}

/* 80114804-80114908       .text procWaitTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn() {
    cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_move_c0::m.field_0x24, daPy_HIO_move_c0::m.field_0x1C,
                 daPy_HIO_move_c0::m.field_0x20);
    if (changeSlideProc()) {
        return true;
    }
    s16 sVar1 = cLib_addCalcAngleS(&shape_angle.y, m34D4, daPy_HIO_turn_c0::m.field_0x4,
                                   daPy_HIO_turn_c0::m.field_0x0, daPy_HIO_turn_c0::m.field_0x2);
    current.angle.y = shape_angle.y;
    if (checkNextActionFromButton()) {
        return true;
    }
    if (sVar1 == 0) {
        if (dComIfGp_event_runCheck()) {
            if (mDemo.getDemoMode() == 5) {
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
    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800_e);
    if (param_1 != 0) {
        m34D4 = (daPy_HIO_move_c0::m.field_0x0 * 4) + 0x4A56;
        m34D6 = daPy_HIO_move_c0::m.field_0x0 * 2;
        m34D0 = 2;
        current.angle.y = m34E8;
        mVelocity *= 0.5f;
    } else {
        m34D4 = daPy_HIO_move_c0::m.field_0x0 * 2;
        m34D6 = daPy_HIO_move_c0::m.field_0x0;
        m34D0 = 3;
    }
    return true;
}

/* 801149EC-80114A60       .text procMoveTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procMoveTurn() {
    setSpeedAndAngleNormal(daPy_HIO_move_c0::m.field_0x0);
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
    setSingleMoveAnime(ANM_SLIP, daPy_HIO_slip_c0::m.field_0xC, 0.0f, -1,
                       daPy_HIO_slip_c0::m.field_0x1C);
    mVelocity = speedF * daPy_HIO_slip_c0::m.field_0x8;
    if (daPy_HIO_slip_c0::m.field_0x0 == 1) {
        mVelocity = mMaxNormalSpeed;
    } else if ((daPy_HIO_slip_c0::m.field_0x0 == 2) && (mVelocity > mMaxNormalSpeed)) {
        mVelocity = mMaxNormalSpeed;
    }
    m34BE = 2;
    seStartMapInfo(JA_SE_LK_RUN_SLIP);
    return true;
}

/* 80114B28-80114D2C       .text procSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlip() {
    f32 dVar5 = cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_slip_c0::m.field_0x18,
                             daPy_HIO_slip_c0::m.field_0x10, daPy_HIO_slip_c0::m.field_0x14);
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
        if (mVelocity < daPy_HIO_slip_c0::m.field_0x20) {
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
            bool bVar2;
            if (!(iVar3->GetNP()->y >= 0.5f) && !(iVar3->GetNP()->y < -0.8f)) {
                bVar2 = true;
            } else {
                bVar2 = false;
            }
            if (bVar2) {
                mVelocity = 0.0f;
                checkNextMode(0);
            }
        }
    }
    return true;
}

/* 80114D2C-80114DE4       .text procSlideFront_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procSlideFront_init(s16 param_1) {
    if ((mCurProc == daPyProc_SLIDE_FRONT_e) || (mCurProc == daPyProc_SLIDE_BACK_e)) {
        return false;
    }
    commonProcInit(daPyProc_SLIDE_FRONT_e);
    m3526 = 8;
    current.angle.y = param_1;
    setSingleMoveAnime(ANM_SLIDEF, daPy_HIO_slide_c0::m.field_0xC, daPy_HIO_slide_c0::m.field_0x10,
                       daPy_HIO_slide_c0::m.field_0x0, daPy_HIO_slide_c0::m.field_0x14);
    mMaxNormalSpeed = daPy_HIO_slide_c0::m.field_0x44;
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
        mVelocity += (1.0f + 0.5f * (1.0f - pfVar2->GetNP()->y)) * daPy_HIO_slide_c0::m.field_0x48 *
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
    if ((mCurProc == daPyProc_SLIDE_BACK_e) || (mCurProc == daPyProc_SLIDE_FRONT_e)) {
        return false;
    }
    commonProcInit(daPyProc_SLIDE_BACK_e);
    m3526 = 8;
    current.angle.y = param_1;
    setSingleMoveAnime(ANM_SLIDEB, daPy_HIO_slide_c0::m.field_0x18, daPy_HIO_slide_c0::m.field_0x1C,
                       daPy_HIO_slide_c0::m.field_0x2, daPy_HIO_slide_c0::m.field_0x20);
    mMaxNormalSpeed = daPy_HIO_slide_c0::m.field_0x44;
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
        mVelocity += (1.0f + 0.5f * (1.0f - pfVar2->GetNP()->y)) * daPy_HIO_slide_c0::m.field_0x48 *
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
    setSingleMoveAnime(ANM_SLIDEFLAND, daPy_HIO_slide_c0::m.field_0x24,
                       daPy_HIO_slide_c0::m.field_0x28, daPy_HIO_slide_c0::m.field_0x4,
                       daPy_HIO_slide_c0::m.field_0x30);
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
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_slide_c0::m.field_0x2C) {
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
    setSingleMoveAnime(ANM_SLIDEBLAND, daPy_HIO_slide_c0::m.field_0x34,
                       daPy_HIO_slide_c0::m.field_0x38, daPy_HIO_slide_c0::m.field_0x6,
                       daPy_HIO_slide_c0::m.field_0x40);
    return true;
}

/* 80115220-801152D0       .text procSlideBackLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBackLand() {
    cLib_addCalc(&mVelocity, 0.0f, 0.5f, 5.0f, 1.0f);
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        current.angle.y = shape_angle.y;
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_slide_c0::m.field_0x3C) {
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
BOOL daPy_lk_c::procFrontRoll_init(f32) {
    /* Nonmatching */
}

/* 80115478-80115628       .text procFrontRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRoll() {
    /* Nonmatching */
}

/* 80115628-801157D8       .text procFrontRollCrash_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRollCrash_init() {
    commonProcInit(daPyProc_FRONT_ROLL_CRASH_e);
    setSingleMoveAnime(ANM_ROLLFMIS, 0.0f, daPy_HIO_roll_c0::m.field_0x28,
                       daPy_HIO_roll_c0::m.field_0x2, daPy_HIO_roll_c0::m.field_0x2C);
    mVelocity = speedF * daPy_HIO_roll_c0::m.field_0x40;
    speed.y = daPy_HIO_roll_c0::m.field_0x44;
    offNoResetFlg0(daPyFlg0_UNK8);
    current.angle.y += 0x8000;
    dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    voiceStart(8);
    mDoAud_seStart(JA_SE_LK_BODYATTACK, &current.pos, m3620, mReverb);
    onResetFlg0(daPyRFlg0_FRONT_ROLL_CRASH);
    dKy_Sound_set(current.pos, 100, fopAcM_GetID(this), 5);
    if ((mAcch.ChkWallHit()) && (mAcchCir[0].ChkWallHit())) {
        daObjMovebox::Act_c* iVar1 =
            (daObjMovebox::Act_c*)dComIfG_Bgsp()->GetActorPointer(mAcchCir[0].GetBgIndex());
        if ((iVar1 != 0) && (fopAcM_GetName(iVar1) == PROC_Obj_Movebox) &&
            ((iVar1->mType == 0) || (iVar1->mType == 5)))
        {
            iVar1->mbRollCrash = 1;
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
            if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_roll_c0::m.field_0x30) {
                checkNextMode(1);
            }
        }
    }
    if ((mAcch.ChkGroundHit()) && (checkModeFlg(ModeFlg_MIDAIR))) {
        mVelocity = 0.0f;
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(daPy_HIO_roll_c0::m.field_0x24);
        voiceStart(9);
        offModeFlg(ModeFlg_MIDAIR);
        onModeFlg(ModeFlg_00008000);
    }
    return true;
}

/* 801158AC-8011590C       .text procNockBackEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd_init() {
    commonProcInit(daPyProc_NOCK_BACK_END_e);
    setSingleMoveAnime(ANM_ROLLFMIS, daPy_HIO_nockback_c0::m.field_0x2C,
                       daPy_HIO_nockback_c0::m.field_0x30, daPy_HIO_nockback_c0::m.field_0x4,
                       daPy_HIO_nockback_c0::m.field_0x34);
    mVelocity = 0.0f;
    return true;
}

/* 8011590C-80115968       .text procNockBackEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_nockback_c0::m.field_0x38) {
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
    setSingleMoveAnime(dVar2, daPy_HIO_fall_c0::m.field_0x3C, daPy_HIO_fall_c0::m.field_0x40,
                       daPy_HIO_fall_c0::m.field_0x8, daPy_HIO_fall_c0::m.field_0x48);
    mVelocity = daPy_HIO_fall_c0::m.field_0x4C;
    if (checkHeavyStateOn()) {
        mVelocity *= daPy_HIO_move_c0::m.field_0x80;
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
            if (frameCtrl.getFrame() > daPy_HIO_fall_c0::m.field_0x44) {
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
    float fVar1;

    if (mCurProc == daPyProc_BACK_JUMP_e) {
        return false;
    }
    commonProcInit(daPyProc_BACK_JUMP_e);
    if (checkHeavyStateOn()) {
        mVelocity = 0.5f * daPy_HIO_backJump_c0::m.field_0x10;
        fVar1 = 1.5f * daPy_HIO_backJump_c0::m.field_0x4;
    } else {
        mVelocity = daPy_HIO_backJump_c0::m.field_0x10;
        fVar1 = daPy_HIO_backJump_c0::m.field_0x4;
    }
    setSingleMoveAnime(ANM_ROLLB, fVar1, daPy_HIO_backJump_c0::m.field_0x8,
                       daPy_HIO_backJump_c0::m.field_0x0, daPy_HIO_backJump_c0::m.field_0xC);
    speed.y = daPy_HIO_backJump_c0::m.field_0x14;
    gravity = daPy_HIO_backJump_c0::m.field_0x18;
    current.angle.y = shape_angle.y + 0x8000;
    voiceStart(7);
    return true;
}

/* 80115BFC-80115CA0       .text procBackJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJump() {
    if ((mAcch.ChkGroundHit()) && (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f)) {
        procBackJumpLand_init();
    } else {
        if (checkFanGlideProc(0)) {
            return true;
        }
        if (current.pos.y < m3688.y - daPy_HIO_backJump_c0::m.field_0x1C) {
            procFall_init(2, daPy_HIO_backJump_c0::m.field_0x20);
        }
    }
    checkItemChangeFromButton();
    return true;
}

/* 80115CA0-80115DA8       .text procBackJumpLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJumpLand_init() {
    commonProcInit(daPyProc_BACK_JUMP_LAND_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_ROLLBLAND, daPy_HIO_backJump_c0::m.field_0x24,
                       daPy_HIO_backJump_c0::m.field_0x28, daPy_HIO_backJump_c0::m.field_0x2,
                       daPy_HIO_backJump_c0::m.field_0x2C);
    m34BE = 3;
    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
    current.angle.y = shape_angle.y;
    if (checkHeavyStateOn()) {
        dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    }
    if ((((mEquipItem == daPyItem_SWORD_e) || (mEquipItem == daPyItem_BOKO_e)) &&
         (!daPy_dmEcallBack_c::checkCurse())) &&
        (checkNoUpperAnime()))
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
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_backJump_c0::m.field_0x30) {
        checkNextMode(1);
    } else {
        if (mProcVar0.m3570 != 0) {
            mProcVar0.m3570 = 0;
            if ((abs(m3578) > 0xf800) && (mEquipItem == daPyItem_SWORD_e)) {
                procCutTurn_init(1);
            }
        }
    }
    return true;
}

/* 80115E88-80115EA4       .text checkAutoJumpFlying__9daPy_lk_cCFv */
int daPy_lk_c::checkAutoJumpFlying() const {
    return mCurProc != daPyProc_AUTO_JUMP_e ? -1 : m34D0;
}

/* 80115EA4-8011602C       .text procAutoJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAutoJump_init() {
    /* Nonmatching */
}

/* 8011602C-801163D4       .text procAutoJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procAutoJump() {
    /* Nonmatching */
}

/* 801163D4-8011651C       .text procLand_init__9daPy_lk_cFfi */
BOOL daPy_lk_c::procLand_init(f32 param_1, int param_2) {
    commonProcInit(daPyProc_LAND_e);
    mVelocity = 0.0f;
    if (param_2 != 0) {
        setSingleMoveAnime(ANM_JMPEDS, param_1, daPy_HIO_fan_c0::m.field_0x54,
                           daPy_HIO_fan_c0::m.field_0x6, daPy_HIO_fan_c0::m.field_0x58);
    } else {
        setSingleMoveAnime(ANM_JMPEDS, param_1, daPy_HIO_autoJump_c0::m.field_0x28,
                           daPy_HIO_autoJump_c0::m.field_0x4, daPy_HIO_autoJump_c0::m.field_0x34);
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
        if (mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK40_e) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else {
            checkNextMode(0);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_autoJump_c0::m.field_0x40) {
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
        m34D0 = daPy_HIO_fall_c0::m.field_0xC;
        offModeFlg(ModeFlg_DAMAGE);
    } else {
        m34D0 = daPy_HIO_fall_c0::m.field_0x2;
        mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
    }
    setSingleMoveAnime(ANM_LANDDAMA, daPy_HIO_fall_c0::m.field_0x1C, daPy_HIO_fall_c0::m.field_0x20,
                       daPy_HIO_fall_c0::m.field_0x4, daPy_HIO_fall_c0::m.field_0x24);
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
        } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_fall_c0::m.field_0x30) {
            checkNextMode(1);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
        } else {
            f32 fVar1;
            if (checkModeFlg(ModeFlg_DAMAGE)) {
                fVar1 = daPy_HIO_fall_c0::m.field_0x28;
            } else {
                fVar1 = daPy_HIO_fall_c0::m.field_0x50;
            }
            setSingleMoveAnime(ANM_LANDDAMAST, fVar1, daPy_HIO_fall_c0::m.field_0x2C,
                               daPy_HIO_fall_c0::m.field_0x6, daPy_HIO_fall_c0::m.field_0x34);
            mProcVar0.m3570 = 1;
        }
    }
    return true;
}

/* 80116864-80116A38       .text procFall_init__9daPy_lk_cFif */
BOOL daPy_lk_c::procFall_init(int, f32) {
    /* Nonmatching */
}

/* 80116A38-80116C14       .text procFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procFall() {
    /* Nonmatching */
}

/* 80116C14-80116CC4       .text procSlowFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlowFall_init() {
    if (mCurProc == daPyProc_SLOW_FALL_e) {
        return true;
    }
    commonProcInit(daPyProc_SLOW_FALL_e);
    maxFallSpeed = -20.0f;
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_MSTEPOVER_JMPED, 0.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);
    mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getEnd() - 0.001f);
    mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(
        mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    return true;
}

/* 80116CC4-80116D3C       .text procSlowFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlowFall() {
    /* Nonmatching - floats */
    if (current.pos.y - mAcch.GetGroundH() < 200.0f) {
        cLib_chaseF(&maxFallSpeed, -5.0f, 1.0f);
    }
    if (mAcch.ChkGroundHit()) {
        procLand_init(daPy_HIO_fan_c0::m.field_0x50, 1);
    }
    return true;
}

/* 80116D3C-80116EB4       .text procSmallJump_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSmallJump_init(int param_1) {
    /* Nonmatching - floats */
    commonProcInit(daPyProc_SMALL_JUMP_e);
    setSingleMoveAnime(ANM_JMPST, daPy_HIO_smallJump_c0::m.field_0x4,
                       daPy_HIO_smallJump_c0::m.field_0x8, daPy_HIO_smallJump_c0::m.field_0x0,
                       daPy_HIO_smallJump_c0::m.field_0xC);
    if (param_1 == 0) {
        mVelocity = daPy_HIO_smallJump_c0::m.field_0x10;
        speed.y = std::sqrtf(
            -gravity * ((m3724.y - current.pos.y) + daPy_HIO_smallJump_c0::m.field_0x14) * 2.0f);
        mProcVar0.m3570 = 2;
    } else {
        mVelocity = 2.0f * daPy_HIO_smallJump_c0::m.field_0x10;
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
        changeLandProc(daPy_HIO_autoJump_c0::m.field_0x24);
    } else if (checkFanGlideProc(0)) {
        return true;
    } else if (speed.y < -gravity) {
        procFall_init(mProcVar0.m3570, daPy_HIO_smallJump_c0::m.field_0x18);
        setTextureAnime(0x37, 0);
    }
    return true;
}

/* 80116F54-80116FEC       .text procVerticalJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procVerticalJump_init() {
    commonProcInit(daPyProc_VERTICAL_JUMP_e);
    setSingleMoveAnime(ANM_VJMP, daPy_HIO_wallCatch_c0::m.field_0x3C, 0.0f,
                       daPy_HIO_wallCatch_c0::m.field_0x6, daPy_HIO_wallCatch_c0::m.field_0x40);
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
    /* Nonmatching */
}

/* 80117448-801176FC       .text procDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procDamage() {
    /* Nonmatching */
}

/* 801176FC-80117794       .text procPolyDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procPolyDamage_init() {
    commonProcInit(daPyProc_POLY_DAMAGE_e);
    mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
    setSingleMoveAnime(ANM_DAM, daPy_HIO_damage_c0::m.field_0x30, daPy_HIO_damage_c0::m.field_0x34,
                       daPy_HIO_damage_c0::m.field_0x4, daPy_HIO_damage_c0::m.field_0x38);
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
BOOL daPy_lk_c::procLargeDamage_init(int, int, s16, s16) {
    /* Nonmatching */
}

/* 80117EAC-8011810C       .text procLargeDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamage() {
    /* Nonmatching */
}

/* 8011810C-80118504       .text procLargeDamageUp_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamageUp_init(int param_1, int param_2, s16 param_3, s16 param_4) {
    daPy_ANM dVar4;
    short sVar3;
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
    } else if ((param_1 == -1) || (param_1 == -2)) {
        dVar4 = ANM_DAMFBUP;
        dVar6 = 7.0f;
        sVar3 = -1;
        dVar5 = daPy_HIO_laDamage_c0::m.field_0x40;
        m35A0 = 36.0f;
        if (param_1 == -1) {
            m34D0 = 0x1e;
            dVar7 = 0.0f;
        } else {
            m34D0 = 0;
            dVar7 = 0.5f;
        }
    } else if ((param_1 == -4) || (dComIfGp_evmng_startCheck("ICE_FAILED"))) {
        dVar4 = ANM_DAMFBUP;
        dVar7 = 0.0f;
        dVar6 = 7.0f;
        sVar3 = daPy_HIO_huDamage_c0::m.field_0x6;
        dVar5 = daPy_HIO_huDamage_c0::m.field_0x40;
        m35A0 = daPy_HIO_huDamage_c0::m.field_0x3C;
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
                dVar7 = daPy_HIO_laDamage_c0::m.field_0x34;
                dVar6 = daPy_HIO_laDamage_c0::m.field_0x38;
                sVar3 = daPy_HIO_laDamage_c0::m.field_0x6;
                dVar5 = daPy_HIO_laDamage_c0::m.field_0x40;
                m35A0 = daPy_HIO_laDamage_c0::m.field_0x3C;
            } else {
                dVar7 = daPy_HIO_huDamage_c0::m.field_0x34;
                dVar6 = daPy_HIO_huDamage_c0::m.field_0x38;
                sVar3 = daPy_HIO_huDamage_c0::m.field_0x6;
                dVar5 = daPy_HIO_huDamage_c0::m.field_0x40;
                m35A0 = daPy_HIO_huDamage_c0::m.field_0x3C;
            }
        } else if (param_1 == ANM_DAMFL) {
            dVar4 = ANM_DAMFLUP;
            if (param_2 != 0) {
                dVar7 = daPy_HIO_laDamage_c0::m.field_0x44;
                dVar6 = daPy_HIO_laDamage_c0::m.field_0x48;
                sVar3 = daPy_HIO_laDamage_c0::m.field_0x8;
                dVar5 = daPy_HIO_laDamage_c0::m.field_0x50;
                m35A0 = daPy_HIO_laDamage_c0::m.field_0x4C;
            } else {
                dVar7 = daPy_HIO_huDamage_c0::m.field_0x44;
                dVar6 = daPy_HIO_huDamage_c0::m.field_0x48;
                sVar3 = daPy_HIO_huDamage_c0::m.field_0x8;
                dVar5 = daPy_HIO_huDamage_c0::m.field_0x50;
                m35A0 = daPy_HIO_huDamage_c0::m.field_0x4C;
            }
        } else if (param_1 == ANM_DAMFR) {
            dVar4 = ANM_DAMFRUP;
            if (param_2 != 0) {
                dVar7 = daPy_HIO_laDamage_c0::m.field_0x54;
                dVar6 = daPy_HIO_laDamage_c0::m.field_0x58;
                sVar3 = daPy_HIO_laDamage_c0::m.field_0xA;
                dVar5 = daPy_HIO_laDamage_c0::m.field_0x60;
                m35A0 = daPy_HIO_laDamage_c0::m.field_0x5C;
            } else {
                dVar7 = daPy_HIO_huDamage_c0::m.field_0x54;
                dVar6 = daPy_HIO_huDamage_c0::m.field_0x58;
                sVar3 = daPy_HIO_huDamage_c0::m.field_0xA;
                dVar5 = daPy_HIO_huDamage_c0::m.field_0x60;
                m35A0 = daPy_HIO_huDamage_c0::m.field_0x5C;
            }
        } else {
            dVar4 = ANM_DAMFFUP;
            if (param_2 != 0) {
                dVar7 = daPy_HIO_laDamage_c0::m.field_0x24;
                dVar6 = daPy_HIO_laDamage_c0::m.field_0x28;
                sVar3 = daPy_HIO_laDamage_c0::m.field_0x4;
                dVar5 = daPy_HIO_laDamage_c0::m.field_0x30;
                m35A0 = daPy_HIO_laDamage_c0::m.field_0x2C;
            } else {
                dVar7 = daPy_HIO_huDamage_c0::m.field_0x24;
                dVar6 = daPy_HIO_huDamage_c0::m.field_0x28;
                sVar3 = daPy_HIO_huDamage_c0::m.field_0x4;
                dVar5 = daPy_HIO_huDamage_c0::m.field_0x30;
                m35A0 = daPy_HIO_huDamage_c0::m.field_0x2C;
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
        if ((m34D0 == 0) ||
            ((mProcVar0.m3570 == -4 && (g_mDoCPd_cpadInfo[0].mMainStickValue > 0.05f))))
        {
            mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.5f);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (dComIfGp_event_runCheck() != 0) {
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
    /* Nonmatching - branching */
    float fVar1;
    float fVar2;
    short sVar3;
    bool bVar4;
    float fVar5;
    s16 sVar6;
    s16 sVar7;
    short sVar10;

    if (mCurProc == 0x6a) {
        return false;
    }
    cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
    sVar6 = cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z);
    if (!(param_1 < 0)) {
        if (!(triPla->GetNP()->y >= 0.5f) && !(triPla->GetNP()->y < -0.8f)) {
            bVar4 = true;
        } else {
            bVar4 = false;
        }
        if ((bVar4) && (cLib_distanceAngleS(sVar6, current.angle.y + -0x8000) > 0x1555)) {
                return false;
            }
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
            fVar1 = daPy_HIO_laDamage_c0::m.field_0x74;
            fVar2 = daPy_HIO_laDamage_c0::m.field_0x78;
            sVar10 = daPy_HIO_laDamage_c0::m.field_0xE;
            fVar5 = daPy_HIO_laDamage_c0::m.field_0x7C;
        } else {
            fVar1 = daPy_HIO_huDamage_c0::m.field_0x74;
            fVar2 = daPy_HIO_huDamage_c0::m.field_0x78;
            sVar10 = daPy_HIO_huDamage_c0::m.field_0xE;
            fVar5 = daPy_HIO_huDamage_c0::m.field_0x7C;
        }
        m34F2 = sVar3 + -0x4000;
        m34D0 = 0;
    } else if (param_1 == 0x59) {
        mProcVar0.mDamageAnm = ANM_DAMFLUP;
        if (param_2) {
            fVar1 = daPy_HIO_laDamage_c0::m.field_0x80;
            fVar2 = daPy_HIO_laDamage_c0::m.field_0x84;
            sVar10 = daPy_HIO_laDamage_c0::m.field_0x10;
            fVar5 = daPy_HIO_laDamage_c0::m.field_0x88;
        } else {
            fVar1 = daPy_HIO_huDamage_c0::m.field_0x80;
            fVar2 = daPy_HIO_huDamage_c0::m.field_0x84;
            sVar10 = daPy_HIO_huDamage_c0::m.field_0x10;
            fVar5 = daPy_HIO_huDamage_c0::m.field_0x88;
        }
        m34F4 = sVar3 + -0x4000;
        m34D0 = 1;
    } else if (param_1 == 0x5a) {
        mProcVar0.mDamageAnm = ANM_DAMFRUP;
        if (param_2) {
            fVar1 = daPy_HIO_laDamage_c0::m.field_0x8C;
            fVar2 = daPy_HIO_laDamage_c0::m.field_0x90;
            sVar10 = daPy_HIO_laDamage_c0::m.field_0x12;
            fVar5 = daPy_HIO_laDamage_c0::m.field_0x94;
        } else {
            fVar1 = daPy_HIO_huDamage_c0::m.field_0x8C;
            fVar2 = daPy_HIO_huDamage_c0::m.field_0x90;
            sVar10 = daPy_HIO_huDamage_c0::m.field_0x12;
            fVar5 = daPy_HIO_huDamage_c0::m.field_0x94;
        }
        m34F4 = 0x4000 - sVar3;
        m34D0 = 1;
    } else {
        mProcVar0.mDamageAnm = ANM_DAMFFUP;
        if (param_2) {
            fVar1 = daPy_HIO_laDamage_c0::m.field_0x68;
            fVar2 = daPy_HIO_laDamage_c0::m.field_0x6C;
            sVar10 = daPy_HIO_laDamage_c0::m.field_0xC;
            fVar5 = daPy_HIO_laDamage_c0::m.field_0x70;
        } else {
            fVar1 = daPy_HIO_huDamage_c0::m.field_0x68;
            fVar2 = daPy_HIO_huDamage_c0::m.field_0x6C;
            sVar10 = daPy_HIO_huDamage_c0::m.field_0xC;
            fVar5 = daPy_HIO_huDamage_c0::m.field_0x70;
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
    /* Nonmatching - floats */
    if (mCurProc == daPyProc_LAVA_DAMAGE_e) {
        if (speed.y <= 0.0f) {
            speed.y = 30.0f;
        }
        gravity = -2.5f;
        return true;
    } else {
        commonProcInit(daPyProc_LAVA_DAMAGE_e);
        f32 dVar3 = current.pos.absXZ();
        dVar3 = (0.00058823527f * (1700.0f - dVar3) - 0.25f);
        if (dVar3 < 0.0) {
            dVar3 = 0.0f;
        }
        gravity = -2.5f;
        mVelocity = 15.0f + (40.0f * dVar3);
        speed.y = 32.0f + (36.0f * dVar3);
        setSingleMoveAnime(ANM_LAVADAM, daPy_HIO_restart_c0::m.field_0x0, 0.0f, -1,
                           daPy_HIO_restart_c0::m.field_0x4);
        m32E4.makeEmitter(dPa_name::ID_SCENE_8078, mpCLModel->getAnmMtx(0), &current.pos, NULL);
        voiceStart(4);
        seStartMapInfo(JA_SE_LK_FALL_MAGMA);
        current.angle.y = cM_atan2s(current.pos.x, current.pos.z);
        mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
        setDamagePoint(-1.0f);
    }
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
    setSingleMoveAnime(ANM_DAMBIRI, daPy_HIO_elecDamage_c0::m.field_0x4, 0.0f, -1,
                       daPy_HIO_elecDamage_c0::m.field_0x8);
    mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
    m34D0 = daPy_HIO_elecDamage_c0::m.field_0x0;
    if (param_1 != 0) {
        m370C = current.pos - *param_1;
        m34D6 = 1;
    } else {
        if (mCyl.ChkTgHit()) {
            cXyz* pfVar4 = getDamageVec(&mCyl);
            m370C = *pfVar4;
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
        if ((mAcch.ChkGroundHit()) && ((int)m34D6 == 0)) {
            checkNextMode(0);
        } else {
            if ((int)m34D6 != 0) {
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

    cXyz* pfVar2 = getDamageVec(&mCyl);
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
    if ((iVar4 != NULL) &&
        (((iVar4->GetAtSpl() == dCcG_At_Spl_UNK5 || (iVar4->GetAtSpl() == dCcG_At_Spl_UNK6)) ||
          (iVar4->GetAtSpl() == dCcG_At_Spl_UNK7))))
    {
        setSingleMoveAnime(dVar5, daPy_HIO_nockback_c0::m.field_0x8,
                           daPy_HIO_nockback_c0::m.field_0xC, daPy_HIO_nockback_c0::m.field_0x0,
                           daPy_HIO_nockback_c0::m.field_0x10);
        mVelocity = (daPy_HIO_nockback_c0::m.field_0x18 * pfVar2->absXZ()) +
                    daPy_HIO_nockback_c0::m.field_0x14;
        m34D0 = daPy_HIO_nockback_c0::m.field_0x2;
        m35A0 = daPy_HIO_nockback_c0::m.field_0x1C;
        m35A4 = daPy_HIO_nockback_c0::m.field_0x20;
        m35A8 = daPy_HIO_nockback_c0::m.field_0x24;
        m35AC = daPy_HIO_nockback_c0::m.field_0x28;
        mProcVar0.m3570 = (cM_rnd() < 0.2f) ? 1 : 0;
    } else {
        setSingleMoveAnime(dVar5, daPy_HIO_guard_c0::m.field_0x4, daPy_HIO_guard_c0::m.field_0x8,
                           daPy_HIO_guard_c0::m.field_0x0, daPy_HIO_guard_c0::m.field_0xC);
        mVelocity =
            (daPy_HIO_guard_c0::m.field_0x14 * pfVar2->absXZ()) + daPy_HIO_guard_c0::m.field_0x10;
        m34D0 = daPy_HIO_guard_c0::m.field_0x2;
        m35A0 = daPy_HIO_guard_c0::m.field_0x18;
        m35A4 = daPy_HIO_guard_c0::m.field_0x1C;
        m35A8 = daPy_HIO_guard_c0::m.field_0x20;
        m35AC = daPy_HIO_guard_c0::m.field_0x24;
        mProcVar0.m3570 = 0;
    }
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    } else {
        m35E8 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    }
    current.angle.y = cM_atan2s(pfVar2->x, pfVar2->z);
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
    setSingleMoveAnime(mProcVar0.mDamageAnm, 1.0f, 0.0f, -1, daPy_HIO_iceSlip_c0::m.field_0x20);
    mVelocity = 0.0f;
    speed.y = daPy_HIO_iceSlip_c0::m.field_0x1C;
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
    cLib_chaseAngleS(psVar1, m34D4, daPy_HIO_iceSlip_c0::m.field_0x2);
    if ((mAcch.ChkGroundHit()) && (!changeSlideProc())) {
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
        fVar1 = daPy_HIO_iceSlip_c0::m.field_0x34;
        fVar2 = daPy_HIO_iceSlip_c0::m.field_0x38;
        sVar6 = daPy_HIO_iceSlip_c0::m.field_0x6;
        fVar3 = daPy_HIO_iceSlip_c0::m.field_0x40;
        m35A0 = daPy_HIO_iceSlip_c0::m.field_0x3C;
    } else if (param_1 == ANM_DAMFL) {
        dVar5 = ANM_DAMFLUP;
        fVar1 = daPy_HIO_iceSlip_c0::m.field_0x44;
        fVar2 = daPy_HIO_iceSlip_c0::m.field_0x48;
        sVar6 = daPy_HIO_iceSlip_c0::m.field_0x8;
        fVar3 = daPy_HIO_iceSlip_c0::m.field_0x50;
        m35A0 = daPy_HIO_iceSlip_c0::m.field_0x4C;
    } else if (param_1 == ANM_DAMFR) {
        dVar5 = ANM_DAMFRUP;
        fVar1 = daPy_HIO_iceSlip_c0::m.field_0x54;
        fVar2 = daPy_HIO_iceSlip_c0::m.field_0x58;
        sVar6 = daPy_HIO_iceSlip_c0::m.field_0xA;
        fVar3 = daPy_HIO_iceSlip_c0::m.field_0x60;
        m35A0 = daPy_HIO_iceSlip_c0::m.field_0x5C;
    } else {
        dVar5 = ANM_DAMFFUP;
        fVar1 = daPy_HIO_iceSlip_c0::m.field_0x24;
        fVar2 = daPy_HIO_iceSlip_c0::m.field_0x28;
        sVar6 = daPy_HIO_iceSlip_c0::m.field_0x4;
        fVar3 = daPy_HIO_iceSlip_c0::m.field_0x30;
        m35A0 = daPy_HIO_iceSlip_c0::m.field_0x2C;
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
    setSingleMoveAnime(anm, daPy_HIO_iceSlip_c0::m.field_0x64, daPy_HIO_iceSlip_c0::m.field_0x68,
                       daPy_HIO_iceSlip_c0::m.field_0xC, daPy_HIO_iceSlip_c0::m.field_0x70);
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
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_iceSlip_c0::m.field_0x6C) {
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
    setSingleMoveAnime(ANM_SETBOOTS, daPy_HIO_boots_c0::m.field_0x4, daPy_HIO_boots_c0::m.field_0x8,
                       daPy_HIO_boots_c0::m.field_0x0, daPy_HIO_boots_c0::m.field_0x10);
    mProcVar0.m3570 = param_1;
    return true;
}

/* 801198E0-80119A5C       .text procBootsEquip__9daPy_lk_cFv */
BOOL daPy_lk_c::procBootsEquip() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    if (frameCtrl.checkPass(11.0f)) {
        if (checkNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS)) {
            offNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
        } else {
            onNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
        }
    }
    if (frameCtrl.getRate() < 0.01f) {
        if (checkGrabAnime()) {
            initGrabNextMode();
        } else {
            checkNextMode(0);
        }
    } else {
        if (frameCtrl.getFrame() > daPy_HIO_boots_c0::m.field_0xC) {
            if (checkGrabAnime()) {
                if (mStickDistance > 0.05f) {
                    initGrabNextMode();
                }
            } else {
                checkNextMode(1);
            }
        } else {
            if ((frameCtrl.checkPass(15.0f)) && (checkNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS))) {
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
    setSingleMoveAnime(ANM_PRESENTATIONB, daPy_HIO_turn_c0::m.field_0x34,
                       daPy_HIO_turn_c0::m.field_0x38, daPy_HIO_turn_c0::m.field_0x10,
                       daPy_HIO_turn_c0::m.field_0x3C);
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
    if ((m34D4 == 0) && (!checkBottleItem((u16)mProcVar0.mBottleItem))) {
        dComIfGp_event_setItemPartnerId(
            fopAcM_createItemForPresentDemo(&current.pos, mProcVar0.mBottleItem, 5, -1,
                                            fopAcM_GetRoomNo(this), &shape_angle, &scale));
        m34D4 = 1;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        daItemBase_c* item = (daItemBase_c*)fopAcM_getItemEventPartner(this);
        if ((item != NULL) &&
            ((fopAcM_GetName(item) == PROC_ITEM || (fopAcM_GetName(item) == PROC_Demo_Item))))
        {
            item->show();
        }
        if ((m34D4 == 0) && (checkBottleItem((u16)mProcVar0.mBottleItem))) {
            setBottleModel(mProcVar0.mBottleItem);
            m34D4 = 1;
        }
        if (m3628 == fpcM_ERROR_PROCESS_ID_e) {
            m3628 = fopMsgM_messageSet(m3624);
        } else {
            msg_class* msg_p = fopMsgM_SearchByID(m3628);
            if (msg_p != 0) {
                if (msg_p->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                    if ((m3624 == 0xf0c) && (msg_p->mSelectNum == 1)) {
                        msg_p->mStatus = fopMsgStts_MSG_CONTINUES_e;
                        m3624 = 0xf10;
                        fopMsgM_messageSet(m3624);
                        g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserveItemEmpty(
                            mReadyItemBtn);
                    } else {
                        msg_p->mStatus = fopMsgStts_MSG_ENDS_e;
                    }
                } else if (msg_p->mStatus == fopMsgStts_BOX_CLOSED_e) {
                    msg_p->mStatus = fopMsgStts_MSG_DESTROYED_e;
                    if ((item != NULL) && ((fopAcM_GetName(item) == PROC_ITEM ||
                                            (fopAcM_GetName(item) == PROC_Demo_Item))))
                    {
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
    if ((plane == NULL) || (!(plane->GetNP()->y >= 0.5f))) {
        return 0;
    }
    f32 cos = cM_scos((cM_atan2s(plane->GetNP()->x, plane->GetNP()->z) - param_2));
    f32 xz =
        (std::sqrtf(plane->GetNP()->x * plane->GetNP()->x + plane->GetNP()->z * plane->GetNP()->z));
    xz *= cos;
    return cM_atan2s(xz, plane->GetNP()->y);
}

/* 80119EBC-8011A508       .text setLegAngle__9daPy_lk_cFfiPsPs */
void daPy_lk_c::setLegAngle(f32, int, s16*, s16*) {
    /* Nonmatching */
}

/* 8011A508-8011ABB0       .text footBgCheck__9daPy_lk_cFv */
void daPy_lk_c::footBgCheck() {
    /* Nonmatching */
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
    return;
}

/* 8011AC78-8011AD9C       .text autoGroundHit__9daPy_lk_cFv */
void daPy_lk_c::autoGroundHit() {
    u32 uVar4 = checkNoResetFlg0(daPyFlg0_UNK80000000);
    offNoResetFlg0(daPyFlg0_UNK80000000);
    if (mTinkleHoverTimer == 0) {
        offNoResetFlg0(daPyFlg0_HOVER_BOOTS);
    }
    if ((!dComIfGp_event_runCheck()) && (mDemo.getDemoType() == 0)) {
        if (mTinkleHoverTimer > 0) {
            mTinkleHoverTimer--;
        }
    }
    if (checkModeFlg(ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP |
                     ModeFlg_CLIMB | ModeFlg_SWIM | ModeFlg_LADDER | ModeFlg_CAUGHT))
    {
        return;
    }
    f32 fVar1 = mAcch.GetGroundH();
    f32 fVar2 = fVar1 - current.pos.y;
    if (mAcch.ChkGroundHit()) {
        return;
    }
    if (fVar2 < 0.0f) {
        if ((fVar2 >= -30.1f) && (uVar4 == 0)) {
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
    if ((dComIfGp_event_runCheck()) && (mDemo.getDemoType() != 5)) {
        return;
    }
    current.pos.y = old.pos.y;
    mAcch.SetGroundHit();
    speed.y = 0.0f;
    onNoResetFlg0(daPyFlg0_UNK80000000);
    return;
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
    /* Nonmatching */
}

/* 8011BE08-8011BEA4       .text checkOriginalHatAnimation__9daPy_lk_cFv */
void daPy_lk_c::checkOriginalHatAnimation() {
    if ((((checkModeFlg(ModeFlg_WHIDE | ModeFlg_SWIM | ModeFlg_CRAWL)) ||
          (mCurProc == daPyProc_VOMIT_WAIT_e)) ||
         (mCurProc == daPyProc_ELEC_DAMAGE_e)) ||
        ((mCurProc == daPyProc_DEMO_DOOR_OPEN_e ||
          ((!strcmp(dComIfGp_getStartStageName(), "GTower") &&
            (dComIfGp_getStartStageLayer() == 9))))))
    {
        onResetFlg0(daPyRFlg0_UNK800000);
    }
    return;
}

/* 8011BEA4-8011CBA4       .text setHatAngle__9daPy_lk_cFv */
void daPy_lk_c::setHatAngle() {
    /* Nonmatching */
}

/* 8011CBA4-8011CCF4       .text setMoveSlantAngle__9daPy_lk_cFv */
void daPy_lk_c::setMoveSlantAngle() {
    f32 fVar1;
    s16 sVar2;

    fVar1 = std::abs(speedF / mMaxNormalSpeed);
    if (checkModeFlg(ModeFlg_02000000)) {
        mBodyAngle.z = 0;
        m351C = 0;
    } else {
        if ((mCurProc == 6) && (fVar1 > daPy_HIO_move_c0::m.field_0x4C)) {
            cLib_addCalcAngleS(&m351C,
                               daPy_HIO_move_c0::m.field_0x50 * (s16)(m34DE - shape_angle.y) *
                                   ((fVar1 - daPy_HIO_move_c0::m.field_0x4C) /
                                    (1.0f - daPy_HIO_move_c0::m.field_0x4C)),
                               daPy_HIO_move_c0::m.field_0xC, daPy_HIO_move_c0::m.field_0x8,
                               daPy_HIO_move_c0::m.field_0xA);
        } else {
            sVar2 = (m351C * daPy_HIO_move_c0::m.field_0x54);
            if (sVar2 == 0) {
                m351C = 0;
            } else {
                m351C = m351C - sVar2;
            }
        }
        shape_angle.z = m351C >> 1;
        mBodyAngle.z = shape_angle.z;
        return;
    }
}

/* 8011CCF4-8011CDB4       .text setWaistAngle__9daPy_lk_cFv */
void daPy_lk_c::setWaistAngle() {
    float fVar1;
    short sVar2;

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
            sVar2 = (0.7f * m34E2 * fVar1);
        }
    }
    cLib_addCalcAngleS(&m34E0, sVar2, 2, 0x800, 0x200);
    return;
}

/* 8011CDB4-8011D070       .text setWorldMatrix__9daPy_lk_cFv */
void daPy_lk_c::setWorldMatrix() {
    /* Nonmatching */
}

/* 8011D070-8011D0E4       .text setAtParam__9daPy_lk_cFUli11dCcG_At_SplUcUcUcf */
void daPy_lk_c::setAtParam(u32 type, int atp, dCcG_At_Spl spl, u8 se, u8 hitMark, u8 cutType, f32 radius) {
    dCcD_Cps* cps = mAtCps;
    if (type == AT_TYPE_SWORD && checkNoResetFlg1(daPyFlg1_UNK8000)) {
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
    /* Nonmatching */
    static JGeometry::TVec3<f32> normal_scale;
    static JGeometry::TVec3<f32> boss_scale;
}

/* 8011D4D0-8011D6C4       .text setSwordAtCollision__9daPy_lk_cFv */
void daPy_lk_c::setSwordAtCollision() {
    /* Nonmatching */
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
        } else {
            daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
            if (mCurProc == daPyProc_JUMP_CUT_e || mCurProc == daPyProc_JUMP_CUT_LAND_e) {
                return boko->getJumpBlurRate();
            } else {
                return boko->getBlurRate();
            }
        }
    }
    
    return 0.0f;
}

/* 8011D788-8011EC0C       .text setCollision__9daPy_lk_cFv */
void daPy_lk_c::setCollision() {
    /* Nonmatching */
}

/* 8011EC0C-8011EEBC       .text setAttentionPos__9daPy_lk_cFv */
void daPy_lk_c::setAttentionPos() {
    /* Nonmatching */
    {
        static const Vec offset = {0.0f, 30.0f, 20.0f};
    }
    {
        static const Vec offset = {0.0f, 70.0f, 0.0f};
    }
}

/* 8011EEBC-8011EF94       .text setRoomInfo__9daPy_lk_cFv */
int daPy_lk_c::setRoomInfo() {
    /* Nonmatching */
}

/* 8011EF94-8011F9C0       .text setDemoData__9daPy_lk_cFv */
void daPy_lk_c::setDemoData() {
    /* Nonmatching */
}

/* 8011F9C0-8011FF50       .text setStickData__9daPy_lk_cFv */
void daPy_lk_c::setStickData() {
    /* Nonmatching */
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
        mAcchCir[0].SetWallR(daPy_HIO_wall_c0::m.field_0x50);
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
            m35D4 = C_BG_MIN_HEIGHT;
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
    /* Nonmatching */
}

/* 80120724-80120BBC       .text startRestartRoom__9daPy_lk_cFUlifi */
BOOL daPy_lk_c::startRestartRoom(u32 mode, int eventInfoIdx, f32 param_3, int i_point) {
    if (!checkNoResetFlg0(daPyFlg0_UNK4000) && (i_point != 0 || dComIfGp_event_compulsory(this))) {
        mDemo.setOriginalDemoType();
        if (i_point == 0) {
            mDemo.setDemoMode(daPy_demo_c::DEMO_UNK01_e);
        }
        onNoResetFlg0(daPyFlg0_UNK4000);
        changePlayer(this);
        
        if (dComIfGp_getMiniGameType() == 1) {
            dComIfGp_setNextStage("sea", 1, 48);
            mDoAud_seStart(JA_SE_FORCE_BACK);
            daNpc_Sarace_c::ship_race_result = 3;
            mTinkleShieldTimer = 0;
            return TRUE;
        } else {
            u32 stageType = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo());
            setDamagePoint(param_3);
            mTinkleShieldTimer = 0;
            
            if (stageType == dStageType_SEA_e && !dComIfGs_isEventBit(dSv_evtBit_c::RODE_KORL) &&
                (current.roomNo == dIsleRoom_WindfallIsland_e || current.roomNo == dIsleRoom_OutsetIsland_e) &&
                dStage_chkPlayerId(0x80, current.roomNo))
            {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0x80, current.roomNo, -1, 0.0f, mode);
                u32 roomParam = setParamData(-1, 0, eventInfoIdx, 0);
                dComIfGs_setRestartRoomParam(roomParam);
                mDoAud_seStart(JA_SE_FORCE_BACK);
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
                    
                    int quad_x = (1.0f/50000.0f) * (350000.0f + pos->x);
                    int quad_z = (1.0f/50000.0f) * (350000.0f + pos->z);
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
                    int sector_num = sector_z*7 + sector_x;
                    int scls_idx = subsector_x + (sector_num << 2) + (subsector_z << 1);
                    
                    dStage_changeScene(scls_idx, 0.0f, mode, -1);
                } else {
                    if (mCurProc == daPyProc_DEMO_DEAD_e) {
                        dStage_changeScene(0, 0.0f, mode, -1);
                    } else {
                        int roomNo = dComIfGs_getRestartRoomNo();
                        u32 roomParam = setParamData(roomNo, 0, eventInfoIdx, 0);
                        dStage_restartRoom(roomParam, mode);
                        mDoAud_seStart(JA_SE_FORCE_BACK);
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
                mDoAud_seStart(JA_SE_FORCE_BACK);
            }
            
            return TRUE;
        }
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
    /* Nonmatching */
}

/* 80120F94-801211B8       .text setStepsOffset__9daPy_lk_cFv */
void daPy_lk_c::setStepsOffset() {
    /* Nonmatching */
}

/* 801211B8-8012135C       .text setBeltConveyerPower__9daPy_lk_cFv */
void daPy_lk_c::setBeltConveyerPower() {
    /* Nonmatching */
}

/* 8012135C-801216A8       .text setWindAtPower__9daPy_lk_cFv */
void daPy_lk_c::setWindAtPower() {
    /* Nonmatching */
}

/* 801216A8-80121870       .text checkRoofRestart__9daPy_lk_cFv */
void daPy_lk_c::checkRoofRestart() {
    /* Nonmatching - math */
    if ((mAcch.ChkRoofHit()) && (mAcch.ChkGroundHit())) {
        if (((mCurProc != daPyProc_CRAWL_START_e)) &&
            ((mCurProc != daPyProc_CRAWL_END_e && (mCurProc != daPyProc_WHIDE_READY_e))))
        {
            if ((dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_BOSS_e &&
                 ((!dComIfG_Bgsp()->ChkMoveBG(mAcch.m_roof) ||
                   (fopAcM_GetName(dComIfG_Bgsp()->GetActorPointer(mAcch.m_roof.GetBgIndex())) !=
                    PROC_BRIDGE)))))
            {
                f32 dVar9 = mAcch.m_roof_y;
                if (dVar9 > mAcch.GetGroundH()) {
                    f32 dVar10 = mHeadTopPos.y - 10.0f;
                    f32 fVar1 = current.pos.y;
                    f32 dVar8 = 10.0f + fVar1;
                    if (dVar10 < dVar8) {
                        dVar10 = dVar8;
                    }
                    if (dVar9 < dVar10) {
                        if (checkModeFlg(ModeFlg_WHIDE)) {
                            f32 fVar4 = 35.0f -
                                        daPy_HIO_wall_c0::m.field_0x50 * cM_scos(shape_angle.y) +
                                        current.pos.z;
                            cXyz local_8;
                            local_8.set(current.pos.x + fVar4 * cM_ssin(shape_angle.y), fVar1,
                                        fVar4);
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
        }
    }
    return;
}

/* 80121870-80122D30       .text execute__9daPy_lk_cFv */
BOOL daPy_lk_c::execute() {
    /* Nonmatching - regalloc */
    if (setGetDemo()) {
        return TRUE;
    }
    
    if (checkNoResetFlg1(daPyFlg1_UNK200)) {
        fopMsgM_demoMsgFlagOn();
        if (checkEndMessage(0x14A3)) {
            offNoResetFlg1(daPyFlg1_UNK200);
            dComIfGs_setEventReg(0x9EFF, 0);
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
                if (mCurProc == daPyProc_SCOPE_e) {
                    procWait_init();
                }
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
    
    current.pos = l_debug_keep_pos;
    shape_angle = l_debug_shape_angle;
    current.angle = l_debug_current_angle;
    
    mCameraInfoIdx = dComIfGp_getPlayerCameraID(0);
    m3748 = current.pos;
    
    if (mCurProc != daPyProc_HOOKSHOT_FLY_e &&
        !dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
        !checkModeFlg(ModeFlg_ROPE | ModeFlg_CLIMB | ModeFlg_LADDER) &&
        mCurProc != daPyProc_DEMO_TOOL_e &&
        mAcch.GetGroundH() != C_BG_MIN_HEIGHT &&
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
        if (m3574 != 0 && mAcch.GetGroundH() != C_BG_MIN_HEIGHT) {
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
    if (mAcch.GetGroundH() != C_BG_MIN_HEIGHT) {
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
                    onResetFlg0(daPyRFlg0_UNK200);
                }
                offNoResetFlg0(daPyFlg0_UNK400000);
                if (current.pos.y < 2000.0f && dComIfG_Bgsp()->GetSpecialCode(mAcch.m_gnd) != 1) {
                    cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
                    if (triPla->GetNP()->y >= 0.5f) {
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
        roomNo = current.roomNo;
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
    
    checkOriginalHatAnimation();
    
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
    
    if (mEquipItem == daPyItem_BOKO_e && mActorKeepEquip.getActor()) {
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
    eventInfo.onCondition(dEvtCnd_CANGETITEM_e);
    
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
        if (checkResetFlg0(daPyRFlg0_UNK10000000)) {
            dComIfGp_setAStatus(dActStts_BLANK_e);
        }
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
    
    l_debug_keep_pos = current.pos;
    l_debug_shape_angle = shape_angle;
    l_debug_current_angle = current.angle;
    
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
    if (mFanSwingCb.mpEmitter) {
        mFanSwingCb.mpEmitter->quitImmortalEmitter();
        mFanSwingCb.mpEmitter->setEmitterCallBackPtr(NULL);
        mFanSwingCb.mpEmitter = NULL;
    }
    m338C.end();
    m33A8.end();
    m3280.end();
    m334C.end();
    m336C.end();
    mSwimTailEcallBack[0].remove();
    mSwimTailEcallBack[1].remove();
    m32E4.end();
    m32F0.end();
    m33E8.end();
    mSmokeEcallBack.end();
    m331C.end();
    m332C.end();
    m333C.end();
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
    g_dComIfG_gameInfo.play.field_0x4947 = 0;
    
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
    JUT_ASSERT(20869, m_tex_anm_heap.m_buffer != NULL);
    
    JKRReadIdxResource(m_tex_anm_heap.m_buffer, 0x1000, LKANM_BTP_TMABAA, dComIfGp_getAnmArchive());
    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(J3DAnmLoaderDataBase::load(m_tex_anm_heap.m_buffer));
    btp->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btp->getUpdateMaterialNum();
    m_texNoAnms = new J3DTexNoAnm[material_num];
    JUT_ASSERT(20885, m_texNoAnms != NULL);
    
    for (u16 i = 0; i < material_num; i++) {
        u16 matID = btp->getUpdateMaterialID(i);
        if (matID != 0xFFFF) {
            J3DMaterialAnm* mat_anm = new J3DMaterialAnm();
            JUT_ASSERT(20894, mat_anm != NULL);
            
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
    /* Nonmatching - regalloc */
    m_tex_scroll_heap.m_buffer = new(0x20) u8[0x800];
    JUT_ASSERT(20944, m_tex_scroll_heap.m_buffer != NULL);
    
    JKRReadIdxResource(m_tex_scroll_heap.m_buffer, 0x800, LKANM_BTK_TMABA, dComIfGp_getAnmArchive());
    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(m_tex_scroll_heap.m_buffer));
    btk->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btk->getUpdateMaterialNum();
    JUT_ASSERT(20958, material_num == 2);
    
    m_texMtxAnm = new J3DTexMtxAnm[material_num];
    JUT_ASSERT(20961, m_texMtxAnm != NULL);
    
    for (u16 no = 0; no < material_num; no++) {
        u16 matID = btk->getUpdateMaterialID(no);
        if (matID != 0xFFFF) {
            m_tex_eye_scroll[no] = new daPy_matAnm_c();
            JUT_ASSERT(20972, m_tex_eye_scroll[no] != NULL);
            
            mpCLModelData->getMaterialNodePointer(matID)->change();
            mpCLModelData->getMaterialNodePointer(matID)->setMaterialAnm(m_tex_eye_scroll[no]);
            
            J3DMaterial* mtl = mpCLModelData->getMaterialNodePointer(matID);
            u8 texMtxID = btk->getUpdateTexMtxID(no);
            if (texMtxID != 0xFF) {
                J3DTexMtx* tmtx;
                if (mtl->getTexMtx(texMtxID) == NULL) {
                    tmtx = new J3DTexMtx();
                    JUT_ASSERT(20984, tmtx != NULL);
                    mtl->setTexMtx(no, tmtx);
                }
                if (mtl->getTexCoord(texMtxID) != NULL) {
                    mtl->getTexCoord(texMtxID)->setTexGenMtx(GX_TEXMTX0 + (texMtxID & 0xFF) * 3);
                }
                tmtx = mtl->getTexMtx(no);
                
                m_texMtxAnm[no].setAnmTransform(btk);
                m_texMtxAnm[no].setAnmIndex(no);
                
                tmtx->getTexMtxInfo().mInfo = (tmtx->getTexMtxInfo().mInfo & 0x7F) | btk->getTexMtxCalcType() << 7;
                // Fakematch? The codegen doesn't match unless a temp variable is used and assigned to multiple times.
                Vec* temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.x = temp->x;
                temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.y = temp->y;
                temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.z = temp->z;
                
                JUT_ASSERT(21001, mtl->getMaterialAnm() != NULL);
                
                mtl->getMaterialAnm()->setTexMtxAnm(texMtxID, &m_texMtxAnm[no]);
            }
        }
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
    if (!ret) { JUT_ASSERT(21046, FALSE); }
    mpTswgripmsabBrk = entryBrk(tmp_modelData, LINK_BRK_TSWGRIPMSAB);
    mpTswgripmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSWGRIPMS);
    
    tmp_modelData = initModel(&mpPodmsModel, LINK_BDL_PODMS, 0x37221222);
    
    tmp_modelData = initModel(&mpShaModel, LINK_BDL_SHA, 0x37221222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_ATNGSHA);
    ret = mAtngshaBck.init(mpShaModel->getModelData(), bck, false, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21063, FALSE); }
    
    tmp_modelData = initModel(&mpShmsModel, LINK_BDL_SHMS, 0x37221222);
    mpTshmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSHMS);
    J3DSkinDeform* shmsSkinDeform = new J3DSkinDeform();
    if (!shmsSkinDeform) { JUT_ASSERT(21077, FALSE); }
    if (mpShmsModel->setSkinDeform(shmsSkinDeform, 1) != J3DErrType_Success ) { JUT_ASSERT(21080, FALSE); }
    
    tmp_modelData = initModel(&mpYmsls00Model, LINK_BDL_YMSLS00, 0x13000222);
    mpYmsls00Btk = entryBtk(tmp_modelData, LINK_BTK_YMSLS00);
    
    tmp_modelData = initModel(&mpHbootsModels[0], LINK_BDL_HBOOTS, 0x37221222);
    tmp_modelData = initModel(&mpHbootsModels[1], LINK_BDL_HBOOTS, 0x37221222);
    
    tmp_modelData = initModel(&mpSuimenMunyaModel, LINK_BDL_SUIMEN_MUNYA, 0x11001222);
    mpSuimenMunyaBtk = entryBtk(tmp_modelData, LINK_BTK_SUIMEN_MUNYA);
    
    tmp_modelData = initModel(&mpYuchw00Model, LINK_BDL_YUCHW00, 0x13000222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_YUCHW00);
    ret = mYuchw00Bck.init(tmp_modelData, bck, 1, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21113, FALSE); }
    mpYuchw00Btk = entryBtk(tmp_modelData, LINK_BTK_YUCHW00);
    mpYuchw00Brk = entryBrk(tmp_modelData, LINK_BRK_YUCHW00);
    mpYuchw00Brk->setFrame(mpYuchw00Brk->getFrameMax()-0.001f);
    
    tmp_modelData = initModel(&mpYbafo00Model, LINK_BDL_YBAFO00, 0x13000222);
    mpYbafo00Btk = entryBtk(tmp_modelData, LINK_BTK_YBAFO00);
    mpYbafo00Btk->setFrame(mpYbafo00Btk->getFrameMax()-0.001f);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_YAURA00));
    JUT_ASSERT(21130, tmp_modelData != NULL);
    daPy_aura_c* aura_p = mMagicArmorAuraEntries;
    for (int i = 0; i < 6; i++) {
        aura_p->setModel(mDoExt_J3DModel__create(tmp_modelData, 0x00080000, 0x11001222));
        JUT_ASSERT(21139, aura_p->getModel() != NULL);
        aura_p++;
    }
    mpYaura00Btk = entryBtk(tmp_modelData, LINK_BTK_YAURA00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YAURA00_R);
    ret = mYaura00rBrk.init(tmp_modelData, brk, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(21147, FALSE); }
    mYaura00rBrk.entryFrame(0.0f);
    
    tmp_modelData = initModel(&mpYmgcs00Model, LINK_BDL_YMGCS00, 0x11001222);
    mpYmgcs00Btk = entryBtk(tmp_modelData, LINK_BTK_YMGCS00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YMGCS00_MS);
    ret = mYmgcs00Brk.init(tmp_modelData, brk, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(21161, FALSE); }
    mYmgcs00Brk.entryFrame(0.0f);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_BOMB));
    JUT_ASSERT(21169, tmp_modelData != NULL);
    mpBombBrk = entryBrk(tmp_modelData, LINK_BRK_BOMB);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GWP00));
    JUT_ASSERT(21176, tmp_modelData != NULL);
    mpGwp00BrkData = entryBrk(tmp_modelData, LINK_BRK_GWP00);
    mpGwp00BtkData = entryBtk(tmp_modelData, LINK_BTK_GWP00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROW));
    JUT_ASSERT(21184, tmp_modelData != NULL);
    mpIceArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TTIPICE);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROWGLITTER));
    JUT_ASSERT(21191, tmp_modelData != NULL);
    mpLightArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TARROWGLITTER);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER00));
    JUT_ASSERT(21198, tmp_modelData != NULL);
    mpGicer00Btk = entryBtk(tmp_modelData, LINK_BTK_GICER00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER01));
    JUT_ASSERT(21205, tmp_modelData != NULL);
    mpGicer01Btk = entryBtk(tmp_modelData, LINK_BTK_GICER01);
    
    const int numCLJoints = 0x2A;
    m_old_fdata = new mDoExt_MtxCalcOldFrame(new J3DTransformInfo[numCLJoints], new Quaternion[numCLJoints]);
    JUT_ASSERT(21233, m_old_fdata != NULL);
    
    m_pbCalc[PART_UNDER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUnder), mAnmRatioUnder);
    JUT_ASSERT(21239, m_pbCalc[PART_UNDER_e] != NULL);
    
    m_pbCalc[PART_UPPER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUpper), mAnmRatioUpper);
    JUT_ASSERT(21245, m_pbCalc[PART_UPPER_e] != NULL);
    
    initTextureScroll();
    initTextureAnime();
    
    m_HIO = new daPy_HIO_c();
    JUT_ASSERT(21254, m_HIO != NULL);
    
    m_anm_heap_under[UNDER_MOVE0_e].m_buffer = new(0x20) u8[0xB400];
    JUT_ASSERT(21259, m_anm_heap_under[UNDER_MOVE0_e].m_buffer != NULL);
    
    m_sanm_buffer = new(0x20) u8[0x200];
    JUT_ASSERT(21266, m_sanm_buffer != NULL);
    
    m_item_bck_buffer = new(0x20) u8[0x1000];
    JUT_ASSERT(21269, m_item_bck_buffer != NULL);
    
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
        JUT_ASSERT(21307, tmp_trans_bas != NULL);
    } else if (heapType == HEAP_TYPE_UNDER_UPPER_e) {
        J3DAnmTransformKey* tmp_trans = new J3DAnmTransformKey;
        JUT_ASSERT(21310, tmp_trans != NULL);
    } else if (heapType == HEAP_TYPE_TEXTURE_ANIME_e) {
        J3DAnmTexPattern* tmp_tp = new J3DAnmTexPattern;
        JUT_ASSERT(21313, tmp_tp != NULL);
    } else { // heapType == HEAP_TYPE_TEXTURE_SCROLL_e
        J3DAnmTextureSRTKey* tmp_tk = new J3DAnmTextureSRTKey;
        JUT_ASSERT(21316, tmp_tk != NULL);
    }
    
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(*pHeap);
}

/* 80124A40-80124B30       .text initModel__9daPy_lk_cFPP8J3DModeliUl */
J3DModelData* daPy_lk_c::initModel(J3DModel** i_model, int i_fileIndex, u32 i_differedDlistFlag) {
    J3DModelData* tmp_modelData;
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, i_fileIndex));
    JUT_ASSERT(21340, tmp_modelData != NULL);
    *i_model = mDoExt_J3DModel__create(tmp_modelData, 0x00080000, i_differedDlistFlag);
    JUT_ASSERT(21344, *i_model != NULL);
    return tmp_modelData;
}

/* 80124B30-80124BE4       .text entryBtk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTextureSRTKey* daPy_lk_c::entryBtk(J3DModelData* param_1, int param_2) {
    J3DAnmTextureSRTKey* btk_anm =
        static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(l_arcName, param_2));
    JUT_ASSERT(21373, btk_anm != 0);
    btk_anm->searchUpdateMaterialID(param_1);
    param_1->entryTexMtxAnimator(btk_anm);
    btk_anm->setFrame(0.0f);
    return btk_anm;
}

/* 80124BE4-80124C98       .text entryBrk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTevRegKey* daPy_lk_c::entryBrk(J3DModelData* param_1, int param_2) {
    J3DAnmTevRegKey* brk_anm =
        static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(l_arcName, param_2));
    JUT_ASSERT(21395, brk_anm != 0);
    brk_anm->searchUpdateMaterialID(param_1);
    param_1->entryTevRegAnimator(brk_anm);
    brk_anm->setFrame(0.0f);
    return brk_anm;
}

/* 80124C98-80125CC8       .text playerInit__9daPy_lk_cFv */
void daPy_lk_c::playerInit() {
    if (!fopAcM_entrySolidHeap(this, daPy_createHeap, 0xB0000)) {
        JUT_ASSERT(0x53B6, FALSE);
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
                // TODO: debug map indicates J3DBlend::getType inline was used
                if (mtl->getBlend()->mBlendMode == GX_BM_BLEND) {
                    mpZOffBlendShape[zoff_blend_cnt] = mtl->getShape();
                    zoff_blend_cnt++;
                    JUT_ASSERT(0x53EE, zoff_blend_cnt <= 4);
                } else {
                    mpZOffNoneShape[zoff_none_cnt] = mtl->getShape();
                    zoff_none_cnt++;
                    JUT_ASSERT(0x53F2, zoff_none_cnt <= 4);
                }
            } else {
                mpZOnShape[zon_cnt] = mtl->getShape();
                zon_cnt++;
                JUT_ASSERT(0x53F6, zon_cnt <= 4);
            }
            mtl = mtl->getNext();
        }
        mtl = mpCLModelData->getJointNodePointer(0x15)->getMesh(); // cl_mayu joint
    }
    JUT_ASSERT(0x53FD, zon_cnt == 4);
    JUT_ASSERT(0x53FE, zoff_none_cnt == 4);
    JUT_ASSERT(0x53FF, zoff_blend_cnt == 4);
    
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
    
    mAcch.Set(&current.pos, &old.pos, this, ARRAY_SIZE(mAcchCir), mAcchCir, &speed, &current.angle, &shape_angle);
    mAcch.ClrWaterNone();
    mAcch.SetWaterCheckOffset(500.0f);
    mAcch.OnLineCheck();
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(125.0f);
    mMaxNormalSpeed = daPy_HIO_move_c0::m.field_0x18;
    gravity = daPy_HIO_autoJump_c0::m.field_0xC;
    maxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
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
    JUT_ASSERT(0x5493, dummy_data != NULL);
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(mpItemHeaps[0]);
    
    mpItemHeaps[1] = mDoExt_createSolidHeapFromGameToCurrent(0xE600, 0x20);
    dummy_data = new u8[0xE600];
    JUT_ASSERT(0x5499, dummy_data != NULL);
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
    JUT_ASSERT(0x54B7, tmp_tex != NULL);
    mSightPacket.setSightTex(tmp_tex);
    ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_ROCK_MARK);
    JUT_ASSERT(0x54BD, tmp_img != NULL);
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
    JUT_ASSERT(0x5504, texture != NULL);
    JUTNameTab* textureName = mpCLModelData->getTextureName();
    JUT_ASSERT(0x5506, textureName != NULL);
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
        
        if (!dComIfGs_isEventBit(0x2A80) || dComIfGs_getClearCount() != 0) {
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
daPy_footData_c::daPy_footData_c() {
    /* Nonmatching - regalloc */
}

/* 80127160-80127B50       .text makeBgWait__9daPy_lk_cFv */
cPhs_State daPy_lk_c::makeBgWait() {
    /* Nonmatching */
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
        JUT_ASSERT(22318, data_size < l_sanm_buffer_size);
        
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
void daPy_lk_c::setMoveAnime(f32, f32, f32, daPy_ANM, daPy_ANM, int, f32) {
    /* Nonmatching */
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
        mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
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
    return;
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
        if (r4 == 6 || fopAcM_GetParam(boko) == r4) {
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
    if (!(dComIfGp_event_runCheck()) && (dComIfGp_getScopeType() != 1)) {
        return;
    }
    if (param_1 != NULL) {
        current.pos = *param_1;
        old.pos = current.pos;
    }
    shape_angle.y = param_2;
    current.angle.y = param_2;
    m34DE = shape_angle.y;
    l_debug_keep_pos = current.pos;
    l_debug_shape_angle = shape_angle;
    l_debug_current_angle = current.angle;
    return;
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
    l_debug_keep_pos = current.pos;
    l_debug_shape_angle = shape_angle;
    l_debug_current_angle = current.angle;
    return;
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
        l_debug_keep_pos = current.pos;
        l_debug_shape_angle = shape_angle;
        l_debug_current_angle = current.angle;
    }
    return;
}

/* 80128DC0-80128F8C       .text endDemoMode__9daPy_lk_cFv */
void daPy_lk_c::endDemoMode() {
    /* Nonmatching - missing clrlwi instruction */
    if (mCurProc != daPyProc_LARGE_DAMAGE_e) {
        current.angle.y = shape_angle.y;
    }
    offNoResetFlg0(daPyFlg0_UNK100000);
    dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK10_e);
    mDemo.setDemoType(0);
    mDemo.setDemoMode(0);
    mDemo.setParam0(0);
    mDemo.setParam1(0);
    mDemo.setStick(1.0f);
    resetDemoTextureAnime();
    if ((mEquipItem == daPyItem_UNK104_e) || (mEquipItem == daPyItem_UNK10A_e)) {
        deleteEquipItem(FALSE);
        offNoResetFlg1(daPyFlg1_SHIP_TACT);
    }
    mDoAud_taktModeMuteOff();
    if ((((mAcch.ChkGroundHit()) &&
          (!checkModeFlg(ModeFlg_MIDAIR | ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_IN_SHIP |
                         ModeFlg_CLIMB | ModeFlg_SWIM | ModeFlg_LADDER | ModeFlg_04000000 |
                         ModeFlg_CAUGHT))) &&
         (mCurProc != daPyProc_LARGE_DAMAGE_UP_e)) &&
        ((mCurProc != daPyProc_DEMO_DEAD_e && (mCurProc != daPyProc_DEMO_LAVA_DAMAGE_e))))
    {
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e)) {
            procScope_init(0x20);
            return;
        }
        changeWaitProc();
        return;
    }
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        if (dComIfGp_getShipActor() == NULL) {
            checkNextMode(0);
        } else if (daPy_getPlayerActorClass() != this) {
            procControllWait_init();
        } else if (dComIfGp_getShipActor()->getPart() == daShip_c::PART_CANNON_e) {
            procShipCannon_init();
        } else if (dComIfGp_getShipActor()->getPart() == daShip_c::PART_CRANE_e) {
            procShipCrane_init();
        } else if (dComIfGp_getShipActor()->getPart() == daShip_c::PART_STEER_e) {
            procShipSteer_init();
        } else {
            procShipPaddle_init();
        }
    } else {
        if (mCurProc == daPyProc_DEMO_BOSS_WARP_e) {
            procWait_init();
        }
    }
    return;
}

/* 80128F8C-8012901C       .text getBokoFlamePos__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::getBokoFlamePos(cXyz* outPos) {
    if (mEquipItem == daPyItem_BOKO_e) {
        daBoko_c* boko = (daBoko_c*)fopAcM_SearchByID(mActorKeepEquip.getID());
        if (boko && boko->m2C4 != 0) { // maybe daBoko_c::getFlameTimer inline
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
    /* Priority     */ 0x0068,
    /* Actor SubMtd */ (actor_method_class*)&l_daPy_Method,
    /* Status       */ fopAcStts_FREEZE_e,
    /* Group        */ fopAc_PLAYER_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
    /* field_0x30   */ 2,
};
