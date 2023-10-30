#ifndef JASWSPARSER_H
#define JASWSPARSER_H

#include "dolphin/types.h"

namespace JASystem {
    class TBasicWaveBank;
    class TSimpleWaveBank;
    namespace WSParser {
        struct TCtrl;
        struct TCtrlGroup;
        struct TCtrlScene;
        struct TCtrlWave;
        struct TWave;
        struct TWaveArchive;
        struct TWaveArchiveBank;

        u32 getGroupCount(void*);
        TBasicWaveBank* createBasicWaveBank(void*);
        TSimpleWaveBank* createSimpleWaveBank(void*);
    }
}

#endif /* JASWSPARSER_H */
