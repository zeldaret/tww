#ifndef JASHEAPCTRL_H
#define JASHEAPCTRL_H

#include "JSystem/JSupport/JSUList.h"
#include "dolphin/os/OSMutex.h"

namespace JASystem {
    namespace Kernel {
        class TDisposer {
        public:
            virtual void onDispose() {}
        };

        class THeap {
        public:
            enum Type {
                Type0,
                Type1,
            };

            THeap(TDisposer*);
            ~THeap() {}
            void initRootHeap(void*, u32, Type);
            bool alloc(THeap*, u32);
            bool free();
            void insertChild(THeap* param_1, THeap* param_2, void* param_3, u32 param_4, bool param_5);
            JASystem::Kernel::THeap* getTailHeap();
            u32 getTailOffset();
            u32 getCurOffset();

            bool isAllocated() { return mBase; }

            /* 0x00 */ JSUTree<THeap> mTree;
            /* 0x1C */ OSMutex mMutex;
            /* 0x34 */ TDisposer* mDisposer;
            /* 0x38 */ Type mType;
            /* 0x3C */ u8* mBase;
            /* 0x40 */ u32 mSize;
            /* 0x44 */ THeap* field_0x44;
        };

        class TSolidHeap {
        public:
            TSolidHeap();
            ~TSolidHeap() {}
            void* alloc(s32 param_1);
            void freeAll();
            void init(u8* param_1, s32 param_2);
            int getRemain();

            /* 0x00 */ u32 field_0x0;
            /* 0x04 */ int field_0x4;
            /* 0x08 */ int field_0x8;
            /* 0x0C */ int field_0xc;
            /* 0x10 */ int field_0x10;
        };
    }
}

#endif /* JASHEAPCTRL_H */
