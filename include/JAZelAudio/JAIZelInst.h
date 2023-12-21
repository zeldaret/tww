#ifndef JAIZELINST_H
#define JAIZELINST_H

#include "dolphin/types.h"

class JAIZelInst {
public:
    JAIZelInst();
    ~JAIZelInst() {}
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
    /* 0x00 */ int field_0x0;
    /* 0x04 */ u8 field_0x4[5];
    /* 0x0C */ int field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ int field_0x14;
    /* 0x18 */ u8 field_0x18[0x1e - 0x18];
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ u8 mMelodyNum;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ u8 field_0x34;
    /* 0x38 */ int field_0x38;
    /* 0x3C */ int field_0x3c;
    /* 0x40 */ int field_0x40;
    /* 0x44 */ int field_0x44;
    /* 0x48 */ u8 field_0x48;
};

#endif /* JAIZELINST_H */
