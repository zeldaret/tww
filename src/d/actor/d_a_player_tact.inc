/**
 * d_a_player_tact.inc
 *
 * Code relating to the Wind Waker item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_main_data.h"
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"
#include "d/d_camera.h"
#include "d/d_procname.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_player_HIO.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "d/d_kankyo_wether.h"

extern const Vec l_tact_top;

/* 8014D778-8014D7D4       .text getDayNightParamData__9daPy_lk_cFv */
u32 daPy_lk_c::getDayNightParamData() {
    u32 spawnType = dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) ? 2 : 0;
    u32 eventIdx = 0xCC;
    u32 extraParams = dComIfGp_getShipActor() != NULL ? 0x140 : 0x40;
    return setParamData(current.roomNo, spawnType, eventIdx, extraParams);
}

/* 8014D7D4-8014D8AC       .text setTactModel__9daPy_lk_cFv */
void daPy_lk_c::setTactModel() {
    if (mEquipItem == dItem_WIND_WAKER_e)
        return;

    deleteEquipItem(FALSE);
    mEquipItem = dItem_WIND_WAKER_e;
    JKRHeap* oldHeap = setItemHeap();

    J3DModelData* modelData = initModel(&mpEquipItemModel, LINK_BDL_TAKT, 0x37221222);
    u8* buffer = new (0x20) u8[0x400];
    dComIfGp_getAnmArchive()->readIdxResource(buffer, 0x400, LKANM_BRK_TTAKT);
    mpEquipItemBrk = (J3DAnmTevRegKey*)J3DAnmLoaderDataBase::load(buffer);
    mpEquipItemBrk->setFrame(0.0f);
    mpEquipItemBrk->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpEquipItemBrk);

    mDoExt_setCurrentHeap(oldHeap);
}

/* 8014D8AC-8014D8F4       .text checkNpcStatus__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNpcStatus() {
    daPy_py_c* partner = (daPy_py_c*)dComIfGp_getCb1Player();
    if (partner) {
        if (!partner->checkNpcNotChange() && partner->current.roomNo == fopAcM_GetRoomNo(this)) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 8014D8F4-8014D938       .text getTactPlayRightArmAnm__9daPy_lk_cFl */
u16 daPy_lk_c::getTactPlayRightArmAnm(s32 r4) {
    if (r4 == 1)
        return LKANM_BCK_ACTIONTAKTRUP;
    else if (r4 == 3)
        return LKANM_BCK_ACTIONTAKTRDW;
    else if (r4 == 2)
        return LKANM_BCK_WAITTAKTRHANDL;
    else if (r4 == 4)
        return LKANM_BCK_WAITTAKTRHANDR;
    else
        return LKANM_BCK_WAITTAKT;
}

/* 8014D938-8014D97C       .text getTactPlayLeftArmAnm__9daPy_lk_cFl */
u16 daPy_lk_c::getTactPlayLeftArmAnm(s32 r4) {
    if (r4 == 1)
        return LKANM_BCK_WAITTAKTLHANDU;
    else if (r4 == 3)
        return LKANM_BCK_WAITTAKTLHANDD;
    else if (r4 == 2)
        return LKANM_BCK_WAITTAKTLHANDL;
    else if (r4 == 4)
        return LKANM_BCK_WAITTAKTLHANDR;
    else
        return LKANM_BCK_WAITTAKT;
}

/* 8014D97C-8014D9A4       .text checkEndTactMusic__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkEndTactMusic() const {
    if (mCurProc == daPyProc_TACT_PLAY_e && m34D0 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* 8014D9A4-8014D9D0       .text getTactMetronomeRate__9daPy_lk_cFv */
f32 daPy_lk_c::getTactMetronomeRate() {
    if (mCurProc == daPyProc_TACT_WAIT_e) {
        return m35A0 / mDoAud_tact_getBeatFrames();
    } else {
        return -1.0f;
    }
}

/* 8014D9D0-8014D9F8       .text checkTactLastInput__9daPy_lk_cFv */
BOOL daPy_lk_c::checkTactLastInput() {
    if (mCurProc == daPyProc_TACT_WAIT_e && m34D2 != -1) {
        return TRUE;
    }
    return FALSE;
}

