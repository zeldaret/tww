/**
 * d_a_obj_toripost.cpp
 * Object - Rito Postbox
 */

#include "d/actor/d_a_obj_toripost.h"
#include "d/res/res_toripost.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_letter.h"
#include "d/d_item_data.h"
#include "d/d_s_play.h"
#include "d/d_a_obj.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

#include "weak_data_1811.h" // IWYU pragma: keep

extern dScnPly_reg_HIO_c g_regHIO;

const char daObjTpost_c::m_arc_name[] = "Toripost";

const daObjTpost_c__letter_data daObjTpost_c::m_letter[] = {
    {false, 0x1AAF, dItem_HEART_PIECE_e,    dSv_evtBit_c::LETTER_BAITOS_MOM},
    {false, 0x0CF9, dItem_HEART_PIECE_e,    dSv_evtBit_c::LETTER_KOMALIS_FATHER},
    {false, 0x0CFA, dItem_COLLECT_MAP_60_e, dSv_evtBit_c::LETTER_BOMBS_AD},
    {false, 0x0CFC, dItem_RED_RUPEE_e,      dSv_evtBit_c::LETTER_ORCA},
    {false, 0x0805, dItem_RED_RUPEE_e,      dSv_evtBit_c::LETTER_GRANDMA},
    {false, 0x0CFD, dItem_GREEN_RUPEE_e,    dSv_evtBit_c::LETTER_ROCK_SPIRE_SHOP_AD},
    {true,  0x0DB6, dItem_COLLECT_MAP_52_e, dSv_evtBit_c::LETTER_TINGLE},
    {false, 0x1148, dItem_RED_RUPEE_e,      dSv_evtBit_c::LETTER_ARYLL},
    {false, 0x1AAF, dItem_HEART_PIECE_e,    dSv_evtBit_c::LETTER_BAITOS_MOM},
    {true,  0x0F76, KAISEN_PRESENT1,        dSv_evtBit_c::LETTER_SILVER_MEMBERSHIP},
    {false, 0x19A6, KAKERA_HEART2,          dSv_evtBit_c::LETTER_HOSKITS_GIRLFRIEND},
    {true,  0x0CFB, dItem_RED_RUPEE_e,      dSv_evtBit_c::LETTER_BAITO},
    {true,  0x0F77, KAISEN_PRESENT2,        dSv_evtBit_c::LETTER_GOLD_MEMBERSHIP},
};

const dCcD_SrcCyl daObjTpost_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_BOOMERANG),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    },
};
const s32 daObjTpost_c::m_send_price[] = {
    0x05,
    0x0A,
    0x14
};

static daObjTpost_HIO_c l_HIO;

/* 000000EC-0000010C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daObjTpost_c*>(i_this)->_createHeap();
}

/* 0000010C-0000022C       .text _createHeap__12daObjTpost_cFv */
BOOL daObjTpost_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, TORIPOST_BDL_VPOST);
    JUT_ASSERT(132, modelData != NULL);

    mMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        NULL,
        -1, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x11000022
    );

    if(mMorf == NULL || mMorf->getModel() == NULL) {
        return FALSE;
    }
    else {
        mMorf->getModel()->setUserArea((u32)this);

        return TRUE;
    }
}

/* 0000022C-00000280       .text __ct__16daObjTpost_HIO_cFv */
daObjTpost_HIO_c::daObjTpost_HIO_c() {
    mNo = -1;
    debug_draw = false;
    field_0x06 = 0;
    field_0x07 = 0;
    attn_pos_offset = 140.0f;
    eye_pos_offset = 100.0f;
    talk_distance = 300.0f;
    field_0x14 = 30;
    field_0x16 = 30;
}

/* 00000280-000003D4       .text cutProc__12daObjTpost_cFv */
void daObjTpost_c::cutProc() {
    static char* action_table[3] = {
        "PRESENT",
        "SET_ANM",
        "DISP_LETTER"
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId("Tpost");
    if(staffIdx != -1) {
        int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, action_table, ARRAY_SIZE(action_table), TRUE, 0);
        if(actIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
        else {
            if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch(actIdx) {
                    case 0:
                        cutPresentStart(staffIdx);
                        break;
                    case 1:
                        cutSetAnmStart(staffIdx);
                        break;
                    case 2:
                        cutDispLetterStart(staffIdx);
                        break;
                }
            }
            
            switch(actIdx) {
                case 0:
                    cutPresentProc(staffIdx);
                    break;
                case 1:
                    cutSetAnmProc(staffIdx);
                    break;
                case 2:
                    cutDispLetterProc(staffIdx);
                    break;
            }
        }
    }
}

