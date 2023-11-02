#ifndef JASBANK_H
#define JASBANK_H

#include "dolphin/types.h"

class JKRHeap;

namespace JASystem {
    class TInst;
    class TWaveBank;
    class TBank {
    public:
        TBank() {
            field_0x4 = 0;
        }
        virtual ~TBank() {}
        virtual TInst* getInst(int) const = 0;
        virtual u32 getType() const = 0;

        static JKRHeap* getCurrentHeap();

        static JKRHeap* sCurrentHeap;

        /* 0x04 */ TWaveBank* field_0x4;
    };
}

#endif /* JASBANK_H */
