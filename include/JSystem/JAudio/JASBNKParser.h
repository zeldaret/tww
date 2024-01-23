#ifndef JASBNKPARSER_H
#define JASBNKPARSER_H

#include "JSystem/JAudio/JASOscillator.h"

namespace JASystem {
    class TBasicBank;
    namespace BNKParser {
        struct THeader {
            /* 0x000 */ u8 field_0x0[0x24];
            /* 0x024 */ u32 mInstOffsets[0x80];
            /* 0x224 */ u8 field_0x224[0x190];
            /* 0x3B4 */ u32 mPercOffsets[12];
        };
        struct TInst {
            /* 0x00 */ u8 field_0x0[8];
            /* 0x08 */ f32 field_0x8;
            /* 0x0C */ f32 field_0xC;
            /* 0x10 */ u32 mOscOffsets[2];
            /* 0x18 */ u32 mRandOffsets[2];
            /* 0x20 */ u32 mSenseOffsets[2];
            /* 0x28 */ u32 mKeyRegionCount;
            /* 0x2C */ u32 mKeymapOffsets[2];
        };
        struct TKeymap {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ u32 field_0x4;
            /* 0x08 */ u32 mVmapOffsets[1];
        };
        struct TOsc {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ u32 field_0x8;
            /* 0x0C */ u32 field_0xC;
            /* 0x10 */ f32 field_0x10;
            /* 0x14 */ f32 field_0x14;
        };
        struct TPerc {
            /* 0x000 */ u32 mMagic;
            /* 0x004 */ u8 field_0x4[0x84];
            /* 0x088 */ u32 mPmapOffsets[0x80];
            /* 0x288 */ s8 field_0x288[0x80];
            /* 0x308 */ u16 field_0x308[0x80];
        };
        struct TPmap {
            /* 0x00 */ f32 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ u32 mRandOffsets[2];
            /* 0x10 */ u32 mVeloRegionCount;
            /* 0x14 */ u32 mVeloRegionOffsets[1];
        };
        struct TRand {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ f32 field_0x8;
        };
        struct TSense {
            /* 0x00 */ u8 field_0x0;
            /* 0x01 */ u8 field_0x1;
            /* 0x02 */ u8 field_0x2;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ f32 field_0x8;
        };
        struct TVmap {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ u32 field_0x4;
            /* 0x08 */ f32 field_0x8;
            /* 0x0C */ f32 field_0xC;
        };

        TBasicBank* createBasicBank(void*);
        TOscillator::Osc_* findOscPtr(JASystem::TBasicBank*, JASystem::BNKParser::THeader*, JASystem::BNKParser::TOsc*);
        s16* getOscTableEndPtr(s16*);

        extern u32 sUsedHeapSize;
    };
}

#endif /* JASBNKPARSER_H */