/* 000003D4-000003D8       .text cutPresentStart__12daObjTpost_cFi */
void daObjTpost_c::cutPresentStart(int staffIdx) {
    return;
}

/* 000003D8-00000474       .text cutPresentProc__12daObjTpost_cFi */
void daObjTpost_c::cutPresentProc(int staffIdx) {
    fpc_ProcID itemPID = fopAcM_createItemForPresentDemo(&current.pos, m_letter[mNumReadable].mItemNo);
    if(itemPID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemPID);
        dComIfGp_evmng_cutEnd(staffIdx);
    }
    else {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
}

/* 00000474-00000500       .text cutSetAnmStart__12daObjTpost_cFi */
void daObjTpost_c::cutSetAnmStart(int staffIdx) {
    const char* name = dComIfGp_evmng_getMyStringP(staffIdx, "Name");
    if(name != 0 && strcmp(name, "HAKIDASU") == 0) {
        setAnm(AnmPrm_POST_PUTOUT, false);
    }
    else {
        setAnm(AnmPrm_POST_GET0, false);
    }
}

/* 00000500-00000560       .text cutSetAnmProc__12daObjTpost_cFi */
void daObjTpost_c::cutSetAnmProc(int staffIdx) {
    if(mMorf->isStop()) {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
}

/* 00000560-00000580       .text cutDispLetterStart__12daObjTpost_cFi */
void daObjTpost_c::cutDispLetterStart(int staffIdx) {
    mCurrMsgNo = m_letter[mNumReadable].mMsgNo;
}

/* 00000580-000005F4       .text cutDispLetterProc__12daObjTpost_cFi */
void daObjTpost_c::cutDispLetterProc(int staffIdx) {
    u16 mode = talk(0);
    if(mode == 5) {
        daPy_getPlayerActorClass()->onLetterReadEyeMove();
    }
    if(mode == fopMsgStts_BOX_CLOSED_e) {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
}

/* 000005F4-00000650       .text deliverLetter__12daObjTpost_cFv */
void daObjTpost_c::deliverLetter() {
    switch(mPreItemNo) {
        case MAGYS_LETTER:
            dComIfGs_onEventBit(0x1220);
            break;
        case dItem_NOTE_TO_MOM_e:
            dLetter_send(dSv_evtBit_c::LETTER_BAITOS_MOM);
            break;
    }
}

/* 00000650-000006C0       .text getReceiveLetterNum__12daObjTpost_cFv */
s16 daObjTpost_c::getReceiveLetterNum() {
    s16 num = 0;
    for(int i = 1; i < (int)ARRAY_SIZE(m_letter); i++) {
        if(dLetter_isStock(m_letter[i].mEventReg)) {
            num = num + 1;
        }
    }

    return num;
}

/* 000006C0-00000750       .text getReadableLetterNum__12daObjTpost_cFv */
s32 daObjTpost_c::getReadableLetterNum() {
    s32 num = 0;
    s32 startIdx = mNumReadable != 0 ? mNumReadable : 1;
    s32 readable = mNumReadable;

    if(readable < (int)ARRAY_SIZE(m_letter)) {
        for(int i = startIdx; i < (int)ARRAY_SIZE(m_letter); i++) {
            if(!dLetter_isStock(m_letter[i].mEventReg)) {
                continue;
            }
            
            num = i;
            break;
        }
    }

    return num;
}

/* 00000750-000007B8       .text checkSendPrice__12daObjTpost_cFv */
u8 daObjTpost_c::checkSendPrice() {
    static const u8 pay_type[dIsleIdx_COUNT_e] = {
        02,
        01,
        01,
        00,
        00,
        00,
        00,
        02,
        01,
        01,
        00,
        00,
        00,
        00,
        02,
        01,
        01,
        00,
        00,
        00,
        00,
        02,
        01,
        01,
        00,
        00,
        00,
        00,
        02,
        01,
        01,
        01,
        01,
        01,
        01,
        02,
        01,
        01,
        01,
        01,
        01,
        01,
        02,
        02,
        02,
        02,
        02,
        02,
        02
    };

    if(strcmp(dComIfGp_getStartStageName(), "sea") != 0) {
        return 0;
    }
    else {
        return pay_type[fopAcM_GetRoomNo(this)];
    }
}

/* 000007B8-0000092C       .text getMsgXY__12daObjTpost_cFv */
int daObjTpost_c::getMsgXY() {
    s32 msgId;
    GXColor col = {0x00, 0x00, 0x00, 0x80};
    cXyz pos(REG12_F(0), REG12_F(1), REG12_F(2));
    cXyz scale(2.0f, 2.0f, 2.0f);

    switch(mPreItemNo) {
        case dItem_NOTE_TO_MOM_e:
        case MAGYS_LETTER:
            msgId = 0xCE8;
            col.r = REG12_S(0) + 0x80;
            col.g = REG12_S(1) + 0x80;
            col.b = REG12_S(2) + 0x80;
            mDoMtx_stack_c::copy(mMorf->getModel()->getAnmMtx(2));
            mDoMtx_stack_c::multVec(&pos, &pos);
            dComIfGp_particle_set(dPa_name::ID_COMMON_0057, &pos, &shape_angle, &scale, 0xFF, NULL, -1, &col);
            
            break;
        case dItem_FATHER_LETTER_e:
        case MO_LETTER:
            setAnm(AnmPrm_POST_PUTOUT, false);
            field_0x8EA = 1;
            msgId = 0xCEA;

            break;
        default:
            setAnm(AnmPrm_POST_PUTOUT, false);
            field_0x8EA = 1;
            msgId = 0xCE9;

            break;
    }

    return msgId;
}

/* 0000092C-00000990       .text getMsgNormal__12daObjTpost_cFv */
int daObjTpost_c::getMsgNormal() {
    s32 msgId;
    if(field_0x8EB) {
        dComIfGp_setMessageCountNumber(field_0x8F0);
        msgId = 0xCF7;
        field_0x8EB = 0;
    }
    else {
        if(dKy_daynight_check() == false) {
            msgId = 0xCE5;
        }
        else {
            msgId = 0xCE6;
        }
    }

    return msgId;
}

/* 00000990-000009EC       .text getMsg__12daObjTpost_cFv */
u32 daObjTpost_c::getMsg() {
    if(dComIfGp_event_chkTalkXY()) {
        return getMsgXY();
    }
    else {
        return getMsgNormal();
    }
}

/* 000009EC-00000CF4       .text next_msgStatus__12daObjTpost_cFPUl */
u16 daObjTpost_c::next_msgStatus(u32* pMsgNo) {
    static const u32 pay_msg_num[3] = {
        0x0CEC,
        0x0CED,
        0x0CEE
    };

    u16 status = fopMsgStts_MSG_CONTINUES_e;
    switch(*pMsgNo) {
        case 0xCE5:
        case 0xCE6:
            if(mNumReadable != 0) {
                dComIfGp_setMessageCountNumber(getReceiveLetterNum());
                *pMsgNo = 0xCEB;
            }
            else {
                *pMsgNo = 0xCE7;
            }

            break;  
        case 0xCEB:
            dComIfGp_setMessageCountNumber(field_0x8F0);
            *pMsgNo = 0xCF7;
            break;
        case 0xCF7:
            if(l_HIO.field_0x07 != 0 || m_letter[mNumReadable].field_0x00) {
                *pMsgNo = 0xCF3;
            }
            else {
                field_0x8E9 = 1;
                status = fopMsgStts_MSG_ENDS_e;
            }

            break;
        case 0xCE8:
            *pMsgNo = pay_msg_num[mPayType];

            break;
        case 0xCEC:
        case 0xCED:
        case 0xCEE:
            *pMsgNo = 0xCEF;

            break;
        case 0xCEF:
            if(mpCurrMsg->mSelectNum == 0) {
                if(dComIfGs_getRupee() >= getSendPrice()) {
                    dComIfGp_setItemRupeeCount(-getSendPrice());
                    dComIfGs_setReserveItemEmpty();
                    deliverLetter();
                    *pMsgNo = 0xCF2;
                }
                else {
                    setAnm(AnmPrm_POST_PUTOUT, false);
                    field_0x8EA = 1;
                    *pMsgNo = 0xCF1;
                }
            }
            else {
                setAnm(AnmPrm_POST_PUTOUT, false);
                field_0x8EA = 1;
                *pMsgNo = 0xCF0;
            }

            break;
        case 0xCF3:
            if(m_letter[mNumReadable].mEventReg == 0xB203) {
                *pMsgNo = 0xCF8;
            }
            else {
                *pMsgNo = 0xCF4;
            }

            break;
        case 0xCF4:
        case 0xCF8:
            if(mpCurrMsg->mSelectNum == 0) {
                int price = 0x0A;
                if(m_letter[mNumReadable].mEventReg == 0xB203) {
                    price = 0xC9;
                }
                if(dComIfGs_getRupee() >= price) {
                    dComIfGp_setItemRupeeCount(-price);
                    field_0x8E9 = 1;
                    status = fopMsgStts_MSG_ENDS_e;
                }
                else {
                    *pMsgNo = 0xCF6;
                }
            }
            else {
                *pMsgNo = 0xCF5;
            }

            break;
        case 0xCF5:
        case 0xCF6:
            mNumReadable += 1;
            field_0x8F0 += 1;
            mNumReadable = getReadableLetterNum();
            if(mNumReadable != 0) {
                dComIfGp_setMessageCountNumber(field_0x8F0);
                *pMsgNo = 0xCF7;
            }
            else {
                status = fopMsgStts_MSG_ENDS_e;
            }

            break;
        default:
            status = fopMsgStts_MSG_ENDS_e;
            break;
    }

    if(mCurrMsgNo == m_letter[mNumReadable].mMsgNo && status == fopMsgStts_MSG_ENDS_e) {
        status = fopMsgStts_MSG_DISPLAYED_e;
    }

    return status;
}

/* 00000CF4-00000D38       .text checkTalk__12daObjTpost_cFv */
bool daObjTpost_c::checkTalk() {
    return fopAcM_searchPlayerDistanceXZ(this) < l_HIO.talk_distance;
}

/* 00000D38-00000DC0       .text eventOrder__12daObjTpost_cFv */
void daObjTpost_c::eventOrder() {
    static char* a_demo_name_tbl[] = {
        "DEFAULT_POST"
    };

    if(mEventIdx == 1 || mEventIdx == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);

        if(mEventIdx == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
    else if(mEventIdx >= 3) {
        fopAcM_orderOtherEvent(this, a_demo_name_tbl[mEventIdx - 3], 0x14F);
    }
}

/* 00000DC0-00000E48       .text checkOrder__12daObjTpost_cFv */
void daObjTpost_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        eventSet(0);
        return;
    }

    if(eventInfo.checkCommandTalk()) {
        if(mEventIdx == 1 || mEventIdx == 2) {
            eventSet(0);
            if(dComIfGp_event_chkTalkXY()) {
                field_0x8F5 = 1;
            }
            else {
                field_0x8F4 = 1;
            }
        }
    }
}

/* 00000E48-00000EA4       .text setAttention__12daObjTpost_cFv */
void daObjTpost_c::setAttention() {
    attention_info.position = current.pos;
    attention_info.position.y += l_HIO.attn_pos_offset;
    eyePos = current.pos;
    eyePos.y += l_HIO.eye_pos_offset;
}

/* 00000EA4-0000100C       .text setAnm__12daObjTpost_cFScb */
void daObjTpost_c::setAnm(s8 anmPrmIdx, bool param_2) {
    static const int a_anm_bcks_tbl[] = {
        TORIPOST_BCK_POST_GET,
        TORIPOST_BCK_POST_PUTOUT,
        TORIPOST_BCK_POST_WAIT,
    };
    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {
            // Unused entry
            /* mBckIdx     */ -1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // AnmPrm_POST_GET0
            /* mBckIdx     */ BckIdx_POST_GET,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 0.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // AnmPrm_POST_GET1
            /* mBckIdx     */ BckIdx_POST_GET,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // AnmPrm_POST_PUTOUT
            /* mBckIdx     */ BckIdx_POST_PUTOUT,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // AnmPrm_POST_WAIT
            /* mBckIdx     */ BckIdx_POST_WAIT,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
    };

    if(anmPrmIdx != AnmPrm_NULL) {
        mAnmPrmIdx = anmPrmIdx;
    }

    if(mBckIdx == BckIdx_POST_GET && mMorf->getFrame() == 1.0f) {
        mDoAud_seStart(JA_SE_OBJ_POST_EAT_LUGGAGE);
    }

    if(mBckIdx == BckIdx_POST_PUTOUT) {
        cXyz scale;
        scale.setall(1.0f);
        if(mMorf->getFrame() == 1.0f) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8190, &current.pos, &current.angle, &scale);
            mDoAud_seStart(JA_SE_OBJ_POST_LUGGAGE_OUT);
        }
    }

    dLib_bcks_setAnm(m_arc_name, mMorf, &mBckIdx, &mAnmPrmIdx, &mOldAnmPrmIdx, a_anm_bcks_tbl, a_anm_prm_tbl, param_2);
}

