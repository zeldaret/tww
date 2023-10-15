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
    field_0x0358 &= 0xffffffef;
    mGravity = -2.5;


    mWaveR.remove();
    mWaveL.remove();

    mSplash.remove();
    mTrack.remove();
    field_0x1970.end();
    field_0x1984.end();
    field_0x1998.end();
    field_0x19ac.end();
    field_0x19c0.end();
}

