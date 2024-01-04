#ifndef JFILEHEADER_H
#define JFILEHEADER_H

// Note: The name of this header is fake.

#include "global.h"

struct JSystemBlockHeader { // actual struct name unknown
    /* 0x0 */ u32 mType;
    /* 0x4 */ u32 mNextOffset;

    const JSystemBlockHeader* getNext() const { // fake inline
        return reinterpret_cast<const JSystemBlockHeader*>(reinterpret_cast<const u8*>(this) + mNextOffset);
    }
};  // Size = 0x8

struct JSystemFileHeader { // actual struct name unknown
    /* 0x00 */ u32 mMagic;
    /* 0x04 */ u32 mType;
    /* 0x08 */ u32 mFileSize;
    /* 0x0C */ u32 mBlockNum;
    /* 0x10 */ u8 _10[0x20 - 0x10];
    /* 0x20 */ JSystemBlockHeader mFirstBlock;
};

#endif /* JFILEHEADER_H */
