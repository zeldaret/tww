#ifndef M_DO_M_DO_MEMCARDRWMNG_H
#define M_DO_M_DO_MEMCARDRWMNG_H

#include "d/d_save.h"
#include "dolphin/types.h"

typedef struct CARDFileInfo CARDFileInfo;

struct mDoMemCdRWm_HeaderData
{
    /* 0x0000 */ u8 banner[0x0e00];
    /* 0x0e00 */ u8 icon[0x0200];
    /* 0x1000 */ u8 field_0x1000[0x0c00];
    /* 0x1c00 */ char comment[32];
    /* 0x1c20 */ char info[32];
};

struct card_pictdata
{
    u8 data[0x1ffe];
    u16 csum;
};

struct card_gamedata
{
    u8 data[dSv_save_c::PACKED_STRUCT_SIZE];
    u64 csum;
};

struct card_savedata
{
    u32 saveCount;
    u32 dataVersion;
    card_gamedata gamedata[3];
    u32 field_0x1658[0x269];
    u32 csum;
};

s32 mDoMemCdRWm_Store(CARDFileInfo*, void*, u32);
s32 mDoMemCdRWm_Restore(CARDFileInfo*, void*, u32);
#if VERSION == VERSION_PAL
s32 mDoMemCdRWm_Restore2(CARDFileInfo*);
#endif
void mDoMemCdRWm_BuildHeader(mDoMemCdRWm_HeaderData*);
void mDoMemCdRWm_SetCardStat(CARDFileInfo*);
BOOL mDoMemCdRWm_CheckCardStat(CARDFileInfo*);
u32 mDoMemCdRWm_CalcCheckSum(void*, u32);
u16 mDoMemCdRWm_CalcCheckSumPictData(void*, u32);
BOOL mDoMemCdRWm_TestCheckSumPictData(void*);
void mDoMemCdRWm_SetCheckSumPictData(u8*);
u64 mDoMemCdRWm_CalcCheckSumGameData(void*, u32);
BOOL mDoMemCdRWm_TestCheckSumGameData(void*);
void mDoMemCdRWm_SetCheckSumGameData(u8*, u8);

#endif /* M_DO_M_DO_MEMCARDRWMNG_H */
