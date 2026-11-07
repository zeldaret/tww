#ifndef JASWAVEBANKMGR_H
#define JASWAVEBANKMGR_H

#include "dolphin/types.h"

namespace JASystem {
    class TWaveArc;
    class TWaveBank;
    namespace Kernel {
        class THeap;
    }
    namespace WaveBankMgr {
        void init(int);
        TWaveBank* getWaveBank(int);
        bool registWaveBank(int, TWaveBank*);
        bool registWaveBankWS(int, void*);
        TWaveArc* getWaveArc(int, int);
        bool loadWave(int, int, Kernel::THeap*);
        bool eraseWave(int, int);

        extern int sTableSize;
        extern TWaveBank** sWaveBank;
    }
}

#endif /* JASWAVEBANKMGR_H */
