#ifndef JASCALLBACK_H
#define JASCALLBACK_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Kernel {
        void resetCallback();
        int checkCallback(s32 (*)(void*), void*);
        int registerDspCallback(s32 (*)(void*), void*);
        int registerSubFrameCallback(s32 (*)(void*), void*);
        void aiCallback();
        void subframeCallback();

        struct unk_callList {
            /* 0x00 */ s32 (*field_0x0)(void*);
            /* 0x04 */ void* field_0x4;
            /* 0x08 */ u32 field_0x8;
        };

        extern u32 maxCallbacksUser;
        extern unk_callList* callList;
        extern bool callbackInit;
    }
}

#endif /* JASCALLBACK_H */
