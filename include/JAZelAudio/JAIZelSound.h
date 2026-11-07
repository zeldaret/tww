#ifndef JAIZELSOUND_H
#define JAIZELSOUND_H

#include "JSystem/JAudio/JAISound.h"

class JAIZelSound : public JAISound {
public:
    JAIZelSound();
#if VERSION <= VERSION_JPN
    // This is merged into the main .text section of JAIZelBasic for demo and
    // JPN. The cause is unclear but it gets its own .text section if it's
    // implemented in another file, so we implement it in JAIZelBasic.cpp as a
    // fakematch.
    ~JAIZelSound();
#else
    ~JAIZelSound() {}
#endif

    virtual f32 setDistanceVolumeCommon(f32, u8);
    virtual void setSeDistanceVolume(u8);
    virtual void setSeDistancePan(u8);
    virtual void setSeDistanceDolby(u8);
};

#endif /* JAIZELSOUND_H */
