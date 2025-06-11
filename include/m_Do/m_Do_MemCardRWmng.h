#ifndef M_DO_M_DO_MEMCARDRWMNG_H
#define M_DO_M_DO_MEMCARDRWMNG_H

#include "d/d_save.h"
#include "dolphin/types.h"

typedef struct CARDFileInfo CARDFileInfo;

struct mDoMemCdRWm_HeaderData
{
    /* 0x0000 */ u8 banner[0x0E00];
    /* 0x0E00 */ u8 icon[0x0200];
    /* 0x1000 */ u8 field_0x1000[0x0C00];
    /* 0x1C00 */ char comment[32];
    /* 0x1C20 */ char info[32];
};  // Size: 0x1C40

struct card_pictdata
{
    /* 0x0000 */ u8 data[0x2000 - sizeof(u16)];
    /* 0x1FFE */ u16 csum;
};  // Size: 0x2000

STATIC_ASSERT(sizeof(card_pictdata) == 0x2000);

struct card_gamedata
{
    /* 0x000 */ u8 data[dSv_save_c::PACKED_STRUCT_SIZE];
    /* 0x768 */ u64 csum;
};  // Size: 0x770

struct card_savedata
{
    /* 0x0000 */ u32 saveCount;
    /* 0x0004 */ u32 dataVersion;
    /* 0x0008 */ card_gamedata gamedata[3];
    /* 0x1658 */ u8 field_0x1658[0x2000 - 3*sizeof(u32) - 3*sizeof(card_gamedata)];
    /* 0x1FFC */ u32 csum;
};  // Size: 0x2000

STATIC_ASSERT(sizeof(card_savedata) == 0x2000);

STATIC_ASSERT(sizeof(card_pictdata) == sizeof(card_savedata));

s32 mDoMemCdRWm_Store(CARDFileInfo* card, void* data, u32 size);
s32 mDoMemCdRWm_Restore(CARDFileInfo* card, void* dst, u32 size);
#if VERSION == VERSION_PAL
s32 mDoMemCdRWm_Restore2(CARDFileInfo*);
#endif
void mDoMemCdRWm_BuildHeader(mDoMemCdRWm_HeaderData*);
void mDoMemCdRWm_SetCardStat(CARDFileInfo*);
BOOL mDoMemCdRWm_CheckCardStat(CARDFileInfo*);
u32 mDoMemCdRWm_CalcCheckSum(void*, u32 size);
u16 mDoMemCdRWm_CalcCheckSumPictData(void*, u32 size);
BOOL mDoMemCdRWm_TestCheckSumPictData(void*);
void mDoMemCdRWm_SetCheckSumPictData(u8*);
u64 mDoMemCdRWm_CalcCheckSumGameData(void*, u32 size);
BOOL mDoMemCdRWm_TestCheckSumGameData(void*);
void mDoMemCdRWm_SetCheckSumGameData(u8*, u8);

#endif /* M_DO_M_DO_MEMCARDRWMNG_H */
