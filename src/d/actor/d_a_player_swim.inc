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

/* 8013CC64-8013CF2C       .text setSpeedAndAngleSwim__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleSwim() {
    float calculatedSpeed;
    short oldAngleY;

    // Flag used to indicate a forced stop due to backwards swimming input while locked on
    BOOL isForcedStop = false;

    // Only perform calculations if not currently in the "swim upward" state
    if (mCurProc != daPyProc_SWIM_UP_e) {

        // If not locked onto a target, handle free swimming movement
        if (!mpAttention->Lockon()) {

            // Only process movement if the stick input is significant
            if (mStickDistance > 0.05f) {
                oldAngleY = shape_angle.y;

                // If swimming backward relative to facing angle, forcibly reset direction
                if (getDirectionFromShapeAngle() == DIR_BACKWARD) {
                    // Stop Link's ripple animation(s)
                    mSwimTailEcallBack[0].onEnd();
                    mSwimTailEcallBack[1].onEnd();

                    // Snap to target
                    shape_angle.y = mTargetAngleY;
                    current.angle.y = mTargetAngleY;
                }
                else {
                    // Smoothly rotate towards target angle
                    cLib_addCalcAngleS(
                        &shape_angle.y,
                        mTargetAngleY,
                        daPy_HIO_swim_c0::m.angleApproachStep,
                        daPy_HIO_swim_c0::m.angleTurnRateMin,
                        daPy_HIO_swim_c0::m.angleTurnRateMax
                    );
                }

                // Calculate forward movement speed based on how much direction has changed
                /*
                   Note:
                   This code is the beginning of a series of oversights that resulted in the `super-swim` bug.
                   The code cM_scos(shape_angle.y - oldAngleY) can return a range of values from -1.0 to 1.0[1].
                   Due to a lack of clamping on the this value, a value <0 would result in a negative speed
                   as mStickDistance represents the magnitude of the stick direction (ie. it is strictley positive).
                   The fact that this variable can take on a negative value produces issues strictly when those negative values 
                   are maintained. The devs most likely intended for negative speeds to be possible but did not foresee 
                   the possibility of maintaining negative directions while in free-cam mode.
                   
                   [1] The case in which it returns -1.0f is when the new shape angle is -180 degrees 
                   relative to the old shape angle (ie. Link turns around in the water). 
                   The 1.0 case would be when the angle hasn't changed at all (ie. Link moving in the same direction).
                */
                calculatedSpeed = mStickDistance * 3.0f * cM_scos(shape_angle.y - oldAngleY);
            }
            else {
                // Halt movement if no significant stick input detected
                calculatedSpeed = 0.0f;
            }

            // Smoothly rotate body angle to match shape angle
            cLib_addCalcAngleS(&current.angle.y, shape_angle.y, 2, 0x2000, 0x1000);

            mMaxNormalSpeed = daPy_HIO_swim_c0::m.baseSwimSpeed;
        }

        // If locked on to a target, handle swimming behavior differently
        else {
            setShapeAngleToAtnActor();  // align shape angle to look-at target

            if (mStickDistance > 0.05f) {
                oldAngleY = current.angle.y;

                // Prevent swimming backward while locked on
                if (getDirectionFromCurrentAngle() == DIR_BACKWARD) {
                    mSwimTailEcallBack[0].onEnd();
                    mSwimTailEcallBack[1].onEnd();

                    calculatedSpeed = 0.0f;
                    isForcedStop = TRUE;  // stop movement
                }
                else {
                    cLib_addCalcAngleS(
                        &current.angle.y,
                        mTargetAngleY,
                        daPy_HIO_swim_c0::m.angleApproachStep,
                        daPy_HIO_swim_c0::m.angleTurnRateMin,
                        daPy_HIO_swim_c0::m.angleTurnRateMax
                    );

                    calculatedSpeed = mStickDistance * 3.0f * cM_scos(current.angle.y - oldAngleY);
                }
            }
            else {
                calculatedSpeed = 0.0f;
            }

            // Adjust max speed based on alignment between shape and facing direction
            mMaxNormalSpeed = ((cM_scos(current.angle.y - shape_angle.y) + 1.0f) * 0.25f + 0.5f) * daPy_HIO_swim_c0::m.baseSwimSpeed;
        }
    }

    // If in swim-up state, stop horizontal movement
    else {
        calculatedSpeed = 0.0f;
        mMaxNormalSpeed = daPy_HIO_swim_c0::m.baseSwimSpeed;
    }

    // Apply calculated speed with acceleration parameters
    /*
        Note:
        This function was developed without consideration of clamping Link's velocity 
        in the negative direction leading to super-swimming being possible. 
        More details on this can be found within the function itself.
    */
    setNormalSpeedF(
        calculatedSpeed,
        daPy_HIO_swim_c0::m.acceleration,
        daPy_HIO_swim_c0::m.speedStepMax,
        daPy_HIO_swim_c0::m.speedStepMin
    );

    // If a forced stop was triggered and velocity is low, zero velocity and reset angle
    if (isForcedStop && mVelocity < 5.0f) {
        current.angle.y = mTargetAngleY;
        mVelocity = 0.0f;
    }

    // Special case: some player status triggers an immediate stop
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e)) {
        mVelocity = 0.0f;
    }
}


