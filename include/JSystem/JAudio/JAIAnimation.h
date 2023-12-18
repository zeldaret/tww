#ifndef JAIANIMATION_H
#define JAIANIMATION_H

#include "global.h"

class Vec;
class JAISound;
class JAIBasic;
namespace JAInter {
    class Actor;
};
class JAIAnimeFrameSoundData;

struct JAIAnimeSound__Slot {
    /* 0x0 */ u8 mbIsPlaying;
    /* 0x4 */ JAISound* mpSound;
    /* 0x8 */ void* mpData;
};

class JAIAnimeSound {
public:
    /* 0x00 */ JAIAnimeSound__Slot mSlots[8];
    /* 0x60 */ u32 field_0x60;
    /* 0x64 */ u32 field_0x64;
    /* 0x68 */ u32 field_0x68;
    /* 0x6C */ u32 field_0x6c;
    /* 0x70 */ void* field_0x70[2];
    /* 0x78 */ int mDataCounterInc;
    /* 0x7C */ int mDataCounterLimit;
    /* 0x80 */ u32 mDataCounter;
    /* 0x84 */ int mLoopCount;
    /* 0x88 */ f32 mCurrentTime;
    /* 0x8C */ u8 field_0x8c[0x90 - 0x8C];
    /* 0x90 */ u16* mpData;
    /* 0x94 */ /* vtable */

public:
    JAIAnimeSound();
    void initActorAnimSound(void*, u32, f32);
    void setAnimSoundVec(JAIBasic*, Vec*, f32, f32, u32, u8);
    void setAnimSoundActor(JAIBasic*, JAInter::Actor*, f32, f32, u8);
    void playActorAnimSound(JAIBasic*, JAInter::Actor*, f32, u8);
    virtual void startAnimSound(void*, u32, JAISound**, JAInter::Actor*, u8);
    virtual void setSpeedModifySound(JAISound*, JAIAnimeFrameSoundData*, f32);
    void stop();
};  // Size: 0x98

#endif /* JAIANIMATION_H */
