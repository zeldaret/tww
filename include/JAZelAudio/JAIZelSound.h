#ifndef JAIZELSOUND_H
#define JAIZELSOUND_H

#include "JSystem/JAudio/JAISound.h"

class JAIZelSound : public JAISound {
public:
    JAIZelSound();
    ~JAIZelSound() {}

    virtual f32 setDistanceVolumeCommon(f32, u8);
    virtual void setSeDistanceVolume(u8);
    virtual void setSeDistancePan(u8);
    virtual void setSeDistanceDolby(u8);
};

#endif /* JAIZELSOUND_H */
