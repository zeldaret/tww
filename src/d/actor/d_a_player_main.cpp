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
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"
#include "d/d_material.h"
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"
#include "d/actor/d_a_hookshot.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_boko.h"
#include "SSystem/SComponent/c_counter.h"
#include "m_Do/m_Do_graphic.h"

cXyz l_hammer_splash_particle_scale(0.00002f, 0.00002f, 0.00002f);

cXyz l_debug_keep_pos;
csXyz l_debug_current_angle;
csXyz l_debug_shape_angle;

#include "d/actor/d_a_player_main_data.inc"

#include "d/actor/d_a_player_HIO.inc"

static u8 l_sightDL[] ALIGN_DECL(32) = {
    0x10, 0x00, 0x00, 0x10, 0x40, 0xFF, 0xFF, 0x42, 0x80, 0x08, 0x30, 0x3C, 0xF3, 0xCF, 0x00,
    0x10, 0x00, 0x00, 0x10, 0x18, 0x3C, 0xF3, 0xCF, 0x00,
    0x61, 0x28, 0x38, 0x03, 0xC0,
    0x61, 0xC0, 0x08, 0x42, 0x8F,
    0x61, 0xC1, 0x08, 0xE6, 0x70,
    0x61, 0x43, 0x00, 0x00, 0x01,
    0x61, 0x40, 0x00, 0x00, 0x06,
    0x61, 0x41, 0x00, 0x04, 0xAD,
    0x61, 0xF3, 0x64, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x10, 0x3F, 0x00, 0x00, 0x00, 0x01,
    0x10, 0x00, 0x00, 0x10, 0x09, 0x00, 0x00, 0x00, 0x00,
    0x61, 0x00, 0x00, 0x00, 0x01,
    0x98, 0x00, 0x04, 0x01, 0x01, 0x00, 0x01,
    0x01, 0xFF, 0x01, 0x00, 0x00, 0x01, 0x01, 0xFF, 0x00, 0x01, 0x00, 0xFF, 0xFF,
    
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
};

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

GXColor l_freeze_fade_color = {0xFF, 0xFF, 0xFF, 0xFF};

u8 daPy_matAnm_c::m_maba_flg;
u8 daPy_matAnm_c::m_eye_move_flg;
u8 daPy_matAnm_c::m_maba_timer;
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
    if (mLastUsedItemButtonIdx == 0) {
        return m34C9 & 0x04;
    } else if (mLastUsedItemButtonIdx == 1) {
        return m34C9 & 0x08;
    } else {
        return m34C9 & 0x10;
    }
}

/* 801031DC-80103214       .text itemTrigger__9daPy_lk_cCFv */
BOOL daPy_lk_c::itemTrigger() const {
    if (mLastUsedItemButtonIdx == 0) {
        return mPressedButtons & 0x04;
    } else if (mLastUsedItemButtonIdx == 1) {
        return mPressedButtons & 0x08;
    } else {
        return mPressedButtons & 0x10;
    }
}

/* 80103214-80103258       .text getReadyItem__9daPy_lk_cFv */
u8 daPy_lk_c::getReadyItem() {
    if (mLastUsedItemButtonIdx == 0) {
        return dComIfGp_getSelectItem(0);
    } else if (mLastUsedItemButtonIdx == 1) {
        return dComIfGp_getSelectItem(1);
    } else {
        return dComIfGp_getSelectItem(2);
    }
}

/* 80103258-801032E4       .text checkGroupItem__9daPy_lk_cFii */
BOOL daPy_lk_c::checkGroupItem(int param_1, int itemNo) {
    if (param_1 == 0x105) {
        return checkDrinkBottleItem(itemNo);
    } else if (param_1 == 0x106) {
        return checkOpenBottleItem(itemNo);
    } else if (param_1 == 0x107) {
        return isEsa(itemNo);
    } else if (param_1 == 0x108) {
        return checkBowItem(itemNo);
    } else if (param_1 == 0x109) {
        return checkPhotoBoxItem(itemNo);
    } else {
        return param_1 == itemNo;
    }
}

