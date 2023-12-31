//
// Generated by dtk
// Translation Unit: random.cpp
//

#include "JSystem/JMath/random.h"
#include "dolphin/types.h"

/* 80301350-80301358       .text __ct__Q25JMath13TRandom_fast_FUl */
JMath::TRandom_fast_::TRandom_fast_(u32 value) {
    this->value = value;
}

/* 80301358-8030142C       .text setSeed__Q25JMath15TRandom_enough_FUl */
void JMath::TRandom_enough_::setSeed(u32 value) {
    field_0x4 = 0;
    field_0x0 = value + 1;
    if (field_0x0 == 0) {
        field_0x0 += 1;
    }
    u32 i;
    for (i = 8; i != 0; i--) {
        next_();
    }
    for (i = 32; i != 0;) {
        i--;
        next_();
        field_0x8[i] = field_0x0;
    }
}

/* 8030142C-803014CC       .text get__Q25JMath15TRandom_enough_Fv */
f32 JMath::TRandom_enough_::get() {
    next_();
    u8 idx = (field_0x4 >> 24 & ~3) / 4;
    field_0x4 = field_0x8[idx];
    field_0x8[idx] = field_0x0;
    f32 var3 = field_0x4 * 4.656613E-10f;
    return var3 < 0.9999999f ? var3 : 0.9999999f;
}
