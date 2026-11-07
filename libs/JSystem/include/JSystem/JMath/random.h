#ifndef RANDOM_H
#define RANDOM_H

#include "dolphin/types.h"
#include <limits>

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

template <class RandomT>
class TRandom_ : public RandomT {
public:
    TRandom_(u32 value) : RandomT(value) {}

    u8 get_uint8(u8 param_0) {
        return this->get_ufloat_1() * param_0;
    }

    u32 get_uint32(u32 param_0) {
        return this->get_ufloat_1() * param_0;
    }

    f32 get_ufloat(f32 param_0) {
        return this->get_ufloat_1() * param_0;
    }

    f32 get_float(f32 param_0) {
        return this->get_ufloat(param_0) - ((param_0 / 2.0f) - std::numeric_limits<f32>::epsilon());
    }
};

}  // namespace JMath

#endif /* RANDOM_H */
