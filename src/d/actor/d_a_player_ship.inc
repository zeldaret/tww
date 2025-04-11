/**
 * d_a_player_ship.inc
 *
 * Code relating to interacting with and controlling The King of Red Lions.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is not known, but a best guess was taken
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_boomerang.h"
#include "d/actor/d_a_hookshot.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_main_data.h"
#include "d/actor/d_a_ship.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "f_op/f_op_camera_mng.h"

/* 8013F848-8013F8AC       .text shipSpecialDemoStart__9daPy_lk_cFv */
BOOL daPy_lk_c::shipSpecialDemoStart() {
    if (dComIfGp_event_compulsory(this)) {
        mDemo.setDemoType(5);
        return true;
    } else {
        return false;
    }
}

/* 8013F8AC-8013F984       .text checkJumpRideShip__9daPy_lk_cFv */
BOOL daPy_lk_c::checkJumpRideShip() {
    if (mCyl.ChkCoHit()) {
        fopAc_ac_c* hit_ac = mCyl.GetCoHitAc();
        if (hit_ac != NULL && fopAcM_GetName(hit_ac) == PROC_SHIP) {
            daShip_c* ship = (daShip_c*)hit_ac;
            cXyz sp20;
            mDoMtx_multVec(ship->m0298->getModel()->getBaseTRMtx(), &l_ship_offset, &sp20);
            sp20 = old.pos - sp20;
            if (sp20.y > 5.0f && sp20.abs2XZ() < 10000.0f) {
                return procShipJumpRide_init();
            }
        }
    }
    return false;
}

/* 8013F984-8013F9B0       .text checkShipNotNormalMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkShipNotNormalMode() {
    if (((m_anm_heap_under[UNDER_MOVE0_e].mIdx != LKANM_BCK_SHIP_JUMP2) &&
         (m_anm_heap_under[UNDER_MOVE0_e].mIdx != LKANM_BCK_VOYAGE1)) &&
        (m_anm_heap_under[UNDER_MOVE0_e].mIdx != LKANM_BCK_SHIP_JUMP1))
    {
        return true;
    }
    return false;
}

/* 8013F9B0-8013FE78       .text setShipRideArmAngle__9daPy_lk_cFiP16J3DTransformInfo */
void daPy_lk_c::setShipRideArmAngle(int, J3DTransformInfo*) {
    /* Nonmatching */
    static cXyz arm_pos;
    static cXyz armA_offset;
}

/* 8013FE78-8013FEF4       .text checkShipRideUseItem__9daPy_lk_cFi */
int daPy_lk_c::checkShipRideUseItem(int param_1) {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && dComIfGp_getShipActor() != NULL) {
        if (param_1 != 0) {
            deleteEquipItem(FALSE);
        }
        if (checkShipNotNormalMode()) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}

/* 8013FEF4-8013FFC0       .text initShipRideUseItem__9daPy_lk_cFii */
void daPy_lk_c::initShipRideUseItem(int param_1, int param_2) {
    if (param_1 == 0) {
        return;
    }
    dComIfGp_getShipActor()->m034D = 2;  // TODO probably inline setter
    gravity = 0.0f;
    speed.y = 0.0f;
    if (param_1 == 1) {
        setOldRootQuaternion(0, 0x4000, 0);
    }
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
    if (param_2 == 2) {
        setShipRidePosUseItem();
    } else if (param_2 == 1) {
        setShipRidePos(1);
    } else {
        setShipRidePos(0);
    }
    onModeFlg(ModeFlg_IN_SHIP);
}

/* 8013FFC0-80140018       .text setShipRidePosUseItem__9daPy_lk_cFv */
void daPy_lk_c::setShipRidePosUseItem() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        setShipRidePos(1);
        shape_angle.y += -0x4000;
        current.angle.y = shape_angle.y;
    }
}

