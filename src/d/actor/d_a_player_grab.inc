/**
 * d_a_player_grab.inc
 *
 * Code relating to grabbing, holding, and throwing other actors.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_obj_barrel.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/d_camera.h"
#include "d/d_procname.h"
#include "f_op/f_op_camera.h"

/* 8013A85C-8013A890       .text checkGrabSpecialHeavyState__9daPy_lk_cFv */
BOOL daPy_lk_c::checkGrabSpecialHeavyState() {
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
    if (grab_actor != NULL) {
        if (fopAcM_GetName(grab_actor) == PROC_KB && ((fopAcM_GetParam(grab_actor) & 8) != 0)) {
            return true;
        }
    }
    return false;
}

/* 8013A890-8013A8B4       .text getGrabMissActor__9daPy_lk_cFv */
fopAc_ac_c* daPy_lk_c::getGrabMissActor() {
    if (mCurProc != ANM_MROLLL && mCurProc != ANM_MROLLLC) {
        return NULL;
    }
    return mActorKeepRope.getActor();
}

/* 8013A8B4-8013A904       .text setWeaponBlur__9daPy_lk_cFv */
void daPy_lk_c::setWeaponBlur() {
    JKRHeap* pJVar1 = setItemHeap();

    mSwBlur.mpPosBuffer = new (0x20) Vec[2 * 0x300];
    mDoExt_setCurrentHeap(pJVar1);
}

/* 8013A904-8013A97C       .text checkGrabBarrelSearch__9daPy_lk_cFi */
BOOL daPy_lk_c::checkGrabBarrelSearch(int param_0) {
    fopAc_ac_c* grab_actor;
    if (param_0 != 0) {
        if (mActorKeepGrab.getID() == fpcM_ERROR_PROCESS_ID_e) {
            return false;
        }
        grab_actor = fopAcM_SearchByID(mActorKeepGrab.getID());
    } else {
        grab_actor = mActorKeepGrab.getActor();
    }

    if (grab_actor != NULL && fopAcM_GetName(grab_actor) == PROC_Obj_Barrel) {
        return true;
    } else {
        return false;
    }
}

