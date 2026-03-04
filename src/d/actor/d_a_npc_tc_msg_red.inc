// The original name of this file is unknown, but it must exist because d_a_npc_tc's "red's" functions
// are in a separate .text section from the rest of its functions.

/* 00005498-00005720       .text next_msgStatusRed__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusRed(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    if ((mAnmPrmIdx == ANM_PRM_IDX_DANCE01_TO_TALK01 || mAnmPrmIdx == ANM_PRM_IDX_DANCE02_TO_WAIT03) && !mpMorf->isStop()) {
        msgStatus = fopMsgStts_MSG_DISPLAYED_e;
    } else {
        switch(*pMsgNo) {
            case 0xDB7:
            case 0xDE1:
                *pMsgNo = 0xDE2;
                break;

            case 0xDE2:
                if (dComIfGs_getClearCount() != 0) {
                    *pMsgNo = 0xDB8;
                } else {
                    *pMsgNo = 0xDE3;
                }
                break;
            case 0xDB8:
            case 0xDE3:
                *pMsgNo = 0xDE4;
                break;
            case 0xDE4:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDE5:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDE6:
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A20)) {
                    *pMsgNo = 0xDEB;
                } else {
                    *pMsgNo = 0xDE7;
                }
                field_0x814 = true;
                break;
            case 0xDEB:
                if (field_0x814) {
                    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A20)) {
                        *pMsgNo = 0xDEC;
                    } else {
                        *pMsgNo = setFinishMsg();
                    }
                } else {
                    *pMsgNo = setFinishMsg();
                }
                break;
            case 0xDEC:
                *pMsgNo = 0xDED;
                break;
            case 0xDED:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDE7:
                *pMsgNo = 0xDE8;
                break;
            case 0xDE8:
                *pMsgNo = 0xDE9;
                break;
            case 0xDE9:
                *pMsgNo = 0xDEA;
                break;
            case 0xDEA:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDEE:
                *pMsgNo = 0xDEF;
                break;
            case 0xDEF:
                mStatus = STATUS_GET_RUPEE;
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
            case 0xDF1:
                *pMsgNo = 0xDF2;
                break;
            case 0xDF2:
                mStatus = STATUS_MONUMENT_COMPLETE;
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
            case 0xDF3:
                *pMsgNo = 0xDF4;
                break;
            case 0xDF4:
                *pMsgNo = 0xDF5;
                break;
            case 0xDF5:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDF0:
                *pMsgNo = setFinishMsg();
                break;
            case 0xDC7:
                m_jnt.onHeadLock();
                msgStatus = fopMsgStts_MSG_ENDS_e;
                field_0x814 = false;
                break;
            default:
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
        }
    }
    return msgStatus;
}

/* 00005720-00005730       .text setFinishMsg__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::setFinishMsg() {
    m_jnt.onHeadLock();
    return 0xDC7;
}

/* 00005730-00005944       .text getMsgRed__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgRed() {
    stopTower();
    if (field_0x813) {
        field_0x813 = false;
        return 0xDF3;
    }

    if (field_0x812) {
        field_0x812 = false;
        switch(checkAllMonumentFee()) { // fake? 
            default:
                return 0xDF1;
            case false:
                return 0xDF0;
        }
    }

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {

        if (!field_0x810) {
            field_0x810 = true;
#if VERSION == VERSION_DEMO
            if(checkAllMonumentFee() || !checkOneMonumentGet()) {
                return 0xDE6;
            }
            return 0xDEE;
#else
            if (dComIfGs_isStageTbox(dSv_save_c::STAGE_DRC, 0xF) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1240)) {
                return 0xDEE;
            }
            if (dComIfGs_isStageTbox(dSv_save_c::STAGE_FW, 0xF) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1D08)) {
                return 0xDEE;
            }
            if (dComIfGs_isStageTbox(dSv_save_c::STAGE_TOTG, 0xF) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1D04)) {
                return 0xDEE;
            }
            if (dComIfGs_isStageTbox(dSv_save_c::STAGE_WT, 0xF)&& !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1D02)) {
                return 0xDEE;
            }
            if (dComIfGs_isStageTbox(dSv_save_c::STAGE_ET, 0xF) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1D01)) {
                return 0xDEE;
            }
            return 0xDE6;
#endif
        } 

        switch(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A20)) { // fake? 
            default:
                return 0xDEB;
            case false:
                return 0xDEA;

        }
    }

    if (dComIfGs_getClearCount() != 0) {
        return setFirstMsg(&field_0x811, 0xDB7U, 0xDE5);
    }
    return setFirstMsg(&field_0x811, 0xDE1U, 0xDE5);
}

/* 00005944-000059A8       .text checkMonumentFee__10daNpc_Tc_cFUsUs */
bool daNpc_Tc_c::checkMonumentFee(u16 i_stageNo, u16 i_eventId) {
    if (dComIfGs_isStageTbox(i_stageNo, 0xf)) {
        return dComIfGs_isEventBit(i_eventId);
    }
    return false;
}