/* 8013CF2C-8013CFC0       .text checkNextModeSwim__9daPy_lk_cFv */
/*
 * Determines whether Link should transition from swimming to another interaction mode.
 * 
 * Specifically checks if Link is near a ship or an NPC, in which case the swim state can end and
 * a new state like boarding or talking may begin.
 * 
 * Returns:
 *   - TRUE if a new mode was triggered (e.g. boarding a ship or talking to an NPC).
 *   - FALSE otherwise.
 */
BOOL daPy_lk_c::checkNextModeSwim() {
    BOOL res;

    if (mpAttnEntryA && mpAttnEntryA->mType == fopAc_Attn_TYPE_SHIP_e) {
        dComIfGp_setDoStatus(dActStts_GET_IN_SHIP_e);
        if (doTrigger()) { 
            return procShipReady_init();
        }
    }

    if (setTalkStatus() && doTrigger()) {
        res = fopAcM_orderTalkEvent(this, mpAttnActorA);
    }
    else {
        res = FALSE;
    }
    return res;
}

/* 8013CFC0-8013D1B0       .text changeSwimProc__9daPy_lk_cFv */
/*
 * Attempts to initiate the swim state based on current conditions.
 *
 * Handles resetting various player states (e.g. removing Iron boots), applying initial velocity and vertical
 * position correction based on water surface, and spawning visual effects (water splash). Transitions to
 * either Swim Wait or Swim Up depending on airborne status.
 * 
 * Returns:
 *   - TRUE if a swim process is initiated.
 *   - FALSE otherwise.
 */
BOOL daPy_lk_c::changeSwimProc() {
    BOOL res;
    cXyz splashEffectPos;
    
    if (checkNoResetFlg0(daPyFlg0_UNK80) &&  // Precondition for being ready to swim, maybe daPyFlg0_READY_TO_SWIM could be a good name?
        !checkModeFlg(ModeFlg_IN_SHIP | ModeFlg_SWIM) && 
        !checkNoControll() && 
        mDemo.getDemoMode() 
        != daPy_demo_c::DEMO_UNK11_e && 
        mSwimHeight - current.pos.y > daPy_HIO_swim_c0::m.minDepthToSwim) {
        
        dComIfGp_setItemTimeCount(900);
        dComIfGp_setItemTimeMax(900);

        offNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
        offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);

        endFlameDamageEmitter();

        offNoResetFlg0(daPyFlg0_SWIM_EXIT);

        mMaxNormalSpeed = daPy_HIO_swim_c0::m.baseSwimSpeed;
        mVelocity *= 0.75f;

        if (mVelocity >= mMaxNormalSpeed) {
            mVelocity = mMaxNormalSpeed;
        }

        m35C4 = 0.0f;

        setSwimTimerStartStop();
        
        if (checkModeFlg(ModeFlg_MIDAIR)) {
            current.pos.y += daPy_HIO_swim_c0::m.minDepthToSwim;
            speed.y = mOldSpeed.y * daPy_HIO_swim_c0::m.fallSpeedMultiplier;

            if (speed.y < daPy_HIO_swim_c0::m.minSplashEntrySpeed) {
                speed.y = daPy_HIO_swim_c0::m.minSplashEntrySpeed;
            }
            else if (speed.y > 0.0f) {
                speed.y = 0.0f;
            }

            float oldSpeedY = mOldSpeed.y * mOldSpeed.y * 0.0004f + 0.2f;

            if (oldSpeedY > 1.0f) {
                oldSpeedY = 1.0f;
            }

            splashEffectPos.x = current.pos.x;
            splashEffectPos.y = mSwimHeight;
            splashEffectPos.z = current.pos.z;
            fopKyM_createWpillar(&splashEffectPos, 1.0f, oldSpeedY, 0);
            seStartOnlyReverb(JA_SE_LK_INTO_WATER);
            res = procSwimWait_init(FALSE);
        }
        else {
            res = procSwimUp_init(FALSE);
        }
    }
    else {
        res = 0;
    }
    return res;
}