/* 8013A97C-8013AF84       .text setGrabItemPos__9daPy_lk_cFv */
void daPy_lk_c::setGrabItemPos() {
    static f32 magtail_offset = 40.0f;
    f32 dVar10;
    cXyz cStack_58;
    cXyz local_64;

    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
    if (grab_actor != NULL) {
        if (mCurProc == daPyProc_GRAB_READY_e) {
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(shape_angle.y - m34D4);
            mDoMtx_stack_c::multVec(&m370C, &grab_actor->current.pos);
        } else {
            s8 sVar2 = current.roomNo;
            grab_actor->tevStr.mRoomNo = sVar2;
            grab_actor->tevStr.mEnvrIdxOverride = tevStr.mEnvrIdxOverride;
            grab_actor->current.roomNo = sVar2;
            if (!checkNoResetFlg0(daPyFlg0_UNK400) && checkGrabBarrelSearch(0) && !doButton()) {
                onNoResetFlg0(daPyFlg0_UNK400);
                for (int i = 0; i < 3; i++) {
                    mAcchCir[i].SetWallR(50.0f);
                }
            }
            if (mCurProc == daPyProc_GRAB_UP_e) {
                cLib_chaseAngleS(&grab_actor->shape_angle.y, shape_angle.y, 0x1000);
            } else {
                if (mCurProc != daPyProc_DEMO_STAND_ITEM_PUT_e) {
                    grab_actor->shape_angle.y = shape_angle.y;
                }
                grab_actor->shape_angle.z = m351C;
                if (checkNoResetFlg0(daPyFlg0_UNK400)) {
                    if (mCurProc == daPyProc_GRAB_PUT_e) {
                        dVar10 = 0.0f;
                    } else if (mCurProc == daPyProc_GRAB_WAIT_e || mCurProc == daPyProc_WAIT_TURN_e) {
                        dVar10 = -115.0f;
                    } else {
                        dVar10 = -85.0f;
                    }
                    field_0x2b0 += m35D8;
                    cLib_addCalc(&field_0x2b0, dVar10, 0.5f, 20.0f, 1.0f);
                    if (field_0x2b0 < -85.0f) {
                        m35D8 = field_0x2b0 - -85.0f;
                        field_0x2b0 = -85.0f;
                    } else {
                        m35D8 = 0.0f;
                    }
                    s16 target_slant_angle;
                    if (speedF > 0.0f && m34C3 != 0) {
                        f32 rad_angle = (M_PI * 2) * mFrameCtrlUnder[UNDER_MOVE1_e].getFrame() /
                                        mFrameCtrlUnder[UNDER_MOVE1_e].getEnd();
                        target_slant_angle = 0x800 * cM_fsin(rad_angle);
                    } else {
                        target_slant_angle = 0;
                    }
                    daObjBarrel::Act_c* barrel = (daObjBarrel::Act_c*)grab_actor;
                    s16 curr_slant_angle = barrel->get_slant_angle();
                    cLib_addCalcAngleS(&curr_slant_angle, target_slant_angle, 5, 0x200, 0x80);
                    barrel->set_slant_angle(curr_slant_angle);
                }
            }
            if (mCurProc == daPyProc_GRAB_UP_e) {
                cStack_58 = grab_actor->current.pos;
            }
            grab_actor->current.pos = ((mLeftHandPos + mRightHandPos) * 0.5f);
            grab_actor->current.pos.y += field_0x2b0;
            f32 fVar1;
            if (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_GRABUP) {
                dVar10 =
                    1.0f - ((mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - mFrameCtrlUnder[UNDER_MOVE0_e].getStart()) /
                            (mFrameCtrlUnder[UNDER_MOVE0_e].getEnd() - mFrameCtrlUnder[UNDER_MOVE0_e].getStart()));
                fVar1 = m35C8 * dVar10;
                grab_actor->current.pos.x += fVar1 * cM_ssin(shape_angle.y);
                grab_actor->current.pos.z += fVar1 * cM_scos(shape_angle.y);
                if (mCurProc == daPyProc_GRAB_PUT_e) {
                    grab_actor->current.pos.y += (-18.07f * dVar10);
                } else {
                    grab_actor->current.pos.y += (-16.41f * dVar10);
                }
                if (mCurProc == daPyProc_GRAB_PUT_e) {
                    local_64.set(grab_actor->current.pos.x, current.pos.y + 125.0f, grab_actor->current.pos.z);
                    mGndChk.SetPos(&local_64);
                    f32 dVar9 = dComIfG_Bgsp()->GroundCross(&mGndChk);
                    if (dVar9 > grab_actor->current.pos.y) {
                        grab_actor->speedF = 0.0f;
                        grab_actor->current.pos.y = dVar9;
                        freeGrabItem();
                        return;
                    }
                }
                if (fopAcM_GetName(grab_actor) == PROC_MT) {
                    grab_actor->current.pos.y += magtail_offset * (1.0f - dVar10);
                }
            } else if (fopAcM_GetName(grab_actor) == PROC_MT) {
                fVar1 = -magtail_offset * cM_ssin(m351C);
                grab_actor->current.pos.x += fVar1 * cM_scos(shape_angle.y);
                grab_actor->current.pos.y += magtail_offset * cM_scos(m351C);
                grab_actor->current.pos.z += -fVar1 * cM_ssin(shape_angle.y);
            }
            if (mCurProc == daPyProc_GRAB_UP_e && grab_actor->current.pos.y < cStack_58.y) {
                grab_actor->current.pos = cStack_58;
            }
            if (checkNoResetFlg0(daPyFlg0_UNK400)) {
                m35CC = 0.0f;
            } else if (checkModeFlg(ModeFlg_MIDAIR) && speed.y < 0.0f) {
                m35CC -= 0.2f * speed.y;
                if (m35CC > 40.0f) {
                    m35CC = 40.0f;
                }
            } else {
                cLib_chaseF(&m35CC, 0.0f, 5.0f);
            }
            grab_actor->current.pos.y = grab_actor->current.pos.y + m35CC;
        }
    }
}