/* 000059A8-00005A50       .text checkAllMonumentFee__10daNpc_Tc_cFv */
bool daNpc_Tc_c::checkAllMonumentFee() {
    if(checkMonumentFee(dSv_save_c::STAGE_DRC, dSv_event_flag_c::UNK_1240) &&
       checkMonumentFee(dSv_save_c::STAGE_FW, dSv_event_flag_c::UNK_1D08) &&
       checkMonumentFee(dSv_save_c::STAGE_TOTG, dSv_event_flag_c::UNK_1D04) &&
       checkMonumentFee(dSv_save_c::STAGE_WT, dSv_event_flag_c::UNK_1D02) &&
       checkMonumentFee(dSv_save_c::STAGE_ET, dSv_event_flag_c::UNK_1D01)) {
        return true;
    }
    return false;
}

#if VERSION == VERSION_DEMO
bool daNpc_Tc_c::checkOneMonumentGet() {
    if(dComIfGs_isStageTbox(dSv_save_c::STAGE_DRC, 0xf)) {
        return true;
    }
    if(dComIfGs_isStageTbox(dSv_save_c::STAGE_FW, 0xf)) {
        return true;
    }
    if(dComIfGs_isStageTbox(dSv_save_c::STAGE_TOTG, 0xf)) {
        return true;
    }
    if(dComIfGs_isStageTbox(dSv_save_c::STAGE_WT, 0xf)) {
        return true;
    }
    if(dComIfGs_isStageTbox(dSv_save_c::STAGE_ET, 0xf)) {
        return true;
    }
    return false;
}
#endif
/* 00005A50-00005B10       .text checkAllMonumentPay__10daNpc_Tc_cFv */
int daNpc_Tc_c::checkAllMonumentPay() {
    int amountOfMonumentsPaid = 0;
    if(checkMonumentPay(dSv_save_c::STAGE_DRC, dSv_event_flag_c::UNK_1240)) {
        amountOfMonumentsPaid++;
    }
    if (checkMonumentPay(dSv_save_c::STAGE_FW, dSv_event_flag_c::UNK_1D08)) {
        amountOfMonumentsPaid++;
    }
    if (checkMonumentPay(dSv_save_c::STAGE_TOTG, dSv_event_flag_c::UNK_1D04)) {
        amountOfMonumentsPaid++;
    }
    if (checkMonumentPay(dSv_save_c::STAGE_WT, dSv_event_flag_c::UNK_1D02)) {
        amountOfMonumentsPaid++;
    }
    if (checkMonumentPay(dSv_save_c::STAGE_ET, dSv_event_flag_c::UNK_1D01)) {
        amountOfMonumentsPaid++;
    }
    return amountOfMonumentsPaid;
}

/* 00005B10-00005B98       .text checkMonumentPay__10daNpc_Tc_cFUsUs */
bool daNpc_Tc_c::checkMonumentPay(u16 i_stageNo, u16 i_eventId) {
    if(dComIfGs_isEventBit(i_eventId)) {
        return false;
    }
    if(dComIfGs_isStageTbox(i_stageNo, 0xF)) {
        dComIfGs_onEventBit(i_eventId);
        return true;
    }
    return false;
}
