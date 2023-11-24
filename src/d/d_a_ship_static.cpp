/*
 * d_a_ship_static.cpp
 */
#include "d/actor/d_a_ship.h"

void daShip_c::initStartPos(const cXyz* pos, short rotY) {
    current.pos.x = pos->x;
    current.pos.y = pos->y;
    current.pos.z = pos->z;
    next.pos.x = pos->x;
    next.pos.y = pos->y;
    next.pos.z = pos->z;
    shape_angle.y = rotY;
    current.angle.y = shape_angle.y;
    m0358 &= 0xffffffef;
    mGravity = -2.5f;

    mWaveL.remove();
    mWaveR.remove();

    mSplash.remove();
    mTrack.remove();
    m1970.end();
    m1984.end();
    m1998.end();
    m19AC.end();
    m19C0.end();
}

