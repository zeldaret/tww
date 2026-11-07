#ifndef JASCALC_H
#define JASCALC_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Calc {
        void initSinfT();
        f32 sinfT(f32);
        f32 sinfDolby2(f32);
        void imixcopy(const s16*, const s16*, s16*, s32);
        void bcopyfast(const u32*, u32*, u32);
        void bcopy(const void*, void*, u32);
        void bzerofast(void*, u32);
        void bzero(void*, u32);

        extern f32* JASC_SINTABLE;
        extern f32* JASC_DOL2TABLE;
    }
}

#endif /* JASCALC_H */
