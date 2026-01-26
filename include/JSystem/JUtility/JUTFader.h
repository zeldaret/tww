#ifndef JUTFADER_H
#define JUTFADER_H

#include "JSystem/JGeometry.h"
#include "JSystem/JUtility/TColor.h"

class JUTFader {
public:
    enum EStatus {
        WaitOut,
        WaitIn,
        FadeIn,
        FadeOut,
    };

    JUTFader(int, int, int, int, JUtility::TColor);
    void control();

    virtual ~JUTFader() {};
    virtual bool startFadeIn(int);
    virtual bool startFadeOut(int);
    virtual void draw();

    s32 getStatus() const { return mStatus; }
    void setColor(JUtility::TColor color) { mColor.set(color); }

    /* 0x04 */ s32 mStatus;
    /* 0x08 */ u16 mFadeTime;
    /* 0x0A */ u16 mTimer;
    /* 0x0C */ JUtility::TColor mColor;
    /* 0x10 */ JGeometry::TBox2<f32> mBox;
    /* 0x20 */ int mDelayTimer;
    /* 0x24 */ u32 mDelayStatus;
};

#endif /* JUTFADER_H */
