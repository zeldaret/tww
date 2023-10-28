#ifndef JASCHGLOBAL_H
#define JASCHGLOBAL_H

#include "dolphin/types.h"

namespace JASystem {
    class TChannel;
    class TChannelMgr;
    class TOscillator;

    namespace TGlobalChannel {
        TChannel* getChannelHandle(u32);
        void init();
        int alloc(TChannelMgr*, u32);
        int release(TChannel*);
        int releaseAll(TChannelMgr*);

        extern TChannelMgr* sChannelMgr;
        extern TChannel* sChannel;
        extern TOscillator* sOscillator;
    }
}

#endif /* JASCHGLOBAL_H */
