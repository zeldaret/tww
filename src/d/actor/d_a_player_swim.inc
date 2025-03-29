/**
 * d_a_player_swim.inc
 *
 * Code relating to swimming.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "f_op/f_op_kankyo_mng.h"

daPy_HIO_swim_c0 l_HIO_swim_c0;
daPy_HIO_wallCatch_c0 l_HIO_wallCatch_c0;
daPy_HIO_turn_c0 l_HIO_turn_c0;

/* 8013CC64-8013CF2C       .text setSpeedAndAngleSwim__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleSwim() {
    float fVar1;
    short oldAngleY;

    BOOL bVar3 = false;

    if (mCurProc != 0x35) {
        if (!mpAttention->Lockon()) {
            if (mStickDistance > 0.05f) {
                oldAngleY = shape_angle.y;

                if (getDirectionFromShapeAngle() == 1) {
                    mSwimTailEcallBack[0].field_0x04 = 1;
                    mSwimTailEcallBack[0].field_0x20 = NULL;

                    mSwimTailEcallBack[1].field_0x04 = 1;
                    mSwimTailEcallBack[1].field_0x20 = NULL;

                    shape_angle.y = m34E8;
                    current.angle.y = m34E8;
                }
                else {
                    cLib_addCalcAngleS(&shape_angle.y, m34E8, l_HIO_swim_c0.m.field_0x8, l_HIO_swim_c0.m.field_0x4, l_HIO_swim_c0.m.field_0x6);     
                }

                fVar1 = mStickDistance * 3.0f * cM_scos(shape_angle.y - oldAngleY);
            }
            else {
                fVar1 = 0.0f;
            }

            cLib_addCalcAngleS(&current.angle.y, shape_angle.y, 2, 0x2000, 0x1000);

            mMaxNormalSpeed = l_HIO_swim_c0.m.field_0xC;
        }
        else {
            setShapeAngleToAtnActor();

            if (mStickDistance > 0.05f) {
                oldAngleY = current.angle.y;

                if (getDirectionFromCurrentAngle() == 1) {
                    mSwimTailEcallBack[0].field_0x04 = 1;
                    mSwimTailEcallBack[0].field_0x20 = NULL;

                    mSwimTailEcallBack[1].field_0x04 = 1;
                    mSwimTailEcallBack[1].field_0x20 = NULL;

                    fVar1 = 0.0f;
                    bVar3 = TRUE;
                }
                else {
                    cLib_addCalcAngleS(&current.angle.y, m34E8, l_HIO_swim_c0.m.field_0x8, l_HIO_swim_c0.m.field_0x4, l_HIO_swim_c0.m.field_0x6);
                    fVar1 = mStickDistance * 3.0f * cM_scos(current.angle.y - oldAngleY);
                }
            }
            else {
                fVar1 = 0.0f;
            }
            
            mMaxNormalSpeed = ((cM_scos(current.angle.y - shape_angle.y) + 1.0f) * 0.25f + 0.5f) * l_HIO_swim_c0.m.field_0xC;
        }
    }
    else {
        fVar1 = 0.0f;
        mMaxNormalSpeed = l_HIO_swim_c0.m.field_0xC;
    }

    setNormalSpeedF(fVar1, l_HIO_swim_c0.m.field_0x18, l_HIO_swim_c0.m.field_0x1C, l_HIO_swim_c0.m.field_0x20);
    
    if (bVar3 && mVelocity < 5.0f) {
        current.angle.y = m34E8;
        mVelocity = 0.0f;
    }
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e)) {
        mVelocity = 0.0f;
    }
}

/* 8013CF2C-8013CFC0       .text checkNextModeSwim__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextModeSwim() {
    BOOL res;

    if (mpAttnEntryA && mpAttnEntryA->mType == 7) { //Action_Ship? fopAc_Attn_ACTION_SHIP_e is 0x80 so not sure why Ghidra is saying this 
        dComIfGp_setDoStatus(0x1C); // Show `Get In` on the A Button? Ghidra says `GetInShip` is the symbol
        if (mItemTrigger & 1) { 
            return procShipReady_init();
        }
    }

    if (setTalkStatus() && (mItemTrigger & 1)) {
        res = fopAcM_orderTalkEvent(this, mpAttnActorA);
    }
    else {
        res = FALSE;
    }
    return res;
}

/* 8013CFC0-8013D1B0       .text changeSwimProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeSwimProc() {
    float fVar1;
    BOOL res;
    cXyz local_18;
    
    if (checkNoResetFlg0(daPyFlg0_UNK80) && !checkModeFlg(0x42000) && !checkNoControll() && !checkPlayerDemoMode(daPy_demo_c::DEMO_UNK11_e) && m35D0 - current.pos.y > l_HIO_swim_c0.m.field_0x24) {
        dComIfGp_setItemTimeCount(900);
        dComIfGp_setItemTimeMax(1);
        g_dComIfG_gameInfo.play.field_0x48c8 = 900; // Some inline? Debug maps make no mention of this function but perhaps it was used earlier?

        offNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
        offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);

        endFlameDamageEmitter();

        offNoResetFlg0(daPyFlg0_UNK100);

        mMaxNormalSpeed = l_HIO_swim_c0.m.field_0xC;
        mVelocity *= 0.75f;

        if (mVelocity >= mMaxNormalSpeed) {
          mVelocity = mMaxNormalSpeed;
        }

        m35C4 = 0.0f;

        setSwimTimerStartStop();
        
        if (checkModeFlg(2)) {
            current.pos.y += l_HIO_swim_c0.m.field_0x24;
            speed.y = mOldSpeed.y * l_HIO_swim_c0.m.field_0x10;

            if (speed.y < l_HIO_swim_c0.m.field_0x14) {
                speed.y = l_HIO_swim_c0.m.field_0x14;
            }
            else if (speed.y > 0.0f) {
                speed.y = 0.0f;
            }

            float oldSpeedY = mOldSpeed.y * mOldSpeed.y * 0.0004f + 0.2f;

            if (oldSpeedY > 1.0f) {
                oldSpeedY = 1.0f;
            }

            local_18.x = current.pos.x;
            local_18.y = m35D0;
            local_18.z = current.pos.z;
            fopKyM_createWpillar(&local_18, 1.0f, oldSpeedY, 0);
            seStartOnlyReverb(JA_SE_LK_INTO_WATER);
            res = procSwimWait_init(0);
        }
        else {
            res = procSwimUp_init(0);
        }
    }
    else {
        res = 0;
    }
    return res;
}

/* 8013D1B0-8013D2AC       .text changeSwimUpProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeSwimUpProc() {
    if (speed.y < l_HIO_swim_c0.m.field_0x68) {
        speed.y += l_HIO_swim_c0.m.field_0x64;
        if (speed.y > l_HIO_swim_c0.m.field_0x68) {
            speed.y = l_HIO_swim_c0.m.field_0x68;
        }
        if (speed.y > 0.0f && mEquipItem != 0x100) { // No value for 0x100 in `ItemTable`?
            deleteEquipItem(1);
        }
    }
    if (m35D0 - current.pos.y < 40.1f + l_HIO_swim_c0.m.field_0x28 && speed.y >= 0.0f) {
        if (mCurProc == 0xb2) {
            onNoResetFlg0(daPyFlg0_UNK100);
            current.pos.y = m35D0;
            return TRUE;
        }
        return procSwimUp_init(1);
    }
    return FALSE;
}

/* 8013D2AC-8013D314       .text swimOutAfter__9daPy_lk_cFi */
void daPy_lk_c::swimOutAfter(int param_1) {
    onNoResetFlg0(daPyFlg0_UNK100);
    m35C4 = 0.0f;
    if (param_1) {
        seStartOnlyReverb(JA_SE_LK_OUTOF_WATER);
    }
    dComIfGp_clearItemTimeCount();
    dComIfGp_setItemTimeMax(0);
    resetPriTextureAnime();
}

