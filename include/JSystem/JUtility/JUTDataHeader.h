#ifndef JFILEHEADER_H
#define JFILEHEADER_H

// Note: The name of this header is fake.

#include "global.h"

struct JUTDataBlockHeader {
    /* 0x0 */ u32 mType;
    /* 0x4 */ u32 mSize;

    const JUTDataBlockHeader* getNext() const { // fake inline
        return reinterpret_cast<const JUTDataBlockHeader*>(reinterpret_cast<const u8*>(this) + mSize);
    }
};

struct JUTDataFileHeader { // actual struct name unknown
    /* 0x00 */ u32 mMagic;
    /* 0x04 */ u32 mType;
    /* 0x08 */ u32 mFileSize;
    /* 0x0C */ u32 mBlockNum;
    /* 0x10 */ u8 _10[0x1C - 0x10];
    /* 0x1C */ u32 mSeAnmOffset; // Only exists for some BCKs
    /* 0x20 */ JUTDataBlockHeader mFirstBlock;
};

#endif /* JFILEHEADER_H */
