#ifndef RANDOM_H
#define RANDOM_H

#include "dolphin/types.h"

namespace JMath {
struct TRandom_fast_ {
    u32 value;

    TRandom_fast_(u32 value);
    u32 get(void) {
        value = (value * 0x19660d) + 0x3c6ef35f;
        return value;
    }

    u32 get_bit32(void) { return this->get(); }
    u16 get_bit16(void) { return this->get() >> 16; }

    // due to the float constant, having this function inlined adds that float to data,
    // making it not match
    float get_ufloat_1(void) {
        union {
            f32 f;
            u32 s;
        } out;
        out.s = (this->get() >> 9) | 0x3f800000;
        return out.f - 1;
    }

    void setSeed(u32 seed) { value = seed; }
};

struct TRandom_enough_ {
    TRandom_enough_() { setSeed(0); }
    void setSeed(u32 value);
    f32 get();

    void next_() {
        field_0x0 = ((u64)field_0x0 * 0x41a7) % 0x7fffffff;
    }

    u32 field_0x0;
    u32 field_0x4;
    u32 field_0x8[32];
};
}  // namespace JMath

#endif /* RANDOM_H */
