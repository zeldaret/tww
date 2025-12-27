#ifndef JAIANIMATION_H
#define JAIANIMATION_H

#include "dolphin/types.h"

struct Vec;
class JAISound;
class JAIBasic;
namespace JAInter {
    class Actor;
};

// BAS sound entry
struct JAIAnimeFrameSoundData {
    /* 0x00 */ u32 mSoundID;
    /* 0x04 */ f32 mStartFrame;
    /* 0x08 */ f32 mEndFrame;
    /* 0x0C */ f32 mPitch;
    /* 0x10 */ u32 mPlayFlags;
    /* 0x14 */ u8 mVolume;
    /* 0x15 */ s8 mPitchFactor;
    /* 0x16 */ u8 mLoopCount;
    /* 0x17 */ u8 mPanning;
    /* 0x18 */ s8 mVolumeFactor;
    /* 0x19 */ u8 field_0x19[0x20 - 0x19]; // Padding
};  // Size: 0x20

// BAS header
struct JAIAnimeSoundData {
    /* 0x00 */ u16 datas; // Entry count
    /* 0x02 */ u16 field_0x02;
    /* 0x04 */ void* field_0x04;
    /* 0x08 */ JAIAnimeFrameSoundData mAfsData[];
};

struct JAIAnimeSound__Slot {
    /* 0x0 */ u8 mbIsPlaying;
    /* 0x4 */ JAISound* mpSound;
    /* 0x8 */ JAIAnimeFrameSoundData* mpAfsData;
};

class JAIAnimeSound {
public:
    /* 0x00 */ JAIAnimeSound__Slot mSlots[8];
    /* 0x60 */ u32 field_0x60;
    /* 0x64 */ u32 field_0x64;
    /* 0x68 */ u32 field_0x68;
    /* 0x6C */ u32 field_0x6c;
    /* 0x70 */ void* field_0x70[2];
    /* 0x78 */ u32 mDataCounterInc;
    /* 0x7C */ int mDataCounterLimit;
    /* 0x80 */ u32 dataCounter;
    /* 0x84 */ u32 mLoopCount;
    /* 0x88 */ f32 mCurrentTime;
    /* 0x8C */ u8 field_0x8c[0x90 - 0x8C];
    /* 0x90 */ JAIAnimeSoundData* mpAsData;
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
