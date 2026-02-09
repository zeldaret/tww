// The original name of this file is unknown, but it must exist because d_a_npc_tc's "white's" functions
// are in a separate .text section from the rest of its functions.

/* 00005158-000053D4       .text next_msgStatusWhite__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusWhite(u32* pMsgNo) {
    m_jnt.offHeadLock();
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    if ((mAnmPrmIdx == ANM_PRM_IDX_DANCE01_TO_TALK01 || mAnmPrmIdx == ANM_PRM_IDX_DANCE02_TO_WAIT03) && !mpMorf->isStop()) {
        msgStatus = fopMsgStts_MSG_DISPLAYED_e;
    } else {
        switch (*pMsgNo) {
            case 0xDC5:
                *pMsgNo = 0xDC6;
                break;
            case 0xDC6:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDC8:
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {
                    if (!field_0x80E) {
                        field_0x80E = true;
                        *pMsgNo = 0xDD7;
                    }
                } else if (!field_0x80F) {
                    field_0x80F = true;
                    *pMsgNo = 0xDC9;
                }
                break;
            case 0xDD7:
                *pMsgNo = 0xDD8;
                break;
            case 0xDD8:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDC9:
                if (mpCurrMsg->mSelectNum == 0) {
                    *pMsgNo = 0xDCA;
                } else {
                    *pMsgNo = 0xDD3;
                }
                break;
            case 0xDCA:
                *pMsgNo = 0xDCB;
                break;
            case 0xDCB:
                *pMsgNo = 0xDCC;
                break;
            case 0xDCC:
                *pMsgNo = 0xDCD;
                break;
            case 0xDCD:
                *pMsgNo = 0xDCE;
                break;
            case 0xDCE:
                *pMsgNo = 0xDCF;
                break;
            case 0xDCF:
                *pMsgNo = 0xDD0;
                break;
            case 0xDD0:
                *pMsgNo = 0xDD1;
                break;
            case 0xDD1:
                *pMsgNo = 0xDD2;
                break;
            case 0xDD2:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDD3:
                *pMsgNo = 0xDD4;
                break;
            case 0xDD4:
                *pMsgNo = 0xDD5;
                break;
            case 0xDD5:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDC7:
                m_jnt.onHeadLock();
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
            case 0xDD9:
                *pMsgNo = 0xDDA;
                break;
            case 0xDDA:
                if (existTcMonument()) {
                    *pMsgNo = setFinishMsg();
                } else {
                    *pMsgNo = 0xDDB;
                }
                break;
            case 0xDDB:
                *pMsgNo = 0xDDC;
                break;
            case 0xDDC:
                *pMsgNo = setFinishMsg();
                break;
            default:
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
        }
    }
    return msgStatus;
}

/* 000053D4-00005498       .text getMsgWhite__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgWhite() {
    u32 msg;
    stopTower();
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1708)) {
        msg = 0xDD9;
        m_jnt.onHeadLock();
        
    } else {
       if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {
            if (!field_0x80E) {
                msg = 0xDC8;
                m_jnt.onHeadLock();
            } else {
                msg = 0xDD6;
            }
        } else if (!field_0x80F) {
            msg = 0xDC8;
            m_jnt.onHeadLock();
        } else {
            msg = 0xDC5;
            m_jnt.onHeadLock();
        }
    }
    return msg;
}
