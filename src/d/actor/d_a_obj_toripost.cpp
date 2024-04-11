/**
 * d_a_obj_toripost.cpp
 * Object - Rito Postbox
 */

#include "d/actor/d_a_obj_toripost.h"
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
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

extern dScnPly_reg_HIO_c g_regHIO;

const char daObjTpost_c::m_arc_name[] = "Toripost";

const daObjTpost_c__letter_data daObjTpost_c::m_letter[] = {
    {false, 0x1AAF, KAKERA_HEART,        dSv_evtBit_c::LETTER_BAITOS_MOM},
    {false, 0x0CF9, KAKERA_HEART,        dSv_evtBit_c::LETTER_KOMALIS_FATHER},
    {false, 0x0CFA, COLLECT_MAP_60,      dSv_evtBit_c::LETTER_BOMBS_AD},
    {false, 0x0CFC, dItem_RED_RUPEE_e,   dSv_evtBit_c::LETTER_ORCA},
    {false, 0x0805, dItem_RED_RUPEE_e,   dSv_evtBit_c::LETTER_GRANDMA},
    {false, 0x0CFD, dItem_GREEN_RUPEE_e, dSv_evtBit_c::LETTER_ROCK_SPIRE_SHOP_AD},
    {true,  0x0DB6, COLLECT_MAP_52,      dSv_evtBit_c::LETTER_TINGLE},
    {false, 0x1148, dItem_RED_RUPEE_e,   dSv_evtBit_c::LETTER_ARYLL},
    {false, 0x1AAF, KAKERA_HEART,        dSv_evtBit_c::LETTER_BAITOS_MOM},
    {true,  0x0F76, KAISEN_PRESENT1,     dSv_evtBit_c::LETTER_SILVER_MEMBERSHIP},
    {false, 0x19A6, KAKERA_HEART2,       dSv_evtBit_c::LETTER_HOSKITS_GIRLFRIEND},
    {true,  0x0CFB, dItem_RED_RUPEE_e,   dSv_evtBit_c::LETTER_BAITO},
    {true,  0x0F77, KAISEN_PRESENT2,     dSv_evtBit_c::LETTER_GOLD_MEMBERSHIP},
};

const dCcD_SrcCyl daObjTpost_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_BOOMERANG),
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_GRP,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK8 | CO_SPRM_VSGRP,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ G_TG_SPRM_SHIELD | G_TG_SPRM_NO_CON_HIT | G_TG_SPRM_NO_HIT_MARK,
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

// need to figure out what's putting this data in front of a bunch of rels with the compiler-generated symbol names
static Vec dummy = {1.0f, 1.0f, 1.0f};
static Vec dummy2 = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

/* 000000EC-0000010C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daObjTpost_c*>(i_this)->_createHeap();
}

/* 0000010C-0000022C       .text _createHeap__12daObjTpost_cFv */
BOOL daObjTpost_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, 9);
    JUT_ASSERT(132, modelData != 0);

    mMorf = new mDoExt_McaMorf(modelData, 0, 0, 0, -1, 1.0f, 0, -1, 1, 0, 0x80000, 0x11000022);

    if(mMorf == 0 || mMorf->getModel() == 0) {
        return FALSE;
    }
    else {
        mMorf->getModel()->setUserArea((u32)this);

        return TRUE;
    }
}

/* 0000022C-00000280       .text __ct__16daObjTpost_HIO_cFv */
daObjTpost_HIO_c::daObjTpost_HIO_c() {
    field_0x04 = -1;
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
        int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, action_table, ARRAY_SIZE(action_table), 1, 0);
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
    uint itemPID = fopAcM_createItemForPresentDemo(&current.pos, m_letter[mNumReadable].mItemNo);
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
        setAnm(3, false);
    }
    else {
        setAnm(1, false);
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
    for(int i = 1; i < 0xD; i++) {
        if(dLetter_isStock(m_letter[i].mEventReg)) {
            num = num + 1;
        }
    }

    return num;
}