/* 8013D314-8013D354       .text checkSwimFallCheck__9daPy_lk_cFv */
BOOL daPy_lk_c::checkSwimFallCheck() {
    if (!checkNoResetFlg0(daPyFlg0_UNK80) || current.pos.y > m35D0 + 30.1f && !(dPa_control_c::mStatus & 1)) { // Fakematch? (dPa_control_c::mStatus & 1) seems like an inline
        return TRUE;
    }
    return FALSE;
}

/* 8013D354-8013D530       .text changeSwimOutProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeSwimOutProc() {
    /* Nonmatching */
    cM3dGPla* pcVar1;
    
    if (mAcch.GetGroundH() != -1e+09f && dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
        pcVar1 = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);   
    }
    else {
        pcVar1 = NULL;
    }

    if (checkSwimFallCheck()) {
        if (mCurProc == 0x37 && m34B8) {
            current.pos.y += m35C4;
        }

        swimOutAfter(1);

        return procFall_init(1, l_HIO_wallCatch_c0.m.field_0x54);
    }
    else {
        if (!checkNoResetFlg0(daPyFlg0_UNK80) || pcVar1 && pcVar1->mNormal.y >= 0.5f && m35D0 - mAcch.GetGroundH() < l_HIO_swim_c0.m.field_0x24 - 5.0f) {
            current.pos.y = m35D0;

            if (mCurProc == 0x37 && m34B8) {
                current.pos.y += m35C4;
            }

            swimOutAfter(1);

            return checkNextMode(0);
        }
        else {
            if (dComIfGp_getItemTimeCount() <= 0 && startRestartRoom(5, 0xC9, -1.0f, 0)) {
                voiceStart(0x21);
                mFrameCtrlUnder[0].mRate = 0.0f;
                onNoResetFlg1(daPyFlg1_LETTER_READ_EYE_MOVE); // the `oris` instruction for this code suggests `onNoResetFlg1` needs to include a `<< 16` op but that breaks other functions
            }
            return FALSE;
        }
    }
}

