/* 00004BAC-00004E6C       .text next_msgStatusNormal2__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusNormal2(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    if ((mAnmPrmIdx == 0x11 || mAnmPrmIdx == 0x12) && !mpMorf->isStop()) {
        msgStatus = fopMsgStts_MSG_DISPLAYED_e;
    } else {
        switch (*pMsgNo) {

#if VERSION > VERSION_JPN
            case 0x38AA:
            case 0x38AB:
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3020)) {
                    *pMsgNo = 0x38AC;
                } else {
                    *pMsgNo = 0x38AD;
                }
                break;
            case 0x38AC:
            case 0x38AD:
                if (existKnownCollectMap()) {
                    *pMsgNo = 0xDBA;
                } else {
                    *pMsgNo = 0xDB5;
                }
                break;
#endif

            case 0xDB2:
            case 0xDB3:
            case 0xDFB:
                *pMsgNo = 0xDB4;
                break;

            case 0xDB4:
                *pMsgNo = getMsgNormal2();
                break;

            case 0xDB5:
                *pMsgNo = 0xDBA;
                break;

            case 0xDBB:
                *pMsgNo = 0xDBC;
                break;

            case 0xDBC:
                *pMsgNo = 0xDBD;
                break;

            case 0xDBD:
                *pMsgNo = 0xDBE;
                break;

            case 0xDBE:
                if (mpCurrMsg->mSelectNum == 0) {
                    if ((u16)dComIfGs_getRupee() >= 398) {
                        field_0x6CF = 13;
                        field_0x80D = true;
                        field_0x80C = true;
                        msgStatus = fopMsgStts_MSG_ENDS_e;
                    } else {
                        *pMsgNo = 0xDC0;
                    }
                } else {
                    *pMsgNo = 0xDBF;
                }
                break;
            
            case 0xDC0:
                if (field_0x80B) {
                    *pMsgNo = 0xDC4;
                } else {
                    *pMsgNo = 0xDC1;
                }
                break;

            case 0xDBF:
                *pMsgNo = 0xDC1;
                break;

            case 0xDC3:
                if (mpCurrMsg->mSelectNum == 0) {
                    if ((u16)dComIfGs_getRupee() >= 398) {
                        field_0x6CF = 13;
                        field_0x80D = true;
                        field_0x80C = true;
                        msgStatus = fopMsgStts_MSG_ENDS_e;
                    } else {
                        field_0x80B = true;
                        *pMsgNo = 0xDC0;
                    }
                } else {
                    *pMsgNo = 0xDC4;
                }
                break;

            case 0xDC4:
                field_0x80D = false;
                field_0x80B = false;
                // fallthrough
            default:
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
        }
    }
    return msgStatus;
    /* Nonmatching */
}

/* 00004E6C-00004F68       .text getMsgNormal2__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgNormal2() {
    u32 msg;
    stopTower();
    if (field_0x80D) {
        if (existUnknownCollectMap()) {
            msg = 0xDC3;
            field_0x80D = false;
        } else {
            msg = 0xDC4;

        }
    } else if (!field_0x808) {
        field_0x808 = true;
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A20)) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1708)) {
                msg = 0xDB3;
            } else {
                msg = 0xDFB;
            }
        } else {
            msg = 0xDB2;
        }
    } else {
        if (existUnknownCollectMap()) {
            if (!field_0x809) {
                field_0x809 = true;
                msg = 0xDBB;
            } else {
                msg = 0xDBE;
            }
        } else {
#if VERSION <= VERSION_JPN
            if(existKnownCollectMap()) {
                msg = 0xDBA;
            } else {
                msg = 0xDB5;
            }
#else
            msg = setRupeeSizeMsg();
#endif
        }
    }
    return msg;
    /* Nonmatching */
}

#if VERSION > VERSION_JPN
/* 00004F68-00004FD8       .text setRupeeSizeMsg__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::setRupeeSizeMsg() {
    u32 msgNo = 0xDB5;
    if (dComIfGs_getWalletSize() == 0) {
        msgNo = 0x38AA;
    } else if (dComIfGs_getWalletSize() == 1) {
        msgNo = 0x38AB;
    }
    else if (dComIfGs_getWalletSize() == 2) {
        if (existKnownCollectMap()) {
            msgNo = 0xDBA;
        } else {
            msgNo = 0xDB5;
        }
    }
    return msgNo;
    /* Nonmatching */
}
#endif
/* 00004FD8-00005054       .text existUnknownCollectMap__10daNpc_Tc_cFv */
bool daNpc_Tc_c::existUnknownCollectMap() {
    for(int i = 1; i <= 8; i++) {
        if(!dComIfGs_isCollectMapTriforce(i) && dComIfGs_isGetCollectMap(i)) {
            return true;
        }
    }
    return false;
    /* Nonmatching */
}

/* 00005054-000050DC       .text analysisCollectMap__10daNpc_Tc_cFv */
int daNpc_Tc_c::analysisCollectMap() {
    for(int i = 1; i <= 8; i++) {
        if(!dComIfGs_isCollectMapTriforce(i) && dComIfGs_isGetCollectMap(i)) {
            dComIfGs_onCollectMapTriforce(i); // check return type and if inline is even correct and stuff
            return i;
        }

    }
    return 0;
    /* Nonmatching */
}

/* 000050DC-00005158       .text existKnownCollectMap__10daNpc_Tc_cFv */
bool daNpc_Tc_c::existKnownCollectMap() {
    for(int i = 1; i <= 8; i++) {
        if(dComIfGs_isGetCollectMap(i) && dComIfGs_isCollectMapTriforce(i)) {
            return true;
        }
    }
    return false;
    /* Nonmatching */
}
