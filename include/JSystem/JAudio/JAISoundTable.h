#ifndef JAISOUNDTABLE_H
#define JAISOUNDTABLE_H

#include "dolphin/types.h"

struct SoundInfo {
    /* 0x00 */ u32 mFlag;
    /* 0x04 */ u8 mPriority;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u16 mOffsetNo;
    /* 0x08 */ u32 mPitch;
    /* 0x0C */ union Volume {
        u32 typeView;
        u8 byteView[4];
    } mVolume;
};

namespace JAInter {
    namespace SoundTable {
        void init(u8*, u32);
        SoundInfo* getInfoPointer(u32);
        u8 getInfoFormat(u32);
        u8 getCategotyMax();

        extern u8 mVersion;
        extern u8 mCategotyMax;
        extern u16* mSoundMax;
        extern u32 mDatasize;
        extern SoundInfo** mPointerCategory;
        extern u8* mAddress;
    }
}

#endif /* JAISOUNDTABLE_H */
