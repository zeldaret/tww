#ifndef JASTRACKPORT_H
#define JASTRACKPORT_H

#include "dolphin/types.h"

namespace JASystem {
    class TTrackPort {
    public:
        void init();
        u16 readImport(int);
        u16 readExport(int);
        void writeImport(int, u16);
        void writeExport(int, u16);

        /* 0x00 */ u8 field_0x0[16];
        /* 0x10 */ u8 field_0x10[16];
        /* 0x20 */ u16 field_0x20[16];
    };
}

#endif /* JASTRACKPORT_H */
