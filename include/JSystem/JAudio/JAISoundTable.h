#ifndef JAISOUNDTABLE_H
#define JAISOUNDTABLE_H

#include "dolphin/types.h"

namespace JAInter {
    namespace SoundTable {
        void init(u8*, u32);
        u8* getInfoPointer(u32);
        u8 getInfoFormat(u32);
        u8 getCategotyMax();

        extern u8 mVersion;
        extern u8 mCategotyMax;
        extern u16* mSoundMax;
        extern u32 mDatasize;
        extern u8** mPointerCategory;
        extern u8* mAddress;
    }
}

#endif /* JAISOUNDTABLE_H */