/* 80140018-801403E0       .text setShipRidePos__9daPy_lk_cFi */
void daPy_lk_c::setShipRidePos(int param_0) {
    daShip_c* iVar1 = dComIfGp_getShipActor();
    if (iVar1 != 0) {
        if (iVar1->mStateFlag & 0x4000) {
            g_dComIfG_gameInfo.play.field_0x492d = 0x12;
        }
        if (param_0 != 0) {
            shape_angle.y = iVar1->shape_angle.y;
            current.angle.y = shape_angle.y;
        }
        if (mCurProc == ANM_MSTEPOVER_JMPED) {
            m353C = iVar1->shape_angle.x;
            m353E = iVar1->shape_angle.z;
            m3540 = 0;
            m3542 = 0;
        } else {
            m353C = m353C + m3540;
            m3540 = (s16)(int)((float)m3540 + 0.75f * (int)(short)(iVar1->shape_angle.x - m353C));
            cLib_addCalcAngleS(&m3540, 0, 5, 0x200, 0x100);
            m353E = m353E + m3542;
            m3542 = m3542 + ((short)(iVar1->shape_angle.z - m353E) >> 1);
            cLib_addCalcAngleS(&m3542, 0, 5, 0x100, 0x30);
        }
        if (mCurProc == ANM_WARPOUT) {
            mDoMtx_multVec(iVar1->m0298->getModel()->getBaseTRMtx(), &l_ship_offset3, &current.pos);
        } else if (mCurProc == ANM_SETBOOTS && m34D8 != 0) {
            mDoMtx_multVec(iVar1->m0298->getModel()->getBaseTRMtx(), &l_ship_offset2, &current.pos);
        } else {
            mDoMtx_multVec(iVar1->m0298->getModel()->getBaseTRMtx(), &l_ship_offset, &current.pos);
        }
        if (checkShipNotNormalMode()) {
            mBodyAngle.y = 0;
        } else {
            cXyz local_38;
            f32 sp08;
            dKyw_get_AllWind_vec(&current.pos, &local_38, &sp08);
            f32 fVar2 = (30.0f * sp08 + iVar1->speedF) / 30.0f;
            if (fVar2 > 1.0f) {
                fVar2 = 1.0f;
            }
            mFrameCtrlUpper[UPPER_MOVE2_e].setRate((1.0f - daPy_HIO_ship_c0::m.field_0xC) * fVar2 +
                                                   daPy_HIO_ship_c0::m.field_0xC);
            if ((iVar1->mStateFlag & 0x40) != 0) {
                if (iVar1->m03E4 > 0.6f) {
                    voiceStart(6);
                } else {
                    if (iVar1->m03E4 > 0.2f) {
                        voiceStart(7);
                    }
                }
                setSingleMoveAnime(ANM_SHIP_JUMP1, 1.0f, 0.0f, -1, 20.0f);
            }
            if (iVar1->mStateFlag & 0x80) {
                setSingleMoveAnime(ANM_SHIP_JUMP2, 1.0f, 3.0f, -1, 3.0f);
            }
            if (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_SHIP_JUMP2) {
                if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
                    if ((iVar1->mStateFlag & 1) != 0) {
                        setSingleMoveAnime(ANM_SHIP_JUMP1, 1.0f, 0.0f, -1, 20.0f);
                    } else {
                        setSingleMoveAnime(ANM_VOYAGE1, 1.0f, 0.0f, -1, 5.0f);
                    }
                } else {
                    mFrameCtrlUpper[UPPER_MOVE2_e].setRate(0.0f);
                }
            }
            s16 sVar4;
            if (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_VOYAGE1) {
                sVar4 = -daPy_HIO_ship_c0::m.field_0x4 * iVar1->m03DC;
            } else {
                sVar4 = 0;
            }
            cLib_addCalcAngleS(&mBodyAngle.y, sVar4, 4, 0x400, 0x80);
        }
    }
}

/* 801403E0-80140480       .text setShipAttentionAnmSpeed__9daPy_lk_cFf */
void daPy_lk_c::setShipAttentionAnmSpeed(f32 param_0) {
    if (mpAttention->Lockon()) {
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(daPy_HIO_atnMove_c0::m.field_0x24);
        mFrameCtrlUpper[UPPER_MOVE2_e].setRate(param_0);
    } else {
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
        mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(0.0f);
        mFrameCtrlUpper[UPPER_MOVE2_e].setRate(0.0f);
        mFrameCtrlUpper[UPPER_MOVE2_e].setFrame(0.0f);
    }
}

/* 80140480-801405F0       .text setShipAttnetionBodyAngle__9daPy_lk_cFv */
void daPy_lk_c::setShipAttnetionBodyAngle() {
    setBodyAngleXReadyAnime();

    s16 r30 = 0;
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
    } else {
        if (mStickDistance > 0.05f) {
            int direction = getDirectionFromAngle(m34DC);
            if (direction == DIR_LEFT) {
                s16 r5 = 512.0f * mStickDistance;
                if (r5 > m34DA) {
                    s16 r0 = 64.0f * mStickDistance;
                    m34DA += r0;
                    if (m34DA > r5) {
                        m34DA = r5;
                    }
                    r30 = m34DA;
                } else {
                    r30 = r5;
                }
            } else if (direction == DIR_RIGHT) {
                s16 r5 = -512.0f * mStickDistance;
                if (r5 < m34DA) {
                    s16 r0 = 64.0f * mStickDistance;
                    m34DA -= r0;
                    if (m34DA < r5) {
                        m34DA = r5;
                    }
                    r30 = m34DA;
                } else {
                    r30 = r5;
                }
            }
        }
        cLib_addCalcAngleS(&m34DA, r30, 3, 0x40, 0x10);
        shape_angle.y = shape_angle.y + m34DA;
    }

    current.angle.y = shape_angle.y;
}

