#ifndef JASTRACKPORT_H
#define JASTRACKPORT_H

#include "dolphin/types.h"

#define TRACKPORT_MAX (16)

namespace JASystem {
    class TTrackPort {
    public:
        void init();
        u16 readImport(int);
        u16 readExport(int);
        void writeImport(int, u16);
        void writeExport(int, u16);

        u8 checkImport(int i) const { return mImportFlag[i]; }
        u8 checkExport(int i) const { return mExportFlag[i]; }
        u16 get(u32 i) { return mValue[i]; }

        /* 0x00 */ u8 mImportFlag[TRACKPORT_MAX];
        /* 0x10 */ u8 mExportFlag[TRACKPORT_MAX];
        /* 0x20 */ u16 mValue[TRACKPORT_MAX];
    };
}

#endif /* JASTRACKPORT_H */
