#ifndef JASSYSTEMHEAP_H
#define JASSYSTEMHEAP_H

#include "dolphin/types.h"

class JKRSolidHeap;

extern JKRSolidHeap* JASDram;

namespace JASystem {
    namespace Kernel {
        class TSolidHeap;

        void sysDramSetup(JKRSolidHeap*);
        void* allocFromSysDram(u32);
        void sysAramSetup(u32);
        void* allocFromSysAramFull(u32*);

        extern TSolidHeap audioAramHeap;
        extern u32 audioDramSize;
        extern u32 audioAramSize;
        extern int audioAramTop;
        extern int CARD_SECURITY_BUFFER;
    }
}

#endif /* JASSYSTEMHEAP_H */
