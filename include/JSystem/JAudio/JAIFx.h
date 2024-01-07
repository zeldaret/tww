#ifndef JAIFX_H
#define JAIFX_H

#include "dolphin/types.h"

namespace JASystem {
    namespace DSPInterface {
        struct FxlineConfig_;
    }
}

namespace JAInter {
    namespace Fx {
        struct initOnCodeFxScene_s {
            u32 field_0x0;
            u32 field_0x4;
            u32 field_0x8;
            u32 field_0xc;
            u32 field_0x10;
            u32 field_0x14[1];
        };

        void init();
        void setSceneMax(u8 param_1);
        void setBufferMax(u32 param_1, u32 param_2, u32 param_3, u32 param_4);
        void setTablePointer(void** param_1);
        void setBufferPointer(u8 param_1, short* param_2);
        void setScenePointer(u8 param_1, void* param_2);
        u8 getSceneMax();
        u32 getBufferSizeMax(u8 param_1);
        s16* getBufferPointer(u8 param_1);
        JASystem::DSPInterface::FxlineConfig_** getFxconfigTable();

        extern initOnCodeFxScene_s* initOnCodeFxScene;
        extern u8 mSceneMax;
        extern u32* mBufferSizeMax;
        extern s16** mBufferPointer;
        extern void** mFxconfigTable;
    }
}

#endif /* JAIFX_H */
