#ifndef CARD_H
#define CARD_H

#include "dolphin/dsp.h"
#include "dolphin/os/OS.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CARD_FILENAME_MAX 32
#define CARD_MAX_FILE 127
#define CARD_ICON_MAX 8

typedef void (*CARDCallback)(s32 chan, s32 result);

typedef struct CARDFileInfo {
    /* 0x00 */ s32 chan;
    /* 0x04 */ s32 fileNo;
    /* 0x08 */ s32 offset;
    /* 0x0C */ s32 length;
    /* 0x10 */ u16 iBlock;
    /* 0x12 */ u16 __padding;
} CARDFileInfo;

typedef struct CARDStat {
    /* 0x00 */ char fileName[CARD_FILENAME_MAX];
    /* 0x20 */ u32 length;
    /* 0x24 */ u32 time;
    /* 0x28 */ u8 gameName[4];
    /* 0x2C */ u8 company[2];
    /* 0x2E */ u8 bannerFormat;
    /* 0x30 */ u32 iconAddr;
    /* 0x34 */ u16 iconFormat;
    /* 0x36 */ u16 iconSpeed;
    /* 0x38 */ u32 commentAddr;
    /* 0x3C */ u32 offsetBanner;
    /* 0x40 */ u32 offsetBannerTlut;
    /* 0x44 */ u32 offsetIcon[CARD_ICON_MAX];
    /* 0x64 */ u32 offsetIconTlut;
    /* 0x68 */ u32 offsetData;
} CARDStat;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 _padding0;
    u8 bannerFormat;
    u8 fileName[CARD_FILENAME_MAX];
    u32 time;     // seconds since 01/01/2000 midnight
    u32 iconAddr; // 0xffffffff if not used
    u16 iconFormat;
    u16 iconSpeed;
    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u8 _padding1[2];
    u32 commentAddr; // 0xffffffff if not used
} CARDDir;

typedef struct CARDID {
    /* 0x000 */ u8 serial[32];
    /* 0x020 */ u16 deviceID;
    /* 0x022 */ u16 size;
    /* 0x024 */ u16 encode;
    /* 0x026 */ u8 padding[470];
    /* 0x1FC */ u16 checkSum;
    /* 0x1FE */ u16 checkSumInv;
} CARDID;

typedef struct CARDDecParam {
    /* 0x00 */ u8* inputAddr;
    /* 0x04 */ u32 inputLength;
    /* 0x08 */ u32 aramAddr;
    /* 0x0C */ u8* outputAddr;
} CARDDecParam;

typedef struct CARDControl {
    /* 0x000 */ BOOL attached;
    /* 0x004 */ s32 result;
    /* 0x008 */ u16 size;
    /* 0x00A */ u16 pageSize;
    /* 0x00C */ s32 sectorSize;
    /* 0x010 */ u16 cBlock;
    /* 0x012 */ u16 vendorID;
    /* 0x014 */ s32 latency;
    /* 0x018 */ u8 id[12];
    /* 0x024 */ int mountStep;
    /* 0x028 */ int formatStep;
    /* 0x028 */ u32 scramble;
    /* 0x02C */ DSPTaskInfo task;
    /* 0x080 */ void* workArea;
    /* 0x084 */ CARDDir* currentDir;
    /* 0x088 */ u16* currentFat;
    /* 0x08C */ OSThreadQueue threadQueue;
    /* 0x094 */ u8 cmd[9];
    /* 0x0A0 */ s32 cmdlen;
    /* 0x0A4 */ volatile u32 mode;
    /* 0x0A8 */ int retry;
    /* 0x0AC */ int repeat;
    /* 0x0B0 */ u32 addr;
    /* 0x0B4 */ void* buffer;
    /* 0x0B8 */ s32 xferred;
    /* 0x0BC */ u16 freeNo;
    /* 0x0BE */ u16 startBlock;
    /* 0x0C0 */ CARDFileInfo* fileInfo;
    /* 0x0C4 */ CARDCallback extCallback;
    /* 0x0C8 */ CARDCallback txCallback;
    /* 0x0CC */ CARDCallback exiCallback;
    /* 0x0D0 */ CARDCallback apiCallback;
    /* 0x0D4 */ CARDCallback xferCallback;
    /* 0x0D8 */ CARDCallback eraseCallback;
    /* 0x0DC */ CARDCallback unlockCallback;
    /* 0x0E0 */ OSAlarm alarm;
    /* 0x108 */ u32 cid;
    /* 0x10C */ const DVDDiskID* diskID;
} CARDControl;

typedef struct CARDDirCheck {
    /* 0x00 */ u8 padding0[56];
    /* 0x38 */ u16 padding1;
    /* 0x3A */ s16 checkCode;
    /* 0x3C */ u16 checkSum;
    /* 0x3E */ u16 checkSumInv;
} CARDDirCheck;

#define CARDGetBannerFormat(stat)     ((stat)->bannerFormat & 0x03)
#define CARDGetIconAnim(stat)         ((stat)->bannerFormat & 0x04)
#define CARDGetIconFormat(stat, n)    ((stat)->iconFormat >> (2 * (n)) & 0x03)
#define CARDGetIconSpeed(stat, n)     ((stat)->iconSpeed >> (2 * (n)) & 0x03)

