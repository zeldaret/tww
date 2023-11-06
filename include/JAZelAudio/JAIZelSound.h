#ifndef JAIZELSOUND_H
#define JAIZELSOUND_H

#include "dolphin/types.h"

class JAIZelSound /* : public JAISound */ {
public:
    JAIZelSound();
    ~JAIZelSound() {}

    void setDistanceVolumeCommon(f32, u8);
    void setSeDistanceVolume(u8);
    void setSeDistancePan(u8);
    void setSeDistanceDolby(u8);
};

#endif /* JAIZELSOUND_H */
