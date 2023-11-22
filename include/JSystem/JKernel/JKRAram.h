#ifndef JKRARAM_H
#define JKRARAM_H

#include "JSystem/JKernel/JKRAramHeap.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JKernel/JKRThread.h"

class JKRHeap;
class JKRAMCommand;
class JKRAramBlock;
class JKRAram : public JKRThread {
private:
    JKRAram(u32, u32, s32);
    virtual ~JKRAram();

    /* vt[03] */ void* run(void); /* override */

public:
    u32 getAudioMemory() const { return mAudioMemoryPtr; }
    u32 getAudioMemSize() const { return mAudioMemorySize; }
    u32 getGraphMemory() const { return mGraphMemoryPtr; }
    u32 getGraphMemSize() const { return mGraphMemorySize; }
//private:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRThread
    /* 0x68 */ u32 mAudioMemoryPtr;
    /* 0x6C */ u32 mAudioMemorySize;
    /* 0x70 */ u32 mGraphMemoryPtr;
    /* 0x74 */ u32 mGraphMemorySize;
    /* 0x78 */ u32 mAramMemoryPtr;
    /* 0x7C */ u32 mAramMemorySize;
    /* 0x80 */ JKRAramHeap* mAramHeap;
    /* 0x84 */ u32 mStackArray[3];

public:
    static JKRAram* create(u32, u32, s32, s32, s32);
    static bool checkOkAddress(u8*, u32, JKRAramBlock*, u32);
    static void changeGroupIdIfNeed(u8*, int);
    static JKRAramBlock* mainRamToAram(u8*, u32, u32, JKRExpandSwitch, u32, JKRHeap*, int);
    static JKRAramBlock* mainRamToAram(u8*, JKRAramBlock*, u32, JKRExpandSwitch, u32, JKRHeap*, int);
    static u8* aramToMainRam(u32, u8*, u32, JKRExpandSwitch, u32, JKRHeap*, int, u32*);
    static u8* aramToMainRam(JKRAramBlock*, u8*, u32, u32, JKRExpandSwitch, u32, JKRHeap*, int, u32*);
    static void dump(void);

    static JKRAram* getManager() { return sAramObject; }
    static JKRAramHeap* getAramHeap() { return getManager()->mAramHeap; }
    static JSUList<JKRAMCommand>& getCommandList() { return sAramCommandList; }

    static u8 decideAramGroupId(int groupId) {
        JKRAramHeap* heap;
        u8 finalGroupId;

        if (groupId < 0) {
            return getAramHeap()->getCurrentGroupID();
        }

        return (u8)groupId;
    }

    static u32 getSzpBufferSize() { return sSzpBufferSize; }
    static void setSzpBufferSize(u32 size) { sSzpBufferSize = size; }

    static OSMessageQueue sMessageQueue;

private:
    static JKRAram* sAramObject;
    static u32 sSzpBufferSize;
    static OSMessage sMessageBuffer[4];
    static JSUList<JKRAMCommand> sAramCommandList;
};

inline JKRAramBlock* JKRAllocFromAram(u32 size, JKRAramHeap::EAllocMode allocMode) {
    return JKRAram::getAramHeap()->alloc(size, allocMode);
}

inline void JKRFreeToAram(JKRAramBlock* block) {
    JKRAram::getAramHeap()->free(block);
}

inline u8* JKRAramToMainRam(u32 p1, u8* p2, u32 p3, JKRExpandSwitch p4, u32 p5, JKRHeap* p6,
                             int p7, u32* p8) {
    return JKRAram::aramToMainRam(p1, p2, p3, p4, p5, p6, p7, p8);
}

inline JKRAramBlock *JKRMainRamToAram(u8 *buf, u32 bufSize, u32 alignedSize, JKRExpandSwitch expandSwitch, u32 fileSize, JKRHeap *heap, int id) {
    return JKRAram::mainRamToAram(buf, bufSize, alignedSize, expandSwitch, fileSize, heap, id);
}

// void JKRDecompressFromAramToMainRam(u32, void*, u32, u32, u32, u32*);

#endif /* JKRARAM_H */
