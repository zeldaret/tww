#ifndef JASPROBE_H
#define JASPROBE_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Kernel {
        void probeStart(s32, char*);
        void probeFinish(s32);
    }
}

#endif /* JASPROBE_H */
