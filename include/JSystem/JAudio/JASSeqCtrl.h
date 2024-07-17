#ifndef JASSEQCTRL_H
#define JASSEQCTRL_H

#include "dolphin/types.h"

namespace JASystem {
    class TTrack;

    class TSeqCtrl {
    public:
        void call(u32) {}
        void clrIntr() {}
        void getAddr(u32) {}
        void getBase() {}
        u8 getByte(u32 offset) const { return field_0x0[offset]; }
        void getLoopCount() const {}
        void getWait() const {}
        void isIntr() const {}
        void jump(u32) {}
        void loopStart(u32) {}
        u8 readByte() { return *field_0x4++; }
        void ret() {}
        void wait(s32) {}

        void init();
        void start(void*, u32);
        int loopEnd();
        bool waitCountDown();
        bool callIntr(void*);
        bool retIntr();
        u16 get16(u32) const;
        u32 get24(u32) const;
        u32 get32(u32) const;
        u32 read16();
        u32 read24();

        /* 0x00 */ u8* field_0x0;
        /* 0x04 */ u8* field_0x4;
        /* 0x08 */ int field_0x8;
        /* 0x0C */ u32 field_0xc;
        /* 0x10 */ u8* field_0x10[8];
        /* 0x30 */ u16 field_0x30[8];
        /* 0x40 */ int field_0x40;
        /* 0x44 */ u8* field_0x44;
    };
}

#endif /* JASSEQCTRL_H */