/* 8013D1B0-8013D2AC       .text changeSwimUpProc__9daPy_lk_cFv */
/*
 * Handles the logic for transitioning into the "swim up" state from underwater.
 * 
 * Gradually accelerates Link upward. If close enough to the surface and not in a special death state,
 * initiates the Swim Up process. Also handles item deletion if rising to surface with something equipped.
 * 
 * Returns:
 *   - TRUE if transition to Swim Up occurred or a death-state override triggered.
 *   - FALSE otherwise.
 */
BOOL daPy_lk_c::changeSwimUpProc() {
    if (speed.y < daPy_HIO_swim_c0::m.maxUnderwaterUpSpeed) {
        speed.y += daPy_HIO_swim_c0::m.maxUnderwaterUpAcceleration;

        if (speed.y > daPy_HIO_swim_c0::m.maxUnderwaterUpSpeed) {
            speed.y = daPy_HIO_swim_c0::m.maxUnderwaterUpSpeed;
        }

        if (speed.y > 0.0f && mEquipItem != daPyItem_NONE_e) {
            deleteEquipItem(TRUE);
        }
    }

    if (mSwimHeight - current.pos.y < 40.1f + daPy_HIO_swim_c0::m.swimSurfaceCloseThreshold && speed.y >= 0.0f) {
        if (mCurProc == daPyProc_DEMO_DEAD_e) {
            onNoResetFlg0(daPyFlg0_SWIM_EXIT); // Seems to indicate that Link is leaving/has left the water (probably set after drowning since the death animation plays on land)
            current.pos.y = mSwimHeight;
            return TRUE;
        }
        return procSwimUp_init(TRUE);
    }

    return FALSE;
}

/* 8013D2AC-8013D314       .text swimOutAfter__9daPy_lk_cFi */
/*
 * Post-processing for exiting the water (either by swimming out or falling out).
 *
 * Resets swim timers, plays sound effects if requested, and clears texture animations.
 * 
 * Parameters:
 *   - i_bPlayWaterExitSE: If TRUE, triggers water exit sound effect.
 */
void daPy_lk_c::swimOutAfter(BOOL i_bPlayWaterExitSE) {
    onNoResetFlg0(daPyFlg0_SWIM_EXIT);
    
    m35C4 = 0.0f;

    if (i_bPlayWaterExitSE) {
        seStartOnlyReverb(JA_SE_LK_OUTOF_WATER);
    }

    dComIfGp_clearItemTimeCount();

    resetPriTextureAnime();
}

/* 8013D314-8013D354       .text checkSwimFallCheck__9daPy_lk_cFv */
/*
 * Checks if Link should be considered as falling out of water.
 *
 * Returns TRUE if:
 *   - Not in swim state (flag missing), OR
 *   - Y-position is significantly above the swim height threshold AND particle status is not active.
 * 
 * Returns:
 *   - TRUE if Link is falling out of swim state.
 *   - FALSE otherwise.
 */
BOOL daPy_lk_c::checkSwimFallCheck() {
    if (!checkNoResetFlg0(daPyFlg0_UNK80) || (current.pos.y > mSwimHeight + 30.1f && !dPa_control_c::isStatus(1))) {
        return TRUE;
    }
    return FALSE;
}

/* 8013D354-8013D530       .text changeSwimOutProc__9daPy_lk_cFv */
/*
 * Handles the logic for transitioning out of swim mode.
 *
 * This function checks ground conditions and whether Link is emerging from the water
 * or falling out. Depending on the evaluation, it initiates appropriate animations and
 * possibly restarts the room if drowning conditions are met.
 * 
 * Returns:
 *   - TRUE if swim mode ends (either via fall or ground emergence).
 *   - FALSE otherwise.
 */
