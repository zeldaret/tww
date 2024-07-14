#ifndef M_DO_M_DO_MEMCARDRWMNG_H
#define M_DO_M_DO_MEMCARDRWMNG_H

#include "dolphin/types.h"

typedef struct CARDFileInfo CARDFileInfo;
struct mDoMemCdRWm_HeaderData;

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
