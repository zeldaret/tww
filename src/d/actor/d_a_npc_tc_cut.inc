/* 00005C58-00005E60       .text cutProc__10daNpc_Tc_cFv */
void daNpc_Tc_c::cutProc() {
    static char* action_table[] = {
        "SIT_TO_JUMP",
        "PRESENT",
        "SET_ANM",
        "BACKJUMP",
        "EFFECT",
        "DOOR_OPEN",
        "DOOR_CLOSE",
        "DOOR_CLOSE2",
        "PAY",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId("Tc");
    if (staffIdx != -1) {
        int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, action_table, ARRAY_SIZE(action_table), TRUE, 0);

        if (actIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch(actIdx) {
                    case 0:
                        cutSitToJumpStart(staffIdx);
                        break;
                    case 1:
                        cutPresentStart(staffIdx);
                        break;
                    case 2:
                        cutSetAnmStart(staffIdx);
                        break;
                    case 3:
                        cutBackJumpStart(staffIdx);
                        break;
                    case 4:
                        cutEffectStart(staffIdx);
                        break;
                    case 5:
                        cutDoorOpenStart(staffIdx);
                        break;
                    case 6:
                        cutDoorCloseStart(staffIdx);
                        break;
                    case 7:
                        cutDoorClose2Start(staffIdx);
                        break;
                    case 8:
                        cutPayStart(staffIdx);
                        break;
                }
            }
            switch(actIdx) {
                case 0:
                    cutSitToJumpProc(staffIdx);
                    break;
                case 1:
                    cutPresentProc(staffIdx);
                    break;
                case 2:
                    cutSetAnmProc(staffIdx);
                    break;
                case 3:
                    cutBackJumpProc(staffIdx);
                    break;
                case 4:
                    cutEffectProc(staffIdx);
                    break;
                case 5:
                    cutDoorOpenProc(staffIdx);
                    break;
                case 6:
                    cutDoorCloseProc(staffIdx);
                    break;
                case 7:
                    cutDoorClose2Proc(staffIdx);
                    break;
                case 8:
                    cutPayProc(staffIdx);
            }
        }
    }
    /* Nonmatching */
}

/* 00005E60-00005E6C       .text cutSitToJumpStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSitToJumpStart(int) {
    mAnmPrmIdx = 6;
    /* Nonmatching */
}

/* 00005E6C-00005FA4       .text cutSitToJumpProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSitToJumpProc(int i_staffIdx) {
    if (mpMorf->isStop() && mAnmPrmIdx == 6) {
        speedF = l_HIO.field_0x38;
        speed.y = l_HIO.field_0x40;
        gravity = l_HIO.field_0x3C;
        mAnmPrmIdx = 7;
    }

    if(speed.y <= 0.0f && mAnmPrmIdx == 7) {
        mAnmPrmIdx = 8;
    }

    if(mObjAcch.ChkGroundHit() && mAnmPrmIdx == 8) {
        speedF = 0.0f;
        mAnmPrmIdx = 9;
        mJumpLandingTimer = 0x33;
        return;
    }
    if (cLib_calcTimer(&mJumpLandingTimer) == 0 && mAnmPrmIdx == 9) {
        mAnmPrmIdx = 1;
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
    /* Nonmatching */
}

/* 00005FA4-00005FA8       .text cutPresentStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPresentStart(int) {
    /* Nonmatching */
}

/* 00005FA8-00006174       .text cutPresentProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPresentProc(int i_staffIdx) {
    int* pItemType = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ItemType");
    int temp;
    if(pItemType == NULL) {
        temp = 0; 
    } else {
        temp = *pItemType;
    }
    int itemNo;
    switch(temp) {
        case 0:
            itemNo = 0x21;
            break;

        case 1:
            itemNo = 0xDC;
            break;

        case 2:
            if (field_0x7FC == 1) {
                if (checkAllMonumentFee()) {
                    itemNo = 0xB8;
                } else {
                    switch (checkAllMonumentPay()) {
                        case 1:
                            itemNo = 0xB3;
                            break;
                        case 2:
                            itemNo = 0xB4;
                            break;
                        case 3:
                            itemNo = 0xB5;
                            break;
                        case 4:
                            itemNo = 0xB6;
                            break;
                        case 5:
                            itemNo = 0xB7;
                            break;
                    }
                }
            } else if (field_0x7FC == 0) {
                switch (analysisCollectMap()) {
                    case 1:
                        itemNo = 0x79;
                        break;
                    case 2:
                        itemNo = 0x7A;
                        break;
                    case 3:
                        itemNo = 0x7B;
                        break;
                    case 4:
                        itemNo = 0x7C;
                        break;
                    case 5:
                        itemNo = 0x7D;
                        break;
                    case 6:
                        itemNo = 0x7E;
                        break;
                    case 7:
                        itemNo = 0x7F;
                        break;
                    case 8:
                        itemNo = 0x80;
                        break;
                }
            }
            break;
    }
#if VERSION == VERSION_DEMO
    fpc_ProcID itemPID = fopAcM_createItemForPresentDemo(&current.pos, itemNo, 0, -1);
#else
    fpc_ProcID itemPID = fopAcM_createItemForPresentDemo(&current.pos, itemNo, 0, -1, current.roomNo);
#endif
    if(itemPID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemPID);
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
    /* Nonmatching */
}

