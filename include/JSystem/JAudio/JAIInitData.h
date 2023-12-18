#ifndef JAIINITDATA_H
#define JAIINITDATA_H

#include "dolphin/types.h"

namespace JAInter {
    namespace InitData {
        BOOL checkInitDataFile();
        void checkInitDataOnMemory();

        extern u32* aafPointer;
    };
}

#endif /* JAIINITDATA_H */