/* 8014D9F8-8014DA78       .text setTactZev__9daPy_lk_cFUiiPc */
void daPy_lk_c::setTactZev(fpc_ProcID tactZevPartnerId, int r30, char* r31) {
#if VERSION <= VERSION_JPN
    if (r31)
#else
    if (tactZevPartnerId != fpcM_ERROR_PROCESS_ID_e)
#endif
    {
        seStartSystem(JA_SE_PRE_TAKT);
    }
    mTactZevPartnerId = tactZevPartnerId;
    m34CC = r30;
    m3494 = r31;
}

/* 8014DA78-8014DACC       .text getTactTopPos__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::getTactTopPos(cXyz* out) {
    if (mEquipItem != dItem_WIND_WAKER_e || mpEquipItemModel == NULL) {
        return FALSE;
    } else {
        MTXMultVec(mpEquipItemModel->getBaseTRMtx(), &l_tact_top, out);
        return TRUE;
    }
}

/* 8014DACC-8014DB00       .text getTactNormalWait__9daPy_lk_cCFv */
BOOL daPy_lk_c::getTactNormalWait() const {
    if (mCurProc == daPyProc_TACT_WAIT_e && mProcVar0.m3570 == -1 && m34D2 == -1) {
        return TRUE;
    }
    return FALSE;
}

/* 8014DB00-8014DB2C       .text getTactMusic__9daPy_lk_cCFv */
s32 daPy_lk_c::getTactMusic() const {
    if (mCurProc == daPyProc_TACT_PLAY_e)
        return mProcVar0.m3570;
    if (mCurProc == daPyProc_TACT_WAIT_e)
        return m3574;
    return -1;
}

