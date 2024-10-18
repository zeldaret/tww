#ifndef MSL_MATH_H_
#define MSL_MATH_H_

#include "float.h"

#define NAN (*(float*) __float_nan)
#define HUGE_VALF (*(float*) __float_huge)

#define M_PI 3.14159265358979323846f
#define M_SQRT3 1.73205f

#define DEG_TO_RAD(degrees) (degrees * (M_PI / 180.0f))
#define RAD_TO_DEG(radians) (radians * (180.0f / M_PI + 0.000005f)) // the 0.000005f is probably a fakematch

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

extern double __fabs(double);
extern float __fabsf(float);
inline double fabs(double f) {
    return __fabs(f);
}

double __frsqrte(double);
float __fres(float);

double floor(double);
double fmod(double, double);

double frexp(double, int*);
double ldexp(double, int);
double modf(double, double*);
double pow(double, double);
double sin(double);
float sinf(float);
double tan(double);
float tanf(float);

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

#ifdef __cplusplus
};


namespace std {
inline float fabsf(float f) { return fabs(f); }
inline float abs(float f) { return fabsf(f); }
inline float fmodf(float x, float y) { return fmod(x, y); }
inline float atan2f(float y, float x) { return (float)atan2(y, x); }
inline float sinf(float x) { return sin(x); }
inline float cosf(float x) { return cos(x); }
inline float tanf(float x) { return tan(x); }

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
}; // namespace std
#endif

#endif
