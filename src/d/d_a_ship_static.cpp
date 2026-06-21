/**
 * d_a_ship_static.cpp
 * King of Red Lions - Static
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_ship.h"

/* 80067D94-80067E78       .text initStartPos__8daShip_cFPC4cXyzs */
void daShip_c::initStartPos(const cXyz* pos, short rotY) {
    current.pos = *pos;
    old.pos = *pos;
    shape_angle.y = rotY;
    current.angle.y = shape_angle.y;
    offStateFlg(daSFLG_UNK10_e);
    gravity = -2.5f;

    mWaveL.remove();
    mWaveR.remove();
    mSplash.remove();
    mTrack.remove();
    mRipple.remove();
    m1984.remove();
    m1998.remove();
    m19AC.remove();
    m19C0.remove();
}
