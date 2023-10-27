#ifndef JASCHALLOCQUEUE_H
#define JASCHALLOCQUEUE_H

#include "JSystem/JSupport/JSUList.h"

namespace JASystem {
    class TChannel;
    namespace TDSPQueue {
        void deQueue();
        void enQueue(JASystem::TChannel*);
        int deleteQueue(JASystem::TChannel*);
        void checkQueue();

    }

    extern JSUList<TChannel> sDspQueueList;
}

#endif /* JASCHALLOCQUEUE_H */
