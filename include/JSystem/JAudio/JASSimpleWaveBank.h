#ifndef JASSIMPLEWAVEBANK_H
#define JASSIMPLEWAVEBANK_H

#include "JSystem/JAudio/JASWaveArcLoader.h"
#include "JSystem/JAudio/JASWaveBank.h"
#include "dolphin/types.h"

namespace JASystem {
    class TSimpleWaveBank : public TWaveBank, public TWaveArc {
    public:
        class TWaveHandle : public JASystem::TWaveHandle {
        public:
            TWaveHandle() { mHeap = NULL; }
            ~TWaveHandle();
            const TWaveInfo* getWaveInfo() const { return &mWaveInfo; }
            const void* getWavePtr() const {
                if (mHeap->mBase == NULL) {
                    return NULL;
                }
                return (u8*)mHeap->mBase + mWaveInfo.mWavePtrOffs;
            }

            /* 0x04 */ TWaveInfo mWaveInfo;
            /* 0x30 */ Kernel::THeap* mHeap;
        };

        TSimpleWaveBank();
        ~TSimpleWaveBank();
        void setWaveTableSize(u32);
        TWaveHandle* getWaveHandle(u32) const;
        void setWaveInfo(u32, const JASystem::TWaveInfo&);
        TWaveArc* getWaveArc(int);

        /* 0x7C */ TWaveHandle* mWaveTable;
        /* 0x80 */ u32 mWaveCount;
    };
}

#endif /* JASSIMPLEWAVEBANK_H */
