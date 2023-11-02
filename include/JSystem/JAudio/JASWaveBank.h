#ifndef JASWAVEBANK_H
#define JASWAVEBANK_H

#include "dolphin/types.h"

class JKRHeap;

namespace JASystem {
    class TWaveArc;

    struct TWaveInfo {
        /* 0x00 */ u8 field_0x0;
        /* 0x01 */ u8 field_0x1;
        /* 0x02 */ u8 field_0x2;
        /* 0x04 */ f32 field_0x4;
        /* 0x08 */ int field_0x8;
        /* 0x0C */ int field_0xc;
        /* 0x10 */ int field_0x10;
        /* 0x14 */ int field_0x14;
        /* 0x18 */ int field_0x18;
        /* 0x1C */ int field_0x1c;
        /* 0x20 */ s16 field_0x20;
        /* 0x22 */ s16 field_0x22;
        /* 0x24 */ void* field_0x24;
        /* 0x28 */ int field_0x28;
    };

    class TWaveHandle {
    public:
        virtual ~TWaveHandle() {}
        virtual const TWaveInfo* getWaveInfo() const = 0;
        virtual const void* getWavePtr() const = 0;
    };

    class TWaveBank {
    public:
        TWaveBank() {}
        virtual ~TWaveBank() {}
        virtual TWaveHandle* getWaveHandle(u32) const = 0;
        virtual TWaveArc* getWaveArc(int) = 0;
        static JKRHeap* getCurrentHeap();

        static JKRHeap* sCurrentHeap;
    };
}

#endif /* JASWAVEBANK_H */
