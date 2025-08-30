#ifndef C_XYZ_H
#define C_XYZ_H

#include "math.h" // IWYU pragma: keep
#include "dolphin/mtx/vec.h"

struct cXy {
    f32 x;
    f32 y;
};

struct cXyz : Vec {
    static const cXyz Zero;
    static const cXyz BaseX;
    static const cXyz BaseY;
    static const cXyz BaseZ;
    static const cXyz BaseXY;
    static const cXyz BaseXZ;
    static const cXyz BaseYZ;
    static const cXyz BaseXYZ;
#ifdef __MWERKS__
    cXyz() {}
    ~cXyz() {}
    cXyz(const cXyz& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
#else
    cXyz() = default;
    ~cXyz() = default;
    cXyz(const cXyz& vec) = default;
#endif
    cXyz(f32 pX, f32 pY, f32 pZ) {
        x = pX;
        y = pY;
        z = pZ;
    }
    cXyz(const Vec& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    void operator=(const Vec& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
    cXyz operator+(const Vec&) const;
    cXyz operator-(const Vec&) const;
    cXyz operator*(f32) const;
    cXyz operator*(const Vec&) const;
    cXyz operator/(f32) const;
    // void operator=(const cXyz&);

    void operator+=(f32 f) {
        x += f;
        y += f;
        z += f;
    }
    void operator-=(f32 f) {
        x -= f;
        y -= f;
        z -= f;
    }
    void operator-=(const Vec& other) { VECSubtract(this, &other, this); }
    void operator+=(const Vec& other) { VECAdd(this, &other, this); }
    void operator*=(f32 scale) { VECScale(this, this, scale); }
    cXyz getCrossProduct(const Vec&) const;
    cXyz outprod(const Vec&) const;
    cXyz norm() const;
    cXyz normZP() const;
    cXyz normZC() const;
    cXyz normalize();
    cXyz normalizeZP();
    bool normalizeRS();
    bool operator==(const Vec&) const;
    bool operator!=(const Vec&) const;
    bool isZero() const;
    s16 atan2sX_Z() const;
    s16 atan2sY_XZ() const;

    void set(f32 pX, f32 pY, f32 pZ) {
        x = pX;
        y = pY;
        z = pZ;
    }

    void set(const Vec& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    void setall(f32 f) { set(f, f, f); }

    f32 getSquareMag() const { return VECSquareMag(this); }
    f32 getSquareDistance(const Vec& other) const { return VECSquareDistance(this, &other); }

    bool isNearZeroSquare() const { return (this->getSquareMag() < 8e-11f); }
    bool isNearZeroSquare(const cXyz& other) const { return (VECSquareMag(&other) < 8e-11f); }
    f32 abs2() const { return this->getSquareMag(); }
    f32 abs2(const Vec& other) const { return this->getSquareDistance(other); }
    f32 abs2XZ() const {
        cXyz tmp(this->x, 0, this->z);
        return tmp.abs2();
    }
    f32 abs2XZ(const Vec& other) const {
        cXyz tmp(this->x, 0, this->z);
        cXyz tmp2(other.x, 0, other.z);
        return tmp.abs2(tmp2);
    }
    f32 abs() const { return std::sqrtf(this->abs2()); }
    f32 abs(const Vec& other) const { return std::sqrtf(this->abs2(other)); }
    f32 absXZ() const { return std::sqrtf(this->abs2XZ()); }
    f32 absXZ(const Vec& other) const { return std::sqrtf(this->abs2XZ(other)); }

    f32 getDotProduct(const Vec& other) const { return VECDotProduct(this, &other); }
    f32 inprod(const Vec& other) const { return getDotProduct(other); }
    f32 inprodXZ(const Vec& other) const { return x * other.x + z * other.z; }

    // TODO
    // void operator*=(const Vec&) {}
    // void operator/=(f32) {}
    // void operator=(const cXyz&) {}
    // void print(const char*) {}
};

#endif /* C_XYZ_H */