/* 00006174-000061F0       .text cutSetAnmStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSetAnmStart(int i_staffIdx) {
    const char* pName = dComIfGp_evmng_getMyStringP(i_staffIdx, "Name");
    if(pName != NULL && strcmp(pName, "GET") == 0) {
        mAnmPrmIdx = 0xF;
    } else {
        mAnmPrmIdx = 1;
    }
    /* Nonmatching */
}

/* 000061F0-000062A0       .text cutSetAnmProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSetAnmProc(int i_staffIdx) {
    const char* pName = dComIfGp_evmng_getMyStringP(i_staffIdx, "Name");
    if (mAnmPrmIdx == 0xF) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
    if(mpMorf->isStop()) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
    /* Nonmatching */
}

/* 000062A0-000062D8       .text cutBackJumpStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutBackJumpStart(int) {
    mTargetSpeed = 0.0f;
    speedF = l_HIO.field_0x48;
    speed.y = l_HIO.field_0x50;
    gravity = l_HIO.field_0x4C;
    mAnmPrmIdx = 10;
    /* Nonmatching */
}

/* 000062D8-000063BC       .text cutBackJumpProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutBackJumpProc(int i_staffIdx) {
    mSmokeCallBack.end();
    if (mObjAcch.ChkGroundLanding()) {
        speedF = 0.0f;
        speed.y = 0.0f;
        field_0x6E0.set(current.pos);
        field_0x6EC = current.angle;
        smoke_set(2.0f, 0.25f, 0.0f, 5.0f, 20.0f);
    } else if (mObjAcch.ChkGroundHit()  && speed.y == 0.0f){
        speedF = 0.0f;
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
    /* Nonmatching */
}

/* 000063BC-000064C8       .text cutEffectStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutEffectStart(int) {
    cXyz pos;
    pos.x = current.pos.x;
    pos.y = current.pos.y;
    pos.z = current.pos.z;

    pos.y -= 80.0f;
    cXyz particleScale;

    particleScale.setall(1.0f);

    JPABaseEmitter* pEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8152, &pos, NULL, &particleScale);
    pEmitter->setGlobalParticleScale(0.62f, 0.6f);
    fopAcM_seStart(this, JA_SE_CM_CMN_NOTICE, 0);

    /* Nonmatching */
}

/* 000064C8-000064F4       .text cutEffectProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutEffectProc(int i_staffIdx) {
    dComIfGp_evmng_cutEnd(i_staffIdx);
    /* Nonmatching */
}

/* 000064F4-00006564       .text cutDoorOpenStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorOpenStart(int) {
    fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_OPEN, 0);
    /* Nonmatching */
}

/* 00006564-00006590       .text cutDoorOpenProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorOpenProc(int i_staffIdx) {
    dComIfGp_evmng_cutEnd(i_staffIdx);
    /* Nonmatching */
}

/* 00006590-00006600       .text cutDoorCloseStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorCloseStart(int) {
    fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_CLOSE_1, 0);
    /* Nonmatching */
}

/* 00006600-0000662C       .text cutDoorCloseProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorCloseProc(int i_staffIdx) {
    dComIfGp_evmng_cutEnd(i_staffIdx);
    /* Nonmatching */
}

/* 0000662C-0000669C       .text cutDoorClose2Start__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorClose2Start(int) {
    fopAcM_seStart(this, JA_SE_OBJ_DOOR_N_CLOSE_2, 0);
    /* Nonmatching */
}

/* 0000669C-000066C8       .text cutDoorClose2Proc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorClose2Proc(int i_staffIdx) {
    dComIfGp_evmng_cutEnd(i_staffIdx);
    /* Nonmatching */
}

/* 000066C8-000066E0       .text cutPayStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPayStart(int i_param) {
    dComIfGp_setItemRupeeCount(-398);
    /* Nonmatching */
}

/* 000066E0-0000670C       .text cutPayProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPayProc(int i_staffIdx) {
    dComIfGp_evmng_cutEnd(i_staffIdx);
    /* Nonmatching */
}
