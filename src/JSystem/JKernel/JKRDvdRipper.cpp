//
// Generated by dtk
// Translation Unit: JKRDvdRipper.cpp
//

#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "string.h"
#include "dolphin/os/OS.h"
#include "dolphin/vi/vi.h"
#include "global.h"

static int JKRDecompressFromDVD(JKRDvdFile*, void*, u32, u32, u32, u32);
static int decompSZS_subroutine(u8*, u8*);
static u8* firstSrcData();
static u8* nextSrcData(u8*);

/* 802BCD4C-802BCE00       .text loadToMainRAM__12JKRDvdRipperFPCcPUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPi */
void* JKRDvdRipper::loadToMainRAM(const char* name, u8* dst, JKRExpandSwitch expandSwitch, u32 dstLength, JKRHeap* heap, EAllocDirection allocDirection, u32 offset, int* pCompression) {
    JKRDvdFile file;
    if (!file.open(name)) {
        return NULL;
    }
    return loadToMainRAM(&file, dst, expandSwitch, dstLength, heap, allocDirection, offset, pCompression);
}

/* 802BCE00-802BCEB4       .text loadToMainRAM__12JKRDvdRipperFlPUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPi */
void* JKRDvdRipper::loadToMainRAM(s32 entryNumber, u8* dst, JKRExpandSwitch expandSwitch, u32 dstLength, JKRHeap* heap, EAllocDirection allocDirection, u32 offset, int* pCompression) {
    JKRDvdFile file;
    if (!file.open(entryNumber)) {
        return NULL;
    }
    return loadToMainRAM(&file, dst, expandSwitch, dstLength, heap, allocDirection, offset, pCompression);
}

bool JKRDvdRipper::errorRetry = true;

/* 802BCEB4-802BD324       .text loadToMainRAM__12JKRDvdRipperFP10JKRDvdFilePUc15JKRExpandSwitchUlP7JKRHeapQ212JKRDvdRipper15EAllocDirectionUlPi */
void* JKRDvdRipper::loadToMainRAM(JKRDvdFile* dvdFile, u8* dst, JKRExpandSwitch expandSwitch, u32 dstLength, JKRHeap* heap, EAllocDirection allocDirection, u32 offset, int* pCompression) {
    s32 fileSizeAligned;
    bool hasAllocated = false;
    JKRCompression compression = COMPRESSION_NONE;
    u32 expandSize;
    u8 *mem = NULL;

    fileSizeAligned = ALIGN_NEXT(dvdFile->getFileSize(), 32);
    if (expandSwitch == EXPAND_SWITCH_UNKNOWN1) {
        u8 buffer[0x40];
        u8 *bufPtr = (u8 *)ALIGN_NEXT((u32)buffer, 32);
        while (true) {
            int readBytes = DVDReadPrio(dvdFile->getFileInfo(), bufPtr, 0x20, 0, 2);
            if (readBytes >= 0) {
                break;
            }

            if (readBytes == -3 || !isErrorRetry()) {
                return NULL;
            }

            VIWaitForRetrace();
        }
        DCInvalidateRange(bufPtr, 0x20);

        compression = JKRCheckCompressed(bufPtr);
        expandSize = JKRDecompExpandSize(bufPtr);
    }

    if (pCompression) {
        *pCompression = (int)compression;
    }

    if (expandSwitch == EXPAND_SWITCH_UNKNOWN1 && compression != COMPRESSION_NONE) {
        if (dstLength != 0 && expandSize > dstLength) {
            expandSize = dstLength;
        }
        if (dst == NULL) {
            dst = (u8 *)JKRAllocFromHeap(heap, expandSize, allocDirection == ALLOC_DIRECTION_FORWARD ? 32 : -32);
            hasAllocated = true;
        }
        if (dst == NULL) {
            return NULL;
        }
        if (compression == COMPRESSION_YAY0) {
            mem = (u8 *)JKRAllocFromHeap((heap), fileSizeAligned, 32);
            if (mem == NULL) {
                if (hasAllocated == true) {
                    i_JKRFree(dst);
                    return NULL;
                }
            }
        }
    } else {
        if (dst == NULL) {
            dst = (u8 *)JKRAllocFromHeap(heap, fileSizeAligned - offset, allocDirection == ALLOC_DIRECTION_FORWARD ? 32 : -32);
            hasAllocated = true;
        }
        if (dst == NULL) {
            return NULL;
        }
    }
    if (compression == COMPRESSION_NONE) {
        JKRCompression compression2 = COMPRESSION_NONE; // maybe for a sub archive?

        if (offset != 0) {
            u8 buffer[0x40];
            u8 *bufPtr = (u8 *)ALIGN_NEXT((u32)buffer, 32);
            while (true) {
                int readBytes = DVDReadPrio(dvdFile->getFileInfo(), bufPtr, 32, (s32)offset, 2);
                if (readBytes >= 0) {
                    break;
                }

                if (readBytes == -3 || !isErrorRetry()) {
                    if (hasAllocated == true) {
                        i_JKRFree(dst);
                    }
                    return NULL;
                }
                VIWaitForRetrace();
            }
            DCInvalidateRange(bufPtr, 32);

            compression2 = JKRCheckCompressed(bufPtr);
        }
        if ((compression2 == COMPRESSION_NONE || expandSwitch == EXPAND_SWITCH_UNKNOWN2) || expandSwitch == EXPAND_SWITCH_UNKNOWN0) {
            s32 size = fileSizeAligned - offset;
            if (dstLength != 0 && dstLength < size)
                size = dstLength; // probably a ternary
            while (true) {
                int readBytes = DVDReadPrio(dvdFile->getFileInfo(), dst, size, (s32)offset, 2);
                if (readBytes >= 0) {
                    break;
                }

                if (readBytes == -3 || !isErrorRetry()) {
                    if (hasAllocated == true) {
                        i_JKRFree(dst);
                    }
                    return NULL;
                }
                VIWaitForRetrace();
            }

            return dst;
        }
        else if (compression2 == COMPRESSION_YAZ0) {
            JKRDecompressFromDVD(dvdFile, dst, fileSizeAligned, dstLength, 0, offset);
        } else {
            OSPanic(__FILE__, VERSION_SELECT(337, 314, 314), "Sorry, not prepared for SZP resource\n");
        }
        return dst;
    }
    else if (compression == COMPRESSION_YAY0)
    {
        // SZP decompression
        // s32 readoffset = startOffset;
        if (offset != 0) {
            OSPanic(__FILE__, VERSION_SELECT(347, 324, 324), ":::Not support SZP with offset read");
        }
        while (true) {
            int readBytes = DVDReadPrio(dvdFile->getFileInfo(), mem, fileSizeAligned, 0, 2);
            if (readBytes >= 0)
                break;

            if (readBytes == -3 || !isErrorRetry()) {
                if (hasAllocated == true)
                    i_JKRFree(dst);

                i_JKRFree(mem);
                return NULL;
            }
            VIWaitForRetrace();
        }
        JKRDecompress(mem, dst, expandSize, offset);
        i_JKRFree(mem);
        return dst;
    } else if (compression == COMPRESSION_YAZ0) {
        if (JKRDecompressFromDVD(dvdFile, dst, fileSizeAligned, expandSize, offset, 0) != 0u)
        {
            if (hasAllocated)
                i_JKRFree(dst);
            dst = NULL;
        }
        return dst;
    }
    else if (hasAllocated)
    {
        i_JKRFree(dst);
        dst = NULL;
    }
    return NULL;
}

