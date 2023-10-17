#ifndef JASTRACKINTERRUPT_H
#define JASTRACKINTERRUPT_H

#include "dolphin/types.h"

namespace JASystem {
    class TIntrMgr {
    public:
        void init();
        void request(u32);
        void setIntr(u32, void*);
        void resetInter(u32);
        void* checkIntr();
        void timerProcess();

        /* 0x00 */ u8 field_0x0;
        /* 0x01 */ u8 field_0x1;
        /* 0x02 */ u8 field_0x2;
        /* 0x03 */ u8 field_0x3;
        /* 0x04 */ u32 field_0x4;
        /* 0x08 */ u32 field_0x8;
        /* 0x0C */ void* field_0xc[8];
    };
}

#endif /* JASTRACKINTERRUPT_H */
