#ifndef D_PATH_H
#define D_PATH_H

#include "d/d_bg_s.h"
#include "dolphin/types.h"

struct dPath__Point {
    /* 0x00 */ u8 mArg0;
    /* 0x01 */ u8 mArg1;
    /* 0x02 */ u8 mArg2;
    /* 0x03 */ u8 mArg3;
    /* 0x04 */ cXyz mPos;
};

struct dPath {
    /* 0x00 */ u16 mNum;
    /* 0x02 */ u16 mNextPathId;
    /* 0x04 */ u8 mArg0;
    /* 0x05 */ u8 mLoops;
    /* 0x06 */ u8 field4_0x6;
    /* 0x07 */ u8 field5_0x7;
    /* 0x08 */ dPath__Point* mpPnt;
};

dPath__Point* dPath_GetPnt(dPath*, int);
dPath* dPath_GetRoomPath(int, int);
dPath* dPath_GetNextRoomPath(dPath*, int);
void dPath_GetPolyRoomPathVec(cBgS_PolyInfo&, cXyz*, int*);

#endif /* D_PATH_H */