#define CARDSetBannerFormat(stat, v)  ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~0x03) | (v)))
#define CARDSetIconAnim(stat, v)      ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~0x04) | (v)))
#define CARDSetIconFormat(stat, n, v) ((stat)->iconFormat = (u16)(((stat)->iconFormat & ~(0x03 << (2 * (n)))) | ((v) << (2 * (n)))))
#define CARDSetIconSpeed(stat, n, v)  ((stat)->iconSpeed = (u16)(((stat)->iconSpeed & ~(0x03 << (2 * (n)))) | ((v) << (2 * (n)))))

#define CARD_ENCODE_ANSI 0
#define CARD_ENCODE_SJIS 1

#define CARD_READ_SIZE 512
#define CARD_COMMENT_SIZE 64

#define CARD_ICON_WIDTH 32
#define CARD_ICON_HEIGHT 32

#define CARD_BANNER_WIDTH 96
#define CARD_BANNER_HEIGHT 32

#define CARD_STAT_ICON_NONE 0
#define CARD_STAT_ICON_C8 1
#define CARD_STAT_ICON_RGB5A3 2
#define CARD_STAT_ICON_MASK 3

#define CARD_STAT_BANNER_NONE 0
#define CARD_STAT_BANNER_C8 1
#define CARD_STAT_BANNER_RGB5A3 2
#define CARD_STAT_BANNER_MASK 3

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

#define CARD_ATTR_PUBLIC  0x04u
#define CARD_ATTR_NO_COPY 0x08u
#define CARD_ATTR_NO_MOVE 0x10u
#define CARD_ATTR_GLOBAL  0x20u
#define CARD_ATTR_COMPANY 0x40u

#define CARD_FAT_AVAIL 0x0000u
#define CARD_FAT_CHECKSUM 0x0000u
#define CARD_FAT_CHECKSUMINV 0x0001u
#define CARD_FAT_CHECKCODE 0x0002u
#define CARD_FAT_FREEBLOCKS 0x0003u
#define CARD_FAT_LASTSLOT 0x0004u

#define CARD_WORKAREA_SIZE (5 * 8 * 1024)

#define CARD_SEG_SIZE 0x200u
#define CARD_PAGE_SIZE 0x80u
#define CARD_MAX_SIZE 0x01000000U

#define CARD_NUM_SYSTEM_BLOCK 5
#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024u)

#define CARD_MAX_MOUNT_STEP (CARD_NUM_SYSTEM_BLOCK + 2)

#define CARD_STAT_SPEED_END 0
#define CARD_STAT_SPEED_FAST 1
#define CARD_STAT_SPEED_MIDDLE 2
#define CARD_STAT_SPEED_SLOW 3
#define CARD_STAT_SPEED_MASK 3

#define CARD_STAT_ANIM_LOOP   0
#define CARD_STAT_ANIM_BOUNCE 4
#define CARD_STAT_ANIM_MASK 0x4

#define CARD_RESULT_UNLOCKED       1
#define CARD_RESULT_READY          0
#define CARD_RESULT_BUSY          -1
#define CARD_RESULT_WRONGDEVICE   -2
#define CARD_RESULT_NOCARD        -3
#define CARD_RESULT_NOFILE        -4
#define CARD_RESULT_IOERROR       -5
#define CARD_RESULT_BROKEN        -6
#define CARD_RESULT_EXIST         -7
#define CARD_RESULT_NOENT         -8
#define CARD_RESULT_INSSPACE      -9
#define CARD_RESULT_NOPERM       -10
#define CARD_RESULT_LIMIT        -11
#define CARD_RESULT_NAMETOOLONG  -12
#define CARD_RESULT_ENCODING     -13
#define CARD_RESULT_CANCELED     -14
#define CARD_RESULT_FATAL_ERROR -128

#define CARDIsValidBlockNo(card, blockNo) ((blockNo) >= CARD_NUM_SYSTEM_BLOCK && (blockNo) < (card)->cBlock)
#define CARDGetDirCheck(dir) ((CARDDirCheck*)&(dir)[CARD_MAX_FILE])

void CARDInit();
BOOL CARDProbe(s32);
s32 CARDGetStatus(s32, s32, CARDStat*);
s32 CARDSetStatus(s32, s32, CARDStat*);
s32 CARDOpen(s32, const char*, CARDFileInfo*);
s32 CARDClose(CARDFileInfo*);
s32 CARDCreate(s32, const char*, u32, CARDFileInfo*);
s32 CARDFormat(s32);
s32 CARDProbeEx(s32, s32*, s32*);
s32 CARDUnmount(s32);
s32 CARDMount(s32 chan, void* workArea, CARDCallback detachCallback);
s32 CARDCheck(s32);
s32 CARDFreeBlocks(s32, s32*, s32*);
s32 CARDRead(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset);
s32 CARDWrite(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset);
s32 CARDGetSerialNo(s32, u64*);

extern CARDControl __CARDBlock[2];
extern DVDDiskID __CARDDiskNone;

#ifdef __cplusplus
}
#endif

#endif /* CARD_H */
