#ifndef JAIZELANIME_H
#define JAIZELANIME_H

#include "JSystem/JAudio/JAIAnimation.h"

class JAIZelAnime : public JAIAnimeSound {
public:
    JAIZelAnime() {}
    
    virtual void startAnimSound(void*, u32, JAISound**, JAInter::Actor*, u8);
    virtual void setSpeedModifySound(JAISound*, JAIAnimeFrameSoundData*, f32);
    
    void setAnimSound(Vec* pos, f32 frame, f32 rate, u32 mtrlSndId, s8 reverb);
    void setPlayPosition(f32);
};

#endif /* JAIZELANIME_H */
