/**
 * d_a_player_boomerang.inc
 *
 * Code relating to the Boomerang item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_boomerang.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"

/* 8014956C-80149590       .text checkBoomerangAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkBoomerangAnime() const {
    /* Nonmatching */
}

/* 80149590-80149698       .text throwBoomerang__9daPy_lk_cFv */
void daPy_lk_c::throwBoomerang() {
    /* Nonmatching */
}

/* 80149698-801497A4       .text returnBoomerang__9daPy_lk_cFv */
void daPy_lk_c::returnBoomerang() {
    /* Nonmatching */
}

/* 801497A4-8014984C       .text checkNextActionBoomerangReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionBoomerangReady() {
    /* Nonmatching */
}

/* 8014984C-801498D8       .text checkNextActionBoomerangFly__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionBoomerangFly() {
    /* Nonmatching */
}

/* 801498D8-80149964       .text checkNextBoomerangMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextBoomerangMode() {
    /* Nonmatching */
}

/* 80149964-80149A44       .text changeBoomerangCatchProc__9daPy_lk_cFv */
void daPy_lk_c::changeBoomerangCatchProc() {
    /* Nonmatching */
}

/* 80149A44-80149AF0       .text procBoomerangSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangSubject_init() {
    if(mCurProc == daPyProc_BOOMERANG_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_BOOMERANG_SUBJECT_e);

    mVelocity = 0.0f;

    setActAnimeUpper(LKANM_BCK_BOOMWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);

    dComIfGp_setPlayerStatus0(0, daPyStts0_BOOMERANG_AIM_e);

    current.angle.y = shape_angle.y;

    return true;
}

/* 80149AF0-80149C00       .text procBoomerangSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangSubject() {
    if(!checkItemModeActorPointer()) {
        return true;
    }

    if(checkBoomerangReadyAnime()) {
        dComIfGp_setDoStatus(7);
    }

    setShapeAngleToAtnActor();

    if(mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    }

    if(checkNextMode(0) == 0) {
        if(setBodyAngleToCamera()) {
            daBoomerang_c* boomerang = (daBoomerang_c*)mActorKeepEquip.getActor();
            if(boomerang != NULL) {
                cXyz sight;
                checkSightLine(boomerang->getFlyMax(), &sight);
                mSightPacket.setPos(&sight);
                mSightPacket.onDrawFlg();
            }
        }
    }
    else {
        mSightPacket.offDrawFlg();
    }

    return true;
}

/* 80149C00-80149CC8       .text procBoomerangMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangMove_init() {
    /* Nonmatching */
}

/* 80149CC8-80149DA4       .text procBoomerangMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangMove() {
    /* Nonmatching */
}

/* 80149DA4-80149E1C       .text procBoomerangCatch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangCatch_init() {
    /* Nonmatching */
}

/* 80149E1C-80149ECC       .text procBoomerangCatch__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangCatch() {
    /* Nonmatching */
}
