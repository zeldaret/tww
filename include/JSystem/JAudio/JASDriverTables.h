#ifndef JASDRIVERTABLES_H
#define JASDRIVERTABLES_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Driver {
        extern f32 C5BASE_PITCHTABLE[];
    }
    namespace DSPInterface {
        extern u16 DSPADPCM_FILTER[] __attribute__((aligned(32)));
        extern u16 DSPRES_FILTER[] __attribute__((aligned(32)));
    }
}

#endif /* JASDRIVERTABLES_H */
