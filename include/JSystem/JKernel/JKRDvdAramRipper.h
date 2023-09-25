#ifndef JKRDVDARAMRIPPER_H
#define JKRDVDARAMRIPPER_H

#include "JSystem/JKernel/JKRDvdRipper.h"
#include "dolphin/types.h"

class JKRAramBlock;
class JKRAramStreamCommand;

class JKRADCommand {
public:
    JKRADCommand();
    ~JKRADCommand();

    /* 0x00 */ JSULink<JKRADCommand> mLink;
    /* 0x10 */ JKRDvdFile* mDvdFile;
    /* 0x14 */ u32 mOffset;
    /* 0x18 */ u32 field_0x18;
    /* 0x1C */ u32 mAddress;
    /* 0x20 */ JKRAramBlock* mBlock;
    /* 0x24 */ JKRExpandSwitch mExpandSwitch;
    /* 0x28 */ int field_0x28;
    /* 0x2C */ int field_0x2c;
    /* 0x30 */ int field_0x30;
    /* 0x34 */ int field_0x34;
    /* 0x38 */ int field_0x38;
    /* 0x3C */ int field_0x3c;
    /* 0x40 */ void (*mCallback)(u32);
    /* 0x44 */ int field_0x44;
    /* 0x48 */ bool field_0x48;
    /* 0x4C */ JKRAramStreamCommand* mStreamCommand;
};

class JKRDvdFile;
class JKRDvdAramRipper {
public:
    static JKRAramBlock* loadToAram(s32, u32, JKRExpandSwitch, u32, u32);
    static JKRAramBlock* loadToAram(JKRDvdFile*, u32, JKRExpandSwitch, u32, u32);
    static JKRADCommand* loadToAram_Async(JKRDvdFile*, u32, JKRExpandSwitch, void (*)(u32), u32,
                                          u32);
    static JKRADCommand* callCommand_Async(JKRADCommand*);
    static bool syncAram(JKRADCommand*, int);

    static u32 getSzpBufferSize() { return sSzpBufferSize; }
    static void setSzpBufferSize(u32 size) { sSzpBufferSize = size; }

    static JSUList<JKRADCommand> sDvdAramAsyncList;
    static u32 sSzpBufferSize;
    static bool errorRetry;
};

inline JKRAramBlock *JKRDvdToAram(s32 entrynum, u32 p2, JKRExpandSwitch expSwitch, u32 p4, u32 p5) {
    return JKRDvdAramRipper::loadToAram(entrynum, p2, expSwitch, p4, p5);
}

#endif /* JKRDVDARAMRIPPER_H */