/* 0000100C-00001094       .text setMtx__12daObjTpost_cFv */
void daObjTpost_c::setMtx() {
    J3DModel* pModel = mMorf->getModel();
    pModel->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00001094-000010E0       .text modeWaitInit__12daObjTpost_cFv */
void daObjTpost_c::modeWaitInit() {
    field_0x8F0 = 1;
    if(mNumReadable != 0) {
        setAnm(AnmPrm_POST_WAIT, false);
    }
    else {
        setAnm(AnmPrm_POST_GET0, false);
    }
}

/* 000010E0-00001188       .text modeWait__12daObjTpost_cFv */
void daObjTpost_c::modeWait() {
    if(mNumReadable != 0) {
        setAnm(AnmPrm_POST_WAIT, false);
    }
    else {
        setAnm(AnmPrm_POST_GET0, false);
    }

    if(field_0x8F4) {
        modeProcInit(MODE_TALK);
    }
    else {
        if(field_0x8F5) {
            modeProcInit(MODE_TALK_XY);
        }
        else {
            if(checkTalk()) {
                eventSet(2);
            }
        }
    }
}

/* 00001188-000011B0       .text modeTalkInit__12daObjTpost_cFv */
void daObjTpost_c::modeTalkInit() {
    setAnm(AnmPrm_POST_GET0, false);
}

/* 000011B0-00001240       .text modeTalk__12daObjTpost_cFv */
void daObjTpost_c::modeTalk() {
    if(talk(1) == fopMsgStts_BOX_CLOSED_e) {
        if(field_0x8E9) {
            modeProcInit(MODE_RECEIVE);
            field_0x8E9 = 0;
        }
        else {
            modeProcInit(MODE_WAIT);
        }

        dComIfGp_event_reset();
        field_0x8F4 = 0;
    }
}

/* 00001240-0000129C       .text modeTalkXYInit__12daObjTpost_cFv */
void daObjTpost_c::modeTalkXYInit() {
    setAnm(AnmPrm_POST_GET0, false);
    mPreItemNo = dComIfGp_event_getPreItemNo();
    field_0x8DC = l_HIO.field_0x14;
    field_0x8E0 = l_HIO.field_0x16;
}

/* 0000129C-00001490       .text modeTalkXY__12daObjTpost_cFv */
void daObjTpost_c::modeTalkXY() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    if(isAnm(AnmPrm_POST_PUTOUT)) {
        if(field_0x8EA != 0) {
            field_0x8E4 = 10;
            field_0x8EA = 0;
        }

        if(field_0x8E4 != -1 && cLib_calcTimer(&field_0x8E4) == 0) {
            player->changeOriginalDemo();
            player->changeDemoMode(daPy_demo_c::DEMO_UNK18_e);

            field_0x8E4 = -1;
        }

        switch(mCurrMsgNo) {
            case 0xCE9:
            case 0xCEA:
            case 0xCF0:
            case 0xCF1:
                if(player->getBaseAnimeFrameRate() == 0.0f) {
                    player->changeOriginalDemo();
                    player->changeDemoMode(daPy_demo_c::DEMO_UNK01_e);
                }

                break;
        }
    }

    if(isAnm(AnmPrm_POST_GET0) && dComIfGp_evmng_ChkPresentEnd() && cLib_calcTimer(&field_0x8E0) == 0) {
        dComIfGp_evmng_CancelPresent();
        setAnm(AnmPrm_POST_GET1, false);
    }

    if(isAnm(AnmPrm_POST_GET1) || isAnm(AnmPrm_POST_PUTOUT)) {
        if(mMorf->isStop()) {
            if(cLib_calcTimer(&field_0x8DC) == 0 && talk(1) == fopMsgStts_BOX_CLOSED_e) {
                modeProcInit(MODE_WAIT);
                dComIfGp_event_reset();
                field_0x8F5 = 0;
            }
        }
    }
}

