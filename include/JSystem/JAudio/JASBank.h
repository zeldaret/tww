#ifndef JASBANK_H
#define JASBANK_H

#include "dolphin/types.h"

class JKRHeap;

namespace JASystem {
    namespace TBank {
        JKRHeap* getCurrentHeap();

        extern JKRHeap* sCurrentHeap;
    };
}

#endif /* JASBANK_H */
