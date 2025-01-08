/**
 * d_a_player_bow.inc
 *
 * Code relating to the Bow item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"

/* 80149ECC-80149F88       .text bowJointCB__9daPy_lk_cFi */
void daPy_lk_c::bowJointCB(int) {
    /* Nonmatching */
}

/* 80149F88-80149FD0       .text daPy_bowJointCB__FP7J3DNodei */
static BOOL daPy_bowJointCB(J3DNode*, int) {
    /* Nonmatching */
}

/* 80149FD0-8014A008       .text bowButton__9daPy_lk_cCFv */
BOOL daPy_lk_c::bowButton() const {
    if (mDemo.getDemoMode() == daPy_demo_c::DEMO_UNK44_e) {
        return doButton();
    } else {
        return itemButton();
    }
}

/* 8014A008-8014A02C       .text checkBowReadyAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkBowReadyAnime() const {
    /* Nonmatching */
}

/* 8014A02C-8014A080       .text checkBowAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkBowAnime() const {
    /* Nonmatching */
}

/* 8014A080-8014A180       .text makeArrow__9daPy_lk_cFv */
void daPy_lk_c::makeArrow() {
    /* Nonmatching */
}

/* 8014A180-8014A1CC       .text deleteArrow__9daPy_lk_cFv */
void daPy_lk_c::deleteArrow() {
    /* Nonmatching */
}

/* 8014A1CC-8014A2A0       .text setBowReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::setBowReadyAnime() {
    /* Nonmatching */
}

/* 8014A2A0-8014A328       .text setBowReloadAnime__9daPy_lk_cFv */
void daPy_lk_c::setBowReloadAnime() {
    /* Nonmatching */
}

/* 8014A328-8014A60C       .text checkNextActionBowReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionBowReady() {
    /* Nonmatching */
}

/* 8014A60C-8014A680       .text checkNextActionBowFly__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionBowFly() {
    /* Nonmatching */
}

/* 8014A680-8014A6F4       .text checkNextBowMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextBowMode() {
    /* Nonmatching */
}

/* 8014A6F4-8014A834       .text setBowModel__9daPy_lk_cFv */
void daPy_lk_c::setBowModel() {
    /* Nonmatching */
}

/* 8014A834-8014A8D4       .text procBowSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowSubject_init() {
    if(mCurProc == daPyProc_BOW_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_BOW_SUBJECT_e);

    if(!checkBowAnime()) {
        setBowReadyAnime();
    }
    setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);

    mVelocity = 0.0f;

    dComIfGp_setPlayerStatus0(0, daPyStts0_BOW_AIM_e);

    return true;
}

/* 8014A8D4-8014A974       .text procBowSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowSubject() {
    dComIfGp_setDoStatus(7);

    if(mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    }

    if(checkNextMode(0) == 0) {
        setBodyAngleToCamera();
        m35EC = mFrameCtrlUpper[UPPER_MOVE2_e].getFrame();
    }

    return true;
}

/* 8014A974-8014AA2C       .text procBowMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowMove_init() {
    /* Nonmatching */
}

/* 8014AA2C-8014AB5C       .text procBowMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procBowMove() {
    /* Nonmatching */
}
