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

/* 8013CC64-8013CF2C       .text setSpeedAndAngleSwim__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleSwim() {
    float fVar1;
    BOOL bVar3;    
    bVar3 = false;
    short oldAngleY;
    if (this->mCurProc != 0x35) {
        if (!this->mpAttention->Lockon()) {
            if (this->m35B0 > 0.05f) {
                oldAngleY = this->shape_angle.y;
                if (getDirectionFromShapeAngle() == 1) {
                    this->mSwimTailEcallBack[0].field_0x04 = 1;
                    this->mSwimTailEcallBack[0].field_0x20 = NULL;
                    this->mSwimTailEcallBack[1].field_0x04 = 1;
                    this->mSwimTailEcallBack[1].field_0x20 = NULL;
                    this->shape_angle.y = this->m34E8;
                    this->current.angle.y = this->m34E8;
                }
                else {
                    cLib_addCalcAngleS(&this->shape_angle.y, this->m34E8, l_HIO_swim_c0.m.field_0x8, l_HIO_swim_c0.m.field_0x4, l_HIO_swim_c0.m.field_0x6);     
                }
                fVar1 = this->m35B0 * 3.0f * cM_scos(this->shape_angle.y - oldAngleY);
            }
            else {
                fVar1 = 0.0f;
            }
            cLib_addCalcAngleS(&this->current.angle.y, this->shape_angle.y, 2, 0x2000, 0x1000);
            this->mMaxNormalSpeed = l_HIO_swim_c0.m.field_0xC;
        }
        else {
            setShapeAngleToAtnActor();
            if (this->m35B0 > 0.05f) {
                oldAngleY = this->current.angle.y;
                if (getDirectionFromCurrentAngle() == 1) {
                    this->mSwimTailEcallBack[0].field_0x04 = 1;
                    this->mSwimTailEcallBack[0].field_0x20 = NULL;
                    this->mSwimTailEcallBack[1].field_0x04 = 1;
                    this->mSwimTailEcallBack[1].field_0x20 = NULL;
                    fVar1 = 0.0f;
                    bVar3 = true;
                }
                else {
                    cLib_addCalcAngleS(&this->current.angle.y, this->m34E8, l_HIO_swim_c0.m.field_0x8, l_HIO_swim_c0.m.field_0x4, l_HIO_swim_c0.m.field_0x6);
                    fVar1 = this->m35B0 * 3.0f * cM_scos(this->current.angle.y - oldAngleY);
                }
            }
            else {
                fVar1 = 0.0f;
            }
            this->mMaxNormalSpeed = ((cM_scos(this->current.angle.y - this->shape_angle.y) + 1.0f) * 0.25f + 0.5f) * l_HIO_swim_c0.m.field_0xC;
        }
    }
    else {
        fVar1 = 0.0f;
        this->mMaxNormalSpeed = l_HIO_swim_c0.m.field_0xC;
    }
    setNormalSpeedF(fVar1, l_HIO_swim_c0.m.field_0x18, l_HIO_swim_c0.m.field_0x1C, l_HIO_swim_c0.m.field_0x20);
    if (bVar3 && this->mVelocity < 5.0f) {
        this->current.angle.y = this->m34E8;
        this->mVelocity = 0.0f;
    }
    if (dComIfGp_checkPlayerStatus0(0, 0x10)) {
        this->mVelocity = 0.0f;
    }
    return;
}

/* 8013CF2C-8013CFC0       .text checkNextModeSwim__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextModeSwim() {
    BOOL res;

    if (this->mpAttnEntryA && this->mpAttnEntryA->mType == 7) { //Action_Ship? fopAc_Attn_ACTION_SHIP_e is 0x80 so not sure why Ghidra is saying this 
        dComIfGp_setDoStatus(0x1C); //GetInShip
        if (this->mItemTrigger & 1) { 
            return procShipReady_init();
        }
    }

    if (setTalkStatus() && (this->mItemTrigger & 1)) {
        res = fopAcM_orderTalkEvent(this,this->mpAttnActorA);
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
    
    if (!this->checkNoResetFlg0(daPyFlg0_UNK80) || this->checkModeFlg(0x42000) || checkNoControll() || this->checkPlayerDemoMode(0x11) || this->m35D0 - this->current.pos.y > l_HIO_swim_c0.m.field_0x24) {
        dComIfGp_setItemTimeCount(900);
        dComIfGp_setItemTimeMax(1);
        g_dComIfG_gameInfo.play.field_0x48c8 = 900; // Some inline?

        this->offNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS);
        this->offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);

        endFlameDamageEmitter();

        this->offNoResetFlg0(daPyFlg0_UNK100);

        this->mMaxNormalSpeed = l_HIO_swim_c0.m.field_0xC;
        this->mVelocity *= 0.75f;

        if (this->mVelocity >= this->mMaxNormalSpeed) {
          this->mVelocity = this->mMaxNormalSpeed;
        }

        this->m35C4 = 0.0f;

        setSwimTimerStartStop();
        
        if (this->checkModeFlg(2)) {
            this->current.pos.y = this->current.pos.y + l_HIO_swim_c0.m.field_0x24;
            this->speed.y = this->mOldSpeed.y * l_HIO_swim_c0.m.field_0x10;

            if (this->speed.y < l_HIO_swim_c0.m.field_0x14) {
                this->speed.y = l_HIO_swim_c0.m.field_0x14;
            }
            else if (this->speed.y > 0.0f) {
                this->speed.y = 0.0f;
            }

            float oldSpeedY = this->mOldSpeed.y * this->mOldSpeed.y * 0.0004f + 0.2f;

            if (oldSpeedY > 1.0f) {
                oldSpeedY = 1.0f;
            }

            local_18.x = this->current.pos.x;
            local_18.y = this->m35D0;
            local_18.z = this->current.pos.z;
            fopKyM_createWpillar(&local_18, 1.0f, oldSpeedY, 0);
            seStartOnlyReverb(0x3808);
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
    if (this->speed.y < l_HIO_swim_c0.m.field_0x68) {
        this->speed.y += l_HIO_swim_c0.m.field_0x64;
        if (this->speed.y > l_HIO_swim_c0.m.field_0x68) {
            this->speed.y = l_HIO_swim_c0.m.field_0x68;
        }
        if (this->speed.y > 0.0f && this->mEquipItem != 0x100) {
            deleteEquipItem(1);
        }
    }
    if (this->m35D0 - this->current.pos.y < 40.1f + l_HIO_swim_c0.m.field_0x28 && this->speed.y >= 0.0f) {
        if (this->mCurProc == 0xb2) {
            this->onNoResetFlg0(daPyFlg0_UNK100);
            this->current.pos.y = this->m35D0;
            return TRUE;
        }
        return procSwimUp_init(1);
    }
    return FALSE;
}

/* 8013D2AC-8013D314       .text swimOutAfter__9daPy_lk_cFi */
void daPy_lk_c::swimOutAfter(int param_1) {
    this->onNoResetFlg0(daPyFlg0_UNK100);
    this->m35C4 = 0.0f;
    if (param_1) {
        seStartOnlyReverb(0x3809);
    }
    dComIfGp_setItemTimeCount(0);
    dComIfGp_setItemTimeMax(0);
    resetPriTextureAnime();
    return;
}