/* 801405F0-80140C88       .text changeShipEndProc__9daPy_lk_cFv */
int daPy_lk_c::changeShipEndProc() {
    /* Nonmatching - branching */
    daBoomerang_c* pfVar4;

    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if (ship == NULL) {
        return checkNextMode(0);
    }
    offNoResetFlg0(daPyFlg0_SHIP_DROP);
    if (doTrigger()) {
        pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
        if (pfVar4 != NULL) {
            pfVar4->onCancelFlg();
        }
    }
    if (((((mCurProc != daPyProc_SHIP_SCOPE_e) && (mCurProc != daPyProc_SHIP_BOW_e)) &&
          (mCurProc != daPyProc_SHIP_HOOKSHOT_e)) &&
         ((mCurProc != daPyProc_SHIP_BOOMERANG_e || (mEquipItem != dItem_BOOMERANG_e)))) &&
        ((ship->mStateFlag & 1) == 0))
    {
        setTalkStatus();
        if (orderTalk()) {
            return true;
        }
    }
    if ((dComIfGp_getMiniGameType() != 1) && (ship->speedF < 3.0f)) {
        if (ship->m1044.absXZ() < 3.0f) {
            if (((!checkShipNotNormalMode() ||
                  (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_FREEA)) ||
                 (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_FREEB)) ||
                (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_FREED))
            {
                if (((!dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e) &&
                      (!spActionButton())) &&
                     ((dComIfGp_getDoStatus() == 0 && (mCurProc == daPyProc_SHIP_PADDLE_e)))))
                {
                    if ((!ship->checkForceMove()) && (dComIfGp_setDoStatus(29), doTrigger())) {
                        return procShipGetOff_init();
                    }
                }
            }
        }
    }
    if ((mCurProc != daPyProc_SHIP_SCOPE_e) && ((ship->mStateFlag & 1) == 0)) {
        if (dComIfGp_getDoStatus() == 0) {
            if ((ship->mShipMode == 1) || (ship->checkForceMove()) ||
                (((ship->speedF < 3.0f) && (ship->mShipMode != 0))))
            {
                dComIfGp_setDoStatus(8);
            }
        }
        if (checkSetItemTrigger(NORMAL_SAIL, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procShipSteer_init();
        } else if (checkSetItemTrigger(dItem_BOMB_BAG_e, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procShipCannon_init();
        } else if (checkSetItemTrigger(dItem_GRAPPLING_HOOK_e, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procShipCrane_init();
        } else if (checkSetItemTrigger(dItem_TELESCOPE_e, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procShipScope_init(1);
        } else if (checkSetItemTrigger(daPyItem_PHOTOBOX_e, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procShipScope_init(0);
        } else if (checkSetItemTrigger(daPyItem_BOW_e, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procShipBow_init();
        } else if ((checkSetItemTrigger(dItem_BOOMERANG_e, 1)) &&
                   (mActorKeepThrow.getActor() == NULL))
        {
            procShipBoomerang_init();
        } else if (checkSetItemTrigger(dItem_HOOKSHOT_e, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procShipHookshot_init();
        } else if (checkSetItemTrigger(dItem_WIND_WAKER_e, 1)) {
            pfVar4 = (daBoomerang_c*)mActorKeepThrow.getActor();
            if (pfVar4 != NULL) {
                pfVar4->onCancelFlg();
            }
            procTactWait_init(-1);
        } else if (checkSetItemTrigger(dItem_TINGLE_TUNER_e, 1)) {
            fopAcM_orderTalkEvent(this, (fopAc_ac_c*)dComIfGp_getAgb());
            if (checkShipNotNormalMode()) {
                setShipRidePos(0);
            } else {
                setShipRidePos(1);
            }
            return true;
        } else if (checkSetItemTrigger(dItem_MAGIC_ARMOR_e, 1)) {
            if (checkShipNotNormalMode()) {
                setShipRidePos(0);
            } else {
                setShipRidePos(1);
            }
            changeDragonShield(1);
        } else if (checkSetItemTrigger(daPyItem_DRINK_BOTTLE_e, 0)) {
            procBottleDrink_init(dComIfGp_getSelectItem(mReadyItemBtn));
        } else if (checkSetItemTrigger(dItem_FAIRY_BOTTLE_e, 0)) {
            procBottleOpen_init(0x57);
        } else if (checkSetItemTrigger(daPyItem_OPEN_BOTTLE_e, 1)) {
            procBottleOpen_init(dComIfGp_getSelectItem(mReadyItemBtn));
        } else if (checkSetItemTrigger(dItem_EMPTY_BOTTLE_e, 1)) {
            procBottleSwing_init(1);
        } else if (checkSetItemTrigger(dItem_HYOI_PEAR_e, 1)) {
            procFoodSet_init();
        } else if (checkSetItemTrigger(daPyItem_ESA_e, 1)) {
            procFoodThrow_init();
        } else if ((doTrigger()) && (dComIfGp_getDoStatus() == 8)) {
            procShipPaddle_init();
        }
    } else {
        return false;
    }
}

/* 80140C88-80140D04       .text initShipBaseAnime__9daPy_lk_cFv */
void daPy_lk_c::initShipBaseAnime() {
    if (m_anm_heap_under[UNDER_MOVE0_e].mIdx != LKANM_BCK_SHIP_JUMP2) {
        setSingleMoveAnime(ANM_VOYAGE1, 1.0f, 0.0f, -1, 5.0f);
    }
    setActAnimeUpper(LKANM_BCK_FN_HAIR1, UPPER_MOVE2_e, 1.0f, 0.0f, -1, -1.0f);
    m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
}

/* 80140D04-80140D80       .text initShipCraneAnime__9daPy_lk_cFv */
void daPy_lk_c::initShipCraneAnime() {
    daPy_ANM dVar1;

    if ((s16)dComIfGp_getShipActor()->m039A > 0) {
        dVar1 = ANM_SALVRWAIT;
        m3570 = 3;
        m3574 = 3;
    } else {
        dVar1 = ANM_SALVLWAIT;
        m3570 = 2;
        m3574 = 2;
    }
    daPy_matAnm_c::offMabaFlg();
    setSingleMoveAnime(dVar1, 1.0f, 0.0f, -1, 10.0f);
}

/* 80140D80-80140EF0       .text procShipReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipReady_init() {
    commonProcInit(daPyProc_SHIP_READY_e);
    deleteEquipItem(TRUE);
    daShip_c* iVar1 = dComIfGp_getShipActor();
    setSingleMoveAnime(ANM_VJMPCL, daPy_HIO_wallCatch_c0::m.field_0x24,
                       daPy_HIO_wallCatch_c0::m.field_0x2C, daPy_HIO_wallCatch_c0::m.field_0x4,
                       daPy_HIO_wallCatch_c0::m.field_0x28);
    gravity = 0.0f;
    mVelocity = 0.0f;
    s16 sVar3 = fopAcM_searchActorAngleY((fopAc_ac_c*)iVar1, this);
    if ((s16)(sVar3 - iVar1->shape_angle.y) > 0) {
        mDoMtx_multVec(iVar1->m0298->getModel()->getBaseTRMtx(), &l_ship_ledge, &current.pos);
        shape_angle.y = iVar1->shape_angle.y + -0x4000;
        m34D4 = shape_angle.y;
        m34D0 = 0;
    } else {
        mDoMtx_multVec(iVar1->m0298->getModel()->getBaseTRMtx(), &l_ship_redge, &current.pos);
        shape_angle.y = iVar1->shape_angle.y + 0x4000;
        m34D4 = shape_angle.y + 0x8000;
        m34D0 = 1;
    }
    current.angle.y = shape_angle.y;
    m3570 = 0;
    iVar1->m034D = 3;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK1000000_e);
    swimOutAfter(1);
    offNoResetFlg0(daPyFlg0_SHIP_DROP);
    m3540 = 0;
    m3542 = 0;
    m353C = 0;
    m353E = 0;
    return true;
}

/* 80140EF0-8014105C       .text procShipReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipReady() {
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();

    if (ship == 0) {
        return checkNextMode(0);
    }

    if (m3570 == 0) {
        if (m34D0 == 0) {
            mDoMtx_multVec(ship->m0298->getModel()->getBaseTRMtx(), &l_ship_ledge, &current.pos);
        } else {
            mDoMtx_multVec(ship->m0298->getModel()->getBaseTRMtx(), &l_ship_redge, &current.pos);
        }
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            m3570 = 1;
            mVelocity = 6.0f;
            setSingleMoveAnime(ANM_WALK, daPy_HIO_move_c0::m.field_0x40, 0.0f, -1, 5.0f);
            m34C2 = 10;
            offModeFlg(ModeFlg_HANG | ModeFlg_00000400);
            ship->m034D = 4;
            m35A0 = ship->current.pos.y;
        }
    } else {
        current.pos.y = current.pos.y + (ship->current.pos.y - m35A0);
        cLib_chaseF(&current.pos.y, (ship->current.pos.y + l_ship_offset.y), 2.0f);
        m35A0 = ship->current.pos.y;
        if (!(fopAcM_seenActorAngleY(this, (fopAc_ac_c*)ship) < 0x4000)) {
            procShipPaddle_init();
        }
    }

    return true;
}

/* 8014105C-80141140       .text procShipJumpRide_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipJumpRide_init() {
    daShip_c* iVar1 = dComIfGp_getShipActor();

    if (iVar1 == 0 || ((iVar1->attention_info.flags & fopAc_Attn_ACTION_SHIP_e) == 0)) {
        return false;
    }

    commonProcInit(daPyProc_SHIP_JUMP_RIDE_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    iVar1->m034D = 2;
    iVar1->mStateFlag = iVar1->mStateFlag | 0x2000;
    setSingleMoveAnime(ANM_SLIPICE, 1.0f, 0.0f, -1, 5.0f);
    setShipRidePos(0);
    offNoResetFlg0(daPyFlg0_SHIP_DROP);
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK80_e);
    seStartOnlyReverb(JA_SE_LK_FT_JUMP_SHIP);
    return true;
}

/* 80141140-80141180       .text procShipJumpRide__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipJumpRide() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        procShipPaddle_init();
    } else {
        setShipRidePos(0);
    }
    return true;
}

/* 80141180-8014123C       .text procShipSteer_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipSteer_init() {
    offNoResetFlg0(daPyFlg0_UNK1);
    daShip_c* iVar1 = dComIfGp_getShipActor();
    if (mCurProc == daPyProc_SHIP_STEER_e) {
        iVar1->m034D = 1;
        return false;
    }

    commonProcInit(daPyProc_SHIP_STEER_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    mVelocity = 0.0f;
    speed.y = 0.0f;
    iVar1->m034D = 1;
    initShipBaseAnime();
    setShipRidePos(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
    return true;
}

/* 8014123C-80141288       .text procShipSteer__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipSteer() {
    if (changeShipEndProc()) {
        return true;
    }

    setShipRidePos(1);
    return true;
}

/* 80141288-801413A4       .text procShipPaddle_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipPaddle_init() {
    offNoResetFlg0(daPyFlg0_UNK800000);
    if (mCurProc == daPyProc_SHIP_PADDLE_e) {
        return false;
    }

    daShip_c* iVar1 = dComIfGp_getShipActor();
    BOOL bVar1;
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && !checkShipNotNormalMode()) {
        bVar1 = true;
    } else {
        bVar1 = false;
    }
    commonProcInit(daPyProc_SHIP_PADDLE_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    iVar1->m034D = 2;
    initShipBaseAnime();
    if (!bVar1) {
        setOldRootQuaternion(0, shape_angle.y - iVar1->shape_angle.y, 0);
    }
    setShipRidePos(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
    m34D0 = (s16)(int)(300.0f + cM_rndF(150.0f));
    return true;
}

/* 801413A4-801416BC       .text procShipPaddle__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipPaddle() {
    /* Nonmatching */
    bool bVar2;
    int iVar3;
    int iVar4;
    daPy_ANM dVar5;
    float dVar6;

    if (changeShipEndProc()) {
        return true;
    }
    setShipRidePos(1);
    dComIfGp_setRStatus(0x2c);
    if ((dComIfGp_getDoStatus() == 0) && (dComIfGp_getShipActor()->speedF >= 3.0f)) {
        dComIfGp_setDoStatus(19);
    }
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e)) {
        dComIfGp_setAStatus(7);
        if (checkSubjectEnd(1)) {
            dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK2000_e);
        }
    } else {
        onResetFlg0(daPyRFlg0_UNK4000000);
        if (((dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x1000))) &&
            (dComIfGp_event_runCheck() == 0))
        {
            setSubjectMode();
        }
    }
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if ((m34D0 == -1) || (m34D0 == -2)) {
        if (m34D0 == -2) {
            if (mFrameCtrlUnder[UNDER_MOVE0_e].checkPass(168.0f)) {
                voiceStart(48);
            } else if (mFrameCtrlUnder[UNDER_MOVE0_e].checkPass(105.0f)) {
                voiceStart(47);
            }
        }
        if ((!(mStickDistance > 0.05f) && (!dComIfGp_event_runCheck())) &&
            (dComIfGp_getDoStatus() == 29))
        {
            if ((!ship->checkForceMove()) && !(mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f))
                goto LAB_801416a4;
        }
        initShipBaseAnime();
        m34D0 = cM_rndF(150.0f) + 300.0f;
    } else {
        if (((!dComIfGp_event_runCheck()) && (dComIfGp_getDoStatus() == 29)) &&
            (mStickDistance <= 0.05f))
        {
            if ((!ship->checkForceMove()) && (!checkShipNotNormalMode())) {
                m34D0--;
                if (m34D0 == 0) {
                    dVar6 = cM_rnd();
                    m34D0 = -1;
                    if (dVar6 < 0.3333f) {
                        dVar5 = ANM_FREEA;
                    } else {
                        if (dVar6 < 0.6666f) {
                            dVar5 = ANM_FREEB;
                            m34D0 = -2;
                        } else {
                            dVar5 = ANM_FREED;
                        }
                    }
                    setSingleMoveAnime(dVar5, 1.0f, 0.0f, -1, 5.0f);
                }
                goto LAB_801416a4;
            }
        }
        m34D0 = cM_rndF(150.0f) + 300.0f;
    }
LAB_801416a4:
    return true;
}

/* 801416BC-801417EC       .text procShipScope_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procShipScope_init(int param_0) {
    daShip_c* iVar1 = dComIfGp_getShipActor();
    commonProcInit(daPyProc_SHIP_SCOPE_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    iVar1->m034D = 2;
    setShipRidePos(0);
    setSingleMoveAnime(ANM_WAITS, daPy_HIO_move_c0::m.field_0x38, 0.0f, -1, 5.0f);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
    mDoAud_seStart(JA_SE_ITM_SUBMENU_IN_1);
    offNoResetFlg0(daPyFlg0_SCOPE_CANCEL);
    mEquipItem = dComIfGp_getSelectItem(mReadyItemBtn);
    if (param_0 != 0) {
        dComIfGp_setPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e);
        setScopeModel();
    } else {
        dComIfGp_setPlayerStatus1(0, daPyStts1_PICTO_BOX_AIM_e);
        setPhotoBoxModel();
    }
    return true;
}

/* 801417EC-801418B4       .text procShipScope__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipScope() {
    int iVar2 = 1;
    if (changeShipEndProc()) {
        return true;
    }
    if (checkScopeEnd()) {
        procShipPaddle_init();
    } else {
        if ((((dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x10))) &&
             (!dComIfGp_event_runCheck())) &&
            (mDemo.getDemoType() == 0))
        {
            shape_angle.y = fopCamM_GetAngleY(dComIfGp_getCamera(mCameraInfoIdx));
            iVar2 = 0;
        }
    }
    offNoResetFlg0(daPyFlg0_SCOPE_CANCEL);
    setShipRidePos(iVar2);
    return true;
}

/* 801418B4-801419B4       .text procShipBoomerang_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipBoomerang_init() {
    daShip_c* iVar1 = dComIfGp_getShipActor();
    if (mCurProc == daPyProc_SHIP_BOOMERANG_e) {
        return false;
    }

    commonProcInit(daPyProc_SHIP_BOOMERANG_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    iVar1->m034D = 2;
    mEquipItem = dItem_BOOMERANG_e;
    setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, 5.0f);
    setActAnimeUpper(LKANM_BCK_BOOMWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    setTextureAnime(0, 0);
    makeItemType();
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e | daPyStts0_BOOMERANG_AIM_e);
    setShipRidePos(0);
    m34D4 = iVar1->shape_angle.y;
    m34DA = 0;
    return true;
}

/* 801419B4-80141BB0       .text procShipBoomerang__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipBoomerang() {
    if (changeShipEndProc()) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
        return true;
    } else {
        setShipRidePos(0);
        if (mActorKeepThrow.getActor() == NULL) {
            if (m_anm_heap_upper[UPPER_MOVE2_e].mIdx != LKANM_BCK_BOOMCATCH) {
                dComIfGp_setDoStatus(7);
                if (doTrigger()) {
                    {
                        procShipPaddle_init();
                        deleteEquipItem(TRUE);
                        return true;
                    }
                }
            }
        }
        mSightPacket.offDrawFlg();
        daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
        if (m_anm_heap_upper[UPPER_MOVE2_e].mIdx != LKANM_BCK_BOOMCATCH) {
            if (mEquipItem == dItem_BOOMERANG_e) {
                if (m_anm_heap_upper[UPPER_MOVE2_e].mIdx == LKANM_BCK_BOOMWAIT) {
                    setShipAttentionAnmSpeed(daPy_HIO_boom_c0::m.field_0x18);
                    checkNextActionBoomerangReady();
                    if (mpAttention->Lockon()) {
                        setShipAttnetionBodyAngle();
                    } else {
                        m34DA = 0;
                        if (setBodyAngleToCamera()) {
                            daBoomerang_c* this_01 = (daBoomerang_c*)mActorKeepEquip.getActor();
                            if (this_01 != NULL) {
                                {
                                    cXyz local_28;
                                    checkSightLine(this_01->getFlyMax(), &local_28);
                                    mSightPacket.setPos(&local_28);
                                    mSightPacket.onDrawFlg();
                                }
                            }
                        }
                    }
                    if (mpAttnActorLockOn == NULL) {
                        shape_angle.y += (s16)(ship->shape_angle.y - m34D4);
                    }
                }
            } else {
                if (mActorKeepThrow.getActor() == NULL) {
                    return procShipPaddle_init();
                }
                setShapeAngleToAtnActor();
                mFrameCtrlUnder[UNDER_MOVE0_e].setRate(daPy_HIO_atnMove_c0::m.field_0x24);
            }
        }
        m34D4 = ship->shape_angle.y;
    }
    return true;
}

/* 80141BB0-80141CF8       .text procShipHookshot_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipHookshot_init() {
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if (mCurProc == daPyProc_SHIP_HOOKSHOT_e) {
        return false;
    }

    commonProcInit(daPyProc_SHIP_HOOKSHOT_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    ship->m034D = 2;
    mEquipItem = dItem_HOOKSHOT_e;
    m355C = 10;
    setSingleMoveAnime(ANM_ATNLS, 0.0f, 0.0f, -1, 5.0f);
    setActAnimeUpper(LKANM_BCK_HOOKSHOTWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    setTextureAnime(0, 0);
    makeItemType();
    dComIfGp_setPlayerStatus0(0, daPyStts0_HOOKSHOT_AIM_e | daPyStts0_SHIP_RIDE_e);
    setShipRidePos(0);
    m34D4 = ship->shape_angle.y;
    if (mpAttention->Lockon()) {
        m3570 = 1;
    } else {
        m3570 = 0;
    }

    return true;
}

/* 80141CF8-80141F2C       .text procShipHookshot__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipHookshot() {
    /* Nonmatching - regalloc */
    if (changeShipEndProc()) {
        return true;
    }
    setShipRidePos(0);
    dComIfGp_setDoStatus(7);
    daHookshot_c* pfVar4 = (daHookshot_c*)mActorKeepEquip.getActor();
    if (((doTrigger()) || (pfVar4 == NULL)) ||
        ((m3570 != 0) && (m355E == 0)) && (!mpAttention->Lockon()))
    {
        procShipPaddle_init();
        deleteEquipItem(TRUE);
        return true;
    } else {
        mSightPacket.offDrawFlg();
        checkNextActionHookshotReady();
        daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
        if (pfVar4->checkWait()) {
            setShipAttentionAnmSpeed(1.0f);
        }
        if (mpAttention->Lockon()) {
            if (pfVar4->checkWait()) {
                setShipAttnetionBodyAngle();
            } else {
                m34DA = 0;
            }
            m3570 = 1;
        } else {
            m34DA = 0;
            setBodyAngleToCamera();
            m3570 = 0;
        }
        if (mpAttnActorLockOn == NULL) {
            shape_angle.y += (s16)(ship->shape_angle.y - m34D4);
        }
        if (pfVar4->checkWait()) {
            if (!mpAttention->Lockon()) {
                setHookshotSight();
            } else {
                mSightPacket.offDrawFlg();
            }
            dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK40000_e);
        } else {
            dComIfGp_setPlayerStatus0(0, daPyStts0_UNK40000_e);
        }
        m34D4 = ship->shape_angle.y;
    }
    return true;
}