JSUList<JKRDMCommand> JKRDvdRipper::sDvdAsyncList;
static OSMutex decompMutex;
u32 JKRDvdRipper::sSzpBufferSize = 0x00000400;
static u8* szpBuf;
static u8* szpEnd;
static u8* refBuf;
static u8* refEnd;
static u8* refCurrent;
static u32 srcOffset;
static u32 transLeft;
static u8* srcLimit;
static JKRDvdFile* srcFile;
static u32 fileOffset;
static u32 readCount;
static u32 maxDest;
static bool isInitMutex;

/* 802BD324-802BD4F0       .text JKRDecompressFromDVD__FP10JKRDvdFilePvUlUlUlUl */
static int JKRDecompressFromDVD(JKRDvdFile* dvdFile, void* dst, u32 fileSize, u32 inMaxDest, u32 inFileOffset, u32 inSrcOffset) {
    BOOL interrupts = OSDisableInterrupts();
    if (isInitMutex == false) {
        OSInitMutex(&decompMutex);
        isInitMutex = true;
    }
    OSRestoreInterrupts(interrupts);
    OSLockMutex(&decompMutex);
    int bufSize = JKRDvdRipper::getSzpBufferSize();
    szpBuf = (u8 *)JKRAllocFromSysHeap(bufSize, -0x20);
    JUT_ASSERT(VERSION_SELECT(913, 884, 884), szpBuf != 0);

    szpEnd = szpBuf + bufSize;
    if (inFileOffset != 0) {
        refBuf = (u8 *)JKRAllocFromSysHeap(0x1120, -4);
        JUT_ASSERT(VERSION_SELECT(922, 893, 893), refBuf != 0);
        refEnd = refBuf + 0x1120;
        refCurrent = refBuf;
    } else {
        refBuf = NULL;
    }
    srcFile = dvdFile;
    srcOffset = inSrcOffset;
    transLeft = fileSize - inSrcOffset;
    fileOffset = inFileOffset;
    readCount = 0;
    maxDest = inMaxDest;
    u8 *data = firstSrcData();
    u32 result = (data != NULL) ? decompSZS_subroutine(data, (u8 *)dst) : -1; // figure out correct datatypes
    u32 decompressedSize = ((u32*)data)[1];
    i_JKRFree(szpBuf);
    if (refBuf) {
        i_JKRFree(refBuf);
    }
    DCStoreRangeNoSync(dst, decompressedSize);
    OSUnlockMutex(&decompMutex);
    return result;
}

