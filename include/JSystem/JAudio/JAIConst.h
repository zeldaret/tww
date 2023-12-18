#ifndef JAICONST_H
#define JAICONST_H

#include "JSystem/JMath/random.h"
#include "dolphin/mtx/vec.h"

namespace JAInter {
    u8* transInitDataFile(u8*, u32);
    void loadTmpDVDFile(char*, u8**);
    void deleteTmpDVDFile(u8**);
    u32 routeToTrack(u32);

    namespace Const {
        extern Vec dummyZeroVec;
        extern JMath::TRandom_fast_ random;
    }
}

#endif /* JAICONST_H */
