#ifndef _DOLPHIN_GBAPRIV
#define _DOLPHIN_GBAPRIV

#include "dolphin/dsp.h"
#include "dolphin/gba/GBA.h"
#include "dolphin/os/OS.h"
#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GBATransferCallback)(s32 chan);

typedef struct GBASecParam {
    /* 0x00 */ u8 readbuf[4];
    /* 0x04 */ s32 paletteColor;
    /* 0x08 */ s32 paletteSpeed;
    /* 0x0C */ s32 length;
    /* 0x10 */ u32* out;
    /* 0x14 */ u8 _padding0[12];
    /* 0x20 */ u32 keyA;
    /* 0x24 */ s32 keyB;
    /* 0x28 */ u8 _padding1[24];
} GBASecParam ALIGN_DECL(32);  // Size: 0x40

typedef struct GBABootInfo {
    /* 0x00 */ s32 paletteColor;
    /* 0x04 */ s32 paletteSpeed;
    /* 0x08 */ u8* programp;
    /* 0x0C */ s32 length;
    /* 0x10 */ u8* status;
    /* 0x14 */ GBACallback callback;
    /* 0x18 */ u8 readbuf[4];
    /* 0x1C */ u8 writebuf[4];
    /* 0x20 */ int i;
    /* 0x24 */ OSTick start;
    /* 0x28 */ OSTime begin;
    /* 0x30 */ int firstXfer;
    /* 0x34 */ int curOffset;
    /* 0x38 */ u32 crc;
    /* 0x3C */ u32 dummyWord[7];
    /* 0x58 */ u32 keyA;
    /* 0x5C */ s32 keyB;
    /* 0x60 */ u32 initialCode;
    /* 0x64 */ int realLength;
} GBABootInfo;  // Size: 0x68

typedef struct GBAControl {
    /* 0x000 */ u8 output[5];
    /* 0x005 */ u8 input[5];
    /* 0x00C */ s32 outputBytes;
    /* 0x010 */ s32 inputBytes;
    /* 0x014 */ u8* status;
    /* 0x018 */ u8* ptr;
    /* 0x01C */ GBACallback callback;
    /* 0x020 */ s32 ret;
    /* 0x024 */ OSThreadQueue threadQueue;
    /* 0x030 */ OSTime delay;
    /* 0x038 */ GBATransferCallback proc;
    /* 0x040 */ GBABootInfo bootInfo;
    /* 0x0A8 */ DSPTaskInfo task;
    /* 0x0F8 */ GBASecParam* param;
} GBAControl;  // Size: 0x100

extern GBAControl __GBA[4];
extern BOOL __GBAReset;

void __GBAHandler(s32 chan, u32 error, OSContext* context);
void __GBASyncCallback(s32 chan, s32 ret);
s32 __GBASync(s32 chan);
OSTime __GBASetDelay(s32 chan, OSTime delay);
s32 __GBATransfer(s32 chan, s32 w1, s32 w2, GBATransferCallback callback);

#ifdef __cplusplus
}
#endif

#endif  // _DOLPHIN_GBAPRIV
