/**
 * d_a_player_dproc.inc
 *
 * Code relating to "demo processes" (small cutscene-like actions).
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "SSystem/SComponent/c_counter.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_itembase.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_main_data.h"
#include "d/actor/d_a_ship.h"
#include "d/d_gameover.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"
#include "m_Do/m_Do_graphic.h"

/* 8012CD60-8012CDD4       .text getDemoLookActor__9daPy_lk_cFv */
fopAc_ac_c* daPy_lk_c::getDemoLookActor() {
    if (mDemo.getParam0() == 1) {
        return dComIfGp_event_getPt1();
    } else if (mDemo.getParam0() == 2) {
        return dComIfGp_event_getPt2();
    } else if (mDemo.getParam0() == 3) {
        return fopAcM_getTalkEventPartner(this);
    }

    return NULL;
}

/* 8012CDD4-8012CE2C       .text setTinkleCeiverModel__9daPy_lk_cFv */
void daPy_lk_c::setTinkleCeiverModel() {
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpEquipItemModel, LINK_BDL_TCEIVER, 0x13000022);
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8012CE2C-8012CEFC       .text setTalismanModel__9daPy_lk_cFv */
void daPy_lk_c::setTalismanModel() {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_TETOLACH);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_TETOLACH, 0x13000022);
    int ret = mSwordAnim.init(tmp_modelData, bck, true, J3DFrameCtrl::EMode_LOOP, 0.2f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(82, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8012CEFC-8012CFE8       .text setLetterModel__9daPy_lk_cFv */
void daPy_lk_c::setLetterModel() {
    if (mEquipItem != daPyItem_UNK104_e) {
        J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_GETLETTERA);
        JKRHeap* oldHeap = setItemHeap();
        J3DModelData* tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_LETTER, 0x13000022);
        int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
        if (!ret) {
            JUT_ASSERT(120, FALSE);
        }
        mDoExt_setCurrentHeap(oldHeap);
        m35EC = 0.0f;
        mEquipItem = daPyItem_UNK104_e;
    }
}

