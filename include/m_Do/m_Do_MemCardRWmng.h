#ifndef M_DO_M_DO_MEMCARDRWMNG_H
#define M_DO_M_DO_MEMCARDRWMNG_H

#include "dolphin/types.h"

typedef struct CARDFileInfo CARDFileInfo;
struct mDoMemCdRWm_HeaderData;

s32 mDoMemCdRWm_Store(CARDFileInfo*, void*, u32);
s32 mDoMemCdRWm_Restore(CARDFileInfo*, void*, u32);
void mDoMemCdRWm_BuildHeader(mDoMemCdRWm_HeaderData*);
void mDoMemCdRWm_SetCardStat(CARDFileInfo*);
void mDoMemCdRWm_CheckCardStat(CARDFileInfo*);
void mDoMemCdRWm_CalcCheckSum(void*, u32);
void mDoMemCdRWm_CalcCheckSumPictData(void*, u32);
void mDoMemCdRWm_TestCheckSumPictData(void*);
void mDoMemCdRWm_SetCheckSumPictData(u8*);
void mDoMemCdRWm_CalcCheckSumGameData(void*, u32);
void mDoMemCdRWm_TestCheckSumGameData(void*);
void mDoMemCdRWm_SetCheckSumGameData(u8*, u8);

#endif /* M_DO_M_DO_MEMCARDRWMNG_H */