/* 802BD4F0-802BD784       .text decompSZS_subroutine__FPUcPUc */
static int decompSZS_subroutine(u8* src, u8* dest) {
    u8 *endPtr;
    s32 validBitCount = 0;
    s32 currCodeByte = 0;
    u32 ts = 0;

    if (src[0] != 'Y' || src[1] != 'a' || src[2] != 'z' || src[3] != '0') {
        return -1;
    }

    SYaz0Header *header = (SYaz0Header *)src;
    endPtr = dest + (header->length - fileOffset);
    if (endPtr > dest + maxDest) {
        endPtr = dest + maxDest;
    }

    src += 0x10;
    do {
        if (validBitCount == 0) {
            if ((src > srcLimit) && transLeft) {
                src = nextSrcData(src);
                if (!src) {
                    return -1;
                }
            }
            currCodeByte = *src;
            validBitCount = 8;
            src++;
        }
        if (currCodeByte & 0x80) {
            if (fileOffset != 0) {
                if (readCount >= fileOffset) {
                    *dest = *src;
                    dest++;
                    ts++;
                    if (dest == endPtr) {
                        break;
                    }
                }
                *(refCurrent++) = *src;
                if (refCurrent == refEnd) {
                    refCurrent = refBuf;
                }
                src++;
            } else {
                *dest = *src;
                dest++;
                src++;
                ts++;
                if (dest == endPtr) {
                    break;
                }
            }
            readCount++;
        } else {
            u32 dist = ((src[0] & 0x0f) << 8) | src[1];
            s32 numBytes = src[0] >> 4;
            src += 2;
            u8 *copySource;
            if (fileOffset != 0) {
                copySource = refCurrent - dist - 1;
                if (copySource < refBuf) {
                    copySource += refEnd - refBuf;
                }
            } else {
                copySource = dest - dist - 1;
            }
            if (numBytes == 0) {
                numBytes = *src + 0x12;
                src += 1;
            } else {
                numBytes += 2;
            }
            if (fileOffset != 0) {
                do {
                    if (readCount >= fileOffset) {
                        *dest = *copySource;
                        dest++;
                        ts++;
                        if (dest == endPtr) {
                            break;
                        }
                    }
                    *(refCurrent++) = *copySource;
                    if (refCurrent == refEnd) {
                        refCurrent = refBuf;
                    }
                    copySource++;
                    if (copySource == refEnd) {
                        copySource = refBuf;
                    }
                    readCount++;
                    numBytes--;
                } while (numBytes != 0);
            } else {
                do {
                    *dest = *copySource;
                    dest++;
                    ts++;
                    if (dest == endPtr) {
                        break;
                    }
                    readCount++;
                    numBytes--;
                    copySource++;
                } while (numBytes != 0);
            }
        }
        currCodeByte <<= 1;
        validBitCount--;
    } while (dest < endPtr);
    return 0;
}

/* 802BD784-802BD84C       .text firstSrcData__Fv */
static u8* firstSrcData() {
    srcLimit = szpEnd - 0x19;
    u8* buffer = szpBuf;
    u32 bufSize = szpEnd - buffer;
    u32 length = transLeft < bufSize ? transLeft : bufSize;

    while (true) {
        int result = DVDReadPrio(srcFile->getFileInfo(), buffer, length, srcOffset, 2);
        if (result >= 0) {
            break;
        }

        if (result == -3 || !JKRDvdRipper::isErrorRetry()) {
            return NULL;
        }
        VIWaitForRetrace();
    }

    srcOffset += length;
    transLeft -= length;
    if (transLeft == 0) {
        srcLimit = buffer + length;
    }
    return buffer;
}

/* 802BD84C-802BD974       .text nextSrcData__FPUc */
static u8* nextSrcData(u8* src) {
    u32 limit = szpEnd - src;
    u8 *buf;
    if (IS_NOT_ALIGNED(limit, 0x20)) {
        buf = szpBuf + 0x20 - (limit & (0x20 - 1));
    } else {
        buf = szpBuf;
    }

    memcpy(buf, src, limit);
    u32 transSize = (u32)(szpEnd - (buf + limit));
    if (transSize > transLeft) {
        transSize = transLeft;
    }
    JUT_ASSERT(VERSION_SELECT(1228, 1176, 1176), transSize > 0);

    while (true) {
        s32 result = DVDReadPrio(srcFile->getFileInfo(), (buf + limit), transSize, srcOffset, 2);
        if (result >= 0) {
            break;
        }
        // bug: supposed to call isErrorRetry, but didn't
        if (result == -3 || !JKRDvdRipper::isErrorRetry) {
            return NULL;
        }

        VIWaitForRetrace();
    }
    srcOffset += transSize;
    transLeft -= transSize;
    if (transLeft == 0) {
        srcLimit = transSize + (buf + limit);
    }

    return buf;
}