/* 80141F2C-80142084       .text procShipBow_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipBow_init() {
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if (mCurProc == daPyProc_SHIP_BOW_e) {
        return false;
    }

    commonProcInit(daPyProc_SHIP_BOW_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    ship->m034D = 2;
    if (mDemo.getDemoMode() == 0x44) {
        mEquipItem = dItem_BOW_e;
    } else {
        mEquipItem = dComIfGp_getSelectItem(mReadyItemBtn);
    }
    setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, 5.0f);
    setBowModel();
    setBowReadyAnime();
    dComIfGp_setPlayerStatus0(0, daPyStts0_BOW_AIM_e | daPyStts0_SHIP_RIDE_e);
    setShipRidePos(0);
    m34D4 = ship->shape_angle.y;
    m34DA = 0;
    if (mpAttention->Lockon() && mDemo.getDemoMode() != 0x44) {
        m3570 = 1;
    } else {
        m3570 = 0;
    }

    return true;
}

/* 80142084-80142250       .text procShipBow__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipBow() {
    if ((mDemo.getDemoMode() != 0x44) && (changeShipEndProc())) {
        return true;
    }
    setShipRidePos(0);
    if (mDemo.getDemoMode() != 0x44) {
        dComIfGp_setDoStatus(7);
        if ((doTrigger()) ||
            (((!mpAttention->Lockon()) && (mActorKeepEquip.getActor() == NULL)) && (m3570 != 0)))
        {
            procShipPaddle_init();
            deleteEquipItem(TRUE);
            return true;
        }
    } else {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    daShip_c* iVar1 = (daShip_c*)dComIfGp_getShipActor();
    if (m_anm_heap_upper[UPPER_MOVE2_e].mIdx == LKANM_BCK_BOWWAIT) {
        setShipAttentionAnmSpeed(1.0f);
    }
    if ((mpAttention->Lockon()) && (mDemo.getDemoMode() != 0x44)) {
        setShipAttnetionBodyAngle();
        m3570 = 1;
    } else {
        m34DA = 0;
        setBodyAngleToCamera();
        m3570 = 0;
    }
    if (mpAttnActorLockOn == NULL) {
        shape_angle.y += (s16)(iVar1->shape_angle.y - m34D4);
    }
    m34D4 = iVar1->shape_angle.y;
    checkNextActionBowReady();
    m35EC = mFrameCtrlUpper[UPPER_MOVE2_e].getFrame();
    return true;
}

/* 80142250-80142300       .text procShipCannon_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipCannon_init() {
    if (mCurProc == daPyProc_SHIP_CANNON_e) {
        return false;
    }

    daShip_c* iVar1 = dComIfGp_getShipActor();
    commonProcInit(daPyProc_SHIP_CANNON_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    mVelocity = 0.0f;
    iVar1->m034D = 9;
    initShipBaseAnime();
    setShipRidePos(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK4_e);
    return true;
}

/* 80142300-80142388       .text procShipCannon__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipCannon() {
    if (changeShipEndProc()) {
        return true;
    }

    g_dComIfG_gameInfo.play.field_0x492d = 0x2c;
    if (dComIfGp_getDoStatus() == 0 && dComIfGp_getShipActor()->speedF >= 3.0f) {
        dComIfGp_setDoStatus(19);
    }
    setShipRidePos(1);
    return true;
}

/* 80142388-80142458       .text procShipCrane_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipCrane_init() {
    if (mCurProc == daPyProc_SHIP_CRANE_e) {
        return false;
    }

    daShip_c* iVar1 = dComIfGp_getShipActor();
    commonProcInit(daPyProc_SHIP_CRANE_e);
    deleteEquipItem(TRUE);
    gravity = 0.0f;
    mVelocity = 0.0f;
    iVar1->m034D = 10;
    if ((s16)iVar1->mCurrentRopeSegmentIndex != 0) {
        initShipCraneAnime();
    } else {
        initShipBaseAnime();
    }
    setShipRidePos(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK2_e);
    m34D4 = 0;
    return true;
}

/* 80142458-80142920       .text procShipCrane__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipCrane() {
    /* Nonmatching */
}