/* 801032E4-801033E4       .text checkSetItemTrigger__9daPy_lk_cFii */
BOOL daPy_lk_c::checkSetItemTrigger(int param_1, int param_2) {
    if (param_2 == 0 || !daPy_dmEcallBack_c::checkCurse()) {
        if (mPressedButtons & 0x04 && checkGroupItem(param_1, dComIfGp_getSelectItem(0))) {
            mLastUsedItemButtonIdx = 0;
            return TRUE;
        }
        if (mPressedButtons & 0x08 && checkGroupItem(param_1, dComIfGp_getSelectItem(1))) {
            mLastUsedItemButtonIdx = 1;
            return TRUE;
        }
        if (mPressedButtons & 0x10 && checkGroupItem(param_1, dComIfGp_getSelectItem(2))) {
            mLastUsedItemButtonIdx = 2;
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
static BOOL daPy_auraCallback(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->auraJointCB0(jntNo);
    }
    return TRUE;
}

/* 80103494-80103A88       .text jointBeforeCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
BOOL daPy_lk_c::jointBeforeCB(int, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
    static Mtx root_mtx;
    static Quaternion norm_quat = {0.0f, 0.0f, 0.0f, 1.0f};
}

/* 80103A88-80103AAC       .text daPy_jointBeforeCallback__FUlUsP16J3DTransformInfoP10Quaternion */
static BOOL daPy_jointBeforeCallback(u32 userArea, u16 param_1, J3DTransformInfo* param_2, Quaternion* param_3) {
    return reinterpret_cast<daPy_lk_c*>(userArea)->jointBeforeCB(param_1, param_2, param_3);
}

/* 80103AAC-80103C1C       .text jointAfterCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
BOOL daPy_lk_c::jointAfterCB(int, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
}

/* 80103C1C-80103C40       .text daPy_jointAfterCallback__FUlUsP16J3DTransformInfoP10Quaternion */
static BOOL daPy_jointAfterCallback(u32 userArea, u16 param_1, J3DTransformInfo* param_2, Quaternion* param_3) {
    return reinterpret_cast<daPy_lk_c*>(userArea)->jointAfterCB(param_1, param_2, param_3);
}

/* 80103C40-80103EE4       .text jointCB0__9daPy_lk_cFi */
BOOL daPy_lk_c::jointCB0(int) {
    /* Nonmatching */
    static f32 guard_rate = 0.0f;
}

/* 80103EE4-80103F28       .text daPy_jointCallback0__FP7J3DNodei */
static BOOL daPy_jointCallback0(J3DNode* node, int param_1) {
    if (!param_1) {
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
    /* Nonmatching */
}

/* 80104178-801041B4       .text daPy_jointCallback1__FP7J3DNodei */
static BOOL daPy_jointCallback1(J3DNode* node, int param_1) {
    if (!param_1) {
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
    JKRReadIdxResource(mSwBlur.mpPosBuffer, 0x4800, index, dComIfGp_getAnmArchive());
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
BOOL daPy_lk_c::checkNormalFace() {
    /* Nonmatching */
}

/* 80104A08-80104E08       .text setTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setTextureAnime(u16, int) {
    /* Nonmatching */
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
    daPy_matAnm_c::setMabaTimer(1);
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
    /* Nonmatching */
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
        pBootModels[0]->setAnmMtx(0x01, mpCLModel->getAnmMtx(0x26));
        pBootModels[1]->setAnmMtx(0x01, mpCLModel->getAnmMtx(0x21));
        bootsJointIdx = 2;
    } else {
        bootsJointIdx = 1;
    }
    
    J3DModel* bootModel = pBootModels[0];
    bootModel->setAnmMtx(bootsJointIdx, mpCLModel->getAnmMtx(0x28));
    bootModel->setAnmMtx(bootsJointIdx+1, mpCLModel->getAnmMtx(0x27));
    
    bootModel = pBootModels[1];
    bootModel->setAnmMtx(bootsJointIdx, mpCLModel->getAnmMtx(0x23));
    bootModel->setAnmMtx(bootsJointIdx+1, mpCLModel->getAnmMtx(0x22));
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
    /* Nonmatching - regalloc */
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
        f32 f2 = fabsf(cM_ssin(g_Counter.mTimer * 0x800));
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
                entryDLSetLight(mpYamuModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
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
        if (!checkNormalSwordEquip() && dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_FF1_e ||
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
        entryDLSetLight(mpHandsModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES) && !checkCaughtShapeHide() && !dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
            entryDLSetLight(mpKatsuraModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        if (checkFreezeState() && checkMaskDraw()) {
            entryDLSetLight(mpYamuModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        if (dComIfGs_getSelectEquip(2) == PWR_GROOVE) {
            entryDLSetLight(mpPringModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        if (checkMasterSwordEquip() && !checkCaughtShapeHide() && !checkDemoShieldNoDraw()) {
            updateDLSetLight(mpPodmsModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
    }
    if (checkEquipHeavyBoots()) {
        entryDLSetLight(mpHbootsModels[0], mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        entryDLSetLight(mpHbootsModels[1], mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
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
            if (checkSwordEquip() && !checkDemoSwordNoDraw(1)) {
                entryDLSetLight(mpEquippedSwordModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
            }
        }
        if (dComIfGs_getSelectEquip(1) != dItem_NONE_e && !checkCaughtShapeHide() && !checkDemoShieldNoDraw()) {
            entryDLSetLight(mpEquippedShieldModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        dComIfGd_setList();
        drawMirrorLightModel();
        dComIfGd_setListP1();
        
        if (mpBottleContentsModel != NULL) {
            updateDLSetLight(mpBottleContentsModel, 0);
        }
        if (mpHeldItemModel && !checkCaughtShapeHide() && !checkDemoSwordNoDraw(0)) {
            if (!checkBowItem(mHeldItemType) || !checkPlayerGuard()) {
                if (mHeldItemType == dItem_HOOKSHOT_e) {
                    if (mActorKeepEquip.getActor()) {
                        daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
                        mpHeldItemModel->setAnmMtx(4, hookshot->getMtxTop());
                    }
                }
                entryDLSetLight(mpHeldItemModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
                if (mpSwordModel1 != NULL) {
                    if (checkChanceMode() || checkNoResetFlg1(daPyFlg1_UNK8000) || dComIfGs_getSelectEquip(0) == MASTER_SWORD_EX) {
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
    
    if (mHeldItemType == 0x101) {
        fopAc_ac_c* actor = mActorKeepEquip.getActor();
        if (actor == NULL || !fopAcM_checkCarryNow(actor)) {
            mActorKeepEquip.clearData();
            mHeldItemType = 0x100;
        }
    }
    
    if (m3630 != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* sp8;
        if (!fopAcM_SearchByID(m3630, &sp8)) {
            m3630 = -1;
        }
    }
}

/* 80108564-80108634       .text setTalkStatus__9daPy_lk_cFv */
void daPy_lk_c::setTalkStatus() {
    /* Nonmatching */
}

/* 80108634-801086C8       .text setHintActor__9daPy_lk_cFv */
void daPy_lk_c::setHintActor() {
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
        return 1;
    } else if (angle >= 0x2000) {
        return 2;
    } else if (angle <= -0x2000) {
        return 3;
    } else {
        return 0;
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
void daPy_lk_c::cancelItemUpperReadyAnime() {
    /* Nonmatching */
}

/* 80109F4C-8010A204       .text checkBodyAngleX__9daPy_lk_cFs */
BOOL daPy_lk_c::checkBodyAngleX(s16) {
    /* Nonmatching */
    static Vec top_vec = {0.0f, 70.0f, 0.0f};
}

/* 8010A204-8010A2F4       .text setBodyAngleToCamera__9daPy_lk_cFv */
void daPy_lk_c::setBodyAngleToCamera() {
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
    if (m35B0 > 0.05f) {
        if (getDirectionFromCurrentAngle() == 1) {
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
        f1 = (daPy_HIO_atnMoveB_c0::m.field_0x8 * m35B0) * cM_scos(current.angle.y - origAngleY);
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
void daPy_lk_c::setAnimeEquipSword(int) {
    /* Nonmatching */
}

/* 8010C100-8010C158       .text setAnimeEquipSingleItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeEquipSingleItem(u16) {
    /* Nonmatching */
}

/* 8010C158-8010C1D4       .text setAnimeEquipItem__9daPy_lk_cFv */
void daPy_lk_c::setAnimeEquipItem() {
    /* Nonmatching */
}

/* 8010C1D4-8010C284       .text setAnimeUnequipSword__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequipSword() {
    /* Nonmatching */
}

/* 8010C284-8010C3C0       .text setAnimeUnequipItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeUnequipItem(u16) {
    /* Nonmatching */
}

/* 8010C3C0-8010C430       .text setAnimeUnequip__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequip() {
    /* Nonmatching */
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
    return m_anm_heap_upper[UPPER_MOVE2_e].mIdx == LKANM_BCK_TAKEL ||
        m_anm_heap_upper[UPPER_MOVE2_e].mIdx == LKANM_BCK_TAKER;
}

/* 8010C4C8-8010C528       .text checkItemEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkItemEquipAnime() const {
    return m_anm_heap_upper[UPPER_MOVE2_e].mIdx == LKANM_BCK_TAKE ||
        checkSingleItemEquipAnime() ||
        m_anm_heap_upper[UPPER_MOVE2_e].mIdx == LKANM_BCK_TAKEBOTH;
}

/* 8010C528-8010C570       .text checkEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkEquipAnime() const {
    return m_anm_heap_upper[UPPER_MOVE2_e].mIdx == LKANM_BCK_REST ||
        checkItemEquipAnime();
}

/* 8010C570-8010C71C       .text deleteEquipItem__9daPy_lk_cFi */
void daPy_lk_c::deleteEquipItem(BOOL param_1) {
    fopAc_ac_c* equipActor = mActorKeepEquip.getActor();
    
    if (param_1 && (mHeldItemType != 0x100 && mHeldItemType != 0x101)) {
        if (mHeldItemType == 0x103) {
            seStartOnlyReverb(JA_SE_LK_SW_PUTIN_S);
        } else {
            seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        }
    }
    
    if (mHeldItemType == 0x103) {
        mDoAud_bgmSetSwordUsing(0);
    } else if (mHeldItemType == 0x101) {
        if (equipActor != NULL) {
            fopAcM_cancelCarryNow(equipActor);
        }
    } else if (equipActor != NULL) {
        fopAcM_delete(equipActor);
    }
    
    if ((mHeldItemType == dItem_GRAPPLING_HOOK_e && checkRopeAnime()) ||
        (mHeldItemType == dItem_BOOMERANG_e && checkBoomerangAnime()) ||
        (mHeldItemType == dItem_HOOKSHOT_e && checkHookshotReadyAnime()) ||
        (checkBowItem(mHeldItemType) && checkBowAnime())
    ) {
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
    }
    
    mActorKeepEquip.clearData();
    mHeldItemType = 0x100;
    mpHeldItemModel = NULL;
    if (mSwordAnim.getBckAnm() != NULL) {
        mSwordAnim.changeBckOnly(NULL);
    }
    mpParachuteFanMorf = NULL;
    mpHeldItemBtk = NULL;
    mpBottleContentsModel = NULL;
    mpBottleCapModel = NULL;
    mpHeldItemBrk = NULL;
    mpSwordBtk = NULL;
    mpSwordModel1 = NULL;
    m3454.end();
    mpSwordTipStabModel = NULL;
    mpCutfBrk = 0;
    mpCutfBtk = 0;
    mpCutfBpk = 0;
    offNoResetFlg1(daPyFlg1_UNK200000);
}

/* 8010C71C-8010C7F4       .text setFallVoice__9daPy_lk_cFv */
void daPy_lk_c::setFallVoice() {
    /* Nonmatching */
}

/* 8010C7F4-8010C854       .text keepItemData__9daPy_lk_cFv */
/* Saves which item the player was holding in their hand so it can be restored later. */
void daPy_lk_c::keepItemData() {
    mKeepItemType = mHeldItemType;
    
    deleteEquipItem(FALSE);
    
    if (mKeepItemType == 0x101) {
        mKeepItemType = 0x100;
    } else if (mKeepItemType == 0x100) {
        mKeepItemType = 0x10B;
    }
}

/* 8010C854-8010C8D4       .text returnKeepItemData__9daPy_lk_cFv */
/* Restores which item the player was holding in their hand. */
void daPy_lk_c::returnKeepItemData() {
    if (mKeepItemType == 0x100) {
        return;
    }
    
    deleteEquipItem(FALSE);
    mHeldItemType = mKeepItemType;
    mKeepItemType = 0x100;
    
    if (mHeldItemType == 0x10B) {
        mHeldItemType = 0x100;
    } else if (mHeldItemType == 0x103) {
        setSwordModel(TRUE);
    } else {
        makeItemType();
    }
}

/* 8010C8D4-8010CB70       .text makeItemType__9daPy_lk_cFv */
void daPy_lk_c::makeItemType() {
    if (mHeldItemType == dItem_GRAPPLING_HOOK_e) {
        fopAc_ac_c* rope = (fopAc_ac_c*)fopAcM_fastCreate(PROC_HIMO2, 0, &current.pos);
        mActorKeepEquip.setData(rope);
    } else if (mHeldItemType == dItem_HOOKSHOT_e) {
        fopAc_ac_c* hookshot = (fopAc_ac_c*)fopAcM_fastCreate(PROC_HOOKSHOT, 0, &current.pos);
        mActorKeepEquip.setData(hookshot);
        setHookshotModel();
    } else if (mHeldItemType == dItem_BOOMERANG_e) {
        fopAc_ac_c* boomerang = (fopAc_ac_c*)fopAcM_fastCreate(PROC_BOOMERANG, 0, &current.pos);
        mActorKeepEquip.setData(boomerang);
        return;
    } else if (mHeldItemType == BOMB_BAG) {
        fopAc_ac_c* bomb = (fopAc_ac_c*)fopAcM_fastCreate(PROC_BOMB, daBomb_c::prm_make(daBomb_c::STATE_3, false, false), &current.pos);
        mActorKeepGrab.setData(bomb);
        mHeldItemType = 0x100;
        if (mActorKeepGrab.getActor() != NULL) {
            setActAnimeUpper(LKANM_BCK_GRABWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, 5.0f);
            mActivePlayerBombs++;
            fopAcM_setCarryNow(mActorKeepGrab.getActor(), FALSE);
            dComIfGp_setItemBombNumCount(-1);
            m35C8 = 17.0f;
        }
        return;
    } else if (checkBowItem(mHeldItemType)) {
        setBowModel();
        return;
    } else if (mHeldItemType == dItem_TELESCOPE_e) {
        setScopeModel();
        return;
    } else if (checkPhotoBoxItem(mHeldItemType)) {
        setPhotoBoxModel();
        return;
    } else if (mHeldItemType == dItem_TINGLE_TUNER_e) {
        setTinkleCeiverModel();
        return;
    } else if (mHeldItemType == dItem_DEKU_LEAF_e) {
        setSmallFanModel();
        return;
    } else if (mHeldItemType == dItem_WIND_WAKER_e) {
        mHeldItemType = dItem_NONE_e;
        setTactModel();
        return;
    } else if (mHeldItemType == dItem_SKULL_HAMMER_e) {
        setHammerModel();
        return;
    } else if (mHeldItemType == EMPTY_BOTTLE) {
        setBottleModel(mHeldItemType);
        return;
    } else {
        return;
    }
    
    if (mActorKeepEquip.getActor() == NULL) {
        mHeldItemType = 0x100;
        offResetFlg0(daPyRFlg0_UNK80);
    }
}

/* 8010CB70-8010CBC8       .text setScopeModel__9daPy_lk_cFv */
void daPy_lk_c::setScopeModel() {
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpHeldItemModel, LINK_BDL_TELESCOPE, 0x37221222);
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8010CBC8-8010CC78       .text setPhotoBoxModel__9daPy_lk_cFv */
void daPy_lk_c::setPhotoBoxModel() {
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpHeldItemModel, LINK_BDL_CAMERA, 0x37221222);
    mDoExt_setCurrentHeap(oldHeap);
    if (mHeldItemType == CAMERA) {
        mpHeldItemModel->getModelData()->getJointNodePointer(0x02)->getMesh()->getShape()->hide();
    } else {
        mpHeldItemModel->getModelData()->getJointNodePointer(0x02)->getMesh()->getShape()->show();
    }
}

/* 8010CC78-8010CD34       .text changeDragonShield__9daPy_lk_cFi */
void daPy_lk_c::changeDragonShield(int) {
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
            if (mPressedButtons & 0x02 && checkSwordEquip() && mHeldItemType != 0x103) {
                setAnimeEquipSword(1);
            } else if (mPressedButtons & 0x04) {
                if (checkNewItemChange(0)) {
                    mLastUsedItemButtonIdx = 0;
                    return TRUE;
                }
            } else if (mPressedButtons & 0x08) {
                if (checkNewItemChange(1)) {
                    mLastUsedItemButtonIdx = 1;
                    return TRUE;
                }
            } else if (mPressedButtons & 0x10) {
                if (checkNewItemChange(2)) {
                    mLastUsedItemButtonIdx = 2;
                    return TRUE;
                }
            } else if (mPressedButtons & 0x01) {
                if (dComIfGp_getDoStatus() == 0x08) { // A button shows "Put Away"
                    setAnimeUnequip();
                }
            }
        } else {
            if (checkEquipDragonShield() && checkSetItemTrigger(dItem_MAGIC_ARMOR_e, 0)) {
                offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
            } else if (mAcch.ChkGroundHit() && !daPy_lk_c::checkPlayerFly()) {
                if (checkEquipHeavyBoots() && checkSetItemTrigger(dItem_IRON_BOOTS_e, 0)) {
                    return procBootsEquip_init(dItem_IRON_BOOTS_e);
                } else if (checkSetItemTrigger(0x105, 0)) {
                    return procBottleDrink_init(dComIfGp_getSelectItem(mLastUsedItemButtonIdx));
                } else if (checkSetItemTrigger(FAIRY_BOTTLE, 0)) {
                    return procBottleOpen_init(FAIRY_BOTTLE);
                } else if (mPressedButtons & 0x01) {
                    if (dComIfGp_getDoStatus() == 0x08) { // A button shows "Put Away"
                        setAnimeUnequip();
                    }
                }
            } else if (mPressedButtons & 0x01) {
                if (dComIfGp_getDoStatus() == 0x08) { // A button shows "Put Away"
                    setAnimeUnequip();
                }
            }
        }
    }
    return FALSE;
}

/* 8010D26C-8010D754       .text checkItemAction__9daPy_lk_cFv */
void daPy_lk_c::checkItemAction() {
    /* Nonmatching */
}

/* 8010D754-8010D810       .text getSlidePolygon__9daPy_lk_cFv */
void daPy_lk_c::getSlidePolygon() {
    /* Nonmatching */
}

/* 8010D810-8010D8B0       .text checkJumpCutFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkJumpCutFromButton() {
    /* Nonmatching */
}

/* 8010D8B0-8010DB58       .text orderTalk__9daPy_lk_cFv */
void daPy_lk_c::orderTalk() {
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
void daPy_lk_c::changeFrontWallTypeProc() {
    /* Nonmatching */
}

/* 8010FEC4-8010FFB0       .text changeSlideProc__9daPy_lk_cFv */
void daPy_lk_c::changeSlideProc() {
    /* Nonmatching */
}

/* 8010FFB0-80110028       .text changeWaitProc__9daPy_lk_cFv */
void daPy_lk_c::changeWaitProc() {
    /* Nonmatching */
}

/* 80110028-8011029C       .text changeLandProc__9daPy_lk_cFf */
void daPy_lk_c::changeLandProc(f32) {
    /* Nonmatching */
}

/* 8011029C-80110338       .text setDamagePoint__9daPy_lk_cFf */
BOOL daPy_lk_c::setDamagePoint(f32 amount) {
    if (!checkNoDamageMode()) {
        dComIfGp_setItemLifeCount(amount);
        if (amount < 0.0f) {
            offNoResetFlg1(daPyFlg1_UNK8000);
            if (dComIfGs_getSelectEquip(0) != MASTER_SWORD_EX) {
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
BOOL daPy_lk_c::checkElecReturnDamage(dCcD_GObjInf*, cXyz*) {
    /* Nonmatching */
}

/* 801105D8-80110654       .text checkWallAtributeDamage__9daPy_lk_cFP12dBgS_AcchCir */
s32 daPy_lk_c::checkWallAtributeDamage(dBgS_AcchCir*) {
    /* Nonmatching */
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
            ship && ship->unknown_inline_TODO()
        )
    ) {
        offNoResetFlg0(daPyFlg0_SHIP_DROP);
        return FALSE;
    }
    
    BOOL r30;
    int damage;
    s32 r28 = dBgS_Attr_NORMAL_e;
    
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
            r28 = mCurrAttributeCode;
        } else {
            for (int i = 0; r28 == dBgS_Attr_NORMAL_e && i < (s32)ARRAY_SIZE(mAcchCir); i++) {
                r28 = checkWallAtributeDamage(&mAcchCir[i]);
            }
        }
    }
    
    if (r28 != dBgS_Attr_NORMAL_e) {
        r30 = TRUE;
        damage = 1;
    } else {
        r30 = FALSE;
        damage = mStts.GetDmg();
        if (mCyl.ChkTgHit() && mCyl.GetTgHitGObj() && mCyl.GetTgHitGObj()->GetAtType() == AT_TYPE_BOMB) {
            damage = 1;
        }
    }
    
    dCcG_At_Spl r27;
    if (mCyl.ChkTgHit()) {
        dCcD_GObjInf* gobj = mCyl.GetTgHitGObj();
        if (gobj) {
            r27 = gobj->GetAtSpl();
        } else {
            r27 = mStts.GetAtSpl();
        }
    } else {
        r27 = dCcG_At_Spl_UNK0;
    }
    
    if (checkModeFlg(ModeFlg_04000000)) {
        if (r30 || mCyl.ChkTgHit() && !checkSuccessGuard(r27)) {
            setDamagePoint(-damage);
            mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x2;
            
            voiceStart(2);
            
            seStartOnlyReverb(JA_SE_LK_DAMAGE_NORMAL);
            changePlayer(this);
            if (mCyl.ChkTgHit() && !checkSuccessGuard(r27)) {
                setDamageEmitter();
            } else if (r28 == dBgS_Attr_ELECTRICITY_e) {
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
            
            if (!checkSuccessGuard(r27)) {
                if (mHeldItemType == 0x101) {
                    deleteEquipItem(FALSE);
                }
                
                setDamageEmitter();
                changePlayer(this);
                setDamagePoint(-damage);
                fopAc_ac_c* grabActor = mActorKeepGrab.getActor();
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
                    grabActor)
                {
                    cXyz* r3 = getDamageVec(&mCyl);
                    grabActor->shape_angle.y = cM_atan2s(r3->x, r3->z);
                    grabActor->shape_angle.x = 0x2000;
                    return procLargeDamage_init(-4, 1, 0, 0);
                }
                if (r27 == 7 || r27 == 2 || r27 == 10) {
                    return procLargeDamage_init(-6, 0, 0, 0);
                }
                if (daPy_lk_c::checkPlayerFly() || r27 == 6 || r27 == 1 || r27 == 9) {
                    return procLargeDamage_init(-1, 1, 0, 0);
                }
                if (checkNormalDamage(damage)) {
                    return procDamage_init();
                }
                setDashDamage();
            } else {
                u8 hitSe = mCyl.GetTgHitObjSe();
                if (hitSe == dCcD_SE_UNK6) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_N_BDY_MPLT);
                } else if (hitSe == dCcD_SE_UNK2 || hitSe == dCcD_SE_UNK5) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_SWS_NMTLP);
                } else if (hitSe == dCcD_SE_UNK4) {
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
            if (mHeldItemType == 0x101) {
                deleteEquipItem(FALSE);
            }
            setDamagePoint(-damage);
            
            if (r28 == dBgS_Attr_ELECTRICITY_e) {
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
    /* Nonmatching */
    static const Vec tact_scale = {2.5f, 2.5f, 2.5f};
}

/* 80111A80-80111B80       .text changeDeadProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeDeadProc() {
    /* Nonmatching */
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
    /* Nonmatching */
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
    return itemNo >= EMPTY_BOTTLE && itemNo <= UNK_BOTTLE_60;
}

/* 80111F7C-80111FEC       .text checkDrinkBottleItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkDrinkBottleItem(int itemNo) const {
    return itemNo == RED_BOTTLE || itemNo == GREEN_BOTTLE || itemNo == BLUE_BOTTLE || itemNo == dItem_SOUP_BOTTLE_e || itemNo == dItem_HALF_SOUP_BOTTLE_e;
}

/* 80111FEC-8011201C       .text checkOpenBottleItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkOpenBottleItem(int itemNo) const {
    return itemNo == FIREFLY_BOTTLE || itemNo == BIN_IN_WATER || itemNo == FWATER_BOTTLE || itemNo == FAIRY_BOTTLE;
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
    /* Nonmatching */
}

/* 80112100-8011215C       .text setSubjectMode__9daPy_lk_cFv */
void daPy_lk_c::setSubjectMode() {
    /* Nonmatching */
}

/* 8011215C-801121C8       .text checkMaskDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::checkMaskDraw() {
    /* Nonmatching */
}

/* 801121C8-80112280       .text checkSubjectEnd__9daPy_lk_cFi */
BOOL daPy_lk_c::checkSubjectEnd(int) {
    /* Nonmatching */
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
    
    s32 temp_r29;
    BOOL resetDemoAnime = FALSE;
    s32 temp_r28;
    
    if (mCurProc == daPyProc_SLIP_e) {
        mDoAud_seStop(JA_SE_LK_RUN_SLIP, 0);
    } else if (mCurProc == daPyProc_GRAB_MISS_e || (mCurProc == daPyProc_GRAB_READY_e && proc != daPyProc_GRAB_MISS_e)) {
        mActorKeepRope.clearData();
    } else if (mCurProc == daPyProc_DEMO_TALISMAN_WAIT_e) {
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        mpHeldItemModel = NULL;
    } else if (mCurProc == daPyProc_FAN_SWING_e) {
        setSmallFanModel();
    } else if (mCurProc == daPyProc_FAN_GLIDE_e) {
        deleteEquipItem(FALSE);
        maxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
        setSmallFanModel();
        mHeldItemType = dItem_DEKU_LEAF_e;
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
    
    temp_r28 = checkModeFlg(ModeFlg_SWIM) >> 0x12; // TODO fakematch? fixes regalloc
    
    // TODO: is this an inline?
    if (checkModeFlg(ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_SWIM | ModeFlg_CAUGHT)) {
        m34C2 = 0xA;
    }
    
    temp_r29 = (checkModeFlg(ModeFlg_MIDAIR) >> 1) ^ 1; // TODO fakematch? fixes regalloc
    
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
    
    if (mHeldItemType == dItem_SKULL_HAMMER_e) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(0x97));
    } else if (checkBowItem(mHeldItemType) && !checkBowAnime()) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(0xD));
    }
    
    m35E8 = 0.0f;
    
    if (!checkModeFlg(ModeFlg_ROPE) && mCurProc != daPyProc_ROPE_SUBJECT_e && mCurProc != daPyProc_ROPE_MOVE_e) {
        freeRopeItem();
    }
    if (!checkModeFlg(ModeFlg_HOOKSHOT)) {
        freeHookshotItem();
    }
    if (temp_r28 && !checkModeFlg(ModeFlg_SWIM)) {
        swimOutAfter(0);
    }
    
    g_dComIfG_gameInfo.play.field_0x4941 = 0; // is this dComIfGp_setAdvanceDirection__FUc?
    
    setBgCheckParam();
    
    return TRUE;
}

/* 80112954-80112A24       .text procScope_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procScope_init(int) {
    /* Nonmatching */
}

/* 80112A24-80112AA8       .text procScope__9daPy_lk_cFv */
BOOL daPy_lk_c::procScope() {
    /* Nonmatching */
}

/* 80112AA8-80112B18       .text procSubjectivity_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSubjectivity_init(int) {
    /* Nonmatching */
}

/* 80112B18-80112BEC       .text procSubjectivity__9daPy_lk_cFv */
BOOL daPy_lk_c::procSubjectivity() {
    /* Nonmatching */
}

/* 80112BEC-80112C90       .text procCall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCall_init() {
    commonProcInit(daPyProc_CALL_e);
    mVelocity = 0.0f;
    daPy_matAnm_c::offMabaFlg();
    daPy_matAnm_c::setMabaTimer(1);
    setSingleMoveAnime(ANM_YOBU, 1.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);
    current.angle.y = shape_angle.y;
    if (mHeldItemType == 0x101) {
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
    
    if (mFrameCtrlUnder[0].getRate() < 0.01f) {
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
    /* Nonmatching */
}

/* 80112DF4-80112E60       .text procControllWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procControllWait() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 801134A0-801135C4       .text procFreeWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procFreeWait() {
    /* Nonmatching */
}

/* 801135C4-80113628       .text procMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procMove_init() {
    /* Nonmatching */
}

/* 80113628-801136D4       .text procMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procMove() {
    /* Nonmatching */
}

/* 801136D4-80113738       .text procAtnMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnMove_init() {
    /* Nonmatching */
}

/* 80113738-801137B4       .text procAtnMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnMove() {
    /* Nonmatching */
}

/* 801137B4-8011388C       .text procAtnActorWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorWait_init() {
    /* Nonmatching */
}

/* 8011388C-801138FC       .text procAtnActorWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorWait() {
    /* Nonmatching */
}

/* 801138FC-80113960       .text procAtnActorMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorMove_init() {
    /* Nonmatching */
}

/* 80113960-801139C0       .text procAtnActorMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorMove() {
    /* Nonmatching */
}

/* 801139C0-80113AC4       .text procSideStep_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSideStep_init(int) {
    /* Nonmatching */
}