/* 00001490-000014D4       .text modeReceiveInit__12daObjTpost_cFv */
void daObjTpost_c::modeReceiveInit() {
    dComIfGp_event_reset();
    eventSet(3);
    setAnm(AnmPrm_POST_GET0, false);
}

/* 000014D4-000014FC       .text modeReceive__12daObjTpost_cFv */
void daObjTpost_c::modeReceive() {
    modeProcInit(MODE_RECEIVE_DEMO);
}

/* 000014FC-00001500       .text modeReceiveDemoInit__12daObjTpost_cFv */
void daObjTpost_c::modeReceiveDemoInit() {
    return;
}

/* 00001500-000015D8       .text modeReceiveDemo__12daObjTpost_cFv */
void daObjTpost_c::modeReceiveDemo() {
    if(dComIfGp_evmng_endCheck("DEFAULT_POST")) {
        dLetter_read(m_letter[mNumReadable].mEventReg);
        mNumReadable = getReadableLetterNum();
        dComIfGp_event_reset();

        if(mNumReadable != 0) {
            modeProcInit(MODE_TALK);
            eventSet(1);
            field_0x8EB = 1;
            field_0x8F0 += 1;
        }
        else {
            modeProcInit(MODE_WAIT);
            field_0x8F0 = 1;
        }
    }
}