/* 8013D314-8013D354       .text checkSwimFallCheck__9daPy_lk_cFv */
BOOL daPy_lk_c::checkSwimFallCheck() {
    if (!this->checkNoResetFlg0(daPyFlg0_UNK80) || this->current.pos.y > this->m35D0 + 30.1f && !(dPa_control_c::mStatus & 1)) {
        return TRUE;
    }
    return FALSE;
}

/* 8013D354-8013D530       .text changeSwimOutProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeSwimOutProc() {
    cM3dGPla* pcVar1;
    
    if (this->mAcch.GetGroundH() != -1e+09f && dComIfG_Bgsp()->ChkPolySafe(this->mAcch.m_gnd)) {
        pcVar1 = dComIfG_Bgsp()->GetTriPla(this->mAcch.m_gnd);   
    }
    else {
        pcVar1 = NULL;
    }

    if (checkSwimFallCheck()) {

        if (this->mCurProc == 0x37 && this->m34B8) {
            this->current.pos.y += this->m35C4;
        }

        swimOutAfter(1);

        return procFall_init(1, l_HIO_wallCatch_c0.m.field_0x54);
    }
    else {
        if (!this->checkNoResetFlg0(daPyFlg0_UNK80) || pcVar1 && pcVar1->mNormal.y >= 0.5f && this->m35D0 - this->mAcch.GetGroundH() < l_HIO_swim_c0.m.field_0x24 - 5.0f) {
            this->current.pos.y = this->m35D0;
            if (this->mCurProc == 0x37 && this->m34B8) {
                this->current.pos.y += this->m35C4;
            }
            swimOutAfter(1);
            return checkNextMode(0);
        }
        else {
            if (dComIfGp_getItemTimeCount() <= 0 && startRestartRoom(5, 0xc9, -1.0f, 0)) {
                this->voiceStart(0x21);
                this->mFrameCtrlUnder[0].mRate = 0.0f;
                this->onNoResetFlg1(daPyFlg1_LETTER_READ_EYE_MOVE); // DoNotAnimate, the `oris` instruction for this code suggests `onNoResetFlg1` needs to include a `<< 16` op
            }
            return FALSE;
        }
    }
}

/* 8013D530-8013D638       .text setSwimMoveAnime__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::setSwimMoveAnime(daPy_ANM swimMoveAnm) {
    float sVar3;
    sVar3 = this->mFrameCtrlUnder[0].getEnd();
    setSingleMoveAnime(swimMoveAnm, (std::fabsf(this->mVelocity) * l_HIO_swim_c0.m.field_0x54) / this->mMaxNormalSpeed + l_HIO_swim_c0.m.field_0x50 + (getSwimTimerRate() * l_HIO_swim_c0.m.field_0x74), 0.0f, -1, l_HIO_swim_c0.m.field_0x58);
    this->mFrameCtrlUnder[0].setFrame(this->mFrameCtrlUnder[0].getFrame() * sVar3 * this->mFrameCtrlUnder[0].getEnd());
    this->mAnmRatioUnder[0].getAnmTransform()->setFrame(this->mFrameCtrlUnder[0].getFrame());
    return;
}

/* 8013D638-8013D6B8       .text getSwimTimerRate__9daPy_lk_cFv */
f32 daPy_lk_c::getSwimTimerRate() {
    f32 swimTimerRate;
    if (dComIfGp_getItemTimeMax() && !dComIfGp_event_getMode()) {
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
    /* Nonmatching */
}

/* 8013D814-8013DA18       .text procSwimUp_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSwimUp_init(int) {
    /* Nonmatching */
    static JGeometry::TVec3<f32> splash_scale;
    static JGeometry::TVec3<f32> ripple_scale;
}

/* 8013DA18-8013DB24       .text procSwimUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procSwimUp() {
    /* Nonmatching */
}

/* 8013DB24-8013DCDC       .text procSwimWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSwimWait_init(int) {
    /* Nonmatching */
}

/* 8013DCDC-8013DE8C       .text procSwimWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procSwimWait() {
    /* Nonmatching */
}

/* 8013DE8C-8013DF60       .text procSwimMove_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSwimMove_init(int) {
    /* Nonmatching */
}

/* 8013DF60-8013E250       .text procSwimMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procSwimMove() {
    /* Nonmatching */
}
