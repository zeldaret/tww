#ifndef FUNCTIONVALUE_INLINES_H
#define FUNCTIONVALUE_INLINES_H

// Note: These weak functions need to go in a separate file for functionvalue's .sdata2 section to match properly.
// The actual name of this file and its exact contents are unknown, this is a guess.

#include "global.h"
#include "math.h"

namespace JStudio {
    
namespace functionvalue {
    
/* 80272F64-80272F68       .text extrapolateParameter_raw__Q27JStudio13functionvalueFdd */
inline f64 extrapolateParameter_raw(f64 a1, f64 a2) {
    return a1;
}

/* 80272F68-80272FA4       .text extrapolateParameter_repeat__Q27JStudio13functionvalueFdd */
inline f64 extrapolateParameter_repeat(f64 a1, f64 a2) {
    f64 t = fmod(a1, a2);

    if (t < 0.0)
        t += a2;

    return t;
}

f64 extrapolateParameter_turn(f64, f64);

/* 80272FA4-80272FD0       .text extrapolateParameter_clamp__Q27JStudio13functionvalueFdd */
inline f64 extrapolateParameter_clamp(f64 value, f64 max) {
    if (value <= 0.0)
        return 0.0;

    if (max <= value)
        value = max;

    return value;
}

};  // namespace functionvalue

}  // namespace JStudio

#endif /* FUNCTIONVALUE_INLINES_H */