/* 80113AC4-80113BDC       .text procSideStep__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStep() {
    /* Nonmatching */
}

/* 80113BDC-80113CBC       .text procSideStepLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStepLand_init() {
    /* Nonmatching */
}

/* 80113CBC-80113D30       .text procSideStepLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStepLand() {
    /* Nonmatching */
}

/* 80113D30-80113DBC       .text procCrouchDefense_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefense_init() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 801143D4-80114440       .text procCrouch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouch_init() {
    /* Nonmatching */
}

/* 80114440-8011476C       .text procCrouch__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouch() {
    /* Nonmatching */
}

/* 8011476C-80114804       .text procWaitTurn_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn_init() {
    /* Nonmatching */
}

/* 80114804-80114908       .text procWaitTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn() {
    /* Nonmatching */
}

/* 80114908-801149EC       .text procMoveTurn_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procMoveTurn_init(int) {
    /* Nonmatching */
}

/* 801149EC-80114A60       .text procMoveTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procMoveTurn() {
    /* Nonmatching */
}

/* 80114A60-80114B28       .text procSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlip_init() {
    /* Nonmatching */
}

/* 80114B28-80114D2C       .text procSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlip() {
    /* Nonmatching */
}

/* 80114D2C-80114DE4       .text procSlideFront_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procSlideFront_init(s16) {
    /* Nonmatching */
}

