#ifndef CARD_H
#define CARD_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct CARDFileInfo {
    /* 0x00 */ s32 chan;
    /* 0x04 */ s32 fileNo;
    /* 0x08 */ s32 offset;
    /* 0x0C */ s32 length;
    /* 0x10 */ u16 iBlock;
    /* 0x12 */ u16 __padding;
};

enum {
    CARD_ERROR_UNLOCKED =  1,
    CARD_ERROR_READY =  0,
    CARD_ERROR_BUSY = -1,
    CARD_ERROR_WRONGDEVICE = -2,
    CARD_ERROR_NOCARD = -3,
    CARD_ERROR_NOFILE = -4,
    CARD_ERROR_IOERROR = -5,
    CARD_ERROR_BROKEN = -6,
    CARD_ERROR_EXIST = -7,
    CARD_ERROR_NOENT = -8,
    CARD_ERROR_INSSPACE = -9,
    CARD_ERROR_NOPERM = -10,
    CARD_ERROR_LIMIT = -11,
    CARD_ERROR_NAMETOOLONG = -12,
    CARD_ERROR_ENCODING = -13,
    CARD_ERROR_CANCELED = -14,
    CARD_ERROR_FATAL_ERROR = -128,
};

void CARDInit();
BOOL CARDProbe(s32);
s32 CARDOpen(s32, const char*, CARDFileInfo*);
s32 CARDClose(CARDFileInfo*);
s32 CARDCreate(s32, const char*, s32, CARDFileInfo*);
s32 CARDFormat(s32);
s32 CARDProbeEx(s32, s32*, s32*);
s32 CARDUnmount(s32);
s32 CARDMount(s32, void*, void*);
s32 CARDCheck(s32);
s32 CARDFreeBlocks(s32, s32*, s32*);

#ifdef __cplusplus
}
#endif

#endif /* CARD_H */
