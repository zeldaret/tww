#ifndef MSL_MATH_H_
#define MSL_MATH_H_

#include "MSL_C/MSL_Common/Src/float.h"

#define NAN (*(float*)__float_nan)
#define HUGE_VALF (*(float*)__float_huge)

#define M_PI 3.14159265358979323846f

#define DEG_TO_RAD(degrees) (degrees * (M_PI / 180.0f))

#ifdef __cplusplus
extern "C" {
#endif

int abs(int);
double acos(double);
float acosf(float);
double asin(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double copysign(double, double);
double cos(double);
float cosf(float);
double exp(double);

extern float __fabsf(float);
inline double fabs(double f) {
    return __fabs(f);
}
inline double fabsf2(float f) {
    return __fabsf(f);
}
inline float fabsf(float f) {
    return fabsf2(f);
}

double floor(double);
double fmod(double, double);
inline float fmodf(float f1, float f2) {
    return fmod(f1, f2);
}

double frexp(double, int*);
double ldexp(double, int);
double modf(double, double*);
double pow(double, double);
double sin(double);
float sinf(float);
double tan(double);
float tanf(float);

inline double sqrt_step(double tmpd, float mag) {
    return tmpd * 0.5 * (3.0 - mag * (tmpd * tmpd));
}

extern inline float sqrtf(float x) {
    const double _half = .5;
    const double _three = 3.0;
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);                   // returns an approximation to
        guess = _half * guess * (_three - guess * guess * x);  // now have 12 sig bits
        guess = _half * guess * (_three - guess * guess * x);  // now have 24 sig bits
        guess = _half * guess * (_three - guess * guess * x);  // now have 32 sig bits
        y = (float)(x * guess);
        return y;
    }
    return x;
}

extern inline double sqrt(double x) {
    if(x > 0.0)
    {
        double guess = __frsqrte(x);                   /* returns an approximation to    */
        guess = .5*guess*(3.0 - guess*guess*x);      /* now have 8 sig bits            */
        guess = .5*guess*(3.0 - guess*guess*x);      /* now have 16 sig bits            */
        guess = .5*guess*(3.0 - guess*guess*x);      /* now have 32 sig bits            */
        guess = .5*guess*(3.0 - guess*guess*x);      /* now have > 53 sig bits        */
        return x*guess ;
    }
    else if ( x == 0 )
        return 0;
    else if ( x )
        return NAN;

    return HUGE_VALF;
}

inline float atan2f(float y, float x) {
    return (float)atan2(y, x);
}

// these are duplicated due to sinf/cosf having a symbol, but
// still being used as inlines elsewhere
inline float i_sinf(float x) {
    return sin(x);
}

inline float i_cosf(float x) {
    return cos(x);
}

#ifdef __cplusplus
};
#endif

#endif
