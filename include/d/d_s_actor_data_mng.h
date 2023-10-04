#ifndef D_S_ACTOR_DATA_MNG
#define D_S_ACTOR_DATA_MNG

#include "SSystem/SComponent/c_data_tbl.h"

class dADM_CharTbl : public cDT {
public:
    u32 mIndex_ARG;
    u32 mIndex_N_ITEM[16];
    u32 mIndex_percent;
    u32 mIndex_ITEM[8];

    dADM_CharTbl();
    void SetData(u32, u32, u32, u32, u32, u32, u32);
    void SetUpIndex();
    int GetNameIndex2(const char*, int) const;
};

class dADM {
public:
    /* 0x00 */ s32 mBlockCount;
    /* 0x04 */ void *mpData;
    /* 0x08 */ dADM_CharTbl mCharTbl;

    dADM();
    virtual ~dADM();
    bool FindTag(u32, u32*, u32*);
    void SetData(void*);
};

#endif