/* 8012CFE8-8012D010       .text checkCaughtShapeHide__9daPy_lk_cFv */
BOOL daPy_lk_c::checkCaughtShapeHide() {
    if (mCurProc == daPyProc_DEMO_CAUGHT_e && mProcVar0.m3570 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* 8012D010-8012D08C       .text setShapeAngleToTalkActor__9daPy_lk_cFv */
void daPy_lk_c::setShapeAngleToTalkActor() {
    fopAc_ac_c* partner_p = fopAcM_getTalkEventPartner(this);

    if (partner_p != NULL) {
        s16 partner_name = fopAcM_GetName(partner_p);
        s16 target;
        if (partner_name == PROC_AGB) {
            target = cLib_targetAngleY(&current.pos, &partner_p->eyePos);
        } else {
            target = fopAcM_searchActorAngleY(this, partner_p);
        }
        cLib_addCalcAngleS(
            &shape_angle.y,
            target,
            daPy_HIO_turn_c0::m.field_0x6,
            daPy_HIO_turn_c0::m.field_0x8,
            daPy_HIO_turn_c0::m.field_0xA
        );
    }
}

/* 8012D08C-8012D134       .text checkEndMessage__9daPy_lk_cFUl */
BOOL daPy_lk_c::checkEndMessage(u32 i_msgNo) {
    if (m3628 == fpcM_ERROR_PROCESS_ID_e) {
        m3628 = fopMsgM_messageSet(i_msgNo);
    } else {
        msg_class* msg_p = fopMsgM_SearchByID(m3628);
        if (msg_p != NULL) {
            if (msg_p->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                msg_p->mStatus = fopMsgStts_MSG_ENDS_e;
            } else if (msg_p->mStatus == fopMsgStts_BOX_CLOSED_e) {
                msg_p->mStatus = fopMsgStts_MSG_DESTROYED_e;
                return TRUE;
            } else if (msg_p->mStatus == fopMsgStts_MSG_PREPARING_e && i_msgNo == 0x14A2) {
                fopMsgM_demoMsgFlagOn();
            }
        }
    }
    return FALSE;
}

/* 8012D134-8012D300       .text setTalkStartBack__9daPy_lk_cFv */
int daPy_lk_c::setTalkStartBack() {
    fopAc_ac_c* partner_p = fopAcM_getTalkEventPartner(this);
    if (partner_p != NULL) {
        cXyz sp24 = current.pos - partner_p->current.pos;
        f32 var_f1 = sp24.absXZ();
        if (var_f1 < 100.0f && var_f1 > 1.0f) {
            f32 temp_f2_2 = 100.0f / var_f1;
            m370C.x = partner_p->current.pos.x + temp_f2_2 * sp24.x;
            m370C.y = current.pos.y + 30.1f;
            m370C.z = partner_p->current.pos.z + temp_f2_2 * sp24.z;
            mGndChk.SetPos(&m370C);

            if (dComIfG_Bgsp()->GroundCross(&mGndChk) - current.pos.y >= -30.1f) {
                current.angle.y = cM_atan2s(sp24.x, sp24.z);
                mVelocity = 5.0f;
                setSingleMoveAnime(ANM_WALK, -daPy_HIO_move_c0::m.field_0x44, 0.0f, -1, daPy_HIO_turn_c0::m.field_0x18);
                return 1;
            }
        }
    }

    return 0;
}

/* 8012D300-8012D3C4       .text dProcTool_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTool_init() {
    if (mCurProc == daPyProc_DEMO_TOOL_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_TOOL_e);
    speed.y = speedF = mVelocity = 0.0f;
    m_anm_heap_under[UNDER_MOVE0_e].field_0x6 = -1;
    m_anm_heap_under[UNDER_MOVE0_e].field_0x4 = -1;
    m_anm_heap_upper[UPPER_MOVE0_e].mIdx = -1;
    m_anm_heap_under[UNDER_MOVE1_e].mIdx = -1;
    m_anm_heap_upper[UPPER_MOVE1_e].mIdx = -1;
    m_pbCalc[PART_UPPER_e]->setRatio(0, 1.0f);
    m_pbCalc[PART_UPPER_e]->setRatio(1, 0.0f);
    m_pbCalc[PART_UNDER_e]->setRatio(0, 1.0f);
    m_pbCalc[PART_UNDER_e]->setRatio(1, 0.0f);
    mAnmRatioUnder[UNDER_MOVE1_e].setAnmTransform(NULL);
    mAnmRatioUpper[UNDER_MOVE1_e].setAnmTransform(NULL);
    mProcVar0.m3570 = 0;
    m3574 = 0;
    m34D4 = 0;
    m34D6 = 0;
    return true;
}

/* 8012D3C4-8012DA3C       .text dProcTool__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTool() {
    /* Nonmatching */
}

/* 8012DA3C-8012DBD0       .text dProcTalk_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTalk_init() {
    if (mCurProc == daPyProc_DEMO_TALK_e) {
        return true;
    }
    mProcVar0.m3570 = 0;
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_TALK_e);
    if (iVar2 == 0) {
        if ((mDemo.getDemoMode() != 8) && (mEquipItem != daPyItem_NONE_e)) {
            setAnimeUnequip();
        }
        mProcVar0.m3570 = setTalkStartBack();
    }
    if (mProcVar0.m3570 == 0) {
        mVelocity = 0.0f;
        if (mDemo.getDemoMode() == 8) {
            setSingleMoveAnime(ANM_WAITS, daPy_HIO_move_c0::m.field_0x38, 0.0f, -1, daPy_HIO_turn_c0::m.field_0x18);
        } else {
            setSingleMoveAnime(ANM_TALKA, daPy_HIO_turn_c0::m.field_0x14, 0.0f, -1, daPy_HIO_turn_c0::m.field_0x18);
        }
        m3574 = mDemo.getParam1();
        if (m3574 == 1) {
            setTextureAnime(145, 0);
            offModeFlg(ModeFlg_00000080);
        }
    }
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK10_e);
    if (mDemo.getParam0() != 1) {
        mDoAud_seStart(JA_SE_TALK_START);
    }
    initShipRideUseItem(iVar2, 0);
    return true;
}

/* 8012DBD0-8012DDEC       .text dProcTalk__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTalk() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    setShapeAngleToTalkActor();
    if (mProcVar0.m3570 != 0) {
        cXyz local_28 = m370C - current.pos;
        int iVar2 = 0;

        if (mAcch.ChkWallHit()) {
            dBgS_AcchCir* acchCir_p = mAcchCir;
            for (int i = 0; i < 3; i++) {
                if (acchCir_p->ChkWallHit()) {
                    iVar2 = cLib_distanceAngleS(acchCir_p->GetWallAngleY(), current.angle.y);
                    break;
                }
                acchCir_p++;
            }
        }
        if ((0x4000 < cLib_distanceAngleS(cM_atan2s(local_28.x, local_28.z), current.angle.y)) || (0x4000 < iVar2)) {
            current.pos.x = m370C.x;
            current.pos.z = m370C.z;
            mProcVar0.m3570 = 0;
            if (mDemo.getDemoMode() == 8) {
                setSingleMoveAnime(ANM_WAITS, daPy_HIO_move_c0::m.field_0x38, 0.0f, -1, daPy_HIO_turn_c0::m.field_0x18);
            } else {
                setSingleMoveAnime(ANM_TALKA, daPy_HIO_turn_c0::m.field_0x14, 0.0f, -1, daPy_HIO_turn_c0::m.field_0x18);
            }
            if (m3574 == 1) {
                setTextureAnime(145, 0);
                offModeFlg(ModeFlg_00000080);
            }
            mVelocity = 0.0f;
        }
    } else {
        current.angle.y = shape_angle.y;
        if (m3574 != mDemo.getParam1()) {
            m3574 = mDemo.getParam1();
            if (m3574 == 1) {
                setTextureAnime(145, m3530);
                offModeFlg(ModeFlg_00000080);
            } else {
                setTextureAnime(0, m3530);
                onModeFlg(ModeFlg_00000080);
            }
        }
    }
    return true;
}

/* 8012DDEC-8012DEA0       .text dProcDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDamage_init() {
    if (mCurProc == daPyProc_DEMO_DAMAGE_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_DAMAGE_e);
    setSingleMoveAnime(
        ANM_DAMF,
        daPy_HIO_damage_c0::m.field_0x14,
        daPy_HIO_damage_c0::m.field_0x18,
        daPy_HIO_damage_c0::m.field_0x0,
        daPy_HIO_damage_c0::m.field_0x8
    );
    mVelocity = 0.0f;
    m35A0 = M_PI / (daPy_HIO_damage_c0::m.field_0x0 - daPy_HIO_damage_c0::m.field_0x18);
    return true;
}

/* 8012DEA0-8012DF24       .text dProcDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDamage() {
    mVelocity = -2.0f * cM_fsin(m35A0 * mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 8012DF24-8012E054       .text dProcHoldup_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcHoldup_init() {
    daPy_ANM dVar3;
    short sVar2;
    f32 dVar6;
    f32 dVar5;
    f32 dVar4;

    if (mCurProc == daPyProc_DEMO_HOLDUP_e) {
        return false;
    }

    BOOL uVar1 = checkModeFlg(ModeFlg_WHIDE) ? TRUE : FALSE;
    commonProcInit(daPyProc_DEMO_HOLDUP_e);
    if (uVar1) {
        if (checkNoResetFlg0(daPyFlg0_UNK10000)) {
            dVar3 = ANM_WALLHOLDUPDW;
            dVar6 = daPy_HIO_holdup_c0::m.field_0x30;
            dVar5 = daPy_HIO_holdup_c0::m.field_0x34;
            sVar2 = daPy_HIO_holdup_c0::m.field_0x6;
            dVar4 = daPy_HIO_holdup_c0::m.field_0x38;
        } else {
            dVar3 = ANM_WALLHOLDUP;
            dVar6 = daPy_HIO_holdup_c0::m.field_0x24;
            dVar5 = daPy_HIO_holdup_c0::m.field_0x28;
            sVar2 = daPy_HIO_holdup_c0::m.field_0x4;
            dVar4 = daPy_HIO_holdup_c0::m.field_0x2C;
        }
        onModeFlg(ModeFlg_WHIDE);
        setBgCheckParam();
    } else {
        dVar3 = ANM_HOLDUP;
        dVar6 = daPy_HIO_holdup_c0::m.field_0x18;
        dVar5 = daPy_HIO_holdup_c0::m.field_0x1C;
        sVar2 = daPy_HIO_holdup_c0::m.field_0x2;
        dVar4 = daPy_HIO_holdup_c0::m.field_0x20;
    }
    setSingleMoveAnime(dVar3, dVar6, dVar5, sVar2, dVar4);
    mVelocity = 0.0f;
    return true;
}

/* 8012E054-8012E09C       .text dProcHoldup__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcHoldup() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 8012E09C-8012E244       .text dProcOpenTreasure_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcOpenTreasure_init() {
    float fVar1;
    daPy_ANM dVar2;

    if (mCurProc == daPyProc_DEMO_OPEN_TREASURE_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_OPEN_TREASURE_e);
    if (mDemo.getParam0() == 1) {
        dVar2 = ANM_BOXOPENSHORTLINK;
        fVar1 = 75.0f;
    } else {
        dVar2 = ANM_BOXOPENLINK;
        fVar1 = 55.0f;
    }
    setSingleMoveAnime(dVar2, 1.0f, 0.0f, -1, 3.0f);
    mVelocity = 0.0f;
    if (mEquipItem == daPyItem_BOKO_e) {
        daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
        if (boko != NULL) {
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(shape_angle.y + 0x2000);
            MtxP mtx = mDoMtx_stack_c::get();
            if (boko->mpModel != NULL) {
                boko->mpModel->setBaseTRMtx(mtx);
            }
        }
    }
    fopAc_ac_c* partner_p = fopAcM_getEventPartner(this);
    if (partner_p != NULL) {
        shape_angle.y = partner_p->shape_angle.y + 0x8000;
        current.angle.y = shape_angle.y;
        current.pos.x = partner_p->current.pos.x - fVar1 * cM_ssin(shape_angle.y);
        current.pos.z = partner_p->current.pos.z - fVar1 * cM_scos(shape_angle.y);
    }
    deleteEquipItem(FALSE);
    mAcch.SetWallNone();
    mAcch.OffLineCheck();
    return true;
}

/* 8012E244-8012E28C       .text dProcOpenTreasure__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcOpenTreasure() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 8012E28C-8012E418       .text setGetItemSound__9daPy_lk_cFUsi */
void daPy_lk_c::setGetItemSound(u16 param_1, int param_2) {
    if (param_1 == dItem_GREEN_RUPEE_e || param_1 == dItem_BLUE_RUPEE_e || param_1 == dItem_YELLOW_RUPEE_e ||
        param_1 == dItem_RED_RUPEE_e || param_1 == dItem_PURPLE_RUPEE_e || param_1 == TINCLE_RUPEE1)
    {
        mDoAud_seStart(JA_SE_ME_ITEM_GET_S);
        dComIfGp_setMesgBgmOn2();
    } else if ((param_1 == dItem_HEART_CONTAINER_e) ||
               (param_1 == dItem_HEART_PIECE_e && ((dComIfGs_getMaxLife() % 4) == 3)))
    {
        mDoAud_subBgmStart(JA_BGM_GET_HEART);
        dComIfGp_setMesgBgmOn();
    } else if (param_1 == dItem_HEART_PIECE_e || param_1 == dItem_JOY_PENDANT_e || param_1 == dItem_SMALL_KEY_e ||
               param_1 == dItem_SILVER_RUPEE_e || param_1 == dItem_ORANGE_RUPEE_e)
    {
        mDoAud_subBgmStart(JA_BGM_ITEM_GET_S);
        dComIfGp_setMesgBgmOn();
    } else if (param_2 != dItem_HEART_e) {
        mDoAud_seStart(JA_SE_ME_ITEM_GET_S);
        dComIfGp_setMesgBgmOn2();
    } else {
        mDoAud_subBgmStart(JA_BGM_ITEM_GET);
        dComIfGp_setMesgBgmOn();
    }
}

/* 8012E418-8012E6B4       .text setGetDemo__9daPy_lk_cFv */
BOOL daPy_lk_c::setGetDemo() {
    int staffIdx = dComIfGp_evmng_getMyStaffId("Link", this);
    if (dComIfGp_event_runCheck() && m34CE & 0x04) {
        dComIfGp_evmng_cutEnd(staffIdx);
        return TRUE;
    }

    if (dComIfGp_evmng_startCheck("DEFAULT_GETITEM")) {
        if (m34CE & 0x01 || ((checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK80000000 | daPyFlg0_UNK20000000)) ||
                              !mAcch.ChkGroundHit() || daPy_lk_c::checkPlayerFly()) &&
                             !dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)))
        {
            if ((m34CE & 0x01) == 0) {
                mMsgId = fpcM_ERROR_PROCESS_ID_e;
            }
            m34CE |= 0x01;
            char* cutName = dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx);
            if (cutName != NULL) {
                // TODO: is there an inline for parsing link's cut name -> cut
                // index?
                u32 r0 = (cutName[0] - '0') * 100 + (cutName[1] - '0') * 10 + (cutName[2] - '0');
                if (r0 == 0xB) {
                    fopAc_ac_c* itemPartner = fopAcM_getItemEventPartner(this);
                    if (itemPartner != NULL &&
                        (fopAcM_GetName(itemPartner) == PROC_ITEM || fopAcM_GetName(itemPartner) == PROC_Demo_Item))
                    {
                        daItemBase_c* item = (daItemBase_c*)itemPartner;
                        item->hide();
                        u32 itemNo = item->getItemNo();
                        if ((m34CE & 0x02) == 0) {
                            setGetItemSound(itemNo, 0);
                            m34CE |= 0x02;
                        }

                        u32 itemGetMsgNo;
                        if (itemNo == dItem_HEART_PIECE_e && (dComIfGs_getMaxLife() % 4) != 0) {
                            itemGetMsgNo = MSG_NO_FOR_ITEM(dItem_HEART_PIECE_2_e + (dComIfGs_getMaxLife() % 4) - 1);
                        } else {
                            itemGetMsgNo = MSG_NO_FOR_ITEM(itemNo);
                        }

                        if (mMsgId == fpcM_ERROR_PROCESS_ID_e) {
                            mMsgId = fopMsgM_messageSet(itemGetMsgNo);
                        } else {
                            msg_class* msg_p = fopMsgM_SearchByID(mMsgId);
                            if (msg_p != NULL) {
                                if (msg_p->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                                    msg_p->mStatus = fopMsgStts_MSG_ENDS_e;
                                } else if (msg_p->mStatus == fopMsgStts_BOX_CLOSED_e) {
                                    msg_p->mStatus = fopMsgStts_MSG_DESTROYED_e;
                                    dComIfGp_evmng_cutEnd(staffIdx);
                                    item->dead();
                                    m34CE |= 0x04;
                                } else if (msg_p->mStatus == fopMsgStts_MSG_PREPARING_e) {
                                    fopMsgM_demoMsgFlagOn();
                                }
                            }
                        }
                    }
                } else {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }
            return TRUE;
        }
    }
    m34CE = 0;
    return FALSE;
}