/* 000006C0-00000750       .text getReadableLetterNum__12daObjTpost_cFv */
s32 daObjTpost_c::getReadableLetterNum() {
    s32 num = 0;
    s32 startIdx = mNumReadable ? mNumReadable : 1;
    s32 readable = mNumReadable;

    if(readable < 0xD) {
        for(int i = startIdx; i < 0xD; i++) {
            if(dLetter_isStock(m_letter[i].mEventReg) == 0) {
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
    static const u8 pay_type[49] = {
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
    cXyz pos(g_regHIO.mChild[12].mFloatRegs[0], g_regHIO.mChild[12].mFloatRegs[1], g_regHIO.mChild[12].mFloatRegs[2]);
    cXyz scale(2.0f, 2.0f, 2.0f);

    switch(mPreItemNo) {
        case dItem_NOTE_TO_MOM_e:
        case MAGYS_LETTER:
            msgId = 0xCE8;
            col.r = g_regHIO.mChild[12].mShortRegs[0] + 0x80;
            col.g = g_regHIO.mChild[12].mShortRegs[1] + 0x80;
            col.b = g_regHIO.mChild[12].mShortRegs[2] + 0x80;
            mDoMtx_stack_c::copy(mMorf->getModel()->mpNodeMtx[2]);
            mDoMtx_stack_c::multVec(&pos, &pos);
            dComIfGp_particle_set(0x57, &pos, &shape_angle, &scale, 0xFF, NULL, -1, &col);
            
            break;
        case dItem_FATHER_LETTER_e:
        case MO_LETTER:
            setAnm(3, false);
            field_0x8EA = 1;
            msgId = 0xCEA;

            break;
        default:
            setAnm(3, false);
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
            if(mNumReadable) {
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
            if(l_HIO.field_0x07 != 0 || m_letter[mNumReadable].field_0x00 != 0) {
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
                    setAnm(3, false);
                    field_0x8EA = 1;
                    *pMsgNo = 0xCF1;
                }
            }
            else {
                setAnm(3, false);
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
                s32 price = 0x0A;
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
            if(mNumReadable) {
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

    if(field_0x8F7 == 1 || field_0x8F7 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);

        if(field_0x8F7 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
    else if(field_0x8F7 >= 3) {
        fopAcM_orderOtherEvent2(this, a_demo_name_tbl[field_0x8F7 - 3], 1, 0x14F);
    }
}

/* 00000DC0-00000E48       .text checkOrder__12daObjTpost_cFv */
void daObjTpost_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        field_0x8F7 = 0;
        return;
    }

    if(eventInfo.checkCommandTalk()) {
        if(field_0x8F7 == 1 || field_0x8F7 == 2) {
            field_0x8F7 = 0;
            if(dComIfGp_event_chkTalkXY()) {
                field_0x8F5 = 1;
            }
            else {
                field_0x8F4 = 1;
            }
        }
    }

    return;
}

/* 00000E48-00000EA4       .text setAttention__12daObjTpost_cFv */
void daObjTpost_c::setAttention() {
    attention_info.position = current.pos;
    attention_info.position.y += l_HIO.attn_pos_offset;
    eyePos = current.pos;
    eyePos.y += l_HIO.eye_pos_offset;
}

/* 00000EA4-0000100C       .text setAnm__12daObjTpost_cFScb */
void daObjTpost_c::setAnm(s8 param_1, bool param_2) {
    static const int a_anm_bcks_tbl[] = {
        0x04,
        0x05,
        0x06,
    };
    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {
            -1,
            -1,
            0,
            8.0f,
            1.0f,
            2
        },
        {
            0,
            -1,
            0,
            8.0f,
            0.0f,
            0
        },
        {
            0,
            -1,
            0,
            8.0f,
            1.0f,
            0
        },
        {
            1,
            -1,
            0,
            8.0f,
            1.0f,
            0
        },
        {
            2,
            -1,
            0,
            8.0f,
            1.0f,
            2
        },
    };

    if(param_1 != 5) {
        field_0x6C9 = param_1;
    }

    if(field_0x6C8 == 0 && mMorf->getFrame() == 1.0f) {
        mDoAud_seStart(JA_SE_OBJ_POST_EAT_LUGGAGE);
    }

    if(field_0x6C8 == 1) {
        cXyz scale;
        scale.setall(1.0f);
        if(mMorf->getFrame() == 1.0f) {
            dComIfGp_particle_set(0x8190, &current.pos, &current.angle, &scale);
            mDoAud_seStart(JA_SE_OBJ_POST_LUGGAGE_OUT);
        }
    }

    dLib_bcks_setAnm(m_arc_name, mMorf, &field_0x6C8, &field_0x6C9, &field_0x6CA, a_anm_bcks_tbl, a_anm_prm_tbl, param_2);
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
    if(mNumReadable) {
        setAnm(4, false);
    }
    else {
        setAnm(1, false);
    }
}

/* 000010E0-00001188       .text modeWait__12daObjTpost_cFv */
void daObjTpost_c::modeWait() {
    if(mNumReadable) {
        setAnm(4, false);
    }
    else {
        setAnm(1, false);
    }

    if(field_0x8F4) {
        modeProc(PROC_INIT, 1);
    }
    else {
        if(field_0x8F5) {
            modeProc(PROC_INIT, 2);
        }
        else {
            if(checkTalk()) {
                field_0x8F7 = 2;
            }
        }
    }
}

/* 00001188-000011B0       .text modeTalkInit__12daObjTpost_cFv */
void daObjTpost_c::modeTalkInit() {
    setAnm(1, false);
}

/* 000011B0-00001240       .text modeTalk__12daObjTpost_cFv */
void daObjTpost_c::modeTalk() {
    if(talk(1) == fopMsgStts_BOX_CLOSED_e) {
        if(field_0x8E9) {
            modeProc(PROC_INIT, 3);
            field_0x8E9 = 0;
        }
        else {
            modeProc(PROC_INIT, 0);
        }

        dComIfGp_event_reset();
        field_0x8F4 = 0;
    }
}

/* 00001240-0000129C       .text modeTalkXYInit__12daObjTpost_cFv */
void daObjTpost_c::modeTalkXYInit() {
    setAnm(1, false);
    mPreItemNo = dComIfGp_event_getPreItemNo();
    field_0x8DC = l_HIO.field_0x14;
    field_0x8E0 = l_HIO.field_0x16;
}

/* 0000129C-00001490       .text modeTalkXY__12daObjTpost_cFv */
void daObjTpost_c::modeTalkXY() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    if(field_0x6C9 == 3) {
        if(field_0x8EA != 0) {
            field_0x8E4 = 10;
            field_0x8EA = 0;
        }

        if(field_0x8E4 != -1 && cLib_calcTimer(&field_0x8E4) == 0) {
            player->mDemo.setOriginalDemoType();
            player->mDemo.setParam0(0);
            player->mDemo.setDemoMode(0x18);

            field_0x8E4 = -1;
        }

        switch(mCurrMsgNo) {
            case 0xCE9:
            case 0xCEA:
            case 0xCF0:
            case 0xCF1:
                if(player->getBaseAnimeFrameRate() == 0.0f) {
                    player->mDemo.setOriginalDemoType();
                    player->mDemo.setParam0(0);
                    player->mDemo.setDemoMode(1);
                }

                break;
        }
    }

    if(field_0x6C9 == 1 && dComIfGp_evmng_ChkPresentEnd() && cLib_calcTimer(&field_0x8E0) == 0) {
        dComIfGp_evmng_CancelPresent();
        setAnm(2, false);
    }

    if(field_0x6C9 == 2 || field_0x6C9 == 3) {
        if(mMorf->isStop()) {
            if(cLib_calcTimer(&field_0x8DC) == 0 && talk(1) == fopMsgStts_BOX_CLOSED_e) {
                modeProc(PROC_INIT, 0);
                dComIfGp_event_reset();
                field_0x8F5 = 0;
            }
        }
    }
}

/* 00001490-000014D4       .text modeReceiveInit__12daObjTpost_cFv */
void daObjTpost_c::modeReceiveInit() {
    dComIfGp_event_reset();
    field_0x8F7 = 3;
    setAnm(1, false);
}

/* 000014D4-000014FC       .text modeReceive__12daObjTpost_cFv */
void daObjTpost_c::modeReceive() {
    modeProc(PROC_INIT, 4);
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
            modeProc(PROC_INIT, 1);
            field_0x8F7 = 1;
            field_0x8EB = 1;
            field_0x8F0 += 1;
        }
        else {
            modeProc(PROC_INIT, 0);
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
    modeProc(PROC_EXEC, 5);

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
    setAnm(5, false);

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

    return 1;
}

/* 00001980-00001BA4       .text createInit__12daObjTpost_cFv */
void daObjTpost_c::createInit() {
    if(dComIfGs_isSymbol(2)) {
        dLetter_autoStock(0xB503);
    }

    if(dComIfGs_checkGetItem(BOMB_BAG)) {
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
    mpCurrMsg = 0;

    attention_info.distances[1] = 5;
    attention_info.distances[3] = 6;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_TALK_e | fopAc_Attn_TALKFLAG_CHECK_e;

    setAnm(1, false);
    setMtx();
    mMorf->calc();

    fopAcM_SetMtx(this, mMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0f, 0.0f, -50.0f, 70.0f, 200.0f, 70.0f);
    fopAcM_setCullSizeFar(this, 10.0f);

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);

    mPayType = checkSendPrice();
    modeProc(PROC_INIT, 0);

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
int daObjTpost_c::_create() {
    fopAcM_SetupActor(this, daObjTpost_c);

    getArg();
    int step = dComIfG_resLoad(&mPhs, m_arc_name);
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
static int daObjTpostCreate(void* i_this) {
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
    fpcLy_CURRENT_e,
    3,
    fpcPi_CURRENT_e,
    PROC_OBJ_TORIPOST,
    &g_fpcLf_Method.base,
    sizeof(daObjTpost_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x01B3,
    &daObjTpostMethodTable,
    0x18 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_4_e,
};