/* 80114DE4-80114EE8       .text procSlideFront__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFront() {
    /* Nonmatching */
}

/* 80114EE8-80114FA0       .text procSlideBack_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procSlideBack_init(s16) {
    /* Nonmatching */
}

/* 80114FA0-801150B0       .text procSlideBack__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBack() {
    /* Nonmatching */
}

/* 801150B0-80115118       .text procSlideFrontLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFrontLand_init() {
    /* Nonmatching */
}

/* 80115118-801151C8       .text procSlideFrontLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFrontLand() {
    /* Nonmatching */
}

/* 801151C8-80115220       .text procSlideBackLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBackLand_init() {
    /* Nonmatching */
}

/* 80115220-801152D0       .text procSlideBackLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBackLand() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 801157D8-801158AC       .text procFrontRollCrash__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRollCrash() {
    /* Nonmatching */
}

/* 801158AC-8011590C       .text procNockBackEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd_init() {
    /* Nonmatching */
}

/* 8011590C-80115968       .text procNockBackEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd() {
    /* Nonmatching */
}

/* 80115968-80115A18       .text procSideRoll_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideRoll_init() {
    /* Nonmatching */
}

/* 80115A18-80115B08       .text procSideRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideRoll() {
    /* Nonmatching */
}

/* 80115B08-80115BFC       .text procBackJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJump_init() {
    /* Nonmatching */
}

/* 80115BFC-80115CA0       .text procBackJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJump() {
    /* Nonmatching */
}

/* 80115CA0-80115DA8       .text procBackJumpLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJumpLand_init() {
    /* Nonmatching */
}

/* 80115DA8-80115E88       .text procBackJumpLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJumpLand() {
    /* Nonmatching */
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
BOOL daPy_lk_c::procLand_init(f32, int) {
    /* Nonmatching */
}

/* 8011651C-801165B4       .text procLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procLand() {
    /* Nonmatching */
}

/* 801165B4-80116768       .text procLandDamage_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procLandDamage_init(int) {
    /* Nonmatching */
}