BOOL daPy_lk_c::changeSwimOutProc() {
    cM3dGPla* pcVar1;
    
    if (mAcch.GetGroundH() != C_BG_MIN_HEIGHT && dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
        pcVar1 = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);   
    }
    else {
        pcVar1 = NULL;
    }

    if (checkSwimFallCheck()) {
        if (mCurProc == daPyProc_SWIM_MOVE_e && mDirection != DIR_FORWARD) {
            current.pos.y += m35C4;
        }

        swimOutAfter(TRUE);

        return procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    }

    if (!checkNoResetFlg0(daPyFlg0_UNK80) || (pcVar1 && pcVar1->mNormal.y >= 0.5f && mSwimHeight - mAcch.GetGroundH() < daPy_HIO_swim_c0::m.minDepthToSwim - 5.0f)) {
        current.pos.y = mSwimHeight;

        if (mCurProc == daPyProc_SWIM_MOVE_e && mDirection != DIR_FORWARD) {
            current.pos.y += m35C4;
        }

        swimOutAfter(TRUE);

        return checkNextMode(0);
    }

    if (dComIfGp_getItemTimeCount() <= 0 && startRestartRoom(5, 0xC9, -1.0f, 0)) {
        voiceStart(0x21);
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
        onNoResetFlg1(daPyFlg1_UNK40000000);
    }
    return FALSE;
}

/* 8013D530-8013D638       .text setSwimMoveAnime__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
/*
 * Sets the swimming movement animation for Link.
 * 
 * Calculates animation playback rate based on Link's current swim velocity and timer status.
 * This ensures that animation speed matches movement speed and reflects swim urgency (e.g. drowning).
 * 
 * Parameters:
 *   - swimMoveAnm: Enum value for the specific swim animation to use.
 */
void daPy_lk_c::setSwimMoveAnime(daPy_ANM swimMoveAnm) {
    f32 startFrame = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    f32 endFrame = startFrame * mFrameCtrlUnder[UNDER_MOVE0_e].getEnd();
    f32 rate = (std::fabsf(mVelocity) * (daPy_HIO_swim_c0::m.maxAnimSpeedScale - daPy_HIO_swim_c0::m.minAnimSpeedScale) / mMaxNormalSpeed) +
                daPy_HIO_swim_c0::m.minAnimSpeedScale +
               (getSwimTimerRate() * daPy_HIO_swim_c0::m.airMeterAnimBoost);
    setSingleMoveAnime(swimMoveAnm, rate, 0.0f, -1, daPy_HIO_swim_c0::m.blendTimer);
    mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(endFrame * mFrameCtrlUnder[UNDER_MOVE0_e].getEnd());
    mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
}

/* 8013D638-8013D6B8       .text getSwimTimerRate__9daPy_lk_cFv */
/*
 * Returns a normalized value (0.0 to 1.0) representing how depleted the air meter is.
 *
 * This value affects things like swim animation speed and possibly audio/visual feedback.
 * Returns 1.0 if the meter is fully depleted or disabled, and 0.0 if it's full.
 * 
 * Returns:
 *   - A float from 0.0 (meter full) to 1.0 (meter depleted).
 */
