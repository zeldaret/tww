#ifndef JAIDUMMYOBJECT_H
#define JAIDUMMYOBJECT_H

#include "dolphin/types.h"

class JAISound;

namespace JAInter {
    struct DummyVec {
        DummyVec* field_0x0;
        DummyVec* field_0x4;
        JAISound* field_0x8;
        u32 field_0xc;
        int field_0x10;
        int field_0x14;
        u32 field_0x18;
        bool field_0x1c;
    };

    namespace DummyObjectMgr {
        void init();
        DummyVec* getPointer(u32 param_1, bool param_2);
        void releasePointer(DummyVec* param_1);
        void check();

        extern DummyVec* deadObjectFreePointer;
        extern DummyVec* deadObjectUsedPointer;
        extern DummyVec* deadObjectObject;
    }
}

#endif /* JAIDUMMYOBJECT_H */