/* 8013AF84-8013B05C       .text freeGrabItem__9daPy_lk_cFv */
void daPy_lk_c::freeGrabItem() {
    daObjBarrel::Act_c* barrel = static_cast<daObjBarrel::Act_c*>(mActorKeepGrab.getActor());

    if (barrel != NULL) {
        fopAcM_cancelCarryNow(barrel);
        barrel->shape_angle.z = 0;
        if (checkGrabBarrelSearch(0)) {
            barrel->m61C = 0;
        }
    }
    mActorKeepGrab.clearData();
    if (checkGrabAnime()) {
        resetActAnimeUpper(UPPER_MOVE2_e, daPy_HIO_basic_c0::m.field_0xC);
    }
    field_0x2b0 = 0.0f;
    m35CC = 0.0f;
    offNoResetFlg0(daPyFlg0_UNK400);
    dComIfGp_clearPlayerStatus1(0, daPyStts1_UNK40000_e);
}

/* 8013B05C-8013B458       .text checkNextActionGrab__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionGrab() {
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
    if (grab_actor == NULL) {
        return false;
    }

    int iVar3 = checkGrabBarrelSearch(0);
    if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e) && !checkGrabSpecialHeavyState()) {
        dComIfGp_setRStatus(dActStts_THROW_e);
        dComIfGp_setDoStatus(dActStts_THROW_e);
    } else {
        dComIfGp_setRStatus(dActStts_DROP_e);
    }
    if (mpAttnActorLockOn == NULL && mpAttnEntryA != NULL && iVar3 == 0 &&
        mpAttnEntryA->mType == fopAc_Attn_TYPE_DOOR_e && fopAcM_CheckStatus(grab_actor, fopAcStts_UNK2000000_e))
    {
        dComIfGp_setDoStatus(dActStts_OPEN_e);
    } else if (iVar3 != 0) {
        dComIfGp_setDoStatus(dActStts_DROP_e);
    } else if (mpAttention->Lockon()) {
        int direction = getDirectionFromShapeAngle();
        if (mStickDistance <= 0.05f ||
            (mStickDistance > 0.05f && (direction == DIR_FORWARD || direction == DIR_BACKWARD)))
        {
            dComIfGp_setDoStatus(dActStts_THROW_e);
        }
    } else {
        dComIfGp_setDoStatus(dActStts_THROW_e);
    }
    if (setHintActor() && doTrigger()) {
        fopAcM_orderZHintEvent(this, dComIfGp_att_getZHint());
        return true;
    }
    if (checkSetItemTrigger(dItem_MAGIC_ARMOR_e, 1) ||
        (checkNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD) && checkSetItemTrigger(dItem_MAGIC_ARMOR_e, 0)))
    {
        changeDragonShield(1);
        return true;
    }
    if (checkSetItemTrigger(dItem_IRON_BOOTS_e, 1) ||
        (checkEquipHeavyBoots() && checkSetItemTrigger(dItem_IRON_BOOTS_e, 0)))
    {
        return procBootsEquip_init(dItem_IRON_BOOTS_e);
    } else if (fopAcM_GetName(grab_actor) == PROC_BOMB && checkSetItemTrigger(dItem_BOMB_BAG_e, 0)) {
        return procGrabThrow_init(0);
    }
    if (cancelTrigger() && checkSwordEquip() && iVar3 == 0) {
        if (dComIfGp_getRStatus() == dActStts_THROW_e) {
            return procGrabThrow_init(1);
        }
        freeGrabItem();
        setAnimeEquipSword(0);
        return true;
    }
    if (doTrigger() && !checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK20000000 | daPyFlg0_UNK80000000)) &&
        dComIfGp_getDoStatus() == dActStts_OPEN_e)
    {
        fopAcM_orderDoorEvent(this, mpAttnActorA);
        return true;
    }
    if ((doTrigger() && dComIfGp_getDoStatus() == dActStts_THROW_e) ||
        (dComIfGp_getRStatus() == dActStts_THROW_e && (allTrigger() || spActionTrigger())))
    {
        if (cancelTrigger()) {
            return procGrabThrow_init(1);
        } else {
            return procGrabThrow_init(0);
        }
    }
    if ((allTrigger() || spActionTrigger()) && (!doTrigger() || dComIfGp_getDoStatus() != dActStts_BLANK_e)) {
        return procGrabPut_init();
    } else {
        return false;
    }
}

/* 8013B458-8013B56C       .text initGrabNextMode__9daPy_lk_cFv */
void daPy_lk_c::initGrabNextMode() {
    if (fopAcM_CheckStatus(mActorKeepGrab.getActor(), fopAcStts_UNK10000_e)) {
        if (!checkGrabSpecialHeavyState()) {
            procGrabHeavyWait_init();
        } else {
            if (!checkGrabAnime()) {
                setActAnimeUpper(LKANM_BCK_GRABWAITB, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
            }
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
            checkNextMode(0);
        }
    } else {
        if (!checkGrabAnime()) {
            setActAnimeUpper(LKANM_BCK_GRABWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
        }
        m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        checkNextMode(0);
    }
}

/* 8013B56C-8013B6F4       .text procGrabReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabReady_init() {
    commonProcInit(daPyProc_GRAB_READY_e);
    mVelocity = 0.0f;
    if (mEquipItem == daPyItem_NONE_e) {
        if (checkEquipAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        setSingleMoveAnime(
            ANM_GRABP,
            daPy_HIO_grab_c0::m.field_0x20,
            daPy_HIO_grab_c0::m.field_0x24,
            daPy_HIO_grab_c0::m.field_0x0,
            daPy_HIO_grab_c0::m.field_0x28
        );
        mProcVar0.m3570 = 1;
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        setAnimeUnequip();
        mProcVar0.m3570 = 0;
    }
    if ((dComIfGs_getSelectEquip(2) == dItem_POWER_BRACELETS_e ||
         !fopAcM_CheckStatus(mpAttnActorA, fopAcStts_UNK10000_e)) &&
        !fopAcM_CheckStatus(mpAttnActorA, fopAcStts_CARRY_e))
    {
        fopAcM_setCarryNow(mpAttnActorA, 1);
        mActorKeepGrab.setData(mpAttnActorA);
        mActorKeepRope.clearData();
    } else {
        mActorKeepRope.setData(mpAttnActorA);
        freeGrabItem();
    }
    if (fopAcM_GetName(mpAttnActorA) == PROC_BOKO) {
        daBoko_c* boko = static_cast<daBoko_c*>(mpAttnActorA);
        boko->mCurrentAction = 3;
    }
    shape_angle.y = fopAcM_searchActorAngleY(this, mpAttnActorA);
    current.angle.y = shape_angle.y;
    m34D4 = shape_angle.y;
    m370C = mpAttnActorA->current.pos - m3748;
    return true;
}

/* 8013B6F4-8013B8A0       .text procGrabReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabReady() {
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();

    if (grab_actor == NULL && mActorKeepRope.getActor() == NULL) {
        return checkNextMode(0);
    }
    if (mProcVar0.m3570 == 2 && (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f)) {
        procGrabUp_init();
    } else if (mProcVar0.m3570 == 1 && (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f)) {
        if (grab_actor != NULL) {
            if (fopAcM_GetName(grab_actor) == PROC_BOKO) {
                mEquipItem = daPyItem_BOKO_e;
                mActorKeepEquip = mActorKeepGrab;
                mActorKeepGrab.clearData();
                setWeaponBlur();
                checkNextMode(0);
            } else if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e | fopAcStts_UNK8000000_e)) {
                f32 fVar1;
                if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK8000000_e)) {
                    fVar1 = daPy_HIO_grab_c0::m.field_0xA4;
                } else {
                    fVar1 = daPy_HIO_grab_c0::m.field_0xA8;
                }
                setSingleMoveAnime(
                    ANM_GRABNG,
                    fVar1,
                    daPy_HIO_grab_c0::m.field_0x40,
                    daPy_HIO_grab_c0::m.field_0x10,
                    daPy_HIO_grab_c0::m.field_0x44
                );
                mProcVar0.m3570 = 2;
            } else {
                procGrabUp_init();
            }
        } else if (mActorKeepRope.getActor() != NULL) {
            procGrabMiss_init();
        } else {
            checkNextMode(0);
        }
    } else if (mProcVar0.m3570 == 0 && checkNoUpperAnime()) {
        setSingleMoveAnime(
            ANM_GRABP,
            daPy_HIO_grab_c0::m.field_0x20,
            daPy_HIO_grab_c0::m.field_0x24,
            daPy_HIO_grab_c0::m.field_0x0,
            daPy_HIO_grab_c0::m.field_0x28
        );
        mProcVar0.m3570 = 1;
    }
    return true;
}

/* 8013B8A0-8013BA50       .text procGrabUp_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabUp_init() {
    commonProcInit(daPyProc_GRAB_UP_e);
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
    s16 sVar1;
    if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e | fopAcStts_UNK8000000_e)) {
        sVar1 = daPy_HIO_grab_c0::m.field_0x12;
    } else {
        sVar1 = daPy_HIO_grab_c0::m.field_0x2;
    }
    setSingleMoveAnime(
        ANM_GRABUP,
        daPy_HIO_grab_c0::m.field_0x2C,
        daPy_HIO_grab_c0::m.field_0x30,
        sVar1,
        daPy_HIO_grab_c0::m.field_0x38
    );
    m370C = mActorKeepGrab.getActor()->current.pos - m3748;
    m35C8 = m370C.absXZ() - 47.0f;
    if (fopAcM_CheckStatus(mActorKeepGrab.getActor(), fopAcStts_UNK10000_e)) {
        voiceStart(16);
    } else {
        voiceStart(15);
    }
    fopAcM_setStageLayer(mActorKeepGrab.getActor());
    onResetFlg0(daPyRFlg0_GRAB_UP_START);
    if (fopAcM_GetName(mActorKeepGrab.getActor()) == PROC_Stone2) {
        dComIfGp_setPlayerStatus1(0, daPyStts1_UNK40000_e);
    }
    return true;
}

/* 8013BA50-8013BBBC       .text procGrabUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabUp() {
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
    if (grab_actor == NULL) {
        return checkNextMode(0);
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        onResetFlg0(daPyRFlg0_GRAB_UP_END);
        if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e | fopAcStts_UNK8000000_e)) {
            procGrabRebound_init();
        } else {
            initGrabNextMode();
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_grab_c0::m.field_0x34) {
        if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e | fopAcStts_UNK8000000_e)) {
            if (mStickDistance > 0.05f) {
                onResetFlg0(daPyRFlg0_GRAB_UP_END);
                procGrabRebound_init();
            }
        } else {
            if (!checkGrabAnime()) {
                setActAnimeUpper(LKANM_BCK_GRABWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
                m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
            }
            if (checkNextMode(1)) {
                onResetFlg0(daPyRFlg0_GRAB_UP_END);
                if (checkGrabAnime()) {
                    m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
                }
            }
        }
    }
    return true;
}

/* 8013BBBC-8013BC40       .text procGrabMiss_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabMiss_init() {
    commonProcInit(daPyProc_GRAB_MISS_e);
    setSingleMoveAnime(
        ANM_GRABNG,
        daPy_HIO_grab_c0::m.field_0x3C,
        daPy_HIO_grab_c0::m.field_0x40,
        daPy_HIO_grab_c0::m.field_0x4,
        daPy_HIO_grab_c0::m.field_0x44
    );
    mProcVar0.m3570 = 0;
    m34D0 = daPy_HIO_grab_c0::m.field_0x6;
    dComIfGs_onEventBit(0x4020);
    return true;
}

/* 8013BC40-8013BD30       .text procGrabMiss__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabMiss() {
    if (mActorKeepRope.getActor() == NULL) {
        checkNextMode(0);
    }
    if (mProcVar0.m3570 == 0) {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            if (m34D0 > 0) {
                m34D0--;
            } else {
                setSingleMoveAnime(
                    ANM_GRABP,
                    daPy_HIO_grab_c0::m.field_0x48,
                    daPy_HIO_grab_c0::m.field_0x4C,
                    daPy_HIO_grab_c0::m.field_0x8,
                    daPy_HIO_grab_c0::m.field_0x54
                );
                mProcVar0.m3570 = 1;
                freeGrabItem();
            }
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > -0.01f) {
        checkNextMode(0);
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < daPy_HIO_grab_c0::m.field_0x50) {
        checkNextMode(1);
    }
    return true;
}

/* 8013BD30-8013BE10       .text procGrabThrow_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procGrabThrow_init(int param_0) {
    if (mCurProc == daPyProc_GRAB_THROW_e) {
        return false;
    }
    commonProcInit(daPyProc_GRAB_THROW_e);
    if (fopAcM_CheckStatus(mActorKeepGrab.getActor(), fopAcStts_UNK10000_e)) {
        setSingleMoveAnime(
            ANM_GRABRE,
            daPy_HIO_grab_c0::m.field_0x94,
            daPy_HIO_grab_c0::m.field_0x98,
            daPy_HIO_grab_c0::m.field_0x1C,
            daPy_HIO_grab_c0::m.field_0xA0
        );
        m3574 = 0;
    } else {
        setSingleMoveAnime(
            ANM_GRABTHROW,
            daPy_HIO_grab_c0::m.field_0x58,
            daPy_HIO_grab_c0::m.field_0x5C,
            daPy_HIO_grab_c0::m.field_0xA,
            daPy_HIO_grab_c0::m.field_0x64
        );
        m3574 = 1;
    }
    m35A0 = mVelocity;
    dComIfGp_clearPlayerStatus1(0, daPyStts1_UNK40000_e);
    mProcVar0.m3570 = param_0;
    return true;
}

/* 8013BE10-8013C020       .text procGrabThrow__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabThrow() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();

    cLib_addCalc(
        &mVelocity, 0.0f, daPy_HIO_move_c0::m.field_0x24, daPy_HIO_move_c0::m.field_0x1C, daPy_HIO_move_c0::m.field_0x20
    );
    if (m3574 == 0) {
        if (frameCtrl.getRate() < 0.01f) {
            setSingleMoveAnime(
                ANM_GRABTHROW,
                daPy_HIO_grab_c0::m.field_0x58,
                daPy_HIO_grab_c0::m.field_0x5C,
                daPy_HIO_grab_c0::m.field_0xA,
                daPy_HIO_grab_c0::m.field_0x64
            );
            m3574 = 1;
        }
        return true;
    }

    if (frameCtrl.checkPass(daPy_HIO_grab_c0::m.field_0x8C) && grab_actor != NULL) {
        grab_actor->current.angle.y = shape_angle.y;
        grab_actor->speedF = daPy_HIO_grab_c0::m.field_0x84;
        grab_actor->speed.y = daPy_HIO_grab_c0::m.field_0x88;
        dComIfGp_getCamera(mCameraInfoIdx)->mCamera.ForceLockOn(mActorKeepGrab.getID());
        if (fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e)) {
            voiceStart(18);
        } else if (fopAcM_GetName(grab_actor) == PROC_BOMB || fopAcM_GetName(grab_actor) == PROC_Bomb2) {
            voiceStart(0);
        } else {
            voiceStart(17);
        }
        freeGrabItem();
    }

    if (frameCtrl.getRate() < 0.01f) {
        if (mProcVar0.m3570 != 0) {
            mProcVar0.m3570 = 0;
            setAnimeEquipSword(0);
        }
        checkNextMode(0);
    } else if (frameCtrl.getFrame() > daPy_HIO_grab_c0::m.field_0x60) {
        if (mProcVar0.m3570 != 0) {
            mProcVar0.m3570 = 0;
            setAnimeEquipSword(0);
        }
        checkNextMode(1);
    }
    return true;
}

/* 8013C020-8013C124       .text procGrabPut_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabPut_init() {
    if (mCurProc == daPyProc_GRAB_PUT_e) {
        return false;
    }

    commonProcInit(daPyProc_GRAB_PUT_e);
    if (checkGrabWear()) {
        mProcVar0.m3570 = 1;
        setSingleMoveAnime(ANM_GRABWAIT, daPy_HIO_grab_c0::m.field_0x78, 0.0f, -1, daPy_HIO_grab_c0::m.field_0x7C);
    } else {
        mProcVar0.m3570 = 0;
        setSingleMoveAnime(
            ANM_GRABUP,
            daPy_HIO_grab_c0::m.field_0x68,
            daPy_HIO_grab_c0::m.field_0x6C,
            daPy_HIO_grab_c0::m.field_0xC,
            daPy_HIO_grab_c0::m.field_0x74
        );
    }
    mVelocity = 0.0f;
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();
    if (grab_actor != NULL) {
        m370C = grab_actor->current.pos;
    } else {
        m370C = current.pos;
    }
    onResetFlg0(daPyRFlg0_GRAB_PUT_START);
    return true;
}

/* 8013C124-8013C504       .text procGrabPut__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabPut() {
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();

    if (grab_actor == NULL) {
        if (mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK38_e) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            return true;
        } else {
            return checkNextMode(0);
        }
    }

    if (mProcVar0.m3570 == 1) {
        if (!checkGrabWear()) {
            mProcVar0.m3570 = 0;
            setSingleMoveAnime(
                ANM_GRABUP,
                daPy_HIO_grab_c0::m.field_0x68,
                daPy_HIO_grab_c0::m.field_0x6C,
                daPy_HIO_grab_c0::m.field_0xC,
                daPy_HIO_grab_c0::m.field_0x74
            );
        } else {
            return true;
        }
    }

    cXyz local_2c;
    local_2c.set(
        grab_actor->current.pos.x + m35C8 * cM_ssin(shape_angle.y),
        grab_actor->current.pos.y,
        grab_actor->current.pos.z + m35C8 * cM_scos(shape_angle.y)
    );
    mLinkLinChk.Set(&m370C, &local_2c, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        if (cBgW_CheckBWall(triPla->GetNP()->y)) {
            cXyz local_44 = (local_2c - mLinkLinChk.GetCross());
            f32 dVar7 = local_44.abs();
            f32 dVar5 = local_44.absXZ();
            if (dVar5 > 0.01f) {
                float dVar6 = dVar7 / dVar5;
                local_44.x *= dVar6;
                local_44.z *= dVar6;
            } else {
                local_44.x *= dVar7;
                local_44.z *= dVar7;
            }
            current.pos.x -= local_44.x;
            current.pos.z -= local_44.z;
            grab_actor->current.pos.x -= local_44.x;
            grab_actor->current.pos.z -= local_44.z;
        }
    }

    m370C = grab_actor->current.pos;
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > -0.01f) {
        grab_actor->speedF = 0.0f;
        freeGrabItem();
        if (mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK38_e) {
            dComIfGp_evmng_cutEnd(mStaffIdx);
        } else {
            checkNextMode(0);
        }
    } else if ((mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < daPy_HIO_grab_c0::m.field_0x70) && checkNextMode(1)) {
        grab_actor->speedF = 0.0f;
        freeGrabItem();
    }

    return true;
}

/* 8013C504-8013C678       .text procGrabWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabWait_init() {
    if (mCurProc == daPyProc_GRAB_WAIT_e) {
        return false;
    }
    commonProcInit(daPyProc_GRAB_WAIT_e);
    if (checkGrabSpecialHeavyState()) {
        setSingleMoveAnime(ANM_GRABWAITB, daPy_HIO_grab_c0::m.field_0x90, 0.0f, -1, daPy_HIO_grab_c0::m.field_0x7C);
        if (!checkGrabAnime()) {
            setActAnimeUpper(LKANM_BCK_GRABWAITB, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
        }
    } else {
        setSingleMoveAnime(ANM_GRABWAIT, daPy_HIO_grab_c0::m.field_0x78, 0.0f, -1, daPy_HIO_grab_c0::m.field_0x7C);
        if (!checkGrabAnime()) {
            setActAnimeUpper(LKANM_BCK_GRABWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
        }
    }
    m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    m35A0 = 0.0f;
    if (m35D8 <= -29.0f) {
        mProcVar0.m3570 = 1;
    } else {
        mProcVar0.m3570 = 0;
    }
    return true;
}

/* 8013C678-8013C914       .text procGrabWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabWait() {
    if (mActorKeepGrab.getActor() == NULL) {
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        return checkNextMode(0);
    }

    if (mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    } else {
        setSpeedAndAngleNormal(daPy_HIO_move_c0::m.field_0x0);
    }
    if (m35D8 <= -29.0f) {
        if ((mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > 0.0f) && mProcVar0.m3570 == 0) {
            mProcVar0.m3570 = 1;
            if (m_anm_heap_under[UNDER_MOVE0_e].mIdx == LKANM_BCK_GRABWAIT) {
                seStartMapInfo(JA_SE_LK_BARREL_PUT_ON);
            }
        }
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
    } else {
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(daPy_HIO_grab_c0::m.field_0x78);
    }
    if (checkNextMode(0)) {
        if (checkGrabAnime()) {
            m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        }
    } else if (shape_angle.y != m34DE && !mpAttention->Lockon()) {
        float fVar2;
        if (checkNoResetFlg1(daPyFlg1_UNK800000)) {
            fVar2 = -1.0f;
        } else {
            fVar2 = daPy_HIO_basic_c0::m.field_0xC;
        }
        setBlendMoveAnime(fVar2);
        m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        m35A0 = 0.005f * (short)(shape_angle.y - m34DE);
        onNoResetFlg1(daPyFlg1_UNK800000);
    } else if (checkNoResetFlg1(daPyFlg1_UNK800000)) {
        if (checkGrabSpecialHeavyState()) {
            setSingleMoveAnime(ANM_GRABWAITB, daPy_HIO_grab_c0::m.field_0x90, 0.0f, -1, daPy_HIO_grab_c0::m.field_0x7C);
        } else {
            setSingleMoveAnime(ANM_GRABWAIT, daPy_HIO_grab_c0::m.field_0x78, 0.0f, -1, daPy_HIO_grab_c0::m.field_0x7C);
        }
        m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
        m35A0 = 0.0f;
        offNoResetFlg1(daPyFlg1_UNK800000);
    }
    return true;
}

/* 8013C914-8013C9AC       .text procGrabHeavyWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabHeavyWait_init() {
    commonProcInit(daPyProc_GRAB_HEAVY_WAIT_e);
    setSingleMoveAnime(ANM_GRABWAITB, daPy_HIO_grab_c0::m.field_0x90, 0.0f, -1, daPy_HIO_grab_c0::m.field_0x7C);
    setActAnimeUpper(LKANM_BCK_GRABWAITB, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    m35A0 = 0.0f;
    return true;
}

/* 8013C9AC-8013CB78       .text procGrabHeavyWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabHeavyWait() {
    if (mActorKeepGrab.getActor() == NULL) {
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        return checkNextMode(0);
    }

    if (!mpAttention->Lockon() && mStickDistance > 0.05f) {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34E8,
            daPy_HIO_grab_c0::m.field_0x16,
            daPy_HIO_grab_c0::m.field_0x18,
            daPy_HIO_grab_c0::m.field_0x1A
        );
        s16 y_diff = shape_angle.y - current.angle.y;
        m35A0 = y_diff / (f32)daPy_HIO_grab_c0::m.field_0x18;
        current.angle.y = shape_angle.y;
        f32 fVar1;
        if (checkNoResetFlg1(daPyFlg1_UNK800000)) {
            fVar1 = -1.0f;
        } else {
            fVar1 = daPy_HIO_basic_c0::m.field_0xC;
        }
        setBlendMoveAnime(fVar1);
        m_pbCalc[PART_UPPER_e]->setRatio(2, 1.0f);
        onNoResetFlg1(daPyFlg1_UNK800000);
    } else {
        m35A0 = 0.0f;
        if (checkNoResetFlg1(daPyFlg1_UNK800000)) {
            setSingleMoveAnime(ANM_GRABWAITB, daPy_HIO_grab_c0::m.field_0x90, 0.0f, -1, daPy_HIO_grab_c0::m.field_0x7C);
            m_pbCalc[PART_UPPER_e]->setRatio(2, 0.0f);
            offNoResetFlg1(daPyFlg1_UNK800000);
        }
    }

    if (mActorKeepGrab.getActor() == NULL) {
        checkNextMode(0);
    } else {
        checkNextActionGrab();
    }

    return true;
}

/* 8013CB78-8013CBD0       .text procGrabRebound_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabRebound_init() {
    commonProcInit(daPyProc_GRAB_REBOUND_e);
    setSingleMoveAnime(
        ANM_GRABRE,
        daPy_HIO_grab_c0::m.field_0x94,
        daPy_HIO_grab_c0::m.field_0x98,
        daPy_HIO_grab_c0::m.field_0xE,
        daPy_HIO_grab_c0::m.field_0xA0
    );
    return true;
}

/* 8013CBD0-8013CC64       .text procGrabRebound__9daPy_lk_cFv */
BOOL daPy_lk_c::procGrabRebound() {
    fopAc_ac_c* grab_actor = mActorKeepGrab.getActor();

    if (grab_actor == NULL) {
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        return checkNextMode(0);
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        initGrabNextMode();
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_grab_c0::m.field_0x9C &&
               fopAcM_CheckStatus(grab_actor, fopAcStts_UNK10000_e))
    {
        initGrabNextMode();
    }
    return true;
}