f32 daPy_lk_c::getSwimTimerRate() {
    f32 swimTimerRate;
    if (dComIfGp_getItemSwimTimerStatus() && dComIfGp_event_getMode() == dEvtMode_NONE_e) {
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
/*
 * Starts or stops the air meter timer based on Link's vertical position.
 *
 * If Link is significantly below the surface, the timer begins. Also sets the
 * drowning voice clip based on swim timer state and current swim animation loop.
 * 
 * Adjusts `m3608` field using a cosine function to reflect Link's oxygen discomfort level.
 */
void daPy_lk_c::setSwimTimerStartStop() {
    float target = 0.0f;

    if (mAcch.GetGroundH() <= mSwimHeight - 175.0f) {
        dComIfGp_startItemSwimTimer();

        if (checkNoResetFlg0(daPyFlg0_SWIM_EXIT)) {
            float swimTimerRate = getSwimTimerRate();

            if (swimTimerRate > 0.5f) {
                target = cM_fcos((1.0f - swimTimerRate) * M_PI) * -daPy_HIO_swim_c0::m.field_0x78;

                if (mFrameCtrlUnder->checkPass(0.0f) && mCurProc != daPyProc_SWIM_UP_e) {
                    if (mProcVar0.m3570 && !checkNoResetFlg0(daPyFlg0_UNK4000)) {
                        voiceStart(0x22);
                        mProcVar0.m3570 = 0;
                    }
                    else {
                        mProcVar0.m3570 = 1;
                    }
                }
            }
        }
    }
    else {
        dComIfGp_setItemTimeCount(900);
        dComIfGp_stopItemSwimTimer();
    }

    cLib_chaseF(&m3608, target, 3.0f);
}

/* 8013D814-8013DA18       .text procSwimUp_init__9daPy_lk_cFi */
/*
 * Starts or stops the air meter timer based on Link's vertical position.
 *
 * If Link is significantly below the surface, the timer begins. Also sets the
 * drowning voice clip based on air meter level and current swim animation loop.
 * 
 * Adjusts `m3608` field using a cosine function to reflect Link's oxygen level.
 */

BOOL daPy_lk_c::procSwimUp_init(BOOL param_1) {
    JPABaseEmitter* mEmitter;
    
    static JGeometry::TVec3<f32> splash_scale(0.4f, 0.4f, 0.4f);
    static JGeometry::TVec3<f32> ripple_scale(0.3f, 0.3f, 0.3f);

    commonProcInit(daPyProc_SWIM_UP_e);

    gravity = 0.0f;
    speed.y = 0.0f;

    current.pos.y = mSwimHeight;

    setSingleMoveAnime(ANM_SWIMP, daPy_HIO_swim_c0::m.field_0x2C, daPy_HIO_swim_c0::m.field_0x30, daPy_HIO_swim_c0::m.field_0x0, daPy_HIO_swim_c0::m.field_0x38);

    dComIfGp_setPlayerStatus0(0, daPyStts0_SWIM_e);

    m35C4 = daPy_HIO_swim_c0::m.field_0x3C;

    onNoResetFlg0(daPyFlg0_SWIM_EXIT);

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

    mProcVar0.m3570 = 0;
    return TRUE;
}

/* 8013DA18-8013DB24       .text procSwimUp__9daPy_lk_cFv */
/*
 * Handles the Swim Up process, transitioning Link from swimming under water to swimming at the water's surface.
 *
 * Updates Link's vertical position, checks for animation progress, and plays the appropriate swim sounds.
 * The function handles different swim speed values depending on whether the user is swimming upwards 
 * manually or being moved by the game logic.
 * 
 * Returns:
 *   - TRUE: Successfully handled the Swim Up process.
 */
BOOL daPy_lk_c::procSwimUp() {
    J3DFrameCtrl* mFrameCtrl = mFrameCtrlUnder;

    setSpeedAndAngleSwim();

    if (!changeSwimOutProc()) {
        if (mFrameCtrl->getRate() < 0.01f) {
            procSwimWait_init(FALSE);
        }
        else {
            if (mFrameCtrl->getFrame() > daPy_HIO_swim_c0::m.field_0x34) {
                if (mStickDistance > 0.05f) {
                    procSwimMove_init(FALSE);
                }
            }
            else {
                if (mFrameCtrl->checkPass(4.0f)) {
                    voiceStart(0x1A);
                    seStartOnlyReverb(JA_SE_LK_WALK_IN_WATER);
                    seStartOnlyReverb(JA_SE_LK_SWIM);
                }
                else {
                    m35C4 = daPy_HIO_swim_c0::m.field_0x3C;
                    current.pos.y = mSwimHeight;
                }
            }
        }
    }
    setSwimTimerStartStop();
    return TRUE;
}

/* 8013DB24-8013DCDC       .text procSwimWait_init__9daPy_lk_cFi */
/*
 * Initializes the Swim Wait state, where Link treads water while idle.
 *
 * Sets up the swim animation with appropriate playback speed, vertical position, 
 * and initializes the water interaction flags. Disables gravity during this process. 
 * Based on the parameter, either plays the splash sound and effects or keeps the character idle.
 * 
 * Parameters:
 *   - param_1: If TRUE, plays the splash effect and sound.
 * 
 * Returns:
 *   - TRUE when initialization of the swim wait process is successful.
 */
BOOL daPy_lk_c::procSwimWait_init(BOOL param_1) {
    float fVar2;
    
    J3DFrameCtrl* mFrameCtrl = mFrameCtrlUnder;

    commonProcInit(daPyProc_SWIM_WAIT_e);

    if (param_1) {
        fVar2 = mFrameCtrl->getFrame() / (float)mFrameCtrl->getEnd();
        mVelocity = speedF * (1.0f - daPy_HIO_swim_c0::m.field_0x60) + speedF * std::fabsf(cM_fcos(fVar2 * M_PI)) * daPy_HIO_swim_c0::m.field_0x60;
    }
    else {
        fVar2 = 0.0f;
    }

    gravity = 0.0f;
    setSingleMoveAnime(ANM_SWIMWAIT, (float)(getSwimTimerRate() * daPy_HIO_swim_c0::m.field_0x70) + daPy_HIO_swim_c0::m.field_0x40, 0.0f, -1, daPy_HIO_swim_c0::m.field_0x44);
    mFrameCtrl->setFrame(fVar2 * mFrameCtrl->getEnd());
    mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrl->getFrame());
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWIM_e);

    if (checkNoResetFlg0(daPyFlg0_SWIM_EXIT)) {
        if (mEquipItem != daPyItem_NONE_e) {
            deleteEquipItem(TRUE);
        }
        current.pos.y = mSwimHeight;
        speed.y = 0.0f;
    }

    m35C4 = daPy_HIO_swim_c0::m.field_0x48;
    m34D4 = 0;
    mProcVar0.m3570 = 0;
    return TRUE;
}