/* 8013D530-8013D638       .text setSwimMoveAnime__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::setSwimMoveAnime(daPy_ANM swimMoveAnm) {
    /* Nonmatching */
    //float startFrame = mFrameCtrlUnder[0].getFrame();
    float endFrame = mFrameCtrlUnder[0].getEnd();
    setSingleMoveAnime(swimMoveAnm, (std::fabsf(mVelocity) * ((l_HIO_swim_c0.m.field_0x54 - l_HIO_swim_c0.m.field_0x50))) / mMaxNormalSpeed + l_HIO_swim_c0.m.field_0x50 + (float)(getSwimTimerRate() * l_HIO_swim_c0.m.field_0x74), 0.0f, -1, l_HIO_swim_c0.m.field_0x58); // Missing a `* currentFrame` in here?
    mFrameCtrlUnder[0].setFrame(endFrame * mFrameCtrlUnder[0].getEnd());
    mAnmRatioUnder[0].getAnmTransform()->setFrame(mFrameCtrlUnder[0].getFrame());
}

/* 8013D638-8013D6B8       .text getSwimTimerRate__9daPy_lk_cFv */
f32 daPy_lk_c::getSwimTimerRate() {
    f32 swimTimerRate;
    if (dComIfGp_getItemTimeMax() && !dComIfGp_event_getMode()) { // fakematch? possibly the dComIfGp_getItemSwimTimerStatus inline mentioned in the debug maps
        swimTimerRate = (1.0f - dComIfGp_getItemTimeCount() * 0.0011111111f);
    }
    else {
        if (dComIfGp_getItemTimeCount() <= 0) {
            swimTimerRate = 1.0f;
        }
        else {
            swimTimerRate = 0.0f;
        }
    }
    return swimTimerRate;
}

/* 8013D6B8-8013D814       .text setSwimTimerStartStop__9daPy_lk_cFv */
void daPy_lk_c::setSwimTimerStartStop() {
    float target = 0.0f;

    if (mAcch.GetGroundH() <= m35D0 - 175.0f) {
        dComIfGp_setItemTimeMax(1);

        if (checkNoResetFlg0(daPyFlg0_UNK100)) {
            float swimTimerRate = getSwimTimerRate();

            if (swimTimerRate > 0.5f) {
                target = cM_scos(cM_rad2s((1.0f - swimTimerRate) * 3.1415927f)) * -l_HIO_swim_c0.m.field_0x78;

                if (mFrameCtrlUnder->checkPass(0.0f) && mCurProc != 0x35) {
                    if (m3570 && !checkNoResetFlg0(daPyFlg0_UNK4000)) {
                        voiceStart(0x22);
                        m3570 = 0;
                    }
                    else {
                        m3570 = 1;
                    }
                }
            }
        }
    }
    else {
        dComIfGp_setItemTimeCount(900);
        dComIfGp_setItemTimeMax(1);
        dComIfGp_setItemTimeMax(0); //Fakematch? Seems nonsensical to set it to 1 then immediately to 0, also could be `dComIfGp_stopItemSwimTimer` and `dComIfGp_startItemSwimTimer` inlines mentioned in the debug maps
    }

    cLib_chaseF(&m3608, target, 3.0f);
}