/* 8012E6B4-8012E8B0       .text dProcGetItem_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcGetItem_init() {
    BOOL sVar6 = 0;
    BOOL sVar5 = 0;

    if (mCurProc == daPyProc_DEMO_GET_ITEM_e) {
        return true;
    }
    if (mCurProc == daPyProc_DEMO_OPEN_TREASURE_e) {
        m34C2 = 10;
        mAcch.ClrWallNone();
        if (m_anm_heap_under[UNDER_MOVE0_e].mIdx != LKANM_BCK_BOXOPENLINK) {
            sVar5 = 1;
        }
    } else if (mCurProc == daPyProc_DEMO_OPEN_SALVAGE_TREASURE_e) {
        m34C2 = 6;
        sVar6 = 1;
    }
    int iVar2 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_DEMO_GET_ITEM_e);
    mVelocity = 0.0f;
    if (mEquipItem == daPyItem_NONE_e) {
        setSingleMoveAnime(ANM_ITEMGET, 1.0f, 0.0f, -1, 3.0f);
        mProcVar0.m3570 = 0;
        onModeFlg(ModeFlg_00000400);
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        setAnimeUnequip();
        m3598 = 0.0f;
        mProcVar0.m3570 = 1;
    }
    if (mDemo.getParam0() != 0) {
        int item_no;
        if (mDemo.getParam0() != 0x100) {
            item_no = mDemo.getParam0();
        } else {
            item_no = dComIfGp_event_getGtItm();
        }
        fpc_ProcID itemID =
            fopAcM_createItemForPresentDemo(&current.pos, item_no, 0, 0xffffffff, fopAcM_GetRoomNo(this), NULL, NULL);
        if (itemID != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(itemID);
        }
        m34D4 = item_no;
    } else {
        m34D4 = -1;
    }
    camera_class* cam = dComIfGp_getCamera(mCameraInfoIdx);
    m34D6 = shape_angle.y - fopCamM_GetAngleY(cam);
    current.angle.y = shape_angle.y;
    m3628 = fpcM_ERROR_PROCESS_ID_e;
    m34D0 = 0;
    m34D8 = sVar6;
    initShipRideUseItem(iVar2, 0);
    m3574 = 0;
    m3624 = 0;
    m34DA = sVar5;
    dKy_Itemgetcol_chg_on();
    return true;
}

/* 8012E8B0-8012ECB0       .text dProcGetItem__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcGetItem() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    if (m3574 != 0) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
        return true;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < 10.0f) {
        camera_class* cam = dComIfGp_getCamera(mCameraInfoIdx);
        m34D6 = shape_angle.y - fopCamM_GetAngleY(cam);
    }
    daItemBase_c* item = (daItemBase_c*)fopAcM_getItemEventPartner(this);
    if ((m34D4 == -1) && (item != NULL)) {
        m34D4 = item->getItemNo() & 0xff;
    }
    if ((mProcVar0.m3570 == 0) && (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= 11.0f)) {
        if ((m34D0 == 0) && (m34D4 != -1)) {
            m34D0 = 1;
            setGetItemSound(m34D4, m34DA);
        }
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() <= 17.0f) {
            if (m34D6 > 0x4000) {
                shape_angle.y =
                    current.angle.y + ((0x10000 - m34D6) * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - 10.0f) / 7.0f);
            } else {
                shape_angle.y = current.angle.y - (m34D6 * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - 10.0f) / 7.0f);
            }
        } else {
            if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > 17.0f) {
                shape_angle.y = current.angle.y - m34D6;
            }
        }
    }
    if (mProcVar0.m3570 != 0) {
        if (checkNoUpperAnime()) {
            setSingleMoveAnime(ANM_ITEMGET, 1.0f, 0.0f, -1, 3.0f);
            mProcVar0.m3570 = 0;
            onModeFlg(ModeFlg_00000400);
        }
        if ((item != NULL) && (fopAcM_GetName(item) == PROC_ITEM || (fopAcM_GetName(item) == PROC_Demo_Item))) {
            item->hide();
        }
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            if ((item != NULL) && (fopAcM_GetName(item) == PROC_ITEM || fopAcM_GetName(item) == PROC_Demo_Item)) {
                item->show();
                if ((m3624 == 0) && (m34D4 != -1)) {
                    if ((m34D4 == 7) && (dComIfGs_getMaxLife() % 4)) {
                        m3624 = (dComIfGs_getMaxLife() % 4) + 0x7b;
                    } else {
                        m3624 = MSG_NO_FOR_ITEM(m34D4);
                    }
                }
                if ((m3624 != 0) && (checkEndMessage(m3624))) {
                    shape_angle.y += 0x8000;
                    current.angle.y = shape_angle.y;
                    m34DE = shape_angle.y;
                    setOldRootQuaternion(0, -0x8000, 0);
                    J3DTransformInfo* pJVar2 = m_old_fdata->getOldFrameTransInfo(0);
                    pJVar2->mTranslate.x *= -1.0f;
                    pJVar2->mTranslate.z *= -1.0f;
                    dComIfGp_evmng_cutEnd(mStaffIdx);
                    item->dead();
                    m3574 = 1;
                    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
                }
            }
        } else if ((item != NULL) && (fopAcM_GetName(item) == PROC_ITEM || (fopAcM_GetName(item) == PROC_Demo_Item))) {
            item->hide();
        }
    }
    return true;
}

/* 8012ECB0-8012ED30       .text dProcUnequip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcUnequip_init() {
    if (mCurProc == daPyProc_DEMO_UNEQUIP_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_UNEQUIP_e);
    mVelocity = 0.0f;
    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    if (mEquipItem != daPyItem_NONE_e) {
        setAnimeUnequip();
        m3598 = 0.0f;
    }
    return true;
}

/* 8012ED30-8012ED74       .text dProcUnequip__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcUnequip() {
    if (checkNoUpperAnime()) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 8012ED74-8012EE0C       .text dProcLavaDamage_init_sub__9daPy_lk_cFv */
void daPy_lk_c::dProcLavaDamage_init_sub() {
    speed.y = daPy_HIO_restart_c0::m.field_0x8;
    mProcVar0.m3570 = 0;
    voiceStart(4);
    seStartMapInfo(JA_SE_LK_FALL_MAGMA);
    gravity = daPy_HIO_autoJump_c0::m.field_0xC;
    mDemo.setDemoType(5);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK10000000_e);
    daPy_py_c::changePlayer(this);
}

/* 8012EE0C-8012EEE4       .text dProcLavaDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLavaDamage_init() {
    if (mCurProc == daPyProc_DEMO_LAVA_DAMAGE_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_LAVA_DAMAGE_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_LAVADAM, daPy_HIO_restart_c0::m.field_0x0, 0.0f, -1, daPy_HIO_restart_c0::m.field_0x4);
    m32E4.makeEmitter(dPa_name::ID_SCENE_8078, mpCLModel->getAnmMtx(0), &current.pos, NULL);
    if (dComIfGp_event_compulsory(this)) {
        dProcLavaDamage_init_sub();
    } else {
        speed.y = 0.0f;
        gravity = 0.0f;
        mProcVar0.m3570 = 1;
    }
    return true;
}

/* 8012EEE4-8012EF78       .text dProcLavaDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLavaDamage() {
    if (mProcVar0.m3570 == 1) {
        if (dComIfGp_event_compulsory(this)) {
            dProcLavaDamage_init_sub();
        }
    } else if (speed.y < -gravity) {
        startRestartRoom(4, 0xca, -1.0f, 1);
    }
    return true;
}

extern GXColor l_freeze_fade_color;

/* 8012EF78-8012F0DC       .text dProcFreezeDamage_init_sub__9daPy_lk_cFi */
void daPy_lk_c::dProcFreezeDamage_init_sub(int param_0) {
    static const u16 eff_joint[] = {
        0x0007,
        0x000B,
        0x001A,
        0x000E,
        0x001E,
    };

    if (param_0 != 0) {
        mProcVar0.m3570 = 1;
        mDemo.setDemoType(5);
        daPy_py_c::changePlayer(this);
    }
    endDamageEmitter();
    onNoResetFlg1(daPyFlg1_FREEZE_STATE);
    offNoResetFlg1(daPyFlg1_UNK40000);
    mDoGph_gInf_c::fadeOut(1.0f, l_freeze_fade_color);
    seStartMapInfo(JA_SE_LK_FREEZE);
    for (int i = 0; i < 5; i++) {
        const u16* uVar1 = eff_joint;
        MtxP pMVar2 = mpCLModel->getAnmMtx(uVar1[i]);
        cXyz local_28;
        mDoMtx_multVecZero(pMVar2, &local_28);
        dComIfGp_particle_setP1(dPa_name::ID_SCENE_827E, &local_28);
        if (i >= 3) {
            dComIfGp_particle_setP1(dPa_name::ID_SCENE_827F, &local_28);
        }
    }
}

/* 8012F0DC-8012F174       .text dProcFreezeDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcFreezeDamage_init() {
    if (mCurProc == daPyProc_DEMO_FREEZE_DAMAGE_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_FREEZE_DAMAGE_e);
    mVelocity = 0.0f;
    m34D0 = 60;
    if (dComIfGp_event_compulsory(this)) {
        dProcFreezeDamage_init_sub(1);
    } else {
        mProcVar0.m3570 = 0;
    }
    return true;
}

/* 8012F174-8012F210       .text dProcFreezeDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcFreezeDamage() {
    if (mProcVar0.m3570 == 0) {
        if (dComIfGp_event_compulsory(this)) {
            dProcFreezeDamage_init_sub(1);
        }
    } else {
        m34D0--;
        if (m34D0 == 0) {
            startRestartRoom(5, 0xc9, -1.0f, 1);
        }
    }
    return true;
}

/* 8012F210-8012F288       .text dProcDead_init_sub__9daPy_lk_cFv */
void daPy_lk_c::dProcDead_init_sub() {
    mProcVar0.m3570 = 0;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK20000000_e);
    m3628 = fopMsgM_create(PROC_GAMEOVER);
    mDemo.setDemoType(5);
    daPy_py_c::changePlayer(this);
}

