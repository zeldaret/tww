#ifndef D_SPLINE_PATH_H
#define D_SPLINE_PATH_H

#include "dolphin/types.h"

class cXyz;

class d2DBSplinePath {
public:
    void Last() {}

    void Init(s32, s32);
    bool Step();
    cXyz Calc(cXyz*);
    f32 Calc(f32*);

public:
    /* 0x00 */ s32 mFrame;
    /* 0x04 */ s32 mKeyNum;
    /* 0x08 */ s32 mDuration;
    /* 0x0C */ s32 mState;
    /* 0x10 */ s32 mKeyNo;
    /* 0x14 */ s32 mEnd;
    /* 0x18 */ s32 field_0x18;
    /* 0x1C */ f32 mStep;
    /* 0x20 */ s32 field_0x20;
    /* 0x24 */ f32 mCurveWeight[3];
    /* 0x30 */ s32 mCurveKey[3];
    /* 0x3C */ void* mUser;
    /* 0x40 */ //void* vtbl; // XXX
    
    d2DBSplinePath() { Init(0, 0); }
    virtual ~d2DBSplinePath(){};
};

#endif /* D_SPLINE_PATH_H */
