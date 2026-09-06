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
            mWaveBank = NULL;
        }
        virtual ~TBank() {}
        virtual TInst* getInst(int) const = 0;
        virtual u32 getType() const = 0;

        void assignWaveBank(const TWaveBank* waveBank) { mWaveBank = waveBank; }
        const TWaveBank* getWaveBank() const { return mWaveBank; }

        static JKRHeap* getCurrentHeap();
        static JKRHeap* sCurrentHeap;

        /* 0x04 */ const TWaveBank* mWaveBank;
    };
}

#endif /* JASBANK_H */