/* 8013D814-8013DA18       .text procSwimUp_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSwimUp_init(int param_1) {
    JPABaseEmitter* mEmitter;
    
    static JGeometry::TVec3<f32> splash_scale(0.4f, 0.4f, 0.4f);
    static JGeometry::TVec3<f32> ripple_scale(0.3f, 0.3f, 0.3f);

    commonProcInit(daPyProc_SWIM_UP_e);

    gravity = 0.0f;
    speed.y = 0.0f;

    current.pos.y = m35D0;

    setSingleMoveAnime(ANM_SWIMP, l_HIO_swim_c0.m.field_0x2C, l_HIO_swim_c0.m.field_0x30, l_HIO_swim_c0.m.field_0x0, l_HIO_swim_c0.m.field_0x38);

    dComIfGp_setPlayerStatus0(0, daPyStts0_SWIM_e);

    m35C4 = l_HIO_swim_c0.m.field_0x3C;

    onNoResetFlg0(daPyFlg0_UNK100);

    if (param_1) {
        mEmitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0040, &current.pos);

        if (mEmitter) {
            mEmitter->setRate(15.0f);
            mEmitter->setGlobalDynamicsScale(splash_scale);
            mEmitter->setGlobalParticleScale(splash_scale);
        }

        mEmitter = dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_003D, &current.pos, NULL, NULL, 0xFF, &dPa_control_c::mSingleRippleEcallBack);
        
        if (mEmitter) {
            mEmitter->setGlobalDynamicsScale(ripple_scale);
            mEmitter->setGlobalParticleScale(ripple_scale);
        }
    }
    m3570 = 0;
    return TRUE;
}

/* 8013DA18-8013DB24       .text procSwimUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procSwimUp() {
    int iVar1;

    J3DFrameCtrl* mFrameCtrl = mFrameCtrlUnder;

    setSpeedAndAngleSwim();

    if (!changeSwimOutProc()) {
        if (mFrameCtrl->getRate() < 0.01f) {
            procSwimWait_init(0);
        }
        else {
            if (mFrameCtrl->getFrame() > l_HIO_swim_c0.m.field_0x34) {
                if (mStickDistance > 0.05f) {
                    procSwimMove_init(0);
                }
            }
            else {
                if (mFrameCtrl->checkPass(4.0f)) {
                    voiceStart(0x1A);
                    seStartOnlyReverb(JA_SE_LK_WALK_IN_WATER);
                    seStartOnlyReverb(JA_SE_LK_SWIM);
                }
                else {
                    m35C4 = l_HIO_swim_c0.m.field_0x3C;
                    current.pos.y = m35D0;
                }
            }
        }
    }
    setSwimTimerStartStop();
    return TRUE;
}

/* 8013DB24-8013DCDC       .text procSwimWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSwimWait_init(int param_1) {
    float fVar2;
    u32 uVar3;
    
    J3DFrameCtrl* mFrameCtrl = mFrameCtrlUnder;

    commonProcInit(daPyProc_SWIM_WAIT_e);

    if (param_1) {
        fVar2 = mFrameCtrl->getFrame() / (float)mFrameCtrl->getEnd();
        uVar3 = cM_rad2s(fVar2 * 3.1415927f);
        mVelocity = speedF * (1.0f - l_HIO_swim_c0.m.field_0x60) + speedF * std::fabsf(cM_scos(uVar3)) * l_HIO_swim_c0.m.field_0x60;
    }
    else {
        fVar2 = 0.0f;
    }

    gravity = 0.0f;
    setSingleMoveAnime(ANM_SWIMWAIT, (float)(getSwimTimerRate() * l_HIO_swim_c0.m.field_0x70) + l_HIO_swim_c0.m.field_0x40, 0.0f, -1, l_HIO_swim_c0.m.field_0x44);
    mFrameCtrl->setFrame(fVar2 * mFrameCtrl->getEnd());
    mAnmRatioUnder[0].getAnmTransform()->setFrame(mFrameCtrl->getFrame());
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWIM_e);

    if (checkNoResetFlg0(daPyFlg0_UNK100)) {
        if (mEquipItem != 0x100) {
            deleteEquipItem(1);
        }
        current.pos.y = m35D0;
        speed.y = 0.0f;
    }

    m35C4 = l_HIO_swim_c0.m.field_0x48;
    m34D4 = 0;
    m3570 = 0;
    return TRUE;
}

/* 8013DCDC-8013DE8C       .text procSwimWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procSwimWait() {
    fopAc_ac_c* talkEventPartner;
    short targetAngleY;
    
    setSpeedAndAngleSwim();
    m34D4 += (short)((cM_rndF(0.3f) + 0.85f) * l_HIO_swim_c0.m.field_0x2);
    m35C4 = cM_ssin(m34D4) * l_HIO_swim_c0.m.field_0x4C + l_HIO_swim_c0.m.field_0x48;

    if (changeSwimOutProc()) {
        return TRUE;
    }
    else {
        if (!checkNoResetFlg0(daPyFlg0_UNK100)) {
            if (changeSwimUpProc()) {
                return TRUE;
            }
        }
        else {
            current.pos.y = m35D0;
        }
        if (checkNextModeSwim()) {
            return TRUE;
        }
        else {
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e)) {
                talkEventPartner = fopAcM_getTalkEventPartner(this);
                if (talkEventPartner) {
                    targetAngleY = cLib_targetAngleY(&current.pos, &talkEventPartner->eyePos);
                    cLib_addCalcAngleS(&shape_angle.y, targetAngleY, l_HIO_turn_c0.m.field_0x6, l_HIO_turn_c0.m.field_0x8, l_HIO_turn_c0.m.field_0xA);
                    current.angle.y = shape_angle.y;
               }
            }

            mFrameCtrlUnder[0].setRate((float)(getSwimTimerRate() * l_HIO_swim_c0.m.field_0x70) + l_HIO_swim_c0.m.field_0x40);

            if (mStickDistance > 0.05f) {
                procSwimMove_init(1);
            }

            setSwimTimerStartStop();
        }
    }
    return TRUE;
}

/* 8013DE8C-8013DF60       .text procSwimMove_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSwimMove_init(int param_1) {
    commonProcInit(daPyProc_SWIM_MOVE_e);

    if (param_1 == 0) {
        mFrameCtrlUnder[0].setFrame(0.0f);
    }

    gravity = 0.0f;

    setSwimMoveAnime(ANM_SWIMING);

    m34B8 = 0;

    if (checkNoResetFlg0(daPyFlg0_UNK100)) {
        if (mEquipItem != 0x100) {
            deleteEquipItem(1);
        }

        current.pos.y = m35D0;
        speed.y = 0.0f;

        setSwimTail();
    }

    dComIfGp_setPlayerStatus0(0, daPyStts0_SWIM_e);

    m35C4 = l_HIO_swim_c0.m.field_0x5C;
    m3570 = 0;

    return TRUE;
}

/* 8013DF60-8013E250       .text procSwimMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procSwimMove() {
    int iVar1;
    daPy_ANM anm;

    setSpeedAndAngleSwim();

    J3DFrameCtrl* mFrameCtrl = mFrameCtrlUnder;

    if (!mpAttention->Lockon()) {
        iVar1 = 0;
    }
    else {
        if (mStickDistance > 0.05f) {
            iVar1 = getDirectionFromShapeAngle();
        }
        else {
            iVar1 = 0;
        }
    }

    if (m34B8 != iVar1) {
        m34B8 = iVar1;
        float fVar1 = m35C4;

        if (m34B8 == 0) {
            anm = ANM_SWIMING;
            m35C4 = l_HIO_swim_c0.m.field_0x5C;
        }
        else {
            m35C4 = -80.0f;

            if (m34B8 == 2) {
                anm = ANM_ATNDLS;
            }
            else if (m34B8 == 3) {
                anm = ANM_ATNDRS;
            }
            else {
                anm = ANM_ATNWB;
            } 
        }

        m_old_fdata->getOldFrameTransInfo(0)->mTranslate.y -= m35C4 - fVar1;
        setSwimMoveAnime(anm);

        if (m34B8) {
            setTextureAnime(3, 0);
            onModeFlg(0x100);
            offModeFlg(0x400);
            mpSeAnmFrameCtrl = NULL;
        }
        else {
            offModeFlg(0x100);
            onModeFlg(0x400);
        }
    }
    else {
        mFrameCtrl[0].setRate((std::fabsf(mVelocity) * (l_HIO_swim_c0.m.field_0x54 - l_HIO_swim_c0.m.field_0x50)) / mMaxNormalSpeed + l_HIO_swim_c0.m.field_0x50 + (float)(getSwimTimerRate() * l_HIO_swim_c0.m.field_0x74));
    }

    if (m34B8 == 1) {
        mFrameCtrl[0].setRate(mFrameCtrl[0].getRate() * 0.5f);
    }

    if (changeSwimOutProc()) {
        return TRUE;
    }

    if (!checkNoResetFlg0(daPyFlg0_UNK100)) {
        if (changeSwimUpProc()) {
            return TRUE;
        }
    }
    else {
        current.pos.y = m35D0;
        setSwimTail();
    }

    if (checkNextModeSwim()) {
        return TRUE;
    }

    if (changeFrontWallTypeProc()) {
        swimOutAfter(1);
        return TRUE;
    }

    if (mStickDistance <= 0.05f) {
        procSwimWait_init(1);
    }
    else if ((!m34B8 && mFrameCtrl->checkPass(20.0f)) || (m34B8 && mFrameCtrl->checkPass(0.0f))) {
            seStartOnlyReverb(JA_SE_LK_SWIM);
    }

    setSwimTimerStartStop();

    return TRUE;
}
