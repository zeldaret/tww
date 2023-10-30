#ifndef JASBASICWAVEBANK_H
#define JASBASICWAVEBANK_H

#include "JSystem/JAudio/JASWaveArcLoader.h"
#include "JSystem/JAudio/JASWaveBank.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/os/OSMutex.h"

namespace JASystem {
    class TBasicWaveBank : public TWaveBank {
    public:
        class TWaveHandle : public JASystem::TWaveHandle {
        public:
            ~TWaveHandle() {}
            const JASystem::TWaveInfo* getWaveInfo() const {
                return &field_0x4;
            }
            const void* getWavePtr() const {
                JUT_ASSERT(77, mHeap);
                if (!mHeap->mBase) {
                    return NULL;
                }
                return (u8*)mHeap->mBase + field_0x4.field_0x8;
            }

            /* 0x04 */ JASystem::TWaveInfo field_0x4;
            /* 0x30 */ Kernel::THeap* mHeap;
        };

        class TWaveInfo {
        public:
            TWaveInfo() {
                field_0x0.mHeap = NULL;
                field_0x34 = 0;
                field_0x38 = NULL;
                field_0x3c = NULL;
            }
            ~TWaveInfo();

            /* 0x00 */ TWaveHandle field_0x0;
            /* 0x34 */ u32 field_0x34;
            /* 0x38 */ TWaveInfo* field_0x38;
            /* 0x3C */ TWaveInfo* field_0x3c;
        };

        class TWaveGroup : public TWaveArc {
        public:
            TWaveGroup(TBasicWaveBank*);
            ~TWaveGroup();
            void setWaveCount(u32);
            void setWaveInfo(int, u32, const JASystem::TWaveInfo&);
            void onLoadDone();
            void onEraseDone();
            u32 getWaveID(int) const;

            /* 0x78 */ TBasicWaveBank* mBank;
            /* 0x7C */ TWaveInfo* mCtrlWaveArray;
            /* 0x80 */ u32 mWaveCount;
        };

        TBasicWaveBank();
        ~TBasicWaveBank();
        TWaveGroup* getWaveGroup(int);
        void setGroupCount(u32);
        void setWaveTableSize(u32);
        void incWaveTable(const TWaveGroup*);
        void decWaveTable(const TWaveGroup*);
        JASystem::TWaveHandle* getWaveHandle(u32) const;
        TWaveArc* getWaveArc(int param_1) { return getWaveGroup(param_1); }

        /* 0x04 */ OSMutex mMutex;
        /* 0x1C */ TWaveInfo** mWaveTable;
        /* 0x20 */ int mWaveCount;
        /* 0x24 */ TWaveGroup** mWaveGroupArray;
        /* 0x28 */ u32 mWaveGroupCount;
    };
}

#endif /* JASBASICWAVEBANK_H */
