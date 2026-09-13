#ifndef JASBNKPARSER_H
#define JASBNKPARSER_H

#include "JSystem/JAudio/JASOscillator.h"
#include "JSystem/JSupport/JSupport.h"

namespace JASystem {
    class TBasicBank;
    namespace BNKParser {
        template <typename T>
        class TOffset {
        public:
            T *ptr(const void *p) { return JSUConvertOffsetToPtr<T>(p, mOffset); }
        private:
            u32 mOffset;
        };

        struct TOsc {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ TOffset<s16> field_0x8;
            /* 0x0C */ TOffset<s16> field_0xC;
            /* 0x10 */ f32 field_0x10;
            /* 0x14 */ f32 field_0x14;
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
        struct TKeymap {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ u32 mVeloRegionCount;
            /* 0x08 */ TOffset<TVmap> mVmapOffsets[1];
        };
        struct TInst {
            /* 0x00 */ u8 field_0x0[8];
            /* 0x08 */ f32 field_0x8;
            /* 0x0C */ f32 field_0xC;
            /* 0x10 */ TOffset<TOsc> mOscOffsets[2];
            /* 0x18 */ TOffset<TRand> mRandOffsets[2];
            /* 0x20 */ TOffset<TSense> mSenseOffsets[2];
            /* 0x28 */ u32 mKeyRegionCount;
            /* 0x2C */ TOffset<TKeymap> mKeymapOffsets[2];
        };
        struct TPmap {
            /* 0x00 */ f32 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ TOffset<TRand> mRandOffsets[2];
            /* 0x10 */ u32 mVeloRegionCount;
            /* 0x14 */ TOffset<TVmap> mVeloRegionOffsets[1];
        };
        struct TPerc {
            /* 0x000 */ u32 mMagic;
            /* 0x004 */ u8 field_0x4[0x84];
            /* 0x088 */ TOffset<TPmap> mPmapOffsets[0x80];
            /* 0x288 */ s8 field_0x288[0x80];
            /* 0x308 */ u16 field_0x308[0x80];
        };
        struct THeader {
            /* 0x000 */ u8 field_0x0[0x24];
            /* 0x024 */ TOffset<TInst> mInstOffsets[0x80];
            /* 0x224 */ u8 field_0x224[0x190];
            /* 0x3B4 */ TOffset<TPerc> mPercOffsets[12];
        };

        TBasicBank* createBasicBank(void*);
        TOscillator::Osc_* findOscPtr(JASystem::TBasicBank*, JASystem::BNKParser::THeader*, JASystem::BNKParser::TOsc*);
        s16* getOscTableEndPtr(s16*);

        extern u32 sUsedHeapSize;
    };
}

#endif /* JASBNKPARSER_H */