/* 8012F288-8012F38C       .text dProcDead_init_sub2__9daPy_lk_cFv */
void daPy_lk_c::dProcDead_init_sub2() {
    static const Vec ripple_scale = {0.75f, 0.75f, 0.75f};

    mFrameCtrlUnder[UNDER_MOVE0_e].setRate(daPy_HIO_restart_c0::m.field_0xC);
    voiceStart(22);
    mDoAud_bgmStop(0);
    mDoAud_bgmStart(JA_BGM_DIE_LINK);
    dCam_getBody()->StartEventCamera(9, fopAcM_GetID(this), 0);
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
        dComIfGp_particle_setShipTail(
            dPa_name::ID_COMMON_003F,
            &current.pos,
            NULL,
            (cXyz*)&ripple_scale,
            0xff,
            &dPa_control_c::mSingleRippleEcallBack,
            -1
        );
        m34D6 = 1;
    }
}

/* 8012F38C-8012F3B8       .text checkGameOverStart__9daPy_lk_cFv */
BOOL daPy_lk_c::checkGameOverStart() {
    if ((mCurProc == daPyProc_DEMO_DEAD_e) && (m35A0 < 0.38f)) {
        return true;
    }
    return false;
}

/* 8012F3B8-8012F5A8       .text dProcDead_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDead_init() {
    daPy_ANM dVar6;
    float dVar8;

    if (mCurProc == daPyProc_DEMO_DEAD_e) {
        return true;
    }
    int iVar4 = checkShipRideUseItem(0);
    u32 uVar2 = checkModeFlg(ModeFlg_SWIM);
    u32 uVar3 = checkNoResetFlg0(daPyFlg0_UNK100);
    if (uVar2 != 0) {
        swimOutAfter(FALSE);
    }
    commonProcInit(daPyProc_DEMO_DEAD_e);
    if (dComIfGp_event_compulsory(this)) {
        dProcDead_init_sub();
        dVar8 = daPy_HIO_restart_c0::m.field_0xC;
    } else {
        dVar8 = 0.0f;
        mProcVar0.m3570 = 1;
    }
    mVelocity = 0.0f;
    m34D4 = 0;
    if (iVar4 != 0) {
        dVar6 = ANM_SHIPDIE;
    } else {
        if (uVar2 != 0) {
            dVar6 = ANM_SWIMDIE;
            onModeFlg(ModeFlg_SWIM);
            dComIfGp_setPlayerStatus0(0, daPyStts0_SWIM_e);
            if (uVar3 == 0) {
                offNoResetFlg0(daPyFlg0_UNK100);
                dVar8 = 0.0f;
                m34D4 = 1;
            } else {
                m34C2 = 0;
            }
        } else {
            dVar6 = ANM_DIELONG;
            onModeFlg(ModeFlg_02000000);
        }
    }
    setSingleMoveAnime(dVar6, dVar8, daPy_HIO_restart_c0::m.field_0x10, -1, daPy_HIO_restart_c0::m.field_0x14);
    mDamageWaitTimer = 0;
    m35E4 = 0.0f;
    m35A0 = 1.0f;
    if (m34D4 == 0) {
        speed.y = 0.0f;
    }
    gravity = 0.0f;
    m3574 = 0;
    initShipRideUseItem(iVar4, 1);
    m34D6 = 0;
    if (dVar8 > 0.0f) {
        dProcDead_init_sub2();
    }
    cancelNoDamageMode();
    return true;
}

/* 8012F5A8-8012F928       .text dProcDead__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDead() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
    }
    if (mProcVar0.m3570 != 0 && dComIfGp_event_compulsory(this)) {
        dProcDead_init_sub();
        if (m34D4 == 0) {
            dProcDead_init_sub2();
        }
    }
    if (m34D4 != 0 && changeSwimUpProc()) {
        m34D4 = 0;
        if (mProcVar0.m3570 == 0) {
            dProcDead_init_sub2();
        }
    }
    if ((mProcVar0.m3570 == 0) && (m34D4 == 0)) {
        if (checkModeFlg(ModeFlg_02000000)) {
            m35E4 = 0.1f * (frameCtrl.getFrame() - 120.0f);
        }
        if (frameCtrl.getRate() < 0.01f) {
            dGameover_c* this_01;
            cLib_chaseF(&m35A0, 0.0f, 0.01f);
            f32 dVar3 = 1.0f - m35A0;
            if ((m3628 != fpcM_ERROR_PROCESS_ID_e)) {
                this_01 = (dGameover_c*)fopMsgM_SearchByID(m3628);
                if (this_01) {
                    this_01->setBackAlpha(dVar3);
                }
            }
            if (((m35A0 < 0.38f) && (m3628 != fpcM_ERROR_PROCESS_ID_e)) &&
                (this_01 = (dGameover_c*)fopMsgM_SearchByID(m3628), this_01))
            {
                this_01->animeStart();
            }
            if (m3574 == 0) {
                int iVar1;
                if (m3628 != fpcM_ERROR_PROCESS_ID_e) {
                    this_01 = (dGameover_c*)fopMsgM_SearchByID(m3628);
                    if (this_01 != NULL) {
                        iVar1 = this_01->deleteCheck();
                    } else {
                        iVar1 = 0;
                    }
                } else {
                    iVar1 = 0;
                }
                if (iVar1 != 0) {
                    m3574 = 1;
                }
            }
            if ((m3574 != 0) && (g_dComIfG_gameInfo.play.mGameoverStatus == 2)) {
                dComIfGs_setGameStartStage();
                dComIfGs_gameStart();
            }
        } else {
            if (!dComIfGp_checkPlayerStatus0(0, (daPyStts0_SHIP_RIDE_e | daPyStts0_SWIM_e))) {
                if (frameCtrl.checkPass(129.0f)) {
                    voiceStart(0x17);
                    m34BE = 6;
                } else {
                    if (frameCtrl.getFrame() >= 129.0f) {
                        resetFootEffect();
                    }
                }
            } else if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
                if (frameCtrl.checkPass(9.0f) || frameCtrl.checkPass(15.0f)) {
                    csXyz acStack_30(0, shape_angle.y, 0);
                    GXColor amb, dif;
                    dKy_get_seacolor(&amb, &dif);
                    if (frameCtrl.checkPass(15.0f)) {
                        acStack_30.y += 0x8000;
                    }
                    dComIfGp_particle_setP1(
                        dPa_name::ID_COMMON_0314, &current.pos, &acStack_30, NULL, 0xff, NULL, -1, &amb
                    );
                } else {
                    if (frameCtrl.checkPass(50.0f)) {
                        m34D6 = 0;
                    } else {
                        if (frameCtrl.checkPass(110.0f)) {
                            m34D6 = 1;
                        }
                    }
                }
            }
        }
    }
    return true;
}

/* 8012F928-8012F99C       .text dProcLookAround_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookAround_init() {
    if (mCurProc == daPyProc_DEMO_LOOK_AROUND_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_LOOK_AROUND_e);
    setSingleMoveAnime(
        ANM_COMEOUT,
        daPy_HIO_holdup_c0::m.field_0xC,
        daPy_HIO_holdup_c0::m.field_0x10,
        daPy_HIO_holdup_c0::m.field_0x0,
        daPy_HIO_holdup_c0::m.field_0x14
    );
    mVelocity = 0.0f;
    return true;
}

/* 8012F99C-8012F9E4       .text dProcLookAround__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookAround() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 8012F9E4-8012FA50       .text dProcSalute_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSalute_init() {
    if (mCurProc == daPyProc_DEMO_SALUTE_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_SALUTE_e);
    setSingleMoveAnime(ANM_SALTATION, 1.0f, 0.0f, -1, 3.0f);
    mVelocity = 0.0f;
    return true;
}

/* 8012FA50-8012FA98       .text dProcSalute__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSalute() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 8012FA98-8012FB2C       .text dProcLookAround2_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookAround2_init() {
    if (mCurProc == daPyProc_DEMO_LOOK_AROUND2_e) {
        return false;
    }
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_LOOK_AROUND2_e);
    setSingleMoveAnime(ANM_WHO, 1.0f, 0.0f, -1, 5.0f);
    mVelocity = 0.0f;
    initShipRideUseItem(iVar2, 0);
    return true;
}

/* 8012FB2C-8012FB88       .text dProcLookAround2__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookAround2() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 8012FB88-8012FC24       .text dProcTalismanPickup_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTalismanPickup_init() {
    if (mCurProc == daPyProc_DEMO_TALISMAN_PICKUP_e) {
        return false;
    }
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_TALISMAN_PICKUP_e);
    setSingleMoveAnime(
        ANM_PICKUP,
        daPy_HIO_holdup_c0::m.field_0x3C,
        daPy_HIO_holdup_c0::m.field_0x40,
        daPy_HIO_holdup_c0::m.field_0x8,
        daPy_HIO_holdup_c0::m.field_0x44
    );
    mVelocity = 0.0f;
    initShipRideUseItem(iVar2, 1);
    return true;
}

/* 8012FC24-8012FCC0       .text dProcTalismanPickup__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTalismanPickup() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
    }
    if (frameCtrl.getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    } else if (frameCtrl.checkPass(65.0f)) {
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
    }
    return true;
}

/* 8012FCC0-8012FE58       .text dProcTalismanWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTalismanWait_init() {
    if (mCurProc == daPyProc_DEMO_TALISMAN_WAIT_e) {
        return false;
    }
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_TALISMAN_WAIT_e);
    setSingleMoveAnime(ANM_WAITPICKUP, 1.0f, 0.0f, -1, daPy_HIO_holdup_c0::m.field_0x48);
    mVelocity = 0.0f;
    setTalismanModel();
    m32E4.makeEmitter(dPa_name::ID_COMMON_03E9, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    mpEquipItemModel->setBaseTRMtx(mpCLModel->getAnmMtx(12));
    mDoMtx_stack_c::copy(mpCLModel->getAnmMtx(12));
    f32 adjust = (cM_ssin(g_Counter.mTimer * 1512));
    mDoMtx_stack_c::transM(7.0f, 0.0f, 15.0f + 3.0f * adjust);
    mDoMtx_stack_c::multVecZero(&m338C.getPos());
    dComIfGp_particle_setP1(dPa_name::ID_COMMON_03EA, &m338C.getPos(), NULL, NULL, 0xff, &m338C, -1);
    initShipRideUseItem(iVar2, 1);
    return true;
}

/* 8012FE58-8012FFEC       .text dProcTalismanWait__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTalismanWait() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
    }
    cXyz* pcVar1 = &m338C.getPos();
    mDoMtx_stack_c::copy(mpCLModel->getAnmMtx(12));
    f32 adjust = (cM_ssin(g_Counter.mTimer * 1512));
    mDoMtx_stack_c::transM(7.0f, 0.0f, 15.0f + 3.0f * adjust);
    mDoMtx_stack_c::multVecZero(pcVar1);
    mDoMtx_stack_c::transS(*pcVar1);
    mDoMtx_stack_c::YrotM(g_Counter.mTimer * 511);
    mpEquipItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mSwordAnim.play();
    J3DModelData* modelData = mpEquipItemModel->getModelData();
    f32 frame = mSwordAnim.getFrameCtrl()->getFrame();
    mSwordAnim.entry(modelData, frame);
    mDoAud_seStart(JA_SE_OBJ_OMAMORI, pcVar1, 0, mReverb);
    if (mDemo.getParam0() != 0) {
        onModeFlg(ModeFlg_00000080);
    } else {
        offModeFlg(ModeFlg_00000080);
    }
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 8012FFEC-801300F4       .text dProcSurprised_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSurprised_init() {
    if (mCurProc == daPyProc_DEMO_SURPRISED_e) {
        return false;
    }
    int iVar3 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_SURPRISED_e);
    setSingleMoveAnime(ANM_SURPRISED, 1.0f, 0.0f, -1, 3.0f);
    mVelocity = 0.0f;
    mProcVar0.m3570 = 0;
    if (mDemo.getParam0() == 1) {
        voiceStart(28);
    } else if (mDemo.getParam0() == 2) {
        voiceStart(45);
    } else if (mDemo.getParam0() == 3) {
        voiceStart(49);
    }
    initShipRideUseItem(iVar3, 1);
    return true;
}

/* 801300F4-801301C0       .text dProcSurprised__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSurprised() {
    u16 uVar1;
    u16 uVar2;

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
    }
    if ((mProcVar0.m3570 != 0) || (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f)) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
        if (mProcVar0.m3570 == 0) {
            uVar1 = m3530;
            uVar2 = m3532;
            mProcVar0.m3570 = 1;
            setSingleMoveAnime(ANM_SURPRISEDWAIT, 1.0f, 0.0f, -1, 3.0f);
            m3530 = uVar1;
            m3532 = uVar2;
            offModeFlg(ModeFlg_00000400);
        }
    }
    return true;
}

/* 801301C0-80130278       .text dProcTurnBack_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTurnBack_init() {
    if (mCurProc == daPyProc_DEMO_TURN_BACK_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_TURN_BACK_e);
    mVelocity = 0.0f;
    if (mActorKeepGrab.getActor() != NULL) {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        mProcVar0.m3570 = 1;
    } else {
        setSingleMoveAnime(
            ANM_TURNBACK,
            daPy_HIO_holdup_c0::m.field_0x4C,
            daPy_HIO_holdup_c0::m.field_0x50,
            daPy_HIO_holdup_c0::m.field_0xA,
            daPy_HIO_holdup_c0::m.field_0x54
        );
        mProcVar0.m3570 = 0;
    }
    return true;
}

/* 80130278-801302CC       .text dProcTurnBack__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcTurnBack() {
    if ((mProcVar0.m3570 != 0) || (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f)) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 801302CC-80130338       .text dProcLookUp_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookUp_init() {
    if (mCurProc == daPyProc_DEMO_LOOK_UP_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_LOOK_UP_e);
    setSingleMoveAnime(ANM_LOOKUP, 1.0f, 0.0f, -1, 5.0f);
    mVelocity = 0.0f;
    return true;
}

/* 80130338-80130380       .text dProcLookUp__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookUp() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 80130380-801303FC       .text dProcQuakeWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcQuakeWait_init() {
    if (mCurProc == daPyProc_DEMO_QUAKE_WAIT_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_QUAKE_WAIT_e);
    setSingleMoveAnime(ANM_WAITQ, 1.0f, 0.0f, -1, 5.0f);
    setTextureAnime(104, 0);
    mVelocity = 0.0f;
    return true;
}

/* 801303FC-80130434       .text dProcQuakeWait__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcQuakeWait() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80130434-801304A0       .text dProcDance_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDance_init() {
    if (mCurProc == daPyProc_DEMO_DANCE_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_DANCE_e);
    setSingleMoveAnime(ANM_GLAD, 1.0f, 0.0f, -1, 5.0f);
    mVelocity = 0.0f;
    return true;
}

/* 801304A0-801304D8       .text dProcDance__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDance() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 801304D8-80130570       .text dProcCaught_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcCaught_init() {
    daPy_ANM dVar2;

    if (mCurProc == daPyProc_DEMO_CAUGHT_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_CAUGHT_e);
    if (mDemo.getParam0() == 0) {
        dVar2 = ANM_MOGAKU1;
        mProcVar0.m3570 = 1;
    } else {
        dVar2 = ANM_FM_BATA;
        mProcVar0.m3570 = 0;
    }
    setSingleMoveAnime(dVar2, 1.0f, 0.0f, -1, 3.0f);
    speed.y = gravity = mVelocity = 0.0f;
    return true;
}

/* 80130570-801305A8       .text dProcCaught__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcCaught() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 801305A8-8013065C       .text dProcLookWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookWait_init() {
    int iVar1 = checkShipRideUseItem(0);
    if (mCurProc == daPyProc_DEMO_LOOK_WAIT_e) {
        return false;
    }
    if (mCurProc == daPyProc_GRAB_WAIT_e) {
        m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
    }
    commonProcInit(daPyProc_DEMO_LOOK_WAIT_e);
    mVelocity = 0.0f;
    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    current.angle.y = shape_angle.y;
    mDirection = DIR_NONE;
    initShipRideUseItem(iVar1, 0);
    return true;
}

/* 8013065C-80130724       .text dProcLookWait__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookWait() {
    fopAc_ac_c* look_actor_p = getDemoLookActor();

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    if (look_actor_p != NULL) {
        s16 target_angle;
        s16 sVar1 = cLib_targetAngleY(&current.pos, &look_actor_p->eyePos) - shape_angle.y;
        if (sVar1 > 0x6000) {
            target_angle = shape_angle.y + 0x6000;
        } else if (sVar1 < -0x6000) {
            target_angle = shape_angle.y + -0x6000;
        } else {
            target_angle = shape_angle.y;
        }
        cLib_addCalcAngleS(&shape_angle.y, target_angle, 2, 0x800, 0x100);
    }
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80130724-801307AC       .text dProcPushPullWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPushPullWait_init() {
    if (mCurProc == daPyProc_DEMO_PUSH_PULL_WAIT_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_PUSH_PULL_WAIT_e);
    setSingleMoveAnime(
        ANM_WAITPUSHPULL, daPy_HIO_pushpull_c0::m.field_0x0, 0.0f, -1, daPy_HIO_pushpull_c0::m.field_0x4
    );
    mVelocity = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK4000000_e);
    return true;
}

/* 801307AC-801307E4       .text dProcPushPullWait__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPushPullWait() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 801307E4-80130884       .text dProcPushMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPushMove_init() {
    if (mCurProc == daPyProc_DEMO_PUSH_MOVE_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_PUSH_MOVE_e);
    setSingleMoveAnime(ANM_WALKPUSH, daPy_HIO_pushpull_c0::m.field_0x8, 0.0f, -1, daPy_HIO_pushpull_c0::m.field_0xC);
    mVelocity = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK4000000_e);
    voiceStart(19);
    return true;
}

/* 80130884-801308BC       .text dProcPushMove__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPushMove() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 801308BC-8013098C       .text dProcDoorOpen_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDoorOpen_init() {
    float fVar1;
    daPy_ANM dVar2;

    if (mCurProc == daPyProc_DEMO_DOOR_OPEN_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_DOOR_OPEN_e);
    if ((mDemo.getParam0() & 1) != 0) {
        dVar2 = ANM_DOOROPENBLINK;
    } else {
        dVar2 = ANM_DOOROPENALINK;
    }
    if ((mDemo.getParam0() & 2) != 0) {
        fVar1 = 35.0f;
    } else {
        fVar1 = 0.0f;
    }
    setSingleMoveAnime(dVar2, 1.0f, fVar1, -1, 0.0f);
    mVelocity = 0.0f;
    mAcch.SetWallNone();
    mAcch.OnLineCheckNone();
    m3700 = cXyz::Zero;
    m34C2 = 3;
    mProcVar0.m3570 = 0;
    return true;
}

/* 8013098C-80130A54       .text dProcDoorOpen__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcDoorOpen() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        mAcch.ClrWallNone();
        mAcch.OffLineCheckNone();
        dComIfGp_evmng_cutEnd(mStaffIdx);
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        mProcVar0.m3570 = 1;
        m3598 = 0.0f;
    } else {
        if (mProcVar0.m3570 == 0) {
            if (m34C2 != 3) {
                m34C2 = 1;
            }
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        }
    }
    return true;
}

/* 80130A54-80130ADC       .text dProcNod_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcNod_init() {
    if (mCurProc == daPyProc_DEMO_NOD_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_NOD_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(
        ANM_SEYYES,
        daPy_HIO_turn_c0::m.field_0x1C,
        daPy_HIO_turn_c0::m.field_0x20,
        daPy_HIO_turn_c0::m.field_0xC,
        daPy_HIO_turn_c0::m.field_0x24
    );
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK10_e);
    return true;
}

/* 80130ADC-80130B38       .text dProcNod__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcNod() {
    setShapeAngleToTalkActor();
    current.angle.y = shape_angle.y;
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 80130B38-80130BE8       .text dProcPresent_init_sub__9daPy_lk_cFv */
void daPy_lk_c::dProcPresent_init_sub() {
    setSingleMoveAnime(
        ANM_PRESENTATIONA,
        daPy_HIO_turn_c0::m.field_0x28,
        daPy_HIO_turn_c0::m.field_0x2C,
        daPy_HIO_turn_c0::m.field_0xE,
        daPy_HIO_turn_c0::m.field_0x30
    );
    onModeFlg(ModeFlg_00000400);
    if (!checkBottleItem(dComIfGp_event_getPreItemNo())) {
        dComIfGp_event_setItemPartnerId(fopAcM_createItemForPresentDemo(
            &current.pos, dComIfGp_event_getPreItemNo(), 3, -1, fopAcM_GetRoomNo(this), &shape_angle, &scale
        ));
    }
    keepItemData();
}