/* 000015D8-00001758       .text modeProc__12daObjTpost_cFQ212daObjTpost_c6Proc_ei */
void daObjTpost_c::modeProc(daObjTpost_c::Proc_e proc, int newMode) {
    typedef void(daObjTpost_c::*mode_func_t)(void);
    struct mode_entry_t {
        mode_func_t init;
        mode_func_t run;
        const char* name;
    };

    static mode_entry_t mode_tbl[] = {
        {
            &daObjTpost_c::modeWaitInit,
            &daObjTpost_c::modeWait,
            "WAIT",
        },
        {
            &daObjTpost_c::modeTalkInit,
            &daObjTpost_c::modeTalk,
            "TALK",
        },
        {
            &daObjTpost_c::modeTalkXYInit,
            &daObjTpost_c::modeTalkXY,
            "TALK_XY",
        },
        {
            &daObjTpost_c::modeReceiveInit,
            &daObjTpost_c::modeReceive,
            "RECEIVE",
        },
        {
            &daObjTpost_c::modeReceiveDemoInit,
            &daObjTpost_c::modeReceiveDemo,
            "RECEIVE_DEMO",
        }
    };

    if(proc == PROC_INIT) {
        mCurMode = newMode;
        (this->*mode_tbl[mCurMode].init)();
    }
    else if(proc == PROC_EXEC) {
        (this->*mode_tbl[mCurMode].run)();
    }
}

