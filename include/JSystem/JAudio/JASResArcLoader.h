#ifndef JASRESARCLOADER_H
#define JASRESARCLOADER_H

#include "dolphin/types.h"

class JKRArchive;

namespace JASystem {
    namespace ResArcLoader {
        struct TLoadResInfo {
            TLoadResInfo(JKRArchive* archive, u16 id, void* buffer, u32 size) {
                mArchive = archive;
                mId = id;
                mBuffer = buffer;
                mSize = size;
                mCallback = NULL;
                mCallbackParam = 0;
                mMessageQueue = NULL;
            }

            /* 0x00 */ JKRArchive* mArchive;
            /* 0x04 */ u16 mId;
            /* 0x08 */ void* mBuffer;
            /* 0x0C */ u32 mSize;
            /* 0x10 */ void (*mCallback)(u32, u32);
            /* 0x14 */ u32 mCallbackParam;
            /* 0x18 */ OSMessageQueue* mMessageQueue;
        };

        u32 getResSize(JKRArchive*, u16);
        s32 loadResourceCallback(void*);
        u32 loadResource(JKRArchive*, u16, u8*, u32);
        void loadResourceAsync(JKRArchive*, u16, u8*, u32, void (*)(u32, u32), u32);
    }
}

#endif /* JASRESARCLOADER_H */