/* 80130BE8-80130CA0       .text dProcPresent_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPresent_init() {
    if (mCurProc == daPyProc_DEMO_PRESENT_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_PRESENT_e);
    mProcVar0.m3570 = setTalkStartBack();
    if (mProcVar0.m3570 == 0) {
        mVelocity = 0.0f;
        dProcPresent_init_sub();
    }
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK10_e);
    mDoAud_seStart(JA_SE_TALK_START);
    m3574 = 0;
    return true;
}

/* 80130CA0-80130E88       .text dProcPresent__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPresent() {
    setShapeAngleToTalkActor();
    if (mProcVar0.m3570 != 0) {
        cXyz local_28 = m370C - current.pos;
        if ((0x4000 < cLib_distanceAngleS(cM_atan2s(local_28.x, local_28.z), current.angle.y)) || mAcch.ChkWallHit()) {
            current.pos.x = m370C.x;
            current.pos.z = m370C.z;
            mProcVar0.m3570 = 0;
            dProcPresent_init_sub();
            mVelocity = 0.0f;
        }
    } else {
        current.angle.y = shape_angle.y;
        if (m3574 != 0) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            m3574 = 1;
            setSingleMoveAnime(ANM_PRESENTATIONAWAIT, 1.0f, 0.0f, -1, 3.0f);
            onModeFlg(ModeFlg_00000080 | ModeFlg_00000100);
            offModeFlg(ModeFlg_00000400);
        } else if (mFrameCtrlUnder[UNDER_MOVE0_e].checkPass(daPy_HIO_turn_c0::m.field_0xE - 10.0f)) {
            if (checkBottleItem(dComIfGp_event_getPreItemNo())) {
                if (mEquipItem == daPyItem_NONE_e) {
                    setBottleModel(dComIfGp_event_getPreItemNo());
                }
            } else {
                daItemBase_c* item = (daItemBase_c*)fopAcM_getItemEventPartner(this);
                if ((item != NULL) && (fopAcM_GetName(item) == PROC_ITEM || fopAcM_GetName(item) == PROC_Demo_Item)) {
                    item->show();
                }
            }
        }
    }
    return true;
}

/* 80130E88-80130F2C       .text dProcWindChange_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcWindChange_init() {
    daPy_ANM dVar4;

    int iVar1 = checkShipRideUseItem(0);
    if (mCurProc == daPyProc_DEMO_WIND_CHANGE_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_WIND_CHANGE_e);
    mVelocity = 0.0f;
    if (dKyw_get_tactwind_dir()) {
        dVar4 = ANM_WINDL;
    } else {
        dVar4 = ANM_WINDR;
    }
    setSingleMoveAnime(dVar4, 1.0f, 0.0f, -1, 5.0f);
    initShipRideUseItem(iVar1, 0);
    return true;
}

/* 80130F2C-80130F98       .text dProcWindChange__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcWindChange() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 80130F98-8013116C       .text dProcStandItemPut_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcStandItemPut_init() {
    daPy_py_c* pdVar1;
    fopAc_ac_c* pfVar2;
    f32 dVar5;
    double in_f4;
    csXyz* angle;

    if (mCurProc == daPyProc_DEMO_STAND_ITEM_PUT_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_STAND_ITEM_PUT_e);
    mVelocity = 0.0f;
    keepItemData();
    mProcVar0.m3570 = 0;
    pdVar1 = (daPy_py_c*)fopAcM_getEventPartner(this);
    if (pdVar1 != NULL) {
        cXyz local_20 = pdVar1->current.pos - current.pos;
        angle = fopAcM_GetShapeAngle_p(this);
        angle->y = fopAcM_searchActorAngleY(this, pdVar1);
        dVar5 = local_20.absXZ();
        if (0.0f < dVar5) {
            in_f4 = 0.5;
        }
        m35C8 = dVar5 - 47.0f;
        angle = fopAcM_GetShapeAngle_p(pdVar1);
    } else {
        m35C8 = 15.0f;
        angle = fopAcM_GetShapeAngle_p(this);
    }
    mProcVar0.m3570 = 1;
    setSingleMoveAnime(ANM_GRABWAIT, daPy_HIO_grab_c0::m.field_0x78, 0.0f, -1, -1.0f);
    pfVar2 = (fopAc_ac_c*)fopAcM_fastCreate(PROC_STANDITEM, dComIfGp_event_getPreItemNo(), &current.pos, -1, angle);
    if (pfVar2 != NULL) {
        mActorKeepGrab.setData(pfVar2);
        fopAcM_setCarryNow(pfVar2, FALSE);
    }
    return true;
}

/* 8013116C-80131274       .text dProcStandItemPut__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcStandItemPut() {
    if (mProcVar0.m3570 == 1) {
        if (m_old_fdata->getOldFrameRate() < 0.01f) {
            setSingleMoveAnime(
                ANM_GRABUP,
                daPy_HIO_grab_c0::m.field_0x68,
                daPy_HIO_grab_c0::m.field_0x6C,
                daPy_HIO_grab_c0::m.field_0xC,
                daPy_HIO_grab_c0::m.field_0x74
            );
            mProcVar0.m3570 = 2;
            voiceStart(7);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > -0.01f) {
        fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
        if (grab_actor != NULL) {
            mDoAud_seStart(
                JA_SE_LK_W_DAIZA_ATTACH, &grab_actor->current.pos, NULL, dComIfGp_getReverb(grab_actor->current.roomNo)
            );
        }
        freeGrabItem();
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 80131274-80131310       .text dProcVorcanoFail_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcVorcanoFail_init() {
    if (mCurProc == daPyProc_DEMO_VORCANO_FAIL_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_VORCANO_FAIL_e);
    mVelocity = 0.0f;
    speed.y = 18.0f;
    gravity = 0.0f;
    setSingleMoveAnime(ANM_LAVADAM, daPy_HIO_restart_c0::m.field_0x0, 0.0f, -1, daPy_HIO_restart_c0::m.field_0x4);
    m32E4.makeEmitter(dPa_name::ID_SCENE_8078, mpCLModel->getAnmMtx(0), &current.pos, NULL);
    return true;
}

/* 80131310-80131348       .text dProcVorcanoFail__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcVorcanoFail() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80131348-80131450       .text dProcSlightSurprised_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSlightSurprised_init() {
    if (mCurProc == daPyProc_DEMO_SLIGHT_SURPRISED_e) {
        return false;
    }
    int iVar3 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_SLIGHT_SURPRISED_e);
    setSingleMoveAnime(ANM_SURPRISEDB, 1.0f, 0.0f, -1, 5.0f);
    mVelocity = 0.0f;
    mProcVar0.m3570 = 0;
    if (mDemo.getParam0() == 1) {
        voiceStart(28);
    } else if (mDemo.getParam0() == 2) {
        voiceStart(45);
    } else if (mDemo.getParam0() == 3) {
        voiceStart(49);
    }
    initShipRideUseItem(iVar3, 0);
    return true;
}

/* 80131450-8013154C       .text dProcSlightSurprised__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSlightSurprised() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    if ((mProcVar0.m3570 != 0) || (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f)) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
        if (mProcVar0.m3570 == 0) {
            mProcVar0.m3570 = 1;
            setSingleMoveAnime(ANM_SURPRISEDWAIT, 1.0f, 0.0f, -1, 3.0f);
            if (mpAnmTexPatternData->getFrameMax() == 0) {
                m3530 = 0;
            } else {
                m3530 = mpAnmTexPatternData->getFrameMax() - 1;
            }
            if (mpTexScrollResData->getFrameMax() == 0) {
                m3532 = 0;
            } else {
                m3532 = mpTexScrollResData->getFrameMax() - 1;
            }
            offModeFlg(ModeFlg_00000400);
        }
    }
    return true;
}

/* 8013154C-801315F8       .text dProcSmile_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSmile_init() {
    if (mCurProc == daPyProc_DEMO_SMILE_e) {
        return false;
    }
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_SMILE_e);
    setSingleMoveAnime(ANM_WAITS, 1.0f, 0.0f, -1, 5.0f);
    setTextureAnime(143, 0);
    mVelocity = 0.0f;
    mProcVar0.m3570 = 0;
    initShipRideUseItem(iVar2, 1);
    return true;
}

/* 801315F8-8013168C       .text dProcSmile__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSmile() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
    }
    m3530++;
    if (m3530 >= mpAnmTexPatternData->getFrameMax()) {
        if (mProcVar0.m3570 == 0) {
            mProcVar0.m3570 = 1;
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        }
    }
    return true;
}

/* 8013168C-80131780       .text dProcBossWarp_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcBossWarp_init() {
    if (mCurProc == daPyProc_DEMO_BOSS_WARP_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_BOSS_WARP_e);
    if (mDemo.getParam0() == 0) {
        setSingleMoveAnime(ANM_WARPOUTFIRST, 1.0f, 0.0f, -1, 3.0f);
        mProcVar0.m3570 = 1;
        deleteEquipItem(FALSE);
    } else {
        setSingleMoveAnime(ANM_WARPIN, 1.0f, 0.0f, -1, -1.0f);
        mProcVar0.m3570 = 0;
    }
    mVelocity = 0.0f;
    if (mDemo.getParam0() == 2) {
        initShipRideUseItem(2, 1);
        m353E = m353C = 0;
    }
    if (mEquipItem == daPyItem_BOKO_e) {
        deleteEquipItem(FALSE);
    }
    return true;
}

/* 80131780-8013182C       .text dProcBossWarp__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcBossWarp() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
        m353E = m353C = 0;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (mProcVar0.m3570 == 0) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else {
            mProcVar0.m3570 = 0;
            setSingleMoveAnime(ANM_WARPOUT, 1.0f, 0.0f, -1, 10.0f);
        }
    }
    return true;
}

/* 8013182C-80131908       .text dProcAgbUse_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcAgbUse_init() {
    if (mCurProc == daPyProc_DEMO_AGB_USE_e) {
        return true;
    }
    int iVar2 = checkShipRideUseItem(1);
    mProcVar0.m3570 = 0;
    commonProcInit(daPyProc_DEMO_AGB_USE_e);
    keepItemData();
    setAnimeEquipItem();
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_USETCEIVER, 1.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);
    mDoAud_seStart(JA_SE_TALK_START);
    initShipRideUseItem(iVar2, 2);
    return true;
}

/* 80131908-8013194C       .text dProcAgbUse__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcAgbUse() {
    setShipRidePosUseItem();
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 8013194C-801319D0       .text dProcLookTurn_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookTurn_init() {
    daPy_ANM dVar2;

    if (mCurProc == daPyProc_DEMO_LOOK_TURN_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_LOOK_TURN_e);
    mVelocity = 0.0f;
    if (mDemo.getParam0() != 0) {
        dVar2 = ANM_WINDL;
    } else {
        dVar2 = ANM_WINDR;
    }
    setSingleMoveAnime(dVar2, 1.0f, 0.0f, -1, 5.0f);
    mProcVar0.m3570 = 0;
    return true;
}

/* 801319D0-80131A7C       .text dProcLookTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLookTurn() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        setBlendMoveAnime(5.0f);
        shape_angle.y -= -0x8000;
        current.angle.y = shape_angle.y;
        setOldRootQuaternion(0, -0x8000, 0);
        mProcVar0.m3570 = 1;
    }
    if ((mProcVar0.m3570 != 0) && (m_old_fdata->getOldFrameRate() < 0.01f)) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 80131A7C-80131B18       .text dProcLetterOpen_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLetterOpen_init() {
    if (mCurProc == daPyProc_DEMO_LETTER_OPEN_e) {
        return true;
    }
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_LETTER_OPEN_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_GETLETTER, 1.0f, 0.0f, -1, 3.0f);
    deleteEquipItem(FALSE);
    initShipRideUseItem(iVar2, 2);
    return true;
}

/* 80131B18-80131B98       .text dProcLetterOpen__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLetterOpen() {
    setShipRidePosUseItem();
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (m_old_fdata->getOldFrameRate() < 0.01f) {
        setLetterModel();
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        setLetterModel();
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 80131B98-80131C54       .text dProcLetterRead_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLetterRead_init() {
    f32 dVar3;

    if (mCurProc == daPyProc_DEMO_LETTER_READ_e) {
        return true;
    }
    dVar3 = m35EC;
    int iVar2 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_DEMO_LETTER_READ_e);
    m35EC = dVar3;
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_WAITLETTER, 1.0f, 0.0f, -1, 5.0f);
    offNoResetFlg1(daPyFlg1_LETTER_READ_EYE_MOVE);
    m34D0 = 0;
    initShipRideUseItem(iVar2, 2);
    return true;
}

/* 80131C54-80131D6C       .text dProcLetterRead__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLetterRead() {
    setShipRidePosUseItem();
    if (checkNoResetFlg1(daPyFlg1_LETTER_READ_EYE_MOVE)) {
        offNoResetFlg1(daPyFlg1_LETTER_READ_EYE_MOVE);
        m_tex_scroll_heap.mIdx = LKANM_BTK_TEDL;
        setTextureScrollResource(loadTextureScrollResource(LKANM_BTK_TEDL, 0), 0);
        m34D0 = 4;
    } else {
        if (0 < m34D0) {
            m34D0--;
            if (m34D0 == 0) {
                if (m_tex_scroll_heap.mIdx == LKANM_BTK_TEDL) {
                    m34D0 = 4;
                    m_tex_scroll_heap.mIdx = LKANM_BTK_TEDR;
                    setTextureScrollResource(loadTextureScrollResource(LKANM_BTK_TEDR, 0), 0);
                } else {
                    m_tex_scroll_heap.mIdx = LKANM_BTK_TEDW;
                    setTextureScrollResource(loadTextureScrollResource(LKANM_BTK_TEDW, 0), 0);
                }
            }
        }
    }
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80131D6C-80131DD4       .text dProcRedeadStop_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcRedeadStop_init() {
    if (mCurProc == daPyProc_DEMO_REDEAD_STOP_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_REDEAD_STOP_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_LINK_FREEZ, 1.0f, 0.0f, -1, 5.0f);
    return true;
}

/* 80131DD4-80131E0C       .text dProcRedeadStop__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcRedeadStop() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80131E0C-80131E74       .text dProcRedeadCatch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcRedeadCatch_init() {
    if (mCurProc == daPyProc_DEMO_REDEAD_CATCH_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_REDEAD_CATCH_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_LINK_MOGAKI, 1.0f, 0.0f, -1, 5.0f);
    return true;
}

/* 80131E74-80131EAC       .text dProcRedeadCatch__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcRedeadCatch() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80131EAC-80131FB0       .text dProcGetDance_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcGetDance_init() {
    if (mCurProc == daPyProc_DEMO_GET_DANCE_e) {
        return true;
    }
    int iVar2 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_DEMO_GET_DANCE_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_TAKTDGE, 1.0f, 0.0f, -1, 3.0f);
    m34D4 = 0;
    camera_class* cam = dComIfGp_getCamera(mCameraInfoIdx);
    m34D6 = shape_angle.y - fopCamM_GetAngleY(cam);
    current.angle.y = shape_angle.y;
    m3628 = fpcM_ERROR_PROCESS_ID_e;
    m34D0 = 0;
    mProcVar0.m3570 = mDemo.getParam0() + 0xd2;
    dComIfGs_onTact(mDemo.getParam0());
    initShipRideUseItem(iVar2, 0);
    dKy_Itemgetcol_chg_on();
    setTactModel();
    m3574 = 0;
    return true;
}

/* 80131FB0-80132224       .text dProcGetDance__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcGetDance() {
    J3DTransformInfo* pJVar3;

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    if (m3574 != 0) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
        return true;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= 11.0f && mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() <= 17.0f) {
        if (m34D0 == 0) {
            m34D0 = 1;
            mDoAud_subBgmStart(JA_BGM_GET_SONG);
            dComIfGp_setMesgBgmOn();
        }
        if (m34D6 > 0x4000) {
            shape_angle.y =
                current.angle.y + ((0x10000 - m34D6) * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - 10.0f) / 7.0f);
        } else {
            shape_angle.y = current.angle.y - (m34D6 * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - 10.0f) / 7.0f);
        }
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > 17.0f) {
            shape_angle.y = current.angle.y - m34D6;
        }
    }
    fopAcM_getItemEventPartner(this);
    if ((mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) && (checkEndMessage(mProcVar0.m3570))) {
        shape_angle.y += 0x8000;
        current.angle.y = shape_angle.y;
        m34DE = shape_angle.y;
        setOldRootQuaternion(0, -0x8000, 0);
        pJVar3 = m_old_fdata->getOldFrameTransInfo(0);
        pJVar3->mTranslate.x *= -1.0f;
        pJVar3->mTranslate.z *= -1.0f;
        dComIfGp_evmng_cutEnd(mStaffIdx);
        m3574 = 1;
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    }
    return true;
}

/* 80132224-801322D0       .text dProcBottleOpenFairy_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcBottleOpenFairy_init() {
    if (mCurProc == daPyProc_DEMO_BOTTLE_OPEN_FAIRY_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_BOTTLE_OPEN_FAIRY_e);
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
    setBottleModel(dItem_FAIRY_BOTTLE_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK4000_e);
    mProcVar0.m3570 = 0;
    return true;
}

/* 801322D0-80132438       .text dProcBottleOpenFairy__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcBottleOpenFairy() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_BINOPENPRE) {
        if (frameCtrl.getRate() < 0.01f) {
            setSingleMoveAnime(
                ANM_BINOPENB,
                1.0f,
                daPy_HIO_bottle_c0::m.field_0x50,
                daPy_HIO_bottle_c0::m.field_0xA,
                daPy_HIO_bottle_c0::m.field_0x54
            );
        } else {
            if (frameCtrl.checkPass(32.0f)) {
                m355E = 0;
                mRightHandIdx = 8;
            }
        }
    } else if (frameCtrl.getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    } else {
        if (mpBottleContentsModel != NULL) {
            if (frameCtrl.getFrame() >= daPy_HIO_bottle_c0::m.field_0x58) {
                mpBottleContentsModel = NULL;
                if (dComIfGp_event_getTalkXYBtn() == dTalkBtn_X_e) {
                    dComIfGs_setEquipBottleItemEmpty(dItemBtn_X_e);
                } else if (dComIfGp_event_getTalkXYBtn() == dTalkBtn_Y_e) {
                    dComIfGs_setEquipBottleItemEmpty(dItemBtn_Y_e);
                } else {
                    dComIfGs_setEquipBottleItemEmpty(dItemBtn_Z_e);
                }
                fopAcM_fastCreate(PROC_NPC_FA1, 3, &mLeftHandPos, fopAcM_GetRoomNo(this), &shape_angle);
            }
        }
    }
    return true;
}

/* 80132438-801324D0       .text dProcWarpShort_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcWarpShort_init() {
    if (mCurProc == daPyProc_DEMO_WARP_SHORT_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_WARP_SHORT_e);
    setSingleMoveAnime(ANM_RISE, 1.0f, 0.0f, -1, 40.0f);
    gravity = mVelocity = 0.0f;
    speed.y = daPy_HIO_warp_c0::m.field_0x10;
    if (mEquipItem == daPyItem_BOKO_e) {
        deleteEquipItem(FALSE);
    }
    return true;
}

/* 801324D0-80132534       .text dProcWarpShort__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcWarpShort() {
    speed.y += daPy_HIO_warp_c0::m.field_0x14;
    if (speed.y > daPy_HIO_warp_c0::m.field_0x18) {
        speed.y = daPy_HIO_warp_c0::m.field_0x18;
    }
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80132534-801325F0       .text dProcOpenSalvageTreasure_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcOpenSalvageTreasure_init() {
    if (mCurProc == daPyProc_DEMO_OPEN_SALVAGE_TREASURE_e) {
        return true;
    }
    int iVar1 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_OPEN_SALVAGE_TREASURE_e);
    setSingleMoveAnime(ANM_BOXOPENSLINK, 1.0f, 0.0f, -1, -1.0f);
    deleteEquipItem(FALSE);
    initShipRideUseItem(iVar1, 1);
    if (dComIfGp_getShipActor() != NULL) {
        shape_angle.y = dComIfGp_getShipActor()->shape_angle.y;
        current.angle.y = shape_angle.y;
    }
    return true;
}

/* 801325F0-8013265C       .text dProcOpenSalvageTreasure__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcOpenSalvageTreasure() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}

/* 8013265C-80132728       .text dProcSurprisedWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSurprisedWait_init() {
    if (mCurProc == daPyProc_DEMO_SURPRISED_WAIT_e) {
        return false;
    }
    commonProcInit(daPyProc_DEMO_SURPRISED_WAIT_e);
    int iVar3 = checkShipRideUseItem(0);
    setSingleMoveAnime(ANM_SURPRISEDWAIT, 1.0f, 0.0f, -1, 3.0f);
    if (mpAnmTexPatternData->getFrameMax() >= 1) {
        m3530 = mpAnmTexPatternData->getFrameMax() - 1;
    }
    if (mpTexScrollResData->getFrameMax() >= 1) {
        m3532 = mpTexScrollResData->getFrameMax() - 1;
    }
    mVelocity = 0.0f;
    initShipRideUseItem(iVar3, 0);
    return true;
}

/* 80132728-80132784       .text dProcSurprisedWait__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcSurprisedWait() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(0);
    }
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80132784-80132844       .text dProcPowerUpWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPowerUpWait_init() {
    if (mCurProc == daPyProc_DEMO_POWER_UP_WAIT_e) {
        return true;
    }
    int iVar1 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_POWER_UP_WAIT_e);
    setSingleMoveAnime(ANM_POWUPWAIT, 1.0f, 0.0f, -1, 3.0f);
    mVelocity = 0.0f;
    initShipRideUseItem(iVar1, 2);
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        shape_angle.y -= -0x8000;
        current.angle.y = shape_angle.y;
    }
    return true;
}

/* 80132844-8013294C       .text dProcPowerUp_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPowerUp_init() {
    if (mCurProc == daPyProc_DEMO_POWER_UP_e) {
        return true;
    }
    int iVar2 = checkShipRideUseItem(1);
    commonProcInit(daPyProc_DEMO_POWER_UP_e);
    setSingleMoveAnime(ANM_POWUP, 1.0f, 0.0f, -1, 3.0f);
    mVelocity = 0.0f;
    m3624 = 0;
    m34D0 = 0;
    if (mDemo.getParam0() != 0) {
        if (mDemo.getParam0() != 0x100) {
            mProcVar0.m3570 = mDemo.getParam0();
        } else {
            mProcVar0.m3570 = dComIfGp_event_getGtItm();
        }
    }
    m3574 = 0;
    m3628 = fpcM_ERROR_PROCESS_ID_e;
    initShipRideUseItem(iVar2, 2);
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        shape_angle.y -= -0x8000;
        current.angle.y = shape_angle.y;
    }
    return true;
}

/* 8013294C-80132A88       .text dProcPowerUp__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcPowerUp() {
    setShipRidePosUseItem();
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        shape_angle.y -= -0x8000;
        current.angle.y = shape_angle.y;
    }
    if (m3574 != 0) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
        return true;
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= 11.0f && m34D0 == 0) {
        m34D0 = 1;
        mDoAud_subBgmStart(JA_BGM_ITEM_GET);
        dComIfGp_setMesgBgmOn();
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (m3624 == 0) {
            m3624 = MSG_NO_FOR_ITEM(mProcVar0.m3570);
        }
        if (checkEndMessage(m3624)) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
            m3574 = 1;
        }
    }
    return true;
}

/* 80132A88-80132B68       .text dProcShipSit_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcShipSit_init() {
    if (mCurProc == daPyProc_DEMO_SHIP_SIT_e) {
        return true;
    }
    int iVar1 = checkShipRideUseItem(1);
    if (iVar1 == 0) {
        if (!dComIfGp_getShipActor()) {
            return checkNextMode(0);
        }
        iVar1 = 1;
    }
    commonProcInit(daPyProc_DEMO_SHIP_SIT_e);
    setSingleMoveAnime(ANM_KOSHIKAKE, 1.0f, 0.0f, -1, -1.0f);
    mVelocity = 0.0f;
    initShipRideUseItem(iVar1, 1);
    daShip_c* ship = dComIfGp_getShipActor();
    ship->onLinkSit();
    ship->setPaddleMove();
    return true;
}

/* 80132B68-80132BC4       .text dProcShipSit__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcShipSit() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
    }
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80132BC4-80132D00       .text dProcLastCombo_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLastCombo_init() {
    J3DAnmTransform* bck;

    if (mCurProc == daPyProc_DEMO_LAST_COMBO_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_LAST_COMBO_e);
    setSingleMoveAnime(ANM_COMBO_LINK, 1.0f, 0.0f, -1, -1.0f);
    mVelocity = 0.0f;
    if (mEquipItem != daPyItem_SWORD_e) {
        deleteEquipItem(FALSE);
        setSwordModel(FALSE);
    }
    bck = getItemAnimeResource(LKANM_BCK_COMBO_KEN);
    mSwordAnim.changeBckOnly(bck);
    m35E8 = m35EC = 0.0f;
    bck = (J3DAnmTransform*)(dComIfG_getObjectRes(l_arcName, LINK_BCK_COMBO_TATE));
    mAtngshaBck.init(mpShmsModel->getModelData(), bck, false, J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, true);
    m34BE = 4;
    offNoResetFlg1(daPyFlg1_LAST_COMBO_WAIT);
    setBlurPosResource(LKANM__LASTCOMBO_POS);
    mProcVar0.m3570 = 1;
    m3574 = 0;
    seStartOnlyReverb(JA_SE_LK_V_TURN_INTO_GN);
    return true;
}

/* 80132D00-80132DDC       .text dProcLastCombo__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcLastCombo() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    m35EC = frameCtrl.getFrame();
    m35E8 = frameCtrl.getFrame();
    if (frameCtrl.getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    } else {
        if (frameCtrl.checkPass(27.0f)) {
            resetFootEffect();
            seStartOnlyReverb(JA_SE_LK_V_GN_LAST_ATTACK);
        }
    }
    if (frameCtrl.getFrame() >= 26.0f) {
        if (frameCtrl.getFrame() < 35.0f) {
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
                onResetFlg0(daPyRFlg0_UNK1);
            }
            onResetFlg0(daPyRFlg0_UNK2);
        }
    }
    return true;
}

/* 80132DDC-80132E48       .text dProcHandUp_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcHandUp_init() {
    if (mCurProc == daPyProc_DEMO_HAND_UP_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_HAND_UP_e);
    setSingleMoveAnime(ANM_WAITAUCTION, 1.0f, 0.0f, -1, 10.0f);
    mVelocity = 0.0f;
    return true;
}

/* 80132E48-80132E80       .text dProcHandUp__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcHandUp() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return true;
}

/* 80132E80-80132EEC       .text dProcIceSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcIceSlip_init() {
    if (mCurProc == daPyProc_DEMO_ICE_SLIP_e) {
        return true;
    }
    commonProcInit(daPyProc_DEMO_ICE_SLIP_e);
    setSingleMoveAnime(ANM_SLIPICE, 1.0f, 0.0f, -1, 3.0f);
    mVelocity = 0.0f;
    return true;
}

/* 80132EEC-80132F34       .text dProcIceSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::dProcIceSlip() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return true;
}