/* 8013DCDC-8013DE8C       .text procSwimWait__9daPy_lk_cFv */
/*
 * Handles the Swim Wait process, where Link remains idle in the water while waiting for user input or event triggers.
 *
 * Updates swim direction and speed, checks for potential transitions to other swim states like swimming up or 
 * swimming out of the water. If specific thresholds are met, Link's animation is modified, and sound effects 
 * are triggered. 
 * 
 * Returns:
 *   - TRUE: Successfully processed the Swim Wait state.
 */
BOOL daPy_lk_c::procSwimWait() {
    setSpeedAndAngleSwim();
    m34D4 += (short)((cM_rndF(0.3f) + 0.85f) * daPy_HIO_swim_c0::m.field_0x2);
    m35C4 = cM_ssin(m34D4) * daPy_HIO_swim_c0::m.field_0x4C + daPy_HIO_swim_c0::m.field_0x48;

    if (changeSwimOutProc()) {
        return TRUE;
    }

    if (!checkNoResetFlg0(daPyFlg0_SWIM_EXIT)) {
        if (changeSwimUpProc()) {
            return TRUE;
        }
    }
    else {
        current.pos.y = mSwimHeight;
    }

    if (checkNextModeSwim()) {
        return TRUE;
    }

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK10_e)) {
        fopAc_ac_c* talkEventPartner = fopAcM_getTalkEventPartner(this);
        if (talkEventPartner) {
            short targetAngleY = cLib_targetAngleY(&current.pos, &talkEventPartner->eyePos);
            cLib_addCalcAngleS(&shape_angle.y, targetAngleY, daPy_HIO_turn_c0::m.field_0x6, daPy_HIO_turn_c0::m.field_0x8, daPy_HIO_turn_c0::m.field_0xA);
            current.angle.y = shape_angle.y;
        }
    }

    mFrameCtrlUnder[UNDER_MOVE0_e].setRate((getSwimTimerRate() * daPy_HIO_swim_c0::m.field_0x70) + daPy_HIO_swim_c0::m.field_0x40);

    if (mStickDistance > 0.05f) {
        procSwimMove_init(TRUE);
    }

    setSwimTimerStartStop();

    return TRUE;
}

/* 8013DE8C-8013DF60       .text procSwimMove_init__9daPy_lk_cFi */
/*
 * Initializes the Swim Move state, where Link begins moving through the water in a swimming motion.
 *
 * Sets up swimming animation and speed, and handles various setup tasks like resetting gravity and adjusting
 * the character's vertical position. If certain flags are set (such as an equipped item), it adjusts the swim 
 * behavior accordingly. Sets the swim tail animation to simulate water movement.
 * 
 * Parameters:
 *   - i_bKeepSwimAnime: If FALSE, resets the swim animation frame to 0; otherwise, it keeps the animation's current state.
 * 
 * Returns:
 *   - TRUE when initialization of the swim move process is successful.
 */
