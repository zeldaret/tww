#ifndef JAICONST_H
#define JAICONST_H

#include "JSystem/JMath/random.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/mtx/vec.h"

namespace JAInter {
    u8* transInitDataFile(u8*, u32);
    void loadTmpDVDFile(char*, u8**);
    void deleteTmpDVDFile(u8**);
    u32 routeToTrack(u32);

    class Actor {
    public:
        Actor(Vec* p1, Vec* p2, u32 p3, void* p4) {
            field_0x0 = p1;
            field_0x4 = p2;
            field_0x8 = p3;
            field_0xc = p4;
        }

        // order is unclear
        Vec* field_0x0;
        Vec* field_0x4;
        u32 field_0x8;
        void* field_0xc;
    };

    class Camera {
    public:
        Camera(Vec* p1 = NULL, Vec* p2 = NULL, MtxP p3 = NULL) {
            field_0x0 = p1;
            field_0x4 = p2;
            field_0x8 = p3;
        }
        Vec* field_0x0;
        Vec* field_0x4;
        MtxP field_0x8;
    };

    namespace Const {
        extern Camera nullCamera;
        extern Actor nullActor;
        extern Mtx camMtx;
        extern Vec camTrans;
        extern Vec camPreTrans;
        extern Vec dummyZeroVec;
        extern u8 sCInfos_0[];
        extern JMath::TRandom_fast_ random;
    }
}

#endif /* JAICONST_H */