/* 8014DB2C-8014DB74       .text getTactTimerCancel__9daPy_lk_cCFv */
int daPy_lk_c::getTactTimerCancel() const {
    if (mCurProc == daPyProc_TACT_WAIT_e && m35AC <= 0.0f) {
        if (m35AC <= -100.0f) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}

/* 8014DB74-8014DB9C       .text checkTactPlayMelody__9daPy_lk_cFv */
BOOL daPy_lk_c::checkTactPlayMelody() {
    if (mCurProc == daPyProc_TACT_PLAY_e && m34DA == 0) {
        return TRUE;
    }
    return FALSE;
}

/* 8014DB9C-8014DBEC       .text resetTactCount__9daPy_lk_cFv */
void daPy_lk_c::resetTactCount() {
    if (mCurProc == daPyProc_TACT_WAIT_e) {
        m34D8 = 0;
        m35A0 = 0.0f;
        m34DA = 0;
        m34D0 = -1;
        mDoAud_tact_reset();
    }
}

/* 8014DBEC-8014E100       .text procTactWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procTactWait_init(int r30) {
    if (mCurProc == daPyProc_TACT_WAIT_e) {
        if (mProcVar0.m3570 != r30) {
            m34D8 = 0;
            m34DA = 0;
            m34D2 = -1;
        }
        mProcVar0.m3570 = r30;
        if (mProcVar0.m3570 != -4) {
            g_dComIfG_gameInfo.play.field_0x4947 = 1;
        } else {
            g_dComIfG_gameInfo.play.field_0x4947 = 0;
        }
        return TRUE;
    } else if (r30 == -1) {
        if (!dComIfGp_event_compulsory(this, NULL, -1)) {
            return FALSE;
        }
        mDemo.setDemoType(5);
    }

    int r31 = checkShipRideUseItem(1);
    if (r31 == 0) {
        if (r30 == -1) {
            f32 f31 = 200.0f * cM_ssin(shape_angle.y);
            f32 f30 = 200.0f * cM_scos(shape_angle.y);
            cXyz startPos(attention_info.position.x, attention_info.position.y - 50.0f, attention_info.position.z);
            cXyz endPos(startPos.x + f31, startPos.y, startPos.z + f30);
            mLinkLinChk.Set(&startPos, &endPos, this);
            if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                endPos.x = startPos.x - f31;
                endPos.z = startPos.z - f30;
                mLinkLinChk.Set(&startPos, &endPos, this);
                if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                    shape_angle.y += 0x8000;
                } else {
                    endPos.x = startPos.x + f30;
                    endPos.z = startPos.z - f31;
                    mLinkLinChk.Set(&startPos, &endPos, this);
                    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        shape_angle.y += 0x4000;
                    } else {
                        endPos.x = startPos.x - f30;
                        endPos.z = startPos.z + f31;
                        mLinkLinChk.Set(&startPos, &endPos, this);
                        if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                            shape_angle.y -= 0x4000;
                        }
                    }
                }
                current.angle.y = shape_angle.y;
            }
        } else if (r30 == -4 || r30 == -5) {
            if (fopAcM_getTalkEventPartner(this)) {
                shape_angle.y = fopAcM_searchActorAngleY(this, fopAcM_getTalkEventPartner(this));
            }
        }
    }

    commonProcInit(daPyProc_TACT_WAIT_e);
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(ANM_WAITTAKT, daPy_HIO_tact_c0::m.mAnmRate, 0.0f, -1, daPy_HIO_tact_c0::m.field_0x4);
    setActAnimeUpper(LKANM_BCK_WAITTAKT, UPPER_MOVE1_e, daPy_HIO_tact_c0::m.mAnmRate, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);
    setActAnimeUpper(LKANM_BCK_WAITTAKT, UPPER_MOVE2_e, daPy_HIO_tact_c0::m.mAnmRate, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE2_e].setRatio(0.0f);
    mVelocity = 0.0f;
    m34D4 = 0;
    m34D6 = 0;
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);

    if (r30 == -1) {
        dCam_getBody()->StartEventCamera(0xC, fopAcM_GetID(this), 0);
        seStartSystem(JA_SE_TAKT_USE_BEGIN);
    }

    mDoAud_tact_reset();
    mDoAud_tact_setBeat(0);
    mDoAud_tact_setVolume(0.0f);
    mDoAud_tact_ambientPlay();

    setTactModel();
    initShipRideUseItem(r31, 2);

    m34D2 = -1;
    m32E4.makeEmitter(dPa_name::ID_COMMON_0050, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    mProcVar0.m3570 = r30;
    m34D8 = 0;
    m3574 = -1;
    m35A0 = 0.0f;
    m34DA = 0;
    m3624 = 0;
    m35A4 = 0.0f;
    m35A8 = 0.0f;
    if (mProcVar0.m3570 == 6 || mProcVar0.m3570 == 7) {
        m35AC = 600.0f;
    } else {
        m35AC = 900.0f;
    }
    m34D0 = -1;
    setTactZev(-1, -1, NULL);

    if (mProcVar0.m3570 != -4) {
        g_dComIfG_gameInfo.play.field_0x4947 = 1;
    }
    mDoAud_taktModeMute();

    return TRUE;
}

/* 8014E100-8014E9A4       .text procTactWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactWait() {
    setShipRidePosUseItem();
    mDoAud_tact_ambientPlay();
    if (mProcVar0.m3570 == -4) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
        return TRUE;
    }

    if (m34D2 > 0) {
        m34D2--;
        if (mProcVar0.m3570 == -5) {
            m35A0 += 1.0f;
        }
        if (m34D2 == 0) {
            if (mProcVar0.m3570 == -5 || mProcVar0.m3570 == 6 || mProcVar0.m3570 == 7) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
                g_dComIfG_gameInfo.play.field_0x4947 = 0;
            } else if (mProcVar0.m3570 == -1 || mProcVar0.m3570 == -3 || mProcVar0.m3570 >= 0) {
                procTactPlay_init(m3574, mProcVar0.m3570 == -1, mProcVar0.m3570 >= 0);
            }
        }
        return TRUE;
    }

    if (mProcVar0.m3570 == 5 || mProcVar0.m3570 == 1 || mProcVar0.m3570 == 6 || mProcVar0.m3570 == 7) {
        if (m35AC >= 0.0f) {
            m35AC -= 1.0f;
        }
        if (mProcVar0.m3570 == 5) {
            dComIfGp_setAStatus(dActStts_RETURN_e);
        }
    } else if (mProcVar0.m3570 != -5) {
        dComIfGp_setAStatus(dActStts_RETURN_e);
    }

    if (m34D2 == 0 || (cancelTrigger() && dComIfGp_getAStatus() == dActStts_RETURN_e) || m35AC <= 0.0f) {
        if (m34D2 != 0) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
            resetActAnimeUpper(UPPER_MOVE1_e, -1.0f);
            seStartSystem(JA_SE_TAKT_USE_CANCEL);
        }

        g_dComIfG_gameInfo.play.field_0x4947 = 0;

        if (cancelTrigger() && mProcVar0.m3570 == 5) {
            m35AC = -1000.0f;
        }

        if (mProcVar0.m3570 == -1) {
            dComIfGp_event_reset();
            dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
            endDemoMode();
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        }
        mDoAud_tact_reset();
        return TRUE;
    }

    int rightDir, leftDir;
    if (mProcVar0.m3570 != -5) {
        rightDir = mDoAud_getTactDirection(1, m34D4);
        leftDir = mDoAud_getTactDirection(0, m34D6);
        mDoAud_tact_setVolume(mStickDistance * cM_scos(m34DC));
    } else {
        rightDir = m34D4;
        leftDir = m34D6;
    }

    m35A0 += 1.0f;

    if (rightDir != m34D4) {
        if (m35A4 <= 0.0f || rightDir != 0) {
            setActAnimeUpper(
                getTactPlayRightArmAnm(rightDir),
                UPPER_MOVE1_e,
                daPy_HIO_tact_c0::m.mRightArmAnmRate,
                0.0f,
                -1,
                daPy_HIO_tact_c0::m.field_0xC
            );

            if (rightDir == 0 || rightDir == 2 || rightDir == 4) {
                mFrameCtrlUpper[UPPER_MOVE1_e].setRate(daPy_HIO_tact_c0::m.mAnmRate);
                mFrameCtrlUpper[UPPER_MOVE1_e].setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
            }

            if (m34D4 == 4 || m34D4 == 2 || rightDir == 4 || rightDir == 2) {
                mDoAud_tact_reset();
                mDoAud_tact_setBeat(rightDir);
                m35A0 = 0.0f;
                m34DA = 0;
                m_old_fdata->initOldFrameMorf(5.0f, 0, 0x2A);
                m3624 = 0;
                m34D0 = -1;
            }
            m34D4 = rightDir;
            mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);

            if (m34D4 != 0) {
                m35A4 = 2.0f;
            }
        } else {
            m35A4 -= 1.0f;
        }
    } else if (m34D4 != 0) {
        m35A4 = 2.0f;
    }

    if (leftDir != m34D6) {
        if (m35A8 <= 0.0f || leftDir != 0) {
            f32 rate;
            if (m34D4 == 4) {
                rate = daPy_HIO_tact_c0::m.field_0x14;
            } else if (m34D4 == 2) {
                rate = daPy_HIO_tact_c0::m.field_0x18;
            } else {
                rate = daPy_HIO_tact_c0::m.field_0x10;
            }
            setActAnimeUpper(
                getTactPlayLeftArmAnm(leftDir), UPPER_MOVE2_e, rate, 0.0f, -1, daPy_HIO_tact_c0::m.field_0xC
            );
            m34D6 = leftDir;
            mAnmRatioUpper[UPPER_MOVE2_e].setRatio(0.0f);
            mDoAud_tact_armSoundPlay(leftDir);
            if (m34D6 != 0) {
                m35A8 = 2.0f;
            }
        } else {
            m35A8 -= 1.0f;
        }
    } else if (m34D6 != 0) {
        m35A8 = 2.0f;
    }

    if (m35A0 >= mDoAud_tact_getBeatFrames()) {
        mDoAud_tact_metronomePlay(m34DA, m34D6);
        mpEquipItemBrk->setFrame(mpEquipItemBrk->getFrameMax() - 0.001f);
        m34D0 = 3;
        m35A0 -= mDoAud_tact_getBeatFrames();
        m3624++;
        if (m3624 == 2) {
            m3624 = 0;
        }
    } else {
        mpEquipItemBrk->setFrame(0.0f);
    }

    if (m34D0 > 0) {
        m34D0--;
    }

    if (m34D0 == 0) {
        m3574 = mDoAud_tact_judge(m34DA, m34D6);
        m34DA++;

        if (m34DA >= mDoAud_tact_getBeat()) {
            m34DA = 0;
        }

        onResetFlg0(daPyRFlg0_TACT_INPUT);
        m34D0 = -1;

        if ((mProcVar0.m3570 >= 0 && mProcVar0.m3570 == m3574) ||
            ((mProcVar0.m3570 == -1 || mProcVar0.m3570 == -3) && (m3574 >= 0 && m3574 != 6 && m3574 != 7 && dComIfGs_isTact(m3574))))
        {
            m34D2 = 30;
            seStartSystem(JA_SE_WTAKT_MATCH_SIGNAL);
            m35A0 = 0.0f;
        } else {
            m3574 = -1;
            if (mProcVar0.m3570 == -5) {
                m34D8++;
                if (m34D8 == 6) {
                    m34D2 = 15;
                }
            } else if (mProcVar0.m3570 == -2) {
                m34D8++;
                if (m34D8 == 5) {
                    m34D2 = 30;
                    m35A0 = 0.0f;
                }
            }
        }
    }

    f32 f0;
    if (m34D4 == 4) {
        f0 = daPy_HIO_tact_c0::m.field_0x14;
    } else if (m34D4 == 2) {
        f0 = daPy_HIO_tact_c0::m.field_0x18;
    } else {
        f0 = daPy_HIO_tact_c0::m.field_0x10;
    }
    mFrameCtrlUpper[UPPER_MOVE2_e].setRate(f0);

    if (m34D2 == -1) {
        f32 f0 = (m35A0 + m3624 * mDoAud_tact_getBeatFrames()) / (2.0f * mDoAud_tact_getBeatFrames());
        mFrameCtrlUnder[UPPER_MOVE0_e].setFrame(f0 * mFrameCtrlUnder[UPPER_MOVE0_e].getEnd());
        mFrameCtrlUpper[UPPER_MOVE1_e].setFrame(f0 * mFrameCtrlUpper[UPPER_MOVE1_e].getEnd());
        getNowAnmPackUnder(UNDER_MOVE0_e)->setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
        if (getNowAnmPackUpper(UPPER_MOVE1_e)) {
            getNowAnmPackUpper(UPPER_MOVE1_e)->setFrame(mFrameCtrlUpper[UPPER_MOVE1_e].getFrame());
        }
    }

    return TRUE;
}

/* 8014E9A4-8014EBA0       .text procTactPlay_init__9daPy_lk_cFlii */
BOOL daPy_lk_c::procTactPlay_init(s32 r27, int r30, int r31) {
    int r28 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_TACT_PLAY_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);
    mProcVar0.m3570 = r27;
    if (r31 == 0) {
        m3628 = fopMsgM_messageSet(0x5AD + r27);
    } else {
        m3628 = fpcM_ERROR_PROCESS_ID_e;
    }
    mDoAud_tact_setVolume(0.0f);
    resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
    resetActAnimeUpper(UPPER_MOVE1_e, -1.0f);
    m34DA = 0xA;

    daPy_ANM anm;
    if (r27 == 0) {
        anm = ANM_TAKTKAZE;
    } else if (r27 == 1) {
        anm = ANM_TAKTSIPPU;
    } else if (r27 == 5) {
        anm = ANM_TAKTCHUYA;
    } else if (r27 == 4) {
        anm = ANM_TAKTFUJIN;
    } else if (r27 == 2) {
        anm = ANM_TAKTAYATSURI;
    } else {
        anm = ANM_TAKTCHISIN;
    }
    setSingleMoveAnime(anm, 1.0f, 0.0f, -1, 3.0f);

    initShipRideUseItem(r28, 2);

    if (r28 != 0 && mProcVar0.m3570 == 1) {
        stage_stag_info_class* stag_info = dComIfGp_getStageStagInfo();
        if (dStage_stagInfo_GetSTType(stag_info) == dStageType_SEA_e && m34CC != 1 && r30 != 0) {
            daShip_c* ship = dComIfGp_getShipActor();
            fpc_ProcID warpID = fopAcM_create(PROC_TORNADO, 1, &current.pos, fopAcM_GetRoomNo(this));
            ship->setTactWarpID(warpID);
        }
    }

    m32E4.makeEmitter(dPa_name::ID_COMMON_0051, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    m34D0 = 0;
    m3574 = r30;
    m3624 = 0;
    m34D8 = r31;

    return TRUE;
}

/* 8014EBA0-8014EFD4       .text procTactPlay__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlay() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts1_UNK10000_e)) {
        setShipRidePos(1);
        shape_angle.y -= 0x4000;
    }

    mDoAud_tact_ambientPlay();

    if (m3624 != 0) {
        if (checkEndMessage(m3624)) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
            dComIfGp_event_reset();
            dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
            endDemoMode();
        }
        return TRUE;
    } else if (m34DA > 0) {
        m34DA--;
        if (m34DA == 0) {
            mDoAud_tact_melodyPlay(mProcVar0.m3570);
        }
    }

    if (m34D0 != 0) {
        if (m34D8 != 0) {
            g_dComIfG_gameInfo.play.field_0x4947 = 0;
            dComIfGp_evmng_cutEnd(mStaffIdx);
            return TRUE;
        }

        msg_class* msg_p = fopMsgM_SearchByID(m3628);
        if (msg_p == NULL || msg_p->mStatus == fopMsgStts_BOX_CLOSED_e) {
            fopAc_ac_c* tactZevPartner = NULL;
            g_dComIfG_gameInfo.play.field_0x4947 = 0;

            if (msg_p != NULL) {
                msg_p->mStatus = fopMsgStts_MSG_DESTROYED_e;
                m3628 = fpcM_ERROR_PROCESS_ID_e;
            }

            if (mTactZevPartnerId != fpcM_ERROR_PROCESS_ID_e && m34CC == mProcVar0.m3570) {
                tactZevPartner = fopAcM_SearchByID(mTactZevPartnerId);
            }

            if (m3574 == 0) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
                return TRUE;
            }

            if (tactZevPartner != NULL) {
                if (m3494 == 0) {
                    resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
                    dComIfGp_event_reset();
                    dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
                    endDemoMode();
                    return TRUE;
                } else {
                    return procTactPlayEnd_init(-1);
                }
            }

            if (mProcVar0.m3570 == 0) {
                if (dKyw_gbwind_use_check()) {
                    return procTactPlayEnd_init(mProcVar0.m3570);
                }
                m3624 = 0x14A5;
            } else if (mProcVar0.m3570 == 1) {
                daShip_c* ship = dComIfGp_getShipActor();
                if (ship != NULL && ship->getTactWarpID() != fpcM_ERROR_PROCESS_ID_e) {
                    return procTactPlayEnd_init(mProcVar0.m3570);
                }
                m3624 = 0x14A6;
            } else if (mProcVar0.m3570 == 2) {
                if (checkNpcStatus() && !dComIfGp_checkPlayerStatus0(0, daPyStts1_UNK10000_e)) {
                    return procTactPlayEnd_init(mProcVar0.m3570);
                }
                m3624 = 0x14A8;
            } else if (mProcVar0.m3570 == 5) {
                if (dKy_daynighttact_stop_chk()) {
                    m3624 = 0x14A7;
                } else {
                    dStage_FileList_dt_c* fili_p =
                        dComIfGp_roomControl_getStatusRoomDt(current.roomNo)->getFileListInfo();
                    if (dStage_FileList_dt_GetSongOk(fili_p)) {
                        m3624 = 0x14AA;
                    } else {
                        return procTactPlayEnd_init(mProcVar0.m3570);
                    }
                }
            } else {
                m3624 = 0x14A9;
            }
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        seStartSystem(JA_SE_TAKT_MATCHED);
        fopMsgM_messageSendOn();
        m34D0 = 1;

        mDoAud_tact_reset();
        setSingleMoveAnime(ANM_WAITTAKT, daPy_HIO_tact_c0::m.mAnmRate, 0.0f, -1, 10.0f);
        setTextureAnime(6, 0);
        onModeFlg(ModeFlg_00000100);
        offModeFlg(ModeFlg_00000400);
    }

    return TRUE;
}

/* 8014EFD4-8014F210       .text procTactPlayEnd_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procTactPlayEnd_init(int r30) {
    int r28 = checkShipRideUseItem(0);
    commonProcInit(daPyProc_TACT_PLAY_END_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);
    initShipRideUseItem(r28, 2);
    mProcVar0.m3570 = r30;
    mVelocity = 0.0f;
    setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);

    if (r30 == -1) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        fopAcM_orderChangeEvent(this, fopAcM_SearchByID(mTactZevPartnerId), m3494, 0, -1);
        mDemo.setDemoType(2);
    } else if (r30 == 0) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        fopAcM_create(PROC_WBIRD, NULL, &current.pos, dComIfGp_roomControl_getStayNo());
    } else if (r30 == 2) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        dComIfGp_event_setTalkPartner(dComIfGp_getCb1Player());
        fopAcM_orderChangeEvent(this, dComIfGp_getCb1Player(), l_tact_event_label, 0, -1);
        seStartSystem(JA_SE_CTRL_LINK_TO_NPC);
    } else if (r30 == 5) {
        dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
        fopAcM_orderChangeEvent(this, l_tact_night_event_label, 0, -1);
    }

    m3574 = 0;
    m34D6 = shape_angle.y + 0x4000;

    return TRUE;
}

/* 8014F210-8014F4DC       .text procTactPlayEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayEnd() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts1_UNK10000_e)) {
        setShipRidePos(0);
        if (mProcVar0.m3570 == 0 && !dComIfGp_evmng_startCheck(l_tact_wind_change_event_label) &&
            !dComIfGp_evmng_startCheck(l_tact_wind_change_event_label2))
        {
            cLib_addCalcAngleS(&shape_angle.y, m34D6, 5, 0x1000, 0x100);
        }
    }

    if (mProcVar0.m3570 == 0) {
        dComIfGp_setAStatus(dActStts_RETURN_e);
    } else if (mProcVar0.m3570 == 5) {
        if (dComIfGp_evmng_endCheck(l_tact_night_event_label) && !checkNoResetFlg0(daPyFlg0_UNK4000)) {
            onNoResetFlg0(daPyFlg0_UNK4000);
            fopAc_ac_c* ship;
            BOOL hasShip;
            if (dComIfGp_getShipActor() != NULL) {
                ship = dComIfGp_getShipActor();
                hasShip = TRUE;
            } else {
                ship = this; // Use Link's position and angle for the ship if it doesn't exist.
                hasShip = FALSE;
            }
            dComIfGs_setTurnRestart(
                current.pos,
                shape_angle.y,
                fopAcM_GetRoomNo(this),
                getDayNightParamData(),
                ship->current.pos,
                ship->shape_angle.y
#if VERSION > VERSION_DEMO
                , hasShip
#endif
            );
            if (dComIfG_getTimerMode() == 3 && dComIfG_getTimerPtr() != NULL) {
                dComIfG_getTimerPtr()->deleteRequest();
            }
            dStage_turnRestart();
            mDoAud_taktModeMuteOff();
        }
    } else if (mProcVar0.m3570 == 2) {
        if (dComIfGp_evmng_endCheck(l_tact_event_label)) {
            dComIfGp_event_reset();
            changePlayer(dComIfGp_getCb1Player());
            endDemoMode();
        }
    } else if (mProcVar0.m3570 == 1) {
        if (m3574 == 0) {
            if (dComIfGp_getMesgStatus() == 0) {
                dComIfGp_fmapOpenOn();
                m3574 = 1;
            }
        } else {
            dCam_getBody()->EndEventCamera(fopAcM_GetID(this));
            daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
            if (ship == NULL || ship->getTactWarpPosNum() < 0) {
                dComIfGp_event_reset();
                endDemoMode();
                if (ship != NULL) {
                    fopAcM_delete(ship->getTactWarpID());
                    ship->setTactWarpID(fpcM_ERROR_PROCESS_ID_e);
                }
            } else {
                if (dComIfG_getTimerMode() == 3 && dComIfG_getTimerPtr() != NULL) {
                    dComIfG_getTimerPtr()->deleteRequest();
                }
                procShipPaddle_init();
                ship->setTactWarp();
            }
        }
    }

    return TRUE;
}

/* 8014F4DC-8014F690       .text procTactPlayOriginal_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayOriginal_init() {
    if (mCurProc == daPyProc_TACT_PLAY_ORIGINAL_e) {
        return TRUE;
    }
    commonProcInit(daPyProc_TACT_PLAY_ORIGINAL_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_WIND_WAKER_CONDUCT_e);
    m34D0 = 0;
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(ANM_WAITTAKT, daPy_HIO_tact_c0::m.mAnmRate, 0.0f, -1, daPy_HIO_tact_c0::m.field_0x4);

    mProcVar0.m3570 = dComIfGp_event_getTactFreeMStick(m34D0);
    setActAnimeUpper(getTactPlayRightArmAnm(mProcVar0.m3570), UPPER_MOVE1_e, 0.0f, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);

    m3574 = dComIfGp_event_getTactFreeCStick(m34D0);
    setActAnimeUpper(getTactPlayLeftArmAnm(m3574), UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    mAnmRatioUpper[UPPER_MOVE2_e].setRatio(0.0f);

    setTextureAnime(0, 0);
    m3530 = 3;
    mDoAud_tact_setStickPos(mProcVar0.m3570, m3574);
    mDoAud_tact_playArmSwing(mProcVar0.m3570, m3574);
    setTactModel();
    m32E4.makeEmitter(dPa_name::ID_COMMON_0051, mpEquipItemModel->getBaseTRMtx(), &current.pos, NULL);
    m34D6 = 0xF;
    m34DA = 0;
    mDoAud_taktModeMute();

    return TRUE;
}

/* 8014F690-8014F8A0       .text procTactPlayOriginal__9daPy_lk_cFv */
BOOL daPy_lk_c::procTactPlayOriginal() {
    seStartSystem(JA_SE_LK_WTAKT_USING);

    if (m_old_fdata->getOldFrameRate() < 0.01f) {
        if (m34D6 > 0) {
            m34D6--;
            if (m34D6 == 0) {
                m34D0++;
            }
        } else if (m34D0 == 5) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            mDoAud_tact_stopArmSwing();
        } else {
            m34D6 = 0xF;

            mProcVar0.m3570 = dComIfGp_event_getTactFreeMStick(m34D0);
            setActAnimeUpper(
                getTactPlayRightArmAnm(mProcVar0.m3570), UPPER_MOVE1_e, daPy_HIO_tact_c0::m.mRightArmAnmRate, 0.0f, -1, 5.0f
            );
            mAnmRatioUpper[UPPER_MOVE1_e].setRatio(0.0f);
            if (mProcVar0.m3570 == 0 || mProcVar0.m3570 == 2 || mProcVar0.m3570 == 4) {
                mFrameCtrlUpper[UPPER_MOVE1_e].setRate(daPy_HIO_tact_c0::m.mAnmRate);
                mFrameCtrlUpper[UPPER_MOVE1_e].setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
            }

            m3574 = dComIfGp_event_getTactFreeCStick(m34D0);
            setActAnimeUpper(getTactPlayLeftArmAnm(m3574), UPPER_MOVE2_e, daPy_HIO_tact_c0::m.mAnmRate, 0.0f, -1, 5.0f);
            mAnmRatioUpper[UPPER_MOVE2_e].setRatio(0.0f);
            mFrameCtrlUpper[UPPER_MOVE2_e].setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());

            mDoAud_tact_setStickPos(mProcVar0.m3570, m3574);
            mDoAud_tact_playArmSwing(mProcVar0.m3570, m3574);
        }
    }

    if (m34D6 != 0 && m34DA != 0) {
        mDoAud_tact_play();
    }
    m34DA = 1;

    return TRUE;
}