BOOL daPy_lk_c::procSwimMove_init(BOOL i_bKeepSwimAnime) {
    commonProcInit(daPyProc_SWIM_MOVE_e);

    if (!i_bKeepSwimAnime) {
        mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(0.0f);
    }

    gravity = 0.0f;

    setSwimMoveAnime(ANM_SWIMING);

    mDirection = DIR_FORWARD;

    if (checkNoResetFlg0(daPyFlg0_SWIM_EXIT)) {
        if (mEquipItem != daPyItem_NONE_e) {
            deleteEquipItem(TRUE);
        }

        current.pos.y = mSwimHeight;
        speed.y = 0.0f;

        setSwimTail();
    }

    dComIfGp_setPlayerStatus0(0, daPyStts0_SWIM_e);

    m35C4 = daPy_HIO_swim_c0::m.field_0x5C;
    mProcVar0.m3570 = 0;

    return TRUE;
}

/* 8013DF60-8013E250       .text procSwimMove__9daPy_lk_cFv */
/*
 * Handles the Swim Move state, where Link is actively swimming in the water.
 *
 * Adjusts movement speed and direction based on player input and environment. The direction of swimming is 
 * updated, and if necessary, it triggers a change in swim animation (forward, backward, or turning). Additionally, 
 * the function handles sound effects and swimming transitions such as moving out of the water or swimming upwards.
 * 
 * Returns:
 *   - TRUE when the swimming move process is successfully processed.
 */
BOOL daPy_lk_c::procSwimMove() {
    daPy_ANM anm;

    setSpeedAndAngleSwim();

    J3DFrameCtrl* mFrameCtrl = mFrameCtrlUnder;

    int direction;
    if (!mpAttention->Lockon()) {
        direction = DIR_FORWARD;
    }
    else if (mStickDistance > 0.05f) {
        direction = getDirectionFromShapeAngle();
    }
    else {
        direction = DIR_FORWARD;
    }

    if (mDirection != direction) {
        mDirection = direction;
        float fVar1 = m35C4;

        if (mDirection == DIR_FORWARD) {
            anm = ANM_SWIMING;
            m35C4 = daPy_HIO_swim_c0::m.field_0x5C;
        }
        else {
            m35C4 = -80.0f;

            if (mDirection == DIR_LEFT) {
                anm = ANM_ATNDLS;
            }
            else if (mDirection == DIR_RIGHT) {
                anm = ANM_ATNDRS;
            }
            else {
                anm = ANM_ATNWB;
            } 
        }

        m_old_fdata->getOldFrameTransInfo(0)->mTranslate.y -= m35C4 - fVar1;
        setSwimMoveAnime(anm);

        if (mDirection != DIR_FORWARD) {
            setTextureAnime(3, 0);
            onModeFlg(ModeFlg_00000100);
            offModeFlg(ModeFlg_00000400);
            mpSeAnmFrameCtrl = NULL;
        }
        else {
            offModeFlg(ModeFlg_00000100);
            onModeFlg(ModeFlg_00000400);
        }
    }
    else {
        mFrameCtrl[0].setRate((std::fabsf(mVelocity) * (daPy_HIO_swim_c0::m.maxAnimSpeedScale - daPy_HIO_swim_c0::m.minAnimSpeedScale)) / mMaxNormalSpeed + daPy_HIO_swim_c0::m.minAnimSpeedScale + (float)(getSwimTimerRate() * daPy_HIO_swim_c0::m.airMeterAnimBoost));
    }

    if (mDirection == DIR_BACKWARD) {
        mFrameCtrl[0].setRate(mFrameCtrl[0].getRate() * 0.5f);
    }

    if (changeSwimOutProc()) {
        return TRUE;
    }

    if (!checkNoResetFlg0(daPyFlg0_SWIM_EXIT)) {
        if (changeSwimUpProc()) {
            return TRUE;
        }
    }
    else {
        current.pos.y = mSwimHeight;
        setSwimTail();
    }

    if (checkNextModeSwim()) {
        return TRUE;
    }

    if (changeFrontWallTypeProc()) {
        swimOutAfter(TRUE);
        return TRUE;
    }

    if (mStickDistance <= 0.05f) {
        procSwimWait_init(TRUE);
    }
    else if ((mDirection == DIR_FORWARD && mFrameCtrl->checkPass(20.0f)) || (mDirection != DIR_FORWARD && mFrameCtrl->checkPass(0.0f))) {
            seStartOnlyReverb(JA_SE_LK_SWIM);
    }

    setSwimTimerStartStop();

    return TRUE;
}