/* 00001758-000018CC       .text _execute__12daObjTpost_cFv */
bool daObjTpost_c::_execute() {
    if(dComIfGs_isSymbol(1)) {
        mNumReadable = getReadableLetterNum();
    }
    else {
        mNumReadable = 0;
    }

    checkOrder();
    setAttention();
    setCollision(40.0f, 140.0f);
    modeProc(PROC_EXEC, MODE_NULL);

    if(dComIfGp_event_runCheck() && !mEventCut.cutProc()) {
        cutProc();
    }
    eventOrder();

    fopAcM_posMoveF(this, 0);
    mAcch.CrrPos(*dComIfG_Bgsp());
    mStts.Move();
    if(mCyl.ChkTgHit()) {
        daObj::HitSeStart(&eyePos, current.roomNo, &mCyl, 0x0B);
    }
    daObj::HitEff_kikuzu(this, &mCyl);
    fopAcM_rollPlayerCrash(this, 40.0f, 7);

    mMorf->play(0, 0, 0);
    mMorf->calc();
    setMtx();
    setAnm(AnmPrm_NULL, false);

    return 0;
}

/* 000018CC-000018D0       .text debugDraw__12daObjTpost_cFv */
void daObjTpost_c::debugDraw() {
    GXColor col = {0xFF, 0x00, 0x00, 0x80};
}