/* 80116768-80116864       .text procLandDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLandDamage() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 80116CC4-80116D3C       .text procSlowFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlowFall() {
    /* Nonmatching */
}

/* 80116D3C-80116EB4       .text procSmallJump_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSmallJump_init(int) {
    /* Nonmatching */
}

/* 80116EB4-80116F54       .text procSmallJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procSmallJump() {
    /* Nonmatching */
}

/* 80116F54-80116FEC       .text procVerticalJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procVerticalJump_init() {
    /* Nonmatching */
}

/* 80116FEC-80117088       .text procVerticalJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procVerticalJump() {
    /* Nonmatching */
}

/* 80117088-801170F0       .text procGuardCrash__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardCrash() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 80117794-801177CC       .text procPolyDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procPolyDamage() {
    /* Nonmatching */
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
BOOL daPy_lk_c::procLargeDamageUp_init(int, int, s16, s16) {
    /* Nonmatching */
}

/* 80118504-80118640       .text procLargeDamageUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamageUp() {
    /* Nonmatching */
}

/* 80118640-801189AC       .text procLargeDamageWall_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamageWall_init(int, int, s16, s16) {
    /* Nonmatching */
}

/* 801189AC-801189F0       .text procLargeDamageWall__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamageWall() {
    /* Nonmatching */
}

/* 801189F0-80118BC4       .text procLavaDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procLavaDamage_init() {
    /* Nonmatching */
}

/* 80118BC4-80118C58       .text procLavaDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLavaDamage() {
    /* Nonmatching */
}

/* 80118C58-80118E6C       .text procElecDamage_init__9daPy_lk_cFPC4cXyz */
BOOL daPy_lk_c::procElecDamage_init(const cXyz*) {
    /* Nonmatching */
}

/* 80118E6C-80118F40       .text procElecDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procElecDamage() {
    /* Nonmatching */
}

/* 80118F40-80119248       .text procGuardSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardSlip_init() {
    /* Nonmatching */
}

/* 80119248-80119334       .text procGuardSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardSlip() {
    /* Nonmatching */
}

/* 80119334-80119478       .text procIceSlipFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFall_init() {
    /* Nonmatching */
}

/* 80119478-80119500       .text procIceSlipFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFall() {
    /* Nonmatching */
}

/* 80119500-80119688       .text procIceSlipFallUp_init__9daPy_lk_cFiss */
BOOL daPy_lk_c::procIceSlipFallUp_init(int, s16, s16) {
    /* Nonmatching */
}

/* 80119688-8011970C       .text procIceSlipFallUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFallUp() {
    /* Nonmatching */
}

/* 8011970C-801197D4       .text procIceSlipAlmostFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipAlmostFall_init() {
    /* Nonmatching */
}

/* 801197D4-80119864       .text procIceSlipAlmostFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipAlmostFall() {
    /* Nonmatching */
}

/* 80119864-801198E0       .text procBootsEquip_init__9daPy_lk_cFUs */
BOOL daPy_lk_c::procBootsEquip_init(u16) {
    /* Nonmatching */
}

/* 801198E0-80119A5C       .text procBootsEquip__9daPy_lk_cFv */
BOOL daPy_lk_c::procBootsEquip() {
    /* Nonmatching */
}

/* 80119A5C-80119BA0       .text procNotUse_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procNotUse_init(int) {
    /* Nonmatching */
}

/* 80119BA0-80119DA0       .text procNotUse__9daPy_lk_cFv */
BOOL daPy_lk_c::procNotUse() {
    /* Nonmatching */
}

