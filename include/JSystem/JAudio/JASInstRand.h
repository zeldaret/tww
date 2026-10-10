#ifndef JASINSTRAND_H
#define JASINSTRAND_H

#include "JSystem/JAudio/JASInstEffect.h"

namespace JASystem {
    class TInstRand : public TInstEffect {
    public:
        TInstRand() {
            mBase = 1.0f;
            mWidth = 0.0f;
        }
        virtual f32 getY(int, int) const;

        void setBase(f32 base) { mBase = base; }
        void setWidth(f32 width) { mWidth = width; }

    private:
        /* 0x08 */ f32 mBase;
        /* 0x0C */ f32 mWidth;
    };
}

#endif /* JASINSTRAND_H */
