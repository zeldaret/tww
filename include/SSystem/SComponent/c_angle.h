#ifndef C_ANGLE_H
#define C_ANGLE_H

#include "SSystem/SComponent/c_xyz.h"

#define RAD2DEG_CONSTANT (180.0f / M_PI) // 57.29577951f
#define DEG2RAD_CONSTANT (M_PI / 180.0f) // 0.017453292f
#define DEG2S_CONSTANT (0x8000 / 180.0f) // 182.04445f
#define S2DEG_CONSTANT (180.0f / 0x8000) // 0.005493164f
#define S2RAD_CONSTANT (M_PI / 0x8000) // 9.58738e-5f / 9.58738e-05f / 0.0000958738f
#define RAD2S_CONSTANT (0x8000 / M_PI) // 10430.378f

#define RAD2DEG(x) ((x) * RAD2DEG_CONSTANT)
#define DEG2RAD(x) ((x) * DEG2RAD_CONSTANT)
#define DEG2S(x) ((s16)((x) * DEG2S_CONSTANT))
#define S2DEG(x) ((x) * S2DEG_CONSTANT)
#define S2RAD(x) ((x) * S2RAD_CONSTANT)
#define RAD2S(x) ((x) * RAD2S_CONSTANT)

class cSAngle {
private:
    s16 mAngle;

public:
    const static cSAngle _0;
    const static cSAngle _1;
    const static cSAngle _90;
    const static cSAngle _180;
    const static cSAngle _270;
#ifdef __MWERKS__
    cSAngle() {}
    ~cSAngle() {}
    cSAngle(const cSAngle&);
#else
    cSAngle() = default;
    ~cSAngle() = default;
    cSAngle(const cSAngle&) = default;
#endif
    cSAngle(s16);
    cSAngle(float);
    s16 Val() const { return mAngle; }
    //void Set(s16 angle) { this->mAngle = angle; }
    void Val(const cSAngle&);
    void Val(s16);
    void Val(float);
    float Degree() const;
    float Radian() const;
    float Norm() const;
    s16 Abs() const;
    s16 Inv() const;
    float Sin() const;
    float Cos() const;
    float Tan() const;
    cSAngle operator-() const;
    cSAngle operator+(const cSAngle&) const;
    cSAngle operator-(const cSAngle&) const;
    void operator+=(const cSAngle&);
    void operator-=(const cSAngle&);
    cSAngle operator+(short) const;
    cSAngle operator-(short) const;
    void operator+=(short);
    void operator-=(short);
    cSAngle operator*(float) const;
    void operator*=(float);
    bool operator<(const cSAngle& other) const { return mAngle < other.mAngle; }
    bool operator>(const cSAngle& other) const { return mAngle > other.mAngle; }
    operator s16() const { return mAngle; }
    static inline cSAngle getMaxNegative() { return cSAngle((s16)-0x8000); }
    inline void mirrorAtMaxNeg() { *this = cSAngle((s16)-0x8000) - *this; }
};

cSAngle operator+(short, const cSAngle&);
cSAngle operator-(short, const cSAngle&);

struct cAngle {
    static f32 Radian_to_Degree(f32 rad) { return RAD2DEG(rad); }
    static f32 Degree_to_Radian(f32 deg) { return  DEG2RAD(deg); }
    static s16 Degree_to_SAngle(f32 deg) { return DEG2S(deg); }
    static f32 SAngle_to_Degree(s16 angle) { return S2DEG(angle); }
    static f32 SAngle_to_Radian(s16 angle) { return S2RAD(angle); }
    static s16 Radian_to_SAngle(f32 rad) { return RAD2S(rad); }
    static f32 SAngle_to_Normal(s16 angle) { return angle * (1.0f / 0x8000); }

    /* Converts Radian value into Degree value */
    static f32 r2d(f32 r) { return Radian_to_Degree(r); }

    /* Converts Degree value into Radian value */
    static f32 d2r(f32 d) { return Degree_to_Radian(d); }

    /* Converts Degree value to s16 angle */
    static s16 d2s(f32 d) { return Degree_to_SAngle(d); }

    /* Converts s16 angle to Degree value */
    static f32 s2d(s16 a) { return SAngle_to_Degree(a); }

    template <typename T>
    static T Adjust(T f1, T f2, T f3);
};

template <typename T>
T cAngle::Adjust(T f1, T f2, T f3) {
    while (f1 >= f3) {
        f1 -= f3 - f2;
    }
    while (f1 < f2) {
        f1 += f3 - f2;
    }
    return f1;
}

class cDegree {
private:
    float mDegree;

public:
    cDegree(float);
    ~cDegree() {}

    cDegree& Formal();
    void Val(float);
    float Radian() const;
    float Sin() const;
    float Cos() const;
};

class cSPolar {
private:
    float mRadial;
    cSAngle mAngle1;
    cSAngle mAngle2;

public:
    cSPolar() {}
    cSPolar(const cXyz&);
    cSPolar& Formal();
    void Val(float, short, short);
    void Val(const cXyz&);
    cXyz Xyz() const;
    void Globe(class cSGlobe*) const;

    void R(f32 i_radial) { mRadial = i_radial; }
    void U(cSAngle const& i_angle) { mAngle2 = i_angle.Val(); }
    void V(cSAngle const& i_angle) { mAngle1 = i_angle.Val(); }
};

class cSGlobe {
private:
    float mRadius;
    cSAngle mAzimuth;      // original: V
    cSAngle mInclination;  // original: U

public:
#ifdef __MWERKS__
    cSGlobe() {}
    ~cSGlobe() {}
    cSGlobe(const cSGlobe&);
#else
    cSGlobe() = default;
    ~cSGlobe() = default;
    cSGlobe(const cSGlobe&) = default;
#endif
    cSGlobe(float, short, short);
    cSGlobe(float, const cSAngle&, const cSAngle&);
    cSGlobe(const cXyz&);
    cSGlobe& Formal();
    void Val(const cSGlobe&);
    void Val(float, short, short);
    void Val(float, const cSAngle&, const cSAngle&);
    void Val(const cXyz&);
    float R() const { return mRadius; }
    const cSAngle& V() const { return mAzimuth; }
    const cSAngle& U() const { return mInclination; }

    void R(f32 i_radius) { mRadius = i_radius; }
    void U(cSAngle const& i_azimuth) { mAzimuth = i_azimuth.Val(); }
    void V(cSAngle const& i_inclination) { mInclination = i_inclination.Val(); }

    cXyz Xyz() const;
    void Polar(cSPolar*) const;
    cXyz Norm() const;
    cSGlobe& Invert();
};  // Size: 0x8

#endif /* C_ANGLE_H */