/* 80119DA0-80119EBC       .text getGroundAngle__9daPy_lk_cFP13cBgS_PolyInfos */
s16 daPy_lk_c::getGroundAngle(cBgS_PolyInfo*, s16) {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 8011AC78-8011AD9C       .text autoGroundHit__9daPy_lk_cFv */
void daPy_lk_c::autoGroundHit() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 8011BEA4-8011CBA4       .text setHatAngle__9daPy_lk_cFv */
void daPy_lk_c::setHatAngle() {
    /* Nonmatching */
}

/* 8011CBA4-8011CCF4       .text setMoveSlantAngle__9daPy_lk_cFv */
void daPy_lk_c::setMoveSlantAngle() {
    /* Nonmatching */
}

/* 8011CCF4-8011CDB4       .text setWaistAngle__9daPy_lk_cFv */
void daPy_lk_c::setWaistAngle() {
    /* Nonmatching */
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
void daPy_lk_c::getBlurTopRate() {
    /* Nonmatching */
}

/* 8011D788-8011EC0C       .text setCollision__9daPy_lk_cFv */
void daPy_lk_c::setCollision() {
    /* Nonmatching */
}

/* 8011EC0C-8011EEBC       .text setAttentionPos__9daPy_lk_cFv */
void daPy_lk_c::setAttentionPos() {
    /* Nonmatching */
    static const Vec offset_39104 = {0.0f, 30.0f, 20.0f};
    static const Vec offset_39108 = {0.0f, 70.0f, 0.0f};
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
    return roomNo & 0x3F | (spawnType & 0xF) << 0xC | eventInfoIdx << 0x18 | extraParams;
}

/* 8012010C-8012024C       .text checkLavaFace__9daPy_lk_cFP4cXyzi */
BOOL daPy_lk_c::checkLavaFace(cXyz* param_1, int attributeCode) {
    if (mDemo.getDemoType() == 5) {
        return FALSE;
    }
    
    if (param_1) {
        cXyz pos(current.pos.x, param_1->y + 20.0f, current.pos.z);
        mLavaGndChk.SetPos(&pos);
        m35D4 = dComIfG_Bgsp()->GroundCross(&mLavaGndChk);
        if (mAcch.GetGroundH() > m35D4) {
            m35D4 = -1000000000.0f;
        }
        if (m35D4 > current.pos.y) {
            attributeCode = dComIfG_Bgsp()->GetAttributeCode(mLavaGndChk);
        } else {
            return FALSE;
        }
    }
    
    if (attributeCode == dBgS_Attr_LAVA_e) {
        if (param_1) {
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
BOOL daPy_lk_c::startRestartRoom(u32 param_1, int eventInfoIdx, f32 param_3, int i_point) {
    /* Nonmatching - npc_sarace */
    if (!checkNoResetFlg0(daPyFlg0_UNK4000) && (i_point != 0 || dComIfGp_event_compulsory(this))) {
        mDemo.setOriginalDemoType();
        if (i_point == 0) {
            mDemo.setDemoMode(1);
        }
        onNoResetFlg0(daPyFlg0_UNK4000);
        changePlayer(this);
        
        if (dComIfGp_getMiniGameType() == 1) {
            dComIfGp_setNextStage("sea", 1, 48);
            mDoAud_seStart(JA_SE_FORCE_BACK);
            // daNpc_Sarace_c::ship_race_result = 3;
            mTinkleShieldTimer = 0;
            return TRUE;
        } else {
            u32 stageType = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo());
            setDamagePoint(param_3);
            mTinkleShieldTimer = 0;
            
            if (stageType == dStageType_SEA_e && !dComIfGs_isEventBit(dSv_evtBit_c::RODE_KORL) &&
                (current.roomNo == 11 || current.roomNo == 44) && dStage_chkPlayerId(0x80, current.roomNo))
            {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0x80, current.roomNo, -1, 0.0f, param_1);
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
                    
                    dStage_changeScene(scls_idx, 0.0f, param_1, -1);
                } else {
                    if (mCurProc == daPyProc_DEMO_DEAD_e) {
                        dStage_changeScene(0, 0.0f, param_1, -1);
                    } else {
                        int roomNo = dComIfGs_getRestartRoomNo();
                        u32 roomParam = setParamData(roomNo, 0, eventInfoIdx, 0);
                        dStage_restartRoom(roomParam, param_1);
                        mDoAud_seStart(JA_SE_FORCE_BACK);
                    }
                    return TRUE;
                }
            } else if (checkNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG)) {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, 41, -1, 0.0f, param_1);
            } else {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, current.roomNo, -1, 0.0f, param_1);
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
    if (!mCyl.ChkTgShieldHit() || atSpl >= 8) {
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
    /* Nonmatching */
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
    
    if (dComIfGs_checkBottle(FWATER_BOTTLE)) {
        if (dComIfGs_getFwaterTimer() == 0) {
            if (dComIfGp_event_compulsory(this)) {
                onNoResetFlg1(daPyFlg1_UNK200);
                dComIfGs_setBottleItemIn(FWATER_BOTTLE, BIN_IN_WATER);
                mDemo.setDemoType(5);
                m3628 = -1;
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
        dComIfGp_getSelectItem(0) != dItem_IRON_BOOTS_e &&
        dComIfGp_getSelectItem(1) != dItem_IRON_BOOTS_e &&
        dComIfGp_getSelectItem(2) != dItem_IRON_BOOTS_e
    ) {
        offNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
    } else if (checkEquipDragonShield() &&
        dComIfGp_getSelectItem(0) != dItem_MAGIC_ARMOR_e &&
        dComIfGp_getSelectItem(1) != dItem_MAGIC_ARMOR_e &&
        dComIfGp_getSelectItem(2) != dItem_MAGIC_ARMOR_e
    ) {
        offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
    }
    
    if (dComIfGp_event_runCheck()) {
        mStaffIdx = dComIfGp_evmng_getMyStaffId("Link", this);
        if (eventInfo.checkCommandDoor() && !dComIfGp_event_chkEventFlag(0x4) && mHeldItemType == 0x101) {
            fopAc_ac_c* equipActor = mActorKeepEquip.getActor();
            if (equipActor) {
                s16 angle = shape_angle.y + 0x8000;
                equipActor->speed.y = 0.0f;
                equipActor->speedF = 5.0f;
                equipActor->current.angle.y = angle;
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
        mAcch.GetGroundH() != -1e9f &&
        !checkNoResetFlg0((daPy_FLG0)(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) &&
        dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd) &&
        dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd)
    ) {
        dComIfG_Bgsp()->MoveBgCrrPos(mAcch.m_gnd, mAcch.ChkGroundHit(), &current.pos, &current.angle, &shape_angle);
        dComIfG_Bgsp()->MoveBgCrrPos(mAcch.m_gnd, mAcch.ChkGroundHit(), &old.pos, NULL, NULL);
    }
    
    cXyz sp20 = old.pos;
    m34DE = shape_angle.y;
    m35B4 = m35B0;
    m34EA = m34DC;
    
    dComIfGp_setDoStatus(0);
    dComIfGp_setRStatus(0);
    
    if (mHeldItemType == 0x101) {
        dComIfGp_setAStatus(0x2F);
    } else if (checkSwordEquip()) {
        dComIfGp_setAStatus(0x35);
    } else {
        dComIfGp_setAStatus(0x00);
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
    fopAc_ac_c* zTarget = dComIfGp_getAttention().getZHintTarget();
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
    
    fopAc_ac_c* grabActor = mActorKeepGrab.getActor();
    fopAc_ac_c* equipActor = mActorKeepEquip.getActor();
    
    if (grabActor && !fopAcM_checkCarryNow(grabActor)) {
        freeGrabItem();
    }
    
    if (mHeldItemType == 0x101) {
        if (equipActor == NULL || !fopAcM_checkCarryNow(equipActor)) {
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
    
    if (mHeldItemType == dItem_GRAPPLING_HOOK_e &&
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
    
    if (mHeldItemType == 0x103 && (m34C4 == 2 || m34C4 == 3)) {
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
    checkLavaFace(&sp20, dBgS_Attr_NORMAL_e);
    
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
        if (m3574 != 0 && mAcch.GetGroundH() != -1e9f) {
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
    if (mAcch.GetGroundH() != -1e9f) {
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
    
    equipActor = mActorKeepEquip.getActor();
    if (equipActor) {
        equipActor->tevStr.mRoomNo = tevStr.mRoomNo;
        equipActor->tevStr.mEnvrIdxOverride = tevStr.mEnvrIdxOverride;
        equipActor->current.roomNo = roomNo;
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
    
    mpCLModelData->getJointNodePointer(0x00)->setMtxCalc(m_pbCalc[PART_UNDER_e]);
    mpCLModelData->getJointNodePointer(0x02)->setMtxCalc(m_pbCalc[PART_UPPER_e]);
    mpCLModelData->getJointNodePointer(0x1D)->setMtxCalc(m_pbCalc[PART_UNDER_e]);
    
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
            mpSwordTipStabModel->setBaseTRMtx(mpHeldItemModel->getAnmMtx(0x03));
        } else {
            mpSwordTipStabModel->setBaseTRMtx(mpHeldItemModel->getAnmMtx(0x04));
        }
    }
    
    cMtx_multVec(mpCLModel->getAnmMtx(0x13), &l_eye_offset, &eyePos);
    
    m36D0 = mSwordTopPos;
    m36DC = m36C4;
    
    if (mHeldItemType == 0x101 && mActorKeepEquip.getActor()) {
        daBoko_c* boko = static_cast<daBoko_c*>(mActorKeepEquip.getActor());
        boko->getTopPos(&mSwordTopPos);
        boko->getBlurRootPos(&m36C4);
    } else if (mHeldItemType == dItem_SKULL_HAMMER_e) {
        cMtx_multVec(mpHeldItemModel->getBaseTRMtx(), &hammer_top, &mSwordTopPos);
        cMtx_multVec(mpHeldItemModel->getBaseTRMtx(), &hammer_root, &m36C4);
    } else if (mHeldItemType == 0x103) {
        if (checkNormalSwordEquip()) {
            cMtx_multVec(mpHeldItemModel->getAnmMtx(0x01), &nsword_top, &mSwordTopPos);
            mDoMtx_multVecZero(mpHeldItemModel->getAnmMtx(0x02), &m36C4);
        } else {
            mDoMtx_multVecZero(mpHeldItemModel->getAnmMtx(0x01), &m36C4);
            cMtx_multVec(mpHeldItemModel->getAnmMtx(0x01), &msword_top, &mSwordTopPos);
        }
    } else if (mCurProc == daPyProc_FAN_SWING_e) {
        mDoMtx_multVecZero(mpHeldItemModel->getBaseTRMtx(), &m36C4);
        cMtx_multVec(mpHeldItemModel->getAnmMtx(0x06), &fan_top, &mSwordTopPos);
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
        dComIfGp_setDoStatus(0);
        dComIfGp_setRStatus(0);
    } else {
        if (dComIfGp_getDoStatus() == 0x43) {
            dComIfGp_setDoStatus(0x12);
        }
        if (checkResetFlg0(daPyRFlg0_UNK10000000)) {
            dComIfGp_setAStatus(0);
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
    
    m3634 = -1;
    
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
    for (i = 0; i < (int)ARRAY_SIZE(m31E8); i++) {
        m31E8[i].getSmokeCallBack()->end();
        m31E8[i].getOtherCallBack()->end();
    }
    if (mFanSwingCb.mpEmitter) {
        mFanSwingCb.mpEmitter->clearStatus(0x40);
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
    mDoAud_seDeleteObject(&m338C.field_0x08);
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
    JUT_ASSERT(20869, m_tex_anm_heap.m_buffer != 0);
    
    JKRReadIdxResource(m_tex_anm_heap.m_buffer, 0x1000, LKANM_BTP_TMABAA, dComIfGp_getAnmArchive());
    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(J3DAnmLoaderDataBase::load(m_tex_anm_heap.m_buffer));
    btp->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btp->getUpdateMaterialNum();
    m_texNoAnms = new J3DTexNoAnm[material_num];
    JUT_ASSERT(20885, m_texNoAnms != 0);
    
    for (u16 i = 0; i < material_num; i++) {
        u16 matID = btp->getUpdateMaterialID(i);
        if (matID != 0xFFFF) {
            J3DMaterialAnm* mat_anm = new J3DMaterialAnm();
            JUT_ASSERT(20894, mat_anm != 0);
            
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
    JUT_ASSERT(20944, m_tex_scroll_heap.m_buffer != 0);
    
    JKRReadIdxResource(m_tex_scroll_heap.m_buffer, 0x800, LKANM_BTK_TMABA, dComIfGp_getAnmArchive());
    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(m_tex_scroll_heap.m_buffer));
    btk->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btk->getUpdateMaterialNum();
    JUT_ASSERT(20958, material_num == 2);
    
    m_texMtxAnm = new J3DTexMtxAnm[material_num];
    JUT_ASSERT(20961, m_texMtxAnm != 0);
    
    for (u16 no = 0; no < material_num; no++) {
        u16 matID = btk->getUpdateMaterialID(no);
        if (matID != 0xFFFF) {
            m_tex_eye_scroll[no] = new daPy_matAnm_c();
            JUT_ASSERT(20972, m_tex_eye_scroll[no] != 0);
            
            mpCLModelData->getMaterialNodePointer(matID)->change();
            mpCLModelData->getMaterialNodePointer(matID)->setMaterialAnm(m_tex_eye_scroll[no]);
            
            J3DMaterial* mtl = mpCLModelData->getMaterialNodePointer(matID);
            u8 texMtxID = btk->getUpdateTexMtxID(no);
            if (texMtxID != 0xFF) {
                J3DTexMtx* tmtx;
                if (mtl->getTexMtx(texMtxID) == NULL) {
                    tmtx = new J3DTexMtx();
                    JUT_ASSERT(20984, tmtx != 0);
                    mtl->setTexMtx(no, tmtx);
                }
                if (mtl->getTexCoord(texMtxID) != NULL) {
                    mtl->getTexCoord(texMtxID)->setTexGenMtx(GX_TEXMTX0 + (texMtxID & 0xFF) * 3);
                }
                tmtx = mtl->getTexMtx(no);
                
                m_texMtxAnm[no].setAnmTransform(btk);
                m_texMtxAnm[no].setAnmIndex(no);
                
                tmtx->getTexMtxInfo().mInfo = tmtx->getTexMtxInfo().mInfo & 0x7F | btk->getTexMtxCalcType() << 7;
                // Fakematch? The codegen doesn't match unless a temp variable is used and assigned to multiple times.
                Vec* temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.x = temp->x;
                temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.y = temp->y;
                temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.z = temp->z;
                
                JUT_ASSERT(21001, mtl->getMaterialAnm() != 0);
                
                mtl->getMaterialAnm()->setTexMtxAnm(texMtxID, &m_texMtxAnm[no]);
            }
        }
    }
}

/* 80123834-8012469C       .text createHeap__9daPy_lk_cFv */
BOOL daPy_lk_c::createHeap() {
    /* Nonmatching - daPy_HIO_c constructor */
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
    ret = mSwgripmsabBckAnim.init(mpSwgripmsModel->getModelData(), bck, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21046, 0); }
    mpTswgripmsabBrk = entryBrk(tmp_modelData, LINK_BRK_TSWGRIPMSAB);
    mpTswgripmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSWGRIPMS);
    
    tmp_modelData = initModel(&mpPodmsModel, LINK_BDL_PODMS, 0x37221222);
    
    tmp_modelData = initModel(&mpShaModel, LINK_BDL_SHA, 0x37221222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_ATNGSHA);
    ret = mAtngshaBck.init(mpShaModel->getModelData(), bck, false, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21063, 0); }
    
    tmp_modelData = initModel(&mpShmsModel, LINK_BDL_SHMS, 0x37221222);
    mpTshmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSHMS);
    J3DSkinDeform* shmsSkinDeform = new J3DSkinDeform();
    if (!shmsSkinDeform) { JUT_ASSERT(21077, 0); }
    if (mpShmsModel->setSkinDeform(shmsSkinDeform, 1) != J3DErrType_Success ) { JUT_ASSERT(21080, 0); }
    
    tmp_modelData = initModel(&mpYmsls00Model, LINK_BDL_YMSLS00, 0x13000222);
    mpYmsls00Btk = entryBtk(tmp_modelData, LINK_BTK_YMSLS00);
    
    tmp_modelData = initModel(&mpHbootsModels[0], LINK_BDL_HBOOTS, 0x37221222);
    tmp_modelData = initModel(&mpHbootsModels[1], LINK_BDL_HBOOTS, 0x37221222);
    
    tmp_modelData = initModel(&mpSuimenMunyaModel, LINK_BDL_SUIMEN_MUNYA, 0x11001222);
    mpSuimenMunyaBtk = entryBtk(tmp_modelData, LINK_BTK_SUIMEN_MUNYA);
    
    tmp_modelData = initModel(&mpYuchw00Model, LINK_BDL_YUCHW00, 0x13000222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_YUCHW00);
    ret = mYuchw00Bck.init(tmp_modelData, bck, 1, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21113, 0); }
    mpYuchw00Btk = entryBtk(tmp_modelData, LINK_BTK_YUCHW00);
    mpYuchw00Brk = entryBrk(tmp_modelData, LINK_BRK_YUCHW00);
    mpYuchw00Brk->setFrame(mpYuchw00Brk->getFrameMax()-0.001f);
    
    tmp_modelData = initModel(&mpYbafo00Model, LINK_BDL_YBAFO00, 0x13000222);
    mpYbafo00Btk = entryBtk(tmp_modelData, LINK_BTK_YBAFO00);
    mpYbafo00Btk->setFrame(mpYbafo00Btk->getFrameMax()-0.001f);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_YAURA00));
    JUT_ASSERT(21130, tmp_modelData != 0);
    daPy_aura_c* aura_p = mMagicArmorAuraEntries;
    for (int i = 0; i < 6; i++) {
        aura_p->setModel(mDoExt_J3DModel__create(tmp_modelData, 0x00080000, 0x11001222));
        JUT_ASSERT(21139, aura_p->getModel() != 0);
        aura_p++;
    }
    mpYaura00Btk = entryBtk(tmp_modelData, LINK_BTK_YAURA00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YAURA00_R);
    ret = mYaura00rBrk.init(tmp_modelData, brk, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(21147, 0); }
    mYaura00rBrk.entryFrame(0.0f);
    
    tmp_modelData = initModel(&mpYmgcs00Model, LINK_BDL_YMGCS00, 0x11001222);
    mpYmgcs00Btk = entryBtk(tmp_modelData, LINK_BTK_YMGCS00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YMGCS00_MS);
    ret = mYmgcs00Brk.init(tmp_modelData, brk, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(21161, 0); }
    mYmgcs00Brk.entryFrame(0.0f);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_BOMB));
    JUT_ASSERT(21169, tmp_modelData != 0);
    mpBombBrk = entryBrk(tmp_modelData, LINK_BRK_BOMB);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GWP00));
    JUT_ASSERT(21176, tmp_modelData != 0);
    mpGwp00BrkData = entryBrk(tmp_modelData, LINK_BRK_GWP00);
    mpGwp00BtkData = entryBtk(tmp_modelData, LINK_BTK_GWP00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROW));
    JUT_ASSERT(21184, tmp_modelData != 0);
    mpIceArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TTIPICE);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROWGLITTER));
    JUT_ASSERT(21191, tmp_modelData != 0);
    mpLightArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TARROWGLITTER);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER00));
    JUT_ASSERT(21198, tmp_modelData != 0);
    mpGicer00Btk = entryBtk(tmp_modelData, LINK_BTK_GICER00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER01));
    JUT_ASSERT(21205, tmp_modelData != 0);
    mpGicer01Btk = entryBtk(tmp_modelData, LINK_BTK_GICER01);
    
    const int numCLJoints = 0x2A;
    m_old_fdata = new mDoExt_MtxCalcOldFrame(new J3DTransformInfo[numCLJoints], new Quaternion[numCLJoints]);
    JUT_ASSERT(21233, m_old_fdata != 0);
    
    m_pbCalc[PART_UNDER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUnder), mAnmRatioUnder);
    JUT_ASSERT(21239, m_pbCalc[PART_UNDER_e] != 0);
    
    m_pbCalc[PART_UPPER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUpper), mAnmRatioUpper);
    JUT_ASSERT(21245, m_pbCalc[PART_UPPER_e] != 0);
    
    initTextureScroll();
    initTextureAnime();
    
    m_HIO = new daPy_HIO_c();
    JUT_ASSERT(21254, m_HIO != 0);
    
    m_anm_heap_under[UNDER_MOVE0_e].m_buffer = new(0x20) u8[0xB400];
    JUT_ASSERT(21259, m_anm_heap_under[UNDER_MOVE0_e].m_buffer != 0);
    
    m_sanm_buffer = new(0x20) u8[0x200];
    JUT_ASSERT(21266, m_sanm_buffer != 0);
    
    m_item_bck_buffer = new(0x20) u8[0x1000];
    JUT_ASSERT(21269, m_item_bck_buffer != 0);
    
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
        JUT_ASSERT(21307, tmp_trans_bas != 0);
    } else if (heapType == HEAP_TYPE_UNDER_UPPER_e) {
        J3DAnmTransformKey* tmp_trans = new J3DAnmTransformKey;
        JUT_ASSERT(21310, tmp_trans != 0);
    } else if (heapType == HEAP_TYPE_TEXTURE_ANIME_e) {
        J3DAnmTexPattern* tmp_tp = new J3DAnmTexPattern;
        JUT_ASSERT(21313, tmp_tp != 0);
    } else { // heapType == HEAP_TYPE_TEXTURE_SCROLL_e
        J3DAnmTextureSRTKey* tmp_tk = new J3DAnmTextureSRTKey;
        JUT_ASSERT(21316, tmp_tk != 0);
    }
    
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(*pHeap);
}