/* 80142920-80142A5C       .text procShipGetOff_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipGetOff_init() {
    if (mCurProc == daPyProc_SHIP_GET_OFF_e) {
        return false;
    }

    daShip_c* iVar1 = dComIfGp_getShipActor();
    commonProcInit(daPyProc_SHIP_GET_OFF_e);
    deleteEquipItem(TRUE);
    setSingleMoveAnime(ANM_DASH, daPy_HIO_move_c0::m.field_0x40, 0.0f, -1, 5.0f);
    mVelocity = 8.0f;
    gravity = 0.0f;
    shape_angle.y = iVar1->shape_angle.y + -0x4000;
    current.angle.y = shape_angle.y;
    m3570 = 0;
    m370C.x = current.pos.x + cM_ssin(shape_angle.y) * l_ship_ledge.x;
    m370C.y = iVar1->current.pos.y + l_ship_ledge.y;
    m370C.z = current.pos.z + cM_scos(shape_angle.y) * l_ship_ledge.x;
    iVar1->m034D = 5;
    mBodyAngle.y = 0;
    m35A0 = iVar1->current.pos.y;
    return true;
}

/* 80142A5C-80142C08       .text procShipGetOff__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipGetOff() {
    /* Nonmatching - branching */
    daShip_c* iVar1 = dComIfGp_getShipActor();
    if (iVar1 == 0) {
        checkNextMode(0);
    } else if (m3570 == 0) {
        current.pos.y = current.pos.y + (iVar1->current.pos.y - m35A0);
        cLib_chaseF(&current.pos.y, iVar1->current.pos.y + l_ship_ledge.y, 4.0f);
        m35A0 = iVar1->current.pos.y;
        s16 sVar3 = cLib_targetAngleY(&current.pos, &m370C);
        if (cLib_distanceAngleS(sVar3, shape_angle.y) >= 0x4000) {
            setSingleMoveAnime(
                ANM_JMPST, daPy_HIO_autoJump_c0::m.field_0x20, daPy_HIO_autoJump_c0::m.field_0x2C,
                daPy_HIO_autoJump_c0::m.field_0x2, daPy_HIO_autoJump_c0::m.field_0x30);
            gravity = daPy_HIO_autoJump_c0::m.field_0xC;
            mVelocity = daPy_HIO_ship_c0::m.field_0x10;
            speed.y = daPy_HIO_ship_c0::m.field_0x14;
            m3570 = 1;
            m34C2 = 1;
            iVar1->m034D = 6;
            onModeFlg(ModeFlg_MIDAIR);
        }
    } else {
        m34C2 = 1;
        dComIfGp_evmng_cutEnd(mStaffIdx);
        if (mAcch.ChkGroundHit()) {
            changeLandProc(daPy_HIO_autoJump_c0::m.field_0x24);
        } else {
            if (checkFanGlideProc(0)) {
                return true;
            } else if (speed.y < -gravity) {
                procFall_init(0, daPy_HIO_smallJump_c0::m.field_0x18);
                setTextureAnime(0x37, 0);
            }
        }
    }
    return true;
}

/* 80142C08-80142C9C       .text procShipRestart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipRestart_init() {
    daShip_c* iVar1 = dComIfGp_getShipActor();
    commonProcInit(daPyProc_SHIP_RESTART_e);
    gravity = 0.0f;
    iVar1->m034D = 2;
    setShipRidePos(1);
    setSingleMoveAnime(ANM_SEARESET, 1.0f, 0.0f, -1, -1.0f);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SHIP_RIDE_e);
    return true;
}

/* 80142C9C-80142D08       .text procShipRestart__9daPy_lk_cFv */
BOOL daPy_lk_c::procShipRestart() {
    if (dComIfGp_getShipActor() == NULL) {
        return checkNextMode(0);
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        procShipPaddle_init();
    }
    setShipRidePos(1);
    return true;
}
