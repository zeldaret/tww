#ifndef JASINSTEFFECT_H
#define JASINSTEFFECT_H

#include "dolphin/types.h"

namespace JASystem {
    class TInstEffect {
    public:
        TInstEffect() { mTarget = 0; }
        virtual f32 getY(int, int) const = 0;
        void setTarget(int);

        /* 0x04 */ u8 mTarget;
    };
}

#endif /* JASINSTEFFECT_H */
