#ifndef JASINSTRAND_H
#define JASINSTRAND_H

#include "JSystem/JAudio/JASInstEffect.h"

namespace JASystem {
    class TInstRand : public TInstEffect {
    public:
        TInstRand() {
            field_0x8 = 1.0f;
            field_0xc = 0.0f;
        }
        virtual f32 getY(int, int) const;

        /* 0x08 */ f32 field_0x8;
        /* 0x0C */ f32 field_0xc;
    };
}

#endif /* JASINSTRAND_H */
