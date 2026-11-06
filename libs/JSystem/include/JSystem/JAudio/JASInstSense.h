#ifndef JASINSTSENSE_H
#define JASINSTSENSE_H

#include "JSystem/JAudio/JASInstEffect.h"

namespace JASystem {
    class TInstSense : public TInstEffect {
    public:
        TInstSense() {
            field_0x8 = 0;
            field_0x9 = 60;
            field_0xc = 1.0f;
            field_0x10 = 1.0f;
        }
        virtual f32 getY(int, int) const;
        void setParams(int, int, f32, f32);

        u8 field_0x8;
        u8 field_0x9;
        f32 field_0xc;
        f32 field_0x10;
    };
}

#endif /* JASINSTSENSE_H */
