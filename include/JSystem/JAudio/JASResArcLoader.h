#ifndef JASRESARCLOADER_H
#define JASRESARCLOADER_H

#include "dolphin/types.h"

class JKRArchive;

namespace JASystem {
    namespace ResArcLoader {
        u32 getResSize(JKRArchive*, u16);
        s32 loadResourceCallback(void*);
        u32 loadResource(JKRArchive*, u16, u8*, u32);
        void loadResourceAsync(JKRArchive*, u16, u8*, u32, void (*)(u32, u32), u32);
    }
}

#endif /* JASRESARCLOADER_H */
