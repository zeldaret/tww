#ifndef JKRDVDRIPPER_H
#define JKRDVDRIPPER_H

#include "JSystem/JKernel/JKRCompression.h"
#include "JSystem/JSupport/JSUList.h"

enum JKRExpandSwitch {
    EXPAND_SWITCH_UNKNOWN0 = 0,
    EXPAND_SWITCH_UNKNOWN1 = 1,
    EXPAND_SWITCH_UNKNOWN2 = 2,
};

struct SYaz0Header {
    u32 signature;
    u32 length;
};

class JKRDMCommand {
    JKRDMCommand();
    ~JKRDMCommand();
};

class JKRHeap;
class JKRDvdFile;
class JKRDvdRipper {
public:
    static JSUList<JKRDMCommand> sDvdAsyncList;
    static u32 sSZSBufferSize;

    enum EAllocDirection {
        UNKNOWN_EALLOC_DIRECTION = 0,
        ALLOC_DIRECTION_FORWARD = 1,
        ALLOC_DIRECTION_BACKWARD = 2,
    };

    static void setSZSBufferSize(u32 size) { sSZSBufferSize = size; }

    static void* loadToMainRAM(char const*, u8*, JKRExpandSwitch, u32, JKRHeap*, EAllocDirection,
                               u32, int*);
    static void* loadToMainRAM(long, u8*, JKRExpandSwitch, u32, JKRHeap*, EAllocDirection, u32,
                               int*);
    static void* loadToMainRAM(JKRDvdFile*, u8*, JKRExpandSwitch, u32, JKRHeap*, EAllocDirection,
                               u32, int*);

    static u8 isErrorRetry(void);
    inline static u32 getSZSBufferSize() { return sSZSBufferSize; }
};

// void JKRDecompressFromDVD(JKRDvdFile*, void*, u32, u32, u32, u32, u32*);

inline void* JKRDvdToMainRam(s32 entryNum, u8* dst, JKRExpandSwitch expandSwitch, u32 dstLength,
                             JKRHeap* heap, JKRDvdRipper::EAllocDirection allocDirection,
                             u32 offset, int* returnSize) {
    return JKRDvdRipper::loadToMainRAM(entryNum, dst, expandSwitch, dstLength, heap, allocDirection,
                                       offset, returnSize);
}

inline void* JKRDvdToMainRam(const char* name, u8* dst, JKRExpandSwitch expandSwitch, u32 dstLength,
                             JKRHeap* heap, JKRDvdRipper::EAllocDirection allocDirection,
                             u32 offset, int* returnSize) {
    return JKRDvdRipper::loadToMainRAM(name, dst, expandSwitch, dstLength, heap, allocDirection,
                                       offset, returnSize);
}

#endif /* JKRDVDRIPPER_H */