/* 000018D0-00001980       .text _draw__12daObjTpost_cFv */
bool daObjTpost_c::_draw() {
    if(l_HIO.debug_draw) {
        debugDraw();
    }

    J3DModel* pModel = mMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mMorf->entryDL();
    dComIfGd_setSimpleShadow2(&current.pos, mAcch.GetGroundH(), 40.0f, mAcch.m_gnd, shape_angle.y, 1.0f, 0);

    return true;
}

/* 00001980-00001BA4       .text createInit__12daObjTpost_cFv */
void daObjTpost_c::createInit() {
    if(dComIfGs_isSymbol(2)) {
        dLetter_autoStock(0xB503);
    }

    if(dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) {
        dLetter_autoStock(0x7D03);
    }

    if(dLetter_isDelivery(dSv_evtBit_c::LETTER_BAITOS_MOM) && dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_ET)) {
        dLetter_autoStock(0x7C03);
    }

    if(dComIfGs_isEventBit(0x1E80)) {
        dLetter_autoStock(0x7B03);
    }

    if(dComIfGs_getWalletSize() == 1 || dComIfGs_getWalletSize() == 2) {
        dLetter_autoStock(0x7A03);
    }

    field_0x8F0 = 1;
    mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
    mpCurrMsg = NULL;

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 5;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 6;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_TALKFLAG_CHECK_e;

    setAnm(AnmPrm_POST_GET0, false);
    setMtx();
    mMorf->calc();

    fopAcM_SetMtx(this, mMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0f, 0.0f, -50.0f, 70.0f, 200.0f, 70.0f);
    fopAcM_setCullSizeFar(this, 10.0f);

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);

    mPayType = checkSendPrice();
    modeProcInit(MODE_WAIT);

    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);
    mAcch.SetRoofNone();
    gravity = -4.5f;

    mEventCut.setActorInfo2("Tpost", this);
}

/* 00001BA4-00001BA8       .text getArg__12daObjTpost_cFv */
void daObjTpost_c::getArg() {
    return;
}

/* 00001BA8-00001D88       .text _create__12daObjTpost_cFv */
cPhs_State daObjTpost_c::_create() {
    fopAcM_SetupActor(this, daObjTpost_c);

    getArg();
    cPhs_State step = dComIfG_resLoad(&mPhs, m_arc_name);
    if(step == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(this, createHeap_CB, 0x7E0) == 0) {
            return cPhs_ERROR_e;
        }

        createInit();
    }

    return step;
}

/* 00002094-000020C4       .text _delete__12daObjTpost_cFv */
bool daObjTpost_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    return true;
}

/* 000020C4-000020E4       .text daObjTpostCreate__FPv */
static cPhs_State daObjTpostCreate(void* i_this) {
    return static_cast<daObjTpost_c*>(i_this)->_create();
}

/* 000020E4-00002108       .text daObjTpostDelete__FPv */
static BOOL daObjTpostDelete(void* i_this) {
    return static_cast<daObjTpost_c*>(i_this)->_delete();
}

/* 00002108-0000212C       .text daObjTpostExecute__FPv */
static BOOL daObjTpostExecute(void* i_this) {
    return static_cast<daObjTpost_c*>(i_this)->_execute();
}

/* 0000212C-00002150       .text daObjTpostDraw__FPv */
static BOOL daObjTpostDraw(void* i_this) {
    return static_cast<daObjTpost_c*>(i_this)->_draw();
}

/* 00002150-00002158       .text daObjTpostIsDelete__FPv */
static BOOL daObjTpostIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObjTpostMethodTable = {
    (process_method_func)daObjTpostCreate,
    (process_method_func)daObjTpostDelete,
    (process_method_func)daObjTpostExecute,
    (process_method_func)daObjTpostIsDelete,
    (process_method_func)daObjTpostDraw,
};

actor_process_profile_definition g_profile_OBJ_TORIPOST = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_TORIPOST,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTpost_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_TORIPOST,
    /* Actor SubMtd */ &daObjTpostMethodTable,
    /* Status       */ 0x18 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
