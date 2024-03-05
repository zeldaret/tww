#ifndef JASWSPARSER_H
#define JASWSPARSER_H

#include "dolphin/types.h"

namespace JASystem {
    class TBasicWaveBank;
    class TSimpleWaveBank;
    namespace WSParser {
        struct TCtrl {
            /* 0x00 */ u32 mMagic;
            /* 0x04 */ u32 mWaveCount;
            /* 0x08 */ u32 mCtrlWaveOffsets[1];
        };
        struct TCtrlGroup {
            /* 0x00 */ u32 mMagic;
            /* 0x04 */ u8 field_0x4[0x08 - 0x04];
            /* 0x08 */ u32 mCtrlGroupCount;
            /* 0x0C */ u32 mCtrlSceneOffsets[1];
        };
        struct TCtrlScene {
            /* 0x00 */ u32 mMagic;
            /* 0x04 */ u8 field_0x4[0x0C - 0x04];
            /* 0x0C */ u32 mCtrlOffset;
        };
        struct TCtrlWave {
            /* 0x00 */ u32 field_0x0;
        };
        struct THeader {
            /* 0x00 */ u8 field_0x0[0x10];
            /* 0x10 */ u32 mArchiveBankOffset;
            /* 0x14 */ u32 mCtrlGroupOffset;
        };
        struct TWave {
            /* 0x00 */ u8 field_0x0;
            /* 0x01 */ u8 field_0x1;
            /* 0x02 */ u8 field_0x2;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ u32 mOffset;
            /* 0x0C */ u32 field_0xc;
            /* 0x10 */ u32 field_0x10;
            /* 0x14 */ u32 field_0x14;
            /* 0x18 */ u32 field_0x18;
            /* 0x1C */ u32 field_0x1c;
            /* 0x20 */ s16 field_0x20;
            /* 0x22 */ s16 field_0x22;
            /* 0x24 */ u8 field_0x24[0x28 - 0x24];
            /* 0x28 */ int field_0x28;
        };
        struct TWaveArchive {
            /* 0x00 */ char mFileName[0x74];
            /* 0x74 */ u32 mWaveOffsets[1];
        };
        struct TWaveArchiveBank {
            /* 0x00 */ u32 mMagic;
            /* 0x04 */ u8 field_0x4[0x08 - 0x04];
            /* 0x08 */ u32 mArchiveOffsets[1];
        };

        u32 getGroupCount(void*);
        TBasicWaveBank* createBasicWaveBank(void*);
        TSimpleWaveBank* createSimpleWaveBank(void*);

        extern u32 sUsedHeapSize;
    }
}

#endif /* JASWSPARSER_H */
