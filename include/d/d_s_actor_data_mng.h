#ifndef D_S_ACTOR_DATA_MNG
#define D_S_ACTOR_DATA_MNG

#include "SSystem/SComponent/c_data_tbl.h"
#include "global.h"

class dADM_CharTbl : public cDT {
public:
    u32 mIndex_ARG;
    u32 mIndex_N_ITEM[16];
    u32 mIndex_percent;
    u32 mIndex_ITEM[8];

    dADM_CharTbl();
    ~dADM_CharTbl();
    void SetData(u32, u32, u32, u32, u32, u32, u32);
    void SetUpIndex();
    int GetNameIndex2(const char*, int) const;

    s32 GetNITEM0()  { return mIndex_N_ITEM[0]; }
    s32 GetNITEM1()  { return mIndex_N_ITEM[1]; }
    s32 GetNITEM2()  { return mIndex_N_ITEM[2]; }
    s32 GetNITEM3()  { return mIndex_N_ITEM[3]; }
    s32 GetNITEM4()  { return mIndex_N_ITEM[4]; }
    s32 GetNITEM5()  { return mIndex_N_ITEM[5]; }
    s32 GetNITEM6()  { return mIndex_N_ITEM[6]; }
    s32 GetNITEM7()  { return mIndex_N_ITEM[7]; }
    s32 GetNITEM8()  { return mIndex_N_ITEM[8]; }
    s32 GetNITEM9()  { return mIndex_N_ITEM[9]; }
    s32 GetNITEM10() { return mIndex_N_ITEM[10]; }
    s32 GetNITEM11() { return mIndex_N_ITEM[11]; }
    s32 GetNITEM12() { return mIndex_N_ITEM[12]; }
    s32 GetNITEM13() { return mIndex_N_ITEM[13]; }
    s32 GetNITEM14() { return mIndex_N_ITEM[14]; }
    s32 GetNITEM15() { return mIndex_N_ITEM[15]; }
    s32 GetPercent() { return mIndex_percent; }
    s32 GetITEM0() { return mIndex_ITEM[0]; }
    s32 GetITEM1() { return mIndex_ITEM[1]; }
    s32 GetITEM2() { return mIndex_ITEM[2]; }
    s32 GetITEM3() { return mIndex_ITEM[3]; }
    s32 GetITEM4() { return mIndex_ITEM[4]; }
    s32 GetITEM5() { return mIndex_ITEM[5]; }
    s32 GetITEM6() { return mIndex_ITEM[6]; }
    s32 GetITEM7() { return mIndex_ITEM[7]; }
};

STATIC_ASSERT(sizeof(dADM_CharTbl) == 0x90);

class dADM {
public:
    /* 0x00 */ int mBlockCount;
    /* 0x04 */ void* mpData;
    /* 0x08 */ dADM_CharTbl mCharTbl;

public:
    dADM();
    virtual ~dADM();
    bool FindTag(u32, u32*, u32*);
    void SetData(void*);
};

#endif
