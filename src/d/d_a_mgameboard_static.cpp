//
// Generated by dtk
// Translation Unit: d_a_mgameboard_static.cpp
//

#include "d/actor/d_a_mgameboard.h"

/* 800685F8-80068608       .text checkClearGame__11daMgBoard_cFv */
bool daMgBoard_c::checkClearGame() {
    return mSeaFightGame.mAliveShipNum == 0;
}

/* 80068608-80068610       .text getScore__11daMgBoard_cFv */
u8 daMgBoard_c::getScore() {
    return mSeaFightGame.mScore;
}

/* 80068610-80068624       .text reqStartGame__11daMgBoard_cFv */
void daMgBoard_c::reqStartGame() {
    mbEndGame = false;
    mbStartGame = true;
}

/* 80068624-80068638       .text checkEndGame__11daMgBoard_cFv */
bool daMgBoard_c::checkEndGame() {
    return mbEndGame;
}

/* 80068638-80068644       .text setGInfoDraw__11daMgBoard_cFv */
void daMgBoard_c::setGInfoDraw() {
    mbDraw = true;
}

/* 80068644-80068650       .text clrGInfoDraw__11daMgBoard_cFv */
void daMgBoard_c::clrGInfoDraw() {
    mbDraw = false;
}
