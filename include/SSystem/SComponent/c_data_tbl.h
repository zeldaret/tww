#ifndef C_DATA_TBL
#define C_DATA_TBL

#include "dolphin/types.h"

struct cDT_NamePTbl {
    cDT_NamePTbl();
    virtual ~cDT_NamePTbl();
    int GetIndex(const char *pName, int start) const;
    void Set(u32 count, char** pNames);

    u32 mCount;
    char ** mpNames;
};

struct cDT_DataSrc {
    u32 mRowNum;
    u32 mColNum;
    u8 *mpData;

    cDT_DataSrc();
    virtual ~cDT_DataSrc();
    u8 GetInf(int row, int col) const;
    void Set(u32 rowNum, u32 colNum, u8* pData);
};

struct cDT_Format : public cDT_NamePTbl {
    cDT_Format();
    ~cDT_Format();
};

struct cDT_Name : public cDT_NamePTbl {
    cDT_Name();
    ~cDT_Name();
};

struct cDT {
public:
    cDT();
    ~cDT();

    u8 GetInf(int row, int col) const;
    void Set(u32 fmtNum, char **pFmt, u32 nameNum, char **pName, u8* pData);

private:
    cDT_Format mFmt;
    cDT_Name mName;
    cDT_DataSrc mSrc;
};

#endif /* C_DATA_TBL */