/* 80124A40-80124B30       .text initModel__9daPy_lk_cFPP8J3DModeliUl */
J3DModelData* daPy_lk_c::initModel(J3DModel** i_model, int i_fileIndex, u32 i_differedDlistFlag) {
    J3DModelData* tmp_modelData;
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, i_fileIndex));
    JUT_ASSERT(21340, tmp_modelData != 0);
    *i_model = mDoExt_J3DModel__create(tmp_modelData, 0x00080000, i_differedDlistFlag);
    JUT_ASSERT(21344, *i_model != 0);
    return tmp_modelData;
}

/* 80124B30-80124BE4       .text entryBtk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTextureSRTKey* daPy_lk_c::entryBtk(J3DModelData*, int) {
    /* Nonmatching */
}

/* 80124BE4-80124C98       .text entryBrk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTevRegKey* daPy_lk_c::entryBrk(J3DModelData*, int) {
    /* Nonmatching */
}

/* 80124C98-80125CC8       .text playerInit__9daPy_lk_cFv */
void daPy_lk_c::playerInit() {
    if (!fopAcM_entrySolidHeap(this, daPy_createHeap, 0xB0000)) {
        JUT_ASSERT(0x53B6, 0);
    }
    
    fopAcM_SetMtx(this, mpCLModel->getBaseTRMtx());
    
    mpCLModel->setUserArea(reinterpret_cast<u32>(this));
    mpYmgcs00Model->setUserArea(reinterpret_cast<u32>(this));
    for (u16 i = 0; i < mpYmgcs00Model->getModelData()->getJointNum(); i++) {
        mpYmgcs00Model->getModelData()->getJointNodePointer(i)->setCallBack(daPy_auraCallback);
    }
    
    mpCLModelData->getJointNodePointer(0x01)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x0D)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x04)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x08)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x0C)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x1C)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x0F)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x00)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x28)->setCallBack(daPy_jointCallback1);
    
    m_pbCalc[PART_UNDER_e]->setUserArea(reinterpret_cast<u32>(this));
    m_pbCalc[PART_UNDER_e]->setBeforeCalc(daPy_jointBeforeCallback);
    m_pbCalc[PART_UNDER_e]->setAfterCalc(daPy_jointAfterCallback);
    m_pbCalc[PART_UPPER_e]->setUserArea(reinterpret_cast<u32>(this));
    m_pbCalc[PART_UPPER_e]->setBeforeCalc(daPy_jointBeforeCallback);
    m_pbCalc[PART_UPPER_e]->setAfterCalc(daPy_jointAfterCallback);
    
    int i;
    J3DMaterial* mat = mpCLModelData->getJointNodePointer(0x13)->getMesh();
    int zoff_blend_cnt = 0;
    int zoff_none_cnt = 0;
    int zon_cnt = 0;
    for (i = 0; i < 2; i++) {
        while (mat) {
            mat->setMaterialMode(1);
            if (mat->getZMode()->getCompareEnable() == 0) {
                if (mat->getBlend()->mBlendMode == 1) {
                    mpZOffBlendShape[zoff_blend_cnt] = mat->getShape();
                    zoff_blend_cnt++;
                    JUT_ASSERT(0x53EE, zoff_blend_cnt <= 4);
                } else {
                    mpZOffNoneShape[zoff_none_cnt] = mat->getShape();
                    zoff_none_cnt++;
                    JUT_ASSERT(0x53F2, zoff_none_cnt <= 4);
                }
            } else {
                mpZOnShape[zon_cnt] = mat->getShape();
                zon_cnt++;
                JUT_ASSERT(0x53F6, zon_cnt <= 4);
            }
            mat = mat->getNext();
        }
        mat = mpCLModelData->getJointNodePointer(0x15)->getMesh();
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
    field_0x2a8 = daPy_HIO_move_c0::m.field_0x18;
    gravity = daPy_HIO_autoJump_c0::m.field_0xC;
    maxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
    mAcchCir[0].SetWall(30.1f, 35.0f);
    mAcchCir[1].SetWall(89.9f, 35.0f);
    mAcchCir[2].SetWall(125.0f, 35.0f);
    mHeadTopPos.setall(0.0f);
    mHeight = 125.0f;
    mHeldItemType = 0x100;
    mKeepItemType = 0x100;
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
    JUT_ASSERT(0x5493, dummy_data != 0);
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(mpItemHeaps[0]);
    
    mpItemHeaps[1] = mDoExt_createSolidHeapFromGameToCurrent(0xE600, 0x20);
    dummy_data = new u8[0xE600];
    JUT_ASSERT(0x5499, dummy_data != 0);
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(mpItemHeaps[1]);
    
    createAnimeHeap(&mpItemAnimeHeap, HEAP_TYPE_ITEM_ANIME_e);
    
    mActorKeepEquip.clearData();
    mActorKeepThrow.clearData();
    mActorKeepGrab.clearData();
    mActorKeepRope.clearData();
    m3628 = fpcM_ERROR_PROCESS_ID_e;
    m3634 = fpcM_ERROR_PROCESS_ID_e;
    mTactZevPartnerPID = fpcM_ERROR_PROCESS_ID_e;
    m3630 = fpcM_ERROR_PROCESS_ID_e;
    
    ResTIMG* blur_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_BLUR);
    mSwBlur.mpTex = blur_img;
    
    current.angle.z = 0;
    shape_angle.z = 0;
    m3526 = 8;
    m3648.w = 1.0f;
    resetSeAnime();
    
    ResTIMG* tmp_tex = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_I4_BALL128B);
    JUT_ASSERT(0x54B7, tmp_tex != 0);
    mSightPacket.setSightTex(tmp_tex);
    ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_ROCK_MARK);
    JUT_ASSERT(0x54BD, tmp_img != 0);
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
    JUT_ASSERT(0x5504, texture != 0);
    JUTNameTab* textureName = mpCLModelData->getTextureName();
    JUT_ASSERT(0x5506, textureName != 0);
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
int phase_1(daPy_lk_c* i_this) {
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
int phase_2(daPy_lk_c* i_this) {
    int result;

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
int daPy_lk_c::makeBgWait() {
    /* Nonmatching */
    return cPhs_NEXT_e;
}

/* 80127B50-80127B70       .text phase_3__FP9daPy_lk_c */
int phase_3(daPy_lk_c* i_this) {
    return i_this->makeBgWait();
}

/* 80127B70-80127BA0       .text daPy_Create__FP10fopAc_ac_c */
static s32 daPy_Create(fopAc_ac_c* i_this) {
    static int (*l_method[4])(daPy_lk_c*) = {
        phase_1,
        phase_2,
        phase_3,
        NULL,
    };
    daPy_lk_c* a_this = (daPy_lk_c*)i_this;

    return dComLbG_PhaseHandler(a_this->getPhase(), (cPhs__Handler*)l_method, a_this);
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
    
    if (mpSeAnmFrameCtrl->getAttribute() == J3DFrameCtrl::LOOP_REPEAT_e) {
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
BOOL daPy_lk_c::setActAnimeUpper(u16 r4, daPy_UPPER r29, f32 f28, f32 f29, s16 r30, f32 f30) {
    J3DAnmTransform* r31 = getAnimeResource(&m_anm_heap_upper[r29], r4, 0x2400);
    resetPriTextureAnime();
    mAnmRatioUpper[r29].setAnmTransform(r31);
    mAnmRatioUpper[r29].setRatio(1.0f);
    if (r30 < 0) {
        r30 = r31->getFrameMax();
    }
    
    f32 f31 = f28 < 0.0f ? r30 - 0.001f : f29;
    setFrameCtrl(&mFrameCtrlUpper[r29], r31->getAttribute(), f29, r30, f28, f31);
    r31->setFrame(f31);
    
    if (f30 >= 0.0f) {
        m_old_fdata->initOldFrameMorf(f30, 2, 0x1D);
    }
    
    return TRUE;
}

/* 801285F8-801286C0       .text resetActAnimeUpper__9daPy_lk_cFQ29daPy_lk_c10daPy_UPPERf */
BOOL daPy_lk_c::resetActAnimeUpper(daPy_UPPER r4, f32 f31) {
    if (checkDashDamageAnime()) {
        mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
    }
    
    mAnmRatioUpper[r4].setAnmTransform(NULL);
    mAnmRatioUpper[r4].setRatio(0.0f);
    m_anm_heap_upper[r4].mIdx = -1;
    mFrameCtrlUpper[r4].init(0);
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
void daPy_lk_c::simpleAnmPlay(J3DAnmBase*) {
    /* Nonmatching */
}

/* 8012887C-801288A0       .text setHandModel__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::setHandModel(daPy_ANM anmIdx) {
    mLeftHandIdx = mAnmDataTable[anmIdx].mLeftHandIdx;
    mRightHandIdx = mAnmDataTable[anmIdx].mRightHandIdx;
}

/* 801288A0-8012894C       .text getAnmData__9daPy_lk_cCFQ29daPy_lk_c8daPy_ANM */
const daPy_anmIndex_c* daPy_lk_c::getAnmData(daPy_ANM anm) const {
    if (mHeldItemType == 0x103) {
        if (anm < (s32)ARRAY_SIZE(mSwordAnmIndexTable)) {
            return &mSwordAnmIndexTable[anm];
        }
    } else if (mHeldItemType == 0x101) {
        if (anm < (s32)ARRAY_SIZE(mBokoAnmIndexTable)) {
            return &mBokoAnmIndexTable[anm];
        }
    } else if (mHeldItemType == dItem_SKULL_HAMMER_e) {
        if (anm < (s32)ARRAY_SIZE(mHammerAnmIndexTable)) {
            return &mHammerAnmIndexTable[anm];
        }
    } else if (mHeldItemType == dItem_BOOMERANG_e || mHeldItemType == dItem_DEKU_LEAF_e || mHeldItemType == dItem_TELESCOPE_e) {
        if (anm == ANM_DASH) {
            return &mSwordAnmIndexTable[anm];
        }
    }
    return &mAnmDataTable[anm].mAnmIdx;
}

/* 8012894C-80128988       .text checkGrabWeapon__9daPy_lk_cFi */
BOOL daPy_lk_c::checkGrabWeapon(int r4) {
    if (mHeldItemType == 0x101 && mActorKeepEquip.getActor() != NULL) {
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
void daPy_lk_c::setPlayerPosAndAngle(cXyz*, s16) {
    /* Nonmatching */
}

/* 80128C10-80128CE4       .text setPlayerPosAndAngle__9daPy_lk_cFP4cXyzP5csXyz */
void daPy_lk_c::setPlayerPosAndAngle(cXyz*, csXyz*) {
    /* Nonmatching */
}

/* 80128CE4-80128DC0       .text setPlayerPosAndAngle__9daPy_lk_cFPA4_f */
void daPy_lk_c::setPlayerPosAndAngle(MtxP) {
    /* Nonmatching */
}

/* 80128DC0-80128F8C       .text endDemoMode__9daPy_lk_cFv */
void daPy_lk_c::endDemoMode() {
    /* Nonmatching */
}

/* 80128F8C-8012901C       .text getBokoFlamePos__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::getBokoFlamePos(cXyz* outPos) {
    if (mHeldItemType == 0x101) {
        daBoko_c* boko = (daBoko_c*)fopAcM_SearchByID(mActorKeepEquip.getID());
        if (boko && boko->m2C4 != 0) { // maybe daBoko_c::getFlameTimer inline
            *outPos = mSwordTopPos;
            return TRUE;
        }
    }
    return FALSE;
}

actor_method_class2 l_daPy_Method = {
    (process_method_func)daPy_Create,
    (process_method_func)daPy_Delete,
    (process_method_func)daPy_Execute,
    (process_method_func)daPy_IsDelete,
    (process_method_func)daPy_Draw,
};

actor_process_profile_definition2 g_profile_PLAYER = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 5,
    /* ListPrio     */ fpcLy_CURRENT_e,
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
