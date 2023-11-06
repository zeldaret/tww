#ifndef JAIZELINST_H
#define JAIZELINST_H

#include "dolphin/types.h"

class JAIZelInst {
public:
    JAIZelInst();
    void reset();
    void playArmSwing(s32, s32);
    void stopArmSwing();
    void setStickPos(s32, s32);
    void play();
    void setBeat(s32);
    void setVolume(f32);
    void metronomePlay(s32, s32);
    void judge(s32, s32);
    void ambientPlay();
    void armSoundPlay(s32);
    f32 getMelodyPattern(s32, s32, s32*);
    void getMelodyBeat(s32);
    void getMelodyGFrames(s32);
    void melodyPlay(s32);
    void melodyStop();

public:
    /* 0x00 */ u8 pad[0x1F];
    /* 0x1F */ u8 mMelodyNum;
};

#endif /* JAIZELINST_H */
